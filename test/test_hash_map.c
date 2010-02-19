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
#include "clist.h"
#include "chash_map.h"
#include "cfunctional.h"
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
        {
            hash_map_t* pt_hmap = create_hash_map(int, double);
            hash_map_t* pt_hmapex = create_hash_map(int, double);
            pair_t* pt_pair = create_pair(int, double);
            if(pt_hmap == NULL || pt_hmapex == NULL || pt_pair == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_int_key_hash, NULL);
            hash_map_init_ex(pt_hmapex, 0, _hash_map_int_key_hash, NULL);
            pair_init(pt_pair);

            hash_map_assign(pt_hmap, pt_hmapex);
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);

            pair_make(pt_pair, 23, 290.233);
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, -7, -7.7);
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, 0, 0.0);
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, 112122, 3.23);
            hash_map_insert(pt_hmapex, pt_pair);
            hash_map_assign(pt_hmap, pt_hmapex);
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);

            hash_map_clear(pt_hmapex);
            pair_make(pt_pair, 9, 434.345);
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, 23, 23.23);
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, 9, 232323.2323);
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, 1, 43.23);
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, 6, 6.6);
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, 5, 23.2323);
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, 4, 232.0);
            hash_map_insert(pt_hmapex, pt_pair);
            hash_map_assign(pt_hmap, pt_hmapex);
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);

            hash_map_clear(pt_hmapex);
            pair_make(pt_pair, 34, 23.23);
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, 6, 34.1);
            hash_map_insert(pt_hmapex, pt_pair);
            hash_map_assign(pt_hmap, pt_hmapex);
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);

            hash_map_clear(pt_hmapex);
            hash_map_assign(pt_hmap, pt_hmapex);
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);

            hash_map_destroy(pt_hmap);
            hash_map_destroy(pt_hmapex);
            pair_destroy(pt_pair);
        }
        /*hash_map_swap              */
        {
            hash_map_t* pt_hmap = create_hash_map(int, double);
            hash_map_t* pt_hmapex = create_hash_map(int, double);
            pair_t* pt_pair = create_pair(int, double);
            if(pt_hmap == NULL || pt_hmapex == NULL || pt_pair == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_int_key_hash, NULL);
            hash_map_init_ex(pt_hmapex, 0, _hash_map_int_key_hash, NULL);
            pair_init(pt_pair);

            hash_map_swap(pt_hmap, pt_hmapex);
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);
            _print_hash_map_c(pt_hmapex, "<%d, %lf>, ", int, double);

            pair_make(pt_pair, 23, 290.233);
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, -7, -7.7);
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, 0, 0.0);
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, 112122, 3.23);
            hash_map_insert(pt_hmapex, pt_pair);
            hash_map_swap(pt_hmap, pt_hmapex);
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);
            _print_hash_map_c(pt_hmapex, "<%d, %lf>, ", int, double);

            hash_map_clear(pt_hmapex);
            pair_make(pt_pair, 9, 434.345);
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, 23, 23.23);
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, 9, 232323.2323);
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, 1, 43.23);
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, 6, 6.6);
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, 5, 23.2323);
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, 4, 232.0);
            hash_map_insert(pt_hmapex, pt_pair);
            hash_map_swap(pt_hmap, pt_hmapex);
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);
            _print_hash_map_c(pt_hmapex, "<%d, %lf>, ", int, double);

            hash_map_clear(pt_hmapex);
            pair_make(pt_pair, 34, 23.23);
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, 6, 34.1);
            hash_map_insert(pt_hmapex, pt_pair);
            hash_map_swap(pt_hmap, pt_hmapex);
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);
            _print_hash_map_c(pt_hmapex, "<%d, %lf>, ", int, double);

            hash_map_clear(pt_hmapex);
            hash_map_swap(pt_hmap, pt_hmapex);
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);
            _print_hash_map_c(pt_hmapex, "<%d, %lf>, ", int, double);

            hash_map_destroy(pt_hmap);
            hash_map_destroy(pt_hmapex);
            pair_destroy(pt_pair);
        }
        /*hash_map_size              */
        /*hash_map_empty             */
        /*hash_map_max_size          */
        /*hash_map_bucket_count      */
        /*hash_map_hash              */
        /*hash_map_key_less          */
        {
            hash_map_t* pt_hmap = create_hash_map(int, double);
            if(pt_hmap == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 100, _hash_map_int_key_hash, fun_great_int);
            assert(hash_map_hash(pt_hmap) == _hash_map_int_key_hash &&
                hash_map_key_less(pt_hmap) == fun_great_int);
            hash_map_destroy(pt_hmap);
        }
        /*hash_map_resize            */
        {
            hash_map_t* pt_hmap = create_hash_map(int, double);
            if(pt_hmap == NULL)
            {
                return;
            }
            hash_map_init(pt_hmap);
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);
            hash_map_resize(pt_hmap, 50);
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);
            hash_map_resize(pt_hmap, 500);
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);
            hash_map_resize(pt_hmap, 5);
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);
            hash_map_resize(pt_hmap, 0);
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);
            hash_map_destroy(pt_hmap);
        }
        /*hash_map_equal             */
        /*hash_map_not_equal         */
        /*hash_map_less              */
        /*hash_map_less_equal        */
        /*hash_map_great             */
        /*hash_map_great_equal       */
        {
            hash_map_t* pt_hmap = create_hash_map(int, double);
            hash_map_t* pt_hmapex = create_hash_map(int, double);
            pair_t* pt_pair = create_pair(int, double);
            if(pt_hmap == NULL || pt_hmapex == NULL || pt_pair == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_int_key_hash, NULL);
            hash_map_init_ex(pt_hmapex, 0, _hash_map_int_key_hash, NULL);
            pair_init(pt_pair);

            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);
            _print_hash_map_c(pt_hmapex, "<%d, %lf>, ", int, double);
            printf("equal: %d, not equal: %d, ",
                hash_map_equal(pt_hmap, pt_hmapex), hash_map_not_equal(pt_hmap, pt_hmapex));
            printf("less: %d, less equal: %d, ",
                hash_map_less(pt_hmap, pt_hmapex), hash_map_less_equal(pt_hmap, pt_hmapex));
            printf("great: %d, great equal: %d\n",
                hash_map_great(pt_hmap, pt_hmapex), hash_map_great_equal(pt_hmap, pt_hmapex));

            pair_make(pt_pair, 4, 89.23);
            hash_map_insert(pt_hmap, pt_pair);
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);
            _print_hash_map_c(pt_hmapex, "<%d, %lf>, ", int, double);
            printf("equal: %d, not equal: %d, ",
                hash_map_equal(pt_hmap, pt_hmapex), hash_map_not_equal(pt_hmap, pt_hmapex));
            printf("less: %d, less equal: %d, ",
                hash_map_less(pt_hmap, pt_hmapex), hash_map_less_equal(pt_hmap, pt_hmapex));
            printf("great: %d, great equal: %d\n",
                hash_map_great(pt_hmap, pt_hmapex), hash_map_great_equal(pt_hmap, pt_hmapex));

            hash_map_insert(pt_hmapex, pt_pair);
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);
            _print_hash_map_c(pt_hmapex, "<%d, %lf>, ", int, double);
            printf("equal: %d, not equal: %d, ",
                hash_map_equal(pt_hmap, pt_hmapex), hash_map_not_equal(pt_hmap, pt_hmapex));
            printf("less: %d, less equal: %d, ",
                hash_map_less(pt_hmap, pt_hmapex), hash_map_less_equal(pt_hmap, pt_hmapex));
            printf("great: %d, great equal: %d\n",
                hash_map_great(pt_hmap, pt_hmapex), hash_map_great_equal(pt_hmap, pt_hmapex));

            pair_make(pt_pair, 2, 90.2);
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, 3, 2323.23423);
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, 10, 10.0);
            hash_map_insert(pt_hmapex, pt_pair);
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);
            _print_hash_map_c(pt_hmapex, "<%d, %lf>, ", int, double);
            printf("equal: %d, not equal: %d, ",
                hash_map_equal(pt_hmap, pt_hmapex), hash_map_not_equal(pt_hmap, pt_hmapex));
            printf("less: %d, less equal: %d, ",
                hash_map_less(pt_hmap, pt_hmapex), hash_map_less_equal(pt_hmap, pt_hmapex));
            printf("great: %d, great equal: %d\n",
                hash_map_great(pt_hmap, pt_hmapex), hash_map_great_equal(pt_hmap, pt_hmapex));

            hash_map_destroy(pt_hmap);
            hash_map_destroy(pt_hmapex);
            pair_destroy(pt_pair);
        }
        /*hash_map_begin             */
        /*hash_map_end               */
        /*hash_map_find              */
        /*hash_map_count             */
        {
            hash_map_t* pt_hmap = create_hash_map(int, double);
            pair_t* pt_pair = create_pair(int, double);
            iterator_t t_iter;
            if(pt_hmap == NULL || pt_pair == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_int_key_hash, NULL);
            pair_init(pt_pair);

            pair_make(pt_pair, 0, 0.0);
            t_iter = hash_map_find(pt_hmap, 0);
            if(iterator_equal(t_iter, hash_map_end(pt_hmap)))
            {
                printf("not found! count : %u\n", hash_map_count(pt_hmap, 0));
            }
            else
            {
                printf("found! count : %u\n", hash_map_count(pt_hmap, 0));
            }

            pair_make(pt_pair, 45, 23.232);
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, 23, 1.111);
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, 56, 23.2222);
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, 0, 0.0);

            t_iter = hash_map_find(pt_hmap, 0);
            if(iterator_equal(t_iter, hash_map_end(pt_hmap)))
            {
                printf("not found! count : %u\n", hash_map_count(pt_hmap, 0));
            }
            else
            {
                printf("found! count : %u\n", hash_map_count(pt_hmap, 0));
            }

            pair_make(pt_pair, 45, 23.232);
            t_iter = hash_map_find(pt_hmap, 45);
            if(iterator_equal(t_iter, hash_map_end(pt_hmap)))
            {
                printf("not found! count : %u\n", hash_map_count(pt_hmap, 45));
            }
            else
            {
                printf("found! count : %u\n", hash_map_count(pt_hmap, 45));
            }

            hash_map_destroy(pt_hmap);
            pair_destroy(pt_pair);
        }
        /*hash_map_equal_range       */
        {
            hash_map_t* pt_hmap = create_hash_map(int, double);
            pair_t* pt_pair = create_pair(int, double);
            range_t t_range;
            if(pt_hmap == NULL || pt_pair == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_int_key_hash, NULL);
            pair_init(pt_pair);

            t_range = hash_map_equal_range(pt_hmap, 0);
            assert(iterator_equal(t_range.t_begin, hash_map_end(pt_hmap)) &&
                iterator_equal(t_range.t_begin, t_range.t_end));

            pair_make(pt_pair, 3, 290.2323);
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, 67, 34.11);
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, 5, 333.222);
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, 14, 44.4);
            hash_map_insert(pt_hmap, pt_pair);
            t_range = hash_map_equal_range(pt_hmap, 0);
            assert(iterator_equal(t_range.t_begin, t_range.t_end));
            t_range = hash_map_equal_range(pt_hmap, 14);
            assert(iterator_equal(iterator_next(t_range.t_begin), t_range.t_end));

            hash_map_destroy(pt_hmap);
            pair_destroy(pt_pair);
        }
        /*hash_map_at                */
        {
            hash_map_t* pt_hmap = create_hash_map(int, double);
            pair_t* pt_pair = create_pair(int, double);
            if(pt_hmap == NULL || pt_pair == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_int_key_hash, NULL);
            pair_init(pt_pair);

            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);
            printf("%lf\n", *(double*)hash_map_at(pt_hmap, 8));
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);

            pair_make(pt_pair, 4, 232.222);
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, 0, 2.222);
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, 9, 12.111);
            hash_map_insert(pt_hmap, pt_pair);

            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);
            *(double*)hash_map_at(pt_hmap, 0) = 0.0;
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);

            hash_map_destroy(pt_hmap);
            pair_destroy(pt_pair);
        }
        /*hash_map_insert            */
        {
            hash_map_t* pt_hmap = create_hash_map(int, double);
            pair_t* pt_pair = create_pair(int, double);
            if(pt_hmap == NULL || pt_pair == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_int_key_hash, NULL);
            pair_init(pt_pair);
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);
            pair_make(pt_pair, 23, 0.983);
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, 4, 90.0);
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, 2, 2.22);
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, 4, -83784.2323);
            hash_map_insert(pt_hmap, pt_pair);
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);

            hash_map_destroy(pt_hmap);
            pair_destroy(pt_pair);
        }
        /*hash_map_insert_range      */
        {
            hash_map_t* pt_hmap = create_hash_map(int, double);
            hash_map_t* pt_hmapex = create_hash_map(int, double);
            pair_t* pt_pair = create_pair(int, double);
            if(pt_hmap == NULL || pt_hmapex == NULL || pt_pair == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_int_key_hash, NULL);
            hash_map_init_ex(pt_hmapex, 0, _hash_map_int_key_hash, NULL);
            pair_init(pt_pair);

            hash_map_insert_range(pt_hmap, hash_map_begin(pt_hmapex), hash_map_end(pt_hmapex));
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);

            *(double*)hash_map_at(pt_hmapex, 45) = 4.34;
            *(double*)hash_map_at(pt_hmapex, 2) = -4.245;
            *(double*)hash_map_at(pt_hmapex, 56) = 34.23;
            *(double*)hash_map_at(pt_hmapex, 3) = 3.3;
            *(double*)hash_map_at(pt_hmapex, 0) = 0.0;
            *(double*)hash_map_at(pt_hmapex, 343) = 5.5634;
            *(double*)hash_map_at(pt_hmapex, 22) = 22.22;
            *(double*)hash_map_at(pt_hmapex, 5) = 5.5555;
            *(double*)hash_map_at(pt_hmapex, 4) = 10.1;
            *(double*)hash_map_at(pt_hmapex, 334) = -0.000003;
            *(double*)hash_map_at(pt_hmapex, 44) = 44.44;
            *(double*)hash_map_at(pt_hmapex, 1) = 1.1;
            _print_hash_map_c(pt_hmapex, "<%d, %lf>, ", int, double);

            hash_map_insert_range(pt_hmap, hash_map_begin(pt_hmapex), hash_map_begin(pt_hmapex));
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);
            hash_map_insert_range(pt_hmap, hash_map_begin(pt_hmapex),
                iterator_advance(hash_map_begin(pt_hmapex), 3));
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);
            hash_map_insert_range(pt_hmap, iterator_advance(hash_map_begin(pt_hmapex), 5),
                iterator_advance(hash_map_begin(pt_hmapex), 7));
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);
            hash_map_insert_range(pt_hmap, iterator_advance(hash_map_begin(pt_hmapex), 9),
                hash_map_end(pt_hmapex));
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);
            hash_map_insert_range(pt_hmap, hash_map_end(pt_hmapex), hash_map_end(pt_hmapex));
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);
            hash_map_clear(pt_hmap);
            hash_map_insert_range(pt_hmap, hash_map_begin(pt_hmapex), hash_map_end(pt_hmapex));
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);

            hash_map_destroy(pt_hmap);
            hash_map_destroy(pt_hmapex);
            pair_destroy(pt_pair);
        }
        /*hash_map_erase             */
        {
            hash_map_t* pt_hmap = create_hash_map(int, double);
            if(pt_hmap == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_int_key_hash, NULL);
            hash_map_erase(pt_hmap, 0);
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);

            *(double*)hash_map_at(pt_hmap, 45) = 4.34;
            *(double*)hash_map_at(pt_hmap, 2) = -4.245;
            *(double*)hash_map_at(pt_hmap, 56) = 34.23;
            *(double*)hash_map_at(pt_hmap, 3) = 3.3;
            *(double*)hash_map_at(pt_hmap, 0) = 0.0;
            *(double*)hash_map_at(pt_hmap, 343) = 5.5634;
            *(double*)hash_map_at(pt_hmap, 22) = 22.22;
            *(double*)hash_map_at(pt_hmap, 5) = 5.5555;
            *(double*)hash_map_at(pt_hmap, 4) = 10.1;
            *(double*)hash_map_at(pt_hmap, 334) = -0.000003;
            *(double*)hash_map_at(pt_hmap, 44) = 44.44;
            *(double*)hash_map_at(pt_hmap, 1) = 1.1;
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);

            hash_map_erase(pt_hmap, 10);
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);
            hash_map_erase(pt_hmap, 22);
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);

            hash_map_destroy(pt_hmap);
        }
        /*hash_map_erase_pos         */
        {
            hash_map_t* pt_hmap = create_hash_map(int, double);
            if(pt_hmap == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_int_key_hash, NULL);
            *(double*)hash_map_at(pt_hmap, 45) = 4.34;
            *(double*)hash_map_at(pt_hmap, 2) = -4.245;
            *(double*)hash_map_at(pt_hmap, 56) = 34.23;
            *(double*)hash_map_at(pt_hmap, 3) = 3.3;
            *(double*)hash_map_at(pt_hmap, 0) = 0.0;
            *(double*)hash_map_at(pt_hmap, 343) = 5.5634;
            *(double*)hash_map_at(pt_hmap, 22) = 22.22;
            *(double*)hash_map_at(pt_hmap, 5) = 5.5555;
            *(double*)hash_map_at(pt_hmap, 4) = 10.1;
            *(double*)hash_map_at(pt_hmap, 334) = -0.000003;
            *(double*)hash_map_at(pt_hmap, 44) = 44.44;
            *(double*)hash_map_at(pt_hmap, 1) = 1.1;
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);

            hash_map_erase_pos(pt_hmap, hash_map_begin(pt_hmap));
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);
            hash_map_erase_pos(pt_hmap, iterator_advance(hash_map_begin(pt_hmap), 3));
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);
            while(!hash_map_empty(pt_hmap))
            {
                hash_map_erase_pos(pt_hmap, hash_map_begin(pt_hmap));
            }
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);

            hash_map_destroy(pt_hmap);
        }
        /*hash_map_erase_range       */
        {
            hash_map_t* pt_hmap = create_hash_map(int, double);
            if(pt_hmap == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_int_key_hash, NULL);
            hash_map_erase_range(pt_hmap, hash_map_begin(pt_hmap), hash_map_end(pt_hmap));
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);
            *(double*)hash_map_at(pt_hmap, 45) = 4.34;
            *(double*)hash_map_at(pt_hmap, 2) = -4.245;
            *(double*)hash_map_at(pt_hmap, 56) = 34.23;
            *(double*)hash_map_at(pt_hmap, 3) = 3.3;
            *(double*)hash_map_at(pt_hmap, 0) = 0.0;
            *(double*)hash_map_at(pt_hmap, 343) = 5.5634;
            *(double*)hash_map_at(pt_hmap, 22) = 22.22;
            *(double*)hash_map_at(pt_hmap, 5) = 5.5555;
            *(double*)hash_map_at(pt_hmap, 4) = 10.1;
            *(double*)hash_map_at(pt_hmap, 334) = -0.000003;
            *(double*)hash_map_at(pt_hmap, 44) = 44.44;
            *(double*)hash_map_at(pt_hmap, 1) = 1.1;
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);

            hash_map_erase_range(pt_hmap, hash_map_begin(pt_hmap), hash_map_begin(pt_hmap));
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);
            hash_map_erase_range(pt_hmap, hash_map_begin(pt_hmap),
                iterator_advance(hash_map_begin(pt_hmap), 3));
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);
            hash_map_erase_range(pt_hmap, iterator_next(hash_map_begin(pt_hmap)),
                iterator_advance(hash_map_begin(pt_hmap), 4));
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);
            hash_map_erase_range(pt_hmap, iterator_advance(hash_map_begin(pt_hmap), 3),
                hash_map_end(pt_hmap));
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);
            hash_map_erase_range(pt_hmap, hash_map_end(pt_hmap), hash_map_end(pt_hmap));
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);
            hash_map_erase_range(pt_hmap, hash_map_begin(pt_hmap), hash_map_end(pt_hmap));
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);

            hash_map_destroy(pt_hmap);
        }
        /*hash_map_clear             */
        {
            hash_map_t* pt_hmap = create_hash_map(int, double);
            if(pt_hmap == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_int_key_hash, NULL);
            hash_map_clear(pt_hmap);
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);
            *(double*)hash_map_at(pt_hmap, 45) = 4.34;
            *(double*)hash_map_at(pt_hmap, 2) = -4.245;
            *(double*)hash_map_at(pt_hmap, 56) = 34.23;
            *(double*)hash_map_at(pt_hmap, 3) = 3.3;
            *(double*)hash_map_at(pt_hmap, 0) = 0.0;
            *(double*)hash_map_at(pt_hmap, 343) = 5.5634;
            *(double*)hash_map_at(pt_hmap, 22) = 22.22;
            *(double*)hash_map_at(pt_hmap, 5) = 5.5555;
            *(double*)hash_map_at(pt_hmap, 4) = 10.1;
            *(double*)hash_map_at(pt_hmap, 334) = -0.000003;
            *(double*)hash_map_at(pt_hmap, 44) = 44.44;
            *(double*)hash_map_at(pt_hmap, 1) = 1.1;
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);

            hash_map_clear(pt_hmap);
            _print_hash_map_c(pt_hmap, "<%d, %lf>, ", int, double);

            hash_map_destroy(pt_hmap);
        }
    }
    /* user define type */
    {
        type_register(hash_sample_t, _hash_sample_init, _hash_sample_copy,
            _hash_sample_less, _hash_sample_destroy);
        /*create_hash_map            */
        /*hash_map_init              */
        {
            hash_map_t* pt_hmap = create_hash_map(int, hash_sample_t);
            if(pt_hmap == NULL)
            {
                return;
            }
            hash_map_init(pt_hmap);
            _print_hash_map_sample(pt_hmap);
            ((hash_sample_t*)hash_map_at(pt_hmap, 34))->_d_first = 43.4;
            ((hash_sample_t*)hash_map_at(pt_hmap, 34))->_l_second = 4509;
            _print_hash_map_sample(pt_hmap);
            hash_map_destroy(pt_hmap);
        }
        /*hash_map_init_ex           */
        {
            hash_map_t* pt_hmap = create_hash_map(int, hash_sample_t);
            if(pt_hmap == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_sample_hash, NULL);
            _print_hash_map_sample(pt_hmap);
            ((hash_sample_t*)hash_map_at(pt_hmap, 34))->_d_first = 43.4;
            ((hash_sample_t*)hash_map_at(pt_hmap, 34))->_l_second = 4509;
            ((hash_sample_t*)hash_map_at(pt_hmap, 90))->_d_first = -1.11;
            ((hash_sample_t*)hash_map_at(pt_hmap, 90))->_l_second = 90;
            _print_hash_map_sample(pt_hmap);

            hash_map_destroy(pt_hmap);
        }
        /*hash_map_init_copy         */
        {
            hash_map_t* pt_hmap = create_hash_map(int, hash_sample_t);
            hash_map_t* pt_hmapex = create_hash_map(int, hash_sample_t);
            if(pt_hmap == NULL || pt_hmapex == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmapex, 0, _hash_map_sample_hash, NULL);

            ((hash_sample_t*)hash_map_at(pt_hmapex, 34))->_d_first = 43.4;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 34))->_l_second = 4509;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 90))->_d_first = -1.11;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 90))->_l_second = 90;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 9))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 9))->_l_second = 50;

            hash_map_init_copy(pt_hmap, pt_hmapex);
            _print_hash_map_sample(pt_hmap);
            hash_map_destroy(pt_hmap);
            hash_map_destroy(pt_hmapex);
        }
        /*hash_map_init_copy_range   */
        {
            hash_map_t* pt_hmap = create_hash_map(int, hash_sample_t);
            hash_map_t* pt_hmapex = create_hash_map(int, hash_sample_t);
            if(pt_hmap == NULL || pt_hmapex == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmapex, 0, _hash_map_sample_hash, NULL);

            ((hash_sample_t*)hash_map_at(pt_hmapex, 34))->_d_first = 43.4;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 34))->_l_second = 4509;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 90))->_d_first = -1.11;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 90))->_l_second = 90;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 9))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 9))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 56))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 56))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 54))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 54))->_l_second = 50;
            _print_hash_map_sample(pt_hmapex);

            hash_map_init_copy_range(pt_hmap,
                hash_map_begin(pt_hmapex), hash_map_end(pt_hmapex));
            _print_hash_map_sample(pt_hmap);
            hash_map_destroy(pt_hmap);
            hash_map_destroy(pt_hmapex);
        }
        /*hash_map_init_copy_range_ex*/
        {
            hash_map_t* pt_hmap = create_hash_map(int, hash_sample_t);
            hash_map_t* pt_hmapex = create_hash_map(int, hash_sample_t);
            if(pt_hmap == NULL || pt_hmapex == NULL)
            {
                return;
            }
            hash_map_init(pt_hmapex);

            ((hash_sample_t*)hash_map_at(pt_hmapex, 34))->_d_first = 43.4;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 34))->_l_second = 4509;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 90))->_d_first = -1.11;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 90))->_l_second = 90;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 9))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 9))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 56))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 56))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 54))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 54))->_l_second = 50;
            _print_hash_map_sample(pt_hmapex);

            hash_map_init_copy_range_ex(pt_hmap,
                hash_map_begin(pt_hmapex), hash_map_end(pt_hmapex),
                0, _hash_map_sample_hash, NULL);
            _print_hash_map_sample(pt_hmap);
            hash_map_destroy(pt_hmap);
            hash_map_destroy(pt_hmapex);
        }
        /*hash_map_destroy           */
        /*hash_map_assign            */
        {
            hash_map_t* pt_hmap = create_hash_map(int, hash_sample_t);
            hash_map_t* pt_hmapex = create_hash_map(int, hash_sample_t);
            if(pt_hmap == NULL || pt_hmapex == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_sample_hash, NULL);
            hash_map_init_ex(pt_hmapex, 0, _hash_map_sample_hash, NULL);
            hash_map_assign(pt_hmap, pt_hmapex);
            _print_hash_map_sample(pt_hmap);

            ((hash_sample_t*)hash_map_at(pt_hmapex, 34))->_d_first = 43.4;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 34))->_l_second = 4509;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 90))->_d_first = -1.11;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 90))->_l_second = 90;

            hash_map_assign(pt_hmap, pt_hmapex);
            _print_hash_map_sample(pt_hmap);

            hash_map_clear(pt_hmapex);
            ((hash_sample_t*)hash_map_at(pt_hmapex, 9))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 9))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 56))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 56))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 54))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 54))->_l_second = 50;

            hash_map_assign(pt_hmap, pt_hmapex);
            _print_hash_map_sample(pt_hmap);

            hash_map_clear(pt_hmapex);
            ((hash_sample_t*)hash_map_at(pt_hmapex, 100))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 100))->_l_second = 50;
            hash_map_assign(pt_hmap, pt_hmapex);
            _print_hash_map_sample(pt_hmap);

            hash_map_clear(pt_hmapex);
            hash_map_assign(pt_hmap, pt_hmapex);
            _print_hash_map_sample(pt_hmap);

            hash_map_destroy(pt_hmap);
            hash_map_destroy(pt_hmapex);
        }
        /*hash_map_swap              */
        {
            hash_map_t* pt_hmap = create_hash_map(int, hash_sample_t);
            hash_map_t* pt_hmapex = create_hash_map(int, hash_sample_t);
            if(pt_hmap == NULL || pt_hmapex == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_sample_hash, NULL);
            hash_map_init_ex(pt_hmapex, 0, _hash_map_sample_hash, NULL);
            hash_map_swap(pt_hmap, pt_hmapex);
            _print_hash_map_sample(pt_hmap);
            _print_hash_map_sample(pt_hmapex);

            ((hash_sample_t*)hash_map_at(pt_hmapex, 34))->_d_first = 43.4;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 34))->_l_second = 4509;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 90))->_d_first = -1.11;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 90))->_l_second = 90;

            hash_map_swap(pt_hmap, pt_hmapex);
            _print_hash_map_sample(pt_hmap);
            _print_hash_map_sample(pt_hmapex);

            hash_map_clear(pt_hmapex);
            ((hash_sample_t*)hash_map_at(pt_hmapex, 9))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 9))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 56))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 56))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 54))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 54))->_l_second = 50;

            hash_map_swap(pt_hmap, pt_hmapex);
            _print_hash_map_sample(pt_hmap);
            _print_hash_map_sample(pt_hmapex);

            hash_map_clear(pt_hmapex);
            ((hash_sample_t*)hash_map_at(pt_hmapex, 100))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 100))->_l_second = 50;
            hash_map_swap(pt_hmap, pt_hmapex);
            _print_hash_map_sample(pt_hmap);
            _print_hash_map_sample(pt_hmapex);

            hash_map_clear(pt_hmapex);
            hash_map_swap(pt_hmap, pt_hmapex);
            _print_hash_map_sample(pt_hmap);
            _print_hash_map_sample(pt_hmapex);

            hash_map_destroy(pt_hmap);
            hash_map_destroy(pt_hmapex);
        }
        /*hash_map_size              */
        /*hash_map_empty             */
        /*hash_map_max_size          */
        /*hash_map_bucket_count      */
        /*hash_map_hash              */
        /*hash_map_key_less          */
        {
            hash_map_t* pt_hmap = create_hash_map(int, hash_sample_t);
            if(pt_hmap == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_sample_hash, fun_great_int);
            assert(hash_map_hash(pt_hmap) == _hash_map_sample_hash &&
                hash_map_key_less(pt_hmap) == fun_great_int);
            hash_map_destroy(pt_hmap);
        }
        /*hash_map_resize            */
        {
            hash_map_t* pt_hmap = create_hash_map(int, hash_sample_t);
            if(pt_hmap == NULL)
            {
                return;
            }
            hash_map_init(pt_hmap);
            _print_hash_map_sample(pt_hmap);
            hash_map_resize(pt_hmap, 70);
            _print_hash_map_sample(pt_hmap);
            hash_map_resize(pt_hmap, 100);
            _print_hash_map_sample(pt_hmap);
            hash_map_resize(pt_hmap, 30);
            _print_hash_map_sample(pt_hmap);
            hash_map_resize(pt_hmap, 0);
            _print_hash_map_sample(pt_hmap);
            hash_map_destroy(pt_hmap);
        }
        /*hash_map_equal             */
        /*hash_map_not_equal         */
        /*hash_map_less              */
        /*hash_map_less_equal        */
        /*hash_map_great             */
        /*hash_map_great_equal       */
        {
            hash_map_t* pt_hmap = create_hash_map(int, hash_sample_t);
            hash_map_t* pt_hmapex = create_hash_map(int, hash_sample_t);
            hash_sample_t t_sample;
            pair_t* pt_pair = create_pair(int, hash_sample_t);
            if(pt_hmap == NULL || pt_hmapex == NULL || pt_pair == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_sample_hash, NULL);
            hash_map_init_ex(pt_hmapex, 0, _hash_map_sample_hash, NULL);
            pair_init(pt_pair);

            _print_hash_map_sample(pt_hmap);
            _print_hash_map_sample(pt_hmapex);
            printf("equal: %d, not equal: %d, ",
                hash_map_equal(pt_hmap, pt_hmapex), hash_map_not_equal(pt_hmap, pt_hmapex));
            printf("less: %d, less equal: %d, ",
                hash_map_less(pt_hmap, pt_hmapex), hash_map_less_equal(pt_hmap, pt_hmapex));
            printf("great: %d, great equal: %d\n",
                hash_map_great(pt_hmap, pt_hmapex), hash_map_great_equal(pt_hmap, pt_hmapex));

            t_sample._d_first = 89.23;
            t_sample._l_second = -11002244;
            pair_make(pt_pair, 4, &t_sample);
            hash_map_insert(pt_hmap, pt_pair);
            _print_hash_map_sample(pt_hmap);
            _print_hash_map_sample(pt_hmapex);
            printf("equal: %d, not equal: %d, ",
                hash_map_equal(pt_hmap, pt_hmapex), hash_map_not_equal(pt_hmap, pt_hmapex));
            printf("less: %d, less equal: %d, ",
                hash_map_less(pt_hmap, pt_hmapex), hash_map_less_equal(pt_hmap, pt_hmapex));
            printf("great: %d, great equal: %d\n",
                hash_map_great(pt_hmap, pt_hmapex), hash_map_great_equal(pt_hmap, pt_hmapex));

            hash_map_insert(pt_hmapex, pt_pair);
            _print_hash_map_sample(pt_hmap);
            _print_hash_map_sample(pt_hmapex);
            printf("equal: %d, not equal: %d, ",
                hash_map_equal(pt_hmap, pt_hmapex), hash_map_not_equal(pt_hmap, pt_hmapex));
            printf("less: %d, less equal: %d, ",
                hash_map_less(pt_hmap, pt_hmapex), hash_map_less_equal(pt_hmap, pt_hmapex));
            printf("great: %d, great equal: %d\n",
                hash_map_great(pt_hmap, pt_hmapex), hash_map_great_equal(pt_hmap, pt_hmapex));

            t_sample._d_first = 90.2;
            t_sample._l_second = 5555555;
            pair_make(pt_pair, 2, &t_sample);
            hash_map_insert(pt_hmap, pt_pair);
            t_sample._d_first = 2323.2323;
            t_sample._l_second = -10101010;
            pair_make(pt_pair, 3, &t_sample);
            hash_map_insert(pt_hmap, pt_pair);
            t_sample._d_first = 10.0;
            t_sample._l_second = 10;
            pair_make(pt_pair, 10, &t_sample);
            hash_map_insert(pt_hmapex, pt_pair);
            _print_hash_map_sample(pt_hmap);
            _print_hash_map_sample(pt_hmapex);
            printf("equal: %d, not equal: %d, ",
                hash_map_equal(pt_hmap, pt_hmapex), hash_map_not_equal(pt_hmap, pt_hmapex));
            printf("less: %d, less equal: %d, ",
                hash_map_less(pt_hmap, pt_hmapex), hash_map_less_equal(pt_hmap, pt_hmapex));
            printf("great: %d, great equal: %d\n",
                hash_map_great(pt_hmap, pt_hmapex), hash_map_great_equal(pt_hmap, pt_hmapex));

            hash_map_destroy(pt_hmap);
            hash_map_destroy(pt_hmapex);
            pair_destroy(pt_pair);
        }
        /*hash_map_begin             */
        /*hash_map_end               */
        /*hash_map_find              */
        /*hash_map_count             */
        {
            hash_map_t* pt_hmap = create_hash_map(int, hash_sample_t);
            iterator_t t_iter;
            if(pt_hmap == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_sample_hash, NULL);
            t_iter = hash_map_find(pt_hmap, 0);
            if(iterator_equal(t_iter, hash_map_end(pt_hmap)))
            {
                printf("not found! count : %u\n", hash_map_count(pt_hmap, 0));
            }
            else
            {
                printf("found! count : %u\n", hash_map_count(pt_hmap, 0));
            }

            ((hash_sample_t*)hash_map_at(pt_hmap, 9))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmap, 9))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmap, 56))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmap, 56))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmap, 54))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmap, 54))->_l_second = 50;

            t_iter = hash_map_find(pt_hmap, 0);
            if(iterator_equal(t_iter, hash_map_end(pt_hmap)))
            {
                printf("not found! count : %u\n", hash_map_count(pt_hmap, 0));
            }
            else
            {
                printf("found! count : %u\n", hash_map_count(pt_hmap, 0));
            }
            t_iter = hash_map_find(pt_hmap, 9);
            if(iterator_equal(t_iter, hash_map_end(pt_hmap)))
            {
                printf("not found! count : %u\n", hash_map_count(pt_hmap, 9));
            }
            else
            {
                printf("found! count : %u\n", hash_map_count(pt_hmap, 9));
            }

            hash_map_destroy(pt_hmap);
        }
        /*hash_map_equal_range       */
        {
            hash_map_t* pt_hmap = create_hash_map(int, hash_sample_t);
            range_t t_range;
            if(pt_hmap == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_sample_hash, NULL);
            t_range = hash_map_equal_range(pt_hmap, 0);
            assert(iterator_equal(t_range.t_begin, hash_map_end(pt_hmap)) &&
                iterator_equal(t_range.t_begin, t_range.t_end));
            ((hash_sample_t*)hash_map_at(pt_hmap, 9))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmap, 9))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmap, 56))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmap, 56))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmap, 54))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmap, 54))->_l_second = 50;
            t_range = hash_map_equal_range(pt_hmap, 0);
            assert(iterator_equal(t_range.t_begin, t_range.t_end));
            t_range = hash_map_equal_range(pt_hmap, 56);
            assert(iterator_equal(iterator_next(t_range.t_begin), t_range.t_end));

            hash_map_destroy(pt_hmap);
        }
        /*hash_map_at                */
        {
            hash_map_t* pt_hmap = create_hash_map(int, hash_sample_t);
            if(pt_hmap == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_sample_hash, NULL);
            ((hash_sample_t*)hash_map_at(pt_hmap, 9))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmap, 9))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmap, 56))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmap, 56))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmap, 54))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmap, 54))->_l_second = 50;
            _print_hash_map_sample(pt_hmap);
            ((hash_sample_t*)hash_map_at(pt_hmap, 56))->_l_second = 500000;
            ((hash_sample_t*)hash_map_at(pt_hmap, 9))->_d_first = -0.00001;
            _print_hash_map_sample(pt_hmap);

            hash_map_destroy(pt_hmap);
        }
        /*hash_map_insert            */
        {
            hash_map_t* pt_hmap = create_hash_map(int, hash_sample_t);
            pair_t* pt_pair = create_pair(int, hash_sample_t);
            hash_sample_t t_sample;
            if(pt_hmap == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_sample_hash, NULL);
            pair_init(pt_pair);
            _print_hash_map_sample(pt_hmap);
            t_sample._d_first = 90.2;
            t_sample._l_second = 5555555;
            pair_make(pt_pair, 2, &t_sample);
            hash_map_insert(pt_hmap, pt_pair);
            t_sample._d_first = 2323.2323;
            t_sample._l_second = -10101010;
            pair_make(pt_pair, 3, &t_sample);
            hash_map_insert(pt_hmap, pt_pair);
            t_sample._d_first = 10.0;
            t_sample._l_second = 10;
            pair_make(pt_pair, 10, &t_sample);
            hash_map_insert(pt_hmap, pt_pair);
            t_sample._d_first = 10.110;
            t_sample._l_second = 1011;
            pair_make(pt_pair, 10, &t_sample);
            hash_map_insert(pt_hmap, pt_pair);
            _print_hash_map_sample(pt_hmap);
            
            hash_map_destroy(pt_hmap);
            pair_destroy(pt_pair);
        }
        /*hash_map_insert_range      */
        {
            hash_map_t* pt_hmap = create_hash_map(int, hash_sample_t);
            hash_map_t* pt_hmapex = create_hash_map(int, hash_sample_t);
            if(pt_hmap == NULL || pt_hmapex == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_sample_hash, NULL);
            hash_map_init_ex(pt_hmapex, 0, _hash_map_sample_hash, NULL);
            hash_map_insert_range(pt_hmap,
                hash_map_begin(pt_hmapex), hash_map_end(pt_hmapex));
            _print_hash_map_sample(pt_hmap);

            ((hash_sample_t*)hash_map_at(pt_hmapex, 9))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 9))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 6))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 6))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 4))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 4))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 19))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 19))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 86))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 86))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 7))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 7))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 3))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 3))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 56))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 56))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 54))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmapex, 54))->_l_second = 50;
            _print_hash_map_sample(pt_hmapex);

            hash_map_insert_range(pt_hmap,
                hash_map_begin(pt_hmapex), hash_map_begin(pt_hmapex));
            _print_hash_map_sample(pt_hmap);
            hash_map_insert_range(pt_hmap,
                hash_map_begin(pt_hmapex), iterator_advance(hash_map_begin(pt_hmapex), 3));
            _print_hash_map_sample(pt_hmap);
            hash_map_insert_range(pt_hmap,
                iterator_advance(hash_map_begin(pt_hmapex), 5),
                iterator_advance(hash_map_begin(pt_hmapex), 7));
            _print_hash_map_sample(pt_hmap);
            hash_map_insert_range(pt_hmap, iterator_advance(hash_map_begin(pt_hmapex), 8),
                hash_map_end(pt_hmapex));
            _print_hash_map_sample(pt_hmap);
            hash_map_insert_range(pt_hmap, hash_map_end(pt_hmapex), hash_map_end(pt_hmapex));
            _print_hash_map_sample(pt_hmap);

            hash_map_clear(pt_hmap);
            hash_map_insert_range(pt_hmap, hash_map_begin(pt_hmapex), hash_map_end(pt_hmapex));
            _print_hash_map_sample(pt_hmap);

            hash_map_destroy(pt_hmap);
            hash_map_destroy(pt_hmapex);
        }
        /*hash_map_erase             */
        {
            hash_map_t* pt_hmap = create_hash_map(int, hash_sample_t);
            if(pt_hmap == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_sample_hash, NULL);
            hash_map_erase(pt_hmap, 0);
            _print_hash_map_sample(pt_hmap);
            ((hash_sample_t*)hash_map_at(pt_hmap, 9))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmap, 9))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmap, 6))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmap, 6))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmap, 4))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmap, 4))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmap, 19))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmap, 19))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmap, 86))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmap, 86))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmap, 7))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmap, 7))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmap, 3))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmap, 3))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmap, 56))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmap, 56))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmap, 54))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmap, 54))->_l_second = 50;
            _print_hash_map_sample(pt_hmap);
            hash_map_erase(pt_hmap, 0);
            _print_hash_map_sample(pt_hmap);
            hash_map_erase(pt_hmap, 7);
            _print_hash_map_sample(pt_hmap);
            hash_map_destroy(pt_hmap);
        }
        /*hash_map_erase_pos         */
        {
            hash_map_t* pt_hmap = create_hash_map(int, hash_sample_t);
            if(pt_hmap == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_sample_hash, NULL);
            ((hash_sample_t*)hash_map_at(pt_hmap, 9))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmap, 9))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmap, 6))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmap, 6))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmap, 4))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmap, 4))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmap, 19))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmap, 19))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmap, 86))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmap, 86))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmap, 7))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmap, 7))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmap, 3))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmap, 3))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmap, 56))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmap, 56))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmap, 54))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmap, 54))->_l_second = 50;
            _print_hash_map_sample(pt_hmap);
            hash_map_erase_pos(pt_hmap, hash_map_begin(pt_hmap));
            _print_hash_map_sample(pt_hmap);
            hash_map_erase_pos(pt_hmap, iterator_advance(hash_map_begin(pt_hmap), 4));
            _print_hash_map_sample(pt_hmap);
            while(!hash_map_empty(pt_hmap))
            {
                hash_map_erase_pos(pt_hmap, hash_map_begin(pt_hmap));
            }
            _print_hash_map_sample(pt_hmap);
            while(!hash_map_empty(pt_hmap))
            hash_map_destroy(pt_hmap);
        }
        /*hash_map_erase_range       */
        {
            hash_map_t* pt_hmap = create_hash_map(int, hash_sample_t);
            if(pt_hmap == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_sample_hash, NULL);
            hash_map_erase_range(pt_hmap, hash_map_begin(pt_hmap), hash_map_end(pt_hmap));
            _print_hash_map_sample(pt_hmap);
            ((hash_sample_t*)hash_map_at(pt_hmap, 9))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmap, 9))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmap, 6))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmap, 6))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmap, 4))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmap, 4))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmap, 19))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmap, 19))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmap, 86))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmap, 86))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmap, 7))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmap, 7))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmap, 3))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmap, 3))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmap, 56))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmap, 56))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmap, 54))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmap, 54))->_l_second = 50;
            _print_hash_map_sample(pt_hmap);
            hash_map_erase_range(pt_hmap, hash_map_begin(pt_hmap), hash_map_begin(pt_hmap));
            _print_hash_map_sample(pt_hmap);
            hash_map_erase_range(pt_hmap,
                hash_map_begin(pt_hmap), iterator_advance(hash_map_begin(pt_hmap), 3));
            _print_hash_map_sample(pt_hmap);
            hash_map_erase_range(pt_hmap,
                iterator_next(hash_map_begin(pt_hmap)),
                iterator_advance(hash_map_begin(pt_hmap), 3));
            _print_hash_map_sample(pt_hmap);
            hash_map_erase_range(pt_hmap,
                iterator_advance(hash_map_begin(pt_hmap), 2), hash_map_end(pt_hmap));
            _print_hash_map_sample(pt_hmap);
            hash_map_erase_range(pt_hmap,
                hash_map_end(pt_hmap), hash_map_end(pt_hmap));
            _print_hash_map_sample(pt_hmap);
            hash_map_erase_range(pt_hmap,
                hash_map_begin(pt_hmap), hash_map_end(pt_hmap));
            _print_hash_map_sample(pt_hmap);

            hash_map_destroy(pt_hmap);
        }
        /*hash_map_clear             */
        {
            hash_map_t* pt_hmap = create_hash_map(int, hash_sample_t);
            if(pt_hmap == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_sample_hash, NULL);
            hash_map_clear(pt_hmap);
            _print_hash_map_sample(pt_hmap);
            ((hash_sample_t*)hash_map_at(pt_hmap, 9))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmap, 9))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmap, 6))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmap, 6))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmap, 4))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmap, 4))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmap, 19))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmap, 19))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmap, 86))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmap, 86))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmap, 7))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmap, 7))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmap, 3))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmap, 3))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmap, 56))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmap, 56))->_l_second = 50;
            ((hash_sample_t*)hash_map_at(pt_hmap, 54))->_d_first = -5.11;
            ((hash_sample_t*)hash_map_at(pt_hmap, 54))->_l_second = 50;
            _print_hash_map_sample(pt_hmap);
            hash_map_clear(pt_hmap);
            _print_hash_map_sample(pt_hmap);

            hash_map_destroy(pt_hmap);
        }
    }
    /* cstl built-in type */
    {
        /*create_hash_map            */
        /*hash_map_init              */
        {
            hash_map_t* pt_hmap = create_hash_map(int, list_t<int>);
            if(pt_hmap == NULL)
            {
                return;
            }
            hash_map_init(pt_hmap);
            list_t* pt_list = (list_t*)hash_map_at(pt_hmap, 10);
            list_push_back(pt_list, 10);
            list_push_back(pt_list, 12);
            list_push_back(pt_list, 49230);
            list_push_back(pt_list, 2);
            list_push_back(pt_list, 0);
            pt_list = (list_t*)hash_map_at(pt_hmap, 45);
            list_push_back(pt_list, 234);
            list_push_back(pt_list, 111);
            pt_list = (list_t*)hash_map_at(pt_hmap, 9);
            list_push_back(pt_list, 1111);
            list_push_back(pt_list, 45);
            list_push_back(pt_list, 12345);
            list_push_back(pt_list, -83);
            list_push_back(pt_list, -3434);
            list_push_back(pt_list, 222);
            _print_hash_map_cstl(pt_hmap);
            hash_map_destroy(pt_hmap);
        }
        /*hash_map_init_ex           */
        {
            hash_map_t* pt_hmap = create_hash_map(int, list_t<int>);
            if(pt_hmap == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_cstl_hash, NULL);
            list_t* pt_list = (list_t*)hash_map_at(pt_hmap, 10);
            list_push_back(pt_list, 10);
            list_push_back(pt_list, 12);
            list_push_back(pt_list, 49230);
            list_push_back(pt_list, 2);
            list_push_back(pt_list, 0);
            pt_list = (list_t*)hash_map_at(pt_hmap, 45);
            list_push_back(pt_list, 234);
            list_push_back(pt_list, 111);
            pt_list = (list_t*)hash_map_at(pt_hmap, 9);
            list_push_back(pt_list, 1111);
            list_push_back(pt_list, 45);
            list_push_back(pt_list, 12345);
            list_push_back(pt_list, -83);
            list_push_back(pt_list, -3434);
            list_push_back(pt_list, 222);
            _print_hash_map_cstl(pt_hmap);
            hash_map_destroy(pt_hmap);
        }
        /*hash_map_init_copy         */
        {
            hash_map_t* pt_hmap = create_hash_map(int, list_t<int>);
            hash_map_t* pt_hmapex = create_hash_map(int, list_t<int>);
            list_t* pt_list = NULL;
            if(pt_hmap == NULL || pt_hmapex == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmapex, 100, _hash_map_cstl_hash, NULL);
            pt_list = (list_t*)hash_map_at(pt_hmapex, 10);
            list_push_back(pt_list, 10);
            list_push_back(pt_list, 12);
            list_push_back(pt_list, 49230);
            list_push_back(pt_list, 2);
            list_push_back(pt_list, 0);
            pt_list = (list_t*)hash_map_at(pt_hmapex, 45);
            list_push_back(pt_list, 234);
            list_push_back(pt_list, 111);
            pt_list = (list_t*)hash_map_at(pt_hmapex, 9);
            list_push_back(pt_list, 1111);
            list_push_back(pt_list, 45);
            list_push_back(pt_list, 12345);
            list_push_back(pt_list, -83);
            list_push_back(pt_list, -3434);
            list_push_back(pt_list, 222);
            hash_map_init_copy(pt_hmap, pt_hmapex);
            _print_hash_map_cstl(pt_hmap);
            hash_map_destroy(pt_hmap);
        }
        /*hash_map_init_copy_range   */
        {
            hash_map_t* pt_hmap = create_hash_map(int, list_t<int>);
            hash_map_t* pt_hmapex = create_hash_map(int, list_t<int>);
            list_t* pt_list = NULL;
            if(pt_hmap == NULL || pt_hmapex == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmapex, 100, _hash_map_cstl_hash, NULL);

            pt_list = (list_t*)hash_map_at(pt_hmapex, 10);
            list_push_back(pt_list, 10);
            list_push_back(pt_list, 12);
            list_push_back(pt_list, 49230);
            list_push_back(pt_list, 2);
            list_push_back(pt_list, 0);
            pt_list = (list_t*)hash_map_at(pt_hmapex, 45);
            list_push_back(pt_list, 234);
            list_push_back(pt_list, 111);
            pt_list = (list_t*)hash_map_at(pt_hmapex, 9);
            list_push_back(pt_list, 1111);
            list_push_back(pt_list, 45);
            list_push_back(pt_list, 12345);
            list_push_back(pt_list, -83);
            list_push_back(pt_list, -3434);
            list_push_back(pt_list, 222);
            pt_list = (list_t*)hash_map_at(pt_hmapex, 3);
            list_push_back(pt_list, 1124);
            list_push_back(pt_list, 0);
            list_push_back(pt_list, 11);
            list_push_back(pt_list, 0);
            list_push_back(pt_list, 0);
            pt_list = (list_t*)hash_map_at(pt_hmapex, 78);
            list_push_back(pt_list, 4);

            hash_map_init_copy_range(pt_hmap,
                hash_map_begin(pt_hmapex),
                hash_map_end(pt_hmapex));
            _print_hash_map_cstl(pt_hmapex);
            _print_hash_map_cstl(pt_hmap);

            hash_map_destroy(pt_hmap);
            hash_map_destroy(pt_hmapex);
        }
        /*hash_map_init_copy_range_ex*/
        {
            hash_map_t* pt_hmap = create_hash_map(int, list_t<int>);
            hash_map_t* pt_hmapex = create_hash_map(int, list_t<int>);
            list_t* pt_list = NULL;
            if(pt_hmap == NULL || pt_hmapex == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmapex, 100, _hash_map_cstl_hash, NULL);

            pt_list = (list_t*)hash_map_at(pt_hmapex, 10);
            list_push_back(pt_list, 10);
            list_push_back(pt_list, 12);
            list_push_back(pt_list, 49230);
            list_push_back(pt_list, 2);
            list_push_back(pt_list, 0);
            pt_list = (list_t*)hash_map_at(pt_hmapex, 45);
            list_push_back(pt_list, 234);
            list_push_back(pt_list, 111);
            pt_list = (list_t*)hash_map_at(pt_hmapex, 9);
            list_push_back(pt_list, 1111);
            list_push_back(pt_list, 45);
            list_push_back(pt_list, 12345);
            list_push_back(pt_list, -83);
            list_push_back(pt_list, -3434);
            list_push_back(pt_list, 222);
            pt_list = (list_t*)hash_map_at(pt_hmapex, 3);
            list_push_back(pt_list, 1124);
            list_push_back(pt_list, 0);
            list_push_back(pt_list, 11);
            list_push_back(pt_list, 0);
            list_push_back(pt_list, 0);
            pt_list = (list_t*)hash_map_at(pt_hmapex, 78);
            list_push_back(pt_list, 4);

            hash_map_init_copy_range_ex(pt_hmap,
                hash_map_begin(pt_hmapex), hash_map_end(pt_hmapex),
                0, _hash_map_cstl_hash, NULL);
            _print_hash_map_cstl(pt_hmapex);
            _print_hash_map_cstl(pt_hmap);

            hash_map_destroy(pt_hmap);
            hash_map_destroy(pt_hmapex);
        }
        /*hash_map_destroy           */
        /*hash_map_assign            */
        {
            hash_map_t* pt_hmap = create_hash_map(int, list_t<int>);
            hash_map_t* pt_hmapex = create_hash_map(int, list_t<int>);
            list_t* pt_list = NULL;
            if(pt_hmap == NULL || pt_hmapex == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_cstl_hash, NULL);
            hash_map_init_ex(pt_hmapex, 100, _hash_map_cstl_hash, NULL);
            hash_map_assign(pt_hmap, pt_hmapex);
            _print_hash_map_cstl(pt_hmap);

            pt_list = (list_t*)hash_map_at(pt_hmapex, 12);
            list_push_back(pt_list, 3234);
            list_push_back(pt_list, -876);
            list_push_back(pt_list, 4);
            pt_list = (list_t*)hash_map_at(pt_hmapex, 2);
            list_push_back(pt_list, -79);
            list_push_back(pt_list, 3);
            hash_map_assign(pt_hmap, pt_hmapex);
            _print_hash_map_cstl(pt_hmap);

            hash_map_clear(pt_hmapex);
            pt_list = (list_t*)hash_map_at(pt_hmapex, 55);
            list_push_back(pt_list, 78);
            list_push_back(pt_list, 2);
            list_push_back(pt_list, 34);
            list_push_back(pt_list, 2);
            list_push_back(pt_list, 567);
            list_push_back(pt_list, 445);
            pt_list = (list_t*)hash_map_at(pt_hmapex, 4);
            list_push_back(pt_list, 4);
            list_push_back(pt_list, 4);
            pt_list = (list_t*)hash_map_at(pt_hmapex, 22);
            pt_list = (list_t*)hash_map_at(pt_hmapex, 5);
            list_push_back(pt_list, 100);
            list_push_back(pt_list, 200);
            list_push_back(pt_list, 300);
            pt_list = (list_t*)hash_map_at(pt_hmapex, 45);
            list_push_back(pt_list, 222);
            hash_map_assign(pt_hmap, pt_hmapex);
            _print_hash_map_cstl(pt_hmap);

            hash_map_clear(pt_hmapex);
            pt_list = (list_t*)hash_map_at(pt_hmapex, 444);
            list_push_back(pt_list, 0);
            list_push_back(pt_list, 2);
            list_push_back(pt_list, 3);
            hash_map_assign(pt_hmap, pt_hmapex);
            _print_hash_map_cstl(pt_hmap);

            hash_map_clear(pt_hmapex);
            hash_map_assign(pt_hmap, pt_hmapex);
            _print_hash_map_cstl(pt_hmap);

            hash_map_destroy(pt_hmap);
            hash_map_destroy(pt_hmapex);
        }
        /*hash_map_swap              */
        {
            hash_map_t* pt_hmap = create_hash_map(int, list_t<int>);
            hash_map_t* pt_hmapex = create_hash_map(int, list_t<int>);
            list_t* pt_list = NULL;
            if(pt_hmap == NULL || pt_hmapex == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_cstl_hash, NULL);
            hash_map_init_ex(pt_hmapex, 100, _hash_map_cstl_hash, NULL);
            hash_map_swap(pt_hmap, pt_hmapex);
            _print_hash_map_cstl(pt_hmap);
            _print_hash_map_cstl(pt_hmapex);

            pt_list = (list_t*)hash_map_at(pt_hmapex, 12);
            list_push_back(pt_list, 3234);
            list_push_back(pt_list, -876);
            list_push_back(pt_list, 4);
            pt_list = (list_t*)hash_map_at(pt_hmapex, 2);
            list_push_back(pt_list, -79);
            list_push_back(pt_list, 3);
            hash_map_swap(pt_hmap, pt_hmapex);
            _print_hash_map_cstl(pt_hmap);
            _print_hash_map_cstl(pt_hmapex);

            hash_map_clear(pt_hmapex);
            pt_list = (list_t*)hash_map_at(pt_hmapex, 55);
            list_push_back(pt_list, 78);
            list_push_back(pt_list, 2);
            list_push_back(pt_list, 34);
            list_push_back(pt_list, 2);
            list_push_back(pt_list, 567);
            list_push_back(pt_list, 445);
            pt_list = (list_t*)hash_map_at(pt_hmapex, 4);
            list_push_back(pt_list, 4);
            list_push_back(pt_list, 4);
            pt_list = (list_t*)hash_map_at(pt_hmapex, 22);
            pt_list = (list_t*)hash_map_at(pt_hmapex, 5);
            list_push_back(pt_list, 100);
            list_push_back(pt_list, 200);
            list_push_back(pt_list, 300);
            pt_list = (list_t*)hash_map_at(pt_hmapex, 45);
            list_push_back(pt_list, 222);
            hash_map_swap(pt_hmap, pt_hmapex);
            _print_hash_map_cstl(pt_hmap);
            _print_hash_map_cstl(pt_hmapex);

            hash_map_clear(pt_hmapex);
            pt_list = (list_t*)hash_map_at(pt_hmapex, 444);
            list_push_back(pt_list, 0);
            list_push_back(pt_list, 2);
            list_push_back(pt_list, 3);
            hash_map_swap(pt_hmap, pt_hmapex);
            _print_hash_map_cstl(pt_hmap);
            _print_hash_map_cstl(pt_hmapex);

            hash_map_clear(pt_hmapex);
            hash_map_swap(pt_hmap, pt_hmapex);
            _print_hash_map_cstl(pt_hmap);
            _print_hash_map_cstl(pt_hmapex);

            hash_map_destroy(pt_hmap);
            hash_map_destroy(pt_hmapex);
        }
        /*hash_map_size              */
        /*hash_map_empty             */
        /*hash_map_max_size          */
        /*hash_map_bucket_count      */
        /*hash_map_hash              */
        /*hash_map_key_less          */
        {
            hash_map_t* pt_hmap = create_hash_map(int, list_t<int>);
            if(pt_hmap == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 100, _hash_map_cstl_hash, fun_great_int);
            assert(hash_map_hash(pt_hmap) == _hash_map_cstl_hash &&
                hash_map_key_less(pt_hmap) == fun_great_int);
            hash_map_destroy(pt_hmap);
        }
        /*hash_map_resize            */
        {
            hash_map_t* pt_hmap = create_hash_map(int, list_t<int>);
            if(pt_hmap == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_cstl_hash, NULL);
            _print_hash_map_cstl(pt_hmap);
            hash_map_resize(pt_hmap, 50);
            _print_hash_map_cstl(pt_hmap);
            hash_map_resize(pt_hmap, 100);
            _print_hash_map_cstl(pt_hmap);
            hash_map_resize(pt_hmap, 700);
            _print_hash_map_cstl(pt_hmap);
            hash_map_resize(pt_hmap, 30);
            _print_hash_map_cstl(pt_hmap);
            hash_map_resize(pt_hmap, 0);
            _print_hash_map_cstl(pt_hmap);
            hash_map_destroy(pt_hmap);
        }
        /*hash_map_equal             */
        /*hash_map_not_equal         */
        /*hash_map_less              */
        /*hash_map_less_equal        */
        /*hash_map_great             */
        /*hash_map_great_equal       */
        {
            hash_map_t* pt_hmap = create_hash_map(int, list_t<int>);
            hash_map_t* pt_hmapex = create_hash_map(int, list_t<int>);
            list_t* pt_list = NULL;
            if(pt_hmap == NULL || pt_hmapex == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_cstl_hash, NULL);
            hash_map_init_ex(pt_hmapex, 0, _hash_map_cstl_hash, NULL);
            _print_hash_map_cstl(pt_hmap);
            _print_hash_map_cstl(pt_hmapex);
            printf("equal: %d, not equal: %d, ",
                hash_map_equal(pt_hmap, pt_hmapex), hash_map_not_equal(pt_hmap, pt_hmapex));
            printf("less: %d, less equal: %d, ",
                hash_map_less(pt_hmap, pt_hmapex), hash_map_less_equal(pt_hmap, pt_hmapex));
            printf("great: %d, great equal: %d\n",
                hash_map_great(pt_hmap, pt_hmapex), hash_map_great_equal(pt_hmap, pt_hmapex));

            pt_list = (list_t*)hash_map_at(pt_hmap, 34);
            list_push_back(pt_list, 56);
            list_push_back(pt_list, 11);
            list_push_back(pt_list, 90);
            _print_hash_map_cstl(pt_hmap);
            _print_hash_map_cstl(pt_hmapex);
            printf("equal: %d, not equal: %d, ",
                hash_map_equal(pt_hmap, pt_hmapex), hash_map_not_equal(pt_hmap, pt_hmapex));
            printf("less: %d, less equal: %d, ",
                hash_map_less(pt_hmap, pt_hmapex), hash_map_less_equal(pt_hmap, pt_hmapex));
            printf("great: %d, great equal: %d\n",
                hash_map_great(pt_hmap, pt_hmapex), hash_map_great_equal(pt_hmap, pt_hmapex));

            pt_list = (list_t*)hash_map_at(pt_hmapex, 34);
            list_push_back(pt_list, 56);
            list_push_back(pt_list, 11);
            list_push_back(pt_list, 90);
            _print_hash_map_cstl(pt_hmap);
            _print_hash_map_cstl(pt_hmapex);
            printf("equal: %d, not equal: %d, ",
                hash_map_equal(pt_hmap, pt_hmapex), hash_map_not_equal(pt_hmap, pt_hmapex));
            printf("less: %d, less equal: %d, ",
                hash_map_less(pt_hmap, pt_hmapex), hash_map_less_equal(pt_hmap, pt_hmapex));
            printf("great: %d, great equal: %d\n",
                hash_map_great(pt_hmap, pt_hmapex), hash_map_great_equal(pt_hmap, pt_hmapex));

            pt_list = (list_t*)hash_map_at(pt_hmap, 20);
            pt_list = (list_t*)hash_map_at(pt_hmap, 10);
            list_push_back(pt_list, 232);
            list_push_back(pt_list, 4455);
            list_push_back(pt_list, 8989);
            pt_list = (list_t*)hash_map_at(pt_hmapex, 50);
            list_push_back(pt_list, 0);
            list_push_back(pt_list, 0);
            _print_hash_map_cstl(pt_hmap);
            _print_hash_map_cstl(pt_hmapex);
            printf("equal: %d, not equal: %d, ",
                hash_map_equal(pt_hmap, pt_hmapex), hash_map_not_equal(pt_hmap, pt_hmapex));
            printf("less: %d, less equal: %d, ",
                hash_map_less(pt_hmap, pt_hmapex), hash_map_less_equal(pt_hmap, pt_hmapex));
            printf("great: %d, great equal: %d\n",
                hash_map_great(pt_hmap, pt_hmapex), hash_map_great_equal(pt_hmap, pt_hmapex));

            hash_map_destroy(pt_hmap);
            hash_map_destroy(pt_hmapex);
        }
        /*hash_map_begin             */
        /*hash_map_end               */
        /*hash_map_find              */
        /*hash_map_count             */
        {
            hash_map_t* pt_hmap = create_hash_map(int, list_t<int>);
            list_t* pt_list = NULL;
            iterator_t t_iter;
            if(pt_hmap == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_cstl_hash, NULL);

            t_iter = hash_map_find(pt_hmap, 0);
            if(iterator_equal(t_iter, hash_map_end(pt_hmap)))
            {
                printf("not found! count : %u\n", hash_map_count(pt_hmap, 0));
            }
            else
            {
                printf("found! count : %u\n", hash_map_count(pt_hmap, 0));
            }
            pt_list = (list_t*)hash_map_at(pt_hmap, 4);
            list_push_back(pt_list, 3);
            list_push_back(pt_list, 0);
            list_push_back(pt_list, 112);
            list_push_back(pt_list, 909);
            pt_list = (list_t*)hash_map_at(pt_hmap, 23);
            list_push_back(pt_list, 122);
            list_push_back(pt_list, 89);
            list_push_back(pt_list, 0);
            pt_list = (list_t*)hash_map_at(pt_hmap, 2);
            list_push_back(pt_list, 9);

            t_iter = hash_map_find(pt_hmap, 0);
            if(iterator_equal(t_iter, hash_map_end(pt_hmap)))
            {
                printf("not found! count : %u\n", hash_map_count(pt_hmap, 0));
            }
            else
            {
                printf("found! count : %u\n", hash_map_count(pt_hmap, 0));
            }
            t_iter = hash_map_find(pt_hmap, 4);
            if(iterator_equal(t_iter, hash_map_end(pt_hmap)))
            {
                printf("not found! count : %u\n", hash_map_count(pt_hmap, 4));
            }
            else
            {
                printf("found! count : %u\n", hash_map_count(pt_hmap, 4));
            }

            hash_map_destroy(pt_hmap);
        }
        /*hash_map_equal_range       */
        {
            hash_map_t* pt_hmap = create_hash_map(int, list_t<int>);
            list_t* pt_list = NULL;
            range_t t_range;
            if(pt_hmap == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_cstl_hash, NULL);
            t_range = hash_map_equal_range(pt_hmap, 4);
            assert(iterator_equal(t_range.t_begin, hash_map_end(pt_hmap)) &&
                iterator_equal(t_range.t_begin, t_range.t_end));
            pt_list = (list_t*)hash_map_at(pt_hmap, 4);
            list_push_back(pt_list, 232);
            list_push_back(pt_list, 0);
            list_push_back(pt_list, 4);
            pt_list = (list_t*)hash_map_at(pt_hmap, 23);
            list_push_back(pt_list, 23);
            pt_list = (list_t*)hash_map_at(pt_hmap, 4);
            list_push_front(pt_list, 222);
            list_push_front(pt_list, 0);
            pt_list = (list_t*)hash_map_at(pt_hmap, 5);
            list_push_front(pt_list, 28);
            t_range = hash_map_equal_range(pt_hmap, 10);
            assert(iterator_equal(t_range.t_begin, t_range.t_end));
            t_range = hash_map_equal_range(pt_hmap, 5);
            assert(iterator_equal(iterator_next(t_range.t_begin), t_range.t_end));
            hash_map_destroy(pt_hmap);
        }
        /*hash_map_at                */
        {
            hash_map_t* pt_hmap = create_hash_map(int, list_t<int>);
            list_t* pt_list = NULL;
            if(pt_hmap == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_cstl_hash, NULL);

            pt_list = (list_t*)hash_map_at(pt_hmap, 45);
            list_push_front(pt_list, 45);
            list_push_front(pt_list, 45);
            pt_list = (list_t*)hash_map_at(pt_hmap, 22);
            list_push_back(pt_list, 899);
            list_push_back(pt_list, 34);
            _print_hash_map_cstl(pt_hmap);

            pt_list = (list_t*)hash_map_at(pt_hmap, 10);
            pt_list = (list_t*)hash_map_at(pt_hmap, 22);
            list_push_back(pt_list, 100);
            list_push_back(pt_list, 200);
            _print_hash_map_cstl(pt_hmap);

            hash_map_destroy(pt_hmap);
        }
        /*hash_map_insert            */
        {
            hash_map_t* pt_hmap = create_hash_map(int, list_t<int>);
            pair_t* pt_pair = create_pair(int, list_t<int>);
            list_t* pt_list = create_list(int);
            if(pt_hmap == NULL || pt_pair == NULL || pt_list == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_cstl_hash, NULL);
            pair_init(pt_pair);
            list_init(pt_list);

            _print_hash_map_cstl(pt_hmap);
            list_push_back(pt_list, 100);
            list_push_back(pt_list, 400);
            list_push_back(pt_list, 200);
            pair_make(pt_pair, 23, pt_list);
            hash_map_insert(pt_hmap, pt_pair);
            list_clear(pt_list);
            list_push_back(pt_list, -990);
            list_push_back(pt_list, 23445);
            pair_make(pt_pair, 45, pt_list);
            hash_map_insert(pt_hmap, pt_pair);
            list_push_front(pt_list, 7);
            list_push_front(pt_list, 34);
            pair_make(pt_pair, 4, pt_list);
            hash_map_insert(pt_hmap, pt_pair);
            list_clear(pt_list);
            pair_make(pt_pair, 5, pt_list);
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, 23, pt_list);
            hash_map_insert(pt_hmap, pt_pair);
            _print_hash_map_cstl(pt_hmap);

            hash_map_destroy(pt_hmap);
            pair_destroy(pt_pair);
            list_destroy(pt_list);
        }
        /*hash_map_insert_range      */
        {
            hash_map_t* pt_hmap = create_hash_map(int, list_t<int>);
            hash_map_t* pt_hmapex = create_hash_map(int, list_t<int>);
            list_t* pt_list = NULL;
            if(pt_hmap == NULL || pt_hmapex == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_cstl_hash, NULL);
            hash_map_init_ex(pt_hmapex, 0, _hash_map_cstl_hash, NULL);

            hash_map_insert_range(pt_hmap, hash_map_begin(pt_hmapex), hash_map_end(pt_hmapex));
            _print_hash_map_cstl(pt_hmap);

            pt_list = (list_t*)hash_map_at(pt_hmapex, 34);
            list_push_front(pt_list, 45);
            list_push_front(pt_list, 45);
            pt_list = (list_t*)hash_map_at(pt_hmapex, 2);
            list_push_front(pt_list, 5678);
            pt_list = (list_t*)hash_map_at(pt_hmapex, 0);
            list_push_front(pt_list, 4);
            list_push_front(pt_list, 20);
            list_push_front(pt_list, 56);
            list_push_front(pt_list, 7);
            pt_list = (list_t*)hash_map_at(pt_hmapex, 56);
            list_push_back(pt_list, 4);
            list_push_back(pt_list, 89);
            pt_list = (list_t*)hash_map_at(pt_hmapex, 3445);
            pt_list = (list_t*)hash_map_at(pt_hmapex, 5);
            list_push_back(pt_list, 567);
            pt_list = (list_t*)hash_map_at(pt_hmapex, 43);
            pt_list = (list_t*)hash_map_at(pt_hmapex, 1);
            pt_list = (list_t*)hash_map_at(pt_hmapex, 456);
            pt_list = (list_t*)hash_map_at(pt_hmapex, 90);
            pt_list = (list_t*)hash_map_at(pt_hmapex, 56);
            _print_hash_map_cstl(pt_hmapex);

            hash_map_insert_range(pt_hmap,
                hash_map_begin(pt_hmapex), hash_map_begin(pt_hmapex));
            _print_hash_map_cstl(pt_hmap);
            hash_map_insert_range(pt_hmap,
                hash_map_begin(pt_hmapex), iterator_advance(hash_map_begin(pt_hmapex), 3));
            _print_hash_map_cstl(pt_hmap);
            hash_map_insert_range(pt_hmap,
                iterator_advance(hash_map_begin(pt_hmapex), 5),
                iterator_advance(hash_map_begin(pt_hmapex), 7));
            _print_hash_map_cstl(pt_hmap);
            hash_map_insert_range(pt_hmap,
                iterator_advance(hash_map_begin(pt_hmapex), 9),
                hash_map_end(pt_hmapex));
            _print_hash_map_cstl(pt_hmap);
            hash_map_insert_range(pt_hmap,
                hash_map_end(pt_hmapex), hash_map_end(pt_hmapex));
            _print_hash_map_cstl(pt_hmap);
            hash_map_clear(pt_hmap);
            hash_map_insert_range(pt_hmap,
                hash_map_begin(pt_hmapex), hash_map_end(pt_hmapex));
            _print_hash_map_cstl(pt_hmap);

            hash_map_destroy(pt_hmap);
            hash_map_destroy(pt_hmapex);
        }
        /*hash_map_erase             */
        {
            hash_map_t* pt_hmap = create_hash_map(int, list_t<int>);
            list_t* pt_list = NULL;
            if(pt_hmap == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_cstl_hash, NULL);

            hash_map_erase(pt_hmap, 44);
            _print_hash_map_cstl(pt_hmap);

            pt_list = (list_t*)hash_map_at(pt_hmap, 34);
            list_push_front(pt_list, 45);
            list_push_front(pt_list, 45);
            pt_list = (list_t*)hash_map_at(pt_hmap, 2);
            list_push_front(pt_list, 5678);
            pt_list = (list_t*)hash_map_at(pt_hmap, 0);
            list_push_front(pt_list, 4);
            list_push_front(pt_list, 20);
            list_push_front(pt_list, 56);
            list_push_front(pt_list, 7);
            pt_list = (list_t*)hash_map_at(pt_hmap, 56);
            list_push_back(pt_list, 4);
            list_push_back(pt_list, 89);
            pt_list = (list_t*)hash_map_at(pt_hmap, 3445);
            pt_list = (list_t*)hash_map_at(pt_hmap, 5);
            list_push_back(pt_list, 567);
            pt_list = (list_t*)hash_map_at(pt_hmap, 43);
            pt_list = (list_t*)hash_map_at(pt_hmap, 1);
            pt_list = (list_t*)hash_map_at(pt_hmap, 456);
            pt_list = (list_t*)hash_map_at(pt_hmap, 90);
            pt_list = (list_t*)hash_map_at(pt_hmap, 56);
            _print_hash_map_cstl(pt_hmap);

            hash_map_erase(pt_hmap, 44);
            _print_hash_map_cstl(pt_hmap);
            hash_map_erase(pt_hmap, 56);
            _print_hash_map_cstl(pt_hmap);

            hash_map_destroy(pt_hmap);
        }
        /*hash_map_erase_pos         */
        {
            hash_map_t* pt_hmap = create_hash_map(int, list_t<int>);
            list_t* pt_list = NULL;
            if(pt_hmap == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_cstl_hash, NULL);

            pt_list = (list_t*)hash_map_at(pt_hmap, 34);
            list_push_front(pt_list, 45);
            list_push_front(pt_list, 45);
            pt_list = (list_t*)hash_map_at(pt_hmap, 2);
            list_push_front(pt_list, 5678);
            pt_list = (list_t*)hash_map_at(pt_hmap, 0);
            list_push_front(pt_list, 4);
            list_push_front(pt_list, 20);
            list_push_front(pt_list, 56);
            list_push_front(pt_list, 7);
            pt_list = (list_t*)hash_map_at(pt_hmap, 56);
            list_push_back(pt_list, 4);
            list_push_back(pt_list, 89);
            pt_list = (list_t*)hash_map_at(pt_hmap, 3445);
            pt_list = (list_t*)hash_map_at(pt_hmap, 5);
            list_push_back(pt_list, 567);
            pt_list = (list_t*)hash_map_at(pt_hmap, 43);
            pt_list = (list_t*)hash_map_at(pt_hmap, 1);
            pt_list = (list_t*)hash_map_at(pt_hmap, 456);
            pt_list = (list_t*)hash_map_at(pt_hmap, 90);
            pt_list = (list_t*)hash_map_at(pt_hmap, 56);
            _print_hash_map_cstl(pt_hmap);

            hash_map_erase_pos(pt_hmap, hash_map_begin(pt_hmap));
            _print_hash_map_cstl(pt_hmap);
            hash_map_erase_pos(pt_hmap, iterator_advance(hash_map_begin(pt_hmap), 3));
            _print_hash_map_cstl(pt_hmap);
            while(!hash_map_empty(pt_hmap))
            {
                hash_map_erase_pos(pt_hmap, hash_map_begin(pt_hmap));
            }
            _print_hash_map_cstl(pt_hmap);

            hash_map_destroy(pt_hmap);
        }
        /*hash_map_erase_range       */
        {
            hash_map_t* pt_hmap = create_hash_map(int, list_t<int>);
            list_t* pt_list = NULL;
            if(pt_hmap == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_cstl_hash, NULL);

            hash_map_erase_range(pt_hmap, hash_map_begin(pt_hmap), hash_map_end(pt_hmap));
            _print_hash_map_cstl(pt_hmap);

            pt_list = (list_t*)hash_map_at(pt_hmap, 34);
            list_push_front(pt_list, 45);
            list_push_front(pt_list, 45);
            pt_list = (list_t*)hash_map_at(pt_hmap, 2);
            list_push_front(pt_list, 5678);
            pt_list = (list_t*)hash_map_at(pt_hmap, 0);
            list_push_front(pt_list, 4);
            list_push_front(pt_list, 20);
            list_push_front(pt_list, 56);
            list_push_front(pt_list, 7);
            pt_list = (list_t*)hash_map_at(pt_hmap, 56);
            list_push_back(pt_list, 4);
            list_push_back(pt_list, 89);
            pt_list = (list_t*)hash_map_at(pt_hmap, 3445);
            pt_list = (list_t*)hash_map_at(pt_hmap, 5);
            list_push_back(pt_list, 567);
            pt_list = (list_t*)hash_map_at(pt_hmap, 43);
            pt_list = (list_t*)hash_map_at(pt_hmap, 1);
            pt_list = (list_t*)hash_map_at(pt_hmap, 456);
            pt_list = (list_t*)hash_map_at(pt_hmap, 90);
            pt_list = (list_t*)hash_map_at(pt_hmap, 56);
            _print_hash_map_cstl(pt_hmap);

            hash_map_erase_range(pt_hmap,
                hash_map_begin(pt_hmap), hash_map_begin(pt_hmap));
            _print_hash_map_cstl(pt_hmap);
            hash_map_erase_range(pt_hmap,
                hash_map_begin(pt_hmap), iterator_advance(hash_map_begin(pt_hmap), 3));
            _print_hash_map_cstl(pt_hmap);
            hash_map_erase_range(pt_hmap,
                iterator_advance(hash_map_begin(pt_hmap), 2),
                iterator_advance(hash_map_begin(pt_hmap), 4));
            _print_hash_map_cstl(pt_hmap);
            hash_map_erase_range(pt_hmap,
                iterator_advance(hash_map_begin(pt_hmap), 3),
                hash_map_end(pt_hmap));
            _print_hash_map_cstl(pt_hmap);
            hash_map_erase_range(pt_hmap,
                hash_map_end(pt_hmap), hash_map_end(pt_hmap));
            _print_hash_map_cstl(pt_hmap);
            hash_map_erase_range(pt_hmap,
                hash_map_begin(pt_hmap), hash_map_end(pt_hmap));
            _print_hash_map_cstl(pt_hmap);

            hash_map_destroy(pt_hmap);
        }
        /*hash_map_clear             */
        {
            hash_map_t* pt_hmap = create_hash_map(int, list_t<int>);
            list_t* pt_list = NULL;
            if(pt_hmap == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_cstl_hash, NULL);

            hash_map_clear(pt_hmap);
            _print_hash_map_cstl(pt_hmap);

            pt_list = (list_t*)hash_map_at(pt_hmap, 34);
            list_push_front(pt_list, 45);
            list_push_front(pt_list, 45);
            pt_list = (list_t*)hash_map_at(pt_hmap, 2);
            list_push_front(pt_list, 5678);
            pt_list = (list_t*)hash_map_at(pt_hmap, 0);
            list_push_front(pt_list, 4);
            list_push_front(pt_list, 20);
            list_push_front(pt_list, 56);
            list_push_front(pt_list, 7);
            pt_list = (list_t*)hash_map_at(pt_hmap, 56);
            list_push_back(pt_list, 4);
            list_push_back(pt_list, 89);
            pt_list = (list_t*)hash_map_at(pt_hmap, 3445);
            pt_list = (list_t*)hash_map_at(pt_hmap, 5);
            list_push_back(pt_list, 567);
            pt_list = (list_t*)hash_map_at(pt_hmap, 43);
            pt_list = (list_t*)hash_map_at(pt_hmap, 1);
            pt_list = (list_t*)hash_map_at(pt_hmap, 456);
            pt_list = (list_t*)hash_map_at(pt_hmap, 90);
            pt_list = (list_t*)hash_map_at(pt_hmap, 56);
            _print_hash_map_cstl(pt_hmap);

            hash_map_clear(pt_hmap);
            _print_hash_map_cstl(pt_hmap);

            hash_map_destroy(pt_hmap);
        }
    }
    /* c-string type */
    {
        /*create_hash_map            */
        /*hash_map_init              */
        {
            hash_map_t* pt_hmap = create_hash_map(char*, char*);
            if(pt_hmap == NULL)
            {
                return;
            }
            hash_map_init(pt_hmap);
            hash_map_at(pt_hmap, "abcdefg");
            hash_map_at(pt_hmap, "a");
            hash_map_at(pt_hmap, "a");
            hash_map_at(pt_hmap, "7");
            hash_map_at(pt_hmap, "88");
            hash_map_at(pt_hmap, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
            _print_hash_map_cstr(pt_hmap);
            hash_map_destroy(pt_hmap);
        }
        /*hash_map_init_ex           */
        {
            hash_map_t* pt_hmap = create_hash_map(char*, char*);
            if(pt_hmap == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_cstr_hash, _hash_map_cstr_less);
            hash_map_at(pt_hmap, "abcdefg");
            hash_map_at(pt_hmap, "a");
            hash_map_at(pt_hmap, "a");
            hash_map_at(pt_hmap, "7");
            hash_map_at(pt_hmap, "88");
            hash_map_at(pt_hmap, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ012");
            _print_hash_map_cstr(pt_hmap);
            hash_map_destroy(pt_hmap);
        }
        /*hash_map_init_copy         */
        {
            hash_map_t* pt_hmap = create_hash_map(char*, char*);
            hash_map_t* pt_hmapex = create_hash_map(char*,char*);
            pair_t* pt_pair = create_pair(char*, char*);
            if(pt_hmap == NULL || pt_hmapex == NULL || pt_pair == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            hash_map_init_ex(pt_hmapex, 100, _hash_map_cstr_hash, NULL);

            pair_make(pt_pair, "8woobw", "WTO");
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, "b", "BB");
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, "VVV", "VVV");
            hash_map_insert(pt_hmapex, pt_pair);

            hash_map_init_copy(pt_hmap, pt_hmapex);
            _print_hash_map_cstr(pt_hmap);
            hash_map_destroy(pt_hmap);
            hash_map_destroy(pt_hmapex);
            pair_destroy(pt_pair);
        }
        /*hash_map_init_copy_range   */
        {
            hash_map_t* pt_hmap = create_hash_map(char*, char*);
            hash_map_t* pt_hmapex = create_hash_map(char*, char*);
            pair_t* pt_pair = create_pair(char*, char*);
            if(pt_hmap == NULL || pt_hmapex == NULL || pt_pair == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            hash_map_init_ex(pt_hmapex, 100, _hash_map_cstr_hash, NULL);

            pair_make(pt_pair, "qqb", "qqq");
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, "uuu", "lakdfadfiasd;flkja");
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, "tqwobqwepoqehawlaskfqweoppqweif", "l");
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, "laksslsllls", "ool");
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, "llllllllllllllll", "akldf");
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, "1111", "zai guo qu de yi nian li");
            hash_map_insert(pt_hmapex, pt_pair);

            _print_hash_map_cstr(pt_hmapex);
            hash_map_init_copy_range(pt_hmap,
                hash_map_begin(pt_hmapex), hash_map_end(pt_hmapex));
            _print_hash_map_cstr(pt_hmap);
            hash_map_destroy(pt_hmap);
            hash_map_destroy(pt_hmapex);
            pair_destroy(pt_pair);
        }
        /*hash_map_init_copy_range_ex*/
        {
            hash_map_t* pt_hmap = create_hash_map(char*, char*);
            hash_map_t* pt_hmapex = create_hash_map(char*, char*);
            pair_t* pt_pair = create_pair(char*, char*);
            if(pt_hmap == NULL || pt_hmapex == NULL || pt_pair == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            hash_map_init(pt_hmapex);

            pair_make(pt_pair, "qqb", "qqq");
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, "uuu", "lakdfadfiasd;flkja");
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, "tqwobqwepoqehawlaskfqweoppqweif", "l");
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, "laksslsllls", "ool");
            hash_map_insert(pt_hmapex, pt_pair);
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, "llllllllllllllll", "akldf");
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, "1111", "zai guo qu de yi nian li");
            hash_map_insert(pt_hmapex, pt_pair);
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, "hhh", "lskflskjflaskdfj");
            hash_map_insert(pt_hmapex, pt_pair);

            _print_hash_map_cstr(pt_hmapex);
            hash_map_init_copy_range_ex(pt_hmap,
                hash_map_begin(pt_hmapex), hash_map_end(pt_hmapex),
                100, _hash_map_cstr_hash, NULL);
            _print_hash_map_cstr(pt_hmap);
            hash_map_destroy(pt_hmap);
            hash_map_destroy(pt_hmapex);
            pair_destroy(pt_pair);
        }
        /*hash_map_destroy           */
        /*hash_map_assign            */
        {
            hash_map_t* pt_hmap = create_hash_map(char*, char*);
            hash_map_t* pt_hmapex = create_hash_map(char*, char*);
            pair_t* pt_pair = create_pair(char*, char*);
            if(pt_hmap == NULL || pt_hmapex == NULL || pt_pair == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_cstr_hash, NULL);
            hash_map_init_ex(pt_hmapex, 0, _hash_map_cstr_hash, NULL);
            pair_init(pt_pair);

            hash_map_assign(pt_hmap, pt_hmapex);
            _print_hash_map_cstr(pt_hmap);

            pair_make(pt_pair, "uuuuu", "httpd");
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, "ladjkfoweijf", "al;kdfjoqwiejf");
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, "bnbnbnb", "bnbnbnbn");
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, "||||||||++++", "23948720349(*%&^%*(&)(*)_(*&%&$E");
            hash_map_insert(pt_hmapex, pt_pair);
            hash_map_assign(pt_hmap, pt_hmapex);
            _print_hash_map_cstr(pt_hmap);

            hash_map_clear(pt_hmapex);
            pair_make(pt_pair, "pair", "hash_map");
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, "**&&^%^&*((&^^%%", "hhh");
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, "uasdhfo", "alsllsls");
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, "1111", "222222222");
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, "88888888", "034950234950234");
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, "", "");
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, "huadl", ":a;lsdkf");
            hash_map_insert(pt_hmapex, pt_pair);
            hash_map_assign(pt_hmap, pt_hmapex);
            _print_hash_map_cstr(pt_hmap);

            hash_map_clear(pt_hmapex);
            pair_make(pt_pair, "first", "1st");
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, "nine", "9");
            hash_map_insert(pt_hmapex, pt_pair);
            hash_map_assign(pt_hmap, pt_hmapex);
            _print_hash_map_cstr(pt_hmap);

            hash_map_clear(pt_hmapex);
            hash_map_assign(pt_hmap, pt_hmapex);
            _print_hash_map_cstr(pt_hmap);

            hash_map_destroy(pt_hmap);
            hash_map_destroy(pt_hmapex);
            pair_destroy(pt_pair);
        }
        /*hash_map_swap              */
        {
            hash_map_t* pt_hmap = create_hash_map(char*, char*);
            hash_map_t* pt_hmapex = create_hash_map(char*, char*);
            pair_t* pt_pair = create_pair(char*, char*);
            if(pt_hmap == NULL || pt_hmapex == NULL || pt_pair == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_cstr_hash, NULL);
            hash_map_init_ex(pt_hmapex, 0, _hash_map_cstr_hash, NULL);
            pair_init(pt_pair);

            hash_map_swap(pt_hmap, pt_hmapex);
            _print_hash_map_cstr(pt_hmap);
            _print_hash_map_cstr(pt_hmapex);

            pair_make(pt_pair, "uuuuu", "httpd");
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, "ladjkfoweijf", "al;kdfjoqwiejf");
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, "bnbnbnb", "bnbnbnbn");
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, "||||||||++++", "23948720349(*%&^%*(&)(*)_(*&%&$E");
            hash_map_insert(pt_hmapex, pt_pair);
            hash_map_swap(pt_hmap, pt_hmapex);
            _print_hash_map_cstr(pt_hmap);
            _print_hash_map_cstr(pt_hmapex);

            hash_map_clear(pt_hmapex);
            pair_make(pt_pair, "pair", "hash_map");
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, "**&&^%^&*((&^^%%", "hhh");
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, "uasdhfo", "alsllsls");
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, "1111", "222222222");
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, "88888888", "034950234950234");
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, "", "");
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, "huadl", ":a;lsdkf");
            hash_map_insert(pt_hmapex, pt_pair);
            hash_map_swap(pt_hmap, pt_hmapex);
            _print_hash_map_cstr(pt_hmap);
            _print_hash_map_cstr(pt_hmapex);

            hash_map_clear(pt_hmapex);
            pair_make(pt_pair, "first", "1st");
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, "nine", "9");
            hash_map_insert(pt_hmapex, pt_pair);
            hash_map_swap(pt_hmap, pt_hmapex);
            _print_hash_map_cstr(pt_hmap);
            _print_hash_map_cstr(pt_hmapex);

            hash_map_clear(pt_hmapex);
            hash_map_swap(pt_hmap, pt_hmapex);
            _print_hash_map_cstr(pt_hmap);
            _print_hash_map_cstr(pt_hmapex);

            hash_map_destroy(pt_hmap);
            hash_map_destroy(pt_hmapex);
            pair_destroy(pt_pair);
        }
        /*hash_map_size              */
        /*hash_map_empty             */
        /*hash_map_max_size          */
        /*hash_map_bucket_count      */
        /*hash_map_hash              */
        /*hash_map_key_less          */
        {
            hash_map_t* pt_hmap = create_hash_map(char*, char*);
            if(pt_hmap == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_cstr_hash, _hash_map_cstr_less);
            assert(hash_map_hash(pt_hmap) == _hash_map_cstr_hash &&
                hash_map_key_less(pt_hmap) == _hash_map_cstr_less);
            hash_map_destroy(pt_hmap);
        }
        /*hash_map_resize            */
        {
            hash_map_t* pt_hmap = create_hash_map(char*, char*);
            if(pt_hmap == NULL)
            {
                return;
            }
            hash_map_init(pt_hmap);
            _print_hash_map_cstr(pt_hmap);
            hash_map_resize(pt_hmap, 40);
            _print_hash_map_cstr(pt_hmap);
            hash_map_resize(pt_hmap, 90);
            _print_hash_map_cstr(pt_hmap);
            hash_map_resize(pt_hmap, 900);
            _print_hash_map_cstr(pt_hmap);
            hash_map_resize(pt_hmap, 44);
            _print_hash_map_cstr(pt_hmap);
            hash_map_resize(pt_hmap, 0);
            _print_hash_map_cstr(pt_hmap);
            hash_map_destroy(pt_hmap);
        }
        /*hash_map_equal             */
        /*hash_map_not_equal         */
        /*hash_map_less              */
        /*hash_map_less_equal        */
        /*hash_map_great             */
        /*hash_map_great_equal       */
        {
            hash_map_t* pt_hmap = create_hash_map(char*, char*);
            hash_map_t* pt_hmapex = create_hash_map(char*, char*);
            pair_t* pt_pair = create_pair(char*, char*);
            if(pt_hmap == NULL || pt_hmapex == NULL || pt_pair == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_cstr_hash, _hash_map_cstr_less);
            hash_map_init_ex(pt_hmapex, 0, _hash_map_cstr_hash, _hash_map_cstr_less);
            pair_init(pt_pair);

            _print_hash_map_cstr(pt_hmap);
            _print_hash_map_cstr(pt_hmapex);            
            printf("equal: %d, not equal: %d, ",
                hash_map_equal(pt_hmap, pt_hmapex), hash_map_not_equal(pt_hmap, pt_hmapex));
            printf("less: %d, less equal: %d, ",
                hash_map_less(pt_hmap, pt_hmapex), hash_map_less_equal(pt_hmap, pt_hmapex));
            printf("great: %d, great equal: %d\n",
                hash_map_great(pt_hmap, pt_hmapex), hash_map_great_equal(pt_hmap, pt_hmapex));

            pair_make(pt_pair, "bowsg", "alsdkfjoawhaosdfloasdkjflkasjdf");
            hash_map_insert(pt_hmap, pt_pair);
            _print_hash_map_cstr(pt_hmap);
            _print_hash_map_cstr(pt_hmapex);            
            printf("equal: %d, not equal: %d, ",
                hash_map_equal(pt_hmap, pt_hmapex), hash_map_not_equal(pt_hmap, pt_hmapex));
            printf("less: %d, less equal: %d, ",
                hash_map_less(pt_hmap, pt_hmapex), hash_map_less_equal(pt_hmap, pt_hmapex));
            printf("great: %d, great equal: %d\n",
                hash_map_great(pt_hmap, pt_hmapex), hash_map_great_equal(pt_hmap, pt_hmapex));

            hash_map_insert(pt_hmapex, pt_pair);
            _print_hash_map_cstr(pt_hmap);
            _print_hash_map_cstr(pt_hmapex);            
            printf("equal: %d, not equal: %d, ",
                hash_map_equal(pt_hmap, pt_hmapex), hash_map_not_equal(pt_hmap, pt_hmapex));
            printf("less: %d, less equal: %d, ",
                hash_map_less(pt_hmap, pt_hmapex), hash_map_less_equal(pt_hmap, pt_hmapex));
            printf("great: %d, great equal: %d\n",
                hash_map_great(pt_hmap, pt_hmapex), hash_map_great_equal(pt_hmap, pt_hmapex));

            pair_make(pt_pair, "7394934347", "sghsdfjkasdfjksdfjkl;asdfjkl;");
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, "ls", "lsl -lhp");
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, "nxcvnnmz,zn,xcznzlajha;djkfas", "");
            hash_map_insert(pt_hmapex, pt_pair);
            _print_hash_map_cstr(pt_hmap);
            _print_hash_map_cstr(pt_hmapex);            
            printf("equal: %d, not equal: %d, ",
                hash_map_equal(pt_hmap, pt_hmapex), hash_map_not_equal(pt_hmap, pt_hmapex));
            printf("less: %d, less equal: %d, ",
                hash_map_less(pt_hmap, pt_hmapex), hash_map_less_equal(pt_hmap, pt_hmapex));
            printf("great: %d, great equal: %d\n",
                hash_map_great(pt_hmap, pt_hmapex), hash_map_great_equal(pt_hmap, pt_hmapex));

            hash_map_destroy(pt_hmap);
            hash_map_destroy(pt_hmapex);
            pair_destroy(pt_pair);
        }
        /*hash_map_begin             */
        /*hash_map_end               */
        /*hash_map_find              */
        /*hash_map_count             */
        {
            hash_map_t* pt_hmap = create_hash_map(char*, char*);
            pair_t* pt_pair = create_pair(char*, char*);
            iterator_t t_iter;
            if(pt_hmap == NULL || pt_pair == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            hash_map_init_ex(pt_hmap, 0, _hash_map_cstr_hash, NULL);
            t_iter = hash_map_find(pt_hmap, "lskdf");
            if(iterator_equal(t_iter, hash_map_end(pt_hmap)))
            {
                printf("not found, count : %u\n", hash_map_count(pt_hmap, "lskdf"));
            }
            else
            {
                printf("found, count : %u\n", hash_map_count(pt_hmap, "lskdf"));
            }

            pair_make(pt_pair, "pair", "hash_map");
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, "**&&^%^&*((&^^%%", "hhh");
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, "uasdhfo", "alsllsls");
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, "1111", "222222222");
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, "88888888", "034950234950234");
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, "", "");
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, "huadl", ":a;lsdkf");
            hash_map_insert(pt_hmap, pt_pair);
            t_iter = hash_map_find(pt_hmap, "lskdf");
            if(iterator_equal(t_iter, hash_map_end(pt_hmap)))
            {
                printf("not found, count : %u\n", hash_map_count(pt_hmap, "lskdf"));
            }
            else
            {
                printf("found, count : %u\n", hash_map_count(pt_hmap, "lskdf"));
            }
            t_iter = hash_map_find(pt_hmap, "1111");
            if(iterator_equal(t_iter, hash_map_end(pt_hmap)))
            {
                printf("not found, count : %u\n", hash_map_count(pt_hmap, "1111"));
            }
            else
            {
                printf("found, count : %u\n", hash_map_count(pt_hmap, "1111"));
            }

            hash_map_destroy(pt_hmap);
            pair_destroy(pt_pair);
        }
        /*hash_map_equal_range       */
        {
            hash_map_t* pt_hmap = create_hash_map(char*, char*);
            pair_t* pt_pair = create_pair(char*, char*);
            range_t t_range;
            if(pt_hmap == NULL || pt_pair == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            hash_map_init_ex(pt_hmap, 0, _hash_map_cstr_hash, NULL);
            t_range = hash_map_equal_range(pt_hmap, "lskdf");
            assert(iterator_equal(t_range.t_begin, hash_map_end(pt_hmap)) &&
                iterator_equal(t_range.t_begin, t_range.t_end));

            pair_make(pt_pair, "pair", "hash_map");
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, "**&&^%^&*((&^^%%", "hhh");
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, "uasdhfo", "alsllsls");
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, "1111", "222222222");
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, "88888888", "034950234950234");
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, "", "");
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, "huadl", ":a;lsdkf");
            hash_map_insert(pt_hmap, pt_pair);
            t_range = hash_map_equal_range(pt_hmap, "lskdf");
            assert(iterator_equal(t_range.t_begin, t_range.t_end));
            t_range = hash_map_equal_range(pt_hmap, "1111");
            assert(iterator_equal(iterator_next(t_range.t_begin), t_range.t_end));

            hash_map_destroy(pt_hmap);
            pair_destroy(pt_pair);
        }
        /*hash_map_at                */
        {
            hash_map_t* pt_hmap = create_hash_map(char*, char*);
            pair_t* pt_pair = create_pair(char*, char*);
            if(pt_hmap == NULL || pt_pair == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_cstr_hash, NULL);
            pair_init(pt_pair);
            hash_map_at(pt_hmap, "slkdfjosidjf");
            hash_map_at(pt_hmap, "lllllll");
            _print_hash_map_cstr(pt_hmap);
            pair_make(pt_pair, "lsdkkkkk", ":::::::");
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, "uls", "lsl");
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, "lllllljslkjd", ";laskdfjeiieslvg");
            hash_map_insert(pt_hmap, pt_pair);
            _print_hash_map_cstr(pt_hmap);

            ((char*)hash_map_at(pt_hmap, "uls"))[1] = 'S';
            _print_hash_map_cstr(pt_hmap);

            hash_map_destroy(pt_hmap);
            pair_destroy(pt_pair);
        }
        /*hash_map_insert            */
        {
            hash_map_t* pt_hmap = create_hash_map(char*, char*);
            pair_t* pt_pair = create_pair(char*, char*);
            if(pt_hmap == NULL || pt_pair == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            hash_map_init_ex(pt_hmap, 0, _hash_map_cstr_hash, NULL);
            _print_hash_map_cstr(pt_hmap);
            pair_make(pt_pair, "lksdjflsdkj", "llllllllllllllll");
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, "uuuu", "UUUUUUUUUUUUUUUUUU");
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, "llll", "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL");
            hash_map_insert(pt_hmap, pt_pair);
            hash_map_insert(pt_hmap, pt_pair);
            _print_hash_map_cstr(pt_hmap);

            pair_destroy(pt_pair);
            hash_map_destroy(pt_hmap);
        }
        /*hash_map_insert_range      */
        {
            hash_map_t* pt_hmap = create_hash_map(char*, char*);
            hash_map_t* pt_hmapex = create_hash_map(char*, char*);
            pair_t* pt_pair = create_pair(char*, char*);
            if(pt_hmap == NULL || pt_hmapex == NULL || pt_pair == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_cstr_hash, NULL);
            hash_map_init_ex(pt_hmapex, 0, _hash_map_cstr_hash, NULL);
            pair_init(pt_pair);

            hash_map_insert_range(pt_hmap, hash_map_begin(pt_hmapex), hash_map_end(pt_hmapex));
            _print_hash_map_cstr(pt_hmap);

            pair_make(pt_pair, "uuuuu", "httpd");
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, "ladjkfoweijf", "al;kdfjoqwiejf");
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, "bnbnbnb", "bnbnbnbn");
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, "||||||||++++", "23948720349(*%&^%*(&)(*)_(*&%&$E");
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, "pair", "hash_map");
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, "**&&^%^&*((&^^%%", "hhh");
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, "uasdhfo", "alsllsls");
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, "1111", "222222222");
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, "88888888", "034950234950234");
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, "", "");
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, "huadl", ":a;lsdkf");
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, "first", "1st");
            hash_map_insert(pt_hmapex, pt_pair);
            pair_make(pt_pair, "nine", "9");
            hash_map_insert(pt_hmapex, pt_pair);
            _print_hash_map_cstr(pt_hmapex);

            hash_map_insert_range(pt_hmap,
                hash_map_begin(pt_hmapex), hash_map_begin(pt_hmapex));
            _print_hash_map_cstr(pt_hmap);
            hash_map_insert_range(pt_hmap,
                hash_map_begin(pt_hmapex), iterator_advance(hash_map_begin(pt_hmapex), 3));
            _print_hash_map_cstr(pt_hmap);
            hash_map_insert_range(pt_hmap,
                iterator_advance(hash_map_begin(pt_hmapex), 5),
                iterator_advance(hash_map_begin(pt_hmapex), 7));
            _print_hash_map_cstr(pt_hmap);
            hash_map_insert_range(pt_hmap,
                iterator_advance(hash_map_begin(pt_hmapex), 10), hash_map_end(pt_hmapex));
            _print_hash_map_cstr(pt_hmap);
            hash_map_insert_range(pt_hmap,
                hash_map_end(pt_hmapex), hash_map_end(pt_hmapex));
            _print_hash_map_cstr(pt_hmap);
            hash_map_insert_range(pt_hmap,
                hash_map_begin(pt_hmapex), hash_map_end(pt_hmapex));
            _print_hash_map_cstr(pt_hmap);

            hash_map_destroy(pt_hmap);
            hash_map_destroy(pt_hmapex);
            pair_destroy(pt_pair);
        }
        /*hash_map_erase             */
        {
            hash_map_t* pt_hmap = create_hash_map(char*, char*);
            pair_t* pt_pair = create_pair(char*, char*);
            if(pt_hmap == NULL || pt_pair == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            hash_map_init_ex(pt_hmap, 0, _hash_map_cstr_hash, NULL);

            hash_map_erase(pt_hmap, "ok");
            _print_hash_map_cstr(pt_hmap);

            pair_make(pt_pair, "lksdjflsdkj", "llllllllllllllll");
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, "uuuu", "UUUUUUUUUUUUUUUUUU");
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, "llll", "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL");
            hash_map_insert(pt_hmap, pt_pair);
            hash_map_insert(pt_hmap, pt_pair);
            _print_hash_map_cstr(pt_hmap);

            hash_map_erase(pt_hmap, "ok");
            _print_hash_map_cstr(pt_hmap);
            hash_map_erase(pt_hmap, "uuuu");
            _print_hash_map_cstr(pt_hmap);

            pair_destroy(pt_pair);
            hash_map_destroy(pt_hmap);
        }
        /*hash_map_erase_pos         */
        {
            hash_map_t* pt_hmap = create_hash_map(char*, char*);
            pair_t* pt_pair = create_pair(char*, char*);
            if(pt_hmap == NULL || pt_pair == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            hash_map_init_ex(pt_hmap, 0, _hash_map_cstr_hash, NULL);

            pair_make(pt_pair, "lksdjflsdkj", "llllllllllllllll");
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, "uuuu", "UUUUUUUUUUUUUUUUUU");
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, "llll", "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL");
            hash_map_insert(pt_hmap, pt_pair);
            hash_map_insert(pt_hmap, pt_pair);
            _print_hash_map_cstr(pt_hmap);

            hash_map_erase_pos(pt_hmap, hash_map_begin(pt_hmap));
            _print_hash_map_cstr(pt_hmap);
            hash_map_erase_pos(pt_hmap, iterator_next(hash_map_begin(pt_hmap)));
            _print_hash_map_cstr(pt_hmap);
            while(!hash_map_empty(pt_hmap))
            {
                hash_map_erase_pos(pt_hmap, hash_map_begin(pt_hmap));
            }
            _print_hash_map_cstr(pt_hmap);

            pair_destroy(pt_pair);
            hash_map_destroy(pt_hmap);
        }
        /*hash_map_erase_range       */
        {
            hash_map_t* pt_hmap = create_hash_map(char*, char*);
            pair_t* pt_pair = create_pair(char*, char*);
            if(pt_hmap == NULL || pt_pair == NULL)
            {
                return;
            }
            hash_map_init_ex(pt_hmap, 0, _hash_map_cstr_hash, NULL);
            pair_init(pt_pair);

            hash_map_erase_range(pt_hmap, hash_map_begin(pt_hmap), hash_map_end(pt_hmap));
            _print_hash_map_cstr(pt_hmap);

            pair_make(pt_pair, "uuuuu", "httpd");
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, "ladjkfoweijf", "al;kdfjoqwiejf");
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, "bnbnbnb", "bnbnbnbn");
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, "||||||||++++", "23948720349(*%&^%*(&)(*)_(*&%&$E");
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, "pair", "hash_map");
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, "**&&^%^&*((&^^%%", "hhh");
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, "uasdhfo", "alsllsls");
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, "1111", "222222222");
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, "88888888", "034950234950234");
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, "", "");
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, "huadl", ":a;lsdkf");
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, "first", "1st");
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, "nine", "9");
            hash_map_insert(pt_hmap, pt_pair);
            _print_hash_map_cstr(pt_hmap);

            hash_map_erase_range(pt_hmap,
                hash_map_begin(pt_hmap), hash_map_begin(pt_hmap));
            _print_hash_map_cstr(pt_hmap);
            hash_map_erase_range(pt_hmap,
                hash_map_begin(pt_hmap), iterator_advance(hash_map_begin(pt_hmap), 3));
            _print_hash_map_cstr(pt_hmap);
            hash_map_erase_range(pt_hmap,
                iterator_advance(hash_map_begin(pt_hmap), 2),
                iterator_advance(hash_map_begin(pt_hmap), 5));
            _print_hash_map_cstr(pt_hmap);
            hash_map_erase_range(pt_hmap,
                iterator_advance(hash_map_begin(pt_hmap), 3), hash_map_end(pt_hmap));
            _print_hash_map_cstr(pt_hmap);
            hash_map_erase_range(pt_hmap,
                hash_map_end(pt_hmap), hash_map_end(pt_hmap));
            _print_hash_map_cstr(pt_hmap);
            hash_map_erase_range(pt_hmap,
                hash_map_begin(pt_hmap), hash_map_end(pt_hmap));
            _print_hash_map_cstr(pt_hmap);

            hash_map_destroy(pt_hmap);
            pair_destroy(pt_pair);
        }
        /*hash_map_clear             */
        {
            hash_map_t* pt_hmap = create_hash_map(char*, char*);
            pair_t* pt_pair = create_pair(char*, char*);
            if(pt_hmap == NULL || pt_pair == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            hash_map_init_ex(pt_hmap, 0, _hash_map_cstr_hash, NULL);

            hash_map_clear(pt_hmap);
            _print_hash_map_cstr(pt_hmap);

            pair_make(pt_pair, "lksdjflsdkj", "llllllllllllllll");
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, "uuuu", "UUUUUUUUUUUUUUUUUU");
            hash_map_insert(pt_hmap, pt_pair);
            pair_make(pt_pair, "llll", "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL");
            hash_map_insert(pt_hmap, pt_pair);
            hash_map_insert(pt_hmap, pt_pair);
            _print_hash_map_cstr(pt_hmap);

            hash_map_clear(pt_hmap);
            _print_hash_map_cstr(pt_hmap);
            pair_destroy(pt_pair);
            hash_map_destroy(pt_hmap);
        }
    }
}

