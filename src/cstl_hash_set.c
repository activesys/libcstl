/*
 *  The implementation of hash_set.
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
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "cstl_alloc.h"
#include "cstl_types.h"
#include "cstl_iterator.h"
#include "cstl_iterator_private.h"

#include "cvector.h"
#include "cstl_hashtable_iterator.h"
#include "cstl_hashtable_private.h"
#include "cutility.h"

#include "cstl_hash_set_iterator.h"
#include "cstl_hash_set_private.h"
#include "cstl_hash_set.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/* hash_set iterator function */
hash_set_iterator_t create_hash_set_iterator(void)
{
    hash_set_iterator_t t_newiterator = _create_hashtable_iterator();

    _GET_HASH_SET_CONTAINER_TYPE(t_newiterator) = _HASH_SET_CONTAINER;
    _GET_HASH_SET_ITERATOR_TYPE(t_newiterator) = _FORWARD_ITERATOR;

    return t_newiterator;
}

void _hash_set_iterator_get_value(hash_set_iterator_t t_iter, void* pv_value)
{
    assert(pv_value != NULL);
    assert(_GET_HASH_SET_CONTAINER_TYPE(t_iter) == _HASH_SET_CONTAINER &&
           _GET_HASH_SET_ITERATOR_TYPE(t_iter) == _FORWARD_ITERATOR);

    _hashtable_iterator_get_value(t_iter, pv_value);
}

const void* _hash_set_iterator_get_pointer(hash_set_iterator_t t_iter)
{
    assert(_GET_HASH_SET_CONTAINER_TYPE(t_iter) == _HASH_SET_CONTAINER &&
           _GET_HASH_SET_ITERATOR_TYPE(t_iter) == _FORWARD_ITERATOR);

    return _hashtable_iterator_get_pointer(t_iter);
}

hash_set_iterator_t _hash_set_iterator_next(hash_set_iterator_t t_iter)
{
    assert(_GET_HASH_SET_CONTAINER_TYPE(t_iter) == _HASH_SET_CONTAINER &&
           _GET_HASH_SET_ITERATOR_TYPE(t_iter) == _FORWARD_ITERATOR);

    return _hashtable_iterator_next(t_iter);
}

bool_t _hash_set_iterator_equal(
    hash_set_iterator_t t_iterfirst, hash_set_iterator_t t_itersecond)
{
    assert(_GET_HASH_SET_CONTAINER_TYPE(t_iterfirst) == _HASH_SET_CONTAINER &&
           _GET_HASH_SET_ITERATOR_TYPE(t_iterfirst) == _FORWARD_ITERATOR &&
           _GET_HASH_SET_CONTAINER_TYPE(t_itersecond) == _HASH_SET_CONTAINER &&
           _GET_HASH_SET_ITERATOR_TYPE(t_itersecond) == _FORWARD_ITERATOR);

    return _hashtable_iterator_equal(t_iterfirst, t_itersecond);
}

int _hash_set_iterator_distance(
    hash_set_iterator_t t_iterfirst, hash_set_iterator_t t_itersecond)
{
    assert(_GET_HASH_SET_CONTAINER_TYPE(t_iterfirst) == _HASH_SET_CONTAINER &&
           _GET_HASH_SET_ITERATOR_TYPE(t_iterfirst) == _FORWARD_ITERATOR &&
           _GET_HASH_SET_CONTAINER_TYPE(t_itersecond) == _HASH_SET_CONTAINER &&
           _GET_HASH_SET_ITERATOR_TYPE(t_itersecond) == _FORWARD_ITERATOR &&
           _GET_HASH_SET_CONTAINER(t_iterfirst) == _GET_HASH_SET_CONTAINER(t_itersecond));

    return _hashtable_iterator_distance(t_iterfirst, t_itersecond);
}

bool_t _hash_set_iterator_before(
    hash_set_iterator_t t_iterfirst, hash_set_iterator_t t_itersecond)
{
    assert(_GET_HASH_SET_CONTAINER_TYPE(t_iterfirst) == _HASH_SET_CONTAINER &&
           _GET_HASH_SET_ITERATOR_TYPE(t_iterfirst) == _FORWARD_ITERATOR &&
           _GET_HASH_SET_CONTAINER_TYPE(t_itersecond) == _HASH_SET_CONTAINER &&
           _GET_HASH_SET_ITERATOR_TYPE(t_itersecond) == _FORWARD_ITERATOR &&
           _GET_HASH_SET_CONTAINER(t_iterfirst) == 
               _GET_HASH_SET_CONTAINER(t_itersecond));

    return _hashtable_iterator_before(t_iterfirst, t_itersecond);
}

