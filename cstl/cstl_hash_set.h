/*
 *  The interface of hash_set.
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

#ifndef _CSTL_HASH_SET_H
#define _CSTL_HASH_SET_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
#define create_hash_set(...) _create_hash_set(#__VA_ARGS__)
/* find */
#define hash_set_find(cpt_hash_set, elem)\
    _hash_set_find((cpt_hash_set), (elem))
/* count */
#define hash_set_count(cpt_hash_set, elem)\
    _hash_set_count((cpt_hash_set), (elem))
/* equal range */
#define hash_set_equal_range(cpt_hash_set, elem)\
    _hash_set_equal_range((cpt_hash_set), (elem))
/* insert */
#define hash_set_insert(pt_hash_set, elem)\
    _hash_set_insert((pt_hash_set), (elem))
/* erase */
#define hash_set_erase(pt_hash_set, elem)\
    _hash_set_erase((pt_hash_set), (elem))

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * Initialization and destroy functions.
 */
extern void hash_set_init(hash_set_t* pt_hash_set);
extern void hash_set_init_ex(hash_set_t* pt_hash_set, size_t t_bucketcount,
    unary_function_t t_hash, binary_function_t t_compare);
extern void hash_set_destroy(hash_set_t* pt_hash_set);
extern void hash_set_init_copy(hash_set_t* pt_hash_setdest, const hash_set_t* cpt_hash_setsrc);
extern void hash_set_init_copy_range(
    hash_set_t* pt_hash_setdest, hash_set_iterator_t t_begin, hash_set_iterator_t t_end);
extern void hash_set_init_copy_range_ex(hash_set_t* pt_hash_set,
    hash_set_iterator_t t_begin, hash_set_iterator_t t_end, size_t t_bucketcount,
    unary_function_t t_hash, binary_function_t t_compare);

/*
 * Assign operator function.
 */
extern void hash_set_assign(hash_set_t* pt_hash_setdest, const hash_set_t* cpt_hash_setsrc);

/*
 * Swap the datas of first hash_set and second hash_set.
 */
extern void hash_set_swap(hash_set_t* pt_hash_setfirst, hash_set_t* pt_hash_setsecond);

/*
 * hash_set_t size operation functions.
 */
extern size_t hash_set_size(const hash_set_t* cpt_hash_set);
extern bool_t hash_set_empty(const hash_set_t* cpt_hash_set);
extern size_t hash_set_max_size(const hash_set_t* cpt_hash_set);
extern size_t hash_set_bucket_count(const hash_set_t* cpt_hash_set);

/*
 * Return the hash function.
 */
extern unary_function_t hash_set_hash(const hash_set_t* cpt_hash_set);

/*
 * Return the compare function.
 */
extern binary_function_t hash_set_key_comp(const hash_set_t* cpt_hash_set);
extern binary_function_t hash_set_value_comp(const hash_set_t* cpt_hash_set);

/*
 * Resize operation.
 */
extern void hash_set_resize(hash_set_t* pt_hash_set, size_t t_resize);

/*
 * Relationship operator.
 */
extern bool_t hash_set_equal(
    const hash_set_t* cpt_hash_setfirst, const hash_set_t* cpt_hash_setsecond);
extern bool_t hash_set_not_equal(
    const hash_set_t* cpt_hash_setfirst, const hash_set_t* cpt_hash_setsecond);
extern bool_t hash_set_less(
    const hash_set_t* cpt_hash_setfirst, const hash_set_t* cpt_hash_setsecond);
extern bool_t hash_set_less_equal(
    const hash_set_t* cpt_hash_setfirst, const hash_set_t* cpt_hash_setsecond);
extern bool_t hash_set_greater(
    const hash_set_t* cpt_hash_setfirst, const hash_set_t* cpt_hash_setsecond);
extern bool_t hash_set_greater_equal(
    const hash_set_t* cpt_hash_setfirst, const hash_set_t* cpt_hash_setsecond);

/*
 * Iterator support.
 */
extern hash_set_iterator_t hash_set_begin(const hash_set_t* cpt_hash_set);
extern hash_set_iterator_t hash_set_end(const hash_set_t* cpt_hash_set);

/*
 * Insert operation function.
 */
extern void hash_set_insert_range(
    hash_set_t* pt_hash_set, hash_set_iterator_t t_begin, hash_set_iterator_t t_end);

/*
 * Erase operation functions.
 */
extern void hash_set_erase_pos(hash_set_t* pt_hash_set, hash_set_iterator_t t_pos);
extern void hash_set_erase_range(
    hash_set_t* pt_hash_set, hash_set_iterator_t t_begin, hash_set_iterator_t t_end);
extern void hash_set_clear(hash_set_t* pt_hash_set);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_HASH_SET_H */
/** eof **/

