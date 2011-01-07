/*
 *  The private interface of iterator.
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

#ifndef _CSTL_ITERATOR_PRIVATE_H
#define _CSTL_ITERATOR_PRIVATE_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * Private iterator functions.
 */
extern bool_t _iterator_same_type(iterator_t t_iterfirst, iterator_t t_itersecond);
extern bool_t _iterator_before(iterator_t t_iterfirst, iterator_t t_itersecond);
extern bool_t _iterator_limit_type(iterator_t t_iter, iteratortype_t t_limittype);

extern bool_t _iterator_valid_range(
    iterator_t t_first, iterator_t t_last, iteratortype_t t_type);
extern bool_t _iterator_same_elem_type(iterator_t t_first, iterator_t t_last);

extern _typestyle_t _iterator_get_typestyle(iterator_t t_iter);
extern const char* _iterator_get_typebasename(iterator_t t_iter);
extern _typeinfo_t* _iterator_get_typeinfo(iterator_t t_iter);
extern const char* _iterator_get_typename(iterator_t t_iter);
extern binary_function_t _iterator_get_typecopy(iterator_t t_iter);
extern size_t _iterator_get_typesize(iterator_t t_iter);
extern void* _iterator_allocate_init_elem(iterator_t t_iter);
extern void _iterator_deallocate_destroy_elem(iterator_t t_iter, void* pv_value);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_ITERATOR_PRIVATE_H */
/** eof **/

