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
 * ----------------------------------------------------------------------------
 *
 *      Functionname: set_init
 *        Parameters: in) pt_set: set_t*
 *           Returns: void
 *       Description: initialize the set.
 *
 * ----------------------------------------------------------------------------
 */
extern void set_init(set_t* pt_set);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: set_destroy
 *        Parameters: in) pt_set: set_t*
 *           Returns: void
 *       Description: destroy the set.
 *
 * ----------------------------------------------------------------------------
 */
extern void set_destroy(set_t* pt_set);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: set_init_copy
 *        Parameters: in) pt_setdest: set_t*
 *                        the dest set pointer.
 *                    in) cpt_setsrc: const set_t*
 *                        the src set pointer.
 *           Returns: void
 *       Description: the copy constructor.
 *
 * ----------------------------------------------------------------------------
 */
extern void set_init_copy(set_t* pt_setdest, const set_t* cpt_setsrc);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: set_init_copy_range_cmp
 *        Parameters: in) pt_set_dest: set_t*
 *                        the dest rb tree pointer.
 *                    in) t_begin: set_iterator_t
 *                        the begin iterator
 *                    in0 t_end: set_iterator_t
 *                        the end iterator.
 *                    in) pfun_cmp: int (*pfun)(const void*, const void*)
 *                          the function for element compare:
 *                          < 0  : element first < element second.
 *                          == 0 : element first == element second.
 *                          > 0  : element first > element second. 
 *           Returns: void
 *       Description: the copy constructor with range and key compare function.
 *
 * ----------------------------------------------------------------------------
 */
extern void set_init_copy_range_cmp(
    set_t* pt_setdest, 
    set_iterator_t t_begin, 
    set_iterator_t t_end,
    int (*pfun_cmp)(const void*, const void*));

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: set_init_copy_range
 *        Parameters: in) pt_set_dest: set_t*
 *                        the dest rb tree pointer.
 *                    in) t_begin: set_iterator_t
 *                        the begin iterator
 *                    in0 t_end: set_iterator_t
 *                        the end iterator.
 *           Returns: void
 *       Description: the copy constructor with range.
 *
 * ----------------------------------------------------------------------------
 */
extern void set_init_copy_range(
    set_t* pt_setdest, 
    set_iterator_t t_begin, 
    set_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: set_assign
 *        Parameters: in) pt_setdest: set_t*
 *                        the dest set pointer.
 *                    in) cpt_setsrc: const set_t*
 *                        the src set pointer.
 *           Returns: void
 *       Description: assign the set_t from src to dest.
 *
 * ----------------------------------------------------------------------------
 */
extern void set_assign(set_t* pt_setdest, const set_t* cpt_setsrc);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: set_size
 *        Parameters: in) cpt_set: const set_t*
 *                          the dest set.
 *           Returns: size_t
 *       Description: get the set size.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t set_size(const set_t* cpt_set);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: set_empty
 *        Parameters: in) cpt_set: const set_t*
 *                          the dest set.
 *           Returns: bool_t
 *       Description: if the set is empty.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t set_empty(const set_t* cpt_set);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: set_max_size
 *        Parameters: in) cpt_set: const set_t*
 *                          the dest set.
 *           Returns: size_t
 *       Description: get the maximum capacity of set.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t set_max_size(const set_t* cpt_set);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: set_begin
 *        Parameters: in) cpt_set: const set_t*
 *                          the set.
 *           Returns: set_iterator_t
 *       Description: return the random access iterator for the first element.
 *
 * ----------------------------------------------------------------------------
 */
extern set_iterator_t set_begin(const set_t* cpt_set);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: set_end
 *        Parameters: in) cpt_set: const set_t*
 *                          the set.
 *           Returns: set_iterator_t
 *       Description: return the random access iterator for the last element.
 *
 * ----------------------------------------------------------------------------
 */
extern set_iterator_t set_end(const set_t* cpt_set);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: set_rbegin
 *        Parameters: in) cpt_set: const set_t*
 *                          the set.
 *           Returns: set_reverse_iterator_t
 *       Description: return the reverse iterator for the first element of the
 *                    reverse iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern set_reverse_iterator_t set_rbegin(const set_t* cpt_set);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: set_rend
 *        Parameters: in) cpt_set: const set_t*
 *                          the set.
 *           Returns: set_reverse_iterator_t
 *       Description: return the reverse iterator for the last element of the
 *                    reverse iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern set_reverse_iterator_t set_rend(const set_t* cpt_set);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: set_key_comp
 *        Parameters: in) cpt_set: const set_t*
 *                        the set pointer.
 *           Returns: int (*)(const void*, const void*)
 *       Description: return the compare function of key.
 *
 * ----------------------------------------------------------------------------
 */
