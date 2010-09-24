/*
 *  The interface of multiset.
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

#ifndef _CSTL_MULTISET_H
#define _CSTL_MULTISET_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/* create new multiset with specific type */
#define create_multiset(...) _create_multiset(#__VA_ARGS__) 
/* find */
#define multiset_find(cpt_multiset, elem)\
    _multiset_find((cpt_multiset), (elem))
/* count */
#define multiset_count(cpt_multiset, elem)\
    _multiset_count((cpt_multiset), (elem))
/* lower bound */
#define multiset_lower_bound(cpt_multiset, elem)\
    _multiset_lower_bound((cpt_multiset), (elem))
/* upper bound */
#define multiset_upper_bound(cpt_multiset, elem)\
    _multiset_upper_bound((cpt_multiset), (elem))
/* equal range */
#define multiset_equal_range(cpt_multiset, elem)\
    _multiset_equal_range((cpt_multiset), (elem))
/* erase */
#define multiset_erase(pt_multiset, elem)\
    _multiset_erase((pt_multiset), (elem))
/* insert */
#define multiset_insert(pt_multiset, elem)\
    _multiset_insert((pt_multiset), (elem))
#define multiset_insert_hint(pt_multiset, t_hint, elem)\
    _multiset_insert_hint((pt_multiset), (t_hint), (elem))

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * Initialization and destroy functions.
 */
extern void multiset_init(multiset_t* pt_multiset);
extern void multiset_init_ex(multiset_t* pt_multiset, binary_function_t t_compare);
extern void multiset_destroy(multiset_t* pt_multiset);
extern void multiset_init_copy(multiset_t* pt_multisetdest, const multiset_t* cpt_multisetsrc);
extern void multiset_init_copy_range_ex(multiset_t* pt_multisetdest,
    multiset_iterator_t t_begin, multiset_iterator_t t_end, binary_function_t t_compare);
extern void multiset_init_copy_range(
    multiset_t* pt_multisetdest, multiset_iterator_t t_begin, multiset_iterator_t t_end);

/*
 * Assign the multiset_t from src to dest.
 */
extern void multiset_assign(
    multiset_t* pt_multisetdest, const multiset_t* cpt_multisetsrc);

/*
 * multiset_t size operation functions.
 */
extern size_t multiset_size(const multiset_t* cpt_multiset);
extern bool_t multiset_empty(const multiset_t* cpt_multiset);
extern size_t multiset_max_size(const multiset_t* cpt_multiset);

/*
 * Iterator support.
 */
extern multiset_iterator_t multiset_begin(const multiset_t* cpt_multiset);
extern multiset_iterator_t multiset_end(const multiset_t* cpt_multiset);
/* private */
extern multiset_reverse_iterator_t multiset_rbegin(const multiset_t* cpt_multiset);
extern multiset_reverse_iterator_t multiset_rend(const multiset_t* cpt_multiset);

/*
 * Return the compare function of key (private).
 */
extern binary_function_t multiset_key_comp(const multiset_t* cpt_multiset);
extern binary_function_t multiset_value_comp(const multiset_t* cpt_multiset);

/*
 * Remove all elements.
 */
extern void multiset_clear(multiset_t* pt_multiset);

/*
 * Relationship operator functions.
 */
extern bool_t multiset_equal(
    const multiset_t* cpt_multisetfirst, const multiset_t* cpt_multisetsecond);
extern bool_t multiset_not_equal(
    const multiset_t* cpt_multisetfirst, const multiset_t* cpt_multisetsecond);
extern bool_t multiset_less(
    const multiset_t* cpt_multisetfirst, const multiset_t* cpt_multisetsecond);
extern bool_t multiset_greater(
    const multiset_t* cpt_multisetfirst, const multiset_t* cpt_multisetsecond);
extern bool_t multiset_less_equal(
    const multiset_t* cpt_multisetfirst, const multiset_t* cpt_multisetsecond);
extern bool_t multiset_greater_equal(
    const multiset_t* cpt_multisetfirst, const multiset_t* cpt_multisetsecond);

/*
 * Swap the datas of first multiset and second multiset.
 */
extern void multiset_swap(
    multiset_t* pt_multisetfirst, multiset_t* pt_multisetsecond);

/*
 * Insert operation functions.
 */
extern void multiset_insert_range(
    multiset_t* pt_multiset, multiset_iterator_t t_begin, multiset_iterator_t t_end);

/*
 * Erase operation functions.
 */
extern void multiset_erase_pos(multiset_t* pt_multiset, multiset_iterator_t t_pos);
extern void multiset_erase_range(
    multiset_t* pt_multiset, multiset_iterator_t t_begin, multiset_iterator_t t_end);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_MULTISET_H */
/** eof **/

