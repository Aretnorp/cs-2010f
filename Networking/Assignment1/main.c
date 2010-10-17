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

#define USER_INFO "user_id=thom0731&password=&login=Login&action=login&remote-user=&new_loc=%C2%A0&auth_type=&one_time_token=&encoded_pw=dVUzNTg0MjM1MCo%3D&encoded_pw_unicode=dQBVADMANQA4ADQAMgAzADUAMAAqAAAA"

#include <stdio.h>
#include <curl/curl.h>

int main( void )
{
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init( );
    if(curl)
    {
        struct curl_slist *chunk = NULL;

        curl_easy_setopt(curl, CURLOPT_URL, "http://online.algonquincollege.com/webapps/login/");
        curl_easy_setopt(curl, CURLOPT_COPYPOSTFIELDS, USER_INFO);

        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
    }

    return 0;
}
