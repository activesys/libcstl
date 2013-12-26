/*
 *  The interface of hash_map.
 *  Copyright (C)  2008 - 2014  Wangbo
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

#ifndef _CSTL_HASH_MAP_H_
#define _CSTL_HASH_MAP_H_

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
#define create_hash_map(...) _create_hash_map(#__VA_ARGS__)

/**
 * Find specific element.
 * @param cphmap_map    hash_map container.
 * @param elem         specific element.
 * @return iterator addresses the sprcific element in the hash_map, otherwise return map_end().
 * @remarks if cphmap_map == NULL then the behavior is undefined. cphmap_map must be initialized, otherwise the behavior is undefined.
 *          the type of specific element and cphmap_map must be same, otherwise the behavior is undefined.
 */
#define hash_map_find(cphmap_map, key_elem) _hash_map_find((cphmap_map), (key_elem))

/**
 * Return the number of specific elements in an hash_map
 * @param cphmap_map     hash_map container.
 * @param elem          specific element.
 * @return the number of specific elements.
 * @remarks if cphmap_map == NULL then the behavior is undefined. cphmap_map must be initialized, otherwise the behavior is undefined.
 *          the type of specific element and cphmap_map must be same, otherwise the behavior is undefined.
 */
#define hash_map_count(cphmap_map, key_elem) _hash_map_count((cphmap_map), (key_elem))

/**
 * Return an iterator range that is equal to a specific element.
 * @param cphmap_map    hash_map container.
 * @param elem         specific element.
 * @return an iterator range that is equal to a specific element.
 * @remarks if cphmap_map == NULL then the behavior is undefined. cphmap_map must be initialized, otherwise the behavior is undefined.
 *          the type of specific element and cphmap_map must be same, otherwise the behavior is undefined.
 */
#define hash_map_equal_range(cphmap_map, key_elem) _hash_map_equal_range((cphmap_map), (key_elem))

/**
 * Access an element with specific index.
 * @param phmap_map          hash_map container.
 * @param key_elem          key element.
 * @return the pointer that point to the second element.
 * @remarks if phmap_map == NULL then the behavior is undefined. cphmap_map must be initialized, otherwise the behavior is
 *          undefined. 
 */
#define hash_map_at(phmap_map, key_elem) _hash_map_at((phmap_map), (key_elem))

/**
 * Erase an element from a hash_map that match a specified element.
 * @param phmap_map       hash_map container.
 * @param elem           specific element.
 * @return the number of erased elements.
 * @remarks if phmap_map == NULL then the behavior is undefined. cphmap_map must be initialized, otherwise the behavior is undefined. 
 */
#define hash_map_erase(phmap_map, key_elem) _hash_map_erase((phmap_map), (key_elem))

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
extern void hash_map_init(hash_map_t* phmap_map);

/**
 * Initialize hash_map container with user define compare function.
 * @param phmap_map          hash_map container.
 * @param bfun_compare         compare function.
 * @return void.
 * @remarks if phmap_map == NULL, then the behavior is undefined, phmap_map must be created by create_map(), otherwise
 *          the behavior is undefined. if bfun_compare == NULL, the default compare function is used.
 */
extern void hash_map_init_ex(hash_map_t* phmap_map, size_t t_bucketcount, ufun_t ufun_hash, bfun_t bfun_compare);

/**
 * Initialize hash_map container with hash_map.
 * @param pmap_dest           destination hash_map.
 * @param cpmap_src           source hash_map.
 * @return void.
 * @remarks if pmap_dest == NULL or cpmap_src == NULL, then the behavior is undefined, pmap_dest must be created by
 *          create_map(), cpmap_src must be initialized, otherwise the behavior is undefined. the element type of
 *          pmap_dest and cpmap_src must be same, otherwise the behavior is undefine.
 */
extern void hash_map_init_copy(hash_map_t* phmap_dest, const hash_map_t* cphmap_src);

/**
 * Initialize hash_map container with specific range.
 * @param pmap_dest         destination hash_map.
 * @param it_begin          begin of range.
 * @param it_end            end of range.
 * @return void.
 * @remarks if pmap_dest == NULL, then the behavior is undefined, pmap_dest must be created by create_map(), otherwise
 *          the behavior is undefined. the type of [it_begin, it_end) and pmap_dest must be same, otherwise the behavior
 *          is undefined.
 */
extern void hash_map_init_copy_range(hash_map_t* phmap_dest, iterator_t it_begin, iterator_t it_end);

