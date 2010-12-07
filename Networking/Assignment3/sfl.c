/*
 * =====================================================================================
 *
 *       Filename:  sfl.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10-12-07 12:34:02 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include "sfl.h"
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


int main(int argc, char *argv[])
{
    CLIENT *clnt; /* Client object for RPC */
    char *server; /* Server to connect to */
    char *directory; /* Directory to list */
    FILE* file; /* File to read from */
    readdir_res *result; /* Directory result */
    namelist nl;

    /* Validate the parameters */
    if (argc != 3)
    {
        fprintf(stderr, "usage: %s host directory\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* Assign the parameters */
    server = argv[1];
    directory = argv[2];

    /* Create the Assignment directory */
    mkdir("assign3", 0777);
    chdir("assign3");

    /* Create the sfl listing file */
    if((file = fopen("sfl_list.txt", "w")) == NULL)
    {
        perror(argv[0]);
        exit(EXIT_FAILURE);
    }

    /* Open the connection to the server */
    clnt = clnt_create(server, DIRPROG, DIRVERS, "tcp");
    if (clnt == (CLIENT*)NULL)
    {
        /* Could not connect to the server */
        clnt_pcreateerror(server);
        exit(EXIT_FAILURE);
    }

    /* Get the results from the server */
    result = readdir_1(&directory, clnt);
    if (result == (readdir_res *)NULL) 
    {
        /* No results were found */
        clnt_perror(clnt, server);
        exit(EXIT_FAILURE);
    }
    else if (result->err != 0)
    {
        /* Ensure that there was no error returned */
        errno = result->err;
        perror(directory);
        exit(EXIT_FAILURE);
    }

    /* Print the results */
    printf("Size\tPermission\tFilename\n");
    for (nl = result->readdir_res_u.list;  nl != NULL; nl = nl->next)
    {
            printf("%d\t%s\t%s\n", nl->size, nl->modes, nl->name);
            fprintf(file, "%d\t%s\t%s\n", nl->size, nl->modes, nl->name);
    }

    /* Free up files and used memory */
    fclose(file);
    xdr_free(xdr_readdir_res, result);
    clnt_destroy(clnt);

    /* Return */
    exit(EXIT_SUCCESS);
}

                        
