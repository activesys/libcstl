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
#include <string.h>

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
typedef struct _tagsetsample
{
    int _n_first;
    int _n_second;
    int _n_third;
}setsample_t;

/** local function prototype section **/
static void _set_cstr_pre(const void* cpv_first, const void* cpv_second, void* pv_output);
static void _print_set_cstr(const set_t* cpt_set);
static void _print_set_set(const set_t* cpt_set);
static void _print_set_user(const set_t* cpt_set);
static void _setsample_init(const void* cpv_input, void* pv_output);
static void _setsample_destroy(const void* cpv_input, void* pv_output);
static void _setsample_less(const void* cpv_first, const void* cpv_second, void* pv_output);
static void _setsample_great(const void* cpv_first, const void* cpv_second, void* pv_output);
static void _setsample_copy(const void* cpv_first, const void* cpv_second, void* pv_output);

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
            t_iter = set_begin(pt_set);
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
            set_t* pt_set = create_set(int);
            size_t t_count = 0;
            if(pt_set == NULL)
            {
                return;
            }
            set_init(pt_set);
            t_count = set_erase(pt_set, 40);
            printf("%d\n", t_count);
            _print_set_c(pt_set, "%d, ", int);
            set_insert(pt_set, 2);
            set_insert(pt_set, 90);
            set_insert(pt_set, 23);
            set_insert(pt_set, 6);
            set_insert(pt_set, -4);
            _print_set_c(pt_set, "%d, ", int);
            t_count = set_erase(pt_set, 44);
            printf("%d\n", t_count);
            _print_set_c(pt_set, "%d, ", int);
            t_count = set_erase(pt_set, 90);
            printf("%d\n", t_count);
            _print_set_c(pt_set, "%d, ", int);
            set_destroy(pt_set);
        }
        /*set_erase_pos         */
        {
            set_t* pt_set = create_set(int);
            if(pt_set == NULL)
            {
                return;
            }
            set_init(pt_set);
            set_insert(pt_set, 78);
            set_insert(pt_set, 4);
            set_insert(pt_set, 0);
            set_insert(pt_set, 23);
            set_insert(pt_set, 44);
            set_insert(pt_set, 3);
            _print_set_c(pt_set, "%d, ", int);
            set_erase_pos(pt_set, set_begin(pt_set));
            _print_set_c(pt_set, "%d, ", int);
            set_erase_pos(pt_set, iterator_prev(set_end(pt_set)));
            _print_set_c(pt_set, "%d, ", int);
            set_erase_pos(pt_set, iterator_next(set_begin(pt_set)));
            _print_set_c(pt_set, "%d, ", int);
            set_destroy(pt_set);
        }
        /*set_erase_range       */
        {
            set_t* pt_set = create_set(int);
            if(pt_set == NULL)
            {
                return;
            }
            set_init(pt_set);
            set_erase_range(pt_set, set_begin(pt_set), set_end(pt_set));
            _print_set_c(pt_set, "%d, ", int);
            set_insert(pt_set, 78);
            set_insert(pt_set, 4);
            set_insert(pt_set, 0);
            set_insert(pt_set, 23);
            set_insert(pt_set, 44);
            set_insert(pt_set, 3);
            set_insert(pt_set, 2);
            set_insert(pt_set, 90);
            set_insert(pt_set, 23);
            set_insert(pt_set, 6);
            set_insert(pt_set, -4);
            set_insert(pt_set, 445);
            set_insert(pt_set, -84);
            set_insert(pt_set, 45);
            set_insert(pt_set, 2);
            set_insert(pt_set, 0);
            set_insert(pt_set, 49);
            set_insert(pt_set, 23);
            set_insert(pt_set, -7);
            set_insert(pt_set, 12);
            set_insert(pt_set, 8);
            set_insert(pt_set, 55);
            set_insert(pt_set, 3);
            _print_set_c(pt_set, "%d, ", int);
            set_erase_range(pt_set, set_begin(pt_set), set_begin(pt_set));
            _print_set_c(pt_set, "%d, ", int);
            set_erase_range(pt_set, set_begin(pt_set), iterator_advance(set_begin(pt_set), 3));
            _print_set_c(pt_set, "%d, ", int);
            set_erase_range(pt_set, iterator_advance(set_begin(pt_set), 5),
                iterator_advance(set_begin(pt_set), 9));
            _print_set_c(pt_set, "%d, ", int);
            set_erase_range(pt_set, iterator_advance(set_begin(pt_set), 10), set_end(pt_set));
            _print_set_c(pt_set, "%d, ", int);
            set_erase_range(pt_set, set_end(pt_set), set_end(pt_set));
            _print_set_c(pt_set, "%d, ", int);
            set_erase_range(pt_set, set_begin(pt_set), set_end(pt_set));
            _print_set_c(pt_set, "%d, ", int);
            set_destroy(pt_set);
        }
    }
    /* user defined type */
    {
        type_register(setsample_t, _setsample_init,
            _setsample_copy, _setsample_less, _setsample_destroy);
        type_duplicate(setsample_t, struct _tagsetsample);
        _type_debug();
        /*create_set            */
        {
            set_t* pt_set = create_set(setsample_t);
            if(pt_set == NULL)
            {
                return;
            }
            set_init(pt_set);
            _print_set_user(pt_set);
            set_destroy(pt_set);
        }
        /*set_init              */
        /*set_init_ex           */
        {
            set_t* pt_set = create_set(setsample_t);
            if(pt_set == NULL)
            {
                return;
            }
            set_init_ex(pt_set, _setsample_great);
            _print_set_user(pt_set);
            set_destroy(pt_set);
        }
        /*set_init_copy         */
        {
            set_t* pt_set = create_set(setsample_t);
            set_t* pt_setex = create_set(setsample_t);
            setsample_t t_ss;
            if(pt_set == NULL || pt_setex == NULL)
            {
                return;
            }
            set_init_ex(pt_setex, _setsample_great);
            t_ss._n_first = 40;
            t_ss._n_second = -45;
            t_ss._n_third = 223;
            set_insert(pt_setex, &t_ss);
            t_ss._n_first = 2;
            t_ss._n_second = -4455;
            t_ss._n_third = -90;
            set_insert(pt_setex, &t_ss);
            t_ss._n_first = 78;
            t_ss._n_second = -456;
            t_ss._n_third = 123;
            set_insert(pt_setex, &t_ss);
            set_init_copy(pt_set, pt_setex);
            _print_set_user(pt_set);
            set_destroy(pt_set);
            set_destroy(pt_setex);
        }
        /*set_init_copy_range   */
        {
            set_t* pt_set = create_set(setsample_t);
            set_t* pt_setex = create_set(setsample_t);
            setsample_t t_ss;
            if(pt_set == NULL || pt_setex == NULL)
            {
                return;
            }
            /* 
             * error in _rb_tree_init_copy_range and _rb_tree_init_copy_range_ex and
             * _rb_tree_same_type functions.
             */
            set_init_ex(pt_setex, _setsample_great);
            t_ss._n_first = -9;
            t_ss._n_second = 5;
            t_ss._n_third = 4;
            set_insert(pt_setex, &t_ss);
            t_ss._n_first = 12;
            t_ss._n_second = 5;
            t_ss._n_third = 789;
            set_insert(pt_setex, &t_ss);
            t_ss._n_first = 12;
            t_ss._n_second = 5;
            t_ss._n_third = 7;
            set_insert(pt_setex, &t_ss);
            t_ss._n_first = 66;
            t_ss._n_second = 66;
            t_ss._n_third = 66;
            set_insert(pt_setex, &t_ss);
            _print_set_user(pt_setex);
            set_init_copy_range(pt_set, set_begin(pt_setex), set_end(pt_setex));
            _print_set_user(pt_set);
            set_destroy(pt_set);
            set_destroy(pt_setex);
        }
        /*set_init_copy_range_ex*/
        {
            set_t* pt_set = create_set(setsample_t);
            set_t* pt_setex = create_set(setsample_t);
            setsample_t t_ss;
            if(pt_set == NULL || pt_setex == NULL)
            {
                return;
            }
            set_init_ex(pt_setex, _setsample_great);
            t_ss._n_first = 56;
            t_ss._n_second = 3;
            t_ss._n_third = 344;
            set_insert(pt_setex, &t_ss);
            t_ss._n_first = 3;
            t_ss._n_second = 89;
            t_ss._n_third = 3;
            set_insert(pt_setex, &t_ss);
            t_ss._n_first = -8;
            t_ss._n_second = 3;
            t_ss._n_third = 3;
            set_insert(pt_setex, &t_ss);
            t_ss._n_first = -6;
            t_ss._n_second = -3;
            t_ss._n_third = 999;
            set_insert(pt_setex, &t_ss);
            t_ss._n_first = 56;
            t_ss._n_second = 90;
            t_ss._n_third = 344;
            set_insert(pt_setex, &t_ss);
            t_ss._n_first = 50;
            t_ss._n_second = 3;
            t_ss._n_third = 34;
            set_insert(pt_setex, &t_ss);
            _print_set_user(pt_setex);
            set_init_copy_range_ex(pt_set, set_begin(pt_setex),
                set_end(pt_setex), _setsample_less);
            _print_set_user(pt_set);
            set_destroy(pt_set);
            set_destroy(pt_setex);
        }
        /*set_destroy           */
        /*set_assign            */
        {
            set_t* pt_set = create_set(setsample_t);
            set_t* pt_setex = create_set(setsample_t);
            setsample_t t_ss;
            if(pt_set == NULL || pt_setex == NULL)
            {
                return;
            }
            set_init_ex(pt_set, _setsample_great);
            set_init_ex(pt_setex, _setsample_great);
            set_assign(pt_set, pt_setex);
            _print_set_user(pt_set);
            t_ss._n_first = 0;
            t_ss._n_second = 89;
            t_ss._n_third = 4;
            set_insert(pt_setex, &t_ss);
            t_ss._n_first = 4;
            t_ss._n_second = -9;
            t_ss._n_third = 45;
            set_insert(pt_setex, &t_ss);
            t_ss._n_first = 9;
            t_ss._n_second = -1;
            t_ss._n_third = 5;
            set_insert(pt_setex, &t_ss);
            t_ss._n_first = 19;
            t_ss._n_second = -11;
            t_ss._n_third = 15;
            set_insert(pt_setex, &t_ss);
            t_ss._n_first = -9;
            t_ss._n_second = -11;
            t_ss._n_third = 50;
            set_insert(pt_setex, &t_ss);
            t_ss._n_first = 90;
            t_ss._n_second = -10;
            t_ss._n_third = -5;
            set_insert(pt_setex, &t_ss);
            /*_print_set_user(pt_setex);*/
            set_assign(pt_set, pt_setex);
            _print_set_user(pt_set);
            set_clear(pt_setex);
            set_assign(pt_set, pt_setex);
            _print_set_user(pt_set);
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
            set_t* pt_set = create_set(setsample_t);
            if(pt_set == NULL)
            {
                return;
            }
            set_init(pt_set);
            assert(set_key_less(pt_set) == _setsample_less);
            assert(set_value_less(pt_set) == _setsample_less);
            set_destroy(pt_set);
        }
        /*set_clear             */
        {
            set_t* pt_set = create_set(setsample_t);
            setsample_t t_ss;
            if(pt_set == NULL)
            {
                return;
            }
            set_init(pt_set);
            set_clear(pt_set);
            _print_set_user(pt_set);
            t_ss._n_first = 45;
            t_ss._n_second = 89;
            t_ss._n_third = 9;
            set_insert(pt_set, &t_ss);
            t_ss._n_first = 3;
            t_ss._n_second = 5;
            t_ss._n_third = 56;
            set_insert(pt_set, &t_ss);
            t_ss._n_first = 8;
            t_ss._n_second = 0;
            t_ss._n_third = 1;
            set_insert(pt_set, &t_ss);
            _print_set_user(pt_set);
            set_clear(pt_set);
            _print_set_user(pt_set);
            set_destroy(pt_set);
        }
        /*set_equal             */
        /*set_not_equal         */
        /*set_less              */
        /*set_less_equal        */
        /*set_great             */
        /*set_great_equal       */
        {
            set_t* pt_set = create_set(setsample_t);
            set_t* pt_setex = create_set(setsample_t);
            setsample_t t_ss;
            if(pt_set == NULL || pt_setex == NULL)
            {
                return;
            }
            set_init(pt_set);
            set_init(pt_setex);
            _print_set_user(pt_set);
            _print_set_user(pt_setex);
            printf("equal: %d, not equal: %d, ",
                set_equal(pt_set, pt_setex), set_not_equal(pt_set, pt_setex));
            printf("less: %d, less equal: %d, ",
                set_less(pt_set, pt_setex), set_less_equal(pt_set, pt_setex));
            printf("great: %d, great equal: %d\n",
                set_great(pt_set, pt_setex), set_great_equal(pt_set, pt_setex));

            t_ss._n_first = 9;
            t_ss._n_second = 45;
            t_ss._n_third = -9;
            set_insert(pt_set, &t_ss);
            _print_set_user(pt_set);
            _print_set_user(pt_setex);
            printf("equal: %d, not equal: %d, ",
                set_equal(pt_set, pt_setex), set_not_equal(pt_set, pt_setex));
            printf("less: %d, less equal: %d, ",
                set_less(pt_set, pt_setex), set_less_equal(pt_set, pt_setex));
            printf("great: %d, great equal: %d\n",
                set_great(pt_set, pt_setex), set_great_equal(pt_set, pt_setex));

            t_ss._n_first = 9;
            t_ss._n_second = 45;
            t_ss._n_third = -9;
            set_insert(pt_setex, &t_ss);
            _print_set_user(pt_set);
            _print_set_user(pt_setex);
            printf("equal: %d, not equal: %d, ",
                set_equal(pt_set, pt_setex), set_not_equal(pt_set, pt_setex));
            printf("less: %d, less equal: %d, ",
                set_less(pt_set, pt_setex), set_less_equal(pt_set, pt_setex));
            printf("great: %d, great equal: %d\n",
                set_great(pt_set, pt_setex), set_great_equal(pt_set, pt_setex));

            t_ss._n_first = 9;
            t_ss._n_second = 45;
            t_ss._n_third = -9;
            set_insert(pt_setex, &t_ss);
            _print_set_user(pt_set);
            _print_set_user(pt_setex);
            printf("equal: %d, not equal: %d, ",
                set_equal(pt_set, pt_setex), set_not_equal(pt_set, pt_setex));
            printf("less: %d, less equal: %d, ",
                set_less(pt_set, pt_setex), set_less_equal(pt_set, pt_setex));
            printf("great: %d, great equal: %d\n",
                set_great(pt_set, pt_setex), set_great_equal(pt_set, pt_setex));

            t_ss._n_first = 49;
            t_ss._n_second = 45;
            t_ss._n_third = -9;
            set_insert(pt_setex, &t_ss);
            t_ss._n_first = 49;
            t_ss._n_second = 5;
            t_ss._n_third = -9;
            set_insert(pt_set, &t_ss);
            t_ss._n_first = -9;
            t_ss._n_second = 5;
            t_ss._n_third = -9;
            set_insert(pt_set, &t_ss);
            _print_set_user(pt_set);
            _print_set_user(pt_setex);
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
            set_t* pt_set = create_set(setsample_t);
            set_t* pt_setex = create_set(setsample_t);
            setsample_t t_ss;
            if(pt_set == NULL || pt_setex == NULL)
            {
                return;
            }
            set_init(pt_set);
            set_init(pt_setex);
            set_swap(pt_set, pt_setex);
            _print_set_user(pt_set);
            _print_set_user(pt_setex);
            t_ss._n_first = 0;
            t_ss._n_second = 5;
            t_ss._n_third = 8;
            set_insert(pt_setex, &t_ss);
            t_ss._n_first = 9;
            t_ss._n_second = 45;
            t_ss._n_third = 8;
            set_insert(pt_setex, &t_ss);
            set_swap(pt_set, pt_setex);
            _print_set_user(pt_set);
            _print_set_user(pt_setex);
            t_ss._n_first = -9;
            t_ss._n_second = 7;
            t_ss._n_third = 9;
            set_insert(pt_setex, &t_ss);
            t_ss._n_first = 4;
            t_ss._n_second = 5;
            t_ss._n_third = 1;
            set_insert(pt_setex, &t_ss);
            t_ss._n_first = 5;
            t_ss._n_second = 8;
            t_ss._n_third = 8;
            set_insert(pt_setex, &t_ss);
            t_ss._n_first = 9;
            t_ss._n_second = 0;
            t_ss._n_third = 0;
            set_insert(pt_setex, &t_ss);
            set_swap(pt_set, pt_setex);
            _print_set_user(pt_set);
            _print_set_user(pt_setex);
            set_clear(pt_setex);
            set_swap(pt_set, pt_setex);
            _print_set_user(pt_set);
            _print_set_user(pt_setex);
            set_destroy(pt_set);
            set_destroy(pt_setex);
        }
        /*set_find              */
        {
            set_t* pt_set = create_set(setsample_t);
            setsample_t t_ss;
            iterator_t t_iter;
            size_t t_count = 0;
            if(pt_set == NULL)
            {
                return;
            }
            set_init(pt_set);
            t_iter = set_find(pt_set, &t_ss);
            t_count = set_count(pt_set, &t_ss);
            if(iterator_equal(t_iter, set_end(pt_set)))
            {
                printf("<%d, %d, %d> not found, count: %d!\n",
                    t_ss._n_first, t_ss._n_second, t_ss._n_third, t_count);
            }
            else
            {
                printf("<%d, %d, %d>, count: %d\n",
                    ((setsample_t*)iterator_get_pointer(t_iter))->_n_first,
                    ((setsample_t*)iterator_get_pointer(t_iter))->_n_second,
                    ((setsample_t*)iterator_get_pointer(t_iter))->_n_third,
                    t_count);
            }

            t_ss._n_first = 98;
            t_ss._n_second = 4;
            t_ss._n_third = 0;
            set_insert(pt_set, &t_ss);
            t_ss._n_first = -8;
            t_ss._n_second = -4;
            t_ss._n_third = -9;
            set_insert(pt_set, &t_ss);
            t_ss._n_first = 9;
            t_ss._n_second = 4;
            t_ss._n_third = 70;
            set_insert(pt_set, &t_ss);
            _print_set_user(pt_set);

            t_ss._n_first = 34;
            t_ss._n_second = 56;
            t_ss._n_third = 1;
            t_iter = set_find(pt_set, &t_ss);
            t_count = set_count(pt_set, &t_ss);
            if(iterator_equal(t_iter, set_end(pt_set)))
            {
                printf("<%d, %d, %d> not found, count: %d!\n",
                    t_ss._n_first, t_ss._n_second, t_ss._n_third, t_count);
            }
            else
            {
                printf("<%d, %d, %d>, count: %d\n",
                    ((setsample_t*)iterator_get_pointer(t_iter))->_n_first,
                    ((setsample_t*)iterator_get_pointer(t_iter))->_n_second,
                    ((setsample_t*)iterator_get_pointer(t_iter))->_n_third,
                    t_count);
            }

            t_ss._n_first = -8;
            t_ss._n_second = -4;
            t_ss._n_third = -9;
            t_iter = set_find(pt_set, &t_ss);
            t_count = set_count(pt_set, &t_ss);
            if(iterator_equal(t_iter, set_end(pt_set)))
            {
                printf("<%d, %d, %d> not found, count: %d!\n",
                    t_ss._n_first, t_ss._n_second, t_ss._n_third, t_count);
            }
            else
            {
                printf("<%d, %d, %d>, count: %d\n",
                    ((setsample_t*)iterator_get_pointer(t_iter))->_n_first,
                    ((setsample_t*)iterator_get_pointer(t_iter))->_n_second,
                    ((setsample_t*)iterator_get_pointer(t_iter))->_n_third,
                    t_count);
            }

            set_destroy(pt_set);
        }
        /*_set_count            */
        /*_set_lower_bound      */
        /*_set_upper_bound      */
        /*_set_equal_range      */
        {
            set_t* pt_set = create_set(setsample_t);
            iterator_t t_begin;
            iterator_t t_end;
            range_t t_range;
            iterator_t t_iter;
            setsample_t t_ss;
            if(pt_set == NULL)
            {
                return;
            }
            set_init(pt_set);
            t_begin = set_lower_bound(pt_set, &t_ss);
            t_end = set_upper_bound(pt_set, &t_ss);
            t_range = set_equal_range(pt_set, &t_ss);
            assert(iterator_equal(t_begin, set_end(pt_set)) &&
                   iterator_equal(t_end, set_end(pt_set)) &&
                   iterator_equal(t_range.t_begin, set_end(pt_set)) &&
                   iterator_equal(t_range.t_end, set_end(pt_set)));
            t_ss._n_first = 35;
            t_ss._n_second = 33;
            t_ss._n_third = 21;
            set_insert(pt_set, &t_ss);
            t_ss._n_first = 20;
            t_ss._n_second = -3;
            t_ss._n_third = 2;
            set_insert(pt_set, &t_ss);
            t_ss._n_first = 23;
            t_ss._n_second = 33;
            t_ss._n_third = 23;
            set_insert(pt_set, &t_ss);
            t_ss._n_first = -4;
            t_ss._n_second = -4;
            t_ss._n_third = -4;
            set_insert(pt_set, &t_ss);
            t_ss._n_first = 2;
            t_ss._n_second = 43;
            t_ss._n_third = 3;
            set_insert(pt_set, &t_ss);
            t_ss._n_first = 3;
            t_ss._n_second = 43;
            t_ss._n_third = 3;
            set_insert(pt_set, &t_ss);
            _print_set_user(pt_set);
            t_ss._n_first = -4;
            t_ss._n_second = -4;
            t_ss._n_third = -4;
            t_begin = set_lower_bound(pt_set, &t_ss);
            t_end = set_upper_bound(pt_set, &t_ss);
            t_range = set_equal_range(pt_set, &t_ss);
            assert(iterator_equal(t_begin, set_begin(pt_set)) &&
                   iterator_equal(t_end, iterator_next(set_begin(pt_set))) &&
                   iterator_equal(t_range.t_begin, set_begin(pt_set)) &&
                   iterator_equal(t_range.t_end, iterator_next(set_begin(pt_set))));
            t_ss._n_first = 4;
            t_ss._n_second = 4;
            t_ss._n_third = 4;
            t_begin = set_lower_bound(pt_set, &t_ss);
            t_end = set_upper_bound(pt_set, &t_ss);
            t_range = set_equal_range(pt_set, &t_ss);
            t_iter = set_lower_bound(pt_set, &t_ss);
            printf("<%d, %d, %d>\n",
                ((setsample_t*)iterator_get_pointer(t_iter))->_n_first,
                ((setsample_t*)iterator_get_pointer(t_iter))->_n_second,
                ((setsample_t*)iterator_get_pointer(t_iter))->_n_third);
            assert(iterator_equal(t_begin, t_iter) &&
                   iterator_equal(t_end, t_iter) &&
                   iterator_equal(t_range.t_begin, t_iter) &&
                   iterator_equal(t_range.t_end, t_iter));

            set_destroy(pt_set);
        }
        /*set_insert            */
        {
            set_t* pt_set = create_set(setsample_t);
            setsample_t t_ss;
            if(pt_set == NULL)
            {
                return;
            }
            set_init_ex(pt_set, _setsample_great);
            _print_set_user(pt_set);
            t_ss._n_first = 100;
            t_ss._n_second = 200;
            t_ss._n_third = 300;
            set_insert(pt_set, &t_ss);
            t_ss._n_first = 49;
            t_ss._n_second = 209;
            t_ss._n_third = 45;
            set_insert(pt_set, &t_ss);
            t_ss._n_first = 100;
            t_ss._n_second = 4;
            t_ss._n_third = -45;
            set_insert(pt_set, &t_ss);
            _print_set_user(pt_set);

            set_destroy(pt_set);
        }
        /*set_insert_hint       */
        {
            set_t* pt_set = create_set(setsample_t);
            iterator_t t_iter;
            setsample_t t_ss;
            if(pt_set == NULL)
            {
                return;
            }
            set_init(pt_set);
            t_iter = set_begin(pt_set);
            t_ss._n_first = 5;
            t_ss._n_second = 6;
            t_ss._n_third = 7;
            set_insert_hint(pt_set, t_iter, &t_ss);
            t_ss._n_first = 9;
            t_ss._n_second = 4;
            t_ss._n_third = 0;
            set_insert_hint(pt_set, t_iter, &t_ss);
            t_ss._n_first = 4;
            t_ss._n_second = -98;
            t_ss._n_third = 2;
            set_insert_hint(pt_set, t_iter, &t_ss);
            t_ss._n_first = 0;
            t_ss._n_second = 5;
            t_ss._n_third = 12;
            set_insert_hint(pt_set, t_iter, &t_ss);
            _print_set_user(pt_set);
            set_destroy(pt_set);
        }
        /*set_insert_range      */
        {
            set_t* pt_set = create_set(setsample_t);
            set_t* pt_setex = create_set(setsample_t);
            setsample_t t_ss;
            if(pt_set == NULL || pt_setex == NULL)
            {
                return;
            }
            set_init_ex(pt_set, _setsample_great);
            set_init(pt_setex);
            set_insert_range(pt_set, set_begin(pt_setex), set_end(pt_setex));
            _print_set_user(pt_set);
            t_ss._n_first = 100;
            t_ss._n_second = 200;
            t_ss._n_third = 300;
            set_insert(pt_setex, &t_ss);
            t_ss._n_first = 49;
            t_ss._n_second = 209;
            t_ss._n_third = 45;
            set_insert(pt_setex, &t_ss);
            t_ss._n_first = 100;
            t_ss._n_second = 4;
            t_ss._n_third = -45;
            set_insert(pt_setex, &t_ss);
            t_ss._n_first = 35;
            t_ss._n_second = 33;
            t_ss._n_third = 21;
            set_insert(pt_setex, &t_ss);
            t_ss._n_first = 20;
            t_ss._n_second = -3;
            t_ss._n_third = 2;
            set_insert(pt_setex, &t_ss);
            t_ss._n_first = 23;
            t_ss._n_second = 33;
            t_ss._n_third = 23;
            set_insert(pt_setex, &t_ss);
            t_ss._n_first = -4;
            t_ss._n_second = -4;
            t_ss._n_third = -4;
            set_insert(pt_setex, &t_ss);
            t_ss._n_first = 2;
            t_ss._n_second = 43;
            t_ss._n_third = 3;
            set_insert(pt_setex, &t_ss);
            t_ss._n_first = 3;
            t_ss._n_second = 43;
            t_ss._n_third = 3;
            set_insert(pt_setex, &t_ss);
            t_ss._n_first = 4;
            t_ss._n_second = 4;
            t_ss._n_third = 4;
            set_insert(pt_setex, &t_ss);
            _print_set_user(pt_setex);
            set_insert_range(pt_set, set_begin(pt_setex), set_begin(pt_setex));
            _print_set_user(pt_set);
            set_insert_range(pt_set, set_begin(pt_setex),
                iterator_advance(set_begin(pt_setex), 3));
            _print_set_user(pt_set);
            set_insert_range(pt_set, iterator_advance(set_begin(pt_setex), 5),
                iterator_advance(set_begin(pt_setex), 7));
            _print_set_user(pt_set);
            set_insert_range(pt_set, iterator_advance(set_begin(pt_setex), 8),
                set_end(pt_setex));
            _print_set_user(pt_set);
            set_insert_range(pt_set, set_end(pt_setex), set_end(pt_setex));
            _print_set_user(pt_set);
            set_clear(pt_set);
            set_insert_range(pt_set, set_begin(pt_setex), set_end(pt_setex));
            _print_set_user(pt_set);
            set_destroy(pt_set);
            set_destroy(pt_setex);
        }
        /*set_erase             */
        {
            set_t* pt_set = create_set(setsample_t);
            setsample_t t_ss;
            if(pt_set == NULL)
            {
                return;
            }
            set_init(pt_set);
            printf("erase: %d\n", set_erase(pt_set, &t_ss));
            t_ss._n_first = 100;
            t_ss._n_second = 200;
            t_ss._n_third = 300;
            set_insert(pt_set, &t_ss);
            t_ss._n_first = 49;
            t_ss._n_second = 209;
            t_ss._n_third = 45;
            set_insert(pt_set, &t_ss);
            t_ss._n_first = 100;
            t_ss._n_second = 4;
            t_ss._n_third = -45;
            set_insert(pt_set, &t_ss);
            t_ss._n_first = 35;
            t_ss._n_second = 33;
            t_ss._n_third = 21;
            set_insert(pt_set, &t_ss);
            t_ss._n_first = 20;
            t_ss._n_second = -3;
            t_ss._n_third = 2;
            set_insert(pt_set, &t_ss);
            t_ss._n_first = 23;
            t_ss._n_second = 33;
            t_ss._n_third = 23;
            set_insert(pt_set, &t_ss);
            t_ss._n_first = -4;
            t_ss._n_second = -4;
            t_ss._n_third = -4;
            set_insert(pt_set, &t_ss);
            t_ss._n_first = 2;
            t_ss._n_second = 43;
            t_ss._n_third = 3;
            set_insert(pt_set, &t_ss);
            t_ss._n_first = 3;
            t_ss._n_second = 43;
            t_ss._n_third = 3;
            set_insert(pt_set, &t_ss);
            t_ss._n_first = 4;
            t_ss._n_second = 4;
            t_ss._n_third = 4;
            set_insert(pt_set, &t_ss);
            _print_set_user(pt_set);
            t_ss._n_first = 123;
            t_ss._n_second = 456;
            t_ss._n_third = 789;
            printf("erase: %d\n", set_erase(pt_set, &t_ss));
            _print_set_user(pt_set);
            t_ss._n_first = 2;
            t_ss._n_second = 43;
            t_ss._n_third = 3;
            printf("erase: %d\n", set_erase(pt_set, &t_ss));
            _print_set_user(pt_set);
            set_destroy(pt_set);
        }
        /*set_erase_pos         */
        {
            set_t* pt_set = create_set(setsample_t);
            setsample_t t_ss;
            if(pt_set == NULL)
            {
                return;
            }
            set_init(pt_set);
            t_ss._n_first = 100;
            t_ss._n_second = 200;
            t_ss._n_third = 300;
            set_insert(pt_set, &t_ss);
            t_ss._n_first = 49;
            t_ss._n_second = 209;
            t_ss._n_third = 45;
            set_insert(pt_set, &t_ss);
            t_ss._n_first = 100;
            t_ss._n_second = 4;
            t_ss._n_third = -45;
            set_insert(pt_set, &t_ss);
            t_ss._n_first = 35;
            t_ss._n_second = 33;
            t_ss._n_third = 21;
            set_insert(pt_set, &t_ss);
            t_ss._n_first = 20;
            t_ss._n_second = -3;
            t_ss._n_third = 2;
            set_insert(pt_set, &t_ss);
            t_ss._n_first = 23;
            t_ss._n_second = 33;
            t_ss._n_third = 23;
            set_insert(pt_set, &t_ss);
            t_ss._n_first = -4;
            t_ss._n_second = -4;
            t_ss._n_third = -4;
            set_insert(pt_set, &t_ss);
            t_ss._n_first = 2;
            t_ss._n_second = 43;
            t_ss._n_third = 3;
            set_insert(pt_set, &t_ss);
            t_ss._n_first = 3;
            t_ss._n_second = 43;
            t_ss._n_third = 3;
            set_insert(pt_set, &t_ss);
            t_ss._n_first = 4;
            t_ss._n_second = 4;
            t_ss._n_third = 4;
            set_insert(pt_set, &t_ss);
            _print_set_user(pt_set);
            set_erase_pos(pt_set, set_begin(pt_set));
            _print_set_user(pt_set);
            set_erase_pos(pt_set, iterator_prev(set_end(pt_set)));
            _print_set_user(pt_set);
            set_erase_pos(pt_set, iterator_advance(set_begin(pt_set), 3));
            _print_set_user(pt_set);
            set_destroy(pt_set);
        }
        /*set_erase_range       */
        {
            set_t* pt_set = create_set(setsample_t);
            setsample_t t_ss;
            if(pt_set == NULL)
            {
                return;
            }
            set_init(pt_set);
            set_erase_range(pt_set, set_begin(pt_set), set_end(pt_set));
            _print_set_user(pt_set);
            t_ss._n_first = 100;
            t_ss._n_second = 200;
            t_ss._n_third = 300;
            set_insert(pt_set, &t_ss);
            t_ss._n_first = 49;
            t_ss._n_second = 209;
            t_ss._n_third = 45;
            set_insert(pt_set, &t_ss);
            t_ss._n_first = 100;
            t_ss._n_second = 4;
            t_ss._n_third = -45;
            set_insert(pt_set, &t_ss);
            t_ss._n_first = 35;
            t_ss._n_second = 33;
            t_ss._n_third = 21;
            set_insert(pt_set, &t_ss);
            t_ss._n_first = 20;
            t_ss._n_second = -3;
            t_ss._n_third = 2;
            set_insert(pt_set, &t_ss);
            t_ss._n_first = 23;
            t_ss._n_second = 33;
            t_ss._n_third = 23;
            set_insert(pt_set, &t_ss);
            t_ss._n_first = -4;
            t_ss._n_second = -4;
            t_ss._n_third = -4;
            set_insert(pt_set, &t_ss);
            t_ss._n_first = 2;
            t_ss._n_second = 43;
            t_ss._n_third = 3;
            set_insert(pt_set, &t_ss);
            t_ss._n_first = 3;
            t_ss._n_second = 43;
            t_ss._n_third = 3;
            set_insert(pt_set, &t_ss);
            t_ss._n_first = 4;
            t_ss._n_second = 4;
            t_ss._n_third = 4;
            set_insert(pt_set, &t_ss);
            _print_set_user(pt_set);
            set_erase_range(pt_set, set_begin(pt_set), set_begin(pt_set));
            _print_set_user(pt_set);
            set_erase_range(pt_set, set_begin(pt_set), iterator_advance(set_begin(pt_set), 3));
            _print_set_user(pt_set);
            set_erase_range(pt_set, iterator_next(set_begin(pt_set)),
                iterator_advance(set_begin(pt_set), 3));
            _print_set_user(pt_set);
            set_erase_range(pt_set, iterator_advance(set_begin(pt_set), 3), set_end(pt_set));
            _print_set_user(pt_set);
            set_erase_range(pt_set, set_end(pt_set), set_end(pt_set));
            _print_set_user(pt_set);
            set_erase_range(pt_set, set_begin(pt_set), set_end(pt_set));
            _print_set_user(pt_set);
            set_destroy(pt_set);
        }
    }
    /* cstl defined type */
    {
        /*create_set            */
        {
            set_t* pt_set = create_set(set_t<int>);
            if(pt_set == NULL)
            {
                return;
            }
            set_init(pt_set);
            _print_set_set(pt_set);
            set_destroy(pt_set);
        }
        /*set_init              */
        /*set_init_ex           */
        {
            set_t* pt_set = create_set(set_t<int>);
            if(pt_set == NULL)
            {
                return;
            }
            set_init_ex(pt_set, fun_great_set);
            _print_set_set(pt_set);
            set_destroy(pt_set);
        }
        /*set_init_copy         */
        {
            set_t* pt_set1 = create_set(set_t<int>);
            set_t* pt_set2 = create_set(set_t<int>);
            set_t* pt_setex = create_set(int);
            if(pt_set1 == NULL || pt_set2 == NULL || pt_setex == NULL)
            {
                return;
            }
            set_init_ex(pt_set2, fun_great_set);
            set_init(pt_setex);
            set_insert(pt_setex, 45);
            set_insert(pt_setex, 2);
            set_insert(pt_setex, 90);
            set_insert(pt_set2, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, 7);
            set_insert(pt_setex, 45);
            set_insert(pt_setex, 90);
            set_insert(pt_setex, 34);
            set_insert(pt_set2, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, 5);
            set_insert(pt_setex, 4);
            set_insert(pt_setex, -8);
            set_insert(pt_set2, pt_setex);
            set_init_copy(pt_set1, pt_set2);
            _print_set_set(pt_set1);
            set_destroy(pt_set1);
            set_destroy(pt_set2);
            set_destroy(pt_setex);
        }
        /*set_init_copy_range   */
        {
            set_t* pt_set1 = create_set(set_t<int>);
            set_t* pt_set2 = create_set(set_t<int>);
            set_t* pt_setex = create_set(int);
            if(pt_set1 == NULL || pt_set2 == NULL || pt_setex == NULL)
            {
                return;
            }
            set_init_ex(pt_set2, fun_great_set);
            set_init(pt_setex);
            set_insert(pt_setex, 45);
            set_insert(pt_setex, 2);
            set_insert(pt_setex, 90);
            set_insert(pt_set2, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, 7);
            set_insert(pt_setex, 45);
            set_insert(pt_setex, 90);
            set_insert(pt_setex, 34);
            set_insert(pt_set2, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, 5);
            set_insert(pt_setex, 4);
            set_insert(pt_setex, -8);
            set_insert(pt_set2, pt_setex);
            set_insert(pt_setex, 3445);
            set_insert(pt_setex, 98);
            set_insert(pt_setex, 900);
            set_insert(pt_setex, 23);
            set_insert(pt_setex, 555);
            set_insert(pt_set2, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, 23);
            set_insert(pt_setex, -4);
            set_insert(pt_setex, -455);
            set_insert(pt_set2, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, 923);
            set_insert(pt_setex, 23);
            set_insert(pt_setex, 4489);
            set_insert(pt_set2, pt_setex);
            _print_set_set(pt_set2);
            set_init_copy_range(pt_set1, set_begin(pt_set2), set_end(pt_set2));
            _print_set_set(pt_set1);
            set_destroy(pt_set1);
            set_destroy(pt_set2);
            set_destroy(pt_setex);
        }
        /*set_init_copy_range_ex*/
        {
            set_t* pt_set1 = create_set(set_t<int>);
            set_t* pt_set2 = create_set(set_t<int>);
            set_t* pt_setex = create_set(int);
            if(pt_set1 == NULL || pt_set2 == NULL || pt_setex == NULL)
            {
                return;
            }
            set_init_ex(pt_set2, fun_great_set);
            set_init(pt_setex);
            set_insert(pt_setex, 45);
            set_insert(pt_setex, 2);
            set_insert(pt_setex, 90);
            set_insert(pt_set2, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, 7);
            set_insert(pt_setex, 45);
            set_insert(pt_setex, 90);
            set_insert(pt_setex, 34);
            set_insert(pt_set2, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, 5);
            set_insert(pt_setex, 4);
            set_insert(pt_setex, -8);
            set_insert(pt_set2, pt_setex);
            set_insert(pt_setex, 3445);
            set_insert(pt_setex, 98);
            set_insert(pt_setex, 900);
            set_insert(pt_setex, 23);
            set_insert(pt_setex, 555);
            set_insert(pt_set2, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, 23);
            set_insert(pt_setex, -4);
            set_insert(pt_setex, -455);
            set_insert(pt_set2, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, 923);
            set_insert(pt_setex, 23);
            set_insert(pt_setex, 4489);
            set_insert(pt_set2, pt_setex);
            _print_set_set(pt_set2);
            set_init_copy_range_ex(pt_set1, set_begin(pt_set2),
                set_end(pt_set2), fun_great_set);
            _print_set_set(pt_set1);
            set_destroy(pt_set1);
            set_destroy(pt_set2);
            set_destroy(pt_setex);
        }
        /*set_destroy           */
        /*set_assign            */
        {
            set_t* pt_set1 = create_set(set_t<int>);
            set_t* pt_set2 = create_set(set_t<int>);
            set_t* pt_setex = create_set(int);
            if(pt_set1 == NULL || pt_set2 == NULL || pt_setex == NULL)
            {
                return;
            }
            set_init_ex(pt_set1, fun_great_set);
            set_init_ex(pt_set2, fun_great_set);
            set_init(pt_setex);
            set_assign(pt_set1, pt_set2);
            _print_set_set(pt_set1);
            set_insert(pt_setex, 6);
            set_insert(pt_setex, 5);
            set_insert(pt_setex, -6);
            set_insert(pt_setex, 4);
            set_insert(pt_set2, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, 5);
            set_insert(pt_setex, 2);
            set_insert(pt_setex, 0);
            set_insert(pt_set2, pt_setex);
            set_assign(pt_set1, pt_set2);
            _print_set_set(pt_set1);
            set_clear(pt_setex);
            set_insert(pt_setex, -87);
            set_insert(pt_setex, 56);
            set_insert(pt_setex, 33);
            set_insert(pt_set2, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, 5);
            set_insert(pt_setex, 4);
            set_insert(pt_set2, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, 23);
            set_insert(pt_setex, 5);
            set_insert(pt_setex, -9);
            set_insert(pt_setex, -5);
            set_insert(pt_set2, pt_setex);
            set_assign(pt_set1, pt_set2);
            _print_set_set(pt_set1);
            set_clear(pt_set2);
            set_assign(pt_set1, pt_set2);
            _print_set_set(pt_set1);
            set_destroy(pt_set1);
            set_destroy(pt_set2);
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
            set_t* pt_set = create_set(set_t<int>);
            if(pt_set == NULL)
            {
                return;
            }
            set_init_ex(pt_set, fun_great_set);
            printf("%d, %d\n", set_key_less(pt_set) == fun_great_set,
                   set_value_less(pt_set) == fun_great_set);
            set_destroy(pt_set);
        }
        /*set_clear             */
        {
            set_t* pt_set = create_set(set_t<int>);
            set_t* pt_setex = create_set(int);
            if(pt_set == NULL || pt_setex == NULL)
            {
                return;
            }
            set_init(pt_set);
            set_init(pt_setex);
            set_clear(pt_set);
            set_insert(pt_setex, 4);
            set_insert(pt_setex, 67);
            set_insert(pt_setex, -4);
            set_insert(pt_setex, 33);
            set_insert(pt_set, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, 11);
            set_insert(pt_setex, 4);
            set_insert(pt_setex, -9);
            set_insert(pt_set, pt_setex);
            _print_set_set(pt_set);
            set_clear(pt_set);
            _print_set_set(pt_set);
            set_destroy(pt_set);
            set_destroy(pt_setex);
        }
        /*set_equal             */
        /*set_not_equal         */
        /*set_less              */
        /*set_less_equal        */
        /*set_great             */
        /*set_great_equal       */
        {
            set_t* pt_set1 = create_set(set_t<int>);
            set_t* pt_set2 = create_set(set_t<int>);
            set_t* pt_setex = create_set(int);
            if(pt_set1 == NULL || pt_set2 == NULL || pt_setex == NULL)
            {
                return;
            }
            set_init(pt_set1);
            set_init(pt_set2);
            set_init(pt_setex);
            _print_set_set(pt_set1);
            _print_set_set(pt_set2);
            printf("equal: %d, not equal: %d, ",
                set_equal(pt_set1, pt_set2), set_not_equal(pt_set1, pt_set2));
            printf("less: %d, less equal: %d, ",
                set_less(pt_set1, pt_set2), set_less_equal(pt_set1, pt_set2));
            printf("great: %d, great equal: %d\n",
                set_great(pt_set1, pt_set2), set_great_equal(pt_set1, pt_set2));

            set_insert(pt_setex, 45);
            set_insert(pt_setex, 88);
            set_insert(pt_setex, 3);
            set_insert(pt_setex, 73);
            set_insert(pt_set1, pt_setex);
            _print_set_set(pt_set1);
            _print_set_set(pt_set2);
            printf("equal: %d, not equal: %d, ",
                set_equal(pt_set1, pt_set2), set_not_equal(pt_set1, pt_set2));
            printf("less: %d, less equal: %d, ",
                set_less(pt_set1, pt_set2), set_less_equal(pt_set1, pt_set2));
            printf("great: %d, great equal: %d\n",
                set_great(pt_set1, pt_set2), set_great_equal(pt_set1, pt_set2));

            set_insert(pt_set2, pt_setex);
            _print_set_set(pt_set1);
            _print_set_set(pt_set2);
            printf("equal: %d, not equal: %d, ",
                set_equal(pt_set1, pt_set2), set_not_equal(pt_set1, pt_set2));
            printf("less: %d, less equal: %d, ",
                set_less(pt_set1, pt_set2), set_less_equal(pt_set1, pt_set2));
            printf("great: %d, great equal: %d\n",
                set_great(pt_set1, pt_set2), set_great_equal(pt_set1, pt_set2));

            set_clear(pt_setex);
            set_insert(pt_setex, 45);
            set_insert(pt_setex, 30);
            set_insert(pt_setex, -4);
            set_insert(pt_setex, 90);
            set_insert(pt_set1, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, -5);
            set_insert(pt_setex, -30);
            set_insert(pt_setex, -4);
            set_insert(pt_setex, -90);
            set_insert(pt_set1, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, 5);
            set_insert(pt_setex, 30);
            set_insert(pt_setex, 4);
            set_insert(pt_setex, 0);
            set_insert(pt_set2, pt_setex);
            _print_set_set(pt_set1);
            _print_set_set(pt_set2);
            printf("equal: %d, not equal: %d, ",
                set_equal(pt_set1, pt_set2), set_not_equal(pt_set1, pt_set2));
            printf("less: %d, less equal: %d, ",
                set_less(pt_set1, pt_set2), set_less_equal(pt_set1, pt_set2));
            printf("great: %d, great equal: %d\n",
                set_great(pt_set1, pt_set2), set_great_equal(pt_set1, pt_set2));

            set_destroy(pt_set1);
            set_destroy(pt_set2);
            set_destroy(pt_setex);
        }
        /*set_swap              */
        {
            set_t* pt_set1 = create_set(set_t<int>);
            set_t* pt_set2 = create_set(set_t<int>);
            set_t* pt_setex = create_set(int);
            if(pt_set1 == NULL || pt_set2 == NULL || pt_setex == NULL)
            {
                return;
            }
            set_init(pt_set1);
            set_init(pt_set2);
            set_init(pt_setex);
            set_swap(pt_set1, pt_set2);
            _print_set_set(pt_set1);
            _print_set_set(pt_set2);
            set_insert(pt_setex, 59);
            set_insert(pt_setex, 66);
            set_insert(pt_setex, 32);
            set_insert(pt_setex, 9);
            set_insert(pt_setex, 300);
            set_insert(pt_set2, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, 45);
            set_insert(pt_setex, -44);
            set_insert(pt_setex, 4);
            set_insert(pt_set2, pt_setex);
            set_swap(pt_set1, pt_set2);
            _print_set_set(pt_set1);
            _print_set_set(pt_set2);
            set_clear(pt_setex);
            set_insert(pt_setex, 300);
            set_insert(pt_setex, 39);
            set_insert(pt_setex, 45);
            set_insert(pt_setex, 400);
            set_insert(pt_set2, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, 30);
            set_insert(pt_setex, 9);
            set_insert(pt_setex, 4);
            set_insert(pt_setex, 5);
            set_insert(pt_setex, 0);
            set_insert(pt_set2, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, -30);
            set_insert(pt_setex, -9);
            set_insert(pt_setex, 4);
            set_insert(pt_setex, -5);
            set_insert(pt_setex, 0);
            set_insert(pt_set2, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, -3000);
            set_insert(pt_setex, 5000);
            set_insert(pt_set2, pt_setex);
            set_swap(pt_set1, pt_set2);
            _print_set_set(pt_set1);
            _print_set_set(pt_set2);
            set_clear(pt_set2);
            set_swap(pt_set1, pt_set2);
            _print_set_set(pt_set1);
            _print_set_set(pt_set2);
            set_destroy(pt_set1);
            set_destroy(pt_set2);
            set_destroy(pt_setex);
        }
        /*set_find              */
        {
            set_t* pt_set = create_set(set_t<int>);
            set_t* pt_setex = create_set(int);
            iterator_t t_iterex;
            if(pt_set == NULL || pt_setex == NULL)
            {
                return;
            }
            set_init(pt_set);
            set_init(pt_setex);
            t_iterex = set_find(pt_set, pt_setex);
            if(iterator_equal(t_iterex, set_end(pt_set)))
            {
                printf("not found, count: %d\n", set_count(pt_set, pt_setex));
            }
            else
            {
                _print_set_c(iterator_get_pointer(t_iterex), "%d, ", int);
                printf("count: %d\n", set_count(pt_set, pt_setex));
            }

            set_insert(pt_setex, 45);
            set_insert(pt_setex, 40);
            set_insert(pt_setex, 22);
            set_insert(pt_setex, 11);
            set_insert(pt_setex, 6);
            set_insert(pt_set, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, -5);
            set_insert(pt_setex, 240);
            set_insert(pt_setex, 22);
            set_insert(pt_setex, 191);
            set_insert(pt_setex, 60);
            set_insert(pt_set, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, 75);
            set_insert(pt_setex, 91);
            set_insert(pt_setex, 6);
            set_insert(pt_set, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, 95);
            set_insert(pt_setex, 888);
            set_insert(pt_setex, 72);
            set_insert(pt_setex, 333);
            set_insert(pt_setex, 80);
            set_insert(pt_set, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, 35);
            set_insert(pt_setex, 240);
            set_insert(pt_setex, -2);
            set_insert(pt_setex, -91);
            set_insert(pt_setex, 0);
            set_insert(pt_set, pt_setex);
            set_clear(pt_setex);
            t_iterex = set_find(pt_set, pt_setex);
            if(iterator_equal(t_iterex, set_end(pt_set)))
            {
                printf("not found, count: %d\n", set_count(pt_set, pt_setex));
            }
            else
            {
                _print_set_c(iterator_get_pointer(t_iterex), "%d, ", int);
                printf("count: %d\n", set_count(pt_set, pt_setex));
            }
            set_clear(pt_setex);
            set_insert(pt_setex, 75);
            set_insert(pt_setex, 91);
            set_insert(pt_setex, 6);
            t_iterex = set_find(pt_set, pt_setex);
            if(iterator_equal(t_iterex, set_end(pt_set)))
            {
                printf("not found, count: %d\n", set_count(pt_set, pt_setex));
            }
            else
            {
                _print_set_c(iterator_get_pointer(t_iterex), "%d, ", int);
                printf("count: %d\n", set_count(pt_set, pt_setex));
            }
            set_destroy(pt_set);
            set_destroy(pt_setex);
        }
        /*set_count             */
        /*set_lower_bound       */
        /*set_upper_bound       */
        /*set_equal_range       */
        {
            set_t* pt_set = create_set(set_t<int>);
            set_t* pt_setex = create_set(int);
            iterator_t t_begin;
            iterator_t t_end;
            range_t t_range;
            iterator_t t_iterex;
            if(pt_set == NULL || pt_setex == NULL)
            {
                return;
            }
            set_init(pt_set);
            set_init(pt_setex);
            t_begin = set_lower_bound(pt_set, pt_setex);
            t_end = set_upper_bound(pt_set, pt_setex);
            t_range = set_equal_range(pt_set, pt_setex);
            assert(iterator_equal(t_begin, set_end(pt_set)) &&
                   iterator_equal(t_end, set_end(pt_set)) &&
                   iterator_equal(t_range.t_begin, set_end(pt_set)) &&
                   iterator_equal(t_range.t_end, set_end(pt_set)));
            set_insert(pt_setex, 35);
            set_insert(pt_setex, 20);
            set_insert(pt_setex, 233);
            set_insert(pt_setex, -4);
            set_insert(pt_setex, 3);
            set_insert(pt_set, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, -5);
            set_insert(pt_setex, 15);
            set_insert(pt_setex, 54);
            set_insert(pt_setex, -45);
            set_insert(pt_setex, 2);
            set_insert(pt_setex, 23);
            set_insert(pt_set, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, 5);
            set_insert(pt_setex, 2);
            set_insert(pt_setex, 23);
            set_insert(pt_set, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, 5);
            set_insert(pt_setex, 8);
            set_insert(pt_setex, 9);
            set_insert(pt_setex, -5);
            set_insert(pt_setex, 4);
            set_insert(pt_setex, 23);
            set_insert(pt_set, pt_setex);
            _print_set_set(pt_set);
            set_clear(pt_setex);
            set_insert(pt_setex, -5);
            set_insert(pt_setex, 15);
            set_insert(pt_setex, 54);
            set_insert(pt_setex, -45);
            set_insert(pt_setex, 2);
            set_insert(pt_setex, 23);
            t_begin = set_lower_bound(pt_set, pt_setex);
            t_end = set_upper_bound(pt_set, pt_setex);
            t_range = set_equal_range(pt_set, pt_setex);
            assert(iterator_equal(t_begin, set_begin(pt_set)) &&
                   iterator_equal(t_end, iterator_next(set_begin(pt_set))) &&
                   iterator_equal(t_range.t_begin, set_begin(pt_set)) &&
                   iterator_equal(t_range.t_end, iterator_next(set_begin(pt_set))));
            set_clear(pt_setex);
            set_insert(pt_setex, -5);
            set_insert(pt_setex, 8);
            set_insert(pt_setex, 3);
            t_begin = set_lower_bound(pt_set, pt_setex);
            t_end = set_upper_bound(pt_set, pt_setex);
            t_range = set_equal_range(pt_set, pt_setex);
            t_iterex = set_lower_bound(pt_set, pt_setex);
            _print_set_c(iterator_get_pointer(t_iterex), "%d, ", int);
            assert(iterator_equal(t_begin, t_iterex) &&
                   iterator_equal(t_end, t_iterex) &&
                   iterator_equal(t_range.t_begin, t_iterex) &&
                   iterator_equal(t_range.t_end, t_iterex));

            set_destroy(pt_set);
            set_destroy(pt_setex);
        }
        /*set_insert            */
        {
            set_t* pt_set = create_set(set_t<int>);
            set_t* pt_setex = create_set(int);
            if(pt_set == NULL || pt_setex == NULL)
            {
                return;
            }
            /*
             * type is not matching. pt_set is set_t<int> and pt_setex is 
             * set_t<int, fun_great_int>.
             */
            set_init(pt_set);
            set_init(pt_setex);
            set_insert(pt_setex, 3445);
            set_insert(pt_setex, 98);
            set_insert(pt_setex, 900);
            set_insert(pt_setex, 23);
            set_insert(pt_setex, 555);
            set_insert(pt_set, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, 23);
            set_insert(pt_setex, -4);
            set_insert(pt_setex, -455);
            set_insert(pt_set, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, 923);
            set_insert(pt_setex, 23);
            set_insert(pt_setex, 4489);
            set_insert(pt_set, pt_setex);
            _print_set_set(pt_set);
            set_destroy(pt_set);
            set_destroy(pt_setex);
        }
        /*set_insert_hint       */
        {
            set_t* pt_set = create_set(set_t<int>);
            set_t* pt_setex = create_set(int);
            set_iterator_t t_iter;
            if(pt_set == NULL || pt_setex == NULL)
            {
                return;
            }
            set_init(pt_set);
            set_init(pt_setex);
            t_iter = set_begin(pt_set);
            set_insert(pt_setex, 3445);
            set_insert(pt_setex, 98);
            set_insert(pt_setex, 900);
            set_insert(pt_setex, 23);
            set_insert(pt_setex, 555);
            set_insert_hint(pt_set, t_iter, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, 23);
            set_insert(pt_setex, -4);
            set_insert(pt_setex, -455);
            set_insert_hint(pt_set, t_iter, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, 923);
            set_insert(pt_setex, 23);
            set_insert(pt_setex, 4489);
            set_insert_hint(pt_set, t_iter, pt_setex);
            _print_set_set(pt_set);
            set_destroy(pt_set);
            set_destroy(pt_setex);
        }
        /*set_insert_range      */
        {
            set_t* pt_set1 = create_set(set_t<int>);
            set_t* pt_set2 = create_set(set_t<int>);
            set_t* pt_setex = create_set(int);
            if(pt_set1 == NULL || pt_set2 == NULL || pt_setex == NULL)
            {
                return;
            }
            set_init(pt_set1);
            set_init_ex(pt_set2, fun_great_set);
            set_init(pt_setex);
            set_insert_range(pt_set1, set_begin(pt_set2), set_end(pt_set2));
            _print_set_set(pt_set1);
            set_insert(pt_setex, 3445);
            set_insert(pt_setex, 98);
            set_insert(pt_setex, 900);
            set_insert(pt_setex, 23);
            set_insert(pt_setex, 555);
            set_insert(pt_set2, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, 23);
            set_insert(pt_setex, -4);
            set_insert(pt_setex, -455);
            set_insert(pt_set2, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, 923);
            set_insert(pt_setex, 23);
            set_insert(pt_setex, 4489);
            set_insert(pt_set2, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, 35);
            set_insert(pt_setex, 20);
            set_insert(pt_setex, 233);
            set_insert(pt_setex, -4);
            set_insert(pt_setex, 3);
            set_insert(pt_set2, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, -5);
            set_insert(pt_setex, 15);
            set_insert(pt_setex, 54);
            set_insert(pt_setex, -45);
            set_insert(pt_setex, 2);
            set_insert(pt_setex, 23);
            set_insert(pt_set2, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, 5);
            set_insert(pt_setex, 2);
            set_insert(pt_setex, 23);
            set_insert(pt_set2, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, 5);
            set_insert(pt_setex, 8);
            set_insert(pt_setex, 9);
            set_insert(pt_setex, -5);
            set_insert(pt_setex, 4);
            set_insert(pt_setex, 23);
            set_insert(pt_set2, pt_setex);
            _print_set_set(pt_set2);
            set_insert_range(pt_set1, set_begin(pt_set2), set_begin(pt_set2));
            _print_set_set(pt_set1);
            set_insert_range(pt_set1, set_begin(pt_set2),
                iterator_advance(set_begin(pt_set2), 2));
            _print_set_set(pt_set1);
            set_insert_range(pt_set1, iterator_advance(set_begin(pt_set2), 3),
                iterator_advance(set_begin(pt_set2), 5));
            _print_set_set(pt_set1);
            set_insert_range(pt_set1, iterator_advance(set_begin(pt_set2), 5),
                set_end(pt_set2));
            _print_set_set(pt_set1);
            set_insert_range(pt_set1, set_end(pt_set2), set_end(pt_set2));
            _print_set_set(pt_set1);
            set_clear(pt_set1);
            set_insert_range(pt_set1, set_begin(pt_set2), set_end(pt_set2));
            _print_set_set(pt_set1);

            set_destroy(pt_set1);
            set_destroy(pt_set2);
            set_destroy(pt_setex);
        }
        /*set_erase             */
        {
            set_t* pt_set = create_set(set_t<int>);
            set_t* pt_setex = create_set(int);
            if(pt_set == NULL || pt_setex == NULL)
            {
                return;
            }
            set_init(pt_set);
            set_init(pt_setex);
            set_erase(pt_set, pt_setex);
            _print_set_set(pt_set);
            set_insert(pt_setex, 3445);
            set_insert(pt_setex, 98);
            set_insert(pt_setex, 900);
            set_insert(pt_setex, 23);
            set_insert(pt_setex, 555);
            set_insert(pt_set, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, 23);
            set_insert(pt_setex, -4);
            set_insert(pt_setex, -455);
            set_insert(pt_set, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, 923);
            set_insert(pt_setex, 23);
            set_insert(pt_setex, 4489);
            set_insert(pt_set, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, 35);
            set_insert(pt_setex, 20);
            set_insert(pt_setex, 233);
            set_insert(pt_setex, -4);
            set_insert(pt_setex, 3);
            set_insert(pt_set, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, -5);
            set_insert(pt_setex, 15);
            set_insert(pt_setex, 54);
            set_insert(pt_setex, -45);
            set_insert(pt_setex, 2);
            set_insert(pt_setex, 23);
            set_insert(pt_set, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, 5);
            set_insert(pt_setex, 2);
            set_insert(pt_setex, 23);
            set_insert(pt_set, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, 5);
            set_insert(pt_setex, 8);
            set_insert(pt_setex, 9);
            set_insert(pt_setex, -5);
            set_insert(pt_setex, 4);
            set_insert(pt_setex, 23);
            set_insert(pt_set, pt_setex);
            _print_set_set(pt_set);
            set_clear(pt_setex);
            set_erase(pt_set, pt_setex);
            _print_set_set(pt_set);
            set_clear(pt_setex);
            set_insert(pt_setex, 35);
            set_insert(pt_setex, 20);
            set_insert(pt_setex, 233);
            set_insert(pt_setex, -4);
            set_insert(pt_setex, 3);
            set_insert(pt_set, pt_setex);
            set_erase(pt_set, pt_setex);
            _print_set_set(pt_set);
            set_destroy(pt_set);
            set_destroy(pt_setex);
        }
        /*set_erase_pos         */
        {
            set_t* pt_set = create_set(set_t<int>);
            set_t* pt_setex = create_set(int);
            if(pt_set == NULL || pt_setex == NULL)
            {
                return;
            }
            set_init(pt_set);
            set_init(pt_setex);
            set_insert(pt_setex, 3445);
            set_insert(pt_setex, 98);
            set_insert(pt_setex, 900);
            set_insert(pt_setex, 23);
            set_insert(pt_setex, 555);
            set_insert(pt_set, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, 23);
            set_insert(pt_setex, -4);
            set_insert(pt_setex, -455);
            set_insert(pt_set, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, 923);
            set_insert(pt_setex, 23);
            set_insert(pt_setex, 4489);
            set_insert(pt_set, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, 35);
            set_insert(pt_setex, 20);
            set_insert(pt_setex, 233);
            set_insert(pt_setex, -4);
            set_insert(pt_setex, 3);
            set_insert(pt_set, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, -5);
            set_insert(pt_setex, 15);
            set_insert(pt_setex, 54);
            set_insert(pt_setex, -45);
            set_insert(pt_setex, 2);
            set_insert(pt_setex, 23);
            set_insert(pt_set, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, 5);
            set_insert(pt_setex, 2);
            set_insert(pt_setex, 23);
            set_insert(pt_set, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, 5);
            set_insert(pt_setex, 8);
            set_insert(pt_setex, 9);
            set_insert(pt_setex, -5);
            set_insert(pt_setex, 4);
            set_insert(pt_setex, 23);
            set_insert(pt_set, pt_setex);
            _print_set_set(pt_set);
            set_erase_pos(pt_set, set_begin(pt_set));
            _print_set_set(pt_set);
            set_erase_pos(pt_set, iterator_prev(set_end(pt_set)));
            _print_set_set(pt_set);
            set_erase_pos(pt_set, iterator_advance(set_begin(pt_set), 2));
            _print_set_set(pt_set);
            while(!set_empty(pt_set))
            {
                set_erase_pos(pt_set, set_begin(pt_set));
            }
            _print_set_set(pt_set);
            set_destroy(pt_set);
            set_destroy(pt_setex);
        }
        /*set_erase_range       */
        {
            set_t* pt_set = create_set(set_t<int>);
            set_t* pt_setex = create_set(int);
            if(pt_set == NULL || pt_setex == NULL)
            {
                return;
            }
            set_init(pt_set);
            set_init(pt_setex);
            set_erase_range(pt_set, set_begin(pt_set), set_end(pt_set));
            _print_set_set(pt_set);
            set_insert(pt_setex, 3445);
            set_insert(pt_setex, 98);
            set_insert(pt_setex, 900);
            set_insert(pt_setex, 23);
            set_insert(pt_setex, 555);
            set_insert(pt_set, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, 23);
            set_insert(pt_setex, -4);
            set_insert(pt_setex, -455);
            set_insert(pt_set, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, 923);
            set_insert(pt_setex, 23);
            set_insert(pt_setex, 4489);
            set_insert(pt_set, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, 35);
            set_insert(pt_setex, 20);
            set_insert(pt_setex, 233);
            set_insert(pt_setex, -4);
            set_insert(pt_setex, 3);
            set_insert(pt_set, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, -5);
            set_insert(pt_setex, 15);
            set_insert(pt_setex, 54);
            set_insert(pt_setex, -45);
            set_insert(pt_setex, 2);
            set_insert(pt_setex, 23);
            set_insert(pt_set, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, 5);
            set_insert(pt_setex, 2);
            set_insert(pt_setex, 23);
            set_insert(pt_set, pt_setex);
            set_clear(pt_setex);
            set_insert(pt_setex, 5);
            set_insert(pt_setex, 8);
            set_insert(pt_setex, 9);
            set_insert(pt_setex, -5);
            set_insert(pt_setex, 4);
            set_insert(pt_setex, 23);
            set_insert(pt_set, pt_setex);
            _print_set_set(pt_set);
            set_erase_range(pt_set, set_begin(pt_set), set_begin(pt_set));
            _print_set_set(pt_set);
            set_erase_range(pt_set, set_begin(pt_set),
                iterator_advance(set_begin(pt_set), 2));
            _print_set_set(pt_set);
            set_erase_range(pt_set, iterator_next(set_begin(pt_set)),
                iterator_advance(set_begin(pt_set), 3));
            _print_set_set(pt_set);
            set_erase_range(pt_set, iterator_advance(set_begin(pt_set), 2), set_end(pt_set));
            _print_set_set(pt_set);
            set_erase_range(pt_set, set_end(pt_set), set_end(pt_set));
            _print_set_set(pt_set);
            set_erase_range(pt_set, set_begin(pt_set), set_end(pt_set));
            _print_set_set(pt_set);
            set_destroy(pt_set);
            set_destroy(pt_setex);
        }
    }
    /* c-str type */
    {
        /*create_set            */
        {
            set_t* pt_set = create_set(char*);
            if(pt_set == NULL)
            {
                return;
            }
            set_init(pt_set);
            _print_set_cstr(pt_set);
            set_insert(pt_set, "abcdefg");
            set_insert(pt_set, "opqrst");
            set_insert(pt_set, "opqrst");
            _print_set_cstr(pt_set);
            set_destroy(pt_set);
        }
        /*set_init              */
        /*set_init_ex           */
        {
            set_t* pt_set = create_set(char*);
            if(pt_set == NULL)
            {
                return;
            }
            /*
             * bugs in get type with c-string.
             */
            set_init_ex(pt_set, _set_cstr_pre);
            _print_set_cstr(pt_set);
            set_insert(pt_set, "abcdefghij");
            set_insert(pt_set, "abcd");
            set_insert(pt_set, "fghijkl");
            _print_set_cstr(pt_set);
            set_destroy(pt_set);
        }
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

    /*
    set_t* pt_set = create_set(int);
    set_t* pt_setex = create_set(int);
    set_t* pt_setex2 = create_set(int);
    set_t* pt_setex3 = create_set(int);

    set_t* pt_set1 = create_set(int);
    set_t* pt_set2 = create_set(int);
    set_t* pt_set3 = create_set(int);
    set_t* pt_set4 = create_set(int);
    if(pt_set == NULL || pt_setex == NULL || pt_setex2 == NULL || pt_setex3 == NULL ||
       pt_set1 == NULL || pt_set2 == NULL || pt_set3 == NULL || pt_set4 == NULL)
    {
        return;
    }
    set_init(pt_set);
    set_insert(pt_set, 34);
    set_insert(pt_set, 90);
    set_insert(pt_set, 3);
    set_insert(pt_set, 67);
    set_insert(pt_set, -9);
    set_insert(pt_set, -6);
    set_insert(pt_set, 9);
    _print_set_c(pt_set, "%d, ", int);
    set_init_copy(pt_setex, pt_set);
    _print_set_c(pt_setex, "%d, ", int);
    set_init_copy_range(pt_setex2, set_begin(pt_set), set_end(pt_set));
    _print_set_c(pt_setex2, "%d, ", int);
    set_init_copy_range_ex(pt_setex3, set_begin(pt_set), set_end(pt_set), fun_great_int);
    _print_set_c(pt_setex3, "%d, ", int);

    printf("===================================\n");
    set_init_ex(pt_set1, fun_great_int);
    set_insert(pt_set1, 34);
    set_insert(pt_set1, 90);
    set_insert(pt_set1, 3);
    set_insert(pt_set1, 67);
    set_insert(pt_set1, -9);
    set_insert(pt_set1, -6);
    set_insert(pt_set1, 9);
    _print_set_c(pt_set1, "%d, ", int);
    set_init_copy(pt_set2, pt_set1);
    _print_set_c(pt_set2, "%d, ", int);
    set_init_copy_range(pt_set3, set_begin(pt_set1), set_end(pt_set1));
    _print_set_c(pt_set3, "%d, ", int);
    set_init_copy_range_ex(pt_set4, set_begin(pt_set1), set_end(pt_set1), fun_great_int);
    _print_set_c(pt_set4, "%d, ", int);

    set_destroy(pt_set);
    set_destroy(pt_setex);
    set_destroy(pt_setex2);
    set_destroy(pt_setex3);
    set_destroy(pt_set1);
    set_destroy(pt_set2);
    set_destroy(pt_set3);
    set_destroy(pt_set4);
    */
}

