/*
 *  The implementation of basic_string private functions.
 *  Copyright (C)  2008,2009,2010,2011  Wangbo
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
#include <cstl/cvector.h>

#include <cstl/cstl_basic_string_iterator.h>
#include <cstl/cstl_basic_string_private.h>
#include <cstl/cstl_basic_string.h>

#include "cstl_basic_string_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/

/* basic_string private function */
basic_string_t* _create_basic_string(const char* s_typename)
{
    assert(sizeof(basic_string_t) == sizeof(vector_t));
    return (basic_string_t*)_create_vector(s_typename);
}

bool_t _create_basic_string_auxiliary(basic_string_t* pt_basic_string, const char* s_typename)
{
    return _create_vector_auxiliary(&pt_basic_string->_t_vector, s_typename);
}

void _basic_string_destroy_auxiliary(basic_string_t* pt_basic_string)
{
    _vector_destroy_auxiliary(&pt_basic_string->_t_vector);
}

void _basic_string_init_elem(
    basic_string_t* pt_basic_string, size_t t_count, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_count);
    _basic_string_init_elem_varg(pt_basic_string, t_count, val_elemlist);
    va_end(val_elemlist);
}

void _basic_string_init_elem_varg(
    basic_string_t* pt_basic_string, size_t t_count, va_list val_elemlist)
{
    _vector_init_elem_varg(&pt_basic_string->_t_vector, t_count, val_elemlist);
}


void _basic_string_connect_elem(basic_string_t* pt_basic_string, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, pt_basic_string);
    _basic_string_connect_elem_varg(pt_basic_string, val_elemlist);
    va_end(val_elemlist);
}

void _basic_string_connect_elem_varg(basic_string_t* pt_basic_string, va_list val_elemlist)
{
    size_t  t_typesize = 0;
    char*   pc_dest = NULL;
    void*   pv_varg = NULL;
    bool_t  t_result = false;

    assert(pt_basic_string != NULL);

    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string);
    pv_varg = _alloc_allocate(&pt_basic_string->_t_vector._t_allocater, t_typesize, 1);
    assert(pv_varg != NULL);
    _basic_string_get_varg_value_auxiliary(pt_basic_string, val_elemlist, pv_varg);

    vector_resize(&pt_basic_string->_t_vector, basic_string_size(pt_basic_string) + 1);
    pc_dest = (char*)vector_at(
        &pt_basic_string->_t_vector, basic_string_size(pt_basic_string) - 1);
    assert(pc_dest != NULL);
    t_result = t_typesize;
    _GET_BASIC_STRING_TYPE_COPY_FUNCTION(pt_basic_string)(pc_dest, pv_varg, &t_result);
    assert(t_result);

    _basic_string_destroy_varg_value_auxiliary(pt_basic_string, pv_varg);
    _alloc_deallocate(&pt_basic_string->_t_vector._t_allocater, pv_varg, t_typesize, 1);
}

size_t _basic_string_find_elem(
    const basic_string_t* cpt_basic_string, size_t t_pos, ...)
{
    size_t t_count = 0;
    va_list val_elemlist;

    va_start(val_elemlist, t_pos);
    t_count = _basic_string_find_elem_varg(cpt_basic_string, t_pos, val_elemlist);
    va_end(val_elemlist);

    return t_count;
}

size_t _basic_string_find_elem_varg(
    const basic_string_t* cpt_basic_string, size_t t_pos, va_list val_elemlist)
{
    size_t  t_typesize = 0;
    size_t  t_findpos = 0;
    size_t  t_stringlen = 0;
    void*   pv_varg = NULL;
    char*   pc_string = NULL;
    bool_t  t_less = false;
    bool_t  t_greater = false;

    assert(cpt_basic_string != NULL);

    if(t_pos >= basic_string_size(cpt_basic_string))
    {
        return NPOS;
    }

    /* get element */
    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
    pv_varg = _alloc_allocate(
        &((basic_string_t*)cpt_basic_string)->_t_vector._t_allocater, t_typesize, 1);
    assert(pv_varg != NULL);
    _basic_string_get_varg_value_auxiliary(
        (basic_string_t*)cpt_basic_string, val_elemlist, pv_varg);

    /* find elemen */
    t_stringlen = basic_string_length(cpt_basic_string);
    pc_string = (char*)basic_string_at(cpt_basic_string, 0);
    t_findpos = t_pos;
    while(t_findpos != t_stringlen)
    {
        t_less = t_greater = t_typesize;
        _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
            pc_string + t_findpos * t_typesize, pv_varg, &t_less);
        _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
            pv_varg, pc_string + t_findpos * t_typesize, &t_greater);
        if(!t_less && !t_greater)
        {
            break;
        }
        else
        {
            t_findpos++;
        }
    }

    if(t_findpos == t_stringlen)
    {
        t_findpos = NPOS;
    }
    _basic_string_destroy_varg_value_auxiliary((basic_string_t*)cpt_basic_string, pv_varg);
    _alloc_deallocate(&((basic_string_t*)cpt_basic_string)->_t_vector._t_allocater, pv_varg,
        _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string), 1);

    return t_findpos;
}

