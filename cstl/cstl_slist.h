/*
 *  The slist interface.
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

#ifndef _CSTL_SLIST_H_
#define _CSTL_SLIST_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/**
 * Create slist container.
 * @param ...    type name.
 * @return slist container pointer, if create slist successfully, else return NULL.
 * @remarks type name must be c builtin type, libcstl builtin type or user defined type, otherwise creation will be failure.
 */
#define create_slist(...) _create_slist(#__VA_ARGS__)

/**
 * Initialize slist with specified element.
 * @param pslist_slist   uninitialized slist container.
 * @param t_count        element number.
 * @param elem           specificed element.
 * @return void
 * @remarks if pslist_slist == NULL, then the behavior is undefined. the type of specificed element and slist element
 *          type must be same, otherwise the behavior is undefined. slist container must be created by create_slist,
 *          otherwise the behavior is undefined.
 */
#define slist_init_elem(pslist_slist, t_count, elem) _slist_init_elem((pslist_slist), (t_count), (elem))

/**
 * Assign slist with specificed element.
 * @param pslist_slist   slist container.
 * @param t_count        element number.
 * @param elem           specificed element.
 * @return void.
 * @remarks if pslist_slist == NULL or slist is uninitialized, then the behavior is undefined. the type of specificed
 *          element and slist element type must be same, otherwise the behavior is undefined.
 */
#define slist_assign_elem(pslist_slist, t_count, elem) _slist_assign_elem((pslist_slist), (t_count), (elem))

/**
 * Add specificed element at the begin of slist container. 
 * @param pslist_slist    slist container.
 * @param elem            specificed element.
 * @return void.
 * @remarks if pslist_slist == NULL or slist is uninitialized, then the behavior is undefined. the type of specificed
 *          element and slist element type must be same, otherwise the behavior is undefined. the first specificed is
 *          in use, others are not in use.
 */
#define slist_push_front(pslist_slist, elem) _slist_push_front((pslist_slist), (elem))

/**
 * Remove specificed element from slist container.
 * @param pslist_slist    slist container.
 * @param elem            specificed element.
 * @return void.
 * @remarks if pslist_slist == NULL or slist is uninitialized, then the behavior is undefined. the type of specificed
 *          element and slist element type must be same, otherwise the behavior is undefined. the first specificed is
 *          in use, others are not in use. this function remove all element that equal to specificed, if no such element
 *          then does nothing.
 */
#define slist_remove(pslist_slist, elem) _slist_remove((pslist_slist), (elem))

/**
 * Reset the size of slist elements.
 * @param pslist_slist  slist container.
 * @param t_resize      new size of slist elements.
 * @param elem          specificed element.
 * @return void.
 * @remarks if pslist_slist == NULL or slist is uninitialized, then the behavior is undefined. the type of specificed
 *          element and slist element type must be same, otherwise the behavior is undefined. the first specificed is
 *          in use, others are not in use. if t_resize less than current slist size, then erase elmement from the end.
 *          if t_resize greater than current slist size, then append elements to the end, and the element is specificed
 *          element.
 */
#define slist_resize_elem(pslist_slist, t_resize, elem) _slist_resize_elem((pslist_slist), (t_resize), (elem))

/**
 * Insert one copy of element befor specificed position.
 * @param pslist_slist  slist container.
 * @param it_pos        insert position.
 * @param t_count       element number.
 * @param elem          specificed element.
 * @return position refereced the first inserted elements.
 * @remarks if pslist_slist == NULL or slist is uninitialized, then the behavior is undefined. the it_pos must be invalid
 *          iterator of slist container, otherwise the behavior is undefined. the type of specificed element and slist
 *          element type must be same, otherwise the behavior is undefined.
 */
#define slist_insert(pslist_slist, it_pos, elem) _slist_insert((pslist_slist), (it_pos), (elem))

