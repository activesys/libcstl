/*
 *  The implement of list module.
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

/** include section **/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include <cstl/cstl_alloc.h>
#include <cstl/cstl_types.h>
#include <cstl/cstl_iterator.h>
#include <cstl/cstl_iterator_private.h>
#include <cstl/cfunctional.h>

#include <cstl/cstl_list_iterator.h>
#include <cstl/cstl_list_private.h>
#include <cstl/cstl_list.h>

#include <cstl/cstring.h>

/** local constant declaration and local macro section **/
#define _LIST_NODE_SIZE(typesize)\
    ((typesize) + sizeof(listnode_t) - 1)

/* macros for type informations */
#define _GET_LIST_TYPE_SIZE(pt_list)\
    ((pt_list)->_t_typeinfo._pt_type->_t_typesize)
#define _GET_LIST_TYPE_NAME(pt_list)\
    ((pt_list)->_t_typeinfo._sz_typename)
#define _GET_LIST_TYPE_BASENAME(pt_list)\
    ((pt_list)->_t_typeinfo._pt_type->_sz_typename)
#define _GET_LIST_TYPE_INIT_FUNCTION(pt_list)\
    ((pt_list)->_t_typeinfo._pt_type->_t_typeinit)
#define _GET_LIST_TYPE_COPY_FUNCTION(pt_list)\
    ((pt_list)->_t_typeinfo._pt_type->_t_typecopy)
#define _GET_LIST_TYPE_LESS_FUNCTION(pt_list)\
    ((pt_list)->_t_typeinfo._pt_type->_t_typeless)
#define _GET_LIST_TYPE_DESTROY_FUNCTION(pt_list)\
    ((pt_list)->_t_typeinfo._pt_type->_t_typedestroy)
#define _GET_LIST_TYPE_STYLE(pt_list)\
    ((pt_list)->_t_typeinfo._t_style)

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/
#ifndef NDEBUG
/*
 * Assert support.
 */
static bool_t _list_iterator_belong_to_list(
    const list_t* cpt_list, list_iterator_t t_iter);
static bool_t _list_same_list_iterator_type(
    const list_t* cpt_list, list_iterator_t t_iter);
#endif /* NDEBUG */
static bool_t _list_same_type(
    const list_t* cpt_listfirst, const list_t* cpt_listsecond);

static void _list_get_varg_value_auxiliary(
    list_t* pt_list, va_list val_elemlist, listnode_t* pt_node);
static void _list_destroy_varg_value_auxiliary(list_t* pt_list, listnode_t* pt_node);
static void _list_init_node_auxiliary(list_t* pt_list, listnode_t* pt_node);

/*
 * Transfer the range [t_begin, t_end) to position.
 */
static void _transfer(
    list_iterator_t t_pos, list_iterator_t t_begin, list_iterator_t t_end);

/*
 * Sort the range (t_beforefirstpos, t_afterlastpos) use the quick sort algorithm.
 */
static void _quick_sort(
    list_iterator_t t_beforefirstpos, list_iterator_t t_afterlastpos,
    binary_function_t t_binary_op);

/*
 * Swap the two node content and don't change the pointer.
 */
static void _swap_node(listnode_t** ppt_first, listnode_t** ppt_second);

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/* list iterator function */
list_iterator_t create_list_iterator(void)
{
    list_iterator_t t_newiterator;

    _GET_LIST_COREPOS(t_newiterator) = NULL;
    _GET_CONTAINER(t_newiterator) = NULL;
    _GET_LIST_CONTAINER_TYPE(t_newiterator) = _LIST_CONTAINER;
    _GET_LIST_ITERATOR_TYPE(t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

void _list_iterator_get_value(list_iterator_t t_iter, void* pv_value)
{
    assert(pv_value != NULL);
    assert(_list_iterator_belong_to_list(_GET_LIST_CONTAINER(t_iter), t_iter));
    assert(!iterator_equal(t_iter, list_end(_GET_LIST_CONTAINER(t_iter))));

    /* char* */
    if(strncmp(_GET_LIST_TYPE_BASENAME(_GET_LIST_CONTAINER(t_iter)),
        _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        *(char**)pv_value = (char*)string_c_str(
            (string_t*)((listnode_t*)_GET_LIST_COREPOS(t_iter))->_pc_data);
    }
    else
    {
        bool_t t_result = _GET_LIST_TYPE_SIZE(_GET_LIST_CONTAINER(t_iter));
        _GET_LIST_TYPE_COPY_FUNCTION(_GET_LIST_CONTAINER(t_iter))(
            pv_value, ((listnode_t*)_GET_LIST_COREPOS(t_iter))->_pc_data, &t_result);
        assert(t_result);
    }
}

void _list_iterator_set_value(list_iterator_t t_iter, const void* cpv_value)
{
    assert(cpv_value != NULL);
    assert(_list_iterator_belong_to_list(_GET_LIST_CONTAINER(t_iter), t_iter));
    assert(!iterator_equal(t_iter, list_end(_GET_LIST_CONTAINER(t_iter))));

    /* char* */
    if(strncmp(_GET_LIST_TYPE_BASENAME(_GET_LIST_CONTAINER(t_iter)),
        _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        string_assign_cstr(
            (string_t*)((listnode_t*)_GET_LIST_COREPOS(t_iter))->_pc_data, (char*)cpv_value);
    }
    else
    {
        bool_t t_result = _GET_LIST_TYPE_SIZE(_GET_LIST_CONTAINER(t_iter));
        _GET_LIST_TYPE_COPY_FUNCTION(_GET_LIST_CONTAINER(t_iter))(
            ((listnode_t*)_GET_LIST_COREPOS(t_iter))->_pc_data, cpv_value, &t_result);
        assert(t_result);
    }
}

const void* _list_iterator_get_pointer(list_iterator_t t_iter)
{
    assert(_list_iterator_belong_to_list(_GET_LIST_CONTAINER(t_iter), t_iter));
    assert(!iterator_equal(t_iter, list_end(_GET_LIST_CONTAINER(t_iter))));

    /* char* */
    if(strncmp(_GET_LIST_TYPE_BASENAME(_GET_LIST_CONTAINER(t_iter)),
        _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        return string_c_str((string_t*)((listnode_t*)_GET_LIST_COREPOS(t_iter))->_pc_data);
    }
    else
    {
        return ((listnode_t*)_GET_LIST_COREPOS(t_iter))->_pc_data;
    }
}

list_iterator_t _list_iterator_next(list_iterator_t t_iter)
{
    assert(_list_iterator_belong_to_list(_GET_LIST_CONTAINER(t_iter), t_iter));
    assert(!iterator_equal(t_iter, list_end(_GET_LIST_CONTAINER(t_iter))));

    _GET_LIST_COREPOS(t_iter) = (char*)(((listnode_t*)_GET_LIST_COREPOS(t_iter))->_pt_next);

    return t_iter;
}

list_iterator_t _list_iterator_prev(list_iterator_t t_iter)
{
    assert(_list_iterator_belong_to_list(_GET_LIST_CONTAINER(t_iter), t_iter));

    _GET_LIST_COREPOS(t_iter) = (char*)(((listnode_t*)_GET_LIST_COREPOS(t_iter))->_pt_prev);

    return t_iter;
}

bool_t _list_iterator_equal(
    list_iterator_t t_iterfirst, list_iterator_t t_itersecond)
{
    assert(_iterator_same_type(t_iterfirst, t_itersecond));
    assert(_GET_LIST_CONTAINER(t_iterfirst) == _GET_LIST_CONTAINER(t_itersecond));
    assert(_list_iterator_belong_to_list(_GET_LIST_CONTAINER(t_iterfirst), t_iterfirst));
    assert(_list_iterator_belong_to_list(_GET_LIST_CONTAINER(t_itersecond), t_itersecond));

    if(_GET_LIST_COREPOS(t_iterfirst) == _GET_LIST_COREPOS(t_itersecond))
    {
        return true;
    }
    else
    {
        return false;
    }
}

int _list_iterator_distance(
    list_iterator_t t_iterfirst, list_iterator_t t_itersecond)
{
    listnode_t* pt_node = NULL;    /* the iterate pointer */
    int         n_distance = 0;    /* the distance of two iterator */

    /* if the end > begin then distance is greater zero */
    if(_list_iterator_before(t_iterfirst, t_itersecond))
    {
        for(pt_node = (listnode_t*)_GET_LIST_COREPOS(t_iterfirst);
            pt_node != (listnode_t*)_GET_LIST_COREPOS(t_itersecond);
            pt_node = pt_node->_pt_next)
        {
            n_distance++;
        }
        return n_distance;
    }
    else if(_list_iterator_before(t_itersecond, t_iterfirst))
    {
        for(pt_node = (listnode_t*)_GET_LIST_COREPOS(t_itersecond);
            pt_node != (listnode_t*)_GET_LIST_COREPOS(t_iterfirst);
            pt_node = pt_node->_pt_next)
        {
            n_distance++;
        }
        return -n_distance;
    }
    else
    {
        return 0;
    }
}

bool_t _list_iterator_before(
    list_iterator_t t_iterfirst, list_iterator_t t_itersecond)
{
    listnode_t* pt_node = NULL; /* current list node pointer */

    assert(_iterator_same_type(t_iterfirst, t_itersecond));
    assert(_GET_LIST_CONTAINER(t_iterfirst) == _GET_LIST_CONTAINER(t_itersecond));
    assert(_list_iterator_belong_to_list(_GET_LIST_CONTAINER(t_iterfirst), t_iterfirst));
    assert(_list_iterator_belong_to_list(_GET_LIST_CONTAINER(t_itersecond), t_itersecond));
    assert(_GET_LIST_COREPOS(t_iterfirst) != NULL &&
           _GET_LIST_COREPOS(t_itersecond) != NULL);
    assert(_GET_LIST_CONTAINER(t_iterfirst) != NULL &&
           _GET_LIST_CONTAINER(t_itersecond) != NULL);

    /* if the first node equal to second node is false */
    if(_GET_LIST_COREPOS(t_iterfirst) == _GET_LIST_COREPOS(t_itersecond))
    {
        return false;
    }

    /* loop from first iterator */
    for(pt_node = (listnode_t*)_GET_LIST_COREPOS(t_iterfirst);
        pt_node != _GET_LIST_CONTAINER(t_iterfirst)->_pt_node;
        pt_node = pt_node->_pt_next)
    {
        /* if meet the second iterator then the first before second */
        if(pt_node == (listnode_t*)_GET_LIST_COREPOS(t_itersecond))
        {
            return true;
        }
    }

    /* if second iterator is end the return true */
    if((listnode_t*)_GET_LIST_COREPOS(t_itersecond) ==
        _GET_LIST_CONTAINER(t_itersecond)->_pt_node)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/* list private function */
list_t* _create_list(const char* s_typename)
{
    list_t*     pt_newlist = NULL;

    if((pt_newlist = (list_t*)malloc(sizeof(list_t))) == NULL)
    {
        return NULL;
    }

    if(!_create_list_auxiliary(pt_newlist, s_typename))
    {
        free(pt_newlist);
        return NULL;
    }

    return pt_newlist;
}

bool_t _create_list_auxiliary(list_t* pt_list, const char* s_typename)
{
    assert(pt_list != NULL && s_typename != NULL);

    _type_get_type(&pt_list->_t_typeinfo, s_typename);
    if(pt_list->_t_typeinfo._t_style == _TYPE_INVALID)
    {
        return false;
    }

    pt_list->_pt_node = NULL;

    return true;
}

/* list function */
void _list_init_elem_varg(list_t* pt_list, size_t t_count, va_list val_elemlist)
{
    listnode_t* pt_varg = NULL;

    assert(pt_list != NULL && pt_list->_pt_node == NULL);

    /* allocate the end element */
    /*
     * _pt_node --+
     *            V
     *     +-->+------+<--+
     *     +---| prev |   |
     *         +------+   |
     *         | next |---+
     *         +------+
     *         | data |
     *         +------+
     */
    allocate_init(&pt_list->_t_allocater);
    pt_list->_pt_node = allocate(&pt_list->_t_allocater,
        _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(pt_list)), 1);
    assert(pt_list->_pt_node != NULL);
    pt_list->_pt_node->_pt_next = pt_list->_pt_node;
    pt_list->_pt_node->_pt_prev = pt_list->_pt_node;

    if(t_count > 0)
    {
        size_t      t_index = 0;
        listnode_t* pt_node = NULL;
        bool_t      t_result = false;

        /* get varg value only once */
        pt_varg = allocate(&pt_list->_t_allocater,
            _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(pt_list)), 1);
        assert(pt_varg != NULL);
        _list_get_varg_value_auxiliary(pt_list, val_elemlist, pt_varg);

        for(t_index = 0; t_index < t_count; ++t_index)
        {
            pt_node = allocate(&pt_list->_t_allocater,
                _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(pt_list)), 1);
            assert(pt_node != NULL);
            _list_init_node_auxiliary(pt_list, pt_node);

            t_result = _GET_LIST_TYPE_SIZE(pt_list);
            _GET_LIST_TYPE_COPY_FUNCTION(pt_list)(
                pt_node->_pc_data, pt_varg->_pc_data, &t_result);
            assert(t_result);

            pt_node->_pt_next = pt_list->_pt_node;
            pt_node->_pt_prev = pt_list->_pt_node->_pt_prev;
            pt_list->_pt_node->_pt_prev->_pt_next = pt_node;
            pt_list->_pt_node->_pt_prev = pt_node;
            pt_node = NULL;
        }

        _list_destroy_varg_value_auxiliary(pt_list, pt_varg);
        deallocate(&pt_list->_t_allocater, pt_varg,
            _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(pt_list)), 1);
    }
}

void _list_init_elem(list_t* pt_list, size_t t_count, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_count);
    _list_init_elem_varg(pt_list, t_count, val_elemlist);
    va_end(val_elemlist);
}

void list_init_n(list_t* pt_list, size_t t_count)
{
    assert(pt_list != NULL && pt_list->_pt_node == NULL);

    /* allocate the end element */
    /*
     * _pt_node --+
     *            V
     *     +-->+------+<--+
     *     +---| prev |   |
     *         +------+   |
     *         | next |---+
     *         +------+
     *         | data |
     *         +------+
     */
    allocate_init(&pt_list->_t_allocater);
    pt_list->_pt_node = allocate(&pt_list->_t_allocater,
        _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(pt_list)), 1);
    assert(pt_list->_pt_node != NULL);
    pt_list->_pt_node->_pt_next = pt_list->_pt_node;
    pt_list->_pt_node->_pt_prev = pt_list->_pt_node;

    if(t_count > 0)
    {
        size_t      t_index = 0;
        listnode_t* pt_node = NULL;

        for(t_index = 0; t_index < t_count; ++t_index)
        {
            pt_node = allocate(&pt_list->_t_allocater,
                _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(pt_list)), 1);
            assert(pt_node != NULL);
            _list_init_node_auxiliary(pt_list, pt_node);

            pt_node->_pt_next = pt_list->_pt_node;
            pt_node->_pt_prev = pt_list->_pt_node->_pt_prev;
            pt_list->_pt_node->_pt_prev->_pt_next = pt_node;
            pt_list->_pt_node->_pt_prev = pt_node;
            pt_node = NULL;
        }
    }
}

