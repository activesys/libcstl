/*
 *  The implementation of base algorithm base.
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

#include "test_algobase.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
void test_algobase(void)
{
    set_t t_s = create_set(float);
    deque_t t_d = create_deque(float);
    vector_t t_v = create_vector(float);
    multiset_t t_ms = create_multiset(float);
    iterator_t t_i;
    pair_t t_p;

    set_init(&t_s);
    deque_init(&t_d);
    vector_init(&t_v);
    multiset_init(&t_ms);

    set_insert(&t_s, 20.1);
    set_insert(&t_s, 88.9);
    set_insert(&t_s, 33.34);
    deque_push_back(&t_d, 20.1);
    deque_push_back(&t_d, 33.34);
    deque_push_back(&t_d, 88.9);
    deque_push_back(&t_d, 444.44);
    vector_push_back(&t_v, -0.04);
    vector_push_back(&t_v, -23.9);
    vector_push_back(&t_v, -100.0);

    printf("equal:%d\n", 
        algo_equal(set_begin(&t_s), set_end(&t_s), deque_begin(&t_d)));
    t_i = set_begin(&t_s);
    algo_fill(deque_begin(&t_d), deque_rbegin(&t_d), 20.0);
    for(t_i = deque_begin(&t_d);
        !iterator_equal(t_i, deque_end(&t_d));
        t_i = iterator_next(t_i))
    {
        printf("%f\n", *(float*)iterator_get_pointer(t_i));
    }
    algo_fill_n(deque_begin(&t_d), 2, 99.98);
    for(t_i = deque_begin(&t_d);
        !iterator_equal(t_i, deque_end(&t_d));
        t_i = iterator_next(t_i))
    {
        printf("%f\n", *(float*)iterator_get_pointer(t_i));
    }

    algo_iter_swap(deque_begin(&t_d), vector_begin(&t_v));
    t_i = deque_begin(&t_d);
    printf("%f ", *(float*)iterator_get_pointer(t_i));
    t_i = vector_begin(&t_v);
    printf("%f\n", *(float*)iterator_get_pointer(t_i));
    for(t_i = deque_begin(&t_d);
        !iterator_equal(t_i, deque_end(&t_d));
        t_i = iterator_next(t_i))
    {
        printf("%f\n", *(float*)iterator_get_pointer(t_i));
    }

    deque_clear(&t_d);
    vector_clear(&t_v);
    deque_push_back(&t_d, 90.09);
    deque_push_back(&t_d, 0.0099);
    vector_push_back(&t_v, 90.09);
    vector_push_back(&t_v, 99999.9);
    printf("%d, %d\n",
        algo_lexicographical_compare(
            deque_begin(&t_d), deque_end(&t_d), vector_begin(&t_v), vector_end(&t_v)),
        algo_lexicographical_compare_3way_if(
            deque_begin(&t_d), deque_end(&t_d), vector_begin(&t_v), vector_end(&t_v),
            fun_less_float));

    t_i = algo_max(vector_begin(&t_v), deque_begin(&t_d));
    printf("max:%f, ", 
        *(float*)iterator_get_pointer(t_i));
    t_i = algo_min(vector_begin(&t_v), deque_begin(&t_d));
    printf("min:%f\n", 
        *(float*)iterator_get_pointer(t_i));
    if(t_i._t_containertype == _DEQUE_CONTAINER)
        printf("deque\n");
    else
        printf("vector\n");

    t_p = algo_mismatch_if(
        deque_begin(&t_d), deque_end(&t_d), vector_begin(&t_v), fun_not_equal_float);
    if(iterator_equal(*(iterator_t*)t_p.first, deque_end(&t_d)))
    {
        printf("<end, %f>\n",
            *(float*)iterator_get_pointer(*(iterator_t*)t_p.second));
    }
    else
    {
        printf("<%f, %f>\n", 
            *(float*)iterator_get_pointer(*(iterator_t*)t_p.first),
            *(float*)iterator_get_pointer(*(iterator_t*)t_p.second));
    }

    set_clear(&t_s);
    set_insert(&t_s, 89.45);
    set_insert(&t_s, -22.01);
    set_insert(&t_s, 34.0009);
    deque_clear(&t_d);
    deque_push_back(&t_d, 120.0);
    deque_push_back(&t_d, 220.0);
    deque_push_back(&t_d, 320.0);
    deque_push_back(&t_d, 420.0);
    deque_push_back(&t_d, 520.0);
    vector_clear(&t_v);
    vector_push_back(&t_v, 11.11);
    vector_push_back(&t_v, 22.22);
    vector_push_back(&t_v, 33.33);
    vector_push_back(&t_v, 44.44);
    vector_push_back(&t_v, 55.55);
    vector_push_back(&t_v, 66.66);
    printf("set: ");
    for(t_i = set_begin(&t_s); !iterator_equal(t_i, set_end(&t_s)); t_i = iterator_next(t_i))
    {
        printf("%f, ", *(float*)iterator_get_pointer(t_i));
    }
    printf("\n");
    printf("deque: ");
    for(t_i = deque_begin(&t_d); !iterator_equal(t_i, deque_end(&t_d)); t_i = iterator_next(t_i))
    {
        printf("%f, ", *(float*)iterator_get_pointer(t_i));
    }
    printf("\n");
    printf("vector: ");
    for(t_i = vector_begin(&t_v); !iterator_equal(t_i, vector_end(&t_v)); t_i = iterator_next(t_i))
    {
        printf("%f, ", *(float*)iterator_get_pointer(t_i));
    }
    printf("\n");
    t_i = vector_end(&t_v);
    /*iterator_advance(&t_i, 1);*/
    t_i = algo_copy_backward(set_begin(&t_s), set_end(&t_s), vector_rbegin(&t_v));
    if(iterator_equal(t_i, vector_end(&t_v)))
    {
        printf("end\n");
    }
    else
    {
        printf("%f\n", *(float*)iterator_get_pointer(t_i));
    }
    printf("set: ");
    for(t_i = set_begin(&t_s); !iterator_equal(t_i, set_end(&t_s)); t_i = iterator_next(t_i))
    {
        printf("%f, ", *(float*)iterator_get_pointer(t_i));
    }
    printf("\n");
    printf("deque: ");
    for(t_i = deque_begin(&t_d); !iterator_equal(t_i, deque_end(&t_d)); t_i = iterator_next(t_i))
    {
        printf("%f, ", *(float*)iterator_get_pointer(t_i));
    }
    printf("\n");
    printf("vector: ");
    for(t_i = vector_begin(&t_v); !iterator_equal(t_i, vector_end(&t_v)); t_i = iterator_next(t_i))
    {
        printf("%f, ", *(float*)iterator_get_pointer(t_i));
    }
    printf("\n");

    t_i = set_end(&t_s);
    while(!iterator_equal(t_i, set_begin(&t_s)))
    {
        t_i = iterator_prev(t_i);
        printf("%f, ", *(float*)iterator_get_pointer(t_i));
    }
    printf("\n");
    multiset_insert(&t_ms, 89.45);
    multiset_insert(&t_ms, -22.01);
    multiset_insert(&t_ms, 34.0009);
    t_i = multiset_end(&t_ms);
    while(!iterator_equal(t_i, multiset_begin(&t_ms)))
    {
        t_i = iterator_prev(t_i);
        printf("%f, ", *(float*)iterator_get_pointer(t_i));
    }
    printf("\n");

    set_destroy(&t_s);
    deque_destroy(&t_d);
    vector_destroy(&t_v);
    pair_destroy(&t_p);
    multiset_destroy(&t_ms);
}

/** local function implementation section **/

/** eof **/

