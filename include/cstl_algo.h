/*
 *  The interface of algorithm.
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

#ifndef _CSTL_ALGO_H
#define _CSTL_ALGO_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/* count */
#define algo_count(t_first, t_last, elem)\
    _algo_count((t_first), (t_last), (elem))
/* find */
#define algo_find(t_first, t_last, elem)\
    _algo_find((t_first), (t_last), (elem))
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
        assert(_tools_valid_iterator_range(t_begin, t_end, _FORWARD_ITERATOR));\
        t_begin = algo_find(t_begin, t_end, (old_elem));\
        while(!iterator_equal(&t_begin, t_end))\
        {\
            _algo_replace_once(t_begin, (new_elem));\
            iterator_next(&t_begin);\
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
        assert(_tools_valid_iterator_range(t_begin, t_end, _INPUT_ITERATOR));\
        assert(_iterator_limit_type(t_copy, _OUTPUT_ITERATOR));\
        assert(_tools_same_elem_type(t_begin, t_copy));\
        for(; !iterator_equal(&t_begin, t_end); iterator_next(&t_begin))\
        {\
            t_tmp = algo_find(t_begin, t_end, (old_elem));\
            if(iterator_equal(&t_tmp, t_begin))\
            {\
                _algo_replace_once(t_copy, (new_elem));\
            }\
            else\
            {\
                /* delete element */\
                iterator_set_value(&t_copy, iterator_get_pointer(&t_begin));\
            }\
            iterator_next(&t_copy);\
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
/* set algorithm */
/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_set_union
 *        Parameters: in) t_first1: input_iterator_t
 *                        the first iterator.
 *                    in) t_last1: input_iterator_t
 *                        the last iterator.
 *                    in) t_first2: input_iterator_t
 *                        the second iterator.
 *                    in) t_last2: input_iterator_t
 *                        the last iterator.
 *                    in) t_result: output_iterator_t
 *                        the result iterator.
 *           Returns: output_iterator_t
 *       Description: construct the sortd range that is the union of the range
 *                    [t_first1, t_last1), and the sortd range [t_first2, t_last2).
 *                    the return value is the end of the output range.
 *
 * ----------------------------------------------------------------------------
 */
extern output_iterator_t algo_set_union(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2,
    output_iterator_t t_result);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_set_union_if
 *        Parameters: in) t_first1: input_iterator_t
 *                        the first iterator.
 *                    in) t_last1: input_iterator_t
 *                        the last iterator.
 *                    in) t_first2: input_iterator_t
 *                        the second iterator.
 *                    in) t_last2: input_iterator_t
 *                        the last iterator.
 *                    in) t_result: output_iterator_t
 *                        the result iterator.
 *                    in) t_binary_op: binary_function_t
 *                        the compare function.
 *           Returns: output_iterator_t
 *       Description: construct the sortd range that is the union of the range
 *                    [t_first1, t_last1), and the sortd range [t_first2, t_last2).
 *                    the return value is the end of the output range.
 *
 * ----------------------------------------------------------------------------
 */
extern output_iterator_t algo_set_union_if(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2,
    output_iterator_t t_result,
    binary_function_t t_binary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_set_intersection
 *        Parameters: in) t_first1: input_iterator_t
 *                        the first iterator.
 *                    in) t_last1: input_iterator_t
 *                        the last iterator.
 *                    in) t_first2: input_iterator_t
 *                        the second iterator.
 *                    in) t_last2: input_iterator_t
 *                        the last iterator.
 *                    in) t_result: output_iterator_t
 *                        the result iterator.
 *           Returns: output_iterator_t
 *       Description: construct the sortd range that is the intersection of the 
 *                    range [t_first1, t_last1), and the sortd range 
 *                    [t_first2, t_last2). the return value is the end of the 
 *                    output range.
 *
 * ----------------------------------------------------------------------------
 */
extern output_iterator_t algo_set_intersection(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2,
    output_iterator_t t_result);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_set_intersection_if
 *        Parameters: in) t_first1: input_iterator_t
 *                        the first iterator.
 *                    in) t_last1: input_iterator_t
 *                        the last iterator.
 *                    in) t_first2: input_iterator_t
 *                        the second iterator.
 *                    in) t_last2: input_iterator_t
 *                        the last iterator.
 *                    in) t_result: output_iterator_t
 *                        the result iterator.
 *                    in) t_binary_op: binary_function_t
 *                        the compare function.
 *           Returns: output_iterator_t
 *       Description: construct the sortd range that is the intersection of the 
 *                    range [t_first1, t_last1), and the sortd range 
 *                    [t_first2, t_last2). the return value is the end of the 
 *                    output range.
 *
 * ----------------------------------------------------------------------------
 */
extern output_iterator_t algo_set_intersection_if(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2,
    output_iterator_t t_result,
    binary_function_t t_binary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_set_difference
 *        Parameters: in) t_first1: input_iterator_t
 *                        the first iterator.
 *                    in) t_last1: input_iterator_t
 *                        the last iterator.
 *                    in) t_first2: input_iterator_t
 *                        the second iterator.
 *                    in) t_last2: input_iterator_t
 *                        the last iterator.
 *                    in) t_result: output_iterator_t
 *                        the result iterator.
 *           Returns: output_iterator_t
 *       Description: construct the sortd range that is the difference of the 
 *                    range [t_first1, t_last1), and the sortd range 
 *                    [t_first2, t_last2). the return value is the end of the 
 *                    output range.
 *
 * ----------------------------------------------------------------------------
 */
extern output_iterator_t algo_set_difference(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2,
    output_iterator_t t_result);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_set_difference_if
 *        Parameters: in) t_first1: input_iterator_t
 *                        the first iterator.
 *                    in) t_last1: input_iterator_t
 *                        the last iterator.
 *                    in) t_first2: input_iterator_t
 *                        the second iterator.
 *                    in) t_last2: input_iterator_t
 *                        the last iterator.
 *                    in) t_result: output_iterator_t
 *                        the result iterator.
 *                    in) t_binary_op: binary_function_t
 *                        the compare function.
 *           Returns: output_iterator_t
 *       Description: construct the sortd range that is the difference of the 
 *                    range [t_first1, t_last1), and the sortd range 
 *                    [t_first2, t_last2). the return value is the end of the 
 *                    output range.
 *
 * ----------------------------------------------------------------------------
 */
