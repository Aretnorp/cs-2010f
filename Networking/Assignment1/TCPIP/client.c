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

#define USER_INFO \
"user_id=thom0731&password=&login=Login&action=login&remote-user=" \
"&new_loc=%C2%A0&auth_type=&one_time_token=" \
"&encoded_pw=dVUzNTg0MjM1MCo%3D&encoded_pw_unicode=dQBVADMANQA4ADQAMgAzADUAMAAqAAAA" \

#define POST_REQUEST \
"POST %s HTTP/1.1\r\n" \
"Host: online.algonquincollege.com\r\n" \
"Connection: close\r\n" \
"Accept: application/xml,application/xhtml+xml,text/html;q=0.9,text/plain;q=0.8,image/png,*/*;q=0.5\r\n" \
"User-Agent: Mozilla/5.0 (X11; U; Linux x86_64; en-US) CST8165 Webot/1.0\r\nAccept-Encoding: gzip, deflate\r\n" \
"Accept-Language: en-US,en;q=0.8\r\n" \
"Accept-Charset: utf-8,*;q=0.3\r\n" \
"content-type: application/x-www-form-urlencoded\r\n" \
"content-length: %ld\r\n" \

#define ADDRESS "online.algonquincollege.com"
#define PORT "http"

#define JSESSION_ID_LENGTH 48
#define SESSION_ID_LENGTH 43

#define A_INFO "action=refreshAjaxModule&modId=_1_1&tabId=_1_1&tab_tab_group_id=_1_1"
#define C_INFO "action=refreshAjaxModule&modId=_2_1&tabId=_1_1&tab_tab_group_id=_1_1"


/** Instantiates the network send
 * @author Cody Thompson
 * @param argc Number of arguments sent
 * @param argv Pointer to the array of arguments
 */
int main(int argc, char* argv[])
{
    int sockfd; /* Socket File Descriptor */
    int sent = 0; /* Bytes Sent */
    int length; /* Holds the length of the data */
    int total;
    char buf[BUF_SIZ]; /* Buffer */
    char jsession[JSESSION_ID_LENGTH + 1];
    char session[SESSION_ID_LENGTH + 1];

    /* Login to Blackboard */
    sockfd = CreateSocket(ADDRESS, PORT);
    sprintf(buf, POST_REQUEST "\r\n%s\r\n\r\n", "/webapps/login/", strlen(USER_INFO),
            USER_INFO);
    length = strlen(buf);
    sent = 0;
    while(sent < length)
        sent += send(sockfd, buf + sent, strlen(buf), 0);

    /* Receive the information */
    total = 0;
    while((length = recv(sockfd, buf + total, BUF_SIZ - 1 - total, 0)) > 0)
    {
        total += length;
        printf("%s\n", buf);
    }
    printf("\n\n\n");

    /* Close the socket */
    close(sockfd);

    /* Extract the SessionID */
    strncpy(jsession, strstr(buf, "JSESSIONID"), JSESSION_ID_LENGTH);
    jsession[JSESSION_ID_LENGTH] = '\0';
    strncpy(session, strstr(buf, "session_id"), SESSION_ID_LENGTH);
    session[SESSION_ID_LENGTH] = '\0';

    /* Post the Announcements */
    sockfd = CreateSocket(ADDRESS, PORT);
    sprintf(buf, POST_REQUEST "Cookie: %s\r\n\r\n%s\r\n\r\n",
            "/webapps/portal/execute/tabs/tabAction",
            strlen(A_INFO),
            session,
            A_INFO);
    length = strlen(buf);
    sent = 0;
    while(sent < length)
        sent += send(sockfd, buf + sent, strlen(buf), 0);

    /* Receive the information */
    total = 0;
    while((length = recv(sockfd, buf + total, BUF_SIZ - 1 - total, 0)) > 0)
    {
        total += length;
        printf("%s\n", buf);
    }
    printf("\n\n\n");

    /* Close the socket */
    close(sockfd);

    /* Post the Calendar */
    sockfd = CreateSocket(ADDRESS, PORT);
    sprintf(buf, POST_REQUEST "Cookie: %s\r\n\r\n%s\r\n\r\n",
            "/webapps/portal/execute/tabs/tabAction",
            strlen(C_INFO),
            session,
            C_INFO);
    length = strlen(buf);
    sent = 0;
    while(sent < length)
        sent += send(sockfd, buf + sent, strlen(buf), 0);

    /* Receive the information */
    total = 0;
    while((length = recv(sockfd, buf + total, BUF_SIZ - 1 - total, 0)) > 0)
    {
        total += length;
        printf("%s\n", buf);
    }
    printf("\n\n\n");

    /* Close the socket */
    close(sockfd);

    return 0;
}

int CreateSocket( char* address, char* port )
{
    struct addrinfo hints, *res; /* Network Structures */
    int sockfd; /* Create the Socket */
    int status; /* Placeholder for status return */

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

    /* Garbage clean-up */
    freeaddrinfo(res);

    return sockfd;
}
