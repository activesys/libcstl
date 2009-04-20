/*
 *  The user interface of list.
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

#ifndef _CSTL_LIST_H
#define _CSTL_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/* create new list with specific type */
#define create_list(type)\
    _create_list(sizeof(type), #type)
/* initialize */
#define list_init_elem(pt_list, t_count, elem)\
    _list_init_elem((pt_list), (t_count), (elem))
/* assign */
#define list_assign_elem(pt_list, t_count, elem)\
    _list_assign_elem((pt_list), (t_count), (elem))
/* push back and push front */
#define list_push_back(pt_list, elem)\
    _list_push_back((pt_list), (elem))
#define list_push_front(pt_list, elem)\
    _list_push_front((pt_list), (elem))
/* resize */
#define list_resize_elem(pt_list, t_count, elem)\
    _list_resize_elem((pt_list), (t_count), (elem))
/* remove */
#define list_remove(pt_list, elem)\
    _list_remove((pt_list), (elem))
/* insert */
#define list_insert(pt_list, t_pos, elem)\
    _list_insert_n((pt_list), (t_pos), 1, (elem))
#define list_insert_n(pt_list, t_pos, t_count, elem)\
    _list_insert_n((pt_list), (t_pos), (t_count), (elem))

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: list_init
 *        Parameters: in) pt_list: list_t*
 *           Returns: void
 *       Description: initialize the list.
 *
 * ----------------------------------------------------------------------------
 */
extern void list_init(list_t* pt_list);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: list_init_n
 *        Parameters: in) pt_list: list_t*
 *                    in) t_count: size_t
 *                          element count.
 *           Returns: void
 *       Description: initialize the list.
 *
 * ----------------------------------------------------------------------------
 */
extern void list_init_n(list_t* pt_list, size_t t_count);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: list_destroy
 *        Parameters: in) pt_list: list_t*
 *           Returns: void
 *       Description: destroy the list.
 *
 * ----------------------------------------------------------------------------
 */
extern void list_destroy(list_t* pt_list);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: list_init_copy
 *        Parameters: in) pt_listdest: list_t*
 *                          the dest list.
 *                    in) cpt_listsrc: const list_t*
 *                          the source list.
 *           Returns: void
 *       Description: the copy constructor.
 *
 * ----------------------------------------------------------------------------
 */
extern void list_init_copy(list_t* pt_listdest, const list_t* cpt_listsrc);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: list_init_copy_range
 *        Parameters: in) pt_listdest: list_t*
 *                          the dest list.
 *                    in) t_begin: list_iterator_t
 *                          the begin iterator.
 *                    in) t_end: list_iterator_t
 *                          the end iterator.
 *           Returns: void
 *       Description: copy the list with specific range.
 *
 * ----------------------------------------------------------------------------
 */
