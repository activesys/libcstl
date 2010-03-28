/*
 *  The implementation of queue test.
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
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "cqueue.h"
#include "cvector.h"
#include "calgorithm.h"
#include "cfunctional.h"
#include "clist.h"
#include "test_queue.h"

/** local constant declaration and local macro section **/
#ifdef CSTL_QUEUE_LIST_SEQUENCE
#define _QUEUE_ITERATOR_BEGIN(pt_queue)\
    for(t_iter = list_begin(&(pt_queue)->_t_sequence);\
        !iterator_equal(t_iter, list_end(&(pt_queue)->_t_sequence));\
        t_iter = iterator_next(t_iter)){
#else
#define _QUEUE_ITERATOR_BEGIN(pt_queue)\
    for(t_iter = deque_begin(&(pt_queue)->_t_sequence);\
        !iterator_equal(t_iter, deque_end(&(pt_queue)->_t_sequence));\
        t_iter = iterator_next(t_iter)){
#endif

#define _QUEUE_ITERATOR_END }printf("\n");

#define _printqueue_c(pt_queue, fmt, type)\
    do{\
        iterator_t t_iter;\
        printf("==================================\n");\
        _QUEUE_ITERATOR_BEGIN(pt_queue)\
            printf(fmt, *(type*)iterator_get_pointer(t_iter));\
        _QUEUE_ITERATOR_END\
    }while(false)

/** local data type declaration and local struct, union, enum section **/
typedef struct _tagweather
{
    int  _n_temperature;
    char _s_city[31];
}weather_t;

/** local function prototype section **/
static void _print_queue_str(const queue_t* cpt_queue);
static void _printqueue(const queue_t* cpt_queue);
static void _weather_set(weather_t* pt_weather, const char* s_city, int n_temperature);
static void _printweather(const queue_t* cpt_queue);
static void _weather_init(const void* cpv_input, void* pv_output);
static void _weather_copy(const void* cpv_first, const void* cpv_second, void* pv_output);
static void _weather_less(const void* cpv_first, const void* cpv_second, void* pv_output);
static void _weather_destroy(const void* cpv_input, void* pv_output);
static void _print_pq_int(const priority_queue_t* cpt_pq);
static void _print_int(const void* cpv_input, void* pv_output);
static void _weather_greater(const void* cpv_first, const void* cpv_second, void* pv_output);
static void _print_pq_user(const priority_queue_t* cpt_pq);
static void _print_user(const void* cpv_input, void* pv_output);
static void _print_pq_cstl(const priority_queue_t* cpt_pq);
static void _print_list(const void* cpv_input, void* pv_output);
static void _print_pq_cstr(const priority_queue_t* cpt_pq);
static void _print_cstr(const void* cpv_input, void* pv_output);

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
void test_queue(void)
{
    /* c built-type */
    {
        /*create_queue     */
        {
            queue_t* pt_queue = create_queue(int);
            if(pt_queue == NULL)
            {
                return;
            }
            queue_init(pt_queue);
            _printqueue_c(pt_queue, "%d, ", int);
            queue_destroy(pt_queue);
        }
        /*queue_init       */
        /*queue_init_copy  */
        {
            queue_t* pt_queue1 = create_queue(double);
            queue_t* pt_queue2 = create_queue(double);
            if(pt_queue1 == NULL || pt_queue2 == NULL)
            {
                return;
            }
            queue_init(pt_queue2);
            queue_push(pt_queue2, 38.42);
            queue_push(pt_queue2, 5.0);
            queue_push(pt_queue2, 100.111);
            queue_init_copy(pt_queue1, pt_queue2);
            _printqueue_c(pt_queue1, "%lf, ", double);
            queue_destroy(pt_queue1);
            queue_destroy(pt_queue2);
        }
        /*queue_destroy    */
        /*queue_assign     */
        {
            queue_t* pt_queue1 = create_queue(int);
            queue_t* pt_queue2 = create_queue(int);
            if(pt_queue1 == NULL || pt_queue2 == NULL)
            {
                return;
            }
            queue_init(pt_queue1);
            queue_init(pt_queue2);
            queue_assign(pt_queue1, pt_queue2);
            _printqueue_c(pt_queue1, "%d, ", int);
            queue_push(pt_queue2, 45);
            queue_push(pt_queue2, -56);
            queue_push(pt_queue2, 0);
            queue_push(pt_queue2, 33);
            queue_assign(pt_queue1, pt_queue2);
            _printqueue_c(pt_queue1, "%d, ", int);
            queue_push(pt_queue2, 8899);
            queue_push(pt_queue2, -4501);
            queue_assign(pt_queue1, pt_queue2);
            _printqueue_c(pt_queue1, "%d, ", int);
            queue_pop(pt_queue2);
            queue_pop(pt_queue2);
            queue_pop(pt_queue2);
            queue_pop(pt_queue2);
            queue_assign(pt_queue1, pt_queue2);
            _printqueue_c(pt_queue1, "%d, ", int);
            while(!queue_empty(pt_queue2))
            {
                queue_pop(pt_queue2);
            }
            queue_assign(pt_queue1, pt_queue2);
            _printqueue_c(pt_queue1, "%d, ", int);
            queue_destroy(pt_queue1);
            queue_destroy(pt_queue2);
        }
        /*queue_empty      */
        {
            queue_t* pt_queue = create_queue(int);
            if(pt_queue == NULL)
            {
                return;
            }
            queue_init(pt_queue);
            printf("empty : %d, size : %d\n", queue_empty(pt_queue), queue_size(pt_queue));
            queue_push(pt_queue, 45);
            queue_push(pt_queue, 2);
            queue_push(pt_queue, -5);
            printf("empty : %d, size : %d\n", queue_empty(pt_queue), queue_size(pt_queue));
            queue_destroy(pt_queue);
        }
        /*queue_size       */
        /*queue_front      */
        {
            queue_t* pt_queue = create_queue(double);
            if(pt_queue == NULL)
            {
                return;
            }
            queue_init(pt_queue);
            _printqueue_c(pt_queue, "%lf, ", double);
            if(queue_front(pt_queue) == NULL && queue_back(pt_queue) == NULL)
            {
                printf("front and back are null!\n");
            }
            queue_push(pt_queue, 8.4);
            queue_push(pt_queue, 29.02);
            queue_push(pt_queue, 333.45);
            queue_push(pt_queue, 20.009);
            _printqueue_c(pt_queue, "%lf, ", double);
            while(!queue_empty(pt_queue))
            {
                if(queue_front(pt_queue) != NULL && queue_back(pt_queue) != NULL)
                {
                    *(double*)queue_front(pt_queue) = 2.0;
                    *(double*)queue_back(pt_queue) += 100.0;
                    _printqueue_c(pt_queue, "%lf, ", double);
                }
                queue_pop(pt_queue);
            }
            queue_destroy(pt_queue);
        }
        /*queue_back       */
        /*queue_push       */
        /*queue_pop        */
        /*queue_equal      */
        {
            queue_t* pt_queue1 = create_queue(int);
            queue_t* pt_queue2 = create_queue(int);
            if(pt_queue1 == NULL || pt_queue2 == NULL)
            {
                return;
            }
            queue_init(pt_queue1);
            queue_init(pt_queue2);
            _printqueue_c(pt_queue1, "%d, ", int);
            _printqueue_c(pt_queue2, "%d, ", int);
            printf("equal : %d, not equal : %d, ",
                queue_equal(pt_queue1, pt_queue2), queue_not_equal(pt_queue1, pt_queue2));
            printf("less : %d, less equal : %d, ",
                queue_less(pt_queue1, pt_queue2), queue_less_equal(pt_queue1, pt_queue2));
            printf("greater : %d, greater equal : %d\n",
                queue_greater(pt_queue1, pt_queue2), queue_greater_equal(pt_queue1, pt_queue2));
            queue_push(pt_queue1, 45);
            _printqueue_c(pt_queue1, "%d, ", int);
            _printqueue_c(pt_queue2, "%d, ", int);
            printf("equal : %d, not equal : %d, ",
                queue_equal(pt_queue1, pt_queue2), queue_not_equal(pt_queue1, pt_queue2));
            printf("less : %d, less equal : %d, ",
                queue_less(pt_queue1, pt_queue2), queue_less_equal(pt_queue1, pt_queue2));
            printf("greater : %d, greater equal : %d\n",
                queue_greater(pt_queue1, pt_queue2), queue_greater_equal(pt_queue1, pt_queue2));
            queue_push(pt_queue2, 45);
            _printqueue_c(pt_queue1, "%d, ", int);
            _printqueue_c(pt_queue2, "%d, ", int);
            printf("equal : %d, not equal : %d, ",
                queue_equal(pt_queue1, pt_queue2), queue_not_equal(pt_queue1, pt_queue2));
            printf("less : %d, less equal : %d, ",
                queue_less(pt_queue1, pt_queue2), queue_less_equal(pt_queue1, pt_queue2));
            printf("greater : %d, greater equal : %d\n",
                queue_greater(pt_queue1, pt_queue2), queue_greater_equal(pt_queue1, pt_queue2));
            queue_push(pt_queue1, -39);
            queue_push(pt_queue2, -4);
            _printqueue_c(pt_queue1, "%d, ", int);
            _printqueue_c(pt_queue2, "%d, ", int);
            printf("equal : %d, not equal : %d, ",
                queue_equal(pt_queue1, pt_queue2), queue_not_equal(pt_queue1, pt_queue2));
            printf("less : %d, less equal : %d, ",
                queue_less(pt_queue1, pt_queue2), queue_less_equal(pt_queue1, pt_queue2));
            printf("greater : %d, greater equal : %d\n",
                queue_greater(pt_queue1, pt_queue2), queue_greater_equal(pt_queue1, pt_queue2));
            queue_push(pt_queue1, 100);
            _printqueue_c(pt_queue1, "%d, ", int);
            _printqueue_c(pt_queue2, "%d, ", int);
            printf("equal : %d, not equal : %d, ",
                queue_equal(pt_queue1, pt_queue2), queue_not_equal(pt_queue1, pt_queue2));
            printf("less : %d, less equal : %d, ",
                queue_less(pt_queue1, pt_queue2), queue_less_equal(pt_queue1, pt_queue2));
            printf("greater : %d, greater equal : %d\n",
                queue_greater(pt_queue1, pt_queue2), queue_greater_equal(pt_queue1, pt_queue2));
            queue_destroy(pt_queue1);
            queue_destroy(pt_queue2);
        }
        /*queue_not_equal  */
        /*queue_less       */
        /*queue_less_equal */
        /*queue_greater      */
        /*queue_greater_equal*/
    }
    /* user defined type */
    {
        type_register(weather_t, _weather_init, _weather_copy, _weather_less, _weather_destroy);
        type_duplicate(weather_t, struct _tagweather);
        _type_debug();
        /*create_queue     */
        {
            queue_t* pt_queue = create_queue(weather_t);
            if(pt_queue == NULL)
            {
                return;
            }
            queue_init(pt_queue);
            _printweather(pt_queue);
            queue_destroy(pt_queue);
        }
        /*queue_init       */
        /*queue_init_copy  */
        {
            queue_t* pt_queue1 = create_queue(weather_t);
            queue_t* pt_queue2 = create_queue(weather_t);
            weather_t t_wea;
            bool_t t_result = 0;
            if(pt_queue1 == NULL || pt_queue2 == NULL)
            {
                return;
            }
            queue_init(pt_queue2);

            _weather_init(&t_wea, &t_result);
            _weather_set(&t_wea, "Shenyang", 3);
            queue_push(pt_queue2, &t_wea);
            _weather_set(&t_wea, "Beijing", 7);
            queue_push(pt_queue2, &t_wea);
            _weather_set(&t_wea, "Haerbin", -4);
            queue_push(pt_queue2, &t_wea);
            _weather_destroy(&t_wea, &t_result);

            queue_init_copy(pt_queue1, pt_queue2);
            _printweather(pt_queue1);

            queue_destroy(pt_queue1);
            queue_destroy(pt_queue2);
        }
        /*queue_destroy    */
        /*queue_assign     */
        {
            queue_t* pt_queue1 = create_queue(weather_t);
            queue_t* pt_queue2 = create_queue(weather_t);
            weather_t t_wea;
            bool_t t_result = 0;
            if(pt_queue1 == NULL || pt_queue2 == NULL)
            {
                return;
            }
            queue_init(pt_queue2);
            queue_init(pt_queue1);
            queue_assign(pt_queue1, pt_queue2);

            _weather_init(&t_wea, &t_result);

            _weather_set(&t_wea, "Shenyang", 3);
            queue_push(pt_queue2, &t_wea);
            _weather_set(&t_wea, "Beijing", 7);
            queue_push(pt_queue2, &t_wea);
            _weather_set(&t_wea, "Haerbin", -4);
            queue_push(pt_queue2, &t_wea);
            queue_assign(pt_queue1, pt_queue2);
            _printweather(pt_queue1);

            _weather_set(&t_wea, "Nanjing", 15);
            queue_push(pt_queue2, &t_wea);
            _weather_set(&t_wea, "Shanghai", 19);
            queue_push(pt_queue2, &t_wea);
            queue_assign(pt_queue1, pt_queue2);
            _printweather(pt_queue1);

            queue_pop(pt_queue2);
            queue_pop(pt_queue2);
            queue_pop(pt_queue2);
            queue_assign(pt_queue1, pt_queue2);
            _printweather(pt_queue1);

            while(!queue_empty(pt_queue2))
            {
                queue_pop(pt_queue2);
            }
            queue_assign(pt_queue1, pt_queue2);
            _printweather(pt_queue1);

            _weather_destroy(&t_wea, &t_result);

            queue_destroy(pt_queue1);
            queue_destroy(pt_queue2);
        }
        /*queue_empty      */
        {
            queue_t* pt_queue = create_queue(struct _tagweather);
            weather_t t_wea;
            bool_t t_result = 0;
            if(pt_queue == NULL)
            {
                return;
            }
            queue_init(pt_queue);
            printf("empty : %d, size : %d\n", queue_empty(pt_queue), queue_size(pt_queue));

            _weather_init(&t_wea, &t_result);
            _weather_set(&t_wea, "Shenyang", 3);
            queue_push(pt_queue, &t_wea);
            _weather_set(&t_wea, "Beijing", 7);
            queue_push(pt_queue, &t_wea);
            _weather_set(&t_wea, "Haerbin", -4);
            queue_push(pt_queue, &t_wea);
            _weather_destroy(&t_wea, &t_result);

            printf("empty : %d, size : %d\n", queue_empty(pt_queue), queue_size(pt_queue));
            queue_destroy(pt_queue);
        }
        /*queue_size       */
        /*queue_front      */
        {
            queue_t* pt_queue = create_queue(weather_t);
            weather_t t_wea;
            bool_t t_result = false;
            if(pt_queue == NULL)
            {
                return;
            }
            queue_init(pt_queue);
            _printweather(pt_queue);
            if(queue_front(pt_queue) == NULL && queue_back(pt_queue) == NULL)
            {
                printf("front and back are null!\n");
            }
            _weather_init(&t_wea, &t_result);
            _weather_set(&t_wea, "Shenyang", 3);
            queue_push(pt_queue, &t_wea);
            _weather_set(&t_wea, "Beijing", 7);
            queue_push(pt_queue, &t_wea);
            _weather_set(&t_wea, "Haerbin", -4);
            queue_push(pt_queue, &t_wea);
            _weather_destroy(&t_wea, &t_result);
            _printweather(pt_queue);
            while(!queue_empty(pt_queue))
            {
                if(queue_front(pt_queue) != NULL && queue_back(pt_queue) != NULL)
                {
                    ((weather_t*)queue_front(pt_queue))->_n_temperature = 100;
                    ((weather_t*)queue_back(pt_queue))->_n_temperature += 100;
                    _printweather(pt_queue);
                }
                queue_pop(pt_queue);
            }
            queue_destroy(pt_queue);
        }
        /*queue_back       */
        /*queue_push       */
        /*queue_pop        */
        /*queue_equal      */
        {
            queue_t* pt_queue1 = create_queue(weather_t);
            queue_t* pt_queue2 = create_queue(struct _tagweather);
            weather_t t_wea;
            if(pt_queue1 == NULL || pt_queue2 == NULL)
            {
                return;
            }
            queue_init(pt_queue1);
            queue_init(pt_queue2);
            _printweather(pt_queue1);
            _printweather(pt_queue2);
            printf("equal : %d, not equal : %d, ",
                queue_equal(pt_queue1, pt_queue2), queue_not_equal(pt_queue1, pt_queue2));
            printf("less : %d, less equal : %d, ",
                queue_less(pt_queue1, pt_queue2), queue_less_equal(pt_queue1, pt_queue2));
            printf("greater : %d, greater equal : %d\n",
                queue_greater(pt_queue1, pt_queue2), queue_greater_equal(pt_queue1, pt_queue2));

            _weather_set(&t_wea, "Shenyang", 3);
            queue_push(pt_queue1, &t_wea);
            _printweather(pt_queue1);
            _printweather(pt_queue2);
            printf("equal : %d, not equal : %d, ",
                queue_equal(pt_queue1, pt_queue2), queue_not_equal(pt_queue1, pt_queue2));
            printf("less : %d, less equal : %d, ",
                queue_less(pt_queue1, pt_queue2), queue_less_equal(pt_queue1, pt_queue2));
            printf("greater : %d, greater equal : %d\n",
                queue_greater(pt_queue1, pt_queue2), queue_greater_equal(pt_queue1, pt_queue2));

            queue_push(pt_queue2, &t_wea);
            _printweather(pt_queue1);
            _printweather(pt_queue2);
            printf("equal : %d, not equal : %d, ",
                queue_equal(pt_queue1, pt_queue2), queue_not_equal(pt_queue1, pt_queue2));
            printf("less : %d, less equal : %d, ",
                queue_less(pt_queue1, pt_queue2), queue_less_equal(pt_queue1, pt_queue2));
            printf("greater : %d, greater equal : %d\n",
                queue_greater(pt_queue1, pt_queue2), queue_greater_equal(pt_queue1, pt_queue2));

            _weather_set(&t_wea, "Changchun", 0);
            queue_push(pt_queue1, &t_wea);
            _weather_set(&t_wea, "Wuhan", 22);
            queue_push(pt_queue2, &t_wea);
            _printweather(pt_queue1);
            _printweather(pt_queue2);
            printf("equal : %d, not equal : %d, ",
                queue_equal(pt_queue1, pt_queue2), queue_not_equal(pt_queue1, pt_queue2));
            printf("less : %d, less equal : %d, ",
                queue_less(pt_queue1, pt_queue2), queue_less_equal(pt_queue1, pt_queue2));
            printf("greater : %d, greater equal : %d\n",
                queue_greater(pt_queue1, pt_queue2), queue_greater_equal(pt_queue1, pt_queue2));

            _weather_set(&t_wea, "Guangzhou", 27);
            queue_push(pt_queue1, &t_wea);
            _printweather(pt_queue1);
            _printweather(pt_queue2);
            printf("equal : %d, not equal : %d, ",
                queue_equal(pt_queue1, pt_queue2), queue_not_equal(pt_queue1, pt_queue2));
            printf("less : %d, less equal : %d, ",
                queue_less(pt_queue1, pt_queue2), queue_less_equal(pt_queue1, pt_queue2));
            printf("greater : %d, greater equal : %d\n",
                queue_greater(pt_queue1, pt_queue2), queue_greater_equal(pt_queue1, pt_queue2));

            queue_destroy(pt_queue1);
            queue_destroy(pt_queue2);
        }
        /*queue_not_equal  */
        /*queue_less       */
        /*queue_less_equal */
        /*queue_greater      */
        /*queue_greater_equal*/
    }
    /* cstl built-in type */
    {
        /*create_queue     */
        {
            queue_t* pt_queue = create_queue(queue_t<int>);
            if(pt_queue == NULL)
            {
                return;
            }
            queue_init(pt_queue);
            _printqueue(pt_queue);
            queue_destroy(pt_queue);
        }
        /*queue_init       */
        /*queue_init_copy  */
        {
        {
            queue_t* pt_queue1 = create_queue(queue_t<int>);
            queue_t* pt_queue2 = create_queue(queue_t<int>);
            queue_t* pt_queueex = create_queue(int);
            if(pt_queue1 == NULL || pt_queue2 == NULL || pt_queueex == NULL)
            {
                return;
            }
            queue_init(pt_queueex);
            queue_init(pt_queue2);
            queue_push(pt_queueex, 38);
            queue_push(pt_queue2, pt_queueex);
            queue_push(pt_queueex, 5);
            queue_push(pt_queue2, pt_queueex);
            queue_push(pt_queueex, 100);
            queue_push(pt_queue2, pt_queueex);
            queue_init_copy(pt_queue1, pt_queue2);
            _printqueue(pt_queue1);
            queue_destroy(pt_queue1);
            queue_destroy(pt_queue2);
            queue_destroy(pt_queueex);
        }
        }
        /*queue_destroy    */
        /*queue_assign     */
        {
            queue_t* pt_queue1 = create_queue(queue_t<int>);
            queue_t* pt_queue2 = create_queue(queue_t<int>);
            queue_t* pt_queueex = create_queue(int);
            if(pt_queue1 == NULL || pt_queue2 == NULL || pt_queueex == NULL)
            {
                return;
            }
            queue_init(pt_queue1);
            queue_init(pt_queue2);
            queue_init(pt_queueex);
            queue_assign(pt_queue1, pt_queue2);
            _printqueue(pt_queue1);

            queue_push(pt_queueex, 45);
            queue_push(pt_queue2, pt_queueex);
            queue_push(pt_queueex, -56);
            queue_push(pt_queue2, pt_queueex);
            queue_push(pt_queueex, 0);
            queue_push(pt_queue2, pt_queueex);
            queue_push(pt_queueex, 33);
            queue_push(pt_queue2, pt_queueex);
            queue_assign(pt_queue1, pt_queue2);
            _printqueue(pt_queue1);

            queue_push(pt_queueex, 8899);
            queue_push(pt_queue2, pt_queueex);
            queue_push(pt_queueex, -4501);
            queue_push(pt_queue2, pt_queueex);
            queue_assign(pt_queue1, pt_queue2);
            _printqueue(pt_queue1);

            queue_pop(pt_queue2);
            queue_pop(pt_queue2);
            queue_pop(pt_queue2);
            queue_pop(pt_queue2);
            queue_assign(pt_queue1, pt_queue2);
            _printqueue(pt_queue1);

            while(!queue_empty(pt_queue2))
            {
                queue_pop(pt_queue2);
            }
            queue_assign(pt_queue1, pt_queue2);
            _printqueue(pt_queue1);

            queue_destroy(pt_queue1);
            queue_destroy(pt_queue2);
            queue_destroy(pt_queueex);
        }
        /*queue_empty      */
        {
            queue_t* pt_queue = create_queue(queue_t<int>);
            queue_t* pt_queueex = create_queue(int);
            if(pt_queue == NULL || pt_queueex == NULL)
            {
                return;
            }
            queue_init(pt_queue);
            queue_init(pt_queueex);
            printf("empty : %d, size : %d\n", queue_empty(pt_queue), queue_size(pt_queue));
            queue_push(pt_queueex, 45);
            queue_push(pt_queue, pt_queueex);
            queue_push(pt_queueex, 2);
            queue_push(pt_queue, pt_queueex);
            queue_push(pt_queueex, -5);
            queue_push(pt_queue, pt_queueex);
            printf("empty : %d, size : %d\n", queue_empty(pt_queue), queue_size(pt_queue));
            queue_destroy(pt_queue);
            queue_destroy(pt_queueex);
        }
        /*queue_size       */
        /*queue_front      */
        {
            queue_t* pt_queue = create_queue(queue_t<int>);
            queue_t* pt_queueex = create_queue(int);
            if(pt_queue == NULL || pt_queueex == NULL)
            {
                return;
            }
            queue_init(pt_queue);
            queue_init(pt_queueex);
            _printqueue(pt_queue);
            if(queue_front(pt_queue) == NULL && queue_back(pt_queue) == NULL)
            {
                printf("front and back are null!\n");
            }
            queue_push(pt_queueex, 8);
            queue_push(pt_queue, pt_queueex);
            queue_push(pt_queueex, 29);
            queue_push(pt_queue, pt_queueex);
            queue_push(pt_queueex, 333);
            queue_push(pt_queue, pt_queueex);
            queue_push(pt_queueex, 2009);
            queue_push(pt_queue, pt_queueex);
            _printqueue(pt_queue);
            while(!queue_empty(pt_queue))
            {
                if(queue_front(pt_queue) != NULL && queue_back(pt_queue) != NULL)
                {
                    queue_push(queue_front(pt_queue), 10000);
                    queue_push(queue_back(pt_queue), - 10000);
                    _printqueue(pt_queue);
                }
                queue_pop(pt_queue);
            }
            queue_destroy(pt_queue);
            queue_destroy(pt_queueex);
        }
        /*queue_back       */
        /*queue_push       */
        /*queue_pop        */
        /*queue_equal      */
        {
            queue_t* pt_queue1 = create_queue(queue_t<int>);
            queue_t* pt_queue2 = create_queue(queue_t<int>);
            queue_t* pt_queueex = create_queue(int);
            if(pt_queue1 == NULL || pt_queue2 == NULL || pt_queueex == NULL)
            {
                return;
            }
            queue_init(pt_queue1);
            queue_init(pt_queue2);
            queue_init(pt_queueex);
            _printqueue(pt_queue1);
            _printqueue(pt_queue2);
            printf("equal : %d, not equal : %d, ",
                queue_equal(pt_queue1, pt_queue2), queue_not_equal(pt_queue1, pt_queue2));
            printf("less : %d, less equal : %d, ",
                queue_less(pt_queue1, pt_queue2), queue_less_equal(pt_queue1, pt_queue2));
            printf("greater : %d, greater equal : %d\n",
                queue_greater(pt_queue1, pt_queue2), queue_greater_equal(pt_queue1, pt_queue2));

            queue_push(pt_queueex, 45);
            queue_push(pt_queue1, pt_queueex);
            _printqueue(pt_queue1);
            _printqueue(pt_queue2);
            printf("equal : %d, not equal : %d, ",
                queue_equal(pt_queue1, pt_queue2), queue_not_equal(pt_queue1, pt_queue2));
            printf("less : %d, less equal : %d, ",
                queue_less(pt_queue1, pt_queue2), queue_less_equal(pt_queue1, pt_queue2));
            printf("greater : %d, greater equal : %d\n",
                queue_greater(pt_queue1, pt_queue2), queue_greater_equal(pt_queue1, pt_queue2));

            queue_push(pt_queue2, pt_queueex);
            _printqueue(pt_queue1);
            _printqueue(pt_queue2);
            printf("equal : %d, not equal : %d, ",
                queue_equal(pt_queue1, pt_queue2), queue_not_equal(pt_queue1, pt_queue2));
            printf("less : %d, less equal : %d, ",
                queue_less(pt_queue1, pt_queue2), queue_less_equal(pt_queue1, pt_queue2));
            printf("greater : %d, greater equal : %d\n",
                queue_greater(pt_queue1, pt_queue2), queue_greater_equal(pt_queue1, pt_queue2));

            queue_pop(pt_queueex);
            queue_push(pt_queueex, -39);
            queue_push(pt_queue1, pt_queueex);
            queue_pop(pt_queueex);
            queue_push(pt_queueex, -4);
            queue_push(pt_queue2, pt_queueex);
            _printqueue(pt_queue1);
            _printqueue(pt_queue2);
            printf("equal : %d, not equal : %d, ",
                queue_equal(pt_queue1, pt_queue2), queue_not_equal(pt_queue1, pt_queue2));
            printf("less : %d, less equal : %d, ",
                queue_less(pt_queue1, pt_queue2), queue_less_equal(pt_queue1, pt_queue2));
            printf("greater : %d, greater equal : %d\n",
                queue_greater(pt_queue1, pt_queue2), queue_greater_equal(pt_queue1, pt_queue2));

            queue_pop(pt_queueex);
            queue_push(pt_queueex, 100);
            queue_push(pt_queue1, pt_queueex);
            _printqueue(pt_queue1);
            _printqueue(pt_queue2);
            printf("equal : %d, not equal : %d, ",
                queue_equal(pt_queue1, pt_queue2), queue_not_equal(pt_queue1, pt_queue2));
            printf("less : %d, less equal : %d, ",
                queue_less(pt_queue1, pt_queue2), queue_less_equal(pt_queue1, pt_queue2));
            printf("greater : %d, greater equal : %d\n",
                queue_greater(pt_queue1, pt_queue2), queue_greater_equal(pt_queue1, pt_queue2));

            queue_destroy(pt_queue1);
            queue_destroy(pt_queue2);
            queue_destroy(pt_queueex);
        }
        /*queue_not_equal  */
        /*queue_less       */
        /*queue_less_equal */
        /*queue_greater      */
        /*queue_greater_equal*/
    }
    /* c-string type */
    {
        printf("**********************************************\n");
        /*create_queue     */
        {
            queue_t* pt_queue = create_queue(char*);
            if(pt_queue == NULL)
            {
                return;
            }
            queue_init(pt_queue);
            _print_queue_str(pt_queue);
            queue_destroy(pt_queue);
        }
        /*queue_init       */
        /*queue_init_copy  */
        {
            queue_t* pt_queue = create_queue(char*);
            queue_t* pt_queueex = create_queue(char*);
            if(pt_queue == NULL || pt_queueex == NULL)
            {
                return;
            }
            queue_init(pt_queueex);
            queue_push(pt_queueex, "DASS");
            queue_push(pt_queueex, "cryptographic");
            queue_push(pt_queueex, "Today");
            queue_init_copy(pt_queue, pt_queueex);
            _print_queue_str(pt_queue);
            queue_destroy(pt_queue);
            queue_destroy(pt_queueex);
        }
        /*queue_destroy    */
        /*queue_assign     */
        {
            queue_t* pt_queue = create_queue(char*);
            queue_t* pt_queueex = create_queue(char*);
            if(pt_queue == NULL || pt_queueex == NULL)
            {
                return;
            }
            queue_init(pt_queue);
            queue_init(pt_queueex);
            queue_assign(pt_queue, pt_queueex);
            _print_queue_str(pt_queue);
            queue_push(pt_queueex, "Timestamps vs. Challenge/Response");
            queue_push(pt_queueex, "as timed out.");
            queue_push(pt_queueex, "The disadvantage");
            queue_assign(pt_queue, pt_queueex);
            _print_queue_str(pt_queue);
            while(!queue_empty(pt_queueex))
            {
                queue_pop(pt_queueex);
            }
            queue_assign(pt_queue, pt_queueex);
            _print_queue_str(pt_queue);
            queue_destroy(pt_queue);
            queue_destroy(pt_queueex);
        }
        /*queue_empty      */
        /*queue_size       */
        /*queue_front      */
        /*queue_back       */
        /*queue_push       */
        /*queue_pop        */
        {
            queue_t* pt_queue = create_queue(char*);
            if(pt_queue == NULL)
            {
                return;
            }
            queue_init(pt_queue);
            _print_queue_str(pt_queue);
            queue_push(pt_queue, "Delegation");
            puts(queue_back(pt_queue));
            queue_push(pt_queue, "Certification Authorities");
            puts(queue_back(pt_queue));
            queue_push(pt_queue, "Certification Authority Hierarchy");
            puts(queue_back(pt_queue));
            _print_queue_str(pt_queue);
            while(!queue_empty(pt_queue))
            {
                puts(queue_front(pt_queue));
                queue_pop(pt_queue);
            }
            _print_queue_str(pt_queue);
            queue_destroy(pt_queue);
        }
        /*queue_equal      */
        /*queue_not_equal  */
        /*queue_less       */
        /*queue_less_equal */
        /*queue_greater      */
        /*queue_greater_equal*/
        {
            queue_t* pt_queue = create_queue(char*);
            queue_t* pt_queueex = create_queue(char*);
            if(pt_queue == NULL || pt_queueex == NULL)
            {
                return;
            }
            queue_init(pt_queue);
            queue_init(pt_queueex);
            _print_queue_str(pt_queue);
            _print_queue_str(pt_queueex);
            printf("equal: %d, not queue: %d, ",
                queue_equal(pt_queue, pt_queueex), queue_not_equal(pt_queue, pt_queueex));
            printf("less: %d, less equal: %d, ",
                queue_less(pt_queue, pt_queueex), queue_less_equal(pt_queue, pt_queueex));
            printf("greater: %d, greater equal: %d\n",
                queue_greater(pt_queue, pt_queueex), queue_greater_equal(pt_queue, pt_queueex));

            queue_push(pt_queue, "Because the CA hierarchy");
            _print_queue_str(pt_queue);
            _print_queue_str(pt_queueex);
            printf("equal: %d, not queue: %d, ",
                queue_equal(pt_queue, pt_queueex), queue_not_equal(pt_queue, pt_queueex));
            printf("less: %d, less equal: %d, ",
                queue_less(pt_queue, pt_queueex), queue_less_equal(pt_queue, pt_queueex));
            printf("greater: %d, greater equal: %d\n",
                queue_greater(pt_queue, pt_queueex), queue_greater_equal(pt_queue, pt_queueex));

            queue_push(pt_queueex, "Because the CA hierarchy");
            _print_queue_str(pt_queue);
            _print_queue_str(pt_queueex);
            printf("equal: %d, not queue: %d, ",
                queue_equal(pt_queue, pt_queueex), queue_not_equal(pt_queue, pt_queueex));
            printf("less: %d, less equal: %d, ",
                queue_less(pt_queue, pt_queueex), queue_less_equal(pt_queue, pt_queueex));
            printf("greater: %d, greater equal: %d\n",
                queue_greater(pt_queue, pt_queueex), queue_greater_equal(pt_queue, pt_queueex));

            queue_push(pt_queueex, "The implication is that");
            _print_queue_str(pt_queue);
            _print_queue_str(pt_queueex);
            printf("equal: %d, not queue: %d, ",
                queue_equal(pt_queue, pt_queueex), queue_not_equal(pt_queue, pt_queueex));
            printf("less: %d, less equal: %d, ",
                queue_less(pt_queue, pt_queueex), queue_less_equal(pt_queue, pt_queueex));
            printf("greater: %d, greater equal: %d\n",
                queue_greater(pt_queue, pt_queueex), queue_greater_equal(pt_queue, pt_queueex));

            queue_push(pt_queue, "DASS uses the X.500");
            queue_push(pt_queue, "In concept");
            _print_queue_str(pt_queue);
            _print_queue_str(pt_queueex);
            printf("equal: %d, not queue: %d, ",
                queue_equal(pt_queue, pt_queueex), queue_not_equal(pt_queue, pt_queueex));
            printf("less: %d, less equal: %d, ",
                queue_less(pt_queue, pt_queueex), queue_less_equal(pt_queue, pt_queueex));
            printf("greater: %d, greater equal: %d\n",
                queue_greater(pt_queue, pt_queueex), queue_greater_equal(pt_queue, pt_queueex));
            queue_destroy(pt_queue);
            queue_destroy(pt_queueex);
        }
    }
}

void test_priority_queue(void)
{
    /* c built-in type */
    {
        /*_create_priority_queue           */
        /*priority_queue_init              */
        {
            priority_queue_t* pt_pq = create_priority_queue(int);
            if(pt_pq == NULL)
            {
                return;
            }
            priority_queue_init(pt_pq);
            _print_pq_int(pt_pq);
            priority_queue_push(pt_pq, 45);
            priority_queue_push(pt_pq, 5);
            priority_queue_push(pt_pq, 95);
            priority_queue_push(pt_pq, 4);
            priority_queue_push(pt_pq, -5);
            _print_pq_int(pt_pq);
            priority_queue_destroy(pt_pq);
        }
        /*priority_queue_init_ex           */
        {
            priority_queue_t* pt_pq = create_priority_queue(int);
            if(pt_pq == NULL)
            {
                return;
            }
            priority_queue_init_ex(pt_pq, fun_greater_int);
            _print_pq_int(pt_pq);
            priority_queue_push(pt_pq, 45);
            priority_queue_push(pt_pq, 5);
            priority_queue_push(pt_pq, 95);
            priority_queue_push(pt_pq, 4);
            priority_queue_push(pt_pq, -5);
            _print_pq_int(pt_pq);
            priority_queue_destroy(pt_pq);
        }
        /*priority_queue_init_copy         */
        {
            priority_queue_t* pt_pq = create_priority_queue(int);
            priority_queue_t* pt_pqex = create_priority_queue(int);
            if(pt_pq == NULL || pt_pqex == NULL)
            {
                return;
            }
            priority_queue_init_ex(pt_pqex, fun_greater_int);
            priority_queue_push(pt_pqex, 45);
            priority_queue_push(pt_pqex, 5);
            priority_queue_push(pt_pqex, 95);
            priority_queue_push(pt_pqex, 4);
            priority_queue_push(pt_pqex, -5);
            _print_pq_int(pt_pqex);
            priority_queue_init_copy(pt_pq, pt_pqex);
            _print_pq_int(pt_pq);

            priority_queue_destroy(pt_pq);
            priority_queue_destroy(pt_pqex);
        }
        /*priority_queue_init_copy_range   */
        {
            priority_queue_t* pt_pq = create_priority_queue(int);
            vector_t* pt_vec = create_vector(int);
            if(pt_pq == NULL || pt_vec == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            vector_push_back(pt_vec, 45);
            vector_push_back(pt_vec, 5);
            vector_push_back(pt_vec, 95);
            vector_push_back(pt_vec, 4);
            vector_push_back(pt_vec, -5);
            priority_queue_init_copy_range(pt_pq, vector_begin(pt_vec), vector_end(pt_vec));
            _print_pq_int(pt_pq);
            vector_destroy(pt_vec);
            priority_queue_destroy(pt_pq);
        }
        /*priority_queue_init_copy_range_ex*/
        {
            priority_queue_t* pt_pq = create_priority_queue(int);
            vector_t* pt_vec = create_vector(int);
            if(pt_pq == NULL || pt_vec == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            vector_push_back(pt_vec, 45);
            vector_push_back(pt_vec, 5);
            vector_push_back(pt_vec, 95);
            vector_push_back(pt_vec, 4);
            vector_push_back(pt_vec, -5);
            priority_queue_init_copy_range_ex(pt_pq,
                vector_begin(pt_vec), vector_end(pt_vec), fun_greater_int);
            _print_pq_int(pt_pq);
            vector_destroy(pt_vec);
            priority_queue_destroy(pt_pq);
        }
        /*priority_queue_destroy           */
        /*priority_queue_assign            */
        {
            priority_queue_t* pt_pq = create_priority_queue(int);
            priority_queue_t* pt_pqex = create_priority_queue(int);
            if(pt_pq == NULL || pt_pqex == NULL)
            {
                return;
            }
            priority_queue_init(pt_pq);
            priority_queue_init_ex(pt_pqex, fun_greater_int);
            priority_queue_push(pt_pqex, 45);
            priority_queue_push(pt_pqex, 5);
            priority_queue_push(pt_pqex, 95);
            priority_queue_push(pt_pqex, 4);
            priority_queue_push(pt_pqex, -5);
            _print_pq_int(pt_pqex);
            priority_queue_assign(pt_pq, pt_pqex);
            _print_pq_int(pt_pq);
            priority_queue_destroy(pt_pq);
            priority_queue_destroy(pt_pqex);
        }
        /*priority_queue_empty             */
        /*priority_queue_size              */
        /*priority_queue_top               */
        /*priority_queue_push              */
        /*priority_queue_pop               */
        {
            priority_queue_t* pt_pq = create_priority_queue(int);
            if(pt_pq == NULL)
            {
                return;
            }
            priority_queue_init_ex(pt_pq, fun_greater_int);
            _print_pq_int(pt_pq);
            priority_queue_push(pt_pq, 45);
            priority_queue_push(pt_pq, 5);
            priority_queue_push(pt_pq, 95);
            priority_queue_push(pt_pq, 4);
            priority_queue_push(pt_pq, -5);
            _print_pq_int(pt_pq);
            priority_queue_pop(pt_pq);
            _print_pq_int(pt_pq);
            while(!priority_queue_empty(pt_pq))
            {
                priority_queue_pop(pt_pq);
            }
            _print_pq_int(pt_pq);
            priority_queue_destroy(pt_pq);
        }
    }
    /* user defined type */
    {
        type_register(weather_t, _weather_init, _weather_copy, _weather_less, _weather_destroy);
        type_duplicate(weather_t, struct _tagweather);
        /*_create_priority_queue           */
        /*priority_queue_init              */
        {
            priority_queue_t* pt_pq = create_priority_queue(weather_t);
            weather_t t_wea;
            bool_t t_result;
            if(pt_pq == NULL)
            {
                return;
            }
            priority_queue_init(pt_pq);
            _weather_init(&t_wea, &t_result);

            _weather_set(&t_wea, "Shenyang", 3);
            priority_queue_push(pt_pq, &t_wea);
            _weather_set(&t_wea, "Beijing", 7);
            priority_queue_push(pt_pq, &t_wea);
            _weather_set(&t_wea, "Haerbin", -4);
            priority_queue_push(pt_pq, &t_wea);
            _weather_set(&t_wea, "Nanjing", 15);
            priority_queue_push(pt_pq, &t_wea);
            _weather_set(&t_wea, "Shanghai", 19);
            priority_queue_push(pt_pq, &t_wea);
            _print_pq_user(pt_pq);
            priority_queue_destroy(pt_pq);
        }
        /*priority_queue_init_ex           */
        {
            priority_queue_t* pt_pq = create_priority_queue(weather_t);
            weather_t t_wea;
            bool_t t_result;
            if(pt_pq == NULL)
            {
                return;
            }
            priority_queue_init_ex(pt_pq, _weather_greater);
            _weather_init(&t_wea, &t_result);

            _weather_set(&t_wea, "Shenyang", 3);
            priority_queue_push(pt_pq, &t_wea);
            _weather_set(&t_wea, "Beijing", 7);
            priority_queue_push(pt_pq, &t_wea);
            _weather_set(&t_wea, "Haerbin", -4);
            priority_queue_push(pt_pq, &t_wea);
            _weather_set(&t_wea, "Nanjing", 15);
            priority_queue_push(pt_pq, &t_wea);
            _weather_set(&t_wea, "Shanghai", 19);
            priority_queue_push(pt_pq, &t_wea);
            _print_pq_user(pt_pq);
            priority_queue_destroy(pt_pq);
        }
        /*priority_queue_init_copy         */
        {
            priority_queue_t* pt_pq = create_priority_queue(weather_t);
            priority_queue_t* pt_pqex = create_priority_queue(weather_t);
            weather_t t_wea;
            bool_t t_result;
            if(pt_pq == NULL || pt_pqex == NULL)
            {
                return;
            }
            priority_queue_init_ex(pt_pq, _weather_greater);
            _weather_init(&t_wea, &t_result);

            _weather_set(&t_wea, "Shenyang", 3);
            priority_queue_push(pt_pq, &t_wea);
            _weather_set(&t_wea, "Beijing", 7);
            priority_queue_push(pt_pq, &t_wea);
            _weather_set(&t_wea, "Haerbin", -4);
            priority_queue_push(pt_pq, &t_wea);
            _weather_set(&t_wea, "Nanjing", 15);
            priority_queue_push(pt_pq, &t_wea);
            _weather_set(&t_wea, "Shanghai", 19);
            priority_queue_push(pt_pq, &t_wea);
            _print_pq_user(pt_pq);

            priority_queue_init_copy(pt_pqex, pt_pq);
            _print_pq_user(pt_pqex);
            priority_queue_destroy(pt_pq);
            priority_queue_destroy(pt_pqex);
        }
        /*priority_queue_init_copy_range   */
        {
            priority_queue_t* pt_pq = create_priority_queue(weather_t);
            vector_t* pt_vec = create_vector(weather_t);
            weather_t t_wea;
            bool_t t_result;
            if(pt_pq == NULL || pt_vec == NULL)
            {
                return;
            }
            _weather_init(&t_wea, &t_result);

            _weather_set(&t_wea, "Shenyang", 3);
            vector_push_back(pt_vec, &t_wea);
            _weather_set(&t_wea, "Beijing", 7);
            vector_push_back(pt_vec, &t_wea);
            _weather_set(&t_wea, "Haerbin", -4);
            vector_push_back(pt_vec, &t_wea);
            _weather_set(&t_wea, "Nanjing", 15);
            vector_push_back(pt_vec, &t_wea);
            _weather_set(&t_wea, "Shanghai", 19);
            vector_push_back(pt_vec, &t_wea);

            priority_queue_init_copy_range(pt_pq, vector_begin(pt_vec), vector_end(pt_vec));
            _print_pq_user(pt_pq);
            priority_queue_destroy(pt_pq);
            vector_destroy(pt_vec);
        }
        /*priority_queue_init_copy_range_ex*/
        {
            priority_queue_t* pt_pq = create_priority_queue(weather_t);
            vector_t* pt_vec = create_vector(weather_t);
            weather_t t_wea;
            bool_t t_result;
            if(pt_pq == NULL || pt_vec == NULL)
            {
                return;
            }
            _weather_init(&t_wea, &t_result);

            _weather_set(&t_wea, "Shenyang", 3);
            vector_push_back(pt_vec, &t_wea);
            _weather_set(&t_wea, "Beijing", 7);
            vector_push_back(pt_vec, &t_wea);
            _weather_set(&t_wea, "Haerbin", -4);
            vector_push_back(pt_vec, &t_wea);
            _weather_set(&t_wea, "Nanjing", 15);
            vector_push_back(pt_vec, &t_wea);
            _weather_set(&t_wea, "Shanghai", 19);
            vector_push_back(pt_vec, &t_wea);

            priority_queue_init_copy_range_ex(pt_pq,
                vector_begin(pt_vec), vector_end(pt_vec), _weather_greater);
            _print_pq_user(pt_pq);
            priority_queue_destroy(pt_pq);
            vector_destroy(pt_vec);
        }
        /*priority_queue_destroy           */
        /*priority_queue_assign            */
        {
            priority_queue_t* pt_pq = create_priority_queue(weather_t);
            priority_queue_t* pt_pqex = create_priority_queue(weather_t);
            weather_t t_wea;
            bool_t t_result;
            if(pt_pq == NULL || pt_pqex == NULL)
            {
                return;
            }
            priority_queue_init_ex(pt_pq, _weather_greater);
            priority_queue_init(pt_pqex);
            _weather_init(&t_wea, &t_result);

            _weather_set(&t_wea, "Shenyang", 3);
            priority_queue_push(pt_pq, &t_wea);
            _weather_set(&t_wea, "Beijing", 7);
            priority_queue_push(pt_pq, &t_wea);
            _weather_set(&t_wea, "Haerbin", -4);
            priority_queue_push(pt_pq, &t_wea);
            _weather_set(&t_wea, "Nanjing", 15);
            priority_queue_push(pt_pq, &t_wea);
            _weather_set(&t_wea, "Shanghai", 19);
            priority_queue_push(pt_pq, &t_wea);
            _print_pq_user(pt_pq);

            priority_queue_assign(pt_pqex, pt_pq);
            _print_pq_user(pt_pqex);
            priority_queue_destroy(pt_pq);
            priority_queue_destroy(pt_pqex);
        }
        /*priority_queue_empty             */
        /*priority_queue_size              */
        /*priority_queue_top               */
        /*_priority_queue_push             */
        /*priority_queue_pop               */
        {
            priority_queue_t* pt_pq = create_priority_queue(weather_t);
            weather_t t_wea;
            bool_t t_result;
            if(pt_pq == NULL)
            {
                return;
            }
            priority_queue_init(pt_pq);
            _weather_init(&t_wea, &t_result);

            _weather_set(&t_wea, "Shenyang", 3);
            priority_queue_push(pt_pq, &t_wea);
            _weather_set(&t_wea, "Beijing", 7);
            priority_queue_push(pt_pq, &t_wea);
            _weather_set(&t_wea, "Haerbin", -4);
            priority_queue_push(pt_pq, &t_wea);
            _weather_set(&t_wea, "Nanjing", 15);
            priority_queue_push(pt_pq, &t_wea);
            _weather_set(&t_wea, "Shanghai", 19);
            priority_queue_push(pt_pq, &t_wea);
            _print_pq_user(pt_pq);
            priority_queue_pop(pt_pq);
            _print_pq_user(pt_pq);
            while(!priority_queue_empty(pt_pq))
            {
                priority_queue_pop(pt_pq);
            }
            _print_pq_user(pt_pq);
            priority_queue_destroy(pt_pq);
        }
    }
    /* cstl built-in type */
    {
        /*_create_priority_queue           */
        /*priority_queue_init              */
        {
            priority_queue_t* pt_pq = create_priority_queue(list_t<int>);
            list_t* pt_list = create_list(int);
            if(pt_pq == NULL || pt_list == NULL)
            {
                return;
            }
            list_init(pt_list);
            priority_queue_init(pt_pq);
            list_push_back(pt_list, 334);
            list_push_back(pt_list, 90);
            list_push_back(pt_list, 44);
            priority_queue_push(pt_pq, pt_list);
            list_clear(pt_list);
            list_push_back(pt_list, 11);
            list_push_back(pt_list, 400);
            list_push_back(pt_list, 455);
            list_push_back(pt_list, -5);
            list_push_back(pt_list, 3);
            priority_queue_push(pt_pq, pt_list);
            list_clear(pt_list);
            list_push_back(pt_list, 300);
            priority_queue_push(pt_pq, pt_list);
            list_clear(pt_list);
            list_push_back(pt_list, -400);
            list_push_back(pt_list, 12);
            priority_queue_push(pt_pq, pt_list);
            list_clear(pt_list);
            list_push_back(pt_list, 1);
            list_push_back(pt_list, 34);
            priority_queue_push(pt_pq, pt_list);
            list_clear(pt_list);
            list_push_back(pt_list, 300);
            list_push_back(pt_list, 300);
            list_push_back(pt_list, 300);
            priority_queue_push(pt_pq, pt_list);
            _print_pq_cstl(pt_pq);

            priority_queue_destroy(pt_pq);
            list_destroy(pt_list);
        }
        /*priority_queue_init_ex           */
        {
            priority_queue_t* pt_pq = create_priority_queue(list_t<int>);
            list_t* pt_list = create_list(int);
            if(pt_pq == NULL || pt_list == NULL)
            {
                return;
            }
            list_init(pt_list);
            priority_queue_init_ex(pt_pq, fun_greater_list);
            list_push_back(pt_list, 334);
            list_push_back(pt_list, 90);
            list_push_back(pt_list, 44);
            priority_queue_push(pt_pq, pt_list);
            list_clear(pt_list);
            list_push_back(pt_list, 11);
            list_push_back(pt_list, 400);
            list_push_back(pt_list, 455);
            list_push_back(pt_list, -5);
            list_push_back(pt_list, 3);
            priority_queue_push(pt_pq, pt_list);
            list_clear(pt_list);
            list_push_back(pt_list, 300);
            priority_queue_push(pt_pq, pt_list);
            list_clear(pt_list);
            list_push_back(pt_list, -400);
            list_push_back(pt_list, 12);
            priority_queue_push(pt_pq, pt_list);
            list_clear(pt_list);
            list_push_back(pt_list, 1);
            list_push_back(pt_list, 34);
            priority_queue_push(pt_pq, pt_list);
            list_clear(pt_list);
            list_push_back(pt_list, 300);
            list_push_back(pt_list, 300);
            list_push_back(pt_list, 300);
            priority_queue_push(pt_pq, pt_list);
            _print_pq_cstl(pt_pq);

            priority_queue_destroy(pt_pq);
            list_destroy(pt_list);
        }
        /*priority_queue_init_copy         */
        {
            priority_queue_t* pt_pq = create_priority_queue(list_t<int>);
            priority_queue_t* pt_pqex = create_priority_queue(list_t<int>);
            list_t* pt_list = create_list(int);
            if(pt_pq == NULL || pt_list == NULL || pt_pqex == NULL)
            {
                return;
            }
            list_init(pt_list);
            priority_queue_init_ex(pt_pq, fun_greater_list);
            list_push_back(pt_list, 334);
            list_push_back(pt_list, 90);
            list_push_back(pt_list, 44);
            priority_queue_push(pt_pq, pt_list);
            list_clear(pt_list);
            list_push_back(pt_list, 11);
            list_push_back(pt_list, 400);
            list_push_back(pt_list, 455);
            list_push_back(pt_list, -5);
            list_push_back(pt_list, 3);
            priority_queue_push(pt_pq, pt_list);
            list_clear(pt_list);
            list_push_back(pt_list, 300);
            priority_queue_push(pt_pq, pt_list);
            list_clear(pt_list);
            list_push_back(pt_list, -400);
            list_push_back(pt_list, 12);
            priority_queue_push(pt_pq, pt_list);
            list_clear(pt_list);
            list_push_back(pt_list, 1);
            list_push_back(pt_list, 34);
            priority_queue_push(pt_pq, pt_list);
            list_clear(pt_list);
            list_push_back(pt_list, 300);
            list_push_back(pt_list, 300);
            list_push_back(pt_list, 300);
            priority_queue_push(pt_pq, pt_list);
            _print_pq_cstl(pt_pq);

            priority_queue_init_copy(pt_pqex, pt_pq);
            _print_pq_cstl(pt_pqex);

            priority_queue_destroy(pt_pq);
            priority_queue_destroy(pt_pqex);
            list_destroy(pt_list);
        }
        /*priority_queue_init_copy_range   */
        {
            priority_queue_t* pt_pq = create_priority_queue(list_t<int>);
            vector_t* pt_vec = create_vector(list_t<int>);
            list_t* pt_list = create_list(int);
            if(pt_pq == NULL || pt_list == NULL || pt_vec == NULL)
            {
                return;
            }
            list_init(pt_list);
            vector_init(pt_vec);
            list_push_back(pt_list, 334);
            list_push_back(pt_list, 90);
            list_push_back(pt_list, 44);
            vector_push_back(pt_vec, pt_list);
            list_clear(pt_list);
            list_push_back(pt_list, 11);
            list_push_back(pt_list, 400);
            list_push_back(pt_list, 455);
            list_push_back(pt_list, -5);
            list_push_back(pt_list, 3);
            vector_push_back(pt_vec, pt_list);
            list_clear(pt_list);
            list_push_back(pt_list, 300);
            vector_push_back(pt_vec, pt_list);
            list_clear(pt_list);
            list_push_back(pt_list, -400);
            list_push_back(pt_list, 12);
            vector_push_back(pt_vec, pt_list);
            list_clear(pt_list);
            list_push_back(pt_list, 1);
            list_push_back(pt_list, 34);
            vector_push_back(pt_vec, pt_list);
            list_clear(pt_list);
            list_push_back(pt_list, 300);
            list_push_back(pt_list, 300);
            list_push_back(pt_list, 300);
            vector_push_back(pt_vec, pt_list);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_list);
            printf("\n");

            priority_queue_init_copy_range(pt_pq, vector_begin(pt_vec), vector_end(pt_vec));
            _print_pq_cstl(pt_pq);

            priority_queue_destroy(pt_pq);
            vector_destroy(pt_vec);
            list_destroy(pt_list);
        }
        /*priority_queue_init_copy_range_ex*/
        {
            priority_queue_t* pt_pq = create_priority_queue(list_t<int>);
            vector_t* pt_vec = create_vector(list_t<int>);
            list_t* pt_list = create_list(int);
            if(pt_pq == NULL || pt_list == NULL || pt_vec == NULL)
            {
                return;
            }
            list_init(pt_list);
            vector_init(pt_vec);
            list_push_back(pt_list, 334);
            list_push_back(pt_list, 90);
            list_push_back(pt_list, 44);
            vector_push_back(pt_vec, pt_list);
            list_clear(pt_list);
            list_push_back(pt_list, 11);
            list_push_back(pt_list, 400);
            list_push_back(pt_list, 455);
            list_push_back(pt_list, -5);
            list_push_back(pt_list, 3);
            vector_push_back(pt_vec, pt_list);
            list_clear(pt_list);
            list_push_back(pt_list, 300);
            vector_push_back(pt_vec, pt_list);
            list_clear(pt_list);
            list_push_back(pt_list, -400);
            list_push_back(pt_list, 12);
            vector_push_back(pt_vec, pt_list);
            list_clear(pt_list);
            list_push_back(pt_list, 1);
            list_push_back(pt_list, 34);
            vector_push_back(pt_vec, pt_list);
            list_clear(pt_list);
            list_push_back(pt_list, 300);
            list_push_back(pt_list, 300);
            list_push_back(pt_list, 300);
            vector_push_back(pt_vec, pt_list);
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_list);
            printf("\n");

            priority_queue_init_copy_range_ex(pt_pq,
                vector_begin(pt_vec), vector_end(pt_vec), fun_greater_list);
            _print_pq_cstl(pt_pq);

            priority_queue_destroy(pt_pq);
            vector_destroy(pt_vec);
            list_destroy(pt_list);
        }
        /*priority_queue_destroy           */
        /*priority_queue_assign            */
        {
            priority_queue_t* pt_pq = create_priority_queue(list_t<int>);
            priority_queue_t* pt_pqex = create_priority_queue(list_t<int>);
            list_t* pt_list = create_list(int);
            if(pt_pq == NULL || pt_list == NULL || pt_pqex == NULL)
            {
                return;
            }
            list_init(pt_list);
            priority_queue_init_ex(pt_pq, fun_greater_list);
            priority_queue_init(pt_pqex);
            list_push_back(pt_list, 334);
            list_push_back(pt_list, 90);
            list_push_back(pt_list, 44);
            priority_queue_push(pt_pq, pt_list);
            list_clear(pt_list);
            list_push_back(pt_list, 11);
            list_push_back(pt_list, 400);
            list_push_back(pt_list, 455);
            list_push_back(pt_list, -5);
            list_push_back(pt_list, 3);
            priority_queue_push(pt_pq, pt_list);
            list_clear(pt_list);
            list_push_back(pt_list, 300);
            priority_queue_push(pt_pq, pt_list);
            list_clear(pt_list);
            list_push_back(pt_list, -400);
            list_push_back(pt_list, 12);
            priority_queue_push(pt_pq, pt_list);
            list_clear(pt_list);
            list_push_back(pt_list, 1);
            list_push_back(pt_list, 34);
            priority_queue_push(pt_pq, pt_list);
            list_clear(pt_list);
            list_push_back(pt_list, 300);
            list_push_back(pt_list, 300);
            list_push_back(pt_list, 300);
            priority_queue_push(pt_pq, pt_list);
            _print_pq_cstl(pt_pq);

            priority_queue_assign(pt_pqex, pt_pq);
            _print_pq_cstl(pt_pqex);

            priority_queue_destroy(pt_pq);
            priority_queue_destroy(pt_pqex);
            list_destroy(pt_list);
        }
        /*priority_queue_empty             */
        /*priority_queue_size              */
        /*priority_queue_top               */
        /*_priority_queue_push             */
        /*priority_queue_pop               */
        {
            priority_queue_t* pt_pq = create_priority_queue(list_t<int>);
            list_t* pt_list = create_list(int);
            if(pt_pq == NULL || pt_list == NULL)
            {
                return;
            }
            list_init(pt_list);
            priority_queue_init_ex(pt_pq, fun_greater_list);
            list_push_back(pt_list, 334);
            list_push_back(pt_list, 90);
            list_push_back(pt_list, 44);
            priority_queue_push(pt_pq, pt_list);
            list_clear(pt_list);
            list_push_back(pt_list, 11);
            list_push_back(pt_list, 400);
            list_push_back(pt_list, 455);
            list_push_back(pt_list, -5);
            list_push_back(pt_list, 3);
            priority_queue_push(pt_pq, pt_list);
            list_clear(pt_list);
            list_push_back(pt_list, 300);
            priority_queue_push(pt_pq, pt_list);
            list_clear(pt_list);
            list_push_back(pt_list, -400);
            list_push_back(pt_list, 12);
            priority_queue_push(pt_pq, pt_list);
            list_clear(pt_list);
            list_push_back(pt_list, 1);
            list_push_back(pt_list, 34);
            priority_queue_push(pt_pq, pt_list);
            list_clear(pt_list);
            list_push_back(pt_list, 300);
            list_push_back(pt_list, 300);
            list_push_back(pt_list, 300);
            priority_queue_push(pt_pq, pt_list);
            _print_pq_cstl(pt_pq);
            priority_queue_pop(pt_pq);
            _print_pq_cstl(pt_pq);
            while(!priority_queue_empty(pt_pq))
            {
                priority_queue_pop(pt_pq);
            }
            _print_pq_cstl(pt_pq);

            priority_queue_destroy(pt_pq);
            list_destroy(pt_list);
        }
    }
    /* c string type */
    {
        /*_create_priority_queue           */
        /*priority_queue_init              */
        {
            priority_queue_t* pt_pq = create_priority_queue(char*);
            if(pt_pq == NULL)
            {
                return;
            }
            priority_queue_init(pt_pq);
            priority_queue_push(pt_pq, "lllllsjsf");
            priority_queue_push(pt_pq, "00000000000");
            priority_queue_push(pt_pq, "ooooooooooooo");
            priority_queue_push(pt_pq, "$$$$$");
            priority_queue_push(pt_pq, "SSSSSSSSSSSSSSS");
            priority_queue_push(pt_pq, "jjjjjjjj");
            priority_queue_push(pt_pq, "VVVVVVVVVVVVVVV");
            _print_pq_cstr(pt_pq);

            priority_queue_destroy(pt_pq);
        }
        /*priority_queue_init_ex           */
        {
            priority_queue_t* pt_pq = create_priority_queue(char*);
            if(pt_pq == NULL)
            {
                return;
            }
            priority_queue_init_ex(pt_pq, fun_greater_cstr);
            priority_queue_push(pt_pq, "lllllsjsf");
            priority_queue_push(pt_pq, "00000000000");
            priority_queue_push(pt_pq, "ooooooooooooo");
            priority_queue_push(pt_pq, "$$$$$");
            priority_queue_push(pt_pq, "SSSSSSSSSSSSSSS");
            priority_queue_push(pt_pq, "jjjjjjjj");
            priority_queue_push(pt_pq, "VVVVVVVVVVVVVVV");
            _print_pq_cstr(pt_pq);

            priority_queue_destroy(pt_pq);
        }
        /*priority_queue_init_copy         */
        {
            priority_queue_t* pt_pq = create_priority_queue(char*);
            priority_queue_t* pt_pqex = create_priority_queue(char*);
            if(pt_pq == NULL || pt_pqex == NULL)
            {
                return;
            }
            priority_queue_init_ex(pt_pq, fun_greater_cstr);
            priority_queue_push(pt_pq, "lllllsjsf");
            priority_queue_push(pt_pq, "00000000000");
            priority_queue_push(pt_pq, "ooooooooooooo");
            priority_queue_push(pt_pq, "$$$$$");
            priority_queue_push(pt_pq, "SSSSSSSSSSSSSSS");
            priority_queue_push(pt_pq, "jjjjjjjj");
            priority_queue_push(pt_pq, "VVVVVVVVVVVVVVV");
            _print_pq_cstr(pt_pq);
            priority_queue_init_copy(pt_pqex, pt_pq);
            _print_pq_cstr(pt_pqex);

            priority_queue_destroy(pt_pq);
            priority_queue_destroy(pt_pqex);
        }
        /*priority_queue_init_copy_range   */
        {
            priority_queue_t* pt_pq = create_priority_queue(char*);
            vector_t* pt_vec = create_vector(char*);
            if(pt_pq == NULL || pt_vec == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            vector_push_back(pt_vec, "lllllsjsf");
            vector_push_back(pt_vec, "00000000000");
            vector_push_back(pt_vec, "ooooooooooooo");
            vector_push_back(pt_vec, "$$$$$");
            vector_push_back(pt_vec, "SSSSSSSSSSSSSSS");
            vector_push_back(pt_vec, "jjjjjjjj");
            vector_push_back(pt_vec, "VVVVVVVVVVVVVVV");
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_cstr);
            printf("\n");
            priority_queue_init_copy_range(pt_pq, vector_begin(pt_vec), vector_end(pt_vec));
            _print_pq_cstr(pt_pq);

            priority_queue_destroy(pt_pq);
            vector_destroy(pt_vec);
        }
        /*priority_queue_init_copy_range_ex*/
        {
            priority_queue_t* pt_pq = create_priority_queue(char*);
            vector_t* pt_vec = create_vector(char*);
            if(pt_pq == NULL || pt_vec == NULL)
            {
                return;
            }
            vector_init(pt_vec);
            vector_push_back(pt_vec, "lllllsjsf");
            vector_push_back(pt_vec, "00000000000");
            vector_push_back(pt_vec, "ooooooooooooo");
            vector_push_back(pt_vec, "$$$$$");
            vector_push_back(pt_vec, "SSSSSSSSSSSSSSS");
            vector_push_back(pt_vec, "jjjjjjjj");
            vector_push_back(pt_vec, "VVVVVVVVVVVVVVV");
            algo_for_each(vector_begin(pt_vec), vector_end(pt_vec), _print_cstr);
            printf("\n");
            priority_queue_init_copy_range_ex(pt_pq,
                vector_begin(pt_vec), vector_end(pt_vec), fun_greater_cstr);
            _print_pq_cstr(pt_pq);

            priority_queue_destroy(pt_pq);
            vector_destroy(pt_vec);
        }
        /*priority_queue_destroy           */
        /*priority_queue_assign            */
        {
            priority_queue_t* pt_pq = create_priority_queue(char*);
            priority_queue_t* pt_pqex = create_priority_queue(char*);
            if(pt_pq == NULL || pt_pqex == NULL)
            {
                return;
            }
            priority_queue_init_ex(pt_pq, fun_greater_cstr);
            priority_queue_init(pt_pqex);
            priority_queue_push(pt_pq, "lllllsjsf");
            priority_queue_push(pt_pq, "00000000000");
            priority_queue_push(pt_pq, "ooooooooooooo");
            priority_queue_push(pt_pq, "$$$$$");
            priority_queue_push(pt_pq, "SSSSSSSSSSSSSSS");
            priority_queue_push(pt_pq, "jjjjjjjj");
            priority_queue_push(pt_pq, "VVVVVVVVVVVVVVV");
            _print_pq_cstr(pt_pq);
            priority_queue_assign(pt_pqex, pt_pq);
            _print_pq_cstr(pt_pqex);

            priority_queue_destroy(pt_pq);
            priority_queue_destroy(pt_pqex);
        }
        /*priority_queue_empty             */
        /*priority_queue_size              */
        /*priority_queue_top               */
        /*_priority_queue_push             */
        /*priority_queue_pop               */
        {
            priority_queue_t* pt_pq = create_priority_queue(char*);
            if(pt_pq == NULL)
            {
                return;
            }
            priority_queue_init_ex(pt_pq, fun_greater_cstr);
            priority_queue_push(pt_pq, "lllllsjsf");
            priority_queue_push(pt_pq, "00000000000");
            priority_queue_push(pt_pq, "ooooooooooooo");
            priority_queue_push(pt_pq, "$$$$$");
            priority_queue_push(pt_pq, "SSSSSSSSSSSSSSS");
            priority_queue_push(pt_pq, "jjjjjjjj");
            priority_queue_push(pt_pq, "VVVVVVVVVVVVVVV");
            _print_pq_cstr(pt_pq);
            priority_queue_pop(pt_pq);
            _print_pq_cstr(pt_pq);
            while(!priority_queue_empty(pt_pq))
            {
                priority_queue_pop(pt_pq);
            }
            _print_pq_cstr(pt_pq);

            priority_queue_destroy(pt_pq);
        }
    }
}

/** local function implementation section **/
static void _print_pq_cstr(const priority_queue_t* cpt_pq)
{
    assert(cpt_pq != NULL);
    printf("empty : %d, size : %d",
        priority_queue_empty(cpt_pq), priority_queue_size(cpt_pq));
    if(!priority_queue_empty(cpt_pq))
    {
        printf(", top : %s\n", (char*)priority_queue_top(cpt_pq));
        algo_for_each(vector_begin(&cpt_pq->_t_vector), vector_end(&cpt_pq->_t_vector),
            _print_cstr);
    }
    printf("\n");
}
static void _print_cstr(const void* cpv_input, void* pv_output)
{
    pv_output = NULL;
    printf("%s\n", (char*)cpv_input);
}
static void _print_pq_cstl(const priority_queue_t* cpt_pq)
{
    assert(cpt_pq != NULL);
    printf("empty : %d, size : %d",
        priority_queue_empty(cpt_pq), priority_queue_size(cpt_pq));
    if(!priority_queue_empty(cpt_pq))
    {
        printf(", top : ");
        _print_list((list_t*)priority_queue_top(cpt_pq), NULL);
        algo_for_each(vector_begin(&cpt_pq->_t_vector), vector_end(&cpt_pq->_t_vector),
            _print_list);
    }
    printf("\n");
}
static void _print_list(const void* cpv_input, void* pv_output)
{
    pv_output = NULL;
    printf("[");
    algo_for_each(list_begin((list_t*)cpv_input), list_end((list_t*)cpv_input), _print_int);
    printf("]\n");
}

static void _print_pq_user(const priority_queue_t* cpt_pq)
{
    assert(cpt_pq != NULL);
    printf("empty : %d, size : %d",
        priority_queue_empty(cpt_pq), priority_queue_size(cpt_pq));
    if(!priority_queue_empty(cpt_pq))
    {
        printf(", top : (city:%s, %dC)\n",
            ((weather_t*)priority_queue_top(cpt_pq))->_s_city,
            ((weather_t*)priority_queue_top(cpt_pq))->_n_temperature);
        algo_for_each(vector_begin(&cpt_pq->_t_vector), vector_end(&cpt_pq->_t_vector),
            _print_user);
    }
    printf("\n");
}
static void _print_user(const void* cpv_input, void* pv_output)
{
    pv_output = NULL;
    printf("(city:%s, %dC), ", ((weather_t*)cpv_input)->_s_city,
        ((weather_t*)cpv_input)->_n_temperature);
}
static void _print_pq_int(const priority_queue_t* cpt_pq)
{
    assert(cpt_pq != NULL);
    printf("empty : %d, size : %d",
        priority_queue_empty(cpt_pq), priority_queue_size(cpt_pq));
    if(!priority_queue_empty(cpt_pq))
    {
        printf(", top : %d\n", *(int*)priority_queue_top(cpt_pq));
        algo_for_each(vector_begin(&cpt_pq->_t_vector), vector_end(&cpt_pq->_t_vector),
            _print_int);
    }
    printf("\n");
}
static void _print_int(const void* cpv_input, void* pv_output)
{
    pv_output = NULL;
    printf("%d, ", *(int*)cpv_input);
}

static void _print_queue_str(const queue_t* cpt_queue)
{
    iterator_t t_pos;
    assert(cpt_queue != NULL);

    printf("+++++++++++++++++++++++++++++++++++++\n");
    printf("empty: %d, size: %d\n", queue_empty(cpt_queue), queue_size(cpt_queue));
#ifdef CSTL_QUEUE_LIST_SEQUENCE
    for(t_pos = list_begin(&(cpt_queue)->_t_sequence);
        !iterator_equal(t_pos, list_end(&(cpt_queue)->_t_sequence));
        t_pos = iterator_next(t_pos))
#else
    for(t_pos = deque_begin(&(cpt_queue)->_t_sequence);
        !iterator_equal(t_pos, deque_end(&(cpt_queue)->_t_sequence));
        t_pos = iterator_next(t_pos))
#endif
    {
        puts(iterator_get_pointer(t_pos));
    }
}

static void _printqueue(const queue_t* cpt_queue)
{
    iterator_t t_pos;
    assert(cpt_queue != NULL);

    printf("+++++++++++++++++++++++++++++++++++++\n");
#ifdef CSTL_QUEUE_LIST_SEQUENCE
    for(t_pos = list_begin(&(cpt_queue)->_t_sequence);
        !iterator_equal(t_pos, list_end(&(cpt_queue)->_t_sequence));
        t_pos = iterator_next(t_pos))
#else
    for(t_pos = deque_begin(&(cpt_queue)->_t_sequence);
        !iterator_equal(t_pos, deque_end(&(cpt_queue)->_t_sequence));
        t_pos = iterator_next(t_pos))
#endif
    {
        _printqueue_c((queue_t*)iterator_get_pointer(t_pos), "%d, ", int);
    }
}

static void _weather_set(weather_t* pt_weather, const char* s_city, int n_temperature)
{
    assert(pt_weather != NULL && s_city != NULL);
    memset(pt_weather->_s_city, '\0', 31);
    strncpy(pt_weather->_s_city, s_city, 30);
    pt_weather->_n_temperature = n_temperature;
}

static void _printweather(const queue_t* cpt_queue)
{
    iterator_t t_iter;
    assert(cpt_queue != NULL);

    printf("============================\n");
#ifdef CSTL_QUEUE_LIST_SEQUENCE
    for(t_iter = list_begin(&(cpt_queue)->_t_sequence);
        !iterator_equal(t_iter, list_end(&(cpt_queue)->_t_sequence));
        t_iter = iterator_next(t_iter))
#else
    for(t_iter = deque_begin(&(cpt_queue)->_t_sequence);
        !iterator_equal(t_iter, deque_end(&(cpt_queue)->_t_sequence));
        t_iter = iterator_next(t_iter))
#endif
    {
        printf("(city:%s, %dC), ",
            ((weather_t*)iterator_get_pointer(t_iter))->_s_city,
            ((weather_t*)iterator_get_pointer(t_iter))->_n_temperature);
    }
    printf("\n");
}

static void _weather_init(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    memset(((weather_t*)cpv_input)->_s_city, '\0', 31);
    ((weather_t*)cpv_input)->_n_temperature = 0;
    *(bool_t*)pv_output = true;
}

static void _weather_copy(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    strncpy(((weather_t*)cpv_first)->_s_city, ((weather_t*)cpv_second)->_s_city, 30);
    ((weather_t*)cpv_first)->_n_temperature = ((weather_t*)cpv_second)->_n_temperature;
    *(bool_t*)pv_output = true;
}

static void _weather_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    if(strncmp(((weather_t*)cpv_first)->_s_city, ((weather_t*)cpv_second)->_s_city, 30) < 0)
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}

static void _weather_greater(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    if(strncmp(((weather_t*)cpv_first)->_s_city, ((weather_t*)cpv_second)->_s_city, 30) > 0)
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}

static void _weather_destroy(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    memset(((weather_t*)cpv_input)->_s_city, '\0', 31);
    ((weather_t*)cpv_input)->_n_temperature = 0;
    *(bool_t*)pv_output = true;
}

/** eof **/

