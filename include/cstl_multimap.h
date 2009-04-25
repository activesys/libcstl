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
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multimap_init
 *        Parameters: in) pt_multimap: multimap_t*
 *           Returns: void
 *       Description: initialize the multimap.
 *
 * ----------------------------------------------------------------------------
 */
extern void multimap_init(multimap_t* pt_multimap);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multimap_destroy
 *        Parameters: in) pt_multimap: multimap_t*
 *           Returns: void
 *       Description: destroy the multimap.
 *
 * ----------------------------------------------------------------------------
 */
extern void multimap_destroy(multimap_t* pt_multimap);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multimap_init_copy
 *        Parameters: in) pt_multimapdest: multimap_t*
 *                        the dest multimap pointer.
 *                    in) cpt_multimapsrc: const multimap_t*
 *                        the src multimap pointer.
 *           Returns: void
 *       Description: the copy constructor.
 *
 * ----------------------------------------------------------------------------
 */
extern void multimap_init_copy(
    multimap_t* pt_multimapdest, const multimap_t* cpt_multimapsrc);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multimap_init_copy_range_cmp
 *        Parameters: in) pt_multimapdest: multimap_t*
 *                        the dest rb tree pointer.
 *                    in) t_begin: multimap_iterator_t
 *                        the begin iterator
 *                    in0 t_end: multimap_iterator_t
 *                        the end iterator.
 *                    in) pfun_key_cmp: int (*pfun)(const void*, const void*)
 *                          the function for element compare:
 *                          < 0  : element first < element second.
 *                          == 0 : element first == element second.
 *                          > 0  : element first > element second. 
 *           Returns: void
 *       Description: the copy constructor with range and key compare function.
 *
 * ----------------------------------------------------------------------------
 */
extern void multimap_init_copy_range_cmp(
    multimap_t* pt_multimapdest, 
    multimap_iterator_t t_begin, 
    multimap_iterator_t t_end,
    int (*pfun_key_cmp)(const void*, const void*));

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multimap_init_copy_range
 *        Parameters: in) pt_multimapdest: multimap_t*
 *                        the dest rb tree pointer.
 *                    in) t_begin: multimap_iterator_t
 *                        the begin iterator
 *                    in0 t_end: multimap_iterator_t
 *                        the end iterator.
 *           Returns: void
 *       Description: the copy constructor with range.
 *
 * ----------------------------------------------------------------------------
 */
extern void multimap_init_copy_range(
    multimap_t* pt_multimapdest, 
    multimap_iterator_t t_begin, 
    multimap_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multimap_assign
 *        Parameters: in) pt_multimapdest: multimap_t*
 *                        the dest multimap pointer.
 *                    in) cpt_multimapsrc: const multimap_t*
 *                        the src multimap pointer.
 *           Returns: void
 *       Description: assign the multimap_t from src to dest.
 *
 * ----------------------------------------------------------------------------
 */
extern void multimap_assign(
    multimap_t* pt_multimapdest, const multimap_t* cpt_multimapsrc);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multimap_swap
 *        Parameters: in) pt_multimapfirst: multimap_t*
 *                          the first multimap.
 *                    in) pt_multimapsecond: multimap_t*
 *                          the second multimap.
 *           Returns: void
 *       Description: swap the datas of first multimap and second multimap.
 *
 * ----------------------------------------------------------------------------
 */
