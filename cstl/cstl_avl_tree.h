/*
 *  The interface of avl tree.
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
/*
 * Create, initialization and destroy operation functions.
 */
extern _avl_tree_t* _create_avl_tree(const char* s_typename);
extern void _avl_tree_init(_avl_tree_t* pt_avl_tree, binary_function_t t_compare);
extern void _avl_tree_destroy(_avl_tree_t* pt_avl_tree);
extern void _avl_tree_init_copy(
    _avl_tree_t* pt_avl_tree_dest, const _avl_tree_t* cpt_avl_tree_src);
extern void _avl_tree_init_copy_range_ex(
    _avl_tree_t* pt_avl_tree_dest, _avl_tree_iterator_t t_begin, _avl_tree_iterator_t t_end,
    binary_function_t t_compare);
extern void _avl_tree_init_copy_range(
    _avl_tree_t* pt_avl_tree_dest, _avl_tree_iterator_t t_begin, _avl_tree_iterator_t t_end);

/*
 * Assign operator functions.
 */
extern void _avl_tree_assign(
    _avl_tree_t* pt_avl_tree_dest, const _avl_tree_t* cpt_avl_tree_src);

/*
 * _avl_tree_t size operation functions.
 */
extern size_t _avl_tree_size(const _avl_tree_t* cpt_avl_tree);
extern bool_t _avl_tree_empty(const _avl_tree_t* cpt_avl_tree);
extern size_t _avl_tree_max_size(const _avl_tree_t* cpt_avl_tree);

/*
 * Iterator support.
 */
extern _avl_tree_iterator_t _avl_tree_begin(const _avl_tree_t* cpt_avl_tree);
extern _avl_tree_iterator_t _avl_tree_end(const _avl_tree_t* cpt_avl_tree);
/* private */
extern _avl_tree_reverse_iterator_t _avl_tree_rbegin(const _avl_tree_t* cpt_avl_tree);
extern _avl_tree_reverse_iterator_t _avl_tree_rend(const _avl_tree_t* cpt_avl_tree);

/*
 * Return the compare function of key.
 */
extern binary_function_t _avl_tree_key_comp(const _avl_tree_t* cpt_avl_tree);

/*
 * Find operation functions.
 */
extern _avl_tree_iterator_t _avl_tree_find(
    const _avl_tree_t* cpt_avl_tree, const void* cpv_value);

/*
 * Remove all elements.
 */
extern void _avl_tree_clear(_avl_tree_t* pt_avl_tree);

/*
 * Count, lower bound, upper bound and equal range operation functions.
 */
extern size_t _avl_tree_count(const _avl_tree_t* cpt_avl_tree, const void* cpv_value);
extern _avl_tree_iterator_t _avl_tree_lower_bound(
    const _avl_tree_t* cpt_avl_tree, const void* cpv_value);
extern _avl_tree_iterator_t _avl_tree_upper_bound(
    const _avl_tree_t* cpt_avl_tree, const void* cpv_value);
extern range_t _avl_tree_equal_range(const _avl_tree_t* cpt_avl_tree, const void* cpv_value);

/*
 * Relationship operator functions.
 */
extern bool_t _avl_tree_equal(
    const _avl_tree_t* cpt_avl_treefirst, const _avl_tree_t* cpt_avl_treesecond);
extern bool_t _avl_tree_not_equal(
    const _avl_tree_t* cpt_avl_treefirst, const _avl_tree_t* cpt_avl_treesecond);
extern bool_t _avl_tree_less(
    const _avl_tree_t* cpt_avl_treefirst, const _avl_tree_t* cpt_avl_treesecond);
extern bool_t _avl_tree_greater(
    const _avl_tree_t* cpt_avl_treefirst, const _avl_tree_t* cpt_avl_treesecond);
extern bool_t _avl_tree_less_equal(
    const _avl_tree_t* cpt_avl_treefirst, const _avl_tree_t* cpt_avl_treesecond);
extern bool_t _avl_tree_greater_equal(
    const _avl_tree_t* cpt_avl_treefirst, const _avl_tree_t* cpt_avl_treesecond);

/*
 * Swap the datas of first avl_tree and second avl_tree.
 */
extern void _avl_tree_swap(_avl_tree_t* pt_avl_treefirst, _avl_tree_t* pt_avl_treesecond);

/*
 * Insert operation functions.
 */
extern _avl_tree_iterator_t _avl_tree_insert_unique(
    _avl_tree_t* pt_avl_tree, const void* cpv_value);
extern _avl_tree_iterator_t _avl_tree_insert_equal(
    _avl_tree_t* pt_avl_tree, const void* cpv_value);
extern void _avl_tree_insert_unique_range(
    _avl_tree_t* pt_avl_tree, _avl_tree_iterator_t t_begin, _avl_tree_iterator_t t_end);
extern void _avl_tree_insert_equal_range(
    _avl_tree_t* pt_avl_tree, _avl_tree_iterator_t t_begin, _avl_tree_iterator_t t_end);

/*
 * Erase operation functions.
 */
extern void _avl_tree_erase_pos(_avl_tree_t* pt_avl_tree, _avl_tree_iterator_t t_pos);
extern void _avl_tree_erase_range(
    _avl_tree_t* pt_avl_tree, _avl_tree_iterator_t t_begin, _avl_tree_iterator_t t_end);
extern size_t _avl_tree_erase(_avl_tree_t* pt_avl_tree, const void* cpv_value);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_AVL_TREE_H_ */
/** eof **/

