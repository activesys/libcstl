/*
 *  The implement of vector private interface.
 *  Copyright (C)  2008 - 2014  Wangbo
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
#include <cstl/cstring.h>
#include <cstl/cvector.h>

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
    if ((pvec_vector = (vector_t*)malloc(sizeof(vector_t))) == NULL) {
        return NULL;
    }

    if (!_create_vector_auxiliary(pvec_vector, s_typename)) {
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
    if (pvec_vector->_t_typeinfo._t_style == _TYPE_INVALID) {
        return false;
    }

    pvec_vector->_pby_start = NULL;
    pvec_vector->_pby_finish = NULL;
    pvec_vector->_pby_endofstorage = NULL;

    _alloc_init(&pvec_vector->_t_allocator);
    return true;
}

/**
 * Initialize vector with specified element.
 */
void _vector_init_elem(vector_t* pvec_vector, size_t t_count, ...)
{
    va_list val_elemlist;

    assert(pvec_vector != NULL);
    assert(_vector_is_created(pvec_vector));

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
    vector_iterator_t it_begin;
    vector_iterator_t it_end;

    assert(pvec_vector != NULL);
    assert(_vector_is_created(pvec_vector));

    /* initialize vector_t */
    vector_init_n(pvec_vector, t_count);
    if (t_count > 0) {
        /* get varg value only once */
        pv_varg = _alloc_allocate(&pvec_vector->_t_allocator, _GET_VECTOR_TYPE_SIZE(pvec_vector), 1);
        assert(pv_varg != NULL);
        _vector_get_varg_value_auxiliary(pvec_vector, val_elemlist, pv_varg);

        /* copy varg value to each element */
        it_begin = vector_begin(pvec_vector);
        it_end = vector_end(pvec_vector);
        for (it_iter = it_begin; !iterator_equal(it_iter, it_end); it_iter = iterator_next(it_iter)) {
            /* copy from varg */
            b_result = _GET_VECTOR_TYPE_SIZE(pvec_vector);
            _GET_VECTOR_TYPE_COPY_FUNCTION(pvec_vector)(_VECTOR_ITERATOR_COREPOS(it_iter), pv_varg, &b_result);
            assert(b_result);
        }

        /* destroy varg value and free memory */
        _vector_destroy_varg_value_auxiliary(pvec_vector, pv_varg);
        _alloc_deallocate(&pvec_vector->_t_allocator, pv_varg, _GET_VECTOR_TYPE_SIZE(pvec_vector), 1);
    }
}

/**
 * Destroy vector container auxiliary function.
 */
void _vector_destroy_auxiliary(vector_t* pvec_vector)
{
    vector_iterator_t it_iter;
    vector_iterator_t it_begin;
    vector_iterator_t it_end;
    bool_t            b_result = false;

    assert(pvec_vector != NULL);
    assert(_vector_is_inited(pvec_vector) || _vector_is_created(pvec_vector));

    /* destroy all elements */
    it_begin = vector_begin(pvec_vector);
    it_end = vector_end(pvec_vector);
    for (it_iter = it_begin; !iterator_equal(it_iter, it_end); it_iter = iterator_next(it_iter)) {
        b_result = _GET_VECTOR_TYPE_SIZE(pvec_vector);
        _GET_VECTOR_TYPE_DESTROY_FUNCTION(pvec_vector)(_VECTOR_ITERATOR_COREPOS(it_iter), &b_result);
        assert(b_result);
    }
    /* free vector memory */
    if (pvec_vector->_pby_start != NULL) {
        _alloc_deallocate(&pvec_vector->_t_allocator, pvec_vector->_pby_start, _GET_VECTOR_TYPE_SIZE(pvec_vector), 
            (pvec_vector->_pby_endofstorage - pvec_vector->_pby_start) / _GET_VECTOR_TYPE_SIZE(pvec_vector));
    }
    _alloc_destroy(&pvec_vector->_t_allocator);

    pvec_vector->_pby_start = NULL;
    pvec_vector->_pby_finish = NULL;
    pvec_vector->_pby_endofstorage = NULL;
}

