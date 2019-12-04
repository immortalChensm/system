//
// Created by 1655664358@qq.com on 2019/11/13.
//
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <windows.h>
#include <semaphore.h>
#include <time.h>
sem_t sem;
void *talk(void *data)
{
    while (1) {
        //sem_wait(&sem);
        pthread_t tid;
        pid_t pid;
        tid = pthread_self();
        printf("i am %s\n", data);
        printf("pid %d thread %d\n", pid, tid);
        Sleep(1000);
       // sem_post(&sem);
    }
    //pthread_exit((void*)1);
}
void *say(void *data)
{
    while(1) {
        //sem_wait(&sem);
        pthread_t tid;
        pid_t pid;
        tid = pthread_self();
        printf("i am %s\n", data);
        printf("pid %d thread %d\n", pid, tid);
        Sleep(1000);
        //sem_post(&sem);
    }
    //pthread_exit((void*)2);
}
int main()
{
    pthread_t tid1,tid2;

    sem_init(&sem,0,1);
    pthread_create(&tid1,NULL,talk,(void*)"english");
    pthread_create(&tid2,NULL,say,(void*)"chinese");
    void *res1;
    void *res2;
    int ret1 = pthread_join(tid1,&res1);
    int ret2 = pthread_join(tid2,&res2);
    printf("ret1=%d,res1=%d\n",ret1,res1);
    printf("ret2=%d,res2=%d\n",ret2,res2);
    sem_destroy(&sem);
    return 0;

}
