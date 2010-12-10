/*
 *  The definition of list_t struct.
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

#ifndef _CSTL_LIST_PRIVATE_H
#define _CSTL_LIST_PRIVATE_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
#define _LIST_NODE_SIZE(typesize) ((typesize) + sizeof(listnode_t) - 1)

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
    /* element type information */
    _typeinfo_t _t_typeinfo;

    /* memory allocate */
    _alloc_t    _t_allocater;

    /* list core struct pointer */
    listnode_t* _pt_node;
}list_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * Create and initialization operation functions.
 */
extern list_t* _create_list(const char* s_typename);
extern bool_t _create_list_auxiliary(list_t* pt_list, const char* s_typename);
extern void _list_init_elem(list_t* pt_list, size_t t_count, ...);
extern void _list_init_elem_varg(list_t* pt_list, size_t t_count, va_list val_elemlist);
extern void _list_destroy_auxiliary(list_t* pt_list);

/*
 * Assign operator functions.
 */
extern void _list_assign_elem(list_t* pt_list, size_t t_count, ...);
extern void _list_assign_elem_varg(list_t* pt_list, size_t t_count, va_list val_elemlist);

/*
 * Push element into list_t.
 */
extern void _list_push_back(list_t* pt_list, ...);
extern void _list_push_back_varg(list_t* pt_list, va_list val_elemlist);
extern void _list_push_front(list_t* pt_list, ...);
extern void _list_push_front_varg(list_t* pt_list, va_list val_elemlist);

/*
 * Resize operation functions.
 */
extern void _list_resize_elem(list_t* pt_list, size_t t_resize, ...);
extern void _list_resize_elem_varg(list_t* pt_list, size_t t_resize, va_list val_elemlist);

/*
 * Remove operation functions.
 */
extern void _list_remove(list_t* pt_list, ...);
extern void _list_remove_varg(list_t* pt_list, va_list val_elemlist);

/*
 * Insert operation functions.
 */
extern list_iterator_t _list_insert_n(
    list_t* pt_list, list_iterator_t t_pos, size_t t_count, ...);
extern list_iterator_t _list_insert_n_varg(
    list_t* pt_list, list_iterator_t t_pos, size_t t_count, va_list val_elemlist);

extern void _list_init_elem_auxiliary(list_t* pt_list, void* pv_value);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_LIST_PRIVATE_H */
/** eof **/

