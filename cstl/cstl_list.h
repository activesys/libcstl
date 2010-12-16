/*
 *  The user interface of list.
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

#ifndef _CSTL_LIST_H
#define _CSTL_LIST_H

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
 *          element type of [it_begin, it_end) and plist_src must be the same, otherwise the behavior is undefined.
 */
extern void list_init_copy_range(list_t* plist_dest, list_iterator_t it_begin, list_iterator_t it_end);

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
 *          initialized, otherwise the behavior is undefined. if the two lists are not same type, then return false.
 *          if cplist_first == cplist_second, then return true.
 */
extern bool_t list_equal(const list_t* cplist_first, const list_t* cplist_second);

/**
 * Test the two lists are unequal.
 * @param cplist_first   first list container.
 * @param cplist_second  second list container.
 * @return if first list unequal to second list, then return true, else return false.
 * @remarks if cplist_first == NULL or cplist_second == NULL, then the behavior is undefined. the two lists must be
 *          initialized, otherwise the behavior is undefined. if the two lists are not same type, then return true.
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
extern void list_assign_range(list_t* plist_list, list_iterator_t it_begin, list_iterator_t it_end);

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

