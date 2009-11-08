/*
 *  The implementation of hash_map.
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
#include "cstring.h"

#include "cstl_hash_map_iterator.h"
#include "cstl_hash_map_private.h"
#include "cstl_hash_map.h"

/** local constant declaration and local macro section **/
/* macros for type informations */
#define _GET_HASH_MAP_FIRST_TYPE_SIZE(pt_hash_map)\
    ((pt_hash_map)->_t_pair._t_typeinfofirst._pt_type->_t_typesize)
#define _GET_HASH_MAP_FIRST_TYPE_NAME(pt_hash_map)\
    ((pt_hash_map)->_t_pair._t_typeinfofirst._sz_typename)
#define _GET_HASH_MAP_FIRST_TYPE_BASENAME(pt_hash_map)\
    ((pt_hash_map)->_t_pair._t_typeinfofirst._pt_type->_sz_typename)
#define _GET_HASH_MAP_FIRST_TYPE_INIT_FUNCTION(pt_hash_map)\
    ((pt_hash_map)->_t_pair._t_typeinfofirst._pt_type->_t_typeinit)
#define _GET_HASH_MAP_FIRST_TYPE_COPY_FUNCTION(pt_hash_map)\
    ((pt_hash_map)->_t_pair._t_typeinfofirst._pt_type->_t_typecopy)
#define _GET_HASH_MAP_FIRST_TYPE_LESS_FUNCTION(pt_hash_map)\
    ((pt_hash_map)->_t_pair._t_typeinfofirst._pt_type->_t_typeless)
#define _GET_HASH_MAP_FIRST_TYPE_DESTROY_FUNCTION(pt_hash_map)\
    ((pt_hash_map)->_t_pair._t_typeinfofirst._pt_type->_t_typedestroy)
#define _GET_HASH_MAP_FIRST_TYPE_STYLE(pt_hash_map)\
    ((pt_hash_map)->_t_pair._t_typeinfofirst._t_style)

#define _GET_HASH_MAP_SECOND_TYPE_SIZE(pt_hash_map)\
    ((pt_hash_map)->_t_pair._t_typeinfosecond._pt_type->_t_typesize)
#define _GET_HASH_MAP_SECOND_TYPE_NAME(pt_hash_map)\
    ((pt_hash_map)->_t_pair._t_typeinfosecond._sz_typename)
#define _GET_HASH_MAP_SECOND_TYPE_BASENAME(pt_hash_map)\
    ((pt_hash_map)->_t_pair._t_typeinfosecond._pt_type->_sz_typename)
#define _GET_HASH_MAP_SECOND_TYPE_INIT_FUNCTION(pt_hash_map)\
    ((pt_hash_map)->_t_pair._t_typeinfosecond._pt_type->_t_typeinit)
#define _GET_HASH_MAP_SECOND_TYPE_COPY_FUNCTION(pt_hash_map)\
    ((pt_hash_map)->_t_pair._t_typeinfosecond._pt_type->_t_typecopy)
#define _GET_HASH_MAP_SECOND_TYPE_LESS_FUNCTION(pt_hash_map)\
    ((pt_hash_map)->_t_pair._t_typeinfosecond._pt_type->_t_typeless)
#define _GET_HASH_MAP_SECOND_TYPE_DESTROY_FUNCTION(pt_hash_map)\
    ((pt_hash_map)->_t_pair._t_typeinfosecond._pt_type->_t_typedestroy)
#define _GET_HASH_MAP_SECOND_TYPE_STYLE(pt_hash_map)\
    ((pt_hash_map)->_t_pair._t_typeinfosecond._t_style)

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/
#ifndef NDEBUG
/*
 * Assert support.
 */
static bool_t _hash_map_same_pair_type(
    const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond);
#endif /* NDEBUG */

