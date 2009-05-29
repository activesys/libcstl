/*
 *  The implement of vector module.
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

/** include section **/
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "cstl_alloc.h"
#include "cstl_types.h"
#include "cstl_iterator.h"
#include "cstl_iterator_private.h"

#include "cstl_vector_iterator.h"
#include "cstl_vector_private.h"
#include "cstl_vector.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/
/* macros of getting type information */
#define _GET_VECTOR_TYPE_SIZE(pt_vector)\
    ((pt_vector)->_t_typeinfo._pt_type->_t_typesize)
#define _GET_VECTOR_TYPE_NAME(pt_vector)\
    ((pt_vector)->_t_typeinfo._sz_typename)
#define _GET_VECTOR_TYPE_BASENAME(pt_vector)\
    ((pt_vector)->_t_typeinfo._pt_type->_sz_typename)
#define _GET_VECTOR_TYPE_INIT_FUNCTION(pt_vector)\
    ((pt_vector)->_t_typeinfo._pt_type->_t_typeinit)
#define _GET_VECTOR_TYPE_COPY_FUNCTION(pt_vector)\
    ((pt_vector)->_t_typeinfo._pt_type->_t_typecopy)
#define _GET_VECTOR_TYPE_LESS_FUNCTION(pt_vector)\
    ((pt_vector)->_t_typeinfo._pt_type->_t_typeless)
#define _GET_VECTOR_TYPE_DESTROY_FUNCTION(pt_vector)\
    ((pt_vector)->_t_typeinfo._pt_type->_t_typedestroy)

/** local function prototype section **/
#ifndef NDEBUG
/*
 * Private function for assert.
 */
static bool_t _vector_iterator_belong_to_vector(
    const vector_t* cpt_vector, vector_iterator_t t_iter);
static bool_t _vector_same_vector_iterator_type(
    const vector_t* cpt_vector, vector_iterator_t t_iter);
#endif /* NDEBUG */
static bool_t _vector_same_type(
    const vector_t* cpt_vectorfirst, const vector_t* cpt_vectorsecond);

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/* vector iterator function */
vector_iterator_t create_vector_iterator(void)
{
    vector_iterator_t t_newiterator;

    _GET_VECTOR_COREPOS(t_newiterator) = NULL;
    _GET_CONTAINER(t_newiterator) = NULL;
    _GET_VECTOR_CONTAINER_TYPE(t_newiterator) = _VECTOR_CONTAINER;
    _GET_VECTOR_ITERATOR_TYPE(t_newiterator) = _RANDOM_ACCESS_ITERATOR;

    return t_newiterator;
}

bool_t _vector_iterator_equal(
    vector_iterator_t t_iterfirst, vector_iterator_t t_itersecond)
{
    assert(_iterator_same_type(t_iterfirst, t_itersecond));
    assert(_GET_VECTOR_CONTAINER(t_iterfirst) == _GET_VECTOR_CONTAINER(t_itersecond));
    assert(_vector_iterator_belong_to_vector(
        _GET_VECTOR_CONTAINER(t_iterfirst), t_iterfirst));
    assert(_vector_iterator_belong_to_vector(
        _GET_VECTOR_CONTAINER(t_itersecond), t_itersecond));

    if(_GET_VECTOR_COREPOS(t_iterfirst) == _GET_VECTOR_COREPOS(t_itersecond))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void _vector_iterator_get_value(vector_iterator_t t_iter, void* pv_value)
{
    bool_t t_result = false;

    assert(pv_value != NULL);
    assert(_vector_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(t_iter), t_iter));
    assert(!iterator_equal(t_iter, vector_end(_GET_VECTOR_CONTAINER(t_iter))));

    t_result = _GET_VECTOR_TYPE_SIZE(_GET_VECTOR_CONTAINER(t_iter));
    _GET_VECTOR_TYPE_COPY_FUNCTION(_GET_VECTOR_CONTAINER(t_iter))(
        pv_value, _GET_VECTOR_COREPOS(t_iter), &t_result);
    assert(t_result);
}

void _vector_iterator_set_value(vector_iterator_t t_iter, const void* cpv_value)
{
    bool_t t_result = false;

    assert(cpv_value != NULL);
    assert(_vector_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(t_iter), t_iter));
    assert(!iterator_equal(t_iter, vector_end(_GET_VECTOR_CONTAINER(t_iter))));

    t_result = _GET_VECTOR_TYPE_SIZE(_GET_VECTOR_CONTAINER(t_iter));
    _GET_VECTOR_TYPE_COPY_FUNCTION(_GET_VECTOR_CONTAINER(t_iter))(
        _GET_VECTOR_COREPOS(t_iter), cpv_value, &t_result);
    assert(t_result);
}

const void* _vector_iterator_get_pointer(vector_iterator_t t_iter)
{
    assert(_vector_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(t_iter), t_iter));
    assert(!iterator_equal(t_iter, vector_end(_GET_VECTOR_CONTAINER(t_iter))));

    return _GET_VECTOR_COREPOS(t_iter);
}

