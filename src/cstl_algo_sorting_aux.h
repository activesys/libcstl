/*
 *  The interface of auxiliary sorting algorithm.
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

#ifndef _CSTL_ALGO_SORTING_AUX_H_
#define _CSTL_ALGO_SORTING_AUX_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Compute logarithm of 2
 * @param t_base        Base.
 * @return  Power.
 */
extern size_t _algo_lg(size_t t_base);

/**
 * Return the median of three random_access_iterator_t
 * @param it_first      A random-access iterator addressing the position of the first element in the range.
 * @param it_middle     A random-access iterator addressing the position of the middle element in the range.
 * @param it_last       A random-access iterator addressing the position of the last element in the range.
 * @param bfun_op       User-defined predicate function object that defines the comparison criterion to be satisfied by successive elements in the ordering.
 * @return  The median iterator.
 * @remarks This three iterator must be point element that have same type, otherwise the behavior is undefined.
 */
extern random_access_iterator_t _algo_median_of_three_if(
    random_access_iterator_t it_first, random_access_iterator_t it_middle, random_access_iterator_t it_last, bfun_t bfun_op);

/**
 * Insertion sort for specify range.
 * @param it_first      A random-access iterator addressing the position of the first element in the range.
 * @param it_last       A random-access iterator addressing the position of the last element in the range.
 * @param bfun_op       User-defined predicate function object that defines the comparison criterion to be satisfied by successive elements in the ordering.
 * @param pv_value      Specificed value.
 * @return  void.
 * @remarks This three iterator must be point element that have same type, otherwise the behavior is undefined.
 */
extern void _algo_insertion_sort_if(random_access_iterator_t it_first, random_access_iterator_t it_last, bfun_t bfun_op, void* pv_value);

/**
 * Quick sort or heap sort for specify range.
 * @param it_first      A random-access iterator addressing the position of the first element in the range.
 * @param it_last       A random-access iterator addressing the position of the last element in the range.
 * @param bfun_op       User-defined predicate function object that defines the comparison criterion to be satisfied by successive elements in the ordering.
 * @param t_depth       Range depth.
 * @param pv_value      Specificed value.
 * @return  void.
 * @remarks This three iterator must be point element that have same type, otherwise the behavior is undefined.
 */
extern void _algo_intro_sort_if(
    random_access_iterator_t it_first, random_access_iterator_t it_last, bfun_t bfun_op, size_t t_depth, void* pv_value);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_ALGO_SORTING_AUX_H_ */
/** eof **/

