//
// Created by 1655664358@qq.com on 2019/12/5.
//

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>
struct demo1
{
    int data;//4个字节
    char *name;//8个字节  内存对齐的话为16个字节
};

//gcc 属性  表示  不进行对齐
//http://blog.chinaunix.net/uid-25768133-id-3485479.html
typedef enum __attribute__((packed)) {
    FIOBJ_T_NUMBER = 0x01,
    FIOBJ_T_NULL = 0x06,
    FIOBJ_T_TRUE = 0x16,
    FIOBJ_T_FALSE = 0x26,
    FIOBJ_T_FLOAT,
    FIOBJ_T_STRING,
    FIOBJ_T_ARRAY,
    FIOBJ_T_HASH,
    FIOBJ_T_DATA,
    FIOBJ_T_UNKNOWN
} fiobj_type_enum;

void randStr()
{
    char string[16];
    unsigned char temp;
    int i;
    srand((int)time(0));
    for(i=0;i<16;i++){
        temp = (unsigned char)(rand()%256);
        string[i] = temp;
        if (temp==0){
            temp = 128;
        }
        printf("%c,%d,rand=%d\n",temp,temp,rand());
    }
    printf("%s,%d\n",string,strlen(string));
}

void str()
{
    int i=0;
    for(i;i<=65525;i++){
        printf("%c=%d\n",i,i);
    }
}
//https://blog.csdn.net/u010076999/article/details/50787399
#pragma weak fm_calloc
void *fm_calloc(size_t size)
{
    void *m = malloc(size);
    return m;
}
struct demo1 demo1()
{
//    struct demo1 *demo11 = (void*)malloc(sizeof(*demo11));
    struct demo1 *demo11 = fm_calloc(sizeof(*demo11));
    *demo11 = (struct demo1){
        .data=1,
        .name = "lucy"
    };

    printf("memory =%X\n",demo11);
    printf("memory and 2=%X\n",(uintptr_t)demo11|2);//0001 0010 0011 0100 0101 0110 0111

    //6F1400   原本
    //6F14 0000 0000
    //0000 0000 0010 与2相或
    //6F14 0    2 结果
    uintptr_t p = (uintptr_t)demo11|2;
    printf("or=%d\n",p);
    printf("and=%d\n",p&1);
    //6F14 0    2
    //0000 F    8
    //6F14 0000 0010
    //FFFF 1111 1000
    //6F14 0000 0000
    uintptr_t demo12 = p&~7;//0000 0111 1111 1000
    printf("%X\n",demo12);

    struct demo1 *demo13 = (struct demo1*)demo12;
    printf("unitp to struct %s\n",demo13->name);
//    return (struct demo1){.data=1,.name="china"};
}

int AveInt(int v,...) {
    int ReturnValue = 0;
    int i = v;
    printf("i=%d\n",i);
    va_list ap;
    va_start(ap, v);
    i+=1;
    while (i > 0) {
        printf("va_arg=%d\n",va_arg(ap, int));
        //ReturnValue += va_arg(ap, int);
        //printf("returnValue=%d\n",ReturnValue);
        i--;
    }
    va_end(ap);
    return ReturnValue /= v;
}

int main() {


    //demo1();
    int b = AveInt(2,3,4,5);
    printf("b=%d\n",b);
   // randStr();
   //str();
   //fiobj_str.h line=133 FIOBJ fiobj_str_new(const char *str, size_t len) 函数的示例源码分析
   /**
    *
    typedef struct {
        fiobj_object_header_s head;
        uint64_t hash;
        fio_str_s str;
    } fiobj_str_s;
    */
//   struct demo1 *demo11 = malloc(sizeof(*demo11));
//
//   *demo11 = (struct demo1){
//       .data=1,
//       .name = "hello"
//   };
//
//   printf("data=%d,name=%s\n",demo11->data,demo11->name);
//    printf("%d\n",FIO_STR_INIT);

//    struct demo1 a = demo1();
//    printf("a=%d\n",a.data);
//    printf("a=%s\n",a.name);
//
//
//    printf("%X\n",(uintptr_t)7);//0000 0111
//    printf("%d\n",(uintptr_t)7);
//
//    printf("%X\n",~(uintptr_t)7);//0000 0111
//    printf("%d\n",~(uintptr_t)7);//1111 1000 F8
//
//    printf("%d\n",1&&(2&3));//0010 & 0011 = 0010 && 1
//
//    fiobj_type_enum num;
//    num = 8;
//    printf("%X\n",(void*)&FIOBJ_T_FLOAT);

//    struct demo1 *demo11 = (struct demo1*)malloc(sizeof(struct demo1));
//    demo11->data = 1;
//    demo11->name = "ok";
//    printf("%d\n",demo11->data);
//
//    uintptr_t b = (uintptr_t)demo11;
//
//    printf("b=%d\n",b);
//    printf("b=%d\n",b|6);//0001 0010 0011 0100 0101 0110 0111 [1-7] [1-6]
//
//    printf("b=%d",(b|2)&~7);

    //struct demo1 demo11 = (struct demo1){.name="hello",.data=100};
    //printf("%s,%d\n",demo11.name,demo11.data);

//    int d = sizeof(struct demo1)-(size_t)((&((struct demo1*)0)->data)+1);
//
//    printf("%d\n",d);
//    printf("%d\n",sizeof(struct demo1));
//    printf("%d\n", sizeof(int));
//    printf("%d\n", sizeof(char));
//    char *k;
//    printf("%d\n", (size_t)((&((struct demo1*)0)->data)));
//    printf("%d\n", sizeof(struct demo1)-(size_t)((&((struct demo1*)0)->data)+1));
//
//    uint8_t o;
    return 0;
}
