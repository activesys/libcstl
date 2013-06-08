/*
 *  The iterator interface of hash_map.
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

#ifndef _CSTL_HASH_MAP_PRIVATE_H_
#define _CSTL_HASH_MAP_PRIVATE_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
typedef struct _taghashmap
{
    pair_t            _pair_temp;
    bfun_t            _bfun_keycompare;    /* for external key compare */
    bfun_t            _bfun_valuecompare;
    _hashtable_t      _t_hashtable;
}hash_map_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Create hash_map container.
 * @param s_typename        element type name.
 * @return if create hash_map successfully return hash_map pointer, otherwise return NULL.
 * @remarks s_typename == NULL, then the behavior is undefined. s_typename should be C builtin type name, libcstl builtin
 *          typename or registed user defined type name, otherwise the function will return NULL.
 */
extern hash_map_t* _create_hash_map(const char* s_typename);

/**
 * Create hash_map container auxiliary function.
 * @param phmap_map          uncreated container.
 * @param s_typename        element type name.
 * @return if create hash_map successfully return true, otherwise return false.
 * @remarks if phmap_map == NULL or s_typename == NULL, then the behavior is undefined. s_typename should be C builtin
 *          type name, libcstl builtin typename or registed user defined type name, otherwise the function will return false.
 */
extern bool_t _create_hash_map_auxiliary(hash_map_t* phmap_map, const char* s_typename);

/**
 * Destroy hash_map container auxiliary function.
 * @param phmap_map        hash_map container.
 * @return void.
 * @remarks if phmap_map == NULL, then the behavior is undefined. hash_map must be initialized or created by
 *          _create_hash_map(), otherwise the behavior is undefine.
 */
extern void _hash_map_destroy_auxiliary(hash_map_t* phmap_map);

/**
 * Find specific element.
 * @param cphmap_map         hash_map container.
 * @param ...               specific element.
 * @return iterator addresses the sprcific element in the hash_map, otherwise return map_end().
 * @remarks if cphmap_map == NULL then the behavior is undefined. cphmap_map must be initialized, otherwise the behavior
 *          is undefined. the type of specific element and cphmap_map must be same, otherwise the behavior is undefined.
 */
extern hash_map_iterator_t _hash_map_find(const hash_map_t* cphmap_map, ...);

/**
 * Find specific element.
 * @param cphmap_map         hash_map container.
 * @param val_elemlist      element list.
 * @return iterator addresses the sprcific element in the hash_map, otherwise return map_end().
 * @remarks if cphmap_map == NULL then the behavior is undefined. cphmap_map must be initialized, otherwise the behavior
 *          is undefined. the type of specific element and cphmap_map must be same, otherwise the behavior is undefined.
 */
extern hash_map_iterator_t _hash_map_find_varg(const hash_map_t* cphmap_map, va_list val_elemlist);

/**
 * Return the number of specific elements in an hash_map
 * @param cphmap_map         hash_map container.
 * @param ...               specific element.
 * @return the number of specific elements.
 * @remarks if cphmap_map == NULL then the behavior is undefined. cphmap_map must be initialized, otherwise the behavior
 *          is undefined. the type of specific element and cphmap_map must be same, otherwise the behavior is undefined.
 */
extern size_t _hash_map_count(const hash_map_t* cphmap_map, ...);

/**
 * Return the number of specific elements in an hash_map
 * @param cphmap_map         hash_map container.
 * @param val_elemlist      element list.
 * @return the number of specific elements.
 * @remarks if cphmap_map == NULL then the behavior is undefined. cphmap_map must be initialized, otherwise the behavior
 *          is undefined. the type of specific element and cphmap_map must be same, otherwise the behavior is undefined.
 */
extern size_t _hash_map_count_varg(const hash_map_t* cphmap_map, va_list val_elemlist);

/**
 * Return an iterator range that is equal to a specific element.
 * @param cphmap_map         hash_map container.
 * @param ...               specific element.
 * @return an iterator range that is equal to a specific element.
 * @remarks if cphmap_map == NULL then the behavior is undefined. cphmap_map must be initialized, otherwise the behavior is
 *          undefined. the type of specific element and cphmap_map must be same, otherwise the behavior is undefined.
 */
extern range_t _hash_map_equal_range(const hash_map_t* cphmap_map, ...);

/**
 * Return an iterator range that is equal to a specific element.
 * @param cphmap_map         hash_map container.
 * @param val_elemlist      element list.
 * @return an iterator range that is equal to a specific element.
 * @remarks if cphmap_map == NULL then the behavior is undefined. cphmap_map must be initialized, otherwise the behavior is
 *          undefined. the type of specific element and cphmap_map must be same, otherwise the behavior is undefined.
 */
extern range_t _hash_map_equal_range_varg(const hash_map_t* cphmap_map, va_list val_elemlist);

/**
 * Access an element with specific index.
 * @param phmap_map          hash_map container.
 * @param val_elemlist      element list.
 * @return the pointer that point to the second element.
 * @remarks if phmap_map == NULL then the behavior is undefined. cphmap_map must be initialized, otherwise the behavior is
 *          undefined. 
 */
extern void* _hash_map_at(hash_map_t* phmap_map, ...);

/**
 * Access an element with specific index.
 * @param phmap_map          hash_map container.
 * @param val_elemlist      element list.
 * @return the pointer that point to the second element.
 * @remarks if phmap_map == NULL then the behavior is undefined. cphmap_map must be initialized, otherwise the behavior is
 *          undefined. 
 */
extern void* _hash_map_at_varg(hash_map_t* phmap_map, va_list val_elemlist);

/**
 * Erase an element from a hash_map that match a specified element.
 * @param phmap_map          hash_map container.
 * @param ...               specific element.
 * @return the number of erased elements.
 * @remarks if phmap_map == NULL then the behavior is undefined. cphmap_map must be initialized, otherwise the behavior is
 *          undefined. 
 */
extern size_t _hash_map_erase(hash_map_t* phmap_map, ...);

/**
 * Erase an element from a hash_map that match a specified element.
 * @param phmap_map          hash_map container.
 * @param val_elemlist      element list.
 * @return the number of erased elements.
 * @remarks if phmap_map == NULL then the behavior is undefined. cphmap_map must be initialized, otherwise the behavior is
 *          undefined. 
 */
extern size_t _hash_map_erase_varg(hash_map_t* phmap_map, va_list val_elemlist);

/**
 * Initialize element auxiliary function
 * @param phmap_map          hash_map.
 * @param pv_value          value.
 * @return void.
 * @remarks if phmap_map == NULL or pv_value == NULL, then the behavior is undefine. phmap_map must be initialized or
 *          created by _create_hash_map(), otherwise the behavior is undefined.
 */
extern void _hash_map_init_elem_auxiliary(hash_map_t* phmap_map, void* pv_value);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_HASH_MAP_PRIVATE_H_ */
/** eof **/

