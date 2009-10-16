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
#include <time.h>
#include "cslist.h"
#include "cfunctional.h"
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

typedef struct _tagcoordinates
{
    int x;
    int y;
    int z;
}coordinates_t;

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/
static void _printcoordinates(const slist_t* cpt_slist);
static void _coordinates_init(const void* cpv_input, void* pv_output);
static void _coordinates_copy(const void* cpv_first, const void* cpv_second, void* pv_output);
static void _coordinates_destroy(const void* cpv_input, void* pv_output);
static void _coordinates_less(const void* cpv_first, const void* cpv_second, void* pv_output);

static void _slist_remove_pred(const void* cpv_input, void* pv_output);
static void _slist_unique_pred(
    const void* cpv_first, const void* cpv_second, void* pv_output);

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
            slist_t* pt_slist = create_slist(int);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_push_front(pt_slist, 0);
            slist_push_front(pt_slist, 1);
            slist_push_front(pt_slist, 2);
            slist_insert_after(pt_slist, slist_begin(pt_slist), 44);
            _printslist_c(pt_slist, "%d, ", int);
            slist_insert_after(pt_slist, iterator_advance(slist_begin(pt_slist), 2), -9);
            _printslist_c(pt_slist, "%d, ", int);
            slist_insert_after(pt_slist, slist_previous(pt_slist, slist_end(pt_slist)), 100);
            _printslist_c(pt_slist, "%d, ", int);
            slist_destroy(pt_slist);
        }
        /*slist_insert_after_n    */
        {
            slist_t* pt_slist = create_slist(int);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_push_front(pt_slist, 0);
            slist_push_front(pt_slist, 1);
            slist_push_front(pt_slist, 2);
            slist_insert_after_n(pt_slist, slist_begin(pt_slist), 3, 44);
            _printslist_c(pt_slist, "%d, ", int);
            slist_insert_after_n(pt_slist, iterator_advance(slist_begin(pt_slist), 2), 7, -9);
            _printslist_c(pt_slist, "%d, ", int);
            slist_insert_after_n(pt_slist,
                slist_previous(pt_slist, slist_end(pt_slist)), 3, 100);
            _printslist_c(pt_slist, "%d, ", int);
            slist_destroy(pt_slist);
        }
        /*slist_insert_after_range*/
        {
            slist_t* pt_slist = create_slist(int);
            slist_t* pt_slistex = create_slist(signed int);
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            slist_push_front(pt_slist, 0);
            slist_push_front(pt_slist, 1);
            slist_push_front(pt_slist, 2);
            slist_push_front(pt_slist, 3);
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
            slist_insert_after_range(pt_slist, slist_begin(pt_slist),
                slist_begin(pt_slistex), slist_begin(pt_slistex));
            _printslist_c(pt_slist, "%d, ", int);
            slist_insert_after_range(pt_slist, slist_previous(pt_slist, slist_end(pt_slist)),
                slist_begin(pt_slistex), iterator_advance(slist_begin(pt_slistex), 2));
            _printslist_c(pt_slist, "%d, ", int);
            slist_insert_after_range(pt_slist, slist_begin(pt_slist),
                iterator_advance(slist_begin(pt_slistex), 2),
                iterator_advance(slist_begin(pt_slistex), 4));
            _printslist_c(pt_slist, "%d, ", int);
            slist_insert_after_range(pt_slist, iterator_advance(slist_begin(pt_slist), 3),
                iterator_advance(slist_begin(pt_slistex), 3),
                iterator_advance(slist_begin(pt_slistex), 6));
            _printslist_c(pt_slist, "%d, ", int);
            slist_insert_after_range(pt_slist, iterator_advance(slist_begin(pt_slist), 5),
                iterator_advance(slist_begin(pt_slistex), 10), slist_end(pt_slistex));
            _printslist_c(pt_slist, "%d, ", int);
            slist_insert_after_range(pt_slist, slist_previous(pt_slist, slist_end(pt_slist)),
                slist_begin(pt_slistex), slist_end(pt_slistex));
            _printslist_c(pt_slist, "%d, ", int);
            slist_insert_after_range(pt_slist, slist_previous(pt_slist, slist_end(pt_slist)),
                slist_end(pt_slistex), slist_end(pt_slistex));
            _printslist_c(pt_slist, "%d, ", int);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_erase             */
        {
            slist_t* pt_slist = create_slist(int);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_push_front(pt_slist, 29);
            slist_push_front(pt_slist, 34);
            slist_push_front(pt_slist, 100);
            slist_push_front(pt_slist, 200);
            slist_push_front(pt_slist, 2);
            slist_push_front(pt_slist, 7);
            slist_push_front(pt_slist, 100);
            slist_push_front(pt_slist, 33);
            _printslist_c(pt_slist, "%d, ", int);
            slist_erase(pt_slist, slist_begin(pt_slist));
            _printslist_c(pt_slist, "%d, ", int);
            slist_erase(pt_slist, iterator_advance(slist_begin(pt_slist), 2));
            _printslist_c(pt_slist, "%d, ", int);
            slist_erase(pt_slist, slist_previous(pt_slist, slist_end(pt_slist)));
            _printslist_c(pt_slist, "%d, ", int);
            slist_destroy(pt_slist);
        }
        /*slist_erase_range       */
        {
            slist_t* pt_slist = create_slist(int);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_erase_range(pt_slist, slist_begin(pt_slist), slist_end(pt_slist));
            _printslist_c(pt_slist, "%d, ", int);
            slist_push_front(pt_slist, 29);
            slist_push_front(pt_slist, 34);
            slist_push_front(pt_slist, 100);
            slist_push_front(pt_slist, 200);
            slist_push_front(pt_slist, 2);
            slist_push_front(pt_slist, 7);
            slist_push_front(pt_slist, 100);
            slist_push_front(pt_slist, 33);
            slist_push_front(pt_slist, 88);
            slist_push_front(pt_slist, -23);
            slist_push_front(pt_slist, 2009);
            slist_push_front(pt_slist, 677);
            _printslist_c(pt_slist, "%d, ", int);
            slist_erase_range(pt_slist, slist_begin(pt_slist), slist_begin(pt_slist));
            _printslist_c(pt_slist, "%d, ", int);
            slist_erase_range(pt_slist,
                slist_begin(pt_slist), iterator_advance(slist_begin(pt_slist), 2));
            _printslist_c(pt_slist, "%d, ", int);
            slist_erase_range(pt_slist,
                iterator_advance(slist_begin(pt_slist), 2),
                iterator_advance(slist_begin(pt_slist), 5));
            _printslist_c(pt_slist, "%d, ", int);
            slist_erase_range(pt_slist,
                iterator_advance(slist_begin(pt_slist), 4), slist_end(pt_slist));
            _printslist_c(pt_slist, "%d, ", int);
            slist_erase_range(pt_slist, slist_begin(pt_slist), slist_end(pt_slist));
            _printslist_c(pt_slist, "%d, ", int);
            slist_destroy(pt_slist);
        }
        /*slist_erase_after       */
        {
            slist_t* pt_slist = create_slist(int);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_push_front(pt_slist, -29);
            slist_push_front(pt_slist, -34);
            slist_push_front(pt_slist, -100);
            slist_push_front(pt_slist, -200);
            slist_push_front(pt_slist, -2);
            slist_push_front(pt_slist, -7);
            slist_push_front(pt_slist, -100);
            slist_push_front(pt_slist, -33);
            _printslist_c(pt_slist, "%d, ", int);
            slist_erase_after(pt_slist, slist_begin(pt_slist));
            _printslist_c(pt_slist, "%d, ", int);
            slist_erase_after(pt_slist, iterator_advance(slist_begin(pt_slist), 2));
            _printslist_c(pt_slist, "%d, ", int);
            slist_erase_after(pt_slist, 
                slist_previous(pt_slist, slist_previous(pt_slist, slist_end(pt_slist))));
            _printslist_c(pt_slist, "%d, ", int);
            slist_destroy(pt_slist);
        }
        /*slist_erase_after_range */
        {
            slist_t* pt_slist = create_slist(int);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_erase_after_range(pt_slist, slist_begin(pt_slist), slist_end(pt_slist));
            _printslist_c(pt_slist, "%d, ", int);
            slist_push_front(pt_slist, 1029);
            slist_push_front(pt_slist, 1034);
            slist_push_front(pt_slist, 100);
            slist_push_front(pt_slist, 10200);
            slist_push_front(pt_slist, 102);
            slist_push_front(pt_slist, 107);
            slist_push_front(pt_slist, 100);
            slist_push_front(pt_slist, 1033);
            slist_push_front(pt_slist, 1088);
            slist_push_front(pt_slist, -1023);
            slist_push_front(pt_slist, 102009);
            slist_push_front(pt_slist, 10677);
            _printslist_c(pt_slist, "%d, ", int);
            slist_erase_after_range(pt_slist, slist_begin(pt_slist), slist_begin(pt_slist));
            _printslist_c(pt_slist, "%d, ", int);
            slist_erase_after_range(pt_slist,
                slist_begin(pt_slist), iterator_advance(slist_begin(pt_slist), 2));
            _printslist_c(pt_slist, "%d, ", int);
            slist_erase_after_range(pt_slist,
                iterator_advance(slist_begin(pt_slist), 2),
                iterator_advance(slist_begin(pt_slist), 5));
            _printslist_c(pt_slist, "%d, ", int);
            slist_erase_after_range(pt_slist,
                iterator_advance(slist_begin(pt_slist), 4), slist_end(pt_slist));
            _printslist_c(pt_slist, "%d, ", int);
            slist_erase_after_range(pt_slist, slist_begin(pt_slist), slist_end(pt_slist));
            _printslist_c(pt_slist, "%d, ", int);
            slist_destroy(pt_slist);
        }
        /*slist_splice            */
        {
            slist_t* pt_slist = create_slist(int);
            slist_t* pt_slistex = create_slist(int);
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            slist_splice(pt_slist, slist_begin(pt_slist), pt_slistex);
            _printslist_c(pt_slist, "%d, ", int);
            slist_push_front(pt_slist, 123);
            slist_push_front(pt_slist, 456);
            slist_push_front(pt_slist, 789);
            slist_push_front(pt_slist, 111);
            slist_push_front(pt_slist, 222);
            slist_push_front(pt_slist, 333);
            slist_splice(pt_slist, iterator_advance(slist_begin(pt_slist), 2), pt_slistex);
            _printslist_c(pt_slist, "%d, ", int);
            slist_push_front(pt_slistex, -111);
            slist_push_front(pt_slistex, -222);
            slist_push_front(pt_slistex, -333);
            slist_push_front(pt_slistex, -444);
            slist_push_front(pt_slistex, -555);
            slist_splice(pt_slist, slist_begin(pt_slist), pt_slistex);
            _printslist_c(pt_slist, "%d, ", int);
            slist_push_front(pt_slistex, -1111);
            slist_push_front(pt_slistex, -2222);
            slist_push_front(pt_slistex, -3333);
            slist_push_front(pt_slistex, -4444);
            slist_push_front(pt_slistex, -5555);
            slist_splice(pt_slist, iterator_advance(slist_begin(pt_slist), 6), pt_slistex);
            _printslist_c(pt_slist, "%d, ", int);
            slist_push_front(pt_slistex, -11111);
            slist_push_front(pt_slistex, -22222);
            slist_push_front(pt_slistex, -33333);
            slist_push_front(pt_slistex, -44444);
            slist_push_front(pt_slistex, -55555);
            slist_splice(pt_slist, slist_end(pt_slist), pt_slistex);
            _printslist_c(pt_slist, "%d, ", int);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_splice_pos        */
        {
            slist_t* pt_slist = create_slist(int);
            slist_t* pt_slistex = create_slist(int);
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            slist_push_front(pt_slistex, -111);
            slist_push_front(pt_slistex, -222);
            slist_push_front(pt_slistex, -333);
            slist_push_front(pt_slistex, -444);
            slist_push_front(pt_slistex, -555);
            slist_push_front(pt_slistex, -666);
            slist_push_front(pt_slistex, -777);
            slist_push_front(pt_slistex, -888);
            slist_push_front(pt_slistex, -999);
            _printslist_c(pt_slistex, "%d, ", int);
            slist_splice_pos(pt_slist, slist_begin(pt_slist),
                pt_slistex, slist_begin(pt_slistex));
            _printslist_c(pt_slist, "%d, ", int);
            slist_splice_pos(pt_slist, slist_end(pt_slist),
                pt_slistex, iterator_advance(slist_begin(pt_slistex), 3));
            _printslist_c(pt_slist, "%d, ", int);
            slist_splice_pos(pt_slist, iterator_advance(slist_begin(pt_slist), 1),
                pt_slistex, slist_previous(pt_slistex, slist_end(pt_slistex)));
            _printslist_c(pt_slist, "%d, ", int);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_splice_range      */
        {
            slist_t* pt_slist = create_slist(int);
            slist_t* pt_slistex = create_slist(int);
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            slist_push_front(pt_slistex, -111);
            slist_push_front(pt_slistex, -222);
            slist_push_front(pt_slistex, -333);
            slist_push_front(pt_slistex, -444);
            slist_push_front(pt_slistex, -555);
            slist_push_front(pt_slistex, -666);
            slist_push_front(pt_slistex, -777);
            slist_push_front(pt_slistex, -888);
            slist_push_front(pt_slistex, -999);
            slist_push_front(pt_slistex, 111);
            slist_push_front(pt_slistex, 222);
            slist_push_front(pt_slistex, 333);
            slist_push_front(pt_slistex, 444);
            slist_push_front(pt_slistex, 555);
            slist_push_front(pt_slistex, 666);
            slist_push_front(pt_slistex, 777);
            slist_push_front(pt_slistex, 888);
            slist_push_front(pt_slistex, 999);
            _printslist_c(pt_slistex, "%d, ", int);
            slist_splice_range(pt_slist, slist_begin(pt_slist),
                pt_slistex, slist_begin(pt_slistex), slist_begin(pt_slistex));
            _printslist_c(pt_slist, "%d, ", int);
            slist_splice_range(pt_slist, slist_end(pt_slist), pt_slistex,
                slist_begin(pt_slistex), iterator_advance(slist_begin(pt_slistex), 3));
            _printslist_c(pt_slist, "%d, ", int);
            slist_splice_range(pt_slist, iterator_advance(slist_begin(pt_slist), 1),
                pt_slistex, iterator_advance(slist_begin(pt_slistex), 2),
                iterator_advance(slist_begin(pt_slistex), 5));
            _printslist_c(pt_slist, "%d, ", int);
            slist_splice_range(pt_slist, slist_begin(pt_slist), pt_slistex,
                iterator_advance(slist_begin(pt_slistex), 5), slist_end(pt_slistex));
            _printslist_c(pt_slist, "%d, ", int);
            slist_splice_range(pt_slist, slist_end(pt_slist),
                pt_slistex, slist_begin(pt_slistex), slist_end(pt_slistex));
            _printslist_c(pt_slist, "%d, ", int);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_splice_after_pos  */
        {
            slist_t* pt_slist = create_slist(int);
            slist_t* pt_slistex = create_slist(int);
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            slist_push_front(pt_slist, 111);
            slist_push_front(pt_slist, 222);
            slist_push_front(pt_slist, 333);
            slist_push_front(pt_slist, 444);
            slist_push_front(pt_slist, 555);
            slist_push_front(pt_slist, 666);
            slist_push_front(pt_slist, 777);
            slist_push_front(pt_slist, 888);
            slist_push_front(pt_slist, 999);
            slist_push_front(pt_slistex, -111);
            slist_push_front(pt_slistex, -222);
            slist_push_front(pt_slistex, -333);
            slist_push_front(pt_slistex, -444);
            slist_push_front(pt_slistex, -555);
            slist_push_front(pt_slistex, -666);
            slist_push_front(pt_slistex, -777);
            slist_push_front(pt_slistex, -888);
            slist_push_front(pt_slistex, -999);
            _printslist_c(pt_slist, "%d, ", int);
            _printslist_c(pt_slistex, "%d, ", int);
            slist_splice_after_pos(pt_slist, slist_begin(pt_slist),
                pt_slistex, slist_begin(pt_slistex));
            _printslist_c(pt_slist, "%d, ", int);
            _printslist_c(pt_slistex, "%d, ", int);
            slist_splice_after_pos(pt_slist, slist_previous(pt_slist, slist_end(pt_slist)),
                pt_slistex,
                slist_previous(pt_slistex, slist_previous(pt_slistex, slist_end(pt_slistex))));
            _printslist_c(pt_slist, "%d, ", int);
            _printslist_c(pt_slistex, "%d, ", int);
            slist_splice_after_pos(pt_slist, iterator_advance(slist_begin(pt_slist), 1),
                pt_slistex, iterator_advance(slist_begin(pt_slistex), 1));
            _printslist_c(pt_slist, "%d, ", int);
            _printslist_c(pt_slistex, "%d, ", int);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_splice_after_range*/
        {
            slist_t* pt_slist = create_slist(int);
            slist_t* pt_slistex = create_slist(int);
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            slist_push_front(pt_slist, 111);
            slist_push_front(pt_slist, 222);
            slist_push_front(pt_slist, 333);
            slist_push_front(pt_slist, 444);
            slist_push_front(pt_slist, 555);
            slist_push_front(pt_slist, 666);
            slist_push_front(pt_slist, 777);
            slist_push_front(pt_slist, 888);
            slist_push_front(pt_slist, 999);
            slist_push_front(pt_slistex, -111);
            slist_push_front(pt_slistex, -222);
            slist_push_front(pt_slistex, -333);
            slist_push_front(pt_slistex, -444);
            slist_push_front(pt_slistex, -555);
            slist_push_front(pt_slistex, -666);
            slist_push_front(pt_slistex, -777);
            slist_push_front(pt_slistex, -888);
            slist_push_front(pt_slistex, -999);
            slist_push_front(pt_slistex, 1111);
            slist_push_front(pt_slistex, 2222);
            slist_push_front(pt_slistex, 3333);
            slist_push_front(pt_slistex, 4444);
            slist_push_front(pt_slistex, 5555);
            slist_push_front(pt_slistex, 6666);
            slist_push_front(pt_slistex, 7777);
            slist_push_front(pt_slistex, 8888);
            slist_push_front(pt_slistex, 9999);
            _printslist_c(pt_slist, "%d, ", int);
            _printslist_c(pt_slistex, "%d, ", int);
            slist_splice_after_range(pt_slist, slist_begin(pt_slist),
                pt_slistex, slist_begin(pt_slistex), slist_begin(pt_slistex));
            _printslist_c(pt_slist, "%d, ", int);
            _printslist_c(pt_slistex, "%d, ", int);
            slist_splice_after_range(pt_slist, slist_previous(pt_slist, slist_end(pt_slist)),
                pt_slistex,
                slist_begin(pt_slistex), iterator_advance(slist_begin(pt_slistex), 3));
            _printslist_c(pt_slist, "%d, ", int);
            _printslist_c(pt_slistex, "%d, ", int);
            slist_splice_after_range(pt_slist, iterator_advance(slist_begin(pt_slist), 1),
                pt_slistex, iterator_advance(slist_begin(pt_slistex), 2),
                iterator_advance(slist_begin(pt_slistex), 5));
            _printslist_c(pt_slist, "%d, ", int);
            _printslist_c(pt_slistex, "%d, ", int);
            slist_splice_after_range(pt_slist, slist_begin(pt_slist), pt_slistex,
                iterator_advance(slist_begin(pt_slistex), 5),
                slist_previous(pt_slistex, slist_end(pt_slistex)));
            _printslist_c(pt_slist, "%d, ", int);
            _printslist_c(pt_slistex, "%d, ", int);
            slist_splice_after_range(pt_slist, slist_previous(pt_slist, slist_end(pt_slist)),
                pt_slistex, slist_begin(pt_slistex),
                slist_previous(pt_slistex, slist_end(pt_slistex)));
            _printslist_c(pt_slist, "%d, ", int);
            _printslist_c(pt_slistex, "%d, ", int);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
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
        {
            slist_t* pt_slist = create_slist(int);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_unique_if(pt_slist, _slist_unique_pred);
            _printslist_c(pt_slist, "%d, ", int);
            slist_push_front(pt_slist, 29);
            slist_push_front(pt_slist, 34);
            slist_push_front(pt_slist, 100);
            slist_push_front(pt_slist, 15);
            slist_push_front(pt_slist, 200);
            slist_push_front(pt_slist, 2);
            slist_push_front(pt_slist, 7);
            slist_push_front(pt_slist, 7);
            slist_push_front(pt_slist, 100);
            slist_push_front(pt_slist, 35);
            slist_push_front(pt_slist, 33);
            _printslist_c(pt_slist, "%d, ", int);
            slist_unique_if(pt_slist, _slist_unique_pred);
            _printslist_c(pt_slist, "%d, ", int);
            slist_unique_if(pt_slist, _slist_unique_pred);
            _printslist_c(pt_slist, "%d, ", int);
            slist_destroy(pt_slist);
        }
        /*slist_reverse           */
        {
            slist_t* pt_slist = create_slist(int);
            int n_count = 0;
            int i = 0;
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            _printslist_c(pt_slist, "%d, ", int);
            slist_reverse(pt_slist);
            _printslist_c(pt_slist, "%d, ", int);
            srand((unsigned)time(NULL));
            n_count = rand() % 100;
            for(i = 0; i < n_count; ++i)
            {
                slist_push_front(pt_slist, rand()-rand());
            }
            _printslist_c(pt_slist, "%d, ", int);
            slist_reverse(pt_slist);
            _printslist_c(pt_slist, "%d, ", int);
            slist_destroy(pt_slist);
        }
        /*slist_sort              */
        {
            slist_t* pt_slist = create_slist(int);
            int n_count = 0;
            int i = 0;
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            _printslist_c(pt_slist, "%d, ", int);
            slist_sort(pt_slist);
            _printslist_c(pt_slist, "%d, ", int);
            srand((unsigned)time(NULL) + 11);
            n_count = rand() % 1000;
            for(i = 0; i < n_count; ++i)
            {
                slist_push_front(pt_slist, rand()-rand());
            }
            _printslist_c(pt_slist, "%d, ", int);
            slist_sort(pt_slist);
            _printslist_c(pt_slist, "%d, ", int);
            slist_destroy(pt_slist);
        }
        /*slist_sort_if           */
        {
            slist_t* pt_slist = create_slist(int);
            int n_count = 0;
            int i = 0;
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            _printslist_c(pt_slist, "%d, ", int);
            slist_sort_if(pt_slist, fun_great_int);
            _printslist_c(pt_slist, "%d, ", int);
            srand((unsigned)time(NULL) + 17);
            n_count = rand() % 1000;
            for(i = 0; i < n_count; ++i)
            {
                slist_push_front(pt_slist, rand()-rand());
            }
            _printslist_c(pt_slist, "%d, ", int);
            slist_sort_if(pt_slist, fun_great_int);
            _printslist_c(pt_slist, "%d, ", int);
            slist_destroy(pt_slist);
        }
        /*slist_merge             */
        {
            slist_t* pt_slist = create_slist(int);
            slist_t* pt_slistex = create_slist(int);
            int n_count = 0;
            int i = 0;
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            slist_merge(pt_slist, pt_slistex);
            _printslist_c(pt_slist, "%d, ", int);
            _printslist_c(pt_slistex, "%d, ", int);
            srand((unsigned)time(NULL) + 11);
            n_count = rand() % 100;
            for(i = 0; i < n_count; ++i)
            {
                slist_push_front(pt_slist, rand()-rand());
            }
            n_count = rand() % 100;
            for(i = 0; i < n_count; ++i)
            {
                slist_push_front(pt_slistex, rand()-rand());
            }
            slist_sort(pt_slist);
            slist_sort(pt_slistex);
            _printslist_c(pt_slist, "%d, ", int);
            _printslist_c(pt_slistex, "%d, ", int);
            slist_merge(pt_slist, pt_slistex);
            _printslist_c(pt_slist, "%d, ", int);
            _printslist_c(pt_slistex, "%d, ", int);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_merge_if          */
        {
            slist_t* pt_slist = create_slist(int);
            slist_t* pt_slistex = create_slist(int);
            int n_count = 0;
            int i = 0;
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            slist_merge_if(pt_slist, pt_slistex, fun_great_int);
            _printslist_c(pt_slist, "%d, ", int);
            _printslist_c(pt_slistex, "%d, ", int);
            srand((unsigned)time(NULL) + 11);
            n_count = rand() % 100;
            for(i = 0; i < n_count; ++i)
            {
                slist_push_front(pt_slist, rand()-rand());
            }
            n_count = rand() % 100;
            for(i = 0; i < n_count; ++i)
            {
                slist_push_front(pt_slistex, rand()-rand());
            }
            slist_sort_if(pt_slist, fun_great_int);
            slist_sort_if(pt_slistex, fun_great_int);
            _printslist_c(pt_slist, "%d, ", int);
            _printslist_c(pt_slistex, "%d, ", int);
            slist_merge_if(pt_slist, pt_slistex, fun_great_int);
            _printslist_c(pt_slist, "%d, ", int);
            _printslist_c(pt_slistex, "%d, ", int);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
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
        type_register(coordinates_t,
            _coordinates_init, _coordinates_copy, _coordinates_less, _coordinates_destroy);
        type_duplicate(coordinates_t, struct _tagcoordinates);
        _type_debug();
        /*create_slist            */
        {
            slist_t* pt_slist = create_slist(coordinates_t);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            _printcoordinates(pt_slist);
            slist_destroy(pt_slist);
        }
        /*slist_init              */
        /*slist_init_n            */
        {
            slist_t* pt_slist = create_slist(coordinates_t);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init_n(pt_slist, 5);
            _printcoordinates(pt_slist);
            slist_destroy(pt_slist);
        }
        /*slist_init_elem         */
        {
            slist_t* pt_slist = create_slist(struct _tagcoordinates);
            coordinates_t t_coor;
            if(pt_slist == NULL)
            {
                return;
            }
            t_coor.x = 24;
            t_coor.y = 1222;
            t_coor.z = -9;
            slist_init_elem(pt_slist, 5, &t_coor);
            _printcoordinates(pt_slist);
            slist_destroy(pt_slist);
        }
        /*slist_init_copy         */
        {
            slist_t* pt_slist = create_slist(coordinates_t);
            slist_t* pt_slistex = create_slist(struct _tagcoordinates);
            coordinates_t t_coor;
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            t_coor.x = -203;
            t_coor.y = 71;
            t_coor.z = -991;
            slist_init_elem(pt_slistex, 9, &t_coor);
            slist_init_copy(pt_slist, pt_slistex);
            _printcoordinates(pt_slist);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_init_copy_range   */
        {
            slist_t* pt_slist = create_slist(coordinates_t);
            slist_t* pt_slistex = create_slist(coordinates_t);
            coordinates_t t_coor;
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slistex);
            t_coor.x = 34;
            t_coor.y = 28;
            t_coor.z = 1024;
            slist_push_front(pt_slistex, &t_coor);
            t_coor.x = -3;
            t_coor.y = -19;
            t_coor.z = 90;
            slist_push_front(pt_slistex, &t_coor);
            t_coor.x = 0;
            t_coor.y = -731;
            t_coor.z = 2;
            slist_push_front(pt_slistex, &t_coor);
            t_coor.x = 90;
            t_coor.y = 54;
            t_coor.z = -1;
            slist_push_front(pt_slistex, &t_coor);
            _printcoordinates(pt_slistex);
            slist_init_copy_range(pt_slist,
                iterator_advance(slist_begin(pt_slistex), 1),
                slist_previous(pt_slistex, slist_end(pt_slistex)));
            _printcoordinates(pt_slist);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_destroy           */
        /*slist_size              */
        {
            slist_t* pt_slist = create_slist(coordinates_t);
            coordinates_t t_coor;
            int i = 0;
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            printf("size : %d, empty : %d, max_size : %d\n",
                slist_size(pt_slist), slist_empty(pt_slist), slist_max_size(pt_slist));
            for(i = 0; i < 100; ++i)
            {
                t_coor.x = t_coor.y = t_coor.z = i;
                slist_push_front(pt_slist, &t_coor);
                printf("size : %d, empty : %d, max_size : %d\n",
                    slist_size(pt_slist), slist_empty(pt_slist), slist_max_size(pt_slist));
            }
            _printcoordinates(pt_slist);
            slist_destroy(pt_slist);
        }
        /*slist_empty             */
        /*slist_max_size          */
        /*slist_begin             */
        /*slist_end               */
        /*slist_previous          */
        /*slist_equal             */
        {
            slist_t* pt_slist = create_slist(coordinates_t);
            slist_t* pt_slistex = create_slist(coordinates_t);
            coordinates_t t_coor;
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            _printcoordinates(pt_slist);
            _printcoordinates(pt_slistex);
            printf("equal : %d, not equal : %d ",
                slist_equal(pt_slist, pt_slistex), slist_not_equal(pt_slist, pt_slistex));
            printf("less : %d, less equal : %d ",
                slist_less(pt_slist, pt_slistex), slist_less_equal(pt_slist, pt_slistex));
            printf("great : %d, great equal : %d\n",
                slist_great(pt_slist, pt_slistex), slist_great_equal(pt_slist, pt_slistex));
            t_coor.x = 8;
            t_coor.y = 26;
            t_coor.z = -43;
            slist_push_front(pt_slist, &t_coor);
            _printcoordinates(pt_slist);
            _printcoordinates(pt_slistex);
            printf("equal : %d, not equal : %d ",
                slist_equal(pt_slist, pt_slistex), slist_not_equal(pt_slist, pt_slistex));
            printf("less : %d, less equal : %d ",
                slist_less(pt_slist, pt_slistex), slist_less_equal(pt_slist, pt_slistex));
            printf("great : %d, great equal : %d\n",
                slist_great(pt_slist, pt_slistex), slist_great_equal(pt_slist, pt_slistex));
            slist_push_front(pt_slistex, &t_coor);
            _printcoordinates(pt_slist);
            _printcoordinates(pt_slistex);
            printf("equal : %d, not equal : %d ",
                slist_equal(pt_slist, pt_slistex), slist_not_equal(pt_slist, pt_slistex));
            printf("less : %d, less equal : %d ",
                slist_less(pt_slist, pt_slistex), slist_less_equal(pt_slist, pt_slistex));
            printf("great : %d, great equal : %d\n",
                slist_great(pt_slist, pt_slistex), slist_great_equal(pt_slist, pt_slistex));

            t_coor.x = 35;
            t_coor.y = 27;
            t_coor.z = 0;
            slist_push_front(pt_slistex, &t_coor);
            _printcoordinates(pt_slist);
            _printcoordinates(pt_slistex);
            printf("equal : %d, not equal : %d ",
                slist_equal(pt_slist, pt_slistex), slist_not_equal(pt_slist, pt_slistex));
            printf("less : %d, less equal : %d ",
                slist_less(pt_slist, pt_slistex), slist_less_equal(pt_slist, pt_slistex));
            printf("great : %d, great equal : %d\n",
                slist_great(pt_slist, pt_slistex), slist_great_equal(pt_slist, pt_slistex));

            t_coor.x = -2;
            t_coor.y = 24;
            t_coor.z = 100;
            slist_push_front(pt_slist, &t_coor);
            _printcoordinates(pt_slist);
            _printcoordinates(pt_slistex);
            printf("equal : %d, not equal : %d ",
                slist_equal(pt_slist, pt_slistex), slist_not_equal(pt_slist, pt_slistex));
            printf("less : %d, less equal : %d ",
                slist_less(pt_slist, pt_slistex), slist_less_equal(pt_slist, pt_slistex));
            printf("great : %d, great equal : %d\n",
                slist_great(pt_slist, pt_slistex), slist_great_equal(pt_slist, pt_slistex));

            t_coor.x = -35;
            t_coor.y = -27;
            t_coor.z = -1;
            slist_push_front(pt_slist, &t_coor);
            _printcoordinates(pt_slist);
            _printcoordinates(pt_slistex);
            printf("equal : %d, not equal : %d ",
                slist_equal(pt_slist, pt_slistex), slist_not_equal(pt_slist, pt_slistex));
            printf("less : %d, less equal : %d ",
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
            slist_t* pt_slist = create_slist(coordinates_t);
            slist_t* pt_slistex = create_slist(coordinates_t);
            coordinates_t t_coor;
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            slist_assign(pt_slist, pt_slistex);
            _printcoordinates(pt_slist);
            t_coor.x = 8;
            t_coor.y = 26;
            t_coor.z = -43;
            slist_push_front(pt_slistex, &t_coor);
            t_coor.x = -2;
            t_coor.y = 24;
            t_coor.z = 100;
            slist_push_front(pt_slistex, &t_coor);
            t_coor.x = 35;
            t_coor.y = 27;
            t_coor.z = 0;
            slist_push_front(pt_slistex, &t_coor);
            slist_assign(pt_slist, pt_slistex);
            _printcoordinates(pt_slist);
            slist_clear(pt_slistex);
            t_coor.x = 72;
            t_coor.y = 69;
            t_coor.z = -8;
            slist_push_front(pt_slistex, &t_coor);
            t_coor.x = 33;
            t_coor.y = -19;
            t_coor.z = -21;
            slist_push_front(pt_slistex, &t_coor);
            t_coor.x = 44;
            t_coor.y = 128;
            t_coor.z = -80;
            slist_push_front(pt_slistex, &t_coor);
            t_coor.x = 32;
            t_coor.y = 69;
            t_coor.z = 69;
            slist_push_front(pt_slistex, &t_coor);
            t_coor.x = -5;
            t_coor.y = -78;
            t_coor.z = 127;
            slist_push_front(pt_slistex, &t_coor);
            t_coor.x = 33;
            t_coor.y = 33;
            t_coor.z = -5;
            slist_push_front(pt_slistex, &t_coor);
            slist_assign(pt_slist, pt_slistex);
            _printcoordinates(pt_slist);
            slist_clear(pt_slistex);
            t_coor.x = -432;
            t_coor.y = 909;
            t_coor.z = 1;
            slist_push_front(pt_slistex, &t_coor);
            t_coor.x = 21;
            t_coor.y = 1171;
            t_coor.z = -88;
            slist_push_front(pt_slistex, &t_coor);
            slist_assign(pt_slist, pt_slistex);
            _printcoordinates(pt_slist);
            slist_clear(pt_slistex);
            slist_assign(pt_slist, pt_slistex);
            _printcoordinates(pt_slist);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_assign_elem       */
        {
            slist_t* pt_slist = create_slist(coordinates_t);
            coordinates_t t_coor;
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_assign_elem(pt_slist, 0, &t_coor);
            _printcoordinates(pt_slist);
            t_coor.x = 98;
            t_coor.y = 89;
            t_coor.z = 23;
            slist_assign_elem(pt_slist, 3, &t_coor);
            _printcoordinates(pt_slist);
            t_coor.x = 0;
            t_coor.y = -48;
            t_coor.z = 22345;
            slist_assign_elem(pt_slist, 12, &t_coor);
            _printcoordinates(pt_slist);
            t_coor.x = 44;
            t_coor.y = 9;
            t_coor.z = 28;
            slist_assign_elem(pt_slist, 1, &t_coor);
            _printcoordinates(pt_slist);
            slist_assign_elem(pt_slist, 0, &t_coor);
            _printcoordinates(pt_slist);
            slist_destroy(pt_slist);
        }
        /*slist_assign_range      */
        {
            slist_t* pt_slist = create_slist(coordinates_t);
            slist_t* pt_slistex = create_slist(coordinates_t);
            coordinates_t t_coor;
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            slist_assign_range(pt_slist, slist_begin(pt_slistex), slist_end(pt_slistex));
            _printcoordinates(pt_slist);
            t_coor.x = 8;
            t_coor.y = 26;
            t_coor.z = -43;
            slist_push_front(pt_slistex, &t_coor);
            t_coor.x = -2;
            t_coor.y = 24;
            t_coor.z = 100;
            slist_push_front(pt_slistex, &t_coor);
            t_coor.x = 35;
            t_coor.y = 27;
            t_coor.z = 0;
            slist_push_front(pt_slistex, &t_coor);
            t_coor.x = 72;
            t_coor.y = 69;
            t_coor.z = -8;
            slist_push_front(pt_slistex, &t_coor);
            t_coor.x = 33;
            t_coor.y = -19;
            t_coor.z = -21;
            slist_push_front(pt_slistex, &t_coor);
            t_coor.x = 44;
            t_coor.y = 128;
            t_coor.z = -80;
            slist_push_front(pt_slistex, &t_coor);
            t_coor.x = 32;
            t_coor.y = 69;
            t_coor.z = 69;
            slist_push_front(pt_slistex, &t_coor);
            t_coor.x = -5;
            t_coor.y = -78;
            t_coor.z = 127;
            slist_push_front(pt_slistex, &t_coor);
            t_coor.x = 33;
            t_coor.y = 33;
            t_coor.z = -5;
            slist_push_front(pt_slistex, &t_coor);
            t_coor.x = -432;
            t_coor.y = 909;
            t_coor.z = 1;
            slist_push_front(pt_slistex, &t_coor);
            t_coor.x = 21;
            t_coor.y = 1171;
            t_coor.z = -88;
            slist_push_front(pt_slistex, &t_coor);
            _printcoordinates(pt_slistex);
            slist_assign_range(pt_slist, slist_begin(pt_slistex), slist_begin(pt_slistex));
            _printcoordinates(pt_slist);
            slist_assign_range(pt_slist,
                slist_begin(pt_slistex), iterator_advance(slist_begin(pt_slistex), 2));
            _printcoordinates(pt_slist);
            slist_assign_range(pt_slist,
                iterator_advance(slist_begin(pt_slistex), 3),
                iterator_advance(slist_begin(pt_slistex), 10));
            _printcoordinates(pt_slist);
            slist_assign_range(pt_slist,
                iterator_advance(slist_begin(pt_slistex), 8), slist_end(pt_slistex));
            _printcoordinates(pt_slist);
            slist_assign_range(pt_slist, slist_end(pt_slistex), slist_end(pt_slistex));
            _printcoordinates(pt_slist);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_swap              */
        {
            slist_t* pt_slist = create_slist(coordinates_t);
            slist_t* pt_slistex = create_slist(coordinates_t);
            coordinates_t t_coor;
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            _printcoordinates(pt_slist);
            _printcoordinates(pt_slistex);
            slist_swap(pt_slist, pt_slistex);
            _printcoordinates(pt_slist);
            _printcoordinates(pt_slistex);
            t_coor.x = -432;
            t_coor.y = 909;
            t_coor.z = 1;
            slist_push_front(pt_slistex, &t_coor);
            t_coor.x = 21;
            t_coor.y = 1171;
            t_coor.z = -88;
            slist_push_front(pt_slistex, &t_coor);
            _printcoordinates(pt_slist);
            _printcoordinates(pt_slistex);
            slist_swap(pt_slist, pt_slistex);
            _printcoordinates(pt_slist);
            _printcoordinates(pt_slistex);
            slist_clear(pt_slistex);
            t_coor.x = 72;
            t_coor.y = 69;
            t_coor.z = -8;
            slist_push_front(pt_slistex, &t_coor);
            t_coor.x = 33;
            t_coor.y = -19;
            t_coor.z = -21;
            slist_push_front(pt_slistex, &t_coor);
            t_coor.x = 44;
            t_coor.y = 128;
            t_coor.z = -80;
            slist_push_front(pt_slistex, &t_coor);
            t_coor.x = 32;
            t_coor.y = 69;
            t_coor.z = 69;
            slist_push_front(pt_slistex, &t_coor);
            t_coor.x = -5;
            t_coor.y = -78;
            t_coor.z = 127;
            slist_push_front(pt_slistex, &t_coor);
            _printcoordinates(pt_slist);
            _printcoordinates(pt_slistex);
            slist_swap(pt_slist, pt_slistex);
            _printcoordinates(pt_slist);
            _printcoordinates(pt_slistex);
            slist_clear(pt_slistex);
            t_coor.x = 8;
            t_coor.y = 26;
            t_coor.z = -43;
            slist_push_front(pt_slistex, &t_coor);
            t_coor.x = -2;
            t_coor.y = 24;
            t_coor.z = 100;
            slist_push_front(pt_slistex, &t_coor);
            t_coor.x = 35;
            t_coor.y = 27;
            t_coor.z = 0;
            slist_push_front(pt_slistex, &t_coor);
            _printcoordinates(pt_slist);
            _printcoordinates(pt_slistex);
            slist_swap(pt_slist, pt_slistex);
            _printcoordinates(pt_slist);
            _printcoordinates(pt_slistex);
            slist_clear(pt_slistex);
            _printcoordinates(pt_slist);
            _printcoordinates(pt_slistex);
            slist_swap(pt_slist, pt_slistex);
            _printcoordinates(pt_slist);
            _printcoordinates(pt_slistex);

            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
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
static void _printcoordinates(const slist_t* cpt_slist)
{
    iterator_t t_iter;
    assert(cpt_slist != NULL);
    printf("===================================\n");
    for(t_iter = slist_begin(cpt_slist);
        !iterator_equal(t_iter, slist_end(cpt_slist));
        t_iter = iterator_next(t_iter))
    {
        printf("(%d, %d, %d), ",
            ((coordinates_t*)iterator_get_pointer(t_iter))->x,
            ((coordinates_t*)iterator_get_pointer(t_iter))->y,
            ((coordinates_t*)iterator_get_pointer(t_iter))->z);
    }
    printf("\n");
}

static void _coordinates_init(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    ((coordinates_t*)cpv_input)->x = 0;
    ((coordinates_t*)cpv_input)->y = 0;
    ((coordinates_t*)cpv_input)->z = 0;
    *(bool_t*)pv_output = true;
}

static void _coordinates_copy(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    ((coordinates_t*)cpv_first)->x = ((coordinates_t*)cpv_second)->x;
    ((coordinates_t*)cpv_first)->y = ((coordinates_t*)cpv_second)->y;
    ((coordinates_t*)cpv_first)->z = ((coordinates_t*)cpv_second)->z;
    *(bool_t*)pv_output = true;
}

static void _coordinates_destroy(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    ((coordinates_t*)cpv_input)->x = 0;
    ((coordinates_t*)cpv_input)->y = 0;
    ((coordinates_t*)cpv_input)->z = 0;
    *(bool_t*)pv_output = true;
}

static void _coordinates_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    if(((coordinates_t*)cpv_first)->x < ((coordinates_t*)cpv_second)->x &&
       ((coordinates_t*)cpv_first)->y < ((coordinates_t*)cpv_second)->y &&
       ((coordinates_t*)cpv_first)->z < ((coordinates_t*)cpv_second)->z)
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}

static void _slist_unique_pred(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    if(*(int*)cpv_first % 5 == 0 && *(int*)cpv_second % 5 == 0)
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}

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

