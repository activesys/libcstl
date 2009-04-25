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
#define create_hash_map(key_type, value_type)\
    _create_hash_map(\
        sizeof(key_type), #key_type, \
        sizeof(value_type), #value_type)
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
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_map_init
 *        Parameters: in) pt_hash_map: hash_map_t*
 *                    in) pfun_hash: int (*)(const void*, size_t, size_t)
 *                          the hash function.
 *           Returns: void
 *       Description: initialize the hash_map.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_map_init(
    hash_map_t* pt_hash_map, int (*pfun_hash)(const void*, size_t, size_t));

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_map_init_n
 *        Parameters: in) pt_hash_map: hash_map_t*
 *                    in) t_bucketcount: size_t
 *                    in) pfun_hash: int (*)(const void*, size_t, size_t)
 *                          the hash function.
 *           Returns: void
 *       Description: initialize the hash_map.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_map_init_n(
    hash_map_t* pt_hash_map, size_t t_bucketcount,
    int (*pfun_hash)(const void*, size_t, size_t));

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_map_destroy
 *        Parameters: in) pt_hash_map: hash_map_t*
 *           Returns: void
 *       Description: destroy the hash_map.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_map_destroy(hash_map_t* pt_hash_map);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_map_init_copy
 *        Parameters: in) pt_hash_mapdest: hash_map_t*
 *                        the dest hash_map pointer.
 *                    in) cpt_hash_mapsrc: const hash_map_t*
 *                        the src hash_map pointer.
 *           Returns: void
 *       Description: copy the hash_map_t from src to dest.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_map_init_copy(
    hash_map_t* pt_hash_mapdest, const hash_map_t* cpt_hash_mapsrc);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_map_init_copy_range
 *        Parameters: in) pt_hash_mapdest: hash_map_t*
 *                        the dest hash_map pointer.
 *                    in) t_begin: hash_map_iterator_t
 *                        range begin.
 *                    in) t_end: hash_map_iterator_t
 *                        range end.
 *                    in) pfun_hash: int (*)(const void*, size_t, size_t)
 *           Returns: void
 *       Description: copy the hash_map_t from src to dest.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_map_init_copy_range(
    hash_map_t* pt_hash_mapdest,
    hash_map_iterator_t t_begin,
    hash_map_iterator_t t_end,
    int (*pfun_hash)(const void*, size_t, size_t));

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_map_init_copy_range_n
 *        Parameters: in) pt_hash_mapdest: hash_map_t*
 *                        the dest hash_map pointer.
 *                    in) t_begin: hash_map_iterator_t
 *                        range begin.
 *                    in) t_end: hash_map_iterator_t
 *                        range end.
 *                    in) t_bucketcount: size_t
 *                    in) pfun_hash: int (*)(const void*, size_t, size_t)
 *           Returns: void
 *       Description: copy the hash_map_t from src to dest.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_map_init_copy_range_n(
    hash_map_t* pt_hash_mapdest,
    hash_map_iterator_t t_begin,
    hash_map_iterator_t t_end,
    size_t t_bucketcount,
    int (*pfun_hash)(const void*, size_t, size_t));

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_map_assign
 *        Parameters: in) pt_hash_mapdest: hash_map_t*
 *                        the dest hash_map pointer.
 *                    in) cpt_hash_mapsrc: const hash_map_t*
 *                        the src hash_map pointer.
 *           Returns: void
 *       Description: assign the hash_map_t from src to dest.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_map_assign(
    hash_map_t* pt_hash_mapdest, const hash_map_t* cpt_hash_mapsrc);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_map_swap
 *        Parameters: in) pt_hash_mapfirst: hash_map_t*
 *                          the first hash_map.
 *                    in) pt_hash_mapsecond: hash_map_t*
 *                          the second hash_map.
 *           Returns: void
 *       Description: swap the datas of first hash_map and second hash_map.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_map_swap(
    hash_map_t* pt_hash_mapfirst, hash_map_t* pt_hash_mapsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_map_size
 *        Parameters: in) cpt_hash_map: const hash_map_t*
 *                          the dest hash_map.
 *           Returns: size_t
 *       Description: get the hash_map size.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t hash_map_size(const hash_map_t* cpt_hash_map);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_map_empty
 *        Parameters: in) cpt_hash_map: const hash_map_t*
 *                          the dest hash_map.
 *           Returns: bool_t
 *       Description: if the hash_map is empty.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t hash_map_empty(const hash_map_t* cpt_hash_map);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_map_max_size
 *        Parameters: in) cpt_hash_map: const hash_map_t*
 *                          the dest hash_map.
 *           Returns: size_t
 *       Description: get the maximum capacity of hash_map.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t hash_map_max_size(const hash_map_t* cpt_hash_map);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_map_bucket_count
 *        Parameters: in) cpt_hash_map: const hash_map_t*
 *                          the dest hash_map.
 *           Returns: size_t
 *       Description: get the bucket count of hast table.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t hash_map_bucket_count(const hash_map_t* cpt_hash_map);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_map_hash_func
 *        Parameters: in) cpt_hash_map: const hash_map_t*
 *                          the hash_map.
 *           Returns: int (*)(const void*, size_t, size_t);
 *       Description: return the hash function.
 *
 * ----------------------------------------------------------------------------
 */
