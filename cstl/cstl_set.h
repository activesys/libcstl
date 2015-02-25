/*
 *  The interface of set.
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

#ifndef _CSTL_SET_H_
#define _CSTL_SET_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/**
 * Create set container.
 * @param ...        element type name.
 * @return if create set successfully return set pointer, otherwise return NULL.
 * @remarks element type name should be C builtin type name, libcstl builtin typename or registed user defined type name,
 *          otherwise the function will return NULL.
 */
#define create_set(...) _create_set(#__VA_ARGS__) 

/**
 * Find specific element.
 * @param cpset_set      set container.
 * @param elem         specific element.
 * @return iterator addresses the sprcific element in the set, otherwise return set_end().
 * @remarks if cpset_set == NULL then the behavior is undefined. cpset_set must be initialized, otherwise the behavior is undefined.
 *          the type of specific element and cpset_set must be same, otherwise the behavior is undefined.
 */
#define set_find(cpset_set, elem) _set_find((cpset_set), (elem))

/**
 * Return the number of specific elements in an set
 * @param cpset_set       set container.
 * @param elem          specific element.
 * @return the number of specific elements.
 * @remarks if cpset_set == NULL then the behavior is undefined. cpset_set must be initialized, otherwise the behavior is undefined.
 *          the type of specific element and cpset_set must be same, otherwise the behavior is undefined.
 */
#define set_count(cpset_set, elem) _set_count((cpset_set), (elem))

/**
 * Return an iterator to the first element that is equal to or greater than a specific element.
 * @param cpset_set      set container.
 * @param elem         specific element.
 * @return an iterator to the first element that is equal to or greater than a specific element.
 * @remarks if cpset_set == NULL then the behavior is undefined. cpset_set must be initialized, otherwise the behavior is undefined.
 *          the type of specific element and cpset_set must be same, otherwise the behavior is undefined.
 */
#define set_lower_bound(cpset_set, elem) _set_lower_bound((cpset_set), (elem))

/**
 * Return an iterator to the first element that is greater than a specific element.
 * @param cpset_set      set container.
 * @param elem         specific element.
 * @return an iterator to the first element that is greater than a specific element.
 * @remarks if cpset_set == NULL then the behavior is undefined. cpset_set must be initialized, otherwise the behavior is undefined.
 *          the type of specific element and cpset_set must be same, otherwise the behavior is undefined.
 */
#define set_upper_bound(cpset_set, elem) _set_upper_bound((cpset_set), (elem))

/**
 * Return an iterator range that is equal to a specific element.
 * @param cpset_set      set container.
 * @param elem         specific element.
 * @return an iterator range that is equal to a specific element.
 * @remarks if cpset_set == NULL then the behavior is undefined. cpset_set must be initialized, otherwise the behavior is undefined.
 *          the type of specific element and cpset_set must be same, otherwise the behavior is undefined.
 */
#define set_equal_range(cpset_set, elem) _set_equal_range((cpset_set), (elem))

/**
 * Erase an element from a set that match a specified element.
 * @param pset_set       set container.
 * @param elem           specific element.
 * @return the number of erased elements.
 * @remarks if pset_set == NULL then the behavior is undefined. cpset_set must be initialized, otherwise the behavior is undefined. 
 */
#define set_erase(pset_set, elem) _set_erase((pset_set), (elem))

/**
 * Inserts an unique element into a set.
 * @param pset_set       set container.
 * @param elem           specific element.
 * @return an iterator addresses the inserted element, or set end if insert failed.
 * @remarks if pset_set == NULL then the behavior is undefined. cpset_set must be initialized, otherwise the behavior is undefined.
 *          the type of specific element and cpset_set must be same, otherwise the behavior is undefined.
 */
#define set_insert(pset_set, elem) _set_insert((pset_set), (elem))

/**
 * Inserts an unique element into a set with hint position.
 * @param pset_set       set container.
 * @param it_hint        hint position.
 * @param elem           specific element.
 * @return an iterator addresses the inserted element, or set end if insert failed.
 * @remarks if pset_set == NULL then the behavior is undefined. cpset_set must be initialized, otherwise the behavior is undefined.
 *          the type of specific element and cpset_set must be same, otherwise the behavior is undefined.
 */
