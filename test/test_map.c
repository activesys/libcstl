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
 *  Author e-mail: activesys.wb@gmail.com
 *                 activesys@sina.com.cn
 */

/** include section **/
#include "cmap.h"
#include "cfunctional.h"
#include "test_map.h"

/** local constant declaration and local macro section **/
#define _print_map_c(pt_map, fmt, key_type, value_type)\
    do{\
        iterator_t t_iter;\
        printf("=======================================\n");\
        printf("empty: %u, size: %u, max_size: %u\n",\
            map_empty(pt_map), map_size(pt_map), map_max_size(pt_map));\
        for(t_iter = map_begin(pt_map);\
            !iterator_equal(t_iter, map_end(pt_map));\
            t_iter = iterator_next(t_iter))\
        {\
            printf(fmt,\
                *(key_type*)pair_first((pair_t*)iterator_get_pointer(t_iter)),\
                *(value_type*)pair_second((pair_t*)iterator_get_pointer(t_iter)));\
        }\
        printf("\n");\
    }while(false)

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
void test_map(void)
{
    /* c built-in types */
    {
        /*create_map            */
        {
            map_t* pt_map = create_map(int, double);
            pair_t* pt_pair = create_pair(int, double);
            if(pt_map == NULL || pt_pair == NULL)
            {
                return;
            }
            map_init(pt_map);
            pair_init(pt_pair);
            _print_map_c(pt_map, "<key: %d, value: %lf>, ", int, double);
            pair_make(pt_pair, 1223, 90.22);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, 42, 23094.222);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, -45, 23.00);
            map_insert(pt_map, pt_pair);
            _print_map_c(pt_map, "<key: %d, value: %lf>, ", int, double);
            map_destroy(pt_map);
            pair_destroy(pt_pair);
        }
        /*map_init              */
        /*map_init_ex           */
        {
            map_t* pt_map = create_map(int, double);
            pair_t* pt_pair = create_pair(int, double);
            if(pt_map == NULL || pt_pair == NULL)
            {
                return;
            }
            map_init_ex(pt_map, fun_great_int);
            pair_init(pt_pair);
            _print_map_c(pt_map, "<key: %d, value: %lf>, ", int, double);
            pair_make(pt_pair, 1223, 90.22);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, 42, 23094.222);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, -45, 23.00);
            map_insert(pt_map, pt_pair);
            _print_map_c(pt_map, "<key: %d, value: %lf>, ", int, double);
            map_destroy(pt_map);
            pair_destroy(pt_pair);
        }
        /*map_init_copy         */
        /*map_init_copy_range   */
        /*map_init_copy_range_ex*/
        /*map_destroy           */
        /*map_assign            */
        /*map_swap              */
        /*map_size              */
        /*map_empty             */
        /*map_max_size          */
        /*map_key_less          */
        /*map_value_less        */
        /*map_clear             */
        /*map_equal             */
        /*map_not_equal         */
        /*map_less              */
        /*map_less_equal        */
        /*map_great             */
        /*map_great_equal       */
        /*map_begin             */
        /*map_end               */
        /*map_find              */
        /*map_count             */
        /*map_lower_bound       */
        /*map_upper_bound       */
        /*map_equal_range       */
        /*map_at                */
        /*map_insert            */
        /*map_insert_hint       */
        /*map_insert_range      */
        /*map_erase             */
        /*map_erase_pos         */
        /*map_erase_range       */
    }
    /* user defined types */
    {
    }
    /* cstl built-in types */
    {
    }
    /* c-string types */
    {
    }
    /*create_map            */
    /*map_init              */
    /*map_init_ex           */
    /*map_init_copy         */
    /*map_init_copy_range   */
    /*map_init_copy_range_ex*/
    /*map_destroy           */
    /*map_assign            */
    /*map_swap              */
    /*map_size              */
    /*map_empty             */
    /*map_max_size          */
    /*map_key_less          */
    /*map_value_less        */
    /*map_clear             */
    /*map_equal             */
    /*map_not_equal         */
    /*map_less              */
    /*map_less_equal        */
    /*map_great             */
    /*map_great_equal       */
    /*map_begin             */
    /*map_end               */
    /*map_find              */
    /*map_count             */
    /*map_lower_bound       */
    /*map_upper_bound       */
    /*map_equal_range       */
    /*map_at                */
    /*map_insert            */
    /*map_insert_hint       */
    /*map_insert_range      */
    /*map_erase             */
    /*map_erase_pos         */
    /*map_erase_range       */
}

/** local function implementation section **/

/** eof **/

