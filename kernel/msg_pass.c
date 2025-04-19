#include "msg_pass.h"
#include "types.h"
#include <string.h>

int send(char *msg,int pid){
  if(strlen(msg)>100){
    return -1;
  }

  return 0;
}
