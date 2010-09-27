/*
 * =====================================================================================
 *
 *       Filename:  client.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/27/2010 08:05:23 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define BUF_SIZ 256

#define ADDRESS 1
#define PORT 2

int main(int argc, char* argv[])
{
    int sockfd; /* Socket File Descriptor */
    int bytesSent; /* Bytes Sent */
    struct addrinfo hints, *res; /* Network Structures */
    char buf[BUF_SIZ]; /* Buffer */
    char* address;
    char* port;

    /* Check the parameters */
    if(argc < 3)
    {
        fprintf(stderr, "No port provided!\n");
        fprintf(stderr, "Proper usage:\n");
        fprintf(stderr, "   ./client address portNumber\n");
        exit(1);
    }
    /* Define the parameters */
    address = argv[ADDRESS];
    port = argv[PORT];

    /* Setup the structures */
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    if(getaddrinfo(address, "1024", &hints, &res) != 0)
    {
        fprintf(stderr, "getaddrinfo failed!\n");
        exit(1);
    }
    
    /* Create the socket */
    sockfd = socket(res->ai_family, res->ai_socktype,
            res->ai_protocol);

    /* Connect to the server */
    connect(sockfd, res->ai_addr, res->ai_addrlen);

    /* Send the message */
    sprintf(buf, "Hello workd!\n");
    bytesSent += send(sockfd, buf, strlen(buf), 0);

    /* Close the socket */
    close(sockfd);

    /* Garbage clean-up */
    freeaddrinfo(res);

    /* Show the number of bytes sent */
    printf("Number of bytes sent: %d\n", bytesSent);

    /* Exit the function */
    return 0;
}
