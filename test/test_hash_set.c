/*
 *  The implementation of hash_set_t and hash_multiset_t test.
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
#include "chash_set.h"
#include "test_hashtable.h"
#include "cfunctional.h"
#include "test_hash_set.h"

/** local constant declaration and local macro section **/

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
        {
            hash_set_t* pt_hset = create_hash_set(int);
            hash_set_t* pt_hsetex = create_hash_set(int);
            if(pt_hset == NULL || pt_hsetex == NULL)
            {
                return;
            }
            hash_set_init(pt_hset);
            hash_set_init_ex(pt_hsetex, 90, NULL, NULL);
            hash_set_swap(pt_hset, pt_hsetex);
            _print_hash_set_c(pt_hset, "%d, ", int);
            _print_hash_set_c(pt_hsetex, "%d, ", int);

            hash_set_insert(pt_hsetex, 450);
            hash_set_insert(pt_hsetex, -45);
            hash_set_insert(pt_hsetex, 90);
            hash_set_insert(pt_hsetex, 233);
            hash_set_insert(pt_hsetex, 109);
            hash_set_insert(pt_hsetex, 2);
            hash_set_swap(pt_hset, pt_hsetex);
            _print_hash_set_c(pt_hset, "%d, ", int);
            _print_hash_set_c(pt_hsetex, "%d, ", int);

            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, -334);
            hash_set_insert(pt_hsetex, 1212);
            hash_set_insert(pt_hsetex, 1);
            hash_set_insert(pt_hsetex, 444);
            hash_set_insert(pt_hsetex, 12);
            hash_set_insert(pt_hsetex, 45);
            hash_set_insert(pt_hsetex, 999);
            hash_set_insert(pt_hsetex, 9);
            hash_set_insert(pt_hsetex, -56);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, 34);
            hash_set_swap(pt_hset, pt_hsetex);
            _print_hash_set_c(pt_hset, "%d, ", int);
            _print_hash_set_c(pt_hsetex, "%d, ", int);

            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 45);
            hash_set_insert(pt_hsetex, 909);
            hash_set_insert(pt_hsetex, 5);
            hash_set_swap(pt_hset, pt_hsetex);
            _print_hash_set_c(pt_hset, "%d, ", int);
            _print_hash_set_c(pt_hsetex, "%d, ", int);

            hash_set_clear(pt_hsetex);
            hash_set_swap(pt_hset, pt_hsetex);
            _print_hash_set_c(pt_hset, "%d, ", int);
            _print_hash_set_c(pt_hsetex, "%d, ", int);

            hash_set_destroy(pt_hset);
            hash_set_destroy(pt_hsetex);
        }
        /*hash_set_size              */
        /*hash_set_empty             */
        /*hash_set_max_size          */
        /*hash_set_bucket_count      */
        /*hash_set_hash              */
        /*hash_set_key_less          */
        {
            hash_set_t* pt_hset = create_hash_set(int);
            if(pt_hset == NULL)
            {
                return;
            }
            hash_set_init_ex(pt_hset, 100, _hash_set_int_hash, fun_great_int);
            assert(hash_set_hash(pt_hset) == _hash_set_int_hash &&
                hash_set_key_less(pt_hset) == fun_great_int);
            hash_set_destroy(pt_hset);
        }
        /*hash_set_resize            */
        {
            hash_set_t* pt_hset = create_hash_set(int);
            if(pt_hset == NULL)
            {
                return;
            }
            hash_set_init(pt_hset);
            _print_hash_set_c(pt_hset, "%d, ", int);

            hash_set_insert(pt_hset, 56);
            hash_set_insert(pt_hset, -5);
            hash_set_insert(pt_hset, 677);
            hash_set_insert(pt_hset, 90);
            hash_set_insert(pt_hset, 23);
            _print_hash_set_c(pt_hset, "%d, ", int);

            hash_set_resize(pt_hset, 30);
            _print_hash_set_c(pt_hset, "%d, ", int);

            hash_set_resize(pt_hset, 100);
            _print_hash_set_c(pt_hset, "%d, ", int);

            hash_set_resize(pt_hset, 90);
            _print_hash_set_c(pt_hset, "%d, ", int);

            hash_set_destroy(pt_hset);
        }
        /*hash_set_equal             */
        /*hash_set_not_equal         */
        /*hash_set_less              */
        /*hash_set_less_equal        */
        /*hash_set_great             */
        /*hash_set_great_equal       */
        {
            hash_set_t* pt_hset = create_hash_set(int);
            hash_set_t* pt_hsetex = create_hash_set(int);
            if(pt_hset == NULL || pt_hsetex == NULL)
            {
                return;
            }
            hash_set_init(pt_hset);
            hash_set_init(pt_hsetex);
            _print_hash_set_c(pt_hset, "%d, ", int);
            _print_hash_set_c(pt_hsetex, "%d, ", int);
            printf("equal: %d, not equal: %d, ",
                hash_set_equal(pt_hset, pt_hsetex), hash_set_not_equal(pt_hset, pt_hsetex));
            printf("less: %d, less equal: %d, ",
                hash_set_less(pt_hset, pt_hsetex), hash_set_less_equal(pt_hset, pt_hsetex));
            printf("great: %d, great equal: %d\n",
                hash_set_great(pt_hset, pt_hsetex), hash_set_great_equal(pt_hset, pt_hsetex));

            hash_set_insert(pt_hset, 23);
            hash_set_insert(pt_hset, 40);
            _print_hash_set_c(pt_hset, "%d, ", int);
            _print_hash_set_c(pt_hsetex, "%d, ", int);
            printf("equal: %d, not equal: %d, ",
                hash_set_equal(pt_hset, pt_hsetex), hash_set_not_equal(pt_hset, pt_hsetex));
            printf("less: %d, less equal: %d, ",
                hash_set_less(pt_hset, pt_hsetex), hash_set_less_equal(pt_hset, pt_hsetex));
            printf("great: %d, great equal: %d\n",
                hash_set_great(pt_hset, pt_hsetex), hash_set_great_equal(pt_hset, pt_hsetex));

            hash_set_insert(pt_hsetex, 23);
            hash_set_insert(pt_hsetex, 40);
            _print_hash_set_c(pt_hset, "%d, ", int);
            _print_hash_set_c(pt_hsetex, "%d, ", int);
            printf("equal: %d, not equal: %d, ",
                hash_set_equal(pt_hset, pt_hsetex), hash_set_not_equal(pt_hset, pt_hsetex));
            printf("less: %d, less equal: %d, ",
                hash_set_less(pt_hset, pt_hsetex), hash_set_less_equal(pt_hset, pt_hsetex));
            printf("great: %d, great equal: %d\n",
                hash_set_great(pt_hset, pt_hsetex), hash_set_great_equal(pt_hset, pt_hsetex));

            hash_set_insert(pt_hset, 61);
            hash_set_insert(pt_hset, 60);
            hash_set_insert(pt_hsetex, 64);
            _print_hash_set_c(pt_hset, "%d, ", int);
            _print_hash_set_c(pt_hsetex, "%d, ", int);
            printf("equal: %d, not equal: %d, ",
                hash_set_equal(pt_hset, pt_hsetex), hash_set_not_equal(pt_hset, pt_hsetex));
            printf("less: %d, less equal: %d, ",
                hash_set_less(pt_hset, pt_hsetex), hash_set_less_equal(pt_hset, pt_hsetex));
            printf("great: %d, great equal: %d\n",
                hash_set_great(pt_hset, pt_hsetex), hash_set_great_equal(pt_hset, pt_hsetex));

            hash_set_resize(pt_hsetex, 80);
            _print_hash_set_c(pt_hset, "%d, ", int);
            _print_hash_set_c(pt_hsetex, "%d, ", int);
            printf("equal: %d, not equal: %d, ",
                hash_set_equal(pt_hset, pt_hsetex), hash_set_not_equal(pt_hset, pt_hsetex));
            printf("less: %d, less equal: %d, ",
                hash_set_less(pt_hset, pt_hsetex), hash_set_less_equal(pt_hset, pt_hsetex));
            printf("great: %d, great equal: %d\n",
                hash_set_great(pt_hset, pt_hsetex), hash_set_great_equal(pt_hset, pt_hsetex));

            hash_set_destroy(pt_hset);
            hash_set_destroy(pt_hsetex);
        }
        /*hash_set_begin             */
        /*hash_set_end               */
        /*hash_set_find              */
        /*hash_set_count             */
        {
            hash_set_t* pt_hset = create_hash_set(int);
            iterator_t t_iter;
            if(pt_hset == NULL)
            {
                return;
            }
            hash_set_init(pt_hset);
            t_iter = hash_set_find(pt_hset, 34);
            if(iterator_equal(t_iter, hash_set_end(pt_hset)))
            {
                printf("not found!, count : %u\n", hash_set_count(pt_hset, 34));
            }
            else
            {
                printf("found!, count : %u\n", hash_set_count(pt_hset, 34));
            }
            hash_set_insert(pt_hset, 56);
            hash_set_insert(pt_hset, 45);
            hash_set_insert(pt_hset, 88);
            hash_set_insert(pt_hset, 900);

            t_iter = hash_set_find(pt_hset, 34);
            if(iterator_equal(t_iter, hash_set_end(pt_hset)))
            {
                printf("not found!, count : %u\n", hash_set_count(pt_hset, 34));
            }
            else
            {
                printf("found!, count : %u\n", hash_set_count(pt_hset, 34));
            }
            t_iter = hash_set_find(pt_hset, 88);
            if(iterator_equal(t_iter, hash_set_end(pt_hset)))
            {
                printf("not found!, count : %u\n", hash_set_count(pt_hset, 88));
            }
            else
            {
                printf("found!, count : %u\n", hash_set_count(pt_hset, 88));
            }
            hash_set_destroy(pt_hset);
        }
        /*hash_set_equal_range       */
        {
            hash_set_t* pt_hset = create_hash_set(int);
            range_t t_range;
            if(pt_hset == NULL)
            {
                return;
            }
            hash_set_init(pt_hset);
            t_range = hash_set_equal_range(pt_hset, 45);
            assert(iterator_equal(t_range.t_begin, hash_set_end(pt_hset)) &&
                iterator_equal(t_range.t_begin, t_range.t_end));
            hash_set_insert(pt_hset, 344);
            hash_set_insert(pt_hset, 90);
            hash_set_insert(pt_hset, 456);
            hash_set_insert(pt_hset, 30);
            hash_set_insert(pt_hset, 4567);
            hash_set_insert(pt_hset, 2);
            t_range = hash_set_equal_range(pt_hset, 45);
            assert(iterator_equal(t_range.t_begin, t_range.t_end));
            t_range = hash_set_equal_range(pt_hset, 90);
            assert(iterator_equal(iterator_next(t_range.t_begin), t_range.t_end));
            hash_set_destroy(pt_hset);
        }
        /*hash_set_insert            */
        {
            hash_set_t* pt_hset = create_hash_set(double);
            if(pt_hset == NULL)
            {
                return;
            }
            hash_set_init(pt_hset);
            _print_hash_set_c(pt_hset, "%lf, ", double);
            hash_set_insert(pt_hset, 45.099);
            hash_set_insert(pt_hset, -22.445);
            hash_set_insert(pt_hset, -0.999);
            hash_set_insert(pt_hset, -0.999);
            hash_set_insert(pt_hset, -273984.0);
            hash_set_insert(pt_hset, 12.012783);
            _print_hash_set_c(pt_hset, "%lf, ", double);
            hash_set_destroy(pt_hset);
        }
        /*hash_set_insert_range      */
        {
            hash_set_t* pt_hset = create_hash_set(long);
            hash_set_t* pt_hsetex = create_hash_set(long);
            if(pt_hset == NULL || pt_hsetex == NULL)
            {
                return;
            }
            hash_set_init(pt_hset);
            hash_set_init(pt_hsetex);
            hash_set_insert_range(pt_hset, hash_set_begin(pt_hsetex), hash_set_end(pt_hsetex));
            _print_hash_set_c(pt_hset, "%ld, ", long);
            hash_set_insert(pt_hsetex, 34232344);
            hash_set_insert(pt_hsetex, 90090);
            hash_set_insert(pt_hsetex, 123445);
            hash_set_insert(pt_hsetex, -4345);
            hash_set_insert(pt_hsetex, 2300020);
            hash_set_insert(pt_hsetex, 50);
            hash_set_insert(pt_hsetex, 4550);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, 8888);
            hash_set_insert(pt_hsetex, 444444);
            hash_set_insert(pt_hsetex, 890093);
            _print_hash_set_c(pt_hsetex, "%ld, ", long);
            hash_set_insert_range(pt_hset, hash_set_begin(pt_hsetex),
                hash_set_begin(pt_hsetex));
            _print_hash_set_c(pt_hset, "%ld, ", long);
            hash_set_insert_range(pt_hset, hash_set_begin(pt_hsetex),
                iterator_advance(hash_set_begin(pt_hsetex), 3));
            _print_hash_set_c(pt_hset, "%ld, ", long);
            hash_set_insert_range(pt_hset, iterator_advance(hash_set_begin(pt_hsetex), 5),
                iterator_advance(hash_set_begin(pt_hsetex), 7));
            _print_hash_set_c(pt_hset, "%ld, ", long);
            hash_set_insert_range(pt_hset, iterator_advance(hash_set_begin(pt_hsetex), 8),
                hash_set_end(pt_hsetex));
            _print_hash_set_c(pt_hset, "%ld, ", long);
            hash_set_insert_range(pt_hset, hash_set_end(pt_hsetex), hash_set_end(pt_hsetex));
            _print_hash_set_c(pt_hset, "%ld, ", long);
            hash_set_clear(pt_hset);
            hash_set_insert_range(pt_hset, hash_set_begin(pt_hsetex), hash_set_end(pt_hsetex));
            _print_hash_set_c(pt_hset, "%ld, ", long);
            hash_set_destroy(pt_hset);
            hash_set_destroy(pt_hsetex);
        }
        /*hash_set_erase             */
        {
            hash_set_t* pt_hset = create_hash_set(long);
            if(pt_hset == NULL)
            {
                return;
            }
            hash_set_init(pt_hset);
            hash_set_erase(pt_hset, 345);
            _print_hash_set_c(pt_hset, "%ld, ", long);
            hash_set_insert(pt_hset, 34232344);
            hash_set_insert(pt_hset, 90090);
            hash_set_insert(pt_hset, 123445);
            hash_set_insert(pt_hset, -4345);
            hash_set_insert(pt_hset, 2300020);
            hash_set_insert(pt_hset, 50);
            hash_set_insert(pt_hset, 4550);
            hash_set_insert(pt_hset, 4);
            hash_set_insert(pt_hset, 8888);
            hash_set_insert(pt_hset, 444444);
            hash_set_insert(pt_hset, 890093);
            _print_hash_set_c(pt_hset, "%ld, ", long);
            hash_set_erase(pt_hset, 345);
            _print_hash_set_c(pt_hset, "%ld, ", long);
            hash_set_erase(pt_hset, 4550);
            _print_hash_set_c(pt_hset, "%ld, ", long);
            hash_set_destroy(pt_hset);
        }
        /*hash_set_erase_pos         */
        {
            hash_set_t* pt_hset = create_hash_set(long);
            if(pt_hset == NULL)
            {
                return;
            }
            hash_set_init(pt_hset);
            hash_set_insert(pt_hset, 34232344);
            hash_set_insert(pt_hset, 90090);
            hash_set_insert(pt_hset, 123445);
            hash_set_insert(pt_hset, -4345);
            hash_set_insert(pt_hset, 2300020);
            hash_set_insert(pt_hset, 50);
            hash_set_insert(pt_hset, 4550);
            hash_set_insert(pt_hset, 4);
            hash_set_insert(pt_hset, 8888);
            hash_set_insert(pt_hset, 444444);
            hash_set_insert(pt_hset, 890093);
            _print_hash_set_c(pt_hset, "%ld, ", long);
            hash_set_erase_pos(pt_hset, hash_set_begin(pt_hset));
            _print_hash_set_c(pt_hset, "%ld, ", long);
            hash_set_erase_pos(pt_hset, iterator_advance(hash_set_begin(pt_hset), 3));
            _print_hash_set_c(pt_hset, "%ld, ", long);
            while(!hash_set_empty(pt_hset))
            {
                hash_set_erase_pos(pt_hset, hash_set_begin(pt_hset));
            }
            _print_hash_set_c(pt_hset, "%ld, ", long);
            hash_set_destroy(pt_hset);
        }
        /*hash_set_erase_range       */
        {
            hash_set_t* pt_hset = create_hash_set(long);
            if(pt_hset == NULL)
            {
                return;
            }
            hash_set_init(pt_hset);
            hash_set_erase_range(pt_hset, hash_set_begin(pt_hset), hash_set_end(pt_hset));
            _print_hash_set_c(pt_hset, "%ld, ", long);
            hash_set_insert(pt_hset, 34232344);
            hash_set_insert(pt_hset, 90090);
            hash_set_insert(pt_hset, 123445);
            hash_set_insert(pt_hset, -4345);
            hash_set_insert(pt_hset, 2300020);
            hash_set_insert(pt_hset, 50);
            hash_set_insert(pt_hset, 4550);
            hash_set_insert(pt_hset, 4);
            hash_set_insert(pt_hset, 8888);
            hash_set_insert(pt_hset, 444444);
            hash_set_insert(pt_hset, 890093);
            _print_hash_set_c(pt_hset, "%ld, ", long);
            hash_set_erase_range(pt_hset, hash_set_begin(pt_hset), hash_set_begin(pt_hset));
            _print_hash_set_c(pt_hset, "%ld, ", long);
            hash_set_erase_range(pt_hset, hash_set_begin(pt_hset),
                iterator_advance(hash_set_begin(pt_hset), 3));
            _print_hash_set_c(pt_hset, "%ld, ", long);
            hash_set_erase_range(pt_hset, iterator_advance(hash_set_begin(pt_hset), 2),
                iterator_advance(hash_set_begin(pt_hset), 5));
            _print_hash_set_c(pt_hset, "%ld, ", long);
            hash_set_erase_range(pt_hset, iterator_advance(hash_set_begin(pt_hset), 3),
                hash_set_end(pt_hset));
            _print_hash_set_c(pt_hset, "%ld, ", long);
            hash_set_erase_range(pt_hset, hash_set_end(pt_hset), hash_set_end(pt_hset));
            _print_hash_set_c(pt_hset, "%ld, ", long);
            hash_set_erase_range(pt_hset, hash_set_begin(pt_hset), hash_set_end(pt_hset));
            _print_hash_set_c(pt_hset, "%ld, ", long);
            hash_set_destroy(pt_hset);
        }
        /*hash_set_clear             */
        {
            hash_set_t* pt_hset = create_hash_set(long);
            if(pt_hset == NULL)
            {
                return;
            }
            hash_set_init(pt_hset);
            hash_set_clear(pt_hset);
            _print_hash_set_c(pt_hset, "%ld, ", long);
            hash_set_insert(pt_hset, 34232344);
            hash_set_insert(pt_hset, 90090);
            hash_set_insert(pt_hset, 123445);
            hash_set_insert(pt_hset, -4345);
            hash_set_insert(pt_hset, 2300020);
            hash_set_insert(pt_hset, 50);
            hash_set_insert(pt_hset, 4550);
            hash_set_insert(pt_hset, 4);
            hash_set_insert(pt_hset, 8888);
            hash_set_insert(pt_hset, 444444);
            hash_set_insert(pt_hset, 890093);
            _print_hash_set_c(pt_hset, "%ld, ", long);
            hash_set_clear(pt_hset);
            _print_hash_set_c(pt_hset, "%ld, ", long);
            hash_set_destroy(pt_hset);
        }
    }
    /* user defined type */
    {
        type_register(hash_sample_t, _hash_sample_init, _hash_sample_copy, _hash_sample_less,
            _hash_sample_destroy);
        type_duplicate(hash_sample_t, struct _taghashsample);
        _type_debug();
        /*create_hash_set            */
        {
            hash_set_t* pt_hset = create_hash_set(hash_sample_t);
            hash_sample_t t_sample;
            if(pt_hset == NULL)
            {
                return;
            }
            hash_set_init(pt_hset);
            t_sample._d_first = 45.098;
            t_sample._l_second = 22390;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = -9834.223;
            t_sample._l_second = 409303;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = 2323.2323;
            t_sample._l_second = 4;
            hash_set_insert(pt_hset, &t_sample);
            _debug_hash_set_user(pt_hset);
            _print_hash_set_sample(pt_hset);
            hash_set_destroy(pt_hset);
        }
        /*hash_set_init              */
        /*hash_set_init_ex           */
        {
            hash_set_t* pt_hset = create_hash_set(struct _taghashsample);
            hash_sample_t t_sample;
            if(pt_hset == NULL)
            {
                return;
            }
            hash_set_init_ex(pt_hset, 200, _hash_set_sample_hash, NULL);
            t_sample._d_first = 45.098;
            t_sample._l_second = 22390;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = -9834.223;
            t_sample._l_second = 409303;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = 2323.2323;
            t_sample._l_second = 4;
            hash_set_insert(pt_hset, &t_sample);
            _debug_hash_set_user(pt_hset);
            _print_hash_set_sample(pt_hset);
            hash_set_destroy(pt_hset);
        }
        /*hash_set_init_copy         */
        {
            hash_set_t* pt_hset = create_hash_set(hash_sample_t);
            hash_set_t* pt_hsetex = create_hash_set(hash_sample_t);
            hash_sample_t t_sample;
            if(pt_hset == NULL || pt_hsetex == NULL)
            {
                return;
            }
            hash_set_init(pt_hsetex);
            t_sample._d_first = 45.098;
            t_sample._l_second = 22390;
            hash_set_insert(pt_hsetex, &t_sample);
            t_sample._d_first = -9834.223;
            t_sample._l_second = 409303;
            hash_set_insert(pt_hsetex, &t_sample);
            t_sample._d_first = 2323.2323;
            t_sample._l_second = 4;
            hash_set_insert(pt_hsetex, &t_sample);
            _print_hash_set_sample(pt_hsetex);
            hash_set_init_copy(pt_hset, pt_hsetex);
            _print_hash_set_sample(pt_hset);
            hash_set_destroy(pt_hset);
            hash_set_destroy(pt_hsetex);
        }
        /*hash_set_init_copy_range   */
        {
            hash_set_t* pt_hset = create_hash_set(hash_sample_t);
            hash_set_t* pt_hsetex = create_hash_set(hash_sample_t);
            hash_sample_t t_sample;
            if(pt_hset == NULL || pt_hsetex == NULL)
            {
                return;
            }
            hash_set_init_ex(pt_hsetex, 100, _hash_set_sample_hash, NULL);
            t_sample._d_first = 45.098;
            t_sample._l_second = 22390;
            hash_set_insert(pt_hsetex, &t_sample);
            t_sample._d_first = -9834.223;
            t_sample._l_second = 409303;
            hash_set_insert(pt_hsetex, &t_sample);
            t_sample._d_first = 2323.2323;
            t_sample._l_second = 4;
            hash_set_insert(pt_hsetex, &t_sample);
            t_sample._d_first = 0.2323;
            t_sample._l_second = 66666;
            hash_set_insert(pt_hsetex, &t_sample);
            t_sample._d_first = 2323.0;
            t_sample._l_second = -66666;
            hash_set_insert(pt_hsetex, &t_sample);
            t_sample._d_first = 0.0;
            t_sample._l_second = 0;
            hash_set_insert(pt_hsetex, &t_sample);
            t_sample._d_first = 1.1;
            t_sample._l_second = 1;
            hash_set_insert(pt_hsetex, &t_sample);
            t_sample._d_first = 8.8;
            t_sample._l_second = 8;
            hash_set_insert(pt_hsetex, &t_sample);
            t_sample._d_first = 44444.4;
            t_sample._l_second = -5666;
            hash_set_insert(pt_hsetex, &t_sample);
            t_sample._d_first = 44.4;
            t_sample._l_second = -5666;
            hash_set_insert(pt_hsetex, &t_sample);
            _print_hash_set_sample(pt_hsetex);
            hash_set_init_copy_range(pt_hset, hash_set_begin(pt_hsetex),
                hash_set_end(pt_hsetex));
            _print_hash_set_sample(pt_hset);
            hash_set_destroy(pt_hset);
            hash_set_destroy(pt_hsetex);
        }
        /*hash_set_init_copy_range_ex*/
        {
            hash_set_t* pt_hset = create_hash_set(hash_sample_t);
            hash_set_t* pt_hsetex = create_hash_set(hash_sample_t);
            hash_sample_t t_sample;
            if(pt_hset == NULL || pt_hsetex == NULL)
            {
                return;
            }
            hash_set_init_ex(pt_hsetex, 100, _hash_set_sample_hash, NULL);
            t_sample._d_first = 45.098;
            t_sample._l_second = 22390;
            hash_set_insert(pt_hsetex, &t_sample);
            t_sample._d_first = -9834.223;
            t_sample._l_second = 409303;
            hash_set_insert(pt_hsetex, &t_sample);
            t_sample._d_first = 2323.2323;
            t_sample._l_second = 4;
            hash_set_insert(pt_hsetex, &t_sample);
            t_sample._d_first = 0.2323;
            t_sample._l_second = 66666;
            hash_set_insert(pt_hsetex, &t_sample);
            t_sample._d_first = 2323.0;
            t_sample._l_second = -66666;
            hash_set_insert(pt_hsetex, &t_sample);
            t_sample._d_first = 0.0;
            t_sample._l_second = 0;
            hash_set_insert(pt_hsetex, &t_sample);
            t_sample._d_first = 1.1;
            t_sample._l_second = 1;
            hash_set_insert(pt_hsetex, &t_sample);
            t_sample._d_first = 8.8;
            t_sample._l_second = 8;
            hash_set_insert(pt_hsetex, &t_sample);
            t_sample._d_first = 44444.4;
            t_sample._l_second = -5666;
            hash_set_insert(pt_hsetex, &t_sample);
            t_sample._d_first = 44.4;
            t_sample._l_second = -5666;
            hash_set_insert(pt_hsetex, &t_sample);
            _print_hash_set_sample(pt_hsetex);
            hash_set_init_copy_range_ex(pt_hset, hash_set_begin(pt_hsetex),
                hash_set_end(pt_hsetex), 80, NULL, _hash_sample_great);
            _print_hash_set_sample(pt_hset);
            hash_set_destroy(pt_hset);
            hash_set_destroy(pt_hsetex);
        }
        /*hash_set_destroy           */
        /*hash_set_assign            */
        {
            hash_set_t* pt_hset = create_hash_set(hash_sample_t);
            hash_set_t* pt_hsetex = create_hash_set(hash_sample_t);
            hash_sample_t t_sample;
            if(pt_hset == NULL || pt_hsetex == NULL)
            {
                return;
            }
            hash_set_init(pt_hset);
            hash_set_init(pt_hsetex);
            hash_set_assign(pt_hset, pt_hsetex);
            _print_hash_set_sample(pt_hset);
            t_sample._d_first = 45.90;
            t_sample._l_second = 3490;
            hash_set_insert(pt_hsetex, &t_sample);
            t_sample._d_first = -10.01111;
            t_sample._l_second = 9009;
            hash_set_insert(pt_hsetex, &t_sample);
            t_sample._d_first = 45.087;
            t_sample._l_second = -290;
            hash_set_insert(pt_hsetex, &t_sample);
            hash_set_assign(pt_hset, pt_hsetex);
            _print_hash_set_sample(pt_hset);
            hash_set_clear(pt_hsetex);
            t_sample._d_first = 40.099;
            t_sample._l_second = -670;
            hash_set_insert(pt_hsetex, &t_sample);
            t_sample._d_first = 122121.0;
            t_sample._l_second = 56;
            hash_set_insert(pt_hsetex, &t_sample);
            t_sample._d_first = 45.09898;
            t_sample._l_second = 898;
            hash_set_insert(pt_hsetex, &t_sample);
            t_sample._d_first = 230.9;
            t_sample._l_second = -7777;
            hash_set_insert(pt_hsetex, &t_sample);
            t_sample._d_first = 45.99999;
            t_sample._l_second = 459999;
            hash_set_insert(pt_hsetex, &t_sample);
            hash_set_assign(pt_hset, pt_hsetex);
            _print_hash_set_sample(pt_hset);
            hash_set_clear(pt_hsetex);
            t_sample._d_first = 4.5;
            t_sample._l_second = 45;
            hash_set_insert(pt_hsetex, &t_sample);
            hash_set_assign(pt_hset, pt_hsetex);
            _print_hash_set_sample(pt_hset);
            hash_set_clear(pt_hsetex);
            hash_set_assign(pt_hset, pt_hsetex);
            _print_hash_set_sample(pt_hset);
            hash_set_destroy(pt_hset);
            hash_set_destroy(pt_hsetex);
        }
        /*hash_set_swap              */
        {
            hash_set_t* pt_hset = create_hash_set(hash_sample_t);
            hash_set_t* pt_hsetex = create_hash_set(hash_sample_t);
            hash_sample_t t_sample;
            if(pt_hset == NULL || pt_hsetex == NULL)
            {
                return;
            }
            hash_set_init(pt_hset);
            hash_set_init(pt_hsetex);
            hash_set_swap(pt_hset, pt_hsetex);
            _print_hash_set_sample(pt_hset);
            _print_hash_set_sample(pt_hsetex);
            t_sample._d_first = 45.90;
            t_sample._l_second = 3490;
            hash_set_insert(pt_hsetex, &t_sample);
            t_sample._d_first = -10.01111;
            t_sample._l_second = 9009;
            hash_set_insert(pt_hsetex, &t_sample);
            t_sample._d_first = 45.087;
            t_sample._l_second = -290;
            hash_set_insert(pt_hsetex, &t_sample);
            hash_set_swap(pt_hset, pt_hsetex);
            _print_hash_set_sample(pt_hset);
            _print_hash_set_sample(pt_hsetex);
            hash_set_clear(pt_hsetex);
            t_sample._d_first = 40.099;
            t_sample._l_second = -670;
            hash_set_insert(pt_hsetex, &t_sample);
            t_sample._d_first = 122121.0;
            t_sample._l_second = 56029;
            hash_set_insert(pt_hsetex, &t_sample);
            t_sample._d_first = 45.09898;
            t_sample._l_second = 898;
            hash_set_insert(pt_hsetex, &t_sample);
            t_sample._d_first = 230.9;
            t_sample._l_second = -7777;
            hash_set_insert(pt_hsetex, &t_sample);
            t_sample._d_first = 45.99999;
            t_sample._l_second = 459999;
            hash_set_insert(pt_hsetex, &t_sample);
            hash_set_swap(pt_hset, pt_hsetex);
            _print_hash_set_sample(pt_hset);
            _print_hash_set_sample(pt_hsetex);
            hash_set_clear(pt_hsetex);
            t_sample._d_first = 4.5;
            t_sample._l_second = 45;
            hash_set_insert(pt_hsetex, &t_sample);
            hash_set_swap(pt_hset, pt_hsetex);
            _print_hash_set_sample(pt_hset);
            _print_hash_set_sample(pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_swap(pt_hset, pt_hsetex);
            _print_hash_set_sample(pt_hset);
            _print_hash_set_sample(pt_hsetex);
            hash_set_destroy(pt_hset);
            hash_set_destroy(pt_hsetex);
        }
        /*hash_set_size              */
        /*hash_set_empty             */
        /*hash_set_max_size          */
        /*hash_set_bucket_count      */
        /*hash_set_hash              */
        /*hash_set_key_less          */
        {
            hash_set_t* pt_hset = create_hash_set(hash_sample_t);
            if(pt_hset == NULL)
            {
                return;
            }
            hash_set_init_ex(pt_hset, 100, _hash_set_sample_hash, _hash_sample_great);
            assert(hash_set_hash(pt_hset) == _hash_set_sample_hash &&
                hash_set_key_less(pt_hset) == _hash_sample_great);
            hash_set_destroy(pt_hset);
        }
        /*hash_set_resize            */
        {
            hash_set_t* pt_hset = create_hash_set(hash_sample_t);
            if(pt_hset == NULL)
            {
                return;
            }
            hash_set_init(pt_hset);
            _print_hash_set_sample(pt_hset);
            hash_set_resize(pt_hset, 100);
            _print_hash_set_sample(pt_hset);
            hash_set_resize(pt_hset, 80);
            _print_hash_set_sample(pt_hset);
            hash_set_destroy(pt_hset);
        }
        /*hash_set_equal             */
        /*hash_set_not_equal         */
        /*hash_set_less              */
        /*hash_set_less_equal        */
        /*hash_set_great             */
        /*hash_set_great_equal       */
        {
            hash_set_t* pt_hset = create_hash_set(hash_sample_t);
            hash_set_t* pt_hsetex = create_hash_set(hash_sample_t);
            hash_sample_t t_sample;
            if(pt_hset == NULL || pt_hsetex == NULL)
            {
                return;
            }
            hash_set_init(pt_hset);
            hash_set_init(pt_hsetex);
            _print_hash_set_sample(pt_hset);
            _print_hash_set_sample(pt_hsetex);
            printf("equal: %d, not equal: %d, ",
                hash_set_equal(pt_hset, pt_hsetex), hash_set_not_equal(pt_hset, pt_hsetex));
            printf("less: %d, less equal: %d, ",
                hash_set_less(pt_hset, pt_hsetex), hash_set_less_equal(pt_hset, pt_hsetex));
            printf("great: %d, great equal: %d\n",
                hash_set_great(pt_hset, pt_hsetex), hash_set_great_equal(pt_hset, pt_hsetex));
            t_sample._d_first = 34.98;
            t_sample._l_second = 34;
            hash_set_insert(pt_hset, &t_sample);
            _print_hash_set_sample(pt_hset);
            _print_hash_set_sample(pt_hsetex);
            printf("equal: %d, not equal: %d, ",
                hash_set_equal(pt_hset, pt_hsetex), hash_set_not_equal(pt_hset, pt_hsetex));
            printf("less: %d, less equal: %d, ",
                hash_set_less(pt_hset, pt_hsetex), hash_set_less_equal(pt_hset, pt_hsetex));
            printf("great: %d, great equal: %d\n",
                hash_set_great(pt_hset, pt_hsetex), hash_set_great_equal(pt_hset, pt_hsetex));
            hash_set_insert(pt_hsetex, &t_sample);
            _print_hash_set_sample(pt_hset);
            _print_hash_set_sample(pt_hsetex);
            printf("equal: %d, not equal: %d, ",
                hash_set_equal(pt_hset, pt_hsetex), hash_set_not_equal(pt_hset, pt_hsetex));
            printf("less: %d, less equal: %d, ",
                hash_set_less(pt_hset, pt_hsetex), hash_set_less_equal(pt_hset, pt_hsetex));
            printf("great: %d, great equal: %d\n",
                hash_set_great(pt_hset, pt_hsetex), hash_set_great_equal(pt_hset, pt_hsetex));
            t_sample._d_first = -90.23;
            t_sample._l_second = 0;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = 452.33;
            t_sample._l_second = 90;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = 23232.2;
            t_sample._l_second = 4849;
            hash_set_insert(pt_hsetex, &t_sample);
            _print_hash_set_sample(pt_hset);
            _print_hash_set_sample(pt_hsetex);
            printf("equal: %d, not equal: %d, ",
                hash_set_equal(pt_hset, pt_hsetex), hash_set_not_equal(pt_hset, pt_hsetex));
            printf("less: %d, less equal: %d, ",
                hash_set_less(pt_hset, pt_hsetex), hash_set_less_equal(pt_hset, pt_hsetex));
            printf("great: %d, great equal: %d\n",
                hash_set_great(pt_hset, pt_hsetex), hash_set_great_equal(pt_hset, pt_hsetex));
            hash_set_destroy(pt_hset);
            hash_set_destroy(pt_hsetex);
        }
        /*hash_set_begin             */
        /*hash_set_end               */
        /*hash_set_find              */
        /*hash_set_count             */
        {
            hash_set_t* pt_hset = create_hash_set(hash_sample_t);
            hash_sample_t t_sample;
            iterator_t t_iter;
            if(pt_hset == NULL)
            {
                return;
            }
            hash_set_init(pt_hset);
            t_sample._d_first = 0.09;
            t_sample._l_second = 45;
            t_iter = hash_set_find(pt_hset, &t_sample);
            if(iterator_equal(t_iter, hash_set_end(pt_hset)))
            {
                printf("not found, count : %d\n", hash_set_count(pt_hset, &t_sample));
            }
            else
            {
                printf("found, count : %d\n", hash_set_count(pt_hset, &t_sample));
            }
            t_sample._d_first = 34234.23;
            t_sample._l_second = 4;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = 67.22;
            t_sample._l_second = 0;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = -8784.23;
            t_sample._l_second = 90;
            hash_set_insert(pt_hset, &t_sample);
            _print_hash_set_sample(pt_hset);
            t_sample._d_first = 0.09;
            t_sample._l_second = 45;
            t_iter = hash_set_find(pt_hset, &t_sample);
            if(iterator_equal(t_iter, hash_set_end(pt_hset)))
            {
                printf("not found, count : %d\n", hash_set_count(pt_hset, &t_sample));
            }
            else
            {
                printf("found, count : %d\n", hash_set_count(pt_hset, &t_sample));
            }
            hash_set_insert(pt_hset, &t_sample);
            _print_hash_set_sample(pt_hset);
            t_iter = hash_set_find(pt_hset, &t_sample);
            if(iterator_equal(t_iter, hash_set_end(pt_hset)))
            {
                printf("not found, count : %d\n", hash_set_count(pt_hset, &t_sample));
            }
            else
            {
                printf("found, count : %d\n", hash_set_count(pt_hset, &t_sample));
            }

            hash_set_destroy(pt_hset);
        }
        /*hash_set_equal_range       */
        {
            hash_set_t* pt_hset = create_hash_set(hash_sample_t);
            hash_sample_t t_sample;
            range_t t_range;
            if(pt_hset == NULL)
            {
                return;
            }
            hash_set_init(pt_hset);
            t_sample._d_first = 344.23;
            t_sample._l_second = 445;
            t_range = hash_set_equal_range(pt_hset, &t_sample);
            assert(iterator_equal(t_range.t_begin, hash_set_end(pt_hset)));
            assert(iterator_equal(t_range.t_end, hash_set_end(pt_hset)));

            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = 45.098;
            t_sample._l_second = 23;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = 23.23;
            t_sample._l_second = 0;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = 111.111;
            t_sample._l_second = -34;
            hash_set_insert(pt_hset, &t_sample);
            _print_hash_set_sample(pt_hset);
            t_sample._d_first = 45.098;
            t_sample._l_second = 23;
            t_range = hash_set_equal_range(pt_hset, &t_sample);
            assert(iterator_equal(iterator_next(t_range.t_begin), t_range.t_end));
            hash_set_destroy(pt_hset);
        }
        /*hash_set_insert            */
        {
            hash_set_t* pt_hset = create_hash_set(hash_sample_t);
            hash_sample_t t_sample;
            if(pt_hset == NULL)
            {
                return;
            }
            hash_set_init_ex(pt_hset, 100, _hash_set_int_hash, NULL);
            t_sample._d_first = 4.555;
            t_sample._l_second = 0;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = 23.232;
            t_sample._l_second = 1111;
            hash_set_insert(pt_hset, &t_sample);
            _print_hash_set_sample(pt_hset);
            hash_set_destroy(pt_hset);
        }
        /*hash_set_insert_range      */
        {
            hash_set_t* pt_hset = create_hash_set(hash_sample_t);
            hash_set_t* pt_hsetex = create_hash_set(hash_sample_t);
            hash_sample_t t_sample;
            if(pt_hset == NULL || pt_hsetex == NULL)
            {
                return;
            }
            hash_set_init(pt_hset);
            hash_set_init(pt_hsetex);
            hash_set_insert_range(pt_hset, hash_set_begin(pt_hsetex), hash_set_end(pt_hsetex));
            _print_hash_set_sample(pt_hset);
            t_sample._d_first = 44.23;
            t_sample._l_second = 99;
            hash_set_insert(pt_hsetex, &t_sample);
            t_sample._d_first = 12.23323;
            t_sample._l_second = 656;
            hash_set_insert(pt_hsetex, &t_sample);
            t_sample._d_first = -3.0;
            t_sample._l_second = 43;
            hash_set_insert(pt_hsetex, &t_sample);
            t_sample._d_first = 45.23;
            t_sample._l_second = 999;
            hash_set_insert(pt_hsetex, &t_sample);
            t_sample._d_first = 13.23323;
            t_sample._l_second = 656;
            hash_set_insert(pt_hsetex, &t_sample);
            t_sample._d_first = -2.0;
            t_sample._l_second = 43;
            hash_set_insert(pt_hsetex, &t_sample);
            t_sample._d_first = 445.3;
            t_sample._l_second = 999;
            hash_set_insert(pt_hsetex, &t_sample);
            t_sample._d_first = 123.3323;
            t_sample._l_second = 656;
            hash_set_insert(pt_hsetex, &t_sample);
            t_sample._d_first = -32.7;
            t_sample._l_second = 43;
            hash_set_insert(pt_hsetex, &t_sample);
            t_sample._d_first = 445.2;
            t_sample._l_second = 999;
            hash_set_insert(pt_hsetex, &t_sample);
            t_sample._d_first = 123.2323;
            t_sample._l_second = 656;
            hash_set_insert(pt_hsetex, &t_sample);
            t_sample._d_first = -32.9;
            t_sample._l_second = 43;
            hash_set_insert(pt_hsetex, &t_sample);
            _print_hash_set_sample(pt_hsetex);

            hash_set_insert_range(pt_hset, hash_set_begin(pt_hsetex), hash_set_begin(pt_hsetex));
            _print_hash_set_sample(pt_hset);
            hash_set_insert_range(pt_hset, hash_set_begin(pt_hsetex), iterator_advance(hash_set_begin(pt_hsetex), 3));
            _print_hash_set_sample(pt_hset);
            hash_set_insert_range(pt_hset, iterator_advance(hash_set_begin(pt_hsetex), 5), iterator_advance(hash_set_begin(pt_hsetex), 7));
            _print_hash_set_sample(pt_hset);
            hash_set_insert_range(pt_hset, iterator_advance(hash_set_begin(pt_hsetex), 9), hash_set_end(pt_hsetex));
            _print_hash_set_sample(pt_hset);
            hash_set_insert_range(pt_hset, hash_set_end(pt_hsetex), hash_set_end(pt_hsetex));
            _print_hash_set_sample(pt_hset);

            hash_set_clear(pt_hset);
            hash_set_insert_range(pt_hset, hash_set_begin(pt_hsetex), hash_set_end(pt_hsetex));
            _print_hash_set_sample(pt_hset);

            hash_set_destroy(pt_hset);
            hash_set_destroy(pt_hsetex);
        }
        /*hash_set_erase             */
        {
            hash_set_t* pt_hset = create_hash_set(hash_sample_t);
            hash_sample_t t_sample;
            if(pt_hset == NULL)
            {
                return;
            }
            hash_set_init(pt_hset);
            t_sample._d_first = 0.445;
            t_sample._l_second = 789;
            hash_set_erase(pt_hset, &t_sample);
            _print_hash_set_sample(pt_hset);

            t_sample._d_first = 44.23;
            t_sample._l_second = 99;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = 12.23323;
            t_sample._l_second = 656;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = -3.0;
            t_sample._l_second = 43;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = 45.23;
            t_sample._l_second = 999;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = 13.23323;
            t_sample._l_second = 656;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = -2.0;
            t_sample._l_second = 43;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = 445.3;
            t_sample._l_second = 999;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = 123.3323;
            t_sample._l_second = 656;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = -32.7;
            t_sample._l_second = 43;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = 445.2;
            t_sample._l_second = 999;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = 123.2323;
            t_sample._l_second = 656;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = -32.9;
            t_sample._l_second = 43;
            hash_set_insert(pt_hset, &t_sample);
            _print_hash_set_sample(pt_hset);

            t_sample._d_first = 29989.0092;
            t_sample._l_second = 834934;
            hash_set_erase(pt_hset, &t_sample);
            _print_hash_set_sample(pt_hset);
            t_sample._d_first = -32.7;
            t_sample._l_second = 43;
            hash_set_erase(pt_hset, &t_sample);
            _print_hash_set_sample(pt_hset);

            hash_set_destroy(pt_hset);
        }
        /*hash_set_erase_pos         */
        {
            hash_set_t* pt_hset = create_hash_set(hash_sample_t);
            hash_sample_t t_sample;
            if(pt_hset == NULL)
            {
                return;
            }
            hash_set_init(pt_hset);
            t_sample._d_first = 44.23;
            t_sample._l_second = 99;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = 12.23323;
            t_sample._l_second = 656;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = -3.0;
            t_sample._l_second = 43;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = 45.23;
            t_sample._l_second = 999;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = 13.23323;
            t_sample._l_second = 656;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = -2.0;
            t_sample._l_second = 43;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = 445.3;
            t_sample._l_second = 999;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = 123.3323;
            t_sample._l_second = 656;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = -32.7;
            t_sample._l_second = 43;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = 445.2;
            t_sample._l_second = 999;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = 123.2323;
            t_sample._l_second = 656;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = -32.9;
            t_sample._l_second = 43;
            hash_set_insert(pt_hset, &t_sample);
            _print_hash_set_sample(pt_hset);

            hash_set_erase_pos(pt_hset, hash_set_begin(pt_hset));
            _print_hash_set_sample(pt_hset);
            hash_set_erase_pos(pt_hset, iterator_advance(hash_set_begin(pt_hset), 5));
            _print_hash_set_sample(pt_hset);
            while(!hash_set_empty(pt_hset))
            {
                hash_set_erase_pos(pt_hset, hash_set_begin(pt_hset));
            }
            _print_hash_set_sample(pt_hset);

            hash_set_destroy(pt_hset);
        }
        /*hash_set_erase_range       */
        {
            hash_set_t* pt_hset = create_hash_set(hash_sample_t);
            hash_sample_t t_sample;
            if(pt_hset == NULL)
            {
                return;
            }
            hash_set_init(pt_hset);
            hash_set_erase_range(pt_hset, hash_set_begin(pt_hset), hash_set_end(pt_hset));
            t_sample._d_first = 44.23;
            t_sample._l_second = 99;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = 12.23323;
            t_sample._l_second = 656;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = -3.0;
            t_sample._l_second = 43;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = 45.23;
            t_sample._l_second = 999;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = 13.23323;
            t_sample._l_second = 656;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = -2.0;
            t_sample._l_second = 43;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = 445.3;
            t_sample._l_second = 999;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = 123.3323;
            t_sample._l_second = 656;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = -32.7;
            t_sample._l_second = 43;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = 445.2;
            t_sample._l_second = 999;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = 123.2323;
            t_sample._l_second = 656;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = -32.9;
            t_sample._l_second = 43;
            hash_set_insert(pt_hset, &t_sample);
            _print_hash_set_sample(pt_hset);

            hash_set_erase_range(pt_hset, hash_set_begin(pt_hset), hash_set_begin(pt_hset));
            _print_hash_set_sample(pt_hset);
            hash_set_erase_range(pt_hset, hash_set_begin(pt_hset), iterator_next(hash_set_begin(pt_hset)));
            _print_hash_set_sample(pt_hset);
            hash_set_erase_range(pt_hset, iterator_advance(hash_set_begin(pt_hset), 3), iterator_advance(hash_set_begin(pt_hset), 6));
            _print_hash_set_sample(pt_hset);
            hash_set_erase_range(pt_hset, iterator_advance(hash_set_begin(pt_hset), 5), hash_set_end(pt_hset));
            _print_hash_set_sample(pt_hset);
            hash_set_erase_range(pt_hset, hash_set_end(pt_hset), hash_set_end(pt_hset));
            _print_hash_set_sample(pt_hset);
            hash_set_erase_range(pt_hset, hash_set_begin(pt_hset), hash_set_end(pt_hset));
            _print_hash_set_sample(pt_hset);

            hash_set_destroy(pt_hset);
        }
        /*hash_set_clear             */
        {
            hash_set_t* pt_hset = create_hash_set(hash_sample_t);
            hash_sample_t t_sample;
            if(pt_hset == NULL)
            {
                return;
            }
            hash_set_init(pt_hset);
            hash_set_clear(pt_hset);
            _print_hash_set_sample(pt_hset);
            t_sample._d_first = 44.23;
            t_sample._l_second = 99;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = 12.23323;
            t_sample._l_second = 656;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = -3.0;
            t_sample._l_second = 43;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = 45.23;
            t_sample._l_second = 999;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = 13.23323;
            t_sample._l_second = 656;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = -2.0;
            t_sample._l_second = 43;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = 445.3;
            t_sample._l_second = 999;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = 123.3323;
            t_sample._l_second = 656;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = -32.7;
            t_sample._l_second = 43;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = 445.2;
            t_sample._l_second = 999;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = 123.2323;
            t_sample._l_second = 656;
            hash_set_insert(pt_hset, &t_sample);
            t_sample._d_first = -32.9;
            t_sample._l_second = 43;
            hash_set_insert(pt_hset, &t_sample);
            _print_hash_set_sample(pt_hset);

            hash_set_clear(pt_hset);
            _print_hash_set_sample(pt_hset);

            hash_set_destroy(pt_hset);
        }
    }
    /* cstl type */
    {
        /*create_hash_set            */
        /*hash_set_init              */
        {
            hash_set_t* pt_hset = create_hash_set(hash_set_t<int>);
            hash_set_t* pt_hsetex = create_hash_set(int);
            if(pt_hset == NULL || pt_hsetex == NULL)
            {
                return;
            }
            hash_set_init(pt_hset);
            hash_set_init(pt_hsetex);
            hash_set_insert(pt_hsetex, 12239);
            hash_set_insert(pt_hsetex, 20);
            hash_set_insert(pt_hsetex, -847);
            hash_set_insert(pt_hsetex, 0);
            hash_set_insert(pt_hsetex, 44);
            hash_set_insert(pt_hsetex, 99);
            hash_set_insert(pt_hset, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, -74);
            hash_set_insert(pt_hsetex, 2233);
            hash_set_insert(pt_hsetex, 90);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, 334);
            hash_set_insert(pt_hsetex, 5);
            hash_set_insert(pt_hsetex, -76);
            hash_set_insert(pt_hset, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, -4);
            hash_set_insert(pt_hset, pt_hsetex);
            _print_hash_set_cstl(pt_hset);
            hash_set_destroy(pt_hset);
            hash_set_destroy(pt_hsetex);
        }
        /*hash_set_init_ex           */
        {
            hash_set_t* pt_hset = create_hash_set(hash_set_t<int>);
            hash_set_t* pt_hsetex = create_hash_set(int);
            if(pt_hset == NULL || pt_hsetex == NULL)
            {
                return;
            }
            hash_set_init_ex(pt_hset, 100, _hash_set_cstl_hash, NULL);
            hash_set_init(pt_hsetex);
            hash_set_insert(pt_hsetex, 12239);
            hash_set_insert(pt_hsetex, 20);
            hash_set_insert(pt_hsetex, -847);
            hash_set_insert(pt_hsetex, 0);
            hash_set_insert(pt_hsetex, 44);
            hash_set_insert(pt_hsetex, 99);
            hash_set_insert(pt_hset, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, -74);
            hash_set_insert(pt_hsetex, 2233);
            hash_set_insert(pt_hsetex, 90);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, 334);
            hash_set_insert(pt_hsetex, 5);
            hash_set_insert(pt_hsetex, -76);
            hash_set_insert(pt_hset, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, -4);
            hash_set_insert(pt_hset, pt_hsetex);
            _print_hash_set_cstl(pt_hset);
            hash_set_destroy(pt_hset);
            hash_set_destroy(pt_hsetex);
        }
        /*hash_set_init_copy         */
        {
            hash_set_t* pt_hset1 = create_hash_set(hash_set_t<int>);
            hash_set_t* pt_hset2 = create_hash_set(hash_set_t<int>);
            hash_set_t* pt_hsetex = create_hash_set(int);
            if(pt_hset1 == NULL || pt_hset2 == NULL || pt_hsetex == NULL)
            {
                return;
            }
            hash_set_init(pt_hsetex);
            hash_set_init_ex(pt_hset2, 200, _hash_set_cstl_hash, NULL);

            hash_set_insert(pt_hsetex, 12239);
            hash_set_insert(pt_hsetex, 20);
            hash_set_insert(pt_hsetex, -847);
            hash_set_insert(pt_hsetex, 0);
            hash_set_insert(pt_hsetex, 44);
            hash_set_insert(pt_hsetex, 99);
            hash_set_insert(pt_hset2, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, -74);
            hash_set_insert(pt_hsetex, 2233);
            hash_set_insert(pt_hsetex, 90);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, 334);
            hash_set_insert(pt_hsetex, 5);
            hash_set_insert(pt_hsetex, -76);
            hash_set_insert(pt_hset2, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, -4);
            hash_set_insert(pt_hset2, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 4444);
            hash_set_insert(pt_hsetex, -98);
            hash_set_insert(pt_hsetex, 2222);
            hash_set_insert(pt_hsetex, 1);
            hash_set_insert(pt_hsetex, 3);
            hash_set_insert(pt_hsetex, 55);
            hash_set_insert(pt_hset2, pt_hsetex);

            hash_set_init_copy(pt_hset1, pt_hset2);

            _print_hash_set_cstl(pt_hset1);

            hash_set_destroy(pt_hsetex);
            hash_set_destroy(pt_hset1);
            hash_set_destroy(pt_hset2);
        }
        /*hash_set_init_copy_range   */
        {
            hash_set_t* pt_hset1 = create_hash_set(hash_set_t<int>);
            hash_set_t* pt_hset2 = create_hash_set(hash_set_t<int>);
            hash_set_t* pt_hsetex = create_hash_set(int);
            if(pt_hset1 == NULL || pt_hset2 == NULL || pt_hsetex == NULL)
            {
                return;
            }
            hash_set_init(pt_hsetex);
            hash_set_init_ex(pt_hset2, 200, _hash_set_cstl_hash, NULL);

            hash_set_insert(pt_hsetex, 12239);
            hash_set_insert(pt_hsetex, 20);
            hash_set_insert(pt_hsetex, -847);
            hash_set_insert(pt_hsetex, 0);
            hash_set_insert(pt_hsetex, 44);
            hash_set_insert(pt_hsetex, 99);
            hash_set_insert(pt_hset2, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, -74);
            hash_set_insert(pt_hsetex, 2233);
            hash_set_insert(pt_hsetex, 90);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, 334);
            hash_set_insert(pt_hsetex, 5);
            hash_set_insert(pt_hsetex, -76);
            hash_set_insert(pt_hset2, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, -4);
            hash_set_insert(pt_hset2, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 4444);
            hash_set_insert(pt_hsetex, -98);
            hash_set_insert(pt_hsetex, 2222);
            hash_set_insert(pt_hsetex, 1);
            hash_set_insert(pt_hsetex, 3);
            hash_set_insert(pt_hsetex, 55);
            hash_set_insert(pt_hset2, pt_hsetex);

            hash_set_init_copy_range(pt_hset1,
                hash_set_begin(pt_hset2), hash_set_end(pt_hset2));

            _print_hash_set_cstl(pt_hset2);
            _print_hash_set_cstl(pt_hset1);

            hash_set_destroy(pt_hsetex);
            hash_set_destroy(pt_hset1);
            hash_set_destroy(pt_hset2);
        }
        /*hash_set_init_copy_range_ex*/
        {
            hash_set_t* pt_hset1 = create_hash_set(hash_set_t<int>);
            hash_set_t* pt_hset2 = create_hash_set(hash_set_t<int>);
            hash_set_t* pt_hsetex = create_hash_set(int);
            if(pt_hset1 == NULL || pt_hset2 == NULL || pt_hsetex == NULL)
            {
                return;
            }
            hash_set_init_ex(pt_hsetex, 200, NULL, NULL);
            hash_set_init(pt_hset2);

            hash_set_insert(pt_hsetex, 12239);
            hash_set_insert(pt_hsetex, 20);
            hash_set_insert(pt_hsetex, -847);
            hash_set_insert(pt_hsetex, 0);
            hash_set_insert(pt_hsetex, 44);
            hash_set_insert(pt_hsetex, 99);
            hash_set_insert(pt_hset2, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, -74);
            hash_set_insert(pt_hsetex, 2233);
            hash_set_insert(pt_hsetex, 90);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, 334);
            hash_set_insert(pt_hsetex, 5);
            hash_set_insert(pt_hsetex, -76);
            hash_set_insert(pt_hset2, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, -4);
            hash_set_insert(pt_hset2, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 4444);
            hash_set_insert(pt_hsetex, -98);
            hash_set_insert(pt_hsetex, 2222);
            hash_set_insert(pt_hsetex, 1);
            hash_set_insert(pt_hsetex, 3);
            hash_set_insert(pt_hsetex, 55);
            hash_set_insert(pt_hset2, pt_hsetex);

            hash_set_init_copy_range_ex(pt_hset1,
                hash_set_begin(pt_hset2), hash_set_end(pt_hset2),
                100, _hash_set_cstl_hash, NULL);

            _print_hash_set_cstl(pt_hset2);
            _print_hash_set_cstl(pt_hset1);

            hash_set_destroy(pt_hsetex);
            hash_set_destroy(pt_hset1);
            hash_set_destroy(pt_hset2);
        }
        /*hash_set_destroy           */
        /*hash_set_assign            */
        {
            hash_set_t* pt_hset1 = create_hash_set(hash_set_t<int>);
            hash_set_t* pt_hset2 = create_hash_set(hash_set_t<int>);
            hash_set_t* pt_hsetex = create_hash_set(int);
            if(pt_hset1 == NULL || pt_hset2 == NULL || pt_hsetex == NULL)
            {
                return;
            }
            hash_set_init_ex(pt_hsetex, 200, NULL, NULL);
            hash_set_init(pt_hset2);
            hash_set_init(pt_hset1);

            hash_set_insert(pt_hsetex, 12239);
            hash_set_insert(pt_hsetex, 20);
            hash_set_insert(pt_hsetex, -847);
            hash_set_insert(pt_hsetex, 0);
            hash_set_insert(pt_hsetex, 44);
            hash_set_insert(pt_hsetex, 99);
            hash_set_insert(pt_hset2, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, -74);
            hash_set_insert(pt_hsetex, 2233);
            hash_set_insert(pt_hsetex, 90);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, 334);
            hash_set_insert(pt_hsetex, 5);
            hash_set_insert(pt_hsetex, -76);
            hash_set_insert(pt_hset2, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, -4);
            hash_set_insert(pt_hset2, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 4444);
            hash_set_insert(pt_hsetex, -98);
            hash_set_insert(pt_hsetex, 2222);
            hash_set_insert(pt_hsetex, 1);
            hash_set_insert(pt_hsetex, 3);
            hash_set_insert(pt_hsetex, 55);
            hash_set_insert(pt_hset2, pt_hsetex);

            hash_set_assign(pt_hset1, pt_hset2);

            _print_hash_set_cstl(pt_hset2);
            _print_hash_set_cstl(pt_hset1);

            hash_set_destroy(pt_hsetex);
            hash_set_destroy(pt_hset1);
            hash_set_destroy(pt_hset2);
        }
        /*hash_set_swap              */
        {
            hash_set_t* pt_hset1 = create_hash_set(hash_set_t<int>);
            hash_set_t* pt_hset2 = create_hash_set(hash_set_t<int>);
            hash_set_t* pt_hsetex = create_hash_set(int);
            if(pt_hset1 == NULL || pt_hset2 == NULL || pt_hsetex == NULL)
            {
                return;
            }
            hash_set_init_ex(pt_hsetex, 200, NULL, NULL);
            hash_set_init(pt_hset2);
            hash_set_init(pt_hset1);

            hash_set_swap(pt_hset1, pt_hset2);
            _print_hash_set_cstl(pt_hset1);
            _print_hash_set_cstl(pt_hset2);

            hash_set_insert(pt_hsetex, 12239);
            hash_set_insert(pt_hsetex, 20);
            hash_set_insert(pt_hsetex, -847);
            hash_set_insert(pt_hsetex, 0);
            hash_set_insert(pt_hsetex, 44);
            hash_set_insert(pt_hsetex, 99);
            hash_set_insert(pt_hset2, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, -74);
            hash_set_insert(pt_hsetex, 2233);
            hash_set_insert(pt_hsetex, 90);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, 334);
            hash_set_insert(pt_hsetex, 5);
            hash_set_insert(pt_hsetex, -76);
            hash_set_insert(pt_hset2, pt_hsetex);

            hash_set_swap(pt_hset1, pt_hset2);
            _print_hash_set_cstl(pt_hset1);
            _print_hash_set_cstl(pt_hset2);

            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, -4);
            hash_set_insert(pt_hset2, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 4444);
            hash_set_insert(pt_hsetex, -98);
            hash_set_insert(pt_hsetex, 2222);
            hash_set_insert(pt_hsetex, 1);
            hash_set_insert(pt_hsetex, 3);
            hash_set_insert(pt_hsetex, 55);
            hash_set_insert(pt_hset2, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, 23844);
            hash_set_insert(pt_hsetex, 2);
            hash_set_insert(pt_hsetex, 4444);
            hash_set_insert(pt_hsetex, 67);
            hash_set_insert(pt_hsetex, 5098);
            hash_set_insert(pt_hsetex, 1);
            hash_set_insert(pt_hsetex, 2);
            hash_set_insert(pt_hsetex, 43);
            hash_set_clear(pt_hset2);
            hash_set_insert(pt_hset2, pt_hsetex);

            hash_set_swap(pt_hset1, pt_hset2);
            _print_hash_set_cstl(pt_hset1);
            _print_hash_set_cstl(pt_hset2);

            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 8);
            hash_set_insert(pt_hsetex, 2);
            hash_set_insert(pt_hsetex, 5);
            hash_set_insert(pt_hsetex, 9);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, 1);
            hash_set_insert(pt_hsetex, 6);
            hash_set_insert(pt_hsetex, 7);
            hash_set_insert(pt_hsetex, 3);
            hash_set_insert(pt_hsetex, 0);
            hash_set_clear(pt_hset2);
            hash_set_insert(pt_hset2, pt_hsetex);

            hash_set_swap(pt_hset1, pt_hset2);
            _print_hash_set_cstl(pt_hset2);
            _print_hash_set_cstl(pt_hset1);

            hash_set_clear(pt_hset2);
            hash_set_swap(pt_hset1, pt_hset2);
            _print_hash_set_cstl(pt_hset2);
            _print_hash_set_cstl(pt_hset1);

            hash_set_destroy(pt_hsetex);
            hash_set_destroy(pt_hset1);
            hash_set_destroy(pt_hset2);
        }
        /*hash_set_size              */
        /*hash_set_empty             */
        /*hash_set_max_size          */
        /*hash_set_bucket_count      */
        /*hash_set_hash              */
        /*hash_set_key_less          */
        {
            hash_set_t* pt_hset = create_hash_set(hash_set_t<int>);
            if(pt_hset == NULL)
            {
                return;
            }
            hash_set_init_ex(pt_hset, 100, _hash_set_cstl_hash, NULL);
            assert(hash_set_hash(pt_hset) == _hash_set_cstl_hash &&
                hash_set_key_less(pt_hset) != NULL);
            hash_set_destroy(pt_hset);
        }
        /*hash_set_resize            */
        {
            hash_set_t* pt_hset = create_hash_set(hash_set_t<int>);
            if(pt_hset == NULL)
            {
                return;
            }
            hash_set_init(pt_hset);
            _print_hash_set_cstl(pt_hset);
            hash_set_resize(pt_hset, 30);
            _print_hash_set_cstl(pt_hset);
            hash_set_resize(pt_hset, 60);
            _print_hash_set_cstl(pt_hset);
            hash_set_resize(pt_hset, 10);
            _print_hash_set_cstl(pt_hset);
            hash_set_resize(pt_hset, 0);
            _print_hash_set_cstl(pt_hset);
            hash_set_destroy(pt_hset);
        }
        /*hash_set_equal             */
        /*hash_set_not_equal         */
        /*hash_set_less              */
        /*hash_set_less_equal        */
        /*hash_set_great             */
        /*hash_set_great_equal       */
        {
            hash_set_t* pt_hset1 = create_hash_set(hash_set_t<int>);
            hash_set_t* pt_hset2 = create_hash_set(hash_set_t<int>);
            hash_set_t* pt_hsetex = create_hash_set(int);
            if(pt_hset1 == NULL || pt_hset2 == NULL || pt_hsetex == NULL)
            {
                return;
            }
            hash_set_init(pt_hsetex);
            hash_set_init(pt_hset1);
            hash_set_init(pt_hset2);
            _print_hash_set_cstl(pt_hset1);
            _print_hash_set_cstl(pt_hset2);
            printf("equal: %d, not equal: %d, ",
                hash_set_equal(pt_hset1, pt_hset2), hash_set_not_equal(pt_hset1, pt_hset2));
            printf("less: %d, less equal: %d, ",
                hash_set_less(pt_hset1, pt_hset2), hash_set_less_equal(pt_hset1, pt_hset2));
            printf("great: %d, great equal: %d\n",
                hash_set_great(pt_hset1, pt_hset2), hash_set_great_equal(pt_hset1, pt_hset2));

            hash_set_insert(pt_hsetex, 23);
            hash_set_insert(pt_hsetex, 56);
            hash_set_insert(pt_hsetex, 90);
            hash_set_insert(pt_hsetex, 3);
            hash_set_insert(pt_hset1, pt_hsetex);
            _print_hash_set_cstl(pt_hset1);
            _print_hash_set_cstl(pt_hset2);
            printf("equal: %d, not equal: %d, ",
                hash_set_equal(pt_hset1, pt_hset2), hash_set_not_equal(pt_hset1, pt_hset2));
            printf("less: %d, less equal: %d, ",
                hash_set_less(pt_hset1, pt_hset2), hash_set_less_equal(pt_hset1, pt_hset2));
            printf("great: %d, great equal: %d\n",
                hash_set_great(pt_hset1, pt_hset2), hash_set_great_equal(pt_hset1, pt_hset2));

            hash_set_insert(pt_hset2, pt_hsetex);
            _print_hash_set_cstl(pt_hset1);
            _print_hash_set_cstl(pt_hset2);
            printf("equal: %d, not equal: %d, ",
                hash_set_equal(pt_hset1, pt_hset2), hash_set_not_equal(pt_hset1, pt_hset2));
            printf("less: %d, less equal: %d, ",
                hash_set_less(pt_hset1, pt_hset2), hash_set_less_equal(pt_hset1, pt_hset2));
            printf("great: %d, great equal: %d\n",
                hash_set_great(pt_hset1, pt_hset2), hash_set_great_equal(pt_hset1, pt_hset2));

            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 333);
            hash_set_insert(pt_hsetex, 2);
            hash_set_insert(pt_hsetex, 55);
            hash_set_insert(pt_hset1, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 50);
            hash_set_insert(pt_hsetex, 55);
            hash_set_insert(pt_hset1, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 33);
            hash_set_insert(pt_hsetex, 9000);
            hash_set_insert(pt_hsetex, 1);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, 999);
            hash_set_insert(pt_hsetex, 34);
            hash_set_insert(pt_hsetex, 12);
            hash_set_insert(pt_hset2, pt_hsetex);
            _print_hash_set_cstl(pt_hset1);
            _print_hash_set_cstl(pt_hset2);
            printf("equal: %d, not equal: %d, ",
                hash_set_equal(pt_hset1, pt_hset2), hash_set_not_equal(pt_hset1, pt_hset2));
            printf("less: %d, less equal: %d, ",
                hash_set_less(pt_hset1, pt_hset2), hash_set_less_equal(pt_hset1, pt_hset2));
            printf("great: %d, great equal: %d\n",
                hash_set_great(pt_hset1, pt_hset2), hash_set_great_equal(pt_hset1, pt_hset2));
            
            hash_set_destroy(pt_hsetex);
            hash_set_destroy(pt_hset1);
            hash_set_destroy(pt_hset2);
        }
        /*hash_set_begin             */
        /*hash_set_end               */
        /*hash_set_find              */
        {
            hash_set_t* pt_hset = create_hash_set(hash_set_t<int>);
            hash_set_t* pt_hsetex = create_hash_set(int);
            iterator_t t_iter;
            if(pt_hset == NULL || pt_hsetex == NULL)
            {
                return;
            }
            hash_set_init_ex(pt_hset, 50, _hash_set_cstl_hash, NULL);
            hash_set_init(pt_hsetex);
            t_iter = hash_set_find(pt_hset, pt_hsetex);
            if(iterator_equal(t_iter, hash_set_end(pt_hset)))
            {
                printf("not found! count : %d\n", hash_set_count(pt_hset, pt_hsetex));
            }
            else
            {
                printf("found! count : %d\n", hash_set_count(pt_hset, pt_hsetex));
            }
            hash_set_insert(pt_hsetex, 12239);
            hash_set_insert(pt_hsetex, 20);
            hash_set_insert(pt_hsetex, -847);
            hash_set_insert(pt_hsetex, 0);
            hash_set_insert(pt_hsetex, 44);
            hash_set_insert(pt_hsetex, 99);
            hash_set_insert(pt_hset, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, -74);
            hash_set_insert(pt_hsetex, 2233);
            hash_set_insert(pt_hsetex, 90);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, 334);
            hash_set_insert(pt_hsetex, 5);
            hash_set_insert(pt_hsetex, -76);
            hash_set_insert(pt_hset, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, -4);
            hash_set_insert(pt_hset, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 4444);
            hash_set_insert(pt_hsetex, -98);
            hash_set_insert(pt_hsetex, 2222);
            hash_set_insert(pt_hsetex, 1);
            hash_set_insert(pt_hsetex, 3);
            hash_set_insert(pt_hsetex, 55);
            hash_set_insert(pt_hset, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, 23844);
            hash_set_insert(pt_hsetex, 2);
            hash_set_insert(pt_hsetex, 4444);
            hash_set_insert(pt_hsetex, 67);
            hash_set_insert(pt_hsetex, 5098);
            hash_set_insert(pt_hsetex, 1);
            hash_set_insert(pt_hsetex, 2);
            hash_set_insert(pt_hsetex, 43);
            hash_set_insert(pt_hset, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 8);
            hash_set_insert(pt_hsetex, 2);
            hash_set_insert(pt_hsetex, 5);
            hash_set_insert(pt_hsetex, 9);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, 1);
            hash_set_insert(pt_hsetex, 6);
            hash_set_insert(pt_hsetex, 7);
            hash_set_insert(pt_hsetex, 3);
            hash_set_insert(pt_hsetex, 0);
            hash_set_insert(pt_hset, pt_hsetex);

            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, -87);
            hash_set_insert(pt_hsetex, -90);
            hash_set_insert(pt_hsetex, -223);

            t_iter = hash_set_find(pt_hset, pt_hsetex);
            if(iterator_equal(t_iter, hash_set_end(pt_hset)))
            {
                printf("not found! count : %d\n", hash_set_count(pt_hset, pt_hsetex));
            }
            else
            {
                printf("found! count : %d\n", hash_set_count(pt_hset, pt_hsetex));
            }
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 4444);
            hash_set_insert(pt_hsetex, -98);
            hash_set_insert(pt_hsetex, 2222);
            hash_set_insert(pt_hsetex, 1);
            hash_set_insert(pt_hsetex, 3);
            hash_set_insert(pt_hsetex, 55);
            t_iter = hash_set_find(pt_hset, pt_hsetex);
            if(iterator_equal(t_iter, hash_set_end(pt_hset)))
            {
                printf("not found! count : %d\n", hash_set_count(pt_hset, pt_hsetex));
            }
            else
            {
                printf("found! count : %d\n", hash_set_count(pt_hset, pt_hsetex));
            }

            hash_set_destroy(pt_hset);
            hash_set_destroy(pt_hsetex);
        }
        /*hash_set_count             */
        /*hash_set_equal_range       */
        {
            hash_set_t* pt_hset = create_hash_set(hash_set_t<int>);
            hash_set_t* pt_hsetex = create_hash_set(int);
            range_t t_range;
            if(pt_hset == NULL || pt_hsetex == NULL)
            {
                return;
            }
            hash_set_init_ex(pt_hset, 50, _hash_set_cstl_hash, NULL);
            hash_set_init(pt_hsetex);
            t_range = hash_set_equal_range(pt_hset, pt_hsetex);
            assert(iterator_equal(t_range.t_begin, t_range.t_end) &&
                iterator_equal(t_range.t_begin, hash_set_end(pt_hset)));
            hash_set_insert(pt_hsetex, 12239);
            hash_set_insert(pt_hsetex, 20);
            hash_set_insert(pt_hsetex, -847);
            hash_set_insert(pt_hsetex, 0);
            hash_set_insert(pt_hsetex, 44);
            hash_set_insert(pt_hsetex, 99);
            hash_set_insert(pt_hset, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, -74);
            hash_set_insert(pt_hsetex, 2233);
            hash_set_insert(pt_hsetex, 90);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, 334);
            hash_set_insert(pt_hsetex, 5);
            hash_set_insert(pt_hsetex, -76);
            hash_set_insert(pt_hset, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, -4);
            hash_set_insert(pt_hset, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 4444);
            hash_set_insert(pt_hsetex, -98);
            hash_set_insert(pt_hsetex, 2222);
            hash_set_insert(pt_hsetex, 1);
            hash_set_insert(pt_hsetex, 3);
            hash_set_insert(pt_hsetex, 55);
            hash_set_insert(pt_hset, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, 23844);
            hash_set_insert(pt_hsetex, 2);
            hash_set_insert(pt_hsetex, 4444);
            hash_set_insert(pt_hsetex, 67);
            hash_set_insert(pt_hsetex, 5098);
            hash_set_insert(pt_hsetex, 1);
            hash_set_insert(pt_hsetex, 2);
            hash_set_insert(pt_hsetex, 43);
            hash_set_insert(pt_hset, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 8);
            hash_set_insert(pt_hsetex, 2);
            hash_set_insert(pt_hsetex, 5);
            hash_set_insert(pt_hsetex, 9);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, 1);
            hash_set_insert(pt_hsetex, 6);
            hash_set_insert(pt_hsetex, 7);
            hash_set_insert(pt_hsetex, 3);
            hash_set_insert(pt_hsetex, 0);
            hash_set_insert(pt_hset, pt_hsetex);

            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 4444);
            hash_set_insert(pt_hsetex, -98);
            hash_set_insert(pt_hsetex, 3);
            hash_set_insert(pt_hsetex, 55);
            t_range = hash_set_equal_range(pt_hset, pt_hsetex);
            assert(iterator_equal(t_range.t_begin, t_range.t_end));

            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 4444);
            hash_set_insert(pt_hsetex, -98);
            hash_set_insert(pt_hsetex, 2222);
            hash_set_insert(pt_hsetex, 1);
            hash_set_insert(pt_hsetex, 3);
            hash_set_insert(pt_hsetex, 55);

            t_range = hash_set_equal_range(pt_hset, pt_hsetex);
            assert(iterator_equal(iterator_next(t_range.t_begin), t_range.t_end));
            hash_set_destroy(pt_hset);
            hash_set_destroy(pt_hsetex);
        }
        /*hash_set_insert            */
        {
            hash_set_t* pt_hset = create_hash_set(hash_set_t<int>);
            hash_set_t* pt_hsetex = create_hash_set(int);
            if(pt_hset == NULL || pt_hsetex == NULL)
            {
                return;
            }
            hash_set_init_ex(pt_hset, 50, _hash_set_cstl_hash, NULL);
            hash_set_init(pt_hsetex);

            hash_set_insert(pt_hsetex, 4444);
            hash_set_insert(pt_hsetex, -98);
            hash_set_insert(pt_hsetex, 2222);
            hash_set_insert(pt_hsetex, 1);
            hash_set_insert(pt_hsetex, 3);
            hash_set_insert(pt_hsetex, 55);
            hash_set_insert(pt_hset, pt_hsetex);
            _print_hash_set_cstl(pt_hset);

            hash_set_insert(pt_hset, pt_hsetex);
            _print_hash_set_cstl(pt_hset);

            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 4444);
            hash_set_insert(pt_hsetex, -98);
            hash_set_insert(pt_hsetex, 3);
            hash_set_insert(pt_hsetex, 55);
            hash_set_insert(pt_hset, pt_hsetex);
            _print_hash_set_cstl(pt_hset);

            hash_set_destroy(pt_hset);
            hash_set_destroy(pt_hsetex);
        }
        /*hash_set_insert_range      */
        {
            hash_set_t* pt_hset1 = create_hash_set(hash_set_t<int>);
            hash_set_t* pt_hset2 = create_hash_set(hash_set_t<int>);
            hash_set_t* pt_hsetex = create_hash_set(int);
            if(pt_hset1 == NULL || pt_hset2 == NULL || pt_hsetex == NULL)
            {
                return;
            }
            hash_set_init(pt_hsetex);
            hash_set_init_ex(pt_hset2, 50, _hash_set_cstl_hash, NULL);
            hash_set_init_ex(pt_hset1, 50, _hash_set_cstl_hash, NULL);

            hash_set_insert_range(pt_hset1, hash_set_begin(pt_hset2), hash_set_end(pt_hset2));
            _print_hash_set_cstl(pt_hset1);

            hash_set_insert(pt_hsetex, 12239);
            hash_set_insert(pt_hsetex, 20);
            hash_set_insert(pt_hsetex, -847);
            hash_set_insert(pt_hsetex, 0);
            hash_set_insert(pt_hsetex, 44);
            hash_set_insert(pt_hsetex, 99);
            hash_set_insert(pt_hset2, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, -74);
            hash_set_insert(pt_hsetex, 2233);
            hash_set_insert(pt_hsetex, 90);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, 334);
            hash_set_insert(pt_hsetex, 5);
            hash_set_insert(pt_hsetex, -76);
            hash_set_insert(pt_hset2, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, -4);
            hash_set_insert(pt_hset2, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 4444);
            hash_set_insert(pt_hsetex, -98);
            hash_set_insert(pt_hsetex, 2222);
            hash_set_insert(pt_hsetex, 1);
            hash_set_insert(pt_hsetex, 3);
            hash_set_insert(pt_hsetex, 55);
            hash_set_insert(pt_hset2, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, 23844);
            hash_set_insert(pt_hsetex, 2);
            hash_set_insert(pt_hsetex, 4444);
            hash_set_insert(pt_hsetex, 67);
            hash_set_insert(pt_hsetex, 5098);
            hash_set_insert(pt_hsetex, 1);
            hash_set_insert(pt_hsetex, 2);
            hash_set_insert(pt_hsetex, 43);
            hash_set_insert(pt_hset2, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 8);
            hash_set_insert(pt_hsetex, 2);
            hash_set_insert(pt_hsetex, 5);
            hash_set_insert(pt_hsetex, 9);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, 1);
            hash_set_insert(pt_hsetex, 6);
            hash_set_insert(pt_hsetex, 7);
            hash_set_insert(pt_hsetex, 3);
            hash_set_insert(pt_hsetex, 0);
            hash_set_insert(pt_hset2, pt_hsetex);
            _print_hash_set_cstl(pt_hset2);

            hash_set_insert_range(pt_hset1, hash_set_begin(pt_hset2), hash_set_begin(pt_hset2));
            _print_hash_set_cstl(pt_hset1);
            hash_set_insert_range(pt_hset1, hash_set_begin(pt_hset2), iterator_advance(hash_set_begin(pt_hset2), 2));
            _print_hash_set_cstl(pt_hset1);
            hash_set_insert_range(pt_hset1, iterator_advance(hash_set_begin(pt_hset2), 3), iterator_advance(hash_set_begin(pt_hset2), 4));
            _print_hash_set_cstl(pt_hset1);
            hash_set_insert_range(pt_hset1, iterator_advance(hash_set_begin(pt_hset2), 5), hash_set_end(pt_hset2));
            _print_hash_set_cstl(pt_hset1);
            hash_set_insert_range(pt_hset1, hash_set_end(pt_hset2), hash_set_end(pt_hset2));
            _print_hash_set_cstl(pt_hset1);

            hash_set_clear(pt_hset1);
            hash_set_insert_range(pt_hset1, hash_set_begin(pt_hset2), hash_set_end(pt_hset2));
            _print_hash_set_cstl(pt_hset1);

            hash_set_destroy(pt_hsetex);
            hash_set_destroy(pt_hset1);
            hash_set_destroy(pt_hset2);
        }
        /*hash_set_erase             */
        {
            hash_set_t* pt_hset = create_hash_set(hash_set_t<int>);
            hash_set_t* pt_hsetex = create_hash_set(int);
            if(pt_hset == NULL || pt_hsetex == NULL)
            {
                return;
            }
            hash_set_init_ex(pt_hset, 50, _hash_set_cstl_hash, NULL);
            hash_set_init(pt_hsetex);
            _print_hash_set_cstl(pt_hset);
            hash_set_erase(pt_hset, pt_hsetex);

            hash_set_insert(pt_hsetex, 12239);
            hash_set_insert(pt_hsetex, 20);
            hash_set_insert(pt_hsetex, -847);
            hash_set_insert(pt_hsetex, 0);
            hash_set_insert(pt_hsetex, 44);
            hash_set_insert(pt_hsetex, 99);
            hash_set_insert(pt_hset, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, -74);
            hash_set_insert(pt_hsetex, 2233);
            hash_set_insert(pt_hsetex, 90);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, 334);
            hash_set_insert(pt_hsetex, 5);
            hash_set_insert(pt_hsetex, -76);
            hash_set_insert(pt_hset, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, -4);
            hash_set_insert(pt_hset, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 4444);
            hash_set_insert(pt_hsetex, -98);
            hash_set_insert(pt_hsetex, 2222);
            hash_set_insert(pt_hsetex, 1);
            hash_set_insert(pt_hsetex, 3);
            hash_set_insert(pt_hsetex, 55);
            hash_set_insert(pt_hset, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, 23844);
            hash_set_insert(pt_hsetex, 2);
            hash_set_insert(pt_hsetex, 4444);
            hash_set_insert(pt_hsetex, 67);
            hash_set_insert(pt_hsetex, 5098);
            hash_set_insert(pt_hsetex, 1);
            hash_set_insert(pt_hsetex, 2);
            hash_set_insert(pt_hsetex, 43);
            hash_set_insert(pt_hset, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 8);
            hash_set_insert(pt_hsetex, 2);
            hash_set_insert(pt_hsetex, 5);
            hash_set_insert(pt_hsetex, 9);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, 1);
            hash_set_insert(pt_hsetex, 6);
            hash_set_insert(pt_hsetex, 7);
            hash_set_insert(pt_hsetex, 3);
            hash_set_insert(pt_hsetex, 0);
            hash_set_insert(pt_hset, pt_hsetex);
            _print_hash_set_cstl(pt_hset);

            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 4444);
            hash_set_insert(pt_hsetex, -98);
            hash_set_insert(pt_hsetex, 3);
            hash_set_insert(pt_hsetex, 55);
            hash_set_erase(pt_hset, pt_hsetex);
            _print_hash_set_cstl(pt_hset);

            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 4444);
            hash_set_insert(pt_hsetex, -98);
            hash_set_insert(pt_hsetex, 2222);
            hash_set_insert(pt_hsetex, 1);
            hash_set_insert(pt_hsetex, 3);
            hash_set_insert(pt_hsetex, 55);
            hash_set_erase(pt_hset, pt_hsetex);
            _print_hash_set_cstl(pt_hset);

            hash_set_destroy(pt_hset);
            hash_set_destroy(pt_hsetex);
        }
        /*hash_set_erase_pos         */
        {
            hash_set_t* pt_hset = create_hash_set(hash_set_t<int>);
            hash_set_t* pt_hsetex = create_hash_set(int);
            if(pt_hset == NULL || pt_hsetex == NULL)
            {
                return;
            }
            hash_set_init_ex(pt_hset, 50, _hash_set_cstl_hash, NULL);
            hash_set_init(pt_hsetex);

            hash_set_insert(pt_hsetex, 12239);
            hash_set_insert(pt_hsetex, 20);
            hash_set_insert(pt_hsetex, -847);
            hash_set_insert(pt_hsetex, 0);
            hash_set_insert(pt_hsetex, 44);
            hash_set_insert(pt_hsetex, 99);
            hash_set_insert(pt_hset, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, -74);
            hash_set_insert(pt_hsetex, 2233);
            hash_set_insert(pt_hsetex, 90);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, 334);
            hash_set_insert(pt_hsetex, 5);
            hash_set_insert(pt_hsetex, -76);
            hash_set_insert(pt_hset, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, -4);
            hash_set_insert(pt_hset, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 4444);
            hash_set_insert(pt_hsetex, -98);
            hash_set_insert(pt_hsetex, 2222);
            hash_set_insert(pt_hsetex, 1);
            hash_set_insert(pt_hsetex, 3);
            hash_set_insert(pt_hsetex, 55);
            hash_set_insert(pt_hset, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, 23844);
            hash_set_insert(pt_hsetex, 2);
            hash_set_insert(pt_hsetex, 4444);
            hash_set_insert(pt_hsetex, 67);
            hash_set_insert(pt_hsetex, 5098);
            hash_set_insert(pt_hsetex, 1);
            hash_set_insert(pt_hsetex, 2);
            hash_set_insert(pt_hsetex, 43);
            hash_set_insert(pt_hset, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 8);
            hash_set_insert(pt_hsetex, 2);
            hash_set_insert(pt_hsetex, 5);
            hash_set_insert(pt_hsetex, 9);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, 1);
            hash_set_insert(pt_hsetex, 6);
            hash_set_insert(pt_hsetex, 7);
            hash_set_insert(pt_hsetex, 3);
            hash_set_insert(pt_hsetex, 0);
            hash_set_insert(pt_hset, pt_hsetex);
            _print_hash_set_cstl(pt_hset);

            hash_set_erase_pos(pt_hset, hash_set_begin(pt_hset));
            _print_hash_set_cstl(pt_hset);
            hash_set_erase_pos(pt_hset, iterator_advance(hash_set_begin(pt_hset), 2));
            _print_hash_set_cstl(pt_hset);
            while(!hash_set_empty(pt_hset))
            {
                hash_set_erase_pos(pt_hset, hash_set_begin(pt_hset));
            }
            _print_hash_set_cstl(pt_hset);

            hash_set_destroy(pt_hset);
            hash_set_destroy(pt_hsetex);
        }
        /*hash_set_erase_range       */
        {
            hash_set_t* pt_hset = create_hash_set(hash_set_t<int>);
            hash_set_t* pt_hsetex = create_hash_set(int);
            if(pt_hset == NULL || pt_hsetex == NULL)
            {
                return;
            }
            hash_set_init_ex(pt_hset, 50, _hash_set_cstl_hash, NULL);
            hash_set_init(pt_hsetex);
            hash_set_erase_range(pt_hset, hash_set_begin(pt_hset), hash_set_end(pt_hset));
            _print_hash_set_cstl(pt_hset);

            hash_set_insert(pt_hsetex, 12239);
            hash_set_insert(pt_hsetex, 20);
            hash_set_insert(pt_hsetex, -847);
            hash_set_insert(pt_hsetex, 0);
            hash_set_insert(pt_hsetex, 44);
            hash_set_insert(pt_hsetex, 99);
            hash_set_insert(pt_hset, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, -74);
            hash_set_insert(pt_hsetex, 2233);
            hash_set_insert(pt_hsetex, 90);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, 334);
            hash_set_insert(pt_hsetex, 5);
            hash_set_insert(pt_hsetex, -76);
            hash_set_insert(pt_hset, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, -4);
            hash_set_insert(pt_hset, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 4444);
            hash_set_insert(pt_hsetex, -98);
            hash_set_insert(pt_hsetex, 2222);
            hash_set_insert(pt_hsetex, 1);
            hash_set_insert(pt_hsetex, 3);
            hash_set_insert(pt_hsetex, 55);
            hash_set_insert(pt_hset, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, 23844);
            hash_set_insert(pt_hsetex, 2);
            hash_set_insert(pt_hsetex, 4444);
            hash_set_insert(pt_hsetex, 67);
            hash_set_insert(pt_hsetex, 5098);
            hash_set_insert(pt_hsetex, 1);
            hash_set_insert(pt_hsetex, 2);
            hash_set_insert(pt_hsetex, 43);
            hash_set_insert(pt_hset, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 8);
            hash_set_insert(pt_hsetex, 2);
            hash_set_insert(pt_hsetex, 5);
            hash_set_insert(pt_hsetex, 9);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, 1);
            hash_set_insert(pt_hsetex, 6);
            hash_set_insert(pt_hsetex, 7);
            hash_set_insert(pt_hsetex, 3);
            hash_set_insert(pt_hsetex, 0);
            hash_set_insert(pt_hset, pt_hsetex);
            _print_hash_set_cstl(pt_hset);

            hash_set_erase_range(pt_hset, hash_set_begin(pt_hset), hash_set_begin(pt_hset));
            _print_hash_set_cstl(pt_hset);
            hash_set_erase_range(pt_hset, hash_set_begin(pt_hset), iterator_advance(hash_set_begin(pt_hset), 2));
            _print_hash_set_cstl(pt_hset);
            hash_set_erase_range(pt_hset, iterator_next(hash_set_begin(pt_hset)), iterator_advance(hash_set_begin(pt_hset), 2));
            _print_hash_set_cstl(pt_hset);
            hash_set_erase_range(pt_hset, iterator_next(hash_set_begin(pt_hset)), hash_set_end(pt_hset));
            _print_hash_set_cstl(pt_hset);
            hash_set_erase_range(pt_hset, hash_set_end(pt_hset), hash_set_end(pt_hset));
            _print_hash_set_cstl(pt_hset);
            hash_set_erase_range(pt_hset, hash_set_begin(pt_hset), hash_set_end(pt_hset));
            _print_hash_set_cstl(pt_hset);

            hash_set_destroy(pt_hset);
            hash_set_destroy(pt_hsetex);
        }
        /*hash_set_clear             */
        {
            hash_set_t* pt_hset = create_hash_set(hash_set_t<int>);
            hash_set_t* pt_hsetex = create_hash_set(int);
            if(pt_hset == NULL || pt_hsetex == NULL)
            {
                return;
            }
            hash_set_init_ex(pt_hset, 50, _hash_set_cstl_hash, NULL);
            hash_set_init(pt_hsetex);

            hash_set_clear(pt_hset);
            _print_hash_set_cstl(pt_hset);

            hash_set_insert(pt_hsetex, 12239);
            hash_set_insert(pt_hsetex, 20);
            hash_set_insert(pt_hsetex, -847);
            hash_set_insert(pt_hsetex, 0);
            hash_set_insert(pt_hsetex, 44);
            hash_set_insert(pt_hsetex, 99);
            hash_set_insert(pt_hset, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, -74);
            hash_set_insert(pt_hsetex, 2233);
            hash_set_insert(pt_hsetex, 90);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, 334);
            hash_set_insert(pt_hsetex, 5);
            hash_set_insert(pt_hsetex, -76);
            hash_set_insert(pt_hset, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, -4);
            hash_set_insert(pt_hset, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 4444);
            hash_set_insert(pt_hsetex, -98);
            hash_set_insert(pt_hsetex, 2222);
            hash_set_insert(pt_hsetex, 1);
            hash_set_insert(pt_hsetex, 3);
            hash_set_insert(pt_hsetex, 55);
            hash_set_insert(pt_hset, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, 23844);
            hash_set_insert(pt_hsetex, 2);
            hash_set_insert(pt_hsetex, 4444);
            hash_set_insert(pt_hsetex, 67);
            hash_set_insert(pt_hsetex, 5098);
            hash_set_insert(pt_hsetex, 1);
            hash_set_insert(pt_hsetex, 2);
            hash_set_insert(pt_hsetex, 43);
            hash_set_insert(pt_hset, pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, 8);
            hash_set_insert(pt_hsetex, 2);
            hash_set_insert(pt_hsetex, 5);
            hash_set_insert(pt_hsetex, 9);
            hash_set_insert(pt_hsetex, 4);
            hash_set_insert(pt_hsetex, 1);
            hash_set_insert(pt_hsetex, 6);
            hash_set_insert(pt_hsetex, 7);
            hash_set_insert(pt_hsetex, 3);
            hash_set_insert(pt_hsetex, 0);
            hash_set_insert(pt_hset, pt_hsetex);
            _print_hash_set_cstl(pt_hset);

            hash_set_clear(pt_hset);
            _print_hash_set_cstl(pt_hset);

            hash_set_destroy(pt_hset);
            hash_set_destroy(pt_hsetex);
        }
    }
    /* c-string type */
    {
        /*create_hash_set            */
        {
            hash_set_t* pt_hset = create_hash_set(char*);
            if(pt_hset == NULL)
            {
                return;
            }
            hash_set_init(pt_hset);
            hash_set_insert(pt_hset, "abcdefg");
            hash_set_insert(pt_hset, "ooooooooooooooooo");
            hash_set_insert(pt_hset, "hhhhkadfoqwbn");
            hash_set_insert(pt_hset, "12124120");
            _print_hash_set_cstr(pt_hset);
            hash_set_destroy(pt_hset);
        }
        /*hash_set_init              */
        /*hash_set_init_ex           */
        {
            hash_set_t* pt_hset = create_hash_set(char*);
            if(pt_hset == NULL)
            {
                return;
            }
            hash_set_init_ex(pt_hset, 50, _hash_set_cstr_hash, NULL);
            hash_set_insert(pt_hset, "999");
            hash_set_insert(pt_hset, "7");
            hash_set_insert(pt_hset, "bbaklsf");
            hash_set_insert(pt_hset, "1111111111111");
            hash_set_insert(pt_hset, "yyy");
            _print_hash_set_cstr(pt_hset);
            hash_set_destroy(pt_hset);
        }
        /*hash_set_init_copy         */
        {
            hash_set_t* pt_hset = create_hash_set(char*);
            hash_set_t* pt_hsetex = create_hash_set(char*);
            if(pt_hset == NULL || pt_hsetex == NULL)
            {
                return;
            }
            hash_set_init_ex(pt_hsetex, 100, _hash_set_cstr_hash, NULL);
            hash_set_insert(pt_hsetex, "bbbb");
            hash_set_insert(pt_hsetex, "99999999");
            hash_set_insert(pt_hsetex, "");
            hash_set_insert(pt_hsetex, "vv");
            hash_set_insert(pt_hsetex, "nnn");
            hash_set_insert(pt_hsetex, ".,._t_hashtable,");
            hash_set_init_copy(pt_hset, pt_hsetex);
            _print_hash_set_cstr(pt_hset);
            hash_set_destroy(pt_hsetex);
            hash_set_destroy(pt_hset);
        }
        /*hash_set_init_copy_range   */
        {
            hash_set_t* pt_hset = create_hash_set(char*);
            hash_set_t* pt_hsetex = create_hash_set(char*);
            if(pt_hset == NULL || pt_hsetex == NULL)
            {
                return;
            }
            hash_set_init_ex(pt_hsetex, 100, _hash_set_cstr_hash, _hash_set_cstr_less);
            hash_set_insert(pt_hsetex, "abcdefghijklmn");
            hash_set_insert(pt_hsetex, "00000000");
            hash_set_insert(pt_hsetex, "uu");
            hash_set_insert(pt_hsetex, "abcdefghijklmn");
            hash_set_insert(pt_hsetex, "94lebgqoi34asdh;adfasd");
            hash_set_insert(pt_hsetex, "787878");
            hash_set_insert(pt_hsetex, "444444");
            hash_set_insert(pt_hsetex, "4902u30230");
            hash_set_insert(pt_hsetex, "tta");
            hash_set_init_copy_range(pt_hset,
                hash_set_begin(pt_hsetex), hash_set_end(pt_hsetex));
            _print_hash_set_cstr(pt_hsetex);
            _print_hash_set_cstr(pt_hset);
            hash_set_destroy(pt_hset);
            hash_set_destroy(pt_hsetex);
        }
        /*hash_set_init_copy_range_ex*/
        {
            hash_set_t* pt_hset = create_hash_set(char*);
            hash_set_t* pt_hsetex = create_hash_set(char*);
            if(pt_hset == NULL || pt_hsetex == NULL)
            {
                return;
            }
            hash_set_init(pt_hsetex);
            hash_set_insert(pt_hsetex, "abcdefghijklmn");
            hash_set_insert(pt_hsetex, "00000000");
            hash_set_insert(pt_hsetex, "uu");
            hash_set_insert(pt_hsetex, "abcdefghijklmn");
            hash_set_insert(pt_hsetex, "94lebgqoi34asdh;adfasd");
            hash_set_insert(pt_hsetex, "787878");
            hash_set_insert(pt_hsetex, "444444");
            hash_set_insert(pt_hsetex, "4902u30230");
            hash_set_insert(pt_hsetex, "tta");
            hash_set_init_copy_range_ex(pt_hset,
                hash_set_begin(pt_hsetex),
                hash_set_end(pt_hsetex),
                100, _hash_set_cstr_hash, _hash_set_cstr_less);
            _print_hash_set_cstr(pt_hsetex);
            _print_hash_set_cstr(pt_hset);
            hash_set_destroy(pt_hset);
            hash_set_destroy(pt_hsetex);
        }
        /*hash_set_destroy           */
        /*hash_set_assign            */
        {
            hash_set_t* pt_hset = create_hash_set(char*);
            hash_set_t* pt_hsetex = create_hash_set(char*);
            if(pt_hset == NULL || pt_hsetex == NULL)
            {
                return;
            }
            hash_set_init(pt_hsetex);
            hash_set_init(pt_hset);
            hash_set_assign(pt_hset, pt_hsetex);
            _print_hash_set_cstr(pt_hset);
            hash_set_insert(pt_hsetex, "abcdefghijklmn");
            hash_set_insert(pt_hsetex, "00000000");
            hash_set_insert(pt_hsetex, "uu");
            hash_set_assign(pt_hset, pt_hsetex);
            _print_hash_set_cstr(pt_hset);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, "abcdefghijklmn");
            hash_set_insert(pt_hsetex, "94lebgqoi34asdh;adfasd");
            hash_set_insert(pt_hsetex, "787878");
            hash_set_insert(pt_hsetex, "444444");
            hash_set_insert(pt_hsetex, "4902u30230");
            hash_set_insert(pt_hsetex, "tta");
            hash_set_assign(pt_hset, pt_hsetex);
            _print_hash_set_cstr(pt_hset);
            hash_set_clear(pt_hsetex);
            hash_set_assign(pt_hset, pt_hsetex);
            _print_hash_set_cstr(pt_hset);
            hash_set_destroy(pt_hset);
            hash_set_destroy(pt_hsetex);
        }
        /*hash_set_swap              */
        {
            hash_set_t* pt_hset = create_hash_set(char*);
            hash_set_t* pt_hsetex = create_hash_set(char*);
            if(pt_hset == NULL || pt_hsetex == NULL)
            {
                return;
            }
            hash_set_init_ex(pt_hsetex, 50, _hash_set_cstr_hash, NULL);
            hash_set_init_ex(pt_hset, 50, _hash_set_cstr_hash, NULL);
            hash_set_swap(pt_hset, pt_hsetex);
            _print_hash_set_cstr(pt_hset);
            _print_hash_set_cstr(pt_hsetex);
            hash_set_insert(pt_hsetex, "abcdefghijklmn");
            hash_set_insert(pt_hsetex, "00000000");
            hash_set_insert(pt_hsetex, "uu");
            hash_set_swap(pt_hset, pt_hsetex);
            _print_hash_set_cstr(pt_hset);
            _print_hash_set_cstr(pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, "abcdefghijklmn");
            hash_set_insert(pt_hsetex, "94lebgqoi34asdh;adfasd");
            hash_set_insert(pt_hsetex, "787878");
            hash_set_insert(pt_hsetex, "444444");
            hash_set_insert(pt_hsetex, "4902u30230");
            hash_set_insert(pt_hsetex, "tta");
            hash_set_insert(pt_hsetex, "444444");
            hash_set_swap(pt_hset, pt_hsetex);
            _print_hash_set_cstr(pt_hset);
            _print_hash_set_cstr(pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_insert(pt_hsetex, "66666");
            hash_set_insert(pt_hsetex, "al;dhiqwegfbfgoqwehfodghf");
            hash_set_swap(pt_hset, pt_hsetex);
            _print_hash_set_cstr(pt_hset);
            _print_hash_set_cstr(pt_hsetex);
            hash_set_clear(pt_hsetex);
            hash_set_swap(pt_hset, pt_hsetex);
            _print_hash_set_cstr(pt_hset);
            _print_hash_set_cstr(pt_hsetex);
            hash_set_destroy(pt_hset);
            hash_set_destroy(pt_hsetex);
        }
        /*hash_set_size              */
        /*hash_set_empty             */
        /*hash_set_max_size          */
        /*hash_set_bucket_count      */
        /*hash_set_hash              */
        /*hash_set_key_less          */
        {
            hash_set_t* pt_hset = create_hash_set(char*);
            if(pt_hset == NULL)
            {
                return;
            }
            hash_set_init_ex(pt_hset, 100, _hash_set_cstr_hash, _hash_set_cstr_less);
            assert(hash_set_hash(pt_hset) == _hash_set_cstr_hash &&
                hash_set_key_less(pt_hset) == _hash_set_cstr_less);
            hash_set_destroy(pt_hset);
        }
        /*hash_set_resize            */
        {
            hash_set_t* pt_hset = create_hash_set(char*);
            if(pt_hset == NULL)
            {
                return;
            }
            hash_set_init(pt_hset);
            _print_hash_set_cstr(pt_hset);
            hash_set_resize(pt_hset, 100);
            _print_hash_set_cstr(pt_hset);
            hash_set_resize(pt_hset, 400);
            _print_hash_set_cstr(pt_hset);
            hash_set_resize(pt_hset, 10);
            _print_hash_set_cstr(pt_hset);
            hash_set_resize(pt_hset, 0);
            _print_hash_set_cstr(pt_hset);
            hash_set_destroy(pt_hset);
        }
        /*hash_set_equal             */
        /*hash_set_not_equal         */
        /*hash_set_less              */
        /*hash_set_less_equal        */
        /*hash_set_great             */
        /*hash_set_great_equal       */
        {
            hash_set_t* pt_hset = create_hash_set(char*);
            hash_set_t* pt_hsetex = create_hash_set(char*);
            if(pt_hset == NULL || pt_hsetex == NULL)
            {
                return;
            }
            hash_set_init_ex(pt_hset, 100, _hash_set_cstr_hash, NULL);
            hash_set_init_ex(pt_hsetex, 100, _hash_set_cstr_hash, NULL);
            _print_hash_set_cstr(pt_hset);
            _print_hash_set_cstr(pt_hsetex);
            printf("equal: %d, not equal: %d, ",
                hash_set_equal(pt_hset, pt_hsetex), hash_set_not_equal(pt_hset, pt_hsetex));
            printf("less: %d, less equal: %d, ",
                hash_set_less(pt_hset, pt_hsetex), hash_set_less_equal(pt_hset, pt_hsetex));
            printf("great: %d, great equal: %d\n",
                hash_set_great(pt_hset, pt_hsetex), hash_set_great_equal(pt_hset, pt_hsetex));

            hash_set_insert(pt_hset, "ynuopqdasdgq");
            _print_hash_set_cstr(pt_hset);
            _print_hash_set_cstr(pt_hsetex);
            printf("equal: %d, not equal: %d, ",
                hash_set_equal(pt_hset, pt_hsetex), hash_set_not_equal(pt_hset, pt_hsetex));
            printf("less: %d, less equal: %d, ",
                hash_set_less(pt_hset, pt_hsetex), hash_set_less_equal(pt_hset, pt_hsetex));
            printf("great: %d, great equal: %d\n",
                hash_set_great(pt_hset, pt_hsetex), hash_set_great_equal(pt_hset, pt_hsetex));

            hash_set_insert(pt_hsetex, "ynuopqdasdgq");
            _print_hash_set_cstr(pt_hset);
            _print_hash_set_cstr(pt_hsetex);
            printf("equal: %d, not equal: %d, ",
                hash_set_equal(pt_hset, pt_hsetex), hash_set_not_equal(pt_hset, pt_hsetex));
            printf("less: %d, less equal: %d, ",
                hash_set_less(pt_hset, pt_hsetex), hash_set_less_equal(pt_hset, pt_hsetex));
            printf("great: %d, great equal: %d\n",
                hash_set_great(pt_hset, pt_hsetex), hash_set_great_equal(pt_hset, pt_hsetex));

            hash_set_insert(pt_hset, "ynuop");
            hash_set_insert(pt_hset, "vvvvvvvv");
            hash_set_insert(pt_hset, "bbbbbb");
            hash_set_insert(pt_hsetex, "ynuopqdasdgqxxxxxxx");
            _print_hash_set_cstr(pt_hset);
            _print_hash_set_cstr(pt_hsetex);
            printf("equal: %d, not equal: %d, ",
                hash_set_equal(pt_hset, pt_hsetex), hash_set_not_equal(pt_hset, pt_hsetex));
            printf("less: %d, less equal: %d, ",
                hash_set_less(pt_hset, pt_hsetex), hash_set_less_equal(pt_hset, pt_hsetex));
            printf("great: %d, great equal: %d\n",
                hash_set_great(pt_hset, pt_hsetex), hash_set_great_equal(pt_hset, pt_hsetex));

            hash_set_destroy(pt_hset);
            hash_set_destroy(pt_hsetex);
        }
        /*hash_set_begin             */
        /*hash_set_end               */
        /*hash_set_find              */
        {
            hash_set_t* pt_hset = create_hash_set(char*);
            iterator_t t_iter;
            if(pt_hset == NULL)
            {
                return;
            }
            hash_set_init_ex(pt_hset, 10, _hash_set_cstr_hash, NULL);
            t_iter = hash_set_find(pt_hset, "abcdefg");
            if(iterator_equal(t_iter, hash_set_end(pt_hset)))
            {
                printf("not found, count : %d\n", hash_set_count(pt_hset, "abcdefg"));
            }
            else
            {
                printf("found, count : %d\n", hash_set_count(pt_hset, "abcdefg"));
            }

            hash_set_insert(pt_hset, "rtrtrtm");
            hash_set_insert(pt_hset, "bvn");
            hash_set_insert(pt_hset, "abcdefg");
            hash_set_insert(pt_hset, ",._t_hashtable,._t_.,.,..,.,.,");
            hash_set_insert(pt_hset, "vvv");
            _print_hash_set_cstr(pt_hset);

            t_iter = hash_set_find(pt_hset, "mmmmmm");
            if(iterator_equal(t_iter, hash_set_end(pt_hset)))
            {
                printf("not found, count : %d\n", hash_set_count(pt_hset, "mmmmmm"));
            }
            else
            {
                printf("found, count : %d\n", hash_set_count(pt_hset, "mmmmmm"));
            }
            t_iter = hash_set_find(pt_hset, "abcdefg");
            if(iterator_equal(t_iter, hash_set_end(pt_hset)))
            {
                printf("not found, count : %d\n", hash_set_count(pt_hset, "abcdefg"));
            }
            else
            {
                printf("found, count : %d\n", hash_set_count(pt_hset, "abcdefg"));
            }

            hash_set_destroy(pt_hset);
        }
        /*hash_set_count             */
        /*hash_set_equal_range       */
        {
            hash_set_t* pt_hset = create_hash_set(char*);
            range_t t_range;
            if(pt_hset == NULL)
            {
                return;
            }
            hash_set_init_ex(pt_hset, 10, _hash_set_cstr_hash, NULL);
            t_range = hash_set_equal_range(pt_hset, "abcdefg");
            assert(iterator_equal(t_range.t_begin, hash_set_end(pt_hset)) &&
                iterator_equal(t_range.t_begin, t_range.t_end));
            hash_set_insert(pt_hset, "lskdj");
            hash_set_insert(pt_hset, "bbbbbbbbb");
            hash_set_insert(pt_hset, "abcdefg");
            hash_set_insert(pt_hset, "nmnm");
            hash_set_insert(pt_hset, "mmmm");
            _print_hash_set_cstr(pt_hset);
            t_range = hash_set_equal_range(pt_hset, "opqrst");
            assert(iterator_equal(t_range.t_begin, t_range.t_end));
            t_range = hash_set_equal_range(pt_hset, "abcdefg");
            assert(iterator_equal(iterator_next(t_range.t_begin), t_range.t_end));
            hash_set_destroy(pt_hset);
        }
        /*hash_set_insert            */
        {
            hash_set_t* pt_hset = create_hash_set(char*);
            if(pt_hset == NULL)
            {
                return;
            }
            hash_set_init_ex(pt_hset, 45, _hash_set_cstr_hash, NULL);
            _print_hash_set_cstr(pt_hset);
            hash_set_insert(pt_hset, "45454545");
            hash_set_insert(pt_hset, "00000");
            hash_set_insert(pt_hset, "124!@##@");
            hash_set_insert(pt_hset, "%^&*");
            _print_hash_set_cstr(pt_hset);
            hash_set_insert(pt_hset, "00000");
            hash_set_insert(pt_hset, "%^&*");
            hash_set_insert(pt_hset, "--------");
            _print_hash_set_cstr(pt_hset);
            hash_set_destroy(pt_hset);
        }
        /*hash_set_insert_range      */
        {
            hash_set_t* pt_hset = create_hash_set(char*);
            hash_set_t* pt_hsetex = create_hash_set(char*);
            if(pt_hset == NULL || pt_hsetex == NULL)
            {
                return;
            }
            hash_set_init_ex(pt_hset, 100, _hash_set_cstr_hash, NULL);
            hash_set_init(pt_hsetex);
            hash_set_insert_range(pt_hset, hash_set_begin(pt_hsetex), hash_set_end(pt_hsetex));
            _print_hash_set_cstr(pt_hset);

            hash_set_insert(pt_hsetex, "xcvbnm");
            hash_set_insert(pt_hsetex, "<><><><><><>");
            hash_set_insert(pt_hsetex, "cccc");
            hash_set_insert(pt_hsetex, "@@@@@@@@");
            hash_set_insert(pt_hsetex, "@@@@@@@@");
            hash_set_insert(pt_hsetex, "()()");
            hash_set_insert(pt_hsetex, "help");
            hash_set_insert(pt_hsetex, "me!!!!!!!!!!!!!!");
            hash_set_insert(pt_hsetex, "++++");
            hash_set_insert(pt_hsetex, "76894");
            hash_set_insert(pt_hsetex, "bfqweoihabgasodifjw");
            hash_set_insert(pt_hsetex, "aaaaaaaa");
            hash_set_insert(pt_hsetex, "{}{}{}{}{}{");
            hash_set_insert(pt_hsetex, "########");
            hash_set_insert(pt_hsetex, "%%%%%%%%%%%%%%");
            hash_set_insert(pt_hsetex, "$$$$$$$$$$$$$$");
            hash_set_insert(pt_hsetex, "!!!!!!!!!!");
            _print_hash_set_cstr(pt_hsetex);

            hash_set_insert_range(pt_hset, hash_set_begin(pt_hsetex),
                hash_set_begin(pt_hsetex));
            _print_hash_set_cstr(pt_hset);
            hash_set_insert_range(pt_hset, hash_set_begin(pt_hsetex),
                iterator_advance(hash_set_begin(pt_hsetex), 3));
            _print_hash_set_cstr(pt_hset);
            hash_set_insert_range(pt_hset, iterator_advance(hash_set_begin(pt_hsetex), 4),
                iterator_advance(hash_set_begin(pt_hsetex), 6));
            _print_hash_set_cstr(pt_hset);
            hash_set_insert_range(pt_hset, iterator_advance(hash_set_begin(pt_hsetex), 7),
                hash_set_end(pt_hsetex));
            _print_hash_set_cstr(pt_hset);
            hash_set_insert_range(pt_hset, hash_set_end(pt_hsetex), hash_set_end(pt_hsetex));
            _print_hash_set_cstr(pt_hset);
            hash_set_clear(pt_hset);
            hash_set_insert_range(pt_hset, hash_set_begin(pt_hsetex), hash_set_end(pt_hsetex));
            _print_hash_set_cstr(pt_hset);

            hash_set_destroy(pt_hset);
            hash_set_destroy(pt_hsetex);
        }
        /*hash_set_erase             */
        {
            hash_set_t* pt_hset = create_hash_set(char*);
            if(pt_hset == NULL)
            {
                return;
            }
            hash_set_init_ex(pt_hset, 100, _hash_set_cstr_hash, NULL);
            hash_set_erase(pt_hset, "76894");
            _print_hash_set_cstr(pt_hset);

            hash_set_insert(pt_hset, "xcvbnm");
            hash_set_insert(pt_hset, "<><><><><><>");
            hash_set_insert(pt_hset, "cccc");
            hash_set_insert(pt_hset, "@@@@@@@@");
            hash_set_insert(pt_hset, "@@@@@@@@");
            hash_set_insert(pt_hset, "()()");
            hash_set_insert(pt_hset, "help");
            hash_set_insert(pt_hset, "me!!!!!!!!!!!!!!");
            hash_set_insert(pt_hset, "++++");
            hash_set_insert(pt_hset, "76894");
            hash_set_insert(pt_hset, "bfqweoihabgasodifjw");
            hash_set_insert(pt_hset, "aaaaaaaa");
            hash_set_insert(pt_hset, "{}{}{}{}{}{");
            hash_set_insert(pt_hset, "########");
            hash_set_insert(pt_hset, "%%%%%%%%%%%%%%");
            hash_set_insert(pt_hset, "$$$$$$$$$$$$$$");
            hash_set_insert(pt_hset, "!!!!!!!!!!");
            _print_hash_set_cstr(pt_hset);

            hash_set_erase(pt_hset, "mnopq");
            _print_hash_set_cstr(pt_hset);
            hash_set_erase(pt_hset, "76894");
            _print_hash_set_cstr(pt_hset);

            hash_set_destroy(pt_hset);
        }
        /*hash_set_erase_pos         */
        {
            hash_set_t* pt_hset = create_hash_set(char*);
            if(pt_hset == NULL)
            {
                return;
            }
            hash_set_init_ex(pt_hset, 100, _hash_set_cstr_hash, NULL);
            hash_set_insert(pt_hset, "xcvbnm");
            hash_set_insert(pt_hset, "<><><><><><>");
            hash_set_insert(pt_hset, "cccc");
            hash_set_insert(pt_hset, "@@@@@@@@");
            hash_set_insert(pt_hset, "@@@@@@@@");
            hash_set_insert(pt_hset, "()()");
            hash_set_insert(pt_hset, "help");
            hash_set_insert(pt_hset, "me!!!!!!!!!!!!!!");
            hash_set_insert(pt_hset, "++++");
            hash_set_insert(pt_hset, "76894");
            hash_set_insert(pt_hset, "bfqweoihabgasodifjw");
            hash_set_insert(pt_hset, "aaaaaaaa");
            hash_set_insert(pt_hset, "{}{}{}{}{}{");
            hash_set_insert(pt_hset, "########");
            hash_set_insert(pt_hset, "%%%%%%%%%%%%%%");
            hash_set_insert(pt_hset, "$$$$$$$$$$$$$$");
            hash_set_insert(pt_hset, "!!!!!!!!!!");
            _print_hash_set_cstr(pt_hset);

            hash_set_erase_pos(pt_hset, hash_set_begin(pt_hset));
            _print_hash_set_cstr(pt_hset);
            hash_set_erase_pos(pt_hset, iterator_advance(hash_set_begin(pt_hset), 5));
            _print_hash_set_cstr(pt_hset);
            while(!hash_set_empty(pt_hset))
            {
                hash_set_erase_pos(pt_hset, hash_set_begin(pt_hset));
            }
            _print_hash_set_cstr(pt_hset);

            hash_set_destroy(pt_hset);
        }
        /*hash_set_erase_range       */
        {
            hash_set_t* pt_hset = create_hash_set(char*);
            if(pt_hset == NULL)
            {
                return;
            }
            hash_set_init_ex(pt_hset, 100, _hash_set_cstr_hash, NULL);
            hash_set_erase_range(pt_hset, hash_set_begin(pt_hset), hash_set_end(pt_hset));
            _print_hash_set_cstr(pt_hset);
            hash_set_insert(pt_hset, "xcvbnm");
            hash_set_insert(pt_hset, "<><><><><><>");
            hash_set_insert(pt_hset, "cccc");
            hash_set_insert(pt_hset, "@@@@@@@@");
            hash_set_insert(pt_hset, "@@@@@@@@");
            hash_set_insert(pt_hset, "()()");
            hash_set_insert(pt_hset, "help");
            hash_set_insert(pt_hset, "me!!!!!!!!!!!!!!");
            hash_set_insert(pt_hset, "++++");
            hash_set_insert(pt_hset, "76894");
            hash_set_insert(pt_hset, "bfqweoihabgasodifjw");
            hash_set_insert(pt_hset, "aaaaaaaa");
            hash_set_insert(pt_hset, "{}{}{}{}{}{");
            hash_set_insert(pt_hset, "########");
            hash_set_insert(pt_hset, "%%%%%%%%%%%%%%");
            hash_set_insert(pt_hset, "$$$$$$$$$$$$$$");
            hash_set_insert(pt_hset, "!!!!!!!!!!");
            _print_hash_set_cstr(pt_hset);

            hash_set_erase_range(pt_hset, hash_set_begin(pt_hset), hash_set_begin(pt_hset));
            _print_hash_set_cstr(pt_hset);
            hash_set_erase_range(pt_hset, hash_set_begin(pt_hset),
                iterator_advance(hash_set_begin(pt_hset), 3));
            _print_hash_set_cstr(pt_hset);
            hash_set_erase_range(pt_hset, iterator_next(hash_set_begin(pt_hset)),
                iterator_advance(hash_set_begin(pt_hset), 3));
            _print_hash_set_cstr(pt_hset);
            hash_set_erase_range(pt_hset, iterator_advance(hash_set_begin(pt_hset), 4),
                hash_set_end(pt_hset));
            _print_hash_set_cstr(pt_hset);
            hash_set_erase_range(pt_hset, hash_set_end(pt_hset), hash_set_end(pt_hset));
            _print_hash_set_cstr(pt_hset);
            hash_set_erase_range(pt_hset, hash_set_begin(pt_hset), hash_set_end(pt_hset));
            _print_hash_set_cstr(pt_hset);

            hash_set_destroy(pt_hset);
        }
        /*hash_set_clear             */
        {
            hash_set_t* pt_hset = create_hash_set(char*);
            if(pt_hset == NULL)
            {
                return;
            }
            hash_set_init_ex(pt_hset, 100, _hash_set_cstr_hash, NULL);
            hash_set_clear(pt_hset);
            _print_hash_set_cstr(pt_hset);
            hash_set_insert(pt_hset, "xcvbnm");
            hash_set_insert(pt_hset, "<><><><><><>");
            hash_set_insert(pt_hset, "cccc");
            hash_set_insert(pt_hset, "@@@@@@@@");
            hash_set_insert(pt_hset, "@@@@@@@@");
            hash_set_insert(pt_hset, "()()");
            hash_set_insert(pt_hset, "help");
            hash_set_insert(pt_hset, "me!!!!!!!!!!!!!!");
            hash_set_insert(pt_hset, "++++");
            hash_set_insert(pt_hset, "76894");
            hash_set_insert(pt_hset, "bfqweoihabgasodifjw");
            hash_set_insert(pt_hset, "aaaaaaaa");
            hash_set_insert(pt_hset, "{}{}{}{}{}{");
            hash_set_insert(pt_hset, "########");
            hash_set_insert(pt_hset, "%%%%%%%%%%%%%%");
            hash_set_insert(pt_hset, "$$$$$$$$$$$$$$");
            hash_set_insert(pt_hset, "!!!!!!!!!!");
            _print_hash_set_cstr(pt_hset);
            hash_set_clear(pt_hset);
            _print_hash_set_cstr(pt_hset);

            hash_set_destroy(pt_hset);
        }
    }
}

