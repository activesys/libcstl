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

#ifndef _CSTL_MAP_H
#define _CSTL_MAP_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
#define create_map(...) _create_map(#__VA_ARGS__)
/* find */
#define map_find(cpt_map, key_elem)\
    _map_find((cpt_map), (key_elem))
/* count */
#define map_count(cpt_map, key_elem)\
    _map_count((cpt_map), (key_elem))
/* lower bound */
#define map_lower_bound(cpt_map, key_elem)\
    _map_lower_bound((cpt_map), (key_elem))
/* upper bound */
#define map_upper_bound(cpt_map, key_elem)\
    _map_upper_bound((cpt_map), (key_elem))
/* equal range */
#define map_equal_range(cpt_map, key_elem)\
    _map_equal_range((cpt_map), (key_elem))
/* at */
#define map_at(pt_map, key_elem)\
    _map_at((pt_map), (key_elem))
/* erase */
#define map_erase(pt_map, key_elem)\
    _map_erase((pt_map), (key_elem))

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * Initialization and destroy functions.
 */
extern void map_init(map_t* pt_map);
extern void map_init_ex(map_t* pt_map, binary_function_t t_keycompare);
extern void map_destroy(map_t* pt_map);
extern void map_init_copy(map_t* pt_mapdest, const map_t* cpt_mapsrc);
extern void map_init_copy_range_ex(map_t* pt_mapdest,
    map_iterator_t t_begin, map_iterator_t t_end, binary_function_t t_keycompare);
extern void map_init_copy_range(
    map_t* pt_mapdest, map_iterator_t t_begin, map_iterator_t t_end);

/*
 * Assign operator function.
 */
extern void map_assign(map_t* pt_mapdest, const map_t* cpt_mapsrc);

/*
 * Swap the datas of first map and second map.
 */
extern void map_swap(map_t* pt_mapfirst, map_t* pt_mapsecond);

/*
 * map_t size operation functions.
 */
extern size_t map_size(const map_t* cpt_map);
extern bool_t map_empty(const map_t* cpt_map);
extern size_t map_max_size(const map_t* cpt_map);

/*
 * Return the compare function of key.
 */
extern binary_function_t map_key_comp(const map_t* cpt_map);
extern binary_function_t map_value_comp(const map_t* cpt_map);

/*
 * Remove all elements.
 */
extern void map_clear(map_t* pt_map);

/*
 * Relationship operator functions.
 */
extern bool_t map_equal(const map_t* cpt_mapfirst, const map_t* cpt_mapsecond);
extern bool_t map_not_equal(const map_t* cpt_mapfirst, const map_t* cpt_mapsecond);
extern bool_t map_less(const map_t* cpt_mapfirst, const map_t* cpt_mapsecond);
extern bool_t map_greater(const map_t* cpt_mapfirst, const map_t* cpt_mapsecond);
extern bool_t map_less_equal(const map_t* cpt_mapfirst, const map_t* cpt_mapsecond);
extern bool_t map_greater_equal(const map_t* cpt_mapfirst, const map_t* cpt_mapsecond);

/*
 * Iterator support.
 */
extern map_iterator_t map_begin(const map_t* cpt_map);
extern map_iterator_t map_end(const map_t* cpt_map);
/* private */
extern map_reverse_iterator_t map_rbegin(const map_t* cpt_map);
extern map_reverse_iterator_t map_rend(const map_t* cpt_map);

/*
 * Insert operation functions.
 */
extern map_iterator_t map_insert(map_t* pt_map, const pair_t* cpt_pair);
extern map_iterator_t map_insert_hint(
    map_t* pt_map, map_iterator_t t_hint, const pair_t* cpt_pair);
extern void map_insert_range(map_t* pt_map, map_iterator_t t_begin, map_iterator_t t_end);

/*
 * Erase element operation functions.
 */
extern void map_erase_pos(map_t* pt_map, map_iterator_t t_pos);
extern void map_erase_range(map_t* pt_map, map_iterator_t t_begin, map_iterator_t t_end);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_MAP_H */
/** eof **/

