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
#define create_slist(type)\
    _create_slist(sizeof(type), #type)
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
 * ----------------------------------------------------------------------------
 *
 *      Functionname: slist_init
 *        Parameters: in) pt_slist: slist_t*
 *           Returns: void
 *       Description: initialize the slist.
 *
 * ----------------------------------------------------------------------------
 */
extern void slist_init(slist_t* pt_slist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: slist_init_n
 *        Parameters: in) pt_slist: slist_t*
 *                    in) t_count: size_t
 *                          element count.
 *           Returns: void
 *       Description: initialize the slist.
 *
 * ----------------------------------------------------------------------------
 */
extern void slist_init_n(slist_t* pt_slist, size_t t_count);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: slist_destroy
 *        Parameters: in) pt_slist: slist_t*
 *           Returns: void
 *       Description: destroy the slist.
 *
 * ----------------------------------------------------------------------------
 */
extern void slist_destroy(slist_t* pt_slist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: slist_begin
 *        Parameters: in) cpt_slist: const slist_t*
 *                          the slist.
 *           Returns: slist_iterator_t
 *       Description: return the random access iterator for the first element.
 *
 * ----------------------------------------------------------------------------
 */
extern slist_iterator_t slist_begin(const slist_t* cpt_slist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: slist_end
 *        Parameters: in) cpt_slist: const slist_t*
 *                          the slist.
 *           Returns: slist_iterator_t
 *       Description: return the random access iterator for the last element.
 *
 * ----------------------------------------------------------------------------
 */
extern slist_iterator_t slist_end(const slist_t* cpt_slist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: slist_size
 *        Parameters: in) cpt_slist: const slist_t*
 *                          the dest slist.
 *           Returns: size_t
 *       Description: get the slist size.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t slist_size(const slist_t* cpt_slist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: slist_empty
 *        Parameters: in) cpt_slist: const slist_t*
 *                          the dest slist.
 *           Returns: bool_t
 *       Description: if the slist is empty.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t slist_empty(const slist_t* cpt_slist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: slist_max_size
 *        Parameters: in) cpt_slist: const slist_t*
 *                          the dest slist.
 *           Returns: size_t
 *       Description: get the maximum capacity of slist.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t slist_max_size(const slist_t* cpt_slist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: slist_init_copy
 *        Parameters: in) pt_slistdest: slist_t*
 *                          the dest slist.
 *                    in) cpt_slistsrc: const slist_t*
 *                          the source slist.
 *           Returns: void
 *       Description: the copy constructor.
 *
 * ----------------------------------------------------------------------------
 */
extern void slist_init_copy(slist_t* pt_slistdest, const slist_t* cpt_slistsrc);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: slist_init_copy_range
 *        Parameters: in) pt_slistdest: slist_t*
 *                          the dest slist.
 *                    in) t_begin: slist_iterator_t
 *                          the begin iterator.
 *                    in) t_end: slist_iterator_t
 *                          the end iterator.
 *           Returns: void
 *       Description: the slist copy constructor with specific range.
 *
 * ----------------------------------------------------------------------------
 */
extern void slist_init_copy_range(
    slist_t* pt_slistdest, slist_iterator_t t_begin, slist_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: slist_assign
 *        Parameters: in) pt_slistdest: slist_t*
 *                          the dest slist.
 *                    in) cpt_slistsrc: const slist_t*
 *                          the source slist.
 *           Returns: void
 *       Description: the assignment operator.
 *
 * ----------------------------------------------------------------------------
 */
extern void slist_assign(slist_t* pt_slistdest, const slist_t* cpt_slistsrc);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: slist_assign_range
 *        Parameters: in) pt_slist: slist_t*
 *                          the slist for assign.
 *                    in) t_begin: slist_iterator_t
 *                          the begin iterator.
 *                    in) t_end: slist_iterator_t
 *                          the end iterator.
 *           Returns: void
 *       Description: assign the elements of range [t_begin, t_end)
 *
 * ----------------------------------------------------------------------------
 */
extern void slist_assign_range(
    slist_t* pt_slist, 
    slist_iterator_t t_begin,
    slist_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: slist_swap
 *        Parameters: in) pt_slistfirst: slist_t*
 *                          the first slist.
 *                    in) pt_slistsecond: slist_t*
 *                          the second slist.
 *           Returns: void
 *       Description: swap the datas of first slist and second slist.
 *
 * ----------------------------------------------------------------------------
 */
extern void slist_swap(slist_t* pt_slistfirst, slist_t* pt_slistsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: slist_front
 *        Parameters: in) cpt_slist: const slist_t*
 *                          the slist.
 *           Returns: void*
 *       Description: return the first element.
 *
 * ----------------------------------------------------------------------------
 */