/**
 * Assign vector with specificed element.
 */
void _vector_assign_elem(vector_t* pvec_vector, size_t t_count, ...)
{
    va_list val_elemlist;

    assert(pvec_vector != NULL);
    assert(_vector_is_inited(pvec_vector));

    va_start(val_elemlist, t_count);
    _vector_assign_elem_varg(pvec_vector, t_count, val_elemlist);
    va_end(val_elemlist);
}

/**
 * Assign vector with variable argument list of specificed element.
 */
void _vector_assign_elem_varg(vector_t* pvec_vector, size_t t_count, va_list val_elemlist)
{
    iterator_t it_iter;
    iterator_t it_begin;
    iterator_t it_end;
    bool_t     b_result = false;
    void*      pv_varg = NULL;

    assert(pvec_vector != NULL);
    assert(_vector_is_inited(pvec_vector));

    /* get value from varg */
    pv_varg = _alloc_allocate(&pvec_vector->_t_allocator, _GET_VECTOR_TYPE_SIZE(pvec_vector), 1);
    assert(pv_varg != NULL);
    _vector_get_varg_value_auxiliary(pvec_vector, val_elemlist, pv_varg);

    /* copy value from varg for each element */
    vector_resize(pvec_vector, t_count);
    it_begin = vector_begin(pvec_vector);
    it_end = vector_end(pvec_vector);
    for (it_iter = it_begin; !iterator_equal(it_iter, it_end); it_iter = iterator_next(it_iter)) {
        b_result = _GET_VECTOR_TYPE_SIZE(pvec_vector);
        _GET_VECTOR_TYPE_COPY_FUNCTION(pvec_vector)(_VECTOR_ITERATOR_COREPOS(it_iter), pv_varg, &b_result);
        assert(b_result);
    }

    /* destroy varg and free memory */
    _vector_destroy_varg_value_auxiliary(pvec_vector, pv_varg);
    _alloc_deallocate(&pvec_vector->_t_allocator, pv_varg, _GET_VECTOR_TYPE_SIZE(pvec_vector), 1);
}

/**
 * Add specificed element at the end of vector container. 
 */
void _vector_push_back(vector_t* pvec_vector, ...)
{
    va_list val_elemlist;

    assert(pvec_vector != NULL);
    assert(_vector_is_inited(pvec_vector));

    va_start(val_elemlist, pvec_vector);
    _vector_push_back_varg(pvec_vector, val_elemlist);
    va_end(val_elemlist);
}

/**
 * Add specificed element from variable argument list at the end of vector container. 
 */
void _vector_push_back_varg(vector_t* pvec_vector, va_list val_elemlist)
{
    _byte_t*  pby_last = NULL;

    assert(pvec_vector != NULL);
    assert(_vector_is_inited(pvec_vector));

    /* if the remain capacity is less then the element count */
    if (vector_capacity(pvec_vector) == vector_size(pvec_vector)) {
        vector_reserve(pvec_vector, _vector_calculate_new_capacity(vector_size(pvec_vector), 1));
    }

    /* initialize the last element */
    pby_last = pvec_vector->_pby_finish;
    assert(pby_last != NULL);
    pvec_vector->_pby_finish += _GET_VECTOR_TYPE_SIZE(pvec_vector);
    _vector_init_elem_auxiliary(pvec_vector, pby_last);
    /* copy value from varg */
    _type_get_varg_value(&pvec_vector->_t_typeinfo, val_elemlist, pby_last);
}

/**
 * Reset the size of vector elements.
 */
void _vector_resize_elem(vector_t* pvec_vector, size_t t_resize, ...)
{
    va_list val_elemlist;

    assert(pvec_vector != NULL);
    assert(_vector_is_inited(pvec_vector));

    va_start(val_elemlist, t_resize);
    _vector_resize_elem_varg(pvec_vector, t_resize, val_elemlist);
    va_end(val_elemlist);
}

/**
 * Reset the size of vector elements, and filled element is from variable argument list.
 */
