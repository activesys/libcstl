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
#include "cvector.h"
#include "test_vector.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

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
            assert(true);
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
            assert(true);
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
            assert(true);
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
            assert(true);
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
            vector_init_copy_range(pv_int, vector_begin(pv_src), iterator_next(vector_begin(pv_src)));
            vector_destroy(pv_src);
            vector_destroy(pv_int);
            assert(true);
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
    /* user defined type */
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

/** eof **/

