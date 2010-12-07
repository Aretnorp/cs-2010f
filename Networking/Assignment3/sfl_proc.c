/*
 * =====================================================================================
 *
 *       Filename:  server.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10-12-07 01:12:47 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <dirent.h>
#include "sfl.h"
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>


readdir_res* readdir_1_svc(nametype *dirname, struct svc_req *req)
{
    DIR *dirp;
    struct dirent *d;
    namelist nl;
    namelist *nlp;
    char file_name[255];
    char file_perm[255];
    struct stat fileStat;
    static readdir_res res;

    /* Open directory */
    dirp = opendir(*dirname);
    if (dirp == (DIR *)NULL)
    {
        res.err = errno;
        return (&res);
    }

    /* Free previous result */
    xdr_free(xdr_readdir_res, &res);

    /* Assign list */
    nlp = &res.readdir_res_u.list;

    /* Read through the directories */
    while ((d = readdir(dirp)))
    {
        /* Assign the node */
        nl = *nlp = (namenode*)malloc(sizeof(namenode));
        if (nl == (namenode *)NULL)
        {
            res.err = EAGAIN;
            closedir(dirp);
            return(&res);
        }

        /* Print the name */
        sprintf(file_name, "%s/%s", *dirname, d->d_name);

        /* Ensure the file exists */
        if(!stat(file_name, &fileStat)) 
        {
            /* Set the attributes */
            nl->name = strdup(d->d_name);
            nl->size = fileStat.st_size;

            /* Determine the permissions */
            sprintf(file_perm, (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
            strcat(file_perm, (fileStat.st_mode & S_IRUSR) ? "r" : "-");
            strcat(file_perm, (fileStat.st_mode & S_IWUSR) ? "w" : "-");
            strcat(file_perm, (fileStat.st_mode & S_IXUSR) ? "x" : "-");
            strcat(file_perm, (fileStat.st_mode & S_IRGRP) ? "r" : "-");
            strcat(file_perm, (fileStat.st_mode & S_IWGRP) ? "w" : "-");
            strcat(file_perm, (fileStat.st_mode & S_IXGRP) ? "x" : "-");
            strcat(file_perm, (fileStat.st_mode & S_IROTH) ? "r" : "-");
            strcat(file_perm, (fileStat.st_mode & S_IWOTH) ? "w" : "-");
            strcat(file_perm, (fileStat.st_mode & S_IXOTH) ? "x" : "-");
            nl->modes = strdup(file_perm);
            nlp = &nl->next;
        }
    }
    *nlp = (namelist)NULL;

    /* Return the result */
    res.err = 0;
    closedir(dirp);

    return (&res);
}
