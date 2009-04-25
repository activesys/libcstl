/*
 *  The iterator interface of basic_string.
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

#ifndef _CSTL_BASIC_STRING_ITERATOR_H
#define _CSTL_BASIC_STRING_ITERATOR_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
typedef iterator_t basic_string_iterator_t;
typedef iterator_t basic_string_reverse_iterator_t;
struct _tagbasicstring;

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: create_basic_string_iterator
 *        Parameters: void
 *           Returns: basic_string_iterator_t
 *                          new basic_string iterator.
 *       Description: create new basic_string iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern basic_string_iterator_t create_basic_string_iterator(void);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _basic_string_iterator_equal
 *        Parameters: in) cpt_basic_string: const struct _tagbasicstring*
 *                            the basic_string pointer.
 *                    in) cpt_iterator: const basic_string_iterator_t*
 *                            the iterator pointer for getting value.
 *                    in) t_iterator: basic_string_iterator_t
 *                            the iterator.
 *           Returns: bool_t
 *                            if the first iterator equal the second.
 *       Description: test if the first iterator equal the second.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t _basic_string_iterator_equal(
    const struct _tagbasicstring* cpt_basic_string,
    const basic_string_iterator_t* cpt_iterator,
    basic_string_iterator_t t_iterator);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _basic_string_iterator_get_value
 *        Parameters: in) cpt_basic_string: const struct _tagbasicstring*
 *                            the basic_string pointer.
 *                    in) cpt_iterator: const basic_string_iterator_t*
 *                            the iterator pointer for getting value.
 *                    modify)pv_value: void*
 *                            the value pointer.
 *           Returns: void
 *       Description: get the value of current basic_string iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern void _basic_string_iterator_get_value(
    const struct _tagbasicstring* cpt_basic_string,
    const basic_string_iterator_t* cpt_iterator, 
    void* pv_value);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _basic_string_iterator_set_value
 *        Parameters: in) cpt_basic_string: const struct _tagbasicstring*
 *                            the basic_string pointer.
 *                    in) cpt_iterator: const basic_string_iterator_t*
 *                            the iterator pointer for getting value.
 *                    in) cpv_value: const void*
 *                            the value pointer.
 *           Returns: void
 *       Description: set the value of current basic_string iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern void _basic_string_iterator_set_value(
    const struct _tagbasicstring* cpt_basic_string,
    const basic_string_iterator_t* cpt_iterator, 
    const void* cpv_value);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _basic_string_iterator_get_pointer
 *        Parameters: in) cpt_basic_string: const struct _tagbasicstring*
 *                            the basic_string pointer.
 *                    in) cpt_iterator: const basic_string_iterator_t*
 *                            the iterator pointer for getting value.
 *           Returns: const void*
 *       Description: get the iterator pointer.
 *
 * ----------------------------------------------------------------------------
 */
extern const void* _basic_string_iterator_get_pointer(
    const struct _tagbasicstring* cpt_basic_string,
    const basic_string_iterator_t* cpt_iterator); 

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _basic_string_iterator_next
 *        Parameters: in) cpt_basic_string: const struct _tagbasicstring*
 *                            the basic_string pointer.
 *                    in) pt_iterator: basic_string_iterator_t*
 *                            the iterator pointer for go to next position.
 *           Returns: void
 *       Description: to the next position of current basic_string iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern void _basic_string_iterator_next(
    const struct _tagbasicstring* cpt_basic_string, 
    basic_string_iterator_t* pt_iterator);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _basic_string_iterator_prev
 *        Parameters: in) cpt_basic_string: const struct _tagbasicstring*
 *                            the basic_string pointer.
 *                    in) pt_iterator: basic_string_iterator_t*
 *                            the iterator pointer for go to previous position.
 *           Returns: void
 *       Description: to the previous position of current basic_string iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern void _basic_string_iterator_prev(
    const struct _tagbasicstring* cpt_basic_string, 
    basic_string_iterator_t* pt_iterator);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _basic_string_iterator_at
 *        Parameters: in) cpt_basic_string: const struct _tagbasicstring*
 *                            the basic_string pointer.
 *                    in) cpt_iterator: const basic_string_iterator_t*
 *                            the iterator pointer for getting value.
 *                    in) un_index: unsigned int
 *                            the index n.
 *           Returns: void*
 *       Description: get the value of current basic_string iterator with index n.
 *
 * ----------------------------------------------------------------------------
 */
extern void* _basic_string_iterator_at(
    const struct _tagbasicstring* cpt_basic_string, 
    const basic_string_iterator_t* cpt_iterator,
    unsigned int un_index);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _basic_string_iterator_next_n
 *        Parameters: in) cpt_basic_string: const struct _tagbasicstring*
 *                            the basic_string pointer.
 *                    in) pt_iterator: basic_string_iterator_t*
 *                            the iterator pointer for go to next position.
 *                    in) n_step: int
 *                            the step of next.
 *           Returns: void
 *       Description: to the next position of current basic_string iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern void _basic_string_iterator_next_n(
    const struct _tagbasicstring* cpt_basic_string, 
    basic_string_iterator_t* pt_iterator,
    int n_step);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _basic_string_iterator_prev_n
 *        Parameters: in) cpt_basic_string: const struct _tagbasicstring*
 *                            the basic_string pointer.
 *                    in) pt_iterator: basic_string_iterator_t*
 *                            the iterator pointer for go to previous position.
 *                    in) n_step: int
 *                            the step of previous.
 *           Returns: void
 *       Description: to the previous n position of current basic_string iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern void _basic_string_iterator_prev_n(
    const struct _tagbasicstring* cpt_basic_string, 
    basic_string_iterator_t* pt_iterator,
    int n_step);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _basic_string_iterator_minus
 *        Parameters: in) cpt_basic_string: const struct _tagbasicstring*
 *                            the basic_string pointer.
 *                    in) cpt_iterator: const basic_string_iterator_t*
 *                            the iterator pointer for getting value.
 *                    in) t_iterator: basic_string_iterator_t
 *                            the iterator.
 *           Returns: int
 *                            the distance of two iterator
 *       Description: compute the distance of two iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern int _basic_string_iterator_minus(
    const struct _tagbasicstring* cpt_basic_string,
    const basic_string_iterator_t* cpt_iterator, 
    basic_string_iterator_t t_iterator);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _basic_string_iterator_less
 *        Parameters: in) cpt_basic_string: const struct _tagbasicstring*
 *                            the basic_string pointer.
 *                    in) cpt_iterator: const basic_string_iterator_t*
 *                            the iterator pointer for getting value.
 *                    in) t_iterator: basic_string_iterator_t
 *                            the iterator.
 *           Returns: bool_t
 *                            if the first iterator less then the second.
 *       Description: test if the first iterator less then the second.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t _basic_string_iterator_less(
    const struct _tagbasicstring* cpt_basic_string,
    const basic_string_iterator_t* cpt_iterator,
    basic_string_iterator_t t_iterator);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _basic_string_iterator_before
 *        Parameters: in) cpt_iteratorfirst: const basic_string_iterator_t*
 *                           first basic_string iterator pointer.
 *                    in) cpt_iteratorsecond: const basic_string_iterator_t*
 *                           second basic_string iterator pointer.
 *           Returns: bool_t
 *       Description: test the first iterator before the second one.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t _basic_string_iterator_before(
    const basic_string_iterator_t* cpt_iteratorfirst, 
    const basic_string_iterator_t* cpt_iteratorsecond);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_BASIC_STRING_ITERATOR_H */
/** eof **/