/* hash_set private function */
hash_set_t _create_hash_set(size_t t_typesize, const char* s_typename)
{
    hash_set_t t_new_hash_set;
    char       ac_hashsettypename[_ELEM_TYPE_NAME_SIZE+1];
    char       ac_unifytypename[_ELEM_TYPE_NAME_SIZE+1];

    assert(s_typename != NULL);

    memset(ac_unifytypename, '\0', _ELEM_TYPE_NAME_SIZE+1);
    strncpy(ac_unifytypename, s_typename, _ELEM_TYPE_NAME_SIZE);
    _unify_types(t_typesize, ac_unifytypename);
    
    memset(ac_hashsettypename, '\0', _ELEM_TYPE_NAME_SIZE+1);
    strncpy(ac_hashsettypename, _HASH_SET_IDENTIFY, _ELEM_TYPE_NAME_SIZE);
    strcat(ac_hashsettypename, _HASH_SET_LEFT_BRACKET);
    strcat(ac_hashsettypename, ac_unifytypename);
    strcat(ac_hashsettypename, _HASH_SET_RIGHT_BRACKET);

    t_new_hash_set._t_hashtable = _create_hashtable(t_typesize, ac_hashsettypename);

    return t_new_hash_set;
}

/* hash_set function */
void hash_set_init(
    hash_set_t* pt_hash_set, int (*pfun_hash)(const void*, size_t, size_t))
{
    hash_set_init_n(pt_hash_set, 0, pfun_hash);
}

void hash_set_init_n(
    hash_set_t* pt_hash_set, size_t t_bucketcount,
    int (*pfun_hash)(const void*, size_t, size_t))
{
    assert(pt_hash_set != NULL);

    _hashtable_init(&pt_hash_set->_t_hashtable, t_bucketcount, pfun_hash, NULL, NULL);
}

void hash_set_destroy(hash_set_t* pt_hash_set)
{
    assert(pt_hash_set != NULL);

    _hashtable_destroy(&pt_hash_set->_t_hashtable);
}

void hash_set_init_copy(hash_set_t* pt_hash_setdest, const hash_set_t* cpt_hash_setsrc)
{
    assert(pt_hash_setdest != NULL && cpt_hash_setsrc != NULL);

    _hashtable_init_copy(&pt_hash_setdest->_t_hashtable, &cpt_hash_setsrc->_t_hashtable);
}

void hash_set_init_copy_range(
    hash_set_t* pt_hash_setdest, hash_set_iterator_t t_begin, hash_set_iterator_t t_end,
    int (*pfun_hash)(const void*, size_t, size_t))
{
    hash_set_init_copy_range_n(pt_hash_setdest, t_begin, t_end, 0, pfun_hash);
}

void hash_set_init_copy_range_n(
    hash_set_t* pt_hash_setdest, hash_set_iterator_t t_begin, hash_set_iterator_t t_end,
    size_t t_bucketcount, int (*pfun_hash)(const void*, size_t, size_t))
{
    assert(pt_hash_setdest != NULL);
    assert(_GET_HASH_SET_CONTAINER_TYPE(t_begin) == _HASH_SET_CONTAINER &&
           _GET_HASH_SET_ITERATOR_TYPE(t_begin) == _FORWARD_ITERATOR &&
           _GET_HASH_SET_CONTAINER_TYPE(t_end) == _HASH_SET_CONTAINER &&
           _GET_HASH_SET_ITERATOR_TYPE(t_end) == _FORWARD_ITERATOR);
    assert(_GET_HASH_SET_CONTAINER(t_begin) != pt_hash_setdest &&
           _GET_HASH_SET_CONTAINER(t_end) != pt_hash_setdest &&
           _GET_HASH_SET_CONTAINER(t_begin) == _GET_HASH_SET_CONTAINER(t_end));

    _hashtable_init_copy_range(
        &pt_hash_setdest->_t_hashtable, t_begin, t_end, t_bucketcount, pfun_hash, NULL);
}

void hash_set_assign(
    hash_set_t* pt_hash_setdest, const hash_set_t* cpt_hash_setsrc)
{
    assert(pt_hash_setdest != NULL && cpt_hash_setsrc != NULL);

    _hashtable_assign(&pt_hash_setdest->_t_hashtable, &cpt_hash_setsrc->_t_hashtable);
}

void hash_set_swap(hash_set_t* pt_hash_setfirst, hash_set_t* pt_hash_setsecond)
{
    assert(pt_hash_setfirst != NULL && pt_hash_setsecond != NULL);

    _hashtable_swap(&pt_hash_setfirst->_t_hashtable, &pt_hash_setsecond->_t_hashtable);
}

