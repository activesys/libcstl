/*
 *  The interface of map.
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

#ifndef _CSTL_MAP_H_
#define _CSTL_MAP_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/**
 * Create map container.
 * @param ...        element type name.
 * @return if create map successfully return map pointer, otherwise return NULL.
 * @remarks element type name should be C builtin type name, libcstl builtin typename or registed user defined type name,
 *          otherwise the function will return NULL.
 */
#define create_map(...) _create_map(#__VA_ARGS__)

/**
 * Find specific element.
 * @param cpmap_map    map container.
 * @param elem         specific element.
 * @return iterator addresses the sprcific element in the map, otherwise return map_end().
 * @remarks if cpmap_map == NULL then the behavior is undefined. cpmap_map must be initialized, otherwise the behavior is undefined.
 *          the type of specific element and cpmap_map must be same, otherwise the behavior is undefined.
 */
#define map_find(cpmap_map, key_elem) _map_find((cpmap_map), (key_elem))

/**
 * Return the number of specific elements in an map
 * @param cpmap_map     map container.
 * @param elem          specific element.
 * @return the number of specific elements.
 * @remarks if cpmap_map == NULL then the behavior is undefined. cpmap_map must be initialized, otherwise the behavior is undefined.
 *          the type of specific element and cpmap_map must be same, otherwise the behavior is undefined.
 */
#define map_count(cpmap_map, key_elem) _map_count((cpmap_map), (key_elem))

/**
 * Return an iterator to the first element that is equal to or greater than a specific element.
 * @param cpmap_map    map container.
 * @param elem         specific element.
 * @return an iterator to the first element that is equal to or greater than a specific element.
 * @remarks if cpmap_map == NULL then the behavior is undefined. cpmap_map must be initialized, otherwise the behavior is undefined.
 *          the type of specific element and cpmap_map must be same, otherwise the behavior is undefined.
 */
#define map_lower_bound(cpmap_map, key_elem) _map_lower_bound((cpmap_map), (key_elem))

/**
 * Return an iterator to the first element that is greater than a specific element.
 * @param cpmap_map    map container.
 * @param elem         specific element.
 * @return an iterator to the first element that is greater than a specific element.
 * @remarks if cpmap_map == NULL then the behavior is undefined. cpmap_map must be initialized, otherwise the behavior is undefined.
 *          the type of specific element and cpmap_map must be same, otherwise the behavior is undefined.
 */
#define map_upper_bound(cpmap_map, key_elem) _map_upper_bound((cpmap_map), (key_elem))

/**
 * Return an iterator range that is equal to a specific element.
 * @param cpmap_map    map container.
 * @param elem         specific element.
 * @return an iterator range that is equal to a specific element.
 * @remarks if cpmap_map == NULL then the behavior is undefined. cpmap_map must be initialized, otherwise the behavior is undefined.
 *          the type of specific element and cpmap_map must be same, otherwise the behavior is undefined.
 */
#define map_equal_range(cpmap_map, key_elem) _map_equal_range((cpmap_map), (key_elem))

/**
 * Access an element with specific index.
 * @param pmap_map          map container.
 * @param key_elem          key element.
 * @return the pointer that point to the second element.
 * @remarks if pmap_map == NULL then the behavior is undefined. cpmap_map must be initialized, otherwise the behavior is
 *          undefined. 
 */
#define map_at(pmap_map, key_elem) _map_at((pmap_map), (key_elem))

/**
 * Erase an element from a map that match a specified element.
 * @param pmap_map       map container.
 * @param elem           specific element.
 * @return the number of erased elements.
 * @remarks if pmap_map == NULL then the behavior is undefined. cpmap_map must be initialized, otherwise the behavior is undefined. 
 */
#define map_erase(pmap_map, key_elem) _map_erase((pmap_map), (key_elem))

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Initialize map container.
 * @param pmap_map          map container.
 * @return void.
 * @remarks if pmap_map == NULL, then the behavior is undefined, pmap_map must be created by create_map(), otherwise
 *          the behavior is undefined. the default compare function is used.
 */
extern void map_init(map_t* pmap_map);

/**
 * Initialize map container with user define compare function.
 * @param pmap_map          map container.
 * @param t_compare         compare function.
 * @return void.
 * @remarks if pmap_map == NULL, then the behavior is undefined, pmap_map must be created by create_map(), otherwise
 *          the behavior is undefined. if t_compare == NULL, the default compare function is used.
 */
extern void map_init_ex(map_t* pmap_map, bfun_t bfun_keycompare);