vector_iterator_t _vector_iterator_next(vector_iterator_t t_iter)
{
    assert(_vector_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(t_iter), t_iter));
    _GET_VECTOR_COREPOS(t_iter) += _GET_VECTOR_TYPE_SIZE(_GET_VECTOR_CONTAINER(t_iter));
    assert(_vector_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(t_iter), t_iter));

    return t_iter;
}

vector_iterator_t _vector_iterator_prev(vector_iterator_t t_iter)
{
    assert(_vector_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(t_iter), t_iter));
    _GET_VECTOR_COREPOS(t_iter) -= _GET_VECTOR_TYPE_SIZE(_GET_VECTOR_CONTAINER(t_iter));
    assert(_vector_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(t_iter), t_iter));

    return t_iter;
}

void* _vector_iterator_at(vector_iterator_t t_iter, int n_index)
{
    assert(_vector_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(t_iter), t_iter));
    _GET_VECTOR_COREPOS(t_iter) +=
        _GET_VECTOR_TYPE_SIZE(_GET_VECTOR_CONTAINER(t_iter)) * n_index;
    assert(_vector_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(t_iter), t_iter));

    return _GET_VECTOR_COREPOS(t_iter);
}

vector_iterator_t _vector_iterator_next_n(vector_iterator_t t_iter, int n_step)
{
    assert(_vector_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(t_iter), t_iter));
    _GET_VECTOR_COREPOS(t_iter) +=
        _GET_VECTOR_TYPE_SIZE(_GET_VECTOR_CONTAINER(t_iter)) * n_step;
    assert(_vector_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(t_iter), t_iter));

    return t_iter;
}

vector_iterator_t _vector_iterator_prev_n(vector_iterator_t t_iter, int n_step)
{
    assert(_vector_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(t_iter), t_iter));
    _GET_VECTOR_COREPOS(t_iter) -=
        _GET_VECTOR_TYPE_SIZE(_GET_VECTOR_CONTAINER(t_iter)) * n_step;
    assert(_vector_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(t_iter), t_iter));

    return t_iter;
}

int _vector_iterator_minus(vector_iterator_t t_iterfirst, vector_iterator_t t_itersecond)
{
    assert(_iterator_same_type(t_iterfirst, t_itersecond));
    assert(_GET_VECTOR_CONTAINER(t_iterfirst) == _GET_VECTOR_CONTAINER(t_itersecond));
    assert(_vector_iterator_belong_to_vector(
        _GET_VECTOR_CONTAINER(t_iterfirst), t_iterfirst));
    assert(_vector_iterator_belong_to_vector(
        _GET_VECTOR_CONTAINER(t_itersecond), t_itersecond));

    return (_GET_VECTOR_COREPOS(t_iterfirst) - _GET_VECTOR_COREPOS(t_itersecond)) / 
           (int)_GET_VECTOR_TYPE_SIZE(_GET_VECTOR_CONTAINER(t_iterfirst));
}

