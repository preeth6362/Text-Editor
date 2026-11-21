#include "text_editor.h"

void move_left(Editor_State *State)
{
    if(State->head==NULL)
    {
        printf("The document is Empty cannot move\n");
        return;
    }
    if(State->col_num>0)
        State->col_num--;
    else
        printf("Cursor is already at the beginning of line cannot go left\n");
    print(State);
}
void move_right(Editor_State *State)
{
    if(State->head==NULL)
    {
        printf("The document is Empty cannot move\n");
        return;
    }
    if(strlen(State->cursor_line->data)>State->col_num)
    State->col_num++;
    else
    printf("Cursor is already at the end of line cannot go right\n");
    print(State);
}
void sol(Editor_State *State)
{
    if(State->head==NULL)
    {
        printf("The document is Empty cannot move\n");
        return;
    }
    State->col_num=0;
    print(State);
}
void eol(Editor_State *State)
{
    if(State->head==NULL)
    {
        printf("The document is Empty cannot move\n");
        return;
    }
    State->col_num=strlen(State->cursor_line->data);
    print(State);
}
void eof(Editor_State *State)
{
    if(State->head==NULL)
    {
        printf("The document is Empty cannot move\n");
        return;
    }
    State->cursor_line=State->tail;
    State->col_num=strlen(State->cursor_line->data);
    State->line_num=State->total_lines;
    print(State);
}
void sof(Editor_State *State)
{
    if(State->head==NULL)
    {
        printf("The document is Empty cannot move\n");
        return;
    }
    State->cursor_line=State->head;
    State->col_num=0;
    State->line_num=1;
    print(State);
}
void move_up(Editor_State *State)
{
    if(State->head==NULL)
    {
        printf("The document is Empty cannot move\n");
        return;
    }
    if(State->cursor_line->prev==NULL)
    printf("You are already at the top of document cannot move up\n");
    else
    {
        State->cursor_line=State->cursor_line->prev;
        State->line_num--;
        int new_len=strlen(State->cursor_line->data);
        if(new_len<State->col_num)
        State->col_num=new_len;
    }
    print(State);
}
void move_down(Editor_State *State)
{
    if(State->head==NULL)
    {
        printf("The document is Empty cannot move\n");
        return;
    }
    if(State->cursor_line->next==NULL)
    printf("You are already at the bottom of document cannot move down\n");
    else
    {
        State->cursor_line=State->cursor_line->next;
        State->line_num++;
        int new_len=strlen(State->cursor_line->data);
        if(new_len<State->col_num)
        State->col_num=new_len;
    }
    print(State);
}