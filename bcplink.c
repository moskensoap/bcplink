#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>

int IsThereMinusH(char *OptionsArgv[])
{
    char *help_flags[] = {"-h", "--h", "-help", "--help"};
    while (*OptionsArgv)
    {
        for (int i = 0; i < sizeof(help_flags) / sizeof(help_flags[0]); i++)
        {
            if (strcmp(*OptionsArgv, help_flags[i]) == 0)
            {
                return 1;
            }
        }
        OptionsArgv++;
    }
    return 0;
}

int IsThereMinusV(char *OptionsArgv[])
{
    char *help_flags[] = {"-v", "--v", "-version", "--version"};
    while (*OptionsArgv)
    {
        for (int i = 0; i < sizeof(help_flags) / sizeof(help_flags[0]); i++)
        {
            if (strcmp(*OptionsArgv, help_flags[i]) == 0)
            {
                return 1;
            }
        }
        OptionsArgv++;
    }
    return 0;
}

int IsThereMinusY(char *OptionsArgv[])
{
    char *help_flags[] = {"-y", "-Y", "-yes", "-f", "-F", "-force"};
    while (*OptionsArgv)
    {
        for (int i = 0; i < sizeof(help_flags) / sizeof(help_flags[0]); i++)
        {
            if (strcmp(*OptionsArgv, help_flags[i]) == 0)
            {
                return 1;
            }
        }
        OptionsArgv++;
    }
    return 0;
}

int IsThere(char *OptionsArgv[], char *input)
{
    while (*OptionsArgv)
    {
        if (strcmp(*OptionsArgv, input) == 0)
        {
            return 1;
        }
        OptionsArgv++;
    }
    return 0;
}

void ShowVersion(void)
{
    printf("bcplink version 0.0.2\n");
    printf("bcplink is a command-line tool that automatically creates Bash, CMD, and PowerShell script links\n");
    printf("\tto set up command aliases for running target scripts or programs.\n");
    printf("To see detailed instructions and examples, run <bcplink -h>\n");
}

void ShowHelp(void)
{
    printf("\nUsage: bcplink [options] linkname TargetName [TargetParameters]\n");
    printf("\nOptions:\n");
    printf("\t-v,--v,-version,--version\tDisplay version info.\n");
    printf("\t-h,--h,-help,--help\t\tDisplay this help message.\n");
    printf("\t-bash,-cmd,-ps1\t\t\tManually choose the type of script to create.\n");
    printf("\t-y,-Y,-yes,-f,-F,-force\t\tForce overwrite of existing scripts.\n");
    printf("\nDescription:\n");
    printf("\tbcplink creates script files that link to other scripts or programs,\n");
    printf("\t\tsetting up command aliases for convenient execution.\n");
    printf("\nArguments:\n");
    printf("\tlinkname\t\tThe name of the links to be created: linkname.cmd linkname.ps1 linkname(for Git Bash).\n");
    printf("\tTargetName\t\tThe name of the target script or program to be linked.\n");
    printf("\tTargetParameters\tOptional parameters to be passed to the target script or program.\n");
    printf("\nExamples:\n");
    printf("\t1. Create restart scripts in the current directory:\n");
    printf("\t  bcplink restart shutdown -r -t 0\n");
    printf("\n\t2. Create links to a Python executable:\n");
    printf("\t  bcplink \"D:\\code\\cmd\\python311\" \"D:\\Develop\\Python\\Python311\\python.exe\"\n");
    printf("\t  This allows you to run 'python311' as if you were running 'python.exe' after adding 'D:\\code\\cmd' to the PATH.\n");
}

int SeparateOptions(char *argv[], char *OptionsArgv[], char *NoOptionsArgv[])
{
    NoOptionsArgv[0] = argv[0];
    int i = 1, j = 0, k = 1, targetflag = 0;
    while (argv[i])
    {
        if ((argv[i][0] == '-') && (targetflag == 0))
        {
            OptionsArgv[j] = argv[i];
            j++;
        }
        else
        {
            targetflag = 1;
            NoOptionsArgv[k] = argv[i];
            k++;
        }
        i++;
    }
    OptionsArgv[j] = argv[i];
    NoOptionsArgv[k] = argv[i];
    return (k);
}

