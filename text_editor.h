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

typedef struct backup
{
    Dll_t *head,*tail,*cursor_line;
    int line_num,col_num,total_lines;
    struct backup *next;
}Backup_State;

typedef struct state
{
    Dll_t *head,*tail,*cursor_line;
    int line_num,col_num,total_lines;
    char *clipboard;
    Backup_State *undo_stack,*redo_stack;
}Editor_State;

int insert(Editor_State *State,char *command);
int print(Editor_State *State);
int validate_delete_command(char *command);
int delete(Editor_State *State,int num,int flag);

//navigation functions
void move_left(Editor_State *State);
void move_right(Editor_State *State);
void sol(Editor_State *State);
void eol(Editor_State *State);
void eof(Editor_State *State);
void sof(Editor_State *State);
void move_up(Editor_State *State);
void move_down(Editor_State *State);

//cut copy paste functions
int validate_copycut_command(char *command,int comlen);
int copy_or_cut(Editor_State *State,char *command,int comlen);
int paste(Editor_State *State);

//find and replace text functions
int validate_replace_command(char *command);
Dll_t *find_text(Editor_State *State,char *str);
int replace_text(Editor_State *State,char *command);

//undo redo functions
Dll_t *clone_list(Dll_t *head, Dll_t **new_tail, Dll_t *orig_cursor, Dll_t **new_cursor);
void free_list(Dll_t *head);
void clear_stack(Backup_State **stack);
void save_history(Editor_State *State);
int undo(Editor_State *State);
int redo(Editor_State *State);








#endif