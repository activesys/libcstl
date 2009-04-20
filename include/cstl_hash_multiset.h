/*
 *  The interface of hash_multiset.
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
 *  Author Email: activesys.wb@gmail.com
 *                activesys@sina.com.cn
 */

#ifndef _CSTL_HASH_MULTISET_H
#define _CSTL_HASH_MULTISET_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
#define create_hash_multiset(type)\
    _create_hash_multiset(sizeof(type), #type)
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
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_multiset_init
 *        Parameters: in) pt_hash_multiset: hash_multiset_t*
 *                    in) pfun_hash: int (*)(const void*, size_t, size_t)
 *                          the hash function.
 *           Returns: void
 *       Description: initialize the hash_multiset.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_multiset_init(
    hash_multiset_t* pt_hash_multiset,
    int (*pfun_hash)(const void*, size_t, size_t));

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_multiset_init_n
 *        Parameters: in) pt_hash_multiset: hash_multiset_t*
 *                    in) t_bucketcount: size_t
 *                    in) pfun_hash: int (*)(const void*, size_t, size_t)
 *                          the hash function.
 *           Returns: void
 *       Description: initialize the hash_multiset.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_multiset_init_n(
    hash_multiset_t* pt_hash_multiset,
    size_t t_bucketcount,
    int (*pfun_hash)(const void*, size_t, size_t));

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_multiset_destroy
 *        Parameters: in) pt_hash_multiset: hash_multiset_t*
 *           Returns: void
 *       Description: destroy the hash_multiset.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_multiset_destroy(hash_multiset_t* pt_hash_multiset);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_multiset_init_copy
 *        Parameters: in) pt_hash_multisetdest: hash_multiset_t*
 *                        the dest avl tree pointer.
 *                    in) cpt_hash_multisetsrc: const hash_multiset_t*
 *                        the src avl tree pointer.
 *           Returns: void
 *       Description: copy the hash_multiset_t from src to dest.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_multiset_init_copy(
    hash_multiset_t* pt_hash_multisetdest, 
    const hash_multiset_t* cpt_hash_multisetsrc);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_multiset_init_copy_range
 *        Parameters: in) pt_hash_multisetdest: hash_multiset_t*
 *                        the dest hash_multiset pointer.
 *                    in) t_begin: hash_multiset_iterator_t
 *                        range begin.
 *                    in) t_end: hash_multiset_iterator_t
 *                        range end.
 *                    in) pfun_hash: int (*)(const void*, size_t, size_t)
 *           Returns: void
 *       Description: copy the hash_multiset_t from src to dest.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_multiset_init_copy_range(
    hash_multiset_t* pt_hash_multisetdest,
    hash_multiset_iterator_t t_begin,
    hash_multiset_iterator_t t_end,
    int (*pfun_hash)(const void*, size_t, size_t));

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_multiset_init_copy_range_n
 *        Parameters: in) pt_hash_multisetdest: hash_multiset_t*
 *                        the dest hash_multiset pointer.
 *                    in) t_begin: hash_multiset_iterator_t
 *                        range begin.
 *                    in) t_end: hash_multiset_iterator_t
 *                        range end.
 *                    in) t_bucketcount: size_t
 *                    in) pfun_hash: int (*)(const void*, size_t, size_t)
 *           Returns: void
 *       Description: copy the hash_multiset_t from src to dest.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_multiset_init_copy_range_n(
    hash_multiset_t* pt_hash_multisetdest,
    hash_multiset_iterator_t t_begin,
    hash_multiset_iterator_t t_end,
    size_t t_bucketcount,
    int (*pfun_hash)(const void*, size_t, size_t));

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_multiset_assign
 *        Parameters: in) pt_hash_multisetdest: hash_multiset_t*
 *                        the dest avl tree pointer.
 *                    in) cpt_hash_multisetsrc: const hash_multiset_t*
 *                        the src avl tree pointer.
 *           Returns: void
 *       Description: assign the hash_multiset_t from src to dest.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_multiset_assign(
    hash_multiset_t* pt_hash_multisetdest, 
    const hash_multiset_t* cpt_hash_multisetsrc);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_multiset_swap
 *        Parameters: in) pt_hash_multisetfirst: hash_multiset_t*
 *                          the first hash_multiset.
 *                    in) pt_hash_multisetsecond: hash_multiset_t*
 *                          the second hash_multiset.
 *           Returns: void
 *       Description: swap the datas of first hash_multiset and second hash_multiset.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_multiset_swap(
    hash_multiset_t* pt_hash_multisetfirst, 
    hash_multiset_t* pt_hash_multisetsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_multiset_size
 *        Parameters: in) cpt_hash_multiset: const hash_multiset_t*
 *                          the dest hash_multiset.
 *           Returns: size_t
 *       Description: get the hash_multiset size.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t hash_multiset_size(const hash_multiset_t* cpt_hash_multiset);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_multiset_empty
 *        Parameters: in) cpt_hash_multiset: const hash_multiset_t*
 *                          the dest hash_multiset.
 *           Returns: bool_t
 *       Description: if the hash_multiset is empty.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t hash_multiset_empty(const hash_multiset_t* cpt_hash_multiset);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_multiset_max_size
 *        Parameters: in) cpt_hash_multiset: const hash_multiset_t*
 *                          the dest hash_multiset.
 *           Returns: size_t
 *       Description: get the maximum capacity of hash_multiset.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t hash_multiset_max_size(const hash_multiset_t* cpt_hash_multiset);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_multiset_bucket_count
 *        Parameters: in) cpt_hash_multiset: const hash_multiset_t*
 *                          the dest hash_multiset.
 *           Returns: size_t
 *       Description: get the bucket count of hast table.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t hash_multiset_bucket_count(
    const hash_multiset_t* cpt_hash_multiset);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_multiset_hash_func
 *        Parameters: in) cpt_hash_multiset: const hash_multiset_t*
 *                          the hash_multiset.
 *           Returns: int (*)(const void*, size_t, size_t);
 *       Description: return the hash function.
 *
 * ----------------------------------------------------------------------------
 */
