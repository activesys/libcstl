/*
 *  The implementation of list test.
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
static void _remove_mutiple_of_5(const void* cpv_input, void* pv_output);
static void _absolute_value(const void* cpv_first, const void* cpv_second, void* pv_output);

static void _listabc_init(const void* cpv_input, void* pv_output);
static void _listabc_destory(const void* cpv_input, void* pv_output);
static void _listabc_copy(const void* cpv_first, const void* cpv_second, void* pv_output);
static void _listabc_less(const void* cpv_first, const void* cpv_second, void* pv_output);

static void _printlist_user(const list_t* cpt_list);
static void _remove_first_5(const void* cpv_input, void* pv_output);
static void _listabc_great(const void* cpv_first, const void* cpv_second, void* pv_output);

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
    /* for c-string type */
    /*create_list         */
    /*list_init           */
    /*list_init_n         */
    /*_list_init_elem     */
    /*list_init_copy      */
    /*list_init_copy_range*/
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
    /*list_assign         */
    /*_list_assign_elem   */
    /*list_assign_range   */
    /*list_swap           */
    /*list_front          */
    /*list_back           */
    /*list_begin          */
    /*list_end            */
    /*_list_insert_n      */
    /*list_insert_range   */
    /*_list_push_back     */
    /*list_pop_back       */
    /*_list_push_front    */
    /*list_pop_front      */
    /*list_erase          */
    /*list_erase_range    */
    /*_list_remove        */
    /*list_remove_if      */
    /*list_resize         */
    /*_list_resize_elem   */
    /*list_clear          */
    /*list_unique         */
    /*list_unique_if      */
    /*list_splice         */
    /*list_splice_pos     */
    /*list_splice_range   */
    /*list_sort           */
    /*list_sort_if        */
    /*list_merge          */
    /*list_merge_if       */
    /*list_reverse        */
}

/** local function implementation section **/
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

