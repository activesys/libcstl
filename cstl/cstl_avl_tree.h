/*
 *  The interface of avl tree.
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

#ifndef _CSTL_AVL_TREE_H_
#define _CSTL_AVL_TREE_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Create avl tree container.
 * @param s_typename        element type name.
 * @return if create avl tree successfully return avl tree pointer, otherwise return NULL.
 * @remarks s_typename == NULL, then the behavior is undefined. s_typename should be C builtin type name, libcstl builtin
 *          typename or registed user defined type name, otherwise the function will return NULL.
 */
extern _avl_tree_t* _create_avl_tree(const char* s_typename);

/**
 * Initialize avl tree container.
 * @param pt_avl_tree       avl tree container.
 * @param t_compare         compare function.
 * @return void.
 * @remarks if pt_avl_tree == NULL, then the behavior is undefined, pt_avl_tree must be created by _create_avl_tree(),
 *          otherwise the behavior is undefined. if t_compare == NULL, then the default compare function is used.
 */
extern void _avl_tree_init(_avl_tree_t* pt_avl_tree, bfun_t t_compare);

/**
 * Initialize avl tree container with avl tree.
 * @param pt_dest           destination avl tree.
 * @param cpt_src           source avl tree.
 * @return void.
 * @remarks if pt_dest == NULL or cpt_src == NULL, then the behavior is undefined, pt_dest must be created by
 *          _create_avl_tree(), cpt_src must be initialized, otherwise the behavior is undefined. the element type of
 *          pt_dest and cpt_src must be same, otherwise the behavior is undefine.
 */
extern void _avl_tree_init_copy(_avl_tree_t* pt_dest, const _avl_tree_t* cpt_src);

/**
 * Initialize avl tree container with specific range.
 * @param pt_dest           destination avl tree.
 * @param it_begin          begin of range.
 * @param it_end            end of range.
 * @return void.
 * @remarks if pt_dest == NULL, then the behavior is undefined, pt_dest must be created by _create_avl_tree(), otherwise
 *          the behavior is undefined. the type of [it_begin, it_end) and pt_dest must be same, otherwise the behavior is
 *          undefined.
 */
extern void _avl_tree_init_copy_equal_range(_avl_tree_t* pt_dest, iterator_t it_begin, iterator_t it_end);

/**
 * Initialize avl tree container with specific array.
 * @param pt_dest           destination avl tree.
 * @param cpv_array         array.
 * @param t_count           element count of array.
 * @return void.
 * @remarks if pt_dest == NULL, then the behavior is undefined, pt_dest must be created by _create_avl_tree(), otherwise
 *          the behavior is undefined. the type of array and pt_dest must be same, otherwise the behavior is undefined.
 */
extern void _avl_tree_init_copy_equal_array(_avl_tree_t* pt_dest, const void* cpv_array, size_t t_count);

/**
 * Initialize avl tree container with specific range.
 * @param pt_dest           destination avl tree.
 * @param it_begin          begin of range.
 * @param it_end            end of range.
 * @return void.
 * @remarks if pt_dest == NULL, then the behavior is undefined, pt_dest must be created by _create_avl_tree(), otherwise
 *          the behavior is undefined. the type of [it_begin, it_end) and pt_dest must be same, otherwise the behavior is
 *          undefined.
 */
extern void _avl_tree_init_copy_unique_range(_avl_tree_t* pt_dest, iterator_t it_begin, iterator_t it_end);

/**
 * Initialize avl tree container with specific array.
 * @param pt_dest           destination avl tree.
 * @param cpv_array         array.
 * @param t_count           element count of array.
 * @return void.
 * @remarks if pt_dest == NULL, then the behavior is undefined, pt_dest must be created by _create_avl_tree(), otherwise
 *          the behavior is undefined. the type of array and pt_dest must be same, otherwise the behavior is undefined.
 */
extern void _avl_tree_init_copy_unique_array(_avl_tree_t* pt_dest, const void* cpv_array, size_t t_count);

