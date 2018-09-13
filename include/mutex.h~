/*
-definition of data types for mutex and condition variable
 */

#include <xinu.h>

syscall mutex_lock(mutex_t *lock);
syscall mutex_unlock(mutex_t *lock);
syscall cond_wait(cond_t *cv, mutex_t lock);
syscall cond_signal(cond_t *cv);
syscall cond_init(cond_t *cv);
syscall mutex_create(mutex_t *lock);
