#include<stdio.h>
#include<sys/types.h>
int main(int argc,char *argv[])
{
printf("before execv\n");
execv("/bin/ls",argv);
printf("after execv\n");
} 
