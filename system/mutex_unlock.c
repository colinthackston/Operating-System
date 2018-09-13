#include <xinu.h>


syscall mutex_unlock(mutex_t *lock) {
  if (lock==NULL){
    return SYSERR;
  }
  *lock = 0;
  return OK;
}
