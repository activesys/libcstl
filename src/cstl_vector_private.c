/*
 *  The implement of vector private interface.
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

#include <cstl/cstl_vector_iterator.h>
#include <cstl/cstl_vector_private.h>

#include <cstl/cstring.h>

#include "cstl_vector_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Create vector container.
 */
vector_t* _create_vector(const char* s_typename)
{
    vector_t*   pvec_vector = NULL;

    /* allocate for vector_t and initialize it */
    if((pvec_vector = (vector_t*)malloc(sizeof(vector_t))) == NULL)
    {
        return NULL;
    }

    if(!_create_vector_auxiliary(pvec_vector, s_typename))
    {
        free(pvec_vector);
        return NULL;
    }

    return pvec_vector;
}

/**
 * Create vector container auxiliary function.
 */
bool_t _create_vector_auxiliary(vector_t* pvec_vector, const char* s_typename)
{
    assert(pvec_vector != NULL);
    assert(s_typename != NULL);

    _type_get_type(&pvec_vector->_t_typeinfo, s_typename);
    if(pvec_vector->_t_typeinfo._t_style == _TYPE_INVALID)
    {
        return false;
    }

    pvec_vector->_pc_start = NULL;
    pvec_vector->_pc_finish = NULL;
    pvec_vector->_pc_endofstorage = NULL;

    _alloc_init(&pvec_vector->_t_allocater);
    return true;
}

/**
 * Initialize vector with specified element.
 */
void _vector_init_elem(vector_t* pvec_vector, size_t t_count, ...)
{
    va_list val_elemlist;

    assert(pvec_vector != NULL);

    va_start(val_elemlist, t_count);
    _vector_init_elem_varg(pvec_vector, t_count, val_elemlist);
    va_end(val_elemlist);
}

/**
 * Initialize vector with variable argument list of specified element.
 */
void _vector_init_elem_varg(vector_t* pvec_vector, size_t t_count, va_list val_elemlist)
{
    void*             pv_varg = NULL;
    bool_t            b_result = false;
    vector_iterator_t it_iter;

    assert(pvec_vector != NULL);

    /* initialize vector_t */
    vector_init_n(pvec_vector, t_count);
    if(t_count > 0)
    {
        /* get varg value only once */
        pv_varg = _alloc_allocate(&pvec_vector->_t_allocater, _GET_VECTOR_TYPE_SIZE(pvec_vector), 1);
        assert(pv_varg != NULL);
        _vector_get_varg_value_auxiliary(pvec_vector, val_elemlist, pv_varg);

        /* copy varg value to each element */
        for(it_iter = vector_begin(pvec_vector);
            !iterator_equal(it_iter, vector_end(pvec_vector));
            it_iter = iterator_next(it_iter))
        {
            /* copy from varg */
            b_result = _GET_VECTOR_TYPE_SIZE(pvec_vector);
            _GET_VECTOR_TYPE_COPY_FUNCTION(pvec_vector)(_GET_VECTOR_COREPOS(it_iter), pv_varg, &b_result);
            assert(b_result);
        }

        /* destroy varg value and free memory */
        _vector_destroy_varg_value_auxiliary(pvec_vector, pv_varg);
        _alloc_deallocate(&pvec_vector->_t_allocater, pv_varg, _GET_VECTOR_TYPE_SIZE(pvec_vector), 1);
    }
}

/**
 * Destroy vector container auxiliary function.
 */
