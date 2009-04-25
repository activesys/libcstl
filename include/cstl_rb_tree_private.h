/*
 *  The private interface of rb tree.
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
    /* element identify */
    size_t          _t_typesize;                          /* element size */
    char            _sz_typename[_ELEM_TYPE_NAME_SIZE+1]; /* element name */

    /* memory allocate */
    alloc_t         _t_allocater;

    /* rb tree node */
    rbnode_t        _t_rbroot;
    size_t          _t_nodecount;

    /* 
     * the compare function :
     * < 0  : element first < element second.
     * == 0 : element first == element second.
     * > 0  : element first > element second. 
     */
    int (*_pfun_cmp)(const void*, const void*);
    /* the element destroy function */
    void (*_pfun_destroy_elem)(void*);
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
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _create_rb_tree
 *        Parameters: in) t_typesize: size_t
 *                          the element type size.
 *                    in) s_typename: const char*
 *                          the element type name.
 *           Returns: rb_tree_t
 *                          new rb_tree.
 *       Description: create the new rb_tree.
 *
 * ----------------------------------------------------------------------------
 */
extern rb_tree_t _create_rb_tree(size_t t_typesize, const char* s_typename);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _rb_tree_init
 *        Parameters: in) pt_rb_tree: rb_tree_t*
 *                    in) pfun_cmp: int (*pfun)(const void*, const void*)
 *                          the function for element compare:
 *                          < 0  : element first < element second.
 *                          == 0 : element first == element second.
 *                          > 0  : element first > element second. 
 *                    in) pfun_destroy_elem: void (*pfun)(void*)
 *                          the destroy element function.
 *           Returns: void
 *       Description: initialize the rb_tree.
 *
 * ----------------------------------------------------------------------------
 */
extern void _rb_tree_init(
    rb_tree_t* pt_rb_tree,
    int (*pfun_cmp)(const void*, const void*),
    void (*pfun_destroy_elem)(void*));

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _rb_tree_destroy
 *        Parameters: in) pt_rb_tree: rb_tree_t*
 *           Returns: void
 *       Description: destroy the rb_tree.
 *
 * ----------------------------------------------------------------------------
 */
extern void _rb_tree_destroy(rb_tree_t* pt_rb_tree);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _rb_tree_copy
 *        Parameters: in) pt_rb_tree_dest: rb_tree_t*
 *                        the dest rb tree pointer.
 *                    in) cpt_rb_tree_src: const rb_tree_t*
 *                        the src rb tree pointer.
 *           Returns: void
 *       Description: the copy constructor.
 *
 * ----------------------------------------------------------------------------
 */
extern void _rb_tree_init_copy(
    rb_tree_t* pt_rb_tree_dest, const rb_tree_t* cpt_rb_tree_src);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _rb_tree_init_copy_range_cmp
 *        Parameters: in) pt_rb_tree_dest: rb_tree_t*
 *                        the dest rb tree pointer.
 *                    in) t_begin: rb_tree_iterator_t
 *                        the begin iterator
 *                    in0 t_end: rb_tree_iterator_t
 *                        the end iterator.
 *                    in) pfun_cmp: int (*pfun)(const void*, const void*)
 *                          the function for element compare:
 *                          < 0  : element first < element second.
 *                          == 0 : element first == element second.
 *                          > 0  : element first > element second. 
 *           Returns: void
 *       Description: the copy constructor with range and key compare function.
 *
 * ----------------------------------------------------------------------------
 */
extern void _rb_tree_init_copy_range_cmp(
    rb_tree_t* pt_rb_tree_dest, 
    rb_tree_iterator_t t_begin, 
    rb_tree_iterator_t t_end,
    int (*pfun_cmp)(const void*, const void*));

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _rb_tree_init_copy_range
 *        Parameters: in) pt_rb_tree_dest: rb_tree_t*
 *                        the dest rb tree pointer.
 *                    in) t_begin: rb_tree_iterator_t
 *                        the begin iterator
 *                    in0 t_end: rb_tree_iterator_t
 *                        the end iterator.
 *           Returns: void
 *       Description: the copy constructor with range.
 *
 * ----------------------------------------------------------------------------
 */
extern void _rb_tree_init_copy_range(
    rb_tree_t* pt_rb_tree_dest, 
    rb_tree_iterator_t t_begin, 
    rb_tree_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _rb_tree_assign
 *        Parameters: in) pt_rb_tree_dest: rb_tree_t*
 *                        the dest rb tree pointer.
 *                    in) cpt_rb_tree_src: const rb_tree_t*
 *                        the src rb tree pointer.
 *           Returns: void
 *       Description: the assignment operator.
 *
 * ----------------------------------------------------------------------------
 */
