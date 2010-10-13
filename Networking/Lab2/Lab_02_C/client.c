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

#define BUF_SIZ 16

#define ADDRESS 1
#define PORT 2
#define FILENAME 3

/* Connects to the server and sends the file via IPv4
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
    char* file;

    /* Check the parameters */
    if(argc < 4)
    {
        fprintf(stderr, "No port provided!\n");
        fprintf(stderr, "Proper usage:\n");
        fprintf(stderr, "   ./client address portNumber file\n");
        exit(EXIT_FAILURE);
    }

    /* Define the parameters */
    address = argv[ADDRESS];
    port = argv[PORT];
    file = argv[FILENAME];

    /* Setup the structures */
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET6;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_ADDRCONFIG;
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
        res->ai_addrlen) == -1))
    {
        perror("Could not connect!\n");
        exit(EXIT_FAILURE);
    }

    /* Send the file */
    bytesSent = sendFile(sockfd, file);

    /* Close the socket */
    close(sockfd);

    /* Garbage clean-up */
    freeaddrinfo(res);

    /* Show the number of bytes sent */
    printf("Number of bytes sent: %d\n", bytesSent);

    return 0;
}
int sendFile(int sockfd, char* file)
{
    FILE* f;
    int totalSent;
    int bytesSent;
    int fileRead;
    char buf[BUF_SIZ];

    /* Open the file */
    if((f = fopen(file, "rb")) == NULL)
    {
        fprintf(stderr, "Could not open file %s\n", file);
        exit(EXIT_FAILURE);
    }

    /* Read the file */
    totalSent = 0;
    while((fileRead = fread(buf, 1, BUF_SIZ - 1, f)) != 0)
    {
        bytesSent = 0;

        /* Send the file */
        while(bytesSent < fileRead)
            bytesSent += send(sockfd, buf + bytesSent, fileRead, 0);

        /* Add to the total */
        totalSent += bytesSent;
    }

    /* Return the number of bytes */
    return totalSent;
}
