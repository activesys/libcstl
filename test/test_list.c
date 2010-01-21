/*
 *  The implementation of list test.
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
#include <time.h>
#include "clist.h"
#include "cfunctional.h"
#include "test_list.h"

/** local constant declaration and local macro section **/
#define _printlist_c(pt_list, fmt, type)\
    do{\
        iterator_t t_iter;\
        printf("==================================\n");\
        for(t_iter = list_begin(pt_list);\
            !iterator_equal(t_iter, list_end(pt_list));\
            t_iter = iterator_next(t_iter)){\
            printf(fmt, *(type*)iterator_get_pointer(t_iter));\
        }printf("\n");\
    }while(false)

/** local data type declaration and local struct, union, enum section **/
typedef enum _tagabcflag
{
    _ABC_FLAG_DESCARTES, _ABC_FLAG_COMPLEX
}abcflat_t;
typedef struct _taglistabc
{
    abcflat_t _t_flag;
    union{
        struct _tagdescartes
        {
            int _n_posx;
            int _n_posy;
        } _t_descartes;
        struct _tagcomplex
        {
            int _n_real;
            int _n_imaginary;
        } _t_complex;
    } _t_abc;
}listabc_t;

/** local function prototype section **/
static void _list_str_sort_pre(const void* cpv_first, const void* cpv_second, void* pv_output);
static void _list_str_unique_pre(const void* cpv_first, const void* cpv_second, void* pv_output);
static void _list_str_remove_pre(const void* cpv_input, void* pv_output);
static void _print_list_str(const list_t* cpt_list);

static void _remove_mutiple_of_5(const void* cpv_input, void* pv_output);
static void _absolute_value(const void* cpv_first, const void* cpv_second, void* pv_output);

static void _listabc_init(const void* cpv_input, void* pv_output);
static void _listabc_destory(const void* cpv_input, void* pv_output);
static void _listabc_copy(const void* cpv_first, const void* cpv_second, void* pv_output);
static void _listabc_less(const void* cpv_first, const void* cpv_second, void* pv_output);

static void _printlist_user(const list_t* cpt_list);
static void _remove_first_5(const void* cpv_input, void* pv_output);
static void _listabc_great(const void* cpv_first, const void* cpv_second, void* pv_output);

static void _printlist_list(const list_t* cpt_list);