/**
 * Insert multiple copys of element befor specificed position.
 * @param pslist_slist  slist container.
 * @param it_pos        insert position.
 * @param t_count       element number.
 * @param elem          specificed element.
 * @return void.
 * @remarks if pslist_slist == NULL or slist is uninitialized, then the behavior is undefined. the it_pos must be invalid
 *          iterator of slist container, otherwise the behavior is undefined. the type of specificed element and slist
 *          element type must be same, otherwise the behavior is undefined.
 */
#define slist_insert_n(pslist_slist, it_pos, t_count, elem) _slist_insert_n((pslist_slist), (it_pos), (t_count), (elem))

/**
 * Insert one copy of element after specificed position.
 * @param pslist_slist  slist container.
 * @param it_pos        before insert position.
 * @param t_count       element number.
 * @param elem          specificed element.
 * @return position refereced the first inserted elements.
 * @remarks if pslist_slist == NULL or slist is uninitialized, then the behavior is undefined. the it_pos must be invalid
 *          iterator of slist container, otherwise the behavior is undefined. the type of specificed element and slist
 *          element type must be same, otherwise the behavior is undefined. the first specificed is in use, others are not
 *          in use.
 */
#define slist_insert_after(pslist_slist, it_pos, elem) _slist_insert_after((pslist_slist), (it_pos), (elem))

/**
 * Insert multiple copys of element after specificed position.
 * @param pslist_slist  slist container.
 * @param it_pos        before insert position.
 * @param t_count       element number.
 * @param elem          specificed element.
 * @return void.
 * @remarks if pslist_slist == NULL or slist is uninitialized, then the behavior is undefined. the it_pos must be invalid
 *          iterator of slist container, otherwise the behavior is undefined. the type of specificed element and slist
 *          element type must be same, otherwise the behavior is undefined. the first specificed is in use, others are not
 *          in use.
 */
#define slist_insert_after_n(pslist_slist, it_pos, t_count, elem)\
    _slist_insert_after_n((pslist_slist), (it_pos), (t_count), (elem))

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Initialize an empty slist container
 * @param pslist_slist   slist container.
 * @return void.
 * @remarks if pslist_slist == NULL, then the behavior is undefined. pslist_slist must be created by create_slist(), otherwise
 *          the behavior is undefine.
 */
extern void slist_init(slist_t* pslist_slist);

/**
 * Initialize slist container with specific size.
 * @param pslist_slist   slist container.
 * @param t_count        the number of default elements.
 * @return void.
 * @remarks if pslist_slist == NULL, then the behavior is undefined. pslist_slist must be created by create_slist(), otherwise
 *          the behavior is undefine.
 */
extern void slist_init_n(slist_t* pslist_slist, size_t t_count);

/**
 * Initialize slist container with exist slist container.
 * @param pslist_dest   destination slist container.
 * @param pslist_src    source slist container.
 * @return void.
 * @remarks if pslist_dest == NULL or pslist_src == NULL, then the behavior is undefined. pslist_dest must be created by
 *          create_slist(), and pslist_src must be initialized, otherwise the behavior is undefined. the element type of
 *          pslist_dest and pslist_src must be the same, otherwise the behavior is undefined.
 */
extern void slist_init_copy(slist_t* pslist_dest, const slist_t* cpslist_src);

/**
 * Initialize slist container with specific range.
 * @param pslist_dest  destination slist container.
 * @param it_begin     range begin.
 * @param it_end       range end.
 * @return void.
 * @remarks if pslist_dest == NULL, then the behavior is undefined. pslist_dest must be created by create_slist(), otherwise
 *          the behavior is undefined. [it_begin, it_end) must be valid range, otherwise the behavior is undefined. the
 *          element type of [it_begin, it_end) and pslist_dest must be the same, otherwise the behavior is undefined.
 */
extern void slist_init_copy_range(slist_t* pslist_dest, iterator_t it_begin, iterator_t it_end);

/**
 * Initialize slist container with specific array.
 * @param pslist_slist destination slist container.
 * @param cpv_array    array.
 * @param t_count      element count of array.
 * @return void.
 * @remarks if pslist_dest == NULL, then the behavior is undefined. pslist_dest must be created by create_slist(), 
 *          otherwise the behavior is undefined. cpv_array must be valid array, otherwise the behavior is undefined. 
 *          the element type of array and pslist_dest must be the same, otherwise the behavior is undefined.
 */
