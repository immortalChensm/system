//
// Created by 1655664358@qq.com on 2019/11/14.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main()
{

//    char *uri = "GET /index.html HTTP/1.1";
//    printf("uri=%s\n",uri);
//
//    int method = 5;
//    int url = 256;
//    int i=0;
//
//    char methods[20];
//    char urls[256];
//    while (i<method&&!isspace(*uri)){
//        methods[i++] = *uri++;
//       // putchar(*uri++);
//    }
//    methods[i] = '\0';
//    printf("method=%s\n",methods);
//
//    while (isspace(*uri))*uri++;
//    i = 0;
//    while (i<url&&!isspace(*uri)){
//        urls[i++] = *uri++;
//    }
//    urls[i] = '\0';
//    printf("%s\n",urls);

    char *content = "POST / HTTP/1.1\n"
                    "User-Agent: test\n"
                    "Content-Type: multipart/form-data; boundary=--------------------------844099519182533031360164\n"
                    "Accept: */*\n"
                    "Cache-Control: no-cache\n"
                    "Postman-Token: e9667bee-3a4f-4a41-b468-ce3fc0ca3638\n"
                    "Host: 143.536.122.532\n"
                    "Accept-Encoding: gzip, deflate\n"
                    "Content-Length: 163\n"
                    "Connection: keep-alive\n"
                    "\n"
                    "----------------------------844099519182533031360164\n"
                    "Content-Disposition: form-data; name='name'\n"
                    "\n"
                    "lucy\n"
                    "----------------------------844099519182533031360164--\n"
                    "\n"
                    "";

    //printf("%s\n",content);

    char str[80] = "This is - www.runoob.com - website";
    const char s[3] = "-";
    char *token;

    /* 获取第一个子字符串 */
    token = strtok(str, s);

    /* 继续获取其他的子字符串 */
    while( token != NULL ) {
        printf( "%s\n", token );

        token = strtok(NULL, s);
    }

    return 0;
}