void _vector_resize_elem_varg(vector_t* pvec_vector, size_t t_resize, va_list val_elemlist)
{
    vector_iterator_t it_cutpos;     /* the cut position */
    size_t            t_expsize = 0;
    size_t            i = 0;
    void*             pv_varg = NULL;
    _byte_t*          pby_oldfinish = NULL;
    bool_t            b_result = false;

    assert(pvec_vector != NULL);
    assert(_vector_is_inited(pvec_vector));

    if (t_resize == vector_size(pvec_vector)) {
        return;
    } else if (t_resize < vector_size(pvec_vector)) {
        it_cutpos = vector_begin(pvec_vector);
        it_cutpos = iterator_next_n(it_cutpos, t_resize);
        vector_erase_range(pvec_vector, it_cutpos, vector_end(pvec_vector));
    } else {
        t_expsize = t_resize - vector_size(pvec_vector);
        if (t_resize > vector_capacity(pvec_vector)) {
            vector_reserve(pvec_vector, _vector_calculate_new_capacity(vector_size(pvec_vector), t_expsize));
        }

        /* get varg value only once */
        pv_varg = _alloc_allocate(&pvec_vector->_t_allocator, _GET_VECTOR_TYPE_SIZE(pvec_vector), 1);
        assert(pv_varg != NULL);
        _vector_get_varg_value_auxiliary(pvec_vector, val_elemlist, pv_varg);

        /* initialize new elements */
        pby_oldfinish = pvec_vector->_pby_finish;
        pvec_vector->_pby_finish += t_expsize * _GET_VECTOR_TYPE_SIZE(pvec_vector);
        _vector_init_elem_range_auxiliary(pvec_vector, pby_oldfinish, pvec_vector->_pby_finish);
        /* copy value from varg to new elements */
        for (i = 0; i < t_expsize; ++i) {
            b_result = _GET_VECTOR_TYPE_SIZE(pvec_vector);
            _GET_VECTOR_TYPE_COPY_FUNCTION(pvec_vector)(pby_oldfinish + i * _GET_VECTOR_TYPE_SIZE(pvec_vector), pv_varg, &b_result);
            assert(b_result);
        }
        /* destroy varg */
        _vector_destroy_varg_value_auxiliary(pvec_vector, pv_varg);
        _alloc_deallocate(&pvec_vector->_t_allocator, pv_varg, _GET_VECTOR_TYPE_SIZE(pvec_vector), 1);
    }
}

/**
 * Insert multiple copys of element befor specificed position.
 */
vector_iterator_t _vector_insert_n(vector_t* pvec_vector, vector_iterator_t it_pos, size_t t_count, ...)
{
    vector_iterator_t it_iter;
    va_list val_elemlist;

    assert(pvec_vector != NULL);
    assert(_vector_is_inited(pvec_vector));
    assert(_vector_iterator_belong_to_vector(pvec_vector, it_pos));

    va_start(val_elemlist, t_count);
    it_iter = _vector_insert_n_varg(pvec_vector, it_pos, t_count, val_elemlist);
    va_end(val_elemlist);

    return it_iter;
}

/**
 * Insert multiple copys of element befor specificed position, the element is from variable argument list.
 */
