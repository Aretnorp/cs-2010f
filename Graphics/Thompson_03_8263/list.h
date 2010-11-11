/*
 * =====================================================================================
 *
 *       Filename:  list.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10-11-11 09:08:02 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef _LIST_H_
#define _LIST_H_
/*-----------------------------------------------------------------------------
 *  Include the headers
 *-----------------------------------------------------------------------------*/
#include <unistd.h>
#include <malloc.h>
#include <stdlib.h>

/*-----------------------------------------------------------------------------
 *  Structure Definitions
 *-----------------------------------------------------------------------------*/
typedef struct Transform
{
    char type;
    char axis;
    int value;
} Transform;

typedef struct TransformNode
{
    struct TransformNode* next;
    struct TransformNode* prev;
    Transform* data;
} TransformNode;

typedef struct TransformList
{
    struct TransformNode* root;
} TransformList;

/*-----------------------------------------------------------------------------
 *  Function Definitions
 *-----------------------------------------------------------------------------*/
void AddNode( TransformList*, Transform* );
void AppendNode( TransformList*, TransformNode* );
void RemoveNode( TransformList*, TransformNode* );
void InsertNode( TransformNode*, TransformNode* );
void PrintList( TransformList* );
TransformNode* CreateNode( Transform* );

#endif /* _LIST_H_ */
