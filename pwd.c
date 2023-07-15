#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<ctype.h>

int main(int argc, char* argv[])
{
    FILE* fptr = fopen("history.txt","a+");
    int i;
    char str[100] = "";
    strcat(str,"pwd");
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
        FILE* help = fopen("documentation/pwd.txt", "r");
        char ch;
        while((ch = fgetc(help))!=EOF)
        {
            printf("%c",ch);
        }

        fclose(help);
        return 0;
    }

    char cwd[100];

    if(argc > 2)
    {
        printf("Too many arguments provided for pwd");
        return 1;
    }

    if(argc == 1)
    {
        getcwd(cwd,sizeof(cwd));
        printf("%s", cwd);
    }

    if(argc == 2)
    {
        if(strcmp(argv[1],"-P") == 0)
        {
            getcwd(cwd,sizeof(cwd));

            cwd[1] = '\\';

            char ch = cwd[0];
            cwd[0] = cwd[1];
            cwd[1] = ch;

            cwd[1] = tolower(cwd[1]);

            printf("%s", cwd);
        }

        if(strcmp(argv[1],"-W") == 0)
        {
            getcwd(cwd,sizeof(cwd));
            printf("%s", cwd);
        }
    }

    return 0;
}