#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<dirent.h>  

void print_directory(char* flag)
{
    // opendir() returns pointer of directory
    DIR* directory = opendir(".");

    if(directory == NULL)
    {
        printf("No such directory");
        return;
    }

    // readdir() reads the directory and gives us the entry pointer for that directory
    struct dirent* directory_entry = readdir(directory);
    int i=0;
    while(directory_entry!=NULL)
    {
        if(strcmp(flag, "-A") != 0)
        {
            printf("%s%s", directory_entry->d_name, flag);
        }
        else{
            if(i>=2)
            {
                printf("%s    ", directory_entry->d_name);   
            }
        }

        directory_entry = readdir(directory);
        i++;
    }

    return;
}

int main(int argc, char* argv[])
{
    
    FILE* fptr = fopen("history.txt","a+");
    int i;
    char str[100] = "";
    strcat(str,"ls");
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
        FILE* help = fopen("documentation/ls.txt", "r");
        char ch;
        while((ch = fgetc(help))!=EOF)
        {
            printf("%c",ch);
        }

        fclose(help);
        return 0;
    }
    
    if(argc > 2)
    {
        printf("Too many arguments provided for ls");
        return 1;
    }

    // opendir() returns pointer of directory
    DIR* directory = opendir(".");

    if(directory == NULL)
    {
        printf("No such directory");
        return 1;
    }

    if(argc == 1)
    {
        print_directory("    ");
    }

    if(argc == 2)
    {
        if(strcmp(argv[1],"-N") == 0)
        {
            print_directory("\n");
        }

        else if(strcmp(argv[1],"-m") == 0)
        {
            print_directory(", ");
        }

        else if(strcmp(argv[1], "-A") == 0)
        {
            print_directory("-A");
        }

        else{
            printf("Invalid syntax");
        }

    }

   
    return 0;
}