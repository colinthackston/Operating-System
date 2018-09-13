#include <xinu.h>

syscall cond_init(cond_t *cv){
  if(cv==NULL){
    return SYSERR;
  }
  *cv=1;
  return OK;
}