extern void slist_init_copy_array(slist_t* pslist_slist, const void* cpv_array, size_t t_count);

/**
 * Destroy slist container.
 * @param pslist_slist   slist container.
 * @return void.
 * @remraks if pslist_slist == NULLL, then the behavior is undefined. pslist_slist must be initialized or created by
 *          create_slist(), otherwise the behavior is undefined.
 */
extern void slist_destroy(slist_t* pslist_slist);

/**
 * Return a iterator to the first element in the slist container.
 * @param cpslist_slist    slist container.
 * @return a iterator to the first element in the slist container.
 * @remarks if cpslist_slist == NULL, then the behavior is undefined. the slist must be initialized, otherwise the behavior
 *          is undefined. if the slist is empty, then return slist_end(cpslist_slist).
 */
extern slist_iterator_t slist_begin(const slist_t* cpslist_slist);

/**
 * Return a iterator that points just beyond the end of slist container.
 * @param cpslist_slist    slist container.
 * @return a iterator to the end of slist.
 * @remarks if cpslist_slist == NULL, then the behavior is undefined. the slist must be initialized, otherwise the behavior
 *          is undefined.
 */
extern slist_iterator_t slist_end(const slist_t* cpslist_slist);

/**
 * Return a iterator that points position before current position.
 * @param cpslist_slist    slist container.
 * @param it_pos           current position.
 * @return a iterator that points position before current position.
 * @remarks if cpslist_slist == NULL, then the behavior is undefined. the slist must be initialized, otherwise the behavior
 *          is undefined. it_pos must be valid for slist and must not be slist_begin(), otherwise the behavior is undefined.
 */
extern slist_iterator_t slist_previous(const slist_t* cpslist_slist, slist_iterator_t it_pos);

/**
 * Return the number of elements in a slist.
 * @param cpslist_slist  slist container.
 * @return the number of elements in the slist.
 * @remarks if cpslist_slist == NULL, then the behavior is undefined. the cpslist_slist must be initialized, otherwise the
 *          behavior is undefine.
 */
extern size_t slist_size(const slist_t* cpslist_slist);

/**
 * Tests if a slist is empty.
 * @param cpslist_slist  slist container.
 * @return true if the slist is empty, else returns false.
 * @remarks if cpslist_slist == NULL, then the behavior is undefined. the cpslist_slist must be initialized, otherwise the
 *          behavior is undefine.
 */
extern bool_t slist_empty(const slist_t* cpslist_slist);

/**
 * Return the maximum number of elements in a slist.
 * @param cpslist_slist  slist container.
 * @return the maximum possible number of elements in the slist.
 * @remarks if cpslist_slist == NULL, then the behavior is undefined. the cpslist_slist must be initialized, otherwise the
 *          behavior is undefine.
 */
extern size_t slist_max_size(const slist_t* cpslist_slist);

/**
 * Assign slist element with an exist slist container.
 * @param pslist_dest     destination slist container.
 * @param cpslist_src     source slist container.
 * @return void.
 * @remarks if pslist_dest == NULL or cpslist_src == NULL, then the behavior is undefined. pslist_dest and cpslist_src must be
 *          initialized, otherwise the behavior is undefined. the element type of two slist must be same, otherwise
 *          the behavior is undefined. if the destination slist equal to source slist, then this function does nothing.
 */
extern void slist_assign(slist_t* pslist_dest, const slist_t* cpslist_src);

/**
 * Assign slist element with an exist slist container range.
 * @param pslist_dest   destination slist container.
 * @param it_begin      range begin.
 * @param it_end        range end.
 * @return void.
 * @remarks if pslist_dest == NULL, then the behavior is undefined. pslist_dest must be initialized, otherwise the behavior
 *          is undefined. the element type of slist and [it_begin, it_end) must be same, otherwise the behavior is
 *          undefined. if [it_begin, it_end) belong to the destination slist, the behavior is undefined.
 */
