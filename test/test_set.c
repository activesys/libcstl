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
            set_init_ex(pt_setex, fun_great_int);
            set_insert(pt_setex, 200);
            set_insert(pt_setex, 100);
            set_insert(pt_setex, -4);
            set_insert(pt_setex, 90);
            set_insert(pt_setex, 90);
            set_insert(pt_setex, 344);
            set_insert(pt_setex, -99);
            set_insert(pt_setex, 0);
            set_insert(pt_setex, 0);
            set_insert(pt_setex, 78);
            _print_set_c(pt_setex, "%d, ", int);
            set_init_copy_range_ex(pt_set, set_begin(pt_setex),
                set_end(pt_setex), fun_great_int);
            _print_set_c(pt_set, "%d, ", int);
            set_destroy(pt_set);
            set_destroy(pt_setex);
        }
        /*set_destroy           */
        /*set_assign            */
        {
            set_t* pt_set = create_set(double);
            set_t* pt_setex = create_set(double);
            if(pt_set == NULL || pt_setex == NULL)
            {
                return;
            }
            set_init_ex(pt_set, fun_great_double);
            set_init_ex(pt_setex, fun_great_double);
            set_assign(pt_set, pt_setex);
            _print_set_c(pt_set, "%lf, ", double);
            set_insert(pt_setex, 845.22);
            set_insert(pt_setex, 1223.09);
            set_insert(pt_setex, 0.0);
            set_insert(pt_setex, 2.222);
            set_insert(pt_setex, -56.8);
            set_assign(pt_set, pt_setex);
            _print_set_c(pt_set, "%lf, ", double);
            set_insert(pt_setex, -23.007);
            set_insert(pt_setex, 78.87);
            set_insert(pt_setex, 222.222);
            set_insert(pt_setex, 2.222);
            set_assign(pt_set, pt_setex);
            _print_set_c(pt_set, "%lf, ", double);
            set_erase(pt_setex, 2.222);
            set_erase(pt_setex, 78.87);
            set_erase(pt_setex, 1223.222);
            set_assign(pt_set, pt_setex);
            _print_set_c(pt_set, "%lf, ", double);
            set_clear(pt_setex);
            set_assign(pt_set, pt_setex);
            _print_set_c(pt_set, "%lf, ", double);
            set_destroy(pt_set);
            set_destroy(pt_setex);
        }
        /*set_size              */
        /*set_empty             */
        /*set_max_size          */
        /*set_begin             */
        /*set_end               */
        /*set_key_less          */
        /*set_value_less        */
        {
            set_t* pt_set = create_set(int);
            if(pt_set == NULL)
            {
                return;
            }
            set_init_ex(pt_set, fun_great_int);
            printf("%d, %d\n", set_key_less(pt_set) == fun_great_int,
                set_value_less(pt_set) == fun_great_int);
            set_destroy(pt_set);
        }
        /*set_clear             */
        {
            set_t* pt_set = create_set(double);
            if(pt_set == NULL)
            {
                return;
            }
            set_init(pt_set);
            set_clear(pt_set);
            _print_set_c(pt_set, "%lf, ", double);
            set_insert(pt_set, 44.90);
            set_insert(pt_set, -93.0);
            set_insert(pt_set, 9.3);
            set_insert(pt_set, 0.4);
            set_clear(pt_set);
            _print_set_c(pt_set, "%lf, ", double);
            set_destroy(pt_set);
        }
        /*set_equal             */
        /*set_not_equal         */
        /*set_less              */
        /*set_less_equal        */
        /*set_great             */
        /*set_great_equal       */
        {
            set_t* pt_set = create_set(int);
            set_t* pt_setex = create_set(int);
            if(pt_set == NULL || pt_setex == NULL)
            {
                return;
            }
            set_init(pt_set);
            set_init(pt_setex);
            _print_set_c(pt_set, "%d, ", int);
            _print_set_c(pt_setex, "%d, ", int);
            printf("equal: %d, not equal: %d, ",
                set_equal(pt_set, pt_setex), set_not_equal(pt_set, pt_setex));
            printf("less: %d, less equal: %d, ",
                set_less(pt_set, pt_setex), set_less_equal(pt_set, pt_setex));
            printf("great: %d, great equal: %d\n",
                set_great(pt_set, pt_setex), set_great_equal(pt_set, pt_setex));

            set_insert(pt_set, 45);
            _print_set_c(pt_set, "%d, ", int);
            _print_set_c(pt_setex, "%d, ", int);
            printf("equal: %d, not equal: %d, ",
                set_equal(pt_set, pt_setex), set_not_equal(pt_set, pt_setex));
            printf("less: %d, less equal: %d, ",
                set_less(pt_set, pt_setex), set_less_equal(pt_set, pt_setex));
            printf("great: %d, great equal: %d\n",
                set_great(pt_set, pt_setex), set_great_equal(pt_set, pt_setex));

            set_insert(pt_setex, 45);
            _print_set_c(pt_set, "%d, ", int);
            _print_set_c(pt_setex, "%d, ", int);
            printf("equal: %d, not equal: %d, ",
                set_equal(pt_set, pt_setex), set_not_equal(pt_set, pt_setex));
            printf("less: %d, less equal: %d, ",
                set_less(pt_set, pt_setex), set_less_equal(pt_set, pt_setex));
            printf("great: %d, great equal: %d\n",
                set_great(pt_set, pt_setex), set_great_equal(pt_set, pt_setex));

            set_insert(pt_set, 4);
            set_insert(pt_set, 5);
            set_insert(pt_setex, 5);
            _print_set_c(pt_set, "%d, ", int);
            _print_set_c(pt_setex, "%d, ", int);
            printf("equal: %d, not equal: %d, ",
                set_equal(pt_set, pt_setex), set_not_equal(pt_set, pt_setex));
            printf("less: %d, less equal: %d, ",
                set_less(pt_set, pt_setex), set_less_equal(pt_set, pt_setex));
            printf("great: %d, great equal: %d\n",
                set_great(pt_set, pt_setex), set_great_equal(pt_set, pt_setex));

            set_destroy(pt_set);
            set_destroy(pt_setex);
        }
        /*set_swap              */
        {
            set_t* pt_set = create_set(int);
            set_t* pt_setex = create_set(int);
            if(pt_set == NULL || pt_setex == NULL)
            {
                return;
            }
            set_init(pt_set);
            set_init(pt_setex);
            set_swap(pt_set, pt_setex);
            _print_set_c(pt_set, "%d, ", int);
            _print_set_c(pt_setex, "%d, ", int);
            set_insert(pt_setex, 56);
            set_insert(pt_setex, 2);
            set_insert(pt_setex, 0);
            set_swap(pt_set, pt_setex);
            _print_set_c(pt_set, "%d, ", int);
            _print_set_c(pt_setex, "%d, ", int);
            set_insert(pt_setex, 99);
            set_insert(pt_setex, -2);
            set_insert(pt_setex, -78);
            set_insert(pt_setex, -445);
            set_insert(pt_setex, 445);
            set_swap(pt_set, pt_setex);
            _print_set_c(pt_set, "%d, ", int);
            _print_set_c(pt_setex, "%d, ", int);
            set_clear(pt_setex);
            set_swap(pt_set, pt_setex);
            _print_set_c(pt_set, "%d, ", int);
            _print_set_c(pt_setex, "%d, ", int);

            set_destroy(pt_set);
            set_destroy(pt_setex);
        }
        /*set_find              */
        {
            set_t* pt_set = create_set(int);
            iterator_t t_iter;
            if(pt_set == NULL)
            {
                return;
            }
            set_init(pt_set);
            t_iter = set_find(pt_set, 344);
            if(!iterator_equal(t_iter, set_end(pt_set)))
            {
                printf("elem: %d, count: %u\n", *(int*)iterator_get_pointer(t_iter),
                    set_count(pt_set, 344));
            }
            else
            {
                printf("not found, count: %u\n", set_count(pt_set, 344));
            }
            set_insert(pt_set, 34);
            set_insert(pt_set, 11);
            set_insert(pt_set, 0);
            set_insert(pt_set, 79);
            set_insert(pt_set, 3);
            t_iter = set_find(pt_set, 11);
            if(!iterator_equal(t_iter, set_end(pt_set)))
            {
                printf("elem: %d, count: %u\n", *(int*)iterator_get_pointer(t_iter),
                    set_count(pt_set, 11));
            }
            else
            {
                printf("not found, count: %u\n", set_count(pt_set, 11));
            }
            t_iter = set_find(pt_set, 44);
            if(!iterator_equal(t_iter, set_end(pt_set)))
            {
                printf("elem: %d, count: %u\n", *(int*)iterator_get_pointer(t_iter),
                    set_count(pt_set, 44));
            }
            else
            {
                printf("not found, count: %u\n", set_count(pt_set, 44));
            }
            
            set_destroy(pt_set);
        }
        /*set_count             */
        /*_set_lower_bound      */
        /*_set_upper_bound      */
        /*_set_equal_range      */
        {
            set_t* pt_set = create_set(int);
            iterator_t t_begin;
            iterator_t t_end;
            range_t t_range;
            iterator_t t_iter;
            if(pt_set == NULL)
            {
                return;
            }
            set_init(pt_set);
            t_begin = set_lower_bound(pt_set, 4);
            t_end = set_upper_bound(pt_set, 4);
            t_range = set_equal_range(pt_set, 4);
            assert(iterator_equal(t_begin, set_end(pt_set)) &&
                   iterator_equal(t_end, set_end(pt_set)) &&
                   iterator_equal(t_range.t_begin, set_end(pt_set)) &&
                   iterator_equal(t_range.t_end, set_end(pt_set)));
            set_insert(pt_set, 35);
            set_insert(pt_set, 20);
            set_insert(pt_set, 233);
            set_insert(pt_set, -4);
            set_insert(pt_set, 3);
            _print_set_c(pt_set, "%d, ", int);
            t_begin = set_lower_bound(pt_set, -4);
            t_end = set_upper_bound(pt_set, -4);
            t_range = set_equal_range(pt_set, -4);
            assert(iterator_equal(t_begin, set_begin(pt_set)) &&
                   iterator_equal(t_end, iterator_next(set_begin(pt_set))) &&
                   iterator_equal(t_range.t_begin, set_begin(pt_set)) &&
                   iterator_equal(t_range.t_end, iterator_next(set_begin(pt_set))));
            t_begin = set_lower_bound(pt_set, 4);
            t_end = set_upper_bound(pt_set, 4);
            t_range = set_equal_range(pt_set, 4);
            t_iter = set_lower_bound(pt_set, 4);
            printf("%d\n", *(int*)iterator_get_pointer(t_iter));
            assert(iterator_equal(t_begin, t_iter) &&
                   iterator_equal(t_end, t_iter) &&
                   iterator_equal(t_range.t_begin, t_iter) &&
                   iterator_equal(t_range.t_end, t_iter));

            set_destroy(pt_set);
        }
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
        /*set_insert_hint       */
        {
            set_t* pt_set = create_set(double);
            iterator_t t_iter;
            if(pt_set == NULL)
            {
                return;
            }
            set_init(pt_set);
            _print_set_c(pt_set, "%lf, ", double);
            set_insert_hint(pt_set, t_iter, 45.6);
            set_insert_hint(pt_set, t_iter, 0.9);
            set_insert_hint(pt_set, t_iter, 22.34);
            set_insert_hint(pt_set, t_iter, -8.9);
            set_insert_hint(pt_set, t_iter, 324.2);
            _print_set_c(pt_set, "%lf, ", double);
            set_destroy(pt_set);
        }
        /*set_insert_range      */
        {
            set_t* pt_set = create_set(int);
            set_t* pt_setex = create_set(int);
            if(pt_set == NULL || pt_setex == NULL)
            {
                return;
            }
            set_init(pt_set);
            set_init(pt_setex);
            set_insert_range(pt_set, set_begin(pt_setex), set_end(pt_setex));
            _print_set_c(pt_set, "%d, ", int);
            set_insert(pt_setex, 445);
            set_insert(pt_setex, -84);
            set_insert(pt_setex, 45);
            set_insert(pt_setex, 2);
            set_insert(pt_setex, 0);
            set_insert(pt_setex, 49);
            set_insert(pt_setex, 23);
            set_insert(pt_setex, -7);
            set_insert(pt_setex, 12);
            set_insert(pt_setex, 8);
            set_insert(pt_setex, 55);
            set_insert(pt_setex, 3);
            _print_set_c(pt_setex, "%d, ", int);
            set_insert_range(pt_set, set_begin(pt_setex), set_begin(pt_setex));
            _print_set_c(pt_set, "%d, ", int);
            set_insert_range(pt_set, set_begin(pt_setex),
                iterator_advance(set_begin(pt_setex), 3));
            _print_set_c(pt_set, "%d, ", int);
            set_insert_range(pt_set, iterator_advance(set_begin(pt_setex), 5),
                iterator_advance(set_begin(pt_setex), 7));
            _print_set_c(pt_set, "%d, ", int);
            set_insert_range(pt_set, iterator_advance(set_begin(pt_setex), 9),
                set_end(pt_setex));
            _print_set_c(pt_set, "%d, ", int);
            set_insert_range(pt_set, set_end(pt_setex), set_end(pt_setex));
            _print_set_c(pt_set, "%d, ", int);
            set_clear(pt_setex);
            set_insert(pt_setex, 100);
            set_insert(pt_setex, 200);
            set_insert(pt_setex, 300);
            set_insert(pt_setex, 400);
            set_insert_range(pt_set, set_begin(pt_setex), set_end(pt_setex));
            _print_set_c(pt_set, "%d, ", int);
            set_destroy(pt_set);
            set_destroy(pt_setex);
        }
        /*set_erase             */
        {
        }
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

