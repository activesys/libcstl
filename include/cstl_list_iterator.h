/*
 *  The list iterator interface for iterator module.
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

#ifndef _CSTL_LIST_ITERATOR_H
#define _CSTL_LIST_ITERATOR_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
typedef iterator_t list_iterator_t;
typedef iterator_t list_reverse_iterator_t;
struct _taglist;

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: create_list_iterator
 *        Parameters: void
 *           Returns: list_iterator_t
 *                          new list iterator.
 *       Description: create new list iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern list_iterator_t create_list_iterator(void);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _list_iterator_get_value
 *        Parameters: in) cpt_list: const struct _taglist*
 *                            the list pointer.
 *                    in) cpt_iterator: const list_iterator_t*
 *                            the iterator pointer for getting value.
 *                    modify)pv_value: void*
 *                            the value pointer.
 *           Returns: void
 *       Description: get the value of current list iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern void _list_iterator_get_value(
    const struct _taglist* cpt_list,
    const list_iterator_t* cpt_iterator, 
    void* pv_value);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _list_iterator_set_value
 *        Parameters: in) cpt_list: const struct _taglist*
 *                            the list pointer.
 *                    in) cpt_iterator: const list_iterator_t*
 *                            the iterator pointer for getting value.
 *                    in) cpv_value: const void*
 *                            the value pointer.
 *           Returns: void
 *       Description: set the value of current list iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern void _list_iterator_set_value(
    const struct _taglist* cpt_list,
    const list_iterator_t* cpt_iterator, 
    const void* cpv_value);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _list_iterator_get_pointer
 *        Parameters: in) cpt_list: const struct _taglist*
 *                            the list pointer.
 *                    in) cpt_iterator: const list_iterator_t*
 *                            the iterator pointer for getting value.
 *           Returns: const void*
 *       Description: get the iterator pointer.
 *
 * ----------------------------------------------------------------------------
 */
extern const void* _list_iterator_get_pointer(
    const struct _taglist* cpt_list,
    const list_iterator_t* cpt_iterator); 

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _list_iterator_next
 *        Parameters: in) cpt_list: const struct _taglist*
 *                            the list pointer.
 *                    in) pt_iterator: list_iterator_t*
 *                            the iterator pointer for go to next position.
 *           Returns: void
 *       Description: to the next position of current list iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern void _list_iterator_next(
    const struct _taglist* cpt_list, list_iterator_t* pt_iterator);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _list_iterator_prev
 *        Parameters: in) cpt_list: const struct _taglist*
 *                            the list pointer.
 *                    in) pt_iterator: list_iterator_t*
 *                            the iterator pointer for go to previous position.
 *           Returns: void
 *       Description: to the previous position of current list iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern void _list_iterator_prev(
    const struct _taglist* cpt_list, list_iterator_t* pt_iterator);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _list_iterator_equal
 *        Parameters: in) cpt_list: const struct _taglist*
 *                            the list pointer.
 *                    in) cpt_iterator: const list_iterator_t*
 *                            the iterator pointer for getting value.
 *                    in) t_iterator: list_iterator_t
 *                            the iterator.
 *           Returns: bool_t
 *                            if the first iterator equal the second.
 *       Description: test if the first iterator equal the second.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t _list_iterator_equal(
    const struct _taglist* cpt_list,
    const list_iterator_t* cpt_iterator,
    list_iterator_t t_iterator);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _list_iterator_distance
 *        Parameters: in) cpt_begin: const list_iterator_t*
 *                            the iterator pointer to the first node.
 *                    in) cpt_end: const list_iterator_t*
 *                            the iterator pointer to the last node.
 *           Returns: int
 *                            the distance of two iterator
 *       Description: get the distance of two iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern int _list_iterator_distance(
    const list_iterator_t* cpt_begin, const list_iterator_t* cpt_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _list_iterator_before
 *        Parameters: in) cpt_iteratorfirst: const list_iterator_t*
 *                            first list iterator pointer.
 *                    in) cpt_iteratorsecond: const list_iterator_t*
 *                            second list iterator pointer.
 *           Returns: bool_t
 *       Description: test the first iterator before the second one.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t _list_iterator_before(
    const list_iterator_t* cpt_iteratorfirst, 
    const list_iterator_t* cpt_iteratorsecond);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_LIST_ITERATOR_H */
/** eof **/

