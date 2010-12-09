/*
 *  The implement of vector module.
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
#include <cstl/cstl_vector.h>

#include <cstl/cstring.h>

#include "cstl_vector_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Initialize empty vector container.
 */
void vector_init(vector_t* pvec_vector)
{
    assert(pvec_vector != NULL);
    assert(_vector_is_created(pvec_vector));

    vector_init_n(pvec_vector, 0);
}

/**
 * Initialize vector container with mutiple default element.
 */
void vector_init_n(vector_t* pvec_vector, size_t t_count)
{
    assert(pvec_vector != NULL);
    assert(_vector_is_created(pvec_vector));

    if(t_count > 0)
    {
        size_t t_newcapacity = _vector_calculate_new_capacity(0, t_count);

        pvec_vector->_pc_start = _alloc_allocate(
            &pvec_vector->_t_allocater, _GET_VECTOR_TYPE_SIZE(pvec_vector), t_newcapacity);
        assert(pvec_vector->_pc_start != NULL);
        pvec_vector->_pc_finish = pvec_vector->_pc_start + _GET_VECTOR_TYPE_SIZE(pvec_vector) * t_count;
        pvec_vector->_pc_endofstorage = pvec_vector->_pc_start + _GET_VECTOR_TYPE_SIZE(pvec_vector) * t_newcapacity;

        /* initialize all elements */
        _vector_init_elem_range_auxiliary(pvec_vector, pvec_vector->_pc_start, pvec_vector->_pc_finish);
    }
}

/**
 * Initialize vector container with an exist vector container.
 */
void vector_init_copy(vector_t* pvec_dest, const vector_t* cpvec_src)
{
    assert(pvec_dest != NULL);
    assert(cpvec_src != NULL);
    assert(_vector_is_created(pvec_dest));
    assert(_vector_is_inited(cpvec_src));
    assert(_vector_same_type(pvec_dest, cpvec_src));

    vector_init_copy_range(pvec_dest, vector_begin(cpvec_src), vector_end(cpvec_src));
}

/**
 * Initialize vector container with an exist vector range.
 */
void vector_init_copy_range(vector_t* pvec_dest, vector_iterator_t it_begin, vector_iterator_t it_end)
{
    vector_iterator_t it_dest;
    vector_iterator_t it_src;
    bool_t            b_result = false;

    assert(pvec_dest != NULL);
    assert(_vector_is_created(pvec_dest));
    assert(_vector_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(it_begin), it_begin));
    assert(_vector_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(it_end), it_end));
    assert(iterator_equal(it_begin, it_end) || _vector_iterator_before(it_begin, it_end));
    assert(_vector_same_vector_iterator_type(pvec_dest, it_begin));
    assert(_vector_same_vector_iterator_type(pvec_dest, it_end));

    /* initialize all elements with default value */
    vector_init_n(pvec_dest, iterator_distance(it_begin, it_end));

    /* copy values for range */
    for(it_dest = vector_begin(pvec_dest), it_src = it_begin;
        !iterator_equal(it_dest, vector_end(pvec_dest)) && !iterator_equal(it_src, it_end);
        it_dest = iterator_next(it_dest), it_src = iterator_next(it_src))
    {
        b_result = _GET_VECTOR_TYPE_SIZE(pvec_dest);
        _GET_VECTOR_TYPE_COPY_FUNCTION(pvec_dest)(_GET_VECTOR_COREPOS(it_dest), _GET_VECTOR_COREPOS(it_src), &b_result);
        assert(b_result);
    }
    assert(iterator_equal(it_dest, vector_end(pvec_dest)) && iterator_equal(it_src, it_end));
}

/**
 * Destroy vector container.
 */
void vector_destroy(vector_t* pvec_vector)
{
    assert(pvec_vector != NULL);
    assert(_vector_is_inited(pvec_vector) || _vector_is_created(pvec_vector));

    _vector_destroy_auxiliary(pvec_vector);
    /* free memory that malloced in _create_vector() function */
    free(pvec_vector);
}

/**
 * Get vector element size.
 */
size_t vector_size(const vector_t* cpvec_vector)
{
    assert(cpvec_vector != NULL);
    assert(_vector_is_inited(cpvec_vector));

    return (cpvec_vector->_pc_finish - cpvec_vector->_pc_start) / _GET_VECTOR_TYPE_SIZE(cpvec_vector);
}

