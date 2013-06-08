/*
 *  The implement of list auxiliary function.
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

#ifndef _CSTL_LIST_AUX_H_
#define _CSTL_LIST_AUX_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/* macros for type informations */
#define _GET_LIST_TYPE_SIZE(plist_list)             ((plist_list)->_t_typeinfo._pt_type->_t_typesize)
#define _GET_LIST_TYPE_NAME(plist_list)             ((plist_list)->_t_typeinfo._s_typename)
#define _GET_LIST_TYPE_BASENAME(plist_list)         ((plist_list)->_t_typeinfo._pt_type->_s_typename)
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
 * Test the type that saved in the list container and referenced by it_iter are same.
 * @param cplist_list     list container.
 * @param it_iter         iterator.
 * @return if the type is same, return true, else return false.
 * @remarks if cplist_first == NULL or it_iter is invalid iterator, then the behavior is undefined.
 */
extern bool_t _list_same_iterator_type(const list_t* cplist_list, iterator_t it_iter);

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
extern void _list_get_varg_value_auxiliary(list_t* plist_list, va_list val_elemlist, _listnode_t* pt_node);

/**
 * Destroy data, the data type and list element data type are same.
 * @param plist_list    list container.
 * @param pt_node       data buffer.
 * @return void.
 * @remarks if plist_list == NULL or pt_node == NULL, then the behavior is undefined. plist_list must be initialized
 *          or created by create_list(), otherwise the behavior is undefined.
 */
extern void _list_destroy_varg_value_auxiliary(list_t* pt_list, _listnode_t* pt_node);

/**
 * Initialize list node auxiliary function.
 * @param plist_list    list container.
 * @param pt_node       data buffer.
 * @return void.
 * @remarks if plist_list == NULL or pt_node == NULL, then the behavior is undefined. plist_list must be initialized
 *          or created by create_list(), otherwise the behavior is undefined.
 */
extern void _list_init_node_auxiliary(list_t* plist_list, _listnode_t* pt_node);

/**
 * Transfer the range [it_begin, it_end) to position it_pos.
 * @param it_pos      insert data position.
 * @param it_begin    range start.
 * @param it_end      range end.
 * @return void.
 * @remarks it_pos, it_begin, it_end must be valid list iterator, otherwise the behavior is undefined. [it_begin, it_end)
 *          must be valid list data range, otherwise the beahvior is undefined. it_pos and [it_begin, it_end) may belong
 *          to same list container, but if it_pos belongs to (it_begin, it_end), then the behavior is undefined. if
 *          it_pos == it_begin or it_pos == it_end or it_begin == it_end, then the function does nothing.
 */
extern void _list_transfer(list_iterator_t it_pos, list_iterator_t it_begin, list_iterator_t it_end);

/**
 * Sort the range [pt_first, pt_last] use the quick sort algorithm.
 * @param plist_list           list container.
 * @param pt_first             first node.
 * @param pt_last              last node.
 * @param bfun_less          sorting rules.
 * @return void.
 * @remarks if plist_list == NULL or pt_first == NULL or pt_last == NULL, then the behavior is undefined. the list must
 *          be initialized, otherwise the behavior is undefined. pt_first and pt_last must belong to plist_list, and
 *          range [pt_first, pt_last] must be valid range, otherwise the behavior is undefined. if bfun_less == NULL,
 *          then use default compare function.
 */
extern void _list_quick_sort(list_t* plist_list, _listnode_t* pt_first, _listnode_t* pt_last, bfun_t bfun_less);

/**
 * Swap the two node content and don't change the pointer.
 * @param ppt_first    first list pointer.
 * @param ppt_second   second list pointer.
 * @return void.
 * @remarks if ppt_first == NULL or *ppt_first == NULL or ppt_second == NULL or *ppt_second == NULL, then the behavior is
 *          undefined.
 */
extern void _list_swap_node(_listnode_t** ppt_first, _listnode_t** ppt_second);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_LIST_AUX_H_ */
/** eof **/

