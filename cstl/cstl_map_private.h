/*
 *  The private interface of map.
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

#ifndef _CSTL_MAP_PRIVATE_H_
#define _CSTL_MAP_PRIVATE_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
/* the map use rb tree default */
typedef struct _tagmap
{
    pair_t            _pair_temp;
    bfun_t            _bfun_keycompare;   /* for init ex */
    bfun_t            _bfun_valuecompare;

#ifdef CSTL_MAP_AVL_TREE
    _avl_tree_t       _t_tree;
#else
    _rb_tree_t        _t_tree;
#endif
}map_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Create map container.
 * @param s_typename        element type name.
 * @return if create map successfully return map pointer, otherwise return NULL.
 * @remarks s_typename == NULL, then the behavior is undefined. s_typename should be C builtin type name, libcstl builtin
 *          typename or registed user defined type name, otherwise the function will return NULL.
 */
extern map_t* _create_map(const char* s_typename);

/**
 * Create map container auxiliary function.
 * @param pmap_map          uncreated container.
 * @param s_typename        element type name.
 * @return if create map successfully return true, otherwise return false.
 * @remarks if pmap_map == NULL or s_typename == NULL, then the behavior is undefined. s_typename should be C builtin
 *          type name, libcstl builtin typename or registed user defined type name, otherwise the function will return false.
 */
extern bool_t _create_map_auxiliary(map_t* pmap_map, const char* s_typename);

/**
 * Destroy map container auxiliary function.
 * @param pmap_map        map container.
 * @return void.
 * @remarks if pmap_map == NULL, then the behavior is undefined. map must be initialized or created by
 *          _create_map(), otherwise the behavior is undefine.
 */
extern void _map_destroy_auxiliary(map_t* pmap_map);

/**
 * Find specific element.
 * @param cpmap_map         map container.
 * @param ...               specific element.
 * @return iterator addresses the sprcific element in the map, otherwise return map_end().
 * @remarks if cpmap_map == NULL then the behavior is undefined. cpmap_map must be initialized, otherwise the behavior
 *          is undefined. the type of specific element and cpmap_map must be same, otherwise the behavior is undefined.
 */
extern map_iterator_t _map_find(const map_t* cpmap_map, ...);

/**
 * Find specific element.
 * @param cpmap_map         map container.
 * @param val_elemlist      element list.
 * @return iterator addresses the sprcific element in the map, otherwise return map_end().
 * @remarks if cpmap_map == NULL then the behavior is undefined. cpmap_map must be initialized, otherwise the behavior
 *          is undefined. the type of specific element and cpmap_map must be same, otherwise the behavior is undefined.
 */
extern map_iterator_t _map_find_varg(const map_t* cpmap_map, va_list val_elemlist);

/**
 * Return the number of specific elements in an map
 * @param cpmap_map         map container.
 * @param ...               specific element.
 * @return the number of specific elements.
 * @remarks if cpmap_map == NULL then the behavior is undefined. cpmap_map must be initialized, otherwise the behavior
 *          is undefined. the type of specific element and cpmap_map must be same, otherwise the behavior is undefined.
 */
extern size_t _map_count(const map_t* cpmap_map, ...);

/**
 * Return the number of specific elements in an map
 * @param cpmap_map         map container.
 * @param val_elemlist      element list.
 * @return the number of specific elements.
 * @remarks if cpmap_map == NULL then the behavior is undefined. cpmap_map must be initialized, otherwise the behavior
 *          is undefined. the type of specific element and cpmap_map must be same, otherwise the behavior is undefined.
 */
extern size_t _map_count_varg(const map_t* cpmap_map, va_list val_elemlist);

/**
 * Return an iterator to the first element that is equal to or greater than a specific element.
 * @param cpmap_map          map container.
 * @param ...                specific element.
 * @return an iterator to the first element that is equal to or greater than a specific element.
 * @remarks if cpmap_map == NULL then the behavior is undefined. cpmap_map must be initialized, otherwise the behavior is
 *          undefined. the type of specific element and cpmap_map must be same, otherwise the behavior is undefined.
 */
extern map_iterator_t _map_lower_bound(const map_t* cpmap_map, ...);

