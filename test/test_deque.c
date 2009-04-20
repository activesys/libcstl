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
 *  Author Email: activesys.wb@gmail.com
 *                activesys@sina.com.cn
 */

/** include section **/
#include <stdio.h>

#include "cdeque.h"
#include "calgorithm.h"
#include "test_deque.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/
static void _print_int(const void* cpv_input, void* pv_output);

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
void test_deque(void)
{
    {
        size_t i = 0;
        deque_t t_dq = create_deque(double);

        deque_init(&t_dq);
        for(i = 0; i < 6; ++i)
        {
            deque_push_front(&t_dq, (i + 1) * 1.1);
        }
        for(i = 0; i < deque_size(&t_dq); ++i)
        {
            printf("%f, ", *(double*)deque_at(&t_dq, i));
        }
        printf("\n");

        deque_destroy(&t_dq);
    }
    {
        deque_t t_dq = create_deque(int);
        size_t i = 0;

        deque_init(&t_dq);
        deque_assign_elem(&t_dq, 3, 300);
        deque_push_back(&t_dq, 500);
        deque_push_front(&t_dq, 100);

        algo_for_each(deque_begin(&t_dq), deque_end(&t_dq), _print_int);
        printf("\n");

        deque_pop_front(&t_dq);
        deque_pop_back(&t_dq);
        for(i = 1; i < deque_size(&t_dq); ++i)
        {
            *(int*)deque_at(&t_dq, i) += 50;
        }

        deque_resize_elem(&t_dq, 5, -300);

        algo_for_each(deque_begin(&t_dq), deque_end(&t_dq), _print_int);
        printf("\n");

        deque_destroy(&t_dq);
    }
}

/** local function implementation section **/
static void _print_int(const void* cpv_input, void* pv_output)
{
    pv_output = NULL;
    printf("%d ", *(int*)cpv_input);
}

/** eof **/

