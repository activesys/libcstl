/*
 *  The interface of hash_multimap.
 *  Copyright (C)  2008 - 2013  Wangbo
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
 * Create hash_multimap container.
 * @param ...        element type name.
 * @return if create hash_multimap successfully return hash_multimap pointer, otherwise return NULL.
 * @remarks element type name should be C builtin type name, libcstl builtin typename or registed user defined type name,
 *          otherwise the function will return NULL.
 */
#define create_hash_multimap(...) _create_hash_multimap(#__VA_ARGS__)

/**
 * Find specific element.
 * @param cphmmap_map    hash_multimap container.
 * @param elem         specific element.
 * @return iterator addresses the sprcific element in the hash_multimap, otherwise return map_end().
 * @remarks if cphmmap_map == NULL then the behavior is undefined. cphmmap_map must be initialized, otherwise the behavior is undefined.
 *          the type of specific element and cphmmap_map must be same, otherwise the behavior is undefined.
 */
#define hash_multimap_find(cphmmap_map, key_elem) _hash_multimap_find((cphmmap_map), (key_elem))

/**
 * Return the number of specific elements in an hash_multimap
 * @param cphmmap_map     hash_multimap container.
 * @param elem          specific element.
 * @return the number of specific elements.
 * @remarks if cphmmap_map == NULL then the behavior is undefined. cphmmap_map must be initialized, otherwise the behavior is undefined.
 *          the type of specific element and cphmmap_map must be same, otherwise the behavior is undefined.
 */
#define hash_multimap_count(cphmmap_map, key_elem) _hash_multimap_count((cphmmap_map), (key_elem))

/**
 * Return an iterator range that is equal to a specific element.
 * @param cphmmap_map    hash_multimap container.
 * @param elem         specific element.
 * @return an iterator range that is equal to a specific element.
 * @remarks if cphmmap_map == NULL then the behavior is undefined. cphmmap_map must be initialized, otherwise the behavior is undefined.
 *          the type of specific element and cphmmap_map must be same, otherwise the behavior is undefined.
 */
#define hash_multimap_equal_range(cphmmap_map, key_elem) _hash_multimap_equal_range((cphmmap_map), (key_elem))

/**
 * Erase an element from a hash_multimap that match a specified element.
 * @param phmmap_map       hash_multimap container.
 * @param elem           specific element.
 * @return the number of erased elements.
 * @remarks if phmmap_map == NULL then the behavior is undefined. cphmmap_map must be initialized, otherwise the behavior is undefined. 
 */
#define hash_multimap_erase(phmmap_map, key_elem) _hash_multimap_erase((phmmap_map), (key_elem))

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Initialize hash_multimap container.
 * @param phmmap_map          hash_multimap container.
 * @return void.
 * @remarks if phmmap_map == NULL, then the behavior is undefined, phmmap_map must be created by create_map(), otherwise
 *          the behavior is undefined. the default compare function is used.
 */
extern void hash_multimap_init(hash_multimap_t* phmmap_map);

/**
 * Initialize hash_multimap container with user define compare function.
 * @param phmmap_map          hash_multimap container.
 * @param bfun_compare         compare function.
 * @return void.
 * @remarks if phmmap_map == NULL, then the behavior is undefined, phmmap_map must be created by create_map(), otherwise
 *          the behavior is undefined. if bfun_compare == NULL, the default compare function is used.
 */
extern void hash_multimap_init_ex(hash_multimap_t* phmmap_map, size_t t_bucketcount, ufun_t ufun_hash, bfun_t bfun_compare);

/**
 * Initialize hash_multimap container with hash_multimap.
 * @param pmap_dest           destination hash_multimap.
 * @param cpmap_src           source hash_multimap.
 * @return void.
 * @remarks if pmap_dest == NULL or cpmap_src == NULL, then the behavior is undefined, pmap_dest must be created by
 *          create_map(), cpmap_src must be initialized, otherwise the behavior is undefined. the element type of
 *          pmap_dest and cpmap_src must be same, otherwise the behavior is undefine.
 */
