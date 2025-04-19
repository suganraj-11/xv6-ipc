#ifndef MSG_PASS_H
#define MSG_PASS_H

// Kernel function declarations
int send(int pid, char* buf);  // Function to send message to a process
int recv(char* msg);           // Function to receive a message from the current process

#endif // MSG_PASS_H
