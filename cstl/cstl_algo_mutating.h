/*
 *  The interface of mutating algorithm.
 *  Copyright (C)  2008 - 2013  Wangbo
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

#ifndef _CSTL_ALGO_MUTATING_H_
#define _CSTL_ALGO_MUTATING_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/**
 * Examines each element in a range and replaces it if it matches a specified value.
 * @param it_first      A forward iterator pointing to the position of the first element in the range from which elements are being replaced.
 * @param it_last       A forward iterator pointing to the position one past the final element in the range from which elements are being replaced.
 * @param old_elem      The old value of the elements being replaced.
 * @param new_elem      The new value being assigned to the elements with the old value.
 * @return  void.
 * @remarks The range recerenced must be valid, otherwise the behavior is undefined.
 */
#define algo_replace(it_first, it_last, old_elem, new_elem)\
    do {\
        iterator_t it_begin = (it_first);\
        iterator_t it_end = (it_last);\
        assert(_iterator_valid_range(it_begin, it_end, _FORWARD_ITERATOR));\
        it_begin = algo_find(it_begin, it_end, (old_elem));\
        while (!iterator_equal(it_begin, it_end)) {\
            _algo_replace_once(it_begin, (new_elem));\
            it_begin = iterator_next(it_begin);\
            it_begin = algo_find(it_begin, it_end, (old_elem));\
        }\
    } while (false)

/**
 * Examines each element in a range and replaces it if it satisfies a specified predicate.
 * @param it_first      A forward iterator pointing to the position of the first element in the range from which elements are being replaced.
 * @param it_last       An iterator pointing to the position one past the final element in the range from which elements are being replaced.
 * @param ufun_op       The unary predicate that must be satisfied is the value of an element is to be replaced.
 * @param elem          The new value being assigned to the elements whose old value satisfies the predicate.
 * @return  void.
 * @remarks The range referenced must be valid, otherwise the behavior is undefined.
 */
#define algo_replace_if(it_first, it_last, ufun_op, elem) _algo_replace_if((it_first), (it_last), (ufun_op), (elem))

/**
 * Examines each element in a source range and replaces it if it matches a specified value while copying the result into a new destination range.
 * @param it_first      An input iterator pointing to the position of the first element in the range from which elements are being replaced.
 * @param it_last       An input iterator pointing to the position one past the final element in the range from which elements are being replaced.
 * @param it_result     An output iterator pointing to the first element in the destination range to where the altered sequence of elements is being copied.
 * @param old_elem      The old value of the elements being replaced.
 * @param new_elem      The new value being assigned to the elements with the old value.
 * @return  void.
 * @remarks The source and destination ranges referenced must not overlap and must both be valid, otherwise the behavior is undefine.
 */
#define algo_replace_copy(it_first, it_last, it_result, old_elem, new_elem)\
    do {\
        iterator_t it_begin = (it_first);\
        iterator_t it_end = (it_last);\
        iterator_t it_copy = (it_result);\
        iterator_t it_tmp;\
        assert(_iterator_valid_range(it_begin, it_end, _INPUT_ITERATOR));\
        assert(_iterator_limit_type(it_copy, _OUTPUT_ITERATOR));\
        assert(_iterator_same_elem_type(it_begin, it_copy));\
        for (; !iterator_equal(it_begin, it_end); it_begin = iterator_next(it_begin), it_copy = iterator_next(it_copy)) {\
            it_tmp = algo_find(it_begin, it_end, (old_elem));\
            if (iterator_equal(it_tmp, it_begin)) {\
                _algo_replace_once(it_copy, (new_elem));\
            } else {\
                iterator_set_value(it_copy, iterator_get_pointer(it_begin));\
            }\
        }\
    } while (false)

