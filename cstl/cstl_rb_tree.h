/*
 *  The interface of rb tree.
 *  Copyright (C)  2008 - 2014  Wangbo
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

#ifndef _CSTL_RB_TREE_H_
#define _CSTL_RB_TREE_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Create rb tree container.
 * @param s_typename        element type name.
 * @return if create rb tree successfully return rb tree pointer, otherwise return NULL.
 * @remarks s_typename == NULL, then the behavior is undefined. s_typename should be C builtin type name, libcstl builtin
 *          typename or registed user defined type name, otherwise the function will return NULL.
 */
extern _rb_tree_t* _create_rb_tree(const char* s_typename);

/**
 * Initialize rb tree container.
 * @param pt_rb_tree       rb tree container.
 * @param t_compare         compare function.
 * @return void.
 * @remarks if pt_rb_tree == NULL, then the behavior is undefined, pt_rb_tree must be created by _create_rb_tree(),
 *          otherwise the behavior is undefined. if t_compare == NULL, then the default compare function is used.
 */
extern void _rb_tree_init(_rb_tree_t* pt_rb_tree, bfun_t t_compare);

/**
 * Initialize rb tree container with rb tree.
 * @param pt_dest           destination rb tree.
 * @param cpt_src           source rb tree.
 * @return void.
 * @remarks if pt_dest == NULL or cpt_src == NULL, then the behavior is undefined, pt_dest must be created by
 *          _create_rb_tree(), cpt_src must be initialized, otherwise the behavior is undefined. the element type of
 *          pt_dest and cpt_src must be same, otherwise the behavior is undefine.
 */
extern void _rb_tree_init_copy(_rb_tree_t* pt_dest, const _rb_tree_t* cpt_src);

/**
 * Initialize rb tree container with specific range.
 * @param pt_dest           destination rb tree.
 * @param it_begin          begin of range.
 * @param it_end            end of range.
 * @return void.
 * @remarks if pt_dest == NULL, then the behavior is undefined, pt_dest must be created by _create_rb_tree(), otherwise
 *          the behavior is undefined. the type of [it_begin, it_end) and pt_dest must be same, otherwise the behavior
 *          is undefined.
 */
extern void _rb_tree_init_copy_equal_range(_rb_tree_t* pt_dest, iterator_t it_begin, iterator_t it_end);

/**
 * Initialize rb tree container with specific range.
 * @param pt_dest           destination rb tree.
 * @param it_begin          begin of range.
 * @param it_end            end of range.
 * @return void.
 * @remarks if pt_dest == NULL, then the behavior is undefined, pt_dest must be created by _create_rb_tree(), otherwise
 *          the behavior is undefined. the type of [it_begin, it_end) and pt_dest must be same, otherwise the behavior
 *          is undefined.
 */
extern void _rb_tree_init_copy_unique_range(_rb_tree_t* pt_dest, iterator_t it_begin, iterator_t it_end);

/**
 * Initialize rb tree container with specific range.
 * @param pt_dest           destination rb tree.
 * @param it_begin          begin of range.
 * @param it_end            end of range.
 * @return void.
 * @remarks if pt_dest == NULL, then the behavior is undefined, pt_dest must be created by _create_rb_tree(), otherwise
 *          the behavior is undefined. the type of [it_begin, it_end) and pt_dest must be same, otherwise the behavior
 *          is undefined.
 */
extern void _rb_tree_init_copy_unique_range(_rb_tree_t* pt_dest, iterator_t it_begin, iterator_t it_end);

/**
 * Initialize rb tree container with specific array.
 * @param pt_dest           destination rb tree.
 * @param cpv_array         array.
 * @param t_count           element count of array.
 * @return void.
 * @remarks if pt_dest == NULL, then the behavior is undefined, pt_dest must be created by _create_rb_tree(), otherwise
 *          the behavior is undefined. the type of array and pt_dest must be same, otherwise the behavior
 *          is undefined.
 */
extern void _rb_tree_init_copy_equal_array(_rb_tree_t* pt_dest, const void* cpv_array, size_t t_count);