extern void slist_assign_range(slist_t* pslist_dest, iterator_t it_begin, iterator_t it_end);

/**
 * Assign slist element with specificed array.
 * @param pslist_dest   destination slist container.
 * @param cpv_array     array.
 * @param t_count       element count of array.
 * @return void.
 * @remarks if pslist_dest == NULL, then the behavior is undefined. pslist_dest must be initialized, otherwise the behavior
 *          is undefined. the element type of slist and array must be same, otherwise the behavior is undefined.
 */
extern void slist_assign_array(slist_t* pslist_dest, const void* cpv_array, size_t t_count);

/**
 * Swap slist datas.
 * @param pslist_first    first slist.
 * @param pslist_second   second slist.
 * @return void.
 * @remarks if pslist_first == NULL or pslist_second == NULL, then the behavior is undefined. the two slists must be
 *          initialized, otherwise the behavior is undefined. the element type of two slists must be the same, otherwise
 *          the behavior is undefined. if slist_equal(pslist_first, pslist_second) == true, then this function does nothing.
 */
extern void slist_swap(slist_t* pslist_first, slist_t* pslist_second);

/**
 * Access first slist data.
 * @param cpslist_slist    slist container.
 * @return pointer to the data.
 * @remarks if cpslist_slist == NULL, then the behavior is undefined. the slist must be initialized, otherwise the behavior
 *          is undefined. if the slist is empty, then the behavior is undefined.
 */
extern void* slist_front(const slist_t* cpslist_slist);

/**
 * Delete the element at the begin of slist.
 * @param pslist_slist    slist container.
 * @return void.
 * @remarks if pslist_slist == NULL, then the behavior is undefined. the slist must be initialized, otherwise the behavior
 *          is undefined. if slist is empty, then the behavior is undefined.
 */
extern void slist_pop_front(slist_t* pslist_slist);

/**
 * Insert a range of elements into slist at a specificed position.
 * @param pslist_slist    slist container.
 * @param it_pos          specificed position.
 * @param it_begin        the position of first element in the range.
 * @param it_end          the position of first element beyond the range.
 * @return void.
 * @remarks if pslist_slist == NULL, then the behavior is undefined. the slist must be initialized, otherwise the
 *          behavior is undefined. the specificed position muse be valid iterator for slist container, otherwise
 *          the behavior is undefined. [it_begin, it_end) must be valid range, otherwise the behavior is undefined.
 *          if [it_begin, it_end) belong to slist, the behavior is undefined. the type of specificed range and 
 *          slist element must be the same, otherwise the behavior is undefined.
 */
extern void slist_insert_range(
    slist_t* pslist_slist, slist_iterator_t it_pos, iterator_t it_begin, iterator_t it_end);

/**
 * Insert a array of elements into slist at a specificed position.
 * @param pslist_slist    slist container.
 * @param it_pos          specificed position.
 * @param cpv_array       array.
 * @param t_count         element count of array.
 * @return void.
 * @remarks if pslist_slist == NULL, then the behavior is undefined. the slist must be initialized, otherwise the
 *          behavior is undefined. the specificed position muse be valid iterator for slist container, otherwise
 *          the behavior is undefined. cpv_array must be valid array, otherwise the behavior is undefined. the type 
 *          of specificed array and slist element must be the same, otherwise the behavior is undefined.
 */
extern void slist_insert_array(
    slist_t* pslist_slist, slist_iterator_t it_pos, const void* cpv_array, size_t t_count);

/**
 * Insert a range of elements into slist at position following specific position.
 * @param pslist_slist    slist container.
 * @param it_pos          specificed position.
 * @param it_begin        the position of first element in the range.
 * @param it_end          the position of first element beyond the range.
 * @return void.
 * @remarks if pslist_slist == NULL, then the behavior is undefined. the slist must be initialized, otherwise the
 *          behavior is undefined. the specificed position muse be valid iterator for slist container and must not be
 *          slist_end(), otherwise the behavior is undefined. [it_begin, it_end) must be valid range, otherwise the
 *          behavior is undefined. if [it_begin, it_end) belong to slist, the behavior is undefined. the type of specificed
 *          range and slist element must be the same, otherwise the behavior is undefined.
 */
