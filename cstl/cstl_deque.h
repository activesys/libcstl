/*
 *  The user interface of deque.
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

#ifndef _CSTL_DEQUE_H_
#define _CSTL_DEQUE_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/**
 * Create deque container.
 * @param ...     element type name.
 * @return if create deque successfully, then return deque pointer, else return NULL.
 * @remarks element type name should be C builtin type name, libcstl builtin typename or registed user defined type name,
 *          otherwise the function will return NULL.
 */
#define create_deque(...) _create_deque(#__VA_ARGS__)

/**
 * Initialize deque with specified element.
 * @param pdeq_deque   uninitialized deque container.
 * @param t_count      element number.
 * @param elem         specificed element.
 * @return void
 * @remarks if pdeq_deque == NULL, then the behavior is undefined. the type of specificed element and deque element
 *          type must be same, otherwise the behavior is undefined. deque container must be created by create_deque,
 *          otherwise the behavior is undefined.
 */
#define deque_init_elem(pdeq_deque, t_count, elem) _deque_init_elem((pdeq_deque), (t_count), (elem))

/**
 * Assign deque with specificed element.
 * @param pdeq_deque   deque container.
 * @param t_count      element number.
 * @param elem         specificed element.
 * @return void.
 * @remarks if pdeq_deque == NULL or deque is uninitialized, then the behavior is undefined. the type of specificed
 *          element and deque element type must be same, otherwise the behavior is undefined.
 */
#define deque_assign_elem(pdeq_deque, t_count, elem) _deque_assign_elem((pdeq_deque), (t_count), (elem))

/**
 * Add specificed element at the end of deque container. 
 * @param pdeq_deque    deque container.
 * @param val_elemdeque  specificed element.
 * @return void.
 * @remarks if pdeq_deque == NULL or deque is uninitialized, then the behavior is undefined. the type of specificed
 *          element and deque element type must be same, otherwise the behavior is undefined.
 */
#define deque_push_back(pdeq_deque, elem) _deque_push_back((pdeq_deque), (elem))

/**
 * Add specificed element at the begin of deque container. 
 * @param pdeq_deque    deque container.
 * @param val_elemdeque  specificed element.
 * @return void.
 * @remarks if pdeq_deque == NULL or deque is uninitialized, then the behavior is undefined. the type of specificed
 *          element and deque element type must be same, otherwise the behavior is undefined.
 */
#define deque_push_front(pdeq_deque, elem) _deque_push_front((pdeq_deque), (elem))

/**
 * Reset the size of deque elements.
 * @param pdeq_deque    deque container.
 * @param t_resize      new size of deque elements.
 * @param ...           specificed element.
 * @return void.
 * @remarks if pdeq_deque == NULL or deque is uninitialized, then the behavior is undefined. the type of specificed
 *          element and deque element type must be same, otherwise the behavior is undefined. if t_resize less than
 *          current deque size, then erase elmement from the end. if t_resize greater than current deque size, then
 *          append elements to the end, and the element is specificed element.
 */
#define deque_resize_elem(pdeq_deque, t_resize, elem) _deque_resize_elem((pdeq_deque), (t_resize), (elem))

/**
 * Insert one copy of element befor specificed position.
 * @param pdeq_deque    deque container.
 * @param it_pos        insert position.
 * @param elem          specificed element.
 * @return position refereced the first inserted elements.
 * @remarks if pdeq_deque == NULL or deque is uninitialized, then the behavior is undefined. the it_pos must be invalid
 *          iterator of deque container, otherwise the behavior is undefined. the type of specificed element and deque
 *          element type must be same, otherwise the behavior is undefined.
 */
#define deque_insert(pdeq_deque, it_pos, elem) _deque_insert_n((pdeq_deque), (it_pos), 1, (elem))

/**
 * Insert multiple copys of element befor specificed position.
 * @param pdeq_deque    deque container.
 * @param it_pos        insert position.
 * @param t_count       element number.
 * @param elem          specificed element.
 * @return position refereced the first inserted elements.
 * @remarks if pdeq_deque == NULL or deque is uninitialized, then the behavior is undefined. the it_pos must be invalid
 *          iterator of deque container, otherwise the behavior is undefined. the type of specificed element and deque
 *          element type must be same, otherwise the behavior is undefined.
 */