/**
 * Examines each element in a source range and replaces it if it satisfies a specified predicate while copying the result into a new destination range.
 * @param it_first      An input iterator pointing to the position of the first element in the range from which elements are being replaced.
 * @param it_last       An input iterator pointing to the position one past the final element in the range from which elements are being replaced.
 * @param it_result     An output iterator pointing to the position of the first element in the destination range to which elements are being copied.
 * @param ufun_op       The unary predicate that must be satisfied is the value of an element is to be replaced.
 * @param elem          The new value being assigned to the elements whose old value satisfies the predicate.
 * @return  An output iterator pointing to the position one past the final element in the destination range to where the altered sequence of elements is being copied.
 * @remarks The source and destination ranges referenced must not overlap and must both be valid, otherwise the behavior is undefined.
 */
#define algo_replace_copy_if(it_first, it_last, it_result, ufun_op, elem) _algo_replace_copy_if((it_first), (it_last), (it_result), (ufun_op), (elem))

/**
 * Assigns the same new value to every element in a specified range.
 * @param it_first      A forward iterator addressing the position of the first element in the range to be traversed.
 * @param it_last       A forward iterator addressing the position one past the final element in the range to be traversed.
 * @param elem          The value to be assigned to elements in the range [it_first, it_last).
 * @return  void.
 * @remarks The destination range must be valid, otherwise the behavior is undefined.
 */
#define algo_fill(it_first, it_last, elem) _algo_fill((it_first), (it_last), (elem))

/**
 * Assigns a new value to a specified number of elements in a range beginning with a particular element.
 * @param it_first      An output iterator addressing the position of the first element in the range to be assigned the value elem.
 * @param t_fillsize    The number of elements to be assigned the value.
 * @param elem          The value to be assigned to elements in the range [it_first, it_first + t_fillsize).
 * @return  An output iterator pointing to the position one past the final element in the destination range to where the altered sequence of elements is being filled.
 * @remarks The destination range must be valid, otherwise the behavior is undefined.
 */
#define algo_fill_n(it_first, t_fillsize, elem) _algo_fill_n((it_first), (t_fillsize), (elem))

/**
 * Eliminates a specified value from a given range without disturbing the order of the remaining elements and returning the end of a new range free of the specified value.
 * @param it_first      A forward iterator addressing the position of the first element in the range from which elements are being removed.
 * @param it_last       A forward iterator addressing the position one past the final element in the range from which elements are being removed.
 * @param elem          The value that is to be removed from the range.
 * @return  A forward iterator addressing the new end position of the modified range, one past the final element of the remnant sequence free of the specified value.
 * @remarks The destination range must be valid, otherwise the behavior is undefined.
 */
#define algo_remove(it_first, it_last, elem) _algo_remove((it_first), (it_last), (elem))

/**
 * Copies elements from a source range to a destination range, except that elements of a specified value are not copied,
 * without disturbing the order of the remaining elements and returning the end of a new destination range.
 * @param it_first      An input iterator addressing the position of the first element in the range from which elements are being removed.
 * @param it_last       An input iterator addressing the position one past the final element in the range from which elements are being removed.
 * @param it_result     An output iterator addressing the position of the first element in the destination range to which elements are being removed.
 * @param elem          The value that is to be removed from the range.
 * @return  A forward iterator addressing the new end position of the destination range, one past the final element of the copy of the remnant 
 *          sequence free of the specified value.
 * @remarks The source and destination ranges referenced must be valid, otherwise the behavior is undefined.
 */
#define algo_remove_copy(it_first, it_last, it_result, elem) _algo_remove_copy((it_first), (it_last), (it_result), (elem))

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Assigns the values of elements from a source range to a destination range, iterating through the source sequence of elements and
 * assigning them new positions in a forward direction.
 * @param it_first      An input iterator addressing the position of the first element in the source range.
 * @param it_last       An input iterator addressing the position that is one past the final element in the source range.
 * @param it_result     An output iterator addressing the position of the first element in the destination range.
 * @return  An output iterator addressing the position that is one past the final element in the destination range,
 *          that is, the iterator addresses it_result + (it_last - it_first ).
 * @remarks The source range must be valid and there must be sufficient space at the destination to hold all the elements being copied.
 *          The two ranges must be contain same element type, otherwise the behavior of the algorithm is undefined.
 */
