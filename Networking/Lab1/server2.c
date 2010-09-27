/* Downloaded from http://www.linuxhowtos.org/data/6/server2.c */

/* A simple server in the internet domain using TCP
   The port number is passed as an argument 
   This version runs forever, forking off a separate 
   process for each connection
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#define BUF_SIZ 16

#define FILENAME "Lab_01_a"

void dostuff(int); /* function prototype */
void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno, clilen, pid;
     struct sockaddr_in serv_addr, cli_addr;

     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }

     /* Open a Socket */
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");

     /* Clear the memory */
     memset(&serv_addr, 0, sizeof(serv_addr));

     /* Set the port number */
     portno = atoi(argv[1]);

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
     while (2) {
     newsockfd = accept(sockfd, 
        (struct sockaddr *) &cli_addr, &clilen);
         if (newsockfd < 0) 
             error("ERROR on accept");
         pid = fork();
         if (pid < 0)
             error("ERROR on fork");
         if (pid == 0)  {
             close(sockfd);
             dostuff(newsockfd);
             exit(0);
         }
         else close(newsockfd);
     } /* end of while */
     return 0; /* we never get here */
}

/******** DOSTUFF() *********************
 There is a separate instance of this function 
 for each connection.  It handles all communication
 once a connnection has been established.
 *****************************************/
void dostuff (int sock)
{
    FILE* f;
    int readBytes;
    char buf[BUF_SIZ];

    /* Empty the Memory */
    memset(buf, 0, sizeof(buf));

    /* Open the file */
    f = fopen(FILENAME, "wb");

    /* Read in a number of digits */
    while((readBytes = read(sock,buf, BUF_SIZ - 1)) > 0)
    {
        printf("Here is the message: %s\n",buf);
        
        fwrite(buf, 1, readBytes, f);

        readBytes = 0;
    }
    fclose(f);
}
