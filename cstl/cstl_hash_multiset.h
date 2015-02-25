/*
 *  The interface of hash_multiset.
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

#ifndef _CSTL_HASH_MULTISET_H_
#define _CSTL_HASH_MULTISET_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/**
 * Create hash_multiset container.
 * @param ...        element type name.
 * @return if create hash_multiset successfully return hash_multiset pointer, otherwise return NULL.
 * @remarks element type name should be C builtin type name, libcstl builtin typename or registed user defined type name,
 *          otherwise the function will return NULL.
 */
#define create_hash_multiset(...) _create_hash_multiset(#__VA_ARGS__)

/**
 * Find specific element.
 * @param cphmset_set      hash_multiset container.
 * @param elem         specific element.
 * @return iterator addresses the sprcific element in the hash_multiset, otherwise return set_end().
 * @remarks if cphmset_set == NULL then the behavior is undefined. cphmset_set must be initialized, otherwise the behavior is undefined.
 *          the type of specific element and cphmset_set must be same, otherwise the behavior is undefined.
 */
#define hash_multiset_find(cphmset_set, elem) _hash_multiset_find((cphmset_set), (elem))

/**
 * Return the number of specific elements in an hash_multiset
 * @param cphmset_set       hash_multiset container.
 * @param elem          specific element.
 * @return the number of specific elements.
 * @remarks if cphmset_set == NULL then the behavior is undefined. cphmset_set must be initialized, otherwise the behavior is undefined.
 *          the type of specific element and cphmset_set must be same, otherwise the behavior is undefined.
 */
#define hash_multiset_count(cphmset_set, elem) _hash_multiset_count((cphmset_set), (elem))

/**
 * Return an iterator range that is equal to a specific element.
 * @param cphmset_set      hash_multiset container.
 * @param elem         specific element.
 * @return an iterator range that is equal to a specific element.
 * @remarks if cphmset_set == NULL then the behavior is undefined. cphmset_set must be initialized, otherwise the behavior is undefined.
 *          the type of specific element and cphmset_set must be same, otherwise the behavior is undefined.
 */
#define hash_multiset_equal_range(cphmset_set, elem) _hash_multiset_equal_range((cphmset_set), (elem))

/**
 * Inserts an unique element into a hash_multiset.
 * @param phmset_set       hash_multiset container.
 * @param elem           specific element.
 * @return an iterator addresses the inserted element, or hash_multiset end if insert failed.
 * @remarks if phmset_set == NULL then the behavior is undefined. cphmset_set must be initialized, otherwise the behavior is undefined.
 *          the type of specific element and cphmset_set must be same, otherwise the behavior is undefined.
 */
#define hash_multiset_insert(phmset_set, elem) _hash_multiset_insert((phmset_set), (elem))

/**
 * Erase an element from a hash_multiset that match a specified element.
 * @param phmset_set       hash_multiset container.
 * @param elem           specific element.
 * @return the number of erased elements.
 * @remarks if phmset_set == NULL then the behavior is undefined. cphmset_set must be initialized, otherwise the behavior is undefined. 
 */
#define hash_multiset_erase(phmset_set, elem) _hash_multiset_erase((phmset_set), (elem))

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Initialize hash_multiset container.
 * @param phmset_set          hash_multiset container.
 * @return void.
 * @remarks if phmset_set == NULL, then the behavior is undefined, phmset_set must be created by create_hash_multiset(), otherwise
 *          the behavior is undefined. the default compare function is used.
 */
extern void hash_multiset_init(hash_multiset_t* phmset_set);

/**
 * Initialize hash_multiset container with user define compare function.
 * @param phmset_set          hash_multiset container.
 * @param bfun_compare         compare function.
 * @return void.
 * @remarks if phmset_set == NULL, then the behavior is undefined, phmset_set must be created by create_hash_multiset(), otherwise
 *          the behavior is undefined. if bfun_compare == NULL, the default compare function is used.
 */