bool_t _vector_iterator_less(vector_iterator_t t_iterfirst, vector_iterator_t t_itersecond)
{
    assert(_iterator_same_type(t_iterfirst, t_itersecond));
    assert(_GET_VECTOR_CONTAINER(t_iterfirst) == _GET_VECTOR_CONTAINER(t_itersecond));
    assert(_vector_iterator_belong_to_vector(
        _GET_VECTOR_CONTAINER(t_iterfirst), t_iterfirst));
    assert(_vector_iterator_belong_to_vector(
        _GET_VECTOR_CONTAINER(t_itersecond), t_itersecond));

    if(_GET_VECTOR_COREPOS(t_iterfirst) < _GET_VECTOR_COREPOS(t_itersecond))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool_t _vector_iterator_before(
    vector_iterator_t t_iterfirst, vector_iterator_t t_itersecond)
{
    return _vector_iterator_less(t_iterfirst, t_itersecond);
}


/* private vector function */
vector_t* _create_vector(const char* s_typename)
{
    _typeinfo_t t_typeinfo;
    vector_t*   pt_newvector = NULL;

    assert(s_typename != NULL);

    /* get type information */
    _type_get_type(&t_typeinfo, s_typename);
    if(t_typeinfo._pt_type == NULL)
    {/* type name is invalid */
        return NULL;
    }

    /* allocate for vector_t and initialize it */
    if((pt_newvector = (vector_t*)malloc(sizeof(vector_t))) == NULL)
    {
        return NULL;
    }
    memset(pt_newvector->_t_typeinfo._sz_typename, '\0', _TYPE_NAME_SIZE+1);
    strncpy(pt_newvector->_t_typeinfo._sz_typename, t_typeinfo._sz_typename,_TYPE_NAME_SIZE);
    pt_newvector->_t_typeinfo._pt_type = t_typeinfo._pt_type;
    pt_newvector->_pc_start = NULL;
    pt_newvector->_pc_finish = NULL;
    pt_newvector->_pc_endofstorage = NULL;

    return pt_newvector;
}

void _vector_push_back_varg(vector_t* pt_vector, va_list val_elemlist)
{
    assert(pt_vector != NULL);

    /* if the remain capacity is less then the element count */
    if(vector_capacity(pt_vector) == vector_size(pt_vector)) 
    {
        /* reserve the new size */
        /* new size = old size + 2 */
        vector_reserve(pt_vector, vector_size(pt_vector) + 2);
    }

    /* append the element to the end of vector */
    _type_get_varg_value(&pt_vector->_t_typeinfo, val_elemlist, pt_vector->_pc_finish);
    pt_vector->_pc_finish += _GET_VECTOR_TYPE_SIZE(pt_vector);
}

/* vector function */
/* initialize and destroy */
void _vector_init_elem_varg(vector_t* pt_vector, size_t t_count, va_list val_elemlist)
{
    void*             pv_varg = NULL;
    bool_t            t_result = false;
    vector_iterator_t t_iter;

    assert(pt_vector != NULL);
    assert(pt_vector->_pc_start == NULL && pt_vector->_pc_finish == NULL &&
           pt_vector->_pc_endofstorage == NULL);
    assert(pt_vector->_t_typeinfo._pt_type != NULL);

    allocate_init(&pt_vector->_t_allocater);
    if(t_count > 0)
    {
        pt_vector->_pc_start = allocate(
            &pt_vector->_t_allocater, _GET_VECTOR_TYPE_SIZE(pt_vector), (2 * t_count));
        assert(pt_vector->_pc_start != NULL);
        pt_vector->_pc_finish =
            pt_vector->_pc_start + _GET_VECTOR_TYPE_SIZE(pt_vector) * t_count;
        pt_vector->_pc_endofstorage =
            pt_vector->_pc_start + _GET_VECTOR_TYPE_SIZE(pt_vector) * (2 * t_count);

        /* get varg value only once */
        pv_varg = allocate(
            &pt_vector->_t_allocater, _GET_VECTOR_TYPE_SIZE(pt_vector), 1);
        assert(pv_varg != NULL);
        t_result = _GET_VECTOR_TYPE_SIZE(pt_vector);
        _GET_VECTOR_TYPE_INIT_FUNCTION(pt_vector)(pv_varg, &t_result);
        assert(t_result);
        _type_get_varg_value(&pt_vector->_t_typeinfo, val_elemlist, pv_varg);
        for(t_iter = vector_begin(pt_vector);
            !iterator_equal(t_iter, vector_end(pt_vector));
            t_iter = iterator_next(t_iter))
        {
            t_result = _GET_VECTOR_TYPE_SIZE(pt_vector);
            _GET_VECTOR_TYPE_COPY_FUNCTION(pt_vector)(
                _GET_VECTOR_COREPOS(t_iter), pv_varg, &t_result);
            assert(t_result);
        }
        t_result = _GET_VECTOR_TYPE_SIZE(pt_vector);
        _GET_VECTOR_TYPE_DESTROY_FUNCTION(pt_vector)(pv_varg, &t_result);
        assert(t_result);
        deallocate(&pt_vector->_t_allocater, pv_varg,
            _GET_VECTOR_TYPE_SIZE(pt_vector), 1);
    }
}

void _vector_init_elem(vector_t* pt_vector, size_t t_count, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_count);
    _vector_init_elem_varg(pt_vector, t_count, val_elemlist);
}

void vector_init_n(vector_t* pt_vector, size_t t_count)
{
    _vector_init_elem(pt_vector, t_count, 0x00);
}

void vector_init(vector_t* pt_vector)
{
    vector_init_n(pt_vector, 0);
}

void vector_destroy(vector_t* pt_vector)
{
    vector_iterator_t t_iter;
    bool_t            t_result = false;

    assert(pt_vector != NULL);
    assert(pt_vector->_pc_finish - pt_vector->_pc_start >= 0);
    assert(pt_vector->_pc_endofstorage - pt_vector->_pc_start >= 0);
    
    /* destroy all elements */
    for(t_iter = vector_begin(pt_vector);
        !iterator_equal(t_iter, vector_end(pt_vector));
        t_iter = iterator_next(t_iter))
    {
        t_result = _GET_VECTOR_TYPE_SIZE(pt_vector);
        _GET_VECTOR_TYPE_DESTROY_FUNCTION(pt_vector)(_GET_VECTOR_COREPOS(t_iter), &t_result);
        assert(t_result);
    }
    /* free vector memory */
    if(pt_vector->_pc_start != NULL)
    {
        deallocate(&pt_vector->_t_allocater, pt_vector->_pc_start,
            _GET_VECTOR_TYPE_SIZE(pt_vector), 
            (pt_vector->_pc_endofstorage - pt_vector->_pc_start) /
            _GET_VECTOR_TYPE_SIZE(pt_vector));
    }
    allocate_destroy(&pt_vector->_t_allocater);

    pt_vector->_pc_start = NULL;
    pt_vector->_pc_finish = NULL;
    pt_vector->_pc_endofstorage = NULL;
}

void vector_init_copy(vector_t* pt_vectordest, const vector_t* cpt_vectorsrc)
{
    vector_init_copy_range(pt_vectordest,
        vector_begin(cpt_vectorsrc), vector_end(cpt_vectorsrc));
}