/**
 * Initialize rb tree container with specific array.
 * @param pt_dest           destination rb tree.
 * @param cpv_array         array.
 * @param t_count           element count of array.
 * @return void.
 * @remarks if pt_dest == NULL, then the behavior is undefined, pt_dest must be created by _create_rb_tree(), otherwise
 *          the behavior is undefined. the type of array and pt_dest must be same, otherwise the behavior
 *          is undefined.
 */
extern void _rb_tree_init_copy_unique_array(_rb_tree_t* pt_dest, const void* cpv_array, size_t t_count);

/**
 * Initialize rb tree container with specific range and compare function.
 * @param pt_dest           destination rb tree.
 * @param it_begin          begin of range.
 * @param it_end            end of range.
 * @param t_compare         compare function.
 * @return void.
 * @remarks if pt_dest == NULL, then the behavior is undefined, pt_dest must be created by _create_rb_tree(), otherwise
 *          the behavior is undefined. the type of [it_begin, it_end) and pt_dest must be same, otherwise the behavior
 *          is undefined. if t_compare == NULL, then use default compare function.
 */
extern void _rb_tree_init_copy_equal_range_ex(
    _rb_tree_t* pt_dest, iterator_t it_begin, iterator_t it_end, bfun_t t_compare);

/**
 * Initialize rb tree container with specific range and compare function.
 * @param pt_dest           destination rb tree.
 * @param it_begin          begin of range.
 * @param it_end            end of range.
 * @param t_compare         compare function.
 * @return void.
 * @remarks if pt_dest == NULL, then the behavior is undefined, pt_dest must be created by _create_rb_tree(), otherwise
 *          the behavior is undefined. the type of [it_begin, it_end) and pt_dest must be same, otherwise the behavior
 *          is undefined. if t_compare == NULL, then use default compare function.
 */
extern void _rb_tree_init_copy_unique_range_ex(
    _rb_tree_t* pt_dest, iterator_t it_begin, iterator_t it_end, bfun_t t_compare);

/**
 * Initialize rb tree container with specific array and compare function.
 * @param pt_dest           destination rb tree.
 * @param cpv_array         array.
 * @param t_count           element count of array.
 * @param t_compare         compare function.
 * @return void.
 * @remarks if pt_dest == NULL, then the behavior is undefined, pt_dest must be created by _create_rb_tree(), otherwise
 *          the behavior is undefined. the type of array and pt_dest must be same, otherwise the behavior
 *          is undefined. if t_compare == NULL, then use default compare function.
 */
extern void _rb_tree_init_copy_equal_array_ex(
    _rb_tree_t* pt_dest, const void* cpv_array, size_t t_count, bfun_t t_compare);

/**
 * Initialize rb tree container with specific array and compare function.
 * @param pt_dest           destination rb tree.
 * @param cpv_array         array.
 * @param t_count           element count of array.
 * @param t_compare         compare function.
 * @return void.
 * @remarks if pt_dest == NULL, then the behavior is undefined, pt_dest must be created by _create_rb_tree(), otherwise
 *          the behavior is undefined. the type of array and pt_dest must be same, otherwise the behavior
 *          is undefined. if t_compare == NULL, then use default compare function.
 */
extern void _rb_tree_init_copy_unique_array_ex(
    _rb_tree_t* pt_dest, const void* cpv_array, size_t t_count, bfun_t t_compare);

/**
 * Destroy rb tree.
 * @param pt_rb_tree       rb tree container.
 * @return void.
 * @remarks if pt_rb_tree == NULL, then the behavior is undefined, the rb tree must be initialized or created by
 *          _create_rb_tree(), otherwise the behavior is undefined.
 */
extern void _rb_tree_destroy(_rb_tree_t* pt_rb_tree);

/**
 * Assign rb tree container.
 * @param pt_dest           destination rb tree container.
 * @param cpt_src           source rb tree container.
 * @return void.
 * @remarks if pt_dest == NULL or cpt_src == NULL, the the behavior is undefined. two rb tree must be initialized, otherwise
 *          the behavior is undefined. if _rb_tree_equal(pt_dest, cpt_src), the function dest nothing.
 */
