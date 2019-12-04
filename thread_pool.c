//
// Created by 1655664358@qq.com on 2019/11/13.
//
//https://blog.csdn.net/stayneckwind2/article/details/54897619
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <windows.h>
#include <errno.h>

#define MAX_THREAD_NUM 16
#define MAX_TASKITEM 1024
#define FAILURE 0
#define SUCCESS 1
typedef struct Queue
{
    void (*callback)(void *arg);
    struct Queue *next;
}Queue;

Queue *front,*rear;
void freeQueue(Queue *queue);
Queue *initQueue(Queue **front,Queue **rear);
void enQueue(Queue **rear,void (*callback)(void *arg));
void deQueue(Queue **front,Queue *rear,void (**callback)(void *arg));
static void *__worker(void *args);


typedef unsigned int u8;
typedef unsigned long int u16;
typedef struct tpool
{
    u8 enable;
    Queue *front;
    Queue *rear;
    pthread_attr_t attr;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    pthread_t tids[MAX_THREAD_NUM];
    u16 num;
}tpool_t;
static int __worker_route(tpool_t *phead);
static int tpool_routine_add(tpool_t *phead,void (*callback)(void *),void *arg);
static int tpool_destroy(tpool_t *phead);
struct routine
{
    void *arg;
    void (*callback)(void*);
};

tpool_t *tpoll_alloc(u16 num)
{
    int ret = FAILURE;
    int ix = 0;
    tpool_t *phead = NULL;
    if (num==0||num>MAX_THREAD_NUM){
        goto _E1;
    }

    phead = calloc(1, sizeof(tpool_t));
    if (!phead){
        goto _E1;
    }
    phead->enable = 1;
    phead->num = num;
    initQueue(&front,&rear);
    phead->rear = rear;
    phead->front = front;
    if (!phead->rear){
        goto _E3;
    }

    ret = pthread_attr_init(&(phead->attr));
    ret|=pthread_mutex_init(&(phead->mutex),NULL);
    ret|=pthread_cond_init(&(phead->cond),NULL);
    if (ret<0){
        goto _E3;
    }
    //设置线程为分离线程  线程结束时自动释放占用的资源
    ret = pthread_attr_setdetachstate(&(phead->attr),PTHREAD_CREATE_DETACHED);
    if (ret<0){
        goto _E4;
    }
    for (int ix = 0; ix <num ; ++ix) {
        ret = pthread_create(&(phead->tids[ix]),&(phead->attr),__worker,phead);
        printf("create thread\n");
        if (ret<0){
            goto _E4;
        }
    }
    ret = SUCCESS;
    goto _E1;
    _E4:
    pthread_mutex_destroy(phead->mutex);
    pthread_cond_destroy(phead->cond);
    pthread_attr_destroy(&(phead->attr));
    _E3:
    freeQueue(phead->front);

    _E2:
    free(phead);

    _E1:
    return phead;
}
static int __worker_route(tpool_t *phead)
{
    //struct routine *ptr = NULL;
    void (*callback)(void *arg);
    pthread_mutex_lock(&(phead->mutex));
    if (phead->front->next==NULL){
        pthread_cond_wait(&(phead->cond),&(phead->mutex));
        printf("thread %d wakeup!\n",pthread_self());
    }
    deQueue(&(phead->front),phead->rear,&callback);
    pthread_mutex_unlock(&(phead->mutex));
    if (callback!=NULL){
        callback("ok");
        return SUCCESS;
    }
    return FAILURE;

}
static void *__worker(void *args)
{
    tpool_t *phead = (tpool_t*)args;
    if (!args){
        return NULL;
    }
    while (phead->enable){
        if (SUCCESS!=__worker_route(phead)){
            printf("__worker_route return thread quit\n");
            break;
        }
    }
    //return NULL;
    printf("%d thread exit\n",pthread_self());
    pthread_exit((void*)0);
}

static int tpool_routine_add(tpool_t *phead,void (*callback)(void *),void *arg)
{
    if (!phead||!callback||!arg){
        return FAILURE;
    }
    pthread_mutex_lock(&(phead->mutex));
    printf("main thread add callback function\n");
    enQueue(&(phead->rear),callback);
    pthread_cond_signal(&(phead->cond));
    pthread_mutex_unlock(&(phead->mutex));
    return SUCCESS;
}

static int tpool_destroy(tpool_t *phead)
{
    int ix = 0;
    if (!phead){
        return FAILURE;
    }
    phead->enable = 0;
    pthread_mutex_lock(&(phead->mutex));
    pthread_cond_broadcast(&(phead->cond));
    pthread_mutex_unlock(&(phead->mutex));
    for (int ix = 0; ix <phead->num ; ++ix) {
        pthread_join((phead->tids[ix]),NULL);
        printf("release %d thread\n",phead->tids[ix]);
    }
    pthread_mutex_destroy(&(phead->mutex));
    pthread_cond_destroy(&(phead->cond));
    pthread_attr_destroy(&(phead->attr));
    return SUCCESS;
}

void freeQueue(Queue *queue)
{
    Queue *temp;
    while (queue->next){
        temp = queue->next;
        queue->next = temp->next;
        free(temp);
    }
}
Queue *initQueue(Queue **front,Queue **rear)
{
    Queue *head = (Queue*)malloc(sizeof(Queue));
    head->next = NULL;
    head->callback = NULL;
    (*front) = (*rear) = head;
}

void enQueue(Queue **rear,void (*callback)(void *arg))
{
    Queue *node = (Queue*)malloc(sizeof(Queue));
    node->next = NULL;
    node->callback = callback;
    (*rear)->next = node;
    (*rear) = (*rear)->next;
}
void deQueue(Queue **front,Queue *rear,void (**callback)(void *arg))
{
    if ((*front)->next==NULL){
        printf("empty queue\n");
        (*callback) = NULL;
        return ;
    }
    Queue *temp = (*front)->next;
    (*callback) = temp->callback;
    (*front)->next = temp->next;
    if (temp==rear){
        (*front) = rear;
    }
    free(temp);
}
void say(void *arg)
{
    printf("hello,world %s\n",arg);
}
void talk(void *arg)
{
    printf("hello,china %s\n",arg);
}
int main()
{

    tpool_t *phead;

    //创建分离线程池
    //线程池里的线程在运行时，队链没有数据就会阻塞，让主线程运行，主线程运行添加数据后，叫醒线程池里的某线程运行，其它线程也会阻塞
    //采取线程互斥锁实现线程同步访问队链
    phead = tpoll_alloc(10);
    Sleep(2000);

    printf("1\n");
    //主线程对队链添加任务
    tpool_routine_add(phead,say,"test1");

    printf("2\n");
   tpool_routine_add(phead,talk,"test1");

    //Sleep(2000);

    //释放分离线程池
    int ret = tpool_destroy(phead);
    printf("ret=%d\n",ret);

//    front=rear=initQueue();
//    enQueue(&rear,say);
//    enQueue(&rear,talk);
//
//    void (*callback)(void *arg);
//    deQueue(&front,rear,&callback);
//
//    callback("hello");
//
//    deQueue(&front,rear,&callback);
//    callback("hello");
//
//    deQueue(&front,rear,&callback);
//    if (callback==NULL){
//        printf("pop cbk is empty\n");
//    }
//
//    enQueue(&rear,talk);
//    deQueue(&front,rear,&callback);
//    if (callback==NULL){
//        printf("pop cbk is empty\n");
//    }else{
//        callback("666");
//    }
    return 0;
}