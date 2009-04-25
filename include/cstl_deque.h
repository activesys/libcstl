/*
 *  The user interface of deque.
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

#ifndef _CSTL_DEQUE_H
#define _CSTL_DEQUE_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/* create new deque with specify type */
#define create_deque(type)\
    _create_deque(sizeof(type), #type)
/* initialize */
#define deque_init_elem(pt_deque, t_count, elem)\
    _deque_init_elem((pt_deque), (t_count), (elem))
/* assign */
#define deque_assign_elem(pt_deque, t_count, elem)\
    _deque_assign_elem((pt_deque), (t_count), (elem))
/* push back and push front */
#define deque_push_back(pt_deque, elem)\
    _deque_push_back((pt_deque), (elem))
#define deque_push_front(pt_deque, elem)\
    _deque_push_front((pt_deque), (elem))
/* resize */
#define deque_resize_elem(pt_deque, t_resize, elem)\
    _deque_resize_elem((pt_deque), (t_resize), (elem))
/* insert */
#define deque_insert(pt_deque, t_pos, elem)\
    _deque_insert_n((pt_deque), (t_pos), 1, (elem))
#define deque_insert_n(pt_deque, t_pos, t_count, elem)\
    _deque_insert_n((pt_deque), (t_pos), (t_count), (elem))

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: deque_init
 *        Parameters: in) pt_deque: deque_t*
 *           Returns: void
 *       Description: initialize the deque.
 *
 * ----------------------------------------------------------------------------
 */
extern void deque_init(deque_t* pt_deque);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: deque_init_n
 *        Parameters: in) pt_deque: deque_t*
 *                    in) t_count: size_t
 *                          element count.
 *           Returns: void
 *       Description: initialize the deque.
 *
 * ----------------------------------------------------------------------------
 */
extern void deque_init_n(deque_t* pt_deque, size_t t_count);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: deque_destroy
 *        Parameters: in) pt_deque: deque_t*
 *           Returns: void
 *       Description: destroy the deque.
 *
 * ----------------------------------------------------------------------------
 */
extern void deque_destroy(deque_t* pt_deque);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: deque_init_copy
 *        Parameters: in) pt_dequedest: deque_t*
 *                          the dest deque.
 *                    in) cpt_dequesrc: const deque_t*
 *                          the source deque.
 *           Returns: void
 *       Description: the copy constructor.
 *
 * ----------------------------------------------------------------------------
 */
extern void deque_init_copy(deque_t* pt_dequedest, const deque_t* cpt_dequesrc);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: deque_init_copy_range
 *        Parameters: in) pt_dequedest: deque_t*
 *                          the dest deque.
 *                    in) t_begin: deque_iterator_t
 *                          the begin iterator.
 *                    in) t_end: deque_iterator_t
 *                          the end iterator.
 *           Returns: void
 *       Description: the copy constructor with specific range.
 *
 * ----------------------------------------------------------------------------
 */
extern void deque_init_copy_range(
    deque_t* pt_dequedest, deque_iterator_t t_begin, deque_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: deque_empty
 *        Parameters: in) cpt_deque: const deque_t*
 *                          the dest deque.
 *           Returns: bool_t
 *       Description: if the deque is empty.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t deque_empty(const deque_t* cpt_deque);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: deque_size
 *        Parameters: in) cpt_deque: const deque_t*
 *                          the dest deque.
 *           Returns: size_t
 *       Description: get the deque size.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t deque_size(const deque_t* cpt_deque);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: deque_max_size
 *        Parameters: in) cpt_deque: const deque_t*
 *                          the dest deque.
 *           Returns: size_t
 *       Description: get the maximum capacity of deque.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t deque_max_size(const deque_t* cpt_deque);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: deque_front
 *        Parameters: in) cpt_deque: const deque_t*
 *                          the deque.
 *           Returns: void*
 *       Description: return the first element.
 *
 * ----------------------------------------------------------------------------
 */
extern void* deque_front(const deque_t* cpt_deque);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: deque_back
 *        Parameters: in) cpt_deque: const deque_t*
 *                          the deque.
 *           Returns: void*
 *       Description: return the last element.
 *
 * ----------------------------------------------------------------------------
 */
