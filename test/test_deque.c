/*
 *  The implementation of deque test.
 *  Copyright (C)  2008,2009,2010  Wangbo
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
static void _printdeque_cstl(const deque_t* pt_deque);
static void _printdeque_user(const deque_t* pt_deque);
static void _print_deq_str(const deque_t* pt_deque);

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
        _type_debug();
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
        {
            deque_t* pt_deq = create_deque(deqabc_t);
            deqabc_t t_abc;
            if(pt_deq == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            _printdeque_user(pt_deq);
            t_abc.d_first = 45.6;
            t_abc.n_second = 233;
            deque_insert(pt_deq, deque_begin(pt_deq), &t_abc);
            _printdeque_user(pt_deq);
            t_abc.d_first = -45.6;
            t_abc.n_second = -233;
            deque_insert(pt_deq, deque_end(pt_deq), &t_abc);
            _printdeque_user(pt_deq);
            t_abc.d_first = 11.11;
            t_abc.n_second = 11;
            deque_insert(pt_deq, iterator_next(deque_begin(pt_deq)), &t_abc);
            _printdeque_user(pt_deq);
            deque_destroy(pt_deq);
        }
        /* deque_insert_n() */
        {
            deque_t* pt_deq = create_deque(deqabc_t);
            deqabc_t t_abc;
            if(pt_deq == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            _printdeque_user(pt_deq);
            t_abc.d_first = 45.6;
            t_abc.n_second = 233;
            deque_insert_n(pt_deq, deque_begin(pt_deq), 4, &t_abc);
            _printdeque_user(pt_deq);
            t_abc.d_first = -45.6;
            t_abc.n_second = -233;
            deque_insert_n(pt_deq, deque_end(pt_deq), 8, &t_abc);
            _printdeque_user(pt_deq);
            t_abc.d_first = 11.11;
            t_abc.n_second = 11;
            deque_insert_n(pt_deq, iterator_next(deque_begin(pt_deq)), 5, &t_abc);
            _printdeque_user(pt_deq);
            deque_destroy(pt_deq);
        }
        /* deque_insert_range() */
        {
            deque_t* pt_deq = create_deque(deqabc_t);
            deque_t* pt_deqex = create_deque(deqabc_t);
            deqabc_t t_abc;
            int i;
            if(pt_deq == NULL || pt_deqex == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            deque_init(pt_deqex);
            for(i = 0; i < 10; ++i)
            {
                t_abc.d_first = i * 1.1;
                t_abc.n_second = i;
                deque_push_back(pt_deqex, &t_abc);
            }
            _printdeque_user(pt_deqex);
            deque_insert_range(pt_deq, deque_begin(pt_deq),
                deque_begin(pt_deqex), deque_end(pt_deqex));
            _printdeque_user(pt_deq);
            deque_insert_range(pt_deq, deque_begin(pt_deq),
                deque_begin(pt_deqex), iterator_next_n(deque_begin(pt_deqex), 4));
            _printdeque_user(pt_deq);
            deque_insert_range(pt_deq, deque_end(pt_deq),
                iterator_prev_n(deque_end(pt_deqex), 5), deque_end(pt_deqex));
            _printdeque_user(pt_deq);
            deque_insert_range(pt_deq, iterator_next_n(deque_begin(pt_deq), 7),
                iterator_next_n(deque_begin(pt_deqex), 3), 
                iterator_next_n(deque_begin(pt_deqex), 3));
            _printdeque_user(pt_deq);
            deque_insert_range(pt_deq, iterator_next_n(deque_begin(pt_deq), 7),
                iterator_next_n(deque_begin(pt_deqex), 3), 
                iterator_next_n(deque_begin(pt_deqex), 8));
            _printdeque_user(pt_deq);
            deque_destroy(pt_deq);
            deque_destroy(pt_deqex);
        }
        /* deque_push_back() */
        {
            deque_t* pt_deq = create_deque(deqabc_t);
            deqabc_t t_abc;
            if(pt_deq == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            t_abc.d_first = 33.44;
            t_abc.n_second = 234;
            deque_push_back(pt_deq, &t_abc);
            t_abc.d_first = -33.44;
            t_abc.n_second = -234;
            deque_push_back(pt_deq, &t_abc);
            t_abc.d_first = 88.99;
            t_abc.n_second = 890;
            deque_push_front(pt_deq, &t_abc);
            t_abc.d_first = -88.99;
            t_abc.n_second = -890;
            deque_push_front(pt_deq, &t_abc);
            _printdeque_user(pt_deq);
            deque_pop_front(pt_deq);
            _printdeque_user(pt_deq);
            deque_pop_back(pt_deq);
            _printdeque_user(pt_deq);
            deque_pop_front(pt_deq);
            deque_pop_front(pt_deq);
            _printdeque_user(pt_deq);
            deque_push_front(pt_deq, &t_abc);
            _printdeque_user(pt_deq);
            deque_pop_back(pt_deq);
            _printdeque_user(pt_deq);
            deque_destroy(pt_deq);
        }
        /* deque_pop_back() */
        /* deque_push_front() */
        /* deque_pop_front() */
        /* deque_erase() */
        {
            deque_t* pt_deq = create_deque(deqabc_t);
            deqabc_t t_abc;
            int i;
            if(pt_deq == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            for(i = 0; i < 10; ++i)
            {
                t_abc.d_first = i * 1.1;
                t_abc.n_second = i;
                deque_push_back(pt_deq, &t_abc);
            }
            _printdeque_user(pt_deq);
            deque_erase(pt_deq, deque_begin(pt_deq));
            _printdeque_user(pt_deq);
            deque_erase(pt_deq, iterator_prev(deque_end(pt_deq)));
            _printdeque_user(pt_deq);
            deque_erase(pt_deq, iterator_next_n(deque_begin(pt_deq), 3));
            _printdeque_user(pt_deq);
            while(!deque_empty(pt_deq))
            {
                deque_erase(pt_deq, deque_begin(pt_deq));
            }
            _printdeque_user(pt_deq);
            deque_destroy(pt_deq);
        }
        /* deque_erase_range() */
        {
            deque_t* pt_deq = create_deque(deqabc_t);
            deqabc_t t_abc;
            int i;
            if(pt_deq == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            for(i = 0; i < 10; ++i)
            {
                t_abc.d_first = i * 1.1;
                t_abc.n_second = i;
                deque_push_back(pt_deq, &t_abc);
            }
            _printdeque_user(pt_deq);
            deque_erase_range(pt_deq, deque_begin(pt_deq), deque_begin(pt_deq));
            _printdeque_user(pt_deq);
            deque_erase_range(pt_deq,
                iterator_prev_n(deque_end(pt_deq), 3), deque_end(pt_deq));
            _printdeque_user(pt_deq);
            deque_erase_range(pt_deq,
                deque_begin(pt_deq), iterator_next_n(deque_begin(pt_deq), 3));
            _printdeque_user(pt_deq);
            deque_erase_range(pt_deq,
                iterator_next(deque_begin(pt_deq)), iterator_prev(deque_end(pt_deq)));
            _printdeque_user(pt_deq);
            deque_erase_range(pt_deq, deque_begin(pt_deq), deque_end(pt_deq));
            _printdeque_user(pt_deq);
            deque_destroy(pt_deq);
        }
        /* deque_clear() */
        {
            deque_t* pt_deq = create_deque(deqabc_t);
            deqabc_t t_abc;
            int i;
            if(pt_deq == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            for(i = 0; i < 10; ++i)
            {
                t_abc.d_first = i * 1.1;
                t_abc.n_second = i;
                deque_push_back(pt_deq, &t_abc);
            }
            _printdeque_user(pt_deq);
            deque_clear(pt_deq);
            _printdeque_user(pt_deq);
            deque_clear(pt_deq);
            _printdeque_user(pt_deq);
            deque_destroy(pt_deq);
        }
        /* deque_resize() */
        {
            deque_t* pt_deq = create_deque(deqabc_t);
            if(pt_deq == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            _printdeque_user(pt_deq);
            deque_resize(pt_deq, 4);
            _printdeque_user(pt_deq);
            deque_resize(pt_deq, 9);
            _printdeque_user(pt_deq);
            deque_resize(pt_deq, 2);
            _printdeque_user(pt_deq);
            deque_resize(pt_deq, 0);
            _printdeque_user(pt_deq);
            deque_destroy(pt_deq);
        }
        /* deque_resize_elem() */
        {
            deque_t* pt_deq = create_deque(deqabc_t);
            deqabc_t t_abc;
            if(pt_deq == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            _printdeque_user(pt_deq);
            t_abc.d_first = 4.4;
            t_abc.n_second = 4;
            deque_resize_elem(pt_deq, 4, &t_abc);
            _printdeque_user(pt_deq);
            t_abc.d_first = 9.9;
            t_abc.n_second = 9;
            deque_resize_elem(pt_deq, 9, &t_abc);
            _printdeque_user(pt_deq);
            t_abc.d_first = 2.2;
            t_abc.n_second = 2;
            deque_resize_elem(pt_deq, 2, &t_abc);
            _printdeque_user(pt_deq);
            t_abc.d_first = 0.0;
            t_abc.n_second = 0;
            deque_resize_elem(pt_deq, 0, &t_abc);
            _printdeque_user(pt_deq);
            deque_destroy(pt_deq);
        }
    }
    /* cstl builtin type */
    {
        /* create_deque(), deque_init(), deque_destroy() */
        {
            deque_t* pt_deq = create_deque(deque_t<int>);
            if(pt_deq == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            deque_destroy(pt_deq);
        }
        /* deque_init_n() */
        {
            deque_t* pt_deq = create_deque(deque_t<int>);
            if(pt_deq == NULL)
            {
                return;
            }
            deque_init_n(pt_deq, 4);
            _printdeque_cstl(pt_deq);
            deque_destroy(pt_deq);
        }
        /* deque_init_elem() */
        {
            deque_t* pt_deq = create_deque(deque_t<int>);
            deque_t* pt_deqex = create_deque(int);
            if(pt_deq == NULL || pt_deqex == NULL)
            {
                return;
            }
            deque_init_elem(pt_deqex, 5, 9);
            deque_init_elem(pt_deq, 4, pt_deqex);
            _printdeque_cstl(pt_deq);
            deque_destroy(pt_deq);
            deque_destroy(pt_deqex);
        }
        /* deque_init_copy() */
        {
            deque_t* pt_deq1 = create_deque(deque_t<int>);
            deque_t* pt_deq2 = create_deque(deque_t<int>);
            deque_t* pt_deqex = create_deque(int);
            int i;
            if(pt_deq1 == NULL || pt_deq2 == NULL || pt_deqex == NULL)
            {
                return;
            }
            deque_init(pt_deqex);
            for(i = 0; i < 10; ++i)
            {
                deque_push_back(pt_deqex, i);
            }
            deque_init_elem(pt_deq2, 5, pt_deqex);
            deque_init_copy(pt_deq1, pt_deq2);
            _printdeque_cstl(pt_deq1);
            deque_destroy(pt_deq1);
            deque_destroy(pt_deq2);
            deque_destroy(pt_deqex);
        }
        /* deque_init_copy_range() */
        {
            deque_t* pt_deq1 = create_deque(deque_t<int>);
            deque_t* pt_deq2 = create_deque(deque_t<int>);
            deque_t* pt_deqex = create_deque(int);
            int i;
            if(pt_deq1 == NULL || pt_deq2 == NULL || pt_deqex == NULL)
            {
                return;
            }
            deque_init(pt_deqex);
            deque_init(pt_deq2);
            for(i = 0; i < 10; ++i)
            {
                deque_push_back(pt_deqex, i);
                deque_push_front(pt_deq2, pt_deqex);
            }
            deque_init_copy_range(pt_deq1,
                iterator_next_n(deque_begin(pt_deq2), 4),
                iterator_prev_n(deque_end(pt_deq2), 3));
            _printdeque_cstl(pt_deq2);
            _printdeque_cstl(pt_deq1);
            deque_destroy(pt_deq1);
            deque_destroy(pt_deq2);
            deque_destroy(pt_deqex);
        }
        /* deque_empty() */
        {
            deque_t* pt_deq = create_deque(deque_t<int>);
            deque_t* pt_deqex = create_deque(int);
            if(pt_deq == NULL || pt_deqex == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            deque_init(pt_deqex);
            printf("empty:%d size:%d, max size:%d\n",
                deque_empty(pt_deq), deque_size(pt_deq), deque_max_size(pt_deq));
            deque_push_back(pt_deq, pt_deqex);
            printf("empty:%d size:%d, max size:%d\n",
                deque_empty(pt_deq), deque_size(pt_deq), deque_max_size(pt_deq));
            deque_insert_n(pt_deq, deque_end(pt_deq), 5, pt_deqex);
            printf("empty:%d size:%d, max size:%d\n",
                deque_empty(pt_deq), deque_size(pt_deq), deque_max_size(pt_deq));
            deque_destroy(pt_deq);
            deque_destroy(pt_deqex);
        }
        /* deque_size() */
        /* deque_max_size() */
        /* deque_equal() */
        {
            deque_t* pt_deq1 = create_deque(deque_t<int>);
            deque_t* pt_deq2 = create_deque(deque_t<int>);
            deque_t* pt_deqex = create_deque(int);
            if(pt_deq1 == NULL || pt_deq2 == NULL || pt_deqex == NULL)
            {
                return;
            }
            deque_init(pt_deq1);
            deque_init(pt_deq2);
            deque_init(pt_deqex);
            printf("equal: %d, not equal: %d\n",
                deque_equal(pt_deq1, pt_deq2), deque_not_equal(pt_deq1, pt_deq2));
            printf("less: %d, less equal: %d\n",
                deque_less(pt_deq1, pt_deq2), deque_less_equal(pt_deq1, pt_deq2));
            printf("great: %d, great equal: %d\n",
                deque_great(pt_deq1, pt_deq2), deque_great_equal(pt_deq1, pt_deq2));
            deque_push_back(pt_deq1, pt_deqex);
            printf("equal: %d, not equal: %d\n",
                deque_equal(pt_deq1, pt_deq2), deque_not_equal(pt_deq1, pt_deq2));
            printf("less: %d, less equal: %d\n",
                deque_less(pt_deq1, pt_deq2), deque_less_equal(pt_deq1, pt_deq2));
            printf("great: %d, great equal: %d\n",
                deque_great(pt_deq1, pt_deq2), deque_great_equal(pt_deq1, pt_deq2));
            deque_push_back(pt_deq2, pt_deqex);
            deque_push_back(pt_deq2, pt_deqex);
            printf("equal: %d, not equal: %d\n",
                deque_equal(pt_deq1, pt_deq2), deque_not_equal(pt_deq1, pt_deq2));
            printf("less: %d, less equal: %d\n",
                deque_less(pt_deq1, pt_deq2), deque_less_equal(pt_deq1, pt_deq2));
            printf("great: %d, great equal: %d\n",
                deque_great(pt_deq1, pt_deq2), deque_great_equal(pt_deq1, pt_deq2));
            deque_push_back(pt_deqex, 29);
            deque_push_back(pt_deq1, pt_deqex);
            printf("equal: %d, not equal: %d\n",
                deque_equal(pt_deq1, pt_deq2), deque_not_equal(pt_deq1, pt_deq2));
            printf("less: %d, less equal: %d\n",
                deque_less(pt_deq1, pt_deq2), deque_less_equal(pt_deq1, pt_deq2));
            printf("great: %d, great equal: %d\n",
                deque_great(pt_deq1, pt_deq2), deque_great_equal(pt_deq1, pt_deq2));
            deque_destroy(pt_deq1);
            deque_destroy(pt_deq2);
            deque_destroy(pt_deqex);
        }
        /* deque_not_equal() */
        /* deque_less() */
        /* deque_less_equal() */
        /* deque_great() */
        /* deque_great_equal() */
        /* deque_assign() */
        {
            deque_t* pt_deq1 = create_deque(deque_t<int>);
            deque_t* pt_deq2 = create_deque(deque_t<int>);
            deque_t* pt_deqex = create_deque(int);
            if(pt_deq1 == NULL || pt_deq2 == NULL || pt_deqex == NULL)
            {
                return;
            }
            deque_init(pt_deq1);
            deque_init(pt_deq2);
            deque_init(pt_deqex);
            _printdeque_cstl(pt_deq1);
            _printdeque_cstl(pt_deq2);
            deque_push_back(pt_deqex, 34);
            deque_push_back(pt_deqex, 120);
            deque_push_back(pt_deq2, pt_deqex);
            deque_push_back(pt_deq2, pt_deqex);
            deque_assign(pt_deq1, pt_deq2);
            _printdeque_cstl(pt_deq1);
            _printdeque_cstl(pt_deq2);
            deque_clear(pt_deq2);
            deque_clear(pt_deqex);
            deque_push_back(pt_deqex, 908);
            deque_push_back(pt_deqex, -223);
            deque_push_back(pt_deqex, 22);
            deque_push_back(pt_deq2, pt_deqex);
            deque_clear(pt_deqex);
            deque_push_back(pt_deqex, -1);
            deque_push_back(pt_deq2, pt_deqex);
            deque_clear(pt_deqex);
            deque_push_back(pt_deqex, 0);
            deque_push_back(pt_deqex, 1999);
            deque_push_back(pt_deqex, -4);
            deque_push_back(pt_deqex, 2223);
            deque_push_back(pt_deq2, pt_deqex);
            deque_clear(pt_deqex);
            deque_push_front(pt_deqex, -445);
            deque_push_front(pt_deqex, 2323);
            deque_push_front(pt_deq2, pt_deqex);
            deque_assign(pt_deq1, pt_deq2);
            _printdeque_cstl(pt_deq1);
            _printdeque_cstl(pt_deq2);
            deque_clear(pt_deqex);
            deque_clear(pt_deq2);
            deque_push_front(pt_deqex, 11111);
            deque_push_back(pt_deq2, pt_deqex);
            deque_assign(pt_deq1, pt_deq2);
            _printdeque_cstl(pt_deq1);
            _printdeque_cstl(pt_deq2);
            deque_clear(pt_deq2);
            deque_assign(pt_deq1, pt_deq2);
            _printdeque_cstl(pt_deq1);
            _printdeque_cstl(pt_deq2);
            deque_destroy(pt_deq1);
            deque_destroy(pt_deq2);
            deque_destroy(pt_deqex);
        }
        /* deque_assign_elem() */
        {
            deque_t* pt_deq = create_deque(deque_t<int>);
            deque_t* pt_deqex = create_deque(int);
            if(pt_deq == NULL || pt_deqex == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            deque_init(pt_deqex);
            _printdeque_cstl(pt_deq);
            deque_assign_elem(pt_deq, 3, pt_deqex);
            _printdeque_cstl(pt_deq);
            deque_push_back(pt_deqex, 112233);
            deque_push_back(pt_deqex, 0);
            deque_push_back(pt_deqex, 34567);
            deque_assign_elem(pt_deq, 7, pt_deqex);
            _printdeque_cstl(pt_deq);
            deque_clear(pt_deqex);
            deque_push_back(pt_deqex, 45);
            deque_push_back(pt_deqex, 12);
            deque_assign_elem(pt_deq, 2, pt_deqex);
            _printdeque_cstl(pt_deq);
            deque_destroy(pt_deq);
            deque_destroy(pt_deqex);
        }
        /* deque_assign_range() */
        {
            deque_t* pt_deq1 = create_deque(deque_t<int>);
            deque_t* pt_deq2 = create_deque(deque_t<int>);
            deque_t* pt_deqex = create_deque(int);
            if(pt_deq1 == NULL || pt_deq2 == NULL || pt_deqex == NULL)
            {
                return;
            }
            deque_init(pt_deq1);
            deque_init(pt_deq2);
            deque_init(pt_deqex);
            deque_push_back(pt_deqex, 908);
            deque_push_back(pt_deqex, -223);
            deque_push_back(pt_deqex, 22);
            deque_push_back(pt_deq2, pt_deqex);
            deque_clear(pt_deqex);
            deque_push_back(pt_deqex, -1);
            deque_push_back(pt_deq2, pt_deqex);
            deque_clear(pt_deqex);
            deque_push_back(pt_deqex, 0);
            deque_push_back(pt_deqex, 1999);
            deque_push_back(pt_deqex, -4);
            deque_push_back(pt_deqex, 2223);
            deque_push_back(pt_deq2, pt_deqex);
            deque_clear(pt_deqex);
            deque_push_front(pt_deqex, -445);
            deque_push_front(pt_deqex, 2323);
            deque_push_front(pt_deq2, pt_deqex);
            deque_clear(pt_deqex);
            deque_push_back(pt_deqex, -555);
            deque_push_back(pt_deqex, 555);
            deque_push_back(pt_deqex, -555);
            deque_push_back(pt_deqex, 555);
            deque_push_back(pt_deqex, -555);
            deque_push_back(pt_deqex, 555);
            deque_push_back(pt_deqex, -555);
            deque_push_back(pt_deqex, 555);
            deque_push_back(pt_deqex, -555);
            deque_push_front(pt_deq2, pt_deqex);
            deque_clear(pt_deqex);
            deque_push_back(pt_deqex, 234);
            deque_push_back(pt_deqex, 55);
            deque_push_front(pt_deq2, pt_deqex);
            deque_push_back(pt_deqex, 5);
            deque_push_back(pt_deqex, 40);
            deque_push_back(pt_deqex, 1);
            deque_push_back(pt_deqex, -58);
            deque_push_back(pt_deqex, -741);
            deque_push_back(pt_deqex, 352);
            deque_push_back(pt_deqex, 9557);
            deque_push_back(pt_deqex, 575);
            deque_push_back(pt_deqex, -555);
            deque_push_front(pt_deq2, pt_deqex);
            _printdeque_cstl(pt_deq2);
            _printdeque_cstl(pt_deq1);
            deque_assign_range(pt_deq1, deque_begin(pt_deq2), deque_begin(pt_deq2));
            _printdeque_cstl(pt_deq1);
            deque_assign_range(pt_deq1,
                deque_begin(pt_deq2), iterator_prev_n(deque_end(pt_deq2), 4));
            _printdeque_cstl(pt_deq1);
            deque_assign_range(pt_deq1,
                deque_begin(pt_deq2), iterator_prev(deque_end(pt_deq2)));
            _printdeque_cstl(pt_deq1);
            deque_assign_range(pt_deq1,
                iterator_next_n(deque_begin(pt_deq2), 5), deque_end(pt_deq2));
            _printdeque_cstl(pt_deq1);
            deque_assign_range(pt_deq1,
                iterator_next_n(deque_begin(pt_deq2), 3), iterator_prev(deque_end(pt_deq2)));
            _printdeque_cstl(pt_deq1);
            deque_assign_range(pt_deq1,
                iterator_next_n(deque_begin(pt_deq2), 3),
                iterator_prev_n(deque_end(pt_deq2), 4));
            _printdeque_cstl(pt_deq1);
            deque_destroy(pt_deq1);
            deque_destroy(pt_deq2);
            deque_destroy(pt_deqex);
        }
        /* deque_swap() */
        {
            deque_t* pt_deq1 = create_deque(deque_t<int>);
            deque_t* pt_deq2 = create_deque(deque_t<int>);
            deque_t* pt_deqex = create_deque(int);
            if(pt_deq1 == NULL || pt_deq2 == NULL || pt_deqex == NULL)
            {
                return;
            }
            deque_init(pt_deq1);
            deque_init(pt_deq2);
            deque_init(pt_deqex);
            _printdeque_cstl(pt_deq1);
            _printdeque_cstl(pt_deq2);
            deque_swap(pt_deq1, pt_deq2);
            _printdeque_cstl(pt_deq1);
            _printdeque_cstl(pt_deq2);
            deque_push_back(pt_deqex, 908);
            deque_push_back(pt_deqex, -223);
            deque_push_back(pt_deqex, 22);
            deque_push_back(pt_deq2, pt_deqex);
            deque_clear(pt_deqex);
            deque_push_back(pt_deqex, -1);
            deque_push_back(pt_deq2, pt_deqex);
            deque_clear(pt_deqex);
            deque_push_back(pt_deqex, 0);
            deque_push_back(pt_deqex, 1999);
            deque_push_back(pt_deqex, -4);
            deque_push_back(pt_deqex, 2223);
            deque_push_back(pt_deq2, pt_deqex);
            deque_clear(pt_deqex);
            deque_push_front(pt_deqex, -445);
            deque_push_front(pt_deqex, 2323);
            deque_push_front(pt_deq2, pt_deqex);
            deque_clear(pt_deqex);
            deque_push_back(pt_deqex, -555);
            deque_push_back(pt_deqex, 555);
            deque_push_back(pt_deqex, -555);
            deque_push_back(pt_deqex, 555);
            deque_push_back(pt_deqex, -555);
            deque_push_back(pt_deqex, 555);
            deque_push_back(pt_deqex, -555);
            deque_push_back(pt_deqex, 555);
            deque_push_back(pt_deqex, -555);
            deque_push_front(pt_deq2, pt_deqex);
            deque_clear(pt_deqex);
            deque_push_back(pt_deqex, 234);
            deque_push_back(pt_deqex, 55);
            deque_push_front(pt_deq2, pt_deqex);
            deque_push_back(pt_deqex, 5);
            deque_push_back(pt_deqex, 40);
            deque_push_back(pt_deqex, 1);
            deque_push_back(pt_deqex, -58);
            deque_push_back(pt_deqex, -741);
            deque_push_back(pt_deqex, 352);
            deque_push_back(pt_deqex, 9557);
            deque_push_back(pt_deqex, 575);
            deque_push_back(pt_deqex, -555);
            deque_push_front(pt_deq2, pt_deqex);
            _printdeque_cstl(pt_deq1);
            _printdeque_cstl(pt_deq2);
            deque_swap(pt_deq1, pt_deq2);
            _printdeque_cstl(pt_deq1);
            _printdeque_cstl(pt_deq2);
            deque_clear(pt_deqex);
            deque_push_front(pt_deqex, -445);
            deque_push_front(pt_deqex, 2323);
            deque_push_front(pt_deq2, pt_deqex);
            deque_clear(pt_deqex);
            deque_push_back(pt_deqex, -555);
            deque_push_back(pt_deqex, 555);
            deque_push_back(pt_deqex, -555);
            deque_push_back(pt_deqex, 555);
            deque_push_back(pt_deqex, -555);
            deque_push_back(pt_deqex, 555);
            deque_push_back(pt_deqex, -555);
            deque_push_back(pt_deqex, 555);
            deque_push_back(pt_deqex, -555);
            deque_push_front(pt_deq2, pt_deqex);
            _printdeque_cstl(pt_deq1);
            _printdeque_cstl(pt_deq2);
            deque_swap(pt_deq1, pt_deq2);
            _printdeque_cstl(pt_deq1);
            _printdeque_cstl(pt_deq2);
            deque_clear(pt_deq2);
            _printdeque_cstl(pt_deq1);
            _printdeque_cstl(pt_deq2);
            deque_swap(pt_deq1, pt_deq2);
            _printdeque_cstl(pt_deq1);
            _printdeque_cstl(pt_deq2);
            deque_destroy(pt_deq1);
            deque_destroy(pt_deq2);
            deque_destroy(pt_deqex);
        }
        /* deque_at() */
        {
            deque_t* pt_deq = create_deque(deque_t<int>);
            deque_t* pt_deqex = create_deque(int);
            if(pt_deq == NULL || pt_deqex == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            deque_init(pt_deqex);
            if(deque_front(pt_deq) != NULL || deque_back(pt_deq) != NULL)
            {
                assert(false);
            }
            deque_push_back(pt_deqex, 908);
            deque_push_back(pt_deqex, -223);
            deque_push_back(pt_deqex, 22);
            deque_push_back(pt_deq, pt_deqex);
            deque_clear(pt_deqex);
            deque_push_back(pt_deqex, -1);
            deque_push_back(pt_deq, pt_deqex);
            deque_clear(pt_deqex);
            deque_push_back(pt_deqex, 0);
            deque_push_back(pt_deqex, 1999);
            deque_push_back(pt_deqex, -4);
            deque_push_back(pt_deqex, 2223);
            deque_push_back(pt_deq, pt_deqex);
            deque_clear(pt_deqex);
            deque_push_front(pt_deqex, -445);
            deque_push_front(pt_deqex, 2323);
            deque_push_front(pt_deq, pt_deqex);
            deque_clear(pt_deqex);
            deque_push_back(pt_deqex, -555);
            deque_push_back(pt_deqex, 555);
            deque_push_back(pt_deqex, -555);
            deque_push_back(pt_deqex, 555);
            deque_push_back(pt_deqex, -555);
            deque_push_back(pt_deqex, 555);
            deque_push_back(pt_deqex, -555);
            deque_push_back(pt_deqex, 555);
            deque_push_back(pt_deqex, -555);
            deque_push_front(pt_deq, pt_deqex);
            deque_clear(pt_deqex);
            deque_push_back(pt_deqex, 234);
            deque_push_back(pt_deqex, 55);
            deque_push_front(pt_deq, pt_deqex);
            deque_push_back(pt_deqex, 5);
            deque_push_back(pt_deqex, 40);
            deque_push_back(pt_deqex, 1);
            deque_push_back(pt_deqex, -58);
            deque_push_back(pt_deqex, -741);
            deque_push_back(pt_deqex, 352);
            deque_push_back(pt_deqex, 9557);
            deque_push_back(pt_deqex, 575);
            deque_push_back(pt_deqex, -555);
            deque_push_front(pt_deq, pt_deqex);
            _printdeque_cstl(pt_deq);
            deque_clear(deque_front(pt_deq));
            deque_assign_elem(deque_back(pt_deq), 5, 100);
            deque_push_back(deque_at(pt_deq, 3), 3333);
            deque_push_front(deque_at(pt_deq, 3), 3333);
            _printdeque_cstl(pt_deq);
            deque_destroy(pt_deq);
            deque_destroy(pt_deqex);
        }
        /* deque_front() */
        /* deque_back() */
        /* deque_begin() */
        /* deque_end() */
        /* deque_insert() */
        {
            deque_t* pt_deq = create_deque(deque_t<int>);
            deque_t* pt_deqex = create_deque(int);
            if(pt_deq == NULL || pt_deqex == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            deque_init(pt_deqex);
            deque_push_front(pt_deqex, 100);
            deque_push_back(pt_deqex, 200);
            deque_push_back(pt_deqex, 300);
            deque_insert(pt_deq, deque_begin(pt_deq), pt_deqex);
            _printdeque_cstl(pt_deq);
            deque_clear(pt_deqex);
            deque_assign_elem(pt_deqex, 5, 0);
            deque_assign_elem(pt_deq, 5, pt_deqex);
            _printdeque_cstl(pt_deq);
            deque_assign_elem(pt_deqex, 5, 9);
            deque_insert(pt_deq, deque_begin(pt_deq), pt_deqex);
            deque_insert(pt_deq, deque_end(pt_deq), pt_deqex);
            deque_insert(pt_deq, iterator_next_n(deque_begin(pt_deq), 4), pt_deqex);
            _printdeque_cstl(pt_deq);
            deque_destroy(pt_deq);
            deque_destroy(pt_deqex);
        }
        /* deque_insert_n() */
        {
            deque_t* pt_deq = create_deque(deque_t<int>);
            deque_t* pt_deqex = create_deque(int);
            if(pt_deq == NULL || pt_deqex == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            deque_init(pt_deqex);
            deque_assign_elem(pt_deqex, 5, 0);
            deque_insert_n(pt_deq, deque_begin(pt_deq), 5, pt_deqex);
            _printdeque_cstl(pt_deq);
            deque_clear(pt_deqex);
            deque_assign_elem(pt_deqex, 5, 7);
            deque_assign_elem(pt_deq, 5, pt_deqex);
            _printdeque_cstl(pt_deq);
            deque_assign_elem(pt_deqex, 5, 9);
            deque_insert_n(pt_deq, deque_begin(pt_deq), 3, pt_deqex);
            deque_assign_elem(pt_deqex, 5, 2);
            deque_insert_n(pt_deq, deque_end(pt_deq), 4, pt_deqex);
            deque_assign_elem(pt_deqex, 5, 1);
            deque_insert_n(pt_deq, iterator_next_n(deque_begin(pt_deq), 4), 8, pt_deqex);
            _printdeque_cstl(pt_deq);
            deque_destroy(pt_deq);
            deque_destroy(pt_deqex);
        }
        /* deque_insert_range() */
        {
            deque_t* pt_deq1 = create_deque(deque_t<int>);
            deque_t* pt_deq2 = create_deque(deque_t<int>);
            deque_t* pt_deqex = create_deque(int);
            if(pt_deq1 == NULL || pt_deq2 == NULL || pt_deqex == NULL)
            {
                return;
            }
            deque_init(pt_deq1);
            deque_init(pt_deq2);
            deque_init(pt_deqex);
            deque_push_back(pt_deqex, 908);
            deque_push_back(pt_deqex, -223);
            deque_push_back(pt_deqex, 22);
            deque_push_back(pt_deq2, pt_deqex);
            deque_clear(pt_deqex);
            deque_push_back(pt_deqex, -1);
            deque_push_back(pt_deq2, pt_deqex);
            deque_clear(pt_deqex);
            deque_push_back(pt_deqex, 0);
            deque_push_back(pt_deqex, 1999);
            deque_push_back(pt_deqex, -4);
            deque_push_back(pt_deqex, 2223);
            deque_push_back(pt_deq2, pt_deqex);
            deque_clear(pt_deqex);
            deque_push_front(pt_deqex, -445);
            deque_push_front(pt_deqex, 2323);
            deque_push_front(pt_deq2, pt_deqex);
            deque_clear(pt_deqex);
            deque_push_back(pt_deqex, -555);
            deque_push_back(pt_deqex, 555);
            deque_push_back(pt_deqex, -555);
            deque_push_back(pt_deqex, 555);
            deque_push_back(pt_deqex, -555);
            deque_push_back(pt_deqex, 555);
            deque_push_back(pt_deqex, -555);
            deque_push_back(pt_deqex, 555);
            deque_push_back(pt_deqex, -555);
            deque_push_front(pt_deq2, pt_deqex);
            deque_clear(pt_deqex);
            deque_push_back(pt_deqex, 234);
            deque_push_back(pt_deqex, 55);
            deque_push_front(pt_deq2, pt_deqex);
            deque_push_back(pt_deqex, 5);
            deque_push_back(pt_deqex, 40);
            deque_push_back(pt_deqex, 1);
            deque_push_back(pt_deqex, -58);
            deque_push_back(pt_deqex, -741);
            deque_push_back(pt_deqex, 352);
            deque_push_back(pt_deqex, 9557);
            deque_push_back(pt_deqex, 575);
            deque_push_back(pt_deqex, -555);
            deque_push_front(pt_deq2, pt_deqex);
            _printdeque_cstl(pt_deq2);
            deque_insert_range(pt_deq1, deque_begin(pt_deq1),
                deque_begin(pt_deq2), deque_end(pt_deq2));
            _printdeque_cstl(pt_deq1);
            deque_assign_elem(pt_deqex, 5, 0);
            deque_assign_elem(pt_deq1, 5, pt_deqex);
            _printdeque_cstl(pt_deq1);
            deque_insert_range(pt_deq1, deque_begin(pt_deq1),
                deque_begin(pt_deq2), iterator_next(deque_begin(pt_deq2)));
            _printdeque_cstl(pt_deq1);
            deque_insert_range(pt_deq1, deque_end(pt_deq1),
                iterator_prev_n(deque_end(pt_deq2), 2), deque_end(pt_deq2));
            _printdeque_cstl(pt_deq1);
            deque_insert_range(pt_deq1, iterator_next_n(deque_begin(pt_deq1), 4),
                iterator_next_n(deque_begin(pt_deq2), 2),
                iterator_prev_n(deque_end(pt_deq2), 2));
            _printdeque_cstl(pt_deq1);
            deque_insert_range(pt_deq1, iterator_next_n(deque_begin(pt_deq1), 4),
                iterator_next_n(deque_begin(pt_deq2), 2),
                iterator_prev_n(deque_end(pt_deq2), 5));
            _printdeque_cstl(pt_deq1);
            deque_destroy(pt_deq1);
            deque_destroy(pt_deq2);
            deque_destroy(pt_deqex);
        }
        /* deque_push_back() */
        {
            deque_t* pt_deq = create_deque(deque_t<int>);
            deque_t* pt_deqex = create_deque(int);
            if(pt_deq == NULL || pt_deqex == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            deque_init(pt_deqex);
            deque_push_back(pt_deqex, 908);
            deque_push_back(pt_deqex, -223);
            deque_push_back(pt_deqex, 22);
            deque_push_back(pt_deq, pt_deqex);
            deque_clear(pt_deqex);
            deque_push_back(pt_deqex, -1);
            deque_push_back(pt_deq, pt_deqex);
            deque_clear(pt_deqex);
            deque_push_back(pt_deqex, 0);
            deque_push_back(pt_deqex, 1999);
            deque_push_back(pt_deqex, -4);
            deque_push_back(pt_deqex, 2223);
            deque_push_back(pt_deq, pt_deqex);
            deque_clear(pt_deqex);
            deque_push_front(pt_deqex, -445);
            deque_push_front(pt_deqex, 2323);
            deque_push_front(pt_deq, pt_deqex);
            deque_clear(pt_deqex);
            deque_push_back(pt_deqex, -555);
            deque_push_back(pt_deqex, 555);
            deque_push_back(pt_deqex, -555);
            deque_push_back(pt_deqex, 555);
            deque_push_back(pt_deqex, -555);
            deque_push_back(pt_deqex, 555);
            deque_push_back(pt_deqex, -555);
            deque_push_back(pt_deqex, 555);
            deque_push_back(pt_deqex, -555);
            deque_push_front(pt_deq, pt_deqex);
            deque_clear(pt_deqex);
            deque_push_back(pt_deqex, 234);
            deque_push_back(pt_deqex, 55);
            deque_push_front(pt_deq, pt_deqex);
            deque_push_back(pt_deqex, 5);
            deque_push_back(pt_deqex, 40);
            deque_push_back(pt_deqex, 1);
            deque_push_back(pt_deqex, -58);
            deque_push_back(pt_deqex, -741);
            deque_push_back(pt_deqex, 352);
            deque_push_back(pt_deqex, 9557);
            deque_push_back(pt_deqex, 575);
            deque_push_back(pt_deqex, -555);
            deque_push_front(pt_deq, pt_deqex);
            _printdeque_cstl(pt_deq);
            deque_pop_back(pt_deq);
            deque_pop_front(pt_deq);
            _printdeque_cstl(pt_deq);
            deque_pop_back(pt_deq);
            deque_pop_back(pt_deq);
            deque_pop_front(pt_deq);
            deque_pop_front(pt_deq);
            _printdeque_cstl(pt_deq);
            deque_pop_front(pt_deq);
            _printdeque_cstl(pt_deq);
            deque_clear(pt_deqex);
            deque_push_back(pt_deqex, 100);
            deque_push_back(pt_deqex, 100);
            deque_push_front(pt_deq, pt_deqex);
            _printdeque_cstl(pt_deq);
            deque_pop_back(pt_deq);
            _printdeque_cstl(pt_deq);
            deque_destroy(pt_deq);
            deque_destroy(pt_deqex);
        }
        /* deque_pop_back() */
        /* deque_push_front() */
        /* deque_pop_front() */
        /* deque_erase() */
        {
            deque_t* pt_deq = create_deque(deque_t<int>);
            deque_t* pt_deqex = create_deque(int);
            if(pt_deq == NULL || pt_deqex == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            deque_init(pt_deqex);
            deque_push_back(pt_deqex, 908);
            deque_push_back(pt_deqex, -223);
            deque_push_back(pt_deqex, 22);
            deque_push_back(pt_deq, pt_deqex);
            deque_clear(pt_deqex);
            deque_push_back(pt_deqex, -1);
            deque_push_back(pt_deq, pt_deqex);
            deque_clear(pt_deqex);
            deque_push_back(pt_deqex, 0);
            deque_push_back(pt_deqex, 1999);
            deque_push_back(pt_deqex, -4);
            deque_push_back(pt_deqex, 2223);
            deque_push_back(pt_deq, pt_deqex);
            deque_clear(pt_deqex);
            deque_push_front(pt_deqex, -445);
            deque_push_front(pt_deqex, 2323);
            deque_push_front(pt_deq, pt_deqex);
            deque_clear(pt_deqex);
            deque_push_back(pt_deqex, -555);
            deque_push_back(pt_deqex, 555);
            deque_push_back(pt_deqex, -555);
            deque_push_back(pt_deqex, 555);
            deque_push_back(pt_deqex, -555);
            deque_push_back(pt_deqex, 555);
            deque_push_back(pt_deqex, -555);
            deque_push_back(pt_deqex, 555);
            deque_push_back(pt_deqex, -555);
            deque_push_front(pt_deq, pt_deqex);
            deque_clear(pt_deqex);
            deque_push_back(pt_deqex, 234);
            deque_push_back(pt_deqex, 55);
            deque_push_front(pt_deq, pt_deqex);
            deque_push_back(pt_deqex, 5);
            deque_push_back(pt_deqex, 40);
            deque_push_back(pt_deqex, 1);
            deque_push_back(pt_deqex, -58);
            deque_push_back(pt_deqex, -741);
            deque_push_back(pt_deqex, 352);
            deque_push_back(pt_deqex, 9557);
            deque_push_back(pt_deqex, 575);
            deque_push_back(pt_deqex, -555);
            deque_push_front(pt_deq, pt_deqex);
            _printdeque_cstl(pt_deq);
            deque_erase(pt_deq, deque_begin(pt_deq));
            _printdeque_cstl(pt_deq);
            deque_erase(pt_deq, iterator_prev(deque_end(pt_deq)));
            _printdeque_cstl(pt_deq);
            deque_erase(pt_deq, iterator_next(deque_begin(pt_deq)));
            _printdeque_cstl(pt_deq);
            deque_erase(pt_deq, iterator_prev_n(deque_end(pt_deq), 2));
            _printdeque_cstl(pt_deq);
            deque_erase(pt_deq, deque_begin(pt_deq));
            deque_erase(pt_deq, deque_begin(pt_deq));
            deque_erase(pt_deq, deque_begin(pt_deq));
            _printdeque_cstl(pt_deq);
            deque_destroy(pt_deq);
            deque_destroy(pt_deqex);
        }
        /* deque_erase_range() */
        {
            deque_t* pt_deq = create_deque(deque_t<int>);
            deque_t* pt_deqex = create_deque(int);
            if(pt_deq == NULL || pt_deqex == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            deque_init(pt_deqex);
            deque_push_back(pt_deqex, 908);
            deque_push_back(pt_deqex, -223);
            deque_push_back(pt_deqex, 22);
            deque_push_back(pt_deq, pt_deqex);
            deque_clear(pt_deqex);
            deque_push_back(pt_deqex, -1);
            deque_push_back(pt_deq, pt_deqex);
            deque_clear(pt_deqex);
            deque_push_back(pt_deqex, 0);
            deque_push_back(pt_deqex, 1999);
            deque_push_back(pt_deqex, -4);
            deque_push_back(pt_deqex, 2223);
            deque_push_back(pt_deq, pt_deqex);
            deque_clear(pt_deqex);
            deque_push_front(pt_deqex, -445);
            deque_push_front(pt_deqex, 2323);
            deque_push_front(pt_deq, pt_deqex);
            deque_clear(pt_deqex);
            deque_push_back(pt_deqex, -555);
            deque_push_back(pt_deqex, 555);
            deque_push_back(pt_deqex, -555);
            deque_push_back(pt_deqex, 555);
            deque_push_back(pt_deqex, -555);
            deque_push_back(pt_deqex, 555);
            deque_push_back(pt_deqex, -555);
            deque_push_back(pt_deqex, 555);
            deque_push_back(pt_deqex, -555);
            deque_push_front(pt_deq, pt_deqex);
            deque_clear(pt_deqex);
            deque_push_back(pt_deqex, 234);
            deque_push_back(pt_deqex, 55);
            deque_push_front(pt_deq, pt_deqex);
            deque_push_back(pt_deqex, 5);
            deque_push_back(pt_deqex, 40);
            deque_push_back(pt_deqex, 1);
            deque_push_back(pt_deqex, -58);
            deque_push_back(pt_deqex, -741);
            deque_push_back(pt_deqex, 352);
            deque_push_back(pt_deqex, 9557);
            deque_push_back(pt_deqex, 575);
            deque_push_back(pt_deqex, -555);
            deque_push_front(pt_deq, pt_deqex);
            _printdeque_cstl(pt_deq);
            deque_erase_range(pt_deq,
                deque_begin(pt_deq), iterator_next_n(deque_begin(pt_deq), 2));
            _printdeque_cstl(pt_deq);
            deque_erase_range(pt_deq,
                iterator_prev_n(deque_end(pt_deq), 2), deque_end(pt_deq));
            _printdeque_cstl(pt_deq);
            deque_erase_range(pt_deq,
                iterator_next(deque_begin(pt_deq)), iterator_prev_n(deque_end(pt_deq), 2));
            _printdeque_cstl(pt_deq);
            deque_erase_range(pt_deq,
                iterator_next(deque_begin(pt_deq)), iterator_prev(deque_end(pt_deq)));
            _printdeque_cstl(pt_deq);
            deque_erase_range(pt_deq, deque_begin(pt_deq), deque_end(pt_deq));
            _printdeque_cstl(pt_deq);
            deque_destroy(pt_deq);
            deque_destroy(pt_deqex);
        }
        /* deque_clear() */
        {
            deque_t* pt_deq = create_deque(deque_t<int>);
            deque_t* pt_deqex = create_deque(int);
            if(pt_deq == NULL || pt_deqex == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            deque_init(pt_deqex);
            _printdeque_cstl(pt_deq);
            deque_clear(pt_deq);
            _printdeque_cstl(pt_deq);
            deque_push_back(pt_deqex, 908);
            deque_push_back(pt_deqex, -223);
            deque_push_back(pt_deqex, 22);
            deque_push_back(pt_deq, pt_deqex);
            deque_clear(pt_deqex);
            deque_push_back(pt_deqex, -1);
            deque_push_back(pt_deq, pt_deqex);
            deque_clear(pt_deqex);
            deque_push_back(pt_deqex, 0);
            deque_push_back(pt_deqex, 1999);
            deque_push_back(pt_deqex, -4);
            deque_push_back(pt_deqex, 2223);
            deque_push_back(pt_deq, pt_deqex);
            deque_clear(pt_deqex);
            deque_push_front(pt_deqex, -445);
            deque_push_front(pt_deqex, 2323);
            deque_push_front(pt_deq, pt_deqex);
            deque_clear(pt_deqex);
            deque_push_back(pt_deqex, -555);
            deque_push_back(pt_deqex, 555);
            deque_push_back(pt_deqex, -555);
            deque_push_back(pt_deqex, 555);
            deque_push_back(pt_deqex, -555);
            deque_push_back(pt_deqex, 555);
            deque_push_back(pt_deqex, -555);
            deque_push_back(pt_deqex, 555);
            deque_push_back(pt_deqex, -555);
            deque_push_front(pt_deq, pt_deqex);
            deque_clear(pt_deqex);
            deque_push_back(pt_deqex, 234);
            deque_push_back(pt_deqex, 55);
            deque_push_front(pt_deq, pt_deqex);
            deque_push_back(pt_deqex, 5);
            deque_push_back(pt_deqex, 40);
            deque_push_back(pt_deqex, 1);
            deque_push_back(pt_deqex, -58);
            deque_push_back(pt_deqex, -741);
            deque_push_back(pt_deqex, 352);
            deque_push_back(pt_deqex, 9557);
            deque_push_back(pt_deqex, 575);
            deque_push_back(pt_deqex, -555);
            deque_push_front(pt_deq, pt_deqex);
            _printdeque_cstl(pt_deq);
            deque_clear(pt_deq);
            _printdeque_cstl(pt_deq);
            deque_destroy(pt_deq);
            deque_destroy(pt_deqex);
        }
        /* deque_resize() */
        {
            deque_t* pt_deq = create_deque(deque_t<int>);
            if(pt_deq == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            _printdeque_cstl(pt_deq);
            deque_resize(pt_deq, 4);
            _printdeque_cstl(pt_deq);
            deque_resize(pt_deq, 13);
            _printdeque_cstl(pt_deq);
            deque_resize(pt_deq, 8);
            _printdeque_cstl(pt_deq);
            deque_resize(pt_deq, 0);
            _printdeque_cstl(pt_deq);
            deque_destroy(pt_deq);
        }
        /* deque_resize_elem() */
        {
            deque_t* pt_deq = create_deque(deque_t<int>);
            deque_t* pt_deqex = create_deque(int);
            if(pt_deq == NULL || pt_deqex == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            deque_init(pt_deqex);
            _printdeque_cstl(pt_deq);
            deque_push_back(pt_deqex, 908);
            deque_push_back(pt_deqex, -223);
            deque_push_back(pt_deqex, 22);
            deque_resize_elem(pt_deq, 3, pt_deqex);
            _printdeque_cstl(pt_deq);
            deque_clear(pt_deqex);
            deque_push_back(pt_deqex, -1);
            deque_resize_elem(pt_deq, 11, pt_deqex);
            _printdeque_cstl(pt_deq);
            deque_clear(pt_deqex);
            deque_push_back(pt_deqex, 0);
            deque_push_back(pt_deqex, 1999);
            deque_push_back(pt_deqex, -4);
            deque_push_back(pt_deqex, 2223);
            deque_resize_elem(pt_deq, 6, pt_deqex);
            _printdeque_cstl(pt_deq);
            deque_clear(pt_deqex);
            deque_push_front(pt_deqex, -445);
            deque_push_front(pt_deqex, 2323);
            deque_resize_elem(pt_deq, 0, pt_deqex);
            _printdeque_cstl(pt_deq);
            deque_destroy(pt_deq);
            deque_destroy(pt_deqex);
        }
    }
    /* c-string type */
    {
        /*create_deque         */
        {
            deque_t* pt_deq = create_deque(char*);
            if(pt_deq == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            _print_deq_str(pt_deq);
            deque_destroy(pt_deq);
        }
        /*deque_init           */
        /*deque_init_n         */
        {
            deque_t* pt_deq = create_deque(char*);
            if(pt_deq == NULL)
            {
                return;
            }
            deque_init_n(pt_deq, 10);
            _print_deq_str(pt_deq);
            deque_destroy(pt_deq);
        }
        /*deque_init_elem      */
        {
            deque_t* pt_deq = create_deque(char*);
            if(pt_deq == NULL)
            {
                return;
            }
            deque_init_elem(pt_deq, 10, "VMware Workstation");
            _print_deq_str(pt_deq);
            deque_destroy(pt_deq);
        }
        /*deque_init_copy      */
        {
            deque_t* pt_deq = create_deque(char*);
            deque_t* pt_deqex = create_deque(char*);
            if(pt_deq == NULL || pt_deqex == NULL)
            {
                return;
            }
            deque_init_elem(pt_deqex, 5, "ActiveSys");
            deque_init_copy(pt_deq, pt_deqex);
            _print_deq_str(pt_deq);
            deque_destroy(pt_deq);
            deque_destroy(pt_deqex);
        }
        /*deque_init_copy_range*/
        {
            deque_t* pt_deq = create_deque(char*);
            deque_t* pt_deqex = create_deque(char*);
            if(pt_deq == NULL || pt_deqex == NULL)
            {
                return;
            }
            deque_init(pt_deqex);
            deque_push_back(pt_deqex,
                "1.      Introduction ...........................................   3");
            deque_push_back(pt_deqex,
                "1.1.     Conventions Used in This Document .....................   4");
            deque_push_back(pt_deqex,
                "1.2.     Example mail messages .................................   4");
            deque_push_back(pt_deqex,
                "2.      Design .................................................   5");
            deque_push_back(pt_deqex,
                "2.1.     Form of the Language ..................................   5");
            deque_push_back(pt_deqex,
                "2.2.     Whitespace ............................................   5");
            _print_deq_str(pt_deqex);
            deque_init_copy_range(pt_deq, deque_begin(pt_deqex), deque_end(pt_deqex));
            _print_deq_str(pt_deq);
            deque_destroy(pt_deq);
            deque_destroy(pt_deqex);
        }
        /*deque_destroy        */
        /*deque_empty          */
        /*deque_size           */
        /*deque_max_size       */
        /*deque_begin          */
        /*deque_end            */
        /*deque_assign         */
        {
            deque_t* pt_deq = create_deque(char*);
            deque_t* pt_deqex = create_deque(char*);
            if(pt_deq == NULL || pt_deqex == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            deque_init(pt_deqex);
            deque_push_back(pt_deqex,
                "1.      Introduction ...........................................   3");
            deque_push_back(pt_deqex,
                "1.1.     Conventions Used in This Document .....................   4");
            deque_push_back(pt_deqex,
                "1.2.     Example mail messages .................................   4");
            deque_push_back(pt_deqex,
                "2.      Design .................................................   5");
            deque_push_back(pt_deqex,
                "2.1.     Form of the Language ..................................   5");
            deque_push_back(pt_deqex,
                "2.2.     Whitespace ............................................   5");
            deque_assign(pt_deq, pt_deqex);
            _print_deq_str(pt_deq);
            deque_destroy(pt_deq);
            deque_destroy(pt_deqex);
        }
        /*deque_assign_elem    */
        {
            deque_t* pt_deq = create_deque(char*);
            if(pt_deq == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            deque_assign_elem(pt_deq, 0,
                "2.10.5.  Extensions and Optional Features ......................  16");
            _print_deq_str(pt_deq);
            deque_assign_elem(pt_deq, 4,
                "6.2.1.   Template for Capability Registrations .................  28");
            _print_deq_str(pt_deq);
            deque_assign_elem(pt_deq, 9,
                "14.     Full Copyright Statement ...............................  36");
            _print_deq_str(pt_deq);
            deque_assign_elem(pt_deq, 3,
                "This memo documents a language that can be used to create filters for");
            _print_deq_str(pt_deq);
            deque_assign_elem(pt_deq, 0,
                "not Turing-complete: it provides no way to write a loop or a function");
            _print_deq_str(pt_deq);
            deque_destroy(pt_deq);
        }
        /*deque_assign_range   */
        {
            deque_t* pt_deq = create_deque(char*);
            deque_t* pt_deqex = create_deque(char*);
            if(pt_deq == NULL || pt_deqex == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            deque_init(pt_deqex);
            deque_assign_range(pt_deq, deque_begin(pt_deqex), deque_end(pt_deqex));
            _print_deq_str(pt_deq);
            deque_push_back(pt_deqex,
                "1.      Introduction ...........................................   3");
            deque_push_back(pt_deqex,
                "1.1.     Conventions Used in This Document .....................   4");
            deque_push_back(pt_deqex,
                "1.2.     Example mail messages .................................   4");
            deque_push_back(pt_deqex,
                "2.      Design .................................................   5");
            deque_push_back(pt_deqex,
                "2.1.     Form of the Language ..................................   5");
            deque_push_back(pt_deqex,
                "2.2.     Whitespace ............................................   5");
            deque_push_back(pt_deqex,
                "2.3.     Comments ..............................................   6");
            deque_push_back(pt_deqex,
                "2.4.     Literal Data ..........................................   6");
            deque_push_back(pt_deqex,
                "2.4.1.   Numbers ...............................................   6");
            _print_deq_str(pt_deqex);
            deque_assign_range(pt_deq, deque_begin(pt_deqex), deque_begin(pt_deqex));
            _print_deq_str(pt_deq);
            deque_assign_range(pt_deq, deque_begin(pt_deqex), iterator_next_n(deque_begin(pt_deqex), 3));
            _print_deq_str(pt_deq);
            deque_assign_range(pt_deq,
                iterator_next_n(deque_begin(pt_deqex), 2), iterator_next_n(deque_begin(pt_deqex), 5));
            _print_deq_str(pt_deq);
            deque_assign_range(pt_deq,
                iterator_next_n(deque_begin(pt_deqex), 5), deque_end(pt_deqex));
            _print_deq_str(pt_deq);
            deque_assign_range(pt_deq, deque_end(pt_deqex), deque_end(pt_deqex));
            _print_deq_str(pt_deq);
            deque_assign_range(pt_deq, deque_begin(pt_deqex), deque_end(pt_deqex));
            _print_deq_str(pt_deq);
            deque_destroy(pt_deq);
            deque_destroy(pt_deqex);
        }
        /*deque_equal          */
        /*deque_not_equal      */
        /*deque_less           */
        /*deque_less_equal     */
        /*deque_great          */
        /*deque_great_equal    */
        {
            deque_t* pt_deq = create_deque(char*);
            deque_t* pt_deqex = create_deque(char*);
            if(pt_deq == NULL || pt_deqex == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            deque_init(pt_deqex);
            _print_deq_str(pt_deq);
            _print_deq_str(pt_deqex);
            printf("equal: %d, not equal: %d, ",
                deque_equal(pt_deq, pt_deqex), deque_not_equal(pt_deq, pt_deqex));
            printf("less: %d, less equal: %d, ",
                deque_less(pt_deq, pt_deqex), deque_less_equal(pt_deq, pt_deqex));
            printf("great: %d, great equal: %d\n",
                deque_great(pt_deq, pt_deqex), deque_great_equal(pt_deq, pt_deqex));
            deque_push_back(pt_deq, "China");
            _print_deq_str(pt_deq);
            _print_deq_str(pt_deqex);
            printf("equal: %d, not equal: %d, ",
                deque_equal(pt_deq, pt_deqex), deque_not_equal(pt_deq, pt_deqex));
            printf("less: %d, less equal: %d, ",
                deque_less(pt_deq, pt_deqex), deque_less_equal(pt_deq, pt_deqex));
            printf("great: %d, great equal: %d\n",
                deque_great(pt_deq, pt_deqex), deque_great_equal(pt_deq, pt_deqex));
            deque_push_back(pt_deqex, "China");
            _print_deq_str(pt_deq);
            _print_deq_str(pt_deqex);
            printf("equal: %d, not equal: %d, ",
                deque_equal(pt_deq, pt_deqex), deque_not_equal(pt_deq, pt_deqex));
            printf("less: %d, less equal: %d, ",
                deque_less(pt_deq, pt_deqex), deque_less_equal(pt_deq, pt_deqex));
            printf("great: %d, great equal: %d\n",
                deque_great(pt_deq, pt_deqex), deque_great_equal(pt_deq, pt_deqex));
            deque_push_back(pt_deqex, "Unix");
            _print_deq_str(pt_deq);
            _print_deq_str(pt_deqex);
            printf("equal: %d, not equal: %d, ",
                deque_equal(pt_deq, pt_deqex), deque_not_equal(pt_deq, pt_deqex));
            printf("less: %d, less equal: %d, ",
                deque_less(pt_deq, pt_deqex), deque_less_equal(pt_deq, pt_deqex));
            printf("great: %d, great equal: %d\n",
                deque_great(pt_deq, pt_deqex), deque_great_equal(pt_deq, pt_deqex));
            deque_push_back(pt_deq, "Pub");
            deque_push_back(pt_deq, "CSDN");
            _print_deq_str(pt_deq);
            _print_deq_str(pt_deqex);
            printf("equal: %d, not equal: %d, ",
                deque_equal(pt_deq, pt_deqex), deque_not_equal(pt_deq, pt_deqex));
            printf("less: %d, less equal: %d, ",
                deque_less(pt_deq, pt_deqex), deque_less_equal(pt_deq, pt_deqex));
            printf("great: %d, great equal: %d\n",
                deque_great(pt_deq, pt_deqex), deque_great_equal(pt_deq, pt_deqex));

            deque_destroy(pt_deq);
            deque_destroy(pt_deqex);
        }
        /*deque_at             */
        /*deque_swap           */
        {
            deque_t* pt_deq = create_deque(char*);
            deque_t* pt_deqex = create_deque(char*);
            if(pt_deq == NULL || pt_deqex == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            deque_init(pt_deqex);
            deque_swap(pt_deq, pt_deqex);
            _print_deq_str(pt_deq);
            _print_deq_str(pt_deqex);
            deque_assign_elem(pt_deqex, 4, "A Mail Filtering Language");
            deque_swap(pt_deq, pt_deqex);
            _print_deq_str(pt_deq);
            _print_deq_str(pt_deqex);
            deque_assign_elem(pt_deqex, 9, "Extensions and Optional Features");
            deque_swap(pt_deq, pt_deqex);
            _print_deq_str(pt_deq);
            _print_deq_str(pt_deqex);
            deque_assign_elem(pt_deqex, 2, "Capability String");
            deque_swap(pt_deq, pt_deqex);
            _print_deq_str(pt_deq);
            _print_deq_str(pt_deqex);
            deque_assign_elem(pt_deqex, 0, "Transmission");
            deque_swap(pt_deq, pt_deqex);
            _print_deq_str(pt_deq);
            _print_deq_str(pt_deqex);
            deque_destroy(pt_deq);
            deque_destroy(pt_deqex);
        }
        /*deque_front          */
        /*deque_back           */
        /*deque_push_back      */
        /*deque_pop_back       */
        /*deque_push_front     */
        /*deque_pop_front      */
        {
            deque_t* pt_deq = create_deque(char*);
            if(pt_deq == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            _print_deq_str(pt_deq);
            deque_push_front(pt_deq, "MTA");
            puts(deque_front(pt_deq));
            deque_push_front(pt_deq, "[FLAMES]");
            puts(deque_front(pt_deq));
            deque_push_front(pt_deq, "GUI-based");
            puts(deque_front(pt_deq));
            deque_push_front(pt_deq, "");
            puts(deque_front(pt_deq));
            deque_push_front(pt_deq, "preferred");
            puts(deque_front(pt_deq));
            while(!deque_empty(pt_deq))
            {
                deque_pop_back(pt_deq);
            }
            _print_deq_str(pt_deq);

            deque_push_back(pt_deq, "Conventions Used in This Document");
            puts(deque_back(pt_deq));
            deque_push_back(pt_deq, "parenthesis are used for grouping, similar to [ABNF].");
            puts(deque_back(pt_deq));
            deque_push_back(pt_deq, "These are discussed in sections 2.7.1, 2.7.3, and 2.7.4");
            puts(deque_back(pt_deq));
            while(!deque_empty(pt_deq))
            {
                deque_pop_front(pt_deq);
            }
            _print_deq_str(pt_deq);

            deque_destroy(pt_deq);
        }
        /*deque_insert_range   */
        {
            deque_t* pt_deq = create_deque(char*);
            deque_t* pt_deqex = create_deque(char*);
            if(pt_deq == NULL || pt_deqex == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            deque_init(pt_deqex);
            deque_insert_range(pt_deq, deque_begin(pt_deq),
                deque_begin(pt_deqex), deque_end(pt_deqex));
            _print_deq_str(pt_deq);

            deque_push_back(pt_deqex, "YOU MAY HAVE ALREADY WON TEN MILLION DOLLARS, BUT I DOUBT");
            deque_push_back(pt_deqex, "IT!  SO JUST POST THIS TO SIX HUNDRED NEWSGROUPS!  IT WILL");
            deque_push_back(pt_deqex, "GUARANTEE THAT YOU GET AT LEAST FIVE RESPONSES WITH MONEY!");
            deque_push_back(pt_deqex, "MONEY! MONEY! COLD HARD CASH!  YOU WILL RECEIVE OVER");
            deque_push_back(pt_deqex, "$20,000 IN LESS THAN TWO MONTHS!  AND IT'S LEGAL!!!!!!!!!");
            deque_push_back(pt_deqex, "!!!!!!!!!!!!!!!!!!111111111!!!!!!!11111111111!!1  JUST");
            deque_push_back(pt_deqex, "SEND $5 IN SMALL, UNMARKED BILLS TO THE ADDRESSES BELOW!");
            deque_push_back(pt_deqex, "Subject: $$$ YOU, TOO, CAN BE A MILLIONAIRE! $$");
            _print_deq_str(pt_deqex);

            deque_insert_range(pt_deq, deque_begin(pt_deq),
                deque_begin(pt_deqex), deque_begin(pt_deqex));
            _print_deq_str(pt_deq);
            deque_insert_range(pt_deq, deque_begin(pt_deq),
                deque_begin(pt_deqex), iterator_next_n(deque_begin(pt_deqex), 3));
            _print_deq_str(pt_deq);
            deque_insert_range(pt_deq, deque_begin(pt_deq),
                iterator_next(deque_begin(pt_deqex)), iterator_next_n(deque_begin(pt_deqex), 5));
            _print_deq_str(pt_deq);
            deque_insert_range(pt_deq, iterator_next_n(deque_begin(pt_deq), 2),
                iterator_next_n(deque_begin(pt_deqex), 4), deque_end(pt_deqex));
            _print_deq_str(pt_deq);
            deque_insert_range(pt_deq, deque_end(pt_deq), deque_end(pt_deqex), deque_end(pt_deqex));
            _print_deq_str(pt_deq);
            deque_insert_range(pt_deq, deque_end(pt_deq), deque_begin(pt_deqex), deque_end(pt_deqex));
            _print_deq_str(pt_deq);

            deque_destroy(pt_deq);
            deque_destroy(pt_deqex);
        }
        /*deque_insert_n       */
        {
            deque_t* pt_deq = create_deque(char*);
            if(pt_deq == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            deque_insert_n(pt_deq, deque_begin(pt_deq), 0,
                "The fields are transmitted from left to right.");
            _print_deq_str(pt_deq);
            deque_insert_n(pt_deq, deque_begin(pt_deq), 3,
                "0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1");
            _print_deq_str(pt_deq);
            deque_insert_n(pt_deq, deque_begin(pt_deq), 5,
                "|         F_MAX_PERIOD          |          F_MAX_TIME           |");
            _print_deq_str(pt_deq);
            deque_insert_n(pt_deq, iterator_next_n(deque_begin(pt_deq), 5), 2, "");
            _print_deq_str(pt_deq);
            deque_insert_n(pt_deq, deque_end(pt_deq), 3, "IP-Compression-Protocol");
            _print_deq_str(pt_deq);
            deque_destroy(pt_deq);
        }
        /*deque_erase          */
        {
            deque_t* pt_deq = create_deque(char*);
            if(pt_deq == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            deque_push_back(pt_deq,
                " 0                   1                   2                   3");
            deque_push_back(pt_deq,
                " 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1");
            deque_push_back(pt_deq,
                "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+");
            deque_push_back(pt_deq,
                "|     Type      |    Length     |    IP-Compression-Protocol    |");
            deque_push_back(pt_deq,
                "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+");
            deque_push_back(pt_deq,
                "|           TCP_SPACE           |         NON_TCP_SPACE         |");
            deque_push_back(pt_deq,
                "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+");
            deque_push_back(pt_deq,
                "|         F_MAX_PERIOD          |          F_MAX_TIME           |");
            deque_push_back(pt_deq,
                "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+");
            deque_push_back(pt_deq,
                "|           MAX_HEADER          |          suboptions...");
            deque_push_back(pt_deq,
                "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+");
            _print_deq_str(pt_deq);
            deque_erase(pt_deq, deque_begin(pt_deq));
            _print_deq_str(pt_deq);
            deque_erase(pt_deq, iterator_prev(deque_end(pt_deq)));
            _print_deq_str(pt_deq);
            deque_erase(pt_deq, iterator_next_n(deque_begin(pt_deq), 3));
            _print_deq_str(pt_deq);

            while(!deque_empty(pt_deq))
            {
                deque_erase(pt_deq, deque_begin(pt_deq));
            }
            _print_deq_str(pt_deq);
            deque_destroy(pt_deq);
        }
        /*deque_erase_range    */
        {
            deque_t* pt_deq = create_deque(char*);
            if(pt_deq == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            deque_erase_range(pt_deq, deque_begin(pt_deq), deque_end(pt_deq));
            _print_deq_str(pt_deq);
            deque_push_back(pt_deq,
                " 0                   1                   2                   3");
            deque_push_back(pt_deq,
                " 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1");
            deque_push_back(pt_deq,
                "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+");
            deque_push_back(pt_deq,
                "|     Type      |    Length     |    IP-Compression-Protocol    |");
            deque_push_back(pt_deq,
                "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+");
            deque_push_back(pt_deq,
                "|           TCP_SPACE           |         NON_TCP_SPACE         |");
            deque_push_back(pt_deq,
                "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+");
            deque_push_back(pt_deq,
                "|         F_MAX_PERIOD          |          F_MAX_TIME           |");
            deque_push_back(pt_deq,
                "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+");
            deque_push_back(pt_deq,
                "|           MAX_HEADER          |          suboptions...");
            deque_push_back(pt_deq,
                "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+");
            _print_deq_str(pt_deq);
            deque_erase_range(pt_deq, deque_begin(pt_deq), deque_begin(pt_deq));
            _print_deq_str(pt_deq);
            deque_erase_range(pt_deq, deque_begin(pt_deq), iterator_next_n(deque_begin(pt_deq), 2));
            _print_deq_str(pt_deq);
            deque_erase_range(pt_deq,
                iterator_next(deque_begin(pt_deq)), iterator_next_n(deque_begin(pt_deq), 4));
            _print_deq_str(pt_deq);
            deque_erase_range(pt_deq, iterator_prev_n(deque_end(pt_deq), 3), deque_end(pt_deq));
            _print_deq_str(pt_deq);
            deque_erase_range(pt_deq, deque_end(pt_deq), deque_end(pt_deq));
            _print_deq_str(pt_deq);
            deque_erase_range(pt_deq, deque_begin(pt_deq), deque_end(pt_deq));
            _print_deq_str(pt_deq);
            deque_destroy(pt_deq);
        }
        /*deque_clear          */
        {
            deque_t* pt_deq = create_deque(char*);
            if(pt_deq == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            deque_clear(pt_deq);
            _print_deq_str(pt_deq);
            
            deque_push_back(pt_deq,
                " 0                   1                   2                   3");
            deque_push_back(pt_deq,
                " 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1");
            deque_push_back(pt_deq,
                "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+");
            deque_push_back(pt_deq,
                "|     Type      |    Length     |    IP-Compression-Protocol    |");
            deque_push_back(pt_deq,
                "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+");
            deque_push_back(pt_deq,
                "|           TCP_SPACE           |         NON_TCP_SPACE         |");
            deque_push_back(pt_deq,
                "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+");
            deque_push_back(pt_deq,
                "|         F_MAX_PERIOD          |          F_MAX_TIME           |");
            deque_push_back(pt_deq,
                "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+");
            deque_push_back(pt_deq,
                "|           MAX_HEADER          |          suboptions...");
            deque_push_back(pt_deq,
                "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+");
            _print_deq_str(pt_deq);
            deque_clear(pt_deq);
            _print_deq_str(pt_deq);
            deque_destroy(pt_deq);
        }
        /*deque_resize         */
        {
            deque_t* pt_deq = create_deque(char*);
            if(pt_deq == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            deque_resize(pt_deq, 0);
            _print_deq_str(pt_deq);
            deque_resize(pt_deq, 5);
            _print_deq_str(pt_deq);
            deque_resize(pt_deq, 10);
            _print_deq_str(pt_deq);
            deque_resize(pt_deq, 3);
            _print_deq_str(pt_deq);
            deque_resize(pt_deq, 0);
            _print_deq_str(pt_deq);
            deque_destroy(pt_deq);
        }
        /*deque_resize_elem    */
        {
            deque_t* pt_deq = create_deque(char*);
            if(pt_deq == NULL)
            {
                return;
            }
            deque_init(pt_deq);
            deque_resize_elem(pt_deq, 0, "Suggested value: 15");
            _print_deq_str(pt_deq);
            deque_resize_elem(pt_deq, 7, "F_MAX_PERIOD");
            _print_deq_str(pt_deq);
            deque_resize_elem(pt_deq, 31, "IP Header Compression over PPP");
            _print_deq_str(pt_deq);
            deque_resize_elem(pt_deq, 13, "");
            _print_deq_str(pt_deq);
            deque_resize_elem(pt_deq, 0, "IP/UDP/RTP");
            _print_deq_str(pt_deq);
            deque_destroy(pt_deq);
        }
    }
}

/** local function implementation section **/
static void _print_deq_str(const deque_t* pt_deque)
{
    size_t i = 0;

    assert(pt_deque != NULL);
    printf("====================================\n");
    printf("empty: %u, size: %u, max_size: %u\n",
        deque_empty(pt_deque), deque_size(pt_deque), deque_max_size(pt_deque));
    for(i = 0; i < deque_size(pt_deque); ++i)
    {
        puts((char*)deque_at(pt_deque, i));
    }
}

static void _printdeque_cstl(const deque_t* pt_deque)
{
    iterator_t t_iter, t_iterex;
    printf("=========================================\n");
    for(t_iter = deque_begin(pt_deque);
        !iterator_equal(t_iter, deque_end(pt_deque));
        t_iter = iterator_next(t_iter))
    {
        for(t_iterex = deque_begin(iterator_get_pointer(t_iter));
            !iterator_equal(t_iterex, deque_end(iterator_get_pointer(t_iter)));
            t_iterex = iterator_next(t_iterex))
        {
            printf("%d, ", *(int*)iterator_get_pointer(t_iterex));
        }
        printf("\n");
    }
}

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

