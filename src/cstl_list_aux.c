/*
 *  The implement of list auxiliary functions.
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
#ifndef NDEBUG
/**
 * Test iterator referenced data is within the list.
 */
bool_t _list_iterator_belong_to_list(const list_t* cplist_list, list_iterator_t it_iter)
{
    listnode_t* pt_listnode = NULL;  /* the list node pointer */

    assert(cplist_list != NULL);
    assert(_list_is_inited(cplist_list));
    assert(_GET_LIST_CONTAINER(it_iter) == cplist_list);
    assert(it_iter._t_containertype == _LIST_CONTAINER);
    assert(it_iter._t_iteratortype == _BIDIRECTIONAL_ITERATOR);

    if((listnode_t*)_GET_LIST_COREPOS(it_iter) == cplist_list->_pt_node)
    {
        return true;
    }

    for(pt_listnode = cplist_list->_pt_node->_pt_next;
        pt_listnode != cplist_list->_pt_node;
        pt_listnode = pt_listnode->_pt_next)
    {
        if(pt_listnode == (listnode_t*)_GET_LIST_COREPOS(it_iter))
        {
            return true;
        }
    }

    return false;
}

/**
 * Test the type that saved in the list container and referenced by it_iter are same.
 */
bool_t _list_same_list_iterator_type(const list_t* cplist_list, list_iterator_t it_iter)
{
    assert(cplist_list != NULL);
    assert(_GET_LIST_CONTAINER(it_iter) != NULL);
    assert(_GET_LIST_CONTAINER_TYPE(it_iter) == _LIST_CONTAINER);
    assert(_GET_LIST_ITERATOR_TYPE(it_iter) == _BIDIRECTIONAL_ITERATOR);
    return _list_same_type(cplist_list, _GET_LIST_CONTAINER(it_iter));
}

/**
 * Test list is created by create_list.
 */
bool_t _list_is_created(const list_t* cplist_list)
{
    assert(cplist_list != NULL);

    if(cplist_list->_t_typeinfo._t_style != _TYPE_C_BUILTIN &&
       cplist_list->_t_typeinfo._t_style != _TYPE_CSTL_BUILTIN &&
       cplist_list->_t_typeinfo._t_style != _TYPE_USER_DEFINE)
    {
        return false;
    }

    if(cplist_list->_t_typeinfo._pt_type == NULL)
    {
        return false;
    }

    if(cplist_list->_pt_node != NULL)
    {
        return false;
    }

    return _alloc_is_inited(&cplist_list->_t_allocater);
}

/**
 * Test list is initialized.
 */
bool_t _list_is_inited(const list_t* cplist_list)
{
    assert(cplist_list != NULL);

    if(cplist_list->_t_typeinfo._t_style != _TYPE_C_BUILTIN &&
       cplist_list->_t_typeinfo._t_style != _TYPE_CSTL_BUILTIN &&
       cplist_list->_t_typeinfo._t_style != _TYPE_USER_DEFINE)
    {
        return false;
    }

    if(cplist_list->_t_typeinfo._pt_type == NULL)
    {
        return false;
    }

    if(cplist_list->_pt_node == NULL)
    {
        return false;
    }

    if(cplist_list->_pt_node->_pt_prev == NULL || cplist_list->_pt_node->_pt_next == NULL)
    {
        return false;
    }

    return true;
}
#endif /* NDEBUG */

/**
 * Test the type that saved in the list container is same.
 */
bool_t _list_same_type(const list_t* cplist_first, const list_t* cplist_second)
{
    assert(cplist_first != NULL);
    assert(cplist_second != NULL);
    assert(_list_is_inited(cplist_first) || _list_is_created(cplist_first));
    assert(_list_is_inited(cplist_second) || _list_is_created(cplist_second));

    return (cplist_first->_t_typeinfo._pt_type == cplist_second->_t_typeinfo._pt_type) &&
           (cplist_first->_t_typeinfo._t_style == cplist_second->_t_typeinfo._t_style) &&
           _type_is_same(_GET_LIST_TYPE_NAME(cplist_first), _GET_LIST_TYPE_NAME(cplist_second));
}

/**
 * Transfer the range [it_begin, it_end) to position it_pos.
 */
void _list_transfer(list_iterator_t it_pos, list_iterator_t it_begin, list_iterator_t it_end)
{
    assert(_list_iterator_belong_to_list(_GET_LIST_CONTAINER(it_pos), it_pos));
    assert(_list_iterator_belong_to_list(_GET_LIST_CONTAINER(it_begin), it_begin));
    assert(_list_iterator_belong_to_list(_GET_LIST_CONTAINER(it_end), it_end));
    assert(_GET_LIST_CONTAINER(it_begin) == _GET_LIST_CONTAINER(it_end));
    assert(iterator_equal(it_begin, it_end) || _list_iterator_before(it_begin, it_end));
    assert(_list_same_list_iterator_type(_GET_LIST_CONTAINER(it_pos), it_begin));

    /* empty range */
    if(iterator_equal(it_begin, it_end))
    {
        return;
    }

    /* same list container */
    if(_GET_LIST_CONTAINER(it_pos) == _GET_LIST_CONTAINER(it_begin))
    {
        assert(iterator_equal(it_pos, it_begin) || iterator_equal(it_pos, it_end) ||
               _list_iterator_before(it_pos, it_begin) || _list_iterator_before(it_end, it_pos));

        if(iterator_equal(it_pos, it_begin) || iterator_equal(it_pos, it_end))
        {
            return;
        }
    }

    /* insert the range [it_begin, it_end) to dest list */
    list_insert_range(_GET_LIST_CONTAINER(it_pos), it_pos, it_begin, it_end);
    /* delete the range [it_begin, it_end) front the source list */
    list_erase_range(_GET_LIST_CONTAINER(it_begin), it_begin, it_end);
}

