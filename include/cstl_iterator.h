/*
 *  The user interface of iterator.
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

#ifndef _CSTL_ITERATOR_H
#define _CSTL_ITERATOR_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/* vector iterator handler */
#define _GET_VECTOR_COREPOS(pt_iterator)\
    ((pt_iterator)->_t_pos._pc_corepos)
#define _GET_VECTOR_CONTAINER(pt_iterator)\
    ((vector_t*)((pt_iterator)->_pt_container))
#define _GET_VECTOR_CONTAINER_TYPE(pt_iterator)\
    ((pt_iterator)->_t_containertype)
#define _GET_VECTOR_ITERATOR_TYPE(pt_iterator)\
    ((pt_iterator)->_t_iteratortype)
/* list iterator handler */
#define _GET_LIST_COREPOS(pt_iterator)\
    ((pt_iterator)->_t_pos._pc_corepos)
#define _GET_LIST_CONTAINER(pt_iterator)\
    ((list_t*)((pt_iterator)->_pt_container))
#define _GET_LIST_CONTAINER_TYPE(pt_iterator)\
    ((pt_iterator)->_t_containertype)
#define _GET_LIST_ITERATOR_TYPE(pt_iterator)\
    ((pt_iterator)->_t_iteratortype)
/* deque iterator handler */
#define _GET_DEQUE_MAP_POINTER(pt_iterator)\
    ((pt_iterator)->_t_pos._t_dequepos._ppc_mappos)
#define _GET_DEQUE_FIRST_POS(pt_iterator)\
    ((pt_iterator)->_t_pos._t_dequepos._pc_first)
#define _GET_DEQUE_AFTERLAST_POS(pt_iterator)\
    ((pt_iterator)->_t_pos._t_dequepos._pc_afterlast)
#define _GET_DEQUE_COREPOS(pt_iterator)\
    ((pt_iterator)->_t_pos._t_dequepos._pc_corepos)
#define _GET_DEQUE_CONTAINER(pt_iterator)\
    ((deque_t*)((pt_iterator)->_pt_container))
#define _GET_DEQUE_CONTAINER_TYPE(pt_iterator)\
    ((pt_iterator)->_t_containertype)
#define _GET_DEQUE_ITERATOR_TYPE(pt_iterator)\
    ((pt_iterator)->_t_iteratortype)
/* slist iterator handler */
#define _GET_SLIST_COREPOS(pt_iterator)\
    ((pt_iterator)->_t_pos._pc_corepos)
#define _GET_SLIST_CONTAINER(pt_iterator)\
    ((slist_t*)((pt_iterator)->_pt_container))
#define _GET_SLIST_CONTAINER_TYPE(pt_iterator)\
    ((pt_iterator)->_t_containertype)
#define _GET_SLIST_ITERATOR_TYPE(pt_iterator)\
    ((pt_iterator)->_t_iteratortype)
/* avl_tree iterator handler */
#define _GET_AVL_TREE_COREPOS(pt_iterator)\
    ((pt_iterator)->_t_pos._t_treepos._pc_corepos)
#define _GET_AVL_TREE(pt_iterator)\
    ((avl_tree_t*)((pt_iterator)->_t_pos._t_treepos._pt_tree))
#define _GET_AVL_TREE_POINTER(pt_iterator)\
    ((pt_iterator)->_t_pos._t_treepos._pt_tree)
/* rb_tree iterator handler */
#define _GET_RB_TREE_COREPOS(pt_iterator)\
    ((pt_iterator)->_t_pos._t_treepos._pc_corepos)
#define _GET_RB_TREE(pt_iterator)\
    ((rb_tree_t*)((pt_iterator)->_t_pos._t_treepos._pt_tree))
#define _GET_RB_TREE_POINTER(pt_iterator)\
    ((pt_iterator)->_t_pos._t_treepos._pt_tree)
/* set iterator handler */
#define _GET_SET_CONTAINER(pt_iterator)\
    ((set_t*)((pt_iterator)->_pt_container))
#define _GET_SET_CONTAINER_TYPE(pt_iterator)\
    ((pt_iterator)->_t_containertype)
#define _GET_SET_ITERATOR_TYPE(pt_iterator)\
    ((pt_iterator)->_t_iteratortype)
/* multiset iterator handler */
#define _GET_MULTISET_CONTAINER(pt_iterator)\
    ((multiset_t*)((pt_iterator)->_pt_container))
