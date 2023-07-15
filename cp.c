#include<stdio.h>
#include<string.h>
#include<unistd.h>

int main(int argc, char* argv[]){
    FILE* fptr = fopen("history.txt","a+");
    int i;
    char str[100] = "";
    strcat(str,"cp");
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
        FILE* help = fopen("documentation/cp.txt", "r");
        char ch;
        while((ch = fgetc(help))!=EOF)
        {
            printf("%c",ch);
        }

        fclose(help);
        return 0;
    }

    if(argc < 3)
    {
        printf("Too few arguments provided for cp");
        return 1;
    }

    if(argc > 4)
    {
        printf("Too many arguments provided for cp");
        return 1;
    }


    FILE *file1, *file2;
    if(argc == 4)
    {
        if(access(argv[2], F_OK) != 0)
        {
        printf("'%s' No such file exists", argv[2]);
        return 1;
        }

        if(strcmp(argv[1],"-i") != 0)
        {
            printf("invalid operation for cp command");
            return 1;
        }

        else{
            // if access returns 0, it means the file exists, so throw a warning
            if(access(argv[3],F_OK) == 0)
            {
                printf("overwrite '%s' ?: y/n \n", argv[3]);
                // flushing the buffer 
                fflush(stdout);
                char ch;
                scanf("%c", &ch);
                if(ch == 'n')
                {
                    printf("Not overwritten!");
                    return 1;
                }
            }
        }

        file1 = fopen(argv[2], "r");
        file2 = fopen(argv[3], "w");
    }

    if(argc == 3)
    {
        if(access(argv[1], F_OK) != 0)
        {
             printf("'%s' No such file exists", argv[1]);
             return 1;
        }

    file1 = fopen(argv[1], "r");
    file2 = fopen(argv[2], "w");
    }

    char ch;
    while((ch=fgetc(file1)) != EOF)
    {
        fputc(ch, file2);
    }

    // closing the files
    fclose(file1);
    fclose(file2);
    return 0;
}