/*
 *  The interface of base algorithm.
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

#ifndef _CSTL_ALGOBASE_H
#define _CSTL_ALGOBASE_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
#define algo_fill(t_first, t_last, elem)\
    _algo_fill((t_first), (t_last), (elem))
#define algo_fill_n(t_first, t_fillsize, elem)\
    _algo_fill_n((t_first), (t_fillsize), (elem))

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_equal
 *        Parameters: in) t_first1: input_iterator_t
 *                        the first iterator.
 *                    in) t_last1: input_iterator_t
 *                        the last iterator.
 *                    in) t_first2: input_iterator_t
 *                        the second iterator.
 *           Returns: bool_t
 *       Description: compare all elements of two range element-by-element.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t algo_equal(
    input_iterator_t t_first1,
    input_iterator_t t_last1,
    input_iterator_t t_first2);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_equal_if
 *        Parameters: in) t_first1: input_iterator_t
 *                        the first iterator.
 *                    in) t_last1: input_iterator_t
 *                        the last iterator.
 *                    in) t_first2: input_iterator_t
 *                        the second iterator.
 *                    in) t_binary_op: binary_function_t
 *                        the compare function.
 *           Returns: bool_t
 *       Description: compare all elements of two range element-by-element.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t algo_equal_if(
    input_iterator_t t_first1,
    input_iterator_t t_last1,
    input_iterator_t t_first2,
    binary_function_t t_binary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_swap
 *        Parameters: in) t_first: forward_iterator_t
 *                            the first iterator.
 *                    in) t_second: forward_iterator_t
 *                            the second iterator.
 *           Returns: void
 *       Description: swap the value of two iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern void algo_swap(forward_iterator_t t_first, forward_iterator_t t_second);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_iter_swap
 *        Parameters: in) t_first: forward_iterator_t
 *                            the first iterator.
 *                    in) t_second: forward_iterator_t
 *                            the second iterator.
 *           Returns: void
 *       Description: swap the value of two iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern void algo_iter_swap(forward_iterator_t t_first, forward_iterator_t t_second);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_lexicographical_compare
 *        Parameters: in) t_first1: input_iterator_t
 *                        the first iterator.
 *                    in) t_last1: input_iterator_t
 *                        the last iterator.
 *                    in) t_first2: input_iterator_t
 *                        the second iterator.
 *                    in) t_last2: input_iterator_t
 *                        the last iterator.
 *           Returns: bool_t
 *       Description: return true if the range of elements [t_first1, t_last1)
 *                    is lexicographically less then the range of elements
 *                    [t_first2, t_last2).
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t algo_lexicographical_compare(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_lexicographical_compare_if
 *        Parameters: in) t_first1: input_iterator_t
 *                        the first iterator.
 *                    in) t_last1: input_iterator_t
 *                        the last iterator.
 *                    in) t_first2: input_iterator_t
 *                        the second iterator.
 *                    in) t_last2: input_iterator_t
 *                        the last iterator.
 *                    in) t_binary_op: binary_function_t
 *                        the compare function.
 *           Returns: bool_t
 *       Description: return true if the range of elements [t_first1, t_last1)
 *                    is lexicographically less then the range of elements
 *                    [t_first2, t_last2).
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t algo_lexicographical_compare_if(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2,
    binary_function_t t_binary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_lexicographical_compare_3way
 *        Parameters: in) t_first1: input_iterator_t
 *                        the first iterator.
 *                    in) t_last1: input_iterator_t
 *                        the last iterator.
 *                    in) t_first2: input_iterator_t
 *                        the second iterator.
 *                    in) t_last2: input_iterator_t
 *                        the last iterator.
 *           Returns: int
 *       Description: return negative number if the range of elements 
 *                    [t_first1, t_last1) is lexicographically less then the 
 *                    range of elements [t_first2, t_last2), return positive
 *                    number if the range of elements [t_first1, t_last1) is
 *                    lexicographically greate then the range of elements
 *                    [t_first2, t_last2), and return 0 if the two is equal.
 *
 * ----------------------------------------------------------------------------
 */
extern int algo_lexicographical_compare_3way(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_lexicographical_compare_3way_if
 *        Parameters: in) t_first1: input_iterator_t
 *                        the first iterator.
 *                    in) t_last1: input_iterator_t
 *                        the last iterator.
 *                    in) t_first2: input_iterator_t
 *                        the second iterator.
 *                    in) t_last2: input_iterator_t
 *                        the last iterator.
 *                    in) t_binary_op: binary_function_t
 *                        the compare function.
 *           Returns: int
 *       Description: return negative number if the range of elements 
 *                    [t_first1, t_last1) is lexicographically less then the 
 *                    range of elements [t_first2, t_last2), return positive
 *                    number if the range of elements [t_first1, t_last1) is
 *                    lexicographically greate then the range of elements
 *                    [t_first2, t_last2), and return 0 if the two is equal.
 *
 * ----------------------------------------------------------------------------
 */
extern int algo_lexicographical_compare_3way_if(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2,
    binary_function_t t_binary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_max
 *        Parameters: in) t_first: input_iterator_t
 *                        the first iterator.
 *                    in) t_second: input_iterator_t
 *                        the last iterator.
 *           Returns: input_iterator_t
 *       Description: return the greater of the two arguments. it return the
 *                    first argument if neither is greater then the other.
 *
 * ----------------------------------------------------------------------------
 */