extern void _rb_tree_assign(_rb_tree_t* pt_dest, const _rb_tree_t* cpt_src);

/**
 * Get the number of elements int the rb tree.
 * @param cpt_rb_tree      rb tree container.
 * @return the number of elements in the rb tree.
 * @remarks if cpt_rb_tree == NULL, then the behavior is undefined, the cpt_rb_tree must be initialized, otherwise the
 *          behavior is undefined.
 */
extern size_t _rb_tree_size(const _rb_tree_t* cpt_rb_tree);

/**
 * Test if an rb tree is empty.
 * @param cpt_rb_tree      rb tree container.
 * @return true if the rb tree is empty, otherwise return false.
 * @remarks if cpt_rb_tree == NULL, then the behavior is undefined, the cpt_rb_tree must be initialized, otherwise the
 *          behavior is undefined.
 */
extern bool_t _rb_tree_empty(const _rb_tree_t* cpt_rb_tree);

/**
 * Get the maximum number of elements int the rb tree.
 * @param cpt_rb_tree      rb tree container.
 * @return the maximum number of elements in the rb tree.
 * @remarks if cpt_rb_tree == NULL, then the behavior is undefined, the cpt_rb_tree must be initialized, otherwise the
 *          behavior is undefined.
 */
extern size_t _rb_tree_max_size(const _rb_tree_t* cpt_rb_tree);

/**
 * Return an iterator that addresses the first element in the rb tree.
 * @param cpt_rb_tree      rb tree container.
 * @return an iterator that addresses the first element in the rb tree.
 * @remarks if cpt_rb_tree == NULL, the behavior is undefined. cpt_rb_tree must be initialized, otherwise the behavior
 *          is undefined. return _rb_tree_end(), if the rb tree is empty.
 */
extern _rb_tree_iterator_t _rb_tree_begin(const _rb_tree_t* cpt_rb_tree);

/**
 * Return an iterator that addresses the location succeeding the last element in the rb tree.
 * @param cpt_rb_tree      rb tree container.
 * @return an iterator that addresses location succeeding the last element in the rb tree.
 * @remarks if cpt_rb_tree == NULL, the behavior is undefined. cpt_rb_tree must be initialized, otherwise the behavior
 *          is undefined.
 */
extern _rb_tree_iterator_t _rb_tree_end(const _rb_tree_t* cpt_rb_tree);
extern _rb_tree_reverse_iterator_t _rb_tree_rbegin(const _rb_tree_t* cpt_rb_tree);
extern _rb_tree_reverse_iterator_t _rb_tree_rend(const _rb_tree_t* cpt_rb_tree);

/**
 * Return the compare function of key.
 * @param cpt_rb_tree      rb tree container.
 * @return compare function.
 * @remarks if cpt_rb_tree == NULL, the behavior is undefined. cpt_rb_tree must be initialized, otherwise the behavior
 *          is undefined.
 */
extern bfun_t _rb_tree_key_comp(const _rb_tree_t* cpt_rb_tree);

/**
 * Find specific element.
 * @param cpt_rb_tree      rb tree container.
 * @param cpv_value         specific element.
 * @return iterator addresses the sprcific element in the rb tree, otherwise return _rb_tree_end().
 * @remarks if cpt_rb_tree == NULL or cpv_value == NULL then the behavior is undefined. cpt_rb_tree must be initialized,
 *          otherwise the behavior is undefined. the type of specific element and cpt_rb_tree must be same, otherwise the
 *          behavior is undefined.
 */
extern _rb_tree_iterator_t _rb_tree_find(const _rb_tree_t* cpt_rb_tree, const void* cpv_value);

/**
 * Erases all the elements of an rb tree.
 * @param pt_rb_tree       rb tree container.
 * @return void.
 * @remarks if pt_rb_tree == NULL, the behavior is undefined. pt_rb_tree must be initialized, otherwise the behavior
 *          is undefined.
 */
extern void _rb_tree_clear(_rb_tree_t* pt_rb_tree);

