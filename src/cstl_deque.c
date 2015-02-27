/*
 *  The implement of deque module.
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
#include <cstl/cdeque.h>

#include "cstl_deque_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Initialize an empty deque container
 */
void deque_init(deque_t* pdeq_deque)
{
    assert(pdeq_deque != NULL);
    assert(_deque_is_created(pdeq_deque));

    deque_init_n(pdeq_deque, 0);
}

/**
 * Initialize deque container with specific size.
 */
void deque_init_n(deque_t* pdeq_deque, size_t t_count)
{
    size_t     i = 0;
    size_t     t_startpos = 0;      /* the real map start pos */
    size_t     t_mapcount = 0;      /* the map count */
    size_t     t_validmapcount = 0; /* the valid count in map */
    size_t     t_endelemcount = 0;  /* the element count in the last container */
    iterator_t it_iter;
    iterator_t it_begin;
    iterator_t it_end;
    
    assert(pdeq_deque != NULL);
    assert(_deque_is_created(pdeq_deque));

    /* initialize the map and element container */
    /* if element count > 0 */
    if (t_count > 0) {
        /* get the element container count */
        t_validmapcount = (t_count + _DEQUE_ELEM_COUNT - 1) / _DEQUE_ELEM_COUNT;
        t_endelemcount = t_count % _DEQUE_ELEM_COUNT;
        /* the last container has element */
        if (t_endelemcount != 0) {
            t_validmapcount += 1;
        } else {
            /* the last container has no element */
            t_validmapcount += 2;
        }

        if (t_validmapcount > _DEQUE_MAP_COUNT) {
            size_t t_growcount = (t_validmapcount - _DEQUE_MAP_COUNT + _DEQUE_MAP_GROW_STEP - 1) / _DEQUE_MAP_GROW_STEP * _DEQUE_MAP_GROW_STEP;
            t_mapcount = _DEQUE_MAP_COUNT + t_growcount;
        } else {
            t_mapcount = _DEQUE_MAP_COUNT;
        }
    } else {
        t_validmapcount = 2;
        t_endelemcount = 0;
        t_mapcount = _DEQUE_MAP_COUNT;
    }
    /* allocate memory for each container */
    pdeq_deque->_ppby_map = _alloc_allocate(&pdeq_deque->_t_allocator, sizeof(_byte_t*), t_mapcount);
    pdeq_deque->_t_mapsize = t_mapcount;
    assert(pdeq_deque->_ppby_map != NULL);
    memset(pdeq_deque->_ppby_map, 0x00, sizeof(_byte_t*) * t_mapcount);
    t_startpos = (t_mapcount - t_validmapcount) / 2;

    for (i = t_startpos; i < t_startpos + t_validmapcount; ++i) {
        pdeq_deque->_ppby_map[i] = _alloc_allocate(&pdeq_deque->_t_allocator, _GET_DEQUE_TYPE_SIZE(pdeq_deque), _DEQUE_ELEM_COUNT);
        assert(pdeq_deque->_ppby_map[i] != NULL);
    }

    /* initialize the start iterator */
    _ITERATOR_CONTAINER(pdeq_deque->_t_start) = pdeq_deque;
    _DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_start) = pdeq_deque->_ppby_map + t_startpos;
    _DEQUE_ITERATOR_FIRST_POS(pdeq_deque->_t_start) = *_DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_start);
    _DEQUE_ITERATOR_AFTERLAST_POS(pdeq_deque->_t_start) = 
        _DEQUE_ITERATOR_FIRST_POS(pdeq_deque->_t_start) + _DEQUE_ELEM_COUNT * _GET_DEQUE_TYPE_SIZE(pdeq_deque);
    _DEQUE_ITERATOR_COREPOS(pdeq_deque->_t_start) = _DEQUE_ITERATOR_AFTERLAST_POS(pdeq_deque->_t_start);
    /* initialize the finish iterator */
    _ITERATOR_CONTAINER(pdeq_deque->_t_finish) = pdeq_deque;
    _DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_finish) = pdeq_deque->_ppby_map + t_startpos + t_validmapcount - 1;
    _DEQUE_ITERATOR_FIRST_POS(pdeq_deque->_t_finish) = *_DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_finish);
    _DEQUE_ITERATOR_AFTERLAST_POS(pdeq_deque->_t_finish) = 
        _DEQUE_ITERATOR_FIRST_POS(pdeq_deque->_t_finish) + _DEQUE_ELEM_COUNT * _GET_DEQUE_TYPE_SIZE(pdeq_deque);
    _DEQUE_ITERATOR_COREPOS(pdeq_deque->_t_finish) = 
        _DEQUE_ITERATOR_FIRST_POS(pdeq_deque->_t_finish) + t_endelemcount * _GET_DEQUE_TYPE_SIZE(pdeq_deque);

    it_begin = deque_begin(pdeq_deque);
    it_end = deque_end(pdeq_deque);
    for (it_iter = it_begin; !iterator_equal(it_iter, it_end); it_iter = iterator_next(it_iter)) {
        _deque_init_elem_auxiliary(pdeq_deque, _deque_iterator_get_pointer_auxiliary(it_iter));
    }
}

