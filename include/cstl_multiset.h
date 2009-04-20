/*
 *  The interface of multiset.
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
 *  Author Email: activesys.wb@gmail.com
 *                activesys@sina.com.cn
 */

#ifndef _CSTL_MULTISET_H
#define _CSTL_MULTISET_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/* create new multiset with specific type */
#define create_multiset(type)\
    _create_multiset(sizeof(type), #type) 
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
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multiset_init
 *        Parameters: in) pt_multiset: multiset_t*
 *           Returns: void
 *       Description: initialize the multiset.
 *
 * ----------------------------------------------------------------------------
 */
extern void multiset_init(multiset_t* pt_multiset);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multiset_destroy
 *        Parameters: in) pt_multiset: multiset_t*
 *           Returns: void
 *       Description: destroy the multiset.
 *
 * ----------------------------------------------------------------------------
 */
extern void multiset_destroy(multiset_t* pt_multiset);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multiset_init_copy
 *        Parameters: in) pt_multisetdest: multiset_t*
 *                        the dest multiset pointer.
 *                    in) cpt_multisetsrc: const multiset_t*
 *                        the src multiset pointer.
 *           Returns: void
 *       Description: the copy constructor.
 *
 * ----------------------------------------------------------------------------
 */
extern void multiset_init_copy(
    multiset_t* pt_multisetdest, const multiset_t* cpt_multisetsrc);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multiset_init_copy_range_cmp
 *        Parameters: in) pt_multisetdest: multiset_t*
 *                        the dest rb tree pointer.
 *                    in) t_begin: multiset_iterator_t
 *                        the begin iterator
 *                    in0 t_end: multiset_iterator_t
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
extern void multiset_init_copy_range_cmp(
    multiset_t* pt_multisetdest, 
    multiset_iterator_t t_begin, 
    multiset_iterator_t t_end,
    int (*pfun_cmp)(const void*, const void*));

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multiset_init_copy_range
 *        Parameters: in) pt_multisetdest: multiset_t*
 *                        the dest rb tree pointer.
 *                    in) t_begin: multiset_iterator_t
 *                        the begin iterator
 *                    in0 t_end: multiset_iterator_t
 *                        the end iterator.
 *           Returns: void
 *       Description: the copy constructor with range.
 *
 * ----------------------------------------------------------------------------
 */
extern void multiset_init_copy_range(
    multiset_t* pt_multisetdest, 
    multiset_iterator_t t_begin, 
    multiset_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multiset_assign
 *        Parameters: in) pt_multisetdest: multiset_t*
 *                        the dest multiset pointer.
 *                    in) cpt_multisetsrc: const multiset_t*
 *                        the src multiset pointer.
 *           Returns: void
 *       Description: assign the multiset_t from src to dest.
 *
 * ----------------------------------------------------------------------------
 */
extern void multiset_assign(
    multiset_t* pt_multisetdest, const multiset_t* cpt_multisetsrc);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multiset_size
 *        Parameters: in) cpt_multiset: const multiset_t*
 *                          the dest multiset.
 *           Returns: size_t
 *       Description: get the multiset size.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t multiset_size(const multiset_t* cpt_multiset);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multiset_empty
 *        Parameters: in) cpt_multiset: const multiset_t*
 *                          the dest multiset.
 *           Returns: bool_t
 *       Description: if the multiset is empty.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t multiset_empty(const multiset_t* cpt_multiset);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multiset_max_size
 *        Parameters: in) cpt_multiset: const multiset_t*
 *                          the dest multiset.
 *           Returns: size_t
 *       Description: get the maximum capacity of multiset.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t multiset_max_size(const multiset_t* cpt_multiset);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multiset_begin
 *        Parameters: in) cpt_multiset: const multiset_t*
 *                          the multiset.
 *           Returns: multiset_iterator_t
 *       Description: return the random access iterator for the first element.
 *
 * ----------------------------------------------------------------------------
 */
extern multiset_iterator_t multiset_begin(const multiset_t* cpt_multiset);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multiset_end
 *        Parameters: in) cpt_multiset: const multiset_t*
 *                          the multiset.
 *           Returns: multiset_iterator_t
 *       Description: return the random access iterator for the last element.
 *
 * ----------------------------------------------------------------------------
 */
extern multiset_iterator_t multiset_end(const multiset_t* cpt_multiset);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multiset_rbegin
 *        Parameters: in) cpt_multiset: const multiset_t*
 *                          the multiset.
 *           Returns: multiset_reverse_iterator_t
 *       Description: return the reverse iterator for the first element of the
 *                    reverse iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern multiset_reverse_iterator_t multiset_rbegin(
    const multiset_t* cpt_multiset);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multiset_rend
 *        Parameters: in) cpt_multiset: const multiset_t*
 *                          the multiset.
 *           Returns: multiset_reverse_iterator_t
 *       Description: return the reverse iterator for the last element of the
 *                    reverse iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern multiset_reverse_iterator_t multiset_rend(
    const multiset_t* cpt_multiset);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multiset_key_comp
 *        Parameters: in) cpt_multiset: const multiset_t*
 *                        the multiset pointer.
 *           Returns: int (*)(const void*, const void*)
 *       Description: return the compare function of key.
 *
 * ----------------------------------------------------------------------------
 */
