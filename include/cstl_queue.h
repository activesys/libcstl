/*
 *  The interface of queue.
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

#ifndef _CSTL_QUEUE_H
#define _CSTL_QUEUE_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/* create new queue with specific type */
#define create_queue(...) _create_queue(#__VA_ARGS__) 
/* push */
#define queue_push(pt_queue, elem)\
    _queue_push((pt_queue), (elem))

/* create new priority queue */
#define create_priority_queue(...) _create_priority_queue(#__VA_ARGS__)
/* push */
#define priority_queue_push(pt_pqueue, elem)\
    _priority_queue_push((pt_pqueue), (elem))

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * Initialization and destroy operation functions.
 */
extern void queue_init(queue_t* pt_queue);
extern void queue_destroy(queue_t* pt_queue);
extern void queue_init_copy(queue_t* pt_queuedest, const queue_t* cpt_queuesrc);

/*
 * Assign operator functions.
 */
extern void queue_assign(queue_t* pt_queuedest, const queue_t* cpt_queuesrc);

/*
 * queue_t size operation functions.
 */
extern bool_t queue_empty(const queue_t* cpt_queue);
extern size_t queue_size(const queue_t* cpt_queue);

/*
 * Element access operation functions.
 */
extern void* queue_front(const queue_t* cpt_queue);
extern void* queue_back(const queue_t* cpt_queue);
extern void queue_pop(queue_t* pt_queue);

/*
 * Relationship operator functions.
 */
extern bool_t queue_equal(const queue_t* cpt_queuefirst, const queue_t* cpt_queuesecond);
extern bool_t queue_not_equal(
    const queue_t* cpt_queuefirst, const queue_t* cpt_queuesecond);
extern bool_t queue_less(const queue_t* cpt_queuefirst, const queue_t* cpt_queuesecond);
extern bool_t queue_great(const queue_t* cpt_queuefirst, const queue_t* cpt_queuesecond);
extern bool_t queue_less_equal(
    const queue_t* cpt_queuefirst, const queue_t* cpt_queuesecond);
extern bool_t queue_great_equal(
    const queue_t* cpt_queuefirst, const queue_t* cpt_queuesecond);

/* priority queue */
/*
 * Initialization and destroy operation functions.
 */
extern void priority_queue_init(priority_queue_t* pt_pqueue);
extern void priority_queue_init_ex(
    priority_queue_t* pt_pqueue, binary_function_t t_binary_op);
extern void priority_queue_destroy(priority_queue_t* pt_pqueue);
extern void priority_queue_init_copy(
    priority_queue_t* pt_pqueuedest, const priority_queue_t* cpt_pqueuesrc);
extern void priority_queue_init_copy_range(
    priority_queue_t* pt_pqueuedest,
    random_access_iterator_t t_first, random_access_iterator_t t_last);
extern void priority_queue_init_copy_range_ex(
    priority_queue_t* pt_pqueuedest, random_access_iterator_t t_first,
    random_access_iterator_t t_last, binary_function_t t_binary_op);

/*
 * Assign operator functions.
 */
extern void priority_queue_assign(
    priority_queue_t* pt_pqueuedest, const priority_queue_t* cpt_pqueuesrc);

/*
 * priority_queue_t size operation functions.
 */
extern bool_t priority_queue_empty(const priority_queue_t* cpt_pqueue);
extern size_t priority_queue_size(const priority_queue_t* cpt_pqueue);
extern void* priority_queue_top(const priority_queue_t* cpt_pqueue);

/*
 * Element access functions.
 */
extern void priority_queue_pop(priority_queue_t* pt_pqueue);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_QUEUE_H */
/** eof **/