size_t hash_set_size(const hash_set_t* cpt_hash_set)
{
    assert(cpt_hash_set != NULL);

    return _hashtable_size(&cpt_hash_set->_t_hashtable);
}

size_t hash_set_max_size(const hash_set_t* cpt_hash_set)
{
    assert(cpt_hash_set != NULL);

    return _hashtable_max_size(&cpt_hash_set->_t_hashtable);
}

bool_t hash_set_empty(const hash_set_t* cpt_hash_set)
{
    assert(cpt_hash_set != NULL);

    return _hashtable_empty(&cpt_hash_set->_t_hashtable);
}

size_t hash_set_bucket_count(const hash_set_t* cpt_hash_set)
{
    assert(cpt_hash_set != NULL);

    return _hashtable_bucket_count(&cpt_hash_set->_t_hashtable);
}

int (*hash_set_hash_func(const hash_set_t* cpt_hash_set))(
    const void*, size_t, size_t)
{
    assert(cpt_hash_set != NULL);

    return _hashtable_hash_func(&cpt_hash_set->_t_hashtable);
}

int (*hash_set_key_comp(const hash_set_t* cpt_hash_set))(
    const void*, const void*)
{
    assert(cpt_hash_set != NULL);

    return _hashtable_key_comp(&cpt_hash_set->_t_hashtable);
}

void hash_set_resize(hash_set_t* pt_hash_set, size_t t_resize)
{
    assert(pt_hash_set != NULL);

    _hashtable_resize(&pt_hash_set->_t_hashtable, t_resize);
}

bool_t hash_set_equal(
    const hash_set_t* cpt_hash_setfirst, const hash_set_t* cpt_hash_setsecond)
{
    assert(cpt_hash_setfirst != NULL && cpt_hash_setsecond != NULL);

    return _hashtable_equal(
        &cpt_hash_setfirst->_t_hashtable, &cpt_hash_setsecond->_t_hashtable);
}

bool_t hash_set_not_equal(
    const hash_set_t* cpt_hash_setfirst, const hash_set_t* cpt_hash_setsecond)
{
    assert(cpt_hash_setfirst != NULL && cpt_hash_setsecond != NULL);

    return _hashtable_not_equal(
        &cpt_hash_setfirst->_t_hashtable, &cpt_hash_setsecond->_t_hashtable);
}

bool_t hash_set_less(
    const hash_set_t* cpt_hash_setfirst, const hash_set_t* cpt_hash_setsecond)
{
    /* add now relationship operator */
    return true;
}

hash_set_iterator_t hash_set_begin(const hash_set_t* cpt_hash_set)
{
    hash_set_iterator_t t_newiterator;

    assert(cpt_hash_set != NULL);

    t_newiterator = _hashtable_begin(&cpt_hash_set->_t_hashtable);

    _GET_CONTAINER(t_newiterator) = (hash_set_t*)cpt_hash_set;
    _GET_HASH_SET_CONTAINER_TYPE(t_newiterator) = _HASH_SET_CONTAINER;
    _GET_HASH_SET_ITERATOR_TYPE(t_newiterator) = _FORWARD_ITERATOR;

    return t_newiterator;
}

hash_set_iterator_t hash_set_end(const hash_set_t* cpt_hash_set)
{
    hash_set_iterator_t t_newiterator;

    assert(cpt_hash_set != NULL);

    t_newiterator = _hashtable_end(&cpt_hash_set->_t_hashtable);

    _GET_CONTAINER(t_newiterator) = (hash_set_t*)cpt_hash_set;
    _GET_HASH_SET_CONTAINER_TYPE(t_newiterator) = _HASH_SET_CONTAINER;
    _GET_HASH_SET_ITERATOR_TYPE(t_newiterator) = _FORWARD_ITERATOR;

    return t_newiterator;
}

hash_set_iterator_t _hash_set_find(const hash_set_t* cpt_hash_set, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, cpt_hash_set);
    return _hash_set_find_varg(cpt_hash_set, val_elemlist);
}

