#include<stdio.h>
#include<string.h>

int main(int argc, char* argv[])
{
    FILE* fptr = fopen("history.txt","a+");
    int i;
    char str[100] = "";
    strcat(str,"history");
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
        FILE* help = fopen("documentation/historyhelp.txt", "r");
        char ch;
        while((ch = fgetc(help))!=EOF)
        {
            printf("%c",ch);
        }

        fclose(help);
        return 0;
    }

    if(argc == 1)
    {
        fptr = fopen("history.txt","r");
    }

    if(argc == 2)
    {
        if(strcmp(argv[1], "-c") == 0)
        {
            fptr = fopen("history.txt", "w");   
        }
        
        else{
            printf("Invalid syntax");
        }
    }
    
    // maximum length of command and it's arguments together can 
    char buf[500];
    int countLines = 1;
    
    while(fgets(buf,sizeof(buf),fptr))
    {
        printf("%d      ", countLines);
        printf("%s",buf);
        countLines++;
    }

    fclose(fptr);

    return 0;
}