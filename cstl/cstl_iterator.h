/*
 *  The user interface of iterator.
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

#ifndef _CSTL_ITERATOR_H_
#define _CSTL_ITERATOR_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Get value that pointed by iterator.
 * @param it_iter      iterator.
 * @param pv_value     value.
 * @return void
 * @remakes it_iter must be valid and pv_value != NULL, otherwise the behavior is undefined.
 */
extern void iterator_get_value(iterator_t it_iter, void* pv_value);

/**
 * Set value that pointed by iterator.
 * @param it_iter      iterator.
 * @param cpv_value    value.
 * @return void
 * @remakes it_iter must be valid and cpv_value != NULL, otherwise the behavior is undefined.
 */
extern void iterator_set_value(iterator_t it_iter, const void* cpv_value);

/**
 * Get pointer that pointed by iterator.
 * @param it_iter      iterator.
 * @return pointer
 * @remakes it_iter must be valid and must be not end(), otherwise the behavior is undefined.
 */
extern const void* iterator_get_pointer(iterator_t it_iter);

/**
 * Move iterator to next position.
 * @param it_iter      iterator.
 * @return next position.
 * @remakes it_iter must be valid and must be not end(), otherwise the behavior is undefined.
 */
extern iterator_t iterator_next(iterator_t it_iter);

/**
 * Move iterator to previous position.
 * @param it_iter      iterator.
 * @return previous position.
 * @remakes it_iter must be valid and must be not end(), otherwise the behavior is undefined.
 */
extern iterator_t iterator_prev(iterator_t it_iter);

/**
 * Move iterator to next n position.
 * @param it_iter      iterator.
 * @return next n position.
 * @remakes it_iter must be valid and must be not end(), otherwise the behavior is undefined.
 */
extern iterator_t iterator_next_n(iterator_t it_iter, int n_step);

/**
 * Move iterator to prev n position.
 * @param it_iter      iterator.
 * @return prev n position.
 * @remakes it_iter must be valid and must be not end(), otherwise the behavior is undefined.
 */
extern iterator_t iterator_prev_n(iterator_t it_iter, int n_step);

/**
 * Test two iterator are equal or not.
 * @param it_first     first iterator.
 * @param it_second    second iterator.
 * @return whether equal or not.
 * @remakes two iterator must be valid, otherwise the behavior is undefined.
 */
extern bool_t iterator_equal(iterator_t it_first, iterator_t it_second);

/**
 * Test two iterator are equal or not.
 * @param it_first     first iterator.
 * @param it_second    second iterator.
 * @return whether equal or not.
 * @remakes two iterator must be valid, otherwise the behavior is undefined.
 */
extern bool_t iterator_not_equal(iterator_t it_first, iterator_t it_second);

/**
 * Test first iterator is less than second iterator.
 * @param it_first     first iterator.
 * @param it_second    second iterator.
 * @return whether first iterator less than second iterator or not.
 * @remakes two iterator must be valid, otherwise the behavior is undefined.
 */
extern bool_t iterator_less(iterator_t it_first, iterator_t it_second);

/**
 * Test first iterator is less than or equal to second iterator.
 * @param it_first     first iterator.
 * @param it_second    second iterator.
 * @return whether first iterator less than or equal to second iterator or not.
 * @remakes two iterator must be valid, otherwise the behavior is undefined.
 */
extern bool_t iterator_less_equal(iterator_t it_first, iterator_t it_second);

/**
 * Test first iterator is greater than second iterator.
 * @param it_first     first iterator.
 * @param it_second    second iterator.
 * @return whether first iterator greater than second iterator or not.
 * @remakes two iterator must be valid, otherwise the behavior is undefined.
 */
extern bool_t iterator_greater(iterator_t it_first, iterator_t it_second);

/**
 * Test first iterator is greater than or equal to second iterator.
 * @param it_first     first iterator.
 * @param it_second    second iterator.
 * @return whether first iterator greater than or equal to second iterator or not.
 * @remakes two iterator must be valid, otherwise the behavior is undefined.
 */
extern bool_t iterator_greater_equal(iterator_t it_first, iterator_t it_second);

/**
 * Element random access.
 * @param it_iter      iterator.
 * @param n_index      index.
 * @return element pointer.
 * @remarks iterator must be valid, otherwise the behavior is undefined.
 */
extern void* iterator_at(iterator_t it_iter, int n_index);

/**
 * Iterator distance.
 * @param it_first     first iterator.
 * @param it_second    second iterator.
 * @return iterator distance.
 * @remakes two iterator must be valid, otherwise the behavior is undefined.
 */
extern int iterator_minus(iterator_t it_first, iterator_t it_second);

/**
 * Iterator next n for all iterator type.
 * @param it_iter      iterator.
 * @param n_step       step.
 * @return next n iterator.
 * @remarks iterator must be valid, otherwise the behavior is undefined.
 */
extern iterator_t iterator_advance(iterator_t it_iter, int n_step);

/**
 * Iterator distance for all iterator type.
 * @param it_first     first iterator.
 * @param it_second    second iterator.
 * @return iterator distance.
 * @remakes two iterator must be valid, otherwise the behavior is undefined.
 */
extern int iterator_distance(iterator_t it_first, iterator_t it_second);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_ITERATOR_H_ */
/** eof **/

