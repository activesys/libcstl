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
/**
 * Create vector container that save specificed element type.
 * @param typename    specificed element type.
 * @return return vector pointer, if create vector container successfully, otherwise return NULL.
 * @remarks the format of specificed element type reference <<The libcstl Library Reference Manual>> Chapter 8.
 */
#define create_vector(...) _create_vector(#__VA_ARGS__) 

/**
 * Initialize vector container with mutiple specificed element.
 * @param pvec_vector    vector container.
 * @param t_count        specificed element number.
 * @param elem           specificed element.
 * @return void.
 * @remarks if pvec_vector == NULL, then the behavior is undefined. pvec_vector muse be created by create_vector(),
 *          otherwise the behavior is undefined. the size of vector is t_count after initialization. the capacity of
 *          vector is satisfied capacity assignment algorithm. all vector elements are specificed element.
 */
#define vector_init_elem(pvec_vector, t_count, elem) _vector_init_elem((pvec_vector), (t_count), (elem))

/**
 * Assign vector with specificed element.
 * @param pvec_vector  vector container.
 * @param t_count      element number.
 * @param elem         specificed element.
 * @return void.
 * @remarks if pvec_vector == NULL or vector is uninitialized, then the behavior is undefined. the type of specificed
 *          element and vector element type must be same, otherwise the behavior is undefined.
 */
#define vector_assign_elem(pvec_vector, t_count, elem) _vector_assign_elem((pvec_vector), (t_count), (elem))

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
/**
 * Initialize empty vector container.
 * @param pvec_vector    vector container.
 * @return void.
 * @remarks if pvec_vector == NULL, then the behavior is undefined. pvec_vector muse be created by create_vector(),
 *          otherwise the behavior is undefined. the size of vector and the capacity of vector is 0 after initialization.
 */
extern void vector_init(vector_t* pvec_vector);

/**
 * Initialize vector container with mutiple default element.
 * @param pvec_vector    vector container.
 * @param t_count        default element number.
 * @return void.
 * @remarks if pvec_vector == NULL, then the behavior is undefined. pvec_vector muse be created by create_vector(),
 *          otherwise the behavior is undefined. the size of vector is t_count after initialization. the capacity of
 *          vector is satisfied capacity assignment algorithm.
 */
extern void vector_init_n(vector_t* pvec_vector, size_t t_count);

/**
 * Initialize vector container with an exist vector container.
 * @param pvec_dest     destination vector container.
 * @param cpvec_src     source vector container.
 * @return void.
 * @remarks if pvec_dest == NULL or cpvec_src == NULL, then the behavior is undefined. pvec_dest must be created by
 *          create_vector() and cpvec_src must be initialized, otherwise the behavior is undefined. after initialization
 *          the size of pvec_dest is equal to the size of cpvec_src, and the capacity of pvec_dest is satisfied capacity
 *          assignment algorithm.
 */
extern void vector_init_copy(vector_t* pvec_dest, const vector_t* cpvec_src);

/**
 * Initialize vector container with an exist vector range.
 * @param pvec_dest     destination vector container.
 * @param it_begin      the begin iterator of range.
 * @param it_end        the end iterator of range.
 * @return void.
 * @remarks if pvec_dest == NULL, then the behavior is undefined. pvec_dest must be created by create_vector(), otherwise
 *          the behavior is undefined. after initialization the size of pvec_dest is equal to the size of range, and the
 *          capacity of pvec_dest is satisfied capacity assignment algorithm.
 */
extern void vector_init_copy_range(vector_t* pvec_dest, vector_iterator_t it_begin, vector_iterator_t it_end);

/**
 * Destroy vector container.
 * @param pvec_vector   vector container.
 * @return void.
 * @remarks if pvec_vector == NULL, then the behavior is undefined. the pvec_vector must be initialized or created by
 *          create_vector(), otherwise the behavior is undefined.
 */
extern void vector_destroy(vector_t* pvec_vector);

/**
 * Get vector element size.
 * @param cpvec_vector   vector container.
 * @return vector element size.
 * @remarks if cpvec_vector == NULL, then the behavior is undefined. cpvec_vector must be initialized, otherwise the
 *          behavior is undefined.
 */
extern size_t vector_size(const vector_t* cpvec_vector);

/**
 * Test vector is empty.
 * @param cpvec_vector   vector container.
 * @return if vector is empty return true, else return false.
 * @remarks if cpvec_vector == NULL, then the behavior is undefined. cpvec_vector must be initialized, otherwise the
 *          behavior is undefined.
 */
extern bool_t vector_empty(const vector_t* cpvec_vector);

/**
 * Return maximum element number.
 * @param cpvec_vector   vector container.
 * @return maximum number.
 * @remarks if cpvec_vector == NULL, then the behavior is undefined. cpvec_vector must be initialized, otherwise the
 *          behavior is undefined. this number is not fixed number.
 */
extern size_t vector_max_size(const vector_t* cpvec_vector);

/**
 * Get vector capacity.
 * @param cpvec_vector   vector container.
 * @return vector capacity.
 * @remarks if cpvec_vector == NULL, then the behavior is undefined. cpvec_vector must be initialized, otherwise the
 *          behavior is undefined.
 */
extern size_t vector_capacity(const vector_t* cpvec_vector);