static void _hash_map_key_less(const void* cpv_first, const void* cpv_second, void* pv_output);

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/* hash_map iterator function */
hash_map_iterator_t create_hash_map_iterator(void)
{
    hash_map_iterator_t t_newiterator = _create_hashtable_iterator();

    _GET_HASH_MAP_CONTAINER_TYPE(t_newiterator) = _HASH_MAP_CONTAINER;
    _GET_HASH_MAP_ITERATOR_TYPE(t_newiterator) = _FORWARD_ITERATOR;

    return t_newiterator;
}

void _hash_map_iterator_get_value(hash_map_iterator_t t_iter, void* pv_value)
{
    assert(pv_value != NULL);
    assert(_GET_HASH_MAP_CONTAINER_TYPE(t_iter) == _HASH_MAP_CONTAINER &&
           _GET_HASH_MAP_ITERATOR_TYPE(t_iter) == _FORWARD_ITERATOR);

    _hashtable_iterator_get_value(t_iter, pv_value);
}

const void* _hash_map_iterator_get_pointer(hash_map_iterator_t t_iter)
{
    assert(_GET_HASH_MAP_CONTAINER_TYPE(t_iter) == _HASH_MAP_CONTAINER &&
           _GET_HASH_MAP_ITERATOR_TYPE(t_iter) == _FORWARD_ITERATOR);

    return _hashtable_iterator_get_pointer(t_iter);
}

hash_map_iterator_t _hash_map_iterator_next(hash_map_iterator_t t_iter)
{
    assert(_GET_HASH_MAP_CONTAINER_TYPE(t_iter) == _HASH_MAP_CONTAINER &&
           _GET_HASH_MAP_ITERATOR_TYPE(t_iter) == _FORWARD_ITERATOR);

    return _hashtable_iterator_next(t_iter);
}

bool_t _hash_map_iterator_equal(
    hash_map_iterator_t t_iterfirst, hash_map_iterator_t t_itersecond)
{
    assert(_GET_HASH_MAP_CONTAINER_TYPE(t_iterfirst) == _HASH_MAP_CONTAINER &&
           _GET_HASH_MAP_ITERATOR_TYPE(t_iterfirst) == _FORWARD_ITERATOR &&
           _GET_HASH_MAP_CONTAINER_TYPE(t_itersecond) == _HASH_MAP_CONTAINER &&
           _GET_HASH_MAP_ITERATOR_TYPE(t_itersecond) == _FORWARD_ITERATOR);

    return _hashtable_iterator_equal(t_iterfirst, t_itersecond);
}

int _hash_map_iterator_distance(
    hash_map_iterator_t t_iterfirst, hash_map_iterator_t t_itersecond)
{
    assert(_GET_HASH_MAP_CONTAINER_TYPE(t_iterfirst) == _HASH_MAP_CONTAINER &&
           _GET_HASH_MAP_ITERATOR_TYPE(t_iterfirst) == _FORWARD_ITERATOR &&
           _GET_HASH_MAP_CONTAINER_TYPE(t_itersecond) == _HASH_MAP_CONTAINER &&
           _GET_HASH_MAP_ITERATOR_TYPE(t_itersecond) == _FORWARD_ITERATOR &&
           _GET_HASH_MAP_CONTAINER(t_iterfirst) == _GET_HASH_MAP_CONTAINER(t_itersecond));

    return _hashtable_iterator_distance(t_iterfirst, t_itersecond);
}

bool_t _hash_map_iterator_before(
    hash_map_iterator_t t_iterfirst, hash_map_iterator_t t_itersecond)
{
    assert(_GET_HASH_MAP_CONTAINER_TYPE(t_iterfirst) == _HASH_MAP_CONTAINER &&
           _GET_HASH_MAP_ITERATOR_TYPE(t_iterfirst) == _FORWARD_ITERATOR &&
           _GET_HASH_MAP_CONTAINER_TYPE(t_itersecond) == _HASH_MAP_CONTAINER &&
           _GET_HASH_MAP_ITERATOR_TYPE(t_itersecond) == _FORWARD_ITERATOR &&
           _GET_HASH_MAP_CONTAINER(t_iterfirst) == 
               _GET_HASH_MAP_CONTAINER(t_itersecond));

    return _hashtable_iterator_before(t_iterfirst, t_itersecond);
}

