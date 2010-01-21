/*
 *  The private interface of rb tree.
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

#ifndef _CSTL_RB_TREE_PRIVATE_H
#define _CSTL_RB_TREE_PRIVATE_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
typedef enum _tagcolor
{
    red, black
}color_t;
/*
 * +-----------+
 * | parent    |
 * +-----------+
 * | left      |
 * +-----------+
 * | right     |
 * +-----------+
 * | color     |
 * +-----------+
 * | data      |
 * |   ...     |
 * +-----------+
 */
typedef struct _tagrbnode
{
    struct _tagrbnode* _pt_parent;
    struct _tagrbnode* _pt_left;
    struct _tagrbnode* _pt_right;
    color_t            _t_color;
    char               _pc_data[1];
}rbnode_t;

typedef struct _tagrbtree
{
    /* element type information */
    _typeinfo_t       _t_typeinfo;

    /* memory allocate */
    alloc_t           _t_allocater;

    /* rb tree node */
    rbnode_t          _t_rbroot;
    size_t            _t_nodecount;

    /* less function */
    binary_function_t _t_less;
}rb_tree_t;

/* for the result of equal_range and insert_unique function */
typedef struct _tagrbtreeresultpair
{
    rb_tree_iterator_t _t_first;
    union
    {
        rb_tree_iterator_t _t_iterator;  /* for equal_range */
        bool_t              _t_bool;     /* for insert_unique */
    }_t_second;
}rb_tree_result_pair_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * Create, initialization and destroy operation functions.
 */
extern rb_tree_t* _create_rb_tree(const char* s_typename);
extern bool_t _create_rb_tree_auxiliary(rb_tree_t* pt_rb_tree, const char* s_typename);
extern void _rb_tree_init(rb_tree_t* pt_rb_tree, binary_function_t t_less);
extern void _rb_tree_destroy(rb_tree_t* pt_rb_tree);
extern void _rb_tree_destroy_auxiliary(rb_tree_t* pt_rb_tree);
extern void _rb_tree_init_copy(
    rb_tree_t* pt_rb_tree_dest, const rb_tree_t* cpt_rb_tree_src);
extern void _rb_tree_init_copy_range_ex(
    rb_tree_t* pt_rb_tree_dest, rb_tree_iterator_t t_begin, rb_tree_iterator_t t_end,
    binary_function_t t_less);
extern void _rb_tree_init_copy_range(
    rb_tree_t* pt_rb_tree_dest, rb_tree_iterator_t t_begin, rb_tree_iterator_t t_end);

/*
 * Assignment operator.
 */
extern void _rb_tree_assign(
    rb_tree_t* pt_rb_tree_dest, const rb_tree_t* cpt_rb_tree_src);

/*
 * rb_tree size operation functions.
 */
extern size_t _rb_tree_size(const rb_tree_t* cpt_rb_tree);
extern bool_t _rb_tree_empty(const rb_tree_t* cpt_rb_tree);
extern size_t _rb_tree_max_size(const rb_tree_t* cpt_rb_tree);

/*
 * Iterator support.
 */
extern rb_tree_iterator_t _rb_tree_begin(const rb_tree_t* cpt_rb_tree);
extern rb_tree_iterator_t _rb_tree_end(const rb_tree_t* cpt_rb_tree);
extern rb_tree_reverse_iterator_t _rb_tree_rbegin(const rb_tree_t* cpt_rb_tree);
extern rb_tree_reverse_iterator_t _rb_tree_rend(const rb_tree_t* cpt_rb_tree);

/*
 * Return the compare function of key.
 */
extern binary_function_t _rb_tree_key_less(const rb_tree_t* cpt_rb_tree);

/*
 * Find the value in rb tree.
 */
extern rb_tree_iterator_t _rb_tree_find(
    const rb_tree_t* cpt_rb_tree, const void* cpv_value);

/*
 * Remove all elements.
 */
extern void _rb_tree_clear(rb_tree_t* pt_rb_tree);

/*
 * Counts the numbers of element whose key is value.
 */
extern size_t _rb_tree_count(
    const rb_tree_t* cpt_rb_tree, const void* cpv_value);

/*
 * Lower bound, upper bound and equal range functions.
 */
extern rb_tree_iterator_t _rb_tree_lower_bound(
    const rb_tree_t* cpt_rb_tree, const void* cpv_value);
extern rb_tree_iterator_t _rb_tree_upper_bound(
    const rb_tree_t* cpt_rb_tree, const void* cpv_value);
extern range_t _rb_tree_equal_range(
    const rb_tree_t* cpt_rb_tree, const void* cpv_value);

/*
 * Relationship operator functions.
 */
extern bool_t _rb_tree_equal(
    const rb_tree_t* cpt_rb_treefirst, const rb_tree_t* cpt_rb_treesecond);
extern bool_t _rb_tree_not_equal(
    const rb_tree_t* cpt_rb_treefirst, const rb_tree_t* cpt_rb_treesecond);
extern bool_t _rb_tree_less(
    const rb_tree_t* cpt_rb_treefirst, const rb_tree_t* cpt_rb_treesecond);
extern bool_t _rb_tree_great(
    const rb_tree_t* cpt_rb_treefirst, const rb_tree_t* cpt_rb_treesecond);
extern bool_t _rb_tree_less_equal(
    const rb_tree_t* cpt_rb_treefirst, const rb_tree_t* cpt_rb_treesecond);
extern bool_t _rb_tree_great_equal(
    const rb_tree_t* cpt_rb_treefirst, const rb_tree_t* cpt_rb_treesecond);

/*
 * Swap the datas of first rb_tree and second rb_tree.
 */
extern void _rb_tree_swap(rb_tree_t* pt_rb_treefirst, rb_tree_t* pt_rb_treesecond);

/*
 * Insert element into rb_tree.
 */
extern rb_tree_iterator_t _rb_tree_insert_unique(
    rb_tree_t* pt_rb_tree, const void* cpv_value);
extern rb_tree_iterator_t _rb_tree_insert_equal(
    rb_tree_t* pt_rb_tree, const void* cpv_value);
extern void _rb_tree_insert_unique_range(
    rb_tree_t* pt_rb_tree, rb_tree_iterator_t t_begin, rb_tree_iterator_t t_end);
extern void _rb_tree_insert_equal_range(
    rb_tree_t* pt_rb_tree, rb_tree_iterator_t t_begin, rb_tree_iterator_t t_end);

/*
 * Erase elements form rb_tree.
 */
extern void _rb_tree_erase_pos(rb_tree_t* pt_rb_tree, rb_tree_iterator_t t_pos);
extern void _rb_tree_erase_range(
    rb_tree_t* pt_rb_tree, rb_tree_iterator_t t_begin, rb_tree_iterator_t t_end);
extern size_t _rb_tree_erase(rb_tree_t* pt_rb_tree, const void* cpv_value);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_RB_TREE_PRIVATE_H */
/** eof **/

