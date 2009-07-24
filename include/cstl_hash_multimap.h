/*
 *  The interface of hash_multimap.
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

#ifndef _CSTL_HASH_MULTIMAP_H
#define _CSTL_HASH_MULTIMAP_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
#define create_hash_multimap(...) _create_hash_multimap(#__VA_ARGS__)
/* find */
#define hash_multimap_find(cpt_hash_multimap, key_elem)\
    _hash_multimap_find((cpt_hash_multimap), (key_elem))
/* count */
#define hash_multimap_count(cpt_hash_multimap, key_elem)\
    _hash_multimap_count((cpt_hash_multimap), (key_elem))
/* equal range */
#define hash_multimap_equal_range(cpt_hash_multimap, key_elem)\
    _hash_multimap_equal_range((cpt_hash_multimap), (key_elem))
/* erase */
#define hash_multimap_erase(pt_hash_multimap, key_elem)\
    _hash_multimap_erase((pt_hash_multimap), (key_elem))

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * Initialization and destroy operation functions.
 */
extern void hash_multimap_init(hash_multimap_t* pt_hash_multimap);
extern void hash_multimap_init_ex(hash_multimap_t* pt_hash_multimap, size_t t_bucketcount,
    unary_function_t t_hash, binary_function_t t_less);
extern void hash_multimap_destroy(hash_multimap_t* pt_hash_multimap);
extern void hash_multimap_init_copy(
    hash_multimap_t* pt_hash_multimapdest, const hash_multimap_t* cpt_hash_multimapsrc);
extern void hash_multimap_init_copy_range(hash_multimap_t* pt_hash_multimapdest,
    hash_multimap_iterator_t t_begin, hash_multimap_iterator_t t_end);
extern void hash_multimap_init_copy_range_ex(hash_multimap_t* pt_hash_multimapdest,
    hash_multimap_iterator_t t_begin, hash_multimap_iterator_t t_end,
    size_t t_bucketcount, unary_function_t t_hash, binary_function_t t_less);

/*
 * Assign operator function.
 */
extern void hash_multimap_assign(
    hash_multimap_t* pt_hash_multimapdest, const hash_multimap_t* cpt_hash_multimapsrc);

/*
 * Swap the datas of first hash_multimap and second hash_multimap.
 */
extern void hash_multimap_swap(
    hash_multimap_t* pt_hash_multimapfirst, hash_multimap_t* pt_hash_multimapsecond);

/*
 * hash_multimap_t size operation functions.
 */
extern size_t hash_multimap_size(const hash_multimap_t* cpt_hash_multimap);
extern bool_t hash_multimap_empty(const hash_multimap_t* cpt_hash_multimap);
extern size_t hash_multimap_max_size(const hash_multimap_t* cpt_hash_multimap);
extern size_t hash_multimap_bucket_count(const hash_multimap_t* cpt_hash_multimap);

/*
 * Return the hash function.
 */
extern unary_function_t hash_multimap_hash(const hash_multimap_t* cpt_hash_multimap);

/*
 * Return the compare function.
 */
extern binary_function_t hash_multimap_key_less(const hash_multimap_t* cpt_hash_multimap);

/*
 * Resize operation function.
 */
extern void hash_multimap_resize(hash_multimap_t* pt_hash_multimap, size_t t_resize);

/*
 * Iterator support.
 */
extern hash_multimap_iterator_t hash_multimap_begin(const hash_multimap_t* cpt_hash_multimap);
extern hash_multimap_iterator_t hash_multimap_end(const hash_multimap_t* cpt_hash_multimap);

/*
 * Relationship operator functions.
 */
extern bool_t hash_multimap_equal(
    const hash_multimap_t* cpt_hash_multimapfirst, 
    const hash_multimap_t* cpt_hash_multimapsecond);
extern bool_t hash_multimap_not_equal(
    const hash_multimap_t* cpt_hash_multimapfirst, 
    const hash_multimap_t* cpt_hash_multimapsecond);
extern bool_t hash_multimap_less(
    const hash_multimap_t* cpt_hash_multimapfirst, 
    const hash_multimap_t* cpt_hash_multimapsecond);
extern bool_t hash_multimap_less_equal(
    const hash_multimap_t* cpt_hash_multimapfirst,
    const hash_multimap_t* cpt_hash_multimapsecond);
extern bool_t hash_multimap_great(
    const hash_multimap_t* cpt_hash_multimapfirst,
    const hash_multimap_t* cpt_hash_multimapsecond);
extern bool_t hash_multimap_great_equal(
    const hash_multimap_t* cpt_hash_multimapfirst,
    const hash_multimap_t* cpt_hash_multimapsecond);

/*
 * Insert operation functions.
 */
extern hash_multimap_iterator_t hash_multimap_insert(
    hash_multimap_t* pt_hash_multimap, const pair_t* cpt_pair);
extern void hash_multimap_insert_range(hash_multimap_t* pt_hash_multimap, 
    hash_multimap_iterator_t t_begin, hash_multimap_iterator_t t_end);

/*
 * Erase operation functions.
 */
extern void hash_multimap_erase_pos(
    hash_multimap_t* pt_hash_multimap, hash_multimap_iterator_t t_pos);
extern void hash_multimap_erase_range(hash_multimap_t* pt_hash_multimap, 
    hash_multimap_iterator_t t_begin, hash_multimap_iterator_t t_end);
extern void hash_multimap_clear(hash_multimap_t* pt_hash_multimap);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_HASH_MULTIMAP_H */
/** eof **/