extern output_iterator_t algo_copy(input_iterator_t it_first, input_iterator_t it_last, output_iterator_t it_result);

/**
 * Assigns the values of elements from a source range to a destination range, iterating through the source sequence of elements and
 * assigning them new positions in a forward direction.
 * @param it_first      An input iterator addressing the position of the first element in the source range.
 * @param t_count       The number of element in the source range.
 * @param it_result     An output iterator addressing the position of the first element in the destination range.
 * @return  An output iterator addressing the position that is one past the final element in the destination range,
 *          that is, the iterator addresses it_result + t_count.
 * @remarks The source range must be valid and there must be sufficient space at the destination to hold all the elements being copied.
 *          The two ranges must be contain same element type, otherwise the behavior of the algorithm is undefined.
 */
extern output_iterator_t algo_copy_n(input_iterator_t it_first, size_t t_count, output_iterator_t it_result);

/**
 * Assigns the values of elements from a source range to a destination range, iterating through the source sequence of elements and
 * assigning them new positions in a backward direction.
 * @param it_first      A bidirectional iterator addressing the position of the first element in the source range.
 * @param it_last       A bidirectional iterator addressing the position that is one past the final element in the source range.
 * @param it_result     A bidirectional iterator addressing the position of the one past the final element in the destination range.
 * @return  An output iterator addressing the position that is one past the final element in the destination range, that is,
 *          the iterator addresses it_result - (it_last - it_first ).
 * @remarks The source range must be valid and there must be sufficient space at the destination to hold all the elements being copied.
 *          The two ranges must be contain same element type, otherwise the behavior of the algorithm is undefined.
 */
extern bidirectional_iterator_t algo_copy_backward(
    bidirectional_iterator_t it_first, bidirectional_iterator_t it_last, bidirectional_iterator_t it_result);

/**
 * Exchanges two values referred to by a pair of specified iterators.
 * @param it_first      One of the forward iterators whose value is to be exchanged.
 * @param it_second     The second of the forward iterators whose value is to be exchanged.
 * @return  void.
 * @remarks Two iterator must be same element type, otherwise the behavior is undefine.
 */
extern void algo_swap(forward_iterator_t it_first, forward_iterator_t it_second);
extern void algo_iter_swap(forward_iterator_t it_first, forward_iterator_t it_second);

/**
 * Exchanges the elements of one range with the elements of another, equal sized range.
 * @param it_first1     A forward iterator pointing to the first position of the first range whose elements are to be exchanged.
 * @param it_second     A forward iterator pointing to one past the final position of the first range whose elements are to be exchanged.
 * @param it_first2     A forward iterator pointing to the first position of the second range whose elements are to be exchanged.
 * @return  A forward iterator pointing to one past the final position of the second range whose elements are to be exchanged.
 * @remarks The ranges referenced must be valid; The second range has to be as large as the first range. The two ranges must be contain
 *          same element type, otherwise the behavior of the algorithm is undefined.
 */
extern forward_iterator_t algo_swap_ranges(forward_iterator_t it_first1, forward_iterator_t it_last1, forward_iterator_t it_first2);

/**
 * Applies a specified function object to each element in a source range and copies the return values of the function object into a destination range.
 * @param it_first      An input iterator addressing the position of the first element in the first source range to be operated on.
 * @param it_last       An input iterator addressing the position one past the final element in the first source range operated on.
 * @param it_result     An output iterator addressing the position of the first element in the destination range.
 * @param ufun_op       User-defined unary function that is applied to each element in the first source range.
 * @return  An output iterator addressing the position one past the final element in the destination range
 *          that is receiving the output elements transformed by the function object.
 * @remarks The ranges referenced must be valid. The destination range must be large enough to contain the transformed source range.
 *          The two ranges must be contain same element type, otherwise the behavior of algorithm is undefined.
 */
extern output_iterator_t algo_transform(
    input_iterator_t it_first, input_iterator_t it_last, output_iterator_t it_result, ufun_t ufun_op);

