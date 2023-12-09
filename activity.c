#include "headers.h"

void act()
{
    struct processes *t = activity->next;
    while (t != NULL)
    {
        pid_t pid = t->pid;
        char stat_filepath[256];
        snprintf(stat_filepath, sizeof(stat_filepath), "/proc/%d/stat", pid);

        FILE *stat_file = fopen(stat_filepath, "r");
        if (stat_file == NULL)
        {
            //perror("fopen");
            t=t->next;
            continue;
        }
        char status;
        fscanf(stat_file, "%*d %*s %c", &status);
        //printf("%c\n",status);
        fclose(stat_file);

        if (status == 'T')
        {
            printf("%d: %s - Stopped.\n", pid,t->processname);
        }
        else
        {
            printf("%d: %s - Running.\n", pid,t->processname);
        }
        t = t->next;
    }
}
