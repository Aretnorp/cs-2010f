const MAXNAMELEN = 255; /* Maximum length of character names */

typedef string nametype<MAXNAMELEN>; /* Length of names */

typedef struct namenode *namelist; /* Listing of names */

struct namenode
{
    nametype name; /* Directory name */
    int size; /* Size of the entry */
    namelist next; /* Pointer to next entry */
    nametype modes; /* Various mode types */
};

union readdir_res switch (int err) 
{
    case 0:
        namelist list; /*  Return directory listing */
    default:
        void; /* Return an error */
};

/* The directory program definition */
program DIRPROG
{
    version DIRVERS
    {
        readdir_res
        READDIR(nametype) = 1;
    } = 1;
} = 0x20000076;