void _vector_destroy_auxiliary(vector_t* pvec_vector)
{
    vector_iterator_t it_iter;
    bool_t            b_result = false;

    assert(pvec_vector != NULL);
    assert(pvec_vector->_pc_finish - pvec_vector->_pc_start >= 0);
    assert(pvec_vector->_pc_endofstorage - pvec_vector->_pc_start >= 0);
    
    /* destroy all elements */
    for(it_iter = vector_begin(pvec_vector);
        !iterator_equal(it_iter, vector_end(pvec_vector));
        it_iter = iterator_next(it_iter))
    {
        b_result = _GET_VECTOR_TYPE_SIZE(pvec_vector);
        _GET_VECTOR_TYPE_DESTROY_FUNCTION(pvec_vector)(_GET_VECTOR_COREPOS(it_iter), &b_result);
        assert(b_result);
    }
    /* free vector memory */
    if(pvec_vector->_pc_start != NULL)
    {
        _alloc_deallocate(&pvec_vector->_t_allocater, pvec_vector->_pc_start, _GET_VECTOR_TYPE_SIZE(pvec_vector), 
            (pvec_vector->_pc_endofstorage - pvec_vector->_pc_start) / _GET_VECTOR_TYPE_SIZE(pvec_vector));
    }
    _alloc_destroy(&pvec_vector->_t_allocater);

    pvec_vector->_pc_start = NULL;
    pvec_vector->_pc_finish = NULL;
    pvec_vector->_pc_endofstorage = NULL;
}

/**
 * Assign vector with specificed element.
 */
void _vector_assign_elem(vector_t* pt_vector, size_t t_count, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_count);
    _vector_assign_elem_varg(pt_vector, t_count, val_elemlist);
    va_end(val_elemlist);
}

/**
 * Assign vector with variable argument list of specificed element.
 */
void _vector_assign_elem_varg(
    vector_t* pt_vector, size_t t_count, va_list val_elemlist)
{
    iterator_t t_iter;
    bool_t     t_result = false;
    void*      pv_varg = NULL;

    assert(pt_vector != NULL);

    /* get value from varg */
    pv_varg = _alloc_allocate(&pt_vector->_t_allocater, _GET_VECTOR_TYPE_SIZE(pt_vector), 1);
    assert(pv_varg != NULL);
    _vector_get_varg_value_auxiliary(pt_vector, val_elemlist, pv_varg);

    /* copy value from varg for each element */
    vector_resize(pt_vector, t_count);
    for(t_iter = vector_begin(pt_vector);
        !iterator_equal(t_iter, vector_end(pt_vector));
        t_iter = iterator_next(t_iter))
    {
        t_result = _GET_VECTOR_TYPE_SIZE(pt_vector);
        _GET_VECTOR_TYPE_COPY_FUNCTION(pt_vector)(
            _GET_VECTOR_COREPOS(t_iter), pv_varg, &t_result);
        assert(t_result);
    }

    /* destroy varg and free memory */
    _vector_destroy_varg_value_auxiliary(pt_vector, pv_varg);
    _alloc_deallocate(&pt_vector->_t_allocater, pv_varg, _GET_VECTOR_TYPE_SIZE(pt_vector), 1);
}

void _vector_push_back(vector_t* pt_vector, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, pt_vector);
    _vector_push_back_varg(pt_vector, val_elemlist);
    va_end(val_elemlist);
}

void _vector_push_back_varg(vector_t* pt_vector, va_list val_elemlist)
{
    char*  pc_last = NULL;

    assert(pt_vector != NULL);

    /* if the remain capacity is less then the element count */
    if(vector_capacity(pt_vector) == vector_size(pt_vector)) 
    {
        /* reserve the new size = old size + 2 */
        vector_reserve(pt_vector, vector_size(pt_vector) + 2);
    }

    /* initialize the last element */
    pc_last = pt_vector->_pc_finish;
    assert(pc_last != NULL);
    pt_vector->_pc_finish += _GET_VECTOR_TYPE_SIZE(pt_vector);
    _vector_init_elem_auxiliary(pt_vector, pc_last);
    /* copy value from varg */
    _type_get_varg_value(&pt_vector->_t_typeinfo, val_elemlist, pc_last);
}

void _vector_resize_elem(vector_t* pt_vector, size_t t_resize, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_resize);
    _vector_resize_elem_varg(pt_vector, t_resize, val_elemlist);
    va_end(val_elemlist);
}

