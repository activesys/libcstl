/*
 *  The implementation of hash_multiset.
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
/*#include "cutility.h"*/

#include "cstl_hash_multiset_iterator.h"
#include "cstl_hash_multiset_private.h"
#include "cstl_hash_multiset.h"

/** local constant declaration and local macro section **/
/* macros for type informations */
#define _GET_HASH_MULTISET_TYPE_SIZE(pt_hash_multiset)\
    ((pt_hash_multiset)->_t_hashtable._t_typeinfo._pt_type->_t_typesize)
#define _GET_HASH_MULTISET_TYPE_NAME(pt_hash_multiset)\
    ((pt_hash_multiset)->_t_hashtable._t_typeinfo._sz_typename)
#define _GET_HASH_MULTISET_TYPE_BASENAME(pt_hash_multiset)\
    ((pt_hash_multiset)->_t_hashtable._t_typeinfo._pt_type->_sz_typename)
#define _GET_HASH_MULTISET_TYPE_INIT_FUNCTION(pt_hash_multiset)\
    ((pt_hash_multiset)->_t_hashtable._t_typeinfo._pt_type->_t_typeinit)
#define _GET_HASH_MULTISET_TYPE_COPY_FUNCTION(pt_hash_multiset)\
    ((pt_hash_multiset)->_t_hashtable._t_typeinfo._pt_type->_t_typecopy)
#define _GET_HASH_MULTISET_TYPE_LESS_FUNCTION(pt_hash_multiset)\
    ((pt_hash_multiset)->_t_hashtable._t_typeinfo._pt_type->_t_typeless)
#define _GET_HASH_MULTISET_TYPE_DESTROY_FUNCTION(pt_hash_multiset)\
    ((pt_hash_multiset)->_t_hashtable._t_typeinfo._pt_type->_t_typedestroy)
#define _GET_HASH_MULTISET_TYPE_STYLE(pt_hash_multiset)\
    ((pt_hash_multiset)->_t_hashtable._t_typeinfo._t_style)

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/
/*static void _hash_multiset_init_elem_auxiliary(
    hash_multiset_t* pt_hash_multiset, void* pv_elem);*/
static void _hash_multiset_get_varg_value_auxiliary(
    hash_multiset_t* pt_hash_multiset, va_list val_elemlist, void* pv_varg);
static void _hash_multiset_destroy_varg_value_auxiliary(
    hash_multiset_t* pt_hash_multiset, void* pv_varg);

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/* hash_multiset iterator function */
hash_multiset_iterator_t create_hash_multiset_iterator(void)
{
    hash_multiset_iterator_t t_newiterator = _create_hashtable_iterator();

    _GET_HASH_MULTISET_CONTAINER_TYPE(t_newiterator) = _HASH_MULTISET_CONTAINER;
    _GET_HASH_MULTISET_ITERATOR_TYPE(t_newiterator) = _FORWARD_ITERATOR;

    return t_newiterator;
}

void _hash_multiset_iterator_get_value(hash_multiset_iterator_t t_iter, void* pv_value)
{
    assert(pv_value != NULL);
    assert(_GET_HASH_MULTISET_CONTAINER_TYPE(t_iter) == _HASH_MULTISET_CONTAINER &&
           _GET_HASH_MULTISET_ITERATOR_TYPE(t_iter) == _FORWARD_ITERATOR);

    _hashtable_iterator_get_value(t_iter, pv_value);
}

const void* _hash_multiset_iterator_get_pointer(hash_multiset_iterator_t t_iter)
{
    assert(_GET_HASH_MULTISET_CONTAINER_TYPE(t_iter) == _HASH_MULTISET_CONTAINER &&
           _GET_HASH_MULTISET_ITERATOR_TYPE(t_iter) == _FORWARD_ITERATOR);

    return _hashtable_iterator_get_pointer(t_iter);
}

hash_multiset_iterator_t _hash_multiset_iterator_next(hash_multiset_iterator_t t_iter)
{
    assert(_GET_HASH_MULTISET_CONTAINER_TYPE(t_iter) == _HASH_MULTISET_CONTAINER &&
           _GET_HASH_MULTISET_ITERATOR_TYPE(t_iter) == _FORWARD_ITERATOR);

    return _hashtable_iterator_next(t_iter);
}

