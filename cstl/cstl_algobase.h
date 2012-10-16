/*
 *  The interface of base algorithm.
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

#ifndef _CSTL_ALGOBASE_H_
#define _CSTL_ALGOBASE_H_

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
 * swap and iterator swap algorithm.
 */
extern void algo_swap(forward_iterator_t t_first, forward_iterator_t t_second);
extern void algo_iter_swap(forward_iterator_t t_first, forward_iterator_t t_second);

/*
 * compare and compare 3way algorithm.
 */
extern bool_t algo_lexicographical_compare(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2);
extern bool_t algo_lexicographical_compare_if(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2,
    binary_function_t t_binary_op);
extern int algo_lexicographical_compare_3way(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2);
extern int algo_lexicographical_compare_3way_if(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2,
    binary_function_t t_binary_op);

/*
 * max and min algorithm.
 */
extern input_iterator_t algo_max(input_iterator_t t_first, input_iterator_t t_second);
extern input_iterator_t algo_max_if(
    input_iterator_t t_first, input_iterator_t t_last, binary_function_t t_binary_op);
extern input_iterator_t algo_min(input_iterator_t t_first, input_iterator_t t_second);
extern input_iterator_t algo_min_if(
    input_iterator_t t_first, input_iterator_t t_last, binary_function_t t_binary_op);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_ALGOBASE_H_ */
/** eof **/