extern output_iterator_t algo_set_difference_if(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2,
    output_iterator_t t_result,
    binary_function_t t_binary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_set_symmetric_difference
 *        Parameters: in) t_first1: input_iterator_t
 *                        the first iterator.
 *                    in) t_last1: input_iterator_t
 *                        the last iterator.
 *                    in) t_first2: input_iterator_t
 *                        the second iterator.
 *                    in) t_last2: input_iterator_t
 *                        the last iterator.
 *                    in) t_result: output_iterator_t
 *                        the result iterator.
 *           Returns: output_iterator_t
 *       Description: construct the sortd range that is the symmetric difference 
 *                    of the range [t_first1, t_last1), and the sortd range 
 *                    [t_first2, t_last2). the return value is the end of the 
 *                    output range.
 *
 * ----------------------------------------------------------------------------
 */
extern output_iterator_t algo_set_symmetric_difference(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2,
    output_iterator_t t_result);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_set_symmetric_difference_if
 *        Parameters: in) t_first1: input_iterator_t
 *                        the first iterator.
 *                    in) t_last1: input_iterator_t
 *                        the last iterator.
 *                    in) t_first2: input_iterator_t
 *                        the second iterator.
 *                    in) t_last2: input_iterator_t
 *                        the last iterator.
 *                    in) t_result: output_iterator_t
 *                        the result iterator.
 *                    in) t_binary_op: binary_function_t
 *                        the compare function.
 *           Returns: output_iterator_t
 *       Description: construct the sortd range that is the symmetric difference 
 *                    of the range [t_first1, t_last1), and the sortd range 
 *                    [t_first2, t_last2). the return value is the end of the 
 *                    output range.
 *
 * ----------------------------------------------------------------------------
 */
extern output_iterator_t algo_set_symmetric_difference_if(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2,
    output_iterator_t t_result,
    binary_function_t t_binary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_adjacent_find
 *        Parameters: in) t_first: forward_iterator_t
 *                        the first iterator.
 *                    in) t_last: forward_iterator_t
 *                        the last iterator.
 *           Returns: forward_iterator_t
 *       Description: if *i == *(i+1) it return the first iterator. it return
 *                    t_last if no such iterator exists.
 *
 * ----------------------------------------------------------------------------
 */
extern forward_iterator_t algo_adjacent_find(
    forward_iterator_t t_first, forward_iterator_t t_last);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_adjacent_find_if
 *        Parameters: in) t_first: forward_iterator_t
 *                        the first iterator.
 *                    in) t_last: forward_iterator_t
 *                        the last iterator.
 *                    in) t_binary_op: binary_function_t
 *                        the compare function.
 *           Returns: forward_iterator_t
 *       Description: if *i == *(i+1) it return the first iterator. it return
 *                    t_last if no such iterator exists.
 *
 * ----------------------------------------------------------------------------
 */
extern forward_iterator_t algo_adjacent_find_if(
    forward_iterator_t t_first, forward_iterator_t t_last,
    binary_function_t t_binary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_count_if
 *        Parameters: in) t_first: input_iterator_t
 *                        the first iterator.
 *                    in) t_last: input_iterator_t
 *                        the last iterator.
 *                    in) t_unary_op: unary_function_t
 *                        unary function.
 *           Returns: size_t
 *       Description: finds the number of elements in range [t_first, t_last)
 *                    that satisfy the predicate t_unary_op.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t algo_count_if(
    input_iterator_t t_first, input_iterator_t t_last,
    unary_function_t t_unary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_find_if
 *        Parameters: in) t_first: input_iterator_t
 *                        the first iterator.
 *                    in) t_last: input_iterator_t
 *                        the last iterator.
 *                    in) t_unary_op: unary_function_t
 *                        unary function.
 *           Returns: input_iterator_t
 *       Description: return the first iterator i in range [t_first, t_last),
 *                    such that *i == value. return t_last if no such iterator
 *                    exists.
 *
 * ----------------------------------------------------------------------------
 */
extern input_iterator_t algo_find_if(
    input_iterator_t t_first, input_iterator_t t_last,
    unary_function_t t_unary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_find_first_of
 *        Parameters: in) t_first1: input_iterator_t
 *                        the first iterator.
 *                    in) t_last1: input_iterator_t
 *                        the last iterator.
 *                    in) t_first2: forward_iterator_t
 *                        the second iterator.
 *                    in) t_last2: forward_iterator_t
 *                        the last iterator.
 *           Returns: input_iterator_t
 *       Description: search for the first occurrance in the range 
 *                    [t_first1, t_last1) of any of elements in range 
 *                    [t_first2, t_last2).
 *
 * ----------------------------------------------------------------------------
 */
extern input_iterator_t algo_find_first_of(
    input_iterator_t t_first1, input_iterator_t t_last1,
    forward_iterator_t t_first2, forward_iterator_t t_last2);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_find_first_of_if
 *        Parameters: in) t_first1: input_iterator_t
 *                        the first iterator.
 *                    in) t_last1: input_iterator_t
 *                        the last iterator.
 *                    in) t_first2: forward_iterator_t
 *                        the second iterator.
 *                    in) t_last2: forward_iterator_t
 *                        the last iterator.
 *                    in) t_binary_op: binary_function_t
 *                        binary function.
 *           Returns: input_iterator_t
 *       Description: search for the first occurrance in the range 
 *                    [t_first1, t_last1) of any of elements in range 
 *                    [t_first2, t_last2).
 *
 * ----------------------------------------------------------------------------
 */
