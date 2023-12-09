#include "headers.h"

// char *removingspacesss(char *tok, int len)
// {
//     char *new = malloc(sizeof(char) * len);
//     int filled = 0;
//     for (int i = 0; i < len; i++)
//     {
//         if (tok[i] == ' ')
//         {
//             if (filled == 0)
//             {
//                 continue;
//             }
//             else if (tok[i - 1] == ' ')
//             {
//                 continue;
//             }
//             else
//             {
//                 new[filled++] = ' ';
//             }
//         }
//         else
//         {
//             new[filled++] = tok[i];
//         }
//     }
//     if (new[filled - 1] == ' ')
//     {
//         new[filled - 1] = '\0';
//     }
//     else
//     {
//         new[filled] = '\0';
//     }
//     return new;
// }
void replacing(int original_stdin, int original_stdout, int flagout, int flagin)
{
    if (flagout == 1 || flagout == 2)
    {
        if (dup2(original_stdout, STDOUT_FILENO) == -1)
        {
            perror("Failed to restore stdout");
        }
    }
    if (flagin == 1)
    {
        if (dup2(original_stdin, STDIN_FILENO) == -1)
        {
            perror("Failed to restore stdin");
        }
    }
    return;
}
int process_execution1(char *command)
{
    //command=removingspacesss(command,strlen(command));
    //printf("%s\n",command);
    int flag = 0;
    int flag2 = 0;
    if (strstr(command, ">>"))
    {
        flag = 1;
    }
    else if (strstr(command, ">"))
    {
        flag = 2;
    }
    if (strstr(command, "<"))
    {
        flag2 = 1;
    }
    char newfilename[1000];
    char inputfile[1000];
    for (int i = 0; i < 1000; i++)
    {
        newfilename[i] = '\0';
        inputfile[i] = '\0';
    }
    for (int i = 0; i < strlen(command); i++)
    {
        if (command[i] == '<')
        {
            int j;
            int filled = 0;
            for (j = i + 1; j < strlen(command); j++)
            {
                if (j == (i + 1) && command[j] != ' ' )
                {
                    inputfile[filled++] = command[j];
                }
                if (j == (i + 1) && command[j] == ' ')
                {
                    continue;
                }
                if (command[j] == '>')
                {
                    break;
                }
                else
                {
                    inputfile[filled++] = command[j];
                }
            }
            i = j - 1;
        }
        else if (command[i] == '>' && command[i + 1] == '>')
        {
            int j;
            int filled = 0;
            for (j = i + 2; j < strlen(command); j++)
            {
                if (j == (i + 2) && command[j] != ' ')
                {
                    newfilename[filled++] = command[j];
                }
                if (j == (i + 2) && command[j] == ' ')
                {
                    continue;
                }
                else if (command[j] == '<')
                {
                    break;
                }
                else
                {
                    // printf("%c",command[j]);
                    newfilename[filled++] = command[j];
                }
            }
            // printf(" ");
            i = j - 1;
        }
        else if (command[i] == '>')
        {
            int j;
            int filled = 0;
            for (j = i + 1; j < strlen(command); j++)
            {
                if (j == (i + 1) && command[j] != ' ')
                {
                    newfilename[filled++] = command[j];
                }
                if (j == (i + 1) && command[j] == ' ')
                {
                    continue;
                }
                if (command[j] == '<')
                {
                    break;
                }
                else
                {
                    // printf("%c",command[j]);
                    newfilename[filled++] = command[j];
                }
            }
            // printf(" ");
            i = j - 1;
        }
    }
    for(int i=0;i<strlen(command);i++){
        if(command[i]=='<' || command[i]=='>'){
            command[i-1]='\0';
            break;
        }
    }
    if(inputfile[strlen(inputfile)-1]==' '){
        inputfile[strlen(inputfile)-1]='\0';
    }
    if(newfilename[strlen(inputfile)-1]==' '){
        newfilename[strlen(inputfile)-1]='\0';
    }
    //printf("%s %s %s\n",newfilename,inputfile,command);
    int original_stdout = dup(STDOUT_FILENO);
    int stdin_org = dup(STDIN_FILENO);
    // printf("Modified Command: %s\n", command);
    if (flag == 1)
    {
        int fd = open(newfilename, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd == -1)
        {
            perror("Failed to open file");
            return 0;
        }
        if (dup2(fd, STDOUT_FILENO) == -1)
        {
            perror("Failed to redirect stdout");
            close(fd); // Close the file descriptor
            return 0;
        }
        //printf("file opened\n");
        close(fd); // Close the file descriptor
    }
    if (flag == 2)
    {
        int fdq = open(newfilename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fdq == -1)
        {
            perror("Failed to open file");
            return 0;
        }
        if (dup2(fdq, STDOUT_FILENO) == -1)
        {
            //printf("!!!!!!file opened\n");
            perror("Failed to redirect stdout");
            close(fdq); // Close the file descriptor
            return 0;
        }
        //printf("file opened\n");
        close(fdq); // Close the file descriptor
    }
    //printf("%d\n",flag2);
    if (flag2 == 1)
    {
        //printf("sanchit1\n");
        int fd = open(inputfile, O_RDONLY);
        if (fd == -1)
        {
            perror("No such input file found!\n");
            return 0;
        }
        if (dup2(fd, STDIN_FILENO) == -1)
        {
            perror("Failed to redirect stdout");
            close(fd); // Close the file descriptor
            return 0;
        }
        //printf("file opened\n");
        close(fd); // Close the file descriptor
    }
    // printf("%s\n",command);
    if (strstr(command, "seek") != NULL)
    {
        // printf("wtf\n");
        seek(command);
        replacing(stdin_org, original_stdout, flag, flag2);
        return 0;
    }
    else if (strstr(command, "warp") != NULL)
    {
        warpp(command);
        replacing(stdin_org, original_stdout, flag, flag2);
        return 0;
    }
    else if (strstr(command, "peek") != NULL)
    {
        peekk(command);
        replacing(stdin_org, original_stdout, flag, flag2);
        return 0;
    }
    else if (strstr(command, "pastevents") != NULL)
    {
        pexec(command);
        replacing(stdin_org, original_stdout, flag, flag2);
        return 0;
    }
    else if (strstr(command, "proclore") != NULL)
    {
        char delimiters[] = " ";
        char *token;
        char *saveptr;
        token = strtok_r(command, delimiters, &saveptr);
        token = strtok_r(NULL, delimiters, &saveptr);
        if (token == NULL)
        {
            int x = getpid();
            char arr[10];
            snprintf(arr, sizeof(arr), "%d", x);
            proclore(arr);
        }
        else
        {
            // printf("%s\n",token);
            proclore(token);
        }
        replacing(stdin_org, original_stdout, flag, flag2);
        return 0;
    }
    else if (strstr(command, "activities") != NULL)
    {
        //printf("hiiii\n");
        act();
        replacing(stdin_org, original_stdout, flag, flag2);
        return 0;
    }
    else if (strstr(command, "ping") != NULL)
    {
        //printf("!!!!\n");
        signal1(command);
        replacing(stdin_org, original_stdout, flag, flag2);
        return 0;
    }
    else if (strstr(command, "iMan") != NULL)
    {
        manpage(command);
        replacing(stdin_org, original_stdout, flag, flag2);
        return 0;
    }
    else if (strstr(command, "neonate") != NULL)
    {
        //printf("hiiii\n");
        neonate(command);
        replacing(stdin_org, original_stdout, flag, flag2);
        return 0;
    }
    else if(strstr(command,"fg")!=NULL){
        bgtofg(command);
        replacing(stdin_org, original_stdout, flag, flag2);
        return 0;

    }
    else if(strstr(command,"bg")!=NULL){
        fgtobg(command);
        replacing(stdin_org, original_stdout, flag, flag2);
        return 0;

    }
    else if (strcmp(command, "exit") == 0)
    {
        replacing(stdin_org, original_stdout, flag, flag2);
        return -1;
    }
    else
    {
        // printf("wtf 1\n");
        foreground_calling(command);
        replacing(stdin_org, original_stdout, flag, flag2);
        return 0;
    }
    return 0;
}

