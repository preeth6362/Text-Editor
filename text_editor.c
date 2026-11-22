#include "text_editor.h"


int main()
{
    Editor_State State={NULL,NULL,NULL,1,0,0,NULL,NULL,NULL};
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
            {
            printf("Unknown Command Enter the proper Command\n\n");
            }
            else{
            int num;
            sscanf(command+7,"%d",&num);
            if(num==0)
            {
            printf("Number of characters to delete should be more than 0\n");
            printf("Delete command operation failed\n\n");
            }
            else
            {
                if(delete(&State,num,1)==FAILURE)
                printf("Delete command operation failed\n\n");
                else
                printf("Delete command operation successful\n\n");
            }
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
        else if(strncmp(command,"copy",4)==0)
        {
            if(validate_copycut_command(command,4)==FAILURE)
            printf("Unknown command Enter proper command\n");
            else
            {
                if(copy_or_cut(&State,command,4)==FAILURE)
                printf("copy operation failed\n\n");
                else
                printf("copy operation successful\n\n");
            }
        }
        else if(strncmp(command,"cut",3)==0)
        {
            if(validate_copycut_command(command,3)==FAILURE)
            printf("Unknown command Enter proper command\n");
            else
            {
                if(copy_or_cut(&State,command,3)==FAILURE)
                printf("cut operation failed\n\n");
                else
                printf("cut operation successful\n\n");
            }
        }
        else if(strcmp(command,"paste")==0)
        {
            if(paste(&State)==FAILURE)
            printf("paste operation failed\n\n");
           else
           printf("Paste opertaion Successful\n\n");
        }
        else if(strncmp(command,"replace",7)==0)
        {
            if(validate_replace_command(command)==FAILURE)
            printf("Unknown command Enter the proper command\n\n");
            else
            {
                if(replace_text(&State,command+8)==FAILURE)
                printf("replace operation failed\n\n");
                else
                printf("replace operation successful\n\n");
            }
        }
        else if(strcmp(command,"undo")==0)
        {
            if(undo(&State)==FAILURE)
            printf("undo operation failed\n\n");
            else
            printf("undo operation successful\n\n");
        }
        else if(strcmp(command,"redo")==0)
        {
            if(redo(&State)==FAILURE)
            printf("redo operation failed\n\n");
            else
            printf("redo operation successful\n\n");
        }




    if(strcmp(command,"print")!=0 && strcmp(comman,"exit")!=0)
    print(&State);
    }while(strcmp("exit",command)!=0);
}