/*
 *  The implementation of hash_set_t and hash_multiset_t test.
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
#include "chash_set.h"
#include "test_hash_set.h"

/** local constant declaration and local macro section **/
#define _print_hash_set_c(pt_hset, fmt, type)\
    do{\
        iterator_t t_iter;\
        printf("=======================================\n");\
        printf("empty: %u, size: %u, max_size: %u, bucket count: %u\n",\
            hash_set_empty(pt_hset), hash_set_size(pt_hset),\
            hash_set_max_size(pt_hset), hash_set_bucket_count(pt_hset));\
        for(t_iter = hash_set_begin(pt_hset);\
            !iterator_equal(t_iter, hash_set_end(pt_hset));\
            t_iter = iterator_next(t_iter))\
        {\
            printf(fmt, *(type*)iterator_get_pointer(t_iter));\
        }\
        printf("\n");\
    }while(false)

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
void test_hash_set(void)
{
    /* c built-in type */
    {
        /*create_hash_set            */
        {
            hash_set_t* pt_hset = create_hash_set(int);
            if(pt_hset == NULL)
            {
                return;
            }
            hash_set_init(pt_hset);
            _print_hash_set_c(pt_hset, "%d, ", int);
            hash_set_insert(pt_hset, 48);
            hash_set_insert(pt_hset, 1234);
            hash_set_insert(pt_hset, 483945);
            hash_set_insert(pt_hset, -74);
            hash_set_insert(pt_hset, 45);
            _print_hash_set_c(pt_hset, "%d, ", int);
            hash_set_destroy(pt_hset);
        }
        /*hash_set_init              */
        /*hash_set_init_ex           */
        /*hash_set_init_copy         */
        /*hash_set_init_copy_range   */
        /*hash_set_init_copy_range_ex*/
        /*hash_set_destroy           */
        /*hash_set_assign            */
        /*hash_set_swap              */
        /*hash_set_size              */
        /*hash_set_empty             */
        /*hash_set_max_size          */
        /*hash_set_bucket_count      */
        /*hash_set_hash              */
        /*hash_set_key_less          */
        /*hash_set_resize            */
        /*hash_set_equal             */
        /*hash_set_not_equal         */
        /*hash_set_less              */
        /*hash_set_less_equal        */
        /*hash_set_great             */
        /*hash_set_great_equal       */
        /*hash_set_begin             */
        /*hash_set_end               */
        /*hash_set_find              */
        /*hash_set_count             */
        /*hash_set_equal_range       */
        /*hash_set_insert            */
        /*hash_set_insert_range      */
        /*hash_set_erase             */
        /*hash_set_erase_pos         */
        /*hash_set_erase_range       */
        /*hash_set_clear             */
    }
    /* user defined type */
    {
    }
    /* cstl type */
    {
    }
    /* c-string type */
    {
    }
    /*create_hash_set            */
    /*hash_set_init              */
    /*hash_set_init_ex           */
    /*hash_set_init_copy         */
    /*hash_set_init_copy_range   */
    /*hash_set_init_copy_range_ex*/
    /*hash_set_destroy           */
    /*hash_set_assign            */
    /*hash_set_swap              */
    /*hash_set_size              */
    /*hash_set_empty             */
    /*hash_set_max_size          */
    /*hash_set_bucket_count      */
    /*hash_set_hash              */
    /*hash_set_key_less          */
    /*hash_set_resize            */
    /*hash_set_equal             */
    /*hash_set_not_equal         */
    /*hash_set_less              */
    /*hash_set_less_equal        */
    /*hash_set_great             */
    /*hash_set_great_equal       */
    /*hash_set_begin             */
    /*hash_set_end               */
    /*hash_set_find              */
    /*hash_set_count             */
    /*hash_set_equal_range       */
    /*hash_set_insert            */
    /*hash_set_insert_range      */
    /*hash_set_erase             */
    /*hash_set_erase_pos         */
    /*hash_set_erase_range       */
    /*hash_set_clear             */
}

void test_hash_multiset(void)
{
}

/** local function implementation section **/

/** eof **/

