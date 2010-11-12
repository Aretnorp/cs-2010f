/*
 * =====================================================================================
 *
 *       Filename:  list.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10-11-11 09:07:19 AM
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
#include "list.h"

/*-----------------------------------------------------------------------------
 *  RunTransform
 *  Process the transformation given and apply it to the pipeline
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
 *  RunTransform
 *  Process the transformation given and apply it to the pipeline
 *-----------------------------------------------------------------------------*/
void AppendNode(TransformList *list, TransformNode *node)
{
    TransformNode *root;

    /* Adds a node to the end of the list */
    if(list->root == NULL)
    {
        list->root = node;
        list->tail = node;
        node->next = NULL;
        node->prev = NULL;
    }
    else
    {
        node->prev = list->tail;
        list->tail->next = node;
        node->next = NULL;
        list->tail = node;
    }
}

/*-----------------------------------------------------------------------------
 *  RunTransform
 *  Process the transformation given and apply it to the pipeline
 *-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 *  RunTransform
 *  Process the transformation given and apply it to the pipeline
 *-----------------------------------------------------------------------------*/
void InsertNode(TransformNode *node, TransformNode *prev)
{
    /* Check to make sure we're not moving it to the same place */
    if(node->prev == prev)
        return;

    /* Remove the node from the list */
    node->prev->next = node->next;
    node->next->prev = node->prev;

    /* Add it after prev */
    prev->next->prev = node;
    prev->next = node;
}


/*-----------------------------------------------------------------------------
 *  RunTransform
 *  Process the transformation given and apply it to the pipeline
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
 *  RunTransform
 *  Process the transformation given and apply it to the pipeline
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