extern void list_init_copy_range(
    list_t* pt_listdest, list_iterator_t t_begin, list_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: list_size
 *        Parameters: in) cpt_list: const list_t*
 *                          the dest list.
 *           Returns: size_t
 *       Description: get the list size.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t list_size(const list_t* cpt_list);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: list_empty
 *        Parameters: in) cpt_list: const list_t*
 *                          the dest list.
 *           Returns: bool_t
 *       Description: if the list is empty.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t list_empty(const list_t* cpt_list);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: list_max_size
 *        Parameters: in) cpt_list: const list_t*
 *                          the dest list.
 *           Returns: size_t
 *       Description: get the maximum capacity of list.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t list_max_size(const list_t* cpt_list);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: list_equal
 *        Parameters: in) cpt_listfirst: const list_t*
 *                          the first list.
 *                    in) cpt_listsecond: const list_t*
 *                          the second list.
 *           Returns: bool_t
 *       Description: return whether first list equal to second list.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t list_equal(
    const list_t* cpt_listfirst, const list_t* cpt_listsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: list_not_equal
 *        Parameters: in) cpt_listfirst: const list_t*
 *                          the first list.
 *                    in) cpt_listsecond: const list_t*
 *                          the second list.
 *           Returns: bool_t
 *       Description: return whether first list not equal to second list.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t list_not_equal(
    const list_t* cpt_listfirst, const list_t* cpt_listsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: list_less
 *        Parameters: in) cpt_listfirst: const list_t*
 *                          the first list.
 *                    in) cpt_listsecond: const list_t*
 *                          the second list.
 *           Returns: bool_t
 *       Description: return whether first list less then second list.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t list_less(
    const list_t* cpt_listfirst, const list_t* cpt_listsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: list_great
 *        Parameters: in) cpt_listfirst: const list_t*
 *                          the first list.
 *                    in) cpt_listsecond: const list_t*
 *                          the second list.
 *           Returns: bool_t
 *       Description: return whether first list greater then second list.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t list_great(
    const list_t* cpt_listfirst, const list_t* cpt_listsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: list_less_equal
 *        Parameters: in) cpt_listfirst: const list_t*
 *                          the first list.
 *                    in) cpt_listsecond: const list_t*
 *                          the second list.
 *           Returns: bool_t
 *       Description: return whether first list less then or equal to the 
 *                    second list.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t list_less_equal(
    const list_t* cpt_listfirst, const list_t* cpt_listsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: list_great_equal
 *        Parameters: in) cpt_listfirst: const list_t*
 *                          the first list.
 *                    in) cpt_listsecond: const list_t*
 *                          the second list.
 *           Returns: bool_t
 *       Description: return whether first list greater then or equal to the
 *                    second list.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t list_great_equal(
    const list_t* cpt_listfirst, const list_t* cpt_listsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: list_assign
 *        Parameters: in) pt_listdest: list_t*
 *                          the dest list.
 *                    in) cpt_listsrc: const list_t*
 *                          the source list.
 *           Returns: void
 *       Description: the assignment operator.
 *
 * ----------------------------------------------------------------------------
 */
extern void list_assign(list_t* pt_listdest, const list_t* cpt_listsrc);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: list_assign_range
 *        Parameters: in) pt_list: list_t*
 *                          the list for assign.
 *                    in) t_begin: list_iterator_t
 *                          the begin iterator.
 *                    in) t_end: list_iterator_t
 *                          the end iterator.
 *           Returns: void
 *       Description: assign the elements of range [t_begin, t_end)
 *
 * ----------------------------------------------------------------------------
 */
extern void list_assign_range(
    list_t* pt_list, list_iterator_t t_begin, list_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: list_swap
 *        Parameters: in) pt_listfirst: list_t*
 *                          the first list.
 *                    in) pt_listsecond: list_t*
 *                          the second list.
 *           Returns: void
 *       Description: swap the datas of first list and second list.
 *
 * ----------------------------------------------------------------------------
 */
extern void list_swap(list_t* pt_listfirst, list_t* pt_listsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: list_front
 *        Parameters: in) cpt_list: const list_t*
 *                          the list.
 *           Returns: void*
 *       Description: return the first element.
 *
 * ----------------------------------------------------------------------------
 */
extern void* list_front(const list_t* cpt_list);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: list_back
 *        Parameters: in) cpt_list: const list_t*
 *                          the list.
 *           Returns: void
 *       Description: return the last element.
 *
 * ----------------------------------------------------------------------------
 */
extern void* list_back(const list_t* cpt_list);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: list_begin
 *        Parameters: in) cpt_list: const list_t*
 *                          the list.
 *           Returns: list_iterator_t
 *       Description: return the random access iterator for the first element.
 *
 * ----------------------------------------------------------------------------
 */
extern list_iterator_t list_begin(const list_t* cpt_list);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: list_end
 *        Parameters: in) cpt_list: const list_t*
 *                          the list.
 *           Returns: list_iterator_t
 *       Description: return the random access iterator for the last element.
 *
 * ----------------------------------------------------------------------------
 */
