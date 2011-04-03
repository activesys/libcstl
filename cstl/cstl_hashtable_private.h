/*
 *  The private interface of hashtable.
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

#ifndef _CSTL_HASHTABLE_PRIVATE_H_
#define _CSTL_HASHTABLE_PRIVATE_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
typedef struct _taghashnode
{
    struct _taghashnode* _pt_next;
    char                 _pc_data[1];
}hashnode_t;

typedef struct _taghashtable
{
    /* element type information */
    _typeinfo_t _t_typeinfo;

    /* memory allocate */
    _alloc_t    _t_allocator;

    /* buckets and node */
    vector_t    _t_bucket;
    size_t      _t_nodecount;

    /* hash function */
    unary_function_t _t_hash;
    /* key compare function */
    binary_function_t _t_compare;
}hashtable_t;

/* for the result of equal_range and insert_unique function */

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * Create, initialization and destroy functions.
 */
extern hashtable_t* _create_hashtable(const char* s_typename);
extern bool_t _create_hashtable_auxiliary(hashtable_t* pt_hashtable, const char* s_typename);
extern void _hashtable_init(hashtable_t* pt_hashtable,
    size_t t_bucketcount, unary_function_t t_hash, binary_function_t t_compare);
extern void _hashtable_destroy(hashtable_t* pt_hashtable);
extern void _hashtable_destroy_auxiliary(hashtable_t* pt_hashtable);
extern void _hashtable_init_copy(
    hashtable_t* pt_hashtabledest, const hashtable_t* cpt_hashtablesrc);
extern void _hashtable_init_copy_range(hashtable_t* pt_hashtabledest,
    hashtable_iterator_t t_begin, hashtable_iterator_t t_end,
    size_t t_bucketcount, unary_function_t t_hash, binary_function_t t_compare);

/*
 * Assign operator function.
 */
extern void _hashtable_assign(
    hashtable_t* pt_hashtabledest, const hashtable_t* cpt_hashtablesrc);

/*
 * _hashtable_t size operation functions.
 */
extern size_t _hashtable_size(const hashtable_t* cpt_hashtable);
extern bool_t _hashtable_empty(const hashtable_t* cpt_hashtable);
extern size_t _hashtable_max_size(const hashtable_t* cpt_hashtable);
extern size_t _hashtable_bucket_count(const hashtable_t* cpt_hashtable);

/*
 * Iterator support.
 */
extern hashtable_iterator_t _hashtable_begin(const hashtable_t* cpt_hashtable);
extern hashtable_iterator_t _hashtable_end(const hashtable_t* cpt_hashtable);

/*
 * Remove all elements.
 */
extern void _hashtable_clear(hashtable_t* pt_hashtable);

/*
 * Return the hash function.
 */
extern unary_function_t _hashtable_hash(const hashtable_t* cpt_hashtable);

/*
 * Return the compare function (private).
 */
extern binary_function_t _hashtable_key_comp(const hashtable_t* cpt_hashtable);

/*
 * Relationship operator functions.
 */
extern bool_t _hashtable_equal(
    const hashtable_t* cpt_hashtablefirst, const hashtable_t* cpt_hashtablesecond);
extern bool_t _hashtable_not_equal(
    const hashtable_t* cpt_hashtablefirst, const hashtable_t* cpt_hashtablesecond);
extern bool_t _hashtable_less(
    const hashtable_t* cpt_hashtablefirst, const hashtable_t* cpt_hashtablesecond);
extern bool_t _hashtable_less_equal(
    const hashtable_t* cpt_hashtablefirst, const hashtable_t* cpt_hashtablesecond);
extern bool_t _hashtable_greater(
    const hashtable_t* cpt_hashtablefirst, const hashtable_t* cpt_hashtablesecond);
extern bool_t _hashtable_greater_equal(
    const hashtable_t* cpt_hashtablefirst, const hashtable_t* cpt_hashtablesecond);

/*
 * Resize operation function.
 */
extern void _hashtable_resize(hashtable_t* pt_hashtable, size_t t_resize);

/*
 * Insert operation functions.
 */
extern hashtable_iterator_t _hashtable_insert_unique(
    hashtable_t* pt_hashtable, const void* cpv_value);
extern hashtable_iterator_t _hashtable_insert_equal(
    hashtable_t* pt_hashtable, const void* cpv_value);
extern void _hashtable_insert_unique_range(
    hashtable_t* pt_hashtable, hashtable_iterator_t t_begin, hashtable_iterator_t t_end);
extern void _hashtable_insert_equal_range(
    hashtable_t* pt_hashtable, hashtable_iterator_t t_begin, hashtable_iterator_t t_end);

/*
 * Find operation function.
 */
extern hashtable_iterator_t _hashtable_find(
    const hashtable_t* cpt_hashtable, const void* cpv_value);

/*
 * Equal range operation functions.
 */
extern range_t _hashtable_equal_range(
    const hashtable_t* cpt_hashtable, const void* cpv_value);

/*
 * Counts the numbers of element whose key is value.
 */
extern size_t _hashtable_count(const hashtable_t* cpt_hashtable, const void* cpv_value);

/*
 * Erase operation functions.
 */
extern void _hashtable_erase_pos(hashtable_t* pt_hashtable, hashtable_iterator_t t_pos);
extern void _hashtable_erase_range(
    hashtable_t* pt_hashtable, hashtable_iterator_t t_begin, hashtable_iterator_t t_end);
extern size_t _hashtable_erase(hashtable_t* pt_hashtable, const void* cpv_value);

/*
 * Swap the datas of first hashtable and second hashtable.
 */
extern void _hashtable_swap(
    hashtable_t* pt_hashtablefirst, hashtable_t* pt_hashtablesecond);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_HASHTABLE_PRIVATE_H_ */
/** eof **/

