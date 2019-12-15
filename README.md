# Project 1: Shell[ing] out commands
by Akash Das and Si Liang Lei
## Features
1. Our shell takes in user input in the form of command 1 ; command 2 ..
    - Each command is seprated by one space, one semicolon followed by one space.
    - Example: ls -a -l ; echo test
2. Our shell is able to take in the commands exit and cd.
3. Our shell implements simple redirection using > (redirecting stdout) and < (redirecting stdin)
4. Our shell implements simple pipes
    - Example: ls|wc

## Features Implemented But Were Unsuccessful
1. None so far

## Bugs
1. Cannot take in commands separated by just semicolons, no spaces. Must be of the format ```command 1 ; command 2 ; command 3... ```

## Function Headers
### main.c
1. int main()
    - Input: None
    - Returns: 0
    - Takes in the commands inputed by the user. Parses the commands separate by a semicolon into separate commands. Executes each of those commands. When each of the commands are executed, the program asks for user input again. Terminates if the command is exit.

### functions.c

1. int find_redirectInput(char ** args)
    - Input: Takes an array of strings
    - Returns: Returns the index of the string that contains "<". If not, returns -1.
2. void redirectInput(int j, char ** command)
    - Input: Takes an integer, and an array of strings
    - Returns: Void
    - Redirects the contents of a file as the Input for the command
3. int find_redirectOutput(char ** args)
    - Input: Takes an array of strings
    - Returns: Returns the index of the string that contains "<". If not, returns -1.
4. void redirectOutput(int j, char ** command)
    - Input: Takes an integer, and an array of strings
    - Returns: void
    - Redirects the output of the command into the given file
5. char ** parse_args( char * line, char * delimeter)
    - Input: Takes a string to be parsed, and a string which is the delimeter the function parses by
    - Returns: Returns an array of strings after the string has been parsed by the given delimeter
6. void runCommand(int j, int k, char input[])
    - Input: Takes in two integers and a command separated by spaces
    - Returns: Void
    - Executes ```redirectOutput(j, args);``` if command contains >
    - Executes ```redirectInput(j, args);``` if command contains <
    - Exits the program if the command is "exit"
    - Changes the current directory if the command contains "cd"
    - Executes ```execvp(args[0], args);``` otherwise
