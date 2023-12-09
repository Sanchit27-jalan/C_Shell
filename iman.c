 #include "headers.h"

void manpage(char *t)
{
    char delimiters[] = " ";
    char *token;
    char *saveptr;
    char *command;
    token = strtok_r(t, delimiters, &saveptr);
    command = strtok_r(NULL, delimiters, &saveptr);
    const char *hostname = "man.he.net";
    const char *service = "http"; 
    //char command[] = "open";        
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int status, sockfd;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    
    hints.ai_socktype = SOCK_STREAM; 

    status = getaddrinfo(hostname, service, &hints, &result);
    if (status != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
    }

    for (rp = result; rp != NULL; rp = rp->ai_next)
    {
        sockfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sockfd == -1)
        {
            perror("socket");
            continue;
        }

        if (connect(sockfd, rp->ai_addr, rp->ai_addrlen) != -1)
        {
            break; 
        }

        close(sockfd); 
    }

    if (rp == NULL)
    {
        fprintf(stderr, "Failed to connect to the server\n");
        freeaddrinfo(result);
    }

    freeaddrinfo(result);

    char url[4096];
    snprintf(url, sizeof(url), "/man1/%s.1", command);

    char http_request[4096];
    snprintf(http_request, sizeof(http_request), "GET /?topic=%s&section=all HTTP/1.1\r\nHost: man.he.net\r\n\r\n", command);
    if (write(sockfd, http_request, strlen(http_request)) == -1)
    {
        perror("write");
        close(sockfd);
    }
    //ssize_t n;
    // while ((n = read(sockfd, buffer, sizeof(buffer))) > 0)
    // {
    //     fwrite(buffer, 1, n, stdout);
    //     //printf("%s\n",buffer);
    // }
    char response[4096];
    ssize_t bytes_received;
    int flag=0;
    while ((bytes_received = recv(sockfd, response, sizeof(response), 0)) > 0) {
        // printf("%s" , response);
        int iterator=0;
        if(flag ==1)
        {
            char* to_break = strstr(response , "AUTHOR");
            if(to_break!=NULL)
            {
                for(int i=0 ; i<to_break - response ; i++)
                {
                    printf("%c" , response[i]);
                }
                break;
            }
        }
        char* result = strstr(response , "NAME\n");
        if(result!=NULL)
        {
            flag = 1;
            char* to_break = strstr(result , "AUTHOR");
            if(to_break!=NULL)
            {
                for(int i=0 ; i<to_break - result ; i++)
                {
                    printf("%c" , result[i]);
                }
                break;
            }
            else{
                printf("%s" , result);
            }
        }       
    }
    if(flag==0)
    {
        printf("ERROR\n\tNo such command\n");
    }

    // if (bytes_received < 0) {
    //     perror("Response receiving error");
    //     // return 1;
    //     //return remaining_token;

    // }

    close(sockfd);

}