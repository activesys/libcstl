/*
 *  The private interface of hash_set.
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

#ifndef _CSTL_HASH_SET_PRIVATE_H
#define _CSTL_HASH_SET_PRIVATE_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
typedef struct _taghashset
{
    hashtable_t _t_hashtable;
}hash_set_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * Create operation function.
 */
extern hash_set_t* _create_hash_set(const char* s_typename);
extern bool_t _create_hash_set_auxiliary(hash_set_t* pt_hash_set, const char* s_typename);
extern void _hash_set_destroy_auxiliary(hash_set_t* pt_hash_set);

/*
 * Find operatio functions.
 */
extern hash_set_iterator_t _hash_set_find(const hash_set_t* cpt_hash_set, ...);
extern hash_set_iterator_t _hash_set_find_varg(
    const hash_set_t* cpt_hash_set, va_list val_elemlist);

/*
 * Count operation functions.
 */
extern size_t _hash_set_count(const hash_set_t* cpt_hash_set, ...);
extern size_t _hash_set_count_varg(const hash_set_t* cpt_hash_set, va_list val_elemlist);

/*
 * Equal range operation functions.
 */
extern range_t _hash_set_equal_range(const hash_set_t* cpt_hash_set, ...);
extern range_t _hash_set_equal_range_varg(
    const hash_set_t* cpt_hash_set, va_list val_elemlist);

/*
 * Insert operation functions.
 */
extern hash_set_iterator_t _hash_set_insert(hash_set_t* pt_hash_set, ...);
extern hash_set_iterator_t _hash_set_insert_varg(
    hash_set_t* pt_hash_set, va_list val_elemlist);

/*
 * Erase operation functions.
 */
extern size_t _hash_set_erase(hash_set_t* pt_hash_set, ...);
extern size_t _hash_set_erase_varg(hash_set_t* pt_hash_set, va_list val_elemlist);

extern void _hash_set_init_elem_auxiliary(hash_set_t* pt_hash_set, void* pv_value);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_HASH_SET_PRIVATE_H */
/** eof **/

