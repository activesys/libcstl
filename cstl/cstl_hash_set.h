/*
 *  The interface of hash_set.
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

#ifndef _CSTL_HASH_SET_H_
#define _CSTL_HASH_SET_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/**
 * Create hash_set container.
 * @param ...        element type name.
 * @return if create hash_set successfully return hash_set pointer, otherwise return NULL.
 * @remarks element type name should be C builtin type name, libcstl builtin typename or registed user defined type name,
 *          otherwise the function will return NULL.
 */
#define create_hash_set(...) _create_hash_set(#__VA_ARGS__)

/**
 * Find specific element.
 * @param cphset_set      hash_set container.
 * @param elem         specific element.
 * @return iterator addresses the sprcific element in the hash_set, otherwise return set_end().
 * @remarks if cphset_set == NULL then the behavior is undefined. cphset_set must be initialized, otherwise the behavior is undefined.
 *          the type of specific element and cphset_set must be same, otherwise the behavior is undefined.
 */
#define hash_set_find(cphset_set, elem) _hash_set_find((cphset_set), (elem))

/**
 * Return the number of specific elements in an hash_set
 * @param cphset_set       hash_set container.
 * @param elem          specific element.
 * @return the number of specific elements.
 * @remarks if cphset_set == NULL then the behavior is undefined. cphset_set must be initialized, otherwise the behavior is undefined.
 *          the type of specific element and cphset_set must be same, otherwise the behavior is undefined.
 */
#define hash_set_count(cphset_set, elem) _hash_set_count((cphset_set), (elem))

/**
 * Return an iterator range that is equal to a specific element.
 * @param cphset_set      hash_set container.
 * @param elem         specific element.
 * @return an iterator range that is equal to a specific element.
 * @remarks if cphset_set == NULL then the behavior is undefined. cphset_set must be initialized, otherwise the behavior is undefined.
 *          the type of specific element and cphset_set must be same, otherwise the behavior is undefined.
 */
#define hash_set_equal_range(cphset_set, elem) _hash_set_equal_range((cphset_set), (elem))

/**
 * Inserts an unique element into a hash_set.
 * @param phset_set       hash_set container.
 * @param elem           specific element.
 * @return an iterator addresses the inserted element, or hash_set end if insert failed.
 * @remarks if phset_set == NULL then the behavior is undefined. cphset_set must be initialized, otherwise the behavior is undefined.
 *          the type of specific element and cphset_set must be same, otherwise the behavior is undefined.
 */
#define hash_set_insert(phset_set, elem) _hash_set_insert((phset_set), (elem))

/**
 * Erase an element from a hash_set that match a specified element.
 * @param phset_set       hash_set container.
 * @param elem           specific element.
 * @return the number of erased elements.
 * @remarks if phset_set == NULL then the behavior is undefined. cphset_set must be initialized, otherwise the behavior is undefined. 
 */
#define hash_set_erase(phset_set, elem) _hash_set_erase((phset_set), (elem))

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Initialize hash_set container.
 * @param phset_set          hash_set container.
 * @return void.
 * @remarks if phset_set == NULL, then the behavior is undefined, phset_set must be created by create_hash_set(), otherwise
 *          the behavior is undefined. the default compare function is used.
 */
extern void hash_set_init(hash_set_t* phset_set);

/**
 * Initialize hash_set container with user define compare function.
 * @param phset_set          hash_set container.
 * @param bfun_compare         compare function.
 * @return void.
 * @remarks if phset_set == NULL, then the behavior is undefined, phset_set must be created by create_hash_set(), otherwise
 *          the behavior is undefined. if bfun_compare == NULL, the default compare function is used.
 */
extern void hash_set_init_ex(hash_set_t* phset_set, size_t t_bucketcount, ufun_t ufun_hash, bfun_t bfun_compare);

/**
 * Initialize hash_set container with hash_set.
 * @param phset_dest           destination hash_set.
 * @param cphset_src           source hash_set.
 * @return void.
 * @remarks if phset_dest == NULL or cphset_src == NULL, then the behavior is undefined, phset_dest must be created by
 *          create_hash_set(), cphset_src must be initialized, otherwise the behavior is undefined. the element type of
 *          phset_dest and cphset_src must be same, otherwise the behavior is undefine.
 */
extern void hash_set_init_copy(hash_set_t* phset_dest, const hash_set_t* cphset_src);