/** local function implementation section **/
static void _set_cstr_pre(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    if(strlen((char*)cpv_first) < strlen((char*)cpv_second))
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}

static void _print_set_cstr(const set_t* cpt_set)
{
    iterator_t t_iter;
    assert(cpt_set != NULL);
    printf("=======================================\n");
    printf("empty: %u, size: %u, max_size: %u\n",
        set_empty(cpt_set), set_size(cpt_set), set_max_size(cpt_set));
    for(t_iter = set_begin(cpt_set);
        !iterator_equal(t_iter, set_end(cpt_set));
        t_iter = iterator_next(t_iter))
    {
        puts(iterator_get_pointer(t_iter));
    }
}

static void _print_set_set(const set_t* cpt_set)
{
    iterator_t t_iter;
    iterator_t t_iterex;
    assert(cpt_set != NULL);
    printf("=======================================\n");
    printf("empty: %u, size: %u, max_size: %u\n",
        set_empty(cpt_set), set_size(cpt_set), set_max_size(cpt_set));
    for(t_iter = set_begin(cpt_set);
        !iterator_equal(t_iter, set_end(cpt_set));
        t_iter = iterator_next(t_iter))
    {
        for(t_iterex = set_begin(iterator_get_pointer(t_iter));
            !iterator_equal(t_iterex, set_end(iterator_get_pointer(t_iter)));
            t_iterex = iterator_next(t_iterex))
        {
            printf("%d, ", *(int*)iterator_get_pointer(t_iterex));
        }
        printf("\n");
    }
}

