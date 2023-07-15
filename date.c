#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
// flags: -R and -u

int main(int argc, char* argv[])
{
    FILE* fptr = fopen("history.txt","a+");
    int i;
    char str[100] = "";
    strcat(str,"date");
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
        FILE* help = fopen("documentation/date.txt", "r");
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
        printf("Too many arguments for date");
        return 1;
    }

    time_t seconds = time(NULL);
     // gmtime function takes time_t*
    // so we pass address of seconds of data type time_t
    // gm_time returns a pointer to a structure variable which consists of various data members that provide us with date, time, day etc
   
    struct tm tm;
    if(argc == 2)
    {
        if(strcmp(argv[1],"-u") == 0)
        {
            tm = *gmtime(&seconds);
        }

        else if(strcmp(argv[1],"-R") == 0)
        {
            tm = *localtime(&seconds);
        }
        else{
            printf("Invalid syntax");
            return 1;
        }
    }

    if(argc == 1)
    {
        tm = *localtime(&seconds);
    }

    char month[5];
    char weekday[5];
    if(tm.tm_mon+1==1){
        strcpy(month,"Jan");
    }
    if(tm.tm_mon+1==2){
        strcpy(month,"Feb");
    }
    if(tm.tm_mon+1==3){
        strcpy(month,"Mar");
    }
    if(tm.tm_mon+1==4){
        strcpy(month,"Apr");
    }
    if(tm.tm_mon+1==5){
        strcpy(month,"May");
    }
    if(tm.tm_mon+1==6){
        strcpy(month,"Jun");
    }
    if(tm.tm_mon+1==7){
        strcpy(month,"Jul");
    }
    if(tm.tm_mon+1==8){
        strcpy(month,"Aug");
    }
    if(tm.tm_mon+1==9){
        strcpy(month,"Sep");
    }
    if(tm.tm_mon+1==10){
        strcpy(month,"Oct");
    }
    if(tm.tm_mon+1==11){
        strcpy(month,"Nov");
    }
    if(tm.tm_mon+1==12){
        strcpy(month,"Dec");
    }
    if(tm.tm_wday+1==2){
        strcpy(weekday,"Mon");
    }
    if(tm.tm_wday+1==3){
        strcpy(weekday,"Tue");
    }
    if(tm.tm_wday+1==4){
        strcpy(weekday,"Wed");
    }
    if(tm.tm_wday+1==5){
        strcpy(weekday,"Thu");
    }
    if(tm.tm_wday+1==6){
        strcpy(weekday,"Fri");
    }
    if(tm.tm_wday+1==7){
        strcpy(weekday,"Sat");
    }
    if(tm.tm_wday+1==1){
        strcpy(weekday,"Sun");
    }

   if(argc == 1)
   {
        printf("%s %s %d %02d:%02d:%02d IST %d",weekday,month,tm.tm_mday,tm.tm_hour,tm.tm_min,tm.tm_sec,tm.tm_year+1900);
   }

   if(argc == 2)
   {
        if(strcmp(argv[1],"-u") == 0)
        {
           printf("%s %s %d %02d:%02d:%02d UTC %d",weekday,month,tm.tm_mday,tm.tm_hour,tm.tm_min,tm.tm_sec,tm.tm_year+1900);
        }

        if(strcmp(argv[1], "-R") == 0)
        {
           printf("%s, %d %s %d %02d:%02d:%02d +0530",weekday,tm.tm_mday,month,tm.tm_year+1900,tm.tm_hour,tm.tm_min,tm.tm_sec);
        }
   }

    return 0;
}