/**
 * Test vector is empty.
 */
bool_t vector_empty(const vector_t* cpvec_vector)
{
    assert(cpvec_vector != NULL);
    assert(_vector_is_inited(cpvec_vector));
    
    return cpvec_vector->_pc_start == cpvec_vector->_pc_finish ? true : false;
}

/**
 * Return maximum element number.
 */
size_t vector_max_size(const vector_t* cpvec_vector)
{
    assert(cpvec_vector != NULL);
    assert(_vector_is_inited(cpvec_vector));

    return (size_t)(-1) / _GET_VECTOR_TYPE_SIZE(cpvec_vector);
}

/**
 * Get vector capacity.
 */
size_t vector_capacity(const vector_t* cpvec_vector)
{
    assert(cpvec_vector != NULL);
    assert(_vector_is_inited(cpvec_vector));

    return (cpvec_vector->_pc_endofstorage - cpvec_vector->_pc_start) / _GET_VECTOR_TYPE_SIZE(cpvec_vector);
}

/**
 * Set vector capacity.
 */
void vector_reserve(vector_t* pvec_vector, size_t t_reservesize)
{
    char*  pc_reservemem = NULL; /* new memory for reserve */
    char*  pc_newstart = NULL;
    char*  pc_newfinish = NULL;
    char*  pc_newendofstorage = NULL;
    char*  pc_newpos = NULL;
    char*  pc_oldpos = NULL;
    size_t t_oldsize = 0;
    size_t t_oldcapacity = 0;
    bool_t b_result = false;

    assert(pvec_vector != NULL);
    assert(_vector_is_inited(pvec_vector));

    if(vector_capacity(pvec_vector) < t_reservesize)
    {
        /* allocate the new vector with reserve size */
        pc_reservemem = _alloc_allocate(&pvec_vector->_t_allocater, _GET_VECTOR_TYPE_SIZE(pvec_vector), t_reservesize);
        assert(pc_reservemem != NULL);
        /* get the new position */
        t_oldsize = pvec_vector->_pc_finish - pvec_vector->_pc_start;
        t_oldcapacity = pvec_vector->_pc_endofstorage - pvec_vector->_pc_start;
        pc_newstart = pc_reservemem;
        pc_newfinish = pc_reservemem + t_oldsize;
        pc_newendofstorage = pc_reservemem + _GET_VECTOR_TYPE_SIZE(pvec_vector) * t_reservesize;

        /* initialize new elements */
        _vector_init_elem_range_auxiliary(pvec_vector, pc_newstart, pc_newfinish);

        /* copy elements from old memory and destroy those */
        for(pc_newpos = pc_newstart, pc_oldpos = pvec_vector->_pc_start;
            pc_newpos < pc_newfinish && pc_oldpos < pvec_vector->_pc_finish;
            pc_newpos += _GET_VECTOR_TYPE_SIZE(pvec_vector),
            pc_oldpos += _GET_VECTOR_TYPE_SIZE(pvec_vector))
        {
            /* copy from old vector_t memory */
            b_result = _GET_VECTOR_TYPE_SIZE(pvec_vector);
            _GET_VECTOR_TYPE_COPY_FUNCTION(pvec_vector)(pc_newpos, pc_oldpos, &b_result);
            assert(b_result);
            /* destroy old vector_t memory */
            b_result = _GET_VECTOR_TYPE_SIZE(pvec_vector);
            _GET_VECTOR_TYPE_DESTROY_FUNCTION(pvec_vector)(pc_oldpos, &b_result);
            assert(b_result);
        }
        assert(pc_newpos == pc_newfinish && pc_oldpos == pvec_vector->_pc_finish);

        /* free the old vector element */
        if(pvec_vector->_pc_start != NULL)
        {
            _alloc_deallocate(&pvec_vector->_t_allocater, pvec_vector->_pc_start,
                _GET_VECTOR_TYPE_SIZE(pvec_vector), t_oldcapacity / _GET_VECTOR_TYPE_SIZE(pvec_vector));
        }
        pvec_vector->_pc_start = pc_newstart;
        pvec_vector->_pc_finish = pc_newfinish;
        pvec_vector->_pc_endofstorage = pc_newendofstorage;
    }
}

