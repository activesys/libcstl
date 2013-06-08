/*
 *  The interface of priority queue.
 *  Copyright (C)  2008 - 2013  Wangbo
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
/**
 * Create priority queue adaptor.
 * @param ...    type name.
 * @return priority queue adaptor pointer, if create queue successfully, else return NULL.
 * @remarks if s_typename == NULL, the behavior is undefined. s_typename must be c builtin type, libcstl builtin type or
 *          user defined type, otherwise creation will be failure.
 */
#define create_priority_queue(...) _create_priority_queue(#__VA_ARGS__)

/**
 * Add specificed element at the back of priority queue. 
 * @param ppque_pqueue    priority queue adaptor.
 * @param elem            specificed element.
 * @return void.
 * @remarks if ppque_pqueue == NULL or priority queue is uninitialized, then the behavior is undefined. the type of specificed
 *          element and priority queue element type must be same, otherwise the behavior is undefined. the first specificed is
 *          in use, others are not in use.
 */
#define priority_queue_push(ppque_pqueue, elem) _priority_queue_push((ppque_pqueue), (elem))

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Initialize an empty priority queue adaptor
 * @param ppque_pqueue   priority queue adaptor.
 * @return void.
 * @remarks if ppque_pqueue == NULL, then the behavior is undefined. pque_queue must be created by create_priority_queue(), otherwise
 *          the behavior is undefine.
 */
extern void priority_queue_init(priority_queue_t* ppque_pqueue);

/**
 * Initialize an empty priority queue adaptor with user define priority rule.
 * @param ppque_pqueue   priority queue adaptor.
 * @param bfun_op        priority rule.
 * @return void.
 * @remarks if ppque_pqueue == NULL, then the behavior is undefined. pque_queue must be created by create_priority_queue(), otherwise
 *          the behavior is undefine.
 */
extern void priority_queue_init_ex(priority_queue_t* ppque_pqueue, bfun_t bfun_op);

/**
 * Initialize an priority queue adaptor from an exist priority queue.
 * @param ppque_dest    destination priority queue adaptor.
 * @param ppque_src     source priority queue_adaptor.
 * @return void.
 * @remarks destination and source priority queue adaptor must be valid, and must be have same element type, otherwise the behavior is undefined.
 */
extern void priority_queue_init_copy(priority_queue_t* ppque_dest, const priority_queue_t* cppque_src);

/**
 * Initialize an priority queue adaptor from an exist range.
 * @param ppque_dest    destination priority queue adaptor.
 * @param it_first      An iterator addressing the first element in the reange.
 * @param it_last       An iterator addressing the last element in the range.
 * @return void.
 * @remarks destination priority queue adaptor and source range must be valid, and must be have same element type, otherwise the behavior is undefined.
 */
extern void priority_queue_init_copy_range(priority_queue_t* ppque_dest, input_iterator_t it_first, input_iterator_t it_last);

/**
 * Initialize an priority queue adaptor from an exist range with user define priority rule.
 * @param ppque_dest    destination priority queue adaptor.
 * @param it_first      An iterator addressing the first element in the reange.
 * @param it_last       An iterator addressing the last element in the range.
 * @param bfun_op       User defined priority rule.
 * @return void.
 * @remarks destination priority queue adaptor and source range must be valid, and must be have same element type, otherwise the behavior is undefined.
 */
extern void priority_queue_init_copy_range_ex(priority_queue_t* ppque_dest, input_iterator_t it_first, input_iterator_t it_last, bfun_t bfun_op);

/**
 * Initialize an priority queue adaptor from an exist array.
 * @param ppque_dest    destination priority queue adaptor.
 * @param cpv_array     An exist array.
 * @param t_count       Element count.
 * @return void.
 * @remarks destination priority queue adaptor and source array must be valid, and must be have same element type, otherwise the behavior is undefined.
 */
extern void priority_queue_init_copy_array(priority_queue_t* ppque_dest, const void* cpv_array, size_t t_count);

/**
 * Initialize an priority queue adaptor from an exist array with user define priority rule.
 * @param ppque_dest    destination priority queue adaptor.
 * @param cpv_array     An exist array.
 * @param t_count       Element count.
 * @param bfun_op       User defined priority rule.
 * @return void.
 * @remarks destination priority queue adaptor and source array must be valid, and must be have same element type, otherwise the behavior is undefined.
 */
extern void priority_queue_init_copy_array_ex(priority_queue_t* ppque_dest, const void* cpv_array, size_t t_count, bfun_t bfun_op);

/**
 * Destroy priority queue adaptor.
 * @param ppque_pqueue   priority queue adaptor.
 * @return void.
 * @remraks if ppque_pqueue == NULLL, then the behavior is undefined. ppque_pqueue must be initialized or created by
 *          create_priority_queue(), otherwise the behavior is undefined.
 */
extern void priority_queue_destroy(priority_queue_t* ppque_pqueue);

/**
 * Assign priority queue adaptor from exist.
 * @param ppque_dest    destination priority queue adaptor.
 * @param ppque_src     source priority queue_adaptor.
 * @return void.
 * @remarks destination and source priority queue adaptor must be valid, and must be have same element type, otherwise the behavior is undefined.
 */
extern void priority_queue_assign(priority_queue_t* ppque_dest, const priority_queue_t* cppque_src);

/**
 * Tests if a priority_queue is empty.
 * @param cppque_pqueue     priority queue adaptor.
 * @reture  true if the priority_queue is empty; false if the priority_queue is nonempty.
 * @remarks The priority queue adaptor must be valid, otherwise the behavior is undefined.
 */
extern bool_t priority_queue_empty(const priority_queue_t* cppque_pqueue);

/**
 * Returns the number of elements in the priority_queue.
 * @param cppque_pqueue     priority queue adaptor.
 * @reture  The current length of the priority_queue.
 * @remarks The priority queue adaptor must be valid, otherwise the behavior is undefined.
 */
extern size_t priority_queue_size(const priority_queue_t* cppque_pqueue);

/**
 * Returns a const reference to the largest element at the top of the priority_queue.
 * @param cppque_pqueue     priority queue adaptor.
 * @reture  A const reference to the largest element, as determined by the Traits function, object of the priority_queue.
 * @remarks The priority queue adaptor must be valid, otherwise the behavior is undefined.
 */
extern void* priority_queue_top(const priority_queue_t* cppque_pqueue);

/**
 * Removes the largest element of the priority_queue from the top position.
 * @param cppque_pqueue     priority queue adaptor.
 * @reture  void.
 * @remarks The priority queue adaptor must be valid, otherwise the behavior is undefined.
 */
extern void priority_queue_pop(priority_queue_t* ppque_pqueue);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_PRIORITY_QUEUE_H_ */
/** eof **/

