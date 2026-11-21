#include "text_editor.h"

int insert(Editor_State *State,char *command)
{
    Dll_t *nnode=malloc(sizeof(Dll_t));
    if(nnode==NULL)return FAILURE;
    nnode->prev=NULL;
    nnode->next=NULL;
    if(command[6]=='\0')
    {
    nnode->data=malloc(1);
    nnode->data[0]='\0';
    }
    else
    {
    nnode->data=malloc(strlen(command+7)+1);
    strcpy(nnode->data,command+7);
    }
    if(State->head==NULL)
    {
        State->head=State->tail=nnode;
        State->total_lines=1;
    }
    else
    {
    nnode->prev=State->tail;
    State->tail->next=nnode;
    State->tail=nnode;
    State->total_lines++;
    }
    State->cursor_line=nnode;
    State->line_num=State->total_lines;
    State->col_num=strlen(nnode->data);
    return SUCCESS;
}

int print(Editor_State *State)
{
    Dll_t *temp=State->head;
    int i=1;
    printf("\t\t\t\tDocument Dispaly\n");
    printf("_______________________________________________________________________________________________________________________________________\n");
    if(temp==NULL)
    printf("Empty Document\n");
else
{
    while(temp!=NULL)
    {
        printf("Line %d: %s\n",i++,temp->data);
        temp=temp->next;
    }
}
    printf("Cursor Position: Line %d, Column %d\n",State->line_num,State->col_num);
    printf("_______________________________________________________________________________________________________________________________________\n\n");
    return SUCCESS;
}

int delete(Editor_State *State,char *command)
{
    int num;
    sscanf(command,"%d",&num);
    if(num==0)
    {
        printf("Number of characters to delete should be more than 0\n");
        return FAILURE;
    }
    else if(State->head==NULL)
    {
        printf("Document is Empty\n");
        return FAILURE;
    }
    else if(num>State->col_num)
    {
        printf("Not enough characters to delete\n");
        return FAILURE;
    }
    int j=0;
    while(j<num)
    {
    for(int i=State->col_num-num;State->cursor_line->data[i]!='\0';i++)
    State->cursor_line->data[i]=State->cursor_line->data[i+1];
    j++;
    }
    State->col_num=State->col_num-num;
    return SUCCESS;
}