extern void hash_multiset_init_ex(
    hash_multiset_t* phmset_set, size_t t_bucketcount, ufun_t ufun_hash, bfun_t bfun_compare);

/**
 * Initialize hash_multiset container with hash_multiset.
 * @param phmset_dest           destination hash_multiset.
 * @param cphmset_src           source hash_multiset.
 * @return void.
 * @remarks if phmset_dest == NULL or cphmset_src == NULL, then the behavior is undefined, phmset_dest must be created by
 *          create_hash_multiset(), cphmset_src must be initialized, otherwise the behavior is undefined. the element type of
 *          phmset_dest and cphmset_src must be same, otherwise the behavior is undefine.
 */
extern void hash_multiset_init_copy(hash_multiset_t* phmset_dest, const hash_multiset_t* cphmset_src);

/**
 * Initialize hash_multiset container with specific range.
 * @param phmset_dest       destination hash_multiset.
 * @param it_begin          begin of range.
 * @param it_end            end of range.
 * @return void.
 * @remarks if phmset_dest == NULL, then the behavior is undefined, phmset_dest must be created by create_hash_multiset(), otherwise
 *          the behavior is undefined. the type of [it_begin, it_end) and phmset_dest must be same, otherwise the behavior is undefined.
 */
extern void hash_multiset_init_copy_range(hash_multiset_t* phmset_dest, iterator_t it_begin, iterator_t it_end);

/**
 * Initialize hash_multiset container with specific array.
 * @param phmset_dest       destination hash_multiset.
 * @param cpv_array         array.
 * @param t_count           element count of array.
 * @return void.
 * @remarks if phmset_dest == NULL, then the behavior is undefined, phmset_dest must be created by create_hash_multiset(), otherwise
 *          the behavior is undefined. the type of array and phmset_dest must be same, otherwise the behavior is undefined.
 */
extern void hash_multiset_init_copy_array(hash_multiset_t* phmset_dest, const void* cpv_array, size_t t_count);

/**
 * Initialize hash_multiset container with specific range and compare function.
 * @param phmset_dest       destination hash_multiset.
 * @param it_begin          begin of range.
 * @param it_end            end of range.
 * @param bfun_compare      compare function.
 * @return void.
 * @remarks if phmset_dest == NULL, then the behavior is undefined, phmset_dest must be created by _create_hash_multiset(), otherwise
 *          the behavior is undefined. the type of [it_begin, it_end) and phmset_dest must be same, otherwise the behavior is undefined. if
 *          bfun_compare == NULL, then use default compare function.
 */
extern void hash_multiset_init_copy_range_ex(hash_multiset_t* phmset_dest, iterator_t it_begin, iterator_t it_end,
    size_t t_bucketcount, ufun_t ufun_hash, bfun_t bfun_compare);

/**
 * Initialize hash_multiset container with specific array and compare function.
 * @param phmset_dest       destination hash_multiset.
 * @param cpv_array         array.
 * @param t_count           element count of array.
 * @param bfun_compare      compare function.
 * @return void.
 * @remarks if phmset_dest == NULL, then the behavior is undefined, phmset_dest must be created by _create_hash_multiset(), otherwise
 *          the behavior is undefined. the type of array and phmset_dest must be same, otherwise the behavior is undefined. if
 *          bfun_compare == NULL, then use default compare function.
 */
extern void hash_multiset_init_copy_array_ex(hash_multiset_t* phmset_dest, const void* cpv_array, size_t t_count,
    size_t t_bucketcount, ufun_t ufun_hash, bfun_t bfun_compare);

/**
 * Destroy hash_multiset.
 * @param phmset_set       hash_multiset container.
 * @return void.
 * @remarks if phmset_set == NULL, then the behavior is undefined, the hash_multiset must be initialized or created by create_hash_multiset(),
 *          otherwise the behavior is undefined.
 */
extern void hash_multiset_destroy(hash_multiset_t* phmset_set);

