/*
 *  The private interface of hash_multimap.
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

#ifndef _CSTL_HASH_MULTIMAP_PRIVATE_H_
#define _CSTL_HASH_MULTIMAP_PRIVATE_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
typedef struct _taghashmultimap
{
    pair_t            _pair_temp;
    bfun_t            _bfun_keycompare; /* external key compare */
    bfun_t            _bfun_valuecompare;
    _hashtable_t      _t_hashtable;
}hash_multimap_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Create hash_multimap container.
 * @param s_typename        element type name.
 * @return if create hash_multimap successfully return hash_multimap pointer, otherwise return NULL.
 * @remarks s_typename == NULL, then the behavior is undefined. s_typename should be C builtin type name, libcstl builtin
 *          typename or registed user defined type name, otherwise the function will return NULL.
 */
extern hash_multimap_t* _create_hash_multimap(const char* s_typename);

/**
 * Create hash_multimap container auxiliary function.
 * @param phmmap_map          uncreated container.
 * @param s_typename        element type name.
 * @return if create hash_multimap successfully return true, otherwise return false.
 * @remarks if phmmap_map == NULL or s_typename == NULL, then the behavior is undefined. s_typename should be C builtin
 *          type name, libcstl builtin typename or registed user defined type name, otherwise the function will return false.
 */
extern bool_t _create_hash_multimap_auxiliary(hash_multimap_t* phmmap_map, const char* s_typename);

/**
 * Destroy hash_multimap container auxiliary function.
 * @param phmmap_map        hash_multimap container.
 * @return void.
 * @remarks if phmmap_map == NULL, then the behavior is undefined. hash_multimap must be initialized or created by
 *          _create_hash_multimap(), otherwise the behavior is undefine.
 */
extern void _hash_multimap_destroy_auxiliary(hash_multimap_t* phmmap_map);

/**
 * Find specific element.
 * @param cphmmap_map         hash_multimap container.
 * @param ...               specific element.
 * @return iterator addresses the sprcific element in the hash_multimap, otherwise return map_end().
 * @remarks if cphmmap_map == NULL then the behavior is undefined. cphmmap_map must be initialized, otherwise the behavior
 *          is undefined. the type of specific element and cphmmap_map must be same, otherwise the behavior is undefined.
 */
extern hash_multimap_iterator_t _hash_multimap_find(const hash_multimap_t* cphmmap_map, ...);

/**
 * Find specific element.
 * @param cphmmap_map         hash_multimap container.
 * @param val_elemlist      element list.
 * @return iterator addresses the sprcific element in the hash_multimap, otherwise return map_end().
 * @remarks if cphmmap_map == NULL then the behavior is undefined. cphmmap_map must be initialized, otherwise the behavior
 *          is undefined. the type of specific element and cphmmap_map must be same, otherwise the behavior is undefined.
 */
extern hash_multimap_iterator_t _hash_multimap_find_varg(const hash_multimap_t* cphmmap_map, va_list val_elemlist);

/**
 * Return the number of specific elements in an hash_multimap
 * @param cphmmap_map         hash_multimap container.
 * @param ...               specific element.
 * @return the number of specific elements.
 * @remarks if cphmmap_map == NULL then the behavior is undefined. cphmmap_map must be initialized, otherwise the behavior
 *          is undefined. the type of specific element and cphmmap_map must be same, otherwise the behavior is undefined.
 */
extern size_t _hash_multimap_count(const hash_multimap_t* cphmmap_map, ...);

/**
 * Return the number of specific elements in an hash_multimap
 * @param cphmmap_map         hash_multimap container.
 * @param val_elemlist      element list.
 * @return the number of specific elements.
 * @remarks if cphmmap_map == NULL then the behavior is undefined. cphmmap_map must be initialized, otherwise the behavior
 *          is undefined. the type of specific element and cphmmap_map must be same, otherwise the behavior is undefined.
 */
extern size_t _hash_multimap_count_varg(const hash_multimap_t* cphmmap_map, va_list val_elemlist);

/**
 * Return an iterator range that is equal to a specific element.
 * @param cphmmap_map         hash_multimap container.
 * @param ...               specific element.
 * @return an iterator range that is equal to a specific element.
 * @remarks if cphmmap_map == NULL then the behavior is undefined. cphmmap_map must be initialized, otherwise the behavior is
 *          undefined. the type of specific element and cphmmap_map must be same, otherwise the behavior is undefined.
 */
extern range_t _hash_multimap_equal_range(const hash_multimap_t* cphmmap_map, ...);

/**
 * Return an iterator range that is equal to a specific element.
 * @param cphmmap_map         hash_multimap container.
 * @param val_elemlist      element list.
 * @return an iterator range that is equal to a specific element.
 * @remarks if cphmmap_map == NULL then the behavior is undefined. cphmmap_map must be initialized, otherwise the behavior is
 *          undefined. the type of specific element and cphmmap_map must be same, otherwise the behavior is undefined.
 */
extern range_t _hash_multimap_equal_range_varg(const hash_multimap_t* cphmmap_map, va_list val_elemlist);

/**
 * Erase an element from a hash_multimap that match a specified element.
 * @param phmmap_map          hash_multimap container.
 * @param ...               specific element.
 * @return the number of erased elements.
 * @remarks if phmmap_map == NULL then the behavior is undefined. cphmmap_map must be initialized, otherwise the behavior is
 *          undefined. 
 */
extern size_t _hash_multimap_erase(hash_multimap_t* phmmap_map, ...);

/**
 * Erase an element from a hash_multimap that match a specified element.
 * @param phmmap_map          hash_multimap container.
 * @param val_elemlist      element list.
 * @return the number of erased elements.
 * @remarks if phmmap_map == NULL then the behavior is undefined. cphmmap_map must be initialized, otherwise the behavior is
 *          undefined. 
 */
extern size_t _hash_multimap_erase_varg(hash_multimap_t* phmmap_map, va_list val_elemlist);

/**
 * Initialize element auxiliary function
 * @param phmmap_map          hash_multimap.
 * @param pv_value          value.
 * @return void.
 * @remarks if phmmap_map == NULL or pv_value == NULL, then the behavior is undefine. phmmap_map must be initialized or
 *          created by _create_hash_multimap(), otherwise the behavior is undefined.
 */
extern void _hash_multimap_init_elem_auxiliary(hash_multimap_t* phmmap_map, void* pv_value);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_HASH_MULTIMAP_PRIVATE_H_ */
/** eof **/

