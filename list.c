/**
 * @brief Implementation of list module
 * @author Izan Robles
 */

#include "list.h"

typedef struct _NodeList
{
    void *data;
    struct _NodeList *next;
} NodeList;

struct _List
{
    NodeList *last;
};

List *list_new()
{
    List *pl = (List *)malloc(sizeof(List));

    if (pl == NULL)
    {
        return NULL;
    }

    pl->last = NULL;

    return pl;
}

Bool list_isEmpty(const List *pl)
{
    if (pl == NULL || pl->last == NULL)
    {
        return TRUE;
    }

    return FALSE;
}

Status list_pushFront(List *pl, void *e)
{
    NodeList *new_node = NULL;
    
    if (pl == NULL || e == NULL)
    {
        return ERROR;
    }

    new_node = (NodeList *)malloc(sizeof(NodeList));
    if (new_node == NULL)
    {
        return ERROR;
    }

    new_node->data = e;

    if (pl->last == NULL)
    {
        new_node->next = new_node; 
        pl->last = new_node;
    }
    else
    {
        new_node->next = pl->last->next;
        pl->last->next = new_node;
    }

    return OK;
}

Status list_pushBack(List *pl, void *e)
{
    Status result;
    
    if (pl == NULL || e == NULL)
    {
        return ERROR;
    }

    result = list_pushFront(pl, e);
    if (result == OK)
    {
        pl->last = pl->last->next;
    }
    return result;
}

Status list_pushInOrder(List *pl, void *e, P_ele_cmp f, int order)
{
    NodeList *current;
    NodeList *prev;
    NodeList *new_node;

    if (pl == NULL || e == NULL || f == NULL)
    {
        return ERROR;
    }

    new_node = (NodeList *)malloc(sizeof(NodeList));
    
    if (new_node == NULL)
    {
        return ERROR;
    }
    new_node->data = e;

    if (list_isEmpty(pl))
    {
        new_node->next = new_node;
        pl->last = new_node;
        return OK;
    }

    current = pl->last->next;
    prev = pl->last;

    do
    {
        int cmp_result = f(e, current->data);

        if ((order == 1 && cmp_result < 0) || (order == -1 && cmp_result > 0))
        {
            if (current == pl->last->next)
            {
                new_node->next = pl->last->next;
                pl->last->next = new_node;
                if (current == pl->last)
                {
                    pl->last = new_node;
                }
            }
            else
            {
                new_node->next = current;
                prev->next = new_node;
            }
            return OK;
        }

        prev = current;
        current = current->next;

    } while (current != pl->last->next);

    new_node->next = pl->last->next;
    pl->last->next = new_node;
    pl->last = new_node;

    return OK;
}

void *list_popFront(List *pl)
{
    NodeList *first = NULL;
    void *data = NULL;
    
    if (pl == NULL || pl->last == NULL)
    {
        return NULL;
    }

    first = pl->last->next;
    data = first->data;

    if (pl->last == first)
    {
        pl->last = NULL;
    }
    else
    {
        pl->last->next = first->next;
    }

    free(first);
    return data;
}

void *list_popBack(List *pl)
{
    NodeList *last_node;
    NodeList *second_last;
    void *data;
    
    if (pl == NULL || pl->last == NULL)
    {
        return NULL;
    }

    last_node = pl->last;
    second_last = pl->last;

    if (pl->last->next == pl->last)
    {
        pl->last = NULL;
        data = last_node->data;
        free(last_node);
        return data;
    }

    while (second_last->next != last_node)
    {
        second_last = second_last->next;
    }

    second_last->next = pl->last->next;
    pl->last = second_last;

    data = last_node->data;
    free(last_node);
    return data;
}


void list_free(List *pl)
{
    if (pl)
    {
        free(pl);
    }
}

void list_free_with_elements(List *pl, P_ele_free f)
{    
    if (!pl || !f)
    {
        return;
    }

    if (list_isEmpty(pl))
    {
        free(pl);
        return;
    }

    while(!list_isEmpty(pl))
    {
        f(list_popFront(pl));
    }

    free(pl);
}

size_t list_size(const List *pl)
{
    size_t count = 0;
    NodeList *node = pl->last->next;

    if (pl == NULL || pl->last == NULL)
    {
        return 0;
    }

    do
    {
        count++;
        node = node->next;
    } while (node != pl->last->next);

    return count;
}

int list_print(FILE *fp, const List *pl, P_ele_print f)
{
    int chars_printed = 0;
    NodeList *node = NULL;
    
    if (fp == NULL || pl == NULL || f == NULL)
    {
        return -1;
    }

    if (list_isEmpty(pl))
    {
        return fprintf(fp, "Empty list\n");
    }

    chars_printed = fprintf(fp, "Size of list: %lu\n", list_size(pl));
    node = pl->last->next;

    do
    {
        chars_printed += f(fp, node->data);
        chars_printed += fprintf(fp, " ");
        node = node->next;
    } while (node != pl->last->next);

    fprintf(stdout, "\n");
    return chars_printed;
}
