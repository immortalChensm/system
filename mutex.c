//
// Created by 1655664358@qq.com on 2019/9/20.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <windows.h>
#define FALSE 0
#define TRUE 1

void readfun();
void writefun();

char buffer[256];
int buffer_has_item = 0;
int retflag = FALSE;

pthread_mutex_t mutex;

int main(void)
{
    pthread_t reader,writer;

    pthread_mutex_init(&mutex,NULL);


    pthread_create(&writer,NULL,(void*)&writefun,NULL);
    pthread_create(&reader,NULL,(void*)&readfun,NULL);
    //pthread_create(&writer,NULL,(void*)&writefun,NULL);
   // writefun();
    //Sleep(10);
    void *ret1;
    void *ret2;

    pthread_join(reader,&ret1);
    pthread_join(writer,&ret2);

    pthread_mutex_destroy(&mutex);

    printf("12/4=%d\n",12%4);
    return 0;
}

void readfun(void)
{
//    while(1){
//        if(retflag){
//            return ;
//        }
//        pthread_mutex_lock(&mutex);
//        if(buffer_has_item=1){
//            printf("%s",buffer);
//            buffer_has_item =0;
//        }
//        pthread_mutex_unlock(&mutex);
//    }
//    return ;
    int i=0;
    while (i<=10){
        //pthread_mutex_lock(&mutex);
        printf("read fun i=%d\n",i++);
        //pthread_mutex_unlock(&mutex);
    }
}

void writefun(void)
{
    int i=0;
//    while(1){
//        if(i==10){
//            retflag = TRUE;
//            return ;
//        }
//        pthread_mutex_lock(&mutex);
//        if(buffer_has_item=0){
//            sprintf(buffer,"this is %d\n",i++);
//            buffer_has_item=1;
//        }
//        pthread_mutex_unlock(&mutex);
//    }
    while (i<=10){
        //pthread_mutex_lock(&mutex);
        printf("write fun i=%d\n",i++);
        //pthread_mutex_unlock(&mutex);
    }
    return ;
}
