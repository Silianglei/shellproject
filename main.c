#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <dirent.h>


char ** parse_args( char * line ){
  char *current = line;
  char *token;
  char ** args = malloc(10 * sizeof(char*));
  int i = 0;
  while(current != NULL){
    args[i] = strsep(&current, " ");
    //args[i] = token;
    i++;
  }
  args[i] = NULL;
  return args;
}

int main(){
  //printf("Input Your Command:");
  char input[100];
  fgets(input, sizeof(input), stdin);
  input[strlen(input)-1] = 0;
  char * line = input;
  printf("%s\n", line );
  char ** args = parse_args( line );
  execvp(args[0], args);
  return 0;
}