extern input_iterator_t algo_find_first_of_if(
    input_iterator_t t_first1, input_iterator_t t_last1,
    forward_iterator_t t_first2, forward_iterator_t t_last2,
    binary_function_t t_binary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_for_each
 *        Parameters: in) t_first: input_iterator_t
 *                        the first iterator.
 *                    in) t_last: input_iterator_t
 *                        the last iterator.
 *                    in) t_unary_op: unary_function_t
 *                        unary function.
 *           Returns: input_iterator_t
 *       Description: applies the unary function t_unary_op to each elements
 *                    in range [t_first, t_last).
 *
 * ----------------------------------------------------------------------------
 */
extern void algo_for_each(
    input_iterator_t t_first, input_iterator_t t_last,
    unary_function_t t_unary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_search
 *        Parameters: in) t_first1: forward_iterator_t
 *                        the first iterator.
 *                    in) t_last1: forward_iterator_t
 *                        the last iterator.
 *                    in) t_first2: forward_iterator_t
 *                        the second iterator.
 *                    in) t_last2: forward_iterator_t
 *                        the last iterator.
 *           Returns: forward_iterator_t
 *       Description: find subsequence with the range [t_first1, t_last1) that
 *                    is identical to [t_first2, t_last2) when compare element
 *                    by element.
 *
 * ----------------------------------------------------------------------------
 */
extern forward_iterator_t algo_search(
    forward_iterator_t t_first1, forward_iterator_t t_last1,
    forward_iterator_t t_first2, forward_iterator_t t_last2);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_search_if
 *        Parameters: in) t_first1: forward_iterator_t
 *                        the first iterator.
 *                    in) t_last1: forward_iterator_t
 *                        the last iterator.
 *                    in) t_first2: forward_iterator_t
 *                        the second iterator.
 *                    in) t_last2: forward_iterator_t
 *                        the last iterator.
 *                    in) t_binary_op: binary_function_t
 *                        binary function.
 *           Returns: forward_iterator_t
 *       Description: find subsequence with the range [t_first1, t_last1) that
 *                    is identical to [t_first2, t_last2) when compare element
 *                    by element.
 *
 * ----------------------------------------------------------------------------
 */
extern forward_iterator_t algo_search_if(
    forward_iterator_t t_first1, forward_iterator_t t_last1,
    forward_iterator_t t_first2, forward_iterator_t t_last2,
    binary_function_t t_binary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_search_end
 *        Parameters: in) t_first1: forward_iterator_t
 *                        the first iterator.
 *                    in) t_last1: forward_iterator_t
 *                        the last iterator.
 *                    in) t_first2: forward_iterator_t
 *                        the second iterator.
 *                    in) t_last2: forward_iterator_t
 *                        the last iterator.
 *           Returns: forward_iterator_t
 *       Description: find subsequence with the range [t_first1, t_last1) that
 *                    is identical to [t_first2, t_last2) when compare element
 *                    by element.
 *
 * ----------------------------------------------------------------------------
 */
extern forward_iterator_t algo_search_end(
    forward_iterator_t t_first1, forward_iterator_t t_last1,
    forward_iterator_t t_first2, forward_iterator_t t_last2);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_search_end_if
 *        Parameters: in) t_first1: forward_iterator_t
 *                        the first iterator.
 *                    in) t_last1: forward_iterator_t
 *                        the last iterator.
 *                    in) t_first2: forward_iterator_t
 *                        the second iterator.
 *                    in) t_last2: forward_iterator_t
 *                        the last iterator.
 *                    in) t_binary_op: binary_function_t
 *                        binary function.
 *           Returns: forward_iterator_t
 *       Description: find subsequence with the range [t_first1, t_last1) that
 *                    is identical to [t_first2, t_last2) when compare element
 *                    by element.
 *
 * ----------------------------------------------------------------------------
 */
extern forward_iterator_t algo_search_end_if(
    forward_iterator_t t_first1, forward_iterator_t t_last1,
    forward_iterator_t t_first2, forward_iterator_t t_last2,
    binary_function_t t_binary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_find_end
 *        Parameters: in) t_first1: forward_iterator_t
 *                        the first iterator.
 *                    in) t_last1: forward_iterator_t
 *                        the last iterator.
 *                    in) t_first2: forward_iterator_t
 *                        the second iterator.
 *                    in) t_last2: forward_iterator_t
 *                        the last iterator.
 *           Returns: forward_iterator_t
 *       Description: this is misnamed, it is equal to algo_search_end
 *
 * ----------------------------------------------------------------------------
 */
extern forward_iterator_t algo_find_end(
    forward_iterator_t t_first1, forward_iterator_t t_last1,
    forward_iterator_t t_first2, forward_iterator_t t_last2);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_find_end_if
 *        Parameters: in) t_first1: forward_iterator_t
 *                        the first iterator.
 *                    in) t_last1: forward_iterator_t
 *                        the last iterator.
 *                    in) t_first2: forward_iterator_t
 *                        the second iterator.
 *                    in) t_last2: forward_iterator_t
 *                        the last iterator.
 *                    in) t_binary_op: binary_function_t
 *                        binary function.
 *           Returns: forward_iterator_t
 *       Description: this is misnamed, it is equal to algo_search_end_if
 *
 * ----------------------------------------------------------------------------
 */
extern forward_iterator_t algo_find_end_if(
    forward_iterator_t t_first1, forward_iterator_t t_last1,
    forward_iterator_t t_first2, forward_iterator_t t_last2,
    binary_function_t t_binary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_generate
 *        Parameters: in) t_first: forward_iterator_t
 *                        the first iterator.
 *                    in) t_last: forward_iterator_t
 *                        the last iterator.
 *                    in) t_unary_op: unary_function_t
 *                        unary function.
 *           Returns: void
 *       Description: assign all elements invoke generate function.
 *
 * ----------------------------------------------------------------------------
 */