hash_set_iterator_t _hash_set_find_varg(
    const hash_set_t* cpt_hash_set, va_list val_elemlist)
{
    hash_set_iterator_t t_newiterator;
    char*               pc_value = NULL;

    assert(cpt_hash_set != NULL);

    pc_value = (char*)malloc(cpt_hash_set->_t_hashtable._t_typesize);
    if(pc_value == NULL)
    {
        fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        memset(pc_value, 0x00, cpt_hash_set->_t_hashtable._t_typesize);
        _get_varg_value(
            pc_value, val_elemlist, cpt_hash_set->_t_hashtable._t_typesize,
            cpt_hash_set->_t_hashtable._sz_typename);
    }

    t_newiterator = _hashtable_find(&cpt_hash_set->_t_hashtable, pc_value);
    free(pc_value);
    pc_value = NULL;

    _GET_CONTAINER(t_newiterator) = (hash_set_t*)cpt_hash_set;
    _GET_HASH_SET_CONTAINER_TYPE(t_newiterator) = _HASH_SET_CONTAINER;
    _GET_HASH_SET_ITERATOR_TYPE(t_newiterator) = _FORWARD_ITERATOR;

    return t_newiterator;
}

size_t _hash_set_count(const hash_set_t* cpt_hash_set, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, cpt_hash_set);
    return _hash_set_count_varg(cpt_hash_set, val_elemlist);
}

size_t _hash_set_count_varg(const hash_set_t* cpt_hash_set, va_list val_elemlist)
{
    size_t  t_countsize = 0;
    char*   pc_value = NULL;

    assert(cpt_hash_set != NULL);

    pc_value = (char*)malloc(cpt_hash_set->_t_hashtable._t_typesize);
    if(pc_value == NULL)
    {
        fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        memset(pc_value, 0x00, cpt_hash_set->_t_hashtable._t_typesize);
        _get_varg_value(
            pc_value, val_elemlist, cpt_hash_set->_t_hashtable._t_typesize,
            cpt_hash_set->_t_hashtable._sz_typename);
    }

    t_countsize = _hashtable_count(&cpt_hash_set->_t_hashtable, pc_value);
    free(pc_value);
    pc_value = NULL;

    return t_countsize;
}

pair_t _hash_set_equal_range(const hash_set_t* cpt_hash_set, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, cpt_hash_set);
    return _hash_set_equal_range_varg(cpt_hash_set, val_elemlist);
}

pair_t _hash_set_equal_range_varg(const hash_set_t* cpt_hash_set, va_list val_elemlist)
{
    hash_set_iterator_t     t_firstiterator;
    hash_set_iterator_t     t_seconditerator;
    hashtable_result_pair_t t_result;
    char*                   pc_value = NULL;
    pair_t                  t_pair;

    assert(cpt_hash_set != NULL);

    pc_value = (char*)malloc(cpt_hash_set->_t_hashtable._t_typesize);
    if(pc_value == NULL)
    {
        fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        memset(pc_value, 0x00, cpt_hash_set->_t_hashtable._t_typesize);
        _get_varg_value(
            pc_value, val_elemlist, cpt_hash_set->_t_hashtable._t_typesize,
            cpt_hash_set->_t_hashtable._sz_typename);
    }

    t_result = _hashtable_equal_range(&cpt_hash_set->_t_hashtable, pc_value);
    free(pc_value);
    pc_value = NULL;

    t_firstiterator = t_result._t_first;
    _GET_CONTAINER(t_firstiterator) = (hash_set_t*)cpt_hash_set;
    _GET_HASH_SET_CONTAINER_TYPE(t_firstiterator) = _HASH_SET_CONTAINER;
    _GET_HASH_SET_ITERATOR_TYPE(t_firstiterator) = _FORWARD_ITERATOR;

    t_seconditerator = t_result._t_second._t_iterator;
    _GET_CONTAINER(t_seconditerator) = (hash_set_t*)cpt_hash_set;
    _GET_HASH_SET_CONTAINER_TYPE(t_seconditerator) = _HASH_SET_CONTAINER;
    _GET_HASH_SET_ITERATOR_TYPE(t_seconditerator) = _FORWARD_ITERATOR;

    t_pair = create_pair(hash_set_iterator_t, hash_set_iterator_t);
    pair_init(&t_pair);
    memcpy(t_pair.first, &t_firstiterator, t_pair._t_firsttypesize);
    memcpy(t_pair.second, &t_seconditerator, t_pair._t_secondtypesize);

    return t_pair;
}

hash_set_iterator_t _hash_set_insert(hash_set_t* pt_hash_set, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, pt_hash_set);
    return _hash_set_insert_varg(pt_hash_set, val_elemlist);
}

