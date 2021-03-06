#include <xinu.h>

syscall mutex_lock(mutex_t *lock) {
  if (lock == NULL) {
    return SYSERR;
  }
  while(test_and_set(lock));
  return OK;
}
