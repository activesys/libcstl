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
 *  Author Email: activesys.wb@gmail.com
 *                activesys@sina.com.cn
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
    /* element identify */
    size_t          _t_typesize;                          /* element size */
    char            _sz_typename[_ELEM_TYPE_NAME_SIZE+1]; /* element name */

    /* memory allocate */
    alloc_t         _t_allocater;

    /* avl tree node */
    avlnode_t       _t_avlroot;
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
}avl_tree_t;

/* for the result of equal_range and insert_unique function */
typedef struct _tagavltreeresultpair
{
    avl_tree_iterator_t _t_first;
    union
    {
        avl_tree_iterator_t _t_iterator; /* for equal_range */
        bool_t              _t_bool;     /* for insert_unique */
    }_t_second;
}avl_tree_result_pair_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _create_avl_tree
 *        Parameters: in) t_typesize: size_t
 *                          the element type size.
 *                    in) s_typename: const char*
 *                          the element type name.
 *           Returns: avl_tree_t
 *                          new avl_tree.
 *       Description: create the new avl_tree.
 *
 * ----------------------------------------------------------------------------
 */
extern avl_tree_t _create_avl_tree(size_t t_typesize, const char* s_typename);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _avl_tree_init
 *        Parameters: in) pt_avl_tree: avl_tree_t*
 *                    in) pfun_cmp: int (*pfun)(const void*, const void*)
 *                          the function for element compare:
 *                          < 0  : element first < element second.
 *                          == 0 : element first == element second.
 *                          > 0  : element first > element second. 
 *                    in) pfun_destroy_elem: void (*pfun)(void*)
 *                          the destroy element function.
 *           Returns: void
 *       Description: initialize the avl_tree.
 *
 * ----------------------------------------------------------------------------
 */
extern void _avl_tree_init(
    avl_tree_t* pt_avl_tree,
    int (*pfun_cmp)(const void*, const void*),
    void (*pfun_destroy_elem)(void*));

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _avl_tree_destroy
 *        Parameters: in) pt_avl_tree: avl_tree_t*
 *           Returns: void
 *       Description: destroy the avl_tree.
 *
 * ----------------------------------------------------------------------------
 */
extern void _avl_tree_destroy(avl_tree_t* pt_avl_tree);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _avl_tree_copy
 *        Parameters: in) pt_avl_tree_dest: avl_tree_t*
 *                        the dest avl tree pointer.
 *                    in) cpt_avl_tree_src: const avl_tree_t*
 *                        the src avl tree pointer.
 *           Returns: void
 *       Description: copy the avl_tree_t from src to dest.
 *
 * ----------------------------------------------------------------------------
 */
extern void _avl_tree_init_copy(
    avl_tree_t* pt_avl_tree_dest, const avl_tree_t* cpt_avl_tree_src);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _avl_tree_init_copy_range_cmp
 *        Parameters: in) pt_avl_tree_dest: avl_tree_t*
 *                        the dest rb tree pointer.
 *                    in) t_begin: avl_tree_iterator_t
 *                        the begin iterator
 *                    in0 t_end: avl_tree_iterator_t
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
extern void _avl_tree_init_copy_range_cmp(
    avl_tree_t* pt_avl_tree_dest, 
    avl_tree_iterator_t t_begin, 
    avl_tree_iterator_t t_end,
    int (*pfun_cmp)(const void*, const void*));

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _avl_tree_init_copy_range
 *        Parameters: in) pt_avl_tree_dest: avl_tree_t*
 *                        the dest rb tree pointer.
 *                    in) t_begin: avl_tree_iterator_t
 *                        the begin iterator
 *                    in0 t_end: avl_tree_iterator_t
 *                        the end iterator.
 *           Returns: void
 *       Description: the copy constructor with range.
 *
 * ----------------------------------------------------------------------------
 */
extern void _avl_tree_init_copy_range(
    avl_tree_t* pt_avl_tree_dest, 
    avl_tree_iterator_t t_begin, 
    avl_tree_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _avl_tree_assign
 *        Parameters: in) pt_avl_tree_dest: avl_tree_t*
 *                        the dest avl tree pointer.
 *                    in) cpt_avl_tree_src: const avl_tree_t*
 *                        the src avl tree pointer.
 *           Returns: void
 *       Description: assign the avl_tree_t from src to dest.
 *
 * ----------------------------------------------------------------------------
 */
