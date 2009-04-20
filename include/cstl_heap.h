/*
 *  The interface of heap.
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

#ifndef _CSTL_HEAP_H
#define _CSTL_HEAP_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_push_heap
 *        Parameters: in) t_first: random_access_iterator_t
 *                            the first iterator.
 *                    in) t_last: random_access_iterator_t
 *                            the last iterator
 *           Returns: void
 *       Description: add an element to a heap, it assumed the rang 
 *                    [t_first, t_last - 1) is already a heap, the element to
 *                    be added the heap is *(t_last -1).
 *
 * ----------------------------------------------------------------------------
 */
extern void algo_push_heap(
    random_access_iterator_t t_first, random_access_iterator_t t_last);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_push_heap_if
 *        Parameters: in) t_first: random_access_iterator_t
 *                            the first iterator.
 *                    in) t_last: random_access_iterator_t
 *                            the last iterator
 *                    in) t_binary_op: binary_function_t
 *                            binary function.
 *           Returns: void
 *       Description: add an element to a heap, it assumed the rang 
 *                    [t_first, t_last - 1) is already a heap, the element to
 *                    be added the heap is *(t_last -1).
 *
 * ----------------------------------------------------------------------------
 */
extern void algo_push_heap_if(
    random_access_iterator_t t_first, random_access_iterator_t t_last,
    binary_function_t t_binary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_pop_heap
 *        Parameters: in) t_first: random_access_iterator_t
 *                            the first iterator.
 *                    in) t_last: random_access_iterator_t
 *                            the last iterator
 *           Returns: void
 *       Description: remove t_first from a heap.
 *
 * ----------------------------------------------------------------------------
 */
extern void algo_pop_heap(
    random_access_iterator_t t_first, random_access_iterator_t t_last);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_pop_heap_if
 *        Parameters: in) t_first: random_access_iterator_t
 *                            the first iterator.
 *                    in) t_last: random_access_iterator_t
 *                            the last iterator
 *                    in) t_binary_op: binary_function_t
 *                            binary function.
 *           Returns: void
 *       Description: remove t_first from a heap.
 *
 * ----------------------------------------------------------------------------
 */
extern void algo_pop_heap_if(
    random_access_iterator_t t_first, random_access_iterator_t t_last,
    binary_function_t t_binary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_sort_heap
 *        Parameters: in) t_first: random_access_iterator_t
 *                            the first iterator.
 *                    in) t_last: random_access_iterator_t
 *                            the last iterator
 *           Returns: void
 *       Description: turn a heap [t_first, t_last) into a sort range.
 *
 * ----------------------------------------------------------------------------
 */
extern void algo_sort_heap(
    random_access_iterator_t t_first, random_access_iterator_t t_last);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_sort_heap_if
 *        Parameters: in) t_first: random_access_iterator_t
 *                            the first iterator.
 *                    in) t_last: random_access_iterator_t
 *                            the last iterator
 *                    in) t_binary_op: binary_function_t
 *                            binary function.
 *           Returns: void
 *       Description: turn a heap [t_first, t_last) into a sort range.
 *
 * ----------------------------------------------------------------------------
 */
extern void algo_sort_heap_if(
    random_access_iterator_t t_first, random_access_iterator_t t_last,
    binary_function_t t_binary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_make_heap
 *        Parameters: in) t_first: random_access_iterator_t
 *                            the first iterator.
 *                    in) t_last: random_access_iterator_t
 *                            the last iterator
 *           Returns: void
 *       Description: turn the rang [t_first, t_last) into heap.
 *
 * ----------------------------------------------------------------------------
 */
extern void algo_make_heap(
    random_access_iterator_t t_first, random_access_iterator_t t_last);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_make_heap_if
 *        Parameters: in) t_first: random_access_iterator_t
 *                            the first iterator.
 *                    in) t_last: random_access_iterator_t
 *                            the last iterator
 *                    in) t_binary_op: binary_function_t
 *                            binary function.
 *           Returns: void
 *       Description: turn the rang [t_first, t_last) into heap.
 *
 * ----------------------------------------------------------------------------
 */
extern void algo_make_heap_if(
    random_access_iterator_t t_first, random_access_iterator_t t_last,
    binary_function_t t_binary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_is_heap
 *        Parameters: in) t_first: random_access_iterator_t
 *                            the first iterator.
 *                    in) t_last: random_access_iterator_t
 *                            the last iterator
 *           Returns: bool_t
 *       Description: return ture is  the rang [t_first, t_last) is a heap.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t algo_is_heap(
    random_access_iterator_t t_first, random_access_iterator_t t_last);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_is_heap_if
 *        Parameters: in) t_first: random_access_iterator_t
 *                            the first iterator.
 *                    in) t_last: random_access_iterator_t
 *                            the last iterator
 *                    in) t_binary_op: binary_function_t
 *                            binary function.
 *           Returns: bool_t
 *       Description: return ture is  the rang [t_first, t_last) is a heap.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t algo_is_heap_if(
    random_access_iterator_t t_first, random_access_iterator_t t_last,
    binary_function_t t_binary_op);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_HEAP_H */
/** eof **/

