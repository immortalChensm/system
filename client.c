//
// Created by 1655664358@qq.com on 2019/11/29.
//

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <WinSock2.h>


#pragma comment(lib, "ws2_32.lib")  //加载 ws2_32.dll

#define NON_NUM '0'

int hex2num(char c)
{
    if (c>='0' && c<='9') return c - '0';
    if (c>='a' && c<='z') return c - 'a' + 10;//这里+10的原因是:比如16进制的a值为10
    if (c>='A' && c<='Z') return c - 'A' + 10;

    printf("unexpected char: %c", c);
    return NON_NUM;
}



/**
 * @brief URLDecode 对字符串URL解码,编码的逆过程
 *
 * @param str 原字符串
 * @param strSize 原字符串大小（不包括最后的\0）
 * @param result 结果字符串缓存区
 * @param resultSize 结果地址的缓冲区大小(包括最后的\0)
 *
 * @return: >0 result 里实际有效的字符串长度
 *            0 解码失败
 */
int URLDecode(const char* str, const int strSize, char* result, const int resultSize)
{
    char ch,ch1,ch2;
    int i;
    int j = 0;//record result index

    if ((str==NULL) || (result==NULL) || (strSize<=0) || (resultSize<=0)) {
        return 0;
    }

    for ( i=0; (i<strSize) && (j<resultSize); ++i) {
        ch = str[i];
        switch (ch) {
            case '+':
                result[j++] = ' ';
                break;
            case '%':
                if (i+2<strSize) {
                    ch1 = hex2num(str[i+1]);//高4位
                    ch2 = hex2num(str[i+2]);//低4位
                    if ((ch1!=NON_NUM) && (ch2!=NON_NUM))
                        result[j++] = (char)((ch1<<4) | ch2);
                    i += 2;
                    break;
                } else {
                    break;
                }
            default:
                result[j++] = ch;
                break;
        }
    }

    result[j] = 0;
    return j;
}
int URLEncode(const char* str, const int strSize, char* result, const int resultSize)
{
    int i;
    int j = 0;//for result index
    char ch;

    if ((str==NULL) || (result==NULL) || (strSize<=0) || (resultSize<=0)) {
        return 0;
    }

    for ( i=0; (i<strSize)&&(j<resultSize); ++i) {
        ch = str[i];
        if (((ch>='A') && (ch<'Z')) ||
            ((ch>='a') && (ch<'z')) ||
            ((ch>='0') && (ch<'9'))) {
            result[j++] = ch;
        } else if (ch == ' ') {
            result[j++] = '+';
        } else if (ch == '.' || ch == '-' || ch == '_' || ch == '*') {
            result[j++] = ch;
        } else {
            if (j+3 < resultSize) {
                sprintf(result+j, "%%%02X", (unsigned char)ch);
                j += 3;
            } else {
                return 0;
            }
        }
    }

    result[j] = '\0';
    return j;
}
int gbk_strlen(const char* str)
{
    const char* p = str;		//p用于后面遍历

    while(*p)					//若是结束符0，则结束循环
    {
        if(*p < 0 && (*(p+1)<0 || *(p+1) < 63))			//中文汉字情况
        {
            str++;				//str移动一位，p移动移动2位，因此长度加1
            p += 2;
        }
        else
        {
            p++;				//str不动，p移动一位，长度加1
        }
    }
    return p-str;				//返回地址之差
}
void http_request(char *text)
{
    //初始化DLL
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    //创建套接字
    SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    //向服务器发起请求
    struct sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
    sockAddr.sin_family = PF_INET;
    sockAddr.sin_addr.s_addr = inet_addr("123.56.12.53");
    sockAddr.sin_port = htons(2347);
    connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

    char str[1024*3];
    char content[100];
    char dest[105];
    char *texts = text;
    URLEncode(texts,strlen(texts),content,100);

    strcpy(dest,"command-");
    strcat(dest,content);
    printf("%s\n",dest);
    sprintf(str,"POST / HTTP/1.1\nUser-Agent: jackcsm\nContent-Type: application/x-www-form-urlencoded \nContent-Length: %d\r\n\r\n%s",strlen(dest)+1,dest);

    //printf("%s\n",str);
    send(sock, str, strlen(str)+sizeof(char), NULL);

    //接收服务器传回的数据
    char szBuffer[MAXBYTE] = {0};
    recv(sock, szBuffer, MAXBYTE, NULL);

    char source[1024];
    URLDecode(szBuffer,strlen(szBuffer),source,1024);
    //输出接收到的数据

    printf("Message form server: %s\n", source);
    //关闭套接字
    closesocket(sock);
    //终止使用 DLL
    WSACleanup();
    system("pause");

}
int main(){

    printf("welcome to use http client,input some data then the server will response your request\n");
    char message[100];
    system("chcp 65001");
    char *menu = " +----------------------------------------------------------------------+\n"
                 " | simple talk framework                                                |\n"
                 " +----------------------------------------------------------------------+\n"
                 " |       login and talk with your friends                               |\n"
                 " |                                                                      |\n"
                 " |       search-friends[1] add-friend[2]             remove-friend[3]   |\n"
                 " |       my-friends[4]     friend-profile[5]         my-profile[6]      |\n"
                 " |                                                                      |\n"
                 " |                                                                      |\n"
                 " |                                                                      |\n"
                 " +----------------------------------------------------------------------+\n"
                 " | exit[Q]                                                              |\n"
                 " +----------------------------------------------------------------------+";
    printf("\r\n%s\n",menu);
    while (1){

        printf(">");
        scanf("%s",message);
        if (strcasecmp(message,"Q")==0){
            break;
        }
        if (message){
            http_request(message);
            memset(message,0, sizeof(message));
        }
    }
    char *source = "中国人";
    char dest[100];


    return 0;
}