/* hash_map private function */
hash_map_t* _create_hash_map(const char* s_typename)
{
    hash_map_t* pt_new_hash_map = NULL;

    if((pt_new_hash_map = (hash_map_t*)malloc(sizeof(hash_map_t))) == NULL)
    {
        return NULL;
    }

    if(!_create_hash_map_auxiliary(pt_new_hash_map, s_typename))
    {
        free(pt_new_hash_map);
        return NULL;
    }

    return pt_new_hash_map;
}

bool_t _create_hash_map_auxiliary(hash_map_t* pt_hash_map, const char* s_typename)
{
    char s_typenameex[_TYPE_NAME_SIZE + 1];

    assert(pt_hash_map != NULL && s_typename != NULL);

    if(!_create_pair_auxiliary(&pt_hash_map->_t_pair, s_typename))
    {
        return false;
    }

    memset(s_typenameex, '\0', _TYPE_NAME_SIZE + 1);
    strncpy(s_typenameex, "pair_t", _TYPE_NAME_SIZE);
    strncat(s_typenameex, "<", _TYPE_NAME_SIZE);
    strncat(s_typenameex, s_typename, _TYPE_NAME_SIZE - 8); /* 8 is length of "pair_t<>" */
    strncat(s_typenameex, ">", _TYPE_NAME_SIZE);

    return _create_hashtable_auxiliary(&pt_hash_map->_t_hashtable, s_typenameex);
}

void _hash_map_destroy_auxiliary(hash_map_t* pt_hash_map)
{
    assert(pt_hash_map != NULL);

    _pair_destroy_auxiliary(&pt_hash_map->_t_pair);
    _hashtable_destroy_auxiliary(&pt_hash_map->_t_hashtable);
}

/* hash_map function */
void hash_map_init(hash_map_t* pt_hash_map)
{
    hash_map_init_ex(pt_hash_map, 0, NULL, NULL);
}

void hash_map_init_ex(hash_map_t* pt_hash_map, size_t t_bucketcount,
    unary_function_t t_hash, binary_function_t t_less)
{
    binary_function_t t_key_less = NULL;

    assert(pt_hash_map != NULL);

    t_key_less = t_less != NULL ? t_less : _hash_map_key_less;
    /* initialize the pair */
    pair_init(&pt_hash_map->_t_pair);
    /* initialize the hashtable */
    _hashtable_init(&pt_hash_map->_t_hashtable, t_bucketcount, t_hash, t_key_less);
}

void hash_map_destroy(hash_map_t* pt_hash_map)
{
    _hash_map_destroy_auxiliary(pt_hash_map);
    free(pt_hash_map);
}

void hash_map_init_copy(hash_map_t* pt_hash_mapdest, const hash_map_t* cpt_hash_mapsrc)
{
    assert(pt_hash_mapdest != NULL && cpt_hash_mapsrc != NULL);
    assert(_hash_map_same_pair_type(&pt_hash_mapdest->_t_pair, &cpt_hash_mapsrc->_t_pair));

    hash_map_init(pt_hash_mapdest);
    if(!hash_map_empty(cpt_hash_mapsrc))
    {
        hash_map_insert_range(pt_hash_mapdest, 
            hash_map_begin(cpt_hash_mapsrc), hash_map_end(cpt_hash_mapsrc));
    }
}

void hash_map_init_copy_range(hash_map_t* pt_hash_mapdest,
    hash_map_iterator_t t_begin, hash_map_iterator_t t_end)
{
    hash_map_init_copy_range_ex(pt_hash_mapdest, t_begin, t_end, 0, NULL, NULL);
}

