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
#include "clist.h"
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

#define _ENV_AND_COND_LEN 100

/** local data type declaration and local struct, union, enum section **/
typedef enum _tagunits
{
    _ERR, _B, _KB, _MB
}_units_t;

typedef struct _tagmapkey
{
    unsigned _un_number;
    _units_t _t_unit;
}_mapkey_t;

typedef struct _tagmapvalue
{
    char _s_enviroment[_ENV_AND_COND_LEN];
    char _s_condition[_ENV_AND_COND_LEN];
}_mapvalue_t;

/** local function prototype section **/
static void _mapkey_init(const void* cpv_input, void* pv_output);
static void _mapkey_copy(const void* cpv_first, const void* cpv_second, void* pv_output);
static void _mapkey_less(const void* cpv_first, const void* cpv_second, void* pv_output);
static void _mapkey_destroy(const void* cpv_input, void* pv_output);

static void _mapvalue_init(const void* cpv_input, void* pv_output);
static void _mapvalue_copy(const void* cpv_first, const void* cpv_second, void* pv_output);
static void _mapvalue_less(const void* cpv_first, const void* cpv_second, void* pv_output);
static void _mapvalue_destroy(const void* cpv_input, void* pv_output);

static void _print_map_user(const map_t* cpt_map);
static void _print_map_cstl(const map_t* cpt_map);
static void _mapkey_number_great(const void* cpv_first, const void* cpv_second, void* pv_output);
static void _mapkey_pair_great(const void* cpv_first, const void* cpv_second, void* pv_output);

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
        {
            map_t* pt_map = create_map(char, short);
            map_t* pt_mapex = create_map(signed char, signed short int);
            pair_t* pt_pair = create_pair(char, short int);
            if(pt_map == NULL || pt_mapex == NULL || pt_pair == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            map_init_ex(pt_mapex, fun_great_char);
            pair_make(pt_pair, 'i', 349);
            map_insert(pt_mapex, pt_pair);
            pair_make(pt_pair, '$', 0);
            map_insert(pt_mapex, pt_pair);
            pair_make(pt_pair, 'R', -5);
            map_insert(pt_mapex, pt_pair);
            pair_make(pt_pair, '>', 60);
            map_insert(pt_mapex, pt_pair);
            _print_map_c(pt_mapex, "<key: '%c', value: %d>, ", char, short);
            map_init_copy(pt_map, pt_mapex);
            _print_map_c(pt_map, "<key: '%c', value: %d>, ", char, short);
            pair_destroy(pt_pair);
            map_destroy(pt_map);
            map_destroy(pt_mapex);
        }
        /*map_init_copy_range   */
        {
            map_t* pt_map = create_map(char, short);
            map_t* pt_mapex = create_map(signed char, signed short int);
            pair_t* pt_pair = create_pair(char, short int);
            if(pt_map == NULL || pt_mapex == NULL || pt_pair == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            map_init_ex(pt_mapex, fun_great_char);
            pair_make(pt_pair, 'i', 349);
            map_insert(pt_mapex, pt_pair);
            pair_make(pt_pair, '$', 0);
            map_insert(pt_mapex, pt_pair);
            pair_make(pt_pair, 'R', -5);
            map_insert(pt_mapex, pt_pair);
            pair_make(pt_pair, '>', 60);
            map_insert(pt_mapex, pt_pair);
            pair_make(pt_pair, 'E', 78);
            map_insert(pt_mapex, pt_pair);
            pair_make(pt_pair, '}', -3344);
            map_insert(pt_mapex, pt_pair);
            pair_make(pt_pair, '+', -93);
            map_insert(pt_mapex, pt_pair);
            pair_make(pt_pair, '@', -555);
            map_insert(pt_mapex, pt_pair);
            _print_map_c(pt_mapex, "<key: '%c', value: %d>, ", char, short);
            map_init_copy_range(pt_map, map_begin(pt_mapex), map_end(pt_mapex));
            _print_map_c(pt_map, "<key: '%c', value: %d>, ", char, short);
            pair_destroy(pt_pair);
            map_destroy(pt_map);
            map_destroy(pt_mapex);
        }
        /*map_init_copy_range_ex*/
        {
            map_t* pt_map = create_map(char, short);
            map_t* pt_mapex = create_map(signed char, signed short int);
            pair_t* pt_pair = create_pair(char, short int);
            if(pt_map == NULL || pt_mapex == NULL || pt_pair == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            map_init(pt_mapex);
            pair_make(pt_pair, 'i', 349);
            map_insert(pt_mapex, pt_pair);
            pair_make(pt_pair, '$', 0);
            map_insert(pt_mapex, pt_pair);
            pair_make(pt_pair, 'R', -5);
            map_insert(pt_mapex, pt_pair);
            pair_make(pt_pair, '>', 60);
            map_insert(pt_mapex, pt_pair);
            pair_make(pt_pair, 'E', 78);
            map_insert(pt_mapex, pt_pair);
            pair_make(pt_pair, '}', -3344);
            map_insert(pt_mapex, pt_pair);
            pair_make(pt_pair, '+', -93);
            map_insert(pt_mapex, pt_pair);
            pair_make(pt_pair, '@', -555);
            map_insert(pt_mapex, pt_pair);
            _print_map_c(pt_mapex, "<key: '%c', value: %d>, ", char, short);
            map_init_copy_range_ex(pt_map, map_begin(pt_mapex), map_end(pt_mapex), fun_great_char);
            _print_map_c(pt_map, "<key: '%c', value: %d>, ", char, short);
            pair_destroy(pt_pair);
            map_destroy(pt_map);
            map_destroy(pt_mapex);
        }
        /*map_destroy           */
        /*map_assign            */
        {
            map_t* pt_map = create_map(double, signed long int);
            map_t* pt_mapex = create_map(double, long);
            pair_t* pt_pair = create_pair(double, signed long);
            if(pt_map == NULL || pt_mapex == NULL || pt_pair == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            map_init(pt_map);
            map_init(pt_mapex);
            map_assign(pt_map, pt_mapex);
            _print_map_c(pt_map, "<key: %g, value: %ld>, ", double, long);

            pair_make(pt_pair, 49.2, -889);
            map_insert(pt_mapex, pt_pair);
            pair_make(pt_pair, 223.909, 343);
            map_insert(pt_mapex, pt_pair);
            pair_make(pt_pair, -0.20023, 134424);
            map_insert(pt_mapex, pt_pair);
            pair_make(pt_pair, -1111.0, -11111);
            map_insert(pt_mapex, pt_pair);
            map_assign(pt_map, pt_mapex);
            _print_map_c(pt_map, "<key: %g, value: %ld>, ", double, long);

            map_clear(pt_mapex);
            pair_make(pt_pair, 0.0, 0);
            map_insert(pt_mapex, pt_pair);
            pair_make(pt_pair, 2.3, 0);
            map_insert(pt_mapex, pt_pair);
            pair_make(pt_pair, -2.009, 9495934);
            map_insert(pt_mapex, pt_pair);
            map_assign(pt_map, pt_mapex);
            _print_map_c(pt_map, "<key: %g, value: %ld>, ", double, long);

            map_clear(pt_mapex);
            map_assign(pt_map, pt_mapex);
            _print_map_c(pt_map, "<key: %g, value: %ld>, ", double, long);

            pair_destroy(pt_pair);
            map_destroy(pt_map);
            map_destroy(pt_mapex);
        }
        /*map_swap              */
        {
            map_t* pt_map = create_map(int, unsigned char);
            map_t* pt_mapex = create_map(int, unsigned char);
            pair_t* pt_pair = create_pair(int, unsigned char);
            if(pt_map == NULL || pt_mapex == NULL || pt_pair == NULL)
            {
                return;
            }
            map_init(pt_map);
            map_init(pt_mapex);
            pair_init(pt_pair);
            map_swap(pt_map, pt_mapex);
            _print_map_c(pt_map, "<key: %d, value: 0x%X>, ", int, unsigned char);
            _print_map_c(pt_mapex, "<key: %d, value: 0x%X>, ", int, unsigned char);

            pair_make(pt_pair, 23, 0x45);
            map_insert(pt_mapex, pt_pair);
            pair_make(pt_pair, 212, 0x66);
            map_insert(pt_mapex, pt_pair);
            pair_make(pt_pair, 22, 0xa8);
            map_insert(pt_mapex, pt_pair);
            map_swap(pt_map, pt_mapex);
            _print_map_c(pt_map, "<key: %d, value: 0x%X>, ", int, unsigned char);
            _print_map_c(pt_mapex, "<key: %d, value: 0x%X>, ", int, unsigned char);

            pair_make(pt_pair, 90, 0x90);
            map_insert(pt_mapex, pt_pair);
            pair_make(pt_pair, -984, 0x00);
            map_insert(pt_mapex, pt_pair);
            pair_make(pt_pair, 23, 0xff);
            map_insert(pt_mapex, pt_pair);
            pair_make(pt_pair, 99, 0xac);
            map_insert(pt_mapex, pt_pair);
            pair_make(pt_pair, -80, 0xeb);
            map_insert(pt_mapex, pt_pair);
            pair_make(pt_pair, -4, 0xee);
            map_insert(pt_mapex, pt_pair);
            pair_make(pt_pair, -5, 0x08);
            map_insert(pt_mapex, pt_pair);
            map_swap(pt_map, pt_mapex);
            _print_map_c(pt_map, "<key: %d, value: 0x%X>, ", int, unsigned char);
            _print_map_c(pt_mapex, "<key: %d, value: 0x%X>, ", int, unsigned char);

            map_clear(pt_mapex);
            pair_make(pt_pair, 6, 0x66);
            map_insert(pt_mapex, pt_pair);
            pair_make(pt_pair, 45, 0x45);
            map_insert(pt_mapex, pt_pair);
            map_swap(pt_map, pt_mapex);
            _print_map_c(pt_map, "<key: %d, value: 0x%X>, ", int, unsigned char);
            _print_map_c(pt_mapex, "<key: %d, value: 0x%X>, ", int, unsigned char);

            map_clear(pt_mapex);
            map_swap(pt_map, pt_mapex);
            _print_map_c(pt_map, "<key: %d, value: 0x%X>, ", int, unsigned char);
            _print_map_c(pt_mapex, "<key: %d, value: 0x%X>, ", int, unsigned char);

            map_destroy(pt_map);
            map_destroy(pt_mapex);
            pair_destroy(pt_pair);
        }
        /*map_size              */
        /*map_empty             */
        /*map_max_size          */
        /*map_key_less          */
        /*map_value_less        */
        {
            map_t* pt_map = create_map(long, double);
            if(pt_map == NULL)
            {
                return;
            }
            map_init_ex(pt_map, fun_great_long);
            assert(map_key_less(pt_map) == fun_great_long && map_value_less(pt_map) != NULL &&
                map_key_less(pt_map) != map_value_less(pt_map));
            map_destroy(pt_map);
        }
        /*map_clear             */
        {
            map_t* pt_map = create_map(char, char);
            pair_t* pt_pair = create_pair(char, char);
            if(pt_map == NULL || pt_pair == NULL)
            {
                return;
            }
            map_init(pt_map);
            pair_init(pt_pair);
            map_clear(pt_map);
            _print_map_c(pt_map, "<key: '%c', value: '%c'>, ", char, char);
            pair_make(pt_pair, '^', '#');
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, 'g', 'B');
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, 'c', 'C');
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, '\\', '|');
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, '@', '$');
            map_insert(pt_map, pt_pair);
            _print_map_c(pt_map, "<key: '%c', value: '%c'>, ", char, char);
            map_clear(pt_map);
            _print_map_c(pt_map, "<key: '%c', value: '%c'>, ", char, char);
            map_destroy(pt_map);
            pair_destroy(pt_pair);
        }
        /*map_equal             */
        /*map_not_equal         */
        /*map_less              */
        /*map_less_equal        */
        /*map_great             */
        /*map_great_equal       */
        {
            map_t* pt_map = create_map(int, long);
            map_t* pt_mapex = create_map(int, long);
            pair_t* pt_pair = create_pair(int, long);
            if(pt_map == NULL || pt_mapex == NULL || pt_pair == NULL)
            {
                return;
            }
            map_init(pt_map);
            map_init(pt_mapex);
            pair_init(pt_pair);
            _print_map_c(pt_map, "<key: %d, value: %ld>, ", int, long);
            _print_map_c(pt_mapex, "<key: %d, value: %ld>, ", int, long);
            printf("equal: %d, not equal: %d, ",
                map_equal(pt_map, pt_mapex), map_not_equal(pt_map, pt_mapex));
            printf("less: %d, less equal: %d, ",
                map_less(pt_map, pt_mapex), map_less_equal(pt_map, pt_mapex));
            printf("great: %d, great equal: %d\n",
                map_great(pt_map, pt_mapex), map_great_equal(pt_map, pt_mapex));

            pair_make(pt_pair, 42, -900);
            map_insert(pt_map, pt_pair);
            _print_map_c(pt_map, "<key: %d, value: %ld>, ", int, long);
            _print_map_c(pt_mapex, "<key: %d, value: %ld>, ", int, long);
            printf("equal: %d, not equal: %d, ",
                map_equal(pt_map, pt_mapex), map_not_equal(pt_map, pt_mapex));
            printf("less: %d, less equal: %d, ",
                map_less(pt_map, pt_mapex), map_less_equal(pt_map, pt_mapex));
            printf("great: %d, great equal: %d\n",
                map_great(pt_map, pt_mapex), map_great_equal(pt_map, pt_mapex));

            map_insert(pt_mapex, pt_pair);
            _print_map_c(pt_map, "<key: %d, value: %ld>, ", int, long);
            _print_map_c(pt_mapex, "<key: %d, value: %ld>, ", int, long);
            printf("equal: %d, not equal: %d, ",
                map_equal(pt_map, pt_mapex), map_not_equal(pt_map, pt_mapex));
            printf("less: %d, less equal: %d, ",
                map_less(pt_map, pt_mapex), map_less_equal(pt_map, pt_mapex));
            printf("great: %d, great equal: %d\n",
                map_great(pt_map, pt_mapex), map_great_equal(pt_map, pt_mapex));

            pair_make(pt_pair, -56, 23);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, 1000, 1000000);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, 0, 0);
            map_insert(pt_mapex, pt_pair);
            _print_map_c(pt_map, "<key: %d, value: %ld>, ", int, long);
            _print_map_c(pt_mapex, "<key: %d, value: %ld>, ", int, long);
            printf("equal: %d, not equal: %d, ",
                map_equal(pt_map, pt_mapex), map_not_equal(pt_map, pt_mapex));
            printf("less: %d, less equal: %d, ",
                map_less(pt_map, pt_mapex), map_less_equal(pt_map, pt_mapex));
            printf("great: %d, great equal: %d\n",
                map_great(pt_map, pt_mapex), map_great_equal(pt_map, pt_mapex));

            map_destroy(pt_map);
            map_destroy(pt_mapex);
            pair_destroy(pt_pair);
        }
        /*map_begin             */
        /*map_end               */
        /*map_find              */
        /*map_count             */
        {
            map_t* pt_map = create_map(double, int);
            pair_t* pt_pair = create_pair(double, int);
            iterator_t t_pos; 
            if(pt_map == NULL || pt_pair == NULL)
            {
                return;
            }
            map_init(pt_map);
            pair_init(pt_pair);
            t_pos = map_find(pt_map, 89.004);
            if(!iterator_equal(t_pos, map_end(pt_map)))
            {
                printf("found <key: %lf, value: %d>, count: %u\n",
                    *(double*)pair_first((pair_t*)iterator_get_pointer(t_pos)),
                    *(int*)pair_second((pair_t*)iterator_get_pointer(t_pos)),
                    map_count(pt_map, 89.004));
            }
            else
            {
                printf("not found, count: %u\n", map_count(pt_map, 89.004));
            }

            pair_make(pt_pair, 45.092, 34);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, 89.004, 1024);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, 0.0, 0);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, -454.0, 1212);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, -44.33, 4433);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, 890.234, 2);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, 123.321, 123321);
            map_insert(pt_map, pt_pair);
            _print_map_c(pt_map, "<key: %lf, value: %d>, ", double, int);

            t_pos = map_find(pt_map, 89.0041);
            if(!iterator_equal(t_pos, map_end(pt_map)))
            {
                printf("found <key: %lf, value: %d>, count: %u\n",
                    *(double*)pair_first((pair_t*)iterator_get_pointer(t_pos)),
                    *(int*)pair_second((pair_t*)iterator_get_pointer(t_pos)),
                    map_count(pt_map, 89.0041));
            }
            else
            {
                printf("not found, count: %u\n", map_count(pt_map, 89.0041));
            }

            t_pos = map_find(pt_map, 89.004);
            if(!iterator_equal(t_pos, map_end(pt_map)))
            {
                printf("found <key: %lf, value: %d>, count: %u\n",
                    *(double*)pair_first((pair_t*)iterator_get_pointer(t_pos)),
                    *(int*)pair_second((pair_t*)iterator_get_pointer(t_pos)),
                    map_count(pt_map, 89.004));
            }
            else
            {
                printf("not found, count: %u\n", map_count(pt_map, 89.004));
            }

            map_destroy(pt_map);
            pair_destroy(pt_pair);
        }
        /*map_lower_bound       */
        /*map_upper_bound       */
        /*map_equal_range       */
        {
            map_t* pt_map = create_map(int, long);
            pair_t* pt_pair = create_pair(int, long);
            iterator_t t_begin;
            iterator_t t_end;
            range_t t_range;
            if(pt_map == NULL || pt_pair == NULL)
            {
                return;
            }
            map_init(pt_map);
            pair_init(pt_pair);
            t_begin = map_lower_bound(pt_map, 78);
            t_end = map_upper_bound(pt_map, 78);
            t_range = map_equal_range(pt_map, 78);
            assert(iterator_equal(t_begin, map_end(pt_map)) &&
                iterator_equal(t_begin, t_end) &&
                iterator_equal(t_range.t_begin, t_begin) &&
                iterator_equal(t_range.t_end, t_end));
            pair_make(pt_pair, 5, 2323);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, 0, 123456);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, -60, -8249339);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, 234, 324);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, 90, 909090);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, 2, 222);
            map_insert(pt_map, pt_pair);
            _print_map_c(pt_map, "<key: %d, value: %ld>, ", int, long);
            t_begin = map_lower_bound(pt_map, 78);
            t_end = map_upper_bound(pt_map, 78);
            t_range = map_equal_range(pt_map, 78);
            assert(iterator_equal(t_begin, t_end) &&
                iterator_equal(t_range.t_begin, t_begin) &&
                iterator_equal(t_range.t_end, t_end));
            t_begin = map_lower_bound(pt_map, 90);
            t_end = map_upper_bound(pt_map, 90);
            t_range = map_equal_range(pt_map, 90);
            assert(iterator_equal(t_begin, iterator_prev(t_end)) &&
                iterator_equal(t_range.t_begin, t_begin) &&
                iterator_equal(t_range.t_end, t_end));
            map_destroy(pt_map);
            pair_destroy(pt_pair);
        }
        /*map_at                */
        {
            map_t* pt_map = create_map(int, double);
            pair_t* pt_pair = create_pair(int, double);
            if(pt_map == NULL || pt_pair == NULL)
            {
                return;
            }
            map_init(pt_map);
            pair_init(pt_pair);
            pair_make(pt_pair, 67, 930.24);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, 23, 3445.22);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, 1, -90);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, 213, -88449);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, 0, 234);
            map_insert(pt_map, pt_pair);
            _print_map_c(pt_map, "<key: %d, value: %lf>, ", int, double);
            *(double*)map_at(pt_map, 1) = 111;
            *(double*)map_at(pt_map, 2) = 222;
            _print_map_c(pt_map, "<key: %d, value: %lf>, ", int, double);
            map_destroy(pt_map);
            pair_destroy(pt_pair);
        }
        /*map_insert            */
        {
            map_t* pt_map = create_map(int, long);
            pair_t* pt_pair = create_pair(int, long);
            if(pt_map == NULL || pt_pair == NULL)
            {
                return;
            }
            map_init(pt_map);
            pair_init(pt_pair);
            pair_make(pt_pair, 23, -849);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, 10, 222);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, 34, 43);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, 4555, 984);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, 10, 238493);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, 34, 2344455);
            map_insert(pt_map, pt_pair);
            _print_map_c(pt_map, "<key: %d, value: %ld>, ", int, long);
            map_destroy(pt_map);
            pair_destroy(pt_pair);
        }
        /*map_insert_hint       */
        {
            map_t* pt_map = create_map(int, long);
            pair_t* pt_pair = create_pair(int, long);
            iterator_t t_pos;
            if(pt_map == NULL || pt_pair == NULL)
            {
                return;
            }
            map_init(pt_map);
            pair_init(pt_pair);
            t_pos = map_begin(pt_map);
            pair_make(pt_pair, 23, -849);
            map_insert_hint(pt_map, t_pos, pt_pair);
            pair_make(pt_pair, 10, 222);
            map_insert_hint(pt_map, t_pos, pt_pair);
            pair_make(pt_pair, 34, 43);
            map_insert_hint(pt_map, t_pos, pt_pair);
            pair_make(pt_pair, 4555, 984);
            map_insert_hint(pt_map, t_pos, pt_pair);
            pair_make(pt_pair, 10, 238493);
            map_insert_hint(pt_map, t_pos, pt_pair);
            pair_make(pt_pair, 34, 2344455);
            map_insert_hint(pt_map, t_pos, pt_pair);
            _print_map_c(pt_map, "<key: %d, value: %ld>, ", int, long);
            map_destroy(pt_map);
            pair_destroy(pt_pair);
        }
        /*map_insert_range      */
        {
            map_t* pt_map = create_map(int, double);
            map_t* pt_mapex = create_map(int, double);
            pair_t* pt_pair = create_pair(int, double);
            if(pt_map == NULL || pt_mapex == NULL || pt_pair == NULL)
            {
                return;
            }
            map_init(pt_map);
            map_init_ex(pt_mapex, fun_great_int);
            pair_init(pt_pair);
            map_insert_range(pt_map, map_begin(pt_mapex), map_end(pt_mapex));
            _print_map_c(pt_map, "<key: %d, value: %lf>, ", int, double);

            pair_make(pt_pair, 19, 90.23445);
            map_insert(pt_mapex, pt_pair);
            pair_make(pt_pair, 2, 90.23445);
            map_insert(pt_mapex, pt_pair);
            pair_make(pt_pair, 88, 74.28);
            map_insert(pt_mapex, pt_pair);
            pair_make(pt_pair, 90, -3565.3);
            map_insert(pt_mapex, pt_pair);
            pair_make(pt_pair, 213, 45);
            map_insert(pt_mapex, pt_pair);
            pair_make(pt_pair, -48, -45.0);
            map_insert(pt_mapex, pt_pair);
            pair_make(pt_pair, -33, -90.23);
            map_insert(pt_mapex, pt_pair);
            pair_make(pt_pair, 232, 33);
            map_insert(pt_mapex, pt_pair);
            pair_make(pt_pair, -100, -100.0);
            map_insert(pt_mapex, pt_pair);
            pair_make(pt_pair, 100, 100.0);
            map_insert(pt_mapex, pt_pair);
            pair_make(pt_pair, 3, 7.21);
            map_insert(pt_mapex, pt_pair);
            _print_map_c(pt_mapex, "<key: %d, value: %lf>, ", int, double);

            map_insert_range(pt_map, map_begin(pt_mapex), map_begin(pt_mapex));
            _print_map_c(pt_map, "<key: %d, value: %lf>, ", int, double);
            map_insert_range(pt_map, map_begin(pt_mapex),
                iterator_advance(map_begin(pt_mapex), 3));
            _print_map_c(pt_map, "<key: %d, value: %lf>, ", int, double);
            map_insert_range(pt_map, iterator_advance(map_begin(pt_mapex), 4),
                iterator_advance(map_begin(pt_mapex), 6));
            _print_map_c(pt_map, "<key: %d, value: %lf>, ", int, double);
            map_insert_range(pt_map, iterator_advance(map_begin(pt_mapex), 7),
                map_end(pt_mapex));
            _print_map_c(pt_map, "<key: %d, value: %lf>, ", int, double);
            map_insert_range(pt_map, map_end(pt_mapex), map_end(pt_mapex));
            _print_map_c(pt_map, "<key: %d, value: %lf>, ", int, double);
            map_clear(pt_map);
            map_insert_range(pt_map, map_begin(pt_mapex), map_end(pt_mapex));
            _print_map_c(pt_map, "<key: %d, value: %lf>, ", int, double);

            map_destroy(pt_map);
            map_destroy(pt_mapex);
            pair_destroy(pt_pair);
        }
        /*map_erase             */
        {
            map_t* pt_map = create_map(int, double);
            pair_t* pt_pair = create_pair(int, double);
            if(pt_map == NULL || pt_pair == NULL)
            {
                return;
            }
            map_init(pt_map);
            pair_init(pt_pair);
            map_erase(pt_map, 89);
            _print_map_c(pt_map, "<key: %d, value: %lf>, ", int, double);
            pair_make(pt_pair, 19, 90.23445);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, 2, 90.23445);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, 88, 74.28);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, 90, -3565.3);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, 213, 45);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, -48, -45.0);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, -33, -90.23);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, 232, 33);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, -100, -100.0);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, 100, 100.0);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, 3, 7.21);
            map_insert(pt_map, pt_pair);
            _print_map_c(pt_map, "<key: %d, value: %lf>, ", int, double);
            map_erase(pt_map, 89);
            _print_map_c(pt_map, "<key: %d, value: %lf>, ", int, double);
            map_erase(pt_map, 88);
            _print_map_c(pt_map, "<key: %d, value: %lf>, ", int, double);

            map_destroy(pt_map);
            pair_destroy(pt_pair);
        }
        /*map_erase_pos         */
        {
            map_t* pt_map = create_map(int, double);
            pair_t* pt_pair = create_pair(int, double);
            if(pt_map == NULL || pt_pair == NULL)
            {
                return;
            }
            map_init(pt_map);
            pair_init(pt_pair);
            pair_make(pt_pair, 19, 90.23445);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, 2, 90.23445);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, 88, 74.28);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, 90, -3565.3);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, 213, 45);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, -48, -45.0);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, -33, -90.23);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, 232, 33);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, -100, -100.0);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, 100, 100.0);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, 3, 7.21);
            map_insert(pt_map, pt_pair);
            _print_map_c(pt_map, "<key: %d, value: %lf>, ", int, double);
            map_erase_pos(pt_map, map_begin(pt_map));
            _print_map_c(pt_map, "<key: %d, value: %lf>, ", int, double);
            map_erase_pos(pt_map, iterator_prev(map_end(pt_map)));
            _print_map_c(pt_map, "<key: %d, value: %lf>, ", int, double);
            map_erase_pos(pt_map, iterator_advance(map_begin(pt_map), 5));
            _print_map_c(pt_map, "<key: %d, value: %lf>, ", int, double);

            while(!map_empty(pt_map))
            {
                map_erase_pos(pt_map, map_begin(pt_map));
            }
            _print_map_c(pt_map, "<key: %d, value: %lf>, ", int, double);

            map_destroy(pt_map);
            pair_destroy(pt_pair);
        }
        /*map_erase_range       */
        {
            map_t* pt_map = create_map(int, double);
            pair_t* pt_pair = create_pair(int, double);
            if(pt_map == NULL || pt_pair == NULL)
            {
                return;
            }
            map_init(pt_map);
            pair_init(pt_pair);
            map_erase_range(pt_map, map_begin(pt_map), map_end(pt_map));
            _print_map_c(pt_map, "<key: %d, value: %lf>, ", int, double);

            pair_make(pt_pair, 19, 90.23445);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, 2, 90.23445);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, 88, 74.28);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, 90, -3565.3);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, 213, 45);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, -48, -45.0);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, -33, -90.23);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, 232, 33);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, -100, -100.0);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, 100, 100.0);
            map_insert(pt_map, pt_pair);
            pair_make(pt_pair, 3, 7.21);
            map_insert(pt_map, pt_pair);
            _print_map_c(pt_map, "<key: %d, value: %lf>, ", int, double);
            map_erase_range(pt_map, map_begin(pt_map), map_begin(pt_map));
            _print_map_c(pt_map, "<key: %d, value: %lf>, ", int, double);
            map_erase_range(pt_map, map_begin(pt_map), iterator_advance(map_begin(pt_map), 3));
            _print_map_c(pt_map, "<key: %d, value: %lf>, ", int, double);
            map_erase_range(pt_map, iterator_next(map_begin(pt_map)),
                iterator_advance(map_begin(pt_map), 3));
            _print_map_c(pt_map, "<key: %d, value: %lf>, ", int, double);
            map_erase_range(pt_map, iterator_advance(map_begin(pt_map), 3), map_end(pt_map));
            _print_map_c(pt_map, "<key: %d, value: %lf>, ", int, double);
            map_erase_range(pt_map, map_end(pt_map), map_end(pt_map));
            _print_map_c(pt_map, "<key: %d, value: %lf>, ", int, double);
            map_erase_range(pt_map, map_begin(pt_map), map_end(pt_map));
            _print_map_c(pt_map, "<key: %d, value: %lf>, ", int, double);

            map_destroy(pt_map);
            pair_destroy(pt_pair);
        }
    }
    /* user defined types */
    {
        type_register(_mapkey_t, _mapkey_init, _mapkey_copy, _mapkey_less, _mapkey_destroy);
        type_register(_mapvalue_t, _mapvalue_init, _mapvalue_copy, _mapvalue_less, _mapvalue_destroy);
        type_duplicate(_mapkey_t, struct _tagmapkey);
        type_duplicate(_mapvalue_t, struct _tagmapvalue);
        _type_debug();
        /*create_map            */
        {
            map_t* pt_map = create_map(_mapkey_t, _mapvalue_t);
            pair_t* pt_pair = create_pair(struct _tagmapkey, struct _tagmapvalue);
            _mapkey_t _t_key;
            _mapvalue_t _t_value;
            if(pt_map == NULL || pt_pair == NULL)
            {
                return;
            }
            map_init(pt_map);
            pair_init(pt_pair);
            _print_map_user(pt_map);

            _t_key._t_unit = _MB;
            _t_key._un_number = 89;
            strcpy(_t_value._s_enviroment, "Download");
            strcpy(_t_value._s_condition, "3G");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);

            _t_key._t_unit = _MB;
            _t_key._un_number = 2;
            strcpy(_t_value._s_enviroment, "Download");
            strcpy(_t_value._s_condition, "3G");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);

            _t_key._t_unit = _KB;
            _t_key._un_number = 5000;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "PPPoE");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);

            _print_map_user(pt_map);
            map_destroy(pt_map);
            pair_destroy(pt_pair);
        }
        /*map_init              */
        /*map_init_ex           */
        {
            map_t* pt_map = create_map(_mapkey_t, _mapvalue_t);
            pair_t* pt_pair = create_pair(struct _tagmapkey, struct _tagmapvalue);
            _mapkey_t _t_key;
            _mapvalue_t _t_value;
            if(pt_map == NULL || pt_pair == NULL)
            {
                return;
            }
            map_init_ex(pt_map, _mapkey_number_great);
            pair_init(pt_pair);
            _print_map_user(pt_map);

            _t_key._t_unit = _MB;
            _t_key._un_number = 89;
            strcpy(_t_value._s_enviroment, "Download");
            strcpy(_t_value._s_condition, "3G");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);

            _t_key._t_unit = _MB;
            _t_key._un_number = 2;
            strcpy(_t_value._s_enviroment, "Download");
            strcpy(_t_value._s_condition, "3G");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);

            _t_key._t_unit = _KB;
            _t_key._un_number = 5000;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "PPPoE");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);

            _print_map_user(pt_map);
            map_destroy(pt_map);
            pair_destroy(pt_pair);
        }
        /*map_init_copy         */
        {
            map_t* pt_map = create_map(_mapkey_t, _mapvalue_t);
            map_t* pt_mapex = create_map(_mapkey_t, _mapvalue_t);
            pair_t* pt_pair = create_pair(struct _tagmapkey, struct _tagmapvalue);
            _mapkey_t _t_key;
            _mapvalue_t _t_value;
            if(pt_map == NULL || pt_mapex == NULL || pt_pair == NULL)
            {
                return;
            }
            map_init(pt_mapex);
            pair_init(pt_pair);

            _t_key._t_unit = _B;
            _t_key._un_number = 89;
            strcpy(_t_value._s_enviroment, "Download");
            strcpy(_t_value._s_condition, "3G");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_mapex, pt_pair);

            _t_key._t_unit = _MB;
            _t_key._un_number = 2;
            strcpy(_t_value._s_enviroment, "Download");
            strcpy(_t_value._s_condition, "3G");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_mapex, pt_pair);

            _t_key._t_unit = _KB;
            _t_key._un_number = 5100;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "PPPoE");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_mapex, pt_pair);
            _print_map_user(pt_mapex);

            map_init_copy(pt_map, pt_mapex);
            _print_map_user(pt_map);
            map_destroy(pt_map);
            map_destroy(pt_mapex);
            pair_destroy(pt_pair);
        }
        /*map_init_copy_range   */
        {
            map_t* pt_map = create_map(_mapkey_t, _mapvalue_t);
            map_t* pt_mapex = create_map(_mapkey_t, _mapvalue_t);
            pair_t* pt_pair = create_pair(struct _tagmapkey, struct _tagmapvalue);
            _mapkey_t _t_key;
            _mapvalue_t _t_value;
            if(pt_map == NULL || pt_mapex == NULL || pt_pair == NULL)
            {
                return;
            }
            map_init_ex(pt_mapex, _mapkey_number_great);
            pair_init(pt_pair);

            _t_key._t_unit = _B;
            _t_key._un_number = 89;
            strcpy(_t_value._s_enviroment, "Download");
            strcpy(_t_value._s_condition, "3G");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_mapex, pt_pair);

            _t_key._t_unit = _MB;
            _t_key._un_number = 2;
            strcpy(_t_value._s_enviroment, "Download");
            strcpy(_t_value._s_condition, "3G");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_mapex, pt_pair);

            _t_key._t_unit = _KB;
            _t_key._un_number = 5100;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "PPPoE");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_mapex, pt_pair);

            _t_key._t_unit = _KB;
            _t_key._un_number = 0;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "Modem");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_mapex, pt_pair);

            _t_key._t_unit = _B;
            _t_key._un_number = 1025;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "Modem");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_mapex, pt_pair);

            _t_key._t_unit = _KB;
            _t_key._un_number = 1;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "Modem");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_mapex, pt_pair);

            _t_key._t_unit = _MB;
            _t_key._un_number = 1;
            strcpy(_t_value._s_enviroment, "Download");
            strcpy(_t_value._s_condition, "PPPoE");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_mapex, pt_pair);
            _print_map_user(pt_mapex);

            map_init_copy_range(pt_map, map_begin(pt_mapex), map_end(pt_mapex));
            _print_map_user(pt_map);
            map_destroy(pt_map);
            map_destroy(pt_mapex);
            pair_destroy(pt_pair);
        }
        /*map_init_copy_range_ex*/
        {
            map_t* pt_map = create_map(_mapkey_t, _mapvalue_t);
            map_t* pt_mapex = create_map(_mapkey_t, _mapvalue_t);
            pair_t* pt_pair = create_pair(struct _tagmapkey, struct _tagmapvalue);
            _mapkey_t _t_key;
            _mapvalue_t _t_value;
            if(pt_map == NULL || pt_mapex == NULL || pt_pair == NULL)
            {
                return;
            }
            map_init(pt_mapex);
            pair_init(pt_pair);

            _t_key._t_unit = _B;
            _t_key._un_number = 89;
            strcpy(_t_value._s_enviroment, "Download");
            strcpy(_t_value._s_condition, "3G");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_mapex, pt_pair);

            _t_key._t_unit = _MB;
            _t_key._un_number = 2;
            strcpy(_t_value._s_enviroment, "Download");
            strcpy(_t_value._s_condition, "3G");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_mapex, pt_pair);

            _t_key._t_unit = _KB;
            _t_key._un_number = 5100;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "PPPoE");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_mapex, pt_pair);

            _t_key._t_unit = _KB;
            _t_key._un_number = 0;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "Modem");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_mapex, pt_pair);

            _t_key._t_unit = _B;
            _t_key._un_number = 1025;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "Modem");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_mapex, pt_pair);

            _t_key._t_unit = _KB;
            _t_key._un_number = 1;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "Modem");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_mapex, pt_pair);

            _t_key._t_unit = _MB;
            _t_key._un_number = 1;
            strcpy(_t_value._s_enviroment, "Download");
            strcpy(_t_value._s_condition, "PPPoE");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_mapex, pt_pair);
            _print_map_user(pt_mapex);

            map_init_copy_range_ex(pt_map, map_begin(pt_mapex), map_end(pt_mapex), _mapkey_number_great);
            _print_map_user(pt_map);
            map_destroy(pt_map);
            map_destroy(pt_mapex);
            pair_destroy(pt_pair);
        }
        /*map_destroy           */
        /*map_assign            */
        {
            map_t* pt_map = create_map(_mapkey_t, _mapvalue_t);
            map_t* pt_mapex = create_map(_mapkey_t, _mapvalue_t);
            pair_t* pt_pair = create_pair(struct _tagmapkey, struct _tagmapvalue);
            _mapkey_t _t_key;
            _mapvalue_t _t_value;
            if(pt_map == NULL || pt_mapex == NULL || pt_pair == NULL)
            {
                return;
            }
            map_init(pt_mapex);
            map_init(pt_map);
            pair_init(pt_pair);

            map_assign(pt_map, pt_mapex);
            _print_map_user(pt_map);

            _t_key._t_unit = _B;
            _t_key._un_number = 89;
            strcpy(_t_value._s_enviroment, "Download");
            strcpy(_t_value._s_condition, "3G");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_mapex, pt_pair);

            _t_key._t_unit = _MB;
            _t_key._un_number = 2;
            strcpy(_t_value._s_enviroment, "Download");
            strcpy(_t_value._s_condition, "3G");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_mapex, pt_pair);

            _t_key._t_unit = _KB;
            _t_key._un_number = 5100;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "PPPoE");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_mapex, pt_pair);

            _t_key._t_unit = _KB;
            _t_key._un_number = 0;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "Modem");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_mapex, pt_pair);

            _t_key._t_unit = _B;
            _t_key._un_number = 1025;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "Modem");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_mapex, pt_pair);

            _t_key._t_unit = _KB;
            _t_key._un_number = 1;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "Modem");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_mapex, pt_pair);

            _t_key._t_unit = _MB;
            _t_key._un_number = 1;
            strcpy(_t_value._s_enviroment, "Download");
            strcpy(_t_value._s_condition, "PPPoE");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_mapex, pt_pair);

            map_assign(pt_map, pt_mapex);
            _print_map_user(pt_map);

            map_clear(pt_mapex);
            map_assign(pt_map, pt_mapex);
            _print_map_user(pt_map);

            map_destroy(pt_map);
            map_destroy(pt_mapex);
            pair_destroy(pt_pair);
        }
        /*map_swap              */
        {
            map_t* pt_map = create_map(_mapkey_t, _mapvalue_t);
            map_t* pt_mapex = create_map(_mapkey_t, _mapvalue_t);
            pair_t* pt_pair = create_pair(struct _tagmapkey, struct _tagmapvalue);
            _mapkey_t _t_key;
            _mapvalue_t _t_value;
            if(pt_map == NULL || pt_mapex == NULL || pt_pair == NULL)
            {
                return;
            }
            map_init(pt_mapex);
            map_init(pt_map);
            pair_init(pt_pair);

            map_swap(pt_map, pt_mapex);
            _print_map_user(pt_map);
            _print_map_user(pt_mapex);

            _t_key._t_unit = _B;
            _t_key._un_number = 89;
            strcpy(_t_value._s_enviroment, "Download");
            strcpy(_t_value._s_condition, "3G");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_mapex, pt_pair);

            _t_key._t_unit = _MB;
            _t_key._un_number = 2;
            strcpy(_t_value._s_enviroment, "Download");
            strcpy(_t_value._s_condition, "3G");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_mapex, pt_pair);

            _t_key._t_unit = _KB;
            _t_key._un_number = 5100;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "PPPoE");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_mapex, pt_pair);

            map_swap(pt_map, pt_mapex);
            _print_map_user(pt_map);
            _print_map_user(pt_mapex);

            _t_key._t_unit = _KB;
            _t_key._un_number = 0;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "Modem");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_mapex, pt_pair);

            _t_key._t_unit = _B;
            _t_key._un_number = 1025;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "Modem");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_mapex, pt_pair);

            _t_key._t_unit = _KB;
            _t_key._un_number = 1;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "Modem");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_mapex, pt_pair);

            _t_key._t_unit = _MB;
            _t_key._un_number = 1;
            strcpy(_t_value._s_enviroment, "Download");
            strcpy(_t_value._s_condition, "PPPoE");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_mapex, pt_pair);

            _t_key._t_unit = _KB;
            _t_key._un_number = 9;
            strcpy(_t_value._s_enviroment, "Download");
            strcpy(_t_value._s_condition, "Modem");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_mapex, pt_pair);

            map_swap(pt_map, pt_mapex);
            _print_map_user(pt_map);
            _print_map_user(pt_mapex);

            map_clear(pt_mapex);
            _t_key._t_unit = _MB;
            _t_key._un_number = 7;
            strcpy(_t_value._s_enviroment, "FTP");
            strcpy(_t_value._s_condition, "PPPoE");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_mapex, pt_pair);

            map_swap(pt_map, pt_mapex);
            _print_map_user(pt_map);
            _print_map_user(pt_mapex);

            map_clear(pt_mapex);
            map_swap(pt_map, pt_mapex);
            _print_map_user(pt_map);
            _print_map_user(pt_mapex);

            map_destroy(pt_map);
            map_destroy(pt_mapex);
            pair_destroy(pt_pair);
        }
        /*map_size              */
        /*map_empty             */
        /*map_max_size          */
        /*map_key_less          */
        /*map_value_less        */
        {
            map_t* pt_map = create_map(_mapkey_t, _mapvalue_t);
            if(pt_map == NULL)
            {
                return;
            }
            map_init(pt_map);
            assert(map_key_less(pt_map) == _mapkey_less &&
                map_value_less(pt_map) == _mapvalue_less);
            map_destroy(pt_map);
        }
        /*map_clear             */
        {
            map_t* pt_map = create_map(_mapkey_t, _mapvalue_t);
            pair_t* pt_pair = create_pair(_mapkey_t, _mapvalue_t);
            _mapkey_t _t_key;
            _mapvalue_t _t_value;
            if(pt_map == NULL || pt_pair == NULL)
            {
                return;
            }
            map_init(pt_map);
            pair_init(pt_pair);
            map_clear(pt_map);
            _print_map_user(pt_map);

            _t_key._t_unit = _B;
            _t_key._un_number = 1025;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "Modem");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);

            _t_key._t_unit = _KB;
            _t_key._un_number = 1;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "Modem");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);

            _t_key._t_unit = _MB;
            _t_key._un_number = 1;
            strcpy(_t_value._s_enviroment, "Download");
            strcpy(_t_value._s_condition, "PPPoE");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);

            _t_key._t_unit = _KB;
            _t_key._un_number = 9;
            strcpy(_t_value._s_enviroment, "Download");
            strcpy(_t_value._s_condition, "Modem");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);
            _print_map_user(pt_map);

            map_clear(pt_map);
            _print_map_user(pt_map);

            map_destroy(pt_map);
            pair_destroy(pt_pair);
        }
        /*map_equal             */
        /*map_not_equal         */
        /*map_less              */
        /*map_less_equal        */
        /*map_great             */
        /*map_great_equal       */
        {
            map_t* pt_map = create_map(_mapkey_t, _mapvalue_t);
            map_t* pt_mapex = create_map(_mapkey_t, _mapvalue_t);
            pair_t* pt_pair = create_pair(struct _tagmapkey, struct _tagmapvalue);
            _mapkey_t _t_key;
            _mapvalue_t _t_value;
            if(pt_map == NULL || pt_mapex == NULL || pt_pair == NULL)
            {
                return;
            }
            map_init(pt_mapex);
            map_init(pt_map);
            pair_init(pt_pair);

            _print_map_user(pt_map);
            _print_map_user(pt_mapex);
            printf("equal: %d, not equal: %d, ",
                map_equal(pt_map, pt_mapex), map_not_equal(pt_map, pt_mapex));
            printf("less: %d, less equal: %d, ",
                map_less(pt_map, pt_mapex), map_less_equal(pt_map, pt_mapex));
            printf("great: %d, great equal: %d\n",
                map_great(pt_map, pt_mapex), map_great_equal(pt_map, pt_mapex));

            _t_key._t_unit = _MB;
            _t_key._un_number = 2;
            strcpy(_t_value._s_enviroment, "Download");
            strcpy(_t_value._s_condition, "3G");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);
            _print_map_user(pt_map);
            _print_map_user(pt_mapex);
            printf("equal: %d, not equal: %d, ",
                map_equal(pt_map, pt_mapex), map_not_equal(pt_map, pt_mapex));
            printf("less: %d, less equal: %d, ",
                map_less(pt_map, pt_mapex), map_less_equal(pt_map, pt_mapex));
            printf("great: %d, great equal: %d\n",
                map_great(pt_map, pt_mapex), map_great_equal(pt_map, pt_mapex));

            map_insert(pt_mapex, pt_pair);
            _print_map_user(pt_map);
            _print_map_user(pt_mapex);
            printf("equal: %d, not equal: %d, ",
                map_equal(pt_map, pt_mapex), map_not_equal(pt_map, pt_mapex));
            printf("less: %d, less equal: %d, ",
                map_less(pt_map, pt_mapex), map_less_equal(pt_map, pt_mapex));
            printf("great: %d, great equal: %d\n",
                map_great(pt_map, pt_mapex), map_great_equal(pt_map, pt_mapex));

            _t_key._t_unit = _B;
            _t_key._un_number = 1025;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "Modem");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);
            _t_key._t_unit = _KB;
            _t_key._un_number = 5100;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "PPPoE");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);
            _t_key._t_unit = _MB;
            _t_key._un_number = 6;
            strcpy(_t_value._s_enviroment, "Download");
            strcpy(_t_value._s_condition, "PPPoE");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_mapex, pt_pair);
            _print_map_user(pt_map);
            _print_map_user(pt_mapex);
            printf("equal: %d, not equal: %d, ",
                map_equal(pt_map, pt_mapex), map_not_equal(pt_map, pt_mapex));
            printf("less: %d, less equal: %d, ",
                map_less(pt_map, pt_mapex), map_less_equal(pt_map, pt_mapex));
            printf("great: %d, great equal: %d\n",
                map_great(pt_map, pt_mapex), map_great_equal(pt_map, pt_mapex));

            map_destroy(pt_map);
            map_destroy(pt_mapex);
            pair_destroy(pt_pair);
        }
        /*map_begin             */
        /*map_end               */
        /*map_find              */
        /*map_count             */
        {
            map_t* pt_map = create_map(_mapkey_t, _mapvalue_t);
            pair_t* pt_pair = create_pair(_mapkey_t, _mapvalue_t);
            _mapkey_t _t_key;
            _mapvalue_t _t_value;
            iterator_t t_iter;
            if(pt_map == NULL || pt_pair == NULL)
            {
                return;
            }
            map_init(pt_map);
            pair_init(pt_pair);

            t_iter = map_find(pt_map, &_t_key);
            if(iterator_equal(t_iter, map_end(pt_map)))
            {
                printf("not found, count: %u\n", map_count(pt_map, &_t_key));
            }
            else
            {
                printf("found, count: %d\n", map_count(pt_map, &_t_key));
            }

            _t_key._t_unit = _B;
            _t_key._un_number = 1025;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "Modem");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);

            _t_key._t_unit = _KB;
            _t_key._un_number = 1;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "Modem");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);

            _t_key._t_unit = _MB;
            _t_key._un_number = 1;
            strcpy(_t_value._s_enviroment, "Download");
            strcpy(_t_value._s_condition, "PPPoE");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);

            _t_key._t_unit = _KB;
            _t_key._un_number = 9;
            strcpy(_t_value._s_enviroment, "Download");
            strcpy(_t_value._s_condition, "Modem");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);
            _print_map_user(pt_map);

            _t_key._t_unit = _KB;
            _t_key._un_number = 19;
            t_iter = map_find(pt_map, &_t_key);
            if(iterator_equal(t_iter, map_end(pt_map)))
            {
                printf("not found, count: %u\n", map_count(pt_map, &_t_key));
            }
            else
            {
                printf("found, count: %d\n", map_count(pt_map, &_t_key));
            }

            _t_key._t_unit = _KB;
            _t_key._un_number = 1;
            t_iter = map_find(pt_map, &_t_key);
            if(iterator_equal(t_iter, map_end(pt_map)))
            {
                printf("not found, count: %u\n", map_count(pt_map, &_t_key));
            }
            else
            {
                printf("found, count: %d\n", map_count(pt_map, &_t_key));
            }

            map_destroy(pt_map);
            pair_destroy(pt_pair);
        }
        /*map_lower_bound       */
        /*map_upper_bound       */
        /*map_equal_range       */
        {
            map_t* pt_map = create_map(_mapkey_t, _mapvalue_t);
            pair_t* pt_pair = create_pair(_mapkey_t, _mapvalue_t);
            _mapkey_t _t_key;
            _mapvalue_t _t_value;
            iterator_t t_begin;
            iterator_t t_end;
            range_t t_range;
            if(pt_map == NULL || pt_pair == NULL)
            {
                return;
            }
            map_init(pt_map);
            pair_init(pt_pair);

            t_begin = map_lower_bound(pt_map, &_t_key);
            t_end = map_upper_bound(pt_map, &_t_key);
            t_range = map_equal_range(pt_map, &_t_key);
            assert(iterator_equal(t_begin, map_end(pt_map)) &&
                iterator_equal(t_begin, t_end) &&
                iterator_equal(t_range.t_begin, t_begin) &&
                iterator_equal(t_range.t_end, t_end));

            _t_key._t_unit = _B;
            _t_key._un_number = 1025;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "Modem");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);

            _t_key._t_unit = _KB;
            _t_key._un_number = 1;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "Modem");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);

            _t_key._t_unit = _MB;
            _t_key._un_number = 1;
            strcpy(_t_value._s_enviroment, "Download");
            strcpy(_t_value._s_condition, "PPPoE");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);

            _t_key._t_unit = _KB;
            _t_key._un_number = 9;
            strcpy(_t_value._s_enviroment, "Download");
            strcpy(_t_value._s_condition, "Modem");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);
            _print_map_user(pt_map);

            _t_key._t_unit = _KB;
            _t_key._un_number = 19;
            t_begin = map_lower_bound(pt_map, &_t_key);
            t_end = map_upper_bound(pt_map, &_t_key);
            t_range = map_equal_range(pt_map, &_t_key);
            assert(iterator_equal(t_begin, t_end) &&
                iterator_equal(t_range.t_begin, t_begin) &&
                iterator_equal(t_range.t_end, t_end));

            _t_key._t_unit = _KB;
            _t_key._un_number = 1;
            t_begin = map_lower_bound(pt_map, &_t_key);
            t_end = map_upper_bound(pt_map, &_t_key);
            t_range = map_equal_range(pt_map, &_t_key);
            assert(iterator_equal(t_begin, iterator_prev(t_end)) &&
                iterator_equal(t_range.t_begin, t_begin) &&
                iterator_equal(t_range.t_end, t_end));

            map_destroy(pt_map);
            pair_destroy(pt_pair);
        }
        /*map_at                */
        {
            map_t* pt_map = create_map(_mapkey_t, _mapvalue_t);
            pair_t* pt_pair = create_pair(_mapkey_t, _mapvalue_t);
            _mapkey_t _t_key;
            _mapvalue_t _t_value;
            if(pt_map == NULL || pt_pair == NULL)
            {
                return;
            }
            map_init(pt_map);
            pair_init(pt_pair);

            _t_key._t_unit = _B;
            _t_key._un_number = 1025;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "Modem");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);

            _t_key._t_unit = _KB;
            _t_key._un_number = 1;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "Modem");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);

            _t_key._t_unit = _MB;
            _t_key._un_number = 1;
            strcpy(_t_value._s_enviroment, "Download");
            strcpy(_t_value._s_condition, "PPPoE");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);

            _t_key._t_unit = _KB;
            _t_key._un_number = 9;
            strcpy(_t_value._s_enviroment, "Download");
            strcpy(_t_value._s_condition, "Modem");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);
            _print_map_user(pt_map);

            _t_key._t_unit = _KB;
            _t_key._un_number = 1;
            strcpy(((_mapvalue_t*)map_at(pt_map, &_t_key))->_s_enviroment, "FTP");
            strcpy(((_mapvalue_t*)map_at(pt_map, &_t_key))->_s_condition, "3G");

            _t_key._t_unit = _KB;
            _t_key._un_number = 100;
            strcpy(((_mapvalue_t*)map_at(pt_map, &_t_key))->_s_enviroment, "FTP");
            strcpy(((_mapvalue_t*)map_at(pt_map, &_t_key))->_s_condition, "3G");
            _print_map_user(pt_map);

            map_destroy(pt_map);
            pair_destroy(pt_pair);
        }
        /*map_insert            */
        {
            map_t* pt_map = create_map(_mapkey_t, _mapvalue_t);
            pair_t* pt_pair = create_pair(_mapkey_t, _mapvalue_t);
            _mapkey_t _t_key;
            _mapvalue_t _t_value;
            if(pt_map == NULL || pt_pair == NULL)
            {
                return;
            }
            map_init(pt_map);
            pair_init(pt_pair);

            _print_map_user(pt_map);

            _t_key._t_unit = _B;
            _t_key._un_number = 1025;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "Modem");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);

            _t_key._t_unit = _KB;
            _t_key._un_number = 1;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "Modem");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);

            _t_key._t_unit = _MB;
            _t_key._un_number = 1;
            strcpy(_t_value._s_enviroment, "Download");
            strcpy(_t_value._s_condition, "PPPoE");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);

            _t_key._t_unit = _KB;
            _t_key._un_number = 9;
            strcpy(_t_value._s_enviroment, "Download");
            strcpy(_t_value._s_condition, "Modem");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);

            _t_key._t_unit = _KB;
            _t_key._un_number = 1024;
            strcpy(_t_value._s_enviroment, "Download");
            strcpy(_t_value._s_condition, "Modem");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);

            _print_map_user(pt_map);

            map_destroy(pt_map);
            pair_destroy(pt_pair);
        }
        /*map_insert_hint       */
        {
            map_t* pt_map = create_map(_mapkey_t, _mapvalue_t);
            pair_t* pt_pair = create_pair(_mapkey_t, _mapvalue_t);
            _mapkey_t _t_key;
            _mapvalue_t _t_value;
            iterator_t t_iter;
            if(pt_map == NULL || pt_pair == NULL)
            {
                return;
            }
            map_init(pt_map);
            pair_init(pt_pair);
            t_iter = map_begin(pt_map);

            _print_map_user(pt_map);

            _t_key._t_unit = _B;
            _t_key._un_number = 1025;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "Modem");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert_hint(pt_map, t_iter, pt_pair);

            _t_key._t_unit = _KB;
            _t_key._un_number = 1;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "Modem");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert_hint(pt_map, t_iter, pt_pair);

            _t_key._t_unit = _MB;
            _t_key._un_number = 1;
            strcpy(_t_value._s_enviroment, "Download");
            strcpy(_t_value._s_condition, "PPPoE");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert_hint(pt_map, t_iter, pt_pair);

            _t_key._t_unit = _KB;
            _t_key._un_number = 9;
            strcpy(_t_value._s_enviroment, "Download");
            strcpy(_t_value._s_condition, "Modem");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert_hint(pt_map, t_iter, pt_pair);

            _t_key._t_unit = _KB;
            _t_key._un_number = 1024;
            strcpy(_t_value._s_enviroment, "Download");
            strcpy(_t_value._s_condition, "Modem");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert_hint(pt_map, t_iter, pt_pair);

            _print_map_user(pt_map);

            map_destroy(pt_map);
            pair_destroy(pt_pair);
        }
        /*map_insert_range      */
        {
            map_t* pt_map = create_map(_mapkey_t, _mapvalue_t);
            map_t* pt_mapex = create_map(_mapkey_t, _mapvalue_t);
            pair_t* pt_pair = create_pair(struct _tagmapkey, struct _tagmapvalue);
            _mapkey_t _t_key;
            _mapvalue_t _t_value;
            if(pt_map == NULL || pt_mapex == NULL || pt_pair == NULL)
            {
                return;
            }
            map_init(pt_mapex);
            map_init_ex(pt_map, _mapkey_number_great);
            pair_init(pt_pair);

            map_insert_range(pt_map, map_begin(pt_mapex), map_end(pt_mapex));
            _print_map_user(pt_map);

            _t_key._t_unit = _B;
            _t_key._un_number = 89;
            strcpy(_t_value._s_enviroment, "Download");
            strcpy(_t_value._s_condition, "3G");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_mapex, pt_pair);

            _t_key._t_unit = _MB;
            _t_key._un_number = 2;
            strcpy(_t_value._s_enviroment, "Download");
            strcpy(_t_value._s_condition, "3G");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_mapex, pt_pair);

            _t_key._t_unit = _KB;
            _t_key._un_number = 5100;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "PPPoE");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_mapex, pt_pair);

            _t_key._t_unit = _KB;
            _t_key._un_number = 0;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "Modem");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_mapex, pt_pair);

            _t_key._t_unit = _B;
            _t_key._un_number = 1025;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "Modem");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_mapex, pt_pair);

            _t_key._t_unit = _KB;
            _t_key._un_number = 1;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "Modem");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_mapex, pt_pair);

            _t_key._t_unit = _MB;
            _t_key._un_number = 1;
            strcpy(_t_value._s_enviroment, "Download");
            strcpy(_t_value._s_condition, "PPPoE");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_mapex, pt_pair);
            _print_map_user(pt_mapex);

            map_insert_range(pt_map, map_begin(pt_mapex), map_begin(pt_mapex));
            _print_map_user(pt_map);
            map_insert_range(pt_map, map_begin(pt_mapex),
                iterator_advance(map_begin(pt_mapex), 3));
            _print_map_user(pt_map);
            map_insert_range(pt_map, iterator_advance(map_begin(pt_mapex), 4), 
                iterator_advance(map_begin(pt_mapex), 5));
            _print_map_user(pt_map);
            map_insert_range(pt_map, iterator_advance(map_begin(pt_mapex), 6),
                map_end(pt_mapex));
            _print_map_user(pt_map);
            map_insert_range(pt_map, map_end(pt_mapex), map_end(pt_mapex));
            _print_map_user(pt_map);
            map_clear(pt_map);
            map_insert_range(pt_map, map_begin(pt_mapex), map_end(pt_mapex));
            _print_map_user(pt_map);

            map_destroy(pt_map);
            map_destroy(pt_mapex);
            pair_destroy(pt_pair);
        }
        /*map_erase             */
        {
            map_t* pt_map = create_map(_mapkey_t, _mapvalue_t);
            pair_t* pt_pair = create_pair(struct _tagmapkey, struct _tagmapvalue);
            _mapkey_t _t_key;
            _mapvalue_t _t_value;
            if(pt_map == NULL || pt_pair == NULL)
            {
                return;
            }
            map_init_ex(pt_map, _mapkey_number_great);
            pair_init(pt_pair);

            map_erase(pt_map, &_t_key);
            _print_map_user(pt_map);

            _t_key._t_unit = _B;
            _t_key._un_number = 89;
            strcpy(_t_value._s_enviroment, "Download");
            strcpy(_t_value._s_condition, "3G");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);

            _t_key._t_unit = _MB;
            _t_key._un_number = 2;
            strcpy(_t_value._s_enviroment, "Download");
            strcpy(_t_value._s_condition, "3G");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);

            _t_key._t_unit = _KB;
            _t_key._un_number = 5100;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "PPPoE");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);

            _t_key._t_unit = _KB;
            _t_key._un_number = 0;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "Modem");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);

            _t_key._t_unit = _B;
            _t_key._un_number = 1025;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "Modem");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);

            _t_key._t_unit = _KB;
            _t_key._un_number = 1;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "Modem");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);

            _t_key._t_unit = _MB;
            _t_key._un_number = 1;
            strcpy(_t_value._s_enviroment, "Download");
            strcpy(_t_value._s_condition, "PPPoE");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);
            _print_map_user(pt_map);

            _t_key._t_unit = _KB;
            _t_key._un_number = 11;
            map_erase(pt_map, &_t_key);
            _print_map_user(pt_map);

            _t_key._t_unit = _KB;
            _t_key._un_number = 0;
            map_erase(pt_map, &_t_key);
            _print_map_user(pt_map);

            map_destroy(pt_map);
            pair_destroy(pt_pair);
        }
        /*map_erase_pos         */
        {
            map_t* pt_map = create_map(_mapkey_t, _mapvalue_t);
            pair_t* pt_pair = create_pair(struct _tagmapkey, struct _tagmapvalue);
            _mapkey_t _t_key;
            _mapvalue_t _t_value;
            if(pt_map == NULL || pt_pair == NULL)
            {
                return;
            }
            map_init(pt_map);
            pair_init(pt_pair);

            _t_key._t_unit = _B;
            _t_key._un_number = 89;
            strcpy(_t_value._s_enviroment, "Download");
            strcpy(_t_value._s_condition, "3G");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);

            _t_key._t_unit = _MB;
            _t_key._un_number = 2;
            strcpy(_t_value._s_enviroment, "Download");
            strcpy(_t_value._s_condition, "3G");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);

            _t_key._t_unit = _KB;
            _t_key._un_number = 5100;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "PPPoE");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);

            _t_key._t_unit = _KB;
            _t_key._un_number = 0;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "Modem");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);

            _t_key._t_unit = _B;
            _t_key._un_number = 1025;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "Modem");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);

            _t_key._t_unit = _KB;
            _t_key._un_number = 1;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "Modem");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);

            _t_key._t_unit = _MB;
            _t_key._un_number = 1;
            strcpy(_t_value._s_enviroment, "Download");
            strcpy(_t_value._s_condition, "PPPoE");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);
            _print_map_user(pt_map);

            map_erase_pos(pt_map, map_begin(pt_map));
            _print_map_user(pt_map);
            map_erase_pos(pt_map, iterator_prev(map_end(pt_map)));
            _print_map_user(pt_map);
            map_erase_pos(pt_map, iterator_advance(map_begin(pt_map), 3));
            _print_map_user(pt_map);
            while(!map_empty(pt_map))
            {
                map_erase_pos(pt_map, map_begin(pt_map));
            }
            _print_map_user(pt_map);

            map_destroy(pt_map);
            pair_destroy(pt_pair);
        }
        /*map_erase_range       */
        {
            map_t* pt_map = create_map(_mapkey_t, _mapvalue_t);
            pair_t* pt_pair = create_pair(struct _tagmapkey, struct _tagmapvalue);
            _mapkey_t _t_key;
            _mapvalue_t _t_value;
            if(pt_map == NULL || pt_pair == NULL)
            {
                return;
            }
            map_init(pt_map);
            pair_init(pt_pair);

            map_erase_range(pt_map, map_begin(pt_map), map_end(pt_map));
            _print_map_user(pt_map);

            _t_key._t_unit = _B;
            _t_key._un_number = 89;
            strcpy(_t_value._s_enviroment, "Download");
            strcpy(_t_value._s_condition, "3G");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);

            _t_key._t_unit = _MB;
            _t_key._un_number = 2;
            strcpy(_t_value._s_enviroment, "Download");
            strcpy(_t_value._s_condition, "3G");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);

            _t_key._t_unit = _KB;
            _t_key._un_number = 5100;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "PPPoE");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);

            _t_key._t_unit = _KB;
            _t_key._un_number = 0;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "Modem");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);

            _t_key._t_unit = _B;
            _t_key._un_number = 1025;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "Modem");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);

            _t_key._t_unit = _KB;
            _t_key._un_number = 1;
            strcpy(_t_value._s_enviroment, "Upload");
            strcpy(_t_value._s_condition, "Modem");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);

            _t_key._t_unit = _MB;
            _t_key._un_number = 1;
            strcpy(_t_value._s_enviroment, "Download");
            strcpy(_t_value._s_condition, "PPPoE");
            pair_make(pt_pair, &_t_key, &_t_value);
            map_insert(pt_map, pt_pair);
            _print_map_user(pt_map);

            map_erase_range(pt_map, map_begin(pt_map), map_begin(pt_map));
            _print_map_user(pt_map);
            map_erase_range(pt_map, map_begin(pt_map), iterator_advance(map_begin(pt_map), 2));
            _print_map_user(pt_map);
            map_erase_range(pt_map, iterator_next(map_begin(pt_map)),
                iterator_advance(map_begin(pt_map), 3));
            _print_map_user(pt_map);
            map_erase_range(pt_map, iterator_advance(map_begin(pt_map), 2), map_end(pt_map));
            _print_map_user(pt_map);
            map_erase_range(pt_map, map_end(pt_map), map_end(pt_map));
            _print_map_user(pt_map);
            map_erase_range(pt_map, map_begin(pt_map), map_end(pt_map));
            _print_map_user(pt_map);

            map_destroy(pt_map);
            pair_destroy(pt_pair);
        }
    }
    /* cstl built-in types */
    {
        /*create_map            */
        {
            map_t* pt_map = create_map(pair_t<int, double>, list_t<long>);
            pair_t* pt_pair = create_pair(pair_t<int, double>, list_t<long>);
            pair_t* pt_key = create_pair(int, double);
            list_t* pt_value = create_list(long);
            if(pt_map == NULL || pt_pair == NULL || pt_key == NULL || pt_value == NULL)
            {
                return;
            }
            map_init(pt_map);
            pair_init(pt_pair);
            pair_init(pt_key);
            list_init(pt_value);

            pair_make(pt_key, 34, 90.2);
            list_push_back(pt_value, 32445);
            list_push_back(pt_value, -37394);
            list_push_back(pt_value, 9090909);
            list_push_back(pt_value, -342134);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);

            pair_make(pt_key, -4, 0.989);
            list_clear(pt_value);
            list_push_back(pt_value, 130000);
            list_push_back(pt_value, 89039);
            list_push_back(pt_value, 2929);
            list_push_back(pt_value, 908728282);
            list_push_back(pt_value, 3222);
            list_push_back(pt_value, 3232222);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);

            _print_map_cstl(pt_map);

            map_destroy(pt_map);
            pair_destroy(pt_pair);
            pair_destroy(pt_key);
            list_destroy(pt_value);
        }
        /*map_init              */
        /*map_init_ex           */
        {
            map_t* pt_map = create_map(pair_t<int, double>, list_t<long>);
            pair_t* pt_pair = create_pair(pair_t<int, double>, list_t<long>);
            pair_t* pt_key = create_pair(int, double);
            list_t* pt_value = create_list(long);
            if(pt_map == NULL || pt_pair == NULL || pt_key == NULL || pt_value == NULL)
            {
                return;
            }
            map_init_ex(pt_map, _mapkey_pair_great);
            pair_init(pt_pair);
            pair_init(pt_key);
            list_init(pt_value);

            pair_make(pt_key, 34, 90.2);
            list_push_back(pt_value, 32445);
            list_push_back(pt_value, -37394);
            list_push_back(pt_value, 9090909);
            list_push_back(pt_value, -342134);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);

            pair_make(pt_key, -4, 0.989);
            list_clear(pt_value);
            list_push_back(pt_value, 130000);
            list_push_back(pt_value, 89039);
            list_push_back(pt_value, 2929);
            list_push_back(pt_value, 908728282);
            list_push_back(pt_value, 3222);
            list_push_back(pt_value, 3232222);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);

            _print_map_cstl(pt_map);

            map_destroy(pt_map);
            pair_destroy(pt_pair);
            pair_destroy(pt_key);
            list_destroy(pt_value);
        }
        /*map_init_copy         */
        {
            map_t* pt_map = create_map(pair_t<int, double>, list_t<long>);
            map_t* pt_mapex = create_map(pair_t<int, double>, list_t<long>);
            pair_t* pt_pair = create_pair(pair_t<int, double>, list_t<long>);
            pair_t* pt_key = create_pair(int, double);
            list_t* pt_value = create_list(long);
            if(pt_map == NULL || pt_mapex == NULL || pt_pair == NULL || pt_key == NULL || pt_value == NULL)
            {
                return;
            }
            map_init_ex(pt_map, _mapkey_pair_great);
            pair_init(pt_pair);
            pair_init(pt_key);
            list_init(pt_value);

            pair_make(pt_key, 34, 90.2);
            list_push_back(pt_value, 32445);
            list_push_back(pt_value, -37394);
            list_push_back(pt_value, 9090909);
            list_push_back(pt_value, -342134);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);

            pair_make(pt_key, -4, 0.989);
            list_clear(pt_value);
            list_push_back(pt_value, 130000);
            list_push_back(pt_value, 89039);
            list_push_back(pt_value, 2929);
            list_push_back(pt_value, 908728282);
            list_push_back(pt_value, 3222);
            list_push_back(pt_value, 3232222);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);

            map_init_copy(pt_mapex, pt_map);
            _print_map_cstl(pt_mapex);

            map_destroy(pt_map);
            map_destroy(pt_mapex);
            pair_destroy(pt_pair);
            pair_destroy(pt_key);
            list_destroy(pt_value);
        }
        /*map_init_copy_range   */
        {
            map_t* pt_map = create_map(pair_t<int, double>, list_t<long>);
            map_t* pt_mapex = create_map(pair_t<int, double>, list_t<long>);
            pair_t* pt_pair = create_pair(pair_t<int, double>, list_t<long>);
            pair_t* pt_key = create_pair(int, double);
            list_t* pt_value = create_list(long);
            if(pt_map == NULL || pt_mapex == NULL || pt_pair == NULL || pt_key == NULL || pt_value == NULL)
            {
                return;
            }
            map_init_ex(pt_mapex, _mapkey_pair_great);
            pair_init(pt_pair);
            pair_init(pt_key);
            list_init(pt_value);

            pair_make(pt_key, 34, 90.2);
            list_push_back(pt_value, 32445);
            list_push_back(pt_value, -37394);
            list_push_back(pt_value, 9090909);
            list_push_back(pt_value, -342134);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);

            pair_make(pt_key, -4, 0.989);
            list_clear(pt_value);
            list_push_back(pt_value, 130000);
            list_push_back(pt_value, 89039);
            list_push_back(pt_value, 2929);
            list_push_back(pt_value, 908728282);
            list_push_back(pt_value, 3222);
            list_push_back(pt_value, 3232222);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);

            pair_make(pt_key, 378, -0.4222);
            list_clear(pt_value);
            list_push_back(pt_value, 902);
            list_push_back(pt_value, 1);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);

            pair_make(pt_key, 378, 0.4222);
            list_clear(pt_value);
            list_push_back(pt_value, 912111);
            list_push_back(pt_value, 11111);
            list_push_back(pt_value, 9022434);
            list_push_back(pt_value, 0);
            list_push_back(pt_value, -748945);
            list_push_back(pt_value, 111);
            list_push_back(pt_value, 111);
            list_push_back(pt_value, 111);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);

            pair_make(pt_key, 378, 4222.0);
            list_clear(pt_value);
            list_push_back(pt_value, 3456789);
            list_push_back(pt_value, 1);
            list_push_back(pt_value, 100);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);

            pair_make(pt_key, -400, 42.220);
            list_clear(pt_value);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);

            pair_make(pt_key, -1300, 42.220);
            list_clear(pt_value);
            list_push_back(pt_value, 1500);
            list_push_back(pt_value, 1300);
            list_push_back(pt_value, 1100);
            list_push_back(pt_value, 900);
            list_push_back(pt_value, 700);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);

            pair_make(pt_key, -400, 1242.220);
            list_clear(pt_value);
            list_push_back(pt_value, 10000);
            list_push_back(pt_value, 20000);
            list_push_back(pt_value, 30000);
            list_push_back(pt_value, 40000);
            list_push_back(pt_value, 50000);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);

            pair_make(pt_key, 456, 0.2);
            list_clear(pt_value);
            list_push_back(pt_value, 0);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);

            pair_make(pt_key, 4, 2.2);
            list_clear(pt_value);
            list_push_back(pt_value, 0);
            list_push_back(pt_value, 0);
            list_push_back(pt_value, 1998);
            list_push_back(pt_value, 2008);
            list_push_back(pt_value, 2018);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);

            pair_make(pt_key, 0, -10000.2);
            list_clear(pt_value);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);

            _print_map_cstl(pt_mapex);
            map_init_copy_range(pt_map, map_begin(pt_mapex), map_end(pt_mapex));
            _print_map_cstl(pt_map);

            map_destroy(pt_map);
            map_destroy(pt_mapex);
            pair_destroy(pt_pair);
            pair_destroy(pt_key);
            list_destroy(pt_value);
        }
        /*map_init_copy_range_ex*/
        {
            map_t* pt_map = create_map(pair_t<int, double>, list_t<long>);
            map_t* pt_mapex = create_map(pair_t<int, double>, list_t<long>);
            pair_t* pt_pair = create_pair(pair_t<int, double>, list_t<long>);
            pair_t* pt_key = create_pair(int, double);
            list_t* pt_value = create_list(long);
            if(pt_map == NULL || pt_mapex == NULL || pt_pair == NULL || pt_key == NULL || pt_value == NULL)
            {
                return;
            }
            map_init(pt_mapex);
            pair_init(pt_pair);
            pair_init(pt_key);
            list_init(pt_value);

            pair_make(pt_key, 34, 90.2);
            list_clear(pt_value);
            list_push_back(pt_value, 32445);
            list_push_back(pt_value, -37394);
            list_push_back(pt_value, 9090909);
            list_push_back(pt_value, -342134);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);

            pair_make(pt_key, -4, 0.989);
            list_clear(pt_value);
            list_push_back(pt_value, 130000);
            list_push_back(pt_value, 89039);
            list_push_back(pt_value, 2929);
            list_push_back(pt_value, 908728282);
            list_push_back(pt_value, 3222);
            list_push_back(pt_value, 3232222);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);

            pair_make(pt_key, 378, -0.4222);
            list_clear(pt_value);
            list_push_back(pt_value, 902);
            list_push_back(pt_value, 1);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);

            pair_make(pt_key, 378, 0.4222);
            list_clear(pt_value);
            list_push_back(pt_value, 912111);
            list_push_back(pt_value, 11111);
            list_push_back(pt_value, 9022434);
            list_push_back(pt_value, 0);
            list_push_back(pt_value, -748945);
            list_push_back(pt_value, 111);
            list_push_back(pt_value, 111);
            list_push_back(pt_value, 111);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);

            pair_make(pt_key, 378, 4222.0);
            list_clear(pt_value);
            list_push_back(pt_value, 3456789);
            list_push_back(pt_value, 1);
            list_push_back(pt_value, 100);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);

            pair_make(pt_key, -400, 42.220);
            list_clear(pt_value);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);

            pair_make(pt_key, -1300, 42.220);
            list_clear(pt_value);
            list_push_back(pt_value, 1500);
            list_push_back(pt_value, 1300);
            list_push_back(pt_value, 1100);
            list_push_back(pt_value, 900);
            list_push_back(pt_value, 700);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);

            pair_make(pt_key, -400, 1242.220);
            list_clear(pt_value);
            list_push_back(pt_value, 10000);
            list_push_back(pt_value, 20000);
            list_push_back(pt_value, 30000);
            list_push_back(pt_value, 40000);
            list_push_back(pt_value, 50000);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);

            pair_make(pt_key, 456, 0.2);
            list_clear(pt_value);
            list_push_back(pt_value, 0);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);

            pair_make(pt_key, 4, 2.2);
            list_clear(pt_value);
            list_push_back(pt_value, 0);
            list_push_back(pt_value, 0);
            list_push_back(pt_value, 1998);
            list_push_back(pt_value, 2008);
            list_push_back(pt_value, 2018);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);

            pair_make(pt_key, 0, -10000.2);
            list_clear(pt_value);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);

            _print_map_cstl(pt_mapex);
            map_init_copy_range_ex(pt_map, map_begin(pt_mapex), map_end(pt_mapex), _mapkey_pair_great);
            _print_map_cstl(pt_map);

            map_destroy(pt_map);
            map_destroy(pt_mapex);
            pair_destroy(pt_pair);
            pair_destroy(pt_key);
            list_destroy(pt_value);
        }
        /*map_destroy           */
        /*map_assign            */
        {
            map_t* pt_map = create_map(pair_t<int, double>, list_t<long>);
            map_t* pt_mapex = create_map(pair_t<int, double>, list_t<long>);
            pair_t* pt_pair = create_pair(pair_t<int, double>, list_t<long>);
            pair_t* pt_key = create_pair(int, double);
            list_t* pt_value = create_list(long);
            if(pt_map == NULL || pt_mapex == NULL || pt_pair == NULL || pt_key == NULL || pt_value == NULL)
            {
                return;
            }
            map_init(pt_mapex);
            map_init(pt_map);
            pair_init(pt_pair);
            pair_init(pt_key);
            list_init(pt_value);

            map_assign(pt_map, pt_mapex);
            _print_map_cstl(pt_map);

            pair_make(pt_key, -400, 1242.220);
            list_clear(pt_value);
            list_push_back(pt_value, 10000);
            list_push_back(pt_value, 20000);
            list_push_back(pt_value, 30000);
            list_push_back(pt_value, 40000);
            list_push_back(pt_value, 50000);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);

            pair_make(pt_key, 456, 0.2);
            list_clear(pt_value);
            list_push_back(pt_value, 0);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);

            pair_make(pt_key, 4, 2.2);
            list_clear(pt_value);
            list_push_back(pt_value, 0);
            list_push_back(pt_value, 0);
            list_push_back(pt_value, 1998);
            list_push_back(pt_value, 2008);
            list_push_back(pt_value, 2018);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);
            map_assign(pt_map, pt_mapex);
            _print_map_cstl(pt_map);

            map_clear(pt_mapex);
            pair_make(pt_key, 34, 90.2);
            list_clear(pt_value);
            list_push_back(pt_value, 32445);
            list_push_back(pt_value, -37394);
            list_push_back(pt_value, 9090909);
            list_push_back(pt_value, -342134);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);

            pair_make(pt_key, -4, 0.989);
            list_clear(pt_value);
            list_push_back(pt_value, 130000);
            list_push_back(pt_value, 89039);
            list_push_back(pt_value, 2929);
            list_push_back(pt_value, 908728282);
            list_push_back(pt_value, 3222);
            list_push_back(pt_value, 3232222);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);

            pair_make(pt_key, 378, -0.4222);
            list_clear(pt_value);
            list_push_back(pt_value, 902);
            list_push_back(pt_value, 1);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);

            pair_make(pt_key, 378, 0.4222);
            list_clear(pt_value);
            list_push_back(pt_value, 912111);
            list_push_back(pt_value, 11111);
            list_push_back(pt_value, 9022434);
            list_push_back(pt_value, 0);
            list_push_back(pt_value, -748945);
            list_push_back(pt_value, 111);
            list_push_back(pt_value, 111);
            list_push_back(pt_value, 111);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);

            pair_make(pt_key, 378, 4222.0);
            list_clear(pt_value);
            list_push_back(pt_value, 3456789);
            list_push_back(pt_value, 1);
            list_push_back(pt_value, 100);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);
            map_assign(pt_map, pt_mapex);
            _print_map_cstl(pt_map);

            map_clear(pt_mapex);
            pair_make(pt_key, 0, -10000.2);
            list_clear(pt_value);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);
            map_assign(pt_map, pt_mapex);
            _print_map_cstl(pt_map);

            map_clear(pt_mapex);
            map_assign(pt_map, pt_mapex);
            _print_map_cstl(pt_map);

            map_destroy(pt_map);
            map_destroy(pt_mapex);
            pair_destroy(pt_pair);
            pair_destroy(pt_key);
            list_destroy(pt_value);
        }
        /*map_swap              */
        {
            map_t* pt_map = create_map(pair_t<int, double>, list_t<long>);
            map_t* pt_mapex = create_map(pair_t<int, double>, list_t<long>);
            pair_t* pt_pair = create_pair(pair_t<int, double>, list_t<long>);
            pair_t* pt_key = create_pair(int, double);
            list_t* pt_value = create_list(long);
            if(pt_map == NULL || pt_mapex == NULL || pt_pair == NULL || pt_key == NULL || pt_value == NULL)
            {
                return;
            }
            map_init(pt_mapex);
            map_init(pt_map);
            pair_init(pt_pair);
            pair_init(pt_key);
            list_init(pt_value);

            map_swap(pt_map, pt_mapex);
            _print_map_cstl(pt_map);
            _print_map_cstl(pt_mapex);

            pair_make(pt_key, -400, 1242.220);
            list_clear(pt_value);
            list_push_back(pt_value, 10000);
            list_push_back(pt_value, 20000);
            list_push_back(pt_value, 30000);
            list_push_back(pt_value, 40000);
            list_push_back(pt_value, 50000);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);

            pair_make(pt_key, 456, 0.2);
            list_clear(pt_value);
            list_push_back(pt_value, 0);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);

            pair_make(pt_key, 4, 2.2);
            list_clear(pt_value);
            list_push_back(pt_value, 0);
            list_push_back(pt_value, 0);
            list_push_back(pt_value, 1998);
            list_push_back(pt_value, 2008);
            list_push_back(pt_value, 2018);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);
            map_swap(pt_map, pt_mapex);
            _print_map_cstl(pt_map);
            _print_map_cstl(pt_mapex);

            map_clear(pt_mapex);
            pair_make(pt_key, 34, 90.2);
            list_clear(pt_value);
            list_push_back(pt_value, 32445);
            list_push_back(pt_value, -37394);
            list_push_back(pt_value, 9090909);
            list_push_back(pt_value, -342134);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);

            pair_make(pt_key, -4, 0.989);
            list_clear(pt_value);
            list_push_back(pt_value, 130000);
            list_push_back(pt_value, 89039);
            list_push_back(pt_value, 2929);
            list_push_back(pt_value, 908728282);
            list_push_back(pt_value, 3222);
            list_push_back(pt_value, 3232222);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);

            pair_make(pt_key, 378, -0.4222);
            list_clear(pt_value);
            list_push_back(pt_value, 902);
            list_push_back(pt_value, 1);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);

            pair_make(pt_key, 378, 0.4222);
            list_clear(pt_value);
            list_push_back(pt_value, 912111);
            list_push_back(pt_value, 11111);
            list_push_back(pt_value, 9022434);
            list_push_back(pt_value, 0);
            list_push_back(pt_value, -748945);
            list_push_back(pt_value, 111);
            list_push_back(pt_value, 111);
            list_push_back(pt_value, 111);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);

            pair_make(pt_key, 378, 4222.0);
            list_clear(pt_value);
            list_push_back(pt_value, 3456789);
            list_push_back(pt_value, 1);
            list_push_back(pt_value, 100);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);
            map_swap(pt_map, pt_mapex);
            _print_map_cstl(pt_map);
            _print_map_cstl(pt_mapex);

            map_clear(pt_mapex);
            pair_make(pt_key, 0, -10000.2);
            list_clear(pt_value);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);
            map_swap(pt_map, pt_mapex);
            _print_map_cstl(pt_map);
            _print_map_cstl(pt_mapex);

            map_clear(pt_mapex);
            map_swap(pt_map, pt_mapex);
            _print_map_cstl(pt_map);
            _print_map_cstl(pt_mapex);

            map_destroy(pt_map);
            map_destroy(pt_mapex);
            pair_destroy(pt_pair);
            pair_destroy(pt_key);
            list_destroy(pt_value);
        }
        /*map_size              */
        /*map_empty             */
        /*map_max_size          */
        /*map_key_less          */
        /*map_value_less        */
        {
            map_t* pt_map = create_map(pair_t<int, double>, list_t<long>);
            if(pt_map == NULL)
            {
                return;
            }
            map_init_ex(pt_map, _mapkey_pair_great);
            assert(map_key_less(pt_map) == _mapkey_pair_great &&
                map_key_less(pt_map) != map_value_less(pt_map));
            map_destroy(pt_map);
        }
        /*map_clear             */
        {
            map_t* pt_map = create_map(pair_t<int, double>, list_t<long>);
            pair_t* pt_pair = create_pair(pair_t<int, double>, list_t<long>);
            pair_t* pt_key = create_pair(int, double);
            list_t* pt_value = create_list(long);
            if(pt_map == NULL || pt_pair == NULL || pt_key == NULL || pt_value == NULL)
            {
                return;
            }
            map_init(pt_map);
            pair_init(pt_pair);
            pair_init(pt_key);
            list_init(pt_value);

            map_clear(pt_map);
            _print_map_cstl(pt_map);

            pair_make(pt_key, 378, -0.4222);
            list_clear(pt_value);
            list_push_back(pt_value, 902);
            list_push_back(pt_value, 1);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);

            pair_make(pt_key, 378, 0.4222);
            list_clear(pt_value);
            list_push_back(pt_value, 912111);
            list_push_back(pt_value, 11111);
            list_push_back(pt_value, 9022434);
            list_push_back(pt_value, 0);
            list_push_back(pt_value, -748945);
            list_push_back(pt_value, 111);
            list_push_back(pt_value, 111);
            list_push_back(pt_value, 111);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);

            pair_make(pt_key, 378, 4222.0);
            list_clear(pt_value);
            list_push_back(pt_value, 3456789);
            list_push_back(pt_value, 1);
            list_push_back(pt_value, 100);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);
            _print_map_cstl(pt_map);

            map_clear(pt_map);
            _print_map_cstl(pt_map);

            map_destroy(pt_map);
            pair_destroy(pt_pair);
            pair_destroy(pt_key);
            list_destroy(pt_value);
        }
        /*map_equal             */
        /*map_not_equal         */
        /*map_less              */
        /*map_less_equal        */
        /*map_great             */
        /*map_great_equal       */
        {
            map_t* pt_map = create_map(pair_t<int, double>, list_t<long>);
            map_t* pt_mapex = create_map(pair_t<int, double>, list_t<long>);
            pair_t* pt_pair = create_pair(pair_t<int, double>, list_t<long>);
            pair_t* pt_key = create_pair(int, double);
            list_t* pt_value = create_list(long);
            if(pt_map == NULL || pt_mapex == NULL || pt_pair == NULL || pt_key == NULL || pt_value == NULL)
            {
                return;
            }
            map_init(pt_mapex);
            map_init(pt_map);
            pair_init(pt_pair);
            pair_init(pt_key);
            list_init(pt_value);

            _print_map_cstl(pt_map);
            _print_map_cstl(pt_mapex);
            printf("equal: %d, not equal: %d, ",
                map_equal(pt_map, pt_mapex), map_not_equal(pt_map, pt_mapex));
            printf("less: %d, less equal: %d, ",
                map_less(pt_map, pt_mapex), map_less_equal(pt_map, pt_mapex));
            printf("great: %d, great equal: %d\n",
                map_great(pt_map, pt_mapex), map_great_equal(pt_map, pt_mapex));

            pair_make(pt_key, 378, 4222.0);
            list_clear(pt_value);
            list_push_back(pt_value, 3456789);
            list_push_back(pt_value, 1);
            list_push_back(pt_value, 100);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);
            _print_map_cstl(pt_map);
            _print_map_cstl(pt_mapex);
            printf("equal: %d, not equal: %d, ",
                map_equal(pt_map, pt_mapex), map_not_equal(pt_map, pt_mapex));
            printf("less: %d, less equal: %d, ",
                map_less(pt_map, pt_mapex), map_less_equal(pt_map, pt_mapex));
            printf("great: %d, great equal: %d\n",
                map_great(pt_map, pt_mapex), map_great_equal(pt_map, pt_mapex));

            map_insert(pt_mapex, pt_pair);
            _print_map_cstl(pt_map);
            _print_map_cstl(pt_mapex);
            printf("equal: %d, not equal: %d, ",
                map_equal(pt_map, pt_mapex), map_not_equal(pt_map, pt_mapex));
            printf("less: %d, less equal: %d, ",
                map_less(pt_map, pt_mapex), map_less_equal(pt_map, pt_mapex));
            printf("great: %d, great equal: %d\n",
                map_great(pt_map, pt_mapex), map_great_equal(pt_map, pt_mapex));

            pair_make(pt_key, 0, -10000.2);
            list_clear(pt_value);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);

            pair_make(pt_key, -4, 0.989);
            list_clear(pt_value);
            list_push_back(pt_value, 130000);
            list_push_back(pt_value, 89039);
            list_push_back(pt_value, 2929);
            list_push_back(pt_value, 908728282);
            list_push_back(pt_value, 3222);
            list_push_back(pt_value, 3232222);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);

            pair_make(pt_key, 34, 90.2);
            list_clear(pt_value);
            list_push_back(pt_value, 32445);
            list_push_back(pt_value, -37394);
            list_push_back(pt_value, 9090909);
            list_push_back(pt_value, -342134);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);

            _print_map_cstl(pt_map);
            _print_map_cstl(pt_mapex);
            printf("equal: %d, not equal: %d, ",
                map_equal(pt_map, pt_mapex), map_not_equal(pt_map, pt_mapex));
            printf("less: %d, less equal: %d, ",
                map_less(pt_map, pt_mapex), map_less_equal(pt_map, pt_mapex));
            printf("great: %d, great equal: %d\n",
                map_great(pt_map, pt_mapex), map_great_equal(pt_map, pt_mapex));

            map_destroy(pt_map);
            map_destroy(pt_mapex);
            pair_destroy(pt_pair);
            pair_destroy(pt_key);
            list_destroy(pt_value);
        }
        /*map_begin             */
        /*map_end               */
        /*map_find              */
        /*map_count             */
        {
            map_t* pt_map = create_map(pair_t<int, double>, list_t<long>);
            pair_t* pt_pair = create_pair(pair_t<int, double>, list_t<long>);
            pair_t* pt_key = create_pair(int, double);
            list_t* pt_value = create_list(long);
            iterator_t t_iter;
            if(pt_map == NULL || pt_pair == NULL || pt_key == NULL || pt_value == NULL)
            {
                return;
            }
            map_init(pt_map);
            pair_init(pt_pair);
            pair_init(pt_key);
            list_init(pt_value);

            t_iter = map_find(pt_map, pt_key);
            if(iterator_equal(t_iter, map_end(pt_map)))
            {
                printf("not found, count: %u\n", map_count(pt_map, pt_key));
            }
            else
            {
                printf("found, count: %u\n", map_count(pt_map, pt_key));
            }

            pair_make(pt_key, 0, -10000.2);
            list_clear(pt_value);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);

            pair_make(pt_key, -4, 0.989);
            list_clear(pt_value);
            list_push_back(pt_value, 130000);
            list_push_back(pt_value, 89039);
            list_push_back(pt_value, 2929);
            list_push_back(pt_value, 908728282);
            list_push_back(pt_value, 3222);
            list_push_back(pt_value, 3232222);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);

            pair_make(pt_key, 34, 90.2);
            list_clear(pt_value);
            list_push_back(pt_value, 32445);
            list_push_back(pt_value, -37394);
            list_push_back(pt_value, 9090909);
            list_push_back(pt_value, -342134);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);

            pair_make(pt_key, 88, 88.88);
            t_iter = map_find(pt_map, pt_key);
            if(iterator_equal(t_iter, map_end(pt_map)))
            {
                printf("not found, count: %u\n", map_count(pt_map, pt_key));
            }
            else
            {
                printf("found, count: %u\n", map_count(pt_map, pt_key));
            }
            pair_make(pt_key, 0, -10000.2);
            t_iter = map_find(pt_map, pt_key);
            if(iterator_equal(t_iter, map_end(pt_map)))
            {
                printf("not found, count: %u\n", map_count(pt_map, pt_key));
            }
            else
            {
                printf("found, count: %u\n", map_count(pt_map, pt_key));
            }

            map_destroy(pt_map);
            pair_destroy(pt_pair);
            pair_destroy(pt_key);
            list_destroy(pt_value);
        }
        /*map_lower_bound       */
        /*map_upper_bound       */
        /*map_equal_range       */
        {
            map_t* pt_map = create_map(pair_t<int, double>, list_t<long>);
            pair_t* pt_pair = create_pair(pair_t<int, double>, list_t<long>);
            pair_t* pt_key = create_pair(int, double);
            list_t* pt_value = create_list(long);
            iterator_t t_begin;
            iterator_t t_end;
            range_t t_range;
            if(pt_map == NULL || pt_pair == NULL || pt_key == NULL || pt_value == NULL)
            {
                return;
            }
            map_init(pt_map);
            pair_init(pt_pair);
            pair_init(pt_key);
            list_init(pt_value);

            t_begin = map_lower_bound(pt_map, pt_key);
            t_end = map_upper_bound(pt_map, pt_key);
            t_range = map_equal_range(pt_map, pt_key);
            assert(iterator_equal(t_begin, map_end(pt_map)) &&
                iterator_equal(t_begin, t_end) &&
                iterator_equal(t_range.t_begin, t_begin) &&
                iterator_equal(t_range.t_end, t_end));

            pair_make(pt_key, 0, -10000.2);
            list_clear(pt_value);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);

            pair_make(pt_key, -4, 0.989);
            list_clear(pt_value);
            list_push_back(pt_value, 130000);
            list_push_back(pt_value, 89039);
            list_push_back(pt_value, 2929);
            list_push_back(pt_value, 908728282);
            list_push_back(pt_value, 3222);
            list_push_back(pt_value, 3232222);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);

            pair_make(pt_key, 34, 90.2);
            list_clear(pt_value);
            list_push_back(pt_value, 32445);
            list_push_back(pt_value, -37394);
            list_push_back(pt_value, 9090909);
            list_push_back(pt_value, -342134);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);

            pair_make(pt_key, 8, 88.88);
            t_begin = map_lower_bound(pt_map, pt_key);
            t_end = map_upper_bound(pt_map, pt_key);
            t_range = map_equal_range(pt_map, pt_key);
            assert(iterator_equal(t_begin, t_end) &&
                iterator_equal(t_range.t_begin, t_begin) &&
                iterator_equal(t_range.t_end, t_end));

            pair_make(pt_key, 0, -10000.2);
            t_begin = map_lower_bound(pt_map, pt_key);
            t_end = map_upper_bound(pt_map, pt_key);
            t_range = map_equal_range(pt_map, pt_key);
            assert(iterator_equal(t_begin, iterator_prev(t_end)) &&
                iterator_equal(t_range.t_begin, t_begin) &&
                iterator_equal(t_range.t_end, t_end));

            map_destroy(pt_map);
            pair_destroy(pt_pair);
            pair_destroy(pt_key);
            list_destroy(pt_value);
        }
        /*map_at                */
        {
            map_t* pt_map = create_map(pair_t<int, double>, list_t<long>);
            pair_t* pt_pair = create_pair(pair_t<int, double>, list_t<long>);
            pair_t* pt_key = create_pair(int, double);
            list_t* pt_value = create_list(long);
            if(pt_map == NULL || pt_pair == NULL || pt_key == NULL || pt_value == NULL)
            {
                return;
            }
            map_init(pt_map);
            pair_init(pt_pair);
            pair_init(pt_key);
            list_init(pt_value);

            pair_make(pt_key, 0, -10000.2);
            list_clear(pt_value);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);

            pair_make(pt_key, -4, 0.989);
            list_clear(pt_value);
            list_push_back(pt_value, 130000);
            list_push_back(pt_value, 89039);
            list_push_back(pt_value, 2929);
            list_push_back(pt_value, 908728282);
            list_push_back(pt_value, 3222);
            list_push_back(pt_value, 3232222);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);

            pair_make(pt_key, 34, 90.2);
            list_clear(pt_value);
            list_push_back(pt_value, 32445);
            list_push_back(pt_value, -37394);
            list_push_back(pt_value, 9090909);
            list_push_back(pt_value, -342134);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);
            _print_map_cstl(pt_map);

            pair_make(pt_key, 0, -10000.2);
            list_clear((list_t*)map_at(pt_map, pt_key));
            pair_make(pt_key, 8, 88.88);
            list_push_back((list_t*)map_at(pt_map, pt_key), 100);
            list_push_back((list_t*)map_at(pt_map, pt_key), 200);
            _print_map_cstl(pt_map);

            map_destroy(pt_map);
            pair_destroy(pt_pair);
            pair_destroy(pt_key);
            list_destroy(pt_value);
        }
        /*map_insert            */
        {
            map_t* pt_map = create_map(pair_t<int, double>, list_t<long>);
            pair_t* pt_pair = create_pair(pair_t<int, double>, list_t<long>);
            pair_t* pt_key = create_pair(int, double);
            list_t* pt_value = create_list(long);
            if(pt_map == NULL || pt_pair == NULL || pt_key == NULL || pt_value == NULL)
            {
                return;
            }
            map_init(pt_map);
            pair_init(pt_pair);
            pair_init(pt_key);
            list_init(pt_value);
            _print_map_cstl(pt_map);

            pair_make(pt_key, 0, -10000.2);
            list_clear(pt_value);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);

            pair_make(pt_key, -4, 0.989);
            list_clear(pt_value);
            list_push_back(pt_value, 130000);
            list_push_back(pt_value, 89039);
            list_push_back(pt_value, 2929);
            list_push_back(pt_value, 908728282);
            list_push_back(pt_value, 3222);
            list_push_back(pt_value, 3232222);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);

            pair_make(pt_key, -4, 0.989);
            list_clear(pt_value);
            list_push_back(pt_value, 100);
            list_push_back(pt_value, 89);
            list_push_back(pt_value, 2);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);

            pair_make(pt_key, 34, 90.2);
            list_clear(pt_value);
            list_push_back(pt_value, 32445);
            list_push_back(pt_value, -37394);
            list_push_back(pt_value, 9090909);
            list_push_back(pt_value, -342134);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);
            _print_map_cstl(pt_map);

            map_destroy(pt_map);
            pair_destroy(pt_pair);
            pair_destroy(pt_key);
            list_destroy(pt_value);
        }
        /*map_insert_hint       */
        {
            map_t* pt_map = create_map(pair_t<int, double>, list_t<long>);
            pair_t* pt_pair = create_pair(pair_t<int, double>, list_t<long>);
            pair_t* pt_key = create_pair(int, double);
            list_t* pt_value = create_list(long);
            iterator_t t_iter;
            if(pt_map == NULL || pt_pair == NULL || pt_key == NULL || pt_value == NULL)
            {
                return;
            }
            map_init(pt_map);
            pair_init(pt_pair);
            pair_init(pt_key);
            list_init(pt_value);
            _print_map_cstl(pt_map);
            t_iter = map_begin(pt_map);

            pair_make(pt_key, 0, -10000.2);
            list_clear(pt_value);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert_hint(pt_map, t_iter, pt_pair);

            pair_make(pt_key, -4, 0.989);
            list_clear(pt_value);
            list_push_back(pt_value, 130000);
            list_push_back(pt_value, 89039);
            list_push_back(pt_value, 2929);
            list_push_back(pt_value, 908728282);
            list_push_back(pt_value, 3222);
            list_push_back(pt_value, 3232222);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert_hint(pt_map, t_iter, pt_pair);

            pair_make(pt_key, -4, 0.989);
            list_clear(pt_value);
            list_push_back(pt_value, 100);
            list_push_back(pt_value, 89);
            list_push_back(pt_value, 2);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert_hint(pt_map, t_iter, pt_pair);

            pair_make(pt_key, 34, 90.2);
            list_clear(pt_value);
            list_push_back(pt_value, 32445);
            list_push_back(pt_value, -37394);
            list_push_back(pt_value, 9090909);
            list_push_back(pt_value, -342134);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert_hint(pt_map, t_iter, pt_pair);
            _print_map_cstl(pt_map);

            map_destroy(pt_map);
            pair_destroy(pt_pair);
            pair_destroy(pt_key);
            list_destroy(pt_value);
        }
        /*map_insert_range      */
        {
            map_t* pt_map = create_map(pair_t<int, double>, list_t<long>);
            map_t* pt_mapex = create_map(pair_t<int, double>, list_t<long>);
            pair_t* pt_pair = create_pair(pair_t<int, double>, list_t<long>);
            pair_t* pt_key = create_pair(int, double);
            list_t* pt_value = create_list(long);
            if(pt_map == NULL || pt_mapex == NULL || pt_pair == NULL || pt_key == NULL || pt_value == NULL)
            {
                return;
            }
            map_init_ex(pt_mapex, _mapkey_pair_great);
            map_init(pt_map);
            pair_init(pt_pair);
            pair_init(pt_key);
            list_init(pt_value);

            map_insert_range(pt_map, map_begin(pt_mapex), map_end(pt_mapex));
            _print_map_cstl(pt_map);

            pair_make(pt_key, 34, 90.2);
            list_push_back(pt_value, 32445);
            list_push_back(pt_value, -37394);
            list_push_back(pt_value, 9090909);
            list_push_back(pt_value, -342134);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);

            pair_make(pt_key, -4, 0.989);
            list_clear(pt_value);
            list_push_back(pt_value, 130000);
            list_push_back(pt_value, 89039);
            list_push_back(pt_value, 2929);
            list_push_back(pt_value, 908728282);
            list_push_back(pt_value, 3222);
            list_push_back(pt_value, 3232222);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);

            pair_make(pt_key, 378, -0.4222);
            list_clear(pt_value);
            list_push_back(pt_value, 902);
            list_push_back(pt_value, 1);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);

            pair_make(pt_key, 378, 0.4222);
            list_clear(pt_value);
            list_push_back(pt_value, 912111);
            list_push_back(pt_value, 11111);
            list_push_back(pt_value, 9022434);
            list_push_back(pt_value, 0);
            list_push_back(pt_value, -748945);
            list_push_back(pt_value, 111);
            list_push_back(pt_value, 111);
            list_push_back(pt_value, 111);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);

            pair_make(pt_key, 378, 4222.0);
            list_clear(pt_value);
            list_push_back(pt_value, 3456789);
            list_push_back(pt_value, 1);
            list_push_back(pt_value, 100);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);

            pair_make(pt_key, -400, 42.220);
            list_clear(pt_value);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);

            pair_make(pt_key, -1300, 42.220);
            list_clear(pt_value);
            list_push_back(pt_value, 1500);
            list_push_back(pt_value, 1300);
            list_push_back(pt_value, 1100);
            list_push_back(pt_value, 900);
            list_push_back(pt_value, 700);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);

            pair_make(pt_key, -400, 1242.220);
            list_clear(pt_value);
            list_push_back(pt_value, 10000);
            list_push_back(pt_value, 20000);
            list_push_back(pt_value, 30000);
            list_push_back(pt_value, 40000);
            list_push_back(pt_value, 50000);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);

            pair_make(pt_key, 456, 0.2);
            list_clear(pt_value);
            list_push_back(pt_value, 0);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);

            pair_make(pt_key, 4, 2.2);
            list_clear(pt_value);
            list_push_back(pt_value, 0);
            list_push_back(pt_value, 0);
            list_push_back(pt_value, 1998);
            list_push_back(pt_value, 2008);
            list_push_back(pt_value, 2018);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);

            pair_make(pt_key, 0, -10000.2);
            list_clear(pt_value);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_mapex, pt_pair);
            _print_map_cstl(pt_mapex);

            map_insert_range(pt_map, map_begin(pt_mapex), map_begin(pt_mapex));
            _print_map_cstl(pt_map);
            map_insert_range(pt_map, map_begin(pt_mapex), iterator_advance(map_begin(pt_mapex), 3));
            _print_map_cstl(pt_map);
            map_insert_range(pt_map, iterator_advance(map_begin(pt_mapex), 4), iterator_advance(map_begin(pt_mapex), 6));
            _print_map_cstl(pt_map);
            map_insert_range(pt_map, iterator_advance(map_begin(pt_mapex), 8), map_end(pt_mapex));
            _print_map_cstl(pt_map);
            map_insert_range(pt_map, map_end(pt_mapex), map_end(pt_mapex));
            _print_map_cstl(pt_map);
            map_clear(pt_map);
            map_insert_range(pt_map, map_begin(pt_mapex), map_end(pt_mapex));
            _print_map_cstl(pt_map);

            map_destroy(pt_map);
            map_destroy(pt_mapex);
            pair_destroy(pt_pair);
            pair_destroy(pt_key);
            list_destroy(pt_value);
        }
        /*map_erase             */
        {
            map_t* pt_map = create_map(pair_t<int, double>, list_t<long>);
            pair_t* pt_pair = create_pair(pair_t<int, double>, list_t<long>);
            pair_t* pt_key = create_pair(int, double);
            list_t* pt_value = create_list(long);
            if(pt_map == NULL || pt_pair == NULL || pt_key == NULL || pt_value == NULL)
            {
                return;
            }
            map_init(pt_map);
            pair_init(pt_pair);
            pair_init(pt_key);
            list_init(pt_value);
            map_erase(pt_map, pt_key);
            _print_map_cstl(pt_map);

            pair_make(pt_key, 0, -10000.2);
            list_clear(pt_value);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);

            pair_make(pt_key, -4, 0.989);
            list_clear(pt_value);
            list_push_back(pt_value, 130000);
            list_push_back(pt_value, 89039);
            list_push_back(pt_value, 2929);
            list_push_back(pt_value, 908728282);
            list_push_back(pt_value, 3222);
            list_push_back(pt_value, 3232222);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);

            pair_make(pt_key, -4, 0.989);
            list_clear(pt_value);
            list_push_back(pt_value, 100);
            list_push_back(pt_value, 89);
            list_push_back(pt_value, 2);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);

            pair_make(pt_key, 34, 90.2);
            list_clear(pt_value);
            list_push_back(pt_value, 32445);
            list_push_back(pt_value, -37394);
            list_push_back(pt_value, 9090909);
            list_push_back(pt_value, -342134);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);
            _print_map_cstl(pt_map);

            pair_make(pt_key, 7, 23.23);
            map_erase(pt_map, pt_key);
            _print_map_cstl(pt_map);
            pair_make(pt_key, -4, 0.989);
            map_erase(pt_map, pt_key);
            _print_map_cstl(pt_map);

            map_destroy(pt_map);
            pair_destroy(pt_pair);
            pair_destroy(pt_key);
            list_destroy(pt_value);
        }
        /*map_erase_pos         */
        {
            map_t* pt_map = create_map(pair_t<int, double>, list_t<long>);
            pair_t* pt_pair = create_pair(pair_t<int, double>, list_t<long>);
            pair_t* pt_key = create_pair(int, double);
            list_t* pt_value = create_list(long);
            if(pt_map == NULL || pt_pair == NULL || pt_key == NULL || pt_value == NULL)
            {
                return;
            }
            map_init(pt_map);
            pair_init(pt_pair);
            pair_init(pt_key);
            list_init(pt_value);

            pair_make(pt_key, 34, 90.2);
            list_push_back(pt_value, 32445);
            list_push_back(pt_value, -37394);
            list_push_back(pt_value, 9090909);
            list_push_back(pt_value, -342134);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);

            pair_make(pt_key, -4, 0.989);
            list_clear(pt_value);
            list_push_back(pt_value, 130000);
            list_push_back(pt_value, 89039);
            list_push_back(pt_value, 2929);
            list_push_back(pt_value, 908728282);
            list_push_back(pt_value, 3222);
            list_push_back(pt_value, 3232222);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);

            pair_make(pt_key, 378, -0.4222);
            list_clear(pt_value);
            list_push_back(pt_value, 902);
            list_push_back(pt_value, 1);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);

            pair_make(pt_key, 378, 0.4222);
            list_clear(pt_value);
            list_push_back(pt_value, 912111);
            list_push_back(pt_value, 11111);
            list_push_back(pt_value, 9022434);
            list_push_back(pt_value, 0);
            list_push_back(pt_value, -748945);
            list_push_back(pt_value, 111);
            list_push_back(pt_value, 111);
            list_push_back(pt_value, 111);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);

            pair_make(pt_key, 378, 4222.0);
            list_clear(pt_value);
            list_push_back(pt_value, 3456789);
            list_push_back(pt_value, 1);
            list_push_back(pt_value, 100);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);

            pair_make(pt_key, -400, 42.220);
            list_clear(pt_value);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);

            pair_make(pt_key, -1300, 42.220);
            list_clear(pt_value);
            list_push_back(pt_value, 1500);
            list_push_back(pt_value, 1300);
            list_push_back(pt_value, 1100);
            list_push_back(pt_value, 900);
            list_push_back(pt_value, 700);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);

            pair_make(pt_key, -400, 1242.220);
            list_clear(pt_value);
            list_push_back(pt_value, 10000);
            list_push_back(pt_value, 20000);
            list_push_back(pt_value, 30000);
            list_push_back(pt_value, 40000);
            list_push_back(pt_value, 50000);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);

            pair_make(pt_key, 456, 0.2);
            list_clear(pt_value);
            list_push_back(pt_value, 0);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);

            pair_make(pt_key, 4, 2.2);
            list_clear(pt_value);
            list_push_back(pt_value, 0);
            list_push_back(pt_value, 0);
            list_push_back(pt_value, 1998);
            list_push_back(pt_value, 2008);
            list_push_back(pt_value, 2018);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);

            pair_make(pt_key, 0, -10000.2);
            list_clear(pt_value);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);
            _print_map_cstl(pt_map);

            map_erase_pos(pt_map, map_begin(pt_map));
            _print_map_cstl(pt_map);
            map_erase_pos(pt_map, iterator_prev(map_end(pt_map)));
            _print_map_cstl(pt_map);
            map_erase_pos(pt_map, iterator_advance(map_begin(pt_map), 3));
            _print_map_cstl(pt_map);
            while(!map_empty(pt_map))
            {
                map_erase_pos(pt_map, map_begin(pt_map));
            }
            _print_map_cstl(pt_map);

            map_destroy(pt_map);
            pair_destroy(pt_pair);
            pair_destroy(pt_key);
            list_destroy(pt_value);
        }
        /*map_erase_range       */
        {
            map_t* pt_map = create_map(pair_t<int, double>, list_t<long>);
            pair_t* pt_pair = create_pair(pair_t<int, double>, list_t<long>);
            pair_t* pt_key = create_pair(int, double);
            list_t* pt_value = create_list(long);
            if(pt_map == NULL || pt_pair == NULL || pt_key == NULL || pt_value == NULL)
            {
                return;
            }
            map_init(pt_map);
            pair_init(pt_pair);
            pair_init(pt_key);
            list_init(pt_value);

            map_erase_range(pt_map, map_begin(pt_map), map_end(pt_map));
            _print_map_cstl(pt_map);

            pair_make(pt_key, 34, 90.2);
            list_push_back(pt_value, 32445);
            list_push_back(pt_value, -37394);
            list_push_back(pt_value, 9090909);
            list_push_back(pt_value, -342134);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);

            pair_make(pt_key, -4, 0.989);
            list_clear(pt_value);
            list_push_back(pt_value, 130000);
            list_push_back(pt_value, 89039);
            list_push_back(pt_value, 2929);
            list_push_back(pt_value, 908728282);
            list_push_back(pt_value, 3222);
            list_push_back(pt_value, 3232222);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);

            pair_make(pt_key, 378, -0.4222);
            list_clear(pt_value);
            list_push_back(pt_value, 902);
            list_push_back(pt_value, 1);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);

            pair_make(pt_key, 378, 0.4222);
            list_clear(pt_value);
            list_push_back(pt_value, 912111);
            list_push_back(pt_value, 11111);
            list_push_back(pt_value, 9022434);
            list_push_back(pt_value, 0);
            list_push_back(pt_value, -748945);
            list_push_back(pt_value, 111);
            list_push_back(pt_value, 111);
            list_push_back(pt_value, 111);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);

            pair_make(pt_key, 378, 4222.0);
            list_clear(pt_value);
            list_push_back(pt_value, 3456789);
            list_push_back(pt_value, 1);
            list_push_back(pt_value, 100);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);

            pair_make(pt_key, -400, 42.220);
            list_clear(pt_value);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);

            pair_make(pt_key, -1300, 42.220);
            list_clear(pt_value);
            list_push_back(pt_value, 1500);
            list_push_back(pt_value, 1300);
            list_push_back(pt_value, 1100);
            list_push_back(pt_value, 900);
            list_push_back(pt_value, 700);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);

            pair_make(pt_key, -400, 1242.220);
            list_clear(pt_value);
            list_push_back(pt_value, 10000);
            list_push_back(pt_value, 20000);
            list_push_back(pt_value, 30000);
            list_push_back(pt_value, 40000);
            list_push_back(pt_value, 50000);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);

            pair_make(pt_key, 456, 0.2);
            list_clear(pt_value);
            list_push_back(pt_value, 0);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);

            pair_make(pt_key, 4, 2.2);
            list_clear(pt_value);
            list_push_back(pt_value, 0);
            list_push_back(pt_value, 0);
            list_push_back(pt_value, 1998);
            list_push_back(pt_value, 2008);
            list_push_back(pt_value, 2018);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);

            pair_make(pt_key, 0, -10000.2);
            list_clear(pt_value);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            list_push_back(pt_value, 9);
            pair_make(pt_pair, pt_key, pt_value);
            map_insert(pt_map, pt_pair);
            _print_map_cstl(pt_map);

            map_erase_range(pt_map, map_begin(pt_map), map_begin(pt_map));
            _print_map_cstl(pt_map);
            map_erase_range(pt_map, map_begin(pt_map), iterator_advance(map_begin(pt_map), 3));
            _print_map_cstl(pt_map);
            map_erase_range(pt_map, iterator_next(map_begin(pt_map)), iterator_advance(map_begin(pt_map), 4));
            _print_map_cstl(pt_map);
            map_erase_range(pt_map, iterator_advance(map_begin(pt_map), 3), map_end(pt_map));
            _print_map_cstl(pt_map);
            map_erase_range(pt_map, map_end(pt_map), map_end(pt_map));
            _print_map_cstl(pt_map);
            map_erase_range(pt_map, map_begin(pt_map), map_end(pt_map));
            _print_map_cstl(pt_map);

            map_destroy(pt_map);
            pair_destroy(pt_pair);
            pair_destroy(pt_key);
            list_destroy(pt_value);
        }
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
static void _mapkey_pair_great(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = pair_great((pair_t*)cpv_first, (pair_t*)cpv_second);
}

