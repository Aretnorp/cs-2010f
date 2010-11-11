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
void RemoveNode(TransformList *list, TransformNode *node)
{
    if((list == NULL) || (node == NULL))
        return;

    /* Delete the root node */
    if(node == list->root)
    {
        /* If it's the last node */
        if(node->next == node)
        {
            printf("Removing root\n");
            list->root = NULL;
        }
        /* If it's the first node */
        else
        {
            printf("Removing first not only\n");
            list->root = node->next;
            node->next->prev = node->prev;
            node->prev->next = node->next;
        }

    }
    else
    {
        printf("Removing a node\n");
        /* Deletes a node from the list */
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    node->next = NULL;
    node->prev = NULL;
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

TransformNode* CreateNode(Transform* data)
{
    TransformNode* newNode;

    /* Create the data */
    if((newNode = (TransformNode*)malloc(sizeof(TransformNode))) == NULL)
    {
        perror("2D"); exit(EXIT_FAILURE);
    }
    printf("oh shi\n");

    /* Assign the new node */
    newNode->next = NULL;
    newNode->prev = NULL;
    newNode->data = data;

    /* Return the newly created node */
    return newNode;
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

        /* Copy the node */
        if(to->root == NULL)
        {
            to->root = newNode;
            newNode->data = t;
            newNode->next = newNode;
            newNode->prev = newNode;
        }
        else
        {
            newNode->data = t;
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
