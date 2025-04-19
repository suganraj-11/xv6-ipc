#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "spinlock.h"
#include "proc.h"
#include "defs.h"



int
send(const char *msg,int pid){
  if(strlen(msg)>100){
    return -1;
  }

  return 0;
}
