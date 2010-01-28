/*
 *  The implementation of hash_map_t and hash_multimap_t test.
 *  Copyright (C)  2008,2009,2010  Wangbo
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
#include "chash_map.h"
#include "test_hashtable.h"
#include "test_hash_map.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
void test_hash_map(void)
{
    /* c built-in type */
    {
        /*create_hash_map            */
        /*hash_map_init              */
        {
            hash_map_t* pt_hmap = create_hash_map(int, double);
            pair_t* pt_pair = create_pair(int, double);
            if(pt_hmap == NULL || pt_pair == NULL)
            {
                return;
            }
            hash_map_init(pt_hmap);
            pair_init(pt_pair);
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);
            pair_make(pt_pair, 45, 42304.23);
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, 1029, 22.2);
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, 0, 0.20);
            hash_map_insert(pt_hmap, pt_pair);
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);
            hash_map_destroy(pt_hmap);
            pair_destroy(pt_pair);
        }
        /*hash_map_init_ex           */
        {
            hash_map_t* pt_hmap = create_hash_map(int, double);
            pair_t* pt_pair = create_pair(int, double);
            if(pt_hmap == NULL || pt_pair == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 100, _hash_map_int_key_hash, NULL);
            pair_init(pt_pair);
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);
            pair_make(pt_pair, 45, 42304.23);
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, 1029, 22.2);
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, 0, 0.20);
            hash_map_insert(pt_hmap, pt_pair);
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);
            hash_map_destroy(pt_hmap);
            pair_destroy(pt_pair);
        }
        /*hash_map_init_copy         */
        {
            hash_map_t* pt_hmap = create_hash_map(short, int);
            hash_map_t* pt_hmapex = create_hash_map(short, int);
            pair_t* pt_pair = create_pair(short, int);
            if(pt_hmap == NULL || pt_hmapex == NULL || pt_pair == NULL)
            {
                return;
            }
            hash_map_init(pt_hmapex);
            pair_init(pt_pair);

            pair_make(pt_pair, 45, 1023);
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, 0, 234);
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, -9, -3235);
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, 23, 23);
            hash_map_insert(pt_hmapex, pt_pair);

            hash_map_init_copy(pt_hmap, pt_hmapex);
            _print_hash_map_c(pt_hmapex, "<%hd, %d>, ", short, int);
            _print_hash_map_c(pt_hmap, "<%hd, %d>, ", short, int);

            hash_map_destroy(pt_hmap);
            hash_map_destroy(pt_hmapex);
            pair_destroy(pt_pair);
        }
        /*hash_map_init_copy_range   */
        {
            hash_map_t* pt_hmap = create_hash_map(int, double);
            hash_map_t* pt_hmapex = create_hash_map(int, double);
            pair_t* pt_pair = create_pair(int, double);
            if(pt_hmap == NULL || pt_hmapex == NULL || pt_pair == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            hash_map_init_ex(pt_hmapex, 100, _hash_map_int_key_hash, NULL);

            pair_make(pt_pair, 23, 434.239);
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, 2, 1.0);
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, 445, 34.23);
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, 6, 2.9);
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, 4, 213);
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, 0, 42.2);
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, 2, 234.09);
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, 3, 20.123);
            hash_map_insert(pt_hmapex, pt_pair);

            hash_map_init_copy_range(pt_hmap, hash_map_begin(pt_hmapex),
                hash_map_end(pt_hmapex));
            _print_hash_map_c(pt_hmapex, "<%d, %lf>, ", int, double);
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);

            hash_map_destroy(pt_hmap);
            hash_map_destroy(pt_hmapex);
            pair_destroy(pt_pair);
        }
        /*hash_map_init_copy_range_ex*/
        {
            hash_map_t* pt_hmap = create_hash_map(int, double);
            hash_map_t* pt_hmapex = create_hash_map(int, double);
            pair_t* pt_pair = create_pair(int, double);
            if(pt_hmap == NULL || pt_hmapex == NULL || pt_pair == NULL)
            {
                return;
            }
            hash_map_init(pt_hmapex);
            pair_init(pt_pair);

            pair_make(pt_pair, 3, 43.23);
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, 12, 12.12);
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, 0, 2.0);
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, 9, 9.0);
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, 121, 23.2);
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, 1, 23.23);
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, 8, 2.23);
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, 3, 45.09);
            hash_map_insert(pt_hmapex, pt_pair);
            hash_map_init_copy_range_ex(pt_hmap, hash_map_begin(pt_hmapex),
                hash_map_end(pt_hmapex),
                100, _hash_map_int_key_hash, NULL);
            _print_hash_map_c(pt_hmapex, "<%d, %lf>, ", int, double);
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);

            hash_map_destroy(pt_hmap);
            hash_map_destroy(pt_hmapex);
            pair_destroy(pt_pair);
        }
        /*hash_map_destroy           */
        /*hash_map_assign            */
        /*hash_map_swap              */
        /*hash_map_size              */
        /*hash_map_empty             */
        /*hash_map_max_size          */
        /*hash_map_bucket_count      */
        /*hash_map_hash              */
        /*hash_map_key_less          */
        /*hash_map_resize            */
        /*hash_map_equal             */
        /*hash_map_not_equal         */
        /*hash_map_less              */
        /*hash_map_less_equal        */
        /*hash_map_great             */
        /*hash_map_great_equal       */
        /*hash_map_begin             */
        /*hash_map_end               */
        /*hash_map_find              */
        /*hash_map_count             */
        /*hash_map_equal_range       */
        /*hash_map_at                */
        /*hash_map_insert            */
        /*hash_map_insert_range      */
        /*hash_map_erase             */
        /*hash_map_erase_pos         */
        /*hash_map_erase_range       */
        /*hash_map_clear             */
    }
    /* user define type */
    {
    }
    /* cstl built-in type */
    {
    }
    /* c-string type */
    {
    }

    /*create_hash_map            */
    /*hash_map_init              */
    /*hash_map_init_ex           */
    /*hash_map_init_copy         */
    /*hash_map_init_copy_range   */
    /*hash_map_init_copy_range_ex*/
    /*hash_map_destroy           */
    /*hash_map_assign            */
    /*hash_map_swap              */
    /*hash_map_size              */
    /*hash_map_empty             */
    /*hash_map_max_size          */
    /*hash_map_bucket_count      */
    /*hash_map_hash              */
    /*hash_map_key_less          */
    /*hash_map_resize            */
    /*hash_map_equal             */
    /*hash_map_not_equal         */
    /*hash_map_less              */
    /*hash_map_less_equal        */
    /*hash_map_great             */
    /*hash_map_great_equal       */
    /*hash_map_begin             */
    /*hash_map_end               */
    /*hash_map_find              */
    /*hash_map_count             */
    /*hash_map_equal_range       */
    /*hash_map_at                */
    /*hash_map_insert            */
    /*hash_map_insert_range      */
    /*hash_map_erase             */
    /*hash_map_erase_pos         */
    /*hash_map_erase_range       */
    /*hash_map_clear             */
}

void test_hash_multimap(void)
{
}

/** local function implementation section **/

/** eof **/

