#include "mesg.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
mesg msg;
int main()
{
    int mq_id;
    int n;
    if ((mq_id = msgget(MKEY1, PERMS | IPC_CREAT)) < 0)
    {
        printf("receiver: Error opening message");
        exit(1);
    }
    msgrcv(mq_id, &msg, 50, 1111L, 0);
    write(1, msg.mdata, 50);
    msgctl(mq_id, IPC_RMID, NULL);
}
