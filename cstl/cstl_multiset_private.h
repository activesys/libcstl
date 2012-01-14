/*
 *  The private interface of multiset.
 *  Copyright (C)  2008 - 2012  Wangbo
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

#ifndef _CSTL_MULTISET_PRIVATE_H_
#define _CSTL_MULTISET_PRIVATE_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
/* the multiset use rb tree default */
typedef struct _tagmultiset
{
#ifdef CSTL_MULTISET_AVL_TREE
    _avl_tree_t _t_tree;
#else
    _rb_tree_t  _t_tree;
#endif
}multiset_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Create multiset container.
 * @param s_typename        element type name.
 * @return if create multiset successfully return multiset pointer, otherwise return NULL.
 * @remarks s_typename == NULL, then the behavior is undefined. s_typename should be C builtin type name, libcstl builtin
 *          typename or registed user defined type name, otherwise the function will return NULL.
 */
extern multiset_t* _create_multiset(const char* s_typename);

/**
 * Create multiset container auxiliary function.
 * @param pmset_mset        uncreated container.
 * @param s_typename        element type name.
 * @return if create multiset successfully return true, otherwise return false.
 * @remarks if pmset_mset == NULL or s_typename == NULL, then the behavior is undefined. s_typename should be C builtin
 *          type name, libcstl builtin typename or registed user defined type name, otherwise the function will return false.
 */
extern bool_t _create_multiset_auxiliary(multiset_t* pmset_mset, const char* s_typename);

/**
 * Destroy multiset container auxiliary function.
 * @param pmset_mset        multiset container.
 * @return void.
 * @remarks if pmset_mset == NULL, then the behavior is undefined. multiset must be initialized or created by
 *          create_multiset(), otherwise the behavior is undefine.
 */
extern void _multiset_destroy_auxiliary(multiset_t* pv_multiset);

/**
 * Find specific element.
 * @param cpmset_mset       multiset container.
 * @param ...               specific element.
 * @return iterator addresses the sprcific element in the multiset, otherwise return multiset_end().
 * @remarks if cpmset_mset == NULL then the behavior is undefined. cpmset_mset must be initialized, otherwise the behavior
 *          is undefined. the type of specific element and cpmset_mset must be same, otherwise the behavior is undefined.
 */
extern multiset_iterator_t _multiset_find(const multiset_t* cpmset_mset, ...);

/**
 * Find specific element.
 * @param cpmset_mset       multiset container.
 * @param val_elemlist      element list.
 * @return iterator addresses the sprcific element in the multiset, otherwise return multiset_end().
 * @remarks if cpmset_mset == NULL then the behavior is undefined. cpmset_mset must be initialized, otherwise the behavior
 *          is undefined. the type of specific element and cpmset_mset must be same, otherwise the behavior is undefined.
 */
extern multiset_iterator_t _multiset_find_varg(const multiset_t* cpmset_mset, va_list val_elemlist);

/**
 * Return the number of specific elements in an multiset
 * @param cpmset_mset       multiset container.
 * @param ...               specific element.
 * @return the number of specific elements.
 * @remarks if cpmset_mset == NULL then the behavior is undefined. cpmset_mset must be initialized, otherwise the behavior
 *          is undefined. the type of specific element and cpmset_mset must be same, otherwise the behavior is undefined.
 */
extern size_t _multiset_count(const multiset_t* cpmset_mset, ...);

/**
 * Return the number of specific elements in an multiset
 * @param cpmset_mset       multiset container.
 * @param val_elemlist      element list.
 * @return the number of specific elements.
 * @remarks if cpmset_mset == NULL then the behavior is undefined. cpmset_mset must be initialized, otherwise the behavior
 *          is undefined. the type of specific element and cpmset_mset must be same, otherwise the behavior is undefined.
 */
extern size_t _multiset_count_varg(const multiset_t* cpmset_mset, va_list val_elemlist);

/**
 * Return an iterator to the first element that is equal to or greater than a specific element.
 * @param cpmset_mset        multiset container.
 * @param ...                specific element.
 * @return an iterator to the first element that is equal to or greater than a specific element.
 * @remarks if cpmset_mset == NULL then the behavior is undefined. cpmset_mset must be initialized, otherwise the behavior is
 *          undefined. the type of specific element and cpmset_mset must be same, otherwise the behavior is undefined.
 */
extern multiset_iterator_t _multiset_lower_bound(const multiset_t* cpmset_mset, ...);

/**
 * Return an iterator to the first element that is equal to or greater than a specific element.
 * @param cpmset_mset       multiset container.
 * @param val_elemlist      element list.
 * @return an iterator to the first element that is equal to or greater than a specific element.
 * @remarks if cpmset_mset == NULL then the behavior is undefined. cpmset_mset must be initialized, otherwise the behavior is
 *          undefined. the type of specific element and cpmset_mset must be same, otherwise the behavior is undefined.
 */
extern multiset_iterator_t _multiset_lower_bound_varg(const multiset_t* cpmset_mset, va_list val_elemlist);

/**
 * Return an iterator to the first element that is greater than a specific element.
 * @param cpmset_mset       multiset container.
 * @param ...               specific element.
 * @return an iterator to the first element that is greater than a specific element.
 * @remarks if cpmset_mset == NULL then the behavior is undefined. cpmset_mset must be initialized, otherwise the behavior is
 *          undefined. the type of specific element and cpmset_mset must be same, otherwise the behavior is undefined.
 */
