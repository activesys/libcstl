/*
 *  The user interface of list.
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

#ifndef _CSTL_LIST_H_
#define _CSTL_LIST_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/**
 * Create list container.
 * @param ...      type name.
 * @return list container pointer, if create list successfully, else return NULL.
 * @remarks type name must be c builtin type, libcstl builtin type or user defined type, otherwise creation will be failure.
 */
#define create_list(...) _create_list(#__VA_ARGS__)

/**
 * Initialize list with specified element.
 * @param plist_list   uninitialized list container.
 * @param t_count      element number.
 * @param elem         specificed element.
 * @return void
 * @remarks if plist_list == NULL, then the behavior is undefined. the type of specificed element and list element
 *          type must be same, otherwise the behavior is undefined.
 */
#define list_init_elem(plist_list, t_count, elem) _list_init_elem((plist_list), (t_count), (elem))

/**
 * Assign list with specificed element.
 * @param plist_list   list container.
 * @param t_count      element number.
 * @param elem         specificed element.
 * @return void.
 * @remarks if plist_list == NULL or list is uninitialized, then the behavior is undefined. the type of specificed
 *          element and list element type must be same, otherwise the behavior is undefined.
 */
#define list_assign_elem(plist_list, t_count, elem) _list_assign_elem((plist_list), (t_count), (elem))

/**
 * Adds an element to the end of list.
 * @param plist_list   list container.
 * @param elem         specificed element.
 * @return void.
 * @remarks if plist_list == NULL or list is uninitialized, then the behavior is undefined. the type of specificed
 *          element and list element type must be same, otherwise the behavior is undefined.
 */
#define list_push_back(plist_list, elem) _list_push_back((plist_list), (elem))

/**
 * Adds an element to the begin of list.
 * @param plist_list   list container.
 * @param elem         specificed element.
 * @return void.
 * @remarks if plist_list == NULL or list is uninitialized, then the behavior is undefined. the type of specificed
 *          element and list element type must be same, otherwise the behavior is undefined.
 */
#define list_push_front(plist_list, elem) _list_push_front((plist_list), (elem))

/**
 * Reset the size of list elements.
 * @param plist_list    list container.
 * @param t_resize      new size of list elements.
 * @param elem          specificed element.
 * @return void.
 * @remarks if plist_list == NULL or list is uninitialized, then the behavior is undefined. the type of specificed
 *          element and list element type must be same, otherwise the behavior is undefined. the first specificed is
 *          in use, others are not in use. if t_resize less than current list size, then erase elmement from the end.
 *          if t_resize greater than current list size, then append elements to the end, and the element is specificed
 *          element.
 */
#define list_resize_elem(plist_list, t_count, elem) _list_resize_elem((plist_list), (t_count), (elem))

/**
 * Remove specificed element from list container.
 * @param plist_list    list container.
 * @elem                specificed element.
 * @return void.
 * @remarks if plist_list == NULL or list is uninitialized, then the behavior is undefined. the type of specificed
 *          element and list element type must be same, otherwise the behavior is undefined. this function remove all
 *          element that equal to specificed, if no such element then does nothing.
 */
#define list_remove(plist_list, elem) _list_remove((plist_list), (elem))

/**
 * Insert an element into list at a specificed position.
 * @param plist_list    list container.
 * @param it_pos        specificed position.
 * @param elem          specificed element.
 * @return the position where the new element was inserted into the list.
 * @remarks if plist_list == NULL, then the behavior is undefined. the list must be initialized, otherwise the
 *          behavior is undefined. the specificed position muse be valid iterator for list container, otherwise
 *          the behavior is undefined. the type of specificed and list element must be the same, otherwise the
 *          behavior is undefined.
 */
#define list_insert(plist_list, it_pos, elem) _list_insert_n((plist_list), (it_pos), 1, (elem))

/**
 * Insert a number of elements into list at a specificed position.
 * @param plist_list    list container.
 * @param it_pos        specificed position.
 * @param t_count       the number of specificed elements.
 * @param elem          specificed element.
 * @return the position where the new element was inserted into the list.
 * @remarks if plist_list == NULL, then the behavior is undefined. the list must be initialized, otherwise the
 *          behavior is undefined. the specificed position muse be valid iterator for list container, otherwise
 *          the behavior is undefined. the type of specificed and list element must be the same, otherwise the
 *          behavior is undefined.
 */