void ToWindowsString(char *NoOptionsArgv[], char *FormatArgv[])
{
    int i = 0;
    while (NoOptionsArgv[i])
    {
        FormatArgv[i] = NoOptionsArgv[i];
        for (int j = 0; FormatArgv[i][j] != 0; j++)
        {
            if (FormatArgv[i][j] == '/')
            {
                FormatArgv[i][j] = '\\';
            }
        }

        for (int j = 0; FormatArgv[i][j] != 0; j++)
        {
            if (FormatArgv[i][j] == '\\')
            {
                if (FormatArgv[i][j + 1] == '\\')
                {
                    do
                    {
                        for (int k = j + 1; FormatArgv[i][k] != 0; k++)
                            FormatArgv[i][k] = FormatArgv[i][k + 1];
                    } while (FormatArgv[i][j + 1] == '\\');
                }
            }
        }

        if (strlen(FormatArgv[i]) >= 2 && FormatArgv[i][0] == '\\' && FormatArgv[i][2] == '\\')
        {
            FormatArgv[i][0] = toupper(FormatArgv[i][1]);
            FormatArgv[i][1] = ':';
        }
        i++;
    }
    FormatArgv[i] = NoOptionsArgv[i];
}

void ToLinuxString(char *NoOptionsArgv[], char *FormatArgv[])
{
    int i = 0;
    while (NoOptionsArgv[i])
    {
        FormatArgv[i] = NoOptionsArgv[i];
        for (int j = 0; FormatArgv[i][j] != 0; j++)
        {
            if (FormatArgv[i][j] == '\\')
            {
                FormatArgv[i][j] = '/';
            }
        }

        for (int j = 0; FormatArgv[i][j] != 0; j++)
        {
            if (FormatArgv[i][j] == '/')
            {
                if (FormatArgv[i][j + 1] == '/')
                {
                    do
                    {
                        for (int k = j + 1; FormatArgv[i][k] != 0; k++)
                            FormatArgv[i][k] = FormatArgv[i][k + 1];
                    } while (FormatArgv[i][j + 1] == '/');
                }
            }
        }

        if (strlen(FormatArgv[i]) >= 2 && FormatArgv[i][1] == ':' && FormatArgv[i][2] == '/')
        {
            FormatArgv[i][1] = tolower(FormatArgv[i][0]);
            FormatArgv[i][0] = '/';
        }
        i++;
    }
    FormatArgv[i] = NoOptionsArgv[i];

    for (int j = 0; FormatArgv[1][j] != 0; j++)
    {
        if (FormatArgv[1][j] == '/')
        {
            FormatArgv[1][j] = '\\';
        }
    }
    if (strlen(FormatArgv[1]) >= 2 && FormatArgv[1][0] == '\\' && FormatArgv[1][2] == '\\')
    {
        FormatArgv[1][0] = toupper(FormatArgv[1][1]);
        FormatArgv[1][1] = ':';
    }
}

int CreatCMD(int argc, char *NoOptionsArgv[], char yflag)
{
    char *FormatArgv[argc];
    FILE *fpCMD;
    ToWindowsString(NoOptionsArgv, FormatArgv);
    int length_linkname = strlen(FormatArgv[1]);
    char linkname_dot_cmd[length_linkname + 5];
    strcpy(linkname_dot_cmd, FormatArgv[1]);
    strcat(linkname_dot_cmd, ".cmd");
    if (yflag == 0)
    {
        fpCMD = fopen(linkname_dot_cmd, "r");
        if (fpCMD != NULL)
        {
            fclose(fpCMD);
            printf("warning: %s exists, use -y to overwrite.\n", linkname_dot_cmd);
            return 1;
        }
    }
    fpCMD = fopen(linkname_dot_cmd, "w");
    if (fpCMD == NULL)
    {
        printf("warning: cannot open %s for writing.\n", linkname_dot_cmd);
        return 2;
    }
    fprintf(fpCMD, "@ECHO off\n");
    for (int i = 2; FormatArgv[i] != 0; i++)
    {
        fprintf(fpCMD, "\"");
        fprintf(fpCMD, FormatArgv[i]);
        fprintf(fpCMD, "\" ");
    }
    fprintf(fpCMD, "%%*");
    fclose(fpCMD);
    return 0;
}

