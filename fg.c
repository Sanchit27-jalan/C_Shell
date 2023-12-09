#include "headers.h"

void foreground_calling(char *input)
{
    //printf("%s\n",input);
    struct timespec start, end;
    // printf("%ld   ",start.tv_sec);
    clock_gettime(CLOCK_REALTIME, &start);
    pid_t pid = fork();
    if (pid == 0)
    {
        char *name[] = {
            "/bin/bash",
            "-c",
            "sanchit",
            NULL};
        // strcpy(name[2],input);
        //printf("%s\n",fgname);
        name[2] = strdup(input);
        execvp(name[0], name);
    }
    else
    {
        // if (feof(stdin)){
        //     ctrl_d();
        // }
        fgpid=pid;
        strcpy(fgname,input);
        int status;
        int x=waitpid(pid,&status,WUNTRACED);

        if (WIFEXITED(status))
        {
            // printf("Child process exited normally\n");
            clock_gettime(CLOCK_REALTIME, &end);
            // printf("%ld   ",start.tv_sec);
            // printf("%ld\n",end.tv_sec);
            cpu_time_used = end.tv_sec - start.tv_sec;
            if (cpu_time_used > 2)
            {
                flagtime = 1;
            }
        }
    }
}
