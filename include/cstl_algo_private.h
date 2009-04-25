/*
 *  The private interface of algorithm.
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

#ifndef _CSTL_ALGO_PRIVATE_H
#define _CSTL_ALGO_PRIVATE_H

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
 *      Functionname: _algo_count
 *        Parameters: in) t_first: input_iterator_t
 *                        the first iterator.
 *                    in) t_last: input_iterator_t
 *                        the last iterator.
 *                    in) ...
 *           Returns: size_t
 *       Description: finds the number of elements in range [t_first, t_last)
 *                    that are equal to value.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t _algo_count(
    input_iterator_t t_first, input_iterator_t t_last, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _algo_count_varg
 *        Parameters: in) t_first: input_iterator_t
 *                        the first iterator.
 *                    in) t_last: input_iterator_t
 *                        the last iterator.
 *                    in) val_elemlist: va_list
 *                        value list.
 *           Returns: size_t
 *       Description: finds the number of elements in range [t_first, t_last)
 *                    that are equal to value.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t _algo_count_varg(
    input_iterator_t t_first, input_iterator_t t_last, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _algo_find
 *        Parameters: in) t_first: input_iterator_t
 *                        the first iterator.
 *                    in) t_last: input_iterator_t
 *                        the last iterator.
 *                    in) ...
 *           Returns: input_iterator_t
 *       Description: return the first iterator i in range [t_first, t_last),
 *                    such that *i == value. return t_last if no such iterator
 *                    exists.
 *
 * ----------------------------------------------------------------------------
 */
extern input_iterator_t _algo_find(
    input_iterator_t t_first, input_iterator_t t_last, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _algo_find_varg
 *        Parameters: in) t_first: input_iterator_t
 *                        the first iterator.
 *                    in) t_last: input_iterator_t
 *                        the last iterator.
 *                    in) val_elemlist: va_list
 *                        value list.
 *           Returns: input_iterator_t
 *       Description: return the first iterator i in range [t_first, t_last),
 *                    such that *i == value. return t_last if no such iterator
 *                    exists.
 *
 * ----------------------------------------------------------------------------
 */
extern input_iterator_t _algo_find_varg(
    input_iterator_t t_first, input_iterator_t t_last, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _algo_search_n
 *        Parameters: in) t_first: forward_iterator_t
 *                        the first iterator.
 *                    in) t_last: forward_iterator_t
 *                        the last iterator.
 *                    in) ...
 *                        value list.
 *           Returns: input_iterator_t
 *       Description: searchs for a sequence of t_count consecutive elements
 *                    in the range [t_first, t_last), all of which are equal
 *                    to value.
 *
 * ----------------------------------------------------------------------------
 */
extern forward_iterator_t _algo_search_n(
    forward_iterator_t t_first, forward_iterator_t t_last,
    size_t t_count, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _algo_search_n_if
 *        Parameters: in) t_first: forward_iterator_t
 *                        the first iterator.
 *                    in) t_last: forward_iterator_t
 *                        the last iterator.
 *                    in) t_count: size_t
 *                        value count.
 *                    in) t_binary_op: binary_function_t
 *                        binary function.
 *                    in) ...
 *                        value list.
 *           Returns: input_iterator_t
 *       Description: searchs for a sequence of t_count consecutive elements
 *                    in the range [t_first, t_last), all of which are equal
 *                    to value.
 *
 * ----------------------------------------------------------------------------
 */
extern forward_iterator_t _algo_search_n_if(
    forward_iterator_t t_first, forward_iterator_t t_last,
    size_t t_count, binary_function_t t_binary_op, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _algo_search_n_if_varg
 *        Parameters: in) t_first: forward_iterator_t
 *                        the first iterator.
 *                    in) t_last: forward_iterator_t
 *                        the last iterator.
 *                    in) t_count: size_t
 *                        value count.
 *                    in) t_binary_op: binary_function_t
 *                        binary function.
 *                    in) val_elemlist: va_list
 *                        value list.
 *           Returns: input_iterator_t
 *       Description: searchs for a sequence of t_count consecutive elements
 *                    in the range [t_first, t_last), all of which are equal
 *                    to value.
 *
 * ----------------------------------------------------------------------------
 */
