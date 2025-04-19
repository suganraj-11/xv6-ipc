#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "spinlock.h"
#include "proc.h"
#include "defs.h"



int send(int pid, const char *msg) {
  struct proc *p;
  
  // Check if the message length is greater than the buffer size (100 characters)
  if(strlen(msg) >= 100) {
    return -1;  // Message is too large, return an error
  }

  // Find the process with the given PID
  for(p = proc; p < &proc[NPROC]; p++) {
    if(p->pid == pid) {
      acquire(&p->lock);  // Acquire lock for the target process

      if(p->msg_full) {
        release(&p->lock);  // Release the lock if there's already a message
        return -1;  // Message queue is full
      }

      // Copy message into the target process's message buffer
      safestrcpy(p->msgbuf, msg, sizeof(p->msgbuf));
      p->msg_full = 1;  // Mark the message as being available

      release(&p->lock);  // Release the lock
      return 0;  // Success
    }
  }
  return -1;  // Process not found
}