extern void* slist_front(const slist_t* cpt_slist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: slist_pop_front
 *        Parameters: in) pt_slist: slist_t*
 *                          the slist.
 *           Returns: void
 *       Description: remove the first element and does not return it.
 *
 * ----------------------------------------------------------------------------
 */
extern void slist_pop_front(slist_t* pt_slist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: slist_previous
 *        Parameters: in) cpt_slist: const slist_t*
 *                          the slist.
 *                    in) t_pos: slist_iterator_t
 *                          the iterator.
 *           Returns: slist_iterator_t
 *                          the previous iterator.
 *       Description: get the previous iterator with t_pos.
 *
 * ----------------------------------------------------------------------------
 */
extern slist_iterator_t slist_previous(
    const slist_t* cpt_slist, slist_iterator_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: slist_insert_range
 *        Parameters: in) pt_slist: slist_t*
 *                          the slist.
 *                    in) t_pos: slist_iterator_t
 *                          the insert position.
 *                    in) t_begin: slist_iterator_t
 *                          the begin insert position.
 *                    in) t_end: slist_iterator_t
 *                          the end insert position.
 *           Returns: void
 *       Description: insert at iterator position t_pos a copy of all elements 
 *                    of range [t_begin, t_end) and return nothing.
 *
 * ----------------------------------------------------------------------------
 */
extern void slist_insert_range(
    slist_t* pt_slist, slist_iterator_t t_pos, 
    slist_iterator_t t_begin, slist_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: slist_insert_after_range
 *        Parameters: in) pt_slist: slist_t*
 *                          the slist.
 *                    in) t_pos: slist_iterator_t
 *                          the insert_after position.
 *                    in) t_begin: slist_iterator_t
 *                          the begin insert_after position.
 *                    in) t_end: slist_iterator_t
 *                          the end insert_after position.
 *           Returns: void
 *       Description: insert_after at iterator position t_pos a copy of all elements 
 *                    of range [t_begin, t_end) and return nothing.
 *
 * ----------------------------------------------------------------------------
 */
extern void slist_insert_after_range(
    slist_t* pt_slist, slist_iterator_t t_pos, 
    slist_iterator_t t_begin, slist_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: slist_erase
 *        Parameters: in) pt_slist: slist_t*
 *                          the slist.
 *                    in) t_pos: slist_iterator_t
 *                          the erase position
 *           Returns: slist_iterator_t
 *       Description: remove the element at the iterator position t_pos and 
 *                    return the position of next element.
 *
 * ----------------------------------------------------------------------------
 */
extern slist_iterator_t slist_erase(slist_t* pt_slist, slist_iterator_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: slist_erase_range
 *        Parameters: in) pt_slist: slist_t*
 *                          the slist.
 *                    in) t_begin: slist_iterator_t
 *                          the begin position of erase range
 *                    in) t_end: slist_iterator_t
 *                          the end position of erase range
 *           Returns: slist_iterator_t
 *       Description: remove all elements of the range [t_begin, t_end) and 
 *                    return the position of next element.
 *
 * ----------------------------------------------------------------------------
 */
extern slist_iterator_t slist_erase_range(
    slist_t* pt_slist, slist_iterator_t t_begin, slist_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: slist_erase_after
 *        Parameters: in) pt_slist: slist_t*
 *                          the slist.
 *                    in) t_pos: slist_iterator_t
 *                          the erase position
 *           Returns: slist_iterator_t
 *       Description: erase the element pointed to by the iterator following
 *                    the pos.
 *
 * ----------------------------------------------------------------------------
 */
extern slist_iterator_t slist_erase_after(
    slist_t* pt_slist, slist_iterator_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: slist_erase_after_range
 *        Parameters: in) pt_slist: slist_t*
 *                          the slist.
 *                    in) t_begin: slist_iterator_t
 *                          the begin position of erase range
 *                    in) t_end: slist_iterator_t
 *                          the end position of erase range
 *           Returns: slist_iterator_t
 *       Description: erase all elements in range [t_begin+1, t_end).
 *
 * ----------------------------------------------------------------------------
 */
extern slist_iterator_t slist_erase_after_range(
    slist_t* pt_slist, slist_iterator_t t_begin, slist_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: slist_splice
 *        Parameters: in) pt_slist: slist_t*
 *                          the slist.
 *                    in) t_pos: slist_iterator_t
 *                          the insert position
 *                    in) pt_slistsrc: slist_t*
 *                          the source slist.
 *           Returns: void
 *       Description: move all elements of source slist to slist in front of 
 *                    iterator position t_pos.
 *
 * ----------------------------------------------------------------------------
 */