/**
 * Initialize avl tree container with specific range and compare function.
 * @param pt_dest           destination avl tree.
 * @param it_begin          begin of range.
 * @param it_end            end of range.
 * @param t_compare         compare function.
 * @return void.
 * @remarks if pt_dest == NULL, then the behavior is undefined, pt_dest must be created by _create_avl_tree(), otherwise
 *          the behavior is undefined. the type of [it_begin, it_end) and pt_dest must be same, otherwise the behavior is
 *          undefined. if t_compare == NULL, then use default compare function.
 */
extern void _avl_tree_init_copy_equal_range_ex(_avl_tree_t* pt_dest, iterator_t it_begin, iterator_t it_end, bfun_t t_compare);

/**
 * Initialize avl tree container with specific array and compare function.
 * @param pt_dest           destination avl tree.
 * @param cpv_array         array.
 * @param t_count           element count of array.
 * @param t_compare         compare function.
 * @return void.
 * @remarks if pt_dest == NULL, then the behavior is undefined, pt_dest must be created by _create_avl_tree(), otherwise
 *          the behavior is undefined. the type of array and pt_dest must be same, otherwise the behavior is undefined. 
 *          if t_compare == NULL, then use default compare function.
 */
extern void _avl_tree_init_copy_equal_array_ex(_avl_tree_t* pt_dest, const void* cpv_array, size_t t_count, bfun_t t_compare);

/**
 * Initialize avl tree container with specific range and compare function.
 * @param pt_dest           destination avl tree.
 * @param it_begin          begin of range.
 * @param it_end            end of range.
 * @param t_compare         compare function.
 * @return void.
 * @remarks if pt_dest == NULL, then the behavior is undefined, pt_dest must be created by _create_avl_tree(), otherwise
 *          the behavior is undefined. the type of [it_begin, it_end) and pt_dest must be same, otherwise the behavior is
 *          undefined. if t_compare == NULL, then use default compare function.
 */
extern void _avl_tree_init_copy_unique_range_ex(_avl_tree_t* pt_dest, iterator_t it_begin, iterator_t it_end, bfun_t t_compare);

/**
 * Initialize avl tree container with specific array and compare function.
 * @param pt_dest           destination avl tree.
 * @param cpv_array         array.
 * @param t_count           element count of array.
 * @param t_compare         compare function.
 * @return void.
 * @remarks if pt_dest == NULL, then the behavior is undefined, pt_dest must be created by _create_avl_tree(), otherwise
 *          the behavior is undefined. the type of array and pt_dest must be same, otherwise the behavior is undefined. 
 *          if t_compare == NULL, then use default compare function.
 */
extern void _avl_tree_init_copy_unique_array_ex(_avl_tree_t* pt_dest, const void* cpv_array, size_t t_count, bfun_t t_compare);

/**
 * Destroy avl tree.
 * @param pt_avl_tree       avl tree container.
 * @return void.
 * @remarks if pt_avl_tree == NULL, then the behavior is undefined, the avl tree must be initialized or created by
 *          _create_avl_tree(), otherwise the behavior is undefined.
 */
extern void _avl_tree_destroy(_avl_tree_t* pt_avl_tree);

/**
 * Assign avl tree container.
 * @param pt_dest           destination avl tree container.
 * @param cpt_src           source avl tree container.
 * @return void.
 * @remarks if pt_dest == NULL or cpt_src == NULL, the the behavior is undefined. two avl tree must be initialized, otherwise
 *          the behavior is undefined. if _avl_tree_equal(pt_dest, cpt_src), the function dest nothing.
 */
extern void _avl_tree_assign(_avl_tree_t* pt_dest, const _avl_tree_t* cpt_src);

/**
 * Get the number of elements int the avl tree.
 * @param cpt_avl_tree      avl tree container.
 * @return the number of elements in the avl tree.
 * @remarks if cpt_avl_tree == NULL, then the behavior is undefined, the cpt_avl_tree must be initialized, otherwise the
 *          behavior is undefined.
 */
