#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "msg_pass.h"

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  if(n < 0)
    n = 0;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}



uint64
sys_send(void) {
  int pid;
  char msg[100];

  argint(0, &pid);
  if(argstr(1, msg, sizeof(msg)) < 0)
    return -1;

  return send(pid, msg);
}
// sys_send function
// int
// sys_send(void) {
//   int pid;
//   char *msg;
//
//   // Fetch the arguments passed from user space
//   if(argint(0, &pid) < 0) {
//     return -1;  // Error fetching the process ID
//   }
//   if(argstr(1,msg,100) < 0) {
//     return -1;  // Error fetching the message string
//   }
//
//   // Call the send function to send the message
//   return send(pid,msg);
// }

// sys_recv function
uint64
sys_recv(void) {
  char msg[100];
  
  // Fetch the argument (message buffer)
  if(argstr(0, msg, sizeof(msg)) < 0) {
    return -1;  // Error fetching the message buffer
  }
  
  // Call the recv function to receive the message
  return recv(msg);
}
