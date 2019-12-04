//
// Created by 1655664358@qq.com on 2019/9/28.
//

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>

struct array{
    char key[20];
    char value[1024];
};
char * findElem(struct array *data,char *key);
char * json(struct array *data);
int main(void)
{


    struct array address[] = {{"address","bejing"},{"age","20"},{"sex","male"}};

    char *data = findElem(address,"sex");
    printf("%s\n",data);

    char *jsonData = json(address);
    printf("%s\n",jsonData);
    return 0;
}

char * findElem(struct array *data,char *key)
{
    for (int i=0;i<3;i++){
        if (strcmp(data[i].key,key)==0){
            return data[i].value;
        }
    }
    return "null";
}

char * json(struct array *data)
{
    //{address:'beijing',age:20,sex:'male'}
    static char jsonData[50]="{";
    for (int i=0;i<3;i++){
        strcat(jsonData,"\"");
        strcat(jsonData,data[i].key);
        strcat(jsonData,"\"");
        strcat(jsonData,":");

        if (!isalnum(data[i].value)){
            strcat(jsonData,"\"");
        }
        strcat(jsonData,data[i].value);
        if (!isalnum(data[i].value)){
            strcat(jsonData,"\"");
        }
        if (i<2){
            strcat(jsonData,",");
        }

    }
    strcat(jsonData,"}");
    return jsonData;
}