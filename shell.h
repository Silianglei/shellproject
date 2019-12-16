char ** parse_args( char * line, char * delimeter);
//Input: Takes a string to be parsed, and a string which is the delimeter the function parses by
//Returns: Returns an array of strings after the given string has been parsed by the given delimeter

void runCommand(int j, int k, char input[]);
// Input: Takes in two integers and a command separated by spaces
// Returns: Void
// Executes ```redirectOutput(j, args);``` if command contains >
// Executes ```redirectInput(j, args);``` if command contains <
// Exits the program if the command is "exit"
// Changes the current directory if the command contains "cd"
// Executes ```execvp(args[0], args);``` otherwise

int find_redirectOutput(char ** args);
//Input: Takes an array of strings
//Returns: Returns the index of the string that contains "<". If not found, returns -1.

int find_redirectInput(char ** args);
//Input: Takes an array of strings
//Returns: Returns the index of the string that contains "<". If not found, returns -1.

void redirectOutput(int j, char ** command);
// Input: Takes an integer, and an array of strings
// Returns: void
// Redirects the output of the given process into the given file

void redirectInput(int j, char ** command);
//Input: Takes an integer, and an array of strings
//Returns: Void
//Redirects the contents of the given file as the input for the given process

void redirectDouble(int j, char ** command);
// Input: Takes an integer and an array of strings
// Returns: void
// Redirects the contents of a given file as the input for a process. That output is then redirected into another given file.

int find_pipe(char ** args);
//Input: Takes an array of strings
// Returns: Returns the index of the string that contains "|". If not found, returns -1.

void pipeCommand(int j, char ** command);
// Input:Takes an integer, and an array of strings
//Returns: Void
// Runs the given process and use the output as the input for the second process

void redirectAppend(int j, char ** command);
// Input: Takes an integer and an array of strings
// Returns: void
// Redirects output to a file, appending the redirected output the end of the given file

int find_redirectAppend(char ** args);
// Input: Takes an array of strings
// Returns: Returns the index of the string that contains ">>". If not found, returns -1.
