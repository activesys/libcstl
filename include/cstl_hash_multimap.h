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
#define create_hash_multimap(key_type, value_type)\
    _create_hash_multimap(\
        sizeof(key_type), #key_type, \
        sizeof(value_type), #value_type)
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
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_multimap_init
 *        Parameters: in) pt_hash_multimap: hash_multimap_t*
 *                    in) pfun_hash: int (*)(const void*, size_t, size_t)
 *                          the hash function.
 *           Returns: void
 *       Description: initialize the hash_multimap.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_multimap_init(
    hash_multimap_t* pt_hash_multimap,
    int (*pfun_hash)(const void*, size_t, size_t));

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_multimap_init_n
 *        Parameters: in) pt_hash_multimap: hash_multimap_t*
 *                    in) t_bucketcount: size_t
 *                    in) pfun_hash: int (*)(const void*, size_t, size_t)
 *                          the hash function.
 *           Returns: void
 *       Description: initialize the hash_multimap.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_multimap_init_n(
    hash_multimap_t* pt_hash_multimap,
    size_t t_bucketcount,
    int (*pfun_hash)(const void*, size_t, size_t));

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_multimap_destroy
 *        Parameters: in) pt_hash_multimap: hash_multimap_t*
 *           Returns: void
 *       Description: destroy the hash_multimap.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_multimap_destroy(hash_multimap_t* pt_hash_multimap);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_multimap_init_copy
 *        Parameters: in) pt_hash_multimapdest: hash_multimap_t*
 *                        the dest hash_multimap pointer.
 *                    in) cpt_hash_multimapsrc: const hash_multimap_t*
 *                        the src hash_multimap pointer.
 *           Returns: void
 *       Description: copy the hash_multimap_t from src to dest.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_multimap_init_copy(
    hash_multimap_t* pt_hash_multimapdest, 
    const hash_multimap_t* cpt_hash_multimapsrc);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_multimap_init_copy_range
 *        Parameters: in) pt_hash_multimapdest: hash_multimap_t*
 *                        the dest hash_multimap pointer.
 *                    in) t_begin: hash_multimap_iterator_t
 *                        range begin.
 *                    in) t_end: hash_multimap_iterator_t
 *                        range end.
 *                    in) pfun_hash: int (*)(const void*, size_t, size_t)
 *           Returns: void
 *       Description: copy the hash_multimap_t from src to dest.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_multimap_init_copy_range(
    hash_multimap_t* pt_hash_multimapdest,
    hash_multimap_iterator_t t_begin,
    hash_multimap_iterator_t t_end,
    int (*pfun_hash)(const void*, size_t, size_t));

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_multimap_init_copy_range_n
 *        Parameters: in) pt_hash_multimapdest: hash_multimap_t*
 *                        the dest hash_multimap pointer.
 *                    in) t_begin: hash_multimap_iterator_t
 *                        range begin.
 *                    in) t_end: hash_multimap_iterator_t
 *                        range end.
 *                    in) t_bucketcount: size_t
 *                    in) pfun_hash: int (*)(const void*, size_t, size_t)
 *           Returns: void
 *       Description: copy the hash_multimap_t from src to dest.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_multimap_init_copy_range_n(
    hash_multimap_t* pt_hash_multimapdest,
    hash_multimap_iterator_t t_begin,
    hash_multimap_iterator_t t_end,
    size_t t_bucketcount,
    int (*pfun_hash)(const void*, size_t, size_t));

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_multimap_assign
 *        Parameters: in) pt_hash_multimapdest: hash_multimap_t*
 *                        the dest hash_multimap pointer.
 *                    in) cpt_hash_multimapsrc: const hash_multimap_t*
 *                        the src hash_multimap pointer.
 *           Returns: void
 *       Description: assign the hash_multimap_t from src to dest.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_multimap_assign(
    hash_multimap_t* pt_hash_multimapdest, 
    const hash_multimap_t* cpt_hash_multimapsrc);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_multimap_swap
 *        Parameters: in) pt_hash_multimapfirst: hash_multimap_t*
 *                          the first hash_multimap.
 *                    in) pt_hash_multimapsecond: hash_multimap_t*
 *                          the second hash_multimap.
 *           Returns: void
 *       Description: swap the datas of first hash_multimap and second hash_multimap.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_multimap_swap(
    hash_multimap_t* pt_hash_multimapfirst, 
    hash_multimap_t* pt_hash_multimapsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_multimap_size
 *        Parameters: in) cpt_hash_multimap: const hash_multimap_t*
 *                          the dest hash_multimap.
 *           Returns: size_t
 *       Description: get the hash_multimap size.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t hash_multimap_size(const hash_multimap_t* cpt_hash_multimap);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_multimap_empty
 *        Parameters: in) cpt_hash_multimap: const hash_multimap_t*
 *                          the dest hash_multimap.
 *           Returns: bool_t
 *       Description: if the hash_multimap is empty.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t hash_multimap_empty(const hash_multimap_t* cpt_hash_multimap);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_multimap_max_size
 *        Parameters: in) cpt_hash_multimap: const hash_multimap_t*
 *                          the dest hash_multimap.
 *           Returns: size_t
 *       Description: get the maximum capacity of hash_multimap.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t hash_multimap_max_size(const hash_multimap_t* cpt_hash_multimap);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_multimap_bucket_count
 *        Parameters: in) cpt_hash_multimap: const hash_multimap_t*
 *                          the dest hash_multimap.
 *           Returns: size_t
 *       Description: get the bucket count of hast table.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t hash_multimap_bucket_count(const hash_multimap_t* cpt_hash_multimap);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_multimap_hash_func
 *        Parameters: in) cpt_hash_multimap: const hash_multimap_t*
 *                          the hash_multimap.
 *           Returns: int (*)(const void*, size_t, size_t);
 *       Description: return the hash function.
 *
 * ----------------------------------------------------------------------------
 */
