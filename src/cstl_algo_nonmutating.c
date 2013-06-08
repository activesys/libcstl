/*
 *  The implementation of non-mutating algorithm.
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

/** include section **/
#include <cstl/cstl_def.h>
#include <cstl/cstl_alloc.h>
#include <cstl/cstl_types.h>
#include <cstl/citerator.h>
#include <cstl/cstring.h>
#include <cstl/cfunctional.h>
#include <cstl/calgorithm.h>

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Applies a unary function to each element in a range.
 */
void algo_for_each(input_iterator_t it_first, input_iterator_t it_last, ufun_t ufun_op)
{
    assert(_iterator_valid_range(it_first, it_last, _INPUT_ITERATOR));

    if (ufun_op == NULL) {
        ufun_op = fun_default_unary;
    }

    for (; !iterator_equal(it_first, it_last); it_first = iterator_next(it_first)) {
        (*ufun_op)(iterator_get_pointer(it_first), NULL);
    }
}

/**
 * Locates the position of the first occurrence of an element in a range that satisfies a specified condition.
 */
input_iterator_t algo_find_if(input_iterator_t it_first, input_iterator_t it_last, ufun_t ufun_op)
{
    bool_t b_result = false;

    assert(_iterator_valid_range(it_first, it_last, _INPUT_ITERATOR));

    if (ufun_op == NULL) {
        ufun_op = fun_default_unary;
    }
    for (; !iterator_equal(it_first, it_last); it_first = iterator_next(it_first)) {
        (*ufun_op)(iterator_get_pointer(it_first), &b_result);
        if (b_result) {
            break;
        }
    }

    return it_first;
}

/**
 * Searches for two adjacent elements that are equal.
 */
forward_iterator_t algo_adjacent_find(forward_iterator_t it_first, forward_iterator_t it_last)
{
    return algo_adjacent_find_if(it_first, it_last, _fun_get_binary(it_first, _EQUAL_FUN));
}

/**
 * Searches for two adjacent elements that satisfy a specificed condition.
 */
forward_iterator_t algo_adjacent_find_if(forward_iterator_t it_first, forward_iterator_t it_last, bfun_t bfun_op)
{
    forward_iterator_t it_next;
    bool_t             b_result = false;
    bool_t             b_less = false;
    bool_t             b_greater = false;

    assert(_iterator_valid_range(it_first, it_last, _FORWARD_ITERATOR));

    if (bfun_op == NULL) {
        bfun_op = _fun_get_binary(it_first, _EQUAL_FUN);
    }

    if (iterator_equal(it_first, it_last)) {
        return it_last;
    }

    if (bfun_op == fun_default_binary) {
        bfun_op = _fun_get_binary(it_first, _LESS_FUN);

        it_next = it_first;
        it_next = iterator_next(it_next);
        while (!iterator_equal(it_next, it_last)) {
            (*bfun_op)(iterator_get_pointer(it_first), iterator_get_pointer(it_next), &b_less);
            (*bfun_op)(iterator_get_pointer(it_next), iterator_get_pointer(it_first), &b_greater);
            if (!b_less && !b_greater) {
                return it_first;
            }

            it_first = it_next;
            it_next = iterator_next(it_next);
        }
    } else {
        it_next = it_first;
        it_next = iterator_next(it_next);
        while (!iterator_equal(it_next, it_last)) {
            (*bfun_op)(iterator_get_pointer(it_first), iterator_get_pointer(it_next), &b_result);
            if (b_result) {
                return it_first;
            }

            it_first = it_next;
            it_next = iterator_next(it_next);
        }
    }

    return it_last;
}

/**
 * Searches for the first occurrence of any of several values within a target range.
 */
input_iterator_t algo_find_first_of(
    input_iterator_t it_first1, input_iterator_t it_last1,
    forward_iterator_t it_first2, forward_iterator_t it_last2)
{
    return algo_find_first_of_if(it_first1, it_last1, it_first2, it_last2, _fun_get_binary(it_first1, _EQUAL_FUN));
}

/**
 * Searches for the first occurrence of any of several elements that are equivalent in a sense specified by
 */
