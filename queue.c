/**
 * @brief Implements queue module
 * @author Izan Robles
 */

#include "queue.h"

#define MAX_QUEUE 100

struct _Queue
{
    void *data[MAX_QUEUE];
    void **front;
    void **rear;
    size_t size;
};

Queue *queue_new()
{
    Queue *q = NULL;
    if (!(q = (Queue*)malloc(sizeof(Queue))))
    {
        return NULL;
    }

    q->front = q->data;
    q->rear = q->data;
    q->size = 0;

    return q;
}

void queue_free(Queue *q)
{
    if (q)
    {
        free(q);
    }
}

Bool queue_isEmpty(const Queue *q)
{
    if (q && q->size == 0)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

Status queue_push(Queue *q, void *ele)
{
    if (!q || q->size >= MAX_QUEUE)
    {
        return ERROR;
    }
    
    *(q->rear) = ele;

    q->rear = q->data + ((q->rear - q->data + 1) % MAX_QUEUE);
    q->size++;

    return OK;
}

void *queue_pop(Queue *q)
{
    void *ele = *(q->front);

    if (!q || q->size == 0)
    {
        return NULL;
    }
    
    q->front = q->data + ((q->front - q->data + 1) % MAX_QUEUE);
    q->size--;
    return ele;
}

void *queue_getFront(const Queue *q)
{
    if (!q || q->size == 0)
    {
        return NULL;
    }

    return *(q->front);
}

void *queue_getBack(const Queue *q)
{
    if (!q || q->size == 0)
    {
        return NULL;
    }

    return *(q->data + ((q->rear - q->data - 1 + MAX_QUEUE) % MAX_QUEUE));
}

size_t queue_size(const Queue *q)
{
    if (q)
    {
        return q->size;
    }

    else
    {
        return 0;
    }
}

int queue_print(FILE *fp, const Queue *q, p_queue_ele_print f)
{
    int count = 0, i;
    const void *const *ptr = (const void *const *)q->front;

    if (!fp || !q || !f)
    {
        return -1;
    }

    for (i = 0; i < q->size; i++)
    {
        count += f(fp, *ptr);
        ptr = (const void *const *)(q->data + ((ptr - (const void *const *)q->data + 1) % MAX_QUEUE));
    }
    return count;
}



