/*
 *  The implementation of slist test.
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
#include "cslist.h"
#include "test_slist.h"

/** local constant declaration and local macro section **/
#define _printslist_c(pt_slist, fmt, type)\
    do{\
        iterator_t t_iter;\
        printf("==================================\n");\
        for(t_iter = slist_begin(pt_slist);\
            !iterator_equal(t_iter, slist_end(pt_slist));\
            t_iter = iterator_next(t_iter)){\
            printf(fmt, *(type*)iterator_get_pointer(t_iter));\
        }printf("\n");\
    }while(false)

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/
static void _slist_remove_pred(const void* cpv_input, void* pv_output);

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
void test_slist(void)
{
    /* c built-in type */
    {
        /*create_slist            */
        {
            slist_t* pt_slist = create_slist(int);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_destroy(pt_slist);
        }
        /*slist_init              */
        /*slist_init_n            */
        {
            slist_t* pt_slist = create_slist(double);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init_n(pt_slist, 21);
            _printslist_c(pt_slist, "%lf, ", double);
            slist_destroy(pt_slist);
        }
        /*slist_init_elem         */
        {
            slist_t* pt_slist = create_slist(double);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init_elem(pt_slist, 21, 45.9801);
            _printslist_c(pt_slist, "%lf, ", double);
            slist_destroy(pt_slist);
        }
        /*slist_init_copy         */
        {
            slist_t* pt_slist = create_slist(long);
            slist_t* pt_slistex = create_slist(signed long int);
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init_elem(pt_slistex, 8, 23097);
            slist_init_copy(pt_slist, pt_slistex);
            _printslist_c(pt_slist, "%ld, ", long);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_init_copy_range   */
        {
            slist_t* pt_slist = create_slist(int);
            slist_t* pt_slistex = create_slist(signed int);
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slistex);
            slist_push_front(pt_slistex, 39);
            slist_push_front(pt_slistex, 88);
            slist_push_front(pt_slistex, 212);
            slist_push_front(pt_slistex, 999);
            slist_push_front(pt_slistex, 90);
            slist_init_copy_range(pt_slist,
                slist_begin(pt_slistex), iterator_advance(slist_begin(pt_slistex), 3));
            _printslist_c(pt_slist, "%d, ", int);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_destroy           */
        /*slist_size              */
        {
            slist_t* pt_slist = create_slist(int);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            printf("empty : %d, size : %d, max size : %d\n",
                slist_empty(pt_slist), slist_size(pt_slist), slist_max_size(pt_slist));
            slist_push_front(pt_slist, 34);
            slist_push_front(pt_slist, 90);
            printf("empty : %d, size : %d, max size : %d\n",
                slist_empty(pt_slist), slist_size(pt_slist), slist_max_size(pt_slist));
            slist_destroy(pt_slist);
        }
        /*slist_empty             */
        /*slist_max_size          */
        /*slist_begin             */
        /*slist_end               */
        /*slist_previous          */
        {
            slist_t* pt_slist = create_slist(int);
            iterator_t t_iter;
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_push_front(pt_slist, 34);
            slist_push_front(pt_slist, 129);
            slist_push_front(pt_slist, 1111);
            printf("%d\n", *(int*)iterator_get_pointer(
                slist_previous(pt_slist, slist_end(pt_slist))));
            t_iter = iterator_next(slist_begin(pt_slist));
            printf("%d\n", *(int*)iterator_get_pointer(slist_previous(pt_slist, t_iter)));
            slist_destroy(pt_slist);
        }
        /*slist_equal             */
        {
            slist_t* pt_slist = create_slist(int);
            slist_t* pt_slistex = create_slist(int);
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            printf("equal : %d, not equal : %d\n",
                slist_equal(pt_slist, pt_slistex), slist_not_equal(pt_slist, pt_slistex));
            printf("less : %d, less equal : %d\n",
                slist_less(pt_slist, pt_slistex), slist_less_equal(pt_slist, pt_slistex));
            printf("great : %d, great equal : %d\n",
                slist_great(pt_slist, pt_slistex), slist_great_equal(pt_slist, pt_slistex));

            slist_push_front(pt_slist, 43);
            printf("equal : %d, not equal : %d\n",
                slist_equal(pt_slist, pt_slistex), slist_not_equal(pt_slist, pt_slistex));
            printf("less : %d, less equal : %d\n",
                slist_less(pt_slist, pt_slistex), slist_less_equal(pt_slist, pt_slistex));
            printf("great : %d, great equal : %d\n",
                slist_great(pt_slist, pt_slistex), slist_great_equal(pt_slist, pt_slistex));

            slist_push_front(pt_slistex, 43);
            printf("equal : %d, not equal : %d\n",
                slist_equal(pt_slist, pt_slistex), slist_not_equal(pt_slist, pt_slistex));
            printf("less : %d, less equal : %d\n",
                slist_less(pt_slist, pt_slistex), slist_less_equal(pt_slist, pt_slistex));
            printf("great : %d, great equal : %d\n",
                slist_great(pt_slist, pt_slistex), slist_great_equal(pt_slist, pt_slistex));

            slist_push_front(pt_slistex, 132);
            printf("equal : %d, not equal : %d\n",
                slist_equal(pt_slist, pt_slistex), slist_not_equal(pt_slist, pt_slistex));
            printf("less : %d, less equal : %d\n",
                slist_less(pt_slist, pt_slistex), slist_less_equal(pt_slist, pt_slistex));
            printf("great : %d, great equal : %d\n",
                slist_great(pt_slist, pt_slistex), slist_great_equal(pt_slist, pt_slistex));

            slist_push_front(pt_slist, 100);
            slist_push_front(pt_slist, 12);
            printf("equal : %d, not equal : %d\n",
                slist_equal(pt_slist, pt_slistex), slist_not_equal(pt_slist, pt_slistex));
            printf("less : %d, less equal : %d\n",
                slist_less(pt_slist, pt_slistex), slist_less_equal(pt_slist, pt_slistex));
            printf("great : %d, great equal : %d\n",
                slist_great(pt_slist, pt_slistex), slist_great_equal(pt_slist, pt_slistex));

            slist_push_front(pt_slistex, 1);
            printf("equal : %d, not equal : %d\n",
                slist_equal(pt_slist, pt_slistex), slist_not_equal(pt_slist, pt_slistex));
            printf("less : %d, less equal : %d\n",
                slist_less(pt_slist, pt_slistex), slist_less_equal(pt_slist, pt_slistex));
            printf("great : %d, great equal : %d\n",
                slist_great(pt_slist, pt_slistex), slist_great_equal(pt_slist, pt_slistex));
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_not_equal         */
        /*slist_less              */
        /*slist_less_equal        */
        /*slist_great             */
        /*slist_great_equal       */
        /*slist_assign            */
        {
            slist_t* pt_slist = create_slist(long double);
            slist_t* pt_slistex = create_slist(long double);
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            slist_assign(pt_slist, pt_slistex);
            _printslist_c(pt_slist, "%Lf, ", long double);
            slist_push_front(pt_slistex, 34.980);
            slist_push_front(pt_slistex, -0.01);
            slist_push_front(pt_slistex, 44.0912);
            slist_assign(pt_slist, pt_slistex);
            printf("size:%d\n", slist_size(pt_slist));
            _printslist_c(pt_slistex, "%Lf, ", long double);
            _printslist_c(pt_slist, "%Lf, ", long double);
            printf("%Lf\n", *(long double*)iterator_get_pointer(slist_begin(pt_slist)));
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_assign_elem       */
        {
            slist_t* pt_slist = create_slist(double);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_assign_elem(pt_slist, 3, -90.334);
            _printslist_c(pt_slist, "%g, ", double);
            slist_assign_elem(pt_slist, 21, 0.0209);
            _printslist_c(pt_slist, "%g, ", double);
            slist_assign_elem(pt_slist, 7, -0.00002);
            _printslist_c(pt_slist, "%g, ", double);
            slist_assign_elem(pt_slist, 0, 88.88);
            _printslist_c(pt_slist, "%g, ", double);
            slist_destroy(pt_slist);
        }
        /*slist_assign_range      */
        {
            slist_t* pt_slist = create_slist(int);
            slist_t* pt_slistex = create_slist(signed);
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            slist_push_front(pt_slistex, 34);
            slist_push_front(pt_slistex, -88);
            slist_push_front(pt_slistex, 2009);
            slist_push_front(pt_slistex, 12345);
            slist_push_front(pt_slistex, -9888);
            slist_push_front(pt_slistex, 2);
            slist_push_front(pt_slistex, -9);
            slist_push_front(pt_slistex, -222);
            slist_push_front(pt_slistex, 2);
            slist_push_front(pt_slistex, 70);
            slist_push_front(pt_slistex, 21);
            slist_push_front(pt_slistex, 2222);
            slist_push_front(pt_slistex, 37);
            _printslist_c(pt_slistex, "%d, ", int);
            slist_assign_range(pt_slist, slist_begin(pt_slistex), slist_begin(pt_slistex));
            _printslist_c(pt_slist, "%d, ", int);
            slist_assign_range(pt_slist, slist_begin(pt_slistex),
                iterator_advance(slist_begin(pt_slistex), 2));
            _printslist_c(pt_slist, "%d, ", int);
            slist_assign_range(pt_slist, iterator_advance(slist_begin(pt_slistex), 1),
                iterator_advance(slist_begin(pt_slistex), 10));
            _printslist_c(pt_slist, "%d, ", int);
            slist_assign_range(pt_slist, iterator_advance(slist_begin(pt_slistex), 10),
                slist_end(pt_slistex));
            _printslist_c(pt_slist, "%d, ", int);
            slist_assign_range(pt_slist, slist_end(pt_slistex), slist_end(pt_slistex));
            _printslist_c(pt_slist, "%d, ", int);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_swap              */
        {
            slist_t* pt_slist = create_slist(unsigned long);
            slist_t* pt_slistex = create_slist(unsigned long int);
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            slist_swap(pt_slist, pt_slistex);
            _printslist_c(pt_slist, "%lu, ", unsigned long);
            _printslist_c(pt_slistex, "%lu, ", unsigned long);
            slist_push_front(pt_slistex, 3);
            slist_push_front(pt_slistex, 9);
            slist_push_front(pt_slistex, 0);
            slist_swap(pt_slist, pt_slistex);
            _printslist_c(pt_slist, "%lu, ", unsigned long);
            _printslist_c(pt_slistex, "%lu, ", unsigned long);
            slist_push_front(pt_slistex, -2);
            slist_push_front(pt_slistex, -9);
            slist_push_front(pt_slistex, -2);
            slist_push_front(pt_slistex, -111);
            slist_push_front(pt_slistex, -44);
            slist_swap(pt_slist, pt_slistex);
            _printslist_c(pt_slist, "%lu, ", unsigned long);
            _printslist_c(pt_slistex, "%lu, ", unsigned long);
            slist_clear(pt_slistex);
            slist_swap(pt_slist, pt_slistex);
            _printslist_c(pt_slist, "%lu, ", unsigned long);
            _printslist_c(pt_slistex, "%lu, ", unsigned long);
            slist_clear(pt_slistex);
            slist_swap(pt_slist, pt_slistex);
            _printslist_c(pt_slist, "%lu, ", unsigned long);
            _printslist_c(pt_slistex, "%lu, ", unsigned long);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_front             */
        {
            slist_t* pt_slist = create_slist(int);
            size_t t_index = 0;
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            for(t_index = 0; t_index < 10; ++t_index)
            {
                slist_push_front(pt_slist, t_index + 100);
            }
            while(!slist_empty(pt_slist))
            {
                if(slist_front(pt_slist) != NULL)
                {
                    printf("%d, ", *(int*)slist_front(pt_slist));
                    slist_pop_front(pt_slist);
                }
            }
            printf("\n");
            slist_destroy(pt_slist);
        }
        /*slist_push_front        */
        /*slist_pop_front         */
        /*slist_insert            */
        {
            slist_t* pt_slist = create_slist(char);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_insert(pt_slist, slist_end(pt_slist), 'Y');
            _printslist_c(pt_slist, "%c, ", char);
            slist_insert(pt_slist, slist_begin(pt_slist), 'O');
            _printslist_c(pt_slist, "%c, ", char);
            slist_insert(pt_slist, slist_end(pt_slist), 'U');
            _printslist_c(pt_slist, "%c, ", char);
            slist_insert(pt_slist, iterator_advance(slist_begin(pt_slist), 2), 'X');
            _printslist_c(pt_slist, "%c, ", char);
            slist_destroy(pt_slist);
        }
        /*slist_insert_n          */
        {
            slist_t* pt_slist = create_slist(char);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_insert_n(pt_slist, slist_end(pt_slist), 3, 'Y');
            _printslist_c(pt_slist, "%c, ", char);
            slist_insert_n(pt_slist, slist_begin(pt_slist), 7, 'O');
            _printslist_c(pt_slist, "%c, ", char);
            slist_insert_n(pt_slist, slist_end(pt_slist), 2, 'U');
            _printslist_c(pt_slist, "%c, ", char);
            slist_insert_n(pt_slist, iterator_advance(slist_begin(pt_slist), 2), 2, 'X');
            _printslist_c(pt_slist, "%c, ", char);
            slist_insert_n(pt_slist, iterator_advance(slist_begin(pt_slist), 2), 0, 'w');
            _printslist_c(pt_slist, "%c, ", char);
            slist_destroy(pt_slist);
        }
        /*slist_insert_range      */
        {
            slist_t* pt_slist = create_slist(int);
            slist_t* pt_slistex = create_slist(signed int);
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            slist_push_front(pt_slistex, 34);
            slist_push_front(pt_slistex, -88);
            slist_push_front(pt_slistex, 2009);
            slist_push_front(pt_slistex, 12345);
            slist_push_front(pt_slistex, -9888);
            slist_push_front(pt_slistex, 2);
            slist_push_front(pt_slistex, -9);
            slist_push_front(pt_slistex, -222);
            slist_push_front(pt_slistex, 2);
            slist_push_front(pt_slistex, 70);
            slist_push_front(pt_slistex, 21);
            slist_push_front(pt_slistex, 2222);
            slist_push_front(pt_slistex, 37);
            _printslist_c(pt_slistex, "%d, ", int);
            slist_insert_range(pt_slist, slist_begin(pt_slist),
                slist_begin(pt_slistex), slist_begin(pt_slistex));
            _printslist_c(pt_slist, "%d, ", int);
            slist_insert_range(pt_slist, slist_end(pt_slist),
                slist_begin(pt_slistex), iterator_advance(slist_begin(pt_slistex), 2));
            _printslist_c(pt_slist, "%d, ", int);
            slist_insert_range(pt_slist, slist_begin(pt_slist),
                iterator_advance(slist_begin(pt_slistex), 2),
                iterator_advance(slist_begin(pt_slistex), 4));
            _printslist_c(pt_slist, "%d, ", int);
            slist_insert_range(pt_slist, iterator_advance(slist_begin(pt_slist), 3),
                iterator_advance(slist_begin(pt_slistex), 3),
                iterator_advance(slist_begin(pt_slistex), 6));
            _printslist_c(pt_slist, "%d, ", int);
            slist_insert_range(pt_slist, iterator_advance(slist_begin(pt_slist), 5),
                iterator_advance(slist_begin(pt_slistex), 10), slist_end(pt_slistex));
            _printslist_c(pt_slist, "%d, ", int);
            slist_insert_range(pt_slist, slist_end(pt_slist),
                slist_begin(pt_slistex), slist_end(pt_slistex));
            _printslist_c(pt_slist, "%d, ", int);
            slist_insert_range(pt_slist, slist_end(pt_slist),
                slist_end(pt_slistex), slist_end(pt_slistex));
            _printslist_c(pt_slist, "%d, ", int);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_insert_after      */
        {
            /*
            slist_t* pt_slist = create_slist(int);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_insert_after(pt_slist, slist_begin(pt_slist), 44);
            _printslist_c(pt_slist, "%d, ", int);
            slist_destroy(pt_slist);
            */
        }
        /*slist_insert_after_n    */
        /*slist_insert_after_range*/
        /*slist_erase             */
        /*slist_erase_range       */
        /*slist_erase_after       */
        /*slist_erase_after_range */
        /*slist_splice            */
        /*slist_splice_pos        */
        /*slist_splice_range      */
        /*slist_splice_after_pos  */
        /*slist_splice_after_range*/
        /*slist_remove            */
        {
            slist_t* pt_slist = create_slist(int);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_remove(pt_slist, 100);
            _printslist_c(pt_slist, "%d, ", int);
            slist_push_front(pt_slist, 29);
            slist_push_front(pt_slist, 34);
            slist_push_front(pt_slist, 100);
            slist_push_front(pt_slist, 200);
            slist_push_front(pt_slist, 2);
            slist_push_front(pt_slist, 7);
            slist_push_front(pt_slist, 100);
            slist_push_front(pt_slist, 33);
            _printslist_c(pt_slist, "%d, ", int);
            slist_remove(pt_slist, 100);
            _printslist_c(pt_slist, "%d, ", int);
            slist_remove(pt_slist, 100);
            _printslist_c(pt_slist, "%d, ", int);
            slist_destroy(pt_slist);
        }
        /*slist_remove_if         */
        {
            slist_t* pt_slist = create_slist(int);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_remove_if(pt_slist, _slist_remove_pred);
            _printslist_c(pt_slist, "%d, ", int);
            slist_push_front(pt_slist, 29);
            slist_push_front(pt_slist, 35);
            slist_push_front(pt_slist, 100);
            slist_push_front(pt_slist, 200);
            slist_push_front(pt_slist, 2);
            slist_push_front(pt_slist, 7);
            slist_push_front(pt_slist, 100);
            slist_push_front(pt_slist, 33);
            _printslist_c(pt_slist, "%d, ", int);
            slist_remove_if(pt_slist, _slist_remove_pred);
            _printslist_c(pt_slist, "%d, ", int);
            slist_remove_if(pt_slist, _slist_remove_pred);
            _printslist_c(pt_slist, "%d, ", int);
            slist_destroy(pt_slist);
        }
        /*slist_unique            */
        {
            slist_t* pt_slist = create_slist(int);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_unique(pt_slist);
            _printslist_c(pt_slist, "%d, ", int);
            slist_push_front(pt_slist, 29);
            slist_push_front(pt_slist, 34);
            slist_push_front(pt_slist, 100);
            slist_push_front(pt_slist, 100);
            slist_push_front(pt_slist, 200);
            slist_push_front(pt_slist, 2);
            slist_push_front(pt_slist, 7);
            slist_push_front(pt_slist, 7);
            slist_push_front(pt_slist, 100);
            slist_push_front(pt_slist, 33);
            _printslist_c(pt_slist, "%d, ", int);
            slist_unique(pt_slist);
            _printslist_c(pt_slist, "%d, ", int);
            slist_unique(pt_slist);
            _printslist_c(pt_slist, "%d, ", int);
            slist_destroy(pt_slist);
        }
        /*slist_unique_if         */
        /*slist_reverse           */
        /*slist_sort              */
        /*slist_sort_if           */
        /*slist_merge             */
        /*slist_merge_if          */
        /*slist_resize            */
        {
            slist_t* pt_slist = create_slist(int);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            _printslist_c(pt_slist, "%d, ", int);
            slist_resize(pt_slist, 3);
            _printslist_c(pt_slist, "%d, ", int);
            slist_resize(pt_slist, 10);
            _printslist_c(pt_slist, "%d, ", int);
            slist_resize(pt_slist, 4);
            _printslist_c(pt_slist, "%d, ", int);
            slist_resize(pt_slist, 0);
            _printslist_c(pt_slist, "%d, ", int);
            slist_destroy(pt_slist);
        }
        /*slist_resize_elem       */
        {
            slist_t* pt_slist = create_slist(int);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            _printslist_c(pt_slist, "%d, ", int);
            slist_resize_elem(pt_slist, 3, 100);
            _printslist_c(pt_slist, "%d, ", int);
            slist_resize_elem(pt_slist, 10, 200);
            _printslist_c(pt_slist, "%d, ", int);
            slist_resize_elem(pt_slist, 4, 300);
            _printslist_c(pt_slist, "%d, ", int);
            slist_resize_elem(pt_slist, 0, 400);
            _printslist_c(pt_slist, "%d, ", int);
            slist_destroy(pt_slist);
        }
        /*slist_clear             */
        {
            slist_t* pt_slist = create_slist(int);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_clear(pt_slist);
            _printslist_c(pt_slist, "%d, ", int);
            slist_push_front(pt_slist, 1);
            slist_push_front(pt_slist, 9);
            slist_push_front(pt_slist, 28);
            slist_push_front(pt_slist, -22);
            _printslist_c(pt_slist, "%d, ", int);
            slist_clear(pt_slist);
            _printslist_c(pt_slist, "%d, ", int);
            slist_destroy(pt_slist);
        }
    }
    /* user defined type */
    {
    }
    /* cstl built-in type */
    {
    }
    /* c-string type */
    {
    }
    /*_create_slist           */
    /*slist_init              */
    /*slist_init_n            */
    /*_slist_init_elem        */
    /*slist_init_copy         */
    /*slist_init_copy_range   */
    /*slist_destroy           */
    /*slist_size              */
    /*slist_empty             */
    /*slist_max_size          */
    /*slist_begin             */
    /*slist_end               */
    /*slist_previous          */
    /*slist_equal             */
    /*slist_not_equal         */
    /*slist_less              */
    /*slist_less_equal        */
    /*slist_great             */
    /*slist_great_equal       */
    /*slist_assign            */
    /*_slist_assign_elem      */
    /*slist_assign_range      */
    /*slist_swap              */
    /*slist_front             */
    /*_slist_push_front       */
    /*slist_pop_front         */
    /*_slist_insert           */
    /*_slist_insert_n         */
    /*slist_insert_range      */
    /*_slist_insert_after     */
    /*_slist_insert_after_n   */
    /*slist_insert_after_range*/
    /*slist_erase             */
    /*slist_erase_range       */
    /*slist_erase_after       */
    /*slist_erase_after_range */
    /*slist_splice            */
    /*slist_splice_pos        */
    /*slist_splice_range      */
    /*slist_splice_after_pos  */
    /*slist_splice_after_range*/
    /*_slist_remove           */
    /*slist_remove_if         */
    /*slist_unique            */
    /*slist_unique_if         */
    /*slist_reverse           */
    /*slist_sort              */
    /*slist_sort_if           */
    /*slist_merge             */
    /*slist_merge_if          */
    /*slist_resize            */
    /*_slist_resize_elem      */
    /*slist_clear             */
}

/** local function implementation section **/
static void _slist_remove_pred(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    if(*(int*)cpv_input % 5 == 0)
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}

/** eof **/