static void _list_remove_pre(const void* cpv_input, void* pv_output);
static void _list_unique_pre(const void* cpv_first, const void* cpv_second, void* pv_output);
static void _list_sort_pre(const void* cpv_first, const void* cpv_second, void* pv_output);

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
void test_list(void)
{
    /* for c built-in type */
    {
        /*create_list         */
        /*list_init           */
        /*list_destroy        */
        {
            list_t* pt_list = create_list(int);
            if(pt_list == NULL)
            {
                return;
            }
            list_init(pt_list);
            list_destroy(pt_list);
        }
        /*list_init_n         */
        {
            list_t* pt_list = create_list(double);
            if(pt_list == NULL)
            {
                return;
            }
            list_init_n(pt_list, 5);
            _printlist_c(pt_list, "%lf, ", double);
            list_destroy(pt_list);
        }
        /*_list_init_elem     */
        {
            list_t* pt_list = create_list(long);
            if(pt_list == NULL)
            {
                return;
            }
            list_init_elem(pt_list, 1000, 2131415161);
            _printlist_c(pt_list, "%ld, ", long);
            list_destroy(pt_list);
        }
        /*list_init_copy      */
        {
            list_t* pt_list = create_list(short);
            list_t* pt_listex = create_list(signed short int);
            if(pt_list == NULL || pt_listex == NULL)
            {
                return;
            }
            list_init_elem(pt_listex, 18, -890);
            /*list_init(pt_listex);*/
            list_init_copy(pt_list, pt_listex);
            _printlist_c(pt_list, "%d, ", short);
            list_destroy(pt_list);
            list_destroy(pt_listex);
        }
        /*list_init_copy_range*/
        {
            list_t* pt_list = create_list(short);
            list_t* pt_listex = create_list(signed short);
            if(pt_list == NULL || pt_listex == NULL)
            {
                return;
            }
            list_init_elem(pt_listex, 18, -890);
            list_init_copy_range(pt_list,
                iterator_advance(list_end(pt_listex), -4), list_end(pt_listex));
            _printlist_c(pt_listex, "%d, ", short);
            _printlist_c(pt_list, "%d, ", short);
            list_destroy(pt_list);
            list_destroy(pt_listex);
        }
        /*list_size           */
        {
            list_t* pt_list = create_list(char);
            if(pt_list == NULL)
            {
                return;
            }
            list_init(pt_list);
            printf("size : %d, empty : %d, max_size : %u\n",
                list_size(pt_list), list_empty(pt_list), list_max_size(pt_list));
            list_push_back(pt_list, 'W');
            list_push_front(pt_list, 'B');
            printf("size : %d, empty : %d, max_size : %u\n",
                list_size(pt_list), list_empty(pt_list), list_max_size(pt_list));
            list_destroy(pt_list);
        }
        /*list_empty          */
        /*list_max_size       */
        /*list_equal          */
        {
            list_t* pt_list = create_list(double);
            list_t* pt_listex = create_list(double);
            if(pt_list == NULL)
            {
                return;
            }
            list_init(pt_list);
            list_init(pt_listex);
            list_push_back(pt_list, 45.3);
            list_push_back(pt_list, 444.44);
            list_push_back(pt_listex, 45.3);
            list_push_back(pt_listex, 444.44);
            _printlist_c(pt_list, "%lf, ", double);
            _printlist_c(pt_listex, "%lf, ", double);
            printf("equal : %d, not equal : %d\n",
                list_equal(pt_list, pt_listex), list_not_equal(pt_list, pt_listex));
            printf("less : %d, less equal : %d\n",
                list_less(pt_list, pt_listex), list_less_equal(pt_list, pt_listex));
            printf("great : %d, great equal : %d\n",
                list_great(pt_list, pt_listex), list_great_equal(pt_list, pt_listex));
            list_destroy(pt_list);
            list_destroy(pt_listex);
        }
        /*list_not_equal      */
        /*list_less           */
        /*list_less_equal     */
        /*list_great          */
        /*list_great_equal    */
        /*list_assign         */
        {
            list_t* pt_list = create_list(int);
            list_t* pt_listex = create_list(signed);
            if(pt_list == NULL || pt_listex == NULL)
            {
                return;
            }
            list_init(pt_list);
            list_init(pt_listex);
            list_assign(pt_list, pt_listex);
            _printlist_c(pt_list, "%d, ", int);
            _printlist_c(pt_listex, "%d, ", int);
            list_push_back(pt_listex, 56);
            list_push_back(pt_listex, -2343);
            list_push_back(pt_listex, -3);
            list_assign(pt_list, pt_listex);
            _printlist_c(pt_list, "%d, ", int);
            _printlist_c(pt_listex, "%d, ", int);
            list_clear(pt_listex);
            list_push_back(pt_listex, 1122);
            list_push_back(pt_listex, 0);
            list_push_back(pt_listex, -333);
            list_push_back(pt_listex, 235);
            list_push_back(pt_listex, -90);
            list_assign(pt_list, pt_listex);
            _printlist_c(pt_list, "%d, ", int);
            _printlist_c(pt_listex, "%d, ", int);
            list_clear(pt_listex);
            list_push_back(pt_listex, 56);
            list_push_back(pt_listex, 33);
            list_assign(pt_list, pt_listex);
            _printlist_c(pt_list, "%d, ", int);
            _printlist_c(pt_listex, "%d, ", int);
            list_clear(pt_listex);
            list_assign(pt_list, pt_listex);
            _printlist_c(pt_list, "%d, ", int);
            _printlist_c(pt_listex, "%d, ", int);
            list_destroy(pt_list);
            list_destroy(pt_listex);
        }
        /*_list_assign_elem   */
        {
            list_t* pt_list = create_list(long);
            if(pt_list == NULL)
            {
                return;
            }
            list_init(pt_list);
            list_assign_elem(pt_list, 15, -34);
            _printlist_c(pt_list, "%ld, ", long);
            list_assign_elem(pt_list, 43, 90);
            _printlist_c(pt_list, "%ld, ", long);
            list_assign_elem(pt_list, 3, -55);
            _printlist_c(pt_list, "%ld, ", long);
            list_assign_elem(pt_list, 0, 27);
            _printlist_c(pt_list, "%ld, ", long);
            list_destroy(pt_list);
        }
        /*list_assign_range   */
        {
            list_t* pt_list = create_list(long);
            list_t* pt_listex = create_list(signed long int);
            if(pt_list == NULL || pt_listex == NULL)
            {
                return;
            }
            list_init(pt_list);
            list_init(pt_listex);
            list_push_back(pt_listex, 90);
            list_push_back(pt_listex, 23);
            list_push_back(pt_listex, 222);
            list_push_back(pt_listex, -98);
            list_push_back(pt_listex, -222);
            list_push_back(pt_listex, 333);
            list_push_back(pt_listex, 22);
            list_push_back(pt_listex, 111);
            list_assign_range(pt_list, list_begin(pt_listex), list_begin(pt_listex));
            _printlist_c(pt_list, "%ld, ", long);
            _printlist_c(pt_listex, "%ld, ", long);
            list_assign_range(pt_list,
                list_begin(pt_listex), iterator_advance(list_begin(pt_listex), 3));
            _printlist_c(pt_list, "%ld, ", long);
            _printlist_c(pt_listex, "%ld, ", long);
            list_assign_range(pt_list,
                iterator_advance(list_begin(pt_listex), 2),
                iterator_advance(list_begin(pt_listex), 7));
            _printlist_c(pt_list, "%ld, ", long);
            _printlist_c(pt_listex, "%ld, ", long);
            list_assign_range(pt_list,
                iterator_advance(list_begin(pt_listex), 5), list_end(pt_listex));
            _printlist_c(pt_list, "%ld, ", long);
            _printlist_c(pt_listex, "%ld, ", long);
            list_assign_range(pt_list, list_end(pt_listex), list_end(pt_listex));
            _printlist_c(pt_list, "%ld, ", long);
            _printlist_c(pt_listex, "%ld, ", long);
            list_destroy(pt_list);
            list_destroy(pt_listex);
        }
        /*list_swap           */
        {
            list_t* pt_list = create_list(int);
            list_t* pt_listex = create_list(int);
            if(pt_list == NULL || pt_listex == NULL)
            {
                return;
            }
            list_init(pt_list);
            list_init(pt_listex);
            list_swap(pt_list, pt_listex);
            _printlist_c(pt_list, "%d, ", int);
            _printlist_c(pt_listex, "%d, ", int);
            list_push_back(pt_listex, 222);
            list_push_back(pt_listex, 90);
            list_push_back(pt_listex, 221);
            list_push_back(pt_listex, -33);
            list_swap(pt_list, pt_listex);
            _printlist_c(pt_list, "%d, ", int);
            _printlist_c(pt_listex, "%d, ", int);
            list_push_back(pt_listex, -111);
            list_push_back(pt_listex, -222);
            list_push_back(pt_listex, -333);
            list_push_back(pt_listex, -444);
            list_push_back(pt_listex, -555);
            list_push_back(pt_listex, -666);
            list_swap(pt_list, pt_listex);
            _printlist_c(pt_list, "%d, ", int);
            _printlist_c(pt_listex, "%d, ", int);
            list_clear(pt_listex);
            list_swap(pt_list, pt_listex);
            _printlist_c(pt_list, "%d, ", int);
            _printlist_c(pt_listex, "%d, ", int);
            list_destroy(pt_list);
            list_destroy(pt_listex);
        }
        /*list_front          */
        {
            list_t* pt_list = create_list(double);
            if(pt_list == NULL)
            {
                return;
            }
            list_init(pt_list);
            if(list_front(pt_list) != NULL)
            {
                printf("%lf\n", *(double*)list_front(pt_list));
            }
            if(list_back(pt_list) != NULL)
            {
                printf("%lf\n", *(double*)list_back(pt_list));
            }
            list_push_back(pt_list, 23.5);
            list_push_back(pt_list, -88.23);
            if(list_front(pt_list) != NULL)
            {
                printf("%lf\n", *(double*)list_front(pt_list));
            }
            if(list_back(pt_list) != NULL)
            {
                printf("%lf\n", *(double*)list_back(pt_list));
            }
            *(double*)list_front(pt_list) = 0.003;
            *(double*)list_back(pt_list) = 4.44;
            if(list_front(pt_list) != NULL)
            {
                printf("%lf\n", *(double*)list_front(pt_list));
            }
            if(list_back(pt_list) != NULL)
            {
                printf("%lf\n", *(double*)list_back(pt_list));
            }
            list_destroy(pt_list);
        }
        /*list_back           */
        /*list_begin          */
        /*list_end            */
        /*list_insert         */
        {
            list_t* pt_list = create_list(int);
            if(pt_list == NULL)
            {
                return;
            }
            list_init(pt_list);
            list_insert(pt_list, list_begin(pt_list), 200);
            _printlist_c(pt_list, "%d, ", int);
            list_insert(pt_list, list_end(pt_list), 500);
            _printlist_c(pt_list, "%d, ", int);
            list_insert(pt_list, list_begin(pt_list), -10);
            _printlist_c(pt_list, "%d, ", int);
            list_insert(pt_list, iterator_advance(list_begin(pt_list), 2), 560);
            _printlist_c(pt_list, "%d, ", int);
            list_destroy(pt_list);
        }
        /*list_insert_n       */
        {
            list_t* pt_list = create_list(int);
            if(pt_list == NULL)
            {
                return;
            }
            list_init(pt_list);
            list_insert_n(pt_list, list_begin(pt_list), 200, -20);
            _printlist_c(pt_list, "%d, ", int);
            list_insert_n(pt_list, list_end(pt_list), 50, -50);
            _printlist_c(pt_list, "%d, ", int);
            list_insert_n(pt_list, list_begin(pt_list), 10, -10);
            _printlist_c(pt_list, "%d, ", int);
            list_insert_n(pt_list, iterator_advance(list_begin(pt_list), 20), 56, -56);
            _printlist_c(pt_list, "%d, ", int);
            list_destroy(pt_list);
        }
        /*list_insert_range   */
        {
            list_t* pt_list = create_list(int);
            list_t* pt_listex = create_list(int);
            int i;
            if(pt_list == NULL || pt_listex == NULL)
            {
                return;
            }
            list_init(pt_list);
            list_init(pt_listex);
            for(i = 0; i < 100; ++i)
            {
                list_push_back(pt_listex, i * 100);
            }
            _printlist_c(pt_listex, "%d, ", int);
            list_insert_range(pt_list, list_begin(pt_list),
                list_begin(pt_listex), list_begin(pt_listex));
            _printlist_c(pt_list, "%d, ", int);
            list_insert_range(pt_list, list_begin(pt_list),
                list_begin(pt_listex), iterator_advance(list_begin(pt_listex), 5));
            _printlist_c(pt_list, "%d, ", int);
            list_insert_range(pt_list, iterator_advance(list_begin(pt_list), 4),
                iterator_advance(list_begin(pt_listex), 10),
                iterator_advance(list_begin(pt_listex), 20));
            _printlist_c(pt_list, "%d, ", int);
            list_insert_range(pt_list, iterator_advance(list_end(pt_list), -4),
                iterator_advance(list_end(pt_listex), -10),
                iterator_advance(list_end(pt_listex), -5));
            _printlist_c(pt_list, "%d, ", int);
            list_insert_range(pt_list, list_end(pt_list),
                iterator_advance(list_end(pt_listex), -20), list_end(pt_listex));
            _printlist_c(pt_list, "%d, ", int);
            list_insert_range(pt_list, list_end(pt_list), list_end(pt_listex), list_end(pt_listex));
            _printlist_c(pt_list, "%d, ", int);
            list_destroy(pt_list);
            list_destroy(pt_listex);
        }
        /*list_push_back      */
        {
            list_t* pt_list = create_list(int);
            int i;
            if(pt_list == NULL)
            {
                return;
            }
            list_init(pt_list);
            for(i = 0; i < 100; ++i)
            {
                list_push_back(pt_list, i);
            }
            _printlist_c(pt_list, "%d, ", int);
            while(!list_empty(pt_list))
            {
                list_pop_front(pt_list);
            }
            _printlist_c(pt_list, "%d, ", int);
            for(i = 0; i < 100; ++i)
            {
                list_push_front(pt_list, -i);
            }
            _printlist_c(pt_list, "%d, ", int);
            while(!list_empty(pt_list))
            {
                list_pop_back(pt_list);
            }
            _printlist_c(pt_list, "%d, ", int);
            list_destroy(pt_list);
        }
        /*list_pop_back       */
        /*list_push_front     */
        /*list_pop_front      */
        /*list_erase          */
        {
            list_t* pt_list = create_list(int);
            int i;
            if(pt_list == NULL)
            {
                return;
            }
            list_init(pt_list);
            for(i = 0; i < 100; ++i)
            {
                list_push_back(pt_list, i * 100);
            }
            _printlist_c(pt_list, "%d, ", int);
            list_erase(pt_list, list_begin(pt_list));
            _printlist_c(pt_list, "%d, ", int);
            list_erase(pt_list, iterator_prev(list_end(pt_list)));
            _printlist_c(pt_list, "%d, ", int);
            list_erase(pt_list, iterator_advance(list_begin(pt_list), 45));
            _printlist_c(pt_list, "%d, ", int);
            list_destroy(pt_list);
        }
        /*list_erase_range    */
        {
            list_t* pt_list = create_list(int);
            int i;
            if(pt_list == NULL)
            {
                return;
            }
            list_init(pt_list);
            for(i = 0; i < 100; ++i)
            {
                list_push_back(pt_list, i * 100);
            }
            _printlist_c(pt_list, "%d, ", int);
            list_erase_range(pt_list, list_begin(pt_list), list_begin(pt_list));
            _printlist_c(pt_list, "%d, ", int);
            list_erase_range(pt_list,
                list_begin(pt_list), iterator_advance(list_begin(pt_list), 10));
            _printlist_c(pt_list, "%d, ", int);
            list_erase_range(pt_list,
                iterator_advance(list_begin(pt_list), 40),
                iterator_advance(list_begin(pt_list), 50));
            _printlist_c(pt_list, "%d, ", int);
            list_erase_range(pt_list,
                iterator_advance(list_end(pt_list), -20),
                iterator_advance(list_end(pt_list), -10));
            _printlist_c(pt_list, "%d, ", int);
            list_erase_range(pt_list,
                iterator_advance(list_end(pt_list), -10), list_end(pt_list));
            _printlist_c(pt_list, "%d, ", int);
            list_erase_range(pt_list, list_end(pt_list), list_end(pt_list));
            _printlist_c(pt_list, "%d, ", int);
            list_destroy(pt_list);
        }
        /*list_remove         */
        {
            list_t* pt_list = create_list(int);
            if(pt_list == NULL)
            {
                return;
            }
            list_init(pt_list);
            list_push_back(pt_list, -23);
            list_push_back(pt_list, 1);
            list_push_back(pt_list, 90);
            list_push_back(pt_list, 45);
            list_push_back(pt_list, 1);
            list_push_back(pt_list, 1);
            list_push_back(pt_list, -3);
            list_push_back(pt_list, -45);
            list_push_back(pt_list, 22);
            _printlist_c(pt_list, "%d, ", int);
            list_remove(pt_list, 5);
            _printlist_c(pt_list, "%d, ", int);
            list_remove(pt_list, 45);
            _printlist_c(pt_list, "%d, ", int);
            list_remove(pt_list, 1);
            _printlist_c(pt_list, "%d, ", int);
            list_destroy(pt_list);
        }
        /*list_remove_if      */
        {
            list_t* pt_list = create_list(int);
            int i;
            if(pt_list == NULL)
            {
                return;
            }
            list_init(pt_list);
            for(i = 0; i < 100; ++i)
            {
                list_push_back(pt_list, i);
            }
            _printlist_c(pt_list, "%d, ", int);
            list_remove_if(pt_list, _remove_mutiple_of_5);
            _printlist_c(pt_list, "%d, ", int);
            list_remove_if(pt_list, _remove_mutiple_of_5);
            _printlist_c(pt_list, "%d, ", int);
            list_destroy(pt_list);
        }
        /*list_resize         */
        {
            list_t* pt_list = create_list(int);
            if(pt_list == NULL)
            {
                return;
            }
            list_init(pt_list);
            _printlist_c(pt_list, "%d, ", int);
            list_resize(pt_list, 15);
            _printlist_c(pt_list, "%d, ", int);
            list_resize(pt_list, 34);
            _printlist_c(pt_list, "%d, ", int);
            list_resize(pt_list, 21);
            _printlist_c(pt_list, "%d, ", int);
            list_resize(pt_list, 0);
            _printlist_c(pt_list, "%d, ", int);
            list_destroy(pt_list);
        }
        /*_list_resize_elem   */
        {
            list_t* pt_list = create_list(int);
            if(pt_list == NULL)
            {
                return;
            }
            list_init(pt_list);
            _printlist_c(pt_list, "%d, ", int);
            list_resize_elem(pt_list, 15, 15);
            _printlist_c(pt_list, "%d, ", int);
            list_resize_elem(pt_list, 34, 34);
            _printlist_c(pt_list, "%d, ", int);
            list_resize_elem(pt_list, 21, 21);
            _printlist_c(pt_list, "%d, ", int);
            list_resize_elem(pt_list, 0, 0);
            _printlist_c(pt_list, "%d, ", int);
            list_destroy(pt_list);
        }
        /*list_clear          */
        {
            list_t* pt_list = create_list(int);
            int i;
            if(pt_list == NULL)
            {
                return;
            }
            list_init(pt_list);
            _printlist_c(pt_list, "%d, ", int);
            for(i = 0; i < 100; ++i)
            {
                list_push_back(pt_list, i);
            }
            _printlist_c(pt_list, "%d, ", int);
            list_clear(pt_list);
            _printlist_c(pt_list, "%d, ", int);
            list_destroy(pt_list);
        }
        /*list_unique         */
        {
            list_t* pt_list = create_list(int);
            if(pt_list == NULL)
            {
                return;
            }
            list_init(pt_list);
            list_unique(pt_list);
            _printlist_c(pt_list, "%d, ", int);
            list_push_back(pt_list, 34);
            list_unique(pt_list);
            _printlist_c(pt_list, "%d, ", int);
            list_push_back(pt_list, 39);
            list_push_back(pt_list, -39);
            list_push_back(pt_list, 21);
            list_push_back(pt_list, 30);
            list_push_back(pt_list, 30);
            list_push_back(pt_list, 30);
            list_push_back(pt_list, -33);
            list_push_back(pt_list, 33);
            list_push_back(pt_list, 33);
            list_push_back(pt_list, 30);
            list_push_back(pt_list, 30);
            _printlist_c(pt_list, "%d, ", int);
            list_unique(pt_list);
            _printlist_c(pt_list, "%d, ", int);
            list_destroy(pt_list);
        }
        /*list_unique_if      */
        {
            list_t* pt_list = create_list(int);
            if(pt_list == NULL)
            {
                return;
            }
            list_init(pt_list);
            list_unique_if(pt_list, _absolute_value);
            _printlist_c(pt_list, "%d, ", int);
            list_push_back(pt_list, 34);
            list_unique_if(pt_list, _absolute_value);
            _printlist_c(pt_list, "%d, ", int);
            list_push_back(pt_list, 39);
            list_push_back(pt_list, -39);
            list_push_back(pt_list, 21);
            list_push_back(pt_list, 30);
            list_push_back(pt_list, 30);
            list_push_back(pt_list, 30);
            list_push_back(pt_list, -33);
            list_push_back(pt_list, 33);
            list_push_back(pt_list, 33);
            list_push_back(pt_list, 30);
            list_push_back(pt_list, 30);
            _printlist_c(pt_list, "%d, ", int);
            list_unique_if(pt_list, _absolute_value);
            _printlist_c(pt_list, "%d, ", int);
            list_destroy(pt_list);
        }
        /*list_splice         */
        {
            list_t* pt_list = create_list(int);
            list_t* pt_listex = create_list(int);
            if(pt_list == NULL || pt_listex == NULL)
            {
                return;
            }
            list_init(pt_list);
            list_init(pt_listex);
            list_splice(pt_list, list_begin(pt_list), pt_listex);
            _printlist_c(pt_list, "%d, ", int);
            list_push_back(pt_listex, 344);
            list_push_back(pt_listex, 12);
            list_push_back(pt_listex, 222);
            list_splice(pt_list, list_begin(pt_list), pt_listex);
            _printlist_c(pt_list, "%d, ", int);
            _printlist_c(pt_listex, "%d, ", int);
            list_push_back(pt_listex, -22);
            list_push_back(pt_listex, -90);
            list_splice(pt_list, list_end(pt_list), pt_listex);
            _printlist_c(pt_list, "%d, ", int);
            _printlist_c(pt_listex, "%d, ", int);
            list_resize(pt_listex, 3);
            list_splice(pt_list, iterator_advance(list_begin(pt_list), 3), pt_listex);
            _printlist_c(pt_list, "%d, ", int);
            _printlist_c(pt_listex, "%d, ", int);

            list_push_back(pt_listex, 100);
            list_push_back(pt_listex, 134);
            list_push_back(pt_listex, 177);
            list_push_back(pt_listex, 145);
            list_push_back(pt_listex, 111);
            list_splice_pos(pt_list, list_begin(pt_list), pt_listex, list_begin(pt_listex));
            _printlist_c(pt_list, "%d, ", int);
            _printlist_c(pt_listex, "%d, ", int);
            list_splice_pos(pt_list, list_end(pt_list), pt_listex, iterator_prev(list_end(pt_listex)));
            _printlist_c(pt_list, "%d, ", int);
            _printlist_c(pt_listex, "%d, ", int);
            list_splice_pos(pt_list, iterator_next(list_begin(pt_list)),
                pt_listex, iterator_next(list_begin(pt_listex)));
            _printlist_c(pt_list, "%d, ", int);
            _printlist_c(pt_listex, "%d, ", int);

            list_splice_range(pt_list, list_begin(pt_list),
                pt_listex, list_begin(pt_listex), list_end(pt_listex));
            _printlist_c(pt_list, "%d, ", int);
            _printlist_c(pt_listex, "%d, ", int);
            list_push_back(pt_listex, 200);
            list_push_back(pt_listex, 234);
            list_push_back(pt_listex, 277);
            list_push_back(pt_listex, 245);
            list_push_back(pt_listex, 211);
            list_push_back(pt_listex, 200);
            list_push_back(pt_listex, 234);
            list_push_back(pt_listex, 277);
            list_push_back(pt_listex, 245);
            list_push_back(pt_listex, 211);
            list_splice_range(pt_list, iterator_next(list_begin(pt_list)),
                pt_listex, list_begin(pt_listex), iterator_advance(list_begin(pt_listex), 3));
            _printlist_c(pt_list, "%d, ", int);
            _printlist_c(pt_listex, "%d, ", int);
            list_splice_range(pt_list, iterator_prev(list_end(pt_list)),
                pt_listex, iterator_advance(list_end(pt_listex), -3), list_end(pt_listex));
            _printlist_c(pt_list, "%d, ", int);
            _printlist_c(pt_listex, "%d, ", int);
            list_splice_range(pt_list, iterator_advance(list_end(pt_list), -8),
                pt_listex, iterator_next(list_begin(pt_listex)),
                iterator_prev(list_end(pt_listex)));
            _printlist_c(pt_list, "%d, ", int);
            _printlist_c(pt_listex, "%d, ", int);
            list_destroy(pt_list);
            list_destroy(pt_listex);
        }
        /*list_splice_pos     */
        /*list_splice_range   */
        /*list_sort           */
        {
            list_t* pt_list = create_list(int);
            int n_count = 0;
            int i;
            if(pt_list == NULL)
            {
                return;
            }
            list_init(pt_list);
            srand((unsigned)time(NULL));
            n_count = rand() % 10000;
            printf("count : %d\n", n_count);
            for(i = 0; i < n_count; ++i)
            {
                list_push_back(pt_list, rand());
            }
            _printlist_c(pt_list, "%d, ", int);
            list_sort(pt_list);
            printf("count : %d, size: %d\n", n_count, list_size(pt_list));
            _printlist_c(pt_list, "%d, ", int);

            n_count = rand() % 10000;
            list_clear(pt_list);
            printf("count : %d\n", n_count);
            srand((unsigned)time(NULL));
            for(i = 0; i < n_count; ++i)
            {
                list_push_back(pt_list, rand());
            }
            _printlist_c(pt_list, "%d, ", int);
            list_sort_if(pt_list, fun_great_int);
            printf("count : %d, size: %d\n", n_count, list_size(pt_list));
            _printlist_c(pt_list, "%d, ", int);
            list_destroy(pt_list);
        }
        /*list_sort_if        */
        /*list_merge          */
        {
            list_t* pt_list = create_list(int);
            list_t* pt_listex = create_list(int);
            int i = 0;
            if(pt_list == NULL || pt_listex == NULL)
            {
                return;
            }
            list_init(pt_list);
            list_init(pt_listex);
            list_merge(pt_list, pt_listex);
            _printlist_c(pt_list, "%d, ", int);
            _printlist_c(pt_listex, "%d, ", int);
            srand((unsigned)time(NULL));
            for(i = 0; i < 30; ++i)
            {
                list_push_back(pt_list, rand() - rand());
            }
            list_sort(pt_list);
            list_merge(pt_list, pt_listex);
            _printlist_c(pt_list, "%d, ", int);
            _printlist_c(pt_listex, "%d, ", int);

            srand((unsigned)time(NULL) + 9);
            for(i = 0; i < 30; ++i)
            {
                list_push_back(pt_listex, rand() - rand());
            }
            list_sort(pt_listex);
            list_merge(pt_list, pt_listex);
            _printlist_c(pt_list, "%d, ", int);
            _printlist_c(pt_listex, "%d, ", int);

            srand((unsigned)time(NULL) + 19);
            list_clear(pt_list);
            for(i = 0; i < 30; ++i)
            {
                list_push_back(pt_listex, rand() - rand());
            }
            list_sort(pt_listex);
            list_merge(pt_list, pt_listex);
            _printlist_c(pt_list, "%d, ", int);
            _printlist_c(pt_listex, "%d, ", int);

            list_clear(pt_list);
            list_merge(pt_list, pt_listex);
            _printlist_c(pt_list, "%d, ", int);
            _printlist_c(pt_listex, "%d, ", int);
            srand((unsigned)time(NULL) + 29);
            for(i = 0; i < 30; ++i)
            {
                list_push_back(pt_list, rand() - rand());
            }
            list_sort_if(pt_list, fun_great_int);
            list_merge_if(pt_list, pt_listex, fun_great_int);
            _printlist_c(pt_list, "%d, ", int);
            _printlist_c(pt_listex, "%d, ", int);

            srand((unsigned)time(NULL) + 9);
            for(i = 0; i < 30; ++i)
            {
                list_push_back(pt_listex, rand() - rand());
            }
            list_sort_if(pt_listex, fun_great_int);
            list_merge_if(pt_list, pt_listex, fun_great_int);
            _printlist_c(pt_list, "%d, ", int);
            _printlist_c(pt_listex, "%d, ", int);

            srand((unsigned)time(NULL) + 19);
            list_clear(pt_list);
            for(i = 0; i < 30; ++i)
            {
                list_push_back(pt_listex, rand() - rand());
            }
            list_sort_if(pt_listex, fun_great_int);
            list_merge_if(pt_list, pt_listex, fun_great_int);
            _printlist_c(pt_list, "%d, ", int);
            _printlist_c(pt_listex, "%d, ", int);
            list_destroy(pt_list);
            list_destroy(pt_listex);
        }
        /*list_merge_if       */
        /*list_reverse        */
        {
            list_t* pt_list = create_list(int);
            int i = 0;
            if(pt_list == NULL)
            {
                return;
            }
            list_init(pt_list);
            list_reverse(pt_list);
            _printlist_c(pt_list, "%d, ", int);
            srand((unsigned)time(NULL) + 69);
            for(i = 0; i < 30; ++i)
            {
                list_push_back(pt_list, rand());
            }
            _printlist_c(pt_list, "%d, ", int);
            list_reverse(pt_list);
            _printlist_c(pt_list, "%d, ", int);
            list_destroy(pt_list);
        }
    }
    /* for user define type */
    {
        type_register(listabc_t, _listabc_init, _listabc_copy, _listabc_less, _listabc_destory);
        type_duplicate(struct _taglistabc, listabc_t);
        _type_debug();
        /*create_list         */
        {
            list_t* pt_list = create_list(listabc_t);
            if(pt_list == NULL)
            {
                return;
            }
            list_init(pt_list);
            list_destroy(pt_list);
        }
        /*list_init           */
        /*list_destroy        */
        /*list_init_n         */
        {
            list_t* pt_list = create_list(struct _taglistabc);
            if(pt_list == NULL)
            {
                return;
            }
            list_init_n(pt_list, 3);
            _printlist_user(pt_list);
            list_destroy(pt_list);
        }
        /*_list_init_elem     */
        {
            list_t* pt_list = create_list(listabc_t);
            listabc_t t_abc;
            if(pt_list == NULL)
            {
                return;
            }
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 8;
            t_abc._t_abc._t_complex._n_imaginary = -43;
            list_init_elem(pt_list, 5, &t_abc);
            _printlist_user(pt_list);
            list_destroy(pt_list);
        }
        /*list_init_copy      */
        {
            list_t* pt_list = create_list(listabc_t);
            list_t* pt_listex = create_list(struct _taglistabc);
            listabc_t t_abc;
            if(pt_list == NULL || pt_listex == NULL)
            {
                return;
            }
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = -5;
            t_abc._t_abc._t_descartes._n_posy = 23;
            list_init_elem(pt_listex, 4, &t_abc);
            _printlist_user(pt_listex);
            list_init_copy(pt_list, pt_listex);
            _printlist_user(pt_list);
            list_destroy(pt_list);
            list_destroy(pt_listex);
        }
        /*list_init_copy_range*/
        {
            list_t* pt_list = create_list(listabc_t);
            list_t* pt_listex = create_list(struct _taglistabc);
            listabc_t t_abc;
            if(pt_list == NULL || pt_listex == NULL)
            {
                return;
            }
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = -5;
            t_abc._t_abc._t_descartes._n_posy = 23;
            list_init_elem(pt_listex, 2, &t_abc);
            t_abc._t_abc._t_descartes._n_posx = 88;
            t_abc._t_abc._t_descartes._n_posy = 99;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_abc._t_descartes._n_posx = -4;
            t_abc._t_abc._t_descartes._n_posy = -4;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 34;
            t_abc._t_abc._t_complex._n_imaginary = 2;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_abc._t_complex._n_real = 100;
            t_abc._t_abc._t_complex._n_imaginary = 21;
            list_push_front(pt_listex, &t_abc);
            t_abc._t_abc._t_complex._n_real = 8788;
            t_abc._t_abc._t_complex._n_imaginary = 9999;
            list_push_front(pt_listex, &t_abc);
            _printlist_user(pt_listex);

            list_init_copy_range(pt_list, list_begin(pt_listex), list_end(pt_listex));
            _printlist_user(pt_list);
            list_destroy(pt_list);
            list_destroy(pt_listex);
        }
        /*list_size           */
        {
            list_t* pt_list = create_list(listabc_t);
            listabc_t t_abc;
            if(pt_list == NULL)
            {
                return;
            }
            list_init(pt_list);
            printf("size : %d, empty : %d, max_size : %d\n",
                list_size(pt_list), list_empty(pt_list), list_max_size(pt_list));
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 1;
            t_abc._t_abc._t_descartes._n_posy = 2;
            list_push_back(pt_list, &t_abc);
            printf("size : %d, empty : %d, max_size : %d\n",
                list_size(pt_list), list_empty(pt_list), list_max_size(pt_list));
            list_destroy(pt_list);
        }
        /*list_empty          */
        /*list_max_size       */
        /*list_equal          */
        {
            list_t* pt_list = create_list(listabc_t);
            list_t* pt_listex = create_list(listabc_t);
            listabc_t t_abc;
            if(pt_list == NULL)
            {
                return;
            }
            list_init(pt_list);
            list_init(pt_listex);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 223;
            t_abc._t_abc._t_complex._n_imaginary = 4565;
            list_push_back(pt_list, &t_abc);
            /*t_abc._t_flag = _ABC_FLAG_COMPLEX;*/
            /*t_abc._t_abc._t_complex._n_real = 223;*/
            /*t_abc._t_abc._t_complex._n_imaginary = 4515;*/
            /*list_push_back(pt_listex, &t_abc);*/
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 245;
            t_abc._t_abc._t_descartes._n_posy = 45;
            list_push_back(pt_listex, &t_abc);
            printf("equal : %d, not equal : %d\n",
                list_equal(pt_list, pt_listex), list_not_equal(pt_list, pt_listex));
            printf("less : %d, less equal : %d\n",
                list_less(pt_list, pt_listex), list_less_equal(pt_list, pt_listex));
            printf("great : %d, great equal : %d\n",
                list_great(pt_list, pt_listex), list_great_equal(pt_list, pt_listex));
            list_destroy(pt_list);
            list_destroy(pt_listex);
        }
        /*list_not_equal      */
        /*list_less           */
        /*list_less_equal     */
        /*list_great          */
        /*list_great_equal    */
        /*list_assign         */
        {
            list_t* pt_list = create_list(listabc_t);
            list_t* pt_listex = create_list(listabc_t);
            listabc_t t_abc;
            if(pt_list == NULL || pt_listex == NULL)
            {
                return;
            }
            list_init(pt_list);
            list_init(pt_listex);
            list_assign(pt_list, pt_listex);
            _printlist_user(pt_list);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 34;
            t_abc._t_abc._t_complex._n_imaginary = -4;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = -8;
            t_abc._t_abc._t_descartes._n_posy = -3;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_abc._t_descartes._n_posx = -45;
            t_abc._t_abc._t_descartes._n_posy = 33;
            list_push_back(pt_listex, &t_abc);
            list_assign(pt_list, pt_listex);
            _printlist_user(pt_list);
            list_clear(pt_listex);
            t_abc._t_abc._t_descartes._n_posx = 90;
            t_abc._t_abc._t_descartes._n_posy = 34;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_abc._t_descartes._n_posx = -1;
            t_abc._t_abc._t_descartes._n_posy = 45;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 89;
            t_abc._t_abc._t_complex._n_imaginary = 34;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_abc._t_complex._n_real = 9;
            t_abc._t_abc._t_complex._n_imaginary = 112;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_abc._t_complex._n_real = 4;
            t_abc._t_abc._t_complex._n_imaginary = 9;
            list_push_back(pt_listex, &t_abc);
            list_assign(pt_list, pt_listex);
            _printlist_user(pt_list);
            list_clear(pt_listex);
            t_abc._t_abc._t_complex._n_real = 90;
            t_abc._t_abc._t_complex._n_imaginary = -90;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_abc._t_complex._n_real = 0;
            t_abc._t_abc._t_complex._n_imaginary = 0;
            list_push_back(pt_listex, &t_abc);
            list_assign(pt_list, pt_listex);
            _printlist_user(pt_list);
            list_clear(pt_listex);
            list_assign(pt_list, pt_listex);
            _printlist_user(pt_list);
            list_destroy(pt_list);
            list_destroy(pt_listex);
        }
        /*list_assign_elem    */
        {
            list_t* pt_list = create_list(listabc_t);
            listabc_t t_abc;
            if(pt_list == NULL)
            {
                return;
            }
            list_init(pt_list);
            list_assign_elem(pt_list, 0, &t_abc);
            _printlist_user(pt_list);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 90;
            t_abc._t_abc._t_complex._n_imaginary = 34;
            list_assign_elem(pt_list, 3, &t_abc);
            _printlist_user(pt_list);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = -4;
            t_abc._t_abc._t_descartes._n_posy = 7;
            list_assign_elem(pt_list, 15, &t_abc);
            _printlist_user(pt_list);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 102;
            t_abc._t_abc._t_complex._n_imaginary = 47;
            list_assign_elem(pt_list, 7, &t_abc);
            _printlist_user(pt_list);
            list_assign_elem(pt_list, 0, &t_abc);
            _printlist_user(pt_list);
            list_destroy(pt_list);
        }
        /*list_assign_range   */
        {
            list_t* pt_list = create_list(listabc_t);
            list_t* pt_listex = create_list(listabc_t);
            listabc_t t_abc;
            if(pt_list == NULL || pt_listex == NULL)
            {
                return;
            }
            list_init(pt_list);
            list_init(pt_listex);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 7;
            t_abc._t_abc._t_descartes._n_posy = 21;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_abc._t_descartes._n_posx = 86;
            t_abc._t_abc._t_descartes._n_posy = 2134;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 9;
            t_abc._t_abc._t_complex._n_imaginary = -777;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 195;
            t_abc._t_abc._t_descartes._n_posy = 12580;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 32;
            t_abc._t_abc._t_complex._n_imaginary = 47;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 62;
            t_abc._t_abc._t_complex._n_imaginary = -7;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 600;
            t_abc._t_abc._t_complex._n_imaginary = -700;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 5;
            t_abc._t_abc._t_descartes._n_posy = 12593;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 5;
            t_abc._t_abc._t_descartes._n_posy = 17951;
            list_push_back(pt_listex, &t_abc);
            _printlist_user(pt_listex);
            list_assign_range(pt_list, list_begin(pt_listex), list_begin(pt_listex));
            _printlist_user(pt_list);
            list_assign_range(pt_list,
                list_begin(pt_listex), iterator_advance(list_begin(pt_listex), 3));
            _printlist_user(pt_list);
            list_assign_range(pt_list,
                iterator_next(list_begin(pt_listex)), iterator_advance(list_begin(pt_listex), 5));
            _printlist_user(pt_list);
            list_assign_range(pt_list,
                iterator_advance(list_end(pt_listex), -3), list_end(pt_listex));
            _printlist_user(pt_list);
            list_assign_range(pt_list, list_end(pt_listex), list_end(pt_listex));
            _printlist_user(pt_list);
            list_destroy(pt_list);
            list_destroy(pt_listex);
        }
        /*list_swap           */
        {
            list_t* pt_list = create_list(listabc_t);
            list_t* pt_listex = create_list(listabc_t);
            listabc_t t_abc;
            if(pt_list == NULL || pt_listex == NULL)
            {
                return;
            }
            list_init(pt_list);
            list_init(pt_listex);
            list_swap(pt_list, pt_listex);
            _printlist_user(pt_list);
            _printlist_user(pt_listex);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 7;
            t_abc._t_abc._t_descartes._n_posy = 21;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_abc._t_descartes._n_posx = 86;
            t_abc._t_abc._t_descartes._n_posy = 2134;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 9;
            t_abc._t_abc._t_complex._n_imaginary = -777;
            list_push_back(pt_listex, &t_abc);
            list_swap(pt_list, pt_listex);
            _printlist_user(pt_list);
            _printlist_user(pt_listex);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 195;
            t_abc._t_abc._t_descartes._n_posy = 12580;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 32;
            t_abc._t_abc._t_complex._n_imaginary = 47;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 62;
            t_abc._t_abc._t_complex._n_imaginary = -7;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 600;
            t_abc._t_abc._t_complex._n_imaginary = -700;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 5;
            t_abc._t_abc._t_descartes._n_posy = 12593;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 5;
            t_abc._t_abc._t_descartes._n_posy = 17951;
            list_push_back(pt_listex, &t_abc);
            list_swap(pt_list, pt_listex);
            _printlist_user(pt_list);
            _printlist_user(pt_listex);
            list_clear(pt_listex);
            list_swap(pt_list, pt_listex);
            _printlist_user(pt_list);
            _printlist_user(pt_listex);
            list_destroy(pt_list);
            list_destroy(pt_listex);
        }
        /*list_front          */
        {
            list_t* pt_list = create_list(listabc_t);
            listabc_t t_abc;
            if(pt_list == NULL)
            {
                return;
            }
            list_init(pt_list);
            if(list_front(pt_list) != NULL)
            {
                ((listabc_t*)list_front(pt_list))->_t_flag = _ABC_FLAG_COMPLEX;
                ((listabc_t*)list_front(pt_list))->_t_abc._t_complex._n_real = 100;
                ((listabc_t*)list_front(pt_list))->_t_abc._t_complex._n_imaginary = 100;
            }
            if(list_back(pt_list) != NULL)
            {
                ((listabc_t*)list_back(pt_list))->_t_flag = _ABC_FLAG_DESCARTES;
                ((listabc_t*)list_back(pt_list))->_t_abc._t_descartes._n_posx = 33;
                ((listabc_t*)list_back(pt_list))->_t_abc._t_descartes._n_posy = 33;
            }
            _printlist_user(pt_list);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 62;
            t_abc._t_abc._t_complex._n_imaginary = -7;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 600;
            t_abc._t_abc._t_complex._n_imaginary = -700;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 5;
            t_abc._t_abc._t_descartes._n_posy = 17951;
            list_push_back(pt_list, &t_abc);
            _printlist_user(pt_list);
            if(list_front(pt_list) != NULL)
            {
                ((listabc_t*)list_front(pt_list))->_t_flag = _ABC_FLAG_COMPLEX;
                ((listabc_t*)list_front(pt_list))->_t_abc._t_complex._n_real = 100;
                ((listabc_t*)list_front(pt_list))->_t_abc._t_complex._n_imaginary = 100;
            }
            if(list_back(pt_list) != NULL)
            {
                ((listabc_t*)list_back(pt_list))->_t_flag = _ABC_FLAG_DESCARTES;
                ((listabc_t*)list_back(pt_list))->_t_abc._t_descartes._n_posx = 33;
                ((listabc_t*)list_back(pt_list))->_t_abc._t_descartes._n_posy = 33;
            }
            _printlist_user(pt_list);
            list_destroy(pt_list);
        }
        /*list_back           */
        /*list_begin          */
        /*list_end            */
        /*list_insert         */
        {
            list_t* pt_list = create_list(listabc_t);
            listabc_t t_abc;
            if(pt_list == NULL)
            {
                return;
            }
            list_init(pt_list);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 62;
            t_abc._t_abc._t_complex._n_imaginary = -7;
            list_insert(pt_list, list_begin(pt_list), &t_abc);
            _printlist_user(pt_list);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 5;
            t_abc._t_abc._t_descartes._n_posy = 17951;
            list_insert(pt_list, list_end(pt_list), &t_abc);
            _printlist_user(pt_list);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 5;
            t_abc._t_abc._t_descartes._n_posy = 12593;
            list_insert(pt_list, list_begin(pt_list), &t_abc);
            _printlist_user(pt_list);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 9;
            t_abc._t_abc._t_complex._n_imaginary = -777;
            list_insert(pt_list, iterator_next(list_begin(pt_list)), &t_abc);
            _printlist_user(pt_list);
            list_destroy(pt_list);
        }
        /*list_insert_n       */
        {
            list_t* pt_list = create_list(listabc_t);
            listabc_t t_abc;
            if(pt_list == NULL)
            {
                return;
            }
            list_init(pt_list);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 62;
            t_abc._t_abc._t_complex._n_imaginary = -7;
            list_insert_n(pt_list, list_begin(pt_list), 3, &t_abc);
            _printlist_user(pt_list);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 5;
            t_abc._t_abc._t_descartes._n_posy = 17951;
            list_insert_n(pt_list, list_end(pt_list), 2, &t_abc);
            _printlist_user(pt_list);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 5;
            t_abc._t_abc._t_descartes._n_posy = 12593;
            list_insert_n(pt_list, list_begin(pt_list), 5, &t_abc);
            _printlist_user(pt_list);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 9;
            t_abc._t_abc._t_complex._n_imaginary = -777;
            list_insert_n(pt_list, iterator_next(list_begin(pt_list)), 3, &t_abc);
            _printlist_user(pt_list);
            list_destroy(pt_list);
        }
        /*list_insert_range   */
        {
            list_t* pt_list = create_list(listabc_t);
            list_t* pt_listex = create_list(listabc_t);
            listabc_t t_abc;
            if(pt_list == NULL || pt_listex == NULL)
            {
                return;
            }
            list_init(pt_list);
            list_init(pt_listex);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 7;
            t_abc._t_abc._t_descartes._n_posy = 21;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_abc._t_descartes._n_posx = 86;
            t_abc._t_abc._t_descartes._n_posy = 2134;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 9;
            t_abc._t_abc._t_complex._n_imaginary = -777;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 195;
            t_abc._t_abc._t_descartes._n_posy = 12580;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 32;
            t_abc._t_abc._t_complex._n_imaginary = 47;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 62;
            t_abc._t_abc._t_complex._n_imaginary = -7;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 600;
            t_abc._t_abc._t_complex._n_imaginary = -700;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 5;
            t_abc._t_abc._t_descartes._n_posy = 12593;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 5;
            t_abc._t_abc._t_descartes._n_posy = 17951;
            list_push_back(pt_listex, &t_abc);
            _printlist_user(pt_listex);
            list_insert_range(pt_list, list_begin(pt_list),
                list_begin(pt_listex), list_begin(pt_listex));
            _printlist_user(pt_list);
            list_insert_range(pt_list, list_begin(pt_list),
                list_begin(pt_listex), iterator_advance(list_begin(pt_listex), 3));
            _printlist_user(pt_list);
            list_insert_range(pt_list, list_end(pt_list),
                iterator_next(list_begin(pt_listex)), iterator_advance(list_begin(pt_listex), 5));
            _printlist_user(pt_list);
            list_insert_range(pt_list, iterator_advance(list_begin(pt_list), 5),
                iterator_advance(list_end(pt_listex), -4), list_end(pt_listex));
            _printlist_user(pt_list);
            list_destroy(pt_list);
            list_destroy(pt_listex);
        }
        /*list_push_back      */
        {
            list_t* pt_list = create_list(listabc_t);
            listabc_t t_abc;
            int i = 0;
            if(pt_list == NULL)
            {
                return;
            }
            list_init(pt_list);
            for(i = 0; i < 10; ++i)
            {
                t_abc._t_flag = _ABC_FLAG_DESCARTES;
                t_abc._t_abc._t_descartes._n_posx = i;
                t_abc._t_abc._t_descartes._n_posy = i;
                list_push_back(pt_list, &t_abc);
            }
            _printlist_user(pt_list);
            while(!list_empty(pt_list))
            {
                list_pop_front(pt_list);
            }
            _printlist_user(pt_list);
            for(i = 0; i < 30; ++i)
            {
                t_abc._t_flag = _ABC_FLAG_COMPLEX;
                t_abc._t_abc._t_complex._n_real = i;
                t_abc._t_abc._t_complex._n_imaginary = i;
                list_push_front(pt_list, &t_abc);
            }
            _printlist_user(pt_list);
            while(!list_empty(pt_list))
            {
                list_pop_back(pt_list);
            }
            _printlist_user(pt_list);
            list_destroy(pt_list);
        }
        /*list_pop_back       */
        /*list_push_front     */
        /*list_pop_front      */
        /*list_erase          */
        {
            list_t* pt_list = create_list(listabc_t);
            listabc_t t_abc;
            if(pt_list == NULL)
            {
                return;
            }
            list_init(pt_list);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 7;
            t_abc._t_abc._t_descartes._n_posy = 21;
            list_push_back(pt_list, &t_abc);
            t_abc._t_abc._t_descartes._n_posx = 86;
            t_abc._t_abc._t_descartes._n_posy = 2134;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 9;
            t_abc._t_abc._t_complex._n_imaginary = -777;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 195;
            t_abc._t_abc._t_descartes._n_posy = 12580;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 32;
            t_abc._t_abc._t_complex._n_imaginary = 47;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 62;
            t_abc._t_abc._t_complex._n_imaginary = -7;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 600;
            t_abc._t_abc._t_complex._n_imaginary = -700;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 5;
            t_abc._t_abc._t_descartes._n_posy = 12593;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 5;
            t_abc._t_abc._t_descartes._n_posy = 17951;
            list_push_back(pt_list, &t_abc);
            _printlist_user(pt_list);
            list_erase(pt_list, list_begin(pt_list));
            _printlist_user(pt_list);
            list_erase(pt_list, iterator_prev(list_end(pt_list)));
            _printlist_user(pt_list);
            list_erase(pt_list, iterator_advance(list_begin(pt_list), 4));
            _printlist_user(pt_list);
            list_destroy(pt_list);
        }
        /*list_erase_range    */
        {
            list_t* pt_list = create_list(listabc_t);
            listabc_t t_abc;
            if(pt_list == NULL)
            {
                return;
            }
            list_init(pt_list);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 7;
            t_abc._t_abc._t_descartes._n_posy = 21;
            list_push_back(pt_list, &t_abc);
            t_abc._t_abc._t_descartes._n_posx = 86;
            t_abc._t_abc._t_descartes._n_posy = 2134;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 9;
            t_abc._t_abc._t_complex._n_imaginary = -777;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 195;
            t_abc._t_abc._t_descartes._n_posy = 12580;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 32;
            t_abc._t_abc._t_complex._n_imaginary = 47;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 62;
            t_abc._t_abc._t_complex._n_imaginary = -7;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 600;
            t_abc._t_abc._t_complex._n_imaginary = -700;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 5;
            t_abc._t_abc._t_descartes._n_posy = 12593;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 5;
            t_abc._t_abc._t_descartes._n_posy = 17951;
            list_push_back(pt_list, &t_abc);
            _printlist_user(pt_list);
            list_erase_range(pt_list, list_begin(pt_list), list_begin(pt_list));
            _printlist_user(pt_list);
            list_erase_range(pt_list, list_begin(pt_list),
                iterator_advance(list_begin(pt_list), 3));
            _printlist_user(pt_list);
            list_erase_range(pt_list, iterator_next(list_begin(pt_list)),
                iterator_advance(list_begin(pt_list), 3));
            _printlist_user(pt_list);
            list_erase_range(pt_list, iterator_advance(list_end(pt_list), -3), list_end(pt_list));
            _printlist_user(pt_list);
            list_erase_range(pt_list, list_begin(pt_list), list_end(pt_list));
            _printlist_user(pt_list);
            list_destroy(pt_list);
        }
        /*list_remove         */
        {
            list_t* pt_list = create_list(listabc_t);
            listabc_t t_abc;
            if(pt_list == NULL)
            {
                return;
            }
            list_init(pt_list);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 7;
            t_abc._t_abc._t_descartes._n_posy = 21;
            list_push_back(pt_list, &t_abc);
            t_abc._t_abc._t_descartes._n_posx = 86;
            t_abc._t_abc._t_descartes._n_posy = 2134;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 9;
            t_abc._t_abc._t_complex._n_imaginary = -777;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 195;
            t_abc._t_abc._t_descartes._n_posy = 12580;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 5;
            t_abc._t_abc._t_complex._n_imaginary = 12593;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 5;
            t_abc._t_abc._t_complex._n_imaginary = 12593;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 32;
            t_abc._t_abc._t_complex._n_imaginary = 47;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 62;
            t_abc._t_abc._t_complex._n_imaginary = -7;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 600;
            t_abc._t_abc._t_complex._n_imaginary = -700;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 5;
            t_abc._t_abc._t_descartes._n_posy = 12593;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 5;
            t_abc._t_abc._t_descartes._n_posy = 17951;
            list_push_back(pt_list, &t_abc);
            _printlist_user(pt_list);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 5;
            t_abc._t_abc._t_descartes._n_posy = 5;
            list_remove(pt_list, &t_abc);
            _printlist_user(pt_list);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 5;
            t_abc._t_abc._t_descartes._n_posy = 12593;
            list_remove(pt_list, &t_abc);
            _printlist_user(pt_list);
            list_destroy(pt_list);
        }
        /*list_remove_if      */
        {
            list_t* pt_list = create_list(listabc_t);
            listabc_t t_abc;
            if(pt_list == NULL)
            {
                return;
            }
            list_init(pt_list);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 7;
            t_abc._t_abc._t_descartes._n_posy = 21;
            list_push_back(pt_list, &t_abc);
            t_abc._t_abc._t_descartes._n_posx = 86;
            t_abc._t_abc._t_descartes._n_posy = 2134;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 9;
            t_abc._t_abc._t_complex._n_imaginary = -777;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 195;
            t_abc._t_abc._t_descartes._n_posy = 12580;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 5;
            t_abc._t_abc._t_complex._n_imaginary = 12593;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 5;
            t_abc._t_abc._t_complex._n_imaginary = 12593;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 32;
            t_abc._t_abc._t_complex._n_imaginary = 47;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 62;
            t_abc._t_abc._t_complex._n_imaginary = -7;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 600;
            t_abc._t_abc._t_complex._n_imaginary = -700;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 5;
            t_abc._t_abc._t_descartes._n_posy = 12593;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 5;
            t_abc._t_abc._t_descartes._n_posy = 17951;
            list_push_back(pt_list, &t_abc);
            _printlist_user(pt_list);
            list_remove_if(pt_list, _remove_first_5);
            _printlist_user(pt_list);
            list_destroy(pt_list);
        }
        /*list_resize         */
        {
            list_t* pt_list = create_list(listabc_t);
            if(pt_list == NULL)
            {
                return;
            }
            list_init(pt_list);
            list_resize(pt_list, 5);
            _printlist_user(pt_list);
            list_resize(pt_list, 18);
            _printlist_user(pt_list);
            list_resize(pt_list, 7);
            _printlist_user(pt_list);
            list_resize(pt_list, 0);
            _printlist_user(pt_list);
            list_destroy(pt_list);
        }
        /*list_resize_elem    */
        {
            list_t* pt_list = create_list(listabc_t);
            listabc_t t_abc;
            if(pt_list == NULL)
            {
                return;
            }
            list_init(pt_list);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 5;
            t_abc._t_abc._t_descartes._n_posy = 12593;
            list_resize_elem(pt_list, 5, &t_abc);
            _printlist_user(pt_list);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 600;
            t_abc._t_abc._t_complex._n_imaginary = -700;
            list_resize_elem(pt_list, 21, &t_abc);
            _printlist_user(pt_list);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 195;
            t_abc._t_abc._t_descartes._n_posy = 12580;
            list_resize_elem(pt_list, 8, &t_abc);
            _printlist_user(pt_list);
            list_resize_elem(pt_list, 0, &t_abc);
            _printlist_user(pt_list);
            list_destroy(pt_list);
        }
        /*list_clear          */
        {
            list_t* pt_list = create_list(listabc_t);
            listabc_t t_abc;
            if(pt_list == NULL)
            {
                return;
            }
            list_init(pt_list);
            list_clear(pt_list);
            _printlist_user(pt_list);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 5;
            t_abc._t_abc._t_descartes._n_posy = 12593;
            list_resize_elem(pt_list, 5, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 600;
            t_abc._t_abc._t_complex._n_imaginary = -700;
            list_resize_elem(pt_list, 21, &t_abc);
            _printlist_user(pt_list);
            list_clear(pt_list);
            _printlist_user(pt_list);
            list_destroy(pt_list);
        }
        /*list_unique         */
        {
            list_t* pt_list = create_list(listabc_t);
            listabc_t t_abc;
            if(pt_list == NULL)
            {
                return;
            }
            list_init(pt_list);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 7;
            t_abc._t_abc._t_descartes._n_posy = 21;
            list_push_back(pt_list, &t_abc);
            t_abc._t_abc._t_descartes._n_posx = 86;
            t_abc._t_abc._t_descartes._n_posy = 2134;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 9;
            t_abc._t_abc._t_complex._n_imaginary = -777;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 195;
            t_abc._t_abc._t_descartes._n_posy = 12580;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 5;
            t_abc._t_abc._t_complex._n_imaginary = 12593;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 5;
            t_abc._t_abc._t_complex._n_imaginary = 12593;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 32;
            t_abc._t_abc._t_complex._n_imaginary = 47;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 62;
            t_abc._t_abc._t_complex._n_imaginary = -7;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 600;
            t_abc._t_abc._t_complex._n_imaginary = -700;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 5;
            t_abc._t_abc._t_descartes._n_posy = 12593;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 5;
            t_abc._t_abc._t_descartes._n_posy = 17951;
            list_push_back(pt_list, &t_abc);
            _printlist_user(pt_list);
            list_unique(pt_list);
            _printlist_user(pt_list);
            list_destroy(pt_list);
        }
        /*list_unique_if      */
        {
            list_t* pt_list = create_list(listabc_t);
            listabc_t t_abc;
            if(pt_list == NULL)
            {
                return;
            }
            list_init(pt_list);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 7;
            t_abc._t_abc._t_descartes._n_posy = 21;
            list_push_back(pt_list, &t_abc);
            t_abc._t_abc._t_descartes._n_posx = 86;
            t_abc._t_abc._t_descartes._n_posy = 2134;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 9;
            t_abc._t_abc._t_complex._n_imaginary = -777;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 195;
            t_abc._t_abc._t_descartes._n_posy = 12580;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 5;
            t_abc._t_abc._t_complex._n_imaginary = 12593;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 5;
            t_abc._t_abc._t_complex._n_imaginary = 12593;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 32;
            t_abc._t_abc._t_complex._n_imaginary = 47;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 62;
            t_abc._t_abc._t_complex._n_imaginary = -7;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 600;
            t_abc._t_abc._t_complex._n_imaginary = -700;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 5;
            t_abc._t_abc._t_descartes._n_posy = 12593;
            list_push_back(pt_list, &t_abc);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 5;
            t_abc._t_abc._t_descartes._n_posy = 17951;
            list_push_back(pt_list, &t_abc);
            _printlist_user(pt_list);
            list_unique_if(pt_list, _listabc_less);
            _printlist_user(pt_list);
            list_destroy(pt_list);
        }
        /*list_splice         */
        {
            list_t* pt_list = create_list(listabc_t);
            list_t* pt_listex = create_list(listabc_t);
            listabc_t t_abc;
            if(pt_list == NULL || pt_listex == NULL)
            {
                return;
            }
            list_init(pt_list);
            list_init(pt_listex);
            list_splice(pt_list, list_begin(pt_list), pt_listex);
            _printlist_user(pt_list);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 5;
            t_abc._t_abc._t_descartes._n_posy = 17951;
            list_resize_elem(pt_listex, 3, &t_abc);
            list_splice(pt_list, list_begin(pt_list), pt_listex);
            _printlist_user(pt_list);
            list_clear(pt_listex);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 600;
            t_abc._t_abc._t_complex._n_imaginary = -700;
            list_resize_elem(pt_listex, 5, &t_abc);
            list_splice(pt_list, list_end(pt_list), pt_listex);
            _printlist_user(pt_list);
            list_clear(pt_listex);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 3000;
            t_abc._t_abc._t_complex._n_imaginary = -300;
            list_resize_elem(pt_listex, 2, &t_abc);
            list_splice(pt_list, list_begin(pt_list), pt_listex);
            _printlist_user(pt_list);
            list_clear(pt_listex);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = -300;
            t_abc._t_abc._t_complex._n_imaginary = -300;
            list_resize_elem(pt_listex, 2, &t_abc);
            list_splice(pt_list, iterator_advance(list_begin(pt_list), 4), pt_listex);
            _printlist_user(pt_list);
            list_destroy(pt_list);
            list_destroy(pt_listex);
        }
        /*list_splice_pos     */
        {
            list_t* pt_list = create_list(listabc_t);
            list_t* pt_listex = create_list(listabc_t);
            listabc_t t_abc;
            if(pt_list == NULL || pt_listex == NULL)
            {
                return;
            }
            list_init(pt_list);
            list_init(pt_listex);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 7;
            t_abc._t_abc._t_descartes._n_posy = 21;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_abc._t_descartes._n_posx = 86;
            t_abc._t_abc._t_descartes._n_posy = 2134;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 9;
            t_abc._t_abc._t_complex._n_imaginary = -777;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 195;
            t_abc._t_abc._t_descartes._n_posy = 12580;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 32;
            t_abc._t_abc._t_complex._n_imaginary = 47;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 62;
            t_abc._t_abc._t_complex._n_imaginary = -7;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 600;
            t_abc._t_abc._t_complex._n_imaginary = -700;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 5;
            t_abc._t_abc._t_descartes._n_posy = 12593;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 5;
            t_abc._t_abc._t_descartes._n_posy = 17951;
            list_push_back(pt_listex, &t_abc);
            _printlist_user(pt_listex);
            list_splice_pos(pt_list, list_begin(pt_list), pt_listex, list_begin(pt_listex));
            _printlist_user(pt_list);
            _printlist_user(pt_listex);
            list_splice_pos(pt_list, list_end(pt_list), pt_listex, iterator_prev(list_end(pt_listex)));
            _printlist_user(pt_list);
            _printlist_user(pt_listex);
            list_splice_pos(pt_list, iterator_next(list_begin(pt_list)),
                pt_listex, iterator_advance(list_begin(pt_listex), 3));
            _printlist_user(pt_list);
            _printlist_user(pt_listex);
            list_destroy(pt_list);
            list_destroy(pt_listex);
        }
        /*list_splice_range   */
        {
            list_t* pt_list = create_list(listabc_t);
            list_t* pt_listex = create_list(listabc_t);
            listabc_t t_abc;
            if(pt_list == NULL || pt_listex == NULL)
            {
                return;
            }
            list_init(pt_list);
            list_init(pt_listex);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 7;
            t_abc._t_abc._t_descartes._n_posy = 21;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_abc._t_descartes._n_posx = 86;
            t_abc._t_abc._t_descartes._n_posy = 2134;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 9;
            t_abc._t_abc._t_complex._n_imaginary = -777;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 195;
            t_abc._t_abc._t_descartes._n_posy = 12580;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 32;
            t_abc._t_abc._t_complex._n_imaginary = 47;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 62;
            t_abc._t_abc._t_complex._n_imaginary = -7;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_flag = _ABC_FLAG_COMPLEX;
            t_abc._t_abc._t_complex._n_real = 600;
            t_abc._t_abc._t_complex._n_imaginary = -700;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 5;
            t_abc._t_abc._t_descartes._n_posy = 12593;
            list_push_back(pt_listex, &t_abc);
            t_abc._t_flag = _ABC_FLAG_DESCARTES;
            t_abc._t_abc._t_descartes._n_posx = 5;
            t_abc._t_abc._t_descartes._n_posy = 17951;
            list_push_back(pt_listex, &t_abc);
            _printlist_user(pt_listex);
            list_splice_range(pt_list, list_begin(pt_list),
                pt_listex, list_begin(pt_listex), list_begin(pt_listex));
            _printlist_user(pt_list);
            _printlist_user(pt_listex);
            list_splice_range(pt_list, list_end(pt_list),
                pt_listex, list_begin(pt_listex), iterator_advance(list_begin(pt_listex), 3));
            _printlist_user(pt_list);
            _printlist_user(pt_listex);
            list_splice_range(pt_list, iterator_next(list_begin(pt_list)),
                pt_listex, iterator_advance(list_end(pt_listex), -3), list_end(pt_listex));
            _printlist_user(pt_list);
            _printlist_user(pt_listex);
            list_splice_range(pt_list, list_begin(pt_list),
                pt_listex, list_begin(pt_listex), list_end(pt_listex));
            _printlist_user(pt_list);
            _printlist_user(pt_listex);
            list_destroy(pt_list);
            list_destroy(pt_listex);
        }
        /*list_sort           */
        {
            list_t* pt_list = create_list(listabc_t);
            listabc_t t_abc;
            int n_count = 0;
            int i = 0;
            if(pt_list == NULL)
            {
                return;
            }
            list_init(pt_list);
            srand((unsigned)time(NULL));
            n_count = rand() % 10000;
            for(i = 0; i < n_count; ++i)
            {
                t_abc._t_flag = rand() % 2;
                t_abc._t_abc._t_descartes._n_posx = rand() - rand();
                t_abc._t_abc._t_descartes._n_posy = rand() - rand();
                list_push_back(pt_list, &t_abc);
            }
            _printlist_user(pt_list);
            list_sort(pt_list);
            _printlist_user(pt_list);
            printf("%d, %d\n", list_size(pt_list), n_count);
            list_destroy(pt_list);
        }
        /*list_sort_if        */
        {
            list_t* pt_list = create_list(listabc_t);
            listabc_t t_abc;
            int n_count = 0;
            int i = 0;
            if(pt_list == NULL)
            {
                return;
            }
            list_init(pt_list);
            srand((unsigned)time(NULL) + 19);
            n_count = rand() % 10000;
            for(i = 0; i < n_count; ++i)
            {
                t_abc._t_flag = rand() % 2;
                t_abc._t_abc._t_descartes._n_posx = rand() - rand();
                t_abc._t_abc._t_descartes._n_posy = rand() - rand();
                list_push_back(pt_list, &t_abc);
            }
            _printlist_user(pt_list);
            list_sort_if(pt_list, _listabc_great);
            _printlist_user(pt_list);
            printf("%d, %d\n", list_size(pt_list), n_count);
            list_destroy(pt_list);
        }
        /*list_merge          */
        {
            list_t* pt_list = create_list(listabc_t);
            list_t* pt_listex = create_list(listabc_t);
            listabc_t t_abc;
            int n_count = 0;
            int i = 0;
            if(pt_list == NULL || pt_listex == NULL)
            {
                return;
            }
            list_init(pt_list);
            list_init(pt_listex);
            srand((unsigned)time(NULL) + 19);
            n_count = rand() % 100;
            for(i = 0; i < n_count; ++i)
            {
                t_abc._t_flag = rand() % 2;
                t_abc._t_abc._t_descartes._n_posx = rand() - rand();
                t_abc._t_abc._t_descartes._n_posy = rand() - rand();
                list_push_back(pt_listex, &t_abc);
            }
            list_sort(pt_listex);
            _printlist_user(pt_list);
            _printlist_user(pt_listex);
            list_merge(pt_list, pt_listex);
            _printlist_user(pt_list);
            _printlist_user(pt_listex);
            srand((unsigned)time(NULL) + 59);
            n_count = rand() % 100;
            for(i = 0; i < n_count; ++i)
            {
                t_abc._t_flag = rand() % 2;
                t_abc._t_abc._t_descartes._n_posx = rand() - rand();
                t_abc._t_abc._t_descartes._n_posy = rand() - rand();
                list_push_back(pt_listex, &t_abc);
            }
            list_sort(pt_listex);
            _printlist_user(pt_list);
            _printlist_user(pt_listex);
            list_merge(pt_list, pt_listex);
            _printlist_user(pt_list);
            _printlist_user(pt_listex);
            list_merge(pt_list, pt_listex);
            _printlist_user(pt_list);
            _printlist_user(pt_listex);
            list_clear(pt_list);
            _printlist_user(pt_list);
            _printlist_user(pt_listex);
            list_merge(pt_list, pt_listex);
            _printlist_user(pt_list);
            _printlist_user(pt_listex);
            list_destroy(pt_list);
            list_destroy(pt_listex);
        }
        /*list_merge_if       */
        {
            list_t* pt_list = create_list(listabc_t);
            list_t* pt_listex = create_list(listabc_t);
            listabc_t t_abc;
            int n_count = 0;
            int i = 0;
            if(pt_list == NULL || pt_listex == NULL)
            {
                return;
            }
            list_init(pt_list);
            list_init(pt_listex);
            srand((unsigned)time(NULL) + 89);
            n_count = rand() % 100;
            for(i = 0; i < n_count; ++i)
            {
                t_abc._t_flag = rand() % 2;
                t_abc._t_abc._t_descartes._n_posx = rand() - rand();
                t_abc._t_abc._t_descartes._n_posy = rand() - rand();
                list_push_back(pt_listex, &t_abc);
            }
            list_sort_if(pt_listex, _listabc_great);
            _printlist_user(pt_list);
            _printlist_user(pt_listex);
            list_merge_if(pt_list, pt_listex, _listabc_great);
            _printlist_user(pt_list);
            _printlist_user(pt_listex);
            srand((unsigned)time(NULL) + 19);
            n_count = rand() % 100;
            for(i = 0; i < n_count; ++i)
            {
                t_abc._t_flag = rand() % 2;
                t_abc._t_abc._t_descartes._n_posx = rand() - rand();
                t_abc._t_abc._t_descartes._n_posy = rand() - rand();
                list_push_back(pt_listex, &t_abc);
            }
            list_sort_if(pt_listex, _listabc_great);
            _printlist_user(pt_list);
            _printlist_user(pt_listex);
            list_merge_if(pt_list, pt_listex, _listabc_great);
            _printlist_user(pt_list);
            _printlist_user(pt_listex);
            list_merge_if(pt_list, pt_listex, _listabc_great);
            _printlist_user(pt_list);
            _printlist_user(pt_listex);
            list_clear(pt_list);
            _printlist_user(pt_list);
            _printlist_user(pt_listex);
            list_merge_if(pt_list, pt_listex, _listabc_great);
            _printlist_user(pt_list);
            _printlist_user(pt_listex);
            list_destroy(pt_list);
            list_destroy(pt_listex);
        }
        /*list_reverse        */
        {
            list_t* pt_list = create_list(listabc_t);
            listabc_t t_abc;
            int n_count = 0;
            int i = 0;
            if(pt_list == NULL)
            {
                return;
            }
            list_init(pt_list);
            _printlist_user(pt_list);
            list_reverse(pt_list);
            _printlist_user(pt_list);
            srand((unsigned)time(NULL) + 109);
            n_count = rand() % 100;
            for(i = 0; i < n_count; ++i)
            {
                t_abc._t_flag = rand() % 2;
                t_abc._t_abc._t_descartes._n_posx = rand() - rand();
                t_abc._t_abc._t_descartes._n_posy = rand() - rand();
                list_push_back(pt_list, &t_abc);
            }
            _printlist_user(pt_list);
            list_reverse(pt_list);
            _printlist_user(pt_list);
            list_destroy(pt_list);
        }
    }
    /* for cstl built-in type */
    {
        /*create_list         */
        {
            list_t* pt_list = create_list(list_t<int>);
            if(pt_list == NULL)
            {
                return;
            }
            list_init(pt_list);
            list_destroy(pt_list);
        }
        /*list_init           */
        /*list_init_n         */
        {
            list_t* pt_list = create_list(list_t<int>);
            if(pt_list == NULL)
            {
                return;
            }
            list_init_n(pt_list, 4);
            _printlist_list(pt_list);
            list_destroy(pt_list);
        }
        /*_list_init_elem     */
        {
            list_t* pt_list = create_list(list_t<int>);
            list_t* pt_listex = create_list(int);
            if(pt_list == NULL || pt_listex == NULL)
            {
                return;
            }
            list_init_elem(pt_listex, 3, 999);
            list_init_elem(pt_list, 5, pt_listex);
            _printlist_list(pt_list);
            list_destroy(pt_list);
            list_destroy(pt_listex);
        }
        /*list_init_copy      */
        {
            list_t* pt_list1 = create_list(list_t<int>);
            list_t* pt_list2 = create_list(list_t<signed int>);
            list_t* pt_listex = create_list(signed);
            if(pt_list1 == NULL || pt_list2 == NULL || pt_listex == NULL)
            {
                return;
            }
            list_init_elem(pt_listex, 10, 10);
            list_init_elem(pt_list2, 10, pt_listex);
            list_init_copy(pt_list1, pt_list2);
            _printlist_list(pt_list1);
            list_destroy(pt_list1);
            list_destroy(pt_list2);
            list_destroy(pt_listex);
        }
        /*list_init_copy_range*/
        {
            list_t* pt_list1 = create_list(list_t<int>);
            list_t* pt_list2 = create_list(list_t<signed int>);
            list_t* pt_listex = create_list(signed);
            if(pt_list1 == NULL || pt_list2 == NULL || pt_listex == NULL)
            {
                return;
            }
            list_init(pt_listex);
            list_init(pt_list2);
            list_push_back(pt_listex, 34);
            list_push_back(pt_listex, -350);
            list_push_back(pt_listex, -300);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 88);
            list_push_back(pt_listex, -888);
            list_push_back(pt_listex, 0);
            list_push_back(pt_listex, 2);
            list_push_back(pt_listex, 9000);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 761);
            list_push_back(pt_listex, 331);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 0);
            list_push_back(pt_listex, 0);
            list_push_back(pt_listex, -1);
            list_push_back(pt_list2, pt_listex);
            list_init_copy_range(pt_list1,
                iterator_advance(list_begin(pt_list2), 2), list_end(pt_list2));
            _printlist_list(pt_list1);
            list_destroy(pt_list1);
            list_destroy(pt_list2);
            list_destroy(pt_listex);
        }
        /*list_destroy        */
        /*list_size           */
        {
            list_t* pt_list = create_list(list_t<int>);
            list_t* pt_listex = create_list(int);
            if(pt_list == NULL || pt_listex == NULL)
            {
                return;
            }
            list_init(pt_list);
            list_init(pt_listex);
            printf("size : %d, empty : %d, max size : %d\n",
                list_size(pt_list), list_empty(pt_list), list_max_size(pt_list));
            list_push_back(pt_listex, 90);
            list_push_back(pt_listex, 34);
            list_push_back(pt_list, pt_listex);
            printf("size : %d, empty : %d, max size : %d\n",
                list_size(pt_list), list_empty(pt_list), list_max_size(pt_list));
            list_destroy(pt_list);
            list_destroy(pt_listex);
        }
        /*list_empty          */
        /*list_max_size       */
        /*list_equal          */
        {
            list_t* pt_list1 = create_list(list_t<int>);
            list_t* pt_list2 = create_list(list_t<int>);
            list_t* pt_listex = create_list(int);
            if(pt_list1 == NULL || pt_list2 == NULL || pt_listex == NULL)
            {
                return;
            }
            list_init(pt_list1);
            list_init(pt_list2);
            list_init(pt_listex);
            _printlist_list(pt_list1);
            _printlist_list(pt_list2);
            printf("equal : %d, not equal : %d\n",
                list_equal(pt_list1, pt_list2), list_not_equal(pt_list1, pt_list2));
            printf("less : %d, less equal : %d\n",
                list_less(pt_list1, pt_list2), list_less_equal(pt_list1, pt_list2));
            printf("great : %d, great equal : %d\n",
                list_great(pt_list1, pt_list2), list_great_equal(pt_list1, pt_list2));
            list_push_back(pt_listex, 100);
            list_push_back(pt_listex, 200);
            list_push_back(pt_list1, pt_listex);
            _printlist_list(pt_list1);
            _printlist_list(pt_list2);
            printf("equal : %d, not equal : %d\n",
                list_equal(pt_list1, pt_list2), list_not_equal(pt_list1, pt_list2));
            printf("less : %d, less equal : %d\n",
                list_less(pt_list1, pt_list2), list_less_equal(pt_list1, pt_list2));
            printf("great : %d, great equal : %d\n",
                list_great(pt_list1, pt_list2), list_great_equal(pt_list1, pt_list2));
            list_push_back(pt_list2, pt_listex);
            _printlist_list(pt_list1);
            _printlist_list(pt_list2);
            printf("equal : %d, not equal : %d\n",
                list_equal(pt_list1, pt_list2), list_not_equal(pt_list1, pt_list2));
            printf("less : %d, less equal : %d\n",
                list_less(pt_list1, pt_list2), list_less_equal(pt_list1, pt_list2));
            printf("great : %d, great equal : %d\n",
                list_great(pt_list1, pt_list2), list_great_equal(pt_list1, pt_list2));
            list_clear(pt_listex);
            list_push_back(pt_listex, -34);
            list_push_back(pt_listex, 28);
            list_push_back(pt_list2, pt_listex);
            _printlist_list(pt_list1);
            _printlist_list(pt_list2);
            printf("equal : %d, not equal : %d\n",
                list_equal(pt_list1, pt_list2), list_not_equal(pt_list1, pt_list2));
            printf("less : %d, less equal : %d\n",
                list_less(pt_list1, pt_list2), list_less_equal(pt_list1, pt_list2));
            printf("great : %d, great equal : %d\n",
                list_great(pt_list1, pt_list2), list_great_equal(pt_list1, pt_list2));
            list_push_back(pt_listex, 98);
            list_push_back(pt_list1, pt_listex);
            _printlist_list(pt_list1);
            _printlist_list(pt_list2);
            printf("equal : %d, not equal : %d\n",
                list_equal(pt_list1, pt_list2), list_not_equal(pt_list1, pt_list2));
            printf("less : %d, less equal : %d\n",
                list_less(pt_list1, pt_list2), list_less_equal(pt_list1, pt_list2));
            printf("great : %d, great equal : %d\n",
                list_great(pt_list1, pt_list2), list_great_equal(pt_list1, pt_list2));
            list_push_back(pt_list2, pt_listex);
            _printlist_list(pt_list1);
            _printlist_list(pt_list2);
            printf("equal : %d, not equal : %d\n",
                list_equal(pt_list1, pt_list2), list_not_equal(pt_list1, pt_list2));
            printf("less : %d, less equal : %d\n",
                list_less(pt_list1, pt_list2), list_less_equal(pt_list1, pt_list2));
            printf("great : %d, great equal : %d\n",
                list_great(pt_list1, pt_list2), list_great_equal(pt_list1, pt_list2));
            list_destroy(pt_list1);
            list_destroy(pt_list2);
            list_destroy(pt_listex);
        }
        /*list_not_equal      */
        /*list_less           */
        /*list_less_equal     */
        /*list_great          */
        /*list_great_equal    */
        /*list_assign         */
        {
            list_t* pt_list1 = create_list(list_t<int>);
            list_t* pt_list2 = create_list(list_t<signed int>);
            list_t* pt_listex = create_list(signed);
            if(pt_list1 == NULL || pt_list2 == NULL || pt_listex == NULL)
            {
                return;
            }
            list_init(pt_listex);
            list_init(pt_list2);
            list_init(pt_list1);
            list_assign(pt_list1, pt_list2);
            _printlist_list(pt_list1);

            list_push_back(pt_listex, 34);
            list_push_back(pt_listex, -350);
            list_push_back(pt_listex, -300);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 88);
            list_push_back(pt_listex, -888);
            list_push_back(pt_listex, 0);
            list_push_back(pt_listex, 2);
            list_push_back(pt_listex, 9000);
            list_push_back(pt_list2, pt_listex);
            list_assign(pt_list1, pt_list2);
            _printlist_list(pt_list1);

            list_clear(pt_list2);
            list_clear(pt_listex);
            list_push_back(pt_listex, 761);
            list_push_back(pt_listex, 331);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 0);
            list_push_back(pt_listex, 0);
            list_push_back(pt_listex, -1);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 777);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 91);
            list_push_back(pt_listex, -17);
            list_push_back(pt_listex, -22);
            list_push_back(pt_listex, -9);
            list_push_back(pt_listex, 11);
            list_push_back(pt_list2, pt_listex);
            list_assign(pt_list1, pt_list2);
            _printlist_list(pt_list1);

            list_clear(pt_list2);
            list_clear(pt_listex);
            list_push_back(pt_listex, 88);
            list_push_back(pt_listex, 100);
            list_push_back(pt_listex, 300);
            list_push_back(pt_list2, pt_listex);
            list_assign(pt_list1, pt_list2);
            _printlist_list(pt_list1);

            list_clear(pt_list2);
            list_assign(pt_list1, pt_list2);
            _printlist_list(pt_list1);

            list_destroy(pt_list1);
            list_destroy(pt_list2);
            list_destroy(pt_listex);
        }
        /*list_assign_elem    */
        {
            list_t* pt_list = create_list(list_t<int>);
            list_t* pt_listex = create_list(int);
            if(pt_list == NULL || pt_listex == NULL)
            {
                return;
            }
            list_init(pt_list);
            list_init(pt_listex);
            list_assign_elem(pt_list, 0, pt_listex);
            _printlist_list(pt_list);

            list_push_back(pt_listex, 88);
            list_push_back(pt_listex, -4);
            list_push_back(pt_listex, -31234);
            list_push_back(pt_listex, 0);
            list_assign_elem(pt_list, 4, pt_listex);
            _printlist_list(pt_list);

            list_clear(pt_listex);
            list_push_back(pt_listex, 76031);
            list_push_back(pt_listex, 98123);
            list_assign_elem(pt_list, 13, pt_listex);
            _printlist_list(pt_list);

            list_clear(pt_listex);
            list_push_back(pt_listex, 90);
            list_push_back(pt_listex, 342);
            list_push_back(pt_listex, -8);
            list_assign_elem(pt_list, 2, pt_listex);
            _printlist_list(pt_list);

            list_assign_elem(pt_list, 0, pt_listex);
            _printlist_list(pt_list);

            list_destroy(pt_list);
            list_destroy(pt_listex);
        }
        /*list_assign_range   */
        {
            list_t* pt_list1 = create_list(list_t<int>);
            list_t* pt_list2 = create_list(list_t<signed int>);
            list_t* pt_listex = create_list(signed);
            if(pt_list1 == NULL || pt_list2 == NULL || pt_listex == NULL)
            {
                return;
            }
            list_init(pt_listex);
            list_init(pt_list2);
            list_init(pt_list1);

            list_push_back(pt_listex, 34);
            list_push_back(pt_listex, -350);
            list_push_back(pt_listex, -300);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 88);
            list_push_back(pt_listex, -888);
            list_push_back(pt_listex, 0);
            list_push_back(pt_listex, 2);
            list_push_back(pt_listex, 9000);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 761);
            list_push_back(pt_listex, 331);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 0);
            list_push_back(pt_listex, 0);
            list_push_back(pt_listex, -1);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 777);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 91);
            list_push_back(pt_listex, -17);
            list_push_back(pt_listex, -22);
            list_push_back(pt_listex, -9);
            list_push_back(pt_listex, 11);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 88);
            list_push_back(pt_listex, 100);
            list_push_back(pt_listex, 300);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 88);
            list_push_back(pt_listex, -4);
            list_push_back(pt_listex, -31234);
            list_push_back(pt_listex, 0);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 76031);
            list_push_back(pt_listex, 98123);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 90);
            list_push_back(pt_listex, 342);
            list_push_back(pt_listex, -8);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 1024);
            list_push_back(pt_listex, 512);
            list_push_back(pt_listex, 256);
            list_push_back(pt_listex, 128);
            list_push_back(pt_listex, 64);
            list_push_back(pt_listex, 32);
            list_push_back(pt_listex, 16);
            list_push_back(pt_listex, 8);
            list_push_back(pt_listex, 4);
            list_push_back(pt_listex, 2);
            list_push_back(pt_listex, 1);
            list_push_back(pt_list2, pt_listex);
            _printlist_list(pt_list2);

            list_assign_range(pt_list1, list_begin(pt_list2), list_begin(pt_list2));
            _printlist_list(pt_list1);
            list_assign_range(pt_list1,
                list_begin(pt_list2), iterator_advance(list_begin(pt_list2), 2));
            _printlist_list(pt_list1);
            list_assign_range(pt_list1, iterator_next(list_begin(pt_list2)),
                iterator_advance(list_end(pt_list2), -2));
            _printlist_list(pt_list1);
            list_assign_range(pt_list1,
                iterator_advance(list_end(pt_list2), -2), list_end(pt_list2));
            _printlist_list(pt_list1);
            list_assign_range(pt_list1, list_end(pt_list2), list_end(pt_list2));
            _printlist_list(pt_list1);

            list_destroy(pt_list1);
            list_destroy(pt_list2);
            list_destroy(pt_listex);
        }
        /*list_swap           */
        {
            list_t* pt_list1 = create_list(list_t<int>);
            list_t* pt_list2 = create_list(list_t<signed int>);
            list_t* pt_listex = create_list(signed);
            if(pt_list1 == NULL || pt_list2 == NULL || pt_listex == NULL)
            {
                return;
            }
            list_init(pt_listex);
            list_init(pt_list2);
            list_init(pt_list1);
            _printlist_list(pt_list1);
            _printlist_list(pt_list2);
            list_swap(pt_list1, pt_list2);
            _printlist_list(pt_list1);
            _printlist_list(pt_list2);

            list_push_back(pt_listex, 34);
            list_push_back(pt_listex, -350);
            list_push_back(pt_listex, -300);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 88);
            list_push_back(pt_listex, -888);
            list_push_back(pt_listex, 0);
            list_push_back(pt_listex, 2);
            list_push_back(pt_listex, 9000);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 761);
            list_push_back(pt_listex, 331);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 0);
            list_push_back(pt_listex, 0);
            list_push_back(pt_listex, -1);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 777);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 91);
            list_push_back(pt_listex, -17);
            list_push_back(pt_listex, -22);
            list_push_back(pt_listex, -9);
            list_push_back(pt_listex, 11);
            list_push_back(pt_list2, pt_listex);
            _printlist_list(pt_list1);
            _printlist_list(pt_list2);
            list_swap(pt_list1, pt_list2);
            _printlist_list(pt_list1);
            _printlist_list(pt_list2);

            list_clear(pt_listex);
            list_push_back(pt_listex, 88);
            list_push_back(pt_listex, 100);
            list_push_back(pt_listex, 300);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 88);
            list_push_back(pt_listex, -4);
            list_push_back(pt_listex, -31234);
            list_push_back(pt_listex, 0);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 76031);
            list_push_back(pt_listex, 98123);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 90);
            list_push_back(pt_listex, 342);
            list_push_back(pt_listex, -8);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 1024);
            list_push_back(pt_listex, 512);
            list_push_back(pt_listex, 256);
            list_push_back(pt_listex, 128);
            list_push_back(pt_listex, 64);
            list_push_back(pt_listex, 32);
            list_push_back(pt_listex, 16);
            list_push_back(pt_listex, 8);
            list_push_back(pt_listex, 4);
            list_push_back(pt_listex, 2);
            list_push_back(pt_listex, 1);
            list_push_back(pt_list2, pt_listex);
            _printlist_list(pt_list1);
            _printlist_list(pt_list2);
            list_swap(pt_list1, pt_list2);
            _printlist_list(pt_list1);
            _printlist_list(pt_list2);

            list_clear(pt_list2);
            _printlist_list(pt_list1);
            _printlist_list(pt_list2);
            list_swap(pt_list1, pt_list2);
            _printlist_list(pt_list1);
            _printlist_list(pt_list2);

            list_clear(pt_list2);
            _printlist_list(pt_list1);
            _printlist_list(pt_list2);
            list_swap(pt_list1, pt_list2);
            _printlist_list(pt_list1);
            _printlist_list(pt_list2);

            list_destroy(pt_list1);
            list_destroy(pt_list2);
            list_destroy(pt_listex);
        }
        /*list_front          */
        {
            list_t* pt_list = create_list(list_t<int>);
            list_t* pt_listex = create_list(int);
            if(pt_list == NULL || pt_listex == NULL)
            {
                return;
            }
            list_init(pt_list);
            list_init(pt_listex);
            if(list_front(pt_list) != NULL)
            {
                list_assign_elem(list_front(pt_list), 4, 90);
            }
            if(list_back(pt_list) != NULL)
            {
                list_assign_elem(list_back(pt_list), 8, -10);
            }
            _printlist_list(pt_list);

            list_push_back(pt_listex, 8);
            list_push_back(pt_listex, 121);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 0);
            list_push_back(pt_listex, -4);
            list_push_back(pt_listex, -8);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 1000);
            list_push_back(pt_listex, 100);
            list_push_back(pt_listex, 10);
            list_push_back(pt_listex, 1);
            list_push_back(pt_list, pt_listex);
            _printlist_list(pt_list);
            if(list_front(pt_list) != NULL)
            {
                list_assign_elem(list_front(pt_list), 4, 90);
            }
            if(list_back(pt_list) != NULL)
            {
                list_assign_elem(list_back(pt_list), 8, -10);
            }
            _printlist_list(pt_list);

            list_destroy(pt_list);
            list_destroy(pt_listex);
        }
        /*list_back           */
        /*list_begin          */
        /*list_end            */
        /*list_insert         */
        {
            list_t* pt_list = create_list(list_t<int>);
            list_t* pt_listex = create_list(int);
            if(pt_list == NULL || pt_listex == NULL)
            {
                return;
            }
            list_init(pt_list);
            list_init(pt_listex);

            list_push_back(pt_listex, 8);
            list_push_back(pt_listex, 121);
            list_insert(pt_list, list_begin(pt_list), pt_listex);

            list_clear(pt_listex);
            list_push_back(pt_listex, 0);
            list_push_back(pt_listex, -4);
            list_push_back(pt_listex, -8);
            list_insert(pt_list, list_end(pt_list), pt_listex);

            list_clear(pt_listex);
            list_push_back(pt_listex, 1000);
            list_push_back(pt_listex, 100);
            list_push_back(pt_listex, 10);
            list_push_back(pt_listex, 1);
            list_insert(pt_list, iterator_next(list_begin(pt_list)), pt_listex);

            list_clear(pt_listex);
            list_push_back(pt_listex, -555);
            list_insert(pt_list, list_begin(pt_list), pt_listex);
            _printlist_list(pt_list);

            list_destroy(pt_list);
            list_destroy(pt_listex);
        }
        /*list_insert_n       */
        {
            list_t* pt_list = create_list(list_t<int>);
            list_t* pt_listex = create_list(int);
            if(pt_list == NULL || pt_listex == NULL)
            {
                return;
            }
            list_init(pt_list);
            list_init(pt_listex);

            list_push_back(pt_listex, 8);
            list_push_back(pt_listex, 121);
            list_insert_n(pt_list, list_begin(pt_list), 2, pt_listex);

            list_clear(pt_listex);
            list_push_back(pt_listex, 0);
            list_push_back(pt_listex, -4);
            list_push_back(pt_listex, -8);
            list_insert_n(pt_list, list_end(pt_list), 4, pt_listex);

            list_clear(pt_listex);
            list_push_back(pt_listex, 1000);
            list_push_back(pt_listex, 100);
            list_push_back(pt_listex, 10);
            list_push_back(pt_listex, 1);
            list_insert_n(pt_list, iterator_next(list_begin(pt_list)), 5, pt_listex);

            list_clear(pt_listex);
            list_push_back(pt_listex, -555);
            list_insert_n(pt_list, list_begin(pt_list), 2, pt_listex);

            list_clear(pt_listex);
            list_push_back(pt_listex, 9999);
            list_insert_n(pt_list, iterator_advance(list_end(pt_list), -3), 0, pt_listex);
            _printlist_list(pt_list);

            list_destroy(pt_list);
            list_destroy(pt_listex);
        }
        /*list_insert_range   */
        {
            list_t* pt_list1 = create_list(list_t<int>);
            list_t* pt_list2 = create_list(list_t<signed int>);
            list_t* pt_listex = create_list(signed);
            if(pt_list1 == NULL || pt_list2 == NULL || pt_listex == NULL)
            {
                return;
            }
            list_init(pt_listex);
            list_init(pt_list2);
            list_init(pt_list1);

            list_push_back(pt_listex, 34);
            list_push_back(pt_listex, -350);
            list_push_back(pt_listex, -300);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 88);
            list_push_back(pt_listex, -888);
            list_push_back(pt_listex, 0);
            list_push_back(pt_listex, 2);
            list_push_back(pt_listex, 9000);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 761);
            list_push_back(pt_listex, 331);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 0);
            list_push_back(pt_listex, 0);
            list_push_back(pt_listex, -1);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 777);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 91);
            list_push_back(pt_listex, -17);
            list_push_back(pt_listex, -22);
            list_push_back(pt_listex, -9);
            list_push_back(pt_listex, 11);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 88);
            list_push_back(pt_listex, 100);
            list_push_back(pt_listex, 300);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 88);
            list_push_back(pt_listex, -4);
            list_push_back(pt_listex, -31234);
            list_push_back(pt_listex, 0);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 76031);
            list_push_back(pt_listex, 98123);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 90);
            list_push_back(pt_listex, 342);
            list_push_back(pt_listex, -8);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 1024);
            list_push_back(pt_listex, 512);
            list_push_back(pt_listex, 256);
            list_push_back(pt_listex, 128);
            list_push_back(pt_listex, 64);
            list_push_back(pt_listex, 32);
            list_push_back(pt_listex, 16);
            list_push_back(pt_listex, 8);
            list_push_back(pt_listex, 4);
            list_push_back(pt_listex, 2);
            list_push_back(pt_listex, 1);
            list_push_back(pt_list2, pt_listex);
            _printlist_list(pt_list2);

            list_insert_range(pt_list1, list_begin(pt_list1),
                list_begin(pt_list2), list_begin(pt_list2));
            _printlist_list(pt_list1);

            list_insert_range(pt_list1, list_end(pt_list1),
                list_begin(pt_list2), iterator_advance(list_begin(pt_list2), 3));
            _printlist_list(pt_list1);

            list_insert_range(pt_list1, iterator_next(list_begin(pt_list1)),
                iterator_advance(list_begin(pt_list2), 4),
                iterator_advance(list_begin(pt_list2), 6));
            _printlist_list(pt_list1);

            list_insert_range(pt_list1, iterator_advance(list_end(pt_list1), -2),
                iterator_advance(list_begin(pt_list2), 4), list_end(pt_list2));
            _printlist_list(pt_list1);

            list_insert_range(pt_list1, iterator_advance(list_end(pt_list1), -2),
                list_end(pt_list2), list_end(pt_list2));
            _printlist_list(pt_list1);

            list_destroy(pt_list1);
            list_destroy(pt_list2);
            list_destroy(pt_listex);
        }
        /*list_push_back      */
        {
            list_t* pt_list = create_list(list_t<int>);
            list_t* pt_listex = create_list(signed);
            if(pt_list == NULL || pt_listex == NULL)
            {
                return;
            }
            list_init(pt_listex);
            list_init(pt_list);

            list_push_back(pt_listex, 34);
            list_push_back(pt_listex, -350);
            list_push_back(pt_listex, -300);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 88);
            list_push_back(pt_listex, -888);
            list_push_back(pt_listex, 0);
            list_push_back(pt_listex, 2);
            list_push_back(pt_listex, 9000);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 761);
            list_push_back(pt_listex, 331);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 0);
            list_push_back(pt_listex, 0);
            list_push_back(pt_listex, -1);
            list_push_back(pt_list, pt_listex);
            _printlist_list(pt_list);
            while(!list_empty(pt_list))
            {
                list_pop_front(pt_list);
            }
            _printlist_list(pt_list);

            list_clear(pt_listex);
            list_push_back(pt_listex, 777);
            list_push_front(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 91);
            list_push_back(pt_listex, -17);
            list_push_back(pt_listex, -22);
            list_push_back(pt_listex, -9);
            list_push_back(pt_listex, 11);
            list_push_front(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 88);
            list_push_back(pt_listex, 100);
            list_push_back(pt_listex, 300);
            list_push_front(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 88);
            list_push_back(pt_listex, -4);
            list_push_back(pt_listex, -31234);
            list_push_back(pt_listex, 0);
            list_push_front(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 76031);
            list_push_back(pt_listex, 98123);
            list_push_front(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 90);
            list_push_back(pt_listex, 342);
            list_push_back(pt_listex, -8);
            list_push_front(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 1024);
            list_push_back(pt_listex, 512);
            list_push_back(pt_listex, 256);
            list_push_back(pt_listex, 128);
            list_push_back(pt_listex, 64);
            list_push_back(pt_listex, 32);
            list_push_back(pt_listex, 16);
            list_push_back(pt_listex, 8);
            list_push_back(pt_listex, 4);
            list_push_back(pt_listex, 2);
            list_push_back(pt_listex, 1);
            list_push_front(pt_list, pt_listex);
            _printlist_list(pt_list);
            while(!list_empty(pt_list))
            {
                list_pop_back(pt_list);
            }
            _printlist_list(pt_list);

            list_destroy(pt_list);
            list_destroy(pt_listex);
        }
        /*list_pop_back       */
        /*list_push_front     */
        /*list_pop_front      */
        /*list_erase          */
        {
            list_t* pt_list = create_list(list_t<int>);
            list_t* pt_listex = create_list(signed);
            if(pt_list == NULL || pt_listex == NULL)
            {
                return;
            }
            list_init(pt_listex);
            list_init(pt_list);

            list_push_back(pt_listex, 34);
            list_push_back(pt_listex, -350);
            list_push_back(pt_listex, -300);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 88);
            list_push_back(pt_listex, -888);
            list_push_back(pt_listex, 0);
            list_push_back(pt_listex, 2);
            list_push_back(pt_listex, 9000);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 761);
            list_push_back(pt_listex, 331);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 0);
            list_push_back(pt_listex, 0);
            list_push_back(pt_listex, -1);
            list_push_back(pt_list, pt_listex);
            _printlist_list(pt_list);

            list_erase(pt_list, iterator_next(list_begin(pt_list)));
            _printlist_list(pt_list);
            list_erase(pt_list, iterator_prev(list_end(pt_list)));
            _printlist_list(pt_list);
            list_erase(pt_list, list_begin(pt_list));
            _printlist_list(pt_list);
            list_erase(pt_list, list_begin(pt_list));
            _printlist_list(pt_list);

            list_destroy(pt_list);
            list_destroy(pt_listex);
        }
        /*list_erase_range    */
        {
            list_t* pt_list = create_list(list_t<int>);
            list_t* pt_listex = create_list(signed);
            if(pt_list == NULL || pt_listex == NULL)
            {
                return;
            }
            list_init(pt_listex);
            list_init(pt_list);

            list_push_back(pt_listex, 34);
            list_push_back(pt_listex, -350);
            list_push_back(pt_listex, -300);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 88);
            list_push_back(pt_listex, -888);
            list_push_back(pt_listex, 0);
            list_push_back(pt_listex, 2);
            list_push_back(pt_listex, 9000);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 761);
            list_push_back(pt_listex, 331);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 0);
            list_push_back(pt_listex, 0);
            list_push_back(pt_listex, -1);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 777);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 91);
            list_push_back(pt_listex, -17);
            list_push_back(pt_listex, -22);
            list_push_back(pt_listex, -9);
            list_push_back(pt_listex, 11);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 88);
            list_push_back(pt_listex, 100);
            list_push_back(pt_listex, 300);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 88);
            list_push_back(pt_listex, -4);
            list_push_back(pt_listex, -31234);
            list_push_back(pt_listex, 0);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 76031);
            list_push_back(pt_listex, 98123);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 90);
            list_push_back(pt_listex, 342);
            list_push_back(pt_listex, -8);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 1024);
            list_push_back(pt_listex, 512);
            list_push_back(pt_listex, 256);
            list_push_back(pt_listex, 128);
            list_push_back(pt_listex, 64);
            list_push_back(pt_listex, 32);
            list_push_back(pt_listex, 16);
            list_push_back(pt_listex, 8);
            list_push_back(pt_listex, 4);
            list_push_back(pt_listex, 2);
            list_push_back(pt_listex, 1);
            list_push_back(pt_list, pt_listex);
            _printlist_list(pt_list);

            list_erase_range(pt_list, list_begin(pt_list), list_begin(pt_list));
            _printlist_list(pt_list);
            list_erase_range(pt_list, list_begin(pt_list),
                iterator_advance(list_begin(pt_list), 2));
            _printlist_list(pt_list);
            list_erase_range(pt_list, iterator_next(list_begin(pt_list)),
                iterator_advance(list_begin(pt_list), 3));
            _printlist_list(pt_list);
            list_erase_range(pt_list,
                iterator_advance(list_end(pt_list), -3), list_end(pt_list));
            _printlist_list(pt_list);
            list_erase_range(pt_list, list_begin(pt_list), list_end(pt_list));
            _printlist_list(pt_list);

            list_destroy(pt_list);
            list_destroy(pt_listex);
        }
        /*list_remove         */
        {
            list_t* pt_list = create_list(list_t<int>);
            list_t* pt_listex = create_list(signed);
            if(pt_list == NULL || pt_listex == NULL)
            {
                return;
            }
            list_init(pt_listex);
            list_init(pt_list);

            list_push_back(pt_listex, 34);
            list_push_back(pt_listex, -350);
            list_push_back(pt_listex, -300);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 88);
            list_push_back(pt_listex, -888);
            list_push_back(pt_listex, 0);
            list_push_back(pt_listex, 2);
            list_push_back(pt_listex, 9000);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 761);
            list_push_back(pt_listex, 331);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 0);
            list_push_back(pt_listex, 0);
            list_push_back(pt_listex, -1);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 777);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 91);
            list_push_back(pt_listex, -17);
            list_push_back(pt_listex, -22);
            list_push_back(pt_listex, -9);
            list_push_back(pt_listex, 11);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 88);
            list_push_back(pt_listex, 100);
            list_push_back(pt_listex, 300);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 88);
            list_push_back(pt_listex, -4);
            list_push_back(pt_listex, -31234);
            list_push_back(pt_listex, 0);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 76031);
            list_push_back(pt_listex, 98123);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 90);
            list_push_back(pt_listex, 342);
            list_push_back(pt_listex, -8);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 1024);
            list_push_back(pt_listex, 512);
            list_push_back(pt_listex, 256);
            list_push_back(pt_listex, 128);
            list_push_back(pt_listex, 64);
            list_push_back(pt_listex, 32);
            list_push_back(pt_listex, 16);
            list_push_back(pt_listex, 8);
            list_push_back(pt_listex, 4);
            list_push_back(pt_listex, 2);
            list_push_back(pt_listex, 1);
            list_push_back(pt_list, pt_listex);

            list_assign_elem(pt_listex, 10, -1);
            list_insert(pt_list, list_begin(pt_list), pt_listex);
            list_insert_n(pt_list, iterator_advance(list_begin(pt_list), 5), 3, pt_listex);
            _printlist_list(pt_list);

            list_remove(pt_list, pt_listex);
            _printlist_list(pt_list);
            list_assign_elem(pt_listex, 10, 1);
            list_remove(pt_list, pt_listex);
            _printlist_list(pt_list);

            list_destroy(pt_list);
            list_destroy(pt_listex);
        }
        /*list_remove_if      */
        {
            list_t* pt_list = create_list(list_t<int>);
            list_t* pt_listex = create_list(signed);
            if(pt_list == NULL || pt_listex == NULL)
            {
                return;
            }
            list_init(pt_listex);
            list_init(pt_list);

            list_push_back(pt_listex, 34);
            list_push_back(pt_listex, -350);
            list_push_back(pt_listex, -300);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 88);
            list_push_back(pt_listex, -888);
            list_push_back(pt_listex, 0);
            list_push_back(pt_listex, 2);
            list_push_back(pt_listex, 9000);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 761);
            list_push_back(pt_listex, 331);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 0);
            list_push_back(pt_listex, 0);
            list_push_back(pt_listex, -1);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 777);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 91);
            list_push_back(pt_listex, -17);
            list_push_back(pt_listex, -22);
            list_push_back(pt_listex, -9);
            list_push_back(pt_listex, 11);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 88);
            list_push_back(pt_listex, 100);
            list_push_back(pt_listex, 300);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 88);
            list_push_back(pt_listex, -4);
            list_push_back(pt_listex, -31234);
            list_push_back(pt_listex, 0);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 76031);
            list_push_back(pt_listex, 98123);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 90);
            list_push_back(pt_listex, 342);
            list_push_back(pt_listex, -8);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 1024);
            list_push_back(pt_listex, 512);
            list_push_back(pt_listex, 256);
            list_push_back(pt_listex, 128);
            list_push_back(pt_listex, 64);
            list_push_back(pt_listex, 32);
            list_push_back(pt_listex, 16);
            list_push_back(pt_listex, 8);
            list_push_back(pt_listex, 4);
            list_push_back(pt_listex, 2);
            list_push_back(pt_listex, 1);
            list_push_back(pt_list, pt_listex);
            _printlist_list(pt_list);

            list_remove_if(pt_list, _list_remove_pre);
            _printlist_list(pt_list);
            list_remove_if(pt_list, _list_remove_pre);
            _printlist_list(pt_list);

            list_destroy(pt_list);
            list_destroy(pt_listex);
        }
        /*list_resize         */
        {
            list_t* pt_list = create_list(list_t<int>);
            if(pt_list == NULL)
            {
                return;
            }
            list_init(pt_list);
            list_resize(pt_list, 0);
            _printlist_list(pt_list);
            list_resize(pt_list, 3);
            _printlist_list(pt_list);
            list_resize(pt_list, 8);
            _printlist_list(pt_list);
            list_resize(pt_list, 5);
            _printlist_list(pt_list);
            list_resize(pt_list, 0);
            _printlist_list(pt_list);
            list_destroy(pt_list);
        }
        /*list_resize_elem    */
        {
            list_t* pt_list = create_list(list_t<int>);
            list_t* pt_listex = create_list(signed);
            if(pt_list == NULL || pt_listex == NULL)
            {
                return;
            }
            list_init(pt_listex);
            list_init(pt_list);

            list_resize_elem(pt_list, 0, pt_listex);
            _printlist_list(pt_list);

            list_push_back(pt_listex, 34);
            list_push_back(pt_listex, -350);
            list_push_back(pt_listex, -300);
            list_resize_elem(pt_list, 4, pt_listex);
            _printlist_list(pt_list);

            list_clear(pt_listex);
            list_push_back(pt_listex, 88);
            list_push_back(pt_listex, -888);
            list_push_back(pt_listex, 0);
            list_push_back(pt_listex, 2);
            list_push_back(pt_listex, 9000);
            list_resize_elem(pt_list, 9, pt_listex);
            _printlist_list(pt_list);

            list_clear(pt_listex);
            list_push_back(pt_listex, 761);
            list_push_back(pt_listex, 331);
            list_resize_elem(pt_list, 7, pt_listex);
            _printlist_list(pt_list);

            list_clear(pt_listex);
            list_push_back(pt_listex, 0);
            list_push_back(pt_listex, 0);
            list_push_back(pt_listex, -1);
            list_resize_elem(pt_list, 0, pt_listex);
            _printlist_list(pt_list);

            list_clear(pt_list);
            list_clear(pt_list);
            _printlist_list(pt_list);

            list_destroy(pt_list);
            list_destroy(pt_listex);
        }
        /*list_clear          */
        /*list_unique         */
        {
            list_t* pt_list = create_list(list_t<int>);
            list_t* pt_listex = create_list(signed);
            if(pt_list == NULL || pt_listex == NULL)
            {
                return;
            }
            list_init(pt_listex);
            list_init(pt_list);

            list_push_back(pt_listex, 34);
            list_push_back(pt_listex, -350);
            list_push_back(pt_listex, -300);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 88);
            list_push_back(pt_listex, -888);
            list_push_back(pt_listex, 0);
            list_push_back(pt_listex, 2);
            list_push_back(pt_listex, 9000);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 761);
            list_push_back(pt_listex, 331);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 0);
            list_push_back(pt_listex, 0);
            list_push_back(pt_listex, -1);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 777);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 91);
            list_push_back(pt_listex, -17);
            list_push_back(pt_listex, -22);
            list_push_back(pt_listex, -9);
            list_push_back(pt_listex, 11);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 88);
            list_push_back(pt_listex, 100);
            list_push_back(pt_listex, 300);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 88);
            list_push_back(pt_listex, -4);
            list_push_back(pt_listex, -31234);
            list_push_back(pt_listex, 0);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 76031);
            list_push_back(pt_listex, 98123);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 90);
            list_push_back(pt_listex, 342);
            list_push_back(pt_listex, -8);
            list_push_back(pt_list, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 1024);
            list_push_back(pt_listex, 512);
            list_push_back(pt_listex, 256);
            list_push_back(pt_listex, 128);
            list_push_back(pt_listex, 64);
            list_push_back(pt_listex, 32);
            list_push_back(pt_listex, 16);
            list_push_back(pt_listex, 8);
            list_push_back(pt_listex, 4);
            list_push_back(pt_listex, 2);
            list_push_back(pt_listex, 1);
            list_push_back(pt_list, pt_listex);

            list_assign_elem(pt_listex, 10, -1);
            list_insert(pt_list, list_begin(pt_list), pt_listex);
            list_insert_n(pt_list, iterator_advance(list_begin(pt_list), 5), 3, pt_listex);
            _printlist_list(pt_list);

            list_unique(pt_list);
            _printlist_list(pt_list);

            list_unique_if(pt_list, _list_unique_pre);
            _printlist_list(pt_list);

            list_destroy(pt_list);
            list_destroy(pt_listex);
        }
        /*list_unique_if      */
        /*list_splice         */
        {
            list_t* pt_list1 = create_list(list_t<int>);
            list_t* pt_list2 = create_list(list_t<signed int>);
            list_t* pt_listex = create_list(signed);
            if(pt_list1 == NULL || pt_list2 == NULL || pt_listex == NULL)
            {
                return;
            }
            list_init(pt_listex);
            list_init(pt_list2);
            list_init(pt_list1);

            list_splice(pt_list1, list_begin(pt_list1), pt_list2);
            _printlist_list(pt_list1);
            _printlist_list(pt_list2);

            list_push_back(pt_listex, 34);
            list_push_back(pt_listex, -350);
            list_push_back(pt_listex, -300);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 88);
            list_push_back(pt_listex, -888);
            list_push_back(pt_listex, 0);
            list_push_back(pt_listex, 2);
            list_push_back(pt_listex, 9000);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 761);
            list_push_back(pt_listex, 331);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 0);
            list_push_back(pt_listex, 0);
            list_push_back(pt_listex, -1);
            list_push_back(pt_list2, pt_listex);
            _printlist_list(pt_list1);
            _printlist_list(pt_list2);
            list_splice(pt_list1, list_begin(pt_list1), pt_list2);
            _printlist_list(pt_list1);
            _printlist_list(pt_list2);

            list_clear(pt_listex);
            list_push_back(pt_listex, 777);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 91);
            list_push_back(pt_listex, -17);
            list_push_back(pt_listex, -22);
            list_push_back(pt_listex, -9);
            list_push_back(pt_listex, 11);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 88);
            list_push_back(pt_listex, 100);
            list_push_back(pt_listex, 300);
            list_push_back(pt_list2, pt_listex);
            _printlist_list(pt_list1);
            _printlist_list(pt_list2);
            list_splice(pt_list1, list_end(pt_list1), pt_list2);
            _printlist_list(pt_list1);
            _printlist_list(pt_list2);

            list_clear(pt_listex);
            list_push_back(pt_listex, 88);
            list_push_back(pt_listex, -4);
            list_push_back(pt_listex, -31234);
            list_push_back(pt_listex, 0);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 76031);
            list_push_back(pt_listex, 98123);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 90);
            list_push_back(pt_listex, 342);
            list_push_back(pt_listex, -8);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 1024);
            list_push_back(pt_listex, 512);
            list_push_back(pt_listex, 256);
            list_push_back(pt_listex, 128);
            list_push_back(pt_listex, 64);
            list_push_back(pt_listex, 32);
            list_push_back(pt_listex, 16);
            list_push_back(pt_listex, 8);
            list_push_back(pt_listex, 4);
            list_push_back(pt_listex, 2);
            list_push_back(pt_listex, 1);
            list_push_back(pt_list2, pt_listex);
            _printlist_list(pt_list1);
            _printlist_list(pt_list2);
            list_splice(pt_list1, iterator_advance(list_begin(pt_list1), 3), pt_list2);
            _printlist_list(pt_list1);
            _printlist_list(pt_list2);

            list_destroy(pt_list1);
            list_destroy(pt_list2);
            list_destroy(pt_listex);
        }
        /*list_splice_pos     */
        {
            list_t* pt_list1 = create_list(list_t<int>);
            list_t* pt_list2 = create_list(list_t<signed int>);
            list_t* pt_listex = create_list(signed);
            if(pt_list1 == NULL || pt_list2 == NULL || pt_listex == NULL)
            {
                return;
            }
            list_init(pt_listex);
            list_init(pt_list2);
            list_init(pt_list1);

            list_push_back(pt_listex, 34);
            list_push_back(pt_listex, -350);
            list_push_back(pt_listex, -300);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 88);
            list_push_back(pt_listex, -888);
            list_push_back(pt_listex, 0);
            list_push_back(pt_listex, 2);
            list_push_back(pt_listex, 9000);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 761);
            list_push_back(pt_listex, 331);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 0);
            list_push_back(pt_listex, 0);
            list_push_back(pt_listex, -1);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 777);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 91);
            list_push_back(pt_listex, -17);
            list_push_back(pt_listex, -22);
            list_push_back(pt_listex, -9);
            list_push_back(pt_listex, 11);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 88);
            list_push_back(pt_listex, 100);
            list_push_back(pt_listex, 300);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 88);
            list_push_back(pt_listex, -4);
            list_push_back(pt_listex, -31234);
            list_push_back(pt_listex, 0);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 76031);
            list_push_back(pt_listex, 98123);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 90);
            list_push_back(pt_listex, 342);
            list_push_back(pt_listex, -8);
            list_push_back(pt_list2, pt_listex);
            list_clear(pt_listex);
            list_push_back(pt_listex, 1024);
            list_push_back(pt_listex, 512);
            list_push_back(pt_listex, 256);
            list_push_back(pt_listex, 128);
            list_push_back(pt_listex, 64);
            list_push_back(pt_listex, 32);
            list_push_back(pt_listex, 16);
            list_push_back(pt_listex, 8);
            list_push_back(pt_listex, 4);
            list_push_back(pt_listex, 2);
            list_push_back(pt_listex, 1);
            list_push_back(pt_list2, pt_listex);
            _printlist_list(pt_list1);
            _printlist_list(pt_list2);

            list_splice_pos(pt_list1, list_begin(pt_list1),
                pt_list2, list_begin(pt_list2));
            _printlist_list(pt_list1);
            _printlist_list(pt_list2);
            list_splice_pos(pt_list1, list_begin(pt_list1),
                pt_list2, iterator_next(list_begin(pt_list2)));
            _printlist_list(pt_list1);
            _printlist_list(pt_list2);
            list_splice_pos(pt_list1, list_end(pt_list1),
                pt_list2, iterator_prev(list_end(pt_list2)));
            _printlist_list(pt_list1);
            _printlist_list(pt_list2);
            list_splice_pos(pt_list1, iterator_next(list_begin(pt_list1)),
                pt_list2, list_begin(pt_list2));
            _printlist_list(pt_list1);
            _printlist_list(pt_list2);

            list_splice_range(pt_list1, list_begin(pt_list1),
                pt_list2, list_begin(pt_list2), list_begin(pt_list2));
            _printlist_list(pt_list1);
            _printlist_list(pt_list2);
            list_splice_range(pt_list1, list_begin(pt_list1),
                pt_list2, list_begin(pt_list2), iterator_advance(list_begin(pt_list2), 2));
            _printlist_list(pt_list1);
            _printlist_list(pt_list2);
            list_splice_range(pt_list1, list_end(pt_list1),
                pt_list2, iterator_prev(list_end(pt_list2)), list_end(pt_list2));
            _printlist_list(pt_list1);
            _printlist_list(pt_list2);
            list_splice_range(pt_list1, iterator_advance(list_begin(pt_list1), 3), pt_list2,
                iterator_next(list_begin(pt_list2)), iterator_prev(list_end(pt_list2)));
            _printlist_list(pt_list1);
            _printlist_list(pt_list2);
            list_splice_range(pt_list1, list_begin(pt_list1),
                pt_list2, list_begin(pt_list2), list_end(pt_list2));
            _printlist_list(pt_list1);
            _printlist_list(pt_list2);

            list_destroy(pt_list1);
            list_destroy(pt_list2);
            list_destroy(pt_listex);
        }
        /*list_splice_range   */
        /*list_sort           */
        {
            list_t* pt_list = create_list(list_t<int>);
            list_t* pt_listex = create_list(int);
            int n_count;
            int n_countex;
            int i,j;
            if(pt_list == NULL || pt_listex == NULL)
            {
                return;
            }
            list_init(pt_list);
            list_init(pt_listex);

            srand((unsigned)time(NULL));
            n_count = rand() % 100;
            for(i = 0; i < n_count; ++i)
            {
                srand((unsigned)time(NULL) + rand());
                n_countex = rand() % 100;
                list_clear(pt_listex);
                for(j = 0; j < n_countex; ++j)
                {
                    list_push_back(pt_listex, rand() - rand());
                }
                list_push_back(pt_list, pt_listex);
            }
            _printlist_list(pt_list);
            list_sort(pt_list);
            _printlist_list(pt_list);
            list_sort_if(pt_list, _list_sort_pre);
            _printlist_list(pt_list);

            list_destroy(pt_list);
            list_destroy(pt_listex);
        }
        /*list_sort_if        */
        /*list_merge          */
        {
            list_t* pt_list1 = create_list(list_t<int>);
            list_t* pt_list2 = create_list(list_t<int>);
            list_t* pt_listex = create_list(int);
            int n_count;
            int n_countex;
            int i,j;
            if(pt_list1 == NULL || pt_list2 == NULL || pt_listex == NULL)
            {
                return;
            }
            list_init(pt_list1);
            list_init(pt_list2);
            list_init(pt_listex);

            srand((unsigned)time(NULL));
            n_count = rand() % 100;
            for(i = 0; i < n_count; ++i)
            {
                srand((unsigned)time(NULL) + rand());
                n_countex = rand() % 100;
                list_clear(pt_listex);
                for(j = 0; j < n_countex; ++j)
                {
                    list_push_back(pt_listex, rand() - rand());
                }
                list_push_back(pt_list1, pt_listex);
            }
            srand((unsigned)time(NULL) + rand());
            n_count = rand() % 100;
            for(i = 0; i < n_count; ++i)
            {
                srand((unsigned)time(NULL) + rand());
                n_countex = rand() % 100;
                list_clear(pt_listex);
                for(j = 0; j < n_countex; ++j)
                {
                    list_push_back(pt_listex, rand() - rand());
                }
                list_push_back(pt_list2, pt_listex);
            }
            list_sort(pt_list1);
            list_sort(pt_list2);
            _printlist_list(pt_list1);
            _printlist_list(pt_list2);
            list_merge(pt_list1, pt_list2);
            _printlist_list(pt_list1);
            _printlist_list(pt_list2);

            list_destroy(pt_list1);
            list_destroy(pt_list2);
            list_destroy(pt_listex);
        }
        /*list_merge_if       */
        {
            list_t* pt_list1 = create_list(list_t<int>);
            list_t* pt_list2 = create_list(list_t<int>);
            list_t* pt_listex = create_list(int);
            int n_count;
            int n_countex;
            int i,j;
            if(pt_list1 == NULL || pt_list2 == NULL || pt_listex == NULL)
            {
                return;
            }
            list_init(pt_list1);
            list_init(pt_list2);
            list_init(pt_listex);

            srand((unsigned)time(NULL));
            n_count = rand() % 100;
            for(i = 0; i < n_count; ++i)
            {
                srand((unsigned)time(NULL) + rand());
                n_countex = rand() % 100;
                list_clear(pt_listex);
                for(j = 0; j < n_countex; ++j)
                {
                    list_push_back(pt_listex, rand() - rand());
                }
                list_push_back(pt_list1, pt_listex);
            }
            srand((unsigned)time(NULL) + rand());
            n_count = rand() % 100;
            for(i = 0; i < n_count; ++i)
            {
                srand((unsigned)time(NULL) + rand());
                n_countex = rand() % 100;
                list_clear(pt_listex);
                for(j = 0; j < n_countex; ++j)
                {
                    list_push_back(pt_listex, rand() - rand());
                }
                list_push_back(pt_list2, pt_listex);
            }
            list_sort_if(pt_list1, _list_sort_pre);
            list_sort_if(pt_list2, _list_sort_pre);
            _printlist_list(pt_list1);
            _printlist_list(pt_list2);
            list_merge_if(pt_list1, pt_list2, _list_sort_pre);
            _printlist_list(pt_list1);
            _printlist_list(pt_list2);

            list_destroy(pt_list1);
            list_destroy(pt_list2);
            list_destroy(pt_listex);
        }
        /*list_reverse        */
        {
            list_t* pt_list = create_list(list_t<int>);
            list_t* pt_listex = create_list(int);
            int n_count;
            int n_countex;
            int i,j;
            if(pt_list == NULL || pt_listex == NULL)
            {
                return;
            }
            list_init(pt_list);
            list_init(pt_listex);

            srand((unsigned)time(NULL));
            n_count = rand() % 100;
            for(i = 0; i < n_count; ++i)
            {
                srand((unsigned)time(NULL) + rand());
                n_countex = rand() % 100;
                list_clear(pt_listex);
                for(j = 0; j < n_countex; ++j)
                {
                    list_push_back(pt_listex, rand() - rand());
                }
                list_push_back(pt_list, pt_listex);
            }
            _printlist_list(pt_list);
            list_reverse(pt_list);
            _printlist_list(pt_list);

            list_destroy(pt_list);
            list_destroy(pt_listex);
        }
    }
    /* for c-string type */
    /*create_list         */
    {
        list_t* pt_list = create_list(char*);
        if(pt_list == NULL)
        {
            return;
        }
        list_init(pt_list);
        _print_list_str(pt_list);
        list_destroy(pt_list);
    }
    /*list_init           */
    /*list_init_n         */
    {
        list_t* pt_list = create_list(char*);
        if(pt_list == NULL)
        {
            return;
        }
        list_init_n(pt_list, 6);
        _print_list_str(pt_list);
        list_destroy(pt_list);
    }
    /*_list_init_elem     */
    {
        list_t* pt_list = create_list(char*);
        if(pt_list == NULL)
        {
            return;
        }
        list_init_elem(pt_list, 10, "|     Type      |    Length     |");
        _print_list_str(pt_list);
        list_destroy(pt_list);
    }
    /*list_init_copy      */
    {
        list_t* pt_list = create_list(char*);
        list_t* pt_listex = create_list(char*);
        if(pt_list == NULL || pt_listex == NULL)
        {
            return;
        }
        list_init_elem(pt_listex, 4, "Value: 0061 (hex)");
        list_init_copy(pt_list, pt_listex);
        _print_list_str(pt_list);
        list_destroy(pt_list);
        list_destroy(pt_listex);
    }
    /*list_init_copy_range*/
    {
        list_t* pt_list = create_list(char*);
        list_t* pt_listex = create_list(char*);
        if(pt_list == NULL || pt_listex == NULL)
        {
            return;
        }
        list_init(pt_listex);
        list_push_back(pt_listex, "Multiple Network Control Protocols");
        list_push_back(pt_listex, "Sharing Context Identifier Space");
        list_push_back(pt_listex, "Demultiplexing of Datagrams");
        list_push_back(pt_listex, "References");
        list_push_back(pt_listex, "RTP-Compression Suboption");
        list_push_back(pt_listex, "Configuration Option Format");
        list_push_back(pt_listex, "Configuration Option");
        _print_list_str(pt_listex);
        list_init_copy_range(pt_list, list_begin(pt_listex), list_end(pt_listex));
        _print_list_str(pt_list);
        list_destroy(pt_list);
        list_destroy(pt_listex);
    }
    /*list_destroy        */
    /*list_size           */
    /*list_empty          */
    /*list_max_size       */
    /*list_equal          */
    /*list_not_equal      */
    /*list_less           */
    /*list_less_equal     */
    /*list_great          */
    /*list_great_equal    */
    {
        list_t* pt_list = create_list(char*);
        list_t* pt_listex = create_list(char*);
        if(pt_list == NULL || pt_listex == NULL)
        {
            return;
        }
        list_init(pt_list);
        list_init(pt_listex);
        _print_list_str(pt_list);
        _print_list_str(pt_listex);
        printf("equal: %d, not equal: %d, ",
            list_equal(pt_list, pt_listex), list_not_equal(pt_list, pt_listex));
        printf("less: %d, less equal: %d, ",
            list_less(pt_list, pt_listex), list_less_equal(pt_list, pt_listex));
        printf("great: %d, great equal: %d\n",
            list_great(pt_list, pt_listex), list_great_equal(pt_list, pt_listex));

        list_push_back(pt_list, "China");
        _print_list_str(pt_list);
        _print_list_str(pt_listex);
        printf("equal: %d, not equal: %d, ",
            list_equal(pt_list, pt_listex), list_not_equal(pt_list, pt_listex));
        printf("less: %d, less equal: %d, ",
            list_less(pt_list, pt_listex), list_less_equal(pt_list, pt_listex));
        printf("great: %d, great equal: %d\n",
            list_great(pt_list, pt_listex), list_great_equal(pt_list, pt_listex));

        list_push_back(pt_listex, "China");
        _print_list_str(pt_list);
        _print_list_str(pt_listex);
        printf("equal: %d, not equal: %d, ",
            list_equal(pt_list, pt_listex), list_not_equal(pt_list, pt_listex));
        printf("less: %d, less equal: %d, ",
            list_less(pt_list, pt_listex), list_less_equal(pt_list, pt_listex));
        printf("great: %d, great equal: %d\n",
            list_great(pt_list, pt_listex), list_great_equal(pt_list, pt_listex));

        list_push_back(pt_listex, "Unix");
        _print_list_str(pt_list);
        _print_list_str(pt_listex);
        printf("equal: %d, not equal: %d, ",
            list_equal(pt_list, pt_listex), list_not_equal(pt_list, pt_listex));
        printf("less: %d, less equal: %d, ",
            list_less(pt_list, pt_listex), list_less_equal(pt_list, pt_listex));
        printf("great: %d, great equal: %d\n",
            list_great(pt_list, pt_listex), list_great_equal(pt_list, pt_listex));

        list_push_back(pt_list, "CSDN");
        list_push_back(pt_list, "Pub");
        _print_list_str(pt_list);
        _print_list_str(pt_listex);
        printf("equal: %d, not equal: %d, ",
            list_equal(pt_list, pt_listex), list_not_equal(pt_list, pt_listex));
        printf("less: %d, less equal: %d, ",
            list_less(pt_list, pt_listex), list_less_equal(pt_list, pt_listex));
        printf("great: %d, great equal: %d\n",
            list_great(pt_list, pt_listex), list_great_equal(pt_list, pt_listex));
        list_destroy(pt_list);
        list_destroy(pt_listex);
    }
    /*list_assign         */
    {
        list_t* pt_list = create_list(char*);
        list_t* pt_listex = create_list(char*);
        if(pt_list == NULL || pt_listex == NULL)
        {
            return;
        }
        list_init(pt_list);
        list_init(pt_listex);
        list_assign(pt_list, pt_listex);
        _print_list_str(pt_list);
        list_push_back(pt_listex, "[RFC1661]");
        list_push_back(pt_listex, "[RFC1331]");
        list_push_back(pt_listex, "[RFC1332]");
        list_assign(pt_list, pt_listex);
        _print_list_str(pt_list);
        list_clear(pt_listex);
        list_assign(pt_list, pt_listex);
        _print_list_str(pt_list);
        list_destroy(pt_list);
        list_destroy(pt_listex);
    }
    /*list_assign_elem    */
    {
        list_t* pt_list = create_list(char*);
        if(pt_list == NULL)
        {
            return;
        }
        list_init(pt_list);
        list_assign_elem(pt_list, 0, "protocol value for the IPCP");
        _print_list_str(pt_list);
        list_assign_elem(pt_list, 3, "such as multiclass multilink PPP [MCML]");
        _print_list_str(pt_list);
        list_assign_elem(pt_list, 17, "[RFC1332]");
        _print_list_str(pt_list);
        list_assign_elem(pt_list, 5, "");
        _print_list_str(pt_list);
        list_assign_elem(pt_list, 0, "NOTE: The of link and network layer parameter");
        _print_list_str(pt_list);
        list_destroy(pt_list);
    }
    /*list_assign_range   */
    {
        list_t* pt_list = create_list(char*);
        list_t* pt_listex = create_list(char*);
        if(pt_list == NULL || pt_listex == NULL)
        {
            return;
        }
        list_init(pt_list);
        list_init(pt_listex);
        list_assign_range(pt_list, list_begin(pt_listex), list_end(pt_listex));
        _print_list_str(pt_list);
        list_push_back(pt_listex, "IP-Compression-Protocol");
        list_push_back(pt_listex, "TCP_SPACE");
        list_push_back(pt_listex, "NON_TCP_SPACE");
        list_push_back(pt_listex, "F_MAX_PERIOD");
        list_push_back(pt_listex, "F_MAX_TIME");
        list_push_back(pt_listex, "MAX_HEADER");
        list_push_back(pt_listex, "suboptions...");
        _print_list_str(pt_listex);
        list_assign_range(pt_list, list_begin(pt_listex), list_begin(pt_listex));
        _print_list_str(pt_list);
        list_destroy(pt_list);
        list_destroy(pt_listex);
    }
    /*list_swap           */
    {
        list_t* pt_list = create_list(char*);
        list_t* pt_listex = create_list(char*);
        if(pt_list == NULL || pt_listex == NULL)
        {
            return;
        }
        list_init(pt_list);
        list_init(pt_listex);
        list_swap(pt_list, pt_listex);
        _print_list_str(pt_list);
        _print_list_str(pt_listex);
        list_assign_elem(pt_listex, 3, "allocated for TCP.");
        list_swap(pt_list, pt_listex);
        _print_list_str(pt_list);
        _print_list_str(pt_listex);
        list_assign_elem(pt_listex, 10, "Suggested value: 15");
        list_swap(pt_list, pt_listex);
        _print_list_str(pt_list);
        _print_list_str(pt_listex);
        list_assign_elem(pt_listex, 2, "NON_TCP_SPACE");
        list_swap(pt_list, pt_listex);
        _print_list_str(pt_list);
        _print_list_str(pt_listex);
        list_clear(pt_listex);
        list_swap(pt_list, pt_listex);
        _print_list_str(pt_list);
        _print_list_str(pt_listex);
        list_destroy(pt_list);
        list_destroy(pt_listex);
    }
    /*list_front          */
    /*list_back           */
    {
        list_t* pt_list = create_list(char*);
        if(pt_list == NULL)
        {
            return;
        }
        list_init(pt_list);
        list_push_back(pt_list, "IMPLICIT SEQUENCE {");
        puts(list_back(pt_list));
        list_push_back(pt_list, "Connection-Oriented Accounting MIB");
        puts(list_back(pt_list));
        list_push_back(pt_list, "04 09 73 77 69 74 63 68 2d 31 32");
        puts(list_back(pt_list));
        list_push_back(pt_list, "OBJECT IDENTIFIER");
        puts(list_back(pt_list));
        while(!list_empty(pt_list))
        {
            list_pop_front(pt_list);
        }
        _print_list_str(pt_list);

        list_push_front(pt_list, "OBJECT IDENTIFIER ::= { accountingControlMIB 1 }");
        puts(list_front(pt_list));
        list_push_front(pt_list, "TEXTUAL-CONVENTION");
        puts(list_front(pt_list));
        list_push_front(pt_list, "FileIndex ::= TEXTUAL-CONVENTION");
        puts(list_front(pt_list));
        while(!list_empty(pt_list))
        {
            list_pop_back(pt_list);
        }
        _print_list_str(pt_list);

        list_destroy(pt_list);
    }
    /*list_begin          */
    /*list_end            */
    /*list_insert_n       */
    {
        list_t* pt_list = create_list(char*);
        if(pt_list == NULL)
        {
            return;
        }
        list_init(pt_list);
        list_insert_n(pt_list, list_begin(pt_list), 0, "FileIndex ::= TEXTUAL-CONVENTION");
        _print_list_str(pt_list);
        list_insert_n(pt_list, list_begin(pt_list), 3, "Integer32 (1..65535)");
        _print_list_str(pt_list);
        list_insert_n(pt_list, list_begin(pt_list), 6, "The Accounting Information Selection table");
        _print_list_str(pt_list);
        list_insert_n(pt_list, iterator_advance(list_begin(pt_list), 3), 5, "");
        _print_list_str(pt_list);
        list_insert_n(pt_list, list_end(pt_list), 1, "acctngSelectionTable OBJECT-TYPE");
        _print_list_str(pt_list);
        list_insert_n(pt_list, list_end(pt_list), 0, "DESCRIPTION");
        _print_list_str(pt_list);
        list_destroy(pt_list);
    }
    /*list_insert_range   */
    {
        list_t* pt_list = create_list(char*);
        list_t* pt_listex = create_list(char*);
        if(pt_list == NULL || pt_listex == NULL)
        {
            return;
        }
        list_init(pt_list);
        list_init(pt_listex);
        list_insert_range(pt_list, list_begin(pt_list), list_begin(pt_listex), list_end(pt_listex));
        _print_list_str(pt_list);
        list_push_back(pt_listex, "acctngSelectionEntry OBJECT-TYPE");
        list_push_back(pt_listex, "SYNTAX      AcctngSelectionEntry");
        list_push_back(pt_listex, "MAX-ACCESS  not-accessible");
        list_push_back(pt_listex, "STATUS      current");
        list_push_back(pt_listex, "DESCRIPTION");
        list_push_back(pt_listex, "An entry identifying an (subtree, list) tuple used to");
        list_push_back(pt_listex, "select a set of accounting information which is to be");
        list_push_back(pt_listex, "INDEX   { acctngSelectionIndex }");
        _print_list_str(pt_listex);
        list_insert_range(pt_list, list_begin(pt_list), list_begin(pt_listex), list_begin(pt_listex));
        _print_list_str(pt_list);
        list_insert_range(pt_list, list_begin(pt_list),
            list_begin(pt_listex), iterator_advance(list_begin(pt_listex), 3));
        _print_list_str(pt_list);
        list_insert_range(pt_list, list_begin(pt_list),
            iterator_advance(list_begin(pt_listex), 4), iterator_advance(list_begin(pt_listex), 6));
        _print_list_str(pt_list);
        list_insert_range(pt_list, iterator_advance(list_begin(pt_list), 3),
            iterator_advance(list_begin(pt_listex), 5), list_end(pt_listex));
        _print_list_str(pt_list);
        list_insert_range(pt_list, list_end(pt_list), list_end(pt_listex), list_end(pt_listex));
        _print_list_str(pt_list);
        list_insert_range(pt_list, list_end(pt_list), list_begin(pt_listex), list_end(pt_listex));
        _print_list_str(pt_list);
        list_destroy(pt_list);
        list_destroy(pt_listex);
    }
    /*list_push_back      */
    /*list_pop_back       */
    /*list_push_front     */
    /*list_pop_front      */
    /*list_erase          */
    {
        list_t* pt_list = create_list(char*);
        if(pt_list == NULL)
        {
            return;
        }
        list_init(pt_list);
        list_push_back(pt_list, "svcIncoming(0)");
        list_push_back(pt_list, "svcOutgoing(1)");
        list_push_back(pt_list, "svpIncoming(2)");
        list_push_back(pt_list, "svpOutgoing(3)");
        list_push_back(pt_list, "pvc(4)");
        list_push_back(pt_list, "pvp(5)");
        list_push_back(pt_list, "spvcOriginator(6)");
        list_push_back(pt_list, "spvcTarget(7)");
        list_push_back(pt_list, "spvpOriginator(8)");
        list_push_back(pt_list, "spvpTarget(9)");
        _print_list_str(pt_list);
        list_erase(pt_list, list_begin(pt_list));
        _print_list_str(pt_list);
        list_erase(pt_list, iterator_prev(list_end(pt_list)));
        _print_list_str(pt_list);
        list_erase(pt_list, iterator_advance(list_begin(pt_list), 3));
        _print_list_str(pt_list);
        while(!list_empty(pt_list))
        {
            list_erase(pt_list, list_begin(pt_list));
        }
        _print_list_str(pt_list);
        list_destroy(pt_list);
    }
    /*list_erase_range    */
    {
        list_t* pt_list = create_list(char*);
        if(pt_list == NULL)
        {
            return;
        }
        list_init(pt_list);
        list_erase_range(pt_list, list_begin(pt_list), list_end(pt_list));
        _print_list_str(pt_list);
        list_push_back(pt_list, "svcIncoming(0)");
        list_push_back(pt_list, "svcOutgoing(1)");
        list_push_back(pt_list, "svpIncoming(2)");
        list_push_back(pt_list, "svpOutgoing(3)");
        list_push_back(pt_list, "pvc(4)");
        list_push_back(pt_list, "pvp(5)");
        list_push_back(pt_list, "spvcOriginator(6)");
        list_push_back(pt_list, "spvcTarget(7)");
        list_push_back(pt_list, "spvpOriginator(8)");
        list_push_back(pt_list, "spvpTarget(9)");
        _print_list_str(pt_list);
        list_erase_range(pt_list, list_begin(pt_list), list_begin(pt_list));
        _print_list_str(pt_list);
        list_erase_range(pt_list, list_begin(pt_list), iterator_advance(list_begin(pt_list), 3));
        _print_list_str(pt_list);
        list_erase_range(pt_list, iterator_advance(list_begin(pt_list), 3), iterator_advance(list_begin(pt_list), 5));
        _print_list_str(pt_list);
        list_erase_range(pt_list, iterator_advance(list_begin(pt_list), 3), list_end(pt_list));
        _print_list_str(pt_list);
        list_erase_range(pt_list, list_end(pt_list), list_end(pt_list));
        _print_list_str(pt_list);
        list_erase_range(pt_list, list_begin(pt_list), list_end(pt_list));
        _print_list_str(pt_list);
        list_destroy(pt_list);
    }
    /*list_remove         */
    {
        list_t* pt_list = create_list(char*);
        if(pt_list == NULL)
        {
            return;
        }
        list_init(pt_list);
        list_remove(pt_list, "CSDN");
        _print_list_str(pt_list);
        list_push_back(pt_list, "China-pub");
        list_push_back(pt_list, "CSDN");
        list_push_back(pt_list, "ChinaUnix");
        list_push_back(pt_list, "taobao");
        list_push_back(pt_list, "sina");
        list_push_back(pt_list, "baidu");
        list_push_back(pt_list, "CSDN");
        list_push_back(pt_list, "mop");
        list_push_back(pt_list, "Google");
        list_push_back(pt_list, "163");
        _print_list_str(pt_list);
        list_remove(pt_list, "CSDN");
        _print_list_str(pt_list);
        list_remove(pt_list, "Microsoft");
        _print_list_str(pt_list);
        list_destroy(pt_list);
    }
    /*list_remove_if      */
    {
        list_t* pt_list = create_list(char*);
        if(pt_list == NULL)
        {
            return;
        }
        list_init(pt_list);
        list_remove_if(pt_list, _list_str_remove_pre);
        _print_list_str(pt_list);
        list_push_back(pt_list, "China-pub");
        list_push_back(pt_list, "CSDN");
        list_push_back(pt_list, "ChinaUnix");
        list_push_back(pt_list, "taobao");
        list_push_back(pt_list, "sina");
        list_push_back(pt_list, "baidu");
        list_push_back(pt_list, "CSDN");
        list_push_back(pt_list, "mop");
        list_push_back(pt_list, "Google");
        list_push_back(pt_list, "163");
        _print_list_str(pt_list);
        list_remove_if(pt_list, _list_str_remove_pre);
        _print_list_str(pt_list);
        list_remove_if(pt_list, _list_str_remove_pre);
        _print_list_str(pt_list);
        list_destroy(pt_list);
    }
    /*list_resize         */
    {
        list_t* pt_list = create_list(char*);
        if(pt_list == NULL)
        {
            return;
        }
        list_init(pt_list);
        list_resize(pt_list, 0);
        _print_list_str(pt_list);
        list_resize(pt_list, 5);
        _print_list_str(pt_list);
        list_resize(pt_list, 13);
        _print_list_str(pt_list);
        list_resize(pt_list, 3);
        _print_list_str(pt_list);
        list_resize(pt_list, 0);
        _print_list_str(pt_list);
        list_destroy(pt_list);
    }
    /*list_resize_elem    */
    {
        list_t* pt_list = create_list(char*);
        if(pt_list == NULL)
        {
            return;
        }
        list_init(pt_list);
        list_resize_elem(pt_list, 0, "::= { acctngSelectionEntry 6 }");
        _print_list_str(pt_list);
        list_resize_elem(pt_list, 4, "Connection-Oriented Accounting MIB");
        _print_list_str(pt_list);
        list_resize_elem(pt_list, 9, "NOTIFICATION-TYPE");
        _print_list_str(pt_list);
        list_resize_elem(pt_list, 5, "");
        _print_list_str(pt_list);
        list_resize_elem(pt_list, 0, "STATUS");
        _print_list_str(pt_list);
        list_destroy(pt_list);
    }
    /*list_clear          */
    {
        list_t* pt_list = create_list(char*);
        if(pt_list == NULL)
        {
            return;
        }
        list_init(pt_list);
        list_clear(pt_list);
        _print_list_str(pt_list);
        list_push_back(pt_list, "acctngFileName");
        list_push_back(pt_list, "acctngFileMaximumSize");
        list_push_back(pt_list, "acctngControlTrapThreshold");
        list_push_back(pt_list, "acctngFileNameSuffix");
        _print_list_str(pt_list);
        list_clear(pt_list);
        _print_list_str(pt_list);
        list_destroy(pt_list);
    }
    /*list_unique         */
    {
        list_t* pt_list = create_list(char*);
        if(pt_list == NULL)
        {
            return;
        }
        list_init(pt_list);
        list_unique(pt_list);
        _print_list_str(pt_list);
        list_push_back(pt_list, "ChinaUnix");
        list_push_back(pt_list, "CSDN");
        list_push_back(pt_list, "mop");
        list_push_back(pt_list, "microsoft");
        list_push_back(pt_list, "microsoft");
        list_push_back(pt_list, "baidu");
        list_push_back(pt_list, "163");
        list_push_back(pt_list, "119-110-112");
        list_push_back(pt_list, "sina");
        _print_list_str(pt_list);
        list_unique(pt_list);
        _print_list_str(pt_list);
        list_unique(pt_list);
        _print_list_str(pt_list);
        list_destroy(pt_list);
    }
    /*list_unique_if      */
    {
        list_t* pt_list = create_list(char*);
        if(pt_list == NULL)
        {
            return;
        }
        list_init(pt_list);
        list_unique_if(pt_list, _list_str_unique_pre);
        _print_list_str(pt_list);
        list_push_back(pt_list, "ChinaUnix");
        list_push_back(pt_list, "CSDN");
        list_push_back(pt_list, "mop");
        list_push_back(pt_list, "microsoft");
        list_push_back(pt_list, "microsoft");
        list_push_back(pt_list, "baidu");
        list_push_back(pt_list, "163");
        list_push_back(pt_list, "119-110-112");
        list_push_back(pt_list, "sina");
        _print_list_str(pt_list);
        list_unique_if(pt_list, _list_str_unique_pre);
        _print_list_str(pt_list);
        list_unique_if(pt_list, _list_str_unique_pre);
        _print_list_str(pt_list);
        list_destroy(pt_list);
    }
    /*list_splice         */
    {
        list_t* pt_list = create_list(char*);
        list_t* pt_listex = create_list(char*);
        if(pt_list == NULL || pt_listex == NULL)
        {
            return;
        }
        list_init(pt_list);
        list_init(pt_listex);
        list_splice(pt_list, list_begin(pt_list), pt_listex);
        _print_list_str(pt_list);
        _print_list_str(pt_listex);
        list_assign_elem(pt_listex, 3, "OBJECTS");
        list_splice(pt_list, list_begin(pt_list), pt_listex);
        _print_list_str(pt_list);
        _print_list_str(pt_listex);
        list_assign_elem(pt_listex, 2, "[Page 22]");
        list_splice(pt_list, list_begin(pt_list), pt_listex);
        _print_list_str(pt_list);
        _print_list_str(pt_listex);
        list_assign_elem(pt_listex, 4, "");
        list_splice(pt_list, iterator_advance(list_begin(pt_list), 2), pt_listex);
        _print_list_str(pt_list);
        _print_list_str(pt_listex);
        list_assign_elem(pt_listex, 6, "OBJECT IDENTIFIER");
        list_splice(pt_list, list_end(pt_list), pt_listex);
        _print_list_str(pt_list);
        _print_list_str(pt_listex);
        list_clear(pt_listex);
        list_splice(pt_list, list_end(pt_list), pt_listex);
        _print_list_str(pt_list);
        _print_list_str(pt_listex);
        list_destroy(pt_list);
        list_destroy(pt_listex);
    }
    /*list_splice_pos     */
    {
        list_t* pt_list = create_list(char*);
        list_t* pt_listex = create_list(char*);
        if(pt_list == NULL || pt_listex == NULL)
        {
            return;
        }
        list_init(pt_list);
        list_init(pt_listex);
        list_push_back(pt_listex, "Identifies v1, v2, or v3");
        list_push_back(pt_listex, "Certificate serial number");
        list_push_back(pt_listex, "an integer assigned by the issuer");
        list_push_back(pt_listex, "OID of algorithm that was used to");
        list_push_back(pt_listex, "sign the certificate");
        list_push_back(pt_listex, "DN of the issuer (the CA who signed)");
        list_push_back(pt_listex, "Validity period; a pair of UTCTime");
        list_push_back(pt_listex, "values: \"not before\" and \"not after\"");
        list_push_back(pt_listex, "DN of entity who owns the public key");
        list_push_back(pt_listex, "Public key value and algorithm OID");
        list_push_back(pt_listex, "Defined for v2, v3; optional");
        list_push_back(pt_listex, "Defined for v2, v2; optional");
        list_push_back(pt_listex, "Defined only for v3; optional");
        _print_list_str(pt_listex);
        list_splice_pos(pt_list, list_begin(pt_list), pt_listex, list_begin(pt_listex));
        _print_list_str(pt_list);
        _print_list_str(pt_listex);
        list_splice_pos(pt_list, list_begin(pt_list), pt_listex, list_begin(pt_listex));
        _print_list_str(pt_list);
        _print_list_str(pt_listex);
        list_splice_pos(pt_list, iterator_next(list_begin(pt_list)), pt_listex, iterator_next(list_begin(pt_listex)));
        _print_list_str(pt_list);
        _print_list_str(pt_listex);
        list_splice_pos(pt_list, list_end(pt_list), pt_listex, iterator_prev(list_end(pt_listex)));
        _print_list_str(pt_list);
        _print_list_str(pt_listex);
        list_destroy(pt_list);
        list_destroy(pt_listex);
    }
    /*list_splice_range   */
    {
        list_t* pt_list = create_list(char*);
        list_t* pt_listex = create_list(char*);
        if(pt_list == NULL || pt_listex == NULL)
        {
            return;
        }
        list_init(pt_list);
        list_init(pt_listex);
        list_splice_range(pt_list, list_begin(pt_list), pt_listex, list_begin(pt_listex), list_end(pt_listex));
        _print_list_str(pt_list);
        _print_list_str(pt_listex);
        list_push_back(pt_listex, "Identifies v1, v2, or v3");
        list_push_back(pt_listex, "Certificate serial number");
        list_push_back(pt_listex, "an integer assigned by the issuer");
        list_push_back(pt_listex, "OID of algorithm that was used to");
        list_push_back(pt_listex, "sign the certificate");
        list_push_back(pt_listex, "DN of the issuer (the CA who signed)");
        list_push_back(pt_listex, "Validity period; a pair of UTCTime");
        list_push_back(pt_listex, "values: \"not before\" and \"not after\"");
        list_push_back(pt_listex, "DN of entity who owns the public key");
        list_push_back(pt_listex, "Public key value and algorithm OID");
        list_push_back(pt_listex, "Defined for v2, v3; optional");
        list_push_back(pt_listex, "Defined for v2, v2; optional");
        list_push_back(pt_listex, "Defined only for v3; optional");
        _print_list_str(pt_listex);
        list_splice_range(pt_list, list_begin(pt_list), pt_listex, list_begin(pt_listex), list_begin(pt_listex));
        _print_list_str(pt_list);
        _print_list_str(pt_listex);
        list_splice_range(pt_list, list_begin(pt_list),
            pt_listex, list_begin(pt_listex), iterator_advance(list_begin(pt_listex), 3));
        _print_list_str(pt_list);
        _print_list_str(pt_listex);
        list_splice_range(pt_list, list_begin(pt_list),
            pt_listex, iterator_next(list_begin(pt_listex)), iterator_advance(list_begin(pt_listex), 3));
        _print_list_str(pt_list);
        _print_list_str(pt_listex);
        list_splice_range(pt_list, iterator_next(list_begin(pt_list)),
            pt_listex, iterator_advance(list_begin(pt_listex), 6), list_end(pt_listex));
        _print_list_str(pt_list);
        _print_list_str(pt_listex);
        list_splice_range(pt_list, list_end(pt_list), pt_listex, list_end(pt_listex), list_end(pt_listex));
        _print_list_str(pt_list);
        _print_list_str(pt_listex);
        list_splice_range(pt_list, list_end(pt_list), pt_listex, list_begin(pt_listex), list_end(pt_listex));
        _print_list_str(pt_list);
        _print_list_str(pt_listex);
        list_destroy(pt_list);
        list_destroy(pt_listex);
    }
    /*list_sort           */
    {
        list_t* pt_list = create_list(char*);
        if(pt_list == NULL)
        {
            return;
        }
        list_init(pt_list);
        list_sort(pt_list);
        _print_list_str(pt_list);
        list_push_back(pt_list, "Identifies v1, v2, or v3");
        list_push_back(pt_list, "Certificate serial number");
        list_push_back(pt_list, "an integer assigned by the issuer");
        list_push_back(pt_list, "OID of algorithm that was used to");
        list_push_back(pt_list, "sign the certificate");
        list_push_back(pt_list, "DN of the issuer (the CA who signed)");
        list_push_back(pt_list, "Validity period; a pair of UTCTime");
        list_push_back(pt_list, "values: \"not before\" and \"not after\"");
        list_push_back(pt_list, "DN of entity who owns the public key");
        list_push_back(pt_list, "Public key value and algorithm OID");
        list_push_back(pt_list, "Defined for v2, v3; optional");
        list_push_back(pt_list, "");
        list_push_back(pt_list, "Defined for v2, v2; optional");
        list_push_back(pt_list, "Defined only for v3; optional");
        list_push_back(pt_list, "ChinaUnix");
        list_push_back(pt_list, "svcIncoming(1)");
        list_push_back(pt_list, "svcOutgoing(0)");
        list_push_back(pt_list, "CSDN");
        list_push_back(pt_list, "mop");
        list_push_back(pt_list, "microsoft");
        list_push_back(pt_list, "microsoft");
        list_push_back(pt_list, "baidu");
        list_push_back(pt_list, "163");
        list_push_back(pt_list, "119-110-112");
        list_push_back(pt_list, "sina");
        list_push_back(pt_list, "svcIncoming(0)");
        list_push_back(pt_list, "svcOutgoing(1)");
        list_push_back(pt_list, "svpIncoming(2)");
        list_push_back(pt_list, "svpOutgoing(3)");
        list_push_back(pt_list, "pvc(4)");
        list_push_back(pt_list, "");
        list_push_back(pt_list, "");
        list_push_back(pt_list, "");
        list_push_back(pt_list, "");
        list_push_back(pt_list, "pvp(5)");
        list_push_back(pt_list, "spvcOriginator(6)");
        list_push_back(pt_list, "spvcTarget(7)");
        list_push_back(pt_list, "spvpOriginator(8)");
        list_push_back(pt_list, "spvpTarget(9)");
        list_push_back(pt_list, "acctngFileName");
        list_push_back(pt_list, "acctngFileMaximumSize");
        list_push_back(pt_list, "acctngSelectionEntry OBJECT-TYPE");
        list_push_back(pt_list, "SYNTAX      AcctngSelectionEntry");
        list_push_back(pt_list, "MAX-ACCESS  not-accessible");
        list_push_back(pt_list, "STATUS      current");
        list_push_back(pt_list, "DESCRIPTION");
        list_push_back(pt_list, "An entry identifying an (subtree, list) tuple used to");
        list_push_back(pt_list, "select a set of accounting information which is to be");
        list_push_back(pt_list, "INDEX   { acctngSelectionIndex }");
        list_push_back(pt_list, "acctngControlTrapThreshold");
        list_push_back(pt_list, "acctngFileNameSuffix");
        _print_list_str(pt_list);
        list_sort(pt_list);
        _print_list_str(pt_list);

        list_destroy(pt_list);
    }
    /*list_sort_if        */
    {
        list_t* pt_list = create_list(char*);
        if(pt_list == NULL)
        {
            return;
        }
        list_init(pt_list);
        list_sort_if(pt_list, _list_str_sort_pre);
        _print_list_str(pt_list);
        list_push_back(pt_list, "Identifies v1, v2, or v3");
        list_push_back(pt_list, "Certificate serial number");
        list_push_back(pt_list, "an integer assigned by the issuer");
        list_push_back(pt_list, "OID of algorithm that was used to");
        list_push_back(pt_list, "sign the certificate");
        list_push_back(pt_list, "DN of the issuer (the CA who signed)");
        list_push_back(pt_list, "Validity period; a pair of UTCTime");
        list_push_back(pt_list, "values: \"not before\" and \"not after\"");
        list_push_back(pt_list, "DN of entity who owns the public key");
        list_push_back(pt_list, "Public key value and algorithm OID");
        list_push_back(pt_list, "Defined for v2, v3; optional");
        list_push_back(pt_list, "");
        list_push_back(pt_list, "Defined for v2, v2; optional");
        list_push_back(pt_list, "Defined only for v3; optional");
        list_push_back(pt_list, "ChinaUnix");
        list_push_back(pt_list, "svcIncoming(1)");
        list_push_back(pt_list, "svcOutgoing(0)");
        list_push_back(pt_list, "CSDN");
        list_push_back(pt_list, "mop");
        list_push_back(pt_list, "microsoft");
        list_push_back(pt_list, "microsoft");
        list_push_back(pt_list, "baidu");
        list_push_back(pt_list, "163");
        list_push_back(pt_list, "119-110-112");
        list_push_back(pt_list, "sina");
        list_push_back(pt_list, "svcIncoming(0)");
        list_push_back(pt_list, "svcOutgoing(1)");
        list_push_back(pt_list, "svpIncoming(2)");
        list_push_back(pt_list, "svpOutgoing(3)");
        list_push_back(pt_list, "pvc(4)");
        list_push_back(pt_list, "");
        list_push_back(pt_list, "");
        list_push_back(pt_list, "");
        list_push_back(pt_list, "");
        list_push_back(pt_list, "pvp(5)");
        list_push_back(pt_list, "spvcOriginator(6)");
        list_push_back(pt_list, "spvcTarget(7)");
        list_push_back(pt_list, "spvpOriginator(8)");
        list_push_back(pt_list, "spvpTarget(9)");
        list_push_back(pt_list, "acctngFileName");
        list_push_back(pt_list, "acctngFileMaximumSize");
        list_push_back(pt_list, "acctngSelectionEntry OBJECT-TYPE");
        list_push_back(pt_list, "SYNTAX      AcctngSelectionEntry");
        list_push_back(pt_list, "MAX-ACCESS  not-accessible");
        list_push_back(pt_list, "STATUS      current");
        list_push_back(pt_list, "DESCRIPTION");
        list_push_back(pt_list, "An entry identifying an (subtree, list) tuple used to");
        list_push_back(pt_list, "select a set of accounting information which is to be");
        list_push_back(pt_list, "INDEX   { acctngSelectionIndex }");
        list_push_back(pt_list, "acctngControlTrapThreshold");
        list_push_back(pt_list, "acctngFileNameSuffix");
        _print_list_str(pt_list);
        list_sort_if(pt_list, _list_str_sort_pre);
        _print_list_str(pt_list);

        list_destroy(pt_list);
    }
    /*list_merge          */
    {
        list_t* pt_list = create_list(char*);
        list_t* pt_listex = create_list(char*);
        if(pt_list == NULL || pt_listex == NULL)
        {
            return;
        }
        list_init(pt_list);
        list_init(pt_listex);
        list_merge(pt_list, pt_listex);
        _print_list_str(pt_list);
        _print_list_str(pt_listex);
        list_push_back(pt_list, "See: (usage note under)");
        list_push_back(pt_list, "recovery of the data");
        list_push_back(pt_list, "");
        list_push_back(pt_list, "(I) Use erasure or other means");
        list_push_back(pt_list, "archival document series");
        list_push_back(pt_list, "[A9009]");
        list_push_back(pt_list, "[A3092]");
        list_sort(pt_list);
        list_merge(pt_list, pt_listex);
        _print_list_str(pt_list);
        _print_list_str(pt_listex);

        list_clear(pt_list);
        list_clear(pt_listex);
        list_push_back(pt_listex, "Public key Cryptography");
        list_push_back(pt_listex, "X9._42, 29 Jan 1999");
        list_push_back(pt_listex, "Informational");
        list_push_back(pt_listex, "issue with: Minerva M");
        list_push_back(pt_listex, "7799-1:1999, effective 15 May 1999");
        list_sort(pt_listex);
        list_merge(pt_list, pt_listex);
        _print_list_str(pt_list);
        _print_list_str(pt_listex);

        list_clear(pt_list);
        list_clear(pt_listex);
        list_push_back(pt_list, "See: (usage note under)");
        list_push_back(pt_list, "recovery of the data");
        list_push_back(pt_list, "");
        list_push_back(pt_list, "(I) Use erasure or other means");
        list_push_back(pt_list, "archival document series");
        list_push_back(pt_list, "[A9009]");
        list_push_back(pt_list, "[A3092]");
        list_sort(pt_list);
        list_push_back(pt_listex, "Public key Cryptography");
        list_push_back(pt_listex, "X9._42, 29 Jan 1999");
        list_push_back(pt_listex, "Informational");
        list_push_back(pt_listex, "issue with: Minerva M");
        list_push_back(pt_listex, "7799-1:1999, effective 15 May 1999");
        list_sort(pt_listex);
        list_merge(pt_list, pt_listex);
        _print_list_str(pt_list);
        _print_list_str(pt_listex);

        list_destroy(pt_list);
        list_destroy(pt_listex);
    }
    /*list_merge_if       */
    {
        list_t* pt_list = create_list(char*);
        list_t* pt_listex = create_list(char*);
        if(pt_list == NULL || pt_listex == NULL)
        {
            return;
        }
        list_init(pt_list);
        list_init(pt_listex);
        list_merge_if(pt_list, pt_listex, _list_str_sort_pre);
        _print_list_str(pt_list);
        _print_list_str(pt_listex);
        list_push_back(pt_list, "See: (usage note under)");
        list_push_back(pt_list, "recovery of the data");
        list_push_back(pt_list, "");
        list_push_back(pt_list, "(I) Use erasure or other means");
        list_push_back(pt_list, "archival document series");
        list_push_back(pt_list, "[A9009]");
        list_push_back(pt_list, "[A3092]");
        list_sort_if(pt_list, _list_str_sort_pre);
        list_merge_if(pt_list, pt_listex, _list_str_sort_pre);
        _print_list_str(pt_list);
        _print_list_str(pt_listex);

        list_clear(pt_list);
        list_clear(pt_listex);
        list_push_back(pt_listex, "Public key Cryptography");
        list_push_back(pt_listex, "X9._42, 29 Jan 1999");
        list_push_back(pt_listex, "Informational");
        list_push_back(pt_listex, "issue with: Minerva M");
        list_push_back(pt_listex, "7799-1:1999, effective 15 May 1999");
        list_sort_if(pt_listex, _list_str_sort_pre);
        list_merge_if(pt_list, pt_listex, _list_str_sort_pre);
        _print_list_str(pt_list);
        _print_list_str(pt_listex);

        list_clear(pt_list);
        list_clear(pt_listex);
        list_push_back(pt_list, "See: (usage note under)");
        list_push_back(pt_list, "recovery of the data");
        list_push_back(pt_list, "");
        list_push_back(pt_list, "(I) Use erasure or other means");
        list_push_back(pt_list, "archival document series");
        list_push_back(pt_list, "[A9009]");
        list_push_back(pt_list, "[A3092]");
        list_sort_if(pt_list, _list_str_sort_pre);
        list_push_back(pt_listex, "Public key Cryptography");
        list_push_back(pt_listex, "X9._42, 29 Jan 1999");
        list_push_back(pt_listex, "Informational");
        list_push_back(pt_listex, "issue with: Minerva M");
        list_push_back(pt_listex, "7799-1:1999, effective 15 May 1999");
        list_sort_if(pt_listex, _list_str_sort_pre);
        list_merge_if(pt_list, pt_listex, _list_str_sort_pre);
        _print_list_str(pt_list);
        _print_list_str(pt_listex);

        list_destroy(pt_list);
        list_destroy(pt_listex);
    }
    /*list_reverse        */
    {
        list_t* pt_list = create_list(char*);
        if(pt_list == NULL)
        {
            return;
        }
        list_init(pt_list);
        list_reverse(pt_list);
        _print_list_str(pt_list);
        list_push_back(pt_list, "[A3092]");
        list_push_back(pt_list, "[A9009][A9017]");
        list_push_back(pt_list, "[A9042][A9052][A9062]");
        list_push_back(pt_list, "[ABA][ACM][Army][B7799]");
        list_push_back(pt_list, "[Bell][CCIB][CIPSO][CSC1]");
        list_push_back(pt_list, "[CSC2][CSC3][CSOR][Denn][DH76]");
        _print_list_str(pt_list);
        list_reverse(pt_list);
        _print_list_str(pt_list);
        list_destroy(pt_list);
    }
}