void hash_map_init_copy_range_ex(hash_map_t* pt_hash_mapdest,
    hash_map_iterator_t t_begin, hash_map_iterator_t t_end, size_t t_bucketcount,
    unary_function_t t_hash, binary_function_t t_less)
{
    assert(pt_hash_mapdest != NULL);
    assert(_GET_HASH_MAP_CONTAINER_TYPE(t_begin) == _HASH_MAP_CONTAINER &&
           _GET_HASH_MAP_ITERATOR_TYPE(t_begin) == _FORWARD_ITERATOR &&
           _GET_HASH_MAP_CONTAINER_TYPE(t_end) == _HASH_MAP_CONTAINER &&
           _GET_HASH_MAP_ITERATOR_TYPE(t_end) == _FORWARD_ITERATOR);
    assert(_GET_HASH_MAP_CONTAINER(t_begin) != pt_hash_mapdest &&
           _GET_HASH_MAP_CONTAINER(t_end) != pt_hash_mapdest &&
           _GET_HASH_MAP_CONTAINER(t_begin) == _GET_HASH_MAP_CONTAINER(t_end));

    hash_map_init_ex(pt_hash_mapdest, t_bucketcount, t_hash, t_less);
    if(!hash_map_empty(_GET_HASH_MAP_CONTAINER(t_begin)))
    {
        hash_map_insert_range(pt_hash_mapdest, t_begin, t_end);
    }
}

void hash_map_assign(hash_map_t* pt_hash_mapdest, const hash_map_t* cpt_hash_mapsrc)
{
    assert(pt_hash_mapdest != NULL && cpt_hash_mapsrc != NULL);
    assert(_hash_map_same_pair_type(
        &pt_hash_mapdest->_t_pair, &cpt_hash_mapsrc->_t_pair));

    hash_map_clear(pt_hash_mapdest);
    if(!hash_map_empty(cpt_hash_mapsrc))
    {
        hash_map_insert_range(pt_hash_mapdest,
            hash_map_begin(cpt_hash_mapsrc), hash_map_end(cpt_hash_mapsrc));
    }
}

void hash_map_swap(
    hash_map_t* pt_hash_mapfirst, hash_map_t* pt_hash_mapsecond)
{
    assert(pt_hash_mapfirst != NULL && pt_hash_mapsecond != NULL);
    assert(_hash_map_same_pair_type(&pt_hash_mapfirst->_t_pair,
        &pt_hash_mapsecond->_t_pair));

    _hashtable_swap(&pt_hash_mapfirst->_t_hashtable, &pt_hash_mapsecond->_t_hashtable);
}

size_t hash_map_size(const hash_map_t* cpt_hash_map)
{
    assert(cpt_hash_map != NULL);

    return _hashtable_size(&cpt_hash_map->_t_hashtable);
}

bool_t hash_map_empty(const hash_map_t* cpt_hash_map)
{
    assert(cpt_hash_map != NULL);

    return _hashtable_empty(&cpt_hash_map->_t_hashtable);
}

size_t hash_map_max_size(const hash_map_t* cpt_hash_map)
{
    assert(cpt_hash_map != NULL);

    return _hashtable_max_size(&cpt_hash_map->_t_hashtable);
}

size_t hash_map_bucket_count(const hash_map_t* cpt_hash_map)
{
    assert(cpt_hash_map != NULL);

    return _hashtable_bucket_count(&cpt_hash_map->_t_hashtable);
}

unary_function_t hash_map_hash(const hash_map_t* cpt_hash_map)
{
    assert(cpt_hash_map != NULL);

    return _hashtable_hash(&cpt_hash_map->_t_hashtable);
}

binary_function_t hash_map_key_less(const hash_map_t* cpt_hash_map)
{
    assert(cpt_hash_map != NULL);

    return _hashtable_key_less(&cpt_hash_map->_t_hashtable);
}