#define deque_insert_n(pdeq_deque, it_pos, t_count, elem) _deque_insert_n((pdeq_deque), (it_pos), (t_count), (elem))

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Initialize an empty deque container
 * @param pdeq_deque   deque container.
 * @return void.
 * @remarks if pdeq_deque == NULL, then the behavior is undefined. pdeq_deque must be created by create_deque(), otherwise
 *          the behavior is undefine.
 */
extern void deque_init(deque_t* pdeq_deque);

/**
 * Initialize deque container with specific size.
 * @param pdeq_deque   deque container.
 * @param t_count      the number of default elements.
 * @return void.
 * @remarks if pdeq_deque == NULL, then the behavior is undefined. pdeq_deque must be created by create_deque(), otherwise
 *          the behavior is undefine.
 */
extern void deque_init_n(deque_t* pdeq_deque, size_t t_count);

/**
 * Destroy deque container.
 * @param pdeq_deque   deque container.
 * @return void.
 * @remraks if pdeq_deque == NULLL, then the behavior is undefined. pdeq_deque must be initialized or created by create_deque(),
 *          otherwise the behavior is undefined.
 */
extern void deque_destroy(deque_t* pdeq_deque);

/**
 * Initialize deque container with exist deque container.
 * @param pdeq_dest   destination deque container.
 * @param pdeq_src    source deque container.
 * @return void.
 * @remarks if pdeq_dest == NULL or pdeq_src == NULL, then the behavior is undefined. pdeq_dest must be created by
 *          create_deque(), and pdeq_src must be initialized, otherwise the behavior is undefined. the element type of
 *          pdeq_dest and pdeq_src must be the same, otherwise the behavior is undefined.
 */
extern void deque_init_copy(deque_t* pdeq_dest, const deque_t* cpdeq_src);

/**
 * Initialize deque container with specific range.
 * @param pdeq_dest    destination deque container.
 * @param it_begin     range begin.
 * @param it_end       range end.
 * @return void.
 * @remarks if pdeq_dest == NULL, then the behavior is undefined. pdeq_dest must be created by create_deque(), otherwise
 *          the behavior is undefined. [it_begin, it_end) must be valid range, otherwise the behavior is undefined. the
 *          element type of [it_begin, it_end) and pdeq_dest must be the same, otherwise the behavior is undefined.
 */
extern void deque_init_copy_range(deque_t* pdeq_dest, iterator_t it_begin, iterator_t it_end);

/**
 * Initialize deque container with specific array.
 * @param pdeq_dest    destination deque container.
 * @param cpv_array    array.
 * @param t_count      element count of array.
 * @return void.
 * @remarks if pdeq_dest == NULL, then the behavior is undefined. pdeq_dest must be created by create_deque(), otherwise
 *          the behavior is undefined. cpv_array must not be NULL, otherwise the behavior is undefined. the element type 
 *          of array and pdeq_dest must be the same, otherwise the behavior is undefined.
 */
extern void deque_init_copy_array(deque_t* pdeq_dest, const void* cpv_array, size_t t_count);

/**
 * Tests if a deque is empty.
 * @param cpdeq_deque  deque container.
 * @return true if the deque is empty, else returns false.
 * @remarks if cpdeq_deque == NULL, then the behavior is undefined. the cpdeq_deque must be initialized, otherwise the
 *          behavior is undefine.
 */
extern bool_t deque_empty(const deque_t* cpdeq_deque);

/**
 * Return the number of elements in a deque.
 * @param cpdeq_deque  deque container.
 * @return the number of elements in the deque.
 * @remarks if cpdeq_deque == NULL, then the behavior is undefined. the cpdeq_deque must be initialized, otherwise the
 *          behavior is undefine.
 */
extern size_t deque_size(const deque_t* cpdeq_deque);

/**
 * Return the maximum number of elements in a deque.
 * @param cpdeq_deque  deque container.
 * @return the maximum possible number of elements in the deque.
 * @remarks if cpdeq_deque == NULL, then the behavior is undefined. the cpdeq_deque must be initialized, otherwise the
 *          behavior is undefine.
 */
extern size_t deque_max_size(const deque_t* cpdeq_deque);

