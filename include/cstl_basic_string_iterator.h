/*
 *  The iterator interface of basic_string.
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

#ifndef _CSTL_BASIC_STRING_ITERATOR_H
#define _CSTL_BASIC_STRING_ITERATOR_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
typedef iterator_t basic_string_iterator_t;
typedef iterator_t basic_string_reverse_iterator_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * Iterator support.
 */
/*
 * Create new iterator for basic string.
 */
extern basic_string_iterator_t create_basic_string_iterator(void);

/*
 * The relationship operator of basic string iterator.
 */
extern bool_t _basic_string_iterator_equal(
    basic_string_iterator_t t_iterfirst, basic_string_iterator_t t_itersecond);
extern bool_t _basic_string_iterator_less(
    basic_string_iterator_t t_iterfirst, basic_string_iterator_t t_itersecond);
extern bool_t _basic_string_iterator_before(
    basic_string_iterator_t t_iterfirst, basic_string_iterator_t t_itersecond);

/*
 * Element accession.
 */
extern void _basic_string_iterator_get_value(
    basic_string_iterator_t t_iter, void* pv_value);
extern void _basic_string_iterator_set_value(
    basic_string_iterator_t t_iter, const void* cpv_value);
extern const void* _basic_string_iterator_get_pointer(
    basic_string_iterator_t t_iter);

/*
 * Increase or decrease of basic string iterator.
 */
extern basic_string_iterator_t _basic_string_iterator_next(
    basic_string_iterator_t t_iter);
extern basic_string_iterator_t _basic_string_iterator_prev(
    basic_string_iterator_t t_iter);
extern basic_string_iterator_t _basic_string_iterator_next_n(
    basic_string_iterator_t t_iter, int n_step);
extern basic_string_iterator_t _basic_string_iterator_prev_n(
    basic_string_iterator_t t_iter, int n_step);

/*
 * Random access.
 */
extern void* _basic_string_iterator_at(
    basic_string_iterator_t t_iter, int n_index);

/*
 * Distance of basic string iterator.
 */
extern int _basic_string_iterator_minus(
    basic_string_iterator_t t_iterfirst, basic_string_iterator_t t_itersecond);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_BASIC_STRING_ITERATOR_H */
/** eof **/

