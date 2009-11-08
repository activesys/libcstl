/*
 *  The implementation of pair test.
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
#include <stdio.h>
#include <assert.h>
#include "cutility.h"
#include "test_pair.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/
typedef struct _tagsample
{
    int _n_first;
    int _n_second;
}sample_t;

/** local function prototype section **/
static void _sample_init(const void* cpv_input, void* pv_output);
static void _sample_destory(const void* cpv_input, void* pv_output);
static void _sample_less(const void* cpv_first, const void* cpv_second, void* pv_output);
static void _sample_copy(const void* cpv_first, const void* cpv_second, void* pv_output);

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
void test_pair(void)
{
    /* c built-in type */
    {
        /*create_pair      */
        {
            pair_t* pt_pair = create_pair(int, int);
            if(pt_pair == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            printf("<%d, %d>\n", *(int*)pair_first(pt_pair), *(int*)pair_second(pt_pair));
            pair_destroy(pt_pair);
        }
        /*pair_make_first  */
        /*pair_make_second */
        {
            pair_t* pt_pair = create_pair(int, double);
            if(pt_pair == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            printf("<%d, %lf>\n", *(int*)pair_first(pt_pair), *(double*)pair_second(pt_pair));
            pair_make(pt_pair, 89, 22.13);
            printf("<%d, %lf>\n", *(int*)pair_first(pt_pair), *(double*)pair_second(pt_pair));
            pair_destroy(pt_pair);
        }
        /*pair_init        */
        /*pair_destroy     */
        /*pair_init_copy   */
        {
            pair_t* pt_pair = create_pair(char, long);
            pair_t* pt_pairex = create_pair(char, long);
            if(pt_pair == NULL || pt_pairex == NULL)
            {
                return;
            }
            pair_init(pt_pairex);
            pair_make(pt_pairex, 'V', 8894084);
            pair_init_copy(pt_pair, pt_pairex);
            printf("<%c, %ld>\n", *(char*)pair_first(pt_pair), *(long*)pair_second(pt_pair));
            pair_destroy(pt_pair);
            pair_destroy(pt_pairex);
        }
        /*pair_assign      */
        {
            pair_t* pt_pair = create_pair(unsigned, double);
            pair_t* pt_pairex = create_pair(unsigned, double);
            if(pt_pair == NULL || pt_pairex == NULL)
            {
                return;
            }
            pair_init(pt_pairex);
            pair_init(pt_pair);
            pair_assign(pt_pair, pt_pairex);
            printf("<%u, %lf>\n",
                *(unsigned*)pair_first(pt_pair), *(double*)pair_second(pt_pair));
            pair_make(pt_pairex, -12345, -990.87);
            pair_assign(pt_pair, pt_pairex);
            printf("<%u, %lf>\n",
                *(unsigned*)pair_first(pt_pair), *(double*)pair_second(pt_pair));
            pair_destroy(pt_pair);
            pair_destroy(pt_pairex);
        }
        /*pair_equal       */
        /*pair_not_equal   */
        /*pair_less        */
        /*pair_less_equal  */
        /*pair_great       */
        /*pair_great_equal */
        {
            pair_t* pt_pair = create_pair(int, int);
            pair_t* pt_pairex = create_pair(int, int);
            if(pt_pair == NULL || pt_pairex == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            pair_init(pt_pairex);
            printf("<%d, %d>\n", *(int*)pair_first(pt_pair), *(int*)pair_second(pt_pair));
            printf("<%d, %d>\n", *(int*)pair_first(pt_pairex), *(int*)pair_second(pt_pairex));
            printf("equal: %d, not equal: %d, ",
                pair_equal(pt_pair, pt_pairex), pair_not_equal(pt_pair, pt_pairex));
            printf("less: %d, less equal: %d, ",
                pair_less(pt_pair, pt_pairex), pair_less_equal(pt_pair, pt_pairex));
            printf("great: %d, great equal: %d\n",
                pair_great(pt_pair, pt_pairex), pair_great_equal(pt_pair, pt_pairex));
            pair_make(pt_pair, 45, -98);
            printf("<%d, %d>\n", *(int*)pair_first(pt_pair), *(int*)pair_second(pt_pair));
            printf("<%d, %d>\n", *(int*)pair_first(pt_pairex), *(int*)pair_second(pt_pairex));
            printf("equal: %d, not equal: %d, ",
                pair_equal(pt_pair, pt_pairex), pair_not_equal(pt_pair, pt_pairex));
            printf("less: %d, less equal: %d, ",
                pair_less(pt_pair, pt_pairex), pair_less_equal(pt_pair, pt_pairex));
            printf("great: %d, great equal: %d\n",
                pair_great(pt_pair, pt_pairex), pair_great_equal(pt_pair, pt_pairex));
            pair_make(pt_pairex, 45, -98);
            printf("<%d, %d>\n", *(int*)pair_first(pt_pair), *(int*)pair_second(pt_pair));
            printf("<%d, %d>\n", *(int*)pair_first(pt_pairex), *(int*)pair_second(pt_pairex));
            printf("equal: %d, not equal: %d, ",
                pair_equal(pt_pair, pt_pairex), pair_not_equal(pt_pair, pt_pairex));
            printf("less: %d, less equal: %d, ",
                pair_less(pt_pair, pt_pairex), pair_less_equal(pt_pair, pt_pairex));
            printf("great: %d, great equal: %d\n",
                pair_great(pt_pair, pt_pairex), pair_great_equal(pt_pair, pt_pairex));
            pair_make(pt_pair, 19, 86978);
            pair_make(pt_pairex, 33, -87898);
            printf("<%d, %d>\n", *(int*)pair_first(pt_pair), *(int*)pair_second(pt_pair));
            printf("<%d, %d>\n", *(int*)pair_first(pt_pairex), *(int*)pair_second(pt_pairex));
            printf("equal: %d, not equal: %d, ",
                pair_equal(pt_pair, pt_pairex), pair_not_equal(pt_pair, pt_pairex));
            printf("less: %d, less equal: %d, ",
                pair_less(pt_pair, pt_pairex), pair_less_equal(pt_pair, pt_pairex));
            printf("great: %d, great equal: %d\n",
                pair_great(pt_pair, pt_pairex), pair_great_equal(pt_pair, pt_pairex));
            pair_make(pt_pair, 77, 86978);
            pair_make(pt_pairex, 77, -87898);
            printf("<%d, %d>\n", *(int*)pair_first(pt_pair), *(int*)pair_second(pt_pair));
            printf("<%d, %d>\n", *(int*)pair_first(pt_pairex), *(int*)pair_second(pt_pairex));
            printf("equal: %d, not equal: %d, ",
                pair_equal(pt_pair, pt_pairex), pair_not_equal(pt_pair, pt_pairex));
            printf("less: %d, less equal: %d, ",
                pair_less(pt_pair, pt_pairex), pair_less_equal(pt_pair, pt_pairex));
            printf("great: %d, great equal: %d\n",
                pair_great(pt_pair, pt_pairex), pair_great_equal(pt_pair, pt_pairex));
            pair_destroy(pt_pair);
            pair_destroy(pt_pairex);
        }
    }
    /* user defined type */
    {
        type_register(sample_t, _sample_init, _sample_copy, _sample_less, _sample_destory);
        type_duplicate(sample_t, struct _tagsample);
        /*create_pair      */
        {
            pair_t* pt_pair = create_pair(sample_t, int);
            if(pt_pair == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            printf("<<%d, %d>, %d>\n",
                ((sample_t*)pair_first(pt_pair))->_n_first,
                ((sample_t*)pair_first(pt_pair))->_n_second,
                *(int*)pair_second(pt_pair));
            pair_destroy(pt_pair);
        }
        /*pair_make_first  */
        /*pair_make_second */
        {
            pair_t* pt_pair = create_pair(sample_t, int);
            sample_t t_sa;
            if(pt_pair == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            printf("<<%d, %d>, %d>\n",
                ((sample_t*)pair_first(pt_pair))->_n_first,
                ((sample_t*)pair_first(pt_pair))->_n_second,
                *(int*)pair_second(pt_pair));
            t_sa._n_first = 100;
            t_sa._n_second = -1244;
            pair_make(pt_pair, &t_sa, 999);
            printf("<<%d, %d>, %d>\n",
                ((sample_t*)pair_first(pt_pair))->_n_first,
                ((sample_t*)pair_first(pt_pair))->_n_second,
                *(int*)pair_second(pt_pair));
            pair_destroy(pt_pair);
        }
        /*pair_init        */
        /*pair_destroy     */
        /*pair_init_copy   */
        {
            pair_t* pt_pair = create_pair(sample_t, int);
            pair_t* pt_pairex = create_pair(sample_t, int);
            sample_t t_sa;
            if(pt_pair == NULL || pt_pairex == NULL)
            {
                return;
            }
            pair_init(pt_pairex);
            t_sa._n_first = -45;
            t_sa._n_second = 900;
            pair_make(pt_pairex, &t_sa, 333);
            pair_init_copy(pt_pair, pt_pairex);
            printf("<<%d, %d>, %d>\n",
                ((sample_t*)pair_first(pt_pair))->_n_first,
                ((sample_t*)pair_first(pt_pair))->_n_second,
                *(int*)pair_second(pt_pair));
            pair_destroy(pt_pair);
            pair_destroy(pt_pairex);
        }
        /*pair_assign      */
        {
            pair_t* pt_pair = create_pair(sample_t, int);
            pair_t* pt_pairex = create_pair(sample_t, int);
            sample_t t_sa;
            if(pt_pair == NULL || pt_pairex == NULL)
            {
                return;
            }
            pair_init(pt_pairex);
            pair_init(pt_pair);
            pair_assign(pt_pair, pt_pairex);
            printf("<<%d, %d>, %d>\n",
                ((sample_t*)pair_first(pt_pair))->_n_first,
                ((sample_t*)pair_first(pt_pair))->_n_second,
                *(int*)pair_second(pt_pair));
            t_sa._n_first = 222;
            t_sa._n_second = 777;
            pair_make(pt_pairex, &t_sa, 333);
            pair_assign(pt_pair, pt_pairex);
            printf("<<%d, %d>, %d>\n",
                ((sample_t*)pair_first(pt_pair))->_n_first,
                ((sample_t*)pair_first(pt_pair))->_n_second,
                *(int*)pair_second(pt_pair));
            pair_destroy(pt_pair);
            pair_destroy(pt_pairex);
        }
        /*pair_equal       */
        /*pair_not_equal   */
        /*pair_less        */
        /*pair_less_equal  */
        /*pair_great       */
        /*pair_great_equal */
        {
            pair_t* pt_pair = create_pair(sample_t, int);
            pair_t* pt_pairex = create_pair(sample_t, int);
            sample_t t_sa;
            if(pt_pair == NULL || pt_pairex == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            pair_init(pt_pairex);
            printf("<<%d, %d>, %d>\n",
                ((sample_t*)pair_first(pt_pair))->_n_first,
                ((sample_t*)pair_first(pt_pair))->_n_second,
                *(int*)pair_second(pt_pair));
            printf("<<%d, %d>, %d>\n",
                ((sample_t*)pair_first(pt_pairex))->_n_first,
                ((sample_t*)pair_first(pt_pairex))->_n_second,
                *(int*)pair_second(pt_pairex));
            printf("equal: %d, not equal: %d, ",
                pair_equal(pt_pair, pt_pairex), pair_not_equal(pt_pair, pt_pairex));
            printf("less: %d, less equal: %d, ",
                pair_less(pt_pair, pt_pairex), pair_less_equal(pt_pair, pt_pairex));
            printf("great: %d, great equal: %d\n",
                pair_great(pt_pair, pt_pairex), pair_great_equal(pt_pair, pt_pairex));

            t_sa._n_first = 456;
            t_sa._n_second = 789;
            pair_make(pt_pair, &t_sa, 23);
            printf("<<%d, %d>, %d>\n",
                ((sample_t*)pair_first(pt_pair))->_n_first,
                ((sample_t*)pair_first(pt_pair))->_n_second,
                *(int*)pair_second(pt_pair));
            printf("<<%d, %d>, %d>\n",
                ((sample_t*)pair_first(pt_pairex))->_n_first,
                ((sample_t*)pair_first(pt_pairex))->_n_second,
                *(int*)pair_second(pt_pairex));
            printf("equal: %d, not equal: %d, ",
                pair_equal(pt_pair, pt_pairex), pair_not_equal(pt_pair, pt_pairex));
            printf("less: %d, less equal: %d, ",
                pair_less(pt_pair, pt_pairex), pair_less_equal(pt_pair, pt_pairex));
            printf("great: %d, great equal: %d\n",
                pair_great(pt_pair, pt_pairex), pair_great_equal(pt_pair, pt_pairex));

            t_sa._n_first = 456;
            t_sa._n_second = 789;
            pair_make(pt_pairex, &t_sa, 23);
            printf("<<%d, %d>, %d>\n",
                ((sample_t*)pair_first(pt_pair))->_n_first,
                ((sample_t*)pair_first(pt_pair))->_n_second,
                *(int*)pair_second(pt_pair));
            printf("<<%d, %d>, %d>\n",
                ((sample_t*)pair_first(pt_pairex))->_n_first,
                ((sample_t*)pair_first(pt_pairex))->_n_second,
                *(int*)pair_second(pt_pairex));
            printf("equal: %d, not equal: %d, ",
                pair_equal(pt_pair, pt_pairex), pair_not_equal(pt_pair, pt_pairex));
            printf("less: %d, less equal: %d, ",
                pair_less(pt_pair, pt_pairex), pair_less_equal(pt_pair, pt_pairex));
            printf("great: %d, great equal: %d\n",
                pair_great(pt_pair, pt_pairex), pair_great_equal(pt_pair, pt_pairex));

            t_sa._n_first = 456;
            t_sa._n_second = -789;
            pair_make(pt_pair, &t_sa, 23);
            t_sa._n_first = 456;
            t_sa._n_second = 0;
            pair_make(pt_pairex, &t_sa, 1123);
            printf("<<%d, %d>, %d>\n",
                ((sample_t*)pair_first(pt_pair))->_n_first,
                ((sample_t*)pair_first(pt_pair))->_n_second,
                *(int*)pair_second(pt_pair));
            printf("<<%d, %d>, %d>\n",
                ((sample_t*)pair_first(pt_pairex))->_n_first,
                ((sample_t*)pair_first(pt_pairex))->_n_second,
                *(int*)pair_second(pt_pairex));
            printf("equal: %d, not equal: %d, ",
                pair_equal(pt_pair, pt_pairex), pair_not_equal(pt_pair, pt_pairex));
            printf("less: %d, less equal: %d, ",
                pair_less(pt_pair, pt_pairex), pair_less_equal(pt_pair, pt_pairex));
            printf("great: %d, great equal: %d\n",
                pair_great(pt_pair, pt_pairex), pair_great_equal(pt_pair, pt_pairex));

            pair_destroy(pt_pair);
            pair_destroy(pt_pairex);
        }
    }
    /* cstl built-in type */
    {
        /*create_pair      */
        {
            pair_t* pt_pair = create_pair(pair_t<int, int>, pair_t<double, double>);
            if(pt_pair == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            printf("<<%d, %d>, <%lf, %lf>>\n",
                *(int*)pair_first(((pair_t*)pair_first(pt_pair))),
                *(int*)pair_second(((pair_t*)pair_first(pt_pair))),
                *(double*)pair_first(((pair_t*)pair_second(pt_pair))),
                *(double*)pair_second(((pair_t*)pair_second(pt_pair))));
            pair_destroy(pt_pair);
        }
        /*pair_make_first  */
        /*pair_make_second */
        {
            pair_t* pt_pair = create_pair(pair_t<int, int>, pair_t<double, double>);
            pair_t* pt_pair1 = create_pair(int, int);
            pair_t* pt_pair2 = create_pair(double, double);
            if(pt_pair == NULL || pt_pair1 == NULL || pt_pair2 == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            pair_init(pt_pair1);
            pair_init(pt_pair2);
            printf("<<%d, %d>, <%lf, %lf>>\n",
                *(int*)pair_first(((pair_t*)pair_first(pt_pair))),
                *(int*)pair_second(((pair_t*)pair_first(pt_pair))),
                *(double*)pair_first(((pair_t*)pair_second(pt_pair))),
                *(double*)pair_second(((pair_t*)pair_second(pt_pair))));
            pair_make(pt_pair1, 34, -98);
            pair_make(pt_pair2, 90.2, 98.1222);
            pair_make(pt_pair, pt_pair1, pt_pair2);
            printf("<<%d, %d>, <%lf, %lf>>\n",
                *(int*)pair_first(((pair_t*)pair_first(pt_pair))),
                *(int*)pair_second(((pair_t*)pair_first(pt_pair))),
                *(double*)pair_first(((pair_t*)pair_second(pt_pair))),
                *(double*)pair_second(((pair_t*)pair_second(pt_pair))));
            pair_destroy(pt_pair);
            pair_destroy(pt_pair1);
            pair_destroy(pt_pair2);
        }
        /*pair_init        */
        /*pair_destroy     */
        /*pair_init_copy   */
        {
            pair_t* pt_pair = create_pair(pair_t<int, int>, pair_t<double, double>);
            pair_t* pt_pairex = create_pair(pair_t<int, int>, pair_t<double, double>);
            pair_t* pt_pair1 = create_pair(int, int);
            pair_t* pt_pair2 = create_pair(double, double);
            if(pt_pair == NULL || pt_pairex == NULL || pt_pair1 == NULL || pt_pair2 == NULL)
            {
                return;
            }
            pair_init(pt_pairex);
            pair_init(pt_pair1);
            pair_init(pt_pair2);
            pair_make(pt_pair1, -50, -200);
            pair_make(pt_pair2, 56.0, 23.0);
            pair_make(pt_pairex, pt_pair1, pt_pair2);
            pair_init_copy(pt_pair, pt_pairex);
            printf("<<%d, %d>, <%lf, %lf>>\n",
                *(int*)pair_first(((pair_t*)pair_first(pt_pair))),
                *(int*)pair_second(((pair_t*)pair_first(pt_pair))),
                *(double*)pair_first(((pair_t*)pair_second(pt_pair))),
                *(double*)pair_second(((pair_t*)pair_second(pt_pair))));
            pair_destroy(pt_pair);
            pair_destroy(pt_pairex);
            pair_destroy(pt_pair1);
            pair_destroy(pt_pair2);
        }
        /*pair_assign      */
        {
            pair_t* pt_pair = create_pair(pair_t<int, int>, pair_t<double, double>);
            pair_t* pt_pairex = create_pair(pair_t<int, int>, pair_t<double, double>);
            pair_t* pt_pair1 = create_pair(int, int);
            pair_t* pt_pair2 = create_pair(double, double);
            if(pt_pair == NULL || pt_pairex == NULL || pt_pair1 == NULL || pt_pair2 == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            pair_init(pt_pairex);
            pair_init(pt_pair1);
            pair_init(pt_pair2);
            pair_assign(pt_pair, pt_pairex);
            printf("<<%d, %d>, <%lf, %lf>>\n",
                *(int*)pair_first(((pair_t*)pair_first(pt_pair))),
                *(int*)pair_second(((pair_t*)pair_first(pt_pair))),
                *(double*)pair_first(((pair_t*)pair_second(pt_pair))),
                *(double*)pair_second(((pair_t*)pair_second(pt_pair))));
            pair_make(pt_pair1, -5, -2);
            pair_make(pt_pair2, 0.560, 0.23);
            pair_make(pt_pairex, pt_pair1, pt_pair2);
            pair_assign(pt_pair, pt_pairex);
            printf("<<%d, %d>, <%lf, %lf>>\n",
                *(int*)pair_first(((pair_t*)pair_first(pt_pair))),
                *(int*)pair_second(((pair_t*)pair_first(pt_pair))),
                *(double*)pair_first(((pair_t*)pair_second(pt_pair))),
                *(double*)pair_second(((pair_t*)pair_second(pt_pair))));
            pair_destroy(pt_pair);
            pair_destroy(pt_pairex);
            pair_destroy(pt_pair1);
            pair_destroy(pt_pair2);
        }
        /*pair_equal       */
        /*pair_not_equal   */
        /*pair_less        */
        /*pair_less_equal  */
        /*pair_great       */
        /*pair_great_equal */
        {
            pair_t* pt_pair = create_pair(pair_t<int, int>, pair_t<double, double>);
            pair_t* pt_pairex = create_pair(pair_t<int, int>, pair_t<double, double>);
            pair_t* pt_pair1 = create_pair(int, int);
            pair_t* pt_pair2 = create_pair(double, double);
            if(pt_pair == NULL || pt_pairex == NULL || pt_pair1 == NULL || pt_pair2 == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            pair_init(pt_pairex);
            pair_init(pt_pair1);
            pair_init(pt_pair2);
            pair_assign(pt_pair, pt_pairex);
            printf("<<%d, %d>, <%lf, %lf>>\n",
                *(int*)pair_first(((pair_t*)pair_first(pt_pair))),
                *(int*)pair_second(((pair_t*)pair_first(pt_pair))),
                *(double*)pair_first(((pair_t*)pair_second(pt_pair))),
                *(double*)pair_second(((pair_t*)pair_second(pt_pair))));
            printf("<<%d, %d>, <%lf, %lf>>\n",
                *(int*)pair_first(((pair_t*)pair_first(pt_pairex))),
                *(int*)pair_second(((pair_t*)pair_first(pt_pairex))),
                *(double*)pair_first(((pair_t*)pair_second(pt_pairex))),
                *(double*)pair_second(((pair_t*)pair_second(pt_pairex))));
            printf("equal: %d, not equal: %d, ",
                pair_equal(pt_pair, pt_pairex), pair_not_equal(pt_pair, pt_pairex));
            printf("less: %d, less equal: %d, ",
                pair_less(pt_pair, pt_pairex), pair_less_equal(pt_pair, pt_pairex));
            printf("great: %d, great equal: %d\n",
                pair_great(pt_pair, pt_pairex), pair_great_equal(pt_pair, pt_pairex));

            pair_make(pt_pair1, 5, 2);
            pair_make(pt_pair2, 0.560, 0.23);
            pair_make(pt_pair, pt_pair1, pt_pair2);
            printf("<<%d, %d>, <%lf, %lf>>\n",
                *(int*)pair_first(((pair_t*)pair_first(pt_pair))),
                *(int*)pair_second(((pair_t*)pair_first(pt_pair))),
                *(double*)pair_first(((pair_t*)pair_second(pt_pair))),
                *(double*)pair_second(((pair_t*)pair_second(pt_pair))));
            printf("<<%d, %d>, <%lf, %lf>>\n",
                *(int*)pair_first(((pair_t*)pair_first(pt_pairex))),
                *(int*)pair_second(((pair_t*)pair_first(pt_pairex))),
                *(double*)pair_first(((pair_t*)pair_second(pt_pairex))),
                *(double*)pair_second(((pair_t*)pair_second(pt_pairex))));
            printf("equal: %d, not equal: %d, ",
                pair_equal(pt_pair, pt_pairex), pair_not_equal(pt_pair, pt_pairex));
            printf("less: %d, less equal: %d, ",
                pair_less(pt_pair, pt_pairex), pair_less_equal(pt_pair, pt_pairex));
            printf("great: %d, great equal: %d\n",
                pair_great(pt_pair, pt_pairex), pair_great_equal(pt_pair, pt_pairex));

            pair_make(pt_pair1, 5, 2);
            pair_make(pt_pair2, 0.560, 0.23);
            pair_make(pt_pairex, pt_pair1, pt_pair2);
            printf("<<%d, %d>, <%lf, %lf>>\n",
                *(int*)pair_first(((pair_t*)pair_first(pt_pair))),
                *(int*)pair_second(((pair_t*)pair_first(pt_pair))),
                *(double*)pair_first(((pair_t*)pair_second(pt_pair))),
                *(double*)pair_second(((pair_t*)pair_second(pt_pair))));
            printf("<<%d, %d>, <%lf, %lf>>\n",
                *(int*)pair_first(((pair_t*)pair_first(pt_pairex))),
                *(int*)pair_second(((pair_t*)pair_first(pt_pairex))),
                *(double*)pair_first(((pair_t*)pair_second(pt_pairex))),
                *(double*)pair_second(((pair_t*)pair_second(pt_pairex))));
            printf("equal: %d, not equal: %d, ",
                pair_equal(pt_pair, pt_pairex), pair_not_equal(pt_pair, pt_pairex));
            printf("less: %d, less equal: %d, ",
                pair_less(pt_pair, pt_pairex), pair_less_equal(pt_pair, pt_pairex));
            printf("great: %d, great equal: %d\n",
                pair_great(pt_pair, pt_pairex), pair_great_equal(pt_pair, pt_pairex));

            pair_make(pt_pair1, -5, 2300);
            pair_make(pt_pair2, 9.560, 10.23);
            pair_make(pt_pair, pt_pair1, pt_pair2);
            pair_make(pt_pair1, 8, 3);
            pair_make(pt_pairex, pt_pair1, pt_pair2);
            printf("<<%d, %d>, <%lf, %lf>>\n",
                *(int*)pair_first(((pair_t*)pair_first(pt_pair))),
                *(int*)pair_second(((pair_t*)pair_first(pt_pair))),
                *(double*)pair_first(((pair_t*)pair_second(pt_pair))),
                *(double*)pair_second(((pair_t*)pair_second(pt_pair))));
            printf("<<%d, %d>, <%lf, %lf>>\n",
                *(int*)pair_first(((pair_t*)pair_first(pt_pairex))),
                *(int*)pair_second(((pair_t*)pair_first(pt_pairex))),
                *(double*)pair_first(((pair_t*)pair_second(pt_pairex))),
                *(double*)pair_second(((pair_t*)pair_second(pt_pairex))));
            printf("equal: %d, not equal: %d, ",
                pair_equal(pt_pair, pt_pairex), pair_not_equal(pt_pair, pt_pairex));
            printf("less: %d, less equal: %d, ",
                pair_less(pt_pair, pt_pairex), pair_less_equal(pt_pair, pt_pairex));
            printf("great: %d, great equal: %d\n",
                pair_great(pt_pair, pt_pairex), pair_great_equal(pt_pair, pt_pairex));
            pair_destroy(pt_pair);
            pair_destroy(pt_pairex);
            pair_destroy(pt_pair1);
            pair_destroy(pt_pair2);
        }
    }
    /* c-string type */
    {
        /*create_pair      */
        {
            pair_t* pt_pair = create_pair(char*, int);
            if(pt_pair == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            printf("<%s, %d>\n", (char*)pair_first(pt_pair), *(int*)pair_second(pt_pair));
            pair_destroy(pt_pair);
        }
        /*pair_make_first  */
        /*pair_make_second */
        {
            pair_t* pt_pair = create_pair(char*, int);
            if(pt_pair == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            pair_make(pt_pair, "China", 10000);
            printf("<%s, %d>\n", (char*)pair_first(pt_pair), *(int*)pair_second(pt_pair));
            pair_destroy(pt_pair);
        }
        /*pair_init        */
        /*pair_destroy     */
        /*pair_init_copy   */
        {
            pair_t* pt_pair = create_pair(char*, int);
            pair_t* pt_pairex = create_pair(char*, int);
            if(pt_pair == NULL || pt_pairex == NULL)
            {
                return;
            }
            pair_init(pt_pairex);
            pair_make(pt_pairex, "Computer", -590);
            pair_init_copy(pt_pair, pt_pairex);
            printf("<%s, %d>\n", (char*)pair_first(pt_pair), *(int*)pair_second(pt_pair));
            pair_destroy(pt_pair);
            pair_destroy(pt_pairex);
        }
        /*pair_assign      */
        {
            pair_t* pt_pair = create_pair(char*, int);
            pair_t* pt_pairex = create_pair(char*, int);
            if(pt_pair == NULL || pt_pairex == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            pair_init(pt_pairex);
            pair_assign(pt_pair, pt_pairex);
            printf("<%s, %d>\n", (char*)pair_first(pt_pair), *(int*)pair_second(pt_pair));
            pair_make(pt_pairex, "2009 - 2010", 2009);
            pair_assign(pt_pair, pt_pairex);
            printf("<%s, %d>\n", (char*)pair_first(pt_pair), *(int*)pair_second(pt_pair));
            pair_destroy(pt_pair);
            pair_destroy(pt_pairex);
        }
        /*pair_equal       */
        /*pair_not_equal   */
        /*pair_less        */
        /*pair_less_equal  */
        /*pair_great       */
        /*pair_great_equal */
        {
            pair_t* pt_pair = create_pair(char*, int);
            pair_t* pt_pairex = create_pair(char*, int);
            if(pt_pair == NULL || pt_pairex == NULL)
            {
                return;
            }
            pair_init(pt_pair);
            pair_init(pt_pairex);
            printf("<%s, %d>\n", (char*)pair_first(pt_pair), *(int*)pair_second(pt_pair));
            printf("<%s, %d>\n", (char*)pair_first(pt_pairex), *(int*)pair_second(pt_pairex));
            printf("equal: %d, not equal: %d, ",
                pair_equal(pt_pair, pt_pairex), pair_not_equal(pt_pair, pt_pairex));
            printf("less: %d, less equal: %d, ",
                pair_less(pt_pair, pt_pairex), pair_less_equal(pt_pair, pt_pairex));
            printf("great: %d, great equal: %d\n",
                pair_great(pt_pair, pt_pairex), pair_great_equal(pt_pair, pt_pairex));

            pair_make(pt_pair, "Linux", 100);
            printf("<%s, %d>\n", (char*)pair_first(pt_pair), *(int*)pair_second(pt_pair));
            printf("<%s, %d>\n", (char*)pair_first(pt_pairex), *(int*)pair_second(pt_pairex));
            printf("equal: %d, not equal: %d, ",
                pair_equal(pt_pair, pt_pairex), pair_not_equal(pt_pair, pt_pairex));
            printf("less: %d, less equal: %d, ",
                pair_less(pt_pair, pt_pairex), pair_less_equal(pt_pair, pt_pairex));
            printf("great: %d, great equal: %d\n",
                pair_great(pt_pair, pt_pairex), pair_great_equal(pt_pair, pt_pairex));

            pair_make(pt_pairex, "Linux", 100);
            printf("<%s, %d>\n", (char*)pair_first(pt_pair), *(int*)pair_second(pt_pair));
            printf("<%s, %d>\n", (char*)pair_first(pt_pairex), *(int*)pair_second(pt_pairex));
            printf("equal: %d, not equal: %d, ",
                pair_equal(pt_pair, pt_pairex), pair_not_equal(pt_pair, pt_pairex));
            printf("less: %d, less equal: %d, ",
                pair_less(pt_pair, pt_pairex), pair_less_equal(pt_pair, pt_pairex));
            printf("great: %d, great equal: %d\n",
                pair_great(pt_pair, pt_pairex), pair_great_equal(pt_pair, pt_pairex));

            pair_make(pt_pair, "AIX", 9100);
            printf("<%s, %d>\n", (char*)pair_first(pt_pair), *(int*)pair_second(pt_pair));
            printf("<%s, %d>\n", (char*)pair_first(pt_pairex), *(int*)pair_second(pt_pairex));
            printf("equal: %d, not equal: %d, ",
                pair_equal(pt_pair, pt_pairex), pair_not_equal(pt_pair, pt_pairex));
            printf("less: %d, less equal: %d, ",
                pair_less(pt_pair, pt_pairex), pair_less_equal(pt_pair, pt_pairex));
            printf("great: %d, great equal: %d\n",
                pair_great(pt_pair, pt_pairex), pair_great_equal(pt_pair, pt_pairex));
            pair_destroy(pt_pair);
            pair_destroy(pt_pairex);
        }
    }
}

/** local function implementation section **/
static void _sample_init(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    ((sample_t*)cpv_input)->_n_first = 0;
    ((sample_t*)cpv_input)->_n_second = 0;
    *(bool_t*)pv_output = true;
}

static void _sample_destory(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    ((sample_t*)cpv_input)->_n_first = 0;
    ((sample_t*)cpv_input)->_n_second = 0;
    *(bool_t*)pv_output = true;
}

static void _sample_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    if(((sample_t*)cpv_first)->_n_first < ((sample_t*)cpv_second)->_n_first)
    {
        *(bool_t*)pv_output = true;
    }
    else if((((sample_t*)cpv_first)->_n_first == ((sample_t*)cpv_second)->_n_first) &&
            (((sample_t*)cpv_first)->_n_second < ((sample_t*)cpv_second)->_n_second))
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}

static void _sample_copy(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    ((sample_t*)cpv_first)->_n_first = ((sample_t*)cpv_second)->_n_first;
    ((sample_t*)cpv_first)->_n_second = ((sample_t*)cpv_second)->_n_second;
    *(bool_t*)pv_output = true;
}

/** eof **/