extern void slist_splice(
    slist_t* pt_slist, slist_iterator_t t_pos, slist_t* pt_slistsrc);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: slist_splice_pos
 *        Parameters: in) pt_slist: slist_t*
 *                          the slist.
 *                    in) t_pos: slist_iterator_t
 *                          the insert position
 *                    in) pt_slistsrc: slist_t*
 *                          the source slist.
 *                    in) t_possrc: slist_iterator_t
 *                          the begin position in source slist
 *           Returns: void
 *       Description: move the element at t_possrc in slistsrc in front of
 *                    t_pos of slist (slist and slistsrc may be identical).
 *
 * ----------------------------------------------------------------------------
 */
extern void slist_splice_pos(
    slist_t* pt_slist, slist_iterator_t t_pos, 
    slist_t* pt_slistsrc, slist_iterator_t t_possrc);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: slist_splice_range
 *        Parameters: in) pt_slist: slist_t*
 *                          the slist.
 *                    in) t_pos: slist_iterator_t
 *                          the insert position
 *                    in) pt_slistsrc: slist_t*
 *                          the source slist.
 *                    in) t_begin: slist_iterator_t
 *                          the begin position in source slist
 *                    in) t_end: slist_iterator_t
 *                          the end position in source slist
 *           Returns: void
 *       Description: move the elements in range [t_begin, t_end) in slistsrc 
 *                    in front of t_pos of slist (slist and slistsrc may be 
 *                    identical).
 *
 * ----------------------------------------------------------------------------
 */
extern void slist_splice_range(
    slist_t* pt_slist, 
    slist_iterator_t t_pos, 
    slist_t* pt_slistsrc, 
    slist_iterator_t t_begin, 
    slist_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: slist_splice_after_pos
 *        Parameters: in) pt_slist: slist_t*
 *                          the slist.
 *                    in) t_pos: slist_iterator_t
 *                          the insert position
 *                    in) pt_slistsrc: slist_t*
 *                          the source slist.
 *                    in) t_prev: slist_iterator_t
 *                          the position before in source slist
 *           Returns: void
 *       Description: move the element at t_possrc in slistsrc in front of
 *                    t_pos of slist (slist and slistsrc may be identical).
 *
 * ----------------------------------------------------------------------------
 */
extern void slist_splice_after_pos(
    slist_t* pt_slist, slist_iterator_t t_pos, 
    slist_t* pt_slistsrc, slist_iterator_t t_prev);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: slist_splice_after_range
 *        Parameters: in) pt_slist: slist_t*
 *                          the slist.
 *                    in) t_pos: slist_iterator_t
 *                          the insert position
 *                    in) pt_slistsrc: slist_t*
 *                          the source slist.
 *                    in) t_begin: slist_iterator_t
 *                          the begin position in source slist
 *                    in) t_end: slist_iterator_t
 *                          the end position in source slist
 *           Returns: void
 *       Description: move the elements in range [t_beforefirst+1,
 *                    t_beforelast+1) in slistsrc in front of t_pos of slist 
 *                    (slist and slistsrc may be identical).
 *
 * ----------------------------------------------------------------------------
 */
extern void slist_splice_after_range(
    slist_t* pt_slist,
    slist_iterator_t t_pos, 
    slist_t* pt_slistsrc,
    slist_iterator_t t_beforefirst, 
    slist_iterator_t t_beforelast);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: slist_remove_if
 *        Parameters: in) pt_slist: slist_t*
 *                          the slist.
 *                    in) t_unary_op: unary_function_t
 *           Returns: void
 *       Description: remove all elements for which op yields true.
 *
 * ----------------------------------------------------------------------------
 */
extern void slist_remove_if(slist_t* pt_slist, unary_function_t t_unary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: slist_unique
 *        Parameters: in) pt_slist: slist_t*
 *                          the slist.
 *           Returns: void
 *       Description: remove duplicates of consecutive elements with the same
 *                    value.
 *
 * ----------------------------------------------------------------------------
 */
extern void slist_unique(slist_t* pt_slist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: slist_unique_if
 *        Parameters: in) pt_slist: slist_t*
 *                          the slist.
 *                    in) t_binary_op: binary_function_t
 *           Returns: void
 *       Description: remove duplicates of consecutive elements for which op()
 *                    yields true.
 *
 * ----------------------------------------------------------------------------
 */
extern void slist_unique_if(slist_t* pt_slist, binary_function_t t_binary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: slist_reverse
 *        Parameters: in) pt_slist: slist_t*
 *                          the slist.
 *           Returns: void
 *       Description: reverse the order of all elements.
 *
 * ----------------------------------------------------------------------------
 */
extern void slist_reverse(slist_t* pt_slist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: slist_sort
 *        Parameters: in) pt_slist: slist_t*
 *                          the slist.
 *           Returns: void
 *       Description: sort all elements with operator <.
 *
 * ----------------------------------------------------------------------------
 */