extern void _rb_tree_assign(
    rb_tree_t* pt_rb_tree_dest, const rb_tree_t* cpt_rb_tree_src);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _rb_tree_size
 *        Parameters: in) cpt_rb_tree: const rb_tree_t*
 *                          the dest rb_tree.
 *           Returns: size_t
 *       Description: get the rb_tree size.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t _rb_tree_size(const rb_tree_t* cpt_rb_tree);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _rb_tree_empty
 *        Parameters: in) cpt_rb_tree: const rb_tree_t*
 *                          the dest rb_tree.
 *           Returns: bool_t
 *       Description: if the rb_tree is empty.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t _rb_tree_empty(const rb_tree_t* cpt_rb_tree);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _rb_tree_max_size
 *        Parameters: in) cpt_rb_tree: const rb_tree_t*
 *                          the dest rb_tree.
 *           Returns: size_t
 *       Description: get the maximum capacity of rb_tree.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t _rb_tree_max_size(const rb_tree_t* cpt_rb_tree);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _rb_tree_begin
 *        Parameters: in) cpt_rb_tree: const rb_tree_t*
 *                          the rb_tree.
 *           Returns: rb_tree_iterator_t
 *       Description: return the random access iterator for the first element.
 *
 * ----------------------------------------------------------------------------
 */
extern rb_tree_iterator_t _rb_tree_begin(const rb_tree_t* cpt_rb_tree);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _rb_tree_end
 *        Parameters: in) cpt_rb_tree: const rb_tree_t*
 *                          the rb_tree.
 *           Returns: rb_tree_iterator_t
 *       Description: return the random access iterator for the last element.
 *
 * ----------------------------------------------------------------------------
 */
extern rb_tree_iterator_t _rb_tree_end(const rb_tree_t* cpt_rb_tree);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _rb_tree_rbegin
 *        Parameters: in) cpt_rb_tree: const rb_tree_t*
 *                          the rb_tree.
 *           Returns: rb_tree_reverse_iterator_t
 *       Description: return the reverse iterator for the first element of the
 *                    reverse iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern rb_tree_reverse_iterator_t _rb_tree_rbegin(
    const rb_tree_t* cpt_rb_tree);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _rb_tree_rend
 *        Parameters: in) cpt_rb_tree: const rb_tree_t*
 *                          the rb_tree.
 *           Returns: rb_tree_reverse_iterator_t
 *       Description: return the reverse iterator for the last element of the
 *                    reverse iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern rb_tree_reverse_iterator_t _rb_tree_rend(
    const rb_tree_t* cpt_rb_tree);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _rb_tree_key_comp
 *        Parameters: in) cpt_rb_tree: const rb_tree_t*
 *                        the rb tree pointer.
 *           Returns: int (*)(const void*, const void*)
 *       Description: return the compare function of key.
 *
 * ----------------------------------------------------------------------------
 */
extern int (*_rb_tree_key_comp(const rb_tree_t* cpt_rb_tree))(
    const void*, const void*);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _rb_tree_find
 *        Parameters: in) cpt_rb_tree: const rb_tree_t*
 *                        the rb tree pointer.
 *                    in) cpv_value: const void*
 *                        the target value.
 *           Returns: rb_tree_iterator_t
 *                        the target iterator or end iterator.
 *       Description: find the value in rb tree.
 *
 * ----------------------------------------------------------------------------
 */
extern rb_tree_iterator_t _rb_tree_find(
    const rb_tree_t* cpt_rb_tree, const void* cpv_value);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _rb_tree_clear
 *        Parameters: in) pt_rb_tree: rb_tree_t*
 *                          the rb_tree.
 *           Returns: void
 *       Description: remove all elements.
 *
 * ----------------------------------------------------------------------------
 */
