/*
 *  The implementation of base algorithm base.
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
#include "cvector.h"
#include "clist.h"
#include "calgorithm.h"
#include "cnumeric.h"
#include "cfunctional.h"
#include "test_algobase.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/
static void _print_int(const void* cpv_input, void* pv_output);
static void _equal_ex(const void* cpv_first, const void* cpv_second, void* pv_output);
static void _absless(const void* cpv_first, const void* cpv_second, void* pv_output);

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
void test_algobase(void)
{
    /* c built-in type */
    {
        /*algo_fill                           */
        {
            list_t* pt_list = create_list(int);
            if(pt_list == NULL)
            {
                return;
            }
            list_init_n(pt_list, 10);
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");

            algo_fill(list_begin(pt_list), list_begin(pt_list), 455);
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");

            algo_fill(list_begin(pt_list), iterator_advance(list_begin(pt_list), 3), 90);
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");

            algo_fill(iterator_next(list_begin(pt_list)),
                iterator_advance(list_begin(pt_list), 5), -512);
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");

            algo_fill(iterator_advance(list_begin(pt_list), 6), list_end(pt_list), -1000);
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");

            algo_fill(list_end(pt_list), list_end(pt_list), 33);
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");

            algo_fill(list_begin(pt_list), list_end(pt_list), 1234);
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");

            list_destroy(pt_list);
        }
        /*algo_fill_n                         */
        {
            list_t* pt_list = create_list(int);
            if(pt_list == NULL)
            {
                return;
            }
            list_init_n(pt_list, 10);
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");

            algo_fill_n(list_begin(pt_list), 0, 455);
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");

            algo_fill_n(list_begin(pt_list), 3, 90);
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");

            algo_fill_n(iterator_next(list_begin(pt_list)), 5, -512);
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");

            algo_fill_n(list_end(pt_list), 0, 33);
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");

            algo_fill_n(list_begin(pt_list), list_size(pt_list), 1234);
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");

            list_destroy(pt_list);
        }
        /*algo_equal                          */
        {
            list_t* pt_list = create_list(int);
            vector_t* pt_vec = create_vector(int);
            size_t t_index = 0;
            if(pt_list == NULL || pt_vec == NULL)
            {
                return;
            }
            list_init(pt_list);
            vector_init(pt_vec);

            printf("equal : %d\n", algo_equal(
                list_begin(pt_list), list_end(pt_list), vector_begin(pt_vec)));
            printf("list  : ");
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");
            printf("vector: ");
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            for(t_index = 0; t_index < 10; ++t_index)
            {
                list_push_back(pt_list, t_index);
                vector_push_back(pt_vec, t_index + 5);
            }
            printf("equal : %d\n", algo_equal(
                list_begin(pt_list), list_end(pt_list), vector_begin(pt_vec)));
            printf("list  : ");
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");
            printf("vector: ");
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            list_clear(pt_list);
            vector_clear(pt_vec);
            for(t_index = 0; t_index < 10; ++t_index)
            {
                list_push_back(pt_list, t_index);
                vector_push_back(pt_vec, t_index);
            }
            printf("equal : %d\n", algo_equal(
                list_begin(pt_list), list_end(pt_list), vector_begin(pt_vec)));
            printf("list  : ");
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");
            printf("vector: ");
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            vector_destroy(pt_vec);
            list_destroy(pt_list);
        }
        /*algo_equal_if                       */
        {
            list_t* pt_list = create_list(int);
            vector_t* pt_vec = create_vector(int);
            size_t t_index = 0;
            if(pt_list == NULL || pt_vec == NULL)
            {
                return;
            }
            list_init(pt_list);
            vector_init(pt_vec);

            printf("equal : %d\n", algo_equal_if(
                list_begin(pt_list), list_end(pt_list), vector_begin(pt_vec), _equal_ex));
            printf("list  : ");
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");
            printf("vector: ");
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            for(t_index = 0; t_index < 10; ++t_index)
            {
                list_push_back(pt_list, t_index);
                vector_push_back(pt_vec, t_index + 5);
            }
            printf("equal : %d\n", algo_equal_if(
                list_begin(pt_list), list_end(pt_list), vector_begin(pt_vec), _equal_ex));
            printf("list  : ");
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");
            printf("vector: ");
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            list_clear(pt_list);
            vector_clear(pt_vec);
            for(t_index = 0; t_index < 10; ++t_index)
            {
                list_push_back(pt_list, t_index);
                vector_push_back(pt_vec, t_index);
            }
            printf("equal : %d\n", algo_equal_if(
                list_begin(pt_list), list_end(pt_list), vector_begin(pt_vec), _equal_ex));
            printf("list  : ");
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");
            printf("vector: ");
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            vector_destroy(pt_vec);
            list_destroy(pt_list);
        }
        /*algo_swap                           */
        /*algo_iter_swap                      */
        {
            list_t* pt_list = create_list(int);
            vector_t* pt_vec = create_vector(int);
            size_t t_index = 0;
            if(pt_list == NULL || pt_vec == NULL)
            {
                return;
            }
            list_init(pt_list);
            vector_init(pt_vec);

            for(t_index = 0; t_index < 10; ++t_index)
            {
                list_push_back(pt_list, t_index + 1);
                vector_push_back(pt_vec, -t_index - 1);
            }
            printf("list  : ");
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");
            printf("vector: ");
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            algo_swap(list_begin(pt_list), list_begin(pt_list));
            algo_iter_swap(vector_begin(pt_vec), vector_begin(pt_vec));
            printf("list  : ");
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");
            printf("vector: ");
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            algo_swap(list_begin(pt_list), iterator_advance(list_begin(pt_list), 5));
            algo_iter_swap(vector_begin(pt_vec), iterator_next_n(vector_begin(pt_vec), 5));
            printf("list  : ");
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");
            printf("vector: ");
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            algo_swap(list_begin(pt_list), iterator_next(vector_begin(pt_vec)));
            algo_iter_swap(vector_begin(pt_vec), iterator_next(list_begin(pt_list)));
            printf("list  : ");
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");
            printf("vector: ");
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            list_destroy(pt_list);
            vector_destroy(pt_vec);
        }
        /*algo_lexicographical_compare        */
        /*algo_lexicographical_compare_3way   */
        {
            list_t* pt_list = create_list(int);
            vector_t* pt_vec = create_vector(int);
            if(pt_list == NULL || pt_vec == NULL)
            {
                return;
            }
            list_init(pt_list);
            vector_init(pt_vec);

            printf("list  : ");
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");
            printf("vector: ");
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            printf("algo_lexicographical_compare() : ");
            algo_lexicographical_compare(list_begin(pt_list), list_end(pt_list),
                vector_begin(pt_vec), vector_end(pt_vec)) == 0 ?
                printf("false\n") : printf("true\n");
            printf("algo_lexicographical_compare_3way() : %d\n",
                algo_lexicographical_compare_3way(list_begin(pt_list), list_end(pt_list),
                vector_begin(pt_vec), vector_end(pt_vec)));

            list_push_back(pt_list, 3);
            list_push_back(pt_list, 2);
            list_push_back(pt_list, 8);
            list_push_back(pt_list, 7);
            vector_push_back(pt_vec, 3);
            vector_push_back(pt_vec, 3);
            vector_push_back(pt_vec, 3);
            vector_push_back(pt_vec, 3);
            printf("list  : ");
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");
            printf("vector: ");
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            printf("algo_lexicographical_compare() : ");
            algo_lexicographical_compare(list_begin(pt_list), list_end(pt_list),
                vector_begin(pt_vec), vector_end(pt_vec)) == 0 ?
                printf("false\n") : printf("true\n");
            printf("algo_lexicographical_compare_3way() : %d\n",
                algo_lexicographical_compare_3way(list_begin(pt_list), list_end(pt_list),
                vector_begin(pt_vec), vector_end(pt_vec)));

            list_clear(pt_list);
            list_push_back(pt_list, 3);
            list_push_back(pt_list, 2);
            list_push_back(pt_list, 8);
            list_push_back(pt_list, 7);
            vector_clear(pt_vec);
            vector_push_back(pt_vec, 3);
            vector_push_back(pt_vec, 2);
            vector_push_back(pt_vec, 8);
            vector_push_back(pt_vec, 7);
            vector_push_back(pt_vec, 7);
            printf("list  : ");
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");
            printf("vector: ");
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            printf("algo_lexicographical_compare() : ");
            algo_lexicographical_compare(list_begin(pt_list), list_end(pt_list),
                vector_begin(pt_vec), vector_end(pt_vec)) == 0 ?
                printf("false\n") : printf("true\n");
            printf("algo_lexicographical_compare_3way() : %d\n",
                algo_lexicographical_compare_3way(list_begin(pt_list), list_end(pt_list),
                vector_begin(pt_vec), vector_end(pt_vec)));

            list_clear(pt_list);
            list_push_back(pt_list, 3);
            list_push_back(pt_list, 2);
            list_push_back(pt_list, 8);
            list_push_back(pt_list, 7);
            vector_clear(pt_vec);
            vector_push_back(pt_vec, 3);
            vector_push_back(pt_vec, 2);
            vector_push_back(pt_vec, 8);
            vector_push_back(pt_vec, 7);
            printf("list  : ");
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");
            printf("vector: ");
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            printf("algo_lexicographical_compare() : ");
            algo_lexicographical_compare(list_begin(pt_list), list_end(pt_list),
                vector_begin(pt_vec), vector_end(pt_vec)) == 0 ?
                printf("false\n") : printf("true\n");
            printf("algo_lexicographical_compare_3way() : %d\n",
                algo_lexicographical_compare_3way(list_begin(pt_list), list_end(pt_list),
                vector_begin(pt_vec), vector_end(pt_vec)));

            list_clear(pt_list);
            list_push_back(pt_list, 3);
            list_push_back(pt_list, 2);
            list_push_back(pt_list, 8);
            list_push_back(pt_list, 7);
            vector_clear(pt_vec);
            vector_push_back(pt_vec, 3);
            vector_push_back(pt_vec, 2);
            vector_push_back(pt_vec, 8);
            printf("list  : ");
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");
            printf("vector: ");
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            printf("algo_lexicographical_compare() : ");
            algo_lexicographical_compare(list_begin(pt_list), list_end(pt_list),
                vector_begin(pt_vec), vector_end(pt_vec)) == 0 ?
                printf("false\n") : printf("true\n");
            printf("algo_lexicographical_compare_3way() : %d\n",
                algo_lexicographical_compare_3way(list_begin(pt_list), list_end(pt_list),
                vector_begin(pt_vec), vector_end(pt_vec)));

            list_clear(pt_list);
            list_push_back(pt_list, 3);
            list_push_back(pt_list, 2);
            list_push_back(pt_list, 8);
            list_push_back(pt_list, 7);
            vector_clear(pt_vec);
            vector_push_back(pt_vec, 3);
            vector_push_back(pt_vec, 2);
            vector_push_back(pt_vec, 8);
            vector_push_back(pt_vec, 5);
            printf("list  : ");
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");
            printf("vector: ");
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            printf("algo_lexicographical_compare() : ");
            algo_lexicographical_compare(list_begin(pt_list), list_end(pt_list),
                vector_begin(pt_vec), vector_end(pt_vec)) == 0 ?
                printf("false\n") : printf("true\n");
            printf("algo_lexicographical_compare_3way() : %d\n",
                algo_lexicographical_compare_3way(list_begin(pt_list), list_end(pt_list),
                vector_begin(pt_vec), vector_end(pt_vec)));

            list_destroy(pt_list);
            vector_destroy(pt_vec);
        }
        /*algo_lexicographical_compare_if     */
        /*algo_lexicographical_compare_3way_if*/
        {
            list_t* pt_list = create_list(int);
            vector_t* pt_vec = create_vector(int);
            if(pt_list == NULL || pt_vec == NULL)
            {
                return;
            }
            list_init(pt_list);
            vector_init(pt_vec);

            printf("list  : ");
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");
            printf("vector: ");
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            printf("algo_lexicographical_compare() : ");
            algo_lexicographical_compare_if(list_begin(pt_list), list_end(pt_list),
                vector_begin(pt_vec), vector_end(pt_vec), fun_great_int) == 0 ?
                printf("false\n") : printf("true\n");
            printf("algo_lexicographical_compare_3way() : %d\n",
                algo_lexicographical_compare_3way_if(list_begin(pt_list), list_end(pt_list),
                vector_begin(pt_vec), vector_end(pt_vec), fun_great_int));

            list_push_back(pt_list, 3);
            list_push_back(pt_list, 2);
            list_push_back(pt_list, 8);
            list_push_back(pt_list, 7);
            vector_push_back(pt_vec, 3);
            vector_push_back(pt_vec, 3);
            vector_push_back(pt_vec, 3);
            vector_push_back(pt_vec, 3);
            printf("list  : ");
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");
            printf("vector: ");
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            printf("algo_lexicographical_compare() : ");
            algo_lexicographical_compare_if(list_begin(pt_list), list_end(pt_list),
                vector_begin(pt_vec), vector_end(pt_vec), fun_great_int) == 0 ?
                printf("false\n") : printf("true\n");
            printf("algo_lexicographical_compare_3way() : %d\n",
                algo_lexicographical_compare_3way_if(list_begin(pt_list), list_end(pt_list),
                vector_begin(pt_vec), vector_end(pt_vec), fun_great_int));

            list_clear(pt_list);
            list_push_back(pt_list, 3);
            list_push_back(pt_list, 2);
            list_push_back(pt_list, 8);
            list_push_back(pt_list, 7);
            vector_clear(pt_vec);
            vector_push_back(pt_vec, 3);
            vector_push_back(pt_vec, 2);
            vector_push_back(pt_vec, 8);
            vector_push_back(pt_vec, 7);
            vector_push_back(pt_vec, 7);
            printf("list  : ");
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");
            printf("vector: ");
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            printf("algo_lexicographical_compare() : ");
            algo_lexicographical_compare_if(list_begin(pt_list), list_end(pt_list),
                vector_begin(pt_vec), vector_end(pt_vec), fun_great_int) == 0 ?
                printf("false\n") : printf("true\n");
            printf("algo_lexicographical_compare_3way() : %d\n",
                algo_lexicographical_compare_3way_if(list_begin(pt_list), list_end(pt_list),
                vector_begin(pt_vec), vector_end(pt_vec), fun_great_int));

            list_clear(pt_list);
            list_push_back(pt_list, 3);
            list_push_back(pt_list, 2);
            list_push_back(pt_list, 8);
            list_push_back(pt_list, 7);
            vector_clear(pt_vec);
            vector_push_back(pt_vec, 3);
            vector_push_back(pt_vec, 2);
            vector_push_back(pt_vec, 8);
            vector_push_back(pt_vec, 7);
            printf("list  : ");
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");
            printf("vector: ");
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            printf("algo_lexicographical_compare() : ");
            algo_lexicographical_compare_if(list_begin(pt_list), list_end(pt_list),
                vector_begin(pt_vec), vector_end(pt_vec), fun_great_int) == 0 ?
                printf("false\n") : printf("true\n");
            printf("algo_lexicographical_compare_3way() : %d\n",
                algo_lexicographical_compare_3way_if(list_begin(pt_list), list_end(pt_list),
                vector_begin(pt_vec), vector_end(pt_vec), fun_great_int));

            list_clear(pt_list);
            list_push_back(pt_list, 3);
            list_push_back(pt_list, 2);
            list_push_back(pt_list, 8);
            list_push_back(pt_list, 7);
            vector_clear(pt_vec);
            vector_push_back(pt_vec, 3);
            vector_push_back(pt_vec, 2);
            vector_push_back(pt_vec, 8);
            printf("list  : ");
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");
            printf("vector: ");
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            printf("algo_lexicographical_compare() : ");
            algo_lexicographical_compare_if(list_begin(pt_list), list_end(pt_list),
                vector_begin(pt_vec), vector_end(pt_vec), fun_great_int) == 0 ?
                printf("false\n") : printf("true\n");
            printf("algo_lexicographical_compare_3way() : %d\n",
                algo_lexicographical_compare_3way_if(list_begin(pt_list), list_end(pt_list),
                vector_begin(pt_vec), vector_end(pt_vec), fun_great_int));

            list_clear(pt_list);
            list_push_back(pt_list, 3);
            list_push_back(pt_list, 2);
            list_push_back(pt_list, 8);
            list_push_back(pt_list, 7);
            vector_clear(pt_vec);
            vector_push_back(pt_vec, 3);
            vector_push_back(pt_vec, 2);
            vector_push_back(pt_vec, 8);
            vector_push_back(pt_vec, 5);
            printf("list  : ");
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");
            printf("vector: ");
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");
            printf("algo_lexicographical_compare() : ");
            algo_lexicographical_compare_if(list_begin(pt_list), list_end(pt_list),
                vector_begin(pt_vec), vector_end(pt_vec), fun_great_int) == 0 ?
                printf("false\n") : printf("true\n");
            printf("algo_lexicographical_compare_3way() : %d\n",
                algo_lexicographical_compare_3way_if(list_begin(pt_list), list_end(pt_list),
                vector_begin(pt_vec), vector_end(pt_vec), fun_great_int));

            list_destroy(pt_list);
            vector_destroy(pt_vec);
        }
        /*algo_max                            */
        /*algo_max_if                         */
        /*algo_min                            */
        /*algo_min_if                         */
        {
            vector_t* pt_vec = create_vector(int);
            list_t* pt_list = create_list(int);
            iterator_t t_min;
            iterator_t t_max;
            if(pt_vec == NULL || pt_list == NULL)
            {
                return;
            }
            vector_init_n(pt_vec, 10);
            list_init_n(pt_list, 10);
            algo_iota(list_begin(pt_list), list_end(pt_list), -2);
            algo_iota(vector_begin(pt_vec), vector_end(pt_vec), -9);
            printf("list  : ");
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");
            printf("vector: ");
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            t_min = algo_min(list_begin(pt_list), vector_begin(pt_vec));
            t_max = algo_max(list_begin(pt_list), vector_begin(pt_vec));
            printf("minmum between two begin : %d\n", *(int*)iterator_get_pointer(t_min));
            printf("maxmum between two begin : %d\n", *(int*)iterator_get_pointer(t_max));

            t_min = algo_min_if(list_begin(pt_list), vector_begin(pt_vec), _absless);
            t_max = algo_max_if(list_begin(pt_list), vector_begin(pt_vec), _absless);
            printf("minmum of absolute between two begin : %d\n",
                *(int*)iterator_get_pointer(t_min));
            printf("maxmum of absolute between two begin : %d\n",
                *(int*)iterator_get_pointer(t_max));

            vector_destroy(pt_vec);
            list_destroy(pt_list);
        }
        /*algo_mismatch                       */
        /*algo_mismatch_if                    */
        {
            vector_t* pt_vec = create_vector(int);
            list_t* pt_list = create_list(int);
            range_t t_range;
            if(pt_vec == NULL || pt_list == NULL)
            {
                return;
            }
            vector_init_n(pt_vec, 5);
            list_init_n(pt_list, 5);
            algo_iota(list_begin(pt_list), list_end(pt_list), 2);
            list_push_back(pt_list, 11);
            list_push_back(pt_list, 22);
            list_push_back(pt_list, 33);
            algo_iota(vector_begin(pt_vec), vector_end(pt_vec), 2);
            vector_push_back(pt_vec, 44);
            vector_push_back(pt_vec, 55);
            vector_push_back(pt_vec, 9);
            printf("list  : ");
            algo_for_each(list_begin(pt_list), list_end(pt_list), _print_int);
            printf("\n");
            printf("vector: ");
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_int);
            printf("\n");

            t_range = algo_mismatch(list_begin(pt_list), list_end(pt_list),
                vector_begin(pt_vec));
            printf("the first mismatch : %d and %d\n",
                *(int*)iterator_get_pointer(t_range.t_begin),
                *(int*)iterator_get_pointer(t_range.t_end));
            t_range = algo_mismatch_if(list_begin(pt_list), list_end(pt_list),
                vector_begin(pt_vec), fun_less_equal_int);
            printf("not less or equal : %d and %d\n",
                *(int*)iterator_get_pointer(t_range.t_begin),
                *(int*)iterator_get_pointer(t_range.t_end));

            vector_destroy(pt_vec);
            list_destroy(pt_list);
        }
        /*algo_copy                           */
        /*algo_copy_n                         */
        /*algo_copy_backward                  */
        {
            vector_t* pt_vec1 = create_vector(int);
            vector_t* pt_vec2 = create_vector(int);
            list_t* pt_list1 = create_list(int);
            list_t* pt_list2 = create_list(int);
            if(pt_vec1 == NULL || pt_vec2 == NULL || pt_list1 == NULL || pt_list2 == NULL)
            {
                return;
            }
            vector_init_n(pt_vec1, 10);
            vector_init_n(pt_vec2, 10);
            list_init_n(pt_list1, 10);
            list_init_n(pt_list2, 10);

            algo_iota(vector_begin(pt_vec1), vector_end(pt_vec1), 0);
            algo_iota(vector_begin(pt_vec2), vector_end(pt_vec2), 0);
            algo_iota(list_begin(pt_list1), list_end(pt_list1), 0);
            algo_iota(list_begin(pt_list2), list_end(pt_list2), 0);
            printf("list1  : ");
            algo_for_each(list_begin(pt_list1), list_end(pt_list1), _print_int);
            printf("\n");
            printf("list2  : ");
            algo_for_each(list_begin(pt_list2), list_end(pt_list2), _print_int);
            printf("\n");
            printf("vector1: ");
            algo_for_each(vector_begin(pt_vec1), vector_end(pt_vec1), _print_int);
            printf("\n");
            printf("vector2: ");
            algo_for_each(vector_begin(pt_vec2), vector_end(pt_vec2), _print_int);
            printf("\n\n");

            algo_copy(iterator_advance(list_begin(pt_list1), 4),
                list_end(pt_list1), list_begin(pt_list1));
            algo_copy(iterator_advance(list_begin(pt_list2), 6),
                list_end(pt_list2), list_begin(pt_list2));
            algo_copy(vector_begin(pt_vec1), iterator_advance(vector_begin(pt_vec1), 6),
                iterator_advance(vector_begin(pt_vec1), 3));
            algo_copy(vector_begin(pt_vec2), iterator_advance(vector_begin(pt_vec2), 3),
                iterator_advance(vector_begin(pt_vec2), 6));
            printf("list1  : ");
            algo_for_each(list_begin(pt_list1), list_end(pt_list1), _print_int);
            printf("\n");
            printf("list2  : ");
            algo_for_each(list_begin(pt_list2), list_end(pt_list2), _print_int);
            printf("\n");
            printf("vector1: ");
            algo_for_each(vector_begin(pt_vec1), vector_end(pt_vec1), _print_int);
            printf("\n");
            printf("vector2: ");
            algo_for_each(vector_begin(pt_vec2), vector_end(pt_vec2), _print_int);
            printf("\n\n");

            algo_iota(vector_begin(pt_vec1), vector_end(pt_vec1), 0);
            algo_iota(vector_begin(pt_vec2), vector_end(pt_vec2), 0);
            algo_iota(list_begin(pt_list1), list_end(pt_list1), 0);
            algo_iota(list_begin(pt_list2), list_end(pt_list2), 0);
            printf("list1  : ");
            algo_for_each(list_begin(pt_list1), list_end(pt_list1), _print_int);
            printf("\n");
            printf("list2  : ");
            algo_for_each(list_begin(pt_list2), list_end(pt_list2), _print_int);
            printf("\n");
            printf("vector1: ");
            algo_for_each(vector_begin(pt_vec1), vector_end(pt_vec1), _print_int);
            printf("\n");
            printf("vector2: ");
            algo_for_each(vector_begin(pt_vec2), vector_end(pt_vec2), _print_int);
            printf("\n\n");

            algo_copy_n(iterator_advance(list_begin(pt_list1), 4), 5, list_begin(pt_list1));
            algo_copy_n(iterator_advance(list_begin(pt_list2), 6), 3, list_begin(pt_list2));
            algo_copy_n(vector_begin(pt_vec1), 6, iterator_advance(vector_begin(pt_vec1), 3));
            algo_copy_n(vector_begin(pt_vec2), 3, iterator_advance(vector_begin(pt_vec2), 6));
            printf("list1  : ");
            algo_for_each(list_begin(pt_list1), list_end(pt_list1), _print_int);
            printf("\n");
            printf("list2  : ");
            algo_for_each(list_begin(pt_list2), list_end(pt_list2), _print_int);
            printf("\n");
            printf("vector1: ");
            algo_for_each(vector_begin(pt_vec1), vector_end(pt_vec1), _print_int);
            printf("\n");
            printf("vector2: ");
            algo_for_each(vector_begin(pt_vec2), vector_end(pt_vec2), _print_int);
            printf("\n\n");

            algo_iota(vector_begin(pt_vec1), vector_end(pt_vec1), 0);
            algo_iota(vector_begin(pt_vec2), vector_end(pt_vec2), 0);
            algo_iota(list_begin(pt_list1), list_end(pt_list1), 0);
            algo_iota(list_begin(pt_list2), list_end(pt_list2), 0);
            printf("list1  : ");
            algo_for_each(list_begin(pt_list1), list_end(pt_list1), _print_int);
            printf("\n");
            printf("list2  : ");
            algo_for_each(list_begin(pt_list2), list_end(pt_list2), _print_int);
            printf("\n");
            printf("vector1: ");
            algo_for_each(vector_begin(pt_vec1), vector_end(pt_vec1), _print_int);
            printf("\n");
            printf("vector2: ");
            algo_for_each(vector_begin(pt_vec2), vector_end(pt_vec2), _print_int);
            printf("\n\n");

            algo_copy_backward(iterator_advance(list_begin(pt_list1), 4), list_end(pt_list1),
                iterator_advance(list_begin(pt_list1), 7));
            algo_copy_backward(iterator_advance(list_begin(pt_list2), 6), list_end(pt_list2),
                iterator_advance(list_begin(pt_list2), 5));
            algo_copy_backward(vector_begin(pt_vec1),
                iterator_advance(vector_begin(pt_vec1), 6),
                iterator_prev(vector_end(pt_vec1)));
            algo_copy_backward(vector_begin(pt_vec2),
                iterator_advance(vector_begin(pt_vec2), 3),
                iterator_prev(vector_end(pt_vec2)));
            printf("list1  : ");
            algo_for_each(list_begin(pt_list1), list_end(pt_list1), _print_int);
            printf("\n");
            printf("list2  : ");
            algo_for_each(list_begin(pt_list2), list_end(pt_list2), _print_int);
            printf("\n");
            printf("vector1: ");
            algo_for_each(vector_begin(pt_vec1), vector_end(pt_vec1), _print_int);
            printf("\n");
            printf("vector2: ");
            algo_for_each(vector_begin(pt_vec2), vector_end(pt_vec2), _print_int);
            printf("\n\n");

            vector_destroy(pt_vec1);
            vector_destroy(pt_vec2);
            list_destroy(pt_list1);
            list_destroy(pt_list2);
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
    /*_algo_fill                          */
    /*_algo_fill_n                        */
    /*algo_equal                          */
    /*algo_equal_if                       */
    /*algo_swap                           */
    /*algo_iter_swap                      */
    /*algo_lexicographical_compare        */
    /*algo_lexicographical_compare_if     */
    /*algo_lexicographical_compare_3way   */
    /*algo_lexicographical_compare_3way_if*/
    /*algo_max                            */
    /*algo_max_if                         */
    /*algo_min                            */
    /*algo_min_if                         */
    /*algo_mismatch                       */
    /*algo_mismatch_if                    */
    /*algo_copy                           */
    /*algo_copy_n                         */
    /*algo_copy_backward                  */
}

/** local function implementation section **/
static void _absless(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    if(abs(*(int*)cpv_first) < abs(*(int*)cpv_second))
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}

static void _equal_ex(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    if(*(int*)cpv_first + 5 == *(int*)cpv_second)
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}

static void _print_int(const void* cpv_input, void* pv_output)
{
    pv_output = NULL;
    printf("%d, ", *(int*)cpv_input);
}

/** eof **/