/**
 * Initialize hash_map container with specific array.
 * @param pmap_dest         destination hash_map.
 * @param cpv_array         array.
 * @param t_count           element count of array.
 * @return void.
 * @remarks if pmap_dest == NULL, then the behavior is undefined, pmap_dest must be created by create_map(), otherwise
 *          the behavior is undefined. the type of array and pmap_dest must be same, otherwise the behavior is undefined.
 */
extern void hash_map_init_copy_array(hash_map_t* phmap_dest, const void* cpv_array, size_t t_count);

/**
 * Initialize hash_map container with specific range and compare function.
 * @param pmap_dest         destination hash_map.
 * @param it_begin          begin of range.
 * @param it_end            end of range.
 * @param bfun_compare      compare function.
 * @return void.
 * @remarks if pmap_dest == NULL, then the behavior is undefined, pmap_dest must be created by _create_map(), otherwise
 *          the behavior is undefined. is undefined. the type of [it_begin, it_end) and pmap_dest must be same, otherwise 
 *          the behavior is undefined. if bfun_compare == NULL, then use default compare function.
 */
extern void hash_map_init_copy_range_ex(hash_map_t* phmap_dest, iterator_t it_begin, iterator_t it_end,
    size_t t_bucketcount, ufun_t ufun_hash, bfun_t bfun_compare);

/**
 * Initialize hash_map container with specific array and compare function.
 * @param pmap_dest         destination hash_map.
 * @param cpv_array         array.
 * @param t_count           element count of array.
 * @param bfun_compare      compare function.
 * @return void.
 * @remarks if pmap_dest == NULL, then the behavior is undefined, pmap_dest must be created by _create_map(), otherwise
 *          the behavior is undefined. is undefined. the type of array and pmap_dest must be same, otherwise the behavior
 *          is undefined. if bfun_compare == NULL, then use default compare function.
 */
extern void hash_map_init_copy_array_ex(hash_map_t* phmap_dest, const void* cpv_array, size_t t_count,
    size_t t_bucketcount, ufun_t ufun_hash, bfun_t bfun_compare);

/**
 * Destroy hash_map.
 * @param phmap_map       hash_map container.
 * @return void.
 * @remarks if phmap_map == NULL, then the behavior is undefined, the hash_map must be initialized or created by create_map(),
 *          otherwise the behavior is undefined.
 */
extern void hash_map_destroy(hash_map_t* phmap_map);

/**
 * Assign hash_map container.
 * @param pmap_dest           destination hash_map container.
 * @param cpmap_src           source hash_map container.
 * @return void.
 * @remarks if pmap_dest == NULL or cpmap_src == NULL, the the behavior is undefined. two hash_map must be initialized, otherwise
 *          the behavior is undefined. if map_equal(pmap_dest, cpmap_src), the function dest nothing.
 */
extern void hash_map_assign(hash_map_t* phmap_dest, const hash_map_t* cphmap_src);

/**
 * Swap the datas of first hash_map and second hash_map.
 * @param pt_first          first hash_map container.
 * @param pt_second         second hash_map container.
 * @return void.
 * @remarks if pt_first == NULL or pt_second == NULL, then the behavior is undefined. the two hash_map must be initialized,
 *          otherwise the behavior is undefined. if the two hash_map are not same type, the behavior is undefined. if
 *          map_equal(cpt_first, cpt_second), then the function do nothing.
 */
extern void hash_map_swap(hash_map_t* phmap_first, hash_map_t* phmap_second);

/**
 * Get the number of elements int the hash_map.
 * @param cphmap_map      hash_map container.
 * @return the number of elements in the hash_map.
 * @remarks if cphmap_map == NULL, then the behavior is undefined, the cphmap_map must be initialized, otherwise the behavior
 *          is undefined.
 */
extern size_t hash_map_size(const hash_map_t* cphmap_map);

/**
 * Test if an hash_map is empty.
 * @param cphmap_map      hash_map container.
 * @return true if the hash_map is empty, otherwise return false.
 * @remarks if cphmap_map == NULL, then the behavior is undefined, the cphmap_map must be initialized, otherwise the behavior
 *          is undefined.
 */
extern bool_t hash_map_empty(const hash_map_t* cphmap_map);

/**
 * Get the maximum number of elements int the hash_map.
 * @param cphmap_map      hash_map container.
 * @return the maximum number of elements in the hash_map.
 * @remarks if cphmap_map == NULL, then the behavior is undefined, the cphmap_map must be initialized, otherwise the behavior
 *          is undefined.
 */
extern size_t hash_map_max_size(const hash_map_t* cphmap_map);

/**
 * Get the bucket count of elements int the hash_map.
 * @param cphmap_map      hash_map container.
 * @return the bucket count of elements in the hash_map.
 * @remarks if cphmap_map == NULL, then the behavior is undefined, the cphmap_map must be initialized, otherwise the behavior
 *          is undefined.
 */
