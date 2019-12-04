//
// Created by 1655664358@qq.com on 2019/10/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

struct msgbuf
{
    long type;
    char data;
    long text;
} msgbuf;
int main(void)
{

    struct stat buf;

    int ret = stat("e:/c/system/main.c",&buf);
    if (ret<0){
        fprintf(stderr,"error %s\n",strerror(errno));
    }
    printf("st_size=%d\n",buf.st_size);
    printf("st_dev=%d\n",buf.st_dev);
    printf("st_ino=%d\n",buf.st_ino);
    printf("st_nlink=%d\n",buf.st_nlink);
    printf("st_mode=%o\n",buf.st_mode);
    printf("%o\n",S_ISREG(buf.st_mode));
    printf("%o\n",S_IRUSR&buf.st_mode);

    struct test{
        int a;
        short int b;

    }test;

    printf("size=%d\n", sizeof(test));

    printf("msg=%d\n", sizeof(struct msgbuf));
    printf("msg1=%d\n", sizeof(long int));

    return 0;
}