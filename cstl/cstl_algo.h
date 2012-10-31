/*
 *  The interface of algorithm.
 *  Copyright (C)  2008 - 2012  Wangbo
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

#ifndef _CSTL_ALGO_H_
#define _CSTL_ALGO_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/* lower bound */
#define algo_lower_bound(t_first, t_last, elem)\
    _algo_lower_bound((t_first), (t_last), (elem))
#define algo_lower_bound_if(t_first, t_last, elem, t_binary_op)\
    _algo_lower_bound_if((t_first), (t_last), (t_binary_op), (elem))
/* upper bound */
#define algo_upper_bound(t_first, t_last, elem)\
    _algo_upper_bound((t_first), (t_last), (elem))
#define algo_upper_bound_if(t_first, t_last, elem, t_binary_op)\
    _algo_upper_bound_if((t_first), (t_last), (t_binary_op), (elem))
/* equal range */
#define algo_equal_range(t_first, t_last, elem)\
    _algo_equal_range((t_first), (t_last), (elem))
#define algo_equal_range_if(t_first, t_last, elem, t_binary_op)\
    _algo_equal_range_if((t_first), (t_last), (t_binary_op), (elem))
/* binary search */
#define algo_binary_search(t_first, t_last, elem)\
    _algo_binary_search((t_first), (t_last), (elem))
#define algo_binary_search_if(t_first, t_last, elem, t_binary_op)\
    _algo_binary_search_if((t_first), (t_last), (t_binary_op), (elem))

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * set algorithm.
 */
extern output_iterator_t algo_set_union(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2,
    output_iterator_t t_result);
extern output_iterator_t algo_set_union_if(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2,
    output_iterator_t t_result,
    binary_function_t t_binary_op);
extern output_iterator_t algo_set_intersection(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2,
    output_iterator_t t_result);
extern output_iterator_t algo_set_intersection_if(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2,
    output_iterator_t t_result,
    binary_function_t t_binary_op);
extern output_iterator_t algo_set_difference(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2,
    output_iterator_t t_result);
extern output_iterator_t algo_set_difference_if(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2,
    output_iterator_t t_result,
    binary_function_t t_binary_op);
extern output_iterator_t algo_set_symmetric_difference(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2,
    output_iterator_t t_result);
extern output_iterator_t algo_set_symmetric_difference_if(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2,
    output_iterator_t t_result,
    binary_function_t t_binary_op);

/*
 * includes algorithm.
 */
extern bool_t algo_includes(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2);
extern bool_t algo_includes_if(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2,
    binary_function_t t_binary_op);

/*
 * max element and min element algorithm.
 */
extern forward_iterator_t algo_max_element(
    forward_iterator_t t_first, forward_iterator_t t_last);
extern forward_iterator_t algo_max_element_if(
    forward_iterator_t t_first, forward_iterator_t t_last,
    binary_function_t t_binary_op);
extern forward_iterator_t algo_min_element(
    forward_iterator_t t_first, forward_iterator_t t_last);
extern forward_iterator_t algo_min_element_if(
    forward_iterator_t t_first, forward_iterator_t t_last,
    binary_function_t t_binary_op);

/*
 * merge algorithm.
 */
extern output_iterator_t algo_merge(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2,
    output_iterator_t t_result);
extern output_iterator_t algo_merge_if(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2,
    output_iterator_t t_result, binary_function_t t_binary_op);

/*
 * permutation algorithm.
 */
extern bool_t algo_next_permutation(
    bidirectional_iterator_t t_first, bidirectional_iterator_t t_last);
extern bool_t algo_next_permutation_if(
    bidirectional_iterator_t t_first, bidirectional_iterator_t t_last,
    binary_function_t t_binary_op);
extern bool_t algo_prev_permutation(
    bidirectional_iterator_t t_first, bidirectional_iterator_t t_last);
extern bool_t algo_prev_permutation_if(
    bidirectional_iterator_t t_first, bidirectional_iterator_t t_last,
    binary_function_t t_binary_op);

/*
 * partial sort algorithm.
 */
/*
extern void algo_partial_sort(
    random_access_iterator_t t_first,
    random_access_iterator_t t_middle,
    random_access_iterator_t t_last);
extern void algo_partial_sort_if(
    random_access_iterator_t t_first,
    random_access_iterator_t t_middle,
    random_access_iterator_t t_last,
    binary_function_t t_binary_op);
    */
extern random_access_iterator_t algo_partial_sort_copy(
    input_iterator_t t_first1, input_iterator_t t_last1,
    random_access_iterator_t t_first2, random_access_iterator_t t_last2);
extern random_access_iterator_t algo_partial_sort_copy_if(
    input_iterator_t t_first1, input_iterator_t t_last1,
    random_access_iterator_t t_first2, random_access_iterator_t t_last2,
    binary_function_t t_binary_op);

/*
 * sort algorithm.
 */
extern void algo_sort(
    random_access_iterator_t t_first, random_access_iterator_t t_last);
extern void algo_sort_if(
    random_access_iterator_t t_first, random_access_iterator_t t_last,
    binary_function_t t_binary_op);

/*
 * inplace merge algorithm.
 */
extern void algo_inplace_merge(
    bidirectional_iterator_t t_first,
    bidirectional_iterator_t t_middle,
    bidirectional_iterator_t t_last);
extern void algo_inplace_merge_if(
    bidirectional_iterator_t t_first,
    bidirectional_iterator_t t_middle,
    bidirectional_iterator_t t_last,
    binary_function_t t_binary_op);

/*
 * nth element algorithm.
 */
extern void algo_nth_element(
    random_access_iterator_t t_first,
    random_access_iterator_t t_nth,
    random_access_iterator_t t_last);
extern void algo_nth_element_if(
    random_access_iterator_t t_first,
    random_access_iterator_t t_nth,
    random_access_iterator_t t_last,
    binary_function_t t_binary_op);

/*
 * Is sorted algorithm.
 */
/*
extern bool_t algo_is_sorted(
    forward_iterator_t t_first, forward_iterator_t t_last);
extern bool_t algo_is_sorted_if(
    forward_iterator_t t_first, forward_iterator_t t_last,
    binary_function_t t_binary_op);
    */

/*
 * Stable sort algorithm.
 */
extern void algo_stable_sort(
    random_access_iterator_t t_first, random_access_iterator_t t_last);
extern void algo_stable_sort_if(
    random_access_iterator_t t_first, random_access_iterator_t t_last,
    binary_function_t t_binary_op);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_ALGO_H_ */
/** eof **/

