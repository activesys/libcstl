/*
 *  The implementation of deque test.
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
#include "cdeque.h"
#include "cvector.h"
#include "test_deque.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
void test_deque(void)
{
    /* c builtin type */
    {
        /* create_deque(), deque_init(), deque_destroy() */
        {
            deque_t* pt_deq = create_deque(vector_t<int>);
            vector_t* pt_vec = create_vector(int);
            if(pt_deq == NULL || pt_vec == NULL)
            {
                return;
            }
            vector_init_elem(pt_vec, 3, 999);
            deque_init_elem(pt_deq, 2, pt_vec);
            deque_push_back(pt_deq, pt_vec);
            deque_destroy(pt_deq);
            vector_destroy(pt_vec);
        }
        /* deque_init_n() */
        {
        }
        /* deque_init_elem() */
        {
        }
        /* deque_init_copy() */
        {
        }
        /* deque_init_copy_range() */
        {
        }
        /* deque_empty() */
        {
        }
        /* deque_size() */
        {
        }
        /* deque_max_size() */
        {
        }
        /* deque_equal() */
        {
        }
        /* deque_not_equal() */
        {
        }
        /* deque_less() */
        {
        }
        /* deque_less_equal() */
        {
        }
        /* deque_great() */
        {
        }
        /* deque_great_equal() */
        {
        }
        /* deque_assign() */
        {
        }
        /* deque_assign_elem() */
        {
        }
        /* deque_assign_range() */
        {
        }
        /* deque_swap() */
        {
        }
        /* deque_at() */
        {
        }
        /* deque_front() */
        {
        }
        /* deque_back() */
        {
        }
        /* deque_begin() */
        {
        }
        /* deque_end() */
        {
        }
        /* deque_insert() */
        {
        }
        /* deque_insert_n() */
        {
        }
        /* deque_insert_range() */
        {
        }
        /* deque_push_back() */
        {
        }
        /* deque_pop_back() */
        {
        }
        /* deque_push_front() */
        {
        }
        /* deque_pop_front() */
        {
        }
        /* deque_erase() */
        {
        }
        /* deque_erase_range() */
        {
        }
        /* deque_clear() */
        {
        }
        /* deque_resize() */
        {
        }
        /* deque_resize_elem() */
        {
        }
    }
    /* user defined type */
    /* cstl builtin type */
    /* c-string type */
}

/** local function implementation section **/

/** eof **/

