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
    TransformNode *root;
    TransformNode *node;

    /* Create the node */
    if((node = malloc(sizeof(struct TransformNode))) == NULL)
    {
        fprintf(stderr, "Node creation failed.\n");
        return;
    }
    node->data = t;

    /* Adds a node to the end of the list */
    if(list->root == NULL)
    {
        list->root = node;
        node->next = node;
        node->prev = node;
    }
    else
    {
        root = list->root;
        node->next = root;
        node->prev = root->prev;
        root->prev->next = node;
        root->prev = node;
    }
}


/*-----------------------------------------------------------------------------
 *  RunTransform
 *  Process the transformation given and apply it to the pipeline
 *-----------------------------------------------------------------------------*/
void RemoveNode(TransformNode *node)
{
    /* Deletes a node from the list */
    node->prev->next = node->next;
    node->next->prev = node->prev;

    /* Free the memory from the list */
    free(node);
}


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


void CopyList(TransformList *from, TransformList *to)
{
    TransformNode* node = from->root;

    /* Verify the list */
    if(from->root == NULL)
        return;

    /* Copy the list */
    do
    {
        TransformNode* newNode;
        TransformNode* prevNode;

        /* Create a new node */
        if((newNode = (TransformNode*)malloc(sizeof(TransformNode))) == NULL)
        {
            perror("2D"); exit(EXIT_FAILURE);
        }
        printf("oh shi\n");

        /* Copy the node */
        if(to->root == NULL)
        {
            to->root = newNode;
            newNode->data = node->data;
            newNode->next = newNode;
            newNode->prev = newNode;
        }
        else
        {
            newNode->data = node->data;
            newNode->prev = prevNode;
            prevNode->next = newNode;
            newNode->next = to->root;
        }

        /* Goto next node */
        prevNode = newNode;
        node = node->next;
    } while((node != from->root) && (node != NULL));
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