extern void slist_insert_after_range(
    slist_t* pslist_slist, slist_iterator_t it_pos, iterator_t it_begin, iterator_t it_end);

/**
 * Insert a array of elements into slist at position following specific position.
 * @param pslist_slist    slist container.
 * @param it_pos          specificed position.
 * @param cpv_array       array.
 * @param t_count         element count of array.
 * @return void.
 * @remarks if pslist_slist == NULL, then the behavior is undefined. the slist must be initialized, otherwise the
 *          behavior is undefined. the specificed position muse be valid iterator for slist container and must not be
 *          slist_end(), otherwise the behavior is undefined. cpv_array must be valid array, otherwise the
 *          behavior is undefined. the type of specificed array and slist element must be the same, otherwise the 
 *          behavior is undefined.
 */
extern void slist_insert_after_array(
    slist_t* pslist_slist, slist_iterator_t it_pos, const void* cpv_array, size_t t_count);

/**
 * Removes an element in slist from specificed position.
 * @param pslist_slist   slist container.
 * @param it_pos         specificed position.
 * @return an iterator that reference the first element beyond the removed element.
 * @remarks if pslist_slist == NULL, then the behavior is undefined. the slist must be initialized, otherwise the
 *          behavior is undefined. the specificed position muse be valid iterator for slist container, otherwise
 *          the behavior is undefined.
 */
extern slist_iterator_t slist_erase(slist_t* pslist_slist, slist_iterator_t it_pos);

/**
 * Removes a range of elements in slist from specificed range.
 * @param pslist_slist   slist container.
 * @param it_begin       position of first element removed from the slist.
 * @param it_end         position just beyond the last element removed from the slist.
 * @return an iterator that reference the first element beyond the removed element.
 * @remarks if pslist_slist == NULL, then the behavior is undefined. the slist must be initialized, otherwise the
 *          behavior is undefined. the [it_begin, it_end) muse be valid range for slist container, otherwise the
 *          behavior is undefined.
 */
extern slist_iterator_t slist_erase_range(slist_t* pslist_slist, slist_iterator_t it_begin, slist_iterator_t it_end);

/**
 * Removes an element in slist after specificed position.
 * @param pslist_slist   slist container.
 * @param it_pos         specificed position.
 * @return an iterator that reference the first element beyond the removed element.
 * @remarks if pslist_slist == NULL, then the behavior is undefined. the slist must be initialized, otherwise the
 *          behavior is undefined. the specificed position muse be valid iterator for slist container and must not be
 *          slist_end(), otherwise the behavior is undefined. if it_pos == slist_previous(slist_end()), then the function
 *          does nothing, and return slist_end().
 */
extern slist_iterator_t slist_erase_after(slist_t* pslist_slist, slist_iterator_t it_pos);

/**
 * Removes a range of elements in slist after specificed range.
 * @param pslist_slist   slist container.
 * @param it_begin       position of first element removed from the slist.
 * @param it_end         position just beyond the last element removed from the slist.
 * @return an iterator that reference the first element beyond the removed element.
 * @remarks if pslist_slist == NULL, then the behavior is undefined. the slist must be initialized, otherwise the
 *          behavior is undefined. the [it_begin, it_end) muse be valid range for slist container and it_begin must not be
 *          slist_end(), otherwise the behavior is undefined. if it_begin() == it_end() or it_begin() + 1 == it_end, then
 *          the function does nothing.
 */
extern slist_iterator_t slist_erase_after_range(slist_t* pslist_slist, slist_iterator_t it_begin, slist_iterator_t it_end);

/**
 * Removes elements from the source slist and insert into the target slist.
 * @param pslist_slist   target slist.
 * @param it_pos         target position.
 * @param pslist_src     source slist.
 * @return void.
 * @remarks  if pslist_slist == NULL or pslist_src == NUll then the behavior is undefined. the target slist and source slist
 *           must be initialized, otherwise the behavior is undefined. target position must be valid position for target slist. 
 *           the element type of two slist must be the same, otherwise the behavior is undefined. if pslist_slist == pslist_src
 *           then the function does nothing.
 */
