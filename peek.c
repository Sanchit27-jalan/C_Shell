#include "headers.h"

int compareStrings(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}

void aflag(char *path)
{
    DIR *dir;
    if (path == NULL)
    {
        dir = opendir(".");
    }
    else
    {
        dir = opendir(path);
    }
    if (dir == NULL) {
        perror("opendir");
        return;
    }
    struct dirent *entry;
    int maxEntries = 1000;
    char *entries[maxEntries];
    int entryCount = 0;

    while ((entry = readdir(dir)) != NULL)
    {
        if (entryCount < maxEntries)
        {
            entries[entryCount] = strdup(entry->d_name);
            entryCount++;
        }
        else
        {
            fprintf(stderr, "Max entries reached\n");
            break;
        }
    }

    closedir(dir);

    qsort(entries, entryCount, sizeof(char *), compareStrings);

    for (int i = 0; i < entryCount; i++)
    {
        printf("%s\n", entries[i]);
        free(entries[i]); // Free the memory allocated by strdup
    }
}

void print_permissions(mode_t mode)
{
    printf((S_ISDIR(mode)) ? "d" : "-");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
}

void lflag(char *path)
{
    DIR *dir;
    if (path == NULL)
    {
        dir = opendir(".");
    }
    else
    {
        dir = opendir(path);
    }
    if (dir == NULL) {
        perror("opendir");
        return;
    }
    struct dirent *entry;
    struct stat file_stat;
    struct passwd *pw;
    struct group *grp;
    struct tm *timeinfo;
    int maxEntries = 1000;
    char *entries[maxEntries];
    int entryCount = 0;

    while ((entry = readdir(dir)) != NULL)
    {
        if (entryCount < maxEntries)
        {
            entries[entryCount] = strdup(entry->d_name);
            entryCount++;
        }
        else
        {
            fprintf(stderr, "Max entries reached\n");
            break;
        }
    }

    closedir(dir);

    qsort(entries, entryCount, sizeof(char *), compareStrings);
    int totalBlocks = 0;
    for (int i = 0; i < entryCount; i++)
    {
        if (entries[i][0] != '.')
        {
            char filePath[1024];
            snprintf(filePath, sizeof(filePath), "%s/%s", path, entries[i]);
            if (filePath[0] == '(')
            {
                int i;
                for (i = 0; i < strlen(filePath) - 7; i++)
                {
                    filePath[i] = filePath[i + 7];
                }
                filePath[i] = '\0';
            }
            // printf("%s\n",filePath);
            if (stat(filePath, &file_stat) == -1)
            {
                perror("stat");
                continue;
            }
            totalBlocks += file_stat.st_blocks;
        }
    }
    printf("total %d\n", totalBlocks);
    for (int i = 0; i < entryCount; i++)
    {
        if (entries[i][0] != '.')
        {
            //printf("%s\n",path);
            char filePath[1024];
            snprintf(filePath, sizeof(filePath), "%s/%s", path, entries[i]);
            if (filePath[0] == '(')
            {
                int i;
                for (i = 0; i < strlen(filePath) - 7; i++)
                {
                    filePath[i] = filePath[i + 7];
                }
                filePath[i] = '\0';
            }
            // printf("%s\n",filePath);
            if (stat(filePath, &file_stat) == -1)
            {
                perror("stat");
                continue;
            }
            print_permissions(file_stat.st_mode);
            printf(" %3d ", file_stat.st_nlink); //assumption hards links are maximum 999 to have formatting 
            pw = getpwuid(file_stat.st_uid);
            grp = getgrgid(file_stat.st_gid);
            printf(" %s %s ", pw->pw_name, grp->gr_name);

            printf("%8lld ", file_stat.st_size);

            timeinfo = localtime(&file_stat.st_mtime);
            for (int i = 4; i < strlen(asctime(timeinfo)) - 9; i++)
            {
                printf("%c", asctime(timeinfo)[i]);
            }

            printf(" %s\n", entries[i]);
        }
        free(entries[i]);
    }
}