extern void algo_generate(
    forward_iterator_t t_first, forward_iterator_t t_last,
    unary_function_t t_unary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_generate_n
 *        Parameters: in) t_first: output_iterator_t
 *                        the first iterator.
 *                    in) t_count: size_t
 *                        element count.
 *                    in) t_unary_op: unary_function_t
 *                        unary function.
 *           Returns: output_iterator_t
 *       Description: assign n elements invoke generate function.
 *
 * ----------------------------------------------------------------------------
 */
extern output_iterator_t algo_generate_n(
    output_iterator_t t_first, size_t t_count, unary_function_t t_unary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_includes
 *        Parameters: in) t_first1: input_iterator_t
 *                        the first iterator.
 *                    in) t_last1: input_iterator_t
 *                        the last iterator.
 *                    in) t_first2: input_iterator_t
 *                        the second iterator.
 *                    in) t_last2: input_iterator_t
 *                        the last iterator.
 *           Returns: bool_t
 *       Description: test the first sorted range [t_first1, t_last1) includes
 *                    the second sorted range [t_first2, t_last2).
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t algo_includes(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_includes_if
 *        Parameters: in) t_first1: input_iterator_t
 *                        the first iterator.
 *                    in) t_last1: input_iterator_t
 *                        the last iterator.
 *                    in) t_first2: input_iterator_t
 *                        the second iterator.
 *                    in) t_last2: input_iterator_t
 *                        the last iterator.
 *                    in) t_binary_op: binary_function_t
 *                        binary function.
 *           Returns: bool_t
 *       Description: test the first sorted range [t_first1, t_last1) includes
 *                    the second sorted range [t_first2, t_last2).
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t algo_includes_if(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2,
    binary_function_t t_binary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_max_element
 *        Parameters: in) t_first: forward_iterator_t
 *                        the first iterator.
 *                    in) t_last: forward_iterator_t
 *                        the last iterator.
 *           Returns: forward_iterator_t
 *       Description: find and return the largest element in the range
 *                    [t_first, t_last).
 *
 * ----------------------------------------------------------------------------
 */
extern forward_iterator_t algo_max_element(
    forward_iterator_t t_first, forward_iterator_t t_last);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_max_element_if
 *        Parameters: in) t_first: forward_iterator_t
 *                        the first iterator.
 *                    in) t_last: forward_iterator_t
 *                        the last iterator.
 *                    in) t_binary_op: binary_function_t
 *                        binary function
 *           Returns: forward_iterator_t
 *       Description: find and return the largest element in the range
 *                    [t_first, t_last).
 *
 * ----------------------------------------------------------------------------
 */
extern forward_iterator_t algo_max_element_if(
    forward_iterator_t t_first, forward_iterator_t t_last,
    binary_function_t t_binary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_min_element
 *        Parameters: in) t_first: forward_iterator_t
 *                        the first iterator.
 *                    in) t_last: forward_iterator_t
 *                        the last iterator.
 *           Returns: forward_iterator_t
 *       Description: find and return the smallest element in the range
 *                    [t_first, t_last).
 *
 * ----------------------------------------------------------------------------
 */
extern forward_iterator_t algo_min_element(
    forward_iterator_t t_first, forward_iterator_t t_last);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_min_element_if
 *        Parameters: in) t_first: forward_iterator_t
 *                        the first iterator.
 *                    in) t_last: forward_iterator_t
 *                        the last iterator.
 *                    in) t_binary_op: binary_function_t
 *                        binary function
 *           Returns: forward_iterator_t
 *       Description: find and return the smallest element in the range
 *                    [t_first, t_last).
 *
 * ----------------------------------------------------------------------------
 */
extern forward_iterator_t algo_min_element_if(
    forward_iterator_t t_first, forward_iterator_t t_last,
    binary_function_t t_binary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_merge
 *        Parameters: in) t_first1: input_iterator_t
 *                        the first iterator.
 *                    in) t_last1: input_iterator_t
 *                        the last iterator.
 *                    in) t_first2: input_iterator_t
 *                        the second iterator.
 *                    in) t_last2: input_iterator_t
 *                        the last iterator.
 *                    in) t_result: output_iterator_t
 *                        result iterator.
 *           Returns: output_iterator_t
 *       Description: combine the two sorted range [t_first1, t_last1) and
 *                    [t_first2, t_last2) to a single sorted range.
 *
 * ----------------------------------------------------------------------------
 */
extern output_iterator_t algo_merge(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2,
    output_iterator_t t_result);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_merge_if
 *        Parameters: in) t_first1: input_iterator_t
 *                        the first iterator.
 *                    in) t_last1: input_iterator_t
 *                        the last iterator.
 *                    in) t_first2: input_iterator_t
 *                        the second iterator.
 *                    in) t_last2: input_iterator_t
 *                        the last iterator.
 *                    in) t_result: output_iterator_t
 *                        result iterator.
 *                    in) t_binary_op: binary_function_t
 *                        binary function.
 *           Returns: output_iterator_t
 *       Description: combine the two sorted range [t_first1, t_last1) and
 *                    [t_first2, t_last2) to a single sorted range.
 *
 * ----------------------------------------------------------------------------
 */
extern output_iterator_t algo_merge_if(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2,
    output_iterator_t t_result, binary_function_t t_binary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_partition
 *        Parameters: in) t_first: forward_iterator_t
 *                        the first iterator.
 *                    in) t_last: forward_iterator_t
 *                        the last iterator.
 *                    in) t_unary_op: unary_function_t
 *                        unary function
 *           Returns: forward_iterator_t
 *       Description: reorder the elements in the range [t_first, t_last)
 *                    base on the t_unary_op.
 *
 * ----------------------------------------------------------------------------
 */
extern forward_iterator_t algo_partition(
    forward_iterator_t t_first, forward_iterator_t t_last,
    unary_function_t t_unary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_stable_partition
 *        Parameters: in) t_first: forward_iterator_t
 *                        the first iterator.
 *                    in) t_last: forward_iterator_t
 *                        the last iterator.
 *                    in) t_unary_op: unary_function_t
 *                        unary function
 *           Returns: forward_iterator_t
 *       Description: reorder the elements in the range [t_first, t_last)
 *                    base on the t_unary_op.
 *
 * ----------------------------------------------------------------------------
 */
