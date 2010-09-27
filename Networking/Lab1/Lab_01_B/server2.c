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
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#define BUF_SIZ 16

#define FILENAME "Lab_01_a"

void dostuff(int, char*); /* function prototype */

/* Uses perror and exists the program
 * @param msg Message for the error
 */
void error(char *msg)
{
    perror(msg);
    exit(1);
}

/* Hosts a server by configuring a socket and 
 * listenning on a port
 * @author Cody Thompson
 * @param argc Number of arguments sent
 * @param argv Pointer to the array of arguments
 */
int main(int argc, char *argv[])
{
    char* dir;
    int sockfd, newsockfd, portno, clilen, pid;
    struct sockaddr_in serv_addr, cli_addr;

    if (argc < 3) {
        fprintf(stderr,"Insufficient parameters!\n");
        exit(EXIT_FAILURE);
    }

    /* Assign the parameters */
    portno = atoi(argv[1]);
    dir = argv[2];

    /* Open a Socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");

    /* Clear the memory */
    memset(&serv_addr, 0, sizeof(serv_addr));

    /* Set the struct */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    /* Bind to the Port and Listen on it */
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
            sizeof(serv_addr)) < 0) 
        error("ERROR on binding");
    listen(sockfd,5);

    /* Incoming Client Request */
    clilen = sizeof(cli_addr);

    /* Receive the text */
    while (2) 
    {
        newsockfd = accept(sockfd, 
            (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0) 
            error("ERROR on accept");
        pid = fork();
        if (pid < 0)
            error("ERROR on fork");
        if (pid == 0)  {
            close(sockfd);
            dostuff(newsockfd, dir);
            exit(0);
        }
        else close(newsockfd);
    } /* end of while */
    return 0; /* we never get here */
}

/* Reads from the socket and writes it to a file
 * @author Cody Thompson
 * @param sock The file descriptor of the socket
 * @param dir The directory to write the file in
 */
void dostuff (int sock, char* dir)
{
    FILE* f;
    int readBytes;
    char buf[BUF_SIZ];
    struct stat st;

    /* Empty the Memory */
    memset(buf, 0, sizeof(buf));

    /* Check for directory */
    if(stat(dir, &st) == -1)
    {
        /* Create the directory */
        mkdir(dir, 0777);
    }

    /* Change to the directory */
    chdir(dir);

    /* Open the file */
    f = fopen(FILENAME, "wb");

    /* Read in a number of characters from the socket
     * and write it to the file
     */
    while((readBytes = read(sock,buf, BUF_SIZ - 1)) > 0)
    {
        fwrite(buf, 1, readBytes, f);
    }

    /* Print to the Console */
    printf("Wrote file to location %s/%s", dir, FILENAME);

    /* Close the file */
    fclose(f);
}
