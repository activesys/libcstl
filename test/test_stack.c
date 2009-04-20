/*
 *  The implementation of stack test.
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

#include "cstack.h"
#include "test_stack.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
void test_stack(void)
{
    {
        stack_t t_sk = create_stack(int);

        stack_init(&t_sk);
        printf("stack1 - size:%u, empty:%d\n", stack_size(&t_sk), stack_empty(&t_sk));

        stack_push(&t_sk, 100);
        printf("top:%d\n", *(int*)stack_top(&t_sk));
        *(int*)stack_top(&t_sk) = 3333;
        printf("top:%d\n", *(int*)stack_top(&t_sk));

        stack_destroy(&t_sk);
    }
    {
        stack_t t_st = create_stack(int);

        stack_init(&t_st);
        stack_push(&t_st, 1);
        stack_push(&t_st, 2);
        stack_push(&t_st, 3);

        printf("%d ", *(int*)stack_top(&t_st));
        stack_pop(&t_st);
        printf("%d ", *(int*)stack_top(&t_st));
        stack_pop(&t_st);

        *(int*)stack_top(&t_st) = 77;
        stack_push(&t_st, 4);

        while(!stack_empty(&t_st))
        {
            printf("%d ", *(int*)stack_top(&t_st));
            stack_pop(&t_st);
        }
        printf("\n");

        stack_destroy(&t_st);
    }
}

/** local function implementation section **/

/** eof **/