/**
 * Applies a specified function object to a pair of elements from two source ranges and copies the return values of the function into a destination range.
 * @param it_first1     An input iterator addressing the position of the first element in the first source range to be operated on.
 * @param it_last1      An input iterator addressing the position one past the final element in the first source range operated on.
 * @param it_first2     An input iterator addressing the position of the first element in the second source range to be operated on.
 * @param it_result     An output iterator addressing the position of the first element in the destination range.
 * @param bfun_op       A user-defined (UD) binary function that is applied pairwise, in a forward order, to the two source ranges.
 * @return  An output iterator addressing the position one past the final element in the destination range
 *          that is receiving the output elements transformed by the function object.
 * @remarks The ranges referenced must be valid. The destination range must be large enough to contain the transformed source range.
 *          The two ranges must be contain same element type, otherwise the behavior of algorithm is undefined.
 */
extern output_iterator_t algo_transform_binary(
    input_iterator_t it_first1, input_iterator_t it_last1, input_iterator_t it_first2, output_iterator_t it_result, bfun_t bfun_op);

/**
 * Assigns the values generated by a unary function to each element in a range.
 * @param it_first      A forward iterator addressing the position of the first element in the range to which values are to be assigned.
 * @param it_last       A forward iterator addressing the position one past the final element in the range to which values are to be assigned.
 * @param ufun_op       A unary function that is used to generate the values to be assigned to each of the elements in the range.
 * @return  void.
 * @remarks The ranges referenced must be valid, otherwise the behavior of algorithm is undefined.
 */
extern void algo_generate(forward_iterator_t it_first, forward_iterator_t it_last, ufun_t ufun_op);

/**
 * Assigns the values generated by a unary function to a specified number of element in a range and returns to the position one past the last assigned value.
 * @param it_first      A forward iterator addressing the position of the first element in the range to which values are to be assigned.
 * @param it_last       The number of elements to be assigned a value by the generator function.
 * @param ufun_op       A unary function that is used to generate the values to be assigned to each of the elements in the range.
 * @return  An output iterator pointing to the position one past the final element in the destination range to where the altered sequence of elements is being assigned.
 * @remarks The ranges referenced must be valid, otherwise the behavior of algorithm is undefined.
 */
extern output_iterator_t algo_generate_n(output_iterator_t it_first, size_t t_count, ufun_t ufun_op);

/**
 * Eliminates elements that satisfy a predicate from a given range without disturbing the order of the remaining elements and
 * returning the end of a new range free of the specified value.
 * @param it_first      A forward iterator pointing to the position of the first element in the range from which elements are being removed.
 * @param it_last       A forward iterator pointing to the position one past the final element in the range from which elements are being removed.
 * @param ufun_op       The unary predicate that must be satisfied is the value of an element is to be replaced.
 * @return  A forward iterator addressing the new end position of the modified range, one past the final element of the remnant sequence free of the specified value.
 * @remarks The ranges referenced must be valid, otherwise the behavior of algorithm is undefined.
 */
extern forward_iterator_t algo_remove_if(forward_iterator_t it_first, forward_iterator_t it_last, ufun_t ufun_op);

/**
 * Copies elements from a source range to a destination range, except that satisfying a predicate are not copied, without disturbing the order of the remaining
 * elements and returning the end of a new destination range.
 * @param it_first      An input iterator addressing the position of the first element in the range from which elements are being removed.
 * @param it_last       An input iterator addressing the position one past the final element in the range from which elements are being removed.
 * @param it_result     An output iterator addressing the position of the first element in the destination range to which elements are being removed.
 * @param ufun_op       The unary predicate that must be satisfied is the value of an element is to be replaced.
 * @return  A forward iterator addressing the new end position of the destination range, one past the final element of the remnant sequence free of
 *          the elements satisfying the predicate.
 * @remarks The ranges referenced must be valid. The destination range must be large enough to contain the transformed source range.
 *          The two ranges must be contain same element type, otherwise the behavior of algorithm is undefined.
 */
extern output_iterator_t algo_remove_copy_if(input_iterator_t it_first, input_iterator_t it_last, output_iterator_t it_result, ufun_t ufun_op);