extern void hash_multimap_init_copy(hash_multimap_t* phmmap_dest, const hash_multimap_t* cphmmap_src);

/**
 * Initialize hash_multimap container with specific range.
 * @param pmap_dest         destination hash_multimap.
 * @param it_begin          begin of range.
 * @param it_end            end of range.
 * @return void.
 * @remarks if pmap_dest == NULL, then the behavior is undefined, pmap_dest must be created by create_map(), otherwise
 *          the behavior is undefined. the type of [it_begin, it_end) and pmap_dest must be same, otherwise the behavior 
 *          is undefined.
 */
extern void hash_multimap_init_copy_range(hash_multimap_t* phmmap_dest, iterator_t it_begin, iterator_t it_end);

/**
 * Initialize hash_multimap container with specific array.
 * @param pmap_dest         destination hash_multimap.
 * @param cpv_array         array.
 * @param t_count           element count of array.
 * @return void.
 * @remarks if pmap_dest == NULL, then the behavior is undefined, pmap_dest must be created by create_map(), otherwise
 *          the behavior is undefined. the type of array and pmap_dest must be same, otherwise the behavior is undefined.
 */
extern void hash_multimap_init_copy_array(hash_multimap_t* phmmap_dest, const void* cpv_array, size_t t_count);

/**
 * Initialize hash_multimap container with specific range and compare function.
 * @param pmap_dest         destination hash_multimap.
 * @param it_begin          begin of range.
 * @param it_end            end of range.
 * @param bfun_compare      compare function.
 * @return void.
 * @remarks if pmap_dest == NULL, then the behavior is undefined, pmap_dest must be created by _create_map(), otherwise
 *          the behavior is undefined. the type of [it_begin, it_end) and pmap_dest must be same, otherwise the behavior 
 *          is undefined. if bfun_compare == NULL, then use default compare function.
 */
extern void hash_multimap_init_copy_range_ex(hash_multimap_t* phmmap_dest, iterator_t it_begin, iterator_t it_end,
    size_t t_bucketcount, ufun_t ufun_hash, bfun_t bfun_compare);

/**
 * Initialize hash_multimap container with specific array and compare function.
 * @param pmap_dest         destination hash_multimap.
 * @param cpv_array         array.
 * @param t_count           element count of array.
 * @param bfun_compare      compare function.
 * @return void.
 * @remarks if pmap_dest == NULL, then the behavior is undefined, pmap_dest must be created by _create_map(), otherwise
 *          the behavior is undefined. the type of array and pmap_dest must be same, otherwise the behavior is undefined.
 *          if bfun_compare == NULL, then use default compare function.
 */
extern void hash_multimap_init_copy_array_ex(hash_multimap_t* phmmap_dest, const void* cpv_array, size_t t_count,
    size_t t_bucketcount, ufun_t ufun_hash, bfun_t bfun_compare);

/**
 * Destroy hash_multimap.
 * @param phmmap_map       hash_multimap container.
 * @return void.
 * @remarks if phmmap_map == NULL, then the behavior is undefined, the hash_multimap must be initialized or created by create_map(),
 *          otherwise the behavior is undefined.
 */
extern void hash_multimap_destroy(hash_multimap_t* phmmap_map);

/**
 * Assign hash_multimap container.
 * @param pmap_dest           destination hash_multimap container.
 * @param cpmap_src           source hash_multimap container.
 * @return void.
 * @remarks if pmap_dest == NULL or cpmap_src == NULL, the the behavior is undefined. two hash_multimap must be initialized, otherwise
 *          the behavior is undefined. if map_equal(pmap_dest, cpmap_src), the function dest nothing.
 */
extern void hash_multimap_assign(hash_multimap_t* phmmap_dest, const hash_multimap_t* cphmmap_src);

