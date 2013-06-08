/*
 *  The interface of multimap.
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

#ifndef _CSTL_MULTIMAP_H_
#define _CSTL_MULTIMAP_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/**
 * Create multimap container.
 * @param ...        element type name.
 * @return if create multimap successfully return multimap pointer, otherwise return NULL.
 * @remarks element type name should be C builtin type name, libcstl builtin typename or registed user defined type name,
 *          otherwise the function will return NULL.
 */
#define create_multimap(...) _create_multimap(#__VA_ARGS__)

/**
 * Find specific element.
 * @param cpmap_map    multimap container.
 * @param elem         specific element.
 * @return iterator addresses the sprcific element in the multimap, otherwise return map_end().
 * @remarks if cpmap_map == NULL then the behavior is undefined. cpmap_map must be initialized, otherwise the behavior is undefined.
 *          the type of specific element and cpmap_map must be same, otherwise the behavior is undefined.
 */
#define multimap_find(cpmmap_map, key_elem) _multimap_find((cpmmap_map), (key_elem))

/**
 * Return the number of specific elements in an multimap
 * @param cpmap_map     multimap container.
 * @param elem          specific element.
 * @return the number of specific elements.
 * @remarks if cpmap_map == NULL then the behavior is undefined. cpmap_map must be initialized, otherwise the behavior is undefined.
 *          the type of specific element and cpmap_map must be same, otherwise the behavior is undefined.
 */
#define multimap_count(cpmmap_map, key_elem) _multimap_count((cpmmap_map), (key_elem))

/**
 * Return an iterator to the first element that is equal to or greater than a specific element.
 * @param cpmap_map    multimap container.
 * @param elem         specific element.
 * @return an iterator to the first element that is equal to or greater than a specific element.
 * @remarks if cpmap_map == NULL then the behavior is undefined. cpmap_map must be initialized, otherwise the behavior is undefined.
 *          the type of specific element and cpmap_map must be same, otherwise the behavior is undefined.
 */
#define multimap_lower_bound(cpmmap_map, key_elem) _multimap_lower_bound((cpmmap_map), (key_elem))

/**
 * Return an iterator to the first element that is greater than a specific element.
 * @param cpmap_map    multimap container.
 * @param elem         specific element.
 * @return an iterator to the first element that is greater than a specific element.
 * @remarks if cpmap_map == NULL then the behavior is undefined. cpmap_map must be initialized, otherwise the behavior is undefined.
 *          the type of specific element and cpmap_map must be same, otherwise the behavior is undefined.
 */
#define multimap_upper_bound(cpmmap_map, key_elem) _multimap_upper_bound((cpmmap_map), (key_elem))

/**
 * Return an iterator range that is equal to a specific element.
 * @param cpmap_map    multimap container.
 * @param elem         specific element.
 * @return an iterator range that is equal to a specific element.
 * @remarks if cpmap_map == NULL then the behavior is undefined. cpmap_map must be initialized, otherwise the behavior is undefined.
 *          the type of specific element and cpmap_map must be same, otherwise the behavior is undefined.
 */
#define multimap_equal_range(cpmmap_map, key_elem) _multimap_equal_range((cpmmap_map), (key_elem))

/**
 * Erase an element from a multimap that match a specified element.
 * @param pmap_map       multimap container.
 * @param elem           specific element.
 * @return the number of erased elements.
 * @remarks if pmap_map == NULL then the behavior is undefined. cpmap_map must be initialized, otherwise the behavior is undefined. 
 */
#define multimap_erase(pmmap_map, key_elem) _multimap_erase((pmmap_map), (key_elem))

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Initialize multimap container.
 * @param pmap_map          multimap container.
 * @return void.
 * @remarks if pmap_map == NULL, then the behavior is undefined, pmap_map must be created by create_map(), otherwise
 *          the behavior is undefined. the default compare function is used.
 */
extern void multimap_init(multimap_t* pmmap_map);

/**
 * Initialize multimap container with user define compare function.
 * @param pmap_map          multimap container.
 * @param t_compare         compare function.
 * @return void.
 * @remarks if pmap_map == NULL, then the behavior is undefined, pmap_map must be created by create_map(), otherwise
 *          the behavior is undefined. if t_compare == NULL, the default compare function is used.
 */
extern void multimap_init_ex(multimap_t* pmmap_map, bfun_t bfun_keycompare);

/**
 * Initialize multimap container with multimap.
 * @param pmap_dest           destination multimap.
 * @param cpmap_src           source multimap.
 * @return void.
 * @remarks if pmap_dest == NULL or cpmap_src == NULL, then the behavior is undefined, pmap_dest must be created by
 *          create_map(), cpmap_src must be initialized, otherwise the behavior is undefined. the element type of
 *          pmap_dest and cpmap_src must be same, otherwise the behavior is undefine.
 */
