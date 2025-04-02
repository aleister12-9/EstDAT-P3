/**
 * @file  stack.h
 * @author Izan Robles
 * @author Teachers at EPS
 * @brief Stack library
 */

#ifndef STACK_H
#define STACK_H

#include "types.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Structure to implement a stack.
 * @author Izan Robles
 *
 **/
typedef struct _Stack Stack;

/**
 * @brief Typedef for a function pointer to print a stack element at stream
 **/
typedef int (*P_stack_ele_print)(FILE *, const void*);

/**
 * @brief Typedef for a function pointer to cmp two stack elements
 **/
typedef int (*P_stack_ele_cmp)(const void *, const void *);

/**
 * @brief This function initializes an empty stack.
 * @author Izan Robles
 *
 * @return This function returns a pointer to the stack or a null pointer
 * if insufficient memory is available to create the stack.
 *  */
Stack * stack_init (void);

/**
 * @brief  This function frees the memory used by the stack.
 * @author Izan Robles
 * 
 * @param s A pointer to the stack
 *  */
void stack_free (Stack *s);

/**
 * @brief This function is used to insert a element at the top of the stack.
 * @author Izan Robles
 *
 * A reference of the element is added to the stack container and the size of the stack is increased by 1.
 * Time complexity: O(1). This function reallocate the stack capacity when it is full.
 * @param s A pointer to the stack.
 * @param ele A pointer to the element to be inserted
 * @return This function returns OK on success or ERROR if the stack is full.
 *  */
Status stack_push (Stack *s, const void *ele);

/**
 * @brief  This function is used to extract a element from the top of the stack.
 * @author Izan Robles
 *
 * The size of the stack is decreased by 1. Time complexity: O(1).
 * @param s A pointer to the stack.
 * @return This function returns a pointer to the extracted element on success
 * or null when the stack is empty.
 * */
void * stack_pop (Stack *s);

/**
 * @brief  This function is used to reference the top (or the newest) element of the stack.
 * @author Izan Robles
 *
 * @param s A pointer to the stack.
 * @return This function returns a pointer to the newest element of the stack.
 * */
void * stack_top (const Stack *s);

/**
 * @brief Returns whether the stack is empty
 * @author Izan Robles
 * 
 * @param s A pointer to the stack.
 * @return TRUE or FALSE
 */
Bool stack_isEmpty (const Stack *s);

/**
 * @brief This function returns the size of the stack.
 * @author Izan Robles
 *
 * Time complexity: O(1).
 * @param s A pointer to the stack.
 * @return the size
 */
size_t stack_size (const Stack *s);

/**
 * @brief  This function writes the elements of the stack to the stream.
 * @author Izan Robles
 * 
 * @param fp A pointer to the stream
 * @param s A pointer to the element to the stack
 * @return Upon successful return, these function returns the number of characters writted.
 * The function returns a negative value if there was a problem writing to the file.
 *  */
int stack_print(FILE* fp, const Stack *s,  P_stack_ele_print f);

#endif	

