//
// Created by 1655664358@qq.com on 2019/9/30.
//

#include <stdio.h>

#include <winsock2.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#pragma comment(lib,"ws2_32.ib")

int main()
{

    WSADATA wsadata;

    WSAStartup(MAKEWORD(2,2),&wsadata);

    SOCKET sockfd = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);

    struct sockaddr_in address;
    memset(&address,0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(1234);
    address.sin_addr.s_addr = inet_addr("0.0.0.0");

    bind(sockfd,(SOCKADDR*)&address, sizeof(SOCKADDR));
    listen(sockfd,20);

    //SOCKADDR client;
    //int size = sizeof(SOCKADDR);

    struct sockaddr_in client;
    memset(&client,0, sizeof(client));
    int client_len = sizeof(client);
    SOCKET con = accept(sockfd,(SOCKADDR*)&client,&client_len);
printf("con=%d\n",con);
    char *str = "hello,world";
    send(con,str, strlen(str)+ sizeof(char),0);

char content[1024] = {0};
    recv(con,content, sizeof(content),0);
    printf("content=%s\n",content);
    closesocket(sockfd);
    closesocket(con);

    WSACleanup();

    return 0;
}