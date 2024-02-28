
# Pipex 42

This project aims to create a program in C that mimics the Unix pipeline mechanism, specifically the `|` (pipe) operator. The pipe operator in Unix/Linux is used to chain multiple commands together, where the output of one command serves as input to the next.

In the context of this project, you'll be expected to create a program that can take two commands as input, execute the first command, capture its output, and then provide that output as input to the second command.

Some rules to keep in mind:

• Your project must be written in C (in accordance with the Norm).

• Your functions should not quit unexpectedly (segmentation fault, bus error, double free, etc) apart from undefined behaviors.

• All heap allocated memory space must be properly freed when necessary.

• You must submit a Makefile which will compile your source files to the required output with the flags -Wall, -Wextra and -Werror, use cc, and your Makefile must not relink. And the Makefile must at least contain the rules `$(NAME), all, clean, fclean and re (bonus if you want maximum score)`.

• If your project allows you to use your libft, you must copy its sources and its associated Makefile in a libft folder with its associated Makefile. Your project’s Makefile must compile the library by using its Makefile, then compile the project.

•Global variables are forbidden.


Mandatory part
Program name:

`pipex` Which has as arguments 4 elements:

`file1 cmd1 cmd2 file2`

• file1 and file2 -> file names.

• cmd1 and cmd2 -> shell commands with their parameters.


Files to turn in:

`Makefile, *.h, *.c`

External functs. allowed:

Libft authorized, and:

`1. open, close, read, write,
malloc, free, perror,
strerror, access, dup, dup2,
execve, exit, fork, pipe,
unlink, wait, waitpid`

`ft_printf and any equivalent YOU coded`

Examples:

`$> < file1 cmd1 | cmd2 > file2`

`$> ./pipex infile "ls -l" "wc -l" outfile`

Should behave like: 

`< infile ls -l | wc -l > outfile`

`$> ./pipex infile "grep a1" "wc -w" outfile`

Should behave like: 

`< infile grep a1 | wc -w > outfile`

