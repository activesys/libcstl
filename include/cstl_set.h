/*
 *  The interface of set.
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

#ifndef _CSTL_SET_H
#define _CSTL_SET_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/* create new set with specific type */
#define create_set(type)\
    _create_set(sizeof(type), #type) 
/* find */
#define set_find(cpt_set, elem)\
    _set_find((cpt_set), (elem))
/* count */
#define set_count(cpt_set, elem)\
    _set_count((cpt_set), (elem))
/* lower bound */
#define set_lower_bound(cpt_set, elem)\
    _set_lower_bound((cpt_set), (elem))
/* upper bound */
#define set_upper_bound(cpt_set, elem)\
    _set_upper_bound((cpt_set), (elem))
/* equal range */
#define set_equal_range(cpt_set, elem)\
    _set_equal_range((cpt_set), (elem))
/* erase */
#define set_erase(pt_set, elem)\
    _set_erase((pt_set), (elem))
/* insert */
#define set_insert(pt_set, elem)\
    _set_insert((pt_set), (elem))
#define set_insert_hint(pt_set, t_hint, elem)\
    _set_insert_hint((pt_set), (t_hint), (elem))

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * Initialization and destroy operation functions.
 */
extern void set_init(set_t* pt_set);
extern void set_destroy(set_t* pt_set);
extern void set_init_copy(set_t* pt_setdest, const set_t* cpt_setsrc);
/* private */
extern void set_init_copy_range_cmp(
    set_t* pt_setdest, set_iterator_t t_begin, set_iterator_t t_end,
    int (*pfun_cmp)(const void*, const void*));
extern void set_init_copy_range(
    set_t* pt_setdest, set_iterator_t t_begin, set_iterator_t t_end);

/*
 * Assign operator function.
 */
extern void set_assign(set_t* pt_setdest, const set_t* cpt_setsrc);

/*
 * set_t size operation functions.
 */
extern size_t set_size(const set_t* cpt_set);
extern bool_t set_empty(const set_t* cpt_set);
extern size_t set_max_size(const set_t* cpt_set);

/*
 * Iterator support.
 */
extern set_iterator_t set_begin(const set_t* cpt_set);
extern set_iterator_t set_end(const set_t* cpt_set);
/* private */
extern set_reverse_iterator_t set_rbegin(const set_t* cpt_set);
extern set_reverse_iterator_t set_rend(const set_t* cpt_set);

/*
 * Compare functions. (private)
 */
extern int (*set_key_comp(const set_t* cpt_set))(const void*, const void*);
extern int (*set_value_comp(const set_t* cpt_set))(const void*, const void*);

/*
 * Remove all elements.
 */
extern void set_clear(set_t* pt_set);

/*
 * Relationship operator functions.
 */
extern bool_t set_equal(const set_t* cpt_setfirst, const set_t* cpt_setsecond);
extern bool_t set_not_equal(const set_t* cpt_setfirst, const set_t* cpt_setsecond);
extern bool_t set_less(const set_t* cpt_setfirst, const set_t* cpt_setsecond);
extern bool_t set_great(const set_t* cpt_setfirst, const set_t* cpt_setsecond);
extern bool_t set_less_equal(const set_t* cpt_setfirst, const set_t* cpt_setsecond);
extern bool_t set_great_equal(const set_t* cpt_setfirst, const set_t* cpt_setsecond);

/*
 * Swap the datas of first set and second set.
 */
extern void set_swap(set_t* pt_setfirst, set_t* pt_setsecond);

/*
 * Insert element into set_t.
 */
extern void set_insert_range(set_t* pt_set, set_iterator_t t_begin, set_iterator_t t_end);

/*
 * Erase element from set_t.
 */
extern void set_erase_pos(set_t* pt_set, set_iterator_t t_pos);
extern void set_erase_range(set_t* pt_set, set_iterator_t t_begin, set_iterator_t t_end);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_SET_H */
/** eof **/

