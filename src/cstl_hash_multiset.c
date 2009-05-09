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

#include "cstl_types.h"
#include "cstl_alloc.h"
#include "cstl_iterator.h"
#include "cstl_iterator_private.h"

#include "cvector.h"
#include "cstl_hashtable_iterator.h"
#include "cstl_hashtable_private.h"
#include "cutility.h"

#include "cstl_hash_multiset_iterator.h"
#include "cstl_hash_multiset_private.h"
#include "cstl_hash_multiset.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

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
hash_multiset_t _create_hash_multiset(size_t t_typesize, const char* s_typename)
{
    hash_multiset_t t_new_hash_multiset;
    char            ac_hashmultisettypename[_ELEM_TYPE_NAME_SIZE+1];
    char            ac_unifytypename[_ELEM_TYPE_NAME_SIZE+1];

    assert(s_typename != NULL);

    memset(ac_unifytypename, '\0', _ELEM_TYPE_NAME_SIZE+1);
    strncpy(ac_unifytypename, s_typename, _ELEM_TYPE_NAME_SIZE);
    _unify_types(t_typesize, ac_unifytypename);
    
    memset(ac_hashmultisettypename, '\0', _ELEM_TYPE_NAME_SIZE+1);
    strncpy(ac_hashmultisettypename, _HASH_MULTISET_IDENTIFY, _ELEM_TYPE_NAME_SIZE);
    strcat(ac_hashmultisettypename, _HASH_MULTISET_LEFT_BRACKET);
    strcat(ac_hashmultisettypename, ac_unifytypename);
    strcat(ac_hashmultisettypename, _HASH_MULTISET_RIGHT_BRACKET);

    t_new_hash_multiset._t_hashtable = 
        _create_hashtable(t_typesize, ac_hashmultisettypename);

    return t_new_hash_multiset;
}

/* hash_multiset function */
void hash_multiset_init(
    hash_multiset_t* pt_hash_multiset,int (*pfun_hash)(const void*, size_t, size_t))
{
    hash_multiset_init_n(pt_hash_multiset, 0, pfun_hash);
}

void hash_multiset_init_n(
    hash_multiset_t* pt_hash_multiset, size_t t_bucketcount,
    int (*pfun_hash)(const void*, size_t, size_t))
{
    assert(pt_hash_multiset != NULL);

    _hashtable_init(
        &pt_hash_multiset->_t_hashtable, t_bucketcount, pfun_hash, NULL, NULL);
}

void hash_multiset_destroy(hash_multiset_t* pt_hash_multiset)
{
    assert(pt_hash_multiset != NULL);

    _hashtable_destroy(&pt_hash_multiset->_t_hashtable);
}

void hash_multiset_init_copy(
    hash_multiset_t* pt_hash_multisetdest, const hash_multiset_t* cpt_hash_multisetsrc)
{
    assert(pt_hash_multisetdest != NULL && cpt_hash_multisetsrc != NULL);

    _hashtable_init_copy(
        &pt_hash_multisetdest->_t_hashtable, &cpt_hash_multisetsrc->_t_hashtable);
}

void hash_multiset_init_copy_range(
    hash_multiset_t* pt_hash_multisetdest, hash_multiset_iterator_t t_begin,
    hash_multiset_iterator_t t_end, int (*pfun_hash)(const void*, size_t, size_t))
{
    hash_multiset_init_copy_range_n(
        pt_hash_multisetdest, t_begin, t_end, 0, pfun_hash);
}

void hash_multiset_init_copy_range_n(
    hash_multiset_t* pt_hash_multisetdest, hash_multiset_iterator_t t_begin,
    hash_multiset_iterator_t t_end, size_t t_bucketcount,
    int (*pfun_hash)(const void*, size_t, size_t))
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
        t_begin, t_end, t_bucketcount, pfun_hash, NULL);
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

int (*hash_multiset_hash_func(const hash_multiset_t* cpt_hash_multiset))(
    const void*, size_t, size_t)
{
    assert(cpt_hash_multiset != NULL);

    return _hashtable_hash_func(&cpt_hash_multiset->_t_hashtable);
}

int (*hash_multiset_key_comp(const hash_multiset_t* cpt_hash_multiset))(
    const void*, const void*)
{
    assert(cpt_hash_multiset != NULL);

    return _hashtable_key_comp(&cpt_hash_multiset->_t_hashtable);
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
    hash_multiset_iterator_t t_newiterator;
    char*                    pc_value = NULL;

    assert(cpt_hash_multiset != NULL);

    pc_value = (char*)malloc(cpt_hash_multiset->_t_hashtable._t_typesize);
    if(pc_value == NULL)
    {
        fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        memset(pc_value, 0x00, cpt_hash_multiset->_t_hashtable._t_typesize);
        _get_varg_value(
            pc_value, val_elemlist, cpt_hash_multiset->_t_hashtable._t_typesize,
            cpt_hash_multiset->_t_hashtable._sz_typename);
    }

    t_newiterator = _hashtable_find(&cpt_hash_multiset->_t_hashtable, pc_value);
    free(pc_value);
    pc_value = NULL;

    _GET_CONTAINER(t_newiterator) = (hash_multiset_t*)cpt_hash_multiset;
    _GET_HASH_MULTISET_CONTAINER_TYPE(t_newiterator) = _HASH_MULTISET_CONTAINER;
    _GET_HASH_MULTISET_ITERATOR_TYPE(t_newiterator) = _FORWARD_ITERATOR;

    return t_newiterator;
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
    size_t  t_countsize = 0;
    char*   pc_value = NULL;

    assert(cpt_hash_multiset != NULL);

    pc_value = (char*)malloc(cpt_hash_multiset->_t_hashtable._t_typesize);
    if(pc_value == NULL)
    {
        fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        memset(pc_value, 0x00, cpt_hash_multiset->_t_hashtable._t_typesize);
        _get_varg_value(
            pc_value, val_elemlist, cpt_hash_multiset->_t_hashtable._t_typesize,
            cpt_hash_multiset->_t_hashtable._sz_typename);
    }

    t_countsize = _hashtable_count(&cpt_hash_multiset->_t_hashtable, pc_value);
    free(pc_value);
    pc_value = NULL;

    return t_countsize;
}