void _vector_resize_elem_varg(
    vector_t* pt_vector, size_t t_resize, va_list val_elemlist)
{
    vector_iterator_t t_cutpos;     /* the cut position */
    size_t            t_expsize = 0;
    size_t            t_index = 0;
    void*             pv_varg = NULL;
    char*             pc_oldfinish = NULL;
    bool_t            t_result = false;

    assert(pt_vector != NULL);

    if(t_resize == vector_size(pt_vector))
    {
        return;
    }
    else if(t_resize < vector_size(pt_vector))
    {
        t_cutpos = vector_begin(pt_vector);
        t_cutpos = iterator_next_n(t_cutpos, t_resize);
        vector_erase_range(pt_vector, t_cutpos, vector_end(pt_vector));
    }
    else
    {
        t_expsize = t_resize - vector_size(pt_vector);
        if(t_resize > vector_capacity(pt_vector))
        {
            vector_reserve(pt_vector, vector_size(pt_vector) + 2 * t_expsize);
        }

        /* get varg value only once */
        pv_varg = _alloc_allocate(&pt_vector->_t_allocater, _GET_VECTOR_TYPE_SIZE(pt_vector), 1);
        assert(pv_varg != NULL);
        _vector_get_varg_value_auxiliary(pt_vector, val_elemlist, pv_varg);

        /* initialize new elements */
        pc_oldfinish = pt_vector->_pc_finish;
        pt_vector->_pc_finish += t_expsize * _GET_VECTOR_TYPE_SIZE(pt_vector);
        _vector_init_elem_range_auxiliary(pt_vector, pc_oldfinish, pt_vector->_pc_finish);
        /* copy value from varg to new elements */
        for(t_index = 0; t_index < t_expsize; ++t_index)
        {
            t_result = _GET_VECTOR_TYPE_SIZE(pt_vector);
            _GET_VECTOR_TYPE_COPY_FUNCTION(pt_vector)(
                pc_oldfinish + t_index * _GET_VECTOR_TYPE_SIZE(pt_vector),
                pv_varg, &t_result);
            assert(t_result);
        }
        /* destroy varg */
        _vector_destroy_varg_value_auxiliary(pt_vector, pv_varg);
        _alloc_deallocate(&pt_vector->_t_allocater, pv_varg, _GET_VECTOR_TYPE_SIZE(pt_vector), 1);
    }
}

vector_iterator_t _vector_insert_n(
    vector_t* pt_vector, vector_iterator_t t_pos, size_t t_count, ...)
{
    vector_iterator_t t_iter;
    va_list val_elemlist;

    va_start(val_elemlist, t_count);
    t_iter = _vector_insert_n_varg(pt_vector, t_pos, t_count, val_elemlist);
    va_end(val_elemlist);

    return t_iter;
}

