/*
 *  The user interface of deque.
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

#ifndef _CSTL_DEQUE_H
#define _CSTL_DEQUE_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/* create new deque with specify type */
#define create_deque(type)\
    _create_deque(sizeof(type), #type)
/* initialize */
#define deque_init_elem(pt_deque, t_count, elem)\
    _deque_init_elem((pt_deque), (t_count), (elem))
/* assign */
#define deque_assign_elem(pt_deque, t_count, elem)\
    _deque_assign_elem((pt_deque), (t_count), (elem))
/* push back and push front */
#define deque_push_back(pt_deque, elem)\
    _deque_push_back((pt_deque), (elem))
#define deque_push_front(pt_deque, elem)\
    _deque_push_front((pt_deque), (elem))
/* resize */
#define deque_resize_elem(pt_deque, t_resize, elem)\
    _deque_resize_elem((pt_deque), (t_resize), (elem))
/* insert */
#define deque_insert(pt_deque, t_pos, elem)\
    _deque_insert_n((pt_deque), (t_pos), 1, (elem))
#define deque_insert_n(pt_deque, t_pos, t_count, elem)\
    _deque_insert_n((pt_deque), (t_pos), (t_count), (elem))

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * Initialization and destroy operation functions.
 */
extern void deque_init(deque_t* pt_deque);
extern void deque_init_n(deque_t* pt_deque, size_t t_count);
extern void deque_destroy(deque_t* pt_deque);
extern void deque_init_copy(deque_t* pt_dequedest, const deque_t* cpt_dequesrc);
extern void deque_init_copy_range(
    deque_t* pt_dequedest, deque_iterator_t t_begin, deque_iterator_t t_end);

/*
 * deque_t size operation functions.
 */
extern bool_t deque_empty(const deque_t* cpt_deque);
extern size_t deque_size(const deque_t* cpt_deque);
extern size_t deque_max_size(const deque_t* cpt_deque);

/*
 * Iterator support.
 */
extern deque_iterator_t deque_begin(const deque_t* cpt_deque);
extern deque_iterator_t deque_end(const deque_t* cpt_deque);
/* private */
extern deque_reverse_iterator_t deque_rbegin(const deque_t* cpt_deque);
extern deque_reverse_iterator_t deque_rend(const deque_t* cpt_deque);

/*
 * Assign operator functions.
 */
extern void deque_assign(deque_t* pt_dequedest, const deque_t* cpt_dequesrc);
extern void deque_assign_range(
    deque_t* pt_deque, deque_iterator_t t_begin, deque_iterator_t t_end);

/*
 * Relationship operator functions.
 */
extern bool_t deque_equal(
    const deque_t* cpt_dequefirst, const deque_t* cpt_dequesecond);
extern bool_t deque_not_equal(
    const deque_t* cpt_dequefirst, const deque_t* cpt_dequesecond);
extern bool_t deque_less(
    const deque_t* cpt_dequefirst, const deque_t* cpt_dequesecond);
extern bool_t deque_great(
    const deque_t* cpt_dequefirst, const deque_t* cpt_dequesecond);
extern bool_t deque_less_equal(
    const deque_t* cpt_dequefirst, const deque_t* cpt_dequesecond);
extern bool_t deque_great_equal(
    const deque_t* cpt_dequefirst, const deque_t* cpt_dequesecond);

/*
 * Element access function.
 */
extern void* deque_at(const deque_t* cpt_deque, size_t t_pos);
extern void* deque_front(const deque_t* cpt_deque);
extern void* deque_back(const deque_t* cpt_deque);

/*
 * Swap the datas of first deque and second deque.
 */
extern void deque_swap(deque_t* pt_dequefirst, deque_t* pt_dequesecond);

/*
 * Pop element from deque_t.
 */
extern void deque_pop_back(deque_t* pt_deque);
extern void deque_pop_front(deque_t* pt_deque);

/*
 * Insert operation functions.
 */
extern void deque_insert_range(
    deque_t* pt_deque, deque_iterator_t t_pos, 
    deque_iterator_t t_begin, deque_iterator_t t_end);

/*
 * Erase operation functions.
 */
extern deque_iterator_t deque_erase(deque_t* pt_deque, deque_iterator_t t_pos);
extern deque_iterator_t deque_erase_range(
    deque_t* pt_deque, deque_iterator_t t_begin, deque_iterator_t t_end);
extern void deque_clear(deque_t* pt_deque);

/*
 * Resize operation functions.
 */
extern void deque_resize(deque_t* pt_deque, size_t t_resize);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_DEQUE_H */
/** eof **/

