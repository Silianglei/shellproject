# Project 1: Shell[ing] out commands
by Akash Das and Si Liang Lei
##Features
1. Our shell takes in user input in the form of command 1 ; command 2 ..
  - Each command is seprated by one space, one semicolon followed by one space.
  - Example: ls -a -l ; echo test
2. Our shell is able to take in the commands exit and cd.
3. Our shell implements simple redirection using > (redirecting stdout) and < (redirecting stdin)
4. Our shell implements simple pipes
- Example: ls|wc

##Features Implemented But Were Unsuccessful

##Bugs

##Function Headers
#main.c
1. int main()
- Input: None
- Returns: 0
- Takes in the commands inputed by the user. Parses the commands separate by a semicolon into separate commands. Executes each of those commands. When each of the commands are executed, the program asks for user input again. Terminates if the command is exit.

#functions.c

1. int find_redirectInput(char ** args)
2. void redirectInput(int j, char ** command)
3. int find_redirectOutput(char ** args)
4. void redirectOutput(int j, char ** command)
5. char ** parse_args( char * line, char * delimeter)
6. void runCommand(int j, int k, char input[])
