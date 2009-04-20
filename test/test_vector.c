/*
 *  The implementation of vector test.
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
 *  Author Email: activesys.wb@gmail.com
 *                activesys@sina.com.cn
 */

/** include section **/
#include <stdio.h>

#include "cvector.h"
#include "cutility.h"
#include "calgorithm.h"
#include "test_vector.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/
static void _print_char(const void* cpv_input, void* pv_output);

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
void test_vector(void)
{
    {
        size_t i = 0;
        vector_t t_v = create_vector(int);

        vector_init(&t_v);
        for(i = 0; i < 6; ++i)
        {
            vector_push_back(&t_v, i);
        }

        for(i = 0; i < vector_size(&t_v); ++i)
        {
            printf("%d, ", *(int*)vector_at(&t_v, i));
        }
        printf("\n");

        vector_destroy(&t_v);
    }
    {
        vector_t t_v = create_vector(pair_t);
        pair_t t_p1 = create_pair(int, int);
        pair_t t_p2 = create_pair(int, int);
        pair_t t_p3 = create_pair(int, int);
        iterator_t t_i;

        vector_init(&t_v);
        pair_init_elem(&t_p1, 1, 1);
        vector_push_back(&t_v, t_p1);
        pair_init_elem(&t_p2, 2, 2);
        vector_push_back(&t_v, t_p2);
        pair_init_elem(&t_p3, 3, 3);
        vector_push_back(&t_v, t_p3);

        for(t_i = vector_begin(&t_v);
            !iterator_equal(&t_i, vector_end(&t_v));
            iterator_next(&t_i))
        {
            printf("<%d, %d>\n",
                *(int*)((pair_t*)iterator_get_pointer(&t_i))->first,
                *(int*)((pair_t*)iterator_get_pointer(&t_i))->second);
            pair_destroy((pair_t*)iterator_get_pointer(&t_i));
        }
        vector_destroy(&t_v);
    }
    {
        vector_t t_v = create_vector(char);

        vector_init_n(&t_v, 30);
        strcpy((char*)vector_at(&t_v, 0), "Hello, World!");
        printf("%s\n", (char*)vector_front(&t_v));

        vector_destroy(&t_v);
    }
    {
        vector_t t_sentence = create_vector(char);
        vector_t t_always = create_vector(char);

        vector_init(&t_sentence);
        vector_push_back(&t_sentence, 'H');
        vector_push_back(&t_sentence, 'e');
        vector_push_back(&t_sentence, 'l');
        vector_push_back(&t_sentence, 'l');
        vector_push_back(&t_sentence, 'o');
        vector_push_back(&t_sentence, ',');
        vector_push_back(&t_sentence, ' ');
        vector_push_back(&t_sentence, 'W');
        vector_push_back(&t_sentence, 'o');
        vector_push_back(&t_sentence, 'r');
        vector_push_back(&t_sentence, 'l');
        vector_push_back(&t_sentence, 'd');
        vector_push_back(&t_sentence, '!');
        algo_for_each(vector_begin(&t_sentence), vector_end(&t_sentence), _print_char);       
        printf("\n");

        printf("max_size: %u\n", vector_max_size(&t_sentence));
        printf("size:     %u\n", vector_size(&t_sentence));
        printf("capacity: %u\n", vector_capacity(&t_sentence));

        vector_init(&t_always);
        vector_push_back(&t_always, ' ');
        vector_push_back(&t_always, 'a');
        vector_push_back(&t_always, 'l');
        vector_push_back(&t_always, 'w');
        vector_push_back(&t_always, 'a');
        vector_push_back(&t_always, 'y');
        vector_push_back(&t_always, 's');
        vector_insert_range(
            &t_sentence,
            algo_find(vector_begin(&t_sentence), vector_end(&t_sentence), '!'),
            vector_begin(&t_always),
            vector_end(&t_always));
        *(char*)vector_back(&t_sentence) = '?';
        algo_for_each(vector_begin(&t_sentence), vector_end(&t_sentence), _print_char);       
        printf("\n");

        printf("max_size: %u\n", vector_max_size(&t_sentence));
        printf("size:     %u\n", vector_size(&t_sentence));
        printf("capacity: %u\n", vector_capacity(&t_sentence));

        vector_destroy(&t_sentence);
        vector_destroy(&t_always);
    }
    {
        vector_t t_v = create_vector(int);
        vector_iterator_t t_i;
        iterator_t t_begin;
        random_access_iterator_t t_last;
        int i = 0;

        vector_init(&t_v);
        for(i = -3; i <= 9; ++i)
        {
            vector_push_back(&t_v, i);
        }
        t_i = vector_end(&t_v);
        printf("number/distance: %d, %d\n",
            iterator_minus(&t_i, vector_begin(&t_v)),
            iterator_distance(vector_begin(&t_v), vector_end(&t_v)));

        for(t_i = vector_begin(&t_v);
            iterator_less(&t_i, vector_end(&t_v));
            iterator_next(&t_i))
        {
            printf("%d, ", *(int*)iterator_get_pointer(&t_i));
        }
        printf("\n");

        t_begin = vector_begin(&t_v);
        for(i = 0; i < (int)vector_size(&t_v); ++i)
        {
            printf("%d, ", *(int*)iterator_at(&t_begin, i));
        }
        printf("\n");

        t_last = vector_end(&t_v);
        iterator_prev(&t_last);
        for(t_i = vector_begin(&t_v);
            iterator_less(&t_i, t_last);
            iterator_next_n(&t_i, 2))
        {
            printf("%d, ", *(int*)iterator_get_pointer(&t_i));
        }
        printf("\n");

        vector_destroy(&t_v);
    }
}

/** local function implementation section **/
static void _print_char(const void* cpv_input, void* pv_output)
{
    pv_output = NULL;
    printf("%c", *(char*)cpv_input);
}

/** eof **/

