/*
Author- Colin Thackston
Created on- 9/7/2016 15:14
Last modified by- Colin Thackston
Last modified on- same
Part of- P436 assignment 1
 */

#include <xinu.h>
#include <string.h>
#include <stdio.h>

shellcmd xsh_hello(int nargs, char *args[]) {

  int32 retval; //return value
  
  if (nargs == 2){
    printf("Hello %s! Welcome to the wonderful world of Xinu!!!!!\n", args[1]);
  }

  if (nargs < 2) {
    printf("Sorry please enter the correct number of arguments\n");
  }

  if (nargs > 2){
    printf("Sorry please only enter 2 arguments\n");
  }


}