extern size_t hash_map_bucket_count(const hash_map_t* cphmap_map);

/**
 * Return the hash function of value.
 * @param cphmap_map      hash_map container.
 * @return compare function.
 * @remarks if cphmap_map == NULL, the behavior is undefined. cphmap_map must be initialized, otherwise the behavior is undefined.
 */
extern ufun_t hash_map_hash(const hash_map_t* cphmap_map);

/**
 * Return the compare function of key.
 * @param cphmap_map      hash_map container.
 * @return compare function.
 * @remarks if cphmap_map == NULL, the behavior is undefined. cphmap_map must be initialized, otherwise the behavior is undefined.
 */
extern bfun_t hash_map_key_comp(const hash_map_t* cphmap_map);

/**
 * Return the compare function of value.
 * @param cphmap_map      hash_map container.
 * @return compare function.
 * @remarks if cphmap_map == NULL, the behavior is undefined. cphmap_map must be initialized, otherwise the behavior is undefined.
 */
extern bfun_t hash_map_value_comp(const hash_map_t* cphmap_map);

/**
 * Resize bucket count of hash map.
 * @param cphmap_map      hash_map container.
 * @return void.
 * @remarks if cphmap_map == NULL, the behavior is undefined. cphmap_map must be initialized, otherwise the behavior is undefined.
 */
extern void hash_map_resize(hash_map_t* phmap_map, size_t t_resize);

/**
 * Return an iterator that addresses the first element in the hash_map.
 * @param cphmap_map      hash_map container.
 * @return an iterator that addresses the first element in the hash_map.
 * @remarks if cphmap_map == NULL, the behavior is undefined. cphmap_map must be initialized, otherwise the behavior is undefined.
 *          return map_end(), if the hash_map is empty.
 */
extern hash_map_iterator_t hash_map_begin(const hash_map_t* cphmap_map);

/**
 * Return an iterator that addresses the location succeeding the last element in the hash_map.
 * @param cphmap_map      hash_map container.
 * @return an iterator that addresses location succeeding the last element in the hash_map.
 * @remarks if cphmap_map == NULL, the behavior is undefined. cphmap_map must be initialized, otherwise the behavior is undefined.
 */
extern hash_map_iterator_t hash_map_end(const hash_map_t* cphmap_map);

/**
 * Tests if the two hash_map are equal.
 * @param cpmap_first         first hash_map container.
 * @param cpmap_second        second hash_map container.
 * @return if first hash_map equal to second hash_map, then return true, else return false.
 * @remarks if cpmap_first == NULL or cpmap_second == NULL, then the behavior is undefined. the two hash_map must be
 *          initialized, otherwise the behavior is undefined. if the two hash_map are not same type, then return false.
 *          if cpmap_first == cpmap_second, then return true.
 */
extern bool_t hash_map_equal(const hash_map_t* cphmap_first, const hash_map_t* cphmap_second);

/**
 * Tests if the two hash_map are not equal.
 * @param cpmap_first         first hash_map container.
 * @param cpmap_second        second hash_map container.
 * @return if first hash_map not equal to second hash_map, then return true, else return false.
 * @remarks if cpmap_first == NULL or cpmap_second == NULL, then the behavior is undefined. the two hash_map must be
 *          initialized, otherwise the behavior is undefined. if the two hash_map are not same type, then return false.
 *          if cpmap_first == cpmap_second, then return false.
 */
extern bool_t hash_map_not_equal(const hash_map_t* cphmap_first, const hash_map_t* cphmap_second);

/**
 * Tests if the first hash_map is less than the second hash_map.
 * @param cpmap_first         first hash_map container.
 * @param cpmap_second        second hash_map container.
 * @return if first hash_map is less than the second hash_map, then return true, else return false.
 * @remarks if cpmap_first == NULL or cpmap_second == NULL, then the behavior is undefined. the two hash_map must be
 *          initialized, otherwise the behavior is undefined. if the two hash_map are not same type, the behavior is
 *          undefined. if cpmap_first == cpmap_second, then return false.
 */
extern bool_t hash_map_less(const hash_map_t* cphmap_first, const hash_map_t* cphmap_second);

/**
 * Tests if the first hash_map is less than or equal to the second hash_map.
 * @param cpmap_first         first hash_map container.
 * @param cpmap_second        second hash_map container.
 * @return if first hash_map is less than or equal to the second hash_map, then return true, else return false.
 * @remarks if cpmap_first == NULL or cpmap_second == NULL, then the behavior is undefined. the two hash_map must be
 *          initialized, otherwise the behavior is undefined. if the two hash_map are not same type, the behavior is
 *          undefined. if cpmap_first == cpmap_second, then return true.
 */