extern void multimap_swap(
    multimap_t* pt_multimapfirst, multimap_t* pt_multimapsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multimap_size
 *        Parameters: in) cpt_multimap: const multimap_t*
 *                          the dest multimap.
 *           Returns: size_t
 *       Description: get the multimap size.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t multimap_size(const multimap_t* cpt_multimap);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multimap_empty
 *        Parameters: in) cpt_multimap: const multimap_t*
 *                          the dest multimap.
 *           Returns: bool_t
 *       Description: if the multimap is empty.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t multimap_empty(const multimap_t* cpt_multimap);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multimap_max_size
 *        Parameters: in) cpt_multimap: const multimap_t*
 *                          the dest multimap.
 *           Returns: size_t
 *       Description: get the maximum capacity of multimap.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t multimap_max_size(const multimap_t* cpt_multimap);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multimap_key_comp
 *        Parameters: in) cpt_multimap: const multimap_t*
 *                        the multimap pointer.
 *           Returns: int (*)(const void*, const void*)
 *       Description: return the compare function of key.
 *
 * ----------------------------------------------------------------------------
 */
extern int (*multimap_key_comp(const multimap_t* cpt_multimap))(
    const void*, const void*);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multimap_value_comp
 *        Parameters: in) cpt_multimap: const multimap_t*
 *                        the multimap pointer.
 *           Returns: int (*)(const void*, const void*)
 *       Description: return the compare function of value.
 *
 * ----------------------------------------------------------------------------
 */
extern int (*multimap_value_comp(const multimap_t* cpt_multimap))(
    const void*, const void*);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multimap_clear
 *        Parameters: in) pt_multimap: multimap_t*
 *                          the multimap.
 *           Returns: void
 *       Description: remove all elements.
 *
 * ----------------------------------------------------------------------------
 */
extern void multimap_clear(multimap_t* pt_multimap);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multimap_equal
 *        Parameters: in) cpt_multimapfirst: const multimap_t*
 *                          the first multimap.
 *                    in) cpt_multimapsecond: const multimap_t*
 *                          the second multimap.
 *           Returns: bool_t
 *       Description: return whether first multimap equal to second multimap.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t multimap_equal(
    const multimap_t* cpt_multimapfirst, const multimap_t* cpt_multimapsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multimap_not_equal
 *        Parameters: in) cpt_multimapfirst: const multimap_t*
 *                          the first multimap.
 *                    in) cpt_multimapsecond: const multimap_t*
 *                          the second multimap.
 *           Returns: bool_t
 *       Description: return whether first multimap not equal to second multimap.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t multimap_not_equal(
    const multimap_t* cpt_multimapfirst, const multimap_t* cpt_multimapsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multimap_less
 *        Parameters: in) cpt_multimapfirst: const multimap_t*
 *                          the first multimap.
 *                    in) cpt_multimapsecond: const multimap_t*
 *                          the second multimap.
 *           Returns: bool_t
 *       Description: return whether first multimap less then second multimap.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t multimap_less(
    const multimap_t* cpt_multimapfirst, const multimap_t* cpt_multimapsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multimap_great
 *        Parameters: in) cpt_multimapfirst: const multimap_t*
 *                          the first multimap.
 *                    in) cpt_multimapsecond: const multimap_t*
 *                          the second multimap.
 *           Returns: bool_t
 *       Description: return whether first multimap greater then second multimap.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t multimap_great(
    const multimap_t* cpt_multimapfirst, const multimap_t* cpt_multimapsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multimap_less_equal
 *        Parameters: in) cpt_multimapfirst: const multimap_t*
 *                          the first multimap.
 *                    in) cpt_multimapsecond: const multimap_t*
 *                          the second multimap.
 *           Returns: bool_t
 *       Description: return whether first multimap less then or equal to the 
 *                    second multimap.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t multimap_less_equal(
    const multimap_t* cpt_multimapfirst, const multimap_t* cpt_multimapsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multimap_great_equal
 *        Parameters: in) cpt_multimapfirst: const multimap_t*
 *                          the first multimap.
 *                    in) cpt_multimapsecond: const multimap_t*
 *                          the second multimap.
 *           Returns: bool_t
 *       Description: return whether first multimap greater then or equal to the
 *                    second multimap.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t multimap_great_equal(
    const multimap_t* cpt_multimapfirst, const multimap_t* cpt_multimapsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multimap_begin
 *        Parameters: in) cpt_multimap: const multimap_t*
 *                          the multimap.
 *           Returns: multimap_iterator_t
 *       Description: return the random access iterator for the first element.
 *
 * ----------------------------------------------------------------------------
 */