/**
 * Initialize hash_set container with specific range.
 * @param phset_dest        destination hash_set.
 * @param it_begin          begin of range.
 * @param it_end            end of range.
 * @return void.
 * @remarks if phset_dest == NULL, then the behavior is undefined, phset_dest must be created by create_hash_set(), otherwise
 *          the behavior is undefined. the type of [it_begin, it_end) and phset_dest must be same, otherwise the behavior is 
 *          undefined.
 */
extern void hash_set_init_copy_range(hash_set_t* phset_dest, iterator_t it_begin, iterator_t it_end);

/**
 * Initialize hash_set container with specific array.
 * @param phset_dest        destination hash_set.
 * @param cpv_array         array.
 * @param t_count           element count of array.
 * @return void.
 * @remarks if phset_dest == NULL, then the behavior is undefined, phset_dest must be created by create_hash_set(), otherwise
 *          the behavior is undefined. the type of array and phset_dest must be same, otherwise the behavior is undefined.
 */
extern void hash_set_init_copy_array(hash_set_t* phset_dest, const void* cpv_array, size_t t_count);

/**
 * Initialize hash_set container with specific range and compare function.
 * @param phset_dest        destination hash_set.
 * @param it_begin          begin of range.
 * @param it_end            end of range.
 * @param bfun_compare      compare function.
 * @return void.
 * @remarks if phset_dest == NULL, then the behavior is undefined, phset_dest must be created by _create_hash_set(), otherwise
 *          the behavior is undefined. the type of [it_begin, it_end) and phset_dest must be same, otherwise the behavior is 
 *          undefined. if bfun_compare == NULL, then use default compare function.
 */
extern void hash_set_init_copy_range_ex(hash_set_t* phset_set, iterator_t it_begin, iterator_t it_end,
    size_t t_bucketcount, ufun_t ufun_hash, bfun_t bfun_compare);

/**
 * Initialize hash_set container with specific array and compare function.
 * @param phset_dest        destination hash_set.
 * @param cpv_array         array.
 * @param t_count           element count of array.
 * @param bfun_compare      compare function.
 * @return void.
 * @remarks if phset_dest == NULL, then the behavior is undefined, phset_dest must be created by _create_hash_set(), otherwise
 *          the behavior is undefined. the type of array and phset_dest must be same, otherwise the behavior is undefined. if 
 *          bfun_compare == NULL, then use default compare function.
 */
extern void hash_set_init_copy_array_ex(hash_set_t* phset_set, const void* cpv_array, size_t t_count,
    size_t t_bucketcount, ufun_t ufun_hash, bfun_t bfun_compare);

/**
 * Destroy hash_set.
 * @param phset_set       hash_set container.
 * @return void.
 * @remarks if phset_set == NULL, then the behavior is undefined, the hash_set must be initialized or created by create_hash_set(),
 *          otherwise the behavior is undefined.
 */
extern void hash_set_destroy(hash_set_t* phset_set);

/**
 * Assign hash_set container.
 * @param phset_dest           destination hash_set container.
 * @param cphset_src           source hash_set container.
 * @return void.
 * @remarks if phset_dest == NULL or cphset_src == NULL, the the behavior is undefined. two hash_set must be initialized, otherwise
 *          the behavior is undefined. if set_equal(phset_dest, cphset_src), the function dest nothing.
 */
extern void hash_set_assign(hash_set_t* phset_dest, const hash_set_t* cphset_src);

/**
 * Swap the datas of first hash_set and second hash_set.
 * @param pt_first          first hash_set container.
 * @param pt_second         second hash_set container.
 * @return void.
 * @remarks if pt_first == NULL or pt_second == NULL, then the behavior is undefined. the two hash_set must be initialized,
 *          otherwise the behavior is undefined. if the two hash_set are not same type, the behavior is undefined. if
 *          set_equal(cpt_first, cpt_second), then the function do nothing.
 */
extern void hash_set_swap(hash_set_t* phset_first, hash_set_t* phset_second);

/**
 * Get the number of elements int the hash_set.
 * @param cphset_set      hash_set container.
 * @return the number of elements in the hash_set.
 * @remarks if cphset_set == NULL, then the behavior is undefined, the cphset_set must be initialized, otherwise the behavior
 *          is undefined.
 */
extern size_t hash_set_size(const hash_set_t* cphset_set);

/**
 * Test if an hash_set is empty.
 * @param cphset_set      hash_set container.
 * @return true if the hash_set is empty, otherwise return false.
 * @remarks if cphset_set == NULL, then the behavior is undefined, the cphset_set must be initialized, otherwise the behavior
 *          is undefined.
 */
extern bool_t hash_set_empty(const hash_set_t* cphset_set);

