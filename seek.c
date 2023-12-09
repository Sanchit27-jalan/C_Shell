#include "headers.h"
int directory_ct = 0;
int file_ct = 0;
char **directorypath;
char **filepath;
char *relativepath;

void print(int d_flag, int e_flag, int f_flag, char *target, char *path)
{
    //printf("%s\n", path);
    //printf("%s\n", target);
    struct dirent *d;
    DIR *dh = opendir(path);
    if (dh == NULL)
    {
        printf("No such directory exists.");
        return;
    }
    while ((d = readdir(dh)) != NULL)
    {
        // printf("%s\n",d->d_name);
        char pathnew[3000] = {'\0'};
        strcpy(pathnew, path);
        char arr[2] = "/";
        strcat(pathnew, arr);
        strcat(pathnew, d->d_name);
        if (d->d_name[0] == '.')
        {
            continue;
        }
        struct stat filetype;
        //printf("%s\n",pathnew);
        stat(pathnew, &filetype);

        // if (strcmp(d->d_name, "src") == 0)
        // {
        //     printf("%d\n", filetype.st_mode);
        // }
        if (S_ISDIR(filetype.st_mode))
        {
            if (strcmp(d->d_name, target) == 0)
            {
                strcpy(directorypath[directory_ct], pathnew);
                directory_ct++;
            }
            //printf("%s\n", pathnew);
            print(d_flag, e_flag, f_flag, target, pathnew);
        }
        else if (S_ISREG(filetype.st_mode))
        {
            char tempname[3000];
            strcpy(tempname, d->d_name);
            char *dot = strrchr(tempname, '.'); // Find the last dot in the filename
            if (dot != NULL)
            {
                *dot = '\0'; // Null-terminate the string at the dot position
            }
            if (strcmp(target, tempname) == 0)
            {
                char pathnew1[300];
                strcpy(pathnew1, path);
                strcat(pathnew1, "/");
                strcat(pathnew1, d->d_name);
                strcpy(filepath[file_ct], pathnew1);
                file_ct++;
            }
        }
    }
    // seek_last(d_flag,e_flag,f_flag);
    return;
}

void seek_last(int d_flag, int e_flag, int f_flag,char *path)
{
    if (d_flag == 1 && e_flag == 1)
    {
        if (directory_ct > 1)
        {
            printf("Greater than 1 directory\n");
        }
        else if (directory_ct == 0)
        {
            printf("No matches found\n");
        }
        else
        {
            if (access(directorypath[0], X_OK) != 0)
            {
                printf("Missing permissions for task!\n");
            }
            printf("\033[0;34m");
            char *substring = strstr(directorypath[0], path);
            printf(".%s\n", substring + strlen(path));
            //printf("%s\n", directorypath[0]);
            printf("\033[0m");
            chdir(directorypath[0]);
            strcpy(prevdir, curdir);
        }
    }
    else if (d_flag == 1 && e_flag == 0)
    {
        if (directory_ct == 0)
        {
            printf("No match found!\n");
            return;
        }
        printf("\033[0;34m");
        for (int i = 0; i < directory_ct; i++)
        {
            char *substring = strstr(directorypath[i], path);
            printf(".%s\n", substring + strlen(path));
            //printf("%s\n", directorypath[i]);
        }
        printf("\033[0m");
    }
    else if (d_flag == 0 && f_flag == 0 && e_flag == 0)
    {
        if (directory_ct == 0 && file_ct == 0)
        {
            printf("No match found!\n");
            return;
        }
        printf("\033[0;34m");
        for (int i = 0; i < directory_ct; i++)
        {
            char *substring = strstr(directorypath[i], path);
            printf(".%s\n", substring + strlen(path));
        }
        printf("\033[0m");
        printf("\033[0;32m");
        for (int i = 0; i < file_ct; i++)
        {
            char *substring = strstr(filepath[i], path);
            printf(".%s\n", substring + strlen(path));
        }
        printf("\033[0m");
    }
    else if (f_flag == 1 && e_flag == 0)
    {
        if (file_ct == 0)
        {
            printf("No match found!\n");
            return;
        }
        printf("\033[0;32m");
        for (int i = 0; i < file_ct; i++)
        {
            char *substring = strstr(filepath[i], path);
            printf(".%s\n", substring + strlen(path));
        }
        printf("\033[0m");
    }
    else if (d_flag == 0 && f_flag == 0 && e_flag == 1)
    {
        if (directory_ct == 0 && file_ct == 1)
        {
            printf("\033[0;32m");
            char *substring = strstr(filepath[0], path);
            printf(".%s\n", substring + strlen(path));
            printf("\033[0m");
            if (access(filepath[0], R_OK) != 0)
            {
                printf("Missing permissions for task!\n");
                return;
            }
            FILE *file = fopen(filepath[0], "r");
            char buffer[1024];
            while (fgets(buffer, sizeof(buffer), file) != NULL)
            {
                printf("%s", buffer);
            }

            fclose(file);
        }
        else if (directory_ct == 1 && file_ct == 0)
        {
            if (access(directorypath[0], X_OK) != 0)
            {
                printf("Missing permissions for task!");
            }
            printf("\033[0;34m");
            char *substring = strstr(directorypath[0], path);
            printf(".%s\n", substring + strlen(path));
            printf("\033[0m");
            chdir(directorypath[0]);
            strcpy(prevdir, curdir);
        }
        else
        {
            printf("No matches found!\n");
        }
    }
    else
    {
        if (file_ct > 1)
        {
            printf("Greater than 1 files\n");
        }
        else if (file_ct == 0)
        {
            printf("No matches found\n");
        }
        else
        {
            //printf("yes\n");
            printf("\033[0;32m");
            char *substring = strstr(filepath[0], path);
            printf(".%s\n", substring + strlen(path));
            printf("\033[0m");
            if (access(filepath[0], R_OK) != 0)
            {
                printf("Missing permissions for task!\n");
                return;
            }
            FILE *file = fopen(filepath[0], "r");
            char buffer[1024];
            while (fgets(buffer, sizeof(buffer), file) != NULL)
            {
                printf("%s", buffer);
            }

            fclose(file);
        }

        // e and f flag
    }
    return;
}