extern bool_t hash_map_less_equal(const hash_map_t* cphmap_first, const hash_map_t* cphmap_second);

/**
 * Tests if the first hash_map is greater than the second hash_map.
 * @param cpmap_first         first hash_map container.
 * @param cpmap_second        second hash_map container.
 * @return if first hash_map is greater than the second hash_map, then return true, else return false.
 * @remarks if cpmap_first == NULL or cpmap_second == NULL, then the behavior is undefined. the two hash_map must be
 *          initialized, otherwise the behavior is undefined. if the two hash_map are not same type, the behavior is
 *          undefined. if cpmap_first == cpmap_second, then return false.
 */
extern bool_t hash_map_greater(const hash_map_t* cphmap_first, const hash_map_t* cphmap_second);

/**
 * Tests if the first hash_map is greater than or equal to the second hash_map.
 * @param cpmap_first         first hash_map container.
 * @param cpmap_second        second hash_map container.
 * @return if first hash_map is greater than or equal to the second hash_map, then return true, else return false.
 * @remarks if cpmap_first == NULL or cpmap_second == NULL, then the behavior is undefined. the two hash_map must be
 *          initialized, otherwise the behavior is undefined. if the two hash_map are not same type, the behavior is
 *          undefined. if cpmap_first == cpmap_second, then return true.
 */
extern bool_t hash_map_greater_equal(const hash_map_t* cphmap_first, const hash_map_t* cphmap_second);

/**
 * Inserts an unique element into a hash_map.
 * @param phmap_map       hash_map container.
 * @param cppair_pair    specific element.
 * @return an iterator addresses the inserted element, or hash_map end if insert failed.
 * @remarks if phmap_map == NULL then the behavior is undefined. cphmap_map must be initialized, otherwise the behavior is undefined.
 *          the type of specific element and cphmap_map must be same, otherwise the behavior is undefined.
 */
extern hash_map_iterator_t hash_map_insert(hash_map_t* phmap_map, const pair_t* cpt_pair);

/**
 * Inserts an range of unique element into a hash_map.
 * @param phmap_map          hash_map container.
 * @param it_begin          begin of specific range.
 * @param it_end            end of specific range.
 * @return void.
 * @remarks if phmap_map == NULL then the behavior is undefined. phmap_map must be initialized, otherwise the behavior
 *          is undefined. the type of [it_begin, it_end) and cphmap_map must be same, otherwise the behavior is undefined.
 *          [it_begin, it_end) must be valid range, otherwise the behavior is undefine.
 */
extern void hash_map_insert_range(hash_map_t* phmap_map, iterator_t it_begin, iterator_t it_end);

/**
 * Inserts an array of unique element into a hash_map.
 * @param phmap_map          hash_map container.
 * @param cpv_array          array.
 * @param t_count            element count of array.
 * @return void.
 * @remarks if phmap_map == NULL then the behavior is undefined. phmap_map must be initialized, otherwise the behavior
 *          is undefined. the type of [it_begin, it_end) and cphmap_map must be same, otherwise the behavior is undefined.
 *          array must be valid, otherwise the behavior is undefine.
 */
extern void hash_map_insert_array(hash_map_t* phmap_map, const void* cpv_array, size_t t_count);

/*
 * Erase an element in an hash_map from specificed position.
 * @param phmap_map          hash_map container.
 * @param it_pos            specificed position.
 * @return void.
 * @remarks if phmap_map == NULL then the behavior is undefined. phmap_map must be initialized, otherwise the behavior
 *          is undefined. it_pos must be valid iterator, otherwise the behavior is undefined.
 */
extern void hash_map_erase_pos(hash_map_t* phmap_map, hash_map_iterator_t it_pos);

/*
 * Erase a range of element in an hash_map.
 * @param phmap_map          hash_map container.
 * @param it_begin          begin of specific range.
 * @param it_end            end of specific range.
 * @return void.
 * @remarks if phmap_map == NULL then the behavior is undefined. phmap_map must be initialized, otherwise the behavior
 *          is undefined. [it_begin, it_end) must be valid range for phmap_map, otherwise the behavior is undefine.
 */
extern void hash_map_erase_range(hash_map_t* phmap_map, hash_map_iterator_t it_begin, hash_map_iterator_t it_end);

/**
 * Erases all the elements of an hash_map.
 * @param phmap_map       hash_map container.
 * @return void.
 * @remarks if phmap_map == NULL, the behavior is undefined. phmap_map must be initialized, otherwise the behavior is undefined.
 */
extern void hash_map_clear(hash_map_t* phmap_map);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_HASH_MAP_H_ */
/** eof **/