void test_hash_multiset(void)
{
    /* c built-in type */
    {
        /*create_hash_multiset            */
        /*hash_multiset_init              */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(int);
            if(pt_hmset == NULL)
            {
                return;
            }
            hash_multiset_init(pt_hmset);
            _print_hash_multiset_c(pt_hmset, "%d, ", int);
            hash_multiset_insert(pt_hmset, 48);
            hash_multiset_insert(pt_hmset, 1234);
            hash_multiset_insert(pt_hmset, 483945);
            hash_multiset_insert(pt_hmset, -74);
            hash_multiset_insert(pt_hmset, 45);
            _print_hash_multiset_c(pt_hmset, "%d, ", int);
            _debug_hash_multiset_c(pt_hmset, "%d", int);
            hash_multiset_destroy(pt_hmset);
        }
        /*hash_multiset_init_ex           */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(int);
            if(pt_hmset == NULL)
            {
                return;
            }
            hash_multiset_init_ex(pt_hmset, 100, _hash_set_int_hash, fun_great_int);
            _print_hash_multiset_c(pt_hmset, "%d, ", int);
            hash_multiset_insert(pt_hmset, 48);
            hash_multiset_insert(pt_hmset, 1234);
            hash_multiset_insert(pt_hmset, 483945);
            hash_multiset_insert(pt_hmset, -74);
            hash_multiset_insert(pt_hmset, -74);
            hash_multiset_insert(pt_hmset, 45);
            hash_multiset_insert(pt_hmset, 48);
            _print_hash_multiset_c(pt_hmset, "%d, ", int);
            _debug_hash_multiset_c(pt_hmset, "%d", int);
            hash_multiset_destroy(pt_hmset);
        }
        /*hash_multiset_init_copy         */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(double);
            hash_multiset_t* pt_hmsetex = create_hash_multiset(double);
            if(pt_hmset == NULL || pt_hmsetex == NULL)
            {
                return;
            }
            hash_multiset_init_ex(pt_hmsetex, 80, NULL, NULL);
            hash_multiset_insert(pt_hmsetex, 45.90);
            hash_multiset_insert(pt_hmsetex, 2.08);
            hash_multiset_insert(pt_hmsetex, -22.34);
            hash_multiset_insert(pt_hmsetex, 2.08);
            hash_multiset_insert(pt_hmsetex, 12.099);
            hash_multiset_init_copy(pt_hmset, pt_hmsetex);
            _print_hash_multiset_c(pt_hmsetex, "%lf, ", double);
            _print_hash_multiset_c(pt_hmset, "%lf, ", double);
            hash_multiset_destroy(pt_hmset);
            hash_multiset_destroy(pt_hmsetex);
        }
        /*hash_multiset_init_copy_range   */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(int);
            hash_multiset_t* pt_hmsetex = create_hash_multiset(signed int);
            if(pt_hmset == NULL || pt_hmsetex == NULL)
            {
                return;
            }
            hash_multiset_init_ex(pt_hmsetex, 110, _hash_set_int_hash, NULL);
            hash_multiset_insert(pt_hmsetex, 290);
            hash_multiset_insert(pt_hmsetex, -82784);
            hash_multiset_insert(pt_hmsetex, 2220);
            hash_multiset_insert(pt_hmsetex, 45);
            hash_multiset_insert(pt_hmsetex, 100);
            hash_multiset_insert(pt_hmsetex, 29000);
            hash_multiset_insert(pt_hmsetex, 23);
            hash_multiset_init_copy_range(pt_hmset, hash_multiset_begin(pt_hmsetex),
                hash_multiset_end(pt_hmsetex));
            /*_debug_hash_multiset_c(pt_hmsetex, "%d", int);*/
            /*_debug_hash_multiset_c(pt_hmset, "%d", int);*/
            _print_hash_multiset_c(pt_hmsetex, "%d, ", int);
            _print_hash_multiset_c(pt_hmset, "%d, ", int);
            hash_multiset_destroy(pt_hmset);
            hash_multiset_destroy(pt_hmsetex);
        }
        /*hash_multiset_init_copy_range_ex*/
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(int);
            hash_multiset_t* pt_hmsetex = create_hash_multiset(signed int);
            if(pt_hmset == NULL || pt_hmsetex == NULL)
            {
                return;
            }
            hash_multiset_init_ex(pt_hmsetex, 110, _hash_set_int_hash, NULL);
            hash_multiset_insert(pt_hmsetex, 290);
            hash_multiset_insert(pt_hmsetex, -82784);
            hash_multiset_insert(pt_hmsetex, 2220);
            hash_multiset_insert(pt_hmsetex, 45);
            hash_multiset_insert(pt_hmsetex, 100);
            hash_multiset_insert(pt_hmsetex, 29000);
            hash_multiset_insert(pt_hmsetex, 23);
            hash_multiset_insert(pt_hmsetex, 23);
            hash_multiset_insert(pt_hmsetex, 92);
            hash_multiset_insert(pt_hmsetex, 94);
            hash_multiset_insert(pt_hmsetex, 95);
            hash_multiset_insert(pt_hmsetex, 96);
            hash_multiset_insert(pt_hmsetex, 97);
            hash_multiset_insert(pt_hmsetex, 98);
            hash_multiset_insert(pt_hmsetex, 99);
            hash_multiset_insert(pt_hmsetex, 101);
            hash_multiset_init_copy_range_ex(pt_hmset, hash_multiset_begin(pt_hmsetex),
                hash_multiset_end(pt_hmsetex), 90, NULL, fun_great_int);
            _debug_hash_multiset_c(pt_hmsetex, "%d", int);
            _debug_hash_multiset_c(pt_hmset, "%d", int);
            _print_hash_multiset_c(pt_hmsetex, "%d, ", int);
            _print_hash_multiset_c(pt_hmset, "%d, ", int);
            hash_multiset_destroy(pt_hmset);
            hash_multiset_destroy(pt_hmsetex);
        }
        /*hash_multiset_destroy           */
        /*hash_multiset_assign            */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(int);
            hash_multiset_t* pt_hmsetex = create_hash_multiset(int);
            size_t t_index = 0;
            if(pt_hmset == NULL || pt_hmsetex == NULL)
            {
                return;
            }
            hash_multiset_init(pt_hmset);
            hash_multiset_init(pt_hmsetex);
            hash_multiset_assign(pt_hmset, pt_hmsetex);
            _print_hash_multiset_c(pt_hmsetex, "%d, ", int);
            _print_hash_multiset_c(pt_hmset, "%d, ", int);

            hash_multiset_insert(pt_hmsetex, 340);
            hash_multiset_insert(pt_hmsetex, 1009);
            hash_multiset_insert(pt_hmsetex, -76);
            hash_multiset_insert(pt_hmsetex, 50);
            hash_multiset_insert(pt_hmsetex, 21);
            hash_multiset_insert(pt_hmsetex, -785);
            hash_multiset_assign(pt_hmset, pt_hmsetex);
            _print_hash_multiset_c(pt_hmsetex, "%d, ", int);
            _print_hash_multiset_c(pt_hmset, "%d, ", int);

            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 88);
            hash_multiset_insert(pt_hmsetex, 245);
            hash_multiset_insert(pt_hmsetex, 120);
            hash_multiset_assign(pt_hmset, pt_hmsetex);
            _print_hash_multiset_c(pt_hmsetex, "%d, ", int);
            _print_hash_multiset_c(pt_hmset, "%d, ", int);

            hash_multiset_clear(pt_hmsetex);
            for(t_index = 0; t_index < 100; ++t_index)
            {
                hash_multiset_insert(pt_hmsetex, t_index);
            }
            hash_multiset_assign(pt_hmset, pt_hmsetex);
            _print_hash_multiset_c(pt_hmsetex, "%d, ", int);
            _print_hash_multiset_c(pt_hmset, "%d, ", int);

            hash_multiset_clear(pt_hmsetex);
            hash_multiset_assign(pt_hmset, pt_hmsetex);
            _print_hash_multiset_c(pt_hmsetex, "%d, ", int);
            _print_hash_multiset_c(pt_hmset, "%d, ", int);

            hash_multiset_destroy(pt_hmset);
            hash_multiset_destroy(pt_hmsetex);
        }
        /*hash_multiset_swap              */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(int);
            hash_multiset_t* pt_hmsetex = create_hash_multiset(int);
            if(pt_hmset == NULL || pt_hmsetex == NULL)
            {
                return;
            }
            hash_multiset_init(pt_hmset);
            hash_multiset_init_ex(pt_hmsetex, 90, NULL, NULL);
            hash_multiset_swap(pt_hmset, pt_hmsetex);
            _print_hash_multiset_c(pt_hmset, "%d, ", int);
            _print_hash_multiset_c(pt_hmsetex, "%d, ", int);

            hash_multiset_insert(pt_hmsetex, 450);
            hash_multiset_insert(pt_hmsetex, -45);
            hash_multiset_insert(pt_hmsetex, 90);
            hash_multiset_insert(pt_hmsetex, 233);
            hash_multiset_insert(pt_hmsetex, 109);
            hash_multiset_insert(pt_hmsetex, 2);
            hash_multiset_swap(pt_hmset, pt_hmsetex);
            _print_hash_multiset_c(pt_hmset, "%d, ", int);
            _print_hash_multiset_c(pt_hmsetex, "%d, ", int);

            hash_multiset_insert(pt_hmsetex, 4);
            hash_multiset_insert(pt_hmsetex, -334);
            hash_multiset_insert(pt_hmsetex, 1212);
            hash_multiset_insert(pt_hmsetex, 1);
            hash_multiset_insert(pt_hmsetex, 444);
            hash_multiset_insert(pt_hmsetex, 12);
            hash_multiset_insert(pt_hmsetex, 45);
            hash_multiset_insert(pt_hmsetex, 999);
            hash_multiset_insert(pt_hmsetex, 999);
            hash_multiset_insert(pt_hmsetex, 999);
            hash_multiset_insert(pt_hmsetex, 999);
            hash_multiset_insert(pt_hmsetex, 9);
            hash_multiset_insert(pt_hmsetex, -56);
            hash_multiset_insert(pt_hmsetex, 4);
            hash_multiset_insert(pt_hmsetex, 4);
            hash_multiset_insert(pt_hmsetex, 34);
            hash_multiset_swap(pt_hmset, pt_hmsetex);
            _print_hash_multiset_c(pt_hmset, "%d, ", int);
            _print_hash_multiset_c(pt_hmsetex, "%d, ", int);

            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 45);
            hash_multiset_insert(pt_hmsetex, 909);
            hash_multiset_insert(pt_hmsetex, 5);
            hash_multiset_swap(pt_hmset, pt_hmsetex);
            _print_hash_multiset_c(pt_hmset, "%d, ", int);
            _print_hash_multiset_c(pt_hmsetex, "%d, ", int);

            hash_multiset_clear(pt_hmsetex);
            hash_multiset_swap(pt_hmset, pt_hmsetex);
            _print_hash_multiset_c(pt_hmset, "%d, ", int);
            _print_hash_multiset_c(pt_hmsetex, "%d, ", int);

            hash_multiset_destroy(pt_hmset);
            hash_multiset_destroy(pt_hmsetex);
        }
        /*hash_multiset_size              */
        /*hash_multiset_empty             */
        /*hash_multiset_max_size          */
        /*hash_multiset_bucket_count      */
        /*hash_multiset_hash              */
        /*hash_multiset_key_less          */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(int);
            if(pt_hmset == NULL)
            {
                return;
            }
            hash_multiset_init_ex(pt_hmset, 100, _hash_set_int_hash, fun_great_int);
            assert(hash_multiset_hash(pt_hmset) == _hash_set_int_hash &&
                hash_multiset_key_less(pt_hmset) == fun_great_int);
            hash_multiset_destroy(pt_hmset);
        }
        /*hash_multiset_resize            */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(int);
            if(pt_hmset == NULL)
            {
                return;
            }
            hash_multiset_init(pt_hmset);
            _print_hash_multiset_c(pt_hmset, "%d, ", int);

            hash_multiset_insert(pt_hmset, 56);
            hash_multiset_insert(pt_hmset, -5);
            hash_multiset_insert(pt_hmset, 677);
            hash_multiset_insert(pt_hmset, 90);
            hash_multiset_insert(pt_hmset, 23);
            _print_hash_multiset_c(pt_hmset, "%d, ", int);

            hash_multiset_resize(pt_hmset, 30);
            _print_hash_multiset_c(pt_hmset, "%d, ", int);

            hash_multiset_resize(pt_hmset, 100);
            _print_hash_multiset_c(pt_hmset, "%d, ", int);

            hash_multiset_resize(pt_hmset, 90);
            _print_hash_multiset_c(pt_hmset, "%d, ", int);

            hash_multiset_destroy(pt_hmset);
        }
        /*hash_multiset_equal             */
        /*hash_multiset_not_equal         */
        /*hash_multiset_less              */
        /*hash_multiset_less_equal        */
        /*hash_multiset_great             */
        /*hash_multiset_great_equal       */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(int);
            hash_multiset_t* pt_hmsetex = create_hash_multiset(int);
            if(pt_hmset == NULL || pt_hmsetex == NULL)
            {
                return;
            }
            hash_multiset_init(pt_hmset);
            hash_multiset_init(pt_hmsetex);
            _print_hash_multiset_c(pt_hmset, "%d, ", int);
            _print_hash_multiset_c(pt_hmsetex, "%d, ", int);
            printf("equal: %d, not equal: %d, ",
                hash_multiset_equal(pt_hmset, pt_hmsetex), hash_multiset_not_equal(pt_hmset, pt_hmsetex));
            printf("less: %d, less equal: %d, ",
                hash_multiset_less(pt_hmset, pt_hmsetex), hash_multiset_less_equal(pt_hmset, pt_hmsetex));
            printf("great: %d, great equal: %d\n",
                hash_multiset_great(pt_hmset, pt_hmsetex), hash_multiset_great_equal(pt_hmset, pt_hmsetex));

            hash_multiset_insert(pt_hmset, 23);
            hash_multiset_insert(pt_hmset, 40);
            _print_hash_multiset_c(pt_hmset, "%d, ", int);
            _print_hash_multiset_c(pt_hmsetex, "%d, ", int);
            printf("equal: %d, not equal: %d, ",
                hash_multiset_equal(pt_hmset, pt_hmsetex), hash_multiset_not_equal(pt_hmset, pt_hmsetex));
            printf("less: %d, less equal: %d, ",
                hash_multiset_less(pt_hmset, pt_hmsetex), hash_multiset_less_equal(pt_hmset, pt_hmsetex));
            printf("great: %d, great equal: %d\n",
                hash_multiset_great(pt_hmset, pt_hmsetex), hash_multiset_great_equal(pt_hmset, pt_hmsetex));

            hash_multiset_insert(pt_hmsetex, 23);
            hash_multiset_insert(pt_hmsetex, 40);
            _print_hash_multiset_c(pt_hmset, "%d, ", int);
            _print_hash_multiset_c(pt_hmsetex, "%d, ", int);
            printf("equal: %d, not equal: %d, ",
                hash_multiset_equal(pt_hmset, pt_hmsetex), hash_multiset_not_equal(pt_hmset, pt_hmsetex));
            printf("less: %d, less equal: %d, ",
                hash_multiset_less(pt_hmset, pt_hmsetex), hash_multiset_less_equal(pt_hmset, pt_hmsetex));
            printf("great: %d, great equal: %d\n",
                hash_multiset_great(pt_hmset, pt_hmsetex), hash_multiset_great_equal(pt_hmset, pt_hmsetex));

            hash_multiset_insert(pt_hmset, 61);
            hash_multiset_insert(pt_hmset, 60);
            hash_multiset_insert(pt_hmsetex, 64);
            _print_hash_multiset_c(pt_hmset, "%d, ", int);
            _print_hash_multiset_c(pt_hmsetex, "%d, ", int);
            printf("equal: %d, not equal: %d, ",
                hash_multiset_equal(pt_hmset, pt_hmsetex), hash_multiset_not_equal(pt_hmset, pt_hmsetex));
            printf("less: %d, less equal: %d, ",
                hash_multiset_less(pt_hmset, pt_hmsetex), hash_multiset_less_equal(pt_hmset, pt_hmsetex));
            printf("great: %d, great equal: %d\n",
                hash_multiset_great(pt_hmset, pt_hmsetex), hash_multiset_great_equal(pt_hmset, pt_hmsetex));

            hash_multiset_resize(pt_hmsetex, 80);
            _print_hash_multiset_c(pt_hmset, "%d, ", int);
            _print_hash_multiset_c(pt_hmsetex, "%d, ", int);
            printf("equal: %d, not equal: %d, ",
                hash_multiset_equal(pt_hmset, pt_hmsetex), hash_multiset_not_equal(pt_hmset, pt_hmsetex));
            printf("less: %d, less equal: %d, ",
                hash_multiset_less(pt_hmset, pt_hmsetex), hash_multiset_less_equal(pt_hmset, pt_hmsetex));
            printf("great: %d, great equal: %d\n",
                hash_multiset_great(pt_hmset, pt_hmsetex), hash_multiset_great_equal(pt_hmset, pt_hmsetex));

            hash_multiset_destroy(pt_hmset);
            hash_multiset_destroy(pt_hmsetex);
        }
        /*hash_multiset_begin             */
        /*hash_multiset_end               */
        /*hash_multiset_find              */
        /*hash_multiset_count             */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(int);
            iterator_t t_iter;
            if(pt_hmset == NULL)
            {
                return;
            }
            hash_multiset_init(pt_hmset);
            t_iter = hash_multiset_find(pt_hmset, 34);
            if(iterator_equal(t_iter, hash_multiset_end(pt_hmset)))
            {
                printf("not found!, count : %u\n", hash_multiset_count(pt_hmset, 34));
            }
            else
            {
                printf("found!, count : %u\n", hash_multiset_count(pt_hmset, 34));
            }
            hash_multiset_insert(pt_hmset, 56);
            hash_multiset_insert(pt_hmset, 45);
            hash_multiset_insert(pt_hmset, 88);
            hash_multiset_insert(pt_hmset, 900);

            t_iter = hash_multiset_find(pt_hmset, 34);
            if(iterator_equal(t_iter, hash_multiset_end(pt_hmset)))
            {
                printf("not found!, count : %u\n", hash_multiset_count(pt_hmset, 34));
            }
            else
            {
                printf("found!, count : %u\n", hash_multiset_count(pt_hmset, 34));
            }
            t_iter = hash_multiset_find(pt_hmset, 88);
            if(iterator_equal(t_iter, hash_multiset_end(pt_hmset)))
            {
                printf("not found!, count : %u\n", hash_multiset_count(pt_hmset, 88));
            }
            else
            {
                printf("found!, count : %u\n", hash_multiset_count(pt_hmset, 88));
            }
            hash_multiset_destroy(pt_hmset);
        }
        /*hash_multiset_equal_range       */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(int);
            range_t t_range;
            if(pt_hmset == NULL)
            {
                return;
            }
            hash_multiset_init(pt_hmset);
            t_range = hash_multiset_equal_range(pt_hmset, 45);
            assert(iterator_equal(t_range.t_begin, hash_multiset_end(pt_hmset)) &&
                iterator_equal(t_range.t_begin, t_range.t_end));
            hash_multiset_insert(pt_hmset, 344);
            hash_multiset_insert(pt_hmset, 90);
            hash_multiset_insert(pt_hmset, 456);
            hash_multiset_insert(pt_hmset, 30);
            hash_multiset_insert(pt_hmset, 4567);
            hash_multiset_insert(pt_hmset, 2);
            t_range = hash_multiset_equal_range(pt_hmset, 45);
            assert(iterator_equal(t_range.t_begin, t_range.t_end));
            t_range = hash_multiset_equal_range(pt_hmset, 90);
            assert(iterator_equal(iterator_next(t_range.t_begin), t_range.t_end));
            hash_multiset_destroy(pt_hmset);
        }
        /*hash_multiset_insert            */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(double);
            if(pt_hmset == NULL)
            {
                return;
            }
            hash_multiset_init(pt_hmset);
            _print_hash_multiset_c(pt_hmset, "%lf, ", double);
            hash_multiset_insert(pt_hmset, 0.000000001);
            hash_multiset_insert(pt_hmset, 0.0000000001);
            hash_multiset_insert(pt_hmset, -22.445);
            hash_multiset_insert(pt_hmset, -0.999);
            hash_multiset_insert(pt_hmset, -0.999);
            hash_multiset_insert(pt_hmset, -273984.0);
            hash_multiset_insert(pt_hmset, 12.012783);
            _debug_hash_multiset_c(pt_hmset, "%g", double);
            _print_hash_multiset_c(pt_hmset, "%g, ", double);
            hash_multiset_destroy(pt_hmset);
        }
        /*hash_multiset_insert_range      */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(long);
            hash_multiset_t* pt_hmsetex = create_hash_multiset(long);
            if(pt_hmset == NULL || pt_hmsetex == NULL)
            {
                return;
            }
            hash_multiset_init(pt_hmset);
            hash_multiset_init(pt_hmsetex);
            hash_multiset_insert_range(pt_hmset, hash_multiset_begin(pt_hmsetex), hash_multiset_end(pt_hmsetex));
            _print_hash_multiset_c(pt_hmset, "%ld, ", long);
            hash_multiset_insert(pt_hmsetex, 34232344);
            hash_multiset_insert(pt_hmsetex, 90090);
            hash_multiset_insert(pt_hmsetex, 123445);
            hash_multiset_insert(pt_hmsetex, -4345);
            hash_multiset_insert(pt_hmsetex, 2300020);
            hash_multiset_insert(pt_hmsetex, 50);
            hash_multiset_insert(pt_hmsetex, 4550);
            hash_multiset_insert(pt_hmsetex, 4);
            hash_multiset_insert(pt_hmsetex, 8888);
            hash_multiset_insert(pt_hmsetex, 444444);
            hash_multiset_insert(pt_hmsetex, 890093);
            _print_hash_multiset_c(pt_hmsetex, "%ld, ", long);
            hash_multiset_insert_range(pt_hmset, hash_multiset_begin(pt_hmsetex),
                hash_multiset_begin(pt_hmsetex));
            _print_hash_multiset_c(pt_hmset, "%ld, ", long);
            hash_multiset_insert_range(pt_hmset, hash_multiset_begin(pt_hmsetex),
                iterator_advance(hash_multiset_begin(pt_hmsetex), 3));
            _print_hash_multiset_c(pt_hmset, "%ld, ", long);
            hash_multiset_insert_range(pt_hmset, iterator_advance(hash_multiset_begin(pt_hmsetex), 5),
                iterator_advance(hash_multiset_begin(pt_hmsetex), 7));
            _print_hash_multiset_c(pt_hmset, "%ld, ", long);
            hash_multiset_insert_range(pt_hmset, iterator_advance(hash_multiset_begin(pt_hmsetex), 8),
                hash_multiset_end(pt_hmsetex));
            _print_hash_multiset_c(pt_hmset, "%ld, ", long);
            hash_multiset_insert_range(pt_hmset, hash_multiset_end(pt_hmsetex), hash_multiset_end(pt_hmsetex));
            _print_hash_multiset_c(pt_hmset, "%ld, ", long);
            hash_multiset_clear(pt_hmset);
            hash_multiset_insert_range(pt_hmset, hash_multiset_begin(pt_hmsetex), hash_multiset_end(pt_hmsetex));
            _print_hash_multiset_c(pt_hmset, "%ld, ", long);
            hash_multiset_destroy(pt_hmset);
            hash_multiset_destroy(pt_hmsetex);
        }
        /*hash_multiset_erase             */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(long);
            if(pt_hmset == NULL)
            {
                return;
            }
            hash_multiset_init(pt_hmset);
            hash_multiset_erase(pt_hmset, 345);
            _print_hash_multiset_c(pt_hmset, "%ld, ", long);
            hash_multiset_insert(pt_hmset, 34232344);
            hash_multiset_insert(pt_hmset, 90090);
            hash_multiset_insert(pt_hmset, 123445);
            hash_multiset_insert(pt_hmset, -4345);
            hash_multiset_insert(pt_hmset, 2300020);
            hash_multiset_insert(pt_hmset, 50);
            hash_multiset_insert(pt_hmset, 4550);
            hash_multiset_insert(pt_hmset, 4);
            hash_multiset_insert(pt_hmset, 8888);
            hash_multiset_insert(pt_hmset, 444444);
            hash_multiset_insert(pt_hmset, 890093);
            _print_hash_multiset_c(pt_hmset, "%ld, ", long);
            hash_multiset_erase(pt_hmset, 345);
            _print_hash_multiset_c(pt_hmset, "%ld, ", long);
            hash_multiset_erase(pt_hmset, 4550);
            _print_hash_multiset_c(pt_hmset, "%ld, ", long);
            hash_multiset_destroy(pt_hmset);
        }
        /*hash_multiset_erase_pos         */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(long);
            if(pt_hmset == NULL)
            {
                return;
            }
            hash_multiset_init(pt_hmset);
            hash_multiset_insert(pt_hmset, 34232344);
            hash_multiset_insert(pt_hmset, 90090);
            hash_multiset_insert(pt_hmset, 123445);
            hash_multiset_insert(pt_hmset, -4345);
            hash_multiset_insert(pt_hmset, 2300020);
            hash_multiset_insert(pt_hmset, 50);
            hash_multiset_insert(pt_hmset, 4550);
            hash_multiset_insert(pt_hmset, 4);
            hash_multiset_insert(pt_hmset, 8888);
            hash_multiset_insert(pt_hmset, 444444);
            hash_multiset_insert(pt_hmset, 890093);
            _print_hash_multiset_c(pt_hmset, "%ld, ", long);
            hash_multiset_erase_pos(pt_hmset, hash_multiset_begin(pt_hmset));
            _print_hash_multiset_c(pt_hmset, "%ld, ", long);
            hash_multiset_erase_pos(pt_hmset, iterator_advance(hash_multiset_begin(pt_hmset), 3));
            _print_hash_multiset_c(pt_hmset, "%ld, ", long);
            while(!hash_multiset_empty(pt_hmset))
            {
                hash_multiset_erase_pos(pt_hmset, hash_multiset_begin(pt_hmset));
            }
            _print_hash_multiset_c(pt_hmset, "%ld, ", long);
            hash_multiset_destroy(pt_hmset);
        }
        /*hash_multiset_erase_range       */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(long);
            if(pt_hmset == NULL)
            {
                return;
            }
            hash_multiset_init(pt_hmset);
            hash_multiset_erase_range(pt_hmset, hash_multiset_begin(pt_hmset), hash_multiset_end(pt_hmset));
            _print_hash_multiset_c(pt_hmset, "%ld, ", long);
            hash_multiset_insert(pt_hmset, 34232344);
            hash_multiset_insert(pt_hmset, 90090);
            hash_multiset_insert(pt_hmset, 123445);
            hash_multiset_insert(pt_hmset, -4345);
            hash_multiset_insert(pt_hmset, 2300020);
            hash_multiset_insert(pt_hmset, 50);
            hash_multiset_insert(pt_hmset, 4550);
            hash_multiset_insert(pt_hmset, 4);
            hash_multiset_insert(pt_hmset, 8888);
            hash_multiset_insert(pt_hmset, 444444);
            hash_multiset_insert(pt_hmset, 890093);
            _print_hash_multiset_c(pt_hmset, "%ld, ", long);
            hash_multiset_erase_range(pt_hmset, hash_multiset_begin(pt_hmset), hash_multiset_begin(pt_hmset));
            _print_hash_multiset_c(pt_hmset, "%ld, ", long);
            hash_multiset_erase_range(pt_hmset, hash_multiset_begin(pt_hmset),
                iterator_advance(hash_multiset_begin(pt_hmset), 3));
            _print_hash_multiset_c(pt_hmset, "%ld, ", long);
            hash_multiset_erase_range(pt_hmset, iterator_advance(hash_multiset_begin(pt_hmset), 2),
                iterator_advance(hash_multiset_begin(pt_hmset), 5));
            _print_hash_multiset_c(pt_hmset, "%ld, ", long);
            hash_multiset_erase_range(pt_hmset, iterator_advance(hash_multiset_begin(pt_hmset), 3),
                hash_multiset_end(pt_hmset));
            _print_hash_multiset_c(pt_hmset, "%ld, ", long);
            hash_multiset_erase_range(pt_hmset, hash_multiset_end(pt_hmset), hash_multiset_end(pt_hmset));
            _print_hash_multiset_c(pt_hmset, "%ld, ", long);
            hash_multiset_erase_range(pt_hmset, hash_multiset_begin(pt_hmset), hash_multiset_end(pt_hmset));
            _print_hash_multiset_c(pt_hmset, "%ld, ", long);
            hash_multiset_destroy(pt_hmset);
        }
        /*hash_multiset_clear             */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(long);
            if(pt_hmset == NULL)
            {
                return;
            }
            hash_multiset_init(pt_hmset);
            hash_multiset_clear(pt_hmset);
            _print_hash_multiset_c(pt_hmset, "%ld, ", long);
            hash_multiset_insert(pt_hmset, 34232344);
            hash_multiset_insert(pt_hmset, 90090);
            hash_multiset_insert(pt_hmset, 123445);
            hash_multiset_insert(pt_hmset, -4345);
            hash_multiset_insert(pt_hmset, 2300020);
            hash_multiset_insert(pt_hmset, 50);
            hash_multiset_insert(pt_hmset, 4550);
            hash_multiset_insert(pt_hmset, 4);
            hash_multiset_insert(pt_hmset, 8888);
            hash_multiset_insert(pt_hmset, 444444);
            hash_multiset_insert(pt_hmset, 890093);
            _print_hash_multiset_c(pt_hmset, "%ld, ", long);
            hash_multiset_clear(pt_hmset);
            _print_hash_multiset_c(pt_hmset, "%ld, ", long);
            hash_multiset_destroy(pt_hmset);
        }
    }
    /* user defined type */
    {
        type_register(hash_sample_t, _hash_sample_init, _hash_sample_copy, _hash_sample_less,
            _hash_sample_destroy);
        type_duplicate(hash_sample_t, struct _taghashsample);
        _type_debug();
        /*create_hash_multiset            */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(hash_sample_t);
            hash_sample_t t_sample;
            if(pt_hmset == NULL)
            {
                return;
            }
            hash_multiset_init(pt_hmset);
            t_sample._d_first = 45.098;
            t_sample._l_second = 22390;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = -9834.223;
            t_sample._l_second = 409303;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = 2323.2323;
            t_sample._l_second = 4;
            hash_multiset_insert(pt_hmset, &t_sample);
            _debug_hash_multiset_user(pt_hmset);
            _print_hash_multiset_sample(pt_hmset);
            hash_multiset_destroy(pt_hmset);
        }
        /*hash_multiset_init              */
        /*hash_multiset_init_ex           */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(struct _taghashsample);
            hash_sample_t t_sample;
            if(pt_hmset == NULL)
            {
                return;
            }
            hash_multiset_init_ex(pt_hmset, 200, _hash_set_sample_hash, NULL);
            t_sample._d_first = 45.098;
            t_sample._l_second = 22390;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = -9834.223;
            t_sample._l_second = 409303;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = 2323.2323;
            t_sample._l_second = 4;
            hash_multiset_insert(pt_hmset, &t_sample);
            _debug_hash_multiset_user(pt_hmset);
            _print_hash_multiset_sample(pt_hmset);
            hash_multiset_destroy(pt_hmset);
        }
        /*hash_multiset_init_copy         */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(hash_sample_t);
            hash_multiset_t* pt_hmsetex = create_hash_multiset(hash_sample_t);
            hash_sample_t t_sample;
            if(pt_hmset == NULL || pt_hmsetex == NULL)
            {
                return;
            }
            hash_multiset_init(pt_hmsetex);
            t_sample._d_first = 45.098;
            t_sample._l_second = 22390;
            hash_multiset_insert(pt_hmsetex, &t_sample);
            t_sample._d_first = -9834.223;
            t_sample._l_second = 409303;
            hash_multiset_insert(pt_hmsetex, &t_sample);
            t_sample._d_first = 2323.2323;
            t_sample._l_second = 4;
            hash_multiset_insert(pt_hmsetex, &t_sample);
            _print_hash_multiset_sample(pt_hmsetex);
            hash_multiset_init_copy(pt_hmset, pt_hmsetex);
            _print_hash_multiset_sample(pt_hmset);
            hash_multiset_destroy(pt_hmset);
            hash_multiset_destroy(pt_hmsetex);
        }
        /*hash_multiset_init_copy_range   */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(hash_sample_t);
            hash_multiset_t* pt_hmsetex = create_hash_multiset(hash_sample_t);
            hash_sample_t t_sample;
            if(pt_hmset == NULL || pt_hmsetex == NULL)
            {
                return;
            }
            hash_multiset_init_ex(pt_hmsetex, 100, _hash_set_sample_hash, NULL);
            t_sample._d_first = 45.098;
            t_sample._l_second = 22390;
            hash_multiset_insert(pt_hmsetex, &t_sample);
            t_sample._d_first = -9834.223;
            t_sample._l_second = 409303;
            hash_multiset_insert(pt_hmsetex, &t_sample);
            t_sample._d_first = 2323.2323;
            t_sample._l_second = 4;
            hash_multiset_insert(pt_hmsetex, &t_sample);
            t_sample._d_first = 0.2323;
            t_sample._l_second = 66666;
            hash_multiset_insert(pt_hmsetex, &t_sample);
            t_sample._d_first = 2323.0;
            t_sample._l_second = -66666;
            hash_multiset_insert(pt_hmsetex, &t_sample);
            t_sample._d_first = 0.0;
            t_sample._l_second = 0;
            hash_multiset_insert(pt_hmsetex, &t_sample);
            t_sample._d_first = 1.1;
            t_sample._l_second = 1;
            hash_multiset_insert(pt_hmsetex, &t_sample);
            t_sample._d_first = 8.8;
            t_sample._l_second = 8;
            hash_multiset_insert(pt_hmsetex, &t_sample);
            t_sample._d_first = 44444.4;
            t_sample._l_second = -5666;
            hash_multiset_insert(pt_hmsetex, &t_sample);
            t_sample._d_first = 44.4;
            t_sample._l_second = -5666;
            hash_multiset_insert(pt_hmsetex, &t_sample);
            _print_hash_multiset_sample(pt_hmsetex);
            hash_multiset_init_copy_range(pt_hmset, hash_multiset_begin(pt_hmsetex), hash_multiset_end(pt_hmsetex));
            _print_hash_multiset_sample(pt_hmset);
            hash_multiset_destroy(pt_hmset);
            hash_multiset_destroy(pt_hmsetex);
        }
        /*hash_multiset_init_copy_range_ex*/
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(hash_sample_t);
            hash_multiset_t* pt_hmsetex = create_hash_multiset(hash_sample_t);
            hash_sample_t t_sample;
            if(pt_hmset == NULL || pt_hmsetex == NULL)
            {
                return;
            }
            hash_multiset_init_ex(pt_hmsetex, 100, _hash_set_sample_hash, NULL);
            t_sample._d_first = 45.098;
            t_sample._l_second = 22390;
            hash_multiset_insert(pt_hmsetex, &t_sample);
            t_sample._d_first = -9834.223;
            t_sample._l_second = 409303;
            hash_multiset_insert(pt_hmsetex, &t_sample);
            t_sample._d_first = 2323.2323;
            t_sample._l_second = 4;
            hash_multiset_insert(pt_hmsetex, &t_sample);
            t_sample._d_first = 0.2323;
            t_sample._l_second = 66666;
            hash_multiset_insert(pt_hmsetex, &t_sample);
            t_sample._d_first = 2323.0;
            t_sample._l_second = -66666;
            hash_multiset_insert(pt_hmsetex, &t_sample);
            t_sample._d_first = 0.0;
            t_sample._l_second = 0;
            hash_multiset_insert(pt_hmsetex, &t_sample);
            t_sample._d_first = 1.1;
            t_sample._l_second = 1;
            hash_multiset_insert(pt_hmsetex, &t_sample);
            t_sample._d_first = 8.8;
            t_sample._l_second = 8;
            hash_multiset_insert(pt_hmsetex, &t_sample);
            t_sample._d_first = 44444.4;
            t_sample._l_second = -5666;
            hash_multiset_insert(pt_hmsetex, &t_sample);
            t_sample._d_first = 44.4;
            t_sample._l_second = -5666;
            hash_multiset_insert(pt_hmsetex, &t_sample);
            _print_hash_multiset_sample(pt_hmsetex);
            hash_multiset_init_copy_range_ex(pt_hmset, hash_multiset_begin(pt_hmsetex),
                hash_multiset_end(pt_hmsetex), 80, NULL, _hash_sample_great);
            _print_hash_multiset_sample(pt_hmset);
            hash_multiset_destroy(pt_hmset);
            hash_multiset_destroy(pt_hmsetex);
        }
        /*hash_multiset_destroy           */
        /*hash_multiset_assign            */
        /*hash_multiset_swap              */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(hash_sample_t);
            hash_multiset_t* pt_hmsetex = create_hash_multiset(hash_sample_t);
            hash_sample_t t_sample;
            if(pt_hmset == NULL || pt_hmsetex == NULL)
            {
                return;
            }
            hash_multiset_init(pt_hmset);
            hash_multiset_init(pt_hmsetex);
            hash_multiset_swap(pt_hmset, pt_hmsetex);
            _print_hash_multiset_sample(pt_hmset);
            _print_hash_multiset_sample(pt_hmsetex);
            t_sample._d_first = 45.90;
            t_sample._l_second = 3490;
            hash_multiset_insert(pt_hmsetex, &t_sample);
            t_sample._d_first = -10.01111;
            t_sample._l_second = 9009;
            hash_multiset_insert(pt_hmsetex, &t_sample);
            t_sample._d_first = 45.087;
            t_sample._l_second = -290;
            hash_multiset_insert(pt_hmsetex, &t_sample);
            hash_multiset_swap(pt_hmset, pt_hmsetex);
            _print_hash_multiset_sample(pt_hmset);
            _print_hash_multiset_sample(pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            t_sample._d_first = 40.099;
            t_sample._l_second = -670;
            hash_multiset_insert(pt_hmsetex, &t_sample);
            t_sample._d_first = 122121.0;
            t_sample._l_second = 56029;
            hash_multiset_insert(pt_hmsetex, &t_sample);
            t_sample._d_first = 45.09898;
            t_sample._l_second = 898;
            hash_multiset_insert(pt_hmsetex, &t_sample);
            t_sample._d_first = 230.9;
            t_sample._l_second = -7777;
            hash_multiset_insert(pt_hmsetex, &t_sample);
            t_sample._d_first = 45.99999;
            t_sample._l_second = 459999;
            hash_multiset_insert(pt_hmsetex, &t_sample);
            hash_multiset_swap(pt_hmset, pt_hmsetex);
            _print_hash_multiset_sample(pt_hmset);
            _print_hash_multiset_sample(pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            t_sample._d_first = 4.5;
            t_sample._l_second = 45;
            hash_multiset_insert(pt_hmsetex, &t_sample);
            hash_multiset_swap(pt_hmset, pt_hmsetex);
            _print_hash_multiset_sample(pt_hmset);
            _print_hash_multiset_sample(pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_swap(pt_hmset, pt_hmsetex);
            _print_hash_multiset_sample(pt_hmset);
            _print_hash_multiset_sample(pt_hmsetex);
            hash_multiset_destroy(pt_hmset);
            hash_multiset_destroy(pt_hmsetex);
        }
        /*hash_multiset_size              */
        /*hash_multiset_empty             */
        /*hash_multiset_max_size          */
        /*hash_multiset_bucket_count      */
        /*hash_multiset_hash              */
        /*hash_multiset_key_less          */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(hash_sample_t);
            if(pt_hmset == NULL)
            {
                return;
            }
            hash_multiset_init_ex(pt_hmset, 100, _hash_set_sample_hash, _hash_sample_great);
            assert(hash_multiset_hash(pt_hmset) == _hash_set_sample_hash &&
                hash_multiset_key_less(pt_hmset) == _hash_sample_great);
            hash_multiset_destroy(pt_hmset);
        }
        /*hash_multiset_resize            */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(hash_sample_t);
            if(pt_hmset == NULL)
            {
                return;
            }
            hash_multiset_init(pt_hmset);
            _print_hash_multiset_sample(pt_hmset);
            hash_multiset_resize(pt_hmset, 100);
            _print_hash_multiset_sample(pt_hmset);
            hash_multiset_resize(pt_hmset, 80);
            _print_hash_multiset_sample(pt_hmset);
            hash_multiset_destroy(pt_hmset);
        }
        /*hash_multiset_equal             */
        /*hash_multiset_not_equal         */
        /*hash_multiset_less              */
        /*hash_multiset_less_equal        */
        /*hash_multiset_great             */
        /*hash_multiset_great_equal       */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(hash_sample_t);
            hash_multiset_t* pt_hmsetex = create_hash_multiset(hash_sample_t);
            hash_sample_t t_sample;
            if(pt_hmset == NULL || pt_hmsetex == NULL)
            {
                return;
            }
            hash_multiset_init(pt_hmset);
            hash_multiset_init(pt_hmsetex);
            _print_hash_multiset_sample(pt_hmset);
            _print_hash_multiset_sample(pt_hmsetex);
            printf("equal: %d, not equal: %d, ",
                hash_multiset_equal(pt_hmset, pt_hmsetex), hash_multiset_not_equal(pt_hmset, pt_hmsetex));
            printf("less: %d, less equal: %d, ",
                hash_multiset_less(pt_hmset, pt_hmsetex), hash_multiset_less_equal(pt_hmset, pt_hmsetex));
            printf("great: %d, great equal: %d\n",
                hash_multiset_great(pt_hmset, pt_hmsetex), hash_multiset_great_equal(pt_hmset, pt_hmsetex));
            t_sample._d_first = 34.98;
            t_sample._l_second = 34;
            hash_multiset_insert(pt_hmset, &t_sample);
            _print_hash_multiset_sample(pt_hmset);
            _print_hash_multiset_sample(pt_hmsetex);
            printf("equal: %d, not equal: %d, ",
                hash_multiset_equal(pt_hmset, pt_hmsetex), hash_multiset_not_equal(pt_hmset, pt_hmsetex));
            printf("less: %d, less equal: %d, ",
                hash_multiset_less(pt_hmset, pt_hmsetex), hash_multiset_less_equal(pt_hmset, pt_hmsetex));
            printf("great: %d, great equal: %d\n",
                hash_multiset_great(pt_hmset, pt_hmsetex), hash_multiset_great_equal(pt_hmset, pt_hmsetex));
            hash_multiset_insert(pt_hmsetex, &t_sample);
            _print_hash_multiset_sample(pt_hmset);
            _print_hash_multiset_sample(pt_hmsetex);
            printf("equal: %d, not equal: %d, ",
                hash_multiset_equal(pt_hmset, pt_hmsetex), hash_multiset_not_equal(pt_hmset, pt_hmsetex));
            printf("less: %d, less equal: %d, ",
                hash_multiset_less(pt_hmset, pt_hmsetex), hash_multiset_less_equal(pt_hmset, pt_hmsetex));
            printf("great: %d, great equal: %d\n",
                hash_multiset_great(pt_hmset, pt_hmsetex), hash_multiset_great_equal(pt_hmset, pt_hmsetex));
            t_sample._d_first = -90.23;
            t_sample._l_second = 0;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = 452.33;
            t_sample._l_second = 90;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = 23232.2;
            t_sample._l_second = 4849;
            hash_multiset_insert(pt_hmsetex, &t_sample);
            _print_hash_multiset_sample(pt_hmset);
            _print_hash_multiset_sample(pt_hmsetex);
            printf("equal: %d, not equal: %d, ",
                hash_multiset_equal(pt_hmset, pt_hmsetex), hash_multiset_not_equal(pt_hmset, pt_hmsetex));
            printf("less: %d, less equal: %d, ",
                hash_multiset_less(pt_hmset, pt_hmsetex), hash_multiset_less_equal(pt_hmset, pt_hmsetex));
            printf("great: %d, great equal: %d\n",
                hash_multiset_great(pt_hmset, pt_hmsetex), hash_multiset_great_equal(pt_hmset, pt_hmsetex));
            hash_multiset_destroy(pt_hmset);
            hash_multiset_destroy(pt_hmsetex);
        }
        /*hash_multiset_begin             */
        /*hash_multiset_end               */
        /*hash_multiset_find              */
        /*hash_multiset_count             */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(hash_sample_t);
            hash_sample_t t_sample;
            iterator_t t_iter;
            if(pt_hmset == NULL)
            {
                return;
            }
            hash_multiset_init(pt_hmset);
            t_sample._d_first = 0.09;
            t_sample._l_second = 45;
            t_iter = hash_multiset_find(pt_hmset, &t_sample);
            if(iterator_equal(t_iter, hash_multiset_end(pt_hmset)))
            {
                printf("not found, count : %d\n", hash_multiset_count(pt_hmset, &t_sample));
            }
            else
            {
                printf("found, count : %d\n", hash_multiset_count(pt_hmset, &t_sample));
            }
            t_sample._d_first = 34234.23;
            t_sample._l_second = 4;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = 67.22;
            t_sample._l_second = 0;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = -8784.23;
            t_sample._l_second = 90;
            hash_multiset_insert(pt_hmset, &t_sample);
            _print_hash_multiset_sample(pt_hmset);
            t_sample._d_first = 0.09;
            t_sample._l_second = 45;
            t_iter = hash_multiset_find(pt_hmset, &t_sample);
            if(iterator_equal(t_iter, hash_multiset_end(pt_hmset)))
            {
                printf("not found, count : %d\n", hash_multiset_count(pt_hmset, &t_sample));
            }
            else
            {
                printf("found, count : %d\n", hash_multiset_count(pt_hmset, &t_sample));
            }
            hash_multiset_insert(pt_hmset, &t_sample);
            _print_hash_multiset_sample(pt_hmset);
            t_iter = hash_multiset_find(pt_hmset, &t_sample);
            if(iterator_equal(t_iter, hash_multiset_end(pt_hmset)))
            {
                printf("not found, count : %d\n", hash_multiset_count(pt_hmset, &t_sample));
            }
            else
            {
                printf("found, count : %d\n", hash_multiset_count(pt_hmset, &t_sample));
            }

            hash_multiset_destroy(pt_hmset);
        }
        /*hash_multiset_equal_range       */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(hash_sample_t);
            hash_sample_t t_sample;
            range_t t_range;
            if(pt_hmset == NULL)
            {
                return;
            }
            hash_multiset_init(pt_hmset);
            t_sample._d_first = 344.23;
            t_sample._l_second = 445;
            t_range = hash_multiset_equal_range(pt_hmset, &t_sample);
            assert(iterator_equal(t_range.t_begin, hash_multiset_end(pt_hmset)));
            assert(iterator_equal(t_range.t_end, hash_multiset_end(pt_hmset)));

            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = 45.098;
            t_sample._l_second = 23;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = 23.23;
            t_sample._l_second = 0;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = 111.111;
            t_sample._l_second = -34;
            hash_multiset_insert(pt_hmset, &t_sample);
            _print_hash_multiset_sample(pt_hmset);
            t_sample._d_first = 45.098;
            t_sample._l_second = 23;
            t_range = hash_multiset_equal_range(pt_hmset, &t_sample);
            assert(iterator_equal(iterator_next(t_range.t_begin), t_range.t_end));
            hash_multiset_destroy(pt_hmset);
        }
        /*hash_multiset_insert            */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(hash_sample_t);
            hash_sample_t t_sample;
            if(pt_hmset == NULL)
            {
                return;
            }
            hash_multiset_init_ex(pt_hmset, 100, _hash_set_int_hash, NULL);
            t_sample._d_first = 4.555;
            t_sample._l_second = 0;
            hash_multiset_insert(pt_hmset, &t_sample);
            hash_multiset_insert(pt_hmset, &t_sample);
            hash_multiset_insert(pt_hmset, &t_sample);
            hash_multiset_insert(pt_hmset, &t_sample);
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = 23.232;
            t_sample._l_second = 1111;
            hash_multiset_insert(pt_hmset, &t_sample);
            hash_multiset_insert(pt_hmset, &t_sample);
            hash_multiset_insert(pt_hmset, &t_sample);
            _print_hash_multiset_sample(pt_hmset);
            hash_multiset_destroy(pt_hmset);
        }
        /*hash_multiset_insert_range      */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(hash_sample_t);
            hash_multiset_t* pt_hmsetex = create_hash_multiset(hash_sample_t);
            hash_sample_t t_sample;
            if(pt_hmset == NULL || pt_hmsetex == NULL)
            {
                return;
            }
            hash_multiset_init(pt_hmset);
            hash_multiset_init(pt_hmsetex);
            hash_multiset_insert_range(pt_hmset, hash_multiset_begin(pt_hmsetex), hash_multiset_end(pt_hmsetex));
            _print_hash_multiset_sample(pt_hmset);
            t_sample._d_first = 44.23;
            t_sample._l_second = 99;
            hash_multiset_insert(pt_hmsetex, &t_sample);
            t_sample._d_first = 12.23323;
            t_sample._l_second = 656;
            hash_multiset_insert(pt_hmsetex, &t_sample);
            t_sample._d_first = -3.0;
            t_sample._l_second = 43;
            hash_multiset_insert(pt_hmsetex, &t_sample);
            t_sample._d_first = 45.23;
            t_sample._l_second = 999;
            hash_multiset_insert(pt_hmsetex, &t_sample);
            t_sample._d_first = 13.23323;
            t_sample._l_second = 656;
            hash_multiset_insert(pt_hmsetex, &t_sample);
            t_sample._d_first = -2.0;
            t_sample._l_second = 43;
            hash_multiset_insert(pt_hmsetex, &t_sample);
            t_sample._d_first = 445.3;
            t_sample._l_second = 999;
            hash_multiset_insert(pt_hmsetex, &t_sample);
            t_sample._d_first = 123.3323;
            t_sample._l_second = 656;
            hash_multiset_insert(pt_hmsetex, &t_sample);
            t_sample._d_first = -32.7;
            t_sample._l_second = 43;
            hash_multiset_insert(pt_hmsetex, &t_sample);
            t_sample._d_first = 445.2;
            t_sample._l_second = 999;
            hash_multiset_insert(pt_hmsetex, &t_sample);
            t_sample._d_first = 123.2323;
            t_sample._l_second = 656;
            hash_multiset_insert(pt_hmsetex, &t_sample);
            t_sample._d_first = -32.9;
            t_sample._l_second = 43;
            hash_multiset_insert(pt_hmsetex, &t_sample);
            _print_hash_multiset_sample(pt_hmsetex);

            hash_multiset_insert_range(pt_hmset, hash_multiset_begin(pt_hmsetex), hash_multiset_begin(pt_hmsetex));
            _print_hash_multiset_sample(pt_hmset);
            hash_multiset_insert_range(pt_hmset, hash_multiset_begin(pt_hmsetex), iterator_advance(hash_multiset_begin(pt_hmsetex), 3));
            _print_hash_multiset_sample(pt_hmset);
            hash_multiset_insert_range(pt_hmset,
                iterator_advance(hash_multiset_begin(pt_hmsetex), 2), iterator_advance(hash_multiset_begin(pt_hmsetex), 7));
            _print_hash_multiset_sample(pt_hmset);
            hash_multiset_insert_range(pt_hmset, iterator_advance(hash_multiset_begin(pt_hmsetex), 5), hash_multiset_end(pt_hmsetex));
            _print_hash_multiset_sample(pt_hmset);
            hash_multiset_insert_range(pt_hmset, hash_multiset_end(pt_hmsetex), hash_multiset_end(pt_hmsetex));
            _print_hash_multiset_sample(pt_hmset);

            hash_multiset_clear(pt_hmset);
            hash_multiset_insert_range(pt_hmset, hash_multiset_begin(pt_hmsetex), hash_multiset_end(pt_hmsetex));
            _print_hash_multiset_sample(pt_hmset);

            hash_multiset_destroy(pt_hmset);
            hash_multiset_destroy(pt_hmsetex);
        }
        /*hash_multiset_erase             */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(hash_sample_t);
            hash_sample_t t_sample;
            if(pt_hmset == NULL)
            {
                return;
            }
            hash_multiset_init(pt_hmset);
            t_sample._d_first = 0.445;
            t_sample._l_second = 789;
            hash_multiset_erase(pt_hmset, &t_sample);
            _print_hash_multiset_sample(pt_hmset);

            t_sample._d_first = 44.23;
            t_sample._l_second = 99;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = 12.23323;
            t_sample._l_second = 656;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = -3.0;
            t_sample._l_second = 43;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = 45.23;
            t_sample._l_second = 999;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = 13.23323;
            t_sample._l_second = 656;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = -2.0;
            t_sample._l_second = 43;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = 445.3;
            t_sample._l_second = 999;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = 123.3323;
            t_sample._l_second = 656;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = -32.7;
            t_sample._l_second = 43;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = 445.2;
            t_sample._l_second = 999;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = 123.2323;
            t_sample._l_second = 656;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = -32.9;
            t_sample._l_second = 43;
            hash_multiset_insert(pt_hmset, &t_sample);
            _print_hash_multiset_sample(pt_hmset);

            t_sample._d_first = 29989.0092;
            t_sample._l_second = 834934;
            hash_multiset_erase(pt_hmset, &t_sample);
            _print_hash_multiset_sample(pt_hmset);
            t_sample._d_first = -32.7;
            t_sample._l_second = 43;
            hash_multiset_erase(pt_hmset, &t_sample);
            _print_hash_multiset_sample(pt_hmset);

            hash_multiset_destroy(pt_hmset);
        }
        /*hash_multiset_erase_pos         */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(hash_sample_t);
            hash_sample_t t_sample;
            if(pt_hmset == NULL)
            {
                return;
            }
            hash_multiset_init(pt_hmset);
            t_sample._d_first = 44.23;
            t_sample._l_second = 99;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = 12.23323;
            t_sample._l_second = 656;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = -3.0;
            t_sample._l_second = 43;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = 45.23;
            t_sample._l_second = 999;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = 13.23323;
            t_sample._l_second = 656;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = -2.0;
            t_sample._l_second = 43;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = 445.3;
            t_sample._l_second = 999;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = 123.3323;
            t_sample._l_second = 656;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = -32.7;
            t_sample._l_second = 43;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = 445.2;
            t_sample._l_second = 999;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = 123.2323;
            t_sample._l_second = 656;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = -32.9;
            t_sample._l_second = 43;
            hash_multiset_insert(pt_hmset, &t_sample);
            _print_hash_multiset_sample(pt_hmset);

            hash_multiset_erase_pos(pt_hmset, hash_multiset_begin(pt_hmset));
            _print_hash_multiset_sample(pt_hmset);
            hash_multiset_erase_pos(pt_hmset, iterator_advance(hash_multiset_begin(pt_hmset), 5));
            _print_hash_multiset_sample(pt_hmset);
            while(!hash_multiset_empty(pt_hmset))
            {
                hash_multiset_erase_pos(pt_hmset, hash_multiset_begin(pt_hmset));
            }
            _print_hash_multiset_sample(pt_hmset);

            hash_multiset_destroy(pt_hmset);
        }
        /*hash_multiset_erase_range       */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(hash_sample_t);
            hash_sample_t t_sample;
            if(pt_hmset == NULL)
            {
                return;
            }
            hash_multiset_init(pt_hmset);
            hash_multiset_erase_range(pt_hmset, hash_multiset_begin(pt_hmset), hash_multiset_end(pt_hmset));
            t_sample._d_first = 44.23;
            t_sample._l_second = 99;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = 12.23323;
            t_sample._l_second = 656;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = -3.0;
            t_sample._l_second = 43;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = 45.23;
            t_sample._l_second = 999;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = 13.23323;
            t_sample._l_second = 656;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = -2.0;
            t_sample._l_second = 43;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = 445.3;
            t_sample._l_second = 999;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = 123.3323;
            t_sample._l_second = 656;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = -32.7;
            t_sample._l_second = 43;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = 445.2;
            t_sample._l_second = 999;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = 123.2323;
            t_sample._l_second = 656;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = -32.9;
            t_sample._l_second = 43;
            hash_multiset_insert(pt_hmset, &t_sample);
            _print_hash_multiset_sample(pt_hmset);

            hash_multiset_erase_range(pt_hmset, hash_multiset_begin(pt_hmset), hash_multiset_begin(pt_hmset));
            _print_hash_multiset_sample(pt_hmset);
            hash_multiset_erase_range(pt_hmset, hash_multiset_begin(pt_hmset), iterator_next(hash_multiset_begin(pt_hmset)));
            _print_hash_multiset_sample(pt_hmset);
            hash_multiset_erase_range(pt_hmset,
                iterator_advance(hash_multiset_begin(pt_hmset), 3), iterator_advance(hash_multiset_begin(pt_hmset), 6));
            _print_hash_multiset_sample(pt_hmset);
            hash_multiset_erase_range(pt_hmset, iterator_advance(hash_multiset_begin(pt_hmset), 5), hash_multiset_end(pt_hmset));
            _print_hash_multiset_sample(pt_hmset);
            hash_multiset_erase_range(pt_hmset, hash_multiset_end(pt_hmset), hash_multiset_end(pt_hmset));
            _print_hash_multiset_sample(pt_hmset);
            hash_multiset_erase_range(pt_hmset, hash_multiset_begin(pt_hmset), hash_multiset_end(pt_hmset));
            _print_hash_multiset_sample(pt_hmset);

            hash_multiset_destroy(pt_hmset);
        }
        /*hash_multiset_clear             */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(hash_sample_t);
            hash_sample_t t_sample;
            if(pt_hmset == NULL)
            {
                return;
            }
            hash_multiset_init(pt_hmset);
            hash_multiset_clear(pt_hmset);
            _print_hash_multiset_sample(pt_hmset);
            t_sample._d_first = 44.23;
            t_sample._l_second = 99;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = 12.23323;
            t_sample._l_second = 656;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = -3.0;
            t_sample._l_second = 43;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = 45.23;
            t_sample._l_second = 999;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = 13.23323;
            t_sample._l_second = 656;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = -2.0;
            t_sample._l_second = 43;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = 445.3;
            t_sample._l_second = 999;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = 123.3323;
            t_sample._l_second = 656;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = -32.7;
            t_sample._l_second = 43;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = 445.2;
            t_sample._l_second = 999;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = 123.2323;
            t_sample._l_second = 656;
            hash_multiset_insert(pt_hmset, &t_sample);
            t_sample._d_first = -32.9;
            t_sample._l_second = 43;
            hash_multiset_insert(pt_hmset, &t_sample);
            _print_hash_multiset_sample(pt_hmset);

            hash_multiset_clear(pt_hmset);
            _print_hash_multiset_sample(pt_hmset);

            hash_multiset_destroy(pt_hmset);
        }
    }
    /* cstl type */
    {
        /*create_hash_multiset            */
        /*hash_multiset_init              */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(hash_multiset_t<int>);
            hash_multiset_t* pt_hmsetex = create_hash_multiset(int);
            if(pt_hmset == NULL || pt_hmsetex == NULL)
            {
                return;
            }
            hash_multiset_init(pt_hmset);
            hash_multiset_init(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 12239);
            hash_multiset_insert(pt_hmsetex, 20);
            hash_multiset_insert(pt_hmsetex, -847);
            hash_multiset_insert(pt_hmsetex, 0);
            hash_multiset_insert(pt_hmsetex, 44);
            hash_multiset_insert(pt_hmsetex, 99);
            hash_multiset_insert(pt_hmset, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, -74);
            hash_multiset_insert(pt_hmsetex, 2233);
            hash_multiset_insert(pt_hmsetex, 90);
            hash_multiset_insert(pt_hmsetex, 4);
            hash_multiset_insert(pt_hmsetex, 334);
            hash_multiset_insert(pt_hmsetex, 5);
            hash_multiset_insert(pt_hmsetex, -76);
            hash_multiset_insert(pt_hmset, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 4);
            hash_multiset_insert(pt_hmsetex, -4);
            hash_multiset_insert(pt_hmset, pt_hmsetex);
            _print_hash_multiset_cstl(pt_hmset);
            hash_multiset_destroy(pt_hmset);
            hash_multiset_destroy(pt_hmsetex);
        }
        /*hash_multiset_init_ex           */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(hash_multiset_t<int>);
            hash_multiset_t* pt_hmsetex = create_hash_multiset(int);
            if(pt_hmset == NULL || pt_hmsetex == NULL)
            {
                return;
            }
            hash_multiset_init_ex(pt_hmset, 100, _hash_multiset_cstl_hash, NULL);
            hash_multiset_init(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 12239);
            hash_multiset_insert(pt_hmsetex, 20);
            hash_multiset_insert(pt_hmsetex, -847);
            hash_multiset_insert(pt_hmsetex, 0);
            hash_multiset_insert(pt_hmsetex, 44);
            hash_multiset_insert(pt_hmsetex, 99);
            hash_multiset_insert(pt_hmset, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, -74);
            hash_multiset_insert(pt_hmsetex, 2233);
            hash_multiset_insert(pt_hmsetex, 90);
            hash_multiset_insert(pt_hmsetex, 4);
            hash_multiset_insert(pt_hmsetex, 334);
            hash_multiset_insert(pt_hmsetex, 5);
            hash_multiset_insert(pt_hmsetex, -76);
            hash_multiset_insert(pt_hmset, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 4);
            hash_multiset_insert(pt_hmsetex, -4);
            hash_multiset_insert(pt_hmset, pt_hmsetex);
            _print_hash_multiset_cstl(pt_hmset);
            hash_multiset_destroy(pt_hmset);
            hash_multiset_destroy(pt_hmsetex);
        }
        /*hash_multiset_init_copy         */
        {
            hash_multiset_t* pt_hmset1 = create_hash_multiset(hash_multiset_t<int>);
            hash_multiset_t* pt_hmset2 = create_hash_multiset(hash_multiset_t<int>);
            hash_multiset_t* pt_hmsetex = create_hash_multiset(int);
            if(pt_hmset1 == NULL || pt_hmset2 == NULL || pt_hmsetex == NULL)
            {
                return;
            }
            hash_multiset_init(pt_hmsetex);
            hash_multiset_init_ex(pt_hmset2, 200, _hash_multiset_cstl_hash, NULL);

            hash_multiset_insert(pt_hmsetex, 12239);
            hash_multiset_insert(pt_hmsetex, 20);
            hash_multiset_insert(pt_hmsetex, -847);
            hash_multiset_insert(pt_hmsetex, 0);
            hash_multiset_insert(pt_hmsetex, 44);
            hash_multiset_insert(pt_hmsetex, 99);
            hash_multiset_insert(pt_hmset2, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, -74);
            hash_multiset_insert(pt_hmsetex, 2233);
            hash_multiset_insert(pt_hmsetex, 90);
            hash_multiset_insert(pt_hmsetex, 4);
            hash_multiset_insert(pt_hmsetex, 334);
            hash_multiset_insert(pt_hmsetex, 5);
            hash_multiset_insert(pt_hmsetex, -76);
            hash_multiset_insert(pt_hmset2, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 4);
            hash_multiset_insert(pt_hmsetex, -4);
            hash_multiset_insert(pt_hmset2, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 4444);
            hash_multiset_insert(pt_hmsetex, -98);
            hash_multiset_insert(pt_hmsetex, 2222);
            hash_multiset_insert(pt_hmsetex, 1);
            hash_multiset_insert(pt_hmsetex, 3);
            hash_multiset_insert(pt_hmsetex, 55);
            hash_multiset_insert(pt_hmset2, pt_hmsetex);

            hash_multiset_init_copy(pt_hmset1, pt_hmset2);

            _print_hash_multiset_cstl(pt_hmset1);

            hash_multiset_destroy(pt_hmsetex);
            hash_multiset_destroy(pt_hmset1);
            hash_multiset_destroy(pt_hmset2);
        }
        /*hash_multiset_init_copy_range   */
        {
            hash_multiset_t* pt_hmset1 = create_hash_multiset(hash_multiset_t<int>);
            hash_multiset_t* pt_hmset2 = create_hash_multiset(hash_multiset_t<int>);
            hash_multiset_t* pt_hmsetex = create_hash_multiset(int);
            if(pt_hmset1 == NULL || pt_hmset2 == NULL || pt_hmsetex == NULL)
            {
                return;
            }
            hash_multiset_init(pt_hmsetex);
            hash_multiset_init_ex(pt_hmset2, 200, _hash_multiset_cstl_hash, NULL);

            hash_multiset_insert(pt_hmsetex, 12239);
            hash_multiset_insert(pt_hmsetex, 20);
            hash_multiset_insert(pt_hmsetex, -847);
            hash_multiset_insert(pt_hmsetex, 0);
            hash_multiset_insert(pt_hmsetex, 44);
            hash_multiset_insert(pt_hmsetex, 99);
            hash_multiset_insert(pt_hmset2, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, -74);
            hash_multiset_insert(pt_hmsetex, 2233);
            hash_multiset_insert(pt_hmsetex, 90);
            hash_multiset_insert(pt_hmsetex, 4);
            hash_multiset_insert(pt_hmsetex, 334);
            hash_multiset_insert(pt_hmsetex, 5);
            hash_multiset_insert(pt_hmsetex, -76);
            hash_multiset_insert(pt_hmset2, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 4);
            hash_multiset_insert(pt_hmsetex, -4);
            hash_multiset_insert(pt_hmset2, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 4444);
            hash_multiset_insert(pt_hmsetex, -98);
            hash_multiset_insert(pt_hmsetex, 2222);
            hash_multiset_insert(pt_hmsetex, 1);
            hash_multiset_insert(pt_hmsetex, 3);
            hash_multiset_insert(pt_hmsetex, 55);
            hash_multiset_insert(pt_hmset2, pt_hmsetex);

            hash_multiset_init_copy_range(pt_hmset1,
                hash_multiset_begin(pt_hmset2),
                hash_multiset_end(pt_hmset2));

            _print_hash_multiset_cstl(pt_hmset2);
            _print_hash_multiset_cstl(pt_hmset1);

            hash_multiset_destroy(pt_hmsetex);
            hash_multiset_destroy(pt_hmset1);
            hash_multiset_destroy(pt_hmset2);
        }
        /*hash_multiset_init_copy_range_ex*/
        {
            hash_multiset_t* pt_hmset1 = create_hash_multiset(hash_multiset_t<int>);
            hash_multiset_t* pt_hmset2 = create_hash_multiset(hash_multiset_t<int>);
            hash_multiset_t* pt_hmsetex = create_hash_multiset(int);
            if(pt_hmset1 == NULL || pt_hmset2 == NULL || pt_hmsetex == NULL)
            {
                return;
            }
            hash_multiset_init_ex(pt_hmsetex, 200, NULL, NULL);
            hash_multiset_init(pt_hmset2);

            hash_multiset_insert(pt_hmsetex, 12239);
            hash_multiset_insert(pt_hmsetex, 20);
            hash_multiset_insert(pt_hmsetex, -847);
            hash_multiset_insert(pt_hmsetex, 0);
            hash_multiset_insert(pt_hmsetex, 44);
            hash_multiset_insert(pt_hmsetex, 99);
            hash_multiset_insert(pt_hmset2, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, -74);
            hash_multiset_insert(pt_hmsetex, 2233);
            hash_multiset_insert(pt_hmsetex, 90);
            hash_multiset_insert(pt_hmsetex, 4);
            hash_multiset_insert(pt_hmsetex, 334);
            hash_multiset_insert(pt_hmsetex, 5);
            hash_multiset_insert(pt_hmsetex, -76);
            hash_multiset_insert(pt_hmset2, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 4);
            hash_multiset_insert(pt_hmsetex, -4);
            hash_multiset_insert(pt_hmset2, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 4444);
            hash_multiset_insert(pt_hmsetex, -98);
            hash_multiset_insert(pt_hmsetex, 2222);
            hash_multiset_insert(pt_hmsetex, 1);
            hash_multiset_insert(pt_hmsetex, 3);
            hash_multiset_insert(pt_hmsetex, 55);
            hash_multiset_insert(pt_hmset2, pt_hmsetex);

            hash_multiset_init_copy_range_ex(pt_hmset1,
                hash_multiset_begin(pt_hmset2),
                hash_multiset_end(pt_hmset2),
                100, _hash_multiset_cstl_hash, NULL);

            _print_hash_multiset_cstl(pt_hmset2);
            _print_hash_multiset_cstl(pt_hmset1);

            hash_multiset_destroy(pt_hmsetex);
            hash_multiset_destroy(pt_hmset1);
            hash_multiset_destroy(pt_hmset2);
        }
        /*hash_multiset_destroy           */
        /*hash_multiset_assign            */
        /*hash_multiset_swap              */
        {
            hash_multiset_t* pt_hmset1 = create_hash_multiset(hash_multiset_t<int>);
            hash_multiset_t* pt_hmset2 = create_hash_multiset(hash_multiset_t<int>);
            hash_multiset_t* pt_hmsetex = create_hash_multiset(int);
            if(pt_hmset1 == NULL || pt_hmset2 == NULL || pt_hmsetex == NULL)
            {
                return;
            }
            hash_multiset_init_ex(pt_hmsetex, 200, NULL, NULL);
            hash_multiset_init(pt_hmset2);
            hash_multiset_init(pt_hmset1);

            hash_multiset_swap(pt_hmset1, pt_hmset2);
            _print_hash_multiset_cstl(pt_hmset1);
            _print_hash_multiset_cstl(pt_hmset2);

            hash_multiset_insert(pt_hmsetex, 12239);
            hash_multiset_insert(pt_hmsetex, 20);
            hash_multiset_insert(pt_hmsetex, -847);
            hash_multiset_insert(pt_hmsetex, 0);
            hash_multiset_insert(pt_hmsetex, 44);
            hash_multiset_insert(pt_hmsetex, 99);
            hash_multiset_insert(pt_hmset2, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, -74);
            hash_multiset_insert(pt_hmsetex, 2233);
            hash_multiset_insert(pt_hmsetex, 90);
            hash_multiset_insert(pt_hmsetex, 4);
            hash_multiset_insert(pt_hmsetex, 334);
            hash_multiset_insert(pt_hmsetex, 5);
            hash_multiset_insert(pt_hmsetex, -76);
            hash_multiset_insert(pt_hmset2, pt_hmsetex);

            hash_multiset_swap(pt_hmset1, pt_hmset2);
            _print_hash_multiset_cstl(pt_hmset1);
            _print_hash_multiset_cstl(pt_hmset2);

            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 4);
            hash_multiset_insert(pt_hmsetex, -4);
            hash_multiset_insert(pt_hmset2, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 4444);
            hash_multiset_insert(pt_hmsetex, -98);
            hash_multiset_insert(pt_hmsetex, 2222);
            hash_multiset_insert(pt_hmsetex, 1);
            hash_multiset_insert(pt_hmsetex, 3);
            hash_multiset_insert(pt_hmsetex, 55);
            hash_multiset_insert(pt_hmset2, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 4);
            hash_multiset_insert(pt_hmsetex, 23844);
            hash_multiset_insert(pt_hmsetex, 2);
            hash_multiset_insert(pt_hmsetex, 4444);
            hash_multiset_insert(pt_hmsetex, 67);
            hash_multiset_insert(pt_hmsetex, 5098);
            hash_multiset_insert(pt_hmsetex, 1);
            hash_multiset_insert(pt_hmsetex, 2);
            hash_multiset_insert(pt_hmsetex, 43);
            hash_multiset_clear(pt_hmset2);
            hash_multiset_insert(pt_hmset2, pt_hmsetex);

            hash_multiset_swap(pt_hmset1, pt_hmset2);
            _print_hash_multiset_cstl(pt_hmset1);
            _print_hash_multiset_cstl(pt_hmset2);

            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 8);
            hash_multiset_insert(pt_hmsetex, 2);
            hash_multiset_insert(pt_hmsetex, 5);
            hash_multiset_insert(pt_hmsetex, 9);
            hash_multiset_insert(pt_hmsetex, 4);
            hash_multiset_insert(pt_hmsetex, 1);
            hash_multiset_insert(pt_hmsetex, 6);
            hash_multiset_insert(pt_hmsetex, 7);
            hash_multiset_insert(pt_hmsetex, 3);
            hash_multiset_insert(pt_hmsetex, 0);
            hash_multiset_clear(pt_hmset2);
            hash_multiset_insert(pt_hmset2, pt_hmsetex);

            hash_multiset_swap(pt_hmset1, pt_hmset2);
            _print_hash_multiset_cstl(pt_hmset2);
            _print_hash_multiset_cstl(pt_hmset1);

            hash_multiset_clear(pt_hmset2);
            hash_multiset_swap(pt_hmset1, pt_hmset2);
            _print_hash_multiset_cstl(pt_hmset2);
            _print_hash_multiset_cstl(pt_hmset1);

            hash_multiset_destroy(pt_hmsetex);
            hash_multiset_destroy(pt_hmset1);
            hash_multiset_destroy(pt_hmset2);
        }
        /*hash_multiset_size              */
        /*hash_multiset_empty             */
        /*hash_multiset_max_size          */
        /*hash_multiset_bucket_count      */
        /*hash_multiset_hash              */
        /*hash_multiset_key_less          */
        {
            hash_multiset_t* pt_hset = create_hash_multiset(hash_multiset_t<int>);
            if(pt_hset == NULL)
            {
                return;
            }
            hash_multiset_init_ex(pt_hset, 100, _hash_multiset_cstl_hash, NULL);
            assert(hash_multiset_hash(pt_hset) == _hash_multiset_cstl_hash &&
                hash_multiset_key_less(pt_hset) != NULL);
            hash_multiset_destroy(pt_hset);
        }
        /*hash_multiset_resize            */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(hash_multiset_t<int>);
            if(pt_hmset == NULL)
            {
                return;
            }
            hash_multiset_init(pt_hmset);
            _print_hash_multiset_cstl(pt_hmset);
            hash_multiset_resize(pt_hmset, 30);
            _print_hash_multiset_cstl(pt_hmset);
            hash_multiset_resize(pt_hmset, 60);
            _print_hash_multiset_cstl(pt_hmset);
            hash_multiset_resize(pt_hmset, 10);
            _print_hash_multiset_cstl(pt_hmset);
            hash_multiset_resize(pt_hmset, 0);
            _print_hash_multiset_cstl(pt_hmset);
            hash_multiset_destroy(pt_hmset);
        }
        /*hash_multiset_equal             */
        /*hash_multiset_not_equal         */
        /*hash_multiset_less              */
        /*hash_multiset_less_equal        */
        /*hash_multiset_great             */
        /*hash_multiset_great_equal       */
        {
            hash_multiset_t* pt_hmset1 = create_hash_multiset(hash_multiset_t<int>);
            hash_multiset_t* pt_hmset2 = create_hash_multiset(hash_multiset_t<int>);
            hash_multiset_t* pt_hmsetex = create_hash_multiset(int);
            if(pt_hmset1 == NULL || pt_hmset2 == NULL || pt_hmsetex == NULL)
            {
                return;
            }
            hash_multiset_init(pt_hmsetex);
            hash_multiset_init(pt_hmset1);
            hash_multiset_init(pt_hmset2);
            _print_hash_multiset_cstl(pt_hmset1);
            _print_hash_multiset_cstl(pt_hmset2);
            printf("equal: %d, not equal: %d, ",
                hash_multiset_equal(pt_hmset1, pt_hmset2), hash_multiset_not_equal(pt_hmset1, pt_hmset2));
            printf("less: %d, less equal: %d, ",
                hash_multiset_less(pt_hmset1, pt_hmset2), hash_multiset_less_equal(pt_hmset1, pt_hmset2));
            printf("great: %d, great equal: %d\n",
                hash_multiset_great(pt_hmset1, pt_hmset2), hash_multiset_great_equal(pt_hmset1, pt_hmset2));

            hash_multiset_insert(pt_hmsetex, 23);
            hash_multiset_insert(pt_hmsetex, 56);
            hash_multiset_insert(pt_hmsetex, 90);
            hash_multiset_insert(pt_hmsetex, 3);
            hash_multiset_insert(pt_hmset1, pt_hmsetex);
            _print_hash_multiset_cstl(pt_hmset1);
            _print_hash_multiset_cstl(pt_hmset2);
            printf("equal: %d, not equal: %d, ",
                hash_multiset_equal(pt_hmset1, pt_hmset2), hash_multiset_not_equal(pt_hmset1, pt_hmset2));
            printf("less: %d, less equal: %d, ",
                hash_multiset_less(pt_hmset1, pt_hmset2), hash_multiset_less_equal(pt_hmset1, pt_hmset2));
            printf("great: %d, great equal: %d\n",
                hash_multiset_great(pt_hmset1, pt_hmset2), hash_multiset_great_equal(pt_hmset1, pt_hmset2));

            hash_multiset_insert(pt_hmset2, pt_hmsetex);
            _print_hash_multiset_cstl(pt_hmset1);
            _print_hash_multiset_cstl(pt_hmset2);
            printf("equal: %d, not equal: %d, ",
                hash_multiset_equal(pt_hmset1, pt_hmset2), hash_multiset_not_equal(pt_hmset1, pt_hmset2));
            printf("less: %d, less equal: %d, ",
                hash_multiset_less(pt_hmset1, pt_hmset2), hash_multiset_less_equal(pt_hmset1, pt_hmset2));
            printf("great: %d, great equal: %d\n",
                hash_multiset_great(pt_hmset1, pt_hmset2), hash_multiset_great_equal(pt_hmset1, pt_hmset2));

            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 333);
            hash_multiset_insert(pt_hmsetex, 2);
            hash_multiset_insert(pt_hmsetex, 55);
            hash_multiset_insert(pt_hmset1, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 50);
            hash_multiset_insert(pt_hmsetex, 55);
            hash_multiset_insert(pt_hmset1, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 33);
            hash_multiset_insert(pt_hmsetex, 9000);
            hash_multiset_insert(pt_hmsetex, 1);
            hash_multiset_insert(pt_hmsetex, 4);
            hash_multiset_insert(pt_hmsetex, 999);
            hash_multiset_insert(pt_hmsetex, 34);
            hash_multiset_insert(pt_hmsetex, 12);
            hash_multiset_insert(pt_hmset2, pt_hmsetex);
            _print_hash_multiset_cstl(pt_hmset1);
            _print_hash_multiset_cstl(pt_hmset2);
            printf("equal: %d, not equal: %d, ",
                hash_multiset_equal(pt_hmset1, pt_hmset2), hash_multiset_not_equal(pt_hmset1, pt_hmset2));
            printf("less: %d, less equal: %d, ",
                hash_multiset_less(pt_hmset1, pt_hmset2), hash_multiset_less_equal(pt_hmset1, pt_hmset2));
            printf("great: %d, great equal: %d\n",
                hash_multiset_great(pt_hmset1, pt_hmset2), hash_multiset_great_equal(pt_hmset1, pt_hmset2));
            
            hash_multiset_destroy(pt_hmsetex);
            hash_multiset_destroy(pt_hmset1);
            hash_multiset_destroy(pt_hmset2);
        }
        /*hash_multiset_begin             */
        /*hash_multiset_end               */
        /*hash_multiset_find              */
        /*hash_multiset_count             */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(hash_multiset_t<int>);
            hash_multiset_t* pt_hmsetex = create_hash_multiset(int);
            iterator_t t_iter;
            if(pt_hmset == NULL || pt_hmsetex == NULL)
            {
                return;
            }
            hash_multiset_init_ex(pt_hmset, 50, _hash_multiset_cstl_hash, NULL);
            hash_multiset_init(pt_hmsetex);
            t_iter = hash_multiset_find(pt_hmset, pt_hmsetex);
            if(iterator_equal(t_iter, hash_multiset_end(pt_hmset)))
            {
                printf("not found! count : %d\n", hash_multiset_count(pt_hmset, pt_hmsetex));
            }
            else
            {
                printf("found! count : %d\n", hash_multiset_count(pt_hmset, pt_hmsetex));
            }
            hash_multiset_insert(pt_hmsetex, 12239);
            hash_multiset_insert(pt_hmsetex, 20);
            hash_multiset_insert(pt_hmsetex, -847);
            hash_multiset_insert(pt_hmsetex, 0);
            hash_multiset_insert(pt_hmsetex, 44);
            hash_multiset_insert(pt_hmsetex, 99);
            hash_multiset_insert(pt_hmset, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, -74);
            hash_multiset_insert(pt_hmsetex, 2233);
            hash_multiset_insert(pt_hmsetex, 90);
            hash_multiset_insert(pt_hmsetex, 4);
            hash_multiset_insert(pt_hmsetex, 334);
            hash_multiset_insert(pt_hmsetex, 5);
            hash_multiset_insert(pt_hmsetex, -76);
            hash_multiset_insert(pt_hmset, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 4);
            hash_multiset_insert(pt_hmsetex, -4);
            hash_multiset_insert(pt_hmset, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 4444);
            hash_multiset_insert(pt_hmsetex, -98);
            hash_multiset_insert(pt_hmsetex, 2222);
            hash_multiset_insert(pt_hmsetex, 1);
            hash_multiset_insert(pt_hmsetex, 3);
            hash_multiset_insert(pt_hmsetex, 55);
            hash_multiset_insert(pt_hmset, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 4);
            hash_multiset_insert(pt_hmsetex, 23844);
            hash_multiset_insert(pt_hmsetex, 2);
            hash_multiset_insert(pt_hmsetex, 4444);
            hash_multiset_insert(pt_hmsetex, 67);
            hash_multiset_insert(pt_hmsetex, 5098);
            hash_multiset_insert(pt_hmsetex, 1);
            hash_multiset_insert(pt_hmsetex, 2);
            hash_multiset_insert(pt_hmsetex, 43);
            hash_multiset_insert(pt_hmset, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 8);
            hash_multiset_insert(pt_hmsetex, 2);
            hash_multiset_insert(pt_hmsetex, 5);
            hash_multiset_insert(pt_hmsetex, 9);
            hash_multiset_insert(pt_hmsetex, 4);
            hash_multiset_insert(pt_hmsetex, 1);
            hash_multiset_insert(pt_hmsetex, 6);
            hash_multiset_insert(pt_hmsetex, 7);
            hash_multiset_insert(pt_hmsetex, 3);
            hash_multiset_insert(pt_hmsetex, 0);
            hash_multiset_insert(pt_hmset, pt_hmsetex);

            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, -87);
            hash_multiset_insert(pt_hmsetex, -90);
            hash_multiset_insert(pt_hmsetex, -223);

            t_iter = hash_multiset_find(pt_hmset, pt_hmsetex);
            if(iterator_equal(t_iter, hash_multiset_end(pt_hmset)))
            {
                printf("not found! count : %d\n", hash_multiset_count(pt_hmset, pt_hmsetex));
            }
            else
            {
                printf("found! count : %d\n", hash_multiset_count(pt_hmset, pt_hmsetex));
            }
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 4444);
            hash_multiset_insert(pt_hmsetex, -98);
            hash_multiset_insert(pt_hmsetex, 2222);
            hash_multiset_insert(pt_hmsetex, 1);
            hash_multiset_insert(pt_hmsetex, 3);
            hash_multiset_insert(pt_hmsetex, 55);
            t_iter = hash_multiset_find(pt_hmset, pt_hmsetex);
            if(iterator_equal(t_iter, hash_multiset_end(pt_hmset)))
            {
                printf("not found! count : %d\n", hash_multiset_count(pt_hmset, pt_hmsetex));
            }
            else
            {
                printf("found! count : %d\n", hash_multiset_count(pt_hmset, pt_hmsetex));
            }

            hash_multiset_destroy(pt_hmset);
            hash_multiset_destroy(pt_hmsetex);
        }
        /*hash_multiset_equal_range       */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(hash_multiset_t<int>);
            hash_multiset_t* pt_hmsetex = create_hash_multiset(int);
            range_t t_range;
            if(pt_hmset == NULL || pt_hmsetex == NULL)
            {
                return;
            }
            hash_multiset_init_ex(pt_hmset, 50, _hash_multiset_cstl_hash, NULL);
            hash_multiset_init(pt_hmsetex);
            t_range = hash_multiset_equal_range(pt_hmset, pt_hmsetex);
            assert(iterator_equal(t_range.t_begin, t_range.t_end) &&
                iterator_equal(t_range.t_begin, hash_multiset_end(pt_hmset)));
            hash_multiset_insert(pt_hmsetex, 12239);
            hash_multiset_insert(pt_hmsetex, 20);
            hash_multiset_insert(pt_hmsetex, -847);
            hash_multiset_insert(pt_hmsetex, 0);
            hash_multiset_insert(pt_hmsetex, 44);
            hash_multiset_insert(pt_hmsetex, 99);
            hash_multiset_insert(pt_hmset, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, -74);
            hash_multiset_insert(pt_hmsetex, 2233);
            hash_multiset_insert(pt_hmsetex, 90);
            hash_multiset_insert(pt_hmsetex, 4);
            hash_multiset_insert(pt_hmsetex, 334);
            hash_multiset_insert(pt_hmsetex, 5);
            hash_multiset_insert(pt_hmsetex, -76);
            hash_multiset_insert(pt_hmset, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 4);
            hash_multiset_insert(pt_hmsetex, -4);
            hash_multiset_insert(pt_hmset, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 4444);
            hash_multiset_insert(pt_hmsetex, -98);
            hash_multiset_insert(pt_hmsetex, 2222);
            hash_multiset_insert(pt_hmsetex, 1);
            hash_multiset_insert(pt_hmsetex, 3);
            hash_multiset_insert(pt_hmsetex, 55);
            hash_multiset_insert(pt_hmset, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 4);
            hash_multiset_insert(pt_hmsetex, 23844);
            hash_multiset_insert(pt_hmsetex, 2);
            hash_multiset_insert(pt_hmsetex, 4444);
            hash_multiset_insert(pt_hmsetex, 67);
            hash_multiset_insert(pt_hmsetex, 5098);
            hash_multiset_insert(pt_hmsetex, 1);
            hash_multiset_insert(pt_hmsetex, 2);
            hash_multiset_insert(pt_hmsetex, 43);
            hash_multiset_insert(pt_hmset, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 8);
            hash_multiset_insert(pt_hmsetex, 2);
            hash_multiset_insert(pt_hmsetex, 5);
            hash_multiset_insert(pt_hmsetex, 9);
            hash_multiset_insert(pt_hmsetex, 4);
            hash_multiset_insert(pt_hmsetex, 1);
            hash_multiset_insert(pt_hmsetex, 6);
            hash_multiset_insert(pt_hmsetex, 7);
            hash_multiset_insert(pt_hmsetex, 3);
            hash_multiset_insert(pt_hmsetex, 0);
            hash_multiset_insert(pt_hmset, pt_hmsetex);

            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 4444);
            hash_multiset_insert(pt_hmsetex, -98);
            hash_multiset_insert(pt_hmsetex, 3);
            hash_multiset_insert(pt_hmsetex, 55);
            t_range = hash_multiset_equal_range(pt_hmset, pt_hmsetex);
            assert(iterator_equal(t_range.t_begin, t_range.t_end));

            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 4444);
            hash_multiset_insert(pt_hmsetex, -98);
            hash_multiset_insert(pt_hmsetex, 2222);
            hash_multiset_insert(pt_hmsetex, 1);
            hash_multiset_insert(pt_hmsetex, 3);
            hash_multiset_insert(pt_hmsetex, 55);

            t_range = hash_multiset_equal_range(pt_hmset, pt_hmsetex);
            assert(iterator_equal(iterator_next(t_range.t_begin), t_range.t_end));
            hash_multiset_destroy(pt_hmset);
            hash_multiset_destroy(pt_hmsetex);
        }
        /*hash_multiset_insert            */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(hash_multiset_t<int>);
            hash_multiset_t* pt_hmsetex = create_hash_multiset(int);
            if(pt_hmset == NULL || pt_hmsetex == NULL)
            {
                return;
            }
            hash_multiset_init_ex(pt_hmset, 50, _hash_multiset_cstl_hash, NULL);
            hash_multiset_init(pt_hmsetex);

            hash_multiset_insert(pt_hmsetex, 4444);
            hash_multiset_insert(pt_hmsetex, -98);
            hash_multiset_insert(pt_hmsetex, 2222);
            hash_multiset_insert(pt_hmsetex, 1);
            hash_multiset_insert(pt_hmsetex, 3);
            hash_multiset_insert(pt_hmsetex, 55);
            hash_multiset_insert(pt_hmset, pt_hmsetex);
            _print_hash_multiset_cstl(pt_hmset);

            hash_multiset_insert(pt_hmset, pt_hmsetex);
            hash_multiset_insert(pt_hmset, pt_hmsetex);
            hash_multiset_insert(pt_hmset, pt_hmsetex);
            _print_hash_multiset_cstl(pt_hmset);

            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 4444);
            hash_multiset_insert(pt_hmsetex, -98);
            hash_multiset_insert(pt_hmsetex, 3);
            hash_multiset_insert(pt_hmsetex, 55);
            hash_multiset_insert(pt_hmset, pt_hmsetex);
            _print_hash_multiset_cstl(pt_hmset);

            hash_multiset_destroy(pt_hmset);
            hash_multiset_destroy(pt_hmsetex);
        }
        /*hash_multiset_insert_range      */
        {
            hash_multiset_t* pt_hmset1 = create_hash_multiset(hash_multiset_t<int>);
            hash_multiset_t* pt_hmset2 = create_hash_multiset(hash_multiset_t<int>);
            hash_multiset_t* pt_hmsetex = create_hash_multiset(int);
            if(pt_hmset1 == NULL || pt_hmset2 == NULL || pt_hmsetex == NULL)
            {
                return;
            }
            hash_multiset_init(pt_hmsetex);
            hash_multiset_init_ex(pt_hmset2, 50, _hash_multiset_cstl_hash, NULL);
            hash_multiset_init_ex(pt_hmset1, 50, _hash_multiset_cstl_hash, NULL);

            hash_multiset_insert_range(pt_hmset1, hash_multiset_begin(pt_hmset2), hash_multiset_end(pt_hmset2));
            _print_hash_multiset_cstl(pt_hmset1);

            hash_multiset_insert(pt_hmsetex, 12239);
            hash_multiset_insert(pt_hmsetex, 20);
            hash_multiset_insert(pt_hmsetex, -847);
            hash_multiset_insert(pt_hmsetex, 0);
            hash_multiset_insert(pt_hmsetex, 44);
            hash_multiset_insert(pt_hmsetex, 99);
            hash_multiset_insert(pt_hmset2, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, -74);
            hash_multiset_insert(pt_hmsetex, 2233);
            hash_multiset_insert(pt_hmsetex, 90);
            hash_multiset_insert(pt_hmsetex, 4);
            hash_multiset_insert(pt_hmsetex, 334);
            hash_multiset_insert(pt_hmsetex, 5);
            hash_multiset_insert(pt_hmsetex, -76);
            hash_multiset_insert(pt_hmset2, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 4);
            hash_multiset_insert(pt_hmsetex, -4);
            hash_multiset_insert(pt_hmset2, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 4444);
            hash_multiset_insert(pt_hmsetex, -98);
            hash_multiset_insert(pt_hmsetex, 2222);
            hash_multiset_insert(pt_hmsetex, 1);
            hash_multiset_insert(pt_hmsetex, 3);
            hash_multiset_insert(pt_hmsetex, 55);
            hash_multiset_insert(pt_hmset2, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 4);
            hash_multiset_insert(pt_hmsetex, 23844);
            hash_multiset_insert(pt_hmsetex, 2);
            hash_multiset_insert(pt_hmsetex, 4444);
            hash_multiset_insert(pt_hmsetex, 67);
            hash_multiset_insert(pt_hmsetex, 5098);
            hash_multiset_insert(pt_hmsetex, 1);
            hash_multiset_insert(pt_hmsetex, 2);
            hash_multiset_insert(pt_hmsetex, 43);
            hash_multiset_insert(pt_hmset2, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 8);
            hash_multiset_insert(pt_hmsetex, 2);
            hash_multiset_insert(pt_hmsetex, 5);
            hash_multiset_insert(pt_hmsetex, 9);
            hash_multiset_insert(pt_hmsetex, 4);
            hash_multiset_insert(pt_hmsetex, 1);
            hash_multiset_insert(pt_hmsetex, 6);
            hash_multiset_insert(pt_hmsetex, 7);
            hash_multiset_insert(pt_hmsetex, 3);
            hash_multiset_insert(pt_hmsetex, 0);
            hash_multiset_insert(pt_hmset2, pt_hmsetex);
            _print_hash_multiset_cstl(pt_hmset2);

            hash_multiset_insert_range(pt_hmset1, hash_multiset_begin(pt_hmset2), hash_multiset_begin(pt_hmset2));
            _print_hash_multiset_cstl(pt_hmset1);
            hash_multiset_insert_range(pt_hmset1, hash_multiset_begin(pt_hmset2), iterator_advance(hash_multiset_begin(pt_hmset2), 2));
            _print_hash_multiset_cstl(pt_hmset1);
            hash_multiset_insert_range(pt_hmset1, iterator_advance(hash_multiset_begin(pt_hmset2), 3), iterator_advance(hash_multiset_begin(pt_hmset2), 4));
            _print_hash_multiset_cstl(pt_hmset1);
            hash_multiset_insert_range(pt_hmset1, iterator_advance(hash_multiset_begin(pt_hmset2), 5), hash_multiset_end(pt_hmset2));
            _print_hash_multiset_cstl(pt_hmset1);
            hash_multiset_insert_range(pt_hmset1, hash_multiset_end(pt_hmset2), hash_multiset_end(pt_hmset2));
            _print_hash_multiset_cstl(pt_hmset1);

            hash_multiset_clear(pt_hmset1);
            hash_multiset_insert_range(pt_hmset1, hash_multiset_begin(pt_hmset2), hash_multiset_end(pt_hmset2));
            _print_hash_multiset_cstl(pt_hmset1);

            hash_multiset_destroy(pt_hmsetex);
            hash_multiset_destroy(pt_hmset1);
            hash_multiset_destroy(pt_hmset2);
        }
        /*hash_multiset_erase             */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(hash_multiset_t<int>);
            hash_multiset_t* pt_hmsetex = create_hash_multiset(int);
            if(pt_hmset == NULL || pt_hmsetex == NULL)
            {
                return;
            }
            hash_multiset_init_ex(pt_hmset, 50, _hash_multiset_cstl_hash, NULL);
            hash_multiset_init(pt_hmsetex);
            _print_hash_multiset_cstl(pt_hmset);
            hash_multiset_erase(pt_hmset, pt_hmsetex);

            hash_multiset_insert(pt_hmsetex, 12239);
            hash_multiset_insert(pt_hmsetex, 20);
            hash_multiset_insert(pt_hmsetex, -847);
            hash_multiset_insert(pt_hmsetex, 0);
            hash_multiset_insert(pt_hmsetex, 44);
            hash_multiset_insert(pt_hmsetex, 99);
            hash_multiset_insert(pt_hmset, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, -74);
            hash_multiset_insert(pt_hmsetex, 2233);
            hash_multiset_insert(pt_hmsetex, 90);
            hash_multiset_insert(pt_hmsetex, 4);
            hash_multiset_insert(pt_hmsetex, 334);
            hash_multiset_insert(pt_hmsetex, 5);
            hash_multiset_insert(pt_hmsetex, -76);
            hash_multiset_insert(pt_hmset, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 4);
            hash_multiset_insert(pt_hmsetex, -4);
            hash_multiset_insert(pt_hmset, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 4444);
            hash_multiset_insert(pt_hmsetex, -98);
            hash_multiset_insert(pt_hmsetex, 2222);
            hash_multiset_insert(pt_hmsetex, 1);
            hash_multiset_insert(pt_hmsetex, 3);
            hash_multiset_insert(pt_hmsetex, 55);
            hash_multiset_insert(pt_hmset, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 4);
            hash_multiset_insert(pt_hmsetex, 23844);
            hash_multiset_insert(pt_hmsetex, 2);
            hash_multiset_insert(pt_hmsetex, 4444);
            hash_multiset_insert(pt_hmsetex, 67);
            hash_multiset_insert(pt_hmsetex, 5098);
            hash_multiset_insert(pt_hmsetex, 1);
            hash_multiset_insert(pt_hmsetex, 2);
            hash_multiset_insert(pt_hmsetex, 43);
            hash_multiset_insert(pt_hmset, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 8);
            hash_multiset_insert(pt_hmsetex, 2);
            hash_multiset_insert(pt_hmsetex, 5);
            hash_multiset_insert(pt_hmsetex, 9);
            hash_multiset_insert(pt_hmsetex, 4);
            hash_multiset_insert(pt_hmsetex, 1);
            hash_multiset_insert(pt_hmsetex, 6);
            hash_multiset_insert(pt_hmsetex, 7);
            hash_multiset_insert(pt_hmsetex, 3);
            hash_multiset_insert(pt_hmsetex, 0);
            hash_multiset_insert(pt_hmset, pt_hmsetex);
            _print_hash_multiset_cstl(pt_hmset);

            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 4444);
            hash_multiset_insert(pt_hmsetex, -98);
            hash_multiset_insert(pt_hmsetex, 3);
            hash_multiset_insert(pt_hmsetex, 55);
            hash_multiset_erase(pt_hmset, pt_hmsetex);
            _print_hash_multiset_cstl(pt_hmset);

            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 4444);
            hash_multiset_insert(pt_hmsetex, -98);
            hash_multiset_insert(pt_hmsetex, 2222);
            hash_multiset_insert(pt_hmsetex, 1);
            hash_multiset_insert(pt_hmsetex, 3);
            hash_multiset_insert(pt_hmsetex, 55);
            hash_multiset_erase(pt_hmset, pt_hmsetex);
            _print_hash_multiset_cstl(pt_hmset);

            hash_multiset_destroy(pt_hmset);
            hash_multiset_destroy(pt_hmsetex);
        }
        /*hash_multiset_erase_pos         */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(hash_multiset_t<int>);
            hash_multiset_t* pt_hmsetex = create_hash_multiset(int);
            if(pt_hmset == NULL || pt_hmsetex == NULL)
            {
                return;
            }
            hash_multiset_init_ex(pt_hmset, 50, _hash_multiset_cstl_hash, NULL);
            hash_multiset_init(pt_hmsetex);

            hash_multiset_insert(pt_hmsetex, 12239);
            hash_multiset_insert(pt_hmsetex, 20);
            hash_multiset_insert(pt_hmsetex, -847);
            hash_multiset_insert(pt_hmsetex, 0);
            hash_multiset_insert(pt_hmsetex, 44);
            hash_multiset_insert(pt_hmsetex, 99);
            hash_multiset_insert(pt_hmset, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, -74);
            hash_multiset_insert(pt_hmsetex, 2233);
            hash_multiset_insert(pt_hmsetex, 90);
            hash_multiset_insert(pt_hmsetex, 4);
            hash_multiset_insert(pt_hmsetex, 334);
            hash_multiset_insert(pt_hmsetex, 5);
            hash_multiset_insert(pt_hmsetex, -76);
            hash_multiset_insert(pt_hmset, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 4);
            hash_multiset_insert(pt_hmsetex, -4);
            hash_multiset_insert(pt_hmset, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 4444);
            hash_multiset_insert(pt_hmsetex, -98);
            hash_multiset_insert(pt_hmsetex, 2222);
            hash_multiset_insert(pt_hmsetex, 1);
            hash_multiset_insert(pt_hmsetex, 3);
            hash_multiset_insert(pt_hmsetex, 55);
            hash_multiset_insert(pt_hmset, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 4);
            hash_multiset_insert(pt_hmsetex, 23844);
            hash_multiset_insert(pt_hmsetex, 2);
            hash_multiset_insert(pt_hmsetex, 4444);
            hash_multiset_insert(pt_hmsetex, 67);
            hash_multiset_insert(pt_hmsetex, 5098);
            hash_multiset_insert(pt_hmsetex, 1);
            hash_multiset_insert(pt_hmsetex, 2);
            hash_multiset_insert(pt_hmsetex, 43);
            hash_multiset_insert(pt_hmset, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 8);
            hash_multiset_insert(pt_hmsetex, 2);
            hash_multiset_insert(pt_hmsetex, 5);
            hash_multiset_insert(pt_hmsetex, 9);
            hash_multiset_insert(pt_hmsetex, 4);
            hash_multiset_insert(pt_hmsetex, 1);
            hash_multiset_insert(pt_hmsetex, 6);
            hash_multiset_insert(pt_hmsetex, 7);
            hash_multiset_insert(pt_hmsetex, 3);
            hash_multiset_insert(pt_hmsetex, 0);
            hash_multiset_insert(pt_hmset, pt_hmsetex);
            _print_hash_multiset_cstl(pt_hmset);

            hash_multiset_erase_pos(pt_hmset, hash_multiset_begin(pt_hmset));
            _print_hash_multiset_cstl(pt_hmset);
            hash_multiset_erase_pos(pt_hmset, iterator_advance(hash_multiset_begin(pt_hmset), 2));
            _print_hash_multiset_cstl(pt_hmset);
            while(!hash_multiset_empty(pt_hmset))
            {
                hash_multiset_erase_pos(pt_hmset, hash_multiset_begin(pt_hmset));
            }
            _print_hash_multiset_cstl(pt_hmset);

            hash_multiset_destroy(pt_hmset);
            hash_multiset_destroy(pt_hmsetex);
        }
        /*hash_multiset_erase_range       */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(hash_multiset_t<int>);
            hash_multiset_t* pt_hmsetex = create_hash_multiset(int);
            if(pt_hmset == NULL || pt_hmsetex == NULL)
            {
                return;
            }
            hash_multiset_init_ex(pt_hmset, 50, _hash_multiset_cstl_hash, NULL);
            hash_multiset_init(pt_hmsetex);
            hash_multiset_erase_range(pt_hmset, hash_multiset_begin(pt_hmset), hash_multiset_end(pt_hmset));
            _print_hash_multiset_cstl(pt_hmset);

            hash_multiset_insert(pt_hmsetex, 12239);
            hash_multiset_insert(pt_hmsetex, 20);
            hash_multiset_insert(pt_hmsetex, -847);
            hash_multiset_insert(pt_hmsetex, 0);
            hash_multiset_insert(pt_hmsetex, 44);
            hash_multiset_insert(pt_hmsetex, 99);
            hash_multiset_insert(pt_hmset, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, -74);
            hash_multiset_insert(pt_hmsetex, 2233);
            hash_multiset_insert(pt_hmsetex, 90);
            hash_multiset_insert(pt_hmsetex, 4);
            hash_multiset_insert(pt_hmsetex, 334);
            hash_multiset_insert(pt_hmsetex, 5);
            hash_multiset_insert(pt_hmsetex, -76);
            hash_multiset_insert(pt_hmset, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 4);
            hash_multiset_insert(pt_hmsetex, -4);
            hash_multiset_insert(pt_hmset, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 4444);
            hash_multiset_insert(pt_hmsetex, -98);
            hash_multiset_insert(pt_hmsetex, 2222);
            hash_multiset_insert(pt_hmsetex, 1);
            hash_multiset_insert(pt_hmsetex, 3);
            hash_multiset_insert(pt_hmsetex, 55);
            hash_multiset_insert(pt_hmset, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 4);
            hash_multiset_insert(pt_hmsetex, 23844);
            hash_multiset_insert(pt_hmsetex, 2);
            hash_multiset_insert(pt_hmsetex, 4444);
            hash_multiset_insert(pt_hmsetex, 67);
            hash_multiset_insert(pt_hmsetex, 5098);
            hash_multiset_insert(pt_hmsetex, 1);
            hash_multiset_insert(pt_hmsetex, 2);
            hash_multiset_insert(pt_hmsetex, 43);
            hash_multiset_insert(pt_hmset, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 8);
            hash_multiset_insert(pt_hmsetex, 2);
            hash_multiset_insert(pt_hmsetex, 5);
            hash_multiset_insert(pt_hmsetex, 9);
            hash_multiset_insert(pt_hmsetex, 4);
            hash_multiset_insert(pt_hmsetex, 1);
            hash_multiset_insert(pt_hmsetex, 6);
            hash_multiset_insert(pt_hmsetex, 7);
            hash_multiset_insert(pt_hmsetex, 3);
            hash_multiset_insert(pt_hmsetex, 0);
            hash_multiset_insert(pt_hmset, pt_hmsetex);
            _print_hash_multiset_cstl(pt_hmset);

            hash_multiset_erase_range(pt_hmset, hash_multiset_begin(pt_hmset), hash_multiset_begin(pt_hmset));
            _print_hash_multiset_cstl(pt_hmset);
            hash_multiset_erase_range(pt_hmset, hash_multiset_begin(pt_hmset), iterator_advance(hash_multiset_begin(pt_hmset), 2));
            _print_hash_multiset_cstl(pt_hmset);
            hash_multiset_erase_range(pt_hmset, iterator_next(hash_multiset_begin(pt_hmset)), iterator_advance(hash_multiset_begin(pt_hmset), 2));
            _print_hash_multiset_cstl(pt_hmset);
            hash_multiset_erase_range(pt_hmset, iterator_next(hash_multiset_begin(pt_hmset)), hash_multiset_end(pt_hmset));
            _print_hash_multiset_cstl(pt_hmset);
            hash_multiset_erase_range(pt_hmset, hash_multiset_end(pt_hmset), hash_multiset_end(pt_hmset));
            _print_hash_multiset_cstl(pt_hmset);
            hash_multiset_erase_range(pt_hmset, hash_multiset_begin(pt_hmset), hash_multiset_end(pt_hmset));
            _print_hash_multiset_cstl(pt_hmset);

            hash_multiset_destroy(pt_hmset);
            hash_multiset_destroy(pt_hmsetex);
        }
        /*hash_multiset_clear             */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(hash_multiset_t<int>);
            hash_multiset_t* pt_hmsetex = create_hash_multiset(int);
            if(pt_hmset == NULL || pt_hmsetex == NULL)
            {
                return;
            }
            hash_multiset_init_ex(pt_hmset, 50, _hash_multiset_cstl_hash, NULL);
            hash_multiset_init(pt_hmsetex);

            hash_multiset_clear(pt_hmset);
            _print_hash_multiset_cstl(pt_hmset);

            hash_multiset_insert(pt_hmsetex, 12239);
            hash_multiset_insert(pt_hmsetex, 20);
            hash_multiset_insert(pt_hmsetex, -847);
            hash_multiset_insert(pt_hmsetex, 0);
            hash_multiset_insert(pt_hmsetex, 44);
            hash_multiset_insert(pt_hmsetex, 99);
            hash_multiset_insert(pt_hmset, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, -74);
            hash_multiset_insert(pt_hmsetex, 2233);
            hash_multiset_insert(pt_hmsetex, 90);
            hash_multiset_insert(pt_hmsetex, 4);
            hash_multiset_insert(pt_hmsetex, 334);
            hash_multiset_insert(pt_hmsetex, 5);
            hash_multiset_insert(pt_hmsetex, -76);
            hash_multiset_insert(pt_hmset, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 4);
            hash_multiset_insert(pt_hmsetex, -4);
            hash_multiset_insert(pt_hmset, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 4444);
            hash_multiset_insert(pt_hmsetex, -98);
            hash_multiset_insert(pt_hmsetex, 2222);
            hash_multiset_insert(pt_hmsetex, 1);
            hash_multiset_insert(pt_hmsetex, 3);
            hash_multiset_insert(pt_hmsetex, 55);
            hash_multiset_insert(pt_hmset, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 4);
            hash_multiset_insert(pt_hmsetex, 23844);
            hash_multiset_insert(pt_hmsetex, 2);
            hash_multiset_insert(pt_hmsetex, 4444);
            hash_multiset_insert(pt_hmsetex, 67);
            hash_multiset_insert(pt_hmsetex, 5098);
            hash_multiset_insert(pt_hmsetex, 1);
            hash_multiset_insert(pt_hmsetex, 2);
            hash_multiset_insert(pt_hmsetex, 43);
            hash_multiset_insert(pt_hmset, pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, 8);
            hash_multiset_insert(pt_hmsetex, 2);
            hash_multiset_insert(pt_hmsetex, 5);
            hash_multiset_insert(pt_hmsetex, 9);
            hash_multiset_insert(pt_hmsetex, 4);
            hash_multiset_insert(pt_hmsetex, 1);
            hash_multiset_insert(pt_hmsetex, 6);
            hash_multiset_insert(pt_hmsetex, 7);
            hash_multiset_insert(pt_hmsetex, 3);
            hash_multiset_insert(pt_hmsetex, 0);
            hash_multiset_insert(pt_hmset, pt_hmsetex);
            _print_hash_multiset_cstl(pt_hmset);

            hash_multiset_clear(pt_hmset);
            _print_hash_multiset_cstl(pt_hmset);

            hash_multiset_destroy(pt_hmset);
            hash_multiset_destroy(pt_hmsetex);
        }
    }
    /* c-string type */
    {
        /*create_hash_multiset            */
        /*hash_multiset_init              */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(char*);
            if(pt_hmset == NULL)
            {
                return;
            }
            hash_multiset_init(pt_hmset);
            hash_multiset_insert(pt_hmset, "abcdefg");
            hash_multiset_insert(pt_hmset, "ooooooooooooooooo");
            hash_multiset_insert(pt_hmset, "hhhhkadfoqwbn");
            hash_multiset_insert(pt_hmset, "12124120");
            _print_hash_multiset_cstr(pt_hmset);
            hash_multiset_destroy(pt_hmset);
        }
        /*hash_multiset_init_ex           */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(char*);
            if(pt_hmset == NULL)
            {
                return;
            }
            hash_multiset_init_ex(pt_hmset, 50, _hash_multiset_cstr_hash, NULL);
            hash_multiset_insert(pt_hmset, "999");
            hash_multiset_insert(pt_hmset, "7");
            hash_multiset_insert(pt_hmset, "bbaklsf");
            hash_multiset_insert(pt_hmset, "bbaklsf");
            hash_multiset_insert(pt_hmset, "bbaklsf");
            hash_multiset_insert(pt_hmset, "1111111111111");
            hash_multiset_insert(pt_hmset, "yyy");
            _print_hash_multiset_cstr(pt_hmset);
            hash_multiset_destroy(pt_hmset);
        }
        /*hash_multiset_init_copy         */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(char*);
            hash_multiset_t* pt_hmsetex = create_hash_multiset(char*);
            if(pt_hmset == NULL || pt_hmsetex == NULL)
            {
                return;
            }
            hash_multiset_init_ex(pt_hmsetex, 100, _hash_multiset_cstr_hash, NULL);
            hash_multiset_insert(pt_hmsetex, "bbbb");
            hash_multiset_insert(pt_hmsetex, "99999999");
            hash_multiset_insert(pt_hmsetex, "99999999");
            hash_multiset_insert(pt_hmsetex, "99999999");
            hash_multiset_insert(pt_hmsetex, "99999999");
            hash_multiset_insert(pt_hmsetex, "");
            hash_multiset_insert(pt_hmsetex, "vv");
            hash_multiset_insert(pt_hmsetex, "vv");
            hash_multiset_insert(pt_hmsetex, "nnn");
            hash_multiset_insert(pt_hmsetex, ".,._t_hashtable,");
            hash_multiset_init_copy(pt_hmset, pt_hmsetex);
            _print_hash_multiset_cstr(pt_hmset);
            hash_multiset_destroy(pt_hmsetex);
            hash_multiset_destroy(pt_hmset);
        }
        /*hash_multiset_init_copy_range   */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(char*);
            hash_multiset_t* pt_hmsetex = create_hash_multiset(char*);
            if(pt_hmset == NULL || pt_hmsetex == NULL)
            {
                return;
            }
            hash_multiset_init_ex(pt_hmsetex, 100, _hash_multiset_cstr_hash, _hash_multiset_cstr_less);
            hash_multiset_insert(pt_hmsetex, "abcdefghijklmn");
            hash_multiset_insert(pt_hmsetex, "00000000");
            hash_multiset_insert(pt_hmsetex, "uu");
            hash_multiset_insert(pt_hmsetex, "abcdefghijklmn");
            hash_multiset_insert(pt_hmsetex, "abcdefghijklmn");
            hash_multiset_insert(pt_hmsetex, "abcdefghijklmn");
            hash_multiset_insert(pt_hmsetex, "94lebgqoi34asdh;adfasd");
            hash_multiset_insert(pt_hmsetex, "787878");
            hash_multiset_insert(pt_hmsetex, "444444");
            hash_multiset_insert(pt_hmsetex, "444444");
            hash_multiset_insert(pt_hmsetex, "4902u30230");
            hash_multiset_insert(pt_hmsetex, "tta");
            hash_multiset_init_copy_range(pt_hmset,
                hash_multiset_end(pt_hmsetex),
                hash_multiset_end(pt_hmsetex));
            _print_hash_multiset_cstr(pt_hmsetex);
            _print_hash_multiset_cstr(pt_hmset);
            hash_multiset_destroy(pt_hmset);
            hash_multiset_destroy(pt_hmsetex);
        }
        /*hash_multiset_init_copy_range_ex*/
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(char*);
            hash_multiset_t* pt_hmsetex = create_hash_multiset(char*);
            if(pt_hmset == NULL || pt_hmsetex == NULL)
            {
                return;
            }
            hash_multiset_init(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, "abcdefghijklmn");
            hash_multiset_insert(pt_hmsetex, "00000000");
            hash_multiset_insert(pt_hmsetex, "00000000");
            hash_multiset_insert(pt_hmsetex, "00000000");
            hash_multiset_insert(pt_hmsetex, "uu");
            hash_multiset_insert(pt_hmsetex, "abcdefghijklmn");
            hash_multiset_insert(pt_hmsetex, "94lebgqoi34asdh;adfasd");
            hash_multiset_insert(pt_hmsetex, "787878");
            hash_multiset_insert(pt_hmsetex, "444444");
            hash_multiset_insert(pt_hmsetex, "4902u30230");
            hash_multiset_insert(pt_hmsetex, "tta");
            hash_multiset_init_copy_range_ex(pt_hmset,
                hash_multiset_begin(pt_hmsetex),
                hash_multiset_end(pt_hmsetex),
                100, _hash_multiset_cstr_hash, _hash_multiset_cstr_less);
            _print_hash_multiset_cstr(pt_hmsetex);
            _print_hash_multiset_cstr(pt_hmset);
            hash_multiset_destroy(pt_hmset);
            hash_multiset_destroy(pt_hmsetex);
        }
        /*hash_multiset_destroy           */
        /*hash_multiset_assign            */
        /*hash_multiset_swap              */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(char*);
            hash_multiset_t* pt_hmsetex = create_hash_multiset(char*);
            if(pt_hmset == NULL || pt_hmsetex == NULL)
            {
                return;
            }
            hash_multiset_init_ex(pt_hmsetex, 50, _hash_multiset_cstr_hash, NULL);
            hash_multiset_init_ex(pt_hmset, 50, _hash_multiset_cstr_hash, NULL);
            hash_multiset_swap(pt_hmset, pt_hmsetex);
            _print_hash_multiset_cstr(pt_hmset);
            _print_hash_multiset_cstr(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, "abcdefghijklmn");
            hash_multiset_insert(pt_hmsetex, "00000000");
            hash_multiset_insert(pt_hmsetex, "uu");
            hash_multiset_swap(pt_hmset, pt_hmsetex);
            _print_hash_multiset_cstr(pt_hmset);
            _print_hash_multiset_cstr(pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, "abcdefghijklmn");
            hash_multiset_insert(pt_hmsetex, "94lebgqoi34asdh;adfasd");
            hash_multiset_insert(pt_hmsetex, "787878");
            hash_multiset_insert(pt_hmsetex, "444444");
            hash_multiset_insert(pt_hmsetex, "4902u30230");
            hash_multiset_insert(pt_hmsetex, "tta");
            hash_multiset_insert(pt_hmsetex, "444444");
            hash_multiset_swap(pt_hmset, pt_hmsetex);
            _print_hash_multiset_cstr(pt_hmset);
            _print_hash_multiset_cstr(pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_insert(pt_hmsetex, "66666");
            hash_multiset_insert(pt_hmsetex, "al;dhiqwegfbfgoqwehfodghf");
            hash_multiset_swap(pt_hmset, pt_hmsetex);
            _print_hash_multiset_cstr(pt_hmset);
            _print_hash_multiset_cstr(pt_hmsetex);
            hash_multiset_clear(pt_hmsetex);
            hash_multiset_swap(pt_hmset, pt_hmsetex);
            _print_hash_multiset_cstr(pt_hmset);
            _print_hash_multiset_cstr(pt_hmsetex);
            hash_multiset_destroy(pt_hmset);
            hash_multiset_destroy(pt_hmsetex);
        }
        /*hash_multiset_size              */
        /*hash_multiset_empty             */
        /*hash_multiset_max_size          */
        /*hash_multiset_bucket_count      */
        /*hash_multiset_hash              */
        /*hash_multiset_key_less          */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(char*);
            if(pt_hmset == NULL)
            {
                return;
            }
            hash_multiset_init_ex(pt_hmset, 100, _hash_multiset_cstr_hash, _hash_multiset_cstr_less);
            assert(hash_multiset_hash(pt_hmset) == _hash_multiset_cstr_hash &&
                hash_multiset_key_less(pt_hmset) == _hash_multiset_cstr_less);
            hash_multiset_destroy(pt_hmset);
        }
        /*hash_multiset_resize            */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(char*);
            if(pt_hmset == NULL)
            {
                return;
            }
            hash_multiset_init(pt_hmset);
            _print_hash_multiset_cstr(pt_hmset);
            hash_multiset_resize(pt_hmset, 100);
            _print_hash_multiset_cstr(pt_hmset);
            hash_multiset_resize(pt_hmset, 400);
            _print_hash_multiset_cstr(pt_hmset);
            hash_multiset_resize(pt_hmset, 10);
            _print_hash_multiset_cstr(pt_hmset);
            hash_multiset_resize(pt_hmset, 0);
            _print_hash_multiset_cstr(pt_hmset);
            hash_multiset_destroy(pt_hmset);
        }
        /*hash_multiset_equal             */
        /*hash_multiset_not_equal         */
        /*hash_multiset_less              */
        /*hash_multiset_less_equal        */
        /*hash_multiset_great             */
        /*hash_multiset_great_equal       */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(char*);
            hash_multiset_t* pt_hmsetex = create_hash_multiset(char*);
            if(pt_hmset == NULL || pt_hmsetex == NULL)
            {
                return;
            }
            hash_multiset_init_ex(pt_hmset, 100, _hash_multiset_cstr_hash, NULL);
            hash_multiset_init_ex(pt_hmsetex, 100, _hash_multiset_cstr_hash, NULL);
            _print_hash_multiset_cstr(pt_hmset);
            _print_hash_multiset_cstr(pt_hmsetex);
            printf("equal: %d, not equal: %d, ",
                hash_multiset_equal(pt_hmset, pt_hmsetex), hash_multiset_not_equal(pt_hmset, pt_hmsetex));
            printf("less: %d, less equal: %d, ",
                hash_multiset_less(pt_hmset, pt_hmsetex), hash_multiset_less_equal(pt_hmset, pt_hmsetex));
            printf("great: %d, great equal: %d\n",
                hash_multiset_great(pt_hmset, pt_hmsetex), hash_multiset_great_equal(pt_hmset, pt_hmsetex));

            hash_multiset_insert(pt_hmset, "ynuopqdasdgq");
            _print_hash_multiset_cstr(pt_hmset);
            _print_hash_multiset_cstr(pt_hmsetex);
            printf("equal: %d, not equal: %d, ",
                hash_multiset_equal(pt_hmset, pt_hmsetex), hash_multiset_not_equal(pt_hmset, pt_hmsetex));
            printf("less: %d, less equal: %d, ",
                hash_multiset_less(pt_hmset, pt_hmsetex), hash_multiset_less_equal(pt_hmset, pt_hmsetex));
            printf("great: %d, great equal: %d\n",
                hash_multiset_great(pt_hmset, pt_hmsetex), hash_multiset_great_equal(pt_hmset, pt_hmsetex));

            hash_multiset_insert(pt_hmsetex, "ynuopqdasdgq");
            _print_hash_multiset_cstr(pt_hmset);
            _print_hash_multiset_cstr(pt_hmsetex);
            printf("equal: %d, not equal: %d, ",
                hash_multiset_equal(pt_hmset, pt_hmsetex), hash_multiset_not_equal(pt_hmset, pt_hmsetex));
            printf("less: %d, less equal: %d, ",
                hash_multiset_less(pt_hmset, pt_hmsetex), hash_multiset_less_equal(pt_hmset, pt_hmsetex));
            printf("great: %d, great equal: %d\n",
                hash_multiset_great(pt_hmset, pt_hmsetex), hash_multiset_great_equal(pt_hmset, pt_hmsetex));

            hash_multiset_insert(pt_hmset, "ynuop");
            hash_multiset_insert(pt_hmset, "vvvvvvvv");
            hash_multiset_insert(pt_hmset, "bbbbbb");
            hash_multiset_insert(pt_hmsetex, "ynuopqdasdgqxxxxxxx");
            _print_hash_multiset_cstr(pt_hmset);
            _print_hash_multiset_cstr(pt_hmsetex);
            printf("equal: %d, not equal: %d, ",
                hash_multiset_equal(pt_hmset, pt_hmsetex), hash_multiset_not_equal(pt_hmset, pt_hmsetex));
            printf("less: %d, less equal: %d, ",
                hash_multiset_less(pt_hmset, pt_hmsetex), hash_multiset_less_equal(pt_hmset, pt_hmsetex));
            printf("great: %d, great equal: %d\n",
                hash_multiset_great(pt_hmset, pt_hmsetex), hash_multiset_great_equal(pt_hmset, pt_hmsetex));

            hash_multiset_destroy(pt_hmset);
            hash_multiset_destroy(pt_hmsetex);
        }
        /*hash_multiset_begin             */
        /*hash_multiset_end               */
        /*hash_multiset_find              */
        /*hash_multiset_count             */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(char*);
            iterator_t t_iter;
            if(pt_hmset == NULL)
            {
                return;
            }
            hash_multiset_init_ex(pt_hmset, 10, _hash_multiset_cstr_hash, NULL);
            t_iter = hash_multiset_find(pt_hmset, "abcdefg");
            if(iterator_equal(t_iter, hash_multiset_end(pt_hmset)))
            {
                printf("not found, count : %d\n", hash_multiset_count(pt_hmset, "abcdefg"));
            }
            else
            {
                printf("found, count : %d\n", hash_multiset_count(pt_hmset, "abcdefg"));
            }

            hash_multiset_insert(pt_hmset, "rtrtrtm");
            hash_multiset_insert(pt_hmset, "bvn");
            hash_multiset_insert(pt_hmset, "abcdefg");
            hash_multiset_insert(pt_hmset, "abcdefg");
            hash_multiset_insert(pt_hmset, "abcdefg");
            hash_multiset_insert(pt_hmset, ",._t_hashtable,._t_.,.,..,.,.,");
            hash_multiset_insert(pt_hmset, "vvv");
            _print_hash_multiset_cstr(pt_hmset);

            t_iter = hash_multiset_find(pt_hmset, "mmmmmm");
            if(iterator_equal(t_iter, hash_multiset_end(pt_hmset)))
            {
                printf("not found, count : %d\n", hash_multiset_count(pt_hmset, "mmmmmm"));
            }
            else
            {
                printf("found, count : %d\n", hash_multiset_count(pt_hmset, "mmmmmm"));
            }
            t_iter = hash_multiset_find(pt_hmset, "abcdefg");
            if(iterator_equal(t_iter, hash_multiset_end(pt_hmset)))
            {
                printf("not found, count : %d\n", hash_multiset_count(pt_hmset, "abcdefg"));
            }
            else
            {
                printf("found, count : %d\n", hash_multiset_count(pt_hmset, "abcdefg"));
            }

            hash_multiset_destroy(pt_hmset);
        }
        /*hash_multiset_equal_range       */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(char*);
            range_t t_range;
            if(pt_hmset == NULL)
            {
                return;
            }
            hash_multiset_init_ex(pt_hmset, 10, _hash_multiset_cstr_hash, NULL);
            t_range = hash_multiset_equal_range(pt_hmset, "abcdefg");
            assert(iterator_equal(t_range.t_begin, hash_multiset_end(pt_hmset)) &&
                iterator_equal(t_range.t_begin, t_range.t_end));
            hash_multiset_insert(pt_hmset, "lskdj");
            hash_multiset_insert(pt_hmset, "bbbbbbbbb");
            hash_multiset_insert(pt_hmset, "abcdefg");
            hash_multiset_insert(pt_hmset, "nmnm");
            hash_multiset_insert(pt_hmset, "mmmm");
            _print_hash_multiset_cstr(pt_hmset);
            t_range = hash_multiset_equal_range(pt_hmset, "opqrst");
            assert(iterator_equal(t_range.t_begin, t_range.t_end));
            t_range = hash_multiset_equal_range(pt_hmset, "abcdefg");
            assert(iterator_equal(iterator_next(t_range.t_begin), t_range.t_end));
            hash_multiset_destroy(pt_hmset);
        }
        /*hash_multiset_insert            */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(char*);
            if(pt_hmset == NULL)
            {
                return;
            }
            hash_multiset_init_ex(pt_hmset, 45, _hash_multiset_cstr_hash, NULL);
            _print_hash_multiset_cstr(pt_hmset);
            hash_multiset_insert(pt_hmset, "45454545");
            hash_multiset_insert(pt_hmset, "00000");
            hash_multiset_insert(pt_hmset, "124!@##@");
            hash_multiset_insert(pt_hmset, "%^&*");
            _print_hash_multiset_cstr(pt_hmset);
            hash_multiset_insert(pt_hmset, "00000");
            hash_multiset_insert(pt_hmset, "%^&*");
            hash_multiset_insert(pt_hmset, "--------");
            _print_hash_multiset_cstr(pt_hmset);
            hash_multiset_destroy(pt_hmset);
        }
        /*hash_multiset_insert_range      */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(char*);
            hash_multiset_t* pt_hmsetex = create_hash_multiset(char*);
            if(pt_hmset == NULL || pt_hmsetex == NULL)
            {
                return;
            }
            hash_multiset_init_ex(pt_hmset, 100, _hash_multiset_cstr_hash, NULL);
            hash_multiset_init(pt_hmsetex);
            hash_multiset_insert_range(pt_hmset, hash_multiset_begin(pt_hmsetex), hash_multiset_end(pt_hmsetex));
            _print_hash_multiset_cstr(pt_hmset);

            hash_multiset_insert(pt_hmsetex, "xcvbnm");
            hash_multiset_insert(pt_hmsetex, "<><><><><><>");
            hash_multiset_insert(pt_hmsetex, "cccc");
            hash_multiset_insert(pt_hmsetex, "@@@@@@@@");
            hash_multiset_insert(pt_hmsetex, "@@@@@@@@");
            hash_multiset_insert(pt_hmsetex, "()()");
            hash_multiset_insert(pt_hmsetex, "help");
            hash_multiset_insert(pt_hmsetex, "me!!!!!!!!!!!!!!");
            hash_multiset_insert(pt_hmsetex, "++++");
            hash_multiset_insert(pt_hmsetex, "76894");
            hash_multiset_insert(pt_hmsetex, "bfqweoihabgasodifjw");
            hash_multiset_insert(pt_hmsetex, "aaaaaaaa");
            hash_multiset_insert(pt_hmsetex, "{}{}{}{}{}{");
            hash_multiset_insert(pt_hmsetex, "########");
            hash_multiset_insert(pt_hmsetex, "%%%%%%%%%%%%%%");
            hash_multiset_insert(pt_hmsetex, "$$$$$$$$$$$$$$");
            hash_multiset_insert(pt_hmsetex, "!!!!!!!!!!");
            _print_hash_multiset_cstr(pt_hmsetex);

            hash_multiset_insert_range(pt_hmset, hash_multiset_begin(pt_hmsetex),
                hash_multiset_begin(pt_hmsetex));
            _print_hash_multiset_cstr(pt_hmset);
            hash_multiset_insert_range(pt_hmset, hash_multiset_begin(pt_hmsetex),
                iterator_advance(hash_multiset_begin(pt_hmsetex), 3));
            _print_hash_multiset_cstr(pt_hmset);
            hash_multiset_insert_range(pt_hmset, iterator_advance(hash_multiset_begin(pt_hmsetex), 4),
                iterator_advance(hash_multiset_begin(pt_hmsetex), 6));
            _print_hash_multiset_cstr(pt_hmset);
            hash_multiset_insert_range(pt_hmset, iterator_advance(hash_multiset_begin(pt_hmsetex), 7),
                hash_multiset_end(pt_hmsetex));
            _print_hash_multiset_cstr(pt_hmset);
            hash_multiset_insert_range(pt_hmset, hash_multiset_end(pt_hmsetex), hash_multiset_end(pt_hmsetex));
            _print_hash_multiset_cstr(pt_hmset);
            hash_multiset_clear(pt_hmset);
            hash_multiset_insert_range(pt_hmset, hash_multiset_begin(pt_hmsetex), hash_multiset_end(pt_hmsetex));
            _print_hash_multiset_cstr(pt_hmset);

            hash_multiset_destroy(pt_hmset);
            hash_multiset_destroy(pt_hmsetex);
        }
        /*hash_multiset_erase             */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(char*);
            if(pt_hmset == NULL)
            {
                return;
            }
            hash_multiset_init_ex(pt_hmset, 100, _hash_multiset_cstr_hash, NULL);
            hash_multiset_erase(pt_hmset, "76894");
            _print_hash_multiset_cstr(pt_hmset);

            hash_multiset_insert(pt_hmset, "xcvbnm");
            hash_multiset_insert(pt_hmset, "<><><><><><>");
            hash_multiset_insert(pt_hmset, "cccc");
            hash_multiset_insert(pt_hmset, "@@@@@@@@");
            hash_multiset_insert(pt_hmset, "@@@@@@@@");
            hash_multiset_insert(pt_hmset, "()()");
            hash_multiset_insert(pt_hmset, "help");
            hash_multiset_insert(pt_hmset, "me!!!!!!!!!!!!!!");
            hash_multiset_insert(pt_hmset, "++++");
            hash_multiset_insert(pt_hmset, "76894");
            hash_multiset_insert(pt_hmset, "76894");
            hash_multiset_insert(pt_hmset, "76894");
            hash_multiset_insert(pt_hmset, "76894");
            hash_multiset_insert(pt_hmset, "bfqweoihabgasodifjw");
            hash_multiset_insert(pt_hmset, "aaaaaaaa");
            hash_multiset_insert(pt_hmset, "{}{}{}{}{}{");
            hash_multiset_insert(pt_hmset, "########");
            hash_multiset_insert(pt_hmset, "%%%%%%%%%%%%%%");
            hash_multiset_insert(pt_hmset, "$$$$$$$$$$$$$$");
            hash_multiset_insert(pt_hmset, "!!!!!!!!!!");
            _print_hash_multiset_cstr(pt_hmset);

            hash_multiset_erase(pt_hmset, "mnopq");
            _print_hash_multiset_cstr(pt_hmset);
            hash_multiset_erase(pt_hmset, "76894");
            _print_hash_multiset_cstr(pt_hmset);

            hash_multiset_destroy(pt_hmset);
        }
        /*hash_multiset_erase_pos         */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(char*);
            if(pt_hmset == NULL)
            {
                return;
            }
            hash_multiset_init_ex(pt_hmset, 100, _hash_multiset_cstr_hash, NULL);
            hash_multiset_insert(pt_hmset, "xcvbnm");
            hash_multiset_insert(pt_hmset, "<><><><><><>");
            hash_multiset_insert(pt_hmset, "cccc");
            hash_multiset_insert(pt_hmset, "@@@@@@@@");
            hash_multiset_insert(pt_hmset, "@@@@@@@@");
            hash_multiset_insert(pt_hmset, "()()");
            hash_multiset_insert(pt_hmset, "help");
            hash_multiset_insert(pt_hmset, "me!!!!!!!!!!!!!!");
            hash_multiset_insert(pt_hmset, "++++");
            hash_multiset_insert(pt_hmset, "76894");
            hash_multiset_insert(pt_hmset, "bfqweoihabgasodifjw");
            hash_multiset_insert(pt_hmset, "aaaaaaaa");
            hash_multiset_insert(pt_hmset, "{}{}{}{}{}{");
            hash_multiset_insert(pt_hmset, "########");
            hash_multiset_insert(pt_hmset, "%%%%%%%%%%%%%%");
            hash_multiset_insert(pt_hmset, "$$$$$$$$$$$$$$");
            hash_multiset_insert(pt_hmset, "!!!!!!!!!!");
            _print_hash_multiset_cstr(pt_hmset);

            hash_multiset_erase_pos(pt_hmset, hash_multiset_begin(pt_hmset));
            _print_hash_multiset_cstr(pt_hmset);
            hash_multiset_erase_pos(pt_hmset, iterator_advance(hash_multiset_begin(pt_hmset), 5));
            _print_hash_multiset_cstr(pt_hmset);
            while(!hash_multiset_empty(pt_hmset))
            {
                hash_multiset_erase_pos(pt_hmset, hash_multiset_begin(pt_hmset));
            }
            _print_hash_multiset_cstr(pt_hmset);

            hash_multiset_destroy(pt_hmset);
        }
        /*hash_multiset_erase_range       */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(char*);
            if(pt_hmset == NULL)
            {
                return;
            }
            hash_multiset_init_ex(pt_hmset, 100, _hash_multiset_cstr_hash, NULL);
            hash_multiset_erase_range(pt_hmset, hash_multiset_begin(pt_hmset), hash_multiset_end(pt_hmset));
            _print_hash_multiset_cstr(pt_hmset);
            hash_multiset_insert(pt_hmset, "xcvbnm");
            hash_multiset_insert(pt_hmset, "<><><><><><>");
            hash_multiset_insert(pt_hmset, "cccc");
            hash_multiset_insert(pt_hmset, "@@@@@@@@");
            hash_multiset_insert(pt_hmset, "@@@@@@@@");
            hash_multiset_insert(pt_hmset, "()()");
            hash_multiset_insert(pt_hmset, "help");
            hash_multiset_insert(pt_hmset, "me!!!!!!!!!!!!!!");
            hash_multiset_insert(pt_hmset, "++++");
            hash_multiset_insert(pt_hmset, "76894");
            hash_multiset_insert(pt_hmset, "bfqweoihabgasodifjw");
            hash_multiset_insert(pt_hmset, "aaaaaaaa");
            hash_multiset_insert(pt_hmset, "{}{}{}{}{}{");
            hash_multiset_insert(pt_hmset, "########");
            hash_multiset_insert(pt_hmset, "%%%%%%%%%%%%%%");
            hash_multiset_insert(pt_hmset, "$$$$$$$$$$$$$$");
            hash_multiset_insert(pt_hmset, "!!!!!!!!!!");
            _print_hash_multiset_cstr(pt_hmset);

            hash_multiset_erase_range(pt_hmset, hash_multiset_begin(pt_hmset), hash_multiset_begin(pt_hmset));
            _print_hash_multiset_cstr(pt_hmset);
            hash_multiset_erase_range(pt_hmset, hash_multiset_begin(pt_hmset),
                iterator_advance(hash_multiset_begin(pt_hmset), 3));
            _print_hash_multiset_cstr(pt_hmset);
            hash_multiset_erase_range(pt_hmset, iterator_next(hash_multiset_begin(pt_hmset)),
                iterator_advance(hash_multiset_begin(pt_hmset), 3));
            _print_hash_multiset_cstr(pt_hmset);
            hash_multiset_erase_range(pt_hmset, iterator_advance(hash_multiset_begin(pt_hmset), 4),
                hash_multiset_end(pt_hmset));
            _print_hash_multiset_cstr(pt_hmset);
            hash_multiset_erase_range(pt_hmset, hash_multiset_end(pt_hmset), hash_multiset_end(pt_hmset));
            _print_hash_multiset_cstr(pt_hmset);
            hash_multiset_erase_range(pt_hmset, hash_multiset_begin(pt_hmset), hash_multiset_end(pt_hmset));
            _print_hash_multiset_cstr(pt_hmset);

            hash_multiset_destroy(pt_hmset);
        }
        /*hash_multiset_clear             */
        {
            hash_multiset_t* pt_hmset = create_hash_multiset(char*);
            if(pt_hmset == NULL)
            {
                return;
            }
            hash_multiset_init_ex(pt_hmset, 100, _hash_multiset_cstr_hash, NULL);
            hash_multiset_clear(pt_hmset);
            _print_hash_multiset_cstr(pt_hmset);
            hash_multiset_insert(pt_hmset, "xcvbnm");
            hash_multiset_insert(pt_hmset, "<><><><><><>");
            hash_multiset_insert(pt_hmset, "cccc");
            hash_multiset_insert(pt_hmset, "@@@@@@@@");
            hash_multiset_insert(pt_hmset, "@@@@@@@@");
            hash_multiset_insert(pt_hmset, "()()");
            hash_multiset_insert(pt_hmset, "help");
            hash_multiset_insert(pt_hmset, "me!!!!!!!!!!!!!!");
            hash_multiset_insert(pt_hmset, "++++");
            hash_multiset_insert(pt_hmset, "76894");
            hash_multiset_insert(pt_hmset, "bfqweoihabgasodifjw");
            hash_multiset_insert(pt_hmset, "aaaaaaaa");
            hash_multiset_insert(pt_hmset, "{}{}{}{}{}{");
            hash_multiset_insert(pt_hmset, "########");
            hash_multiset_insert(pt_hmset, "%%%%%%%%%%%%%%");
            hash_multiset_insert(pt_hmset, "$$$$$$$$$$$$$$");
            hash_multiset_insert(pt_hmset, "!!!!!!!!!!");
            _print_hash_multiset_cstr(pt_hmset);
            hash_multiset_clear(pt_hmset);
            _print_hash_multiset_cstr(pt_hmset);

            hash_multiset_destroy(pt_hmset);
        }
    }
}

/** local function implementation section **/

/** eof **/