size_t _basic_string_rfind_elem(
    const basic_string_t* cpt_basic_string, size_t t_pos, ...)
{
    size_t t_count = 0;
    va_list val_elemlist;

    va_start(val_elemlist, t_pos);
    t_count = _basic_string_rfind_elem_varg(cpt_basic_string, t_pos, val_elemlist);
    va_end(val_elemlist);

    return t_count;
}

size_t _basic_string_rfind_elem_varg(
    const basic_string_t* cpt_basic_string, size_t t_pos, va_list val_elemlist)
{
    size_t  t_typesize = 0;
    size_t  t_stringlen = 0;
    void*   pv_varg = NULL;
    char*   pc_string = NULL;
    size_t  t_findpos = 0;
    bool_t  t_less = false;
    bool_t  t_greater = false;

    assert(cpt_basic_string != NULL);

    if(basic_string_empty(cpt_basic_string))
    {
        return NPOS;
    }

    /* get element */
    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
    pv_varg = _alloc_allocate(
        &((basic_string_t*)cpt_basic_string)->_t_vector._t_allocater, t_typesize, 1);
    assert(pv_varg != NULL);
    _basic_string_get_varg_value_auxiliary(
        (basic_string_t*)cpt_basic_string, val_elemlist, pv_varg);

    /* find elemen */
    t_stringlen = basic_string_length(cpt_basic_string);
    if(t_pos > t_stringlen)
    {
        t_pos = t_stringlen;
    }
    pc_string = (char*)basic_string_at(cpt_basic_string, 0);
    t_findpos = t_pos == t_stringlen ? t_pos - 1 : t_pos;
    for(;;)
    {
        t_less = t_greater = t_typesize;
        _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
            pc_string + t_findpos * t_typesize, pv_varg, &t_less);
        _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
            pv_varg, pc_string + t_findpos * t_typesize, &t_greater);
        if(!t_less && !t_greater)
        {
            break;
        }
        else
        {
            if(t_findpos > 0)
            {
                t_findpos--;
            }
            else
            {
                t_findpos = NPOS;
                break;
            }
        }
    }
    _basic_string_destroy_varg_value_auxiliary((basic_string_t*)cpt_basic_string, pv_varg);
    _alloc_deallocate(&((basic_string_t*)cpt_basic_string)->_t_vector._t_allocater, pv_varg,
        _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string), 1);

    return t_findpos;
}

size_t _basic_string_find_first_not_of_elem(
    const basic_string_t* cpt_basic_string, size_t t_pos, ...)
{
    size_t t_count = 0;
    va_list val_elemlist;

    va_start(val_elemlist, t_pos);
    t_count = _basic_string_find_first_not_of_elem_varg(cpt_basic_string, t_pos, val_elemlist);
    va_end(val_elemlist);

    return t_count;
}

