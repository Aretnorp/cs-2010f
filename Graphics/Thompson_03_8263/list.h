/*
 * =====================================================================================
 *
 *       Filename:  list.h
 *
 *    Description:  Provides an interface to a 2D transformation game. Levels are read
 *                  from a file. Each level is a list of transformations. The users
 *                  objective is to figure out the value of each of the transformations.
 *
 *        Version:  1.0
 *        Created:  11/11/2010 4:00:00 PM
 *
 *         Author:  Cody Thompson
 *
 *     Difficulty:  The most difficult aspects were the drag and drop functionality,
 *                  and implementing a functional linked list within the assignment
 *                  specification. Once the custom tailored Linked List was complete
 *                  and the drag drop code properly implemented, the remaining
 *                  sections fell into place. I would rate the level of difficulty at
 *                  a 4, making it among the most difficult of Graphics assignments
 *                  yet.
 *     Objectives:  Receive a better grasp of Transformations within a 2D Space. Make
 *                  use of Drag and Drop Mouse related functions in GLUT. Learn pop
 *                  and push matrices. Implement a custom set of transformations within
 *                  an assignment.
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
    struct TransformNode* tail;
} TransformList;

/*-----------------------------------------------------------------------------
 *  Function Definitions
 *-----------------------------------------------------------------------------*/
void AddNode( TransformList*, Transform* );
void AppendNode( TransformList*, TransformNode* );
void RemoveNode( TransformList*, TransformNode* );
void InsertNode( TransformList*, TransformNode*, TransformNode* );
void PrintList( TransformList* );
void CopyList( TransformList*, TransformList* );
TransformNode* CreateNode( Transform* );

#endif /* _LIST_H_ */
