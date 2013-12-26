/*
 *  The definition of list_t struct.
 *  Copyright (C)  2008 - 2014  Wangbo
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

#ifndef _CSTL_LIST_PRIVATE_H_
#define _CSTL_LIST_PRIVATE_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
#define _LIST_NODE_SIZE(typesize) ((typesize) + sizeof(_listnode_t) - sizeof(_byte_t))

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
    _byte_t              _pby_data[1];   /* the element value */
}_listnode_t;

typedef struct _taglist
{
    /* element type information */
    _typeinfo_t  _t_typeinfo;

    /* memory allocate */
    _alloc_t     _t_allocator;

    /* list core struct pointer */
    _listnode_t* _pt_node;
}list_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Create list container.
 * @param s_typename    type name.
 * @return list container pointer, if create list successfully, else return NULL.
 * @remarks if s_typename == NULL, the behavior is undefined. s_typename must be c builtin type, libcstl builtin type or
 *          user defined type, otherwise creation will be failure.
 */
extern list_t* _create_list(const char* s_typename);

/**
 * Create list container auxiliary function.
 * @param plist_list    list container.
 * @param s_typename    type name.
 * @return true if create list container successfully, otherwise return false.
 * @remarks if plist_list == NULL or s_typename == NULL, the behavior is undefined. s_typename must be c builtin type,
 *          libcstl builtin type or user defined type, otherwise creation will be failure.
 */
extern bool_t _create_list_auxiliary(list_t* plist_list, const char* s_typename);

/**
 * Initialize list with specified element.
 * @param plist_list   uninitialized list container.
 * @param t_count      element number.
 * @param ...          specificed element.
 * @return void
 * @remarks if plist_list == NULL, then the behavior is undefined. the type of specificed element and list element
 *          type must be same, otherwise the behavior is undefined. the first specificed element is in use, others are
 *          not in use. list container must be created by create_list, otherwise the behavior is undefined.
 */
extern void _list_init_elem(list_t* plist_list, size_t t_count, ...);

/**
 * Initialize list with variable argument list of specified element.
 * @param plist_list   uninitialized list container.
 * @param t_count      element number.
 * @param val_elemlist variable argument list of specificed element.
 * @return void
 * @remarks if plist_list == NULL, then the behavior is undefined. the type of specificed element and list element
 *          type must be same, otherwise the behavior is undefined. the first specificed element is in use, others are
 *          not in use. list container must be created by create_list, otherwise the behavior is undefined.
 */
extern void _list_init_elem_varg(list_t* plist_list, size_t t_count, va_list val_elemlist);

/**
 * Destroy list container auxiliary function.
 * @param plist_list   list container.
 * @return void.
 * @remarks if plist_list == NULL, then the behavior is undefined. list container must be initialized or created by
 *          create_list, otherwise the behavior is undefined.
 */
extern void _list_destroy_auxiliary(list_t* plist_list);

/**
 * Assign list with specificed element.
 * @param plist_list   list container.
 * @param t_count      element number.
 * @param ...          specificed element.
 * @return void.
 * @remarks if plist_list == NULL or list is uninitialized, then the behavior is undefined. the type of specificed
 *          element and list element type must be same, otherwise the behavior is undefined. the first specificed is
 *          in use, others are not in use.
 */
extern void _list_assign_elem(list_t* plist_list, size_t t_count, ...);

/**
 * Assign list with variable argument of specificed element.
 * @param plist_list   list container.
 * @param t_count      element number.
 * @param val_elemlist variable argumnet list of specificed element.
 * @return void.
 * @remarks if plist_list == NULL or list is uninitialized, then the behavior is undefined. the type of specificed
 *          element and list element type must be same, otherwise the behavior is undefined. the first specificed is
 *          in use, others are not in use.
 */
extern void _list_assign_elem_varg(list_t* plist_list, size_t t_count, va_list val_elemlist);

/**
 * Add specificed element at the end of list container. 
 * @param plist_list    list container.
 * @param val_elemlist  specificed element.
 * @return void.
 * @remarks if plist_list == NULL or list is uninitialized, then the behavior is undefined. the type of specificed
 *          element and list element type must be same, otherwise the behavior is undefined. the first specificed is
 *          in use, others are not in use.
 */
extern void _list_push_back(list_t* plist_list, ...);

/**
 * Add specificed element from variable argument list at the end of list container. 
 * @param plist_list    list container.
 * @param val_elemlist  variable argumnet list of specificed element.
 * @return void.
 * @remarks if plist_list == NULL or list is uninitialized, then the behavior is undefined. the type of specificed
 *          element and list element type must be same, otherwise the behavior is undefined. the first specificed is
 *          in use, others are not in use.
 */
extern void _list_push_back_varg(list_t* plist_list, va_list val_elemlist);