pair_t _hash_multiset_equal_range(const hash_multiset_t* cpt_hash_multiset, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, cpt_hash_multiset);
    return _hash_multiset_equal_range_varg(cpt_hash_multiset, val_elemlist);
}

pair_t _hash_multiset_equal_range_varg(
    const hash_multiset_t* cpt_hash_multiset, va_list val_elemlist)
{
    hash_multiset_iterator_t t_firstiterator;
    hash_multiset_iterator_t t_seconditerator;
    hashtable_result_pair_t  t_result;
    char*                    pc_value = NULL;
    pair_t                   t_pair;

    assert(cpt_hash_multiset != NULL);

    pc_value = (char*)malloc(cpt_hash_multiset->_t_hashtable._t_typesize);
    if(pc_value == NULL)
    {
        fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        memset(pc_value, 0x00, cpt_hash_multiset->_t_hashtable._t_typesize);
        _get_varg_value(
            pc_value, val_elemlist, cpt_hash_multiset->_t_hashtable._t_typesize,
            cpt_hash_multiset->_t_hashtable._sz_typename);
    }

    t_result = _hashtable_equal_range(&cpt_hash_multiset->_t_hashtable, pc_value);
    free(pc_value);
    pc_value = NULL;

    t_firstiterator = t_result._t_first;
    _GET_CONTAINER(t_firstiterator) = (hash_multiset_t*)cpt_hash_multiset;
    _GET_HASH_MULTISET_CONTAINER_TYPE(t_firstiterator) = _HASH_MULTISET_CONTAINER;
    _GET_HASH_MULTISET_ITERATOR_TYPE(t_firstiterator) = _FORWARD_ITERATOR;

    t_seconditerator = t_result._t_second._t_iterator;
    _GET_CONTAINER(t_seconditerator) = (hash_multiset_t*)cpt_hash_multiset;
    _GET_HASH_MULTISET_CONTAINER_TYPE(t_seconditerator) = _HASH_MULTISET_CONTAINER;
    _GET_HASH_MULTISET_ITERATOR_TYPE(t_seconditerator) = _FORWARD_ITERATOR;

    t_pair = create_pair(hash_multiset_iterator_t, hash_multiset_iterator_t);
    pair_init(&t_pair);
    memcpy(t_pair.first, &t_firstiterator, t_pair._t_firsttypesize);
    memcpy(t_pair.second, &t_seconditerator, t_pair._t_secondtypesize);

    return t_pair;
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
    hash_multiset_iterator_t t_iterator;
    char*                    pc_value;

    assert(pt_hash_multiset != NULL);

    pc_value = (char*)malloc(pt_hash_multiset->_t_hashtable._t_typesize);
    if(pc_value == NULL)
    {
        fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        memset(pc_value, 0x00, pt_hash_multiset->_t_hashtable._t_typesize);
        _get_varg_value(
            pc_value, val_elemlist, pt_hash_multiset->_t_hashtable._t_typesize,
            pt_hash_multiset->_t_hashtable._sz_typename);
    }

    t_iterator = _hashtable_insert_equal(&pt_hash_multiset->_t_hashtable, pc_value);
    free(pc_value);
    pc_value = NULL;

    _GET_CONTAINER(t_iterator) = pt_hash_multiset;
    _GET_HASH_MULTISET_CONTAINER_TYPE(t_iterator) = _HASH_MULTISET_CONTAINER;
    _GET_HASH_MULTISET_ITERATOR_TYPE(t_iterator) = _FORWARD_ITERATOR;

    return t_iterator;
}

void hash_multiset_insert_range(
    hash_multiset_t* pt_hash_multiset, 
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
    size_t  t_countsize = 0;
    char*   pc_value = NULL;

    assert(pt_hash_multiset != NULL);

    pc_value = (char*)malloc(pt_hash_multiset->_t_hashtable._t_typesize);
    if(pc_value == NULL)
    {
        fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        memset(pc_value, 0x00, pt_hash_multiset->_t_hashtable._t_typesize);
        _get_varg_value(
            pc_value, val_elemlist, pt_hash_multiset->_t_hashtable._t_typesize,
            pt_hash_multiset->_t_hashtable._sz_typename);
    }

    t_countsize = _hashtable_erase(&pt_hash_multiset->_t_hashtable, pc_value);
    free(pc_value);
    pc_value = NULL;

    return t_countsize;
}

void hash_multiset_clear(hash_multiset_t* pt_hash_multiset)
{
    assert(pt_hash_multiset != NULL);

    _hashtable_clear(&pt_hash_multiset->_t_hashtable);
}

/** local function implementation section **/

/** eof **/