bool_t _hash_multiset_iterator_equal(
    hash_multiset_iterator_t t_iterfirst, hash_multiset_iterator_t t_itersecond)
{
    assert(_GET_HASH_MULTISET_CONTAINER_TYPE(t_iterfirst) == _HASH_MULTISET_CONTAINER &&
           _GET_HASH_MULTISET_ITERATOR_TYPE(t_iterfirst) == _FORWARD_ITERATOR &&
           _GET_HASH_MULTISET_CONTAINER_TYPE(t_itersecond) == _HASH_MULTISET_CONTAINER &&
           _GET_HASH_MULTISET_ITERATOR_TYPE(t_itersecond) == _FORWARD_ITERATOR);

    return _hashtable_iterator_equal(t_iterfirst, t_itersecond);
}

int _hash_multiset_iterator_distance(
    hash_multiset_iterator_t t_iterfirst, hash_multiset_iterator_t t_itersecond)
{
    assert(_GET_HASH_MULTISET_CONTAINER_TYPE(t_iterfirst) == _HASH_MULTISET_CONTAINER &&
           _GET_HASH_MULTISET_ITERATOR_TYPE(t_iterfirst) == _FORWARD_ITERATOR &&
           _GET_HASH_MULTISET_CONTAINER_TYPE(t_itersecond) == _HASH_MULTISET_CONTAINER &&
           _GET_HASH_MULTISET_ITERATOR_TYPE(t_itersecond) == _FORWARD_ITERATOR &&
           _GET_HASH_MULTISET_CONTAINER(t_iterfirst) == 
               _GET_HASH_MULTISET_CONTAINER(t_itersecond));

    return _hashtable_iterator_distance(t_iterfirst, t_itersecond);
}

bool_t _hash_multiset_iterator_before(
    hash_multiset_iterator_t t_iterfirst, hash_multiset_iterator_t t_itersecond)
{
    assert(_GET_HASH_MULTISET_CONTAINER_TYPE(t_iterfirst) == _HASH_MULTISET_CONTAINER &&
           _GET_HASH_MULTISET_ITERATOR_TYPE(t_iterfirst) == _FORWARD_ITERATOR &&
           _GET_HASH_MULTISET_CONTAINER_TYPE(t_itersecond) == _HASH_MULTISET_CONTAINER &&
           _GET_HASH_MULTISET_ITERATOR_TYPE(t_itersecond) == _FORWARD_ITERATOR &&
           _GET_HASH_MULTISET_CONTAINER(t_iterfirst) == 
               _GET_HASH_MULTISET_CONTAINER(t_itersecond));

    return _hashtable_iterator_before(t_iterfirst, t_itersecond);
}

/* hash_multiset private function */
hash_multiset_t* _create_hash_multiset(const char* s_typename)
{
    hash_multiset_t* pt_new_hash_multiset = NULL;

    if((pt_new_hash_multiset = (hash_multiset_t*)malloc(sizeof(hash_multiset_t))) == NULL)
    {
        return NULL;
    }

    if(!_create_hash_multiset_auxiliary(pt_new_hash_multiset, s_typename))
    {
        free(pt_new_hash_multiset);
        return NULL;
    }

    return pt_new_hash_multiset;
}

bool_t _create_hash_multiset_auxiliary(
    hash_multiset_t* pt_hash_multiset, const char* s_typename)
{
    assert(pt_hash_multiset != NULL && s_typename != NULL);

    return _create_hashtable_auxiliary(&pt_hash_multiset->_t_hashtable, s_typename);
}

void _hash_multiset_destroy_auxiliary(hash_multiset_t* pt_hash_multiset)
{
    assert(pt_hash_multiset != NULL);
    _hashtable_destroy_auxiliary(&pt_hash_multiset->_t_hashtable);
}

/* hash_multiset function */
void hash_multiset_init(hash_multiset_t* pt_hash_multiset)
{
    hash_multiset_init_ex(pt_hash_multiset, 0, NULL, NULL);
}

void hash_multiset_init_ex(hash_multiset_t* pt_hash_multiset, size_t t_bucketcount,
    unary_function_t t_hash, binary_function_t t_less)
{
    assert(pt_hash_multiset != NULL);

    _hashtable_init(&pt_hash_multiset->_t_hashtable, t_bucketcount, t_hash, t_less);
}

void hash_multiset_destroy(hash_multiset_t* pt_hash_multiset)
{
    _hash_multiset_destroy_auxiliary(pt_hash_multiset);
    free(pt_hash_multiset);
}

