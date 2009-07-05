/*
 *  The slist interface.
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

#ifndef _CSTL_SLIST_H
#define _CSTL_SLIST_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/* create new slist with specific type */
#define create_slist(...) _create_slist(#__VA_ARGS__)
/* initialize */
#define slist_init_elem(pt_slist, t_count, elem)\
    _slist_init_elem((pt_slist), (t_count), (elem))
/* assign */
#define slist_assign_elem(pt_slist, t_count, elem)\
    _slist_assign_elem((pt_slist), (t_count), (elem))
/* push front */
#define slist_push_front(pt_slist, elem)\
    _slist_push_front((pt_slist), (elem))
/* remove */
#define slist_remove(pt_slist, elem)\
    _slist_remove((pt_slist), (elem))
/* resize */
#define slist_resize_elem(pt_slist, t_resize, elem)\
    _slist_resize_elem((pt_slist), (t_resize), (elem))
/* insert and insert after */
#define slist_insert(pt_slist, t_pos, elem)\
    _slist_insert((pt_slist), (t_pos), (elem))
#define slist_insert_n(pt_slist, t_pos, t_count, elem)\
    _slist_insert_n((pt_slist), (t_pos), (t_count), (elem))
#define slist_insert_after(pt_slist, t_pos, elem)\
    _slist_insert_after((pt_slist), (t_pos), (elem))
#define slist_insert_after_n(pt_slist, t_pos, t_count, elem)\
    _slist_insert_after_n((pt_slist), (t_pos), (t_count), (elem))

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * Initialization and destroy operation functions.
 */
extern void slist_init(slist_t* pt_slist);
extern void slist_init_n(slist_t* pt_slist, size_t t_count);
extern void slist_init_copy(slist_t* pt_slistdest, const slist_t* cpt_slistsrc);
extern void slist_init_copy_range(
    slist_t* pt_slistdest, slist_iterator_t t_begin, slist_iterator_t t_end);
extern void slist_destroy(slist_t* pt_slist);

/*
 * Iterator support functions.
 */
extern slist_iterator_t slist_begin(const slist_t* cpt_slist);
extern slist_iterator_t slist_end(const slist_t* cpt_slist);
extern slist_iterator_t slist_previous(
    const slist_t* cpt_slist, slist_iterator_t t_pos);

/*
 * slist_t size functions.
 */
extern size_t slist_size(const slist_t* cpt_slist);
extern bool_t slist_empty(const slist_t* cpt_slist);
extern size_t slist_max_size(const slist_t* cpt_slist);

/*
 * Assign operator functions.
 */
extern void slist_assign(slist_t* pt_slistdest, const slist_t* cpt_slistsrc);
extern void slist_assign_range(
    slist_t* pt_slist, slist_iterator_t t_begin, slist_iterator_t t_end);

/*
 * Swap and element access operation functions.
 */
extern void slist_swap(slist_t* pt_slistfirst, slist_t* pt_slistsecond);
extern void* slist_front(const slist_t* cpt_slist);
extern void slist_pop_front(slist_t* pt_slist);

/*
 * Insert operation functions.
 */
extern void slist_insert_range(
    slist_t* pt_slist, slist_iterator_t t_pos, 
    slist_iterator_t t_begin, slist_iterator_t t_end);
extern void slist_insert_after_range(
    slist_t* pt_slist, slist_iterator_t t_pos, 
    slist_iterator_t t_begin, slist_iterator_t t_end);

/*
 * Erase operation functions.
 */
extern slist_iterator_t slist_erase(slist_t* pt_slist, slist_iterator_t t_pos);
extern slist_iterator_t slist_erase_range(
    slist_t* pt_slist, slist_iterator_t t_begin, slist_iterator_t t_end);
extern slist_iterator_t slist_erase_after(
    slist_t* pt_slist, slist_iterator_t t_pos);
extern slist_iterator_t slist_erase_after_range(
    slist_t* pt_slist, slist_iterator_t t_begin, slist_iterator_t t_end);

/*
 * Splice operation functions.
 */
extern void slist_splice(
    slist_t* pt_slist, slist_iterator_t t_pos, slist_t* pt_slistsrc);
extern void slist_splice_pos(
    slist_t* pt_slist, slist_iterator_t t_pos, 
    slist_t* pt_slistsrc, slist_iterator_t t_possrc);
extern void slist_splice_range(
    slist_t* pt_slist, slist_iterator_t t_pos, 
    slist_t* pt_slistsrc, slist_iterator_t t_begin, slist_iterator_t t_end);
extern void slist_splice_after_pos(
    slist_t* pt_slist, slist_iterator_t t_pos, 
    slist_t* pt_slistsrc, slist_iterator_t t_prev);
extern void slist_splice_after_range(
    slist_t* pt_slist, slist_iterator_t t_pos, 
    slist_t* pt_slistsrc, slist_iterator_t t_beforefirst, slist_iterator_t t_beforelast);

/*
 * Remove element form slist_t.
 */
extern void slist_remove_if(slist_t* pt_slist, unary_function_t t_unary_op);

/*
 * Unique and reverse operation functions.
 */
extern void slist_unique(slist_t* pt_slist);
extern void slist_unique_if(slist_t* pt_slist, binary_function_t t_binary_op);
extern void slist_reverse(slist_t* pt_slist);

/*
 * Sort and merge operation functions.
 */
extern void slist_sort(slist_t* pt_slist);
extern void slist_sort_if(slist_t* pt_slist, binary_function_t t_binary_op);
extern void slist_merge(slist_t* pt_slistdest, slist_t* pt_slistsrc);
extern void slist_merge_if(
    slist_t* pt_slistdest, slist_t* pt_slistsrc, binary_function_t t_binary_op);

/*
 * Reset slist_t size.
 */
extern void slist_resize(slist_t* pt_slist, size_t t_resize);

/*
 * Remove all elements.
 */
extern void slist_clear(slist_t* pt_slist);

/*
 * Relationship operation functions.
 */
extern bool_t slist_equal(
    const slist_t* cpt_slistfirst, const slist_t* cpt_slistsecond);
extern bool_t slist_not_equal(
    const slist_t* cpt_slistfirst, const slist_t* cpt_slistsecond);
extern bool_t slist_less(
    const slist_t* cpt_slistfirst, const slist_t* cpt_slistsecond);
extern bool_t slist_great(
    const slist_t* cpt_slistfirst, const slist_t* cpt_slistsecond);
extern bool_t slist_less_equal(
    const slist_t* cpt_slistfirst, const slist_t* cpt_slistsecond);
extern bool_t slist_great_equal(
    const slist_t* cpt_slistfirst, const slist_t* cpt_slistsecond);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_SLIST_H */
/** eof **/

