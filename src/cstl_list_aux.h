/*
 *  The implement of list auxiliary function.
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

#ifndef _CSTL_LIST_AUX_H
#define _CSTL_LIST_AUX_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/* macros for type informations */
#define _GET_LIST_TYPE_SIZE(plist_list)             ((plist_list)->_t_typeinfo._pt_type->_t_typesize)
#define _GET_LIST_TYPE_NAME(plist_list)             ((plist_list)->_t_typeinfo._sz_typename)
#define _GET_LIST_TYPE_BASENAME(plist_list)         ((plist_list)->_t_typeinfo._pt_type->_sz_typename)
#define _GET_LIST_TYPE_INIT_FUNCTION(plist_list)    ((plist_list)->_t_typeinfo._pt_type->_t_typeinit)
#define _GET_LIST_TYPE_COPY_FUNCTION(plist_list)    ((plist_list)->_t_typeinfo._pt_type->_t_typecopy)
#define _GET_LIST_TYPE_LESS_FUNCTION(plist_list)    ((plist_list)->_t_typeinfo._pt_type->_t_typeless)
#define _GET_LIST_TYPE_DESTROY_FUNCTION(plist_list) ((plist_list)->_t_typeinfo._pt_type->_t_typedestroy)
#define _GET_LIST_TYPE_STYLE(plist_list)            ((plist_list)->_t_typeinfo._t_style)

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
#ifndef NDEBUG
/**
 * Test iterator referenced data is within the list.
 * @param cplist_list     point to list container.
 * @param it_iter         list iterator.
 * @return if iterator referenced is within the list, then return true, otherwise return false.
 * @remarks if cplist_list == NULL, then the behavior is undefined, the it_iter must be valie list iterator and
 *          must belong to list, otherwist the behavior is undefined. 
 */
extern bool_t _list_iterator_belong_to_list(const list_t* cplist_list, list_iterator_t it_iter);

/**
 * Test the type that saved in the list container and referenced by it_iter are same.
 * @param cplist_list     list container.
 * @param it_iter         list iterator.
 * @return if the type is same, return true, else return false.
 * @remarks if cplist_first == NULL or it_iter is not list iterator, then the behavior is undefined.
 */
extern bool_t _list_same_list_iterator_type(const list_t* cplist_list, list_iterator_t it_iter);

/**
 * Test list is created by create_list.
 * @param cplist_list  list container.
 * @return if list is created by create_list, then return true, else return false.
 * @remarks if cplist_list == NULL, then the behavior is undefined.
 */
extern bool_t _list_is_created(const list_t* cplist_list);

/**
 * Test list is initialized.
 * @param cplist_list  list container.
 * @return if list is initialized, then return true, else return false.
 * @remarks if cplist_list == NULL, then the behavior is undefined.
 */
extern bool_t _list_is_inited(const list_t* cplist_list);
#endif /* NDEBUG */

/**
 * Test the type that saved in the list container is same.
 * @param cplist_first    first list.
 * @param cplist_second   second list.
 * @return if the type is same, return true, else return false.
 * @remarks if cplist_first == NULL or cplist_second == NULL, the behavior is undefined. the two list must be
 *          initialized or created by create_list(), otherwise the behavior is undefined.
 */
extern bool_t _list_same_type(const list_t* cplist_first, const list_t* cplist_second);

/**
 * Obtain data from variable argument list, the data type and list element data type are same.
 * @param plist_list     list container.
 * @param val_elemlist   variable argument list.
 * @param pt_node        data buffer.
 * @return void.
 * @remarks if plist_list == NULL or pt_node == NULL, then the behavior is undefined. plist_list must be initialized
 *          or created by create_list(), otherwise the behavior is undefined.
 */
extern void _list_get_varg_value_auxiliary(list_t* plist_list, va_list val_elemlist, listnode_t* pt_node);

/**
 * Destroy data, the data type and list element data type are same.
 * @param plist_list    list container.
 * @param pt_node       data buffer.
 * @return void.
 * @remarks if plist_list == NULL or pt_node == NULL, then the behavior is undefined. plist_list must be initialized
 *          or created by create_list(), otherwise the behavior is undefined.
 */
extern void _list_destroy_varg_value_auxiliary(list_t* pt_list, listnode_t* pt_node);

/**
 * Initialize list node auxiliary function.
 * @param plist_list    list container.
 * @param pt_node       data buffer.
 * @return void.
 * @remarks if plist_list == NULL or pt_node == NULL, then the behavior is undefined. plist_list must be initialized
 *          or created by create_list(), otherwise the behavior is undefined.
 */
extern void _list_init_node_auxiliary(list_t* plist_list, listnode_t* pt_node);

/*
 * Transfer the range [t_begin, t_end) to position.
 */
extern void _transfer(
    list_iterator_t t_pos, list_iterator_t t_begin, list_iterator_t t_end);

/*
 * Sort the range (t_beforefirstpos, t_afterlastpos) use the quick sort algorithm.
 */
extern void _quick_sort(
    list_iterator_t t_beforefirstpos, list_iterator_t t_afterlastpos,
    binary_function_t t_binary_op);

/*
 * Swap the two node content and don't change the pointer.
 */
extern void _swap_node(listnode_t** ppt_first, listnode_t** ppt_second);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_LIST_AUX_H */
/** eof **/

