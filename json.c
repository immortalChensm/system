//
// Created by 1655664358@qq.com on 2019/11/30.
//


#include <stdlib.h>
#include <stdio.h>
#include "cJSON.h"

struct talks{
    int data;
    int age;
    char *name;
};

//void talk(char *format,struct talks talking);
//#define talk(format,...) talk((format),(struct talks){__VA_ARGS__})
//https://www.cnblogs.com/do-your-best/p/11007435.html
//gcc inline
//https://www.jianshu.com/p/21aef14340a8
#define FIO_INLINE static inline  __attribute__((unused))

FIO_INLINE int test(void){return 1+2;}
int main()
{
    char text1[]="{\n\"name\": \"Jack (\\\"Bee\\\") Nimble\", \n\"format\": {\"type\":       \"rect\", \n\"width\":      1920, \n\"height\":     1080, \n\"interlace\":  false,\"frame rate\": 24\n}\n}";
    char *out;cJSON *json;

    printf("%d\n",test());

//    json=cJSON_Parse(text1); json解析
//    if (!json) {printf("Error before: [%s]\n",cJSON_GetErrorPtr());}
//    else
//    {
//        out=cJSON_Print(json);
//        cJSON_Delete(json);
//        printf("%s\n",out);
//        free(out);
//    }

//    json = cJSON_Parse(text1);
//    out = cJSON_Print(json);
//    printf("%s\n",out);
//
//    cJSON *arr = cJSON_GetObjectItem(json,"format");
//    cJSON *object = cJSON_GetObjectItem(arr,"width");
//    printf("%d",object->valueint);
//    printf("%s",object->string);

   // printf("************************\n");
    //cJSON *root,*fmt;
//    root=cJSON_CreateObject(); 创建json
//    cJSON_AddItemToObject(root, "name", cJSON_CreateString("Jack (\"Bee\") Nimble"));
//    cJSON_AddItemToObject(root, "format", fmt=cJSON_CreateObject());
//    cJSON_AddStringToObject(fmt,"type",		"rect");
//    cJSON_AddNumberToObject(fmt,"width",		1920);
//    cJSON_AddNumberToObject(fmt,"height",		1080);
//    cJSON_AddFalseToObject (fmt,"interlace");
//    cJSON_AddNumberToObject(fmt,"frame rate",	24);
//    cJSON_AddStringToObject(fmt,"name","lucy");
//
//    out=cJSON_Print(root);
//    cJSON_Delete(root);
//    printf("%s\n",out);
//    free(out);

//    root = cJSON_CreateObject();
//    cJSON_AddStringToObject(root,"name","jack");
//    cJSON_AddNumberToObject(root,"age",100);
//
//    cJSON_AddItemToObject(root,"hobby",fmt=cJSON_CreateObject());
//    cJSON_AddStringToObject(fmt,"key","baskball");
//    cJSON_AddNumberToObject(fmt,"value",100);
//
//    out = cJSON_Print(root);
//    cJSON_Delete(root);
//    printf("%s\n",out);
//    free(out);

//    const char *strings[7]={"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
//    root=cJSON_CreateStringArray(strings,7);创建一维字符串数组
//
//    out=cJSON_Print(root);	cJSON_Delete(root);	printf("%s\n",out);	free(out);

//    char *address[3] = {"上海","北京","贵阳"};
//    root = cJSON_CreateStringArray(address,3);
//    out = cJSON_Print(root);
//    cJSON_Delete(root);
//    printf("%s\n",out);
//    free(out);
//    int numbers[3][3]={{0,-1,0},{1,0,0},{0,0,1}};
//    int i;
//    root=cJSON_CreateArray();创建多维数组
//    for (i=0;i<3;i++) cJSON_AddItemToArray(root,cJSON_CreateIntArray(numbers[i],3));
//
///*	cJSON_ReplaceItemInArray(root,1,cJSON_CreateString("Replacement")); */
//
//    out=cJSON_Print(root);	cJSON_Delete(root);	printf("%s\n",out);	free(out);

//    const char *sex[2] = {"female","male"};
//    root = cJSON_CreateArray();
//    cJSON_AddItemToArray(root,cJSON_CreateStringArray(sex,2));
//    out = cJSON_Print(root);
//    cJSON_Delete(root);
//    printf("%s\n",out);
//    free(out);
//    const char *address[3] = {"shanghai","guiyang","beijing"};
//    root = cJSON_CreateObject();
//    cJSON_AddStringToObject(root,"name","张三");
//    cJSON_AddNumberToObject(root,"age",100);
//    cJSON_AddItemToObject(root,"address",fmt=cJSON_CreateStringArray(address,3));
//    cJSON *city;
//    cJSON_AddItemToObject(root,"city",city=cJSON_CreateObject());
//    cJSON_AddStringToObject(city,"name","japanese");
//    cJSON_AddStringToObject(city,"alias","reben");
//    cJSON *articles;
//    cJSON_AddItemToObject(root,"articles",articles=cJSON_CreateArray());
//    cJSON *article;
//    cJSON_AddItemToArray(articles,article=cJSON_CreateObject());
//    cJSON_AddStringToObject(article,"title","how to speak japanese");
//    cJSON_AddStringToObject(article,"authour","jack");
//
//    cJSON_AddItemToArray(articles,article=cJSON_CreateObject());
//    cJSON_AddStringToObject(article,"title","is it ok?");
//    cJSON_AddStringToObject(article,"authour","tom");
//
//    out = cJSON_Print(root);
//    cJSON_Delete(root);
//    printf("%s\n",out);
//    free(out);
//
//
//    typedef struct st_mysql_res {
//        my_ulonglong row_count;
//        MYSQL_FIELD *fields;
//        MYSQL_DATA *data;
//        MYSQL_ROWS *data_cursor;
//        unsigned long *lengths; /* column lengths of current row */
//        MYSQL *handle; /* for unbuffered reads */
//        const struct st_mysql_methods *methods;
//        MYSQL_ROW row; /* If unbuffered read */
//        MYSQL_ROW current_row; /* buffer to current row */
//        MEM_ROOT field_alloc;
//        unsigned int field_count, current_field;
//        my_bool eof; /* Used by mysql_fetch_row */ /* mysql_stmt_close() had to cancel this result */
//        my_bool unbuffered_fetch_cancelled;
//        void *extension; }
//        MYSQL_RES;

    //char *data = "▒▒a▒▒0▒'M▒▒):▒▒NQ▒";
    //printf("%b\n",data);
//    int a = 1;//0000 0001 左移 0000 0010 2 0100
//    printf("%d\n",a<<1);
//    printf("%d\n",a<<2);
//    printf("%d\n",a>>1);//0000 0000
//
//    int b = -3;//0011 1100 1101 d
//    printf("%x\n",-3);
//
//    int c = 0b00011001;// 00000000 00000000 00000000 00011001
//    printf("=%x\n",c);
//    printf("=%x\n",c<<3);//1100 1000
//    printf("=%x\n",c<<4);//0000 00000000 00000000 0001 1001 0000
//
//
//    int d = 0b01111111;
//    printf("d=%x\n",-20);//1110 1100 补码 ec
//                        //1110  1011 减1 eb
//                        //0001  0100 原码 14 20
//
//    printf("d=%#X\n",-17);//1110 ffff
//                         //1110 1110
//                         //0001 0001

//    unsigned char *data = "1001000011001010";
//
//    printf("%s\n",data);
//
//    int type = data[0]&0x0F;//0000 1111
//    printf("%x\n",type);
    //debug("%s=%d\n",.con="hi",.d=100);
    //talk("%d-%s\n",.age=100,.name="hi");

    return 0;
}
//
//void talk(char *format,struct talks talking)
//{
//    printf(format,talking.age,talking.name);
//}