#define set_insert_hint(pset_set, it_hint, elem) _set_insert_hint((pset_set), (it_hint), (elem))

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Initialize set container.
 * @param pset_set          set container.
 * @return void.
 * @remarks if pset_set == NULL, then the behavior is undefined, pset_set must be created by create_set(), otherwise
 *          the behavior is undefined. the default compare function is used.
 */
extern void set_init(set_t* pset_set);

/**
 * Initialize set container with user define compare function.
 * @param pset_set          set container.
 * @param bfun_compare         compare function.
 * @return void.
 * @remarks if pset_set == NULL, then the behavior is undefined, pset_set must be created by create_set(), otherwise
 *          the behavior is undefined. if bfun_compare == NULL, the default compare function is used.
 */
extern void set_init_ex(set_t* pset_set, bfun_t bfun_compare);

/**
 * Initialize set container with set.
 * @param pset_dest           destination set.
 * @param cpset_src           source set.
 * @return void.
 * @remarks if pset_dest == NULL or cpset_src == NULL, then the behavior is undefined, pset_dest must be created by
 *          create_set(), cpset_src must be initialized, otherwise the behavior is undefined. the element type of
 *          pset_dest and cpset_src must be same, otherwise the behavior is undefine.
 */
extern void set_init_copy(set_t* pset_dest, const set_t* cpset_src);

/**
 * Initialize set container with specific range.
 * @param pset_dest         destination set.
 * @param it_begin          begin of range.
 * @param it_end            end of range.
 * @return void.
 * @remarks if pset_dest == NULL, then the behavior is undefined, pset_dest must be created by create_set(), otherwise
 *          the behavior is undefined. the type of [it_begin, it_end) and pset_dest must be same, otherwise the behavior
 *          is undefined.
 */
extern void set_init_copy_range(set_t* pset_dest, iterator_t it_begin, iterator_t it_end);

/**
 * Initialize set container with specific array.
 * @param pset_dest         destination set.
 * @param cpv_array         array.
 * @param t_count           element count of array.
 * @return void.
 * @remarks if pset_dest == NULL, then the behavior is undefined, pset_dest must be created by create_set(), otherwise
 *          the behavior is undefined. the type of array and pset_dest must be same, otherwise the behavior
 *          is undefined.
 */
extern void set_init_copy_array(set_t* pset_dest, const void* cpv_array, size_t t_count);

/**
 * Initialize set container with specific range and compare function.
 * @param pset_dest         destination set.
 * @param it_begin          begin of range.
 * @param it_end            end of range.
 * @param bfun_compare      compare function.
 * @return void.
 * @remarks if pset_dest == NULL, then the behavior is undefined, pset_dest must be created by _create_set(), otherwise
 *          the behavior is undefined. the type of [it_begin, it_end) and pset_dest must be same, otherwise the behavior
 *          is undefined. if bfun_compare == NULL, then use default compare function.
 */
extern void set_init_copy_range_ex(
    set_t* pset_dest, iterator_t it_begin, iterator_t it_end, bfun_t bfun_compare);

/**
 * Initialize set container with specific array and compare function.
 * @param pset_dest         destination set.
 * @param cpv_array         array.
 * @param t_count           element count of array.
 * @param bfun_compare      compare function.
 * @return void.
 * @remarks if pset_dest == NULL, then the behavior is undefined, pset_dest must be created by _create_set(), otherwise
 *          the behavior is undefined. the type of array and pset_dest must be same, otherwise the behavior
 *          is undefined. if bfun_compare == NULL, then use default compare function.
 */
extern void set_init_copy_array_ex(
    set_t* pset_dest, const void* cpv_array, size_t t_count, bfun_t bfun_compare);

/**
 * Destroy set.
 * @param pset_set       set container.
 * @return void.
 * @remarks if pset_set == NULL, then the behavior is undefined, the set must be initialized or created by create_set(),
 *          otherwise the behavior is undefined.
 */
extern void set_destroy(set_t* pset_set);

/**
 * Assign set container.
 * @param pset_dest           destination set container.
 * @param cpset_src           source set container.
 * @return void.
 * @remarks if pset_dest == NULL or cpset_src == NULL, the the behavior is undefined. two set must be initialized, otherwise
 *          the behavior is undefined. if set_equal(pset_dest, cpset_src), the function dest nothing.
 */
extern void set_assign(set_t* pset_dest, const set_t* cpset_src);