/**
 * Initialize deque container with exist deque container.
 */
void deque_init_copy(deque_t* pdeq_dest, const deque_t* cpdeq_src)
{
    assert(pdeq_dest != NULL);
    assert(cpdeq_src != NULL);
    assert(_deque_is_created(pdeq_dest));
    assert(_deque_is_inited(cpdeq_src));
    assert(_deque_same_type(pdeq_dest, cpdeq_src));

    deque_init_copy_range(pdeq_dest, deque_begin(cpdeq_src), deque_end(cpdeq_src));
}

/**
 * Initialize deque container with specific range.
 */
void deque_init_copy_range(deque_t* pdeq_dest, iterator_t it_begin, iterator_t it_end)
{
    iterator_t it_dest_begin;
    iterator_t it_dest_end;
    iterator_t it_dest;   /* the iterator of dest deque for iterate */
    iterator_t it_src;    /* the iterator of src range for iterate */
    bool_t     b_result = false;

    assert(pdeq_dest != NULL);
    assert(_deque_is_created(pdeq_dest));
    assert(_deque_same_iterator_type(pdeq_dest, it_begin));
    assert(_deque_same_iterator_type(pdeq_dest, it_end));
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));

    /* init the dest deque with the distance between it_begin and it_end */
    deque_init_n(pdeq_dest, iterator_distance(it_begin, it_end));
    it_dest_begin = deque_begin(pdeq_dest);
    it_dest_end = deque_end(pdeq_dest);

    /* copy the elements from src range to dest deque */
    for (it_dest = it_dest_begin, it_src = it_begin;
         !iterator_equal(it_dest, it_dest_end) && !iterator_equal(it_src, it_end);
         it_dest = iterator_next(it_dest), it_src = iterator_next(it_src)) {
        b_result = _GET_DEQUE_TYPE_SIZE(pdeq_dest);
        _GET_DEQUE_TYPE_COPY_FUNCTION(pdeq_dest)(
            _iterator_get_pointer_ignore_cstr(it_dest),
            _iterator_get_pointer_ignore_cstr(it_src), &b_result);
        assert(b_result);
    }
    assert(iterator_equal(it_dest, it_dest_end) && iterator_equal(it_src, it_end));
}

/**
 * Initialize deque container with specific array.
 */
void deque_init_copy_array(deque_t* pdeq_dest, const void* cpv_array, size_t t_count)
{
    iterator_t it_dest;   /* the iterator of dest deque for iterate */
    iterator_t it_begin;
    iterator_t it_end;
    bool_t     b_result = false;
    size_t     i = 0;

    assert(pdeq_dest != NULL);
    assert(_deque_is_created(pdeq_dest));
    assert(cpv_array != NULL);

    /* init the dest deque with the count of array */
    deque_init_n(pdeq_dest, t_count);
    it_begin = deque_begin(pdeq_dest);
    it_end = deque_end(pdeq_dest);

    /*
     * Copy the elements from src array to dest deque.
     * The array of c builtin and user define or cstl builtin are different,
     * the elements of c builtin array are element itself, but the elements of 
     * c string, user define or cstl are pointer of element.
     */
    if (strncmp(_GET_DEQUE_TYPE_BASENAME(pdeq_dest), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
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
            b_result = _GET_DEQUE_TYPE_SIZE(pdeq_dest);
            _GET_DEQUE_TYPE_COPY_FUNCTION(pdeq_dest)(
                _iterator_get_pointer_ignore_cstr(it_dest), pstr_elem, &b_result);
            assert(b_result);
        }
        string_destroy(pstr_elem);
    } else if (_GET_DEQUE_TYPE_STYLE(pdeq_dest) == _TYPE_C_BUILTIN) {
        for (it_dest = it_begin, i = 0;
             !iterator_equal(it_dest, it_end) && i < t_count;
             it_dest = iterator_next(it_dest), ++i) {
            b_result = _GET_DEQUE_TYPE_SIZE(pdeq_dest);
            _GET_DEQUE_TYPE_COPY_FUNCTION(pdeq_dest)(
                _iterator_get_pointer_ignore_cstr(it_dest),
                (unsigned char*)cpv_array + i * _GET_DEQUE_TYPE_SIZE(pdeq_dest), &b_result);
            assert(b_result);
        }
    } else {
        for (it_dest = it_begin, i = 0;
             !iterator_equal(it_dest, it_end) && i < t_count;
             it_dest = iterator_next(it_dest), ++i) {
            b_result = _GET_DEQUE_TYPE_SIZE(pdeq_dest);
            _GET_DEQUE_TYPE_COPY_FUNCTION(pdeq_dest)(
                _iterator_get_pointer_ignore_cstr(it_dest), *((void**)cpv_array + i), &b_result);
            assert(b_result);
        }
    }
    assert(iterator_equal(it_dest, it_end) && i == t_count);
}

