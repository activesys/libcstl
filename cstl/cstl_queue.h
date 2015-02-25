/*
 *  The interface of queue.
 *  Copyright (C)  2008 - 2012  Wangbo
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

#ifndef _CSTL_QUEUE_H_
#define _CSTL_QUEUE_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/**
 * Create queue adaptor.
 * @param ...    type name.
 * @return queue adaptor pointer, if create queue successfully, else return NULL.
 * @remarks type name must be c builtin type, libcstl builtin type or user defined type, otherwise creation will be failure.
 */
#define create_queue(...) _create_queue(#__VA_ARGS__) 

/**
 * Add specificed element at the back of queue. 
 * @param pque_queue      queue adaptor.
 * @param elem            specificed element.
 * @return void.
 * @remarks if pque_queue == NULL or queue is uninitialized, then the behavior is undefined. the type of specificed
 *          element and queue element type must be same, otherwise the behavior is undefined
 */
#define queue_push(pque_deque, elem) _queue_push((pque_deque), (elem))

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Initialize an empty queue adaptor
 * @param pque_queue   queue adaptor.
 * @return void.
 * @remarks if pque_queue == NULL, then the behavior is undefined. pque_queue must be created by create_queue(), otherwise
 *          the behavior is undefine.
 */
extern void queue_init(queue_t* pque_queue);

/**
 * Initialize queue adaptor with exist queue adaptor.
 * @param pque_dest   destination queue adaptor.
 * @param pque_src    source queue adaptor.
 * @return void.
 * @remarks if pque_dest == NULL or pque_src == NULL, then the behavior is undefined. pque_dest must be created by
 *          create_queue(), and pque_src must be initialized, otherwise the behavior is undefined. the element type of
 *          pque_dest and pque_src must be the same, otherwise the behavior is undefined.
 */
extern void queue_init_copy(queue_t* pque_dest, const queue_t* cpque_src);

/**
 * Destroy queue adaptor.
 * @param pque_queue   queue adaptor.
 * @return void.
 * @remraks if pque_queue == NULLL, then the behavior is undefined. pque_queue must be initialized or created by
 *          create_queue(), otherwise the behavior is undefined.
 */
extern void queue_destroy(queue_t* pque_queue);

/**
 * Assign queue element with an exist queue adaptor.
 * @param pque_dest     destination queue adaptor.
 * @param cpque_src     source queue adaptor.
 * @return void.
 * @remarks if pque_dest == NULL or cpque_src == NULL, then the behavior is undefined. pque_dest and cpque_src must be
 *          initialized, otherwise the behavior is undefined. the element type of two queue must be same, otherwise
 *          the behavior is undefined. if the destination queue equal to source queue, then this function does nothing.
 */
extern void queue_assign(queue_t* pque_dest, const queue_t* cpque_src);

/**
 * Tests if a queue is empty.
 * @param cpque_queue  queue adaptor.
 * @return true if the queue is empty, else returns false.
 * @remarks if cpque_queue == NULL, then the behavior is undefined. the cpque_queue must be initialized, otherwise the
 *          behavior is undefine.
 */
extern bool_t queue_empty(const queue_t* cpque_queue);

/**
 * Return the number of elements in a queue.
 * @param cpque_queue  queue adaptor.
 * @return the number of elements in the queue.
 * @remarks if cpque_queue == NULL, then the behavior is undefined. the cpque_queue must be initialized, otherwise the
 *          behavior is undefine.
 */
extern size_t queue_size(const queue_t* cpque_queue);

/**
 * Access queue front data.
 * @param cpque_queue  queue adaptor.
 * @return pointer to the data.
 * @remarks if cpque_queue == NULL, then the behavior is undefined. the queue must be initialized, otherwise the behavior
 *          is undefined. if queue is empty, the behavior is undefine.
 */
extern void* queue_front(const queue_t* cpque_queue);

/**
 * Access queue last data.
 * @param cpque_queue  queue adaptor.
 * @return pointer to the data.
 * @remarks if cpque_queue == NULL, then the behavior is undefined. the queue must be initialized, otherwise the behavior
 *          is undefined. if queue is empty, the behavior is undefine.
 */