/**
 * Swap the datas of first hash_multimap and second hash_multimap.
 * @param pt_first          first hash_multimap container.
 * @param pt_second         second hash_multimap container.
 * @return void.
 * @remarks if pt_first == NULL or pt_second == NULL, then the behavior is undefined. the two hash_multimap must be initialized,
 *          otherwise the behavior is undefined. if the two hash_multimap are not same type, the behavior is undefined. if
 *          map_equal(cpt_first, cpt_second), then the function do nothing.
 */
extern void hash_multimap_swap(hash_multimap_t* phmmap_first, hash_multimap_t* phmmap_second);

/**
 * Get the number of elements int the hash_multimap.
 * @param cphmmap_map      hash_multimap container.
 * @return the number of elements in the hash_multimap.
 * @remarks if cphmmap_map == NULL, then the behavior is undefined, the cphmmap_map must be initialized, otherwise the behavior
 *          is undefined.
 */
extern size_t hash_multimap_size(const hash_multimap_t* cphmmap_map);

/**
 * Test if an hash_multimap is empty.
 * @param cphmmap_map      hash_multimap container.
 * @return true if the hash_multimap is empty, otherwise return false.
 * @remarks if cphmmap_map == NULL, then the behavior is undefined, the cphmmap_map must be initialized, otherwise the behavior
 *          is undefined.
 */
extern bool_t hash_multimap_empty(const hash_multimap_t* cphmmap_map);

/**
 * Get the maximum number of elements int the hash_multimap.
 * @param cphmmap_map      hash_multimap container.
 * @return the maximum number of elements in the hash_multimap.
 * @remarks if cphmmap_map == NULL, then the behavior is undefined, the cphmmap_map must be initialized, otherwise the behavior
 *          is undefined.
 */
extern size_t hash_multimap_max_size(const hash_multimap_t* cphmmap_map);

/**
 * Get the bucket count of elements int the hash_multimap.
 * @param cphmmap_map      hash_multimap container.
 * @return the bucket count of elements in the hash_multimap.
 * @remarks if cphmmap_map == NULL, then the behavior is undefined, the cphmmap_map must be initialized, otherwise the behavior
 *          is undefined.
 */
extern size_t hash_multimap_bucket_count(const hash_multimap_t* cphmmap_map);

/**
 * Return the hash function of value.
 * @param cphmmap_map      hash_multimap container.
 * @return compare function.
 * @remarks if cphmmap_map == NULL, the behavior is undefined. cphmmap_map must be initialized, otherwise the behavior is undefined.
 */
extern ufun_t hash_multimap_hash(const hash_multimap_t* cphmmap_map);

/**
 * Return the compare function of key.
 * @param cphmmap_map      hash_multimap container.
 * @return compare function.
 * @remarks if cphmmap_map == NULL, the behavior is undefined. cphmmap_map must be initialized, otherwise the behavior is undefined.
 */
extern bfun_t hash_multimap_key_comp(const hash_multimap_t* cphmmap_map);

/**
 * Return the compare function of value.
 * @param cphmmap_map      hash_multimap container.
 * @return compare function.
 * @remarks if cphmmap_map == NULL, the behavior is undefined. cphmmap_map must be initialized, otherwise the behavior is undefined.
 */
extern bfun_t hash_multimap_value_comp(const hash_multimap_t* cphmmap_map);

/**
 * Resize bucket count of hash map.
 * @param cphmmap_map      hash_multimap container.
 * @return void.
 * @remarks if cphmmap_map == NULL, the behavior is undefined. cphmmap_map must be initialized, otherwise the behavior is undefined.
 */
extern void hash_multimap_resize(hash_multimap_t* phmmap_map, size_t t_resize);

/**
 * Return an iterator that addresses the first element in the hash_multimap.
 * @param cphmmap_map      hash_multimap container.
 * @return an iterator that addresses the first element in the hash_multimap.
 * @remarks if cphmmap_map == NULL, the behavior is undefined. cphmmap_map must be initialized, otherwise the behavior is undefined.
 *          return map_end(), if the hash_multimap is empty.
 */
extern hash_multimap_iterator_t hash_multimap_begin(const hash_multimap_t* cphmmap_map);