/**
 * Add specificed element at the begin of list container. 
 * @param plist_list    list container.
 * @param ...           specificed element.
 * @return void.
 * @remarks if plist_list == NULL or list is uninitialized, then the behavior is undefined. the type of specificed
 *          element and list element type must be same, otherwise the behavior is undefined. the first specificed is
 *          in use, others are not in use.
 */
extern void _list_push_front(list_t* plist_list, ...);

/**
 * Add specificed element from variable argument list at the begin of list container. 
 * @param plist_list    list container.
 * @param val_elemlist  variable argumnet list of specificed element.
 * @return void.
 * @remarks if plist_list == NULL or list is uninitialized, then the behavior is undefined. the type of specificed
 *          element and list element type must be same, otherwise the behavior is undefined. the first specificed is
 *          in use, others are not in use.
 */
extern void _list_push_front_varg(list_t* plist_list, va_list val_elemlist);

/**
 * Reset the size of list elements.
 * @param plist_list    list container.
 * @param t_resize      new size of list elements.
 * @param ...           specificed element.
 * @return void.
 * @remarks if plist_list == NULL or list is uninitialized, then the behavior is undefined. the type of specificed
 *          element and list element type must be same, otherwise the behavior is undefined. the first specificed is
 *          in use, others are not in use. if t_resize less than current list size, then erase elmement from the end.
 *          if t_resize greater than current list size, then append elements to the end, and the element is specificed
 *          element.
 */
extern void _list_resize_elem(list_t* plist_list, size_t t_resize, ...);

/**
 * Reset the size of list elements, and filled element is from variable argument list.
 * @param plist_list    list container.
 * @param t_resize      new size of list elements.
 * @param val_elemlist  variable argument list.
 * @return void.
 * @remarks if plist_list == NULL or list is uninitialized, then the behavior is undefined. the type of specificed
 *          element and list element type must be same, otherwise the behavior is undefined. the first specificed is
 *          in use, others are not in use. if t_resize less than current list size, then erase elmement from the end.
 *          if t_resize greater than current list size, then append elements to the end, and the element is from
 *          variable argument list.
 */
extern void _list_resize_elem_varg(list_t* plist_list, size_t t_resize, va_list val_elemlist);

/**
 * Remove specificed element from list container.
 * @param plist_list    list container.
 * @param ...           specificed element.
 * @return void.
 * @remarks if plist_list == NULL or list is uninitialized, then the behavior is undefined. the type of specificed
 *          element and list element type must be same, otherwise the behavior is undefined. the first specificed is
 *          in use, others are not in use. this function remove all element that equal to specificed, if no such element
 *          then does nothing.
 */
extern void _list_remove(list_t* plist_list, ...);

/**
 * Remove element that specificed by variable argument list from list container.
 * @param plist_list    list container.
 * @param val_elemlist  variable argument list.
 * @return void.
 * @remarks if plist_list == NULL or list is uninitialized, then the behavior is undefined. the type of specificed
 *          element and list element type must be same, otherwise the behavior is undefined. the first specificed is
 *          in use, others are not in use. this function remove all element that equal to specificed, if no such element
 *          then does nothing.
 */
extern void _list_remove_varg(list_t* plist_list, va_list val_elemlist);

/**
 * Insert multiple copys of element befor specificed position.
 * @param plist_list    list container.
 * @param it_pos        insert position.
 * @param t_count       element number.
 * @param ...           specificed element.
 * @return position refereced the first inserted elements.
 * @remarks if plist_list == NULL or list is uninitialized, then the behavior is undefined. the it_pos must be invalid
 *          iterator of list container, otherwise the behavior is undefined. the type of specificed element and list
 *          element type must be same, otherwise the behavior is undefined. the first specificed is in use, others are not
 *          in use.
 */
extern list_iterator_t _list_insert_n(list_t* plist_list, list_iterator_t it_pos, size_t t_count, ...);

/**
 * Insert multiple copys of element befor specificed position, the element is from variable argument list.
 * @param plist_list    list container.
 * @param it_pos        insert position.
 * @param t_count       element number.
 * @param val_elemlist  variable argument list.
 * @return position refereced the first inserted elements.
 * @remarks if plist_list == NULL or list is uninitialized, then the behavior is undefined. the it_pos must be invalid
 *          iterator of list container, otherwise the behavior is undefined. the type of specificed element and list
 *          element type must be same, otherwise the behavior is undefined. the first specificed is in use, others are not
 *          in use. the inserted element is from variable argument list.
 */
extern list_iterator_t _list_insert_n_varg(list_t* plist_list, list_iterator_t it_pos, size_t t_count, va_list val_elemlist);

/**
 * Initialize element with list element type auxiliary function.
 * @param plist_list    list container.
 * @param pv_elem       initialized element.
 * @return void.
 * @remarks if plist_list == NULL or pv_elem == NULL, then the behavior is undefined. plist_list must be initialized
 *          list container or created by create_list, otherwise the behavior is undefined.
 */
extern void _list_init_elem_auxiliary(list_t* plist_list, void* pv_elem);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_LIST_PRIVATE_H_ */
/** eof **/