extern forward_iterator_t algo_stable_partition(
    forward_iterator_t t_first, forward_iterator_t t_last,
    unary_function_t t_unary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_remove_if
 *        Parameters: in) t_first: forward_iterator_t
 *                        the first iterator.
 *                    in) t_last: forward_iterator_t
 *                        the last iterator.
 *                    in) t_unary_op: unary_function_t
 *                        unary function.
 *           Returns: forward_iterator_t
 *       Description: copies elements that are not equal to value from the 
 *                    range [t_first, t_last) to a range begining at t_result.
 *
 * ----------------------------------------------------------------------------
 */
extern forward_iterator_t algo_remove_if(
    forward_iterator_t t_first, forward_iterator_t t_last, unary_function_t t_unary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_remove_copy_if
 *        Parameters: in) t_first: input_iterator_t
 *                        the first iterator.
 *                    in) t_last: input_iterator_t
 *                        the last iterator.
 *                    in) t_result: output_iterator_t
 *                        the output iterator.
 *                    in) t_unary_op: unary_function_t
 *                        unary function.
 *           Returns: output_iterator_t
 *       Description: copies elements that are not equal to value from the 
 *                    range [t_first, t_last) to a range begining at t_result.
 *
 * ----------------------------------------------------------------------------
 */
extern output_iterator_t algo_remove_copy_if(
    input_iterator_t t_first, input_iterator_t t_last,
    output_iterator_t t_result, unary_function_t t_unary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_reverse
 *        Parameters: in) t_first: bidirectional_iterator_t
 *                        the first iterator.
 *                    in) t_last: bidirectional_iterator_t
 *                        the last iterator.
 *           Returns: void
 *       Description: reverse the range [t_first, t_last).
 *
 * ----------------------------------------------------------------------------
 */
extern void algo_reverse(
    bidirectional_iterator_t t_first, bidirectional_iterator_t t_last);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_reverse_copy
 *        Parameters: in) t_first: bidirectional_iterator_t
 *                        the first iterator.
 *                    in) t_last: bidirectional_iterator_t
 *                        the last iterator.
 *                    in) t_result: output_iterator_t
 *                        the output iterator.
 *           Returns: output_iterator_t
 *       Description: reverse the range [t_first, t_last).
 *
 * ----------------------------------------------------------------------------
 */
extern output_iterator_t algo_reverse_copy(
    bidirectional_iterator_t t_first, bidirectional_iterator_t t_last,
    output_iterator_t t_result);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_rotate
 *        Parameters: in) t_first: forward_iterator_t
 *                        the first iterator.
 *                    in) t_middle: forward_iterator_t
 *                        the middle iterator.
 *                    in) t_last: forward_iterator_t
 *                        the last iterator.
 *           Returns: void
 *       Description: rotates the elements in the range [t_first, t_last).
 *
 * ----------------------------------------------------------------------------
 */
extern forward_iterator_t algo_rotate(
    forward_iterator_t t_first,
    forward_iterator_t t_middle,
    forward_iterator_t t_last);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_rotate_copy
 *        Parameters: in) t_first: forward_iterator_t
 *                        the first iterator.
 *                    in) t_middle: forward_iterator_t
 *                        the middle iterator.
 *                    in) t_last: forward_iterator_t
 *                        the last iterator.
 *                    in) t_result: output_iterator_t
 *                        the output iterator.
 *           Returns: output_iterator_t
 *       Description: rotates the elements in the range [t_first, t_last).
 *
 * ----------------------------------------------------------------------------
 */
extern output_iterator_t algo_rotate_copy(
    forward_iterator_t t_first,
    forward_iterator_t t_middle,
    forward_iterator_t t_last,
    output_iterator_t t_result);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_swap_ranges
 *        Parameters: in) t_first1: forward_iterator_t
 *                        the first iterator.
 *                    in) t_last1: forward_iterator_t
 *                        the last iterator.
 *                    in) t_first2: forward_iterator_t
 *                        the first iterator.
 *           Returns: forward_iterator_t
 *       Description: swap each element of range [t_first1, t_last1) and
 *                    range [t_first2, t_first2 + (t_last1 - t_first1)).
 *
 * ----------------------------------------------------------------------------
 */
extern forward_iterator_t algo_swap_ranges(
    forward_iterator_t t_first1, forward_iterator_t t_last1,
    forward_iterator_t t_first2);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_transform
 *        Parameters: in) t_first: input_iterator_t
 *                        the first iterator.
 *                    in) t_last: input_iterator_t
 *                        the last iterator.
 *                    in) t_result: output_iterator_t
 *                        the output iterator.
 *                    in) t_unary_op: unary_function_t
 *                        unary function.
 *           Returns: output_iterator_t
 *       Description: perform an operation on objects.
 *
 * ----------------------------------------------------------------------------
 */
extern output_iterator_t algo_transform(
    input_iterator_t t_first, input_iterator_t t_last,
    output_iterator_t t_result, unary_function_t t_unary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_transform_binary
 *        Parameters: in) t_first1: input_iterator_t
 *                        the first iterator.
 *                    in) t_last1: input_iterator_t
 *                        the last iterator.
 *                    in) t_first2: input_iterator_t
 *                        the first iterator of second range.
 *                    in) t_result: output_iterator_t
 *                        the output iterator.
 *                    in) t_unary_op: unary_function_t
 *                        unary function.
 *           Returns: output_iterator_t
 *       Description: perform an operation on objects of two range.
 *
 * ----------------------------------------------------------------------------
 */
