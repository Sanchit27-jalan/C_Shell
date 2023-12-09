#include "headers.h"

void die(const char *s) {
    perror(s);
    exit(1);
}

struct termios orig_termios;

void disableRawMode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr");
}

/**
 * Enable row mode for the terminal
 * The ECHO feature causes each key you type to be printed to the terminal, so you can see what you’re typing.
 * Terminal attributes can be read into a termios struct by tcgetattr().
 * After modifying them, you can then apply them to the terminal using tcsetattr().
 * The TCSAFLUSH argument specifies when to apply the change: in this case, it waits for all pending output to be written to the terminal, and also discards any input that hasn’t been read.
 * The c_lflag field is for “local flags”
*/
void enableRawMode() {
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) die("tcgetattr");
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
}

/**
 * stdout and stdin are buffered we disable buffering on that
 * After entering in raw mode we read characters one by one
 * Up arrow keys and down arrow keys are represented by 3 byte escape codes
 * starting with ascii number 27 i.e. ESC key
 * This way we interpret arrow keys
 * Tabs are usually handled by the term, but here we are simulating tabs for the sake of simplicity
 * Backspace move the cursor one control character to the left
 * @return
*/
void neonate(char *command)
{
    //printf("neonate is\n");
    char delimiters[] = " ";
    char *token;
    char *saveptr;
    token = strtok_r(command, delimiters, &saveptr);
    token = strtok_r(NULL, delimiters, &saveptr);
    char *time=strtok_r(NULL, delimiters, &saveptr);
    int t=atoi(time);
    setbuf(stdout, NULL);
    enableRawMode();
    pid_t pid=fork();
    if(pid<0)
    {
        perror("fork");
    }
    else if(pid==0)
    {
        while(1)
        {
            int fd=open("/proc/sys/kernel/ns_last_pid",O_RDONLY);
            ssize_t bytesRead;
            char buffer[100];
            bytesRead = read(fd, buffer, sizeof(buffer));
            printf("%s",buffer);
            close(fd);
            sleep(t);
        }
    }
    else
    {
        char input ;
        while(read(STDIN_FILENO, &input, 1) == 1)
        {
            if(input == 'x' || input == 'X')
            {
                break;
            }
        }
        kill(pid , SIGKILL);

    }
    disableRawMode();

}