extern void _avl_tree_assign(
    avl_tree_t* pt_avl_tree_dest, const avl_tree_t* cpt_avl_tree_src);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _avl_tree_size
 *        Parameters: in) cpt_avl_tree: const avl_tree_t*
 *                          the dest avl_tree.
 *           Returns: size_t
 *       Description: get the avl_tree size.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t _avl_tree_size(const avl_tree_t* cpt_avl_tree);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _avl_tree_empty
 *        Parameters: in) cpt_avl_tree: const avl_tree_t*
 *                          the dest avl_tree.
 *           Returns: bool_t
 *       Description: if the avl_tree is empty.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t _avl_tree_empty(const avl_tree_t* cpt_avl_tree);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _avl_tree_max_size
 *        Parameters: in) cpt_avl_tree: const avl_tree_t*
 *                          the dest avl_tree.
 *           Returns: size_t
 *       Description: get the maximum capacity of avl_tree.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t _avl_tree_max_size(const avl_tree_t* cpt_avl_tree);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _avl_tree_begin
 *        Parameters: in) cpt_avl_tree: const avl_tree_t*
 *                          the avl_tree.
 *           Returns: avl_tree_iterator_t
 *       Description: return the random access iterator for the first element.
 *
 * ----------------------------------------------------------------------------
 */
extern avl_tree_iterator_t _avl_tree_begin(const avl_tree_t* cpt_avl_tree);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _avl_tree_end
 *        Parameters: in) cpt_avl_tree: const avl_tree_t*
 *                          the avl_tree.
 *           Returns: avl_tree_iterator_t
 *       Description: return the random access iterator for the last element.
 *
 * ----------------------------------------------------------------------------
 */
extern avl_tree_iterator_t _avl_tree_end(const avl_tree_t* cpt_avl_tree);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _avl_tree_rbegin
 *        Parameters: in) cpt_avl_tree: const avl_tree_t*
 *                          the avl_tree.
 *           Returns: avl_tree_reverse_iterator_t
 *       Description: return the reverse iterator for the first element of the
 *                    reverse iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern avl_tree_reverse_iterator_t _avl_tree_rbegin(
    const avl_tree_t* cpt_avl_tree);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _avl_tree_rend
 *        Parameters: in) cpt_avl_tree: const avl_tree_t*
 *                          the avl_tree.
 *           Returns: avl_tree_reverse_iterator_t
 *       Description: return the reverse iterator for the last element of the
 *                    reverse iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern avl_tree_reverse_iterator_t _avl_tree_rend(
    const avl_tree_t* cpt_avl_tree);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _avl_tree_key_comp
 *        Parameters: in) cpt_avl_tree: const avl_tree_t*
 *                        the avl tree pointer.
 *           Returns: int (*)(const void*, const void*)
 *       Description: return the compare function of key.
 *
 * ----------------------------------------------------------------------------
 */
extern int (*_avl_tree_key_comp(const avl_tree_t* cpt_avl_tree))(
    const void*, const void*);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _avl_tree_find
 *        Parameters: in) cpt_avl_tree: const avl_tree_t*
 *                        the avl tree pointer.
 *                    in) cpv_value: const void*
 *                        the target value.
 *           Returns: avl_tree_iterator_t
 *                        the target iterator or end iterator.
 *       Description: find the value in avl tree.
 *
 * ----------------------------------------------------------------------------
 */
extern avl_tree_iterator_t _avl_tree_find(
    const avl_tree_t* cpt_avl_tree, const void* cpv_value);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _avl_tree_clear
 *        Parameters: in) pt_avl_tree: avl_tree_t*
 *                          the avl_tree.
 *           Returns: void
 *       Description: remove all elements.
 *
 * ----------------------------------------------------------------------------
 */
extern void _avl_tree_clear(avl_tree_t* pt_avl_tree);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _avl_tree_count
 *        Parameters: in) cpt_avl_tree: const avl_tree_t*
 *                        the avl tree pointer.
 *                    in) cpv_value: const void*
 *                        the target value.
 *           Returns: size_t
 *                        count.
 *       Description: counts the numbers of element whose key is value.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t _avl_tree_count(
    const avl_tree_t* cpt_avl_tree, const void* cpv_value);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _avl_tree_lower_bound
 *        Parameters: in) cpt_avl_tree: const avl_tree_t*
 *                        the avl tree pointer.
 *                    in) cpv_value: const void*
 *                        the target value.
 *           Returns: avl_tree_iterator_t
 *                        the target iterator or end iterator.
 *       Description: find the first element whose key is not less then value.
 *
 * ----------------------------------------------------------------------------
 */
