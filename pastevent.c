#include "headers.h"

char *removingspacess(char *tok, int len)
{
    char *new = malloc(sizeof(char) * len);
    int filled = 0;
    for (int i = 0; i < len; i++)
    {
        if (tok[i] == ' ')
        {
            if (filled == 0)
            {
                continue;
            }
            else if (tok[i - 1] == ' ')
            {
                continue;
            }
            else
            {
                new[filled++] = ' ';
            }
        }
        else
        {
            new[filled++] = tok[i];
        }
    }
    if (new[filled - 1] == ' ')
    {
        new[filled - 1] = '\0';
    }
    else
    {
        new[filled] = '\0';
    }
    return new;
}
void purge(char path[])
{
    FILE *fp;
    fp = fopen(path, "w");
    fclose(fp);
}
void openfile(char path[])
{
    FILE *fp;
    fp = fopen(path, "r");
    int nline = 0;
    char str[15][10000];
    char line[10000] = {'\0'};
    while (fgets(line, sizeof(line), fp) != NULL && nline != 15)
    {
        // fgets(line, sizeof(line), fp);
        // printf("Line: %s", line);
        strcpy(str[nline], line);
        nline++;
    }
    for (int i = nline - 1; i >= 0; i--)
    {
        printf("%s", str[i]);
    }
    fclose(fp);
}
void execute(char path[], char *number, int len)
{
    FILE *fp;
    fp = fopen(path, "r");
    int x = 0;
    if (len == 1)
    {
        x = (int)(number[0]) - 48;
    }
    else
    {
        x = 10 + (int)number[1] - 48;
    }
    char temp[10000];
    for (int i = 0; i < x; i++)
    {
        fgets(temp, sizeof(temp), fp);
    }
    temp[strlen(temp) - 1] = '\0';
    // printf("%s\n",line);
    // int aa=process_execution(line);
    char *arr = calloc(1000, sizeof(char));
    int filled = 0;
    int flag = 0;
    for (int i = 0; i < strlen(temp); i++)
    {
        if (temp[i] != '&' && temp[i] != ';')
        {
            arr[filled++] = temp[i];
        }
        else if (temp[i] == '&')
        {
            // background call with arr
            arr = removingspacess(arr, strlen(arr));
            background_calling(arr);
            // printf("%s\n", arr);
            free(arr);
            filled = 0;
            arr = calloc(1000, sizeof(char));
        }
        else if (temp[i] == ';')
        {
            arr = removingspacess(arr, strlen(arr));
            int y = pipe1(arr);
            if (y == -1)
            {
                exit(1);
            }
            // printf("%s\n", arr);
            free(arr);
            filled = 0;
            arr = calloc(1000, sizeof(char));
        }
    }
    arr = removingspacess(arr, strlen(arr)); // len 0 condition add

    int y = pipe1(arr);
    if (y == -1)
    {
        exit(1);
    }

    fclose(fp);
}
void pexec(char *command)
{
    char filename[1000] = "/pastevent.txt";
    char filepath[10000];
    strcpy(filepath, homedir);
    strcat(filepath, filename);
    char copy[1000];
    strcpy(copy, command);
    const char *s = " ";
    char *tok;
    char *saveptr;
    tok = strtok_r(command, s, &saveptr);
    // printf("%s\n",tok);
    tok = strtok_r(NULL, s, &saveptr);
    // printf("%s\n",tok);
    if (tok != NULL && strcmp(tok, "execute") == 0)
    {
        tok = strtok_r(NULL, s, &saveptr);
        execute(filepath, tok, strlen(tok));
        // call execute
        return;
    }
    else if (tok != NULL && strcmp(tok, "purge") == 0)
    {
        purge(filepath);
        // call purge;
        return;
    }
    else if (tok == NULL)
    {
        openfile(filepath);
        // call to open file
    }
}
void pastevent(char *command)
{
    // printf("%s\n",command);
    char filename[1000] = "/pastevent.txt";
    char filepath[10000];
    strcpy(filepath, homedir);
    strcat(filepath, filename);
    // printf("%s\n",copy);
    FILE *fp;
    // printf("%s\n",filepath);
    fp = fopen(filepath, "r");
    char line[10000] = {'\0'};
    // printf("%s\n",line);
    fgets(line, sizeof(line), fp);
    line[strlen(line) - 1] = '\0';
    if (strcmp(line, command) == 0)
    {
        return;
    }
    int nline = 2;
    char str[15][10000];
    char sy = '\n';
    // strcat(str,copy);
    strcat(command, &sy);
    strcpy(str[0], command);
    // strcat(str,line);
    strcat(line, &sy);
    strcpy(str[1], line);
    // printf("%s",str);
    while (fgets(line, sizeof(line), fp) != NULL && nline != 15)
    {
        // fgets(line, sizeof(line), fp);
        // printf("Line: %s", line);
        strcpy(str[nline], line);
        nline++;
    }
    // printf("%s",str);
    //  for(int i=0;i<nline;i++){
    //      printf("%s",str[i]);
    //  }
    fclose(fp);
    FILE *fp1;
    fp1 = fopen(filepath, "w");
    for (int i = 0; i < nline; i++)
    {
        fprintf(fp1, "%s", str[i]);
    }
    // fprintf(fp1, "%s\n", str);
    fclose(fp1);
}