vector_iterator_t _vector_insert_n_varg(vector_t* pvec_vector, vector_iterator_t it_pos, size_t t_count, va_list val_elemlist)
{
    void*  pv_varg = NULL;
    bool_t b_result = false;

    /* test the vector and iterator is valid */
    assert(pvec_vector != NULL);
    assert(_vector_is_inited(pvec_vector));
    assert(_vector_iterator_belong_to_vector(pvec_vector, it_pos));

    if (t_count > 0) {
        size_t i = 0;
        _byte_t*  pby_oldfinish = NULL;
        _byte_t*  pby_pos = NULL;   /* for initialize elments and insert elements */
        _byte_t*  pby_destpos = NULL;

        /* if the remain capacity is less then the element count */
        if (vector_size(pvec_vector) + t_count > vector_capacity(pvec_vector)) {
            size_t t_insertpos = iterator_distance(vector_begin(pvec_vector), it_pos);
            /* reserve the new size */
            vector_reserve(pvec_vector, _vector_calculate_new_capacity(vector_size(pvec_vector), t_count));
            it_pos = iterator_next_n(vector_begin(pvec_vector), t_insertpos);
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
         * start     it_pos         finish
         *                           _t_count__
         *                          /          \
         * +-----------------------------------------+
         * |          |             |new element|    |
         * +-----------------------------------------+
         * ^          ^             ^           ^
         * |          |             |           |
         * start     it_pos       pby_oldfinish  finish
         */
        /* initialize new elements */
        pby_oldfinish = pvec_vector->_pby_finish;
        assert(pby_oldfinish != NULL);
        pvec_vector->_pby_finish += t_count * _GET_VECTOR_TYPE_SIZE(pvec_vector);
        _vector_init_elem_range_auxiliary(pvec_vector, pby_oldfinish, pvec_vector->_pby_finish);
        /* move element from old finish to new finish */
        for (pby_pos = pby_oldfinish - _GET_VECTOR_TYPE_SIZE(pvec_vector),
             pby_destpos = pvec_vector->_pby_finish - _GET_VECTOR_TYPE_SIZE(pvec_vector);
             pby_pos >= _VECTOR_ITERATOR_COREPOS(it_pos);
             pby_pos -= _GET_VECTOR_TYPE_SIZE(pvec_vector),
             pby_destpos -= _GET_VECTOR_TYPE_SIZE(pvec_vector)) {
            b_result = _GET_VECTOR_TYPE_SIZE(pvec_vector);
            _GET_VECTOR_TYPE_COPY_FUNCTION(pvec_vector)(pby_destpos, pby_pos, &b_result);
            assert(b_result);
        }

        /* get varg value only once */
        pv_varg = _alloc_allocate(&pvec_vector->_t_allocator, _GET_VECTOR_TYPE_SIZE(pvec_vector), 1);
        assert(pv_varg != NULL);
        _vector_get_varg_value_auxiliary(pvec_vector, val_elemlist, pv_varg);
        /* copy value for varg */
        for (i = 0; i < t_count; ++i) {
            b_result = _GET_VECTOR_TYPE_SIZE(pvec_vector);
            _GET_VECTOR_TYPE_COPY_FUNCTION(pvec_vector)(_VECTOR_ITERATOR_COREPOS(it_pos) + i * _GET_VECTOR_TYPE_SIZE(pvec_vector), pv_varg, &b_result);
            assert(b_result);
        }
        /* destroy varg and free memory */
        _vector_destroy_varg_value_auxiliary(pvec_vector, pv_varg);
        _alloc_deallocate(&pvec_vector->_t_allocator, pv_varg, _GET_VECTOR_TYPE_SIZE(pvec_vector), 1);
    }

    return it_pos;
}

/**
 * Initialize element with vector element type auxiliary function.
 */
void _vector_init_elem_auxiliary(vector_t* pvec_vector, void* pv_elem)
{
    assert(pvec_vector != NULL);
    assert(pv_elem != NULL);
    assert(_vector_is_inited(pvec_vector) || _vector_is_created(pvec_vector));

    /* initialize new elements */
    if (_GET_VECTOR_TYPE_STYLE(pvec_vector) == _TYPE_CSTL_BUILTIN) {
        /* get element type name */
        char s_elemtypename[_TYPE_NAME_SIZE + 1];
        _type_get_elem_typename(_GET_VECTOR_TYPE_NAME(pvec_vector), s_elemtypename);

        _GET_VECTOR_TYPE_INIT_FUNCTION(pvec_vector)(pv_elem, s_elemtypename);
    } else {
        bool_t b_result = _GET_VECTOR_TYPE_SIZE(pvec_vector);
        _GET_VECTOR_TYPE_INIT_FUNCTION(pvec_vector)(pv_elem, &b_result);
        assert(b_result);
    }
}

/** local function implementation section **/

/** eof **/