extern void* deque_back(const deque_t* cpt_deque);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: deque_begin
 *        Parameters: in) cpt_deque: const deque_t*
 *                          the deque.
 *           Returns: deque_iterator_t
 *       Description: return the random access iterator for the first element.
 *
 * ----------------------------------------------------------------------------
 */
extern deque_iterator_t deque_begin(const deque_t* cpt_deque);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: deque_end
 *        Parameters: in) cpt_deque: const deque_t*
 *                          the deque.
 *           Returns: deque_iterator_t
 *       Description: return the random access iterator for the last element.
 *
 * ----------------------------------------------------------------------------
 */
extern deque_iterator_t deque_end(const deque_t* cpt_deque);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: deque_rbegin
 *        Parameters: in) cpt_deque: const deque_t*
 *                          the deque.
 *           Returns: deque_reverse_iterator_t
 *       Description: return the reverse iterator for the first element of the
 *                    reverse iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern deque_reverse_iterator_t deque_rbegin(const deque_t* cpt_deque);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: deque_rend
 *        Parameters: in) cpt_deque: const deque_t*
 *                          the deque.
 *           Returns: deque_reverse_iterator_t
 *       Description: return the reverse iterator for the last element of the
 *                    reverse iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern deque_reverse_iterator_t deque_rend(const deque_t* cpt_deque);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: deque_assign
 *        Parameters: in) pt_dequedest: deque_t*
 *                          the dest deque.
 *                    in) cpt_dequesrc: const deque_t*
 *                          the source deque.
 *           Returns: void
 *       Description: the assignment operator.
 *
 * ----------------------------------------------------------------------------
 */
extern void deque_assign(deque_t* pt_dequedest, const deque_t* cpt_dequesrc);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: deque_assign_range
 *        Parameters: in) pt_deque: deque_t*
 *                          the deque for assign.
 *                    in) t_begin: deque_iterator_t
 *                          the begin iterator.
 *                    in) t_end: deque_iterator_t
 *                          the end iterator.
 *           Returns: void
 *       Description: assign the elements of range [t_begin, t_end)
 *
 * ----------------------------------------------------------------------------
 */
extern void deque_assign_range(
    deque_t* pt_deque, deque_iterator_t t_begin, deque_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: deque_equal
 *        Parameters: in) cpt_dequefirst: const deque_t*
 *                          the first deque.
 *                    in) cpt_dequesecond: const deque_t*
 *                          the second deque.
 *           Returns: bool_t
 *       Description: return whether first deque equal to second deque.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t deque_equal(
    const deque_t* cpt_dequefirst, const deque_t* cpt_dequesecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: deque_not_equal
 *        Parameters: in) cpt_dequefirst: const deque_t*
 *                          the first deque.
 *                    in) cpt_dequesecond: const deque_t*
 *                          the second deque.
 *           Returns: bool_t
 *       Description: return whether first deque not equal to second deque.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t deque_not_equal(
    const deque_t* cpt_dequefirst, const deque_t* cpt_dequesecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: deque_less
 *        Parameters: in) cpt_dequefirst: const deque_t*
 *                          the first deque.
 *                    in) cpt_dequesecond: const deque_t*
 *                          the second deque.
 *           Returns: bool_t
 *       Description: return whether first deque less then second deque.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t deque_less(
    const deque_t* cpt_dequefirst, const deque_t* cpt_dequesecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: deque_great
 *        Parameters: in) cpt_dequefirst: const deque_t*
 *                          the first deque.
 *                    in) cpt_dequesecond: const deque_t*
 *                          the second deque.
 *           Returns: bool_t
 *       Description: return whether first deque greater then second deque.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t deque_great(
    const deque_t* cpt_dequefirst, const deque_t* cpt_dequesecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: deque_less_equal
 *        Parameters: in) cpt_dequefirst: const deque_t*
 *                          the first deque.
 *                    in) cpt_dequesecond: const deque_t*
 *                          the second deque.
 *           Returns: bool_t
 *       Description: return whether first deque less then or equal to the 
 *                    second deque.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t deque_less_equal(
    const deque_t* cpt_dequefirst, const deque_t* cpt_dequesecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: deque_great_equal
 *        Parameters: in) cpt_dequefirst: const deque_t*
 *                          the first deque.
 *                    in) cpt_dequesecond: const deque_t*
 *                          the second deque.
 *           Returns: bool_t
 *       Description: return whether first deque greater then or equal to the
 *                    second deque.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t deque_great_equal(
    const deque_t* cpt_dequefirst, const deque_t* cpt_dequesecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: deque_at
 *        Parameters: in) cpt_deque: const deque_t*
 *                          the deque.
 *                    in) t_pos: size_t
 *                          the element pos.
 *           Returns: void*
 *       Description: return the element with the n_elempos.
 *
 * ----------------------------------------------------------------------------
 */