extern forward_iterator_t _algo_search_n_if_varg(
    forward_iterator_t t_first, forward_iterator_t t_last,
    size_t t_count, binary_function_t t_binary_op, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _algo_remove_copy
 *        Parameters: in) t_first: input_iterator_t
 *                        the first iterator.
 *                    in) t_last: input_iterator_t
 *                        the last iterator.
 *                    in) t_result: output_iterator_t
 *                        the output iterator.
 *                    in) ...
 *                        value list.
 *           Returns: output_iterator_t
 *       Description: copies elements that are not equal to value from the 
 *                    range [t_first, t_last) to a range begining at t_result.
 *
 * ----------------------------------------------------------------------------
 */
extern output_iterator_t _algo_remove_copy(
    input_iterator_t t_first, input_iterator_t t_last,
    output_iterator_t t_result, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _algo_remove_copy_varg
 *        Parameters: in) t_first: input_iterator_t
 *                        the first iterator.
 *                    in) t_last: input_iterator_t
 *                        the last iterator.
 *                    in) t_result: output_iterator_t
 *                        the output iterator.
 *                    in) val_elemlist: va_list
 *                        value list.
 *           Returns: output_iterator_t
 *       Description: copies elements that are not equal to value from the 
 *                    range [t_first, t_last) to a range begining at t_result.
 *
 * ----------------------------------------------------------------------------
 */
extern output_iterator_t _algo_remove_copy_varg(
    input_iterator_t t_first, input_iterator_t t_last,
    output_iterator_t t_result, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _algo_remove
 *        Parameters: in) t_first: input_iterator_t
 *                        the first iterator.
 *                    in) t_last: input_iterator_t
 *                        the last iterator.
 *                    in) t_result: output_iterator_t
 *                        the output iterator.
 *                    in) ...
 *                        value list.
 *           Returns: output_iterator_t
 *       Description: copies elements that are not equal to value from the 
 *                    range [t_first, t_last) to a range begining at t_result.
 *
 * ----------------------------------------------------------------------------
 */
extern forward_iterator_t _algo_remove(
    forward_iterator_t t_first, forward_iterator_t t_last, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _algo_remove_varg
 *        Parameters: in) t_first: forward_iterator_t
 *                        the first iterator.
 *                    in) t_last: forward_iterator_t
 *                        the last iterator.
 *                    in) val_elemlist: va_list
 *                        value list.
 *           Returns: forward_iterator_t
 *       Description: copies elements that are not equal to value from the 
 *                    range [t_first, t_last) to a range begining at t_result.
 *
 * ----------------------------------------------------------------------------
 */
extern forward_iterator_t _algo_remove_varg(
    forward_iterator_t t_first, forward_iterator_t t_last, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _algo_replace_once
 *        Parameters: in) t_iterator: forward_iterator_t
 *                        the replace iterator.
 *                    in) ...
 *                        value list.
 *           Returns: void
 *       Description: replace iterator withe new element.
 *
 * ----------------------------------------------------------------------------
 */
extern void _algo_replace_once(forward_iterator_t t_iterator, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _algo_replace_once_varg
 *        Parameters: in) t_iterator: forward_iterator_t
 *                        the replace iterator.
 *                    in) val_elemlist: va_list
 *                        value list.
 *           Returns: void
 *       Description: replace iterator withe new element.
 *
 * ----------------------------------------------------------------------------
 */
extern void _algo_replace_once_varg(
    forward_iterator_t t_iterator, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _algo_replace_if
 *        Parameters: in) t_first: forward_iterator_t
 *                        the first iterator.
 *                    in) t_last: forward_iterator_t
 *                        the last iterator.
 *                    in) t_unary_op: unary_function_t
 *                        the unary operator.
 *                    in) ...
 *                        value list.
 *           Returns: void
 *       Description: replaces every element in the range [t_first, t_last)
 *                    for which t_unary_op output true with new element.
 *
 * ----------------------------------------------------------------------------
 */
extern void _algo_replace_if(
    forward_iterator_t t_first, forward_iterator_t t_last,
    unary_function_t t_unary_op, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _algo_replace_if_varg
 *        Parameters: in) t_first: forward_iterator_t
 *                        the first iterator.
 *                    in) t_last: forward_iterator_t
 *                        the last iterator.
 *                    in) t_unary_op: unary_function_t
 *                        the unary operator.
 *                    in) val_elemlist: va_list
 *                        value list.
 *           Returns: void
 *       Description: replaces every element in the range [t_first, t_last)
 *                    for which t_unary_op output true with new element.
 *
 * ----------------------------------------------------------------------------
 */
