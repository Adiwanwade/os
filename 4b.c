#include <sys/ipc.h>
#include <stdio.h>
#include <string.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <unistd.h>
struct
{
    long mtype;
    char mtext[20];
} send, recv;
int main()
{
    int qid, pid, len;
    qid = msgget((key_t)0X2000, IPC_CREAT | 0666);
    if (qid == -1)
    {
        perror("\n message failed");
        exit(1);
    }
    send.mtype = 1;
    strcpy(send.mtext, "\n hello i am parent");
    len = strlen(send.mtext);
    pid = fork();
    if (pid > 0)
    {
        if (msgsnd(qid, &send, len, 0) == -1)
        {
            perror("\n message sending failed");
            exit(1);
        }
        printf("\n message has been posted");
        sleep(2);
        if (msgrcv(qid, &recv, 100, 2, 0) == -1)
        {
            perror("\n msgrcv error:");
            exit(1);
        }
        printf("\n message received from child - %s\n", recv.mtext);
    }
    else
    {
        send.mtype = 2;
        strcpy(send.mtext, "\n hi i am child");
        len = strlen(send.mtext);
        if (msgrcv(qid, &recv, 100, 1, 0) == -1)
        {
            perror("\n child message received failed");
            exit(1);
        }
        if (msgsnd(qid, &send, len, 0) == -1)
        {
            perror("\n child message send failed");
        }
        printf("\n received from parent - %s", recv.mtext);
    }
}