extern int (*hash_multiset_hash_func(const hash_multiset_t* cpt_hash_multiset))(
    const void*, size_t, size_t);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_multiset_key_comp
 *        Parameters: in) cpt_hash_multiset: const hash_multiset_t*
 *                          the hash_multiset.
 *           Returns: int (*)(const void*, const void*);
 *       Description: return the compare function.
 *
 * ----------------------------------------------------------------------------
 */
extern int (*hash_multiset_key_comp(const hash_multiset_t* cpt_hash_multiset))(
    const void*, const void*);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_multiset_resize
 *        Parameters: in) pt_hash_multiset: hash_multiset_t*
 *                          the _hash_multiset.
 *                    in) t_resize: size_t
 *                          the new size of _hash_multiset.
 *           Returns: void
 *       Description: change the number of elements to t_resize, if the size
 *                    grows new element create with the default 0.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_multiset_resize(
    hash_multiset_t* pt_hash_multiset, size_t t_resize);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_multiset_equal
 *        Parameters: in) cpt_hash_multisetfirst: const hash_multiset_t*
 *                          the first hash_multiset.
 *                    in) cpt_hash_multisetsecond: const hash_multiset_t*
 *                          the second hash_multiset.
 *           Returns: bool_t
 *       Description: return whether first hash_multiset equal to 
 *                    second hash_multiset.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t hash_multiset_equal(
    const hash_multiset_t* cpt_hash_multisetfirst, 
    const hash_multiset_t* cpt_hash_multisetsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_multiset_not_equal
 *        Parameters: in) cpt_hash_multisetfirst: const hash_multiset_t*
 *                          the first hash_multiset.
 *                    in) cpt_hash_multisetsecond: const hash_multiset_t*
 *                          the second hash_multiset.
 *           Returns: bool_t
 *       Description: return whether first hash_multiset not equal to 
 *                    second hash_multiset.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t hash_multiset_not_equal(
    const hash_multiset_t* cpt_hash_multisetfirst, 
    const hash_multiset_t* cpt_hash_multisetsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_multiset_begin
 *        Parameters: in) cpt_hash_multiset: const hash_multiset_t*
 *                          the hash_multiset.
 *           Returns: hash_multiset_iterator_t
 *       Description: return the random access iterator for the first element.
 *
 * ----------------------------------------------------------------------------
 */
extern hash_multiset_iterator_t hash_multiset_begin(
    const hash_multiset_t* cpt_hash_multiset);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_multiset_end
 *        Parameters: in) cpt_hash_multiset: const hash_multiset_t*
 *                          the hash_multiset.
 *           Returns: hash_multiset_iterator_t
 *       Description: return the random access iterator for the last element.
 *
 * ----------------------------------------------------------------------------
 */
extern hash_multiset_iterator_t hash_multiset_end(
    const hash_multiset_t* cpt_hash_multiset);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_multiset_insert_range
 *        Parameters: in) pt_hash_multiset: hash_multiset_t*
 *                        the rb tree pointer.
 *                    in) t_begin: hash_multiset_iterator_t
 *                        the begin iterator
 *                    in0 t_end: hash_multiset_iterator_t
 *                        the end iterator.
 *           Returns: void
 *       Description: insert a range into the hash_multiset.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_multiset_insert_range(
    hash_multiset_t* pt_hash_multiset, 
    hash_multiset_iterator_t t_begin, 
    hash_multiset_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_multiset_erase_pos
 *        Parameters: in) pt_hash_multiset: hash_multiset_t*
 *                        the rb tree pointer.
 *                    in) t_pos: hash_multiset_iterator_t
 *                        the erase iterator.
 *           Returns: void
 *       Description: erase the element pointed by t_pos.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_multiset_erase_pos(
    hash_multiset_t* pt_hash_multiset, hash_multiset_iterator_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_multiset_erase_range
 *        Parameters: in) pt_hash_multiset: hash_multiset_t*
 *                        the rb tree pointer.
 *                    in) t_begin: hash_multiset_iterator_t
 *                        the begin iterator.
 *                    in) t_end: hash_multiset_iterator_t
 *                        the end iterator.
 *           Returns: void
 *       Description: erase the all elements in the range.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_multiset_erase_range(
    hash_multiset_t* pt_hash_multiset, 
    hash_multiset_iterator_t t_begin, 
    hash_multiset_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_multiset_clear
 *        Parameters: in) pt_hash_multiset: hash_multiset_t*
 *                          the hash_multiset.
 *           Returns: void
 *       Description: remove all elements.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_multiset_clear(hash_multiset_t* pt_hash_multiset);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_HASH_MULTISET_H */
/** eof **/

