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
#include "test_hashtable.h"
#include "cfunctional.h"
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
static void _hash_set_int_hash(const void* cpv_input, void* pv_output);

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
            _debug_hash_set_c(pt_hset, "%d", int);
            hash_set_destroy(pt_hset);
        }
        /*hash_set_init              */
        /*hash_set_init_ex           */
        {
            hash_set_t* pt_hset = create_hash_set(int);
            if(pt_hset == NULL)
            {
                return;
            }
            hash_set_init_ex(pt_hset, 0, _hash_set_int_hash, fun_great_int);
            _print_hash_set_c(pt_hset, "%d, ", int);
            hash_set_insert(pt_hset, 48);
            hash_set_insert(pt_hset, 1234);
            hash_set_insert(pt_hset, 483945);
            hash_set_insert(pt_hset, -74);
            hash_set_insert(pt_hset, 45);
            _print_hash_set_c(pt_hset, "%d, ", int);
            _debug_hash_set_c(pt_hset, "%d", int);
            hash_set_destroy(pt_hset);
        }
        /*hash_set_init_copy         */
        {
            hash_set_t* pt_hset = create_hash_set(double);
            hash_set_t* pt_hsetex = create_hash_set(double);
            if(pt_hset == NULL || pt_hsetex == NULL)
            {
                return;
            }
            hash_set_init_ex(pt_hsetex, 80, NULL, NULL);
            hash_set_insert(pt_hsetex, 45.90);
            hash_set_insert(pt_hsetex, 2.08);
            hash_set_insert(pt_hsetex, -22.34);
            hash_set_init_copy(pt_hset, pt_hsetex);
            _debug_hash_set_c(pt_hset, "%lf", double);
            hash_set_destroy(pt_hset);
            hash_set_destroy(pt_hsetex);
        }
        /*hash_set_init_copy_range   */
        {
            hash_set_t* pt_hset = create_hash_set(int);
            hash_set_t* pt_hsetex = create_hash_set(signed int);
            if(pt_hset == NULL || pt_hsetex == NULL)
            {
                return;
            }
            hash_set_init_ex(pt_hsetex, 110, _hash_set_int_hash, NULL);
            hash_set_insert(pt_hsetex, 290);
            hash_set_insert(pt_hsetex, -82784);
            hash_set_insert(pt_hsetex, 2220);
            hash_set_insert(pt_hsetex, 45);
            hash_set_insert(pt_hsetex, 100);
            hash_set_insert(pt_hsetex, 29000);
            hash_set_insert(pt_hsetex, 23);
            hash_set_init_copy_range(pt_hset, hash_set_begin(pt_hsetex),
                hash_set_end(pt_hsetex));
            _debug_hash_set_c(pt_hsetex, "%d", int);
            _debug_hash_set_c(pt_hset, "%d", int);
            _print_hash_set_c(pt_hsetex, "%d, ", int);
            _print_hash_set_c(pt_hset, "%d, ", int);
            hash_set_destroy(pt_hset);
            hash_set_destroy(pt_hsetex);
        }
        /*hash_set_init_copy_range_ex*/
        {
            hash_set_t* pt_hset = create_hash_set(int);
            hash_set_t* pt_hsetex = create_hash_set(signed int);
            if(pt_hset == NULL || pt_hsetex == NULL)
            {
                return;
            }
            hash_set_init_ex(pt_hsetex, 110, _hash_set_int_hash, NULL);
            hash_set_insert(pt_hsetex, 290);
            hash_set_insert(pt_hsetex, -82784);
            hash_set_insert(pt_hsetex, 2220);
            hash_set_insert(pt_hsetex, 45);
            hash_set_insert(pt_hsetex, 100);
            hash_set_insert(pt_hsetex, 29000);
            hash_set_insert(pt_hsetex, 23);
            hash_set_insert(pt_hsetex, 23);
            hash_set_insert(pt_hsetex, 92);
            hash_set_insert(pt_hsetex, 94);
            hash_set_insert(pt_hsetex, 95);
            hash_set_insert(pt_hsetex, 96);
            hash_set_insert(pt_hsetex, 97);
            hash_set_insert(pt_hsetex, 98);
            hash_set_insert(pt_hsetex, 99);
            hash_set_insert(pt_hsetex, 101);
            hash_set_init_copy_range_ex(pt_hset, hash_set_begin(pt_hsetex),
                hash_set_end(pt_hsetex), 90, NULL, fun_great_int);
            _debug_hash_set_c(pt_hsetex, "%d", int);
            _debug_hash_set_c(pt_hset, "%d", int);
            _print_hash_set_c(pt_hsetex, "%d, ", int);
            _print_hash_set_c(pt_hset, "%d, ", int);
            hash_set_destroy(pt_hset);
            hash_set_destroy(pt_hsetex);
        }
        /*hash_set_destroy           */
        /*hash_set_assign            */
        {
            hash_set_t* pt_hset = create_hash_set(int);
            hash_set_t* pt_hsetex = create_hash_set(int);
            size_t t_index = 0;
            if(pt_hset == NULL || pt_hsetex == NULL)
            {
                return;
            }
            hash_set_init(pt_hset);
            hash_set_init(pt_hsetex);
            hash_set_assign(pt_hset, pt_hsetex);
            _print_hash_set_c(pt_hsetex, "%d, ", int);
            _print_hash_set_c(pt_hset, "%d, ", int);

            hash_set_insert(pt_hsetex, 340);
            hash_set_insert(pt_hsetex, 1009);
            hash_set_insert(pt_hsetex, -76);
            hash_set_insert(pt_hsetex, 50);
            hash_set_insert(pt_hsetex, 21);
            hash_set_insert(pt_hsetex, -785);
            hash_set_assign(pt_hset, pt_hsetex);
            _print_hash_set_c(pt_hsetex, "%d, ", int);
            _print_hash_set_c(pt_hset, "%d, ", int);

            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 88);
            hash_set_insert(pt_hsetex, 245);
            hash_set_insert(pt_hsetex, 120);
            hash_set_assign(pt_hset, pt_hsetex);
            _print_hash_set_c(pt_hsetex, "%d, ", int);
            _print_hash_set_c(pt_hset, "%d, ", int);

            hash_set_clear(pt_hsetex);
            for(t_index = 0; t_index < 100; ++t_index)
            {
                hash_set_insert(pt_hsetex, t_index);
            }
            hash_set_assign(pt_hset, pt_hsetex);
            _print_hash_set_c(pt_hsetex, "%d, ", int);
            _print_hash_set_c(pt_hset, "%d, ", int);

            hash_set_clear(pt_hsetex);
            hash_set_assign(pt_hset, pt_hsetex);
            _print_hash_set_c(pt_hsetex, "%d, ", int);
            _print_hash_set_c(pt_hset, "%d, ", int);

            hash_set_destroy(pt_hset);
            hash_set_destroy(pt_hsetex);
        }
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
static void _hash_set_int_hash(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    *(int*)pv_output = *(int*)cpv_input;
}

/** eof **/