/**
 * Get the number of elements int the set.
 * @param cpset_set      set container.
 * @return the number of elements in the set.
 * @remarks if cpset_set == NULL, then the behavior is undefined, the cpset_set must be initialized, otherwise the behavior
 *          is undefined.
 */
extern size_t set_size(const set_t* cpset_set);

/**
 * Test if an set is empty.
 * @param cpset_set      set container.
 * @return true if the set is empty, otherwise return false.
 * @remarks if cpset_set == NULL, then the behavior is undefined, the cpset_set must be initialized, otherwise the behavior
 *          is undefined.
 */
extern bool_t set_empty(const set_t* cpset_set);

/**
 * Get the maximum number of elements int the set.
 * @param cpset_set      set container.
 * @return the maximum number of elements in the set.
 * @remarks if cpset_set == NULL, then the behavior is undefined, the cpset_set must be initialized, otherwise the behavior
 *          is undefined.
 */
extern size_t set_max_size(const set_t* cpset_set);

/**
 * Return an iterator that addresses the first element in the set.
 * @param cpset_set      set container.
 * @return an iterator that addresses the first element in the set.
 * @remarks if cpset_set == NULL, the behavior is undefined. cpset_set must be initialized, otherwise the behavior is undefined.
 *          return set_end(), if the set is empty.
 */
extern set_iterator_t set_begin(const set_t* cpset_set);

/**
 * Return an iterator that addresses the location succeeding the last element in the set.
 * @param cpset_set      set container.
 * @return an iterator that addresses location succeeding the last element in the set.
 * @remarks if cpset_set == NULL, the behavior is undefined. cpset_set must be initialized, otherwise the behavior is undefined.
 */
extern set_iterator_t set_end(const set_t* cpset_set);
/* private */
extern set_reverse_iterator_t set_rbegin(const set_t* cpset_set);
extern set_reverse_iterator_t set_rend(const set_t* cpset_set);

/**
 * Return the compare function of key.
 * @param cpset_set      set container.
 * @return compare function.
 * @remarks if cpset_set == NULL, the behavior is undefined. cpset_set must be initialized, otherwise the behavior is undefined.
 */
extern bfun_t set_key_comp(const set_t* cpset_set);

/**
 * Return the compare function of value.
 * @param cpset_set      set container.
 * @return compare function.
 * @remarks if cpset_set == NULL, the behavior is undefined. cpset_set must be initialized, otherwise the behavior is undefined.
 */
extern bfun_t set_value_comp(const set_t* cpset_set);

/**
 * Erases all the elements of an set.
 * @param pset_set       set container.
 * @return void.
 * @remarks if pset_set == NULL, the behavior is undefined. pset_set must be initialized, otherwise the behavior is undefined.
 */
extern void set_clear(set_t* pset_set);

/**
 * Tests if the two set are equal.
 * @param cpset_first         first set container.
 * @param cpset_second        second set container.
 * @return if first set equal to second set, then return true, else return false.
 * @remarks if cpset_first == NULL or cpset_second == NULL, then the behavior is undefined. the two set must be
 *          initialized, otherwise the behavior is undefined. if the two set are not same type, the behavior is undefined.
 *          if cpset_first == cpset_second, then return true.
 */
extern bool_t set_equal(const set_t* cpset_first, const set_t* cpset_second);

/**
 * Tests if the two set are not equal.
 * @param cpset_first         first set container.
 * @param cpset_second        second set container.
 * @return if first set not equal to second set, then return true, else return false.
 * @remarks if cpset_first == NULL or cpset_second == NULL, then the behavior is undefined. the two set must be
 *          initialized, otherwise the behavior is undefined. if the two set are not same type, the behavior is undefined.
 *          if cpset_first == cpset_second, then return false.
 */
extern bool_t set_not_equal(const set_t* cpset_first, const set_t* cpset_second);

/**
 * Tests if the first set is less than the second set.
 * @param cpset_first         first set container.
 * @param cpset_second        second set container.
 * @return if first set is less than the second set, then return true, else return false.
 * @remarks if cpset_first == NULL or cpset_second == NULL, then the behavior is undefined. the two set must be
 *          initialized, otherwise the behavior is undefined. if the two set are not same type, the behavior is
 *          undefined. if cpset_first == cpset_second, then return false.
 */