/**
 * Return a iterator to the first element in the deque container.
 * @param cpdeq_deque    deque container.
 * @return a iterator to the first element in the deque container.
 * @remarks if cpdeq_deque == NULL, then the behavior is undefined. the deque must be initialized, otherwise the behavior
 *          is undefined. if the deque is empty, then return deque_end(cpdeq_deque).
 */
extern deque_iterator_t deque_begin(const deque_t* cpdeq_deque);

/**
 * Return a iterator that points just beyond the end of deque container.
 * @param cpdeq_deque    deque container.
 * @return a iterator to the end of deque.
 * @remarks if cpdeq_deque == NULL, then the behavior is undefined. the deque must be initialized, otherwise the behavior
 *          is undefined.
 */
extern deque_iterator_t deque_end(const deque_t* cpdeq_deque);
/* private */
extern deque_reverse_iterator_t deque_rbegin(const deque_t* cpdeq_deque);
extern deque_reverse_iterator_t deque_rend(const deque_t* cpdeq_deque);

/**
 * Assign deque element with an exist deque container.
 * @param pdeq_dest     destination deque container.
 * @param cpdeq_src     source deque container.
 * @return void.
 * @remarks if pdeq_dest == NULL or cpdeq_src == NULL, then the behavior is undefined. pdeq_dest and cpdeq_src must be
 *          initialized, otherwise the behavior is undefined. the element type of two deque must be same, otherwise
 *          the behavior is undefined. if the destination deque equal to source deque, then this function does nothing.
 */
extern void deque_assign(deque_t* pdeq_dest, const deque_t* cpdeq_src);

/**
 * Assign deque element with an exist deque container range.
 * @param pdeq_dest     destination deque container.
 * @param it_begin      range begin.
 * @param it_end        range end.
 * @return void.
 * @remarks if pdeq_dest == NULL, then the behavior is undefined. pdeq_dest must be initialized, otherwise the behavior
 *          is undefined. the element type of deque and [it_begin, it_end) must be same, otherwise the behavior is
 *          undefined. if [it_begin, it_end) belong to the destination deque, the behavior is undefined.
 */
extern void deque_assign_range(deque_t* pdeq_deque, iterator_t it_begin, iterator_t it_end);

/**
 * Assign deque element with an exist deque container array.
 * @param pdeq_dest    destination deque container.
 * @param cpv_array    array.
 * @param t_count      element count of array.
 * @return void.
 * @remarks if pdeq_dest == NULL, then the behavior is undefined. pdeq_dest must be initialized, otherwise the behavior
 *          is undefined. the element type of deque and array must be same, otherwise the behavior is
 *          undefined. cpv_array must not be NULL, otherwise the behavior is undefined.
 */
extern void deque_assign_array(deque_t* pdeq_deque, const void* cpv_array, size_t t_count);

/**
 * Tests if the two deques are equal.
 * @param cpdeq_first   first deque container.
 * @param cpdeq_second  second deque container.
 * @return if first deque equal to second deque, then return true, else return false.
 * @remarks if cpdeq_first == NULL or cpdeq_second == NULL, then the behavior is undefined. the two deques must be
 *          initialized, otherwise the behavior is undefined. if the two deques are not same type, the behavior is undefined.
 *          if cpdeq_first == cpdeq_second, then return true.
 */
extern bool_t deque_equal(const deque_t* cpdeq_first, const deque_t* cpdeq_second);

/**
 * Test the two deques are unequal.
 * @param cpdeq_first   first deque container.
 * @param cpdeq_second  second deque container.
 * @return if first deque unequal to second deque, then return true, else return false.
 * @remarks if cpdeq_first == NULL or cpdeq_second == NULL, then the behavior is undefined. the two deques must be
 *          initialized, otherwise the behavior is undefined. if the two deques are not same type, the behavior is undefined.
 *          if cpdeq_first == cpdeq_second, then return false.
 */
extern bool_t deque_not_equal(const deque_t* cpdeq_first, const deque_t* cpdeq_second);