#define list_insert_n(plist_list, it_pos, t_count, elem) _list_insert_n((plist_list), (it_pos), (t_count), (elem))

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Initialize an empty list container
 * @param plist_list   list container.
 * @return void.
 * @remarks if plist_list == NULL, then the behavior is undefined. plist_list must be created by create_list(), otherwise
 *          the behavior is undefine.
 */
extern void list_init(list_t* plist_list);

/**
 * Initialize list container with specific size.
 * @param plist_list   list container.
 * @param t_count      the number of default elements.
 * @return void.
 * @remarks if plist_list == NULL, then the behavior is undefined. plist_list must be created by create_list(), otherwise
 *          the behavior is undefine.
 */
extern void list_init_n(list_t* plist_list, size_t t_count);

/**
 * Destroy list container.
 * @param plist_list   list container.
 * @return void.
 * @remraks if plist_list == NULLL, then the behavior is undefined. plist_list must be initialized or created by create_list(),
 *          otherwise the behavior is undefined.
 */
extern void list_destroy(list_t* plist_list);

/**
 * Initialize list container with exist list container.
 * @param plist_dest   destination list container.
 * @param plist_src    source list container.
 * @return void.
 * @remarks if plist_dest == NULL or plist_src == NULL, then the behavior is undefined. plist_dest must be created by
 *          create_list(), and plist_src must be initialized, otherwise the behavior is undefined. the element type of
 *          plist_dest and plist_src must be the same, otherwise the behavior is undefined.
 */
extern void list_init_copy(list_t* plist_dest, const list_t* cplist_src);

/**
 * Initialize list container with specific range.
 * @param plist_dest   destination list container.
 * @param it_begin     range begin.
 * @param it_end       range end.
 * @return void.
 * @remarks if plist_dest == NULL, then the behavior is undefined. plist_dest must be created by create_list(), otherwise
 *          the behavior is undefined. [it_begin, it_end) must be valid range, otherwise the behavior is undefined. the
 *          element type of [it_begin, it_end) and plist_dest must be the same, otherwise the behavior is undefined.
 */
extern void list_init_copy_range(list_t* plist_dest, iterator_t it_begin, iterator_t it_end);

/**
 * Initialize list container with specific array.
 * @param plist_dest   destination list container.
 * @param cpv_array    array.
 * @param t_count      element count of array.
 * @return void.
 * @remarks if plist_dest == NULL, then the behavior is undefined. plist_dest must be created by create_list(), otherwise
 *          the behavior is undefined. cpv_array must be not NULL, otherwist the behavior is undefined. the
 *          element type of array and plist_dest must be the same, otherwise the behavior is undefined.
 */
extern void list_init_copy_array(list_t* plist_dest, const void* cpv_array, size_t t_count);

/**
 * Return the number of elements in a list.
 * @param cplist_list  list container.
 * @return the number of elements in the list.
 * @remarks if cplist_list == NULL, then the behavior is undefined. the cplist_list must be initialized, otherwise the
 *          behavior is undefine.
 */
extern size_t list_size(const list_t* cplist_list);

/**
 * Tests if a list is empty.
 * @param cplist_list  list container.
 * @return true if the list is empty, else returns false.
 * @remarks if cplist_list == NULL, then the behavior is undefined. the cplist_list must be initialized, otherwise the
 *          behavior is undefine.
 */
extern bool_t list_empty(const list_t* cplist_list);

/**
 * Return the maximum number of elements in a list.
 * @param cplist_list  list container.
 * @return the maximum possible number of elements in the list.
 * @remarks if cplist_list == NULL, then the behavior is undefined. the cplist_list must be initialized, otherwise the
 *          behavior is undefine.
 */
extern size_t list_max_size(const list_t* cplist_list);

