#include <xinu.h>

syscall cond_wait(cond_t *cv, mutex_t lock) {
  if(cv==NULL){
    return SYSERR;
  }
  mutex_unlock(lock);
  while(test_and_set(cv)); //puts thread to sleep
  //  sleepms(1);
  mutex_lock(lock);
  return OK;
}

