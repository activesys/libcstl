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
#define _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string)             ((pt_basic_string)->_t_typeinfo._pt_type->_t_typesize)
#define _GET_BASIC_STRING_TYPE_NAME(pt_basic_string)             ((pt_basic_string)->_t_typeinfo._s_typename)
#define _GET_BASIC_STRING_TYPE_BASENAME(pt_basic_string)         ((pt_basic_string)->_t_typeinfo._pt_type->_s_typename)
#define _GET_BASIC_STRING_TYPE_INIT_FUNCTION(pt_basic_string)    ((pt_basic_string)->_t_typeinfo._pt_type->_t_typeinit)
#define _GET_BASIC_STRING_TYPE_COPY_FUNCTION(pt_basic_string)    ((pt_basic_string)->_t_typeinfo._pt_type->_t_typecopy)
#define _GET_BASIC_STRING_TYPE_LESS_FUNCTION(pt_basic_string)    ((pt_basic_string)->_t_typeinfo._pt_type->_t_typeless)
#define _GET_BASIC_STRING_TYPE_DESTROY_FUNCTION(pt_basic_string) ((pt_basic_string)->_t_typeinfo._pt_type->_t_typedestroy)
#define _GET_BASIC_STRING_TYPE_STYLE(pt_basic_string)            ((pt_basic_string)->_t_typeinfo._t_style)

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
#ifndef NDEBUG
/*
 * Assert support.
 */
/**
 * Test iterator referenced data is within the basic_string.
 * @param cpt_basic_string point to basic_string container.
 * @param it_iter basic_string iterator.
 * @return if iterator referenced is within the basic_string, then return true, otherwise return false.
 * @remarks if cpt_basic_string == NULL, then the behavior is undefined, the it_iter must be valie basic_string
 *          iterator and must belong to basic_string, otherwist the behavior is undefined. 
 */
extern bool_t _basic_string_iterator_belong_to_basic_string(
    const basic_string_t* cpt_basic_string, basic_string_iterator_t it_iter);

/**
 * Test the type that saved in the basic_string container and referenced by it_iter are same.
 * @param cpt_basic_string  basic_string container.
 * @param it_iter           basic_string iterator.
 * @return if the type is same, return true, else return false.
 * @remarks if cpt_basic_string == NULL, then the behavior is undefined.
 */
extern bool_t _basic_string_same_iterator_type(const basic_string_t* cpt_basic_string, iterator_t it_iter);

/**
 * Test basic_string_t is created by create_basic_string.
 * @param cpt_basic_string  basic_string_t pointer.
 * @return if basic_string is created by create_basic_string, then return true, else return false.
 * @remarks if cpt_basic_string == NULL, then the behavior is undefined.
 */
extern bool_t _basic_string_is_created(const basic_string_t* cpt_basic_string);

/**
 * Test basic_string is initialized by basic_string initialization functions.
 * @param cpt_basic_string  basic_string container.
 * @return if basic_string is initialized by basic_string initialization functions, then return true, else return false.
 * @remarks if cpt_basic_string == NULL, then the behavior is undefined.
 */
extern bool_t _basic_string_is_inited(const basic_string_t* cpt_basic_string);

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
 * @remarks if cpt_basic_string == NULL or cpv_value_string == NULL, the behavior is undefined. the basic_string must be
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

/**
 * Initialize data within string according to data type of basic_string.
 * @param pt_basic_string   basic_string.
 * @param pby_string        string.
 * @param t_len          string length.
 * @return void.
 * @remarks pt_basic_string must be initialized or created by create_basic_string().
 */
extern void _basic_string_init_elem_range_auxiliary(basic_string_t* pt_basic_string, _byte_t* pby_string, size_t t_len);

/**
 * Detach this basic_string from sharable string.
 * @param pt_basic_string   basic_string.
 * @return void.
 * @remarks pt_basic_string must be initialized.
 */
extern void _basic_string_detach(basic_string_t* pt_basic_string);

/**
 * Check whether the basic_string_t is shared.
 * @param cpt_basic_string   basic_string.
 * @return bool_t.
 * @remarks cpt_basic_string must be initialized.
 */
extern bool_t _basic_string_is_shared(const basic_string_t* cpt_basic_string);