/** local function implementation section **/
static void _list_str_sort_pre(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    if(strlen((char*)cpv_first) > strlen((char*)cpv_second))
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}

static void _list_str_unique_pre(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    if(((char*)cpv_first)[0] == ((char*)cpv_second)[0])
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}

static void _list_str_remove_pre(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    if(((char*)cpv_input)[0] == 'C')
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}

static void _print_list_str(const list_t* cpt_list)
{
    iterator_t t_iter;
    assert(cpt_list != NULL);
    printf("=====================================\n");
    printf("empty: %u, size: %u, max_size: %u\n",
        list_empty(cpt_list), list_size(cpt_list), list_max_size(cpt_list));
    for(t_iter = list_begin(cpt_list);
        !iterator_equal(t_iter, list_end(cpt_list));
        t_iter = iterator_next(t_iter))
    {
        puts((char*)iterator_get_pointer(t_iter));
    }
}

static void _list_sort_pre(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = false;
    if(list_size(cpv_first) <= list_size(cpv_second))
    {
        *(bool_t*)pv_output = true;
    }
}

static void _list_unique_pre(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = false;
    if(list_front(cpv_first) != NULL && list_front(cpv_second) != NULL)
    {
        if(*(int*)list_front(cpv_first) == *(int*)list_front(cpv_second))
        {
            *(bool_t*)pv_output = true;
        }
    }
}