/**
 * Destroy deque container.
 */
void deque_destroy(deque_t* pdeq_deque)
{
    assert(pdeq_deque != NULL);
    assert(_deque_is_inited(pdeq_deque) || _deque_is_created(pdeq_deque));

    _deque_destroy_auxiliary(pdeq_deque);
    free(pdeq_deque);
}

/**
 * Tests if a deque is empty.
 */
bool_t deque_empty(const deque_t* cpdeq_deque)
{
    assert(cpdeq_deque != NULL);
    assert(_deque_is_inited(cpdeq_deque));

    return iterator_equal(cpdeq_deque->_t_start, cpdeq_deque->_t_finish);
}

/**
 * Return the number of elements in a deque.
 */
size_t deque_size(const deque_t* cpdeq_deque)
{
    assert(cpdeq_deque != NULL);
    assert(_deque_is_inited(cpdeq_deque));

    return iterator_distance(cpdeq_deque->_t_start, cpdeq_deque->_t_finish);
}

/**
 * Return the maximum number of elements in a deque.
 */
size_t deque_max_size(const deque_t* cpdeq_deque)
{
    assert(cpdeq_deque != NULL);
    assert(_deque_is_inited(cpdeq_deque));

    return (size_t)(-1) / _GET_DEQUE_TYPE_SIZE(cpdeq_deque);
}

/**
 * Access first deque data.
 */
void* deque_front(const deque_t* cpdeq_deque)
{
    assert(cpdeq_deque != NULL);
    assert(_deque_is_inited(cpdeq_deque));
    assert(!deque_empty(cpdeq_deque));

    return deque_at(cpdeq_deque, 0);
}

/**
 * Access first last data.
 */
void* deque_back(const deque_t* cpdeq_deque)
{
    assert(cpdeq_deque != NULL);
    assert(_deque_is_inited(cpdeq_deque));
    assert(!deque_empty(cpdeq_deque));

    return deque_at(cpdeq_deque, deque_size(cpdeq_deque) - 1);
}

/**
 * Return a iterator to the first element in the deque container.
 */
deque_iterator_t deque_begin(const deque_t* cpdeq_deque)
{
    assert(cpdeq_deque != NULL);
    assert(_deque_is_inited(cpdeq_deque));

    return cpdeq_deque->_t_start;
}

/**
 * Return a iterator that points just beyond the end of deque container.
 */
deque_iterator_t deque_end(const deque_t* cpdeq_deque)
{
    assert(cpdeq_deque != NULL);
    assert(_deque_is_inited(cpdeq_deque));

    return cpdeq_deque->_t_finish;
}

deque_reverse_iterator_t deque_rbegin(const deque_t* cpdeq_deque)
{
    assert(cpdeq_deque != NULL);
    assert(_deque_is_inited(cpdeq_deque));

    return iterator_prev(cpdeq_deque->_t_finish);
}

deque_reverse_iterator_t deque_rend(const deque_t* cpdeq_deque)
{
    deque_iterator_t it_iter;

    assert(cpdeq_deque != NULL);
    assert(_deque_is_inited(cpdeq_deque));

    it_iter = cpdeq_deque->_t_start;
    _DEQUE_ITERATOR_COREPOS(it_iter) = _DEQUE_ITERATOR_COREPOS(cpdeq_deque->_t_start) - _GET_DEQUE_TYPE_SIZE(cpdeq_deque);

    return it_iter;
}

/**
 * Assign deque element with an exist deque container.
 */
void deque_assign(deque_t* pdeq_dest, const deque_t* cpdeq_src)
{
    assert(pdeq_dest != NULL);
    assert(cpdeq_src != NULL);
    assert(_deque_is_inited(pdeq_dest));
    assert(_deque_is_inited(cpdeq_src));
    assert(_deque_same_type(pdeq_dest, cpdeq_src));

    if (deque_equal(pdeq_dest, cpdeq_src)) {
        return;
    }

    deque_assign_range(pdeq_dest, deque_begin(cpdeq_src), deque_end(cpdeq_src));
}

/**
 * Assign deque element with an exist deque container range.
 */