void hash_multiset_init_copy(
    hash_multiset_t* pt_hash_multisetdest, const hash_multiset_t* cpt_hash_multisetsrc)
{
    assert(pt_hash_multisetdest != NULL && cpt_hash_multisetsrc != NULL);

    _hashtable_init_copy(
        &pt_hash_multisetdest->_t_hashtable, &cpt_hash_multisetsrc->_t_hashtable);
}

void hash_multiset_init_copy_range(hash_multiset_t* pt_hash_multisetdest,
    hash_multiset_iterator_t t_begin, hash_multiset_iterator_t t_end)
{
    hash_multiset_init_copy_range_ex(
        pt_hash_multisetdest, t_begin, t_end, 0, NULL, NULL);
}

void hash_multiset_init_copy_range_ex(hash_multiset_t* pt_hash_multisetdest,
    hash_multiset_iterator_t t_begin, hash_multiset_iterator_t t_end,
    size_t t_bucketcount, unary_function_t t_hash, binary_function_t t_less)
{
    assert(pt_hash_multisetdest != NULL);
    assert(_GET_HASH_MULTISET_CONTAINER_TYPE(t_begin) == _HASH_MULTISET_CONTAINER &&
           _GET_HASH_MULTISET_ITERATOR_TYPE(t_begin) == _FORWARD_ITERATOR &&
           _GET_HASH_MULTISET_CONTAINER_TYPE(t_end) == _HASH_MULTISET_CONTAINER &&
           _GET_HASH_MULTISET_ITERATOR_TYPE(t_end) == _FORWARD_ITERATOR);
    assert(_GET_HASH_MULTISET_CONTAINER(t_begin) != pt_hash_multisetdest &&
           _GET_HASH_MULTISET_CONTAINER(t_end) != pt_hash_multisetdest &&
           _GET_HASH_MULTISET_CONTAINER(t_begin) ==
               _GET_HASH_MULTISET_CONTAINER(t_end));

    _hashtable_init_copy_range(&pt_hash_multisetdest->_t_hashtable, 
        t_begin, t_end, t_bucketcount, t_hash, t_less);
}

void hash_multiset_assign(
    hash_multiset_t* pt_hash_multisetdest, const hash_multiset_t* cpt_hash_multisetsrc)
{
    assert(pt_hash_multisetdest != NULL && cpt_hash_multisetsrc != NULL);

    _hashtable_assign(
        &pt_hash_multisetdest->_t_hashtable, &cpt_hash_multisetsrc->_t_hashtable);
}

void hash_multiset_swap(
    hash_multiset_t* pt_hash_multisetfirst, hash_multiset_t* pt_hash_multisetsecond)
{
    assert(pt_hash_multisetfirst != NULL && pt_hash_multisetsecond != NULL);

    _hashtable_swap(
        &pt_hash_multisetfirst->_t_hashtable, &pt_hash_multisetsecond->_t_hashtable);
}

size_t hash_multiset_size(const hash_multiset_t* cpt_hash_multiset)
{
    assert(cpt_hash_multiset != NULL);

    return _hashtable_size(&cpt_hash_multiset->_t_hashtable);
}

size_t hash_multiset_max_size(const hash_multiset_t* cpt_hash_multiset)
{
    assert(cpt_hash_multiset != NULL);

    return _hashtable_max_size(&cpt_hash_multiset->_t_hashtable);
}

bool_t hash_multiset_empty(const hash_multiset_t* cpt_hash_multiset)
{
    assert(cpt_hash_multiset != NULL);

    return _hashtable_empty(&cpt_hash_multiset->_t_hashtable);
}

size_t hash_multiset_bucket_count(const hash_multiset_t* cpt_hash_multiset)
{
    assert(cpt_hash_multiset != NULL);

    return _hashtable_bucket_count(&cpt_hash_multiset->_t_hashtable);
}

unary_function_t hash_multiset_hash(const hash_multiset_t* cpt_hash_multiset)
{
    assert(cpt_hash_multiset != NULL);

    return _hashtable_hash(&cpt_hash_multiset->_t_hashtable);
}

binary_function_t hash_multiset_key_less(const hash_multiset_t* cpt_hash_multiset)
{
    assert(cpt_hash_multiset != NULL);

    return _hashtable_key_less(&cpt_hash_multiset->_t_hashtable);
}

