/*
 *  The interface of hash_multiset.
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

#ifndef _CSTL_HASH_MULTISET_H_
#define _CSTL_HASH_MULTISET_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
#define create_hash_multiset(...) _create_hash_multiset(#__VA_ARGS__)
/* find */
#define hash_multiset_find(cpt_hash_multiset, elem)\
    _hash_multiset_find((cpt_hash_multiset), (elem))
/* count */
#define hash_multiset_count(cpt_hash_multiset, elem)\
    _hash_multiset_count((cpt_hash_multiset), (elem))
/* equal range */
#define hash_multiset_equal_range(cpt_hash_multiset, elem)\
    _hash_multiset_equal_range((cpt_hash_multiset), (elem))
/* insert */
#define hash_multiset_insert(pt_hash_multiset, elem)\
    _hash_multiset_insert((pt_hash_multiset), (elem))
/* erase */
#define hash_multiset_erase(pt_hash_multiset, elem)\
    _hash_multiset_erase((pt_hash_multiset), (elem))

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * Initialization and destroy functions.
 */
extern void hash_multiset_init(hash_multiset_t* pt_hash_multiset);
extern void hash_multiset_init_ex(hash_multiset_t* pt_hash_multiset, size_t t_bucketcount,
    unary_function_t t_hash, binary_function_t t_compare);
extern void hash_multiset_destroy(hash_multiset_t* pt_hash_multiset);
extern void hash_multiset_init_copy(
    hash_multiset_t* pt_hash_multisetdest, const hash_multiset_t* cpt_hash_multisetsrc);
extern void hash_multiset_init_copy_range(hash_multiset_t* pt_hash_multisetdest,
    hash_multiset_iterator_t t_begin, hash_multiset_iterator_t t_end);
extern void hash_multiset_init_copy_range_ex(hash_multiset_t* pt_hash_multisetdest,
    hash_multiset_iterator_t t_begin, hash_multiset_iterator_t t_end, size_t t_bucketcount,
    unary_function_t t_hash, binary_function_t t_compare);

/*
 * Assign operator function.
 */
extern void hash_multiset_assign(
    hash_multiset_t* pt_hash_multisetdest, const hash_multiset_t* cpt_hash_multisetsrc);

/*
 * Swap the datas of first hash_multiset and second hash_multiset.
 */
extern void hash_multiset_swap(
    hash_multiset_t* pt_hash_multisetfirst, hash_multiset_t* pt_hash_multisetsecond);

/*
 * hash_multiset_t size operation functions.
 */
extern size_t hash_multiset_size(const hash_multiset_t* cpt_hash_multiset);
extern bool_t hash_multiset_empty(const hash_multiset_t* cpt_hash_multiset);
extern size_t hash_multiset_max_size(const hash_multiset_t* cpt_hash_multiset);
extern size_t hash_multiset_bucket_count(const hash_multiset_t* cpt_hash_multiset);

/*
 * Return the hash function.
 */
extern unary_function_t hash_multiset_hash(const hash_multiset_t* cpt_hash_multiset);

/*
 * Return the compare function.
 */
extern binary_function_t hash_multiset_key_comp(const hash_multiset_t* cpt_hash_multiset);
extern binary_function_t hash_multiset_value_comp(const hash_multiset_t* cpt_hash_multiset);

/*
 * Resize operation functions.
 */
extern void hash_multiset_resize(hash_multiset_t* pt_hash_multiset, size_t t_resize);

/*
 * Relationship operator functions.
 */
extern bool_t hash_multiset_equal(
    const hash_multiset_t* cpt_hash_multisetfirst, 
    const hash_multiset_t* cpt_hash_multisetsecond);
extern bool_t hash_multiset_not_equal(
    const hash_multiset_t* cpt_hash_multisetfirst, 
    const hash_multiset_t* cpt_hash_multisetsecond);
extern bool_t hash_multiset_less(
    const hash_multiset_t* cpt_hash_multisetfirst,
    const hash_multiset_t* cpt_hash_multisetsecond);
extern bool_t hash_multiset_less_equal(
    const hash_multiset_t* cpt_hash_multisetfirst,
    const hash_multiset_t* cpt_hash_multisetsecond);
extern bool_t hash_multiset_greater(
    const hash_multiset_t* cpt_hash_multisetfirst,
    const hash_multiset_t* cpt_hash_multisetsecond);
extern bool_t hash_multiset_greater_equal(
    const hash_multiset_t* cpt_hash_multisetfirst,
    const hash_multiset_t* cpt_hash_multisetsecond);

/*
 * Iterator support.
 */
extern hash_multiset_iterator_t hash_multiset_begin(const hash_multiset_t* cpt_hash_multiset);
extern hash_multiset_iterator_t hash_multiset_end(const hash_multiset_t* cpt_hash_multiset);

/*
 * Insert operation function.
 */
extern void hash_multiset_insert_range(hash_multiset_t* pt_hash_multiset, 
    hash_multiset_iterator_t t_begin, hash_multiset_iterator_t t_end);

/*
 * Erase operation functions.
 */
extern void hash_multiset_erase_pos(
    hash_multiset_t* pt_hash_multiset, hash_multiset_iterator_t t_pos);
extern void hash_multiset_erase_range(hash_multiset_t* pt_hash_multiset,
    hash_multiset_iterator_t t_begin, hash_multiset_iterator_t t_end);
extern void hash_multiset_clear(hash_multiset_t* pt_hash_multiset);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_HASH_MULTISET_H_ */
/** eof **/

