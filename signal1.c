//
// Created by 1655664358@qq.com on 2019/9/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <windows.h>

void interrupt(int sig)
{
    printf("中断处理程序%d\n",sig);
}
int main(void)
{
    signal(SIGINT,interrupt);

    for (int i = 0; ; ++i) {
        printf("i=%d\n",i);
        Sleep(2);
    }

    return 0;
}