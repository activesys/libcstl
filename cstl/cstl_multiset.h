/*
 *  The interface of multiset.
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

#ifndef _CSTL_MULTISET_H_
#define _CSTL_MULTISET_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/**
 * Create multiset container.
 * @param ...        element type name.
 * @return if create multiset successfully return multiset pointer, otherwise return NULL.
 * @remarks element type name should be C builtin type name, libcstl builtin typename or registed user defined type name,
 *          otherwise the function will return NULL.
 */
#define create_multiset(...) _create_multiset(#__VA_ARGS__) 

/**
 * Find specific element.
 * @param cpmset_mset      multiset container.
 * @param elem         specific element.
 * @return iterator addresses the sprcific element in the multiset, otherwise return set_end().
 * @remarks if cpmset_mset == NULL then the behavior is undefined. cpmset_mset must be initialized, otherwise the behavior is undefined.
 *          the type of specific element and cpmset_mset must be same, otherwise the behavior is undefined.
 */
#define multiset_find(cpmset_mset, elem) _multiset_find((cpmset_mset), (elem))

/**
 * Return the number of specific elements in an multiset
 * @param cpmset_mset       multiset container.
 * @param elem          specific element.
 * @return the number of specific elements.
 * @remarks if cpmset_mset == NULL then the behavior is undefined. cpmset_mset must be initialized, otherwise the behavior is undefined.
 *          the type of specific element and cpmset_mset must be same, otherwise the behavior is undefined.
 */
#define multiset_count(cpmset_mset, elem) _multiset_count((cpmset_mset), (elem))

/**
 * Return an iterator to the first element that is equal to or greater than a specific element.
 * @param cpmset_mset      multiset container.
 * @param elem         specific element.
 * @return an iterator to the first element that is equal to or greater than a specific element.
 * @remarks if cpmset_mset == NULL then the behavior is undefined. cpmset_mset must be initialized, otherwise the behavior is undefined.
 *          the type of specific element and cpmset_mset must be same, otherwise the behavior is undefined.
 */
#define multiset_lower_bound(cpmset_mset, elem) _multiset_lower_bound((cpmset_mset), (elem))

/**
 * Return an iterator to the first element that is greater than a specific element.
 * @param cpmset_mset      multiset container.
 * @param elem         specific element.
 * @return an iterator to the first element that is greater than a specific element.
 * @remarks if cpmset_mset == NULL then the behavior is undefined. cpmset_mset must be initialized, otherwise the behavior is undefined.
 *          the type of specific element and cpmset_mset must be same, otherwise the behavior is undefined.
 */
#define multiset_upper_bound(cpmset_mset, elem) _multiset_upper_bound((cpmset_mset), (elem))

/**
 * Return an iterator range that is equal to a specific element.
 * @param cpmset_mset      multiset container.
 * @param elem         specific element.
 * @return an iterator range that is equal to a specific element.
 * @remarks if cpmset_mset == NULL then the behavior is undefined. cpmset_mset must be initialized, otherwise the behavior is undefined.
 *          the type of specific element and cpmset_mset must be same, otherwise the behavior is undefined.
 */
#define multiset_equal_range(cpmset_mset, elem) _multiset_equal_range((cpmset_mset), (elem))

/**
 * Erase an element from a multiset that match a specified element.
 * @param pmset_mset       multiset container.
 * @param elem           specific element.
 * @return the number of erased elements.
 * @remarks if pmset_mset == NULL then the behavior is undefined. cpmset_mset must be initialized, otherwise the behavior is undefined. 
 */
#define multiset_erase(pmset_mset, elem) _multiset_erase((pmset_mset), (elem))

/**
 * Inserts an element into a multiset.
 * @param pmset_mset       multiset container.
 * @param elem           specific element.
 * @return an iterator addresses the inserted element, or multiset end if insert failed.
 * @remarks if pmset_mset == NULL then the behavior is undefined. cpmset_mset must be initialized, otherwise the behavior is undefined.
 *          the type of specific element and cpmset_mset must be same, otherwise the behavior is undefined.
 */
#define multiset_insert(pmset_mset, elem) _multiset_insert((pmset_mset), (elem))

/**
 * Inserts an element into a multiset with hint position.
 * @param pmset_mset       multiset container.
 * @param it_hint        hint position.
 * @param elem           specific element.
 * @return an iterator addresses the inserted element, or multiset end if insert failed.
 * @remarks if pmset_mset == NULL then the behavior is undefined. cpmset_mset must be initialized, otherwise the behavior is undefined.
 *          the type of specific element and cpmset_mset must be same, otherwise the behavior is undefined.
 */