extern void slist_splice(slist_t* pslist_slist, slist_iterator_t it_pos, slist_t* pslist_src);

/**
 * Removes element from the source slist and insert into the target slist.
 * @param pslist_slist   target slist.
 * @param it_pos         target position.
 * @param pslist_src     source slist.
 * @param it_src         source position.
 * @return void.
 * @remarks  if pslist_slist == NULL or pslist_src == NUll then the behavior is undefined. the target slist and source slist
 *           must be initialized, otherwise the behavior is undefined. target position must be valid position for target slist,
 *           soruce position muse be valid position for source slist, otherwise the behavior is undefine. the element type of
 *           two slist must be the same, otherwise the behavior is undefined. if pslist_slist == pslist_src and it_pos == it_src
 *           or it_pos = iterator_next(it_src), then the function does nothing.
 */
extern void slist_splice_pos(slist_t* pslist_slist, slist_iterator_t it_pos, slist_t* pslist_src, slist_iterator_t it_src);

/**
 * Removes elements from the source slist range and insert into the target slist.
 * @param pslist_slist   target slist.
 * @param it_pos         target position.
 * @param pslist_src     source slist.
 * @param it_begin       source range begin position.
 * @param it_end         source range end position.
 * @return void.
 * @remarks  if pslist_slist == NULL or pslist_src == NUll then the behavior is undefined. the target slist and source slist
 *           must be initialized, otherwise the behavior is undefined. target position must be valid position for target slist,
 *           soruce range muse be valid range for source slist, otherwise the behavior is undefine. the element type of
 *           two slist must be the same, otherwise the behavior is undefined. if pslist_slist == pslist_src and it_pos == it_begin
 *           or it_pos = it_end, then the function does nothing.
 */
extern void slist_splice_range(
    slist_t* pslist_slist, slist_iterator_t it_pos, slist_t* pslist_src, slist_iterator_t it_begin, slist_iterator_t it_end);

/**
 * Removes element from the source slist and insert into the target slist.
 * @param pslist_slist   target slist.
 * @param it_pos         target position.
 * @param pslist_src     source slist.
 * @param it_prev        source position.
 * @return void.
 * @remarks  if pslist_slist == NULL or pslist_src == NUll then the behavior is undefined. the target slist and source slist
 *           must be initialized, otherwise the behavior is undefined. target position must be valid position for target slist,
 *           soruce position muse be valid position for source slist, otherwise the behavior is undefine. the element type of
 *           two slist must be the same, otherwise the behavior is undefined. if pslist_slist == pslist_src and it_pos == it_src
 *           or it_pos = iterator_next(it_src), then the function does nothing.
 */
extern void slist_splice_after_pos(
    slist_t* pslist_slist, slist_iterator_t it_pos, slist_t* pslist_src, slist_iterator_t it_prev);

/**
 * Removes elements from the source slist range and insert into the target slist.
 * @param pslist_slist   target slist.
 * @param it_pos         target position.
 * @param pslist_src     source slist.
 * @param it_begin       source range begin position.
 * @param it_end         source range end position.
 * @return void.
 * @remarks  if pslist_slist == NULL or pslist_src == NUll then the behavior is undefined. the target slist and source slist
 *           must be initialized, otherwise the behavior is undefined. target position must be valid position for target slist,
 *           soruce range muse be valid range for source slist, otherwise the behavior is undefine. the element type of
 *           two slist must be the same, otherwise the behavior is undefined. if pslist_slist == pslist_src and it_pos == it_begin
 *           or it_pos = it_end, then the function does nothing.
 */
extern void slist_splice_after_range(
    slist_t* pslist_slist, slist_iterator_t it_pos, slist_t* pslist_src, slist_iterator_t it_begin, slist_iterator_t it_end);