/**
 * Return the number of specific elements in an rb tree
 * @param cpt_rb_tree       rb tree container.
 * @param cpv_value         specific element.
 * @return the number of specific elements.
 * @remarks if cpt_rb_tree == NULL or cpv_value == NULL then the behavior is undefined. cpt_rb_tree must be initialized,
 *          otherwise the behavior is undefined. the type of specific element and cpt_rb_tree must be same, otherwise the
 *          behavior is undefined.
 */
extern size_t _rb_tree_count(const _rb_tree_t* cpt_rb_tree, const void* cpv_value);

/**
 * Return an iterator to the first element that is equal to or greater than a specific element.
 * @param cpt_rb_tree      rb tree container.
 * @param cpv_value         specific element.
 * @return an iterator to the first element that is equal to or greater than a specific element.
 * @remarks if cpt_rb_tree == NULL or cpv_value == NULL then the behavior is undefined. cpt_rb_tree must be initialized,
 *          otherwise the behavior is undefined. the type of specific element and cpt_rb_tree must be same, otherwise the
 *          behavior is undefined.
 */
extern _rb_tree_iterator_t _rb_tree_lower_bound(const _rb_tree_t* cpt_rb_tree, const void* cpv_value);

/**
 * Return an iterator to the first element that is greater than a specific element.
 * @param cpt_rb_tree      rb tree container.
 * @param cpv_value         specific element.
 * @return an iterator to the first element that is greater than a specific element.
 * @remarks if cpt_rb_tree == NULL or cpv_value == NULL then the behavior is undefined. cpt_rb_tree must be initialized,
 *          otherwise the behavior is undefined. the type of specific element and cpt_rb_tree must be same, otherwise the
 *          behavior is undefined.
 */
extern _rb_tree_iterator_t _rb_tree_upper_bound(const _rb_tree_t* cpt_rb_tree, const void* cpv_value);

/**
 * Return an iterator range that is equal to a specific element.
 * @param cpt_rb_tree      rb tree container.
 * @param cpv_value         specific element.
 * @return an iterator range that is equal to a specific element.
 * @remarks if cpt_rb_tree == NULL or cpv_value == NULL then the behavior is undefined. cpt_rb_tree must be initialized,
 *          otherwise the behavior is undefined. the type of specific element and cpt_rb_tree must be same, otherwise the
 *          behavior is undefined.
 */
extern range_t _rb_tree_equal_range(const _rb_tree_t* cpt_rb_tree, const void* cpv_value);

/**
 * Tests if the two rb tree are equal.
 * @param cpt_first         first rb tree container.
 * @param cpt_second        second rb tree container.
 * @return if first rb tree equal to second rb tree, then return true, else return false.
 * @remarks if cpt_first == NULL or cpt_second == NULL, then the behavior is undefined. the two rb tree must be
 *          initialized, otherwise the behavior is undefined. if the two rb tree are not same type, the behavior is undefined.
 *          if cpt_first == cpt_second, then return true.
 */
extern bool_t _rb_tree_equal(const _rb_tree_t* pt_first, const _rb_tree_t* cpt_second);

/**
 * Tests if the two rb tree are not equal.
 * @param cpt_first         first rb tree container.
 * @param cpt_second        second rb tree container.
 * @return if first rb tree not equal to second rb tree, then return true, else return false.
 * @remarks if cpt_first == NULL or cpt_second == NULL, then the behavior is undefined. the two rb tree must be
 *          initialized, otherwise the behavior is undefined. if the two rb tree are not same type, the behavior is undefined.
 *          if cpt_first == cpt_second, then return false.
 */
extern bool_t _rb_tree_not_equal(const _rb_tree_t* pt_first, const _rb_tree_t* cpt_second);

/**
 * Tests if the first rb tree is less than the second rb tree.
 * @param cpt_first         first rb tree container.
 * @param cpt_second        second rb tree container.
 * @return if first rb tree is less than the second rb tree, then return true, else return false.
 * @remarks if cpt_first == NULL or cpt_second == NULL, then the behavior is undefined. the two rb tree must be
 *          initialized, otherwise the behavior is undefined. if the two rb tree are not same type, the behavior is
 *          undefined. if cpt_first == cpt_second, then return false.
 */
