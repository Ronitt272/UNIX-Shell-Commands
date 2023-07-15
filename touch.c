#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char* argv[])
{
    FILE* fptr = fopen("history.txt","a+");
    int i;
    char str[100] = "";
    strcat(str,"touch");
    strcat(str," ");
    for(i=1;i<argc;i++)
    {
        strcat(str, argv[i]);
        strcat(str, " ");
    }
    fputs(str,fptr);
    fputc('\n',fptr);
    fclose(fptr);

    // handling the case if user asks for help for the command
    if(argc == 2 && strcmp(argv[1], "--help") == 0)
    {
        FILE* help = fopen("documentation/touch.txt", "r");
        char ch;
        while((ch = fgetc(help))!=EOF)
        {
            printf("%c",ch);
        }

        fclose(help);
        return 0;
    }

    if(argc > 3)
    {
        printf("Too many arguments provided for touch");
        return 1;
    }

    if(argc < 2)
    {
        printf("Too few arguments provided for touch");
        return 1;
    }

    if(argc == 3)
    {
        // the file will be created without any prompts if it does not exist
        // If the file exists, a prompt is displayed to ask the user whether he/she wishes to override the existing file
        if(strcmp(argv[1],"-O") == 0)
        {
            if(access(argv[2],F_OK) == 0)
            {
                printf("'%s' File already exists: Overwrite ? y/n ", argv[2]);
                char ch;
                fflush(stdout);
                scanf("%c", &ch);

                if(ch == 'y')
                {
                    // fopen function in write mode performs overwrite
                    FILE* fptr = fopen(argv[2], "w");
                    fclose(fptr);
                    return 0;
                }

                else{
                    printf("Not overwritten!");
                    return 1;
                }

            }

            else{
                fptr = fopen(argv[2], "w");
                fclose(fptr);
                return 0;
            }
        }

        else{
            printf("Invalid syntax");
            return 1;
        }

    }


    if(argc == 2)
    {
        // Since, we have opened the file in write mode, and it does not exist, fopen will create the file 
        fptr = fopen(argv[1], "w");
        fclose(fptr);
    }
    
    return 0;
}