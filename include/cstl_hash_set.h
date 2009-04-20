/*
 *  The interface of hash_set.
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

#ifndef _CSTL_HASH_SET_H
#define _CSTL_HASH_SET_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
#define create_hash_set(type)\
    _create_hash_set(sizeof(type), #type)
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
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_set_init
 *        Parameters: in) pt_hash_set: hash_set_t*
 *                    in) pfun_hash: int (*)(const void*, size_t, size_t)
 *                          the hash function.
 *           Returns: void
 *       Description: initialize the hash_set.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_set_init(
    hash_set_t* pt_hash_set,
    int (*pfun_hash)(const void*, size_t, size_t));

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_set_init_n
 *        Parameters: in) pt_hash_set: hash_set_t*
 *                    in) t_bucketcount: size_t
 *                    in) pfun_hash: int (*)(const void*, size_t, size_t)
 *                          the hash function.
 *           Returns: void
 *       Description: initialize the hash_set.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_set_init_n(
    hash_set_t* pt_hash_set,
    size_t t_bucketcount,
    int (*pfun_hash)(const void*, size_t, size_t));

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_set_destroy
 *        Parameters: in) pt_hash_set: hash_set_t*
 *           Returns: void
 *       Description: destroy the hash_set.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_set_destroy(hash_set_t* pt_hash_set);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_set_init_copy
 *        Parameters: in) pt_hash_setdest: hash_set_t*
 *                        the dest avl tree pointer.
 *                    in) cpt_hash_setsrc: const hash_set_t*
 *                        the src avl tree pointer.
 *           Returns: void
 *       Description: copy the hash_set_t from src to dest.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_set_init_copy(
    hash_set_t* pt_hash_setdest, const hash_set_t* cpt_hash_setsrc);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_set_init_copy_range
 *        Parameters: in) pt_hash_setdest: hash_set_t*
 *                        the dest hash_set pointer.
 *                    in) t_begin: hash_set_iterator_t
 *                        range begin.
 *                    in) t_end: hash_set_iterator_t
 *                        range end.
 *                    in) pfun_hash: int (*)(const void*, size_t, size_t)
 *           Returns: void
 *       Description: copy the hash_set_t from src to dest.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_set_init_copy_range(
    hash_set_t* pt_hash_setdest,
    hash_set_iterator_t t_begin,
    hash_set_iterator_t t_end,
    int (*pfun_hash)(const void*, size_t, size_t));

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_set_init_copy_range_n
 *        Parameters: in) pt_hash_setdest: hash_set_t*
 *                        the dest hash_set pointer.
 *                    in) t_begin: hash_set_iterator_t
 *                        range begin.
 *                    in) t_end: hash_set_iterator_t
 *                        range end.
 *                    in) t_bucketcount: size_t
 *                    in) pfun_hash: int (*)(const void*, size_t, size_t)
 *           Returns: void
 *       Description: copy the hash_set_t from src to dest.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_set_init_copy_range_n(
    hash_set_t* pt_hash_setdest,
    hash_set_iterator_t t_begin,
    hash_set_iterator_t t_end,
    size_t t_bucketcount,
    int (*pfun_hash)(const void*, size_t, size_t));

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_set_assign
 *        Parameters: in) pt_hash_setdest: hash_set_t*
 *                        the dest avl tree pointer.
 *                    in) cpt_hash_setsrc: const hash_set_t*
 *                        the src avl tree pointer.
 *           Returns: void
 *       Description: assign the hash_set_t from src to dest.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_set_assign(
    hash_set_t* pt_hash_setdest, const hash_set_t* cpt_hash_setsrc);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_set_swap
 *        Parameters: in) pt_hash_setfirst: hash_set_t*
 *                          the first hash_set.
 *                    in) pt_hash_setsecond: hash_set_t*
 *                          the second hash_set.
 *           Returns: void
 *       Description: swap the datas of first hash_set and second hash_set.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_set_swap(
    hash_set_t* pt_hash_setfirst, hash_set_t* pt_hash_setsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_set_size
 *        Parameters: in) cpt_hash_set: const hash_set_t*
 *                          the dest hash_set.
 *           Returns: size_t
 *       Description: get the hash_set size.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t hash_set_size(const hash_set_t* cpt_hash_set);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_set_empty
 *        Parameters: in) cpt_hash_set: const hash_set_t*
 *                          the dest hash_set.
 *           Returns: bool_t
 *       Description: if the hash_set is empty.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t hash_set_empty(const hash_set_t* cpt_hash_set);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_set_max_size
 *        Parameters: in) cpt_hash_set: const hash_set_t*
 *                          the dest hash_set.
 *           Returns: size_t
 *       Description: get the maximum capacity of hash_set.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t hash_set_max_size(const hash_set_t* cpt_hash_set);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_set_bucket_count
 *        Parameters: in) cpt_hash_set: const hash_set_t*
 *                          the dest hash_set.
 *           Returns: size_t
 *       Description: get the bucket count of hast table.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t hash_set_bucket_count(const hash_set_t* cpt_hash_set);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_set_hash_func
 *        Parameters: in) cpt_hash_set: const hash_set_t*
 *                          the hash_set.
 *           Returns: int (*)(const void*, size_t, size_t);
 *       Description: return the hash function.
 *
 * ----------------------------------------------------------------------------
 */
