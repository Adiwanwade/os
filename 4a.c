#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define msgsize 30
int main()
{
    int ser[2], cli[2], pid;
    char inbuff[msgsize];
    char *msg = "Thank you";
    system("clear"); // Clear the screen
    // Create pipes
    pipe(ser);
    pipe(cli);
    printf("\n server read id = %d, write id = %d", ser[0], ser[1]);
    printf("\n client read id = %d, write id = %d", cli[0], cli[1]);
    pid = fork(); // Fork a child process
    if (pid == 0) // Child process
    {
        printf("\n I am in the child process!");
        close(cli[0]); // Close unused read end of client pipe
        close(ser[1]); // Close unused write end of server pipe
        // Write message to client pipe
        write(cli[1], msg, strlen(msg) + 1); // Include the null terminator
        printf("\n Message written to pipe...");
        sleep(2); // Wait for a moment
        // Read echo message from server pipe
        read(ser[0], inbuff, msgsize);
        printf("\n Echo message received from server:");
        printf("\n %s", inbuff);
    }
    else // Parent process
    {
        close(cli[1]); // Close unused write end of client pipe
        close(ser[0]); // Close unused read end of server pipe
        printf("\n Parent process");
        // Read message from client pipe
        read(cli[0], inbuff, msgsize);
        // Write the same message back to server pipe
        write(ser[1], inbuff, msgsize);
        printf("\n Parent ended!");
    }
    return 0;
}