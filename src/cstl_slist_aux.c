/*
 *  The implementation of slist auxiliary functions.
 *  Copyright (C)  2008 - 2012  Wangbo
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
#include <cstl/citerator.h>
#include <cstl/cfunctional.h>
#include <cstl/cstring.h>
#include <cstl/cslist.h>

#include "cstl_slist_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
#ifndef NDEBUG
/**
 * Test iterator referenced data is within the slist.
 */
bool_t _slist_iterator_belong_to_slist(const slist_t* cpslist_slist, slist_iterator_t it_iter)
{
    _slistnode_t* pt_node = NULL;

    assert(cpslist_slist != NULL);
    assert(_slist_is_inited(cpslist_slist));
    assert(_SLIST_ITERATOR_CONTAINER(it_iter) == cpslist_slist);
    assert(_SLIST_ITERATOR_CONTAINER_TYPE(it_iter) == _SLIST_CONTAINER);
    assert(_SLIST_ITERATOR_ITERATOR_TYPE(it_iter) == _FORWARD_ITERATOR);

    /* the end iterator of slist corepos is NULL */
    if (_SLIST_ITERATOR_COREPOS(it_iter) == NULL) {
        return true;
    }

    for (pt_node = cpslist_slist->_t_head._pt_next; pt_node != NULL; pt_node = pt_node->_pt_next) {
        if (pt_node == (_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_iter)) {
            return true;
        }
    }

    return false;
}

/**
 * Test the type that saved in the slist container and referenced by it_iter are same.
 */
bool_t _slist_same_slist_iterator_type(const slist_t* cpslist_slist, slist_iterator_t it_iter)
{
    assert(cpslist_slist != NULL);
    assert(_SLIST_ITERATOR_CONTAINER(it_iter) != NULL);
    assert(_SLIST_ITERATOR_CONTAINER_TYPE(it_iter) == _SLIST_CONTAINER);
    assert(_SLIST_ITERATOR_ITERATOR_TYPE(it_iter) == _FORWARD_ITERATOR);

    return _slist_same_type(cpslist_slist, _SLIST_ITERATOR_CONTAINER(it_iter));
}

/**
 * Test the type that saved in the slist container and referenced by it_iter are same.
 */
bool_t _slist_same_iterator_type(const slist_t* cpslist_slist, iterator_t it_iter)
{
    assert(cpslist_slist != NULL);
    assert(_slist_is_inited(cpslist_slist) || _slist_is_created(cpslist_slist));
    assert(_iterator_is_valid(it_iter));

    return _type_is_same_ex(&cpslist_slist->_t_typeinfo, _iterator_get_typeinfo(it_iter));
}

/**
 * Test slist is created by create_slist.
 */
bool_t _slist_is_created(const slist_t* cpslist_slist)
{
    assert(cpslist_slist != NULL);

    if (cpslist_slist->_t_typeinfo._t_style != _TYPE_C_BUILTIN &&
        cpslist_slist->_t_typeinfo._t_style != _TYPE_CSTL_BUILTIN &&
        cpslist_slist->_t_typeinfo._t_style != _TYPE_USER_DEFINE) {
        return false;
    }

    if (cpslist_slist->_t_typeinfo._pt_type == NULL) {
        return false;
    }

    if (cpslist_slist->_t_head._pt_next != NULL) {
        return false;
    }

    return _alloc_is_inited(&cpslist_slist->_t_allocator);
}

/**
 * Test slist is initialized.
 */
bool_t _slist_is_inited(const slist_t* cpslist_slist)
{
    assert(cpslist_slist != NULL);

    if (cpslist_slist->_t_typeinfo._t_style != _TYPE_C_BUILTIN &&
        cpslist_slist->_t_typeinfo._t_style != _TYPE_CSTL_BUILTIN &&
        cpslist_slist->_t_typeinfo._t_style != _TYPE_USER_DEFINE) {
        return false;
    }

    if (cpslist_slist->_t_typeinfo._pt_type == NULL) {
        return false;
    }

    return true;
}
#endif /* NDEBUG */

/**
 * Test the type that saved in the slist container is same.
 */
bool_t _slist_same_type(const slist_t* cpslist_first, const slist_t* cpslist_second)
{
    assert(cpslist_first != NULL);
    assert(cpslist_second != NULL);
    assert(_slist_is_inited(cpslist_first) || _slist_is_created(cpslist_first));
    assert(_slist_is_inited(cpslist_second) || _slist_is_created(cpslist_second));

    if (cpslist_first == cpslist_second) {
        return true;
    }

    return (cpslist_first->_t_typeinfo._pt_type == cpslist_second->_t_typeinfo._pt_type) &&
           (cpslist_first->_t_typeinfo._t_style == cpslist_second->_t_typeinfo._t_style) &&
           _type_is_same(_GET_SLIST_TYPE_NAME(cpslist_first), _GET_SLIST_TYPE_NAME(cpslist_second));
}

/**
 * Transfer the range [it_begin, it_end) to position it_pos+1.
 */