extern void multimap_init_copy(multimap_t* pmmap_dest, const multimap_t* cpmmap_src);

/**
 * Initialize multimap container with specific range.
 * @param pmap_dest         destination multimap.
 * @param it_begin          begin of range.
 * @param it_end            end of range.
 * @return void.
 * @remarks if pmap_dest == NULL, then the behavior is undefined, pmap_dest must be created by create_map(), otherwise
 *          the behavior is undefined. the type of [it_begin, it_end) and pmap_dest must be same, otherwise the behavior
 *          is undefined.
 */
extern void multimap_init_copy_range(multimap_t* pmmap_dest, iterator_t it_begin, iterator_t it_end);

/**
 * Initialize multimap container with specific array.
 * @param pmap_dest         destination multimap.
 * @param cpv_array         array.
 * @param t_count           element count of array.
 * @return void.
 * @remarks if pmap_dest == NULL, then the behavior is undefined, pmap_dest must be created by create_map(), otherwise
 *          the behavior is undefined. the type of array and pmap_dest must be same, otherwise the behavior
 *          is undefined.
 */
extern void multimap_init_copy_array(multimap_t* pmmap_dest, const void* cpv_array, size_t t_count);

/**
 * Initialize multimap container with specific range and compare function.
 * @param pmap_dest         destination multimap.
 * @param it_begin          begin of range.
 * @param it_end            end of range.
 * @param t_compare         compare function.
 * @return void.
 * @remarks if pmap_dest == NULL, then the behavior is undefined, pmap_dest must be created by _create_map(), otherwise
 *          the behavior is undefined. the type of [it_begin, it_end) and pmap_dest must be same, otherwise the behavior
 *          is undefined. if t_compare == NULL, then use default compare function.
 */
extern void multimap_init_copy_range_ex(
    multimap_t* pmmap_dest, iterator_t it_begin, iterator_t it_end, bfun_t bfun_keycompare);

/**
 * Initialize multimap container with specific array and compare function.
 * @param pmap_dest         destination multimap.
 * @param cpv_array         array.
 * @param t_count           element count of array.
 * @param t_compare         compare function.
 * @return void.
 * @remarks if pmap_dest == NULL, then the behavior is undefined, pmap_dest must be created by _create_map(), otherwise
 *          the behavior is undefined. the type of array and pmap_dest must be same, otherwise the behavior
 *          is undefined. if t_compare == NULL, then use default compare function.
 */
extern void multimap_init_copy_array_ex(
    multimap_t* pmmap_dest, const void* cpv_array, size_t t_count, bfun_t bfun_keycompare);

/**
 * Destroy multimap.
 * @param pmap_map       multimap container.
 * @return void.
 * @remarks if pmap_map == NULL, then the behavior is undefined, the multimap must be initialized or created by create_map(),
 *          otherwise the behavior is undefined.
 */
extern void multimap_destroy(multimap_t* pmmap_map);

/**
 * Assign multimap container.
 * @param pmap_dest           destination multimap container.
 * @param cpmap_src           source multimap container.
 * @return void.
 * @remarks if pmap_dest == NULL or cpmap_src == NULL, the the behavior is undefined. two multimap must be initialized, otherwise
 *          the behavior is undefined. if map_equal(pmap_dest, cpmap_src), the function dest nothing.
 */
extern void multimap_assign(multimap_t* pmmap_dest, const multimap_t* cpmmap_src);

/**
 * Swap the datas of first multimap and second multimap.
 * @param pt_first          first multimap container.
 * @param pt_second         second multimap container.
 * @return void.
 * @remarks if pt_first == NULL or pt_second == NULL, then the behavior is undefined. the two multimap must be initialized,
 *          otherwise the behavior is undefined. if the two multimap are not same type, the behavior is undefined. if
 *          map_equal(cpt_first, cpt_second), then the function do nothing.
 */
extern void multimap_swap(multimap_t* pmmap_first, multimap_t* pmmap_second);

/**
 * Get the number of elements int the multimap.
 * @param cpmap_map      multimap container.
 * @return the number of elements in the multimap.
 * @remarks if cpmap_map == NULL, then the behavior is undefined, the cpmap_map must be initialized, otherwise the behavior
 *          is undefined.
 */
extern size_t multimap_size(const multimap_t* cpmmap_map);

/**
 * Test if an multimap is empty.
 * @param cpmap_map      multimap container.
 * @return true if the multimap is empty, otherwise return false.
 * @remarks if cpmap_map == NULL, then the behavior is undefined, the cpmap_map must be initialized, otherwise the behavior
 *          is undefined.
 */
extern bool_t multimap_empty(const multimap_t* cpmmap_map);