extern void* queue_back(const queue_t* cpque_queue);

/**
 * Delete the element at the begin of queue.
 * @param pque_queue    queue adaptor.
 * @return void.
 * @remarks if pque_queue == NULL, then the behavior is undefined. the queue must be initialized, otherwise the behavior
 *          is undefined. if queue is empty, then the behavior is undefined.
 */
extern void queue_pop(queue_t* pque_queue);

/**
 * Tests if the two queues are equal.
 * @param cpque_first   first queue adaptor.
 * @param cpque_second  second queue adaptor.
 * @return if first queue equal to second queue, then return true, else return false.
 * @remarks if cpque_first == NULL or cpque_second == NULL, then the behavior is undefined. the two queues must be
 *          initialized, otherwise the behavior is undefined. if the two queues are not same type, the behavior is undefined.
 *          if cpque_first == cpque_second, then return true.
 */
extern bool_t queue_equal(const queue_t* cpque_first, const queue_t* cpque_second);

/**
 * Test the two queues are unequal.
 * @param cpque_first   first queue adaptor.
 * @param cpque_second  second queue adaptor.
 * @return if first queue unequal to second queue, then return true, else return false.
 * @remarks if cpque_first == NULL or cpque_second == NULL, then the behavior is undefined. the two queues must be
 *          initialized, otherwise the behavior is undefined. if the two queues are not same type, the behavior is undefined.
 *          if cpque_first == cpque_second, then return false.
 */
extern bool_t queue_not_equal(const queue_t* cpque_first, const queue_t* cpque_second);

/**
 * Test the first queue is less than the second queue.
 * @param cpque_first   first queue adaptor.
 * @param cpque_second  second queue adaptor.
 * @return if the first queue is less than the second queue, then return true, else return false.
 * @remarks if cpque_first == NULL or cpque_second == NULL, then the behavior is undefined. the two queues must be
 *          initialized, otherwise the behavior is undefined. if the two queues are not same type, the behavior is
 *          undefined. if cpque_first == cpque_second, then return false.
 */
extern bool_t queue_less(const queue_t* cpque_first, const queue_t* cpque_second);

/**
 * Test the first queue is less than or equal to the second queue.
 * @param cpque_first   first queue adaptor.
 * @param cpque_second  second queue adaptor.
 * @return if the first queue is less than or equal to the second queue, then return true, else return false.
 * @remarks if cpque_first == NULL or cpque_second == NULL, then the behavior is undefined. the two queues must be
 *          initialized, otherwise the behavior is undefined. if the two queues are not same type, the behavior is
 *          undefined. if cpque_first == cpque_second, then return true.
 */
extern bool_t queue_less_equal(const queue_t* cpque_first, const queue_t* cpque_second);

/**
 * Test the first queue is greater than the second queue.
 * @param cpque_first   first queue adaptor.
 * @param cpque_second  second queue adaptor.
 * @return if the first queue is greater than the second queue, then return true, else return false.
 * @remarks if cpque_first == NULL or cpque_second == NULL, then the behavior is undefined. the two queues must be
 *          initialized, otherwise the behavior is undefined. if the two queues are not same type, the behavior is
 *          undefined. if cpque_first == cpque_second, then return false.
 */
extern bool_t queue_greater(const queue_t* cpque_first, const queue_t* cpque_second);

/**
 * Test the first queue is greater than or equal to the second queue.
 * @param cpque_first   first queue adaptor.
 * @param cpque_second  second queue adaptor.
 * @return if the first queue is greater than or equal to the second queue, then return true, else return false.
 * @remarks if cpque_first == NULL or cpque_second == NULL, then the behavior is undefined. the two queues must be
 *          initialized, otherwise the behavior is undefined. if the two queues are not same type, the behavior is
 *          undefined. if cpque_first == cpque_second, then return true.
 */
extern bool_t queue_greater_equal(const queue_t* cpque_first, const queue_t* cpque_second);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_QUEUE_H_ */
/** eof **/

