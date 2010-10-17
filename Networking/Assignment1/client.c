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

#define BUF_SIZ 32767

#define ADDRESS 1
#define PORT 2


#define USER_INFO "user_id=thom0731&password=&login=Login&action=login&remote-user=&new_loc=%C2%A0&auth_type=&one_time_token=&encoded_pw=dVUzNTg0MjM1MCo%3D&encoded_pw_unicode=dQBVADMANQA4ADQAMgAzADUAMAAqAAAA"
#define POST_REQUEST "POST %s HTTP/1.1\r\nHost: online.algonquincollege.com\r\nConnection: close\r\nAccept: application/xml,application/xhtml+xml,text/html;q=0.9,text/plain;q=0.8,image/png,*/*;q=0.5\r\nUser-Agent: Mozilla/5.0 (X11; U; Linux x86_64; en-US) CST8165 Webot/1.0\r\nAccept-Encoding: gzip, deflate\r\nAccept-Language: en-US,en;q=0.8\r\nAccept-Charset: utf-8,*;q=0.3\r\ncontent-type: application/x-www-form-urlencoded\r\ncontent-length: %ld\r\n"

/** Instantiates the network send
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
    char* address = "online.algonquincollege.com";
    char* port = "80";

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
    sprintf(buf, POST_REQUEST "\r\n%s\r\n\r\n", "/webapps/login/", strlen(USER_INFO),
            USER_INFO);
    length = strlen(buf);
    bytesSent = 0;
    while(bytesSent < length)
        bytesSent += send(sockfd, buf + bytesSent, strlen(buf), 0);

    /* Receive the information */
    while((length = recv(sockfd, buf, BUF_SIZ - 1, 0)) > 0)
    {
        printf("%s\n", buf);
    }

    /* Close the socket */
    close(sockfd);

    /* Garbage clean-up */
    freeaddrinfo(res);

    /* Show the number of bytes sent */
    printf("Number of bytes sent: %d\n", bytesSent);

    return 0;
}
