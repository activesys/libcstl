/*
 *  The private interface of multiset.
 *  Copyright (C)  2008,2009,2010  Wangbo
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

#ifndef _CSTL_MULTISET_PRIVATE_H
#define _CSTL_MULTISET_PRIVATE_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
/* the multiset use rb tree default */
typedef struct _tagmultiset
{
#ifdef CSTL_MULTISET_AVL_TREE
    avl_tree_t _t_tree;
#else
    rb_tree_t  _t_tree;
#endif
}multiset_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * Create new multiset_t.
 */
extern multiset_t* _create_multiset(const char* s_typename);
extern bool_t _create_multiset_auxiliary(multiset_t* pt_multiset, const char* s_typename);
extern void _multiset_destroy_auxiliary(multiset_t* pv_multiset);

/*
 * Find operation functions.
 */
extern multiset_iterator_t _multiset_find(const multiset_t* cpt_multiset, ...);
extern multiset_iterator_t _multiset_find_varg(
    const multiset_t* cpt_multiset, va_list val_elemlist);

/*
 * Count operation functions.
 */
extern size_t _multiset_count(const multiset_t* cpt_multiset, ...);
extern size_t _multiset_count_varg(const multiset_t* cpt_multiset, va_list val_elemlist);

/*
 * Lower bound, uppder bound and equal range functions.
 */
extern multiset_iterator_t _multiset_lower_bound(const multiset_t* cpt_multiset, ...);
extern multiset_iterator_t _multiset_lower_bound_varg(
    const multiset_t* cpt_multiset, va_list val_elemlist);
extern multiset_iterator_t _multiset_upper_bound(const multiset_t* cpt_multiset, ...);
extern multiset_iterator_t _multiset_upper_bound_varg(
    const multiset_t* cpt_multiset, va_list val_elemlist);
extern range_t _multiset_equal_range(const multiset_t* cpt_multiset, ...);
extern range_t _multiset_equal_range_varg(
    const multiset_t* cpt_multiset, va_list val_elemlist);

/*
 * Erase operation functions.
 */
extern size_t _multiset_erase(multiset_t* pt_multiset, ...);
extern size_t _multiset_erase_varg(multiset_t* pt_multiset, va_list val_elemlist);

/*
 * Insert operation functions.
 */
extern multiset_iterator_t _multiset_insert(multiset_t* pt_multiset, ...);
extern multiset_iterator_t _multiset_insert_varg(
    multiset_t* pt_multiset, va_list val_elemlist);
extern multiset_iterator_t _multiset_insert_hint(
    multiset_t* pt_multiset, multiset_iterator_t t_hint, ...);
extern multiset_iterator_t _multiset_insert_hint_varg(
    multiset_t* pt_multiset, multiset_iterator_t t_hint, va_list val_elemlist);

extern void _multiset_init_elem_auxiliary(multiset_t* pt_multiset, void* pv_value);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_MULTISET_PRIVATE_H */
/** eof **/

