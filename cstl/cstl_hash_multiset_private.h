/*
 *  The private interface of hash_multiset.
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

#ifndef _CSTL_HASH_MULTISET_PRIVATE_H_
#define _CSTL_HASH_MULTISET_PRIVATE_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
typedef struct _taghashmultiset
{
    _hashtable_t _t_hashtable;
}hash_multiset_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Create hash_multiset container.
 * @param s_typename        element type name.
 * @return if create hash_multiset successfully return hash_multiset pointer, otherwise return NULL.
 * @remarks s_typename == NULL, then the behavior is undefined. s_typename should be C builtin type name, libcstl builtin
 *          typename or registed user defined type name, otherwise the function will return NULL.
 */
extern hash_multiset_t* _create_hash_multiset(const char* s_typename);

/**
 * Create hash_multiset container auxiliary function.
 * @param pset_set          uncreated container.
 * @param s_typename        element type name.
 * @return if create hash_multiset successfully return true, otherwise return false.
 * @remarks if pset_set == NULL or s_typename == NULL, then the behavior is undefined. s_typename should be C builtin
 *          type name, libcstl builtin typename or registed user defined type name, otherwise the function will return false.
 */
extern bool_t _create_hash_multiset_auxiliary(hash_multiset_t* phmset_set, const char* s_typename);

/**
 * Destroy hash_multiset container auxiliary function.
 * @param pset_set        hash_multiset container.
 * @return void.
 * @remarks if pset_set == NULL, then the behavior is undefined. hash_multiset must be initialized or created by
 *          _create_hash_multiset(), otherwise the behavior is undefine.
 */
extern void _hash_multiset_destroy_auxiliary(hash_multiset_t* phmset_set);

/**
 * Find specific element.
 * @param cpset_set         hash_multiset container.
 * @param ...               specific element.
 * @return iterator addresses the sprcific element in the hash_multiset, otherwise return set_end().
 * @remarks if cpset_set == NULL then the behavior is undefined. cpset_set must be initialized, otherwise the behavior
 *          is undefined. the type of specific element and cpset_set must be same, otherwise the behavior is undefined.
 */
extern hash_multiset_iterator_t _hash_multiset_find(const hash_multiset_t* cphmset_set, ...);

/**
 * Find specific element.
 * @param cpset_set         hash_multiset container.
 * @param val_elemlist      element list.
 * @return iterator addresses the sprcific element in the hash_multiset, otherwise return set_end().
 * @remarks if cpset_set == NULL then the behavior is undefined. cpset_set must be initialized, otherwise the behavior
 *          is undefined. the type of specific element and cpset_set must be same, otherwise the behavior is undefined.
 */
extern hash_multiset_iterator_t _hash_multiset_find_varg(const hash_multiset_t* cphmset_set, va_list val_elemlist);

/**
 * Return the number of specific elements in an hash_multiset
 * @param cpset_set         hash_multiset container.
 * @param ...               specific element.
 * @return the number of specific elements.
 * @remarks if cpset_set == NULL then the behavior is undefined. cpset_set must be initialized, otherwise the behavior
 *          is undefined. the type of specific element and cpset_set must be same, otherwise the behavior is undefined.
 */
extern size_t _hash_multiset_count(const hash_multiset_t* cphmset_set, ...);

/**
 * Return the number of specific elements in an hash_multiset
 * @param cpset_set         hash_multiset container.
 * @param val_elemlist      element list.
 * @return the number of specific elements.
 * @remarks if cpset_set == NULL then the behavior is undefined. cpset_set must be initialized, otherwise the behavior
 *          is undefined. the type of specific element and cpset_set must be same, otherwise the behavior is undefined.
 */
extern size_t _hash_multiset_count_varg(const hash_multiset_t* cphmset_set, va_list val_elemlist);

/**
 * Return an iterator range that is equal to a specific element.
 * @param cpset_set         hash_multiset container.
 * @param ...               specific element.
 * @return an iterator range that is equal to a specific element.
 * @remarks if cpset_set == NULL then the behavior is undefined. cpset_set must be initialized, otherwise the behavior is
 *          undefined. the type of specific element and cpset_set must be same, otherwise the behavior is undefined.
 */
extern range_t _hash_multiset_equal_range(const hash_multiset_t* cphmset_set, ...);

/**
 * Return an iterator range that is equal to a specific element.
 * @param cpset_set         hash_multiset container.
 * @param val_elemlist      element list.
 * @return an iterator range that is equal to a specific element.
 * @remarks if cpset_set == NULL then the behavior is undefined. cpset_set must be initialized, otherwise the behavior is
 *          undefined. the type of specific element and cpset_set must be same, otherwise the behavior is undefined.
 */
extern range_t _hash_multiset_equal_range_varg(const hash_multiset_t* cphmset_set, va_list val_elemlist);

/**
 * Inserts an unique element into a hash_multiset.
 * @param pset_set          hash_multiset container.
 * @param ...               specific element.
 * @return an iterator addresses the inserted element, or hash_multiset end if insert failed.
 * @remarks if pset_set == NULL then the behavior is undefined. cpset_set must be initialized, otherwise the behavior is
 *          undefined. the type of specific element and cpset_set must be same, otherwise the behavior is undefined.
 */
extern hash_multiset_iterator_t _hash_multiset_insert(hash_multiset_t* phmset_set, ...);

/**
 * Inserts an unique element into a hash_multiset.
 * @param pset_set          hash_multiset container.
 * @param val_elemlist      element list.
 * @return an iterator addresses the inserted element, or hash_multiset end if insert failed.
 * @remarks if pset_set == NULL then the behavior is undefined. cpset_set must be initialized, otherwise the behavior is
 *          undefined. the type of specific element and cpset_set must be same, otherwise the behavior is undefined.
 */
extern hash_multiset_iterator_t _hash_multiset_insert_varg(hash_multiset_t* phmset_set, va_list val_elemlist);

/**
 * Erase an element from a hash_multiset that match a specified element.
 * @param pset_set          hash_multiset container.
 * @param ...               specific element.
 * @return the number of erased elements.
 * @remarks if pset_set == NULL then the behavior is undefined. cpset_set must be initialized, otherwise the behavior is
 *          undefined. 
 */
extern size_t _hash_multiset_erase(hash_multiset_t* phmset_set, ...);

/**
 * Erase an element from a hash_multiset that match a specified element.
 * @param pset_set          hash_multiset container.
 * @param val_elemlist      element list.
 * @return the number of erased elements.
 * @remarks if pset_set == NULL then the behavior is undefined. cpset_set must be initialized, otherwise the behavior is
 *          undefined. 
 */
extern size_t _hash_multiset_erase_varg(hash_multiset_t* phmset_set, va_list val_elemlist);

/**
 * Initialize element auxiliary function
 * @param pset_set          hash_multiset.
 * @param pv_value          value.
 * @return void.
 * @remarks if pset_set == NULL or pv_value == NULL, then the behavior is undefine. pset_set must be initialized or
 *          created by _create_hash_multiset(), otherwise the behavior is undefined.
 */
extern void _hash_multiset_init_elem_auxiliary(hash_multiset_t* phmset_set, void* pv_value);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_HASH_MULTISET_PRIVATE_H_ */
/** eof **/