extern avl_tree_iterator_t _avl_tree_lower_bound(
    const avl_tree_t* cpt_avl_tree, const void* cpv_value);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _avl_tree_upper_bound
 *        Parameters: in) cpt_avl_tree: const avl_tree_t*
 *                        the avl tree pointer.
 *                    in) cpv_value: const void*
 *                        the target value.
 *           Returns: avl_tree_iterator_t
 *                        the target iterator or end iterator.
 *       Description: find the first element whose key is greater then value.
 *
 * ----------------------------------------------------------------------------
 */
extern avl_tree_iterator_t _avl_tree_upper_bound(
    const avl_tree_t* cpt_avl_tree, const void* cpv_value);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _avl_tree_equal_range
 *        Parameters: in) cpt_avl_tree: const avl_tree_t*
 *                        the avl tree pointer.
 *                    in) cpv_value: const void*
 *                        the target value.
 *           Returns: avl_tree_result_pair_t
 *                        the result pair.
 *       Description: find a range that contain all elements whos key is value.
 *
 * ----------------------------------------------------------------------------
 */
extern avl_tree_result_pair_t _avl_tree_equal_range(
    const avl_tree_t* cpt_avl_tree, const void* cpv_value);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _avl_tree_equal
 *        Parameters: in) cpt_avl_treefirst: const avl_tree_t*
 *                          the first avl_tree.
 *                    in) cpt_avl_treesecond: const avl_tree_t*
 *                          the second avl_tree.
 *           Returns: bool_t
 *       Description: return whether first avl_tree equal to second avl_tree.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t _avl_tree_equal(
    const avl_tree_t* cpt_avl_treefirst, const avl_tree_t* cpt_avl_treesecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _avl_tree_not_equal
 *        Parameters: in) cpt_avl_treefirst: const avl_tree_t*
 *                          the first avl_tree.
 *                    in) cpt_avl_treesecond: const avl_tree_t*
 *                          the second avl_tree.
 *           Returns: bool_t
 *       Description: return whether first avl_tree not equal to second avl_tree.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t _avl_tree_not_equal(
    const avl_tree_t* cpt_avl_treefirst, const avl_tree_t* cpt_avl_treesecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _avl_tree_less
 *        Parameters: in) cpt_avl_treefirst: const avl_tree_t*
 *                          the first avl_tree.
 *                    in) cpt_avl_treesecond: const avl_tree_t*
 *                          the second avl_tree.
 *           Returns: bool_t
 *       Description: return whether first avl_tree less then second avl_tree.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t _avl_tree_less(
    const avl_tree_t* cpt_avl_treefirst, const avl_tree_t* cpt_avl_treesecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _avl_tree_great
 *        Parameters: in) cpt_avl_treefirst: const avl_tree_t*
 *                          the first avl_tree.
 *                    in) cpt_avl_treesecond: const avl_tree_t*
 *                          the second avl_tree.
 *           Returns: bool_t
 *       Description: return whether first avl_tree greater then second avl_tree.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t _avl_tree_great(
    const avl_tree_t* cpt_avl_treefirst, const avl_tree_t* cpt_avl_treesecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _avl_tree_less_equal
 *        Parameters: in) cpt_avl_treefirst: const avl_tree_t*
 *                          the first avl_tree.
 *                    in) cpt_avl_treesecond: const avl_tree_t*
 *                          the second avl_tree.
 *           Returns: bool_t
 *       Description: return whether first avl_tree less then or equal to the 
 *                    second avl_tree.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t _avl_tree_less_equal(
    const avl_tree_t* cpt_avl_treefirst, const avl_tree_t* cpt_avl_treesecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _avl_tree_great_equal
 *        Parameters: in) cpt_avl_treefirst: const avl_tree_t*
 *                          the first avl_tree.
 *                    in) cpt_avl_treesecond: const avl_tree_t*
 *                          the second avl_tree.
 *           Returns: bool_t
 *       Description: return whether first avl_tree greater then or equal to the
 *                    second avl_tree.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t _avl_tree_great_equal(
    const avl_tree_t* cpt_avl_treefirst, const avl_tree_t* cpt_avl_treesecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _avl_tree_swap
 *        Parameters: in) pt_avl_treefirst: avl_tree_t*
 *                          the first avl_tree.
 *                    in) pt_avl_treesecond: avl_tree_t*
 *                          the second avl_tree.
 *           Returns: void
 *       Description: swap the datas of first avl_tree and second avl_tree.
 *
 * ----------------------------------------------------------------------------
 */
