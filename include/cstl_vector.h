/*
 *  The user interface of vector.
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

#ifndef _CSTL_VECTOR_H
#define _CSTL_VECTOR_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/* create new vector with specific type */
#define create_vector(type)\
    _create_vector(sizeof(type), #type) 
/* initialize */
#define vector_init_elem(pt_vector, t_count, elem)\
    _vector_init_elem((pt_vector), (t_count), (elem))
/* assign */
#define vector_assign_elem(pt_vector, t_count, elem)\
    _vector_assign_elem((pt_vector), (t_count), (elem))
/* push back */
#define vector_push_back(pt_vector, elem)\
    _vector_push_back((pt_vector), (elem))
/* resize */
#define vector_resize_elem(pt_vector, t_resize, elem)\
    _vector_resize_elem((pt_vector), (t_resize), (elem))
/* insert */
#define vector_insert(pt_vector, t_pos, elem)\
    _vector_insert_n((pt_vector), (t_pos), 1, (elem))
#define vector_insert_n(pt_vector, t_pos, t_count, elem)\
    _vector_insert_n((pt_vector), (t_pos), (t_count), (elem))

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: vector_init
 *        Parameters: in) pt_vector: vector_t*
 *           Returns: void
 *       Description: initialize the vector.
 *
 * ----------------------------------------------------------------------------
 */
extern void vector_init(vector_t* pt_vector);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: vector_init_n
 *        Parameters: in) pt_vector: vector_t*
 *                    in) t_count: size_t
 *                          element count.
 *           Returns: void
 *       Description: initialize the vector.
 *
 * ----------------------------------------------------------------------------
 */
extern void vector_init_n(vector_t* pt_vector, size_t t_count);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: vector_destroy
 *        Parameters: in) pt_vector: vector_t*
 *           Returns: void
 *       Description: destroy the vector.
 *
 * ----------------------------------------------------------------------------
 */
extern void vector_destroy(vector_t* pt_vector);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: vector_init_copy
 *        Parameters: in) pt_vectordest: vector_t*
 *                          the dest vector.
 *                    in) cpt_vectorsrc: const vector_t*
 *                          the source vector.
 *           Returns: void
 *       Description: the vector copy constructor.
 *
 * ----------------------------------------------------------------------------
 */
extern void vector_init_copy(
    vector_t* pt_vectordest, const vector_t* cpt_vectorsrc);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: vector_init_copy_range
 *        Parameters: in) pt_vectordest: vector_t*
 *                          the dest vector.
 *                    in) t_begin: vector_iterator_t
 *                          the begin iterator.
 *                    in) t_end: vector_iterator_t
 *                          the end iterator.
 *           Returns: void
 *       Description: the vector copy constructor with specific range.
 *
 * ----------------------------------------------------------------------------
 */
extern void vector_init_copy_range(
    vector_t* pt_vectordest, 
    vector_iterator_t t_begin, 
    vector_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: vector_size
 *        Parameters: in) cpt_vector: const vector_t*
 *                          the dest vector.
 *           Returns: size_t
 *       Description: get the vector size.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t vector_size(const vector_t* cpt_vector);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: vector_empty
 *        Parameters: in) cpt_vector: const vector_t*
 *                          the dest vector.
 *           Returns: bool_t
 *       Description: if the vector is empty.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t vector_empty(const vector_t* cpt_vector);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: vector_max_size
 *        Parameters: in) cpt_vector: const vector_t*
 *                          the dest vector.
 *           Returns: size_t
 *       Description: get the maximum capacity of vector.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t vector_max_size(const vector_t* cpt_vector);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: vector_capacity
 *        Parameters: in) cpt_vector: const vector_t*
 *                          the dest vector.
 *           Returns: size_t
 *       Description: get the capacity of vector with out reallocation.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t vector_capacity(const vector_t* cpt_vector);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: vector_reserve
 *        Parameters: in) pt_vector: vector_t*
 *                          the dest vector.
 *                    in) t_reservesize: size_t
 *                          the enlarge capacity.
 *           Returns: void
 *       Description: enlarge capacity if not enough.
 *
 * ----------------------------------------------------------------------------
 */