extern void _rb_tree_clear(rb_tree_t* pt_rb_tree);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _rb_tree_count
 *        Parameters: in) cpt_rb_tree: const rb_tree_t*
 *                        the rb tree pointer.
 *                    in) cpv_value: const void*
 *                        the target value.
 *           Returns: size_t
 *                        count.
 *       Description: counts the numbers of element whose key is value.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t _rb_tree_count(
    const rb_tree_t* cpt_rb_tree, const void* cpv_value);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _rb_tree_lower_bound
 *        Parameters: in) cpt_rb_tree: const rb_tree_t*
 *                        the rb tree pointer.
 *                    in) cpv_value: const void*
 *                        the target value.
 *           Returns: rb_tree_iterator_t
 *                        the target iterator or end iterator.
 *       Description: find the first element whose key is not less then value.
 *
 * ----------------------------------------------------------------------------
 */
extern rb_tree_iterator_t _rb_tree_lower_bound(
    const rb_tree_t* cpt_rb_tree, const void* cpv_value);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _rb_tree_upper_bound
 *        Parameters: in) cpt_rb_tree: const rb_tree_t*
 *                        the rb tree pointer.
 *                    in) cpv_value: const void*
 *                        the target value.
 *           Returns: rb_tree_iterator_t
 *                        the target iterator or end iterator.
 *       Description: find the first element whose key is greater then value.
 *
 * ----------------------------------------------------------------------------
 */
extern rb_tree_iterator_t _rb_tree_upper_bound(
    const rb_tree_t* cpt_rb_tree, const void* cpv_value);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _rb_tree_equal_range
 *        Parameters: in) cpt_rb_tree: const rb_tree_t*
 *                        the rb tree pointer.
 *                    in) cpv_value: const void*
 *                        the target value.
 *           Returns: rb_tree_result_pair_t
 *                        the result pair.
 *       Description: find a range that contain all elements whos key is value.
 *
 * ----------------------------------------------------------------------------
 */
extern rb_tree_result_pair_t _rb_tree_equal_range(
    const rb_tree_t* cpt_rb_tree, const void* cpv_value);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _rb_tree_equal
 *        Parameters: in) cpt_rb_treefirst: const rb_tree_t*
 *                          the first rb_tree.
 *                    in) cpt_rb_treesecond: const rb_tree_t*
 *                          the second rb_tree.
 *           Returns: bool_t
 *       Description: return whether first rb_tree equal to second rb_tree.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t _rb_tree_equal(
    const rb_tree_t* cpt_rb_treefirst, const rb_tree_t* cpt_rb_treesecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _rb_tree_not_equal
 *        Parameters: in) cpt_rb_treefirst: const rb_tree_t*
 *                          the first rb_tree.
 *                    in) cpt_rb_treesecond: const rb_tree_t*
 *                          the second rb_tree.
 *           Returns: bool_t
 *       Description: return whether first rb_tree not equal to second rb_tree.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t _rb_tree_not_equal(
    const rb_tree_t* cpt_rb_treefirst, const rb_tree_t* cpt_rb_treesecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _rb_tree_less
 *        Parameters: in) cpt_rb_treefirst: const rb_tree_t*
 *                          the first rb_tree.
 *                    in) cpt_rb_treesecond: const rb_tree_t*
 *                          the second rb_tree.
 *           Returns: bool_t
 *       Description: return whether first rb_tree less then second rb_tree.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t _rb_tree_less(
    const rb_tree_t* cpt_rb_treefirst, const rb_tree_t* cpt_rb_treesecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _rb_tree_great
 *        Parameters: in) cpt_rb_treefirst: const rb_tree_t*
 *                          the first rb_tree.
 *                    in) cpt_rb_treesecond: const rb_tree_t*
 *                          the second rb_tree.
 *           Returns: bool_t
 *       Description: return whether first rb_tree greater then second rb_tree.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t _rb_tree_great(
    const rb_tree_t* cpt_rb_treefirst, const rb_tree_t* cpt_rb_treesecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _rb_tree_less_equal
 *        Parameters: in) cpt_rb_treefirst: const rb_tree_t*
 *                          the first rb_tree.
 *                    in) cpt_rb_treesecond: const rb_tree_t*
 *                          the second rb_tree.
 *           Returns: bool_t
 *       Description: return whether first rb_tree less then or equal to the 
 *                    second rb_tree.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t _rb_tree_less_equal(
    const rb_tree_t* cpt_rb_treefirst, const rb_tree_t* cpt_rb_treesecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _rb_tree_great_equal
 *        Parameters: in) cpt_rb_treefirst: const rb_tree_t*
 *                          the first rb_tree.
 *                    in) cpt_rb_treesecond: const rb_tree_t*
 *                          the second rb_tree.
 *           Returns: bool_t
 *       Description: return whether first rb_tree greater then or equal to the
 *                    second rb_tree.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t _rb_tree_great_equal(
    const rb_tree_t* cpt_rb_treefirst, const rb_tree_t* cpt_rb_treesecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _rb_tree_swap
 *        Parameters: in) pt_rb_treefirst: rb_tree_t*
 *                          the first rb_tree.
 *                    in) pt_rb_treesecond: rb_tree_t*
 *                          the second rb_tree.
 *           Returns: void
 *       Description: swap the datas of first rb_tree and second rb_tree.
 *
 * ----------------------------------------------------------------------------
 */