/**
 * Removes duplicate elements that are adjacent to each other in a specified range.
 * @param it_first      A forward iterator addressing the position of the first element in the range to be scanned for duplicate removal.
 * @param it_last       A forward iterator addressing the position one past the final element in the range to be scanned for duplicate removal.
 * @return  A forward iterator to the new end of the modified sequence that contains no consecutive duplicates, addressing the position one past the last element not removed.
 * @remarks The ranges referenced must be valid, otherwise the behavior of algorithm is undefined.
 */
extern forward_iterator_t algo_unique(forward_iterator_t it_first, forward_iterator_t it_last);

/**
 * Removes duplicate elements that are adjacent to each other in a specified range.
 * @param it_first      A forward iterator addressing the position of the first element in the range to be scanned for duplicate removal.
 * @param it_last       A forward iterator addressing the position one past the final element in the range to be scanned for duplicate removal.
 * @param bfun_op       User-defined predicate function that defines the condition to be satisfied if two elements are to be taken as equivalent.
 * @return  A forward iterator to the new end of the modified sequence that contains no consecutive duplicates, addressing the position one past the last element not removed.
 * @remarks The ranges referenced must be valid, otherwise the behavior of algorithm is undefined.
 */
extern forward_iterator_t algo_unique_if(forward_iterator_t it_first, forward_iterator_t it_last, bfun_t bfun_op);

/**
 * Copies elements from a source range into a destination range except for the duplicate elements that are adjacent to each other.
 * @param it_first      A forward iterator addressing the position of the first element in the source range to be copied.
 * @param it_last       A forward iterator addressing the position one past the final element in the source range to be copied.
 * @param it_result     An output iterator addressing the position of the first element in the destination range that is receiving the copy with consecutive duplicates removed.
 * @return  An output iterator addressing the position one past the final element in the destination range that is receiving the copy with consecutive duplicates removed.
 * @remarks The ranges referenced must be valid. The destination range must be large enough to contain the transformed source range.
 *          The two ranges must be contain same element type, otherwise the behavior of algorithm is undefined.
 */
extern output_iterator_t algo_unique_copy(input_iterator_t it_first, input_iterator_t it_last, output_iterator_t it_result);

/**
 * Copies elements from a source range into a destination range except for the duplicate elements that are adjacent to each other.
 * @param it_first      A forward iterator addressing the position of the first element in the source range to be copied.
 * @param it_last       A forward iterator addressing the position one past the final element in the source range to be copied.
 * @param it_result     An output iterator addressing the position of the first element in the destination range that is receiving the copy with consecutive duplicates removed.
 * @param bfun_op       User-defined predicate function object that defines the condition to be satisfied if two elements are to be taken as equivalent.
 * @return  An output iterator addressing the position one past the final element in the destination range that is receiving the copy with consecutive duplicates removed.
 * @remarks The ranges referenced must be valid. The destination range must be large enough to contain the transformed source range.
 *          The two ranges must be contain same element type, otherwise the behavior of algorithm is undefined.
 */
extern output_iterator_t algo_unique_copy_if(input_iterator_t it_first, input_iterator_t it_last, output_iterator_t it_result, bfun_t bfun_op);

/**
 * Reverses the order of the elements within a range.
 * @param it_first      A bidirectional iterator pointing to the position of the first element in the range within which the elements are being permuted.
 * @param it_last       A bidirectional iterator pointing to the position one past the final element in the range within which the elements are being permuted.
 * @return  void.
 * @remarks The ranges referenced must be valid, otherwise the behavior of algorithm is undefined.
 */
extern void algo_reverse(bidirectional_iterator_t it_first, bidirectional_iterator_t it_last);