hash_set_iterator_t _hash_set_insert_varg(hash_set_t* pt_hash_set, va_list val_elemlist)
{
    hashtable_result_pair_t t_result;
    char*                   pc_value;

    assert(pt_hash_set != NULL);

    pc_value = (char*)malloc(pt_hash_set->_t_hashtable._t_typesize);
    if(pc_value == NULL)
    {
        fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        memset(pc_value, 0x00, pt_hash_set->_t_hashtable._t_typesize);
        _get_varg_value(
            pc_value, val_elemlist, pt_hash_set->_t_hashtable._t_typesize,
            pt_hash_set->_t_hashtable._sz_typename);
    }

    t_result = _hashtable_insert_unique(&pt_hash_set->_t_hashtable, pc_value);
    free(pc_value);
    pc_value = NULL;

    _GET_CONTAINER(t_result._t_first) = pt_hash_set;
    _GET_HASH_SET_CONTAINER_TYPE(t_result._t_first) = _HASH_SET_CONTAINER;
    _GET_HASH_SET_ITERATOR_TYPE(t_result._t_first) = _FORWARD_ITERATOR;

    return t_result._t_second._t_bool ? t_result._t_first : hash_set_end(pt_hash_set);
}

void hash_set_insert_range(
    hash_set_t* pt_hash_set, hash_set_iterator_t t_begin, hash_set_iterator_t t_end)
{
    assert(pt_hash_set != NULL);
    assert(_GET_HASH_SET_CONTAINER_TYPE(t_begin) == _HASH_SET_CONTAINER &&
           _GET_HASH_SET_ITERATOR_TYPE(t_begin) == _FORWARD_ITERATOR &&
           _GET_HASH_SET_CONTAINER_TYPE(t_end) == _HASH_SET_CONTAINER &&
           _GET_HASH_SET_ITERATOR_TYPE(t_end) == _FORWARD_ITERATOR);
    assert(_GET_HASH_SET_CONTAINER(t_begin) != pt_hash_set &&
           _GET_HASH_SET_CONTAINER(t_end) != pt_hash_set &&
           _GET_HASH_SET_CONTAINER(t_begin) == _GET_HASH_SET_CONTAINER(t_end));

    _hashtable_insert_unique_range(&pt_hash_set->_t_hashtable, t_begin, t_end);
}

void hash_set_erase_pos(hash_set_t* pt_hash_set, hash_set_iterator_t t_pos)
{
    assert(pt_hash_set != NULL);
    assert(_GET_HASH_SET_CONTAINER_TYPE(t_pos) == _HASH_SET_CONTAINER &&
           _GET_HASH_SET_ITERATOR_TYPE(t_pos) == _FORWARD_ITERATOR &&
           _GET_HASH_SET_CONTAINER(t_pos) == pt_hash_set);

    _hashtable_erase_pos(&pt_hash_set->_t_hashtable, t_pos);
}

void hash_set_erase_range(
    hash_set_t* pt_hash_set, hash_set_iterator_t t_begin, hash_set_iterator_t t_end)
{
    assert(pt_hash_set != NULL);
    assert(_GET_HASH_SET_CONTAINER_TYPE(t_begin) == _HASH_SET_CONTAINER &&
           _GET_HASH_SET_ITERATOR_TYPE(t_begin) == _FORWARD_ITERATOR &&
           _GET_HASH_SET_CONTAINER_TYPE(t_end) == _HASH_SET_CONTAINER &&
           _GET_HASH_SET_ITERATOR_TYPE(t_end) == _FORWARD_ITERATOR);
    assert(_GET_HASH_SET_CONTAINER(t_begin) == pt_hash_set &&
           _GET_HASH_SET_CONTAINER(t_end) == pt_hash_set);

    _hashtable_erase_range(&pt_hash_set->_t_hashtable, t_begin, t_end);
}

size_t _hash_set_erase(hash_set_t* pt_hash_set, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, pt_hash_set);
    return _hash_set_erase_varg(pt_hash_set, val_elemlist);
}

size_t _hash_set_erase_varg(hash_set_t* pt_hash_set, va_list val_elemlist)
{
    size_t  t_countsize = 0;
    char*   pc_value = NULL;

    assert(pt_hash_set != NULL);

    pc_value = (char*)malloc(pt_hash_set->_t_hashtable._t_typesize);
    if(pc_value == NULL)
    {
        fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        memset(pc_value, 0x00, pt_hash_set->_t_hashtable._t_typesize);
        _get_varg_value(
            pc_value, val_elemlist, pt_hash_set->_t_hashtable._t_typesize,
            pt_hash_set->_t_hashtable._sz_typename);
    }

    t_countsize = _hashtable_erase(&pt_hash_set->_t_hashtable, pc_value);
    free(pc_value);
    pc_value = NULL;

    return t_countsize;
}

void hash_set_clear(hash_set_t* pt_hash_set)
{
    assert(pt_hash_set != NULL);

    _hashtable_clear(&pt_hash_set->_t_hashtable);
}

/** local function implementation section **/

/** eof **/

