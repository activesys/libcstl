/*
 *  The implementation of numeric test.
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
#include "cvector.h"
#include "clist.h"
#include "cnumeric.h"
#include "test_numeric.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
void test_numeric(void)
{
    /*_algo_iota                 */
    {
        vector_t* pt_vec = create_vector(int);
        list_t* pt_list = create_list(char);
        size_t t_index = 0;
        iterator_t t_iter;
        if(pt_vec == NULL || pt_list == NULL)
        {
            return;
        }
        vector_init_n(pt_vec, 30);
        for(t_index = 0; t_index < vector_size(pt_vec); ++t_index)
        {
            printf("%d, ", *(int*)vector_at(pt_vec, t_index));
        }
        printf("\n");
        algo_iota(vector_begin(pt_vec), vector_end(pt_vec), -6);
        for(t_index = 0; t_index < vector_size(pt_vec); ++t_index)
        {
            printf("%d, ", *(int*)vector_at(pt_vec, t_index));
        }
        printf("\n");
        algo_iota(iterator_next_n(vector_begin(pt_vec), 5), iterator_next_n(vector_begin(pt_vec), 15), 100);
        for(t_index = 0; t_index < vector_size(pt_vec); ++t_index)
        {
            printf("%d, ", *(int*)vector_at(pt_vec, t_index));
        }
        printf("\n");

        vector_destroy(pt_vec);

        list_init_n(pt_list, 20);
        for(t_iter = list_begin(pt_list); !iterator_equal(t_iter, list_end(pt_list)); t_iter = iterator_next(t_iter))
        {
            printf("%c, ", *(char*)iterator_get_pointer(t_iter));
        }
        printf("\n");
        algo_iota(list_begin(pt_list), list_end(pt_list), 'a');
        for(t_iter = list_begin(pt_list); !iterator_equal(t_iter, list_end(pt_list)); t_iter = iterator_next(t_iter))
        {
            printf("%c, ", *(char*)iterator_get_pointer(t_iter));
        }
        printf("\n");
        algo_iota(iterator_advance(list_begin(pt_list), 3), iterator_advance(list_begin(pt_list), 15), 'A');
        for(t_iter = list_begin(pt_list); !iterator_equal(t_iter, list_end(pt_list)); t_iter = iterator_next(t_iter))
        {
            printf("%c, ", *(char*)iterator_get_pointer(t_iter));
        }
        printf("\n");

        list_destroy(pt_list);
    }
    /*_algo_accumulate           */
    {
        list_t* pt_list = create_list(int);
        size_t t_index = 0;
        int n_result = 0;
        iterator_t t_iter;
        if(pt_list == NULL)
        {
            return;
        }
        list_init(pt_list);
        for(t_index = 0; t_index < 10; ++t_index)
        {
            list_push_back(pt_list, t_index + 1);
        }
        for(t_iter = list_begin(pt_list); !iterator_equal(t_iter, list_end(pt_list)); t_iter = iterator_next(t_iter))
        {
            printf("%d, ", *(int*)iterator_get_pointer(t_iter));
        }
        printf("\n");
        algo_accumulate(list_begin(pt_list), list_end(pt_list), 0, &n_result);
        printf("sum : %d\n", n_result);
        algo_accumulate(list_begin(pt_list), list_end(pt_list), -100, &n_result);
        printf("sum : %d\n", n_result);

        list_destroy(pt_list);
    }
    /*_algo_accumulate_if        */
    /*_algo_inner_product        */
    /*_algo_inner_product_if     */
    /*algo_power                 */
    /*algo_power_if              */
    /*algo_adjacent_difference   */
    /*algo_adjacent_difference_if*/
    /*algo_partial_sum           */
    /*algo_partial_sum_if        */
}

/** local function implementation section **/

/** eof **/