static void _print_map_cstl(const map_t* cpt_map)
{
    pair_t* pt_key = NULL;
    list_t* pt_value = NULL;

    iterator_t t_iter;
    printf("=======================================\n");
    printf("empty: %u, size: %u, max_size: %u\n",
        map_empty(cpt_map), map_size(cpt_map), map_max_size(cpt_map));

    for(t_iter = map_begin(cpt_map);
        !iterator_equal(t_iter, map_end(cpt_map));
        t_iter = iterator_next(t_iter))
    {
        iterator_t t_pos;
        pt_key = (pair_t*)pair_first((pair_t*)iterator_get_pointer(t_iter));
        pt_value = (list_t*)pair_second((pair_t*)iterator_get_pointer(t_iter));
        assert(pt_key != NULL && pt_value != NULL);
        printf("<%d, %lf>: ", *(int*)pair_first(pt_key), *(double*)pair_second(pt_key));
        for(t_pos = list_begin(pt_value);
            !iterator_equal(t_pos, list_end(pt_value));
            t_pos = iterator_next(t_pos))
        {
            printf("[%ld]", *(long*)iterator_get_pointer(t_pos));
        }
        printf("\n----------------------------\n");
    }
}

static void _print_map_user(const map_t* cpt_map)
{
    pair_t*  pt_pair = NULL;
    unsigned un_number = 0;
    _units_t t_unit = 0;
    char*    s_enviroment = NULL;
    char*    s_condition = NULL;

    iterator_t t_iter;
    printf("=======================================\n");
    printf("empty: %u, size: %u, max_size: %u\n",
        map_empty(cpt_map), map_size(cpt_map), map_max_size(cpt_map));
    for(t_iter = map_begin(cpt_map);
        !iterator_equal(t_iter, map_end(cpt_map));
        t_iter = iterator_next(t_iter))
    {
        pt_pair = (pair_t*)iterator_get_pointer(t_iter);
        un_number = ((_mapkey_t*)pair_first(pt_pair))->_un_number;
        t_unit = ((_mapkey_t*)pair_first(pt_pair))->_t_unit;
        s_enviroment = ((_mapvalue_t*)pair_second(pt_pair))->_s_enviroment;
        s_condition = ((_mapvalue_t*)pair_second(pt_pair))->_s_condition;
        printf("<key: [%d ", un_number);
        switch(t_unit)
        {
        case _B: printf("B/s]"); break;
        case _KB: printf("KB/s]"); break;
        case _MB: printf("MB/s]"); break;
        default: printf("ERR]"); break;
        }
        printf(", value: (%s, %s)>\n", s_enviroment, s_condition);
    }
}

