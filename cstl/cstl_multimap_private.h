/*
 *  The private interface of multimap.
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

#ifndef _CSTL_MULTIMAP_PRIVATE_H_
#define _CSTL_MULTIMAP_PRIVATE_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
/* the multimap use rb tree default */
typedef struct _tagmultimap
{
    pair_t            _pair_temp;
    bfun_t            _bfun_keycompare; /* for init ex */
    bfun_t            _bfun_valuecompare;

#ifdef CSTL_MULTIMAP_AVL_TREE
    _avl_tree_t       _t_tree;
#else
    _rb_tree_t        _t_tree;
#endif
}multimap_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Create multimap container.
 * @param s_typename        element type name.
 * @return if create multimap successfully return multimap pointer, otherwise return NULL.
 * @remarks s_typename == NULL, then the behavior is undefined. s_typename should be C builtin type name, libcstl builtin
 *          typename or registed user defined type name, otherwise the function will return NULL.
 */
extern multimap_t* _create_multimap(const char* s_typename);

/**
 * Create multimap container auxiliary function.
 * @param pmmap_map          uncreated container.
 * @param s_typename        element type name.
 * @return if create multimap successfully return true, otherwise return false.
 * @remarks if pmmap_map == NULL or s_typename == NULL, then the behavior is undefined. s_typename should be C builtin
 *          type name, libcstl builtin typename or registed user defined type name, otherwise the function will return false.
 */
extern bool_t _create_multimap_auxiliary(multimap_t* pmmap_map, const char* s_typename);

/**
 * Destroy multimap container auxiliary function.
 * @param pmmap_map        multimap container.
 * @return void.
 * @remarks if pmmap_map == NULL, then the behavior is undefined. multimap must be initialized or created by
 *          _create_map(), otherwise the behavior is undefine.
 */
extern void _multimap_destroy_auxiliary(multimap_t* pmmap_map);

/**
 * Find specific element.
 * @param cpmmap_map         multimap container.
 * @param ...               specific element.
 * @return iterator addresses the sprcific element in the multimap, otherwise return map_end().
 * @remarks if cpmmap_map == NULL then the behavior is undefined. cpmmap_map must be initialized, otherwise the behavior
 *          is undefined. the type of specific element and cpmmap_map must be same, otherwise the behavior is undefined.
 */
extern multimap_iterator_t _multimap_find(const multimap_t* cpmmap_map, ...);

/**
 * Find specific element.
 * @param cpmmap_map         multimap container.
 * @param val_elemlist      element list.
 * @return iterator addresses the sprcific element in the multimap, otherwise return map_end().
 * @remarks if cpmmap_map == NULL then the behavior is undefined. cpmmap_map must be initialized, otherwise the behavior
 *          is undefined. the type of specific element and cpmmap_map must be same, otherwise the behavior is undefined.
 */
extern multimap_iterator_t _multimap_find_varg(const multimap_t* cpmmap_map, va_list val_elemlist);

/**
 * Return the number of specific elements in an multimap
 * @param cpmmap_map         multimap container.
 * @param ...               specific element.
 * @return the number of specific elements.
 * @remarks if cpmmap_map == NULL then the behavior is undefined. cpmmap_map must be initialized, otherwise the behavior
 *          is undefined. the type of specific element and cpmmap_map must be same, otherwise the behavior is undefined.
 */
extern size_t _multimap_count(const multimap_t* cpmmap_map, ...);

/**
 * Return the number of specific elements in an multimap
 * @param cpmmap_map         multimap container.
 * @param val_elemlist      element list.
 * @return the number of specific elements.
 * @remarks if cpmmap_map == NULL then the behavior is undefined. cpmmap_map must be initialized, otherwise the behavior
 *          is undefined. the type of specific element and cpmmap_map must be same, otherwise the behavior is undefined.
 */
extern size_t _multimap_count_varg(const multimap_t* cpmmap_map, va_list val_elemlist);

/**
 * Return an iterator to the first element that is equal to or greater than a specific element.
 * @param cpmmap_map          multimap container.
 * @param ...                specific element.
 * @return an iterator to the first element that is equal to or greater than a specific element.
 * @remarks if cpmmap_map == NULL then the behavior is undefined. cpmmap_map must be initialized, otherwise the behavior is
 *          undefined. the type of specific element and cpmmap_map must be same, otherwise the behavior is undefined.
 */
