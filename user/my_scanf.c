#include "my_scanf.h"
#include "user.h"

// void my_scanf(char *buf){
//   int i=0;
//   char curr;
//   do{
//     if(read(0,&curr,1)<0){
//       printf("Error reading file\n");
//     }
//
//   }while(curr);
// }



void my_scanf(char *buf) {
    char c;
    int i = 0;

    while (1) {
        if (read(0, &c, 1) < 1) break;

        // Stop on space, newline, or null character
        if (c == ' ' || c == '\n' || c == '\0') {
            break;
        }

        buf[i] = c;
        i++;
    }

    buf[i] = '\0'; // Null-terminate
}