void deque_assign_range(deque_t* pdeq_deque, iterator_t it_begin, iterator_t it_end)
{
    iterator_t it_dest_begin;
    iterator_t it_dest_end;
    iterator_t it_dest;   /* the iterator of dest deque for iterate */
    iterator_t it_src;    /* the iterator of src range for iterate */
    bool_t     b_result = false;

    assert(pdeq_deque != NULL);
    assert(_deque_is_inited(pdeq_deque));
    assert(_deque_same_iterator_type(pdeq_deque, it_begin));
    assert(_deque_same_iterator_type(pdeq_deque, it_end));
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));

    it_dest_begin = deque_begin(pdeq_deque);
    it_dest_end = deque_end(pdeq_deque);

    /* copy the elements from src range to dest deque */
    for (it_dest = it_dest_begin, it_src = it_begin;
         !iterator_equal(it_dest, it_dest_end) && !iterator_equal(it_src, it_end);
         it_dest = iterator_next(it_dest), it_src = iterator_next(it_src)) {
        b_result = _GET_DEQUE_TYPE_SIZE(pdeq_deque);
        _GET_DEQUE_TYPE_COPY_FUNCTION(pdeq_deque)(
            _iterator_get_pointer_ignore_cstr(it_dest),
            _iterator_get_pointer_ignore_cstr(it_src), &b_result);
        assert(b_result);
    }

    if (deque_size(pdeq_deque) < iterator_distance(it_begin, it_end)) {
        assert(iterator_equal(it_dest, it_dest_end) && _iterator_before(it_src, it_end));
        deque_insert_range(pdeq_deque, it_dest, it_src, it_end);
    } else {
        assert((_iterator_before(it_dest, it_dest_end) || iterator_equal(it_dest, it_dest_end)) &&
               iterator_equal(it_src, it_end));
        deque_erase_range(pdeq_deque, it_dest, it_dest_end);
    }
}

/**
 * Assign deque element with an exist deque container array.
 */
void deque_assign_array(deque_t* pdeq_deque, const void* cpv_array, size_t t_count)
{
    iterator_t it_dest;   /* the iterator of dest deque for iterate */
    iterator_t it_begin;
    iterator_t it_end;
    bool_t     b_result = false;
    size_t     i = 0;

    assert(pdeq_deque != NULL);
    assert(_deque_is_inited(pdeq_deque));
    assert(cpv_array != NULL);

    /* init the dest deque with the t_count, compare and element destroy function. */
    deque_resize(pdeq_deque, t_count);
    it_begin = deque_begin(pdeq_deque);
    it_end = deque_end(pdeq_deque);

    /*
     * Copy the elements from src array to dest deque.
     * The array of c builtin and user define or cstl builtin are different,
     * the elements of c builtin array are element itself, but the elements of 
     * c string, user define or cstl are pointer of element.
     */
    if (strncmp(_GET_DEQUE_TYPE_BASENAME(pdeq_deque), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
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
            b_result = _GET_DEQUE_TYPE_SIZE(pdeq_deque);
            _GET_DEQUE_TYPE_COPY_FUNCTION(pdeq_deque)(
                _iterator_get_pointer_ignore_cstr(it_dest), pstr_elem, &b_result);
            assert(b_result);
        }
        string_destroy(pstr_elem);
    } else if (_GET_DEQUE_TYPE_STYLE(pdeq_deque) == _TYPE_C_BUILTIN) {
        for (it_dest = it_begin, i = 0;
             !iterator_equal(it_dest, it_end) && i < t_count;
             it_dest = iterator_next(it_dest), ++i) {
            b_result = _GET_DEQUE_TYPE_SIZE(pdeq_deque);
            _GET_DEQUE_TYPE_COPY_FUNCTION(pdeq_deque)(
                _iterator_get_pointer_ignore_cstr(it_dest),
                (unsigned char*)cpv_array + i * _GET_DEQUE_TYPE_SIZE(pdeq_deque), &b_result);
            assert(b_result);
        }
    } else {
        for (it_dest = it_begin, i = 0;
             !iterator_equal(it_dest, it_end) && i < t_count;
             it_dest = iterator_next(it_dest), ++i) {
            b_result = _GET_DEQUE_TYPE_SIZE(pdeq_deque);
            _GET_DEQUE_TYPE_COPY_FUNCTION(pdeq_deque)(
                _iterator_get_pointer_ignore_cstr(it_dest), *((void**)cpv_array + i), &b_result);
            assert(b_result);
        }
    }
    assert(iterator_equal(it_dest, it_end) && i == t_count);
}

/**
 * Tests if the two deques are equal.
 */