void vector_init_copy_range(
    vector_t* pt_vector, vector_iterator_t t_begin, vector_iterator_t t_end)
{
    vector_iterator_t t_dest;
    vector_iterator_t t_src;
    bool_t            t_result = false;

    assert(pt_vector != NULL);
    assert(_vector_same_vector_iterator_type(pt_vector, t_begin));
    assert(pt_vector->_pc_start == NULL && pt_vector->_pc_finish == NULL &&
           pt_vector->_pc_endofstorage == NULL);
    assert(iterator_equal(t_begin, t_end) || _vector_iterator_before(t_begin, t_end));

    vector_init_n(pt_vector, iterator_distance(t_begin, t_end));

    for(t_dest = vector_begin(pt_vector), t_src = t_begin;
        !iterator_equal(t_dest, vector_end(pt_vector)) && !iterator_equal(t_src, t_end);
        t_dest = iterator_next(t_dest), t_src = iterator_next(t_src))
    {
        t_result = _GET_VECTOR_TYPE_SIZE(pt_vector);
        _GET_VECTOR_TYPE_COPY_FUNCTION(pt_vector)(
            _GET_VECTOR_COREPOS(t_dest), _GET_VECTOR_COREPOS(t_src), &t_result);
        assert(t_result);
    }
    assert(iterator_equal(t_dest, vector_end(pt_vector)) && iterator_equal(t_src, t_end));
}

size_t vector_size(const vector_t* cpt_vector)
{
    assert(cpt_vector != NULL);
    return (cpt_vector->_pc_finish - cpt_vector->_pc_start) / 
            _GET_VECTOR_TYPE_SIZE(cpt_vector);
}

bool_t vector_empty(const vector_t* cpt_vector)
{
    assert(cpt_vector != NULL);
    
    if(cpt_vector->_pc_start == cpt_vector->_pc_finish)
    {
        return true;
    }
    else
    {
        return false;
    }
}

size_t vector_max_size(const vector_t* cpt_vector)
{
    assert(cpt_vector != NULL);

    return (size_t)(-1) / _GET_VECTOR_TYPE_SIZE(cpt_vector);
}

size_t vector_capacity(const vector_t* cpt_vector)
{
    assert(cpt_vector != NULL);

    return (cpt_vector->_pc_endofstorage - cpt_vector->_pc_start) /
            _GET_VECTOR_TYPE_SIZE(cpt_vector);
}

void vector_reserve(vector_t* pt_vector, size_t t_reservesize)
{
    char*  pc_reservemem = NULL; /* new memory for reserve */
    size_t t_oldsize = 0;
    size_t t_oldcapacitysize = 0;

    assert(pt_vector != NULL);

    if(vector_capacity(pt_vector) < t_reservesize)
    {
        /* allocate the new vector with reserve size */
        pc_reservemem = allocate(
            &pt_vector->_t_allocater, _GET_VECTOR_TYPE_SIZE(pt_vector), t_reservesize);
        assert(pc_reservemem != NULL);
        /* copy the vector element to new vector */
        t_oldsize = pt_vector->_pc_finish - pt_vector->_pc_start;
        t_oldcapacitysize = pt_vector->_pc_endofstorage - pt_vector->_pc_start;
        memcpy(pc_reservemem, pt_vector->_pc_start, t_oldsize);
        /* free the old vector element */
        if(pt_vector->_pc_start != NULL)
        {
            deallocate(&pt_vector->_t_allocater, pt_vector->_pc_start,
                _GET_VECTOR_TYPE_SIZE(pt_vector),
                t_oldcapacitysize / _GET_VECTOR_TYPE_SIZE(pt_vector));
        }
        pt_vector->_pc_start = pc_reservemem;
        pt_vector->_pc_finish = pt_vector->_pc_start + t_oldsize;
        pt_vector->_pc_endofstorage = 
            pt_vector->_pc_start + (_GET_VECTOR_TYPE_SIZE(pt_vector) * t_reservesize);
    }
}

bool_t vector_equal(
    const vector_t* cpt_vectorfirst, const vector_t* cpt_vectorsecond)
{
    vector_iterator_t t_iterfirst;
    vector_iterator_t t_itersecond;
    bool_t            t_resultless = false;
    bool_t            t_resultgreat = false;

    assert(cpt_vectorfirst != NULL && cpt_vectorsecond != NULL);

    /* the element type is equal */
    if(!_vector_same_type(cpt_vectorfirst, cpt_vectorsecond))
    {
        return false;
    }
    /* the element count is equal */
    if(vector_size(cpt_vectorfirst) != vector_size(cpt_vectorsecond))
    {
        return false;
    }

    /* each element is equal */
    for(t_iterfirst = vector_begin(cpt_vectorfirst),
        t_itersecond = vector_begin(cpt_vectorsecond);
        !iterator_equal(t_iterfirst, vector_end(cpt_vectorfirst)) &&
        !iterator_equal(t_itersecond, vector_end(cpt_vectorsecond));
        t_iterfirst = iterator_next(t_iterfirst),
        t_itersecond = iterator_next(t_itersecond))
    {
        t_resultless = _GET_VECTOR_TYPE_SIZE(cpt_vectorfirst);
        t_resultgreat = _GET_VECTOR_TYPE_SIZE(cpt_vectorsecond);
        _GET_VECTOR_TYPE_LESS_FUNCTION(cpt_vectorfirst)(_GET_VECTOR_COREPOS(t_iterfirst),
            _GET_VECTOR_COREPOS(t_itersecond), &t_resultless);
        _GET_VECTOR_TYPE_LESS_FUNCTION(cpt_vectorsecond)(_GET_VECTOR_COREPOS(t_itersecond),
            _GET_VECTOR_COREPOS(t_iterfirst), &t_resultgreat);
        if(t_resultless || t_resultgreat)
        {
            return false;
        }
    }
    assert(iterator_equal(t_iterfirst, vector_end(cpt_vectorfirst)) &&
           iterator_equal(t_itersecond, vector_end(cpt_vectorsecond)));

    return true;
}

