#include "headers.h"

void bgtofg(char *command)
{
    char delimiters[] = " ";
    char *token;
    char *saveptr;
    token = strtok_r(command, delimiters, &saveptr);
    token = strtok_r(NULL, delimiters, &saveptr);
    int pid = atoi(token);
    struct processes *temp = activity->next;
    char *processname = calloc(1000, sizeof(char));
    int flag = 0;
    while (temp != NULL)
    {
        if (temp->pid == pid)
        {
            strcpy(processname, temp->processname);
            flag = 1;
            break;
        }
        temp = temp->next;
    }
    if (flag == 0)
    {
        printf("No such process exist\n");
        return;
    }
    int terminal_fd = open("/dev/tty", O_RDWR);

    if (terminal_fd == -1)
    {
        perror("open");
    }
    pid_t pgid = getpgid(pid);

    if (pgid == -1)
    {
        perror("getpgid");
    }

    // Set the PGID as the foreground process group for the terminal.
    if (tcsetpgrp(terminal_fd, pgid) == -1)
    {
        perror("tcsetpgrp");
    }
    int status;
    waitpid(pid, &status, 0);

    // Reset the foreground process group to the shell.
    if (tcsetpgrp(terminal_fd, getpgrp()) == -1)
    {
        perror("tcsetpgrp");
    }

    close(terminal_fd);
    // int result = kill(pid, SIGKILL);
    // if (result != 0)
    // {
    //     perror("kill");
    // }
    // foreground_calling(processname);
    // if (tcsetpgrp(STDIN_FILENO, pid) == -1) {
    //     perror("tcsetpgrp");
    // }
    // if (tcsetpgrp(STDIN_FILENO, getpgrp()) == -1) {
    //     perror("tcsetpgrp");
    // }
}

void fgtobg(char *command)
{
    char delimiters[] = " ";
    char *token;
    char *saveptr;
    token = strtok_r(command, delimiters, &saveptr);
    token = strtok_r(NULL, delimiters, &saveptr);
    int pid = atoi(token);
    struct processes *temp = activity->next;
    char *processname = calloc(1000, sizeof(char));
    int flag = 0;
    while (temp != NULL)
    {
        if (temp->pid == pid)
        {
            strcpy(processname, temp->processname);
            flag = 1;
            break;
        }
        temp = temp->next;
    }
    if (flag == 0)
    {
        printf("No such process exist\n");
        return;
    }
    int result = kill(pid, SIGCONT);
    if (result != 0)
    {
        perror("kill");
    }
    return;
}
