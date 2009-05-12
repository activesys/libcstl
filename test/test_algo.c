/*
 *  The implementation of algorithm test.
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
#include <stdarg.h>
#include <unistd.h>
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

#include "test_algo.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/
struct abc_t
{
    int n_value;
    long l_value;
    double d_key;
};

/** local function prototype section **/
static void _print(const void* cpv_input, void* pv_output);
static void _square(const void* cpv_input, void* pv_output);
static void _isprime(const void* cpv_input, void* pv_output);
static void _abcgreat(const void* cpv_first, const void* cpv_second, void* pv_output);
static void _print_abc(const void* cpv_input, void* pv_output);
static void _mod3(const void* cpv_input, void* pv_output);
static void _generate(const void* cpv_input, void* pv_output);
static void _plus100(const void* cpv_input, void* pv_output);
static void _is_even(const void* cpv_input, void* pv_output);
static void _greater3(const void* cpv_input, void* pv_output);
static void _doubled(const void* cpv_first, const void* cpv_second, void* pv_output);
static void _both_even_or_odd(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _check_even(const void* cpv_first, const void* cpv_second, void* pv_output);
static void _multipiles10(const void* cpv_input, void* pv_output);
static void _fibonacci(const void* cpv_input, void* pv_output);
static void _less4(const void* cpv_input, void* pv_output);
static void _absless(const void* cpv_first, const void* cpv_second, void* pv_output);
/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
void test_algo(void)
{
    {
        vector_t t_v = create_vector(int);
        iterator_t t_i;

        vector_init(&t_v);
        vector_push_back(&t_v, 2);
        vector_push_back(&t_v, 5);
        vector_push_back(&t_v, 4);
        vector_push_back(&t_v, 1);
        vector_push_back(&t_v, 6);
        vector_push_back(&t_v, 3);

        t_i = algo_min_element(vector_begin(&t_v), vector_end(&t_v));
        printf("min:%d\n", *(int*)iterator_get_pointer(t_i));
        t_i = algo_max_element(vector_begin(&t_v), vector_end(&t_v));
        printf("max:%d\n", *(int*)iterator_get_pointer(t_i));

        algo_sort(vector_begin(&t_v), vector_end(&t_v));
        t_i = algo_find(vector_begin(&t_v), vector_end(&t_v), 3);
        algo_reverse(t_i, vector_end(&t_v));

        for(t_i = vector_begin(&t_v);
            !iterator_equal(t_i, vector_end(&t_v));
            t_i = iterator_next(t_i))
        {
            printf("%d, ", *(int*)iterator_get_pointer(t_i));
        }
        printf("\n");

        vector_destroy(&t_v);
    }
    {
        list_t t_l = create_list(int);
        iterator_t t_i;
        iterator_t t_i25;
        iterator_t t_i35;
        int i = 0;

        list_init(&t_l);
        for(i = 20; i <= 40; ++i)
        {
            list_push_back(&t_l, i);
        }

        t_i = algo_find(list_begin(&t_l), list_end(&t_l), 3);
        algo_reverse(t_i, list_end(&t_l));

        t_i25 = algo_find(list_begin(&t_l), list_end(&t_l), 25);
        t_i35 = algo_find(list_begin(&t_l), list_end(&t_l), 35);

        t_i = algo_max_element(t_i25, t_i35);
        printf("max: %d\n", *(int*)iterator_get_pointer(t_i));

        t_i35 = iterator_next(t_i35);
        t_i = algo_max_element(t_i25, t_i35);
        printf("max: %d\n", *(int*)iterator_get_pointer(t_i));

        list_destroy(&t_l);
    }
    {
        list_t t_l = create_list(int);
        vector_t t_v = create_vector(int);
        int i = 0;

        list_init(&t_l);
        vector_init(&t_v);

        for(i = 0; i < 10; ++i)
        {
            list_push_back(&t_l, i);
        }

        vector_resize(&t_v, list_size(&t_l));
        algo_copy(list_begin(&t_l), list_end(&t_l), vector_begin(&t_v));

        list_destroy(&t_l);
        vector_destroy(&t_v);
    }
    {
        list_t t_l = create_list(int);
        iterator_t t_i;
        int i = 0;

        list_init(&t_l);
        for(i = 0; i < 7; ++i)
        {
            list_push_back(&t_l, i);
            list_push_front(&t_l, i);
        }

        printf("pre:  ");
        for(t_i = list_begin(&t_l);
            !iterator_equal(t_i, list_end(&t_l));
            t_i = iterator_next(t_i))
        {
            printf("%d, ", *(int*)iterator_get_pointer(t_i));
        }
        printf("\n");

        algo_remove(list_begin(&t_l), list_end(&t_l), 3);

        printf("post: ");
        for(t_i = list_begin(&t_l);
            !iterator_equal(t_i, list_end(&t_l));
            t_i = iterator_next(t_i))
        {
            printf("%d, ", *(int*)iterator_get_pointer(t_i));
        }
        printf("\n");

        list_destroy(&t_l);
    }
    {
        list_t t_l = create_list(int);
        iterator_t t_i;
        iterator_t t_end;
        int i = 0;

        list_init(&t_l);
        for(i = 0; i < 7; ++i)
        {
            list_push_back(&t_l, i);
            list_push_front(&t_l, i);
        }

        for(t_i = list_begin(&t_l);
            !iterator_equal(t_i, list_end(&t_l));
            t_i = iterator_next(t_i))
        {
            printf("%d, ", *(int*)iterator_get_pointer(t_i));
        }
        printf("\n");

        t_end = algo_remove(list_begin(&t_l), list_end(&t_l), 3);

        for(t_i = list_begin(&t_l);
            !iterator_equal(t_i, t_end);
            t_i = iterator_next(t_i))
        {
            printf("%d, ", *(int*)iterator_get_pointer(t_i));
        }
        printf("\n");

        printf("number of removed elements: %d\n",
            iterator_distance(t_end, list_end(&t_l)));
        list_erase_range(&t_l, t_end, list_end(&t_l));

        for(t_i = list_begin(&t_l);
            !iterator_equal(t_i, list_end(&t_l));
            t_i = iterator_next(t_i))
        {
            printf("%d, ", *(int*)iterator_get_pointer(t_i));
        }
        printf("\n");

        list_destroy(&t_l);
    }
    {
        set_t t_s = create_set(int);
        iterator_t t_i;
        int i = 0;

        set_init(&t_s);
        for(i = 0; i < 10; ++i)
        {
            set_insert(&t_s, i);
        }

        for(t_i = set_begin(&t_s);
            !iterator_equal(t_i, set_end(&t_s));
            t_i = iterator_next(t_i))
        {
            printf("%d, ", *(int*)iterator_get_pointer(t_i));
        }
        printf("\n");

        printf("number of removed elements: %d\n", set_erase(&t_s, 3));

        for(t_i = set_begin(&t_s);
            !iterator_equal(t_i, set_end(&t_s));
            t_i = iterator_next(t_i))
        {
            printf("%d, ", *(int*)iterator_get_pointer(t_i));
        }
        printf("\n");

        set_destroy(&t_s);
    }
    {
        list_t t_l = create_list(int);
        int i = 0;
        iterator_t t_i;

        list_init(&t_l);
        for(i = 0; i < 7; ++i)
        {
            list_push_back(&t_l, i);
            list_push_front(&t_l, i);
        }

        for(t_i = list_begin(&t_l);
            !iterator_equal(t_i, list_end(&t_l));
            t_i = iterator_next(t_i))
        {
            printf("%d, ", *(int*)iterator_get_pointer(t_i));
        }
        printf("\n");

        list_erase_range(
            &t_l, algo_remove(list_begin(&t_l), list_end(&t_l), 3), list_end(&t_l));
        for(t_i = list_begin(&t_l);
            !iterator_equal(t_i, list_end(&t_l));
            t_i = iterator_next(t_i))
        {
            printf("%d, ", *(int*)iterator_get_pointer(t_i));
        }
        printf("\n");

        list_remove(&t_l, 4);
        for(t_i = list_begin(&t_l);
            !iterator_equal(t_i, list_end(&t_l));
             t_i = iterator_next(t_i))
        {
            printf("%d, ", *(int*)iterator_get_pointer(t_i));
        }
        printf("\n");

        list_destroy(&t_l);
    }
    {
        vector_t t_v = create_vector(int);
        int i = 0;

        vector_init(&t_v);
        for(i = 0; i < 10; ++i)
        {
            vector_push_back(&t_v, i);
        }

        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        vector_destroy(&t_v);
    }
    {
        list_t t_l = create_list(int);
        vector_t t_v = create_vector(int);
        int i = 0;

        list_init(&t_l);
        vector_init_n(&t_v, 10);
        for(i = 0; i < 10; ++i)
        {
            list_push_back(&t_l, i+1);
        }

        algo_transform(list_begin(&t_l), list_end(&t_l), vector_begin(&t_v), _square);

        printf("initialized: ");
        algo_for_each(list_begin(&t_l), list_end(&t_l), _print);
        printf("\n");
        printf("squared:     ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        list_destroy(&t_l);
        vector_destroy(&t_v);
    }
    {
        list_t t_l = create_list(int);
        int i = 0;
        iterator_t t_i;

        list_init(&t_l);
        for(i = 24; i <= 30; ++i)
        {
            list_push_back(&t_l, i);
        }

        t_i = algo_find_if(list_begin(&t_l), list_end(&t_l), _isprime);
        if(iterator_equal(t_i, list_end(&t_l)))
        {
            printf("no prime number found!\n");
        }
        else
        {
            printf("%d is first prime number found!\n",
                *(int*)iterator_get_pointer(t_i));
        }

        list_destroy(&t_l);
    }
    {
        deque_t t_q = create_deque(struct abc_t);
        struct abc_t t_abc;

        deque_init(&t_q);
        t_abc.n_value = 70;
        t_abc.l_value = 934000;
        t_abc.d_key = 0.24;
        deque_push_back(&t_q, t_abc);
        t_abc.n_value = 100;
        t_abc.l_value = 3000;
        t_abc.d_key = 2.09;
        deque_push_back(&t_q, t_abc);
        t_abc.n_value = 2;
        t_abc.l_value = -18;
        t_abc.d_key = 110.00;
        deque_push_back(&t_q, t_abc);
        t_abc.n_value = -902;
        t_abc.l_value = 88000;
        t_abc.d_key = -10.007;
        deque_push_back(&t_q, t_abc);

        algo_for_each(deque_begin(&t_q), deque_end(&t_q), _print_abc);
        algo_sort_if(deque_begin(&t_q), deque_end(&t_q), _abcgreat);
        printf("\n");
        algo_for_each(deque_begin(&t_q), deque_end(&t_q), _print_abc);

        deque_destroy(&t_q);
    }
    {
        deque_t t_q = create_deque(int);

        deque_init(&t_q);
        deque_push_back(&t_q, 34);
        deque_push_back(&t_q, 89);
        deque_push_back(&t_q, 33);
        deque_push_back(&t_q, 40);
        deque_push_back(&t_q, 12);
        deque_push_back(&t_q, 77);
        algo_for_each(deque_begin(&t_q), deque_end(&t_q), _print);
        printf("\n");

        algo_sort(deque_begin(&t_q), deque_end(&t_q));
        algo_for_each(deque_begin(&t_q), deque_end(&t_q), _print);
        printf("\n");

        algo_sort_if(deque_begin(&t_q), deque_end(&t_q), fun_great_int);
        algo_for_each(deque_begin(&t_q), deque_end(&t_q), _print);
        printf("\n");

        deque_destroy(&t_q);
    }
    {
        vector_t t_v = create_vector(int);
        size_t t_limit = 1000;
        size_t t_output = 0;
        int i = 0;

        vector_init(&t_v);
        for(i = 0; i < 10; ++i)
        {
            fun_random_number(&t_limit, &t_output);
            vector_push_back(&t_v, t_output);
        }
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        algo_sort(vector_begin(&t_v), vector_end(&t_v));
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        algo_random_shuffle(vector_begin(&t_v), vector_end(&t_v));
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        algo_sort_if(vector_begin(&t_v), vector_end(&t_v), fun_great_int);
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        vector_destroy(&t_v);
    }
    {
        vector_t t_v1 = create_vector(int);
        vector_t t_v2 = create_vector(int);
        int i = 0;

        vector_init(&t_v1);
        vector_init(&t_v2);
        for(i = 1; i <= 10; ++i)
        {
            vector_push_back(&t_v1, i);
            vector_push_back(&t_v2, i);
        }
        printf("before remove:\n");
        printf("vector1: ");
        algo_for_each(vector_begin(&t_v1), vector_end(&t_v1), _print);
        printf("\n");
        printf("vector2: ");
        algo_for_each(vector_begin(&t_v2), vector_end(&t_v2), _print);
        printf("\n");

        algo_remove(vector_begin(&t_v1), vector_end(&t_v1), 3);
        algo_remove_if(vector_begin(&t_v2), vector_end(&t_v2), _mod3);
        printf("after remove:\n");
        printf("vector1: ");
        algo_for_each(vector_begin(&t_v1), vector_end(&t_v1), _print);
        printf("\n");
        printf("vector2: ");
        algo_for_each(vector_begin(&t_v2), vector_end(&t_v2), _print);
        printf("\n");

        vector_destroy(&t_v1);
        vector_destroy(&t_v2);
    }
    {
        vector_t t_v = create_vector(int);

        vector_init_n(&t_v, 10);
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");
        algo_generate(vector_begin(&t_v), vector_end(&t_v), _generate);
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");
        
        vector_destroy(&t_v);
    }
    {
        vector_t t_v = create_vector(int);
        int i = 0;

        vector_init(&t_v);
        for(i = 0; i < 10; ++i)
        {
            vector_push_back(&t_v, i);
        }
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _plus100);
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        vector_destroy(&t_v);
    }
    {
        vector_t t_v = create_vector(int);
        int i = 0;

        vector_init(&t_v);
        for(i = 1; i <= 10; ++i)
        {
            vector_push_back(&t_v, i);
        }
        printf("vector: ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");
        printf("number of elements equal to 4:           %u\n",
            algo_count(vector_begin(&t_v), vector_end(&t_v), 4));
        printf("number of elements with even value:      %u\n",
            algo_count_if(vector_begin(&t_v), vector_end(&t_v), _is_even));
        printf("number of elements divided exactly by 3: %u\n",
            algo_count_if(vector_begin(&t_v), vector_end(&t_v), _mod3));

        vector_destroy(&t_v);
    }
    {
        list_t t_l = create_list(int);
        iterator_t t_pos1, t_pos2;
        int i = 0;

        list_init(&t_l);
        for(i = 1; i <= 10; ++i)
        {
            list_push_back(&t_l, i);
        }
        for(i = 1; i <= 10; ++i)
        {
            list_push_back(&t_l, i);
        }
        printf("list: ");
        algo_for_each(list_begin(&t_l), list_end(&t_l), _print);
        printf("\n");

        t_pos1 = algo_find(list_begin(&t_l), list_end(&t_l), 4);
        if(!iterator_equal(t_pos1, list_end(&t_l)))
        {
            t_pos1 = iterator_next(t_pos1);
            t_pos2 = algo_find(t_pos1, list_end(&t_l), 4);
        }

        if(!iterator_equal(t_pos1, list_end(&t_l)) &&
           !iterator_equal(t_pos2, list_end(&t_l)))
        {
            t_pos1 = iterator_prev(t_pos1);
            t_pos2 = iterator_next(t_pos2);
            algo_for_each(t_pos1, t_pos2, _print);
            printf("\n");
        }

        list_destroy(&t_l); 
    }
    {
        vector_t t_v = create_vector(int);
        int i = 0;
        iterator_t t_pos;

        vector_init(&t_v);
        for(i = 1; i <= 10; ++i)
        {
            vector_push_back(&t_v, i);
        }
        printf("vector: ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        t_pos = algo_find_if(vector_begin(&t_v), vector_end(&t_v), _greater3);
        printf("the %d. element is the first greater then 3.\n",
            iterator_distance(vector_begin(&t_v), t_pos) + 1);
        t_pos = algo_find_if(vector_begin(&t_v), vector_end(&t_v), _mod3);
        printf("the %d. element is the first divisible by 3.\n",
            iterator_distance(vector_begin(&t_v), t_pos) + 1);

        vector_destroy(&t_v);
    }
    {
        vector_t t_v = create_vector(int);
        iterator_t t_pos;

        vector_init(&t_v);
        vector_push_back(&t_v, 1);
        vector_push_back(&t_v, 3);
        vector_push_back(&t_v, 2);
        vector_push_back(&t_v, 4);
        vector_push_back(&t_v, 5);
        vector_push_back(&t_v, 5);
        vector_push_back(&t_v, 0);
        printf("vector: ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        t_pos = algo_adjacent_find(vector_begin(&t_v), vector_end(&t_v));
        if(!iterator_equal(t_pos, vector_end(&t_v)))
        {
            printf("first two elements with equal value have position %d\n",
                iterator_distance(vector_begin(&t_v), t_pos) + 1);
        }

        t_pos = algo_adjacent_find_if(vector_begin(&t_v), vector_end(&t_v), _doubled);
        if(!iterator_equal(t_pos, vector_end(&t_v)))
        {
            printf("first two elements with second value twice the first have pos. %d\n",
                iterator_distance(vector_begin(&t_v), t_pos) + 1);
        }

        vector_destroy(&t_v);
    }
    {
        vector_t t_v = create_vector(int);
        list_t t_l = create_list(int);
        int i = 0;
        iterator_t t_pos;

        vector_init(&t_v);
        list_init(&t_l);
        for(i = 0; i < 10; ++i)
        {
            vector_push_back(&t_v, i);
        }
        for(i = 3; i < 6; ++i)
        {
            list_push_back(&t_l, i);
        }
        printf("vector: ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");
        printf("search: ");
        algo_for_each(list_begin(&t_l), list_end(&t_l), _print);
        printf("\n");

        t_pos = algo_find_first_of(
            vector_begin(&t_v), vector_end(&t_v), list_begin(&t_l), list_end(&t_l));
        printf("first element of search in vector is element %d\n",
            iterator_distance(vector_begin(&t_v), t_pos) + 1);

        algo_reverse(vector_begin(&t_v), vector_end(&t_v));
        printf("vector: ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");
        printf("search: ");
        algo_for_each(list_begin(&t_l), list_end(&t_l), _print);
        printf("\n");
        t_pos = algo_find_first_of(
            vector_begin(&t_v), vector_end(&t_v), list_begin(&t_l), list_end(&t_l));
        printf("first element of search in vector is element %d\n",
            iterator_distance(vector_begin(&t_v), t_pos) + 1);

        vector_destroy(&t_v);
        list_destroy(&t_l);
    }
    {
        vector_t t_v = create_vector(int);
        list_t t_l = create_list(int);
        int i = 0;

        vector_init(&t_v);
        list_init(&t_l);
        for(i = 1; i <= 7; ++i)
        {
            vector_push_back(&t_v, i);
        }
        for(i = 3; i <= 9; ++i)
        {
            list_push_back(&t_l, i);
        }
        printf("vector: ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");
        printf("list:   ");
        algo_for_each(list_begin(&t_l), list_end(&t_l), _print);
        printf("\n");

        if(algo_equal(vector_begin(&t_v), vector_end(&t_v), list_begin(&t_l)))
        {
            printf("vector == list\n");
        }
        else
        {
            printf("vector != list\n");
        }
        if(algo_equal_if(
            vector_begin(&t_v), vector_end(&t_v), list_begin(&t_l), _both_even_or_odd))
        {
            printf("even and odd elements correspond.\n");
        }
        else
        {
            printf("even and odd elements is not correspond.\n");
        }

        vector_destroy(&t_v);
        list_destroy(&t_l);
    }
    {
        vector_t t_v = create_vector(int);
        list_t t_l = create_list(int);
        pair_t t_p;
        int i = 0;

        vector_init(&t_v);
        list_init(&t_l);
        for(i = 1; i <= 6; ++i)
        {
            vector_push_back(&t_v, i);
        }
        for(i = 1; i <= 16; i *= 2)
        {
            list_push_back(&t_l, i);
        }
        list_push_back(&t_l, 3);
        printf("vector: ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");
        printf("list:   ");
        algo_for_each(list_begin(&t_l), list_end(&t_l), _print);
        printf("\n");

        t_p = algo_mismatch(vector_begin(&t_v), vector_end(&t_v), list_begin(&t_l));
        if(iterator_equal(*(iterator_t*)t_p.first, vector_end(&t_v)))
        {
            printf("no mismatch!\n");
        }
        else
        {
            printf("first mismatch: %d and %d\n",
                *(int*)iterator_get_pointer(*(iterator_t*)t_p.first),
                *(int*)iterator_get_pointer(*(iterator_t*)t_p.second));
        }
        pair_destroy(&t_p);

        t_p = algo_mismatch_if(
            vector_begin(&t_v), vector_end(&t_v), list_begin(&t_l), fun_less_equal_int);
        if(iterator_equal(*(iterator_t*)t_p.first, vector_end(&t_v)))
        {
            printf("always less-or-equal\n");
        }
        else
        {
            printf("not less-or-equal: %d and %d\n",
                *(int*)iterator_get_pointer(*(iterator_t*)t_p.first),
                *(int*)iterator_get_pointer(*(iterator_t*)t_p.second));
        }
        pair_destroy(&t_p);

        vector_destroy(&t_v);
        list_destroy(&t_l);
    }
    {
        deque_t t_dq = create_deque(int);
        list_t t_l = create_list(int);
        int i = 0;
        iterator_t t_pos;

        deque_init(&t_dq);
        list_init(&t_l);
        for(i = 1; i <= 7; ++i)
        {
            deque_push_back(&t_dq, i);
        }
        for(i = 1; i <= 7; ++i)
        {
            deque_push_back(&t_dq, i);
        }
        for(i = 3; i <= 6; ++i)
        {
            list_push_back(&t_l, i);
        }
        printf("deque: ");
        algo_for_each(deque_begin(&t_dq), deque_end(&t_dq), _print);
        printf("\n");
        printf("sub:   ");
        algo_for_each(list_begin(&t_l), list_end(&t_l), _print);
        printf("\n");

        t_pos = algo_search(
            deque_begin(&t_dq), deque_end(&t_dq), list_begin(&t_l), list_end(&t_l));
        while(!iterator_equal(t_pos, deque_end(&t_dq)))
        {
            printf("sub find with element %d\n",
                iterator_distance(deque_begin(&t_dq), t_pos) + 1);
            t_pos = iterator_next(t_pos);
            t_pos = algo_search(
                t_pos, deque_end(&t_dq), list_begin(&t_l), list_end(&t_l));
        }

        deque_destroy(&t_dq);
        list_destroy(&t_l);
    }
    {
        vector_t t_v = create_vector(int);
        deque_t t_dq = create_deque(bool_t);
        int i = 0;
        iterator_t t_pos;

        vector_init(&t_v);
        deque_init(&t_dq);
        for(i = 1; i <= 9; ++i)
        {
            vector_push_back(&t_v, i);
        }
        deque_push_back(&t_dq, true);
        deque_push_back(&t_dq, false);
        deque_push_back(&t_dq, true);
        printf("vector: ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        t_pos = algo_search_if(
            vector_begin(&t_v), vector_end(&t_v),
            deque_begin(&t_dq), deque_end(&t_dq),
            _check_even);
        while(!iterator_equal(t_pos, vector_end(&t_v)))
        {
            printf("subrange found starting with element %d\n",
                iterator_distance(vector_begin(&t_v), t_pos) + 1);

            t_pos = iterator_next(t_pos);
            t_pos = algo_search_if(
                t_pos, vector_end(&t_v),
                deque_begin(&t_dq), deque_end(&t_dq),
                _check_even);
        }

        vector_destroy(&t_v);
        deque_destroy(&t_dq);
    }
    {
        deque_t t_dq = create_deque(int);
        int i = 0;
        iterator_t t_pos;

        deque_init(&t_dq);
        for(i = 1; i <= 9; ++i)
        {
            deque_push_back(&t_dq, i);
        }
        printf("deque: ");
        algo_for_each(deque_begin(&t_dq), deque_end(&t_dq), _print);
        printf("\n");

        t_pos = algo_search_n(deque_begin(&t_dq), deque_end(&t_dq), 4, 3);
        if(iterator_equal(t_pos, deque_end(&t_dq)))
        {
            printf("no four consecutive elements with value 3 found\n");
        }
        else
        {
            printf("four consective elements with value 3 start with %d. element\n",
                iterator_distance(deque_begin(&t_dq), t_pos) + 1);
        }

        t_pos = algo_search_n_if(
            deque_begin(&t_dq), deque_end(&t_dq), 4, 3, fun_great_int);
        if(iterator_equal(t_pos, deque_end(&t_dq)))
        {
            printf("no four consecutive elements with value > 3 found\n");
        }
        else
        {
            printf("four consective elements with value > 3 start with %d. element\n",
                iterator_distance(deque_begin(&t_dq), t_pos) + 1);
        }

        deque_destroy(&t_dq);
    }
    {
        deque_t t_dq = create_deque(int);
        list_t t_l = create_list(int);
        int i = 0;
        iterator_t t_pos, t_end;

        deque_init(&t_dq);
        list_init(&t_l);
        for(i = 1; i <= 7; ++i)
        {
            deque_push_back(&t_dq, i);
        }
        for(i = 1; i <= 7; ++i)
        {
            deque_push_back(&t_dq, i);
        }
        for(i = 3; i <= 6; ++i)
        {
            list_push_back(&t_l, i);
        }
        printf("deque: ");
        algo_for_each(deque_begin(&t_dq), deque_end(&t_dq), _print);
        printf("\n");
        printf("sub:   ");
        algo_for_each(list_begin(&t_l), list_end(&t_l), _print);
        printf("\n");

        t_pos = algo_search_end(
            deque_begin(&t_dq), deque_end(&t_dq), list_begin(&t_l), list_end(&t_l));
        t_end = deque_end(&t_dq);
        while(!iterator_equal(t_pos, t_end))
        {
            printf("sub found starting with element %d\n",
                iterator_distance(deque_begin(&t_dq), t_pos) + 1);
            t_end = t_pos;
            t_pos = algo_find_end(
                deque_begin(&t_dq), t_end, list_begin(&t_l), list_end(&t_l));
        }

        deque_destroy(&t_dq);
        list_destroy(&t_l);
    }
    {
        vector_t t_v1 = create_vector(int);
        vector_t t_v2 = create_vector(int);
        list_t t_l1 = create_list(int);
        list_t t_l2 = create_list(int);
        int i = 0;
        iterator_t t_first, t_last, t_result;

        vector_init(&t_v1);
        vector_init(&t_v2);
        list_init(&t_l1);
        list_init(&t_l2);
        for(i = 0; i < 9; ++i)
        {
            vector_push_back(&t_v1, i);
            vector_push_back(&t_v2, i);
            list_push_back(&t_l1, i);
            list_push_back(&t_l2, i);
        }
        printf("before copy:\n");
        printf("vector1: ");
        algo_for_each(vector_begin(&t_v1), vector_end(&t_v1), _print);
        printf("\n");
        printf("list1:   ");
        algo_for_each(list_begin(&t_l1), list_end(&t_l1), _print);
        printf("\n");
        printf("vector2: ");
        algo_for_each(vector_begin(&t_v2), vector_end(&t_v2), _print);
        printf("\n");
        printf("list2:   ");
        algo_for_each(list_begin(&t_l2), list_end(&t_l2), _print);
        printf("\n");

        /* case 1 */
        t_first = vector_begin(&t_v1);
        t_first = iterator_advance(t_first, 2);
        t_last = t_first;
        t_last = iterator_advance(t_last, 5);
        t_result = vector_begin(&t_v1);
        algo_copy(t_first, t_last, t_result);

        t_first = list_begin(&t_l1);
        t_first = iterator_advance(t_first, 2);
        t_last = t_first;
        t_last = iterator_advance(t_last, 5);
        t_result = list_begin(&t_l1);
        algo_copy(t_first, t_last, t_result);

        /* case 2 */
        t_first = vector_begin(&t_v2);
        t_first = iterator_advance(t_first, 2);
        t_last = t_first;
        t_last = iterator_advance(t_last, 5);
        t_result = vector_begin(&t_v2);
        t_result = iterator_advance(t_result, 4);
        algo_copy(t_first, t_last, t_result);

        t_first = list_begin(&t_l2);
        t_first = iterator_advance(t_first, 2);
        t_last = t_first;
        t_last = iterator_advance(t_last, 5);
        t_result = list_begin(&t_l2);
        t_result = iterator_advance(t_result, 4);
        algo_copy(t_first, t_last, t_result);

        printf("after copy:\n");
        printf("vector1: ");
        algo_for_each(vector_begin(&t_v1), vector_end(&t_v1), _print);
        printf("\n");
        printf("list1:   ");
        algo_for_each(list_begin(&t_l1), list_end(&t_l1), _print);
        printf("\n");
        printf("vector2: ");
        algo_for_each(vector_begin(&t_v2), vector_end(&t_v2), _print);
        printf("\n");
        printf("list2:   ");
        algo_for_each(list_begin(&t_l2), list_end(&t_l2), _print);
        printf("\n");

        vector_destroy(&t_v1);
        list_destroy(&t_l1);
        vector_destroy(&t_v2);
        list_destroy(&t_l2);
    }
    {
        vector_t t_v1 = create_vector(int);
        vector_t t_v2 = create_vector(int);
        list_t t_l1 = create_list(int);
        list_t t_l2 = create_list(int);
        int i = 0;
        iterator_t t_first, t_last, t_result;

        vector_init(&t_v1);
        vector_init(&t_v2);
        list_init(&t_l1);
        list_init(&t_l2);
        for(i = 0; i < 9; ++i)
        {
            vector_push_back(&t_v1, i);
            vector_push_back(&t_v2, i);
            list_push_back(&t_l1, i);
            list_push_back(&t_l2, i);
        }
        printf("before copy:\n");
        printf("vector1: ");
        algo_for_each(vector_begin(&t_v1), vector_end(&t_v1), _print);
        printf("\n");
        printf("list1:   ");
        algo_for_each(list_begin(&t_l1), list_end(&t_l1), _print);
        printf("\n");
        printf("vector2: ");
        algo_for_each(vector_begin(&t_v2), vector_end(&t_v2), _print);
        printf("\n");
        printf("list2:   ");
        algo_for_each(list_begin(&t_l2), list_end(&t_l2), _print);
        printf("\n");

        /* case 1 */
        t_first = vector_begin(&t_v1);
        t_first = iterator_advance(t_first, 2);
        t_last = t_first;
        t_last = iterator_advance(t_last, 5);
        t_result = vector_begin(&t_v1);
        t_result = iterator_advance(t_result, 5);
        algo_copy_backward(t_first, t_last, t_result);

        t_first = list_begin(&t_l1);
        t_first = iterator_advance(t_first, 2);
        t_last = t_first;
        t_last = iterator_advance(t_last, 5);
        t_result = list_begin(&t_l1);
        t_result = iterator_advance(t_result, 5);
        algo_copy_backward(t_first, t_last, t_result);

        /* case 2 */
        t_first = vector_begin(&t_v2);
        t_first = iterator_advance(t_first, 2);
        t_last = t_first;
        t_last = iterator_advance(t_last, 5);
        t_result = vector_end(&t_v2);
        algo_copy_backward(t_first, t_last, t_result);

        t_first = list_begin(&t_l2);
        t_first = iterator_advance(t_first, 2);
        t_last = t_first;
        t_last = iterator_advance(t_last, 5);
        t_result = list_end(&t_l2);
        algo_copy_backward(t_first, t_last, t_result);

        printf("after copy:\n");
        printf("vector1: ");
        algo_for_each(vector_begin(&t_v1), vector_end(&t_v1), _print);
        printf("\n");
        printf("list1:   ");
        algo_for_each(list_begin(&t_l1), list_end(&t_l1), _print);
        printf("\n");
        printf("vector2: ");
        algo_for_each(vector_begin(&t_v2), vector_end(&t_v2), _print);
        printf("\n");
        printf("list2:   ");
        algo_for_each(list_begin(&t_l2), list_end(&t_l2), _print);
        printf("\n");

        vector_destroy(&t_v1);
        list_destroy(&t_l1);
        vector_destroy(&t_v2);
        list_destroy(&t_l2);
    }
    {
        vector_t t_v = create_vector(int);
        deque_t t_dq = create_deque(int);
        int i = 0;

        vector_init(&t_v);
        deque_init(&t_dq);
        for(i = 1; i <= 9; ++i)
        {
            vector_push_back(&t_v, i);
        }
        for(i = 11; i <= 23; ++i)
        {
            deque_push_back(&t_dq, i);
        }
        printf("vector: ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");
        printf("deque:  ");
        algo_for_each(deque_begin(&t_dq), deque_end(&t_dq), _print);
        printf("\n\n");

        algo_swap(vector_begin(&t_v), deque_begin(&t_dq));
        printf("vector: ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");
        printf("deque:  ");
        algo_for_each(deque_begin(&t_dq), deque_end(&t_dq), _print);
        printf("\n\n");

        algo_swap_ranges(vector_begin(&t_v), vector_end(&t_v), deque_begin(&t_dq));
        printf("vector: ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");
        printf("deque:  ");
        algo_for_each(deque_begin(&t_dq), deque_end(&t_dq), _print);
        printf("\n\n");

        algo_iter_swap(vector_begin(&t_v), deque_begin(&t_dq));
        printf("vector: ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");
        printf("deque:  ");
        algo_for_each(deque_begin(&t_dq), deque_end(&t_dq), _print);
        printf("\n\n");

        vector_destroy(&t_v);
        deque_destroy(&t_dq);
    }
    {
        vector_t t_v = create_vector(int);
        list_t t_l = create_list(int);
        int i = 0;

        vector_init(&t_v);
        list_init_n(&t_l, 10);
        for(i = 1; i <= 10; ++i)
        {
            vector_push_back(&t_v, i);
        }
        printf("vector:  ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");
        algo_transform(
            vector_begin(&t_v), vector_end(&t_v), vector_begin(&t_v), fun_negate_int);
        printf("negated: ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        algo_transform(
            vector_begin(&t_v), vector_end(&t_v), list_begin(&t_l), _multipiles10);
        printf("list:    ");
        algo_for_each(list_begin(&t_l), list_end(&t_l), _print);
        printf("\n");

        vector_destroy(&t_v);
        list_destroy(&t_l);
    }
    {
        vector_t t_v = create_vector(int);
        list_t t_l = create_list(int);
        deque_t t_dq = create_deque(int);
        int i = 0;

        vector_init(&t_v);
        list_init_n(&t_l, 10);
        deque_init_n(&t_dq, 10);
        for(i = 1; i <= 10; ++i)
        {
            vector_push_back(&t_v, i);
        }
        printf("vector:  ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        algo_transform_binary(
            vector_begin(&t_v), vector_end(&t_v),
            vector_begin(&t_v), vector_begin(&t_v),
            fun_multiplies_int);
        printf("squared: ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        algo_transform_binary(
            vector_begin(&t_v), vector_end(&t_v),
            vector_begin(&t_v), list_begin(&t_l),
            fun_plus_int);
        printf("list:    ");
        algo_for_each(list_begin(&t_l), list_end(&t_l), _print);
        printf("\n");

        algo_transform_binary(
            vector_begin(&t_v), vector_end(&t_v),
            list_begin(&t_l), deque_begin(&t_dq),
            fun_minus_int);
        printf("deque:   ");
        algo_for_each(deque_begin(&t_dq), deque_end(&t_dq), _print);
        printf("\n");

        vector_destroy(&t_v);
        list_destroy(&t_l);
        deque_destroy(&t_dq);
    }
    {
        vector_t t_v = create_vector(int);
        list_t t_l = create_list(int);
        int i = 0;

        vector_init(&t_v);
        list_init_n(&t_l, 20);
        for(i = 1; i <= 10; ++i)
        {
            vector_push_back(&t_v, i);
        }
        for(i = 1; i <= 10; ++i)
        {
            vector_push_back(&t_v, i);
        }
        printf("vector: ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        printf("        ");
        algo_replace(vector_begin(&t_v), vector_end(&t_v), 6, 42);
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        printf("        ");
        algo_replace_if(vector_begin(&t_v), vector_end(&t_v), _mod3, -3);
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        printf("list:   ");
        algo_replace_copy_if(
            vector_begin(&t_v), vector_end(&t_v), list_begin(&t_l), _greater3, 0);
        algo_for_each(list_begin(&t_l), list_end(&t_l), _print);
        printf("\n");

        vector_destroy(&t_v);
    }
    {
        vector_t t_v = create_vector(int);
        iterator_t t_first, t_last;

        vector_init_n(&t_v, 20);
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        t_first = t_last = vector_begin(&t_v);
        t_last = iterator_advance(t_last, 5);
        algo_fill(t_first, t_last, 2);
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");
        algo_fill_n(t_last, 3, 5);
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        t_first = iterator_advance(t_first, 10);
        t_last = iterator_advance(t_last, 10);
        algo_generate(t_first, t_last, _fibonacci);
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");
        algo_generate_n(t_last, 2, _fibonacci);
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        vector_destroy(&t_v);
    }
    {
        vector_t t_v = create_vector(int);
        list_t t_l = create_list(int);
        int i = 0;
        iterator_t t_pos;

        vector_init(&t_v);
        list_init_n(&t_l, 20);
        for(i = 2; i <= 6; ++i)
        {
            vector_push_back(&t_v, i);
        }
        for(i = 4; i <= 9; ++i)
        {
            vector_push_back(&t_v, i);
        }
        for(i = 1; i <= 7; ++i)
        {
            vector_push_back(&t_v, i);
        }
        printf("vector:            ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        t_pos = algo_remove(vector_begin(&t_v), vector_end(&t_v), 5);
        printf("size not changed:  ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");
        vector_erase_range(&t_v, t_pos, vector_end(&t_v));
        printf("size changed:      ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        list_erase_range(
            &t_l, 
            algo_remove_copy_if(
                vector_begin(&t_v), vector_end(&t_v), list_begin(&t_l), _less4),
            list_end(&t_l));
        printf("list(< 4 removed): ");
        algo_for_each(list_begin(&t_l), list_end(&t_l), _print);
        printf("\n");

        vector_destroy(&t_v);
        list_destroy(&t_l);
    }
    {
        vector_t t_v1 = create_vector(int);
        vector_t t_v2 = create_vector(int);
        list_t t_l = create_list(int);
        iterator_t t_pos;

        vector_init(&t_v1);
        vector_push_back(&t_v1, 1);
        vector_push_back(&t_v1, 4);
        vector_push_back(&t_v1, 4);
        vector_push_back(&t_v1, 6);
        vector_push_back(&t_v1, 1);
        vector_push_back(&t_v1, 2);
        vector_push_back(&t_v1, 2);
        vector_push_back(&t_v1, 3);
        vector_push_back(&t_v1, 1);
        vector_push_back(&t_v1, 6);
        vector_push_back(&t_v1, 6);
        vector_push_back(&t_v1, 6);
        vector_push_back(&t_v1, 5);
        vector_push_back(&t_v1, 7);
        vector_push_back(&t_v1, 5);
        vector_push_back(&t_v1, 4);
        vector_push_back(&t_v1, 4);
        vector_init_copy(&t_v2, &t_v1);
        list_init_n(&t_l, vector_size(&t_v1));

        printf("vector:           ");
        algo_for_each(vector_begin(&t_v1), vector_end(&t_v1), _print);
        printf("\n");
        t_pos = algo_unique(vector_begin(&t_v1), vector_end(&t_v1));
        printf("size not changed: ");
        algo_for_each(vector_begin(&t_v1), vector_end(&t_v1), _print);
        printf("\n");
        vector_erase_range(&t_v1, t_pos, vector_end(&t_v1));
        printf("size changed:     ");
        algo_for_each(vector_begin(&t_v1), vector_end(&t_v1), _print);
        printf("\n");

        list_erase_range(
            &t_l,
            algo_unique_copy_if(
                vector_begin(&t_v2), vector_end(&t_v2), list_begin(&t_l), fun_great_int),
            list_end(&t_l));
        printf("list:             ");
        algo_for_each(list_begin(&t_l), list_end(&t_l), _print);
        printf("\n");

        vector_destroy(&t_v1);
        vector_destroy(&t_v2);
        list_destroy(&t_l);
    }
    {
        vector_t t_v = create_vector(int);
        list_t t_l = create_list(int);
        int i = 0;
        iterator_t t_first, t_last;

        vector_init(&t_v);
        for(i = 1; i <= 9; ++i)
        {
            vector_push_back(&t_v, i);
        }
        list_init_n(&t_l, vector_size(&t_v));

        printf("vector:           ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");
        algo_reverse(vector_begin(&t_v), vector_end(&t_v));
        printf("reverse:          ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");
        t_first = vector_begin(&t_v);
        t_last = vector_end(&t_v);
        t_first = iterator_next(t_first), t_last = iterator_prev(t_last);
        algo_reverse(t_first, t_last);
        printf("reverse subrange: ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        algo_reverse_copy(vector_begin(&t_v), vector_end(&t_v), list_begin(&t_l));
        printf("list:             ");
        algo_for_each(list_begin(&t_l), list_end(&t_l), _print);
        printf("\n");

        vector_destroy(&t_v);
        list_destroy(&t_l);
    }
    {
        vector_t t_v = create_vector(int);
        list_t t_l = create_list(int);
        int i = 0;
        iterator_t t_pos;

        vector_init(&t_v);
        for(i = 0; i < 10; ++i)
        {
            vector_push_back(&t_v, i);
        }
        list_init_n(&t_l, vector_size(&t_v));

        printf("vector:        ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        t_pos = vector_begin(&t_v);
        t_pos = iterator_next(t_pos);
        algo_rotate(vector_begin(&t_v), t_pos, vector_end(&t_v));
        printf("one left:      ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        t_pos = vector_end(&t_v);
        t_pos = iterator_prev_n(t_pos, 2);
        algo_rotate(vector_begin(&t_v), t_pos, vector_end(&t_v));
        printf("two right:     ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        algo_rotate_copy(
            vector_begin(&t_v),
            algo_find(vector_begin(&t_v), vector_end(&t_v), 4),
            vector_end(&t_v),
            list_begin(&t_l));
        printf("list(4 first): ");
        algo_for_each(list_begin(&t_l), list_end(&t_l), _print);
        printf("\n");

        vector_destroy(&t_v);
        list_destroy(&t_l);
    }
    {
        vector_t t_v = create_vector(int);
        int i = 0;

        vector_init(&t_v);
        for(i = 0; i < 10; ++i)
        {
            vector_push_back(&t_v, i);
        }
        printf("vector:   ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        algo_random_shuffle(vector_begin(&t_v), vector_end(&t_v));
        printf("shuffled: ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        algo_sort(vector_begin(&t_v), vector_end(&t_v));
        printf("sorted:   ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        algo_random_shuffle(vector_begin(&t_v), vector_end(&t_v));
        printf("shuffled: ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        vector_destroy(&t_v);
    }
    {
        vector_t t_v = create_vector(int);
        deque_t t_dq = create_deque(int);
        int i = 0;

        vector_init(&t_v);
        for(i = 0; i < 15; ++i)
        {
            vector_push_back(&t_v, i);
        }
        printf("vector: ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        deque_init_n(&t_dq, 10);
        algo_random_sample(
            vector_begin(&t_v), vector_end(&t_v),
            deque_begin(&t_dq), deque_end(&t_dq));
        printf("deque:   ");
        algo_for_each(deque_begin(&t_dq), deque_end(&t_dq), _print);
        printf("\n");

        deque_resize(&t_dq, 20);
        algo_random_sample(
            vector_begin(&t_v), vector_end(&t_v),
            deque_begin(&t_dq), deque_end(&t_dq));
        printf("deque:   ");
        algo_for_each(deque_begin(&t_dq), deque_end(&t_dq), _print);
        printf("\n");

        vector_destroy(&t_v);
        deque_destroy(&t_dq);
    }
    {
        vector_t t_v1 = create_vector(int);
        vector_t t_v2 = create_vector(int);
        int i = 0;
        iterator_t t_pos;

        vector_init(&t_v1);
        vector_init(&t_v2);
        for(i = 1; i <= 9; ++i)
        {
            vector_push_back(&t_v1, i);
            vector_push_back(&t_v2, i);
        }
        printf("vector1: ");
        algo_for_each(vector_begin(&t_v1), vector_end(&t_v1), _print);
        printf("\n");
        printf("vector2: ");
        algo_for_each(vector_begin(&t_v2), vector_end(&t_v2), _print);
        printf("\n");

        t_pos = algo_partition(vector_begin(&t_v1), vector_end(&t_v1), _is_even);
        printf("vector1: ");
        algo_for_each(vector_begin(&t_v1), vector_end(&t_v1), _print);
        printf("\n");
        printf("first odd element: %d\n", *(int*)iterator_get_pointer(t_pos));

        t_pos = algo_stable_partition(vector_begin(&t_v2), vector_end(&t_v2), _is_even);
        printf("vector2: ");
        algo_for_each(vector_begin(&t_v2), vector_end(&t_v2), _print);
        printf("\n");
        printf("first odd element: %d\n", *(int*)iterator_get_pointer(t_pos));

        vector_destroy(&t_v1);
        vector_destroy(&t_v2);
    }
    {
        vector_t t_v = create_vector(int);
        int i = 0;

        vector_init(&t_v);
        for(i = 1; i <= 9; ++i)
        {
            vector_push_back(&t_v, i);
            vector_push_back(&t_v, i);
        }
        algo_random_shuffle(vector_begin(&t_v), vector_end(&t_v));
        printf("vector:   ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        algo_sort(vector_begin(&t_v), vector_end(&t_v));
        printf("sorted:   ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        algo_sort_if(vector_begin(&t_v), vector_end(&t_v), fun_great_int);
        printf("sorted >: ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        vector_destroy(&t_v);
    }
    {
        vector_t t_v = create_vector(struct abc_t);
        deque_t t_dq = create_deque(struct abc_t);
        struct abc_t t_abc;
        
        vector_init(&t_v);
        deque_init(&t_dq);
        t_abc.n_value = 70;
        t_abc.l_value = 934000;
        t_abc.d_key = 0.24;
        vector_push_back(&t_v, t_abc);
        deque_push_back(&t_dq, t_abc);
        t_abc.n_value = 100;
        t_abc.l_value = 3000;
        t_abc.d_key = 2.09;
        vector_push_back(&t_v, t_abc);
        deque_push_back(&t_dq, t_abc);
        t_abc.n_value = 2;
        t_abc.l_value = -18;
        t_abc.d_key = 110.00;
        vector_push_back(&t_v, t_abc);
        deque_push_back(&t_dq, t_abc);
        t_abc.n_value = -902;
        t_abc.l_value = 88000;
        t_abc.d_key = -10.007;
        vector_push_back(&t_v, t_abc);
        deque_push_back(&t_dq, t_abc);
        t_abc.n_value = 302;
        t_abc.l_value = 800;
        t_abc.d_key = 0.067;
        vector_push_back(&t_v, t_abc);
        deque_push_back(&t_dq, t_abc);
        t_abc.n_value = 2;
        t_abc.l_value = 7;
        t_abc.d_key = 0.067;
        vector_push_back(&t_v, t_abc);
        deque_push_back(&t_dq, t_abc);
        t_abc.n_value = 1;
        t_abc.l_value = 89;
        t_abc.d_key = 1618.9;
        vector_push_back(&t_v, t_abc);
        deque_push_back(&t_dq, t_abc);
        t_abc.n_value = -10000;
        t_abc.l_value = -18;
        t_abc.d_key = -8.9;
        vector_push_back(&t_v, t_abc);
        deque_push_back(&t_dq, t_abc);
        t_abc.n_value = 0;
        t_abc.l_value = 0;
        t_abc.d_key = 0.0;
        vector_push_back(&t_v, t_abc);
        deque_push_back(&t_dq, t_abc);
        t_abc.n_value = 2340;
        t_abc.l_value = 890;
        t_abc.d_key = 0.009;
        vector_push_back(&t_v, t_abc);
        deque_push_back(&t_dq, t_abc);
        t_abc.n_value = 2340;
        t_abc.l_value = 890;
        t_abc.d_key = 0.067;
        vector_push_back(&t_v, t_abc);
        deque_push_back(&t_dq, t_abc);
        t_abc.n_value = 2;
        t_abc.l_value = 7;
        t_abc.d_key = 0.067;
        vector_push_back(&t_v, t_abc);
        deque_push_back(&t_dq, t_abc);
        t_abc.n_value = 1111;
        t_abc.l_value = 11189;
        t_abc.d_key = 1618.9;
        vector_push_back(&t_v, t_abc);
        deque_push_back(&t_dq, t_abc);
        t_abc.n_value = -2340;
        t_abc.l_value = -890;
        t_abc.d_key = 0.009;
        vector_push_back(&t_v, t_abc);
        deque_push_back(&t_dq, t_abc);
        t_abc.n_value = 992;
        t_abc.l_value = 918;
        t_abc.d_key = 110.00;
        vector_push_back(&t_v, t_abc);
        deque_push_back(&t_dq, t_abc);
        t_abc.n_value = 40;
        t_abc.l_value = 90;
        t_abc.d_key = 0.009;
        vector_push_back(&t_v, t_abc);
        deque_push_back(&t_dq, t_abc);
        t_abc.n_value = 2;
        t_abc.l_value = 8;
        t_abc.d_key = 110.00;
        vector_push_back(&t_v, t_abc);
        deque_push_back(&t_dq, t_abc);

        printf("vector:\n");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print_abc);
        printf("\n");
        printf("deque:\n");
        algo_for_each(deque_begin(&t_dq), deque_end(&t_dq), _print_abc);
        printf("\n");

        algo_sort_if(vector_begin(&t_v), vector_end(&t_v), _abcgreat);
        printf("sorted vector:\n");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print_abc);
        printf("\n");

        algo_stable_sort_if(deque_begin(&t_dq), deque_end(&t_dq), _abcgreat);
        printf("stable sorted deque:\n");
        algo_for_each(deque_begin(&t_dq), deque_end(&t_dq), _print_abc);
        printf("\n");

        vector_destroy(&t_v);
        deque_destroy(&t_dq);
    }
    {
        deque_t t_dq = create_deque(int);
        int i = 0;
        iterator_t t_pos;

        deque_init(&t_dq);
        for(i = 3; i <= 7; ++i)
        {
            deque_push_back(&t_dq, i);
        }
        for(i = 2; i <= 6; ++i)
        {
            deque_push_back(&t_dq, i);
        }
        for(i = 1; i <= 5; ++i)
        {
            deque_push_back(&t_dq, i);
        }
        algo_for_each(deque_begin(&t_dq), deque_end(&t_dq), _print);
        printf("\n");

        t_pos = deque_begin(&t_dq);
        t_pos = iterator_advance(t_pos, 5);
        algo_partial_sort(deque_begin(&t_dq), t_pos, deque_end(&t_dq));
        algo_for_each(deque_begin(&t_dq), deque_end(&t_dq), _print);
        printf("\n");

        algo_partial_sort_if(deque_begin(&t_dq), t_pos, deque_end(&t_dq), fun_great_int);
        algo_for_each(deque_begin(&t_dq), deque_end(&t_dq), _print);
        printf("\n");

        algo_partial_sort(deque_begin(&t_dq), deque_end(&t_dq), deque_end(&t_dq));
        algo_for_each(deque_begin(&t_dq), deque_end(&t_dq), _print);
        printf("\n");

        deque_destroy(&t_dq);
    }
    {
        deque_t t_dq = create_deque(int);
        vector_t t_v6 = create_vector(int);  /* initialized with 6 elements */
        vector_t t_v30 = create_vector(int); /* initialized with 30 elements */
        int i = 0;
        iterator_t t_pos;

        deque_init(&t_dq);
        vector_init_n(&t_v6, 6);
        vector_init_n(&t_v30, 30);
        for(i = 3; i <= 7; ++i)
        {
            deque_push_back(&t_dq, i);
        }
        for(i = 2; i <= 6; ++i)
        {
            deque_push_back(&t_dq, i);
        }
        for(i = 1; i <= 5; ++i)
        {
            deque_push_back(&t_dq, i);
        }
        algo_for_each(deque_begin(&t_dq), deque_end(&t_dq), _print);
        printf("\n");

        t_pos = algo_partial_sort_copy(
            deque_begin(&t_dq), deque_end(&t_dq),
            vector_begin(&t_v6), vector_end(&t_v6));
        algo_for_each(vector_begin(&t_v6), t_pos, _print);
        printf("\n");

        t_pos = algo_partial_sort_copy_if(
            deque_begin(&t_dq), deque_end(&t_dq),
            vector_begin(&t_v30), vector_end(&t_v30),
            fun_great_int);
        algo_for_each(vector_begin(&t_v30), t_pos, _print);
        printf("\n");

        deque_destroy(&t_dq);
        vector_destroy(&t_v6);
        vector_destroy(&t_v30);
    }
    {
        vector_t t_v = create_vector(int);
        int i = 0;

        vector_init(&t_v);
        for(i = 0; i < 20; ++i)
        {
            vector_push_back(&t_v, i);
        }
        algo_random_shuffle(vector_begin(&t_v), vector_end(&t_v));
        printf("vector: ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");
        if(algo_is_sorted(vector_begin(&t_v), vector_end(&t_v)))
        {
            printf("sorted\n");
        }
        else
        {
            printf("not sorted\n");
        }
        if(algo_is_sorted_if(vector_begin(&t_v), vector_end(&t_v), fun_great_int))
        {
            printf("sorted with >\n");
        }
        else
        {
            printf("not sorted with >\n");
        }

        algo_sort(vector_begin(&t_v), vector_end(&t_v));
        printf("vector: ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");
        if(algo_is_sorted(vector_begin(&t_v), vector_end(&t_v)))
        {
            printf("sorted\n");
        }
        else
        {
            printf("not sorted\n");
        }
        if(algo_is_sorted_if(vector_begin(&t_v), vector_end(&t_v), fun_great_int))
        {
            printf("sorted with >\n");
        }
        else
        {
            printf("not sorted with >\n");
        }

        algo_sort_if(vector_begin(&t_v), vector_end(&t_v), fun_great_int);
        printf("vector: ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");
        if(algo_is_sorted(vector_begin(&t_v), vector_end(&t_v)))
        {
            printf("sorted\n");
        }
        else
        {
            printf("not sorted\n");
        }
        if(algo_is_sorted_if(vector_begin(&t_v), vector_end(&t_v), fun_great_int))
        {
            printf("sorted with >\n");
        }
        else
        {
            printf("not sorted with >\n");
        }

        vector_destroy(&t_v);
    }
    {
        vector_t t_v1 = create_vector(int);
        vector_t t_v2 = create_vector(int);
        int i = 0;
        iterator_t t_pos;

        vector_init(&t_v1);
        vector_init(&t_v2);
        for(i = 0; i < 10; ++i)
        {
            vector_push_back(&t_v1, i);
            vector_push_back(&t_v2, i);
        }

        algo_random_shuffle(vector_begin(&t_v1), vector_end(&t_v1));
        algo_random_shuffle(vector_begin(&t_v2), vector_end(&t_v2));

        algo_sort(vector_begin(&t_v1), vector_end(&t_v1));
        t_pos = vector_begin(&t_v2);
        t_pos = iterator_advance(t_pos, 5);
        algo_nth_element(vector_begin(&t_v2), t_pos, vector_end(&t_v2));

        printf("vector1: ");
        algo_for_each(vector_begin(&t_v1), vector_end(&t_v1), _print);
        printf("\n");
        printf("vector2: ");
        algo_for_each(vector_begin(&t_v2), vector_end(&t_v2), _print);
        printf("\n");

        algo_sort_if(vector_begin(&t_v1), vector_end(&t_v1), fun_great_int);
        t_pos = vector_begin(&t_v2);
        t_pos = iterator_advance(t_pos, 4);
        algo_nth_element_if(
            vector_begin(&t_v2), t_pos, vector_end(&t_v2), fun_great_int);

        printf("vector1: ");
        algo_for_each(vector_begin(&t_v1), vector_end(&t_v1), _print);
        printf("\n");
        printf("vector2: ");
        algo_for_each(vector_begin(&t_v2), vector_end(&t_v2), _print);
        printf("\n");

        vector_destroy(&t_v1);
        vector_destroy(&t_v2);
    }
    {
        list_t t_l = create_list(int);
        int i = 0;
        iterator_t t_lower, t_upper;

        list_init(&t_l);
        for(i = 0; i < 10; ++i)
        {
            list_push_back(&t_l, i);
            list_push_back(&t_l, i);
        }
        algo_for_each(list_begin(&t_l), list_end(&t_l), _print);
        printf("\n");

        t_lower = algo_lower_bound(list_begin(&t_l), list_end(&t_l), 5);
        t_upper = algo_upper_bound(list_begin(&t_l), list_end(&t_l), 5);
        printf("5 could get position %d up to %d without break the sorting\n",
            iterator_distance(list_begin(&t_l), t_lower) + 1,
            iterator_distance(list_begin(&t_l), t_upper) + 1);

        list_insert(&t_l, algo_lower_bound(list_begin(&t_l), list_end(&t_l), 3), 3);
        list_insert(&t_l, algo_upper_bound(list_begin(&t_l), list_end(&t_l), 7), 7);
        algo_for_each(list_begin(&t_l), list_end(&t_l), _print);
        printf("\n");

        list_destroy(&t_l);
    }
    {
        vector_t t_v = create_vector(int);
        int i = 0;
        pair_t t_p;

        vector_init(&t_v);
        for(i = 0; i < 10; ++i)
        {
            vector_push_back(&t_v, i);
            vector_push_back(&t_v, i);
        }
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        t_p = algo_equal_range(vector_begin(&t_v), vector_end(&t_v), 5);
        printf("5 could get position %d up to %d without break the sorting\n",
            iterator_distance(vector_begin(&t_v), *(iterator_t*)t_p.first) + 1,
            iterator_distance(vector_begin(&t_v), *(iterator_t*)t_p.second) + 1);

        pair_destroy(&t_p);
        vector_destroy(&t_v);
    }
    {
        list_t t_l = create_list(int);
        int i = 0;

        list_init(&t_l);
        for(i = 0; i < 10; ++i)
        {
            list_push_back(&t_l, i);
        }
        algo_for_each(list_begin(&t_l), list_end(&t_l), _print);
        printf("\n");

        if(algo_binary_search(list_begin(&t_l), list_end(&t_l), 5))
        {
            printf("5 is present\n");
        }
        else
        {
            printf("5 isn't present\n");
        }
        if(algo_binary_search(list_begin(&t_l), list_end(&t_l), 42))
        {
            printf("42 is present\n");
        }
        else
        {
            printf("42 isn't present\n");
        }

        list_destroy(&t_l);
    }
    {
        list_t t_l = create_list(int);
        set_t t_s = create_set(int);
        deque_t t_dq = create_deque(int);
        int i = 0;

        list_init(&t_l);
        for(i = 1; i <=6; ++i)
        {
            list_push_back(&t_l, i);
        }
        set_init(&t_s);
        for(i = 3; i <=8; ++i)
        {
            set_insert(&t_s, i);
        }
        deque_init_n(&t_dq, list_size(&t_l) + set_size(&t_s));

        printf("list: ");
        algo_for_each(list_begin(&t_l), list_end(&t_l), _print);
        printf("\n");
        printf("set:  ");
        algo_for_each(set_begin(&t_s), set_end(&t_s), _print);
        printf("\n");

        algo_merge(
            list_begin(&t_l), list_end(&t_l), 
            set_begin(&t_s), set_end(&t_s),
            deque_begin(&t_dq));
        printf("deque: ");
        algo_for_each(deque_begin(&t_dq), deque_end(&t_dq), _print);
        printf("\n");

        list_destroy(&t_l);
        set_destroy(&t_s);
        deque_destroy(&t_dq);
    }
    {
        list_t t_l = create_list(int);
        int i = 0;
        iterator_t t_pos;

        list_init(&t_l);
        for(i = 1; i <= 7; ++i)
        {
            list_push_back(&t_l, i);
        }
        for(i = 1; i <=8; ++i)
        {
            list_push_back(&t_l, i);
        }
        algo_for_each(list_begin(&t_l), list_end(&t_l), _print);
        printf("\n");

        t_pos = algo_find(list_begin(&t_l), list_end(&t_l), 7);
        t_pos = iterator_next(t_pos);
        algo_inplace_merge(list_begin(&t_l), t_pos, list_end(&t_l));
        algo_for_each(list_begin(&t_l), list_end(&t_l), _print);
        printf("\n");

        list_destroy(&t_l);
    }
    {
        list_t t_l = create_list(int);
        vector_t t_v = create_vector(int);
        int i = 0;

        list_init(&t_l);
        for(i = 0; i < 10; ++i)
        {
            list_push_back(&t_l, i);
        }
        printf("list:  ");
        algo_for_each(list_begin(&t_l), list_end(&t_l), _print);
        printf("\n");

        vector_init(&t_v);
        vector_push_back(&t_v, 3);
        vector_push_back(&t_v, 4);
        vector_push_back(&t_v, 7);
        printf("vector: ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        if(algo_includes(
            list_begin(&t_l), list_end(&t_l), vector_begin(&t_v), vector_end(&t_v)))
        {
            printf("all elements of vector are also in list\n");
        }
        else
        {
            printf("not all elements of vector are also in list\n");
        }

        list_destroy(&t_l);
        vector_destroy(&t_v);
    }
    {
        list_t t_l = create_list(int);
        vector_t t_v = create_vector(int);
        deque_t t_dq = create_deque(int);
        iterator_t t_pos;

        list_init(&t_l);
        list_push_back(&t_l, 1);
        list_push_back(&t_l, 2);
        list_push_back(&t_l, 2);
        list_push_back(&t_l, 4);
        list_push_back(&t_l, 6);
        list_push_back(&t_l, 7);
        list_push_back(&t_l, 7);
        list_push_back(&t_l, 9);
        vector_init(&t_v);
        vector_push_back(&t_v, 2);
        vector_push_back(&t_v, 2);
        vector_push_back(&t_v, 2);
        vector_push_back(&t_v, 3);
        vector_push_back(&t_v, 6);
        vector_push_back(&t_v, 6);
        vector_push_back(&t_v, 8);
        vector_push_back(&t_v, 9);
        deque_init_n(&t_dq, list_size(&t_l) + vector_size(&t_v));

        printf("list:                  ");
        algo_for_each(list_begin(&t_l), list_end(&t_l), _print);
        printf("\n");
        printf("vector:                ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        t_pos = algo_merge(
            list_begin(&t_l), list_end(&t_l),
            vector_begin(&t_v), vector_end(&t_v),
            deque_begin(&t_dq));
        printf("merge:                 ");
        algo_for_each(deque_begin(&t_dq), t_pos, _print);
        printf("\n");

        t_pos = algo_set_union(
            list_begin(&t_l), list_end(&t_l),
            vector_begin(&t_v), vector_end(&t_v),
            deque_begin(&t_dq));
        printf("union:                 ");
        algo_for_each(deque_begin(&t_dq), t_pos, _print);
        printf("\n");

        t_pos = algo_set_intersection(
            list_begin(&t_l), list_end(&t_l),
            vector_begin(&t_v), vector_end(&t_v),
            deque_begin(&t_dq));
        printf("intersection:          ");
        algo_for_each(deque_begin(&t_dq), t_pos, _print);
        printf("\n");

        t_pos = algo_set_difference(
            list_begin(&t_l), list_end(&t_l),
            vector_begin(&t_v), vector_end(&t_v),
            deque_begin(&t_dq));
        printf("difference:            ");
        algo_for_each(deque_begin(&t_dq), t_pos, _print);
        printf("\n");

        t_pos = algo_set_symmetric_difference(
            list_begin(&t_l), list_end(&t_l),
            vector_begin(&t_v), vector_end(&t_v),
            deque_begin(&t_dq));
        printf("symmetric difference:  ");
        algo_for_each(deque_begin(&t_dq), t_pos, _print);
        printf("\n");

        list_destroy(&t_l);
        vector_destroy(&t_v);
        deque_destroy(&t_dq);
    }
    {
        vector_t t_v = create_vector(int);
        int i = 0;

        vector_init(&t_v);
        for(i = 3; i <= 7; ++i)
        {
            vector_push_back(&t_v, i);
        }
        for(i = 5; i <= 9; ++i)
        {
            vector_push_back(&t_v, i);
        }
        for(i = 1; i <= 4; ++i)
        {
            vector_push_back(&t_v, i);
        }
        printf("on entry:               ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        algo_make_heap(vector_begin(&t_v), vector_end(&t_v));
        printf("after algo_make_heap(): ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        algo_pop_heap(vector_begin(&t_v), vector_end(&t_v));
        vector_pop_back(&t_v);
        printf("after algo_pop_heap():  ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        vector_push_back(&t_v, 17);
        algo_push_heap(vector_begin(&t_v), vector_end(&t_v));
        printf("after algo_push_heap(): ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        algo_sort_heap(vector_begin(&t_v), vector_end(&t_v));
        printf("after algo_sort_heap(): ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        vector_destroy(&t_v);
    }
    {
        vector_t t_v = create_vector(int);
        list_t t_l = create_list(int);
        int i = 0;
        iterator_t t_min, t_max;

        vector_init(&t_v);
        list_init(&t_l);
        for(i = -2; i <= 7; ++i)
        {
            vector_push_back(&t_v, i);
        }
        for(i = 0; i >= -9; --i)
        {
            list_push_back(&t_l, i);
        }
        printf("vector: ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        printf("list:   ");
        algo_for_each(list_begin(&t_l), list_end(&t_l), _print);
        printf("\n");

        t_min = algo_min(vector_begin(&t_v), list_begin(&t_l));
        printf("minmum between two first: %d\n", *(int*)iterator_get_pointer(t_min));
        t_max = algo_max(vector_begin(&t_v), list_begin(&t_l));
        printf("maxmum between two first: %d\n", *(int*)iterator_get_pointer(t_max));

        t_min = algo_min_if(vector_begin(&t_v), list_begin(&t_l), _absless);
        printf("minmum of absolute value between two first: %d\n",
            *(int*)iterator_get_pointer(t_min));
        t_max = algo_max_if(vector_begin(&t_v), list_begin(&t_l), _absless);
        printf("maxmum of absolute value between two first: %d\n",
            *(int*)iterator_get_pointer(t_max));

        t_min = algo_min_element(vector_begin(&t_v), vector_end(&t_v));
        printf("minmum in vector: %d\n",
            *(int*)iterator_get_pointer(t_min));
        t_max = algo_max_element(vector_begin(&t_v), vector_end(&t_v));
        printf("maxmum in vector: %d\n",
            *(int*)iterator_get_pointer(t_max));

        t_min = algo_min_element(list_begin(&t_l), list_end(&t_l));
        printf("minmum in list: %d\n",
            *(int*)iterator_get_pointer(t_min));
        t_max = algo_max_element(list_begin(&t_l), list_end(&t_l));
        printf("maxmum in list: %d\n",
            *(int*)iterator_get_pointer(t_max));

        t_min = algo_min_element_if(vector_begin(&t_v), vector_end(&t_v), _absless);
        printf("minmum of absolute value in vector: %d\n",
            *(int*)iterator_get_pointer(t_min));
        t_max = algo_max_element_if(vector_begin(&t_v), vector_end(&t_v), _absless);
        printf("maxmum of absolute value in vector: %d\n",
            *(int*)iterator_get_pointer(t_max));

        t_min = algo_min_element_if(list_begin(&t_l), list_end(&t_l), _absless);
        printf("minmum of absolute value in list: %d\n",
            *(int*)iterator_get_pointer(t_min));
        t_max = algo_max_element_if(list_begin(&t_l), list_end(&t_l), _absless);
        printf("maxmum of absolute value in list: %d\n",
            *(int*)iterator_get_pointer(t_max));

        vector_destroy(&t_v);
        list_destroy(&t_l);
    }
    {
        vector_t t_v = create_vector(int);
        list_t t_l = create_list(int);

        vector_init(&t_v);
        list_init(&t_l);
        vector_push_back(&t_v, 3);
        vector_push_back(&t_v, 2);
        vector_push_back(&t_v, 8);
        vector_push_back(&t_v, 7);

        /* case 1 */
        list_push_back(&t_l, 3);
        list_push_back(&t_l, 3);
        list_push_back(&t_l, 3);
        list_push_back(&t_l, 3);
        printf("vector: ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");
        printf("list:   ");
        algo_for_each(list_begin(&t_l), list_end(&t_l), _print);
        printf("\n");
        if(algo_lexicographical_compare(
            vector_begin(&t_v), vector_end(&t_v),
            list_begin(&t_l), list_end(&t_l)))
        {
            printf("algo_lexicographical_compare(): true\n");
        }
        else
        {
            printf("algo_lexicographical_compare(): false\n");
        }
        printf("algo_lexicographical_compare_3way(): %d\n",
            algo_lexicographical_compare_3way(
                vector_begin(&t_v), vector_end(&t_v),
                list_begin(&t_l), list_end(&t_l)));
        /* case 2 */
        list_clear(&t_l);
        list_push_back(&t_l, 3);
        list_push_back(&t_l, 2);
        list_push_back(&t_l, 8);
        list_push_back(&t_l, 7);
        list_push_back(&t_l, 7);
        printf("vector: ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");
        printf("list:   ");
        algo_for_each(list_begin(&t_l), list_end(&t_l), _print);
        printf("\n");
        if(algo_lexicographical_compare(
            vector_begin(&t_v), vector_end(&t_v),
            list_begin(&t_l), list_end(&t_l)))
        {
            printf("algo_lexicographical_compare(): true\n");
        }
        else
        {
            printf("algo_lexicographical_compare(): false\n");
        }
        printf("algo_lexicographical_compare_3way(): %d\n",
            algo_lexicographical_compare_3way(
                vector_begin(&t_v), vector_end(&t_v),
                list_begin(&t_l), list_end(&t_l)));
        /* case 3 */
        list_pop_back(&t_l);
        printf("vector: ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");
        printf("list:   ");
        algo_for_each(list_begin(&t_l), list_end(&t_l), _print);
        printf("\n");
        if(algo_lexicographical_compare(
            vector_begin(&t_v), vector_end(&t_v),
            list_begin(&t_l), list_end(&t_l)))
        {
            printf("algo_lexicographical_compare(): true\n");
        }
        else
        {
            printf("algo_lexicographical_compare(): false\n");
        }
        printf("algo_lexicographical_compare_3way(): %d\n",
            algo_lexicographical_compare_3way(
                vector_begin(&t_v), vector_end(&t_v),
                list_begin(&t_l), list_end(&t_l)));
        /* case 4 */
        list_pop_back(&t_l);
        printf("vector: ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");
        printf("list:   ");
        algo_for_each(list_begin(&t_l), list_end(&t_l), _print);
        printf("\n");
        if(algo_lexicographical_compare(
            vector_begin(&t_v), vector_end(&t_v),
            list_begin(&t_l), list_end(&t_l)))
        {
            printf("algo_lexicographical_compare(): true\n");
        }
        else
        {
            printf("algo_lexicographical_compare(): false\n");
        }
        printf("algo_lexicographical_compare_3way(): %d\n",
            algo_lexicographical_compare_3way(
                vector_begin(&t_v), vector_end(&t_v),
                list_begin(&t_l), list_end(&t_l)));
        /* case 5 */
        list_push_back(&t_l, 5);
        printf("vector: ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");
        printf("list:   ");
        algo_for_each(list_begin(&t_l), list_end(&t_l), _print);
        printf("\n");
        if(algo_lexicographical_compare(
            vector_begin(&t_v), vector_end(&t_v),
            list_begin(&t_l), list_end(&t_l)))
        {
            printf("algo_lexicographical_compare(): true\n");
        }
        else
        {
            printf("algo_lexicographical_compare(): false\n");
        }
        printf("algo_lexicographical_compare_3way(): %d\n",
            algo_lexicographical_compare_3way(
                vector_begin(&t_v), vector_end(&t_v),
                list_begin(&t_l), list_end(&t_l)));

        vector_destroy(&t_v);
        list_destroy(&t_l);
    }
    {
        vector_t t_v = create_vector(int);

        vector_init(&t_v);
        vector_push_back(&t_v, 1);
        vector_push_back(&t_v, 2);
        vector_push_back(&t_v, 3);

        printf("on entry: ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        while(algo_next_permutation(vector_begin(&t_v), vector_end(&t_v)))
        {
            algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
            printf("\n");
        }
        printf("afterward: ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        while(algo_prev_permutation(vector_begin(&t_v), vector_end(&t_v)))
        {
            algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
            printf("\n");
        }
        printf("now: ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");
        while(algo_prev_permutation(vector_begin(&t_v), vector_end(&t_v)))
        {
            algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
            printf("\n");
        }
        printf("afterward: ");
        algo_for_each(vector_begin(&t_v), vector_end(&t_v), _print);
        printf("\n");

        vector_destroy(&t_v);
    }
}

/** local function implementation section **/
static void _print(const void* cpv_input, void* pv_output)
{
    pv_output = NULL;
    printf("%d, ", *(int*)cpv_input);
}
static void _square(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    *(int*)pv_output = *(int*)cpv_input * *(int*)cpv_input;
}
static void _isprime(const void* cpv_input, void* pv_output)
{
    int n_number = *(int*)cpv_input;
    int n_divisor = 0;

    n_number = abs(n_number);

    if(n_number == 0 || n_number == 1)
    {
        *(bool_t*)pv_output = true;
        return;
    }

    for(n_divisor = n_number/2; n_number%n_divisor != 0; --n_divisor)
    {
        continue;
    }

    if(n_divisor == 1)
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}
static void _abcgreat(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    if(((struct abc_t*)cpv_first)->d_key > ((struct abc_t*)cpv_second)->d_key)
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}
static void _print_abc(const void* cpv_input, void* pv_output)
{
    pv_output = NULL;
    printf("(%d, %ld, %f)\n",
        ((struct abc_t*)cpv_input)->n_value,
        ((struct abc_t*)cpv_input)->l_value,
        ((struct abc_t*)cpv_input)->d_key);
}
static void _mod3(const void* cpv_input, void* pv_output)
{
    if(*(int*)cpv_input % 3 == 0)
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}
static void _generate(const void* cpv_input, void* pv_output)
{
    void* pv_tmp = NULL;
    pv_tmp = (void*)cpv_input;

    *(int*)pv_output = 100;
}
static void _plus100(const void* cpv_input, void* pv_output)
{
    pv_output = NULL;
    *(int*)cpv_input += 100;
}
static void _is_even(const void* cpv_input, void* pv_output)
{
    if(*(int*)cpv_input % 2 == 0)
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}
static void _greater3(const void* cpv_input, void* pv_output)
{
    if(*(int*)cpv_input > 3)
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}
static void _doubled(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    if(*(int*)cpv_first * 2 == *(int*)cpv_second)
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}
static void _both_even_or_odd(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    if(*(int*)cpv_first % 2 == *(int*)cpv_second % 2)
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}
static void _check_even(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    if(*(bool_t*)cpv_second)
    {
        if(*(int*)cpv_first %2 == 0)
        {
            *(bool_t*)pv_output = true;
        }
        else
        {
            *(bool_t*)pv_output = false;
        }
    }
    else
    {
        if(*(int*)cpv_first % 2 == 1)
        {
            *(bool_t*)pv_output = true;
        }
        else
        {
            *(bool_t*)pv_output = false;
        }
    }
}
static void _multipiles10(const void* cpv_input, void* pv_output)
{
    *(int*)pv_output = *(int*)cpv_input * 10;
}
static void _fibonacci(const void* cpv_input, void* pv_output)
{
    static int i = 1;
    static int j = 0;
    void* pv_tmp = NULL;
    pv_tmp = (void*)cpv_input;

    *(int*)pv_output = j + i;
    i = j;
    j = *(int*)pv_output;
}
static void _less4(const void* cpv_input, void* pv_output)
{
    if(*(int*)cpv_input < 4)
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}
static void _absless(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    if(abs(*(int*)cpv_first) < abs(*(int*)cpv_second))
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}

/** eof **/