void test_hash_multimap(void)
{
    /* c built-in */
    {
        /*create_hash_multimap            */
        /*hash_multimap_init              */
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, double);
            pair_t* pt_pair = create_pair(int, double);
            if(pt_hmmap == NULL || pt_pair == NULL)
            {
                return;
            }
            hash_multimap_init(pt_hmmap);
            pair_init(pt_pair);
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);
            pair_make(pt_pair, 45, 42304.23);
            hash_multimap_insert(pt_hmmap, pt_pair);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 1029, 22.2);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 0, 0.20);
            hash_multimap_insert(pt_hmmap, pt_pair);
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);
            hash_multimap_destroy(pt_hmmap);
            pair_destroy(pt_pair);
        }
        /*hash_multimap_init_ex           */
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, double);
            pair_t* pt_pair = create_pair(int, double);
            if(pt_hmmap == NULL || pt_pair == NULL)
            {
                return;
            }
            hash_multimap_init_ex(pt_hmmap, 100, _hash_multimap_int_key_hash, NULL);
            pair_init(pt_pair);
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);
            pair_make(pt_pair, 45, 42304.23);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 1029, 22.2);
            hash_multimap_insert(pt_hmmap, pt_pair);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 0, 0.20);
            hash_multimap_insert(pt_hmmap, pt_pair);
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);
            hash_multimap_destroy(pt_hmmap);
            pair_destroy(pt_pair);
        }
        /*hash_multimap_init_copy         */
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(short, int);
            hash_multimap_t* pt_hmmapex = create_hash_multimap(short, int);
            pair_t* pt_pair = create_pair(short, int);
            if(pt_hmmap == NULL || pt_hmmapex == NULL || pt_pair == NULL)
            {
                return;
            }
            hash_multimap_init(pt_hmmapex);
            pair_init(pt_pair);

            pair_make(pt_pair, 45, 1023);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            pair_make(pt_pair, 0, 234);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            pair_make(pt_pair, -9, -3235);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            pair_make(pt_pair, 23, 23);
            hash_multimap_insert(pt_hmmapex, pt_pair);

            hash_multimap_init_copy(pt_hmmap, pt_hmmapex);
            _print_hash_multimap_c(pt_hmmapex, "<%hd, %d>, ", short, int);
            _print_hash_multimap_c(pt_hmmap, "<%hd, %d>, ", short, int);

            hash_multimap_destroy(pt_hmmap);
            hash_multimap_destroy(pt_hmmapex);
            pair_destroy(pt_pair);
        }
        /*hash_multimap_init_copy_range   */
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, double);
            hash_multimap_t* pt_hmmapex = create_hash_multimap(int, double);
            pair_t* pt_pair = create_pair(int, double);
            if(pt_hmmap == NULL || pt_hmmapex == NULL || pt_pair == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            hash_multimap_init_ex(pt_hmmapex, 100, _hash_multimap_int_key_hash, NULL);

            pair_make(pt_pair, 23, 434.239);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            pair_make(pt_pair, 2, 1.0);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            pair_make(pt_pair, 445, 34.23);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            pair_make(pt_pair, 6, 2.9);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            pair_make(pt_pair, 4, 213);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            pair_make(pt_pair, 0, 42.2);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            pair_make(pt_pair, 2, 234.09);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            pair_make(pt_pair, 3, 20.123);
            hash_multimap_insert(pt_hmmapex, pt_pair);

            hash_multimap_init_copy_range(pt_hmmap, hash_multimap_begin(pt_hmmapex),
                hash_multimap_end(pt_hmmapex));
            _print_hash_multimap_c(pt_hmmapex, "<%d, %lf>, ", int, double);
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);

            hash_multimap_destroy(pt_hmmap);
            hash_multimap_destroy(pt_hmmapex);
            pair_destroy(pt_pair);
        }
        /*hash_multimap_init_copy_range_ex*/
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, double);
            hash_multimap_t* pt_hmmapex = create_hash_multimap(int, double);
            pair_t* pt_pair = create_pair(int, double);
            if(pt_hmmap == NULL || pt_hmmapex == NULL || pt_pair == NULL)
            {
                return;
            }
            hash_multimap_init(pt_hmmapex);
            pair_init(pt_pair);

            pair_make(pt_pair, 3, 43.23);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            pair_make(pt_pair, 12, 12.12);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            pair_make(pt_pair, 0, 2.0);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            pair_make(pt_pair, 9, 9.0);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            pair_make(pt_pair, 121, 23.2);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            pair_make(pt_pair, 1, 23.23);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            pair_make(pt_pair, 8, 2.23);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            pair_make(pt_pair, 3, 45.09);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            hash_multimap_init_copy_range_ex(pt_hmmap, hash_multimap_begin(pt_hmmapex),
                hash_multimap_end(pt_hmmapex),
                100, _hash_multimap_int_key_hash, NULL);
            _print_hash_multimap_c(pt_hmmapex, "<%d, %lf>, ", int, double);
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);

            hash_multimap_destroy(pt_hmmap);
            hash_multimap_destroy(pt_hmmapex);
            pair_destroy(pt_pair);
        }
        /*hash_multimap_destroy           */
        /*hash_multimap_assign            */
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, double);
            hash_multimap_t* pt_hmmapex = create_hash_multimap(int, double);
            pair_t* pt_pair = create_pair(int, double);
            if(pt_hmmap == NULL || pt_hmmapex == NULL || pt_pair == NULL)
            {
                return;
            }
            hash_multimap_init_ex(pt_hmmap, 0, _hash_multimap_int_key_hash, NULL);
            hash_multimap_init_ex(pt_hmmapex, 0, _hash_multimap_int_key_hash, NULL);
            pair_init(pt_pair);

            hash_multimap_assign(pt_hmmap, pt_hmmapex);
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);

            pair_make(pt_pair, 23, 290.233);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            pair_make(pt_pair, -7, -7.7);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            pair_make(pt_pair, 0, 0.0);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            pair_make(pt_pair, 112122, 3.23);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            hash_multimap_assign(pt_hmmap, pt_hmmapex);
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);

            hash_multimap_clear(pt_hmmapex);
            pair_make(pt_pair, 9, 434.345);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            pair_make(pt_pair, 23, 23.23);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            pair_make(pt_pair, 9, 232323.2323);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            pair_make(pt_pair, 1, 43.23);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            pair_make(pt_pair, 6, 6.6);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            pair_make(pt_pair, 5, 23.2323);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            pair_make(pt_pair, 4, 232.0);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            hash_multimap_assign(pt_hmmap, pt_hmmapex);
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);

            hash_multimap_clear(pt_hmmapex);
            pair_make(pt_pair, 34, 23.23);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            pair_make(pt_pair, 6, 34.1);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            hash_multimap_assign(pt_hmmap, pt_hmmapex);
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);

            hash_multimap_clear(pt_hmmapex);
            hash_multimap_assign(pt_hmmap, pt_hmmapex);
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);

            hash_multimap_destroy(pt_hmmap);
            hash_multimap_destroy(pt_hmmapex);
            pair_destroy(pt_pair);
        }
        /*hash_multimap_swap              */
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, double);
            hash_multimap_t* pt_hmmapex = create_hash_multimap(int, double);
            pair_t* pt_pair = create_pair(int, double);
            if(pt_hmmap == NULL || pt_hmmapex == NULL || pt_pair == NULL)
            {
                return;
            }
            hash_multimap_init_ex(pt_hmmap, 0, _hash_multimap_int_key_hash, NULL);
            hash_multimap_init_ex(pt_hmmapex, 0, _hash_multimap_int_key_hash, NULL);
            pair_init(pt_pair);

            hash_multimap_swap(pt_hmmap, pt_hmmapex);
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);
            _print_hash_multimap_c(pt_hmmapex, "<%d, %lf>, ", int, double);

            pair_make(pt_pair, 23, 290.233);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            pair_make(pt_pair, -7, -7.7);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            pair_make(pt_pair, 0, 0.0);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            pair_make(pt_pair, 112122, 3.23);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            hash_multimap_swap(pt_hmmap, pt_hmmapex);
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);
            _print_hash_multimap_c(pt_hmmapex, "<%d, %lf>, ", int, double);

            hash_multimap_clear(pt_hmmapex);
            pair_make(pt_pair, 9, 434.345);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            pair_make(pt_pair, 23, 23.23);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            pair_make(pt_pair, 9, 232323.2323);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            pair_make(pt_pair, 1, 43.23);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            pair_make(pt_pair, 6, 6.6);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            pair_make(pt_pair, 5, 23.2323);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            pair_make(pt_pair, 4, 232.0);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            hash_multimap_swap(pt_hmmap, pt_hmmapex);
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);
            _print_hash_multimap_c(pt_hmmapex, "<%d, %lf>, ", int, double);

            hash_multimap_clear(pt_hmmapex);
            pair_make(pt_pair, 34, 23.23);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            pair_make(pt_pair, 6, 34.1);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            hash_multimap_swap(pt_hmmap, pt_hmmapex);
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);
            _print_hash_multimap_c(pt_hmmapex, "<%d, %lf>, ", int, double);

            hash_multimap_clear(pt_hmmapex);
            hash_multimap_swap(pt_hmmap, pt_hmmapex);
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);
            _print_hash_multimap_c(pt_hmmapex, "<%d, %lf>, ", int, double);

            hash_multimap_destroy(pt_hmmap);
            hash_multimap_destroy(pt_hmmapex);
            pair_destroy(pt_pair);
        }
        /*hash_multimap_size              */
        /*hash_multimap_empty             */
        /*hash_multimap_max_size          */
        /*hash_multimap_bucket_count      */
        /*hash_multimap_hash              */
        /*hash_multimap_key_less          */
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, double);
            if(pt_hmmap == NULL)
            {
                return;
            }
            hash_multimap_init_ex(pt_hmmap, 100, _hash_multimap_int_key_hash, fun_great_int);
            assert(hash_multimap_hash(pt_hmmap) == _hash_multimap_int_key_hash &&
                hash_multimap_key_less(pt_hmmap) == fun_great_int);
            hash_multimap_destroy(pt_hmmap);
        }
        /*hash_multimap_resize            */
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, double);
            if(pt_hmmap == NULL)
            {
                return;
            }
            hash_multimap_init(pt_hmmap);
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);
            hash_multimap_resize(pt_hmmap, 50);
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);
            hash_multimap_resize(pt_hmmap, 500);
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);
            hash_multimap_resize(pt_hmmap, 5);
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);
            hash_multimap_resize(pt_hmmap, 0);
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);
            hash_multimap_destroy(pt_hmmap);
        }
        /*hash_multimap_equal             */
        /*hash_multimap_not_equal         */
        /*hash_multimap_less              */
        /*hash_multimap_less_equal        */
        /*hash_multimap_great             */
        /*hash_multimap_great_equal       */
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, double);
            hash_multimap_t* pt_hmmapex = create_hash_multimap(int, double);
            pair_t* pt_pair = create_pair(int, double);
            if(pt_hmmap == NULL || pt_hmmapex == NULL || pt_pair == NULL)
            {
                return;
            }
            hash_multimap_init_ex(pt_hmmap, 0, _hash_multimap_int_key_hash, NULL);
            hash_multimap_init_ex(pt_hmmapex, 0, _hash_multimap_int_key_hash, NULL);
            pair_init(pt_pair);

            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);
            _print_hash_multimap_c(pt_hmmapex, "<%d, %lf>, ", int, double);
            printf("equal: %d, not equal: %d, ",
                hash_multimap_equal(pt_hmmap, pt_hmmapex), hash_multimap_not_equal(pt_hmmap, pt_hmmapex));
            printf("less: %d, less equal: %d, ",
                hash_multimap_less(pt_hmmap, pt_hmmapex), hash_multimap_less_equal(pt_hmmap, pt_hmmapex));
            printf("great: %d, great equal: %d\n",
                hash_multimap_great(pt_hmmap, pt_hmmapex), hash_multimap_great_equal(pt_hmmap, pt_hmmapex));

            pair_make(pt_pair, 4, 89.23);
            hash_multimap_insert(pt_hmmap, pt_pair);
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);
            _print_hash_multimap_c(pt_hmmapex, "<%d, %lf>, ", int, double);
            printf("equal: %d, not equal: %d, ",
                hash_multimap_equal(pt_hmmap, pt_hmmapex), hash_multimap_not_equal(pt_hmmap, pt_hmmapex));
            printf("less: %d, less equal: %d, ",
                hash_multimap_less(pt_hmmap, pt_hmmapex), hash_multimap_less_equal(pt_hmmap, pt_hmmapex));
            printf("great: %d, great equal: %d\n",
                hash_multimap_great(pt_hmmap, pt_hmmapex), hash_multimap_great_equal(pt_hmmap, pt_hmmapex));

            hash_multimap_insert(pt_hmmapex, pt_pair);
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);
            _print_hash_multimap_c(pt_hmmapex, "<%d, %lf>, ", int, double);
            printf("equal: %d, not equal: %d, ",
                hash_multimap_equal(pt_hmmap, pt_hmmapex), hash_multimap_not_equal(pt_hmmap, pt_hmmapex));
            printf("less: %d, less equal: %d, ",
                hash_multimap_less(pt_hmmap, pt_hmmapex), hash_multimap_less_equal(pt_hmmap, pt_hmmapex));
            printf("great: %d, great equal: %d\n",
                hash_multimap_great(pt_hmmap, pt_hmmapex), hash_multimap_great_equal(pt_hmmap, pt_hmmapex));

            pair_make(pt_pair, 2, 90.2);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 3, 2323.23423);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 10, 10.0);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);
            _print_hash_multimap_c(pt_hmmapex, "<%d, %lf>, ", int, double);
            printf("equal: %d, not equal: %d, ",
                hash_multimap_equal(pt_hmmap, pt_hmmapex), hash_multimap_not_equal(pt_hmmap, pt_hmmapex));
            printf("less: %d, less equal: %d, ",
                hash_multimap_less(pt_hmmap, pt_hmmapex), hash_multimap_less_equal(pt_hmmap, pt_hmmapex));
            printf("great: %d, great equal: %d\n",
                hash_multimap_great(pt_hmmap, pt_hmmapex), hash_multimap_great_equal(pt_hmmap, pt_hmmapex));

            hash_multimap_destroy(pt_hmmap);
            hash_multimap_destroy(pt_hmmapex);
            pair_destroy(pt_pair);
        }
        /*hash_multimap_begin             */
        /*hash_multimap_end               */
        /*hash_multimap_find              */
        /*hash_multimap_count             */
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, double);
            pair_t* pt_pair = create_pair(int, double);
            iterator_t t_iter;
            if(pt_hmmap == NULL || pt_pair == NULL)
            {
                return;
            }
            hash_multimap_init_ex(pt_hmmap, 0, _hash_multimap_int_key_hash, NULL);
            pair_init(pt_pair);

            pair_make(pt_pair, 0, 0.0);
            t_iter = hash_multimap_find(pt_hmmap, 0);
            if(iterator_equal(t_iter, hash_multimap_end(pt_hmmap)))
            {
                printf("not found! count : %u\n", hash_multimap_count(pt_hmmap, 0));
            }
            else
            {
                printf("found! count : %u\n", hash_multimap_count(pt_hmmap, 0));
            }

            pair_make(pt_pair, 45, 23.232);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 23, 1.111);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 56, 23.2222);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 0, 0.0);

            t_iter = hash_multimap_find(pt_hmmap, 0);
            if(iterator_equal(t_iter, hash_multimap_end(pt_hmmap)))
            {
                printf("not found! count : %u\n", hash_multimap_count(pt_hmmap, 0));
            }
            else
            {
                printf("found! count : %u\n", hash_multimap_count(pt_hmmap, 0));
            }

            pair_make(pt_pair, 45, 23.232);
            t_iter = hash_multimap_find(pt_hmmap, 45);
            if(iterator_equal(t_iter, hash_multimap_end(pt_hmmap)))
            {
                printf("not found! count : %u\n", hash_multimap_count(pt_hmmap, 45));
            }
            else
            {
                printf("found! count : %u\n", hash_multimap_count(pt_hmmap, 45));
            }

            hash_multimap_destroy(pt_hmmap);
            pair_destroy(pt_pair);
        }
        /*hash_multimap_equal_range       */
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, double);
            pair_t* pt_pair = create_pair(int, double);
            range_t t_range;
            if(pt_hmmap == NULL || pt_pair == NULL)
            {
                return;
            }
            hash_multimap_init_ex(pt_hmmap, 0, _hash_multimap_int_key_hash, NULL);
            pair_init(pt_pair);

            t_range = hash_multimap_equal_range(pt_hmmap, 0);
            assert(iterator_equal(t_range.t_begin, hash_multimap_end(pt_hmmap)) &&
                iterator_equal(t_range.t_begin, t_range.t_end));

            pair_make(pt_pair, 3, 290.2323);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 67, 34.11);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 5, 333.222);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 14, 44.4);
            hash_multimap_insert(pt_hmmap, pt_pair);
            t_range = hash_multimap_equal_range(pt_hmmap, 0);
            assert(iterator_equal(t_range.t_begin, t_range.t_end));
            t_range = hash_multimap_equal_range(pt_hmmap, 14);
            assert(iterator_equal(iterator_next(t_range.t_begin), t_range.t_end));

            hash_multimap_destroy(pt_hmmap);
            pair_destroy(pt_pair);
        }
        /*hash_multimap_insert            */
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, double);
            pair_t* pt_pair = create_pair(int, double);
            if(pt_hmmap == NULL || pt_pair == NULL)
            {
                return;
            }
            hash_multimap_init_ex(pt_hmmap, 0, _hash_multimap_int_key_hash, NULL);
            pair_init(pt_pair);
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);
            pair_make(pt_pair, 23, 0.983);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 4, 90.0);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 2, 2.22);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 4, -83784.2323);
            hash_multimap_insert(pt_hmmap, pt_pair);
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);

            hash_multimap_destroy(pt_hmmap);
            pair_destroy(pt_pair);
        }
        /*hash_multimap_insert_range      */
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, double);
            hash_multimap_t* pt_hmmapex = create_hash_multimap(int, double);
            pair_t* pt_pair = create_pair(int, double);
            if(pt_hmmap == NULL || pt_hmmapex == NULL || pt_pair == NULL)
            {
                return;
            }
            hash_multimap_init_ex(pt_hmmap, 0, _hash_multimap_int_key_hash, NULL);
            hash_multimap_init_ex(pt_hmmapex, 0, _hash_multimap_int_key_hash, NULL);
            pair_init(pt_pair);

            hash_multimap_insert_range(pt_hmmap, hash_multimap_begin(pt_hmmapex), hash_multimap_end(pt_hmmapex));
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);

            /**(double*)hash_multimap_at(pt_hmmapex, 45) = 4.34;*/
            pair_make(pt_pair, 45, 4.34);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            /**(double*)hash_multimap_at(pt_hmmapex, 2) = -4.245;*/
            pair_make(pt_pair, 2, -4.34);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            /**(double*)hash_multimap_at(pt_hmmapex, 56) = 34.23;*/
            pair_make(pt_pair, 56, 34.23);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            /**(double*)hash_multimap_at(pt_hmmapex, 3) = 3.3;*/
            pair_make(pt_pair, 3, 3.3);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            /**(double*)hash_multimap_at(pt_hmmapex, 0) = 0.0;*/
            pair_make(pt_pair, 0, 0.0);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            /**(double*)hash_multimap_at(pt_hmmapex, 343) = 5.5634;*/
            pair_make(pt_pair, 343, 5.5634);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            /**(double*)hash_multimap_at(pt_hmmapex, 22) = 22.22;*/
            pair_make(pt_pair, 22, 22.22);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            /**(double*)hash_multimap_at(pt_hmmapex, 5) = 5.5555;*/
            pair_make(pt_pair, 5, 5.5555);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            /**(double*)hash_multimap_at(pt_hmmapex, 4) = 10.1;*/
            pair_make(pt_pair, 4, 10.1);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            /**(double*)hash_multimap_at(pt_hmmapex, 334) = -0.000003;*/
            pair_make(pt_pair, 334, -0.0000003);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            /**(double*)hash_multimap_at(pt_hmmapex, 44) = 44.44;*/
            pair_make(pt_pair, 4, 4.444444);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            /**(double*)hash_multimap_at(pt_hmmapex, 1) = 1.1;*/
            pair_make(pt_pair, 1, 1.111111);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            _print_hash_multimap_c(pt_hmmapex, "<%d, %lf>, ", int, double);

            hash_multimap_insert_range(pt_hmmap, hash_multimap_begin(pt_hmmapex), hash_multimap_begin(pt_hmmapex));
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);
            hash_multimap_insert_range(pt_hmmap, hash_multimap_begin(pt_hmmapex),
                iterator_advance(hash_multimap_begin(pt_hmmapex), 3));
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);
            hash_multimap_insert_range(pt_hmmap, iterator_advance(hash_multimap_begin(pt_hmmapex), 5),
                iterator_advance(hash_multimap_begin(pt_hmmapex), 7));
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);
            hash_multimap_insert_range(pt_hmmap, iterator_advance(hash_multimap_begin(pt_hmmapex), 9),
                hash_multimap_end(pt_hmmapex));
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);
            hash_multimap_insert_range(pt_hmmap, hash_multimap_end(pt_hmmapex), hash_multimap_end(pt_hmmapex));
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);
            hash_multimap_clear(pt_hmmap);
            hash_multimap_insert_range(pt_hmmap, hash_multimap_begin(pt_hmmapex), hash_multimap_end(pt_hmmapex));
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);

            hash_multimap_destroy(pt_hmmap);
            hash_multimap_destroy(pt_hmmapex);
            pair_destroy(pt_pair);
        }
        /*hash_multimap_erase             */
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, double);
            pair_t* pt_pair = create_pair(int, double);
            if(pt_hmmap == NULL || pt_pair == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            hash_multimap_init_ex(pt_hmmap, 0, _hash_multimap_int_key_hash, NULL);
            hash_multimap_erase(pt_hmmap, 0);
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);

            /**(double*)hash_multimap_at(pt_hmmap, 45) = 4.34;*/
            pair_make(pt_pair, 45, 4.34);
            hash_multimap_insert(pt_hmmap, pt_pair);
            /**(double*)hash_multimap_at(pt_hmmap, 2) = -4.245;*/
            pair_make(pt_pair, 2, -4.34);
            hash_multimap_insert(pt_hmmap, pt_pair);
            /**(double*)hash_multimap_at(pt_hmmap, 56) = 34.23;*/
            pair_make(pt_pair, 56, 34.23);
            hash_multimap_insert(pt_hmmap, pt_pair);
            /**(double*)hash_multimap_at(pt_hmmap, 3) = 3.3;*/
            pair_make(pt_pair, 3, 3.3);
            hash_multimap_insert(pt_hmmap, pt_pair);
            /**(double*)hash_multimap_at(pt_hmmap, 0) = 0.0;*/
            pair_make(pt_pair, 0, 0.0);
            hash_multimap_insert(pt_hmmap, pt_pair);
            /**(double*)hash_multimap_at(pt_hmmap, 343) = 5.5634;*/
            pair_make(pt_pair, 343, 5.5634);
            hash_multimap_insert(pt_hmmap, pt_pair);
            /**(double*)hash_multimap_at(pt_hmmap, 22) = 22.22;*/
            pair_make(pt_pair, 22, 22.22);
            hash_multimap_insert(pt_hmmap, pt_pair);
            /**(double*)hash_multimap_at(pt_hmmap, 5) = 5.5555;*/
            pair_make(pt_pair, 5, 5.5555);
            hash_multimap_insert(pt_hmmap, pt_pair);
            /**(double*)hash_multimap_at(pt_hmmap, 4) = 10.1;*/
            pair_make(pt_pair, 4, 10.1);
            hash_multimap_insert(pt_hmmap, pt_pair);
            /**(double*)hash_multimap_at(pt_hmmap, 334) = -0.000003;*/
            pair_make(pt_pair, 334, -0.0000003);
            hash_multimap_insert(pt_hmmap, pt_pair);
            /**(double*)hash_multimap_at(pt_hmmap, 44) = 44.44;*/
            pair_make(pt_pair, 4, 4.444444);
            hash_multimap_insert(pt_hmmap, pt_pair);
            /**(double*)hash_multimap_at(pt_hmmap, 1) = 1.1;*/
            pair_make(pt_pair, 1, 1.111111);
            hash_multimap_insert(pt_hmmap, pt_pair);
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);

            hash_multimap_erase(pt_hmmap, 10);
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);
            hash_multimap_erase(pt_hmmap, 22);
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);

            hash_multimap_destroy(pt_hmmap);
            pair_destroy(pt_pair);
        }
        /*hash_multimap_erase_pos         */
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, double);
            pair_t* pt_pair = create_pair(int, double);
            if(pt_hmmap == NULL || pt_pair == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            hash_multimap_init_ex(pt_hmmap, 0, _hash_multimap_int_key_hash, NULL);
            pair_make(pt_pair, 45, 4.34);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 2, -4.34);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 56, 34.23);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 3, 3.3);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 0, 0.0);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 343, 5.5634);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 22, 22.22);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 5, 5.5555);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 4, 10.1);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 334, -0.0000003);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 4, 4.444444);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 1, 1.111111);
            hash_multimap_insert(pt_hmmap, pt_pair);
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);

            hash_multimap_erase_pos(pt_hmmap, hash_multimap_begin(pt_hmmap));
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);
            hash_multimap_erase_pos(pt_hmmap, iterator_advance(hash_multimap_begin(pt_hmmap), 3));
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);
            while(!hash_multimap_empty(pt_hmmap))
            {
                hash_multimap_erase_pos(pt_hmmap, hash_multimap_begin(pt_hmmap));
            }
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);

            hash_multimap_destroy(pt_hmmap);
            pair_destroy(pt_pair);
        }
        /*hash_multimap_erase_range       */
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, double);
            pair_t* pt_pair = create_pair(int, double);
            if(pt_hmmap == NULL || pt_pair == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            hash_multimap_init_ex(pt_hmmap, 0, _hash_multimap_int_key_hash, NULL);
            hash_multimap_erase_range(pt_hmmap, hash_multimap_begin(pt_hmmap), hash_multimap_end(pt_hmmap));
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);
            pair_make(pt_pair, 45, 4.34);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 2, -4.34);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 56, 34.23);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 3, 3.3);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 0, 0.0);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 343, 5.5634);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 22, 22.22);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 5, 5.5555);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 4, 10.1);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 334, -0.0000003);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 4, 4.444444);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 1, 1.111111);
            hash_multimap_insert(pt_hmmap, pt_pair);
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);

            hash_multimap_erase_range(pt_hmmap, hash_multimap_begin(pt_hmmap), hash_multimap_begin(pt_hmmap));
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);
            hash_multimap_erase_range(pt_hmmap, hash_multimap_begin(pt_hmmap),
                iterator_advance(hash_multimap_begin(pt_hmmap), 3));
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);
            hash_multimap_erase_range(pt_hmmap, iterator_next(hash_multimap_begin(pt_hmmap)),
                iterator_advance(hash_multimap_begin(pt_hmmap), 4));
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);
            hash_multimap_erase_range(pt_hmmap, iterator_advance(hash_multimap_begin(pt_hmmap), 3),
                hash_multimap_end(pt_hmmap));
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);
            hash_multimap_erase_range(pt_hmmap, hash_multimap_end(pt_hmmap), hash_multimap_end(pt_hmmap));
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);
            hash_multimap_erase_range(pt_hmmap, hash_multimap_begin(pt_hmmap), hash_multimap_end(pt_hmmap));
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);

            hash_multimap_destroy(pt_hmmap);
            pair_destroy(pt_pair);
        }
        /*hash_multimap_clear             */
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, double);
            pair_t* pt_pair = create_pair(int, double);
            if(pt_hmmap == NULL || pt_pair == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            hash_multimap_init_ex(pt_hmmap, 0, _hash_multimap_int_key_hash, NULL);
            hash_multimap_clear(pt_hmmap);
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);
            pair_make(pt_pair, 45, 4.34);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 2, -4.34);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 56, 34.23);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 3, 3.3);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 0, 0.0);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 343, 5.5634);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 22, 22.22);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 5, 5.5555);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 4, 10.1);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 334, -0.0000003);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 4, 4.444444);
            hash_multimap_insert(pt_hmmap, pt_pair);
            pair_make(pt_pair, 1, 1.111111);
            hash_multimap_insert(pt_hmmap, pt_pair);
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);

            hash_multimap_clear(pt_hmmap);
            _print_hash_multimap_c(pt_hmmap, "<%d, %lf>, ", int, double);

            hash_multimap_destroy(pt_hmmap);
            pair_destroy(pt_pair);
        }
    }
    /* user define */
    {
        type_register(hash_sample_t, _hash_sample_init, _hash_sample_copy,
            _hash_sample_less, _hash_sample_destroy);
        /*create_hash_multimap            */
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, hash_sample_t);
            pair_t* pt_pair = create_pair(int, hash_sample_t);
            hash_sample_t t_sample;
            if(pt_hmmap == NULL || pt_pair == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            hash_multimap_init(pt_hmmap);
            _print_hash_multimap_sample(pt_hmmap);

            t_sample._l_second = 4509;
            t_sample._d_first = 43.4;
            pair_make(pt_pair, 34, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            _print_hash_multimap_sample(pt_hmmap);
            hash_multimap_destroy(pt_hmmap);
            pair_destroy(pt_pair);
        }
        /*hash_multimap_init              */
        /*hash_multimap_init_ex           */
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, hash_sample_t);
            pair_t* pt_pair = create_pair(int, hash_sample_t);
            hash_sample_t t_sample;
            if(pt_hmmap == NULL || pt_pair == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            hash_multimap_init_ex(pt_hmmap, 0, _hash_multimap_sample_hash, NULL);
            _print_hash_multimap_sample(pt_hmmap);

            t_sample._l_second = 4509;
            t_sample._d_first = 43.4;
            pair_make(pt_pair, 34, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            _print_hash_multimap_sample(pt_hmmap);
            hash_multimap_destroy(pt_hmmap);
            pair_destroy(pt_pair);
        }
        /*hash_multimap_init_copy         */
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, hash_sample_t);
            hash_multimap_t* pt_hmmapex = create_hash_multimap(int, hash_sample_t);
            pair_t* pt_pair = create_pair(int, hash_sample_t);
            hash_sample_t t_sample;
            if(pt_hmmap == NULL || pt_hmmapex == NULL || pt_pair == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            hash_multimap_init_ex(pt_hmmapex, 0, _hash_multimap_sample_hash, NULL);

            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 34))->_d_first = 43.4;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 34))->_l_second = 4509;*/
            t_sample._l_second = 4509;
            t_sample._d_first = 43.4;
            pair_make(pt_pair, 34, &t_sample);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 90))->_d_first = -1.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 90))->_l_second = 90;*/
            t_sample._l_second = 90;
            t_sample._d_first = -1.11;
            pair_make(pt_pair, 90, &t_sample);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 9))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 9))->_l_second = 50;*/
            t_sample._l_second = 50;
            t_sample._d_first = -5.11;
            pair_make(pt_pair, 9, &t_sample);
            hash_multimap_insert(pt_hmmapex, pt_pair);

            hash_multimap_init_copy(pt_hmmap, pt_hmmapex);
            _print_hash_multimap_sample(pt_hmmap);
            hash_multimap_destroy(pt_hmmap);
            hash_multimap_destroy(pt_hmmapex);
            pair_destroy(pt_pair);
        }
        /*hash_multimap_init_copy_range   */
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, hash_sample_t);
            hash_multimap_t* pt_hmmapex = create_hash_multimap(int, hash_sample_t);
            pair_t* pt_pair = create_pair(int, hash_sample_t);
            hash_sample_t t_sample;
            if(pt_hmmap == NULL || pt_hmmapex == NULL || pt_pair == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            hash_multimap_init_ex(pt_hmmapex, 0, _hash_multimap_sample_hash, NULL);

            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 34))->_d_first = 43.4;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 34))->_l_second = 4509;*/
            t_sample._l_second = 4509;
            t_sample._d_first = 43.4;
            pair_make(pt_pair, 34, &t_sample);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 90))->_d_first = -1.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 90))->_l_second = 90;*/
            t_sample._l_second = 90;
            t_sample._d_first = -1.11;
            pair_make(pt_pair, 90, &t_sample);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 9))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 9))->_l_second = 50;*/
            t_sample._l_second = 50;
            t_sample._d_first = -5.11;
            pair_make(pt_pair, 9, &t_sample);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            _print_hash_multimap_sample(pt_hmmapex);

            hash_multimap_init_copy_range(pt_hmmap,
                hash_multimap_begin(pt_hmmapex), hash_multimap_end(pt_hmmapex));
            _print_hash_multimap_sample(pt_hmmap);
            hash_multimap_destroy(pt_hmmap);
            hash_multimap_destroy(pt_hmmapex);
            pair_destroy(pt_pair);
        }
        /*hash_multimap_init_copy_range_ex*/
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, hash_sample_t);
            hash_multimap_t* pt_hmmapex = create_hash_multimap(int, hash_sample_t);
            pair_t* pt_pair = create_pair(int, hash_sample_t);
            hash_sample_t t_sample;
            if(pt_hmmap == NULL || pt_hmmapex == NULL || pt_pair == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            hash_multimap_init_ex(pt_hmmapex, 0, _hash_multimap_sample_hash, NULL);

            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 34))->_d_first = 43.4;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 34))->_l_second = 4509;*/
            t_sample._l_second = 4509;
            t_sample._d_first = 43.4;
            pair_make(pt_pair, 34, &t_sample);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 90))->_d_first = -1.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 90))->_l_second = 90;*/
            t_sample._l_second = 90;
            t_sample._d_first = -1.11;
            pair_make(pt_pair, 90, &t_sample);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 9))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 9))->_l_second = 50;*/
            t_sample._l_second = 50;
            t_sample._d_first = -5.11;
            pair_make(pt_pair, 9, &t_sample);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            _print_hash_multimap_sample(pt_hmmapex);

            hash_multimap_init_copy_range_ex(pt_hmmap,
                hash_multimap_begin(pt_hmmapex), hash_multimap_end(pt_hmmapex),
                100, _hash_multimap_sample_hash, NULL);
            _print_hash_multimap_sample(pt_hmmap);
            hash_multimap_destroy(pt_hmmap);
            hash_multimap_destroy(pt_hmmapex);
            pair_destroy(pt_pair);
        }
        /*hash_multimap_destroy           */
        /*hash_multimap_assign            */
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, hash_sample_t);
            hash_multimap_t* pt_hmmapex = create_hash_multimap(int, hash_sample_t);
            pair_t* pt_pair = create_pair(int, hash_sample_t);
            hash_sample_t t_sample;
            if(pt_hmmap == NULL || pt_hmmapex == NULL || pt_pair == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            hash_multimap_init_ex(pt_hmmap, 0, _hash_multimap_sample_hash, NULL);
            hash_multimap_init_ex(pt_hmmapex, 0, _hash_multimap_sample_hash, NULL);
            hash_multimap_assign(pt_hmmap, pt_hmmapex);
            _print_hash_multimap_sample(pt_hmmap);

            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 34))->_d_first = 43.4;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 34))->_l_second = 4509;*/
            t_sample._d_first = 43.4;
            t_sample._l_second = 4509;
            pair_make(pt_pair, 34, &t_sample);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 90))->_d_first = -1.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 90))->_l_second = 90;*/
            t_sample._d_first = -1.11;
            t_sample._l_second = 90;
            pair_make(pt_pair, 90, &t_sample);
            hash_multimap_insert(pt_hmmapex, pt_pair);

            hash_multimap_assign(pt_hmmap, pt_hmmapex);
            _print_hash_multimap_sample(pt_hmmap);

            hash_multimap_clear(pt_hmmapex);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 9))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 9))->_l_second = 50;*/
            t_sample._d_first = -5.11;
            t_sample._l_second = 50;
            pair_make(pt_pair, 9, &t_sample);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            pair_make(pt_pair, 56, &t_sample);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 56))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 56))->_l_second = 50;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 54))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 54))->_l_second = 50;*/
            t_sample._d_first = 45.209;
            t_sample._l_second = 0;
            pair_make(pt_pair, 78, &t_sample);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            hash_multimap_insert(pt_hmmapex, pt_pair);

            hash_multimap_assign(pt_hmmap, pt_hmmapex);
            _print_hash_multimap_sample(pt_hmmap);

            hash_multimap_clear(pt_hmmapex);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 100))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 100))->_l_second = 50;*/
            t_sample._d_first = 0.289;
            t_sample._l_second = 4523;
            pair_make(pt_pair, 100, &t_sample);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            hash_multimap_assign(pt_hmmap, pt_hmmapex);
            _print_hash_multimap_sample(pt_hmmap);

            hash_multimap_clear(pt_hmmapex);
            hash_multimap_assign(pt_hmmap, pt_hmmapex);
            _print_hash_multimap_sample(pt_hmmap);

            hash_multimap_destroy(pt_hmmap);
            hash_multimap_destroy(pt_hmmapex);
            pair_destroy(pt_pair);
        }
        /*hash_multimap_swap              */
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, hash_sample_t);
            hash_multimap_t* pt_hmmapex = create_hash_multimap(int, hash_sample_t);
            pair_t* pt_pair = create_pair(int, hash_sample_t);
            hash_sample_t t_sample;
            if(pt_hmmap == NULL || pt_hmmapex == NULL || pt_pair == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            hash_multimap_init_ex(pt_hmmap, 0, _hash_multimap_sample_hash, NULL);
            hash_multimap_init_ex(pt_hmmapex, 0, _hash_multimap_sample_hash, NULL);
            hash_multimap_swap(pt_hmmap, pt_hmmapex);
            _print_hash_multimap_sample(pt_hmmap);
            _print_hash_multimap_sample(pt_hmmapex);

            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 34))->_d_first = 43.4;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 34))->_l_second = 4509;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 90))->_d_first = -1.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 90))->_l_second = 90;*/
            t_sample._d_first = 43.3;
            t_sample._l_second = 2233;
            pair_make(pt_pair, 34, &t_sample);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            t_sample._d_first = -1.0002;
            t_sample._l_second = 8934;
            pair_make(pt_pair, 90, &t_sample);
            hash_multimap_insert(pt_hmmapex, pt_pair);

            hash_multimap_swap(pt_hmmap, pt_hmmapex);
            _print_hash_multimap_sample(pt_hmmap);
            _print_hash_multimap_sample(pt_hmmapex);

            hash_multimap_clear(pt_hmmapex);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 9))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 9))->_l_second = 50;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 56))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 56))->_l_second = 50;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 54))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 54))->_l_second = 50;*/
            t_sample._d_first = 45.22;
            t_sample._l_second = 802;
            pair_make(pt_pair, 4, &t_sample);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            t_sample._d_first = 90.33;
            t_sample._l_second = -8747;
            pair_make(pt_pair, 89, &t_sample);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            t_sample._d_first = 0.1;
            t_sample._l_second = 4556;
            pair_make(pt_pair, 12, &t_sample);
            hash_multimap_insert(pt_hmmapex, pt_pair);

            hash_multimap_swap(pt_hmmap, pt_hmmapex);
            _print_hash_multimap_sample(pt_hmmap);
            _print_hash_multimap_sample(pt_hmmapex);

            hash_multimap_clear(pt_hmmapex);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 100))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 100))->_l_second = 50;*/
            t_sample._d_first = -5.555;
            t_sample._l_second = 5453;
            pair_make(pt_pair, 100, &t_sample);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            hash_multimap_swap(pt_hmmap, pt_hmmapex);
            _print_hash_multimap_sample(pt_hmmap);
            _print_hash_multimap_sample(pt_hmmapex);

            hash_multimap_clear(pt_hmmapex);
            hash_multimap_swap(pt_hmmap, pt_hmmapex);
            _print_hash_multimap_sample(pt_hmmap);
            _print_hash_multimap_sample(pt_hmmapex);

            hash_multimap_destroy(pt_hmmap);
            hash_multimap_destroy(pt_hmmapex);
            pair_destroy(pt_pair);
        }
        /*hash_multimap_size              */
        /*hash_multimap_empty             */
        /*hash_multimap_max_size          */
        /*hash_multimap_bucket_count      */
        /*hash_multimap_hash              */
        /*hash_multimap_key_less          */
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, hash_sample_t);
            if(pt_hmmap == NULL)
            {
                return;
            }
            hash_multimap_init_ex(pt_hmmap, 0, _hash_multimap_sample_hash, fun_great_int);
            assert(hash_multimap_hash(pt_hmmap) == _hash_multimap_sample_hash &&
                hash_multimap_key_less(pt_hmmap) == fun_great_int);
            hash_multimap_destroy(pt_hmmap);
        }
        /*hash_multimap_resize            */
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, hash_sample_t);
            if(pt_hmmap == NULL)
            {
                return;
            }
            hash_multimap_init(pt_hmmap);
            _print_hash_multimap_sample(pt_hmmap);
            hash_multimap_resize(pt_hmmap, 70);
            _print_hash_multimap_sample(pt_hmmap);
            hash_multimap_resize(pt_hmmap, 100);
            _print_hash_multimap_sample(pt_hmmap);
            hash_multimap_resize(pt_hmmap, 30);
            _print_hash_multimap_sample(pt_hmmap);
            hash_multimap_resize(pt_hmmap, 0);
            _print_hash_multimap_sample(pt_hmmap);
            hash_multimap_destroy(pt_hmmap);
        }
        /*hash_multimap_equal             */
        /*hash_multimap_not_equal         */
        /*hash_multimap_less              */
        /*hash_multimap_less_equal        */
        /*hash_multimap_great             */
        /*hash_multimap_great_equal       */
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, hash_sample_t);
            hash_multimap_t* pt_hmmapex = create_hash_multimap(int, hash_sample_t);
            hash_sample_t t_sample;
            pair_t* pt_pair = create_pair(int, hash_sample_t);
            if(pt_hmmap == NULL || pt_hmmapex == NULL || pt_pair == NULL)
            {
                return;
            }
            hash_multimap_init_ex(pt_hmmap, 0, _hash_multimap_sample_hash, NULL);
            hash_multimap_init_ex(pt_hmmapex, 0, _hash_multimap_sample_hash, NULL);
            pair_init(pt_pair);

            _print_hash_multimap_sample(pt_hmmap);
            _print_hash_multimap_sample(pt_hmmapex);
            printf("equal: %d, not equal: %d, ",
                hash_multimap_equal(pt_hmmap, pt_hmmapex), hash_multimap_not_equal(pt_hmmap, pt_hmmapex));
            printf("less: %d, less equal: %d, ",
                hash_multimap_less(pt_hmmap, pt_hmmapex), hash_multimap_less_equal(pt_hmmap, pt_hmmapex));
            printf("great: %d, great equal: %d\n",
                hash_multimap_great(pt_hmmap, pt_hmmapex), hash_multimap_great_equal(pt_hmmap, pt_hmmapex));

            t_sample._d_first = 89.23;
            t_sample._l_second = -11002244;
            pair_make(pt_pair, 4, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            _print_hash_multimap_sample(pt_hmmap);
            _print_hash_multimap_sample(pt_hmmapex);
            printf("equal: %d, not equal: %d, ",
                hash_multimap_equal(pt_hmmap, pt_hmmapex), hash_multimap_not_equal(pt_hmmap, pt_hmmapex));
            printf("less: %d, less equal: %d, ",
                hash_multimap_less(pt_hmmap, pt_hmmapex), hash_multimap_less_equal(pt_hmmap, pt_hmmapex));
            printf("great: %d, great equal: %d\n",
                hash_multimap_great(pt_hmmap, pt_hmmapex), hash_multimap_great_equal(pt_hmmap, pt_hmmapex));

            hash_multimap_insert(pt_hmmapex, pt_pair);
            _print_hash_multimap_sample(pt_hmmap);
            _print_hash_multimap_sample(pt_hmmapex);
            printf("equal: %d, not equal: %d, ",
                hash_multimap_equal(pt_hmmap, pt_hmmapex), hash_multimap_not_equal(pt_hmmap, pt_hmmapex));
            printf("less: %d, less equal: %d, ",
                hash_multimap_less(pt_hmmap, pt_hmmapex), hash_multimap_less_equal(pt_hmmap, pt_hmmapex));
            printf("great: %d, great equal: %d\n",
                hash_multimap_great(pt_hmmap, pt_hmmapex), hash_multimap_great_equal(pt_hmmap, pt_hmmapex));

            t_sample._d_first = 90.2;
            t_sample._l_second = 5555555;
            pair_make(pt_pair, 2, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            t_sample._d_first = 2323.2323;
            t_sample._l_second = -10101010;
            pair_make(pt_pair, 3, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            t_sample._d_first = 10.0;
            t_sample._l_second = 10;
            pair_make(pt_pair, 10, &t_sample);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            _print_hash_multimap_sample(pt_hmmap);
            _print_hash_multimap_sample(pt_hmmapex);
            printf("equal: %d, not equal: %d, ",
                hash_multimap_equal(pt_hmmap, pt_hmmapex), hash_multimap_not_equal(pt_hmmap, pt_hmmapex));
            printf("less: %d, less equal: %d, ",
                hash_multimap_less(pt_hmmap, pt_hmmapex), hash_multimap_less_equal(pt_hmmap, pt_hmmapex));
            printf("great: %d, great equal: %d\n",
                hash_multimap_great(pt_hmmap, pt_hmmapex), hash_multimap_great_equal(pt_hmmap, pt_hmmapex));

            hash_multimap_destroy(pt_hmmap);
            hash_multimap_destroy(pt_hmmapex);
            pair_destroy(pt_pair);
        }
        /*hash_multimap_begin             */
        /*hash_multimap_end               */
        /*hash_multimap_find              */
        /*hash_multimap_count             */
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, hash_sample_t);
            pair_t* pt_pair = create_pair(int, hash_sample_t);
            hash_sample_t t_sample;
            iterator_t t_iter;
            if(pt_hmmap == NULL || pt_pair == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            hash_multimap_init_ex(pt_hmmap, 0, _hash_multimap_sample_hash, NULL);
            t_iter = hash_multimap_find(pt_hmmap, 0);
            if(iterator_equal(t_iter, hash_multimap_end(pt_hmmap)))
            {
                printf("not found! count : %u\n", hash_multimap_count(pt_hmmap, 0));
            }
            else
            {
                printf("found! count : %u\n", hash_multimap_count(pt_hmmap, 0));
            }

            /*((hash_sample_t*)hash_multimap_at(pt_hmmap, 9))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmap, 9))->_l_second = 50;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmap, 56))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmap, 56))->_l_second = 50;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmap, 54))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmap, 54))->_l_second = 50;*/
            t_sample._d_first = -5.44;
            t_sample._l_second = 89;
            pair_make(pt_pair, 9, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            t_sample._d_first = 902.22;
            t_sample._l_second = 122324;
            pair_make(pt_pair, 56, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            t_sample._d_first = 0.1212;
            t_sample._l_second = 33;
            pair_make(pt_pair, 56, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            t_sample._d_first = 45.3;
            t_sample._l_second = 90;
            pair_make(pt_pair, 54, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);

            t_iter = hash_multimap_find(pt_hmmap, 0);
            if(iterator_equal(t_iter, hash_multimap_end(pt_hmmap)))
            {
                printf("not found! count : %u\n", hash_multimap_count(pt_hmmap, 0));
            }
            else
            {
                printf("found! count : %u\n", hash_multimap_count(pt_hmmap, 0));
            }
            t_iter = hash_multimap_find(pt_hmmap, 9);
            if(iterator_equal(t_iter, hash_multimap_end(pt_hmmap)))
            {
                printf("not found! count : %u\n", hash_multimap_count(pt_hmmap, 9));
            }
            else
            {
                printf("found! count : %u\n", hash_multimap_count(pt_hmmap, 9));
            }

            hash_multimap_destroy(pt_hmmap);
            pair_destroy(pt_pair);
        }
        /*hash_multimap_equal_range       */
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, hash_sample_t);
            pair_t* pt_pair = create_pair(int, hash_sample_t);
            hash_sample_t t_sample;
            range_t t_range;
            if(pt_hmmap == NULL || pt_pair == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            hash_multimap_init_ex(pt_hmmap, 0, _hash_multimap_sample_hash, NULL);
            t_range = hash_multimap_equal_range(pt_hmmap, 0);
            assert(iterator_equal(t_range.t_begin, hash_multimap_end(pt_hmmap)) &&
                iterator_equal(t_range.t_begin, t_range.t_end));
            /*((hash_sample_t*)hash_multimap_at(pt_hmmap, 9))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmap, 9))->_l_second = 50;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmap, 56))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmap, 56))->_l_second = 50;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmap, 54))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmap, 54))->_l_second = 50;*/
            t_sample._d_first = -5.44;
            t_sample._l_second = 89;
            pair_make(pt_pair, 9, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            t_sample._d_first = 902.22;
            t_sample._l_second = 122324;
            pair_make(pt_pair, 56, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            t_sample._d_first = 0.1212;
            t_sample._l_second = 33;
            pair_make(pt_pair, 56, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            t_sample._d_first = 45.3;
            t_sample._l_second = 90;
            pair_make(pt_pair, 54, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            t_range = hash_multimap_equal_range(pt_hmmap, 0);
            assert(iterator_equal(t_range.t_begin, t_range.t_end));
            t_range = hash_multimap_equal_range(pt_hmmap, 54);
            assert(iterator_equal(iterator_next(t_range.t_begin), t_range.t_end));

            hash_multimap_destroy(pt_hmmap);
            pair_destroy(pt_pair);
        }
        /*hash_multimap_insert            */
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, hash_sample_t);
            pair_t* pt_pair = create_pair(int, hash_sample_t);
            hash_sample_t t_sample;
            if(pt_hmmap == NULL)
            {
                return;
            }
            hash_multimap_init_ex(pt_hmmap, 0, _hash_multimap_sample_hash, NULL);
            pair_init(pt_pair);
            _print_hash_multimap_sample(pt_hmmap);
            t_sample._d_first = 90.2;
            t_sample._l_second = 5555555;
            pair_make(pt_pair, 2, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            t_sample._d_first = 2323.2323;
            t_sample._l_second = -10101010;
            pair_make(pt_pair, 3, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            t_sample._d_first = 10.0;
            t_sample._l_second = 10;
            pair_make(pt_pair, 10, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            t_sample._d_first = 10.110;
            t_sample._l_second = 1011;
            pair_make(pt_pair, 10, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            _print_hash_multimap_sample(pt_hmmap);
            
            hash_multimap_destroy(pt_hmmap);
            pair_destroy(pt_pair);
        }
        /*hash_multimap_insert_range      */
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, hash_sample_t);
            hash_multimap_t* pt_hmmapex = create_hash_multimap(int, hash_sample_t);
            pair_t* pt_pair = create_pair(int, hash_sample_t);
            hash_sample_t t_sample;
            if(pt_hmmap == NULL || pt_hmmapex == NULL || pt_pair == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            hash_multimap_init_ex(pt_hmmap, 0, _hash_multimap_sample_hash, NULL);
            hash_multimap_init_ex(pt_hmmapex, 0, _hash_multimap_sample_hash, NULL);
            hash_multimap_insert_range(pt_hmmap,
                hash_multimap_begin(pt_hmmapex), hash_multimap_end(pt_hmmapex));
            _print_hash_multimap_sample(pt_hmmap);

            t_sample._d_first = -5.55;
            t_sample._l_second = 2344;
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 9))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 9))->_l_second = 50;*/
            pair_make(pt_pair, 9, &t_sample);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 6))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 6))->_l_second = 50;*/
            pair_make(pt_pair, 6, &t_sample);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 4))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 4))->_l_second = 50;*/
            pair_make(pt_pair, 4, &t_sample);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 19))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 19))->_l_second = 50;*/
            pair_make(pt_pair, -14, &t_sample);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 86))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 86))->_l_second = 50;*/
            pair_make(pt_pair, 86, &t_sample);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 7))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 7))->_l_second = 50;*/
            pair_make(pt_pair, 55, &t_sample);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 3))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 3))->_l_second = 50;*/
            pair_make(pt_pair, 5, &t_sample);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 56))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 56))->_l_second = 50;*/
            pair_make(pt_pair, 500, &t_sample);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 54))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 54))->_l_second = 50;*/
            pair_make(pt_pair, 60, &t_sample);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            _print_hash_multimap_sample(pt_hmmapex);

            hash_multimap_insert_range(pt_hmmap,
                hash_multimap_begin(pt_hmmapex), hash_multimap_begin(pt_hmmapex));
            _print_hash_multimap_sample(pt_hmmap);
            hash_multimap_insert_range(pt_hmmap,
                hash_multimap_begin(pt_hmmapex), iterator_advance(hash_multimap_begin(pt_hmmapex), 3));
            _print_hash_multimap_sample(pt_hmmap);
            hash_multimap_insert_range(pt_hmmap,
                iterator_advance(hash_multimap_begin(pt_hmmapex), 5),
                iterator_advance(hash_multimap_begin(pt_hmmapex), 7));
            _print_hash_multimap_sample(pt_hmmap);
            hash_multimap_insert_range(pt_hmmap, iterator_advance(hash_multimap_begin(pt_hmmapex), 8),
                hash_multimap_end(pt_hmmapex));
            _print_hash_multimap_sample(pt_hmmap);
            hash_multimap_insert_range(pt_hmmap, hash_multimap_end(pt_hmmapex), hash_multimap_end(pt_hmmapex));
            _print_hash_multimap_sample(pt_hmmap);

            hash_multimap_clear(pt_hmmap);
            hash_multimap_insert_range(pt_hmmap, hash_multimap_begin(pt_hmmapex), hash_multimap_end(pt_hmmapex));
            _print_hash_multimap_sample(pt_hmmap);

            hash_multimap_destroy(pt_hmmap);
            hash_multimap_destroy(pt_hmmapex);
            pair_destroy(pt_pair);
        }
        /*hash_multimap_erase             */
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, hash_sample_t);
            pair_t* pt_pair = create_pair(int, hash_sample_t);
            hash_sample_t t_sample;
            if(pt_hmmap == NULL || pt_pair == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            hash_multimap_init_ex(pt_hmmap, 0, _hash_multimap_sample_hash, NULL);
            hash_multimap_erase(pt_hmmap, 0);
            _print_hash_multimap_sample(pt_hmmap);
            t_sample._d_first = -5.55;
            t_sample._l_second = 2344;
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 9))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 9))->_l_second = 50;*/
            pair_make(pt_pair, 9, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 6))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 6))->_l_second = 50;*/
            pair_make(pt_pair, 6, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 4))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 4))->_l_second = 50;*/
            pair_make(pt_pair, 4, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 19))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 19))->_l_second = 50;*/
            pair_make(pt_pair, -14, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 86))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 86))->_l_second = 50;*/
            pair_make(pt_pair, 86, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            hash_multimap_insert(pt_hmmap, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 7))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 7))->_l_second = 50;*/
            pair_make(pt_pair, 55, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 3))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 3))->_l_second = 50;*/
            pair_make(pt_pair, 5, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 56))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 56))->_l_second = 50;*/
            pair_make(pt_pair, 500, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 54))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 54))->_l_second = 50;*/
            pair_make(pt_pair, 60, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            _print_hash_multimap_sample(pt_hmmap);
            hash_multimap_erase(pt_hmmap, 66);
            _print_hash_multimap_sample(pt_hmmap);
            hash_multimap_erase(pt_hmmap, 86);
            _print_hash_multimap_sample(pt_hmmap);
            hash_multimap_destroy(pt_hmmap);
            pair_destroy(pt_pair);
        }
        /*hash_multimap_erase_pos         */
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, hash_sample_t);
            pair_t* pt_pair = create_pair(int, hash_sample_t);
            hash_sample_t t_sample;
            if(pt_hmmap == NULL || pt_pair == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            hash_multimap_init_ex(pt_hmmap, 0, _hash_multimap_sample_hash, NULL);
            t_sample._d_first = -5.55;
            t_sample._l_second = 2344;
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 9))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 9))->_l_second = 50;*/
            pair_make(pt_pair, 9, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 6))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 6))->_l_second = 50;*/
            pair_make(pt_pair, 6, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 4))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 4))->_l_second = 50;*/
            pair_make(pt_pair, 4, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 19))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 19))->_l_second = 50;*/
            pair_make(pt_pair, -14, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 86))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 86))->_l_second = 50;*/
            pair_make(pt_pair, 86, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            hash_multimap_insert(pt_hmmap, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 7))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 7))->_l_second = 50;*/
            pair_make(pt_pair, 55, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 3))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 3))->_l_second = 50;*/
            pair_make(pt_pair, 5, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 56))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 56))->_l_second = 50;*/
            pair_make(pt_pair, 500, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 54))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 54))->_l_second = 50;*/
            pair_make(pt_pair, 60, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            _print_hash_multimap_sample(pt_hmmap);

            hash_multimap_erase_pos(pt_hmmap, hash_multimap_begin(pt_hmmap));
            _print_hash_multimap_sample(pt_hmmap);
            hash_multimap_erase_pos(pt_hmmap, iterator_advance(hash_multimap_begin(pt_hmmap), 3));
            _print_hash_multimap_sample(pt_hmmap);
            while(!hash_multimap_empty(pt_hmmap))
            {
                hash_multimap_erase_pos(pt_hmmap, hash_multimap_begin(pt_hmmap));
            }
            _print_hash_multimap_sample(pt_hmmap);
            hash_multimap_destroy(pt_hmmap);
            pair_destroy(pt_pair);
        }
        /*hash_multimap_erase_range       */
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, hash_sample_t);
            pair_t* pt_pair = create_pair(int, hash_sample_t);
            hash_sample_t t_sample;
            if(pt_hmmap == NULL || pt_pair == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            hash_multimap_init_ex(pt_hmmap, 0, _hash_multimap_sample_hash, NULL);
            hash_multimap_erase_range(pt_hmmap, hash_multimap_begin(pt_hmmap), hash_multimap_end(pt_hmmap));
            _print_hash_multimap_sample(pt_hmmap);
            t_sample._d_first = -5.55;
            t_sample._l_second = 2344;
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 9))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 9))->_l_second = 50;*/
            pair_make(pt_pair, 9, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 6))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 6))->_l_second = 50;*/
            pair_make(pt_pair, 6, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 4))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 4))->_l_second = 50;*/
            pair_make(pt_pair, 4, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 19))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 19))->_l_second = 50;*/
            pair_make(pt_pair, -14, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 86))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 86))->_l_second = 50;*/
            pair_make(pt_pair, 86, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            hash_multimap_insert(pt_hmmap, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 7))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 7))->_l_second = 50;*/
            pair_make(pt_pair, 55, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 3))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 3))->_l_second = 50;*/
            pair_make(pt_pair, 5, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 56))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 56))->_l_second = 50;*/
            pair_make(pt_pair, 500, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 54))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 54))->_l_second = 50;*/
            pair_make(pt_pair, 60, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            _print_hash_multimap_sample(pt_hmmap);
            hash_multimap_erase_range(pt_hmmap, hash_multimap_begin(pt_hmmap), hash_multimap_begin(pt_hmmap));
            _print_hash_multimap_sample(pt_hmmap);
            hash_multimap_erase_range(pt_hmmap,
                hash_multimap_begin(pt_hmmap), iterator_advance(hash_multimap_begin(pt_hmmap), 3));
            _print_hash_multimap_sample(pt_hmmap);
            hash_multimap_erase_range(pt_hmmap,
                iterator_next(hash_multimap_begin(pt_hmmap)),
                iterator_advance(hash_multimap_begin(pt_hmmap), 3));
            _print_hash_multimap_sample(pt_hmmap);
            hash_multimap_erase_range(pt_hmmap,
                iterator_advance(hash_multimap_begin(pt_hmmap), 2), hash_multimap_end(pt_hmmap));
            _print_hash_multimap_sample(pt_hmmap);
            hash_multimap_erase_range(pt_hmmap,
                hash_multimap_end(pt_hmmap), hash_multimap_end(pt_hmmap));
            _print_hash_multimap_sample(pt_hmmap);
            hash_multimap_erase_range(pt_hmmap,
                hash_multimap_begin(pt_hmmap), hash_multimap_end(pt_hmmap));
            _print_hash_multimap_sample(pt_hmmap);

            hash_multimap_destroy(pt_hmmap);
            pair_destroy(pt_pair);
        }
        /*hash_multimap_clear             */
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, hash_sample_t);
            pair_t* pt_pair = create_pair(int, hash_sample_t);
            hash_sample_t t_sample;
            if(pt_hmmap == NULL || pt_pair == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            hash_multimap_init_ex(pt_hmmap, 0, _hash_multimap_sample_hash, NULL);
            hash_multimap_clear(pt_hmmap);
            _print_hash_multimap_sample(pt_hmmap);
            t_sample._d_first = -5.55;
            t_sample._l_second = 2344;
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 9))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 9))->_l_second = 50;*/
            pair_make(pt_pair, 9, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 6))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 6))->_l_second = 50;*/
            pair_make(pt_pair, 6, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 4))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 4))->_l_second = 50;*/
            pair_make(pt_pair, 4, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 19))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 19))->_l_second = 50;*/
            pair_make(pt_pair, -14, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 86))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 86))->_l_second = 50;*/
            pair_make(pt_pair, 86, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            hash_multimap_insert(pt_hmmap, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 7))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 7))->_l_second = 50;*/
            pair_make(pt_pair, 55, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 3))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 3))->_l_second = 50;*/
            pair_make(pt_pair, 5, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 56))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 56))->_l_second = 50;*/
            pair_make(pt_pair, 500, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 54))->_d_first = -5.11;*/
            /*((hash_sample_t*)hash_multimap_at(pt_hmmapex, 54))->_l_second = 50;*/
            pair_make(pt_pair, 60, &t_sample);
            hash_multimap_insert(pt_hmmap, pt_pair);
            _print_hash_multimap_sample(pt_hmmap);
            hash_multimap_clear(pt_hmmap);
            _print_hash_multimap_sample(pt_hmmap);

            hash_multimap_destroy(pt_hmmap);
            pair_destroy(pt_pair);
        }
    }
    /* cstl built-in */
    {
        /*create_hash_multimap            */
        /*hash_multimap_init              */
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, list_t<int>);
            list_t* pt_list = create_list(int);
            pair_t* pt_pair = create_pair(int, list_t<int>);
            if(pt_hmmap == NULL || pt_list == NULL || pt_pair == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            list_init(pt_list);
            hash_multimap_init(pt_hmmap);

            list_push_back(pt_list, 10);
            list_push_back(pt_list, 12);
            list_push_back(pt_list, 49230);
            list_push_back(pt_list, 2);
            list_push_back(pt_list, 0);
            pair_make(pt_pair, 10, pt_list);
            hash_multimap_insert(pt_hmmap, pt_pair);

            list_clear(pt_list);
            list_push_back(pt_list, 234);
            list_push_back(pt_list, 111);
            pair_make(pt_pair, 87, pt_list);
            hash_multimap_insert(pt_hmmap, pt_pair);

            list_clear(pt_list);
            list_push_back(pt_list, 1111);
            list_push_back(pt_list, 45);
            list_push_back(pt_list, 12345);
            list_push_back(pt_list, -83);
            list_push_back(pt_list, -3434);
            list_push_back(pt_list, 222);
            pair_make(pt_pair, 9, pt_list);
            hash_multimap_insert(pt_hmmap, pt_pair);

            _print_hash_multimap_cstl(pt_hmmap);
            hash_multimap_destroy(pt_hmmap);
            list_destroy(pt_list);
            pair_destroy(pt_pair);
        }
        /*hash_multimap_init_ex           */
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, list_t<int>);
            list_t* pt_list = create_list(int);
            pair_t* pt_pair = create_pair(int, list_t<int>);
            if(pt_hmmap == NULL || pt_list == NULL || pt_pair == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            list_init(pt_list);
            hash_multimap_init_ex(pt_hmmap, 0, _hash_multimap_cstl_hash, NULL);

            list_push_back(pt_list, 10);
            list_push_back(pt_list, 12);
            list_push_back(pt_list, 49230);
            list_push_back(pt_list, 2);
            list_push_back(pt_list, 0);
            pair_make(pt_pair, 10, pt_list);
            hash_multimap_insert(pt_hmmap, pt_pair);

            list_clear(pt_list);
            list_push_back(pt_list, 234);
            list_push_back(pt_list, 111);
            pair_make(pt_pair, 87, pt_list);
            hash_multimap_insert(pt_hmmap, pt_pair);

            list_clear(pt_list);
            list_push_back(pt_list, 1111);
            list_push_back(pt_list, 45);
            list_push_back(pt_list, 12345);
            list_push_back(pt_list, -83);
            list_push_back(pt_list, -3434);
            list_push_back(pt_list, 222);
            pair_make(pt_pair, 9, pt_list);
            hash_multimap_insert(pt_hmmap, pt_pair);

            _print_hash_multimap_cstl(pt_hmmap);
            hash_multimap_destroy(pt_hmmap);
            list_destroy(pt_list);
            pair_destroy(pt_pair);
        }
        /*hash_multimap_init_copy         */
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, list_t<int>);
            hash_multimap_t* pt_hmmapex = create_hash_multimap(int, list_t<int>);
            list_t* pt_list = create_list(int);
            pair_t* pt_pair = create_pair(int, list_t<int>);
            if(pt_hmmap == NULL || pt_hmmapex == NULL || pt_list == NULL || pt_pair == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            list_init(pt_list);
            hash_multimap_init_ex(pt_hmmapex, 0, _hash_multimap_cstl_hash, NULL);

            list_push_back(pt_list, 10);
            list_push_back(pt_list, 12);
            list_push_back(pt_list, 49230);
            list_push_back(pt_list, 2);
            list_push_back(pt_list, 0);
            pair_make(pt_pair, 10, pt_list);
            hash_multimap_insert(pt_hmmapex, pt_pair);

            list_clear(pt_list);
            list_push_back(pt_list, 234);
            list_push_back(pt_list, 111);
            pair_make(pt_pair, 87, pt_list);
            hash_multimap_insert(pt_hmmapex, pt_pair);

            list_clear(pt_list);
            list_push_back(pt_list, 1111);
            list_push_back(pt_list, 45);
            list_push_back(pt_list, 12345);
            list_push_back(pt_list, -83);
            list_push_back(pt_list, -3434);
            list_push_back(pt_list, 222);
            pair_make(pt_pair, 9, pt_list);
            hash_multimap_insert(pt_hmmapex, pt_pair);

            hash_multimap_init_copy(pt_hmmap, pt_hmmapex);
            _print_hash_multimap_cstl(pt_hmmap);
            hash_multimap_destroy(pt_hmmap);
            hash_multimap_destroy(pt_hmmapex);
            pair_destroy(pt_pair);
            list_destroy(pt_list);
        }
        /*hash_multimap_init_copy_range   */
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, list_t<int>);
            hash_multimap_t* pt_hmmapex = create_hash_multimap(int, list_t<int>);
            list_t* pt_list = create_list(int);
            pair_t* pt_pair = create_pair(int, list_t<int>);
            if(pt_hmmap == NULL || pt_hmmapex == NULL || pt_list == NULL || pt_pair == NULL)
            {
                return;
            }
            list_init(pt_list);
            pair_init(pt_pair);
            hash_multimap_init_ex(pt_hmmapex, 100, _hash_multimap_cstl_hash, NULL);

            list_push_back(pt_list, 10);
            list_push_back(pt_list, 12);
            list_push_back(pt_list, 49230);
            list_push_back(pt_list, 2);
            list_push_back(pt_list, 0);
            pair_make(pt_pair, 10, pt_list);
            hash_multimap_insert(pt_hmmapex, pt_pair);

            list_clear(pt_list);
            list_push_back(pt_list, 234);
            list_push_back(pt_list, 111);
            pair_make(pt_pair, 45, pt_list);
            hash_multimap_insert(pt_hmmapex, pt_pair);

            list_push_back(pt_list, 1111);
            list_push_back(pt_list, 45);
            list_push_back(pt_list, 12345);
            list_push_back(pt_list, -83);
            list_push_back(pt_list, -3434);
            list_push_back(pt_list, 222);
            pair_make(pt_pair, 9, pt_list);
            hash_multimap_insert(pt_hmmapex, pt_pair);

            list_clear(pt_list);
            list_push_back(pt_list, 1124);
            list_push_back(pt_list, 0);
            list_push_back(pt_list, 11);
            list_push_back(pt_list, 0);
            list_push_back(pt_list, 0);
            pair_make(pt_pair, 3, pt_list);
            hash_multimap_insert(pt_hmmapex, pt_pair);

            list_clear(pt_list);
            list_push_back(pt_list, 4);
            pair_make(pt_pair, 4, pt_list);
            hash_multimap_insert(pt_hmmapex, pt_pair);

            hash_multimap_init_copy_range(pt_hmmap,
                hash_multimap_begin(pt_hmmapex), hash_multimap_end(pt_hmmapex));
            _print_hash_multimap_cstl(pt_hmmapex);
            _print_hash_multimap_cstl(pt_hmmap);

            hash_multimap_destroy(pt_hmmap);
            hash_multimap_destroy(pt_hmmapex);
            list_destroy(pt_list);
            pair_destroy(pt_pair);
        }
        /*hash_multimap_init_copy_range_ex*/
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, list_t<int>);
            hash_multimap_t* pt_hmmapex = create_hash_multimap(int, list_t<int>);
            list_t* pt_list = create_list(int);
            pair_t* pt_pair = create_pair(int, list_t<int>);
            if(pt_hmmap == NULL || pt_hmmapex == NULL || pt_list == NULL || pt_pair == NULL)
            {
                return;
            }
            list_init(pt_list);
            pair_init(pt_pair);
            hash_multimap_init_ex(pt_hmmapex, 100, _hash_multimap_cstl_hash, NULL);

            list_push_back(pt_list, 10);
            list_push_back(pt_list, 12);
            list_push_back(pt_list, 49230);
            list_push_back(pt_list, 2);
            list_push_back(pt_list, 0);
            pair_make(pt_pair, 10, pt_list);
            hash_multimap_insert(pt_hmmapex, pt_pair);

            list_clear(pt_list);
            list_push_back(pt_list, 234);
            list_push_back(pt_list, 111);
            pair_make(pt_pair, 45, pt_list);
            hash_multimap_insert(pt_hmmapex, pt_pair);

            list_push_back(pt_list, 1111);
            list_push_back(pt_list, 45);
            list_push_back(pt_list, 12345);
            list_push_back(pt_list, -83);
            list_push_back(pt_list, -3434);
            list_push_back(pt_list, 222);
            pair_make(pt_pair, 9, pt_list);
            hash_multimap_insert(pt_hmmapex, pt_pair);

            list_clear(pt_list);
            list_push_back(pt_list, 1124);
            list_push_back(pt_list, 0);
            list_push_back(pt_list, 11);
            list_push_back(pt_list, 0);
            list_push_back(pt_list, 0);
            pair_make(pt_pair, 3, pt_list);
            hash_multimap_insert(pt_hmmapex, pt_pair);

            list_clear(pt_list);
            list_push_back(pt_list, 4);
            pair_make(pt_pair, 4, pt_list);
            hash_multimap_insert(pt_hmmapex, pt_pair);

            hash_multimap_init_copy_range_ex(pt_hmmap,
                hash_multimap_begin(pt_hmmapex), hash_multimap_end(pt_hmmapex),
                0, _hash_multimap_cstl_hash, NULL);
            _print_hash_multimap_cstl(pt_hmmapex);
            _print_hash_multimap_cstl(pt_hmmap);

            hash_multimap_destroy(pt_hmmap);
            hash_multimap_destroy(pt_hmmapex);
            list_destroy(pt_list);
            pair_destroy(pt_pair);
        }
        /*hash_multimap_destroy           */
        /*hash_multimap_assign            */
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, list_t<int>);
            hash_multimap_t* pt_hmmapex = create_hash_multimap(int, list_t<int>);
            pair_t* pt_pair = create_pair(int, list_t<int>);
            list_t* pt_list = create_list(int);
            if(pt_hmmap == NULL || pt_hmmapex == NULL || pt_list == NULL || pt_pair == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            list_init(pt_list);
            hash_multimap_init_ex(pt_hmmap, 0, _hash_multimap_cstl_hash, NULL);
            hash_multimap_init_ex(pt_hmmapex, 100, _hash_multimap_cstl_hash, NULL);
            hash_multimap_assign(pt_hmmap, pt_hmmapex);
            _print_hash_multimap_cstl(pt_hmmap);

            list_push_back(pt_list, 3234);
            list_push_back(pt_list, -876);
            list_push_back(pt_list, 4);
            pair_make(pt_pair, 12, pt_list);
            hash_multimap_insert(pt_hmmapex, pt_pair);

            list_clear(pt_list);
            list_push_back(pt_list, -79);
            list_push_back(pt_list, 3);
            pair_make(pt_pair, 2, pt_list);
            hash_multimap_insert(pt_hmmapex, pt_pair);

            hash_multimap_assign(pt_hmmap, pt_hmmapex);
            _print_hash_multimap_cstl(pt_hmmap);

            hash_multimap_clear(pt_hmmapex);
            list_clear(pt_list);
            list_push_back(pt_list, 78);
            list_push_back(pt_list, 2);
            list_push_back(pt_list, 34);
            list_push_back(pt_list, 2);
            list_push_back(pt_list, 567);
            list_push_back(pt_list, 445);
            pair_make(pt_pair, 55, pt_list);
            hash_multimap_insert(pt_hmmapex, pt_pair);

            list_clear(pt_list);
            list_push_back(pt_list, 4);
            list_push_back(pt_list, 4);
            pair_make(pt_pair, 4, pt_list);
            hash_multimap_insert(pt_hmmapex, pt_pair);

            list_clear(pt_list);
            pair_make(pt_pair, 22, pt_list);
            hash_multimap_insert(pt_hmmapex, pt_pair);

            list_clear(pt_list);
            list_push_back(pt_list, 100);
            list_push_back(pt_list, 200);
            list_push_back(pt_list, 300);
            pair_make(pt_pair, 5, pt_list);
            hash_multimap_insert(pt_hmmapex, pt_pair);

            list_clear(pt_list);
            list_push_back(pt_list, 222);
            pair_make(pt_pair, 45, pt_list);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            hash_multimap_assign(pt_hmmap, pt_hmmapex);
            _print_hash_multimap_cstl(pt_hmmap);

            hash_multimap_clear(pt_hmmapex);
            list_clear(pt_list);
            list_push_back(pt_list, 0);
            list_push_back(pt_list, 2);
            list_push_back(pt_list, 3);
            pair_make(pt_pair, 444, pt_list);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            hash_multimap_assign(pt_hmmap, pt_hmmapex);
            _print_hash_multimap_cstl(pt_hmmap);

            hash_multimap_clear(pt_hmmapex);
            hash_multimap_assign(pt_hmmap, pt_hmmapex);
            _print_hash_multimap_cstl(pt_hmmap);

            hash_multimap_destroy(pt_hmmap);
            hash_multimap_destroy(pt_hmmapex);
            list_destroy(pt_list);
            pair_destroy(pt_pair);
        }
        /*hash_multimap_swap              */
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, list_t<int>);
            hash_multimap_t* pt_hmmapex = create_hash_multimap(int, list_t<int>);
            pair_t* pt_pair = create_pair(int, list_t<int>);
            list_t* pt_list = create_list(int);
            if(pt_hmmap == NULL || pt_hmmapex == NULL || pt_list == NULL || pt_pair == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            list_init(pt_list);
            hash_multimap_init_ex(pt_hmmap, 0, _hash_multimap_cstl_hash, NULL);
            hash_multimap_init_ex(pt_hmmapex, 100, _hash_multimap_cstl_hash, NULL);
            hash_multimap_swap(pt_hmmap, pt_hmmapex);
            _print_hash_multimap_cstl(pt_hmmap);
            _print_hash_multimap_cstl(pt_hmmapex);

            list_push_back(pt_list, 3234);
            list_push_back(pt_list, -876);
            list_push_back(pt_list, 4);
            pair_make(pt_pair, 12, pt_list);
            hash_multimap_insert(pt_hmmapex, pt_pair);

            list_clear(pt_list);
            list_push_back(pt_list, -79);
            list_push_back(pt_list, 3);
            pair_make(pt_pair, 2, pt_list);
            hash_multimap_insert(pt_hmmapex, pt_pair);

            hash_multimap_swap(pt_hmmap, pt_hmmapex);
            _print_hash_multimap_cstl(pt_hmmap);
            _print_hash_multimap_cstl(pt_hmmapex);

            hash_multimap_clear(pt_hmmapex);
            list_clear(pt_list);
            list_push_back(pt_list, 78);
            list_push_back(pt_list, 2);
            list_push_back(pt_list, 34);
            list_push_back(pt_list, 2);
            list_push_back(pt_list, 567);
            list_push_back(pt_list, 445);
            pair_make(pt_pair, 55, pt_list);
            hash_multimap_insert(pt_hmmapex, pt_pair);

            list_clear(pt_list);
            list_push_back(pt_list, 4);
            list_push_back(pt_list, 4);
            pair_make(pt_pair, 4, pt_list);
            hash_multimap_insert(pt_hmmapex, pt_pair);

            list_clear(pt_list);
            pair_make(pt_pair, 22, pt_list);
            hash_multimap_insert(pt_hmmapex, pt_pair);

            list_clear(pt_list);
            list_push_back(pt_list, 100);
            list_push_back(pt_list, 200);
            list_push_back(pt_list, 300);
            pair_make(pt_pair, 5, pt_list);
            hash_multimap_insert(pt_hmmapex, pt_pair);

            list_clear(pt_list);
            list_push_back(pt_list, 222);
            pair_make(pt_pair, 45, pt_list);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            hash_multimap_swap(pt_hmmap, pt_hmmapex);
            _print_hash_multimap_cstl(pt_hmmap);
            _print_hash_multimap_cstl(pt_hmmapex);

            hash_multimap_clear(pt_hmmapex);
            list_clear(pt_list);
            list_push_back(pt_list, 0);
            list_push_back(pt_list, 2);
            list_push_back(pt_list, 3);
            pair_make(pt_pair, 444, pt_list);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            hash_multimap_swap(pt_hmmap, pt_hmmapex);
            _print_hash_multimap_cstl(pt_hmmap);
            _print_hash_multimap_cstl(pt_hmmapex);

            hash_multimap_clear(pt_hmmapex);
            hash_multimap_swap(pt_hmmap, pt_hmmapex);
            _print_hash_multimap_cstl(pt_hmmap);
            _print_hash_multimap_cstl(pt_hmmapex);

            hash_multimap_destroy(pt_hmmap);
            hash_multimap_destroy(pt_hmmapex);
            list_destroy(pt_list);
            pair_destroy(pt_pair);
        }
        /*hash_multimap_size              */
        /*hash_multimap_empty             */
        /*hash_multimap_max_size          */
        /*hash_multimap_bucket_count      */
        /*hash_multimap_hash              */
        /*hash_multimap_key_less          */
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, list_t<int>);
            if(pt_hmmap == NULL)
            {
                return;
            }
            hash_multimap_init_ex(pt_hmmap, 100, _hash_multimap_cstl_hash, fun_great_int);
            assert(hash_multimap_hash(pt_hmmap) == _hash_multimap_cstl_hash &&
                hash_multimap_key_less(pt_hmmap) == fun_great_int);
            hash_multimap_destroy(pt_hmmap);
        }
        /*hash_multimap_resize            */
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, list_t<int>);
            if(pt_hmmap == NULL)
            {
                return;
            }
            hash_multimap_init_ex(pt_hmmap, 0, _hash_multimap_cstl_hash, NULL);
            _print_hash_multimap_cstl(pt_hmmap);
            hash_multimap_resize(pt_hmmap, 50);
            _print_hash_multimap_cstl(pt_hmmap);
            hash_multimap_resize(pt_hmmap, 100);
            _print_hash_multimap_cstl(pt_hmmap);
            hash_multimap_resize(pt_hmmap, 700);
            _print_hash_multimap_cstl(pt_hmmap);
            hash_multimap_resize(pt_hmmap, 30);
            _print_hash_multimap_cstl(pt_hmmap);
            hash_multimap_resize(pt_hmmap, 0);
            _print_hash_multimap_cstl(pt_hmmap);
            hash_multimap_destroy(pt_hmmap);
        }
        /*hash_multimap_equal             */
        /*hash_multimap_not_equal         */
        /*hash_multimap_less              */
        /*hash_multimap_less_equal        */
        /*hash_multimap_great             */
        /*hash_multimap_great_equal       */
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, list_t<int>);
            hash_multimap_t* pt_hmmapex = create_hash_multimap(int, list_t<int>);
            pair_t* pt_pair = create_pair(int, list_t<int>);
            list_t* pt_list = create_list(int);
            if(pt_hmmap == NULL || pt_hmmapex == NULL || pt_pair == NULL || pt_list == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            list_init(pt_list);
            hash_multimap_init_ex(pt_hmmap, 0, _hash_multimap_cstl_hash, NULL);
            hash_multimap_init_ex(pt_hmmapex, 0, _hash_multimap_cstl_hash, NULL);
            _print_hash_multimap_cstl(pt_hmmap);
            _print_hash_multimap_cstl(pt_hmmapex);
            printf("equal: %d, not equal: %d, ",
                hash_multimap_equal(pt_hmmap, pt_hmmapex), hash_multimap_not_equal(pt_hmmap, pt_hmmapex));
            printf("less: %d, less equal: %d, ",
                hash_multimap_less(pt_hmmap, pt_hmmapex), hash_multimap_less_equal(pt_hmmap, pt_hmmapex));
            printf("great: %d, great equal: %d\n",
                hash_multimap_great(pt_hmmap, pt_hmmapex), hash_multimap_great_equal(pt_hmmap, pt_hmmapex));

            list_clear(pt_list);
            list_push_back(pt_list, 56);
            list_push_back(pt_list, 11);
            list_push_back(pt_list, 90);
            pair_make(pt_pair, 34, pt_list);
            hash_multimap_insert(pt_hmmap, pt_pair);
            _print_hash_multimap_cstl(pt_hmmap);
            _print_hash_multimap_cstl(pt_hmmapex);
            printf("equal: %d, not equal: %d, ",
                hash_multimap_equal(pt_hmmap, pt_hmmapex), hash_multimap_not_equal(pt_hmmap, pt_hmmapex));
            printf("less: %d, less equal: %d, ",
                hash_multimap_less(pt_hmmap, pt_hmmapex), hash_multimap_less_equal(pt_hmmap, pt_hmmapex));
            printf("great: %d, great equal: %d\n",
                hash_multimap_great(pt_hmmap, pt_hmmapex), hash_multimap_great_equal(pt_hmmap, pt_hmmapex));

            list_clear(pt_list);
            list_push_back(pt_list, 5006);
            list_push_back(pt_list, -11);
            list_push_back(pt_list, 0);
            list_push_back(pt_list, 43);
            list_push_back(pt_list, -278484);
            pair_make(pt_pair, 34, pt_list);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            _print_hash_multimap_cstl(pt_hmmap);
            _print_hash_multimap_cstl(pt_hmmapex);
            printf("equal: %d, not equal: %d, ",
                hash_multimap_equal(pt_hmmap, pt_hmmapex), hash_multimap_not_equal(pt_hmmap, pt_hmmapex));
            printf("less: %d, less equal: %d, ",
                hash_multimap_less(pt_hmmap, pt_hmmapex), hash_multimap_less_equal(pt_hmmap, pt_hmmapex));
            printf("great: %d, great equal: %d\n",
                hash_multimap_great(pt_hmmap, pt_hmmapex), hash_multimap_great_equal(pt_hmmap, pt_hmmapex));

            list_clear(pt_list);
            pair_make(pt_pair, 20, pt_list);
            hash_multimap_insert(pt_hmmap, pt_pair);
            list_clear(pt_list);
            list_push_back(pt_list, 232);
            list_push_back(pt_list, 4455);
            list_push_back(pt_list, 8989);
            pair_make(pt_pair, 10, pt_list);
            hash_multimap_insert(pt_hmmap, pt_pair);
            list_clear(pt_list);
            list_push_back(pt_list, 0);
            list_push_back(pt_list, 0);
            pair_make(pt_pair, 50, pt_list);
            hash_multimap_insert(pt_hmmapex, pt_pair);
            _print_hash_multimap_cstl(pt_hmmap);
            _print_hash_multimap_cstl(pt_hmmapex);
            printf("equal: %d, not equal: %d, ",
                hash_multimap_equal(pt_hmmap, pt_hmmapex), hash_multimap_not_equal(pt_hmmap, pt_hmmapex));
            printf("less: %d, less equal: %d, ",
                hash_multimap_less(pt_hmmap, pt_hmmapex), hash_multimap_less_equal(pt_hmmap, pt_hmmapex));
            printf("great: %d, great equal: %d\n",
                hash_multimap_great(pt_hmmap, pt_hmmapex), hash_multimap_great_equal(pt_hmmap, pt_hmmapex));

            hash_multimap_destroy(pt_hmmap);
            hash_multimap_destroy(pt_hmmapex);
            pair_destroy(pt_pair);
            list_destroy(pt_list);
        }
        /*hash_multimap_begin             */
        /*hash_multimap_end               */
        /*hash_multimap_find              */
        /*hash_multimap_count             */
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, list_t<int>);
            pair_t* pt_pair = create_pair(int, list_t<int>);
            list_t* pt_list = create_list(int);
            iterator_t t_iter;
            if(pt_hmmap == NULL || pt_pair == NULL || pt_list == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            list_init(pt_list);
            hash_multimap_init_ex(pt_hmmap, 0, _hash_multimap_cstl_hash, NULL);

            t_iter = hash_multimap_find(pt_hmmap, 0);
            if(iterator_equal(t_iter, hash_multimap_end(pt_hmmap)))
            {
                printf("not found! count : %u\n", hash_multimap_count(pt_hmmap, 0));
            }
            else
            {
                printf("found! count : %u\n", hash_multimap_count(pt_hmmap, 0));
            }
            list_clear(pt_list);
            list_push_back(pt_list, 3);
            list_push_back(pt_list, 0);
            list_push_back(pt_list, 112);
            list_push_back(pt_list, 909);
            pair_make(pt_pair, 4, pt_list);
            hash_multimap_insert(pt_hmmap, pt_pair);
            list_clear(pt_list);
            list_push_back(pt_list, 122);
            list_push_back(pt_list, 89);
            list_push_back(pt_list, 0);
            pair_make(pt_pair, 23, pt_list);
            hash_multimap_insert(pt_hmmap, pt_pair);
            list_clear(pt_list);
            list_push_back(pt_list, 9);
            pair_make(pt_pair, 2, pt_list);
            hash_multimap_insert(pt_hmmap, pt_pair);

            t_iter = hash_multimap_find(pt_hmmap, 0);
            if(iterator_equal(t_iter, hash_multimap_end(pt_hmmap)))
            {
                printf("not found! count : %u\n", hash_multimap_count(pt_hmmap, 0));
            }
            else
            {
                printf("found! count : %u\n", hash_multimap_count(pt_hmmap, 0));
            }
            t_iter = hash_multimap_find(pt_hmmap, 4);
            if(iterator_equal(t_iter, hash_multimap_end(pt_hmmap)))
            {
                printf("not found! count : %u\n", hash_multimap_count(pt_hmmap, 4));
            }
            else
            {
                printf("found! count : %u\n", hash_multimap_count(pt_hmmap, 4));
            }

            hash_multimap_destroy(pt_hmmap);
            list_destroy(pt_list);
            pair_destroy(pt_pair);
        }
        /*hash_multimap_equal_range       */
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, list_t<int>);
            pair_t* pt_pair = create_pair(int, list_t<int>);
            list_t* pt_list = create_list(int);
            range_t t_range;
            if(pt_hmmap == NULL || pt_pair == NULL || pt_list == NULL)
            {
                return;
            }
            hash_multimap_init_ex(pt_hmmap, 0, _hash_multimap_cstl_hash, NULL);
            pair_init(pt_pair);
            list_init(pt_list);
            t_range = hash_multimap_equal_range(pt_hmmap, 4);
            assert(iterator_equal(t_range.t_begin, hash_multimap_end(pt_hmmap)) &&
                iterator_equal(t_range.t_begin, t_range.t_end));
            list_clear(pt_list);
            list_push_back(pt_list, 3);
            list_push_back(pt_list, 0);
            list_push_back(pt_list, 112);
            list_push_back(pt_list, 909);
            pair_make(pt_pair, 4, pt_list);
            hash_multimap_insert(pt_hmmap, pt_pair);
            list_clear(pt_list);
            list_push_back(pt_list, 122);
            list_push_back(pt_list, 89);
            list_push_back(pt_list, 0);
            pair_make(pt_pair, 23, pt_list);
            hash_multimap_insert(pt_hmmap, pt_pair);
            list_clear(pt_list);
            list_push_back(pt_list, 9);
            pair_make(pt_pair, 2, pt_list);
            hash_multimap_insert(pt_hmmap, pt_pair);
            t_range = hash_multimap_equal_range(pt_hmmap, 10);
            assert(iterator_equal(t_range.t_begin, t_range.t_end));
            t_range = hash_multimap_equal_range(pt_hmmap, 4);
            assert(iterator_equal(iterator_next(t_range.t_begin), t_range.t_end));
            hash_multimap_destroy(pt_hmmap);
            pair_destroy(pt_pair);
            list_destroy(pt_list);
        }
        /*hash_multimap_insert            */
        {
            hash_multimap_t* pt_hmmap = create_hash_multimap(int, list_t<int>);
            pair_t* pt_pair = create_pair(int, list_t<int>);
            list_t* pt_list = create_list(int);
            if(pt_hmmap == NULL || pt_pair == NULL || pt_list == NULL)
            {
                return;
            }
            hash_multimap_init_ex(pt_hmmap, 0, _hash_multimap_cstl_hash, NULL);
            pair_init(pt_pair);
            list_init(pt_list);
            list_clear(pt_list);
            _print_hash_multimap_cstl(pt_hmmap);
            list_push_back(pt_list, 3);
            list_push_back(pt_list, 0);
            list_push_back(pt_list, 112);
            list_push_back(pt_list, 909);
            pair_make(pt_pair, 4, pt_list);
            hash_multimap_insert(pt_hmmap, pt_pair);
            hash_multimap_insert(pt_hmmap, pt_pair);
            hash_multimap_insert(pt_hmmap, pt_pair);
            list_clear(pt_list);
            list_push_back(pt_list, 122);
            list_push_back(pt_list, 89);
            list_push_back(pt_list, 0);
            pair_make(pt_pair, 23, pt_list);
            hash_multimap_insert(pt_hmmap, pt_pair);
            list_clear(pt_list);
            list_push_back(pt_list, 9);
            pair_make(pt_pair, 2, pt_list);
            hash_multimap_insert(pt_hmmap, pt_pair);
            _print_hash_multimap_cstl(pt_hmmap);
            hash_multimap_destroy(pt_hmmap);
            pair_destroy(pt_pair);
            list_destroy(pt_list);
        }
        /*hash_multimap_insert_range      */
        /*hash_multimap_erase             */
        /*hash_multimap_erase_pos         */
        /*hash_multimap_erase_range       */
        /*hash_multimap_clear             */
    }
    /* c-string */
    {
    }
    /*create_hash_multimap            */
    /*hash_multimap_init              */
    /*hash_multimap_init_ex           */
    /*hash_multimap_init_copy         */
    /*hash_multimap_init_copy_range   */
    /*hash_multimap_init_copy_range_ex*/
    /*hash_multimap_destroy           */
    /*hash_multimap_assign            */
    /*hash_multimap_swap              */
    /*hash_multimap_size              */
    /*hash_multimap_empty             */
    /*hash_multimap_max_size          */
    /*hash_multimap_bucket_count      */
    /*hash_multimap_hash              */
    /*hash_multimap_key_less          */
    /*hash_multimap_resize            */
    /*hash_multimap_equal             */
    /*hash_multimap_not_equal         */
    /*hash_multimap_less              */
    /*hash_multimap_less_equal        */
    /*hash_multimap_great             */
    /*hash_multimap_great_equal       */
    /*hash_multimap_begin             */
    /*hash_multimap_end               */
    /*hash_multimap_find              */
    /*hash_multimap_count             */
    /*hash_multimap_equal_range       */
    /*hash_multimap_insert            */
    /*hash_multimap_insert_range      */
    /*hash_multimap_erase             */
    /*hash_multimap_erase_pos         */
    /*hash_multimap_erase_range       */
    /*hash_multimap_clear             */
}

/** local function implementation section **/

/** eof **/

