/*
 *  The implementation of stack test.
 *  Copyright (C)  2008 2009  Wangbo
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *  Author e-mail: activesys.wb@gmail.com
 *                 activesys@sina.com.cn
 */

/** include section **/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "cstack.h"
#include "test_stack.h"

/** local constant declaration and local macro section **/
#if defined (CSTL_STACK_VECTOR_SEQUENCE)
#define _STACK_ITERATOR_BEGIN(pt_stack)\
    for(t_iter = vector_begin(&(pt_stack)->_t_sequence);\
        !iterator_equal(t_iter, vector_end(&(pt_stack)->_t_sequence));\
        t_iter = iterator_next(t_iter)){
#elif defined (CSTL_STACK_LIST_SEQUENCE)
#define _STACK_ITERATOR_BEGIN(pt_stack)\
    for(t_iter = list_begin(&(pt_stack)->_t_sequence);\
        !iterator_equal(t_iter, list_end(&(pt_stack)->_t_sequence));\
        t_iter = iterator_next(t_iter)){
#else
#define _STACK_ITERATOR_BEGIN(pt_stack)\
    for(t_iter = deque_begin(&(pt_stack)->_t_sequence);\
        !iterator_equal(t_iter, deque_end(&(pt_stack)->_t_sequence));\
        t_iter = iterator_next(t_iter)){
#endif

#define _STACK_ITERATOR_END }printf("\n");

#define _printstack_c(pt_stack, fmt, type)\
    do{\
        iterator_t t_iter;\
        printf("==================================\n");\
        _STACK_ITERATOR_BEGIN(pt_stack)\
            printf(fmt, *(type*)iterator_get_pointer(t_iter));\
        _STACK_ITERATOR_END\
    }while(false)

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/
static void _print_stack_str(const stack_t* cpt_stack);

static void _printstack(const stack_t* cpt_stack);
static void _printpointer(const stack_t* cpt_stack);
static void _pointer_init(const void* cpv_input, void* pv_output);
static void _pointer_copy(const void* cpv_first, const void* cpv_second, void* pv_output);
static void _pointer_less(const void* cpv_first, const void* cpv_second, void* pv_output);
static void _pointer_destroy(const void* cpv_input, void* pv_output);

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
void test_stack(void)
{
    /* c built-in type */
    {
        /*create_stack     */
        {
            stack_t* pt_stack = create_stack(double);
            if(pt_stack == NULL)
            {
                return;
            }
            stack_init(pt_stack);
            _printstack_c(pt_stack, "%lf, ", double);
            stack_destroy(pt_stack);
        }
        /*stack_init       */
        /*stack_init_copy  */
        {
            stack_t* pt_stack1 = create_stack(int);
            stack_t* pt_stack2 = create_stack(int);
            if(pt_stack1 == NULL || pt_stack2 == NULL)
            {
                return;
            }
            stack_init(pt_stack2);
            stack_push(pt_stack2, 34);
            stack_push(pt_stack2, -345);
            stack_push(pt_stack2, 23);
            _printstack_c(pt_stack2, "%d, ", int);
            stack_init_copy(pt_stack1, pt_stack2);
            _printstack_c(pt_stack1, "%d, ", int);
            stack_destroy(pt_stack1);
            stack_destroy(pt_stack2);
        }
        /*stack_destroy    */
        /*stack_assign     */
        {
            stack_t* pt_stack1 = create_stack(signed long int);
            stack_t* pt_stack2 = create_stack(long);
            if(pt_stack1 == NULL || pt_stack2 == NULL)
            {
                return;
            }
            stack_init(pt_stack1);
            stack_init(pt_stack2);
            stack_assign(pt_stack1, pt_stack2);
            _printstack_c(pt_stack1, "%ld, ", long);
            _printstack_c(pt_stack2, "%ld, ", long);
            stack_push(pt_stack2, 333);
            stack_push(pt_stack2, 120);
            stack_push(pt_stack2, -34);
            stack_push(pt_stack2, 111111);
            stack_assign(pt_stack1, pt_stack2);
            _printstack_c(pt_stack1, "%ld, ", long);
            _printstack_c(pt_stack2, "%ld, ", long);
            while(!stack_empty(pt_stack2))
            {
                stack_pop(pt_stack2);
            }
            stack_assign(pt_stack1, pt_stack2);
            _printstack_c(pt_stack1, "%ld, ", long);
            _printstack_c(pt_stack2, "%ld, ", long);
            stack_destroy(pt_stack1);
            stack_destroy(pt_stack2);
        }
        /*stack_empty      */
        {
            stack_t* pt_stack = create_stack(double);
            if(pt_stack == NULL)
            {
                return;
            }
            stack_init(pt_stack);
            printf("empty : %d, size : %d\n", stack_empty(pt_stack), stack_size(pt_stack));
            stack_push(pt_stack, 128);
            stack_push(pt_stack, 256);
            stack_push(pt_stack, 512);
            printf("empty : %d, size : %d\n", stack_empty(pt_stack), stack_size(pt_stack));
            stack_destroy(pt_stack);
        }
        /*stack_size       */
        /*stack_top        */
        {
            stack_t* pt_stack = create_stack(double);
            if(pt_stack == NULL)
            {
                return;
            }
            stack_init(pt_stack);
            _printstack_c(pt_stack, "%lf, ", double);
            if(stack_top(pt_stack) == NULL)
            {
                printf("top is null!\n");
            }
            stack_push(pt_stack, 23.44);
            stack_push(pt_stack, 0.992);
            stack_push(pt_stack, 22.0);
            _printstack_c(pt_stack, "%lf, ", double);
            if(stack_top(pt_stack) != NULL)
            {
                *(double*)stack_top(pt_stack) = 100.0;
            }
            _printstack_c(pt_stack, "%lf, ", double);
            stack_destroy(pt_stack);
        }
        /*stack_push       */
        {
            stack_t* pt_stack = create_stack(int);
            if(pt_stack == NULL)
            {
                return;
            }
            stack_init(pt_stack);
            stack_push(pt_stack, 12);
            stack_push(pt_stack, 89);
            stack_push(pt_stack, 345);
            stack_push(pt_stack, 90);
            _printstack_c(pt_stack, "%d, ", int);
            while(!stack_empty(pt_stack))
            {
                stack_pop(pt_stack);
                _printstack_c(pt_stack, "%d, ", int);
            }
            stack_destroy(pt_stack);
        }
        /*stack_pop        */
        /*stack_equal      */
        {
            stack_t* pt_stack1 = create_stack(double);
            stack_t* pt_stack2 = create_stack(double);
            if(pt_stack1 == NULL || pt_stack2 == NULL)
            {
                return;
            }
            stack_init(pt_stack1);
            stack_init(pt_stack2);
            _printstack_c(pt_stack1, "%lf, ", double);
            _printstack_c(pt_stack2, "%lf, ", double);
            printf("equal : %d, not equal : %d, ",
                stack_equal(pt_stack1, pt_stack2), stack_not_equal(pt_stack1, pt_stack2));
            printf("less : %d, less equal : %d, ",
                stack_less(pt_stack1, pt_stack2), stack_less_equal(pt_stack1, pt_stack2));
            printf("great : %d, great equal : %d\n",
                stack_great(pt_stack1, pt_stack2), stack_great_equal(pt_stack1, pt_stack2));
            stack_push(pt_stack1, 45.22);
            _printstack_c(pt_stack1, "%lf, ", double);
            _printstack_c(pt_stack2, "%lf, ", double);
            printf("equal : %d, not equal : %d, ",
                stack_equal(pt_stack1, pt_stack2), stack_not_equal(pt_stack1, pt_stack2));
            printf("less : %d, less equal : %d, ",
                stack_less(pt_stack1, pt_stack2), stack_less_equal(pt_stack1, pt_stack2));
            printf("great : %d, great equal : %d\n",
                stack_great(pt_stack1, pt_stack2), stack_great_equal(pt_stack1, pt_stack2));
            stack_push(pt_stack2, 45.22);
            _printstack_c(pt_stack1, "%lf, ", double);
            _printstack_c(pt_stack2, "%lf, ", double);
            printf("equal : %d, not equal : %d, ",
                stack_equal(pt_stack1, pt_stack2), stack_not_equal(pt_stack1, pt_stack2));
            printf("less : %d, less equal : %d, ",
                stack_less(pt_stack1, pt_stack2), stack_less_equal(pt_stack1, pt_stack2));
            printf("great : %d, great equal : %d\n",
                stack_great(pt_stack1, pt_stack2), stack_great_equal(pt_stack1, pt_stack2));
            stack_push(pt_stack1, -18.4909);
            stack_push(pt_stack2, -4.35);
            _printstack_c(pt_stack1, "%lf, ", double);
            _printstack_c(pt_stack2, "%lf, ", double);
            printf("equal : %d, not equal : %d, ",
                stack_equal(pt_stack1, pt_stack2), stack_not_equal(pt_stack1, pt_stack2));
            printf("less : %d, less equal : %d, ",
                stack_less(pt_stack1, pt_stack2), stack_less_equal(pt_stack1, pt_stack2));
            printf("great : %d, great equal : %d\n",
                stack_great(pt_stack1, pt_stack2), stack_great_equal(pt_stack1, pt_stack2));
            stack_push(pt_stack1, 100.0);
            _printstack_c(pt_stack1, "%lf, ", double);
            _printstack_c(pt_stack2, "%lf, ", double);
            printf("equal : %d, not equal : %d, ",
                stack_equal(pt_stack1, pt_stack2), stack_not_equal(pt_stack1, pt_stack2));
            printf("less : %d, less equal : %d, ",
                stack_less(pt_stack1, pt_stack2), stack_less_equal(pt_stack1, pt_stack2));
            printf("great : %d, great equal : %d\n",
                stack_great(pt_stack1, pt_stack2), stack_great_equal(pt_stack1, pt_stack2));
            stack_destroy(pt_stack1);
            stack_destroy(pt_stack2);
        }
        /*stack_not_equal  */
        /*stack_less       */
        /*stack_less_equal */
        /*stack_great      */
        /*stack_great_equal*/
    }
    /* user defined type */
    {
        type_register(int*, _pointer_init, _pointer_copy, _pointer_less, _pointer_destroy);
        _type_debug();
        /*create_stack     */
        {
            stack_t* pt_stack = create_stack(int*);
            if(pt_stack == NULL)
            {
                return;
            }
            stack_init(pt_stack);
            _printpointer(pt_stack);
            stack_destroy(pt_stack);
        }
        /*stack_init       */
        /*stack_init_copy  */
        {
            stack_t* pt_stack1 = create_stack(int*);
            stack_t* pt_stack2 = create_stack(int*);
            int* pn_pointer = NULL;
            bool_t t_result = false;
            if(pt_stack1 == NULL || pt_stack2 == NULL)
            {
                return;
            }
            stack_init(pt_stack2);
            _pointer_init(&pn_pointer, &t_result);
            *pn_pointer = 90;
            stack_push(pt_stack2, &pn_pointer);
            *pn_pointer = 34;
            stack_push(pt_stack2, &pn_pointer);
            *pn_pointer = 1;
            stack_push(pt_stack2, &pn_pointer);
            _pointer_destroy(&pn_pointer, &t_result);
            _printpointer(pt_stack2);
            stack_init_copy(pt_stack1, pt_stack2);
            _printpointer(pt_stack1);
            stack_destroy(pt_stack1);
            stack_destroy(pt_stack2);
        }
        /*stack_destroy    */
        /*stack_assign     */
        {
            stack_t* pt_stack1 = create_stack(int*);
            stack_t* pt_stack2 = create_stack(int*);
            int* pn_pointer = NULL;
            bool_t t_result = false;
            if(pt_stack1 == NULL || pt_stack2 == NULL)
            {
                return;
            }
            stack_init(pt_stack1);
            stack_init(pt_stack2);
            stack_assign(pt_stack1, pt_stack2);
            _printpointer(pt_stack1);
            _printpointer(pt_stack2);

            _pointer_init(&pn_pointer, &t_result);
            *pn_pointer = 77;
            stack_push(pt_stack2, &pn_pointer);
            *pn_pointer = 11;
            stack_push(pt_stack2, &pn_pointer);
            *pn_pointer = 0;
            stack_push(pt_stack2, &pn_pointer);
            _pointer_destroy(&pn_pointer, &t_result);

            stack_assign(pt_stack1, pt_stack2);
            _printpointer(pt_stack1);
            _printpointer(pt_stack2);

            while(!stack_empty(pt_stack2))
            {
                stack_pop(pt_stack2);
            }
            stack_assign(pt_stack1, pt_stack2);
            _printpointer(pt_stack1);
            _printpointer(pt_stack2);

            stack_destroy(pt_stack1);
            stack_destroy(pt_stack2);
        }
        /*stack_empty      */
        {
            stack_t* pt_stack = create_stack(int*);
            int* pn_pointer = NULL;
            bool_t t_result = false;
            if(pt_stack == NULL)
            {
                return;
            }
            stack_init(pt_stack);
            printf("empty : %d, size : %d\n", stack_empty(pt_stack), stack_size(pt_stack));

            _pointer_init(&pn_pointer, &t_result);
            *pn_pointer = 77;
            stack_push(pt_stack, &pn_pointer);
            *pn_pointer = 11;
            stack_push(pt_stack, &pn_pointer);
            *pn_pointer = 0;
            stack_push(pt_stack, &pn_pointer);
            _pointer_destroy(&pn_pointer, &t_result);
            printf("empty : %d, size : %d\n", stack_empty(pt_stack), stack_size(pt_stack));

            stack_destroy(pt_stack);
        }
        /*stack_size       */
        /*stack_top        */
        {
            stack_t* pt_stack = create_stack(int*);
            int* pn_pointer = NULL;
            bool_t t_result = false;
            if(pt_stack == NULL)
            {
                return;
            }
            stack_init(pt_stack);
            _printpointer(pt_stack);
            if(stack_top(pt_stack) == NULL)
            {
                printf("top is null!\n");
            }

            _pointer_init(&pn_pointer, &t_result);
            *pn_pointer = 77;
            stack_push(pt_stack, &pn_pointer);
            *pn_pointer = 11;
            stack_push(pt_stack, &pn_pointer);
            *pn_pointer = 0;
            stack_push(pt_stack, &pn_pointer);
            _pointer_destroy(&pn_pointer, &t_result);
            _printpointer(pt_stack);
            if(stack_top(pt_stack) != NULL)
            {
                **(int**)stack_top(pt_stack) = 100;
            }
            _printpointer(pt_stack);
            stack_destroy(pt_stack);
        }
        /*stack_push       */
        {
            stack_t* pt_stack = create_stack(int*);
            int* pn_pointer = NULL;
            bool_t t_result = false;
            if(pt_stack == NULL)
            {
                return;
            }
            stack_init(pt_stack);
            _pointer_init(&pn_pointer, &t_result);
            *pn_pointer = -37;
            stack_push(pt_stack, &pn_pointer);
            *pn_pointer = 113;
            stack_push(pt_stack, &pn_pointer);
            *pn_pointer = 66;
            stack_push(pt_stack, &pn_pointer);
            *pn_pointer = -40;
            stack_push(pt_stack, &pn_pointer);
            _pointer_destroy(&pn_pointer, &t_result);
            _printpointer(pt_stack);
            while(!stack_empty(pt_stack))
            {
                stack_pop(pt_stack);
                _printpointer(pt_stack);
            }
            stack_destroy(pt_stack);
        }
        /*stack_pop        */
        /*stack_equal      */
        {
            stack_t* pt_stack1 = create_stack(int*);
            stack_t* pt_stack2 = create_stack(int*);
            int* pn_pointer = NULL;
            bool_t t_result = false;
            if(pt_stack1 == NULL || pt_stack2 == NULL)
            {
                return;
            }
            stack_init(pt_stack1);
            stack_init(pt_stack2);
            _printpointer(pt_stack1);
            _printpointer(pt_stack2);
            printf("equal : %d, not equal : %d, ",
                stack_equal(pt_stack1, pt_stack2), stack_not_equal(pt_stack1, pt_stack2));
            printf("less : %d, less equal : %d, ",
                stack_less(pt_stack1, pt_stack2), stack_less_equal(pt_stack1, pt_stack2));
            printf("great : %d, great equal : %d\n",
                stack_great(pt_stack1, pt_stack2), stack_great_equal(pt_stack1, pt_stack2));

            _pointer_init(&pn_pointer, &t_result);

            *pn_pointer = 45;
            stack_push(pt_stack1, &pn_pointer);
            _printpointer(pt_stack1);
            _printpointer(pt_stack2);
            printf("equal : %d, not equal : %d, ",
                stack_equal(pt_stack1, pt_stack2), stack_not_equal(pt_stack1, pt_stack2));
            printf("less : %d, less equal : %d, ",
                stack_less(pt_stack1, pt_stack2), stack_less_equal(pt_stack1, pt_stack2));
            printf("great : %d, great equal : %d\n",
                stack_great(pt_stack1, pt_stack2), stack_great_equal(pt_stack1, pt_stack2));

            *pn_pointer = 45;
            stack_push(pt_stack2, &pn_pointer);
            _printpointer(pt_stack1);
            _printpointer(pt_stack2);
            printf("equal : %d, not equal : %d, ",
                stack_equal(pt_stack1, pt_stack2), stack_not_equal(pt_stack1, pt_stack2));
            printf("less : %d, less equal : %d, ",
                stack_less(pt_stack1, pt_stack2), stack_less_equal(pt_stack1, pt_stack2));
            printf("great : %d, great equal : %d\n",
                stack_great(pt_stack1, pt_stack2), stack_great_equal(pt_stack1, pt_stack2));

            *pn_pointer = -18;
            stack_push(pt_stack1, &pn_pointer);
            *pn_pointer = -4;
            stack_push(pt_stack2, &pn_pointer);
            _printpointer(pt_stack1);
            _printpointer(pt_stack2);
            printf("equal : %d, not equal : %d, ",
                stack_equal(pt_stack1, pt_stack2), stack_not_equal(pt_stack1, pt_stack2));
            printf("less : %d, less equal : %d, ",
                stack_less(pt_stack1, pt_stack2), stack_less_equal(pt_stack1, pt_stack2));
            printf("great : %d, great equal : %d\n",
                stack_great(pt_stack1, pt_stack2), stack_great_equal(pt_stack1, pt_stack2));

            *pn_pointer = 100;
            stack_push(pt_stack1, &pn_pointer);
            _printpointer(pt_stack1);
            _printpointer(pt_stack2);
            printf("equal : %d, not equal : %d, ",
                stack_equal(pt_stack1, pt_stack2), stack_not_equal(pt_stack1, pt_stack2));
            printf("less : %d, less equal : %d, ",
                stack_less(pt_stack1, pt_stack2), stack_less_equal(pt_stack1, pt_stack2));
            printf("great : %d, great equal : %d\n",
                stack_great(pt_stack1, pt_stack2), stack_great_equal(pt_stack1, pt_stack2));

            _pointer_destroy(&pn_pointer, &t_result);

            stack_destroy(pt_stack1);
            stack_destroy(pt_stack2);
        }
        /*stack_not_equal  */
        /*stack_less       */
        /*stack_less_equal */
        /*stack_great      */
        /*stack_great_equal*/
    }
    /* cstl built-in type */
    {
        /*create_stack     */
        {
            stack_t* pt_stack = create_stack(stack_t<int>);
            if(pt_stack == NULL)
            {
                return;
            }
            stack_init(pt_stack);
            _printstack(pt_stack);
            stack_destroy(pt_stack);
        }
        /*stack_init       */
        /*stack_init_copy  */
        {
            stack_t* pt_stack1 = create_stack(stack_t<int>);
            stack_t* pt_stack2 = create_stack(stack_t<int>);
            stack_t* pt_stackex = create_stack(int);
            if(pt_stack1 == NULL || pt_stack2 == NULL || pt_stackex == NULL)
            {
                return;
            }
            stack_init(pt_stackex);
            stack_init(pt_stack2);
            stack_push(pt_stackex, 34);
            stack_push(pt_stack2, pt_stackex);
            stack_push(pt_stackex, 90);
            stack_push(pt_stack2, pt_stackex);
            stack_push(pt_stackex, 123);
            stack_push(pt_stack2, pt_stackex);
            stack_init_copy(pt_stack1, pt_stack2);
            _printstack(pt_stack1);
            stack_destroy(pt_stack1);
            stack_destroy(pt_stack2);
            stack_destroy(pt_stackex);
        }
        /*stack_destroy    */
        /*stack_assign     */
        {
            stack_t* pt_stack1 = create_stack(stack_t<int>);
            stack_t* pt_stack2 = create_stack(stack_t<int>);
            stack_t* pt_stackex = create_stack(int);
            if(pt_stack1 == NULL || pt_stack2 == NULL || pt_stackex == NULL)
            {
                return;
            }
            stack_init(pt_stackex);
            stack_init(pt_stack1);
            stack_init(pt_stack2);
            stack_assign(pt_stack1, pt_stack2);
            _printstack(pt_stack1);

            stack_push(pt_stackex, 34);
            stack_push(pt_stack2, pt_stackex);
            stack_push(pt_stackex, 90);
            stack_push(pt_stack2, pt_stackex);
            stack_push(pt_stackex, 123);
            stack_push(pt_stack2, pt_stackex);
            stack_assign(pt_stack1, pt_stack2);
            _printstack(pt_stack1);

            stack_push(pt_stackex, -3);
            stack_push(pt_stack2, pt_stackex);
            stack_push(pt_stack2, pt_stackex);
            stack_push(pt_stack2, pt_stackex);
            stack_assign(pt_stack1, pt_stack2);
            _printstack(pt_stack1);

            stack_pop(pt_stack2);
            stack_pop(pt_stack2);
            stack_assign(pt_stack1, pt_stack2);
            _printstack(pt_stack1);

            while(!stack_empty(pt_stack2))
            {
                stack_pop(pt_stack2);
            }
            stack_assign(pt_stack1, pt_stack2);
            _printstack(pt_stack1);

            stack_destroy(pt_stack1);
            stack_destroy(pt_stack2);
            stack_destroy(pt_stackex);
        }
        /*stack_empty      */
        {
            stack_t* pt_stack = create_stack(stack_t<int>);
            stack_t* pt_stackex = create_stack(int);
            if(pt_stack == NULL || pt_stackex == NULL)
            {
                return;
            }
            stack_init(pt_stack);
            stack_init(pt_stackex);
            printf("empty : %d, size : %d\n", stack_empty(pt_stack), stack_size(pt_stack));
            stack_push(pt_stack, pt_stackex);
            stack_push(pt_stack, pt_stackex);
            stack_push(pt_stack, pt_stackex);
            printf("empty : %d, size : %d\n", stack_empty(pt_stack), stack_size(pt_stack));
            stack_destroy(pt_stack);
            stack_destroy(pt_stackex);
        }
        /*stack_size       */
        /*stack_top        */
        {
            stack_t* pt_stack = create_stack(stack_t<int>);
            stack_t* pt_stackex = create_stack(int);
            if(pt_stack == NULL || pt_stackex == NULL)
            {
                return;
            }
            stack_init(pt_stack);
            stack_init(pt_stackex);
            _printstack(pt_stack);
            if(stack_top(pt_stack) == NULL)
            {
                printf("top is null!\n");
            }
            stack_push(pt_stackex, 23);
            stack_push(pt_stack, pt_stackex);
            stack_push(pt_stackex, 0);
            stack_push(pt_stack, pt_stackex);
            stack_push(pt_stackex, 22);
            stack_push(pt_stack, pt_stackex);
            _printstack(pt_stack);
            if(stack_top(pt_stack) != NULL)
            {
                stack_push(stack_top(pt_stack), 100);
            }
            _printstack(pt_stack);
            stack_destroy(pt_stack);
            stack_destroy(pt_stackex);
        }
        /*stack_push       */
        {
            stack_t* pt_stack = create_stack(stack_t<int>);
            stack_t* pt_stackex = create_stack(int);
            if(pt_stack == NULL || pt_stackex == NULL)
            {
                return;
            }
            stack_init(pt_stack);
            stack_init(pt_stackex);
            stack_push(pt_stackex, 12);
            stack_push(pt_stack, pt_stackex);
            stack_push(pt_stackex, 89);
            stack_push(pt_stack, pt_stackex);
            stack_push(pt_stackex, 345);
            stack_push(pt_stack, pt_stackex);
            stack_push(pt_stackex, 90);
            stack_push(pt_stack, pt_stackex);
            _printstack(pt_stack);
            while(!stack_empty(pt_stack))
            {
                stack_pop(pt_stack);
                _printstack(pt_stack);
            }
            stack_destroy(pt_stack);
            stack_destroy(pt_stackex);
        }
        /*stack_pop        */
        /*stack_equal      */
        {
            stack_t* pt_stack1 = create_stack(stack_t<int>);
            stack_t* pt_stack2 = create_stack(stack_t<int>);
            stack_t* pt_stackex = create_stack(int);
            if(pt_stack1 == NULL || pt_stack2 == NULL || pt_stackex == NULL)
            {
                return;
            }
            stack_init(pt_stack1);
            stack_init(pt_stack2);
            stack_init(pt_stackex);
            _printstack(pt_stack1);
            _printstack(pt_stack2);
            printf("equal : %d, not equal : %d, ",
                stack_equal(pt_stack1, pt_stack2), stack_not_equal(pt_stack1, pt_stack2));
            printf("less : %d, less equal : %d, ",
                stack_less(pt_stack1, pt_stack2), stack_less_equal(pt_stack1, pt_stack2));
            printf("great : %d, great equal : %d\n",
                stack_great(pt_stack1, pt_stack2), stack_great_equal(pt_stack1, pt_stack2));
            stack_push(pt_stackex, 45);
            stack_push(pt_stack1, pt_stackex);
            _printstack(pt_stack1);
            _printstack(pt_stack2);
            printf("equal : %d, not equal : %d, ",
                stack_equal(pt_stack1, pt_stack2), stack_not_equal(pt_stack1, pt_stack2));
            printf("less : %d, less equal : %d, ",
                stack_less(pt_stack1, pt_stack2), stack_less_equal(pt_stack1, pt_stack2));
            printf("great : %d, great equal : %d\n",
                stack_great(pt_stack1, pt_stack2), stack_great_equal(pt_stack1, pt_stack2));
            stack_push(pt_stack2, pt_stackex);
            _printstack(pt_stack1);
            _printstack(pt_stack2);
            printf("equal : %d, not equal : %d, ",
                stack_equal(pt_stack1, pt_stack2), stack_not_equal(pt_stack1, pt_stack2));
            printf("less : %d, less equal : %d, ",
                stack_less(pt_stack1, pt_stack2), stack_less_equal(pt_stack1, pt_stack2));
            printf("great : %d, great equal : %d\n",
                stack_great(pt_stack1, pt_stack2), stack_great_equal(pt_stack1, pt_stack2));
            stack_pop(pt_stackex);
            stack_push(pt_stackex, -18);
            stack_push(pt_stack1, pt_stackex);
            stack_pop(pt_stackex);
            stack_push(pt_stackex, -4);
            stack_push(pt_stack2, pt_stackex);
            _printstack(pt_stack1);
            _printstack(pt_stack2);
            printf("equal : %d, not equal : %d, ",
                stack_equal(pt_stack1, pt_stack2), stack_not_equal(pt_stack1, pt_stack2));
            printf("less : %d, less equal : %d, ",
                stack_less(pt_stack1, pt_stack2), stack_less_equal(pt_stack1, pt_stack2));
            printf("great : %d, great equal : %d\n",
                stack_great(pt_stack1, pt_stack2), stack_great_equal(pt_stack1, pt_stack2));
            stack_pop(pt_stackex);
            stack_push(pt_stackex, 100);
            stack_push(pt_stack1, pt_stackex);
            _printstack(pt_stack1);
            _printstack(pt_stack2);
            printf("equal : %d, not equal : %d, ",
                stack_equal(pt_stack1, pt_stack2), stack_not_equal(pt_stack1, pt_stack2));
            printf("less : %d, less equal : %d, ",
                stack_less(pt_stack1, pt_stack2), stack_less_equal(pt_stack1, pt_stack2));
            printf("great : %d, great equal : %d\n",
                stack_great(pt_stack1, pt_stack2), stack_great_equal(pt_stack1, pt_stack2));
            stack_destroy(pt_stack1);
            stack_destroy(pt_stack2);
            stack_destroy(pt_stackex);
        }
        /*stack_not_equal  */
        /*stack_less       */
        /*stack_less_equal */
        /*stack_great      */
        /*stack_great_equal*/
    }
    /* c-string type */
    {
        printf("************************************************\n");
        /*create_stack     */
        {
            stack_t* pt_stack = create_stack(char*);
            if(pt_stack == NULL)
            {
                return;
            }
            stack_init(pt_stack);
            _print_stack_str(pt_stack);
            stack_destroy(pt_stack);
        }
        /*stack_init       */
        /*stack_init_copy  */
        {
            stack_t* pt_stack = create_stack(char*);
            stack_t* pt_stackex = create_stack(char*);
            if(pt_stack == NULL || pt_stackex == NULL)
            {
                return;
            }
            stack_init(pt_stackex);
            stack_push(pt_stackex, "Eventual");
            stack_push(pt_stackex, "Email: cherylp@stac.com");
            stack_init_copy(pt_stack, pt_stackex);
            _print_stack_str(pt_stack);
            stack_destroy(pt_stack);
            stack_destroy(pt_stackex);
        }
        /*stack_destroy    */
        /*stack_assign     */
        {
            stack_t* pt_stack = create_stack(char*);
            stack_t* pt_stackex = create_stack(char*);
            if(pt_stack == NULL || pt_stackex == NULL)
            {
                return;
            }
            stack_init(pt_stackex);
            stack_init(pt_stack);
            stack_assign(pt_stack, pt_stackex);
            _print_stack_str(pt_stack);
            stack_push(pt_stackex, "CIDR as the solution for the short term routing table");
            stack_push(pt_stackex, "explosion problem [1].");
            stack_assign(pt_stack, pt_stackex);
            _print_stack_str(pt_stack);
            while(!stack_empty(pt_stackex))
            {
                stack_pop(pt_stackex);
            }
            stack_push(pt_stackex, "supporting, rather than defining, documents.");
            stack_push(pt_stackex, "Applicability of CIDR");
            stack_push(pt_stackex, "This Applicability Statement requires Internet");
            stack_push(pt_stackex, "significantly slower than");
            stack_push(pt_stackex, "");
            stack_assign(pt_stack, pt_stackex);
            _print_stack_str(pt_stack);

            while(!stack_empty(pt_stackex))
            {
                stack_pop(pt_stackex);
            }
            stack_assign(pt_stack, pt_stackex);
            _print_stack_str(pt_stack);
            
            stack_destroy(pt_stack);
            stack_destroy(pt_stackex);
        }
        /*stack_empty      */
        /*stack_size       */
        /*stack_top        */
        /*stack_push       */
        /*stack_pop        */
        {
            stack_t* pt_stack = create_stack(char*);
            if(pt_stack == NULL)
            {
                return;
            }
            stack_init(pt_stack);
            _print_stack_str(pt_stack);
            stack_push(pt_stack, "(1)  The SNMP protocol");
            puts(stack_top(pt_stack));
            stack_push(pt_stack, "(2)  For each such party");
            puts(stack_top(pt_stack));
            stack_push(pt_stack, "(3)  For each such access control entry");
            puts(stack_top(pt_stack));
            stack_push(pt_stack, "(4)  Whenever such a party");
            puts(stack_top(pt_stack));
            _print_stack_str(pt_stack);
            while(!stack_empty(pt_stack))
            {
                stack_pop(pt_stack);
            }
            _print_stack_str(pt_stack);
            stack_destroy(pt_stack);
        }
        /*stack_equal      */
        /*stack_not_equal  */
        /*stack_less       */
        /*stack_less_equal */
        /*stack_great      */
        /*stack_great_equal*/
        {
            stack_t* pt_stack = create_stack(char*);
            stack_t* pt_stackex = create_stack(char*);
            if(pt_stack == NULL || pt_stackex == NULL)
            {
                return;
            }
            stack_init(pt_stack);
            stack_init(pt_stackex);
            _print_stack_str(pt_stack);
            _print_stack_str(pt_stackex);
            printf("equal: %d, not equal: %d, ",
                stack_equal(pt_stack, pt_stackex), stack_not_equal(pt_stack, pt_stackex));
            printf("less: %d, less equal: %d, ",
                stack_less(pt_stack, pt_stackex), stack_less_equal(pt_stack, pt_stackex));
            printf("great: %d, great equal: %d\n",
                stack_great(pt_stack, pt_stackex), stack_great_equal(pt_stack, pt_stackex));

            stack_push(pt_stack, "Only those instances corresponding to parties in the");
            _print_stack_str(pt_stack);
            _print_stack_str(pt_stackex);
            printf("equal: %d, not equal: %d, ",
                stack_equal(pt_stack, pt_stackex), stack_not_equal(pt_stack, pt_stackex));
            printf("less: %d, less equal: %d, ",
                stack_less(pt_stack, pt_stackex), stack_less_equal(pt_stack, pt_stackex));
            printf("great: %d, great equal: %d\n",
                stack_great(pt_stack, pt_stackex), stack_great_equal(pt_stack, pt_stackex));

            stack_push(pt_stackex, "Only those instances corresponding to parties in the");
            _print_stack_str(pt_stack);
            _print_stack_str(pt_stackex);
            printf("equal: %d, not equal: %d, ",
                stack_equal(pt_stack, pt_stackex), stack_not_equal(pt_stack, pt_stackex));
            printf("less: %d, less equal: %d, ",
                stack_less(pt_stack, pt_stackex), stack_less_equal(pt_stack, pt_stackex));
            printf("great: %d, great equal: %d\n",
                stack_great(pt_stack, pt_stackex), stack_great_equal(pt_stack, pt_stackex));

            stack_push(pt_stackex, "Whenever the SNMP");
            _print_stack_str(pt_stack);
            _print_stack_str(pt_stackex);
            printf("equal: %d, not equal: %d, ",
                stack_equal(pt_stack, pt_stackex), stack_not_equal(pt_stack, pt_stackex));
            printf("less: %d, less equal: %d, ",
                stack_less(pt_stack, pt_stackex), stack_less_equal(pt_stack, pt_stackex));
            printf("great: %d, great equal: %d\n",
                stack_great(pt_stack, pt_stackex), stack_great_equal(pt_stack, pt_stackex));

            stack_push(pt_stack, "For each instance");
            stack_push(pt_stack, "The SNMP protocol engine");
            _print_stack_str(pt_stack);
            _print_stack_str(pt_stackex);
            printf("equal: %d, not equal: %d, ",
                stack_equal(pt_stack, pt_stackex), stack_not_equal(pt_stack, pt_stackex));
            printf("less: %d, less equal: %d, ",
                stack_less(pt_stack, pt_stackex), stack_less_equal(pt_stack, pt_stackex));
            printf("great: %d, great equal: %d\n",
                stack_great(pt_stack, pt_stackex), stack_great_equal(pt_stack, pt_stackex));

            stack_destroy(pt_stack);
            stack_destroy(pt_stackex);
        }
    }
}

/** local function implementation section **/
static void _print_stack_str(const stack_t* cpt_stack)
{
    iterator_t t_pos;
    assert(cpt_stack != NULL);
    printf("+++++++++++++++++++++++++++++++++++++\n");
    printf("empty: %u, size: %u\n", stack_empty(cpt_stack), stack_size(cpt_stack));
#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    for(t_pos = vector_begin(&cpt_stack->_t_sequence);
        !iterator_equal(t_pos, vector_end(&cpt_stack->_t_sequence));
        t_pos = iterator_next(t_pos))
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    for(t_pos = list_begin(&cpt_stack->_t_sequence);
        !iterator_equal(t_pos, list_end(&cpt_stack->_t_sequence));
        t_pos = iterator_next(t_pos))
#else
    for(t_pos = deque_begin(&cpt_stack->_t_sequence);
        !iterator_equal(t_pos, deque_end(&cpt_stack->_t_sequence));
        t_pos = iterator_next(t_pos))
#endif
    {
        puts(iterator_get_pointer(t_pos));
    }
}

static void _printstack(const stack_t* cpt_stack)
{
    iterator_t t_pos;
    assert(cpt_stack != NULL);
    printf("+++++++++++++++++++++++++++++++++++++\n");
#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    for(t_pos = vector_begin(&cpt_stack->_t_sequence);
        !iterator_equal(t_pos, vector_end(&cpt_stack->_t_sequence));
        t_pos = iterator_next(t_pos))
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    for(t_pos = list_begin(&cpt_stack->_t_sequence);
        !iterator_equal(t_pos, list_end(&cpt_stack->_t_sequence));
        t_pos = iterator_next(t_pos))
#else
    for(t_pos = deque_begin(&cpt_stack->_t_sequence);
        !iterator_equal(t_pos, deque_end(&cpt_stack->_t_sequence));
        t_pos = iterator_next(t_pos))
#endif
    {
        _printstack_c((stack_t*)iterator_get_pointer(t_pos), "%d, ", int);
    }
}

static void _printpointer(const stack_t* cpt_stack)
{
    iterator_t t_iter;
    int* pn_pointer = NULL;
    assert(cpt_stack != NULL);

    printf("=====================================\n");
#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    for(t_iter = vector_begin(&cpt_stack->_t_sequence);
        !iterator_equal(t_iter, vector_end(&cpt_stack->_t_sequence));
        t_iter = iterator_next(t_iter))
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    for(t_iter = list_begin(&cpt_stack->_t_sequence);
        !iterator_equal(t_iter, list_end(&cpt_stack->_t_sequence));
        t_iter = iterator_next(t_iter))
#else
    for(t_iter = deque_begin(&cpt_stack->_t_sequence);
        !iterator_equal(t_iter, deque_end(&cpt_stack->_t_sequence));
        t_iter = iterator_next(t_iter))
#endif
    {
        pn_pointer = *(int**)iterator_get_pointer(t_iter);
        assert(pn_pointer != NULL);
        printf("(p:%p, v:%d), ", pn_pointer, *pn_pointer);
    }
    printf("\n");
}

static void _pointer_init(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    *(int**)cpv_input = (int*)malloc(sizeof(int));
    if(*(int**)cpv_input != NULL)
    {
        **(int**)cpv_input = 0;
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}

static void _pointer_copy(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    **(int**)cpv_first = **(int**)cpv_second;
    *(bool_t*)pv_output = true;
}

static void _pointer_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    if(**(int**)cpv_first < **(int**)cpv_second)
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}

static void _pointer_destroy(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    if(*(int**)cpv_input != NULL)
    {
        free(*(int**)cpv_input);
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}

/** eof **/