bool_t deque_equal(const deque_t* cpdeq_first, const deque_t* cpdeq_second)
{
    deque_iterator_t it_first;  /* the iterator to first deque for iterate */
    deque_iterator_t it_first_begin;
    deque_iterator_t it_first_end;
    deque_iterator_t it_second; /* the iterator to second deque for iterate */
    deque_iterator_t it_second_begin;
    deque_iterator_t it_second_end;
    bool_t           b_less = false;
    bool_t           b_greater = false;

    assert(cpdeq_first != NULL);
    assert(cpdeq_second != NULL);
    assert(_deque_is_inited(cpdeq_first));
    assert(_deque_is_inited(cpdeq_second));
    assert(_deque_same_type(cpdeq_first, cpdeq_second));

    if (cpdeq_first == cpdeq_second) {
        return true;
    }

    if (deque_size(cpdeq_first) != deque_size(cpdeq_second)) {
        return false;
    }

    it_first_begin = deque_begin(cpdeq_first);
    it_first_end = deque_end(cpdeq_first);
    it_second_begin = deque_begin(cpdeq_second);
    it_second_end = deque_end(cpdeq_second);

    for (it_first = it_first_begin, it_second = it_second_begin;
         !iterator_equal(it_first, it_first_end) && !iterator_equal(it_second, it_second_end);
         it_first = iterator_next(it_first), it_second = iterator_next(it_second)) {
        b_less = b_greater = _GET_DEQUE_TYPE_SIZE(cpdeq_first);
        _GET_DEQUE_TYPE_LESS_FUNCTION(cpdeq_first)(
            _deque_iterator_get_pointer_auxiliary(it_first),
            _deque_iterator_get_pointer_auxiliary(it_second), &b_less);
        _GET_DEQUE_TYPE_LESS_FUNCTION(cpdeq_first)(
            _deque_iterator_get_pointer_auxiliary(it_second),
            _deque_iterator_get_pointer_auxiliary(it_first), &b_greater);
        if (b_less || b_greater) {
            return false;
        }
    }
    assert(iterator_equal(it_first, it_first_end) && iterator_equal(it_second, it_second_end));

    return true;
}

/**
 * Test the two deques are unequal.
 */
bool_t deque_not_equal(const deque_t* cpdeq_first, const deque_t* cpdeq_second)
{
    assert(cpdeq_first != NULL);
    assert(cpdeq_second != NULL);
    assert(_deque_is_inited(cpdeq_first));
    assert(_deque_is_inited(cpdeq_second));

    return !deque_equal(cpdeq_first, cpdeq_second);
}

/**
 * Test the first deque is less than the second deque.
 */
bool_t deque_less(const deque_t* cpdeq_first, const deque_t* cpdeq_second)
{
    deque_iterator_t it_first;
    deque_iterator_t it_first_begin;
    deque_iterator_t it_first_end;
    deque_iterator_t it_second;
    deque_iterator_t it_second_begin;
    deque_iterator_t it_second_end;
    bool_t           b_result = false;

    assert(cpdeq_first != NULL);
    assert(cpdeq_second != NULL);
    assert(_deque_is_inited(cpdeq_first));
    assert(_deque_is_inited(cpdeq_second));
    assert(_deque_same_type(cpdeq_first, cpdeq_second));

    if (cpdeq_first == cpdeq_second) {
        return false;
    }

    it_first_begin = deque_begin(cpdeq_first);
    it_first_end = deque_end(cpdeq_first);
    it_second_begin = deque_begin(cpdeq_second);
    it_second_end = deque_end(cpdeq_second);

    for (it_first = it_first_begin, it_second = it_second_begin;
         !iterator_equal(it_first, it_first_end) && !iterator_equal(it_second, it_second_end);
         it_first = iterator_next(it_first), it_second = iterator_next(it_second)) {
        b_result = _GET_DEQUE_TYPE_SIZE(cpdeq_first);
        _GET_DEQUE_TYPE_LESS_FUNCTION(cpdeq_first)(
            _deque_iterator_get_pointer_auxiliary(it_first),
            _deque_iterator_get_pointer_auxiliary(it_second), &b_result);
        if (b_result) {
            return true;
        }

        b_result = _GET_DEQUE_TYPE_SIZE(cpdeq_first);
        _GET_DEQUE_TYPE_LESS_FUNCTION(cpdeq_first)(
            _deque_iterator_get_pointer_auxiliary(it_second),
            _deque_iterator_get_pointer_auxiliary(it_first), &b_result);
        if (b_result) {
            return false;
        }
    }

    return deque_size(cpdeq_first) < deque_size(cpdeq_second) ? true : false;
}

/**
 * Test the first deque is less than or equal to the second deque.
 */
bool_t deque_less_equal(const deque_t* cpdeq_first, const deque_t* cpdeq_second)
{
    return (deque_less(cpdeq_first, cpdeq_second) || deque_equal(cpdeq_first, cpdeq_second)) ? true : false;
}

