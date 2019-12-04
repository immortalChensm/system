#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <windows.h>
int key=5;
void *msg(void *arg)
{
    printf("%s\n",arg);
}

void *number1(void *arg)
{
    pthread_t tid;
    pid_t pid;
    pid = getpid();
    tid = pthread_self();

    key++;

    printf("thread 1 pid=%d,tid=%d,key=%d\n",pid,tid,key);
    pthread_exit((void*)1);

}
void *number2(void *arg)
{
    pthread_t tid;
    pid_t pid;
    pid = getpid();
    tid = pthread_self();

    key++;
    printf("thread 2 pid=%d,tid=%d,key=%d\n",pid,tid,key);
    pthread_exit((void*)1);

}
void *number3(void *arg)
{
    pthread_t tid;
    pid_t pid;
    pid = getpid();
    tid = pthread_self();

    key++;
    printf("thread 3 pid=%d,tid=%d,key=%d\n",pid,tid,key);
    pthread_exit((void*)1);

}
int main()
{
    pthread_t thread1,thread2,thread3;

//    pthread_create(&thread1,NULL,(void*)msg,(void*)"hello,world");
//    void *retval;
//    pthread_join(thread1,&retval);

    pthread_create(&thread1,NULL,(void*)number1,(void*)"number1");
    pthread_create(&thread2,NULL,(void*)number2,(void*)"number2");
    pthread_create(&thread3,NULL,(void*)number3,(void*)"number3");

    void *retval1;
    void *retval2;
    void *retval3;

    //pthread_join(thread1,&retval1);
    //pthread_join(thread2,&retval2);
    //pthread_join(thread3,&retval3);

    //printf("thread1=%d\n",(int*)retval1);
    //printf("thread2=%d\n",(int*)retval2);
    //printf("thread3=%d\n",(int*)retval3);

    Sleep(2);
    return 0;
}