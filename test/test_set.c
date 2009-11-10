/*
 *  The implementation of set_t and multiset_t test.
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
#include <assert.h>

#include "cset.h"
#include "cfunctional.h"
#include "test_set.h"

/** local constant declaration and local macro section **/
#define _print_set_c(pt_set, fmt, type)\
    do{\
        iterator_t t_iter;\
        printf("=======================================\n");\
        printf("empty: %u, size: %u, max_size: %u\n",\
            set_empty(pt_set), set_size(pt_set), set_max_size(pt_set));\
        for(t_iter = set_begin(pt_set);\
            !iterator_equal(t_iter, set_end(pt_set));\
            t_iter = iterator_next(t_iter))\
        {\
            printf(fmt, *(type*)iterator_get_pointer(t_iter));\
        }\
        printf("\n");\
    }while(false)

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
void test_set(void)
{
    /* c built-in type */
    {
        /*create_set            */
        {
            set_t* pt_set = create_set(int);
            if(pt_set == NULL)
            {
                return;
            }
            set_init(pt_set);
            _print_set_c(pt_set, "%d, ", int);
            set_destroy(pt_set);
        }
        /*set_init              */
        /*set_init_ex           */
        {
            set_t* pt_set = create_set(double);
            if(pt_set == NULL)
            {
                return;
            }
            set_init_ex(pt_set, fun_great_double);
            _print_set_c(pt_set, "%lf, ", double);
            set_insert(pt_set, 45.98);
            set_insert(pt_set, -4.098);
            set_insert(pt_set, 0.042);
            set_insert(pt_set, -4.008);
            set_insert(pt_set, 34.2);
            _print_set_c(pt_set, "%lf, ", double);
            set_destroy(pt_set);
        }
        /*set_init_copy         */
        {
            set_t* pt_set = create_set(int);
            set_t* pt_setex = create_set(int);
            if(pt_set == NULL || pt_setex == NULL)
            {
                return;
            }
            set_init_ex(pt_setex, fun_great_int);
            set_insert(pt_setex, 800);
            set_insert(pt_setex, 400);
            set_insert(pt_setex, 20);
            set_insert(pt_setex, 556);
            set_insert(pt_setex, 1220);
            set_init_copy(pt_set, pt_setex);
            _print_set_c(pt_set, "%d, ", int);
            set_destroy(pt_set);
            set_destroy(pt_setex);
        }
        /*set_init_copy_range   */
        {
            set_t* pt_set = create_set(double);
            set_t* pt_setex = create_set(double);
            if(pt_set == NULL || pt_setex == NULL)
            {
                return;
            }
            set_init_ex(pt_setex, fun_great_double);
            set_insert(pt_setex, 34.2);
            set_insert(pt_setex, 0.91);
            set_insert(pt_setex, -4.4);
            set_insert(pt_setex, 11.2);
            set_insert(pt_setex, -90.9);
            set_insert(pt_setex, 3.998);
            set_insert(pt_setex, -0.98);
            set_insert(pt_setex, 12.0845);
            set_insert(pt_setex, 3.4);
            _print_set_c(pt_setex, "%lf, ", double);
            set_init_copy_range(pt_set, set_begin(pt_setex), set_end(pt_setex));
            _print_set_c(pt_set, "%lf, ", double);
            set_destroy(pt_set);
            set_destroy(pt_setex);
        }
        /*set_init_copy_range_ex*/
        {
            set_t* pt_set = create_set(int);
            set_t* pt_setex = create_set(int);
            if(pt_set == NULL || pt_setex == NULL)
            {
                return;
            }
            set_init(pt_setex);
            set_insert(pt_setex, 200);
            set_insert(pt_setex, 100);
            set_insert(pt_setex, -4);
            set_insert(pt_setex, 90);
            set_insert(pt_setex, 344);
            set_insert(pt_setex, -99);
            set_insert(pt_setex, 0);
            set_insert(pt_setex, 78);
            _print_set_c(pt_setex, "%d, ", int);
            /* bug in _rb_tree_same_type */
            set_init_copy_range_ex(pt_set, set_begin(pt_setex),
                set_begin(pt_setex), fun_great_int);
            _print_set_c(pt_set, "%d, ", int);
            set_destroy(pt_set);
            set_destroy(pt_setex);
        }
        /*set_destroy           */
        /*set_assign            */
        /*set_size              */
        /*set_empty             */
        /*set_max_size          */
        /*set_begin             */
        /*set_end               */
        /*set_key_less          */
        /*set_value_less        */
        /*set_clear             */
        /*set_equal             */
        /*set_not_equal         */
        /*set_less              */
        /*set_less_equal        */
        /*set_great             */
        /*set_great_equal       */
        /*set_swap              */
        /*_set_find             */
        /*_set_count            */
        /*_set_lower_bound      */
        /*_set_upper_bound      */
        /*_set_equal_range      */
        /*set_insert            */
        {
            set_t* pt_set = create_set(int);
            if(pt_set == NULL)
            {
                return;
            }
            set_init(pt_set);
            _print_set_c(pt_set, "%d, ", int);
            set_insert(pt_set, 100);
            set_insert(pt_set, -34);
            set_insert(pt_set, 23);
            set_insert(pt_set, 112);
            _print_set_c(pt_set, "%d, ", int);
            set_destroy(pt_set);
        }
        /*_set_insert_hint      */
        /*set_insert_range      */
        /*_set_erase            */
        /*set_erase_pos         */
        /*set_erase_range       */
    }
    /* user defined type */
    {
    }
    /* cstl defined type */
    {
    }
    /* c-str type */
    {
    }
    /*_create_set           */
    /*set_init              */
    /*set_init_ex           */
    /*set_init_copy         */
    /*set_init_copy_range   */
    /*set_init_copy_range_ex*/
    /*set_destroy           */
    /*set_assign            */
    /*set_size              */
    /*set_empty             */
    /*set_max_size          */
    /*set_begin             */
    /*set_end               */
    /*set_key_less          */
    /*set_value_less        */
    /*set_clear             */
    /*set_equal             */
    /*set_not_equal         */
    /*set_less              */
    /*set_less_equal        */
    /*set_great             */
    /*set_great_equal       */
    /*set_swap              */
    /*_set_find             */
    /*_set_count            */
    /*_set_lower_bound      */
    /*_set_upper_bound      */
    /*_set_equal_range      */
    /*_set_insert           */
    /*_set_insert_hint      */
    /*set_insert_range      */
    /*_set_erase            */
    /*set_erase_pos         */
    /*set_erase_range       */
}

/** local function implementation section **/

/** eof **/

