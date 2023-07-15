#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<errno.h>
#include<stdlib.h>
// flags: -i: permission from user
// -v: verbose
int main(int argc, char* argv[])
{
    FILE* fptr = fopen("history.txt","a+");
    int i;
    char str[100] = "";
    strcat(str,"rm");
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
        FILE* help = fopen("documentation/rm.txt", "r");
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
        printf("Too few arguments for rm");
        return 1;
    }

    if(argc > 3)
    {
        printf("Too many arguments for rm");
        return 1;
    }

    if(argc == 2)
    {
        int x = remove(argv[1]);
        if(x != 0)
        {
            perror(argv[1]);
        }
    }

    if(argc == 3)
    {
        if(strcmp(argv[1],"-i") == 0)
        {
            printf("rm: remove regular file '%s' ",argv[2]);
            fflush(stdout);
            char ch;
            scanf("%c", &ch);

            if(ch == 'y')
            {
                int x = remove(argv[2]);
                if(x != 0)
                {
                    perror(argv[2]);
                }
            }

            if(ch == 'n')
            {
                return 1;
            }
        }

        else if(strcmp(argv[1],"-v") == 0)
        {
            int x = remove(argv[2]);
            if(x == 0)
            {
                printf("removed '%s'", argv[2]);
                return 0;
            }

            else{
                perror(argv[2]);
                return 1;
            }
        }
        else{
            printf("Invalid syntax");
            return 1;
        }

    }

    return 0;
}