void hash_multiset_resize(hash_multiset_t* pt_hash_multiset, size_t t_resize)
{
    assert(pt_hash_multiset != NULL);

    _hashtable_resize(&pt_hash_multiset->_t_hashtable, t_resize);
}

bool_t hash_multiset_equal(
    const hash_multiset_t* cpt_hash_multisetfirst, 
    const hash_multiset_t* cpt_hash_multisetsecond)
{
    assert(cpt_hash_multisetfirst != NULL && cpt_hash_multisetsecond != NULL);

    return _hashtable_equal(
        &cpt_hash_multisetfirst->_t_hashtable, &cpt_hash_multisetsecond->_t_hashtable);
}

bool_t hash_multiset_not_equal(
    const hash_multiset_t* cpt_hash_multisetfirst, 
    const hash_multiset_t* cpt_hash_multisetsecond)
{
    assert(cpt_hash_multisetfirst != NULL && cpt_hash_multisetsecond != NULL);

    return _hashtable_not_equal(
        &cpt_hash_multisetfirst->_t_hashtable, &cpt_hash_multisetsecond->_t_hashtable);
}

bool_t hash_multiset_less(
    const hash_multiset_t* cpt_hash_multisetfirst,
    const hash_multiset_t* cpt_hash_multisetsecond)
{
    assert(cpt_hash_multisetfirst != NULL && cpt_hash_multisetsecond != NULL);

    return _hashtable_less(
        &cpt_hash_multisetfirst->_t_hashtable, &cpt_hash_multisetsecond->_t_hashtable);
}

bool_t hash_multiset_less_equal(
    const hash_multiset_t* cpt_hash_multisetfirst,
    const hash_multiset_t* cpt_hash_multisetsecond)
{
    assert(cpt_hash_multisetfirst != NULL && cpt_hash_multisetsecond != NULL);

    return _hashtable_less_equal(
        &cpt_hash_multisetfirst->_t_hashtable, &cpt_hash_multisetsecond->_t_hashtable);
}

bool_t hash_multiset_great(
    const hash_multiset_t* cpt_hash_multisetfirst,
    const hash_multiset_t* cpt_hash_multisetsecond)
{
    assert(cpt_hash_multisetfirst != NULL && cpt_hash_multisetsecond != NULL);

    return _hashtable_great(
        &cpt_hash_multisetfirst->_t_hashtable, &cpt_hash_multisetsecond->_t_hashtable);
}

bool_t hash_multiset_great_equal(
    const hash_multiset_t* cpt_hash_multisetfirst,
    const hash_multiset_t* cpt_hash_multisetsecond)
{
    assert(cpt_hash_multisetfirst != NULL && cpt_hash_multisetsecond != NULL);

    return _hashtable_great_equal(
        &cpt_hash_multisetfirst->_t_hashtable, &cpt_hash_multisetsecond->_t_hashtable);
}

hash_multiset_iterator_t hash_multiset_begin(const hash_multiset_t* cpt_hash_multiset)
{
    hash_multiset_iterator_t t_newiterator;

    assert(cpt_hash_multiset != NULL);

    t_newiterator = _hashtable_begin(&cpt_hash_multiset->_t_hashtable);

    _GET_CONTAINER(t_newiterator) = (hash_multiset_t*)cpt_hash_multiset;
    _GET_HASH_MULTISET_CONTAINER_TYPE(t_newiterator) = _HASH_MULTISET_CONTAINER;
    _GET_HASH_MULTISET_ITERATOR_TYPE(t_newiterator) = _FORWARD_ITERATOR;

    return t_newiterator;
}

hash_multiset_iterator_t hash_multiset_end(const hash_multiset_t* cpt_hash_multiset)
{
    hash_multiset_iterator_t t_newiterator;

    assert(cpt_hash_multiset != NULL);

    t_newiterator = _hashtable_end(&cpt_hash_multiset->_t_hashtable);

    _GET_CONTAINER(t_newiterator) = (hash_multiset_t*)cpt_hash_multiset;
    _GET_HASH_MULTISET_CONTAINER_TYPE(t_newiterator) = _HASH_MULTISET_CONTAINER;
    _GET_HASH_MULTISET_ITERATOR_TYPE(t_newiterator) = _FORWARD_ITERATOR;

    return t_newiterator;
}