extern output_iterator_t algo_transform_binary(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, output_iterator_t t_result,
    binary_function_t t_binary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_unique
 *        Parameters: in) t_first: forward_iterator_t
 *                        the first iterator.
 *                    in) t_last: forward_iterator_t
 *                        the last iterator.
 *           Returns: forward_iterator_t
 *       Description: every a time consecutive group of duplicate elements 
 *                    appear in the range [t_first, t_last), the algorithm
 *                    remove all but the first element.
 *
 * ----------------------------------------------------------------------------
 */
extern forward_iterator_t algo_unique(
    forward_iterator_t t_first, forward_iterator_t t_last);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_unique_if
 *        Parameters: in) t_first: forward_iterator_t
 *                        the first iterator.
 *                    in) t_last: forward_iterator_t
 *                        the last iterator.
 *                    in) t_binary_op: binary_function_t
 *                        binary function.
 *           Returns: forward_iterator_t
 *       Description: every a time consecutive group of duplicate elements 
 *                    appear in the range [t_first, t_last), the algorithm
 *                    remove all but the first element.
 *
 * ----------------------------------------------------------------------------
 */
extern forward_iterator_t algo_unique_if(
    forward_iterator_t t_first, forward_iterator_t t_last,
    binary_function_t t_binary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_unique_copy
 *        Parameters: in) t_first: input_iterator_t
 *                        the first iterator.
 *                    in) t_last: input_iterator_t
 *                        the last iterator.
 *                    in) t_result: output_iterator_t
 *                        the output iterator.
 *           Returns: output_iterator_t
 *       Description: every a time consecutive group of duplicate elements 
 *                    appear in the range [t_first, t_last), the algorithm
 *                    remove all but the first element.
 *
 * ----------------------------------------------------------------------------
 */
extern output_iterator_t algo_unique_copy(
    input_iterator_t t_first, input_iterator_t t_last,
    output_iterator_t t_result);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_unique_copy_if
 *        Parameters: in) t_first: input_iterator_t
 *                        the first iterator.
 *                    in) t_last: input_iterator_t
 *                        the last iterator.
 *                    in) t_result: output_iterator_t
 *                        the output iterator.
 *                    in) t_binary_op: binary_function_t
 *                        binary function.
 *           Returns: output_iterator_t
 *       Description: every a time consecutive group of duplicate elements 
 *                    appear in the range [t_first, t_last), the algorithm
 *                    remove all but the first element.
 *
 * ----------------------------------------------------------------------------
 */
extern output_iterator_t algo_unique_copy_if(
    input_iterator_t t_first, input_iterator_t t_last,
    output_iterator_t t_result, binary_function_t t_binary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_next_permutation
 *        Parameters: in) t_first: bidirectional_iterator_t
 *                        the first iterator.
 *                    in) t_last: bidirectional_iterator_t
 *                        the last iterator.
 *           Returns: bool_t
 *       Description: transform the range of elements [t_first, t_last) into 
 *                    lexicograpically next greater permutation of elements.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t algo_next_permutation(
    bidirectional_iterator_t t_first, bidirectional_iterator_t t_last);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_next_permutation_if
 *        Parameters: in) t_first: bidirectional_iterator_t
 *                        the first iterator.
 *                    in) t_last: bidirectional_iterator_t
 *                        the last iterator.
 *                    in) t_binary_op: binary_function_t
 *                        binary function.
 *           Returns: bool_t
 *       Description: transform the range of elements [t_first, t_last) into 
 *                    lexicograpically next greater permutation of elements.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t algo_next_permutation_if(
    bidirectional_iterator_t t_first, bidirectional_iterator_t t_last,
    binary_function_t t_binary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_prev_permutation
 *        Parameters: in) t_first: bidirectional_iterator_t
 *                        the first iterator.
 *                    in) t_last: bidirectional_iterator_t
 *                        the last iterator.
 *           Returns: bool_t
 *       Description: transform the range of elements [t_first, t_last) into 
 *                    lexicograpically next smaller permutation of elements.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t algo_prev_permutation(
    bidirectional_iterator_t t_first, bidirectional_iterator_t t_last);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_prev_permutation_if
 *        Parameters: in) t_first: bidirectional_iterator_t
 *                        the first iterator.
 *                    in) t_last: bidirectional_iterator_t
 *                        the last iterator.
 *                    in) t_binary_op: binary_function_t
 *                        binary function.
 *           Returns: bool_t
 *       Description: transform the range of elements [t_first, t_last) into 
 *                    lexicograpically next smaller permutation of elements.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t algo_prev_permutation_if(
    bidirectional_iterator_t t_first, bidirectional_iterator_t t_last,
    binary_function_t t_binary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_random_shuffle
 *        Parameters: in) t_first: random_access_iterator_t
 *                        the first iterator.
 *                    in) t_last: random_access_iterator_t
 *                        the last iterator.
 *           Returns: void
 *       Description: redomly rearrangs the elements in the range
 *                    [t_first, t_last).
 *
 * ----------------------------------------------------------------------------
 */
extern void algo_random_shuffle(
    random_access_iterator_t t_first, random_access_iterator_t t_last);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_random_shuffle_if
 *        Parameters: in) t_first: random_access_iterator_t
 *                        the first iterator.
 *                    in) t_last: random_access_iterator_t
 *                        the last iterator.
 *                    in) t_unary_op: unary_function_t
 *                        unary function.
 *           Returns: void
 *       Description: redomly rearrangs the elements in the range
 *                    [t_first, t_last).
 *
 * ----------------------------------------------------------------------------
 */
extern void algo_random_shuffle_if(
    random_access_iterator_t t_first, random_access_iterator_t t_last,
    unary_function_t t_unary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_random_sample
 *        Parameters: in) t_first1: input_iterator_t
 *                        the first iterator.
 *                    in) t_last1: input_iterator_t
 *                        the last iterator.
 *                    in) t_first2: random_access_iterator_t
 *                        the first iterator.
 *                    in) t_last2: random_access_iterator_t
 *                        the last iterator.
 *           Returns: random_access_iterator_t
 *       Description: redomly copy the elements from the range [t_first1, t_last1)
 *                    into the range [t_first2, t_last2).
 *
 * ----------------------------------------------------------------------------
 */