/**
 * Reverses the order of the elements within a source range while copying them into a destination range
 * @param it_first      A bidirectional iterator pointing to the position of the first element in the range within which the elements are being permuted.
 * @param it_last       A bidirectional iterator pointing to the position one past the final element in the range within which the elements are being permuted.
 * @param it_result     An output iterator pointing to the position of the first element in the destination range to which elements are being copied.
 * @return  An output iterator pointing to the position one past the final element in the destination range to where the altered sequence of elements is being copied.
 * @remarks The ranges referenced must be valid. The destination range must be large enough to contain the transformed source range.
 *          The two ranges must be contain same element type, otherwise the behavior of algorithm is undefined.
 */
extern output_iterator_t algo_reverse_copy(bidirectional_iterator_t it_first, bidirectional_iterator_t it_last, output_iterator_t it_result);

/**
 * Exchanges the elements in two adjacent ranges.
 * @param it_first      A forward iterator addressing the position of the first element in the range to be rotated.
 * @param it_middle     A forward iterator defining the boundary within the range that addresses the position of the first element
 *                      in the second part of the range whose elements are to be exchanged with those in the first part of the range.
 * @param it_last       A forward iterator addressing the position one past the final element in the range to be rotated.
 * @return  An forward iterator addressing the new middle position.
 * @remarks The ranges referenced must be valid, otherwise the behavior is undefined.
 */
extern forward_iterator_t algo_rotate(forward_iterator_t it_first, forward_iterator_t it_middle, forward_iterator_t it_last);

/**
 * Exchanges the elements in two adjacent ranges within a source range and copies the result to a destination range.
 * @param it_first      A forward iterator addressing the position of the first element in the range to be rotated.
 * @param it_middle     A forward iterator defining the boundary within the range that addresses the position of the first element
 *                      in the second part of the range whose elements are to be exchanged with those in the first part of the range.
 * @param it_last       A forward iterator addressing the position one past the final element in the range to be rotated.
 * @param it_result     An output iterator addressing the position of the first element in the destination range.
 * @return  An output iterator addressing the position one past the final element in the destination range.
 * @remarks The ranges referenced must be valid, otherwise the behavior is undefined.
 */
extern output_iterator_t algo_rotate_copy(forward_iterator_t it_first, forward_iterator_t it_middle, forward_iterator_t it_last, output_iterator_t it_result);

/**
 * Rearranges a sequence of N elements in a range into one of N! possible arrangements selected at random.
 * @param it_first      A random-access iterator addressing the position of the first element in the range to be rearranged.
 * @param it_last       A random-access iterator addressing the position one past the final element in the range to be rearranged.
 * @return  void.
 * @remarks The ranges referenced must be valid, otherwise the behavior is undefined.
 */
extern void algo_random_shuffle(random_access_iterator_t it_first, random_access_iterator_t it_last);

/**
 * Rearranges a sequence of N elements in a range into one of N! possible arrangements selected at random.
 * @param it_first      A random-access iterator addressing the position of the first element in the range to be rearranged.
 * @param it_last       A random-access iterator addressing the position one past the final element in the range to be rearranged.
 * @param ufun_op       A special function called a random number generator.
 * @return  void.
 * @remarks The ranges referenced must be valid, otherwise the behavior is undefined.
 */
extern void algo_random_shuffle_if(random_access_iterator_t it_first, random_access_iterator_t it_last, ufun_t ufun_op);

/**
 * Copy a sample of the elements from the range [it_first1, it_last1) into the range [it_first2, it_last2).
 * @param it_first1     An input iterator pointing to the position of the first element in the range from which elements are being selected.
 * @param it_last1      An input iterator pointing to the position one past the final element in the range from which elements are being selected.
 * @param it_first2     An random-access iterator pointing to the position of the first element in the destination range to which elements are being copied.
 * @param it_last2      An random-access iterator pointing to the position one past the final element in the destination range to which elements are being copied.
 * @return  An random-access iterator addressing the position one past the final element in the destination range.
 * @remarks The ranges referenced must be valid, otherwise the behavior is undefined.
 */
extern random_access_iterator_t algo_random_sample(
    input_iterator_t it_first1, input_iterator_t it_last1, random_access_iterator_t it_first2, random_access_iterator_t it_last2);