static void _print_set_user(const set_t* cpt_set)
{
    iterator_t t_iter;
    assert(cpt_set != NULL);

    printf("=======================================\n");
    printf("empty: %u, size: %u, max_size: %u\n",
        set_empty(cpt_set), set_size(cpt_set), set_max_size(cpt_set));
    for(t_iter = set_begin(cpt_set);
        !iterator_equal(t_iter, set_end(cpt_set));
        t_iter = iterator_next(t_iter))
    {
        printf("<%d, %d, %d>, ",
            ((setsample_t*)iterator_get_pointer(t_iter))->_n_first,
            ((setsample_t*)iterator_get_pointer(t_iter))->_n_second,
            ((setsample_t*)iterator_get_pointer(t_iter))->_n_third);
    }
    printf("\n");
}

static void _setsample_init(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    ((setsample_t*)cpv_input)->_n_first = 0;
    ((setsample_t*)cpv_input)->_n_second = 0;
    ((setsample_t*)cpv_input)->_n_third = 0;
    *(bool_t*)pv_output = true;
}

static void _setsample_destroy(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    ((setsample_t*)cpv_input)->_n_first = 0;
    ((setsample_t*)cpv_input)->_n_second = 0;
    ((setsample_t*)cpv_input)->_n_third = 0;
    *(bool_t*)pv_output = true;
}