extern random_access_iterator_t algo_random_sample(
    input_iterator_t t_first1, input_iterator_t t_last1,
    random_access_iterator_t t_first2, random_access_iterator_t t_last2);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_random_sample_if
 *        Parameters: in) t_first1: input_iterator_t
 *                        the first iterator.
 *                    in) t_last1: input_iterator_t
 *                        the last iterator.
 *                    in) t_first2: random_access_iterator_t
 *                        the first iterator.
 *                    in) t_last2: random_access_iterator_t
 *                        the last iterator.
 *                    in) t_unary_op: unary_function_t
 *                        unary function.
 *           Returns: random_access_iterator_t
 *       Description: redomly copy the elements from the range [t_first1, t_last1)
 *                    into the range [t_first2, t_last2).
 *
 * ----------------------------------------------------------------------------
 */
extern random_access_iterator_t algo_random_sample_if(
    input_iterator_t t_first1, input_iterator_t t_last1,
    random_access_iterator_t t_first2, random_access_iterator_t t_last2,
    unary_function_t t_unary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_random_sample_n
 *        Parameters: in) t_first: input_iterator_t
 *                        the first iterator.
 *                    in) t_last: input_iterator_t
 *                        the last iterator.
 *                    in) t_result: output_iterator_t
 *                        the output iterator.
 *                    in) t_count: size_t
 *                        element count.
 *           Returns: output_iterator_t
 *       Description: redomly copy the elements from the range [t_first, t_last)
 *                    into the range [t_result, t_result + t_count).
 *
 * ----------------------------------------------------------------------------
 */
extern output_iterator_t algo_random_sample_n(
    input_iterator_t t_first, input_iterator_t t_last,
    output_iterator_t t_result, size_t t_count);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_random_sample_n_if
 *        Parameters: in) t_first: input_iterator_t
 *                        the first iterator.
 *                    in) t_last: input_iterator_t
 *                        the last iterator.
 *                    in) t_result: output_iterator_t
 *                        the output iterator.
 *                    in) t_count: size_t
 *                        element count.
 *                    in) t_unary_op: unary_function_t
 *                        unary function.
 *           Returns: output_iterator_t
 *       Description: redomly copy the elements from the range [t_first, t_last)
 *                    into the range [t_result, t_result + t_count).
 *
 * ----------------------------------------------------------------------------
 */
extern output_iterator_t algo_random_sample_n_if(
    input_iterator_t t_first, input_iterator_t t_last,
    output_iterator_t t_result, size_t t_count, unary_function_t t_unary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_partial_sort
 *        Parameters: in) t_first: random_access_iterator_t
 *                        the first iterator.
 *                    in) t_middle: random_access_iterator_t
 *                        the middle iterator.
 *                    in) t_last: random_access_iterator_t
 *                        the last iterator.
 *           Returns: void
 *       Description: rearranges the elements in the range [t_first, t_last)
 *                    so that they are partially in ascending order.
 *
 * ----------------------------------------------------------------------------
 */
extern void algo_partial_sort(
    random_access_iterator_t t_first,
    random_access_iterator_t t_middle,
    random_access_iterator_t t_last);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_partial_sort_if
 *        Parameters: in) t_first: random_access_iterator_t
 *                        the first iterator.
 *                    in) t_middle: random_access_iterator_t
 *                        the middle iterator.
 *                    in) t_last: random_access_iterator_t
 *                        the last iterator.
 *                    in) t_binary_op: binary_function_t
 *                        binary function.
 *           Returns: void
 *       Description: rearranges the elements in the range [t_first, t_last)
 *                    so that they are partially in ascending order.
 *
 * ----------------------------------------------------------------------------
 */
extern void algo_partial_sort_if(
    random_access_iterator_t t_first,
    random_access_iterator_t t_middle,
    random_access_iterator_t t_last,
    binary_function_t t_binary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_partial_sort_copy
 *        Parameters: in) t_first1: input_iterator_t
 *                        the first iterator.
 *                    in) t_last1: input_iterator_t
 *                        the last iterator.
 *                    in) t_first2: random_access_iterator_t
 *                        the first iterator.
 *                    in) t_last2: random_access_iterator_t
 *                        the last iterator.
 *           Returns: random_access_iterator_t
 *       Description: copies the smallest N elements from range [t_first1, t_last1).
 *                    to the range [t_first2, t_first2 + N). where N is smaller
 *                    of t_last2 - t_first2 and t_last1 - t_first1, the element
 *                    in [t_first2, t_first2 + N) is in ascending order.
 *
 * ----------------------------------------------------------------------------
 */
extern random_access_iterator_t algo_partial_sort_copy(
    input_iterator_t t_first1, input_iterator_t t_last1,
    random_access_iterator_t t_first2, random_access_iterator_t t_last2);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_partial_sort_copy_if
 *        Parameters: in) t_first1: input_iterator_t
 *                        the first iterator.
 *                    in) t_last1: input_iterator_t
 *                        the last iterator.
 *                    in) t_first2: random_access_iterator_t
 *                        the first iterator.
 *                    in) t_last2: random_access_iterator_t
 *                        the last iterator.
 *                    in) t_binary_op: binary_function_t
 *                        binary function.
 *           Returns: random_access_iterator_t
 *       Description: copies the smallest N elements from range [t_first1, t_last1).
 *                    to the range [t_first2, t_first2 + N). where N is smaller
 *                    of t_last2 - t_first2 and t_last1 - t_first1, the element
 *                    in [t_first2, t_first2 + N) is in ascending order.
 *
 * ----------------------------------------------------------------------------
 */
extern random_access_iterator_t algo_partial_sort_copy_if(
    input_iterator_t t_first1, input_iterator_t t_last1,
    random_access_iterator_t t_first2, random_access_iterator_t t_last2,
    binary_function_t t_binary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_sort
 *        Parameters: in) t_first: random_access_iterator_t
 *                        the first iterator.
 *                    in) t_last: random_access_iterator_t
 *                        the last iterator.
 *           Returns: void
 *       Description: sorts the elements in the range [t_first, t_last) into
 *                    ascending order.
 *
 * ----------------------------------------------------------------------------
 */
