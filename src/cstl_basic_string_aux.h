/*
 *  The implement of basic string auxiliary function.
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

#ifndef _CSTL_BASIC_STRING_AUX_H
#define _CSTL_BASIC_STRING_AUX_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/* macros for type informations */
#define _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string)\
    ((pt_basic_string)->_t_vector._t_typeinfo._pt_type->_t_typesize)
#define _GET_BASIC_STRING_TYPE_NAME(pt_basic_string)\
    ((pt_basic_string)->_t_vector._t_typeinfo._sz_typename)
#define _GET_BASIC_STRING_TYPE_BASENAME(pt_basic_string)\
    ((pt_basic_string)->_t_vector._t_typeinfo._pt_type->_sz_typename)
#define _GET_BASIC_STRING_TYPE_INIT_FUNCTION(pt_basic_string)\
    ((pt_basic_string)->_t_vector._t_typeinfo._pt_type->_t_typeinit)
#define _GET_BASIC_STRING_TYPE_COPY_FUNCTION(pt_basic_string)\
    ((pt_basic_string)->_t_vector._t_typeinfo._pt_type->_t_typecopy)
#define _GET_BASIC_STRING_TYPE_LESS_FUNCTION(pt_basic_string)\
    ((pt_basic_string)->_t_vector._t_typeinfo._pt_type->_t_typeless)
#define _GET_BASIC_STRING_TYPE_DESTROY_FUNCTION(pt_basic_string)\
    ((pt_basic_string)->_t_vector._t_typeinfo._pt_type->_t_typedestroy)
#define _GET_BASIC_STRING_TYPE_STYLE(pt_basic_string)\
    ((pt_basic_string)->_t_vector._t_typeinfo._t_style)

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
#ifndef NDEBUG
/*
 * Assert support.
 */
extern bool_t _iterator_belong_to_basic_string(
    const basic_string_t* cpt_basic_string, basic_string_iterator_t t_iter);
extern bool_t _basic_string_same_type(
    const basic_string_t* cpt_basic_stringfirst, 
    const basic_string_t* cpt_basic_stringsecond);
#endif /* NDEBUG */

/*
 * Get the value string length.
 */
extern size_t _get_valuestring_len(
    const basic_string_t* cpt_basic_string, const void* cpv_valuestring);

extern void _basic_string_get_varg_value_auxiliary(
    basic_string_t* pt_basic_string, va_list val_elemlist, void* pv_varg);
extern void _basic_string_destroy_varg_value_auxiliary(
    basic_string_t* pt_basic_string, void* pv_varg);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_BASIC_STRING_AUX_H */
/** eof **/

