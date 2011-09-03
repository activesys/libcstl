/*
 *  The interface of hashtable.
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

#ifndef _CSTL_HASHTABLE_H_
#define _CSTL_HASHTABLE_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/

/* for the result of equal_range and insert_unique function */

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * Create, initialization and destroy functions.
 */
extern _hashtable_t* _create_hashtable(const char* s_typename);
extern void _hashtable_init(_hashtable_t* pt_hashtable,
    size_t t_bucketcount, unary_function_t t_hash, binary_function_t t_compare);
extern void _hashtable_destroy(_hashtable_t* pt_hashtable);
extern void _hashtable_init_copy(
    _hashtable_t* pt_hashtabledest, const _hashtable_t* cpt_hashtablesrc);
extern void _hashtable_init_copy_range(_hashtable_t* pt_hashtabledest,
    _hashtable_iterator_t t_begin, _hashtable_iterator_t t_end,
    size_t t_bucketcount, unary_function_t t_hash, binary_function_t t_compare);

/*
 * Assign operator function.
 */
extern void _hashtable_assign(
    _hashtable_t* pt_hashtabledest, const _hashtable_t* cpt_hashtablesrc);

/*
 * _hashtable_t size operation functions.
 */
extern size_t _hashtable_size(const _hashtable_t* cpt_hashtable);
extern bool_t _hashtable_empty(const _hashtable_t* cpt_hashtable);
extern size_t _hashtable_max_size(const _hashtable_t* cpt_hashtable);
extern size_t _hashtable_bucket_count(const _hashtable_t* cpt_hashtable);

/*
 * Iterator support.
 */
extern _hashtable_iterator_t _hashtable_begin(const _hashtable_t* cpt_hashtable);
extern _hashtable_iterator_t _hashtable_end(const _hashtable_t* cpt_hashtable);

/*
 * Remove all elements.
 */
extern void _hashtable_clear(_hashtable_t* pt_hashtable);

/*
 * Return the hash function.
 */
extern unary_function_t _hashtable_hash(const _hashtable_t* cpt_hashtable);

/*
 * Return the compare function (private).
 */
extern binary_function_t _hashtable_key_comp(const _hashtable_t* cpt_hashtable);

/*
 * Relationship operator functions.
 */
extern bool_t _hashtable_equal(
    const _hashtable_t* cpt_hashtablefirst, const _hashtable_t* cpt_hashtablesecond);
extern bool_t _hashtable_not_equal(
    const _hashtable_t* cpt_hashtablefirst, const _hashtable_t* cpt_hashtablesecond);
extern bool_t _hashtable_less(
    const _hashtable_t* cpt_hashtablefirst, const _hashtable_t* cpt_hashtablesecond);
extern bool_t _hashtable_less_equal(
    const _hashtable_t* cpt_hashtablefirst, const _hashtable_t* cpt_hashtablesecond);
extern bool_t _hashtable_greater(
    const _hashtable_t* cpt_hashtablefirst, const _hashtable_t* cpt_hashtablesecond);
extern bool_t _hashtable_greater_equal(
    const _hashtable_t* cpt_hashtablefirst, const _hashtable_t* cpt_hashtablesecond);

/*
 * Resize operation function.
 */
extern void _hashtable_resize(_hashtable_t* pt_hashtable, size_t t_resize);

/*
 * Insert operation functions.
 */
extern _hashtable_iterator_t _hashtable_insert_unique(
    _hashtable_t* pt_hashtable, const void* cpv_value);
extern _hashtable_iterator_t _hashtable_insert_equal(
    _hashtable_t* pt_hashtable, const void* cpv_value);
extern void _hashtable_insert_unique_range(
    _hashtable_t* pt_hashtable, _hashtable_iterator_t t_begin, _hashtable_iterator_t t_end);
extern void _hashtable_insert_equal_range(
    _hashtable_t* pt_hashtable, _hashtable_iterator_t t_begin, _hashtable_iterator_t t_end);

/*
 * Find operation function.
 */
extern _hashtable_iterator_t _hashtable_find(
    const _hashtable_t* cpt_hashtable, const void* cpv_value);

/*
 * Equal range operation functions.
 */
extern range_t _hashtable_equal_range(
    const _hashtable_t* cpt_hashtable, const void* cpv_value);

/*
 * Counts the numbers of element whose key is value.
 */
extern size_t _hashtable_count(const _hashtable_t* cpt_hashtable, const void* cpv_value);

/*
 * Erase operation functions.
 */
extern void _hashtable_erase_pos(_hashtable_t* pt_hashtable, _hashtable_iterator_t t_pos);
extern void _hashtable_erase_range(
    _hashtable_t* pt_hashtable, _hashtable_iterator_t t_begin, _hashtable_iterator_t t_end);
extern size_t _hashtable_erase(_hashtable_t* pt_hashtable, const void* cpv_value);

/*
 * Swap the datas of first hashtable and second hashtable.
 */
extern void _hashtable_swap(
    _hashtable_t* pt_hashtablefirst, _hashtable_t* pt_hashtablesecond);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_HASHTABLE_H_ */
/** eof **/

