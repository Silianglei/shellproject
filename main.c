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
  char *s1 = line;
  char ** arguments = malloc(5 * sizeof(char *));
  int index = 0;
  while(s1 != NULL){
    arguments[index] = strsep(&s1, " ");
    //printf("%d: [%s]\n",index, arguments[index]);
    index++;
  }
  arguments[index] = NULL;
  return arguments;
}

int main(){
  return 0;
}
