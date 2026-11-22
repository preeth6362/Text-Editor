#include "text_editor.h"

int validate_delete_command(char *command)
{
    if(command[6]!=' '||command[7]=='\0')
    return FAILURE;
    command=command+7;int i;
    for(i=0;command[i]!='\0';i++)
    {
        if(isdigit(command[i])==0)
        return FAILURE;
    }
    return SUCCESS;
}
int validate_copycut_command(char *command,int comlen)
{
    int space_count=0;
    int i;
    if(comlen==4)i=4;
    else if(comlen==3)i=3;
    for(;command[i]!='\0';i++)
    {
        if(command[i]==' ')
        space_count++;
    }
    if(space_count!=2)
    return FAILURE;
    if(comlen==4)
    {
    if(command[4]!=' ')
    return FAILURE;
    }
    if(comlen==3)
    {
    if(command[3]!=' ')
    return FAILURE;
    }
    if(comlen==4)i=5;
    else if(comlen==3)i=4;
    if(command[i]==' ')return FAILURE;
    for(;command[i]!=' '&&command[i]!='\0';i++)
    {
        if(command[i]!='+' && command[i]!='-' && isdigit(command[i])==0)
        return FAILURE;
    }
    if(command[i]=='\0')return FAILURE;
    i++;
    if(command[i]=='\0')return FAILURE;
    while(command[i]!='\0')
    {
        if(command[i]!='+' && command[i]!='-' && isdigit(command[i])==0)
        return FAILURE;
    i++;
    }
    return SUCCESS;
}

int validate_replace_command(char *command)
{
    int space_count=0;
    if(command[7]!=' ')return FAILURE;
    for(int i=7;command[i]!='\0';i++)
    {
        if(command[i]==' ')space_count++;
    }
    if(space_count!=2)return FAILURE;
    if(command[8]==' ')return FAILURE;
    return SUCCESS;
}