/**
 * Initialize map container with map.
 * @param pmap_dest           destination map.
 * @param cpmap_src           source map.
 * @return void.
 * @remarks if pmap_dest == NULL or cpmap_src == NULL, then the behavior is undefined, pmap_dest must be created by
 *          create_map(), cpmap_src must be initialized, otherwise the behavior is undefined. the element type of
 *          pmap_dest and cpmap_src must be same, otherwise the behavior is undefine.
 */
extern void map_init_copy(map_t* pmap_dest, const map_t* cpmap_src);

/**
 * Initialize map container with specific range.
 * @param pmap_dest         destination map.
 * @param it_begin          begin of range.
 * @param it_end            end of range.
 * @return void.
 * @remarks if pmap_dest == NULL, then the behavior is undefined, pmap_dest must be created by create_map(), otherwise
 *          the behavior is undefined. the type of [it_begin, it_end) and pmap_dest must be same, otherwise the behavior
 *          is undefined.
 */
extern void map_init_copy_range(map_t* pmap_dest, iterator_t it_begin, iterator_t it_end);

/**
 * Initialize map container with specific array.
 * @param pmap_dest         destination map.
 * @param cpv_array         array.
 * @param t_count           element count of array.
 * @return void.
 * @remarks if pmap_dest == NULL, then the behavior is undefined, pmap_dest must be created by create_map(), otherwise
 *          the behavior is undefined. the type of array and pmap_dest must be same, otherwise the behavior
 *          is undefined.
 */
extern void map_init_copy_array(map_t* pmap_dest, const void* cpv_array, size_t t_count);

/**
 * Initialize map container with specific range and compare function.
 * @param pmap_dest         destination map.
 * @param it_begin          begin of range.
 * @param it_end            end of range.
 * @param t_compare         compare function.
 * @return void.
 * @remarks if pmap_dest == NULL, then the behavior is undefined, pmap_dest must be created by _create_map(), otherwise
 *          the behavior is undefined. the type of [it_begin, it_end) and pmap_dest must be same, otherwise the behavior
 *          is undefined. if t_compare == NULL, then use default compare function.
 */
extern void map_init_copy_range_ex(
    map_t* pmap_dest, iterator_t it_begin, iterator_t it_end, bfun_t bfun_keycompare);

/**
 * Initialize map container with specific array and compare function.
 * @param pmap_dest         destination map.
 * @param cpv_array         array.
 * @param t_count           element count of array.
 * @param t_compare         compare function.
 * @return void.
 * @remarks if pmap_dest == NULL, then the behavior is undefined, pmap_dest must be created by _create_map(), otherwise
 *          the behavior is undefined. the type of array and pmap_dest must be same, otherwise the behavior
 *          is undefined. if t_compare == NULL, then use default compare function.
 */
extern void map_init_copy_array_ex(
    map_t* pmap_dest, const void* cpv_array, size_t t_count, bfun_t bfun_keycompare);

/**
 * Destroy map.
 * @param pmap_map       map container.
 * @return void.
 * @remarks if pmap_map == NULL, then the behavior is undefined, the map must be initialized or created by create_map(),
 *          otherwise the behavior is undefined.
 */
extern void map_destroy(map_t* pmap_map);

/**
 * Assign map container.
 * @param pmap_dest           destination map container.
 * @param cpmap_src           source map container.
 * @return void.
 * @remarks if pmap_dest == NULL or cpmap_src == NULL, the the behavior is undefined. two map must be initialized, otherwise
 *          the behavior is undefined. if map_equal(pmap_dest, cpmap_src), the function dest nothing.
 */
extern void map_assign(map_t* pmap_dest, const map_t* cpmap_src);

/**
 * Swap the datas of first map and second map.
 * @param pt_first          first map container.
 * @param pt_second         second map container.
 * @return void.
 * @remarks if pt_first == NULL or pt_second == NULL, then the behavior is undefined. the two map must be initialized,
 *          otherwise the behavior is undefined. if the two map are not same type, the behavior is undefined. if
 *          map_equal(cpt_first, cpt_second), then the function do nothing.
 */
extern void map_swap(map_t* pmap_first, map_t* pmap_second);

/**
 * Get the number of elements int the map.
 * @param cpmap_map      map container.
 * @return the number of elements in the map.
 * @remarks if cpmap_map == NULL, then the behavior is undefined, the cpmap_map must be initialized, otherwise the behavior
 *          is undefined.
 */
extern size_t map_size(const map_t* cpmap_map);