#define multiset_insert_hint(pmset_mset, it_hint, elem) _multiset_insert_hint((pmset_mset), (it_hint), (elem))

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Initialize multiset container.
 * @param pmset_mset          multiset container.
 * @return void.
 * @remarks if pmset_mset == NULL, then the behavior is undefined, pmset_mset must be created by create_set(), otherwise
 *          the behavior is undefined. the default compare function is used.
 */
extern void multiset_init(multiset_t* pmset_mset);

/**
 * Initialize multiset container with user define compare function.
 * @param pmset_mset          multiset container.
 * @param bfun_compare         compare function.
 * @return void.
 * @remarks if pmset_mset == NULL, then the behavior is undefined, pmset_mset must be created by create_set(), otherwise
 *          the behavior is undefined. if bfun_compare == NULL, the default compare function is used.
 */
extern void multiset_init_ex(multiset_t* pmset_mset, bfun_t bfun_compare);

/**
 * Initialize multiset container with multiset.
 * @param pmset_dest           destination multiset.
 * @param cpmset_src           source multiset.
 * @return void.
 * @remarks if pmset_dest == NULL or cpmset_src == NULL, then the behavior is undefined, pmset_dest must be created by
 *          create_set(), cpmset_src must be initialized, otherwise the behavior is undefined. the element type of
 *          pmset_dest and cpmset_src must be same, otherwise the behavior is undefine.
 */
extern void multiset_init_copy(multiset_t* pmset_dest, const multiset_t* cpmset_src);

/**
 * Initialize multiset container with specific range.
 * @param pmset_dest        destination multiset.
 * @param it_begin          begin of range.
 * @param it_end            end of range.
 * @return void.
 * @remarks if pmset_dest == NULL, then the behavior is undefined, pmset_dest must be created by create_set(), otherwise
 *          the behavior is undefined. the type of [it_begin, it_end) and pmset_dest must be same, otherwise the behavior
 *          is undefined.
 */
extern void multiset_init_copy_range(multiset_t* pmset_dest, iterator_t it_begin, iterator_t it_end);

/**
 * Initialize multiset container with specific array.
 * @param pmset_dest        destination multiset.
 * @param cpv_array         array.
 * @param t_count           element count of array.
 * @return void.
 * @remarks if pmset_dest == NULL, then the behavior is undefined, pmset_dest must be created by create_set(), otherwise
 *          the behavior is undefined. the type of array and pmset_dest must be same, otherwise the behavior is undefined.
 */
extern void multiset_init_copy_array(multiset_t* pmset_dest, const void* cpv_array, size_t t_count);

/**
 * Initialize multiset container with specific range and compare function.
 * @param pmset_dest        destination multiset.
 * @param it_begin          begin of range.
 * @param it_end            end of range.
 * @param bfun_compare      compare function.
 * @return void.
 * @remarks if pmset_dest == NULL, then the behavior is undefined, pmset_dest must be created by _create_set(), otherwise
 *          the behavior is undefined. the type of [it_begin, it_end) and pmset_dest must be same, otherwise the behavior
 *          is undefined. if bfun_compare == NULL, then use default compare function.
 */
extern void multiset_init_copy_range_ex(
    multiset_t* pmset_dest, iterator_t it_begin, iterator_t it_end, bfun_t bfun_compare);

/**
 * Initialize multiset container with specific array and compare function.
 * @param pmset_dest        destination multiset.
 * @param cpv_array         array.
 * @param t_count           element count of array.
 * @param bfun_compare      compare function.
 * @return void.
 * @remarks if pmset_dest == NULL, then the behavior is undefined, pmset_dest must be created by _create_set(), otherwise
 *          the behavior is undefined. the type of array and pmset_dest must be same, otherwise the behavior
 *          is undefined. if bfun_compare == NULL, then use default compare function.
 */
extern void multiset_init_copy_array_ex(
    multiset_t* pmset_dest, const void* cpv_array, size_t t_count, bfun_t bfun_compare);

/**
 * Destroy multiset.
 * @param pmset_mset       multiset container.
 * @return void.
 * @remarks if pmset_mset == NULL, then the behavior is undefined, the multiset must be initialized or created by create_set(),
 *          otherwise the behavior is undefined.
 */
extern void multiset_destroy(multiset_t* pmset_mset);

/**
 * Assign multiset container.
 * @param pmset_dest           destination multiset container.
 * @param cpmset_src           source multiset container.
 * @return void.
 * @remarks if pmset_dest == NULL or cpmset_src == NULL, the the behavior is undefined. two multiset must be initialized, otherwise
 *          the behavior is undefined. if set_equal(pmset_dest, cpmset_src), the function dest nothing.
 */
extern void multiset_assign(multiset_t* pmset_dest, const multiset_t* cpmset_src);

/**
 * Get the number of elements int the multiset.
 * @param cpmset_mset      multiset container.
 * @return the number of elements in the multiset.
 * @remarks if cpmset_mset == NULL, then the behavior is undefined, the cpmset_mset must be initialized, otherwise the behavior
 *          is undefined.
 */