extern void _rb_tree_swap(
    rb_tree_t* pt_rb_treefirst, rb_tree_t* pt_rb_treesecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _rb_tree_insert_unique
 *        Parameters: in) pt_rb_tree: rb_tree_t*
 *                        the rb tree pointer.
 *                    in) cpv_value: const void*
 *                        the target value.
 *           Returns: rb_tree_iterator_t
 *                        the target iterator or end iterator.
 *       Description: insert unique value into rb tree.
 *
 * ----------------------------------------------------------------------------
 */
extern rb_tree_result_pair_t _rb_tree_insert_unique(
    rb_tree_t* pt_rb_tree, const void* cpv_value);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _rb_tree_insert_equal
 *        Parameters: in) pt_rb_tree: rb_tree_t*
 *                        the rb tree pointer.
 *                    in) cpv_value: const void*
 *                        the target value.
 *           Returns: rb_tree_iterator_t
 *                        the target iterator or end iterator.
 *       Description: insert equal value into rb tree.
 *
 * ----------------------------------------------------------------------------
 */
extern rb_tree_iterator_t _rb_tree_insert_equal(
    rb_tree_t* pt_rb_tree, const void* cpv_value);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _rb_tree_insert_unique_range
 *        Parameters: in) pt_rb_tree: rb_tree_t*
 *                        the rb tree pointer.
 *                    in) t_begin: rb_tree_iterator_t
 *                        the begin iterator
 *                    in0 t_end: rb_tree_iterator_t
 *                        the end iterator.
 *           Returns: void
 *       Description: insert a range into the val tree.
 *
 * ----------------------------------------------------------------------------
 */
extern void _rb_tree_insert_unique_range(
    rb_tree_t* pt_rb_tree, 
    rb_tree_iterator_t t_begin, 
    rb_tree_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _rb_tree_insert_equal_range
 *        Parameters: in) pt_rb_tree: rb_tree_t*
 *                        the rb tree pointer.
 *                    in) t_begin: rb_tree_iterator_t
 *                        the begin iterator.
 *                    in) t_end: rb_tree_iterator_t
 *                        the end iterator.
 *           Returns: void
 *       Description: insert a range into rb tree.
 *
 * ----------------------------------------------------------------------------
 */
extern void _rb_tree_insert_equal_range(
    rb_tree_t* pt_rb_tree, 
    rb_tree_iterator_t t_begin,
    rb_tree_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _rb_tree_erase_pos
 *        Parameters: in) pt_rb_tree: rb_tree_t*
 *                        the rb tree pointer.
 *                    in) t_pos: rb_tree_iterator_t
 *                        the erase iterator.
 *           Returns: void
 *       Description: erase the element pointed by t_pos.
 *
 * ----------------------------------------------------------------------------
 */
extern void _rb_tree_erase_pos(
    rb_tree_t* pt_rb_tree, rb_tree_iterator_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _rb_tree_erase_range
 *        Parameters: in) pt_rb_tree: rb_tree_t*
 *                        the rb tree pointer.
 *                    in) t_begin: rb_tree_iterator_t
 *                        the begin iterator.
 *                    in) t_end: rb_tree_iterator_t
 *                        the end iterator.
 *           Returns: void
 *       Description: erase the all elements in the range.
 *
 * ----------------------------------------------------------------------------
 */
extern void _rb_tree_erase_range(
    rb_tree_t* pt_rb_tree, 
    rb_tree_iterator_t t_begin, 
    rb_tree_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _rb_tree_erase
 *        Parameters: in) pt_rb_tree: rb_tree_t*
 *                        the rb tree pointer.
 *                    in) cpv_value: const void*
 *                        the target value.
 *           Returns: size_t
 *                        the element numbers.
 *       Description: erase all elements whose key is value.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t _rb_tree_erase(rb_tree_t* pt_rb_tree, const void* cpv_value);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_RB_TREE_PRIVATE_H */
/** eof **/

