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
/*#include "tree_traverse.h"*/

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

#define _print_multiset_c(pt_mset, fmt, type)\
    do{\
        iterator_t t_iter;\
        printf("=======================================\n");\
        printf("empty: %u, size: %u, max_size: %u\n",\
            multiset_empty(pt_mset), multiset_size(pt_mset), multiset_max_size(pt_mset));\
        for(t_iter = multiset_begin(pt_mset);\
            !iterator_equal(t_iter, multiset_end(pt_mset));\
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
typedef setsample_t multisetsample_t;

/** local function prototype section **/
static void _print_multiset_multiset(const multiset_t* cpt_mset);
static void _print_multiset_user(const multiset_t* cpt_mset);

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
        {
            set_t* pt_set = create_set(char*);
            set_t* pt_setex = create_set(char*);
            if(pt_set == NULL || pt_setex == NULL)
            {
                return;
            }
            set_init_ex(pt_setex, _set_cstr_pre);
            set_insert(pt_setex, "achieving the goals of the Internet standards process");
            set_insert(pt_setex, "needed, and the wishes of the WG should");
            set_insert(pt_setex, "There shall be an extended Last Call for public review.");
            set_init_copy(pt_set, pt_setex);
            _print_set_cstr(pt_set);
            set_destroy(pt_set);
            set_destroy(pt_setex);
        }
        /*set_init_copy_range   */
        {
            set_t* pt_set = create_set(char* );
            set_t* pt_setex = create_set(   char   *   );
            if(pt_set == NULL || pt_setex == NULL)
            {
                return;
            }
            set_init_ex(pt_setex, _set_cstr_pre);
            set_insert(pt_setex, "When the IESG (on reviewing a recommendation a variance)");
            set_insert(pt_setex, "do not apply or lead to a deadlock");
            set_insert(pt_setex, "Depending on the results of the Last Call");
            set_insert(pt_setex, "accept the solution; or revise the proposal");
            set_insert(pt_setex, "Draft, and initiate another extended Last Call");
            set_insert(pt_setex, "In any case");
            set_insert(pt_setex, "When the IESG accepts a solution");
            set_insert(pt_setex, "IESG -- and Brian Carpenter");
            _print_set_cstr(pt_setex);
            set_init_copy_range(pt_set, set_begin(pt_setex), set_end(pt_setex));
            _print_set_cstr(pt_set);
            set_destroy(pt_set);
            set_destroy(pt_setex);
        }
        /*set_init_copy_range_ex*/
        {
            set_t* pt_set = create_set(char* );
            set_t* pt_setex = create_set(   char   *   );
            if(pt_set == NULL || pt_setex == NULL)
            {
                return;
            }
            set_init_ex(pt_setex, _set_cstr_pre);
            set_insert(pt_setex, "When the IESG (on reviewing a recommendation a variance)");
            set_insert(pt_setex, "do not apply or lead to a deadlock");
            set_insert(pt_setex, "Depending on the results of the Last Call");
            set_insert(pt_setex, "accept the solution; or revise the proposal");
            set_insert(pt_setex, "Draft, and initiate another extended Last Call");
            set_insert(pt_setex, "In any case");
            set_insert(pt_setex, "When the IESG accepts a solution");
            set_insert(pt_setex, "IESG -- and Brian Carpenter");
            _print_set_cstr(pt_setex);
            set_init_copy_range_ex(pt_set, set_begin(pt_setex),
                set_end(pt_setex), _set_cstr_pre);
            _print_set_cstr(pt_set);
            set_destroy(pt_set);
            set_destroy(pt_setex);
        }
        /*set_destroy           */
        /*set_assign            */
        {
            set_t* pt_set = create_set(char*);
            set_t* pt_setex = create_set(char *);
            if(pt_set == NULL || pt_setex == NULL)
            {
                return;
            }
            set_init_ex(pt_set, _set_cstr_pre);
            set_init_ex(pt_setex, _set_cstr_pre);
            set_assign(pt_set, pt_setex);
            _print_set_cstr(pt_set);
            set_insert(pt_setex, "Jon Postel");
            set_insert(pt_setex, "USC - ISI, Suite 1001");
            set_insert(pt_setex, "4676 Admiralty Way");
            set_insert(pt_setex, "Marina del Rey, CA  90292-6695");
            set_insert(pt_setex, "Phone: 310-822-1511");
            set_insert(pt_setex, "EMail: postel@isi.edu");
            set_assign(pt_set, pt_setex);
            _print_set_cstr(pt_set);
            set_clear(pt_setex);
            set_assign(pt_set, pt_setex);
            _print_set_cstr(pt_set);
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
            set_t* pt_set = create_set(char*);
            set_t* pt_setex = create_set(char*);
            if(pt_set == NULL || pt_setex == NULL)
            {
                return;
            }
            set_init(pt_set);
            set_init_ex(pt_setex, _set_cstr_pre);
            assert(set_key_less(pt_set) != _set_cstr_pre &&
                   set_value_less(pt_set) != _set_cstr_pre &&
                   set_key_less(pt_setex) == _set_cstr_pre &&
                   set_value_less(pt_setex) == _set_cstr_pre);
            set_destroy(pt_set);
            set_destroy(pt_setex);
        }
        /*set_clear             */
        {
            set_t* pt_set = create_set(char*);
            if(pt_set == NULL)
            {
                return;
            }
            set_init(pt_set);
            set_clear(pt_set);
            _print_set_cstr(pt_set);
            set_insert(pt_set, "no Working Group is constituted");
            set_insert(pt_set, "community from entering or advancing the specification the");
            set_insert(pt_set, "community that result from noncompliance with section 5");
            set_insert(pt_set, "(c) alternatives to the granting of a variance");
            set_insert(pt_set, "community.");
            _print_set_cstr(pt_set);
            set_clear(pt_set);
            _print_set_cstr(pt_set);
            set_destroy(pt_set);
        }
        /*set_equal             */
        /*set_not_equal         */
        /*set_less              */
        /*set_less_equal        */
        /*set_great             */
        /*set_great_equal       */
        {
            set_t* pt_set = create_set(char*);
            set_t* pt_setex = create_set(char*);
            if(pt_set == NULL || pt_setex == NULL)
            {
                return;
            }
            set_init(pt_set);
            set_init(pt_setex);
            _print_set_cstr(pt_set);
            _print_set_cstr(pt_setex);
            printf("equal: %d, not equal: %d, ",
                set_equal(pt_set, pt_setex), set_not_equal(pt_set, pt_setex));
            printf("less: %d, less equal: %d, ",
                set_less(pt_set, pt_setex), set_less_equal(pt_set, pt_setex));
            printf("great: %d, great equal: %d\n",
                set_great(pt_set, pt_setex), set_great_equal(pt_set, pt_setex));

            set_insert(pt_set, "Eric Brunsen");
            _print_set_cstr(pt_set);
            _print_set_cstr(pt_setex);
            printf("equal: %d, not equal: %d, ",
                set_equal(pt_set, pt_setex), set_not_equal(pt_set, pt_setex));
            printf("less: %d, less equal: %d, ",
                set_less(pt_set, pt_setex), set_less_equal(pt_set, pt_setex));
            printf("great: %d, great equal: %d\n",
                set_great(pt_set, pt_setex), set_great_equal(pt_set, pt_setex));

            set_insert(pt_setex, "Eric Brunsen");
            _print_set_cstr(pt_set);
            _print_set_cstr(pt_setex);
            printf("equal: %d, not equal: %d, ",
                set_equal(pt_set, pt_setex), set_not_equal(pt_set, pt_setex));
            printf("less: %d, less equal: %d, ",
                set_less(pt_set, pt_setex), set_less_equal(pt_set, pt_setex));
            printf("great: %d, great equal: %d\n",
                set_great(pt_set, pt_setex), set_great_equal(pt_set, pt_setex));

            set_insert(pt_set, "Author's Address");
            set_insert(pt_set, "Eastern New Mexico University");
            set_insert(pt_setex, "Phone: (505) 562-2694");
            _print_set_cstr(pt_set);
            _print_set_cstr(pt_setex);
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
            set_t* pt_set = create_set(char*);
            set_t* pt_setex = create_set(char*);
            if(pt_set == NULL || pt_setex == NULL)
            {
                return;
            }
            set_init(pt_set);
            set_init(pt_setex);
            set_swap(pt_set, pt_setex);
            _print_set_cstr(pt_set);
            _print_set_cstr(pt_setex);
            set_insert(pt_setex, "some gauge of how many people");
            set_insert(pt_setex, "OS/2 User Group");
            set_insert(pt_setex, "You may recognize some of the names in this group");
            set_swap(pt_set, pt_setex);
            _print_set_cstr(pt_set);
            _print_set_cstr(pt_setex);
            set_insert(pt_setex, "systems or CPU's.");
            set_insert(pt_setex, "number of researchers and implementers.");
            set_insert(pt_setex, "There is a group called The Phoenix Group");
            set_insert(pt_setex, "their desires for OS/2 to IBM.");
            set_insert(pt_setex, "organizations such as SHARE, GUIDE, COMMON");
            set_insert(pt_setex, "Company (DECIUS)");
            set_insert(pt_setex, "(SHARE, GUIDE and COMMON)");
            set_swap(pt_set, pt_setex);
            _print_set_cstr(pt_set);
            _print_set_cstr(pt_setex);
            set_clear(pt_setex);
            set_swap(pt_set, pt_setex);
            _print_set_cstr(pt_set);
            _print_set_cstr(pt_setex);
            set_destroy(pt_set);
            set_destroy(pt_setex);
        }
        /*set_find              */
        /*set_count             */
        {
            set_t* pt_set = create_set(char*);
            iterator_t t_iter;
            if(pt_set == NULL)
            {
                return;
            }
            set_init(pt_set);
            t_iter = set_find(pt_set, "SONET to Sonnet Translation");
            if(!iterator_equal(t_iter, set_end(pt_set)))
            {
                printf("cstr: %s, count: %d\n", (char*)iterator_get_pointer(t_iter),
                    set_count(pt_set, "SONET to Sonnet Translation"));
            }
            else
            {
                printf("not found, count: %d\n",
                    set_count(pt_set, "SONET to Sonnet Translation"));
            }
            set_insert(pt_set, "(SONNET).");
            set_insert(pt_set, "Protocol Overview");
            set_insert(pt_set, "this memo is unlimited.");
            set_insert(pt_set, "OCh-#");
            set_insert(pt_set, "indicates 50%");
            _print_set_cstr(pt_set);
            t_iter = set_find(pt_set, "2**704");
            if(!iterator_equal(t_iter, set_end(pt_set)))
            {
                printf("cstr: %s, count: %d\n", (char*)iterator_get_pointer(t_iter),
                    set_count(pt_set, "2**704"));
            }
            else
            {
                printf("not found, count: %d\n",
                    set_count(pt_set, "SONET to Sonnet Translation"));
            }
            t_iter = set_find(pt_set, "OCh-#");
            if(!iterator_equal(t_iter, set_end(pt_set)))
            {
                printf("cstr: %s, count: %d\n", (char*)iterator_get_pointer(t_iter),
                    set_count(pt_set, "OCh-#"));
            }
            else
            {
                printf("not found, count: %d\n",
                    set_count(pt_set, "SONET to Sonnet Translation"));
            }

            set_destroy(pt_set);
        }
        /*set_lower_bound       */
        /*set_upper_bound       */
        /*set_equal_range       */
        {
            set_t* pt_set = create_set(char*);
            iterator_t t_begin;
            iterator_t t_end;
            range_t t_range;
            iterator_t t_iter;
            if(pt_set == NULL)
            {
                return;
            }
            set_init(pt_set);
            t_begin = set_lower_bound(pt_set, "SONET");
            t_end = set_upper_bound(pt_set, "SONET");
            t_range = set_equal_range(pt_set, "SONET");
            assert(iterator_equal(t_begin, set_end(pt_set)) &&
                   iterator_equal(t_end, set_end(pt_set)) &&
                   iterator_equal(t_range.t_begin, set_end(pt_set)) &&
                   iterator_equal(t_range.t_end, set_end(pt_set)));
            set_insert(pt_set, "And sable curls,...");
            set_insert(pt_set, "OC-1, the OC-1");
            set_insert(pt_set, "Full many a glorious morning have I seen");
            set_insert(pt_set, "Kissing with golden face...");
            set_insert(pt_set, "When");
            set_insert(pt_set, "individual");
            set_insert(pt_set, "When");
            set_insert(pt_set, "I all alone beweep my outcast state");
            _print_set_cstr(pt_set);
            t_begin = set_lower_bound(pt_set, "Globe Communications");
            t_end = set_upper_bound(pt_set, "Globe Communications");
            t_range = set_equal_range(pt_set, "Globe Communications");
            t_iter = set_lower_bound(pt_set, "Globe Communications");
            assert(iterator_equal(t_begin, t_iter) &&
                   iterator_equal(t_end, t_iter) &&
                   iterator_equal(t_range.t_begin, t_iter) &&
                   iterator_equal(t_range.t_end, t_iter));
            t_begin = set_lower_bound(pt_set, "I all alone beweep my outcast state");
            t_end = set_upper_bound(pt_set, "I all alone beweep my outcast state");
            t_range = set_equal_range(pt_set, "I all alone beweep my outcast state");
            t_iter = set_lower_bound(pt_set, "I all alone beweep my outcast state");
            assert(iterator_equal(t_end, iterator_next(t_begin)) &&
                   iterator_equal(t_range.t_begin, t_begin) &&
                   iterator_equal(t_range.t_end, t_end));
            set_destroy(pt_set);
        }
        /*set_insert            */
        {
            set_t* pt_set = create_set(char*);
            if(pt_set == NULL)
            {
                return;
            }
            set_init_ex(pt_set, _set_cstr_pre);
            _print_set_cstr(pt_set);
            set_insert(pt_set, "BIB-VERSION:: CS-TR-v2.1");
            set_insert(pt_set, "ID:: OUKS//CS-TR-91-123");
            set_insert(pt_set, "ENTRY:: January 15, 1992");
            set_insert(pt_set, "ORGANIZATION:: Oceanview University, Kansas Computer Science");
            set_insert(pt_set, "TYPE:: Technical Report");
            set_insert(pt_set, "REVISION:: January 5, 1995; FTP access information added");
            set_insert(pt_set, "AUTHOR:: Finnegan, James A.");
            _print_set_cstr(pt_set);
            set_destroy(pt_set);
        }
        /*set_insert_hint       */
        {
            set_t* pt_set = create_set(char*);
            iterator_t t_iter;
            if(pt_set == NULL)
            {
                return;
            }
            set_init_ex(pt_set, _set_cstr_pre);
            t_iter = set_begin(pt_set);
            _print_set_cstr(pt_set);
            set_insert_hint(pt_set, t_iter, "Oceanview, KS 54321  Tel: 913-456-7890");
            set_insert_hint(pt_set, t_iter, "<Finnegan@cs.ouks.edu>");
            set_insert_hint(pt_set, t_iter, "AUTHOR:: Pooh, Winnie The");
            set_insert_hint(pt_set, t_iter, "DATE:: December 1991");
            set_insert_hint(pt_set, t_iter, "PAGES:: 48");
            _print_set_cstr(pt_set);
            set_destroy(pt_set);
        }
        /*set_insert_range      */
        {
            set_t* pt_set = create_set(char*);
            set_t* pt_setex = create_set(char*);
            if(pt_set == NULL || pt_setex == NULL)
            {
                return;
            }
            set_init_ex(pt_set, _set_cstr_pre);
            set_init(pt_setex);
            set_insert_range(pt_set, set_begin(pt_setex), set_end(pt_setex));
            _print_set_cstr(pt_set);
            set_insert(pt_setex, "HANDLE:: hdl:oceanview.electr/CS-TR-91-123");
            set_insert(pt_setex, "OTHER_ACCESS::url:http://electr.oceanview.edu/CS-TR-91-123");
            set_insert(pt_setex, "OTHER_ACCESS:: url:ftp://electr.oceanview.edu/CS-TR-91-123");
            set_insert(pt_setex, "KEYWORD:: Scientific Communication");
            set_insert(pt_setex, "CR-CATEGORY:: D.0");
            set_insert(pt_setex, "SERIES:: Communication");
            set_insert(pt_setex, "FUNDING:: FAS");
            set_insert(pt_setex, "CONTRACT:: FAS-91-C-1234");
            set_insert(pt_setex, "MONITORING:: FNBO");
            set_insert(pt_setex, "LANGUAGE:: English");
            set_insert(pt_setex, "CONTACT:: 100 Aker Wood");
            _print_set_cstr(pt_setex);
            set_insert_range(pt_set, set_begin(pt_setex), set_begin(pt_setex));
            _print_set_cstr(pt_set);
            set_insert_range(pt_set, set_begin(pt_setex),
                iterator_advance(set_begin(pt_setex), 3));
            _print_set_cstr(pt_set);
            set_insert_range(pt_set, iterator_advance(set_begin(pt_setex), 4),
                iterator_advance(set_begin(pt_setex), 6));
            _print_set_cstr(pt_set);
            set_insert_range(pt_set, iterator_advance(set_begin(pt_setex), 8),
                set_end(pt_setex));
            _print_set_cstr(pt_set);
            set_insert_range(pt_set, set_end(pt_setex), set_end(pt_setex));
            _print_set_cstr(pt_set);
            set_clear(pt_set);
            set_insert_range(pt_set, set_begin(pt_setex), set_end(pt_setex));
            _print_set_cstr(pt_set);
            set_destroy(pt_set);
            set_destroy(pt_setex);
        }
        /*set_erase             */
        {
            set_t* pt_set = create_set(char*);
            if(pt_set == NULL)
            {
                return;
            }
            set_init(pt_set);
            set_erase(pt_set, "Keep It Simple.");
            _print_set_cstr(pt_set);
            set_insert(pt_set, "HANDLE:: hdl:oceanview.electr/CS-TR-91-123");
            set_insert(pt_set, "OTHER_ACCESS::url:http://electr.oceanview.edu/CS-TR-91-123");
            set_insert(pt_set, "OTHER_ACCESS:: url:ftp://electr.oceanview.edu/CS-TR-91-123");
            set_insert(pt_set, "KEYWORD:: Scientific Communication");
            set_insert(pt_set, "CR-CATEGORY:: D.0");
            set_insert(pt_set, "SERIES:: Communication");
            set_insert(pt_set, "FUNDING:: FAS");
            set_insert(pt_set, "CONTRACT:: FAS-91-C-1234");
            set_insert(pt_set, "MONITORING:: FNBO");
            set_insert(pt_set, "LANGUAGE:: English");
            set_insert(pt_set, "CONTACT:: 100 Aker Wood");
            set_erase(pt_set, "Keep It Simple.");
            _print_set_cstr(pt_set);
            set_erase(pt_set, "FUNDING:: FAS");
            _print_set_cstr(pt_set);
            set_destroy(pt_set);
        }
        /*set_erase_pos         */
        {
            set_t* pt_set = create_set(char*);
            if(pt_set == NULL)
            {
                return;
            }
            set_init(pt_set);
            set_insert(pt_set, "HANDLE:: hdl:oceanview.electr/CS-TR-91-123");
            set_insert(pt_set, "OTHER_ACCESS::url:http://electr.oceanview.edu/CS-TR-91-123");
            set_insert(pt_set, "OTHER_ACCESS:: url:ftp://electr.oceanview.edu/CS-TR-91-123");
            set_insert(pt_set, "KEYWORD:: Scientific Communication");
            set_insert(pt_set, "CR-CATEGORY:: D.0");
            set_insert(pt_set, "SERIES:: Communication");
            set_insert(pt_set, "FUNDING:: FAS");
            set_insert(pt_set, "CONTRACT:: FAS-91-C-1234");
            set_insert(pt_set, "MONITORING:: FNBO");
            set_insert(pt_set, "LANGUAGE:: English");
            set_insert(pt_set, "CONTACT:: 100 Aker Wood");
            _print_set_cstr(pt_set);
            set_erase_pos(pt_set, set_begin(pt_set));
            _print_set_cstr(pt_set);
            set_erase_pos(pt_set, iterator_prev(set_end(pt_set)));
            _print_set_cstr(pt_set);
            set_erase_pos(pt_set, iterator_advance(set_begin(pt_set), 4));
            _print_set_cstr(pt_set);
            while(!set_empty(pt_set))
            {
                set_erase_pos(pt_set, set_begin(pt_set));
            }
            _print_set_cstr(pt_set);
            set_destroy(pt_set);
        }
        /*set_erase_range       */
        {
            set_t* pt_set = create_set(char*);
            if(pt_set == NULL)
            {
                return;
            }
            set_init(pt_set);
            set_erase_range(pt_set, set_begin(pt_set), set_end(pt_set));
            _print_set_cstr(pt_set);
            set_insert(pt_set, "BIB-VERSION:: CS-TR-v2.1");
            set_insert(pt_set, "ID:: OUKS//CS-TR-91-123");
            set_insert(pt_set, "ENTRY:: January 15, 1992");
            set_insert(pt_set, "ORGANIZATION:: Oceanview University, Kansas Computer Science");
            set_insert(pt_set, "TYPE:: Technical Report");
            set_insert(pt_set, "REVISION:: January 5, 1995; FTP access information added");
            set_insert(pt_set, "AUTHOR:: Finnegan, James A.");
            set_insert(pt_set, "HANDLE:: hdl:oceanview.electr/CS-TR-91-123");
            set_insert(pt_set, "OTHER_ACCESS::url:http://electr.oceanview.edu/CS-TR-91-123");
            set_insert(pt_set, "OTHER_ACCESS:: url:ftp://electr.oceanview.edu/CS-TR-91-123");
            set_insert(pt_set, "KEYWORD:: Scientific Communication");
            set_insert(pt_set, "CR-CATEGORY:: D.0");
            set_insert(pt_set, "SERIES:: Communication");
            set_insert(pt_set, "FUNDING:: FAS");
            set_insert(pt_set, "CONTRACT:: FAS-91-C-1234");
            set_insert(pt_set, "MONITORING:: FNBO");
            set_insert(pt_set, "LANGUAGE:: English");
            set_insert(pt_set, "CONTACT:: 100 Aker Wood");
            _print_set_cstr(pt_set);
            set_erase_range(pt_set, set_begin(pt_set), set_begin(pt_set));
            _print_set_cstr(pt_set);
            set_erase_range(pt_set, set_begin(pt_set), iterator_advance(set_begin(pt_set), 3));
            _print_set_cstr(pt_set);
            set_erase_range(pt_set, iterator_advance(set_begin(pt_set), 2),
                iterator_advance(set_begin(pt_set), 5));
            _print_set_cstr(pt_set);
            set_erase_range(pt_set, iterator_advance(set_begin(pt_set), 5), set_end(pt_set));
            _print_set_cstr(pt_set);
            set_erase_range(pt_set, set_end(pt_set), set_end(pt_set));
            _print_set_cstr(pt_set);
            set_erase_range(pt_set, set_begin(pt_set), set_end(pt_set));
            _print_set_cstr(pt_set);
            set_destroy(pt_set);
        }
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

void test_multiset(void)
{
    /* c built-in type */
    {
        /*create_multiset            */
        {
            multiset_t* pt_mset = create_multiset(int);
            if(pt_mset == NULL)
            {
                return;
            }
            multiset_init(pt_mset);
            _print_multiset_c(pt_mset, "%d, ", int);
            multiset_insert(pt_mset, 344);
            multiset_insert(pt_mset, 98);
            multiset_insert(pt_mset, 23);
            multiset_insert(pt_mset, 222);
            multiset_insert(pt_mset, 98);
            _print_multiset_c(pt_mset, "%d, ", int);
            multiset_destroy(pt_mset);
        }
        /*multiset_init              */
        /*multiset_init_ex           */
        {
            multiset_t* pt_mset = create_multiset(double);
            if(pt_mset == NULL)
            {
                return;
            }
            multiset_init_ex(pt_mset, fun_great_double);
            _print_multiset_c(pt_mset, "%lf, ", double);
            multiset_insert(pt_mset, 43.452);
            multiset_insert(pt_mset, 0.009);
            multiset_insert(pt_mset, 334.22);
            multiset_insert(pt_mset, 0.009);
            multiset_insert(pt_mset, 2.2);
            _print_multiset_c(pt_mset, "%lf, ", double);
            multiset_destroy(pt_mset);
        }
        /*multiset_init_copy         */
        {
            multiset_t* pt_mset = create_multiset(double);
            multiset_t* pt_msetex = create_multiset(double);
            if(pt_mset == NULL || pt_msetex == NULL)
            {
                return;
            }
            multiset_init_ex(pt_msetex, fun_great_double);
            multiset_insert(pt_msetex, 78.243211);
            multiset_insert(pt_msetex, 223.22);
            multiset_insert(pt_msetex, -787.2);
            multiset_insert(pt_msetex, -55.3);
            multiset_insert(pt_msetex, 223.33);
            multiset_init_copy(pt_mset, pt_msetex);
            _print_multiset_c(pt_mset, "%lf, ", double);
            multiset_destroy(pt_mset);
            multiset_destroy(pt_msetex);
        }
        /*multiset_init_copy_range   */
        {
            multiset_t* pt_mset = create_multiset(int);
            multiset_t* pt_msetex = create_multiset(int);
            if(pt_mset == NULL || pt_msetex == NULL)
            {
                return;
            }
            multiset_init_ex(pt_msetex, fun_great_int);
            multiset_insert(pt_msetex, 209);
            multiset_insert(pt_msetex, 1212);
            multiset_insert(pt_msetex, 2);
            multiset_insert(pt_msetex, 1792);
            multiset_insert(pt_msetex, 200);
            multiset_insert(pt_msetex, 12);
            multiset_insert(pt_msetex, -99);
            multiset_insert(pt_msetex, 12);
            multiset_insert(pt_msetex, 29);
            multiset_insert(pt_msetex, -212);
            multiset_insert(pt_msetex, 259);
            multiset_insert(pt_msetex, -12);
            _print_multiset_c(pt_msetex, "%d, ", int);
            multiset_init_copy_range(pt_mset,
                multiset_begin(pt_msetex), multiset_end(pt_msetex));
            _print_multiset_c(pt_mset, "%d, ", int);
            multiset_destroy(pt_mset);
            multiset_destroy(pt_msetex);
        }
        /*multiset_init_copy_range_ex*/
        {
            multiset_t* pt_mset = create_multiset(int);
            multiset_t* pt_msetex = create_multiset(int);
            if(pt_mset == NULL || pt_msetex == NULL)
            {
                return;
            }
            multiset_init(pt_msetex);
            multiset_insert(pt_msetex, 209);
            multiset_insert(pt_msetex, 1212);
            multiset_insert(pt_msetex, 2);
            multiset_insert(pt_msetex, 1792);
            multiset_insert(pt_msetex, 200);
            multiset_insert(pt_msetex, 12);
            multiset_insert(pt_msetex, -99);
            multiset_insert(pt_msetex, 12);
            multiset_insert(pt_msetex, 29);
            multiset_insert(pt_msetex, -212);
            multiset_insert(pt_msetex, 259);
            multiset_insert(pt_msetex, -12);
            _print_multiset_c(pt_msetex, "%d, ", int);
            multiset_init_copy_range_ex(pt_mset,
                multiset_begin(pt_msetex), multiset_end(pt_msetex), fun_great_int);
            _print_multiset_c(pt_mset, "%d, ", int);
            multiset_destroy(pt_mset);
            multiset_destroy(pt_msetex);
        }
        /*multiset_destroy           */
        /*multiset_assign            */
        {
            multiset_t* pt_mset = create_multiset(int);
            multiset_t* pt_msetex = create_multiset(int);
            if(pt_mset == NULL || pt_msetex == NULL)
            {
                return;
            }
            multiset_init(pt_mset);
            multiset_init(pt_msetex);
            multiset_assign(pt_mset, pt_msetex);
            _print_multiset_c(pt_mset, "%d, ", int);
            multiset_insert(pt_msetex, 34);
            multiset_insert(pt_msetex, 78);
            multiset_insert(pt_msetex, 234);
            multiset_insert(pt_msetex, -34);
            multiset_insert(pt_msetex, -4);
            multiset_assign(pt_mset, pt_msetex);
            _print_multiset_c(pt_mset, "%d, ", int);
            multiset_clear(pt_msetex);
            multiset_assign(pt_mset, pt_msetex);
            _print_multiset_c(pt_mset, "%d, ", int);
            multiset_destroy(pt_mset);
            multiset_destroy(pt_msetex);
        }
        /*multiset_size              */
        /*multiset_empty             */
        /*multiset_max_size          */
        /*multiset_begin             */
        /*multiset_end               */
        /*multiset_key_less          */
        /*multiset_value_less        */
        {
            multiset_t* pt_mset = create_multiset(double);
            if(pt_mset == NULL)
            {
                return;
            }
            multiset_init(pt_mset);
            assert(multiset_key_less(pt_mset) == multiset_value_less(pt_mset));
            multiset_destroy(pt_mset);
        }
        /*multiset_clear             */
        {
            multiset_t* pt_mset = create_multiset(double);
            if(pt_mset == NULL)
            {
                return;
            }
            multiset_init(pt_mset);
            multiset_clear(pt_mset);
            _print_multiset_c(pt_mset, "%lf, ", double);
            multiset_insert(pt_mset, 23.099);
            multiset_insert(pt_mset, 122.222);
            multiset_insert(pt_mset, 122.222);
            multiset_insert(pt_mset, 90.00);
            multiset_insert(pt_mset, 43.323);
            _print_multiset_c(pt_mset, "%lf, ", double);
            multiset_clear(pt_mset);
            _print_multiset_c(pt_mset, "%lf, ", double);
            multiset_destroy(pt_mset);
        }
        /*multiset_equal             */
        /*multiset_not_equal         */
        /*multiset_less              */
        /*multiset_less_equal        */
        /*multiset_great             */
        /*multiset_great_equal       */
        {
            multiset_t* pt_mset = create_multiset(int);
            multiset_t* pt_msetex = create_multiset(int);
            if(pt_mset == NULL || pt_msetex == NULL)
            {
                return;
            }
            multiset_init(pt_mset);
            multiset_init(pt_msetex);
            _print_multiset_c(pt_mset, "%d, ", int);
            _print_multiset_c(pt_msetex, "%d, ", int);
            printf("equal: %d, not equal: %d, ",
                multiset_equal(pt_mset, pt_msetex), multiset_not_equal(pt_mset, pt_msetex));
            printf("less: %d, less equal: %d, ",
                multiset_less(pt_mset, pt_msetex), multiset_less_equal(pt_mset, pt_msetex));
            printf("great: %d, great equal: %d\n",
                multiset_great(pt_mset, pt_msetex), multiset_great_equal(pt_mset, pt_msetex));

            multiset_insert(pt_mset, 4567);
            _print_multiset_c(pt_mset, "%d, ", int);
            _print_multiset_c(pt_msetex, "%d, ", int);
            printf("equal: %d, not equal: %d, ",
                multiset_equal(pt_mset, pt_msetex), multiset_not_equal(pt_mset, pt_msetex));
            printf("less: %d, less equal: %d, ",
                multiset_less(pt_mset, pt_msetex), multiset_less_equal(pt_mset, pt_msetex));
            printf("great: %d, great equal: %d\n",
                multiset_great(pt_mset, pt_msetex), multiset_great_equal(pt_mset, pt_msetex));

            multiset_insert(pt_msetex, 4567);
            _print_multiset_c(pt_mset, "%d, ", int);
            _print_multiset_c(pt_msetex, "%d, ", int);
            printf("equal: %d, not equal: %d, ",
                multiset_equal(pt_mset, pt_msetex), multiset_not_equal(pt_mset, pt_msetex));
            printf("less: %d, less equal: %d, ",
                multiset_less(pt_mset, pt_msetex), multiset_less_equal(pt_mset, pt_msetex));
            printf("great: %d, great equal: %d\n",
                multiset_great(pt_mset, pt_msetex), multiset_great_equal(pt_mset, pt_msetex));

            multiset_insert(pt_mset, 334);
            multiset_insert(pt_mset, 9092);
            multiset_insert(pt_msetex, 4567);
            _print_multiset_c(pt_mset, "%d, ", int);
            _print_multiset_c(pt_msetex, "%d, ", int);
            printf("equal: %d, not equal: %d, ",
                multiset_equal(pt_mset, pt_msetex), multiset_not_equal(pt_mset, pt_msetex));
            printf("less: %d, less equal: %d, ",
                multiset_less(pt_mset, pt_msetex), multiset_less_equal(pt_mset, pt_msetex));
            printf("great: %d, great equal: %d\n",
                multiset_great(pt_mset, pt_msetex), multiset_great_equal(pt_mset, pt_msetex));
            
            multiset_destroy(pt_mset);
            multiset_destroy(pt_msetex);
        }
        /*multiset_swap              */
        {
            multiset_t* pt_mset = create_multiset(int);
            multiset_t* pt_msetex = create_multiset(int);
            if(pt_mset == NULL || pt_msetex == NULL)
            {
                return;
            }
            multiset_init(pt_mset);
            multiset_init_ex(pt_msetex, fun_great_int);
            multiset_swap(pt_mset, pt_msetex);
            _print_multiset_c(pt_mset, "%d, ", int);
            _print_multiset_c(pt_msetex, "%d, ", int);
            multiset_insert(pt_msetex, 92482);
            multiset_insert(pt_msetex, -9883402);
            multiset_insert(pt_msetex, 282);
            multiset_insert(pt_msetex, 222722);
            multiset_swap(pt_mset, pt_msetex);
            _print_multiset_c(pt_mset, "%d, ", int);
            _print_multiset_c(pt_msetex, "%d, ", int);
            multiset_insert(pt_msetex, 92482);
            multiset_insert(pt_msetex, -9883402);
            multiset_insert(pt_msetex, 282);
            multiset_insert(pt_msetex, 222722);
            multiset_insert(pt_msetex, 92482);
            multiset_insert(pt_msetex, -9883402);
            multiset_insert(pt_msetex, 282);
            multiset_insert(pt_msetex, 222722);
            multiset_swap(pt_mset, pt_msetex);
            _print_multiset_c(pt_mset, "%d, ", int);
            _print_multiset_c(pt_msetex, "%d, ", int);
            multiset_clear(pt_msetex);
            multiset_swap(pt_mset, pt_msetex);
            _print_multiset_c(pt_mset, "%d, ", int);
            _print_multiset_c(pt_msetex, "%d, ", int);
            multiset_destroy(pt_mset);
            multiset_destroy(pt_msetex);
        }
        /*multiset_find              */
        {
            multiset_t* pt_mset = create_multiset(int);
            iterator_t t_iterex;
            int        n_elem = 0;
            if(pt_mset == NULL)
            {
                return;
            }
            multiset_init(pt_mset);
            n_elem = 7884;
            t_iterex = multiset_find(pt_mset, n_elem);
            if(!iterator_equal(t_iterex, multiset_end(pt_mset)))
            {
                printf("%d, count: %d\n",
                    *(int*)iterator_get_pointer(t_iterex), multiset_count(pt_mset, n_elem));
            }
            else
            {
                printf("not found, count: %d\n", multiset_count(pt_mset, n_elem));
            }
            multiset_insert(pt_mset, 2220);
            multiset_insert(pt_mset, 1110);
            multiset_insert(pt_mset, 45677);
            multiset_insert(pt_mset, 222);
            multiset_insert(pt_mset, 2323);
            multiset_insert(pt_mset, 1110);
            multiset_insert(pt_mset, 1110);
            _print_multiset_c(pt_mset, "%d, ", int);
            n_elem = 7884;
            t_iterex = multiset_find(pt_mset, n_elem);
            if(!iterator_equal(t_iterex, multiset_end(pt_mset)))
            {
                printf("%d, count: %d\n",
                    *(int*)iterator_get_pointer(t_iterex), multiset_count(pt_mset, n_elem));
            }
            else
            {
                printf("not found, count: %d\n", multiset_count(pt_mset, n_elem));
            }
            n_elem = 1110;
            t_iterex = multiset_find(pt_mset, n_elem);
            if(!iterator_equal(t_iterex, multiset_end(pt_mset)))
            {
                printf("%d, count: %d\n",
                    *(int*)iterator_get_pointer(t_iterex), multiset_count(pt_mset, n_elem));
            }
            else
            {
                printf("not found, count: %d\n", multiset_count(pt_mset, n_elem));
            }
            multiset_destroy(pt_mset);
        }
        /*_multiset_count            */
        /*_multiset_lower_bound      */
        /*_multiset_upper_bound      */
        /*_multiset_equal_range      */
        {
            multiset_t* pt_mset = create_multiset(int);
            iterator_t t_begin;
            iterator_t t_end;
            iterator_t t_iter;
            range_t    t_range;
            int        n_elem = 0;
            if(pt_mset == NULL)
            {
                return;
            }
            multiset_init(pt_mset);
            n_elem = 89;
            t_begin = multiset_lower_bound(pt_mset, n_elem);
            t_end = multiset_upper_bound(pt_mset, n_elem);
            t_range = multiset_equal_range(pt_mset, n_elem);
            assert(iterator_equal(t_begin, multiset_end(pt_mset)) &&
                   iterator_equal(t_end, multiset_end(pt_mset)) &&
                   iterator_equal(t_range.t_begin, multiset_end(pt_mset)) &&
                   iterator_equal(t_range.t_end, multiset_end(pt_mset)));
            multiset_insert(pt_mset, 23234);
            multiset_insert(pt_mset, 222);
            multiset_insert(pt_mset, 222);
            multiset_insert(pt_mset, 203859);
            multiset_insert(pt_mset, 222);
            multiset_insert(pt_mset, 2);
            multiset_insert(pt_mset, 99);
            multiset_insert(pt_mset, 2123);
            _print_multiset_c(pt_mset, "%d, ", int);
            t_begin = multiset_lower_bound(pt_mset, n_elem);
            t_end = multiset_upper_bound(pt_mset, n_elem);
            t_range = multiset_equal_range(pt_mset, n_elem);
            t_iter = multiset_lower_bound(pt_mset, n_elem);
            assert(iterator_equal(t_begin, t_iter) &&
                   iterator_equal(t_end, t_iter) &&
                   iterator_equal(t_range.t_begin, t_iter) &&
                   iterator_equal(t_range.t_end, t_iter));
            n_elem = 222;
            t_begin = multiset_lower_bound(pt_mset, n_elem);
            t_end = multiset_upper_bound(pt_mset, n_elem);
            t_range = multiset_equal_range(pt_mset, n_elem);
            t_iter = multiset_lower_bound(pt_mset, n_elem);
            assert(iterator_distance(t_begin, t_end) ==
                iterator_distance(t_range.t_begin, t_range.t_end));
            printf("%d\n", iterator_distance(t_begin, t_end));
            multiset_destroy(pt_mset);
        }
        /*multiset_insert            */
        {
            multiset_t* pt_mset = create_multiset(double);
            multiset_t* pt_msetex = create_multiset(double);
            if(pt_mset == NULL || pt_msetex == NULL)
            {
                return;
            }
            multiset_init(pt_mset);
            multiset_init_ex(pt_msetex, fun_great_double);
            multiset_insert(pt_mset, 2344.222);
            multiset_insert(pt_mset, -234.0);
            multiset_insert(pt_mset, 90.90);
            multiset_insert(pt_mset, 222.222);
            multiset_insert(pt_mset, 46.25);
            multiset_insert(pt_mset, 222.222);
            multiset_insert(pt_mset, 90.90);
            multiset_insert(pt_msetex, 2344.222);
            multiset_insert(pt_msetex, -234.0);
            multiset_insert(pt_msetex, 90.90);
            multiset_insert(pt_msetex, 222.222);
            multiset_insert(pt_msetex, 46.25);
            multiset_insert(pt_msetex, 222.222);
            multiset_insert(pt_msetex, 90.90);
            _print_multiset_c(pt_mset, "%lf, ", double);
            _print_multiset_c(pt_msetex, "%lf, ", double);
            multiset_destroy(pt_mset);
            multiset_destroy(pt_msetex);
        }
        /*multiset_insert_hint       */
        {
            multiset_t* pt_mset = create_multiset(int);
            multiset_t* pt_msetex = create_multiset(int);
            iterator_t t_iter;
            iterator_t t_iterex;
            if(pt_mset == NULL || pt_msetex == NULL)
            {
                return;
            }
            multiset_init(pt_mset);
            multiset_init_ex(pt_msetex, fun_great_int);
            t_iter = multiset_begin(pt_mset);
            t_iterex = multiset_begin(pt_msetex);
            multiset_insert_hint(pt_mset, t_iter, 92);
            multiset_insert_hint(pt_mset, t_iter, 2334);
            multiset_insert_hint(pt_mset, t_iter, 289);
            multiset_insert_hint(pt_mset, t_iter, -284);
            multiset_insert_hint(pt_mset, t_iter, -74);
            multiset_insert_hint(pt_mset, t_iter, 289);
            multiset_insert_hint(pt_msetex, t_iterex, 92);
            multiset_insert_hint(pt_msetex, t_iterex, 2334);
            multiset_insert_hint(pt_msetex, t_iterex, 289);
            multiset_insert_hint(pt_msetex, t_iterex, -284);
            multiset_insert_hint(pt_msetex, t_iterex, -74);
            multiset_insert_hint(pt_msetex, t_iterex, 289);
            _print_multiset_c(pt_mset, "%d, ", int);
            _print_multiset_c(pt_msetex, "%d, ", int);
            multiset_destroy(pt_mset);
            multiset_destroy(pt_msetex);
        }
        /*multiset_insert_range      */
        {
            multiset_t* pt_mset = create_multiset(double);
            multiset_t* pt_msetex = create_multiset(double);
            if(pt_mset == NULL || pt_msetex == NULL)
            {
                return;
            }
            multiset_init_ex(pt_mset, fun_great_double);
            multiset_init(pt_msetex);
            multiset_insert_range(pt_mset, multiset_begin(pt_msetex), multiset_end(pt_msetex));
            _print_multiset_c(pt_mset, "%g, ", double);
            multiset_insert(pt_msetex, 0.0004);
            multiset_insert(pt_msetex, 2934.920);
            multiset_insert(pt_msetex, -4.0202);
            multiset_insert(pt_msetex, 22.2222);
            multiset_insert(pt_msetex, -4.0202);
            multiset_insert(pt_msetex, -4.0202);
            multiset_insert(pt_msetex, -555.0);
            multiset_insert(pt_msetex, 8.0004);
            multiset_insert(pt_msetex, 34.929);
            multiset_insert(pt_msetex, 0.0202);
            multiset_insert(pt_msetex, 22.2222);
            multiset_insert(pt_msetex, 4.0202);
            multiset_insert(pt_msetex, 4.0202);
            multiset_insert(pt_msetex, -555.0);
            _print_multiset_c(pt_msetex, "%g, ", double);
            multiset_insert_range(pt_mset, multiset_begin(pt_msetex),
                multiset_begin(pt_msetex));
            _print_multiset_c(pt_mset, "%g, ", double);
            multiset_insert_range(pt_mset, multiset_begin(pt_msetex),
                iterator_advance(multiset_begin(pt_msetex), 3));
            _print_multiset_c(pt_mset, "%g, ", double);
            multiset_insert_range(pt_mset, iterator_advance(multiset_begin(pt_msetex), 5),
                iterator_advance(multiset_begin(pt_msetex), 7));
            _print_multiset_c(pt_mset, "%g, ", double);
            multiset_insert_range(pt_mset, iterator_advance(multiset_begin(pt_msetex), 10),
                multiset_end(pt_msetex));
            _print_multiset_c(pt_mset, "%g, ", double);
            multiset_insert_range(pt_mset, multiset_end(pt_msetex), multiset_end(pt_msetex));
            _print_multiset_c(pt_mset, "%g, ", double);
            multiset_clear(pt_mset);
            multiset_insert_range(pt_mset, multiset_begin(pt_msetex), multiset_end(pt_msetex));
            _print_multiset_c(pt_mset, "%g, ", double);
            multiset_destroy(pt_mset);
            multiset_destroy(pt_msetex);
        }
        /*multiset_erase             */
        {
            multiset_t* pt_mset = create_multiset(double);
            double      d_elem = 0.0;
            if(pt_mset == NULL)
            {
                return;
            }
            multiset_init(pt_mset);
            d_elem = 45.222;
            multiset_erase(pt_mset, d_elem);
            _print_multiset_c(pt_mset, "%g, ", double);
            multiset_insert(pt_mset, 0.0004);
            multiset_insert(pt_mset, 2934.920);
            multiset_insert(pt_mset, -4.0202);
            multiset_insert(pt_mset, 22.2222);
            multiset_insert(pt_mset, -4.0202);
            multiset_insert(pt_mset, -4.0202);
            multiset_insert(pt_mset, -555.0);
            multiset_insert(pt_mset, 8.0004);
            multiset_insert(pt_mset, 34.929);
            multiset_insert(pt_mset, 0.0202);
            multiset_insert(pt_mset, 22.2222);
            multiset_insert(pt_mset, 4.0202);
            multiset_insert(pt_mset, 4.0202);
            multiset_insert(pt_mset, -555.0);
            _print_multiset_c(pt_mset, "%g, ", double);
            d_elem = 8.0004;
            multiset_erase(pt_mset, d_elem);
            _print_multiset_c(pt_mset, "%g, ", double);
            d_elem = 22.2222;
            multiset_erase(pt_mset, d_elem);
            _print_multiset_c(pt_mset, "%g, ", double);
            d_elem = 9999.999;
            multiset_erase(pt_mset, d_elem);
            _print_multiset_c(pt_mset, "%g, ", double);
            multiset_destroy(pt_mset);
        }
        /*multiset_erase_pos         */
        {
            multiset_t* pt_mset = create_multiset(double);
            if(pt_mset == NULL)
            {
                return;
            }
            multiset_init(pt_mset);
            multiset_insert(pt_mset, 0.0004);
            multiset_insert(pt_mset, 2934.920);
            multiset_insert(pt_mset, -4.0202);
            multiset_insert(pt_mset, 22.2222);
            multiset_insert(pt_mset, -4.0202);
            multiset_insert(pt_mset, -4.0202);
            multiset_insert(pt_mset, -555.0);
            multiset_insert(pt_mset, 8.0004);
            multiset_insert(pt_mset, 34.929);
            multiset_insert(pt_mset, 0.0202);
            multiset_insert(pt_mset, 22.2222);
            multiset_insert(pt_mset, 4.0202);
            multiset_insert(pt_mset, 4.0202);
            multiset_insert(pt_mset, -555.0);
            _print_multiset_c(pt_mset, "%g, ", double);
            multiset_erase_pos(pt_mset, multiset_begin(pt_mset));
            _print_multiset_c(pt_mset, "%g, ", double);
            /* bug in rb tree */
            multiset_erase_pos(pt_mset, iterator_advance(multiset_begin(pt_mset), 3));
            _print_multiset_c(pt_mset, "%g, ", double);
            multiset_erase_pos(pt_mset, iterator_prev(multiset_end(pt_mset)));
            _print_multiset_c(pt_mset, "%g, ", double);
            while(!multiset_empty(pt_mset))
            {
                multiset_erase_pos(pt_mset, multiset_begin(pt_mset));
            }
            _print_multiset_c(pt_mset, "%g, ", double);
            multiset_destroy(pt_mset);
        }
        /*multiset_erase_range       */
        {
            multiset_t* pt_mset = create_multiset(int);
            if(pt_mset == NULL)
            {
                return;
            }
            multiset_init(pt_mset);
            multiset_erase_range(pt_mset, multiset_begin(pt_mset), multiset_end(pt_mset));
            _print_multiset_c(pt_mset, "%d, ", int);
            multiset_insert(pt_mset, 234);
            multiset_insert(pt_mset, -233);
            multiset_insert(pt_mset, 220);
            multiset_insert(pt_mset, 22);
            multiset_insert(pt_mset, -88);
            multiset_insert(pt_mset, 0);
            multiset_insert(pt_mset, 0);
            multiset_insert(pt_mset, 23);
            multiset_insert(pt_mset, -3);
            multiset_insert(pt_mset, 456);
            multiset_insert(pt_mset, 111);
            multiset_insert(pt_mset, 90);
            multiset_insert(pt_mset, 4);
            multiset_insert(pt_mset, 20);
            multiset_insert(pt_mset, -566);
            multiset_insert(pt_mset, -53);
            _print_multiset_c(pt_mset, "%d, ", int);
            multiset_erase_range(pt_mset, multiset_begin(pt_mset), multiset_begin(pt_mset));
            _print_multiset_c(pt_mset, "%d, ", int);
            multiset_erase_range(pt_mset, multiset_begin(pt_mset),
                iterator_advance(multiset_begin(pt_mset), 4));
            _print_multiset_c(pt_mset, "%d, ", int);
            multiset_erase_range(pt_mset, iterator_next(multiset_begin(pt_mset)),
                iterator_advance(multiset_begin(pt_mset), 3));
            _print_multiset_c(pt_mset, "%d, ", int);
            multiset_erase_range(pt_mset, iterator_advance(multiset_begin(pt_mset), 3),
                multiset_end(pt_mset));
            _print_multiset_c(pt_mset, "%d, ", int);
            multiset_erase_range(pt_mset, multiset_end(pt_mset), multiset_end(pt_mset));
            _print_multiset_c(pt_mset, "%d, ", int);
            multiset_erase_range(pt_mset, multiset_begin(pt_mset), multiset_end(pt_mset));
            _print_multiset_c(pt_mset, "%d, ", int);
            multiset_destroy(pt_mset);
        }
    }
    /* user define type */
    {
        type_register(setsample_t, _setsample_init, _setsample_copy,
            _setsample_less, _setsample_destroy);
        type_duplicate(setsample_t, multisetsample_t);
        _type_debug();
        /*create_multiset            */
        {
            multiset_t* pt_mset = create_multiset(multisetsample_t);
            multisetsample_t t_mss;
            if(pt_mset == NULL)
            {
                return;
            }
            multiset_init(pt_mset);
            _print_multiset_user(pt_mset);
            t_mss._n_first = 78;
            t_mss._n_second = -4;
            t_mss._n_third = 2234;
            multiset_insert(pt_mset, &t_mss);
            t_mss._n_first = 0;
            t_mss._n_second = 0;
            t_mss._n_third = 0;
            multiset_insert(pt_mset, &t_mss);
            t_mss._n_first = 45;
            t_mss._n_second = 900;
            t_mss._n_third = 223;
            multiset_insert(pt_mset, &t_mss);
            _print_multiset_user(pt_mset);
            multiset_destroy(pt_mset);
        }
        /*multiset_init              */
        /*multiset_init_ex           */
        {
            multiset_t* pt_mset = create_multiset(multisetsample_t);
            multisetsample_t t_mss;
            if(pt_mset == NULL)
            {
                return;
            }
            multiset_init_ex(pt_mset, _setsample_great);
            _print_multiset_user(pt_mset);
            t_mss._n_first = 84;
            t_mss._n_second = 0;
            t_mss._n_third = -5;
            multiset_insert(pt_mset, &t_mss);
            t_mss._n_first = 23;
            t_mss._n_second = 90;
            t_mss._n_third = 22222;
            multiset_insert(pt_mset, &t_mss);
            t_mss._n_first = -3990;
            t_mss._n_second = 9000;
            t_mss._n_third = 22;
            multiset_insert(pt_mset, &t_mss);
            t_mss._n_first = 10;
            t_mss._n_second = 789;
            t_mss._n_third = 90;
            multiset_insert(pt_mset, &t_mss);
            multiset_insert(pt_mset, &t_mss);
            _print_multiset_user(pt_mset);
            multiset_destroy(pt_mset);
        }
        /*multiset_init_copy         */
        {
            multiset_t* pt_mset = create_multiset(setsample_t);
            multiset_t* pt_msetex = create_multiset(multisetsample_t);
            setsample_t t_ss;
            if(pt_mset == NULL || pt_msetex == NULL)
            {
                return;
            }
            multiset_init_ex(pt_msetex, _setsample_great);
            t_ss._n_first = 34;
            t_ss._n_second = 4893;
            t_ss._n_third = 289;
            multiset_insert(pt_msetex, &t_ss);
            t_ss._n_first = 0;
            t_ss._n_second = -878;
            t_ss._n_third = -3;
            multiset_insert(pt_msetex, &t_ss);
            multiset_insert(pt_msetex, &t_ss);
            t_ss._n_first = 53;
            t_ss._n_second = 55;
            t_ss._n_third = 122;
            multiset_insert(pt_msetex, &t_ss);
            multiset_insert(pt_msetex, &t_ss);
            multiset_init_copy(pt_mset, pt_msetex);
            _print_multiset_user(pt_mset);
            multiset_destroy(pt_mset);
            multiset_destroy(pt_msetex);
        }
        /*multiset_init_copy_range   */
        {
            multiset_t* pt_mset = create_multiset(setsample_t);
            multiset_t* pt_msetex = create_multiset(multisetsample_t);
            setsample_t t_ss;
            if(pt_mset == NULL || pt_msetex == NULL)
            {
                return;
            }
            multiset_init_ex(pt_msetex, _setsample_great);
            t_ss._n_first = 34;
            t_ss._n_second = 4893;
            t_ss._n_third = 289;
            multiset_insert(pt_msetex, &t_ss);
            t_ss._n_first = 0;
            t_ss._n_second = -878;
            t_ss._n_third = -3;
            multiset_insert(pt_msetex, &t_ss);
            multiset_insert(pt_msetex, &t_ss);
            t_ss._n_first = 53;
            t_ss._n_second = 55;
            t_ss._n_third = 122;
            multiset_insert(pt_msetex, &t_ss);
            multiset_insert(pt_msetex, &t_ss);
            _print_multiset_user(pt_msetex);
            multiset_init_copy_range(pt_mset, multiset_begin(pt_msetex),
                multiset_end(pt_msetex));
            _print_multiset_user(pt_mset);
            multiset_destroy(pt_mset);
            multiset_destroy(pt_msetex);
        }
        /*multiset_init_copy_range_ex*/
        {
            multiset_t* pt_mset = create_multiset(setsample_t);
            multiset_t* pt_msetex = create_multiset(multisetsample_t);
            setsample_t t_ss;
            if(pt_mset == NULL || pt_msetex == NULL)
            {
                return;
            }
            multiset_init(pt_msetex);
            t_ss._n_first = 34;
            t_ss._n_second = 4893;
            t_ss._n_third = 289;
            multiset_insert(pt_msetex, &t_ss);
            t_ss._n_first = 0;
            t_ss._n_second = -878;
            t_ss._n_third = -3;
            multiset_insert(pt_msetex, &t_ss);
            multiset_insert(pt_msetex, &t_ss);
            t_ss._n_first = 53;
            t_ss._n_second = 55;
            t_ss._n_third = 122;
            multiset_insert(pt_msetex, &t_ss);
            multiset_insert(pt_msetex, &t_ss);
            _print_multiset_user(pt_msetex);
            multiset_init_copy_range_ex(pt_mset, multiset_begin(pt_msetex),
                multiset_end(pt_msetex), _setsample_great);
            _print_multiset_user(pt_mset);
            multiset_destroy(pt_mset);
            multiset_destroy(pt_msetex);
        }
        /*multiset_destroy           */
        /*multiset_assign            */
        {
            multiset_t* pt_mset = create_multiset(setsample_t);
            multiset_t* pt_msetex = create_multiset(multisetsample_t);
            setsample_t t_ss;
            if(pt_mset == NULL || pt_msetex == NULL)
            {
                return;
            }
            multiset_init_ex(pt_msetex, _setsample_great);
            multiset_init_ex(pt_mset, _setsample_great);
            t_ss._n_first = 34;
            t_ss._n_second = 4893;
            t_ss._n_third = 289;
            multiset_insert(pt_msetex, &t_ss);
            t_ss._n_first = 0;
            t_ss._n_second = -878;
            t_ss._n_third = -3;
            multiset_insert(pt_msetex, &t_ss);
            multiset_insert(pt_msetex, &t_ss);
            t_ss._n_first = 53;
            t_ss._n_second = 55;
            t_ss._n_third = 122;
            multiset_insert(pt_msetex, &t_ss);
            multiset_insert(pt_msetex, &t_ss);
            _print_multiset_user(pt_msetex);
            multiset_assign(pt_mset, pt_msetex);
            _print_multiset_user(pt_mset);
            multiset_destroy(pt_mset);
            multiset_destroy(pt_msetex);
        }
        /*multiset_size              */
        /*multiset_empty             */
        /*multiset_max_size          */
        /*multiset_begin             */
        /*multiset_end               */
        /*multiset_key_less          */
        /*multiset_value_less        */
        {
            multiset_t* pt_mset = create_multiset(multisetsample_t);
            if(pt_mset == NULL)
            {
                return;
            }
            multiset_init(pt_mset);
            assert(multiset_key_less(pt_mset) == _setsample_less &&
                   multiset_value_less(pt_mset) == _setsample_less);
            multiset_destroy(pt_mset);
        }
        /*multiset_clear             */
        {
            multiset_t* pt_mset = create_multiset(multisetsample_t);
            setsample_t t_ss;
            if(pt_mset == NULL)
            {
                return;
            }
            multiset_init(pt_mset);
            multiset_clear(pt_mset);
            _print_multiset_user(pt_mset);
            t_ss._n_first = 34;
            t_ss._n_second = 4893;
            t_ss._n_third = 289;
            multiset_insert(pt_mset, &t_ss);
            t_ss._n_first = 0;
            t_ss._n_second = -878;
            t_ss._n_third = -3;
            multiset_insert(pt_mset, &t_ss);
            multiset_insert(pt_mset, &t_ss);
            t_ss._n_first = 53;
            t_ss._n_second = 55;
            t_ss._n_third = 122;
            multiset_insert(pt_mset, &t_ss);
            multiset_insert(pt_mset, &t_ss);
            _print_multiset_user(pt_mset);
            multiset_clear(pt_mset);
            _print_multiset_user(pt_mset);
            multiset_destroy(pt_mset);
        }
        /*multiset_equal             */
        /*multiset_not_equal         */
        /*multiset_less              */
        /*multiset_less_equal        */
        /*multiset_great             */
        /*multiset_great_equal       */
        {
            multiset_t* pt_mset = create_multiset(setsample_t);
            multiset_t* pt_msetex = create_multiset(multisetsample_t);
            multisetsample_t t_mss;
            if(pt_mset == NULL || pt_msetex == NULL)
            {
                return;
            }
            multiset_init(pt_mset);
            multiset_init(pt_msetex);
            _print_multiset_user(pt_mset);
            _print_multiset_user(pt_msetex);
            printf("equal: %d, not equal: %d, ",
                multiset_equal(pt_mset, pt_msetex), multiset_not_equal(pt_mset, pt_msetex));
            printf("less: %d, less equal: %d, ",
                multiset_less(pt_mset, pt_msetex), multiset_less_equal(pt_mset, pt_msetex));
            printf("great: %d, great equal: %d\n",
                multiset_great(pt_mset, pt_msetex), multiset_great_equal(pt_mset, pt_msetex));
            t_mss._n_first = 43;
            t_mss._n_second = 556;
            t_mss._n_third = 556;
            multiset_insert(pt_mset, &t_mss);
            _print_multiset_user(pt_mset);
            _print_multiset_user(pt_msetex);
            printf("equal: %d, not equal: %d, ",
                multiset_equal(pt_mset, pt_msetex), multiset_not_equal(pt_mset, pt_msetex));
            printf("less: %d, less equal: %d, ",
                multiset_less(pt_mset, pt_msetex), multiset_less_equal(pt_mset, pt_msetex));
            printf("great: %d, great equal: %d\n",
                multiset_great(pt_mset, pt_msetex), multiset_great_equal(pt_mset, pt_msetex));
            multiset_insert(pt_msetex, &t_mss);
            _print_multiset_user(pt_mset);
            _print_multiset_user(pt_msetex);
            printf("equal: %d, not equal: %d, ",
                multiset_equal(pt_mset, pt_msetex), multiset_not_equal(pt_mset, pt_msetex));
            printf("less: %d, less equal: %d, ",
                multiset_less(pt_mset, pt_msetex), multiset_less_equal(pt_mset, pt_msetex));
            printf("great: %d, great equal: %d\n",
                multiset_great(pt_mset, pt_msetex), multiset_great_equal(pt_mset, pt_msetex));

            t_mss._n_first = 43;
            t_mss._n_second = 6;
            t_mss._n_third = 596;
            multiset_insert(pt_mset, &t_mss);
            t_mss._n_first = 43;
            t_mss._n_second = 98456;
            t_mss._n_third = 596;
            multiset_insert(pt_mset, &t_mss);
            t_mss._n_first = 4300;
            t_mss._n_second = 8056;
            t_mss._n_third = 506;
            multiset_insert(pt_msetex, &t_mss);
            _print_multiset_user(pt_mset);
            _print_multiset_user(pt_msetex);
            printf("equal: %d, not equal: %d, ",
                multiset_equal(pt_mset, pt_msetex), multiset_not_equal(pt_mset, pt_msetex));
            printf("less: %d, less equal: %d, ",
                multiset_less(pt_mset, pt_msetex), multiset_less_equal(pt_mset, pt_msetex));
            printf("great: %d, great equal: %d\n",
                multiset_great(pt_mset, pt_msetex), multiset_great_equal(pt_mset, pt_msetex));

            multiset_destroy(pt_mset);
            multiset_destroy(pt_msetex);
        }
        /*multiset_swap              */
        {
            multiset_t* pt_mset = create_multiset(setsample_t);
            multiset_t* pt_msetex = create_multiset(multisetsample_t);
            multisetsample_t t_mss;
            if(pt_mset == NULL || pt_msetex == NULL)
            {
                return;
            }
            multiset_init(pt_mset);
            multiset_init(pt_msetex);
            multiset_swap(pt_mset, pt_msetex);
            _print_multiset_user(pt_mset);
            _print_multiset_user(pt_msetex);

            t_mss._n_first = 43;
            t_mss._n_second = 556;
            t_mss._n_third = 556;
            multiset_insert(pt_msetex, &t_mss);
            t_mss._n_first = -3;
            t_mss._n_second = 956;
            t_mss._n_third = -56;
            multiset_insert(pt_msetex, &t_mss);
            multiset_swap(pt_mset, pt_msetex);
            _print_multiset_user(pt_mset);
            _print_multiset_user(pt_msetex);


            t_mss._n_first = 43;
            t_mss._n_second = 6;
            t_mss._n_third = 596;
            multiset_insert(pt_msetex, &t_mss);
            t_mss._n_first = 43;
            t_mss._n_second = 98456;
            t_mss._n_third = 596;
            multiset_insert(pt_msetex, &t_mss);
            t_mss._n_first = 4300;
            t_mss._n_second = 8056;
            t_mss._n_third = 506;
            multiset_insert(pt_msetex, &t_mss);
            multiset_swap(pt_mset, pt_msetex);
            _print_multiset_user(pt_mset);
            _print_multiset_user(pt_msetex);

            multiset_clear(pt_msetex);
            multiset_swap(pt_mset, pt_msetex);
            _print_multiset_user(pt_mset);
            _print_multiset_user(pt_msetex);

            multiset_destroy(pt_mset);
            multiset_destroy(pt_msetex);
        }
        /*multiset_find              */
        /*multiset_count             */
        {
            multiset_t* pt_mset = create_multiset(multisetsample_t);
            iterator_t t_iter;
            multisetsample_t t_mss;
            if(pt_mset == NULL)
            {
                return;
            }
            multiset_init(pt_mset);
            t_iter = multiset_find(pt_mset, &t_mss);
            if(!iterator_equal(t_iter, multiset_end(pt_mset)))
            {
                printf("<%d, %d, %d>, count : %d\n",
                    ((setsample_t*)iterator_get_pointer(t_iter))->_n_first,
                    ((setsample_t*)iterator_get_pointer(t_iter))->_n_second,
                    ((setsample_t*)iterator_get_pointer(t_iter))->_n_third,
                    multiset_count(pt_mset, &t_mss));
            }
            else
            {
                printf("not found, count : %d\n", multiset_count(pt_mset, &t_mss));
            }
            t_mss._n_first = 43;
            t_mss._n_second = 556;
            t_mss._n_third = 556;
            multiset_insert(pt_mset, &t_mss);
            t_mss._n_first = -3;
            t_mss._n_second = 956;
            t_mss._n_third = -56;
            multiset_insert(pt_mset, &t_mss);
            t_mss._n_first = 43;
            t_mss._n_second = 6;
            t_mss._n_third = 596;
            multiset_insert(pt_mset, &t_mss);
            t_mss._n_first = 43;
            t_mss._n_second = 98456;
            t_mss._n_third = 596;
            multiset_insert(pt_mset, &t_mss);
            multiset_insert(pt_mset, &t_mss);
            multiset_insert(pt_mset, &t_mss);
            multiset_insert(pt_mset, &t_mss);
            t_mss._n_first = 4300;
            t_mss._n_second = 8056;
            t_mss._n_third = 506;
            multiset_insert(pt_mset, &t_mss);
            _print_multiset_user(pt_mset);
            t_mss._n_first = 843;
            t_mss._n_second = 4;
            t_mss._n_third = 223;
            t_iter = multiset_find(pt_mset, &t_mss);
            if(!iterator_equal(t_iter, multiset_end(pt_mset)))
            {
                printf("<%d, %d, %d>, count : %d\n",
                    ((setsample_t*)iterator_get_pointer(t_iter))->_n_first,
                    ((setsample_t*)iterator_get_pointer(t_iter))->_n_second,
                    ((setsample_t*)iterator_get_pointer(t_iter))->_n_third,
                    multiset_count(pt_mset, &t_mss));
            }
            else
            {
                printf("not found, count : %d\n", multiset_count(pt_mset, &t_mss));
            }

            t_mss._n_first = 43;
            t_mss._n_second = 98456;
            t_mss._n_third = 596;
            t_iter = multiset_find(pt_mset, &t_mss);
            if(!iterator_equal(t_iter, multiset_end(pt_mset)))
            {
                printf("<%d, %d, %d>, count : %d\n",
                    ((setsample_t*)iterator_get_pointer(t_iter))->_n_first,
                    ((setsample_t*)iterator_get_pointer(t_iter))->_n_second,
                    ((setsample_t*)iterator_get_pointer(t_iter))->_n_third,
                    multiset_count(pt_mset, &t_mss));
            }
            else
            {
                printf("not found, count : %d\n", multiset_count(pt_mset, &t_mss));
            }
            multiset_destroy(pt_mset);
        }
        /*multiset_lower_bound       */
        /*multiset_upper_bound       */
        /*multiset_equal_range       */
        {
            multiset_t* pt_mset = create_multiset(multisetsample_t);
            iterator_t t_begin;
            iterator_t t_end;
            iterator_t t_iter;
            range_t    t_range;
            multisetsample_t t_mss;
            if(pt_mset == NULL)
            {
                return;
            }
            multiset_init(pt_mset);
            t_begin = multiset_lower_bound(pt_mset, &t_mss);
            t_end = multiset_upper_bound(pt_mset, &t_mss);
            t_range = multiset_equal_range(pt_mset, &t_mss);
            assert(iterator_equal(t_begin, multiset_end(pt_mset)) &&
                   iterator_equal(t_begin, t_end) &&
                   iterator_equal(t_begin, t_range.t_begin) &&
                   iterator_equal(t_end, t_range.t_end));
            t_mss._n_first = 43;
            t_mss._n_second = 556;
            t_mss._n_third = 556;
            multiset_insert(pt_mset, &t_mss);
            t_mss._n_first = -3;
            t_mss._n_second = 956;
            t_mss._n_third = -56;
            multiset_insert(pt_mset, &t_mss);
            t_mss._n_first = 43;
            t_mss._n_second = 6;
            t_mss._n_third = 596;
            multiset_insert(pt_mset, &t_mss);
            t_mss._n_first = 43;
            t_mss._n_second = 98456;
            t_mss._n_third = 596;
            multiset_insert(pt_mset, &t_mss);
            multiset_insert(pt_mset, &t_mss);
            multiset_insert(pt_mset, &t_mss);
            multiset_insert(pt_mset, &t_mss);
            t_mss._n_first = 4300;
            t_mss._n_second = 8056;
            t_mss._n_third = 506;
            multiset_insert(pt_mset, &t_mss);
            t_mss._n_first = 43;
            t_mss._n_second = 100;
            t_mss._n_third = 45;
            t_begin = multiset_lower_bound(pt_mset, &t_mss);
            t_end = multiset_upper_bound(pt_mset, &t_mss);
            t_range = multiset_equal_range(pt_mset, &t_mss);
            t_iter = multiset_lower_bound(pt_mset, &t_mss);
            assert(iterator_equal(t_begin, t_iter) &&
                   iterator_equal(t_end, t_iter) &&
                   iterator_equal(t_range.t_begin, t_iter) &&
                   iterator_equal(t_range.t_end, t_iter));
            t_mss._n_first = 43;
            t_mss._n_second = 98456;
            t_mss._n_third = 596;
            t_begin = multiset_lower_bound(pt_mset, &t_mss);
            t_end = multiset_upper_bound(pt_mset, &t_mss);
            t_range = multiset_equal_range(pt_mset, &t_mss);
            assert(iterator_equal(iterator_advance(t_begin, 4), t_end) &&
                   iterator_equal(t_begin, t_range.t_begin) &&
                   iterator_equal(t_end, t_range.t_end));
            multiset_destroy(pt_mset);
        }
        /*multiset_insert            */
        {
            multiset_t* pt_mset = create_multiset(setsample_t);
            multisetsample_t t_mss;
            if(pt_mset == NULL)
            {
                return;
            }
            multiset_init(pt_mset);
            _print_multiset_user(pt_mset);
            t_mss._n_first = 4345;
            t_mss._n_second = 5;
            t_mss._n_third = -784;
            multiset_insert(pt_mset, &t_mss);
            t_mss._n_first = -9784;
            t_mss._n_second = 223;
            t_mss._n_third = 9;
            multiset_insert(pt_mset, &t_mss);
            t_mss._n_first = 0;
            t_mss._n_second = 234;
            t_mss._n_third = 2;
            multiset_insert(pt_mset, &t_mss);
            multiset_insert(pt_mset, &t_mss);
            _print_multiset_user(pt_mset);
            multiset_destroy(pt_mset);
        }
        /*multiset_insert_hint       */
        {
            multiset_t* pt_mset = create_multiset(setsample_t);
            iterator_t t_iter;
            multisetsample_t t_mss;
            if(pt_mset == NULL)
            {
                return;
            }
            multiset_init(pt_mset);
            t_iter = multiset_begin(pt_mset);
            _print_multiset_user(pt_mset);
            t_mss._n_first = 4345;
            t_mss._n_second = 5;
            t_mss._n_third = -784;
            multiset_insert_hint(pt_mset, t_iter, &t_mss);
            t_mss._n_first = -9784;
            t_mss._n_second = 223;
            t_mss._n_third = 9;
            multiset_insert_hint(pt_mset, t_iter, &t_mss);
            t_mss._n_first = 0;
            t_mss._n_second = 234;
            t_mss._n_third = 2;
            multiset_insert_hint(pt_mset, t_iter, &t_mss);
            multiset_insert_hint(pt_mset, t_iter, &t_mss);
            _print_multiset_user(pt_mset);
            multiset_destroy(pt_mset);
        }
        /*multiset_insert_range      */
        {
            multiset_t* pt_mset = create_multiset(setsample_t);
            multiset_t* pt_msetex = create_multiset(setsample_t);
            multisetsample_t t_mss;
            if(pt_mset == NULL || pt_msetex == NULL)
            {
                return;
            }
            multiset_init_ex(pt_mset, _setsample_great);
            multiset_init(pt_msetex);
            multiset_insert_range(pt_mset, multiset_begin(pt_msetex), multiset_end(pt_msetex));
            _print_multiset_user(pt_mset);
            t_mss._n_first = 43;
            t_mss._n_second = 556;
            t_mss._n_third = 556;
            multiset_insert(pt_msetex, &t_mss);
            t_mss._n_first = -3;
            t_mss._n_second = 956;
            t_mss._n_third = -56;
            multiset_insert(pt_msetex, &t_mss);
            t_mss._n_first = 43;
            t_mss._n_second = 6;
            t_mss._n_third = 596;
            multiset_insert(pt_msetex, &t_mss);
            t_mss._n_first = 43;
            t_mss._n_second = 98456;
            t_mss._n_third = 596;
            multiset_insert(pt_msetex, &t_mss);
            multiset_insert(pt_msetex, &t_mss);
            multiset_insert(pt_msetex, &t_mss);
            multiset_insert(pt_msetex, &t_mss);
            t_mss._n_first = 4300;
            t_mss._n_second = 8056;
            t_mss._n_third = 506;
            multiset_insert(pt_msetex, &t_mss);
            t_mss._n_first = 43;
            t_mss._n_second = 100;
            t_mss._n_third = 45;
            multiset_insert(pt_msetex, &t_mss);
            _print_multiset_user(pt_msetex);
            multiset_insert_range(pt_mset, multiset_begin(pt_msetex),
                multiset_begin(pt_msetex));
            _print_multiset_user(pt_mset);
            multiset_insert_range(pt_mset, multiset_begin(pt_msetex),
                iterator_advance(multiset_begin(pt_msetex), 2));
            _print_multiset_user(pt_mset);
            multiset_insert_range(pt_mset, iterator_advance(multiset_begin(pt_msetex), 4),
                iterator_advance(multiset_begin(pt_msetex), 6));
            _print_multiset_user(pt_mset);
            multiset_insert_range(pt_mset, iterator_advance(multiset_begin(pt_msetex), 5),
                multiset_end(pt_msetex));
            _print_multiset_user(pt_mset);
            multiset_clear(pt_mset);
            multiset_insert_range(pt_mset, multiset_begin(pt_msetex), multiset_end(pt_msetex));
            _print_multiset_user(pt_mset);
            multiset_destroy(pt_mset);
            multiset_destroy(pt_msetex);
        }
        /*multiset_erase             */
        {
            multiset_t* pt_mset = create_multiset(setsample_t);
            multisetsample_t t_mss;
            if(pt_mset == NULL)
            {
                return;
            }
            multiset_init(pt_mset);
            multiset_erase(pt_mset, &t_mss);
            _print_multiset_user(pt_mset);
            t_mss._n_first = 43;
            t_mss._n_second = 556;
            t_mss._n_third = 556;
            multiset_insert(pt_mset, &t_mss);
            t_mss._n_first = -3;
            t_mss._n_second = 956;
            t_mss._n_third = -56;
            multiset_insert(pt_mset, &t_mss);
            t_mss._n_first = 43;
            t_mss._n_second = 6;
            t_mss._n_third = 596;
            multiset_insert(pt_mset, &t_mss);
            t_mss._n_first = 43;
            t_mss._n_second = 98456;
            t_mss._n_third = 596;
            multiset_insert(pt_mset, &t_mss);
            multiset_insert(pt_mset, &t_mss);
            multiset_insert(pt_mset, &t_mss);
            multiset_insert(pt_mset, &t_mss);
            t_mss._n_first = 4300;
            t_mss._n_second = 8056;
            t_mss._n_third = 506;
            multiset_insert(pt_mset, &t_mss);
            t_mss._n_first = 43;
            t_mss._n_second = 100;
            t_mss._n_third = 45;
            multiset_insert(pt_mset, &t_mss);
            _print_multiset_user(pt_mset);
            t_mss._n_first = 0;
            t_mss._n_second = 0;
            t_mss._n_third = 0;
            multiset_erase(pt_mset, &t_mss);
            _print_multiset_user(pt_mset);
            t_mss._n_first = 43;
            t_mss._n_second = 6;
            t_mss._n_third = 596;
            multiset_erase(pt_mset, &t_mss);
            _print_multiset_user(pt_mset);
            multiset_destroy(pt_mset);
        }
        /*multiset_erase_pos         */
        {
            multiset_t* pt_mset = create_multiset(setsample_t);
            multisetsample_t t_mss;
            if(pt_mset == NULL)
            {
                return;
            }
            multiset_init_ex(pt_mset, _setsample_great);
            _print_multiset_user(pt_mset);
            t_mss._n_first = 43;
            t_mss._n_second = 556;
            t_mss._n_third = 556;
            multiset_insert(pt_mset, &t_mss);
            t_mss._n_first = -3;
            t_mss._n_second = 956;
            t_mss._n_third = -56;
            multiset_insert(pt_mset, &t_mss);
            t_mss._n_first = 43;
            t_mss._n_second = 6;
            t_mss._n_third = 596;
            multiset_insert(pt_mset, &t_mss);
            t_mss._n_first = 43;
            t_mss._n_second = 98456;
            t_mss._n_third = 596;
            multiset_insert(pt_mset, &t_mss);
            multiset_insert(pt_mset, &t_mss);
            multiset_insert(pt_mset, &t_mss);
            multiset_insert(pt_mset, &t_mss);
            t_mss._n_first = 4300;
            t_mss._n_second = 8056;
            t_mss._n_third = 506;
            multiset_insert(pt_mset, &t_mss);
            t_mss._n_first = 43;
            t_mss._n_second = 100;
            t_mss._n_third = 45;
            multiset_insert(pt_mset, &t_mss);
            _print_multiset_user(pt_mset);

            multiset_erase_pos(pt_mset, multiset_begin(pt_mset));
            _print_multiset_user(pt_mset);
            multiset_erase_pos(pt_mset, iterator_prev(multiset_end(pt_mset)));
            _print_multiset_user(pt_mset);
            multiset_erase_pos(pt_mset, iterator_advance(multiset_begin(pt_mset), 4));
            _print_multiset_user(pt_mset);
            while(!multiset_empty(pt_mset))
            {
                multiset_erase_pos(pt_mset, multiset_begin(pt_mset));
            }
            _print_multiset_user(pt_mset);
            multiset_destroy(pt_mset);
        }
        /*multiset_erase_range       */
        {
            multiset_t* pt_mset = create_multiset(setsample_t);
            multisetsample_t t_mss;
            if(pt_mset == NULL)
            {
                return;
            }
            multiset_init_ex(pt_mset, _setsample_great);
            multiset_erase_range(pt_mset, multiset_begin(pt_mset), multiset_end(pt_mset));
            _print_multiset_user(pt_mset);
            _print_multiset_user(pt_mset);
            t_mss._n_first = 43;
            t_mss._n_second = 556;
            t_mss._n_third = 556;
            multiset_insert(pt_mset, &t_mss);
            t_mss._n_first = -3;
            t_mss._n_second = 956;
            t_mss._n_third = -56;
            multiset_insert(pt_mset, &t_mss);
            t_mss._n_first = 43;
            t_mss._n_second = 6;
            t_mss._n_third = 596;
            multiset_insert(pt_mset, &t_mss);
            t_mss._n_first = 43;
            t_mss._n_second = 98456;
            t_mss._n_third = 596;
            multiset_insert(pt_mset, &t_mss);
            multiset_insert(pt_mset, &t_mss);
            multiset_insert(pt_mset, &t_mss);
            multiset_insert(pt_mset, &t_mss);
            t_mss._n_first = 4300;
            t_mss._n_second = 8056;
            t_mss._n_third = 506;
            multiset_insert(pt_mset, &t_mss);
            t_mss._n_first = 43;
            t_mss._n_second = 100;
            t_mss._n_third = 45;
            multiset_insert(pt_mset, &t_mss);
            _print_multiset_user(pt_mset);

            multiset_erase_range(pt_mset, multiset_begin(pt_mset), multiset_begin(pt_mset));
            _print_multiset_user(pt_mset);
            multiset_erase_range(pt_mset, multiset_begin(pt_mset),
                iterator_advance(multiset_begin(pt_mset), 2));
            _print_multiset_user(pt_mset);
            multiset_erase_range(pt_mset, iterator_next(multiset_begin(pt_mset)),
                iterator_advance(multiset_begin(pt_mset), 3));
            _print_multiset_user(pt_mset);
            multiset_erase_range(pt_mset, iterator_advance(multiset_begin(pt_mset), 3),
                multiset_end(pt_mset));
            _print_multiset_user(pt_mset);
            multiset_erase_range(pt_mset, multiset_end(pt_mset), multiset_end(pt_mset));
            _print_multiset_user(pt_mset);
            multiset_erase_range(pt_mset, multiset_begin(pt_mset), multiset_end(pt_mset));
            _print_multiset_user(pt_mset);
            multiset_destroy(pt_mset);
        }
    }
    /* cstl built-in type */
    {
        /*create_multiset            */
        {
            multiset_t* pt_mset = create_multiset(multiset_t<int>);
            multiset_t* pt_msetex = create_multiset(int);
            if(pt_mset == NULL)
            {
                return;
            }
            multiset_init(pt_mset);
            multiset_init(pt_msetex);
            multiset_insert(pt_msetex, 23499);
            multiset_insert(pt_msetex, -38);
            multiset_insert(pt_msetex, 930);
            multiset_insert(pt_msetex, 234);
            multiset_insert(pt_mset, pt_msetex);
            multiset_clear(pt_msetex);
            multiset_insert(pt_msetex, 49);
            multiset_insert(pt_msetex, -455);
            multiset_insert(pt_msetex, 23);
            multiset_insert(pt_mset, pt_msetex);
            _print_multiset_multiset(pt_mset);
            multiset_destroy(pt_mset);
            multiset_destroy(pt_msetex);
        }
        /*multiset_init              */
        /*multiset_init_ex           */
        {
            multiset_t* pt_mset = create_multiset(multiset_t<int>);
            multiset_t* pt_msetex = create_multiset(int);
            if(pt_mset == NULL)
            {
                return;
            }
            multiset_init_ex(pt_mset, fun_great_multiset);
            multiset_init(pt_msetex);
            multiset_insert(pt_msetex, 23499);
            multiset_insert(pt_msetex, -38);
            multiset_insert(pt_msetex, 930);
            multiset_insert(pt_msetex, 234);
            multiset_insert(pt_mset, pt_msetex);
            multiset_clear(pt_msetex);
            multiset_insert(pt_msetex, 49);
            multiset_insert(pt_msetex, -455);
            multiset_insert(pt_msetex, 23);
            multiset_insert(pt_mset, pt_msetex);
            _print_multiset_multiset(pt_mset);
            multiset_destroy(pt_mset);
            multiset_destroy(pt_msetex);
        }
        /*multiset_init_copy         */
        {
            multiset_t* pt_mset1 = create_multiset(multiset_t<int>);
            multiset_t* pt_mset2 = create_multiset(multiset_t<int>);
            multiset_t* pt_msetex = create_multiset(int);
            if(pt_mset1 == NULL || pt_mset2 == NULL || pt_msetex == NULL)
            {
                return;
            }
            multiset_init(pt_msetex);
            multiset_init_ex(pt_mset2, fun_great_multiset);
            multiset_insert(pt_msetex, 23499);
            multiset_insert(pt_msetex, -38);
            multiset_insert(pt_msetex, 930);
            multiset_insert(pt_msetex, 234);
            multiset_insert(pt_mset2, pt_msetex);
            multiset_clear(pt_msetex);
            multiset_insert(pt_msetex, 49);
            multiset_insert(pt_msetex, -455);
            multiset_insert(pt_msetex, 23);
            multiset_insert(pt_mset2, pt_msetex);
            multiset_clear(pt_msetex);
            multiset_insert(pt_msetex, 7894);
            multiset_insert(pt_msetex, -87);
            multiset_insert(pt_msetex, 23);
            multiset_insert(pt_msetex, 111);
            multiset_insert(pt_mset2, pt_msetex);
            multiset_init_copy(pt_mset1, pt_mset2);
            _print_multiset_multiset(pt_mset1);
            multiset_destroy(pt_mset1);
            multiset_destroy(pt_mset2);
            multiset_destroy(pt_msetex);
        }
        /*multiset_init_copy_range   */
        {
            multiset_t* pt_mset1 = create_multiset(multiset_t<int>);
            multiset_t* pt_mset2 = create_multiset(multiset_t<int>);
            multiset_t* pt_msetex = create_multiset(int);
            if(pt_mset1 == NULL || pt_mset2 == NULL || pt_msetex == NULL)
            {
                return;
            }
            multiset_init(pt_msetex);
            multiset_init_ex(pt_mset2, fun_great_multiset);
            multiset_insert(pt_msetex, 23499);
            multiset_insert(pt_msetex, -38);
            multiset_insert(pt_msetex, 930);
            multiset_insert(pt_msetex, 234);
            multiset_insert(pt_mset2, pt_msetex);
            multiset_clear(pt_msetex);
            multiset_insert(pt_msetex, 49);
            multiset_insert(pt_msetex, -455);
            multiset_insert(pt_msetex, 23);
            multiset_insert(pt_mset2, pt_msetex);
            multiset_clear(pt_msetex);
            multiset_insert(pt_msetex, 7894);
            multiset_insert(pt_msetex, -87);
            multiset_insert(pt_msetex, 23);
            multiset_insert(pt_msetex, 111);
            multiset_insert(pt_mset2, pt_msetex);
            multiset_clear(pt_msetex);
            multiset_insert(pt_msetex, -84);
            multiset_insert(pt_msetex, -87);
            multiset_insert(pt_msetex, -11);
            multiset_insert(pt_mset2, pt_msetex);
            multiset_clear(pt_msetex);
            multiset_insert(pt_msetex, 7894);
            multiset_insert(pt_msetex, 987);
            multiset_insert(pt_msetex, 23);
            multiset_insert(pt_msetex, 111);
            multiset_insert(pt_msetex, 11);
            multiset_insert(pt_msetex, 11);
            multiset_insert(pt_msetex, 11);
            multiset_insert(pt_mset2, pt_msetex);
            multiset_clear(pt_msetex);
            multiset_insert(pt_msetex, 7894);
            multiset_insert(pt_msetex, 111);
            multiset_insert(pt_mset2, pt_msetex);
            multiset_clear(pt_msetex);
            multiset_insert(pt_msetex, 7894);
            multiset_insert(pt_msetex, 111);
            multiset_insert(pt_mset2, pt_msetex);
            _print_multiset_multiset(pt_mset2);
            multiset_init_copy_range(pt_mset1,
                multiset_begin(pt_mset2), multiset_end(pt_mset2));
            _print_multiset_multiset(pt_mset1);
            multiset_destroy(pt_mset1);
            multiset_destroy(pt_mset2);
            multiset_destroy(pt_msetex);
        }
        /*multiset_init_copy_range_ex*/
        {
            multiset_t* pt_mset1 = create_multiset(multiset_t<int>);
            multiset_t* pt_mset2 = create_multiset(multiset_t<int>);
            multiset_t* pt_msetex = create_multiset(int);
            if(pt_mset1 == NULL || pt_mset2 == NULL || pt_msetex == NULL)
            {
                return;
            }
            multiset_init(pt_msetex);
            multiset_init(pt_mset2);
            multiset_insert(pt_msetex, 23499);
            multiset_insert(pt_msetex, -38);
            multiset_insert(pt_msetex, 930);
            multiset_insert(pt_msetex, 234);
            multiset_insert(pt_mset2, pt_msetex);
            multiset_clear(pt_msetex);
            multiset_insert(pt_msetex, 49);
            multiset_insert(pt_msetex, -455);
            multiset_insert(pt_msetex, 23);
            multiset_insert(pt_mset2, pt_msetex);
            multiset_clear(pt_msetex);
            multiset_insert(pt_msetex, 7894);
            multiset_insert(pt_msetex, -87);
            multiset_insert(pt_msetex, 23);
            multiset_insert(pt_msetex, 111);
            multiset_insert(pt_mset2, pt_msetex);
            multiset_clear(pt_msetex);
            multiset_insert(pt_msetex, -84);
            multiset_insert(pt_msetex, -87);
            multiset_insert(pt_msetex, -11);
            multiset_insert(pt_mset2, pt_msetex);
            multiset_clear(pt_msetex);
            multiset_insert(pt_msetex, 7894);
            multiset_insert(pt_msetex, 987);
            multiset_insert(pt_msetex, 23);
            multiset_insert(pt_msetex, 111);
            multiset_insert(pt_msetex, 11);
            multiset_insert(pt_msetex, 11);
            multiset_insert(pt_msetex, 11);
            multiset_insert(pt_mset2, pt_msetex);
            multiset_clear(pt_msetex);
            multiset_insert(pt_msetex, 7894);
            multiset_insert(pt_msetex, 111);
            multiset_insert(pt_mset2, pt_msetex);
            multiset_clear(pt_msetex);
            multiset_insert(pt_msetex, 7894);
            multiset_insert(pt_msetex, 111);
            multiset_insert(pt_mset2, pt_msetex);
            _print_multiset_multiset(pt_mset2);
            multiset_init_copy_range_ex(pt_mset1,
                multiset_begin(pt_mset2), multiset_end(pt_mset2), fun_great_multiset);
            _print_multiset_multiset(pt_mset1);
            multiset_destroy(pt_mset1);
            multiset_destroy(pt_mset2);
            multiset_destroy(pt_msetex);
        }
        /*multiset_destroy           */
        /*multiset_assign            */
        /*multiset_size              */
        /*multiset_empty             */
        /*multiset_max_size          */
        /*multiset_begin             */
        /*multiset_end               */
        /*multiset_key_less          */
        /*multiset_value_less        */
        /*multiset_clear             */
        /*multiset_equal             */
        /*multiset_not_equal         */
        /*multiset_less              */
        /*multiset_less_equal        */
        /*multiset_great             */
        /*multiset_great_equal       */
        /*multiset_swap              */
        /*_multiset_find             */
        /*_multiset_count            */
        /*_multiset_lower_bound      */
        /*_multiset_upper_bound      */
        /*_multiset_equal_range      */
        /*_multiset_insert           */
        /*_multiset_insert_hint      */
        /*multiset_insert_range      */
        /*_multiset_erase            */
        /*multiset_erase_pos         */
        /*multiset_erase_range       */
    }
    /* c-string type */

    /*_create_multiset           */
    /*multiset_init              */
    /*multiset_init_ex           */
    /*multiset_init_copy         */
    /*multiset_init_copy_range   */
    /*multiset_init_copy_range_ex*/
    /*multiset_destroy           */
    /*multiset_assign            */
    /*multiset_size              */
    /*multiset_empty             */
    /*multiset_max_size          */
    /*multiset_begin             */
    /*multiset_end               */
    /*multiset_key_less          */
    /*multiset_value_less        */
    /*multiset_clear             */
    /*multiset_equal             */
    /*multiset_not_equal         */
    /*multiset_less              */
    /*multiset_less_equal        */
    /*multiset_great             */
    /*multiset_great_equal       */
    /*multiset_swap              */
    /*_multiset_find             */
    /*_multiset_count            */
    /*_multiset_lower_bound      */
    /*_multiset_upper_bound      */
    /*_multiset_equal_range      */
    /*_multiset_insert           */
    /*_multiset_insert_hint      */
    /*multiset_insert_range      */
    /*_multiset_erase            */
    /*multiset_erase_pos         */
    /*multiset_erase_range       */
}

/** local function implementation section **/
static void _print_multiset_multiset(const multiset_t* cpt_mset)
{
    iterator_t t_iter;
    iterator_t t_iterex;
    assert(cpt_mset != NULL);
    printf("========================================\n");
    printf("empty: %u, size: %u, max_size: %u\n",
        multiset_empty(cpt_mset), multiset_size(cpt_mset), multiset_max_size(cpt_mset));
    for(t_iter = multiset_begin(cpt_mset);
        !iterator_equal(t_iter, multiset_end(cpt_mset));
        t_iter = iterator_next(t_iter))
    {
        for(t_iterex = multiset_begin((multiset_t*)iterator_get_pointer(t_iter));
            !iterator_equal(t_iterex, multiset_end((multiset_t*)iterator_get_pointer(t_iter)));
            t_iterex = iterator_next(t_iterex))
        {
            printf("%d, ", *(int*)iterator_get_pointer(t_iterex));
        }
        printf("\n");
    }
}

static void _print_multiset_user(const multiset_t* cpt_mset)
{
    iterator_t t_iter;
    assert(cpt_mset != NULL);

    printf("=======================================\n");
    printf("empty: %u, size: %u, max_size: %u\n",
        multiset_empty(cpt_mset), multiset_size(cpt_mset), multiset_max_size(cpt_mset));
    for(t_iter = multiset_begin(cpt_mset);
        !iterator_equal(t_iter, multiset_end(cpt_mset));
        t_iter = iterator_next(t_iter))
    {
        printf("<%d, %d, %d>, ",
            ((setsample_t*)iterator_get_pointer(t_iter))->_n_first,
            ((setsample_t*)iterator_get_pointer(t_iter))->_n_second,
            ((setsample_t*)iterator_get_pointer(t_iter))->_n_third);
    }
    printf("\n");
}

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