/**
 * Set vector capacity.
 * @param pvec_vector   vector container.
 * @param t_reservesize  new capacity.
 * @return vector capacity.
 * @remarks if pvec_vector == NULL, then the behavior is undefined. pvec_vector must be initialized, otherwise the
 *          behavior is undefined. if t_reservesize > vector_capacity(), then t_reservesize is new capacity, otherwise
 *          capacity is not change.
 */
extern void vector_reserve(vector_t* pvec_vector, size_t t_reservesize);

/**
 * Test the two vectors are equal.
 * @param cpvec_first   first vector container.
 * @param cpvec_second  second vector container.
 * @return if first vector equal to second vector, then return true, else return false.
 * @remarks if cpvec_first == NULL or cpvec_second == NULL, then the behavior is undefined. the two vectors must be
 *          initialized, otherwise the behavior is undefined. if the two vectors are not same type, then return false.
 *          if cpvec_first == cpvec_second, then return true.
 */
extern bool_t vector_equal(const vector_t* cpvec_first, const vector_t* cpvec_second);

/**
 * Test the two vectors are unequal.
 * @param cpvec_first   first vector container.
 * @param cpvec_second  second vector container.
 * @return if first vector unequal to second vector, then return true, else return false.
 * @remarks if cpvec_first == NULL or cpvec_second == NULL, then the behavior is undefined. the two vectors must be
 *          initialized, otherwise the behavior is undefined. if the two vectors are not same type, then return true.
 *          if cpvec_first == cpvec_second, then return false.
 */
extern bool_t vector_not_equal(const vector_t* cpvec_first, const vector_t* cpvec_second);

/**
 * Test the first vector is less than the second vector.
 * @param cpvec_first   first vector container.
 * @param cpvec_second  second vector container.
 * @return if the first vector is less than the second vector, then return true, else return false.
 * @remarks if cpvec_first == NULL or cpvec_second == NULL, then the behavior is undefined. the two vectors must be
 *          initialized, otherwise the behavior is undefined. if the two vectors are not same type, the behavior is
 *          undefined. if cpvec_first == cpvec_second, then return false.
 */
extern bool_t vector_less(const vector_t* cpvec_first, const vector_t* cpvec_second);

/**
 * Test the first vector is less than or equal to the second vector.
 * @param cpvec_first   first vector container.
 * @param cpvec_second  second vector container.
 * @return if the first vector is less than or equal to the second vector, then return true, else return false.
 * @remarks if cpvec_first == NULL or cpvec_second == NULL, then the behavior is undefined. the two vectors must be
 *          initialized, otherwise the behavior is undefined. if the two vectors are not same type, the behavior is
 *          undefined. if cpvec_first == cpvec_second, then return true.
 */
extern bool_t vector_less_equal(const vector_t* cpvec_first, const vector_t* cpvec_second);

/**
 * Test the first vector is greater than the second vector.
 * @param cpvec_first   first vector container.
 * @param cpvec_second  second vector container.
 * @return if the first vector is greater than the second vector, then return true, else return false.
 * @remarks if cpvec_first == NULL or cpvec_second == NULL, then the behavior is undefined. the two vectors must be
 *          initialized, otherwise the behavior is undefined. if the two vectors are not same type, the behavior is
 *          undefined. if cpvec_first == cpvec_second, then return false.
 */
extern bool_t vector_greater(const vector_t* cpvec_first, const vector_t* cpvec_second);

/**
 * Test the first vector is greater than or equal to the second vector.
 * @param cpvec_first   first vector container.
 * @param cpvec_second  second vector container.
 * @return if the first vector is greater than or equal to the second vector, then return true, else return false.
 * @remarks if cpvec_first == NULL or cpvec_second == NULL, then the behavior is undefined. the two vectors must be
 *          initialized, otherwise the behavior is undefined. if the two vectors are not same type, the behavior is
 *          undefined. if cpvec_first == cpvec_second, then return true.
 */
extern bool_t vector_greater_equal(const vector_t* cpvec_first, const vector_t* cpvec_second);

/**
 * Assign vector element with an exist vector container.
 * @param pvec_dest     destination vector container.
 * @param cpvec_src     source vector container.
 * @return void.
 * @remarks if pvec_dest == NULL or cpvec_src == NULL, then the behavior is undefined. pvec_dest and cpvec_src must be
 *          initialized, otherwise the behavior is undefined. the element type of two vector must be same, otherwise
 *          the behavior is undefined. if the destination vector equal to source vector, then this function does nothing.
 */
extern void vector_assign(vector_t* pvec_dest, const vector_t* cpvec_src);

/**
 * Assign vector element with an exist vector container range.
 * @param pvec_dest     destination vector container.
 * @param it_begin      range begin.
 * @param it_end        range end.
 * @return void.
 * @remarks if pvec_dest == NULL, then the behavior is undefined. pvec_dest must be initialized, otherwise the behavior
 *          is undefined. the element type of vector and [it_begin, it_end) must be same, otherwise the behavior is
 *          undefined. if [it_begin, it_end) belong to the destination vector, the behavior is undefined.
 */
extern void vector_assign_range(vector_t* pvec_vector, vector_iterator_t it_begin, vector_iterator_t it_end);

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

