/*
 *  The private interface of multimap.
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

#ifndef _CSTL_MULTIMAP_PRIVATE_H_
#define _CSTL_MULTIMAP_PRIVATE_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
/* the multimap use rb tree default */
typedef struct _tagmultimap
{
    pair_t            _t_pair;
    binary_function_t _t_keycompare; /* for init ex */
    binary_function_t _t_valuecompare;

#ifdef CSTL_MULTIMAP_AVL_TREE
    avl_tree_t        _t_tree;
#else
    _rb_tree_t         _t_tree;
#endif
}multimap_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * Create the new multimap.
 */
extern multimap_t* _create_multimap(const char* s_typename);
extern bool_t _create_multimap_auxiliary(multimap_t* pt_multimap, const char* s_typename);
extern void _multimap_destroy_auxiliary(multimap_t* pt_multimap);

/*
 * Find operation functions.
 */
extern multimap_iterator_t _multimap_find(const multimap_t* cpt_multimap, ...);
extern multimap_iterator_t _multimap_find_varg(
    const multimap_t* cpt_multimap, va_list val_elemlist);

/*
 * Count operation functions.
 */
extern size_t _multimap_count(const multimap_t* cpt_multimap, ...);
extern size_t _multimap_count_varg(const multimap_t* cpt_multimap, va_list val_elemlist);

/*
 * Lower bound, upper bound and equal range operation functions.
 */
extern multimap_iterator_t _multimap_lower_bound(const multimap_t* cpt_multimap, ...);
extern multimap_iterator_t _multimap_lower_bound_varg(
    const multimap_t* cpt_multimap, va_list val_elemlist);
extern multimap_iterator_t _multimap_upper_bound(const multimap_t* cpt_multimap, ...);
extern multimap_iterator_t _multimap_upper_bound_varg(
    const multimap_t* cpt_multimap, va_list val_elemlist);
extern range_t _multimap_equal_range(const multimap_t* cpt_multimap, ...);
extern range_t _multimap_equal_range_varg(
    const multimap_t* cpt_multimap, va_list val_elemlist);

/*
 * Erase operation functions.
 */
extern size_t _multimap_erase(multimap_t* pt_multimap, ...);
extern size_t _multimap_erase_varg(multimap_t* pt_multimap, va_list val_elemlist);

extern void _multimap_init_elem_auxiliary(multimap_t* pt_multimap, void* pv_value);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_MULTIMAP_PRIVATE_H_ */
/** eof **/

