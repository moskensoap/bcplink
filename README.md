# Motivation
A quick search reveals that each type of Windows shell (Git Bash, PowerShell, CMD) offers its own methods for setting local aliases. However, there is a lack of a global alias management tool, and creating aliases for combined commands is not supported.

This project starts with Windows but has plans to expand to Linux. Its goal is to provide a global alias creation tool, especially for combined commands, to benefit users across different shell environments.

# How to install
You need to set up a c language on your local computer. We recommend using the following open-source toolchains:

MSYS2 (https://www.msys2.org): After installing MSYS2, execute the following command:

    pacman -S mingw-w64-ucrt-x86_64-toolchain.
Alternatively, you can use a smaller standalone compiler:

    pacman -S ucrt64/mingw-w64-ucrt-x86_64-gcc

If you prefer, you can download the binaries for MinGW64 from MinGW-w64(https://www.mingw-w64.org) or SourceForge(https://sourceforge.net/projects/mingw-w64/files/mingw-w64/mingw-w64-release). We recommend using MinGW-W64 GCC-8.1.0.

Once installed, make sure to add the directory containing gcc.exe to your computer's PATH to run gcc.exe from any location. After that, create a directory and run the following command (make sure you have Git installed, https://git-scm.com):

    git clone https://github.com/moskensoap/bcplink.git

Alternatively, you can copy the bcplink.c code from this repository to your local files. Compile it using the following command:

    gcc bcplink.c -o bcplink.exe

Move the generated bcplink.exe to a directory included in your PATH. After completing these steps, you can run bcplink anywhere. 


# Command-line Usage

    bcplink [options] linkname TargetName [TargetParameters]
### Options:

        -v,--v,-version,--version       Display version info.
        -h,--h,-help,--help             Display this help message.
        -bash,-cmd,-ps1                 Manually choose the type of script to create.
        -y,-Y,-yes,-f,-F,-force         Force overwrite of existing scripts.
### Arguments:
        linkname                The name of the links to be created: linkname.cmd linkname.ps1 linkname(for Git Bash).
        TargetName              The name of the target script or program to be linked.
        TargetParameters        Optional parameters to be passed to the target script or program.

# Inspiration

This project was originally inspired by npm, bundled with node.js, which automatically creates scripts to run its packages.


# Examples
## restart script
if you are in the directory "D:/code/cmd" and run

    bcplink restart shutdown -r -t 0
Three scripts will be created in current directory.

__restart.cmd__

    @ECHO off
    "shutdown" "-r" "-t" "0" %*

__restart.ps1__

    	# Support pipeline input
    if ($MyInvocation.ExpectingInput) {
    	$input | & "shutdown" "-r" "-t" "0" $args
    } else {
    	& "shutdown" "-r" "-t" "0" $args
    }

__restart__

    #!/bin/sh
    exec "shutdown" "-r" "-t" "0" "$@"

You can run the full script name, which will call its respective shell to execute. When you run just "restart," the shell will automatically choose the appropriate script to run.

For example, in Command Prompt, if you run "restart," "restart.cmd" will be executed. If you run "restart.ps1," the script will invoke PowerShell to run silently and return its output.

## Version control for Python

Running the following command from any location:

    bcplink "D:/code/cmd/python311" "D:\Develop\Python\Python311\python.exe"
will generate three scripts in the 'D:/code/cmd' directory.

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
### Create a Link to Show Git History in the Command Line
    bcplink git-log git log --pretty=oneline --all --graph --abbrev-commit

### Create a Link from "mingw32-make" to "make"
    bcplink make mingw32-make

### Run Lua with the CODE RUNNER Extension Without Setting in VS Code 
    bcplink lua lua54
    bcplink luac luac54
    bcplink wlua wlua54

# Acknowledgements and Bug Reporting
Special Thanks to the VS Code(https://code.visualstudio.com) for supporting the development of this project. We are also eager to assist with any bug reports and issues submitted by the community. Your feedback is invaluable in making this project better.