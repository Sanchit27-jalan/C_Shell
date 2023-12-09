#include "headers.h"

char curdir[300];
char prevdir[300];
char homedir[300];
int flagtime;
char *timestr;
struct processes *header;
int cpu_time_used;
struct processes *activity;
pid_t fgpid;
char *fgname;

char *removingspaces(char *tok, int len)
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

int main()
{
    header = (struct processes *)malloc(sizeof(struct processes));
    header->next = NULL;
    header->pid = -1;
    strcpy(header->processname, "random");
    // Keep accepting commands
    getcwd(homedir, 300);
    getcwd(prevdir, 300);
    getcwd(curdir, 300);
    flagtime = 0;
    cpu_time_used = 0;
    timestr = calloc(300, sizeof(char));
    activity = (struct processes *)malloc(sizeof(struct processes));
    activity->next = NULL;
    activity->pid = -1;
    strcpy(activity->processname, "random");
    while (1)
    {
        fgpid = 0;
        fgname = calloc(1000, sizeof(char));
        struct processes *tempp = header->next;
        struct processes *before = header;
        // printf("!!!!!!!!!!!!!!!!!\n");
        while (tempp != NULL)
        {
            int status;
            pid_t result = waitpid(tempp->pid, &status, WNOHANG);
            if (result > 0)
            {
                if (WIFEXITED(status))
                {
                    if (!WEXITSTATUS(status))
                    {
                        printf("%s exited normally (%d)\n", tempp->processname, tempp->pid);
                    }
                    else
                    {
                        printf("%s exited abruptly (%d)\n", tempp->processname, tempp->pid);
                    }
                }
            }
            else
            {
                tempp = tempp->next;
                before = before->next;
            }
        }
        if (signal(SIGINT, ctrl_c) == SIG_ERR)
        {
            perror("signal");
        }
        if (signal(SIGQUIT, ctrl_d) == SIG_ERR)
        {
            perror("signal");
        }
        if (signal(SIGTSTP, ctrl_z) == SIG_ERR)
        {
            perror("signal");
        }
        // Print appropriate prompt with username, systemname and directory before accepting input
        prompt();
        char input[4096] = {'\0'};
        fgets(input, sizeof(input), stdin);
        if (input[0] == '\0')
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
        char temp[strlen(input)];
        for (int i = 0; i < strlen(input) - 1; i++)
        {
            temp[i] = input[i];
        }
        temp[strlen(input) - 1] = '\0';
        // printf("%s\n",temp);
        char copy[strlen(input)];
        strcpy(copy, temp);
        char p[100] = "pastevents";
        if (strstr(copy, p) == NULL)
        {
            pastevent(copy);
        }
        // printf("%s\n",temp);
        char *arr = calloc(1000, sizeof(char));
        int filled = 0;
        int flag = 0;
        // printf("%s\n",temp);
        for (int i = 0; i < strlen(temp); i++)
        {
            if (temp[i] != '&' && temp[i] != ';')
            {
                arr[filled++] = temp[i];
            }
            else if (temp[i] == '&')
            {
                // background call with arr
                arr = removingspaces(arr, strlen(arr));
                background_calling(arr);
                // printf("%s\n", arr);
                free(arr);
                filled = 0;
                arr = calloc(1000, sizeof(char));
            }
            else if (temp[i] == ';')
            {
                arr = removingspaces(arr, strlen(arr));
                int x = pipe1(arr);
                if (x == -1)
                {
                    flag = 1;
                    break;
                }
                // printf("%s\n", arr);
                free(arr);
                filled = 0;
                arr = calloc(1000, sizeof(char));
            }
        }
        // printf("%s\n",arr);
        arr = removingspaces(arr, strlen(arr));
        if (strlen(arr) == 0)
        {
            continue;
        }
        int x = pipe1(arr);
        if (x == -1)
        {
            flag = 1;
            break;
        }
        if (flag == 1)
        {
            break;
        }
        if (flagtime == 1)
        {
            strcpy(timestr, temp);
        }
        // printf("%s\n", arr);
    }
}
