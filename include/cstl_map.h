/*
 *  The interface of map.
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

#ifndef _CSTL_MAP_H
#define _CSTL_MAP_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
#define create_map(key_type, value_type)\
    _create_map(\
        sizeof(key_type), #key_type, \
        sizeof(value_type), #value_type)
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
 * ----------------------------------------------------------------------------
 *
 *      Functionname: map_init
 *        Parameters: in) pt_map: map_t*
 *           Returns: void
 *       Description: initialize the map.
 *
 * ----------------------------------------------------------------------------
 */
extern void map_init(map_t* pt_map);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: map_destroy
 *        Parameters: in) pt_map: map_t*
 *           Returns: void
 *       Description: destroy the map.
 *
 * ----------------------------------------------------------------------------
 */
extern void map_destroy(map_t* pt_map);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: map_init_copy
 *        Parameters: in) pt_mapdest: map_t*
 *                        the dest map pointer.
 *                    in) cpt_mapsrc: const map_t*
 *                        the src map pointer.
 *           Returns: void
 *       Description: the copy constructor.
 *
 * ----------------------------------------------------------------------------
 */
extern void map_init_copy(map_t* pt_mapdest, const map_t* cpt_mapsrc);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: map_init_copy_range_cmp
 *        Parameters: in) pt_mapdest: map_t*
 *                        the dest rb tree pointer.
 *                    in) t_begin: map_iterator_t
 *                        the begin iterator
 *                    in0 t_end: map_iterator_t
 *                        the end iterator.
 *                    in) pfun_key_cmp: int (*pfun)(const void*, const void*)
 *                          the function for element compare:
 *                          < 0  : element first < element second.
 *                          == 0 : element first == element second.
 *                          > 0  : element first > element second. 
 *           Returns: void
 *       Description: the copy constructor with range and key compare function.
 *
 * ----------------------------------------------------------------------------
 */
extern void map_init_copy_range_cmp(
    map_t* pt_mapdest, 
    map_iterator_t t_begin, 
    map_iterator_t t_end,
    int (*pfun_key_cmp)(const void*, const void*));

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: map_init_copy_range
 *        Parameters: in) pt_mapdest: map_t*
 *                        the dest rb tree pointer.
 *                    in) t_begin: map_iterator_t
 *                        the begin iterator
 *                    in0 t_end: map_iterator_t
 *                        the end iterator.
 *           Returns: void
 *       Description: the copy constructor with range.
 *
 * ----------------------------------------------------------------------------
 */
extern void map_init_copy_range(
    map_t* pt_mapdest, 
    map_iterator_t t_begin, 
    map_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: map_assign
 *        Parameters: in) pt_mapdest: map_t*
 *                        the dest map pointer.
 *                    in) cpt_mapsrc: const map_t*
 *                        the src map pointer.
 *           Returns: void
 *       Description: assign the map_t from src to dest.
 *
 * ----------------------------------------------------------------------------
 */
extern void map_assign(map_t* pt_mapdest, const map_t* cpt_mapsrc);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: map_swap
 *        Parameters: in) pt_mapfirst: map_t*
 *                          the first map.
 *                    in) pt_mapsecond: map_t*
 *                          the second map.
 *           Returns: void
 *       Description: swap the datas of first map and second map.
 *
 * ----------------------------------------------------------------------------
 */
extern void map_swap(map_t* pt_mapfirst, map_t* pt_mapsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: map_size
 *        Parameters: in) cpt_map: const map_t*
 *                          the dest map.
 *           Returns: size_t
 *       Description: get the map size.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t map_size(const map_t* cpt_map);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: map_empty
 *        Parameters: in) cpt_map: const map_t*
 *                          the dest map.
 *           Returns: bool_t
 *       Description: if the map is empty.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t map_empty(const map_t* cpt_map);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: map_max_size
 *        Parameters: in) cpt_map: const map_t*
 *                          the dest map.
 *           Returns: size_t
 *       Description: get the maximum capacity of map.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t map_max_size(const map_t* cpt_map);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: map_key_comp
 *        Parameters: in) cpt_map: const map_t*
 *                        the map pointer.
 *           Returns: int (*)(const void*, const void*)
 *       Description: return the compare function of key.
 *
 * ----------------------------------------------------------------------------
 */
extern int (*map_key_comp(const map_t* cpt_map))(const void*, const void*);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: map_value_comp
 *        Parameters: in) cpt_map: const map_t*
 *                        the map pointer.
 *           Returns: int (*)(const void*, const void*)
 *       Description: return the compare function of value.
 *
 * ----------------------------------------------------------------------------
 */
extern int (*map_value_comp(const map_t* cpt_map))(const void*, const void*);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: map_clear
 *        Parameters: in) pt_map: map_t*
 *                          the map.
 *           Returns: void
 *       Description: remove all elements.
 *
 * ----------------------------------------------------------------------------
 */
