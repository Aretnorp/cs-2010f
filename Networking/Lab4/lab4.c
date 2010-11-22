/*
 * =====================================================================================
 *
 *       Filename:  lab4.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10-11-21 06:35:46 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>

#define BUF_SIZ 2048

void ReadLine( int, char* );
void SendLine( int, char* );
int CreateSocket( char*, char* );

int main(void)
{
    int sockfd;
    char buf[BUF_SIZ];

    /* Connect to the POP server */
    printf("POP3\n\n");
    sockfd = CreateSocket("127.0.0.1", "110");
    ReadLine(sockfd, buf);

    /* Query the server */
    sprintf(buf, "USER %s\r\n", "aretnorp");
    SendLine(sockfd, buf);
    ReadLine(sockfd, buf);

    sprintf(buf, "PASS %s\r\n", "OMGNOTMYPASS");
    SendLine(sockfd, buf);
    ReadLine(sockfd, buf);

    /* List the messages */
    sprintf(buf, "LIST\r\n");
    SendLine(sockfd, buf);
    ReadLine(sockfd, buf);

    /* Check for a message */
    if(strstr(buf, "0 messages") != NULL)
        printf("Can not retrieve a message, no messages to retrieve!\n");
    else
    {
        /* Retrieve a message */
        sprintf(buf, "RETR 1\r\n");
        SendLine(sockfd, buf);
        ReadLine(sockfd, buf);

        /* Print the message */
        printf("Message Received:\n%s\n", buf);
    }

    /* Disconnect from server */
    close(sockfd);
    printf("\n\nIMAP\n\n");

    /* Connect to the IMAP server */
    sockfd = CreateSocket("127.0.0.1", "143");
    ReadLine(sockfd, buf);

    /* Login to the IMAP server */
    sprintf(buf, ". LOGIN %s %s\r\n", "aretnorp", "zanozano01");
    SendLine(sockfd, buf);
    ReadLine(sockfd, buf);

    /* Switch to the inbox */
    sprintf(buf, ". SELECT \"INBOX\"\r\n");
    SendLine(sockfd, buf);
    ReadLine(sockfd, buf);

    /* Retrieve all messages and their bodies */
    sprintf(buf, ". FETCH 1:* BODY[]\r\n");
    SendLine(sockfd, buf);
    ReadLine(sockfd, buf);

    /* Print the result */
    printf("Messages: \n");
    printf("%s\n", buf);
}

/** SendLine
 *      Sending a line on a socket
 *
 *      @param sockfd The socket to send on
 *      @param in The buffer reads from
 */
void SendLine(int sockfd, char* in)
{
    /* Send the line */
    send(sockfd, in, strlen(in), 0);
}

/** ReadLine
 *      Reading a line on a socket
 *
 *      @param sockfd The socket to send on
 *      @param out The buffer to write too
 */
void ReadLine(int sockfd, char* out)
{
    int count;

    /* Reset the buffer */
    memset(out, '\0', BUF_SIZ);

    /* Receive the line */
    count = recv(sockfd, out, BUF_SIZ - 1, 0);

    /* Add an EOL and newline to the buffer */
    out[count]='\0';
    //printf("%s\n", out);
}

/** CreateSocket
 *      Create a new socket based on a URL and Port
 *
 *      @param url The URL to connect too
 *      @param port The port to connect too
 */
int CreateSocket(char *url, char* port)
{
        struct addrinfo hints, *res;
        int sockfd;

        /* Create the hints structs */
        memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        getaddrinfo(url, port, &hints, &res);

        /* Create the Socket */
        sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

        /* Connect the Socket */
        if (sockfd < 0)
        {
                perror("WEBBOT Create Socket");
                exit(EXIT_FAILURE);
        }
        else if (connect(sockfd, res->ai_addr, res->ai_addrlen) < 0)
        {
            perror("WEBBOT Connect Socket");
            exit(EXIT_FAILURE);
        }

        /* Return the created socket */
        return sockfd;
}
