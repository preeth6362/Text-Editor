#include "text_editor.h"

Dll_t *clone_list(Dll_t *head, Dll_t **new_tail, Dll_t *orig_cursor, Dll_t **new_cursor)
{
    Dll_t *temp=head;
    Dll_t *headb=NULL;
    *new_tail=NULL;*new_cursor=NULL;
    if(head==NULL)return NULL;
    while(temp!=NULL)
    {
        Dll_t *nnode=malloc(sizeof(Dll_t));
        nnode->data=malloc(strlen(temp->data)+1);
        strcpy(nnode->data,temp->data);
        nnode->prev=nnode->next=NULL;
        if(headb==NULL)
            headb=*new_tail=nnode;
        else
        {
        nnode->prev=*new_tail;
        (*new_tail)->next=nnode;
        *new_tail=nnode;
        }
        if(temp==orig_cursor)*new_cursor=nnode;
        temp=temp->next;
    }
    return headb;
}
void free_list(Dll_t *head)
{
    Dll_t *del;
    while(head!=NULL)
    {
        del=head;
        free(head->data);
        head=head->next;
        free(del);
    }
}
void clear_stack(Backup_State **stack)
{
    Backup_State *del;
    while(*stack!=NULL)
    {
        del=*stack;
        free_list((*stack)->head);
        *stack=(*stack)->next;
        free(del);
    }
}

void save_history(Editor_State *State)
{
    Backup_State *nnode=malloc(sizeof(Backup_State));
    nnode->head=clone_list(State->head,&nnode->tail,State->cursor_line,&nnode->cursor_line);
    nnode->line_num=State->line_num;
    nnode->col_num=State->col_num;
    nnode->total_lines=State->total_lines;
    nnode->next=State->undo_stack;
    State->undo_stack=nnode;
    clear_stack(&State->redo_stack);
}

int undo(Editor_State *State)
{
    if(State->undo_stack==NULL)
    {
        printf("Nothing to undo\n");
        return FAILURE;
    }
    Backup_State *nnode=malloc(sizeof(Backup_State));
    nnode->head=clone_list(State->head,&nnode->tail,State->cursor_line,&nnode->cursor_line);
    nnode->line_num=State->line_num;
    nnode->col_num=State->col_num;
    nnode->total_lines=State->total_lines;
    nnode->next=State->redo_stack;
    State->redo_stack=nnode;
    Backup_State *popped=State->undo_stack;
    State->undo_stack=State->undo_stack->next;
    free_list(State->head);
    State->head=popped->head;
    State->tail=popped->tail;
    State->cursor_line=popped->cursor_line;
    State->line_num=popped->line_num;
    State->col_num=popped->col_num;
    State->total_lines=popped->total_lines;
    free(popped);
    return SUCCESS;
}

int redo(Editor_State *State)
{
    if(State->redo_stack==NULL)
    {
        printf("Nothing to redo\n");
        return FAILURE;
    }
    Backup_State *nnode=malloc(sizeof(Backup_State));
    nnode->head=clone_list(State->head,&nnode->tail,State->cursor_line,&nnode->cursor_line);
    nnode->line_num=State->line_num;
    nnode->col_num=State->col_num;
    nnode->total_lines=State->total_lines;
    nnode->next=State->undo_stack;
    State->undo_stack=nnode;
    Backup_State *popped=State->redo_stack;
    State->redo_stack=State->redo_stack->next;
    free_list(State->head);
    State->head=popped->head;
    State->tail=popped->tail;
    State->cursor_line=popped->cursor_line;
    State->line_num=popped->line_num;
    State->col_num=popped->col_num;
    State->total_lines=popped->total_lines;
    free(popped);
    return SUCCESS;
}