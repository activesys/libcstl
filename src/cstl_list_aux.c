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
bool_t _list_iterator_belong_to_list(
    const list_t* cpt_list, list_iterator_t t_iter)
{
    listnode_t* pt_listnode = NULL;  /* the list node pointer */

    assert(cpt_list != NULL);
    assert(cpt_list->_pt_node != NULL);
    assert(_GET_LIST_COREPOS(t_iter) != NULL);
    assert(_GET_LIST_CONTAINER(t_iter) == cpt_list);
    assert(t_iter._t_containertype == _LIST_CONTAINER);
    assert(t_iter._t_iteratortype == _BIDIRECTIONAL_ITERATOR);

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

bool_t _list_same_list_iterator_type(
    const list_t* cpt_list, list_iterator_t t_iter)
{
    assert(cpt_list != NULL && _GET_LIST_CONTAINER(t_iter) != NULL);
    assert(_GET_LIST_CONTAINER_TYPE(t_iter) == _LIST_CONTAINER &&
           _GET_LIST_ITERATOR_TYPE(t_iter) == _BIDIRECTIONAL_ITERATOR);
    return _list_same_type(cpt_list, _GET_LIST_CONTAINER(t_iter));
}
#endif /* NDEBUG */

bool_t _list_same_type(const list_t* cpt_listfirst, const list_t* cpt_listsecond)
{
    assert(cpt_listfirst != NULL && cpt_listsecond != NULL);
    return _type_is_same(_GET_LIST_TYPE_NAME(cpt_listfirst),
                         _GET_LIST_TYPE_NAME(cpt_listsecond)) &&
           (cpt_listfirst->_t_typeinfo._pt_type == cpt_listsecond->_t_typeinfo._pt_type) &&
           (cpt_listfirst->_t_typeinfo._t_style == cpt_listsecond->_t_typeinfo._t_style);
}

void _transfer(
    list_iterator_t t_pos, list_iterator_t t_begin, list_iterator_t t_end)
{
    /* insert the range [t_begin, t_end) to dest list */
    list_insert_range(_GET_LIST_CONTAINER(t_pos), t_pos, t_begin, t_end);
    /* delete the range [t_begin, t_end) front the source list */
    list_erase_range(_GET_LIST_CONTAINER(t_begin), t_begin, t_end);
}

void _quick_sort(
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
        t_beforepivot = _create_list_iterator();
        _GET_CONTAINER(t_beforepivot) = _GET_CONTAINER(t_firstpos);
        _GET_LIST_COREPOS(t_beforepivot) = _GET_LIST_COREPOS(t_firstpos);
        t_afterpivot = _create_list_iterator();
        _GET_CONTAINER(t_afterpivot) = _GET_CONTAINER(t_lastpos);
        _GET_LIST_COREPOS(t_afterpivot) = _GET_LIST_COREPOS(t_lastpos);
        t_pivotpos = _create_list_iterator();
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

void _swap_node(listnode_t** ppt_first, listnode_t** ppt_second)
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

void _list_get_varg_value_auxiliary(
    list_t* pt_list, va_list val_elemlist, listnode_t* pt_node)
{
    _list_init_node_auxiliary(pt_list, pt_node);
    _type_get_varg_value(&pt_list->_t_typeinfo, val_elemlist, pt_node->_pc_data);
}

void _list_destroy_varg_value_auxiliary(list_t* pt_list, listnode_t* pt_node)
{
    bool_t t_result = _GET_LIST_TYPE_SIZE(pt_list);
    _GET_LIST_TYPE_DESTROY_FUNCTION(pt_list)(pt_node->_pc_data, &t_result);
    assert(t_result);
}

void _list_init_node_auxiliary(list_t* pt_list, listnode_t* pt_node)
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

/** local function implementation section **/

/** eof **/

