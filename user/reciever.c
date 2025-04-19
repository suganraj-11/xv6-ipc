#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "user.h"
#include "my_scanf.h"
// void my_scanf(char *buf) {
//   int i = 0;
//   char c;
//   while (read(0, &c, 1) == 1 && c != ' ' && c != '\n' && c != '\0') {
//     buf[i++] = c;
//   }
//   buf[i] = 0;
// }

int
main() {
  char buf[128];

  int pid = getpid();
  printf("Receiver running, my pid is %d\n", pid);

  while (1) {
    printf("Enter 1 to check for messages: ");
    my_scanf(buf);
    if (buf[0] == '1') {
      char msg[100];
      int status = recv(msg);
      if (status == 0) {
        printf("Received message: %s\n", msg);
      } else {
        printf("No message received\n");
      }
    }
  }

  exit(0);
}