extern size_t _avl_tree_size(const _avl_tree_t* cpt_avl_tree);

/**
 * Test if an avl tree is empty.
 * @param cpt_avl_tree      avl tree container.
 * @return true if the avl tree is empty, otherwise return false.
 * @remarks if cpt_avl_tree == NULL, then the behavior is undefined, the cpt_avl_tree must be initialized, otherwise the
 *          behavior is undefined.
 */
extern bool_t _avl_tree_empty(const _avl_tree_t* cpt_avl_tree);

/**
 * Get the maximum number of elements int the avl tree.
 * @param cpt_avl_tree      avl tree container.
 * @return the maximum number of elements in the avl tree.
 * @remarks if cpt_avl_tree == NULL, then the behavior is undefined, the cpt_avl_tree must be initialized, otherwise the
 *          behavior is undefined.
 */
extern size_t _avl_tree_max_size(const _avl_tree_t* cpt_avl_tree);

/**
 * Return an iterator that addresses the first element in the avl tree.
 * @param cpt_avl_tree      avl tree container.
 * @return an iterator that addresses the first element in the avl tree.
 * @remarks if cpt_avl_tree == NULL, the behavior is undefined. cpt_avl_tree must be initialized, otherwise the behavior
 *          is undefined. return _avl_tree_end(), if the avl tree is empty.
 */
extern _avl_tree_iterator_t _avl_tree_begin(const _avl_tree_t* cpt_avl_tree);

/**
 * Return an iterator that addresses the location succeeding the last element in the avl tree.
 * @param cpt_avl_tree      avl tree container.
 * @return an iterator that addresses location succeeding the last element in the avl tree.
 * @remarks if cpt_avl_tree == NULL, the behavior is undefined. cpt_avl_tree must be initialized, otherwise the behavior
 *          is undefined.
 */
extern _avl_tree_iterator_t _avl_tree_end(const _avl_tree_t* cpt_avl_tree);
/* private */
extern _avl_tree_reverse_iterator_t _avl_tree_rbegin(const _avl_tree_t* cpt_avl_tree);
extern _avl_tree_reverse_iterator_t _avl_tree_rend(const _avl_tree_t* cpt_avl_tree);

/**
 * Return the compare function of key.
 * @param cpt_avl_tree      avl tree container.
 * @return compare function.
 * @remarks if cpt_avl_tree == NULL, the behavior is undefined. cpt_avl_tree must be initialized, otherwise the behavior
 *          is undefined.
 */
extern bfun_t _avl_tree_key_comp(const _avl_tree_t* cpt_avl_tree);

/**
 * Find specific element.
 * @param cpt_avl_tree      avl tree container.
 * @param cpv_value         specific element.
 * @return iterator addresses the sprcific element in the avl tree, otherwise return _avl_tree_end().
 * @remarks if cpt_avl_tree == NULL or cpv_value == NULL then the behavior is undefined. cpt_avl_tree must be initialized,
 *          otherwise the behavior is undefined. the type of specific element and cpt_avl_tree must be same, otherwise the
 *          behavior is undefined.
 */
extern _avl_tree_iterator_t _avl_tree_find(const _avl_tree_t* cpt_avl_tree, const void* cpv_value);

/**
 * Erases all the elements of an avl tree.
 * @param pt_avl_tree       avl tree container.
 * @return void.
 * @remarks if pt_avl_tree == NULL, the behavior is undefined. pt_avl_tree must be initialized, otherwise the behavior
 *          is undefined.
 */
extern void _avl_tree_clear(_avl_tree_t* pt_avl_tree);

/**
 * Return the number of specific elements in an avl tree
 * @param cpt_avl_tree      avl tree container.
 * @param cpv_value         specific element.
 * @return the number of specific elements.
 * @remarks if cpt_avl_tree == NULL or cpv_value == NULL then the behavior is undefined. cpt_avl_tree must be initialized,
 *          otherwise the behavior is undefined. the type of specific element and cpt_avl_tree must be same, otherwise the
 *          behavior is undefined.
 */
