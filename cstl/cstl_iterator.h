/*
 *  The user interface of iterator.
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

#ifndef _CSTL_ITERATOR_H_
#define _CSTL_ITERATOR_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/* vector iterator handler */
#define _GET_VECTOR_COREPOS(t_iter)\
    ((t_iter)._t_pos._pby_corepos)
#define _GET_VECTOR_CONTAINER(t_iter)\
    ((vector_t*)((t_iter)._pt_container))
#define _GET_VECTOR_CONTAINER_TYPE(t_iter)\
    ((t_iter)._t_containertype)
#define _GET_VECTOR_ITERATOR_TYPE(t_iter)\
    ((t_iter)._t_iteratortype)
/* list iterator handler */
#define _GET_LIST_COREPOS(t_iter)\
    ((t_iter)._t_pos._pby_corepos)
#define _GET_LIST_CONTAINER(t_iter)\
    ((list_t*)((t_iter)._pt_container))
#define _GET_LIST_CONTAINER_TYPE(t_iter)\
    ((t_iter)._t_containertype)
#define _GET_LIST_ITERATOR_TYPE(t_iter)\
    ((t_iter)._t_iteratortype)
/* deque iterator handler */
#define _GET_DEQUE_MAP_POINTER(t_iter)\
    ((t_iter)._t_pos._t_dequepos._ppby_mappos)
#define _GET_DEQUE_FIRST_POS(t_iter)\
    ((t_iter)._t_pos._t_dequepos._pby_first)
#define _GET_DEQUE_AFTERLAST_POS(t_iter)\
    ((t_iter)._t_pos._t_dequepos._pby_afterlast)
#define _GET_DEQUE_COREPOS(t_iter)\
    ((t_iter)._t_pos._t_dequepos._pby_corepos)
#define _GET_DEQUE_CONTAINER(t_iter)\
    ((deque_t*)((t_iter)._pt_container))
#define _GET_DEQUE_CONTAINER_TYPE(t_iter)\
    ((t_iter)._t_containertype)
#define _GET_DEQUE_ITERATOR_TYPE(t_iter)\
    ((t_iter)._t_iteratortype)
/* slist iterator handler */
#define _GET_SLIST_COREPOS(t_iter)\
    ((t_iter)._t_pos._pby_corepos)
#define _GET_SLIST_CONTAINER(t_iter)\
    ((slist_t*)((t_iter)._pt_container))
#define _GET_SLIST_CONTAINER_TYPE(t_iter)\
    ((t_iter)._t_containertype)
#define _GET_SLIST_ITERATOR_TYPE(t_iter)\
    ((t_iter)._t_iteratortype)
/* avl_tree iterator handler */
#define _GET_AVL_TREE_COREPOS(t_iter)\
    ((t_iter)._t_pos._t_treepos._pc_corepos)
#define _GET_AVL_TREE(t_iter)\
    ((_avl_tree_t*)((t_iter)._t_pos._t_treepos._pt_tree))
#define _GET_AVL_TREE_POINTER(t_iter)\
    ((t_iter)._t_pos._t_treepos._pt_tree)
/* rb_tree iterator handler */
#define _GET_RB_TREE_COREPOS(t_iter)\
    ((t_iter)._t_pos._t_treepos._pc_corepos)
#define _GET_RB_TREE(t_iter)\
    ((_rb_tree_t*)((t_iter)._t_pos._t_treepos._pt_tree))
#define _GET_RB_TREE_POINTER(t_iter)\
    ((t_iter)._t_pos._t_treepos._pt_tree)
/* set iterator handler */
#define _GET_SET_CONTAINER(t_iter)\
    ((set_t*)((t_iter)._pt_container))
#define _GET_SET_CONTAINER_TYPE(t_iter)\
    ((t_iter)._t_containertype)
#define _GET_SET_ITERATOR_TYPE(t_iter)\
    ((t_iter)._t_iteratortype)
/* multiset iterator handler */
#define _GET_MULTISET_CONTAINER(t_iter)\
    ((multiset_t*)((t_iter)._pt_container))
#define _GET_MULTISET_CONTAINER_TYPE(t_iter)\
    ((t_iter)._t_containertype)
#define _GET_MULTISET_ITERATOR_TYPE(t_iter)\
    ((t_iter)._t_iteratortype)
/* map iterator handler */
#define _GET_MAP_CONTAINER(t_iter)\
    ((map_t*)((t_iter)._pt_container))
#define _GET_MAP_CONTAINER_TYPE(t_iter)\
    ((t_iter)._t_containertype)
#define _GET_MAP_ITERATOR_TYPE(t_iter)\
    ((t_iter)._t_iteratortype)
/* multimap iterator handler */
#define _GET_MULTIMAP_CONTAINER(t_iter)\
    ((multimap_t*)((t_iter)._pt_container))
#define _GET_MULTIMAP_CONTAINER_TYPE(t_iter)\
    ((t_iter)._t_containertype)
#define _GET_MULTIMAP_ITERATOR_TYPE(t_iter)\
    ((t_iter)._t_iteratortype)
/* hashtable iterator handler */
#define _GET_HASHTABLE_BUCKETPOS(t_iter)\
    ((t_iter)._t_pos._t_hashpos._pc_bucketpos)
#define _GET_HASHTABLE_COREPOS(t_iter)\
    ((t_iter)._t_pos._t_hashpos._pc_corepos)
#define _GET_HASHTABLE(t_iter)\
    ((hashtable_t*)((t_iter)._t_pos._t_hashpos._pt_hashtable))