/**
 * Test if an map is empty.
 * @param cpmap_map      map container.
 * @return true if the map is empty, otherwise return false.
 * @remarks if cpmap_map == NULL, then the behavior is undefined, the cpmap_map must be initialized, otherwise the behavior
 *          is undefined.
 */
extern bool_t map_empty(const map_t* cpmap_map);

/**
 * Get the maximum number of elements int the map.
 * @param cpmap_map      map container.
 * @return the maximum number of elements in the map.
 * @remarks if cpmap_map == NULL, then the behavior is undefined, the cpmap_map must be initialized, otherwise the behavior
 *          is undefined.
 */
extern size_t map_max_size(const map_t* cpmap_map);

/**
 * Return an iterator that addresses the first element in the map.
 * @param cpmap_map      map container.
 * @return an iterator that addresses the first element in the map.
 * @remarks if cpmap_map == NULL, the behavior is undefined. cpmap_map must be initialized, otherwise the behavior is undefined.
 *          return map_end(), if the map is empty.
 */
extern map_iterator_t map_begin(const map_t* cpmap_map);

/**
 * Return an iterator that addresses the location succeeding the last element in the map.
 * @param cpmap_map      map container.
 * @return an iterator that addresses location succeeding the last element in the map.
 * @remarks if cpmap_map == NULL, the behavior is undefined. cpmap_map must be initialized, otherwise the behavior is undefined.
 */
extern map_iterator_t map_end(const map_t* cpmap_map);
/* private */
extern map_reverse_iterator_t map_rbegin(const map_t* cpmap_map);
extern map_reverse_iterator_t map_rend(const map_t* cpmap_map);

/**
 * Return the compare function of key.
 * @param cpmap_map      map container.
 * @return compare function.
 * @remarks if cpmap_map == NULL, the behavior is undefined. cpmap_map must be initialized, otherwise the behavior is undefined.
 */
extern bfun_t map_key_comp(const map_t* cpmap_map);

/**
 * Return the compare function of value.
 * @param cpmap_map      map container.
 * @return compare function.
 * @remarks if cpmap_map == NULL, the behavior is undefined. cpmap_map must be initialized, otherwise the behavior is undefined.
 */
extern bfun_t map_value_comp(const map_t* cpmap_map);

/**
 * Inserts an unique element into a map.
 * @param pmap_map       map container.
 * @param cppair_pair    specific element.
 * @return an iterator addresses the inserted element, or map end if insert failed.
 * @remarks if pmap_map == NULL then the behavior is undefined. cpmap_map must be initialized, otherwise the behavior is undefined.
 *          the type of specific element and cpmap_map must be same, otherwise the behavior is undefined.
 */
extern map_iterator_t map_insert(map_t* pmap_map, const pair_t* cppair_pair);

/**
 * Inserts an unique element into a map with hint position.
 * @param pmap_map       map container.
 * @param it_hint        hint position.
 * @param cppair_pair    specific element.
 * @return an iterator addresses the inserted element, or map end if insert failed.
 * @remarks if pmap_map == NULL then the behavior is undefined. cpmap_map must be initialized, otherwise the behavior is undefined.
 *          the type of specific element and cpmap_map must be same, otherwise the behavior is undefined.
 */
extern map_iterator_t map_insert_hint(map_t* pmap_map, map_iterator_t it_hint, const pair_t* cppair_pair);

/**
 * Inserts an range of unique element into a map.
 * @param pmap_map          map container.
 * @param it_begin          begin of specific range.
 * @param it_end            end of specific range.
 * @return void.
 * @remarks if pmap_map == NULL then the behavior is undefined. pmap_map must be initialized, otherwise the behavior
 *          is undefined. the type of [it_begin, it_end) and cpmap_map must be same, otherwise the behavior is undefined.
 *          [it_begin, it_end) must be valid range, otherwise the behavior is undefine.
 */
extern void map_insert_range(map_t* pmap_map, iterator_t it_begin, iterator_t it_end);

/**
 * Inserts an array of unique element into a map.
 * @param pmap_map          map container.
 * @param cpv_array         array.
 * @param t_count           element count of array.
 * @return void.
 * @remarks if pmap_map == NULL then the behavior is undefined. pmap_map must be initialized, otherwise the behavior
 *          is undefined. the type of array and cpmap_map must be same, otherwise the behavior is undefined.
 *          array must be valid range, otherwise the behavior is undefine.
 */
extern void map_insert_array(map_t* pmap_map, const void* cpv_array, size_t t_count);