/**
 * Assign hash_multiset container.
 * @param phmset_dest           destination hash_multiset container.
 * @param cphmset_src           source hash_multiset container.
 * @return void.
 * @remarks if phmset_dest == NULL or cphmset_src == NULL, the the behavior is undefined. two hash_multiset must be initialized, otherwise
 *          the behavior is undefined. if set_equal(phmset_dest, cphmset_src), the function dest nothing.
 */
extern void hash_multiset_assign(hash_multiset_t* phmset_dest, const hash_multiset_t* cphmset_src);

/**
 * Swap the datas of first hash_multiset and second hash_multiset.
 * @param pt_first          first hash_multiset container.
 * @param pt_second         second hash_multiset container.
 * @return void.
 * @remarks if pt_first == NULL or pt_second == NULL, then the behavior is undefined. the two hash_multiset must be initialized,
 *          otherwise the behavior is undefined. if the two hash_multiset are not same type, the behavior is undefined. if
 *          set_equal(cpt_first, cpt_second), then the function do nothing.
 */
extern void hash_multiset_swap(hash_multiset_t* phmset_first, hash_multiset_t* phmset_second);

/**
 * Get the number of elements int the hash_multiset.
 * @param cphmset_set      hash_multiset container.
 * @return the number of elements in the hash_multiset.
 * @remarks if cphmset_set == NULL, then the behavior is undefined, the cphmset_set must be initialized, otherwise the behavior
 *          is undefined.
 */
extern size_t hash_multiset_size(const hash_multiset_t* cphmset_set);

/**
 * Test if an hash_multiset is empty.
 * @param cphmset_set      hash_multiset container.
 * @return true if the hash_multiset is empty, otherwise return false.
 * @remarks if cphmset_set == NULL, then the behavior is undefined, the cphmset_set must be initialized, otherwise the behavior
 *          is undefined.
 */
extern bool_t hash_multiset_empty(const hash_multiset_t* cphmset_set);

/**
 * Get the maximum number of elements int the hash_multiset.
 * @param cphmset_set      hash_multiset container.
 * @return the maximum number of elements in the hash_multiset.
 * @remarks if cphmset_set == NULL, then the behavior is undefined, the cphmset_set must be initialized, otherwise the behavior
 *          is undefined.
 */
extern size_t hash_multiset_max_size(const hash_multiset_t* cphmset_set);

/**
 * Get the bucket number of elements int the hash_multiset.
 * @param cphmset_set      hash_multiset container.
 * @return the bucket number of elements in the hash_multiset.
 * @remarks if cphmset_set == NULL, then the behavior is undefined, the cphmset_set must be initialized, otherwise the behavior
 *          is undefined.
 */
extern size_t hash_multiset_bucket_count(const hash_multiset_t* cphmset_set);

/**
 * Return the hash function.
 * @param cphmset_set      hash_multiset container.
 * @return hash function.
 * @remarks if cphmset_set == NULL, the behavior is undefined. cphmset_set must be initialized, otherwise the behavior is undefined.
 */
extern ufun_t hash_multiset_hash(const hash_multiset_t* cphmset_set);

/**
 * Return the compare function of key.
 * @param cphmset_set      hash_multiset container.
 * @return compare function.
 * @remarks if cphmset_set == NULL, the behavior is undefined. cphmset_set must be initialized, otherwise the behavior is undefined.
 */
extern bfun_t hash_multiset_key_comp(const hash_multiset_t* cphmset_set);

/**
 * Return the compare function of value.
 * @param cphmset_set      hash_multiset container.
 * @return compare function.
 * @remarks if cphmset_set == NULL, the behavior is undefined. cphmset_set must be initialized, otherwise the behavior is undefined.
 */
extern bfun_t hash_multiset_value_comp(const hash_multiset_t* cphmset_set);

/**
 * Resize.
 * @param phmset_set      hash_multiset container.
 * @param t_resize       resize hashtable bucket count.
 * @return void.
 * @remarks if phash_multiset == NULL, the behavior is undefined, phmset_set must be initialized,otherwise the behavior
 *          is undefined.
 */