bool_t vector_not_equal(
    const vector_t* cpt_vectorfirst, const vector_t* cpt_vectorsecond)
{
    return !vector_equal(cpt_vectorfirst, cpt_vectorsecond);
}

bool_t vector_less(
    const vector_t* cpt_vectorfirst, const vector_t* cpt_vectorsecond)
{
    bool_t t_result = false;
    vector_iterator_t t_iterfirst;
    vector_iterator_t t_itersecond;

    assert(_vector_same_type(cpt_vectorfirst, cpt_vectorsecond));

    for(t_iterfirst = vector_begin(cpt_vectorfirst),
        t_itersecond = vector_begin(cpt_vectorsecond);
        !iterator_equal(t_iterfirst, vector_end(cpt_vectorfirst)) &&
        !iterator_equal(t_itersecond, vector_end(cpt_vectorsecond));
        t_iterfirst = iterator_next(t_iterfirst),
        t_itersecond = iterator_next(t_itersecond))
    {
        t_result = _GET_VECTOR_TYPE_SIZE(cpt_vectorfirst);
        _GET_VECTOR_TYPE_LESS_FUNCTION(cpt_vectorfirst)(
            _GET_VECTOR_COREPOS(t_iterfirst), _GET_VECTOR_COREPOS(t_itersecond), &t_result);
        /* if any element in first vector are less then the second return true */
        if(t_result)
        {
            return true;
        }
        t_result = _GET_VECTOR_TYPE_SIZE(cpt_vectorfirst);
        _GET_VECTOR_TYPE_LESS_FUNCTION(cpt_vectorfirst)(
            _GET_VECTOR_COREPOS(t_itersecond), _GET_VECTOR_COREPOS(t_iterfirst), &t_result);
        /* if any element in first vector are great then the second return false */
        if(t_result)
        {
            return false;
        }
    }

    /* if the first n elements in two vector are equal then compare the vector size */
    if(vector_size(cpt_vectorfirst) < vector_size(cpt_vectorsecond))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool_t vector_great(
    const vector_t* cpt_vectorfirst, const vector_t* cpt_vectorsecond)
{
    return vector_less(cpt_vectorsecond, cpt_vectorfirst);
}

bool_t vector_less_equal(
    const vector_t* cpt_vectorfirst, const vector_t* cpt_vectorsecond)
{
    if(vector_less(cpt_vectorfirst, cpt_vectorsecond) == true ||
       vector_equal(cpt_vectorfirst, cpt_vectorsecond) == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool_t vector_great_equal(
    const vector_t* cpt_vectorfirst, const vector_t* cpt_vectorsecond)
{
    if(vector_great(cpt_vectorfirst, cpt_vectorsecond) == true ||
       vector_equal(cpt_vectorfirst, cpt_vectorsecond) == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/* assign */
void vector_assign(vector_t* pt_vectordest, const vector_t* cpt_vectorsrc)
{
    assert(_vector_same_type(pt_vectordest, cpt_vectorsrc));

    /* destroy vector */
    vector_destroy(pt_vectordest);
    /* initialize vector copy */
    vector_init_copy(pt_vectordest, cpt_vectorsrc);
}

void _vector_assign_elem_varg(
    vector_t* pt_vector, size_t t_count, va_list val_elemlist)
{
    assert(pt_vector != NULL);

    /* destroy vector */
    vector_destroy(pt_vector);
    /* initialzie vector */
    _vector_init_elem_varg(pt_vector, t_count, val_elemlist);
}

void _vector_assign_elem(vector_t* pt_vector, size_t t_count, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_count);
    _vector_assign_elem_varg(pt_vector, t_count, val_elemlist);
}

void vector_assign_range(
    vector_t* pt_vector, vector_iterator_t t_begin, vector_iterator_t t_end)
{
    /* assign the two iterator is as the same type as pt_vector */
    assert(_vector_same_vector_iterator_type(pt_vector, t_begin));
    assert(iterator_equal(t_begin, t_end) || _vector_iterator_before(t_begin, t_end));

    /*destroy vector*/
    vector_destroy(pt_vector);
    /* initialize copy range */
    vector_init_copy_range(pt_vector, t_begin, t_end);
}

void vector_swap(vector_t* pt_vectorfirst, vector_t* pt_vectorsecond)
{
    vector_t t_swapvector;  /* the swap temporary vector */

    /* test the two vector has the same type */
    assert(_vector_same_type(pt_vectorfirst, pt_vectorsecond));

    t_swapvector = *pt_vectorfirst;
    *pt_vectorfirst = *pt_vectorsecond;
    *pt_vectorsecond = t_swapvector;
}

void* vector_at(const vector_t* cpt_vector, size_t t_pos)
{
    assert(cpt_vector != NULL);
    assert(t_pos < vector_size(cpt_vector));

    return cpt_vector->_pc_start + t_pos * _GET_VECTOR_TYPE_SIZE(cpt_vector);
}

void* vector_front(const vector_t* cpt_vector)
{
    if(vector_empty(cpt_vector))
    {
        return NULL;
    }
    else
    {
        return vector_at(cpt_vector, 0);
    }
}

void* vector_back(const vector_t* cpt_vector)
{
    if(vector_empty(cpt_vector))
    {
        return NULL;
    }
    else
    {
        return vector_at(cpt_vector, vector_size(cpt_vector) - 1);
    }
}

vector_iterator_t vector_begin(const vector_t* cpt_vector)
{
    vector_iterator_t t_newiterator; /* new vector iterator */

    assert(cpt_vector != NULL);

    t_newiterator = create_vector_iterator();
    _GET_CONTAINER(t_newiterator) = (vector_t*)cpt_vector;
    _GET_VECTOR_COREPOS(t_newiterator) = cpt_vector->_pc_start;

    return t_newiterator;
}

vector_iterator_t vector_end(const vector_t* cpt_vector)
{
    vector_iterator_t t_newiterator;

    assert(cpt_vector != NULL);

    t_newiterator = create_vector_iterator();
    _GET_CONTAINER(t_newiterator) = (vector_t*)cpt_vector;
    _GET_VECTOR_COREPOS(t_newiterator) = cpt_vector->_pc_finish;

    return t_newiterator;
}

vector_reverse_iterator_t vector_rbegin(const vector_t* cpt_vector)
{
    vector_reverse_iterator_t t_newiterator;

    assert(cpt_vector != NULL);

    t_newiterator = create_vector_iterator();
    _GET_CONTAINER(t_newiterator) = (vector_t*)cpt_vector;
    _GET_VECTOR_COREPOS(t_newiterator) =
        cpt_vector->_pc_finish - _GET_VECTOR_TYPE_SIZE(cpt_vector);

    return t_newiterator;
}

vector_reverse_iterator_t vector_rend(const vector_t* cpt_vector)
{
    vector_reverse_iterator_t t_newiterator;

    assert(cpt_vector != NULL);

    t_newiterator = create_vector_iterator();
    _GET_CONTAINER(t_newiterator) = (vector_t*)cpt_vector;
    _GET_VECTOR_COREPOS(t_newiterator) =
        cpt_vector->_pc_start - _GET_VECTOR_TYPE_SIZE(cpt_vector);

    return t_newiterator;
}

vector_iterator_t _vector_insert_n(
    vector_t* pt_vector, vector_iterator_t t_pos, size_t t_count, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_count);
    return _vector_insert_n_varg(pt_vector, t_pos, t_count, val_elemlist);
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

        /* if the remain capacity is less then the element count */
        if(vector_size(pt_vector) + t_count > vector_capacity(pt_vector))
        {
            size_t t_insertpos = iterator_distance(vector_begin(pt_vector), t_pos);
            /* reserve the new size */
            /* new size = old size + 2 * element count */
            vector_reserve(pt_vector, vector_size(pt_vector) + 2 * t_count);
            t_pos = vector_begin(pt_vector);
            t_pos = iterator_next_n(t_pos, t_insertpos);
        }

        /* insert the element counts of element to the position */
        /* move the elements from pos to the finish of vector to the 
         * memory that after the pos element count*/
        memmove(_GET_VECTOR_COREPOS(t_pos) + t_count * _GET_VECTOR_TYPE_SIZE(pt_vector),
            _GET_VECTOR_COREPOS(t_pos), pt_vector->_pc_finish - _GET_VECTOR_COREPOS(t_pos)); 
        pt_vector->_pc_finish += t_count * _GET_VECTOR_TYPE_SIZE(pt_vector);
        /* insert element counts copys to the pos */

        /* get varg value only once */
        pv_varg = allocate(&pt_vector->_t_allocater, _GET_VECTOR_TYPE_SIZE(pt_vector), 1);
        assert(pv_varg != NULL);
        t_result = _GET_VECTOR_TYPE_SIZE(pt_vector);
        _GET_VECTOR_TYPE_INIT_FUNCTION(pt_vector)(pv_varg, &t_result);
        assert(t_result);
        _type_get_varg_value(&pt_vector->_t_typeinfo, val_elemlist, pv_varg);
        for(t_index = 0; t_index < t_count; ++t_index)
        {
            t_result = _GET_VECTOR_TYPE_SIZE(pt_vector);
            _GET_VECTOR_TYPE_COPY_FUNCTION(pt_vector)(
                _GET_VECTOR_COREPOS(t_pos) + t_index * _GET_VECTOR_TYPE_SIZE(pt_vector),
                pv_varg, &t_result);
            assert(t_result);
        }
        t_result = _GET_VECTOR_TYPE_SIZE(pt_vector);
        _GET_VECTOR_TYPE_DESTROY_FUNCTION(pt_vector)(pv_varg, &t_result);
        assert(t_result);
        deallocate(&pt_vector->_t_allocater, pv_varg, _GET_VECTOR_TYPE_SIZE(pt_vector), 1);

        t_pos = iterator_next_n(t_pos, t_count);
    }

    return t_pos;
}

void vector_insert_range(
    vector_t* pt_vector, vector_iterator_t t_pos,
    vector_iterator_t t_begin, vector_iterator_t t_end)
{
    size_t t_count = 0; /* the element count */
    bool_t t_result = false;
    vector_iterator_t t_iterfirst;
    vector_iterator_t t_itersecond;

    /* test the vector and iterator is valid */
    assert(_vector_iterator_belong_to_vector(pt_vector, t_pos));
    assert(iterator_equal(t_begin, t_end) || _vector_iterator_before(t_begin, t_end));
    assert(_vector_same_vector_iterator_type(pt_vector, t_begin));

    t_count = iterator_distance(t_begin, t_end);
    /* if the remain capacity is less then the element count */
    if(vector_size(pt_vector) + t_count > vector_capacity(pt_vector))
    {
        size_t t_iteratordistance = _GET_VECTOR_COREPOS(t_pos) - pt_vector->_pc_start;
        /* reserve the new size */
        /* new size = old size + 2 * element count */
        vector_reserve(pt_vector, vector_size(pt_vector) + 2 * t_count);
        _GET_VECTOR_COREPOS(t_pos) = pt_vector->_pc_start + t_iteratordistance;
    }

    /* insert the element counts of element to the position */
    /* move the elements from pos to the finish of vector to the 
     * memory that after the pos element count*/
    memmove(_GET_VECTOR_COREPOS(t_pos) + t_count * _GET_VECTOR_TYPE_SIZE(pt_vector),
        _GET_VECTOR_COREPOS(t_pos), pt_vector->_pc_finish - _GET_VECTOR_COREPOS(t_pos)); 
    pt_vector->_pc_finish += t_count * _GET_VECTOR_TYPE_SIZE(pt_vector);
    /* insert element counts copys to the pos */
    for(t_iterfirst = t_pos, t_itersecond = t_begin;
        !iterator_equal(t_itersecond, t_end);
        t_iterfirst = iterator_next(t_iterfirst), t_itersecond = iterator_next(t_itersecond))
    {
        t_result = _GET_VECTOR_TYPE_SIZE(pt_vector);
        _GET_VECTOR_TYPE_COPY_FUNCTION(pt_vector)(
            _GET_VECTOR_COREPOS(t_iterfirst), _GET_VECTOR_COREPOS(t_itersecond), &t_result);
        assert(t_result);
    }
    assert(_GET_VECTOR_COREPOS(t_iterfirst) ==
           _GET_VECTOR_COREPOS(t_pos) +
           (_GET_VECTOR_COREPOS(t_end) - _GET_VECTOR_COREPOS(t_begin)));
}

void _vector_push_back(vector_t* pt_vector, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, pt_vector);
    _vector_push_back_varg(pt_vector, val_elemlist);
}

void vector_pop_back(vector_t* pt_vector)
{
    bool_t t_result = false;

    assert(pt_vector != NULL);
    assert(vector_size(pt_vector) > 0);

    /* destroy last element */
    t_result = _GET_VECTOR_TYPE_SIZE(pt_vector);
    _GET_VECTOR_TYPE_DESTROY_FUNCTION(pt_vector)(
        pt_vector->_pc_finish-_GET_VECTOR_TYPE_SIZE(pt_vector), &t_result);
    assert(t_result);
    pt_vector->_pc_finish -= _GET_VECTOR_TYPE_SIZE(pt_vector);
}

vector_iterator_t vector_erase(vector_t* pt_vector, vector_iterator_t t_pos)
{
    bool_t t_result = false;

    assert(_vector_iterator_belong_to_vector(pt_vector, t_pos));
    assert(!iterator_equal(t_pos, vector_end(pt_vector)));

    t_result = _GET_VECTOR_TYPE_SIZE(pt_vector);
    _GET_VECTOR_TYPE_DESTROY_FUNCTION(pt_vector)(_GET_VECTOR_COREPOS(t_pos), &t_result);
    assert(t_result);

    memmove(_GET_VECTOR_COREPOS(t_pos),
        _GET_VECTOR_COREPOS(t_pos) + _GET_VECTOR_TYPE_SIZE(pt_vector),
        pt_vector->_pc_finish - _GET_VECTOR_COREPOS(t_pos) -
        _GET_VECTOR_TYPE_SIZE(pt_vector));
    pt_vector->_pc_finish -= _GET_VECTOR_TYPE_SIZE(pt_vector);

    return t_pos;
}

vector_iterator_t vector_erase_range(
    vector_t* pt_vector, vector_iterator_t t_begin, vector_iterator_t t_end)
{
    size_t            t_erasesize = 0;
    bool_t            t_result = false;
    vector_iterator_t t_iter;

    assert(_vector_iterator_belong_to_vector(pt_vector, t_begin));
    assert(iterator_equal(t_begin, t_end) || _vector_iterator_before(t_begin, t_end));
    assert(!iterator_equal(t_begin, vector_end(pt_vector)));

    /* destroy elements */
    for(t_iter = t_begin; !iterator_equal(t_iter, t_end); t_iter = iterator_next(t_iter))
    {
        t_result = _GET_VECTOR_TYPE_SIZE(pt_vector);
        _GET_VECTOR_TYPE_DESTROY_FUNCTION(pt_vector)(_GET_VECTOR_COREPOS(t_iter), &t_result);
        assert(t_result);
    }
    /* move the element */
    t_erasesize = iterator_distance(t_begin, t_end);
    memmove(_GET_VECTOR_COREPOS(t_begin), _GET_VECTOR_COREPOS(t_end),
        pt_vector->_pc_finish - _GET_VECTOR_COREPOS(t_end));
    pt_vector->_pc_finish -= t_erasesize * _GET_VECTOR_TYPE_SIZE(pt_vector);

    return t_begin;
}

void vector_resize(vector_t* pt_vector, size_t t_resize)
{
    vector_resize_elem(pt_vector, t_resize, 0x00);
}

void _vector_resize_elem_varg(
    vector_t* pt_vector, size_t t_resize, va_list val_elemlist)
{
    vector_iterator_t t_cutpos;     /* the cut position */
    size_t            t_expsize = 0;
    size_t            t_index = 0;
    void*             pv_varg = NULL;
    bool_t            t_result = false;

    assert(pt_vector != NULL);

    if(t_resize < vector_size(pt_vector))
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
        pv_varg = allocate(&pt_vector->_t_allocater, _GET_VECTOR_TYPE_SIZE(pt_vector), 1);
        assert(pv_varg != NULL);
        t_result = _GET_VECTOR_TYPE_SIZE(pt_vector);
        _GET_VECTOR_TYPE_INIT_FUNCTION(pt_vector)(pv_varg, &t_result);
        assert(t_result);
        _type_get_varg_value(&pt_vector->_t_typeinfo, val_elemlist, pv_varg);
        for(t_index = 0; t_index < t_expsize; ++t_index)
        {
            t_result = _GET_VECTOR_TYPE_SIZE(pt_vector);
            _GET_VECTOR_TYPE_COPY_FUNCTION(pt_vector)(
                pt_vector->_pc_finish + t_index * _GET_VECTOR_TYPE_SIZE(pt_vector),
                pv_varg, &t_result);
            assert(t_result);
        }
        t_result = _GET_VECTOR_TYPE_SIZE(pt_vector);
        _GET_VECTOR_TYPE_DESTROY_FUNCTION(pt_vector)(pv_varg, &t_result);
        assert(t_result);
        deallocate(&pt_vector->_t_allocater, pv_varg, _GET_VECTOR_TYPE_SIZE(pt_vector), 1);
        pt_vector->_pc_finish += t_expsize * _GET_VECTOR_TYPE_SIZE(pt_vector);
    }
}

