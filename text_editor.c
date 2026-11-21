#include "text_editor.h"


int main()
{
    Editor_State State={NULL,NULL,NULL,1,0,0};
    printf("_____________________________________________________________________________________________________________________\n");
    printf("\t\t\tTEXT EDITOR v1.0\n");
    printf("_____________________________________________________________________________________________________________________\n");
    char command[300];
    do
    {
        printf("Text Editor Commands\n");
        printf("1. insert <text> - Add text as a new line at the end\n2. delete <num_chars> - Delete characters before the cursor\n");
        printf("3. undo - Undo the last operation\n4. redo - Redo the last undone operation\n5. print - Print the current document\n");
        printf("6. replace <old> <new>\n7. exit - Exit the text editor\n\nEnter command: ");
        scanf(" %[^\n]",command);
    
        if(strncmp(command,"insert",6)==0)
        {
            if(command[6]!='\0'&&command[6]!=' ')
            {
                printf("Unknown Command Enter the proper Command\n\n");
            }
            else
            {
            if(insert(&State,command)==FAILURE)
            printf("Insert command operation failed\n\n");
            else
            printf("Insert command operation successful\n\n");
            }
        }
        else if(strcmp(command,"print")==0)
        {
            print(&State);
        }
        else if(strncmp(command,"delete",6)==0)
        {
            if(validate_delete_command(command)==FAILURE)
            printf("Unknown Command Enter the proper Command\n\n");
            else
            {
                if(delete(&State,command+7)==FAILURE)
                printf("Delete command operation failed\n\n");
                else
                printf("Delete command operation successful\n\n");
            }
        }
        else if(strcmp(command,"left")==0)
        move_left(&State);
        else if(strcmp(command,"right")==0)
        move_right(&State);
        else if(strcmp(command,"sol")==0)
        sol(&State);
        else if(strcmp(command,"eol")==0)
        eol(&State);
        else if(strcmp(command,"eof")==0)
        eof(&State);
        else if(strcmp(command,"sof")==0)
        sof(&State);
        else if(strcmp(command,"up")==0)
        move_up(&State);
        else if(strcmp(command,"down")==0)
        move_down(&State);




    }while(strcmp("exit",command)!=0);
}