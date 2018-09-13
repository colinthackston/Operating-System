#ifndef _FUTURE_H_
#define _FUTURE_H_  
#define NFUT 100

typedef enum {
  FUTURE_EMPTY,
  FUTURE_WAITING,
  FUTURE_READY,
  FUTURE_USED
} future_state_t;

typedef enum {
  FUTURE_EXCLUSIVE,
  FUTURE_SHARED,
  FUTURE_QUEUE
} future_mode_t;

typedef struct future_t {
  int value;
  future_state_t state;
  future_mode_t mode;
  pid32 pid;
  qid16 set_queue;
  qid16 get_queue;
} future_t;

//future table
extern future_t futtab[NFUT];

/* Interface for the Futures system calls */
future_t* future_alloc(future_mode_t mode);
syscall future_free(future_t* fut);
syscall future_get(future_t* fut, int* data);
syscall future_set(future_t* fut, int data);

#endif /* _FUTURE_H_ */
