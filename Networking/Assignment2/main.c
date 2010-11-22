/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/16/2010 02:01:52 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
/*-----------------------------------------------------------------------------
 *  Include the headers
 *-----------------------------------------------------------------------------*/
#include <stdio.h>
#include "main.h"

/*-----------------------------------------------------------------------------
 *  Constant Definitions
 *-----------------------------------------------------------------------------*/
#define MAX_BUF_SIZ 32767
#define BUF_SIZ 1024

/*-----------------------------------------------------------------------------
 *  Global Variable Definitions
 *-----------------------------------------------------------------------------*/
char g_buf[MAX_BUF_SIZ]; /* Global buffer containing all necessary data */
char* g_fileName; /* Global buffer containing the current file */
int g_sendEmail = FALSE; /* Global indicator if an e-mail has been sent */
CURL *curl; /* Main instance of CURL */

/** main
 *      Enables the use of libcurl, and connects to
 *      BB9 using a username and password. Requests
 *      the Announcements and Calendar info
 *
 *      @param argc The number of arguments
 *      @param argv Array of arguments for strings
 *      @return EXIT_SUCCESS for successful execution or
 *              EXIT_FAILURE for unsuccessful execution
 */
int main( int argc, char** argv )
{
    CURLcode res; /* Return value of CURL */
    FILE* loginFile; /* File value of Announcements */
    char* userName; /* The username that was given to the program */
    struct stat st; /* Structure to use for directory check */

    /* Run initialization functions */
    crcInit();
    curl = curl_easy_init( );
    if(curl)
    {
        /* Initialize our curl object */
        InitBB9( curl );

        /* Validate arguments */
        if(argc > 1)
        {
            /* Assign the parameters */
            userName = argv[USERNAME];

            /* Check for directory */
            if(stat(userName, &st) == -1)
            {
                /* Create the directory */
                mkdir(userName, 0777);
            }
        }

        /* Change to the directory */
        chdir(userName);

        /* Enter a Loop */
        for(;;)
        {
            /* Open the Login file */
            loginFile = OpenFile(LOGIN_FILE);
            curl_easy_setopt(curl, CURLOPT_HEADERDATA, loginFile);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, loginFile);

            /* Post the Login Page */
            curl_easy_setopt(curl, CURLOPT_URL, URL LOGIN);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, USER);
            res = curl_easy_perform(curl);

            /* Close the Login file */
            fclose(loginFile);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, stdout);
            curl_easy_setopt(curl, CURLOPT_HEADERDATA, NULL);

            /* Post the Required Data */
            PostData(curl, CALENDAR_FILE, CALENDAR);
            PostData(curl, ANNOUNCEMENTS_FILE, ANNOUNCEMENTS);

            /* Sleep for one minute */
            sleep(SLEEP_TIME);
        }

        /* Clean up */
        curl_easy_cleanup(curl);
    }

    return EXIT_SUCCESS;
}

/** InitBB9
 *      Does the initialize configuration of the curl object
 *      Sets up the required header for BB9 communication
 *      @param curl The curl object to initialize
 */
void InitBB9( CURL* curl )
{
#ifdef DEBUG
    /* Enable the debugging function */
    struct data config;
    config.trace_ascii = 1;
    curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, my_trace);
    curl_easy_setopt(curl, CURLOPT_DEBUGDATA, &config);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
#endif

    /* Configure our specialized header */
    struct curl_slist *chunk = NULL;
    chunk = curl_slist_append(chunk, "Host: online.algonquincollege.com");
    chunk = curl_slist_append(chunk, "Connection: close");
    chunk = curl_slist_append(chunk, "Accept: application/xml,application/xhtml+xml,text/html;"
                                     "q=0.9,text/plain;q=0.8,image/png,*/*;q=0.5");
    chunk = curl_slist_append(chunk, "User-Agent: Mozilla/5.0 (X11; U; Linux x86_64; en-US) "
                                     "Cody T WebBot/1.0\r\nAccept-Encoding: gzip, deflate");
    chunk = curl_slist_append(chunk, "Accept-Language: en-US,en;q=0.8");
    chunk = curl_slist_append(chunk, "Accept-Charset: utf-8,*;q=0.3");

    /* Configure CURL to use special headers */
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

    /* Enable cookies */
    curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");
}

/** AppendBuffer
 *      Reads data from buffer and concatenates it to the
 *      global buffer
 *
 *      @param ptr The pointer containing data
 *      @param size The size of each member in the data
 *      @param nmemb The number of members in the data
 *      @param data The pointer where to write
 *      @return The number of bytes read
 */
