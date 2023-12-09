#include "headers.h"

int substringornot(char *main, char *second, int l1, int l2)
{
    if (l1 > l2)
    {
        return 0;
    }
    for (int i = 0; i < l1; i++)
    {
        if (main[i] != second[i])
        {
            return 0;
        }
    }
    return 1;
}
void prompt()
{
    register struct passwd *pw;
    pw = getpwuid(getuid());
    char *username = pw->pw_name;
    struct hostent *host_entry;
    char name[10000]={'\0'};
    name[0] = '<';
    int filled = 1;
    strcat(name, username);
    name[strlen(username) + 1] = '@';
    filled = strlen(username) + 2;
    char hostbuffer[256];
    int hostname;
    hostname = gethostname(hostbuffer, sizeof(hostbuffer));
    if (hostname == -1)
    {
        perror("gethostname error");
        exit(1);
    }
    getcwd(curdir, 300);
    hostbuffer[strlen(hostbuffer)] = ':';
    strcat(name, hostbuffer);
    filled = filled + strlen(hostbuffer);
    int comparison = substringornot(homedir, curdir, strlen(homedir), strlen(curdir));
    //printf("%d\n",comparison);
    //printf("%d\n",comparison);
    if (strcmp(curdir, homedir) == 0)
    {
        char add[3] = "~>";
        //printf("%s\n",name);
        strcat(name, add);
        filled = filled + 2;
    }
    else if (comparison == 1)
    {
        int newlength = strlen(curdir) - strlen(homedir);
        //printf("%d\n",newlength);
        char dir[newlength + 2];
        strncpy(dir, curdir + strlen(homedir), newlength);
        dir[newlength] = '>';      
        dir[newlength + 1] = '\0';
        //printf("%s\n",dir);
        strcat(name, dir);
        filled = filled + newlength+1;
    }
    else
    {
        strcat(name, curdir);
        filled = filled + strlen(curdir);
        name[filled++] = '>';
        //printf("%c\n",name[filled]);
        //name[filled++] = '\0';
    }
    if(flagtime==1){
        name[filled-1]=' ';
        for(int i=0;i<strlen(timestr);i++){
            if(timestr[i]==' '){
                break;
            }
            else{
                name[filled++]=timestr[i];
            }
        }
        name[filled++]=' ';
        // strcat(name,timestr);
        // filled=filled+strlen(timestr);
        name[filled++]=':';
        name[filled++]=' ';
        char n[20000]={'\0'};
        sprintf(n, "%d",cpu_time_used);
        strcat(name,n);
        filled=filled+strlen(n);
        name[filled++]='s';
        name[filled++] = '>';
        flagtime=0;
        free(timestr);
        timestr=calloc(300,sizeof(char));
    }
    //printf("%c\n",name[filled-1]);
    printf("%s", name);
}