static void _setsample_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    if(((setsample_t*)cpv_first)->_n_first < ((setsample_t*)cpv_second)->_n_first)
    {
        *(bool_t*)pv_output = true;
    }
    else if(((setsample_t*)cpv_first)->_n_first == ((setsample_t*)cpv_second)->_n_first &&
            ((setsample_t*)cpv_first)->_n_second < ((setsample_t*)cpv_second)->_n_second)
    {
        *(bool_t*)pv_output = true;
    }
    else if(((setsample_t*)cpv_first)->_n_first == ((setsample_t*)cpv_second)->_n_first &&
            ((setsample_t*)cpv_first)->_n_second == ((setsample_t*)cpv_second)->_n_second &&
            ((setsample_t*)cpv_first)->_n_third < ((setsample_t*)cpv_second)->_n_third)
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}

static void _setsample_great(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    if(((setsample_t*)cpv_first)->_n_first > ((setsample_t*)cpv_second)->_n_first)
    {
        *(bool_t*)pv_output = true;
    }
    else if(((setsample_t*)cpv_first)->_n_first == ((setsample_t*)cpv_second)->_n_first &&
            ((setsample_t*)cpv_first)->_n_second > ((setsample_t*)cpv_second)->_n_second)
    {
        *(bool_t*)pv_output = true;
    }
    else if(((setsample_t*)cpv_first)->_n_first == ((setsample_t*)cpv_second)->_n_first &&
            ((setsample_t*)cpv_first)->_n_second == ((setsample_t*)cpv_second)->_n_second &&
            ((setsample_t*)cpv_first)->_n_third > ((setsample_t*)cpv_second)->_n_third)
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}

static void _setsample_copy(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    ((setsample_t*)cpv_first)->_n_first = ((setsample_t*)cpv_second)->_n_first;
    ((setsample_t*)cpv_first)->_n_second = ((setsample_t*)cpv_second)->_n_second;
    ((setsample_t*)cpv_first)->_n_third = ((setsample_t*)cpv_second)->_n_third;
    *(bool_t*)pv_output = true;
}

/** eof **/

