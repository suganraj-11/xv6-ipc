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
      p->from_pid = myproc()->pid; //set the sender's pid to the from_pid of the receiving process
      p->msg_full = 1;  // Mark the message as being available

      release(&p->lock);  // Release the lock
      return 0;  // Success
    }
  }
  return -1;  // Process not found
}




int recv(char* msg) {
  struct proc *p = myproc();  // Get the current process

  acquire(&p->lock);  // Acquire lock for the current process

  if(p->msg_full == 0) {  // Check if there is no message
    release(&p->lock);  // Release the lock before returning
    return -1;  // No message available
  }

  // Copy the message from the buffer to the provided msg pointer
  safestrcpy(msg, p->msgbuf, sizeof(p->msgbuf));

  // Return the from_pid (the sender's PID)
  int sender_pid = p->from_pid;

  // Clear the message and reset flags
  p->msg_full = 0;  // Mark the message buffer as empty
  p->from_pid = 0;  // Clear the sender's PID
  p->msgbuf[0] = '\0';  // Clear the message buffer

  release(&p->lock);  // Release the lock after the operation

  return sender_pid;  // Return the PID of the sender
}