void _vector_resize_elem(vector_t* pt_vector, size_t t_resize, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_resize);
    _vector_resize_elem_varg(pt_vector, t_resize, val_elemlist);
}

void vector_clear(vector_t* pt_vector)
{
    vector_erase_range(pt_vector, vector_begin(pt_vector), vector_end(pt_vector));
}

/** local function implementation section **/
#ifndef NDEBUG
static bool_t _vector_iterator_belong_to_vector(
    const vector_t* cpt_vector, vector_iterator_t t_iter)
{
    assert(cpt_vector != NULL);
    assert(_GET_VECTOR_CONTAINER(t_iter) == cpt_vector);

    if(_GET_VECTOR_COREPOS(t_iter) >= cpt_vector->_pc_start &&
       _GET_VECTOR_COREPOS(t_iter) <= cpt_vector->_pc_finish)
    {
        return true;
    }
    else
    {
        return false;
    }
}
#endif /* NDEBUG */

static bool_t _vector_same_vector_iterator_type(
    const vector_t* cpt_vector, vector_iterator_t t_iter)
{
    assert(cpt_vector != NULL && _GET_VECTOR_CONTAINER(t_iter) != NULL);
    assert(_GET_VECTOR_CONTAINER_TYPE(t_iter) == _VECTOR_CONTAINER &&
           _GET_VECTOR_ITERATOR_TYPE(t_iter) == _RANDOM_ACCESS_ITERATOR);
    return _vector_same_type(cpt_vector, _GET_VECTOR_CONTAINER(t_iter));
}

static bool_t _vector_same_type(
    const vector_t* cpt_vectorfirst, const vector_t* cpt_vectorsecond)
{
    assert(cpt_vectorfirst != NULL && cpt_vectorsecond != NULL);
    return _type_is_same(_GET_VECTOR_TYPE_NAME(cpt_vectorfirst),
                         _GET_VECTOR_TYPE_NAME(cpt_vectorsecond)) &&
           (cpt_vectorfirst->_t_typeinfo._pt_type == cpt_vectorsecond->_t_typeinfo._pt_type);
}

/** eof **/

