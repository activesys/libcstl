/*
 *  The private interface of hash_multiset.
 *  Copyright (C)  2008,2009,2010,2011  Wangbo
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
/*
 * Create operation function.
 */
extern hash_multiset_t* _create_hash_multiset(const char* s_typename);
extern bool_t _create_hash_multiset_auxiliary(
    hash_multiset_t* pt_hash_multiset, const char* s_typename);
extern void _hash_multiset_destroy_auxiliary(hash_multiset_t* pt_hash_multiset);

/*
 * Find operation functions.
 */
extern hash_multiset_iterator_t _hash_multiset_find(
    const hash_multiset_t* cpt_hash_multiset, ...);
extern hash_multiset_iterator_t _hash_multiset_find_varg(
    const hash_multiset_t* cpt_hash_multiset, va_list val_elemlist);

/*
 * Count operation function.
 */
extern size_t _hash_multiset_count(const hash_multiset_t* cpt_hash_multiset, ...);
extern size_t _hash_multiset_count_varg(
    const hash_multiset_t* cpt_hash_multiset, va_list val_elemlist);

/*
 * Equal range operation functions.
 */
extern range_t _hash_multiset_equal_range(const hash_multiset_t* cpt_hash_multiset, ...);
extern range_t _hash_multiset_equal_range_varg(
    const hash_multiset_t* cpt_hash_multiset, va_list val_elemlist);

/*
 * Insert operation functions.
 */
extern hash_multiset_iterator_t _hash_multiset_insert(
    hash_multiset_t* pt_hash_multiset, ...);
extern hash_multiset_iterator_t _hash_multiset_insert_varg(
    hash_multiset_t* pt_hash_multiset, va_list val_elemlist);

/*
 * Erase operation functions.
 */
extern size_t _hash_multiset_erase(hash_multiset_t* pt_hash_multiset, ...);
extern size_t _hash_multiset_erase_varg(
    hash_multiset_t* pt_hash_multiset, va_list val_elemlist);

extern void _hash_multiset_init_elem_auxiliary(
    hash_multiset_t* pt_hash_multiset, void* pv_value);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_HASH_MULTISET_PRIVATE_H_ */
/** eof **/