static void _list_remove_pre(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    *(bool_t*)pv_output = false;
    if(list_front(cpv_input) != NULL)
    {
        if(*(int*)list_front(cpv_input) == 88)
        {
            *(bool_t*)pv_output = true;
        }
    }
}

static void _printlist_list(const list_t* cpt_list)
{
    iterator_t t_iter;
    iterator_t t_iterex;
    printf("=====================================\n");
    for(t_iter = list_begin(cpt_list);
        !iterator_equal(t_iter, list_end(cpt_list));
        t_iter = iterator_next(t_iter))
    {
        for(t_iterex = list_begin(iterator_get_pointer(t_iter));
            !iterator_equal(t_iterex, list_end(iterator_get_pointer(t_iter)));
            t_iterex = iterator_next(t_iterex))
        {
            printf("%d, ", *(int*)iterator_get_pointer(t_iterex));
        }
        printf("\n");
    }
}

static void _printlist_user(const list_t* cpt_list)
{
    iterator_t t_iter;
    listabc_t* pt_abc;
    printf("======================================\n");
    for(t_iter = list_begin(cpt_list);
        !iterator_equal(t_iter, list_end(cpt_list));
        t_iter = iterator_next(t_iter))
    {
        pt_abc = (listabc_t*)iterator_get_pointer(t_iter);
        switch(pt_abc->_t_flag)
        {
        case _ABC_FLAG_DESCARTES:
            printf("(%d, %d), ",
                pt_abc->_t_abc._t_descartes._n_posx, pt_abc->_t_abc._t_descartes._n_posy);
            break;
        case _ABC_FLAG_COMPLEX:
            printf("(%d%+di), ",
                pt_abc->_t_abc._t_complex._n_real, pt_abc->_t_abc._t_complex._n_imaginary);
            break;
        default:
            assert(false);
            break;
        }
    }
    printf("\n");
}

