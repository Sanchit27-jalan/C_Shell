# Description
This is a simple representation of the Bash shell coded in the C Programming language as a part of the Operating Systems and Networks course at IIIT-Hyderabad Monsoon 2023 semester. This is the final submission<br>
## ABOUT

It has some of the following features as of now:

- Colourful shell display with username/hostname and current directory.
- Can run some built-in commands such as `warp`, `peek` (With -a and -l flags).
- Other Commands - `proclore`, `seek` (with -d and -f flags)
- Stores `pastevents` of upto 15, for all the sessions.
- Error Handling
- Can run both `background` and `foreground` processes. (For any other shell commands)
- Multiple Command Execution in a single line using `;`.
- `exit` is used to exit the shell.
- I/O Redirection along with pipes and < & >/>>.
- Signal Handling (Ctrl-C, Ctrl-Z, Ctrl-D)

# Various files 
header.h = Includes all the header files <br>
foreground.c= it contains the code for execution of foreground/background process<br>
main.c= it contains the main code in which prompt is invoked and input is being taken<br>
pastevents.c=it contains the code for execution of pastevent<br>
peek.c=it contains the code for execution of peek <br>
proclore.c=it contains the code for execution of proclore<br>
prompt.c=it contains the code for execution of prompt<br>
seek.c=it contains the code for execution of seek<br>
warp.c=It has the code for execution of warp .<br>
execution.c = it is the execution file which executes the input<br>
neonate.c = it implements the neonate function<br>
iman.c = implements iman<br>
activities.c = inplements activities command<br>

# How to Run
Go to directory in which you save the file <br>
Run make in terminal <br>
Then run ./a.out<br>

### COMMANDS & INSTRUCTIONS
- ### `warp` Command
The `warp` command is designed to navigate directories in a shell environment. It supports both absolute and relative paths, including paths from the home directory. The command recognizes specific flags to represent common directory shortcuts:

- `~`: Represents the home directory of the shell.
- `-`: Represents the path to the previous directory.
- `.`: Represents the path to the current directory.
- `..`: Represents the path to the parent directory.

When using the `warp` command, users can provide one or more arguments. If multiple arguments are present, the `warp` command executes sequentially with each argument being the directory path (from left to right). If no arguments are provided, the `warp` command defaults to navigating into the home directory.

```
Usage

warp <path_to_directory>
```
- ### `peek` Command

The `peek` command lists all the files and directories in the specified directory in lexicographic order. By default, `peek` does not show hidden files. The command supports the following flags:

- `-l`: Displays extra information.
- `-a`: Displays all files, including hidden files.

Similar to the `warp` command, `peek` supports the use of symbols:

- `.`: Represents the current directory.
- `..`: Represents the parent directory.
- `~`: Represents the home directory.
- `-`: Represents the previous directory.

The command supports both relative and absolute paths. If no argument is given, `peek` will show the contents of the current working directory. Multiple arguments will not be given as input.
```
 Usage

peek <flags> <path/name>
```

- ### `pastevents` Command

The `pastevents` command facilitates the management and retrieval of the most recent command statements in a shell environment. This history is persistent across different shell runs and includes features such as displaying past events, clearing the history, and executing previous commands.
- The system maintains a record of the 15 most recent command statements, including their arguments.
- Commands identical to the previous one are not stored.
- Statements containing `pastevents` or `pastevents purge` are excluded from storage.
- A file p.txt is created for storing pastevents (if it already exists then it will be used for storing pastevents and it assumes that it was used for storing pastevents previously too)

```
Usage

pastevents
-Displays the 15 most recent command statements along with their respective arguments.
pastevents purge
-Clears all stored past events.
pastevents execute <index>
-Executes the command at the specified position in the past events history (ordered from most recent to oldest).
```
- ### `proclore` Command

The `proclore` command is used to obtain information regarding a process. If an argument is missing, it prints information about your shell.
The following information is displayed:

- **PID:** Process ID.
- **Process Status:** It includes the process status, which can be one of the following - R, R+, S, S+, Z.
- **Process Group:** The process group to which the process belongs.
- **Virtual Memory:** Information about the virtual memory used by the process.
- **Executable Path:** The path to the executable of the process.

 Usage

```
proclore [pid]
```
- ### `exit`
    ```
    Usage: exit
    ```
    Alaias for `exit` -> `quit`
- ### `seek` Command

The `seek` command looks for a file or directory in the specified target directory (or the current directory if none is specified). It returns a list of relative paths (from the target directory) of all matching files/directories. Files are displayed in green, and directories are displayed in blue, with each entry separated by a newline character.

Flags 
- `-d`: Only look for directories (ignore files even if the name matches).
- `-f`: Only look for files (ignore directories even if the name matches).
- `-e`: This flag is effective only when a single file or a single directory with the specified name is found. If only one file (and no directories) is found, it prints the file's path. If only one directory (and no files) is found, it changes the current working directory to that directory. Otherwise, the flag has no effect. This flag works with both the `-d` and `-f` flags. If the `-e` flag is enabled but the directory lacks execute permissions or the file lacks read permissions, it outputs "Missing permissions for task!"

Arguments

1. The target name that the user is looking for. It must not contain whitespace characters.
2. The path to the target directory where the search will be performed. If missing, the target directory is the current working directory. The target directory's tree is searched, not just the directory itself.
```
 Usage

seek [options] <target_name> [target_directory]
```
- ### `activities`

The following specification outlines the requirements for printing a list of all processes currently running that were spawned by your shell. The list should be displayed in lexicographic order and include the following information for each process:

- PID (Process ID)
- Command Name
- State: Running or Stopped

```
Usage

activities
```
- ### `ping` Command

The `ping` command is used to send signals to processes. Provide the PID of a process and the signal number as arguments. The command sends the corresponding signal to the specified process. If the process with the given PID does not exist, it prints an error message: "No such process found." The signal number is taken modulo 32 before checking which signal it belongs to, assuming an x86/ARM machine.
```
Usage

ping <pid> <signal_number>
```
- ### `fg`
    ```
    Usage: fg <pid>
    ```
    - Brings the process into foreground and set it running.
    - If no process with the given PID exists, it prints "No such process found."
- ### `bg`
    ```
    Usage: bg <pid>
    ```
    - Sets the given id background process in running state.
    - If no process with the given PID exists, it prints "No such process found."
- ### `bg`
    ```
    Usage: bg <pid>
    ```
    - Sets the given id background process in running state.
    - If no process with the given PID exists, it prints "No such process found."
- ### `neonate` Command

The `neonate` command prints the Process-ID of the most recently created process on the system. The PID will be printed every [time_arg] seconds until the key 'x' is pressed.

```
Usage

neonate -n [time_arg]
```
- ### `iMan` Command

The `iMan` command fetches man pages from the website [http://man.he.net/](http://man.he.net/). 

```
Usage

iMan <command_name>
```
- ### `<command>`
    - Runs the command in the foreground.
    - If `&` is added at the end, will run the command in background.


---