extern int (*hash_map_hash_func(const hash_map_t* cpt_hash_map))(
    const void*, size_t, size_t);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_map_key_comp
 *        Parameters: in) cpt_hash_map: const hash_map_t*
 *                          the hash_map.
 *           Returns: int (*)(const void*, const void*);
 *       Description: return the compare function.
 *
 * ----------------------------------------------------------------------------
 */
extern int (*hash_map_key_comp(const hash_map_t* cpt_hash_map))(
    const void*, const void*);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_map_resize
 *        Parameters: in) pt_hash_map: hash_map_t*
 *                          the _hash_map.
 *                    in) t_resize: size_t
 *                          the new size of _hash_map.
 *           Returns: void
 *       Description: change the number of elements to t_resize, if the size
 *                    grows new element create with the default 0.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_map_resize(hash_map_t* pt_hash_map, size_t t_resize);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_map_begin
 *        Parameters: in) cpt_hash_map: const hash_map_t*
 *                          the hash_map.
 *           Returns: hash_map_iterator_t
 *       Description: return the random access iterator for the first element.
 *
 * ----------------------------------------------------------------------------
 */
extern hash_map_iterator_t hash_map_begin(const hash_map_t* cpt_hash_map);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_map_end
 *        Parameters: in) cpt_hash_map: const hash_map_t*
 *                          the hash_map.
 *           Returns: hash_map_iterator_t
 *       Description: return the random access iterator for the last element.
 *
 * ----------------------------------------------------------------------------
 */
extern hash_map_iterator_t hash_map_end(const hash_map_t* cpt_hash_map);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_map_equal
 *        Parameters: in) cpt_hash_mapfirst: const hash_map_t*
 *                          the first hash_map.
 *                    in) cpt_hash_mapsecond: const hash_map_t*
 *                          the second hash_map.
 *           Returns: bool_t
 *       Description: return whether first hash_map equal to second hash_map.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t hash_map_equal(
    const hash_map_t* cpt_hash_mapfirst, 
    const hash_map_t* cpt_hash_mapsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_map_not_equal
 *        Parameters: in) cpt_hash_mapfirst: const hash_map_t*
 *                          the first hash_map.
 *                    in) cpt_hash_mapsecond: const hash_map_t*
 *                          the second hash_map.
 *           Returns: bool_t
 *       Description: return whether first hash_map not equal to second hash_map.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t hash_map_not_equal(
    const hash_map_t* cpt_hash_mapfirst, 
    const hash_map_t* cpt_hash_mapsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_map_insert
 *        Parameters: in) pt_hash_map: hash_map_t*
 *                        the hash_map pointer.
 *                    in) cpt_pair: const pair_t*
 *                        the element pair.
 *           Returns: hash_map_iterator_t
 *                        the insert result.
 *       Description: insert value into hash_map.
 *
 * ----------------------------------------------------------------------------
 */
extern hash_map_iterator_t hash_map_insert(
    hash_map_t* pt_hash_map, const pair_t* cpt_pair);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_map_insert_range
 *        Parameters: in) pt_hash_map: hash_map_t*
 *                        the rb tree pointer.
 *                    in) t_begin: hash_map_iterator_t
 *                        the begin iterator
 *                    in0 t_end: hash_map_iterator_t
 *                        the end iterator.
 *           Returns: void
 *       Description: insert a range into the hash_map.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_map_insert_range(
    hash_map_t* pt_hash_map, 
    hash_map_iterator_t t_begin, 
    hash_map_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_map_erase_pos
 *        Parameters: in) pt_hash_map: hash_map_t*
 *                        the rb tree pointer.
 *                    in) t_pos: hash_map_iterator_t
 *                        the erase iterator.
 *           Returns: void
 *       Description: erase the element pointed by t_pos.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_map_erase_pos(
    hash_map_t* pt_hash_map, hash_map_iterator_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_map_erase_range
 *        Parameters: in) pt_hash_map: hash_map_t*
 *                        the rb tree pointer.
 *                    in) t_begin: hash_map_iterator_t
 *                        the begin iterator.
 *                    in) t_end: hash_map_iterator_t
 *                        the end iterator.
 *           Returns: void
 *       Description: erase the all elements in the range.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_map_erase_range(
    hash_map_t* pt_hash_map, 
    hash_map_iterator_t t_begin, 
    hash_map_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: hash_map_clear
 *        Parameters: in) pt_hash_map: hash_map_t*
 *                          the hash_map.
 *           Returns: void
 *       Description: remove all elements.
 *
 * ----------------------------------------------------------------------------
 */
extern void hash_map_clear(hash_map_t* pt_hash_map);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_HASH_MAP_H */
/** eof **/