int CreatPS1(int argc, char *NoOptionsArgv[], char yflag)
{
    char *FormatArgv[argc];
    FILE *fpPS1;
    ToWindowsString(NoOptionsArgv, FormatArgv);
    int length_linkname = strlen(FormatArgv[1]);
    char linkname_dot_ps1[length_linkname + 5];
    strcpy(linkname_dot_ps1, FormatArgv[1]);
    strcat(linkname_dot_ps1, ".ps1");
    if (yflag == 0)
    {
        fpPS1 = fopen(linkname_dot_ps1, "r");
        if (fpPS1 != NULL)
        {
            fclose(fpPS1);
            printf("warning: %s exists, use -y to overwrite.\n", linkname_dot_ps1);
            return 10;
        }
    }
    fpPS1 = fopen(linkname_dot_ps1, "w");
    if (fpPS1 == NULL)
    {
        printf("warning: cannot open %s for writing.\n", linkname_dot_ps1);
        return 20;
    }
    fprintf(fpPS1, "\t# Support pipeline input\n");

    fprintf(fpPS1, "if ($MyInvocation.ExpectingInput) {\n");
    fprintf(fpPS1, "\t$input | & ");
    for (int i = 2; FormatArgv[i] != 0; i++)
    {
        fprintf(fpPS1, "\"");
        fprintf(fpPS1, FormatArgv[i]);
        fprintf(fpPS1, "\" ");
    }
    fprintf(fpPS1, "$args\n");
    fprintf(fpPS1, "} else {\n");
    fprintf(fpPS1, "\t& ");
    for (int i = 2; FormatArgv[i] != 0; i++)
    {
        fprintf(fpPS1, "\"");
        fprintf(fpPS1, FormatArgv[i]);
        fprintf(fpPS1, "\" ");
    }
    fprintf(fpPS1, "$args\n");
    fprintf(fpPS1, "}");

    fclose(fpPS1);
    return 0;
}

int CreatBASH(int argc, char *NoOptionsArgv[], char yflag)
{
    char *FormatArgv[argc];
    FILE *fpBASH;
    ToLinuxString(NoOptionsArgv, FormatArgv);
    int length_linkname = strlen(FormatArgv[1]);
    char linkname_dot_sh[length_linkname + 1];
    strcpy(linkname_dot_sh, FormatArgv[1]);
    if (yflag == 0)
    {
        fpBASH = fopen(linkname_dot_sh, "r");
        if (fpBASH != NULL)
        {
            fclose(fpBASH);
            printf("warning: %s exists, use -y to overwrite.\n", linkname_dot_sh);
            return 100;
        }
    }
    fpBASH = fopen(linkname_dot_sh, "w");
    if (fpBASH == NULL)
    {
        printf("warning: cannot open %s for writing.\n", linkname_dot_sh);
        return 200;
    }
    fprintf(fpBASH, "#!/bin/sh\n");
    fprintf(fpBASH, "exec");
    fprintf(fpBASH, " ");
    for (int i = 2; FormatArgv[i] != 0; i++)
    {
        fprintf(fpBASH, "\"");
        fprintf(fpBASH, FormatArgv[i]);
        fprintf(fpBASH, "\" ");
    }
    fprintf(fpBASH, "\"$@\"");
    fclose(fpBASH);
    return 0;
}

int main(int argc, char *argv[])
{
    char flag, yflag;
    char *OptionsArgv[argc], *NoOptionsArgv[argc];
    int NoOptionsLength;

    NoOptionsLength = SeparateOptions(argv, OptionsArgv, NoOptionsArgv);

    if (argc == 1 || IsThereMinusV(OptionsArgv))
    {
        ShowVersion();
    }

    if (IsThereMinusH(OptionsArgv))
    {
        ShowHelp();
    }

    if (NoOptionsLength <= 1)
        return 0;
    if (NoOptionsLength == 2)
    {
        printf("\nError: Missing TargetName for input.\n");
        ShowHelp();
        return (-1);
    }

    if (IsThereMinusY(OptionsArgv))
        yflag = 1;
    if (IsThere(OptionsArgv, "-cmd"))
        flag = flag + 1;
    if (IsThere(OptionsArgv, "-ps1"))
        flag = flag + 2;
    if (IsThere(OptionsArgv, "-bash"))
        flag = flag + 4;
    switch (flag)
    {
    case 0:
    case 7:
        return (CreatCMD(argc, NoOptionsArgv, yflag) + CreatPS1(argc, NoOptionsArgv, yflag) + CreatBASH(argc, NoOptionsArgv, yflag));
        break;
    case 1:
        return (CreatCMD(argc, NoOptionsArgv, yflag));
        break;
    case 2:
        return (CreatPS1(argc, NoOptionsArgv, yflag));
        break;
    case 3:
        return (CreatCMD(argc, NoOptionsArgv, yflag) + CreatPS1(argc, NoOptionsArgv, yflag));
        break;
    case 4:
        return (CreatBASH(argc, NoOptionsArgv, yflag));
        break;
    case 5:
        return (CreatCMD(argc, NoOptionsArgv, yflag) + CreatBASH(argc, NoOptionsArgv, yflag));
        break;
    case 6:
        return (CreatPS1(argc, NoOptionsArgv, yflag) + CreatBASH(argc, NoOptionsArgv, yflag));
        break;
    default:
        break;
    }

    return 0;
}