// char *inputname(char *command)
// {
//     char *inputfilename = calloc(1000, sizeof(char));
//     int filled;
//     for (int i = 0; i < strlen(command); i++)
//     {
//         filled = 0;
//         if (command[i] == '<')
//         {
//             int j = i + 1;
//             if (command[j] == ' ')
//             {
//                 j++;
//             }
//             while (command[j] != ' ')
//             {
//                 inputfilename[filled++] = command[j];
//                 j++;
//             }
//             break;
//         }
//     }
//     inputfilename[filled] = '\0';
//     return inputfilename;
// }
// char *outputname(char *command)
// {
//     char *inputfilename = calloc(1000, sizeof(char));
//     int filled;
//     for (int i = 0; i < strlen(command); i++)
//     {
//         filled = 0;
//         if (command[i] == '>')
//         {
//             int j = i + 1;
//             if (command[j] == ' ' || command[j] == '>')
//             {
//                 j++;
//             }
//             if (command[j] == ' ')
//             {
//                 j++;
//             }
//             while (command[j] != ' ')
//             {
//                 inputfilename[filled++] = command[j];
//                 j++;
//             }
//             break;
//         }
//     }
//     inputfilename[filled] = '\0';
//     return inputfilename;
// }

// void changeoutput(int op, char *outputfilename)
// {
//     if (op == 1)
//     {
//         int fd = open(outputfilename, O_WRONLY | O_CREAT | O_APPEND, 0644);
//         if (fd == -1)
//         {
//             perror("Failed to open file");
//         }
//         if (dup2(fd, STDOUT_FILENO) == -1)
//         {
//             perror("Failed to redirect stdout");
//             close(fd); // Close the file descriptor
//         }
//         // printf("file opened\n");
//         close(fd); // Close the file descriptor
//     }
//     if (op == 2)
//     {
//         int fdq = open(outputfilename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
//         if (fdq == -1)
//         {
//             perror("Failed to open file");
//         }
//         if (dup2(fdq, STDOUT_FILENO) == -1)
//         {
//             // printf("!!!!!!file opened\n");
//             perror("Failed to redirect stdout");
//             close(fdq); // Close the file descriptor
//         }
//         // printf("file opened\n");
//         close(fdq);
//     }
// }