input_iterator_t algo_find_first_of_if(
    input_iterator_t it_first1, input_iterator_t it_last1,
    forward_iterator_t it_first2, forward_iterator_t it_last2,
    bfun_t bfun_op)
{
    iterator_t it_index;
    bool_t     b_result = false;
    bool_t     b_less = false;
    bool_t     b_greater = false;

    assert(_iterator_valid_range(it_first1, it_last1, _INPUT_ITERATOR));
    assert(_iterator_valid_range(it_first2, it_last2, _FORWARD_ITERATOR));
    assert(_iterator_same_elem_type(it_first1, it_first2));

    if (bfun_op == NULL) {
        bfun_op = _fun_get_binary(it_first1, _EQUAL_FUN);
    }

    if (bfun_op == fun_default_binary) {
        bfun_op = _fun_get_binary(it_first1, _LESS_FUN);

        for (; !iterator_equal(it_first1, it_last1); it_first1 = iterator_next(it_first1)) {
            for (it_index = it_first2; !iterator_equal(it_index, it_last2); it_index = iterator_next(it_index)) {
                (*bfun_op)(iterator_get_pointer(it_first1), iterator_get_pointer(it_index), &b_less);
                if (b_less) {
                    continue;
                }
                (*bfun_op)(iterator_get_pointer(it_index), iterator_get_pointer(it_first1), &b_greater);
                if (b_greater) {
                    continue;
                }

                return it_first1;
            }
        }
    } else {
        for (; !iterator_equal(it_first1, it_last1); it_first1 = iterator_next(it_first1)) {
            for (it_index = it_first2; !iterator_equal(it_index, it_last2); it_index = iterator_next(it_index)) {
                (*bfun_op)(iterator_get_pointer(it_first1), iterator_get_pointer(it_index), &b_result);
                if (b_result) {
                    return it_first1;
                }
            }
        }
    }

    return it_last1;
}

/**
 * Returns the number of elements in a range whose values satisfy a specified condition.
 */
size_t algo_count_if(input_iterator_t it_first, input_iterator_t it_last, ufun_t ufun_op)
{
    bool_t b_result = false;
    size_t t_count = 0;

    assert(_iterator_valid_range(it_first, it_last, _INPUT_ITERATOR));

    if (ufun_op == NULL) {
        ufun_op = fun_default_unary;
    }
    for (; !iterator_equal(it_first, it_last); it_first = iterator_next(it_first)) {
        (*ufun_op)(iterator_get_pointer(it_first), &b_result);
        if (b_result) {
            t_count++;
        }
    }

    return t_count;
}

/**
 * Compares two ranges element by element either for equality and locates the first position where a difference occurs.
 */
range_t algo_mismatch(input_iterator_t it_first1, input_iterator_t it_last1, input_iterator_t it_first2)
{
    return algo_mismatch_if(it_first1, it_last1, it_first2, _fun_get_binary(it_first1, _EQUAL_FUN));
}

/**
 * Compares two ranges element by element either for equivalent in a sense specified by a binary predicate and locates
 * the first position where a difference occurs.
 */
range_t algo_mismatch_if(
    input_iterator_t it_first1, input_iterator_t it_last1, input_iterator_t it_first2, bfun_t bfun_op)
{
    bool_t  b_result = false;
    bool_t  b_less = false;
    bool_t  b_greater = false;
    range_t r_range;

    assert(_iterator_valid_range(it_first1, it_last1, _INPUT_ITERATOR));
    assert(_iterator_limit_type(it_first2, _INPUT_ITERATOR));
    assert(_iterator_same_elem_type(it_first1, it_first2));

    if (bfun_op == NULL) {
        bfun_op = _fun_get_binary(it_first1, _EQUAL_FUN);
    }

    if (bfun_op == fun_default_binary) {
        bfun_op = _fun_get_binary(it_first1, _LESS_FUN);
        for (;
             !iterator_equal(it_first1, it_last1);
             it_first1 = iterator_next(it_first1), it_first2 = iterator_next(it_first2)) {
            (*bfun_op)(iterator_get_pointer(it_first1), iterator_get_pointer(it_first2), &b_less);
            if (b_less) {
                break;
            }
            (*bfun_op)(iterator_get_pointer(it_first2), iterator_get_pointer(it_first1), &b_greater);
            if (b_greater) {
                break;
            }
        }
    } else {
        for (;
             !iterator_equal(it_first1, it_last1);
             it_first1 = iterator_next(it_first1), it_first2 = iterator_next(it_first2)) {
            (*bfun_op)(iterator_get_pointer(it_first1), iterator_get_pointer(it_first2), &b_result);
            if (!b_result) {
                break;
            }
        }
    }

    r_range.it_begin = it_first1;
    r_range.it_end = it_first2;
    return r_range;
}