extern bool_t _rb_tree_less(const _rb_tree_t* pt_first, const _rb_tree_t* cpt_second);

/**
 * Tests if the first rb tree is less than or equal to the second rb tree.
 * @param cpt_first         first rb tree container.
 * @param cpt_second        second rb tree container.
 * @return if first rb tree is less than or equal to the second rb tree, then return true, else return false.
 * @remarks if cpt_first == NULL or cpt_second == NULL, then the behavior is undefined. the two rb tree must be
 *          initialized, otherwise the behavior is undefined. if the two rb tree are not same type, the behavior is
 *          undefined. if cpt_first == cpt_second, then return true.
 */
extern bool_t _rb_tree_less_equal(const _rb_tree_t* pt_first, const _rb_tree_t* cpt_second);

/**
 * Tests if the first rb tree is greater than the second rb tree.
 * @param cpt_first         first rb tree container.
 * @param cpt_second        second rb tree container.
 * @return if first rb tree is greater than the second rb tree, then return true, else return false.
 * @remarks if cpt_first == NULL or cpt_second == NULL, then the behavior is undefined. the two rb tree must be
 *          initialized, otherwise the behavior is undefined. if the two rb tree are not same type, the behavior is
 *          undefined. if cpt_first == cpt_second, then return false.
 */
extern bool_t _rb_tree_greater(const _rb_tree_t* pt_first, const _rb_tree_t* cpt_second);

/**
 * Tests if the first rb tree is greater than or equal to the second rb tree.
 * @param cpt_first         first rb tree container.
 * @param cpt_second        second rb tree container.
 * @return if first rb tree is greater than or equal to the second rb tree, then return true, else return false.
 * @remarks if cpt_first == NULL or cpt_second == NULL, then the behavior is undefined. the two rb tree must be
 *          initialized, otherwise the behavior is undefined. if the two rb tree are not same type, the behavior is
 *          undefined. if cpt_first == cpt_second, then return true.
 */
extern bool_t _rb_tree_greater_equal(const _rb_tree_t* pt_first, const _rb_tree_t* cpt_second);

/**
 * Swap the datas of first rb_tree and second rb_tree.
 * @param pt_first          first rb tree container.
 * @param pt_second         second rb tree container.
 * @return void.
 * @remarks if pt_first == NULL or pt_second == NULL, then the behavior is undefined. the two rb tree must be
 *          initialized, otherwise the behavior is undefined. if the two rb tree are not same type, the behavior is
 *          undefined. if _rb_tree_equal(cpt_first, cpt_second), then the function do nothing.
 */
extern void _rb_tree_swap(_rb_tree_t* pt_first, _rb_tree_t* pt_second);

/**
 * Inserts an unique element into a rb tree.
 * @param pt_rb_tree       rb tree container.
 * @param cpv_value         specific element.
 * @return an iterator addresses the inserted element, or rb tree end if insert failed.
 * @remarks if pt_rb_tree == NULL or cpv_value == NULL then the behavior is undefined. cpt_rb_tree must be initialized,
 *          otherwise the behavior is undefined. the type of specific element and cpt_rb_tree must be same, otherwise the
 *          behavior is undefined.
 */
extern _rb_tree_iterator_t _rb_tree_insert_unique(_rb_tree_t* pt_rb_tree, const void* cpv_value);

/**
 * Inserts an element into a rb tree.
 * @param pt_rb_tree       rb tree container.
 * @param cpv_value         specific element.
 * @return an iterator addresses the inserted element, or rb tree end if insert failed.
 * @remarks if pt_rb_tree == NULL or cpv_value == NULL then the behavior is undefined. cpt_rb_tree must be initialized,
 *          otherwise the behavior is undefined. the type of specific element and cpt_rb_tree must be same, otherwise the
 *          behavior is undefined.
 */
extern _rb_tree_iterator_t _rb_tree_insert_equal(_rb_tree_t* pt_rb_tree, const void* cpv_value);

