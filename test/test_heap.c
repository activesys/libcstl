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
#include "calgorithm.h"
#include "cfunctional.h"
#include "test_heap.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/
static void _print_int(const void* cpv_input, void* pv_output);

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
        /*algo_is_heap_if  */
    }
    /* user define type */
    {
    }
    /* string_t type */
    {
    }
    /* c-string type */
    {
    }
    /*algo_push_heap   */
    /*algo_push_heap_if*/
    /*algo_pop_heap    */
    /*algo_pop_heap_if */
    /*algo_sort_heap   */
    /*algo_sort_heap_if*/
    /*algo_make_heap   */
    /*algo_make_heap_if*/
    /*algo_is_heap     */
    /*algo_is_heap_if  */
}

/** local function implementation section **/
static void _print_int(const void* cpv_input, void* pv_output)
{
    pv_output = NULL;
    printf("%d, ", *(int*)cpv_input);
}

/** eof **/

