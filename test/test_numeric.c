/*
 *  The implementation of numeric test.
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
#include <stdarg.h>
#include "cnumeric.h"
#include "cvector.h"
#include "cdeque.h"
#include "clist.h"
#include "cslist.h"
#include "cset.h"
#include "cmap.h"
#include "chash_set.h"
#include "chash_map.h"
#include "cstring.h"
#include "cutility.h"
#include "cfunctional.h"
#include "calgorithm.h"

#include "test_numeric.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/
typedef struct _tagabc
{
    int n_a;
    double d_b;
}abc_t;

/** local function prototype section **/
static void plus_struct(const void* cpv_first, const void* cpv_second, void* pv_output);
static void multiplies_struct(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _print(const void* cpv_input, void* pv_output);

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
void test_numeric(void)
{
    {
        abc_t t_init = {8, 8.8};
        abc_t t_output = {0, 0.0};
        abc_t t_tmp;
        vector_t t_v = create_vector(abc_t);

        vector_init(&t_v);
        t_tmp.n_a = 1;
        t_tmp.d_b = 10.01;
        vector_push_back(&t_v, t_tmp);
        t_tmp.n_a = 2;
        t_tmp.d_b = 20.02;
        vector_push_back(&t_v, t_tmp);
        t_tmp.n_a = 3;
        t_tmp.d_b = 30.03;
        vector_push_back(&t_v, t_tmp);

        algo_accumulate(
            vector_begin(&t_v), vector_end(&t_v), t_init, &t_output);
        printf("output:%d, %f\n", t_output.n_a, t_output.d_b);
        algo_accumulate_if(
            vector_begin(&t_v), vector_end(&t_v), t_init, plus_struct, &t_output);
        printf("output:%d, %f\n", t_output.n_a, t_output.d_b);
        algo_inner_product_if(
            vector_begin(&t_v), vector_end(&t_v), vector_begin(&t_v), t_init,
            plus_struct, multiplies_struct, &t_output);
        printf("output:%d, %f\n", t_output.n_a, t_output.d_b);

        vector_destroy(&t_v);
    }
    {
        list_t t_l = create_list(int);
        set_t t_l2 = create_set(int);
        int n_output = 0;

        list_init(&t_l);
        set_init(&t_l2);
        list_push_back(&t_l, 1);
        list_push_back(&t_l, 2);
        list_push_back(&t_l, 3);
        set_insert(&t_l2, 10);
        set_insert(&t_l2, 20);
        set_insert(&t_l2, 30);

        /*algo_inner_product_if(*/
        /*list_begin(&t_l), list_end(&t_l), list_begin(&t_l2), &n_init,*/
        /*fun_plus_int, fun_multiplies_int, &n_output);*/
        algo_inner_product(
            list_begin(&t_l), list_end(&t_l), set_begin(&t_l2), 10000, &n_output);
        printf("output: %d\n", n_output);
        
        list_destroy(&t_l);
        set_destroy(&t_l2);
    }
    {
        deque_t t_d = create_deque(int);
        int n_output = 0;
        deque_init(&t_d);
        deque_push_back(&t_d, 2);

        algo_power(deque_begin(&t_d), 3, &n_output);
        printf("output:%d\n", n_output);
        algo_power_if(deque_begin(&t_d), 31, fun_plus_int, &n_output);
        printf("output:%d\n", n_output);

        deque_destroy(&t_d);
    }
    {
        slist_t t_sl = create_slist(int);
        multiset_t t_ms = create_multiset(int);
        slist_iterator_t t_sli;

        slist_init(&t_sl);
        multiset_init(&t_ms);

        slist_push_front(&t_sl, 109);
        slist_push_front(&t_sl, 150);
        slist_push_front(&t_sl, 78);
        multiset_insert(&t_ms, 11);
        multiset_insert(&t_ms, 21);
        multiset_insert(&t_ms, 31);

        algo_adjacent_difference(
                slist_begin(&t_sl), slist_end(&t_sl), slist_begin(&t_sl));
        for(t_sli = slist_begin(&t_sl);
                !iterator_equal(&t_sli, slist_end(&t_sl));
                iterator_next(&t_sli))
        {
            printf("%d ", *(int*)iterator_get_pointer(&t_sli));
        }
        printf("\n");
        algo_partial_sum(
                slist_begin(&t_sl), slist_end(&t_sl), slist_begin(&t_sl));
        for(t_sli = slist_begin(&t_sl);
                !iterator_equal(&t_sli, slist_end(&t_sl));
                iterator_next(&t_sli))
        {
            printf("%d ", *(int*)iterator_get_pointer(&t_sli));
        }
        printf("\n");
        algo_adjacent_difference_if(
            multiset_begin(&t_ms), multiset_end(&t_ms), slist_begin(&t_sl), fun_minus_int);
        for(t_sli = slist_begin(&t_sl);
            !iterator_equal(&t_sli, slist_end(&t_sl));
            iterator_next(&t_sli))
        {
            printf("%d ", *(int*)iterator_get_pointer(&t_sli));
        }
        printf("\n");
        algo_partial_sum_if(
            slist_begin(&t_sl), slist_end(&t_sl), slist_begin(&t_sl), fun_plus_int);
        for(t_sli = slist_begin(&t_sl);
            !iterator_equal(&t_sli, slist_end(&t_sl));
            iterator_next(&t_sli))
        {
            printf("%d ", *(int*)iterator_get_pointer(&t_sli));
        }
        printf("\n");

        slist_destroy(&t_sl);
        multiset_destroy(&t_ms);
    }
    {
        deque_iterator_t t_iterator;
        deque_t t_d = create_deque(float);
        deque_init(&t_d);

        deque_push_back(&t_d, 3.3);
        deque_push_back(&t_d, 90.1);
        deque_push_back(&t_d, 455.554);
        deque_push_back(&t_d, 100.001);

        for(t_iterator = deque_begin(&t_d);
            !iterator_equal(&t_iterator, deque_end(&t_d));
            iterator_next(&t_iterator))
        {
            printf("%f\n", *(float*)iterator_get_pointer(&t_iterator));
        }
        algo_iota(deque_begin(&t_d), deque_rbegin(&t_d), 0.01);
        for(t_iterator = deque_begin(&t_d);
            !iterator_equal(&t_iterator, deque_end(&t_d));
            iterator_next(&t_iterator))
        {
            printf("%f\n", *(float*)iterator_get_pointer(&t_iterator));
        }

        deque_destroy(&t_d);
    }
    {
        vector_t t_v = create_vector(int);

        vector_init_n(&t_v, 10);
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        algo_iota(vector_begin(&t_v), vector_end(&t_v), 100);
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        vector_destroy(&t_v);
    }
    {
        vector_t t_v = create_vector(int);
        int i = 0;
        int n_result;

        vector_init(&t_v);
        for(i = 1; i <= 9; ++i)
        {
            vector_push_back(&t_v, i);
        }
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        algo_accumulate(vector_begin(&t_v), vector_end(&t_v), 0, &n_result);
        printf("sum: %d\n", n_result);
        algo_accumulate(vector_begin(&t_v), vector_end(&t_v), -100, &n_result);
        printf("sum: %d\n", n_result);

        algo_accumulate_if(
            vector_begin(&t_v), vector_end(&t_v), 1, fun_multiplies_int, &n_result);
        printf("product: %d\n", n_result);
        algo_accumulate_if(
            vector_begin(&t_v), vector_end(&t_v), 0, fun_multiplies_int, &n_result);
        printf("product: %d\n", n_result);

        vector_destroy(&t_v);
    }
    {
        vector_t t_v = create_vector(int);
        list_t t_l = create_list(int);
        int i = 0;
        int n_result = 0;

        vector_init(&t_v);
        list_init(&t_l);
        for(i = 1; i <= 6; ++i)
        {
            vector_push_back(&t_v, i);
            list_push_back(&t_l, i);
        }
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");
        algo_for_each(list_begin(&t_l), list_end(&t_l), _print);
        printf("\n");

        algo_inner_product(
            vector_begin(&t_v), vector_end(&t_v), list_begin(&t_l), 0, &n_result);
        printf("inner product: %d\n", n_result);
        list_reverse(&t_l);
        algo_inner_product(
            vector_begin(&t_v), vector_end(&t_v), list_begin(&t_l), 0, &n_result);
        printf("inner reverse product: %d\n", n_result);
        algo_inner_product_if(
            vector_begin(&t_v), vector_end(&t_v), vector_begin(&t_v), 
            1, fun_multiplies_int, fun_plus_int, &n_result);
        printf("product of sums: %d\n", n_result);

        vector_destroy(&t_v);
        list_destroy(&t_l);
    }
    {
        vector_t t_v = create_vector(int);
        list_t t_l = create_list(int);
        int i = 0;

        vector_init(&t_v);
        for(i = 1; i <= 6; ++i)
        {
            vector_push_back(&t_v, i);
        }
        list_init_n(&t_l, vector_size(&t_v));
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        algo_partial_sum(vector_begin(&t_v), vector_end(&t_v), list_begin(&t_l));
        algo_for_each(list_begin(&t_l), list_end(&t_l), _print);
        printf("\n");

        algo_partial_sum_if(
            vector_begin(&t_v), vector_end(&t_v), list_begin(&t_l), fun_multiplies_int);
        algo_for_each(list_begin(&t_l), list_end(&t_l), _print);
        printf("\n");

        vector_destroy(&t_v);
        list_destroy(&t_l);
    }
    {
        vector_t t_v = create_vector(int);
        list_t t_l = create_list(int);
        int i = 0;

        vector_init(&t_v);
        for(i = 1; i <= 6; ++i)
        {
            vector_push_back(&t_v, i);
        }
        list_init_n(&t_l, vector_size(&t_v));
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        algo_adjacent_difference(vector_begin(&t_v), vector_end(&t_v), list_begin(&t_l));
        algo_for_each(list_begin(&t_l), list_end(&t_l), _print);
        printf("\n");

        algo_adjacent_difference_if(
            vector_begin(&t_v), vector_end(&t_v), list_begin(&t_l), fun_plus_int);
        algo_for_each(list_begin(&t_l), list_end(&t_l), _print);
        printf("\n");

        algo_adjacent_difference_if(
            vector_begin(&t_v), vector_end(&t_v), list_begin(&t_l), fun_multiplies_int);
        algo_for_each(list_begin(&t_l), list_end(&t_l), _print);
        printf("\n");

        vector_destroy(&t_v);
        list_destroy(&t_l);
    }
    {
        deque_t t_d = create_deque(int);
        int n_output = 0;
        deque_init(&t_d);
        deque_push_back(&t_d, 2);

        algo_power(deque_begin(&t_d), 3, &n_output);
        printf("output:%d\n", n_output);
        algo_power_if(deque_begin(&t_d), 3, fun_plus_int, &n_output);
        printf("output:%d\n", n_output);

        deque_destroy(&t_d);
    }
}

/** local function implementation section **/
static void plus_struct(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    ((abc_t*)pv_output)->n_a = ((abc_t*)cpv_first)->n_a + ((abc_t*)cpv_second)->n_a;
    ((abc_t*)pv_output)->d_b = ((abc_t*)cpv_first)->d_b + ((abc_t*)cpv_second)->d_b;
}

static void multiplies_struct(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    ((abc_t*)pv_output)->n_a = ((abc_t*)cpv_first)->n_a * ((abc_t*)cpv_second)->n_a;
    ((abc_t*)pv_output)->d_b = ((abc_t*)cpv_first)->d_b * ((abc_t*)cpv_second)->d_b;
}
static void _print(const void* cpv_input, void* pv_output)
{
    pv_output = NULL;
    printf("%d, ", *(int*)cpv_input);
}

/** eof **/

