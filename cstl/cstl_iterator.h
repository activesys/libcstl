/*
 *  The user interface of iterator.
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
/* the handler of iterator */
/*
 * Get and set value.
 */
extern void iterator_get_value(iterator_t t_iter, void* pv_value);
extern void iterator_set_value(iterator_t t_iter, const void* cpv_value);
extern const void* iterator_get_pointer(iterator_t t_iter);

/*
 * Move iterator.
 */
extern iterator_t iterator_next(iterator_t t_iter);
extern iterator_t iterator_prev(iterator_t t_iter);
extern iterator_t iterator_next_n(iterator_t t_iter, int n_step);
extern iterator_t iterator_prev_n(iterator_t t_iter, int n_step);

/*
 * Relationship operator functions.
 */
extern bool_t iterator_equal(iterator_t t_iterfirst, iterator_t t_itersecond);
extern bool_t iterator_not_equal(iterator_t t_iterfirst, iterator_t t_itersecond);
extern bool_t iterator_less(iterator_t t_iterfirst, iterator_t t_itersecond);
extern bool_t iterator_less_equal(iterator_t t_iterfirst, iterator_t t_itersecond);
extern bool_t iterator_greater(iterator_t t_iterfirst, iterator_t t_itersecond);
extern bool_t iterator_greater_equal(iterator_t t_iterfirst, iterator_t t_itersecond);

/*
 * Element random access.
 */
extern void* iterator_at(iterator_t t_iter, int n_index);


/*
 * Distance.
 */
extern int iterator_minus(iterator_t t_iterfirst, iterator_t t_itersecond);

/* the iterator auxilary function */
/*
 * Advance and distance.
 */
extern iterator_t iterator_advance(iterator_t t_iter, int n_step);
extern int iterator_distance(iterator_t t_iterfirst, iterator_t t_itersecond);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_ITERATOR_H_ */
/** eof **/

