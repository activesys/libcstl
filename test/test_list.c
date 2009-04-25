/*
 *  The implementation of list test.
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
#include "clist.h"
#include "calgorithm.h"
#include "test_list.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/
static void _print_int(const void* cpv_input, void* pv_output);
static void _print_list(const list_t* cpt_first, const list_t* cpt_second);

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
void test_list(void)
{
    {
        char c_char;
        list_t t_l = create_list(char);

        list_init(&t_l);
        for(c_char = 'a'; c_char <= 'z'; ++c_char)
        {
            list_push_back(&t_l, c_char);
        }
        while(!list_empty(&t_l))
        {
            printf("%c, ", *(char*)list_front(&t_l));
            list_pop_front(&t_l);
        }
        printf("\n");

        list_destroy(&t_l);
    }
    {
        char c_char;
        list_t t_l = create_list(char);
        iterator_t t_i;

        list_init(&t_l);
        for(c_char = 'a'; c_char <= 'z'; ++c_char)
        {
            list_push_back(&t_l, c_char);
        }

        for(t_i = list_begin(&t_l);
            !iterator_equal(&t_i, list_end(&t_l));
            iterator_next(&t_i))
        {
            printf("%c, ", *(char*)iterator_get_pointer(&t_i));
        }
        printf("\n");

        list_destroy(&t_l);
    }
    {
        list_t t_l1 = create_list(int);
        list_t t_l2 = create_list(int);
        int i = 0;

        list_init(&t_l1);
        list_init(&t_l2);
        for(i = 0; i < 6; ++i)
        {
            list_push_back(&t_l1, i);
            list_push_front(&t_l2, i);
        }
        _print_list(&t_l1, &t_l2);

        list_splice(
            &t_l2,
            algo_find(list_begin(&t_l2), list_end(&t_l2), 3),
            &t_l1);
        _print_list(&t_l1, &t_l2);

        list_splice_pos(&t_l2, list_end(&t_l2), &t_l2, list_begin(&t_l2));
        _print_list(&t_l1, &t_l2);

        list_sort(&t_l2);
        list_assign(&t_l1, &t_l2);
        list_unique(&t_l2);
        _print_list(&t_l1, &t_l2);

        list_merge(&t_l1, &t_l2);
        _print_list(&t_l1, &t_l2);

        list_destroy(&t_l1);
        list_destroy(&t_l2);
    }
    {
        list_t t_l = create_list(int);
        int i = 0;
        iterator_t t_i;

        list_init(&t_l);
        for(i = 1; i <=9; ++i)
        {
            list_push_back(&t_l, i);
        }

        t_i = list_begin(&t_l);
        printf("%d\n", *(int*)iterator_get_pointer(&t_i));

        iterator_advance(&t_i, 3);
        printf("%d\n", *(int*)iterator_get_pointer(&t_i));

        iterator_advance(&t_i, -1);
        printf("%d\n", *(int*)iterator_get_pointer(&t_i));

        list_destroy(&t_l);
    }
    {
        list_t t_l = create_list(int);
        iterator_t t_i;
        int i = 0;

        list_init(&t_l);
        for(i = -3; i <= 9; ++i)
        {
            list_push_back(&t_l, i);
        }

        t_i = algo_find(list_begin(&t_l), list_end(&t_l), 5);
        printf("distance between beginning and 5: %d\n",
            iterator_distance(list_begin(&t_l), t_i));

        list_destroy(&t_l);
    }
}

/** local function implementation section **/
static void _print_int(const void* cpv_input, void* pv_output)
{
    pv_output = NULL;
    printf("%d ", *(int*)cpv_input);
}

static void _print_list(const list_t* cpt_first, const list_t* cpt_second)
{
    printf("list1: ");
    algo_for_each(list_begin(cpt_first), list_end(cpt_first), _print_int);
    printf("\n");
    printf("list2: ");
    algo_for_each(list_begin(cpt_second), list_end(cpt_second), _print_int);
    printf("\n\n");
}

/** eof **/