extern size_t multiset_size(const multiset_t* cpmset_mset);

/**
 * Test if an multiset is empty.
 * @param cpmset_mset      multiset container.
 * @return true if the multiset is empty, otherwise return false.
 * @remarks if cpmset_mset == NULL, then the behavior is undefined, the cpmset_mset must be initialized, otherwise the behavior
 *          is undefined.
 */
extern bool_t multiset_empty(const multiset_t* cpmset_mset);

/**
 * Get the maximum number of elements int the multiset.
 * @param cpmset_mset      multiset container.
 * @return the maximum number of elements in the multiset.
 * @remarks if cpmset_mset == NULL, then the behavior is undefined, the cpmset_mset must be initialized, otherwise the behavior
 *          is undefined.
 */
extern size_t multiset_max_size(const multiset_t* cpmset_mset);

/**
 * Return an iterator that addresses the first element in the multiset.
 * @param cpmset_mset      multiset container.
 * @return an iterator that addresses the first element in the multiset.
 * @remarks if cpmset_mset == NULL, the behavior is undefined. cpmset_mset must be initialized, otherwise the behavior is undefined.
 *          return set_end(), if the multiset is empty.
 */
extern multiset_iterator_t multiset_begin(const multiset_t* cpmset_mset);

/**
 * Return an iterator that addresses the location succeeding the last element in the multiset.
 * @param cpmset_mset      multiset container.
 * @return an iterator that addresses location succeeding the last element in the multiset.
 * @remarks if cpmset_mset == NULL, the behavior is undefined. cpmset_mset must be initialized, otherwise the behavior is undefined.
 */
extern multiset_iterator_t multiset_end(const multiset_t* cpmset_mset);
/* private */
extern multiset_reverse_iterator_t multiset_rbegin(const multiset_t* cpmset_mset);
extern multiset_reverse_iterator_t multiset_rend(const multiset_t* cpmset_mset);

/**
 * Return the compare function of key.
 * @param cpmset_mset      multiset container.
 * @return compare function.
 * @remarks if cpmset_mset == NULL, the behavior is undefined. cpmset_mset must be initialized, otherwise the behavior is undefined.
 */
extern bfun_t multiset_key_comp(const multiset_t* cpmset_mset);

/**
 * Return the compare function of value.
 * @param cpmset_mset      multiset container.
 * @return compare function.
 * @remarks if cpmset_mset == NULL, the behavior is undefined. cpmset_mset must be initialized, otherwise the behavior is undefined.
 */
extern bfun_t multiset_value_comp(const multiset_t* cpmset_mset);

/**
 * Erases all the elements of an multiset.
 * @param pmset_mset       multiset container.
 * @return void.
 * @remarks if pmset_mset == NULL, the behavior is undefined. pmset_mset must be initialized, otherwise the behavior is undefined.
 */
extern void multiset_clear(multiset_t* pmset_mset);

/**
 * Tests if the two multiset are equal.
 * @param cpmset_first         first multiset container.
 * @param cpmset_second        second multiset container.
 * @return if first multiset equal to second multiset, then return true, else return false.
 * @remarks if cpmset_first == NULL or cpmset_second == NULL, then the behavior is undefined. the two multiset must be
 *          initialized, otherwise the behavior is undefined. if the two multiset are not same type, the behavior is undefined.
 *          if cpmset_first == cpmset_second, then return true.
 */
extern bool_t multiset_equal(const multiset_t* cpmset_first, const multiset_t* cpmset_second);

/**
 * Tests if the two multiset are not equal.
 * @param cpmset_first         first multiset container.
 * @param cpmset_second        second multiset container.
 * @return if first multiset not equal to second multiset, then return true, else return false.
 * @remarks if cpmset_first == NULL or cpmset_second == NULL, then the behavior is undefined. the two multiset must be
 *          initialized, otherwise the behavior is undefined. if the two multiset are not same type, the behavior is undefined.
 *          if cpmset_first == cpmset_second, then return false.
 */
extern bool_t multiset_not_equal(const multiset_t* cpmset_first, const multiset_t* cpmset_second);

/**
 * Tests if the first multiset is less than the second multiset.
 * @param cpmset_first         first multiset container.
 * @param cpmset_second        second multiset container.
 * @return if first multiset is less than the second multiset, then return true, else return false.
 * @remarks if cpmset_first == NULL or cpmset_second == NULL, then the behavior is undefined. the two multiset must be
 *          initialized, otherwise the behavior is undefined. if the two multiset are not same type, the behavior is
 *          undefined. if cpmset_first == cpmset_second, then return false.
 */