/**
 * Clone representation.
 * @param cpt_basic_string   basic_string.
 * @param t_addsize          additional size.
 * @return new rep that cloned from cpt_basic_string.
 * @remarks cpt_basic_string must not be NULL.
 */
extern _basic_string_rep_t* _basic_string_clone_representation(const basic_string_t* cpt_basic_string, size_t t_addsize);

/**
 * Copy elements from source.
 * @param cpt_basic_string  basic_string container.
 * @param pby_dest          destination pointer.
 * @param pby_src/cpv_value_string/it_begin/it_end/val_elemlist
 *                          source.
 * @param t_len/t_count     element count.
 * @return void.
 * @remarks cpt_basic_string, destination and source pointer must be not NULL, and the destination pointer must be initialized.
 */
extern void _basic_string_copy_substring_auxiliary(
    const basic_string_t* cpt_basic_string, _byte_t* pby_dest, _byte_t* pby_src, size_t t_len);
extern void _basic_string_copy_subcstr_auxiliary(
    const basic_string_t* cpt_basic_string, _byte_t* pby_dest, const void* cpv_value_string, size_t t_len);
extern void _basic_string_copy_range_auxiliary(
    const basic_string_t* cpt_basic_string, _byte_t* pby_dest, iterator_t it_begin, iterator_t it_end);
extern void _basic_string_copy_elem_auxiliary(
    const basic_string_t* cpt_basic_string, _byte_t* pby_dest, size_t t_count, va_list val_elemlist);
extern void _basic_string_copy_substring_backward_auxiliary(
    const basic_string_t* cpt_basic_string, _byte_t* pby_dest, _byte_t* pby_src, size_t t_len);

/**
 * Destroy elements in substring.
 * @param cpt_basic_string  basic_string container.
 * @param pby_del           destination pointer.
 * @param t_len             element count.
 * @return void.
 * @remarks cpt_basic_string, destination  pointer must be not NULL.
 */
extern void _basic_string_destroy_elem_range_auxiliary(
    const basic_string_t* cpt_basic_string, _byte_t* pby_del, size_t t_len);

/**
 * Preparation for replace.
 * @param pt_basic_string   basic string container.
 * @param t_pos             position.
 * @param t_len             length.
 * @param t_replacelen      replace length.
 * @return void.
 * @remarks pt_basic_string must be not NULL.
 */
extern void _basic_string_replace_preparation(
    basic_string_t* pt_basic_string, size_t t_pos, size_t t_len, size_t t_replacelen);

/**
 * Find element in value string/basic_string.
 * @param cpt_basic_string  basic string container.
 * @param t_pos             position.
 * @param cpv_value_string  value string.
 * @param cpt_find          basic_string.
 * @param t_len             length.
 * @return true if find, otherwise return false.
 * @remarks cpt_basic_string and cpv_value_string must be not NULL.
 */
extern bool_t _basic_string_value_string_find(
    const basic_string_t* cpt_basic_string, size_t t_pos, const void* cpv_value_string, size_t t_len);
extern bool_t _basic_string_substring_find(
    const basic_string_t* cpt_basic_string, size_t t_pos, const basic_string_t* cpt_find);

/**
 * Create basic_string representation and initialize it.
 * @param cpt_basic_string  basic string container.
 * @param t_len             length.
 * @param t_newcapacity     new capacity.
 * @param t_oldcapacity     old capacity.
 * @return representation.
 * @remarks cpt_basic_string must be not NULL.
 */
extern _basic_string_rep_t* _basic_string_rep_construct(
    const basic_string_t* cpt_basic_string, size_t t_len, size_t t_newcapacity, size_t t_oldcapacity);

/**
 * Copy element with terminator.
 * @param cpt_basic_string  basic string container.
 * @param pby_dest          destination.
 * @param pby_src           source.
 * @param pby_terminator    terminator.
 * @return void.
 * @remarks cpt_basic_string must be not NULL.
 */
extern void _basic_string_copy_elem_with_terminator(
    const basic_string_t* cpt_basic_string, _byte_t* pby_dest, _byte_t* pby_src, _byte_t* pby_terminator);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_BASIC_STRING_AUX_H_ */
/** eof **/

