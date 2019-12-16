# Project 1: Shell[ing] out commands
by Akash Das and Si Liang Lei
## Features
1. Our shell takes in user input in the form of ```command 1 ; command 2 ; command 3... ```
    - Each command is seprated by one space, one semicolon followed by one space.
    - Example: ```ls -a -l ; echo test```
2. Our shell implements exit and cd.
3. Our shell implements simple redirection using > (redirecting stdout) and < (redirecting stdin)
    - Example: ```w > wholist``` and ```./program < commands.txt```
4. Our shell implements simple pipes
    - Example: ```ls|wc```
5. ADDITIONAL FEATURE: Our shell implements ">>" which redirects output to a file, appending the redirected output  the end of the given file
    - Example: ```ls -a -l >> testfile```

## Features Implemented But Were Unsuccessful
None

## Bugs
1. Cannot take in commands separated by just semicolons. All items on the command line are to be separated by a single space. Must be of the format ```command 1 ; command 2 ; command 3... ```
2. Unless there is an exit in ```commands.txt```, the shell repeatedly prints the current directory. If there is an ```exit```, the shell prints the current directory a finite number of times and then terminates.

## Function Headers
### main.c
Takes in the commands inputed by the user. Parses the commands separate by a semicolon into separate commands. Executes each of those commands. When each of the commands are executed, the program asks for user input again. Terminates if the command is exit.

### functions.c

1. ```int find_redirectInput(char ** args)```
    - Input: Takes an array of strings
    - Returns: Returns the index of the string that contains "<". If not found, returns -1.
2. ```int find_redirectOutput(char ** args)```
    - Input: Takes an array of strings
    - Returns: Returns the index of the string that contains "<". If not found, returns -1.
3. ```int find_pipe(char ** args)```
    - Input: Takes an array of strings
    - Returns: Returns the index of the string that contains "|". If not found, returns -1.
4. ```int find_redirectAppend(char ** args)```
    - Input: Takes an array of strings
    - Returns: Returns the index of the string that contains ">>". If not found, returns -1.
4. ```void redirectInput(int j, char ** command)```
    - Input: Takes an integer, and an array of strings
    - Returns: Void
    - Redirects the contents of the given file as the input for the given process
5. ```void redirectOutput(int j, char ** command)```
    - Input: Takes an integer, and an array of strings
    - Returns: void
    - Redirects the output of the given process into the given file
6. ```void pipeCommand(int j, char ** command)```
    - Input:Takes an integer, and an array of strings
    - Returns: Void
    - Runs the given process and use the output as the input for the second process
7. ```char ** parse_args( char * line, char * delimeter)```
    - Input: Takes a string to be parsed, and a string which is the delimeter the function parses by
    - Returns: Returns an array of strings after the given string has been parsed by the given delimeter
8. ```void redirectDouble(int j, char ** command)```
    - Input: Takes an integer and an array of strings
    - Returns: void
    - Redirects the contents of a given file as the input for a process. That output is then redirected into another given file.
9. ```void redirectAppend(int j, char ** command)```
    - Input: Takes an integer and an array of strings
    - Returns: void
    - Redirects output to a file, appending the redirected output  the end of the given file
10. ```void runCommand(int j, int k, char input[])```
    - Input: Takes in two integers and a command separated by spaces
    - Returns: Void
    - Executes ```redirectOutput(j, args);``` if command contains >
    - Executes ```redirectInput(j, args);``` if command contains <
    - Exits the program if the command is "exit"
    - Changes the current directory if the command contains "cd"
    - Executes ```execvp(args[0], args);``` otherwise