static void _mapkey_number_great(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    if(((_mapkey_t*)cpv_first)->_un_number > ((_mapkey_t*)cpv_second)->_un_number)
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}

static void _mapkey_init(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    ((_mapkey_t*)cpv_input)->_un_number = 0;
    ((_mapkey_t*)cpv_input)->_t_unit = _ERR;
    *(bool_t*)pv_output = true;
}
static void _mapkey_copy(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    ((_mapkey_t*)cpv_first)->_un_number = ((_mapkey_t*)cpv_second)->_un_number;
    ((_mapkey_t*)cpv_first)->_t_unit = ((_mapkey_t*)cpv_second)->_t_unit;
    *(bool_t*)pv_output = true;
}
static void _mapkey_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    unsigned un_first = 0;
    unsigned un_second = 0;

    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    un_first = ((_mapkey_t*)cpv_first)->_un_number;
    un_second = ((_mapkey_t*)cpv_second)->_un_number;
    switch(((_mapkey_t*)cpv_first)->_t_unit)
    {
    case _B: break;
    case _KB: un_first *= 1024; break;
    case _MB: un_first *= 1024*1024; break;
    default: un_first = 0; break;
    }
    switch(((_mapkey_t*)cpv_second)->_t_unit)
    {
    case _B: break;
    case _KB: un_second *= 1024; break;
    case _MB: un_second *= 1024*1024; break;
    default: un_second = 0; break;
    }
    if(un_first < un_second)
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}
static void _mapkey_destroy(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    ((_mapkey_t*)cpv_input)->_un_number = 0;
    ((_mapkey_t*)cpv_input)->_t_unit = _ERR;
    *(bool_t*)pv_output = true;
}

