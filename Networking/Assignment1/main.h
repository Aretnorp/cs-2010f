/*
 * =====================================================================================
 *
 *       Filename:  main.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/17/2010 05:52:29 PM
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
#include <string.h>
#include <stdlib.h>

#include <curl/curl.h>

#include "crc.h"

/*-----------------------------------------------------------------------------
 *  Constant Definitions
 *-----------------------------------------------------------------------------*/
/* Constants for URLS */
#define URL "http://online.algonquincollege.com/"
#define LOGIN "webapps/login/"
#define MODULE "webapps/portal/execute/tabs/tabAction"

/* Constants for POST requests */
#define USER \
"user_id=thom0731&password=&login=Login&action=login&remote-user=" \
"&new_loc=%C2%A0&auth_type=&one_time_token=" \
"&encoded_pw=dVUzNTg0MjM1MCo%3D&encoded_pw_unicode=dQBVADMANQA4ADQAMgAzADUAMAAqAAAA" \
#define CALENDAR "action=refreshAjaxModule&modId=_2_1&tabId=_1_1&tab_tab_group_id=_1_1"
#define ANNOUNCEMENTS "action=refreshAjaxModule&modId=_1_1&tabId=_1_1&tab_tab_group_id=_1_1"

/* Constants for File Definitions */
#define ANNOUNCEMENTS_FILE "announcements"
#define CALENDAR_FILE "calendar"

/* Constants for Application */
#define APPLICATION "WebBot"


/*-----------------------------------------------------------------------------
 *  Function Definitions
 *-----------------------------------------------------------------------------*/
size_t WriteData( void*, size_t, size_t, void* );
size_t IgnoreData( void*, size_t, size_t, void* );

FILE* OpenFile( char* );
void PostData( CURL*, char*, char* );

void InitBB9( CURL* );