/**
 * Remove elements from a slist for which a specificed predicate is satisfied.
 * @param pslist_slist  slist container.
 * @unary_op            unary predicate.
 * @return void.
 * @remarks if pslist_slist == NULL or slist is uninitialized, then the behavior is undefined. this function remove all
 *          element that satisfy the predicate, if no such element then does nothing. if ufun_op == NULL then use default
 *          unary predicate.
 */
extern void slist_remove_if(slist_t* pslist_slist, ufun_t ufun_op);

/**
 * Removes adjacent duplicate elements from a slist.
 * @param pslist_slist     slist container.
 * @return void.
 * @remarks if pslist_slist == NULL, then the behavior is undefined. the slist must be initialized, otherwise the behavior
 *          is undefined. this function removes adjacent duplicate elements, but duplicates that are not adjacent will not
 *          bt deleted.
 */
extern void slist_unique(slist_t* pslist_slist);

/**
 * Removes adjacent elements that satisfy some other binary predicate from a slist.
 * @param pslist_slist   slist container.
 * @param bfun_op        binary predicate.
 * @return void.
 * @remarks if pslist_slist == NULL, then the behavior is undefined. the slist must be initialized, otherwise the behavior
 *          is undefined. this function removes adjacent elements that satisfy some other binary predicate, but elements
 *          that are not adjacent will not bt deleted. if bfun_op == NULL, then use default binary function.
 */
extern void slist_unique_if(slist_t* pslist_slist, bfun_t bfun_op);

/**
 * Reverse the order of all elements.
 * @param pslist_slist    slist container.
 * @return void.
 * @remarks if pslist_slist == NULL, then the behavior is undefined. the slist must be initialized, otherwise the behavior is
 *          undefined.
 */
extern void slist_reverse(slist_t* pslist_slist);

/**
 * Sort elements of slist container.
 * @param pslist_slist     slist container.
 * @return void.
 * @remarks if pslist_slist == NULL, then the behavior is undefined. the slist must be initialized, otherwise the behavior is
 *          undefined.
 */
extern void slist_sort(slist_t* pslist_slist);

/**
 * Sort elements of slist container with user-specifide order relation.
 * @param pslist_slist   slist container.
 * @param bfun_op        user-specified order relation.
 * @return void.
 * @remarks if pslist_slist == NULL, then the behavior is undefined. the slist must be initialized, otherwise the behavior is
 *          undefined. if bfun_op == NULL, then use default type less function.
 */
extern void slist_sort_if(slist_t* pslist_slist, bfun_t bfun_op);

/**
 * Merge two sorted slist.
 * @param pslist_dest    destination slist.
 * @param pslist_src     source slist.
 * @return void.
 * @remarks if pslist_dest == NULL or pslist_src == NULL, then the behavior is undefined. destination slist and source slist
 *          must be initialized, otherwise the behavior is undefined. the element type of two slist must be the same, otherwise
 *          the behavior is undefined. if pslist_dest == pslist_src then the function does nothing.
 */
extern void slist_merge(slist_t* pslist_dest, slist_t* pslist_src);

/**
 * Merge two sorted slist.
 * @param pslist_dest    destination slist.
 * @param pslist_src     source slist.
 * @param bfun_op        sorted predicate.
 * @return void.
 * @remarks if pslist_dest == NULL or pslist_src == NULL, then the behavior is undefined. destination slist and source slist
 *          must be initialized, otherwise the behavior is undefined. the element type of two slist must be the same, otherwise
 *          the behavior is undefined. if pslist_dest == pslist_src then the function does nothing. if bfun_op == NULL then use
 *          type less compare function.
 */
extern void slist_merge_if(slist_t* pslist_dest, slist_t* pslist_src, bfun_t bfun_op);

/**
 * Specifies a new size of a slist.
 * @param pslist_slist  slist container.
 * @param t_resize      new size of slist.
 * @return void.
 * @remarks if cpslist_slist == NULL, then the behavior is undefined. the slist must be initialized, otherwise the behavior
 *          is undefined. if slist is empty, then the behavior is undefined. if t_resize is greater than slist size, new
 *          default element are added to the slist until it reaches the required size.
 */
