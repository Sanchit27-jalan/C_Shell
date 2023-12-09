#include "headers.h"

void ctrl_c(int signal)
{
    if (fgpid == 0)
    {
        // putchar('\n');
        printf("\n");
        // prompt();
        return;
    }
    int result = kill(fgpid, SIGINT);
    if (result != 0)
    {
        perror("kill");
    }
    // putchar('\n');
}

void ctrl_d(int signal)
{
    struct processes *temp = activity->next;
    while (temp != NULL)
    {
        int result = kill(temp->pid, SIGKILL);
        if (result != 0)
        {
            perror("kill");
        }
        temp = temp->next;
    }
    exit(1);
}

void ctrl_z(int signal)
{
    //printf("%s\n",fgname);
    //printf("hi!!!!!!!!\n");
    if (fgpid == 0)
    {
        // putchar('\n');
        // printf("\n");
        // prompt();
        return;
    }
    else
    {
        //printf("%s\n",fgname);
        int result = kill(fgpid, SIGTSTP);
        if (result != 0)
        {
            perror("kill");
        }
        int result2 = kill(fgpid, SIGSTOP);
        if (result2 != 0)
        {
            perror("kill");
        }
        struct processes *temp = header;
        while ((temp->next) != NULL)
        {
            temp = temp->next;
        }
        struct processes *new = malloc(sizeof(struct processes));
        new->pid = fgpid;
        new->next = NULL;
        //printf("wtf\n");
        strcpy(new->processname, fgname);
        temp->next = new;   
        struct processes *temp2 = activity;
        struct processes *temp3 = activity->next;
        struct processes *new2 = malloc(sizeof(struct processes));
        new2->pid = fgpid;
        new2->next = NULL;
        strcpy(new2->processname, fgname);
        while (temp2 != NULL)
        {
            if (temp2->pid == -1)
            {
                if (temp3 == NULL)
                {
                    temp2->next = new2;
                    return;
                }
                else if (temp3->pid > fgpid)
                {
                    temp2->next = new2;
                    new2->next = temp3;
                    return;
                }
                else
                {
                    temp2 = temp2->next;
                    temp3 = temp3->next;
                }
            }
            else if (temp3 == NULL)
            {
                temp2->next = new2;
                return;
            }
            else if (temp3->pid < fgpid && temp2->pid < fgpid)
            {
                temp3 = temp3->next;
                temp2 = temp2->next;
            }
            else if (temp3->pid > fgpid && temp2->pid < fgpid)
            {
                temp2->next = new2;
                new2->next = temp3;
                return;
            }
        }
    }
}

void signal1(char *command)
{
    //printf("%s\n",command);
    //printf("Wtf\n");
    const char *s = " ";
    char *tok;
    char *pid1;
    char *signno1;
    tok = strtok(command, s);
    pid1 = strtok(0, s);
    signno1 = strtok(0, s);
    //printf("%s %s\n", pid1, signno1);
    struct processes *t = activity->next;
    int pid2 = atoi(pid1);
    pid_t pid = pid2;
    int sig_no = atoi(signno1);
    sig_no = sig_no % 32;
    int flag = 0;
    while (t != NULL)
    {
        if (t->pid == pid2)
        {
            flag = 1;
            break;
        }
        t = t->next;
    }
    //printf("%d %d \n",pid,sig_no);
    if (flag == 0)
    {
        printf("No such process found\n");
        return;
    }
    // printf("wtf\n");
    //printf("%d %d \n",pid,sig_no);
    int result = kill(pid, sig_no);
    if (result != 0)
    {
        perror("kill");
    }
    //printf("Signal finished\n");
}
