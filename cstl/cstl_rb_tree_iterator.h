/*
 *  The interface of rb tree iterator.
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

#ifndef _CSTL_RB_TREE_ITERATOR_H_
#define _CSTL_RB_TREE_ITERATOR_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
typedef iterator_t _rb_tree_iterator_t;
typedef iterator_t _rb_tree_reverse_iterator_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Create rb tree iterator.
 * @return rb tree iterator.
 * @remarks the returned iterator is invalid iterator.
 */
extern _rb_tree_iterator_t _create_rb_tree_iterator(void);

/**
 * Get data value referenced by iterator.
 * @param it_iter    rb tree iterator.
 * @param pv_value   data value buffer.
 * @return void.
 * @remarks it_iter must be valid rb tree iterator, otherwise the behavior is undefined. if pv_value == NULL, then the
 *          behavior is undefined.
 */
extern void _rb_tree_iterator_get_value(_rb_tree_iterator_t it_iter, void* pv_value);

/**
 * Get data value pointer referenced by iterator.
 * @param it_iter    rb tree iterator.
 * @return void.
 * @remarks it_iter must be valid rb tree iterator, otherwise the behavior is undefined.
 */
extern const void* _rb_tree_iterator_get_pointer(_rb_tree_iterator_t it_iter);

/**
 * Get data value pointer referenced by iterator, but ignore char*.
 * @param it_iter    rb tree iterator.
 * @return void.
 * @remarks it_iter must be valid rb tree iterator, otherwise the behavior is undefined.
 */
extern const void* _rb_tree_iterator_get_pointer_ignore_cstr(_rb_tree_iterator_t it_iter);

/**
 * Return iterator reference next element.
 * @param  it_iter    current iterator.
 * @return next iterator.
 * @remarks it_iter and next iterator must be valid iterator, otherwise the behavior is undefined.
 */
extern _rb_tree_iterator_t _rb_tree_iterator_next(_rb_tree_iterator_t it_iter);

/**
 * Return iterator reference previous element.
 * @param  it_iter    current iterator.
 * @return previous iterator.
 * @remarks it_iter and previous iterator must be valid iterator, otherwise the behavior is undefined.
 */
extern _rb_tree_iterator_t _rb_tree_iterator_prev(_rb_tree_iterator_t it_iter);

/**
 * Test the two rb tree iterator are equal.
 * @param it_first    rb tree iterator.
 * @param it_second   rb tree iterator.
 * @return true, if the two iterator are equal, else return false.
 * @remarks the two iterator must be valid rb tree iterator, otherwise the behavior is undefined.
 */
extern bool_t _rb_tree_iterator_equal(_rb_tree_iterator_t it_first, _rb_tree_iterator_t it_second);

/**
 * Calculate distance between two iterators.
 * @param it_first    rb tree iterator.
 * @param it_second   rb tree iterator.
 * @return distance.
 * @remarks the two iterator must be valid rb tree iterator, and must be belong to same rb tree, otherwise the behavior
 *          is undefined. the result distance may be less than 0, equal to 0 or greater than 0.
 */
extern int _rb_tree_iterator_distance(_rb_tree_iterator_t it_first, _rb_tree_iterator_t it_second);

/**
 * Test the first iterator is before the second.
 * @param it_first    rb tree iterator.
 * @param it_second   rb tree iterator.
 * @return true, if the first iterator is before the second, else return false.
 * @remarks the two iterator must be valid rb tree iterator, and must be belong to same rb tree, otherwise the behavior
 *          is undefined.
 */
extern bool_t _rb_tree_iterator_before(_rb_tree_iterator_t it_first, _rb_tree_iterator_t it_second);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_RB_TREE_ITERATOR_H_ */
/** eof **/