extern void _algo_replace_if_varg(
    forward_iterator_t t_first, forward_iterator_t t_last,
    unary_function_t t_unary_op, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _algo_replace_copy_if
 *        Parameters: in) t_first: forward_iterator_t
 *                        the first iterator.
 *                    in) t_last: forward_iterator_t
 *                        the last iterator.
 *                    in) t_result: output_iterator_t
 *                        the output iterator
 *                    in) t_unary_op: unary_function_t
 *                        the unary operator.
 *                    in) ...
 *                        value list.
 *           Returns: output_iterator_t
 *       Description: replaces every element in the range [t_first, t_last)
 *                    for which t_unary_op output true with new element.
 *
 * ----------------------------------------------------------------------------
 */
extern output_iterator_t _algo_replace_copy_if(
    input_iterator_t t_first, input_iterator_t t_last,
    output_iterator_t t_result, unary_function_t t_unary_op, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _algo_replace_copy_if_varg
 *        Parameters: in) t_first: forward_iterator_t
 *                        the first iterator.
 *                    in) t_last: forward_iterator_t
 *                        the last iterator.
 *                    in) t_result: output_iterator_t
 *                        the output iterator
 *                    in) t_unary_op: unary_function_t
 *                        the unary operator.
 *                    in) val_elemlist: va_list
 *                        value list.
 *           Returns: output_iterator_t
 *       Description: replaces every element in the range [t_first, t_last)
 *                    for which t_unary_op output true with new element.
 *
 * ----------------------------------------------------------------------------
 */
extern output_iterator_t _algo_replace_copy_if_varg(
    input_iterator_t t_first, input_iterator_t t_last,
    output_iterator_t t_result, unary_function_t t_unary_op,
    va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _algo_lower_bound
 *        Parameters: in) t_first: forward_iterator_t
 *                        the first iterator.
 *                    in) t_last: forward_iterator_t
 *                        the last iterator.
 *                    in) ...
 *                        value list.
 *           Returns: forward_iterator_t
 *       Description: attempts to find the element value in an order range
 *                    [t_first, t_last).
 *
 * ----------------------------------------------------------------------------
 */
extern forward_iterator_t _algo_lower_bound(
    forward_iterator_t t_first, forward_iterator_t t_last, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _algo_lower_bound_if
 *        Parameters: in) t_first: forward_iterator_t
 *                        the first iterator.
 *                    in) t_last: forward_iterator_t
 *                        the last iterator.
 *                    in) t_binary_op: binary_function_t
 *                        the binary operator.
 *                    in) ...
 *                        value list.
 *           Returns: forward_iterator_t
 *       Description: attempts to find the element value in an order range
 *                    [t_first, t_last).
 *
 * ----------------------------------------------------------------------------
 */
extern forward_iterator_t _algo_lower_bound_if(
    forward_iterator_t t_first, forward_iterator_t t_last,
    binary_function_t t_binary_op, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _algo_lower_bound_if_varg
 *        Parameters: in) t_first: forward_iterator_t
 *                        the first iterator.
 *                    in) t_last: forward_iterator_t
 *                        the last iterator.
 *                    in) t_binary_op: binary_function_t
 *                        the binary operator.
 *                    in) val_elemlist: va_list
 *                        value list.
 *           Returns: forward_iterator_t
 *       Description: attempts to find the element value in an order range
 *                    [t_first, t_last).
 *
 * ----------------------------------------------------------------------------
 */
extern forward_iterator_t _algo_lower_bound_if_varg(
    forward_iterator_t t_first, forward_iterator_t t_last,
    binary_function_t t_binary_op, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _algo_upper_bound
 *        Parameters: in) t_first: forward_iterator_t
 *                        the first iterator.
 *                    in) t_last: forward_iterator_t
 *                        the last iterator.
 *                    in) ...
 *                        value list.
 *           Returns: forward_iterator_t
 *       Description: attempts to find the element value in an order range
 *                    [t_first, t_last).
 *
 * ----------------------------------------------------------------------------
 */
extern forward_iterator_t _algo_upper_bound(
    forward_iterator_t t_first, forward_iterator_t t_last, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _algo_upper_bound_if
 *        Parameters: in) t_first: forward_iterator_t
 *                        the first iterator.
 *                    in) t_last: forward_iterator_t
 *                        the last iterator.
 *                    in) t_binary_op: binary_function_t
 *                        the binary operator.
 *                    in) ...
 *                        value list.
 *           Returns: forward_iterator_t
 *       Description: attempts to find the element value in an order range
 *                    [t_first, t_last).
 *
 * ----------------------------------------------------------------------------
 */