static void _listabc_init(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    ((listabc_t*)cpv_input)->_t_flag = _ABC_FLAG_DESCARTES;
    ((listabc_t*)cpv_input)->_t_abc._t_descartes._n_posx = 0;
    ((listabc_t*)cpv_input)->_t_abc._t_descartes._n_posy = 0;
    *(bool_t*)pv_output = true;
}
static void _listabc_destory(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    ((listabc_t*)cpv_input)->_t_flag = _ABC_FLAG_DESCARTES;
    ((listabc_t*)cpv_input)->_t_abc._t_descartes._n_posx = 0;
    ((listabc_t*)cpv_input)->_t_abc._t_descartes._n_posy = 0;
    *(bool_t*)pv_output = true;
}
static void _listabc_copy(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    if(((listabc_t*)cpv_second)->_t_flag == _ABC_FLAG_DESCARTES)
    {
        ((listabc_t*)cpv_first)->_t_flag = ((listabc_t*)cpv_second)->_t_flag;
        ((listabc_t*)cpv_first)->_t_abc._t_descartes._n_posx =
            ((listabc_t*)cpv_second)->_t_abc._t_descartes._n_posx;
        ((listabc_t*)cpv_first)->_t_abc._t_descartes._n_posy =
            ((listabc_t*)cpv_second)->_t_abc._t_descartes._n_posy;
    }
    else
    {
        ((listabc_t*)cpv_first)->_t_flag = ((listabc_t*)cpv_second)->_t_flag;
        ((listabc_t*)cpv_first)->_t_abc._t_complex._n_real =
            ((listabc_t*)cpv_second)->_t_abc._t_complex._n_real;
        ((listabc_t*)cpv_first)->_t_abc._t_complex._n_imaginary =
            ((listabc_t*)cpv_second)->_t_abc._t_complex._n_imaginary;
    }
    *(bool_t*)pv_output = true;
}
static void _listabc_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    /*
    assert(((listabc_t*)cpv_first)->_t_flag == ((listabc_t*)cpv_second)->_t_flag);
    if(((listabc_t*)cpv_first)->_t_flag == _ABC_FLAG_DESCARTES)
    {
        if((((listabc_t*)cpv_first)->_t_abc._t_descartes._n_posx <
            ((listabc_t*)cpv_second)->_t_abc._t_descartes._n_posx) &&
           (((listabc_t*)cpv_first)->_t_abc._t_descartes._n_posy <
            ((listabc_t*)cpv_second)->_t_abc._t_descartes._n_posy))
        {
            *(bool_t*)pv_output = true;
        }
        else
        {
            *(bool_t*)pv_output = false;
        }
    }
    else
    */
    {
        if(((listabc_t*)cpv_first)->_t_abc._t_complex._n_real <
           ((listabc_t*)cpv_second)->_t_abc._t_complex._n_real)
        {
            *(bool_t*)pv_output = true;
        }
        else if((((listabc_t*)cpv_first)->_t_abc._t_complex._n_real ==
                 ((listabc_t*)cpv_second)->_t_abc._t_complex._n_real) &&
                (((listabc_t*)cpv_first)->_t_abc._t_complex._n_imaginary <
                 ((listabc_t*)cpv_second)->_t_abc._t_complex._n_imaginary))
        {
            *(bool_t*)pv_output = true;
        }
        else
        {
            *(bool_t*)pv_output = false;
        }
    }
}

static void _listabc_great(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    {
        if(((listabc_t*)cpv_first)->_t_abc._t_complex._n_real >
           ((listabc_t*)cpv_second)->_t_abc._t_complex._n_real)
        {
            *(bool_t*)pv_output = true;
        }
        else if((((listabc_t*)cpv_first)->_t_abc._t_complex._n_real ==
                 ((listabc_t*)cpv_second)->_t_abc._t_complex._n_real) &&
                (((listabc_t*)cpv_first)->_t_abc._t_complex._n_imaginary >
                 ((listabc_t*)cpv_second)->_t_abc._t_complex._n_imaginary))
        {
            *(bool_t*)pv_output = true;
        }
        else
        {
            *(bool_t*)pv_output = false;
        }
    }
}

static void _remove_first_5(const void* cpv_input, void* pv_output)
{
    if(((listabc_t*)cpv_input)->_t_abc._t_complex._n_real == 5)
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}

static void _remove_mutiple_of_5(const void* cpv_input, void* pv_output)
{
    if((*(int*)cpv_input) % 5 == 0)
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}

static void _absolute_value(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    if(*(int*)cpv_first + *(int*)cpv_second == 0 ||
       *(int*)cpv_first == *(int*)cpv_second)
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}

/** eof **/

