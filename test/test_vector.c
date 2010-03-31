/*
 *  The implementation of vector test.
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
#include <float.h>
#include "cvector.h"
#include "test_vector.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/
typedef struct _tagabc
{
    int    _n_first;
    double _d_second;
    char*  _pc_third;
}abc_t;

/** local function prototype section **/
static void _abc_init(const void* cpv_input, void* pv_output);
static void _abc_copy(const void* cpv_first, const void* cpv_second, void* pv_output);
static void _abc_less(const void* cpv_first, const void* cpv_second, void * pv_output);
static void _abc_destroy(const void* cpv_input, void* pv_output);

static void _print_vec_str(const vector_t* pt_vec);

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
void test_vector(void)
{
    /* c builtin type */
    {
        /* create_vector(), vector_init(), vector_destroy() */
        {
            vector_t* pv_int = create_vector(int);
            if(pv_int == NULL)
            {
                return;
            }

            vector_init(pv_int);
            vector_destroy(pv_int);
        }
        /* vector_init_n() */
        {
            vector_t* pv_int = create_vector(int);
            if(pv_int == NULL)
            {
                return;
            }

            vector_init_n(pv_int, 3);
            vector_destroy(pv_int);
        }
        /* vector_init_elem() */
        {
            vector_t* pv_int = create_vector(int);
            if(pv_int == NULL)
            {
                return;
            }

            vector_init_elem(pv_int, 3, 100);
            vector_destroy(pv_int);
        }
        /* vector_init_copy() */
        {
            vector_t* pv_int = create_vector(int);
            vector_t* pv_src = create_vector(int);

            if(pv_int == NULL || pv_src == NULL)
            {
                return;
            }

            vector_init_elem(pv_src, 3, -39);
            vector_init_copy(pv_int, pv_src);
            vector_destroy(pv_src);
            vector_destroy(pv_int);
        }
        /* vector_init_copy_range() */
        {
            vector_t* pv_int = create_vector(int);
            vector_t* pv_src = create_vector(int);

            if(pv_int == NULL || pv_src == NULL)
            {
                return;
            }

            vector_init_elem(pv_src, 3, -39);
            vector_init_copy_range(pv_int,
                vector_begin(pv_src), iterator_next(vector_begin(pv_src)));
            vector_destroy(pv_src);
            vector_destroy(pv_int);
        }
        /* vector_size() */
        {
            vector_t* pv_int = create_vector(int);
            if(pv_int == NULL)
            {
                return;
            }

            vector_init_n(pv_int, 100);
            printf("size: %d\n", vector_size(pv_int));
            vector_destroy(pv_int);
        }
        /* vector_capacity() */
        {
            vector_t* pv_int = create_vector(int);
            if(pv_int == NULL)
            {
                return;
            }

            vector_init(pv_int);
            printf("capacity: %d\n", vector_capacity(pv_int));
            vector_destroy(pv_int);
        }
        /* vector_max_size() */
        {
            vector_t* pv_int = create_vector(int);
            if(pv_int == NULL)
            {
                return;
            }

            vector_init_n(pv_int, 20);
            printf("max size: %d\n", vector_max_size(pv_int));
            vector_destroy(pv_int);
        }
        /* vector_empty() */
        {
            vector_t* pv_int = create_vector(int);
            if(pv_int == NULL)
            {
                return;
            }

            vector_init(pv_int);
            printf("empty: %d\n", vector_empty(pv_int));
            vector_push_back(pv_int, 100);
            printf("empty: %d\n", vector_empty(pv_int));
            vector_destroy(pv_int);
        }
        /* vector_reserve() */
        {
            vector_t* pv_int = create_vector(int);
            if(pv_int == NULL)
            {
                return;
            }

            vector_init_elem(pv_int, 2, 33);
            printf("capacity: %d\n", vector_capacity(pv_int));
            vector_reserve(pv_int, 5);
            printf("capacity: %d\n", vector_capacity(pv_int));
            vector_destroy(pv_int);
        }
        /* vector_assign() */
        {
            vector_t* pv_int = create_vector(int);
            vector_t* pv_signed = create_vector(signed);
            if(pv_int == NULL || pv_signed == NULL)
            {
                return;
            }

            vector_init_elem(pv_int, 7, 33);
            vector_init_elem(pv_signed, 5, -200);
            vector_assign(pv_int, pv_signed);
            vector_destroy(pv_int);
            vector_destroy(pv_signed);
        }
        /* vector_assign_elem() */
        {
            vector_t* pv_int = create_vector(int);
            if(pv_int == NULL)
            {
                return;
            }

            vector_init_elem(pv_int, 7, 33);
            vector_assign_elem(pv_int, 3, -88888);
            vector_destroy(pv_int);
        }
        /* vector_assign_range() */
        {
            vector_t* pv_int = create_vector(int);
            vector_t* pv_signed = create_vector(signed);
            if(pv_int == NULL || pv_signed == NULL)
            {
                return;
            }

            vector_init_elem(pv_int, 7, 33);
            vector_init_elem(pv_signed, 5, -200);
            vector_assign_range(pv_int,
                iterator_next(vector_begin(pv_signed)),
                iterator_prev_n(vector_end(pv_signed), 2));
            vector_destroy(pv_int);
            vector_destroy(pv_signed);
        }
        /* vector_equal() */
        {
            vector_t* pv_int = create_vector(int);
            vector_t* pv_signed = create_vector(signed int);
            if(pv_int == NULL || pv_signed == NULL)
            {
                return;
            }

            vector_init_elem(pv_int, 5, 100);
            vector_init_elem(pv_signed, 5, 100);
            printf("equal: %d\n", vector_equal(pv_int, pv_signed));
            vector_destroy(pv_int);
            vector_destroy(pv_signed);
        }
        /* vector_not_equal() */
        {
            vector_t* pv_int = create_vector(int);
            vector_t* pv_signed = create_vector(signed);
            if(pv_int == NULL || pv_signed == NULL)
            {
                return;
            }

            vector_init_elem(pv_int, 3, 300);
            vector_init_elem(pv_signed, 3, 300);
            printf("not equal: %d\n", vector_not_equal(pv_int, pv_signed));
            vector_destroy(pv_int);
            vector_destroy(pv_signed);
        }
        /* vector_less() */
        {
            vector_t* pv_int = create_vector(int);
            vector_t* pv_signed = create_vector(signed);
            if(pv_int == NULL || pv_signed == NULL)
            {
                return;
            }

            vector_init_elem(pv_int, 2, 200);
            vector_init_elem(pv_signed, 2, 200);
            printf("less: %d\n", vector_less(pv_int, pv_signed));
            vector_destroy(pv_int);
            vector_destroy(pv_signed);
        }
        /* vector_less_equal() */
        {
            vector_t* pv_int = create_vector(int);
            vector_t* pv_signed = create_vector(signed);
            if(pv_int == NULL || pv_signed == NULL)
            {
                return;
            }

            vector_init_elem(pv_int, 2, 200);
            vector_init_elem(pv_signed, 2, 200);
            printf("less equal: %d\n", vector_less_equal(pv_int, pv_signed));
            vector_destroy(pv_int);
            vector_destroy(pv_signed);
        }
        /* vector_greater() */
        {
            vector_t* pv_int = create_vector(int);
            vector_t* pv_signed = create_vector(signed);
            if(pv_int == NULL || pv_signed == NULL)
            {
                return;
            }

            vector_init_elem(pv_int, 2, 200);
            vector_init_elem(pv_signed, 2, 200);
            printf("greater: %d\n", vector_greater(pv_int, pv_signed));
            vector_destroy(pv_int);
            vector_destroy(pv_signed);
        }
        /* vector_greater_equal() */
        {
            vector_t* pv_int = create_vector(int);
            vector_t* pv_signed = create_vector(signed);
            if(pv_int == NULL || pv_signed == NULL)
            {
                return;
            }

            vector_init_elem(pv_int, 2, 200);
            vector_init_elem(pv_signed, 2, 200);
            printf("greater equal: %d\n", vector_greater_equal(pv_int, pv_signed));
            vector_destroy(pv_int);
            vector_destroy(pv_signed);
        }
        /* vector_swap() */
        {
            vector_t* pv_int = create_vector(int);
            vector_t* pv_signed = create_vector(signed);
            if(pv_int == NULL || pv_signed == NULL)
            {
                return;
            }

            vector_init_elem(pv_int, 0, 200);
            vector_init_elem(pv_signed, 2, 200);
            vector_swap(pv_int, pv_signed);
            vector_destroy(pv_int);
            vector_destroy(pv_signed);
        }
        /* vector_at() */
        {
            vector_t* pv_int = create_vector(int);
            if(pv_int == NULL)
            {
                return;
            }

            vector_init_elem(pv_int, 10, -99999);
            if(vector_at(pv_int, 4) != NULL)
            {
                printf("%d\n", *(int*)vector_at(pv_int, 4));
            }
            vector_destroy(pv_int);
        }
        /* vector_front() */
        {
            vector_t* pv_int = create_vector(int);
            if(pv_int == NULL)
            {
                return;
            }

            vector_init_n(pv_int, 4);
            if(vector_front(pv_int) != NULL)
            {
                printf("%d\n", *(int*)vector_front(pv_int));
            }
            vector_destroy(pv_int);
        }
        /* vector_back() */
        {
            vector_t* pv_int = create_vector(int);
            if(pv_int == NULL)
            {
                return;
            }

            vector_init_elem(pv_int, 4, -112);
            if(vector_back(pv_int) != NULL)
            {
                printf("%d\n", *(int*)vector_back(pv_int));
            }
            vector_destroy(pv_int);
        }
        /* vector_begin() */
        {
            vector_t* pv_int = create_vector(int);
            if(pv_int == NULL)
            {
                return;
            }

            vector_init_n(pv_int, 10);
            vector_begin(pv_int);
            vector_destroy(pv_int);
        }
        /* vector_end() */
        {
            vector_t* pv_int = create_vector(int);
            if(pv_int == NULL)
            {
                return;
            }

            vector_init_n(pv_int, 10);
            vector_end(pv_int);
            vector_destroy(pv_int);
        }
        /* vector_insert() */
        {
            vector_t* pv_int = create_vector(int);
            if(pv_int == NULL)
            {
                return;
            }

            vector_init(pv_int);
            vector_insert(pv_int, vector_end(pv_int), 10);
            vector_destroy(pv_int);
        }
        /* vector_insert_n() */
        {
            vector_t* pv_int = create_vector(int);
            if(pv_int == NULL)
            {
                return;
            }

            vector_init_n(pv_int, 3);
            vector_insert_n(pv_int, iterator_next(vector_begin(pv_int)), 5, 100);
            vector_destroy(pv_int);
        }
        /* vector_insert_range() */
        {
            vector_t* pv_int = create_vector(int);
            vector_t* pv_insert = create_vector(signed);
            if(pv_int == NULL || pv_insert == NULL)
            {
                return;
            }

            vector_init_elem(pv_int, 3, 12);
            vector_init_elem(pv_insert, 5, 100);
            vector_insert_range(pv_int, vector_end(pv_int),
                iterator_next(vector_begin(pv_insert)), iterator_prev(vector_end(pv_insert)));
            vector_destroy(pv_int);
            vector_destroy(pv_insert);
        }
        /* vector_push_back() */
        {
            vector_t* pv_int = create_vector(int);
            if(pv_int == NULL)
            {
                return;
            }

            vector_init_elem(pv_int, 3, -22);
            vector_push_back(pv_int, 100);
            vector_destroy(pv_int);
        }
        /* vector_pop_back() */
        {
            vector_t* pv_int = create_vector(int);
            if(pv_int == NULL)
            {
                return;
            }

            vector_init(pv_int);
            vector_push_back(pv_int, 100);
            vector_push_back(pv_int, 200);
            vector_push_back(pv_int, 300);
            vector_pop_back(pv_int);
            vector_destroy(pv_int);
        }
        /* vector_erase() */
        {
            vector_t* pv_int = create_vector(int);
            if(pv_int == NULL)
            {
                return;
            }

            vector_init(pv_int);
            vector_push_back(pv_int, 100);
            vector_push_back(pv_int, 200);
            vector_push_back(pv_int, 300);
            vector_erase(pv_int, iterator_next(vector_begin(pv_int)));
            vector_destroy(pv_int);
        }
        /* vector_erase_range() */
        {
            vector_t* pv_int = create_vector(int);
            if(pv_int == NULL)
            {
                return;
            }

            vector_init_elem(pv_int, 10, 100);
            vector_erase_range(pv_int, vector_begin(pv_int),
                iterator_prev_n(vector_end(pv_int), 6));
            vector_destroy(pv_int);
        }
        /* vector_clear() */
        {
            vector_t* pv_int = create_vector(int);
            if(pv_int == NULL)
            {
                return;
            }

            vector_init_elem(pv_int, 10, 100);
            printf("%d\n", vector_empty(pv_int));
            vector_clear(pv_int);
            printf("%d\n", vector_empty(pv_int));
            vector_destroy(pv_int);
        }
        /* vector_resize() */
        {
            vector_t* pv_int = create_vector(int);
            if(pv_int == NULL)
            {
                return;
            }

            vector_init_elem(pv_int, 100, 100);
            printf("%d\n", vector_size(pv_int));
            vector_resize(pv_int, 30);
            printf("%d\n", vector_size(pv_int));
            vector_resize(pv_int, 50);
            printf("%d\n", vector_size(pv_int));
            vector_destroy(pv_int);
        }
        /* vector_resize_elem() */
        {
            vector_t* pv_int = create_vector(int);
            if(pv_int == NULL)
            {
                return;
            }

            vector_init_elem(pv_int, 10, 100);
            printf("%d\n", vector_size(pv_int));
            vector_resize_elem(pv_int, 3, 200);
            printf("%d\n", vector_size(pv_int));
            vector_resize_elem(pv_int, 5, 300);
            printf("%d\n", vector_size(pv_int));
            vector_destroy(pv_int);
        }
    }
    /* user defined type */
    {
        /* create_vector(), vector_init(), vector_destroy() */
        {
            vector_t* pt_abc = NULL;

            type_register(abc_t, _abc_init, _abc_copy, _abc_less, _abc_destroy);
            pt_abc = create_vector(abc_t);
            if(pt_abc == NULL)
            {
                return;
            }

            vector_init(pt_abc);
            vector_destroy(pt_abc);
        }
        /* vector_init_n() */
        {
            vector_t* pt_abc = NULL;
            type_duplicate(abc_t, struct _tagabc);
            _type_debug();
            pt_abc = create_vector(struct _tagabc);
            if(pt_abc == NULL)
            {
                return;
            }
            vector_init_n(pt_abc, 2);
            vector_destroy(pt_abc);
        }
        /* vector_init_elem() */
        {
            vector_t* pt_abc = create_vector(abc_t);
            abc_t t_abc;
            bool_t t_result = false;
            if(pt_abc == NULL)
            {
                return;
            }

            _abc_init(&t_abc, &t_result);
            t_abc._n_first = 100;
            t_abc._d_second = 32.98;
            memset(t_abc._pc_third, 0x33, sizeof(double));

            vector_init_elem(pt_abc, 3, &t_abc);
            vector_destroy(pt_abc);
            _abc_destroy(&t_abc, &t_result);
        }
        /* vector_init_copy() */
        {
            vector_t* pt_abc = create_vector(abc_t);
            vector_t* pt_abcex = create_vector(struct _tagabc);
            abc_t t_abc;
            bool_t t_result = false;
            if(pt_abc == NULL || pt_abcex == NULL)
            {
                return;
            }
            _abc_init(&t_abc, &t_result);
            t_abc._n_first = 12345;
            t_abc._d_second = 0.99;
            memset(t_abc._pc_third, 0x77, sizeof(double));

            vector_init_elem(pt_abcex, 3, &t_abc);
            vector_init_copy(pt_abc, pt_abcex);
            vector_destroy(pt_abc);
            vector_destroy(pt_abcex);
            _abc_destroy(&t_abc, &t_result);
        }
        /* vector_init_copy_range() */
        {
            vector_t* pt_abc = create_vector(abc_t);
            vector_t* pt_abcex = create_vector(struct _tagabc);
            abc_t t_abc;
            bool_t t_result = false;
            if(pt_abc == NULL || pt_abcex == NULL)
            {
                return;
            }
            _abc_init(&t_abc, &t_result);
            t_abc._n_first = 12345;
            t_abc._d_second = 0.99;
            memset(t_abc._pc_third, 0x77, sizeof(double));

            vector_init_elem(pt_abcex, 5, &t_abc);
            vector_init_copy_range(pt_abc,
                iterator_next(vector_begin(pt_abcex)),
                iterator_prev(vector_end(pt_abcex)));
            vector_destroy(pt_abc);
            vector_destroy(pt_abcex);
            _abc_destroy(&t_abc, &t_result);
        }
        /* vector_size() */
        {
            vector_t* pt_abc = create_vector(abc_t);
            if(pt_abc == NULL)
            {
                return;
            }
            vector_init_n(pt_abc, 10);
            printf("%d\n", vector_size(pt_abc));
            vector_destroy(pt_abc);
        }
        /* vector_capacity() */
        {
            vector_t* pt_abc = create_vector(struct _tagabc);
            if(pt_abc == NULL)
            {
                return;
            }
            vector_init_n(pt_abc, 10);
            printf("%d\n", vector_capacity(pt_abc));
            vector_destroy(pt_abc);
        }
        /* vector_max_size() */
        {
            vector_t* pt_abc = create_vector(abc_t);
            if(pt_abc == NULL)
            {
                return;
            }
            vector_init_n(pt_abc, 3);
            printf("%d\n", vector_max_size(pt_abc));
            vector_destroy(pt_abc);
        }
        /* vector_empty() */
        {
            vector_t* pt_abc = create_vector(abc_t);
            if(pt_abc == NULL)
            {
                return;
            }
            vector_init(pt_abc);
            printf("%d\n", vector_empty(pt_abc));
            vector_destroy(pt_abc);
        }
        /* vector_reserve() */
        {
            vector_t* pt_abc = create_vector(abc_t);
            if(pt_abc == NULL)
            {
                return;
            }
            vector_init_n(pt_abc, 2);
            printf("%d\n", vector_capacity(pt_abc));
            vector_reserve(pt_abc, 20);
            printf("%d\n", vector_capacity(pt_abc));
            vector_reserve(pt_abc, 2);
            printf("%d\n", vector_capacity(pt_abc));
            vector_destroy(pt_abc);
        }
        /* vector_assign() */
        {
            vector_t* pt_abc = create_vector(abc_t);
            vector_t* pt_abcex = create_vector(struct _tagabc);
            if(pt_abc == NULL || pt_abcex == NULL)
            {
                return;
            }
            vector_init_n(pt_abc, 1);
            vector_init_n(pt_abcex, 3);
            printf("%d, %d\n", vector_size(pt_abc), vector_size(pt_abcex));
            vector_assign(pt_abc, pt_abcex);
            printf("%d, %d\n", vector_size(pt_abc), vector_size(pt_abcex));
            vector_destroy(pt_abc);
            vector_destroy(pt_abcex);
        }
        /* vector_assign_elem() */
        {
            vector_t* pt_abc = create_vector(abc_t);
            abc_t t_abc;
            if(pt_abc == NULL)
            {
                return;
            }
            vector_init_n(pt_abc, 12);
            printf("%d\n", vector_size(pt_abc));
            t_abc._n_first = 99;
            t_abc._d_second = 34.22;
            t_abc._pc_third = malloc(sizeof(double));
            if(t_abc._pc_third == NULL)
            {
                return;
            }
            *(double*)(t_abc._pc_third) = 344.20;
            vector_assign_elem(pt_abc, 3, &t_abc);
            printf("%d : %d, %lf, %lf\n", vector_size(pt_abc),
                ((abc_t*)vector_front(pt_abc))->_n_first,
                ((abc_t*)vector_front(pt_abc))->_d_second,
                *(double*)((abc_t*)vector_front(pt_abc))->_pc_third);
            vector_destroy(pt_abc);
            free(t_abc._pc_third);
        }
        /* vector_assign_range() */
        {
            vector_t* pt_abc = create_vector(abc_t);
            vector_t* pt_abcex = create_vector(struct _tagabc);
            abc_t t_abc;
            t_abc._pc_third = malloc(sizeof(double));
            if(pt_abc == NULL || t_abc._pc_third == NULL || pt_abcex == NULL)
            {
                return;
            }
            t_abc._n_first = 1000;
            t_abc._d_second = 2000.0002;
            *(double*)t_abc._pc_third = 3000.0003;
            vector_init_n(pt_abc, 2);
            vector_init_elem(pt_abcex, 2, &t_abc);
            t_abc._n_first = 4000;
            t_abc._d_second = 5000.0005;
            *(double*)t_abc._pc_third = 6000.0006;
            vector_push_back(pt_abcex, &t_abc);
            t_abc._n_first = 7000;
            t_abc._d_second = 8000.0008;
            *(double*)t_abc._pc_third = 9000.0009;
            vector_push_back(pt_abcex, &t_abc);
            printf("%d, %d\n", vector_size(pt_abc), vector_size(pt_abcex));
            vector_assign_range(pt_abc,
                vector_begin(pt_abcex), iterator_prev(vector_end(pt_abcex)));
            printf("%d, %d\n", vector_size(pt_abc), vector_size(pt_abcex));
            printf("%d, %lf, %lf\n",
                ((abc_t*)vector_back(pt_abc))->_n_first,
                ((abc_t*)vector_back(pt_abc))->_d_second,
                *(double*)((abc_t*)vector_back(pt_abc))->_pc_third);
            vector_destroy(pt_abc);
            vector_destroy(pt_abcex);
            free(t_abc._pc_third);
        }
        /* vector_equal() */
        {
            vector_t* pt_abc = create_vector(abc_t);
            vector_t* pt_abcex = create_vector(struct _tagabc);
            if(pt_abc == NULL || pt_abcex == NULL)
            {
                return;
            }
            vector_init(pt_abc);
            vector_init(pt_abcex);
            printf("%d\n", vector_equal(pt_abc, pt_abcex));
            vector_destroy(pt_abc);
            vector_destroy(pt_abcex);
        }
        /* vector_not_equal() */
        {
            vector_t* pt_abc = create_vector(abc_t);
            vector_t* pt_abcex = create_vector(struct _tagabc);
            abc_t t_abc;
            t_abc._pc_third = malloc(sizeof(double));
            if(pt_abc == NULL || pt_abcex == NULL || t_abc._pc_third == NULL)
            {
                return;
            }
            t_abc._n_first = 9;
            t_abc._d_second = 123.43;
            *(double*)t_abc._pc_third = 89.444;
            vector_init_n(pt_abc, 3);
            vector_init_elem(pt_abcex, 3, &t_abc);
            printf("%d\n", vector_not_equal(pt_abc, pt_abcex));
            vector_destroy(pt_abc);
            vector_destroy(pt_abcex);
            free(t_abc._pc_third);
        }
        /* vector_less() */
        {
            vector_t* pt_abc = create_vector(abc_t);
            vector_t* pt_abcex = create_vector(struct _tagabc);
            if(pt_abc == NULL || pt_abcex == NULL)
            {
                return;
            }
            vector_init_n(pt_abc, 3);
            vector_init_n(pt_abcex, 3);
            printf("%d\n", vector_less(pt_abc, pt_abcex));
            vector_destroy(pt_abc);
            vector_destroy(pt_abcex);
        }
        /* vector_less_equal() */
        {
            vector_t* pt_abc = create_vector(abc_t);
            vector_t* pt_abcex = create_vector(struct _tagabc);
            if(pt_abc == NULL || pt_abcex == NULL)
            {
                return;
            }
            vector_init_n(pt_abc, 3);
            vector_init_n(pt_abcex, 3);
            printf("%d\n", vector_less_equal(pt_abc, pt_abcex));
            vector_destroy(pt_abc);
            vector_destroy(pt_abcex);
        }
        /* vector_greater() */
        {
            vector_t* pt_abc = create_vector(abc_t);
            vector_t* pt_abcex = create_vector(struct _tagabc);
            abc_t t_abc;
            t_abc._pc_third = malloc(sizeof(double));
            if(pt_abc == NULL || pt_abcex == NULL || t_abc._pc_third == NULL)
            {
                return;
            }
            t_abc._n_first = 9;
            t_abc._d_second = 123.43;
            *(double*)t_abc._pc_third = 89.444;
            vector_init_n(pt_abc, 3);
            vector_init_elem(pt_abcex, 3, &t_abc);
            printf("%d\n", vector_greater(pt_abc, pt_abcex));
            vector_destroy(pt_abc);
            vector_destroy(pt_abcex);
            free(t_abc._pc_third);
        }
        /* vector_greater_equal() */
        {
            vector_t* pt_abc = create_vector(abc_t);
            vector_t* pt_abcex = create_vector(struct _tagabc);
            abc_t t_abc;
            t_abc._pc_third = malloc(sizeof(double));
            if(pt_abc == NULL || pt_abcex == NULL || t_abc._pc_third == NULL)
            {
                return;
            }
            t_abc._n_first = 11119;
            t_abc._d_second = 123.43;
            *(double*)t_abc._pc_third = 89.444;
            vector_init_n(pt_abc, 3);
            vector_init_elem(pt_abcex, 3, &t_abc);
            printf("%d\n", vector_greater_equal(pt_abc, pt_abcex));
            vector_destroy(pt_abc);
            vector_destroy(pt_abcex);
            free(t_abc._pc_third);
        }
        /* vector_swap() */
        {
            vector_t* pt_abc = create_vector(abc_t);
            vector_t* pt_abcex = create_vector(abc_t);
            if(pt_abc == NULL || pt_abcex == NULL)
            {
                return;
            }
            vector_init_n(pt_abc, 2);
            vector_init_n(pt_abcex, 3);
            ((abc_t*)vector_front(pt_abc))->_n_first = 100;
            printf("%d, %d\n",
                ((abc_t*)vector_front(pt_abc))->_n_first,
                ((abc_t*)vector_front(pt_abcex))->_n_first);
            vector_swap(pt_abc, pt_abcex);
            printf("%d, %d\n",
                ((abc_t*)vector_front(pt_abc))->_n_first,
                ((abc_t*)vector_front(pt_abcex))->_n_first);
            vector_destroy(pt_abc);
            vector_destroy(pt_abcex);
        }
        /* vector_at() */
        {
            vector_t* pt_abc = create_vector(abc_t);
            if(pt_abc == NULL)
            {
                return;
            }
            vector_init_n(pt_abc, 3);
            printf("%d\n", ((abc_t*)vector_at(pt_abc, 0))->_n_first);
            ((abc_t*)vector_front(pt_abc))->_n_first = 6666666;
            printf("%d\n", ((abc_t*)vector_at(pt_abc, 0))->_n_first);
            vector_destroy(pt_abc);
        }
        /* vector_front() */
        {
            vector_t* pt_abc = create_vector(abc_t);
            abc_t* pt_tmp = NULL;
            if(pt_abc == NULL)
            {
                return;
            }
            vector_init(pt_abc);
            pt_tmp = (abc_t*)vector_front(pt_abc);
            if(pt_tmp != NULL)
            {
                printf("%d\n", pt_tmp->_n_first);
            }
            else
            {
                printf("no elements\n");
            }
            vector_destroy(pt_abc);
        }
        /* vector_back() */
        {
            vector_t* pt_abc = create_vector(abc_t);
            abc_t* pt_tmp = NULL;
            if(pt_abc == NULL)
            {
                return;
            }
            vector_init_n(pt_abc, 4);
            pt_tmp = (abc_t*)vector_back(pt_abc);
            if(pt_tmp != NULL)
            {
                printf("%d\n", pt_tmp->_n_first);
            }
            else
            {
                printf("no elements\n");
            }
            vector_destroy(pt_abc);
        }
        /* vector_begin() */
        {
            vector_t* pt_abc = create_vector(abc_t);
            iterator_t t_iter;
            if(pt_abc == NULL)
            {
                return;
            }
            vector_init_n(pt_abc, 12);
            for(t_iter = vector_begin(pt_abc);
                !iterator_equal(t_iter, vector_end(pt_abc));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, %lf, %g\n",
                    ((abc_t*)iterator_get_pointer(t_iter))->_n_first,
                    ((abc_t*)iterator_get_pointer(t_iter))->_d_second,
                    *(double*)((abc_t*)iterator_get_pointer(t_iter))->_pc_third);
            }
            vector_destroy(pt_abc);
        }
        /* vector_end() */
        {
            vector_t* pt_abc = create_vector(abc_t);
            iterator_t t_iter;
            if(pt_abc == NULL)
            {
                return;
            }
            vector_init(pt_abc);
            for(t_iter = vector_begin(pt_abc);
                !iterator_equal(t_iter, vector_end(pt_abc));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, %lf, %g\n",
                    ((abc_t*)iterator_get_pointer(t_iter))->_n_first,
                    ((abc_t*)iterator_get_pointer(t_iter))->_d_second,
                    *(double*)((abc_t*)iterator_get_pointer(t_iter))->_pc_third);
            }
            vector_destroy(pt_abc);
        }
        /* vector_insert() */
        {
            vector_t* pt_abc = create_vector(abc_t);
            abc_t t_abc;
            t_abc._pc_third = malloc(sizeof(double));
            if(pt_abc == NULL || t_abc._pc_third == NULL)
            {
                return;
            }
            vector_init(pt_abc);
            t_abc._n_first = 99;
            t_abc._d_second = 23.4;
            *(double*)t_abc._pc_third = 33.22;
            printf("%d\n", vector_size(pt_abc));
            vector_insert(pt_abc, vector_end(pt_abc), &t_abc);
            printf("%d : %d, %lf, %g\n", vector_size(pt_abc),
                ((abc_t*)vector_front(pt_abc))->_n_first,
                ((abc_t*)vector_front(pt_abc))->_d_second,
                *(double*)((abc_t*)vector_front(pt_abc))->_pc_third);
            vector_destroy(pt_abc);
            free(t_abc._pc_third);
        }
        /* vector_insert_n() */
        {
            vector_t* pt_abc = create_vector(abc_t);
            abc_t t_abc;
            iterator_t t_iter;
            t_abc._pc_third = malloc(sizeof(double));
            if(pt_abc == NULL || t_abc._pc_third == NULL)
            {
                return;
            }
            vector_init_n(pt_abc, 3);
            t_abc._n_first = 99;
            t_abc._d_second = 23.4;
            *(double*)t_abc._pc_third = 33.22;
            printf("%d\n", vector_size(pt_abc));
            vector_insert_n(pt_abc, iterator_next(vector_begin(pt_abc)), 4, &t_abc);
            for(t_iter = vector_begin(pt_abc);
                !iterator_equal(t_iter, vector_end(pt_abc));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, %lf, %g\n",
                    ((abc_t*)iterator_get_pointer(t_iter))->_n_first,
                    ((abc_t*)iterator_get_pointer(t_iter))->_d_second,
                    *(double*)((abc_t*)iterator_get_pointer(t_iter))->_pc_third);
            }
            vector_destroy(pt_abc);
            free(t_abc._pc_third);
        }
        /* vector_insert_range() */
        {
            vector_t* pt_abc = create_vector(abc_t);
            vector_t* pt_abcex = create_vector(struct _tagabc);
            abc_t t_abc;
            iterator_t t_iter;
            t_abc._pc_third = malloc(sizeof(double));
            if(pt_abc == NULL || pt_abcex == NULL || t_abc._pc_third == NULL)
            {
                return;
            }
            vector_init_n(pt_abc, 3);
            t_abc._n_first = 99;
            t_abc._d_second = 23.4;
            *(double*)t_abc._pc_third = 33.22;
            vector_init_elem(pt_abcex, 10, &t_abc);
            vector_insert_range(pt_abc, iterator_next(vector_begin(pt_abc)),
                iterator_next(vector_begin(pt_abcex)),
                iterator_prev_n(vector_end(pt_abcex), 3));
            printf("--------------------------------\n");
            for(t_iter = vector_begin(pt_abc);
                !iterator_equal(t_iter, vector_end(pt_abc));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, %lf, %g\n",
                    ((abc_t*)iterator_get_pointer(t_iter))->_n_first,
                    ((abc_t*)iterator_get_pointer(t_iter))->_d_second,
                    *(double*)((abc_t*)iterator_get_pointer(t_iter))->_pc_third);
            }
            vector_destroy(pt_abc);
            vector_destroy(pt_abcex);
            free(t_abc._pc_third);
        }
        /* vector_push_back() */
        {
            vector_t* pt_abc = create_vector(abc_t);
            abc_t t_abc;
            iterator_t t_iter;
            t_abc._pc_third = malloc(sizeof(double));
            if(pt_abc == NULL || t_abc._pc_third == NULL)
            {
                return;
            }
            vector_init(pt_abc);
            t_abc._n_first = 2222;
            t_abc._d_second = 893243.2234;
            *(double*)t_abc._pc_third = 0.000000002143;
            vector_push_back(pt_abc, &t_abc);
            printf("--------------------------------\n");
            for(t_iter = vector_begin(pt_abc);
                !iterator_equal(t_iter, vector_end(pt_abc));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, %lf, %g\n",
                    ((abc_t*)iterator_get_pointer(t_iter))->_n_first,
                    ((abc_t*)iterator_get_pointer(t_iter))->_d_second,
                    *(double*)((abc_t*)iterator_get_pointer(t_iter))->_pc_third);
            }

            t_abc._n_first = -432;
            t_abc._d_second = -7828372.22;
            *(double*)t_abc._pc_third = 3.14e-22;
            vector_push_back(pt_abc, &t_abc);
            printf("--------------------------------\n");
            for(t_iter = vector_begin(pt_abc);
                !iterator_equal(t_iter, vector_end(pt_abc));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, %lf, %g\n",
                    ((abc_t*)iterator_get_pointer(t_iter))->_n_first,
                    ((abc_t*)iterator_get_pointer(t_iter))->_d_second,
                    *(double*)((abc_t*)iterator_get_pointer(t_iter))->_pc_third);
            }

            vector_destroy(pt_abc);
            free(t_abc._pc_third);
        }
        /* vector_pop_back() */
        {
            vector_t* pt_abc = create_vector(abc_t);
            iterator_t t_iter;
            if(pt_abc == NULL)
            {
                return;
            }
            vector_init_n(pt_abc, 2);
            printf("--------------------------------\n");
            for(t_iter = vector_begin(pt_abc);
                !iterator_equal(t_iter, vector_end(pt_abc));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, %lf, %g\n",
                    ((abc_t*)iterator_get_pointer(t_iter))->_n_first,
                    ((abc_t*)iterator_get_pointer(t_iter))->_d_second,
                    *(double*)((abc_t*)iterator_get_pointer(t_iter))->_pc_third);
            }

            vector_pop_back(pt_abc);
            printf("--------------------------------\n");
            for(t_iter = vector_begin(pt_abc);
                !iterator_equal(t_iter, vector_end(pt_abc));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, %lf, %g\n",
                    ((abc_t*)iterator_get_pointer(t_iter))->_n_first,
                    ((abc_t*)iterator_get_pointer(t_iter))->_d_second,
                    *(double*)((abc_t*)iterator_get_pointer(t_iter))->_pc_third);
            }
            vector_pop_back(pt_abc);
            printf("--------------------------------\n");
            for(t_iter = vector_begin(pt_abc);
                !iterator_equal(t_iter, vector_end(pt_abc));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, %lf, %g\n",
                    ((abc_t*)iterator_get_pointer(t_iter))->_n_first,
                    ((abc_t*)iterator_get_pointer(t_iter))->_d_second,
                    *(double*)((abc_t*)iterator_get_pointer(t_iter))->_pc_third);
            }

            vector_destroy(pt_abc);
        }
        /* vector_erase() */
        {
            vector_t* pt_abc = create_vector(abc_t);
            abc_t t_abc;
            iterator_t t_iter;
            t_abc._pc_third = malloc(sizeof(double));
            if(pt_abc == NULL || t_abc._pc_third == NULL)
            {
                return;
            }
            vector_init(pt_abc);
            
            t_abc._n_first = -432;
            t_abc._d_second = -7828372.22;
            *(double*)t_abc._pc_third = 3.14e-22;
            vector_push_back(pt_abc, &t_abc);
            t_abc._n_first = 62;
            t_abc._d_second = 372.02;
            *(double*)t_abc._pc_third = 3.14e22;
            vector_push_back(pt_abc, &t_abc);
            t_abc._n_first = -666;
            t_abc._d_second = -3332222.22;
            *(double*)t_abc._pc_third = 11.4e-22;
            vector_push_back(pt_abc, &t_abc);
            t_abc._n_first = 2;
            t_abc._d_second = 372.22;
            *(double*)t_abc._pc_third = 88883.14e-22;
            vector_push_back(pt_abc, &t_abc);
            t_abc._n_first = 432;
            t_abc._d_second = 7828372.22;
            *(double*)t_abc._pc_third = -3.14e22;
            vector_push_back(pt_abc, &t_abc);
            printf("--------------------------------\n");
            for(t_iter = vector_begin(pt_abc);
                !iterator_equal(t_iter, vector_end(pt_abc));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, %lf, %g\n",
                    ((abc_t*)iterator_get_pointer(t_iter))->_n_first,
                    ((abc_t*)iterator_get_pointer(t_iter))->_d_second,
                    *(double*)((abc_t*)iterator_get_pointer(t_iter))->_pc_third);
            }

            vector_erase(pt_abc, vector_begin(pt_abc));
            printf("--------------------------------\n");
            for(t_iter = vector_begin(pt_abc);
                !iterator_equal(t_iter, vector_end(pt_abc));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, %lf, %g\n",
                    ((abc_t*)iterator_get_pointer(t_iter))->_n_first,
                    ((abc_t*)iterator_get_pointer(t_iter))->_d_second,
                    *(double*)((abc_t*)iterator_get_pointer(t_iter))->_pc_third);
            }

            vector_erase(pt_abc, iterator_prev(vector_end(pt_abc)));
            printf("--------------------------------\n");
            for(t_iter = vector_begin(pt_abc);
                !iterator_equal(t_iter, vector_end(pt_abc));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, %lf, %g\n",
                    ((abc_t*)iterator_get_pointer(t_iter))->_n_first,
                    ((abc_t*)iterator_get_pointer(t_iter))->_d_second,
                    *(double*)((abc_t*)iterator_get_pointer(t_iter))->_pc_third);
            }

            vector_erase(pt_abc, iterator_prev_n(vector_end(pt_abc), 2));
            printf("--------------------------------\n");
            for(t_iter = vector_begin(pt_abc);
                !iterator_equal(t_iter, vector_end(pt_abc));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, %lf, %g\n",
                    ((abc_t*)iterator_get_pointer(t_iter))->_n_first,
                    ((abc_t*)iterator_get_pointer(t_iter))->_d_second,
                    *(double*)((abc_t*)iterator_get_pointer(t_iter))->_pc_third);
            }

            vector_erase(pt_abc, vector_begin(pt_abc));
            vector_erase(pt_abc, vector_begin(pt_abc));
            printf("--------------------------------\n");
            for(t_iter = vector_begin(pt_abc);
                !iterator_equal(t_iter, vector_end(pt_abc));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, %lf, %g\n",
                    ((abc_t*)iterator_get_pointer(t_iter))->_n_first,
                    ((abc_t*)iterator_get_pointer(t_iter))->_d_second,
                    *(double*)((abc_t*)iterator_get_pointer(t_iter))->_pc_third);
            }

            vector_destroy(pt_abc);
            free(t_abc._pc_third);
        }
        /* vector_erase_range() */
        {
            vector_t* pt_abc = create_vector(abc_t);
            abc_t t_abc;
            iterator_t t_iter;
            t_abc._pc_third = malloc(sizeof(double));
            if(pt_abc == NULL || t_abc._pc_third == NULL)
            {
                return;
            }
            vector_init(pt_abc);
            
            t_abc._n_first = 1;
            t_abc._d_second = -7828372.22;
            *(double*)t_abc._pc_third = 3.14e-22;
            vector_push_back(pt_abc, &t_abc);
            t_abc._n_first = 2;
            t_abc._d_second = 372.02;
            *(double*)t_abc._pc_third = 3.14e22;
            vector_push_back(pt_abc, &t_abc);
            t_abc._n_first = 3;
            t_abc._d_second = -3332222.22;
            *(double*)t_abc._pc_third = 11.4e-22;
            vector_push_back(pt_abc, &t_abc);
            t_abc._n_first = 4;
            t_abc._d_second = 372.22;
            *(double*)t_abc._pc_third = 88883.14e-22;
            vector_push_back(pt_abc, &t_abc);
            t_abc._n_first = 5;
            t_abc._d_second = 7828372.22;
            *(double*)t_abc._pc_third = -3.14e22;
            vector_push_back(pt_abc, &t_abc);
            t_abc._n_first = 6;
            t_abc._d_second = 8888888.22;
            *(double*)t_abc._pc_third = -3.14e22;
            vector_push_back(pt_abc, &t_abc);
            t_abc._n_first = 7;
            t_abc._d_second = 1199992.22;
            *(double*)t_abc._pc_third = 3.1422;
            vector_push_back(pt_abc, &t_abc);
            t_abc._n_first = 8;
            t_abc._d_second = -7828372.22;
            *(double*)t_abc._pc_third = 2223.14e21;
            vector_push_back(pt_abc, &t_abc);
            t_abc._n_first = 9;
            t_abc._d_second = 7.22;
            *(double*)t_abc._pc_third = 3.0e22;
            vector_push_back(pt_abc, &t_abc);
            t_abc._n_first = 10;
            t_abc._d_second = 72.22;
            *(double*)t_abc._pc_third = -3.14e22;
            vector_push_back(pt_abc, &t_abc);
            printf("--------------------------------\n");
            for(t_iter = vector_begin(pt_abc);
                !iterator_equal(t_iter, vector_end(pt_abc));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, %lf, %g\n",
                    ((abc_t*)iterator_get_pointer(t_iter))->_n_first,
                    ((abc_t*)iterator_get_pointer(t_iter))->_d_second,
                    *(double*)((abc_t*)iterator_get_pointer(t_iter))->_pc_third);
            }

            vector_erase_range(pt_abc, vector_begin(pt_abc), vector_begin(pt_abc));
            printf("--------------------------------\n");
            for(t_iter = vector_begin(pt_abc);
                !iterator_equal(t_iter, vector_end(pt_abc));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, %lf, %g\n",
                    ((abc_t*)iterator_get_pointer(t_iter))->_n_first,
                    ((abc_t*)iterator_get_pointer(t_iter))->_d_second,
                    *(double*)((abc_t*)iterator_get_pointer(t_iter))->_pc_third);
            }

            vector_erase_range(pt_abc, vector_begin(pt_abc),
                iterator_next_n(vector_begin(pt_abc), 2));
            printf("--------------------------------\n");
            for(t_iter = vector_begin(pt_abc);
                !iterator_equal(t_iter, vector_end(pt_abc));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, %lf, %g\n",
                    ((abc_t*)iterator_get_pointer(t_iter))->_n_first,
                    ((abc_t*)iterator_get_pointer(t_iter))->_d_second,
                    *(double*)((abc_t*)iterator_get_pointer(t_iter))->_pc_third);
            }

            vector_erase_range(pt_abc, iterator_prev_n(vector_end(pt_abc), 2),
                vector_end(pt_abc));
            printf("--------------------------------\n");
            for(t_iter = vector_begin(pt_abc);
                !iterator_equal(t_iter, vector_end(pt_abc));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, %lf, %g\n",
                    ((abc_t*)iterator_get_pointer(t_iter))->_n_first,
                    ((abc_t*)iterator_get_pointer(t_iter))->_d_second,
                    *(double*)((abc_t*)iterator_get_pointer(t_iter))->_pc_third);
            }

            vector_erase_range(pt_abc, iterator_next(vector_begin(pt_abc)),
                iterator_prev_n(vector_end(pt_abc), 2));
            printf("--------------------------------\n");
            for(t_iter = vector_begin(pt_abc);
                !iterator_equal(t_iter, vector_end(pt_abc));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, %lf, %g\n",
                    ((abc_t*)iterator_get_pointer(t_iter))->_n_first,
                    ((abc_t*)iterator_get_pointer(t_iter))->_d_second,
                    *(double*)((abc_t*)iterator_get_pointer(t_iter))->_pc_third);
            }

            vector_erase_range(pt_abc, vector_begin(pt_abc), vector_end(pt_abc));
            printf("--------------------------------\n");
            for(t_iter = vector_begin(pt_abc);
                !iterator_equal(t_iter, vector_end(pt_abc));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, %lf, %g\n",
                    ((abc_t*)iterator_get_pointer(t_iter))->_n_first,
                    ((abc_t*)iterator_get_pointer(t_iter))->_d_second,
                    *(double*)((abc_t*)iterator_get_pointer(t_iter))->_pc_third);
            }

            vector_destroy(pt_abc);
            free(t_abc._pc_third);
        }
        /* vector_clear() */
        {
            vector_t* pt_abc = create_vector(abc_t);
            abc_t t_abc;
            iterator_t t_iter;
            t_abc._pc_third = malloc(sizeof(double));
            if(pt_abc == NULL || t_abc._pc_third == NULL)
            {
                return;
            }
            vector_init(pt_abc);
            
            vector_clear(pt_abc);
            printf("--------------------------------\n");
            for(t_iter = vector_begin(pt_abc);
                !iterator_equal(t_iter, vector_end(pt_abc));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, %lf, %g\n",
                    ((abc_t*)iterator_get_pointer(t_iter))->_n_first,
                    ((abc_t*)iterator_get_pointer(t_iter))->_d_second,
                    *(double*)((abc_t*)iterator_get_pointer(t_iter))->_pc_third);
            }
            t_abc._n_first = 1;
            t_abc._d_second = -7828372.22;
            *(double*)t_abc._pc_third = 3.14e-22;
            vector_push_back(pt_abc, &t_abc);
            t_abc._n_first = 2;
            t_abc._d_second = 372.02;
            *(double*)t_abc._pc_third = 3.14e22;
            vector_push_back(pt_abc, &t_abc);
            t_abc._n_first = 3;
            t_abc._d_second = -3332222.22;
            *(double*)t_abc._pc_third = 11.4e-22;
            vector_push_back(pt_abc, &t_abc);
            t_abc._n_first = 4;
            t_abc._d_second = 372.22;
            *(double*)t_abc._pc_third = 88883.14e-22;
            vector_push_back(pt_abc, &t_abc);
            t_abc._n_first = 5;
            t_abc._d_second = 7828372.22;
            *(double*)t_abc._pc_third = -3.14e22;
            vector_push_back(pt_abc, &t_abc);
            t_abc._n_first = 6;
            t_abc._d_second = 8888888.22;
            *(double*)t_abc._pc_third = -3.14e22;
            vector_push_back(pt_abc, &t_abc);
            t_abc._n_first = 7;
            t_abc._d_second = 1199992.22;
            *(double*)t_abc._pc_third = 3.1422;
            vector_push_back(pt_abc, &t_abc);
            t_abc._n_first = 8;
            t_abc._d_second = -7828372.22;
            *(double*)t_abc._pc_third = 2223.14e21;
            vector_push_back(pt_abc, &t_abc);
            t_abc._n_first = 9;
            t_abc._d_second = 7.22;
            *(double*)t_abc._pc_third = 3.0e22;
            vector_push_back(pt_abc, &t_abc);
            t_abc._n_first = 10;
            t_abc._d_second = 72.22;
            *(double*)t_abc._pc_third = -3.14e22;
            vector_push_back(pt_abc, &t_abc);
            printf("--------------------------------\n");
            for(t_iter = vector_begin(pt_abc);
                !iterator_equal(t_iter, vector_end(pt_abc));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, %lf, %g\n",
                    ((abc_t*)iterator_get_pointer(t_iter))->_n_first,
                    ((abc_t*)iterator_get_pointer(t_iter))->_d_second,
                    *(double*)((abc_t*)iterator_get_pointer(t_iter))->_pc_third);
            }
            vector_clear(pt_abc);
            printf("--------------------------------\n");
            for(t_iter = vector_begin(pt_abc);
                !iterator_equal(t_iter, vector_end(pt_abc));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, %lf, %g\n",
                    ((abc_t*)iterator_get_pointer(t_iter))->_n_first,
                    ((abc_t*)iterator_get_pointer(t_iter))->_d_second,
                    *(double*)((abc_t*)iterator_get_pointer(t_iter))->_pc_third);
            }

            vector_destroy(pt_abc);
            free(t_abc._pc_third);
        }
        /* vector_resize() */
        {
            vector_t* pt_abc = create_vector(abc_t);
            iterator_t t_iter;
            if(pt_abc == NULL)
            {
                return;
            }
            vector_init(pt_abc);
            printf("--------------------------------\n");
            for(t_iter = vector_begin(pt_abc);
                !iterator_equal(t_iter, vector_end(pt_abc));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, %lf, %g\n",
                    ((abc_t*)iterator_get_pointer(t_iter))->_n_first,
                    ((abc_t*)iterator_get_pointer(t_iter))->_d_second,
                    *(double*)((abc_t*)iterator_get_pointer(t_iter))->_pc_third);
            }
            vector_resize(pt_abc, 3);
            printf("--------------------------------\n");
            for(t_iter = vector_begin(pt_abc);
                !iterator_equal(t_iter, vector_end(pt_abc));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, %lf, %g\n",
                    ((abc_t*)iterator_get_pointer(t_iter))->_n_first,
                    ((abc_t*)iterator_get_pointer(t_iter))->_d_second,
                    *(double*)((abc_t*)iterator_get_pointer(t_iter))->_pc_third);
            }
            vector_resize(pt_abc, 6);
            printf("--------------------------------\n");
            for(t_iter = vector_begin(pt_abc);
                !iterator_equal(t_iter, vector_end(pt_abc));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, %lf, %g\n",
                    ((abc_t*)iterator_get_pointer(t_iter))->_n_first,
                    ((abc_t*)iterator_get_pointer(t_iter))->_d_second,
                    *(double*)((abc_t*)iterator_get_pointer(t_iter))->_pc_third);
            }
            vector_resize(pt_abc, 2);
            printf("--------------------------------\n");
            for(t_iter = vector_begin(pt_abc);
                !iterator_equal(t_iter, vector_end(pt_abc));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, %lf, %g\n",
                    ((abc_t*)iterator_get_pointer(t_iter))->_n_first,
                    ((abc_t*)iterator_get_pointer(t_iter))->_d_second,
                    *(double*)((abc_t*)iterator_get_pointer(t_iter))->_pc_third);
            }
            vector_destroy(pt_abc);
        }
        /* vector_resize_elem() */
        {
            vector_t* pt_abc = create_vector(abc_t);
            iterator_t t_iter;
            abc_t t_abc;
            t_abc._pc_third = malloc(sizeof(double));
            if(pt_abc == NULL || t_abc._pc_third == NULL)
            {
                return;
            }
            vector_init(pt_abc);
            printf("--------------------------------\n");
            for(t_iter = vector_begin(pt_abc);
                !iterator_equal(t_iter, vector_end(pt_abc));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, %lf, %g\n",
                    ((abc_t*)iterator_get_pointer(t_iter))->_n_first,
                    ((abc_t*)iterator_get_pointer(t_iter))->_d_second,
                    *(double*)((abc_t*)iterator_get_pointer(t_iter))->_pc_third);
            }
            t_abc._n_first = 1;
            t_abc._d_second = -7828372.22;
            *(double*)t_abc._pc_third = 3.14e-22;
            vector_resize_elem(pt_abc, 3, &t_abc);
            printf("--------------------------------\n");
            for(t_iter = vector_begin(pt_abc);
                !iterator_equal(t_iter, vector_end(pt_abc));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, %lf, %g\n",
                    ((abc_t*)iterator_get_pointer(t_iter))->_n_first,
                    ((abc_t*)iterator_get_pointer(t_iter))->_d_second,
                    *(double*)((abc_t*)iterator_get_pointer(t_iter))->_pc_third);
            }
            t_abc._n_first = 2;
            t_abc._d_second = 372.77;
            *(double*)t_abc._pc_third = 351.22;
            vector_resize_elem(pt_abc, 6, &t_abc);
            printf("--------------------------------\n");
            for(t_iter = vector_begin(pt_abc);
                !iterator_equal(t_iter, vector_end(pt_abc));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, %lf, %g\n",
                    ((abc_t*)iterator_get_pointer(t_iter))->_n_first,
                    ((abc_t*)iterator_get_pointer(t_iter))->_d_second,
                    *(double*)((abc_t*)iterator_get_pointer(t_iter))->_pc_third);
            }
            t_abc._n_first = 3;
            t_abc._d_second = 372.77;
            *(double*)t_abc._pc_third = 351.22;
            vector_resize(pt_abc, 2);
            printf("--------------------------------\n");
            for(t_iter = vector_begin(pt_abc);
                !iterator_equal(t_iter, vector_end(pt_abc));
                t_iter = iterator_next(t_iter))
            {
                printf("%d, %lf, %g\n",
                    ((abc_t*)iterator_get_pointer(t_iter))->_n_first,
                    ((abc_t*)iterator_get_pointer(t_iter))->_d_second,
                    *(double*)((abc_t*)iterator_get_pointer(t_iter))->_pc_third);
            }
            vector_destroy(pt_abc);
            free(t_abc._pc_third);
        }
    }
    /* libcstl builtin type */
    {
        /* create_vector(), vector_init(), vector_destroy() */
        {
            vector_t* pt_vec = create_vector(vector_t<int>);
            if(pt_vec == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            vector_destroy(pt_vec);
        }
        /* vector_init_n() */
        {
            vector_t* pt_vec = create_vector(vector_t<int>);
            if(pt_vec == NULL)
            {
                return;
            }
            vector_init_n(pt_vec, 3);
            vector_destroy(pt_vec);
        }
        /* vector_init_elem() */
        {
            vector_t* pt_vec = create_vector(vector_t<int>);
            vector_t* pt_int = create_vector(signed);
            if(pt_vec == NULL || pt_int == NULL)
            {
                return;
            }
            vector_init_n(pt_int, 3);
            vector_init_elem(pt_vec, 2, pt_int);
            vector_destroy(pt_int);
            vector_destroy(pt_vec);
        }
        /* vector_init_copy() */
        {
            vector_t* pt_vec = create_vector(vector_t<int>);
            vector_t* pt_vecex = create_vector(vector_t<int>);
            if(pt_vec == NULL || pt_vecex == NULL)
            {
                return;
            }
            vector_init_n(pt_vecex, 3);
            vector_init_copy(pt_vec, pt_vecex);
            vector_destroy(pt_vecex);
            vector_destroy(pt_vec);
        }
        /* vector_init_copy_range() */
        {
            vector_t* pt_vec = create_vector(vector_t<int>);
            vector_t* pt_vecex = create_vector(vector_t<int>);
            if(pt_vec == NULL || pt_vecex == NULL)
            {
                return;
            }
            vector_init_n(pt_vecex, 3);
            vector_init_copy_range(pt_vec,
                vector_begin(pt_vecex), iterator_prev(vector_end(pt_vecex)));
            vector_destroy(pt_vecex);
            vector_destroy(pt_vec);
        }
        /* vector_size() */
        {
            vector_t* pt_vec = create_vector(vector_t<double>);
            vector_t* pt_vecex = create_vector(double);
            if(pt_vec == NULL || pt_vecex == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            vector_init_elem(pt_vecex, 3, 89.033);
            printf("%d\n", vector_size(pt_vec));
            vector_push_back(pt_vec, pt_vecex);
            printf("%d\n", vector_size(pt_vec));
            vector_push_back(pt_vec, pt_vecex);
            printf("%d\n", vector_size(pt_vec));
            vector_destroy(pt_vec);
            vector_destroy(pt_vecex);
        }
        /* vector_capacity() */
        {
            vector_t* pt_vec = create_vector(vector_t<vector_t<double>>);
            vector_t* pt_vecex1 = create_vector(vector_t<double>);
            vector_t* pt_vecex2 = create_vector(double);
            if(pt_vec == NULL || pt_vecex1 == NULL || pt_vecex2 == NULL)
            {
                return;
            }
            vector_init_elem(pt_vecex2, 2, -22.424);
            vector_init_elem(pt_vecex1, 4, pt_vecex2);
            vector_init(pt_vec);
            printf("%d\n", vector_capacity(pt_vec));
            vector_push_back(pt_vec, pt_vecex1);
            printf("%d\n", vector_capacity(pt_vec));
            vector_destroy(pt_vec);
            vector_destroy(pt_vecex1);
            vector_destroy(pt_vecex2);
        }
        /* vector_max_size() */
        {
            vector_t* pt_vec = create_vector(vector_t<long>);
            if(pt_vec == NULL)
            {
                return;
            }
            vector_init_n(pt_vec,3);
            printf("%d\n", vector_max_size(pt_vec));
            vector_destroy(pt_vec);
        }
        /* vector_empty() */
        {
            vector_t* pt_vec = create_vector(vector_t<long double>);
            if(pt_vec == NULL)
            {
                return;
            }
            vector_init_n(pt_vec, 3);
            printf("%d\n", vector_empty(pt_vec));
            vector_destroy(pt_vec);
        }
        /* vector_reserve() */
        {
            vector_t* pt_vec = create_vector(vector_t<signed short>);
            if(pt_vec == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            printf("%d\n", vector_capacity(pt_vec));
            vector_reserve(pt_vec, 0);
            printf("%d\n", vector_capacity(pt_vec));
            vector_reserve(pt_vec, 12);
            printf("%d\n", vector_capacity(pt_vec));
            vector_reserve(pt_vec, 3);
            printf("%d\n", vector_capacity(pt_vec));
            vector_destroy(pt_vec);
        }
        /* vector_assign() */
        {
            vector_t* pt_vec = create_vector(vector_t<char>);
            vector_t* pt_vecex1 = create_vector(vector_t<signed char>);
            vector_t* pt_vecex2 = create_vector(char);
            iterator_t t_iter;
            iterator_t t_iterex2;
            if(pt_vec == NULL || pt_vecex1 == NULL || pt_vecex2 == NULL)
            {
                return;
            }
            vector_init(pt_vecex2);
            vector_init(pt_vecex1);
            vector_init(pt_vec);
            vector_push_back(pt_vecex2, 'u');
            vector_push_back(pt_vec, pt_vecex2);
            vector_push_back(pt_vecex2, 'U');
            vector_push_back(pt_vecex1, pt_vecex2);
            printf("before:\n");
            printf("vec:\n");
            for(t_iter = vector_begin(pt_vec);
                !iterator_equal(t_iter, vector_end(pt_vec));
                t_iter = iterator_next(t_iter))
            {
                for(t_iterex2 = vector_begin((vector_t*)iterator_get_pointer(t_iter));
                    !iterator_equal(t_iterex2, vector_end((vector_t*)iterator_get_pointer(t_iter)));
                    t_iterex2 = iterator_next(t_iterex2))
                {
                    printf("%c, ", *(char*)iterator_get_pointer(t_iterex2));
                }
                printf("\n");

            }
            printf("vecex1:\n");
            for(t_iter = vector_begin(pt_vecex1);
                !iterator_equal(t_iter, vector_end(pt_vecex1));
                t_iter = iterator_next(t_iter))
            {
                for(t_iterex2 = vector_begin((vector_t*)iterator_get_pointer(t_iter));
                    !iterator_equal(t_iterex2, vector_end((vector_t*)iterator_get_pointer(t_iter)));
                    t_iterex2 = iterator_next(t_iterex2))
                {
                    printf("%c, ", *(char*)iterator_get_pointer(t_iterex2));
                }
                printf("\n");

            }
            vector_assign(pt_vec, pt_vecex1);
            printf("after:\n");
            printf("vec:\n");
            for(t_iter = vector_begin(pt_vec);
                !iterator_equal(t_iter, vector_end(pt_vec));
                t_iter = iterator_next(t_iter))
            {
                for(t_iterex2 = vector_begin((vector_t*)iterator_get_pointer(t_iter));
                    !iterator_equal(t_iterex2, vector_end((vector_t*)iterator_get_pointer(t_iter)));
                    t_iterex2 = iterator_next(t_iterex2))
                {
                    printf("%c, ", *(char*)iterator_get_pointer(t_iterex2));
                }
                printf("\n");

            }
            printf("vecex1:\n");
            for(t_iter = vector_begin(pt_vecex1);
                !iterator_equal(t_iter, vector_end(pt_vecex1));
                t_iter = iterator_next(t_iter))
            {
                for(t_iterex2 = vector_begin((vector_t*)iterator_get_pointer(t_iter));
                    !iterator_equal(t_iterex2, vector_end((vector_t*)iterator_get_pointer(t_iter)));
                    t_iterex2 = iterator_next(t_iterex2))
                {
                    printf("%c, ", *(char*)iterator_get_pointer(t_iterex2));
                }
                printf("\n");

            }
            vector_destroy(pt_vec);
            vector_destroy(pt_vecex1);
            vector_destroy(pt_vecex2);
        }
        /* vector_assign_elem() */
        {
            vector_t* pt_vec = create_vector(vector_t<signed long int>);
            vector_t* pt_vecex = create_vector(long);
            iterator_t t_iter;
            iterator_t t_iterex;
            if(pt_vec == NULL || pt_vecex == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            vector_init(pt_vecex);
            vector_push_back(pt_vecex, 1000);
            vector_push_back(pt_vecex, 2000);
            vector_push_back(pt_vecex, 3000);
            printf("before:\n");
            for(t_iter = vector_begin(pt_vec);
                !iterator_equal(t_iter, vector_end(pt_vec));
                t_iter = iterator_next(t_iter))
            {
                for(t_iterex = vector_begin((vector_t*)iterator_get_pointer(t_iter));
                    !iterator_equal(t_iterex, vector_end((vector_t*)iterator_get_pointer(t_iter)));
                    t_iterex = iterator_next(t_iterex))
                {
                    printf("%ld, ", *(long*)iterator_get_pointer(t_iterex));
                }
                printf("\n");
            }
            vector_assign_elem(pt_vec, 3, pt_vecex);
            printf("after:\n");
            for(t_iter = vector_begin(pt_vec);
                !iterator_equal(t_iter, vector_end(pt_vec));
                t_iter = iterator_next(t_iter))
            {
                for(t_iterex = vector_begin((vector_t*)iterator_get_pointer(t_iter));
                    !iterator_equal(t_iterex, vector_end((vector_t*)iterator_get_pointer(t_iter)));
                    t_iterex = iterator_next(t_iterex))
                {
                    printf("%ld, ", *(long*)iterator_get_pointer(t_iterex));
                }
                printf("\n");
            }
            vector_destroy(pt_vec);
            vector_destroy(pt_vecex);
        }
        /* vector_assign_range() */
        {
            vector_t* pt_vec = create_vector(vector_t<char>);
            vector_t* pt_vecex1 = create_vector(vector_t<signed char>);
            vector_t* pt_vecex2 = create_vector(char);
            iterator_t t_iter;
            iterator_t t_iterex2;
            if(pt_vec == NULL || pt_vecex1 == NULL || pt_vecex2 == NULL)
            {
                return;
            }
            vector_init(pt_vecex2);
            vector_init(pt_vecex1);
            vector_init(pt_vec);
            vector_push_back(pt_vecex2, 'L');
            vector_push_back(pt_vecex1, pt_vecex2);
            vector_push_back(pt_vecex2, 'O');
            vector_push_back(pt_vecex1, pt_vecex2);
            vector_push_back(pt_vecex2, 'V');
            vector_push_back(pt_vecex1, pt_vecex2);
            vector_push_back(pt_vecex2, 'E');
            vector_push_back(pt_vecex1, pt_vecex2);
            printf("before:\n");
            printf("vec:\n");
            for(t_iter = vector_begin(pt_vec);
                !iterator_equal(t_iter, vector_end(pt_vec));
                t_iter = iterator_next(t_iter))
            {
                for(t_iterex2 = vector_begin((vector_t*)iterator_get_pointer(t_iter));
                    !iterator_equal(t_iterex2, vector_end((vector_t*)iterator_get_pointer(t_iter)));
                    t_iterex2 = iterator_next(t_iterex2))
                {
                    printf("%c, ", *(char*)iterator_get_pointer(t_iterex2));
                }
                printf("\n");

            }
            printf("vecex1:\n");
            for(t_iter = vector_begin(pt_vecex1);
                !iterator_equal(t_iter, vector_end(pt_vecex1));
                t_iter = iterator_next(t_iter))
            {
                for(t_iterex2 = vector_begin((vector_t*)iterator_get_pointer(t_iter));
                    !iterator_equal(t_iterex2, vector_end((vector_t*)iterator_get_pointer(t_iter)));
                    t_iterex2 = iterator_next(t_iterex2))
                {
                    printf("%c, ", *(char*)iterator_get_pointer(t_iterex2));
                }
                printf("\n");

            }
            vector_assign_range(pt_vec, iterator_next(vector_begin(pt_vecex1)), vector_end(pt_vecex1));
            printf("after:\n");
            printf("vec:\n");
            for(t_iter = vector_begin(pt_vec);
                !iterator_equal(t_iter, vector_end(pt_vec));
                t_iter = iterator_next(t_iter))
            {
                for(t_iterex2 = vector_begin((vector_t*)iterator_get_pointer(t_iter));
                    !iterator_equal(t_iterex2, vector_end((vector_t*)iterator_get_pointer(t_iter)));
                    t_iterex2 = iterator_next(t_iterex2))
                {
                    printf("%c, ", *(char*)iterator_get_pointer(t_iterex2));
                }
                printf("\n");

            }
            printf("vecex1:\n");
            for(t_iter = vector_begin(pt_vecex1);
                !iterator_equal(t_iter, vector_end(pt_vecex1));
                t_iter = iterator_next(t_iter))
            {
                for(t_iterex2 = vector_begin((vector_t*)iterator_get_pointer(t_iter));
                    !iterator_equal(t_iterex2, vector_end((vector_t*)iterator_get_pointer(t_iter)));
                    t_iterex2 = iterator_next(t_iterex2))
                {
                    printf("%c, ", *(char*)iterator_get_pointer(t_iterex2));
                }
                printf("\n");

            }
            vector_destroy(pt_vec);
            vector_destroy(pt_vecex1);
            vector_destroy(pt_vecex2);
        }
        /* vector_equal() */
        {
            vector_t* pt_vec = create_vector(vector_t<unsigned long>);
            vector_t* pt_vecex = create_vector(vector_t<unsigned long int>);
            vector_t* pt_vecex1 = create_vector(unsigned long);
            iterator_t t_iter;
            iterator_t t_iterex;
            if(pt_vec == NULL || pt_vecex == NULL || pt_vecex1 == NULL)
            {
                return;
            }
            vector_init(pt_vecex1);
            vector_init(pt_vecex);
            vector_init(pt_vec);
            vector_push_back(pt_vecex1, 344);
            vector_push_back(pt_vecex, pt_vecex1);
            vector_push_back(pt_vecex1, 23099);
            *(unsigned long*)vector_front(pt_vecex1) = 222;
            vector_push_back(pt_vec, pt_vecex1);
            printf("vec:\n");
            for(t_iter = vector_begin(pt_vec);
                !iterator_equal(t_iter, vector_end(pt_vec));
                t_iter = iterator_next(t_iter))
            {
                for(t_iterex = vector_begin((vector_t*)iterator_get_pointer(t_iter));
                    !iterator_equal(t_iterex, vector_end((vector_t*)iterator_get_pointer(t_iter)));
                    t_iterex = iterator_next(t_iterex))
                {
                    printf("%lu, ", *(unsigned long*)iterator_get_pointer(t_iterex));
                }
                printf("\n");
            }
            printf("vecex:\n");
            for(t_iter = vector_begin(pt_vecex);
                !iterator_equal(t_iter, vector_end(pt_vecex));
                t_iter = iterator_next(t_iter))
            {
                for(t_iterex = vector_begin((vector_t*)iterator_get_pointer(t_iter));
                    !iterator_equal(t_iterex, vector_end((vector_t*)iterator_get_pointer(t_iter)));
                    t_iterex = iterator_next(t_iterex))
                {
                    printf("%lu, ", *(unsigned long*)iterator_get_pointer(t_iterex));
                }
                printf("\n");
            }
            printf("equal: %d\n", vector_equal(pt_vec, pt_vecex));
            printf("not equal: %d\n", vector_not_equal(pt_vec, pt_vecex));
            printf("less: %d\n", vector_less(pt_vec, pt_vecex));
            printf("less equal: %d\n", vector_less_equal(pt_vec, pt_vecex));
            printf("greater: %d\n", vector_greater(pt_vec, pt_vecex));
            printf("greater equal: %d\n", vector_greater_equal(pt_vec, pt_vecex));
            vector_destroy(pt_vec);
            vector_destroy(pt_vecex);
            vector_destroy(pt_vecex1);
        }
        /* vector_not_equal() */
        {
        }
        /* vector_less() */
        {
        }
        /* vector_less_equal() */
        {
        }
        /* vector_greater() */
        {
        }
        /* vector_greater_equal() */
        {
        }
        /* vector_swap() */
        {
            vector_t* pt_vecex1 = create_vector(vector_t<double>);
            vector_t* pt_vecex2 = create_vector(vector_t<double>);
            vector_t* pt_vec = create_vector(double);
            iterator_t t_iter;
            iterator_t t_iterex;
            if(pt_vecex1 == NULL || pt_vecex2 == NULL || pt_vec == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            vector_init(pt_vecex1);
            vector_init_n(pt_vecex2, 3);
            vector_push_back(pt_vec, 23.994);
            vector_push_back(pt_vec, 11.0003);
            vector_push_back(pt_vecex1, pt_vec);
            vector_clear(pt_vec);
            vector_push_back(pt_vec, 0.43);
            vector_push_back(pt_vecex1, pt_vec);
            vector_clear(pt_vec);
            vector_push_back(pt_vecex1, pt_vec);
            vector_push_back(pt_vec, -34.2e12);
            vector_push_back(pt_vec, 3.0009112);
            vector_push_back(pt_vec, 3.3333e-5);
            vector_push_back(pt_vec, -5.3e-53);
            vector_push_back(pt_vecex1, pt_vec);

            vector_clear(pt_vec);
            vector_push_back(pt_vecex2, pt_vec);
            vector_push_back(pt_vec, 88.888);
            vector_push_back(pt_vec, 2e-4);
            vector_push_back(pt_vecex2, pt_vec);
            vector_push_back(pt_vecex2, pt_vec);
            printf("before swap:\n");
            printf("vecex1 : size: %d, capacity:%d, max_size: %d\n",
                vector_size(pt_vecex1), vector_capacity(pt_vecex1), vector_max_size(pt_vecex1));
            for(t_iterex = vector_begin(pt_vecex1);
                !iterator_equal(t_iterex, vector_end(pt_vecex1));
                t_iterex = iterator_next(t_iterex))
            {
                for(t_iter = vector_begin((vector_t*)iterator_get_pointer(t_iterex));
                    !iterator_equal(t_iter, vector_end((vector_t*)iterator_get_pointer(t_iterex)));
                    t_iter = iterator_next(t_iter))
                {
                    printf("%g, ", *(double*)iterator_get_pointer(t_iter));
                }
                printf("\n");
            }
            printf("vecex2 : size: %d, capacity:%d, max_size: %d\n",
                vector_size(pt_vecex2), vector_capacity(pt_vecex2), vector_max_size(pt_vecex2));
            for(t_iterex = vector_begin(pt_vecex2);
                !iterator_equal(t_iterex, vector_end(pt_vecex2));
                t_iterex = iterator_next(t_iterex))
            {
                for(t_iter = vector_begin((vector_t*)iterator_get_pointer(t_iterex));
                    !iterator_equal(t_iter, vector_end((vector_t*)iterator_get_pointer(t_iterex)));
                    t_iter = iterator_next(t_iter))
                {
                    printf("%g, ", *(double*)iterator_get_pointer(t_iter));
                }
                printf("\n");
            }
            vector_swap(pt_vecex1, pt_vecex2);
            printf("after swap:\n");
            printf("vecex1 : size: %d, capacity:%d, max_size: %d\n",
                vector_size(pt_vecex1), vector_capacity(pt_vecex1), vector_max_size(pt_vecex1));
            for(t_iterex = vector_begin(pt_vecex1);
                !iterator_equal(t_iterex, vector_end(pt_vecex1));
                t_iterex = iterator_next(t_iterex))
            {
                for(t_iter = vector_begin((vector_t*)iterator_get_pointer(t_iterex));
                    !iterator_equal(t_iter, vector_end((vector_t*)iterator_get_pointer(t_iterex)));
                    t_iter = iterator_next(t_iter))
                {
                    printf("%g, ", *(double*)iterator_get_pointer(t_iter));
                }
                printf("\n");
            }
            printf("vecex2 : size: %d, capacity:%d, max_size: %d\n",
                vector_size(pt_vecex2), vector_capacity(pt_vecex2), vector_max_size(pt_vecex2));
            for(t_iterex = vector_begin(pt_vecex2);
                !iterator_equal(t_iterex, vector_end(pt_vecex2));
                t_iterex = iterator_next(t_iterex))
            {
                for(t_iter = vector_begin((vector_t*)iterator_get_pointer(t_iterex));
                    !iterator_equal(t_iter, vector_end((vector_t*)iterator_get_pointer(t_iterex)));
                    t_iter = iterator_next(t_iter))
                {
                    printf("%g, ", *(double*)iterator_get_pointer(t_iter));
                }
                printf("\n");
            }
            vector_destroy(pt_vec);
            vector_destroy(pt_vecex1);
            vector_destroy(pt_vecex2);
        }
        /* vector_at() */
        {
            vector_t* pt_vec = create_vector(vector_t<double>);
            vector_t* pt_vecex = create_vector(double);
            iterator_t t_iter;
            if(pt_vec == NULL || pt_vecex == NULL)
            {
                return;
            }
            vector_init_n(pt_vec, 2);
            vector_init(pt_vecex);
            vector_push_back(pt_vecex, 34.99);
            vector_push_back(pt_vecex, 2.0);
            vector_push_back(pt_vecex, 222.222);
            vector_assign(vector_at(pt_vec, vector_size(pt_vec)-1), pt_vecex);
            for(t_iter = vector_begin(vector_at(pt_vec, vector_size(pt_vec)-1));
                !iterator_equal(t_iter, vector_end(vector_at(pt_vec, vector_size(pt_vec)-1)));
                t_iter = iterator_next(t_iter))
            {
                printf("%g, ", *(double*)iterator_get_pointer(t_iter));
            }
            printf("\n");
            vector_destroy(pt_vec);
            vector_destroy(pt_vecex);
        }
        /* vector_front() */
        {
            vector_t* pt_vec = create_vector(vector_t<signed>);
            vector_t* pt_vecex = create_vector(int);
            if(pt_vec == NULL || pt_vecex == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            vector_init(pt_vecex);
            vector_push_back(pt_vecex, 89);
            vector_push_back(pt_vecex, 222);
            vector_push_back(pt_vecex, 12);
            vector_push_back(pt_vec, pt_vecex);
            if(vector_front(pt_vec) != NULL)
            {
                iterator_t t_iter;
                for(t_iter = vector_begin(vector_front(pt_vec));
                    !iterator_equal(t_iter, vector_end(vector_front(pt_vec)));
                    t_iter = iterator_next(t_iter))
                {
                    printf("%d, ", *(int*)iterator_get_pointer(t_iter));
                }
                printf("\n");
            }
            vector_destroy(pt_vec);
            vector_destroy(pt_vecex);
        }
        /* vector_back() */
        {
            vector_t* pt_vec = create_vector(vector_t<signed>);
            vector_t* pt_vecex = create_vector(int);
            if(pt_vec == NULL || pt_vecex == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            vector_init(pt_vecex);
            vector_push_back(pt_vecex, 89);
            vector_push_back(pt_vecex, 222);
            vector_push_back(pt_vecex, 12);
            vector_push_back(pt_vec, pt_vecex);
            vector_clear(pt_vecex);
            vector_push_back(pt_vecex, -23);
            vector_push_back(pt_vecex, -22222);
            vector_push_back(pt_vec, pt_vecex);
            if(vector_back(pt_vec) != NULL)
            {
                iterator_t t_iter;
                for(t_iter = vector_begin(vector_back(pt_vec));
                    !iterator_equal(t_iter, vector_end(vector_back(pt_vec)));
                    t_iter = iterator_next(t_iter))
                {
                    printf("%d, ", *(int*)iterator_get_pointer(t_iter));
                }
                printf("\n");
            }
            vector_destroy(pt_vec);
            vector_destroy(pt_vecex);
        }
        /* vector_begin() */
        {
        }
        /* vector_end() */
        {
        }
        /* vector_insert() */
        {
            vector_t* pt_vec = create_vector(vector_t<double>);
            vector_t* pt_vecex = create_vector(double);
            iterator_t t_iter;
            iterator_t t_iterex;
            if(pt_vec == NULL || pt_vecex == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            vector_init(pt_vecex);
            vector_push_back(pt_vecex, 4.30092);
            vector_push_back(pt_vecex, 23.333135);
            vector_insert(pt_vec, vector_begin(pt_vec), pt_vecex);
            for(t_iter = vector_begin(pt_vec);
                !iterator_equal(t_iter, vector_end(pt_vec));
                t_iter = iterator_next(t_iter))
            {
                for(t_iterex = vector_begin(iterator_get_pointer(t_iter));
                    !iterator_equal(t_iterex, vector_end(iterator_get_pointer(t_iter)));
                    t_iterex = iterator_next(t_iterex))
                {
                    printf("%g, ", *(double*)iterator_get_pointer(t_iterex));
                }
                printf("\n");
            }
            vector_clear(pt_vecex);
            vector_push_back(pt_vecex, 2.0e5);
            vector_push_back(pt_vecex, 4.9e-9);
            vector_push_back(pt_vecex, -33.3e-4);
            vector_insert(pt_vec, vector_begin(pt_vec), pt_vecex);
            for(t_iter = vector_begin(pt_vec);
                !iterator_equal(t_iter, vector_end(pt_vec));
                t_iter = iterator_next(t_iter))
            {
                for(t_iterex = vector_begin(iterator_get_pointer(t_iter));
                    !iterator_equal(t_iterex, vector_end(iterator_get_pointer(t_iter)));
                    t_iterex = iterator_next(t_iterex))
                {
                    printf("%g, ", *(double*)iterator_get_pointer(t_iterex));
                }
                printf("\n");
            }
            vector_clear(pt_vecex);
            vector_push_back(pt_vecex, 6.3e3);
            vector_push_back(pt_vecex, 9.845e-29);
            vector_push_back(pt_vecex, -3.09e-14);
            vector_insert(pt_vec, iterator_next(vector_begin(pt_vec)), pt_vecex);
            for(t_iter = vector_begin(pt_vec);
                !iterator_equal(t_iter, vector_end(pt_vec));
                t_iter = iterator_next(t_iter))
            {
                for(t_iterex = vector_begin(iterator_get_pointer(t_iter));
                    !iterator_equal(t_iterex, vector_end(iterator_get_pointer(t_iter)));
                    t_iterex = iterator_next(t_iterex))
                {
                    printf("%g, ", *(double*)iterator_get_pointer(t_iterex));
                }
                printf("\n");
            }
            vector_destroy(pt_vec);
            vector_destroy(pt_vecex);
        }
        /* vector_insert_n() */
        {
            vector_t* pt_vec = create_vector(vector_t<float>);
            vector_t* pt_vecex = create_vector(float);
            iterator_t t_iter;
            iterator_t t_iterex;
            if(pt_vec == NULL || pt_vecex == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            vector_init(pt_vecex);
            vector_push_back(pt_vecex, 4.30092);
            vector_push_back(pt_vecex, 23.333135);
            vector_insert_n(pt_vec, vector_begin(pt_vec), 3, pt_vecex);
            printf("\n");
            for(t_iter = vector_begin(pt_vec);
                !iterator_equal(t_iter, vector_end(pt_vec));
                t_iter = iterator_next(t_iter))
            {
                for(t_iterex = vector_begin(iterator_get_pointer(t_iter));
                    !iterator_equal(t_iterex, vector_end(iterator_get_pointer(t_iter)));
                    t_iterex = iterator_next(t_iterex))
                {
                    printf("%f, ", *(float*)iterator_get_pointer(t_iterex));
                }
                printf("\n");
            }
            vector_clear(pt_vecex);
            vector_push_back(pt_vecex, 2.0e5);
            vector_push_back(pt_vecex, 4.9e-2);
            vector_push_back(pt_vecex, -33.3e-4);
            vector_insert_n(pt_vec, vector_begin(pt_vec), 2, pt_vecex);
            for(t_iter = vector_begin(pt_vec);
                !iterator_equal(t_iter, vector_end(pt_vec));
                t_iter = iterator_next(t_iter))
            {
                for(t_iterex = vector_begin(iterator_get_pointer(t_iter));
                    !iterator_equal(t_iterex, vector_end(iterator_get_pointer(t_iter)));
                    t_iterex = iterator_next(t_iterex))
                {
                    printf("%f, ", *(float*)iterator_get_pointer(t_iterex));
                }
                printf("\n");
            }
            vector_clear(pt_vecex);
            vector_push_back(pt_vecex, 6.3e3);
            vector_push_back(pt_vecex, 9.845e-2);
            vector_push_back(pt_vecex, -3.09e-3);
            vector_insert_n(pt_vec, iterator_next(vector_begin(pt_vec)), 5, pt_vecex);
            for(t_iter = vector_begin(pt_vec);
                !iterator_equal(t_iter, vector_end(pt_vec));
                t_iter = iterator_next(t_iter))
            {
                for(t_iterex = vector_begin(iterator_get_pointer(t_iter));
                    !iterator_equal(t_iterex, vector_end(iterator_get_pointer(t_iter)));
                    t_iterex = iterator_next(t_iterex))
                {
                    printf("%f, ", *(float*)iterator_get_pointer(t_iterex));
                }
                printf("\n");
            }
            vector_destroy(pt_vec);
            vector_destroy(pt_vecex);
        }
        /* vector_insert_range() */
        {
            vector_t* pt_vec = create_vector(unsigned);
            vector_t* pt_vecex1 = create_vector(vector_t<unsigned>);
            vector_t* pt_vecex2 = create_vector(vector_t<unsigned int>);
            vector_iterator_t t_iter;
            vector_iterator_t t_iterex;
            if(pt_vec == NULL || pt_vecex1 == NULL || pt_vecex2 == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            vector_init(pt_vecex1);
            vector_init(pt_vecex2);
            vector_push_back(pt_vec, 12);
            vector_push_back(pt_vec, 30);
            vector_push_back(pt_vec, 1998);
            vector_push_back(pt_vecex1, pt_vec);
            vector_push_back(pt_vecex1, pt_vec);
            vector_clear(pt_vec);
            vector_push_back(pt_vec, 222);
            vector_push_back(pt_vecex1, pt_vec);
            vector_push_back(pt_vec, 0);
            vector_push_back(pt_vec, 4444);
            vector_push_back(pt_vec, 209);
            vector_push_back(pt_vecex1, pt_vec);
            vector_clear(pt_vec);
            vector_push_back(pt_vec, 667);
            vector_push_back(pt_vec, 766);
            vector_push_back(pt_vecex1, pt_vec);
            printf("vecex1:\n");
            for(t_iterex = vector_begin(pt_vecex1);
                !iterator_equal(t_iterex, vector_end(pt_vecex1));
                t_iterex = iterator_next(t_iterex))
            {
                for(t_iter = vector_begin(iterator_get_pointer(t_iterex));
                    !iterator_equal(t_iter, vector_end(iterator_get_pointer(t_iterex)));
                    t_iter = iterator_next(t_iter))
                {
                    printf("%d, ", *(unsigned*)iterator_get_pointer(t_iter));
                }
                printf("\n");
            }
            vector_insert_range(pt_vecex2, vector_end(pt_vecex2), 
                vector_begin(pt_vecex1), vector_end(pt_vecex1));
            printf("vecex2:\n");
            for(t_iterex = vector_begin(pt_vecex2);
                !iterator_equal(t_iterex, vector_end(pt_vecex2));
                t_iterex = iterator_next(t_iterex))
            {
                for(t_iter = vector_begin(iterator_get_pointer(t_iterex));
                    !iterator_equal(t_iter, vector_end(iterator_get_pointer(t_iterex)));
                    t_iter = iterator_next(t_iter))
                {
                    printf("%d, ", *(unsigned*)iterator_get_pointer(t_iter));
                }
                printf("\n");
            }
            vector_insert_range(pt_vecex2, vector_begin(pt_vecex2), 
                iterator_next_n(vector_begin(pt_vecex1), 2), vector_end(pt_vecex1));
            printf("vecex2:\n");
            for(t_iterex = vector_begin(pt_vecex2);
                !iterator_equal(t_iterex, vector_end(pt_vecex2));
                t_iterex = iterator_next(t_iterex))
            {
                for(t_iter = vector_begin(iterator_get_pointer(t_iterex));
                    !iterator_equal(t_iter, vector_end(iterator_get_pointer(t_iterex)));
                    t_iter = iterator_next(t_iter))
                {
                    printf("%d, ", *(unsigned*)iterator_get_pointer(t_iter));
                }
                printf("\n");
            }
            vector_insert_range(pt_vecex2, iterator_next_n(vector_begin(pt_vecex2), 5), 
                iterator_next_n(vector_begin(pt_vecex1), 2),
                iterator_prev(vector_end(pt_vecex1)));
            printf("vecex2:\n");
            for(t_iterex = vector_begin(pt_vecex2);
                !iterator_equal(t_iterex, vector_end(pt_vecex2));
                t_iterex = iterator_next(t_iterex))
            {
                for(t_iter = vector_begin(iterator_get_pointer(t_iterex));
                    !iterator_equal(t_iter, vector_end(iterator_get_pointer(t_iterex)));
                    t_iter = iterator_next(t_iter))
                {
                    printf("%d, ", *(unsigned*)iterator_get_pointer(t_iter));
                }
                printf("\n");
            }
            vector_destroy(pt_vec);
            vector_destroy(pt_vecex1);
            vector_destroy(pt_vecex2);
        }
        /* vector_push_back() */
        {
        }
        /* vector_pop_back() */
        {
            vector_t* pt_vec = create_vector(vector_t<char>);
            vector_t* pt_vecex = create_vector(signed char);
            iterator_t t_iter;
            iterator_t t_iterex;
            if(pt_vec == NULL || pt_vecex == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            vector_init(pt_vecex);
            vector_push_back(pt_vecex, '9');
            vector_push_back(pt_vecex, 'r');
            vector_push_back(pt_vecex, 'G');
            vector_push_back(pt_vec, pt_vecex);
            vector_clear(pt_vecex);
            vector_push_back(pt_vecex, '#');
            vector_push_back(pt_vecex, '^');
            vector_push_back(pt_vecex, '@');
            vector_push_back(pt_vecex, '~');
            vector_push_back(pt_vec, pt_vecex);
            for(t_iter = vector_begin(pt_vec);
                !iterator_equal(t_iter, vector_end(pt_vec));
                t_iter = iterator_next(t_iter))
            {
                for(t_iterex = vector_begin(iterator_get_pointer(t_iter));
                    !iterator_equal(t_iterex, vector_end(iterator_get_pointer(t_iter)));
                    t_iterex = iterator_next(t_iterex))
                {
                    printf("%c, ", *(char*)iterator_get_pointer(t_iterex));
                }
                printf("\n");
            }
            printf("\n");
            vector_pop_back(pt_vec);
            for(t_iter = vector_begin(pt_vec);
                !iterator_equal(t_iter, vector_end(pt_vec));
                t_iter = iterator_next(t_iter))
            {
                for(t_iterex = vector_begin(iterator_get_pointer(t_iter));
                    !iterator_equal(t_iterex, vector_end(iterator_get_pointer(t_iter)));
                    t_iterex = iterator_next(t_iterex))
                {
                    printf("%c, ", *(char*)iterator_get_pointer(t_iterex));
                }
                printf("\n");
            }
            printf("\n");
            vector_pop_back(pt_vec);
            for(t_iter = vector_begin(pt_vec);
                !iterator_equal(t_iter, vector_end(pt_vec));
                t_iter = iterator_next(t_iter))
            {
                for(t_iterex = vector_begin(iterator_get_pointer(t_iter));
                    !iterator_equal(t_iterex, vector_end(iterator_get_pointer(t_iter)));
                    t_iterex = iterator_next(t_iterex))
                {
                    printf("%c, ", *(char*)iterator_get_pointer(t_iterex));
                }
                printf("\n");
            }
            printf("\n");
            vector_destroy(pt_vec);
            vector_destroy(pt_vecex);
        }
        /* vector_erase() */
        {
            vector_t* pt_vec = create_vector(vector_t<long>);
            vector_t* pt_vecex = create_vector(signed long int);
            iterator_t t_iter;
            iterator_t t_iterex;
            if(pt_vec == NULL || pt_vecex == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            vector_init(pt_vecex);
            vector_push_back(pt_vecex, 112);
            vector_push_back(pt_vecex, -2409);
            vector_push_back(pt_vec, pt_vecex);
            vector_clear(pt_vecex);
            vector_insert_n(pt_vecex, vector_begin(pt_vecex), 4, -87654);
            vector_push_back(pt_vec, pt_vecex);
            vector_push_back(pt_vecex, 234);
            vector_push_back(pt_vecex, 112);
            vector_push_back(pt_vec, pt_vecex);
            for(t_iter = vector_begin(pt_vec);
                !iterator_equal(t_iter, vector_end(pt_vec));
                t_iter = iterator_next(t_iter))
            {
                for(t_iterex = vector_begin(iterator_get_pointer(t_iter));
                    !iterator_equal(t_iterex, vector_end(iterator_get_pointer(t_iter)));
                    t_iterex = iterator_next(t_iterex))
                {
                    printf("%ld, ", *(long*)iterator_get_pointer(t_iterex));
                }
                printf("\n");
            }
            printf("erase middle:\n");
            vector_erase(pt_vec, iterator_next(vector_begin(pt_vec)));
            for(t_iter = vector_begin(pt_vec);
                !iterator_equal(t_iter, vector_end(pt_vec));
                t_iter = iterator_next(t_iter))
            {
                for(t_iterex = vector_begin(iterator_get_pointer(t_iter));
                    !iterator_equal(t_iterex, vector_end(iterator_get_pointer(t_iter)));
                    t_iterex = iterator_next(t_iterex))
                {
                    printf("%ld, ", *(long*)iterator_get_pointer(t_iterex));
                }
                printf("\n");
            }
            printf("erase begin:\n");
            vector_erase(pt_vec, vector_begin(pt_vec));
            for(t_iter = vector_begin(pt_vec);
                !iterator_equal(t_iter, vector_end(pt_vec));
                t_iter = iterator_next(t_iter))
            {
                for(t_iterex = vector_begin(iterator_get_pointer(t_iter));
                    !iterator_equal(t_iterex, vector_end(iterator_get_pointer(t_iter)));
                    t_iterex = iterator_next(t_iterex))
                {
                    printf("%ld, ", *(long*)iterator_get_pointer(t_iterex));
                }
                printf("\n");
            }
            printf("erase prev end:\n");
            vector_erase(pt_vec, iterator_prev(vector_end(pt_vec)));
            for(t_iter = vector_begin(pt_vec);
                !iterator_equal(t_iter, vector_end(pt_vec));
                t_iter = iterator_next(t_iter))
            {
                for(t_iterex = vector_begin(iterator_get_pointer(t_iter));
                    !iterator_equal(t_iterex, vector_end(iterator_get_pointer(t_iter)));
                    t_iterex = iterator_next(t_iterex))
                {
                    printf("%ld, ", *(long*)iterator_get_pointer(t_iterex));
                }
                printf("\n");
            }
            vector_destroy(pt_vec);
            vector_destroy(pt_vecex);
        }
        /* vector_erase_range() */
        {
            vector_t* pt_vec = create_vector(vector_t<long>);
            vector_t* pt_vecex = create_vector(signed long int);
            iterator_t t_iter;
            iterator_t t_iterex;
            if(pt_vec == NULL || pt_vecex == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            vector_init(pt_vecex);
            vector_push_back(pt_vecex, 112);
            vector_push_back(pt_vecex, -2409);
            vector_push_back(pt_vec, pt_vecex);
            vector_clear(pt_vecex);
            vector_insert_n(pt_vecex, vector_begin(pt_vecex), 4, -87654);
            vector_push_back(pt_vec, pt_vecex);
            vector_push_back(pt_vecex, 234);
            vector_push_back(pt_vecex, 112);
            vector_push_back(pt_vec, pt_vecex);
            vector_clear(pt_vecex);
            vector_push_back(pt_vecex, 23);
            vector_push_back(pt_vecex, -9765);
            vector_push_back(pt_vecex, 898);
            vector_push_back(pt_vec, pt_vecex);
            vector_clear(pt_vecex);
            vector_push_back(pt_vecex, 28);
            vector_push_back(pt_vecex, 5);
            vector_push_back(pt_vecex, -33898);
            vector_push_back(pt_vec, pt_vecex);
            vector_clear(pt_vecex);
            vector_push_back(pt_vecex, 333);
            vector_push_back(pt_vecex, 74);
            vector_push_back(pt_vecex, -8);
            vector_push_back(pt_vec, pt_vecex);
            vector_clear(pt_vecex);
            vector_push_back(pt_vecex, 2355);
            vector_push_back(pt_vecex, 5);
            vector_push_back(pt_vecex, 0);
            vector_push_back(pt_vec, pt_vecex);
            vector_clear(pt_vecex);
            vector_push_back(pt_vecex, -23);
            vector_push_back(pt_vecex, -9765);
            vector_push_back(pt_vecex, -898);
            vector_push_back(pt_vec, pt_vecex);
            vector_clear(pt_vecex);
            vector_push_back(pt_vecex, -3);
            vector_push_back(pt_vecex, -65);
            vector_push_back(pt_vecex, 8);
            vector_push_back(pt_vec, pt_vecex);
            for(t_iter = vector_begin(pt_vec);
                !iterator_equal(t_iter, vector_end(pt_vec));
                t_iter = iterator_next(t_iter))
            {
                for(t_iterex = vector_begin(iterator_get_pointer(t_iter));
                    !iterator_equal(t_iterex, vector_end(iterator_get_pointer(t_iter)));
                    t_iterex = iterator_next(t_iterex))
                {
                    printf("%ld, ", *(long*)iterator_get_pointer(t_iterex));
                }
                printf("\n");
            }
            printf("erase middle:\n");
            vector_erase_range(pt_vec,
                iterator_next(vector_begin(pt_vec)),
                iterator_next_n(vector_begin(pt_vec), 3));
            for(t_iter = vector_begin(pt_vec);
                !iterator_equal(t_iter, vector_end(pt_vec));
                t_iter = iterator_next(t_iter))
            {
                for(t_iterex = vector_begin(iterator_get_pointer(t_iter));
                    !iterator_equal(t_iterex, vector_end(iterator_get_pointer(t_iter)));
                    t_iterex = iterator_next(t_iterex))
                {
                    printf("%ld, ", *(long*)iterator_get_pointer(t_iterex));
                }
                printf("\n");
            }
            printf("erase begin:\n");
            vector_erase_range(pt_vec, vector_begin(pt_vec),
                iterator_next_n(vector_begin(pt_vec), 2));
            for(t_iter = vector_begin(pt_vec);
                !iterator_equal(t_iter, vector_end(pt_vec));
                t_iter = iterator_next(t_iter))
            {
                for(t_iterex = vector_begin(iterator_get_pointer(t_iter));
                    !iterator_equal(t_iterex, vector_end(iterator_get_pointer(t_iter)));
                    t_iterex = iterator_next(t_iterex))
                {
                    printf("%ld, ", *(long*)iterator_get_pointer(t_iterex));
                }
                printf("\n");
            }
            printf("erase prev end:\n");
            vector_erase_range(pt_vec, iterator_prev_n(vector_end(pt_vec), 3),
                vector_end(pt_vec));
            for(t_iter = vector_begin(pt_vec);
                !iterator_equal(t_iter, vector_end(pt_vec));
                t_iter = iterator_next(t_iter))
            {
                for(t_iterex = vector_begin(iterator_get_pointer(t_iter));
                    !iterator_equal(t_iterex, vector_end(iterator_get_pointer(t_iter)));
                    t_iterex = iterator_next(t_iterex))
                {
                    printf("%ld, ", *(long*)iterator_get_pointer(t_iterex));
                }
                printf("\n");
            }
            vector_destroy(pt_vec);
            vector_destroy(pt_vecex);
        }
        /* vector_clear() */
        {
            vector_t* pt_vec = create_vector(vector_t<long>);
            vector_t* pt_vecex = create_vector(signed long int);
            iterator_t t_iter;
            iterator_t t_iterex;
            if(pt_vec == NULL || pt_vecex == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            vector_init(pt_vecex);
            vector_push_back(pt_vecex, 112);
            vector_push_back(pt_vecex, -2409);
            vector_push_back(pt_vec, pt_vecex);
            vector_clear(pt_vecex);
            vector_insert_n(pt_vecex, vector_begin(pt_vecex), 4, -87654);
            vector_push_back(pt_vec, pt_vecex);
            vector_push_back(pt_vecex, 234);
            vector_push_back(pt_vecex, 112);
            vector_push_back(pt_vec, pt_vecex);
            vector_clear(pt_vecex);
            vector_push_back(pt_vecex, 23);
            vector_push_back(pt_vecex, -9765);
            vector_push_back(pt_vecex, 898);
            vector_push_back(pt_vec, pt_vecex);
            vector_clear(pt_vecex);
            vector_push_back(pt_vecex, 28);
            vector_push_back(pt_vecex, 5);
            vector_push_back(pt_vecex, -33898);
            vector_push_back(pt_vec, pt_vecex);
            vector_clear(pt_vecex);
            vector_push_back(pt_vecex, 333);
            vector_push_back(pt_vecex, 74);
            vector_push_back(pt_vecex, -8);
            vector_push_back(pt_vec, pt_vecex);
            vector_clear(pt_vecex);
            vector_push_back(pt_vecex, 2355);
            vector_push_back(pt_vecex, 5);
            vector_push_back(pt_vecex, 0);
            vector_push_back(pt_vec, pt_vecex);
            vector_clear(pt_vecex);
            vector_push_back(pt_vecex, -23);
            vector_push_back(pt_vecex, -9765);
            vector_push_back(pt_vecex, -898);
            vector_push_back(pt_vec, pt_vecex);
            vector_clear(pt_vecex);
            vector_push_back(pt_vecex, -3);
            vector_push_back(pt_vecex, -65);
            vector_push_back(pt_vecex, 8);
            vector_push_back(pt_vec, pt_vecex);
            for(t_iter = vector_begin(pt_vec);
                !iterator_equal(t_iter, vector_end(pt_vec));
                t_iter = iterator_next(t_iter))
            {
                for(t_iterex = vector_begin(iterator_get_pointer(t_iter));
                    !iterator_equal(t_iterex, vector_end(iterator_get_pointer(t_iter)));
                    t_iterex = iterator_next(t_iterex))
                {
                    printf("%ld, ", *(long*)iterator_get_pointer(t_iterex));
                }
                printf("\n");
            }
            printf("clear:\n");
            vector_clear(pt_vec);
            for(t_iter = vector_begin(pt_vec);
                !iterator_equal(t_iter, vector_end(pt_vec));
                t_iter = iterator_next(t_iter))
            {
                for(t_iterex = vector_begin(iterator_get_pointer(t_iter));
                    !iterator_equal(t_iterex, vector_end(iterator_get_pointer(t_iter)));
                    t_iterex = iterator_next(t_iterex))
                {
                    printf("%ld, ", *(long*)iterator_get_pointer(t_iterex));
                }
                printf("\n");
            }
            vector_destroy(pt_vec);
            vector_destroy(pt_vecex);
        }
        /* vector_resize() */
        {
            vector_t* pt_vec = create_vector(vector_t<long>);
            vector_t* pt_vecex = create_vector(signed long int);
            iterator_t t_iter;
            iterator_t t_iterex;
            if(pt_vec == NULL || pt_vecex == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            vector_init(pt_vecex);
            vector_push_back(pt_vecex, 112);
            vector_push_back(pt_vecex, -2409);
            vector_push_back(pt_vec, pt_vecex);
            vector_clear(pt_vecex);
            vector_insert_n(pt_vecex, vector_begin(pt_vecex), 4, -87654);
            vector_push_back(pt_vec, pt_vecex);
            vector_push_back(pt_vecex, 234);
            vector_push_back(pt_vecex, 112);
            vector_push_back(pt_vec, pt_vecex);
            vector_clear(pt_vecex);
            vector_push_back(pt_vecex, 23);
            vector_push_back(pt_vecex, -9765);
            vector_push_back(pt_vecex, 898);
            vector_push_back(pt_vec, pt_vecex);
            vector_clear(pt_vecex);
            vector_push_back(pt_vecex, 28);
            vector_push_back(pt_vecex, 5);
            vector_push_back(pt_vecex, -33898);
            vector_push_back(pt_vec, pt_vecex);
            vector_clear(pt_vecex);
            vector_push_back(pt_vecex, 333);
            vector_push_back(pt_vecex, 74);
            vector_push_back(pt_vecex, -8);
            vector_push_back(pt_vec, pt_vecex);
            vector_clear(pt_vecex);
            vector_push_back(pt_vecex, 2355);
            vector_push_back(pt_vecex, 5);
            vector_push_back(pt_vecex, 0);
            vector_push_back(pt_vec, pt_vecex);
            vector_clear(pt_vecex);
            vector_push_back(pt_vecex, -23);
            vector_push_back(pt_vecex, -9765);
            vector_push_back(pt_vecex, -898);
            vector_push_back(pt_vec, pt_vecex);
            vector_clear(pt_vecex);
            vector_push_back(pt_vecex, -3);
            vector_push_back(pt_vecex, -65);
            vector_push_back(pt_vecex, 8);
            vector_push_back(pt_vec, pt_vecex);
            for(t_iter = vector_begin(pt_vec);
                !iterator_equal(t_iter, vector_end(pt_vec));
                t_iter = iterator_next(t_iter))
            {
                for(t_iterex = vector_begin(iterator_get_pointer(t_iter));
                    !iterator_equal(t_iterex, vector_end(iterator_get_pointer(t_iter)));
                    t_iterex = iterator_next(t_iterex))
                {
                    printf("%ld, ", *(long*)iterator_get_pointer(t_iterex));
                }
                printf("\n");
            }
            printf("resize: 3\n");
            vector_resize(pt_vec, 3);
            for(t_iter = vector_begin(pt_vec);
                !iterator_equal(t_iter, vector_end(pt_vec));
                t_iter = iterator_next(t_iter))
            {
                for(t_iterex = vector_begin(iterator_get_pointer(t_iter));
                    !iterator_equal(t_iterex, vector_end(iterator_get_pointer(t_iter)));
                    t_iterex = iterator_next(t_iterex))
                {
                    printf("%ld, ", *(long*)iterator_get_pointer(t_iterex));
                }
                printf("\n");
            }
            printf("resize: 6\n");
            vector_resize(pt_vec, 6);
            for(t_iter = vector_begin(pt_vec);
                !iterator_equal(t_iter, vector_end(pt_vec));
                t_iter = iterator_next(t_iter))
            {
                for(t_iterex = vector_begin(iterator_get_pointer(t_iter));
                    !iterator_equal(t_iterex, vector_end(iterator_get_pointer(t_iter)));
                    t_iterex = iterator_next(t_iterex))
                {
                    printf("%ld, ", *(long*)iterator_get_pointer(t_iterex));
                }
                printf("\n");
            }
            vector_destroy(pt_vec);
            vector_destroy(pt_vecex);
        }
        /* vector_resize_elem() */
        {
            vector_t* pt_vec = create_vector(vector_t<double>);
            vector_t* pt_vecex = create_vector(double);
            iterator_t t_iter;
            iterator_t t_iterex;
            if(pt_vec == NULL || pt_vecex == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            vector_init(pt_vecex);
            printf("no resize:\n");
            for(t_iter = vector_begin(pt_vec);
                !iterator_equal(t_iter, vector_end(pt_vec));
                t_iter = iterator_next(t_iter))
            {
                for(t_iterex = vector_begin(iterator_get_pointer(t_iter));
                    !iterator_equal(t_iterex, vector_end(iterator_get_pointer(t_iter)));
                    t_iterex = iterator_next(t_iterex))
                {
                    printf("%lf, ", *(double*)iterator_get_pointer(t_iterex));
                }
                printf("\n");
            }
            printf("resize: 3\n");
            vector_insert_n(pt_vecex, vector_begin(pt_vecex), 3, 90.34);
            vector_resize_elem(pt_vec, 3, pt_vecex);
            for(t_iter = vector_begin(pt_vec);
                !iterator_equal(t_iter, vector_end(pt_vec));
                t_iter = iterator_next(t_iter))
            {
                for(t_iterex = vector_begin(iterator_get_pointer(t_iter));
                    !iterator_equal(t_iterex, vector_end(iterator_get_pointer(t_iter)));
                    t_iterex = iterator_next(t_iterex))
                {
                    printf("%lf, ", *(double*)iterator_get_pointer(t_iterex));
                }
                printf("\n");
            }
            printf("resize: 6\n");
            vector_clear(pt_vecex);
            vector_insert_n(pt_vecex, vector_begin(pt_vecex), 5, -0.009);
            vector_resize_elem(pt_vec, 6, pt_vecex);
            for(t_iter = vector_begin(pt_vec);
                !iterator_equal(t_iter, vector_end(pt_vec));
                t_iter = iterator_next(t_iter))
            {
                for(t_iterex = vector_begin(iterator_get_pointer(t_iter));
                    !iterator_equal(t_iterex, vector_end(iterator_get_pointer(t_iter)));
                    t_iterex = iterator_next(t_iterex))
                {
                    printf("%lf, ", *(double*)iterator_get_pointer(t_iterex));
                }
                printf("\n");
            }
            printf("resize: 4\n");
            vector_resize_elem(pt_vec, 4, pt_vecex);
            for(t_iter = vector_begin(pt_vec);
                !iterator_equal(t_iter, vector_end(pt_vec));
                t_iter = iterator_next(t_iter))
            {
                for(t_iterex = vector_begin(iterator_get_pointer(t_iter));
                    !iterator_equal(t_iterex, vector_end(iterator_get_pointer(t_iter)));
                    t_iterex = iterator_next(t_iterex))
                {
                    printf("%lf, ", *(double*)iterator_get_pointer(t_iterex));
                }
                printf("\n");
            }
            vector_destroy(pt_vec);
            vector_destroy(pt_vecex);
        }
    }
    /* c-string type */
    {
        /* create_vector(), vector_init(), vector_destroy() */
        {
            vector_t* pt_vec = create_vector(char*);
            if(pt_vec == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            _print_vec_str(pt_vec);
            vector_destroy(pt_vec);
        }
        /* vector_init_n() */
        {
            vector_t* pt_vec = create_vector(char*);
            if(pt_vec == NULL)
            {
                return;
            }
            vector_init_n(pt_vec, 4);
            _print_vec_str(pt_vec);
            vector_destroy(pt_vec);
        }
        /* vector_init_elem() */
        {
            vector_t* pt_vec = create_vector(char     *);
            char s_str[31] = {'\0'};
            if(pt_vec == NULL)
            {
                return;
            }
            strncpy(s_str, "Hello every body!", 30);
            vector_init_elem(pt_vec, 3, s_str);
            _print_vec_str(pt_vec);
            vector_destroy(pt_vec);
        }
        /* vector_init_copy() */
        {
            vector_t* pt_vec = create_vector(char*);
            vector_t* pt_vecex = create_vector(char*);
            if(pt_vec == NULL || pt_vecex == NULL)
            {
                return;
            }
            vector_init_elem(pt_vecex, 5, "Hello World!");
            vector_init_copy(pt_vec, pt_vecex);
            _print_vec_str(pt_vecex);
            vector_destroy(pt_vec);
            vector_destroy(pt_vecex);
        }
        /* vector_init_copy_range() */
        {
            vector_t* pt_vec = create_vector(char*);
            vector_t* pt_vecex = create_vector(char*);
            if(pt_vec == NULL || pt_vecex == NULL)
            {
                return;
            }
            vector_init_elem(pt_vecex, 8, "Hello libcstl!");
            vector_init_copy_range(pt_vec,
                iterator_next_n(vector_begin(pt_vecex), 3), vector_end(pt_vecex));
            _print_vec_str(pt_vec);
            vector_destroy(pt_vec);
            vector_destroy(pt_vecex);
        }
        /* vector_size() */
        /* vector_capacity() */
        /* vector_max_size() */
        /* vector_empty() */
        /* vector_reserve() */
        {
            vector_t* pt_vec = create_vector(char*);
            if(pt_vec == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            _print_vec_str(pt_vec);
            vector_reserve(pt_vec, 0);
            _print_vec_str(pt_vec);
            vector_reserve(pt_vec, 10);
            _print_vec_str(pt_vec);
            vector_reserve(pt_vec, 15);
            _print_vec_str(pt_vec);
            vector_reserve(pt_vec, 4);
            _print_vec_str(pt_vec);
            vector_reserve(pt_vec, 0);
            _print_vec_str(pt_vec);
            vector_destroy(pt_vec);
        }
        /* vector_assign() */
        {
            vector_t* pt_vec = create_vector(char*);
            vector_t* pt_vecex = create_vector(char*);
            if(pt_vec == NULL || pt_vecex == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            vector_init(pt_vecex);
            vector_assign(pt_vec, pt_vecex);
            _print_vec_str(pt_vec);
            vector_push_back(pt_vecex, "Hello World!");
            vector_push_back(pt_vecex, "Hello libcstl!");
            vector_assign(pt_vec, pt_vecex);
            _print_vec_str(pt_vec);
            vector_clear(pt_vecex);
            vector_push_back(pt_vecex, "abcdefghijklmnopqrstuvwxyz");
            vector_push_back(pt_vecex, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
            vector_push_back(pt_vecex, "1234567890");
            vector_assign(pt_vec, pt_vecex);
            _print_vec_str(pt_vec);
            vector_clear(pt_vecex);
            vector_push_back(pt_vecex, "!@@%#@$&$**(()_+||_)(*&^%$");
            vector_assign(pt_vec, pt_vecex);
            _print_vec_str(pt_vec);
            vector_clear(pt_vecex);
            vector_assign(pt_vec, pt_vecex);
            _print_vec_str(pt_vec);
            vector_destroy(pt_vec);
            vector_destroy(pt_vecex);
        }
        /* vector_assign_elem() */
        {
            vector_t* pt_vec = create_vector(char*);
            if(pt_vec == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            _print_vec_str(pt_vec);
            vector_assign_elem(pt_vec, 0, "China");
            _print_vec_str(pt_vec);
            vector_assign_elem(pt_vec, 8, "ChinaUnix");
            _print_vec_str(pt_vec);
            vector_assign_elem(pt_vec, 21, "CSDN");
            _print_vec_str(pt_vec);
            vector_assign_elem(pt_vec, 5, "");
            _print_vec_str(pt_vec);
            vector_assign_elem(pt_vec, 0, "Google");
            _print_vec_str(pt_vec);
            vector_destroy(pt_vec);
        }
        /* vector_assign_range() */
        {
            vector_t* pt_vec = create_vector(char*);
            vector_t* pt_vecex = create_vector(char*);
            if(pt_vec == NULL || pt_vecex == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            vector_init(pt_vecex);
            vector_assign_range(pt_vec, vector_begin(pt_vecex), vector_end(pt_vecex));
            _print_vec_str(pt_vec);
            vector_push_back(pt_vecex, "ChinaUnix");
            vector_push_back(pt_vecex, "CSDN");
            vector_push_back(pt_vecex, "China-Pub");
            vector_push_back(pt_vecex, "Google");
            vector_push_back(pt_vecex, "sina");
            vector_push_back(pt_vecex, "163");
            vector_push_back(pt_vecex, "mop");
            vector_push_back(pt_vecex, "openv");
            vector_assign_range(pt_vec, vector_begin(pt_vecex), vector_begin(pt_vecex));
            _print_vec_str(pt_vec);
            vector_assign_range(pt_vec,
                vector_begin(pt_vecex), iterator_next_n(vector_begin(pt_vecex), 3));
            _print_vec_str(pt_vec);
            vector_assign_range(pt_vec,
                iterator_next_n(vector_begin(pt_vecex), 2), iterator_next_n(vector_begin(pt_vecex), 5));
            _print_vec_str(pt_vec);
            vector_assign_range(pt_vec, iterator_prev(vector_end(pt_vecex)), vector_end(pt_vecex));
            _print_vec_str(pt_vec);
            vector_assign_range(pt_vec, vector_end(pt_vecex), vector_end(pt_vecex));
            _print_vec_str(pt_vec);
            vector_assign_range(pt_vec, vector_begin(pt_vecex), vector_end(pt_vecex));
            _print_vec_str(pt_vec);
            vector_destroy(pt_vec);
            vector_destroy(pt_vecex);
        }
        /* vector_equal() */
        {
            vector_t* pt_vec = create_vector(char*);
            vector_t* pt_vecex = create_vector(char*);
            if(pt_vec == NULL || pt_vecex == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            vector_init(pt_vecex);
            _print_vec_str(pt_vec);
            _print_vec_str(pt_vecex);
            printf("equal: %d, not equal: %d, ",
                vector_equal(pt_vec, pt_vecex), vector_not_equal(pt_vec, pt_vecex));
            printf("less: %d, less equal: %d, ",
                vector_less(pt_vec, pt_vecex), vector_less_equal(pt_vec, pt_vecex));
            printf("greater: %d, greater equal: %d\n",
                vector_greater(pt_vec, pt_vecex), vector_greater_equal(pt_vec, pt_vecex));
            vector_push_back(pt_vec, "China");
            _print_vec_str(pt_vec);
            _print_vec_str(pt_vecex);
            printf("equal: %d, not equal: %d, ",
                vector_equal(pt_vec, pt_vecex), vector_not_equal(pt_vec, pt_vecex));
            printf("less: %d, less equal: %d, ",
                vector_less(pt_vec, pt_vecex), vector_less_equal(pt_vec, pt_vecex));
            printf("greater: %d, greater equal: %d\n",
                vector_greater(pt_vec, pt_vecex), vector_greater_equal(pt_vec, pt_vecex));
            vector_push_back(pt_vecex, "China");
            _print_vec_str(pt_vec);
            _print_vec_str(pt_vecex);
            printf("equal: %d, not equal: %d, ",
                vector_equal(pt_vec, pt_vecex), vector_not_equal(pt_vec, pt_vecex));
            printf("less: %d, less equal: %d, ",
                vector_less(pt_vec, pt_vecex), vector_less_equal(pt_vec, pt_vecex));
            printf("greater: %d, greater equal: %d\n",
                vector_greater(pt_vec, pt_vecex), vector_greater_equal(pt_vec, pt_vecex));
            vector_push_back(pt_vecex, "UNIX");
            _print_vec_str(pt_vec);
            _print_vec_str(pt_vecex);
            printf("equal: %d, not equal: %d, ",
                vector_equal(pt_vec, pt_vecex), vector_not_equal(pt_vec, pt_vecex));
            printf("less: %d, less equal: %d, ",
                vector_less(pt_vec, pt_vecex), vector_less_equal(pt_vec, pt_vecex));
            printf("greater: %d, greater equal: %d\n",
                vector_greater(pt_vec, pt_vecex), vector_greater_equal(pt_vec, pt_vecex));
            vector_push_back(pt_vec, "CSDN");
            vector_push_back(pt_vec, "sina");
            _print_vec_str(pt_vec);
            _print_vec_str(pt_vecex);
            printf("equal: %d, not equal: %d, ",
                vector_equal(pt_vec, pt_vecex), vector_not_equal(pt_vec, pt_vecex));
            printf("less: %d, less equal: %d, ",
                vector_less(pt_vec, pt_vecex), vector_less_equal(pt_vec, pt_vecex));
            printf("greater: %d, greater equal: %d\n",
                vector_greater(pt_vec, pt_vecex), vector_greater_equal(pt_vec, pt_vecex));
            vector_destroy(pt_vec);
            vector_destroy(pt_vecex);
        }
        /* vector_not_equal() */
        /* vector_less() */
        /* vector_less_equal() */
        /* vector_greater() */
        /* vector_greater_equal() */
        /* vector_swap() */
        {
            vector_t* pt_vec = create_vector(char*);
            vector_t* pt_vecex = create_vector(char*);
            if(pt_vec == NULL || pt_vecex == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            vector_init(pt_vecex);
            vector_swap(pt_vec, pt_vecex);
            _print_vec_str(pt_vec);
            _print_vec_str(pt_vecex);
            vector_assign_elem(pt_vecex, 3, "libcstl");
            vector_swap(pt_vec, pt_vecex);
            _print_vec_str(pt_vec);
            _print_vec_str(pt_vecex);
            vector_assign_elem(pt_vecex, 9, "Hello World!");
            vector_swap(pt_vec, pt_vecex);
            _print_vec_str(pt_vec);
            _print_vec_str(pt_vecex);
            vector_clear(pt_vecex);
            vector_swap(pt_vec, pt_vecex);
            _print_vec_str(pt_vec);
            _print_vec_str(pt_vecex);
            vector_clear(pt_vecex);
            vector_swap(pt_vec, pt_vecex);
            _print_vec_str(pt_vec);
            _print_vec_str(pt_vecex);
            vector_destroy(pt_vec);
            vector_destroy(pt_vecex);
        }
        /* vector_at() */
        {
            vector_t* pt_vec = create_vector(char*);
            size_t i;
            if(pt_vec == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            vector_push_back(pt_vec, "I. Errors and Overflow");
            vector_push_back(pt_vec,
                "    In line with the discussion in NWG/RFC #48, we felt that two");
            vector_push_back(pt_vec,
                "types of errors should be distinguished.  One is a real error, such as");
            vector_push_back(pt_vec,
                "an RFC composed of two send sockets.  This type of error can only be");
            vector_push_back(pt_vec,
                "generated by a broken NCP.  In the absence of hardware and software");
            vector_push_back(pt_vec,
                "bugs, these events should never occur; the correct response upon");
            vector_push_back(pt_vec,
                "detection of such an event was outlined in the description of the ERR");
            vector_push_back(pt_vec, "command in NWG/RFC #54.");

            for(i = 0; i < vector_size(pt_vec); ++i)
            {
                puts((char*)vector_at(pt_vec, i));
            }

            printf("front: %s\n", (char*)vector_front(pt_vec));
            printf("back: %s\n", (char*)vector_back(pt_vec));
            vector_destroy(pt_vec);
        }
        /* vector_front() */
        /* vector_back() */
        /* vector_begin() */
        /* vector_end() */
        /* vector_insert() */
        {
            vector_t* pt_vec = create_vector(char*);
            if(pt_vec == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            _print_vec_str(pt_vec);
            vector_insert(pt_vec, vector_begin(pt_vec),
                "The other \"error\" is an overflow condition arising because");
            _print_vec_str(pt_vec);
            vector_insert(pt_vec, vector_begin(pt_vec),
                "finite system resources are exhausted.  An overflow condition could");
            _print_vec_str(pt_vec);
            vector_insert(pt_vec, vector_end(pt_vec),
                "occur if an RFC was received, but there was no room to create the");
            _print_vec_str(pt_vec);
            vector_insert(pt_vec, iterator_next(vector_begin(pt_vec)),
                "requisite tables and queues.  This is not a real error, in the sense");
            _print_vec_str(pt_vec);
            vector_destroy(pt_vec);
        }
        /* vector_insert_n() */
        {
            vector_t* pt_vec = create_vector(char*);
            if(pt_vec == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            vector_insert_n(pt_vec, vector_begin(pt_vec), 0, "0.  UNSPECIFIED ERROR");
            _print_vec_str(pt_vec);
            vector_insert_n(pt_vec, vector_begin(pt_vec), 3,
                "1.  HOMOSEX  (invalid send/rcv pair in an RFC)");
            _print_vec_str(pt_vec);
            vector_insert_n(pt_vec, vector_begin(pt_vec), 7, "2.  ILLEGAL OP CODE");
            _print_vec_str(pt_vec);
            vector_insert_n(pt_vec, vector_end(pt_vec), 4,
                "3.  ILLEGAL LEADER (bad message type, etc.)");
            _print_vec_str(pt_vec);
            vector_insert_n(pt_vec, iterator_prev_n(vector_end(pt_vec), 3), 2,
                "6.  ILLEGAL COMMAND LENGTH (last command in message was too short)");
            _print_vec_str(pt_vec);
            vector_insert_n(pt_vec, iterator_next_n(vector_begin(pt_vec), 4), 0,
                "8.  DATA OVERFLOW (message longer than advertised available");
            _print_vec_str(pt_vec);
            vector_destroy(pt_vec);
        }
        /* vector_insert_range() */
        {
            vector_t* pt_vec = create_vector(char*);
            vector_t* pt_vecex = create_vector(char*);
            if(pt_vec == NULL || pt_vecex == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            vector_init(pt_vecex);
            vector_insert_range(pt_vec, vector_begin(pt_vec),
                vector_begin(pt_vecex), vector_end(pt_vecex));
            _print_vec_str(pt_vec);
            vector_push_back(pt_vecex,
                "       In light of the other considerations mentioned earlier, we");
            vector_push_back(pt_vecex,
                "would also like to propose an additional control command to singify");
            vector_push_back(pt_vecex,
                "overflow:");
            vector_push_back(pt_vecex,
                "        +-------------+-------------------+---------------------+");
            vector_push_back(pt_vecex,
                "        |     OVF     |     my socket     |     your socket     |");
            vector_push_back(pt_vecex,
                "        +-------------+-------------------+---------------------+");
            vector_push_back(pt_vecex,
                "The format of the message is similar to that of the CLS message, which");
            vector_push_back(pt_vecex,
                "it replaces in this context.  The socket numbers are 32 bits long and");
            vector_insert_range(pt_vec, vector_begin(pt_vec),
                vector_begin(pt_vecex), vector_begin(pt_vecex));
            _print_vec_str(pt_vec);
            vector_insert_range(pt_vec, vector_begin(pt_vec),
                vector_begin(pt_vecex), iterator_next_n(vector_begin(pt_vecex), 3));
            _print_vec_str(pt_vec);
            vector_insert_range(pt_vec, vector_begin(pt_vec),
                iterator_next_n(vector_begin(pt_vecex), 3),
                iterator_next_n(vector_begin(pt_vecex), 6));
            _print_vec_str(pt_vec);
            vector_insert_range(pt_vec, vector_end(pt_vec),
                iterator_prev_n(vector_end(pt_vecex), 2), vector_end(pt_vecex));
            _print_vec_str(pt_vec);
            vector_insert_range(pt_vec, iterator_prev(vector_end(pt_vec)),
                vector_end(pt_vecex), vector_end(pt_vecex));
            _print_vec_str(pt_vec);
            vector_insert_range(pt_vec, vector_end(pt_vec),
                vector_begin(pt_vecex), vector_end(pt_vecex));
            _print_vec_str(pt_vec);
            vector_destroy(pt_vec);
            vector_destroy(pt_vecex);
        }
        /* vector_push_back() */
        /* vector_pop_back() */
        {
            vector_t* pt_vec = create_vector(char*);
            if(pt_vec == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            vector_push_back(pt_vec,
                "       In light of the other considerations mentioned earlier, we");
            vector_push_back(pt_vec,
                "would also like to propose an additional control command to singify");
            vector_push_back(pt_vec,
                "overflow:");
            vector_push_back(pt_vec,
                "        +-------------+-------------------+---------------------+");
            vector_push_back(pt_vec,
                "        |     OVF     |     my socket     |     your socket     |");
            vector_push_back(pt_vec,
                "        +-------------+-------------------+---------------------+");
            vector_push_back(pt_vec,
                "The format of the message is similar to that of the CLS message, which");
            vector_push_back(pt_vec,
                "it replaces in this context.  The socket numbers are 32 bits long and");

            while(!vector_empty(pt_vec))
            {
                _print_vec_str(pt_vec);
                vector_pop_back(pt_vec);
            }
            vector_destroy(pt_vec);
        }
        /* vector_erase() */
        {
            vector_t* pt_vec = create_vector(char*);
            if(pt_vec == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            vector_push_back(pt_vec, "Abhay Bhushan, MIT-DMCG");
            vector_push_back(pt_vec, "Bob Braden, UCLA-CCN");
            vector_push_back(pt_vec, "Eric Harslem, RAND");
            vector_push_back(pt_vec, "John Heafner, RAND");
            vector_push_back(pt_vec, "Alex McKenzie, BBN-NET");
            vector_push_back(pt_vec, "John Melvin, SRI-ARC");
            vector_push_back(pt_vec, "Bob Sundberg, HARV");
            vector_push_back(pt_vec, "Dick Watson, SRI-ARC");
            vector_push_back(pt_vec, "Jim White, UCSB");
            _print_vec_str(pt_vec);
            vector_erase(pt_vec, vector_begin(pt_vec));
            _print_vec_str(pt_vec);
            vector_erase(pt_vec, iterator_prev(vector_end(pt_vec)));
            _print_vec_str(pt_vec);
            vector_erase(pt_vec, iterator_next_n(vector_begin(pt_vec), 3));
            _print_vec_str(pt_vec);
            while(!vector_empty(pt_vec))
            {
                vector_erase(pt_vec, vector_begin(pt_vec));
            }
            _print_vec_str(pt_vec);
            vector_destroy(pt_vec);
        }
        /* vector_erase_range() */
        {
            vector_t* pt_vec = create_vector(char*);
            if(pt_vec == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            vector_erase_range(pt_vec, vector_begin(pt_vec), vector_end(pt_vec));
            _print_vec_str(pt_vec);
            vector_push_back(pt_vec, "Abhay Bhushan, MIT-DMCG");
            vector_push_back(pt_vec, "Bob Braden, UCLA-CCN");
            vector_push_back(pt_vec, "Eric Harslem, RAND");
            vector_push_back(pt_vec, "John Heafner, RAND");
            vector_push_back(pt_vec, "Alex McKenzie, BBN-NET");
            vector_push_back(pt_vec, "John Melvin, SRI-ARC");
            vector_push_back(pt_vec, "Bob Sundberg, HARV");
            vector_push_back(pt_vec, "Dick Watson, SRI-ARC");
            vector_push_back(pt_vec, "Jim White, UCSB");
            _print_vec_str(pt_vec);
            vector_erase_range(pt_vec, vector_begin(pt_vec), vector_begin(pt_vec));
            _print_vec_str(pt_vec);
            vector_erase_range(pt_vec,
                vector_begin(pt_vec), iterator_next_n(vector_begin(pt_vec), 2));
            _print_vec_str(pt_vec);
            vector_erase_range(pt_vec,
                iterator_next(vector_begin(pt_vec)), iterator_next_n(vector_begin(pt_vec), 3));
            _print_vec_str(pt_vec);
            vector_erase_range(pt_vec,
                iterator_prev_n(vector_end(pt_vec), 2), vector_end(pt_vec));
            _print_vec_str(pt_vec);
            vector_erase_range(pt_vec, vector_end(pt_vec), vector_end(pt_vec));
            _print_vec_str(pt_vec);
            vector_erase_range(pt_vec, vector_begin(pt_vec), vector_end(pt_vec));
            _print_vec_str(pt_vec);
            vector_destroy(pt_vec);
        }
        /* vector_clear() */
        {
            vector_t* pt_vec = create_vector(char*);
            if(pt_vec == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            vector_clear(pt_vec);
            _print_vec_str(pt_vec);
            vector_push_back(pt_vec, "Abhay Bhushan, MIT-DMCG");
            vector_push_back(pt_vec, "Bob Braden, UCLA-CCN");
            vector_push_back(pt_vec, "Eric Harslem, RAND");
            vector_push_back(pt_vec, "John Heafner, RAND");
            vector_push_back(pt_vec, "Alex McKenzie, BBN-NET");
            vector_push_back(pt_vec, "John Melvin, SRI-ARC");
            vector_push_back(pt_vec, "Bob Sundberg, HARV");
            vector_push_back(pt_vec, "Dick Watson, SRI-ARC");
            vector_push_back(pt_vec, "Jim White, UCSB");
            _print_vec_str(pt_vec);
            vector_clear(pt_vec);
            _print_vec_str(pt_vec);
            vector_destroy(pt_vec);
        }
        /* vector_resize() */
        {
            vector_t* pt_vec = create_vector(char*);
            if(pt_vec == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            _print_vec_str(pt_vec);
            vector_resize(pt_vec, 3);
            _print_vec_str(pt_vec);
            vector_resize(pt_vec, 10);
            _print_vec_str(pt_vec);
            vector_resize(pt_vec, 6);
            _print_vec_str(pt_vec);
            vector_resize(pt_vec, 0);
            _print_vec_str(pt_vec);
            vector_destroy(pt_vec);
        }
        /* vector_resize_elem() */
        {
            vector_t* pt_vec = create_vector(char*);
            if(pt_vec == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            _print_vec_str(pt_vec);
            vector_resize_elem(pt_vec, 5, "\"MAIL\" <separator> (\"PRINTER\"/<ident>)");
            _print_vec_str(pt_vec);
            vector_resize_elem(pt_vec, 13, "<ident> is a NIC IDENT");
            _print_vec_str(pt_vec);
            vector_resize_elem(pt_vec, 7, "2) Append With Create the following file to a file");
            _print_vec_str(pt_vec);
            vector_resize_elem(pt_vec, 0, "");
            _print_vec_str(pt_vec);
            vector_destroy(pt_vec);
        }
    }
}

/** local function implementation section **/
static void _print_vec_str(const vector_t* pt_vec)
{
    size_t t_index = 0;

    assert(pt_vec != NULL);

    printf("======================================\n");
    printf("empty: %u, size: %u, capacity:%u, max_size: %u\n",
        vector_empty(pt_vec), vector_size(pt_vec),
        vector_capacity(pt_vec), vector_max_size(pt_vec));
    for(t_index = 0; t_index < vector_size(pt_vec); ++t_index)
    {
        printf("%s\n", (char*)vector_at(pt_vec, t_index));
    }
}

static void _abc_init(const void* cpv_input, void* pv_output)
{
    abc_t* pt_input = (abc_t*)cpv_input;

    assert(cpv_input != NULL && pv_output != NULL);

    pt_input->_n_first = 1024;
    pt_input->_d_second = 1024.1024;
    pt_input->_pc_third = (char*)malloc(sizeof(double));
    if(pt_input->_pc_third == NULL)
    {
        *(bool_t*)pv_output = false;
    }
    else
    {
        memset(pt_input->_pc_third, 0x44, sizeof(double));
        *(bool_t*)pv_output = true;
    }
}

static void _abc_copy(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    abc_t* pt_first = (abc_t*)cpv_first;
    abc_t* pt_second = (abc_t*)cpv_second;

    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    pt_first->_n_first = pt_second->_n_first;
    pt_first->_d_second = pt_second->_d_second;
    memcpy(pt_first->_pc_third, pt_second->_pc_third, sizeof(double));
    *(bool_t*)pv_output = true;
}

static void _abc_less(const void* cpv_first, const void* cpv_second, void * pv_output)
{
    abc_t* pt_first = (abc_t*)cpv_first;
    abc_t* pt_second = (abc_t*)cpv_second;

    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    if(pt_first->_n_first < pt_second->_n_first &&
       pt_first->_d_second - pt_second->_d_second < DBL_EPSILON &&
       memcmp(pt_first->_pc_third, pt_second->_pc_third, sizeof(double)) < 0)
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}

static void _abc_destroy(const void* cpv_input, void* pv_output)
{
    abc_t* pt_input = (abc_t*)cpv_input;

    assert(cpv_input != NULL && pv_output != NULL);

    pt_input->_n_first = 0;
    pt_input->_d_second = 0.0;
    memset(pt_input->_pc_third, 0xcc, sizeof(double));
    free(pt_input->_pc_third);
    *(bool_t*)pv_output = true;
}

/** eof **/