extern bool_t set_less(const set_t* cpset_first, const set_t* cpset_second);

/**
 * Tests if the first set is less than or equal to the second set.
 * @param cpset_first         first set container.
 * @param cpset_second        second set container.
 * @return if first set is less than or equal to the second set, then return true, else return false.
 * @remarks if cpset_first == NULL or cpset_second == NULL, then the behavior is undefined. the two set must be
 *          initialized, otherwise the behavior is undefined. if the two set are not same type, the behavior is
 *          undefined. if cpset_first == cpset_second, then return true.
 */
extern bool_t set_less_equal(const set_t* cpset_first, const set_t* cpset_second);

/**
 * Tests if the first set is greater than the second set.
 * @param cpset_first         first set container.
 * @param cpset_second        second set container.
 * @return if first set is greater than the second set, then return true, else return false.
 * @remarks if cpset_first == NULL or cpset_second == NULL, then the behavior is undefined. the two set must be
 *          initialized, otherwise the behavior is undefined. if the two set are not same type, the behavior is
 *          undefined. if cpset_first == cpset_second, then return false.
 */
extern bool_t set_greater(const set_t* cpset_first, const set_t* cpset_second);

/**
 * Tests if the first set is greater than or equal to the second set.
 * @param cpset_first         first set container.
 * @param cpset_second        second set container.
 * @return if first set is greater than or equal to the second set, then return true, else return false.
 * @remarks if cpset_first == NULL or cpset_second == NULL, then the behavior is undefined. the two set must be
 *          initialized, otherwise the behavior is undefined. if the two set are not same type, the behavior is
 *          undefined. if cpset_first == cpset_second, then return true.
 */
extern bool_t set_greater_equal(const set_t* cpset_first, const set_t* cpset_second);

/**
 * Swap the datas of first set and second set.
 * @param pt_first          first set container.
 * @param pt_second         second set container.
 * @return void.
 * @remarks if pt_first == NULL or pt_second == NULL, then the behavior is undefined. the two set must be initialized,
 *          otherwise the behavior is undefined. if the two set are not same type, the behavior is undefined. if
 *          set_equal(cpt_first, cpt_second), then the function do nothing.
 */
extern void set_swap(set_t* pset_first, set_t* pset_second);

/**
 * Inserts an range of unique element into a set.
 * @param pset_set          set container.
 * @param it_begin          begin of specific range.
 * @param it_end            end of specific range.
 * @return void.
 * @remarks if pset_set == NULL then the behavior is undefined. pset_set must be initialized, otherwise the behavior
 *          is undefined. the type of [it_begin, it_end) and cpset_set must be same, otherwise the behavior is undefined.
 *          [it_begin, it_end) must be valid range, otherwise the behavior is undefine.
 */
extern void set_insert_range(set_t* pset_set, iterator_t it_begin, iterator_t it_end);

/**
 * Inserts an array of unique element into a set.
 * @param pset_set          set container.
 * @param cpv_array         array.
 * @param t_count           element count of array.
 * @return void.
 * @remarks if pset_set == NULL then the behavior is undefined. pset_set must be initialized, otherwise the behavior
 *          is undefined. the type of array and cpset_set must be same, otherwise the behavior is undefined.
 *          array must be valid range, otherwise the behavior is undefine.
 */
extern void set_insert_array(set_t* pset_set, const void* cpv_array, size_t t_count);

/*
 * Erase an element in an set from specificed position.
 * @param pset_set          set container.
 * @param it_pos            specificed position.
 * @return void.
 * @remarks if pset_set == NULL then the behavior is undefined. pset_set must be initialized, otherwise the behavior
 *          is undefined. it_pos must be valid iterator, otherwise the behavior is undefined.
 */
extern void set_erase_pos(set_t* pset_set, set_iterator_t it_pos);

/*
 * Erase a range of element in an set.
 * @param pset_set          set container.
 * @param it_begin          begin of specific range.
 * @param it_end            end of specific range.
 * @return void.
 * @remarks if pset_set == NULL then the behavior is undefined. pset_set must be initialized, otherwise the behavior
 *          is undefined. [it_begin, it_end) must be valid range for pset_set, otherwise the behavior is undefine.
 */
extern void set_erase_range(set_t* pset_set, set_iterator_t it_begin, set_iterator_t it_end);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_SET_H_ */
/** eof **/

