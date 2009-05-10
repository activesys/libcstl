/*
 *  The interface of map iterator.
 *  Copyright (C)  2008 2009  Wangbo
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

#ifndef _CSTL_MAP_ITERATOR_H
#define _CSTL_MAP_ITERATOR_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
typedef iterator_t map_iterator_t;
typedef iterator_t map_reverse_iterator_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * Iterator support.
 */
extern map_iterator_t create_map_iterator(void);
extern void _map_iterator_get_value(map_iterator_t t_iter, void* pv_value);
extern const void* _map_iterator_get_pointer(map_iterator_t t_iter);
extern map_iterator_t _map_iterator_next(map_iterator_t t_iter);
extern map_iterator_t _map_iterator_prev(map_iterator_t t_iter);
extern bool_t _map_iterator_equal(
    map_iterator_t t_iterfirst, map_iterator_t t_itersecond);
extern int _map_iterator_distance(
    map_iterator_t t_iterfirst, map_iterator_t t_itersecond);
extern bool_t _map_iterator_before(
    map_iterator_t t_iterfirst, map_iterator_t t_itersecond);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_MAP_ITERATOR_H */
/** eof **/

