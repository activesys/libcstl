/*
 *  The definition of deque_t struct.
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

#ifndef _CSTL_DEQUE_PRIVATE_H
#define _CSTL_DEQUE_PRIVATE_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
/* deque struct */
typedef char**  _mappointer_t;
typedef struct _tagdeque
{
    /* element type information */
    _typeinfo_t      _t_typeinfo;

    /* memory allocate */
    _alloc_t         _t_allocater;

    /* the element manager map and size */
    _mappointer_t    _ppc_map;
    size_t           _t_mapsize;
    /* the first element */
    deque_iterator_t _t_start;
    /* the element after the last element */
    deque_iterator_t _t_finish;
}deque_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * Create and initialization operation functions.
 */
extern deque_t* _create_deque(const char* s_typename);
extern bool_t _create_deque_auxiliary(deque_t* pt_deque, const char* s_typename);
extern void _deque_init_elem(deque_t* pt_deque, size_t t_count, ...);
extern void _deque_init_elem_varg(
    deque_t* pt_deque, size_t t_count, va_list val_elemlist);
extern void _deque_destroy_auxiliary(deque_t* pt_deque);

/*
 * Assign operator functions.
 */
extern void _deque_assign_elem(deque_t* pt_deque, size_t t_count, ...);
extern void _deque_assign_elem_varg(
    deque_t* pt_deque, size_t t_count, va_list val_elemlist);

/*
 * Push element into deque_t.
 */
extern void _deque_push_back(deque_t* pt_deque, ...);
extern void _deque_push_back_varg(deque_t* pt_deque, va_list val_elemlist);
extern void _deque_push_front(deque_t* pt_deque, ...);
extern void _deque_push_front_varg(deque_t* pt_deque, va_list val_elemlist);

/*
 * Resize operation functions.
 */
extern void _deque_resize_elem(deque_t* pt_deque, size_t t_resize, ...);
extern void _deque_resize_elem_varg(
    deque_t* pt_deque, size_t t_resize, va_list val_elemlist);

/*
 * Insert operation functions.
 */
extern deque_iterator_t _deque_insert_n(
    deque_t* pt_deque, deque_iterator_t t_pos, size_t t_count, ...);
extern deque_iterator_t _deque_insert_n_varg(
    deque_t* pt_deque, deque_iterator_t t_pos, size_t t_count, va_list val_elemlist);

extern void _deque_init_elem_auxiliary(deque_t* pt_deque, void* pv_value);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_DEQUE_PRIVATE_H */
/** eof **/