void hash_map_resize(hash_map_t* pt_hash_map, size_t t_resize)
{
    assert(pt_hash_map != NULL);

    _hashtable_resize(&pt_hash_map->_t_hashtable, t_resize);
}

hash_map_iterator_t hash_map_begin(const hash_map_t* cpt_hash_map)
{
    hash_map_iterator_t t_newiterator;

    assert(cpt_hash_map != NULL);

    t_newiterator = _hashtable_begin(&cpt_hash_map->_t_hashtable);

    _GET_CONTAINER(t_newiterator) = (hash_map_t*)cpt_hash_map;
    _GET_HASH_MAP_CONTAINER_TYPE(t_newiterator) = _HASH_MAP_CONTAINER;
    _GET_HASH_MAP_ITERATOR_TYPE(t_newiterator) = _FORWARD_ITERATOR;

    return t_newiterator;
}

hash_map_iterator_t hash_map_end(const hash_map_t* cpt_hash_map)
{
    hash_map_iterator_t t_newiterator;

    assert(cpt_hash_map != NULL);

    t_newiterator = _hashtable_end(&cpt_hash_map->_t_hashtable);

    _GET_CONTAINER(t_newiterator) = (hash_map_t*)cpt_hash_map;
    _GET_HASH_MAP_CONTAINER_TYPE(t_newiterator) = _HASH_MAP_CONTAINER;
    _GET_HASH_MAP_ITERATOR_TYPE(t_newiterator) = _FORWARD_ITERATOR;

    return t_newiterator;
}

bool_t hash_map_equal(
    const hash_map_t* cpt_hash_mapfirst, const hash_map_t* cpt_hash_mapsecond)
{
    assert(cpt_hash_mapfirst != NULL && cpt_hash_mapsecond != NULL);

    return _hashtable_equal(
        &cpt_hash_mapfirst->_t_hashtable, &cpt_hash_mapsecond->_t_hashtable);
}

bool_t hash_map_not_equal(
    const hash_map_t* cpt_hash_mapfirst, const hash_map_t* cpt_hash_mapsecond)
{
    assert(cpt_hash_mapfirst != NULL && cpt_hash_mapsecond != NULL);

    return _hashtable_not_equal(
        &cpt_hash_mapfirst->_t_hashtable, &cpt_hash_mapsecond->_t_hashtable);
}

bool_t hash_map_less(
    const hash_map_t* cpt_hash_mapfirst, const hash_map_t* cpt_hash_mapsecond)
{
    assert(cpt_hash_mapfirst != NULL && cpt_hash_mapsecond != NULL);

    return _hashtable_less(
        &cpt_hash_mapfirst->_t_hashtable, &cpt_hash_mapsecond->_t_hashtable);
}

bool_t hash_map_less_equal(
    const hash_map_t* cpt_hash_mapfirst, const hash_map_t* cpt_hash_mapsecond)
{
    assert(cpt_hash_mapfirst != NULL && cpt_hash_mapsecond != NULL);

    return _hashtable_less_equal(
        &cpt_hash_mapfirst->_t_hashtable, &cpt_hash_mapsecond->_t_hashtable);
}

bool_t hash_map_great(
    const hash_map_t* cpt_hash_mapfirst, const hash_map_t* cpt_hash_mapsecond)
{
    assert(cpt_hash_mapfirst != NULL && cpt_hash_mapsecond != NULL);

    return _hashtable_great(
        &cpt_hash_mapfirst->_t_hashtable, &cpt_hash_mapsecond->_t_hashtable);
}

bool_t hash_map_great_equal(
    const hash_map_t* cpt_hash_mapfirst, const hash_map_t* cpt_hash_mapsecond)
{
    assert(cpt_hash_mapfirst != NULL && cpt_hash_mapsecond != NULL);

    return _hashtable_great_equal(
        &cpt_hash_mapfirst->_t_hashtable, &cpt_hash_mapsecond->_t_hashtable);
}

