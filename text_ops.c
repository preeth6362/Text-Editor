#include "text_editor.h"

int insert(Editor_State *State,char *command)
{
    Dll_t *nnode=malloc(sizeof(Dll_t));
    if(nnode==NULL)return FAILURE;
    save_history(State);
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

int delete(Editor_State *State,int num,int flag)
{
    if(State->head==NULL)
    {
        printf("Document is Empty\n");
        return FAILURE;
    }
    else if(num>State->col_num)
    {
        printf("Not enough characters to delete\n");
        return FAILURE;
    }
    if(flag)
    save_history(State);
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

int copy_or_cut(Editor_State *State,char *command,int comlen)
{
    if(State->head==NULL)
    {
        printf("Document Empty\n");
        return FAILURE;
    }
    int left,right;
    sscanf(command+comlen+1,"%d %d",&left,&right);
    if(left<0 || left>=right || right>strlen(State->cursor_line->data))
    {
        printf("Invalid Range\n");
        return FAILURE;
    }
    State->clipboard=malloc((right-left)+1);
    if(State->clipboard==NULL)return FAILURE;
    int i,j;
    for(i=left,j=0;i<right;i++,j++)
    State->clipboard[j]=State->cursor_line->data[i];
    State->clipboard[j]='\0';
    if(comlen==3)
    {
        save_history(State);
        State->col_num=right;
        if(delete(State,right-left,0)==FAILURE)
        return FAILURE;
    }
    return SUCCESS;
}

int paste(Editor_State *State)
{
    if(State->head==NULL)
    {
        printf("Document is Empty\n");
        return FAILURE;
    }
    if(State->clipboard==NULL)
    {
        printf("The clipboard is Empty\n");
        return FAILURE;
    }
    save_history(State);
    int len=strlen(State->cursor_line->data);
    int right_len=strlen(State->cursor_line->data+State->col_num);
    char *right=malloc(right_len+1);
    strcpy(right,State->cursor_line->data+State->col_num);
    State->cursor_line->data[State->col_num]='\0';
    
    State->cursor_line->data=realloc(State->cursor_line->data,len+strlen(State->clipboard)+1);
    strcat(State->cursor_line->data,State->clipboard);
    strcat(State->cursor_line->data,right);
    State->col_num+=strlen(State->clipboard);
    free(right);
    return SUCCESS;
}

Dll_t *find_text(Editor_State *State,char *str)
{
    if(State->head==NULL)
    {
        printf("Document is Empty\n");
        return NULL;
    }
    Dll_t *temp=State->head;
    while(temp!=NULL)
    {
        if(strstr(temp->data,str))
            return temp;
        temp=temp->next;
    }
    return NULL;
}
int replace_text(Editor_State *State,char *command)
{
    int old_len=0,new_len=0,i;
    for(i=0;command[i]!=' ';i++)
    old_len++;
    for(i=i+1;command[i]!='\0';i++)
    new_len++;
    char *old_text=malloc(old_len+1);
    char *new_text=malloc(new_len+1);
    sscanf(command,"%s %s",old_text,new_text);
    Dll_t *text_node=find_text(State,old_text);
    if(text_node==NULL)
    {
        printf("text not found\n");
        free(old_text);
        free(new_text);
        return FAILURE;
    }
    save_history(State);
    while(text_node!=NULL)
    {
    int pos=0;
    char *start;
    while ((start = strstr(text_node->data + pos, old_text)) != NULL)
    {
    int left_len=start-text_node->data;
    char *right=malloc(strlen(start+old_len)+1);
    strcpy(right,start+old_len);
    text_node->data[left_len]='\0';
    text_node->data=realloc(text_node->data,left_len+new_len+strlen(right)+1);
    strcat(text_node->data,new_text);
    strcat(text_node->data,right);
    free(right);
    pos=left_len+new_len;
    }
    text_node=text_node->next;
    }
    if(State->cursor_line!=NULL)
    {
        if(strlen(State->cursor_line->data)<State->col_num)
        State->col_num=strlen(State->cursor_line->data);
    }
    free(old_text);free(new_text);
    return SUCCESS;
}