extern int (*set_key_comp(const set_t* cpt_set))(const void*, const void*);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: set_value_comp
 *        Parameters: in) cpt_set: const set_t*
 *                        the set pointer.
 *           Returns: int (*)(const void*, const void*)
 *       Description: return the compare function of value.
 *
 * ----------------------------------------------------------------------------
 */
extern int (*set_value_comp(const set_t* cpt_set))(const void*, const void*);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: set_clear
 *        Parameters: in) pt_set: set_t*
 *                          the set.
 *           Returns: void
 *       Description: remove all elements.
 *
 * ----------------------------------------------------------------------------
 */
extern void set_clear(set_t* pt_set);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: set_equal
 *        Parameters: in) cpt_setfirst: const set_t*
 *                          the first set.
 *                    in) cpt_setsecond: const set_t*
 *                          the second set.
 *           Returns: bool_t
 *       Description: return whether first set equal to second set.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t set_equal(const set_t* cpt_setfirst, const set_t* cpt_setsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: set_not_equal
 *        Parameters: in) cpt_setfirst: const set_t*
 *                          the first set.
 *                    in) cpt_setsecond: const set_t*
 *                          the second set.
 *           Returns: bool_t
 *       Description: return whether first set not equal to second set.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t set_not_equal(
    const set_t* cpt_setfirst, const set_t* cpt_setsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: set_less
 *        Parameters: in) cpt_setfirst: const set_t*
 *                          the first set.
 *                    in) cpt_setsecond: const set_t*
 *                          the second set.
 *           Returns: bool_t
 *       Description: return whether first set less then second set.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t set_less(const set_t* cpt_setfirst, const set_t* cpt_setsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: set_great
 *        Parameters: in) cpt_setfirst: const set_t*
 *                          the first set.
 *                    in) cpt_setsecond: const set_t*
 *                          the second set.
 *           Returns: bool_t
 *       Description: return whether first set greater then second set.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t set_great(const set_t* cpt_setfirst, const set_t* cpt_setsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: set_less_equal
 *        Parameters: in) cpt_setfirst: const set_t*
 *                          the first set.
 *                    in) cpt_setsecond: const set_t*
 *                          the second set.
 *           Returns: bool_t
 *       Description: return whether first set less then or equal to the 
 *                    second set.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t set_less_equal(
    const set_t* cpt_setfirst, const set_t* cpt_setsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: set_great_equal
 *        Parameters: in) cpt_setfirst: const set_t*
 *                          the first set.
 *                    in) cpt_setsecond: const set_t*
 *                          the second set.
 *           Returns: bool_t
 *       Description: return whether first set greater then or equal to the
 *                    second set.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t set_great_equal(
    const set_t* cpt_setfirst, const set_t* cpt_setsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: set_swap
 *        Parameters: in) pt_setfirst: set_t*
 *                          the first set.
 *                    in) pt_setsecond: set_t*
 *                          the second set.
 *           Returns: void
 *       Description: swap the datas of first set and second set.
 *
 * ----------------------------------------------------------------------------
 */
extern void set_swap(set_t* pt_setfirst, set_t* pt_setsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: set_insert_range
 *        Parameters: in) pt_set: set_t*
 *                        the rb tree pointer.
 *                    in) t_begin: set_iterator_t
 *                        the begin iterator
 *                    in0 t_end: set_iterator_t
 *                        the end iterator.
 *           Returns: void
 *       Description: insert a range into the set.
 *
 * ----------------------------------------------------------------------------
 */
extern void set_insert_range(
    set_t* pt_set, set_iterator_t t_begin, set_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: set_erase_pos
 *        Parameters: in) pt_set: set_t*
 *                        the rb tree pointer.
 *                    in) t_pos: set_iterator_t
 *                        the erase iterator.
 *           Returns: void
 *       Description: erase the element pointed by t_pos.
 *
 * ----------------------------------------------------------------------------
 */
extern void set_erase_pos(set_t* pt_set, set_iterator_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: set_erase_range
 *        Parameters: in) pt_set: set_t*
 *                        the rb tree pointer.
 *                    in) t_begin: set_iterator_t
 *                        the begin iterator.
 *                    in) t_end: set_iterator_t
 *                        the end iterator.
 *           Returns: void
 *       Description: erase the all elements in the range.
 *
 * ----------------------------------------------------------------------------
 */
extern void set_erase_range(
    set_t* pt_set, set_iterator_t t_begin, set_iterator_t t_end);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_SET_H */
/** eof **/

