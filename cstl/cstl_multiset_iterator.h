/*
 *  The iterator interface of multiset.
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

#ifndef _CSTL_MULTISET_ITERATOR_H
#define _CSTL_MULTISET_ITERATOR_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
typedef iterator_t multiset_iterator_t;
typedef iterator_t multiset_reverse_iterator_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * Iterator support.
 */
extern multiset_iterator_t create_multiset_iterator(void);
extern void _multiset_iterator_get_value(
    multiset_iterator_t t_iter, void* pv_value);
extern const void* _multiset_iterator_get_pointer(multiset_iterator_t t_iter);
extern multiset_iterator_t _multiset_iterator_next(multiset_iterator_t t_iter);
extern multiset_iterator_t _multiset_iterator_prev(multiset_iterator_t t_iter);
extern bool_t _multiset_iterator_equal(
    multiset_iterator_t t_iterfirst, multiset_iterator_t t_itersecond);
extern int _multiset_iterator_distance(
    multiset_iterator_t t_iterfirst, multiset_iterator_t t_itersecond);
extern bool_t _multiset_iterator_before(
    multiset_iterator_t t_iterfirst, multiset_iterator_t t_itersecond);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_MULTISET_ITERATOR_H */
/** eof **/