extern int (*hash_set_hash_func(const hash_set_t* cpt_hash_set))(
    const void*, size_t, size_t);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_set_key_comp
 *        Parameters: in) cpt_hash_set: const hash_set_t*
 *                          the hash_set.
 *           Returns: int (*)(const void*, const void*);
 *       Description: return the compare function.
 *
 * ----------------------------------------------------------------------------
 */
extern int (*hash_set_key_comp(const hash_set_t* cpt_hash_set))(
    const void*, const void*);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_set_resize
 *        Parameters: in) pt_hash_set: hash_set_t*
 *                          the _hash_set.
 *                    in) t_resize: size_t
 *                          the new size of _hash_set.
 *           Returns: void
 *       Description: change the number of elements to t_resize, if the size
 *                    grows new element create with the default 0.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_set_resize(hash_set_t* pt_hash_set, size_t t_resize);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_set_equal
 *        Parameters: in) cpt_hash_setfirst: const hash_set_t*
 *                          the first hash_set.
 *                    in) cpt_hash_setsecond: const hash_set_t*
 *                          the second hash_set.
 *           Returns: bool_t
 *       Description: return whether first hash_set equal to second hash_set.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t hash_set_equal(
    const hash_set_t* cpt_hash_setfirst, 
    const hash_set_t* cpt_hash_setsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_set_not_equal
 *        Parameters: in) cpt_hash_setfirst: const hash_set_t*
 *                          the first hash_set.
 *                    in) cpt_hash_setsecond: const hash_set_t*
 *                          the second hash_set.
 *           Returns: bool_t
 *       Description: return whether first hash_set not equal to second hash_set.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t hash_set_not_equal(
    const hash_set_t* cpt_hash_setfirst, 
    const hash_set_t* cpt_hash_setsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_set_begin
 *        Parameters: in) cpt_hash_set: const hash_set_t*
 *                          the hash_set.
 *           Returns: hash_set_iterator_t
 *       Description: return the random access iterator for the first element.
 *
 * ----------------------------------------------------------------------------
 */
extern hash_set_iterator_t hash_set_begin(const hash_set_t* cpt_hash_set);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_set_end
 *        Parameters: in) cpt_hash_set: const hash_set_t*
 *                          the hash_set.
 *           Returns: hash_set_iterator_t
 *       Description: return the random access iterator for the last element.
 *
 * ----------------------------------------------------------------------------
 */
extern hash_set_iterator_t hash_set_end(const hash_set_t* cpt_hash_set);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_set_insert_range
 *        Parameters: in) pt_hash_set: hash_set_t*
 *                        the rb tree pointer.
 *                    in) t_begin: hash_set_iterator_t
 *                        the begin iterator
 *                    in0 t_end: hash_set_iterator_t
 *                        the end iterator.
 *           Returns: void
 *       Description: insert a range into the hash_set.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_set_insert_range(
    hash_set_t* pt_hash_set, 
    hash_set_iterator_t t_begin, 
    hash_set_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_set_erase_pos
 *        Parameters: in) pt_hash_set: hash_set_t*
 *                        the rb tree pointer.
 *                    in) t_pos: hash_set_iterator_t
 *                        the erase iterator.
 *           Returns: void
 *       Description: erase the element pointed by t_pos.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_set_erase_pos(
    hash_set_t* pt_hash_set, hash_set_iterator_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_set_erase_range
 *        Parameters: in) pt_hash_set: hash_set_t*
 *                        the rb tree pointer.
 *                    in) t_begin: hash_set_iterator_t
 *                        the begin iterator.
 *                    in) t_end: hash_set_iterator_t
 *                        the end iterator.
 *           Returns: void
 *       Description: erase the all elements in the range.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_set_erase_range(
    hash_set_t* pt_hash_set, 
    hash_set_iterator_t t_begin, 
    hash_set_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_set_clear
 *        Parameters: in) pt_hash_set: hash_set_t*
 *                          the hash_set.
 *           Returns: void
 *       Description: remove all elements.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_set_clear(hash_set_t* pt_hash_set);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_HASH_SET_H */
/** eof **/