void list_init(list_t* pt_list)
{
    list_init_n(pt_list, 0);
}

void _list_destroy_auxiliary(list_t* pt_list)
{
    listnode_t* pt_node = NULL;         /* for destroy element */
    listnode_t* pt_destroynode = NULL;  /* for destroy node itself */
    bool_t      t_result = false;

    assert(pt_list != NULL && pt_list->_pt_node != NULL);

    pt_node = pt_list->_pt_node->_pt_next;
    /* destroy all element and node except the end node */
    while(pt_node != pt_list->_pt_node)
    {
        pt_destroynode = pt_node;
        pt_node = pt_node->_pt_next;
        /* delete the destroy node from the link list */
        pt_node->_pt_prev = pt_destroynode->_pt_prev;
        pt_destroynode->_pt_prev->_pt_next = pt_node;
        /* destroy the node */

        t_result = _GET_LIST_TYPE_SIZE(pt_list);
        _GET_LIST_TYPE_DESTROY_FUNCTION(pt_list)(pt_destroynode->_pc_data, &t_result);
        assert(t_result);
        deallocate(&pt_list->_t_allocater, pt_destroynode,
            _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(pt_list)), 1);
    }
    /* destroy the end node */
    deallocate(&pt_list->_t_allocater, pt_list->_pt_node,
        _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(pt_list)), 1);
    allocate_destroy(&pt_list->_t_allocater);

    pt_list->_pt_node = NULL;
}

void list_destroy(list_t* pt_list)
{
    _list_destroy_auxiliary(pt_list);
    free(pt_list);
}

void list_init_copy(list_t* pt_listdest, const list_t* cpt_listsrc)
{
    list_init_copy_range(pt_listdest, list_begin(cpt_listsrc), list_end(cpt_listsrc));
}

void list_init_copy_range(list_t* pt_list, list_iterator_t t_begin, list_iterator_t t_end)
{
    list_iterator_t t_dest;
    list_iterator_t t_src;
    bool_t          t_result = false;

    assert(pt_list != NULL && pt_list->_pt_node == NULL);
    assert(_list_same_list_iterator_type(pt_list, t_begin));
    assert(iterator_equal(t_begin, t_end) || _list_iterator_before(t_begin, t_end));

    /* 
     * initialize the new list with the list size, compare function,
     * destroy element function of list that t_begin and t_end iterator
     * point to.
     */
    list_init_n(pt_list, iterator_distance(t_begin, t_end));
    /* copy the element from the range [t_begin, t_end) to now list */
    for(t_dest = list_begin(pt_list), t_src = t_begin;
        !iterator_equal(t_dest, list_end(pt_list)) && !iterator_equal(t_src, t_end);
        t_dest = iterator_next(t_dest), t_src = iterator_next(t_src))
    {
        t_result = _GET_LIST_TYPE_SIZE(pt_list);
        _GET_LIST_TYPE_COPY_FUNCTION(pt_list)(
            ((listnode_t*)_GET_LIST_COREPOS(t_dest))->_pc_data,
            ((listnode_t*)_GET_LIST_COREPOS(t_src))->_pc_data, &t_result);
        assert(t_result);
    }
    assert(iterator_equal(t_dest, list_end(pt_list)) && iterator_equal(t_src, t_end));
}

size_t list_size(const list_t* cpt_list)
{
    listnode_t* pt_node = NULL;     /* the current list node */
    size_t      t_listsize = 0;     /* list size */
    assert(cpt_list != NULL && cpt_list->_pt_node != NULL);
    
    for(pt_node = cpt_list->_pt_node->_pt_next;
        pt_node != cpt_list->_pt_node;
        pt_node = pt_node->_pt_next)
    {
        t_listsize++;
    }

    return t_listsize;
}

bool_t list_empty(const list_t* cpt_list)
{
    assert(cpt_list != NULL && cpt_list->_pt_node != NULL);

    if(cpt_list->_pt_node->_pt_next == cpt_list->_pt_node)
    {
        assert(cpt_list->_pt_node->_pt_prev == cpt_list->_pt_node);
        return true;
    }
    else
    {
        return false;
    }
}

