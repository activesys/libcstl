/*
 *  The deque iterator interface for iterator module.
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

#ifndef _CSTL_DEQUE_ITERATOR_H
#define _CSTL_DEQUE_ITERATOR_H

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
extern const void* _deque_iterator_get_pointer(deque_iterator_t t_iter); 

/*
 * Increase and decrease of deque iterator.
 */
extern deque_iterator_t _deque_iterator_next(deque_iterator_t pt_iter);
extern deque_iterator_t _deque_iterator_prev(deque_iterator_t t_iter);
extern void* _deque_iterator_at(deque_iterator_t t_iter, int n_index);
extern deque_iterator_t _deque_iterator_next_n(deque_iterator_t t_iter, int n_step);
extern deque_iterator_t _deque_iterator_prev_n(deque_iterator_t t_iter, int n_step);

/*
 * Distance of deque iterator.
 */
extern int _deque_iterator_minus(
    deque_iterator_t t_iterfirst, deque_iterator_t t_itersecond);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_DEQUE_ITERATOR_H */
/** eof **/