#define _GET_MULTISET_CONTAINER_TYPE(pt_iterator)\
    ((pt_iterator)->_t_containertype)
#define _GET_MULTISET_ITERATOR_TYPE(pt_iterator)\
    ((pt_iterator)->_t_iteratortype)
/* map iterator handler */
#define _GET_MAP_CONTAINER(pt_iterator)\
    ((map_t*)((pt_iterator)->_pt_container))
#define _GET_MAP_CONTAINER_TYPE(pt_iterator)\
    ((pt_iterator)->_t_containertype)
#define _GET_MAP_ITERATOR_TYPE(pt_iterator)\
    ((pt_iterator)->_t_iteratortype)
/* multimap iterator handler */
#define _GET_MULTIMAP_CONTAINER(pt_iterator)\
    ((multimap_t*)((pt_iterator)->_pt_container))
#define _GET_MULTIMAP_CONTAINER_TYPE(pt_iterator)\
    ((pt_iterator)->_t_containertype)
#define _GET_MULTIMAP_ITERATOR_TYPE(pt_iterator)\
    ((pt_iterator)->_t_iteratortype)
/* hashtable iterator handler */
#define _GET_HASHTABLE_BUCKETPOS(pt_iterator)\
    ((pt_iterator)->_t_pos._t_hashpos._pc_bucketpos)
#define _GET_HASHTABLE_COREPOS(pt_iterator)\
    ((pt_iterator)->_t_pos._t_hashpos._pc_corepos)
#define _GET_HASHTABLE(pt_iterator)\
    ((hashtable_t*)((pt_iterator)->_t_pos._t_hashpos._pt_hashtable))
#define _GET_HASHTABLE_POINTER(pt_iterator)\
    ((pt_iterator)->_t_pos._t_hashpos._pt_hashtable)
/* hash_set iterator handler */
#define _GET_HASH_SET_CONTAINER(pt_iterator)\
    ((hash_set_t*)((pt_iterator)->_pt_container))
#define _GET_HASH_SET_CONTAINER_TYPE(pt_iterator)\
    ((pt_iterator)->_t_containertype)
#define _GET_HASH_SET_ITERATOR_TYPE(pt_iterator)\
    ((pt_iterator)->_t_iteratortype)
/* hash_multiset iterator handler */
#define _GET_HASH_MULTISET_CONTAINER(pt_iterator)\
    ((hash_multiset_t*)((pt_iterator)->_pt_container))
#define _GET_HASH_MULTISET_CONTAINER_TYPE(pt_iterator)\
    ((pt_iterator)->_t_containertype)
#define _GET_HASH_MULTISET_ITERATOR_TYPE(pt_iterator)\
    ((pt_iterator)->_t_iteratortype)
/* hash_map iterator handler */
#define _GET_HASH_MAP_CONTAINER(pt_iterator)\
    ((hash_map_t*)((pt_iterator)->_pt_container))
#define _GET_HASH_MAP_CONTAINER_TYPE(pt_iterator)\
    ((pt_iterator)->_t_containertype)
#define _GET_HASH_MAP_ITERATOR_TYPE(pt_iterator)\
    ((pt_iterator)->_t_iteratortype)
/* hash_multimap iterator handler */
#define _GET_HASH_MULTIMAP_CONTAINER(pt_iterator)\
    ((hash_multimap_t*)((pt_iterator)->_pt_container))
#define _GET_HASH_MULTIMAP_CONTAINER_TYPE(pt_iterator)\
    ((pt_iterator)->_t_containertype)
#define _GET_HASH_MULTIMAP_ITERATOR_TYPE(pt_iterator)\
    ((pt_iterator)->_t_iteratortype)
/* basic_string iterator handler */
#define _GET_BASIC_STRING_COREPOS(pt_iterator)\
    ((pt_iterator)->_t_pos._pc_corepos)
#define _GET_BASIC_STRING_CONTAINER(pt_iterator)\
    ((basic_string_t*)((pt_iterator)->_pt_container))
#define _GET_BASIC_STRING_CONTAINER_TYPE(pt_iterator)\
    ((pt_iterator)->_t_containertype)
#define _GET_BASIC_STRING_ITERATOR_TYPE(pt_iterator)\
    ((pt_iterator)->_t_iteratortype)
/* for all container iterator */
#define _GET_CONTAINER(pt_iterator)\
    ((pt_iterator)->_pt_container)