/**
 * Test the first deque is greater than the second deque.
 */
bool_t deque_greater(const deque_t* cpdeq_first, const deque_t* cpdeq_second)
{
    return deque_less(cpdeq_second, cpdeq_first);
}

/**
 * Test the first deque is greater than or equal to the second deque.
 */
bool_t deque_greater_equal(const deque_t* cpdeq_first, const deque_t* cpdeq_second)
{
    return (deque_greater(cpdeq_first, cpdeq_second) || deque_equal(cpdeq_first, cpdeq_second)) ? true : false;
}

/**
 * Access deque data using subscript.
 */
void* deque_at(const deque_t* cpdeq_deque, size_t t_pos)
{
    deque_iterator_t it_iter;

    assert(cpdeq_deque != NULL);
    assert(_deque_is_inited(cpdeq_deque));
    assert(t_pos < deque_size(cpdeq_deque));

    it_iter = iterator_next_n(deque_begin(cpdeq_deque), t_pos);
    assert(_deque_iterator_belong_to_deque(cpdeq_deque, it_iter));

    return (void*)iterator_get_pointer(it_iter);
}

/**
 * Swap deque datas.
 */
void deque_swap(deque_t* pdeq_first, deque_t* pdeq_second)
{
    deque_t deq_tmp;

    assert(pdeq_first != NULL);
    assert(pdeq_second != NULL);
    assert(_deque_is_inited(pdeq_first));
    assert(_deque_is_inited(pdeq_second));
    assert(_deque_same_type(pdeq_first, pdeq_second));

    if (deque_equal(pdeq_first, pdeq_second)) {
        return;
    }

    deq_tmp = *pdeq_first;
    *pdeq_first = *pdeq_second;
    *pdeq_second = deq_tmp;

    /* the pointer to container must not be swap */
    _ITERATOR_CONTAINER(pdeq_first->_t_start) = pdeq_first;
    _ITERATOR_CONTAINER(pdeq_first->_t_finish) = pdeq_first;

    _ITERATOR_CONTAINER(pdeq_second->_t_start) = pdeq_second;
    _ITERATOR_CONTAINER(pdeq_second->_t_finish) = pdeq_second;
}

/**
 * Delete the element at the end of deque.
 */
void deque_pop_back(deque_t* pdeq_deque)
{
    assert(pdeq_deque != NULL);
    assert(_deque_is_inited(pdeq_deque));
    assert(!deque_empty(pdeq_deque));

    _deque_shrink_at_end(pdeq_deque, 1);
}

/**
 * Delete the element at the begin of deque.
 */
void deque_pop_front(deque_t* pdeq_deque)
{
    assert(pdeq_deque != NULL);
    assert(_deque_is_inited(pdeq_deque));
    assert(!deque_empty(pdeq_deque));

    _deque_shrink_at_begin(pdeq_deque, 1);
}


/**
 * Insert a range of elements into deque at a specificed position.
 */
void deque_insert_range(deque_t* pdeq_deque, deque_iterator_t it_pos, iterator_t it_begin, iterator_t it_end)
{
    int    n_elemcount = 0;
    bool_t b_result = false;

    assert(pdeq_deque != NULL);
    assert(_deque_is_inited(pdeq_deque));
    assert(_deque_iterator_belong_to_deque(pdeq_deque, it_pos));
    assert(_deque_same_iterator_type(pdeq_deque, it_begin));
    assert(_deque_same_iterator_type(pdeq_deque, it_end));
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));

    n_elemcount = iterator_distance(it_begin, it_end);
    /* if the element number after insert pos is little then insert in front */
    if (iterator_distance(deque_begin(pdeq_deque), it_pos) < (int)deque_size(pdeq_deque)/2) {
        deque_iterator_t it_oldbegin;
        deque_iterator_t it_gap;

        /* expand one element at front */
        it_oldbegin = _deque_expand_at_begin(pdeq_deque, n_elemcount, &it_pos);
        /* move the element range [oldfront, pos) to [newfront, pos) */
        it_gap = _deque_move_elem_to_begin(pdeq_deque, it_oldbegin, it_pos, n_elemcount);
        assert(iterator_distance(it_gap, it_pos) == n_elemcount);

        for (;
             !iterator_equal(it_gap, it_pos) && !iterator_equal(it_begin, it_end); 
             it_gap = iterator_next(it_gap), it_begin = iterator_next(it_begin)) {
            b_result = _GET_DEQUE_TYPE_SIZE(pdeq_deque);
            _GET_DEQUE_TYPE_COPY_FUNCTION(pdeq_deque)(
                _iterator_get_pointer_ignore_cstr(it_gap),
                _iterator_get_pointer_ignore_cstr(it_begin), &b_result);
            assert(b_result);
        }
        assert(iterator_equal(it_gap, it_pos) && iterator_equal(it_begin, it_end));
    } else {
        /* insert in back */
        deque_iterator_t it_oldend = _deque_expand_at_end(pdeq_deque, n_elemcount, &it_pos);
        _deque_move_elem_to_end(pdeq_deque, it_pos, it_oldend, n_elemcount);

        for (;
             !iterator_equal(it_begin, it_end);
             it_pos = iterator_next(it_pos), it_begin = iterator_next(it_begin)) {
            b_result = _GET_DEQUE_TYPE_SIZE(pdeq_deque);
            _GET_DEQUE_TYPE_COPY_FUNCTION(pdeq_deque)(
                _iterator_get_pointer_ignore_cstr(it_pos),
                _iterator_get_pointer_ignore_cstr(it_begin), &b_result);
            assert(b_result);
        }
    }
}