size_t AppendBuffer( void* ptr, size_t size, size_t nmemb, void* data )
{
    /* Append to the buffer */
    sprintf(g_buf, "%s%s", g_buf, (char*)ptr);

    /* Return the number of bytes appended */
    return (size * nmemb);
}

/** WriteData
 *      Compares the data contained in the global buffer to the data
 *      contained within the given file. If the data is different,
 *      it overwrites the data in the file with the data in the buffer
 *
 *  @param fileName The filename to read from and write too
 *  @return The number of bytes written, if any
 */
int WriteData( char* fileName )
{
    char buf[MAX_BUF_SIZ];
    crc inData, fileData;
    int length;
    FILE* f;

    /* Open the File */
    f = OpenFile( fileName );

    /* Clear our buffer */
    memset(buf, '\0', MAX_BUF_SIZ);

    /* Calculate the crc of the data */
    inData = crcSlow(g_buf, strlen(g_buf));

    /* Read the file and calculate it's crc */
    length = fread(buf, 1, MAX_BUF_SIZ - 1, f);
    buf[length + 1] = '\0';

    /* Calculate the crc of the file data */
    fileData = crcSlow(buf, length);

    /* Check if CRC's are the same */
    length = 0;
    if(inData != fileData)
    {
        /* File changed, notify user */
        printf("Updated data contained in %s! Old CRC: %d, New CRC: %d\n",
                fileName, fileData, inData);

        /* Create the Delta File */
        length = CreateDelta( fileName );

        /* E-mail the Delta */
        SendEmail( EMAIL, "aretnorp", fileName );
    }
    else
        printf("%s checked, no changes were made!\n", fileName);

    /* Close the File */
    fclose(f);

    /* Return the number of bytes written */
    return length;
}

/** PostData
 *      Opens the file for posting, sets up the post data through
 *      curl, and sends it
 *
 *      @param curl The curl object to use for posting
 *      @param fileName The filename of the file to write too
 *      @param postString What to post to the server
 */
void PostData( CURL* curl, char* fileName, char* postString )
{
    FILE* f; /* File to write too */
    CURLcode res; /* Return value of CURL */
    char buf[MAX_BUF_SIZ]; /* Buffer which holds the data */

    /* Use the Module page to get Module Information */
    curl_easy_setopt(curl, CURLOPT_URL, URL MODULE);
    
    /* Reset the global buffer */
    memset(g_buf, '\0', sizeof(g_buf));

    /* Setup our Write Function so it does print */
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, AppendBuffer);

    /* Post the Calendar Module */
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postString);
    res = curl_easy_perform(curl);

    /* Compare the files */
    WriteData( fileName );
}

/** OpenFile
 *      Opens a file for reading and writing. If it can not
 *      be opened for reading, then it creates it and opens
 *      for reading and writing
 *
 *      @param fileName The file to open/create
 *      @return The FILE* pointer for the requested file or
 *              NULL if it fails to open
 */
FILE* OpenFile( char* fileName )
{
    FILE* f;
    f = fopen(fileName, "r+b");
    if(f == NULL)
    {
        /* Could not open file! */
        f = fopen(fileName, "w+b");
        if(f == NULL)
        {
            perror(APPLICATION);
            exit(EXIT_FAILURE);
        }
    }
}

/** CreateDelta
 *      Creates a delta of a file, creates the diff
 *      patch file, and then moves the temp file over
 *      the original using rename
 *
 *      @param fileName The file to open/create
 *      @return The number of bytes written to the temp file
 */
int CreateDelta( char* fileName )
{
        FILE* f;
        int length;
        char tempFileName[BUF_SIZ];
        char diffCmd[BUF_SIZ];

        /* Generate the Delta file */
        sprintf(tempFileName, "%s-new", fileName);
        f = fopen( tempFileName, "w+b" );
        if( f == NULL)
        {
            perror(APPLICATION " Temp Diff");
            exit(EXIT_FAILURE);
        }
        length = fwrite(g_buf, 1, strlen(g_buf), f);
        fclose(f);

        /* Generate the patch file */
        sprintf(diffCmd, "diff -rcNP %s %s > %s.patch",
            fileName, tempFileName, fileName);
        system(diffCmd);

        /* Copy over the file */
        if(rename(tempFileName, fileName) != 0)
        {
            perror(APPLICATION " File Move");
            exit(EXIT_FAILURE);
        }
}


/** SendEmail
 *      Opens up a connection with a given SMTP server
 *      and sends an e-mail to it
 *
 *      @param e The file to open/create
 *      @return The number of bytes written to the temp file
 */