extern void vector_reserve(vector_t* pt_vector, size_t t_reservesize);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: vector_equal
 *        Parameters: in) cpt_vectorfirst: const vector_t*
 *                          the first vector.
 *                    in) cpt_vectorsecond: const vector_t*
 *                          the second vector.
 *           Returns: bool_t
 *       Description: return whether first vector equal to second vector.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t vector_equal(
    const vector_t* cpt_vectorfirst, const vector_t* cpt_vectorsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: vector_not_equal
 *        Parameters: in) cpt_vectorfirst: const vector_t*
 *                          the first vector.
 *                    in) cpt_vectorsecond: const vector_t*
 *                          the second vector.
 *           Returns: bool_t
 *       Description: return whether first vector not equal to second vector.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t vector_not_equal(
    const vector_t* cpt_vectorfirst, const vector_t* cpt_vectorsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: vector_less
 *        Parameters: in) cpt_vectorfirst: const vector_t*
 *                          the first vector.
 *                    in) cpt_vectorsecond: const vector_t*
 *                          the second vector.
 *           Returns: bool_t
 *       Description: return whether first vector less then second vector.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t vector_less(
    const vector_t* cpt_vectorfirst, const vector_t* cpt_vectorsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: vector_great
 *        Parameters: in) cpt_vectorfirst: const vector_t*
 *                          the first vector.
 *                    in) cpt_vectorsecond: const vector_t*
 *                          the second vector.
 *           Returns: bool_t
 *       Description: return whether first vector greater then second vector.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t vector_great(
    const vector_t* cpt_vectorfirst, const vector_t* cpt_vectorsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: vector_less_equal
 *        Parameters: in) cpt_vectorfirst: const vector_t*
 *                          the first vector.
 *                    in) cpt_vectorsecond: const vector_t*
 *                          the second vector.
 *           Returns: bool_t
 *       Description: return whether first vector less then or equal to the 
 *                    second vector.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t vector_less_equal(
    const vector_t* cpt_vectorfirst, const vector_t* cpt_vectorsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: vector_great_equal
 *        Parameters: in) cpt_vectorfirst: const vector_t*
 *                          the first vector.
 *                    in) cpt_vectorsecond: const vector_t*
 *                          the second vector.
 *           Returns: bool_t
 *       Description: return whether first vector greater then or equal to the
 *                    second vector.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t vector_great_equal(
    const vector_t* cpt_vectorfirst, const vector_t* cpt_vectorsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: vector_assign
 *        Parameters: in) pt_vectordest: vector_t*
 *                          the dest vector.
 *                    in) cpt_vectorsrc: const vector_t*
 *                          the source vector.
 *           Returns: void
 *       Description: the assignment operator.
 *
 * ----------------------------------------------------------------------------
 */
extern void vector_assign(
    vector_t* pt_vectordest, const vector_t* cpt_vectorsrc);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: vector_assign_range
 *        Parameters: in) pt_vector: vector_t*
 *                          the vector for assign.
 *                    in) t_begin: vector_iterator_t
 *                          the begin iterator.
 *                    in) t_end: vector_iterator_t
 *                          the end iterator.
 *           Returns: void
 *       Description: assign the elements of range [t_begin, t_end)
 *
 * ----------------------------------------------------------------------------
 */
extern void vector_assign_range(
    vector_t* pt_vector, 
    vector_iterator_t t_begin,
    vector_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: vector_swap
 *        Parameters: in) pt_vectorfirst: vector_t*
 *                          the first vector.
 *                    in) pt_vectorsecond: vector_t*
 *                          the second vector.
 *           Returns: void
 *       Description: swap the datas of first vector and second vector.
 *
 * ----------------------------------------------------------------------------
 */
extern void vector_swap(vector_t* pt_vectorfirst, vector_t* pt_vectorsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: vector_at
 *        Parameters: in) cpt_vector: const vector_t*
 *                          the vector.
 *                    in) t_pos: size_t
 *                          the element pos.
 *           Returns: void*
 *                          the element pointer.
 *       Description: return the element with the n_elempos.
 *
 * ----------------------------------------------------------------------------
 */
extern void* vector_at(const vector_t* cpt_vector, size_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: vector_front
 *        Parameters: in) cpt_vector: const vector_t*
 *                          the vector.
 *           Returns: void*
 *       Description: return the first element.
 *
 * ----------------------------------------------------------------------------
 */