hash_map_iterator_t _hash_map_find(const hash_map_t* cpt_hash_map, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, cpt_hash_map);
    return _hash_map_find_varg(cpt_hash_map, val_elemlist);
}

hash_map_iterator_t _hash_map_find_varg(
    const hash_map_t* cpt_hash_map, va_list val_elemlist)
{
    hash_map_iterator_t t_iterator;

    assert(cpt_hash_map != NULL);

    _type_get_varg_value(&((hash_map_t*)cpt_hash_map)->_t_pair._t_typeinfofirst,
        val_elemlist, cpt_hash_map->_t_pair._pv_first);

    t_iterator = _hashtable_find(&cpt_hash_map->_t_hashtable, &cpt_hash_map->_t_pair);

    _GET_CONTAINER(t_iterator) = (hash_map_t*)cpt_hash_map;
    _GET_HASH_MAP_CONTAINER_TYPE(t_iterator) = _HASH_MAP_CONTAINER;
    _GET_HASH_MAP_ITERATOR_TYPE(t_iterator) = _FORWARD_ITERATOR;

    return t_iterator;
}

size_t _hash_map_count(const hash_map_t* cpt_hash_map, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, cpt_hash_map);
    return _hash_map_count_varg(cpt_hash_map, val_elemlist);
}

size_t _hash_map_count_varg(const hash_map_t* cpt_hash_map, va_list val_elemlist)
{
    assert(cpt_hash_map != NULL);

    _type_get_varg_value(&((hash_map_t*)cpt_hash_map)->_t_pair._t_typeinfofirst,
        val_elemlist, cpt_hash_map->_t_pair._pv_first);

    return _hashtable_count(&cpt_hash_map->_t_hashtable, &cpt_hash_map->_t_pair);
}

range_t _hash_map_equal_range(const hash_map_t* cpt_hash_map, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, cpt_hash_map);
    return _hash_map_equal_range_varg(cpt_hash_map, val_elemlist);
}

range_t _hash_map_equal_range_varg(
    const hash_map_t* cpt_hash_map, va_list val_elemlist)
{
    range_t t_result;

    assert(cpt_hash_map != NULL);

    _type_get_varg_value(&((hash_map_t*)cpt_hash_map)->_t_pair._t_typeinfofirst,
        val_elemlist, cpt_hash_map->_t_pair._pv_first);

    t_result = _hashtable_equal_range(
        &cpt_hash_map->_t_hashtable, &cpt_hash_map->_t_pair);

    _GET_CONTAINER(t_result.t_begin) = (hash_map_t*)cpt_hash_map;
    _GET_HASH_MAP_CONTAINER_TYPE(t_result.t_begin) = _HASH_MAP_CONTAINER;
    _GET_HASH_MAP_ITERATOR_TYPE(t_result.t_begin) = _FORWARD_ITERATOR;

    _GET_CONTAINER(t_result.t_end) = (hash_map_t*)cpt_hash_map;
    _GET_HASH_MAP_CONTAINER_TYPE(t_result.t_end) = _HASH_MAP_CONTAINER;
    _GET_HASH_MAP_ITERATOR_TYPE(t_result.t_end) = _FORWARD_ITERATOR;

    return t_result;
}

hash_map_iterator_t hash_map_insert(
    hash_map_t* pt_hash_map, const pair_t* cpt_pair)
{
    hash_map_iterator_t t_result;

    assert(pt_hash_map != NULL && cpt_pair != NULL);
    assert(_hash_map_same_pair_type(&pt_hash_map->_t_pair, cpt_pair));

    /* insert int hashtable */
    t_result = _hashtable_insert_unique(&pt_hash_map->_t_hashtable, cpt_pair);

    _GET_CONTAINER(t_result) = pt_hash_map;
    _GET_HASH_MAP_CONTAINER_TYPE(t_result) = _HASH_MAP_CONTAINER;
    _GET_HASH_MAP_ITERATOR_TYPE(t_result) = _FORWARD_ITERATOR;

    return t_result;
}

