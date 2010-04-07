/*
 *  The implementation of algorithm test.
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
#include <assert.h>
#include <stdio.h>
#include "cvector.h"
#include "clist.h"
#include "cdeque.h"
#include "calgorithm.h"
#include "cfunctional.h"
#include "cnumeric.h"
#include "test_algo.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/
static void _print_int(const void* cpv_input, void* pv_output);
static void _plus100(const void* cpv_input, void* pv_output);
static void _is_even(const void* cpv_input, void* pv_output);
static void _mod3(const void* cpv_input, void* pv_output);
static void _doubled(const void* cpv_first, const void* cpv_second, void* pv_output);
static void _check_even(const void* cpv_first, const void* cpv_second, void* pv_output);

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
void test_algo(void)
{
    /* c built-in type */
    {
        /*_algo_count                             @23000*/
        /*algo_count_if                           @23028*/
        {
            vector_t* pt_vec = create_vector(int);
            int i = 0;
            if(pt_vec == NULL)
            {
                return;
            }

            vector_init(pt_vec);

            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            printf("the number of equal to 4: %u.\n",
                algo_count(vector_begin(pt_vec), vector_end(pt_vec), 4));
            printf("the number of even: %u.\n",
                algo_count_if(vector_begin(pt_vec), vector_end(pt_vec), _is_even));

            for(i = 1; i < 10; ++i)
            {
                vector_push_back(pt_vec, i);
                vector_push_back(pt_vec, i - 3);
            }
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            printf("the number of equal to 4: %u.\n",
                algo_count(vector_begin(pt_vec), vector_end(pt_vec), 4));
            printf("the number of even: %u.\n",
                algo_count_if(vector_begin(pt_vec), vector_end(pt_vec), _is_even));

            vector_destroy(pt_vec);
        }
        /*_algo_find                      */
        /*algo_find_if                    */
        {
            vector_t* pt_vec = create_vector(int);
            iterator_t t_iter;
            int i = 0;
            if(pt_vec == NULL)
            {
                return;
            }

            vector_init(pt_vec);

            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            t_iter = algo_find(vector_begin(pt_vec), vector_end(pt_vec), 4);
            if(iterator_equal(t_iter, vector_end(pt_vec)))
            {
                printf("The element 4 is not in the vector.\n");
            }
            else
            {
                printf("The element 4 is already exist.\n");
            }

            for(i = 1; i < 10; ++i)
            {
                vector_push_back(pt_vec, i);
                vector_push_back(pt_vec, i - 3);
            }
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            t_iter = algo_find(vector_begin(pt_vec), vector_end(pt_vec), 4);
            if(iterator_equal(t_iter, vector_end(pt_vec)))
            {
                printf("The element 4 is not in the vector.\n");
            }
            else
            {
                printf("The element 4 is already exist.\n");
            }

            t_iter = algo_find(iterator_next(t_iter), vector_end(pt_vec), 4);
            if(iterator_equal(t_iter, vector_end(pt_vec)))
            {
                printf("The second 4 is not in the vector.\n");
            }
            else
            {
                printf("The second 4 is already exist.\n");
            }

            vector_clear(pt_vec);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            t_iter = algo_find_if(vector_begin(pt_vec), vector_end(pt_vec), _is_even);
            if(iterator_equal(t_iter, vector_end(pt_vec)))
            {
                printf("no even element.\n");
            }
            else
            {
                printf("The first even element is: %d.\n",
                    *(int*)iterator_get_pointer(t_iter));
            }

            for(i = 1; i < 10; ++i)
            {
                vector_push_back(pt_vec, i);
            }
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            t_iter = algo_find_if(vector_begin(pt_vec), vector_end(pt_vec), _is_even);
            if(iterator_equal(t_iter, vector_end(pt_vec)))
            {
                printf("no even element.\n");
            }
            else
            {
                printf("The first even element is: %d.\n",
                    *(int*)iterator_get_pointer(t_iter));
            }
            t_iter = algo_find_if(iterator_next(t_iter), vector_end(pt_vec), _is_even);
            if(iterator_equal(t_iter, vector_end(pt_vec)))
            {
                printf("no even element.\n");
            }
            else
            {
                printf("The second even element is: %d.\n",
                    *(int*)iterator_get_pointer(t_iter));
            }

            vector_destroy(pt_vec);
        }
        /*_algo_search_n                  */
        /*_algo_search_n_if               */
        {
            deque_t* pt_deq = create_deque(int);
            iterator_t t_iter;
            int i = 0;

            if(pt_deq == NULL)
            {
                return;
            }

            deque_init(pt_deq);

            for(i = 0; i < 10; ++i)
            {
                deque_push_back(pt_deq, i);
            }
            algo_for_each(deque_begin(pt_deq), deque_end(pt_deq), _print_int);
            printf("\n");

            t_iter = algo_search_n(deque_begin(pt_deq), deque_end(pt_deq), 4, 3);
            if(iterator_equal(t_iter, deque_end(pt_deq)))
            {
                printf("no four consecutive elements with value 3 found.\n");
            }
            else
            {
                printf("four consecutive elements with value 3 start with %d. element.\n",
                    iterator_distance(deque_begin(pt_deq), t_iter) + 1);
            }

            t_iter = algo_search_n_if(deque_begin(pt_deq), deque_end(pt_deq),
                4, 3, fun_greater_int);
            if(iterator_equal(t_iter, deque_end(pt_deq)))
            {
                printf("no four consecutive elements with value > 3 found.\n");
            }
            else
            {
                printf("four consecutive elements with value > 3 start with %d. element.\n",
                    iterator_distance(deque_begin(pt_deq), t_iter) + 1);
            }

            deque_destroy(pt_deq);
        }
        /*algo_replace                    */
        /*algo_replace_copy               */
        /*_algo_replace_if                */
        /*_algo_replace_copy_if           */
        {
            vector_t* pt_vec = create_vector(int);
            list_t* pt_list = create_list(int);
            int i = 0;
            if(pt_vec == NULL || pt_list == NULL)
            {
                return;
            }

            vector_init(pt_vec);
            list_init_n(pt_list, 20);

            for(i = 0; i < 10; ++i)
            {
                vector_push_back(pt_vec, i);
            }
            for(i = 0; i < 10; ++i)
            {
                vector_push_back(pt_vec, i);
            }
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            algo_replace(vector_begin(pt_vec), vector_end(pt_vec), 6, 42);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            algo_replace_if(vector_begin(pt_vec), vector_end(pt_vec), _is_even, -3);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            algo_replace_copy(vector_begin(pt_vec), vector_end(pt_vec),
                list_begin(pt_list), -3, 100);
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");
            algo_iota(vector_begin(pt_vec), vector_end(pt_vec), 1);
            algo_replace_copy_if(vector_begin(pt_vec), vector_end(pt_vec),
                list_begin(pt_list), _is_even, 0);
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");

            vector_destroy(pt_vec);
            list_destroy(pt_list);
        }
        /*_algo_lower_bound               */
        /*_algo_lower_bound_if            */
        /*_algo_upper_bound               */
        /*_algo_upper_bound_if            */
        {
            vector_t* pt_vec = create_vector(int);
            iterator_t t_lower, t_upper;
            if(pt_vec == NULL)
            {
                return;
            }

            vector_init_n(pt_vec, 15);

            printf("\n");
            algo_iota(vector_begin(pt_vec), vector_end(pt_vec), 1);
            algo_iota(iterator_next_n(vector_begin(pt_vec), 7), vector_end(pt_vec), 5);
            algo_iota(iterator_next_n(vector_begin(pt_vec), 12), vector_end(pt_vec), 3);
            algo_sort(vector_begin(pt_vec), vector_end(pt_vec));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            t_lower = algo_lower_bound(vector_begin(pt_vec), vector_end(pt_vec), 0);
            t_upper = algo_upper_bound(vector_begin(pt_vec), vector_end(pt_vec), 0);
            if(!iterator_equal(t_lower, vector_end(pt_vec)) && !iterator_equal(t_upper, vector_end(pt_vec)))
            {
                printf("lower : %d, upper : %d.\n",
                    *(int*)iterator_get_pointer(t_lower), *(int*)iterator_get_pointer(t_upper));
            }
            t_lower = algo_lower_bound(vector_begin(pt_vec), vector_end(pt_vec), 2);
            t_upper = algo_upper_bound(vector_begin(pt_vec), vector_end(pt_vec), 2);
            if(!iterator_equal(t_lower, vector_end(pt_vec)) && !iterator_equal(t_upper, vector_end(pt_vec)))
            {
                printf("lower : %d, upper : %d.\n",
                    *(int*)iterator_get_pointer(t_lower), *(int*)iterator_get_pointer(t_upper));
            }
            t_lower = algo_lower_bound(vector_begin(pt_vec), vector_end(pt_vec), 5);
            t_upper = algo_upper_bound(vector_begin(pt_vec), vector_end(pt_vec), 5);
            if(!iterator_equal(t_lower, vector_end(pt_vec)) && !iterator_equal(t_upper, vector_end(pt_vec)))
            {
                printf("lower : %d, upper : %d.\n",
                    *(int*)iterator_get_pointer(t_lower), *(int*)iterator_get_pointer(t_upper));
            }
            t_lower = algo_lower_bound(vector_begin(pt_vec), vector_end(pt_vec), 15);
            t_upper = algo_upper_bound(vector_begin(pt_vec), vector_end(pt_vec), 15);
            if(!iterator_equal(t_lower, vector_end(pt_vec)) && !iterator_equal(t_upper, vector_end(pt_vec)))
            {
                printf("lower : %d, upper : %d.\n",
                    *(int*)iterator_get_pointer(t_lower), *(int*)iterator_get_pointer(t_upper));
            }

            algo_sort_if(vector_begin(pt_vec), vector_end(pt_vec), fun_greater_int);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            t_lower = algo_lower_bound_if(vector_begin(pt_vec), vector_end(pt_vec), 0, fun_greater_int);
            t_upper = algo_upper_bound_if(vector_begin(pt_vec), vector_end(pt_vec), 0, fun_greater_int);
            if(!iterator_equal(t_lower, vector_end(pt_vec)) && !iterator_equal(t_upper, vector_end(pt_vec)))
            {
                printf("lower : %d, upper : %d.\n",
                    *(int*)iterator_get_pointer(t_lower), *(int*)iterator_get_pointer(t_upper));
            }
            t_lower = algo_lower_bound_if(vector_begin(pt_vec), vector_end(pt_vec), 2, fun_greater_int);
            t_upper = algo_upper_bound_if(vector_begin(pt_vec), vector_end(pt_vec), 2, fun_greater_int);
            if(!iterator_equal(t_lower, vector_end(pt_vec)) && !iterator_equal(t_upper, vector_end(pt_vec)))
            {
                printf("lower : %d, upper : %d.\n",
                    *(int*)iterator_get_pointer(t_lower), *(int*)iterator_get_pointer(t_upper));
            }
            t_lower = algo_lower_bound_if(vector_begin(pt_vec), vector_end(pt_vec), 5, fun_greater_int);
            t_upper = algo_upper_bound_if(vector_begin(pt_vec), vector_end(pt_vec), 5, fun_greater_int);
            if(!iterator_equal(t_lower, vector_end(pt_vec)) && !iterator_equal(t_upper, vector_end(pt_vec)))
            {
                printf("lower : %d, upper : %d.\n",
                    *(int*)iterator_get_pointer(t_lower), *(int*)iterator_get_pointer(t_upper));
            }
            t_lower = algo_lower_bound_if(vector_begin(pt_vec), vector_end(pt_vec), 15, fun_greater_int);
            t_upper = algo_upper_bound_if(vector_begin(pt_vec), vector_end(pt_vec), 15, fun_greater_int);
            if(!iterator_equal(t_lower, vector_end(pt_vec)) && !iterator_equal(t_upper, vector_end(pt_vec)))
            {
                printf("lower : %d, upper : %d.\n",
                    *(int*)iterator_get_pointer(t_lower), *(int*)iterator_get_pointer(t_upper));
            }

            printf("\n");
            vector_destroy(pt_vec);
        }
        /*_algo_equal_range               */
        /*_algo_equal_range_if            */
        {
            vector_t* pt_vec = create_vector(int);
            range_t t_range;
            if(pt_vec == NULL)
            {
                return;
            }

            vector_init_n(pt_vec, 15);

            printf("\n");
            algo_iota(vector_begin(pt_vec), vector_end(pt_vec), 1);
            algo_iota(iterator_next_n(vector_begin(pt_vec), 7), vector_end(pt_vec), 5);
            algo_iota(iterator_next_n(vector_begin(pt_vec), 12), vector_end(pt_vec), 3);
            algo_sort(vector_begin(pt_vec), vector_end(pt_vec));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            t_range = algo_equal_range(vector_begin(pt_vec), vector_end(pt_vec), 0);
            if(!iterator_equal(t_range.it_begin, vector_end(pt_vec)) && !iterator_equal(t_range.it_end, vector_end(pt_vec)))
            {
                printf("lower : %d, upper : %d.\n",
                    *(int*)iterator_get_pointer(t_range.it_begin), *(int*)iterator_get_pointer(t_range.it_end));
            }
            t_range = algo_equal_range(vector_begin(pt_vec), vector_end(pt_vec), 2);
            if(!iterator_equal(t_range.it_begin, vector_end(pt_vec)) && !iterator_equal(t_range.it_end, vector_end(pt_vec)))
            {
                printf("lower : %d, upper : %d.\n",
                    *(int*)iterator_get_pointer(t_range.it_begin), *(int*)iterator_get_pointer(t_range.it_end));
            }
            t_range = algo_equal_range(vector_begin(pt_vec), vector_end(pt_vec), 5);
            if(!iterator_equal(t_range.it_begin, vector_end(pt_vec)) && !iterator_equal(t_range.it_end, vector_end(pt_vec)))
            {
                printf("lower : %d, upper : %d.\n",
                    *(int*)iterator_get_pointer(t_range.it_begin), *(int*)iterator_get_pointer(t_range.it_end));
            }
            t_range = algo_equal_range(vector_begin(pt_vec), vector_end(pt_vec), 15);
            if(!iterator_equal(t_range.it_begin, vector_end(pt_vec)) && !iterator_equal(t_range.it_end, vector_end(pt_vec)))
            {
                printf("lower : %d, upper : %d.\n",
                    *(int*)iterator_get_pointer(t_range.it_begin), *(int*)iterator_get_pointer(t_range.it_end));
            }

            algo_sort_if(vector_begin(pt_vec), vector_end(pt_vec), fun_greater_int);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            t_range = algo_equal_range_if(vector_begin(pt_vec), vector_end(pt_vec), 0, fun_greater_int);
            if(!iterator_equal(t_range.it_begin, vector_end(pt_vec)) && !iterator_equal(t_range.it_end, vector_end(pt_vec)))
            {
                printf("lower : %d, upper : %d.\n",
                    *(int*)iterator_get_pointer(t_range.it_begin), *(int*)iterator_get_pointer(t_range.it_end));
            }
            t_range = algo_equal_range_if(vector_begin(pt_vec), vector_end(pt_vec), 2, fun_greater_int);
            if(!iterator_equal(t_range.it_begin, vector_end(pt_vec)) && !iterator_equal(t_range.it_end, vector_end(pt_vec)))
            {
                printf("lower : %d, upper : %d.\n",
                    *(int*)iterator_get_pointer(t_range.it_begin), *(int*)iterator_get_pointer(t_range.it_end));
            }
            t_range = algo_equal_range_if(vector_begin(pt_vec), vector_end(pt_vec), 5, fun_greater_int);
            if(!iterator_equal(t_range.it_begin, vector_end(pt_vec)) && !iterator_equal(t_range.it_end, vector_end(pt_vec)))
            {
                printf("lower : %d, upper : %d.\n",
                    *(int*)iterator_get_pointer(t_range.it_begin), *(int*)iterator_get_pointer(t_range.it_end));
            }
            t_range = algo_equal_range_if(vector_begin(pt_vec), vector_end(pt_vec), 15, fun_greater_int);
            if(!iterator_equal(t_range.it_begin, vector_end(pt_vec)) && !iterator_equal(t_range.it_end, vector_end(pt_vec)))
            {
                printf("lower : %d, upper : %d.\n",
                    *(int*)iterator_get_pointer(t_range.it_begin), *(int*)iterator_get_pointer(t_range.it_end));
            }

            printf("\n");
            vector_destroy(pt_vec);
        }
        /*_algo_binary_search             */
        /*_algo_binary_search_if          */
        {
            vector_t* pt_vec = create_vector(int);
            if(pt_vec == NULL)
            {
                return;
            }

            vector_init_n(pt_vec, 10);

            algo_iota(vector_begin(pt_vec), vector_end(pt_vec), 1);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            if(algo_binary_search(vector_begin(pt_vec), vector_end(pt_vec), 5))
            {
                printf("5 is present.\n");
            }
            else
            {
                printf("5 is not present.\n");
            }
            if(algo_binary_search(vector_begin(pt_vec), vector_end(pt_vec), 15))
            {
                printf("15 is present.\n");
            }
            else
            {
                printf("15 is not present.\n");
            }

            algo_sort_if(vector_begin(pt_vec), vector_end(pt_vec), fun_greater_int);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            if(algo_binary_search_if(vector_begin(pt_vec), vector_end(pt_vec), 5, fun_greater_int))
            {
                printf("greater than 5 is present.\n");
            }
            else
            {
                printf("greater than 5 is not present.\n");
            }
            if(algo_binary_search_if(vector_begin(pt_vec), vector_end(pt_vec), 10, fun_greater_int))
            {
                printf("greater than 10 is present.\n");
            }
            else
            {
                printf("greater than 10 is not present.\n");
            }

            vector_destroy(pt_vec);
        }
        /*algo_set_union                  */
        /*algo_set_union_if               */
        /*algo_set_intersection           */
        /*algo_set_intersection_if        */
        /*algo_set_difference             */
        /*algo_set_difference_if          */
        /*algo_set_symmetric_difference   */
        /*algo_set_symmetric_difference_if*/
        {
            vector_t* pt_vec = create_vector(int);
            list_t* pt_list = create_list(int);
            deque_t* pt_deq = create_deque(int);
            iterator_t t_iter;
            if(pt_vec == NULL || pt_list == NULL || pt_deq == NULL)
            {
                return;
            }

            vector_init(pt_vec);
            vector_push_back(pt_vec, 1);
            vector_push_back(pt_vec, 2);
            vector_push_back(pt_vec, 2);
            vector_push_back(pt_vec, 4);
            vector_push_back(pt_vec, 6);
            vector_push_back(pt_vec, 7);
            vector_push_back(pt_vec, 7);
            vector_push_back(pt_vec, 9);
            list_init(pt_list);
            list_push_back(pt_list, 2);
            list_push_back(pt_list, 2);
            list_push_back(pt_list, 2);
            list_push_back(pt_list, 3);
            list_push_back(pt_list, 6);
            list_push_back(pt_list, 6);
            list_push_back(pt_list, 8);
            list_push_back(pt_list, 9);
            deque_init_n(pt_deq, vector_size(pt_vec) + list_size(pt_list));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");
            algo_merge(vector_begin(pt_vec), vector_end(pt_vec), list_begin(pt_list), list_end(pt_list),
                deque_begin(pt_deq));
            printf("merge:\n");
            algo_for_each(deque_begin(pt_deq), deque_end(pt_deq), _print_int);
            printf("\n");

            t_iter = algo_set_union(vector_begin(pt_vec), vector_end(pt_vec), list_begin(pt_list),
                    list_end(pt_list), deque_begin(pt_deq));
            printf("union:\n");
            algo_for_each(deque_begin(pt_deq), t_iter, _print_int);
            printf("\n");
            t_iter = algo_set_intersection(vector_begin(pt_vec), vector_end(pt_vec), list_begin(pt_list),
                list_end(pt_list), deque_begin(pt_deq));
            printf("intersection:\n");
            algo_for_each(deque_begin(pt_deq), t_iter, _print_int);
            printf("\n");
            t_iter = algo_set_difference(vector_begin(pt_vec), vector_end(pt_vec), list_begin(pt_list),
                list_end(pt_list), deque_begin(pt_deq));
            printf("difference:\n");
            algo_for_each(deque_begin(pt_deq), t_iter, _print_int);
            printf("\n");
            t_iter = algo_set_symmetric_difference(vector_begin(pt_vec), vector_end(pt_vec), list_begin(pt_list),
                list_end(pt_list), deque_begin(pt_deq));
            printf("symmetric difference:\n");
            algo_for_each(deque_begin(pt_deq), t_iter, _print_int);
            printf("\n");

            algo_reverse(vector_begin(pt_vec), vector_end(pt_vec));
            list_reverse(pt_list);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");
            algo_merge_if(vector_begin(pt_vec), vector_end(pt_vec), list_begin(pt_list), list_end(pt_list),
                deque_begin(pt_deq), fun_greater_int);
            printf("merge:\n");
            algo_for_each(deque_begin(pt_deq), deque_end(pt_deq), _print_int);
            printf("\n");

            t_iter = algo_set_union_if(vector_begin(pt_vec), vector_end(pt_vec), list_begin(pt_list),
                    list_end(pt_list), deque_begin(pt_deq), fun_greater_int);
            printf("union:\n");
            algo_for_each(deque_begin(pt_deq), t_iter, _print_int);
            printf("\n");
            t_iter = algo_set_intersection_if(vector_begin(pt_vec), vector_end(pt_vec), list_begin(pt_list),
                list_end(pt_list), deque_begin(pt_deq), fun_greater_int);
            printf("intersection:\n");
            algo_for_each(deque_begin(pt_deq), t_iter, _print_int);
            printf("\n");
            t_iter = algo_set_difference_if(vector_begin(pt_vec), vector_end(pt_vec), list_begin(pt_list),
                list_end(pt_list), deque_begin(pt_deq), fun_greater_int);
            printf("difference:\n");
            algo_for_each(deque_begin(pt_deq), t_iter, _print_int);
            printf("\n");
            t_iter = algo_set_symmetric_difference_if(vector_begin(pt_vec), vector_end(pt_vec), list_begin(pt_list),
                list_end(pt_list), deque_begin(pt_deq), fun_greater_int);
            printf("symmetric difference:\n");
            algo_for_each(deque_begin(pt_deq), t_iter, _print_int);
            printf("\n");

            vector_destroy(pt_vec);
            list_destroy(pt_list);
            deque_destroy(pt_deq);
        }
        /*algo_adjacent_find              */
        /*algo_adjacent_find_if           */
        {
            vector_t* pt_vec = create_vector(int);
            iterator_t t_iter;
            if(pt_vec == NULL)
            {
                return;
            }
            vector_init(pt_vec);

            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            t_iter = algo_adjacent_find(vector_begin(pt_vec), vector_end(pt_vec));
            if(iterator_equal(t_iter, vector_end(pt_vec)))
            {
                printf("no two elements with equal value.\n");
            }
            else
            {
                printf("first two elements with equal value have position %d.\n",
                    iterator_distance(vector_begin(pt_vec), t_iter) + 1);
            }

            t_iter = algo_adjacent_find_if(vector_begin(pt_vec), vector_end(pt_vec), _doubled);
            if(iterator_equal(t_iter, vector_end(pt_vec)))
            {
                printf("no two elements with second value twice the first.\n");
            }
            else
            {
                printf("first two elements with second value twice the first have pos %d.\n",
                    iterator_distance(vector_begin(pt_vec), t_iter) + 1);
            }

            vector_push_back(pt_vec, 1);
            vector_push_back(pt_vec, 3);
            vector_push_back(pt_vec, 2);
            vector_push_back(pt_vec, 4);
            vector_push_back(pt_vec, 5);
            vector_push_back(pt_vec, 5);
            vector_push_back(pt_vec, 0);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            t_iter = algo_adjacent_find(vector_begin(pt_vec), vector_end(pt_vec));
            if(iterator_equal(t_iter, vector_end(pt_vec)))
            {
                printf("no two elements with equal value.\n");
            }
            else
            {
                printf("first two elements with equal value have position %d.\n",
                    iterator_distance(vector_begin(pt_vec), t_iter) + 1);
            }

            t_iter = algo_adjacent_find_if(vector_begin(pt_vec), vector_end(pt_vec), _doubled);
            if(iterator_equal(t_iter, vector_end(pt_vec)))
            {
                printf("no two elements with second value twice the first.\n");
            }
            else
            {
                printf("first two elements with second value twice the first have pos %d.\n",
                    iterator_distance(vector_begin(pt_vec), t_iter) + 1);
            }

            vector_destroy(pt_vec);
        }
        /*algo_find_first_of              */
        /*algo_find_first_of_if           */
        {
            vector_t* pt_vec = create_vector(int);
            list_t* pt_list = create_list(int);
            iterator_t t_iter;
            int i = 0;
            if(pt_vec == NULL || pt_list == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            list_init(pt_list);

            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");

            t_iter = algo_find_first_of(vector_begin(pt_vec), vector_end(pt_vec),
                list_begin(pt_list), list_end(pt_list));
            if(iterator_equal(t_iter, vector_begin(pt_vec)))
            {
                printf("no element in vector for serach.\n");
            }
            else
            {
                printf("first elment in vector for search is element %d.\n",
                    iterator_distance(vector_begin(pt_vec), t_iter) + 1);
            }
            t_iter = algo_find_first_of_if(vector_begin(pt_vec), vector_end(pt_vec),
                list_begin(pt_list), list_end(pt_list), _doubled);
            if(iterator_equal(t_iter, vector_begin(pt_vec)))
            {
                printf("no element in vector for serach.\n");
            }
            else
            {
                printf("first elment in vector for search is element %d.\n",
                    iterator_distance(vector_begin(pt_vec), t_iter) + 1);
            }

            for(i = 0; i < 10; ++i)
            {
                vector_push_back(pt_vec, i);
            }
            for(i = 3; i < 6; ++i)
            {
                list_push_back(pt_list, i);
            }
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");

            t_iter = algo_find_first_of(vector_begin(pt_vec), vector_end(pt_vec),
                list_begin(pt_list), list_end(pt_list));
            if(iterator_equal(t_iter, vector_begin(pt_vec)))
            {
                printf("no element in vector for serach.\n");
            }
            else
            {
                printf("first elment in vector for search is element %d.\n",
                    iterator_distance(vector_begin(pt_vec), t_iter) + 1);
            }
            t_iter = algo_find_first_of_if(vector_begin(pt_vec), vector_end(pt_vec),
                list_begin(pt_list), list_end(pt_list), _doubled);
            if(iterator_equal(t_iter, vector_begin(pt_vec)))
            {
                printf("no element in vector for serach.\n");
            }
            else
            {
                printf("first elment in vector for search is element %d.\n",
                    iterator_distance(vector_begin(pt_vec), t_iter) + 1);
            }

            algo_reverse(vector_begin(pt_vec), vector_end(pt_vec));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");

            t_iter = algo_find_first_of(vector_begin(pt_vec), vector_end(pt_vec),
                list_begin(pt_list), list_end(pt_list));
            if(iterator_equal(t_iter, vector_begin(pt_vec)))
            {
                printf("no element in vector for serach.\n");
            }
            else
            {
                printf("first elment in vector for search is element %d.\n",
                    iterator_distance(vector_begin(pt_vec), t_iter) + 1);
            }
            t_iter = algo_find_first_of_if(vector_begin(pt_vec), vector_end(pt_vec),
                list_begin(pt_list), list_end(pt_list), _doubled);
            if(iterator_equal(t_iter, vector_begin(pt_vec)))
            {
                printf("no element in vector for serach.\n");
            }
            else
            {
                printf("first elment in vector for search is element %d.\n",
                    iterator_distance(vector_begin(pt_vec), t_iter) + 1);
            }

            vector_destroy(pt_vec);
            list_destroy(pt_list);
        }
        /*algo_for_each                   */
        {
            vector_t* pt_vec = create_vector(int);
            int i = 0;
            if(pt_vec == NULL)
            {
                return;
            }

            vector_init(pt_vec);

            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _plus100);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            for(i = 0; i < 10; ++i)
            {
                vector_push_back(pt_vec, i);
            }

            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _plus100);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            vector_destroy(pt_vec);
        }
        /*algo_search                     */
        /*algo_search_if                  */
        {
            vector_t* pt_vec = create_vector(int);
            deque_t* pt_deq = create_deque(int);
            list_t* pt_list = create_list(bool_t);
            iterator_t t_iter;
            int i = 0;

            if(pt_vec == NULL || pt_deq == NULL || pt_list == NULL)
            {
                return;
            }

            vector_init(pt_vec);
            deque_init(pt_deq);
            list_init(pt_list);

            for(i = 0; i < 10; ++i)
            {
                vector_push_back(pt_vec, i);
            }
            for(i = 0; i < 7; ++i)
            {
                vector_push_back(pt_vec, i);
            }
            for(i = 3; i < 7; ++i)
            {
                deque_push_back(pt_deq, i);
            }
            list_push_back(pt_list, true);
            list_push_back(pt_list, false);
            list_push_back(pt_list, true);

            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            algo_for_each(deque_begin(pt_deq), deque_end(pt_deq), _print_int);
            printf("\n");

            t_iter = algo_search(vector_begin(pt_vec), vector_end(pt_vec),
                deque_begin(pt_deq), deque_end(pt_deq));
            while(!iterator_equal(t_iter, vector_end(pt_vec)))
            {
                printf("sub find with element %d\n",
                    iterator_distance(vector_begin(pt_vec), t_iter) + 1);
                t_iter = iterator_next(t_iter);
                t_iter = algo_search(t_iter, vector_end(pt_vec),
                    deque_begin(pt_deq), deque_end(pt_deq));
            }

            t_iter = algo_search_if(vector_begin(pt_vec), vector_end(pt_vec),
                list_begin(pt_list), list_end(pt_list), _check_even);
            while(!iterator_equal(t_iter, vector_end(pt_vec)))
            {
                printf("sub find with element %d\n",
                    iterator_distance(vector_begin(pt_vec), t_iter) + 1);
                t_iter = iterator_next(t_iter);
                t_iter = algo_search_if(t_iter, vector_end(pt_vec),
                    list_begin(pt_list), list_end(pt_list), _check_even);
            }

            vector_destroy(pt_vec);
            deque_destroy(pt_deq);
            list_destroy(pt_list);
        }
        /*algo_search_end                 */
        /*algo_search_end_if              */
        /*algo_find_end                   */
        /*algo_find_end_if                */
        {
            vector_t* pt_vec = create_vector(int);
            deque_t* pt_deq = create_deque(int);
            list_t* pt_list = create_list(bool_t);
            iterator_t t_iter;
            iterator_t t_end;
            int i = 0;

            if(pt_vec == NULL || pt_deq == NULL || pt_list == NULL)
            {
                return;
            }

            vector_init(pt_vec);
            deque_init(pt_deq);
            list_init(pt_list);

            for(i = 0; i < 10; ++i)
            {
                vector_push_back(pt_vec, i);
            }
            for(i = 0; i < 7; ++i)
            {
                vector_push_back(pt_vec, i);
            }
            for(i = 3; i < 7; ++i)
            {
                deque_push_back(pt_deq, i);
            }
            list_push_back(pt_list, true);
            list_push_back(pt_list, false);
            list_push_back(pt_list, true);

            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            algo_for_each(deque_begin(pt_deq), deque_end(pt_deq), _print_int);
            printf("\n");

            t_iter = algo_search_end(vector_begin(pt_vec), vector_end(pt_vec),
                deque_begin(pt_deq), deque_end(pt_deq));
            t_end = vector_end(pt_vec);
            while(!iterator_equal(t_iter, t_end))
            {
                printf("sub find with element %d\n",
                    iterator_distance(vector_begin(pt_vec), t_iter) + 1);
                t_end = t_iter;
                t_iter = algo_search_end(vector_begin(pt_vec), t_end,
                    deque_begin(pt_deq), deque_end(pt_deq));
            }

            t_iter = algo_search_end_if(vector_begin(pt_vec), vector_end(pt_vec),
                list_begin(pt_list), list_end(pt_list), _check_even);
            t_end = vector_end(pt_vec);
            while(!iterator_equal(t_iter, t_end))
            {
                printf("sub find with element %d\n",
                    iterator_distance(vector_begin(pt_vec), t_iter) + 1);
                t_end = t_iter;
                t_iter = algo_search_end_if(vector_begin(pt_vec), t_end,
                    list_begin(pt_list), list_end(pt_list), _check_even);
            }

            vector_destroy(pt_vec);
            deque_destroy(pt_deq);
            list_destroy(pt_list);
        }
        /*algo_generate                   */
        /*algo_generate_n                 */
        {
            vector_t* pt_vec = create_vector(int);
            if(pt_vec == NULL)
            {
                return;
            }

            vector_init_n(pt_vec, 10);

            algo_iota(vector_begin(pt_vec), vector_end(pt_vec), 1);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            algo_generate(vector_begin(pt_vec), vector_end(pt_vec), _plus100);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            algo_generate_n(vector_begin(pt_vec), 5, _plus100);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            vector_destroy(pt_vec);
        }
        /*algo_includes                   */
        /*algo_includes_if                */
        {
            vector_t* pt_vec = create_vector(int);
            deque_t* pt_deq = create_deque(int);
            list_t* pt_list = create_list(int);
            if(pt_vec == NULL || pt_deq == NULL || pt_list == NULL)
            {
                return;
            }
            vector_init_n(pt_vec, 10);
            deque_init(pt_deq);
            list_init(pt_list);

            algo_iota(vector_begin(pt_vec), vector_end(pt_vec), 1);
            deque_push_back(pt_deq, 3);
            deque_push_back(pt_deq, 4);
            deque_push_back(pt_deq, 7);
            list_push_back(pt_list, 6);
            list_push_back(pt_list, 9);
            list_push_back(pt_list, 12);

            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            algo_for_each(deque_begin(pt_deq), deque_end(pt_deq), _print_int);
            printf("\n");
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");

            if(algo_includes(vector_begin(pt_vec), vector_end(pt_vec),
                    deque_begin(pt_deq), deque_end(pt_deq)))
            {
                printf("includes.\n");
            }
            else
            {
                printf("not includes.\n");
            }
            if(algo_includes(vector_begin(pt_vec), vector_end(pt_vec),
                    list_begin(pt_list), list_end(pt_list)))
            {
                printf("includes.\n");
            }
            else
            {
                printf("not includes.\n");
            }

            algo_reverse(vector_begin(pt_vec), vector_end(pt_vec));
            algo_reverse(deque_begin(pt_deq), deque_end(pt_deq));
            list_reverse(pt_list);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            algo_for_each(deque_begin(pt_deq), deque_end(pt_deq), _print_int);
            printf("\n");
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");

            if(algo_includes_if(vector_begin(pt_vec), vector_end(pt_vec),
                    deque_begin(pt_deq), deque_end(pt_deq), fun_greater_int))
            {
                printf("includes.\n");
            }
            else
            {
                printf("not includes.\n");
            }
            if(algo_includes_if(vector_begin(pt_vec), vector_end(pt_vec),
                    list_begin(pt_list), list_end(pt_list), fun_greater_int))
            {
                printf("includes.\n");
            }
            else
            {
                printf("not includes.\n");
            }

            vector_destroy(pt_vec);
            deque_destroy(pt_deq);
            list_destroy(pt_list);
        }
        /*algo_max_element                */
        /*algo_max_element_if             */
        /*algo_min_element                */
        /*algo_min_element_if             */
        {
            vector_t* pt_vec = create_vector(int);
            iterator_t t_max, t_min;
            if(pt_vec == NULL)
            {
                return;
            }

            vector_init_n(pt_vec, 15);
            algo_iota(vector_begin(pt_vec), vector_end(pt_vec), -4);
            algo_random_shuffle(vector_begin(pt_vec), vector_end(pt_vec));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            t_max = algo_max_element(vector_begin(pt_vec), vector_end(pt_vec));
            t_min = algo_min_element(vector_begin(pt_vec), vector_end(pt_vec));
            printf("max: %d, min: %d.\n", *(int*)iterator_get_pointer(t_max),
                *(int*)iterator_get_pointer(t_min));
            t_max = algo_max_element_if(vector_begin(pt_vec), vector_end(pt_vec), fun_greater_int);
            t_min = algo_min_element_if(vector_begin(pt_vec), vector_end(pt_vec), fun_greater_int);
            printf("max: %d, min: %d.\n", *(int*)iterator_get_pointer(t_max),
                *(int*)iterator_get_pointer(t_min));
            
            vector_destroy(pt_vec);
        }
        /*algo_merge                      */
        /*algo_merge_if                   */
        {
            vector_t* pt_vec = create_vector(int);
            list_t* pt_list = create_list(int);
            deque_t* pt_deq = create_deque(int);
            if(pt_vec == NULL || pt_list == NULL || pt_deq == NULL)
            {
                return;
            }
            vector_init_n(pt_vec, 10);
            list_init_n(pt_list, 5);
            deque_init_n(pt_deq, 15);

            printf("\n");
            algo_iota(vector_begin(pt_vec), vector_end(pt_vec), 1);
            algo_iota(list_begin(pt_list), list_end(pt_list), 4);
            algo_merge(vector_begin(pt_vec), vector_end(pt_vec),
                list_begin(pt_list), list_end(pt_list), deque_begin(pt_deq));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");
            algo_for_each(deque_begin(pt_deq), deque_end(pt_deq), _print_int);
            printf("\n");

            algo_sort_if(vector_begin(pt_vec), vector_end(pt_vec), fun_greater_int);
            list_sort_if(pt_list, fun_greater_int);
            algo_merge_if(vector_begin(pt_vec), vector_end(pt_vec),
                list_begin(pt_list), list_end(pt_list), deque_begin(pt_deq), fun_greater_int);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");
            algo_for_each(deque_begin(pt_deq), deque_end(pt_deq), _print_int);
            printf("\n");

            printf("\n");
            vector_destroy(pt_vec);
            list_destroy(pt_list);
            deque_destroy(pt_deq);
        }
        /*algo_partition                  */
        /*algo_stable_partition           */
        {
            vector_t* pt_vec1 = create_vector(int);
            vector_t* pt_vec2 = create_vector(int);
            if(pt_vec1 == NULL || pt_vec2 == NULL)
            {
                return;
            }

            vector_init_n(pt_vec1, 10);
            vector_init_n(pt_vec2, 10);

            algo_iota(vector_begin(pt_vec1), vector_end(pt_vec1), 10);
            algo_iota(vector_begin(pt_vec2), vector_end(pt_vec2), 10);
            algo_for_each(vector_begin(pt_vec1), vector_end(pt_vec1), _print_int);
            printf("\n");
            algo_for_each(vector_begin(pt_vec2), vector_end(pt_vec2), _print_int);
            printf("\n");

            algo_partition(vector_begin(pt_vec1), vector_end(pt_vec1), _is_even);
            algo_for_each(vector_begin(pt_vec1), vector_end(pt_vec1), _print_int);
            printf("\n");
            algo_stable_partition(vector_begin(pt_vec2), vector_end(pt_vec2), _is_even);
            algo_for_each(vector_begin(pt_vec2), vector_end(pt_vec2), _print_int);
            printf("\n");

            vector_destroy(pt_vec1);
            vector_destroy(pt_vec2);
        }
        /*_algo_remove_copy               */
        /*_algo_remove                    */
        /*algo_remove_if                  */
        /*algo_remove_copy_if             */
        {
            vector_t* pt_vec = create_vector(int);
            list_t* pt_list = create_list(int);
            iterator_t t_iter;

            if(pt_vec == NULL || pt_list == NULL)
            {
                return;
            }

            vector_init_n(pt_vec, 20);
            list_init_n(pt_list, 20);

            algo_iota(vector_begin(pt_vec), vector_end(pt_vec), 2);
            algo_iota(iterator_next_n(vector_begin(pt_vec), 4), vector_end(pt_vec), 4);
            algo_iota(iterator_next_n(vector_begin(pt_vec), 12), vector_end(pt_vec), 1);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            t_iter = algo_remove(vector_begin(pt_vec), vector_end(pt_vec), 100);
            algo_for_each(vector_begin(pt_vec), t_iter, _print_int);
            printf("\n");
            t_iter = algo_remove(vector_begin(pt_vec), vector_end(pt_vec), 5);
            algo_for_each(vector_begin(pt_vec), t_iter, _print_int);
            printf("\n");

            algo_iota(vector_begin(pt_vec), vector_end(pt_vec), 2);
            algo_iota(iterator_next_n(vector_begin(pt_vec), 4), vector_end(pt_vec), 4);
            algo_iota(iterator_next_n(vector_begin(pt_vec), 12), vector_end(pt_vec), 1);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            t_iter = algo_remove_if(vector_begin(pt_vec), vector_end(pt_vec), _is_even);
            algo_for_each(vector_begin(pt_vec), t_iter, _print_int);
            printf("\n");

            algo_iota(vector_begin(pt_vec), vector_end(pt_vec), 2);
            algo_iota(iterator_next_n(vector_begin(pt_vec), 4), vector_end(pt_vec), 4);
            algo_iota(iterator_next_n(vector_begin(pt_vec), 12), vector_end(pt_vec), 1);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            t_iter = algo_remove_copy(vector_begin(pt_vec), vector_end(pt_vec),
                list_begin(pt_list), 3);
            algo_for_each(list_begin(pt_list), t_iter, _print_int);
            printf("\n");

            algo_iota(vector_begin(pt_vec), vector_end(pt_vec), 2);
            algo_iota(iterator_next_n(vector_begin(pt_vec), 4), vector_end(pt_vec), 4);
            algo_iota(iterator_next_n(vector_begin(pt_vec), 12), vector_end(pt_vec), 1);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            t_iter = algo_remove_copy_if(vector_begin(pt_vec), vector_end(pt_vec),
                list_begin(pt_list), _mod3);
            algo_for_each(list_begin(pt_list), t_iter, _print_int);
            printf("\n");

            vector_destroy(pt_vec);
            list_destroy(pt_list);
        }
        /*algo_reverse                    */
        /*algo_reverse_copy               */
        {
            vector_t* pt_vec = create_vector(int);
            list_t* pt_list = create_list(int);
            int i = 0;
            if(pt_vec == NULL || pt_list == NULL)
            {
                return;
            }

            vector_init(pt_vec);
            for(i = 0; i < 10; ++i)
            {
                vector_push_back(pt_vec, i);
            }
            list_init_n(pt_list, vector_size(pt_vec));

            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            algo_reverse(vector_begin(pt_vec), vector_end(pt_vec));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            algo_reverse(iterator_next_n(vector_begin(pt_vec), 3),
                iterator_prev_n(vector_end(pt_vec), 3));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            algo_reverse_copy(vector_begin(pt_vec), vector_end(pt_vec), list_begin(pt_list));
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");

            vector_destroy(pt_vec);
            list_destroy(pt_list);
        }
        /*algo_rotate                     */
        /*algo_rotate_copy                */
        {
            vector_t* pt_vec = create_vector(int);
            list_t* pt_list = create_list(int);

            if(pt_vec == NULL || pt_list == NULL)
            {
                return;
            }

            vector_init_n(pt_vec, 10);
            list_init_n(pt_list, 10);

            algo_iota(vector_begin(pt_vec), vector_end(pt_vec), 0);

            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            algo_rotate(vector_begin(pt_vec), vector_begin(pt_vec), vector_end(pt_vec));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            algo_rotate(vector_begin(pt_vec), iterator_next_n(vector_begin(pt_vec), 3),
                vector_end(pt_vec));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            algo_rotate(vector_begin(pt_vec), iterator_next_n(vector_begin(pt_vec), 5),
                vector_end(pt_vec));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            algo_rotate(vector_begin(pt_vec), vector_end(pt_vec), vector_end(pt_vec));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            algo_rotate_copy(vector_begin(pt_vec), iterator_next_n(vector_begin(pt_vec), 5),
                vector_end(pt_vec), list_begin(pt_list));
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");

            vector_destroy(pt_vec);
            list_destroy(pt_list);
        }
        /*algo_swap_ranges                */
        {
            vector_t* pt_vec = create_vector(int);
            deque_t* pt_deq = create_deque(int);
            int i = 0;
            if(pt_vec == NULL || pt_deq == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            deque_init(pt_deq);

            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            algo_for_each(deque_begin(pt_deq), deque_end(pt_deq), _print_int);
            printf("\n");
            algo_swap_ranges(vector_begin(pt_vec), vector_end(pt_vec), deque_begin(pt_deq));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            algo_for_each(deque_begin(pt_deq), deque_end(pt_deq), _print_int);
            printf("\n");

            for(i = 0; i < 10; ++i)
            {
                vector_push_back(pt_vec, i);
            }
            for(i = 20; i < 35; ++i)
            {
                deque_push_back(pt_deq, i);
            }

            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            algo_for_each(deque_begin(pt_deq), deque_end(pt_deq), _print_int);
            printf("\n");
            algo_swap_ranges(vector_begin(pt_vec), vector_end(pt_vec), deque_begin(pt_deq));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            algo_for_each(deque_begin(pt_deq), deque_end(pt_deq), _print_int);
            printf("\n");

            vector_destroy(pt_vec);
            deque_destroy(pt_deq);
        }
        /*algo_transform                  */
        /*algo_transform_binary           */
        {
            vector_t* pt_vec = create_vector(int);
            list_t* pt_list = create_list(int);
            deque_t* pt_deq = create_deque(int);
            int i = 0;
            if(pt_vec == NULL || pt_list == NULL || pt_deq == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            list_init_n(pt_list, 10);
            deque_init_n(pt_deq, 10);

            for(i = 1; i <= 10; ++i)
            {
                vector_push_back(pt_vec, i);
            }

            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            algo_transform(vector_begin(pt_vec), vector_end(pt_vec),
                vector_begin(pt_vec), fun_negate_int);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            algo_transform(vector_begin(pt_vec), vector_end(pt_vec),
                list_begin(pt_list), _plus100);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            algo_transform_binary(vector_begin(pt_vec), vector_end(pt_vec),
                vector_begin(pt_vec), vector_begin(pt_vec), fun_multiplies_int);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            algo_transform_binary(vector_begin(pt_vec), vector_end(pt_vec),
                vector_begin(pt_vec), list_begin(pt_list), fun_plus_int);
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");
            algo_transform_binary(vector_begin(pt_vec), vector_end(pt_vec),
                list_begin(pt_list), deque_begin(pt_deq), fun_minus_int);
            algo_for_each(deque_begin(pt_deq), deque_end(pt_deq), _print_int);
            printf("\n");

            vector_destroy(pt_vec);
            list_destroy(pt_list);
            deque_destroy(pt_deq);
        }
        /*algo_unique                     */
        /*algo_unique_if                  */
        /*algo_unique_copy                */
        /*algo_unique_copy_if             */
        {
            vector_t* pt_vec1 = create_vector(int);
            vector_t* pt_vec2 = create_vector(int);
            list_t* pt_list = create_list(int);
            iterator_t t_iter;

            if(pt_vec1 == NULL || pt_vec2 == NULL || pt_list == NULL)
            {
                return;
            }

            vector_init(pt_vec1);
            vector_push_back(pt_vec1, 1);
            vector_push_back(pt_vec1, 4);
            vector_push_back(pt_vec1, 4);
            vector_push_back(pt_vec1, 6);
            vector_push_back(pt_vec1, 1);
            vector_push_back(pt_vec1, 2);
            vector_push_back(pt_vec1, 2);
            vector_push_back(pt_vec1, 3);
            vector_push_back(pt_vec1, 1);
            vector_push_back(pt_vec1, 6);
            vector_push_back(pt_vec1, 6);
            vector_push_back(pt_vec1, 6);
            vector_push_back(pt_vec1, 3);
            vector_push_back(pt_vec1, 3);
            vector_push_back(pt_vec1, 5);
            vector_push_back(pt_vec1, 7);
            vector_push_back(pt_vec1, 5);
            vector_push_back(pt_vec1, 4);
            vector_push_back(pt_vec1, 4);
            vector_push_back(pt_vec1, 4);
            vector_init_copy(pt_vec2, pt_vec1);
            list_init_n(pt_list, vector_size(pt_vec1));

            algo_for_each(vector_begin(pt_vec1), vector_end(pt_vec1), _print_int);
            printf("\n");
            t_iter = algo_unique(vector_begin(pt_vec2), vector_end(pt_vec2));
            algo_for_each(vector_begin(pt_vec2), t_iter, _print_int);
            printf("\n");
            vector_assign(pt_vec2, pt_vec1);
            t_iter = algo_unique_if(vector_begin(pt_vec2), vector_end(pt_vec2),
                fun_greater_int);
            algo_for_each(vector_begin(pt_vec2), t_iter, _print_int);
            printf("\n");
            vector_assign(pt_vec2, pt_vec1);
            t_iter = algo_unique_copy(vector_begin(pt_vec2), vector_end(pt_vec2),
                list_begin(pt_list));
            algo_for_each(list_begin(pt_list), t_iter, _print_int);
            printf("\n");
            vector_assign(pt_vec2, pt_vec1);
            t_iter = algo_unique_copy_if(vector_begin(pt_vec2), vector_end(pt_vec2),
                list_begin(pt_list), fun_greater_int);
            algo_for_each(list_begin(pt_list), t_iter, _print_int);
            printf("\n");

            vector_destroy(pt_vec1);
            vector_destroy(pt_vec2);
            list_destroy(pt_list);
        }
        /*algo_next_permutation           */
        /*algo_next_permutation_if        */
        /*algo_prev_permutation           */
        /*algo_prev_permutation_if        */
        {
            vector_t* pt_vec = create_vector(int);
            if(pt_vec == NULL)
            {
                return;
            }

            vector_init(pt_vec);
            vector_push_back(pt_vec, 1);
            vector_push_back(pt_vec, 2);
            vector_push_back(pt_vec, 3);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            while(algo_next_permutation(vector_begin(pt_vec), vector_end(pt_vec)))
            {
                algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
                printf("\n");
            }
            printf("afterward:\n");
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            while(algo_prev_permutation(vector_begin(pt_vec), vector_end(pt_vec)))
            {
                algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
                printf("\n");
            }
            printf("now:\n");
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            while(algo_prev_permutation(vector_begin(pt_vec), vector_end(pt_vec)))
            {
                algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
                printf("\n");
            }
            printf("afterward:\n");
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            while(algo_next_permutation_if(vector_begin(pt_vec), vector_end(pt_vec), fun_greater_int))
            {
                algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
                printf("\n");
            }
            printf("afterward:\n");
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            while(algo_prev_permutation_if(vector_begin(pt_vec), vector_end(pt_vec), fun_greater_int))
            {
                algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
                printf("\n");
            }
            printf("now:\n");
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            while(algo_prev_permutation_if(vector_begin(pt_vec), vector_end(pt_vec), fun_greater_int))
            {
                algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
                printf("\n");
            }
            printf("afterward:\n");
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            vector_destroy(pt_vec);
        }
        /*algo_random_shuffle             */
        /*algo_random_shuffle_if          */
        {
            vector_t* pt_vec = create_vector(int);
            if(pt_vec == NULL)
            {
                return;
            }

            vector_init_n(pt_vec, 10);

            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            algo_random_shuffle(vector_begin(pt_vec), vector_end(pt_vec));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            algo_iota(vector_begin(pt_vec), vector_end(pt_vec), 1);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            algo_random_shuffle(vector_begin(pt_vec), vector_end(pt_vec));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            algo_sort(vector_begin(pt_vec), vector_end(pt_vec));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            algo_random_shuffle(vector_begin(pt_vec), vector_end(pt_vec));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            vector_destroy(pt_vec);
        }
        /*algo_random_sample              */
        /*algo_random_sample_if           */
        /*algo_random_sample_n            */
        /*algo_random_sample_n_if         */
        {
            vector_t* pt_vec = create_vector(int);
            deque_t* pt_deq = create_deque(int);
            if(pt_vec == NULL || pt_deq == NULL)
            {
                return;
            }

            vector_init_n(pt_vec, 15);
            deque_init_n(pt_deq, 10);

            algo_iota(vector_begin(pt_vec), vector_end(pt_vec), 1);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            algo_random_sample(vector_begin(pt_vec), vector_end(pt_vec),
                deque_begin(pt_deq), deque_end(pt_deq));
            algo_for_each(deque_begin(pt_deq), deque_end(pt_deq), _print_int);
            printf("\n");

            deque_resize(pt_deq, 20);
            algo_random_sample(vector_begin(pt_vec), vector_end(pt_vec),
                deque_begin(pt_deq), deque_end(pt_deq));
            algo_for_each(deque_begin(pt_deq), deque_end(pt_deq), _print_int);
            printf("\n");

            algo_random_sample_n(vector_begin(pt_vec), vector_end(pt_vec),
                deque_begin(pt_deq), 5);
            algo_for_each(deque_begin(pt_deq), deque_end(pt_deq), _print_int);
            printf("\n");

            vector_destroy(pt_vec);
            deque_destroy(pt_deq);
        }
        /*algo_partial_sort               */
        /*algo_partial_sort_if            */
        /*algo_partial_sort_copy          */
        /*algo_partial_sort_copy_if       */
        {
            vector_t* pt_vec1 = create_vector(int);
            vector_t* pt_vec2 = create_vector(int);
            deque_t* pt_deq = create_deque(int);
            iterator_t t_iter;
            if(pt_vec1 == NULL || pt_vec2 == NULL || pt_deq == NULL)
            {
                return;
            }

            vector_init_n(pt_vec1, 20);
            vector_init_n(pt_vec2, 10);
            deque_init_n(pt_deq, 30);

            algo_iota(vector_begin(pt_vec1), vector_end(pt_vec1), 1);
            algo_iota(iterator_next_n(vector_begin(pt_vec1), 7), vector_end(pt_vec1), 1);
            algo_iota(iterator_next_n(vector_begin(pt_vec1), 11), vector_end(pt_vec1), 2);
            printf("\n");
            algo_for_each(vector_begin(pt_vec1), vector_end(pt_vec1), _print_int);
            printf("\n");

            algo_partial_sort(vector_begin(pt_vec1), vector_begin(pt_vec1),
                vector_end(pt_vec1));
            algo_for_each(vector_begin(pt_vec1), vector_end(pt_vec1), _print_int);
            printf("\n");
            algo_partial_sort(vector_begin(pt_vec1),
                iterator_next_n(vector_begin(pt_vec1), 5), vector_end(pt_vec1));
            algo_for_each(vector_begin(pt_vec1), vector_end(pt_vec1), _print_int);
            printf("\n");
            algo_partial_sort(vector_begin(pt_vec1), vector_end(pt_vec1),
                vector_end(pt_vec1));
            algo_for_each(vector_begin(pt_vec1), vector_end(pt_vec1), _print_int);
            printf("\n");

            algo_random_shuffle(vector_begin(pt_vec1), vector_end(pt_vec1));
            algo_for_each(vector_begin(pt_vec1), vector_end(pt_vec1), _print_int);
            printf("\n");
            algo_partial_sort_if(vector_begin(pt_vec1), vector_begin(pt_vec1),
                vector_end(pt_vec1), fun_greater_int);
            algo_for_each(vector_begin(pt_vec1), vector_end(pt_vec1), _print_int);
            printf("\n");
            algo_partial_sort_if(vector_begin(pt_vec1),
                iterator_next_n(vector_begin(pt_vec1), 5), vector_end(pt_vec1),
                fun_greater_int);
            algo_for_each(vector_begin(pt_vec1), vector_end(pt_vec1), _print_int);
            printf("\n");
            algo_partial_sort_if(vector_begin(pt_vec1), vector_end(pt_vec1),
                vector_end(pt_vec1), fun_greater_int);
            algo_for_each(vector_begin(pt_vec1), vector_end(pt_vec1), _print_int);
            printf("\n");

            algo_random_shuffle(vector_begin(pt_vec1), vector_end(pt_vec1));
            algo_for_each(vector_begin(pt_vec1), vector_end(pt_vec1), _print_int);
            printf("\n");
            t_iter = algo_partial_sort_copy(vector_begin(pt_vec1), vector_end(pt_vec1),
                vector_begin(pt_vec2), vector_end(pt_vec2));
            algo_for_each(vector_begin(pt_vec2), vector_end(pt_vec2), _print_int);
            printf("\n");
            algo_for_each(vector_begin(pt_vec2), t_iter, _print_int);
            printf("\n");
            t_iter = algo_partial_sort_copy_if(vector_begin(pt_vec1), vector_end(pt_vec1),
                vector_begin(pt_vec2), vector_end(pt_vec2), fun_greater_int);
            algo_for_each(vector_begin(pt_vec2), vector_end(pt_vec2), _print_int);
            printf("\n");
            algo_for_each(vector_begin(pt_vec2), t_iter, _print_int);
            printf("\n");

            algo_random_shuffle(vector_begin(pt_vec1), vector_end(pt_vec1));
            algo_for_each(vector_begin(pt_vec1), vector_end(pt_vec1), _print_int);
            printf("\n");
            t_iter = algo_partial_sort_copy(vector_begin(pt_vec1), vector_end(pt_vec1),
                deque_begin(pt_deq), deque_end(pt_deq));
            algo_for_each(deque_begin(pt_deq), deque_end(pt_deq), _print_int);
            printf("\n");
            algo_for_each(deque_begin(pt_deq), t_iter, _print_int);
            printf("\n");
            t_iter = algo_partial_sort_copy_if(vector_begin(pt_vec1), vector_end(pt_vec1),
                deque_begin(pt_deq), deque_end(pt_deq), fun_greater_int);
            algo_for_each(deque_begin(pt_deq), deque_end(pt_deq), _print_int);
            printf("\n");
            algo_for_each(deque_begin(pt_deq), t_iter, _print_int);
            printf("\n");

            printf("\n");
            vector_destroy(pt_vec1);
            vector_destroy(pt_vec2);
            deque_destroy(pt_deq);
        }
        /*algo_sort                       */
        /*algo_sort_if                    */
        {
            vector_t* pt_vec1 = create_vector(int);
            vector_t* pt_vec2 = create_vector(int);
            if(pt_vec1 == NULL || pt_vec2 == NULL)
            {
                return;
            }

            vector_init_n(pt_vec1, 15);
            vector_init_n(pt_vec2, 15);

            algo_iota(vector_begin(pt_vec1), vector_end(pt_vec1), 1);
            algo_iota(vector_begin(pt_vec2), vector_end(pt_vec2), 1);
            algo_random_shuffle(vector_begin(pt_vec1), vector_end(pt_vec1));
            algo_random_shuffle(vector_begin(pt_vec2), vector_end(pt_vec2));
            algo_for_each(vector_begin(pt_vec1), vector_end(pt_vec1), _print_int);
            printf("\n");
            algo_for_each(vector_begin(pt_vec2), vector_end(pt_vec2), _print_int);
            printf("\n");
            algo_sort(vector_begin(pt_vec1), vector_end(pt_vec1));
            algo_sort_if(vector_begin(pt_vec2), vector_end(pt_vec2), fun_greater_int);
            algo_for_each(vector_begin(pt_vec1), vector_end(pt_vec1), _print_int);
            printf("\n");
            algo_for_each(vector_begin(pt_vec2), vector_end(pt_vec2), _print_int);
            printf("\n");

            vector_destroy(pt_vec1);
            vector_destroy(pt_vec2);
        }
        /*algo_inplace_merge              */
        /*algo_inplace_merge_if           */
        {
            vector_t* pt_vec = create_vector(int);
            int i = 0;
            iterator_t t_iter;
            if(pt_vec == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            printf("\n");

            for(i = 0; i < 8; ++i)
            {
                vector_push_back(pt_vec, i);
            }
            for(i = 2; i < 5; ++i)
            {
                vector_push_back(pt_vec, i);
            }
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            t_iter = algo_find(vector_begin(pt_vec), vector_end(pt_vec), 7);
            algo_inplace_merge(vector_begin(pt_vec), iterator_next(t_iter), vector_end(pt_vec));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            vector_clear(pt_vec);
            for(i = 10; i > 3; --i)
            {
                vector_push_back(pt_vec, i);
            }
            for(i = 5; i > 0; --i)
            {
                vector_push_back(pt_vec, i);
            }
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            t_iter = algo_find(vector_begin(pt_vec), vector_end(pt_vec), 4);
            algo_inplace_merge_if(vector_begin(pt_vec), iterator_next(t_iter), vector_end(pt_vec), fun_greater_int);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            printf("\n");
            vector_destroy(pt_vec);
        }
        /*algo_nth_element                */
        /*algo_nth_element_if             */
        {
            vector_t* pt_vec1 = create_vector(int);
            vector_t* pt_vec2 = create_vector(int);
            if(pt_vec1 == NULL || pt_vec2 == NULL)
            {
                return;
            }
            vector_init_n(pt_vec1, 15);
            vector_init_n(pt_vec2, 15);

            printf("\n");
            algo_iota(vector_begin(pt_vec1), vector_end(pt_vec1), 1);
            algo_iota(vector_begin(pt_vec2), vector_end(pt_vec2), 1);
            algo_random_shuffle(vector_begin(pt_vec1), vector_end(pt_vec1));
            algo_random_shuffle(vector_begin(pt_vec2), vector_end(pt_vec2));
            algo_for_each(vector_begin(pt_vec1), vector_end(pt_vec1), _print_int);
            printf("\n");
            algo_for_each(vector_begin(pt_vec2), vector_end(pt_vec2), _print_int);
            printf("\n");

            algo_nth_element(vector_begin(pt_vec1), iterator_next_n(vector_begin(pt_vec1), 9),
                vector_end(pt_vec1));
            algo_sort(vector_begin(pt_vec2), vector_end(pt_vec2));
            algo_for_each(vector_begin(pt_vec1), vector_end(pt_vec1), _print_int);
            printf("\n");
            algo_for_each(vector_begin(pt_vec2), vector_end(pt_vec2), _print_int);
            printf("\n");

            algo_nth_element_if(vector_begin(pt_vec1),
                iterator_next_n(vector_begin(pt_vec1), 9), vector_end(pt_vec1),
                fun_greater_int);
            algo_sort_if(vector_begin(pt_vec2), vector_end(pt_vec2), fun_greater_int);
            algo_for_each(vector_begin(pt_vec1), vector_end(pt_vec1), _print_int);
            printf("\n");
            algo_for_each(vector_begin(pt_vec2), vector_end(pt_vec2), _print_int);
            printf("\n");

            printf("\n");
            vector_destroy(pt_vec1);
            vector_destroy(pt_vec2);
        }
        /*algo_is_sorted                  */
        /*algo_is_sorted_if               */
        {
            vector_t* pt_vec = create_vector(int);
            if(pt_vec == NULL)
            {
                return;
            }

            vector_init_n(pt_vec, 10);

            algo_iota(vector_begin(pt_vec), vector_end(pt_vec), 1);
            algo_random_shuffle(vector_begin(pt_vec), vector_end(pt_vec));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            if(algo_is_sorted(vector_begin(pt_vec), vector_end(pt_vec)))
            {
                printf("is sorted.\n");
            }
            else
            {
                printf("is not sorted.\n");
            }
            if(algo_is_sorted_if(vector_begin(pt_vec), vector_end(pt_vec), fun_greater_int))
            {
                printf("is greater sorted.\n");
            }
            else
            {
                printf("is not sorted.\n");
            }
            algo_sort(vector_begin(pt_vec), vector_end(pt_vec));
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            if(algo_is_sorted(vector_begin(pt_vec), vector_end(pt_vec)))
            {
                printf("is sorted.\n");
            }
            else
            {
                printf("is not sorted.\n");
            }
            if(algo_is_sorted_if(vector_begin(pt_vec), vector_end(pt_vec), fun_greater_int))
            {
                printf("is greater sorted.\n");
            }
            else
            {
                printf("is not sorted.\n");
            }
            algo_sort_if(vector_begin(pt_vec), vector_end(pt_vec), fun_greater_int);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            if(algo_is_sorted(vector_begin(pt_vec), vector_end(pt_vec)))
            {
                printf("is sorted.\n");
            }
            else
            {
                printf("is not sorted.\n");
            }
            if(algo_is_sorted_if(vector_begin(pt_vec), vector_end(pt_vec), fun_greater_int))
            {
                printf("is greater sorted.\n");
            }
            else
            {
                printf("is not sorted.\n");
            }

            vector_destroy(pt_vec);
        }
        /*algo_stable_sort                */
        /*algo_stable_sort_if             */
        {
            vector_t* pt_vec1 = create_vector(int);
            vector_t* pt_vec2 = create_vector(int);
            if(pt_vec1 == NULL || pt_vec2 == NULL)
            {
                return;
            }

            vector_init_n(pt_vec1, 15);
            vector_init_n(pt_vec2, 15);

            algo_iota(vector_begin(pt_vec1), vector_end(pt_vec1), 1);
            algo_iota(vector_begin(pt_vec2), vector_end(pt_vec2), 1);
            algo_random_shuffle(vector_begin(pt_vec1), vector_end(pt_vec1));
            algo_random_shuffle(vector_begin(pt_vec2), vector_end(pt_vec2));
            algo_for_each(vector_begin(pt_vec1), vector_end(pt_vec1), _print_int);
            printf("\n");
            algo_for_each(vector_begin(pt_vec2), vector_end(pt_vec2), _print_int);
            printf("\n");
            algo_stable_sort(vector_begin(pt_vec1), vector_end(pt_vec1));
            algo_stable_sort_if(vector_begin(pt_vec2), vector_end(pt_vec2), fun_greater_int);
            algo_for_each(vector_begin(pt_vec1), vector_end(pt_vec1), _print_int);
            printf("\n");
            algo_for_each(vector_begin(pt_vec2), vector_end(pt_vec2), _print_int);
            printf("\n");

            vector_destroy(pt_vec1);
            vector_destroy(pt_vec2);
        }
    }
    /* user define type */
    {
    }
    /* cstl built-in type */
    {
    }
    /* c string type */
    {
    }

    /*_algo_count                     */
    /*_algo_find                      */
    /*_algo_search_n                  */
    /*_algo_search_n_if               */
    /*_algo_remove_copy               */
    /*_algo_remove                    */
    /*algo_replace                    */
    /*algo_replace_copy               */
    /*_algo_replace_if                */
    /*_algo_replace_copy_if           */
    /*_algo_lower_bound               */
    /*_algo_lower_bound_if            */
    /*_algo_upper_bound               */
    /*_algo_upper_bound_if            */
    /*_algo_equal_range               */
    /*_algo_equal_range_if            */
    /*_algo_binary_search             */
    /*_algo_binary_search_if          */
    /*algo_set_union                  */
    /*algo_set_union_if               */
    /*algo_set_intersection           */
    /*algo_set_intersection_if        */
    /*algo_set_difference             */
    /*algo_set_difference_if          */
    /*algo_set_symmetric_difference   */
    /*algo_set_symmetric_difference_if*/
    /*algo_adjacent_find              */
    /*algo_adjacent_find_if           */
    /*algo_count_if                   */
    /*algo_find_if                    */
    /*algo_find_first_of              */
    /*algo_find_first_of_if           */
    /*algo_for_each                   */
    /*algo_search                     */
    /*algo_search_if                  */
    /*algo_search_end                 */
    /*algo_search_end_if              */
    /*algo_find_end                   */
    /*algo_find_end_if                */
    /*algo_generate                   */
    /*algo_generate_n                 */
    /*algo_includes                   */
    /*algo_includes_if                */
    /*algo_max_element                */
    /*algo_max_element_if             */
    /*algo_min_element                */
    /*algo_min_element_if             */
    /*algo_merge                      */
    /*algo_merge_if                   */
    /*algo_partition                  */
    /*algo_stable_partition           */
    /*algo_remove_if                  */
    /*algo_remove_copy_if             */
    /*algo_reverse                    */
    /*algo_reverse_copy               */
    /*algo_rotate                     */
    /*algo_rotate_copy                */
    /*algo_swap_ranges                */
    /*algo_transform                  */
    /*algo_transform_binary           */
    /*algo_unique                     */
    /*algo_unique_if                  */
    /*algo_unique_copy                */
    /*algo_unique_copy_if             */
    /*algo_next_permutation           */
    /*algo_next_permutation_if        */
    /*algo_prev_permutation           */
    /*algo_prev_permutation_if        */
    /*algo_random_shuffle             */
    /*algo_random_shuffle_if          */
    /*algo_random_sample              */
    /*algo_random_sample_if           */
    /*algo_random_sample_n            */
    /*algo_random_sample_n_if         */
    /*algo_partial_sort               */
    /*algo_partial_sort_if            */
    /*algo_partial_sort_copy          */
    /*algo_partial_sort_copy_if       */
    /*algo_sort                       */
    /*algo_sort_if                    */
    /*algo_inplace_merge              */
    /*algo_inplace_merge_if           */
    /*algo_nth_element                */
    /*algo_nth_element_if             */
    /*algo_is_sorted                  */
    /*algo_is_sorted_if               */
    /*algo_stable_sort                */
    /*algo_stable_sort_if             */
}

/** local function implementation section **/
static void _print_int(const void* cpv_input, void* pv_output)
{
    pv_output = NULL;
    printf("%d, ", *(int*)cpv_input);
}

static void _plus100(const void* cpv_input, void* pv_output)
{
    pv_output = NULL;
    *(int*)cpv_input += 100;
}

static void _is_even(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    *(bool_t*)pv_output = *(int*)cpv_input % 2 == 0 ? true : false;
}

static void _mod3(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    *(bool_t*)pv_output = *(int*)cpv_input % 3 == 0 ? true : false;
}

static void _doubled(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = *(int*)cpv_first * 2 == *(int*)cpv_second ? true : false;
}

static void _check_even(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    if(*(bool_t*)cpv_second)
    {
        *(bool_t*)pv_output = *(int*)cpv_first % 2 == 0 ? true : false;
    }
    else
    {
        *(bool_t*)pv_output = *(int*)cpv_first % 2 == 0 ? false : true;
    }
}

/** eof **/

