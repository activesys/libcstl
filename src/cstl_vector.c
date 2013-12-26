/*
 *  The implement of vector module.
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

    if (t_count > 0) {
        size_t t_newcapacity = _vector_calculate_new_capacity(0, t_count);

        pvec_vector->_pby_start = _alloc_allocate(&pvec_vector->_t_allocator, _GET_VECTOR_TYPE_SIZE(pvec_vector), t_newcapacity);
        assert(pvec_vector->_pby_start != NULL);
        pvec_vector->_pby_finish = pvec_vector->_pby_start + _GET_VECTOR_TYPE_SIZE(pvec_vector) * t_count;
        pvec_vector->_pby_endofstorage = pvec_vector->_pby_start + _GET_VECTOR_TYPE_SIZE(pvec_vector) * t_newcapacity;

        /* initialize all elements */
        _vector_init_elem_range_auxiliary(pvec_vector, pvec_vector->_pby_start, pvec_vector->_pby_finish);
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
 * Initialize vector container with an exist range.
 */
void vector_init_copy_range(vector_t* pvec_dest, iterator_t it_begin, iterator_t it_end)
{
    iterator_t it_dest_begin;
    iterator_t it_dest_end;
    iterator_t it_dest;
    iterator_t it_src;
    bool_t     b_result = false;

    assert(pvec_dest != NULL);
    assert(_vector_is_created(pvec_dest));
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));
    assert(_vector_same_iterator_type(pvec_dest, it_begin));
    assert(_vector_same_iterator_type(pvec_dest, it_end));

    /* initialize all elements with default value */
    vector_init_n(pvec_dest, iterator_distance(it_begin, it_end));

    /* copy values for range */
    it_dest_begin = vector_begin(pvec_dest);
    it_dest_end = vector_end(pvec_dest);
    for (it_dest = it_dest_begin, it_src = it_begin;
         !iterator_equal(it_dest, it_dest_end) && !iterator_equal(it_src, it_end);
         it_dest = iterator_next(it_dest), it_src = iterator_next(it_src)) {
        b_result = _GET_VECTOR_TYPE_SIZE(pvec_dest);
        _GET_VECTOR_TYPE_COPY_FUNCTION(pvec_dest)(
            _iterator_get_pointer_ignore_cstr(it_dest),
            _iterator_get_pointer_ignore_cstr(it_src), &b_result);
        assert(b_result);
    }
    assert(iterator_equal(it_dest, it_dest_end) && iterator_equal(it_src, it_end));
}

/**
 * Initialize vector container with an exist array.
 */