extern void slist_resize(slist_t* pslist_slist, size_t t_resize);

/**
 * Erases the elements of slist.
 * @param pslist_slist    slist container.
 * @return void.
 * @remarks if pslist_slist == NULL, then the behavior is undefined. the slist must be initialized, otherwise the behavior
 *          is undefined.
 */
extern void slist_clear(slist_t* pslist_slist);

/**
 * Tests if the two slists are equal.
 * @param cpslist_first   first slist container.
 * @param cpslist_second  second slist container.
 * @return if first slist equal to second slist, then return true, else return false.
 * @remarks if cpslist_first == NULL or cpslist_second == NULL, then the behavior is undefined. the two slists must be
 *          initialized, otherwise the behavior is undefined. if the two slists are not same type, then return false.
 *          if cpslist_first == cpslist_second, then return true.
 */
extern bool_t slist_equal(const slist_t* cpslist_first, const slist_t* cpslist_second);

/**
 * Test the two slists are unequal.
 * @param cpslist_first   first slist container.
 * @param cpslist_second  second slist container.
 * @return if first slist unequal to second slist, then return true, else return false.
 * @remarks if cpslist_first == NULL or cpslist_second == NULL, then the behavior is undefined. the two slists must be
 *          initialized, otherwise the behavior is undefined. if the two slists are not same type, then return true.
 *          if cpslist_first == cpslist_second, then return false.
 */
extern bool_t slist_not_equal(const slist_t* cpslist_first, const slist_t* cpslist_second);

/**
 * Test the first slist is less than the second slist.
 * @param cpslist_first   first slist container.
 * @param cpslist_second  second slist container.
 * @return if the first slist is less than the second slist, then return true, else return false.
 * @remarks if cpslist_first == NULL or cpslist_second == NULL, then the behavior is undefined. the two slists must be
 *          initialized, otherwise the behavior is undefined. if the two slists are not same type, the behavior is
 *          undefined. if cpslist_first == cpslist_second, then return false.
 */
extern bool_t slist_less(const slist_t* cpslist_first, const slist_t* cpslist_second);

/**
 * Test the first slist is less than or equal to the second slist.
 * @param cpslist_first   first slist container.
 * @param cpslist_second  second slist container.
 * @return if the first slist is less than or equal to the second slist, then return true, else return false.
 * @remarks if cpslist_first == NULL or cpslist_second == NULL, then the behavior is undefined. the two slists must be
 *          initialized, otherwise the behavior is undefined. if the two slists are not same type, the behavior is
 *          undefined. if cpslist_first == cpslist_second, then return true.
 */
extern bool_t slist_less_equal(const slist_t* cpslist_first, const slist_t* cpslist_second);

/**
 * Test the first slist is greater than the second slist.
 * @param cpslist_first   first slist container.
 * @param cpslist_second  second slist container.
 * @return if the first slist is greater than the second slist, then return true, else return false.
 * @remarks if cpslist_first == NULL or cpslist_second == NULL, then the behavior is undefined. the two slists must be
 *          initialized, otherwise the behavior is undefined. if the two slists are not same type, the behavior is
 *          undefined. if cpslist_first == cpslist_second, then return false.
 */
extern bool_t slist_greater(const slist_t* cpslist_first, const slist_t* cpslist_second);

/**
 * Test the first slist is greater than or equal to the second slist.
 * @param cpslist_first   first slist container.
 * @param cpslist_second  second slist container.
 * @return if the first slist is greater than or equal to the second slist, then return true, else return false.
 * @remarks if cpslist_first == NULL or cpslist_second == NULL, then the behavior is undefined. the two slists must be
 *          initialized, otherwise the behavior is undefined. if the two slists are not same type, the behavior is
 *          undefined. if cpslist_first == cpslist_second, then return true.
 */
extern bool_t slist_greater_equal(const slist_t* cpslist_first, const slist_t* cpslist_second);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_SLIST_H_ */
/** eof **/