/**
 * Test the two vectors are equal.
 */
bool_t vector_equal(const vector_t* cpvec_first, const vector_t* cpvec_second)
{
    vector_iterator_t it_first;
    vector_iterator_t it_second;
    bool_t            b_less = false;
    bool_t            b_greater = false;

    assert(cpvec_first != NULL);
    assert(cpvec_second != NULL);
    assert(_vector_is_inited(cpvec_first));
    assert(_vector_is_inited(cpvec_second));

    /* same vector container */
    if(cpvec_first == cpvec_second)
    {
        return true;
    }
    /* the element type is equal */
    if(!_vector_same_type(cpvec_first, cpvec_second))
    {
        return false;
    }
    /* the element count is equal */
    if(vector_size(cpvec_first) != vector_size(cpvec_second))
    {
        return false;
    }

    /* each element is equal */
    for(it_first = vector_begin(cpvec_first), it_second = vector_begin(cpvec_second);
        !iterator_equal(it_first, vector_end(cpvec_first)) && !iterator_equal(it_second, vector_end(cpvec_second));
        it_first = iterator_next(it_first), it_second = iterator_next(it_second))
    {
        b_less = _GET_VECTOR_TYPE_SIZE(cpvec_first);
        b_greater = _GET_VECTOR_TYPE_SIZE(cpvec_second);
        _GET_VECTOR_TYPE_LESS_FUNCTION(cpvec_first)(
            _GET_VECTOR_COREPOS(it_first), _GET_VECTOR_COREPOS(it_second), &b_less);
        _GET_VECTOR_TYPE_LESS_FUNCTION(cpvec_second)(
            _GET_VECTOR_COREPOS(it_second), _GET_VECTOR_COREPOS(it_first), &b_greater);
        if(b_less || b_greater)
        {
            return false;
        }
    }
    assert(iterator_equal(it_first, vector_end(cpvec_first)) &&
           iterator_equal(it_second, vector_end(cpvec_second)));

    return true;
}


/**
 * Test the two vectors are unequal.
 */
bool_t vector_not_equal(const vector_t* cpvec_first, const vector_t* cpvec_second)
{
    return !vector_equal(cpvec_first, cpvec_second);
}

/**
 * Test the first vector is less than the second vector.
 */
bool_t vector_less(const vector_t* cpvec_first, const vector_t* cpvec_second)
{
    bool_t b_result = false;
    vector_iterator_t it_first;
    vector_iterator_t it_second;

    assert(cpvec_first != NULL);
    assert(cpvec_second != NULL);
    assert(_vector_is_inited(cpvec_first));
    assert(_vector_is_inited(cpvec_second));
    assert(_vector_same_type(cpvec_first, cpvec_second));

    for(it_first = vector_begin(cpvec_first), it_second = vector_begin(cpvec_second);
        !iterator_equal(it_first, vector_end(cpvec_first)) && !iterator_equal(it_second, vector_end(cpvec_second));
        it_first = iterator_next(it_first), it_second = iterator_next(it_second))
    {
        b_result = _GET_VECTOR_TYPE_SIZE(cpvec_first);
        _GET_VECTOR_TYPE_LESS_FUNCTION(cpvec_first)(
            _GET_VECTOR_COREPOS(it_first), _GET_VECTOR_COREPOS(it_second), &b_result);
        /* if any element in first vector are less then the second return true */
        if(b_result)
        {
            return true;
        }
        b_result = _GET_VECTOR_TYPE_SIZE(cpvec_first);
        _GET_VECTOR_TYPE_LESS_FUNCTION(cpvec_first)(
            _GET_VECTOR_COREPOS(it_second), _GET_VECTOR_COREPOS(it_first), &b_result);
        /* if any element in first vector are greater then the second return false */
        if(b_result)
        {
            return false;
        }
    }

    /* if the first n elements in two vector are equal then compare the vector size */
    return vector_size(cpvec_first) < vector_size(cpvec_second) ? true : false;
}

/**
 * Test the first vector is less than or equal to the second vector.
 */
bool_t vector_less_equal(const vector_t* cpvec_first, const vector_t* cpvec_second)
{
    return (vector_less(cpvec_first, cpvec_second) || vector_equal(cpvec_first, cpvec_second)) ? true : false;
}

/**
 * Test the first vector is greater than the second vector.
 */
