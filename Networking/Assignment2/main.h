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
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>

#include <curl/curl.h>

#include "crc/crc.h"

/*-----------------------------------------------------------------------------
 *  Constant Definitions
 *-----------------------------------------------------------------------------*/
/* Constants for URLS */
#define URL "http://online.algonquincollege.com/"
#define LOGIN "webapps/login/"
#define MODULE "webapps/portal/execute/tabs/tabAction"
#define EMAIL "smtp://localhost"

/* Constants for POST requests */
#define USER \
"user_id=thom0731&password=&login=Login&action=login&remote-user=" \
"&new_loc=%C2%A0&auth_type=&one_time_token=" \
"&encoded_pw=dVUzNTg0MjM1MCo%3D&encoded_pw_unicode=dQBVADMANQA4ADQAMgAzADUAMAAqAAAA"

#define CALENDAR "action=refreshAjaxModule&modId=_2_1&tabId=_1_1&tab_tab_group_id=_1_1"
#define ANNOUNCEMENTS "action=refreshAjaxModule&modId=_1_1&tabId=_1_1&tab_tab_group_id=_1_1"

/* Constants for File Definitions */
#define ANNOUNCEMENTS_FILE "announcements"
#define CALENDAR_FILE "calendar"
#define LOGIN_FILE "login"

/* Constants for Application */
#define APPLICATION "WebBot"
#define USERNAME 1
#define SLEEP_TIME 10

/* Constants for e-mail composition */
#define EMAILBODY \
"From: %s\r\n" \
"To: %s\r\n" \
"Subject: %s\r\n\r\n" \
"%s\r\n\r\n"

/*-----------------------------------------------------------------------------
 *  Function Definitions
 *-----------------------------------------------------------------------------*/
void InitBB9( CURL* );

size_t AppendData( void*, size_t, size_t, void* );

void PostData( CURL*, char*, char* );
int WriteData( char* );
int CreateDelta( char* );

FILE* OpenFile( char* );

void SendEmail( char* );

size_t ReadEmailBody( void*, size_t, size_t, void* );