/**
 * Sort the range [pt_first, pt_last] use the quick sort algorithm.
 */
void _list_quick_sort(list_t* plist_list, listnode_t* pt_first, listnode_t* pt_last, binary_function_t t_binary_op)
{
    listnode_t* pt_beforefirst = NULL;
    listnode_t* pt_afterlast = NULL;
    listnode_t* pt_pivot = NULL;
    listnode_t* pt_before = NULL;
    listnode_t* pt_after = NULL;
    bool_t      b_less = false;
    bool_t      b_greater = false;

#ifndef NDEBUG
    list_iterator_t it_first = _create_list_iterator();
    list_iterator_t it_last = _create_list_iterator();
#endif
    assert(plist_list != NULL);
    assert(pt_first != NULL);
    assert(pt_last != NULL);
    assert(_list_is_inited(plist_list));
#ifndef NDEBUG
    _GET_CONTAINER(it_first) = plist_list;
    _GET_LIST_COREPOS(it_first) = pt_first;
    _GET_CONTAINER(it_last) = plist_list;
    _GET_LIST_COREPOS(it_last) = pt_last;
    assert(_list_iterator_belong_to_list(plist_list, it_first));
    assert(_list_iterator_belong_to_list(plist_list, it_last));
    assert(iterator_equal(it_first, it_last) || _list_iterator_before(it_first, it_last));
#endif

    if(pt_first == pt_last)
    {
        return;
    }

    if(t_binary_op == NULL)
    {
        t_binary_op = _GET_LIST_TYPE_LESS_FUNCTION(plist_list);
        pt_beforefirst = pt_first->_pt_prev;
        pt_afterlast = pt_last->_pt_next;
        for(pt_pivot = pt_last, pt_before = pt_first->_pt_prev, pt_after = pt_first;
            pt_after != pt_pivot;
            pt_after = pt_after->_pt_next)
        {
            (*t_binary_op)(pt_after->_pc_data, pt_pivot->_pc_data, &b_less);
            (*t_binary_op)(pt_pivot->_pc_data, pt_after->_pc_data, &b_greater);
            if(b_less || (!b_less && !b_greater))
            {
                pt_before = pt_before->_pt_next;
                _list_swap_node(&pt_before, &pt_after);
            }
        }
        pt_before = pt_before->_pt_next;
        _list_swap_node(&pt_before, &pt_pivot);
        pt_pivot = pt_before;

        /* pivot is not the first node */
        if(pt_pivot->_pt_prev != pt_beforefirst)
        {
            _list_quick_sort(plist_list, pt_beforefirst->_pt_next, pt_pivot->_pt_prev, t_binary_op);
        }
        /* pivot is not the last node */
        if(pt_pivot->_pt_next != pt_afterlast)
        {
            _list_quick_sort(plist_list, pt_pivot->_pt_next, pt_afterlast->_pt_prev, t_binary_op);
        }
    }
    else
    {
        if(strncmp(_GET_LIST_TYPE_BASENAME(plist_list), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
        {
            pt_beforefirst = pt_first->_pt_prev;
            pt_afterlast = pt_last->_pt_next;
            for(pt_pivot = pt_last, pt_before = pt_first->_pt_prev, pt_after = pt_first;
                pt_after != pt_pivot;
                pt_after = pt_after->_pt_next)
            {
                (*t_binary_op)(
                    string_c_str((string_t*)pt_after->_pc_data), string_c_str((string_t*)pt_pivot->_pc_data), &b_less);
                (*t_binary_op)(
                    string_c_str((string_t*)pt_pivot->_pc_data), string_c_str((string_t*)pt_after->_pc_data), &b_greater);
                if(b_less || (!b_less && !b_greater))
                {
                    pt_before = pt_before->_pt_next;
                    _list_swap_node(&pt_before, &pt_after);
                }
            }
            pt_before = pt_before->_pt_next;
            _list_swap_node(&pt_before, &pt_pivot);
            pt_pivot = pt_before;

            /* pivot is not the first node */
            if(pt_pivot->_pt_prev != pt_beforefirst)
            {
                _list_quick_sort(plist_list, pt_beforefirst->_pt_next, pt_pivot->_pt_prev, t_binary_op);
            }
            /* pivot is not the last node */
            if(pt_pivot->_pt_next != pt_afterlast)
            {
                _list_quick_sort(plist_list, pt_pivot->_pt_next, pt_afterlast->_pt_prev, t_binary_op);
            }
        }
        else
        {
            pt_beforefirst = pt_first->_pt_prev;
            pt_afterlast = pt_last->_pt_next;
            for(pt_pivot = pt_last, pt_before = pt_first->_pt_prev, pt_after = pt_first;
                pt_after != pt_pivot;
                pt_after = pt_after->_pt_next)
            {
                (*t_binary_op)(pt_after->_pc_data, pt_pivot->_pc_data, &b_less);
                (*t_binary_op)(pt_pivot->_pc_data, pt_after->_pc_data, &b_greater);
                if(b_less || (!b_less && !b_greater))
                {
                    pt_before = pt_before->_pt_next;
                    _list_swap_node(&pt_before, &pt_after);
                }
            }
            pt_before = pt_before->_pt_next;
            _list_swap_node(&pt_before, &pt_pivot);
            pt_pivot = pt_before;

            /* pivot is not the first node */
            if(pt_pivot->_pt_prev != pt_beforefirst)
            {
                _list_quick_sort(plist_list, pt_beforefirst->_pt_next, pt_pivot->_pt_prev, t_binary_op);
            }
            /* pivot is not the last node */
            if(pt_pivot->_pt_next != pt_afterlast)
            {
                _list_quick_sort(plist_list, pt_pivot->_pt_next, pt_afterlast->_pt_prev, t_binary_op);
            }
        }
    }
}

/**
 * Swap the two node content and don't change the pointer.
 */
void _list_swap_node(listnode_t** ppt_first, listnode_t** ppt_second)
{
    listnode_t* pt_afterfirst = NULL;   /* the position after first */
    listnode_t* pt_aftersecond = NULL;  /* the position after second */

    assert(ppt_first != NULL && *ppt_first != NULL);
    assert(ppt_second != NULL && *ppt_second != NULL);

    /* if the first node equal to the second */
    if(*ppt_first == *ppt_second)
    {
        return;
    }
    /* if the first followed by the second */
    else if((*ppt_first)->_pt_next == (*ppt_second))
    {
        /* extra the first node */
        (*ppt_second)->_pt_prev = (*ppt_first)->_pt_prev;
        (*ppt_first)->_pt_prev->_pt_next = (*ppt_second);
        /* insert first node into position after second node */
        (*ppt_first)->_pt_next = (*ppt_second)->_pt_next;
        (*ppt_first)->_pt_prev = (*ppt_second);
        (*ppt_second)->_pt_next->_pt_prev = (*ppt_first);
        (*ppt_second)->_pt_next = (*ppt_first);

        (*ppt_first) = (*ppt_second);
        (*ppt_second) = (*ppt_second)->_pt_next;
    }
    /* if the second followed by the first */
    else if((*ppt_second)->_pt_next == (*ppt_first))
    {
        /* extra the second node */
        (*ppt_first)->_pt_prev = (*ppt_second)->_pt_prev;
        (*ppt_second)->_pt_prev->_pt_next = (*ppt_first);
        /* insert second node into position after first node */
        (*ppt_second)->_pt_next = (*ppt_first)->_pt_next;
        (*ppt_second)->_pt_prev = (*ppt_first);
        (*ppt_first)->_pt_next->_pt_prev = (*ppt_second);
        (*ppt_first)->_pt_next = (*ppt_second);

        (*ppt_second) = (*ppt_first);
        (*ppt_first) = (*ppt_first)->_pt_next;
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

/**
 * Obtain data from variable argument list, the data type and list element data type are same.
 */
void _list_get_varg_value_auxiliary(list_t* plist_list, va_list val_elemlist, listnode_t* pt_node)
{
    assert(plist_list != NULL);
    assert(pt_node != NULL);
    assert(_list_is_inited(plist_list) || _list_is_created(plist_list));

    _list_init_node_auxiliary(plist_list, pt_node);
    _type_get_varg_value(&plist_list->_t_typeinfo, val_elemlist, pt_node->_pc_data);
}

/**
 * Destroy data, the data type and list element data type are same.
 */
void _list_destroy_varg_value_auxiliary(list_t* plist_list, listnode_t* pt_node)
{
    assert(plist_list != NULL);
    assert(pt_node != NULL);
    assert(_list_is_inited(plist_list) || _list_is_created(plist_list));

    bool_t b_result = _GET_LIST_TYPE_SIZE(plist_list);
    _GET_LIST_TYPE_DESTROY_FUNCTION(plist_list)(pt_node->_pc_data, &b_result);
    assert(b_result);
}

/**
 * Initialize list node auxiliary function.
 */
void _list_init_node_auxiliary(list_t* plist_list, listnode_t* pt_node)
{
    assert(plist_list != NULL);
    assert(pt_node != NULL);
    assert(_list_is_inited(plist_list) || _list_is_created(plist_list));

    _list_init_elem_auxiliary(plist_list, pt_node->_pc_data);
}

/** local function implementation section **/

/** eof **/