static void _mapvalue_init(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    memset(((_mapvalue_t*)cpv_input)->_s_enviroment, '\0', _ENV_AND_COND_LEN);
    memset(((_mapvalue_t*)cpv_input)->_s_condition, '\0', _ENV_AND_COND_LEN);
    *(bool_t*)pv_output = true;
}
static void _mapvalue_copy(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    memcpy(((_mapvalue_t*)cpv_first)->_s_enviroment, ((_mapvalue_t*)cpv_second)->_s_enviroment, _ENV_AND_COND_LEN);
    memcpy(((_mapvalue_t*)cpv_first)->_s_condition, ((_mapvalue_t*)cpv_second)->_s_condition, _ENV_AND_COND_LEN);
    *(bool_t*)pv_output = true;
}
static void _mapvalue_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    if(memcmp(((_mapvalue_t*)cpv_first)->_s_enviroment, ((_mapvalue_t*)cpv_second)->_s_enviroment, _ENV_AND_COND_LEN) < 0)
    {
        *(bool_t*)pv_output = true;
    }
    else if(memcmp(((_mapvalue_t*)cpv_first)->_s_enviroment, ((_mapvalue_t*)cpv_second)->_s_enviroment, _ENV_AND_COND_LEN) == 0 &&
            memcmp(((_mapvalue_t*)cpv_first)->_s_condition, ((_mapvalue_t*)cpv_second)->_s_condition, _ENV_AND_COND_LEN) < 0)
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}
static void _mapvalue_destroy(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    memset(((_mapvalue_t*)cpv_input)->_s_enviroment, '\0', _ENV_AND_COND_LEN);
    memset(((_mapvalue_t*)cpv_input)->_s_condition, '\0', _ENV_AND_COND_LEN);
    *(bool_t*)pv_output = true;
}

/** eof **/

