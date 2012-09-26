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
/* count */
#define algo_count(t_first, t_last, elem)\
    _algo_count((t_first), (t_last), (elem))
    /*
#define algo_find(t_first, t_last, elem)\
    _algo_find((t_first), (t_last), (elem))
    */
/* search */
#define algo_search_n(t_first, t_last, t_count, elem)\
    _algo_search_n((t_first), (t_last), (t_count), (elem))
#define algo_search_n_if(t_first, t_last, t_count, elem, t_binary_op)\
    _algo_search_n_if((t_first), (t_last), (t_count), (t_binary_op), (elem))
/* remove */
#define algo_remove_copy(t_first, t_last, t_result, elem)\
    _algo_remove_copy((t_first), (t_last), (t_result), (elem))
#define algo_remove(t_first, t_last, elem)\
    _algo_remove((t_first), (t_last), (elem))
/* replace */
#define algo_replace(t_first, t_last, old_elem, new_elem)\
    do\
    {\
        iterator_t t_begin = (t_first);\
        iterator_t t_end = (t_last);\
        assert(_iterator_valid_range(t_begin, t_end, _FORWARD_ITERATOR));\
        t_begin = algo_find(t_begin, t_end, (old_elem));\
        while(!iterator_equal(t_begin, t_end))\
        {\
            _algo_replace_once(t_begin, (new_elem));\
            t_begin = iterator_next(t_begin);\
            t_begin = algo_find(t_begin, t_end, (old_elem));\
        }\
    }while(false)
#define algo_replace_copy(t_first, t_last, t_result, old_elem, new_elem)\
    do\
    {\
        iterator_t t_begin = (t_first);\
        iterator_t t_end = (t_last);\
        iterator_t t_copy = (t_result);\
        iterator_t t_tmp;\
        assert(_iterator_valid_range(t_begin, t_end, _INPUT_ITERATOR));\
        assert(_iterator_limit_type(t_copy, _OUTPUT_ITERATOR));\
        for(; !iterator_equal(t_begin, t_end); t_begin = iterator_next(t_begin))\
        {\
            t_tmp = algo_find(t_begin, t_end, (old_elem));\
            if(iterator_equal(t_tmp, t_begin))\
            {\
                _algo_replace_once(t_copy, (new_elem));\
            }\
            else\
            {\
                /* delete element */\
                iterator_set_value(t_copy, iterator_get_pointer(t_begin));\
            }\
            t_copy = iterator_next(t_copy);\
        }\
    }while(false)
#define algo_replace_if(t_first, t_last, t_unary_op, elem)\
    _algo_replace_if((t_first), (t_last), (t_unary_op), (elem))
#define algo_replace_copy_if(t_first, t_last, t_result, t_unary_op, elem)\
    _algo_replace_copy_if((t_first), (t_last), (t_result), (t_unary_op), (elem))
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
 * adjacent find algorithm.
 */
extern forward_iterator_t algo_adjacent_find(
    forward_iterator_t t_first, forward_iterator_t t_last);
extern forward_iterator_t algo_adjacent_find_if(
    forward_iterator_t t_first, forward_iterator_t t_last,
    binary_function_t t_binary_op);

/*
 * count algorithm.
 */
extern size_t algo_count_if(
    input_iterator_t t_first, input_iterator_t t_last,
    unary_function_t t_unary_op);

/*
 * find and find first of algorithm.
 */
/*
extern input_iterator_t algo_find_if(
    input_iterator_t t_first, input_iterator_t t_last,
    unary_function_t t_unary_op);
    */
extern input_iterator_t algo_find_first_of(
    input_iterator_t t_first1, input_iterator_t t_last1,
    forward_iterator_t t_first2, forward_iterator_t t_last2);
extern input_iterator_t algo_find_first_of_if(
    input_iterator_t t_first1, input_iterator_t t_last1,
    forward_iterator_t t_first2, forward_iterator_t t_last2,
    binary_function_t t_binary_op);

/*
 * for each algorithm.
 */
/*
extern void algo_for_each(
    input_iterator_t t_first, input_iterator_t t_last,
    unary_function_t t_unary_op);
	*/

/*
 * search algorithm.
 */
extern forward_iterator_t algo_search(
    forward_iterator_t t_first1, forward_iterator_t t_last1,
    forward_iterator_t t_first2, forward_iterator_t t_last2);
extern forward_iterator_t algo_search_if(
    forward_iterator_t t_first1, forward_iterator_t t_last1,
    forward_iterator_t t_first2, forward_iterator_t t_last2,
    binary_function_t t_binary_op);

/*
 * search end and find end algorithm.
 */
extern forward_iterator_t algo_search_end(
    forward_iterator_t t_first1, forward_iterator_t t_last1,
    forward_iterator_t t_first2, forward_iterator_t t_last2);
extern forward_iterator_t algo_search_end_if(
    forward_iterator_t t_first1, forward_iterator_t t_last1,
    forward_iterator_t t_first2, forward_iterator_t t_last2,
    binary_function_t t_binary_op);
