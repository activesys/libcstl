/*
 *  The interface of multimap.
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

#ifndef _CSTL_MULTIMAP_H
#define _CSTL_MULTIMAP_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
#define create_multimap(key_type, value_type)\
    _create_multimap(\
        sizeof(key_type), #key_type, \
        sizeof(value_type), #value_type)
/* find */
#define multimap_find(cpt_multimap, key_elem)\
    _multimap_find((cpt_multimap), (key_elem))
/* count */
#define multimap_count(cpt_multimap, key_elem)\
    _multimap_count((cpt_multimap), (key_elem))
/* lower bound */
#define multimap_lower_bound(cpt_multimap, key_elem)\
    _multimap_lower_bound((cpt_multimap), (key_elem))
/* upper bound */
#define multimap_upper_bound(cpt_multimap, key_elem)\
    _multimap_upper_bound((cpt_multimap), (key_elem))
/* equal range */
#define multimap_equal_range(cpt_multimap, key_elem)\
    _multimap_equal_range((cpt_multimap), (key_elem))
/* erase */
#define multimap_erase(pt_multimap, key_elem)\
    _multimap_erase((pt_multimap), (key_elem))

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * Initialization and destroy functions.
 */
extern void multimap_init(multimap_t* pt_multimap);
extern void multimap_destroy(multimap_t* pt_multimap);
extern void multimap_init_copy(
    multimap_t* pt_multimapdest, const multimap_t* cpt_multimapsrc);
extern void multimap_init_copy_range_cmp(
    multimap_t* pt_multimapdest, multimap_iterator_t t_begin, multimap_iterator_t t_end,
    int (*pfun_key_cmp)(const void*, const void*));
extern void multimap_init_copy_range(
    multimap_t* pt_multimapdest, multimap_iterator_t t_begin, multimap_iterator_t t_end);

/*
 * Assign the multimap_t from src to dest.
 */
extern void multimap_assign(
    multimap_t* pt_multimapdest, const multimap_t* cpt_multimapsrc);

/*
 * Swap the datas of first multimap and second multimap.
 */
extern void multimap_swap(
    multimap_t* pt_multimapfirst, multimap_t* pt_multimapsecond);

/*
 * multimap_t size operation functions.
 */
extern size_t multimap_size(const multimap_t* cpt_multimap);
extern bool_t multimap_empty(const multimap_t* cpt_multimap);
extern size_t multimap_max_size(const multimap_t* cpt_multimap);

/*
 * Return the compare function of key.
 */
extern int (*multimap_key_comp(const multimap_t* cpt_multimap))(const void*, const void*);
extern int (*multimap_value_comp(const multimap_t* cpt_multimap))(const void*, const void*);

/*
 * Remove all elements.
 */
extern void multimap_clear(multimap_t* pt_multimap);

/*
 * Relationship operator functions.
 */
extern bool_t multimap_equal(
    const multimap_t* cpt_multimapfirst, const multimap_t* cpt_multimapsecond);
extern bool_t multimap_not_equal(
    const multimap_t* cpt_multimapfirst, const multimap_t* cpt_multimapsecond);
extern bool_t multimap_less(
    const multimap_t* cpt_multimapfirst, const multimap_t* cpt_multimapsecond);
extern bool_t multimap_great(
    const multimap_t* cpt_multimapfirst, const multimap_t* cpt_multimapsecond);
extern bool_t multimap_less_equal(
    const multimap_t* cpt_multimapfirst, const multimap_t* cpt_multimapsecond);
extern bool_t multimap_great_equal(
    const multimap_t* cpt_multimapfirst, const multimap_t* cpt_multimapsecond);

/*
 * Iterator support.
 */
extern multimap_iterator_t multimap_begin(const multimap_t* cpt_multimap);
extern multimap_iterator_t multimap_end(const multimap_t* cpt_multimap);
/* private */
extern multimap_reverse_iterator_t multimap_rbegin(const multimap_t* cpt_multimap);
extern multimap_reverse_iterator_t multimap_rend(const multimap_t* cpt_multimap);

/*
 * Insert operation functions.
 */
extern multimap_iterator_t multimap_insert(multimap_t* pt_multimap, const pair_t* cpt_pair);
extern multimap_iterator_t multimap_insert_hint(
    multimap_t* pt_multimap, multimap_iterator_t t_hint, const pair_t* cpt_pair);
extern void multimap_insert_range(
    multimap_t* pt_multimap, multimap_iterator_t t_begin, multimap_iterator_t t_end);

/*
 * Erase operation functions.
 */
extern void multimap_erase_pos(multimap_t* pt_multimap, multimap_iterator_t t_pos);
extern void multimap_erase_range(
    multimap_t* pt_multimap, multimap_iterator_t t_begin, multimap_iterator_t t_end);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_MULTIMAP_H */
/** eof **/

