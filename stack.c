/**
 * @file  stack.c
 * @author Izan Robles
 * @brief Stack library
 */

#include "stack.h"

#define INIT_CAPACITY 2  
#define FCT_CAPACITY 2  

struct _Stack {
    void **item;   
    int top;       
    int capacity; 
};

/* ------------------------------------------------------------------------------------ */
Stack *stack_init()
{
    Stack *s = NULL;

    s = (Stack *)malloc(sizeof(Stack));
    if (!s)
    {
        return NULL;
    }

    s->item = (void **)malloc(INIT_CAPACITY * sizeof(void *));
    if (!s->item)
    {
        free(s);
        return NULL;
    }

    s->top = -1;
    s->capacity = INIT_CAPACITY;

    return s;
}

/* ------------------------------------------------------------------------------------ */
void stack_free(Stack *s)
{
    if (s)
    {
        if (s->item)
        {
            free(s->item);
        }
        free(s);
    }
}

/* ------------------------------------------------------------------------------------ */
Status stack_push(Stack *s, const void *ele)
{
    void **new_item;
    
    if (!s || !ele)
    {
        return ERROR;
    }

    if (s->top == s->capacity - 1)
    {
        new_item = (void **)realloc(s->item, FCT_CAPACITY * s->capacity * sizeof(void *));
        if (!new_item)
        {
            return ERROR;
        }
        s->item = new_item;
        s->capacity *= FCT_CAPACITY;
    }

    s->top++;
    s->item[s->top] = (void *)ele;

    return OK;
}

/* ------------------------------------------------------------------------------------ */
void *stack_pop(Stack *s)
{
    void *ele;

    if (!s || stack_isEmpty(s))
    {
        return NULL;
    }

    ele = s->item[s->top];
    s->top--;

    return ele;
}

/* ------------------------------------------------------------------------------------ */
void *stack_top(const Stack *s)
{
    if (!s || stack_isEmpty(s))
    {
        return NULL;
    }

    return s->item[s->top];
}

/* ------------------------------------------------------------------------------------ */
Bool stack_isEmpty(const Stack *s)
{
    if (!s)
    {
        return TRUE;
    }

    return (s->top == -1) ? TRUE : FALSE;
}

/* ------------------------------------------------------------------------------------ */
size_t stack_size(const Stack *s)
{
    if (!s)
    {
        return 0;
    }

    return s->top + 1;
}

/* ------------------------------------------------------------------------------------ */
int stack_print(FILE *fp, const Stack *s, P_stack_ele_print f)
{
    int i;
    int num_chars = 0;

    if (!fp || !s || !f)
    {
        return -1;
    }

    for (i = 0; i <= s->top; i++)
    {
        num_chars += f(fp, s->item[i]);
        if (i < s->top)
        {
            num_chars += fprintf(fp, " ");
        }
    }

    return num_chars;
}