hash_multiset_iterator_t _hash_multiset_find(
    const hash_multiset_t* cpt_hash_multiset, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, cpt_hash_multiset);
    return _hash_multiset_find_varg(cpt_hash_multiset, val_elemlist);
}

hash_multiset_iterator_t _hash_multiset_find_varg(
    const hash_multiset_t* cpt_hash_multiset, va_list val_elemlist)
{
    hash_multiset_iterator_t t_iter;
    void*                    pv_varg = NULL;

    assert(cpt_hash_multiset != NULL);

    pv_varg = allocate(&((hash_multiset_t*)cpt_hash_multiset)->_t_hashtable._t_allocater,
        _GET_HASH_MULTISET_TYPE_SIZE(cpt_hash_multiset), 1);
    assert(pv_varg != NULL);
    _hash_multiset_get_varg_value_auxiliary((hash_multiset_t*)cpt_hash_multiset,
        val_elemlist, pv_varg);

    t_iter = _hashtable_find(&cpt_hash_multiset->_t_hashtable, pv_varg);

    _hash_multiset_destroy_varg_value_auxiliary((hash_multiset_t*)cpt_hash_multiset, pv_varg);
    deallocate(&((hash_multiset_t*)cpt_hash_multiset)->_t_hashtable._t_allocater, pv_varg,
        _GET_HASH_MULTISET_TYPE_SIZE(cpt_hash_multiset), 1);

    _GET_CONTAINER(t_iter) = (hash_multiset_t*)cpt_hash_multiset;
    _GET_HASH_MULTISET_CONTAINER_TYPE(t_iter) = _HASH_MULTISET_CONTAINER;
    _GET_HASH_MULTISET_ITERATOR_TYPE(t_iter) = _FORWARD_ITERATOR;

    return t_iter;
}

size_t _hash_multiset_count(const hash_multiset_t* cpt_hash_multiset, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, cpt_hash_multiset);
    return _hash_multiset_count_varg(cpt_hash_multiset, val_elemlist);
}

size_t _hash_multiset_count_varg(
    const hash_multiset_t* cpt_hash_multiset, va_list val_elemlist)
{
    size_t t_count = 0;
    void*  pv_varg = NULL;

    assert(cpt_hash_multiset != NULL);

    pv_varg = allocate(&((hash_multiset_t*)cpt_hash_multiset)->_t_hashtable._t_allocater,
        _GET_HASH_MULTISET_TYPE_SIZE(cpt_hash_multiset), 1);
    assert(pv_varg != NULL);
    _hash_multiset_get_varg_value_auxiliary((hash_multiset_t*)cpt_hash_multiset,
        val_elemlist, pv_varg);

    t_count = _hashtable_count(&cpt_hash_multiset->_t_hashtable, pv_varg);

    _hash_multiset_destroy_varg_value_auxiliary((hash_multiset_t*)cpt_hash_multiset, pv_varg);
    deallocate(&((hash_multiset_t*)cpt_hash_multiset)->_t_hashtable._t_allocater, pv_varg,
        _GET_HASH_MULTISET_TYPE_SIZE(cpt_hash_multiset), 1);

    return t_count;
}

range_t _hash_multiset_equal_range(const hash_multiset_t* cpt_hash_multiset, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, cpt_hash_multiset);
    return _hash_multiset_equal_range_varg(cpt_hash_multiset, val_elemlist);
}

range_t _hash_multiset_equal_range_varg(
    const hash_multiset_t* cpt_hash_multiset, va_list val_elemlist)
{
    range_t t_range;
    void*   pv_varg = NULL;

    assert(cpt_hash_multiset != NULL);

    pv_varg = allocate(&((hash_multiset_t*)cpt_hash_multiset)->_t_hashtable._t_allocater,
        _GET_HASH_MULTISET_TYPE_SIZE(cpt_hash_multiset), 1);
    assert(pv_varg != NULL);
    _hash_multiset_get_varg_value_auxiliary((hash_multiset_t*)cpt_hash_multiset,
        val_elemlist, pv_varg);

    t_range = _hashtable_equal_range(&cpt_hash_multiset->_t_hashtable, pv_varg);

    _hash_multiset_destroy_varg_value_auxiliary((hash_multiset_t*)cpt_hash_multiset, pv_varg);
    deallocate(&((hash_multiset_t*)cpt_hash_multiset)->_t_hashtable._t_allocater, pv_varg,
        _GET_HASH_MULTISET_TYPE_SIZE(cpt_hash_multiset), 1);

    _GET_CONTAINER(t_range.t_begin) = (hash_multiset_t*)cpt_hash_multiset;
    _GET_HASH_MULTISET_CONTAINER_TYPE(t_range.t_begin) = _HASH_MULTISET_CONTAINER;
    _GET_HASH_MULTISET_ITERATOR_TYPE(t_range.t_begin) = _FORWARD_ITERATOR;

    _GET_CONTAINER(t_range.t_end) = (hash_multiset_t*)cpt_hash_multiset;
    _GET_HASH_MULTISET_CONTAINER_TYPE(t_range.t_end) = _HASH_MULTISET_CONTAINER;
    _GET_HASH_MULTISET_ITERATOR_TYPE(t_range.t_end) = _FORWARD_ITERATOR;

    return t_range;
}