void SendEmail(char* server, char* recipient, char* fileName)
{
        char buf[BUF_SIZ];
        char deltaFile[BUF_SIZ];
        int sockfd;
        FILE *file = NULL;

        /* Open the connection to the mail server*/
        sockfd = CreateSocket(server, "25");
        ReadLine(sockfd, buf);
        sprintf(buf, "HELO %s\r\n", server);
        SendLine(sockfd, buf);

        /* Read the server response */
        memset(buf, '\0', BUF_SIZ);
        ReadLine(sockfd, buf);

        /* Send in the mail headers */
        sprintf( buf, "MAIL FROM: %s\r\n", "WebBot");
        SendLine(sockfd, buf);
        memset(buf, '\0', BUF_SIZ);
        ReadLine(sockfd, buf);

        sprintf( buf, "RCPT TO: %s\r\n", recipient);
        SendLine(sockfd, buf);
        memset(buf, '\0', BUF_SIZ);
        ReadLine(sockfd, buf);

        /* Send the mailbody */
        sprintf( buf, "DATA\r\n");
        SendLine(sockfd, buf);
        memset(buf, '\0', BUF_SIZ);

        ReadLine(sockfd, buf);
        memset(buf, '\0', BUF_SIZ);

        /* Open the file for read */
        if ((file = fopen(fileName, "r"))==NULL)
        {
            perror("WEBBOT");
            exit(EXIT_FAILURE);
        }
        fread(deltaFile, 1, BUF_SIZ, file);

        /* Create Message */
        sprintf( buf, "From: WebBot\r\n To: %s\r\n Subject: WebBot Update\r\nBody: %s\r\n.\r\n", recipient, deltaFile);
        SendLine(sockfd, buf);
        ReadLine(sockfd, buf);

        /* Close the connection */
        SendLine(sockfd, "QUIT");
        fclose(file);
        close(sockfd);
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

    /* Receive the line */
    count = recv(sockfd, out, BUF_SIZ - 1, 0);

    /* Add an EOL and newline to the buffer */
    out[count]='\0';
    printf("%s\n", out);
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
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        getaddrinfo(url, port, &hints, &res);

        /* Create the Socket */
        sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

        /* Connect the Socket */
        if ((sockfd < 0) || (connect(sockfd, res->ai_addr, res->ai_addrlen) < 0))
        {
                perror("WEBBOT");
                exit(EXIT_FAILURE);
        }

        /* Return the created socket */
        return sockfd;
}

/** SendEmail
 *      Sending an e-mail using the libCURL. Takes the cURL
 *      object in the program and opens a connection with the
 *      SMTP server
 *
 *      @param fileName The file to open/create
 *      @return The number of bytes written to the temp file
 */
void SendEmailCURL( char* fileName )
{
    struct curl_slist *recipients = NULL;

    /* Set the e-mail server */
    curl_easy_setopt(curl, CURLOPT_URL, EMAIL);
    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, "WebBot@algonquincollege.com");

    /* Set the recipients */
    recipients = curl_slist_append(recipients, "aretnorp");
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

    /* Set the origin of the body */
    g_sendEmail = TRUE;
    g_fileName = fileName;
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, ReadEmailBody);

    /* Set the content */
    curl_easy_perform(curl);

    /* Reset the Read function */
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);

    /* Free the list */
    curl_slist_free_all(recipients);
}

/** ReadEmailBody
 *      Writes the e-mail data, used for cURL
 *
 *      @param ptr Where the data is going
 *      @param size The size of the members
 *      @param nmemb The number of members
 *      @param data The data (not used)
 *      @return The number of bytes written
 */
size_t ReadEmailBody( void* ptr, size_t size, size_t nmemb, void* data )
{
    if(g_sendEmail)
    {
        size_t bytes, total;
        FILE* diff;
        char buf[BUF_SIZ];
        char fileBuf[MAX_BUF_SIZ];

        /* Read in the changes */
        sprintf(buf, "%s.patch", g_fileName);
        bytes = 0;
        diff = fopen(buf, "r");
        while(!feof(diff))
            bytes += fread(fileBuf, 1, MAX_BUF_SIZ, diff);
        fileBuf[bytes] = '\0';

        /* Print the message to our temporary buffer */
        bytes = sprintf(ptr, EMAILBODY,
                "WebBot", "Aretnorp",
                g_fileName, fileBuf);

        /* Indicate that the e-mail is sent */
        g_sendEmail = FALSE;

        /* Return the number of bytes */
        return bytes;
    }
    else
        return 0;
}