void _slist_transfer_after(slist_iterator_t it_pos, slist_iterator_t it_begin, slist_iterator_t it_end)
{
    assert(_slist_iterator_belong_to_slist(_SLIST_ITERATOR_CONTAINER(it_pos), it_pos));
    assert(!iterator_equal(it_pos, slist_end(_SLIST_ITERATOR_CONTAINER(it_pos))));
    assert(_slist_iterator_belong_to_slist(_SLIST_ITERATOR_CONTAINER(it_begin), it_begin));
    assert(_slist_iterator_belong_to_slist(_SLIST_ITERATOR_CONTAINER(it_end), it_end));
    assert(_SLIST_ITERATOR_CONTAINER(it_begin) == _SLIST_ITERATOR_CONTAINER(it_end));
    assert(iterator_equal(it_begin, it_end) || _slist_iterator_before(it_begin, it_end));
    assert(_slist_same_slist_iterator_type(_SLIST_ITERATOR_CONTAINER(it_pos), it_begin));

    /* empty range */
    if (iterator_equal(it_begin, it_end)) {
        return;
    }

    /* same slist container */
    if (_SLIST_ITERATOR_CONTAINER(it_pos) == _SLIST_ITERATOR_CONTAINER(it_begin)) {
        iterator_t it_iter = iterator_next(it_pos);

        assert(iterator_equal(it_iter, it_begin) || iterator_equal(it_iter, it_end) ||
               _slist_iterator_before(it_iter, it_begin) || _slist_iterator_before(it_end, it_iter));

        if (iterator_equal(it_iter, it_begin) || iterator_equal(it_iter, it_end)) {
            return;
        }
    }

    slist_insert_after_range(_SLIST_ITERATOR_CONTAINER(it_pos), it_pos, it_begin, it_end);
    slist_erase_range(_SLIST_ITERATOR_CONTAINER(it_begin), it_begin, it_end);
}

/**
 * Transfer the range [it_begin, it_end) to position it_pos.
 */
void _slist_transfer(slist_iterator_t it_pos, slist_iterator_t it_begin, slist_iterator_t it_end)
{
    assert(_slist_iterator_belong_to_slist(_SLIST_ITERATOR_CONTAINER(it_pos), it_pos));
    assert(_slist_iterator_belong_to_slist(_SLIST_ITERATOR_CONTAINER(it_begin), it_begin));
    assert(_slist_iterator_belong_to_slist(_SLIST_ITERATOR_CONTAINER(it_end), it_end));
    assert(_SLIST_ITERATOR_CONTAINER(it_begin) == _SLIST_ITERATOR_CONTAINER(it_end));
    assert(iterator_equal(it_begin, it_end) || _slist_iterator_before(it_begin, it_end));
    assert(_slist_same_slist_iterator_type(_SLIST_ITERATOR_CONTAINER(it_pos), it_begin));

    /* empty range */
    if (iterator_equal(it_begin, it_end)) {
        return;
    }

    /* same slist container */
    if (_SLIST_ITERATOR_CONTAINER(it_pos) == _SLIST_ITERATOR_CONTAINER(it_begin)) {
        assert(iterator_equal(it_pos, it_begin) || iterator_equal(it_pos, it_end) ||
               _slist_iterator_before(it_pos, it_begin) || _slist_iterator_before(it_end, it_pos));

        if (iterator_equal(it_pos, it_begin) || iterator_equal(it_pos, it_end)) {
            return;
        }
    }

    slist_insert_range(_SLIST_ITERATOR_CONTAINER(it_pos), it_pos, it_begin, it_end);
    slist_erase_range(_SLIST_ITERATOR_CONTAINER(it_begin), it_begin, it_end);
}

/**
 * Obtain data from variable argument slist, the data type and slist element data type are same.
 */
void _slist_get_varg_value_auxiliary(slist_t* pslist_slist, va_list val_elemlist, _slistnode_t* pt_node)
{
    assert(pslist_slist != NULL);
    assert(pt_node != NULL);
    assert(_slist_is_inited(pslist_slist) || _slist_is_created(pslist_slist));

    _slist_init_node_auxiliary(pslist_slist, pt_node);
    _type_get_varg_value(&pslist_slist->_t_typeinfo, val_elemlist, pt_node->_pby_data);
}

/**
 * Destroy data, the data type and slist element data type are same.
 */
void _slist_destroy_varg_value_auxiliary(slist_t* pslist_slist, _slistnode_t* pt_node)
{
    bool_t b_result = false;

    assert(pslist_slist != NULL);
    assert(pt_node != NULL);
    assert(_slist_is_inited(pslist_slist) || _slist_is_created(pslist_slist));

    b_result = _GET_SLIST_TYPE_SIZE(pslist_slist);
    _GET_SLIST_TYPE_DESTROY_FUNCTION(pslist_slist)(pt_node->_pby_data, &b_result);
    assert(b_result);
}

/**
 * Initialize slist node auxiliary function.
 */
void _slist_init_node_auxiliary(slist_t* pslist_slist, _slistnode_t* pt_node)
{
    assert(pslist_slist != NULL);
    assert(pt_node != NULL);
    assert(_slist_is_inited(pslist_slist) || _slist_is_created(pslist_slist));

    /* initialize new elements */
    if (_GET_SLIST_TYPE_STYLE(pslist_slist) == _TYPE_CSTL_BUILTIN) {
        /* get element type name */
        char s_elemtypename[_TYPE_NAME_SIZE + 1];
        _type_get_elem_typename(_GET_SLIST_TYPE_NAME(pslist_slist), s_elemtypename);

        _GET_SLIST_TYPE_INIT_FUNCTION(pslist_slist)(pt_node->_pby_data, s_elemtypename);
    } else {
        bool_t b_result = _GET_SLIST_TYPE_SIZE(pslist_slist);
        _GET_SLIST_TYPE_INIT_FUNCTION(pslist_slist)(pt_node->_pby_data, &b_result);
        assert(b_result);
    }
}

/** local function implementation section **/

/** eof **/

