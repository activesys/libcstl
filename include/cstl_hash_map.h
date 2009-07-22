/*
 *  The interface of hash_map.
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

#ifndef _CSTL_HASH_MAP_H
#define _CSTL_HASH_MAP_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
#define create_hash_map(...) _create_hash_map(#__VA_ARGS__)
/* find */
#define hash_map_find(cpt_hash_map, key_elem)\
    _hash_map_find((cpt_hash_map), (key_elem))
/* count */
#define hash_map_count(cpt_hash_map, key_elem)\
    _hash_map_count((cpt_hash_map), (key_elem))
/* equal range */
#define hash_map_equal_range(cpt_hash_map, key_elem)\
    _hash_map_equal_range((cpt_hash_map), (key_elem))
/* at */
#define hash_map_at(pt_hash_map, key_elem)\
    _hash_map_at((pt_hash_map), (key_elem))
/* erase */
#define hash_map_erase(pt_hash_map, key_elem)\
    _hash_map_erase((pt_hash_map), (key_elem))

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * Initialization and destroy functions.
 */
extern void hash_map_init(hash_map_t* pt_hash_map);
extern void hash_map_init_ex(hash_map_t* pt_hash_map, size_t t_bucketcount,
    unary_function_t t_hash, binary_function_t t_less);
extern void hash_map_destroy(hash_map_t* pt_hash_map);
extern void hash_map_init_copy(
    hash_map_t* pt_hash_mapdest, const hash_map_t* cpt_hash_mapsrc);
extern void hash_map_init_copy_range(hash_map_t* pt_hash_mapdest,
    hash_map_iterator_t t_begin, hash_map_iterator_t t_end);
extern void hash_map_init_copy_range_ex(hash_map_t* pt_hash_mapdest,
    hash_map_iterator_t t_begin, hash_map_iterator_t t_end, size_t t_bucketcount,
    unary_function_t t_hash, binary_function_t t_less);

/*
 * Assign operator function.
 */
extern void hash_map_assign(
    hash_map_t* pt_hash_mapdest, const hash_map_t* cpt_hash_mapsrc);

/*
 * Swap the datas of first hash_map and second hash_map.
 */
extern void hash_map_swap(
    hash_map_t* pt_hash_mapfirst, hash_map_t* pt_hash_mapsecond);

/*
 * hash_map_t size operation functions.
 */
extern size_t hash_map_size(const hash_map_t* cpt_hash_map);
extern bool_t hash_map_empty(const hash_map_t* cpt_hash_map);
extern size_t hash_map_max_size(const hash_map_t* cpt_hash_map);
extern size_t hash_map_bucket_count(const hash_map_t* cpt_hash_map);

/*
 * Return the hash function.
 */
extern unary_function_t hash_map_hash_func(const hash_map_t* cpt_hash_map);

/*
 * Return the compare function.
 */
extern binary_function_t hash_map_key_comp(const hash_map_t* cpt_hash_map);

/*
 * hash_map_t resize operation function.
 */
extern void hash_map_resize(hash_map_t* pt_hash_map, size_t t_resize);

/*
 * Iterator support.
 */
extern hash_map_iterator_t hash_map_begin(const hash_map_t* cpt_hash_map);
extern hash_map_iterator_t hash_map_end(const hash_map_t* cpt_hash_map);

/*
 * Relationship operator functions.
 */
extern bool_t hash_map_equal(
    const hash_map_t* cpt_hash_mapfirst, const hash_map_t* cpt_hash_mapsecond);
extern bool_t hash_map_not_equal(
    const hash_map_t* cpt_hash_mapfirst, const hash_map_t* cpt_hash_mapsecond);
extern bool_t hash_map_less(
    const hash_map_t* cpt_hash_mapfirst, const hash_map_t* cpt_hash_mapsecond);
extern bool_t hash_map_less_equal(
    const hash_map_t* cpt_hash_mapfirst, const hash_map_t* cpt_hash_mapsecond);
extern bool_t hash_map_great(
    const hash_map_t* cpt_hash_mapfirst, const hash_map_t* cpt_hash_mapsecond);
extern bool_t hash_map_great_great(
    const hash_map_t* cpt_hash_mapfirst, const hash_map_t* cpt_hash_mapsecond);

/*
 * Insert operation functions.
 */
extern hash_map_iterator_t hash_map_insert(
    hash_map_t* pt_hash_map, const pair_t* cpt_pair);
extern void hash_map_insert_range(
    hash_map_t* pt_hash_map, hash_map_iterator_t t_begin, hash_map_iterator_t t_end);

/*
 * Erase operation functions.
 */
extern void hash_map_erase_pos(hash_map_t* pt_hash_map, hash_map_iterator_t t_pos);
extern void hash_map_erase_range(
    hash_map_t* pt_hash_map, hash_map_iterator_t t_begin, hash_map_iterator_t t_end);
extern void hash_map_clear(hash_map_t* pt_hash_map);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_HASH_MAP_H */
/** eof **/

