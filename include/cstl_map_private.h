/*
 *  The private interface of map.
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

#ifndef _CSTL_MAP_PRIVATE_H
#define _CSTL_MAP_PRIVATE_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
#define _GET_MAP_AVL_TREE(pt_map)\
    (&((pt_map)->_t_tree._t_avl))
#define _GET_MAP_RB_TREE(pt_map)\
    (&((pt_map)->_t_tree._t_rb))

/** data type declaration and struct, union, enum section **/
/* the map use rb tree default */
typedef struct _tagmap
{
    pair_t _t_pair;
    union
    {
        avl_tree_t _t_avl;
        rb_tree_t  _t_rb;
    }_t_tree;
}map_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _create_map
 *        Parameters: in) t_keytypesize: size_t
 *                          the key element type size.
 *                    in) s_keytypename: const char*
 *                          the key element type name.
 *                    in) t_valuetypesize: size_t
 *                          the value element type size.
 *                    in) s_valuetypename: const char*
 *                          the value element type name.
 *           Returns: map_t
 *                          new map.
 *       Description: create the new map.
 *
 * ----------------------------------------------------------------------------
 */
extern map_t _create_map(
    size_t t_keytypesize, const char* s_keytypename,
    size_t t_valuetypesize, const char* s_valuetypename);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _map_find
 *        Parameters: in) cpt_map: const map_t*
 *                        the map pointer.
 *                    in) ...
 *                        the target value.
 *           Returns: map_iterator_t
 *                        the target iterator or end iterator.
 *       Description: find the value in map.
 *
 * ----------------------------------------------------------------------------
 */
extern map_iterator_t _map_find(const map_t* cpt_map, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _map_find_varg
 *        Parameters: in) cpt_map: const map_t*
 *                        the map pointer.
 *                    in) val_elemlist: va_list
 *                        the target value.
 *           Returns: map_iterator_t
 *                        the target iterator or end iterator.
 *       Description: find the value in map.
 *
 * ----------------------------------------------------------------------------
 */
extern map_iterator_t _map_find_varg(const map_t* cpt_map, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _map_count
 *        Parameters: in) cpt_map: const map_t*
 *                        the map pointer.
 *                    in) ...
 *                        the target value.
 *           Returns: size_t
 *                        count.
 *       Description: counts the numbers of element whose key is value.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t _map_count(const map_t* cpt_map, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _map_count_varg
 *        Parameters: in) cpt_map: const map_t*
 *                        the map pointer.
 *                    in) val_elemlist: va_list
 *                        the target value.
 *           Returns: size_t
 *                        count.
 *       Description: counts the numbers of element whose key is value.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t _map_count_varg(const map_t* cpt_map, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _map_lower_bound
 *        Parameters: in) cpt_map: const map_t*
 *                        the map pointer.
 *                    in) ...
 *                        the target value.
 *           Returns: map_iterator_t
 *                        the target iterator or end iterator.
 *       Description: find the first element whose key is not less then value.
 *
 * ----------------------------------------------------------------------------
 */
extern map_iterator_t _map_lower_bound(const map_t* cpt_map, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _map_lower_bound_varg
 *        Parameters: in) cpt_map: const map_t*
 *                        the map pointer.
 *                    in) val_elemlist: va_list
 *                        the target value.
 *           Returns: map_iterator_t
 *                        the target iterator or end iterator.
 *       Description: find the first element whose key is not less then value.
 *
 * ----------------------------------------------------------------------------
 */
extern map_iterator_t _map_lower_bound_varg(
    const map_t* cpt_map, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _map_upper_bound
 *        Parameters: in) cpt_map: const map_t*
 *                        the map pointer.
 *                    in) ...
 *                        the target value.
 *           Returns: map_iterator_t
 *                        the target iterator or end iterator.
 *       Description: find the first element whose key is greater then value.
 *
 * ----------------------------------------------------------------------------
 */
extern map_iterator_t _map_upper_bound(const map_t* cpt_map, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _map_upper_bound_varg
 *        Parameters: in) cpt_map: const map_t*
 *                        the map pointer.
 *                    in) val_elemlist: va_list
 *                        the target value.
 *           Returns: map_iterator_t
 *                        the target iterator or end iterator.
 *       Description: find the first element whose key is greater then value.
 *
 * ----------------------------------------------------------------------------
 */
extern map_iterator_t _map_upper_bound_varg(
    const map_t* cpt_map, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _map_equal_range
 *        Parameters: in) cpt_map: const map_t*
 *                        the map pointer.
 *                    in) ...
 *                        the target value.
 *           Returns: pair_t(map_iterator_t, map_iterator_t).
 *       Description: find a range that contain all elements whos key is value.
 *
 * ----------------------------------------------------------------------------
 */
extern pair_t _map_equal_range(const map_t* cpt_map, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _map_equal_range_varg
 *        Parameters: in) cpt_map: const map_t*
 *                        the map pointer.
 *                    in) val_elemlist: va_list
 *                        the target value.
 *           Returns: pair_t(map_iterator_t, map_iterator_t).
 *       Description: find a range that contain all elements whos key is value.
 *
 * ----------------------------------------------------------------------------
 */
extern pair_t _map_equal_range_varg(const map_t* cpt_map, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _map_at
 *        Parameters: in) pt_map: map_t*
 *                        the rb tree pointer.
 *                    in) ...
 *                        the target value.
 *           Returns: void*
 *                        the value pointer
 *       Description: return the value pointer that is associate with the key.
 *                    if the element is not already in the map, this function 
 *                    will insert the element.
 *
 * ----------------------------------------------------------------------------
 */
extern void* _map_at(map_t* pt_map, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _map_at_varg
 *        Parameters: in) pt_map: map_t*
 *                        the rb tree pointer.
 *                    in) val_elemlist: va_list
 *                        the target value.
 *           Returns: void*
 *                        the value pointer
 *       Description: return the value pointer that is associate with the key.
 *                    if the element is not already in the map, this function 
 *                    will insert the element.
 *
 * ----------------------------------------------------------------------------
 */
extern void* _map_at_varg(map_t* pt_map, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _map_erase
 *        Parameters: in) pt_map: map_t*
 *                        the rb tree pointer.
 *                    in) ...
 *                        the target value.
 *           Returns: size_t
 *                        the element numbers.
 *       Description: erase all elements whose key is value.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t _map_erase(map_t* pt_map, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _map_erase_varg
 *        Parameters: in) pt_map: map_t*
 *                        the rb tree pointer.
 *                    in) val_elemlist: va_list
 *                        the target value.
 *           Returns: size_t
 *                        the element numbers.
 *       Description: erase all elements whose key is value.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t _map_erase_varg(map_t* pt_map, va_list val_elemlist);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_MAP_PRIVATE_H */
/** eof **/

