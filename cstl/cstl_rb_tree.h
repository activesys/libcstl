/*
 *  The interface of rb tree.
 *  Copyright (C)  2008,2009,2010,2011  Wangbo
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
extern void _rb_tree_init(_rb_tree_t* pt_rb_tree, binary_function_t t_compare);

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
extern void _rb_tree_init_copy_range_ex(
    _rb_tree_t* pt_rb_tree_dest, _rb_tree_iterator_t t_begin, _rb_tree_iterator_t t_end,
    binary_function_t t_compare);
extern void _rb_tree_init_copy_range(
    _rb_tree_t* pt_rb_tree_dest, _rb_tree_iterator_t t_begin, _rb_tree_iterator_t t_end);
extern void _rb_tree_destroy(_rb_tree_t* pt_rb_tree);

/*
 * Assignment operator.
 */
extern void _rb_tree_assign(
    _rb_tree_t* pt_rb_tree_dest, const _rb_tree_t* cpt_rb_tree_src);

/*
 * rb_tree size operation functions.
 */
extern size_t _rb_tree_size(const _rb_tree_t* cpt_rb_tree);
extern bool_t _rb_tree_empty(const _rb_tree_t* cpt_rb_tree);
extern size_t _rb_tree_max_size(const _rb_tree_t* cpt_rb_tree);

/*
 * Iterator support.
 */
extern _rb_tree_iterator_t _rb_tree_begin(const _rb_tree_t* cpt_rb_tree);
extern _rb_tree_iterator_t _rb_tree_end(const _rb_tree_t* cpt_rb_tree);
extern _rb_tree_reverse_iterator_t _rb_tree_rbegin(const _rb_tree_t* cpt_rb_tree);
extern _rb_tree_reverse_iterator_t _rb_tree_rend(const _rb_tree_t* cpt_rb_tree);

/*
 * Return the compare function of key.
 */
extern binary_function_t _rb_tree_key_comp(const _rb_tree_t* cpt_rb_tree);

/*
 * Find the value in rb tree.
 */
extern _rb_tree_iterator_t _rb_tree_find(
    const _rb_tree_t* cpt_rb_tree, const void* cpv_value);

/*
 * Remove all elements.
 */
extern void _rb_tree_clear(_rb_tree_t* pt_rb_tree);

/*
 * Counts the numbers of element whose key is value.
 */
extern size_t _rb_tree_count(
    const _rb_tree_t* cpt_rb_tree, const void* cpv_value);

/*
 * Lower bound, upper bound and equal range functions.
 */
extern _rb_tree_iterator_t _rb_tree_lower_bound(
    const _rb_tree_t* cpt_rb_tree, const void* cpv_value);
extern _rb_tree_iterator_t _rb_tree_upper_bound(
    const _rb_tree_t* cpt_rb_tree, const void* cpv_value);
extern range_t _rb_tree_equal_range(
    const _rb_tree_t* cpt_rb_tree, const void* cpv_value);

/*
 * Relationship operator functions.
 */
extern bool_t _rb_tree_equal(
    const _rb_tree_t* cpt_rb_treefirst, const _rb_tree_t* cpt_rb_treesecond);
extern bool_t _rb_tree_not_equal(
    const _rb_tree_t* cpt_rb_treefirst, const _rb_tree_t* cpt_rb_treesecond);
extern bool_t _rb_tree_less(
    const _rb_tree_t* cpt_rb_treefirst, const _rb_tree_t* cpt_rb_treesecond);
extern bool_t _rb_tree_greater(
    const _rb_tree_t* cpt_rb_treefirst, const _rb_tree_t* cpt_rb_treesecond);
extern bool_t _rb_tree_less_equal(
    const _rb_tree_t* cpt_rb_treefirst, const _rb_tree_t* cpt_rb_treesecond);
extern bool_t _rb_tree_greater_equal(
    const _rb_tree_t* cpt_rb_treefirst, const _rb_tree_t* cpt_rb_treesecond);

/*
 * Swap the datas of first rb_tree and second rb_tree.
 */
extern void _rb_tree_swap(_rb_tree_t* pt_rb_treefirst, _rb_tree_t* pt_rb_treesecond);

/*
 * Insert element into rb_tree.
 */
extern _rb_tree_iterator_t _rb_tree_insert_unique(
    _rb_tree_t* pt_rb_tree, const void* cpv_value);
extern _rb_tree_iterator_t _rb_tree_insert_equal(
    _rb_tree_t* pt_rb_tree, const void* cpv_value);
extern void _rb_tree_insert_unique_range(
    _rb_tree_t* pt_rb_tree, _rb_tree_iterator_t t_begin, _rb_tree_iterator_t t_end);
extern void _rb_tree_insert_equal_range(
    _rb_tree_t* pt_rb_tree, _rb_tree_iterator_t t_begin, _rb_tree_iterator_t t_end);

/*
 * Erase elements form rb_tree.
 */
extern void _rb_tree_erase_pos(_rb_tree_t* pt_rb_tree, _rb_tree_iterator_t t_pos);
extern void _rb_tree_erase_range(
    _rb_tree_t* pt_rb_tree, _rb_tree_iterator_t t_begin, _rb_tree_iterator_t t_end);
extern size_t _rb_tree_erase(_rb_tree_t* pt_rb_tree, const void* cpv_value);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_RB_TREE_H_ */
/** eof **/

