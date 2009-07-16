/*
 *  The private interface of hash_multimap.
 *  Copyright (C)  2008 2009  Wangbo
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

#ifndef _CSTL_HASH_MULTIMAP_PRIVATE_H
#define _CSTL_HASH_MULTIMAP_PRIVATE_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
typedef struct _taghashmultimap
{
    pair_t      _t_pair;
    hashtable_t _t_hashtable;
}hash_multimap_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * Create operation functions.
 */
extern hash_multimap_t _create_hash_multimap(
    size_t t_keytypesize, const char* s_keytypename,
    size_t t_valuetypesize, const char* s_valuetypename);

/*
 * Find operation function.
 */
extern hash_multimap_iterator_t _hash_multimap_find(
    const hash_multimap_t* cpt_hash_multimap, ...);
extern hash_multimap_iterator_t _hash_multimap_find_varg(
    const hash_multimap_t* cpt_hash_multimap, va_list val_elemlist);

/*
 * Count operation functions.
 */
extern size_t _hash_multimap_count(const hash_multimap_t* cpt_hash_multimap, ...);
extern size_t _hash_multimap_count_varg(
    const hash_multimap_t* cpt_hash_multimap, va_list val_elemlist);

/*
 * Equal range operation functions.
 */
extern range_t _hash_multimap_equal_range(
    const hash_multimap_t* cpt_hash_multimap, ...);
extern range_t _hash_multimap_equal_range_varg(
    const hash_multimap_t* cpt_hash_multimap, va_list val_elemlist);

/*
 * Erase operation functions.
 */
extern size_t _hash_multimap_erase(hash_multimap_t* pt_hash_multimap, ...);
extern size_t _hash_multimap_erase_varg(
    hash_multimap_t* pt_hash_multimap, va_list val_elemlist);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_HASH_MULTIMAP_PRIVATE_H */
/** eof **/

