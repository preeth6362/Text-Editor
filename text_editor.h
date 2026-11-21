#ifndef text
#define text

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define SUCCESS 0
#define FAILURE 1

typedef struct node
{
    char *data;
    struct node *prev,*next;
}Dll_t;

typedef struct state
{
    Dll_t *head,*tail,*cursor_line;
    int line_num,col_num,total_lines;
}Editor_State;

int insert(Editor_State *State,char *command);
int print(Editor_State *State);
int validate_delete_command(char *command);
int delete(Editor_State *State,char *command);
void move_left(Editor_State *State);
void move_right(Editor_State *State);
void sol(Editor_State *State);
void eol(Editor_State *State);
void eof(Editor_State *State);
void sof(Editor_State *State);
void up(Editor_State *State);
void down(Editor_State *State);














#endif