size_t list_max_size(const list_t* cpt_list)
{
    assert(cpt_list != NULL);

    return (size_t)(-1) / _GET_LIST_TYPE_SIZE(cpt_list);
}

bool_t list_equal(const list_t* cpt_listfirst, const list_t* cpt_listsecond)
{
    listnode_t* pt_nodefirst = NULL;    /* the firs list node pointer */
    listnode_t* pt_nodesecond = NULL;   /* the second node pointer */
    bool_t      t_less = false;
    bool_t      t_greater = false;

    assert(cpt_listfirst != NULL && cpt_listsecond != NULL);
    assert(cpt_listfirst->_pt_node != NULL && cpt_listsecond->_pt_node != NULL);
    /* test type identification */
    if(!_list_same_type(cpt_listfirst, cpt_listsecond))
    {
        return false;
    }
    /* test size */
    if(list_size(cpt_listfirst) != list_size(cpt_listsecond))
    {
        return false;
    }
    /* test each element */
    for(pt_nodefirst = cpt_listfirst->_pt_node->_pt_next,
        pt_nodesecond = cpt_listsecond->_pt_node->_pt_next;
        pt_nodefirst != cpt_listfirst->_pt_node &&
        pt_nodesecond != cpt_listsecond->_pt_node;
        pt_nodefirst = pt_nodefirst->_pt_next,
        pt_nodesecond = pt_nodesecond->_pt_next)
    {
        t_less = t_greater = _GET_LIST_TYPE_SIZE(cpt_listfirst);
        _GET_LIST_TYPE_LESS_FUNCTION(cpt_listfirst)(
            pt_nodefirst->_pc_data, pt_nodesecond->_pc_data, &t_less);
        _GET_LIST_TYPE_LESS_FUNCTION(cpt_listfirst)(
            pt_nodesecond->_pc_data, pt_nodefirst->_pc_data, &t_greater);
        if(t_less || t_greater)
        {
            return false;
        }
    }
    assert(pt_nodefirst == cpt_listfirst->_pt_node &&
           pt_nodesecond == cpt_listsecond->_pt_node);

    return true;
}

bool_t list_not_equal(const list_t* cpt_listfirst, const list_t* cpt_listsecond)
{
    return !list_equal(cpt_listfirst, cpt_listsecond);
}

bool_t list_less(const list_t* cpt_listfirst, const list_t* cpt_listsecond)
{
    listnode_t* pt_nodefirst = NULL;   /* the node pointer of first list */
    listnode_t* pt_nodesecond = NULL;  /* the node pointer of second list */
    bool_t      t_result = false;

    assert(_list_same_type(cpt_listfirst, cpt_listsecond));

    for(pt_nodefirst = cpt_listfirst->_pt_node->_pt_next,
        pt_nodesecond = cpt_listsecond->_pt_node->_pt_next;
        pt_nodefirst != cpt_listfirst->_pt_node &&
        pt_nodesecond != cpt_listsecond->_pt_node;
        pt_nodefirst = pt_nodefirst->_pt_next,
        pt_nodesecond = pt_nodesecond->_pt_next)
    {
        t_result = _GET_LIST_TYPE_SIZE(cpt_listfirst);
        _GET_LIST_TYPE_LESS_FUNCTION(cpt_listfirst)(
            pt_nodefirst->_pc_data, pt_nodesecond->_pc_data, &t_result);
        if(t_result)
        {
            return true;
        }

        t_result = _GET_LIST_TYPE_SIZE(cpt_listfirst);
        _GET_LIST_TYPE_LESS_FUNCTION(cpt_listfirst)(
            pt_nodesecond->_pc_data, pt_nodefirst->_pc_data, &t_result);
        if(t_result)
        {
            return false;
        }
    }

    return list_size(cpt_listfirst) < list_size(cpt_listsecond) ? true : false;
}

bool_t list_greater(const list_t* cpt_listfirst, const list_t* cpt_listsecond)
{
    return list_less(cpt_listsecond, cpt_listfirst);
}

bool_t list_less_equal(const list_t* cpt_listfirst, const list_t* cpt_listsecond)
{
    return (list_less(cpt_listfirst, cpt_listsecond) ||
            list_equal(cpt_listfirst, cpt_listsecond)) ? true : false;
}

bool_t list_greater_equal(const list_t* cpt_listfirst, const list_t* cpt_listsecond)
{
    return (list_greater(cpt_listfirst, cpt_listsecond) ||
            list_equal(cpt_listfirst, cpt_listsecond)) ? true : false;
}

void list_assign(list_t* pt_listdest, const list_t* cpt_listsrc)
{
    list_assign_range(pt_listdest, list_begin(cpt_listsrc), list_end(cpt_listsrc));
}

void _list_assign_elem(list_t* pt_list, size_t t_count, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_count);
    _list_assign_elem_varg(pt_list, t_count, val_elemlist);
    va_end(val_elemlist);
}

void _list_assign_elem_varg(list_t* pt_list, size_t t_count, va_list val_elemlist)
{
    listnode_t*     pt_varg = NULL;
    list_iterator_t t_iter;
    bool_t          t_result = false;

    assert(pt_list != NULL);

    list_resize(pt_list, t_count);

    /* get varg value */
    pt_varg = allocate(&pt_list->_t_allocater,
        _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(pt_list)), 1);
    assert(pt_varg != NULL);
    _list_get_varg_value_auxiliary(pt_list, val_elemlist, pt_varg);

    /* copy value form varg */
    for(t_iter = list_begin(pt_list);
        !iterator_equal(t_iter, list_end(pt_list));
        t_iter = iterator_next(t_iter))
    {
        t_result = _GET_LIST_TYPE_SIZE(pt_list);
        _GET_LIST_TYPE_COPY_FUNCTION(pt_list)(
            ((listnode_t*)_GET_LIST_COREPOS(t_iter))->_pc_data, pt_varg->_pc_data, &t_result);
        assert(t_result);
    }

    /* destroy varg value */
    _list_destroy_varg_value_auxiliary(pt_list, pt_varg);
    deallocate(&pt_list->_t_allocater, pt_varg,
        _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(pt_list)), 1);
}

void list_assign_range(list_t* pt_list, list_iterator_t t_begin, list_iterator_t t_end)
{
    list_iterator_t t_dest;
    list_iterator_t t_src;
    bool_t          t_result = false;

    assert(_list_same_list_iterator_type(pt_list, t_begin));
    assert(iterator_equal(t_begin, t_end) || _list_iterator_before(t_begin, t_end));

    list_resize(pt_list, iterator_distance(t_begin, t_end));

    /* copy value form varg */
    for(t_dest = list_begin(pt_list), t_src = t_begin;
        !iterator_equal(t_dest, list_end(pt_list)) && !iterator_equal(t_src, t_end);
        t_dest = iterator_next(t_dest), t_src = iterator_next(t_src))
    {
        t_result = _GET_LIST_TYPE_SIZE(pt_list);
        _GET_LIST_TYPE_COPY_FUNCTION(pt_list)(
            ((listnode_t*)_GET_LIST_COREPOS(t_dest))->_pc_data,
            ((listnode_t*)_GET_LIST_COREPOS(t_src))->_pc_data, &t_result);
        assert(t_result);
    }
}

void list_swap(list_t* pt_listfirst, list_t* pt_listsecond)
{
    list_t t_listtmp;   /* the temporary list */

    assert(_list_same_type(pt_listfirst, pt_listsecond));

    t_listtmp = *pt_listfirst;
    *pt_listfirst = *pt_listsecond;
    *pt_listsecond = t_listtmp;
}