/**
 * Return an iterator that addresses the location succeeding the last element in the hash_multimap.
 * @param cphmmap_map      hash_multimap container.
 * @return an iterator that addresses location succeeding the last element in the hash_multimap.
 * @remarks if cphmmap_map == NULL, the behavior is undefined. cphmmap_map must be initialized, otherwise the behavior is undefined.
 */
extern hash_multimap_iterator_t hash_multimap_end(const hash_multimap_t* cphmmap_map);

/**
 * Tests if the two hash_multimap are equal.
 * @param cpmap_first         first hash_multimap container.
 * @param cpmap_second        second hash_multimap container.
 * @return if first hash_multimap equal to second hash_multimap, then return true, else return false.
 * @remarks if cpmap_first == NULL or cpmap_second == NULL, then the behavior is undefined. the two hash_multimap must be
 *          initialized, otherwise the behavior is undefined. if the two hash_multimap are not same type, the behavior is undefined.
 *          if cpmap_first == cpmap_second, then return true.
 */
extern bool_t hash_multimap_equal(const hash_multimap_t* cphmmap_first, const hash_multimap_t* cphmmap_second);

/**
 * Tests if the two hash_multimap are not equal.
 * @param cpmap_first         first hash_multimap container.
 * @param cpmap_second        second hash_multimap container.
 * @return if first hash_multimap not equal to second hash_multimap, then return true, else return false.
 * @remarks if cpmap_first == NULL or cpmap_second == NULL, then the behavior is undefined. the two hash_multimap must be
 *          initialized, otherwise the behavior is undefined. if the two hash_multimap are not same type, the behavior is undefined.
 *          if cpmap_first == cpmap_second, then return false.
 */
extern bool_t hash_multimap_not_equal(const hash_multimap_t* cphmmap_first, const hash_multimap_t* cphmmap_second);

/**
 * Tests if the first hash_multimap is less than the second hash_multimap.
 * @param cpmap_first         first hash_multimap container.
 * @param cpmap_second        second hash_multimap container.
 * @return if first hash_multimap is less than the second hash_multimap, then return true, else return false.
 * @remarks if cpmap_first == NULL or cpmap_second == NULL, then the behavior is undefined. the two hash_multimap must be
 *          initialized, otherwise the behavior is undefined. if the two hash_multimap are not same type, the behavior is
 *          undefined. if cpmap_first == cpmap_second, then return false.
 */
extern bool_t hash_multimap_less(const hash_multimap_t* cphmmap_first, const hash_multimap_t* cphmmap_second);

/**
 * Tests if the first hash_multimap is less than or equal to the second hash_multimap.
 * @param cpmap_first         first hash_multimap container.
 * @param cpmap_second        second hash_multimap container.
 * @return if first hash_multimap is less than or equal to the second hash_multimap, then return true, else return false.
 * @remarks if cpmap_first == NULL or cpmap_second == NULL, then the behavior is undefined. the two hash_multimap must be
 *          initialized, otherwise the behavior is undefined. if the two hash_multimap are not same type, the behavior is
 *          undefined. if cpmap_first == cpmap_second, then return true.
 */
extern bool_t hash_multimap_less_equal(const hash_multimap_t* cphmmap_first, const hash_multimap_t* cphmmap_second);

/**
 * Tests if the first hash_multimap is greater than the second hash_multimap.
 * @param cpmap_first         first hash_multimap container.
 * @param cpmap_second        second hash_multimap container.
 * @return if first hash_multimap is greater than the second hash_multimap, then return true, else return false.
 * @remarks if cpmap_first == NULL or cpmap_second == NULL, then the behavior is undefined. the two hash_multimap must be
 *          initialized, otherwise the behavior is undefined. if the two hash_multimap are not same type, the behavior is
 *          undefined. if cpmap_first == cpmap_second, then return false.
 */
extern bool_t hash_multimap_greater(const hash_multimap_t* cphmmap_first, const hash_multimap_t* cphmmap_second);