extern void map_clear(map_t* pt_map);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: map_equal
 *        Parameters: in) cpt_mapfirst: const map_t*
 *                          the first map.
 *                    in) cpt_mapsecond: const map_t*
 *                          the second map.
 *           Returns: bool_t
 *       Description: return whether first map equal to second map.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t map_equal(
    const map_t* cpt_mapfirst, const map_t* cpt_mapsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: map_not_equal
 *        Parameters: in) cpt_mapfirst: const map_t*
 *                          the first map.
 *                    in) cpt_mapsecond: const map_t*
 *                          the second map.
 *           Returns: bool_t
 *       Description: return whether first map not equal to second map.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t map_not_equal(
    const map_t* cpt_mapfirst, const map_t* cpt_mapsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: map_less
 *        Parameters: in) cpt_mapfirst: const map_t*
 *                          the first map.
 *                    in) cpt_mapsecond: const map_t*
 *                          the second map.
 *           Returns: bool_t
 *       Description: return whether first map less then second map.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t map_less(
    const map_t* cpt_mapfirst, const map_t* cpt_mapsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: map_great
 *        Parameters: in) cpt_mapfirst: const map_t*
 *                          the first map.
 *                    in) cpt_mapsecond: const map_t*
 *                          the second map.
 *           Returns: bool_t
 *       Description: return whether first map greater then second map.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t map_great(
    const map_t* cpt_mapfirst, const map_t* cpt_mapsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: map_less_equal
 *        Parameters: in) cpt_mapfirst: const map_t*
 *                          the first map.
 *                    in) cpt_mapsecond: const map_t*
 *                          the second map.
 *           Returns: bool_t
 *       Description: return whether first map less then or equal to the 
 *                    second map.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t map_less_equal(
    const map_t* cpt_mapfirst, const map_t* cpt_mapsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: map_great_equal
 *        Parameters: in) cpt_mapfirst: const map_t*
 *                          the first map.
 *                    in) cpt_mapsecond: const map_t*
 *                          the second map.
 *           Returns: bool_t
 *       Description: return whether first map greater then or equal to the
 *                    second map.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t map_great_equal(
    const map_t* cpt_mapfirst, const map_t* cpt_mapsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: map_begin
 *        Parameters: in) cpt_map: const map_t*
 *                          the map.
 *           Returns: map_iterator_t
 *       Description: return the random access iterator for the first element.
 *
 * ----------------------------------------------------------------------------
 */
extern map_iterator_t map_begin(const map_t* cpt_map);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: map_end
 *        Parameters: in) cpt_map: const map_t*
 *                          the map.
 *           Returns: map_iterator_t
 *       Description: return the random access iterator for the last element.
 *
 * ----------------------------------------------------------------------------
 */
extern map_iterator_t map_end(const map_t* cpt_map);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: map_rbegin
 *        Parameters: in) cpt_map: const map_t*
 *                          the map.
 *           Returns: map_reverse_iterator_t
 *       Description: return the reverse iterator for the first element of the
 *                    reverse iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern map_reverse_iterator_t map_rbegin(const map_t* cpt_map);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: map_rend
 *        Parameters: in) cpt_map: const map_t*
 *                          the map.
 *           Returns: map_reverse_iterator_t
 *       Description: return the reverse iterator for the last element of the
 *                    reverse iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern map_reverse_iterator_t map_rend(const map_t* cpt_map);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: map_insert
 *        Parameters: in) pt_map: map_t*
 *                        the map pointer.
 *                    in) cpt_pair: const pair_t*
 *                        the element pair.
 *           Returns: map_iterator_t
 *                        the insert result.
 *       Description: insert value into map.
 *
 * ----------------------------------------------------------------------------
 */
extern map_iterator_t map_insert(map_t* pt_map, const pair_t* cpt_pair);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: map_insert_hint
 *        Parameters: in) pt_map: map_t*
 *                        the map pointer.
 *                    in) t_hint: map_iterator_t
 *                        the hint iterator.
 *                    in) ...
 *                        the target value.
 *           Returns: map_iterator_t
 *                        the iterator of new element.
 *       Description: insert value into map.
 *
 * ----------------------------------------------------------------------------
 */
extern map_iterator_t map_insert_hint(
    map_t* pt_map, map_iterator_t t_hint, const pair_t* cpt_pair);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: map_insert_range
 *        Parameters: in) pt_map: map_t*
 *                        the rb tree pointer.
 *                    in) t_begin: map_iterator_t
 *                        the begin iterator
 *                    in0 t_end: map_iterator_t
 *                        the end iterator.
 *           Returns: void
 *       Description: insert a range into the map.
 *
 * ----------------------------------------------------------------------------
 */
extern void map_insert_range(
    map_t* pt_map, map_iterator_t t_begin, map_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: map_erase_pos
 *        Parameters: in) pt_map: map_t*
 *                        the rb tree pointer.
 *                    in) t_pos: map_iterator_t
 *                        the erase iterator.
 *           Returns: void
 *       Description: erase the element pointed by t_pos.
 *
 * ----------------------------------------------------------------------------
 */
extern void map_erase_pos(map_t* pt_map, map_iterator_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: map_erase_range
 *        Parameters: in) pt_map: map_t*
 *                        the rb tree pointer.
 *                    in) t_begin: map_iterator_t
 *                        the begin iterator.
 *                    in) t_end: map_iterator_t
 *                        the end iterator.
 *           Returns: void
 *       Description: erase the all elements in the range.
 *
 * ----------------------------------------------------------------------------
 */
extern void map_erase_range(
    map_t* pt_map, map_iterator_t t_begin, map_iterator_t t_end);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_MAP_H */
/** eof **/