/**
 * Inserts an range of unique element into a rb tree.
 * @param pt_rb_tree       rb tree container.
 * @param it_begin         begin of specific range.
 * @param it_end           end of specific range.
 * @return void.
 * @remarks if pt_rb_tree == NULL then the behavior is undefined. pt_rb_tree must be initialized, otherwise the behavior
 *          is undefined. the type of [it_begin, it_end) and cpt_rb_tree must be same, otherwise the behavior is undefined.
 *          [it_begin, it_end) must be valid range, otherwise the behavior is undefine.
 */
extern void _rb_tree_insert_unique_range(_rb_tree_t* pt_rb_tree, iterator_t it_begin, iterator_t it_end);

/**
 * Inserts an array of unique element into a rb tree.
 * @param pt_rb_tree       rb tree container.
 * @param cpv_array        array.
 * @param t_count          element count of array.
 * @return void.
 * @remarks if pt_rb_tree == NULL then the behavior is undefined. pt_rb_tree must be initialized, otherwise the behavior
 *          is undefined. the type of array and cpt_rb_tree must be same, otherwise the behavior is undefined.
 *          array must be valid range, otherwise the behavior is undefine.
 */
extern void _rb_tree_insert_unique_array(_rb_tree_t* pt_rb_tree, const void* cpv_array, size_t t_count);

/**
 * Inserts an range into a rb tree.
 * @param pt_rb_tree       rb tree container.
 * @param it_begin         begin of specific range.
 * @param it_end           end of specific range.
 * @return void.
 * @remarks if pt_rb_tree == NULL then the behavior is undefined. pt_rb_tree must be initialized, otherwise the behavior
 *          is undefined. the type of [it_begin, it_end) and cpt_rb_tree must be same, otherwise the behavior is undefined.
 *          [it_begin, it_end) must be valid range, otherwise the behavior is undefine.
 */
extern void _rb_tree_insert_equal_range(_rb_tree_t* pt_rb_tree, iterator_t it_begin, iterator_t it_end);

/**
 * Inserts an array into a rb tree.
 * @param pt_rb_tree       rb tree container.
 * @param cpv_array        array.
 * @param t_count          element count of array.
 * @return void.
 * @remarks if pt_rb_tree == NULL then the behavior is undefined. pt_rb_tree must be initialized, otherwise the behavior
 *          is undefined. the type of array and cpt_rb_tree must be same, otherwise the behavior is undefined.
 *          array must be valid range, otherwise the behavior is undefine.
 */
extern void _rb_tree_insert_equal_array(_rb_tree_t* pt_rb_tree, const void* cpv_array, size_t t_count);

/*
 * Erase an element in an rb tree from specificed position.
 * @param pt_rb_tree       rb tree container.
 * @param it_pos           specificed position.
 * @return void.
 * @remarks if pt_rb_tree == NULL then the behavior is undefined. pt_rb_tree must be initialized, otherwise the behavior
 *          is undefined. it_pos must be valid iterator, otherwise the behavior is undefined.
 */
extern void _rb_tree_erase_pos(_rb_tree_t* pt_rb_tree, _rb_tree_iterator_t it_pos);

/*
 * Erase a range of element in an rb tree.
 * @param pt_rb_tree       rb tree container.
 * @param it_begin          begin of specific range.
 * @param it_end            end of specific range.
 * @return void.
 * @remarks if pt_rb_tree == NULL then the behavior is undefined. pt_rb_tree must be initialized, otherwise the behavior
 *          is undefined. [it_begin, it_end) must be valid range for pt_rb_tree, otherwise the behavior is undefine.
 */
extern void _rb_tree_erase_range(_rb_tree_t* pt_rb_tree, _rb_tree_iterator_t it_begin, _rb_tree_iterator_t it_end);

/**
 * Erase an element from a rb tree that match a specified element.
 * @param pt_rb_tree       rb tree container.
 * @param cpv_value         specific element.
 * @return the number of erased elements.
 * @remarks if pt_rb_tree == NULL or cpv_value == NULL then the behavior is undefined. cpt_rb_tree must be initialized,
 *          otherwise the behavior is undefined. 
 */
extern size_t _rb_tree_erase(_rb_tree_t* pt_rb_tree, const void* cpv_value);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_RB_TREE_H_ */
/** eof **/