/**
 * Tests if the two lists are equal.
 * @param cplist_first   first list container.
 * @param cplist_second  second list container.
 * @return if first list equal to second list, then return true, else return false.
 * @remarks if cplist_first == NULL or cplist_second == NULL, then the behavior is undefined. the two lists must be
 *          initialized, otherwise the behavior is undefined. if the two lists are not same type, the behavior is undefined.
 *          if cplist_first == cplist_second, then return true.
 */
extern bool_t list_equal(const list_t* cplist_first, const list_t* cplist_second);

/**
 * Test the two lists are unequal.
 * @param cplist_first   first list container.
 * @param cplist_second  second list container.
 * @return if first list unequal to second list, then return true, else return false.
 * @remarks if cplist_first == NULL or cplist_second == NULL, then the behavior is undefined. the two lists must be
 *          initialized, otherwise the behavior is undefined. if the two lists are not same type, the behavior is undefined.
 *          if cplist_first == cplist_second, then return false.
 */
extern bool_t list_not_equal(const list_t* cplist_first, const list_t* cplist_second);

/**
 * Test the first list is less than the second list.
 * @param cplist_first   first list container.
 * @param cplist_second  second list container.
 * @return if the first list is less than the second list, then return true, else return false.
 * @remarks if cplist_first == NULL or cplist_second == NULL, then the behavior is undefined. the two lists must be
 *          initialized, otherwise the behavior is undefined. if the two lists are not same type, the behavior is
 *          undefined. if cplist_first == cplist_second, then return false.
 */
extern bool_t list_less(const list_t* cplist_first, const list_t* cplist_second);

/**
 * Test the first list is less than or equal to the second list.
 * @param cplist_first   first list container.
 * @param cplist_second  second list container.
 * @return if the first list is less than or equal to the second list, then return true, else return false.
 * @remarks if cplist_first == NULL or cplist_second == NULL, then the behavior is undefined. the two lists must be
 *          initialized, otherwise the behavior is undefined. if the two lists are not same type, the behavior is
 *          undefined. if cplist_first == cplist_second, then return true.
 */
extern bool_t list_less_equal(const list_t* cpt_listfirst, const list_t* cpt_listsecond);

/**
 * Test the first list is greater than the second list.
 * @param cplist_first   first list container.
 * @param cplist_second  second list container.
 * @return if the first list is greater than the second list, then return true, else return false.
 * @remarks if cplist_first == NULL or cplist_second == NULL, then the behavior is undefined. the two lists must be
 *          initialized, otherwise the behavior is undefined. if the two lists are not same type, the behavior is
 *          undefined. if cplist_first == cplist_second, then return false.
 */
extern bool_t list_greater(const list_t* cplist_first, const list_t* cplist_second);

/**
 * Test the first list is greater than or equal to the second list.
 * @param cplist_first   first list container.
 * @param cplist_second  second list container.
 * @return if the first list is greater than or equal to the second list, then return true, else return false.
 * @remarks if cplist_first == NULL or cplist_second == NULL, then the behavior is undefined. the two lists must be
 *          initialized, otherwise the behavior is undefined. if the two lists are not same type, the behavior is
 *          undefined. if cplist_first == cplist_second, then return true.
 */
extern bool_t list_greater_equal(const list_t* cplist_first, const list_t* cplist_second);

/**
 * Assign list element with an exist list container.
 * @param plist_dest     destination list container.
 * @param cplist_src     source list container.
 * @return void.
 * @remarks if plist_dest == NULL or cplist_src == NULL, then the behavior is undefined. plist_dest and cplist_src must be
 *          initialized, otherwise the behavior is undefined. the element type of two list must be same, otherwise
 *          the behavior is undefined. if the destination list equal to source list, then this function does nothing.
 */
extern void list_assign(list_t* plist_dest, const list_t* cplist_src);

/**
 * Assign list element with an exist list container range.
 * @param plist_dest    destination list container.
 * @param it_begin      range begin.
 * @param it_end        range end.
 * @return void.
 * @remarks if plist_dest == NULL, then the behavior is undefined. plist_dest must be initialized, otherwise the behavior
 *          is undefined. the element type of list and [it_begin, it_end) must be same, otherwise the behavior is
 *          undefined. if [it_begin, it_end) belong to the destination list, the behavior is undefined.
 */
extern void list_assign_range(list_t* plist_list, iterator_t it_begin, iterator_t it_end);

