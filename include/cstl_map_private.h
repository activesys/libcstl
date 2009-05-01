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
 * Create map.
 */
extern map_t _create_map(
    size_t t_keytypesize, const char* s_keytypename,
    size_t t_valuetypesize, const char* s_valuetypename);

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
extern pair_t _map_equal_range(const map_t* cpt_map, ...);
extern pair_t _map_equal_range_varg(const map_t* cpt_map, va_list val_elemlist);

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

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_MAP_PRIVATE_H */
/** eof **/

