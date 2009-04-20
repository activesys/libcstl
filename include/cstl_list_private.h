/*
 *  The definition of list_t struct.
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
 *  Author Email: activesys.wb@gmail.com
 *                activesys@sina.com.cn
 */

#ifndef _CSTL_LIST_PRIVATE_H
#define _CSTL_LIST_PRIVATE_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
/*
 * +----------------+
 * | previous node  |
 * +----------------+
 * | next node      |
 * +----------------+
 * | data  ...      |
 * |     . . .      |
 * +----------------+
 */
typedef struct _taglistnode
{
    struct _taglistnode* _pt_prev;
    struct _taglistnode* _pt_next;
    char                 _pc_data[1];   /* the element value */
}listnode_t;

typedef struct _taglist
{
    /* element identify */
    size_t          _t_typesize;                          /* element size */
    char            _sz_typename[_ELEM_TYPE_NAME_SIZE+1]; /* element name */

    /* memory allocate */
    alloc_t         _t_allocater;

    /* list core struct pointer */
    listnode_t*     _pt_node;

    /* 
     * the compare function :
     * < 0  : element first < element second.
     * == 0 : element first == element second.
     * > 0  : element first > element second. 
     */
    int (*_pfun_cmp)(const void*, const void*);
}list_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _create_list
 *        Parameters: in) t_typesize: size_t
 *                          the element type size.
 *                    in) s_typename: const char*
 *                          the element type name.
 *           Returns: list_t
 *                          new list.
 *       Description: create the new list.
 *
 * ----------------------------------------------------------------------------
 */
extern list_t _create_list(size_t t_typesize, const char* s_typename);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _list_init_elem
 *        Parameters: in) pt_list: list_t*
 *                    in) t_count: size_t
 *                          element count.
 *                    in) ...
 *                          element list.
 *           Returns: void
 *       Description: initialize the list.
 *
 * ----------------------------------------------------------------------------
 */
extern void _list_init_elem(list_t* pt_list, size_t t_count, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _list_init_elem_varg
 *        Parameters: in) pt_list: list_t*
 *                    in) t_count: size_t
 *                          element count.
 *                    in) val_elemlist: va_list
 *                          element list.
 *           Returns: void
 *       Description: initialize the list.
 *
 * ----------------------------------------------------------------------------
 */
extern void _list_init_elem_varg(
    list_t* pt_list, size_t t_count, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _list_assign_elem
 *        Parameters: in) pt_list: list_t*
 *                          the list for assign.
 *                    in) t_count: size_t
 *                          the element count.
 *                    in) ...
 *                          the element list.
 *           Returns: void
 *       Description: assign n_elemcount copys of element.
 *
 * ----------------------------------------------------------------------------
 */
extern void _list_assign_elem(list_t* pt_list, size_t t_count, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _list_assign_elem_varg
 *        Parameters: in) pt_list: list_t*
 *                          the list for assign.
 *                    in) t_count: size_t
 *                          the element count.
 *                    in) val_elemlist: va_list
 *                          the element list.
 *           Returns: void
 *       Description: assign n_elemcount copys of element.
 *
 * ----------------------------------------------------------------------------
 */
extern void _list_assign_elem_varg(
    list_t* pt_list, size_t t_count, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _list_push_back
 *        Parameters: in) pt_list: list_t*
 *                          the list.
 *                    in) ...
 *                          the element.
 *           Returns: void
 *       Description: append a copy of element at the end.
 *
 * ----------------------------------------------------------------------------
 */
extern void _list_push_back(list_t* pt_list, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _list_push_back_varg
 *        Parameters: in) pt_list: list_t*
 *                          the list.
 *                    in) val_elemlist: va_list
 *                          the element.
 *           Returns: void
 *       Description: append a copy of element at the end.
 *
 * ----------------------------------------------------------------------------
 */
extern void _list_push_back_varg(list_t* pt_list, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _list_push_front
 *        Parameters: in) pt_list: list_t*
 *                          the list.
 *                    in) ...
 *                          the element.
 *           Returns: void
 *       Description: append a copy of element at the front.
 *
 * ----------------------------------------------------------------------------
 */
extern void _list_push_front(list_t* pt_list, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _list_push_front_varg
 *        Parameters: in) pt_list: list_t*
 *                          the list.
 *                    in) val_elemlist: va_list
 *                          the element.
 *           Returns: void
 *       Description: append a copy of element at the front.
 *
 * ----------------------------------------------------------------------------
 */
extern void _list_push_front_varg(list_t* pt_list, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _list_resize_elem
 *        Parameters: in) pt_list: list_t*
 *                          the list.
 *                    in) t_resize: size_t
 *                          the new size of list.
 *                    in) ...
 *                          the default element.
 *           Returns: void
 *       Description: change the number of elements to t_resize, if the size
 *                    grows new element create with the default element.
 *
 * ----------------------------------------------------------------------------
 */
extern void _list_resize_elem(list_t* pt_list, size_t t_resize, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _list_resize_elem_varg
 *        Parameters: in) pt_list: list_t*
 *                          the list.
 *                    in) t_resize: size_t
 *                          the new size of list.
 *                    in) val_elemlist: va_list
 *                          the default element.
 *           Returns: void
 *       Description: change the number of elements to t_resize, if the size
 *                    grows new element create with the default element.
 *
 * ----------------------------------------------------------------------------
 */
extern void _list_resize_elem_varg(
    list_t* pt_list, size_t t_resize, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _list_remove
 *        Parameters: in) pt_list: list_t*
 *                          the list.
 *                    in) ...
 *                          the element.
 *           Returns: void
 *       Description: remove all elements with the element value.
 *
 * ----------------------------------------------------------------------------
 */
extern void _list_remove(list_t* pt_list, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _list_remove_varg
 *        Parameters: in) pt_list: list_t*
 *                          the list.
 *                    in) val_elemlist: va_list
 *                          the element.
 *           Returns: void
 *       Description: remove all elements with the element value.
 *
 * ----------------------------------------------------------------------------
 */
extern void _list_remove_varg(list_t* pt_list, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _list_insert_n
 *        Parameters: in) pt_list: list_t*
 *                          the list.
 *                    in) t_pos: list_iterator_t
 *                          the insert position.
 *                    in) t_count: size_t
 *                          the element count.
 *                    in) ...
 *                          the element.
 *           Returns: void
 *       Description: insert at iterator position t_pos n_elemcount copys of
 *                    element and return nothing.
 *
 * ----------------------------------------------------------------------------
 */
extern list_iterator_t _list_insert_n(
    list_t* pt_list, list_iterator_t t_pos, size_t t_count, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _list_insert_n_varg
 *        Parameters: in) pt_list: list_t*
 *                          the list.
 *                    in) t_pos: list_iterator_t
 *                          the insert position.
 *                    in) t_count: size_t
 *                          the element count.
 *                    in) val_elemlist: va_list
 *                          the element list.
 *           Returns: void
 *       Description: insert at iterator position t_pos n_elemcount copys of
 *                    element and return nothing.
 *
 * ----------------------------------------------------------------------------
 */
extern list_iterator_t _list_insert_n_varg(
    list_t* pt_list, list_iterator_t t_pos, size_t t_count, va_list val_elemlist);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_LIST_PRIVATE_H */
/** eof **/