extern void _avl_tree_swap(
    avl_tree_t* pt_avl_treefirst, avl_tree_t* pt_avl_treesecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _avl_tree_insert_unique
 *        Parameters: in) pt_avl_tree: avl_tree_t*
 *                        the avl tree pointer.
 *                    in) cpv_value: const void*
 *                        the target value.
 *           Returns: avl_tree_iterator_t
 *                        the target iterator or end iterator.
 *       Description: insert unique value into avl tree.
 *
 * ----------------------------------------------------------------------------
 */
extern avl_tree_result_pair_t _avl_tree_insert_unique(
    avl_tree_t* pt_avl_tree, const void* cpv_value);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _avl_tree_insert_equal
 *        Parameters: in) pt_avl_tree: avl_tree_t*
 *                        the avl tree pointer.
 *                    in) cpv_value: const void*
 *                        the target value.
 *           Returns: avl_tree_iterator_t
 *                        the target iterator or end iterator.
 *       Description: insert equal value into avl tree.
 *
 * ----------------------------------------------------------------------------
 */
extern avl_tree_iterator_t _avl_tree_insert_equal(
    avl_tree_t* pt_avl_tree, const void* cpv_value);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _avl_tree_insert_unique_range
 *        Parameters: in) pt_avl_tree: avl_tree_t*
 *                        the avl tree pointer.
 *                    in) t_begin: avl_tree_iterator_t
 *                        the begin iterator
 *                    in0 t_end: avl_tree_iterator_t
 *                        the end iterator.
 *           Returns: void
 *       Description: insert a range into the val tree.
 *
 * ----------------------------------------------------------------------------
 */
extern void _avl_tree_insert_unique_range(
    avl_tree_t* pt_avl_tree, 
    avl_tree_iterator_t t_begin, 
    avl_tree_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _avl_tree_insert_equal_range
 *        Parameters: in) pt_avl_tree: avl_tree_t*
 *                        the avl tree pointer.
 *                    in) t_begin: avl_tree_iterator_t
 *                        the begin iterator.
 *                    in) t_end: avl_tree_iterator_t
 *                        the end iterator.
 *           Returns: void
 *       Description: insert a range into avl tree.
 *
 * ----------------------------------------------------------------------------
 */
extern void _avl_tree_insert_equal_range(
    avl_tree_t* pt_avl_tree, 
    avl_tree_iterator_t t_begin,
    avl_tree_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _avl_tree_erase_pos
 *        Parameters: in) pt_avl_tree: avl_tree_t*
 *                        the avl tree pointer.
 *                    in) t_pos: avl_tree_iterator_t
 *                        the erase iterator.
 *           Returns: void
 *       Description: erase the element pointed by t_pos.
 *
 * ----------------------------------------------------------------------------
 */
extern void _avl_tree_erase_pos(
    avl_tree_t* pt_avl_tree, avl_tree_iterator_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _avl_tree_erase_range
 *        Parameters: in) pt_avl_tree: avl_tree_t*
 *                        the avl tree pointer.
 *                    in) t_begin: avl_tree_iterator_t
 *                        the begin iterator.
 *                    in) t_end: avl_tree_iterator_t
 *                        the end iterator.
 *           Returns: void
 *       Description: erase the all elements in the range.
 *
 * ----------------------------------------------------------------------------
 */
extern void _avl_tree_erase_range(
    avl_tree_t* pt_avl_tree, 
    avl_tree_iterator_t t_begin, 
    avl_tree_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _avl_tree_erase
 *        Parameters: in) pt_avl_tree: avl_tree_t*
 *                        the avl tree pointer.
 *                    in) cpv_value: const void*
 *                        the target value.
 *           Returns: size_t
 *                        the element numbers.
 *       Description: erase all elements whose key is value.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t _avl_tree_erase(avl_tree_t* pt_avl_tree, const void* cpv_value);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_AVL_TREE_PRIVATE_H */
/** eof **/

