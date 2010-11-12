/*
 * =====================================================================================
 *
 *       Filename:  list.c
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
/*-----------------------------------------------------------------------------
 *  Include the headers
 *-----------------------------------------------------------------------------*/
#include "list.h"

/*-----------------------------------------------------------------------------
 *  AddNode
 *  Create a Node and add it to the end of the list
 *-----------------------------------------------------------------------------*/
void AddNode(TransformList *list, Transform *t)
{
    TransformNode *node;

    /* Create the Node */
    if((node = CreateNode(t)) == NULL)
        return;

    /* Add the Node to the list */
    AppendNode(list, node);
}


/*-----------------------------------------------------------------------------
 *  CreateNode
 *  Generate a new node and return its pointer or NULL
 *-----------------------------------------------------------------------------*/
TransformNode* CreateNode(Transform* data)
{
    TransformNode* newNode;

    /* Create the data */
    if((newNode = (TransformNode*)malloc(sizeof(TransformNode))) == NULL)
    {
        perror("2D"); exit(EXIT_FAILURE);
    }

    /* Assign the new node */
    newNode->next = NULL;
    newNode->prev = NULL;
    newNode->data = data;

    /* Return the newly created node */
    return newNode;
}

/*-----------------------------------------------------------------------------
 *  CopyList
 *  Take a list, copy it, but exclude the actual Transform data
 *-----------------------------------------------------------------------------*/
void CopyList(TransformList *from, TransformList *to)
{
    TransformNode* node = from->root;

    /* Verify the list */
    if(from->root == NULL)
        return;

    /* Copy the list */
    node = from->root;
    while(node != NULL)
    {
        TransformNode* newNode;
        Transform* t;

        /* Create a new node */
        if((newNode = (TransformNode*)malloc(sizeof(TransformNode))) == NULL)
        {
            perror("2D"); exit(EXIT_FAILURE);
        }
        if((t = (Transform*)malloc(sizeof(Transform))) == NULL)
        {
            perror("2D"); exit(EXIT_FAILURE);
        }
        t->type = node->data->type;
        t->axis = node->data->axis;
        t->value = 0;
        newNode->data = t;

        /* Copy the node */
        AppendNode(to, newNode);

        /* Goto next node */
        node = node->next;
    }
}

/*-----------------------------------------------------------------------------
 *  RunTransform
 *  Process the transformation given and apply it to the pipeline
 *-----------------------------------------------------------------------------*/
void PrintList(TransformList *list)
{
    TransformNode* node = list->root;

    /* Verify the list */
    if(list->root == NULL)
        return;

    /* Iterate through the list */
    do
    {
        printf("Transform: %c %c %d\n", node->data->type, node->data->axis,
                node->data->value);
        node = node->next;
    } while((node != list->root) && (node != NULL));
}

/*-----------------------------------------------------------------------------
 *  RemoveNode
 *  Remove a node from the specified list
 *-----------------------------------------------------------------------------*/
void RemoveNode(TransformList* list, TransformNode* lnode)
{
    if(lnode->prev == NULL)
        list->root = lnode->next;
    else
        lnode->prev->next = lnode->next;

    if(lnode->next == NULL)
        list->tail = lnode->prev;
    else
        lnode->next->prev = lnode->prev;
}

/*-----------------------------------------------------------------------------
 *  AppendNode
 *  Add a Node to the end of the list
 *-----------------------------------------------------------------------------*/
void AppendNode(TransformList* list, TransformNode* lnode)
{
    if(list->root == NULL)
    {
        list->root = lnode;
        lnode->prev = NULL;
    }
    else
    {
        list->tail->next = lnode;
        lnode->prev = list->tail;
    }
    list->tail = lnode;
    lnode->next = NULL;
}

/*-----------------------------------------------------------------------------
 *  InsertNode
 *  Insert a node at a specified place
 *-----------------------------------------------------------------------------*/
void InsertNode(TransformList* list, TransformNode* lnode, TransformNode* after)
{
    lnode->next = after->next;
    lnode->prev = after;

    if(after->next != NULL)
        after->next->prev = lnode;
    else
        list->tail = lnode;
    after->next = lnode;
}

/*-----------------------------------------------------------------------------
 *  ClearList
 *  Clears out a list
 *-----------------------------------------------------------------------------*/
void ClearList(TransformList* list)
{
    TransformNode* node = list->root;

    while(node != NULL)
    {
        TransformNode* temp = node;

        /* Advance to next node */
        node = node->next;

        /* Clear the node from the list */
        RemoveNode(list, temp);

        /* Free the data */
        free(temp->data);
        free(temp);
    }
}