extern void hash_multiset_resize(hash_multiset_t* phmset_set, size_t t_resize);

/**
 * Tests if the two hash_multiset are equal.
 * @param cphmset_first         first hash_multiset container.
 * @param cphmset_second        second hash_multiset container.
 * @return if first hash_multiset equal to second hash_multiset, then return true, else return false.
 * @remarks if cphmset_first == NULL or cphmset_second == NULL, then the behavior is undefined. the two hash_multiset must be
 *          initialized, otherwise the behavior is undefined. if the two hash_multiset are not same type, the behavior is undefined.
 *          if cphmset_first == cphmset_second, then return true.
 */
extern bool_t hash_multiset_equal(const hash_multiset_t* cphmset_first, const hash_multiset_t* cphmset_second);

/**
 * Tests if the two hash_multiset are not equal.
 * @param cphmset_first         first hash_multiset container.
 * @param cphmset_second        second hash_multiset container.
 * @return if first hash_multiset not equal to second hash_multiset, then return true, else return false.
 * @remarks if cphmset_first == NULL or cphmset_second == NULL, then the behavior is undefined. the two hash_multiset must be
 *          initialized, otherwise the behavior is undefined. if the two hash_multiset are not same type, the behavior is undefined.
 *          if cphmset_first == cphmset_second, then return false.
 */
extern bool_t hash_multiset_not_equal(const hash_multiset_t* cphmset_first, const hash_multiset_t* cphmset_second);

/**
 * Tests if the first hash_multiset is less than the second hash_multiset.
 * @param cphmset_first         first hash_multiset container.
 * @param cphmset_second        second hash_multiset container.
 * @return if first hash_multiset is less than the second hash_multiset, then return true, else return false.
 * @remarks if cphmset_first == NULL or cphmset_second == NULL, then the behavior is undefined. the two hash_multiset must be
 *          initialized, otherwise the behavior is undefined. if the two hash_multiset are not same type, the behavior is
 *          undefined. if cphmset_first == cphmset_second, then return false.
 */
extern bool_t hash_multiset_less(const hash_multiset_t* cphmset_first, const hash_multiset_t* cphmset_second);

/**
 * Tests if the first hash_multiset is less than or equal to the second hash_multiset.
 * @param cphmset_first         first hash_multiset container.
 * @param cphmset_second        second hash_multiset container.
 * @return if first hash_multiset is less than or equal to the second hash_multiset, then return true, else return false.
 * @remarks if cphmset_first == NULL or cphmset_second == NULL, then the behavior is undefined. the two hash_multiset must be
 *          initialized, otherwise the behavior is undefined. if the two hash_multiset are not same type, the behavior is
 *          undefined. if cphmset_first == cphmset_second, then return true.
 */
extern bool_t hash_multiset_less_equal(const hash_multiset_t* cphmset_first, const hash_multiset_t* cphmset_second);

/**
 * Tests if the first hash_multiset is greater than the second hash_multiset.
 * @param cphmset_first         first hash_multiset container.
 * @param cphmset_second        second hash_multiset container.
 * @return if first hash_multiset is greater than the second hash_multiset, then return true, else return false.
 * @remarks if cphmset_first == NULL or cphmset_second == NULL, then the behavior is undefined. the two hash_multiset must be
 *          initialized, otherwise the behavior is undefined. if the two hash_multiset are not same type, the behavior is
 *          undefined. if cphmset_first == cphmset_second, then return false.
 */
extern bool_t hash_multiset_greater(const hash_multiset_t* cphmset_first, const hash_multiset_t* cphmset_second);

/**
 * Tests if the first hash_multiset is greater than or equal to the second hash_multiset.
 * @param cphmset_first         first hash_multiset container.
 * @param cphmset_second        second hash_multiset container.
 * @return if first hash_multiset is greater than or equal to the second hash_multiset, then return true, else return false.
 * @remarks if cphmset_first == NULL or cphmset_second == NULL, then the behavior is undefined. the two hash_multiset must be
 *          initialized, otherwise the behavior is undefined. if the two hash_multiset are not same type, the behavior is
 *          undefined. if cphmset_first == cphmset_second, then return true.
 */
