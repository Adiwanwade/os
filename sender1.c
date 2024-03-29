// File: sender1.c
#include "mesg.h"
#include <fcntl.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
mesg msg;
int main()
{
    int mq_id;
    int n;
    if ((mq_id = msgget(MKEY1, PERMS | IPC_CREAT)) < 0)
    {
        printf("Sender: Error creating message");
        exit(1);
    }
    msg.mtype = 1111L;
    n = read(0, msg.mdata, 50);
    msg.mdata[n] = '\0';
    msgsnd(mq_id, &msg, 50, 0);
}
