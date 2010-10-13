/*
 * =====================================================================================
 *
 *                 Student Name: Cody Thompson
 *             Algonquin E-Mail: thom0731
 *               Student Number: 040 584 188
 *                Course Number: CST8165
 *                  Lab Section: 010
 *               Professor Name: David Watson
 *  Assignment Name/Number/Date: Lab 2 due October 4th, 2010
 *
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h> 
#include <sys/stat.h>
#include <sys/socket.h>
#include <netdb.h>

#define PORT 1
#define DIRECTORY 2

#define FILENAME "Lab_02_C"

#define BACKLOG 5
#define BUF_SIZ 256


/** Errors out of the program
 * @param msg The error message to use with perror
 */
void error(char *msg)
{
    perror(msg);
    exit(1);
}

/** Instantiates the network receive
 * @author Cody Thompson
 * @param argc Number of arguments sent
 * @param argv Pointer to the array of arguments
 */
int main(int argc, char *argv[])
{
    int sockfd, clilen, bytes;
    struct addrinfo hints, *res;
    struct sockaddr_storage cli_addr;
    char* port;
    char* dir;
    char buf[BUF_SIZ];
    FILE* f;
    struct stat st;

    /* Confirm the parameters */
    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }

    /* Configure parameters */
    port = argv[PORT];
    dir = argv[DIRECTORY];

    /* Setup the structure */
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET6;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;
    if(getaddrinfo(NULL, port, &hints, &res) != 0)
    {
        fprintf(stderr, "getaddrinfo failed!\n");
        exit(EXIT_FAILURE);
    }

    /* Create the socket */
    sockfd = socket(res->ai_family, res->ai_socktype,
            res->ai_protocol);

    /* Bind to the socket */
    if (bind(sockfd, res->ai_addr, res->ai_addrlen) < 0)
            error("ERROR on binding");

    /* Clear memory */
    freeaddrinfo(res);

    /* Check for directory */
    if(stat(dir, &st) == -1)
    {
        /* Create the directory */
        mkdir(dir, 0777);
    }

    /* Change to the directory */
    chdir(dir);

    /* Handle incoming connections */
    clilen = sizeof(cli_addr);

    /* Open the file */
    f = fopen(FILENAME, "wb");

    /* Wait to receive from */
    while (1)
    {
        /* Accepting connections */
        bytes = recvfrom(sockfd, buf, BUF_SIZ - 1, 0, (struct sockaddr*)&cli_addr, &clilen);
        buf[bytes] = '\0';

        /* Write the file */
        fwrite(buf, 1, bytes, f);

        fflush(f);
    }

    /* Close the file */
    fclose(f);

    /* Close the socket */
    close(sockfd);
    return 0;
}
