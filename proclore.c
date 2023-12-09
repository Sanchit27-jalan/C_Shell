#include "headers.h"

void proclore(char *command)
{
    char status;
    int num;
    if (command != NULL)
    {
        num = atoi(command);
    }
    else
    {
        num = getpid();
    }
    int process_grp;
    int tpgid;
    // printf("pid : %d\n", num);
    char stat_path[1000] = {'\0'};
    sprintf(stat_path, "/proc/%d/stat", num);
    //strcat(stat_path, "/stat");
    // printf("%s\n", stat_path);
    int vm=0;
    FILE *file = fopen(stat_path, "r");
    if (file != NULL)
    {
        char *stat_file = (char *)calloc(sizeof(char), 5000);
        while (fgets(stat_file, 5000, file))
        {
            char list[52][30];
            for (int i = 0; i < 52; i++)
            {
                for (int j = 0; j < 30; j++)
                {
                    list[i][j] = '\0';
                }
            }
            int total = 0;
            char *delimiter = " :\t\n\0";
            char *token = strtok(stat_file, delimiter);
            while (token != NULL)
            {
                strcpy(list[total++],token);
                token = strtok(NULL, delimiter);
            }
            status = list[2][0];
            process_grp = atoi(list[4]);
            tpgid = atoi(list[7]);
            vm=atoi(list[22]);
            fclose(file);
        }
    }
    else
    {
        printf("Process with %d is not valid", num);
        return;
    }
    char fgbg;
    if (process_grp == tpgid)
    {
        fgbg = '+';
    }
    else
    {
        fgbg = ' ';
    }
    char executable_path[4096];
    char exec_path[1000] = {'\0'};
    sprintf(exec_path, "/proc/%d", num);
    strcat(exec_path, "/exe");
    ssize_t n_bytes = readlink(exec_path, executable_path, sizeof(executable_path) - 1);
    executable_path[n_bytes] = '\0';
    // executable path done
    printf("pid : %d\n", num);
    printf("process status : %c%c\n", status, fgbg);
    printf("Process group : %d\n", process_grp);
    printf("Virtual Memory : %d KB\n", vm/1024);
    printf("Executable path : %s\n", executable_path);
}
