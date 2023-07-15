#include<stdio.h>
#include<string.h>
#include<errno.h>
//two flags: -n and -e
int main(int argc, char* argv[]){

    FILE* fptr = fopen("history.txt","a+");
    int i;
    char str[100] = "";
    strcat(str,"cat");
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
        FILE* help = fopen("documentation/cat.txt", "r");
        char ch;
        while((ch = fgetc(help))!=EOF)
        {
            printf("%c",ch);
        }

        fclose(help);
        return 0;
    }

    if(argc<2){
      
        printf("Error : Please provide input file name");
        return 1;
    }
    else if(argc>3){
        printf("Error : Multiple files in input");
        return 2;
    }

    if(argc == 2)
    {
        FILE* fptr = fopen(argv[1], "r");
            if(!fptr)
            {
                // printf("'%s' No such file exists.", argv[1]);
                // error handling
                perror(argv[1]);
                return 1;
            }
            char ch; 
            while((ch=fgetc(fptr))!=EOF){
                printf("%c", ch);
            }

            // closing the file
            fclose(fptr);
    }

    if(argc == 3)
    {
        FILE* fptr = fopen(argv[2], "r");
        if(strcmp(argv[1],"-e") == 0)
        {
            if(!fptr)
            {
                perror(argv[2]);
                return 1;
            }

            char ch;
            while((ch=fgetc(fptr))!=EOF)
            {
                if(ch == '\n')
                {
                    ch = '$';
                }
                printf("%c", ch);
                if(ch == '$')
                {
                    printf("\n");
                }
            }
            printf("$");
            fclose(fptr);
        }

        else if(strcmp(argv[1],"-n") == 0)
        {
            if(!fptr)
            {
                perror(argv[2]);
                return 1;
            }

            // maximum length of line specified is 100
            int MAX = 100;
            // a buffer created to store the contents of each of the lines of the file
            char buf[MAX];
            // count of lines starts from 1
            int count = 1;
            while(fgets(buf,MAX,fptr))
            {
                printf("%d      ",count);
                printf("%s",buf);
                count = count+1;
            }
            fclose(fptr);
        }

        else{
            printf("Invalid syntax");
            return 1;
        }
    }
    
    return 0;
}