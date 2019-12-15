char ** parse_args( char * line, char * delimeter);

void runCommand(int j, int k, char input[]);

int find_redirectOutput(char ** args);

int find_redirectInput(char ** args);

void redirectOutput(int j, char ** command);

void redirectInput(int j, char ** command);
