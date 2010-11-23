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
extern bool_t _vector_iterator_less(
    vector_iterator_t t_iterfirst, vector_iterator_t t_itersecond);
extern bool_t _vector_iterator_before(
    vector_iterator_t t_iterfirst, vector_iterator_t t_itersecond);

/*
 * Get and Set element that is referenced by iterator_t.
 */
extern void _vector_iterator_get_value(vector_iterator_t t_iter, void* pv_value);
extern void _vector_iterator_set_value(vector_iterator_t t_iter, const void* cpv_value);
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