void vector_init_copy_array(vector_t* pvec_dest, const void* cpv_array, size_t t_count)
{
    iterator_t it_dest;
    iterator_t it_begin;
    iterator_t it_end;
    bool_t     b_result = false;
    size_t     i = 0;

    assert(pvec_dest != NULL);
    assert(_vector_is_created(pvec_dest));
    assert(cpv_array != NULL);

    /* initialize all elements with default value */
    vector_init_n(pvec_dest, t_count);
    it_begin = vector_begin(pvec_dest);
    it_end = vector_end(pvec_dest);

    /*
     * Copy the elements from src array to dest vector.
     * The array of c builtin and user define or cstl builtin are different,
     * the elements of c builtin array are element itself, but the elements of 
     * c string, user define or cstl are pointer of element.
     */
    if (strncmp(_GET_VECTOR_TYPE_BASENAME(pvec_dest), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        /*
         * We need built a string_t for c string element.
         */
        string_t* pstr_elem = create_string();
        assert(pstr_elem != NULL);
        string_init(pstr_elem);

        for (it_dest = it_begin, i = 0;
             !iterator_equal(it_dest, it_end) && i < t_count;
             it_dest = iterator_next(it_dest), ++i) {
            string_assign_cstr(pstr_elem, *((const char**)cpv_array + i));
            b_result = _GET_VECTOR_TYPE_SIZE(pvec_dest);
            _GET_VECTOR_TYPE_COPY_FUNCTION(pvec_dest)(
                _iterator_get_pointer_ignore_cstr(it_dest), pstr_elem, &b_result);
            assert(b_result);
        }
        string_destroy(pstr_elem);
    } else if (_GET_VECTOR_TYPE_STYLE(pvec_dest) == _TYPE_C_BUILTIN) {
        for (it_dest = it_begin, i = 0;
             !iterator_equal(it_dest, it_end) && i < t_count;
             it_dest = iterator_next(it_dest), ++i) {
            b_result = _GET_VECTOR_TYPE_SIZE(pvec_dest);
            _GET_VECTOR_TYPE_COPY_FUNCTION(pvec_dest)(
                _iterator_get_pointer_ignore_cstr(it_dest),
                (unsigned char*)cpv_array + i * _GET_VECTOR_TYPE_SIZE(pvec_dest), &b_result);
            assert(b_result);
        }
    } else {
        for (it_dest = it_begin, i = 0;
             !iterator_equal(it_dest, it_end) && i < t_count;
             it_dest = iterator_next(it_dest), ++i) {
            b_result = _GET_VECTOR_TYPE_SIZE(pvec_dest);
            _GET_VECTOR_TYPE_COPY_FUNCTION(pvec_dest)(
                _iterator_get_pointer_ignore_cstr(it_dest), *((void**)cpv_array + i), &b_result);
            assert(b_result);
        }
    }
    assert(iterator_equal(it_dest, it_end) && i == t_count);
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

    return (cpvec_vector->_pby_finish - cpvec_vector->_pby_start) / _GET_VECTOR_TYPE_SIZE(cpvec_vector);
}

/**
 * Test vector is empty.
 */
bool_t vector_empty(const vector_t* cpvec_vector)
{
    assert(cpvec_vector != NULL);
    assert(_vector_is_inited(cpvec_vector));
    
    return cpvec_vector->_pby_start == cpvec_vector->_pby_finish ? true : false;
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

    return (cpvec_vector->_pby_endofstorage - cpvec_vector->_pby_start) / _GET_VECTOR_TYPE_SIZE(cpvec_vector);
}

/**
 * Set vector capacity.
 */
void vector_reserve(vector_t* pvec_vector, size_t t_reservesize)
{
    _byte_t* pby_reservemem = NULL; /* new memory for reserve */
    _byte_t* pby_newstart = NULL;
    _byte_t* pby_newfinish = NULL;
    _byte_t* pby_newendofstorage = NULL;
    _byte_t* pby_newpos = NULL;
    _byte_t* pby_oldpos = NULL;
    size_t   t_oldsize = 0;
    size_t   t_oldcapacity = 0;
    bool_t   b_result = false;

    assert(pvec_vector != NULL);
    assert(_vector_is_inited(pvec_vector));

    if (vector_capacity(pvec_vector) < t_reservesize) {
        /* allocate the new vector with reserve size */
        pby_reservemem = _alloc_allocate(&pvec_vector->_t_allocator, _GET_VECTOR_TYPE_SIZE(pvec_vector), t_reservesize);
        assert(pby_reservemem != NULL);
        /* get the new position */
        t_oldsize = pvec_vector->_pby_finish - pvec_vector->_pby_start;
        t_oldcapacity = pvec_vector->_pby_endofstorage - pvec_vector->_pby_start;
        pby_newstart = pby_reservemem;
        pby_newfinish = pby_reservemem + t_oldsize;
        pby_newendofstorage = pby_reservemem + _GET_VECTOR_TYPE_SIZE(pvec_vector) * t_reservesize;

        /* initialize new elements */
        _vector_init_elem_range_auxiliary(pvec_vector, pby_newstart, pby_newfinish);

        /* copy elements from old memory and destroy those */
        for (pby_newpos = pby_newstart, pby_oldpos = pvec_vector->_pby_start;
             pby_newpos < pby_newfinish && pby_oldpos < pvec_vector->_pby_finish;
             pby_newpos += _GET_VECTOR_TYPE_SIZE(pvec_vector),
             pby_oldpos += _GET_VECTOR_TYPE_SIZE(pvec_vector)) {
            /* copy from old vector_t memory */
            b_result = _GET_VECTOR_TYPE_SIZE(pvec_vector);
            _GET_VECTOR_TYPE_COPY_FUNCTION(pvec_vector)(pby_newpos, pby_oldpos, &b_result);
            assert(b_result);
            /* destroy old vector_t memory */
            b_result = _GET_VECTOR_TYPE_SIZE(pvec_vector);
            _GET_VECTOR_TYPE_DESTROY_FUNCTION(pvec_vector)(pby_oldpos, &b_result);
            assert(b_result);
        }
        assert(pby_newpos == pby_newfinish && pby_oldpos == pvec_vector->_pby_finish);

        /* free the old vector element */
        if (pvec_vector->_pby_start != NULL) {
            _alloc_deallocate(&pvec_vector->_t_allocator, pvec_vector->_pby_start,
                _GET_VECTOR_TYPE_SIZE(pvec_vector), t_oldcapacity / _GET_VECTOR_TYPE_SIZE(pvec_vector));
        }
        pvec_vector->_pby_start = pby_newstart;
        pvec_vector->_pby_finish = pby_newfinish;
        pvec_vector->_pby_endofstorage = pby_newendofstorage;
    }
}

/**
 * Test the two vectors are equal.
 */
bool_t vector_equal(const vector_t* cpvec_first, const vector_t* cpvec_second)
{
    vector_iterator_t it_first;
    vector_iterator_t it_first_begin;
    vector_iterator_t it_first_end;
    vector_iterator_t it_second;
    vector_iterator_t it_second_begin;
    vector_iterator_t it_second_end;
    bool_t            b_less = false;
    bool_t            b_greater = false;

    assert(cpvec_first != NULL);
    assert(cpvec_second != NULL);
    assert(_vector_is_inited(cpvec_first));
    assert(_vector_is_inited(cpvec_second));
    assert(_vector_same_type(cpvec_first, cpvec_second));

    /* same vector container */
    if (cpvec_first == cpvec_second) {
        return true;
    }
    /* the element count is equal */
    if (vector_size(cpvec_first) != vector_size(cpvec_second)) {
        return false;
    }

    it_first_begin = vector_begin(cpvec_first);
    it_first_end = vector_end(cpvec_first);
    it_second_begin = vector_begin(cpvec_second);
    it_second_end = vector_end(cpvec_second);

    /* each element is equal */
    for (it_first = it_first_begin, it_second = it_second_begin;
         !iterator_equal(it_first, it_first_end) && !iterator_equal(it_second, it_second_end);
         it_first = iterator_next(it_first), it_second = iterator_next(it_second)) {
        b_less = _GET_VECTOR_TYPE_SIZE(cpvec_first);
        b_greater = _GET_VECTOR_TYPE_SIZE(cpvec_second);
        _GET_VECTOR_TYPE_LESS_FUNCTION(cpvec_first)(_VECTOR_ITERATOR_COREPOS(it_first), _VECTOR_ITERATOR_COREPOS(it_second), &b_less);
        _GET_VECTOR_TYPE_LESS_FUNCTION(cpvec_second)(_VECTOR_ITERATOR_COREPOS(it_second), _VECTOR_ITERATOR_COREPOS(it_first), &b_greater);
        if (b_less || b_greater) {
            return false;
        }
    }
    assert(iterator_equal(it_first, it_first_end) && iterator_equal(it_second, it_second_end));

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
    vector_iterator_t it_first_begin;
    vector_iterator_t it_first_end;
    vector_iterator_t it_second;
    vector_iterator_t it_second_begin;
    vector_iterator_t it_second_end;

    assert(cpvec_first != NULL);
    assert(cpvec_second != NULL);
    assert(_vector_is_inited(cpvec_first));
    assert(_vector_is_inited(cpvec_second));
    assert(_vector_same_type(cpvec_first, cpvec_second));

    it_first_begin = vector_begin(cpvec_first);
    it_first_end = vector_end(cpvec_first);
    it_second_begin = vector_begin(cpvec_second);
    it_second_end = vector_end(cpvec_second);

    for (it_first = it_first_begin, it_second = it_second_begin;
         !iterator_equal(it_first, it_first_end) && !iterator_equal(it_second, it_second_end);
         it_first = iterator_next(it_first), it_second = iterator_next(it_second)) {
        b_result = _GET_VECTOR_TYPE_SIZE(cpvec_first);
        _GET_VECTOR_TYPE_LESS_FUNCTION(cpvec_first)(_VECTOR_ITERATOR_COREPOS(it_first), _VECTOR_ITERATOR_COREPOS(it_second), &b_result);
        /* if any element in first vector are less then the second return true */
        if (b_result) {
            return true;
        }
        b_result = _GET_VECTOR_TYPE_SIZE(cpvec_first);
        _GET_VECTOR_TYPE_LESS_FUNCTION(cpvec_first)(_VECTOR_ITERATOR_COREPOS(it_second), _VECTOR_ITERATOR_COREPOS(it_first), &b_result);
        /* if any element in first vector are greater then the second return false */
        if (b_result) {
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

    if (vector_equal(pvec_dest, cpvec_src)) {
        return;
    }

    vector_assign_range(pvec_dest, vector_begin(cpvec_src), vector_end(cpvec_src));
}

/**
 * Assign vector element with an exist container range.
 */
void vector_assign_range(vector_t* pvec_vector, iterator_t it_begin, iterator_t it_end)
{
    iterator_t it_dest_begin;
    iterator_t it_dest_end;
    iterator_t it_dest;
    iterator_t it_src;
    bool_t     b_result = false;

    /* assign the two iterator is as the same type as pvec_vector */
    assert(pvec_vector != NULL);
    assert(_vector_is_inited(pvec_vector));
    /*assert(!_vector_iterator_belong_to_vector(pvec_vector, it_begin));*/
    /*assert(!_vector_iterator_belong_to_vector(pvec_vector, it_end));*/
    assert(_vector_same_iterator_type(pvec_vector, it_begin));
    assert(_vector_same_iterator_type(pvec_vector, it_end));
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));

    /* copy value from range [it_begin, it_end) for each element */
    vector_resize(pvec_vector, iterator_distance(it_begin, it_end));
    it_dest_begin = vector_begin(pvec_vector);
    it_dest_end = vector_end(pvec_vector);
    for (it_dest = it_dest_begin, it_src = it_begin;
         !iterator_equal(it_dest, it_dest_end) && !iterator_equal(it_src, it_end);
         it_dest = iterator_next(it_dest), it_src = iterator_next(it_src)) {
        b_result = _GET_VECTOR_TYPE_SIZE(pvec_vector);
        _GET_VECTOR_TYPE_COPY_FUNCTION(pvec_vector)(
            _iterator_get_pointer_ignore_cstr(it_dest),
            _iterator_get_pointer_ignore_cstr(it_src), &b_result);
        assert(b_result);
    }
    assert(iterator_equal(it_dest, it_dest_end) && iterator_equal(it_src, it_end));
}

/**
 * Assign vector element with an exist container array.
 */
void vector_assign_array(vector_t* pvec_vector, const void* cpv_array, size_t t_count)
{
    iterator_t it_dest;
    iterator_t it_begin;
    iterator_t it_end;
    bool_t     b_result = false;
    size_t     i = 0;

    /* assign the two iterator is as the same type as pvec_vector */
    assert(pvec_vector != NULL);
    assert(_vector_is_inited(pvec_vector));
    assert(cpv_array != NULL);

    /* copy value from array for each element */
    vector_resize(pvec_vector, t_count);
    it_begin = vector_begin(pvec_vector);
    it_end = vector_end(pvec_vector);

    /*
     * Copy the elements from src array to dest vector.
     * The array of c builtin and user define or cstl builtin are different,
     * the elements of c builtin array are element itself, but the elements of 
     * c string, user define or cstl are pointer of element.
     */
    if (strncmp(_GET_VECTOR_TYPE_BASENAME(pvec_vector), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        /*
         * We need built a string_t for c string element.
         */
        string_t* pstr_elem = create_string();
        assert(pstr_elem != NULL);
        string_init(pstr_elem);

        for (it_dest = it_begin, i = 0;
             !iterator_equal(it_dest, it_end) && i < t_count;
             it_dest = iterator_next(it_dest), ++i) {
            string_assign_cstr(pstr_elem, *((const char**)cpv_array + i));
            b_result = _GET_VECTOR_TYPE_SIZE(pvec_vector);
            _GET_VECTOR_TYPE_COPY_FUNCTION(pvec_vector)(
                _iterator_get_pointer_ignore_cstr(it_dest), pstr_elem, &b_result);
            assert(b_result);
        }
        string_destroy(pstr_elem);
    } else if (_GET_VECTOR_TYPE_STYLE(pvec_vector) == _TYPE_C_BUILTIN) {
        for (it_dest = it_begin, i = 0;
             !iterator_equal(it_dest, it_end) && i < t_count;
             it_dest = iterator_next(it_dest), ++i) {
            b_result = _GET_VECTOR_TYPE_SIZE(pvec_vector);
            _GET_VECTOR_TYPE_COPY_FUNCTION(pvec_vector)(
                _iterator_get_pointer_ignore_cstr(it_dest),
                (unsigned char*)cpv_array + i * _GET_VECTOR_TYPE_SIZE(pvec_vector), &b_result);
            assert(b_result);
        }
    } else {
        for (it_dest = it_begin, i = 0;
             !iterator_equal(it_dest, it_end) && i < t_count;
             it_dest = iterator_next(it_dest), ++i) {
            b_result = _GET_VECTOR_TYPE_SIZE(pvec_vector);
            _GET_VECTOR_TYPE_COPY_FUNCTION(pvec_vector)(
                _iterator_get_pointer_ignore_cstr(it_dest), *((void**)cpv_array + i), &b_result);
            assert(b_result);
        }
    }
    assert(iterator_equal(it_dest, it_end) && i == t_count);
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

    if (vector_equal(pvec_first, pvec_second)) {
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

    return (void*)iterator_get_pointer(iterator_next_n(vector_begin(cpvec_vector), t_pos));
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
    _ITERATOR_CONTAINER(it_begin) = (vector_t*)cpvec_vector;
    _VECTOR_ITERATOR_COREPOS(it_begin) = cpvec_vector->_pby_start;

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
    _ITERATOR_CONTAINER(it_end) = (vector_t*)cpvec_vector;
    _VECTOR_ITERATOR_COREPOS(it_end) = cpvec_vector->_pby_finish;

    return it_end;
}

vector_reverse_iterator_t vector_rbegin(const vector_t* cpvec_vector)
{
    vector_reverse_iterator_t it_rbegin;

    assert(cpvec_vector != NULL);
    assert(_vector_is_inited(cpvec_vector));

    it_rbegin = _create_vector_iterator();
    _ITERATOR_CONTAINER(it_rbegin) = (vector_t*)cpvec_vector;
    _VECTOR_ITERATOR_COREPOS(it_rbegin) = cpvec_vector->_pby_finish - _GET_VECTOR_TYPE_SIZE(cpvec_vector);

    return it_rbegin;
}

vector_reverse_iterator_t vector_rend(const vector_t* cpvec_vector)
{
    vector_reverse_iterator_t it_rend;

    assert(cpvec_vector != NULL);
    assert(_vector_is_inited(cpvec_vector));

    it_rend = _create_vector_iterator();
    _ITERATOR_CONTAINER(it_rend) = (vector_t*)cpvec_vector;
    _VECTOR_ITERATOR_COREPOS(it_rend) = cpvec_vector->_pby_start - _GET_VECTOR_TYPE_SIZE(cpvec_vector);

    return it_rend;
}

/**
 * Insert a range of elements into vector at a specificed position.
 */
void vector_insert_range(vector_t* pvec_vector, vector_iterator_t it_pos, iterator_t it_begin, iterator_t it_end)
{
    size_t     t_count = 0; /* the element count */
    bool_t     b_result = false;
    iterator_t it_first;
    iterator_t it_second;
    _byte_t*   pby_oldfinish = NULL;
    _byte_t*   pby_pos = NULL;
    _byte_t*   pby_destpos = NULL;

    /* test the vector and iterator is valid */
    assert(pvec_vector != NULL);
    assert(_vector_is_inited(pvec_vector));
    assert(_vector_iterator_belong_to_vector(pvec_vector, it_pos));
    /*assert(!_vector_iterator_belong_to_vector(pvec_vector, it_begin));*/
    /*assert(!_vector_iterator_belong_to_vector(pvec_vector, it_end));*/
    assert(_vector_same_iterator_type(pvec_vector, it_begin));
    assert(_vector_same_iterator_type(pvec_vector, it_end));
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));

    t_count = iterator_distance(it_begin, it_end);
    if (t_count > 0) {
        /* if the remain capacity is less then the element count */
        if (vector_size(pvec_vector) + t_count > vector_capacity(pvec_vector)) {
            size_t t_distance = _VECTOR_ITERATOR_COREPOS(it_pos) - pvec_vector->_pby_start;
            /* reserve the new size */
            vector_reserve(pvec_vector, _vector_calculate_new_capacity(vector_size(pvec_vector), t_count));
            _VECTOR_ITERATOR_COREPOS(it_pos) = pvec_vector->_pby_start + t_distance;
        }

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

        /* insert element counts copys to the pos */
        for (it_first = it_pos, it_second = it_begin;
             !iterator_equal(it_second, it_end);
             it_first = iterator_next(it_first), it_second = iterator_next(it_second)) {
            b_result = _GET_VECTOR_TYPE_SIZE(pvec_vector);
            _GET_VECTOR_TYPE_COPY_FUNCTION(pvec_vector)(
                _iterator_get_pointer_ignore_cstr(it_first),
                _iterator_get_pointer_ignore_cstr(it_second), &b_result);
            assert(b_result);
        }
        assert((size_t)iterator_distance(it_pos, it_first) == t_count);
    }
}

/**
 * Insert an array of elements into vector at a specificed position.
 */
void vector_insert_array(vector_t* pvec_vector, vector_iterator_t it_pos, const void* cpv_array, size_t t_count)
{
    size_t     i = 0;
    bool_t     b_result = false;
    iterator_t it_iter;
    _byte_t*   pby_oldfinish = NULL;
    _byte_t*   pby_pos = NULL;
    _byte_t*   pby_destpos = NULL;

    /* test the vector and iterator is valid */
    assert(pvec_vector != NULL);
    assert(_vector_is_inited(pvec_vector));
    assert(_vector_iterator_belong_to_vector(pvec_vector, it_pos));
    assert(cpv_array != NULL);

    if (t_count > 0) {
        /* if the remain capacity is less then the element count */
        if (vector_size(pvec_vector) + t_count > vector_capacity(pvec_vector)) {
            size_t t_distance = _VECTOR_ITERATOR_COREPOS(it_pos) - pvec_vector->_pby_start;
            /* reserve the new size */
            vector_reserve(pvec_vector, _vector_calculate_new_capacity(vector_size(pvec_vector), t_count));
            _VECTOR_ITERATOR_COREPOS(it_pos) = pvec_vector->_pby_start + t_distance;
        }

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

        /*
         * Copy the elements from src array to dest vector.
         * The array of c builtin and user define or cstl builtin are different,
         * the elements of c builtin array are element itself, but the elements of 
         * c string, user define or cstl are pointer of element.
         */
        if (strncmp(_GET_VECTOR_TYPE_BASENAME(pvec_vector), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
            /*
             * We need built a string_t for c string element.
             */
            string_t* pstr_elem = create_string();
            assert(pstr_elem != NULL);
            string_init(pstr_elem);
            for (it_iter = it_pos, i = 0; i < t_count; it_iter = iterator_next(it_iter), ++i) {
                string_assign_cstr(pstr_elem, *((const char**)cpv_array + i));
                b_result = _GET_VECTOR_TYPE_SIZE(pvec_vector);
                _GET_VECTOR_TYPE_COPY_FUNCTION(pvec_vector)(
                    _iterator_get_pointer_ignore_cstr(it_iter), pstr_elem, &b_result);
                assert(b_result);
            }
            string_destroy(pstr_elem);
        } else if (_GET_VECTOR_TYPE_STYLE(pvec_vector) == _TYPE_C_BUILTIN) {
            for (it_iter = it_pos, i = 0; i < t_count; it_iter = iterator_next(it_iter), ++i) {
                b_result = _GET_VECTOR_TYPE_SIZE(pvec_vector);
                _GET_VECTOR_TYPE_COPY_FUNCTION(pvec_vector)(
                    _iterator_get_pointer_ignore_cstr(it_iter),
                    (unsigned char*)cpv_array + i * _GET_VECTOR_TYPE_SIZE(pvec_vector), &b_result);
                assert(b_result);
            }
        } else {
            for (it_iter = it_pos, i = 0; i < t_count; it_iter = iterator_next(it_iter), ++i) {
                b_result = _GET_VECTOR_TYPE_SIZE(pvec_vector);
                _GET_VECTOR_TYPE_COPY_FUNCTION(pvec_vector)(
                    _iterator_get_pointer_ignore_cstr(it_iter), *((void**)cpv_array + i), &b_result);
                assert(b_result);
            }
        }
        assert((size_t)iterator_distance(it_pos, it_iter) == t_count);
    }
}

/**
 * Delete the element at the end of vector.
 */
void vector_pop_back(vector_t* pvec_vector)
{
    bool_t b_result = false;

    assert(pvec_vector != NULL);
    assert(_vector_is_inited(pvec_vector));
    assert(!vector_empty(pvec_vector));

    /* destroy last element */
    b_result = _GET_VECTOR_TYPE_SIZE(pvec_vector);
    _GET_VECTOR_TYPE_DESTROY_FUNCTION(pvec_vector)(pvec_vector->_pby_finish - _GET_VECTOR_TYPE_SIZE(pvec_vector), &b_result);
    assert(b_result);
    pvec_vector->_pby_finish -= _GET_VECTOR_TYPE_SIZE(pvec_vector);
}

/**
 * Removes an element in vector from specificed position.
 */
vector_iterator_t vector_erase(vector_t* pvec_vector, vector_iterator_t it_pos)
{
    assert(pvec_vector != NULL);
    assert(_vector_is_inited(pvec_vector));
    assert(_vector_iterator_belong_to_vector(pvec_vector, it_pos));
    assert(!iterator_equal(it_pos, vector_end(pvec_vector)));

    return vector_erase_range(pvec_vector, it_pos, iterator_next(it_pos));
}

/**
 * Removes a range of elements in vector from specificed position.
 */
vector_iterator_t vector_erase_range(vector_t* pvec_vector, vector_iterator_t it_begin, vector_iterator_t it_end)
{
    size_t            t_erasesize = 0;
    bool_t            b_result = false;
    vector_iterator_t it_iter;
    vector_iterator_t it_vec_end;

    assert(pvec_vector != NULL);
    assert(_vector_is_inited(pvec_vector));
    assert(_vector_iterator_belong_to_vector(pvec_vector, it_begin));
    assert(_vector_iterator_belong_to_vector(pvec_vector, it_end));
    assert(iterator_equal(it_begin, it_end) || _vector_iterator_before(it_begin, it_end));

    if (iterator_equal(it_begin, it_end)) {
        return it_end;
    }

    it_iter = it_begin;
    it_vec_end = vector_end(pvec_vector);
    t_erasesize = iterator_distance(it_begin, it_end);

    for (; !iterator_equal(it_end, it_vec_end); it_begin = iterator_next(it_begin), it_end = iterator_next(it_end)) {
        b_result = _GET_VECTOR_TYPE_SIZE(pvec_vector);
        _GET_VECTOR_TYPE_COPY_FUNCTION(pvec_vector)(_VECTOR_ITERATOR_COREPOS(it_begin), _VECTOR_ITERATOR_COREPOS(it_end), &b_result);
        assert(b_result);
    }
    assert(_VECTOR_ITERATOR_COREPOS(it_begin) == pvec_vector->_pby_finish - t_erasesize * _GET_VECTOR_TYPE_SIZE(pvec_vector));

    /* destroy the deleted elements */
    for (; !iterator_equal(it_begin, it_end); it_begin = iterator_next(it_begin)) {
        b_result = _GET_VECTOR_TYPE_SIZE(pvec_vector);
        _GET_VECTOR_TYPE_DESTROY_FUNCTION(pvec_vector)(_VECTOR_ITERATOR_COREPOS(it_begin), &b_result);
        assert(b_result);
    }
    pvec_vector->_pby_finish -= t_erasesize * _GET_VECTOR_TYPE_SIZE(pvec_vector);

    return it_iter;
}

/*
 * Specifies a new size of a vector.
 */
void vector_resize(vector_t* pvec_vector, size_t t_resize)
{
    vector_iterator_t it_cutpos;     /* the cut position */
    size_t            t_expsize = 0;
    _byte_t*          pby_oldfinish = NULL;

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

        /* initialize new elements */
        pby_oldfinish = pvec_vector->_pby_finish;
        pvec_vector->_pby_finish += t_expsize * _GET_VECTOR_TYPE_SIZE(pvec_vector);
        _vector_init_elem_range_auxiliary(pvec_vector, pby_oldfinish, pvec_vector->_pby_finish);
    }
}

/**
 * Erases the elements of vector.
 */
void vector_clear(vector_t* pvec_vector)
{
    assert(pvec_vector != NULL);
    assert(_vector_is_inited(pvec_vector));

    vector_erase_range(pvec_vector, vector_begin(pvec_vector), vector_end(pvec_vector));
}

/** local function implementation section **/

/** eof **/