extern multimap_iterator_t _multimap_lower_bound(const multimap_t* cpmmap_map, ...);

/**
 * Return an iterator to the first element that is equal to or greater than a specific element.
 * @param cpmmap_map         multimap container.
 * @param val_elemlist      element list.
 * @return an iterator to the first element that is equal to or greater than a specific element.
 * @remarks if cpmmap_map == NULL then the behavior is undefined. cpmmap_map must be initialized, otherwise the behavior is
 *          undefined. the type of specific element and cpmmap_map must be same, otherwise the behavior is undefined.
 */
extern multimap_iterator_t _multimap_lower_bound_varg(const multimap_t* cpmmap_map, va_list val_elemlist);

/**
 * Return an iterator to the first element that is greater than a specific element.
 * @param cpmmap_map         multimap container.
 * @param ...               specific element.
 * @return an iterator to the first element that is greater than a specific element.
 * @remarks if cpmmap_map == NULL then the behavior is undefined. cpmmap_map must be initialized, otherwise the behavior is
 *          undefined. the type of specific element and cpmmap_map must be same, otherwise the behavior is undefined.
 */
extern multimap_iterator_t _multimap_upper_bound(const multimap_t* cpmmap_map, ...);

/**
 * Return an iterator to the first element that is greater than a specific element.
 * @param cpmmap_map         multimap container.
 * @param val_elemlist      element list.
 * @return an iterator to the first element that is greater than a specific element.
 * @remarks if cpmmap_map == NULL then the behavior is undefined. cpmmap_map must be initialized, otherwise the behavior is
 *          undefined. the type of specific element and cpmmap_map must be same, otherwise the behavior is undefined.
 */
extern multimap_iterator_t _multimap_upper_bound_varg(const multimap_t* cpmmap_map, va_list val_elemlist);

/**
 * Return an iterator range that is equal to a specific element.
 * @param cpmmap_map         multimap container.
 * @param ...               specific element.
 * @return an iterator range that is equal to a specific element.
 * @remarks if cpmmap_map == NULL then the behavior is undefined. cpmmap_map must be initialized, otherwise the behavior is
 *          undefined. the type of specific element and cpmmap_map must be same, otherwise the behavior is undefined.
 */
extern range_t _multimap_equal_range(const multimap_t* cpmmap_map, ...);

/**
 * Return an iterator range that is equal to a specific element.
 * @param cpmmap_map         multimap container.
 * @param val_elemlist      element list.
 * @return an iterator range that is equal to a specific element.
 * @remarks if cpmmap_map == NULL then the behavior is undefined. cpmmap_map must be initialized, otherwise the behavior is
 *          undefined. the type of specific element and cpmmap_map must be same, otherwise the behavior is undefined.
 */
extern range_t _multimap_equal_range_varg(const multimap_t* cpmmap_map, va_list val_elemlist);

/**
 * Erase an element from a multimap that match a specified element.
 * @param pmmap_map          multimap container.
 * @param ...               specific element.
 * @return the number of erased elements.
 * @remarks if pmmap_map == NULL then the behavior is undefined. cpmmap_map must be initialized, otherwise the behavior is
 *          undefined. 
 */
extern size_t _multimap_erase(multimap_t* pmmap_map, ...);

/**
 * Erase an element from a multimap that match a specified element.
 * @param pmmap_map          multimap container.
 * @param val_elemlist      element list.
 * @return the number of erased elements.
 * @remarks if pmmap_map == NULL then the behavior is undefined. cpmmap_map must be initialized, otherwise the behavior is
 *          undefined. 
 */
extern size_t _multimap_erase_varg(multimap_t* pmmap_map, va_list val_elemlist);

/**
 * Initialize element auxiliary function
 * @param pmmap_map          multimap.
 * @param pv_value          value.
 * @return void.
 * @remarks if pmmap_map == NULL or pv_value == NULL, then the behavior is undefine. pmmap_map must be initialized or
 *          created by _create_map(), otherwise the behavior is undefined.
 */
extern void _multimap_init_elem_auxiliary(multimap_t* pmmap_map, void* pv_value);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_MULTIMAP_PRIVATE_H_ */
/** eof **/