extern size_t _avl_tree_count(const _avl_tree_t* cpt_avl_tree, const void* cpv_value);

/**
 * Return an iterator to the first element that is equal to or greater than a specific element.
 * @param cpt_avl_tree      avl tree container.
 * @param cpv_value         specific element.
 * @return an iterator to the first element that is equal to or greater than a specific element.
 * @remarks if cpt_avl_tree == NULL or cpv_value == NULL then the behavior is undefined. cpt_avl_tree must be initialized,
 *          otherwise the behavior is undefined. the type of specific element and cpt_avl_tree must be same, otherwise the
 *          behavior is undefined.
 */
extern _avl_tree_iterator_t _avl_tree_lower_bound(const _avl_tree_t* cpt_avl_tree, const void* cpv_value);

/**
 * Return an iterator to the first element that is greater than a specific element.
 * @param cpt_avl_tree      avl tree container.
 * @param cpv_value         specific element.
 * @return an iterator to the first element that is greater than a specific element.
 * @remarks if cpt_avl_tree == NULL or cpv_value == NULL then the behavior is undefined. cpt_avl_tree must be initialized,
 *          otherwise the behavior is undefined. the type of specific element and cpt_avl_tree must be same, otherwise the
 *          behavior is undefined.
 */
extern _avl_tree_iterator_t _avl_tree_upper_bound(const _avl_tree_t* cpt_avl_tree, const void* cpv_value);

/**
 * Return an iterator range that is equal to a specific element.
 * @param cpt_avl_tree      avl tree container.
 * @param cpv_value         specific element.
 * @return an iterator range that is equal to a specific element.
 * @remarks if cpt_avl_tree == NULL or cpv_value == NULL then the behavior is undefined. cpt_avl_tree must be initialized,
 *          otherwise the behavior is undefined. the type of specific element and cpt_avl_tree must be same, otherwise the
 *          behavior is undefined.
 */
extern range_t _avl_tree_equal_range(const _avl_tree_t* cpt_avl_tree, const void* cpv_value);

/**
 * Tests if the two avl tree are equal.
 * @param cpt_first         first avl tree container.
 * @param cpt_second        second avl tree container.
 * @return if first avl tree equal to second avl tree, then return true, else return false.
 * @remarks if cpt_first == NULL or cpt_second == NULL, then the behavior is undefined. the two avl tree must be
 *          initialized, otherwise the behavior is undefined. if the two avl tree are not same type, the behavior is undefined.
 *          if cpt_first == cpt_second, then return true.
 */
extern bool_t _avl_tree_equal(const _avl_tree_t* cpt_first, const _avl_tree_t* cpt_second);

/**
 * Tests if the two avl tree are not equal.
 * @param cpt_first         first avl tree container.
 * @param cpt_second        second avl tree container.
 * @return if first avl tree not equal to second avl tree, then return true, else return false.
 * @remarks if cpt_first == NULL or cpt_second == NULL, then the behavior is undefined. the two avl tree must be
 *          initialized, otherwise the behavior is undefined. if the two avl tree are not same type, the behavior is undefined.
 *          if cpt_first == cpt_second, then return false.
 */
extern bool_t _avl_tree_not_equal(const _avl_tree_t* cpt_first, const _avl_tree_t* cpt_second);

/**
 * Tests if the first avl tree is less than the second avl tree.
 * @param cpt_first         first avl tree container.
 * @param cpt_second        second avl tree container.
 * @return if first avl tree is less than the second avl tree, then return true, else return false.
 * @remarks if cpt_first == NULL or cpt_second == NULL, then the behavior is undefined. the two avl tree must be
 *          initialized, otherwise the behavior is undefined. if the two avl tree are not same type, the behavior is
 *          undefined. if cpt_first == cpt_second, then return false.
 */
extern bool_t _avl_tree_less(const _avl_tree_t* cpt_first, const _avl_tree_t* cpt_second);