void* list_front(const list_t* cpt_list)
{
    assert(cpt_list != NULL && cpt_list->_pt_node != NULL);

    if(list_empty(cpt_list))
    {
        return NULL;
    }
    else if(strncmp(_GET_LIST_TYPE_BASENAME(cpt_list), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        return (char*)string_c_str((string_t*)cpt_list->_pt_node->_pt_next->_pc_data);
    }
    else
    {
        return cpt_list->_pt_node->_pt_next->_pc_data; 
    }
}

void* list_back(const list_t* cpt_list)
{
    assert(cpt_list != NULL && cpt_list->_pt_node != NULL);

    if(list_empty(cpt_list))
    {
        return NULL;
    }
    else if(strncmp(_GET_LIST_TYPE_BASENAME(cpt_list), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        return (char*)string_c_str((string_t*)cpt_list->_pt_node->_pt_prev->_pc_data);
    }
    else
    {
        return cpt_list->_pt_node->_pt_prev->_pc_data;
    }
}

list_iterator_t list_begin(const list_t* cpt_list)
{
    list_iterator_t t_newiterator;  /* new list iterator */

    assert(cpt_list != NULL && cpt_list->_pt_node != NULL);

    t_newiterator = create_list_iterator();
    _GET_LIST_COREPOS(t_newiterator) = (char*)(cpt_list->_pt_node->_pt_next);
    _GET_CONTAINER(t_newiterator) = (list_t*)cpt_list;

    return t_newiterator;
}

list_iterator_t list_end(const list_t* cpt_list)
{
    list_iterator_t t_newiterator;  /* new list iterator */

    assert(cpt_list != NULL && cpt_list->_pt_node != NULL);

    t_newiterator = create_list_iterator();
    _GET_LIST_COREPOS(t_newiterator) = (char*)(cpt_list->_pt_node);
    _GET_CONTAINER(t_newiterator) = (list_t*)cpt_list;

    return t_newiterator;
}

list_reverse_iterator_t list_rbegin(const list_t* cpt_list)
{
    list_reverse_iterator_t t_newiterator;   /* new list reverse iterator */

    assert(cpt_list != NULL && cpt_list->_pt_node != NULL);

    t_newiterator = create_list_iterator();
    _GET_LIST_COREPOS(t_newiterator) = (char*)(cpt_list->_pt_node->_pt_prev);
    _GET_CONTAINER(t_newiterator) = (list_t*)cpt_list;

    return t_newiterator;
}

list_reverse_iterator_t list_rend(const list_t* cpt_list)
{
    list_reverse_iterator_t t_newiterator;  /* new list reverse iterator */

    assert(cpt_list != NULL && cpt_list->_pt_node != NULL);

    t_newiterator = create_list_iterator();
    _GET_LIST_COREPOS(t_newiterator) = (char*)(cpt_list->_pt_node);
    _GET_CONTAINER(t_newiterator) = (list_t*)cpt_list;

    return t_newiterator;
}

list_iterator_t _list_insert_n(
    list_t* pt_list, list_iterator_t t_pos, size_t t_count, ...)
{
    list_iterator_t t_iter;
    va_list val_elemlist;

    va_start(val_elemlist, t_count);
    t_iter = _list_insert_n_varg(pt_list, t_pos, t_count, val_elemlist);
    va_end(val_elemlist);

    return t_iter;
}

list_iterator_t _list_insert_n_varg(
    list_t* pt_list, list_iterator_t t_pos, size_t t_count, va_list val_elemlist)
{
    listnode_t* pt_node = NULL;    /* the insert node */
    size_t      t_index = 0;
    listnode_t* pt_varg = NULL;
    bool_t      t_result = false;

    assert(_list_iterator_belong_to_list(pt_list, t_pos));

    /* get varg value only once */
    pt_varg = allocate(&pt_list->_t_allocater,
        _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(pt_list)), 1);
    assert(pt_varg != NULL);
    _list_get_varg_value_auxiliary(pt_list, val_elemlist, pt_varg);

    for(t_index = 0; t_index < t_count; ++t_index)
    {
        /* allocate the memory for insert node */
        pt_node = allocate(&pt_list->_t_allocater,
            _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(pt_list)), 1);
        assert(pt_node != NULL);
        _list_init_node_auxiliary(pt_list, pt_node);

        /* copy value from varg */
        t_result = _GET_LIST_TYPE_SIZE(pt_list);
        _GET_LIST_TYPE_COPY_FUNCTION(pt_list)(pt_node->_pc_data, pt_varg->_pc_data, &t_result);
        assert(t_result);

        /* insert the element in the position t_pos */
        pt_node->_pt_next = (listnode_t*)_GET_LIST_COREPOS(t_pos);
        pt_node->_pt_prev = ((listnode_t*)_GET_LIST_COREPOS(t_pos))->_pt_prev;
        ((listnode_t*)_GET_LIST_COREPOS(t_pos))->_pt_prev->_pt_next = pt_node;
        ((listnode_t*)_GET_LIST_COREPOS(t_pos))->_pt_prev = pt_node;
        pt_node = NULL;
    }

    /* destroy varg value */
    _list_destroy_varg_value_auxiliary(pt_list, pt_varg);
    deallocate(&pt_list->_t_allocater, pt_varg,
        _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(pt_list)), 1);

    return t_pos;
}

void list_insert_range(
    list_t* pt_list, list_iterator_t t_pos, 
    list_iterator_t t_begin, list_iterator_t t_end)
{
    listnode_t* pt_listbegin = NULL;    /* the begin pointer of copy list */
    listnode_t* pt_listend = NULL;      /* the end pointer of copy list */
    listnode_t* pt_node = NULL;         /* the new allocate node */
    listnode_t* pt_nodeinrange = NULL;  /* the node that in range */
    bool_t      t_result = false;

    assert(_list_iterator_belong_to_list(pt_list, t_pos));
    assert(iterator_equal(t_begin, t_end) || _list_iterator_before(t_begin, t_end));
    assert(_list_same_list_iterator_type(pt_list, t_begin));

    /* allocate the copy list of range [t_begin, t_end) */
    for(pt_nodeinrange = (listnode_t*)_GET_LIST_COREPOS(t_begin);
        pt_nodeinrange != (listnode_t*)_GET_LIST_COREPOS(t_end);
        pt_nodeinrange = pt_nodeinrange->_pt_next)
    {
        pt_node = allocate(&pt_list->_t_allocater,
            _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(pt_list)), 1);
        assert(pt_node != NULL);
        pt_node->_pt_next = pt_node->_pt_prev = NULL;
        _list_init_node_auxiliary(pt_list, pt_node);
        t_result = _GET_LIST_TYPE_SIZE(pt_list);
        _GET_LIST_TYPE_COPY_FUNCTION(pt_list)(
            pt_node->_pc_data, pt_nodeinrange->_pc_data, &t_result);
        assert(t_result);

        if(pt_listbegin == NULL)
        {
            assert(pt_listend == NULL);
            pt_listbegin = pt_listend = pt_node;
        }
        else
        {
            assert(pt_listend != NULL);
            pt_listend->_pt_next = pt_node;
            pt_node->_pt_prev = pt_listend;
            pt_listend = pt_listend->_pt_next;
        }
        pt_node = NULL;
    }
    /* insert the list into the list */
    if(pt_listbegin != NULL && pt_listend != NULL)
    {
        pt_listbegin->_pt_prev = ((listnode_t*)_GET_LIST_COREPOS(t_pos))->_pt_prev;
        pt_listend->_pt_next = (listnode_t*)_GET_LIST_COREPOS(t_pos);
        ((listnode_t*)_GET_LIST_COREPOS(t_pos))->_pt_prev->_pt_next = pt_listbegin;
        ((listnode_t*)_GET_LIST_COREPOS(t_pos))->_pt_prev = pt_listend;
    }
}

void _list_push_back(list_t* pt_list, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, pt_list);
    _list_push_back_varg(pt_list, val_elemlist);
    va_end(val_elemlist);
}

void _list_push_back_varg(list_t* pt_list, va_list val_elemlist)
{
    listnode_t* pt_node = NULL;    /* the insert node */

    assert(pt_list != NULL && pt_list->_pt_node != NULL);

    /* allocate the insert node */
    pt_node = allocate(&pt_list->_t_allocater,
        _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(pt_list)), 1);
    assert(pt_node != NULL);
    _list_get_varg_value_auxiliary(pt_list, val_elemlist, pt_node);
    /* insert the node before the end node */
    pt_node->_pt_next = pt_list->_pt_node;
    pt_node->_pt_prev = pt_list->_pt_node->_pt_prev;
    pt_list->_pt_node->_pt_prev->_pt_next = pt_node;
    pt_list->_pt_node->_pt_prev = pt_node;
}

void list_pop_back(list_t* pt_list)
{
    listnode_t* pt_node = NULL;    /* the delete node */
    bool_t      t_result = false;

    assert(pt_list != NULL && pt_list->_pt_node != NULL);
    assert(list_size(pt_list) > 0);

    /* extrace the back node from the list */
    pt_node = pt_list->_pt_node->_pt_prev;
    pt_node->_pt_prev->_pt_next = pt_list->_pt_node;
    pt_list->_pt_node->_pt_prev = pt_node->_pt_prev;

    /* destroy deleted node */
    t_result = _GET_LIST_TYPE_SIZE(pt_list);
    _GET_LIST_TYPE_DESTROY_FUNCTION(pt_list)(pt_node->_pc_data, &t_result);
    assert(t_result);
    deallocate(&pt_list->_t_allocater, pt_node,
        _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(pt_list)), 1);
}

void _list_push_front(list_t* pt_list, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, pt_list);
    _list_push_front_varg(pt_list, val_elemlist);
    va_end(val_elemlist);
}

void _list_push_front_varg(list_t* pt_list, va_list val_elemlist)
{
    listnode_t* pt_node = NULL;    /* the allocate node */

    assert(pt_list != NULL && pt_list->_pt_node != NULL);

    /* allocate the node */
    pt_node = allocate(&pt_list->_t_allocater,
        _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(pt_list)), 1);
    assert(pt_node != NULL);
    _list_get_varg_value_auxiliary(pt_list, val_elemlist, pt_node);
    /* insert the node into the first position */
    pt_node->_pt_next = pt_list->_pt_node->_pt_next;
    pt_node->_pt_prev = pt_list->_pt_node;
    pt_list->_pt_node->_pt_next->_pt_prev = pt_node;
    pt_list->_pt_node->_pt_next = pt_node;
}

void list_pop_front(list_t* pt_list)
{
    listnode_t* pt_node = NULL;    /* the delete node */
    bool_t      t_result = false;

    assert(pt_list != NULL && pt_list->_pt_node != NULL);
    assert(list_size(pt_list) > 0);

    /* extrac the first node from the list */
    pt_node = pt_list->_pt_node->_pt_next;
    pt_list->_pt_node->_pt_next = pt_node->_pt_next;
    pt_node->_pt_next->_pt_prev = pt_list->_pt_node;
    /* destroy deleted node */
    t_result = _GET_LIST_TYPE_SIZE(pt_list);
    _GET_LIST_TYPE_DESTROY_FUNCTION(pt_list)(pt_node->_pc_data, &t_result);
    assert(t_result);
    deallocate(&pt_list->_t_allocater, pt_node,
        _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(pt_list)), 1);
}

list_iterator_t list_erase(list_t* pt_list, list_iterator_t t_pos)
{
    listnode_t* pt_node = NULL;    /* the delete node */
    bool_t      t_result = false;

    assert(_list_iterator_belong_to_list(pt_list, t_pos));
    assert(!iterator_equal(t_pos, list_end(pt_list)));

    pt_node = (listnode_t*)_GET_LIST_COREPOS(t_pos);
    _GET_LIST_COREPOS(t_pos) = (char*)(pt_node->_pt_next);
    /* extrac the node from list */
    t_result = _GET_LIST_TYPE_SIZE(pt_list);
    _GET_LIST_TYPE_DESTROY_FUNCTION(pt_list)(pt_node->_pc_data, &t_result);
    assert(t_result);
    pt_node->_pt_prev->_pt_next = pt_node->_pt_next;
    pt_node->_pt_next->_pt_prev = pt_node->_pt_prev;
    deallocate(&pt_list->_t_allocater, pt_node,
        _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(pt_list)), 1);

    return t_pos;
}