/**
 * Get the maximum number of elements int the multimap.
 * @param cpmap_map      multimap container.
 * @return the maximum number of elements in the multimap.
 * @remarks if cpmap_map == NULL, then the behavior is undefined, the cpmap_map must be initialized, otherwise the behavior
 *          is undefined.
 */
extern size_t multimap_max_size(const multimap_t* cpmmap_map);

/**
 * Return the compare function of key.
 * @param cpmap_map      multimap container.
 * @return compare function.
 * @remarks if cpmap_map == NULL, the behavior is undefined. cpmap_map must be initialized, otherwise the behavior is undefined.
 */
extern bfun_t multimap_key_comp(const multimap_t* cpmmap_map);

/**
 * Return the compare function of value.
 * @param cpmap_map      multimap container.
 * @return compare function.
 * @remarks if cpmap_map == NULL, the behavior is undefined. cpmap_map must be initialized, otherwise the behavior is undefined.
 */
extern bfun_t multimap_value_comp(const multimap_t* cpmmap_map);

/**
 * Erases all the elements of an multimap.
 * @param pmap_map       multimap container.
 * @return void.
 * @remarks if pmap_map == NULL, the behavior is undefined. pmap_map must be initialized, otherwise the behavior is undefined.
 */
extern void multimap_clear(multimap_t* pmmap_map);

/**
 * Tests if the two multimap are equal.
 * @param cpmap_first         first multimap container.
 * @param cpmap_second        second multimap container.
 * @return if first multimap equal to second multimap, then return true, else return false.
 * @remarks if cpmap_first == NULL or cpmap_second == NULL, then the behavior is undefined. the two multimap must be
 *          initialized, otherwise the behavior is undefined. if the two multimap are not same type, then return false.
 *          if cpmap_first == cpmap_second, then return true.
 */
extern bool_t multimap_equal(const multimap_t* cpmmap_first, const multimap_t* cpmmap_second);

/**
 * Tests if the two multimap are not equal.
 * @param cpmap_first         first multimap container.
 * @param cpmap_second        second multimap container.
 * @return if first multimap not equal to second multimap, then return true, else return false.
 * @remarks if cpmap_first == NULL or cpmap_second == NULL, then the behavior is undefined. the two multimap must be
 *          initialized, otherwise the behavior is undefined. if the two multimap are not same type, then return false.
 *          if cpmap_first == cpmap_second, then return false.
 */
extern bool_t multimap_not_equal(const multimap_t* cpmmap_first, const multimap_t* cpmmap_second);

/**
 * Tests if the first multimap is less than the second multimap.
 * @param cpmap_first         first multimap container.
 * @param cpmap_second        second multimap container.
 * @return if first multimap is less than the second multimap, then return true, else return false.
 * @remarks if cpmap_first == NULL or cpmap_second == NULL, then the behavior is undefined. the two multimap must be
 *          initialized, otherwise the behavior is undefined. if the two multimap are not same type, the behavior is
 *          undefined. if cpmap_first == cpmap_second, then return false.
 */
extern bool_t multimap_less(const multimap_t* cpmmap_first, const multimap_t* cpmmap_second);

/**
 * Tests if the first multimap is less than or equal to the second multimap.
 * @param cpmap_first         first multimap container.
 * @param cpmap_second        second multimap container.
 * @return if first multimap is less than or equal to the second multimap, then return true, else return false.
 * @remarks if cpmap_first == NULL or cpmap_second == NULL, then the behavior is undefined. the two multimap must be
 *          initialized, otherwise the behavior is undefined. if the two multimap are not same type, the behavior is
 *          undefined. if cpmap_first == cpmap_second, then return true.
 */
extern bool_t multimap_less_equal(const multimap_t* cpmmap_first, const multimap_t* cpmmap_second);

/**
 * Tests if the first multimap is greater than the second multimap.
 * @param cpmap_first         first multimap container.
 * @param cpmap_second        second multimap container.
 * @return if first multimap is greater than the second multimap, then return true, else return false.
 * @remarks if cpmap_first == NULL or cpmap_second == NULL, then the behavior is undefined. the two multimap must be
 *          initialized, otherwise the behavior is undefined. if the two multimap are not same type, the behavior is
 *          undefined. if cpmap_first == cpmap_second, then return false.
 */
extern bool_t multimap_greater(const multimap_t* cpmmap_first, const multimap_t* cpmmap_second);

/**
 * Tests if the first multimap is greater than or equal to the second multimap.
 * @param cpmap_first         first multimap container.
 * @param cpmap_second        second multimap container.
 * @return if first multimap is greater than or equal to the second multimap, then return true, else return false.
 * @remarks if cpmap_first == NULL or cpmap_second == NULL, then the behavior is undefined. the two multimap must be
 *          initialized, otherwise the behavior is undefined. if the two multimap are not same type, the behavior is
 *          undefined. if cpmap_first == cpmap_second, then return true.
 */
