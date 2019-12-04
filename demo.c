//
// Created by 1655664358@qq.com on 2019/11/16.
//

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

//调用了普通求 next 的方式，这里并未直接对 next[1] 赋值为 1，但通过函数第一次运行，也可以得出它的值为 1
void Next(char*T,int *next){
    int i=1;
    next[1]=0;
    int j=0;
    while (i<strlen(T)) {
        if (j==0||T[i-1]==T[j-1]) {
            i++;
            j++;
            next[i]=j;
        }else{
            j=next[j];
        }
    }
}
int KMP(char * S,char * T){
    int next[10];
    Next(T,next);//根据模式串T,初始化next数组
    int i=1;
    int j=1;
    while (i<=strlen(S)&&j<=strlen(T)) {
        //j==0:代表模式串的第一个字符就和当前测试的字符不相等；S[i-1]==T[j-1],如果对应位置字符相等，两种情况下，指向当前测试的两个指针下标i和j都向后移
        if (j==0 || S[i-1]==T[j-1]) {
            i++;
            j++;
        }
        else{
            j=next[j];//如果测试的两个字符不相等，i不动，j变为当前测试字符串的next值
        }
    }
    if (j>strlen(T)) {//如果条件为真，说明匹配成功
        return i-(int)strlen(T);
    }
    return -1;
}
char *substring(char *dst,char *src,int start,int len)
{
    char *p=dst;
    char *q=src;
    int length=strlen(src);
    if(start>=length||start<0)
        return NULL;
    if(len>length)
        len=length-start;
    q+=start;
    while(len--)
    {
        *(p++)=*(q++);
    }
    *(p++)='\0';
    return dst;
}
char *right(char *dst,char *src,int n)
{
    char *p=src;
    char *q=dst;
    int len=strlen(src);
    if(n>len) n=len;
    p+=(len-n);
    while(*(q++)=*(p++));
    return dst;
}

int main()
{
//    FILE *fp = fopen("demo1.txt","w+");
//    if (!fp){
//        printf("%s\n",strerror(errno));
//    }
//    int a = 100;
//
//    fprintf(fp,"%d",a);
//    int b;
//
//    FILE *fps = fopen("demo1.txt","r");
//    fseek(fps,0,SEEK_SET);
//    fscanf(fps,"%d",&b);
//    printf("b=%d\n",b);
//
//    fclose(fps);

//
//    form_split=
//    ----------------------------330099373899964802175039
//    Content-Disposition: form-data; name=
//
//    request_body=
//    ----------------------------330099373899964802175039
//    Content-Disposition: form-data; name="address"
//
//    mimi55
//    ----------------------------330099373899964802175039
//    Content-Disposition: form-data; name="city"
//
//    doyun55
//    ----------------------------330099373899964802175039
//    Content-Disposition: form-data; name="state"
//
//
//    ----------------------------330099373899964802175039--





//    char *a = "hahaba\n\r\nfsdfsdafsdfsdf\r\n\n346346";
//
//    char *b = strtok(a,"\n\r\n");

    //char *a = "china-and-japanese";
   // char *b = a;

   // char *c = strstr(a,"-");
    //printf("a=%s\n",a);
//    printf("b=%s\n",b);

//    int b;
//    char *c = "1234";
//    b = atoi(c);
//    printf("b=%d\n",b);

//    void *b = strstr("china-japanese","content");
//    printf("%s\n",b);

//    int i = KMP("china","na");
//    printf("%d\n",i);

//    int fd = open("e:/c/system/666.jpg",O_RDONLY);
//    printf("fd=%d,error=%s\n",fd,strerror(errno));
//    char con[1024];
//    int len;
//    while((len = read(fd,con, 1024))>0){
//        printf("--%s\n",con);
//        memset(con,0, sizeof(con));
//    }
//    close(fd);

//    char *a = "name=jack&age=100";
//    char c[strlen(a)+1];
//    strcpy(c,a);
//
//    char *b = NULL;
//    b = strtok(c,"&");
//    printf("%s\n",b);
//    b = strtok(NULL,"&");
//    printf("%s\n",b);
//
//    b = strtok(NULL,"&");
//    printf("%s\n",b);


    char *a = "name23523532523";

    printf("%d\n", sizeof(a));
    return 0;
}