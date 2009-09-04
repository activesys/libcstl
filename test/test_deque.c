/*
 *  The implementation of deque test.
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
#include "cdeque.h"
/*#include "cvector.h"*/
#include "test_deque.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/
typedef struct _tagdeqabc
{
    double d_first;
    int    n_second;
}deqabc_t;

/** local function prototype section **/
static void _printdeque_user(const deque_t* pt_deque);

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
void test_deque(void)
{
    /* c builtin type */
    {
        /* create_deque(), deque_init(), deque_destroy() */
        {
            deque_t* pt_deq = create_deque(int);
            if(pt_deq == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            deque_destroy(pt_deq);
        }
        /* deque_init_n() */
        {
            deque_t* pt_deq = create_deque(double);
            if(pt_deq == NULL)
            {
                return;
            }
            deque_init_n(pt_deq, 10);
            deque_destroy(pt_deq);
        }
        /* deque_init_elem() */
        {
            deque_t* pt_deq = create_deque(long);
            iterator_t t_iter;
            if(pt_deq == NULL)
            {
                return;
            }
            deque_init_elem(pt_deq, 18, 2147483647);
            printf("size : %d\n", deque_size(pt_deq));
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%ld, ", *(long*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_destroy(pt_deq);
        }
        /* deque_init_copy() */
        {
            deque_t* pt_deq = create_deque(long);
            deque_t* pt_deqex = create_deque(signed long int);
            iterator_t t_iter;
            if(pt_deq == NULL || pt_deqex == NULL)
            {
                return;
            }
            deque_init_elem(pt_deqex, 9999, 333);
            deque_init_copy(pt_deq, pt_deqex);
            printf("size : %d\n", deque_size(pt_deq));
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%ld, ", *(long*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_destroy(pt_deq);
            deque_destroy(pt_deqex);
        }
        /* deque_init_copy_range() */
        {
            deque_t* pt_deq = create_deque(long);
            deque_t* pt_deqex = create_deque(signed long int);
            iterator_t t_iter;
            if(pt_deq == NULL || pt_deqex == NULL)
            {
                return;
            }
            deque_init_n(pt_deqex, 38);
            deque_init_copy_range(pt_deq,
                iterator_next_n(deque_begin(pt_deqex), 20), deque_end(pt_deqex));
            printf("size : %d\n", deque_size(pt_deq));
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%ld, ", *(long*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_destroy(pt_deq);
            deque_destroy(pt_deqex);
        }
        /* deque_empty() */
        {
            deque_t* pt_deq = create_deque(double);
            if(pt_deq == NULL)
            {
                return;
            }
            deque_init_n(pt_deq, 5);
            printf("empty : %d\n", deque_empty(pt_deq));
            deque_destroy(pt_deq);
        }
        /* deque_size() */
        {
            deque_t* pt_deq = create_deque(int);
            if(pt_deq == NULL)
            {
                return;
            }
            deque_init_n(pt_deq, 12345);
            printf("size : %d\n", deque_size(pt_deq));
            deque_destroy(pt_deq);
        }
        /* deque_max_size() */
        {
            deque_t* pt_deq = create_deque(long double);
            if(pt_deq == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            printf("max size : %d\n", deque_max_size(pt_deq));
            deque_destroy(pt_deq);
        }
        /* deque_equal() */
        {
            deque_t* pt_deq = create_deque(signed);
            deque_t* pt_deqex = create_deque(int);
            if(pt_deq == NULL || pt_deqex == NULL)
            {
                return;
            }
            deque_init_elem(pt_deq, 3, 3);
            deque_init_elem(pt_deqex, 4, 2);
            printf("equal : %d, not equal : %d\n",
                deque_equal(pt_deq, pt_deqex),
                deque_not_equal(pt_deq, pt_deqex));
            printf("less : %d, less equal : %d\n",
                deque_less(pt_deq, pt_deqex),
                deque_less_equal(pt_deq, pt_deqex));
            printf("great : %d, great equal : %d\n",
                deque_great(pt_deq, pt_deqex),
                deque_great_equal(pt_deq, pt_deqex));
            deque_destroy(pt_deq);
            deque_destroy(pt_deqex);
        }
        /* deque_not_equal() */
        {
        }
        /* deque_less() */
        {
        }
        /* deque_less_equal() */
        {
        }
        /* deque_great() */
        {
        }
        /* deque_great_equal() */
        {
        }
        /* deque_assign() */
        {
            deque_t* pt_deq = create_deque(int);
            deque_t* pt_deqex = create_deque(signed int);
            iterator_t t_iter;
            if(pt_deq == NULL || pt_deqex == NULL)
            {
                return;
            }
            deque_init_elem(pt_deq, 10, -3);
            deque_init_elem(pt_deqex, 0, 100);
            printf("before assign:\n");
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_assign(pt_deq, pt_deqex);
            printf("after assign:\n");
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_destroy(pt_deq);
            deque_destroy(pt_deqex);
        }
        /* deque_assign_elem() */
        {
            deque_t* pt_deq = create_deque(int);
            iterator_t t_iter;
            if(pt_deq == NULL)
            {
                return;
            }
            deque_init_elem(pt_deq, 140, -3);
            printf("before assign:\n");
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_assign_elem(pt_deq, 50, -77);
            printf("after assign:\n");
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_destroy(pt_deq);
        }
        /* deque_assign_range() */
        {
            deque_t* pt_deq = create_deque(int);
            deque_t* pt_deqex = create_deque(signed int);
            iterator_t t_iter;
            if(pt_deq == NULL || pt_deqex == NULL)
            {
                return;
            }
            deque_init_elem(pt_deq, 3, -3);
            deque_init_elem(pt_deqex, 50, 100);
            printf("before assign:\n");
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_assign_range(pt_deq, deque_begin(pt_deqex), deque_end(pt_deqex));
            printf("after assign:\n");
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_destroy(pt_deq);
            deque_destroy(pt_deqex);
        }
        /* deque_swap() */
        {
            deque_t* pt_deq = create_deque(int);
            deque_t* pt_deqex = create_deque(signed int);
            iterator_t t_iter;
            iterator_t t_iterex;
            if(pt_deq == NULL || pt_deqex == NULL)
            {
                return;
            }
            deque_init_elem(pt_deq, 5, -3);
            deque_init_elem(pt_deqex, 9, 100);
            printf("before swap:\n");
            printf("pt_deq:\n");
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iter));
            }
            printf("\npt_depex:\n");
            for(t_iterex = deque_begin(pt_deqex);
                !iterator_equal(t_iterex, deque_end(pt_deqex));
                t_iterex = iterator_next(t_iterex))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iterex));
            }
            printf("\n");
            deque_swap(pt_deq, pt_deqex);
            printf("after swap:\n");
            printf("pt_deq:\n");
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iter));
            }
            printf("\npt_depex:\n");
            for(t_iterex = deque_begin(pt_deqex);
                !iterator_equal(t_iterex, deque_end(pt_deqex));
                t_iterex = iterator_next(t_iterex))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iterex));
            }
            printf("\n");
            deque_destroy(pt_deq);
            deque_destroy(pt_deqex);
        }
        /* deque_at() */
        {
            deque_t* pt_deq = create_deque(double);
            if(pt_deq == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            deque_push_back(pt_deq, 3.5);
            deque_push_back(pt_deq, 90.4e-2);
            printf("%lf\n", *(double*)deque_at(pt_deq, 1));
            *(double*)deque_at(pt_deq, 0) = -100.2;
            printf("%lf\n", *(double*)deque_at(pt_deq, 0));
            deque_destroy(pt_deq);
        }
        /* deque_front() */
        {
            deque_t* pt_deq = create_deque(double);
            if(pt_deq == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            if(deque_front(pt_deq) == NULL)
            {
                printf("NULL\n");
            }
            else
            {
                printf("%lf\n", *(double*)deque_front(pt_deq));
            }
            deque_push_back(pt_deq, 3.5);
            deque_push_back(pt_deq, 90.4e-2);
            if(deque_front(pt_deq) == NULL)
            {
                printf("NULL\n");
            }
            else
            {
                printf("%lf\n", *(double*)deque_front(pt_deq));
            }
            deque_push_front(pt_deq, -34.56);
            if(deque_front(pt_deq) == NULL)
            {
                printf("NULL\n");
            }
            else
            {
                printf("%lf\n", *(double*)deque_front(pt_deq));
            }
            deque_destroy(pt_deq);
        }
        /* deque_back() */
        {
            deque_t* pt_deq = create_deque(double);
            if(pt_deq == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            if(deque_back(pt_deq) == NULL)
            {
                printf("NULL\n");
            }
            else
            {
                printf("%lf\n", *(double*)deque_back(pt_deq));
            }
            deque_push_back(pt_deq, 3.5);
            deque_push_back(pt_deq, 90.4e-2);
            if(deque_back(pt_deq) == NULL)
            {
                printf("NULL\n");
            }
            else
            {
                printf("%lf\n", *(double*)deque_back(pt_deq));
            }
            deque_push_front(pt_deq, -34.56);
            if(deque_back(pt_deq) == NULL)
            {
                printf("NULL\n");
            }
            else
            {
                printf("%lf\n", *(double*)deque_back(pt_deq));
            }
            deque_destroy(pt_deq);
        }
        /* deque_begin() */
        {
        }
        /* deque_end() */
        {
        }
        /* deque_insert() */
        {
            deque_t* pt_deq = create_deque(int);
            iterator_t t_iter;
            if(pt_deq == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_insert(pt_deq, deque_begin(pt_deq), 34);
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_insert(pt_deq, deque_end(pt_deq), -89);
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_insert(pt_deq, iterator_prev(deque_end(pt_deq)), 589);
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_destroy(pt_deq);
        }
        /* deque_insert_n() */
        {
            deque_t* pt_deq = create_deque(int);
            iterator_t t_iter;
            if(pt_deq == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_insert_n(pt_deq, deque_begin(pt_deq), 3, -23);
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_insert_n(pt_deq, deque_end(pt_deq), 2, 90);
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_insert_n(pt_deq, iterator_next(deque_begin(pt_deq)), 5, 566);
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_destroy(pt_deq);
        }
        /* deque_insert_range() */
        {
            deque_t* pt_deq = create_deque(int);
            deque_t* pt_deqex = create_deque(int);
            iterator_t t_iter;
            if(pt_deq == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            deque_init_elem(pt_deqex, 4, 90);
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_insert_range(pt_deq, deque_begin(pt_deq),
                deque_begin(pt_deqex), deque_end(pt_deqex));
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_insert_range(pt_deq, deque_end(pt_deq),
                deque_begin(pt_deqex), deque_begin(pt_deqex));
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_push_front(pt_deqex, -345);
            deque_push_back(pt_deqex, -2222);
            deque_insert_range(pt_deq, iterator_next(deque_begin(pt_deq)),
                deque_begin(pt_deqex), deque_end(pt_deqex));
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_push_front(pt_deqex, 345);
            deque_push_back(pt_deqex, 2222);
            deque_insert_range(pt_deq, deque_end(pt_deq),
                deque_begin(pt_deqex), deque_end(pt_deqex));
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_destroy(pt_deq);
        }
        /* deque_push_back() */
        {
            deque_t* pt_deq = create_deque(double);
            iterator_t t_iter;
            if(pt_deq == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%g, ", *(double*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_push_back(pt_deq, 23.490);
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%g, ", *(double*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_pop_front(pt_deq);
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%g, ", *(double*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_push_front(pt_deq, 21.09e-3);
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%g, ", *(double*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_pop_back(pt_deq);
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%g, ", *(double*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_push_back(pt_deq, 3.e-2);
            deque_push_back(pt_deq, -5.2);
            deque_push_front(pt_deq, 11.111);
            deque_push_front(pt_deq, 0.9);
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%g, ", *(double*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_pop_front(pt_deq);
            deque_pop_back(pt_deq);
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%g, ", *(double*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_destroy(pt_deq);
        }
        /* deque_pop_back() */
        {
        }
        /* deque_push_front() */
        {
        }
        /* deque_pop_front() */
        {
        }
        /* deque_erase() */
        {
            deque_t* pt_deq = create_deque(int);
            iterator_t t_iter;
            if(pt_deq == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            deque_push_back(pt_deq, 12);
            deque_push_back(pt_deq, 98);
            deque_push_back(pt_deq, 2222);
            deque_push_back(pt_deq, -56);
            deque_push_back(pt_deq, 33);
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_erase(pt_deq, iterator_prev(deque_end(pt_deq)));
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_erase(pt_deq, deque_begin(pt_deq));
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_erase(pt_deq, iterator_next(deque_begin(pt_deq)));
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_erase(pt_deq, deque_begin(pt_deq));
            deque_erase(pt_deq, deque_begin(pt_deq));
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_destroy(pt_deq);
        }
        /* deque_erase_range() */
        {
            deque_t* pt_deq = create_deque(int);
            iterator_t t_iter;
            if(pt_deq == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            deque_push_back(pt_deq, 1);
            deque_push_back(pt_deq, 9);
            deque_push_back(pt_deq, 22);
            deque_push_back(pt_deq, -6);
            deque_push_back(pt_deq, 39);
            deque_push_back(pt_deq, 72);
            deque_push_back(pt_deq, 898);
            deque_push_back(pt_deq, 5522);
            deque_push_back(pt_deq, 56);
            deque_push_back(pt_deq, 33);
            deque_push_back(pt_deq, -12);
            deque_push_back(pt_deq, -98);
            deque_push_back(pt_deq, -222);
            deque_push_back(pt_deq, -56);
            deque_push_back(pt_deq, 33);
            deque_push_back(pt_deq, -12);
            deque_push_back(pt_deq, 98);
            deque_push_back(pt_deq, 2222);
            deque_push_back(pt_deq, -56);
            deque_push_back(pt_deq, -33);
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_erase_range(pt_deq, deque_begin(pt_deq), deque_begin(pt_deq));
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_erase_range(pt_deq,
                deque_begin(pt_deq), iterator_next_n(deque_begin(pt_deq), 3));
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_erase_range(pt_deq,
                iterator_prev_n(deque_end(pt_deq), 2), deque_end(pt_deq));
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_erase_range(pt_deq,
                iterator_next_n(deque_begin(pt_deq), 2), iterator_prev_n(deque_end(pt_deq), 2));
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_erase_range(pt_deq, deque_begin(pt_deq), deque_end(pt_deq));
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_destroy(pt_deq);
        }
        /* deque_clear() */
        {
            deque_t* pt_deq = create_deque(int);
            iterator_t t_iter;
            if(pt_deq == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_clear(pt_deq);
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_push_back(pt_deq, -12);
            deque_push_back(pt_deq, 98);
            deque_push_back(pt_deq, 2222);
            deque_push_back(pt_deq, -56);
            deque_push_back(pt_deq, -33);
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_clear(pt_deq);
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_destroy(pt_deq);
        }
        /* deque_resize() */
        {
            deque_t* pt_deq = create_deque(int);
            iterator_t t_iter;
            if(pt_deq == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_resize(pt_deq, 50);
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_resize(pt_deq, 67);
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_resize(pt_deq, 36);
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_resize(pt_deq, 0);
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_destroy(pt_deq);
        }
        /* deque_resize_elem() */
        {
            deque_t* pt_deq = create_deque(int);
            iterator_t t_iter;
            if(pt_deq == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_resize_elem(pt_deq, 50, 44);
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_resize_elem(pt_deq, 67, -9);
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_resize_elem(pt_deq, 36, 222);
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_resize_elem(pt_deq, 0, 87);
            for(t_iter = deque_begin(pt_deq);
                !iterator_equal(t_iter, deque_end(pt_deq));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, ", *(int*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            deque_destroy(pt_deq);
        }
    }
    /* user defined type */
    {
        type_register(deqabc_t, NULL, NULL, NULL, NULL);
        type_duplicate(deqabc_t, struct _tagdeqabc);
        type_debug();
        /* create_deque(), deque_init(), deque_destroy() */
        {
            deque_t* pt_deq = create_deque(deqabc_t);
            if(pt_deq == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            deque_destroy(pt_deq);
        }
        /* deque_init_n() */
        {
            deque_t* pt_deq = create_deque(deqabc_t);
            if(pt_deq == NULL)
            {
                return;
            }
            deque_init_n(pt_deq, 4);
            deque_destroy(pt_deq);
        }
        /* deque_init_elem() */
        {
            deque_t* pt_deq = create_deque(struct _tagdeqabc);
            deqabc_t t_abc;
            if(pt_deq == NULL)
            {
                return;
            }
            t_abc.d_first = 3.4;
            t_abc.n_second = 90;
            deque_init_elem(pt_deq, 5, &t_abc);
            _printdeque_user(pt_deq);
            deque_destroy(pt_deq);
        }
        /* deque_init_copy() */
        {
            deque_t* pt_deq = create_deque(deqabc_t);
            deque_t* pt_deqex = create_deque(struct _tagdeqabc);
            deqabc_t t_abc = {8.8, 8};
            if(pt_deq == NULL || pt_deqex == NULL)
            {
                return;
            }
            deque_init_elem(pt_deqex, 6, &t_abc);
            deque_init_copy(pt_deq, pt_deqex);
            _printdeque_user(pt_deq);
            deque_destroy(pt_deqex);
            deque_destroy(pt_deq);
        }
        /* deque_init_copy_range() */
        {
            deque_t* pt_deq = create_deque(deqabc_t);
            deque_t* pt_deqex = create_deque(struct _tagdeqabc);
            deqabc_t t_abc = {8.8, 8};
            if(pt_deq == NULL || pt_deqex == NULL)
            {
                return;
            }
            deque_init_elem(pt_deqex, 6, &t_abc);
            t_abc.d_first = 0.01;
            t_abc.n_second = -43;
            deque_push_front(pt_deqex, &t_abc);
            t_abc.d_first = 555.55;
            t_abc.n_second = 34;
            deque_push_back(pt_deqex, &t_abc);
            deque_init_copy_range(pt_deq,
                iterator_next(deque_begin(pt_deqex)), iterator_prev_n(deque_end(pt_deqex), 3));
            _printdeque_user(pt_deq);
            deque_destroy(pt_deqex);
            deque_destroy(pt_deq);
        }
        /* deque_empty() */
        {
            deque_t* pt_deq = create_deque(deqabc_t);
            deqabc_t t_abc = {34.9, 349};
            if(pt_deq == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            printf("empty : %d, size : %d, max size : %d\n",
                deque_empty(pt_deq), deque_size(pt_deq), deque_max_size(pt_deq));
            deque_push_back(pt_deq, &t_abc);
            printf("empty : %d, size : %d, max size : %d\n",
                deque_empty(pt_deq), deque_size(pt_deq), deque_max_size(pt_deq));
            deque_push_back(pt_deq, &t_abc);
            deque_push_back(pt_deq, &t_abc);
            deque_push_back(pt_deq, &t_abc);
            deque_push_back(pt_deq, &t_abc);
            deque_push_back(pt_deq, &t_abc);
            deque_push_back(pt_deq, &t_abc);
            printf("empty : %d, size : %d, max size : %d\n",
                deque_empty(pt_deq), deque_size(pt_deq), deque_max_size(pt_deq));
            deque_destroy(pt_deq);
        }
        /* deque_size() */
        /* deque_max_size() */
        /* deque_equal() */
        {
            deque_t* pt_deq = create_deque(deqabc_t);
            deque_t* pt_deqex = create_deque(deqabc_t);
            deqabc_t t_abc;
            if(pt_deq == NULL || pt_deqex == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            deque_init(pt_deqex);
            printf("equal: %d, not equal: %d, "
                   "less: %d, less equal: %d, great: %d, great equal: %d\n",
                deque_equal(pt_deq, pt_deqex), deque_not_equal(pt_deq, pt_deqex),
                deque_less(pt_deq, pt_deqex), deque_less_equal(pt_deq, pt_deqex),
                deque_great(pt_deq, pt_deqex), deque_great_equal(pt_deq, pt_deqex));
            t_abc.d_first = 2.3;
            t_abc.n_second = 889;
            deque_push_back(pt_deqex, &t_abc);
            printf("equal: %d, not equal: %d, "
                   "less: %d, less equal: %d, great: %d, great equal: %d\n",
                deque_equal(pt_deq, pt_deqex), deque_not_equal(pt_deq, pt_deqex),
                deque_less(pt_deq, pt_deqex), deque_less_equal(pt_deq, pt_deqex),
                deque_great(pt_deq, pt_deqex), deque_great_equal(pt_deq, pt_deqex));
            deque_push_back(pt_deq, &t_abc);
            printf("equal: %d, not equal: %d, "
                   "less: %d, less equal: %d, great: %d, great equal: %d\n",
                deque_equal(pt_deq, pt_deqex), deque_not_equal(pt_deq, pt_deqex),
                deque_less(pt_deq, pt_deqex), deque_less_equal(pt_deq, pt_deqex),
                deque_great(pt_deq, pt_deqex), deque_great_equal(pt_deq, pt_deqex));
            deque_push_back(pt_deq, &t_abc);
            printf("equal: %d, not equal: %d, "
                   "less: %d, less equal: %d, great: %d, great equal: %d\n",
                deque_equal(pt_deq, pt_deqex), deque_not_equal(pt_deq, pt_deqex),
                deque_less(pt_deq, pt_deqex), deque_less_equal(pt_deq, pt_deqex),
                deque_great(pt_deq, pt_deqex), deque_great_equal(pt_deq, pt_deqex));
            t_abc.d_first = 2.3;
            t_abc.n_second = 77;
            deque_push_back(pt_deqex, &t_abc);
            printf("equal: %d, not equal: %d, "
                   "less: %d, less equal: %d, great: %d, great equal: %d\n",
                deque_equal(pt_deq, pt_deqex), deque_not_equal(pt_deq, pt_deqex),
                deque_less(pt_deq, pt_deqex), deque_less_equal(pt_deq, pt_deqex),
                deque_great(pt_deq, pt_deqex), deque_great_equal(pt_deq, pt_deqex));
            deque_destroy(pt_deq);
            deque_destroy(pt_deqex);
        }
        /* deque_not_equal() */
        /* deque_less() */
        /* deque_less_equal() */
        /* deque_great() */
        /* deque_great_equal() */
        /* deque_assign() */
        {
            deque_t* pt_deq = create_deque(deqabc_t);
            deque_t* pt_deqex = create_deque(deqabc_t);
            deqabc_t t_abc = {33.33, 3333};
            if(pt_deq == NULL || pt_deqex == NULL)
            {
                return;
            }
            deque_init_n(pt_deq, 4);
            deque_init(pt_deqex);
            _printdeque_user(pt_deq);
            deque_assign(pt_deq, pt_deqex);
            _printdeque_user(pt_deq);
            deque_push_back(pt_deqex, &t_abc);
            deque_push_back(pt_deqex, &t_abc);
            deque_assign(pt_deq, pt_deqex);
            _printdeque_user(pt_deq);
            t_abc.d_first = 9.9;
            t_abc.n_second = 99;
            deque_push_front(pt_deqex, &t_abc);
            deque_assign(pt_deq, pt_deqex);
            _printdeque_user(pt_deq);
            deque_pop_front(pt_deqex);
            deque_pop_back(pt_deqex);
            deque_assign(pt_deq, pt_deqex);
            _printdeque_user(pt_deq);
            deque_destroy(pt_deq);
            deque_destroy(pt_deqex);
        }
        /* deque_assign_elem() */
        {
            deque_t* pt_deq = create_deque(deqabc_t);
            deqabc_t t_abc;
            if(pt_deq == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            _printdeque_user(pt_deq);
            t_abc.d_first = 0.0;
            t_abc.n_second = 435;
            deque_assign_elem(pt_deq, 3, &t_abc);
            _printdeque_user(pt_deq);
            t_abc.d_first = 4.4;
            t_abc.n_second = 5;
            deque_assign_elem(pt_deq, 13, &t_abc);
            _printdeque_user(pt_deq);
            t_abc.d_first = -24.4;
            t_abc.n_second = -95;
            deque_assign_elem(pt_deq, 6, &t_abc);
            _printdeque_user(pt_deq);
            deque_assign_elem(pt_deq, 0, &t_abc);
            _printdeque_user(pt_deq);
            deque_destroy(pt_deq);
        }
        /* deque_assign_range() */
        {
            deque_t* pt_deq = create_deque(deqabc_t);
            deque_t* pt_deqex = create_deque(deqabc_t);
            deqabc_t t_abc;
            if(pt_deq == NULL || pt_deqex == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            deque_init(pt_deqex);
            t_abc.d_first = 66.6;
            t_abc.n_second = 3499;
            deque_push_back(pt_deqex, &t_abc);
            t_abc.d_first = -8.0;
            t_abc.n_second = 4;
            deque_push_back(pt_deqex, &t_abc);
            t_abc.d_first = 9.0;
            t_abc.n_second = 72;
            deque_push_back(pt_deqex, &t_abc);
            t_abc.d_first = 89.0;
            t_abc.n_second = 340;
            deque_push_back(pt_deqex, &t_abc);
            t_abc.d_first = 8.74;
            t_abc.n_second = 384;
            deque_push_back(pt_deqex, &t_abc);
            t_abc.d_first = 890;
            t_abc.n_second = 34;
            deque_push_back(pt_deqex, &t_abc);
            t_abc.d_first = 89.0;
            t_abc.n_second = 34;
            deque_push_back(pt_deqex, &t_abc);
            _printdeque_user(pt_deqex);
            _printdeque_user(pt_deq);
            deque_assign_range(pt_deq, deque_begin(pt_deqex), deque_begin(pt_deqex));
            _printdeque_user(pt_deq);
            deque_assign_range(pt_deq,
                deque_begin(pt_deqex), iterator_prev_n(deque_end(pt_deqex), 3));
            _printdeque_user(pt_deq);
            deque_assign_range(pt_deq,
                iterator_next_n(deque_begin(pt_deqex), 2), deque_end(pt_deqex));
            _printdeque_user(pt_deq);
            deque_assign_range(pt_deq,
                iterator_next_n(deque_begin(pt_deqex), 3),
                iterator_prev_n(deque_end(pt_deqex), 3));
            _printdeque_user(pt_deq);
            deque_assign_range(pt_deq, deque_end(pt_deqex), deque_end(pt_deqex));
            _printdeque_user(pt_deq);
            deque_destroy(pt_deq);
            deque_destroy(pt_deqex);
        }
        /* deque_swap() */
        {
            deque_t* pt_deq = create_deque(deqabc_t);
            deque_t* pt_deqex = create_deque(deqabc_t);
            deqabc_t t_abc;
            if(pt_deq == NULL || pt_deqex == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            deque_init(pt_deqex);
            _printdeque_user(pt_deq);
            _printdeque_user(pt_deqex);
            deque_swap(pt_deq, pt_deqex);
            _printdeque_user(pt_deq);
            _printdeque_user(pt_deqex);
            t_abc.d_first = 66.6;
            t_abc.n_second = 3499;
            deque_push_back(pt_deqex, &t_abc);
            t_abc.d_first = -8.0;
            t_abc.n_second = 4;
            deque_push_back(pt_deqex, &t_abc);
            t_abc.d_first = 9.0;
            t_abc.n_second = 72;
            deque_push_back(pt_deqex, &t_abc);
            t_abc.d_first = 89.0;
            t_abc.n_second = 340;
            deque_push_back(pt_deqex, &t_abc);
            t_abc.d_first = 8.74;
            t_abc.n_second = 384;
            deque_push_back(pt_deqex, &t_abc);
            t_abc.d_first = 890;
            t_abc.n_second = 34;
            deque_push_back(pt_deqex, &t_abc);
            t_abc.d_first = 89.0;
            t_abc.n_second = 34;
            deque_push_back(pt_deqex, &t_abc);
            _printdeque_user(pt_deq);
            _printdeque_user(pt_deqex);
            deque_swap(pt_deq, pt_deqex);
            _printdeque_user(pt_deq);
            _printdeque_user(pt_deqex);
            t_abc.d_first = -890;
            t_abc.n_second = -34;
            deque_push_back(pt_deqex, &t_abc);
            t_abc.d_first = -89.0;
            t_abc.n_second = -34;
            deque_push_back(pt_deqex, &t_abc);
            _printdeque_user(pt_deq);
            _printdeque_user(pt_deqex);
            deque_swap(pt_deq, pt_deqex);
            _printdeque_user(pt_deq);
            _printdeque_user(pt_deqex);
            deque_destroy(pt_deq);
            deque_destroy(pt_deqex);
        }
        /* deque_at() */
        {
            deque_t* pt_deq = create_deque(deqabc_t);
            if(pt_deq == NULL)
            {
                return;
            }
            deque_init_n(pt_deq, 7);
            _printdeque_user(pt_deq);
            ((deqabc_t*)deque_at(pt_deq, 0))->d_first = 45.98;
            ((deqabc_t*)deque_at(pt_deq, 0))->n_second = 23;
            _printdeque_user(pt_deq);
            ((deqabc_t*)deque_at(pt_deq, 3))->d_first = 33.77;
            ((deqabc_t*)deque_at(pt_deq, 3))->n_second = 99;
            _printdeque_user(pt_deq);
            ((deqabc_t*)deque_at(pt_deq, deque_size(pt_deq)-1))->d_first = 0.01;
            ((deqabc_t*)deque_at(pt_deq, deque_size(pt_deq)-1))->n_second = -99;
            _printdeque_user(pt_deq);
            deque_destroy(pt_deq);
        }
        /* deque_front() */
        {
            deque_t* pt_deq = create_deque(deqabc_t);
            deqabc_t t_abc;
            if(pt_deq == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            _printdeque_user(pt_deq);
            if(deque_front(pt_deq) != NULL)
            {
                ((deqabc_t*)deque_front(pt_deq))->d_first = 0.01;
                ((deqabc_t*)deque_front(pt_deq))->n_second = -99;
            }
            if(deque_back(pt_deq) != NULL)
            {
                ((deqabc_t*)deque_back(pt_deq))->d_first = 100.1;
                ((deqabc_t*)deque_back(pt_deq))->n_second = 2323;
            }
            _printdeque_user(pt_deq);
            t_abc.d_first = 8.74;
            t_abc.n_second = 384;
            deque_push_back(pt_deq, &t_abc);
            t_abc.d_first = 890;
            t_abc.n_second = 34;
            deque_push_back(pt_deq, &t_abc);
            t_abc.d_first = 89.0;
            t_abc.n_second = 34;
            deque_push_back(pt_deq, &t_abc);
            _printdeque_user(pt_deq);
            if(deque_front(pt_deq) != NULL)
            {
                ((deqabc_t*)deque_front(pt_deq))->d_first = 0.01;
                ((deqabc_t*)deque_front(pt_deq))->n_second = -99;
            }
            if(deque_back(pt_deq) != NULL)
            {
                ((deqabc_t*)deque_back(pt_deq))->d_first = 100.1;
                ((deqabc_t*)deque_back(pt_deq))->n_second = 2323;
            }
            _printdeque_user(pt_deq);
            deque_destroy(pt_deq);
        }
        /* deque_back() */
        /* deque_begin() */
        /* deque_end() */
        /* deque_insert() */
        /* deque_insert_n() */
        /* deque_insert_range() */
        /* deque_push_back() */
        /* deque_pop_back() */
        /* deque_push_front() */
        /* deque_pop_front() */
        /* deque_erase() */
        /* deque_erase_range() */
        /* deque_clear() */
        /* deque_resize() */
        /* deque_resize_elem() */
    }
    /* cstl builtin type */
    /* c-string type */
}

/** local function implementation section **/
static void _printdeque_user(const deque_t* pt_deque)
{
    iterator_t t_iter;
    for(t_iter = deque_begin(pt_deque);
        !iterator_equal(t_iter, deque_end(pt_deque));
        t_iter = iterator_next(t_iter))
    {
        printf("<%g, %d>, ",
            ((deqabc_t*)iterator_get_pointer(t_iter))->d_first,
            ((deqabc_t*)iterator_get_pointer(t_iter))->n_second);
    }
    printf("\n");
}

/** eof **/

