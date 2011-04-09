/*
 *  Interface of avl tree iterator.
 *  Copyright (C)  2008,2009,2010,2011  Wangbo
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

#ifndef _CSTL_AVL_TREE_ITERATOR_H_
#define _CSTL_AVL_TREE_ITERATOR_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
typedef iterator_t _avl_tree_iterator_t;
typedef iterator_t _avl_tree_reverse_iterator_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Create avl tree iterator.
 * @return avl tree iterator.
 * @remarks the returned iterator is invalid iterator.
 */
extern _avl_tree_iterator_t _create_avl_tree_iterator(void);

/**
 * Get data value referenced by iterator.
 * @param it_iter    avl tree iterator.
 * @param pv_value   data value buffer.
 * @return void.
 * @remarks it_iter must be valid avl tree iterator, otherwise the behavior is undefined. if pv_value == NULL, then the
 *          behavior is undefined.
 */
extern void _avl_tree_iterator_get_value(_avl_tree_iterator_t t_iter, void* pv_value);
extern const void* _avl_tree_iterator_get_pointer(_avl_tree_iterator_t t_iter); 
extern _avl_tree_iterator_t _avl_tree_iterator_next(_avl_tree_iterator_t t_iter);
extern _avl_tree_iterator_t _avl_tree_iterator_prev(_avl_tree_iterator_t t_iter);
extern bool_t _avl_tree_iterator_equal(
    _avl_tree_iterator_t t_iterfirst, _avl_tree_iterator_t t_itersecond);
extern int _avl_tree_iterator_distance(
    _avl_tree_iterator_t t_iterfirst, _avl_tree_iterator_t t_itersecond);
extern bool_t _avl_tree_iterator_before(
    _avl_tree_iterator_t t_iterfirst, _avl_tree_iterator_t t_itersecond);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_AVL_TREE_ITERATOR_H_ */
/** eof **/