extern multimap_iterator_t multimap_begin(const multimap_t* cpt_multimap);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multimap_end
 *        Parameters: in) cpt_multimap: const multimap_t*
 *                          the multimap.
 *           Returns: multimap_iterator_t
 *       Description: return the random access iterator for the last element.
 *
 * ----------------------------------------------------------------------------
 */
extern multimap_iterator_t multimap_end(const multimap_t* cpt_multimap);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multimap_rbegin
 *        Parameters: in) cpt_multimap: const multimap_t*
 *                          the multimap.
 *           Returns: multimap_reverse_iterator_t
 *       Description: return the reverse iterator for the first element of the
 *                    reverse iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern multimap_reverse_iterator_t multimap_rbegin(
    const multimap_t* cpt_multimap);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multimap_rend
 *        Parameters: in) cpt_multimap: const multimap_t*
 *                          the multimap.
 *           Returns: multimap_reverse_iterator_t
 *       Description: return the reverse iterator for the last element of the
 *                    reverse iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern multimap_reverse_iterator_t multimap_rend(
    const multimap_t* cpt_multimap);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multimap_insert
 *        Parameters: in) pt_multimap: multimap_t*
 *                        the multimap pointer.
 *                    in) cpt_pair: const pair_t*
 *                        the element pair.
 *           Returns: multimap_iterator_t
 *                        the insert result.
 *       Description: insert value into multimap.
 *
 * ----------------------------------------------------------------------------
 */
extern multimap_iterator_t multimap_insert(
    multimap_t* pt_multimap, const pair_t* cpt_pair);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multimap_insert_hint
 *        Parameters: in) pt_multimap: multimap_t*
 *                        the multimap pointer.
 *                    in) t_hint: multimap_iterator_t
 *                        the hint iterator.
 *                    in) ...
 *                        the target value.
 *           Returns: multimap_iterator_t
 *                        the iterator of new element.
 *       Description: insert value into multimap.
 *
 * ----------------------------------------------------------------------------
 */
extern multimap_iterator_t multimap_insert_hint(
    multimap_t* pt_multimap, multimap_iterator_t t_hint, const pair_t* cpt_pair);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multimap_insert_range
 *        Parameters: in) pt_multimap: multimap_t*
 *                        the rb tree pointer.
 *                    in) t_begin: multimap_iterator_t
 *                        the begin iterator
 *                    in0 t_end: multimap_iterator_t
 *                        the end iterator.
 *           Returns: void
 *       Description: insert a range into the multimap.
 *
 * ----------------------------------------------------------------------------
 */
extern void multimap_insert_range(
    multimap_t* pt_multimap, multimap_iterator_t t_begin, multimap_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multimap_erase_pos
 *        Parameters: in) pt_multimap: multimap_t*
 *                        the rb tree pointer.
 *                    in) t_pos: multimap_iterator_t
 *                        the erase iterator.
 *           Returns: void
 *       Description: erase the element pointed by t_pos.
 *
 * ----------------------------------------------------------------------------
 */
extern void multimap_erase_pos(
    multimap_t* pt_multimap, multimap_iterator_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: multimap_erase_range
 *        Parameters: in) pt_multimap: multimap_t*
 *                        the rb tree pointer.
 *                    in) t_begin: multimap_iterator_t
 *                        the begin iterator.
 *                    in) t_end: multimap_iterator_t
 *                        the end iterator.
 *           Returns: void
 *       Description: erase the all elements in the range.
 *
 * ----------------------------------------------------------------------------
 */
extern void multimap_erase_range(
    multimap_t* pt_multimap, 
    multimap_iterator_t t_begin, 
    multimap_iterator_t t_end);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_MULTIMAP_H */
/** eof **/