extern input_iterator_t algo_max(
    input_iterator_t t_first, input_iterator_t t_second);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_max_if
 *        Parameters: in) t_first: input_iterator_t
 *                        the first iterator.
 *                    in) t_second: input_iterator_t
 *                        the last iterator.
 *                    in) t_binary_op: binary_function_t
 *                        the compare function.
 *           Returns: input_iterator_t
 *       Description: return the greater of the two arguments. it return the
 *                    first argument if neither is greater then the other.
 *
 * ----------------------------------------------------------------------------
 */
extern input_iterator_t algo_max_if(
    input_iterator_t t_first,
    input_iterator_t t_last,
    binary_function_t t_binary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_min
 *        Parameters: in) t_first: input_iterator_t
 *                        the first iterator.
 *                    in) t_second: input_iterator_t
 *                        the last iterator.
 *           Returns: input_iterator_t
 *       Description: return the less of the two arguments. it return the
 *                    first argument if neither is greater then the other.
 *
 * ----------------------------------------------------------------------------
 */
extern input_iterator_t algo_min(
    input_iterator_t t_first, input_iterator_t t_second);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_min_if
 *        Parameters: in) t_first: input_iterator_t
 *                        the first iterator.
 *                    in) t_second: input_iterator_t
 *                        the last iterator.
 *                    in) t_binary_op: binary_function_t
 *                        the compare function.
 *           Returns: input_iterator_t
 *       Description: return the less of the two arguments. it return the
 *                    first argument if neither is greater then the other.
 *
 * ----------------------------------------------------------------------------
 */
extern input_iterator_t algo_min_if(
    input_iterator_t t_first,
    input_iterator_t t_last,
    binary_function_t t_binary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_mismatch
 *        Parameters: in) t_first1: input_iterator_t
 *                        the first iterator.
 *                    in) t_last1: input_iterator_t
 *                        the last iterator.
 *                    in) t_first2: input_iterator_t
 *                        the second iterator.
 *           Returns: pair_t(input_iterator_t, input_iterator_t)
 *       Description: find the first position where the two range is differ.
 *              note: you must be destroy the result pair.
 *
 * ----------------------------------------------------------------------------
 */
extern pair_t algo_mismatch(
    input_iterator_t t_first1,
    input_iterator_t t_last1,
    input_iterator_t t_first2);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_mismatch_if
 *        Parameters: in) t_first1: input_iterator_t
 *                        the first iterator.
 *                    in) t_last1: input_iterator_t
 *                        the last iterator.
 *                    in) t_first2: input_iterator_t
 *                        the second iterator.
 *                    in) t_binary_op: binary_function_t
 *                        the compare function.
 *           Returns: pair_t(input_iterator_t, input_iterator_t)
 *       Description: find the first position where the two range is differ.
 *              note: you must be destroy the resutl pair.
 *
 * ----------------------------------------------------------------------------
 */
extern pair_t algo_mismatch_if(
    input_iterator_t t_first1,
    input_iterator_t t_last1,
    input_iterator_t t_first2,
    binary_function_t t_binary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_copy
 *        Parameters: in) t_first: input_iterator_t
 *                        the first iterator.
 *                    in) t_last: input_iterator_t
 *                        the last iterator.
 *                    in) t_result: output_iterator_t
 *                        the output iterator.
 *           Returns: output_iterator_t
 *       Description: copy elements from the range [t_first, t_last) to the
 *                    range [t_result, t_result + (t_last - t_first)).
 *
 * ----------------------------------------------------------------------------
 */
extern output_iterator_t algo_copy(
    input_iterator_t t_first,
    input_iterator_t t_last,
    output_iterator_t t_result);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_copy_n
 *        Parameters: in) t_first: input_iterator_t
 *                        the first iterator.
 *                    in) t_count: size_t
 *                        the copy count.
 *                    in) t_result: output_iterator_t
 *                        the output iterator.
 *           Returns: output_iterator_t
 *       Description: copy elements from the range [t_first, t_first + t_count)
 *                    to the range [t_result, t_result + t_count).
 *
 * ----------------------------------------------------------------------------
 */
extern output_iterator_t algo_copy_n(
    input_iterator_t t_first, size_t t_count, output_iterator_t t_result);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_copy_backward
 *        Parameters: in) t_first: bidirectional_iterator_t
 *                        the first iterator.
 *                    in) t_last: bidirectional_iterator_t
 *                        the last iterator.
 *                    in) t_result: bidirectional_iterator_t
 *                        the output iterator.
 *           Returns: bidirectional_iterator_t
 *       Description: copy elements from the range [t_first, t_last) to the
 *                    range [t_result, t_result + (t_last - t_first)) backward.
 *
 * ----------------------------------------------------------------------------
 */
extern bidirectional_iterator_t algo_copy_backward(
    bidirectional_iterator_t t_first,
    bidirectional_iterator_t t_last,
    bidirectional_iterator_t t_result);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_ALGOBASE_H */
/** eof **/

