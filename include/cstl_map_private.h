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

/** data type declaration and struct, union, enum section **/
/* the map use rb tree default */
typedef struct _tagmap
{
    pair_t            _t_pair;
    binary_function_t _t_keyless;   /* for init ex */
    binary_function_t _t_valueless;

#ifdef CSTL_MAP_AVL_TREE
    avl_tree_t        _t_tree;
#else
    rb_tree_t         _t_tree;
#endif
}map_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * Create map.
 */
extern map_t* _create_map(const char* s_typename);
extern bool_t _create_map_auxiliary(map_t* pt_map, const char* s_typename);
extern void _map_destroy_auxiliary(map_t* pt_map);

/*
 * Find operation functions.
 */
extern map_iterator_t _map_find(const map_t* cpt_map, ...);
extern map_iterator_t _map_find_varg(const map_t* cpt_map, va_list val_elemlist);

/*
 * Count, lower bound, upper bound and equal range operation functions.
 */
extern size_t _map_count(const map_t* cpt_map, ...);
extern size_t _map_count_varg(const map_t* cpt_map, va_list val_elemlist);
extern map_iterator_t _map_lower_bound(const map_t* cpt_map, ...);
extern map_iterator_t _map_lower_bound_varg(const map_t* cpt_map, va_list val_elemlist);
extern map_iterator_t _map_upper_bound(const map_t* cpt_map, ...);
extern map_iterator_t _map_upper_bound_varg(const map_t* cpt_map, va_list val_elemlist);
extern range_t _map_equal_range(const map_t* cpt_map, ...);
extern range_t _map_equal_range_varg(const map_t* cpt_map, va_list val_elemlist);

/*
 * Random access operation functions.
 */
extern void* _map_at(map_t* pt_map, ...);
extern void* _map_at_varg(map_t* pt_map, va_list val_elemlist);

/*
 * Erase operation functions.
 */
extern size_t _map_erase(map_t* pt_map, ...);
extern size_t _map_erase_varg(map_t* pt_map, va_list val_elemlist);

extern void _map_init_elem_auxiliary(map_t* pt_map, void* pv_value);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_MAP_PRIVATE_H */
/** eof **/