#define _GET_CONTAINER_TYPE(pt_iterator)\
    ((pt_iterator)->_t_containertype)
#define _GET_ITERATOR_TYPE(pt_iterator)\
    ((pt_iterator)->_t_iteratortype)

#define _STRING_CONTAINER        _BASIC_STRING_CONTAINER

/** data type declaration and struct, union, enum section **/
/* container type */
typedef enum _tagcontainertype
{
    _VECTOR_CONTAINER,
    _LIST_CONTAINER,
    _DEQUE_CONTAINER,
    _SLIST_CONTAINER,
    _MAP_CONTAINER,
    _MULTIMAP_CONTAINER,
    _SET_CONTAINER,
    _MULTISET_CONTAINER,
    _HASH_SET_CONTAINER,
    _HASH_MULTISET_CONTAINER,
    _HASH_MAP_CONTAINER,
    _HASH_MULTIMAP_CONTAINER,
    _BASIC_STRING_CONTAINER
}containertype_t;

/* iterator type */
typedef enum _tagiteratortype
{
    _INPUT_ITERATOR,
    _OUTPUT_ITERATOR,
    _FORWARD_ITERATOR,
    _BIDIRECTIONAL_ITERATOR,
    _RANDOM_ACCESS_ITERATOR
}iteratortype_t;

/* cstl iterator */
typedef struct _tagiterator
{
    /* flexibility for all containter */
    union 
    {
        char*       _pc_corepos;    /* for vector list e.g. */
        struct 
        {                    /* for deque */
            char*   _pc_corepos;
            char*   _pc_first;
            char*   _pc_afterlast;  /* the node after the last node */
            char**  _ppc_mappos;    /* point to the map */
        }_t_dequepos;
        struct
        {                    /* for avl tree or rb tree */
            char*   _pc_corepos;
            void*   _pt_tree;       /* point to the avl tree or rb tree*/
        }_t_treepos;
        struct               /* for hash table */
        {
            char*   _pc_corepos;
            char*   _pc_bucketpos;   /* pointer to vector bucket position */
            void*   _pt_hashtable;   /* point to hash node */
        }_t_hashpos;
    }_t_pos;
    void*           _pt_container;
    containertype_t _t_containertype;
    iteratortype_t  _t_iteratortype;
}iterator_t;

/* declaration five iterator type */
typedef iterator_t                  input_iterator_t;
typedef iterator_t                  output_iterator_t;
typedef input_iterator_t            forward_iterator_t;
typedef forward_iterator_t          bidirectional_iterator_t;
typedef bidirectional_iterator_t    random_access_iterator_t;
/* declaration four iterator adapters */
typedef iterator_t                  reverse_iterator_t;
typedef output_iterator_t           insert_iterator_t;
typedef input_iterator_t            istream_iterator_t;
typedef output_iterator_t           ostream_iterator_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/* the handler of iterator */
/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: iterator_copy
 *        Parameters: modify) pt_iterator: iterator_t*
 *                            the iterator pointer for assign.
 *                    in) t_iteratorsrc: iterator_t
 *                            the source iterator
 *           Returns: void
 *       Description: copy the iterator for sepcify value.
 *
 * ----------------------------------------------------------------------------
 */
extern void iterator_copy(iterator_t* pt_iterator, iterator_t t_iteratorsrc);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: iterator_assign
 *        Parameters: modify) pt_iterator: iterator_t*
 *                            the iterator pointer for assign.
 *                    in) t_iteratorsrc: iterator_t
 *                            the source iterator
 *           Returns: void
 *       Description: assign the iterator for sepcify value.
 *
 * ----------------------------------------------------------------------------
 */
