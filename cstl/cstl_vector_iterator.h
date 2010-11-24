/*
 *  The vector iterator interface for iterator module.
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

#ifndef _CSTL_VECTOR_ITERATOR_H
#define _CSTL_VECTOR_ITERATOR_H

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
extern const void* _vector_iterator_get_pointer(vector_iterator_t t_iter); 

/*
 * Increase or decrease operator of iterator_t.
 */
extern vector_iterator_t _vector_iterator_next(vector_iterator_t t_iter);
extern vector_iterator_t _vector_iterator_prev(vector_iterator_t t_iter);
extern vector_iterator_t _vector_iterator_next_n(vector_iterator_t t_iter, int n_step);
extern vector_iterator_t _vector_iterator_prev_n(vector_iterator_t t_iter, int n_step);

/*
 * Access element randomly through iterator_t.
 */
extern void* _vector_iterator_at(vector_iterator_t t_iter, int n_index);

/*
 * Subaction operator of iterator_t.
 */
extern int _vector_iterator_minus(
    vector_iterator_t t_iterfirst, vector_iterator_t t_itersecond);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_VECTOR_ITERATOR_H */
/** eof **/

