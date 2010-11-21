/*
 *  The implementation of hash_set.
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
#ifdef HAVE_CONFIG_H
#   include <config.h>
#endif
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include <cstl/cstl_alloc.h>
#include <cstl/cstl_types.h>
#include <cstl/cstl_iterator.h>
#include <cstl/cstl_iterator_private.h>

#include <cstl/cvector.h>
#include <cstl/cstl_hashtable_iterator.h>
#include <cstl/cstl_hashtable_private.h>

#include <cstl/cstl_hash_set_iterator.h>
#include <cstl/cstl_hash_set_private.h>
#include <cstl/cstl_hash_set.h>

/** local constant declaration and local macro section **/
/* macros for type informations */
#define _GET_HASH_SET_TYPE_SIZE(pt_hash_set)\
    ((pt_hash_set)->_t_hashtable._t_typeinfo._pt_type->_t_typesize)
#define _GET_HASH_SET_TYPE_NAME(pt_hash_set)\
    ((pt_hash_set)->_t_hashtable._t_typeinfo._sz_typename)
#define _GET_HASH_SET_TYPE_BASENAME(pt_hash_set)\
    ((pt_hash_set)->_t_hashtable._t_typeinfo._pt_type->_sz_typename)
#define _GET_HASH_SET_TYPE_INIT_FUNCTION(pt_hash_set)\
    ((pt_hash_set)->_t_hashtable._t_typeinfo._pt_type->_t_typeinit)
#define _GET_HASH_SET_TYPE_COPY_FUNCTION(pt_hash_set)\
    ((pt_hash_set)->_t_hashtable._t_typeinfo._pt_type->_t_typecopy)
#define _GET_HASH_SET_TYPE_LESS_FUNCTION(pt_hash_set)\
    ((pt_hash_set)->_t_hashtable._t_typeinfo._pt_type->_t_typeless)
#define _GET_HASH_SET_TYPE_DESTROY_FUNCTION(pt_hash_set)\
    ((pt_hash_set)->_t_hashtable._t_typeinfo._pt_type->_t_typedestroy)
#define _GET_HASH_SET_TYPE_STYLE(pt_hash_set)\
    ((pt_hash_set)->_t_hashtable._t_typeinfo._t_style)

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/
static void _hash_set_get_varg_value_auxiliary(
    hash_set_t* pt_hash_set, va_list val_elemlist, void* pv_varg);
