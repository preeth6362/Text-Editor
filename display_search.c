#include "text_editor.h"

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

int find(Editor_State *State,char *command)
{
    if(State->head==NULL)
    {
        printf("Document is empty\n");
        return FAILURE;
    }
    int line=1;
    Dll_t *temp=State->head;
    char *start;int found=0;
    while(temp!=NULL)
    {
        if(start=strstr(temp->data,command))
        {
            if(!found)
            printf("%s is Found ",command);
            found=1;
            printf("at line %d at column %d\n",line,(int)(start-temp->data));
        }
        temp=temp->next;
        line++;
    }
    if(found)return SUCCESS;
    else
    {
        printf("Data not found\n");
        return FAILURE;
    }
}

void print_supported_commands()
{
printf("Supported Text Editor Commands:\n");
printf("1.  insert                  - Create a new blank line at the end of the document\n");
printf("2.  insert <text>           - Append the supplied text as a new line at the end of the document\n");
printf("3.  delete <num_chars>      - Delete the requested number of characters before the cursor, if valid\n");
printf("4.  print                   - Display all lines and the current cursor position\n");
printf("5.  undo                    - Undo the most recent supported editing operation\n");
printf("6.  redo                    - Redo the most recently undone operation\n");
printf("7.  sol                     - Move the cursor to the start of the current line\n");
printf("8.  eol                     - Move the cursor to the end of the current line\n");
printf("9.  sof                     - Move the cursor to the start of the file\n");
printf("10. eof                     - Move the cursor to the end of the file\n");
printf("11. left / right            - Move the cursor one character left or right where possible\n");
printf("12. up / down               - Move to the corresponding position on the previous or next line where possible\n");
printf("13. copy <startpos> <endpos> - Copy a character range from the current line (start inclusive, end exclusive)\n");
printf("14. cut <startpos> <endpos>  - Cut a character range from the current line and place it in the clipboard\n");
printf("15. paste                   - Insert the clipboard contents at the cursor location\n");
printf("16. find <text>             - Search for the specified text value\n");
printf("17. replace <old> <new>     - Replace the old text with the new text without requiring quotation marks\n");
printf("18. open <file>             - Open a document by name\n");
printf("19. save <file>             - Save the current document under the supplied name\n");
printf("20. close                   - Close the current document\n");
printf("21. help                    - Display the supported commands and usage\n");
printf("22. exit                    - Exit the editor cleanly and release resources\n");

}