size_t _basic_string_find_first_not_of_elem_varg(
    const basic_string_t* cpt_basic_string, size_t t_pos, va_list val_elemlist)
{
    size_t  t_typesize = 0;
    size_t  t_findpos = 0;
    size_t  t_stringlen = 0;
    void*   pv_varg = NULL;
    char*   pc_string = NULL;
    bool_t  t_less = false;
    bool_t  t_greater = false;

    assert(cpt_basic_string != NULL);

    if(t_pos >= basic_string_size(cpt_basic_string))
    {
        return NPOS;
    }

    /* get element */
    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
    pv_varg = _alloc_allocate(
        &((basic_string_t*)cpt_basic_string)->_t_vector._t_allocater, t_typesize, 1);
    assert(pv_varg != NULL);
    _basic_string_get_varg_value_auxiliary(
        (basic_string_t*)cpt_basic_string, val_elemlist, pv_varg);

    /* find elemen */
    t_stringlen = basic_string_length(cpt_basic_string);
    pc_string = (char*)basic_string_at(cpt_basic_string, 0);
    t_findpos = t_pos;
    while(t_findpos != t_stringlen)
    {
        t_less = t_greater = t_typesize;
        _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
            pc_string + t_findpos * t_typesize, pv_varg, &t_less);
        _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
            pv_varg, pc_string + t_findpos * t_typesize, &t_greater);
        if(t_less || t_greater)
        {
            break;
        }
        else
        {
            t_findpos++;
        }
    }

    if(t_findpos == t_stringlen)
    {
        t_findpos = NPOS;
    }
    _basic_string_destroy_varg_value_auxiliary((basic_string_t*)cpt_basic_string, pv_varg);
    _alloc_deallocate(&((basic_string_t*)cpt_basic_string)->_t_vector._t_allocater, pv_varg,
        _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string), 1);

    return t_findpos;
}

size_t _basic_string_find_last_not_of_elem(
    const basic_string_t* cpt_basic_string, size_t t_pos, ...)
{
    size_t t_count = 0;
    va_list val_elemlist;

    va_start(val_elemlist, t_pos);
    t_count = _basic_string_find_last_not_of_elem_varg(
        cpt_basic_string, t_pos, val_elemlist);
    va_end(val_elemlist);

    return t_count;
}

size_t _basic_string_find_last_not_of_elem_varg(
    const basic_string_t* cpt_basic_string, size_t t_pos, va_list val_elemlist)
{
    size_t  t_typesize = 0;
    size_t  t_stringlen = 0;
    void*   pv_varg = NULL;
    char*   pc_string = NULL;
    size_t  t_findpos = 0;
    bool_t  t_less = false;
    bool_t  t_greater = false;

    assert(cpt_basic_string != NULL);

    if(basic_string_empty(cpt_basic_string))
    {
        return NPOS;
    }

    /* get element */
    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
    pv_varg = _alloc_allocate(
        &((basic_string_t*)cpt_basic_string)->_t_vector._t_allocater, t_typesize, 1);
    assert(pv_varg != NULL);
    _basic_string_get_varg_value_auxiliary(
        (basic_string_t*)cpt_basic_string, val_elemlist, pv_varg);

    /* find elemen */
    t_stringlen = basic_string_length(cpt_basic_string);
    if(t_pos > t_stringlen)
    {
        t_pos = t_stringlen;
    }
    pc_string = (char*)basic_string_at(cpt_basic_string, 0);
    t_findpos = t_pos == t_stringlen ? t_pos - 1 : t_pos;
    for(;;)
    {
        t_less = t_greater = t_typesize;
        _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
            pc_string + t_findpos * t_typesize, pv_varg, &t_less);
        _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
            pv_varg, pc_string + t_findpos * t_typesize, &t_greater);
        if(t_less || t_greater)
        {
            break;
        }
        else
        {
            if(t_findpos > 0)
            {
                t_findpos--;
            }
            else
            {
                t_findpos = NPOS;
                break;
            }
        }
    }

    _basic_string_destroy_varg_value_auxiliary((basic_string_t*)cpt_basic_string, pv_varg);
    _alloc_deallocate(&((basic_string_t*)cpt_basic_string)->_t_vector._t_allocater, pv_varg,
        _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string), 1);

    return t_findpos;
}


void _basic_string_resize(basic_string_t* pt_basic_string, size_t t_resize, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_resize);
    _basic_string_resize_varg(pt_basic_string, t_resize, val_elemlist);
    va_end(val_elemlist);
}

void _basic_string_resize_varg(
    basic_string_t* pt_basic_string, size_t t_resize, va_list val_elemlist)
{
    assert(pt_basic_string != NULL);

    _vector_resize_elem_varg(&pt_basic_string->_t_vector, t_resize, val_elemlist);
}

void _basic_string_pop_back(basic_string_t* pt_basic_string)
{
    assert(pt_basic_string != NULL);
    vector_pop_back(&pt_basic_string->_t_vector);
}