extern void* vector_front(const vector_t* cpt_vector);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: vector_back
 *        Parameters: in) cpt_vector: const vector_t*
 *                          the vector.
 *           Returns: void*
 *       Description: return the last element.
 *
 * ----------------------------------------------------------------------------
 */
extern void* vector_back(const vector_t* cpt_vector);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: vector_begin
 *        Parameters: in) cpt_vector: const vector_t*
 *                          the vector.
 *           Returns: vector_iterator_t
 *       Description: return the random access iterator for the first element.
 *
 * ----------------------------------------------------------------------------
 */
extern vector_iterator_t vector_begin(const vector_t* cpt_vector);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: vector_end
 *        Parameters: in) cpt_vector: const vector_t*
 *                          the vector.
 *           Returns: vector_iterator_t
 *       Description: return the random access iterator for the last element.
 *
 * ----------------------------------------------------------------------------
 */
extern vector_iterator_t vector_end(const vector_t* cpt_vector);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: vector_rbegin
 *        Parameters: in) cpt_vector: const vector_t*
 *                          the vector.
 *           Returns: vector_reverse_iterator_t
 *       Description: return the reverse iterator for the first element of the
 *                    reverse iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern vector_reverse_iterator_t vector_rbegin(const vector_t* cpt_vector);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: vector_rend
 *        Parameters: in) cpt_vector: const vector_t*
 *                          the vector.
 *           Returns: vector_reverse_iterator_t
 *       Description: return the reverse iterator for the last element of the
 *                    reverse iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern vector_reverse_iterator_t vector_rend(const vector_t* cpt_vector);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: vector_insert_range
 *        Parameters: in) pt_vector: vector_t*
 *                          the vector.
 *                    in) t_pos: vector_iterator_t
 *                          the insert position.
 *                    in) t_begin: vector_iterator_t
 *                          the begin insert position.
 *                    in) t_end: vector_iterator_t
 *                          the end insert position.
 *           Returns: void
 *       Description: insert at iterator position t_pos a copy of all elements 
 *                    of range [t_begin, t_end) and return nothing.
 *
 * ----------------------------------------------------------------------------
 */
extern void vector_insert_range(
    vector_t* pt_vector, 
    vector_iterator_t t_pos, 
    vector_iterator_t t_begin, 
    vector_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: vector_pop_back
 *        Parameters: in) pt_vector: vector_t*
 *                          the vector.
 *           Returns: void
 *       Description: remove the last element and does not return it.
 *
 * ----------------------------------------------------------------------------
 */
extern void vector_pop_back(vector_t* pt_vector);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: vector_erase
 *        Parameters: in) pt_vector: vector_t*
 *                          the vector.
 *                    in) t_pos: vector_iterator_t
 *                          the erase position
 *           Returns: vector_iterator_t
 *       Description: remove the element at the iterator position t_pos and 
 *                    return the position of next element.
 *
 * ----------------------------------------------------------------------------
 */
extern vector_iterator_t vector_erase(
    vector_t* pt_vector, vector_iterator_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: vector_erase_range
 *        Parameters: in) pt_vector: vector_t*
 *                          the vector.
 *                    in) t_begin: vector_iterator_t
 *                          the begin position of erase range
 *                    in) t_end: vector_iterator_t
 *                          the end position of erase range
 *           Returns: vector_iterator_t
 *       Description: remove all elements of the range [t_begin, t_end) and 
 *                    return the position of next element.
 *
 * ----------------------------------------------------------------------------
 */
extern vector_iterator_t vector_erase_range(
    vector_t* pt_vector, vector_iterator_t t_begin, vector_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: vector_resize
 *        Parameters: in) pt_vector: vector_t*
 *                          the vector.
 *                    in) t_resize: size_t
 *                          the new size of vector.
 *           Returns: void
 *       Description: change the number of elements to t_resize, if the size
 *                    grows new element create with the default 0.
 *
 * ----------------------------------------------------------------------------
 */
extern void vector_resize(vector_t* pt_vector, size_t t_resize);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: vector_clear
 *        Parameters: in) pt_vector: vector_t*
 *                          the vector.
 *           Returns: void
 *       Description: remove all elements.
 *
 * ----------------------------------------------------------------------------
 */
extern void vector_clear(vector_t* pt_vector);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_VECTOR_H */
/** eof **/

