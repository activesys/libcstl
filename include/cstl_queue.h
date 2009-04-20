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
 *  Author Email: activesys.wb@gmail.com
 *                activesys@sina.com.cn
 */

#ifndef _CSTL_QUEUE_H
#define _CSTL_QUEUE_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/* create new queue with specific type */
#define create_queue(type)\
    _create_queue(sizeof(type), #type) 
/* push */
#define queue_push(pt_queue, elem)\
    _queue_push((pt_queue), (elem))

/* create new priority queue */
#define create_priority_queue(type)\
    _create_priority_queue(sizeof(type), #type)
/* push */
#define priority_queue_push(pt_pqueue, elem)\
    _priority_queue_push((pt_pqueue), (elem))

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: queue_init
 *        Parameters: in) pt_queue: queue_t*
 *           Returns: void
 *       Description: initialize the queue.
 *
 * ----------------------------------------------------------------------------
 */
extern void queue_init(queue_t* pt_queue);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: queue_destroy
 *        Parameters: in) pt_queue: queue_t*
 *           Returns: void
 *       Description: destroy the queue.
 *
 * ----------------------------------------------------------------------------
 */
extern void queue_destroy(queue_t* pt_queue);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: queue_init_copy
 *        Parameters: in) pt_queuedest: queue_t*
 *                          the dest queue.
 *                    in) cpt_queuesrc: const queue_t*
 *                          the source queue.
 *           Returns: void
 *       Description: the copy constructor.
 *
 * ----------------------------------------------------------------------------
 */
extern void queue_init_copy(queue_t* pt_queuedest, const queue_t* cpt_queuesrc);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: queue_assign
 *        Parameters: in) pt_queuedest: queue_t*
 *                          the dest queue.
 *                    in) cpt_queuesrc: const queue_t*
 *                          the source queue.
 *           Returns: void
 *       Description: copy the queue.
 *
 * ----------------------------------------------------------------------------
 */
extern void queue_assign(queue_t* pt_queuedest, const queue_t* cpt_queuesrc);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: queue_empty
 *        Parameters: in) cpt_queue: const queue_t*
 *                          the dest queue.
 *           Returns: bool_t
 *       Description: if the queue is empty.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t queue_empty(const queue_t* cpt_queue);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: queue_size
 *        Parameters: in) cpt_queue: const queue_t*
 *                          the dest queue.
 *           Returns: size_t
 *       Description: get the queue size.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t queue_size(const queue_t* cpt_queue);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: queue_front
 *        Parameters: in) cpt_queue: const queue_t*
 *                          the queue.
 *           Returns: void*
 *       Description: return the first element.
 *
 * ----------------------------------------------------------------------------
 */
extern void* queue_front(const queue_t* cpt_queue);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: queue_back
 *        Parameters: in) cpt_queue: const queue_t*
 *                          the queue.
 *           Returns: void*
 *       Description: return the last element.
 *
 * ----------------------------------------------------------------------------
 */
extern void* queue_back(const queue_t* cpt_queue);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: queue_pop
 *        Parameters: in) pt_queue: queue_t*
 *                          the queue.
 *           Returns: void
 *       Description: remove the top element and does not return it.
 *
 * ----------------------------------------------------------------------------
 */
extern void queue_pop(queue_t* pt_queue);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: queue_equal
 *        Parameters: in) cpt_queuefirst: const queue_t*
 *                          the first queue.
 *                    in) cpt_queuesecond: const queue_t*
 *                          the second queue.
 *           Returns: bool_t
 *       Description: return whether first queue equal to second queue.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t queue_equal(
    const queue_t* cpt_queuefirst, const queue_t* cpt_queuesecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: queue_not_equal
 *        Parameters: in) cpt_queuefirst: const queue_t*
 *                          the first queue.
 *                    in) cpt_queuesecond: const queue_t*
 *                          the second queue.
 *           Returns: bool_t
 *       Description: return whether first queue not equal to second queue.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t queue_not_equal(
    const queue_t* cpt_queuefirst, const queue_t* cpt_queuesecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: queue_less
 *        Parameters: in) cpt_queuefirst: const queue_t*
 *                          the first queue.
 *                    in) cpt_queuesecond: const queue_t*
 *                          the second queue.
 *           Returns: bool_t
 *       Description: return whether first queue less then second queue.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t queue_less(
    const queue_t* cpt_queuefirst, const queue_t* cpt_queuesecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: queue_great
 *        Parameters: in) cpt_queuefirst: const queue_t*
 *                          the first queue.
 *                    in) cpt_queuesecond: const queue_t*
 *                          the second queue.
 *           Returns: bool_t
 *       Description: return whether first queue greater then second queue.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t queue_great(
    const queue_t* cpt_queuefirst, const queue_t* cpt_queuesecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: queue_less_equal
 *        Parameters: in) cpt_queuefirst: const queue_t*
 *                          the first queue.
 *                    in) cpt_queuesecond: const queue_t*
 *                          the second queue.
 *           Returns: bool_t
 *       Description: return whether first queue less then or equal to the 
 *                    second queue.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t queue_less_equal(
    const queue_t* cpt_queuefirst, const queue_t* cpt_queuesecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: queue_great_equal
 *        Parameters: in) cpt_queuefirst: const queue_t*
 *                          the first queue.
 *                    in) cpt_queuesecond: const queue_t*
 *                          the second queue.
 *           Returns: bool_t
 *       Description: return whether first queue greater then or equal to the
 *                    second queue.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t queue_great_equal(
    const queue_t* cpt_queuefirst, const queue_t* cpt_queuesecond);