/**
 * Test the first deque is less than the second deque.
 * @param cpdeq_first   first deque container.
 * @param cpdeq_second  second deque container.
 * @return if the first deque is less than the second deque, then return true, else return false.
 * @remarks if cpdeq_first == NULL or cpdeq_second == NULL, then the behavior is undefined. the two deques must be
 *          initialized, otherwise the behavior is undefined. if the two deques are not same type, the behavior is
 *          undefined. if cpdeq_first == cpdeq_second, then return false.
 */
extern bool_t deque_less(const deque_t* cpdeq_first, const deque_t* cpdeq_second);

/**
 * Test the first deque is less than or equal to the second deque.
 * @param cpdeq_first   first deque container.
 * @param cpdeq_second  second deque container.
 * @return if the first deque is less than or equal to the second deque, then return true, else return false.
 * @remarks if cpdeq_first == NULL or cpdeq_second == NULL, then the behavior is undefined. the two deques must be
 *          initialized, otherwise the behavior is undefined. if the two deques are not same type, the behavior is
 *          undefined. if cpdeq_first == cpdeq_second, then return true.
 */
extern bool_t deque_less_equal(const deque_t* cpdeq_first, const deque_t* cpdeq_second);

/**
 * Test the first deque is greater than the second deque.
 * @param cpdeq_first   first deque container.
 * @param cpdeq_second  second deque container.
 * @return if the first deque is greater than the second deque, then return true, else return false.
 * @remarks if cpdeq_first == NULL or cpdeq_second == NULL, then the behavior is undefined. the two deques must be
 *          initialized, otherwise the behavior is undefined. if the two deques are not same type, the behavior is
 *          undefined. if cpdeq_first == cpdeq_second, then return false.
 */
extern bool_t deque_greater(const deque_t* cpdeq_first, const deque_t* cpdeq_second);

/**
 * Test the first deque is greater than or equal to the second deque.
 * @param cpdeq_first   first deque container.
 * @param cpdeq_second  second deque container.
 * @return if the first deque is greater than or equal to the second deque, then return true, else return false.
 * @remarks if cpdeq_first == NULL or cpdeq_second == NULL, then the behavior is undefined. the two deques must be
 *          initialized, otherwise the behavior is undefined. if the two deques are not same type, the behavior is
 *          undefined. if cpdeq_first == cpdeq_second, then return true.
 */
extern bool_t deque_greater_equal(const deque_t* cpdeq_first, const deque_t* cpdeq_second);

/**
 * Access deque data using subscript.
 * @param cpdeq_deque  deque container.
 * @param t_pos         subscript.
 * @return pointer to the data.
 * @remarks if cpdeq_deque == NULL, then the behavior is undefined. the deque must be initialized, otherwise the behavior
 *          is undefined. if t_pos >= deque_size(cpdeq_deque), then the behavior is undefined.
 */
extern void* deque_at(const deque_t* cpdeq_deque, size_t t_pos);

/**
 * Access first deque data.
 * @param cpdeq_deque    deque container.
 * @return pointer to the data.
 * @remarks if cpdeq_deque == NULL, then the behavior is undefined. the deque must be initialized, otherwise the behavior
 *          is undefined. if the deque is empty, then the behavior is undefined.
 */
extern void* deque_front(const deque_t* cpdeq_deque);

/**
 * Access first last data.
 * @param cpdeq_deque    deque container.
 * @return pointer to the data.
 * @remarks if cpdeq_deque == NULL, then the behavior is undefined. the deque must be initialized, otherwise the behavior
 *          is undefined. if the deque is empty, then the behavior is undefined.
 */
extern void* deque_back(const deque_t* cpdeq_deque);

/**
 * Swap deque datas.
 * @param pdeq_first    first deque.
 * @param pdeq_second   second deque.
 * @return void.
 * @remarks if pdeq_first == NULL or pdeq_second == NULL, then the behavior is undefined. the two deques must be
 *          initialized, otherwise the behavior is undefined. the element type of two deques must be the same, otherwise
 *          the behavior is undefined. if deque_equal(pdeq_first, pdeq_second) == true, then this function does nothing.
 */
extern void deque_swap(deque_t* pdeq_first, deque_t* pdeq_second);

/**
 * Delete the element at the end of deque.
 * @param pdeq_deque    deque container.
 * @return void.
 * @remarks if cpdeq_deque == NULL, then the behavior is undefined. the deque must be initialized, otherwise the behavior
 *          is undefined. if deque is empty, then the behavior is undefined.
 */
