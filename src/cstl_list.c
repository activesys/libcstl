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
#include <cstl/cstl_def.h>
#include <cstl/cstl_alloc.h>
#include <cstl/cstl_types.h>
#include <cstl/cstl_iterator.h>
#include <cstl/cstl_iterator_private.h>
#include <cstl/cfunctional.h>

#include <cstl/cstl_list_iterator.h>
#include <cstl/cstl_list_private.h>
#include <cstl/cstl_list.h>

#include <cstl/cstring.h>

#include "cstl_list_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/

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
    _alloc_init(&pt_list->_t_allocater);
    pt_list->_pt_node = _alloc_allocate(&pt_list->_t_allocater,
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
            pt_node = _alloc_allocate(&pt_list->_t_allocater,
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

    t_newiterator = _create_list_iterator();
    _GET_LIST_COREPOS(t_newiterator) = (char*)(cpt_list->_pt_node->_pt_next);
    _GET_CONTAINER(t_newiterator) = (list_t*)cpt_list;

    return t_newiterator;
}

list_iterator_t list_end(const list_t* cpt_list)
{
    list_iterator_t t_newiterator;  /* new list iterator */

    assert(cpt_list != NULL && cpt_list->_pt_node != NULL);

    t_newiterator = _create_list_iterator();
    _GET_LIST_COREPOS(t_newiterator) = (char*)(cpt_list->_pt_node);
    _GET_CONTAINER(t_newiterator) = (list_t*)cpt_list;

    return t_newiterator;
}

list_reverse_iterator_t list_rbegin(const list_t* cpt_list)
{
    list_reverse_iterator_t t_newiterator;   /* new list reverse iterator */

    assert(cpt_list != NULL && cpt_list->_pt_node != NULL);

    t_newiterator = _create_list_iterator();
    _GET_LIST_COREPOS(t_newiterator) = (char*)(cpt_list->_pt_node->_pt_prev);
    _GET_CONTAINER(t_newiterator) = (list_t*)cpt_list;

    return t_newiterator;
}

list_reverse_iterator_t list_rend(const list_t* cpt_list)
{
    list_reverse_iterator_t t_newiterator;  /* new list reverse iterator */

    assert(cpt_list != NULL && cpt_list->_pt_node != NULL);

    t_newiterator = _create_list_iterator();
    _GET_LIST_COREPOS(t_newiterator) = (char*)(cpt_list->_pt_node);
    _GET_CONTAINER(t_newiterator) = (list_t*)cpt_list;

    return t_newiterator;
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
        pt_node = _alloc_allocate(&pt_list->_t_allocater,
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
    _alloc_deallocate(&pt_list->_t_allocater, pt_node,
        _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(pt_list)), 1);
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
    _alloc_deallocate(&pt_list->_t_allocater, pt_node,
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
    _alloc_deallocate(&pt_list->_t_allocater, pt_node,
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
            pt_node = _alloc_allocate(&pt_list->_t_allocater,
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
            t_pos = _create_list_iterator();
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
                t_pos = _create_list_iterator();
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
                t_pos = _create_list_iterator();
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

/** local function implementation section **/

/** eof **/

