/*
 *  The implementation of slist test.
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
#include <stdlib.h>
#include <ctype.h>
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
static void _slist_str_sort_pre(const void* cpv_first, const void* cpv_second, void* pv_output);
static void _slist_str_unique_pre(const void* cpv_first, const void* cpv_second, void* pv_output);
static void _slist_str_remove_pre(const void* cpv_input, void* pv_output);
static void _print_slist_src(const slist_t* cpt_slist);

static void _slist_sort_slist_pred(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _slist_unique_slist_pred(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _slist_remove_slist_pred(const void* cpv_input, void* pv_output);

static void _printslist(const slist_t* cpt_slist);

static void _slist_unique_coor_pred(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _slist_sort_coor_pred(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _slist_remove_coor_pred1(const void* cpv_input, void* pv_output);
static void _slist_remove_coor_pred2(const void* cpv_input, void* pv_output);
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
        {
            slist_t* pt_slist = create_slist(coordinates_t);
            coordinates_t t_coor;
            int i = 0;
            int n_count = 0;
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            srand((unsigned)time(NULL) + 111);
            n_count = rand() % 100;
            for(i = 0; i < n_count; ++i)
            {
                t_coor.x = rand() - rand();
                t_coor.y = rand() - rand();
                t_coor.z = rand() - rand();
                slist_push_front(pt_slist, &t_coor);
            }
            _printcoordinates(pt_slist);
            i = 0;
            printf("=================================\n");
            while(!slist_empty(pt_slist))
            {
                if(slist_front(pt_slist) != NULL)
                {
                    ((coordinates_t*)slist_front(pt_slist))->x = i;
                    ((coordinates_t*)slist_front(pt_slist))->y = i * 10;
                    ((coordinates_t*)slist_front(pt_slist))->z = i * 100;
                    printf("<%d, %d, %d>, ",
                        ((coordinates_t*)slist_front(pt_slist))->x,
                        ((coordinates_t*)slist_front(pt_slist))->y,
                        ((coordinates_t*)slist_front(pt_slist))->z);
                }
                ++i;
                slist_pop_front(pt_slist);
            }
            printf("\n");
            _printcoordinates(pt_slist);
            slist_destroy(pt_slist);
        }
        /*slist_push_front        */
        /*slist_pop_front         */
        /*slist_insert            */
        {
            slist_t* pt_slist = create_slist(coordinates_t);
            coordinates_t t_coor;
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            t_coor.x = 23;
            t_coor.y = -8;
            t_coor.z = 34;
            slist_insert(pt_slist, slist_begin(pt_slist), &t_coor);
            _printcoordinates(pt_slist);
            t_coor.x = 222;
            t_coor.y = 9;
            t_coor.z = 7;
            slist_insert(pt_slist, slist_begin(pt_slist), &t_coor);
            _printcoordinates(pt_slist);
            t_coor.x = 111;
            t_coor.y = 421;
            t_coor.z = 87;
            slist_insert(pt_slist, slist_end(pt_slist), &t_coor);
            _printcoordinates(pt_slist);
            t_coor.x = 0;
            t_coor.y = 1;
            t_coor.z = 4;
            slist_insert(pt_slist, iterator_advance(slist_begin(pt_slist), 2), &t_coor);
            _printcoordinates(pt_slist);
            slist_destroy(pt_slist);
        }
        /*slist_insert_n          */
        {
            slist_t* pt_slist = create_slist(coordinates_t);
            coordinates_t t_coor;
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            t_coor.x = 23;
            t_coor.y = -8;
            t_coor.z = 34;
            slist_insert_n(pt_slist, slist_begin(pt_slist), 0, &t_coor);
            _printcoordinates(pt_slist);
            t_coor.x = 222;
            t_coor.y = 9;
            t_coor.z = 7;
            slist_insert_n(pt_slist, slist_begin(pt_slist), 5, &t_coor);
            _printcoordinates(pt_slist);
            t_coor.x = 111;
            t_coor.y = 421;
            t_coor.z = 87;
            slist_insert_n(pt_slist, slist_begin(pt_slist), 3, &t_coor);
            _printcoordinates(pt_slist);
            t_coor.x = -111;
            t_coor.y = -421;
            t_coor.z = -87;
            slist_insert_n(pt_slist, slist_end(pt_slist), 3, &t_coor);
            _printcoordinates(pt_slist);
            t_coor.x = 0;
            t_coor.y = 1;
            t_coor.z = 4;
            slist_insert_n(pt_slist, iterator_advance(slist_begin(pt_slist), 2), 2, &t_coor);
            _printcoordinates(pt_slist);
            slist_destroy(pt_slist);
        }
        /*slist_insert_range      */
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
            slist_insert_range(pt_slist, slist_begin(pt_slist),
                slist_begin(pt_slistex), slist_end(pt_slistex));
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
            slist_insert_range(pt_slist, slist_begin(pt_slist),
                slist_begin(pt_slistex), slist_begin(pt_slistex));
            _printcoordinates(pt_slist);
            slist_insert_range(pt_slist, slist_begin(pt_slist),
                slist_begin(pt_slistex), iterator_advance(slist_begin(pt_slistex), 2));
            _printcoordinates(pt_slist);
            slist_insert_range(pt_slist, slist_begin(pt_slist),
                iterator_advance(slist_begin(pt_slistex), 3),
                iterator_advance(slist_begin(pt_slistex), 6));
            _printcoordinates(pt_slist);
            slist_insert_range(pt_slist, slist_end(pt_slist),
                iterator_advance(slist_begin(pt_slistex), 8), slist_end(pt_slistex));
            _printcoordinates(pt_slist);
            slist_insert_range(pt_slist, iterator_advance(slist_begin(pt_slist), 5),
                slist_begin(pt_slistex), slist_end(pt_slistex));
            _printcoordinates(pt_slist);
            slist_insert_range(pt_slist, iterator_advance(slist_begin(pt_slist), 2),
                slist_end(pt_slistex), slist_end(pt_slistex));
            _printcoordinates(pt_slist);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_insert_after      */
        {
            slist_t* pt_slist = create_slist(coordinates_t);
            coordinates_t t_coor;
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init_n(pt_slist, 10);
            _printcoordinates(pt_slist);
            t_coor.x = t_coor.y = t_coor.z = 100;
            slist_insert_after(pt_slist, slist_begin(pt_slist), &t_coor);
            _printcoordinates(pt_slist);
            t_coor.x = t_coor.y = t_coor.z = 200;
            slist_insert_after(pt_slist, iterator_advance(slist_begin(pt_slist), 5), &t_coor);
            _printcoordinates(pt_slist);
            t_coor.x = t_coor.y = t_coor.z = 300;
            slist_insert_after(pt_slist,
                slist_previous(pt_slist, slist_end(pt_slist)), &t_coor);
            _printcoordinates(pt_slist);
            slist_destroy(pt_slist);
        }
        /*slist_insert_after_n    */
        {
            slist_t* pt_slist = create_slist(coordinates_t);
            coordinates_t t_coor;
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init_n(pt_slist, 10);
            _printcoordinates(pt_slist);
            t_coor.x = t_coor.y = t_coor.z = 1;
            slist_insert_after_n(pt_slist, slist_begin(pt_slist), 0, &t_coor);
            _printcoordinates(pt_slist);
            t_coor.x = t_coor.y = t_coor.z = 100;
            slist_insert_after_n(pt_slist, slist_begin(pt_slist), 3, &t_coor);
            _printcoordinates(pt_slist);
            t_coor.x = t_coor.y = t_coor.z = 200;
            slist_insert_after_n(pt_slist,
                iterator_advance(slist_begin(pt_slist), 5), 4, &t_coor);
            _printcoordinates(pt_slist);
            t_coor.x = t_coor.y = t_coor.z = 300;
            slist_insert_after_n(pt_slist,
                slist_previous(pt_slist, slist_end(pt_slist)), 5, &t_coor);
            _printcoordinates(pt_slist);
            slist_destroy(pt_slist);
        }
        /*slist_insert_after_range*/
        {
            slist_t* pt_slist = create_slist(coordinates_t);
            slist_t* pt_slistex = create_slist(coordinates_t);
            coordinates_t t_coor;
            int i = 0;
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init_n(pt_slist, 10);
            slist_init(pt_slistex);
            for(i = 0; i < 10; ++i)
            {
                t_coor.x = t_coor.y = t_coor.z = i;
                slist_push_front(pt_slistex, &t_coor);
            }
            _printcoordinates(pt_slist);
            _printcoordinates(pt_slistex);
            slist_insert_after_range(pt_slist, slist_begin(pt_slist),
                slist_begin(pt_slistex), slist_begin(pt_slistex));
            _printcoordinates(pt_slist);
            slist_insert_after_range(pt_slist, slist_begin(pt_slist),
                slist_begin(pt_slistex), iterator_advance(slist_begin(pt_slistex), 3));
            _printcoordinates(pt_slist);
            slist_insert_after_range(pt_slist, iterator_advance(slist_begin(pt_slist), 3),
                iterator_advance(slist_begin(pt_slistex), 3),
                iterator_advance(slist_begin(pt_slistex), 6));
            _printcoordinates(pt_slist);
            slist_insert_after_range(pt_slist, slist_previous(pt_slist, slist_end(pt_slist)),
                iterator_advance(slist_begin(pt_slistex), 7),
                slist_previous(pt_slistex, slist_end(pt_slistex)));
            _printcoordinates(pt_slist);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_erase             */
        {
            slist_t* pt_slist = create_slist(coordinates_t);
            coordinates_t t_coor;
            int i = 0;
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            for(i = 0; i < 10; ++i)
            {
                t_coor.x = t_coor.y = t_coor.z = i;
                slist_push_front(pt_slist, &t_coor);
            }
            _printcoordinates(pt_slist);
            slist_erase(pt_slist, slist_begin(pt_slist));
            _printcoordinates(pt_slist);
            slist_erase(pt_slist, iterator_advance(slist_begin(pt_slist), 4));
            _printcoordinates(pt_slist);
            slist_erase(pt_slist, slist_previous(pt_slist, slist_end(pt_slist)));
            _printcoordinates(pt_slist);
            slist_destroy(pt_slist);
        }
        /*slist_erase_range       */
        {
            slist_t* pt_slist = create_slist(coordinates_t);
            coordinates_t t_coor;
            int i = 0;
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_erase_range(pt_slist, slist_begin(pt_slist), slist_end(pt_slist));
            _printcoordinates(pt_slist);
            for(i = 0; i < 10; ++i)
            {
                t_coor.x = t_coor.y = t_coor.z = i;
                slist_push_front(pt_slist, &t_coor);
            }
            _printcoordinates(pt_slist);
            slist_erase_range(pt_slist, slist_begin(pt_slist), slist_begin(pt_slist));
            _printcoordinates(pt_slist);
            slist_erase_range(pt_slist,
                slist_begin(pt_slist), iterator_advance(slist_begin(pt_slist), 3));
            _printcoordinates(pt_slist);
            slist_erase_range(pt_slist,
                iterator_advance(slist_begin(pt_slist), 3),
                iterator_advance(slist_begin(pt_slist), 5));
            _printcoordinates(pt_slist);
            slist_erase_range(pt_slist,
                slist_previous(pt_slist, slist_end(pt_slist)), slist_end(pt_slist));
            _printcoordinates(pt_slist);
            slist_erase_range(pt_slist, slist_begin(pt_slist), slist_end(pt_slist));
            _printcoordinates(pt_slist);
            slist_destroy(pt_slist);
        }
        /*slist_erase_after       */
        {
            slist_t* pt_slist = create_slist(coordinates_t);
            coordinates_t t_coor;
            int i = 0;
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            for(i = 0; i < 10; ++i)
            {
                t_coor.x = t_coor.y = t_coor.z = i;
                slist_push_front(pt_slist, &t_coor);
            }
            _printcoordinates(pt_slist);
            slist_erase_after(pt_slist, slist_begin(pt_slist));
            _printcoordinates(pt_slist);
            slist_erase_after(pt_slist, iterator_advance(slist_begin(pt_slist), 4));
            _printcoordinates(pt_slist);
            slist_erase_after(pt_slist,
                slist_previous(pt_slist, slist_previous(pt_slist, slist_end(pt_slist))));
            _printcoordinates(pt_slist);
            slist_destroy(pt_slist);
        }
        /*slist_erase_after_range */
        {
            slist_t* pt_slist = create_slist(coordinates_t);
            coordinates_t t_coor;
            int i = 0;
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            for(i = 0; i < 10; ++i)
            {
                t_coor.x = t_coor.y = t_coor.z = i;
                slist_push_front(pt_slist, &t_coor);
            }
            _printcoordinates(pt_slist);
            slist_erase_after_range(pt_slist, slist_begin(pt_slist), slist_begin(pt_slist));
            _printcoordinates(pt_slist);
            slist_erase_after_range(pt_slist,
                slist_begin(pt_slist), iterator_advance(slist_begin(pt_slist), 3));
            _printcoordinates(pt_slist);
            slist_erase_after_range(pt_slist,
                iterator_advance(slist_begin(pt_slist), 3),
                iterator_advance(slist_begin(pt_slist), 5));
            _printcoordinates(pt_slist);
            slist_erase_after_range(pt_slist,
                iterator_advance(slist_begin(pt_slist), 3), slist_end(pt_slist));
            _printcoordinates(pt_slist);
            slist_erase_after_range(pt_slist,
                slist_previous(pt_slist, slist_end(pt_slist)), slist_end(pt_slist));
            _printcoordinates(pt_slist);
            slist_erase_after_range(pt_slist, slist_begin(pt_slist), slist_end(pt_slist));
            _printcoordinates(pt_slist);
            slist_destroy(pt_slist);
        }
        /*slist_splice            */
        {
            slist_t* pt_slist = create_slist(coordinates_t);
            slist_t* pt_slistex = create_slist(coordinates_t);
            coordinates_t t_coor;
            int i = 0;
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            slist_splice(pt_slist, slist_begin(pt_slist), pt_slistex);
            t_coor.x = t_coor.y = t_coor.z = 0;
            slist_insert_n(pt_slist, slist_begin(pt_slist), 10, &t_coor);
            _printcoordinates(pt_slist);
            slist_splice(pt_slist, slist_begin(pt_slist), pt_slistex);
            _printcoordinates(pt_slist);
            for(i = 0; i < 10; ++i)
            {
                t_coor.x = t_coor.y = t_coor.z = i + 1;
                slist_push_front(pt_slistex, &t_coor);
            }
            _printcoordinates(pt_slistex);
            slist_splice(pt_slist, slist_begin(pt_slist), pt_slistex);
            _printcoordinates(pt_slist);
            for(i = 0; i < 10; ++i)
            {
                t_coor.x = t_coor.y = t_coor.z = (i + 1) * 10;
                slist_push_front(pt_slistex, &t_coor);
            }
            _printcoordinates(pt_slistex);
            slist_splice(pt_slist, iterator_advance(slist_begin(pt_slist), 11), pt_slistex);
            _printcoordinates(pt_slist);
            for(i = 0; i < 10; ++i)
            {
                t_coor.x = t_coor.y = t_coor.z = (i + 1) * 100;
                slist_push_front(pt_slistex, &t_coor);
            }
            _printcoordinates(pt_slistex);
            slist_splice(pt_slist, slist_end(pt_slist), pt_slistex);
            _printcoordinates(pt_slist);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_splice_pos        */
        {
            slist_t* pt_slist = create_slist(coordinates_t);
            slist_t* pt_slistex = create_slist(coordinates_t);
            coordinates_t t_coor;
            int i = 0;
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            for(i = 0; i < 10; ++i)
            {
                t_coor.x = t_coor.y = t_coor.z = i + 1;
                slist_push_front(pt_slistex, &t_coor);
            }
            _printcoordinates(pt_slistex);
            slist_splice_pos(pt_slist, slist_begin(pt_slist),
                pt_slistex, slist_begin(pt_slistex));
            _printcoordinates(pt_slist);
            _printcoordinates(pt_slistex);
            slist_splice_pos(pt_slist, slist_begin(pt_slist),
                pt_slistex, iterator_next(slist_begin(pt_slistex)));
            _printcoordinates(pt_slist);
            _printcoordinates(pt_slistex);
            slist_splice_pos(pt_slist, slist_end(pt_slist),
                pt_slistex, slist_previous(pt_slistex, slist_end(pt_slistex)));
            _printcoordinates(pt_slist);
            _printcoordinates(pt_slistex);
            slist_splice_pos(pt_slist, iterator_advance(slist_begin(pt_slist), 2),
                pt_slistex, iterator_advance(slist_begin(pt_slistex), 3));
            _printcoordinates(pt_slist);
            _printcoordinates(pt_slistex);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_splice_range      */
        {
            slist_t* pt_slist = create_slist(coordinates_t);
            slist_t* pt_slistex = create_slist(coordinates_t);
            coordinates_t t_coor;
            int i = 0;
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            slist_splice_range(pt_slist, slist_begin(pt_slist),
                pt_slistex, slist_begin(pt_slistex), slist_end(pt_slistex));
            _printcoordinates(pt_slist);
            _printcoordinates(pt_slistex);
            for(i = 0; i < 20; ++i)
            {
                t_coor.x = t_coor.y = t_coor.z = i + 1;
                slist_push_front(pt_slistex, &t_coor);
            }
            _printcoordinates(pt_slistex);
            slist_splice_range(pt_slist, slist_begin(pt_slist),
                pt_slistex, slist_begin(pt_slistex), slist_begin(pt_slistex));
            _printcoordinates(pt_slist);
            _printcoordinates(pt_slistex);
            slist_splice_range(pt_slist, slist_begin(pt_slist),
                pt_slistex, slist_begin(pt_slistex),
                iterator_advance(slist_begin(pt_slistex), 3));
            _printcoordinates(pt_slist);
            _printcoordinates(pt_slistex);
            slist_splice_range(pt_slist, slist_begin(pt_slist),
                pt_slistex, iterator_advance(slist_begin(pt_slistex), 2),
                iterator_advance(slist_begin(pt_slistex), 5));
            _printcoordinates(pt_slist);
            _printcoordinates(pt_slistex);
            slist_splice_range(pt_slist, iterator_advance(slist_begin(pt_slist), 3),
                pt_slistex, iterator_advance(slist_begin(pt_slistex), 5),
                slist_end(pt_slistex));
            _printcoordinates(pt_slist);
            _printcoordinates(pt_slistex);
            slist_splice_range(pt_slist, slist_end(pt_slist),
                pt_slistex, slist_end(pt_slistex), slist_end(pt_slistex));
            _printcoordinates(pt_slist);
            _printcoordinates(pt_slistex);
            slist_splice_range(pt_slist, slist_end(pt_slist),
                pt_slistex, slist_begin(pt_slistex), slist_end(pt_slistex));
            _printcoordinates(pt_slist);
            _printcoordinates(pt_slistex);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_splice_after_pos  */
        {
            slist_t* pt_slist = create_slist(coordinates_t);
            slist_t* pt_slistex = create_slist(coordinates_t);
            coordinates_t t_coor;
            int i = 0;
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init_n(pt_slist, 10);
            slist_init(pt_slistex);
            for(i = 0; i < 10; ++i)
            {
                t_coor.x = t_coor.y = t_coor.z = i + 1;
                slist_push_front(pt_slistex, &t_coor);
            }
            _printcoordinates(pt_slist);
            _printcoordinates(pt_slistex);
            slist_splice_after_pos(pt_slist, slist_begin(pt_slist),
                pt_slistex, slist_begin(pt_slistex));
            _printcoordinates(pt_slist);
            _printcoordinates(pt_slistex);
            slist_splice_after_pos(pt_slist, iterator_advance(slist_begin(pt_slist), 5),
                pt_slistex, iterator_advance(slist_begin(pt_slistex), 5));
            _printcoordinates(pt_slist);
            _printcoordinates(pt_slistex);
            slist_splice_after_pos(pt_slist, slist_previous(pt_slist, slist_end(pt_slist)),
                pt_slistex, slist_previous(pt_slistex, slist_previous(
                    pt_slistex, slist_end(pt_slistex))));
            _printcoordinates(pt_slist);
            _printcoordinates(pt_slistex);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_splice_after_range*/
        {
            slist_t* pt_slist = create_slist(coordinates_t);
            slist_t* pt_slistex = create_slist(coordinates_t);
            coordinates_t t_coor;
            int i = 0;
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init_n(pt_slist, 10);
            slist_init(pt_slistex);
            for(i = 0; i < 20; ++i)
            {
                t_coor.x = t_coor.y = t_coor.z = i + 1;
                slist_push_front(pt_slistex, &t_coor);
            }
            _printcoordinates(pt_slist);
            _printcoordinates(pt_slistex);
            slist_splice_after_range(pt_slist, slist_begin(pt_slist),
                pt_slistex, slist_begin(pt_slistex), slist_begin(pt_slistex));
            _printcoordinates(pt_slist);
            _printcoordinates(pt_slistex);
            slist_splice_after_range(pt_slist, slist_begin(pt_slist),
                pt_slistex, slist_begin(pt_slistex),
                iterator_advance(slist_begin(pt_slistex), 3));
            _printcoordinates(pt_slist);
            _printcoordinates(pt_slistex);
            slist_splice_after_range(pt_slist, iterator_advance(slist_begin(pt_slist), 2),
                pt_slistex, iterator_advance(slist_begin(pt_slistex), 3),
                iterator_advance(slist_begin(pt_slistex), 5));
            _printcoordinates(pt_slist);
            _printcoordinates(pt_slistex);
            slist_splice_after_range(pt_slist, slist_previous(pt_slist, slist_end(pt_slist)),
                pt_slistex, iterator_advance(slist_begin(pt_slistex), 5),
                slist_previous(pt_slistex, slist_end(pt_slistex)));
            _printcoordinates(pt_slist);
            _printcoordinates(pt_slistex);
            slist_splice_after_range(pt_slist, slist_previous(pt_slist, slist_end(pt_slist)),
                pt_slistex, slist_previous(pt_slistex, slist_end(pt_slistex)),
                slist_previous(pt_slistex, slist_end(pt_slistex)));
            _printcoordinates(pt_slist);
            _printcoordinates(pt_slistex);
            slist_splice_after_range(pt_slist, slist_previous(pt_slist, slist_end(pt_slist)),
                pt_slistex, slist_begin(pt_slistex),
                slist_previous(pt_slistex, slist_end(pt_slistex)));
            _printcoordinates(pt_slist);
            _printcoordinates(pt_slistex);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_remove            */
        {
            slist_t* pt_slist = create_slist(coordinates_t);
            coordinates_t t_coor;
            int i = 0;
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init_n(pt_slist, 5);
            for(i = 0; i < 10; ++i)
            {
                t_coor.x = t_coor.y = t_coor.z = i;
                slist_push_front(pt_slist, &t_coor);
            }
            t_coor.x = t_coor.y = t_coor.z = 3;
            slist_insert_n(pt_slist, iterator_advance(slist_begin(pt_slist), 5), 2, &t_coor);
            t_coor.x = t_coor.y = t_coor.z = 7;
            slist_insert_n(pt_slist, slist_end(pt_slist), 4, &t_coor);
            _printcoordinates(pt_slist);
            t_coor.x = t_coor.y = t_coor.z = 33;
            slist_remove(pt_slist, &t_coor);
            _printcoordinates(pt_slist);
            t_coor.x = t_coor.y = t_coor.z = 0;
            slist_remove(pt_slist, &t_coor);
            _printcoordinates(pt_slist);
            t_coor.x = 6;
            t_coor.y = 7;
            t_coor.z = 8;
            slist_remove(pt_slist, &t_coor);
            _printcoordinates(pt_slist);
            t_coor.x = 0;
            t_coor.y = 7;
            t_coor.z = 10;
            slist_remove(pt_slist, &t_coor);
            _printcoordinates(pt_slist);
            slist_destroy(pt_slist);
        }
        /*slist_remove_if         */
        {
            slist_t* pt_slist = create_slist(coordinates_t);
            coordinates_t t_coor;
            int i = 0;
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init_n(pt_slist, 3);
            for(i = 0; i < 5; ++i)
            {
                t_coor.x = i;
                t_coor.y = i * 10;
                t_coor.z = i * 100;
                slist_push_front(pt_slist, &t_coor);
            }
            for(i = 0; i < 3; ++i)
            {
                t_coor.x = t_coor.y = t_coor.z = i + 1;
                slist_insert(pt_slist, slist_end(pt_slist), &t_coor);
            }
            _printcoordinates(pt_slist);
            slist_remove_if(pt_slist, _slist_remove_coor_pred1);
            _printcoordinates(pt_slist);
            slist_remove_if(pt_slist, _slist_remove_coor_pred1);
            _printcoordinates(pt_slist);
            slist_remove_if(pt_slist, _slist_remove_coor_pred2);
            _printcoordinates(pt_slist);
            slist_destroy(pt_slist);
        }
        /*slist_unique            */
        {
            slist_t* pt_slist = create_slist(coordinates_t);
            coordinates_t t_coor;
            int i = 0;
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_unique(pt_slist);
            _printcoordinates(pt_slist);
            for(i = 0; i < 10; ++i)
            {
                t_coor.x = t_coor.y = t_coor.z = i + 1;
                slist_push_front(pt_slist, &t_coor);
                slist_push_front(pt_slist, &t_coor);
            }
            _printcoordinates(pt_slist);
            slist_unique(pt_slist);
            _printcoordinates(pt_slist);
            slist_unique(pt_slist);
            _printcoordinates(pt_slist);
            slist_destroy(pt_slist);
        }
        /*slist_unique_if         */
        {
            slist_t* pt_slist = create_slist(coordinates_t);
            coordinates_t t_coor;
            int i = 0;
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_unique_if(pt_slist, _slist_unique_coor_pred);
            _printcoordinates(pt_slist);
            for(i = 0; i < 10; ++i)
            {
                t_coor.x = t_coor.y = t_coor.z = i + 1;
                slist_push_front(pt_slist, &t_coor);
            }
            for(i = 100; i > 90; --i)
            {
                t_coor.x = t_coor.y = t_coor.z = i;
                slist_push_front(pt_slist, &t_coor);
            }
            _printcoordinates(pt_slist);
            slist_unique_if(pt_slist, _slist_unique_coor_pred);
            _printcoordinates(pt_slist);
            slist_unique_if(pt_slist, _slist_unique_coor_pred);
            _printcoordinates(pt_slist);
            slist_destroy(pt_slist);
        }
        /*slist_reverse           */
        {
            slist_t* pt_slist = create_slist(coordinates_t);
            coordinates_t t_coor;
            int n_count = 0;
            int i = 0;
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_reverse(pt_slist);
            _printcoordinates(pt_slist);
            srand((unsigned)time(NULL) + 31);
            n_count = rand() % 30;
            for(i = 0; i < n_count; ++i)
            {
                t_coor.x = rand() - rand();
                t_coor.y = rand() - rand();
                t_coor.z = rand() - rand();
                slist_push_front(pt_slist, &t_coor);
            }
            _printcoordinates(pt_slist);
            slist_reverse(pt_slist);
            _printcoordinates(pt_slist);
            slist_destroy(pt_slist);
        }
        /*slist_sort              */
        {
            slist_t* pt_slist = create_slist(coordinates_t);
            coordinates_t t_coor;
            int n_count = 0;
            int i = 0;
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_sort(pt_slist);
            _printcoordinates(pt_slist);
            srand((unsigned)time(NULL) + 31);
            n_count = rand() % 100;
            for(i = 0; i < n_count; ++i)
            {
                t_coor.x = rand() - rand();
                t_coor.y = rand() - rand();
                t_coor.z = rand() - rand();
                slist_push_front(pt_slist, &t_coor);
            }
            _printcoordinates(pt_slist);
            slist_sort(pt_slist);
            _printcoordinates(pt_slist);
            slist_destroy(pt_slist);
        }
        /*slist_sort_if           */
        {
            slist_t* pt_slist = create_slist(coordinates_t);
            coordinates_t t_coor;
            int n_count = 0;
            int i = 0;
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_sort_if(pt_slist, _slist_sort_coor_pred);
            _printcoordinates(pt_slist);
            srand((unsigned)time(NULL) + 31);
            n_count = rand() % 100;
            for(i = 0; i < n_count; ++i)
            {
                t_coor.x = rand() - rand();
                t_coor.y = rand() - rand();
                t_coor.z = rand() - rand();
                slist_push_front(pt_slist, &t_coor);
            }
            _printcoordinates(pt_slist);
            slist_sort_if(pt_slist, _slist_sort_coor_pred);
            _printcoordinates(pt_slist);
            slist_destroy(pt_slist);
        }
        /*slist_merge             */
        {
            slist_t* pt_slist = create_slist(coordinates_t);
            slist_t* pt_slistex = create_slist(coordinates_t);
            coordinates_t t_coor;
            int n_count = 0;
            int i = 0;
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            slist_merge(pt_slist, pt_slistex);
            _printcoordinates(pt_slist);
            _printcoordinates(pt_slistex);
            srand((unsigned)time(NULL) + 1111);
            n_count = rand() % 30;
            for(i = 0; i < n_count; ++i)
            {
                t_coor.x = rand() - rand();
                t_coor.y = rand() - rand();
                t_coor.z = rand() - rand();
                slist_push_front(pt_slist, &t_coor);
            }
            slist_sort(pt_slist);
            _printcoordinates(pt_slist);
            n_count = rand() % 30;
            for(i = 0; i < n_count; ++i)
            {
                t_coor.x = rand() - rand();
                t_coor.y = rand() - rand();
                t_coor.z = rand() - rand();
                slist_push_front(pt_slistex, &t_coor);
            }
            slist_sort(pt_slistex);
            _printcoordinates(pt_slistex);
            slist_merge(pt_slist, pt_slistex);
            _printcoordinates(pt_slist);
            _printcoordinates(pt_slistex);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_merge_if          */
        {
            slist_t* pt_slist = create_slist(coordinates_t);
            slist_t* pt_slistex = create_slist(coordinates_t);
            coordinates_t t_coor;
            int n_count = 0;
            int i = 0;
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            slist_merge_if(pt_slist, pt_slistex, _slist_sort_coor_pred);
            _printcoordinates(pt_slist);
            _printcoordinates(pt_slistex);
            srand((unsigned)time(NULL) + 1111);
            n_count = rand() % 30;
            for(i = 0; i < n_count; ++i)
            {
                t_coor.x = rand() - rand();
                t_coor.y = rand() - rand();
                t_coor.z = rand() - rand();
                slist_push_front(pt_slist, &t_coor);
            }
            slist_sort_if(pt_slist, _slist_sort_coor_pred);
            _printcoordinates(pt_slist);
            n_count = rand() % 30;
            for(i = 0; i < n_count; ++i)
            {
                t_coor.x = rand() - rand();
                t_coor.y = rand() - rand();
                t_coor.z = rand() - rand();
                slist_push_front(pt_slistex, &t_coor);
            }
            slist_sort_if(pt_slistex, _slist_sort_coor_pred);
            _printcoordinates(pt_slistex);
            slist_merge_if(pt_slist, pt_slistex, _slist_sort_coor_pred);
            _printcoordinates(pt_slist);
            _printcoordinates(pt_slistex);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_resize            */
        {
            slist_t* pt_slist = create_slist(coordinates_t);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            _printcoordinates(pt_slist);
            slist_resize(pt_slist, 4);
            _printcoordinates(pt_slist);
            slist_resize(pt_slist, 11);
            _printcoordinates(pt_slist);
            slist_resize(pt_slist, 7);
            _printcoordinates(pt_slist);
            slist_resize(pt_slist, 0);
            _printcoordinates(pt_slist);
            slist_destroy(pt_slist);
        }
        /*slist_resize_elem       */
        {
            slist_t* pt_slist = create_slist(coordinates_t);
            coordinates_t t_coor;
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            _printcoordinates(pt_slist);
            t_coor.x = 8;
            t_coor.y = 33;
            t_coor.z = 128;
            slist_resize_elem(pt_slist, 4, &t_coor);
            _printcoordinates(pt_slist);
            t_coor.x = 21;
            t_coor.y = -66;
            t_coor.z = -55;
            slist_resize_elem(pt_slist, 11, &t_coor);
            _printcoordinates(pt_slist);
            slist_resize(pt_slist, 7);
            _printcoordinates(pt_slist);
            slist_resize(pt_slist, 0);
            _printcoordinates(pt_slist);
            slist_destroy(pt_slist);
        }
        /*slist_clear             */
        {
            slist_t* pt_slist = create_slist(coordinates_t);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_clear(pt_slist);
            _printcoordinates(pt_slist);
            slist_resize(pt_slist, 3);
            _printcoordinates(pt_slist);
            slist_clear(pt_slist);
            _printcoordinates(pt_slist);
            slist_destroy(pt_slist);
        }
    }
    /* cstl built-in type */
    {
        /*create_slist            */
        {
            slist_t* pt_slist = create_slist(slist_t<int>);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            _printslist(pt_slist);
            slist_destroy(pt_slist);
        }
        /*slist_init              */
        /*slist_init_n            */
        {
            slist_t* pt_slist = create_slist(slist_t<int>);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init_n(pt_slist, 3);
            _printslist(pt_slist);
            slist_destroy(pt_slist);
        }
        /*slist_init_elem         */
        {
            slist_t* pt_slist = create_slist(slist_t<int>);
            slist_t* pt_slistex = create_slist(int);
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init_elem(pt_slistex, 3, 100);
            slist_init_elem(pt_slist, 3, pt_slistex);
            _printslist(pt_slist);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_init_copy         */
        {
            slist_t* pt_slist1 = create_slist(slist_t<int>);
            slist_t* pt_slist2 = create_slist(slist_t<signed>);
            slist_t* pt_slistex = create_slist(signed int);
            if(pt_slist1 == NULL || pt_slist2 == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init_elem(pt_slistex, 5, -88);
            slist_init_elem(pt_slist2, 3, pt_slistex);
            slist_init_copy(pt_slist1, pt_slist2);
            _printslist(pt_slist1);
            slist_destroy(pt_slistex);
            slist_destroy(pt_slist1);
            slist_destroy(pt_slist2);
        }
        /*slist_init_copy_range   */
        {
            slist_t* pt_slist1 = create_slist(slist_t<int>);
            slist_t* pt_slist2 = create_slist(slist_t<signed>);
            slist_t* pt_slistex = create_slist(signed int);
            if(pt_slist1 == NULL || pt_slist2 == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slistex);
            slist_init(pt_slist2);
            slist_insert_n(pt_slistex, slist_begin(pt_slistex), 4, 99);
            slist_push_front(pt_slist2, pt_slistex);
            slist_clear(pt_slistex);
            slist_insert_n(pt_slistex, slist_begin(pt_slistex), 8, -12);
            slist_push_front(pt_slist2, pt_slistex);
            slist_clear(pt_slistex);
            slist_insert_n(pt_slistex, slist_begin(pt_slistex), 2, 335);
            slist_push_front(pt_slist2, pt_slistex);
            slist_clear(pt_slistex);
            slist_insert_n(pt_slistex, slist_begin(pt_slistex), 9, 311);
            slist_push_front(pt_slist2, pt_slistex);
            _printslist(pt_slist2);
            slist_init_copy_range(pt_slist1, slist_begin(pt_slist2), slist_end(pt_slist2));
            _printslist(pt_slist1);
            slist_destroy(pt_slistex);
            slist_destroy(pt_slist1);
            slist_destroy(pt_slist2);
        }
        /*slist_destroy           */
        /*slist_size              */
        {
            slist_t* pt_slist = create_slist(slist_t<int>);
            slist_t* pt_slistex = create_slist(int);
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            printf("size : %d, empty : %d, max size : %d\n",
                slist_size(pt_slist), slist_empty(pt_slist), slist_max_size(pt_slist));
            slist_push_front(pt_slist, pt_slistex);
            slist_push_front(pt_slist, pt_slistex);
            printf("size : %d, empty : %d, max size : %d\n",
                slist_size(pt_slist), slist_empty(pt_slist), slist_max_size(pt_slist));
            slist_push_front(pt_slist, pt_slistex);
            printf("size : %d, empty : %d, max size : %d\n",
                slist_size(pt_slist), slist_empty(pt_slist), slist_max_size(pt_slist));
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_empty             */
        /*slist_max_size          */
        /*slist_begin             */
        /*slist_end               */
        /*slist_previous          */
        /*slist_equal             */
        {
            slist_t* pt_slist1 = create_slist(slist_t<int>);
            slist_t* pt_slist2 = create_slist(slist_t<int>);
            slist_t* pt_slistex = create_slist(int);
            if(pt_slist1 == NULL || pt_slist2 == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist1);
            slist_init(pt_slist2);
            slist_init(pt_slistex);
            _printslist(pt_slist1);
            _printslist(pt_slist2);
            printf("equal : %d, not equal : %d, ",
                slist_equal(pt_slist1, pt_slist2), slist_not_equal(pt_slist1, pt_slist2));
            printf("less : %d, less equal : %d, ",
                slist_less(pt_slist1, pt_slist2), slist_less_equal(pt_slist1, pt_slist2));
            printf("great : %d, great equal : %d\n",
                slist_great(pt_slist1, pt_slist2), slist_great_equal(pt_slist1, pt_slist2));

            slist_push_front(pt_slist1, pt_slistex);
            _printslist(pt_slist1);
            _printslist(pt_slist2);
            printf("equal : %d, not equal : %d, ",
                slist_equal(pt_slist1, pt_slist2), slist_not_equal(pt_slist1, pt_slist2));
            printf("less : %d, less equal : %d, ",
                slist_less(pt_slist1, pt_slist2), slist_less_equal(pt_slist1, pt_slist2));
            printf("great : %d, great equal : %d\n",
                slist_great(pt_slist1, pt_slist2), slist_great_equal(pt_slist1, pt_slist2));

            slist_push_front(pt_slist2, pt_slistex);
            _printslist(pt_slist1);
            _printslist(pt_slist2);
            printf("equal : %d, not equal : %d, ",
                slist_equal(pt_slist1, pt_slist2), slist_not_equal(pt_slist1, pt_slist2));
            printf("less : %d, less equal : %d, ",
                slist_less(pt_slist1, pt_slist2), slist_less_equal(pt_slist1, pt_slist2));
            printf("great : %d, great equal : %d\n",
                slist_great(pt_slist1, pt_slist2), slist_great_equal(pt_slist1, pt_slist2));

            slist_push_front(pt_slistex, -3);
            slist_push_front(pt_slist1, pt_slistex);
            _printslist(pt_slist1);
            _printslist(pt_slist2);
            printf("equal : %d, not equal : %d, ",
                slist_equal(pt_slist1, pt_slist2), slist_not_equal(pt_slist1, pt_slist2));
            printf("less : %d, less equal : %d, ",
                slist_less(pt_slist1, pt_slist2), slist_less_equal(pt_slist1, pt_slist2));
            printf("great : %d, great equal : %d\n",
                slist_great(pt_slist1, pt_slist2), slist_great_equal(pt_slist1, pt_slist2));

            slist_clear(pt_slistex);
            slist_push_front(pt_slistex, 0);
            slist_push_front(pt_slist2, pt_slistex);
            _printslist(pt_slist1);
            _printslist(pt_slist2);
            printf("equal : %d, not equal : %d, ",
                slist_equal(pt_slist1, pt_slist2), slist_not_equal(pt_slist1, pt_slist2));
            printf("less : %d, less equal : %d, ",
                slist_less(pt_slist1, pt_slist2), slist_less_equal(pt_slist1, pt_slist2));
            printf("great : %d, great equal : %d\n",
                slist_great(pt_slist1, pt_slist2), slist_great_equal(pt_slist1, pt_slist2));
            slist_destroy(pt_slist1);
            slist_destroy(pt_slist2);
            slist_destroy(pt_slistex);
        }
        /*slist_not_equal         */
        /*slist_less              */
        /*slist_less_equal        */
        /*slist_great             */
        /*slist_great_equal       */
        /*slist_assign            */
        {
            slist_t* pt_slist1 = create_slist(slist_t<int>);
            slist_t* pt_slist2 = create_slist(slist_t<int>);
            slist_t* pt_slistex = create_slist(int);
            if(pt_slist1 == NULL || pt_slist2 == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist1);
            slist_init(pt_slist2);
            slist_init(pt_slistex);
            slist_assign(pt_slist1, pt_slist2);
            _printslist(pt_slist1);
            _printslist(pt_slist2);
            slist_assign_elem(pt_slist2, 0, pt_slistex);
            slist_assign(pt_slist1, pt_slist2);
            _printslist(pt_slist1);
            _printslist(pt_slist2);
            slist_assign_elem(pt_slist2, 8, pt_slistex);
            slist_assign(pt_slist1, pt_slist2);
            _printslist(pt_slist1);
            _printslist(pt_slist2);
            slist_assign_elem(pt_slistex, 4, 28);
            slist_assign_elem(pt_slist2, 10, pt_slistex);
            slist_assign(pt_slist1, pt_slist2);
            _printslist(pt_slist1);
            _printslist(pt_slist2);
            slist_assign_elem(pt_slistex, 8, -34);
            slist_assign_elem(pt_slist2, 3, pt_slistex);
            slist_assign(pt_slist1, pt_slist2);
            _printslist(pt_slist1);
            _printslist(pt_slist2);
            slist_assign_elem(pt_slistex, 0, 4);
            slist_assign_elem(pt_slist2, 0, pt_slistex);
            slist_assign(pt_slist1, pt_slist2);
            _printslist(pt_slist1);
            _printslist(pt_slist2);
            slist_destroy(pt_slist1);
            slist_destroy(pt_slist2);
            slist_destroy(pt_slistex);
        }
        /*slist_assign_elem       */
        /*slist_assign_range      */
        {
            slist_t* pt_slist1 = create_slist(slist_t<int>);
            slist_t* pt_slist2 = create_slist(slist_t<int>);
            slist_t* pt_slistex = create_slist(int);
            int i = 0;
            if(pt_slist1 == NULL || pt_slist2 == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist1);
            slist_init(pt_slist2);
            slist_init(pt_slistex);
            slist_assign_range(pt_slist1, slist_begin(pt_slist2), slist_end(pt_slist2));
            _printslist(pt_slist1);
            for(i = 0; i < 10; ++i)
            {
                slist_assign_elem(pt_slistex, i + 1, i + 1);
                slist_push_front(pt_slist2, pt_slistex);
            }
            _printslist(pt_slist2);
            slist_assign_range(pt_slist1, slist_begin(pt_slist2), slist_begin(pt_slist2));
            _printslist(pt_slist1);
            slist_assign_range(pt_slist1,
                slist_begin(pt_slist2), iterator_advance(slist_begin(pt_slist2), 3));
            _printslist(pt_slist1);
            slist_assign_range(pt_slist1,
                iterator_advance(slist_begin(pt_slist2), 2),
                iterator_advance(slist_begin(pt_slist2), 8));
            _printslist(pt_slist1);
            slist_assign_range(pt_slist1,
                iterator_advance(slist_begin(pt_slist2), 8), slist_end(pt_slist2));
            _printslist(pt_slist1);
            slist_assign_range(pt_slist1, slist_end(pt_slist2), slist_end(pt_slist2));
            _printslist(pt_slist1);
            slist_destroy(pt_slist1);
            slist_destroy(pt_slist2);
            slist_destroy(pt_slistex);
        }
        /*slist_swap              */
        {
            slist_t* pt_slist1 = create_slist(slist_t<int>);
            slist_t* pt_slist2 = create_slist(slist_t<int>);
            slist_t* pt_slistex = create_slist(int);
            if(pt_slist1 == NULL || pt_slist2 == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist1);
            slist_init(pt_slist2);
            slist_init(pt_slistex);
            slist_swap(pt_slist1, pt_slist2);
            _printslist(pt_slist1);
            _printslist(pt_slist2);
            slist_assign_elem(pt_slist2, 4, pt_slistex);
            slist_swap(pt_slist1, pt_slist2);
            _printslist(pt_slist1);
            _printslist(pt_slist2);
            slist_assign_elem(pt_slistex, 9, 12);
            slist_assign_elem(pt_slist2, 8, pt_slistex);
            slist_swap(pt_slist1, pt_slist2);
            _printslist(pt_slist1);
            _printslist(pt_slist2);
            slist_assign_elem(pt_slistex, 3, -898);
            slist_assign_elem(pt_slist2, 2, pt_slistex);
            slist_swap(pt_slist1, pt_slist2);
            _printslist(pt_slist1);
            _printslist(pt_slist2);
            slist_clear(pt_slist2);
            slist_swap(pt_slist1, pt_slist2);
            _printslist(pt_slist1);
            _printslist(pt_slist2);
            slist_destroy(pt_slist1);
            slist_destroy(pt_slist2);
            slist_destroy(pt_slistex);
        }
        /*slist_front             */
        {
            slist_t* pt_slist = create_slist(slist_t<int>);
            slist_t* pt_slistex = create_slist(int);
            int i = 0;
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            for(i = 0; i < 10; ++i)
            {
                slist_assign_elem(pt_slistex, i + 1, -(i + 1));
                slist_push_front(pt_slist, pt_slistex);
            }
            _printslist(pt_slist);
            while(!slist_empty(pt_slist))
            {
                if(slist_front(pt_slist) != NULL)
                {
                    slist_push_front(slist_front(pt_slist), 0);
                    _printslist_c(slist_front(pt_slist), "%d, ", int);
                    slist_pop_front(pt_slist);
                }
            }
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_push_front        */
        /*slist_pop_front         */
        /*slist_insert            */
        {
            slist_t* pt_slist = create_slist(slist_t<int>);
            slist_t* pt_slistex = create_slist(int);
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            slist_insert(pt_slist, slist_begin(pt_slist), pt_slistex);
            _printslist(pt_slist);
            slist_assign_elem(pt_slistex, 3, 89);
            slist_insert(pt_slist, slist_begin(pt_slist), pt_slistex);
            _printslist(pt_slist);
            slist_assign_elem(pt_slistex, 9, 0);
            slist_insert(pt_slist, slist_end(pt_slist), pt_slistex);
            _printslist(pt_slist);
            slist_assign_elem(pt_slistex, 2, 256);
            slist_insert(pt_slist, iterator_next(slist_begin(pt_slist)), pt_slistex);
            _printslist(pt_slist);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_insert_n          */
        {
            slist_t* pt_slist = create_slist(slist_t<int>);
            slist_t* pt_slistex = create_slist(int);
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            slist_insert_n(pt_slist, slist_begin(pt_slist), 0, pt_slistex);
            _printslist(pt_slist);
            slist_assign_elem(pt_slistex, 7, -41);
            slist_insert_n(pt_slist, slist_begin(pt_slist), 2, pt_slistex);
            _printslist(pt_slist);
            slist_assign_elem(pt_slistex, 3, 89);
            slist_insert_n(pt_slist, slist_begin(pt_slist), 5, pt_slistex);
            _printslist(pt_slist);
            slist_assign_elem(pt_slistex, 9, 0);
            slist_insert_n(pt_slist, slist_end(pt_slist), 3, pt_slistex);
            _printslist(pt_slist);
            slist_assign_elem(pt_slistex, 2, 256);
            slist_insert_n(pt_slist, iterator_next(slist_begin(pt_slist)), 8, pt_slistex);
            _printslist(pt_slist);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_insert_range      */
        {
            slist_t* pt_slist1 = create_slist(slist_t<int>);
            slist_t* pt_slist2 = create_slist(slist_t<int>);
            slist_t* pt_slistex = create_slist(int);
            int i = 0;
            if(pt_slist1 == NULL || pt_slist2 == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist1);
            slist_init(pt_slist2);
            slist_init(pt_slistex);
            slist_insert_range(pt_slist1, slist_begin(pt_slist1),
                slist_begin(pt_slist2), slist_end(pt_slist2));
            _printslist(pt_slist1);
            for(i = 0; i < 10; ++i)
            {
                slist_assign_elem(pt_slistex, i + 1, i + 1);
                slist_push_front(pt_slist2, pt_slistex);
                slist_insert(pt_slist2, slist_end(pt_slist2), pt_slistex);
            }
            _printslist(pt_slist2);
            slist_insert_range(pt_slist1, slist_begin(pt_slist1),
                slist_begin(pt_slist2), slist_begin(pt_slist2));
            _printslist(pt_slist1);
            slist_insert_range(pt_slist1, slist_begin(pt_slist1),
                slist_begin(pt_slist2), iterator_advance(slist_begin(pt_slist2), 3));
            _printslist(pt_slist1);
            slist_insert_range(pt_slist1, slist_begin(pt_slist1),
                iterator_advance(slist_begin(pt_slist2), 3),
                iterator_advance(slist_begin(pt_slist2), 7));
            _printslist(pt_slist1);
            slist_insert_range(pt_slist1, slist_end(pt_slist1),
                iterator_advance(slist_begin(pt_slist2), 7),
                iterator_advance(slist_begin(pt_slist2), 12));
            _printslist(pt_slist1);
            slist_insert_range(pt_slist1, iterator_advance(slist_begin(pt_slist1), 3),
                iterator_advance(slist_begin(pt_slist2), 15), slist_end(pt_slist2));
            _printslist(pt_slist1);
            slist_insert_range(pt_slist1, iterator_advance(slist_begin(pt_slist1), 3),
                slist_end(pt_slist2), slist_end(pt_slist2));
            _printslist(pt_slist1);
            slist_insert_range(pt_slist1, slist_end(pt_slist1),
                slist_begin(pt_slist2), slist_end(pt_slist2));
            _printslist(pt_slist1);
            slist_destroy(pt_slist1);
            slist_destroy(pt_slist2);
            slist_destroy(pt_slistex);
        }
        /*slist_insert_after      */
        {
            slist_t* pt_slist = create_slist(slist_t<int>);
            slist_t* pt_slistex = create_slist(int);
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init_n(pt_slist, 10);
            slist_init_n(pt_slistex, 2);
            slist_insert_after(pt_slist, slist_begin(pt_slist), pt_slistex);
            _printslist(pt_slist);
            slist_assign_elem(pt_slistex, 4, 90);
            slist_insert_after(pt_slist, slist_previous(pt_slist, slist_end(pt_slist)), pt_slistex);
            _printslist(pt_slist);
            slist_assign_elem(pt_slistex, 5, 55);
            slist_insert_after(pt_slist, iterator_advance(slist_begin(pt_slist), 3), pt_slistex);
            _printslist(pt_slist);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_insert_after_n    */
        {
            slist_t* pt_slist = create_slist(slist_t<int>);
            slist_t* pt_slistex = create_slist(int);
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init_n(pt_slist, 10);
            slist_init_n(pt_slistex, 2);
            slist_insert_after_n(pt_slist, slist_begin(pt_slist), 0, pt_slistex);
            _printslist(pt_slist);
            slist_assign_elem(pt_slistex, 7, 33);
            slist_insert_after_n(pt_slist, slist_begin(pt_slist), 2, pt_slistex);
            _printslist(pt_slist);
            slist_assign_elem(pt_slistex, 4, 90);
            slist_insert_after_n(pt_slist, slist_previous(pt_slist, slist_end(pt_slist)), 5, pt_slistex);
            _printslist(pt_slist);
            slist_assign_elem(pt_slistex, 5, 55);
            slist_insert_after_n(pt_slist, iterator_advance(slist_begin(pt_slist), 3), 3, pt_slistex);
            _printslist(pt_slist);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_insert_after_range*/
        {
            slist_t* pt_slist1 = create_slist(slist_t<int>);
            slist_t* pt_slist2 = create_slist(slist_t<int>);
            slist_t* pt_slistex = create_slist(int);
            int i = 0;
            if(pt_slist1 == NULL || pt_slist2 == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init_n(pt_slist1, 3);
            slist_init(pt_slist2);
            slist_init(pt_slistex);
            slist_insert_after_range(pt_slist1, slist_begin(pt_slist1),
                slist_begin(pt_slist2), slist_end(pt_slist2));
            _printslist(pt_slist1);
            for(i = 0; i < 15; ++i)
            {
                slist_assign_elem(pt_slistex, i + 1, i + 1);
                slist_insert(pt_slist2, slist_end(pt_slist2), pt_slistex);
            }
            _printslist(pt_slist2);
            slist_insert_after_range(pt_slist1, slist_begin(pt_slist1),
                slist_begin(pt_slist2), slist_begin(pt_slist2));
            _printslist(pt_slist1);
            slist_insert_after_range(pt_slist1, slist_begin(pt_slist1),
                slist_begin(pt_slist2), iterator_advance(slist_begin(pt_slist2), 3));
            _printslist(pt_slist1);
            slist_insert_after_range(pt_slist1, iterator_advance(slist_begin(pt_slist1), 3),
                iterator_advance(slist_begin(pt_slist2), 4),
                iterator_advance(slist_begin(pt_slist2), 6));
            _printslist(pt_slist1);
            slist_insert_after_range(pt_slist1, slist_previous(pt_slist1, slist_end(pt_slist1)),
                iterator_advance(slist_begin(pt_slist2), 10), slist_end(pt_slist2));
            _printslist(pt_slist1);
            slist_insert_after_range(pt_slist1, slist_previous(pt_slist1, slist_end(pt_slist1)),
                slist_end(pt_slist2), slist_end(pt_slist2));
            _printslist(pt_slist1);
            slist_destroy(pt_slist1);
            slist_destroy(pt_slist2);
            slist_destroy(pt_slistex);
        }
        /*slist_erase             */
        {
            slist_t* pt_slist = create_slist(slist_t<int>);
            slist_t* pt_slistex = create_slist(int);
            int i = 0;
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            for(i = 0; i < 10; ++i)
            {
                slist_assign_elem(pt_slistex, 5, i);
                slist_push_front(pt_slist, pt_slistex);
            }
            _printslist(pt_slist);
            slist_erase(pt_slist, slist_begin(pt_slist));
            _printslist(pt_slist);
            slist_erase(pt_slist, slist_previous(pt_slist, slist_end(pt_slist)));
            _printslist(pt_slist);
            slist_erase(pt_slist, iterator_advance(slist_begin(pt_slist), 4));
            _printslist(pt_slist);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_erase_range       */
        {
            slist_t* pt_slist = create_slist(slist_t<int>);
            slist_t* pt_slistex = create_slist(int);
            int i = 0;
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            slist_erase_range(pt_slist, slist_begin(pt_slist), slist_end(pt_slist));
            _printslist(pt_slist);
            for(i = 0; i < 15; ++i)
            {
                slist_assign_elem(pt_slistex, 5, i);
                slist_push_front(pt_slist, pt_slistex);
            }
            _printslist(pt_slist);
            slist_erase_range(pt_slist, slist_begin(pt_slist), slist_begin(pt_slist));
            _printslist(pt_slist);
            slist_erase_range(pt_slist, slist_begin(pt_slist), iterator_advance(slist_begin(pt_slist), 3));
            _printslist(pt_slist);
            slist_erase_range(pt_slist,
                iterator_advance(slist_begin(pt_slist), 2), iterator_advance(slist_begin(pt_slist), 4));
            _printslist(pt_slist);
            slist_erase_range(pt_slist, iterator_advance(slist_begin(pt_slist), 7), slist_end(pt_slist));
            _printslist(pt_slist);
            slist_erase_range(pt_slist, slist_end(pt_slist), slist_end(pt_slist));
            _printslist(pt_slist);
            slist_erase_range(pt_slist, slist_begin(pt_slist), slist_end(pt_slist));
            _printslist(pt_slist);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_erase_after       */
        {
            slist_t* pt_slist = create_slist(slist_t<int>);
            slist_t* pt_slistex = create_slist(int);
            int i = 0;
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            for(i = 0; i < 10; ++i)
            {
                slist_assign_elem(pt_slistex, 5, i + 1);
                slist_push_front(pt_slist, pt_slistex);
            }
            _printslist(pt_slist);
            slist_erase_after(pt_slist, slist_begin(pt_slist));
            _printslist(pt_slist);
            slist_erase_after(pt_slist,
                slist_previous(pt_slist, slist_previous(pt_slist, slist_end(pt_slist))));
            _printslist(pt_slist);
            slist_erase_after(pt_slist, iterator_advance(slist_begin(pt_slist), 3));
            _printslist(pt_slist);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_erase_after_range */
        {
            slist_t* pt_slist = create_slist(slist_t<int>);
            slist_t* pt_slistex = create_slist(int);
            int i = 0;
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            slist_erase_after_range(pt_slist, slist_begin(pt_slist), slist_end(pt_slist));
            _printslist(pt_slist);
            for(i = 0; i < 15; ++i)
            {
                slist_assign_elem(pt_slistex, 5, i + 1);
                slist_push_front(pt_slist, pt_slistex);
            }
            _printslist(pt_slist);
            slist_erase_after_range(pt_slist, slist_begin(pt_slist), slist_begin(pt_slist));
            _printslist(pt_slist);
            slist_erase_after_range(pt_slist,
                slist_begin(pt_slist), iterator_advance(slist_begin(pt_slist), 3));
            _printslist(pt_slist);
            slist_erase_after_range(pt_slist,
                iterator_advance(slist_begin(pt_slist), 5),
                iterator_advance(slist_begin(pt_slist), 8));
            _printslist(pt_slist);
            slist_erase_after_range(pt_slist,
                iterator_advance(slist_begin(pt_slist), 7), slist_end(pt_slist));
            _printslist(pt_slist);
            slist_erase_after_range(pt_slist, slist_end(pt_slist), slist_end(pt_slist));
            _printslist(pt_slist);
            slist_erase_after_range(pt_slist, slist_begin(pt_slist), slist_end(pt_slist));
            _printslist(pt_slist);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_splice            */
        {
            slist_t* pt_slist1 = create_slist(slist_t<int>);
            slist_t* pt_slist2 = create_slist(slist_t<int>);
            slist_t* pt_slistex = create_slist(int);
            if(pt_slist1 == NULL || pt_slist2 == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist1);
            slist_init(pt_slist2);
            slist_init(pt_slistex);
            slist_splice(pt_slist1, slist_begin(pt_slist1), pt_slist2);
            _printslist(pt_slist1);
            slist_assign_elem(pt_slistex, 5, 9);
            slist_assign_elem(pt_slist2, 4, pt_slistex);
            slist_splice(pt_slist1, slist_begin(pt_slist1), pt_slist2);
            _printslist(pt_slist1);
            slist_assign_elem(pt_slistex, 3, -100);
            slist_assign_elem(pt_slist2, 2, pt_slistex);
            slist_splice(pt_slist1, iterator_advance(slist_begin(pt_slist1), 2), pt_slist2);
            _printslist(pt_slist1);
            slist_assign_elem(pt_slistex, 2, -5);
            slist_assign_elem(pt_slist2, 6, pt_slistex);
            slist_splice(pt_slist1, slist_end(pt_slist1), pt_slist2);
            _printslist(pt_slist1);
            slist_destroy(pt_slist1);
            slist_destroy(pt_slist2);
            slist_destroy(pt_slistex);
        }
        /*slist_splice_pos        */
        {
            slist_t* pt_slist1 = create_slist(slist_t<int>);
            slist_t* pt_slist2 = create_slist(slist_t<int>);
            slist_t* pt_slistex = create_slist(int);
            int i = 0;
            if(pt_slist1 == NULL || pt_slist2 == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist1);
            slist_init(pt_slist2);
            slist_init(pt_slistex);
            for(i = 0; i < 10; ++i)
            {
                slist_assign_elem(pt_slistex, 5, i + 1);
                slist_push_front(pt_slist2, pt_slistex);
            }
            _printslist(pt_slist2);
            slist_splice_pos(pt_slist1, slist_begin(pt_slist1),
                pt_slist2, slist_begin(pt_slist2));
            _printslist(pt_slist1);
            _printslist(pt_slist2);
            slist_splice_pos(pt_slist1, slist_begin(pt_slist1),
                pt_slist2, slist_begin(pt_slist2));
            _printslist(pt_slist1);
            _printslist(pt_slist2);
            slist_splice_pos(pt_slist1, iterator_next(slist_begin(pt_slist1)),
                pt_slist2, iterator_next(slist_begin(pt_slist2)));
            _printslist(pt_slist1);
            _printslist(pt_slist2);
            slist_splice_pos(pt_slist1, slist_end(pt_slist1),
                pt_slist2, slist_previous(pt_slist2, slist_end(pt_slist2)));
            _printslist(pt_slist1);
            _printslist(pt_slist2);
            slist_destroy(pt_slist1);
            slist_destroy(pt_slist2);
            slist_destroy(pt_slistex);
        }
        /*slist_splice_range      */
        {
            slist_t* pt_slist1 = create_slist(slist_t<int>);
            slist_t* pt_slist2 = create_slist(slist_t<int>);
            slist_t* pt_slistex = create_slist(int);
            int i = 0;
            if(pt_slist1 == NULL || pt_slist2 == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist1);
            slist_init(pt_slist2);
            slist_init(pt_slistex);
            slist_splice_range(pt_slist1, slist_begin(pt_slist1),
                pt_slist2, slist_begin(pt_slist2), slist_end(pt_slist2));
            _printslist(pt_slist1);
            _printslist(pt_slist2);
            for(i = 0; i < 15; ++i)
            {
                slist_assign_elem(pt_slistex, 5, i + 1);
                slist_push_front(pt_slist2, pt_slistex);
            }
            _printslist(pt_slist2);
            slist_splice_range(pt_slist1, slist_begin(pt_slist1),
                pt_slist2, slist_begin(pt_slist2), slist_begin(pt_slist2));
            _printslist(pt_slist1);
            _printslist(pt_slist2);
            slist_splice_range(pt_slist1, slist_begin(pt_slist1),
                pt_slist2, slist_begin(pt_slist2), iterator_advance(slist_begin(pt_slist2), 3));
            _printslist(pt_slist1);
            _printslist(pt_slist2);
            slist_splice_range(pt_slist1, slist_begin(pt_slist1),
                pt_slist2, slist_begin(pt_slist2), iterator_advance(slist_begin(pt_slist2), 3));
            _printslist(pt_slist1);
            _printslist(pt_slist2);
            slist_splice_range(pt_slist1, iterator_next(slist_begin(pt_slist1)),
                pt_slist2, iterator_next(slist_begin(pt_slist2)), iterator_advance(slist_begin(pt_slist2), 4));
            _printslist(pt_slist1);
            _printslist(pt_slist2);
            slist_splice_range(pt_slist1, slist_end(pt_slist1),
                pt_slist2, iterator_advance(slist_begin(pt_slist2), 4), slist_end(pt_slist2)); 
            _printslist(pt_slist1);
            _printslist(pt_slist2);
            slist_splice_range(pt_slist1, slist_end(pt_slist1),
                pt_slist2, slist_end(pt_slist2), slist_end(pt_slist2));
            _printslist(pt_slist1);
            _printslist(pt_slist2);
            slist_splice_range(pt_slist1, slist_end(pt_slist1),
                pt_slist2, slist_begin(pt_slist2), slist_end(pt_slist2));
            _printslist(pt_slist1);
            _printslist(pt_slist2);
            slist_destroy(pt_slist1);
            slist_destroy(pt_slist2);
            slist_destroy(pt_slistex);
        }
        /*slist_splice_after_pos  */
        {
            slist_t* pt_slist1 = create_slist(slist_t<int>);
            slist_t* pt_slist2 = create_slist(slist_t<int>);
            slist_t* pt_slistex = create_slist(int);
            int i = 0;
            if(pt_slist1 == NULL || pt_slist2 == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init_n(pt_slist1, 4);
            slist_init(pt_slist2);
            slist_init(pt_slistex);
            for(i = 0; i < 15; ++i)
            {
                slist_assign_elem(pt_slistex, 5, i + 1);
                slist_push_front(pt_slist2, pt_slistex);
            }
            _printslist(pt_slist1);
            _printslist(pt_slist2);
            slist_splice_after_pos(pt_slist1, slist_begin(pt_slist1),
                pt_slist2, slist_begin(pt_slist2));
            _printslist(pt_slist1);
            _printslist(pt_slist2);
            slist_splice_after_pos(pt_slist1, iterator_next(slist_begin(pt_slist1)),
                pt_slist2, iterator_next(slist_begin(pt_slist2)));
            _printslist(pt_slist1);
            _printslist(pt_slist2);
            slist_splice_after_pos(pt_slist1, slist_previous(pt_slist1, slist_end(pt_slist1)),
                pt_slist2, slist_previous(pt_slist2, slist_previous(pt_slist2, slist_end(pt_slist2))));
            _printslist(pt_slist1);
            _printslist(pt_slist2);
            slist_destroy(pt_slist1);
            slist_destroy(pt_slist2);
            slist_destroy(pt_slistex);
        }
        /*slist_splice_after_range*/
        {
            slist_t* pt_slist1 = create_slist(slist_t<int>);
            slist_t* pt_slist2 = create_slist(slist_t<int>);
            slist_t* pt_slistex = create_slist(int);
            int i = 0;
            if(pt_slist1 == NULL || pt_slist2 == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init_n(pt_slist1, 4);
            slist_init(pt_slist2);
            slist_init(pt_slistex);
            for(i = 0; i < 15; ++i)
            {
                slist_assign_elem(pt_slistex, 5, i + 1);
                slist_push_front(pt_slist2, pt_slistex);
            }
            _printslist(pt_slist1);
            _printslist(pt_slist2);
            slist_splice_after_range(pt_slist1, slist_begin(pt_slist1),
                pt_slist2, slist_begin(pt_slist2), slist_begin(pt_slist2));
            _printslist(pt_slist1);
            _printslist(pt_slist2);
            slist_splice_after_range(pt_slist1, slist_begin(pt_slist1),
                pt_slist2, slist_begin(pt_slist2), iterator_advance(slist_begin(pt_slist2), 3));
            _printslist(pt_slist1);
            _printslist(pt_slist2);
            slist_splice_after_range(pt_slist1, iterator_next(slist_begin(pt_slist1)),
                pt_slist2, iterator_next(slist_begin(pt_slist2)), iterator_advance(slist_begin(pt_slist2), 4));
            _printslist(pt_slist1);
            _printslist(pt_slist2);
            slist_splice_after_range(pt_slist1, slist_previous(pt_slist1, slist_end(pt_slist1)),
                pt_slist2, iterator_advance(slist_begin(pt_slist2), 5), slist_previous(pt_slist2, slist_end(pt_slist2)));
            _printslist(pt_slist1);
            _printslist(pt_slist2);
            slist_splice_after_range(pt_slist1, slist_previous(pt_slist1, slist_end(pt_slist1)),
                pt_slist2, slist_begin(pt_slist2), slist_previous(pt_slist2, slist_end(pt_slist2)));
            _printslist(pt_slist1);
            _printslist(pt_slist2);
            slist_destroy(pt_slist1);
            slist_destroy(pt_slist2);
            slist_destroy(pt_slistex);
        }
        /*slist_remove            */
        {
            slist_t* pt_slist = create_slist(slist_t<int>);
            slist_t* pt_slistex = create_slist(int);
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            slist_assign_elem(pt_slistex, 3, 67);
            slist_remove(pt_slist, pt_slistex);
            _printslist(pt_slist);
            slist_assign_elem(pt_slistex, 5, 0);
            slist_insert_n(pt_slist, slist_end(pt_slist), 3, pt_slistex);
            slist_assign_elem(pt_slistex, 8, 2);
            slist_insert_n(pt_slist, slist_end(pt_slist), 2, pt_slistex);
            slist_assign_elem(pt_slistex, 3, 67);
            slist_insert_n(pt_slist, slist_end(pt_slist), 4, pt_slistex);
            slist_assign_elem(pt_slistex, 5, 2);
            slist_insert_n(pt_slist, slist_end(pt_slist), 3, pt_slistex);
            slist_assign_elem(pt_slistex, 7, 67);
            slist_insert_n(pt_slist, slist_end(pt_slist), 4, pt_slistex);
            _printslist(pt_slist);
            slist_assign_elem(pt_slistex, 8, 2);
            slist_remove(pt_slist, pt_slistex);
            _printslist(pt_slist);
            slist_remove(pt_slist, pt_slistex);
            _printslist(pt_slist);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_remove_if         */
        {
            slist_t* pt_slist = create_slist(slist_t<int>);
            slist_t* pt_slistex = create_slist(int);
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            slist_remove_if(pt_slist, _slist_remove_slist_pred);
            _printslist(pt_slist);
            slist_assign_elem(pt_slistex, 5, 0);
            slist_insert_n(pt_slist, slist_end(pt_slist), 3, pt_slistex);
            slist_assign_elem(pt_slistex, 8, 2);
            slist_insert_n(pt_slist, slist_end(pt_slist), 2, pt_slistex);
            slist_assign_elem(pt_slistex, 3, 67);
            slist_insert_n(pt_slist, slist_end(pt_slist), 4, pt_slistex);
            slist_assign_elem(pt_slistex, 5, 2);
            slist_insert_n(pt_slist, slist_end(pt_slist), 3, pt_slistex);
            slist_assign_elem(pt_slistex, 7, 67);
            slist_insert_n(pt_slist, slist_end(pt_slist), 4, pt_slistex);
            _printslist(pt_slist);
            slist_remove_if(pt_slist, _slist_remove_slist_pred);
            _printslist(pt_slist);
            slist_remove_if(pt_slist, _slist_remove_slist_pred);
            _printslist(pt_slist);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_unique            */
        {
            slist_t* pt_slist = create_slist(slist_t<int>);
            slist_t* pt_slistex = create_slist(int);
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            slist_unique(pt_slist);
            _printslist(pt_slist);
            slist_assign_elem(pt_slistex, 5, 0);
            slist_insert_n(pt_slist, slist_end(pt_slist), 3, pt_slistex);
            slist_assign_elem(pt_slistex, 8, 2);
            slist_insert_n(pt_slist, slist_end(pt_slist), 2, pt_slistex);
            slist_assign_elem(pt_slistex, 3, 67);
            slist_insert_n(pt_slist, slist_end(pt_slist), 4, pt_slistex);
            slist_assign_elem(pt_slistex, 4, 11);
            slist_insert_n(pt_slist, slist_end(pt_slist), 2, pt_slistex);
            slist_assign_elem(pt_slistex, 5, 2);
            slist_insert_n(pt_slist, slist_end(pt_slist), 3, pt_slistex);
            slist_assign_elem(pt_slistex, 7, 67);
            slist_insert_n(pt_slist, slist_end(pt_slist), 4, pt_slistex);
            _printslist(pt_slist);
            slist_unique(pt_slist);
            _printslist(pt_slist);
            slist_unique(pt_slist);
            _printslist(pt_slist);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_unique_if         */
        {
            slist_t* pt_slist = create_slist(slist_t<int>);
            slist_t* pt_slistex = create_slist(int);
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            slist_unique_if(pt_slist, _slist_unique_slist_pred);
            _printslist(pt_slist);
            slist_assign_elem(pt_slistex, 5, 0);
            slist_insert_n(pt_slist, slist_end(pt_slist), 3, pt_slistex);
            slist_assign_elem(pt_slistex, 8, 2);
            slist_insert_n(pt_slist, slist_end(pt_slist), 2, pt_slistex);
            slist_assign_elem(pt_slistex, 3, 67);
            slist_insert_n(pt_slist, slist_end(pt_slist), 4, pt_slistex);
            slist_assign_elem(pt_slistex, 4, 11);
            slist_insert_n(pt_slist, slist_end(pt_slist), 2, pt_slistex);
            slist_assign_elem(pt_slistex, 5, 2);
            slist_insert_n(pt_slist, slist_end(pt_slist), 3, pt_slistex);
            slist_assign_elem(pt_slistex, 7, 67);
            slist_insert_n(pt_slist, slist_end(pt_slist), 4, pt_slistex);
            _printslist(pt_slist);
            slist_unique_if(pt_slist, _slist_unique_slist_pred);
            _printslist(pt_slist);
            slist_unique_if(pt_slist, _slist_unique_slist_pred);
            _printslist(pt_slist);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_reverse           */
        {
            slist_t* pt_slist = create_slist(slist_t<int>);
            slist_t* pt_slistex = create_slist(int);
            int n_count = 0;
            int n_countex = 0;
            int i, j;
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            slist_reverse(pt_slist);
            _printslist(pt_slist);
            srand((unsigned)time(NULL) + 119);
            n_count = rand() % 20;
            for(i = 0; i < n_count; ++i)
            {
                slist_clear(pt_slistex);
                n_countex = rand() % 10;
                for(j = 0; j < n_countex; ++j)
                {
                    slist_push_front(pt_slistex, rand()-rand());
                }
                slist_push_front(pt_slist, pt_slistex);
            }
            _printslist(pt_slist);
            slist_reverse(pt_slist);
            _printslist(pt_slist);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_sort              */
        {
            slist_t* pt_slist = create_slist(slist_t<int>);
            slist_t* pt_slistex = create_slist(int);
            int n_count = 0;
            int n_countex = 0;
            int i, j;
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            slist_sort(pt_slist);
            _printslist(pt_slist);
            srand((unsigned)time(NULL) + 110);
            n_count = rand() % 30;
            for(i = 0; i < n_count; ++i)
            {
                slist_clear(pt_slistex);
                n_countex = rand() % 10;
                for(j = 0; j < n_countex; ++j)
                {
                    slist_push_front(pt_slistex, rand()-rand());
                }
                slist_push_front(pt_slist, pt_slistex);
            }
            _printslist(pt_slist);
            slist_sort(pt_slist);
            _printslist(pt_slist);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_sort_if           */
        {
            slist_t* pt_slist = create_slist(slist_t<int>);
            slist_t* pt_slistex = create_slist(int);
            int n_count = 0;
            int n_countex = 0;
            int i, j;
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            slist_sort_if(pt_slist, _slist_sort_slist_pred);
            _printslist(pt_slist);
            srand((unsigned)time(NULL) + 110);
            n_count = rand() % 30;
            for(i = 0; i < n_count; ++i)
            {
                slist_clear(pt_slistex);
                n_countex = rand() % 10;
                for(j = 0; j < n_countex; ++j)
                {
                    slist_push_front(pt_slistex, rand()-rand());
                }
                slist_push_front(pt_slist, pt_slistex);
            }
            _printslist(pt_slist);
            slist_sort_if(pt_slist, _slist_sort_slist_pred);
            _printslist(pt_slist);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_merge             */
        {
            slist_t* pt_slist1 = create_slist(slist_t<int>);
            slist_t* pt_slist2 = create_slist(slist_t<int>);
            slist_t* pt_slistex = create_slist(int);
            int n_count = 0;
            int n_countex = 0;
            int i, j;
            if(pt_slist1 == NULL || pt_slist2 == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist1);
            slist_init(pt_slist2);
            slist_init(pt_slistex);
            slist_merge(pt_slist1, pt_slist2);
            _printslist(pt_slist1);
            _printslist(pt_slist2);
            srand((unsigned)time(NULL) + 110);
            n_count = rand() % 30;
            for(i = 0; i < n_count; ++i)
            {
                slist_clear(pt_slistex);
                n_countex = rand() % 10;
                for(j = 0; j < n_countex; ++j)
                {
                    slist_push_front(pt_slistex, rand()-rand());
                }
                slist_push_front(pt_slist1, pt_slistex);
            }
            n_count = rand() % 30;
            for(i = 0; i < n_count; ++i)
            {
                slist_clear(pt_slistex);
                n_countex = rand() % 10;
                for(j = 0; j < n_countex; ++j)
                {
                    slist_push_front(pt_slistex, rand()-rand());
                }
                slist_push_front(pt_slist2, pt_slistex);
            }
            slist_sort(pt_slist1);
            slist_sort(pt_slist2);
            _printslist(pt_slist1);
            _printslist(pt_slist2);
            slist_merge(pt_slist1, pt_slist2);
            _printslist(pt_slist1);
            _printslist(pt_slist2);
            slist_destroy(pt_slist1);
            slist_destroy(pt_slist2);
            slist_destroy(pt_slistex);
        }
        /*slist_merge_if          */
        {
            slist_t* pt_slist1 = create_slist(slist_t<int>);
            slist_t* pt_slist2 = create_slist(slist_t<int>);
            slist_t* pt_slistex = create_slist(int);
            int n_count = 0;
            int n_countex = 0;
            int i, j;
            if(pt_slist1 == NULL || pt_slist2 == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist1);
            slist_init(pt_slist2);
            slist_init(pt_slistex);
            slist_merge_if(pt_slist1, pt_slist2, _slist_sort_slist_pred);
            _printslist(pt_slist1);
            _printslist(pt_slist2);
            srand((unsigned)time(NULL) + 110);
            n_count = rand() % 30;
            for(i = 0; i < n_count; ++i)
            {
                slist_clear(pt_slistex);
                n_countex = rand() % 10;
                for(j = 0; j < n_countex; ++j)
                {
                    slist_push_front(pt_slistex, rand()-rand());
                }
                slist_push_front(pt_slist1, pt_slistex);
            }
            n_count = rand() % 30;
            for(i = 0; i < n_count; ++i)
            {
                slist_clear(pt_slistex);
                n_countex = rand() % 10;
                for(j = 0; j < n_countex; ++j)
                {
                    slist_push_front(pt_slistex, rand()-rand());
                }
                slist_push_front(pt_slist2, pt_slistex);
            }
            slist_sort_if(pt_slist1, _slist_sort_slist_pred);
            slist_sort_if(pt_slist2, _slist_sort_slist_pred);
            _printslist(pt_slist1);
            _printslist(pt_slist2);
            slist_merge_if(pt_slist1, pt_slist2, _slist_sort_slist_pred);
            _printslist(pt_slist1);
            _printslist(pt_slist2);
            slist_destroy(pt_slist1);
            slist_destroy(pt_slist2);
            slist_destroy(pt_slistex);
        }
        /*slist_resize            */
        {
            slist_t* pt_slist = create_slist(slist_t<int>);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            _printslist(pt_slist);
            slist_resize(pt_slist, 4);
            _printslist(pt_slist);
            slist_resize(pt_slist, 9);
            _printslist(pt_slist);
            slist_resize(pt_slist, 5);
            _printslist(pt_slist);
            slist_resize(pt_slist, 0);
            _printslist(pt_slist);
            slist_destroy(pt_slist);
        }
        /*slist_resize_elem       */
        {
            slist_t* pt_slist = create_slist(slist_t<int>);
            slist_t* pt_slistex = create_slist(int);
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            _printslist(pt_slist);
            slist_assign_elem(pt_slistex, 4, 78);
            slist_resize_elem(pt_slist, 4, pt_slistex);
            _printslist(pt_slist);
            slist_assign_elem(pt_slistex, 8, 8);
            slist_resize_elem(pt_slist, 9, pt_slistex);
            _printslist(pt_slist);
            slist_assign_elem(pt_slistex, 2, -51);
            slist_resize_elem(pt_slist, 5, pt_slistex);
            _printslist(pt_slist);
            slist_assign_elem(pt_slistex, 9, 0);
            slist_resize_elem(pt_slist, 0, pt_slistex);
            _printslist(pt_slist);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_clear             */
        {
            slist_t* pt_slist = create_slist(slist_t<int>);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_clear(pt_slist);
            _printslist(pt_slist);
            slist_resize(pt_slist, 8);
            _printslist(pt_slist);
            slist_clear(pt_slist);
            _printslist(pt_slist);
            slist_destroy(pt_slist);
        }
    }
    /* c-string type */
    {
        /*create_slist            */
        {
            slist_t* pt_slist = create_slist(char*);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            _print_slist_src(pt_slist);
            slist_destroy(pt_slist);
        }
        /*slist_init              */
        /*slist_init_n            */
        {
            slist_t* pt_slist = create_slist(char*);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init_n(pt_slist, 6);
            _print_slist_src(pt_slist);
            slist_destroy(pt_slist);
        }
        /*slist_init_elem         */
        {
            slist_t* pt_slist = create_slist(char*);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init_elem(pt_slist, 20, "GSS_S_CALL_INACCESSIBLE_READ");
            _print_slist_src(pt_slist);
            slist_destroy(pt_slist);
        }
        /*slist_init_copy         */
        {
            slist_t* pt_slist = create_slist(char*);
            slist_t* pt_slistex = create_slist(char*);
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init_elem(pt_slistex, 5, "GSS_S_CALL_INACCESSIBLE_WRITE");
            slist_init_copy(pt_slist, pt_slistex);
            _print_slist_src(pt_slist);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_init_copy_range   */
        {
            slist_t* pt_slist = create_slist(char*);
            slist_t* pt_slistex = create_slist(char*);
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slistex);
            slist_push_front(pt_slistex, "GSS_S_BAD_MECH");
            slist_push_front(pt_slistex, "GSS_S_BAD_NAME");
            slist_push_front(pt_slistex, "GSS_S_BAD_NAMETYPE");
            slist_push_front(pt_slistex, "GSS_S_BAD_BINDINGS");
            slist_push_front(pt_slistex, "GSS_S_BAD_STATUS");
            slist_push_front(pt_slistex, "GSS_S_BAD_SIG");
            slist_push_front(pt_slistex, "GSS_S_NO_CRED");
            slist_push_front(pt_slistex, "GSS_S_NO_CONTEXT");
            slist_push_front(pt_slistex, "GSS_S_DEFECTIVE_TOKEN");
            _print_slist_src(pt_slistex);
            slist_init_copy_range(pt_slist, slist_begin(pt_slistex), slist_end(pt_slistex));
            _print_slist_src(pt_slist);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
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
        {
            slist_t* pt_slist = create_slist(char*);
            slist_t* pt_slistex = create_slist(char*);
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            _print_slist_src(pt_slist);
            _print_slist_src(pt_slistex);
            printf("equal: %d, not equal: %d, ",
                slist_equal(pt_slist, pt_slistex), slist_not_equal(pt_slist, pt_slistex));
            printf("less: %d, less equal: %d, ",
                slist_less(pt_slist, pt_slistex), slist_less_equal(pt_slist, pt_slistex));
            printf("great: %d, great equal: %d\n",
                slist_great(pt_slist, pt_slistex), slist_great_equal(pt_slist, pt_slistex));

            slist_push_front(pt_slist, "GSS_C_AF_NBS");
            _print_slist_src(pt_slist);
            _print_slist_src(pt_slistex);
            printf("equal: %d, not equal: %d, ",
                slist_equal(pt_slist, pt_slistex), slist_not_equal(pt_slist, pt_slistex));
            printf("less: %d, less equal: %d, ",
                slist_less(pt_slist, pt_slistex), slist_less_equal(pt_slist, pt_slistex));
            printf("great: %d, great equal: %d\n",
                slist_great(pt_slist, pt_slistex), slist_great_equal(pt_slist, pt_slistex));

            slist_push_front(pt_slistex, "GSS_C_AF_NBS");
            _print_slist_src(pt_slist);
            _print_slist_src(pt_slistex);
            printf("equal: %d, not equal: %d, ",
                slist_equal(pt_slist, pt_slistex), slist_not_equal(pt_slist, pt_slistex));
            printf("less: %d, less equal: %d, ",
                slist_less(pt_slist, pt_slistex), slist_less_equal(pt_slist, pt_slistex));
            printf("great: %d, great equal: %d\n",
                slist_great(pt_slist, pt_slistex), slist_great_equal(pt_slist, pt_slistex));

            slist_push_front(pt_slistex, "GSS_C_AF_UCMA");
            _print_slist_src(pt_slist);
            _print_slist_src(pt_slistex);
            printf("equal: %d, not equal: %d, ",
                slist_equal(pt_slist, pt_slistex), slist_not_equal(pt_slist, pt_slistex));
            printf("less: %d, less equal: %d, ",
                slist_less(pt_slist, pt_slistex), slist_less_equal(pt_slist, pt_slistex));
            printf("great: %d, great equal: %d\n",
                slist_great(pt_slist, pt_slistex), slist_great_equal(pt_slist, pt_slistex));

            slist_push_front(pt_slist, "GSS_C_AF_JCMA");
            slist_push_front(pt_slist, "GSS_C_AF_BCMA");
            _print_slist_src(pt_slist);
            _print_slist_src(pt_slistex);
            printf("equal: %d, not equal: %d, ",
                slist_equal(pt_slist, pt_slistex), slist_not_equal(pt_slist, pt_slistex));
            printf("less: %d, less equal: %d, ",
                slist_less(pt_slist, pt_slistex), slist_less_equal(pt_slist, pt_slistex));
            printf("great: %d, great equal: %d\n",
                slist_great(pt_slist, pt_slistex), slist_great_equal(pt_slist, pt_slistex));
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_assign            */
        {
            slist_t* pt_slist = create_slist(char*);
            slist_t* pt_slistex = create_slist(char*);
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            slist_assign(pt_slist, pt_slistex);
            _print_slist_src(pt_slist);
            slist_push_front(pt_slistex, "CCITT protocols (eg X.25)");
            slist_push_front(pt_slistex, "NSC Hyperchannel address type");
            slist_push_front(pt_slistex, "No address specified");
            slist_push_front(pt_slistex, "X25");
            slist_push_front(pt_slistex, "OSI TP4 address type");
            slist_assign(pt_slist, pt_slistex);
            _print_slist_src(pt_slist);
            slist_clear(pt_slistex);
            slist_assign(pt_slist, pt_slistex);
            _print_slist_src(pt_slist);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_assign_elem       */
        {
            slist_t* pt_slist = create_slist(char*);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_assign_elem(pt_slist, 0, "signature is calculated in the same way");
            _print_slist_src(pt_slist);
            slist_assign_elem(pt_slist, 4, "2.1.12. Optional parameters");
            _print_slist_src(pt_slist);
            slist_assign_elem(pt_slist, 16, "Specify GSS_C_NO_BUFFER as a value.  For an input parameter this");
            _print_slist_src(pt_slist);
            slist_assign_elem(pt_slist, 3, "Integer types (output)");
            _print_slist_src(pt_slist);
            slist_assign_elem(pt_slist, 0, "GSS_C_NULL_OID_SET");
            _print_slist_src(pt_slist);
            slist_destroy(pt_slist);
        }
        /*slist_assign_range      */
        {
            slist_t* pt_slist = create_slist(char*);
            slist_t* pt_slistex = create_slist(char*);
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            slist_assign_range(pt_slist, slist_begin(pt_slistex), slist_end(pt_slistex));
            _print_slist_src(pt_slist);
            slist_push_front(pt_slistex, "CCITT protocols (eg X.25)");
            slist_push_front(pt_slistex, "NSC Hyperchannel address type");
            slist_push_front(pt_slistex, "No address specified");
            slist_push_front(pt_slistex, "X25");
            slist_push_front(pt_slistex, "OSI TP4 address type");
            slist_push_front(pt_slistex, "Parameters");
            slist_push_front(pt_slistex, "GSS_S_COMPLETE");
            slist_push_front(pt_slistex, "GSS_S_NO_CRED     Credentials could not be accessed.");
            slist_assign_range(pt_slist, slist_begin(pt_slistex), slist_begin(pt_slistex));
            _print_slist_src(pt_slist);
            slist_assign_range(pt_slist, slist_begin(pt_slistex), iterator_advance(slist_begin(pt_slistex), 3));
            _print_slist_src(pt_slist);
            slist_assign_range(pt_slist, iterator_next(slist_begin(pt_slistex)), iterator_advance(slist_begin(pt_slistex), 5));
            _print_slist_src(pt_slist);
            slist_assign_range(pt_slist, slist_previous(pt_slistex, slist_previous(pt_slistex, slist_end(pt_slistex))), slist_end(pt_slistex));
            _print_slist_src(pt_slist);
            slist_assign_range(pt_slist, slist_end(pt_slistex), slist_end(pt_slistex));
            _print_slist_src(pt_slist);
            slist_assign_range(pt_slist, slist_begin(pt_slistex), slist_end(pt_slistex));
            _print_slist_src(pt_slist);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_swap              */
        {
            slist_t* pt_slist = create_slist(char*);
            slist_t* pt_slistex = create_slist(char*);
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            slist_swap(pt_slist, pt_slistex);
            _print_slist_src(pt_slist);
            _print_slist_src(pt_slistex);
            slist_assign_elem(pt_slistex, 5, "gss_cred_id_t * cred_handle)");
            slist_swap(pt_slist, pt_slistex);
            _print_slist_src(pt_slist);
            _print_slist_src(pt_slistex);
            slist_assign_elem(pt_slistex, 7, "minor_status");
            slist_swap(pt_slist, pt_slistex);
            _print_slist_src(pt_slist);
            _print_slist_src(pt_slistex);
            slist_assign_elem(pt_slistex, 2, "GSS_S_COMPLETE");
            slist_swap(pt_slist, pt_slistex);
            _print_slist_src(pt_slist);
            _print_slist_src(pt_slistex);
            slist_assign_elem(pt_slist, 0, "Function value");
            slist_swap(pt_slist, pt_slistex);
            _print_slist_src(pt_slist);
            _print_slist_src(pt_slistex);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_front             */
        /*slist_push_front        */
        /*slist_pop_front         */
        {
            slist_t* pt_slist = create_slist(char*);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            _print_slist_src(pt_slist);
            slist_push_front(pt_slist, "the default credential will be released");
            puts(slist_front(pt_slist));
            slist_push_front(pt_slist, "GSSAPI - Overview and C bindings");
            puts(slist_front(pt_slist));
            slist_push_front(pt_slist, "typedef struct gss_OID_set_desc_struct\n{int     count;\n}");
            puts(slist_front(pt_slist));
            slist_push_front(pt_slist, "OM_uint32 initiator_addrtype;");
            puts(slist_front(pt_slist));

            while(!slist_empty(pt_slist))
            {
                slist_pop_front(pt_slist);
            }
            _print_slist_src(pt_slist);
            slist_destroy(pt_slist);
        }
        /*slist_insert            */
        {
            slist_t* pt_slist = create_slist(char*);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_insert(pt_slist, slist_begin(pt_slist), "#define GSS_C_DELEG_FLAG 1");
            _print_slist_src(pt_slist);
            slist_insert(pt_slist, slist_begin(pt_slist), "#define GSS_C_SUPPLEMENTARY_MASK 0177777ul");
            _print_slist_src(pt_slist);
            slist_insert(pt_slist, slist_end(pt_slist), "#define GSS_CALLING_ERROR(x) \\");
            _print_slist_src(pt_slist);
            slist_insert(pt_slist, iterator_next(slist_begin(pt_slist)), "#define GSS_S_CALL_INACCESSIBLE_READ");
            _print_slist_src(pt_slist);
            slist_destroy(pt_slist);
        }
        /*slist_insert_n          */
        {
            slist_t* pt_slist = create_slist(char*);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_insert_n(pt_slist, slist_begin(pt_slist), 0, "#define GSS_S_BAD_MECH (1ul << GSS_C_ROUTINE_ERROR_OFFSET)");
            _print_slist_src(pt_slist);
            slist_insert_n(pt_slist, slist_begin(pt_slist), 3, "#define GSS_S_BAD_NAME (2ul << GSS_C_ROUTINE_ERROR_OFFSET)");
            _print_slist_src(pt_slist);
            slist_insert_n(pt_slist, slist_begin(pt_slist), 6, "(3ul << GSS_C_CALLING_ERROR_OFFSET)");
            _print_slist_src(pt_slist);
            slist_insert_n(pt_slist, slist_end(pt_slist), 2, "Supplementary info bits:");
            _print_slist_src(pt_slist);
            slist_insert_n(pt_slist, slist_previous(pt_slist, slist_end(pt_slist)), 4, "");
            _print_slist_src(pt_slist);
            slist_destroy(pt_slist);
        }
        /*slist_insert_range      */
        {
            slist_t* pt_slist = create_slist(char*);
            slist_t* pt_slistex = create_slist(char*);
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            slist_insert_range(pt_slist, slist_begin(pt_slist), slist_begin(pt_slistex), slist_end(pt_slistex));
            _print_slist_src(pt_slist);
            slist_push_front(pt_slistex, "CCITT protocols (eg X.25)");
            slist_push_front(pt_slistex, "NSC Hyperchannel address type");
            slist_push_front(pt_slistex, "No address specified");
            slist_push_front(pt_slistex, "X25");
            slist_push_front(pt_slistex, "OSI TP4 address type");
            slist_push_front(pt_slistex, "Parameters");
            slist_push_front(pt_slistex, "GSS_S_COMPLETE");
            slist_push_front(pt_slistex, "GSS_S_NO_CRED     Credentials could not be accessed.");
            slist_push_front(pt_slistex, "#define GSS_S_CONTINUE_NEEDED (1ul << (GSS_C_SUPPLEMENTARY_OFFSET + 0))");
            slist_push_front(pt_slistex, "#define GSS_S_OLD_TOKEN (1ul << (GSS_C_SUPPLEMENTARY_OFFSET + 2))");
            _print_slist_src(pt_slistex);
            slist_insert_range(pt_slist, slist_begin(pt_slist), slist_begin(pt_slistex), slist_begin(pt_slistex));
            _print_slist_src(pt_slist);
            slist_insert_range(pt_slist, slist_begin(pt_slist), slist_begin(pt_slistex), iterator_advance(slist_begin(pt_slistex), 3));
            _print_slist_src(pt_slist);
            slist_insert_range(pt_slist, slist_begin(pt_slist),
                iterator_advance(slist_begin(pt_slistex), 3), iterator_advance(slist_begin(pt_slistex), 5));
            _print_slist_src(pt_slist);
            slist_insert_range(pt_slist, slist_end(pt_slist), iterator_advance(slist_begin(pt_slistex), 5), slist_end(pt_slistex));
            _print_slist_src(pt_slist);
            slist_insert_range(pt_slist, iterator_next(slist_begin(pt_slist)),
                slist_previous(pt_slistex, slist_end(pt_slistex)), slist_end(pt_slistex));
            _print_slist_src(pt_slist);
            slist_insert_range(pt_slist, slist_end(pt_slist), slist_end(pt_slistex), slist_end(pt_slistex));
            _print_slist_src(pt_slist);
            slist_insert_range(pt_slist, slist_end(pt_slist), slist_begin(pt_slistex), slist_end(pt_slistex));
            _print_slist_src(pt_slist);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_insert_after      */
        {
            slist_t* pt_slist = create_slist(char*);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init_n(pt_slist, 3);
            slist_insert_after(pt_slist, slist_begin(pt_slist), "Finally, function prototypes for the GSSAPI routines.");
            _print_slist_src(pt_slist);
            slist_insert_after(pt_slist, iterator_next(slist_begin(pt_slist)), "(OM_uint32*,       /* minor_status */");
            _print_slist_src(pt_slist);
            slist_insert_after(pt_slist, slist_previous(pt_slist, slist_end(pt_slist)), "OM_uint32 gss_release_cred,");
            _print_slist_src(pt_slist);
            slist_destroy(pt_slist);
        }
        /*slist_insert_after_n    */
        {
            slist_t* pt_slist = create_slist(char*);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init_n(pt_slist, 3);
            slist_insert_after_n(pt_slist, slist_begin(pt_slist), 0, "ifMauJabberState OBJECT-TYPE");
            _print_slist_src(pt_slist);
            slist_insert_after_n(pt_slist, slist_begin(pt_slist), 3, "dot3MauTypeAUI, this counter will always indicate");
            _print_slist_src(pt_slist);
            slist_insert_after_n(pt_slist, slist_begin(pt_slist), 5, "REFERENCE");
            _print_slist_src(pt_slist);
            slist_insert_after_n(pt_slist, iterator_next(slist_begin(pt_slist)), 2, "");
            _print_slist_src(pt_slist);
            slist_insert_after_n(pt_slist, slist_previous(pt_slist, slist_end(pt_slist)), 4, "for broadband MAUs attached to DTEs.");
            _print_slist_src(pt_slist);
            slist_destroy(pt_slist);
        }
        /*slist_insert_after_range*/
        {
            slist_t* pt_slist = create_slist(char*);
            slist_t* pt_slistex = create_slist(char*);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init_n(pt_slist, 3);
            slist_init(pt_slistex);
            slist_insert_after_range(pt_slist, slist_begin(pt_slist), slist_begin(pt_slistex), slist_end(pt_slistex));
            _print_slist_src(pt_slist);
            slist_push_front(pt_slistex, "CCITT protocols (eg X.25)");
            slist_push_front(pt_slistex, "NSC Hyperchannel address type");
            slist_push_front(pt_slistex, "No address specified");
            slist_push_front(pt_slistex, "X25");
            slist_push_front(pt_slistex, "OSI TP4 address type");
            slist_push_front(pt_slistex, "Parameters");
            slist_push_front(pt_slistex, "GSS_S_COMPLETE");
            slist_push_front(pt_slistex, "GSS_S_NO_CRED     Credentials could not be accessed.");
            slist_push_front(pt_slistex, "#define GSS_S_CONTINUE_NEEDED (1ul << (GSS_C_SUPPLEMENTARY_OFFSET + 0))");
            slist_push_front(pt_slistex, "#define GSS_S_OLD_TOKEN (1ul << (GSS_C_SUPPLEMENTARY_OFFSET + 2))");
            _print_slist_src(pt_slistex);

            slist_insert_after_range(pt_slist, slist_begin(pt_slist), slist_begin(pt_slistex), slist_begin(pt_slistex));
            _print_slist_src(pt_slist);
            slist_insert_after_range(pt_slist, slist_begin(pt_slist), slist_begin(pt_slistex), iterator_advance(slist_begin(pt_slistex), 3));
            _print_slist_src(pt_slist);
            slist_insert_after_range(pt_slist, iterator_next(slist_begin(pt_slist)),
                iterator_advance(slist_begin(pt_slistex), 3), iterator_advance(slist_begin(pt_slistex), 6));
            _print_slist_src(pt_slist);
            slist_insert_after_range(pt_slist, slist_previous(pt_slist, slist_end(pt_slist)),
                iterator_advance(slist_begin(pt_slistex), 8), slist_end(pt_slistex));
            _print_slist_src(pt_slist);
            slist_insert_after_range(pt_slist, slist_previous(pt_slist, slist_end(pt_slist)), slist_end(pt_slistex), slist_end(pt_slistex));
            _print_slist_src(pt_slist);
            slist_insert_after_range(pt_slist, slist_previous(pt_slist, slist_end(pt_slist)), slist_begin(pt_slistex), slist_end(pt_slistex));
            _print_slist_src(pt_slist);

            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_erase             */
        {
            slist_t* pt_slist = create_slist(char*);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_push_front(pt_slist, "SYNTAX    SEQUENCE OF BroadMauBasicEntry");
            slist_push_front(pt_slist, "ACCESS    not-accessible");
            slist_push_front(pt_slist, "STATUS    mandatory");
            slist_push_front(pt_slist, "DESCRIPTION");
            slist_push_front(pt_slist, "Table of descriptive and status information about");
            slist_push_front(pt_slist, "the broadband MAUs connected to interfaces.");
            slist_push_front(pt_slist, "{ dot3BroadMauBasicGroup 1 }");
            slist_push_front(pt_slist, "broadMauBasicEntry OBJECT-TYPE");
            slist_push_front(pt_slist, "BroadMauBasicEntry ::=");
            _print_slist_src(pt_slist);
            slist_erase(pt_slist, slist_begin(pt_slist));
            _print_slist_src(pt_slist);
            slist_erase(pt_slist, slist_previous(pt_slist, slist_end(pt_slist)));
            _print_slist_src(pt_slist);
            slist_erase(pt_slist, iterator_next(slist_begin(pt_slist)));
            _print_slist_src(pt_slist);
            slist_destroy(pt_slist);
        }
        /*slist_erase_range       */
        {
            slist_t* pt_slist = create_slist(char*);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_erase_range(pt_slist, slist_begin(pt_slist), slist_end(pt_slist));
            _print_slist_src(pt_slist);
            slist_push_front(pt_slist, "SYNTAX    SEQUENCE OF BroadMauBasicEntry");
            slist_push_front(pt_slist, "ACCESS    not-accessible");
            slist_push_front(pt_slist, "STATUS    mandatory");
            slist_push_front(pt_slist, "DESCRIPTION");
            slist_push_front(pt_slist, "Table of descriptive and status information about");
            slist_push_front(pt_slist, "the broadband MAUs connected to interfaces.");
            slist_push_front(pt_slist, "{ dot3BroadMauBasicGroup 1 }");
            slist_push_front(pt_slist, "broadMauBasicEntry OBJECT-TYPE");
            slist_push_front(pt_slist, "BroadMauBasicEntry ::=");
            _print_slist_src(pt_slist);
            slist_erase_range(pt_slist, slist_begin(pt_slist), slist_begin(pt_slist));
            _print_slist_src(pt_slist);
            slist_erase_range(pt_slist, slist_begin(pt_slist), iterator_advance(slist_begin(pt_slist), 2));
            _print_slist_src(pt_slist);
            slist_erase_range(pt_slist, iterator_next(slist_begin(pt_slist)), iterator_advance(slist_begin(pt_slist), 3));
            _print_slist_src(pt_slist);
            slist_erase_range(pt_slist, iterator_advance(slist_begin(pt_slist), 3), slist_end(pt_slist));
            _print_slist_src(pt_slist);
            slist_erase_range(pt_slist, slist_end(pt_slist), slist_end(pt_slist));
            _print_slist_src(pt_slist);
            slist_erase_range(pt_slist, slist_begin(pt_slist), slist_end(pt_slist));
            _print_slist_src(pt_slist);
            
            slist_destroy(pt_slist);
        }
        /*slist_erase_after       */
        {
            slist_t* pt_slist = create_slist(char*);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_push_front(pt_slist, "SYNTAX    SEQUENCE OF BroadMauBasicEntry");
            slist_push_front(pt_slist, "ACCESS    not-accessible");
            slist_push_front(pt_slist, "STATUS    mandatory");
            slist_push_front(pt_slist, "DESCRIPTION");
            slist_push_front(pt_slist, "Table of descriptive and status information about");
            slist_push_front(pt_slist, "the broadband MAUs connected to interfaces.");
            slist_push_front(pt_slist, "{ dot3BroadMauBasicGroup 1 }");
            slist_push_front(pt_slist, "broadMauBasicEntry OBJECT-TYPE");
            slist_push_front(pt_slist, "BroadMauBasicEntry ::=");
            _print_slist_src(pt_slist);
            slist_erase_after(pt_slist, slist_begin(pt_slist));
            _print_slist_src(pt_slist);
            slist_erase_after(pt_slist, iterator_next(slist_begin(pt_slist)));
            _print_slist_src(pt_slist);
            slist_erase_after(pt_slist, iterator_advance(slist_begin(pt_slist), 5));
            _print_slist_src(pt_slist);
            slist_destroy(pt_slist);
        }
        /*slist_erase_after_range */
        {
            slist_t* pt_slist = create_slist(char*);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_erase_after_range(pt_slist, slist_begin(pt_slist), slist_end(pt_slist));
            _print_slist_src(pt_slist);
            slist_push_front(pt_slist, "SYNTAX    SEQUENCE OF BroadMauBasicEntry");
            slist_push_front(pt_slist, "ACCESS    not-accessible");
            slist_push_front(pt_slist, "STATUS    mandatory");
            slist_push_front(pt_slist, "DESCRIPTION");
            slist_push_front(pt_slist, "Table of descriptive and status information about");
            slist_push_front(pt_slist, "the broadband MAUs connected to interfaces.");
            slist_push_front(pt_slist, "{ dot3BroadMauBasicGroup 1 }");
            slist_push_front(pt_slist, "broadMauBasicEntry OBJECT-TYPE");
            slist_push_front(pt_slist, "BroadMauBasicEntry ::=");
            slist_push_front(pt_slist, "CCITT protocols (eg X.25)");
            slist_push_front(pt_slist, "NSC Hyperchannel address type");
            slist_push_front(pt_slist, "No address specified");
            slist_push_front(pt_slist, "X25");
            slist_push_front(pt_slist, "OSI TP4 address type");
            slist_push_front(pt_slist, "Parameters");
            slist_push_front(pt_slist, "GSS_S_COMPLETE");
            slist_push_front(pt_slist, "GSS_S_NO_CRED     Credentials could not be accessed.");
            slist_push_front(pt_slist, "#define GSS_S_CONTINUE_NEEDED (1ul << (GSS_C_SUPPLEMENTARY_OFFSET + 0))");
            slist_push_front(pt_slist, "#define GSS_S_OLD_TOKEN (1ul << (GSS_C_SUPPLEMENTARY_OFFSET + 2))");
            _print_slist_src(pt_slist);
            slist_erase_after_range(pt_slist, slist_begin(pt_slist), slist_begin(pt_slist));
            _print_slist_src(pt_slist);
            slist_erase_after_range(pt_slist, slist_begin(pt_slist), iterator_next(slist_begin(pt_slist)));
            _print_slist_src(pt_slist);
            slist_erase_after_range(pt_slist, slist_begin(pt_slist), iterator_advance(slist_begin(pt_slist), 3));
            _print_slist_src(pt_slist);
            slist_erase_after_range(pt_slist, iterator_next(slist_begin(pt_slist)), iterator_advance(slist_begin(pt_slist), 3));
            _print_slist_src(pt_slist);
            slist_erase_after_range(pt_slist, iterator_advance(slist_begin(pt_slist), 8), slist_end(pt_slist));
            _print_slist_src(pt_slist);
            slist_erase_after_range(pt_slist, slist_end(pt_slist), slist_end(pt_slist));
            _print_slist_src(pt_slist);
            slist_erase_after_range(pt_slist, slist_begin(pt_slist), slist_end(pt_slist));
            _print_slist_src(pt_slist);
            
            slist_destroy(pt_slist);
        }
        /*slist_splice            */
        {
            slist_t* pt_slist = create_slist(char*);
            slist_t* pt_slistex = create_slist(char*);
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            slist_splice(pt_slist, slist_begin(pt_slist), pt_slistex);
            _print_slist_src(pt_slist);
            slist_assign_elem(pt_slistex, 3, "1. Should we try to build integrated documentation/computation systems?");
            slist_splice(pt_slist, slist_begin(pt_slist), pt_slistex);
            _print_slist_src(pt_slist);
            slist_assign_elem(pt_slistex, 2, "");
            slist_splice(pt_slist, slist_begin(pt_slist), pt_slistex);
            _print_slist_src(pt_slist);
            slist_assign_elem(pt_slistex, 4, "2. WYSIWYG editing of mathematical expressions.");
            slist_splice(pt_slist, slist_end(pt_slist), pt_slistex);
            _print_slist_src(pt_slist);
            slist_assign_elem(pt_slistex, 3, "3. Interchange representation of mathematics.");
            slist_splice(pt_slist, iterator_next(slist_begin(pt_slist)), pt_slistex);
            _print_slist_src(pt_slist);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_splice_pos        */
        {
            slist_t* pt_slist = create_slist(char*);
            slist_t* pt_slistex = create_slist(char*);
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            slist_push_front(pt_slistex,
                "10.\"Presentation and Interchange of Mathematical Expressions in the Andrew System\",Maria Wadlow, Carnegie-Mellon University.");
            slist_push_front(pt_slistex,
                "9.\"Internal and External Representations of Valid Mathematical Reasoning\", Tryg Ager, Stanford University.");
            slist_push_front(pt_slistex,
                "8.\"Domain-Driven Expression Display in Scratchpad II\", Stephen Watt, IBM Yorktown Heights.");
            slist_push_front(pt_slistex,
                "7.\"CaminoReal: A Direct Manipulation Style User Interface for Mathematical Software\", Dennis Arnon, Xerox PARC.");
            slist_push_front(pt_slistex,
                "6.\"Iris User Interface for Computer Algebra Systemsi\", Benton Leong, University of Waterloo.");
            slist_push_front(pt_slistex,
                "5.\"INFOR: an Interactive WYSIWYG System for Technical Text\", William Schelter, University of Texas.");
            slist_push_front(pt_slistex,
                "4.\"MathScribe: A User Interface for Computer Algebra systems\", Neil Soiffer, Tektronix Labs.");
            slist_push_front(pt_slistex,
                "3.\"Milo: A Macintosh System for Students\", Ron Avitzur, Free Lance Developer, Palo Alto, CA.");
            slist_push_front(pt_slistex,
                "2.\"MATLAB - an Interactive Matrix Laboratory\", Cleve Moler, MathWorks Inc.");
            slist_push_front(pt_slistex,
                "1.\"The MathCad System: a Graphical Interface for Computer Mathematics\", Richard Smaby, MathSOFT Inc.");
            _print_slist_src(pt_slist);
            _print_slist_src(pt_slistex);
            slist_splice_pos(pt_slist, slist_begin(pt_slist), pt_slistex, slist_begin(pt_slistex));
            _print_slist_src(pt_slist);
            _print_slist_src(pt_slistex);
            slist_splice_pos(pt_slist, slist_begin(pt_slist), pt_slistex, slist_begin(pt_slistex));
            _print_slist_src(pt_slist);
            _print_slist_src(pt_slistex);
            slist_splice_pos(pt_slist, iterator_next(slist_begin(pt_slist)), pt_slistex, iterator_next(slist_begin(pt_slistex)));
            _print_slist_src(pt_slist);
            _print_slist_src(pt_slistex);
            slist_splice_pos(pt_slist, slist_end(pt_slist), pt_slistex, slist_previous(pt_slistex, slist_end(pt_slistex)));
            _print_slist_src(pt_slist);
            _print_slist_src(pt_slistex);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_splice_range      */
        {
            slist_t* pt_slist = create_slist(char*);
            slist_t* pt_slistex = create_slist(char*);
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            slist_splice_range(pt_slist, slist_begin(pt_slist), pt_slistex, slist_begin(pt_slistex), slist_end(pt_slistex));
            _print_slist_src(pt_slist);
            _print_slist_src(pt_slistex);
            slist_push_front(pt_slistex,
                "10.\"Presentation and Interchange of Mathematical Expressions in the Andrew System\",Maria Wadlow, Carnegie-Mellon University.");
            slist_push_front(pt_slistex,
                "9.\"Internal and External Representations of Valid Mathematical Reasoning\", Tryg Ager, Stanford University.");
            slist_push_front(pt_slistex,
                "8.\"Domain-Driven Expression Display in Scratchpad II\", Stephen Watt, IBM Yorktown Heights.");
            slist_push_front(pt_slistex,
                "7.\"CaminoReal: A Direct Manipulation Style User Interface for Mathematical Software\", Dennis Arnon, Xerox PARC.");
            slist_push_front(pt_slistex,
                "6.\"Iris User Interface for Computer Algebra Systemsi\", Benton Leong, University of Waterloo.");
            slist_push_front(pt_slistex,
                "5.\"INFOR: an Interactive WYSIWYG System for Technical Text\", William Schelter, University of Texas.");
            slist_push_front(pt_slistex,
                "4.\"MathScribe: A User Interface for Computer Algebra systems\", Neil Soiffer, Tektronix Labs.");
            slist_push_front(pt_slistex,
                "3.\"Milo: A Macintosh System for Students\", Ron Avitzur, Free Lance Developer, Palo Alto, CA.");
            slist_push_front(pt_slistex,
                "2.\"MATLAB - an Interactive Matrix Laboratory\", Cleve Moler, MathWorks Inc.");
            slist_push_front(pt_slistex,
                "1.\"The MathCad System: a Graphical Interface for Computer Mathematics\", Richard Smaby, MathSOFT Inc.");
            slist_splice_range(pt_slist, slist_begin(pt_slist), pt_slistex, slist_begin(pt_slistex), slist_begin(pt_slistex));
            _print_slist_src(pt_slist);
            _print_slist_src(pt_slistex);
            slist_splice_range(pt_slist, slist_begin(pt_slist),
                pt_slistex, slist_begin(pt_slistex), iterator_advance(slist_begin(pt_slistex), 3));
            _print_slist_src(pt_slist);
            _print_slist_src(pt_slistex);
            slist_splice_range(pt_slist, slist_begin(pt_slist),
                pt_slistex, iterator_next(slist_begin(pt_slistex)), iterator_advance(slist_begin(pt_slistex), 3));
            _print_slist_src(pt_slist);
            _print_slist_src(pt_slistex);
            slist_splice_range(pt_slist, iterator_next(slist_begin(pt_slist)),
                pt_slistex, iterator_advance(slist_begin(pt_slistex), 3), slist_end(pt_slistex));
            _print_slist_src(pt_slist);
            _print_slist_src(pt_slistex);
            slist_splice_range(pt_slist, slist_end(pt_slist), pt_slistex, slist_end(pt_slistex), slist_end(pt_slistex));
            _print_slist_src(pt_slist);
            _print_slist_src(pt_slistex);
            slist_splice_range(pt_slist, slist_end(pt_slist), pt_slistex, slist_begin(pt_slistex), slist_end(pt_slistex));
            _print_slist_src(pt_slist);
            _print_slist_src(pt_slistex);

            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_splice_after_pos  */
        {
            slist_t* pt_slist = create_slist(char*);
            slist_t* pt_slistex = create_slist(char*);
            if(pt_slist == NULL || pt_slist == NULL)
            {
                return;
            }
            slist_init_n(pt_slist, 3);
            slist_init(pt_slistex);
            slist_push_front(pt_slistex,
                "10.\"Presentation and Interchange of Mathematical Expressions in the Andrew System\",Maria Wadlow, Carnegie-Mellon University.");
            slist_push_front(pt_slistex,
                "9.\"Internal and External Representations of Valid Mathematical Reasoning\", Tryg Ager, Stanford University.");
            slist_push_front(pt_slistex,
                "8.\"Domain-Driven Expression Display in Scratchpad II\", Stephen Watt, IBM Yorktown Heights.");
            slist_push_front(pt_slistex,
                "7.\"CaminoReal: A Direct Manipulation Style User Interface for Mathematical Software\", Dennis Arnon, Xerox PARC.");
            slist_push_front(pt_slistex,
                "6.\"Iris User Interface for Computer Algebra Systemsi\", Benton Leong, University of Waterloo.");
            slist_push_front(pt_slistex,
                "5.\"INFOR: an Interactive WYSIWYG System for Technical Text\", William Schelter, University of Texas.");
            slist_push_front(pt_slistex,
                "4.\"MathScribe: A User Interface for Computer Algebra systems\", Neil Soiffer, Tektronix Labs.");
            slist_push_front(pt_slistex,
                "3.\"Milo: A Macintosh System for Students\", Ron Avitzur, Free Lance Developer, Palo Alto, CA.");
            slist_push_front(pt_slistex,
                "2.\"MATLAB - an Interactive Matrix Laboratory\", Cleve Moler, MathWorks Inc.");
            slist_push_front(pt_slistex,
                "1.\"The MathCad System: a Graphical Interface for Computer Mathematics\", Richard Smaby, MathSOFT Inc.");
            slist_splice_after_pos(pt_slist, slist_begin(pt_slist), pt_slistex, slist_begin(pt_slistex));
            _print_slist_src(pt_slist);
            _print_slist_src(pt_slistex);
            slist_splice_after_pos(pt_slist, slist_begin(pt_slist), pt_slistex, slist_begin(pt_slistex));
            _print_slist_src(pt_slist);
            _print_slist_src(pt_slistex);
            slist_splice_after_pos(pt_slist, iterator_next(slist_begin(pt_slist)), pt_slistex, iterator_next(slist_begin(pt_slistex)));
            _print_slist_src(pt_slist);
            _print_slist_src(pt_slistex);
            slist_splice_after_pos(pt_slist, slist_previous(pt_slist, slist_end(pt_slist)),
                pt_slistex, slist_previous(pt_slistex, slist_previous(pt_slistex, slist_end(pt_slistex))));
            _print_slist_src(pt_slist);
            _print_slist_src(pt_slistex);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_splice_after_range*/
        {
            slist_t* pt_slist = create_slist(char*);
            slist_t* pt_slistex = create_slist(char*);
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init_n(pt_slist, 3);
            slist_init(pt_slistex);
            /*slist_splice_after_range(pt_slist, slist_begin(pt_slist), pt_slistex, slist_begin(pt_slistex), slist_end(pt_slistex));*/
            /*_print_slist_src(pt_slist);*/
            /*_print_slist_src(pt_slistex);*/
            slist_push_front(pt_slistex,
                "10.\"Presentation and Interchange of Mathematical Expressions in the Andrew System\",Maria Wadlow, Carnegie-Mellon University.");
            slist_push_front(pt_slistex,
                "9.\"Internal and External Representations of Valid Mathematical Reasoning\", Tryg Ager, Stanford University.");
            slist_push_front(pt_slistex,
                "8.\"Domain-Driven Expression Display in Scratchpad II\", Stephen Watt, IBM Yorktown Heights.");
            slist_push_front(pt_slistex,
                "7.\"CaminoReal: A Direct Manipulation Style User Interface for Mathematical Software\", Dennis Arnon, Xerox PARC.");
            slist_push_front(pt_slistex,
                "6.\"Iris User Interface for Computer Algebra Systemsi\", Benton Leong, University of Waterloo.");
            slist_push_front(pt_slistex,
                "5.\"INFOR: an Interactive WYSIWYG System for Technical Text\", William Schelter, University of Texas.");
            slist_push_front(pt_slistex,
                "4.\"MathScribe: A User Interface for Computer Algebra systems\", Neil Soiffer, Tektronix Labs.");
            slist_push_front(pt_slistex,
                "3.\"Milo: A Macintosh System for Students\", Ron Avitzur, Free Lance Developer, Palo Alto, CA.");
            slist_push_front(pt_slistex,
                "2.\"MATLAB - an Interactive Matrix Laboratory\", Cleve Moler, MathWorks Inc.");
            slist_push_front(pt_slistex,
                "1.\"The MathCad System: a Graphical Interface for Computer Mathematics\", Richard Smaby, MathSOFT Inc.");
            slist_splice_after_range(pt_slist, slist_begin(pt_slist), pt_slistex, slist_begin(pt_slistex), slist_begin(pt_slistex));
            _print_slist_src(pt_slist);
            _print_slist_src(pt_slistex);
            slist_splice_after_range(pt_slist, slist_begin(pt_slist),
                pt_slistex, slist_begin(pt_slistex), iterator_next(slist_begin(pt_slistex)));
            _print_slist_src(pt_slist);
            _print_slist_src(pt_slistex);
            slist_splice_after_range(pt_slist, slist_begin(pt_slist),
                pt_slistex, slist_begin(pt_slistex), iterator_advance(slist_begin(pt_slistex), 3));
            _print_slist_src(pt_slist);
            _print_slist_src(pt_slistex);
            slist_splice_after_range(pt_slist, iterator_next(slist_begin(pt_slist)),
                pt_slistex, iterator_next(slist_begin(pt_slistex)), iterator_advance(slist_begin(pt_slistex), 3));
            _print_slist_src(pt_slist);
            _print_slist_src(pt_slistex);
            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_remove            */
        {
            slist_t* pt_slist = create_slist(char*);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_remove(pt_slist, "NetworkAddress");
            _print_slist_src(pt_slist);
            slist_push_front(pt_slist, "NetworkAddress");
            slist_push_front(pt_slist, "application-wide");
            slist_push_front(pt_slist, "original");
            slist_push_front(pt_slist, "ASN.1 EXTERNAL");
            slist_push_front(pt_slist, "NetworkAddress");
            slist_push_front(pt_slist, "IpAddress");
            _print_slist_src(pt_slist);
            slist_remove(pt_slist, "NetworkAddress");
            _print_slist_src(pt_slist);
            slist_remove(pt_slist, "ipaddress");
            _print_slist_src(pt_slist);
            slist_destroy(pt_slist);
        }
        /*slist_remove_if         */
        {
            slist_t* pt_slist = create_slist(char*);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_remove_if(pt_slist, _slist_str_remove_pre);
            _print_slist_src(pt_slist);
            slist_push_front(pt_slist, "NetworkAddress");
            slist_push_front(pt_slist, "application-wide");
            slist_push_front(pt_slist, "original");
            slist_push_front(pt_slist, "ASN.1 EXTERNAL");
            slist_push_front(pt_slist, "NetworkAddress");
            slist_push_front(pt_slist, "");
            slist_push_front(pt_slist, "IpAddress");
            slist_push_front(pt_slist, "represents");
            slist_push_front(pt_slist, "");
            slist_push_front(pt_slist, "monotonically");
            slist_push_front(pt_slist, "4294967295");
            _print_slist_src(pt_slist);
            slist_remove_if(pt_slist, _slist_str_remove_pre);
            _print_slist_src(pt_slist);
            slist_remove_if(pt_slist, _slist_str_remove_pre);
            _print_slist_src(pt_slist);
            slist_destroy(pt_slist);
        }
        /*slist_unique            */
        {
            slist_t* pt_slist = create_slist(char*);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_unique(pt_slist);
            _print_slist_src(pt_slist);
            slist_push_front(pt_slist, "NetworkAddress");
            slist_push_front(pt_slist, "application-wide");
            slist_push_front(pt_slist, "original");
            slist_push_front(pt_slist, "original");
            slist_push_front(pt_slist, "ASN.1 EXTERNAL");
            slist_push_front(pt_slist, "original");
            slist_push_front(pt_slist, "NetworkAddress");
            slist_push_front(pt_slist, "");
            slist_push_front(pt_slist, "IpAddress");
            slist_push_front(pt_slist, "represents");
            slist_push_front(pt_slist, "represents");
            slist_push_front(pt_slist, "");
            slist_push_front(pt_slist, "monotonically");
            slist_push_front(pt_slist, "4294967295");
            _print_slist_src(pt_slist);
            slist_unique(pt_slist);
            _print_slist_src(pt_slist);
            slist_unique(pt_slist);
            _print_slist_src(pt_slist);
            slist_destroy(pt_slist);
        }
        /*slist_unique_if         */
        {
            slist_t* pt_slist = create_slist(char*);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_unique_if(pt_slist, _slist_str_unique_pre);
            _print_slist_src(pt_slist);
            slist_push_front(pt_slist, "NetworkAddress");
            slist_push_front(pt_slist, "IpAddress");
            slist_push_front(pt_slist, "application-wide");
            slist_push_front(pt_slist, "original");
            slist_push_front(pt_slist, "represents");
            slist_push_front(pt_slist, "original");
            slist_push_front(pt_slist, "ASN.1 EXTERNAL");
            slist_push_front(pt_slist, "IpAddress");
            slist_push_front(pt_slist, "original");
            slist_push_front(pt_slist, "NetworkAddress");
            slist_push_front(pt_slist, "");
            slist_push_front(pt_slist, "IpAddress");
            slist_push_front(pt_slist, "represents");
            slist_push_front(pt_slist, "represents");
            slist_push_front(pt_slist, "represents");
            slist_push_front(pt_slist, "");
            slist_push_front(pt_slist, "monotonically");
            slist_push_front(pt_slist, "4294967295");
            _print_slist_src(pt_slist);
            slist_unique_if(pt_slist, _slist_str_unique_pre);
            _print_slist_src(pt_slist);
            slist_unique_if(pt_slist, _slist_str_unique_pre);
            _print_slist_src(pt_slist);
            slist_destroy(pt_slist);
        }
        /*slist_reverse           */
        {
            slist_t* pt_slist = create_slist(char*);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_reverse(pt_slist);
            _print_slist_src(pt_slist);
            slist_push_front(pt_slist,
                "10.\"Presentation and Interchange of Mathematical Expressions in the Andrew System\",Maria Wadlow, Carnegie-Mellon University.");
            slist_push_front(pt_slist,
                "9.\"Internal and External Representations of Valid Mathematical Reasoning\", Tryg Ager, Stanford University.");
            slist_push_front(pt_slist,
                "8.\"Domain-Driven Expression Display in Scratchpad II\", Stephen Watt, IBM Yorktown Heights.");
            slist_push_front(pt_slist,
                "7.\"CaminoReal: A Direct Manipulation Style User Interface for Mathematical Software\", Dennis Arnon, Xerox PARC.");
            slist_push_front(pt_slist,
                "6.\"Iris User Interface for Computer Algebra Systemsi\", Benton Leong, University of Waterloo.");
            slist_push_front(pt_slist,
                "5.\"INFOR: an Interactive WYSIWYG System for Technical Text\", William Schelter, University of Texas.");
            slist_push_front(pt_slist,
                "4.\"MathScribe: A User Interface for Computer Algebra systems\", Neil Soiffer, Tektronix Labs.");
            slist_push_front(pt_slist,
                "3.\"Milo: A Macintosh System for Students\", Ron Avitzur, Free Lance Developer, Palo Alto, CA.");
            slist_push_front(pt_slist,
                "2.\"MATLAB - an Interactive Matrix Laboratory\", Cleve Moler, MathWorks Inc.");
            slist_push_front(pt_slist,
                "1.\"The MathCad System: a Graphical Interface for Computer Mathematics\", Richard Smaby, MathSOFT Inc.");
            _print_slist_src(pt_slist);
            slist_reverse(pt_slist);
            _print_slist_src(pt_slist);

            slist_destroy(pt_slist);
        }
        /*slist_sort              */
        {
            slist_t* pt_slist = create_slist(char*);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_sort(pt_slist);
            _print_slist_src(pt_slist);
            slist_push_front(pt_slist, "NetworkAddress");
            slist_push_front(pt_slist, "IpAddress");
            slist_push_front(pt_slist, "application-wide");
            slist_push_front(pt_slist, "original");
            slist_push_front(pt_slist, "represents");
            slist_push_front(pt_slist, "original");
            slist_push_front(pt_slist, "ASN.1 EXTERNAL");
            slist_push_front(pt_slist, "IpAddress");
            slist_push_front(pt_slist, "original");
            slist_push_front(pt_slist, "NetworkAddress");
            slist_push_front(pt_slist, "");
            slist_push_front(pt_slist, "IpAddress");
            slist_push_front(pt_slist, "represents");
            slist_push_front(pt_slist, "represents");
            slist_push_front(pt_slist, "represents");
            slist_push_front(pt_slist, "");
            slist_push_front(pt_slist, "monotonically");
            slist_push_front(pt_slist, "4294967295");
            _print_slist_src(pt_slist);
            slist_sort(pt_slist);
            _print_slist_src(pt_slist);
            slist_destroy(pt_slist);
        }
        /*slist_sort_if           */
        {
            slist_t* pt_slist = create_slist(char*);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_sort_if(pt_slist, _slist_str_sort_pre);
            _print_slist_src(pt_slist);
            slist_push_front(pt_slist, "NetworkAddress");
            slist_push_front(pt_slist, "IpAddress");
            slist_push_front(pt_slist, "application-wide");
            slist_push_front(pt_slist, "original");
            slist_push_front(pt_slist, "represents");
            slist_push_front(pt_slist, "original");
            slist_push_front(pt_slist, "ASN.1 EXTERNAL");
            slist_push_front(pt_slist, "IpAddress");
            slist_push_front(pt_slist, "original");
            slist_push_front(pt_slist, "NetworkAddress");
            slist_push_front(pt_slist, "");
            slist_push_front(pt_slist, "IpAddress");
            slist_push_front(pt_slist, "represents");
            slist_push_front(pt_slist, "represents");
            slist_push_front(pt_slist, "represents");
            slist_push_front(pt_slist, "");
            slist_push_front(pt_slist, "monotonically");
            slist_push_front(pt_slist, "4294967295");
            _print_slist_src(pt_slist);
            slist_sort_if(pt_slist, _slist_str_sort_pre);
            _print_slist_src(pt_slist);
            slist_destroy(pt_slist);
        }
        /*slist_merge             */
        {
            slist_t* pt_slist = create_slist(char*);
            slist_t* pt_slistex = create_slist(char*);
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            slist_merge(pt_slist, pt_slistex);
            _print_slist_src(pt_slist);
            _print_slist_src(pt_slistex);
            slist_push_front(pt_slist, "NetworkAddress");
            slist_push_front(pt_slist, "IpAddress");
            slist_push_front(pt_slist, "application-wide");
            slist_push_front(pt_slist, "original");
            slist_push_front(pt_slist, "represents");
            slist_push_front(pt_slist, "original");
            slist_push_front(pt_slist, "ASN.1 EXTERNAL");
            slist_sort(pt_slist);
            slist_merge(pt_slist, pt_slistex);
            _print_slist_src(pt_slist);
            _print_slist_src(pt_slistex);

            slist_clear(pt_slist);
            slist_push_front(pt_slistex, "IpAddress");
            slist_push_front(pt_slistex, "original");
            slist_push_front(pt_slistex, "NetworkAddress");
            slist_push_front(pt_slistex, "");
            slist_push_front(pt_slistex, "IpAddress");
            slist_push_front(pt_slistex, "represents");
            slist_push_front(pt_slistex, "represents");
            slist_push_front(pt_slistex, "represents");
            slist_push_front(pt_slistex, "");
            slist_push_front(pt_slistex, "monotonically");
            slist_push_front(pt_slistex, "4294967295");
            slist_sort(pt_slistex);
            slist_merge(pt_slist, pt_slistex);
            _print_slist_src(pt_slist);
            _print_slist_src(pt_slistex);

            slist_clear(pt_slist);
            slist_clear(pt_slistex);
            slist_push_front(pt_slistex, "IpAddress");
            slist_push_front(pt_slistex, "original");
            slist_push_front(pt_slistex, "NetworkAddress");
            slist_push_front(pt_slistex, "");
            slist_push_front(pt_slistex, "IpAddress");
            slist_push_front(pt_slistex, "represents");
            slist_push_front(pt_slistex, "represents");
            slist_push_front(pt_slistex, "represents");
            slist_push_front(pt_slistex, "");
            slist_push_front(pt_slistex, "monotonically");
            slist_push_front(pt_slistex, "4294967295");
            slist_push_front(pt_slist, "NetworkAddress");
            slist_push_front(pt_slist, "IpAddress");
            slist_push_front(pt_slist, "application-wide");
            slist_push_front(pt_slist, "original");
            slist_push_front(pt_slist, "represents");
            slist_push_front(pt_slist, "original");
            slist_push_front(pt_slist, "ASN.1 EXTERNAL");
            slist_sort(pt_slist);
            slist_sort(pt_slistex);
            slist_merge(pt_slist, pt_slistex);
            _print_slist_src(pt_slist);
            _print_slist_src(pt_slistex);

            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_merge_if          */
        {
            slist_t* pt_slist = create_slist(char*);
            slist_t* pt_slistex = create_slist(char*);
            if(pt_slist == NULL || pt_slistex == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_init(pt_slistex);
            slist_merge_if(pt_slist, pt_slistex, _slist_str_sort_pre);
            _print_slist_src(pt_slist);
            _print_slist_src(pt_slistex);
            slist_push_front(pt_slist, "NetworkAddress");
            slist_push_front(pt_slist, "IpAddress");
            slist_push_front(pt_slist, "application-wide");
            slist_push_front(pt_slist, "original");
            slist_push_front(pt_slist, "represents");
            slist_push_front(pt_slist, "original");
            slist_push_front(pt_slist, "ASN.1 EXTERNAL");
            slist_sort_if(pt_slist, _slist_str_sort_pre);
            slist_merge_if(pt_slist, pt_slistex, _slist_str_sort_pre);
            _print_slist_src(pt_slist);
            _print_slist_src(pt_slistex);

            slist_clear(pt_slist);
            slist_push_front(pt_slistex, "IpAddress");
            slist_push_front(pt_slistex, "original");
            slist_push_front(pt_slistex, "NetworkAddress");
            slist_push_front(pt_slistex, "");
            slist_push_front(pt_slistex, "IpAddress");
            slist_push_front(pt_slistex, "represents");
            slist_push_front(pt_slistex, "represents");
            slist_push_front(pt_slistex, "represents");
            slist_push_front(pt_slistex, "");
            slist_push_front(pt_slistex, "monotonically");
            slist_push_front(pt_slistex, "4294967295");
            slist_sort_if(pt_slistex, _slist_str_sort_pre);
            slist_merge_if(pt_slist, pt_slistex, _slist_str_sort_pre);
            _print_slist_src(pt_slist);
            _print_slist_src(pt_slistex);

            slist_clear(pt_slist);
            slist_clear(pt_slistex);
            slist_push_front(pt_slistex, "IpAddress");
            slist_push_front(pt_slistex, "original");
            slist_push_front(pt_slistex, "NetworkAddress");
            slist_push_front(pt_slistex, "");
            slist_push_front(pt_slistex, "IpAddress");
            slist_push_front(pt_slistex, "represents");
            slist_push_front(pt_slistex, "represents");
            slist_push_front(pt_slistex, "represents");
            slist_push_front(pt_slistex, "");
            slist_push_front(pt_slistex, "monotonically");
            slist_push_front(pt_slistex, "4294967295");
            slist_push_front(pt_slist, "NetworkAddress");
            slist_push_front(pt_slist, "IpAddress");
            slist_push_front(pt_slist, "application-wide");
            slist_push_front(pt_slist, "original");
            slist_push_front(pt_slist, "represents");
            slist_push_front(pt_slist, "original");
            slist_push_front(pt_slist, "ASN.1 EXTERNAL");
            slist_sort_if(pt_slist, _slist_str_sort_pre);
            slist_sort_if(pt_slistex, _slist_str_sort_pre);
            slist_merge_if(pt_slist, pt_slistex, _slist_str_sort_pre);
            _print_slist_src(pt_slist);
            _print_slist_src(pt_slistex);

            slist_destroy(pt_slist);
            slist_destroy(pt_slistex);
        }
        /*slist_resize            */
        {
            slist_t* pt_slist = create_slist(char*);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_resize(pt_slist, 0);
            _print_slist_src(pt_slist);
            slist_resize(pt_slist, 5);
            _print_slist_src(pt_slist);
            slist_resize(pt_slist, 9);
            _print_slist_src(pt_slist);
            slist_resize(pt_slist, 3);
            _print_slist_src(pt_slist);
            slist_resize(pt_slist, 0);
            _print_slist_src(pt_slist);
            slist_destroy(pt_slist);
        }
        /*slist_resize_elem       */
        {
            slist_t* pt_slist = create_slist(char*);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_resize_elem(pt_slist, 0, "cpptest");
            _print_slist_src(pt_slist);
            slist_resize_elem(pt_slist, 4, "Phone: +1 313 764-2278");
            _print_slist_src(pt_slist);
            slist_resize_elem(pt_slist, 18, "EMail: mcs@umich.edu");
            _print_slist_src(pt_slist);
            slist_resize_elem(pt_slist, 7, "");
            _print_slist_src(pt_slist);
            slist_resize_elem(pt_slist, 0, "University of Michigan");
            _print_slist_src(pt_slist);
            slist_destroy(pt_slist);
        }
        /*slist_clear             */
        {
            slist_t* pt_slist = create_slist(char*);
            if(pt_slist == NULL)
            {
                return;
            }
            slist_init(pt_slist);
            slist_clear(pt_slist);
            _print_slist_src(pt_slist);
            slist_assign_elem(pt_slist, 100, "The second form will see to it that existing values (if any) are2.2.4.2 Modify Reply");
            _print_slist_src(pt_slist);
            slist_clear(pt_slist);
            _print_slist_src(pt_slist);
            slist_destroy(pt_slist);
        }
    }
}

/** local function implementation section **/
static void _slist_str_sort_pre(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    if(strncmp((char*)cpv_first, (char*)cpv_second, 100) > 0)
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}

static void _slist_str_unique_pre(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    if((isupper(((char*)cpv_first)[0]) && isupper(((char*)cpv_second)[0])) ||
       (islower(((char*)cpv_first)[0]) && islower(((char*)cpv_second)[0])))
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}

static void _slist_str_remove_pre(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    if(isupper(((char*)cpv_input)[0]) || strlen((char*)cpv_input) == 0)
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}

static void _print_slist_src(const slist_t* cpt_slist)
{
    iterator_t t_iter;
    assert(cpt_slist != NULL);
    printf("=============================================\n");
    printf("empty: %u, size: %u, max_size: %u\n",
        slist_empty(cpt_slist), slist_size(cpt_slist), slist_max_size(cpt_slist));
    for(t_iter = slist_begin(cpt_slist);
        !iterator_equal(t_iter, slist_end(cpt_slist));
        t_iter = iterator_next(t_iter))
    {
        puts(iterator_get_pointer(t_iter));
    }
}

static void _slist_sort_slist_pred(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    if(slist_size((slist_t*)cpv_first) < slist_size((slist_t*)cpv_second))
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}

static void _slist_unique_slist_pred(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    if(slist_front((slist_t*)cpv_first) != NULL && slist_front((slist_t*)cpv_second) &&
       *(int*)slist_front((slist_t*)cpv_first) % 2 ==
       *(int*)slist_front((slist_t*)cpv_second) % 2)
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}

static void _slist_remove_slist_pred(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    if(slist_size((slist_t*)cpv_input) == 5)
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}

static void _printslist(const slist_t* cpt_slist)
{
    iterator_t t_iterex;
    assert(cpt_slist != NULL);

    printf("+++++++++++++++++++++++++++++++++++++++++\n");
    for(t_iterex = slist_begin(cpt_slist);
        !iterator_equal(t_iterex, slist_end(cpt_slist));
        t_iterex = iterator_next(t_iterex))
    {
        _printslist_c(iterator_get_pointer(t_iterex), "%d, ", int);
    }
}

static void _slist_sort_coor_pred(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    if(((coordinates_t*)cpv_first)->x < ((coordinates_t*)cpv_second)->x)
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}

static void _slist_unique_coor_pred(
    const void* cpv_first, const void* cpv_second, void* pv_output)
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

static void _slist_remove_coor_pred2(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    if(((coordinates_t*)cpv_input)->x * 10 == ((coordinates_t*)cpv_input)->y &&
       ((coordinates_t*)cpv_input)->x * 100 == ((coordinates_t*)cpv_input)->z)
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}

static void _slist_remove_coor_pred1(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    if(((coordinates_t*)cpv_input)->x == ((coordinates_t*)cpv_input)->y &&
       ((coordinates_t*)cpv_input)->x == ((coordinates_t*)cpv_input)->z)
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}

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

