#include<stdio.h>
#include<string.h>
#include<sys/stat.h> //this header file is for system commands
#include<sys/types.h>

// two flags: -p and -v
int main(int argc, char* argv[])
{
    FILE* fptr = fopen("history.txt","a+");
    int i;
    char str[100] = "";
    strcat(str,"mkdir");
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
        FILE* help = fopen("documentation/mkdir.txt", "r");
        char ch;
        while((ch = fgetc(help))!=EOF)
        {
            printf("%c",ch);
        }

        fclose(help);
        return 0;
    }

    if(argc < 2)
    {
        printf("Too few arguments for mkdir");
        return 1;
    }

    if(argc > 3)
    {
        printf("Too many arguments for mkdir");
        return 1;
    }

    if(argc == 2)
    {
        int x;
        x = mkdir(argv[1]);
        if(x == -1)
        {
            printf("mkdir: cannot create directory '%s'", argv[1]);
            return 1;
        }
    }

    if(argc == 3)
    {
        if(strcmp(argv[1],"-v") == 0)
        {
            int x = mkdir(argv[2]);

            if(x == -1)
            {
                printf("mkdir: cannot create directory '%s'", argv[2]);
                return 1;
            }

            if(x == 0)
            {
                printf("mkdir: created directory '%s'", argv[2]);
                return 0;
            }
        }

        else if(strcmp(argv[1],"-p") == 0)
        {
            char* dir = strtok(argv[2],"/");
            while(dir!=NULL)
            {
                int x = mkdir(dir);
                if(x == -1)
                {
                    printf("mkdir: cannot create directory '%s'",dir);
                    return 1;
                }
                chdir(dir);
                // passing NULL means that strtok will get the tokens from the buffer
                dir = strtok(NULL,"/");
            }
        }

        else{
            printf("invalid syntax");
            return 1;
        }
    }

    return 0;
}