#include "headers.h"

char *inputname(char *command)
{
    char *inputfilename = calloc(1000, sizeof(char));
    int filled;
    for (int i = 0; i < strlen(command); i++)
    {
        filled = 0;
        if (command[i] == '<')
        {
            int j = i + 1;
            if (command[j] == ' ')
            {
                j++;
            }
            while (command[j] != ' ')
            {
                inputfilename[filled++] = command[j];
                j++;
            }
            break;
        }
    }
    inputfilename[filled] = '\0';
    return inputfilename;
}

char *changecommand(char *command)
{
    for (int i = 0; i < strlen(command); i++)
    {
        if (command[i] == '>' || command[i] == '<')
        {
            command[i] = '\0';
        }
    }
    return command;
}
char *outputname(char *command)
{
    char *inputfilename = calloc(1000, sizeof(char));
    int filled;
    for (int i = 0; i < strlen(command); i++)
    {
        filled = 0;
        if (command[i] == '>')
        {
            int j = i + 1;
            if (command[j] == ' ' || command[j] == '>')
            {
                j++;
            }
            if (command[j] == ' ')
            {
                j++;
            }
            while (command[j] != ' ')
            {
                inputfilename[filled++] = command[j];
                j++;
            }
            break;
        }
    }
    inputfilename[filled] = '\0';
    return inputfilename;
}
int pipe1(char *command)
{
    int n;
    char cmds[100][100];
    int cmdCount = 0;
    int tokenLength = 0;
    for (int i = 0; command[i] != '\0'; i++)
    {
        if (command[i] == '|')
        {
            cmds[cmdCount][tokenLength] = '\0';
            cmdCount++;
            tokenLength = 0;
        }
        else
        {
            cmds[cmdCount][tokenLength] = command[i];
            tokenLength++;
        }
    }
    cmds[cmdCount][tokenLength] = '\0';
    cmdCount++;
    // for(int i=0;i<cmdCount;i++){
    //     printf("%s\n",cmds[i]);
    // }
    if (cmdCount == 1)
    {
        int x = process_execution1(cmds[0]);
        if (x == -1)
        {
            return -1;
        }
    }
    else
    {
        n = cmdCount;
        int pipes[n - 1][2];
        // for(int i=0;i<n;i++){
        //     printf("%s\n",cmds[i]);
        // }
        for (int i = 0; i < n - 1; i++)
        {
            if (pipe(pipes[i]) == -1)
            {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
        }
        // printf("wtf\n");
        int inp = dup(STDIN_FILENO);
        int opt = dup(STDOUT_FILENO);
        // close(pipes[0][0]);
        if (dup2(pipes[0][1], STDOUT_FILENO) == -1)
        {
            // printf("wtf1\n");
            perror("dup2");
            return 0;
        }
        char *inputfilename = calloc(1000, sizeof(char));
        char *outputfilename = calloc(1000, sizeof(char));
        int ip = 0;
        if (strstr(command, "<"))
            ip = 1;
        if (ip == 1)
        {
            inputfilename = inputname(command);
            int fd = open(inputfilename, O_RDONLY);
            if (fd == -1)
            {
                perror("No such input file found!\n");
            }
            if (dup2(fd, STDIN_FILENO) == -1)
            {
                perror("Failed to redirect stdout");
                close(fd); // Close the file descriptor
            }
            // printf("file opened\n");
            close(fd); // Close the file descriptor
        }
        // cmds[0] = changecommand(cmds[0]);
        for(int i=0;i<100;i++)
        {
            if (cmds[0][i] == '>' || cmds[0][i] == '<')
            {
                cmds[0][i] = '\0';
                break;
            }
        }
        process_execution(cmds[0]);
        // printf("%s\n", cmds[0]);
        for (int i = 1; i < n - 1; i++)
        {
            if (dup2(pipes[i - 1][0], STDIN_FILENO) == -1)
            {
                perror("dup2");
                return 0;
            }
            close(pipes[i - 1][0]);
            close(pipes[i - 1][1]);
            if (dup2(pipes[i][1], STDOUT_FILENO) == -1)
            {
                perror("dup2");
                return 0;
            }
            process_execution(cmds[i]);
        }

        if (dup2(pipes[n - 2][0], STDIN_FILENO) == -1)
        {
            perror("dup2");
            return 0;
        }
        close(pipes[n - 2][0]);
        close(pipes[n - 2][1]);
        if (dup2(opt, STDOUT_FILENO) == -1)
        {
            perror("dup2");
            return 0;
        }
        int op = 0;
        if (strstr(command, ">"))
            op = 2;
        if (strstr(command, ">>"))
            op = 1;
        if (op == 1 || op == 2)
        {
            outputfilename = outputname(command);
            if (op == 1)
            {
                int fd = open(outputfilename, O_WRONLY | O_CREAT | O_APPEND, 0644);
                if (fd == -1)
                {
                    perror("Failed to open file");
                }
                if (dup2(fd, STDOUT_FILENO) == -1)
                {
                    perror("Failed to redirect stdout");
                    close(fd); // Close the file descriptor
                }
                // printf("file opened\n");
                close(fd); // Close the file descriptor
            }
            if (op == 2)
            {
                int fdq = open(outputfilename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fdq == -1)
                {
                    perror("Failed to open file");
                }
                if (dup2(fdq, STDOUT_FILENO) == -1)
                {
                    // printf("!!!!!!file opened\n");
                    perror("Failed to redirect stdout");
                    close(fdq); // Close the file descriptor
                }
                // printf("file opened\n");
                close(fdq);
            }
        }
        for(int i=0;i<100;i++)
        {
            if (cmds[n-1][i] == '>' || cmds[n-1][i] == '<')
            {
                cmds[n-1][i] = '\0';
                break;
            }
        }
        process_execution(cmds[n - 1]);
        if (dup2(inp, STDIN_FILENO) == -1)
        {
            perror("dup2");
            return 0;
        }
        if (dup2(opt, STDOUT_FILENO) == -1)
        {
            perror("dup2");
            return 0;
        }
        // if (dup2(op, STDOUT_FILENO) == -1)
        // {
        //     perror("dup2");
        //     return 0;
        // }
        return 0;
    }
    return 0;
}