// void changeinput(char *inputfilename)
// {
//     int fd = open(inputfilename, O_RDONLY);
//     if (fd == -1)
//     {
//         perror("No such input file found!\n");
//     }
//     if (dup2(fd, STDIN_FILENO) == -1)
//     {
//         perror("Failed to redirect stdout");
//         close(fd); // Close the file descriptor
//     }
//     // printf("file opened\n");
//     close(fd); // Close the file descriptor
// }
void process_execution(char *command)
{
    // int ip = 0, op = 0;
    // if (strstr(command, "<"))
    //     ip = 1;
    // if (strstr(command, ">"))
    //     op = 1;
    // if (strstr(command, ">>"))
    //     op = 2;
    // char *inputfilename = calloc(1000, sizeof(char));
    // char *outputfilename = calloc(1000, sizeof(char));
    // if (ip == 1)
    // {
    //     inputfilename = inputname(command);
    // }
    // if (op == 1 || op == 2)
    // {
    //     outputfilename = outputname(command);
    // }
    // printf("%s %s\n",inputfilename,outputfilename);
    // command = changecommand(command);
    // int std_op = dup(STDOUT_FILENO);
    // int std_in = dup(STDIN_FILENO);
    // // printf("%s\n",command);
    // if (op > 0)
    // {
    //     changeoutput(op, outputfilename);
    // }
    // if (ip > 0)
    // {
    //     changeinput(inputfilename);
    // }
    if (strstr(command, "seek") != NULL)
    {
        // printf("wtf\n");
        seek(command);
    }
    else if (strstr(command, "warp") != NULL)
    {
        warpp(command);
    }
    else if (strstr(command, "peek") != NULL)
    {
        peekk(command);
    }
    else if (strstr(command, "pastevents") != NULL)
    {
        pexec(command);
    }
    else if (strstr(command, "proclore") != NULL)
    {
        char delimiters[] = " ";
        char *token;
        char *saveptr;
        token = strtok_r(command, delimiters, &saveptr);
        token = strtok_r(NULL, delimiters, &saveptr);
        if (token == NULL)
        {
            int x = getpid();
            char arr[10];
            snprintf(arr, sizeof(arr), "%d", x);
            proclore(arr);
        }
        else
        {
            // printf("%s\n",token);
            proclore(token);
        }
    }
    else if (strstr(command, "activities") != NULL)
    {
        // printf("hiiii\n");
        act();
    }
    else if (strstr(command, "ping") != NULL)
    {
        // printf("!!!!\n");
        signal1(command);
    }
    else if (strstr(command, "iMan") != NULL)
    {
        manpage(command);
    }
    else if (strstr(command, "neonate") != NULL)
    {
        // printf("hiiii\n");
        neonate(command);
    }
    else if (strstr(command, "fg") != NULL)
    {
        bgtofg(command);
    }
    else if (strstr(command, "bg") != NULL)
    {
        fgtobg(command);
    }
    else if (strcmp(command, "exit") == 0)
    {
        exit(1);
    }
    else
    {
        // printf("wtf 1\n");
        foreground_calling(command);
    }
    //replacing(std_in,std_op,op,ip);
}