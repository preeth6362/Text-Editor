#include "text_editor.h"

int open_file(Editor_State *State,char *filename)
{
    if(State->head!=NULL)
    {
        char opt;
        printf("Do you want to Save your current changes y/n: ");
        scanf(" %c",&opt);
        if(opt=='y')
        {
            char filename[30];
            printf("Enter the filename in which you want to save the changes: ");
            scanf("%s",filename);
            save_file(State,filename);
        }
    }
    FILE *fptr=fopen(filename,"r");
    if(fptr==NULL)
    {
        printf("Error opening file/ file does not exist\n");
        return FAILURE;
    }
    free_list(State->head);
    clear_stack(&State->undo_stack);
    clear_stack(&State->redo_stack);
    State->line_num=1;
    State->col_num=0;
    State->total_lines=0;
    State->head=State->tail=State->cursor_line=NULL;
    char text[300];
    while(fgets(text,300,fptr)!=NULL)
    {
        int len=strlen(text);
        if(len>0 && text[len-1]=='\n') 
        text[len-1]='\0';
        Dll_t *nnode=malloc(sizeof(Dll_t));
        nnode->data=malloc(strlen(text)+1);
        strcpy(nnode->data,text);
        nnode->prev=nnode->next=NULL;
        if(State->head==NULL)
        State->head=State->tail=nnode;
        else{
            nnode->prev=State->tail;
            State->tail->next=nnode;
            State->tail=nnode;
        }
        State->total_lines++;
    }
    State->cursor_line=State->head;
    State->line_num=1;
    State->col_num=0;
    fclose(fptr);
    return SUCCESS;
}

int save_file(Editor_State *State,char *filename)
{
    if(State->head==NULL)
    {
        printf("Nothing to Save\n");
        return FAILURE;
    }
    FILE *fptr=fopen(filename,"w");
    Dll_t *temp=State->head;
    while(temp!=NULL)
    {
        fprintf(fptr,"%s\n",temp->data);
        temp=temp->next;
    }
    fclose(fptr);
    return SUCCESS;
}
int close_file(Editor_State *State)
{
    if(State->head==NULL)
    {
        printf("No active document to close\n");
        return FAILURE;
    }
    else if(State->head!=NULL)
    {
        char opt;
        printf("Do you want to Save your current changes y/n: ");
        scanf(" %c",&opt);
        if(opt=='y')
        {
            char filename[30];
            printf("Enter the filename in which you want to save the changes: ");
            scanf("%s",filename);
            save_file(State,filename);
        }
    }
    free_list(State->head);
    clear_stack(&State->undo_stack);
    clear_stack(&State->redo_stack);
    State->line_num=1;
    State->col_num=0;
    State->total_lines=0;
    State->head=State->tail=State->cursor_line=NULL;
    return SUCCESS;
}