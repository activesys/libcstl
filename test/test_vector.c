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
        /* vector_great() */
        {
            vector_t* pv_int = create_vector(int);
            vector_t* pv_signed = create_vector(signed);
            if(pv_int == NULL || pv_signed == NULL)
            {
                return;
            }

            vector_init_elem(pv_int, 2, 200);
            vector_init_elem(pv_signed, 2, 200);
            printf("great: %d\n", vector_great(pv_int, pv_signed));
            vector_destroy(pv_int);
            vector_destroy(pv_signed);
        }
        /* vector_great_equal() */
        {
            vector_t* pv_int = create_vector(int);
            vector_t* pv_signed = create_vector(signed);
            if(pv_int == NULL || pv_signed == NULL)
            {
                return;
            }

            vector_init_elem(pv_int, 2, 200);
            vector_init_elem(pv_signed, 2, 200);
            printf("great equal: %d\n", vector_great_equal(pv_int, pv_signed));
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
            type_debug();
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
        /* vector_great() */
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
            printf("%d\n", vector_great(pt_abc, pt_abcex));
            vector_destroy(pt_abc);
            vector_destroy(pt_abcex);
            free(t_abc._pc_third);
        }
        /* vector_great_equal() */
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
            printf("%d\n", vector_great_equal(pt_abc, pt_abcex));
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
        }
        /* vector_init_n() */
        {
        }
        /* vector_init_elem() */
        {
        }
        /* vector_init_copy() */
        {
        }
        /* vector_init_copy_range() */
        {
        }
        /* vector_size() */
        {
        }
        /* vector_capacity() */
        {
        }
        /* vector_max_size() */
        {
        }
        /* vector_empty() */
        {
        }
        /* vector_reserve() */
        {
        }
        /* vector_assign() */
        {
        }
        /* vector_assign_elem() */
        {
        }
        /* vector_assign_range() */
        {
        }
        /* vector_equal() */
        {
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
        /* vector_great() */
        {
        }
        /* vector_great_equal() */
        {
        }
        /* vector_swap() */
        {
        }
        /* vector_at() */
        {
        }
        /* vector_front() */
        {
        }
        /* vector_back() */
        {
        }
        /* vector_begin() */
        {
        }
        /* vector_end() */
        {
        }
        /* vector_insert() */
        {
        }
        /* vector_insert_n() */
        {
        }
        /* vector_insert_range() */
        {
        }
        /* vector_push_back() */
        {
        }
        /* vector_pop_back() */
        {
        }
        /* vector_erase() */
        {
        }
        /* vector_erase_range() */
        {
        }
        /* vector_clear() */
        {
        }
        /* vector_resize() */
        {
        }
        /* vector_resize_elem() */
        {
        }
    }
    /* c-string type */
    {
        /* create_vector(), vector_init(), vector_destroy() */
        {
        }
        /* vector_init_n() */
        {
        }
        /* vector_init_elem() */
        {
        }
        /* vector_init_copy() */
        {
        }
        /* vector_init_copy_range() */
        {
        }
        /* vector_size() */
        {
        }
        /* vector_capacity() */
        {
        }
        /* vector_max_size() */
        {
        }
        /* vector_empty() */
        {
        }
        /* vector_reserve() */
        {
        }
        /* vector_assign() */
        {
        }
        /* vector_assign_elem() */
        {
        }
        /* vector_assign_range() */
        {
        }
        /* vector_equal() */
        {
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
        /* vector_great() */
        {
        }
        /* vector_great_equal() */
        {
        }
        /* vector_swap() */
        {
        }
        /* vector_at() */
        {
        }
        /* vector_front() */
        {
        }
        /* vector_back() */
        {
        }
        /* vector_begin() */
        {
        }
        /* vector_end() */
        {
        }
        /* vector_insert() */
        {
        }
        /* vector_insert_n() */
        {
        }
        /* vector_insert_range() */
        {
        }
        /* vector_push_back() */
        {
        }
        /* vector_pop_back() */
        {
        }
        /* vector_erase() */
        {
        }
        /* vector_erase_range() */
        {
        }
        /* vector_clear() */
        {
        }
        /* vector_resize() */
        {
        }
        /* vector_resize_elem() */
        {
        }
    }
}

/** local function implementation section **/
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