void bothflags(char *path)
{
    DIR *dir;
    if (path == NULL)
    {
        dir = opendir(".");
    }
    else
    {
        dir = opendir(path);
    }
    if (dir == NULL) {
        perror("opendir");
        return;
    }
    struct dirent *entry;
    struct stat file_stat;
    struct passwd *pw;
    struct group *grp;
    struct tm *timeinfo;
    int maxEntries = 1000;
    char *entries[maxEntries];
    int entryCount = 0;

    while ((entry = readdir(dir)) != NULL)
    {
        if (entryCount < maxEntries)
        {
            entries[entryCount] = strdup(entry->d_name);
            entryCount++;
        }
        else
        {
            fprintf(stderr, "Max entries reached\n");
            break;
        }
    }

    closedir(dir);
    //printf("%s\n",entries[0]);
    qsort(entries, entryCount, sizeof(char *), compareStrings);
    int totalBlocks = 0;
    for (int i = 0; i < entryCount; i++)
    {
        char filePath[1024];
        snprintf(filePath, sizeof(filePath), "%s/%s", path, entries[i]);
        if (filePath[0] == '(')
        {
            int i;
            for (i = 0; i < strlen(filePath) - 7; i++)
            {
                filePath[i] = filePath[i + 7];
            }
            filePath[i] = '\0';
        }
        //printf("%s\n",filePath);
        if (stat(filePath, &file_stat) == -1)
        {
            perror("stat");
            continue;
        }
        totalBlocks += file_stat.st_blocks;
    }
    printf("total %d\n", totalBlocks);
    for (int i = 0; i < entryCount; i++)
    {
        char filePath[1024];
        snprintf(filePath, sizeof(filePath), "%s/%s", path, entries[i]);
        if (filePath[0] == '(')
        {
            int i;
            for (i = 0; i < strlen(filePath) - 7; i++)
            {
                filePath[i] = filePath[i + 7];
            }
            filePath[i] = '\0';
        }
        //printf("!!!!!!!%s\n",filePath);
        if (stat(filePath, &file_stat) == -1)
        {
            perror("stat");
            continue;
        }
        print_permissions(file_stat.st_mode);
        printf(" %3d ", file_stat.st_nlink);

        pw = getpwuid(file_stat.st_uid);
        grp = getgrgid(file_stat.st_gid);
        printf(" %s %s ", pw->pw_name, grp->gr_name);

        printf("%8lld ", file_stat.st_size);

        timeinfo = localtime(&file_stat.st_mtime);
        for (int i = 4; i < strlen(asctime(timeinfo)) - 9; i++)
        {
            printf("%c", asctime(timeinfo)[i]);
        }

        printf(" %s\n", entries[i]);
        free(entries[i]);
    }
}
void normal(char *path)
{
    //printf("%s\n",path);
    DIR *dir;
    if (path == NULL)
    {
        dir = opendir(".");
    }
    else
    {
        dir = opendir(path);
    }
    if (dir == NULL) {
        perror("opendir");
        return;
    }
    struct dirent *entry;
    int maxEntries = 1000;
    char *entries[maxEntries];
    int entryCount = 0;

    while ((entry = readdir(dir)) != NULL)
    {
        if (entryCount < maxEntries)
        {
            entries[entryCount] = strdup(entry->d_name);
            entryCount++;
        }
        else
        {
            fprintf(stderr, "Max entries reached\n");
            break;
        }
    }

    closedir(dir);

    qsort(entries, entryCount, sizeof(char *), compareStrings);

    for (int i = 0; i < entryCount; i++)
    {
        if (entries[i][0] != '.')
        {
            printf("%s\n", entries[i]);
        }
        free(entries[i]);
    }
}
void peekk(char *command)
{
    const char *s = " ";
    char *tok;
    char *tok2;
    char *path;
    tok = strtok(command, s);
    tok = strtok(0, s);
    if (tok == NULL)
    {
        normal(NULL);
        return;
    }
    if (strcmp(tok,"-la")==0 || strcmp(tok,"-al")==0)
    {
        // call function doing both
        path = strtok(0, s);
        bothflags(path);
    }
    else if (tok[1] == 'a' && tok[0]=='-')
    {
        tok2 = strtok(0, s);
        if (tok2 == NULL)
        {
            aflag(tok2);
            return;
        }
        if (tok2[0] != '-')
        {
            // call -a flag
            path = tok2;
            aflag(path);
        }
        else
        {
            // call function doing both
            path = strtok(0, s);
            bothflags(path);
        }
    }
    else if (tok[1] == 'l' && tok[0]=='-')
    {
        tok2 = strtok(0, s);
        if (tok2 == NULL)
        {
            lflag(tok2);
            return;
        }
        if (tok2[0] != '-')
        {
            // call -l flag
            path = tok2;
            lflag(path);
        }
        else
        {
            // call function doing both
            path = strtok(0, s);
            bothflags(path);
        }
    }
    else
    {
        // normal ls flag
        path = tok;
        normal(path);
    }
    //printf("%s\n",path);
}