static void _hash_set_destroy_varg_value_auxiliary(hash_set_t* pt_hash_set, void* pv_varg);

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/* hash_set iterator function */
hash_set_iterator_t create_hash_set_iterator(void)
{
    hash_set_iterator_t t_newiterator = _create_hashtable_iterator();

    _GET_HASH_SET_CONTAINER_TYPE(t_newiterator) = _HASH_SET_CONTAINER;
    _GET_HASH_SET_ITERATOR_TYPE(t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

void _hash_set_iterator_get_value(hash_set_iterator_t t_iter, void* pv_value)
{
    assert(pv_value != NULL);
    assert(_GET_HASH_SET_CONTAINER_TYPE(t_iter) == _HASH_SET_CONTAINER &&
           _GET_HASH_SET_ITERATOR_TYPE(t_iter) == _BIDIRECTIONAL_ITERATOR);

    _hashtable_iterator_get_value(t_iter, pv_value);
}

const void* _hash_set_iterator_get_pointer(hash_set_iterator_t t_iter)
{
    assert(_GET_HASH_SET_CONTAINER_TYPE(t_iter) == _HASH_SET_CONTAINER &&
           _GET_HASH_SET_ITERATOR_TYPE(t_iter) == _BIDIRECTIONAL_ITERATOR);

    return _hashtable_iterator_get_pointer(t_iter);
}

hash_set_iterator_t _hash_set_iterator_prev(hash_set_iterator_t t_iter)
{
    assert(_GET_HASH_SET_CONTAINER_TYPE(t_iter) == _HASH_SET_CONTAINER &&
           _GET_HASH_SET_ITERATOR_TYPE(t_iter) == _BIDIRECTIONAL_ITERATOR);

    return _hashtable_iterator_prev(t_iter);
}

hash_set_iterator_t _hash_set_iterator_next(hash_set_iterator_t t_iter)
{
    assert(_GET_HASH_SET_CONTAINER_TYPE(t_iter) == _HASH_SET_CONTAINER &&
           _GET_HASH_SET_ITERATOR_TYPE(t_iter) == _BIDIRECTIONAL_ITERATOR);

    return _hashtable_iterator_next(t_iter);
}

bool_t _hash_set_iterator_equal(
    hash_set_iterator_t t_iterfirst, hash_set_iterator_t t_itersecond)
{
    assert(_GET_HASH_SET_CONTAINER_TYPE(t_iterfirst) == _HASH_SET_CONTAINER &&
           _GET_HASH_SET_ITERATOR_TYPE(t_iterfirst) == _BIDIRECTIONAL_ITERATOR &&
           _GET_HASH_SET_CONTAINER_TYPE(t_itersecond) == _HASH_SET_CONTAINER &&
           _GET_HASH_SET_ITERATOR_TYPE(t_itersecond) == _BIDIRECTIONAL_ITERATOR);

    return _hashtable_iterator_equal(t_iterfirst, t_itersecond);
}

int _hash_set_iterator_distance(
    hash_set_iterator_t t_iterfirst, hash_set_iterator_t t_itersecond)
{
    assert(_GET_HASH_SET_CONTAINER_TYPE(t_iterfirst) == _HASH_SET_CONTAINER &&
           _GET_HASH_SET_ITERATOR_TYPE(t_iterfirst) == _BIDIRECTIONAL_ITERATOR &&
           _GET_HASH_SET_CONTAINER_TYPE(t_itersecond) == _HASH_SET_CONTAINER &&
           _GET_HASH_SET_ITERATOR_TYPE(t_itersecond) == _BIDIRECTIONAL_ITERATOR &&
           _GET_HASH_SET_CONTAINER(t_iterfirst) == _GET_HASH_SET_CONTAINER(t_itersecond));

    return _hashtable_iterator_distance(t_iterfirst, t_itersecond);
}

bool_t _hash_set_iterator_before(
    hash_set_iterator_t t_iterfirst, hash_set_iterator_t t_itersecond)
{
    assert(_GET_HASH_SET_CONTAINER_TYPE(t_iterfirst) == _HASH_SET_CONTAINER &&
           _GET_HASH_SET_ITERATOR_TYPE(t_iterfirst) == _BIDIRECTIONAL_ITERATOR &&
           _GET_HASH_SET_CONTAINER_TYPE(t_itersecond) == _HASH_SET_CONTAINER &&
           _GET_HASH_SET_ITERATOR_TYPE(t_itersecond) == _BIDIRECTIONAL_ITERATOR &&
           _GET_HASH_SET_CONTAINER(t_iterfirst) == 
               _GET_HASH_SET_CONTAINER(t_itersecond));

    return _hashtable_iterator_before(t_iterfirst, t_itersecond);
}

/* hash_set private function */
hash_set_t* _create_hash_set(const char* s_typename)
{
    hash_set_t* pt_new_hash_set = NULL;

    if((pt_new_hash_set = (hash_set_t*)malloc(sizeof(hash_set_t))) == NULL)
    {
        return NULL;
    }

    if(!_create_hash_set_auxiliary(pt_new_hash_set, s_typename))
    {
        free(pt_new_hash_set);
        return NULL;
    }

    return pt_new_hash_set;
}

bool_t _create_hash_set_auxiliary(hash_set_t* pt_hash_set, const char* s_typename)
{
    assert(pt_hash_set != NULL && s_typename != NULL);

    return _create_hashtable_auxiliary(&pt_hash_set->_t_hashtable, s_typename);
}

void _hash_set_destroy_auxiliary(hash_set_t* pt_hash_set)
{
    assert(pt_hash_set != NULL);

    _hashtable_destroy_auxiliary(&pt_hash_set->_t_hashtable);
}

/* hash_set function */
void hash_set_init(hash_set_t* pt_hash_set)
{
    hash_set_init_ex(pt_hash_set, 0, NULL, NULL);
}

void hash_set_init_ex(hash_set_t* pt_hash_set, size_t t_bucketcount,
    unary_function_t t_hash, binary_function_t t_compare)
{
    assert(pt_hash_set != NULL);

    _hashtable_init(&pt_hash_set->_t_hashtable, t_bucketcount, t_hash, t_compare);
}

void hash_set_destroy(hash_set_t* pt_hash_set)
{
    _hash_set_destroy_auxiliary(pt_hash_set);
    free(pt_hash_set);
}

void hash_set_init_copy(hash_set_t* pt_hash_setdest, const hash_set_t* cpt_hash_setsrc)
{
    assert(pt_hash_setdest != NULL && cpt_hash_setsrc != NULL);

    _hashtable_init_copy(&pt_hash_setdest->_t_hashtable, &cpt_hash_setsrc->_t_hashtable);
}

void hash_set_init_copy_range(hash_set_t* pt_hash_setdest,
    hash_set_iterator_t t_begin, hash_set_iterator_t t_end)
{
    hash_set_init_copy_range_ex(pt_hash_setdest, t_begin, t_end, 0, NULL, NULL);
}

void hash_set_init_copy_range_ex(hash_set_t* pt_hash_setdest,
    hash_set_iterator_t t_begin, hash_set_iterator_t t_end, size_t t_bucketcount,
    unary_function_t t_hash, binary_function_t t_compare)
{
    assert(pt_hash_setdest != NULL);
    assert(_GET_HASH_SET_CONTAINER_TYPE(t_begin) == _HASH_SET_CONTAINER &&
           _GET_HASH_SET_ITERATOR_TYPE(t_begin) == _BIDIRECTIONAL_ITERATOR &&
           _GET_HASH_SET_CONTAINER_TYPE(t_end) == _HASH_SET_CONTAINER &&
           _GET_HASH_SET_ITERATOR_TYPE(t_end) == _BIDIRECTIONAL_ITERATOR);
    assert(_GET_HASH_SET_CONTAINER(t_begin) != pt_hash_setdest &&
           _GET_HASH_SET_CONTAINER(t_end) != pt_hash_setdest &&
           _GET_HASH_SET_CONTAINER(t_begin) == _GET_HASH_SET_CONTAINER(t_end));

    _hashtable_init_copy_range(&pt_hash_setdest->_t_hashtable, t_begin, t_end,
        t_bucketcount, t_hash, t_compare);
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

unary_function_t hash_set_hash(const hash_set_t* cpt_hash_set)
{
    assert(cpt_hash_set != NULL);

    return _hashtable_hash(&cpt_hash_set->_t_hashtable);
}

binary_function_t hash_set_key_comp(const hash_set_t* cpt_hash_set)
{
    assert(cpt_hash_set != NULL);

    return _hashtable_key_comp(&cpt_hash_set->_t_hashtable);
}

binary_function_t hash_set_value_comp(const hash_set_t* cpt_hash_set)
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
    assert(cpt_hash_setfirst != NULL && cpt_hash_setsecond != NULL);

    return _hashtable_less(
        &cpt_hash_setfirst->_t_hashtable, &cpt_hash_setsecond->_t_hashtable);
}

bool_t hash_set_less_equal(
    const hash_set_t* cpt_hash_setfirst, const hash_set_t* cpt_hash_setsecond)
{
    assert(cpt_hash_setfirst != NULL && cpt_hash_setsecond != NULL);

    return _hashtable_less_equal(
        &cpt_hash_setfirst->_t_hashtable, &cpt_hash_setsecond->_t_hashtable);
}

bool_t hash_set_greater(
    const hash_set_t* cpt_hash_setfirst, const hash_set_t* cpt_hash_setsecond)
{
    assert(cpt_hash_setfirst != NULL && cpt_hash_setsecond != NULL);

    return _hashtable_greater(
        &cpt_hash_setfirst->_t_hashtable, &cpt_hash_setsecond->_t_hashtable);
}

bool_t hash_set_greater_equal(
    const hash_set_t* cpt_hash_setfirst, const hash_set_t* cpt_hash_setsecond)
{
    assert(cpt_hash_setfirst != NULL && cpt_hash_setsecond != NULL);

    return _hashtable_greater_equal(
        &cpt_hash_setfirst->_t_hashtable, &cpt_hash_setsecond->_t_hashtable);
}

hash_set_iterator_t hash_set_begin(const hash_set_t* cpt_hash_set)
{
    hash_set_iterator_t t_newiterator;

    assert(cpt_hash_set != NULL);

    t_newiterator = _hashtable_begin(&cpt_hash_set->_t_hashtable);

    _GET_CONTAINER(t_newiterator) = (hash_set_t*)cpt_hash_set;
    _GET_HASH_SET_CONTAINER_TYPE(t_newiterator) = _HASH_SET_CONTAINER;
    _GET_HASH_SET_ITERATOR_TYPE(t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

hash_set_iterator_t hash_set_end(const hash_set_t* cpt_hash_set)
{
    hash_set_iterator_t t_newiterator;

    assert(cpt_hash_set != NULL);

    t_newiterator = _hashtable_end(&cpt_hash_set->_t_hashtable);

    _GET_CONTAINER(t_newiterator) = (hash_set_t*)cpt_hash_set;
    _GET_HASH_SET_CONTAINER_TYPE(t_newiterator) = _HASH_SET_CONTAINER;
    _GET_HASH_SET_ITERATOR_TYPE(t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

hash_set_iterator_t _hash_set_find(const hash_set_t* cpt_hash_set, ...)
{
    hash_set_iterator_t t_iter;
    va_list val_elemlist;

    va_start(val_elemlist, cpt_hash_set);
    t_iter = _hash_set_find_varg(cpt_hash_set, val_elemlist);
    va_end(val_elemlist);

    return t_iter;
}

hash_set_iterator_t _hash_set_find_varg(
    const hash_set_t* cpt_hash_set, va_list val_elemlist)
{
    hash_set_iterator_t t_iter;
    void*               pv_varg = NULL;

    assert(cpt_hash_set != NULL);

    pv_varg = _alloc_allocate(&((hash_set_t*)cpt_hash_set)->_t_hashtable._t_allocater,
        _GET_HASH_SET_TYPE_SIZE(cpt_hash_set), 1);
    assert(pv_varg != NULL);
    _hash_set_get_varg_value_auxiliary((hash_set_t*)cpt_hash_set, val_elemlist, pv_varg);

    t_iter = _hashtable_find(&cpt_hash_set->_t_hashtable, pv_varg);

    _hash_set_destroy_varg_value_auxiliary((hash_set_t*)cpt_hash_set, pv_varg);
    _alloc_deallocate(&((hash_set_t*)cpt_hash_set)->_t_hashtable._t_allocater, pv_varg,
        _GET_HASH_SET_TYPE_SIZE(cpt_hash_set), 1);

    _GET_CONTAINER(t_iter) = (hash_set_t*)cpt_hash_set;
    _GET_HASH_SET_CONTAINER_TYPE(t_iter) = _HASH_SET_CONTAINER;
    _GET_HASH_SET_ITERATOR_TYPE(t_iter) = _BIDIRECTIONAL_ITERATOR;

    return t_iter;
}

size_t _hash_set_count(const hash_set_t* cpt_hash_set, ...)
{
    size_t t_count = 0;
    va_list val_elemlist;

    va_start(val_elemlist, cpt_hash_set);
    t_count = _hash_set_count_varg(cpt_hash_set, val_elemlist);
    va_end(val_elemlist);

    return t_count;
}

size_t _hash_set_count_varg(const hash_set_t* cpt_hash_set, va_list val_elemlist)
{
    size_t t_count = 0;
    void*  pv_varg = NULL;

    assert(cpt_hash_set != NULL);

    pv_varg = _alloc_allocate(&((hash_set_t*)cpt_hash_set)->_t_hashtable._t_allocater,
        _GET_HASH_SET_TYPE_SIZE(cpt_hash_set), 1);
    assert(pv_varg != NULL);
    _hash_set_get_varg_value_auxiliary((hash_set_t*)cpt_hash_set, val_elemlist, pv_varg);

    t_count = _hashtable_count(&cpt_hash_set->_t_hashtable, pv_varg);

    _hash_set_destroy_varg_value_auxiliary((hash_set_t*)cpt_hash_set, pv_varg);
    _alloc_deallocate(&((hash_set_t*)cpt_hash_set)->_t_hashtable._t_allocater, pv_varg,
        _GET_HASH_SET_TYPE_SIZE(cpt_hash_set), 1);

    return t_count;
}

range_t _hash_set_equal_range(const hash_set_t* cpt_hash_set, ...)
{
    range_t t_range;
    va_list val_elemlist;

    va_start(val_elemlist, cpt_hash_set);
    t_range = _hash_set_equal_range_varg(cpt_hash_set, val_elemlist);
    va_end(val_elemlist);

    return t_range;
}

range_t _hash_set_equal_range_varg(const hash_set_t* cpt_hash_set, va_list val_elemlist)
{
    range_t t_range;
    void*   pv_varg = NULL;

    assert(cpt_hash_set != NULL);

    pv_varg = _alloc_allocate(&((hash_set_t*)cpt_hash_set)->_t_hashtable._t_allocater,
        _GET_HASH_SET_TYPE_SIZE(cpt_hash_set), 1);
    assert(pv_varg != NULL);
    _hash_set_get_varg_value_auxiliary((hash_set_t*)cpt_hash_set, val_elemlist, pv_varg);

    t_range = _hashtable_equal_range(&cpt_hash_set->_t_hashtable, pv_varg);

    _hash_set_destroy_varg_value_auxiliary((hash_set_t*)cpt_hash_set, pv_varg);
    _alloc_deallocate(&((hash_set_t*)cpt_hash_set)->_t_hashtable._t_allocater, pv_varg,
        _GET_HASH_SET_TYPE_SIZE(cpt_hash_set), 1);

    _GET_CONTAINER(t_range.it_begin) = (hash_set_t*)cpt_hash_set;
    _GET_HASH_SET_CONTAINER_TYPE(t_range.it_begin) = _HASH_SET_CONTAINER;
    _GET_HASH_SET_ITERATOR_TYPE(t_range.it_begin) = _BIDIRECTIONAL_ITERATOR;

    _GET_CONTAINER(t_range.it_end) = (hash_set_t*)cpt_hash_set;
    _GET_HASH_SET_CONTAINER_TYPE(t_range.it_end) = _HASH_SET_CONTAINER;
    _GET_HASH_SET_ITERATOR_TYPE(t_range.it_end) = _BIDIRECTIONAL_ITERATOR;

    return t_range;
}

hash_set_iterator_t _hash_set_insert(hash_set_t* pt_hash_set, ...)
{
    hash_set_iterator_t t_iter;
    va_list val_elemlist;

    va_start(val_elemlist, pt_hash_set);
    t_iter = _hash_set_insert_varg(pt_hash_set, val_elemlist);
    va_end(val_elemlist);

    return t_iter;
}

hash_set_iterator_t _hash_set_insert_varg(hash_set_t* pt_hash_set, va_list val_elemlist)
{
    hash_set_iterator_t t_iter;
    void*               pv_varg = NULL;

    assert(pt_hash_set != NULL);

    pv_varg = _alloc_allocate(&pt_hash_set->_t_hashtable._t_allocater,
        _GET_HASH_SET_TYPE_SIZE(pt_hash_set), 1);
    assert(pv_varg != NULL);
    _hash_set_get_varg_value_auxiliary(pt_hash_set, val_elemlist, pv_varg);

    t_iter = _hashtable_insert_unique(&pt_hash_set->_t_hashtable, pv_varg);

    _hash_set_destroy_varg_value_auxiliary(pt_hash_set, pv_varg);
    _alloc_deallocate(&pt_hash_set->_t_hashtable._t_allocater, pv_varg,
        _GET_HASH_SET_TYPE_SIZE(pt_hash_set), 1);

    _GET_CONTAINER(t_iter) = pt_hash_set;
    _GET_HASH_SET_CONTAINER_TYPE(t_iter) = _HASH_SET_CONTAINER;
    _GET_HASH_SET_ITERATOR_TYPE(t_iter) = _BIDIRECTIONAL_ITERATOR;

    return t_iter;
}

void hash_set_insert_range(
    hash_set_t* pt_hash_set, hash_set_iterator_t t_begin, hash_set_iterator_t t_end)
{
    assert(pt_hash_set != NULL);
    assert(_GET_HASH_SET_CONTAINER_TYPE(t_begin) == _HASH_SET_CONTAINER &&
           _GET_HASH_SET_ITERATOR_TYPE(t_begin) == _BIDIRECTIONAL_ITERATOR &&
           _GET_HASH_SET_CONTAINER_TYPE(t_end) == _HASH_SET_CONTAINER &&
           _GET_HASH_SET_ITERATOR_TYPE(t_end) == _BIDIRECTIONAL_ITERATOR);
    assert(_GET_HASH_SET_CONTAINER(t_begin) != pt_hash_set &&
           _GET_HASH_SET_CONTAINER(t_end) != pt_hash_set &&
           _GET_HASH_SET_CONTAINER(t_begin) == _GET_HASH_SET_CONTAINER(t_end));

    _hashtable_insert_unique_range(&pt_hash_set->_t_hashtable, t_begin, t_end);
}

void hash_set_erase_pos(hash_set_t* pt_hash_set, hash_set_iterator_t t_pos)
{
    assert(pt_hash_set != NULL);
    assert(_GET_HASH_SET_CONTAINER_TYPE(t_pos) == _HASH_SET_CONTAINER &&
           _GET_HASH_SET_ITERATOR_TYPE(t_pos) == _BIDIRECTIONAL_ITERATOR &&
           _GET_HASH_SET_CONTAINER(t_pos) == pt_hash_set);

    _hashtable_erase_pos(&pt_hash_set->_t_hashtable, t_pos);
}

void hash_set_erase_range(
    hash_set_t* pt_hash_set, hash_set_iterator_t t_begin, hash_set_iterator_t t_end)
{
    assert(pt_hash_set != NULL);
    assert(_GET_HASH_SET_CONTAINER_TYPE(t_begin) == _HASH_SET_CONTAINER &&
           _GET_HASH_SET_ITERATOR_TYPE(t_begin) == _BIDIRECTIONAL_ITERATOR &&
           _GET_HASH_SET_CONTAINER_TYPE(t_end) == _HASH_SET_CONTAINER &&
           _GET_HASH_SET_ITERATOR_TYPE(t_end) == _BIDIRECTIONAL_ITERATOR);
    assert(_GET_HASH_SET_CONTAINER(t_begin) == pt_hash_set &&
           _GET_HASH_SET_CONTAINER(t_end) == pt_hash_set);

    _hashtable_erase_range(&pt_hash_set->_t_hashtable, t_begin, t_end);
}

size_t _hash_set_erase(hash_set_t* pt_hash_set, ...)
{
    size_t t_count = 0;
    va_list val_elemlist;

    va_start(val_elemlist, pt_hash_set);
    t_count = _hash_set_erase_varg(pt_hash_set, val_elemlist);
    va_end(val_elemlist);

    return t_count;
}

size_t _hash_set_erase_varg(hash_set_t* pt_hash_set, va_list val_elemlist)
{
    size_t  t_count = 0;
    void*   pv_varg = NULL;

    assert(pt_hash_set != NULL);

    pv_varg = _alloc_allocate(&pt_hash_set->_t_hashtable._t_allocater,
        _GET_HASH_SET_TYPE_SIZE(pt_hash_set), 1);
    assert(pv_varg != NULL);
    _hash_set_get_varg_value_auxiliary(pt_hash_set, val_elemlist, pv_varg);

    t_count = _hashtable_erase(&pt_hash_set->_t_hashtable, pv_varg);

    _hash_set_destroy_varg_value_auxiliary(pt_hash_set, pv_varg);
    _alloc_deallocate(&pt_hash_set->_t_hashtable._t_allocater, pv_varg,
        _GET_HASH_SET_TYPE_SIZE(pt_hash_set), 1);

    return t_count;
}

void hash_set_clear(hash_set_t* pt_hash_set)
{
    assert(pt_hash_set != NULL);

    _hashtable_clear(&pt_hash_set->_t_hashtable);
}

void _hash_set_init_elem_auxiliary(hash_set_t* pt_hash_set, void* pv_elem)
{
    assert(pt_hash_set != NULL && pv_elem != NULL);

    /* initialize new elements */
    if(_GET_HASH_SET_TYPE_STYLE(pt_hash_set) == _TYPE_CSTL_BUILTIN)
    {
        /* get element type name */
        char s_elemtypename[_TYPE_NAME_SIZE + 1];
        _type_get_elem_typename(_GET_HASH_SET_TYPE_NAME(pt_hash_set), s_elemtypename);

        _GET_HASH_SET_TYPE_INIT_FUNCTION(pt_hash_set)(pv_elem, s_elemtypename);
    }
    else
    {
        bool_t t_result = _GET_HASH_SET_TYPE_SIZE(pt_hash_set);
        _GET_HASH_SET_TYPE_INIT_FUNCTION(pt_hash_set)(pv_elem, &t_result);
        assert(t_result);
    }
}

/** local function implementation section **/
static void _hash_set_get_varg_value_auxiliary(
    hash_set_t* pt_hash_set, va_list val_elemlist, void* pv_varg)
{
    _hash_set_init_elem_auxiliary(pt_hash_set, pv_varg);
    _type_get_varg_value(&pt_hash_set->_t_hashtable._t_typeinfo, val_elemlist, pv_varg);
}

static void _hash_set_destroy_varg_value_auxiliary(hash_set_t* pt_hash_set, void* pv_varg)
{
    /* destroy varg value and free memory */
    bool_t t_result = _GET_HASH_SET_TYPE_SIZE(pt_hash_set);
    _GET_HASH_SET_TYPE_DESTROY_FUNCTION(pt_hash_set)(pv_varg, &t_result);
    assert(t_result);
}

/** eof **/