/**
 * Return an iterator to the first element that is equal to or greater than a specific element.
 * @param cpmap_map         map container.
 * @param val_elemlist      element list.
 * @return an iterator to the first element that is equal to or greater than a specific element.
 * @remarks if cpmap_map == NULL then the behavior is undefined. cpmap_map must be initialized, otherwise the behavior is
 *          undefined. the type of specific element and cpmap_map must be same, otherwise the behavior is undefined.
 */
extern map_iterator_t _map_lower_bound_varg(const map_t* cpmap_map, va_list val_elemlist);

/**
 * Return an iterator to the first element that is greater than a specific element.
 * @param cpmap_map         map container.
 * @param ...               specific element.
 * @return an iterator to the first element that is greater than a specific element.
 * @remarks if cpmap_map == NULL then the behavior is undefined. cpmap_map must be initialized, otherwise the behavior is
 *          undefined. the type of specific element and cpmap_map must be same, otherwise the behavior is undefined.
 */
extern map_iterator_t _map_upper_bound(const map_t* cpmap_map, ...);

/**
 * Return an iterator to the first element that is greater than a specific element.
 * @param cpmap_map         map container.
 * @param val_elemlist      element list.
 * @return an iterator to the first element that is greater than a specific element.
 * @remarks if cpmap_map == NULL then the behavior is undefined. cpmap_map must be initialized, otherwise the behavior is
 *          undefined. the type of specific element and cpmap_map must be same, otherwise the behavior is undefined.
 */
extern map_iterator_t _map_upper_bound_varg(const map_t* cpmap_map, va_list val_elemlist);

/**
 * Return an iterator range that is equal to a specific element.
 * @param cpmap_map         map container.
 * @param ...               specific element.
 * @return an iterator range that is equal to a specific element.
 * @remarks if cpmap_map == NULL then the behavior is undefined. cpmap_map must be initialized, otherwise the behavior is
 *          undefined. the type of specific element and cpmap_map must be same, otherwise the behavior is undefined.
 */
extern range_t _map_equal_range(const map_t* cpmap_map, ...);

/**
 * Return an iterator range that is equal to a specific element.
 * @param cpmap_map         map container.
 * @param val_elemlist      element list.
 * @return an iterator range that is equal to a specific element.
 * @remarks if cpmap_map == NULL then the behavior is undefined. cpmap_map must be initialized, otherwise the behavior is
 *          undefined. the type of specific element and cpmap_map must be same, otherwise the behavior is undefined.
 */
extern range_t _map_equal_range_varg(const map_t* cpmap_map, va_list val_elemlist);

/**
 * Access an element with specific index.
 * @param pmap_map          map container.
 * @param val_elemlist      element list.
 * @return the pointer that point to the second element.
 * @remarks if pmap_map == NULL then the behavior is undefined. cpmap_map must be initialized, otherwise the behavior is
 *          undefined. 
 */
extern void* _map_at(map_t* pmap_map, ...);

/**
 * Access an element with specific index.
 * @param pmap_map          map container.
 * @param val_elemlist      element list.
 * @return the pointer that point to the second element.
 * @remarks if pmap_map == NULL then the behavior is undefined. cpmap_map must be initialized, otherwise the behavior is
 *          undefined. 
 */
extern void* _map_at_varg(map_t* pmap_map, va_list val_elemlist);

/**
 * Erase an element from a map that match a specified element.
 * @param pmap_map          map container.
 * @param ...               specific element.
 * @return the number of erased elements.
 * @remarks if pmap_map == NULL then the behavior is undefined. cpmap_map must be initialized, otherwise the behavior is
 *          undefined. 
 */
extern size_t _map_erase(map_t* pmap_map, ...);

/**
 * Erase an element from a map that match a specified element.
 * @param pmap_map          map container.
 * @param val_elemlist      element list.
 * @return the number of erased elements.
 * @remarks if pmap_map == NULL then the behavior is undefined. cpmap_map must be initialized, otherwise the behavior is
 *          undefined. 
 */
extern size_t _map_erase_varg(map_t* pmap_map, va_list val_elemlist);

/**
 * Initialize element auxiliary function
 * @param pmap_map          map.
 * @param pv_value          value.
 * @return void.
 * @remarks if pmap_map == NULL or pv_value == NULL, then the behavior is undefine. pmap_map must be initialized or
 *          created by _create_map(), otherwise the behavior is undefined.
 */
extern void _map_init_elem_auxiliary(map_t* pmap_map, void* pv_value);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_MAP_PRIVATE_H_ */
/** eof **/

