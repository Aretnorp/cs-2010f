/*
 * =====================================================================================
 *
 *                 Student Name: Cody Thompson
 *             Algonquin E-Mail: thom0731
 *               Student Number: 040 584 188
 *                Course Number: CST8165
 *                  Lab Section: 010
 *               Professor Name: David Watson
 *  Assignment Name/Number/Date: Lab 1 due September 27th, 2010
 *
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

/* Instantiates the 
 * @author Cody Thompson
 * @param argc Number of arguments sent
 * @param argv Pointer to the array of arguments
 */
int main(int argc, char* argv[])
{
    int sockfd; /* Socket File Descriptor */
    int bytesSent = 0; /* Bytes Sent */
    int status; /* Placeholder for status return */
    int length; /* Holds the length of the data */
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
        exit(EXIT_FAILURE);
    }

    /* Define the parameters */
    address = argv[ADDRESS];
    port = argv[PORT];

    /* Setup the structures */
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    if((status = getaddrinfo(address, port, &hints, &res) != 0))
    {
        fprintf(stderr, "getaddrinfo failed!\n");
        exit(EXIT_FAILURE);
    }
    
    /* Create the socket */
    sockfd = socket(res->ai_family, res->ai_socktype,
            res->ai_protocol);

    /* Connect to the server */
    if((status = connect(sockfd, res->ai_addr, 
        res->ai_addrlen) != 0))
    {
        fprintf(stderr, "Could not connect!\n");
        exit(EXIT_FAILURE);
    }

    /* Send the message */
    sprintf(buf, "Hello workd!\n");
    length = strlen(buf);
    bytesSent = 0;
    while(bytesSent < length)
        bytesSent += send(sockfd, buf + bytesSent, strlen(buf), 0);

    /* Close the socket */
    close(sockfd);

    /* Garbage clean-up */
    freeaddrinfo(res);

    /* Show the number of bytes sent */
    printf("Number of bytes sent: %d\n", bytesSent);

    return 0;
}