/**
 * Tests if the first hash_multimap is greater than or equal to the second hash_multimap.
 * @param cpmap_first         first hash_multimap container.
 * @param cpmap_second        second hash_multimap container.
 * @return if first hash_multimap is greater than or equal to the second hash_multimap, then return true, else return false.
 * @remarks if cpmap_first == NULL or cpmap_second == NULL, then the behavior is undefined. the two hash_multimap must be
 *          initialized, otherwise the behavior is undefined. if the two hash_multimap are not same type, the behavior is
 *          undefined. if cpmap_first == cpmap_second, then return true.
 */
extern bool_t hash_multimap_greater_equal(const hash_multimap_t* cphmmap_first, const hash_multimap_t* cphmmap_second);

/**
 * Inserts an unique element into a hash_multimap.
 * @param phmmap_map       hash_multimap container.
 * @param cppair_pair    specific element.
 * @return an iterator addresses the inserted element, or hash_multimap end if insert failed.
 * @remarks if phmmap_map == NULL then the behavior is undefined. cphmmap_map must be initialized, otherwise the behavior is undefined.
 *          the type of specific element and cphmmap_map must be same, otherwise the behavior is undefined.
 */
extern hash_multimap_iterator_t hash_multimap_insert(hash_multimap_t* phmmap_map, const pair_t* cppair_pair);

/**
 * Inserts an range of unique element into a hash_multimap.
 * @param phmmap_map        hash_multimap container.
 * @param it_begin          begin of specific range.
 * @param it_end            end of specific range.
 * @return void.
 * @remarks if phmmap_map == NULL then the behavior is undefined. phmmap_map must be initialized, otherwise the behavior
 *          is undefined. the type of [it_begin, it_end) and cphmmap_map must be same, otherwise the behavior is undefined.
 *          [it_begin, it_end) must be valid range, otherwise the behavior is undefine.
 */
extern void hash_multimap_insert_range(hash_multimap_t* phmmap_map, iterator_t it_begin, iterator_t it_end);

/**
 * Inserts an array of unique element into a hash_multimap.
 * @param phmmap_map        hash_multimap container.
 * @param cpv_array         array.
 * @param t_count           element count of array.
 * @return void.
 * @remarks if phmmap_map == NULL then the behavior is undefined. phmmap_map must be initialized, otherwise the behavior
 *          is undefined. the type of array and cphmmap_map must be same, otherwise the behavior is undefined. array must 
 *          be valid, otherwise the behavior is undefine.
 */
extern void hash_multimap_insert_array(hash_multimap_t* phmmap_map, const void* cpv_array, size_t t_count);

/**
 * Erase an element in an hash_multimap from specificed position.
 * @param phmmap_map        hash_multimap container.
 * @param it_pos            specificed position.
 * @return void.
 * @remarks if phmmap_map == NULL then the behavior is undefined. phmmap_map must be initialized, otherwise the behavior
 *          is undefined. it_pos must be valid iterator, otherwise the behavior is undefined.
 */
extern void hash_multimap_erase_pos(hash_multimap_t* phmmap_map, hash_multimap_iterator_t it_pos);

/**
 * Erase a range of element in an hash_multimap.
 * @param phmmap_map        hash_multimap container.
 * @param it_begin          begin of specific range.
 * @param it_end            end of specific range.
 * @return void.
 * @remarks if phmmap_map == NULL then the behavior is undefined. phmmap_map must be initialized, otherwise the behavior
 *          is undefined. [it_begin, it_end) must be valid range for phmmap_map, otherwise the behavior is undefine.
 */
extern void hash_multimap_erase_range(hash_multimap_t* phmmap_map, hash_multimap_iterator_t it_begin, hash_multimap_iterator_t it_end);

/**
 * Erases all the elements of an hash_multimap.
 * @param phmmap_map       hash_multimap container.
 * @return void.
 * @remarks if phmmap_map == NULL, the behavior is undefined. phmmap_map must be initialized, otherwise the behavior is undefined.
 */
extern void hash_multimap_clear(hash_multimap_t* phmmap_map);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_HASH_MULTIMAP_H_ */
/** eof **/