void hash_map_insert_range(
    hash_map_t* pt_hash_map, hash_map_iterator_t t_begin, hash_map_iterator_t t_end)
{
    hash_map_iterator_t t_iterator;

    assert(pt_hash_map != NULL);
    assert(_GET_HASH_MAP_CONTAINER_TYPE(t_begin) == _HASH_MAP_CONTAINER &&
           _GET_HASH_MAP_ITERATOR_TYPE(t_begin) == _FORWARD_ITERATOR &&
           _GET_HASH_MAP_CONTAINER_TYPE(t_end) == _HASH_MAP_CONTAINER &&
           _GET_HASH_MAP_ITERATOR_TYPE(t_end) == _FORWARD_ITERATOR);
    assert(_GET_HASH_MAP_CONTAINER(t_begin) != pt_hash_map &&
           _GET_HASH_MAP_CONTAINER(t_end) != pt_hash_map &&
           _GET_HASH_MAP_CONTAINER(t_begin) == _GET_HASH_MAP_CONTAINER(t_end));

    for(t_iterator = t_begin;
        !iterator_equal(t_iterator, t_end);
        t_iterator = iterator_next(t_iterator))
    {
         hash_map_insert(pt_hash_map, (pair_t*)iterator_get_pointer(t_iterator));
    }
}

void hash_map_erase_pos(hash_map_t* pt_hash_map, hash_map_iterator_t t_pos)
{
    assert(pt_hash_map != NULL);
    assert(_GET_HASH_MAP_CONTAINER_TYPE(t_pos) == _HASH_MAP_CONTAINER &&
           _GET_HASH_MAP_ITERATOR_TYPE(t_pos) == _FORWARD_ITERATOR &&
           _GET_HASH_MAP_CONTAINER(t_pos) == pt_hash_map);

    _hashtable_erase_pos(&pt_hash_map->_t_hashtable, t_pos);
}

void hash_map_erase_range(
    hash_map_t* pt_hash_map, hash_map_iterator_t t_begin, hash_map_iterator_t t_end)
{
    assert(pt_hash_map != NULL);
    assert(_GET_HASH_MAP_CONTAINER_TYPE(t_begin) == _HASH_MAP_CONTAINER &&
           _GET_HASH_MAP_ITERATOR_TYPE(t_begin) == _FORWARD_ITERATOR &&
           _GET_HASH_MAP_CONTAINER_TYPE(t_end) == _HASH_MAP_CONTAINER &&
           _GET_HASH_MAP_ITERATOR_TYPE(t_end) == _FORWARD_ITERATOR);
    assert(_GET_HASH_MAP_CONTAINER(t_begin) == pt_hash_map &&
           _GET_HASH_MAP_CONTAINER(t_end) == pt_hash_map);

    _hashtable_erase_range(&pt_hash_map->_t_hashtable, t_begin, t_end);
}

size_t _hash_map_erase(hash_map_t* pt_hash_map, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, pt_hash_map);
    return _hash_map_erase_varg(pt_hash_map, val_elemlist);
}

size_t _hash_map_erase_varg(hash_map_t* pt_hash_map, va_list val_elemlist)
{
    assert(pt_hash_map != NULL);

    _type_get_varg_value(&pt_hash_map->_t_pair._t_typeinfofirst,
        val_elemlist, pt_hash_map->_t_pair._pv_first);

    return _hashtable_erase(&pt_hash_map->_t_hashtable, &pt_hash_map->_t_pair);
}

void hash_map_clear(hash_map_t* pt_hash_map)
{
    assert(pt_hash_map != NULL);

    _hashtable_clear(&pt_hash_map->_t_hashtable);
}