extern forward_iterator_t _algo_upper_bound_if(
    forward_iterator_t t_first, forward_iterator_t t_last,
    binary_function_t t_binary_op, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _algo_upper_bound_if_varg
 *        Parameters: in) t_first: forward_iterator_t
 *                        the first iterator.
 *                    in) t_last: forward_iterator_t
 *                        the last iterator.
 *                    in) t_binary_op: binary_function_t
 *                        the binary operator.
 *                    in) val_elemlist: va_list
 *                        value list.
 *           Returns: forward_iterator_t
 *       Description: attempts to find the element value in an order range
 *                    [t_first, t_last).
 *
 * ----------------------------------------------------------------------------
 */
extern forward_iterator_t _algo_upper_bound_if_varg(
    forward_iterator_t t_first, forward_iterator_t t_last,
    binary_function_t t_binary_op, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _algo_equal_range
 *        Parameters: in) t_first: forward_iterator_t
 *                        the first iterator.
 *                    in) t_last: forward_iterator_t
 *                        the last iterator.
 *                    in) ...
 *                        value list.
 *           Returns: pair_t<forward_iterator_t, forward_iterator_t>
 *       Description: attempts to find the element value in an order range
 *                    [t_first, t_last).
 *
 * ----------------------------------------------------------------------------
 */
extern pair_t _algo_equal_range(
    forward_iterator_t t_first, forward_iterator_t t_last, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _algo_equal_range_if
 *        Parameters: in) t_first: forward_iterator_t
 *                        the first iterator.
 *                    in) t_last: forward_iterator_t
 *                        the last iterator.
 *                    in) t_binary_op: binary_function_t
 *                        the binary operator.
 *                    in) ...
 *                        value list.
 *           Returns: pair_t<forward_iterator_t, forward_iterator_t>
 *       Description: attempts to find the element value in an order range
 *                    [t_first, t_last).
 *
 * ----------------------------------------------------------------------------
 */
extern pair_t _algo_equal_range_if(
    forward_iterator_t t_first, forward_iterator_t t_last,
    binary_function_t t_binary_op, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _algo_equal_range_if_varg
 *        Parameters: in) t_first: forward_iterator_t
 *                        the first iterator.
 *                    in) t_last: forward_iterator_t
 *                        the last iterator.
 *                    in) t_binary_op: binary_function_t
 *                        the binary operator.
 *                    in) val_elemlist: va_list
 *                        value list.
 *           Returns: pair_t<forward_iterator_t, forward_iterator_t>
 *       Description: attempts to find the element value in an order range
 *                    [t_first, t_last).
 *
 * ----------------------------------------------------------------------------
 */
extern pair_t _algo_equal_range_if_varg(
    forward_iterator_t t_first, forward_iterator_t t_last,
    binary_function_t t_binary_op, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _algo_binary_search
 *        Parameters: in) t_first: forward_iterator_t
 *                        the first iterator.
 *                    in) t_last: forward_iterator_t
 *                        the last iterator.
 *                    in) ...
 *                        value list.
 *           Returns: bool_t
 *       Description: attempts to find the element value in an order range
 *                    [t_first, t_last).
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t _algo_binary_search(
    forward_iterator_t t_first, forward_iterator_t t_last, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _algo_binary_search_if
 *        Parameters: in) t_first: forward_iterator_t
 *                        the first iterator.
 *                    in) t_last: forward_iterator_t
 *                        the last iterator.
 *                    in) t_binary_op: binary_function_t
 *                        the binary operator.
 *                    in) ...
 *                        value list.
 *           Returns: bool_t
 *       Description: attempts to find the element value in an order range
 *                    [t_first, t_last).
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t _algo_binary_search_if(
    forward_iterator_t t_first, forward_iterator_t t_last,
    binary_function_t t_binary_op, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _algo_binary_search_if_varg
 *        Parameters: in) t_first: forward_iterator_t
 *                        the first iterator.
 *                    in) t_last: forward_iterator_t
 *                        the last iterator.
 *                    in) t_binary_op: binary_function_t
 *                        the binary operator.
 *                    in) val_elemlist: va_list
 *                        value list.
 *           Returns: bool_t
 *       Description: attempts to find the element value in an order range
 *                    [t_first, t_last).
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t _algo_binary_search_if_varg(
    forward_iterator_t t_first, forward_iterator_t t_last,
    binary_function_t t_binary_op, va_list val_elemlist);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_ALGO_PRIVATE_H */
/** eof **/