/**
 * Assign list element with an exist list container array.
 * @param plist_dest    destination list container.
 * @param cpv_array     array.
 * @param t_count       element count of array.
 * @return void.
 * @remarks if plist_dest == NULL, then the behavior is undefined. plist_dest must be initialized, otherwise the behavior
 *          is undefined. the element type of list and array must be same, otherwise the behavior is
 *          undefined. cpv_array must be not NULL, otherwise the behavior is undefined.
 */
extern void list_assign_array(list_t* plist_list, const void* cpv_array, size_t t_count);

/**
 * Swap list datas.
 * @param plist_first    first list.
 * @param plist_second   second list.
 * @return void.
 * @remarks if plist_first == NULL or plist_second == NULL, then the behavior is undefined. the two lists must be
 *          initialized, otherwise the behavior is undefined. the element type of two lists must be the same, otherwise
 *          the behavior is undefined. if list_equal(plist_first, plist_second) == true, then this function does nothing.
 */
extern void list_swap(list_t* pt_listfirst, list_t* pt_listsecond);

/**
 * Access first list data.
 * @param cplist_list    list container.
 * @return pointer to the data.
 * @remarks if cplist_list == NULL, then the behavior is undefined. the list must be initialized, otherwise the behavior
 *          is undefined. if the list is empty, then the behavior is undefined.
 */
extern void* list_front(const list_t* cplist_list);

/**
 * Access first last data.
 * @param cplist_list    list container.
 * @return pointer to the data.
 * @remarks if cplist_list == NULL, then the behavior is undefined. the list must be initialized, otherwise the behavior
 *          is undefined. if the list is empty, then the behavior is undefined.
 */
extern void* list_back(const list_t* cplist_list);

/**
 * Return a iterator to the first element in the list container.
 * @param cplist_list    list container.
 * @return a iterator to the first element in the list container.
 * @remarks if cplist_list == NULL, then the behavior is undefined. the list must be initialized, otherwise the behavior
 *          is undefined. if the list is empty, then return list_end(cplist_list).
 */
extern list_iterator_t list_begin(const list_t* cplist_list);

/**
 * Return a iterator that points just beyond the end of list container.
 * @param cplist_list    list container.
 * @return a iterator to the end of list.
 * @remarks if cplist_list == NULL, then the behavior is undefined. the list must be initialized, otherwise the behavior
 *          is undefined.
 */
extern list_iterator_t list_end(const list_t* cplist_list);
/* private */
extern list_reverse_iterator_t list_rbegin(const list_t* cplist_list);
extern list_reverse_iterator_t list_rend(const list_t* cplist_list);

/**
 * Insert a range of elements into list at a specificed position.
 * @param plist_list    list container.
 * @param it_pos        specificed position.
 * @param it_begin      the position of first element in the range.
 * @param it_end        the position of first element beyond the range.
 * @return void.
 * @remarks if plist_list == NULL, then the behavior is undefined. the list must be initialized, otherwise the
 *          behavior is undefined. the specificed position muse be valid iterator for list container, otherwise
 *          the behavior is undefined. [it_begin, it_end) must be valid range, otherwise the behavior is undefined.
 *          if [it_begin, it_end) belong to list, the behavior is undefined. the type of specificed range and 
 *          list element must be the same, otherwise the behavior is undefined.
 */
extern void list_insert_range(list_t* plist_list, list_iterator_t it_pos, iterator_t it_begin, iterator_t it_end);

/**
 * Insert a array of elements into list at a specificed position.
 * @param plist_list    list container.
 * @param it_pos        specificed position.
 * @param cpv_array     array.
 * @param t_count       element count of array.
 * @return void.
 * @remarks if plist_list == NULL, then the behavior is undefined. the list must be initialized, otherwise the
 *          behavior is undefined. the specificed position muse be valid iterator for list container, otherwise
 *          the behavior is undefined. cpv_array must not be NULL, otherwise the behavior is undefined. the type 
 *          of specificed array and list element must be the same, otherwise the behavior is undefined.
 */
extern void list_insert_array(list_t* plist_list, list_iterator_t it_pos, const void* cpv_array, size_t t_count);

