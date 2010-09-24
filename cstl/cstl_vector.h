/*
 *  The user interface of vector.
 *  Copyright (C)  2008,2009,2010  Wangbo
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

#ifndef _CSTL_VECTOR_H
#define _CSTL_VECTOR_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/*
 * Creation and initialization vector_t.
 */
#define create_vector(...) _create_vector(#__VA_ARGS__) 
#define vector_init_elem(pt_vector, t_count, elem)\
    _vector_init_elem((pt_vector), (t_count), (elem))

/*
 * The assignment operator of vector_t.
 */
#define vector_assign_elem(pt_vector, t_count, elem)\
    _vector_assign_elem((pt_vector), (t_count), (elem))

/*
 * Insert a new element at the end of vector_t.
 */
#define vector_push_back(pt_vector, elem)\
    _vector_push_back((pt_vector), (elem))

/*
 * Append elements or erase elements from the end, as necessary to make the vector_t's
 * size exactly t_resize elements.
 */
#define vector_resize_elem(pt_vector, t_resize, elem)\
    _vector_resize_elem((pt_vector), (t_resize), (elem))

/*
 * Insert t_count copys of element befor position t_pos.
 */
#define vector_insert(pt_vector, t_pos, elem)\
    _vector_insert_n((pt_vector), (t_pos), 1, (elem))
#define vector_insert_n(pt_vector, t_pos, t_count, elem)\
    _vector_insert_n((pt_vector), (t_pos), (t_count), (elem))

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * Initialization and destroy operation of vector_t.
 */
extern void vector_init(vector_t* pt_vector);
extern void vector_init_n(vector_t* pt_vector, size_t t_count);
extern void vector_init_copy(vector_t* pt_vectordest, const vector_t* cpt_vectorsrc);
extern void vector_init_copy_range(
    vector_t* pt_vectordest, vector_iterator_t t_begin, vector_iterator_t t_end);
extern void vector_destroy(vector_t* pt_vector);

/*
 * Get the size and largest possible size of vector_t.
 */
extern size_t vector_size(const vector_t* cpt_vector);
extern bool_t vector_empty(const vector_t* cpt_vector);
extern size_t vector_max_size(const vector_t* cpt_vector);

/*
 * Capacity operation.
 */
extern size_t vector_capacity(const vector_t* cpt_vector);
extern void vector_reserve(vector_t* pt_vector, size_t t_reservesize);

/*
 * The relationship operator of vector_t.
 */
extern bool_t vector_equal(
    const vector_t* cpt_vectorfirst, const vector_t* cpt_vectorsecond);
extern bool_t vector_not_equal(
    const vector_t* cpt_vectorfirst, const vector_t* cpt_vectorsecond);
extern bool_t vector_less(
    const vector_t* cpt_vectorfirst, const vector_t* cpt_vectorsecond);
extern bool_t vector_greater(
    const vector_t* cpt_vectorfirst, const vector_t* cpt_vectorsecond);
extern bool_t vector_less_equal(
    const vector_t* cpt_vectorfirst, const vector_t* cpt_vectorsecond);
extern bool_t vector_greater_equal(
    const vector_t* cpt_vectorfirst, const vector_t* cpt_vectorsecond);

/*
 * The assignment operator of vector_t.
 */
extern void vector_assign(
    vector_t* pt_vectordest, const vector_t* cpt_vectorsrc);
extern void vector_assign_range(
    vector_t* pt_vector, vector_iterator_t t_begin, vector_iterator_t t_end);

/*
 * Swap the contents of two vector_ts.
 */
extern void vector_swap(vector_t* pt_vectorfirst, vector_t* pt_vectorsecond);

/*
 * Access element of vector_t.
 */
extern void* vector_at(const vector_t* cpt_vector, size_t t_pos);
extern void* vector_front(const vector_t* cpt_vector);
extern void* vector_back(const vector_t* cpt_vector);

/*
 * Iterator support of vector_t.
 */
extern vector_iterator_t vector_begin(const vector_t* cpt_vector);
extern vector_iterator_t vector_end(const vector_t* cpt_vector);
/* private interface */
extern vector_reverse_iterator_t vector_rbegin(const vector_t* cpt_vector);
extern vector_reverse_iterator_t vector_rend(const vector_t* cpt_vector);

/*
 * Insert the range [t_begin, t_end) before position t_pos.
 */
extern void vector_insert_range(
    vector_t* pt_vector, vector_iterator_t t_pos,
    vector_iterator_t t_begin, vector_iterator_t t_end);

/*
 * Erase element form vector_t.
 */
extern void vector_pop_back(vector_t* pt_vector);
extern vector_iterator_t vector_erase(vector_t* pt_vector, vector_iterator_t t_pos);
extern vector_iterator_t vector_erase_range(
    vector_t* pt_vector, vector_iterator_t t_begin, vector_iterator_t t_end);
extern void vector_clear(vector_t* pt_vector);

/*
 * Reset the vector_t size.
 */
extern void vector_resize(vector_t* pt_vector, size_t t_resize);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_VECTOR_H */
/** eof **/

