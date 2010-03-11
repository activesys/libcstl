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
#include "calgorithm.h"
#include "test_numeric.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/
static void _print_int(const void* cpv_input, void* pv_output);
static void _print_char(const void* cpv_input, void* pv_output);

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
void test_numeric(void)
{
    /*_algo_iota                 */
    {
        vector_t* pt_vec = create_vector(int);
        list_t* pt_list = create_list(char);
        if(pt_vec == NULL || pt_list == NULL)
        {
            return;
        }
        vector_init_n(pt_vec, 30);
        algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
        printf("\n");
        algo_iota(vector_begin(pt_vec), vector_end(pt_vec), -6);
        algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
        printf("\n");
        algo_iota(iterator_next_n(vector_begin(pt_vec), 5),
            iterator_next_n(vector_begin(pt_vec), 15), 100);
        algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
        printf("\n");

        vector_destroy(pt_vec);

        list_init_n(pt_list, 20);
        algo_for_each(list_begin(pt_list), list_end(pt_list), _print_char);
        printf("\n");
        algo_iota(list_begin(pt_list), list_end(pt_list), 'a');
        algo_for_each(list_begin(pt_list), list_end(pt_list), _print_char);
        printf("\n");
        algo_iota(iterator_advance(list_begin(pt_list), 3),
            iterator_advance(list_begin(pt_list), 15), 'A');
        algo_for_each(list_begin(pt_list), list_end(pt_list), _print_char);
        printf("\n");

        list_destroy(pt_list);
    }
    /*_algo_accumulate           */
    {
        list_t* pt_list = create_list(int);
        size_t t_index = 0;
        int n_result = 0;
        if(pt_list == NULL)
        {
            return;
        }
        list_init(pt_list);
        for(t_index = 0; t_index < 10; ++t_index)
        {
            list_push_back(pt_list, t_index + 1);
        }
        algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
        printf("\n");
        algo_accumulate(list_begin(pt_list), list_end(pt_list), 0, &n_result);
        printf("sum : %d\n", n_result);
        algo_accumulate(list_begin(pt_list), list_end(pt_list), -100, &n_result);
        printf("sum : %d\n", n_result);

        list_destroy(pt_list);
    }
    /*_algo_accumulate_if        */
    {
        list_t* pt_list = create_list(int);
        size_t t_index = 0;
        int n_result = 0;
        if(pt_list == NULL)
        {
            return;
        }
        list_init(pt_list);
        for(t_index = 0; t_index < 10; ++t_index)
        {
            list_push_back(pt_list, t_index + 1);
        }
        algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
        printf("\n");
        algo_accumulate_if(list_begin(pt_list), list_end(pt_list), 1,
            fun_multiplies_int, &n_result);
        printf("product : %d\n", n_result);
        algo_accumulate_if(list_begin(pt_list), list_end(pt_list), 0,
            fun_multiplies_int, &n_result);
        printf("produc : %d\n", n_result);
        list_destroy(pt_list);
    }
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
static void _print_int(const void* cpv_input, void* pv_output)
{
    pv_output = NULL;
    printf("%d, ", *(int*)cpv_input);
}

static void _print_char(const void* cpv_input, void* pv_output)
{
    pv_output = NULL;
    printf("%c, ", *(char*)cpv_input);
}

/** eof **/