extern bool_t hash_multiset_greater_equal(const hash_multiset_t* cphmset_first, const hash_multiset_t* cphmset_second);

/**
 * Return an iterator that addresses the first element in the hash_multiset.
 * @param cphmset_set      hash_multiset container.
 * @return an iterator that addresses the first element in the hash_multiset.
 * @remarks if cphmset_set == NULL, the behavior is undefined. cphmset_set must be initialized, otherwise the behavior is undefined.
 *          return set_end(), if the hash_multiset is empty.
 */
extern hash_multiset_iterator_t hash_multiset_begin(const hash_multiset_t* cphmset_set);

/**
 * Return an iterator that addresses the location succeeding the last element in the hash_multiset.
 * @param cphmset_set      hash_multiset container.
 * @return an iterator that addresses location succeeding the last element in the hash_multiset.
 * @remarks if cphmset_set == NULL, the behavior is undefined. cphmset_set must be initialized, otherwise the behavior is undefined.
 */
extern hash_multiset_iterator_t hash_multiset_end(const hash_multiset_t* cphmset_set);

/**
 * Inserts an range of unique element into a hash_multiset.
 * @param phmset_set          hash_multiset container.
 * @param it_begin          begin of specific range.
 * @param it_end            end of specific range.
 * @return void.
 * @remarks if phmset_set == NULL then the behavior is undefined. phmset_set must be initialized, otherwise the behavior
 *          is undefined. the type of [it_begin, it_end) and cphmset_set must be same, otherwise the behavior is undefined.
 *          [it_begin, it_end) must be valid range, otherwise the behavior is undefine.
 */
extern void hash_multiset_insert_range(hash_multiset_t* phmset_set, iterator_t it_begin, iterator_t it_end);

/**
 * Inserts an array of unique element into a hash_multiset.
 * @param phmset_set          hash_multiset container.
 * @param cpv_array           array.
 * @param t_count             element count of array.
 * @return void.
 * @remarks if phmset_set == NULL then the behavior is undefined. phmset_set must be initialized, otherwise the behavior
 *          is undefined. the type of array and cphmset_set must be same, otherwise the behavior is undefined. array must 
 *          be valid range, otherwise the behavior is undefine.
 */
extern void hash_multiset_insert_array(hash_multiset_t* phmset_set, const void* cpv_array, size_t t_count);

/*
 * Erase an element in an hash_multiset from specificed position.
 * @param phmset_set          hash_multiset container.
 * @param it_pos            specificed position.
 * @return void.
 * @remarks if phmset_set == NULL then the behavior is undefined. phmset_set must be initialized, otherwise the behavior
 *          is undefined. it_pos must be valid iterator, otherwise the behavior is undefined.
 */
extern void hash_multiset_erase_pos(hash_multiset_t* phmset_set, hash_multiset_iterator_t it_pos);

/*
 * Erase a range of element in an hash_multiset.
 * @param phmset_set          hash_multiset container.
 * @param it_begin          begin of specific range.
 * @param it_end            end of specific range.
 * @return void.
 * @remarks if phmset_set == NULL then the behavior is undefined. phmset_set must be initialized, otherwise the behavior
 *          is undefined. [it_begin, it_end) must be valid range for phmset_set, otherwise the behavior is undefine.
 */
extern void hash_multiset_erase_range(
    hash_multiset_t* phmset_set, hash_multiset_iterator_t it_begin, hash_multiset_iterator_t it_end);

/**
 * Erases all the elements of an hash_multiset.
 * @param phmset_set       hash_multiset container.
 * @return void.
 * @remarks if phmset_set == NULL, the behavior is undefined. phmset_set must be initialized, otherwise the behavior is undefined.
 */
extern void hash_multiset_clear(hash_multiset_t* phmset_set);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_HASH_MULTISET_H_ */
/** eof **/