#define _GET_HASHTABLE_POINTER(t_iter)\
    ((t_iter)._t_pos._t_hashpos._pt_hashtable)
/* hash_set iterator handler */
#define _GET_HASH_SET_CONTAINER(t_iter)\
    ((hash_set_t*)((t_iter)._pt_container))
#define _GET_HASH_SET_CONTAINER_TYPE(t_iter)\
    ((t_iter)._t_containertype)
#define _GET_HASH_SET_ITERATOR_TYPE(t_iter)\
    ((t_iter)._t_iteratortype)
/* hash_multiset iterator handler */
#define _GET_HASH_MULTISET_CONTAINER(t_iter)\
    ((hash_multiset_t*)((t_iter)._pt_container))
#define _GET_HASH_MULTISET_CONTAINER_TYPE(t_iter)\
    ((t_iter)._t_containertype)
#define _GET_HASH_MULTISET_ITERATOR_TYPE(t_iter)\
    ((t_iter)._t_iteratortype)
/* hash_map iterator handler */
#define _GET_HASH_MAP_CONTAINER(t_iter)\
    ((hash_map_t*)((t_iter)._pt_container))
#define _GET_HASH_MAP_CONTAINER_TYPE(t_iter)\
    ((t_iter)._t_containertype)
#define _GET_HASH_MAP_ITERATOR_TYPE(t_iter)\
    ((t_iter)._t_iteratortype)
/* hash_multimap iterator handler */
#define _GET_HASH_MULTIMAP_CONTAINER(t_iter)\
    ((hash_multimap_t*)((t_iter)._pt_container))
#define _GET_HASH_MULTIMAP_CONTAINER_TYPE(t_iter)\
    ((t_iter)._t_containertype)
#define _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_iter)\
    ((t_iter)._t_iteratortype)
/* basic_string iterator handler */
#define _GET_BASIC_STRING_COREPOS(t_iter)\
    ((t_iter)._t_pos._pby_corepos)
#define _GET_BASIC_STRING_CONTAINER(t_iter)\
    ((basic_string_t*)((t_iter)._pt_container))
#define _GET_BASIC_STRING_CONTAINER_TYPE(t_iter)\
    ((t_iter)._t_containertype)
#define _GET_BASIC_STRING_ITERATOR_TYPE(t_iter)\
    ((t_iter)._t_iteratortype)
/* for all container iterator */
#define _GET_CONTAINER(t_iter)\
    ((t_iter)._pt_container)
#define _GET_CONTAINER_TYPE(t_iter)\
    ((t_iter)._t_containertype)
#define _GET_ITERATOR_TYPE(t_iter)\
    ((t_iter)._t_iteratortype)

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
        _byte_t*      _pby_corepos;    /* for vector list e.g. */
        struct 
        {                    /* for deque */
            _byte_t*  _pby_corepos;
            _byte_t*  _pby_first;
            _byte_t*  _pby_afterlast;  /* the node after the last node */
            _byte_t** _ppby_mappos;    /* point to the map */
        }_t_dequepos;
        struct
        {                    /* for avl tree or rb tree */
            _byte_t*  _pc_corepos;
            void*     _pt_tree;       /* point to the avl tree or rb tree*/
        }_t_treepos;
        struct               /* for hash table */
        {
            char*     _pc_corepos;
            char*     _pc_bucketpos;   /* pointer to vector bucket position */
            void*     _pt_hashtable;   /* point to hash node */
        }_t_hashpos;
    }_t_pos;
    void*             _pt_container;
    containertype_t   _t_containertype;
    iteratortype_t    _t_iteratortype;
}iterator_t;

/* range type */
typedef struct _tagrange
{
    iterator_t it_begin;
    iterator_t it_end;
}range_t;


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
 * Get and set value.
 */
extern void iterator_get_value(iterator_t t_iter, void* pv_value);
extern void iterator_set_value(iterator_t t_iter, const void* cpv_value);
extern const void* iterator_get_pointer(iterator_t t_iter);

/*
 * Move iterator.
 */
extern iterator_t iterator_next(iterator_t t_iter);
extern iterator_t iterator_prev(iterator_t t_iter);
extern iterator_t iterator_next_n(iterator_t t_iter, int n_step);
extern iterator_t iterator_prev_n(iterator_t t_iter, int n_step);

/*
 * Relationship operator functions.
 */
extern bool_t iterator_equal(iterator_t t_iterfirst, iterator_t t_itersecond);
extern bool_t iterator_not_equal(iterator_t t_iterfirst, iterator_t t_itersecond);
extern bool_t iterator_less(iterator_t t_iterfirst, iterator_t t_itersecond);
extern bool_t iterator_less_equal(iterator_t t_iterfirst, iterator_t t_itersecond);
extern bool_t iterator_greater(iterator_t t_iterfirst, iterator_t t_itersecond);
extern bool_t iterator_greater_equal(iterator_t t_iterfirst, iterator_t t_itersecond);

/*
 * Element random access.
 */
extern void* iterator_at(iterator_t t_iter, int n_index);


/*
 * Distance.
 */
extern int iterator_minus(iterator_t t_iterfirst, iterator_t t_itersecond);

/* the iterator auxilary function */
/*
 * Advance and distance.
 */
extern iterator_t iterator_advance(iterator_t t_iter, int n_step);
extern int iterator_distance(iterator_t t_iterfirst, iterator_t t_itersecond);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_ITERATOR_H_ */
/** eof **/