/**
 * Copy a sample of the elements from the range [it_first1, it_last1) into the range [it_first2, it_last2).
 * @param it_first1     An input iterator pointing to the position of the first element in the range from which elements are being selected.
 * @param it_last1      An input iterator pointing to the position one past the final element in the range from which elements are being selected.
 * @param it_first2     An random-access iterator pointing to the position of the first element in the destination range to which elements are being copied.
 * @param it_last2      An random-access iterator pointing to the position one past the final element in the destination range to which elements are being copied.
 * @param ufun_op       A special function called a random number generator.
 * @return  An random-access iterator addressing the position one past the final element in the destination range.
 * @remarks The ranges referenced must be valid, otherwise the behavior is undefined.
 */
extern random_access_iterator_t algo_random_sample_if(
    input_iterator_t it_first1, input_iterator_t it_last1, random_access_iterator_t it_first2, random_access_iterator_t it_last2, ufun_t ufun_op);

/**
 * Copy a sample of the elements from the range [it_first1, it_last1) into the range [it_first2, it_first2 + t_count).
 * @param it_first      An input iterator pointing to the position of the first element in the range from which elements are being selected.
 * @param it_last       An input iterator pointing to the position one past the final element in the range from which elements are being selected.
 * @param it_result     An output iterator pointing to the position of the first element in the destination range to which elements are being copied.
 * @param t_count       The number of elements to be copied the value.
 * @return  An output iterator addressing the position one past the final element in the destination range.
 * @remarks The ranges referenced must be valid, otherwise the behavior is undefined.
 */
extern output_iterator_t algo_random_sample_n(
    input_iterator_t it_first, input_iterator_t it_last, output_iterator_t it_result, size_t t_count);

/**
 * Copy a sample of the elements from the range [it_first1, it_last1) into the range [it_first2, it_first2 + t_count).
 * @param it_first      An input iterator pointing to the position of the first element in the range from which elements are being selected.
 * @param it_last       An input iterator pointing to the position one past the final element in the range from which elements are being selected.
 * @param it_result     An output iterator pointing to the position of the first element in the destination range to which elements are being copied.
 * @param t_count       The number of elements to be copied the value.
 * @param ufun_op       A special function called a random number generator.
 * @return  An output iterator addressing the position one past the final element in the destination range.
 * @remarks The ranges referenced must be valid, otherwise the behavior is undefined.
 */
extern output_iterator_t algo_random_sample_n_if(
    input_iterator_t it_first, input_iterator_t it_last, output_iterator_t it_result, size_t t_count, ufun_t ufun_op);

/**
 * Classifies elements in a range into two disjoint sets, with those elements satisfying a unary predicate preceding those that fail to satisfy it.
 * @param it_first      A forward iterator addressing the position of the first element in the range to be partitioned.
 * @param it_last       A forward iterator addressing the position one past the final element in the range to be partitioned.
 * @param ufun_op       User-defined predicate function that defines the condition to be satisfied if an element is to be classified.
 * @return  A forward iterator addressing the position of the first element in the range to not satisfy the predicate condition.
 * @remarks The ranges referenced must be valid, otherwise the behavior is undefined.
 */
extern forward_iterator_t algo_partition(forward_iterator_t it_first, forward_iterator_t it_last, ufun_t ufun_op);

/**
 * Classifies elements in a range into two disjoint sets, with those elements satisfying a unary predicate preceding those that fail to satisfy it,
 * preserving the relative order of equivalent elements.
 * @param it_first      A forward iterator addressing the position of the first element in the range to be partitioned.
 * @param it_last       A forward iterator addressing the position one past the final element in the range to be partitioned.
 * @param ufun_op       User-defined predicate function that defines the condition to be satisfied if an element is to be classified.
 * @return  A forward iterator addressing the position of the first element in the range to not satisfy the predicate condition.
 * @remarks The ranges referenced must be valid, otherwise the behavior is undefined.
 */
extern forward_iterator_t algo_stable_partition(forward_iterator_t it_first, forward_iterator_t it_last, ufun_t ufun_op);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_ALGO_MUTATING_H_ */
/** eof **/