/**
 * Get the maximum number of elements int the hash_set.
 * @param cphset_set      hash_set container.
 * @return the maximum number of elements in the hash_set.
 * @remarks if cphset_set == NULL, then the behavior is undefined, the cphset_set must be initialized, otherwise the behavior
 *          is undefined.
 */
extern size_t hash_set_max_size(const hash_set_t* cphset_set);

/**
 * Get the bucket number of elements int the hash_set.
 * @param cphset_set      hash_set container.
 * @return the bucket number of elements in the hash_set.
 * @remarks if cphset_set == NULL, then the behavior is undefined, the cphset_set must be initialized, otherwise the behavior
 *          is undefined.
 */
extern size_t hash_set_bucket_count(const hash_set_t* cphset_set);

/**
 * Return the hash function.
 * @param cphset_set      hash_set container.
 * @return hash function.
 * @remarks if cphset_set == NULL, the behavior is undefined. cphset_set must be initialized, otherwise the behavior is undefined.
 */
extern ufun_t hash_set_hash(const hash_set_t* cphset_set);

/**
 * Return the compare function of key.
 * @param cphset_set      hash_set container.
 * @return compare function.
 * @remarks if cphset_set == NULL, the behavior is undefined. cphset_set must be initialized, otherwise the behavior is undefined.
 */
extern bfun_t hash_set_key_comp(const hash_set_t* cphset_set);

/**
 * Return the compare function of value.
 * @param cphset_set      hash_set container.
 * @return compare function.
 * @remarks if cphset_set == NULL, the behavior is undefined. cphset_set must be initialized, otherwise the behavior is undefined.
 */
extern bfun_t hash_set_value_comp(const hash_set_t* cphset_set);

/**
 * Resize.
 * @param phset_set      hash_set container.
 * @param t_resize       resize hashtable bucket count.
 * @return void.
 * @remarks if phash_set == NULL, the behavior is undefined, phset_set must be initialized,otherwise the behavior
 *          is undefined.
 */
extern void hash_set_resize(hash_set_t* phset_set, size_t t_resize);

/**
 * Tests if the two hash_set are equal.
 * @param cphset_first         first hash_set container.
 * @param cphset_second        second hash_set container.
 * @return if first hash_set equal to second hash_set, then return true, else return false.
 * @remarks if cphset_first == NULL or cphset_second == NULL, then the behavior is undefined. the two hash_set must be
 *          initialized, otherwise the behavior is undefined. if the two hash_set are not same type, the behavior is undefined.
 *          if cphset_first == cphset_second, then return true.
 */
extern bool_t hash_set_equal(const hash_set_t* cphset_first, const hash_set_t* cphset_second);

/**
 * Tests if the two hash_set are not equal.
 * @param cphset_first         first hash_set container.
 * @param cphset_second        second hash_set container.
 * @return if first hash_set not equal to second hash_set, then return true, else return false.
 * @remarks if cphset_first == NULL or cphset_second == NULL, then the behavior is undefined. the two hash_set must be
 *          initialized, otherwise the behavior is undefined. if the two hash_set are not same type, the behavior is undefined.
 *          if cphset_first == cphset_second, then return false.
 */
extern bool_t hash_set_not_equal(const hash_set_t* cphset_first, const hash_set_t* cphset_second);

/**
 * Tests if the first hash_set is less than the second hash_set.
 * @param cphset_first         first hash_set container.
 * @param cphset_second        second hash_set container.
 * @return if first hash_set is less than the second hash_set, then return true, else return false.
 * @remarks if cphset_first == NULL or cphset_second == NULL, then the behavior is undefined. the two hash_set must be
 *          initialized, otherwise the behavior is undefined. if the two hash_set are not same type, the behavior is
 *          undefined. if cphset_first == cphset_second, then return false.
 */
extern bool_t hash_set_less(const hash_set_t* cphset_first, const hash_set_t* cphset_second);

/**
 * Tests if the first hash_set is less than or equal to the second hash_set.
 * @param cphset_first         first hash_set container.
 * @param cphset_second        second hash_set container.
 * @return if first hash_set is less than or equal to the second hash_set, then return true, else return false.
 * @remarks if cphset_first == NULL or cphset_second == NULL, then the behavior is undefined. the two hash_set must be
 *          initialized, otherwise the behavior is undefined. if the two hash_set are not same type, the behavior is
 *          undefined. if cphset_first == cphset_second, then return true.
 */
extern bool_t hash_set_less_equal(const hash_set_t* cphset_first, const hash_set_t* cphset_second);

