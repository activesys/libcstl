/*
 *  The implementation of set_t and multiset_t test.
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
#include "cset.h"
#include "cutility.h"
#include "test_set.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
void test_set(void)
{
    {
        set_t t_s = create_set(int);
        iterator_t t_i;
        int n_value = 0;

        set_init(&t_s);
        set_insert(&t_s, 3);
        set_insert(&t_s, 1);
        set_insert(&t_s, 5);
        set_insert(&t_s, 4);
        set_insert(&t_s, 1);
        set_insert(&t_s, 6);
        set_insert(&t_s, 2);

        for(t_i = set_begin(&t_s);
            !iterator_equal(&t_i, set_end(&t_s));
            iterator_next(&t_i))
        {
            iterator_get_value(&t_i, &n_value);
            printf("%d, ", n_value);
        }
        printf("\n");

        set_destroy(&t_s);
    }
    {
        set_t t_s = create_set(int);
        iterator_t t_i;
        pair_t t_range;

        set_init(&t_s);
        set_insert(&t_s, 1);
        set_insert(&t_s, 2);
        set_insert(&t_s, 4);
        set_insert(&t_s, 5);
        set_insert(&t_s, 6);

        t_i = set_lower_bound(&t_s, 3);
        printf("lower_bound(3): %d\n", *(int*)iterator_get_pointer(&t_i));
        t_i = set_upper_bound(&t_s, 3);
        printf("upper_bound(3): %d\n", *(int*)iterator_get_pointer(&t_i));
        t_range = set_equal_range(&t_s, 3);
        printf("equal_range(3): %d, %d\n\n",
            *(int*)iterator_get_pointer((iterator_t*)(t_range.first)),
            *(int*)iterator_get_pointer((iterator_t*)(t_range.second)));
        pair_destroy(&t_range);

        t_i = set_lower_bound(&t_s, 5);
        printf("lower_bound(5): %d\n", *(int*)iterator_get_pointer(&t_i));
        t_i = set_upper_bound(&t_s, 5);
        printf("upper_bound(5): %d\n", *(int*)iterator_get_pointer(&t_i));
        t_range = set_equal_range(&t_s, 5);
        printf("equal_range(5): %d, %d\n",
            *(int*)iterator_get_pointer((iterator_t*)(t_range.first)),
            *(int*)iterator_get_pointer((iterator_t*)(t_range.second)));
        pair_destroy(&t_range);

        set_destroy(&t_s);
    }
    {
        set_t t_s1 = create_set(int);
        set_t t_s2 = create_set(int);
        iterator_t t_i;

        set_init(&t_s1);

        set_insert(&t_s1, 4);
        set_insert(&t_s1, 3);
        set_insert(&t_s1, 5);
        set_insert(&t_s1, 1);
        set_insert(&t_s1, 6);
        set_insert(&t_s1, 2);
        set_insert(&t_s1, 5);
        for(t_i = set_begin(&t_s1);
            !iterator_equal(&t_i, set_end(&t_s1));
            iterator_next(&t_i))
        {
            printf("%d ", *(int*)iterator_get_pointer(&t_i));
        }
        printf("\n");

        t_i = set_insert(&t_s1, 4);
        if(iterator_equal(&t_i, set_end(&t_s1)))
        {
            printf("4 already exists!\n");
        }
        else
        {
            printf("4 inserted as element %u\n",
                iterator_distance(set_begin(&t_s1), t_i));
        }

        set_init_copy_range(&t_s2, set_begin(&t_s1), set_end(&t_s1));
        for(t_i = set_begin(&t_s2);
            !iterator_equal(&t_i, set_end(&t_s2));
            iterator_next(&t_i))
        {
            printf("%d ", *(int*)iterator_get_pointer(&t_i));
        }
        printf("\n");

        set_erase_range(&t_s2, set_begin(&t_s2), set_find(&t_s2, 3));
        printf("%u element(s) removed!\n", set_erase(&t_s2, 5));
        for(t_i = set_begin(&t_s2);
            !iterator_equal(&t_i, set_end(&t_s2));
            iterator_next(&t_i))
        {
            printf("%d ", *(int*)iterator_get_pointer(&t_i));
        }
        printf("\n");

        set_destroy(&t_s1);
        set_destroy(&t_s2);
    }
    {
        multiset_t t_s1 = create_multiset(int);
        multiset_t t_s2 = create_multiset(int);
        iterator_t t_i;

        multiset_init(&t_s1);

        multiset_insert(&t_s1, 4);
        multiset_insert(&t_s1, 3);
        multiset_insert(&t_s1, 5);
        multiset_insert(&t_s1, 1);
        multiset_insert(&t_s1, 6);
        multiset_insert(&t_s1, 2);
        multiset_insert(&t_s1, 5);
        for(t_i = multiset_begin(&t_s1);
            !iterator_equal(&t_i, multiset_end(&t_s1));
            iterator_next(&t_i))
        {
            printf("%d ", *(int*)iterator_get_pointer(&t_i));
        }
        printf("\n");

        t_i = multiset_insert(&t_s1, 4);
        if(iterator_equal(&t_i, multiset_end(&t_s1)))
        {
            printf("4 already exists!\n");
        }
        else
        {
            printf("4 inserted as element %u\n",
                iterator_distance(multiset_begin(&t_s1), t_i));
        }

        multiset_init_copy_range(&t_s2, multiset_begin(&t_s1), multiset_end(&t_s1));
        for(t_i = multiset_begin(&t_s2);
            !iterator_equal(&t_i, multiset_end(&t_s2));
            iterator_next(&t_i))
        {
            printf("%d ", *(int*)iterator_get_pointer(&t_i));
        }
        printf("\n");

        multiset_erase_range(&t_s2, multiset_begin(&t_s2), multiset_find(&t_s2, 3));
        printf("%u element(s) removed!\n", multiset_erase(&t_s2, 5));
        for(t_i = multiset_begin(&t_s2);
            !iterator_equal(&t_i, multiset_end(&t_s2));
            iterator_next(&t_i))
        {
            printf("%d ", *(int*)iterator_get_pointer(&t_i));
        }
        printf("\n");

        multiset_destroy(&t_s1);
        multiset_destroy(&t_s2);
    }
}

/** local function implementation section **/

/** eof **/