extern void slist_sort(slist_t* pt_slist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: slist_sort_if
 *        Parameters: in) pt_slist: slist_t*
 *                          the slist.
 *                    in) t_binary_op: binary_function_t
 *           Returns: void
 *       Description: sort all elements with operator pfun_op function.
 *
 * ----------------------------------------------------------------------------
 */
extern void slist_sort_if(slist_t* pt_slist, binary_function_t t_binary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: slist_merge
 *        Parameters: in) pt_slistdest: slist_t*
 *                          the dest slist.
 *                    in) pt_slistsrc: slist_t*
 *                          the source slist.
 *           Returns: void
 *       Description: assuming both container contain the elements sorted, move
 *                    all elements of source slist into dest slist so that all
 *                    elements merged and still sorted.
 *
 * ----------------------------------------------------------------------------
 */
extern void slist_merge(slist_t* pt_slistdest, slist_t* pt_slistsrc);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: slist_merge_if
 *        Parameters: in) pt_slistdest: slist_t*
 *                          the dest slist.
 *                    in) pt_slistsrc: slist_t*
 *                          the source slist.
 *                    in) t_binary_op: binary_function_t
 *           Returns: void
 *       Description: assuming both container contain the elements sorted, move
 *                    all elements of source slist into dest slist so that all
 *                    elements merged and still sorted (with the confition
 *                    function pfun_op).
 *
 * ----------------------------------------------------------------------------
 */
extern void slist_merge_if(
    slist_t* pt_slistdest, slist_t* pt_slistsrc, 
    binary_function_t t_binary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: slist_resize
 *        Parameters: in) pt_slist: slist_t*
 *                          the slist.
 *                    in) t_resize: size_t
 *                          the new size of slist.
 *           Returns: void
 *       Description: change the number of elements to t_resize, if the size
 *                    grows new element create with the default 0.
 *
 * ----------------------------------------------------------------------------
 */
extern void slist_resize(slist_t* pt_slist, size_t t_resize);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: slist_clear
 *        Parameters: in) pt_slist: slist_t*
 *                          the slist.
 *           Returns: void
 *       Description: remove all elements.
 *
 * ----------------------------------------------------------------------------
 */
extern void slist_clear(slist_t* pt_slist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: slist_equal
 *        Parameters: in) cpt_slistfirst: const slist_t*
 *                          the first slist.
 *                    in) cpt_slistsecond: const slist_t*
 *                          the second slist.
 *           Returns: bool_t
 *       Description: return whether first slist equal to second slist.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t slist_equal(
    const slist_t* cpt_slistfirst, const slist_t* cpt_slistsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: slist_not_equal
 *        Parameters: in) cpt_slistfirst: const slist_t*
 *                          the first slist.
 *                    in) cpt_slistsecond: const slist_t*
 *                          the second slist.
 *           Returns: bool_t
 *       Description: return whether first slist not equal to second slist.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t slist_not_equal(
    const slist_t* cpt_slistfirst, const slist_t* cpt_slistsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: slist_less
 *        Parameters: in) cpt_slistfirst: const slist_t*
 *                          the first slist.
 *                    in) cpt_slistsecond: const slist_t*
 *                          the second slist.
 *           Returns: bool_t
 *       Description: return whether first slist less then second slist.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t slist_less(
    const slist_t* cpt_slistfirst, const slist_t* cpt_slistsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: slist_great
 *        Parameters: in) cpt_slistfirst: const slist_t*
 *                          the first slist.
 *                    in) cpt_slistsecond: const slist_t*
 *                          the second slist.
 *           Returns: bool_t
 *       Description: return whether first slist greater then second slist.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t slist_great(
    const slist_t* cpt_slistfirst, const slist_t* cpt_slistsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: slist_less_equal
 *        Parameters: in) cpt_slistfirst: const slist_t*
 *                          the first slist.
 *                    in) cpt_slistsecond: const slist_t*
 *                          the second slist.
 *           Returns: bool_t
 *       Description: return whether first slist less then or equal to the 
 *                    second slist.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t slist_less_equal(
    const slist_t* cpt_slistfirst, const slist_t* cpt_slistsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: slist_great_equal
 *        Parameters: in) cpt_slistfirst: const slist_t*
 *                          the first slist.
 *                    in) cpt_slistsecond: const slist_t*
 *                          the second slist.
 *           Returns: bool_t
 *       Description: return whether first slist greater then or equal to the
 *                    second slist.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t slist_great_equal(
    const slist_t* cpt_slistfirst, const slist_t* cpt_slistsecond);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_SLIST_H */
/** eof **/