vector_iterator_t _vector_insert_n_varg(
    vector_t* pt_vector, vector_iterator_t t_pos, size_t t_count, va_list val_elemlist)
{
    void*  pv_varg = NULL;
    bool_t t_result = false;

    /* test the vector and iterator is valid */
    assert(_vector_iterator_belong_to_vector(pt_vector, t_pos));

    if(t_count > 0)
    {
        size_t t_index = 0;
        char*  pc_oldfinish = NULL;
        char*  pc_pos = NULL;   /* for initialize elments and insert elements */
        char*  pc_destpos = NULL;

        /* if the remain capacity is less then the element count */
        if(vector_size(pt_vector) + t_count > vector_capacity(pt_vector))
        {
            size_t t_insertpos = iterator_distance(vector_begin(pt_vector), t_pos);
            /* reserve the new size */
            /* new size = old size + 2 * element count */
            vector_reserve(pt_vector, vector_size(pt_vector) + 2 * t_count);
            t_pos = iterator_next_n(vector_begin(pt_vector), t_insertpos);
        }

        /* insert the element counts of element to the position */
        /* 
         * move the elements from pos to the finish of vector to the 
         * memory that after the pos element count.
         * +-----------------------------------------+
         * |          |             |                |
         * +-----------------------------------------+
         * ^          ^             ^
         * |          |             |
         * start     t_pos         finish
         *                           _t_count__
         *                          /          \
         * +-----------------------------------------+
         * |          |             |new element|    |
         * +-----------------------------------------+
         * ^          ^             ^           ^
         * |          |             |           |
         * start     t_pos       pc_oldfinish  finish
         */
        /* initialize new elements */
        pc_oldfinish = pt_vector->_pc_finish;
        assert(pc_oldfinish != NULL);
        pt_vector->_pc_finish += t_count * _GET_VECTOR_TYPE_SIZE(pt_vector);
        _vector_init_elem_range_auxiliary(pt_vector, pc_oldfinish, pt_vector->_pc_finish);
        /* move element from old finish to new finish */
        for(pc_pos = pc_oldfinish - _GET_VECTOR_TYPE_SIZE(pt_vector),
            pc_destpos = pt_vector->_pc_finish - _GET_VECTOR_TYPE_SIZE(pt_vector);
            pc_pos >= _GET_VECTOR_COREPOS(t_pos);
            pc_pos -= _GET_VECTOR_TYPE_SIZE(pt_vector),
            pc_destpos -= _GET_VECTOR_TYPE_SIZE(pt_vector))
        {
            t_result = _GET_VECTOR_TYPE_SIZE(pt_vector);
            _GET_VECTOR_TYPE_COPY_FUNCTION(pt_vector)(pc_destpos, pc_pos, &t_result);
            assert(t_result);
        }

        /* get varg value only once */
        pv_varg = _alloc_allocate(&pt_vector->_t_allocater, _GET_VECTOR_TYPE_SIZE(pt_vector), 1);
        assert(pv_varg != NULL);
        _vector_get_varg_value_auxiliary(pt_vector, val_elemlist, pv_varg);
        /* copy value for varg */
        for(t_index = 0; t_index < t_count; ++t_index)
        {
            t_result = _GET_VECTOR_TYPE_SIZE(pt_vector);
            _GET_VECTOR_TYPE_COPY_FUNCTION(pt_vector)(
                _GET_VECTOR_COREPOS(t_pos) + t_index * _GET_VECTOR_TYPE_SIZE(pt_vector),
                pv_varg, &t_result);
            assert(t_result);
        }
        /* destroy varg and free memory */
        _vector_destroy_varg_value_auxiliary(pt_vector, pv_varg);
        _alloc_deallocate(&pt_vector->_t_allocater, pv_varg, _GET_VECTOR_TYPE_SIZE(pt_vector), 1);

        t_pos = iterator_next_n(t_pos, t_count);
    }

    return t_pos;
}

void _vector_init_elem_auxiliary(vector_t* pt_vector, void* pv_elem)
{
    assert(pt_vector != NULL && pv_elem != NULL);

    /* initialize new elements */
    if(_GET_VECTOR_TYPE_STYLE(pt_vector) == _TYPE_CSTL_BUILTIN)
    {
        /* get element type name */
        char s_elemtypename[_TYPE_NAME_SIZE + 1];
        _type_get_elem_typename(_GET_VECTOR_TYPE_NAME(pt_vector), s_elemtypename);

        _GET_VECTOR_TYPE_INIT_FUNCTION(pt_vector)(pv_elem, s_elemtypename);
    }
    else
    {
        bool_t t_result = _GET_VECTOR_TYPE_SIZE(pt_vector);
        _GET_VECTOR_TYPE_INIT_FUNCTION(pt_vector)(pv_elem, &t_result);
        assert(t_result);
    }
}

/** local function implementation section **/

/** eof **/

