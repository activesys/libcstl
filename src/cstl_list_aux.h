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
#define _GET_LIST_TYPE_SIZE(pt_list)\
    ((pt_list)->_t_typeinfo._pt_type->_t_typesize)
#define _GET_LIST_TYPE_NAME(pt_list)\
    ((pt_list)->_t_typeinfo._sz_typename)
#define _GET_LIST_TYPE_BASENAME(pt_list)\
    ((pt_list)->_t_typeinfo._pt_type->_sz_typename)
#define _GET_LIST_TYPE_INIT_FUNCTION(pt_list)\
    ((pt_list)->_t_typeinfo._pt_type->_t_typeinit)
#define _GET_LIST_TYPE_COPY_FUNCTION(pt_list)\
    ((pt_list)->_t_typeinfo._pt_type->_t_typecopy)
#define _GET_LIST_TYPE_LESS_FUNCTION(pt_list)\
    ((pt_list)->_t_typeinfo._pt_type->_t_typeless)
#define _GET_LIST_TYPE_DESTROY_FUNCTION(pt_list)\
    ((pt_list)->_t_typeinfo._pt_type->_t_typedestroy)
#define _GET_LIST_TYPE_STYLE(pt_list)\
    ((pt_list)->_t_typeinfo._t_style)

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
#ifndef NDEBUG
/*
 * Assert support.
 */
extern bool_t _list_iterator_belong_to_list(
    const list_t* cpt_list, list_iterator_t t_iter);
extern bool_t _list_same_list_iterator_type(
    const list_t* cpt_list, list_iterator_t t_iter);
#endif /* NDEBUG */
extern bool_t _list_same_type(
    const list_t* cpt_listfirst, const list_t* cpt_listsecond);

extern void _list_get_varg_value_auxiliary(
    list_t* pt_list, va_list val_elemlist, listnode_t* pt_node);
extern void _list_destroy_varg_value_auxiliary(list_t* pt_list, listnode_t* pt_node);
extern void _list_init_node_auxiliary(list_t* pt_list, listnode_t* pt_node);

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

