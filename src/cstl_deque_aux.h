/*
 *  The implement of deque auxiliary function.
 *  Copyright (C)  2008,2009,2010  Wangbo
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

#ifndef _CSTL_DEQUE_AUX_H
#define _CSTL_DEQUE_AUX_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
#define _DEQUE_MAP_COUNT                16
#define _DEQUE_MAP_GROW_STEP            8
#define _DEQUE_ELEM_COUNT               16

/* macros for type informations */
#define _GET_DEQUE_TYPE_SIZE(pt_deque)\
    ((pt_deque)->_t_typeinfo._pt_type->_t_typesize)
#define _GET_DEQUE_TYPE_NAME(pt_deque)\
    ((pt_deque)->_t_typeinfo._sz_typename)
#define _GET_DEQUE_TYPE_BASENAME(pt_deque)\
    ((pt_deque)->_t_typeinfo._pt_type->_sz_typename)
#define _GET_DEQUE_TYPE_INIT_FUNCTION(pt_deque)\
    ((pt_deque)->_t_typeinfo._pt_type->_t_typeinit)
#define _GET_DEQUE_TYPE_COPY_FUNCTION(pt_deque)\
    ((pt_deque)->_t_typeinfo._pt_type->_t_typecopy)
#define _GET_DEQUE_TYPE_LESS_FUNCTION(pt_deque)\
    ((pt_deque)->_t_typeinfo._pt_type->_t_typeless)
#define _GET_DEQUE_TYPE_DESTROY_FUNCTION(pt_deque)\
    ((pt_deque)->_t_typeinfo._pt_type->_t_typedestroy)
#define _GET_DEQUE_TYPE_STYLE(pt_deque)\
    ((pt_deque)->_t_typeinfo._t_style)

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
#ifndef NDEBUG
/*
 * Assert support.
 */
extern bool_t _deque_iterator_belong_to_deque(
    const deque_t* cpt_deque, deque_iterator_t t_iter);
extern bool_t _deque_same_deque_iterator_type(
    const deque_t* cpt_deque, deque_iterator_t t_iter);
#endif /* NDEBUG */
extern bool_t _deque_same_type(
    const deque_t* cpt_dequefirst, const deque_t* cpt_dequesecond);

/*
 * Expand deque_t.
 */
extern deque_iterator_t _expand_at_end(
    deque_t* pt_deque, size_t t_expandsize, deque_iterator_t* pt_pos);
extern deque_iterator_t _expand_at_begin(
    deque_t* pt_deque, size_t t_expandsize, deque_iterator_t* pt_pos);

/*
 * Shrink deque_t.
 */
extern void _shrink_at_end(deque_t* pt_deque, size_t t_shrinksize);
extern void _shrink_at_begin(deque_t* pt_deque, size_t t_shrinksize);

/*
 * Move element.
 */
extern deque_iterator_t _move_elem_to_end(
    deque_t* pt_deque, deque_iterator_t t_begin, 
    deque_iterator_t t_end, size_t t_movesize);
extern deque_iterator_t _move_elem_to_begin(
    deque_t* pt_deque, deque_iterator_t t_begin, 
    deque_iterator_t t_end, size_t t_movesize);

/*
 * Auxiliary.
 */
extern void _deque_get_varg_value_auxiliary(
    deque_t* pt_deque, va_list val_elemlist, void* pv_varg);
extern void _deque_destroy_varg_value_auxiliary(deque_t* pt_deque, void* pv_varg);
extern void _deque_init_elem_range_auxiliary(
    deque_t* pt_deque, deque_iterator_t t_begin, deque_iterator_t t_end);
extern void* _deque_iterator_get_pointer_auxiliary(iterator_t t_iter);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_DEQUE_AUX_H */
/** eof **/

