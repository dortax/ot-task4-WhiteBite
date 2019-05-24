
/***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string>
#include <unistd.h>
#include <cstring>
/* Host name of my system, change accordingly */
/* Put the server hostname that run the UDP server program */
/* This will be used as default UDP server for client connection */
#define server "Lord9000"
/* Server's port number */
#define SERVPORT 2007
/* Pass in 1 argument (argv[1]) which is either the */
/* address or host name of the server, or */
/* set the server name in the #define SERVER above. */
int main(int argc, char *argv[])
{
    /* Variable and structure definitions. */
    int sd, rc;
    struct sockaddr_in serveraddr;
    char buffer[1000];
    int buflen = sizeof(buffer);
    struct hostent *hostp;
    for (size_t i = 0; i < argc; i++) {
        printf("arv[%zu] %s\n",i,argv[i] );
    }
    memset(buffer, 0x00, sizeof(buffer));

    //memcpy(buffer, "Hello! A client request message lol!", 37);

    /* get a socket descriptor */
    if ((sd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("UDP Client - socket() error");
        /* Just exit lol! */
        exit(-1);
    }
    else
        printf("UDP Client - socket() is OK!\n");
    // printf("ECHO\n");
    /* If the hostname/IP of the server is supplied */
    /* Or if(argc = 2) */
    strcpy(server, argv[1]);
    std::string q=argv[2] ;


    printf("%i\n",argc );
    if(argc>3){
        q+=" ";
        printf("%s\n",argv[3] );
        q+=argv[3];
    }
    printf("ECHO2\n");
    printf("[%s]\n",q.c_str() );
    strcpy(buffer, q.c_str());
    printf("UDP Client - buffer : %s \n", buffer);

    memset(&serveraddr, 0x00, sizeof(struct sockaddr_in));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(SERVPORT);
    printf("ECHO\n");
    if ((serveraddr.sin_addr.s_addr = inet_addr(server)) == (unsigned long)INADDR_NONE)
    {
        /* Use the gethostbyname() function to retrieve */
        /* the address of the host server if the system */
        /* passed the host name of the server as a parameter. */
        /************************************************/
        /* get server address */
        hostp = gethostbyname(server);
        if (hostp == (struct hostent *)NULL)
        {
            printf("HOST NOT FOUND --> ");
            /* h_errno is usually defined */
            /* in netdb.h */
            printf("h_errno = %d\n", h_errno);
            exit(-1);
        }
        else
        {
            printf("UDP Client - gethostname() of the server is OK... \n");
            printf("Connected to UDP server %s on port %d.\n", server, SERVPORT);
        }
        memcpy(&serveraddr.sin_addr, hostp->h_addr, sizeof(serveraddr.sin_addr));
    }
    /* Use the sendto() function to send the data */
    /* to the server. */
    /************************************************/
    /* This example does not use flags that control */
    /* the transmission of the data. */
    /************************************************/
    /* send request to server */

    rc = sendto(sd, buffer, buflen, 0, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    if (rc < 0)
    {
        perror("UDP Client - sendto() error");
        close(sd);
        exit(-1);
    }
    else
        printf("UDP Client - sendto() is OK!\n");
    printf("Waiting a reply from UDP server...\n");
    /* Use the recvfrom() function to receive the */
    /* data back from the server. */
    /************************************************/
    /* This example does not use flags that control */
    /* the reception of the data. */
    /************************************************/
    /* Read server reply. */
    /* Note: serveraddr is reset on the recvfrom() function. */

    memset(buffer, 0x00, sizeof(buffer));
    rc = recv(sd, buffer, sizeof(buffer), 0);
    if (rc < 0)
    {
        perror("UDP Client - recvfrom() error");
        close(sd);
        exit(-1);
    }
    else
    {
        printf("UDP client received the following: \"%s\" message\n%i\n", buffer,sizeof(buffer));
        printf(" from port %d, address %s\n", ntohs(serveraddr.sin_port), inet_ntoa(serveraddr.sin_addr));
    }
    /* When the data has been received, close() */
    /* the socket descriptor. */
    /********************************************/
    /* close() the socket descriptor. */
    close(sd);
    exit(0);
}
