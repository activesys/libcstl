/*
 *  The interface of set.
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

#ifndef _CSTL_SET_H_
#define _CSTL_SET_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/**
 * Create set container.
 * @param ...        element type name.
 * @return if create set successfully return set pointer, otherwise return NULL.
 * @remarks element type name should be C builtin type name, libcstl builtin typename or registed user defined type name,
 *          otherwise the function will return NULL.
 */
#define create_set(...) _create_set(#__VA_ARGS__) 
/* find */
#define set_find(cpset_set, elem)\
    _set_find((cpset_set), (elem))
/* count */
#define set_count(cpset_set, elem)\
    _set_count((cpset_set), (elem))
/* lower bound */
#define set_lower_bound(cpset_set, elem)\
    _set_lower_bound((cpset_set), (elem))
/* upper bound */
#define set_upper_bound(cpset_set, elem)\
    _set_upper_bound((cpset_set), (elem))
/* equal range */
#define set_equal_range(cpset_set, elem)\
    _set_equal_range((cpset_set), (elem))
/* erase */
#define set_erase(pset_set, elem)\
    _set_erase((pset_set), (elem))
/* insert */
#define set_insert(pset_set, elem)\
    _set_insert((pset_set), (elem))
#define set_insert_hint(pset_set, it_hint, elem)\
    _set_insert_hint((pset_set), (it_hint), (elem))

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Initialize set container.
 * @param pset_set          set container.
 * @return void.
 * @remarks if pset_set == NULL, then the behavior is undefined, pset_set must be created by create_set(), otherwise
 *          the behavior is undefined. the default compare function is used.
 */
extern void set_init(set_t* pset_set);

/**
 * Initialize set container with user define compare function.
 * @param pset_set          set container.
 * @param t_compare         compare function.
 * @return void.
 * @remarks if pset_set == NULL, then the behavior is undefined, pset_set must be created by create_set(), otherwise
 *          the behavior is undefined. if t_compare == NULL, the default compare function is used.
 */
extern void set_init_ex(set_t* pset_set, binary_function_t t_compare);
extern void set_destroy(set_t* pset_set);
extern void set_init_copy(set_t* pset_dest, const set_t* cpset_src);
extern void set_init_copy_range(
    set_t* pset_dest, set_iterator_t it_begin, set_iterator_t it_end);
extern void set_init_copy_range_ex(
    set_t* pset_dest, set_iterator_t it_begin, set_iterator_t it_end, binary_function_t t_compare);

/*
 * Assign operator function.
 */
extern void set_assign(set_t* pset_dest, const set_t* cpset_src);

/*
 * set_t size operation functions.
 */
extern size_t set_size(const set_t* cpset_set);
extern bool_t set_empty(const set_t* cpset_set);
extern size_t set_max_size(const set_t* cpset_set);

/*
 * Iterator support.
 */
extern set_iterator_t set_begin(const set_t* cpset_set);
extern set_iterator_t set_end(const set_t* cpset_set);
/* private */
extern set_reverse_iterator_t set_rbegin(const set_t* cpset_set);
extern set_reverse_iterator_t set_rend(const set_t* cpset_set);

/*
 * Compare functions.
 */
extern binary_function_t set_key_comp(const set_t* cpset_set);
extern binary_function_t set_value_comp(const set_t* cpset_set);

/*
 * Remove all elements.
 */
extern void set_clear(set_t* pset_set);

/*
 * Relationship operator functions.
 */
extern bool_t set_equal(const set_t* cpset_first, const set_t* cpset_second);
extern bool_t set_not_equal(const set_t* cpset_first, const set_t* cpset_second);
extern bool_t set_less(const set_t* cpset_first, const set_t* cpset_second);
extern bool_t set_greater(const set_t* cpset_first, const set_t* cpset_second);
extern bool_t set_less_equal(const set_t* cpset_first, const set_t* cpset_second);
extern bool_t set_greater_equal(const set_t* cpset_first, const set_t* cpset_second);

/*
 * Swap the datas of first set and second set.
 */
extern void set_swap(set_t* pset_first, set_t* pset_second);

/*
 * Insert element into set_t.
 */
extern void set_insert_range(set_t* pset_set, set_iterator_t it_begin, set_iterator_t it_end);

/*
 * Erase element from set_t.
 */
extern void set_erase_pos(set_t* pset_set, set_iterator_t it_pos);
extern void set_erase_range(set_t* pset_set, set_iterator_t it_begin, set_iterator_t it_end);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_SET_H_ */
/** eof **/