extern void algo_sort(
    random_access_iterator_t t_first, random_access_iterator_t t_last);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_sort_if
 *        Parameters: in) t_first: random_access_iterator_t
 *                        the first iterator.
 *                    in) t_last: random_access_iterator_t
 *                        the last iterator.
 *                    in) t_binary_op: binary_function_t
 *                        binary function.
 *           Returns: void
 *       Description: sorts the elements in the range [t_first, t_last) into
 *                    ascending order.
 *
 * ----------------------------------------------------------------------------
 */
extern void algo_sort_if(
    random_access_iterator_t t_first, random_access_iterator_t t_last,
    binary_function_t t_binary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_inplace_merge
 *        Parameters: in) t_first: bidirectional_iterator_t
 *                        the first iterator.
 *                    in) t_middle: bidirectional_iterator_t
 *                        the middle iterator.
 *                    in) t_last: bidirectional_iterator_t
 *                        the last iterator.
 *           Returns: void
 *       Description: combines two consecutive sorted range [t_first, t_middle) 
 *                    and [t_middle, t_last) into a single sorted range
 *                    [t_first, t_last).
 *
 * ----------------------------------------------------------------------------
 */
extern void algo_inplace_merge(
    bidirectional_iterator_t t_first,
    bidirectional_iterator_t t_middle,
    bidirectional_iterator_t t_last);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_inplace_merge_if
 *        Parameters: in) t_first: bidirectional_iterator_t
 *                        the first iterator.
 *                    in) t_middle: bidirectional_iterator_t
 *                        the middle iterator.
 *                    in) t_last: bidirectional_iterator_t
 *                        the last iterator.
 *                    in) t_binary_op: binary_function_t
 *                        binary function.
 *           Returns: void
 *       Description: combines two consecutive sorted range [t_first, t_middle) 
 *                    and [t_middle, t_last) into a single sorted range
 *                    [t_first, t_last).
 *
 * ----------------------------------------------------------------------------
 */
extern void algo_inplace_merge_if(
    bidirectional_iterator_t t_first,
    bidirectional_iterator_t t_middle,
    bidirectional_iterator_t t_last,
    binary_function_t t_binary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_nth_element
 *        Parameters: in) t_first: random_access_iterator_t
 *                        the first iterator.
 *                    in) t_nth: random_access_iterator_t
 *                        the middle iterator.
 *                    in) t_last: random_access_iterator_t
 *                        the last iterator.
 *           Returns: void
 *       Description: it arranges the range [t_first, t_last) such that the 
 *                    element pointed by the pointer t_nth is the same of the
 *                    element that would be in that position if the entire 
 *                    range [t_first, t_last) had been sorted.
 *
 * ----------------------------------------------------------------------------
 */
extern void algo_nth_element(
    random_access_iterator_t t_first,
    random_access_iterator_t t_nth,
    random_access_iterator_t t_last);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_nth_element_if
 *        Parameters: in) t_first: random_access_iterator_t
 *                        the first iterator.
 *                    in) t_nth: random_access_iterator_t
 *                        the middle iterator.
 *                    in) t_last: random_access_iterator_t
 *                        the last iterator.
 *                    in) t_binary_op: binary_function_t
 *                        binary function.
 *           Returns: void
 *       Description: it arranges the range [t_first, t_last) such that the 
 *                    element pointed by the pointer t_nth is the same of the
 *                    element that would be in that position if the entire 
 *                    range [t_first, t_last) had been sorted.
 *
 * ----------------------------------------------------------------------------
 */
extern void algo_nth_element_if(
    random_access_iterator_t t_first,
    random_access_iterator_t t_nth,
    random_access_iterator_t t_last,
    binary_function_t t_binary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_is_sorted
 *        Parameters: in) t_first: forward_iterator_t
 *                        the first iterator.
 *                    in) t_last: forward_iterator_t
 *                        the last iterator.
 *           Returns: bool_t
 *       Description: return true if the range [t_first, t_last) is sorted in
 *                    ascending order, and false otherwise.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t algo_is_sorted(
    forward_iterator_t t_first, forward_iterator_t t_last);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_is_sorted_if
 *        Parameters: in) t_first: forward_iterator_t
 *                        the first iterator.
 *                    in) t_last: forward_iterator_t
 *                        the last iterator.
 *                    in) t_binary_op: binary_function_t
 *                        binary function.
 *           Returns: bool_t
 *       Description: return true if the range [t_first, t_last) is sorted in
 *                    ascending order, and false otherwise.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t algo_is_sorted_if(
    forward_iterator_t t_first, forward_iterator_t t_last,
    binary_function_t t_binary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_stable_sort
 *        Parameters: in) t_first: random_access_iterator_t
 *                        the first iterator.
 *                    in) t_last: random_access_iterator_t
 *                        the last iterator.
 *           Returns: void
 *       Description: is sort the elements in the range [t_first, t_last)
 *                    into ascending order stably.
 *
 * ----------------------------------------------------------------------------
 */
extern void algo_stable_sort(
    random_access_iterator_t t_first, random_access_iterator_t t_last);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_stable_sort_if
 *        Parameters: in) t_first: random_access_iterator_t
 *                        the first iterator.
 *                    in) t_last: random_access_iterator_t
 *                        the last iterator.
 *                    in) t_unary_op: unary_function_t
 *                        unary function.
 *           Returns: void
 *       Description: is sort the elements in the range [t_first, t_last)
 *                    into ascending order stably.
 *
 * ----------------------------------------------------------------------------
 */
extern void algo_stable_sort_if(
    random_access_iterator_t t_first, random_access_iterator_t t_last,
    binary_function_t t_binary_op);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_ALGO_H */
/** eof **/