extern int (*hash_multimap_hash_func(const hash_multimap_t* cpt_hash_multimap))(
    const void*, size_t, size_t);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_multimap_key_comp
 *        Parameters: in) cpt_hash_multimap: const hash_multimap_t*
 *                          the hash_multimap.
 *           Returns: int (*)(const void*, const void*);
 *       Description: return the compare function.
 *
 * ----------------------------------------------------------------------------
 */
extern int (*hash_multimap_key_comp(const hash_multimap_t* cpt_hash_multimap))(
    const void*, const void*);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_multimap_resize
 *        Parameters: in) pt_hash_multimap: hash_multimap_t*
 *                          the _hash_multimap.
 *                    in) t_resize: size_t
 *                          the new size of _hash_multimap.
 *           Returns: void
 *       Description: change the number of elements to t_resize, if the size
 *                    grows new element create with the default 0.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_multimap_resize(
    hash_multimap_t* pt_hash_multimap, size_t t_resize);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_multimap_begin
 *        Parameters: in) cpt_hash_multimap: const hash_multimap_t*
 *                          the hash_multimap.
 *           Returns: hash_multimap_iterator_t
 *       Description: return the random access iterator for the first element.
 *
 * ----------------------------------------------------------------------------
 */
extern hash_multimap_iterator_t hash_multimap_begin(
    const hash_multimap_t* cpt_hash_multimap);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_multimap_end
 *        Parameters: in) cpt_hash_multimap: const hash_multimap_t*
 *                          the hash_multimap.
 *           Returns: hash_multimap_iterator_t
 *       Description: return the random access iterator for the last element.
 *
 * ----------------------------------------------------------------------------
 */
extern hash_multimap_iterator_t hash_multimap_end(
    const hash_multimap_t* cpt_hash_multimap);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_multimap_equal
 *        Parameters: in) cpt_hash_multimapfirst: const hash_multimap_t*
 *                          the first hash_multimap.
 *                    in) cpt_hash_multimapsecond: const hash_multimap_t*
 *                          the second hash_multimap.
 *           Returns: bool_t
 *       Description: return whether first hash_multimap equal to 
 *                    second hash_multimap.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t hash_multimap_equal(
    const hash_multimap_t* cpt_hash_multimapfirst, 
    const hash_multimap_t* cpt_hash_multimapsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_multimap_not_equal
 *        Parameters: in) cpt_hash_multimapfirst: const hash_multimap_t*
 *                          the first hash_multimap.
 *                    in) cpt_hash_multimapsecond: const hash_multimap_t*
 *                          the second hash_multimap.
 *           Returns: bool_t
 *       Description: return whether first hash_multimap not equal to 
 *                    second hash_multimap.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t hash_multimap_not_equal(
    const hash_multimap_t* cpt_hash_multimapfirst, 
    const hash_multimap_t* cpt_hash_multimapsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_multimap_insert
 *        Parameters: in) pt_hash_multimap: hash_multimap_t*
 *                        the hash_multimap pointer.
 *                    in) cpt_pair: const pair_t*
 *                        the element pair.
 *           Returns: hash_multimap_iterator_t
 *                        the insert result.
 *       Description: insert value into hash_multimap.
 *
 * ----------------------------------------------------------------------------
 */
extern hash_multimap_iterator_t hash_multimap_insert(
    hash_multimap_t* pt_hash_multimap, const pair_t* cpt_pair);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_multimap_insert_range
 *        Parameters: in) pt_hash_multimap: hash_multimap_t*
 *                        the rb tree pointer.
 *                    in) t_begin: hash_multimap_iterator_t
 *                        the begin iterator
 *                    in0 t_end: hash_multimap_iterator_t
 *                        the end iterator.
 *           Returns: void
 *       Description: insert a range into the hash_multimap.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_multimap_insert_range(
    hash_multimap_t* pt_hash_multimap, 
    hash_multimap_iterator_t t_begin, 
    hash_multimap_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_multimap_erase_pos
 *        Parameters: in) pt_hash_multimap: hash_multimap_t*
 *                        the rb tree pointer.
 *                    in) t_pos: hash_multimap_iterator_t
 *                        the erase iterator.
 *           Returns: void
 *       Description: erase the element pointed by t_pos.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_multimap_erase_pos(
    hash_multimap_t* pt_hash_multimap, hash_multimap_iterator_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_multimap_erase_range
 *        Parameters: in) pt_hash_multimap: hash_multimap_t*
 *                        the rb tree pointer.
 *                    in) t_begin: hash_multimap_iterator_t
 *                        the begin iterator.
 *                    in) t_end: hash_multimap_iterator_t
 *                        the end iterator.
 *           Returns: void
 *       Description: erase the all elements in the range.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_multimap_erase_range(
    hash_multimap_t* pt_hash_multimap, 
    hash_multimap_iterator_t t_begin, 
    hash_multimap_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_multimap_clear
 *        Parameters: in) pt_hash_multimap: hash_multimap_t*
 *                          the hash_multimap.
 *           Returns: void
 *       Description: remove all elements.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_multimap_clear(hash_multimap_t* pt_hash_multimap);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_HASH_MULTIMAP_H */
/** eof **/