extern list_iterator_t list_end(const list_t* cpt_list);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: list_rbegin
 *        Parameters: in) cpt_list: const list_t*
 *                          the list.
 *           Returns: list_reverse_iterator_t
 *       Description: return the reverse iterator for the first element of the
 *                    reverse iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern list_reverse_iterator_t list_rbegin(const list_t* cpt_list);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: list_rend
 *        Parameters: in) cpt_list: const list_t*
 *                          the list.
 *           Returns: list_reverse_iterator_t
 *       Description: return the reverse iterator for the last element of the
 *                    reverse iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern list_reverse_iterator_t list_rend(const list_t* cpt_list);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: list_insert_range
 *        Parameters: in) pt_list: list_t*
 *                          the list.
 *                    in) t_pos: list_iterator_t
 *                          the insert position.
 *                    in) t_begin: list_iterator_t
 *                          the begin insert position.
 *                    in) t_end: list_iterator_t
 *                          the end insert position.
 *           Returns: void
 *       Description: insert at iterator position t_pos a copy of all elements 
 *                    of range [t_begin, t_end) and return nothing.
 *
 * ----------------------------------------------------------------------------
 */
extern void list_insert_range(
    list_t* pt_list, list_iterator_t t_pos, 
    list_iterator_t t_begin, list_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: list_pop_back
 *        Parameters: in) pt_list: list_t*
 *                          the list.
 *           Returns: void
 *       Description: remove the last element and does not return it.
 *
 * ----------------------------------------------------------------------------
 */
extern void list_pop_back(list_t* pt_list);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: list_pop_front
 *        Parameters: in) pt_list: list_t*
 *                          the list.
 *           Returns: void
 *       Description: remove the first element and does not return it.
 *
 * ----------------------------------------------------------------------------
 */
extern void list_pop_front(list_t* pt_list);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: list_erase
 *        Parameters: in) pt_list: list_t*
 *                          the list.
 *                    in) t_pos: list_iterator_t
 *                          the erase position
 *           Returns: list_iterator_t
 *       Description: remove the element at the iterator position t_pos and 
 *                    return the position of next element.
 *
 * ----------------------------------------------------------------------------
 */
extern list_iterator_t list_erase(list_t* pt_list, list_iterator_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: list_erase_range
 *        Parameters: in) pt_list: list_t*
 *                          the list.
 *                    in) t_begin: list_iterator_t
 *                          the begin position of erase range
 *                    in) t_end: list_iterator_t
 *                          the end position of erase range
 *           Returns: list_iterator_t
 *       Description: remove all elements of the range [t_begin, t_end) and 
 *                    return the position of next element.
 *
 * ----------------------------------------------------------------------------
 */
extern list_iterator_t list_erase_range(
    list_t* pt_list, list_iterator_t t_begin, list_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: list_remove_if
 *        Parameters: in) pt_list: list_t*
 *                          the list.
 *                    in) t_unary_op: unary_function_t
 *           Returns: void
 *       Description: remove all elements for which op yields true.
 *
 * ----------------------------------------------------------------------------
 */
extern void list_remove_if(list_t* pt_list, unary_function_t t_unary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: list_resize
 *        Parameters: in) pt_list: list_t*
 *                          the list.
 *                    in) t_resize: size_t
 *                          the new size of list.
 *           Returns: void
 *       Description: change the number of elements to t_resize, if the size
 *                    grows new element create with the default 0.
 *
 * ----------------------------------------------------------------------------
 */
extern void list_resize(list_t* pt_list, size_t t_resize);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: list_clear
 *        Parameters: in) pt_list: list_t*
 *                          the list.
 *           Returns: void
 *       Description: remove all elements.
 *
 * ----------------------------------------------------------------------------
 */
extern void list_clear(list_t* pt_list);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: list_unique
 *        Parameters: in) pt_list: list_t*
 *                          the list.
 *           Returns: void
 *       Description: remove duplicates of consecutive elements with the same
 *                    value.
 *
 * ----------------------------------------------------------------------------
 */
extern void list_unique(list_t* pt_list);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: list_unique_if
 *        Parameters: in) pt_list: list_t*
 *                          the list.
 *                    in) t_binary_op: binary_function_t
 *           Returns: void
 *       Description: remove duplicates of consecutive elements for which op()
 *                    yields true.
 *
 * ----------------------------------------------------------------------------
 */