extern bool_t multimap_greater_equal(const multimap_t* cpmmap_first, const multimap_t* cpmmap_second);

/**
 * Return an iterator that addresses the first element in the multimap.
 * @param cpmap_map      multimap container.
 * @return an iterator that addresses the first element in the multimap.
 * @remarks if cpmap_map == NULL, the behavior is undefined. cpmap_map must be initialized, otherwise the behavior is undefined.
 *          return map_end(), if the multimap is empty.
 */
extern multimap_iterator_t multimap_begin(const multimap_t* cpmmap_map);

/**
 * Return an iterator that addresses the location succeeding the last element in the multimap.
 * @param cpmap_map      multimap container.
 * @return an iterator that addresses location succeeding the last element in the multimap.
 * @remarks if cpmap_map == NULL, the behavior is undefined. cpmap_map must be initialized, otherwise the behavior is undefined.
 */
extern multimap_iterator_t multimap_end(const multimap_t* cpmmap_map);
/* private */
extern multimap_reverse_iterator_t multimap_rbegin(const multimap_t* cpmmap_map);
extern multimap_reverse_iterator_t multimap_rend(const multimap_t* cpmmap_map);

/**
 * Inserts an unique element into a multimap.
 * @param pmap_map       multimap container.
 * @param cppair_pair    specific element.
 * @return an iterator addresses the inserted element, or multimap end if insert failed.
 * @remarks if pmap_map == NULL then the behavior is undefined. cpmap_map must be initialized, otherwise the behavior is undefined.
 *          the type of specific element and cpmap_map must be same, otherwise the behavior is undefined.
 */
extern multimap_iterator_t multimap_insert(multimap_t* pmmap_map, const pair_t* cppair_pair);

/**
 * Inserts an unique element into a multimap with hint position.
 * @param pmap_map       multimap container.
 * @param it_hint        hint position.
 * @param cppair_pair    specific element.
 * @return an iterator addresses the inserted element, or multimap end if insert failed.
 * @remarks if pmap_map == NULL then the behavior is undefined. cpmap_map must be initialized, otherwise the behavior is undefined.
 *          the type of specific element and cpmap_map must be same, otherwise the behavior is undefined.
 */
extern multimap_iterator_t multimap_insert_hint(multimap_t* pmmap_map, multimap_iterator_t it_hint, const pair_t* cppair_pair);

/**
 * Inserts an range of element into a multimap.
 * @param pmap_map          multimap container.
 * @param it_begin          begin of specific range.
 * @param it_end            end of specific range.
 * @return void.
 * @remarks if pmap_map == NULL then the behavior is undefined. pmap_map must be initialized, otherwise the behavior
 *          is undefined. the type of [it_begin, it_end) and cpmap_map must be same, otherwise the behavior is undefined.
 *          [it_begin, it_end) must be valid range, otherwise the behavior is undefine.
 */
extern void multimap_insert_range(multimap_t* pmmap_map, iterator_t it_begin, iterator_t it_end);

/**
 * Inserts an array of element into a multimap.
 * @param pmap_map          multimap container.
 * @param cpv_array         array.
 * @param t_count           element count of array.
 * @return void.
 * @remarks if pmap_map == NULL then the behavior is undefined. pmap_map must be initialized, otherwise the behavior
 *          is undefined. the type of array and cpmap_map must be same, otherwise the behavior is undefined.
 *          array must be valid range, otherwise the behavior is undefine.
 */
extern void multimap_insert_array(multimap_t* pmmap_map, const void* cpv_array, size_t t_count);

/*
 * Erase an element in an multimap from specificed position.
 * @param pmap_map          multimap container.
 * @param it_pos            specificed position.
 * @return void.
 * @remarks if pmap_map == NULL then the behavior is undefined. pmap_map must be initialized, otherwise the behavior
 *          is undefined. it_pos must be valid iterator, otherwise the behavior is undefined.
 */
extern void multimap_erase_pos(multimap_t* pmmap_map, multimap_iterator_t it_pos);

/*
 * Erase a range of element in an multimap.
 * @param pmap_map          multimap container.
 * @param it_begin          begin of specific range.
 * @param it_end            end of specific range.
 * @return void.
 * @remarks if pmap_map == NULL then the behavior is undefined. pmap_map must be initialized, otherwise the behavior
 *          is undefined. [it_begin, it_end) must be valid range for pmap_map, otherwise the behavior is undefine.
 */
extern void multimap_erase_range(multimap_t* pmmap_map, multimap_iterator_t it_begin, multimap_iterator_t it_end);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_MULTIMAP_H_ */
/** eof **/