extern void* deque_at(const deque_t* cpt_deque, size_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: deque_swap
 *        Parameters: in) pt_dequefirst: deque_t*
 *                          the first deque.
 *                    in) pt_dequesecond: deque_t*
 *                          the second deque.
 *           Returns: void
 *       Description: swap the datas of first deque and second deque.
 *
 * ----------------------------------------------------------------------------
 */
extern void deque_swap(deque_t* pt_dequefirst, deque_t* pt_dequesecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: deque_pop_back
 *        Parameters: in) pt_deque: deque_t*
 *                          the deque.
 *           Returns: void
 *       Description: remove the last element and does not return it.
 *
 * ----------------------------------------------------------------------------
 */
extern void deque_pop_back(deque_t* pt_deque);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: deque_pop_front
 *        Parameters: in) pt_deque: deque_t*
 *                          the deque.
 *           Returns: void
 *       Description: remove the first element and does not return it.
 *
 * ----------------------------------------------------------------------------
 */
extern void deque_pop_front(deque_t* pt_deque);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: deque_insert_range
 *        Parameters: in) pt_deque: deque_t*
 *                          the deque.
 *                    in) t_pos: deque_iterator_t
 *                          the insert position.
 *                    in) t_begin: deque_iterator_t
 *                          the begin insert position.
 *                    in) t_end: deque_iterator_t
 *                          the end insert position.
 *           Returns: void
 *       Description: insert at iterator position t_pos a copy of all elements 
 *                    of range [t_begin, t_end) and return nothing.
 *
 * ----------------------------------------------------------------------------
 */
extern void deque_insert_range(
    deque_t* pt_deque, deque_iterator_t t_pos, 
    deque_iterator_t t_begin, deque_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: deque_erase
 *        Parameters: in) pt_deque: deque_t*
 *                          the deque.
 *                    in) t_pos: deque_iterator_t
 *                          the erase position
 *           Returns: deque_iterator_t
 *       Description: remove the element at the iterator position t_pos and 
 *                    return the position of next element.
 *
 * ----------------------------------------------------------------------------
 */
extern deque_iterator_t deque_erase(deque_t* pt_deque, deque_iterator_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: deque_erase_range
 *        Parameters: in) pt_deque: deque_t*
 *                          the deque.
 *                    in) t_begin: deque_iterator_t
 *                          the begin position of erase range
 *                    in) t_end: deque_iterator_t
 *                          the end position of erase range
 *           Returns: deque_iterator_t
 *       Description: remove all elements of the range [t_begin, t_end) and 
 *                    return the position of next element.
 *
 * ----------------------------------------------------------------------------
 */
extern deque_iterator_t deque_erase_range(
    deque_t* pt_deque, deque_iterator_t t_begin, deque_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: deque_resize
 *        Parameters: in) pt_deque: deque_t*
 *                          the deque.
 *                    in) t_resize: size_t
 *                          the new size of deque.
 *           Returns: void
 *       Description: change the number of elements to t_resize, if the size
 *                    grows new element create with the default 0.
 *
 * ----------------------------------------------------------------------------
 */
extern void deque_resize(deque_t* pt_deque, size_t t_resize);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: deque_clear
 *        Parameters: in) pt_deque: deque_t*
 *                          the deque.
 *           Returns: void
 *       Description: remove all elements.
 *
 * ----------------------------------------------------------------------------
 */
extern void deque_clear(deque_t* pt_deque);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_DEQUE_H */
/** eof **/