extern void list_unique_if(list_t* pt_list, binary_function_t t_binary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: list_splice
 *        Parameters: in) pt_list: list_t*
 *                          the list.
 *                    in) t_pos: list_iterator_t
 *                          the insert position
 *                    in) pt_listsrc: list_t*
 *                          the source list.
 *           Returns: void
 *       Description: move all elements of source list to list in front of 
 *                    iterator position t_pos.
 *
 * ----------------------------------------------------------------------------
 */
extern void list_splice(
    list_t* pt_list, list_iterator_t t_pos, list_t* pt_listsrc);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: list_splice_pos
 *        Parameters: in) pt_list: list_t*
 *                          the list.
 *                    in) t_pos: list_iterator_t
 *                          the insert position
 *                    in) pt_listsrc: list_t*
 *                          the source list.
 *                    in) t_possrc: list_iterator_t
 *                          the begin position in source list
 *           Returns: void
 *       Description: move the element at t_possrc in listsrc in front of
 *                    t_pos of list (list and listsrc may be identical).
 *
 * ----------------------------------------------------------------------------
 */
extern void list_splice_pos(
    list_t* pt_list, list_iterator_t t_pos, 
    list_t* pt_listsrc, list_iterator_t t_possrc);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: list_splice_range
 *        Parameters: in) pt_list: list_t*
 *                          the list.
 *                    in) t_pos: list_iterator_t
 *                          the insert position
 *                    in) pt_listsrc: list_t*
 *                          the source list.
 *                    in) t_begin: list_iterator_t
 *                          the begin position in source list
 *                    in) t_end: list_iterator_t
 *                          the end position in source list
 *           Returns: void
 *       Description: move the elements in range [t_begin, t_end) in listsrc 
 *                    in front of t_pos of list (list and listsrc may be 
 *                    identical).
 *
 * ----------------------------------------------------------------------------
 */
extern void list_splice_range(
    list_t* pt_list, 
    list_iterator_t t_pos, 
    list_t* pt_listsrc, 
    list_iterator_t t_begin, 
    list_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: list_sort
 *        Parameters: in) pt_list: list_t*
 *                          the list.
 *           Returns: void
 *       Description: sort all elements with operator <.
 *
 * ----------------------------------------------------------------------------
 */
extern void list_sort(list_t* pt_list);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: list_sort_if
 *        Parameters: in) pt_list: list_t*
 *                          the list.
 *                    in) t_binary_op: binary_function_t
 *           Returns: void
 *       Description: sort all elements with operator pfun_op function.
 *
 * ----------------------------------------------------------------------------
 */
extern void list_sort_if(list_t* pt_list, binary_function_t t_binary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: list_merge
 *        Parameters: in) pt_listdest: list_t*
 *                          the dest list.
 *                    in) pt_listsrc: list_t*
 *                          the source list.
 *           Returns: void
 *       Description: assuming both container contain the elements sorted, move
 *                    all elements of source list into dest list so that all
 *                    elements merged and still sorted.
 *
 * ----------------------------------------------------------------------------
 */
extern void list_merge(list_t* pt_listdest, list_t* pt_listsrc);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: list_merge_if
 *        Parameters: in) pt_listdest: list_t*
 *                          the dest list.
 *                    in) pt_listsrc: list_t*
 *                          the source list.
 *                    in) t_binary_op: binary_function_t 
 *           Returns: void
 *       Description: assuming both container contain the elements sorted, move
 *                    all elements of source list into dest list so that all
 *                    elements merged and still sorted (with the confition
 *                    function pfun_op).
 *
 * ----------------------------------------------------------------------------
 */
extern void list_merge_if(
    list_t* pt_listdest, list_t* pt_listsrc, binary_function_t t_binary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: list_reverse
 *        Parameters: in) pt_list: list_t*
 *                          the list.
 *           Returns: void
 *       Description: reverse the order of all elements.
 *
 * ----------------------------------------------------------------------------
 */
extern void list_reverse(list_t* pt_list);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_LIST_H */
/** eof **/

