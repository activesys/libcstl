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
static void _hash_set_int_hash(const void* cpv_input, void* pv_output);

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