/*
 * Erase an element in an map from specificed position.
 * @param pmap_map          map container.
 * @param it_pos            specificed position.
 * @return void.
 * @remarks if pmap_map == NULL then the behavior is undefined. pmap_map must be initialized, otherwise the behavior
 *          is undefined. it_pos must be valid iterator, otherwise the behavior is undefined.
 */
extern void map_erase_pos(map_t* pmap_map, map_iterator_t it_pos);

/*
 * Erase a range of element in an map.
 * @param pmap_map          map container.
 * @param it_begin          begin of specific range.
 * @param it_end            end of specific range.
 * @return void.
 * @remarks if pmap_map == NULL then the behavior is undefined. pmap_map must be initialized, otherwise the behavior
 *          is undefined. [it_begin, it_end) must be valid range for pmap_map, otherwise the behavior is undefine.
 */
extern void map_erase_range(map_t* pmap_map, map_iterator_t it_begin, map_iterator_t it_end);

/**
 * Erases all the elements of an map.
 * @param pmap_map       map container.
 * @return void.
 * @remarks if pmap_map == NULL, the behavior is undefined. pmap_map must be initialized, otherwise the behavior is undefined.
 */
extern void map_clear(map_t* pmap_map);

/**
 * Tests if the two map are equal.
 * @param cpmap_first         first map container.
 * @param cpmap_second        second map container.
 * @return if first map equal to second map, then return true, else return false.
 * @remarks if cpmap_first == NULL or cpmap_second == NULL, then the behavior is undefined. the two map must be
 *          initialized, otherwise the behavior is undefined. if the two map are not same type, then return false.
 *          if cpmap_first == cpmap_second, then return true.
 */
extern bool_t map_equal(const map_t* cpmap_first, const map_t* cpmap_second);

/**
 * Tests if the two map are not equal.
 * @param cpmap_first         first map container.
 * @param cpmap_second        second map container.
 * @return if first map not equal to second map, then return true, else return false.
 * @remarks if cpmap_first == NULL or cpmap_second == NULL, then the behavior is undefined. the two map must be
 *          initialized, otherwise the behavior is undefined. if the two map are not same type, then return false.
 *          if cpmap_first == cpmap_second, then return false.
 */
extern bool_t map_not_equal(const map_t* cpmap_first, const map_t* cpmap_second);

/**
 * Tests if the first map is less than the second map.
 * @param cpmap_first         first map container.
 * @param cpmap_second        second map container.
 * @return if first map is less than the second map, then return true, else return false.
 * @remarks if cpmap_first == NULL or cpmap_second == NULL, then the behavior is undefined. the two map must be
 *          initialized, otherwise the behavior is undefined. if the two map are not same type, the behavior is
 *          undefined. if cpmap_first == cpmap_second, then return false.
 */
extern bool_t map_less(const map_t* cpmap_first, const map_t* cpmap_second);

/**
 * Tests if the first map is less than or equal to the second map.
 * @param cpmap_first         first map container.
 * @param cpmap_second        second map container.
 * @return if first map is less than or equal to the second map, then return true, else return false.
 * @remarks if cpmap_first == NULL or cpmap_second == NULL, then the behavior is undefined. the two map must be
 *          initialized, otherwise the behavior is undefined. if the two map are not same type, the behavior is
 *          undefined. if cpmap_first == cpmap_second, then return true.
 */
extern bool_t map_less_equal(const map_t* cpmap_first, const map_t* cpmap_second);

/**
 * Tests if the first map is greater than the second map.
 * @param cpmap_first         first map container.
 * @param cpmap_second        second map container.
 * @return if first map is greater than the second map, then return true, else return false.
 * @remarks if cpmap_first == NULL or cpmap_second == NULL, then the behavior is undefined. the two map must be
 *          initialized, otherwise the behavior is undefined. if the two map are not same type, the behavior is
 *          undefined. if cpmap_first == cpmap_second, then return false.
 */
extern bool_t map_greater(const map_t* cpmap_first, const map_t* cpmap_second);

/**
 * Tests if the first map is greater than or equal to the second map.
 * @param cpmap_first         first map container.
 * @param cpmap_second        second map container.
 * @return if first map is greater than or equal to the second map, then return true, else return false.
 * @remarks if cpmap_first == NULL or cpmap_second == NULL, then the behavior is undefined. the two map must be
 *          initialized, otherwise the behavior is undefined. if the two map are not same type, the behavior is
 *          undefined. if cpmap_first == cpmap_second, then return true.
 */
extern bool_t map_greater_equal(const map_t* cpmap_first, const map_t* cpmap_second);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_MAP_H_ */
/** eof **/

