/*
 *  The private interface of avl tree.
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

#ifndef _CSTL_AVL_TREE_PRIVATE_H
#define _CSTL_AVL_TREE_PRIVATE_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
/*
 * +-----------+
 * | parent    |
 * +-----------+
 * | left      |
 * +-----------+
 * | right     |
 * +-----------+
 * | height    |
 * +-----------+
 * | data      |
 * |   ...     |
 * +-----------+
 */
typedef struct _tagavlnode
{
    struct _tagavlnode* _pt_parent;
    struct _tagavlnode* _pt_left;
    struct _tagavlnode* _pt_right;
    unsigned int        _un_height;
    char                _pc_data[1];
}avlnode_t;

typedef struct _tagavltree
{
    /* element type information */
    _typeinfo_t      _t_typeinfo;

    /* memory allocate */
    alloc_t          _t_allocater;

    /* avl tree node */
    avlnode_t        _t_avlroot;
    size_t           _t_nodecount;

    /* less function */
    binary_function_t _t_less;
}avl_tree_t;

/**//* for the result of equal_range and insert_unique function */
/*typedef struct _tagavltreeresultpair*/
/*{*/
/*avl_tree_iterator_t _t_first;*/
/*union*/
/*{*/
/*avl_tree_iterator_t _t_iterator; *//* for equal_range */
/*bool_t              _t_bool;     *//* for insert_unique */
/*}_t_second;*/
/*}avl_tree_result_pair_t;*/

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * Create, initialization and destroy operation functions.
 */
extern avl_tree_t* _create_avl_tree(const char* s_typename);
extern bool_t _create_avl_tree_auxiliary(avl_tree_t* pt_avl_tree, const char* s_typename);
extern void _avl_tree_init(avl_tree_t* pt_avl_tree, binary_function_t t_less);
extern void _avl_tree_destroy(avl_tree_t* pt_avl_tree);
extern void _avl_tree_destroy_auxiliary(avl_tree_t* pt_avl_tree);
extern void _avl_tree_init_copy(
    avl_tree_t* pt_avl_tree_dest, const avl_tree_t* cpt_avl_tree_src);
extern void _avl_tree_init_copy_range_ex(
    avl_tree_t* pt_avl_tree_dest, avl_tree_iterator_t t_begin, avl_tree_iterator_t t_end,
    binary_function_t t_less);
extern void _avl_tree_init_copy_range(
    avl_tree_t* pt_avl_tree_dest, avl_tree_iterator_t t_begin, avl_tree_iterator_t t_end);

/*
 * Assign operator functions.
 */
extern void _avl_tree_assign(
    avl_tree_t* pt_avl_tree_dest, const avl_tree_t* cpt_avl_tree_src);

/*
 * avl_tree_t size operation functions.
 */
extern size_t _avl_tree_size(const avl_tree_t* cpt_avl_tree);
extern bool_t _avl_tree_empty(const avl_tree_t* cpt_avl_tree);
extern size_t _avl_tree_max_size(const avl_tree_t* cpt_avl_tree);

/*
 * Iterator support.
 */
extern avl_tree_iterator_t _avl_tree_begin(const avl_tree_t* cpt_avl_tree);
extern avl_tree_iterator_t _avl_tree_end(const avl_tree_t* cpt_avl_tree);
/* private */
extern avl_tree_reverse_iterator_t _avl_tree_rbegin(const avl_tree_t* cpt_avl_tree);
extern avl_tree_reverse_iterator_t _avl_tree_rend(const avl_tree_t* cpt_avl_tree);

/*
 * Return the compare function of key (private).
 */
extern int (*_avl_tree_key_comp(const avl_tree_t* cpt_avl_tree))(
    const void*, const void*);

/*
 * Find operation functions.
 */
extern avl_tree_iterator_t _avl_tree_find(
    const avl_tree_t* cpt_avl_tree, const void* cpv_value);

/*
 * Remove all elements.
 */
extern void _avl_tree_clear(avl_tree_t* pt_avl_tree);

/*
 * Count, lower bound, upper bound and equal range operation functions.
 */
extern size_t _avl_tree_count(const avl_tree_t* cpt_avl_tree, const void* cpv_value);
extern avl_tree_iterator_t _avl_tree_lower_bound(
    const avl_tree_t* cpt_avl_tree, const void* cpv_value);
extern avl_tree_iterator_t _avl_tree_upper_bound(
    const avl_tree_t* cpt_avl_tree, const void* cpv_value);
extern range_t _avl_tree_equal_range(const avl_tree_t* cpt_avl_tree, const void* cpv_value);

/*
 * Relationship operator functions.
 */
extern bool_t _avl_tree_equal(
    const avl_tree_t* cpt_avl_treefirst, const avl_tree_t* cpt_avl_treesecond);
extern bool_t _avl_tree_not_equal(
    const avl_tree_t* cpt_avl_treefirst, const avl_tree_t* cpt_avl_treesecond);
extern bool_t _avl_tree_less(
    const avl_tree_t* cpt_avl_treefirst, const avl_tree_t* cpt_avl_treesecond);
extern bool_t _avl_tree_great(
    const avl_tree_t* cpt_avl_treefirst, const avl_tree_t* cpt_avl_treesecond);
extern bool_t _avl_tree_less_equal(
    const avl_tree_t* cpt_avl_treefirst, const avl_tree_t* cpt_avl_treesecond);
extern bool_t _avl_tree_great_equal(
    const avl_tree_t* cpt_avl_treefirst, const avl_tree_t* cpt_avl_treesecond);

/*
 * Swap the datas of first avl_tree and second avl_tree.
 */
extern void _avl_tree_swap(avl_tree_t* pt_avl_treefirst, avl_tree_t* pt_avl_treesecond);

/*
 * Insert operation functions.
 */
extern avl_tree_iterator_t _avl_tree_insert_unique(
    avl_tree_t* pt_avl_tree, const void* cpv_value);
extern avl_tree_iterator_t _avl_tree_insert_equal(
    avl_tree_t* pt_avl_tree, const void* cpv_value);
extern void _avl_tree_insert_unique_range(
    avl_tree_t* pt_avl_tree, avl_tree_iterator_t t_begin, avl_tree_iterator_t t_end);
extern void _avl_tree_insert_equal_range(
    avl_tree_t* pt_avl_tree, avl_tree_iterator_t t_begin, avl_tree_iterator_t t_end);

/*
 * Erase operation functions.
 */
extern void _avl_tree_erase_pos(avl_tree_t* pt_avl_tree, avl_tree_iterator_t t_pos);
extern void _avl_tree_erase_range(
    avl_tree_t* pt_avl_tree, avl_tree_iterator_t t_begin, avl_tree_iterator_t t_end);
extern size_t _avl_tree_erase(avl_tree_t* pt_avl_tree, const void* cpv_value);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_AVL_TREE_PRIVATE_H */
/** eof **/