/**
 * Compares two ranges element by element either for equality.
 */
bool_t algo_equal(input_iterator_t it_first1, input_iterator_t it_last1, input_iterator_t it_first2)
{
    return algo_equal_if(it_first1, it_last1, it_first2, _fun_get_binary(it_first1, _EQUAL_FUN));
}

/**
 * Compares two ranges element by element either for equivalence in a sense specified by a binary predicate.
 */
bool_t algo_equal_if(
    input_iterator_t it_first1, input_iterator_t it_last1, input_iterator_t it_first2, bfun_t bfun_op)
{
    bool_t b_result = false;
    bool_t b_less = false;
    bool_t b_greater = false;

    assert(_iterator_valid_range(it_first1, it_last1, _INPUT_ITERATOR));
    assert(_iterator_limit_type(it_first2, _INPUT_ITERATOR));
    assert(_iterator_same_elem_type(it_first1, it_first2));

    if (bfun_op == NULL) {
        bfun_op = _fun_get_binary(it_first1, _EQUAL_FUN);
    }

    if (bfun_op == fun_default_binary) {
        bfun_op = _fun_get_binary(it_first1, _LESS_FUN);
        for (; !iterator_equal(it_first1, it_last1); it_first1 = iterator_next(it_first1), it_first2 = iterator_next(it_first2)) {
            (*bfun_op)(iterator_get_pointer(it_first1), iterator_get_pointer(it_first2), &b_less);
            if (b_less) {
                return false;
            }
            (*bfun_op)(iterator_get_pointer(it_first2), iterator_get_pointer(it_first1), &b_greater);
            if (b_greater) {
                return false;
            }
        }
    } else {
        for (; !iterator_equal(it_first1, it_last1); it_first1 = iterator_next(it_first1), it_first2 = iterator_next(it_first2)) {
            (*bfun_op)(iterator_get_pointer(it_first1), iterator_get_pointer(it_first2), &b_result);
            if (!b_result) {
                return false;
            }
        }
    }

    return true;
}

/**
 * Searches for the first occurrence of a sequence within a target range whose elements are equal to those in a given sequence.
 */
forward_iterator_t algo_search(
    forward_iterator_t it_first1, forward_iterator_t it_last1, forward_iterator_t it_first2, forward_iterator_t it_last2)
{
    return algo_search_if(it_first1, it_last1, it_first2, it_last2, _fun_get_binary(it_first1, _EQUAL_FUN));
}

/**
 * Searches for the first occurrence of a sequence within a target range whose elements or whose elements are equivalent in a sense specified
 */