extern bool_t multiset_less(const multiset_t* cpmset_first, const multiset_t* cpmset_second);

/**
 * Tests if the first multiset is less than or equal to the second multiset.
 * @param cpmset_first         first multiset container.
 * @param cpmset_second        second multiset container.
 * @return if first multiset is less than or equal to the second multiset, then return true, else return false.
 * @remarks if cpmset_first == NULL or cpmset_second == NULL, then the behavior is undefined. the two multiset must be
 *          initialized, otherwise the behavior is undefined. if the two multiset are not same type, the behavior is
 *          undefined. if cpmset_first == cpmset_second, then return true.
 */
extern bool_t multiset_less_equal(const multiset_t* cpmset_first, const multiset_t* cpmset_second);

/**
 * Tests if the first multiset is greater than the second multiset.
 * @param cpmset_first         first multiset container.
 * @param cpmset_second        second multiset container.
 * @return if first multiset is greater than the second multiset, then return true, else return false.
 * @remarks if cpmset_first == NULL or cpmset_second == NULL, then the behavior is undefined. the two multiset must be
 *          initialized, otherwise the behavior is undefined. if the two multiset are not same type, the behavior is
 *          undefined. if cpmset_first == cpmset_second, then return false.
 */
extern bool_t multiset_greater(const multiset_t* cpmset_first, const multiset_t* cpmset_second);

/**
 * Tests if the first multiset is greater than or equal to the second multiset.
 * @param cpmset_first         first multiset container.
 * @param cpmset_second        second multiset container.
 * @return if first multiset is greater than or equal to the second multiset, then return true, else return false.
 * @remarks if cpmset_first == NULL or cpmset_second == NULL, then the behavior is undefined. the two multiset must be
 *          initialized, otherwise the behavior is undefined. if the two multiset are not same type, the behavior is
 *          undefined. if cpmset_first == cpmset_second, then return true.
 */
extern bool_t multiset_greater_equal(const multiset_t* cpmset_first, const multiset_t* cpmset_second);

/**
 * Swap the datas of first multiset and second multiset.
 * @param pt_first          first multiset container.
 * @param pt_second         second multiset container.
 * @return void.
 * @remarks if pt_first == NULL or pt_second == NULL, then the behavior is undefined. the two multiset must be initialized,
 *          otherwise the behavior is undefined. if the two multiset are not same type, the behavior is undefined. if
 *          set_equal(cpt_first, cpt_second), then the function do nothing.
 */
extern void multiset_swap(multiset_t* pmset_first, multiset_t* pmset_second);

/**
 * Inserts an range of element into a multiset.
 * @param pmset_mset          multiset container.
 * @param it_begin          begin of specific range.
 * @param it_end            end of specific range.
 * @return void.
 * @remarks if pmset_mset == NULL then the behavior is undefined. pmset_mset must be initialized, otherwise the behavior
 *          is undefined. the type of [it_begin, it_end) and cpmset_mset must be same, otherwise the behavior is undefined.
 *          [it_begin, it_end) must be valid range, otherwise the behavior is undefine.
 */
extern void multiset_insert_range(multiset_t* pmset_mset, iterator_t it_begin, iterator_t it_end);

/**
 * Inserts an array of element into a multiset.
 * @param pmset_mset          multiset container.
 * @param cpv_array           array.
 * @param t_count             element count of array.
 * @return void.
 * @remarks if pmset_mset == NULL then the behavior is undefined. pmset_mset must be initialized, otherwise the behavior
 *          is undefined. the type of array and cpmset_mset must be same, otherwise the behavior is undefined.
 *          array must be valid range, otherwise the behavior is undefine.
 */
extern void multiset_insert_array(multiset_t* pmset_mset, const void* cpv_array, size_t t_count);

/*
 * Erase an element in an multiset from specificed position.
 * @param pmset_mset          multiset container.
 * @param it_pos            specificed position.
 * @return void.
 * @remarks if pmset_mset == NULL then the behavior is undefined. pmset_mset must be initialized, otherwise the behavior
 *          is undefined. it_pos must be valid iterator, otherwise the behavior is undefined.
 */
extern void multiset_erase_pos(multiset_t* pmset_mset, multiset_iterator_t it_pos);

/*
 * Erase a range of element in an multiset.
 * @param pmset_mset          multiset container.
 * @param it_begin          begin of specific range.
 * @param it_end            end of specific range.
 * @return void.
 * @remarks if pmset_mset == NULL then the behavior is undefined. pmset_mset must be initialized, otherwise the behavior
 *          is undefined. [it_begin, it_end) must be valid range for pmset_mset, otherwise the behavior is undefine.
 */
extern void multiset_erase_range(multiset_t* pmset_mset, multiset_iterator_t it_begin, multiset_iterator_t it_end);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_MULTISET_H_ */
/** eof **/