list_iterator_t list_erase_range(
    list_t* pt_list, list_iterator_t t_begin, list_iterator_t t_end)
{
    assert(_list_iterator_belong_to_list(pt_list, t_begin));
    assert(iterator_equal(t_begin, t_end) || _list_iterator_before(t_begin, t_end));

    while(!iterator_equal(t_begin, t_end))
    {
        t_begin = list_erase(pt_list, t_begin);
    }

    return t_end;
}

void _list_remove(list_t* pt_list, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, pt_list);
    _list_remove_varg(pt_list, val_elemlist);
    va_end(val_elemlist);
}

void _list_remove_varg(list_t* pt_list, va_list val_elemlist)
{
    list_iterator_t t_pos;    /* the remove element position */
    listnode_t*     pt_varg = NULL;
    bool_t          t_less = false;
    bool_t          t_greater = false;

    assert(pt_list != NULL && pt_list->_pt_node != NULL);

    pt_varg = allocate(&pt_list->_t_allocater,
        _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(pt_list)), 1);
    assert(pt_varg != NULL);
    _list_get_varg_value_auxiliary(pt_list, val_elemlist, pt_varg);

    t_pos = list_begin(pt_list);
    while(!iterator_equal(t_pos, list_end(pt_list)))
    {
        t_less = t_greater = _GET_LIST_TYPE_SIZE(pt_list);
        _GET_LIST_TYPE_LESS_FUNCTION(pt_list)(
            ((listnode_t*)_GET_LIST_COREPOS(t_pos))->_pc_data, pt_varg->_pc_data, &t_less);
        _GET_LIST_TYPE_LESS_FUNCTION(pt_list)(
            pt_varg->_pc_data, ((listnode_t*)_GET_LIST_COREPOS(t_pos))->_pc_data, &t_greater);
        if(t_less || t_greater)
        {
            t_pos = iterator_next(t_pos);
        }
        else
        {
            t_pos = list_erase(pt_list, t_pos);
        }
    }

    _list_destroy_varg_value_auxiliary(pt_list, pt_varg);
    deallocate(&pt_list->_t_allocater, pt_varg,
        _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(pt_list)), 1);
}

void list_remove_if(list_t* pt_list, unary_function_t t_unary_op)
{
    list_iterator_t t_pos;    /* the delete position */
    bool_t          t_result = false;

    assert(pt_list != NULL && pt_list->_pt_node != NULL);

    if(t_unary_op == NULL)
    {
        t_unary_op = fun_default_unary;
    }

    t_pos = list_begin(pt_list);
    while(!iterator_equal(t_pos, list_end(pt_list)))
    {
        (*t_unary_op)(iterator_get_pointer(t_pos), &t_result);
        if(t_result)
        {
            t_pos = list_erase(pt_list, t_pos);
        }
        else
        {
            t_pos = iterator_next(t_pos);
        }
    }
}

void list_resize(list_t* pt_list, size_t t_resize)
{
    listnode_t* pt_node = NULL; /* the node for allocate */
    size_t      t_listsize = 0; /* the list size */
    size_t      t_index = 0;

    assert(pt_list != NULL && pt_list->_pt_node != NULL);


    t_listsize = list_size(pt_list);
    if(t_resize < t_listsize)
    {
        for(t_index = 0; t_index < t_listsize - t_resize; ++t_index)
        {
            list_pop_back(pt_list);
        }
    }
    else
    {
        for(t_index = 0; t_index < t_resize - t_listsize; ++t_index)
        {
            pt_node = allocate(&pt_list->_t_allocater,
                _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(pt_list)), 1);
            assert(pt_node != NULL);
            _list_init_node_auxiliary(pt_list, pt_node);

            pt_node->_pt_next = pt_list->_pt_node;
            pt_node->_pt_prev = pt_list->_pt_node->_pt_prev;
            pt_list->_pt_node->_pt_prev->_pt_next = pt_node;
            pt_list->_pt_node->_pt_prev = pt_node;
            pt_node = NULL;
        }
    }
}

void _list_resize_elem(list_t* pt_list, size_t t_resize, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_resize);
    _list_resize_elem_varg(pt_list, t_resize, val_elemlist);
    va_end(val_elemlist);
}

void _list_resize_elem_varg(list_t* pt_list, size_t t_resize, va_list val_elemlist)
{
    listnode_t* pt_node = NULL; /* the node for allocate */
    size_t      t_listsize = 0; /* the list size */
    size_t      t_index = 0;
    listnode_t* pt_varg = NULL;
    bool_t      t_result = false;

    assert(pt_list != NULL && pt_list->_pt_node != NULL);


    t_listsize = list_size(pt_list);
    if(t_resize < t_listsize)
    {
        for(t_index = 0; t_index < t_listsize - t_resize; ++t_index)
        {
            list_pop_back(pt_list);
        }
    }
    else
    {
        /* get varg value only once */
        pt_varg = allocate(&pt_list->_t_allocater,
            _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(pt_list)), 1);
        assert(pt_varg != NULL);
        _list_get_varg_value_auxiliary(pt_list, val_elemlist, pt_varg);

        for(t_index = 0; t_index < t_resize - t_listsize; ++t_index)
        {
            pt_node = allocate(&pt_list->_t_allocater,
                _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(pt_list)), 1);
            assert(pt_node != NULL);
            _list_init_node_auxiliary(pt_list, pt_node);
            t_result = _GET_LIST_TYPE_SIZE(pt_list);
            _GET_LIST_TYPE_COPY_FUNCTION(pt_list)(
                pt_node->_pc_data, pt_varg->_pc_data, &t_result);
            assert(t_result);

            pt_node->_pt_next = pt_list->_pt_node;
            pt_node->_pt_prev = pt_list->_pt_node->_pt_prev;
            pt_list->_pt_node->_pt_prev->_pt_next = pt_node;
            pt_list->_pt_node->_pt_prev = pt_node;
            pt_node = NULL;
        }

        _list_destroy_varg_value_auxiliary(pt_list, pt_varg);
        deallocate(&pt_list->_t_allocater, pt_varg,
            _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(pt_list)), 1);
    }
}

void list_clear(list_t* pt_list)
{
    list_erase_range(pt_list, list_begin(pt_list), list_end(pt_list));
}

void list_unique(list_t* pt_list)
{
    list_iterator_t t_pos;
    listnode_t*     pt_node = NULL;   /* current node */
    bool_t          t_less = false;
    bool_t          t_greater = false;

    assert(pt_list != NULL && pt_list->_pt_node != NULL);

    pt_node = pt_list->_pt_node->_pt_next->_pt_next;
    while(pt_node != pt_list->_pt_node)
    {
        t_less = t_greater = _GET_LIST_TYPE_SIZE(pt_list);
        _GET_LIST_TYPE_LESS_FUNCTION(pt_list)(
            pt_node->_pt_prev->_pc_data, pt_node->_pc_data, &t_less);
        _GET_LIST_TYPE_LESS_FUNCTION(pt_list)(
            pt_node->_pc_data, pt_node->_pt_prev->_pc_data, &t_greater);
        if(t_less || t_greater)
        {
            pt_node = pt_node->_pt_next;
        }
        else
        {
            t_pos = create_list_iterator();
            _GET_CONTAINER(t_pos) = pt_list;
            _GET_LIST_COREPOS(t_pos) = (char*)pt_node;
            t_pos = list_erase(pt_list, t_pos);
            pt_node = (listnode_t*)_GET_LIST_COREPOS(t_pos);
        }
    }
}