hash_multiset_iterator_t _hash_multiset_insert(hash_multiset_t* pt_hash_multiset, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, pt_hash_multiset);
    return _hash_multiset_insert_varg(pt_hash_multiset, val_elemlist);
}

hash_multiset_iterator_t _hash_multiset_insert_varg(
    hash_multiset_t* pt_hash_multiset, va_list val_elemlist)
{
    hash_multiset_iterator_t t_iter;
    void*                    pv_varg = NULL;

    assert(pt_hash_multiset != NULL);

    pv_varg = allocate(&pt_hash_multiset->_t_hashtable._t_allocater,
        _GET_HASH_MULTISET_TYPE_SIZE(pt_hash_multiset), 1);
    assert(pv_varg != NULL);
    _hash_multiset_get_varg_value_auxiliary(pt_hash_multiset, val_elemlist, pv_varg);

    t_iter = _hashtable_insert_equal(&pt_hash_multiset->_t_hashtable, pv_varg);

    _hash_multiset_destroy_varg_value_auxiliary(pt_hash_multiset, pv_varg);
    deallocate(&pt_hash_multiset->_t_hashtable._t_allocater, pv_varg,
        _GET_HASH_MULTISET_TYPE_SIZE(pt_hash_multiset), 1);

    _GET_CONTAINER(t_iter) = pt_hash_multiset;
    _GET_HASH_MULTISET_CONTAINER_TYPE(t_iter) = _HASH_MULTISET_CONTAINER;
    _GET_HASH_MULTISET_ITERATOR_TYPE(t_iter) = _FORWARD_ITERATOR;

    return t_iter;
}

void hash_multiset_insert_range(hash_multiset_t* pt_hash_multiset, 
    hash_multiset_iterator_t t_begin, hash_multiset_iterator_t t_end)
{
    assert(pt_hash_multiset != NULL);
    assert(_GET_HASH_MULTISET_CONTAINER_TYPE(t_begin) == _HASH_MULTISET_CONTAINER &&
           _GET_HASH_MULTISET_ITERATOR_TYPE(t_begin) == _FORWARD_ITERATOR &&
           _GET_HASH_MULTISET_CONTAINER_TYPE(t_end) == _HASH_MULTISET_CONTAINER &&
           _GET_HASH_MULTISET_ITERATOR_TYPE(t_end) == _FORWARD_ITERATOR);
    assert(_GET_HASH_MULTISET_CONTAINER(t_begin) != pt_hash_multiset &&
           _GET_HASH_MULTISET_CONTAINER(t_end) != pt_hash_multiset &&
           _GET_HASH_MULTISET_CONTAINER(t_begin) == _GET_HASH_MULTISET_CONTAINER(t_end));

    _hashtable_insert_equal_range(&pt_hash_multiset->_t_hashtable, t_begin, t_end);
}

void hash_multiset_erase_pos(
    hash_multiset_t* pt_hash_multiset, hash_multiset_iterator_t t_pos)
{
    assert(pt_hash_multiset != NULL);
    assert(_GET_HASH_MULTISET_CONTAINER_TYPE(t_pos) == _HASH_MULTISET_CONTAINER &&
           _GET_HASH_MULTISET_ITERATOR_TYPE(t_pos) == _FORWARD_ITERATOR &&
           _GET_HASH_MULTISET_CONTAINER(t_pos) == pt_hash_multiset);

    _hashtable_erase_pos(&pt_hash_multiset->_t_hashtable, t_pos);
}