forward_iterator_t algo_search_if(
    forward_iterator_t it_first1, forward_iterator_t it_last1,
    forward_iterator_t it_first2, forward_iterator_t it_last2,
    bfun_t bfun_op)
{
    bool_t     b_result = false;
    bool_t     b_less = false;
    bool_t     b_greater = false;
    iterator_t it_index1;
    iterator_t it_index2;
    size_t     t_len1 = 0;
    size_t     t_len2 = 0;

    assert(_iterator_valid_range(it_first1, it_last1, _FORWARD_ITERATOR));
    assert(_iterator_valid_range(it_first2, it_last2, _FORWARD_ITERATOR));
    assert(_iterator_same_elem_type(it_first1, it_first2));

    if (bfun_op == NULL) {
        bfun_op = _fun_get_binary(it_first1, _EQUAL_FUN);
    }

    t_len1 = iterator_distance(it_first1, it_last1);
    t_len2 = iterator_distance(it_first2, it_last2);
    if (t_len1 == 0 || t_len1 < t_len2) {
        return it_last1;
    }
    if (t_len2 == 0) {
        return it_first1;
    }

    if (bfun_op == fun_default_binary) {
        bfun_op = _fun_get_binary(it_first1, _LESS_FUN);

        for (; !iterator_equal(it_first1, it_last1); it_first1 = iterator_next(it_first1)) {
            (*bfun_op)(iterator_get_pointer(it_first1), iterator_get_pointer(it_first2), &b_less);
            if (b_less) {
                continue;
            }
            (*bfun_op)(iterator_get_pointer(it_first2), iterator_get_pointer(it_first1), &b_greater);
            if (b_greater) {
                continue;
            }

            for (it_index1 = it_first1, it_index1 = iterator_next(it_index1),
                 it_index2 = it_first2, it_index2 = iterator_next(it_index2);
                 !iterator_equal(it_index1, it_last1) && 
                 !iterator_equal(it_index2, it_last2);
                 it_index1 = iterator_next(it_index1), 
                 it_index2 = iterator_next(it_index2)) {
                (*bfun_op)(iterator_get_pointer(it_index1), iterator_get_pointer(it_index2), &b_less);
                if (b_less) {
                    break;
                }
                (*bfun_op)(iterator_get_pointer(it_index2), iterator_get_pointer(it_index1), &b_greater);
                if (b_greater) {
                    break;
                }
            }

            if (iterator_equal(it_index2, it_last2)) {
                return it_first1;
            }
        }
    } else {
        for (; !iterator_equal(it_first1, it_last1); it_first1 = iterator_next(it_first1)) {
            (*bfun_op)(iterator_get_pointer(it_first1), iterator_get_pointer(it_first2), &b_result);
            if (b_result) {
                for (it_index1 = it_first1, it_index1 = iterator_next(it_index1),
                     it_index2 = it_first2, it_index2 = iterator_next(it_index2);
                     !iterator_equal(it_index1, it_last1) && 
                     !iterator_equal(it_index2, it_last2);
                     it_index1 = iterator_next(it_index1), 
                     it_index2 = iterator_next(it_index2)) {
                    (*bfun_op)(iterator_get_pointer(it_index1), iterator_get_pointer(it_index2), &b_result);
                    if (!b_result) {
                        break;
                    }
                }

                if (iterator_equal(it_index2, it_last2)) {
                    return it_first1;
                }
            }
        }
    }

    return it_last1;
}

/**
 * Looks in a range for the last subsequence that is identical to a specified sequence.
 */
forward_iterator_t algo_search_end(
    forward_iterator_t it_first1, forward_iterator_t it_last1,
    forward_iterator_t it_first2, forward_iterator_t it_last2)
{
    return algo_search_end_if(it_first1, it_last1, it_first2, it_last2, _fun_get_binary(it_first1, _EQUAL_FUN));
}

/**
 * Looks in a range for the last subsequence that is equivalent in a sense specified by a binary predicate.
 */
forward_iterator_t algo_search_end_if(
    forward_iterator_t it_first1, forward_iterator_t it_last1,
    forward_iterator_t it_first2, forward_iterator_t it_last2,
    bfun_t bfun_op)
{
    forward_iterator_t it_tmp;
    forward_iterator_t it_result;

    assert(_iterator_valid_range(it_first1, it_last1, _FORWARD_ITERATOR));
    assert(_iterator_valid_range(it_first2, it_last2, _FORWARD_ITERATOR));
    assert(_iterator_same_elem_type(it_first1, it_first2));

    if (iterator_equal(it_first2, it_last2)) {
        return it_last1;
    }

    it_result = it_tmp = it_last1;
    for (;;) {
        it_tmp = algo_search_if(it_first1, it_last1, it_first2, it_last2, bfun_op);
        if (iterator_equal(it_tmp, it_last1)) {
            return it_result;
        } else {
            it_result = it_tmp;
            it_first1 = iterator_next(it_tmp);
        }
    }
}

/**
 * Looks in a range for the last subsequence that is identical to a specified sequence.
 */
forward_iterator_t algo_find_end(
    forward_iterator_t it_first1, forward_iterator_t it_last1,
    forward_iterator_t it_first2, forward_iterator_t it_last2)
{
    return algo_search_end(it_first1, it_last1, it_first2, it_last2);
}

/**
 * Looks in a range for the last subsequence that is equivalent in a sense specified by a binary predicate.
 */
forward_iterator_t algo_find_end_if(
    forward_iterator_t it_first1, forward_iterator_t it_last1,
    forward_iterator_t it_first2, forward_iterator_t it_last2,
    bfun_t bfun_op)
{
    return algo_search_end_if(it_first1, it_last1, it_first2, it_last2, bfun_op);
}

/** eof **/

