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

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_ALGO_MUTATING_H_ */
/** eof **/

