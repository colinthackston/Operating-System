#include <xinu.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

unsigned int maxStackLocation;
unsigned int minStackLocation;

void genericFunc(unsigned int buf[], int num);

shellcmd xsh_maxstack(int nargs, char *args[]){
  int localVar=args[1];
  void *currLocation=(void*)(&localVar);
  maxStackLocation=*(unsigned int*)(&currLocation);
  
  int buffer[atoi(args[2])];
  int number=atoi(args[3]);
  genericFunc(buffer,number);
  unsigned int space=maxStackLocation-minStackLocation;
  printf("max stack space used %d\n", space);
}

void genericFunc(unsigned int buf[], int num){
  /*
  for(num=0;num<sizeof(buf);num++){
    buf[num]=num*5;
    }*/
  void *currPtrLocation= (void*)(&num);
  unsigned int currLocation=*(unsigned int*)(&currPtrLocation);
  if (currLocation<minStackLocation){
    minStackLocation=currLocation;
  }
  return;
}
