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
 *  Author e-mail: activesys.wb@gmail.com
 *                 activesys@sina.com.cn
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
 * Initialization and destroy functions.
 */
extern void list_init(list_t* pt_list);
extern void list_init_n(list_t* pt_list, size_t t_count);
extern void list_destroy(list_t* pt_list);
extern void list_init_copy(list_t* pt_listdest, const list_t* cpt_listsrc);
extern void list_init_copy_range(
    list_t* pt_listdest, list_iterator_t t_begin, list_iterator_t t_end);

/*
 * list_t size operation functions.
 */
extern size_t list_size(const list_t* cpt_list);
extern bool_t list_empty(const list_t* cpt_list);
extern size_t list_max_size(const list_t* cpt_list);

/*
 * Relationship operator functions.
 */
extern bool_t list_equal(const list_t* cpt_listfirst, const list_t* cpt_listsecond);
extern bool_t list_not_equal(const list_t* cpt_listfirst, const list_t* cpt_listsecond);
extern bool_t list_less(const list_t* cpt_listfirst, const list_t* cpt_listsecond);
extern bool_t list_great(const list_t* cpt_listfirst, const list_t* cpt_listsecond);
extern bool_t list_less_equal(const list_t* cpt_listfirst, const list_t* cpt_listsecond);
extern bool_t list_great_equal(const list_t* cpt_listfirst, const list_t* cpt_listsecond);

/*
 * Assign operator functions.
 */
extern void list_assign(list_t* pt_listdest, const list_t* cpt_listsrc);
extern void list_assign_range(
    list_t* pt_list, list_iterator_t t_begin, list_iterator_t t_end);

/*
 * Swap the datas of first list and second list.
 */
extern void list_swap(list_t* pt_listfirst, list_t* pt_listsecond);

/*
 * Element access.
 */
extern void* list_front(const list_t* cpt_list);
extern void* list_back(const list_t* cpt_list);

/*
 * Iterator support.
 */
extern list_iterator_t list_begin(const list_t* cpt_list);
extern list_iterator_t list_end(const list_t* cpt_list);
/* private */
extern list_reverse_iterator_t list_rbegin(const list_t* cpt_list);
extern list_reverse_iterator_t list_rend(const list_t* cpt_list);

/*
 * Insert operation function.
 */
extern void list_insert_range(
    list_t* pt_list, list_iterator_t t_pos,
    list_iterator_t t_begin, list_iterator_t t_end);

/*
 * Pop element from list_t.
 */
extern void list_pop_back(list_t* pt_list);
extern void list_pop_front(list_t* pt_list);

/*
 * Erase operation functions.
 */
extern list_iterator_t list_erase(list_t* pt_list, list_iterator_t t_pos);
extern list_iterator_t list_erase_range(
    list_t* pt_list, list_iterator_t t_begin, list_iterator_t t_end);

/*
 * Remove all elements for which op yields true.
 */
extern void list_remove_if(list_t* pt_list, unary_function_t t_unary_op);

/*
 * Resize operatio functions.
 */
extern void list_resize(list_t* pt_list, size_t t_resize);

/*
 * Remove all elements.
 */
extern void list_clear(list_t* pt_list);

/*
 * Unique operatio functions.
 */
extern void list_unique(list_t* pt_list);
extern void list_unique_if(list_t* pt_list, binary_function_t t_binary_op);

/*
 * Splice operation functions.
 */
extern void list_splice(list_t* pt_list, list_iterator_t t_pos, list_t* pt_listsrc);
extern void list_splice_pos(
    list_t* pt_list, list_iterator_t t_pos, list_t* pt_listsrc, list_iterator_t t_possrc);
extern void list_splice_range(
    list_t* pt_list, list_iterator_t t_pos, 
    list_t* pt_listsrc, list_iterator_t t_begin, list_iterator_t t_end);

/*
 * Sort operation functions.
 */
extern void list_sort(list_t* pt_list);
extern void list_sort_if(list_t* pt_list, binary_function_t t_binary_op);

/*
 * Merge operation functions.
 */
extern void list_merge(list_t* pt_listdest, list_t* pt_listsrc);
extern void list_merge_if(
    list_t* pt_listdest, list_t* pt_listsrc, binary_function_t t_binary_op);

/*
 * Reverse the order of all elements.
 */
extern void list_reverse(list_t* pt_list);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_LIST_H */
/** eof **/

