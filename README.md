# Motivation
This project aims to provide a alias creating tool in Windows for MSYS2 or GitBash users, to offer common alias across different shell enviroments.


# How to install
1.Download and compile via makefile

    git clone https://github.com/moskensoap/bcplink.git
    cd bcplink
    make

2.Copy the generated bcplink.exe to a directory included in your PATH.

# Command-line Usage

    Usage: bcplink [options] Alias Command [CommandParameters]
### Options:

        -v, --v, -version, --version    Display version info.
        -h, --h, -help, --help          Display this help message.
        -bash, -cmd, -ps1               Manually choose the type of script to create.
        -y, -Y, -yes, -f, -F, -force    Force overwrite of existing scripts.
### Arguments:
        Alias                   The name of the Alias files to be created: Alias.cmd Alias.ps1 Alias(for Bash).
        Command                 The Alias files will run the Command
        CommandParameters       Optional parameters of the Command.

# Inspiration

This project was originally inspired by npm, bundled with node.js, which automatically creates scripts to run its packages.

# Examples
## reboot script
To create a reboot script, navigate to the directory included in your PATH where you want to store the scripts (e.g., D:/code/cmd), to run:

    #CMD
    D:
    cd D:/code/cmd
    #Powershell
    cd D:/code/cmd
    #bash
    cd /d/code/cmd
 and run:

    bcplink reboot shutdown -r -t 0
Three scripts will be created in current directory.

__reboot.cmd__

    @ECHO off
    "shutdown" "-r" "-t" "0" %*

__reboot.ps1__

    	# Support pipeline input
    if ($MyInvocation.ExpectingInput) {
    	$input | & "shutdown" "-r" "-t" "0" $args
    } else {
    	& "shutdown" "-r" "-t" "0" $args
    }

__reboot__

    #!/bin/sh
    exec "shutdown" "-r" "-t" "0" "$@"

Using:

    reboot
It will automatically call 'reboot.cmd' in CMD, call 'reboot.ps1' in PowerShell, call 'reboot' in Bash.

## Version control for Python

Running the following command from any location:

    bcplink "D:/code/cmd/python311" "D:\Develop\Python\Python311\python.exe"
will generate three scripts in 'D:/code/cmd' directory.

__python311.cmd__

    @ECHO off
    "D:\Develop\Python\Python311\python.exe" %*

__python311.ps1__

	    # Support pipeline input
    if ($MyInvocation.ExpectingInput) {
	    $input | & "D:\Develop\Python\Python311\python.exe" $args
    } else {
    	& "D:\Develop\Python\Python311\python.exe" $args
    }

__python311__

    #!/bin/sh
    exec "/d/Develop/Python/Python311/python.exe" "$@"

## Other usefull link
    #CMD
    D:
    cd D:/code/cmd
    #Powershell
    cd D:/code/cmd
    #bash
    cd /d/code/cmd
and run:
### Create a Link to Show Git History in the Command Line
    bcplink git-log git log --pretty=oneline --all --graph --abbrev-commit

### Create a Link from "mingw32-make" to "make"
    bcplink make mingw32-make

### Run Lua with the CODE RUNNER Extension Without Setting in VS Code 
    bcplink lua lua54
    bcplink luac luac54
    bcplink wlua wlua54

### make ls.exe alias like in ubuntu after adding msys64/usr/bin to PATH.
    bcplink lc ls.exe --color=auto
    bcplink lf ls.exe --color=auto -F
    bcplink l ls.exe --color=auto -lh
    bcplink ll ls.exe --color=auto -lah
    bcplink la ls.exe --color=auto -A
    bcplink lm ls.exe --color=auto -m
    bcplink lr ls.exe --color=auto -R
    bcplink lg ls.exe --color=auto -l --group-directories-first
### make grep.exe alias like in ubuntu after adding msys64/usr/bin to PATH.
    bcplink grepc grep.exe --color=auto --exclude-dir={.bzr,CVS,.git,.hg,.svn,.idea,.tox}
    bcplink grepe grep.exe -E --color=auto --exclude-dir={.bzr,CVS,.git,.hg,.svn,.idea,.tox}
    bcplink grepf grep.exe -F --color=auto --exclude-dir={.bzr,CVS,.git,.hg,.svn,.idea,.tox}
### make diff.exe alias like in ubuntu after adding msys64/usr/bin to PATH.  
    bcplink diffc diff.exe --color
### nodejs version control
    bcplink node20 D:\Develop\Nodejs\node-v20.9.0-win-x64\node
    bcplink node18 D:\Develop\Nodejs\node-v18.17.1-win-x64\node.exe
    bcplink npm20 D:\Develop\Nodejs\node-v20.9.0-win-x64\npm
    bcplink npm18 D:\Develop\Nodejs\node-v18.17.1-win-x64\npm

# Acknowledgements and Bug Reporting
Special Thanks to VS Code (https://code.visualstudio.com). If you have any suggestions or bug reports, don't hesitate to report them. Your feedback is invaluable to make this project better.