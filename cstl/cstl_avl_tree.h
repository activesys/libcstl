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
extern void _avl_tree_init(_avl_tree_t* pt_avl_tree, binary_function_t t_compare);

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
 *          the behavior is undefined. [it_begin, it_end) must be belong to a initialized avl tree, otherwise the behavior
 *          is undefined. the type of [it_begin, it_end) and pt_dest must be same, otherwise the behavior is undefined.
 */
extern void _avl_tree_init_copy_range(_avl_tree_t* pt_dest, _avl_tree_iterator_t it_begin, _avl_tree_iterator_t it_end);

/**
 * Initialize avl tree container with specific range and compare function.
 * @param pt_dest           destination avl tree.
 * @param it_begin          begin of range.
 * @param it_end            end of range.
 * @param t_compare         compare function.
 * @return void.
 * @remarks if pt_dest == NULL, then the behavior is undefined, pt_dest must be created by _create_avl_tree(), otherwise
 *          the behavior is undefined. [it_begin, it_end) must be belong to a initialized avl tree, otherwise the behavior
 *          is undefined. the type of [it_begin, it_end) and pt_dest must be same, otherwise the behavior is undefined. if
 *          t_compare == NULL, then use default compare function.
 */
extern void _avl_tree_init_copy_range_ex(
    _avl_tree_t* pt_dest, _avl_tree_iterator_t it_begin, _avl_tree_iterator_t it_end, binary_function_t t_compare);

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