bool_t vector_greater(const vector_t* cpvec_first, const vector_t* cpvec_second)
{
    return vector_less(cpvec_second, cpvec_first);
}

/**
 * Test the first vector is greater than or equal to the second vector.
 */
bool_t vector_greater_equal(const vector_t* cpvec_first, const vector_t* cpvec_second)
{
    return (vector_greater(cpvec_first, cpvec_second) || vector_equal(cpvec_first, cpvec_second)) ? true : false;
}

/**
 * Assign vector element with an exist vector container.
 */
void vector_assign(vector_t* pvec_dest, const vector_t* cpvec_src)
{
    assert(pvec_dest != NULL);
    assert(cpvec_src != NULL);
    assert(_vector_is_inited(pvec_dest));
    assert(_vector_is_inited(cpvec_src));
    assert(_vector_same_type(pvec_dest, cpvec_src));

    if(vector_equal(pvec_dest, cpvec_src))
    {
        return;
    }

    vector_assign_range(pvec_dest, vector_begin(cpvec_src), vector_end(cpvec_src));
}

/**
 * Assign vector element with an exist vector container range.
 */
void vector_assign_range(vector_t* pvec_vector, vector_iterator_t it_begin, vector_iterator_t it_end)
{
    iterator_t it_dest;
    iterator_t it_src;
    bool_t     b_result = false;

    /* assign the two iterator is as the same type as pvec_vector */
    assert(pvec_vector != NULL);
    assert(_vector_is_inited(pvec_vector));
    /*assert(!_vector_iterator_belong_to_vector(pvec_vector, it_begin));*/
    /*assert(!_vector_iterator_belong_to_vector(pvec_vector, it_end));*/
    assert(_vector_same_vector_iterator_type(pvec_vector, it_begin));
    assert(_vector_same_vector_iterator_type(pvec_vector, it_end));
    assert(iterator_equal(it_begin, it_end) || _vector_iterator_before(it_begin, it_end));

    /* copy value from range [it_begin, it_end) for each element */
    vector_resize(pvec_vector, iterator_distance(it_begin, it_end));
    for(it_dest = vector_begin(pvec_vector), it_src = it_begin;
        !iterator_equal(it_dest, vector_end(pvec_vector)) && !iterator_equal(it_src, it_end);
        it_dest = iterator_next(it_dest), it_src = iterator_next(it_src))
    {
        b_result = _GET_VECTOR_TYPE_SIZE(pvec_vector);
        _GET_VECTOR_TYPE_COPY_FUNCTION(pvec_vector)(_GET_VECTOR_COREPOS(it_dest), _GET_VECTOR_COREPOS(it_src), &b_result);
        assert(b_result);
    }
    assert(iterator_equal(it_dest, vector_end(pvec_vector)) && iterator_equal(it_src, it_end));
}

/**
 * Swap vector datas.
 */
void vector_swap(vector_t* pvec_first, vector_t* pvec_second)
{
    vector_t vec_swap;  /* the swap temporary vector */

    /* test the two vector has the same type */
    assert(pvec_first != NULL);
    assert(pvec_second != NULL);
    assert(_vector_is_inited(pvec_first));
    assert(_vector_is_inited(pvec_second));
    assert(_vector_same_type(pvec_first, pvec_second));

    if(vector_equal(pvec_first, pvec_second))
    {
        return;
    }

    vec_swap = *pvec_first;
    *pvec_first = *pvec_second;
    *pvec_second = vec_swap;
}

/**
 * Access vector data using subscript.
 */