extern forward_iterator_t algo_find_end(
    forward_iterator_t t_first1, forward_iterator_t t_last1,
    forward_iterator_t t_first2, forward_iterator_t t_last2);
extern forward_iterator_t algo_find_end_if(
    forward_iterator_t t_first1, forward_iterator_t t_last1,
    forward_iterator_t t_first2, forward_iterator_t t_last2,
    binary_function_t t_binary_op);

/*
 * generate algorithm.
 */
extern void algo_generate(
    forward_iterator_t t_first, forward_iterator_t t_last,
    unary_function_t t_unary_op);
extern output_iterator_t algo_generate_n(
    output_iterator_t t_first, size_t t_count, unary_function_t t_unary_op);

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
 * partition algorithm.
 */
extern forward_iterator_t algo_partition(
    forward_iterator_t t_first, forward_iterator_t t_last,
    unary_function_t t_unary_op);
extern forward_iterator_t algo_stable_partition(
    forward_iterator_t t_first, forward_iterator_t t_last,
    unary_function_t t_unary_op);

/*
 * remove algorithm.
 */
extern forward_iterator_t algo_remove_if(
    forward_iterator_t t_first, forward_iterator_t t_last, unary_function_t t_unary_op);
extern output_iterator_t algo_remove_copy_if(
    input_iterator_t t_first, input_iterator_t t_last,
    output_iterator_t t_result, unary_function_t t_unary_op);

/*
 * reverse algorithm.
 */
extern void algo_reverse(
    bidirectional_iterator_t t_first, bidirectional_iterator_t t_last);
extern output_iterator_t algo_reverse_copy(
    bidirectional_iterator_t t_first, bidirectional_iterator_t t_last,
    output_iterator_t t_result);

/*
 * rotate algorithm.
 */
extern forward_iterator_t algo_rotate(
    forward_iterator_t t_first,
    forward_iterator_t t_middle,
    forward_iterator_t t_last);
extern output_iterator_t algo_rotate_copy(
    forward_iterator_t t_first,
    forward_iterator_t t_middle,
    forward_iterator_t t_last,
    output_iterator_t t_result);

/*
 * swap range algorithm.
 */
extern forward_iterator_t algo_swap_ranges(
    forward_iterator_t t_first1, forward_iterator_t t_last1,
    forward_iterator_t t_first2);

/*
 * transform algorithm.
 */
extern output_iterator_t algo_transform(
    input_iterator_t t_first, input_iterator_t t_last,
    output_iterator_t t_result, unary_function_t t_unary_op);
extern output_iterator_t algo_transform_binary(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, output_iterator_t t_result,
    binary_function_t t_binary_op);

/*
 * unique algorithm.
 */
extern forward_iterator_t algo_unique(
    forward_iterator_t t_first, forward_iterator_t t_last);
extern forward_iterator_t algo_unique_if(
    forward_iterator_t t_first, forward_iterator_t t_last,
    binary_function_t t_binary_op);
extern output_iterator_t algo_unique_copy(
    input_iterator_t t_first, input_iterator_t t_last,
    output_iterator_t t_result);
extern output_iterator_t algo_unique_copy_if(
    input_iterator_t t_first, input_iterator_t t_last,
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
 * random algorithm.
 */
extern void algo_random_shuffle(
    random_access_iterator_t t_first, random_access_iterator_t t_last);
extern void algo_random_shuffle_if(
    random_access_iterator_t t_first, random_access_iterator_t t_last,
    unary_function_t t_unary_op);
extern random_access_iterator_t algo_random_sample(
    input_iterator_t t_first1, input_iterator_t t_last1,
    random_access_iterator_t t_first2, random_access_iterator_t t_last2);
extern random_access_iterator_t algo_random_sample_if(
    input_iterator_t t_first1, input_iterator_t t_last1,
    random_access_iterator_t t_first2, random_access_iterator_t t_last2,
    unary_function_t t_unary_op);
extern output_iterator_t algo_random_sample_n(
    input_iterator_t t_first, input_iterator_t t_last,
    output_iterator_t t_result, size_t t_count);
extern output_iterator_t algo_random_sample_n_if(
    input_iterator_t t_first, input_iterator_t t_last,
    output_iterator_t t_result, size_t t_count, unary_function_t t_unary_op);

/*
 * partial sort algorithm.
 */
extern void algo_partial_sort(
    random_access_iterator_t t_first,
    random_access_iterator_t t_middle,
    random_access_iterator_t t_last);
extern void algo_partial_sort_if(
    random_access_iterator_t t_first,
    random_access_iterator_t t_middle,
    random_access_iterator_t t_last,
    binary_function_t t_binary_op);
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
extern bool_t algo_is_sorted(
    forward_iterator_t t_first, forward_iterator_t t_last);
extern bool_t algo_is_sorted_if(
    forward_iterator_t t_first, forward_iterator_t t_last,
    binary_function_t t_binary_op);

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

