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