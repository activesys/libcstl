/*
 *  The implement of basic string auxiliary function.
 *  Copyright (C)  2008 - 2013  Wangbo
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

#ifndef _CSTL_BASIC_STRING_AUX_H_
#define _CSTL_BASIC_STRING_AUX_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/* macros for type informations */
#define _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string)             ((pt_basic_string)->_vec_base._t_typeinfo._pt_type->_t_typesize)
#define _GET_BASIC_STRING_TYPE_NAME(pt_basic_string)             ((pt_basic_string)->_vec_base._t_typeinfo._s_typename)
#define _GET_BASIC_STRING_TYPE_BASENAME(pt_basic_string)         ((pt_basic_string)->_vec_base._t_typeinfo._pt_type->_s_typename)
#define _GET_BASIC_STRING_TYPE_INIT_FUNCTION(pt_basic_string)    ((pt_basic_string)->_vec_base._t_typeinfo._pt_type->_t_typeinit)
#define _GET_BASIC_STRING_TYPE_COPY_FUNCTION(pt_basic_string)    ((pt_basic_string)->_vec_base._t_typeinfo._pt_type->_t_typecopy)
#define _GET_BASIC_STRING_TYPE_LESS_FUNCTION(pt_basic_string)    ((pt_basic_string)->_vec_base._t_typeinfo._pt_type->_t_typeless)
#define _GET_BASIC_STRING_TYPE_DESTROY_FUNCTION(pt_basic_string) ((pt_basic_string)->_vec_base._t_typeinfo._pt_type->_t_typedestroy)
#define _GET_BASIC_STRING_TYPE_STYLE(pt_basic_string)            ((pt_basic_string)->_vec_base._t_typeinfo._t_style)

/** data type declaration and struct, union, enum section **/
/**
 * This structure is representation of basic_string_t.
 * and basic_string_t look like this:
 *
 *                     _t_length;
 *                     _t_capacity;
 *                     _n_refcount;
 *   _pt_string -----> data
 */
typedef struct _tag_basic_string_rep
{
    size_t _t_length;
    size_t _t_capacity;
    int    _n_refcount;
}_basic_string_rep_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
#ifndef NDEBUG
/*
 * Assert support.
 */
extern bool_t _iterator_belong_to_basic_string(
    const basic_string_t* cpt_basic_string, basic_string_iterator_t t_iter);
/**
 * Test the type that saved in the basic_string container is same.
 * @param cpt_first     first basic_string.
 * @param cpt_second    second basic_string.
 * @return if the type is same, return true, else return false.
 * @remarks if cpt_first == NULL or cpt_second == NULL, the behavior is undefined. the two basic_string must be
 *          initialized or created by create_basic_string(), otherwise the behavior is undefined.
 */
extern bool_t _basic_string_same_type(const basic_string_t* cpt_first, const basic_string_t* cpt_second);
#endif /* NDEBUG */

/**
 * Get the value string length.
 * @param cpt_basic_string   basic_string container.
 * @param cpv_value_string   value string.
 * @return value string length.
 * @remarks if cpt_basic_string == NULL or cpv_valuestring == NULL, the behavior is undefined. the basic_string must be
 *          initialized or created by create_basic_string(), otherwise the behavior is undefine.
 */
extern size_t _basic_string_get_value_string_length(const basic_string_t* cpt_basic_string, const void* cpv_value_string);

/**
 * Obtain data from variable argument list, the data type and basic_string element data type are same.
 * @param pt_basic_string    basic_string container.
 * @param val_elemlist       variable argument list.
 * @param pv_varg            data buffer.
 * @return void.
 * @remarks if pvec_basic_string == NULL or pv_varg == NULL, then the behavior is undefined. pvec_basic_string must be initialized
 *          or created by create_basic_string(), otherwise the behavior is undefined.
 */
extern void _basic_string_get_varg_value_auxiliary(basic_string_t* pt_basic_string, va_list val_elemlist, void* pv_varg);

/**
 * Destroy data, the data type and basic_string element data type are same.
 * @param pt_basic_string    basic_string container.
 * @param pv_varg            data buffer.
 * @return void.
 * @remarks if pvec_basic_string == NULL or pv_varg == NULL, then the behavior is undefined. pvec_basic_string must be initialized
 *          or created by create_basic_string(), otherwise the behavior is undefined.
 */
extern void _basic_string_destroy_varg_value_auxiliary(basic_string_t* pt_basic_string, void* pv_varg);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_BASIC_STRING_AUX_H_ */
/** eof **/