extern int (*multiset_key_comp(const multiset_t* cpt_multiset))(
    const void*, const void*);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multiset_value_comp
 *        Parameters: in) cpt_multiset: const multiset_t*
 *                        the multiset pointer.
 *           Returns: int (*)(const void*, const void*)
 *       Description: return the compare function of value.
 *
 * ----------------------------------------------------------------------------
 */
extern int (*multiset_value_comp(const multiset_t* cpt_multiset))(
    const void*, const void*);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multiset_clear
 *        Parameters: in) pt_multiset: multiset_t*
 *                          the multiset.
 *           Returns: void
 *       Description: remove all elements.
 *
 * ----------------------------------------------------------------------------
 */
extern void multiset_clear(multiset_t* pt_multiset);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multiset_equal
 *        Parameters: in) cpt_multisetfirst: const multiset_t*
 *                          the first multiset.
 *                    in) cpt_multisetsecond: const multiset_t*
 *                          the second multiset.
 *           Returns: bool_t
 *       Description: return whether first multiset equal to second multiset.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t multiset_equal(
    const multiset_t* cpt_multisetfirst, const multiset_t* cpt_multisetsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multiset_not_equal
 *        Parameters: in) cpt_multisetfirst: const multiset_t*
 *                          the first multiset.
 *                    in) cpt_multisetsecond: const multiset_t*
 *                          the second multiset.
 *           Returns: bool_t
 *       Description: return whether first multiset not equal to second multiset.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t multiset_not_equal(
    const multiset_t* cpt_multisetfirst, const multiset_t* cpt_multisetsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multiset_less
 *        Parameters: in) cpt_multisetfirst: const multiset_t*
 *                          the first multiset.
 *                    in) cpt_multisetsecond: const multiset_t*
 *                          the second multiset.
 *           Returns: bool_t
 *       Description: return whether first multiset less then second multiset.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t multiset_less(
    const multiset_t* cpt_multisetfirst, const multiset_t* cpt_multisetsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multiset_great
 *        Parameters: in) cpt_multisetfirst: const multiset_t*
 *                          the first multiset.
 *                    in) cpt_multisetsecond: const multiset_t*
 *                          the second multiset.
 *           Returns: bool_t
 *       Description: return whether first multiset greater then second multiset.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t multiset_great(
    const multiset_t* cpt_multisetfirst, const multiset_t* cpt_multisetsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multiset_less_equal
 *        Parameters: in) cpt_multisetfirst: const multiset_t*
 *                          the first multiset.
 *                    in) cpt_multisetsecond: const multiset_t*
 *                          the second multiset.
 *           Returns: bool_t
 *       Description: return whether first multiset less then or equal to the 
 *                    second multiset.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t multiset_less_equal(
    const multiset_t* cpt_multisetfirst, const multiset_t* cpt_multisetsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multiset_great_equal
 *        Parameters: in) cpt_multisetfirst: const multiset_t*
 *                          the first multiset.
 *                    in) cpt_multisetsecond: const multiset_t*
 *                          the second multiset.
 *           Returns: bool_t
 *       Description: return whether first multiset greater then or equal to the
 *                    second multiset.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t multiset_great_equal(
    const multiset_t* cpt_multisetfirst, const multiset_t* cpt_multisetsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multiset_swap
 *        Parameters: in) pt_multisetfirst: multiset_t*
 *                          the first multiset.
 *                    in) pt_multisetsecond: multiset_t*
 *                          the second multiset.
 *           Returns: void
 *       Description: swap the datas of first multiset and second multiset.
 *
 * ----------------------------------------------------------------------------
 */
extern void multiset_swap(
    multiset_t* pt_multisetfirst, multiset_t* pt_multisetsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multiset_insert_range
 *        Parameters: in) pt_multiset: multiset_t*
 *                        the rb tree pointer.
 *                    in) t_begin: multiset_iterator_t
 *                        the begin iterator
 *                    in0 t_end: multiset_iterator_t
 *                        the end iterator.
 *           Returns: void
 *       Description: insert a range into the multiset.
 *
 * ----------------------------------------------------------------------------
 */
extern void multiset_insert_range(
    multiset_t* pt_multiset, 
    multiset_iterator_t t_begin, 
    multiset_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multiset_erase_pos
 *        Parameters: in) pt_multiset: multiset_t*
 *                        the rb tree pointer.
 *                    in) t_pos: multiset_iterator_t
 *                        the erase iterator.
 *           Returns: void
 *       Description: erase the element pointed by t_pos.
 *
 * ----------------------------------------------------------------------------
 */
extern void multiset_erase_pos(
    multiset_t* pt_multiset, multiset_iterator_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multiset_erase_range
 *        Parameters: in) pt_multiset: multiset_t*
 *                        the rb tree pointer.
 *                    in) t_begin: multiset_iterator_t
 *                        the begin iterator.
 *                    in) t_end: multiset_iterator_t
 *                        the end iterator.
 *           Returns: void
 *       Description: erase the all elements in the range.
 *
 * ----------------------------------------------------------------------------
 */
extern void multiset_erase_range(
    multiset_t* pt_multiset, 
    multiset_iterator_t t_begin, 
    multiset_iterator_t t_end);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_MULTISET_H */
/** eof **/

