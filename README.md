# Pipex

## What's the project about?

The summary says:

> This project will let you discover in detail a UNIX mechanism that you already know by using it in your program. 

This is a little bit vague. What is this UNIX mechanism the summary is talking about? Probably the pipe. The pipe is a shell command, that to this point the student have already used. It enables us to pipe, i.e. to connect or chain different commands, so that the output of a command becomes the input for the next one. 

This is an example of piping two commands with the pipe control operator: `ls | grep ".txt"`.

In the description of the project is written:

> This project is about handling pipes. 
> Your programm will be exectuted as follows: `./pipex file1 cmd1 cmd2 file2`
> It must take 4 arguments
> - file1 and file2 are file names.
> - cmd1 and cmd2 are shell command with their parameters.

> It must behave exactly the same as the shell command below:
> `$> < file1 cmc1 | cmd2 > file2`
> Examples:
> `$> ./pipex infile "ls -l" "we -l" outfilei`
> Should behave like: < infile ls -l | wc -l > outfile
> `$> ./pipex infile "grep a1" "wc -w" outfile`
> Should behave like < infile grep a1 | wc -w > outfile. 

It is important to note that yes, using a pipe is the smartest solution to achieve the goal of the project, but it is not as fundamental as the ability to executing other programs from within your program. The project is more writing a  program  which makes possible to execute different programs and chaining output and input of these programs. We can reach the objective in a probably less efficient way also without the use of a pipe but it is feasable. What is not possible is to reach this objective without creating a new process, a child process and let this process execute a program. When we execute an external program from within our program, the process 'image' wich runs our program is replaced by the image of the process of the program we launched. This means that theoretically we could launch another program from within our program, but we would completely lost control on our program, cause the process, which runs the program would 'forget' about program and execute the instructions of the other program, wihtout knowing anything about our program and even when the process terminates the execution of the program it would not go back to our program/process cause this is been completely substituted. For this reason without forking the process and executing the command in the child process it would not be possible to chain input and output of two different program from within our program. 

To better understand this, is important to have clear in mind the difference between a program and a process. A program is just a list of instructions, a process is the 'action' of executing this instruction, which requires different resources. A program is like a shopping list, but go out and buy what is written in the shopping list, the action, needs a lot of more abilites. 






## New functions

- fork
- waitpid
- wait
- pipe
- dup
- dup2
- execve
- perror
- strerror
- unlink

## execve

### fork

The `fork` function is used to generate a new process. It is a system call function.

### wait, waitpid

The `wait` and `waitpid` functions are two of the four functions of the wait* family function, the other two being `wait3` and `wait4`. We use this function to wait for the termination of child processes in the parent process

## Old functions

- open
- close
- read
- write
- malloc
- free
- exit


