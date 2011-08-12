/*
 *  The interface of map.
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
/* find */
#define map_find(cpmap_map, key_elem)\
    _map_find((cpmap_map), (key_elem))
/* count */
#define map_count(cpmap_map, key_elem)\
    _map_count((cpmap_map), (key_elem))
/* lower bound */
#define map_lower_bound(cpmap_map, key_elem)\
    _map_lower_bound((cpmap_map), (key_elem))
/* upper bound */
#define map_upper_bound(cpmap_map, key_elem)\
    _map_upper_bound((cpmap_map), (key_elem))
/* equal range */
#define map_equal_range(cpmap_map, key_elem)\
    _map_equal_range((cpmap_map), (key_elem))
/* at */
#define map_at(pmap_map, key_elem)\
    _map_at((pmap_map), (key_elem))
/* erase */
#define map_erase(pmap_map, key_elem)\
    _map_erase((pmap_map), (key_elem))

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
extern void map_init_ex(map_t* pmap_map, binary_function_t t_keycompare);

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
 *          the behavior is undefined. [it_begin, it_end) must be belong to a initialized map, otherwise the behavior
 *          is undefined. the type of [it_begin, it_end) and pmap_dest must be same, otherwise the behavior is undefined.
 */
extern void map_init_copy_range(map_t* pmap_dest, map_iterator_t it_begin, map_iterator_t it_end);

/**
 * Initialize map container with specific range and compare function.
 * @param pmap_dest         destination map.
 * @param it_begin          begin of range.
 * @param it_end            end of range.
 * @param t_compare         compare function.
 * @return void.
 * @remarks if pmap_dest == NULL, then the behavior is undefined, pmap_dest must be created by _create_map(), otherwise
 *          the behavior is undefined. [it_begin, it_end) must be belong to a initialized map, otherwise the behavior
 *          is undefined. the type of [it_begin, it_end) and pmap_dest must be same, otherwise the behavior is undefined. if
 *          t_compare == NULL, then use default compare function.
 */
extern void map_init_copy_range_ex(map_t* pmap_dest,
    map_iterator_t it_begin, map_iterator_t it_end, binary_function_t t_keycompare);

extern void map_destroy(map_t* pmap_map);

/*
 * Assign operator function.
 */
extern void map_assign(map_t* pmap_dest, const map_t* cpmap_src);

/*
 * Swap the datas of first map and second map.
 */
extern void map_swap(map_t* pmap_first, map_t* pmap_second);

/*
 * map_t size operation functions.
 */
extern size_t map_size(const map_t* cpmap_map);
extern bool_t map_empty(const map_t* cpmap_map);
extern size_t map_max_size(const map_t* cpmap_map);

/*
 * Return the compare function of key.
 */
extern binary_function_t map_key_comp(const map_t* cpmap_map);
extern binary_function_t map_value_comp(const map_t* cpmap_map);

/*
 * Remove all elements.
 */
extern void map_clear(map_t* pmap_map);

/*
 * Relationship operator functions.
 */
extern bool_t map_equal(const map_t* cpmap_first, const map_t* cpmap_second);
extern bool_t map_not_equal(const map_t* cpmap_first, const map_t* cpmap_second);
extern bool_t map_less(const map_t* cpmap_first, const map_t* cpmap_second);
extern bool_t map_greater(const map_t* cpmap_first, const map_t* cpmap_second);
extern bool_t map_less_equal(const map_t* cpmap_first, const map_t* cpmap_second);
extern bool_t map_greater_equal(const map_t* cpmap_first, const map_t* cpmap_second);

/*
 * Iterator support.
 */
extern map_iterator_t map_begin(const map_t* cpmap_map);
extern map_iterator_t map_end(const map_t* cpmap_map);
/* private */
extern map_reverse_iterator_t map_rbegin(const map_t* cpmap_map);
extern map_reverse_iterator_t map_rend(const map_t* cpmap_map);

/*
 * Insert operation functions.
 */
extern map_iterator_t map_insert(map_t* pmap_map, const pair_t* cpt_pair);
extern map_iterator_t map_insert_hint(
    map_t* pmap_map, map_iterator_t t_hint, const pair_t* cpt_pair);
extern void map_insert_range(map_t* pmap_map, map_iterator_t it_begin, map_iterator_t it_end);

/*
 * Erase element operation functions.
 */
extern void map_erase_pos(map_t* pmap_map, map_iterator_t t_pos);
extern void map_erase_range(map_t* pmap_map, map_iterator_t it_begin, map_iterator_t it_end);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_MAP_H_ */
/** eof **/