/**
 * Tests if the first avl tree is less than or equal to the second avl tree.
 * @param cpt_first         first avl tree container.
 * @param cpt_second        second avl tree container.
 * @return if first avl tree is less than or equal to the second avl tree, then return true, else return false.
 * @remarks if cpt_first == NULL or cpt_second == NULL, then the behavior is undefined. the two avl tree must be
 *          initialized, otherwise the behavior is undefined. if the two avl tree are not same type, the behavior is
 *          undefined. if cpt_first == cpt_second, then return true.
 */
extern bool_t _avl_tree_less_equal(const _avl_tree_t* cpt_first, const _avl_tree_t* cpt_second);

/**
 * Tests if the first avl tree is greater than the second avl tree.
 * @param cpt_first         first avl tree container.
 * @param cpt_second        second avl tree container.
 * @return if first avl tree is greater than the second avl tree, then return true, else return false.
 * @remarks if cpt_first == NULL or cpt_second == NULL, then the behavior is undefined. the two avl tree must be
 *          initialized, otherwise the behavior is undefined. if the two avl tree are not same type, the behavior is
 *          undefined. if cpt_first == cpt_second, then return false.
 */
extern bool_t _avl_tree_greater(const _avl_tree_t* cpt_first, const _avl_tree_t* cpt_second);

/**
 * Tests if the first avl tree is greater than or equal to the second avl tree.
 * @param cpt_first         first avl tree container.
 * @param cpt_second        second avl tree container.
 * @return if first avl tree is greater than or equal to the second avl tree, then return true, else return false.
 * @remarks if cpt_first == NULL or cpt_second == NULL, then the behavior is undefined. the two avl tree must be
 *          initialized, otherwise the behavior is undefined. if the two avl tree are not same type, the behavior is
 *          undefined. if cpt_first == cpt_second, then return true.
 */
extern bool_t _avl_tree_greater_equal(const _avl_tree_t* cpt_first, const _avl_tree_t* cpt_second);

/**
 * Swap the datas of first avl_tree and second avl_tree.
 * @param pt_first          first avl tree container.
 * @param pt_second         second avl tree container.
 * @return void.
 * @remarks if pt_first == NULL or pt_second == NULL, then the behavior is undefined. the two avl tree must be
 *          initialized, otherwise the behavior is undefined. if the two avl tree are not same type, the behavior is
 *          undefined. if _avl_tree_equal(cpt_first, cpt_second), then the function do nothing.
 */
extern void _avl_tree_swap(_avl_tree_t* pt_first, _avl_tree_t* pt_second);

/**
 * Inserts an unique element into a avl tree.
 * @param pt_avl_tree       avl tree container.
 * @param cpv_value         specific element.
 * @return an iterator addresses the inserted element, or avl tree end if insert failed.
 * @remarks if pt_avl_tree == NULL or cpv_value == NULL then the behavior is undefined. cpt_avl_tree must be initialized,
 *          otherwise the behavior is undefined. the type of specific element and cpt_avl_tree must be same, otherwise the
 *          behavior is undefined.
 */
extern _avl_tree_iterator_t _avl_tree_insert_unique(_avl_tree_t* pt_avl_tree, const void* cpv_value);

/**
 * Inserts an element into a avl tree.
 * @param pt_avl_tree       avl tree container.
 * @param cpv_value         specific element.
 * @return an iterator addresses the inserted element, or avl tree end if insert failed.
 * @remarks if pt_avl_tree == NULL or cpv_value == NULL then the behavior is undefined. cpt_avl_tree must be initialized,
 *          otherwise the behavior is undefined. the type of specific element and cpt_avl_tree must be same, otherwise the
 *          behavior is undefined.
 */
extern _avl_tree_iterator_t _avl_tree_insert_equal(_avl_tree_t* pt_avl_tree, const void* cpv_value);

/**
 * Inserts an range of unique element into a avl tree.
 * @param pt_avl_tree       avl tree container.
 * @param it_begin          begin of specific range.
 * @param it_end            end of specific range.
 * @return void.
 * @remarks if pt_avl_tree == NULL then the behavior is undefined. pt_avl_tree must be initialized, otherwise the behavior
 *          is undefined. the type of [it_begin, it_end) and cpt_avl_tree must be same, otherwise the behavior is undefined.
 *          [it_begin, it_end) must be valid range, otherwise the behavior is undefine.
 */
