/*
 *  The definition of deque_t struct.
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
    /* element identify */
    size_t           _t_typesize;                          /* element size */
    char             _sz_typename[_ELEM_TYPE_NAME_SIZE+1]; /* element name */

    /* memory allocate */
    alloc_t          _t_allocater;

    /* the element manager map and size */
    _mappointer_t    _ppc_map;
    size_t           _t_mapsize;
    /* the first element */
    deque_iterator_t _t_start;
    /* the element after the last element */
    deque_iterator_t _t_finish;

    /* 
     * the compare function :
     * < 0  : element first < element second.
     * == 0 : element first == element second.
     * > 0  : element first > element second. 
     */
    int (*_pfun_cmp)(const void*, const void*);
}deque_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _create_deque
 *        Parameters: in) t_typesize: size_t
 *                          the element type size.
 *                    in) s_typename: const char*
 *                          the element type name.
 *           Returns: deque_t
 *                          new deque.
 *       Description: create the new deque.
 *
 * ----------------------------------------------------------------------------
 */
extern deque_t _create_deque(size_t t_typesize, const char* s_typename);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _deque_init_elem
 *        Parameters: in) pt_deque: deque_t*
 *                    in) t_count: size_t
 *                          element count.
 *                    in) ...
 *                          element list.
 *           Returns: void
 *       Description: initialize the deque.
 *
 * ----------------------------------------------------------------------------
 */
extern void _deque_init_elem(deque_t* pt_deque, size_t t_count, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _deque_init_elem_varg
 *        Parameters: in) pt_deque: deque_t*
 *                    in) t_count: size_t
 *                          element count.
 *                    in) val_elemlist: va_list
 *                          element list.
 *           Returns: void
 *       Description: initialize the deque.
 *
 * ----------------------------------------------------------------------------
 */
extern void _deque_init_elem_varg(
    deque_t* pt_deque, size_t t_count, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _deque_assign_elem
 *        Parameters: in) pt_deque: deque_t*
 *                          the deque for assign.
 *                    in) t_count: size_t
 *                          the element count.
 *                    in) ...
 *                          the element.
 *           Returns: void
 *       Description: assign n_elemcount copys of element.
 *
 * ----------------------------------------------------------------------------
 */
extern void _deque_assign_elem(deque_t* pt_deque, size_t t_count, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _deque_assign_elem_varg
 *        Parameters: in) pt_deque: deque_t*
 *                          the deque for assign.
 *                    in) t_count: size_t
 *                          the element count.
 *                    in) val_elemlist: va_list
 *                          the element list.
 *           Returns: void
 *       Description: assign n_elemcount copys of element.
 *
 * ----------------------------------------------------------------------------
 */
extern void _deque_assign_elem_varg(
    deque_t* pt_deque, size_t t_count, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _deque_push_back
 *        Parameters: in) pt_deque: deque_t*
 *                          the deque.
 *                    in) ...
 *                          the element.
 *           Returns: void
 *       Description: append a copy of element at the end.
 *
 * ----------------------------------------------------------------------------
 */
extern void _deque_push_back(deque_t* pt_deque, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _deque_push_back
 *        Parameters: in) pt_deque: deque_t*
 *                          the deque.
 *                    in) val_elemlist: va_list
 *                          the element.
 *           Returns: void
 *       Description: append a copy of element at the end.
 *
 * ----------------------------------------------------------------------------
 */
extern void _deque_push_back_varg(deque_t* pt_deque, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _deque_push_front
 *        Parameters: in) pt_deque: deque_t*
 *                          the deque.
 *                    in) ...
 *                          the element.
 *           Returns: void
 *       Description: append a copy of element at the front.
 *
 * ----------------------------------------------------------------------------
 */
extern void _deque_push_front(deque_t* pt_deque, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _deque_push_front
 *        Parameters: in) pt_deque: deque_t*
 *                          the deque.
 *                    in) val_elemlist: va_list
 *                          the element.
 *           Returns: void
 *       Description: append a copy of element at the front.
 *
 * ----------------------------------------------------------------------------
 */
extern void _deque_push_front_varg(deque_t* pt_deque, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _deque_resize_elem
 *        Parameters: in) pt_deque: deque_t*
 *                          the deque.
 *                    in) t_resize: size_t
 *                          the new size of deque.
 *                    in) ...
 *                          the default element.
 *           Returns: void
 *       Description: change the number of elements to t_resize, if the size
 *                    grows new element create with the default element.
 *
 * ----------------------------------------------------------------------------
 */
extern void _deque_resize_elem(deque_t* pt_deque, size_t t_resize, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _deque_resize_elem_varg
 *        Parameters: in) pt_deque: deque_t*
 *                          the deque.
 *                    in) t_resize: size_t
 *                          the new size of deque.
 *                    in) val_elemlist: va_list
 *                          the default element.
 *           Returns: void
 *       Description: change the number of elements to t_resize, if the size
 *                    grows new element create with the default element.
 *
 * ----------------------------------------------------------------------------
 */
extern void _deque_resize_elem_varg(
    deque_t* pt_deque, size_t t_resize, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _deque_insert_n
 *        Parameters: in) pt_deque: deque_t*
 *                          the deque.
 *                    in) t_pos: deque_iterator_t
 *                          the insert position.
 *                    in) t_count: size_t
 *                          the element count.
 *                    in) ...
 *                          the element.
 *           Returns: deque_iterator_t
 *       Description: insert at iterator position t_pos n_elemcount copys of
 *                    element and return nothing.
 *
 * ----------------------------------------------------------------------------
 */
extern deque_iterator_t _deque_insert_n(
    deque_t* pt_deque, deque_iterator_t t_pos, size_t t_count, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _deque_insert_n_varg
 *        Parameters: in) pt_deque: deque_t*
 *                          the deque.
 *                    in) t_pos: deque_iterator_t
 *                          the insert position.
 *                    in) t_count: size_t
 *                          the element count.
 *                    in) val_elemlist: va_list
 *                          the element list.
 *           Returns: deque_iterator_t
 *       Description: insert at iterator position t_pos n_elemcount copys of
 *                    element and return nothing.
 *
 * ----------------------------------------------------------------------------
 */
extern deque_iterator_t _deque_insert_n_varg(
    deque_t* pt_deque, 
    deque_iterator_t t_pos, 
    size_t t_count, va_list val_elemlist);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_DEQUE_PRIVATE_H */
/** eof **/