/* priority queue */
/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: priority_queue_init
 *        Parameters: in) pt_pqueue: priority_queue_t*
 *           Returns: void
 *       Description: initialize the priority queue.
 *
 * ----------------------------------------------------------------------------
 */
extern void priority_queue_init(priority_queue_t* pt_pqueue);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: priority_queue_init_op
 *        Parameters: in) pt_pqueue: priority_queue_t*
 *                    in) t_binary_op: binary_function_t
 *           Returns: void
 *       Description: initialize the priority queue.
 *
 * ----------------------------------------------------------------------------
 */
extern void priority_queue_init_op(
    priority_queue_t* pt_pqueue, binary_function_t t_binary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: priority_queue_destroy
 *        Parameters: in) pt_pqueue: priority_queue_t*
 *           Returns: void
 *       Description: destroy the priority queue.
 *
 * ----------------------------------------------------------------------------
 */
extern void priority_queue_destroy(priority_queue_t* pt_pqueue);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: priority_queue_init_copy
 *        Parameters: in) pt_pqueuedest: priority_queue_t*
 *                          the dest priority queue.
 *                    in) cpt_pqueuesrc: const priority_queue_t*
 *                          the source priority queue.
 *           Returns: void
 *       Description: the copy constructor.
 *
 * ----------------------------------------------------------------------------
 */
extern void priority_queue_init_copy(
    priority_queue_t* pt_pqueuedest, const priority_queue_t* cpt_pqueuesrc);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: priority_queue_init_copy_range
 *        Parameters: in) pt_pqueuedest: priority_queue_t*
 *                          the dest priority queue.
 *                    in) t_first: random_access_iterator_t
 *                          the first iterator.
 *                    in) t_last: random_access_iterator_t
 *                          the first iterator.
 *           Returns: void
 *       Description: the copy constructor.
 *
 * ----------------------------------------------------------------------------
 */
extern void priority_queue_init_copy_range(
    priority_queue_t* pt_pqueuedest,
    random_access_iterator_t t_first,
    random_access_iterator_t t_last);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: priority_queue_init_copy_range_op
 *        Parameters: in) pt_pqueuedest: priority_queue_t*
 *                          the dest priority queue.
 *                    in) t_first: random_access_iterator_t
 *                          the first iterator.
 *                    in) t_last: random_access_iterator_t
 *                          the first iterator.
 *                    in) t_binary_op: binary_function_t
 *           Returns: void
 *       Description: the copy constructor.
 *
 * ----------------------------------------------------------------------------
 */
extern void priority_queue_init_copy_range_op(
    priority_queue_t* pt_pqueuedest,
    random_access_iterator_t t_first,
    random_access_iterator_t t_last,
    binary_function_t t_binary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: priority_queue_assign
 *        Parameters: in) pt_pqueuedest: priority_queue_t*
 *                          the dest priority queue.
 *                    in) cpt_pqueuesrc: const priority queue_t*
 *                          the source priority queue.
 *           Returns: void
 *       Description: copy the priority queue.
 *
 * ----------------------------------------------------------------------------
 */
extern void priority_queue_assign(
    priority_queue_t* pt_pqueuedest, const priority_queue_t* cpt_pqueuesrc);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: priority_queue_empty
 *        Parameters: in) cpt_pqueue: const priority_queue_t*
 *                          the dest priority queue.
 *           Returns: bool_t
 *       Description: if the priority queue is empty.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t priority_queue_empty(const priority_queue_t* cpt_pqueue);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: priority_queue_size
 *        Parameters: in) cpt_pqueue: const priority_queue_t*
 *                          the dest priority queue.
 *           Returns: size_t
 *       Description: get the priority queue size.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t priority_queue_size(const priority_queue_t* cpt_pqueue);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: priority_queue_top
 *        Parameters: in) cpt_pqueue: const priority_queue_t*
 *                          the priority queue.
 *           Returns: void*
 *       Description: return the top element.
 *
 * ----------------------------------------------------------------------------
 */
extern void* priority_queue_top(const priority_queue_t* cpt_pqueue);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: priority_queue_pop
 *        Parameters: in) pt_pqueue: priority_queue_t*
 *                          the priority queue.
 *           Returns: void
 *       Description: remove the top element and does not return it.
 *
 * ----------------------------------------------------------------------------
 */
extern void priority_queue_pop(priority_queue_t* pt_pqueue);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_QUEUE_H */
/** eof **/

