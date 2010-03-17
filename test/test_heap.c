/*
 *  The implementation of heap test.
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
#include "clist.h"
#include "cvector.h"
#include "cstring.h"
#include "calgorithm.h"
#include "cfunctional.h"
#include "test_hashtable.h"
#include "test_heap.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/
static void _print_int(const void* cpv_input, void* pv_output);
static void _print_hash_sample(const void* cpv_input, void* pv_output);
static void _print_cstl(const void* cpv_input, void* pv_output);
static void _print_string(const void* cpv_input, void* pv_output);

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
void test_heap(void)
{
    /* c built-in type */
    {
        /*algo_make_heap   */
        {
            vector_t* pt_vec = create_vector(int);
            size_t t_index = 0;
            if(pt_vec == NULL)
            {
                return;
            }
            vector_init(pt_vec);

            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            algo_make_heap(vector_begin(pt_vec), vector_end(pt_vec));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            for(t_index = 3; t_index <= 7; ++t_index)
            {
                vector_push_back(pt_vec, t_index);
            }
            for(t_index = 5; t_index <= 9; ++t_index)
            {
                vector_push_back(pt_vec, t_index);
            }
            for(t_index = 1; t_index <= 4; ++t_index)
            {
                vector_push_back(pt_vec, t_index);
            }
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            algo_make_heap(vector_begin(pt_vec), vector_end(pt_vec));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            vector_destroy(pt_vec);
        }
        /*algo_make_heap_if*/
        {
            vector_t* pt_vec = create_vector(int);
            size_t t_index = 0;
            if(pt_vec == NULL)
            {
                return;
            }
            vector_init(pt_vec);

            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            algo_make_heap_if(vector_begin(pt_vec), vector_end(pt_vec), fun_great_int);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            for(t_index = 3; t_index <= 7; ++t_index)
            {
                vector_push_back(pt_vec, t_index);
            }
            for(t_index = 5; t_index <= 9; ++t_index)
            {
                vector_push_back(pt_vec, t_index);
            }
            for(t_index = 1; t_index <= 4; ++t_index)
            {
                vector_push_back(pt_vec, t_index);
            }
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            algo_make_heap_if(vector_begin(pt_vec), vector_end(pt_vec), fun_great_int);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            vector_destroy(pt_vec);
        }
        /*algo_push_heap   */
        {
            vector_t* pt_vec = create_vector(int);
            size_t t_index = 0;
            if(pt_vec == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            algo_push_heap(vector_begin(pt_vec), vector_end(pt_vec));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            for(t_index = 3; t_index <= 7; ++t_index)
            {
                vector_push_back(pt_vec, t_index);
            }
            for(t_index = 5; t_index <= 9; ++t_index)
            {
                vector_push_back(pt_vec, t_index);
            }
            for(t_index = 1; t_index <= 4; ++t_index)
            {
                vector_push_back(pt_vec, t_index);
            }
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            algo_make_heap(vector_begin(pt_vec), vector_end(pt_vec));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            vector_push_back(pt_vec, 7);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            algo_push_heap(vector_begin(pt_vec), vector_end(pt_vec));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            vector_push_back(pt_vec, 17);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            algo_push_heap(vector_begin(pt_vec), vector_end(pt_vec));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            vector_destroy(pt_vec);
        }
        /*algo_push_heap_if*/
        {
            vector_t* pt_vec = create_vector(int);
            size_t t_index = 0;
            if(pt_vec == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            algo_push_heap_if(vector_begin(pt_vec), vector_end(pt_vec), fun_great_int);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            for(t_index = 3; t_index <= 7; ++t_index)
            {
                vector_push_back(pt_vec, t_index);
            }
            for(t_index = 5; t_index <= 9; ++t_index)
            {
                vector_push_back(pt_vec, t_index);
            }
            for(t_index = 1; t_index <= 4; ++t_index)
            {
                vector_push_back(pt_vec, t_index);
            }
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            algo_make_heap_if(vector_begin(pt_vec), vector_end(pt_vec), fun_great_int);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            vector_push_back(pt_vec, 7);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            algo_push_heap_if(vector_begin(pt_vec), vector_end(pt_vec), fun_great_int);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            vector_push_back(pt_vec, 0);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            algo_push_heap_if(vector_begin(pt_vec), vector_end(pt_vec), fun_great_int);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            vector_destroy(pt_vec);
        }
        /*algo_pop_heap    */
        {
            vector_t* pt_vec = create_vector(int);
            size_t t_index = 0;
            if(pt_vec == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            algo_pop_heap(vector_begin(pt_vec), vector_end(pt_vec));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            for(t_index = 3; t_index <= 7; ++t_index)
            {
                vector_push_back(pt_vec, t_index);
            }
            for(t_index = 5; t_index <= 9; ++t_index)
            {
                vector_push_back(pt_vec, t_index);
            }
            for(t_index = 1; t_index <= 4; ++t_index)
            {
                vector_push_back(pt_vec, t_index);
            }
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            algo_make_heap(vector_begin(pt_vec), vector_end(pt_vec));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            algo_pop_heap(vector_begin(pt_vec), vector_end(pt_vec));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            algo_pop_heap(vector_begin(pt_vec), iterator_prev(vector_end(pt_vec)));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            vector_destroy(pt_vec);
        }
        /*algo_pop_heap_if */
        {
            vector_t* pt_vec = create_vector(int);
            size_t t_index = 0;
            if(pt_vec == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            algo_pop_heap_if(vector_begin(pt_vec), vector_end(pt_vec), fun_great_int);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            for(t_index = 3; t_index <= 7; ++t_index)
            {
                vector_push_back(pt_vec, t_index);
            }
            for(t_index = 5; t_index <= 9; ++t_index)
            {
                vector_push_back(pt_vec, t_index);
            }
            for(t_index = 1; t_index <= 4; ++t_index)
            {
                vector_push_back(pt_vec, t_index);
            }
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            algo_make_heap_if(vector_begin(pt_vec), vector_end(pt_vec), fun_great_int);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            algo_pop_heap_if(vector_begin(pt_vec), vector_end(pt_vec), fun_great_int);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            algo_pop_heap_if(vector_begin(pt_vec), iterator_prev(vector_end(pt_vec)), fun_great_int);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            vector_destroy(pt_vec);
        }
        /*algo_sort_heap   */
        {
            vector_t* pt_vec = create_vector(int);
            size_t t_index = 0;
            if(pt_vec == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            algo_sort_heap(vector_begin(pt_vec), vector_end(pt_vec));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            for(t_index = 3; t_index <= 7; ++t_index)
            {
                vector_push_back(pt_vec, t_index);
            }
            for(t_index = 5; t_index <= 9; ++t_index)
            {
                vector_push_back(pt_vec, t_index);
            }
            for(t_index = 1; t_index <= 4; ++t_index)
            {
                vector_push_back(pt_vec, t_index);
            }
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            algo_make_heap(vector_begin(pt_vec), vector_end(pt_vec));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            algo_sort_heap(vector_begin(pt_vec), vector_end(pt_vec));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            vector_destroy(pt_vec);
        }
        /*algo_sort_heap_if*/
        {
            vector_t* pt_vec = create_vector(int);
            size_t t_index = 0;
            if(pt_vec == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            algo_sort_heap_if(vector_begin(pt_vec), vector_end(pt_vec), fun_great_int);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            for(t_index = 3; t_index <= 7; ++t_index)
            {
                vector_push_back(pt_vec, t_index);
            }
            for(t_index = 5; t_index <= 9; ++t_index)
            {
                vector_push_back(pt_vec, t_index);
            }
            for(t_index = 1; t_index <= 4; ++t_index)
            {
                vector_push_back(pt_vec, t_index);
            }
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            algo_make_heap_if(vector_begin(pt_vec), vector_end(pt_vec), fun_great_int);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            algo_sort_heap_if(vector_begin(pt_vec), vector_end(pt_vec), fun_great_int);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            vector_destroy(pt_vec);
        }
        /*algo_is_heap     */
        {
            vector_t* pt_vec = create_vector(int);
            size_t t_index = 0;
            if(pt_vec == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            printf("is heap : %d\n", algo_is_heap(vector_begin(pt_vec), vector_end(pt_vec)));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            for(t_index = 3; t_index <= 7; ++t_index)
            {
                vector_push_back(pt_vec, t_index);
            }
            for(t_index = 5; t_index <= 9; ++t_index)
            {
                vector_push_back(pt_vec, t_index);
            }
            for(t_index = 1; t_index <= 4; ++t_index)
            {
                vector_push_back(pt_vec, t_index);
            }
            printf("is heap : %d\n", algo_is_heap(vector_begin(pt_vec), vector_end(pt_vec)));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            algo_make_heap(vector_begin(pt_vec), vector_end(pt_vec));
            printf("is heap : %d\n", algo_is_heap(vector_begin(pt_vec), vector_end(pt_vec)));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            vector_destroy(pt_vec);
        }
        /*algo_is_heap_if  */
        {
            vector_t* pt_vec = create_vector(int);
            size_t t_index = 0;
            if(pt_vec == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            printf("is heap : %d\n", algo_is_heap_if(
                vector_begin(pt_vec), vector_end(pt_vec), fun_great_int));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            for(t_index = 3; t_index <= 7; ++t_index)
            {
                vector_push_back(pt_vec, t_index);
            }
            for(t_index = 5; t_index <= 9; ++t_index)
            {
                vector_push_back(pt_vec, t_index);
            }
            for(t_index = 1; t_index <= 4; ++t_index)
            {
                vector_push_back(pt_vec, t_index);
            }
            printf("is heap : %d\n", algo_is_heap_if(
                vector_begin(pt_vec), vector_end(pt_vec), fun_great_int));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            algo_make_heap_if(vector_begin(pt_vec), vector_end(pt_vec), fun_great_int);
            printf("is heap : %d\n", algo_is_heap_if(
                vector_begin(pt_vec), vector_end(pt_vec), fun_great_int));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            vector_destroy(pt_vec);
        }
    }
    /* user define type */
    {
        type_register(hash_sample_t, _hash_sample_init, _hash_sample_copy,
            _hash_sample_less, _hash_sample_destroy);
        type_duplicate(hash_sample_t, struct _taghashsample);
        /*algo_make_heap   */
        {
            vector_t* pt_vec = create_vector(hash_sample_t);
            hash_sample_t t_sample;
            if(pt_vec == NULL)
            {
                return;
            }
            vector_init(pt_vec);

            algo_make_heap(vector_begin(pt_vec), vector_end(pt_vec));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_hash_sample);
            printf("\n");

            t_sample._d_first = 45.33;
            t_sample._l_second = 90;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 23.22;
            t_sample._l_second = 10;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 8.09;
            t_sample._l_second = 3444;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 8.33;
            t_sample._l_second = 555;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 444.2;
            t_sample._l_second = 4344;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 90.2;
            t_sample._l_second = 999;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 45.23;
            t_sample._l_second = 909;
            vector_push_back(pt_vec, &t_sample);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_hash_sample);
            printf("\n");

            algo_make_heap(vector_begin(pt_vec), vector_end(pt_vec));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_hash_sample);
            printf("\n");

            vector_destroy(pt_vec);
        }
        /*algo_make_heap_if*/
        {
            vector_t* pt_vec = create_vector(hash_sample_t);
            hash_sample_t t_sample;
            if(pt_vec == NULL)
            {
                return;
            }
            vector_init(pt_vec);

            algo_make_heap_if(vector_begin(pt_vec), vector_end(pt_vec), _hash_sample_great);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_hash_sample);
            printf("\n");

            t_sample._d_first = 45.33;
            t_sample._l_second = 90;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 23.22;
            t_sample._l_second = 10;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 8.09;
            t_sample._l_second = 3444;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 8.33;
            t_sample._l_second = 555;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 444.2;
            t_sample._l_second = 4344;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 90.2;
            t_sample._l_second = 999;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 45.23;
            t_sample._l_second = 909;
            vector_push_back(pt_vec, &t_sample);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_hash_sample);
            printf("\n");

            algo_make_heap_if(vector_begin(pt_vec), vector_end(pt_vec), _hash_sample_great);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_hash_sample);
            printf("\n");

            vector_destroy(pt_vec);
        }
        /*algo_push_heap   */
        {
            vector_t* pt_vec = create_vector(hash_sample_t);
            hash_sample_t t_sample;
            if(pt_vec == NULL)
            {
                return;
            }
            vector_init(pt_vec);

            t_sample._d_first = 45.33;
            t_sample._l_second = 90;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 23.22;
            t_sample._l_second = 10;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 8.09;
            t_sample._l_second = 3444;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 8.33;
            t_sample._l_second = 555;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 444.2;
            t_sample._l_second = 4344;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 90.2;
            t_sample._l_second = 999;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 45.23;
            t_sample._l_second = 909;
            vector_push_back(pt_vec, &t_sample);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_hash_sample);
            printf("\n");

            algo_make_heap(vector_begin(pt_vec), vector_end(pt_vec));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_hash_sample);
            printf("\n");

            t_sample._d_first = 500.0;
            t_sample._l_second = 500;
            vector_push_back(pt_vec, &t_sample);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_hash_sample);
            printf("\n");

            algo_push_heap(vector_begin(pt_vec), vector_end(pt_vec));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_hash_sample);
            printf("\n");

            vector_destroy(pt_vec);
        }
        /*algo_push_heap_if*/
        {
            vector_t* pt_vec = create_vector(hash_sample_t);
            hash_sample_t t_sample;
            if(pt_vec == NULL)
            {
                return;
            }
            vector_init(pt_vec);

            t_sample._d_first = 45.33;
            t_sample._l_second = 90;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 23.22;
            t_sample._l_second = 10;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 8.09;
            t_sample._l_second = 3444;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 8.33;
            t_sample._l_second = 555;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 444.2;
            t_sample._l_second = 4344;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 90.2;
            t_sample._l_second = 999;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 45.23;
            t_sample._l_second = 909;
            vector_push_back(pt_vec, &t_sample);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_hash_sample);
            printf("\n");

            algo_make_heap_if(vector_begin(pt_vec), vector_end(pt_vec), _hash_sample_great);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_hash_sample);
            printf("\n");

            t_sample._d_first = 0.0;
            t_sample._l_second = 500;
            vector_push_back(pt_vec, &t_sample);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_hash_sample);
            printf("\n");

            algo_push_heap_if(vector_begin(pt_vec), vector_end(pt_vec), _hash_sample_great);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_hash_sample);
            printf("\n");

            vector_destroy(pt_vec);
        }
        /*algo_pop_heap    */
        {
            vector_t* pt_vec = create_vector(hash_sample_t);
            hash_sample_t t_sample;
            if(pt_vec == NULL)
            {
                return;
            }
            vector_init(pt_vec);

            t_sample._d_first = 45.33;
            t_sample._l_second = 90;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 23.22;
            t_sample._l_second = 10;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 8.09;
            t_sample._l_second = 3444;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 8.33;
            t_sample._l_second = 555;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 444.2;
            t_sample._l_second = 4344;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 90.2;
            t_sample._l_second = 999;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 45.23;
            t_sample._l_second = 909;
            vector_push_back(pt_vec, &t_sample);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_hash_sample);
            printf("\n");

            algo_make_heap(vector_begin(pt_vec), vector_end(pt_vec));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_hash_sample);
            printf("\n");

            algo_pop_heap(vector_begin(pt_vec), vector_end(pt_vec));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_hash_sample);
            printf("\n");

            vector_destroy(pt_vec);
        }
        /*algo_pop_heap_if */
        {
            vector_t* pt_vec = create_vector(hash_sample_t);
            hash_sample_t t_sample;
            if(pt_vec == NULL)
            {
                return;
            }
            vector_init(pt_vec);

            t_sample._d_first = 45.33;
            t_sample._l_second = 90;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 23.22;
            t_sample._l_second = 10;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 8.09;
            t_sample._l_second = 3444;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 8.33;
            t_sample._l_second = 555;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 444.2;
            t_sample._l_second = 4344;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 90.2;
            t_sample._l_second = 999;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 45.23;
            t_sample._l_second = 909;
            vector_push_back(pt_vec, &t_sample);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_hash_sample);
            printf("\n");

            algo_make_heap_if(vector_begin(pt_vec), vector_end(pt_vec), _hash_sample_great);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_hash_sample);
            printf("\n");

            algo_pop_heap_if(vector_begin(pt_vec), vector_end(pt_vec), _hash_sample_great);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_hash_sample);
            printf("\n");

            vector_destroy(pt_vec);
        }
        /*algo_sort_heap   */
        {
            vector_t* pt_vec = create_vector(hash_sample_t);
            hash_sample_t t_sample;
            if(pt_vec == NULL)
            {
                return;
            }
            vector_init(pt_vec);

            t_sample._d_first = 45.33;
            t_sample._l_second = 90;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 23.22;
            t_sample._l_second = 10;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 8.09;
            t_sample._l_second = 3444;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 8.33;
            t_sample._l_second = 555;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 444.2;
            t_sample._l_second = 4344;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 90.2;
            t_sample._l_second = 999;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 45.23;
            t_sample._l_second = 909;
            vector_push_back(pt_vec, &t_sample);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_hash_sample);
            printf("\n");

            algo_make_heap(vector_begin(pt_vec), vector_end(pt_vec));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_hash_sample);
            printf("\n");

            algo_sort_heap(vector_begin(pt_vec), vector_end(pt_vec));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_hash_sample);
            printf("\n");

            vector_destroy(pt_vec);
        }
        /*algo_sort_heap_if*/
        {
            vector_t* pt_vec = create_vector(hash_sample_t);
            hash_sample_t t_sample;
            if(pt_vec == NULL)
            {
                return;
            }
            vector_init(pt_vec);

            t_sample._d_first = 45.33;
            t_sample._l_second = 90;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 23.22;
            t_sample._l_second = 10;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 8.09;
            t_sample._l_second = 3444;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 8.33;
            t_sample._l_second = 555;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 444.2;
            t_sample._l_second = 4344;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 90.2;
            t_sample._l_second = 999;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 45.23;
            t_sample._l_second = 909;
            vector_push_back(pt_vec, &t_sample);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_hash_sample);
            printf("\n");

            algo_make_heap_if(vector_begin(pt_vec), vector_end(pt_vec), _hash_sample_great);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_hash_sample);
            printf("\n");

            algo_sort_heap_if(vector_begin(pt_vec), vector_end(pt_vec), _hash_sample_great);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_hash_sample);
            printf("\n");

            vector_destroy(pt_vec);
        }
        /*algo_is_heap     */
        {
            vector_t* pt_vec = create_vector(hash_sample_t);
            hash_sample_t t_sample;
            if(pt_vec == NULL)
            {
                return;
            }
            vector_init(pt_vec);

            printf("is heap : %d\n", algo_is_heap(vector_begin(pt_vec), vector_end(pt_vec)));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_hash_sample);
            printf("\n");

            t_sample._d_first = 45.33;
            t_sample._l_second = 90;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 23.22;
            t_sample._l_second = 10;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 8.09;
            t_sample._l_second = 3444;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 8.33;
            t_sample._l_second = 555;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 444.2;
            t_sample._l_second = 4344;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 90.2;
            t_sample._l_second = 999;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 45.23;
            t_sample._l_second = 909;
            vector_push_back(pt_vec, &t_sample);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_hash_sample);
            printf("\n");

            algo_make_heap(vector_begin(pt_vec), vector_end(pt_vec));
            printf("is heap : %d\n", algo_is_heap(vector_begin(pt_vec), vector_end(pt_vec)));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_hash_sample);
            printf("\n");

            vector_destroy(pt_vec);
        }
        /*algo_is_heap_if  */
        {
            vector_t* pt_vec = create_vector(hash_sample_t);
            hash_sample_t t_sample;
            if(pt_vec == NULL)
            {
                return;
            }
            vector_init(pt_vec);

            printf("is heap : %d\n", algo_is_heap_if(
                vector_begin(pt_vec), vector_end(pt_vec), _hash_sample_great));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_hash_sample);
            printf("\n");

            t_sample._d_first = 45.33;
            t_sample._l_second = 90;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 23.22;
            t_sample._l_second = 10;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 8.09;
            t_sample._l_second = 3444;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 8.33;
            t_sample._l_second = 555;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 444.2;
            t_sample._l_second = 4344;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 90.2;
            t_sample._l_second = 999;
            vector_push_back(pt_vec, &t_sample);
            t_sample._d_first = 45.23;
            t_sample._l_second = 909;
            vector_push_back(pt_vec, &t_sample);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_hash_sample);
            printf("\n");

            algo_make_heap_if(vector_begin(pt_vec), vector_end(pt_vec), _hash_sample_great);
            printf("is heap : %d\n", algo_is_heap_if(
                vector_begin(pt_vec), vector_end(pt_vec), _hash_sample_great));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_hash_sample);
            printf("\n");

            vector_destroy(pt_vec);
        }
    }
    /* cstl builtin type */
    {
        /*algo_make_heap   */
        {
            vector_t* pt_vec = create_vector(list_t<int>);
            list_t* pt_list = create_list(int);
            if(pt_vec == NULL || pt_list == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            list_init(pt_list);

            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_cstl);
            printf("\n");

            list_push_back(pt_list, 56);
            list_push_back(pt_list, 22);
            list_push_back(pt_list, 90);
            vector_push_back(pt_vec, pt_list);
            list_clear(pt_list);
            list_push_back(pt_list, -8);
            vector_push_back(pt_vec, pt_list);
            list_clear(pt_list);
            list_push_back(pt_list, 8);
            list_push_back(pt_list, 22);
            list_push_back(pt_list, 45);
            list_push_back(pt_list, 4);
            vector_push_back(pt_vec, pt_list);
            list_clear(pt_list);
            list_push_back(pt_list, 9);
            list_push_back(pt_list, 45);
            list_push_back(pt_list, 3);
            vector_push_back(pt_vec, pt_list);
            list_clear(pt_list);
            list_push_back(pt_list, -5);
            list_push_back(pt_list, -6);
            vector_push_back(pt_vec, pt_list);
            list_clear(pt_list);
            list_push_back(pt_list, 2);
            list_push_back(pt_list, 3);
            vector_push_back(pt_vec, pt_list);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_cstl);
            printf("\n");
            algo_make_heap(vector_begin(pt_vec), vector_end(pt_vec));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_cstl);
            printf("\n");

            vector_destroy(pt_vec);
            list_destroy(pt_list);
        }
        /*algo_make_heap_if*/
        /*algo_push_heap   */
        /*algo_push_heap_if*/
        /*algo_pop_heap    */
        /*algo_pop_heap_if */
        /*algo_sort_heap   */
        /*algo_sort_heap_if*/
        /*algo_is_heap     */
        /*algo_is_heap_if  */
    }
    /* c-string type */
    {
    }
    /*algo_make_heap   */
    /*algo_make_heap_if*/
    /*algo_push_heap   */
    /*algo_push_heap_if*/
    /*algo_pop_heap    */
    /*algo_pop_heap_if */
    /*algo_sort_heap   */
    /*algo_sort_heap_if*/
    /*algo_is_heap     */
    /*algo_is_heap_if  */
}

/** local function implementation section **/
static void _print_int(const void* cpv_input, void* pv_output)
{
    pv_output = NULL;
    printf("%d, ", *(int*)cpv_input);
}
static void _print_hash_sample(const void* cpv_input, void* pv_output)
{
    hash_sample_t* pt_sample = (hash_sample_t*)cpv_input;
    pv_output = NULL;
    printf("<%lf, %ld>, ", pt_sample->_d_first, pt_sample->_l_second);
}
static void _print_cstl(const void* cpv_input, void* pv_output)
{
    iterator_t t_iter;
    list_t* pt_list = (list_t*)cpv_input;
    pv_output = NULL;
    printf("[");
    for(t_iter = list_begin(pt_list);
        !iterator_equal(t_iter, list_end(pt_list));
        t_iter = iterator_next(t_iter))
    {
        printf("%d, ", *(int*)iterator_get_pointer(t_iter));
    }
    printf("]\n");
}
static void _print_string(const void* cpv_input, void* pv_output)
{
    string_t* pt_string = (string_t*)cpv_input;
    pv_output = NULL;
    string_output(pt_string, stdout);
    printf(", ");
}

/** eof **/