/**
 * Delete the element at the end of list.
 * @param plist_list    list container.
 * @return void.
 * @remarks if cplist_list == NULL, then the behavior is undefined. the list must be initialized, otherwise the behavior
 *          is undefined. if list is empty, then the behavior is undefined.
 */
extern void list_pop_back(list_t* plist_list);

/**
 * Delete the element at the begin of list.
 * @param plist_list    list container.
 * @return void.
 * @remarks if plist_list == NULL, then the behavior is undefined. the list must be initialized, otherwise the behavior
 *          is undefined. if list is empty, then the behavior is undefined.
 */
extern void list_pop_front(list_t* plist_list);

/**
 * Removes an element in list from specificed position.
 * @param plist_list     list container.
 * @param it_pos         specificed position.
 * @return an iterator that reference the first element beyond the removed element.
 * @remarks if plist_list == NULL, then the behavior is undefined. the list must be initialized, otherwise the
 *          behavior is undefined. the specificed position muse be valid iterator for list container, otherwise
 *          the behavior is undefined.
 */
extern list_iterator_t list_erase(list_t* plist_list, list_iterator_t it_pos);

/**
 * Removes a range of elements in list from specificed position.
 * @param plist_list     list container.
 * @param it_begin       position of first element removed from the list.
 * @param it_end         position just beyond the last element removed from the list.
 * @return an iterator that reference the first element beyond the removed element.
 * @remarks if plist_list == NULL, then the behavior is undefined. the list must be initialized, otherwise the
 *          behavior is undefined. the [it_begin, it_end) muse be valid range for list container, otherwise the
 *          behavior is undefined.
 */
extern list_iterator_t list_erase_range(list_t* plist_list, list_iterator_t it_begin, list_iterator_t it_end);

/**
 * Remove elements from a list for which a specificed predicate is satisfied.
 * @param plist_list    list container.
 * @unary_op            unary predicate.
 * @return void.
 * @remarks if plist_list == NULL or list is uninitialized, then the behavior is undefined. this function remove all
 *          element that satisfy the predicate, if no such element then does nothing. if ufun_op == NULL then use default
 *          unary predicate.
 */
extern void list_remove_if(list_t* pt_list, ufun_t ufun_op);

/**
 * Specifies a new size of a list.
 * @param plist_list    list container.
 * @param t_resize      new size of list.
 * @return void.
 * @remarks if cplist_list == NULL, then the behavior is undefined. the list must be initialized, otherwise the behavior
 *          is undefined. if list is empty, then the behavior is undefined. if t_resize is greater than list size, new
 *          default element are added to the list until it reaches the required size.
 */
extern void list_resize(list_t* plist_list, size_t t_resize);

/**
 * Erases the elements of list.
 * @param plist_list    list container.
 * @return void.
 * @remarks if plist_list == NULL, then the behavior is undefined. the list must be initialized, otherwise the behavior
 *          is undefined.
 */
extern void list_clear(list_t* pt_list);

/**
 * Removes adjacent duplicate elements from a list.
 * @param plist_list     list container.
 * @return void.
 * @remarks if plist_list == NULL, then the behavior is undefined. the list must be initialized, otherwise the behavior
 *          is undefined. this function removes adjacent duplicate elements, but duplicates that are not adjacent will not
 *          bt deleted.
 */
extern void list_unique(list_t* plist_list);

/**
 * Removes adjacent elements that satisfy some other binary predicate from a list.
 * @param plist_list     list container.
 * @param bfun_op        binary predicate.
 * @return void.
 * @remarks if plist_list == NULL, then the behavior is undefined. the list must be initialized, otherwise the behavior
 *          is undefined. this function removes adjacent elements that satisfy some other binary predicate, but elements
 *          that are not adjacent will not bt deleted. if bfun_op == NULL, then use default binary function.
 */
extern void list_unique_if(list_t* plist_list, bfun_t bfun_op);