void list_unique_if(list_t* pt_list, binary_function_t t_binary_op)
{
    list_iterator_t t_pos;
    listnode_t*     pt_node = NULL;   /* current node */
    bool_t          t_result = false;

    assert(pt_list != NULL && pt_list->_pt_node != NULL);

    if(t_binary_op == NULL)
    {
        t_binary_op = fun_default_binary;
    }

    pt_node = pt_list->_pt_node->_pt_next->_pt_next;

    /* char* */
    if(strncmp(_GET_LIST_TYPE_BASENAME(pt_list), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        while(pt_node != pt_list->_pt_node)
        {
            (*t_binary_op)(string_c_str((string_t*)pt_node->_pt_prev->_pc_data),
                string_c_str((string_t*)pt_node->_pc_data), &t_result);
            if(t_result)
            {
                t_pos = create_list_iterator();
                _GET_CONTAINER(t_pos) = pt_list;
                _GET_LIST_COREPOS(t_pos) = (char*)pt_node;
                t_pos = list_erase(pt_list, t_pos);
                pt_node = (listnode_t*)_GET_LIST_COREPOS(t_pos);
            }
            else
            {
                pt_node = pt_node->_pt_next;
            }
        }
    }
    else
    {
        while(pt_node != pt_list->_pt_node)
        {
            (*t_binary_op)(pt_node->_pt_prev->_pc_data, pt_node->_pc_data, &t_result);
            if(t_result)
            {
                t_pos = create_list_iterator();
                _GET_CONTAINER(t_pos) = pt_list;
                _GET_LIST_COREPOS(t_pos) = (char*)pt_node;
                t_pos = list_erase(pt_list, t_pos);
                pt_node = (listnode_t*)_GET_LIST_COREPOS(t_pos);
            }
            else
            {
                pt_node = pt_node->_pt_next;
            }
        }
    }
}

void list_splice(list_t* pt_list, list_iterator_t t_pos, list_t* pt_listsrc)
{
#ifdef NDEBUG
    list_t* pt_avoidwarning = NULL;
    pt_avoidwarning = pt_list;
#endif

    assert(_list_same_type(pt_list, pt_listsrc));
    assert(_list_iterator_belong_to_list(pt_list, t_pos));
    /* ensure the pt_list is difference from pt_listsrc */
    assert(_GET_LIST_CONTAINER(t_pos) != pt_listsrc);

    if(!list_empty(pt_listsrc))
    {
        _transfer(t_pos, list_begin(pt_listsrc), list_end(pt_listsrc));
    }
}

void list_splice_pos(
    list_t* pt_list, list_iterator_t t_pos, list_t* pt_listsrc, list_iterator_t t_possrc)
{
    list_iterator_t t_possrcnext;  /* the next position of possrc */

#ifdef NDEBUG
    list_t* pt_avoidwarning = NULL;
    pt_avoidwarning = pt_list;
#endif

    assert(_list_same_type(pt_list, pt_listsrc));
    assert(_list_iterator_belong_to_list(pt_list, t_pos));
    assert(_list_iterator_belong_to_list(pt_listsrc, t_possrc));

    /* t_possrcnext = t_possrc; */
    t_possrcnext = iterator_next(t_possrc);
    if(!list_empty(pt_listsrc) && !iterator_equal(t_possrc, list_end(pt_listsrc)))
    {
        _transfer(t_pos, t_possrc, t_possrcnext);
    }
}

void list_splice_range(
    list_t* pt_list, list_iterator_t t_pos,
    list_t* pt_listsrc, list_iterator_t t_begin, list_iterator_t t_end)
{
#ifdef NDEBUG
    list_t* pt_avoidwarning1 = NULL;
    list_t* pt_avoidwarning2 = NULL;
    pt_avoidwarning1 = pt_list;
    pt_avoidwarning2 = pt_listsrc;
#endif

    assert(_list_same_type(pt_list, pt_listsrc));
    assert(_list_iterator_belong_to_list(pt_list, t_pos));
    assert(_list_iterator_belong_to_list(pt_listsrc, t_begin));
    assert(iterator_equal(t_begin, t_end) || _list_iterator_before(t_begin, t_end));
    /* ensure the pt_list is difference from pt_listsrc */
    assert(_GET_LIST_CONTAINER(t_pos) != pt_listsrc);

    _transfer(t_pos, t_begin, t_end);
}

void list_sort(list_t* pt_list)
{
    assert(pt_list != NULL && pt_list->_pt_node != NULL);

    if(list_size(pt_list) > 1)
    {
        _quick_sort(list_end(pt_list), list_end(pt_list), NULL);
    }
}

void list_sort_if(list_t* pt_list, binary_function_t t_binary_op)
{
    assert(pt_list != NULL && pt_list->_pt_node != NULL);

    if(list_size(pt_list) > 1)
    {
        _quick_sort(list_end(pt_list), list_end(pt_list), t_binary_op);
    }
}

void list_merge(list_t* pt_listdest, list_t* pt_listsrc)
{
    listnode_t*     pt_dest = NULL;   /* the insert position */
    listnode_t*     pt_src = NULL;    /* the srource position */
    list_iterator_t t_dest;
    list_iterator_t t_src;
    list_iterator_t t_srcnext;
    bool_t          t_result = false;

    assert(_list_same_type(pt_listdest, pt_listsrc));

    t_dest = list_begin(pt_listdest);
    t_src = list_begin(pt_listsrc);
    t_srcnext = t_src;

    pt_dest = pt_listdest->_pt_node->_pt_next;
    pt_src = pt_listsrc->_pt_node->_pt_next;
    while(pt_dest != pt_listdest->_pt_node && pt_src != pt_listsrc->_pt_node)
    {
        t_result = _GET_LIST_TYPE_SIZE(pt_listdest);
        _GET_LIST_TYPE_LESS_FUNCTION(pt_listdest)(
            pt_src->_pc_data, pt_dest->_pc_data, &t_result);
        if(t_result)
        {
            _GET_LIST_COREPOS(t_dest) = (char*)pt_dest;
            _GET_LIST_COREPOS(t_src) = (char*)(pt_src);
            _GET_LIST_COREPOS(t_srcnext) = (char*)(pt_src->_pt_next);
            pt_src = pt_src->_pt_next;
            _transfer(t_dest, t_src, t_srcnext);
        }
        else
        {
            pt_dest = pt_dest->_pt_next;
        }
    }

    if(pt_src != pt_listsrc->_pt_node)
    {
        _GET_LIST_COREPOS(t_src) = (char*)pt_src;
        _transfer(list_end(pt_listdest), t_src, list_end(pt_listsrc));
    }
}

void list_merge_if(
    list_t* pt_listdest, list_t* pt_listsrc, binary_function_t t_binary_op)
{
    listnode_t* pt_dest = NULL;   /* the insert position */
    listnode_t* pt_src = NULL;    /* the srource position */
    list_iterator_t t_dest;
    list_iterator_t t_src;
    list_iterator_t t_srcnext;
    bool_t          t_result = false;

    assert(_list_same_type(pt_listdest, pt_listsrc));

    if(t_binary_op == NULL)
    {
        t_binary_op = fun_default_binary;
    }

    t_dest = list_begin(pt_listdest);
    t_src = list_begin(pt_listsrc);
    t_srcnext = t_src;

    pt_dest = pt_listdest->_pt_node->_pt_next;
    pt_src = pt_listsrc->_pt_node->_pt_next;
    /* char* */
    if(strncmp(_GET_LIST_TYPE_BASENAME(pt_listdest), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        while(pt_dest != pt_listdest->_pt_node && pt_src != pt_listsrc->_pt_node)
        {
            (*t_binary_op)(string_c_str((string_t*)pt_src->_pc_data),
                string_c_str((string_t*)pt_dest->_pc_data), &t_result);
            if(t_result)
            {
                _GET_LIST_COREPOS(t_dest) = (char*)pt_dest;
                _GET_LIST_COREPOS(t_src) = (char*)(pt_src);
                _GET_LIST_COREPOS(t_srcnext) = (char*)(pt_src->_pt_next);
                pt_src = pt_src->_pt_next;
                _transfer(t_dest, t_src, t_srcnext);
            }
            else
            {
                pt_dest = pt_dest->_pt_next;
            }
        }
    }
    else
    {
        while(pt_dest != pt_listdest->_pt_node && pt_src != pt_listsrc->_pt_node)
        {
            (*t_binary_op)(pt_src->_pc_data, pt_dest->_pc_data, &t_result);
            if(t_result)
            {
                _GET_LIST_COREPOS(t_dest) = (char*)pt_dest;
                _GET_LIST_COREPOS(t_src) = (char*)(pt_src);
                _GET_LIST_COREPOS(t_srcnext) = (char*)(pt_src->_pt_next);
                pt_src = pt_src->_pt_next;
                _transfer(t_dest, t_src, t_srcnext);
            }
            else
            {
                pt_dest = pt_dest->_pt_next;
            }
        }
    }

    if(pt_src != pt_listsrc->_pt_node)
    {
        _GET_LIST_COREPOS(t_src) = (char*)pt_src;
        _transfer(list_end(pt_listdest), t_src, list_end(pt_listsrc));
    }
}

void list_reverse(list_t* pt_list)
{
    listnode_t* pt_node = NULL;
    list_iterator_t t_pos;
    list_iterator_t t_posnext;

    assert(pt_list != NULL && pt_list->_pt_node != NULL);

    if(list_size(pt_list) > 1)
    {
        t_pos = list_begin(pt_list);
        t_posnext = t_pos;

        /* point to the second node */
        pt_node = pt_list->_pt_node->_pt_next->_pt_next;
        while(pt_node != pt_list->_pt_node)
        {
            _GET_LIST_COREPOS(t_pos) = (char*)pt_node;
            _GET_LIST_COREPOS(t_posnext) = (char*)(pt_node->_pt_next);
            pt_node = pt_node->_pt_next;
            _transfer(list_begin(pt_list), t_pos, t_posnext);
        }
    }
}

void _list_init_elem_auxiliary(list_t* pt_list, void* pv_elem)
{
    assert(pt_list != NULL && pv_elem != NULL);

    /* initialize new elements */
    if(_GET_LIST_TYPE_STYLE(pt_list) == _TYPE_CSTL_BUILTIN)
    {
        /* get element type name */
        char s_elemtypename[_TYPE_NAME_SIZE + 1];
        _type_get_elem_typename(_GET_LIST_TYPE_NAME(pt_list), s_elemtypename);

        _GET_LIST_TYPE_INIT_FUNCTION(pt_list)(pv_elem, s_elemtypename);
    }
    else
    {
        bool_t t_result = _GET_LIST_TYPE_SIZE(pt_list);
        _GET_LIST_TYPE_INIT_FUNCTION(pt_list)(pv_elem, &t_result);
        assert(t_result);
    }
}

/** local function implementation section **/
#ifndef NDEBUG
static bool_t _list_iterator_belong_to_list(
    const list_t* cpt_list, list_iterator_t t_iter)
{
    listnode_t* pt_listnode = NULL;  /* the list node pointer */

    assert(cpt_list != NULL);
    assert(cpt_list->_pt_node != NULL);
    assert(_GET_LIST_COREPOS(t_iter) != NULL);
    assert(_GET_LIST_CONTAINER(t_iter) == cpt_list);

    if((listnode_t*)_GET_LIST_COREPOS(t_iter) == cpt_list->_pt_node)
    {
        return true;
    }

    for(pt_listnode = cpt_list->_pt_node->_pt_next;
        pt_listnode != cpt_list->_pt_node;
        pt_listnode = pt_listnode->_pt_next)
    {
        if(pt_listnode == (listnode_t*)_GET_LIST_COREPOS(t_iter))
        {
            return true;
        }
    }

    return false;
}

static bool_t _list_same_list_iterator_type(
    const list_t* cpt_list, list_iterator_t t_iter)
{
    assert(cpt_list != NULL && _GET_LIST_CONTAINER(t_iter) != NULL);
    assert(_GET_LIST_CONTAINER_TYPE(t_iter) == _LIST_CONTAINER &&
           _GET_LIST_ITERATOR_TYPE(t_iter) == _BIDIRECTIONAL_ITERATOR);
    return _list_same_type(cpt_list, _GET_LIST_CONTAINER(t_iter));
}
#endif /* NDEBUG */

static bool_t _list_same_type(const list_t* cpt_listfirst, const list_t* cpt_listsecond)
{
    assert(cpt_listfirst != NULL && cpt_listsecond != NULL);
    return _type_is_same(_GET_LIST_TYPE_NAME(cpt_listfirst),
                         _GET_LIST_TYPE_NAME(cpt_listsecond)) &&
           (cpt_listfirst->_t_typeinfo._pt_type == cpt_listsecond->_t_typeinfo._pt_type) &&
           (cpt_listfirst->_t_typeinfo._t_style == cpt_listsecond->_t_typeinfo._t_style);
}

static void _transfer(
    list_iterator_t t_pos, list_iterator_t t_begin, list_iterator_t t_end)
{
    /* insert the range [t_begin, t_end) to dest list */
    list_insert_range(_GET_LIST_CONTAINER(t_pos), t_pos, t_begin, t_end);
    /* delete the range [t_begin, t_end) front the source list */
    list_erase_range(_GET_LIST_CONTAINER(t_begin), t_begin, t_end);
}

static void _quick_sort(
    list_iterator_t t_beforefirstpos, list_iterator_t t_afterlastpos,
    binary_function_t t_binary_op)
{
    listnode_t*     pt_pivot = NULL;               /* the pivot pointer */
    listnode_t*     pt_afterpivot = NULL;          /* the node after pivot */
    listnode_t*     pt_beforepivot = NULL;         /* the node before pivot */
    list_t*         pt_container = NULL;           /* the container */
    list_iterator_t t_afterpivot;                  /* the pos after pivot */
    list_iterator_t t_beforepivot;                 /* the pos before pivot */
    list_iterator_t t_firstpos = t_beforefirstpos; /* the first pos */
    list_iterator_t t_lastpos = t_afterlastpos;    /* the last pos */
    list_iterator_t t_pivotpos;                    /* the pivot pos */

    if(iterator_equal(t_firstpos, list_end(_GET_LIST_CONTAINER(t_firstpos))))
    {
        t_firstpos = list_begin(_GET_LIST_CONTAINER(t_firstpos));
    }
    else
    {
        t_firstpos = iterator_next(t_firstpos);
    }
    t_lastpos = iterator_prev(t_lastpos);

    assert(_list_iterator_before(t_firstpos, t_lastpos));

    /* if the iterator distance > 0 (the element count > 1) then sort */
    if(_list_iterator_distance(t_firstpos, t_lastpos) > 0)
    {
        /* take the last node as the pivot */
        pt_pivot = (listnode_t*)_GET_LIST_COREPOS(t_lastpos);
        pt_beforepivot = (listnode_t*)_GET_LIST_COREPOS(t_firstpos);
        pt_afterpivot = ((listnode_t*)_GET_LIST_COREPOS(t_lastpos))->_pt_prev;
        t_beforepivot = create_list_iterator();
        _GET_CONTAINER(t_beforepivot) = _GET_CONTAINER(t_firstpos);
        _GET_LIST_COREPOS(t_beforepivot) = _GET_LIST_COREPOS(t_firstpos);
        t_afterpivot = create_list_iterator();
        _GET_CONTAINER(t_afterpivot) = _GET_CONTAINER(t_lastpos);
        _GET_LIST_COREPOS(t_afterpivot) = _GET_LIST_COREPOS(t_lastpos);
        t_pivotpos = create_list_iterator();
        _GET_CONTAINER(t_pivotpos) = _GET_CONTAINER(t_lastpos);
        _GET_LIST_COREPOS(t_pivotpos) = _GET_LIST_COREPOS(t_lastpos);

        pt_container = _GET_LIST_CONTAINER(t_firstpos);

        if(t_binary_op != NULL)
        {
            bool_t t_result = false;
            bool_t t_greater = false;
            /* char* */
            if(strncmp(_GET_LIST_TYPE_BASENAME(pt_container),
                    _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
            {
                for(;;)
                {
                    /* move the before pointer next until the node > pivot */
                    (*t_binary_op)(string_c_str((string_t*)pt_beforepivot->_pc_data),
                        string_c_str((string_t*)pt_pivot->_pc_data), &t_result);
                    (*t_binary_op)(string_c_str((string_t*)pt_pivot->_pc_data),
                        string_c_str((string_t*)pt_beforepivot->_pc_data), &t_greater);
                    while((t_result || (!t_result && !t_greater)) &&
                          pt_beforepivot != pt_pivot->_pt_prev)
                    {
                        pt_beforepivot = pt_beforepivot->_pt_next;
                        (*t_binary_op)(string_c_str((string_t*)pt_beforepivot->_pc_data),
                            string_c_str((string_t*)pt_pivot->_pc_data), &t_result);
                        (*t_binary_op)(string_c_str((string_t*)pt_pivot->_pc_data),
                            string_c_str((string_t*)pt_beforepivot->_pc_data), &t_greater);
                    }

                    /* move the after pointer prev until the node <= pivot */
                    (*t_binary_op)(string_c_str((string_t*)pt_pivot->_pc_data),
                        string_c_str((string_t*)pt_afterpivot->_pc_data), &t_result);
                    while(t_result && pt_afterpivot !=
                            ((listnode_t*)_GET_LIST_COREPOS(t_beforefirstpos))->_pt_next)
                    {
                        pt_afterpivot = pt_afterpivot->_pt_prev;
                        (*t_binary_op)(string_c_str((string_t*)pt_pivot->_pc_data),
                            string_c_str((string_t*)pt_afterpivot->_pc_data), &t_result);
                    }

                    /* if the before pointer before the after pointer then swap */
                    _GET_LIST_COREPOS(t_beforepivot) = (char*)pt_beforepivot;
                    _GET_LIST_COREPOS(t_afterpivot) = (char*)pt_afterpivot;
                    if(_list_iterator_before(t_beforepivot, t_afterpivot))
                    {
                        _swap_node(&pt_beforepivot, &pt_afterpivot);
                        pt_beforepivot = pt_beforepivot->_pt_next;
                        pt_afterpivot = pt_afterpivot->_pt_prev;
                    }
                    else
                    {
                        break;
                    }
                }

                (*t_binary_op)(string_c_str((string_t*)pt_beforepivot->_pc_data),
                    string_c_str((string_t*)pt_pivot->_pc_data), &t_result);
                if(!t_result)
                {
                    _swap_node(&pt_beforepivot, &pt_pivot);
                    pt_pivot = pt_beforepivot;
                }
                _GET_LIST_COREPOS(t_pivotpos) = (char*)pt_pivot;
                if(((listnode_t*)_GET_LIST_COREPOS(t_beforefirstpos))->_pt_next !=
                       (listnode_t*)_GET_LIST_COREPOS(t_pivotpos) &&
                   ((listnode_t*)_GET_LIST_COREPOS(t_beforefirstpos))->_pt_next !=
                       ((listnode_t*)_GET_LIST_COREPOS(t_pivotpos))->_pt_prev)
                {
                    _quick_sort(t_beforefirstpos, t_pivotpos, t_binary_op);
                }
                if(((listnode_t*)_GET_LIST_COREPOS(t_pivotpos))->_pt_next !=
                       (listnode_t*)_GET_LIST_COREPOS(t_afterlastpos) &&
                   ((listnode_t*)_GET_LIST_COREPOS(t_pivotpos))->_pt_next !=
                       ((listnode_t*)_GET_LIST_COREPOS(t_afterlastpos))->_pt_prev)
                {
                    _quick_sort(t_pivotpos, t_afterlastpos, t_binary_op);
                }
            }
            else
            {
                for(;;)
                {
                    /* move the before pointer next until the node > pivot */
                    (*t_binary_op)(pt_beforepivot->_pc_data, pt_pivot->_pc_data, &t_result);
                    (*t_binary_op)(pt_pivot->_pc_data, pt_beforepivot->_pc_data, &t_greater);
                    while((t_result || (!t_result && !t_greater)) &&
                          pt_beforepivot != pt_pivot->_pt_prev)
                    {
                        pt_beforepivot = pt_beforepivot->_pt_next;
                        (*t_binary_op)(pt_beforepivot->_pc_data, pt_pivot->_pc_data, &t_result);
                        (*t_binary_op)(pt_pivot->_pc_data, pt_beforepivot->_pc_data, &t_greater);
                    }

                    /* move the after pointer prev until the node <= pivot */
                    (*t_binary_op)(pt_pivot->_pc_data, pt_afterpivot->_pc_data, &t_result);
                    while(t_result && pt_afterpivot !=
                            ((listnode_t*)_GET_LIST_COREPOS(t_beforefirstpos))->_pt_next)
                    {
                        pt_afterpivot = pt_afterpivot->_pt_prev;
                        (*t_binary_op)(pt_pivot->_pc_data, pt_afterpivot->_pc_data, &t_result);
                    }

                    /* if the before pointer before the after pointer then swap */
                    _GET_LIST_COREPOS(t_beforepivot) = (char*)pt_beforepivot;
                    _GET_LIST_COREPOS(t_afterpivot) = (char*)pt_afterpivot;
                    if(_list_iterator_before(t_beforepivot, t_afterpivot))
                    {
                        _swap_node(&pt_beforepivot, &pt_afterpivot);
                        pt_beforepivot = pt_beforepivot->_pt_next;
                        pt_afterpivot = pt_afterpivot->_pt_prev;
                    }
                    else
                    {
                        break;
                    }
                }

                (*t_binary_op)(pt_beforepivot->_pc_data, pt_pivot->_pc_data, &t_result);
                if(!t_result)
                {
                    _swap_node(&pt_beforepivot, &pt_pivot);
                    pt_pivot = pt_beforepivot;
                }
                _GET_LIST_COREPOS(t_pivotpos) = (char*)pt_pivot;
                if(((listnode_t*)_GET_LIST_COREPOS(t_beforefirstpos))->_pt_next !=
                       (listnode_t*)_GET_LIST_COREPOS(t_pivotpos) &&
                   ((listnode_t*)_GET_LIST_COREPOS(t_beforefirstpos))->_pt_next !=
                       ((listnode_t*)_GET_LIST_COREPOS(t_pivotpos))->_pt_prev)
                {
                    _quick_sort(t_beforefirstpos, t_pivotpos, t_binary_op);
                }
                if(((listnode_t*)_GET_LIST_COREPOS(t_pivotpos))->_pt_next !=
                       (listnode_t*)_GET_LIST_COREPOS(t_afterlastpos) &&
                   ((listnode_t*)_GET_LIST_COREPOS(t_pivotpos))->_pt_next !=
                       ((listnode_t*)_GET_LIST_COREPOS(t_afterlastpos))->_pt_prev)
                {
                    _quick_sort(t_pivotpos, t_afterlastpos, t_binary_op);
                }
            }
        }
        else
        {
            bool_t t_result = false;
            bool_t t_greater = false;
            for(;;)
            {
                /* move the before pointer next until the node > pivot */
                t_result = t_greater = _GET_LIST_TYPE_SIZE(pt_container);
                _GET_LIST_TYPE_LESS_FUNCTION(pt_container)(
                    pt_beforepivot->_pc_data, pt_pivot->_pc_data, &t_result);
                _GET_LIST_TYPE_LESS_FUNCTION(pt_container)(
                    pt_pivot->_pc_data, pt_beforepivot->_pc_data, &t_greater);
                while((t_result || (!t_result && !t_greater)) &&
                      pt_beforepivot != pt_pivot->_pt_prev)
                {
                    pt_beforepivot = pt_beforepivot->_pt_next;

                    t_result = t_greater = _GET_LIST_TYPE_SIZE(pt_container);
                    _GET_LIST_TYPE_LESS_FUNCTION(pt_container)(
                        pt_beforepivot->_pc_data, pt_pivot->_pc_data, &t_result);
                    _GET_LIST_TYPE_LESS_FUNCTION(pt_container)(
                        pt_pivot->_pc_data, pt_beforepivot->_pc_data, &t_greater);
                }
                /* move the after pointer prev until the node <= pivot */
                t_result = _GET_LIST_TYPE_SIZE(pt_container);
                _GET_LIST_TYPE_LESS_FUNCTION(pt_container)(
                    pt_pivot->_pc_data, pt_afterpivot->_pc_data, &t_result);
                while(t_result && pt_afterpivot !=
                        ((listnode_t*)_GET_LIST_COREPOS(t_beforefirstpos))->_pt_next)
                {
                    pt_afterpivot = pt_afterpivot->_pt_prev;

                    t_result = _GET_LIST_TYPE_SIZE(pt_container);
                    _GET_LIST_TYPE_LESS_FUNCTION(pt_container)(
                        pt_pivot->_pc_data, pt_afterpivot->_pc_data, &t_result);
                }
                /* if the before pointer before the after pointer then swap */
                _GET_LIST_COREPOS(t_beforepivot) = (char*)pt_beforepivot;
                _GET_LIST_COREPOS(t_afterpivot) = (char*)pt_afterpivot;
                if(_list_iterator_before(t_beforepivot, t_afterpivot))
                {
                    _swap_node(&pt_beforepivot, &pt_afterpivot);
                    pt_beforepivot = pt_beforepivot->_pt_next;
                    pt_afterpivot = pt_afterpivot->_pt_prev;
                }
                else
                {
                    break;
                }
            }

            t_result = _GET_LIST_TYPE_SIZE(pt_container);
            _GET_LIST_TYPE_LESS_FUNCTION(pt_container)(
                pt_pivot->_pc_data, pt_beforepivot->_pc_data, &t_result);
            if(t_result)
            {
                _swap_node(&pt_beforepivot, &pt_pivot);
                pt_pivot = pt_beforepivot;
            }
            _GET_LIST_COREPOS(t_pivotpos) = (char*)pt_pivot;
            if(((listnode_t*)_GET_LIST_COREPOS(t_beforefirstpos))->_pt_next !=
                   (listnode_t*)_GET_LIST_COREPOS(t_pivotpos) &&
               ((listnode_t*)_GET_LIST_COREPOS(t_beforefirstpos))->_pt_next !=
                   ((listnode_t*)_GET_LIST_COREPOS(t_pivotpos))->_pt_prev)
            {
                _quick_sort(t_beforefirstpos, t_pivotpos, t_binary_op);
            }
            if(((listnode_t*)_GET_LIST_COREPOS(t_pivotpos))->_pt_next !=
                   (listnode_t*)_GET_LIST_COREPOS(t_afterlastpos) &&
               ((listnode_t*)_GET_LIST_COREPOS(t_pivotpos))->_pt_next !=
                   ((listnode_t*)_GET_LIST_COREPOS(t_afterlastpos))->_pt_prev)
            {
                _quick_sort(t_pivotpos, t_afterlastpos, t_binary_op);
            }
        }
    }
}

static void _swap_node(listnode_t** ppt_first, listnode_t** ppt_second)
{
    listnode_t* pt_afterfirst = NULL;   /* the position after first */
    listnode_t* pt_aftersecond = NULL;  /* the position after second */

    assert(ppt_first != NULL && *ppt_first != NULL);
    assert(ppt_second != NULL && *ppt_second != NULL);

    /* if the first followed by the second */
    if((*ppt_first)->_pt_next == (*ppt_second))
    {
        (*ppt_second)->_pt_prev = (*ppt_first)->_pt_prev;
        (*ppt_first)->_pt_prev->_pt_next = (*ppt_second);
        (*ppt_first)->_pt_next = (*ppt_second)->_pt_next;
        (*ppt_first)->_pt_prev = (*ppt_second);
        (*ppt_second)->_pt_next->_pt_prev = (*ppt_first);
        (*ppt_second)->_pt_next = (*ppt_first);

        (*ppt_first) = (*ppt_second);
        (*ppt_second) = (*ppt_second)->_pt_next;
    }
    else
    {
        /* keep the position after the two node */
        pt_afterfirst = (*ppt_first)->_pt_next;
        pt_aftersecond = (*ppt_second)->_pt_next;
        /* extrac the two node from the list */
        (*ppt_first)->_pt_prev->_pt_next = pt_afterfirst;
        pt_afterfirst->_pt_prev = (*ppt_first)->_pt_prev;
        (*ppt_second)->_pt_prev->_pt_next = pt_aftersecond;
        pt_aftersecond->_pt_prev = (*ppt_second)->_pt_prev;
        /* swap insert into the position */
        (*ppt_first)->_pt_next = pt_aftersecond;
        (*ppt_first)->_pt_prev = pt_aftersecond->_pt_prev;
        pt_aftersecond->_pt_prev->_pt_next = (*ppt_first);
        pt_aftersecond->_pt_prev = (*ppt_first);
        (*ppt_second)->_pt_next = pt_afterfirst;
        (*ppt_second)->_pt_prev = pt_afterfirst->_pt_prev;
        pt_afterfirst->_pt_prev->_pt_next = (*ppt_second);
        pt_afterfirst->_pt_prev = (*ppt_second);

        (*ppt_first) = pt_afterfirst->_pt_prev;
        (*ppt_second) = pt_aftersecond->_pt_prev;
    }
}

static void _list_get_varg_value_auxiliary(
    list_t* pt_list, va_list val_elemlist, listnode_t* pt_node)
{
    _list_init_node_auxiliary(pt_list, pt_node);
    _type_get_varg_value(&pt_list->_t_typeinfo, val_elemlist, pt_node->_pc_data);
}

static void _list_destroy_varg_value_auxiliary(list_t* pt_list, listnode_t* pt_node)
{
    bool_t t_result = _GET_LIST_TYPE_SIZE(pt_list);
    _GET_LIST_TYPE_DESTROY_FUNCTION(pt_list)(pt_node->_pc_data, &t_result);
    assert(t_result);
}

static void _list_init_node_auxiliary(list_t* pt_list, listnode_t* pt_node)
{
    assert(pt_list != NULL && pt_node != NULL);

    /* initialize new elements */
    if(_GET_LIST_TYPE_STYLE(pt_list) == _TYPE_CSTL_BUILTIN)
    {
        /* get element type name */
        char s_elemtypename[_TYPE_NAME_SIZE + 1];
        _type_get_elem_typename(_GET_LIST_TYPE_NAME(pt_list), s_elemtypename);

        _GET_LIST_TYPE_INIT_FUNCTION(pt_list)(pt_node->_pc_data, s_elemtypename);
    }
    else
    {
        bool_t t_result = _GET_LIST_TYPE_SIZE(pt_list);
        _GET_LIST_TYPE_INIT_FUNCTION(pt_list)(pt_node->_pc_data, &t_result);
        assert(t_result);
    }
}

/** eof **/