/**
 * Tests if the first hash_set is greater than the second hash_set.
 * @param cphset_first         first hash_set container.
 * @param cphset_second        second hash_set container.
 * @return if first hash_set is greater than the second hash_set, then return true, else return false.
 * @remarks if cphset_first == NULL or cphset_second == NULL, then the behavior is undefined. the two hash_set must be
 *          initialized, otherwise the behavior is undefined. if the two hash_set are not same type, the behavior is
 *          undefined. if cphset_first == cphset_second, then return false.
 */
extern bool_t hash_set_greater(const hash_set_t* cphset_first, const hash_set_t* cphset_second);

/**
 * Tests if the first hash_set is greater than or equal to the second hash_set.
 * @param cphset_first         first hash_set container.
 * @param cphset_second        second hash_set container.
 * @return if first hash_set is greater than or equal to the second hash_set, then return true, else return false.
 * @remarks if cphset_first == NULL or cphset_second == NULL, then the behavior is undefined. the two hash_set must be
 *          initialized, otherwise the behavior is undefined. if the two hash_set are not same type, the behavior is
 *          undefined. if cphset_first == cphset_second, then return true.
 */
extern bool_t hash_set_greater_equal(const hash_set_t* cphset_first, const hash_set_t* cphset_second);

/**
 * Return an iterator that addresses the first element in the hash_set.
 * @param cphset_set      hash_set container.
 * @return an iterator that addresses the first element in the hash_set.
 * @remarks if cphset_set == NULL, the behavior is undefined. cphset_set must be initialized, otherwise the behavior is undefined.
 *          return set_end(), if the hash_set is empty.
 */
extern hash_set_iterator_t hash_set_begin(const hash_set_t* cphset_set);

/**
 * Return an iterator that addresses the location succeeding the last element in the hash_set.
 * @param cphset_set      hash_set container.
 * @return an iterator that addresses location succeeding the last element in the hash_set.
 * @remarks if cphset_set == NULL, the behavior is undefined. cphset_set must be initialized, otherwise the behavior is undefined.
 */
extern hash_set_iterator_t hash_set_end(const hash_set_t* cphset_set);

/**
 * Inserts an range of unique element into a hash_set.
 * @param phset_set          hash_set container.
 * @param it_begin          begin of specific range.
 * @param it_end            end of specific range.
 * @return void.
 * @remarks if phset_set == NULL then the behavior is undefined. phset_set must be initialized, otherwise the behavior
 *          is undefined. the type of [it_begin, it_end) and cphset_set must be same, otherwise the behavior is undefined.
 *          [it_begin, it_end) must be valid range, otherwise the behavior is undefine.
 */
extern void hash_set_insert_range(hash_set_t* phset_set, iterator_t it_begin, iterator_t it_end);

/**
 * inserts an array of unique element into a hash_set.
 * @param phset_set          hash_set container.
 * @param cpv_array          array.
 * @param t_count            element count of array.
 * @return void.
 * @remarks if phset_set == null then the behavior is undefined. phset_set must be initialized, otherwise the behavior
 *          is undefined. the type of array and cphset_set must be same, otherwise the behavior is undefined. array 
 *          must be valid range, otherwise the behavior is undefine.
 */
extern void hash_set_insert_array(hash_set_t* phset_set, const void* cpv_array, size_t t_count);

/*
 * Erase an element in an hash_set from specificed position.
 * @param phset_set          hash_set container.
 * @param it_pos            specificed position.
 * @return void.
 * @remarks if phset_set == NULL then the behavior is undefined. phset_set must be initialized, otherwise the behavior
 *          is undefined. it_pos must be valid iterator, otherwise the behavior is undefined.
 */
extern void hash_set_erase_pos(hash_set_t* phset_set, hash_set_iterator_t it_pos);

/*
 * Erase a range of element in an hash_set.
 * @param phset_set          hash_set container.
 * @param it_begin          begin of specific range.
 * @param it_end            end of specific range.
 * @return void.
 * @remarks if phset_set == NULL then the behavior is undefined. phset_set must be initialized, otherwise the behavior
 *          is undefined. [it_begin, it_end) must be valid range for phset_set, otherwise the behavior is undefine.
 */
extern void hash_set_erase_range(hash_set_t* phset_set, hash_set_iterator_t it_begin, hash_set_iterator_t it_end);

/**
 * Erases all the elements of an hash_set.
 * @param phset_set       hash_set container.
 * @return void.
 * @remarks if phset_set == NULL, the behavior is undefined. phset_set must be initialized, otherwise the behavior is undefined.
 */
extern void hash_set_clear(hash_set_t* phset_set);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_HASH_SET_H_ */
/** eof **/

