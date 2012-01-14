/*
 *  The vector iterator interface for iterator module.
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

#ifndef _CSTL_VECTOR_ITERATOR_H_
#define _CSTL_VECTOR_ITERATOR_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
typedef iterator_t vector_iterator_t;
typedef iterator_t vector_reverse_iterator_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Create new vector iterator.
 * @param void.
 * @return new vector iterator.
 * @remarks the newly created vector iterator is not a valid iterator, it does not belong to any vector.
 */
extern vector_iterator_t _create_vector_iterator(void);

/**
 * Compare two iterators for equality.
 * @param it_first   first iterator.
 * @param it_second  second iterator.
 * @return true if two iterators are equal, otherwise return false.
 * @remarks if two iterators with different container type or iterator type, then behavior is undefined.
 *          if two iterators are not belong to same container, then behavior is undefined.
 */
extern bool_t _vector_iterator_equal(vector_iterator_t it_first, vector_iterator_t it_second);

/**
 * Testing of the first iterator is less than the second iterator.
 * @param it_first   first iterator.
 * @param it_second  second iterator.
 * @return true if the first iterator is less than the second one, otherwise return false.
 * @remarks if two iterators with different container type or iterator type, then behavior is undefined.
 *          if two iterators are not belong to same container, then behavior is undefined.
 */
extern bool_t _vector_iterator_less(vector_iterator_t it_first, vector_iterator_t it_second);

/**
 * Testing of the first iterator is located in front of the second iterator.
 * @param it_first   first iterator.
 * @param it_second  second iterator.
 * @return true if the first iterator is in front of the second iterator, otherwise return false.
 * @remarks if two iterators with different container type or iterator type, then behavior is undefined.
 *          if two iterators are not belong to same container, then behavior is undefined.
 */
extern bool_t _vector_iterator_before(vector_iterator_t it_first, vector_iterator_t it_second);

/**
 * Get iterator reference data.
 * @param it_iter vector iterator.
 * @param pv_value point to buffer that be used to save date.
 * @return void.
 * @remarks it_iter must be valid vector iterator, otherwise the behavior is undefined. if pv_value == NULL,
 *          then the behavior is undefined.
 */
extern void _vector_iterator_get_value(vector_iterator_t it_iter, void* pv_value);

/**
 * Set iterator reference data.
 * @param it_iter vector iterator.
 * @param cpv_value point to buffer that be used to save date.
 * @return void.
 * @remarks it_iter must be valid vector iterator, otherwise the behavior is undefined. if pv_value == NULL,
 *          then the behavior is undefined.
 */
extern void _vector_iterator_set_value(vector_iterator_t it_iter, const void* cpv_value);

/**
 * Get the pointer that point to the iterator reference data.
 * @param it_iter vector iterator.
 * @return data pointer.
 * @remarks it_iter must be valid vector iterator, otherwise the behavior is undefined.
 */
extern const void* _vector_iterator_get_pointer(vector_iterator_t it_iter); 

/**
 * Get the pointer that point to the iterator reference data, but ignore char*.
 * @param it_iter vector iterator.
 * @return data pointer.
 * @remarks it_iter must be valid vector iterator, otherwise the behavior is undefined.
 */
extern const void* _vector_iterator_get_pointer_ignore_cstr(vector_iterator_t it_iter); 

/**
 * Get the iterator that reference next data.
 * @param it_iter vector iterator.
 * @return next iterator.
 * @remarks it_iter and the returned iterator must be valid vector iterator, otherwise the behavior is undefined.
 */
extern vector_iterator_t _vector_iterator_next(vector_iterator_t it_iter);

/**
 * Get the iterator that reference previous data.
 * @param it_iter vector iterator.
 * @return previous iterator.
 * @remarks it_iter and the returned iterator must be valid vector iterator, otherwise the behavior is undefined.
 */
extern vector_iterator_t _vector_iterator_prev(vector_iterator_t it_iter);

/**
 * Get the iterator that reference next n data.
 * @param it_iter vector iterator.
 * @param n_step steps to move.
 * @return next n iterator.
 * @remarks it_iter and the returned iterator must be valid vector iterator, otherwise the behavior is undefined.
 *          if n_step > 0, iterator move to the end of the container. if n_step < 0, iterator move to the begin of
 *          the container. if n_step == 0, iterator dose not move.
 */
extern vector_iterator_t _vector_iterator_next_n(vector_iterator_t it_iter, int n_step);

/**
 * Get the iterator that reference previous n data.
 * @param it_iter vector iterator.
 * @param n_step steps to move.
 * @return next n iterator.
 * @remarks it_iter and the returned iterator must be valid vector iterator, otherwise the behavior is undefined.
 *          if n_step > 0, iterator move to the begin of the container. if n_step < 0, iterator move to the end of
 *          the container. if n_step == 0, iterator dose not move.
 */
extern vector_iterator_t _vector_iterator_prev_n(vector_iterator_t it_iter, int n_step);

/**
 * Access iterator reference data randomly with subscript.
 * @param it_iter vector iterator.
 * @param n_index subscript
 * @return reference data.
 * @remarks it_iter must be valid vector iterator, and referenced data must whitin the vector, otherwise the behavior
 *          is undefined. if n_index > 0, iterator move to the begin of the container. if n_index < 0, iterator move to
 *          the end of the container. if n_index == 0, return iterator reference data.
 */
extern void* _vector_iterator_at(vector_iterator_t it_iter, int n_index);

/**
 * Calculate the distance between two iterators.
 * @param it_first first vector iterator.
 * @param it_second second vector iterator.
 * @return the distance between two iterators.
 * @remarks the two iterators must be valid vector iterator, otherwist the behavious is undefined. if it_first < it_second,
 *          then return value < 0, if it_first > it_second, then return value > 0, if it_first == it_second, then return
 *          value == 0.
 */
extern int _vector_iterator_minus(vector_iterator_t it_first, vector_iterator_t it_second);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_VECTOR_ITERATOR_H_ */
/** eof **/

