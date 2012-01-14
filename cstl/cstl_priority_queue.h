/*
 *  The interface of priority queue.
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
#ifndef _CSTL_PRIORITY_QUEUE_H_
#define _CSTL_PRIORITY_QUEUE_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/* create new priority queue */
#define create_priority_queue(...) _create_priority_queue(#__VA_ARGS__)
/* push */
#define priority_queue_push(pt_pqueue, elem)\
    _priority_queue_push((pt_pqueue), (elem))

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/

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

#endif /* _CSTL_PRIORITY_QUEUE_H_ */
/** eof **/