void hash_multiset_erase_range(
    hash_multiset_t* pt_hash_multiset,
    hash_multiset_iterator_t t_begin, hash_multiset_iterator_t t_end)
{
    assert(pt_hash_multiset != NULL);
    assert(_GET_HASH_MULTISET_CONTAINER_TYPE(t_begin) == _HASH_MULTISET_CONTAINER &&
           _GET_HASH_MULTISET_ITERATOR_TYPE(t_begin) == _FORWARD_ITERATOR &&
           _GET_HASH_MULTISET_CONTAINER_TYPE(t_end) == _HASH_MULTISET_CONTAINER &&
           _GET_HASH_MULTISET_ITERATOR_TYPE(t_end) == _FORWARD_ITERATOR);
    assert(_GET_HASH_MULTISET_CONTAINER(t_begin) == pt_hash_multiset &&
           _GET_HASH_MULTISET_CONTAINER(t_end) == pt_hash_multiset);

    _hashtable_erase_range(&pt_hash_multiset->_t_hashtable, t_begin, t_end);
}

size_t _hash_multiset_erase(hash_multiset_t* pt_hash_multiset, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, pt_hash_multiset);
    return _hash_multiset_erase_varg(pt_hash_multiset, val_elemlist);
}

size_t _hash_multiset_erase_varg(hash_multiset_t* pt_hash_multiset, va_list val_elemlist)
{
    size_t t_count = 0;
    void*  pv_varg = NULL;

    assert(pt_hash_multiset != NULL);

    pv_varg = allocate(&pt_hash_multiset->_t_hashtable._t_allocater,
        _GET_HASH_MULTISET_TYPE_SIZE(pt_hash_multiset), 1);
    assert(pv_varg != NULL);
    _hash_multiset_get_varg_value_auxiliary(pt_hash_multiset, val_elemlist, pv_varg);

    t_count = _hashtable_erase(&pt_hash_multiset->_t_hashtable, pv_varg);

    _hash_multiset_destroy_varg_value_auxiliary(pt_hash_multiset, pv_varg);
    deallocate(&pt_hash_multiset->_t_hashtable._t_allocater, pv_varg,
        _GET_HASH_MULTISET_TYPE_SIZE(pt_hash_multiset), 1);

    return t_count;
}

void hash_multiset_clear(hash_multiset_t* pt_hash_multiset)
{
    assert(pt_hash_multiset != NULL);

    _hashtable_clear(&pt_hash_multiset->_t_hashtable);
}

void _hash_multiset_init_elem_auxiliary(
    hash_multiset_t* pt_hash_multiset, void* pv_elem)
{
    assert(pt_hash_multiset != NULL && pv_elem != NULL);

    /* initialize new elements */
    if(_GET_HASH_MULTISET_TYPE_STYLE(pt_hash_multiset) == _TYPE_CSTL_BUILTIN)
    {
        /* get element type name */
        char s_elemtypename[_TYPE_NAME_SIZE + 1];
        _type_get_elem_typename(_GET_HASH_MULTISET_TYPE_NAME(pt_hash_multiset), s_elemtypename);

        _GET_HASH_MULTISET_TYPE_INIT_FUNCTION(pt_hash_multiset)(pv_elem, s_elemtypename);
    }
    else
    {
        bool_t t_result = _GET_HASH_MULTISET_TYPE_SIZE(pt_hash_multiset);
        _GET_HASH_MULTISET_TYPE_INIT_FUNCTION(pt_hash_multiset)(pv_elem, &t_result);
        assert(t_result);
    }
}

/** local function implementation section **/
static void _hash_multiset_get_varg_value_auxiliary(
    hash_multiset_t* pt_hash_multiset, va_list val_elemlist, void* pv_varg)
{
    _hash_multiset_init_elem_auxiliary(pt_hash_multiset, pv_varg);
    _type_get_varg_value(&pt_hash_multiset->_t_hashtable._t_typeinfo, val_elemlist, pv_varg);
}

static void _hash_multiset_destroy_varg_value_auxiliary(
    hash_multiset_t* pt_hash_multiset, void* pv_varg)
{
    /* destroy varg value and free memory */
    bool_t t_result = _GET_HASH_MULTISET_TYPE_SIZE(pt_hash_multiset);
    _GET_HASH_MULTISET_TYPE_DESTROY_FUNCTION(pt_hash_multiset)(pv_varg, &t_result);
    assert(t_result);
}

/** eof **/

