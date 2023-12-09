#include "headers.h"

void warpp(char *command)
{
    const char *s = " ";
    char *tok;
    tok = strtok(command, s);
    tok = strtok(0, s);
    while (tok != 0)
    {
        // printf(" %s\n", tok);
        if (tok[0] == '~' && strlen(tok) == 1)
        {
            // printf("Home Directory is: %s\n",homedir);
            int x = chdir(homedir);
            if (x != 0)
            {
                printf("Error directory does not exist\n");
            }
            strcpy(prevdir, curdir);
            strcpy(curdir, homedir);
            printf("%s\n", curdir);
        }
        else if (tok[0] == '.' && tok[1] == '.' && strlen(tok) == 2)
        {
            int x = chdir("..");
            if (x != 0)
            {
                printf("Error directory does not exist\n");
            }
            strcpy(prevdir, curdir);
            getcwd(curdir, 300);
            printf("%s\n", curdir);
        }
        else if (tok[0] == '.' && strlen(tok) == 1)
        {
            int x = chdir(".");
            if (x != 0)
            {
                printf("Error directory does not exist\n");
            }
            strcpy(prevdir, curdir);
            getcwd(curdir, 300);
            printf("%s\n", curdir);
        }
        else if (tok[0] == '-')
        {
            int x = chdir(prevdir);
            if (x != 0)
            {
                printf("Error directory does not exist\n");
            }
            char temp[300];
            strcpy(temp, prevdir);
            strcpy(prevdir, curdir);
            strcpy(curdir, temp);
            printf("%s\n", curdir);
        }
        else
        {
            int x = chdir(tok);
            if (x == 0)
            {
                strcpy(prevdir, curdir);
                getcwd(curdir, 300);
                printf("%s\n", curdir);
            }
            else
            {
                printf("Error : directory does not exist\n");
            }
        }
        tok = strtok(0, s);
    }
}