void* vector_at(const vector_t* cpvec_vector, size_t t_pos)
{
    assert(cpvec_vector != NULL);
    assert(_vector_is_inited(cpvec_vector));
    assert(t_pos < vector_size(cpvec_vector));

    /* char* */
    if(strncmp(_GET_VECTOR_TYPE_BASENAME(cpvec_vector), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        return (char*)string_c_str((string_t*)(cpvec_vector->_pc_start + t_pos * _GET_VECTOR_TYPE_SIZE(cpvec_vector)));
    }
    else
    {
        return cpvec_vector->_pc_start + t_pos * _GET_VECTOR_TYPE_SIZE(cpvec_vector);
    }
}

/**
 * Access first vector data.
 */
void* vector_front(const vector_t* cpvec_vector)
{
    assert(cpvec_vector != NULL);
    assert(_vector_is_inited(cpvec_vector));
    assert(!vector_empty(cpvec_vector));

    return vector_at(cpvec_vector, 0);
}

/**
 * Access last vector data.
 */
void* vector_back(const vector_t* cpvec_vector)
{
    assert(cpvec_vector != NULL);
    assert(_vector_is_inited(cpvec_vector));
    assert(!vector_empty(cpvec_vector));

    return vector_at(cpvec_vector, vector_size(cpvec_vector) - 1);
}

/**
 * Return a iterator to the first element in the vector container.
 */
vector_iterator_t vector_begin(const vector_t* cpvec_vector)
{
    vector_iterator_t it_begin; /* new vector iterator */

    assert(cpvec_vector != NULL);
    assert(_vector_is_inited(cpvec_vector));

    it_begin = _create_vector_iterator();
    _GET_CONTAINER(it_begin) = (vector_t*)cpvec_vector;
    _GET_VECTOR_COREPOS(it_begin) = cpvec_vector->_pc_start;

    return it_begin;
}

/**
 * Return a iterator that points just beyond the end of vector container.
 */
vector_iterator_t vector_end(const vector_t* cpvec_vector)
{
    vector_iterator_t it_end;

    assert(cpvec_vector != NULL);
    assert(_vector_is_inited(cpvec_vector));

    it_end = _create_vector_iterator();
    _GET_CONTAINER(it_end) = (vector_t*)cpvec_vector;
    _GET_VECTOR_COREPOS(it_end) = cpvec_vector->_pc_finish;

    return it_end;
}

vector_reverse_iterator_t vector_rbegin(const vector_t* cpvec_vector)
{
    vector_reverse_iterator_t it_rbegin;

    assert(cpvec_vector != NULL);
    assert(_vector_is_inited(cpvec_vector));

    it_rbegin = _create_vector_iterator();
    _GET_CONTAINER(it_rbegin) = (vector_t*)cpvec_vector;
    _GET_VECTOR_COREPOS(it_rbegin) = cpvec_vector->_pc_finish - _GET_VECTOR_TYPE_SIZE(cpvec_vector);

    return it_rbegin;
}

vector_reverse_iterator_t vector_rend(const vector_t* cpvec_vector)
{
    vector_reverse_iterator_t it_rend;

    assert(cpvec_vector != NULL);
    assert(_vector_is_inited(cpvec_vector));

    it_rend = _create_vector_iterator();
    _GET_CONTAINER(it_rend) = (vector_t*)cpvec_vector;
    _GET_VECTOR_COREPOS(it_rend) = cpvec_vector->_pc_start - _GET_VECTOR_TYPE_SIZE(cpvec_vector);

    return it_rend;
}

/**
 * Insert a range of elements into vector at a specificed position.
 */
void vector_insert_range(
    vector_t* pt_vector, vector_iterator_t t_pos,
    vector_iterator_t t_begin, vector_iterator_t t_end)
{
    size_t t_count = 0; /* the element count */
    bool_t t_result = false;
    vector_iterator_t t_iterfirst;
    vector_iterator_t t_itersecond;
    char*             pc_oldfinish = NULL;
    char*             pc_pos = NULL;
    char*             pc_destpos = NULL;

    /* test the vector and iterator is valid */
    assert(_vector_iterator_belong_to_vector(pt_vector, t_pos));
    assert(iterator_equal(t_begin, t_end) || _vector_iterator_before(t_begin, t_end));
    assert(_vector_same_vector_iterator_type(pt_vector, t_begin));

    t_count = iterator_distance(t_begin, t_end);
    if(t_count > 0)
    {
        /* if the remain capacity is less then the element count */
        if(vector_size(pt_vector) + t_count > vector_capacity(pt_vector))
        {
            size_t t_iteratordistance = _GET_VECTOR_COREPOS(t_pos) - pt_vector->_pc_start;
            /* reserve the new size */
            /* new size = old size + 2 * element count */
            vector_reserve(pt_vector, vector_size(pt_vector) + 2 * t_count);
            _GET_VECTOR_COREPOS(t_pos) = pt_vector->_pc_start + t_iteratordistance;
        }

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

        /* insert element counts copys to the pos */
        for(t_iterfirst = t_pos, t_itersecond = t_begin;
            !iterator_equal(t_itersecond, t_end);
            t_iterfirst = iterator_next(t_iterfirst),
            t_itersecond = iterator_next(t_itersecond))
        {
            t_result = _GET_VECTOR_TYPE_SIZE(pt_vector);
            _GET_VECTOR_TYPE_COPY_FUNCTION(pt_vector)(_GET_VECTOR_COREPOS(t_iterfirst),
                _GET_VECTOR_COREPOS(t_itersecond), &t_result);
            assert(t_result);
        }
        assert(_GET_VECTOR_COREPOS(t_iterfirst) == _GET_VECTOR_COREPOS(t_pos) +
               (_GET_VECTOR_COREPOS(t_end) - _GET_VECTOR_COREPOS(t_begin)));
    }
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
    bool_t     t_result = false;
    iterator_t t_iter;
    iterator_t t_prev;

    assert(_vector_iterator_belong_to_vector(pt_vector, t_pos));
    assert(!iterator_equal(t_pos, vector_end(pt_vector)));

    /* move element */
    for(t_iter = iterator_next(t_pos), t_prev = t_pos;
        !iterator_equal(t_iter, vector_end(pt_vector));
        t_iter = iterator_next(t_iter), t_prev = iterator_next(t_prev))
    {
        t_result = _GET_VECTOR_TYPE_SIZE(pt_vector);
        _GET_VECTOR_TYPE_COPY_FUNCTION(pt_vector)(
            _GET_VECTOR_COREPOS(t_prev), _GET_VECTOR_COREPOS(t_iter), &t_result);
        assert(t_result);
    }
    assert(_GET_VECTOR_COREPOS(t_prev) ==
           pt_vector->_pc_finish - _GET_VECTOR_TYPE_SIZE(pt_vector));

    /* destroy the deleted element */
    t_result = _GET_VECTOR_TYPE_SIZE(pt_vector);
    _GET_VECTOR_TYPE_DESTROY_FUNCTION(pt_vector)(_GET_VECTOR_COREPOS(t_prev), &t_result);
    assert(t_result);

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

    if(iterator_equal(t_begin, t_end))
    {
        return t_end;
    }

    t_iter = t_begin;
    t_erasesize = iterator_distance(t_begin, t_end);

    for(; !iterator_equal(t_end, vector_end(pt_vector));
        t_begin = iterator_next(t_begin), t_end = iterator_next(t_end))
    {
        t_result = _GET_VECTOR_TYPE_SIZE(pt_vector);
        _GET_VECTOR_TYPE_COPY_FUNCTION(pt_vector)(
            _GET_VECTOR_COREPOS(t_begin), _GET_VECTOR_COREPOS(t_end), &t_result);
        assert(t_result);
    }
    assert(_GET_VECTOR_COREPOS(t_begin) ==
           pt_vector->_pc_finish - t_erasesize * _GET_VECTOR_TYPE_SIZE(pt_vector));

    /* destroy the deleted elements */
    for(; !iterator_equal(t_begin, t_end); t_begin = iterator_next(t_begin))
    {
        t_result = _GET_VECTOR_TYPE_SIZE(pt_vector);
        _GET_VECTOR_TYPE_DESTROY_FUNCTION(pt_vector)(_GET_VECTOR_COREPOS(t_begin), &t_result);
        assert(t_result);
    }
    pt_vector->_pc_finish -= t_erasesize * _GET_VECTOR_TYPE_SIZE(pt_vector);

    return t_iter;
}

void vector_resize(vector_t* pt_vector, size_t t_resize)
{
    vector_iterator_t t_cutpos;     /* the cut position */
    size_t            t_expsize = 0;
    char*             pc_oldfinish = NULL;

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

        /* initialize new elements */
        pc_oldfinish = pt_vector->_pc_finish;
        pt_vector->_pc_finish += t_expsize * _GET_VECTOR_TYPE_SIZE(pt_vector);
        _vector_init_elem_range_auxiliary(pt_vector, pc_oldfinish, pt_vector->_pc_finish);
    }
}

void vector_clear(vector_t* pt_vector)
{
    vector_erase_range(pt_vector, vector_begin(pt_vector), vector_end(pt_vector));
}

/** local function implementation section **/

/** eof **/

