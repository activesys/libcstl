/*
 *  The deque iterator interface for iterator module.
 *  Copyright (C)  2008 - 2014  Wangbo
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

#ifndef _CSTL_DEQUE_ITERATOR_H_
#define _CSTL_DEQUE_ITERATOR_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
typedef iterator_t deque_iterator_t;
typedef iterator_t deque_reverse_iterator_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Create new deque iterator.
 * @param void.
 * @return new deque iterator.
 * @remarks the newly created deque iterator is not a valid iterator, it does not belong to any deque.
 */
extern deque_iterator_t _create_deque_iterator(void);

/**
 * Compare two iterators for equality.
 * @param it_first   first iterator.
 * @param it_second  second iterator.
 * @return true if two iterators are equal, otherwise return false.
 * @remarks if two iterators with different container type or iterator type, then behavior is undefined.
 *          if two iterators are not belong to same container, then behavior is undefined.
 */
extern bool_t _deque_iterator_equal(deque_iterator_t it_first, deque_iterator_t it_second);

/**
 * Testing of the first iterator is less than the second iterator.
 * @param it_first   first iterator.
 * @param it_second  second iterator.
 * @return true if the first iterator is less than the second one, otherwise return false.
 * @remarks if two iterators with different container type or iterator type, then behavior is undefined.
 *          if two iterators are not belong to same container, then behavior is undefined.
 */
extern bool_t _deque_iterator_less(deque_iterator_t it_first, deque_iterator_t it_second);

/**
 * Testing of the first iterator is located in front of the second iterator.
 * @param it_first   first iterator.
 * @param it_second  second iterator.
 * @return true if the first iterator is in front of the second iterator, otherwise return false.
 * @remarks if two iterators with different container type or iterator type, then behavior is undefined.
 *          if two iterators are not belong to same container, then behavior is undefined.
 */
extern bool_t _deque_iterator_before(deque_iterator_t it_first, deque_iterator_t it_second);

/**
 * Get iterator reference data.
 * @param it_iter deque iterator.
 * @param pv_value point to buffer that be used to save date.
 * @return void.
 * @remarks it_iter must be valid deque iterator, otherwise the behavior is undefined. if pv_value == NULL,
 *          then the behavior is undefined.
 */
extern void _deque_iterator_get_value(deque_iterator_t it_iter, void* pv_value);

/**
 * Set iterator reference data.
 * @param it_iter deque iterator.
 * @param cpv_value point to buffer that be used to save date.
 * @return void.
 * @remarks it_iter must be valid deque iterator, otherwise the behavior is undefined. if pv_value == NULL,
 *          then the behavior is undefined.
 */
extern void _deque_iterator_set_value(deque_iterator_t it_iter, const void* cpv_value);

/**
 * Get the pointer that point to the iterator reference data.
 * @param it_iter deque iterator.
 * @return data pointer.
 * @remarks it_iter must be valid deque iterator, otherwise the behavior is undefined.
 */
extern const void* _deque_iterator_get_pointer(deque_iterator_t it_iter); 

/**
 * Get the pointer that point to the iterator reference data, but ignore char*.
 * @param it_iter deque iterator.
 * @return data pointer.
 * @remarks it_iter must be valid deque iterator, otherwise the behavior is undefined.
 */
extern const void* _deque_iterator_get_pointer_ignore_cstr(deque_iterator_t it_iter); 

/**
 * Get the iterator that reference next data.
 * @param it_iter deque iterator.
 * @return next iterator.
 * @remarks it_iter and the returned iterator must be valid deque iterator, otherwise the behavior is undefined.
 */
extern deque_iterator_t _deque_iterator_next(deque_iterator_t it_iter);

/**
 * Get the iterator that reference previous data.
 * @param it_iter deque iterator.
 * @return previous iterator.
 * @remarks it_iter and the returned iterator must be valid deque iterator, otherwise the behavior is undefined.
 */
extern deque_iterator_t _deque_iterator_prev(deque_iterator_t it_iter);

/**
 * Get the iterator that reference next n data.
 * @param it_iter deque iterator.
 * @param n_step steps to move.
 * @return next n iterator.
 * @remarks it_iter and the returned iterator must be valid deque iterator, otherwise the behavior is undefined.
 *          if n_step > 0, iterator move to the end of the container. if n_step < 0, iterator move to the begin of
 *          the container. if n_step == 0, iterator dose not move.
 */
extern deque_iterator_t _deque_iterator_next_n(deque_iterator_t it_iter, int n_step);

/**
 * Get the iterator that reference previous n data.
 * @param it_iter deque iterator.
 * @param n_step steps to move.
 * @return next n iterator.
 * @remarks it_iter and the returned iterator must be valid deque iterator, otherwise the behavior is undefined.
 *          if n_step > 0, iterator move to the begin of the container. if n_step < 0, iterator move to the end of
 *          the container. if n_step == 0, iterator dose not move.
 */
extern deque_iterator_t _deque_iterator_prev_n(deque_iterator_t it_iter, int n_step);

/**
 * Access iterator reference data randomly with subscript.
 * @param it_iter deque iterator.
 * @param n_index subscript
 * @return reference data.
 * @remarks it_iter must be valid deque iterator, and referenced data must whitin the deque, otherwise the behavior
 *          is undefined. if n_index > 0, iterator move to the begin of the container. if n_index < 0, iterator move to
 *          the end of the container. if n_index == 0, return iterator reference data.
 */
extern void* _deque_iterator_at(deque_iterator_t it_iter, int n_index);

/**
 * Calculate the distance between two iterators.
 * @param it_first first deque iterator.
 * @param it_second second deque iterator.
 * @return the distance between two iterators.
 * @remarks the two iterators must be valid deque iterator, otherwist the behavious is undefined. if it_first < it_second,
 *          then return value < 0, if it_first > it_second, then return value > 0, if it_first == it_second, then return
 *          value == 0.
 */
extern int _deque_iterator_minus(deque_iterator_t it_first, deque_iterator_t it_second);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_DEQUE_ITERATOR_H_ */
/** eof **/

