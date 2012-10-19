/*
 *  The interface of mutating algorithm.
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
    do\
    {\
        iterator_t it_begin = (it_first);\
        iterator_t it_end = (it_last);\
        assert(_iterator_valid_range(it_begin, it_end, _FORWARD_ITERATOR));\
        it_begin = algo_find(it_begin, it_end, (old_elem));\
        while (!iterator_equal(it_begin, it_end)) {\
            _algo_replace_once(it_begin, (new_elem));\
            it_begin = iterator_next(it_begin);\
            it_begin = algo_find(it_begin, it_end, (old_elem));\
        }\
    }while(false)

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
    input_iterator_t it_first, input_iterator_t it_last, output_iterator_t it_result, unary_function_t ufun_op);

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
    input_iterator_t it_first1, input_iterator_t it_last1, input_iterator_t it_first2, output_iterator_t it_result, binary_function_t bfun_op);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_ALGO_MUTATING_H_ */
/** eof **/

