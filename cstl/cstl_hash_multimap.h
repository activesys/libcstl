/*
 *  The interface of hash_multimap.
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

#ifndef _CSTL_HASH_MULTIMAP_H_
#define _CSTL_HASH_MULTIMAP_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/**
 * Create hash_map container.
 * @param ...        element type name.
 * @return if create hash_map successfully return hash_map pointer, otherwise return NULL.
 * @remarks element type name should be C builtin type name, libcstl builtin typename or registed user defined type name,
 *          otherwise the function will return NULL.
 */
#define create_hash_multimap(...) _create_hash_multimap(#__VA_ARGS__)

/**
 * Find specific element.
 * @param cphmap_map    hash_map container.
 * @param elem         specific element.
 * @return iterator addresses the sprcific element in the hash_map, otherwise return map_end().
 * @remarks if cphmap_map == NULL then the behavior is undefined. cphmap_map must be initialized, otherwise the behavior is undefined.
 *          the type of specific element and cphmap_map must be same, otherwise the behavior is undefined.
 */
#define hash_multimap_find(cpt_hash_multimap, key_elem) _hash_multimap_find((cpt_hash_multimap), (key_elem))

/**
 * Return the number of specific elements in an hash_map
 * @param cphmap_map     hash_map container.
 * @param elem          specific element.
 * @return the number of specific elements.
 * @remarks if cphmap_map == NULL then the behavior is undefined. cphmap_map must be initialized, otherwise the behavior is undefined.
 *          the type of specific element and cphmap_map must be same, otherwise the behavior is undefined.
 */
#define hash_multimap_count(cpt_hash_multimap, key_elem) _hash_multimap_count((cpt_hash_multimap), (key_elem))

/**
 * Return an iterator range that is equal to a specific element.
 * @param cphmap_map    hash_map container.
 * @param elem         specific element.
 * @return an iterator range that is equal to a specific element.
 * @remarks if cphmap_map == NULL then the behavior is undefined. cphmap_map must be initialized, otherwise the behavior is undefined.
 *          the type of specific element and cphmap_map must be same, otherwise the behavior is undefined.
 */
#define hash_multimap_equal_range(cpt_hash_multimap, key_elem) _hash_multimap_equal_range((cpt_hash_multimap), (key_elem))

/**
 * Erase an element from a hash_map that match a specified element.
 * @param phmap_map       hash_map container.
 * @param elem           specific element.
 * @return the number of erased elements.
 * @remarks if phmap_map == NULL then the behavior is undefined. cphmap_map must be initialized, otherwise the behavior is undefined. 
 */
#define hash_multimap_erase(pt_hash_multimap, key_elem) _hash_multimap_erase((pt_hash_multimap), (key_elem))

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Initialize hash_map container.
 * @param phmap_map          hash_map container.
 * @return void.
 * @remarks if phmap_map == NULL, then the behavior is undefined, phmap_map must be created by create_map(), otherwise
 *          the behavior is undefined. the default compare function is used.
 */
extern void hash_multimap_init(hash_multimap_t* pt_hash_multimap);

/**
 * Initialize hash_map container with user define compare function.
 * @param phmap_map          hash_map container.
 * @param bfun_compare         compare function.
 * @return void.
 * @remarks if phmap_map == NULL, then the behavior is undefined, phmap_map must be created by create_map(), otherwise
 *          the behavior is undefined. if bfun_compare == NULL, the default compare function is used.
 */
extern void hash_multimap_init_ex(hash_multimap_t* pt_hash_multimap, size_t t_bucketcount, unary_function_t t_hash, binary_function_t t_compare);

/**
 * Initialize hash_map container with hash_map.
 * @param pmap_dest           destination hash_map.
 * @param cpmap_src           source hash_map.
 * @return void.
 * @remarks if pmap_dest == NULL or cpmap_src == NULL, then the behavior is undefined, pmap_dest must be created by
 *          create_map(), cpmap_src must be initialized, otherwise the behavior is undefined. the element type of
 *          pmap_dest and cpmap_src must be same, otherwise the behavior is undefine.
 */
extern void hash_multimap_init_copy(hash_multimap_t* pt_hash_multimapdest, const hash_multimap_t* cpt_hash_multimapsrc);

/**
 * Initialize hash_map container with specific range.
 * @param pmap_dest         destination hash_map.
 * @param it_begin          begin of range.
 * @param it_end            end of range.
 * @return void.
 * @remarks if pmap_dest == NULL, then the behavior is undefined, pmap_dest must be created by create_map(), otherwise
 *          the behavior is undefined. [it_begin, it_end) must be belong to a initialized hash_map, otherwise the behavior
 *          is undefined. the type of [it_begin, it_end) and pmap_dest must be same, otherwise the behavior is undefined.
 */
extern void hash_multimap_init_copy_range(hash_multimap_t* pt_hash_multimapdest, hash_multimap_iterator_t t_begin, hash_multimap_iterator_t t_end);

/**
 * Initialize hash_map container with specific range and compare function.
 * @param pmap_dest         destination hash_map.
 * @param it_begin          begin of range.
 * @param it_end            end of range.
 * @param bfun_compare         compare function.
 * @return void.
 * @remarks if pmap_dest == NULL, then the behavior is undefined, pmap_dest must be created by _create_map(), otherwise
 *          the behavior is undefined. [it_begin, it_end) must be belong to a initialized hash_map, otherwise the behavior
 *          is undefined. the type of [it_begin, it_end) and pmap_dest must be same, otherwise the behavior is undefined. if
 *          bfun_compare == NULL, then use default compare function.
 */
extern void hash_multimap_init_copy_range_ex(
    hash_multimap_t* pt_hash_multimapdest, hash_multimap_iterator_t t_begin, hash_multimap_iterator_t t_end,
    size_t t_bucketcount, unary_function_t t_hash, binary_function_t t_compare);

/**
 * Destroy hash_map.
 * @param phmap_map       hash_map container.
 * @return void.
 * @remarks if phmap_map == NULL, then the behavior is undefined, the hash_map must be initialized or created by create_map(),
 *          otherwise the behavior is undefined.
 */
extern void hash_multimap_destroy(hash_multimap_t* pt_hash_multimap);

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
extern binary_function_t hash_multimap_key_comp(const hash_multimap_t* cpt_hash_multimap);
extern binary_function_t hash_multimap_value_comp(const hash_multimap_t* cpt_hash_multimap);

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
extern bool_t hash_multimap_greater(
    const hash_multimap_t* cpt_hash_multimapfirst,
    const hash_multimap_t* cpt_hash_multimapsecond);
extern bool_t hash_multimap_greater_equal(
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

#endif /* _CSTL_HASH_MULTIMAP_H_ */
/** eof **/