void _basic_string_push_back(basic_string_t* pt_basic_string, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, pt_basic_string);
    _basic_string_push_back_varg(pt_basic_string, val_elemlist);
    va_end(val_elemlist);
}

void _basic_string_push_back_varg(basic_string_t* pt_basic_string, va_list val_elemlist)
{
    void*   pv_varg = NULL;
    char*   pc_dest = NULL;
    size_t  t_typesize = 0;
    bool_t  t_result = false;

    assert(pt_basic_string != NULL);

    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string);
    pv_varg = _alloc_allocate(&pt_basic_string->_t_vector._t_allocater, t_typesize, 1);
    assert(pv_varg != NULL);
    _basic_string_get_varg_value_auxiliary(pt_basic_string, val_elemlist, pv_varg);

    vector_resize(&pt_basic_string->_t_vector, basic_string_size(pt_basic_string) + 1);
    /*
    pc_dest = vector_at(&pt_basic_string->_t_vector, basic_string_size(pt_basic_string) - 1);
    assert(pc_dest != NULL);
    _basic_string_init_elem_auxiliary(pt_basic_string, pc_dest);
    */
    pc_dest = _GET_VECTOR_COREPOS(iterator_prev(vector_end(&pt_basic_string->_t_vector)));
    assert(pc_dest != NULL);

    t_result = t_typesize;
    _GET_BASIC_STRING_TYPE_COPY_FUNCTION(pt_basic_string)(pc_dest, pv_varg, &t_result);
    assert(t_result);

    _basic_string_destroy_varg_value_auxiliary(pt_basic_string, pv_varg);
    _alloc_deallocate(&pt_basic_string->_t_vector._t_allocater, pv_varg, t_typesize, 1);
}

void _basic_string_assign_elem(
    basic_string_t* pt_basic_string, size_t t_count, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_count);
    _basic_string_assign_elem_varg(pt_basic_string, t_count, val_elemlist);
    va_end(val_elemlist);
}

void _basic_string_assign_elem_varg(
    basic_string_t* pt_basic_string, size_t t_count, va_list val_elemlist)
{
    size_t  t_index = 0;

    assert(pt_basic_string != NULL);

    vector_clear(&pt_basic_string->_t_vector);
    assert(vector_size(&pt_basic_string->_t_vector) == 0);

    vector_reserve(&pt_basic_string->_t_vector, t_count * 2);
    for(t_index = 0; t_index < t_count; ++t_index)
    {
        va_list val_elemlist_copy;

        va_copy(val_elemlist_copy, val_elemlist);
        _vector_push_back_varg(&pt_basic_string->_t_vector, val_elemlist_copy);
        va_end(val_elemlist_copy);
    }
}


void _basic_string_append_elem(
    basic_string_t* pt_basic_string, size_t t_count, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_count);
    _basic_string_append_elem_varg(pt_basic_string, t_count, val_elemlist);
    va_end(val_elemlist);
}

void _basic_string_append_elem_varg(
    basic_string_t* pt_basic_string, size_t t_count, va_list val_elemlist)
{
    _basic_string_resize_varg(
        pt_basic_string, basic_string_size(pt_basic_string) + t_count, val_elemlist);
}

/* insert */
basic_string_iterator_t _basic_string_insert(
    basic_string_t* pt_basic_string, basic_string_iterator_t t_pos, ...)
{
    basic_string_iterator_t t_iter;
    va_list val_elemlist;

    va_start(val_elemlist, t_pos);
    t_iter = _basic_string_insert_n_varg(pt_basic_string, t_pos, 1, val_elemlist);
    va_end(val_elemlist);

    return t_iter;
}

basic_string_iterator_t _basic_string_insert_n(
    basic_string_t* pt_basic_string, basic_string_iterator_t t_pos, size_t t_count, ...)
{
    basic_string_iterator_t t_iter;
    va_list val_elemlist;

    va_start(val_elemlist, t_count);
    t_iter = _basic_string_insert_n_varg(pt_basic_string, t_pos, t_count, val_elemlist);
    va_end(val_elemlist);

    return t_iter;
}