extern multiset_iterator_t _multiset_upper_bound(const multiset_t* cpmset_mset, ...);

/**
 * Return an iterator to the first element that is greater than a specific element.
 * @param cpmset_mset       multiset container.
 * @param val_elemlist      element list.
 * @return an iterator to the first element that is greater than a specific element.
 * @remarks if cpmset_mset == NULL then the behavior is undefined. cpmset_mset must be initialized, otherwise the behavior is
 *          undefined. the type of specific element and cpmset_mset must be same, otherwise the behavior is undefined.
 */
extern multiset_iterator_t _multiset_upper_bound_varg(const multiset_t* cpmset_mset, va_list val_elemlist);

/**
 * Return an iterator range that is equal to a specific element.
 * @param cpmset_mset       multiset container.
 * @param ...               specific element.
 * @return an iterator range that is equal to a specific element.
 * @remarks if cpmset_mset == NULL then the behavior is undefined. cpmset_mset must be initialized, otherwise the behavior is
 *          undefined. the type of specific element and cpmset_mset must be same, otherwise the behavior is undefined.
 */
extern range_t _multiset_equal_range(const multiset_t* cpmset_mset, ...);

/**
 * Return an iterator range that is equal to a specific element.
 * @param cpmset_mset       multiset container.
 * @param val_elemlist      element list.
 * @return an iterator range that is equal to a specific element.
 * @remarks if cpmset_mset == NULL then the behavior is undefined. cpmset_mset must be initialized, otherwise the behavior is
 *          undefined. the type of specific element and cpmset_mset must be same, otherwise the behavior is undefined.
 */
extern range_t _multiset_equal_range_varg(const multiset_t* cpmset_mset, va_list val_elemlist);

/**
 * Erase an element from a multiset that match a specified element.
 * @param pmset_mset        multiset container.
 * @param ...               specific element.
 * @return the number of erased elements.
 * @remarks if pmset_mset == NULL then the behavior is undefined. cpmset_mset must be initialized, otherwise the behavior is
 *          undefined. 
 */
extern size_t _multiset_erase(multiset_t* pmset_mset, ...);

/**
 * Erase an element from a multiset that match a specified element.
 * @param pmset_mset        multiset container.
 * @param val_elemlist      element list.
 * @return the number of erased elements.
 * @remarks if pmset_mset == NULL then the behavior is undefined. cpmset_mset must be initialized, otherwise the behavior is
 *          undefined. 
 */
extern size_t _multiset_erase_varg(multiset_t* pmset_mset, va_list val_elemlist);

/**
 * Inserts an element into a multiset.
 * @param pmset_mset        multiset container.
 * @param ...               specific element.
 * @return an iterator addresses the inserted element, or multiset end if insert failed.
 * @remarks if pmset_mset == NULL then the behavior is undefined. cpmset_mset must be initialized, otherwise the behavior is
 *          undefined. the type of specific element and cpmset_mset must be same, otherwise the behavior is undefined.
 */
extern multiset_iterator_t _multiset_insert(multiset_t* pmset_mset, ...);

/**
 * Inserts an element into a multiset.
 * @param pmset_mset        multiset container.
 * @param val_elemlist      element list.
 * @return an iterator addresses the inserted element, or multiset end if insert failed.
 * @remarks if pmset_mset == NULL then the behavior is undefined. cpmset_mset must be initialized, otherwise the behavior is
 *          undefined. the type of specific element and cpmset_mset must be same, otherwise the behavior is undefined.
 */
extern multiset_iterator_t _multiset_insert_varg(multiset_t* pmset_mset, va_list val_elemlist);

/**
 * Inserts an element into a multiset with hint.
 * @param pmset_mset        multiset container.
 * @param it_hint           hint position.
 * @param ...               specific element.
 * @return an iterator addresses the inserted element, or multiset end if insert failed.
 * @remarks if pmset_mset == NULL then the behavior is undefined. cpmset_mset must be initialized, otherwise the behavior is
 *          undefined. the type of specific element and cpmset_mset must be same, otherwise the behavior is undefined.
 */
extern multiset_iterator_t _multiset_insert_hint(multiset_t* pmset_mset, multiset_iterator_t it_hint, ...);

/**
 * Inserts an element into a multiset with hint.
 * @param pmset_mset        multiset container.
 * @param it_hint           hint position.
 * @param val_elemlist      element list.
 * @return an iterator addresses the inserted element, or multiset end if insert failed.
 * @remarks if pmset_mset == NULL then the behavior is undefined. cpmset_mset must be initialized, otherwise the behavior is
 *          undefined. the type of specific element and cpmset_mset must be same, otherwise the behavior is undefined.
 */
extern multiset_iterator_t _multiset_insert_hint_varg(multiset_t* pmset_mset, multiset_iterator_t it_hint, va_list val_elemlist);

/**
 * Initialize element auxiliary function
 * @param pmset_mset        multiset.
 * @param pv_value          value.
 * @return void.
 * @remarks if pmset_mset == NULL or pv_value == NULL, then the behavior is undefine. pmset_mset must be initialized or
 *          created by _create_set(), otherwise the behavior is undefined.
 */
extern void _multiset_init_elem_auxiliary(multiset_t* pmset_mset, void* pv_value);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_MULTISET_PRIVATE_H_ */
/** eof **/