extern void iterator_assign(iterator_t* pt_iterator, iterator_t t_iteratorsrc);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: iterator_get_value
 *        Parameters: in) cpt_iterator: const iterator_t*
 *                            the iterator pointer for getting value.
 *                    modify)pv_value: void*
 *                            the value pointer.
 *           Returns: void
 *       Description: get the value of current iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern void iterator_get_value(const iterator_t* cpt_iterator, void* pv_value);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: iterator_set_value
 *        Parameters: in) cpt_iterator: const iterator_t*
 *                            the iterator pointer for setting value.
 *                    in)cpv_value: const void*
 *                            the value pointer.
 *           Returns: void
 *       Description: set the value of current iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern void iterator_set_value(
    const iterator_t* cpt_iterator, const void* cpv_value);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: iterator_get_pointer
 *        Parameters: in) cpt_iterator: const iterator_t*
 *                            the iterator pointer for getting pointer.
 *           Returns: const void*
 *                            the container pointer.
 *       Description: get the pointer of current iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern const void* iterator_get_pointer(const iterator_t* cpt_iterator);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: iterator_next
 *        Parameters: in) pt_iterator: iterator_t*
 *                            the iterator pointer for getting pointer.
 *           Returns: void
 *       Description: to the next position of current iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern void iterator_next(iterator_t* pt_iterator);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: iterator_equal
 *        Parameters: in) cpt_iterator: const iterator_t*
 *                            the iterator pointer.
 *                    in) t_iterator: iterator_t
 *                            iterator.
 *           Returns: bool_t
 *       Description: if the two iterator is equal.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t iterator_equal(
    const iterator_t* cpt_iterator, iterator_t t_iterator);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: iterator_prev
 *        Parameters: in) pt_iterator: iterator_t*
 *                            the iterator pointer for getting pointer.
 *           Returns: void
 *       Description: to the previous position of current iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern void iterator_prev(iterator_t* pt_iterator);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: iterator_at
 *        Parameters: in) cpt_iterator: const iterator_t*
 *                            the iterator pointer for getting value.
 *                    in) un_index: unsigned int
 *                            the index of iterator.
 *           Returns: void
 *       Description: get the value of current iterator with index n.
 *
 * ----------------------------------------------------------------------------
 */
extern void* iterator_at(const iterator_t* cpt_iterator, unsigned int un_index);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: iterator_next_n
 *        Parameters: in) pt_iterator: iterator_t*
 *                            the iterator pointer for getting pointer.
 *                    in) n_step: int
 *                            the step of next.
 *           Returns: void
 *       Description: to the next n position of current iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern void iterator_next_n(iterator_t* pt_iterator, int n_step);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: iterator_prev_n
 *        Parameters: in) pt_iterator: iterator_t*
 *                            the iterator pointer for getting pointer.
 *                    in) n_step: int
 *                            the step of previous.
 *           Returns: void
 *       Description: to the previous n position of current iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern void iterator_prev_n(iterator_t* pt_iterator, int n_step);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: iterator_minus
 *        Parameters: in) cpt_iterator: const iterator_t*
 *                            the iterator pointer for minu.
 *                    in) t_iteratorsrc: iterator_t
 *                            the source iterator
 *           Returns: int
 *                            the distance of two iterator.
 *       Description: compute the distance of two iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern int iterator_minus(
    const iterator_t* cpt_iterator, iterator_t t_iterator);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: iterator_less
 *        Parameters: in) cpt_iterator: const iterator_t*
 *                            the iterator pointer for minu.
 *                    in) t_iteratorsrc: iterator_t
 *                            the source iterator
 *           Returns: bool_t
 *                            if the first iterator less then the second.
 *       Description: test if the first iterator less then the second.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t iterator_less(
    const iterator_t* cpt_iterator, iterator_t t_iterator);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: iterator_less_equal
 *        Parameters: in) cpt_iterator: const iterator_t*
 *                            the iterator pointer for minu.
 *                    in) t_iteratorsrc: iterator_t
 *                            the source iterator
 *           Returns: bool_t
 *                            if the first iterator less equal then the second.
 *       Description: test if the first iterator less equal then the second.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t iterator_less_equal(
    const iterator_t* cpt_iterator, iterator_t t_iterator);

/* the iterator auxilary function */
/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: iterator_advance
 *        Parameters: in) pt_iterator: iterator_t*
 *                            the iterator pointer for getting pointer.
 *                    in) n_step: int
 *                            the step of next.
 *           Returns: void
 *       Description: to the next n position of current iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern void iterator_advance(iterator_t* pt_iterator, int n_step);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: iterator_distance
 *        Parameters: in) t_iterator: iterator_t
 *                            the first iterator for distance.
 *                    in) t_iteratorsrc: iterator_t
 *                            the second iterator for distance.
 *           Returns: int
 *                            the distance of two iterator.
 *       Description: compute the distance of two iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern int iterator_distance(
    iterator_t t_iteratorfirst, iterator_t t_iteratorsecond);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_ITERATOR_H */
/** eof **/

