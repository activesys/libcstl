/*
 *  The implementation of map_t and multimap_t test.
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
#include "cmap.h"
#include "cutility.h"
#include "calgorithm.h"
#include "test_map.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/
static void _find_value(const void* cpv_input, void* pv_output);

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
void test_map(void)
{
    {
        multimap_t t_mm = create_multimap(int, char);
        pair_t     t_p = create_pair(int, char);
        iterator_t t_i;

        multimap_init(&t_mm);
        pair_init(&t_p);

        pair_make(&t_p, 3, 'L');
        multimap_insert(&t_mm, &t_p);
        pair_make(&t_p, 6, 'M');
        multimap_insert(&t_mm, &t_p);
        pair_make(&t_p, 2, 'U');
        multimap_insert(&t_mm, &t_p);
        pair_make(&t_p, 3, 'T');
        multimap_insert(&t_mm, &t_p);
        pair_make(&t_p, 7, 'A');
        multimap_insert(&t_mm, &t_p);
        pair_make(&t_p, 7, 'P');
        multimap_insert(&t_mm, &t_p);
        pair_make(&t_p, 1, 'M');
        multimap_insert(&t_mm, &t_p);
        pair_make(&t_p, 5, 'I');
        multimap_insert(&t_mm, &t_p);

        for(t_i = multimap_begin(&t_mm);
            !iterator_equal(&t_i, multimap_end(&t_mm));
            iterator_next(&t_i))
        {
            printf("%c", *(char*)((pair_t*)iterator_get_pointer(&t_i))->second);
        }
        printf("\n");

        multimap_destroy(&t_mm);
        pair_destroy(&t_p);
    }
    {
        map_t t_m = create_map(char, double);
        iterator_t t_i;

        map_init(&t_m);
        *(double*)map_at(&t_m, 'V') = 4.509;
        *(double*)map_at(&t_m, 'P') = 3.1415926;
        *(double*)map_at(&t_m, 'a') = 4983.223;
        *(double*)map_at(&t_m, 'N') = 0.0;

        for(t_i = map_begin(&t_m);
            !iterator_equal(&t_i, map_end(&t_m));
            iterator_next(&t_i))
        {
            printf("key:%c, value:%f\n",
                *(char*)((pair_t*)iterator_get_pointer(&t_i))->first,
                *(double*)((pair_t*)iterator_get_pointer(&t_i))->second);
        }
        printf("\n");

        map_destroy(&t_m);
    }
    {
        map_t t_m = create_map(char, double);
        iterator_t t_i;

        map_init(&t_m);
        *(double*)map_at(&t_m, 'B') = 369.50;
        *(double*)map_at(&t_m, 'V') = 413.50;
        *(double*)map_at(&t_m, 'D') = 819.00;
        *(double*)map_at(&t_m, 'M') = 834.00;
        *(double*)map_at(&t_m, 'S') = 842.20;

        for(t_i = map_begin(&t_m);
            !iterator_equal(&t_i, map_end(&t_m));
            iterator_next(&t_i))
        {
            printf("key:%c, value:%f\n",
                *(char*)((pair_t*)iterator_get_pointer(&t_i))->first,
                *(double*)((pair_t*)iterator_get_pointer(&t_i))->second);
        }
        printf("\n");

        for(t_i = map_begin(&t_m);
            !iterator_equal(&t_i, map_end(&t_m));
            iterator_next(&t_i))
        {
            *(double*)((pair_t*)iterator_get_pointer(&t_i))->second *= 2;
        }

        for(t_i = map_begin(&t_m);
            !iterator_equal(&t_i, map_end(&t_m));
            iterator_next(&t_i))
        {
            printf("key:%c, value:%f\n",
                *(char*)((pair_t*)iterator_get_pointer(&t_i))->first,
                *(double*)((pair_t*)iterator_get_pointer(&t_i))->second);
        }
        printf("\n");

        *(double*)map_at(&t_m, 'v') = *(double*)map_at(&t_m, 'V');
        map_erase(&t_m, 'V');

        for(t_i = map_begin(&t_m);
            !iterator_equal(&t_i, map_end(&t_m));
            iterator_next(&t_i))
        {
            printf("key:%c, value:%f\n",
                *(char*)((pair_t*)iterator_get_pointer(&t_i))->first,
                *(double*)((pair_t*)iterator_get_pointer(&t_i))->second);
        }
        printf("\n");

        map_destroy(&t_m);
    }
    {
        multimap_t t_mm = create_multimap(int, double);
        pair_t t_p = create_pair(int, double);
        iterator_t t_i;

        multimap_init(&t_mm);
        pair_init(&t_p);

        pair_make(&t_p, 0, 34.112);
        multimap_insert(&t_mm, &t_p);
        pair_make(&t_p, 0, 4.080);
        multimap_insert(&t_mm, &t_p);
        pair_make(&t_p, 2, 29.752);
        multimap_insert(&t_mm, &t_p);
        pair_make(&t_p, 4, 394.288);
        multimap_insert(&t_mm, &t_p);
        pair_make(&t_p, 4, 13.496);
        multimap_insert(&t_mm, &t_p);
        pair_make(&t_p, 5, 0.332);
        multimap_insert(&t_mm, &t_p);
        pair_make(&t_p, 4, 0.076);
        multimap_insert(&t_mm, &t_p);
        pair_make(&t_p, -3, 4.096);
        multimap_insert(&t_mm, &t_p);

        printf("priority    memory(m)\n");
        printf("------------------------\n");
        for(t_i = multimap_begin(&t_mm);
            !iterator_equal(&t_i, multimap_end(&t_mm));
            iterator_next(&t_i))
        {
            printf("%8d    %f\n",
                *(int*)((pair_t*)iterator_get_pointer(&t_i))->first,
                *(double*)((pair_t*)iterator_get_pointer(&t_i))->second);
        }
        printf("\n");

        printf("priority: 0\n");
        for(t_i = multimap_lower_bound(&t_mm, 0);
            !iterator_equal(&t_i, multimap_upper_bound(&t_mm, 0));
            iterator_next(&t_i))
        {
            printf("        %f\n",
                *(double*)((pair_t*)iterator_get_pointer(&t_i))->second);
        }
        printf("priority: 4\n");
        for(t_i = multimap_lower_bound(&t_mm, 4);
            !iterator_equal(&t_i, multimap_upper_bound(&t_mm, 4));
            iterator_next(&t_i))
        {
            printf("        %f\n",
                *(double*)((pair_t*)iterator_get_pointer(&t_i))->second);
        }
        printf("\n");

        multimap_destroy(&t_mm);
        pair_destroy(&t_p);
    }
    {
        map_t t_m = create_map(int, int);
        iterator_t t_i;

        map_init(&t_m);
        *(int*)map_at(&t_m, 1) = 7;
        *(int*)map_at(&t_m, 2) = 4;
        *(int*)map_at(&t_m, 3) = 2;
        *(int*)map_at(&t_m, 4) = 3;
        *(int*)map_at(&t_m, 5) = 6;
        *(int*)map_at(&t_m, 6) = 1;
        *(int*)map_at(&t_m, 7) = 3;

        t_i = map_find(&t_m, 3);
        if(!iterator_equal(&t_i, map_end(&t_m)))
        {
            printf("%d : %d\n",
                *(int*)((pair_t*)iterator_get_pointer(&t_i))->first,
                *(int*)((pair_t*)iterator_get_pointer(&t_i))->second);
        }

        t_i = algo_find_if(map_begin(&t_m), map_end(&t_m), _find_value);
        if(!iterator_equal(&t_i, map_end(&t_m)))
        {
            printf("%d : %d\n",
                *(int*)((pair_t*)iterator_get_pointer(&t_i))->first,
                *(int*)((pair_t*)iterator_get_pointer(&t_i))->second);
        }

        map_destroy(&t_m);
    }
}

/** local function implementation section **/
static void _find_value(const void* cpv_input, void* pv_output)
{
    if(*(int*)((pair_t*)cpv_input)->second == 3)
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}

/** eof **/