void* _hash_map_at(hash_map_t* pt_hash_map, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, pt_hash_map);
    return _hash_map_at_varg(pt_hash_map, val_elemlist);
}

void* _hash_map_at_varg(hash_map_t* pt_hash_map, va_list val_elemlist)
{
    hash_map_iterator_t t_result;

    assert(pt_hash_map != NULL);

    _type_get_varg_value(&pt_hash_map->_t_pair._t_typeinfofirst,
        val_elemlist, pt_hash_map->_t_pair._pv_first);

    t_result = _hashtable_insert_unique(&pt_hash_map->_t_hashtable, &pt_hash_map->_t_pair);
    if(iterator_equal(t_result, hash_map_end(pt_hash_map)))
    {
        t_result = _hash_map_find_varg(pt_hash_map, val_elemlist);
    }

    /* char* */
    if(strncmp(_GET_HASH_MAP_SECOND_TYPE_BASENAME(pt_hash_map),
        _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        return (char*)string_c_str(
            (string_t*)((pair_t*)iterator_get_pointer(t_result))->_pv_second);
    }
    else
    {
        return ((pair_t*)iterator_get_pointer(t_result))->_pv_second;
    }
}

void _hash_map_init_elem_auxiliary(hash_map_t* pt_hash_map, void* pv_elem)
{
    assert(pt_hash_map != NULL && pv_elem != NULL);

    /* initialize new elements */
    if(pt_hash_map->_t_hashtable._t_typeinfo._t_style == _TYPE_CSTL_BUILTIN)
    {
        /* get element type name */
        char s_elemtypename[_TYPE_NAME_SIZE + 1];
        _type_get_elem_typename(
            pt_hash_map->_t_hashtable._t_typeinfo._sz_typename, s_elemtypename);

        pt_hash_map->_t_hashtable._t_typeinfo._pt_type->_t_typeinit(pv_elem, s_elemtypename);
    }
    else
    {
        bool_t t_result = pt_hash_map->_t_hashtable._t_typeinfo._pt_type->_t_typesize;
        pt_hash_map->_t_hashtable._t_typeinfo._pt_type->_t_typeinit(pv_elem, &t_result);
        assert(t_result);
    }
}

/** local function implementation section **/
#ifndef NDEBUG
static bool_t _hash_map_same_pair_type(
    const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond)
{
    assert(cpt_pairfirst != NULL && cpt_pairsecond != NULL);

    return _type_is_same(cpt_pairfirst->_t_typeinfofirst._sz_typename,
                         cpt_pairsecond->_t_typeinfofirst._sz_typename) &&
           (cpt_pairfirst->_t_typeinfofirst._pt_type ==
            cpt_pairsecond->_t_typeinfofirst._pt_type) &&
           (cpt_pairfirst->_t_typeinfofirst._t_style ==
            cpt_pairsecond->_t_typeinfofirst._t_style) &&
           _type_is_same(cpt_pairfirst->_t_typeinfosecond._sz_typename,
                         cpt_pairsecond->_t_typeinfosecond._sz_typename) &&
           (cpt_pairfirst->_t_typeinfosecond._pt_type ==
            cpt_pairsecond->_t_typeinfosecond._pt_type) &&
           (cpt_pairfirst->_t_typeinfosecond._t_style ==
            cpt_pairsecond->_t_typeinfosecond._t_style);
}
#endif /* NDEBUG */

static void _hash_map_key_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    pair_t* pt_first = NULL;
    pair_t* pt_second = NULL;

    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    pt_first = (pair_t*)cpv_first;
    pt_second = (pair_t*)cpv_second;

    assert(_hash_map_same_pair_type(pt_first, pt_second));

    *(bool_t*)pv_output = pt_first->_t_typeinfofirst._pt_type->_t_typesize;
    pt_first->_t_typeinfofirst._pt_type->_t_typeless(
        pt_first->_pv_first, pt_second->_pv_first, pv_output);
}

/** eof **/

