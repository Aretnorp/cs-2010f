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

/** main
 *      Enables the use of libcurl, and connects to
 *      BB9 using a username and password. Requests
 *      the Announcements and Calendar info
 *
 *      @return EXIT_SUCCESS for successful execution or
 *              EXIT_FAILURE for unsuccessful execution
 */
int main( void )
{
    CURL *curl; /* Main instance of CURL */
    CURLcode res; /* Return value of CURL */
    FILE* annFile;
    FILE* calFile;

    curl = curl_easy_init( );
    if(curl)
    {
        /* Initialize our curl object */
        InitBB9( curl );

        /* Setup our Write Function so it doesn't print */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, IgnoreData);

        /* Post the Login Page */
        curl_easy_setopt(curl, CURLOPT_URL, URL LOGIN);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, USER);
        res = curl_easy_perform(curl);

        /* Post the Required Data */
        PostData(curl, CALENDAR_FILE, CALENDAR);
        PostData(curl, ANNOUNCEMENTS_FILE, ANNOUNCEMENTS);

        /* Clean up */
        curl_easy_cleanup(curl);
    }

    return 0;
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

/** WriteData
 *      Reads data from file, does a CRC check if it's the same.
 *      If it isn't, it writes the file.
 *
 *      @param ptr The pointer containing data
 *      @param size The size of each member in the data
 *      @param nmemb The number of members in the data
 *      @param data The pointer where to write
 *      @return The number of bytes written
 */
size_t WriteData( void* ptr, size_t size, size_t nmemb, void* data )
{
    crc inData, fileData;
    int length;
    char buf[MAX_BUF_SIZ];
    FILE* f = (FILE*)data;

    /* Calculate the crc of the data */
    inData = crcSlow(ptr, (size * nmemb));
    printf("The CRC of our data: %d\n", inData);

    /* Read the file and calculate it's crc */
    length = fread(buf, 1, MAX_BUF_SIZ, f);
    buf[length] = '\0';

    /* Calculate the crc of the file data */
    fileData = crcSlow(buf, length);
    printf("The CRC of our file data: %d\n", fileData);

    /* Check if CRC's are the same */
    length = 0;
    if(inData != fileData)
    {
        printf("Updated data contained in file!\n");
        length = fwrite(ptr, size, nmemb, data);
    }

    /* Return the number of bytes written */
    return length;
}

/** IgnoreData
 *      Calculates the size of data and returns it, but doesn't
 *      print anything
 *      
 *      @param ptr The pointer containing data
 *      @param size The size of each member in the data
 *      @param nmemb The number of members in the data
 *      @param data The pointer where to write
 *      @return The number of bytes that was ignored
 */
size_t IgnoreData( void* ptr, size_t size, size_t nmemb, void* data )
{
    /* Ignore any of the data, and simply return the size of the data */
    return (size * nmemb);
}

/** PostData
 *      Opens the file for posting, sets up the post data through
 *      curl, and sends it
 *
 *      @param curl The curl object to use for posting
 *      @param size The filename of the file to write too
 *      @param postString What to post to the server
 */
void PostData( CURL* curl, char* fileName, char* postString )
{
    FILE* f; /* File to write too */
    CURLcode res; /* Return value of CURL */

    /* Open up the Calendar file */
    f = OpenFile(fileName);

    /* Use the Module page to get Module Information */
    curl_easy_setopt(curl, CURLOPT_URL, URL MODULE);

    /* Setup our Write Function so it does print */
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteData);

    /* Set the Write to the Opened File */
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, f);

    /* Post the Calendar Module */
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postString);
    res = curl_easy_perform(curl);

    /* Close the File */
    fclose(f);
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
