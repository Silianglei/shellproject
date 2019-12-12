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
#include "headers.h"
#include "functions.c"


//Continously recieves user input
int main(int argc, char * argv[]){
  int j;
  int k;
  char prompt[100];
  char input[100];
  char ** commandsToRun;
  printf("%s# ", getcwd(prompt, 100));
  while(1){
    input[strlen(input) - 1] = 0;
    fgets(input, sizeof(input), stdin);
    char ** commandsToRun = parse_args(input, ";");
    int i;
    for(i=0 ; commandsToRun[i] != NULL ; i++){
      //printf("'%s'\n", commandsToRun[i]);
      if(strchr(commandsToRun[i], 62) != NULL){
        runRedirect_in(commandsToRun[i]);
      }
      else if(strchr(commandsToRun[i], 60) != NULL){
        runRedirect_out(commandsToRun[i]);
      }
      else runCommand(k, commandsToRun[i]);
      wait(&j);
    }
    printf("%s# ", getcwd(prompt, 100));
  }
}
