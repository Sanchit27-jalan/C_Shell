#include "headers.h"

void background_calling(char *input)
{
    //printf("%s\n",input);
    pid_t pid = fork();
    //printf("%s\n",input);
    if (pid == 0)
    {
        char *name[] = {
            "/bin/bash",
            "-c",
            "sleep 5&",
            NULL};
        //strcpy(name[2],input);
        name[2]=strdup(input);
        //printf("%s      %s\n",name[2],name[0]);
        execvp(name[0], name);
        printf("Error\n");
        // return -1;
    }
    else
    {
        printf("%d\n",pid);
        struct processes *temp = header;
        while ((temp->next) != NULL)
        {
            temp = temp->next;
        }
        struct processes *new = malloc(sizeof(struct processes));
        new->pid = pid;
        new->next = NULL;
        strcpy(new->processname, input);
        temp->next = new;
        //printf("Insider function %d %s\n",header->next->pid,header->next->processname);
        struct processes* temp2=activity;
        struct processes* temp3=activity->next;
        struct processes *new2 = malloc(sizeof(struct processes));
        new2->pid = pid;
        new2->next = NULL;
        strcpy(new2->processname, input);
        while(temp2!=NULL){
            if(temp2->pid==-1){
                if(temp3==NULL){
                    temp2->next=new2;
                    return;
                }
                else if(temp3->pid>pid){
                    temp2->next=new2;
                    new2->next=temp3;
                    return;
                }
                else{
                    temp2=temp2->next;
                    temp3=temp3->next;
                }
            }
            else if(temp3==NULL){
                temp2->next=new2;
                return;
            }
            else if(temp3->pid<pid && temp2->pid<pid){
                temp3=temp3->next;
                temp2=temp2->next;
            }
            else if(temp3->pid>pid && temp2->pid<pid){
                temp2->next=new2;
                new2->next=temp3;
                return;
            }
        }
        return;
    }
}