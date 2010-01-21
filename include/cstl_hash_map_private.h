/*
 *  The iterator interface of hash_map.
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

#ifndef _CSTL_HASH_MAP_PRIVATE_H
#define _CSTL_HASH_MAP_PRIVATE_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
typedef struct _taghashmap
{
    pair_t      _t_pair;
    hashtable_t _t_hashtable;
}hash_map_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * Create operation function.
 */
extern hash_map_t* _create_hash_map(const char* s_typename);
extern bool_t _create_hash_map_auxiliary(hash_map_t* pt_hash_map, const char* s_typename);
extern void _hash_map_destroy_auxiliary(hash_map_t* pt_hash_map);

/*
 * Find operation functions.
 */
extern hash_map_iterator_t _hash_map_find(const hash_map_t* cpt_hash_map, ...);
extern hash_map_iterator_t _hash_map_find_varg(
    const hash_map_t* cpt_hash_map, va_list val_elemlist);

/*
 * Count operation functions.
 */
extern size_t _hash_map_count(const hash_map_t* cpt_hash_map, ...);
extern size_t _hash_map_count_varg(
    const hash_map_t* cpt_hash_map, va_list val_elemlist);

/*
 * Equal range operation functions.
 */
extern range_t _hash_map_equal_range(const hash_map_t* cpt_hash_map, ...);
extern range_t _hash_map_equal_range_varg(
    const hash_map_t* cpt_hash_map, va_list val_elemlist);

/*
 * Element random access operation.
 */
extern void* _hash_map_at(hash_map_t* pt_hash_map, ...);
extern void* _hash_map_at_varg(hash_map_t* pt_hash_map, va_list val_elemlist);

/*
 * Erase operation functions.
 */
extern size_t _hash_map_erase(hash_map_t* pt_hash_map, ...);
extern size_t _hash_map_erase_varg(hash_map_t* pt_hash_map, va_list val_elemlist);

extern void _hash_map_init_elem_auxiliary(hash_map_t* pt_hash_map, void* pv_value);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_HASH_MAP_PRIVATE_H */
/** eof **/

