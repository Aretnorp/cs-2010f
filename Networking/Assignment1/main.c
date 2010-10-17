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

#define USER_INFO \
"user_id=thom0731&password=&login=Login&action=login&remote-user=" \
"&new_loc=%C2%A0&auth_type=&one_time_token=" \
"&encoded_pw=dVUzNTg0MjM1MCo%3D&encoded_pw_unicode=dQBVADMANQA4ADQAMgAzADUAMAAqAAAA" \

#define POST_REQUEST \
"Accept: application/xml,application/xhtml+xml,text/html;q=0.9,text/plain;q=0.8,image/png,*/*;q=0.5\r\n" \
"User-Agent: Mozilla/5.0 (X11; U; Linux x86_64; en-US) CST8165 Webot/1.0\r\nAccept-Encoding: gzip, deflate\r\n" \
"Accept-Language: en-US,en;q=0.8\r\n" \
"Accept-Charset: utf-8,*;q=0.3\r\n" \

#define BUF_SIZ 1024

#define CALENDAR "action=refreshAjaxModule&modId=_2_1&tabId=_1_1&tab_tab_group_id=_1_1"
#define ANNOUNCEMENTS "action=refreshAjaxModule&modId=_1_1&tabId=_1_1&tab_tab_group_id=_1_1"

#include <stdio.h>
#include <curl/curl.h>
#include <string.h>

#define URL "http://online.algonquincollege.com/"
#define LOGIN "webapps/login/"
#define MODULE "webapps/portal/execute/tabs/tabAction"

int main( void )
{
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init( );
    if(curl)
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
        chunk = curl_slist_append(chunk, "Accept: application/xml,application/xhtml+xml,text/html;q=0.9,text/plain;q=0.8,image/png,*/*;q=0.5");
        chunk = curl_slist_append(chunk, "User-Agent: Mozilla/5.0 (X11; U; Linux x86_64; en-US) CST8165 Webot/1.0\r\nAccept-Encoding: gzip, deflate");
        chunk = curl_slist_append(chunk, "Accept-Language: en-US,en;q=0.8");
        chunk = curl_slist_append(chunk, "Accept-Charset: utf-8,*;q=0.3");

        /* Configure CURL to use special headers and cookies */
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
        curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");

        /* Post the Login Page */
        curl_easy_setopt(curl, CURLOPT_URL, URL LOGIN);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, USER_INFO);
        res = curl_easy_perform(curl);

        /* Use the Module page to get Module Information */
        curl_easy_setopt(curl, CURLOPT_URL, URL MODULE);

        /* Post the Announcements Module */
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, ANNOUNCEMENTS);
        res = curl_easy_perform(curl);

        /* Post the Calendar Module */
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, CALENDAR);
        res = curl_easy_perform(curl);

        /* Clean up */
        curl_easy_cleanup(curl);
    }

    return 0;
}