extern void deque_pop_back(deque_t* pdeq_deque);

/**
 * Delete the element at the begin of deque.
 * @param pdeq_deque    deque container.
 * @return void.
 * @remarks if cpdeq_deque == NULL, then the behavior is undefined. the deque must be initialized, otherwise the behavior
 *          is undefined. if deque is empty, then the behavior is undefined.
 */
extern void deque_pop_front(deque_t* pdeq_deque);

/**
 * Insert a range of elements into deque at a specificed position.
 * @param pdeq_deque    deque container.
 * @param it_pos        specificed position.
 * @param it_begin      the position of first element in the range.
 * @param it_end        the position of first element beyond the range.
 * @return void.
 * @remarks if pdeq_deque == NULL, then the behavior is undefined. the deque must be initialized, otherwise the
 *          behavior is undefined. the specificed position muse be valid iterator for deque container, otherwise
 *          the behavior is undefined. [it_begin, it_end) must be valid range, otherwise the behavior is undefined.
 *          if [it_begin, it_end) belong to deque, the behavior is undefined. the type of specificed range and 
 *          deque element must be the same, otherwise the behavior is undefined.
 */
extern void deque_insert_range(
    deque_t* pdeq_deque, deque_iterator_t it_pos, iterator_t it_begin, iterator_t it_end);

/**
 * Insert a array of elements into deque at a specificed position.
 * @param pdeq_deque    deque container.
 * @param it_pos        specificed position.
 * @param cpv_array     array.
 * @param t_count       element count of array.
 * @return void.
 * @remarks if pdeq_deque == NULL, then the behavior is undefined. the deque must be initialized, otherwise the
 *          behavior is undefined. the specificed position muse be valid iterator for deque container, otherwise
 *          the behavior is undefined. cpv_array must not be NULL, otherwise the behavior is undefined. the type 
 *          of specificed array and deque element must be the same, otherwise the behavior is undefined.
 */
extern void deque_insert_array(
    deque_t* pdeq_deque, deque_iterator_t it_pos, const void* cpv_array, size_t t_count);

/**
 * Removes an element in deque from specificed position.
 * @param pdeq_deque     deque container.
 * @param it_pos         specificed position.
 * @return an iterator that reference the first element beyond the removed element.
 * @remarks if pdeq_deque == NULL, then the behavior is undefined. the deque must be initialized, otherwise the
 *          behavior is undefined. the specificed position muse be valid iterator for deque container, otherwise
 *          the behavior is undefined.
 */
extern deque_iterator_t deque_erase(deque_t* pdeq_deque, deque_iterator_t it_pos);

/**
 * Removes a range of elements in deque from specificed position.
 * @param pdeq_deque     deque container.
 * @param it_begin       position of first element removed from the deque.
 * @param it_end         position just beyond the last element removed from the deque.
 * @return an iterator that reference the first element beyond the removed element.
 * @remarks if pdeq_deque == NULL, then the behavior is undefined. the deque must be initialized, otherwise the
 *          behavior is undefined. the [it_begin, it_end) muse be valid range for deque container, otherwise the
 *          behavior is undefined.
 */
extern deque_iterator_t deque_erase_range(deque_t* pdeq_deque, deque_iterator_t it_begin, deque_iterator_t it_end);

/**
 * Erases the elements of deque.
 * @param pdeq_deque    deque container.
 * @return void.
 * @remarks if pdeq_deque == NULL, then the behavior is undefined. the deque must be initialized, otherwise the behavior
 *          is undefined.
 */
extern void deque_clear(deque_t* pdeq_deque);

/**
 * Specifies a new size of a deque.
 * @param pdeq_deque    deque container.
 * @param t_resize      new size of deque.
 * @return void.
 * @remarks if cpdeq_deque == NULL, then the behavior is undefined. the deque must be initialized, otherwise the behavior
 *          is undefined. if deque is empty, then the behavior is undefined. if t_resize is greater than deque size, new
 *          default element are added to the deque until it reaches the required size.
 */
extern void deque_resize(deque_t* pdeq_deque, size_t t_resize);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_DEQUE_H_ */
/** eof **/