/**
 * Insert a array of elements into deque at a specificed position.
 */
void deque_insert_array(deque_t* pdeq_deque, deque_iterator_t it_pos, const void* cpv_array, size_t t_count)
{
    bool_t b_result = false;
    size_t i = 0;

    assert(pdeq_deque != NULL);
    assert(_deque_is_inited(pdeq_deque));
    assert(_deque_iterator_belong_to_deque(pdeq_deque, it_pos));
    assert(cpv_array != NULL);

    /* if the element number after insert pos is little then insert in front */
    if (iterator_distance(deque_begin(pdeq_deque), it_pos) < (int)deque_size(pdeq_deque)/2) {
        deque_iterator_t it_oldbegin;
        deque_iterator_t it_gap;

        /* expand one element at front */
        it_oldbegin = _deque_expand_at_begin(pdeq_deque, t_count, &it_pos);
        /* move the element range [oldfront, pos) to [newfront, pos) */
        it_gap = _deque_move_elem_to_begin(pdeq_deque, it_oldbegin, it_pos, t_count);
        assert(iterator_distance(it_gap, it_pos) == (int)t_count);

        /*
         * Copy the elements from src array to dest deque.
         * The array of c builtin and user define or cstl builtin are different,
         * the elements of c builtin array are element itself, but the elements of 
         * c string, user define or cstl are pointer of element.
         */
        if (strncmp(_GET_DEQUE_TYPE_BASENAME(pdeq_deque), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
            /*
             * We need built a string_t for c string element.
             */
            string_t* pstr_elem = create_string();
            assert(pstr_elem != NULL);
            string_init(pstr_elem);
            for (i = 0; !iterator_equal(it_gap, it_pos) && i < t_count; it_gap = iterator_next(it_gap), ++i) {
                string_assign_cstr(pstr_elem, *((const char**)cpv_array + i));
                b_result = _GET_DEQUE_TYPE_SIZE(pdeq_deque);
                _GET_DEQUE_TYPE_COPY_FUNCTION(pdeq_deque)(
                    _iterator_get_pointer_ignore_cstr(it_gap), pstr_elem, &b_result);
                assert(b_result);
            }
            string_destroy(pstr_elem);
        } else if (_GET_DEQUE_TYPE_STYLE(pdeq_deque) == _TYPE_C_BUILTIN) {
            for (i = 0; !iterator_equal(it_gap, it_pos) && i < t_count; it_gap = iterator_next(it_gap), ++i) {
                b_result = _GET_DEQUE_TYPE_SIZE(pdeq_deque);
                _GET_DEQUE_TYPE_COPY_FUNCTION(pdeq_deque)(
                    _iterator_get_pointer_ignore_cstr(it_gap),
                    (unsigned char*)cpv_array + i * _GET_DEQUE_TYPE_SIZE(pdeq_deque), &b_result);
                assert(b_result);
            }
        } else {
            for (i = 0; !iterator_equal(it_gap, it_pos) && i < t_count; it_gap = iterator_next(it_gap), ++i) {
                b_result = _GET_DEQUE_TYPE_SIZE(pdeq_deque);
                _GET_DEQUE_TYPE_COPY_FUNCTION(pdeq_deque)(
                    _iterator_get_pointer_ignore_cstr(it_gap), *((void**)cpv_array + i), &b_result);
                assert(b_result);
            }
        }
        assert(iterator_equal(it_gap, it_pos) && i == t_count);
    } else {
        /* insert in back */
        deque_iterator_t it_oldend = _deque_expand_at_end(pdeq_deque, t_count, &it_pos);
        _deque_move_elem_to_end(pdeq_deque, it_pos, it_oldend, t_count);

        /*
         * Copy the elements from src array to dest deque.
         * The array of c builtin and user define or cstl builtin are different,
         * the elements of c builtin array are element itself, but the elements of 
         * c string, user define or cstl are pointer of element.
         */
        if (strncmp(_GET_DEQUE_TYPE_BASENAME(pdeq_deque), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
            /*
             * We need built a string_t for c string element.
             */
            string_t* pstr_elem = create_string();
            assert(pstr_elem != NULL);
            string_init(pstr_elem);
            for (i = 0; i < t_count; it_pos = iterator_next(it_pos), ++i) {
                string_assign_cstr(pstr_elem, *((const char**)cpv_array + i));
                b_result = _GET_DEQUE_TYPE_SIZE(pdeq_deque);
                _GET_DEQUE_TYPE_COPY_FUNCTION(pdeq_deque)(
                    _iterator_get_pointer_ignore_cstr(it_pos), pstr_elem, &b_result);
                assert(b_result);
            }
            string_destroy(pstr_elem);
        } else if (_GET_DEQUE_TYPE_STYLE(pdeq_deque) == _TYPE_C_BUILTIN) {
            for (i = 0; i < t_count; it_pos = iterator_next(it_pos), ++i) {
                b_result = _GET_DEQUE_TYPE_SIZE(pdeq_deque);
                _GET_DEQUE_TYPE_COPY_FUNCTION(pdeq_deque)(
                    _iterator_get_pointer_ignore_cstr(it_pos),
                    (unsigned char*)cpv_array + i * _GET_DEQUE_TYPE_SIZE(pdeq_deque), &b_result);
                assert(b_result);
            }
        } else {
            for (i = 0; i < t_count; it_pos = iterator_next(it_pos), ++i) {
                b_result = _GET_DEQUE_TYPE_SIZE(pdeq_deque);
                _GET_DEQUE_TYPE_COPY_FUNCTION(pdeq_deque)(
                    _iterator_get_pointer_ignore_cstr(it_pos), *((void**)cpv_array + i), &b_result);
                assert(b_result);
            }
        }
    }
}

/**
 * Removes an element in deque from specificed position.
 */
deque_iterator_t deque_erase(deque_t* pdeq_deque, deque_iterator_t it_pos)
{
    assert(pdeq_deque != NULL);
    assert(_deque_is_inited(pdeq_deque));
    assert(_deque_iterator_belong_to_deque(pdeq_deque, it_pos));
    assert(!iterator_equal(it_pos, deque_end(pdeq_deque)));

    if (iterator_equal(it_pos, deque_begin(pdeq_deque))) {
        deque_pop_front(pdeq_deque);
        return deque_begin(pdeq_deque);
    } else if (iterator_equal(it_pos, iterator_prev(deque_end(pdeq_deque)))) {
        deque_pop_back(pdeq_deque);
        return deque_end(pdeq_deque);
    } else {
        deque_iterator_t it_iter = it_pos;

        it_pos = iterator_next(it_pos);
        _deque_move_elem_to_begin(pdeq_deque, it_pos, deque_end(pdeq_deque), 1);
        _deque_shrink_at_end(pdeq_deque, 1);

        return it_iter;
    }
}

/**
 * Removes a range of elements in deque from specificed position.
 */
deque_iterator_t deque_erase_range(deque_t* pdeq_deque, deque_iterator_t it_begin, deque_iterator_t it_end)
{
    assert(pdeq_deque != NULL);
    assert(_deque_is_inited(pdeq_deque));
    assert(_deque_iterator_belong_to_deque(pdeq_deque, it_begin));
    assert(_deque_iterator_belong_to_deque(pdeq_deque, it_end));
    assert(iterator_equal(it_begin, it_end) || _deque_iterator_before(it_begin, it_end));

    _deque_move_elem_to_begin(pdeq_deque, it_end, deque_end(pdeq_deque), iterator_distance(it_begin, it_end));
    _deque_shrink_at_end(pdeq_deque, iterator_distance(it_begin, it_end));

    return it_begin;
}

/**
 * Specifies a new size of a deque.
 */
void deque_resize(deque_t* pdeq_deque, size_t t_resize)
{
    assert(pdeq_deque != NULL);
    assert(_deque_is_inited(pdeq_deque));

    if (t_resize < deque_size(pdeq_deque)) {
        _deque_shrink_at_end(pdeq_deque, deque_size(pdeq_deque) - t_resize);
    } else if (t_resize > deque_size(pdeq_deque)) {
        _deque_expand_at_end(pdeq_deque, t_resize - deque_size(pdeq_deque), NULL);
    }
}

/**
 * Erases the elements of deque.
 */
void deque_clear(deque_t* pdeq_deque)
{
    assert(pdeq_deque != NULL);
    assert(_deque_is_inited(pdeq_deque));

    deque_erase_range(pdeq_deque, deque_begin(pdeq_deque), deque_end(pdeq_deque));
}

/** local function implementation section **/

/** eof **/