basic_string_iterator_t _basic_string_insert_n_varg(
    basic_string_t* pt_basic_string, basic_string_iterator_t t_pos,
    size_t t_count, va_list val_elemlist)
{
    assert(pt_basic_string != NULL);

    _GET_BASIC_STRING_CONTAINER_TYPE(t_pos) = _VECTOR_CONTAINER;
    return _vector_insert_n_varg(
        &pt_basic_string->_t_vector, t_pos, t_count, val_elemlist);
}

void _basic_string_insert_elem(
    basic_string_t* pt_basic_string, size_t t_pos, size_t t_count, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_count);
    _basic_string_insert_elem_varg(pt_basic_string, t_pos, t_count, val_elemlist);
    va_end(val_elemlist);
}

void _basic_string_insert_elem_varg(
    basic_string_t* pt_basic_string, size_t t_pos, size_t t_count, va_list val_elemlist)
{
    basic_string_iterator_t t_insert;

    assert(pt_basic_string != NULL);
    assert(t_pos <= basic_string_size(pt_basic_string));

    t_insert = iterator_next_n(basic_string_begin(pt_basic_string), t_pos);
    _GET_VECTOR_CONTAINER_TYPE(t_insert) = _VECTOR_CONTAINER;
    _vector_insert_n_varg(&pt_basic_string->_t_vector, t_insert, t_count, val_elemlist);
}


void _basic_string_replace_elem(
    basic_string_t* pt_basic_string, size_t t_pos, size_t t_len, size_t t_count, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_count);
    _basic_string_replace_elem_varg(pt_basic_string, t_pos, t_len, t_count, val_elemlist);
    va_end(val_elemlist);
}

void _basic_string_replace_elem_varg(
    basic_string_t* pt_basic_string, size_t t_pos, 
    size_t t_len, size_t t_count, va_list val_elemlist)
{
    basic_string_iterator_t t_begin = basic_string_begin(pt_basic_string);
    basic_string_iterator_t t_end   = basic_string_begin(pt_basic_string);

    assert(t_pos <= basic_string_size(pt_basic_string));

    t_begin = iterator_next_n(t_begin, t_pos);
    if(t_len == NPOS || t_pos + t_len >= basic_string_size(pt_basic_string))
    {
        t_end = basic_string_end(pt_basic_string);
    }
    else
    {
        t_end = iterator_next_n(t_end, t_pos + t_len);
    }
    _basic_string_range_replace_elem_varg(
        pt_basic_string, t_begin, t_end, t_count, val_elemlist);
}

void _basic_string_range_replace_elem(
    basic_string_t* pt_basic_string, basic_string_iterator_t t_begin,
    basic_string_iterator_t t_end, size_t t_count, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_count);
    _basic_string_range_replace_elem_varg(
        pt_basic_string, t_begin, t_end, t_count, val_elemlist);
    va_end(val_elemlist);
}

void _basic_string_range_replace_elem_varg(
    basic_string_t* pt_basic_string, basic_string_iterator_t t_begin,
    basic_string_iterator_t t_end, size_t t_count, va_list val_elemlist)
{
    basic_string_iterator_t t_iterator = basic_string_erase_range(
        pt_basic_string, t_begin, t_end);
    size_t t_pos = (size_t)iterator_distance(
        basic_string_begin(pt_basic_string), t_iterator);

    _basic_string_insert_elem_varg(pt_basic_string, t_pos, t_count, val_elemlist);
}

void _basic_string_init_elem_auxiliary(basic_string_t* pt_basic_string, void* pv_elem)
{
    assert(pt_basic_string != NULL && pv_elem != NULL);

    /* initialize new elements */
    if(_GET_BASIC_STRING_TYPE_STYLE(pt_basic_string) == _TYPE_CSTL_BUILTIN)
    {
        /* get element type name */
        char s_elemtypename[_TYPE_NAME_SIZE + 1];
        _type_get_elem_typename(_GET_BASIC_STRING_TYPE_NAME(pt_basic_string), s_elemtypename);

        _GET_BASIC_STRING_TYPE_INIT_FUNCTION(pt_basic_string)(pv_elem, s_elemtypename);
    }
    else
    {
        bool_t t_result = _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string);
        _GET_BASIC_STRING_TYPE_INIT_FUNCTION(pt_basic_string)(pv_elem, &t_result);
        assert(t_result);
    }
}

/** local function implementation section **/

/** eof **/

