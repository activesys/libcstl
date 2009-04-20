/*
 *  The vector iterator interface for iterator module.
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
 *  Author Email: activesys.wb@gmail.com
 *                activesys@sina.com.cn
 */

#ifndef _CSTL_VECTOR_ITERATOR_H
#define _CSTL_VECTOR_ITERATOR_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
typedef iterator_t vector_iterator_t;
typedef iterator_t vector_reverse_iterator_t;
struct _tagvector;

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: create_vector_iterator
 *        Parameters: void
 *           Returns: vector_iterator_t
 *                          new vector iterator.
 *       Description: create new vector iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern vector_iterator_t create_vector_iterator(void);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _vector_iterator_equal
 *        Parameters: in) cpt_vector: const struct _tagvector*
 *                            the vector pointer.
 *                    in) cpt_iterator: const vector_iterator_t*
 *                            the iterator pointer for getting value.
 *                    in) t_iterator: vector_iterator_t
 *                            the iterator.
 *           Returns: bool_t
 *                            if the first iterator equal the second.
 *       Description: test if the first iterator equal the second.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t _vector_iterator_equal(
    const struct _tagvector* cpt_vector,
    const vector_iterator_t* cpt_iterator,
    vector_iterator_t t_iterator);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _vector_iterator_get_value
 *        Parameters: in) cpt_vector: const struct _tagvector*
 *                            the vector pointer.
 *                    in) cpt_iterator: const vector_iterator_t*
 *                            the iterator pointer for getting value.
 *                    modify)pv_value: void*
 *                            the value pointer.
 *           Returns: void
 *       Description: get the value of current vector iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern void _vector_iterator_get_value(
    const struct _tagvector* cpt_vector,
    const vector_iterator_t* cpt_iterator, 
    void* pv_value);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _vector_iterator_set_value
 *        Parameters: in) cpt_vector: const struct _tagvector*
 *                            the vector pointer.
 *                    in) cpt_iterator: const vector_iterator_t*
 *                            the iterator pointer for getting value.
 *                    in) cpv_value: const void*
 *                            the value pointer.
 *           Returns: void
 *       Description: set the value of current vector iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern void _vector_iterator_set_value(
    const struct _tagvector* cpt_vector,
    const vector_iterator_t* cpt_iterator, 
    const void* cpv_value);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _vector_iterator_get_pointer
 *        Parameters: in) cpt_vector: const struct _tagvector*
 *                            the vector pointer.
 *                    in) cpt_iterator: const vector_iterator_t*
 *                            the iterator pointer for getting value.
 *           Returns: const void*
 *       Description: get the iterator pointer.
 *
 * ----------------------------------------------------------------------------
 */
extern const void* _vector_iterator_get_pointer(
    const struct _tagvector* cpt_vector,
    const vector_iterator_t* cpt_iterator); 

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _vector_iterator_next
 *        Parameters: in) cpt_vector: const struct _tagvector*
 *                            the vector pointer.
 *                    in) pt_iterator: vector_iterator_t*
 *                            the iterator pointer for go to next position.
 *           Returns: void
 *       Description: to the next position of current vector iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern void _vector_iterator_next(
    const struct _tagvector* cpt_vector, vector_iterator_t* pt_iterator);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _vector_iterator_prev
 *        Parameters: in) cpt_vector: const struct _tagvector*
 *                            the vector pointer.
 *                    in) pt_iterator: vector_iterator_t*
 *                            the iterator pointer for go to previous position.
 *           Returns: void
 *       Description: to the previous position of current vector iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern void _vector_iterator_prev(
    const struct _tagvector* cpt_vector, vector_iterator_t* pt_iterator);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _vector_iterator_at
 *        Parameters: in) cpt_vector: const struct _tagvector*
 *                            the vector pointer.
 *                    in) cpt_iterator: const vector_iterator_t*
 *                            the iterator pointer for getting value.
 *                    in) un_index: unsigned int
 *                            the index n.
 *           Returns: void*
 *       Description: get the value of current vector iterator with index n.
 *
 * ----------------------------------------------------------------------------
 */
extern void* _vector_iterator_at(
    const struct _tagvector* cpt_vector, 
    const vector_iterator_t* cpt_iterator,
    unsigned int un_index);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _vector_iterator_next_n
 *        Parameters: in) cpt_vector: const struct _tagvector*
 *                            the vector pointer.
 *                    in) pt_iterator: vector_iterator_t*
 *                            the iterator pointer for go to next position.
 *                    in) n_step: int
 *                            the step of next.
 *           Returns: void
 *       Description: to the next position of current vector iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern void _vector_iterator_next_n(
    const struct _tagvector* cpt_vector, 
    vector_iterator_t* pt_iterator,
    int n_step);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _vector_iterator_prev_n
 *        Parameters: in) cpt_vector: const struct _tagvector*
 *                            the vector pointer.
 *                    in) pt_iterator: vector_iterator_t*
 *                            the iterator pointer for go to previous position.
 *                    in) n_step: int
 *                            the step of previous.
 *           Returns: void
 *       Description: to the previous n position of current vector iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern void _vector_iterator_prev_n(
    const struct _tagvector* cpt_vector, 
    vector_iterator_t* pt_iterator,
    int n_step);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _vector_iterator_minus
 *        Parameters: in) cpt_vector: const struct _tagvector*
 *                            the vector pointer.
 *                    in) cpt_iterator: const vector_iterator_t*
 *                            the iterator pointer for getting value.
 *                    in) t_iterator: vector_iterator_t
 *                            the iterator.
 *           Returns: int
 *                            the distance of two iterator
 *       Description: compute the distance of two iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern int _vector_iterator_minus(
    const struct _tagvector* cpt_vector,
    const vector_iterator_t* cpt_iterator, 
    vector_iterator_t t_iterator);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _vector_iterator_less
 *        Parameters: in) cpt_vector: const struct _tagvector*
 *                            the vector pointer.
 *                    in) cpt_iterator: const vector_iterator_t*
 *                            the iterator pointer for getting value.
 *                    in) t_iterator: vector_iterator_t
 *                            the iterator.
 *           Returns: bool_t
 *                            if the first iterator less then the second.
 *       Description: test if the first iterator less then the second.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t _vector_iterator_less(
    const struct _tagvector* cpt_vector,
    const vector_iterator_t* cpt_iterator,
    vector_iterator_t t_iterator);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _vector_iterator_before
 *        Parameters: in) cpt_iteratorfirst: const vector_iterator_t*
 *                            the first iterator.
 *                    in) cpt_iteratorsecond: const vector_iterator_t*
 *                            the second iterator.
 *           Returns: bool_t
 *       Description: test if the first iterator before the second.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t _vector_iterator_before(
    const vector_iterator_t* cpt_iteratorfirst, 
    const vector_iterator_t* cpt_iteratorsecond);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_VECTOR_ITERATOR_H */
/** eof **/

