#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "user.h"
#include "my_scanf.h"

int
main() {
  char buf[100];

  printf("Enter receiver PID: ");
  my_scanf(buf);
  int pid = atoi(buf);

  printf("Enter message: ");
  my_scanf(buf);

  int status = send(pid, buf);
  if (status == 0) {
    printf("Message sent to pid %d\n", pid);
  } else {
    printf("Failed to send message\n");
  }

  exit(0);
}