extern void _avl_tree_insert_unique_range(_avl_tree_t* pt_avl_tree, iterator_t it_begin, iterator_t it_end);

/**
 * Inserts an array of unique element into a avl tree.
 * @param pt_avl_tree       avl tree container.
 * @param cpv_array         array.
 * @param t_count           element count of array.
 * @return void.
 * @remarks if pt_avl_tree == NULL then the behavior is undefined. pt_avl_tree must be initialized, otherwise the behavior
 *          is undefined. the type of array and cpt_avl_tree must be same, otherwise the behavior is undefined.
 *          array must be valid array, otherwise the behavior is undefine.
 */
extern void _avl_tree_insert_unique_array(_avl_tree_t* pt_avl_tree, const void* cpv_array, size_t t_count);

/**
 * Inserts an range into a avl tree.
 * @param pt_avl_tree       avl tree container.
 * @param it_begin          begin of specific range.
 * @param it_end            end of specific range.
 * @return void.
 * @remarks if pt_avl_tree == NULL then the behavior is undefined. pt_avl_tree must be initialized, otherwise the behavior
 *          is undefined. the type of [it_begin, it_end) and cpt_avl_tree must be same, otherwise the behavior is undefined.
 *          [it_begin, it_end) must be valid range, otherwise the behavior is undefine.
 */
extern void _avl_tree_insert_equal_range(_avl_tree_t* pt_avl_tree, iterator_t it_begin, iterator_t it_end);

/**
 * Inserts an array into a avl tree.
 * @param pt_avl_tree       avl tree container.
 * @param cpv_array         array.
 * @param t_count           element count of array.
 * @return void.
 * @remarks if pt_avl_tree == NULL then the behavior is undefined. pt_avl_tree must be initialized, otherwise the behavior
 *          is undefined. the type of array and cpt_avl_tree must be same, otherwise the behavior is undefined.
 *          array must be valid array, otherwise the behavior is undefine.
 */
extern void _avl_tree_insert_equal_array(_avl_tree_t* pt_avl_tree, const void* cpv_array, size_t t_count);

/*
 * Erase an element in an avl tree from specificed position.
 * @param pt_avl_tree       avl tree container.
 * @param it_pos            specificed position.
 * @return void.
 * @remarks if pt_avl_tree == NULL then the behavior is undefined. pt_avl_tree must be initialized, otherwise the behavior
 *          is undefined. it_pos must be valid iterator, otherwise the behavior is undefined.
 */
extern void _avl_tree_erase_pos(_avl_tree_t* pt_avl_tree, _avl_tree_iterator_t it_pos);

/*
 * Erase a range of element in an avl tree.
 * @param pt_avl_tree       avl tree container.
 * @param it_begin          begin of specific range.
 * @param it_end            end of specific range.
 * @return void.
 * @remarks if pt_avl_tree == NULL then the behavior is undefined. pt_avl_tree must be initialized, otherwise the behavior
 *          is undefined. [it_begin, it_end) must be valid range for pt_avl_tree, otherwise the behavior is undefine.
 */
extern void _avl_tree_erase_range(_avl_tree_t* pt_avl_tree, _avl_tree_iterator_t it_begin, _avl_tree_iterator_t it_end);

/**
 * Erase an element from a avl tree that match a specified element.
 * @param pt_avl_tree       avl tree container.
 * @param cpv_value         specific element.
 * @return the number of erased elements.
 * @remarks if pt_avl_tree == NULL or cpv_value == NULL then the behavior is undefined. cpt_avl_tree must be initialized,
 *          otherwise the behavior is undefined. 
 */
extern size_t _avl_tree_erase(_avl_tree_t* pt_avl_tree, const void* cpv_value);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_AVL_TREE_H_ */
/** eof **/