/**
 * Removes elements from the source list and insert into the target list.
 * @param plist_list     target list.
 * @param it_pos         target position.
 * @param plist_src      source list.
 * @return void.
 * @remarks  if plist_list == NULL or plist_src == NUll then the behavior is undefined. the target list and source list
 *           must be initialized, otherwise the behavior is undefined. target position must be valid position for target list. 
 *           the element type of two list must be the same, otherwise the behavior is undefined. if plist_list == plist_src
 *           then the function does nothing.
 */
extern void list_splice(list_t* plist_list, list_iterator_t it_pos, list_t* plist_src);

/**
 * Removes element from the source list and insert into the target list.
 * @param plist_list     target list.
 * @param it_pos         target position.
 * @param plist_src      source list.
 * @param it_src         source position.
 * @return void.
 * @remarks  if plist_list == NULL or plist_src == NUll then the behavior is undefined. the target list and source list
 *           must be initialized, otherwise the behavior is undefined. target position must be valid position for target list,
 *           soruce position muse be valid position for source list, otherwise the behavior is undefine. the element type of
 *           two list must be the same, otherwise the behavior is undefined. if plist_list == plist_src and it_pos == it_src
 *           or it_pos = iterator_next(it_src), then the function does nothing.
 */
extern void list_splice_pos(list_t* plist_list, list_iterator_t it_pos, list_t* plist_src, list_iterator_t it_src);

/**
 * Removes elements from the source list range and insert into the target list.
 * @param plist_list     target list.
 * @param it_pos         target position.
 * @param plist_src      source list.
 * @param it_begin       source range begin position.
 * @param it_end         source range end position.
 * @return void.
 * @remarks  if plist_list == NULL or plist_src == NUll then the behavior is undefined. the target list and source list
 *           must be initialized, otherwise the behavior is undefined. target position must be valid position for target list,
 *           soruce range muse be valid range for source list, otherwise the behavior is undefine. the element type of
 *           two list must be the same, otherwise the behavior is undefined. if plist_list == plist_src and it_pos == it_begin
 *           or it_pos = it_end, then the function does nothing.
 */
extern void list_splice_range(
    list_t* plist_list, list_iterator_t it_pos, list_t* plist_src, list_iterator_t it_begin, list_iterator_t it_end);

/**
 * Sort elements of list container.
 * @param plist_list     list container.
 * @return void.
 * @remarks if plist_list == NULL, then the behavior is undefined. the list must be initialized, otherwise the behavior is
 *          undefined.
 */
extern void list_sort(list_t* plist_list);

/**
 * Sort elements of list container with user-specifide order relation.
 * @param plist_list     list container.
 * @param bfun_op        user-specified order relation.
 * @return void.
 * @remarks if plist_list == NULL, then the behavior is undefined. the list must be initialized, otherwise the behavior is
 *          undefined. if bfun_op == NULL, then use default type less function.
 */
extern void list_sort_if(list_t* plist_list, bfun_t bfun_op);

/**
 * Merge two sorted list.
 * @param plist_dest    destination list.
 * @param plist_src     source list.
 * @return void.
 * @remarks if plist_dest == NULL or plist_src == NULL, then the behavior is undefined. destination list and source list
 *          must be initialized, otherwise the behavior is undefined. the element type of two list must be the same, otherwise
 *          the behavior is undefined. if plist_dest == plist_src then the function does nothing.
 */
extern void list_merge(list_t* plist_dest, list_t* plist_src);

/**
 * Merge two sorted list.
 * @param plist_dest    destination list.
 * @param plist_src     source list.
 * @param bfun_op       sorted predicate.
 * @return void.
 * @remarks if plist_dest == NULL or plist_src == NULL, then the behavior is undefined. destination list and source list
 *          must be initialized, otherwise the behavior is undefined. the element type of two list must be the same, otherwise
 *          the behavior is undefined. if plist_dest == plist_src then the function does nothing. if bfun_op == NULL then use
 *          type less compare function.
 */
extern void list_merge_if(list_t* plist_dest, list_t* plist_src, bfun_t bfun_op);

/**
 * Reverse the order of all elements.
 * @param plist_list    list container.
 * @return void.
 * @remarks if plist_list == NULL, then the behavior is undefined. the list must be initialized, otherwise the behavior is
 *          undefined.
 */
extern void list_reverse(list_t* plist_list);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_LIST_H_ */
/** eof **/

