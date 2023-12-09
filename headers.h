#ifndef HEADERS_H_
#define HEADERS_H_

#include <stdio.h>
#include "prompt.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <string.h>
#include <pwd.h>
#include "warp.h"
#include <sys/types.h>
#include <sys/stat.h>
#include "peek.h"
#include <dirent.h>
#include <grp.h>
#include <time.h>
#include "pastevent.h"
#include "bg.h"
#include "processexec.h"
#include <signal.h>
#include "fg.h"
#include <time.h>
#include "seek.h"
#include "proclore.h"
#include "iman.h"
#include "activity.h"
#include <netdb.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include "signal.h"
#include "pipe.h"
#include "change.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include "neonate.h"
#include <termios.h>
#include <ctype.h>

struct processes
{
    pid_t pid;
    char processname[1000];
    struct processes *next;
};

extern char curdir[300];
extern char prevdir[300];
extern char homedir[300];
extern int flagtime;
extern struct processes *header;
extern char *timestr;
extern int cpu_time_used;
extern struct processes *activity;
extern pid_t fgpid;
extern char* fgname;

#endif