void seek(char *command)
{
    // printf("seek function inside\n");
    directorypath = malloc(sizeof(char *) * 100);
    filepath = malloc(sizeof(char *) * 100);
    for (int i = 0; i < 100; i++)
    {
        directorypath[i] = malloc(sizeof(char) * 1000);
        filepath[i] = malloc(sizeof(char) * 1000);
    }
    char delimiter[] = " ";
    char *tokens[7];
    for (int i = 0; i < 7; i++)
    {
        tokens[i] = NULL;
    }
    int token_count = 0;
    char *target;
    char *path;
    char *token = strtok(command, delimiter);
    int d = 0;
    int e = 0;
    int f = 0;
    while (token != NULL && token_count < 7)
    {
        tokens[token_count] = strdup(token);
        token_count++;
        token = strtok(NULL, delimiter);
    }
    // for(int i=0;i<token_count;i++)
    // {
    //     printf("%s\n",tokens[i]);
    // }
    // token_count=token_count-2;
    if (token_count >= 5 && tokens[1][0] == '-' && tokens[2][0] == '-' && tokens[3][0] == '-')
    {
        printf("Invalid flags!.\n");
        return;
    }
    else if (token_count >= 4)
    {
        if ((tokens[1][1] == 'd' && tokens[2][1] == 'f') || (tokens[1][1] == 'f' && tokens[2][1] == 'd'))
        {
            printf("Invalid flags!.\n");
            return;
        }
        else if ((tokens[1][1] == 'e' && tokens[2][1] == 'd') || (tokens[1][1] == 'd' && tokens[2][1] == 'e'))
        {
            target = strdup(tokens[3]);
            if (tokens[4] == NULL || tokens[4][0] == ' ')
            {
                path = strdup(curdir);
            }
            else
            {
                path = strdup(tokens[4]);
            }
            print(1, 1, 0, target, path);
            seek_last(1, 1, 0,path);
            // call e and d flags
        }
        else if ((tokens[1][1] == 'e' && tokens[2][1] == 'f') || (tokens[1][1] == 'f' && tokens[2][1] == 'e'))
        {
            target = strdup(tokens[3]);
            if (tokens[4] == NULL || tokens[4][0] == ' ')
            {
                path = strdup(curdir);
            }
            else
            {
                path = strdup(tokens[4]);
            }
            print(0, 1, 1, target, path);
            seek_last(0, 1, 1,path);
            // call e and f flags
        }
    }
    else if (token_count >= 3 && tokens[1][0] == '-')
    {
        if (tokens[1][1] == 'd')
        {
            target = strdup(tokens[2]);
            if (tokens[3] == NULL || tokens[3][0] == ' ')
            {
                path = strdup(curdir);
            }
            else
            {
                path = strdup(tokens[3]);
            }
            print(1, 0, 0, target, path);
            seek_last(1, 0, 0,path);
            // call d flag
        }
        else if (tokens[1][1] == 'e')
        {
            target = strdup(tokens[2]);
            if (tokens[3] == NULL || tokens[3][0] == ' ')
            {
                path = strdup(curdir);
            }
            else
            {
                path = strdup(tokens[3]);
            }
            print(0, 1, 0, target, path);
            seek_last(0, 1, 0,path);
            // call e flag
        }
        else if (tokens[1][1] == 'f')
        {
            target = strdup(tokens[2]);
            if (tokens[3] == NULL || tokens[3][0] == ' ')
            {

                path = strdup(curdir);
            }
            else
            {
                path = strdup(tokens[3]);
            }
            print(0, 0, 1, target, path);
            seek_last(0, 0, 1,path);
            // call f flag
        }
    }
    else
    {
        target = strdup(tokens[1]);
        // printf("!!!\n");
        if (tokens[2] == NULL || tokens[2][0] == ' ')
        {

            path = strdup(curdir);
        }
        else
        {
            path = strdup(tokens[2]);
        }
        print(0, 0, 0, target, path);
        seek_last(0, 0, 0,path);
    }
    // printf("%s\n",path);
    directory_ct = 0;
    file_ct = 0;
    for (int i = 0; i < 100; i++)
    {
        free(directorypath[i]);
        free(filepath[i]);
    }
}