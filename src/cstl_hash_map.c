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

#include "cstl_types.h"
#include "cstl_alloc.h"
#include "cstl_iterator.h"

#include "cvector.h"
#include "cstl_hashtable_iterator.h"
#include "cstl_hashtable_private.h"
#include "cutility.h"

#include "cstl_hash_map_iterator.h"
#include "cstl_hash_map_private.h"
#include "cstl_hash_map.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/
#ifndef NDEBUG
/*
 * Assert support.
 */
static bool_t _same_hash_map_pair_type(
    const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond);
#endif /* NDEBUG */

/*
 * hash_map element compare function.
 */
static int _hash_map_cmp(const void* cpv_firstelem, const void* cpv_secondelem);

/*
 * Destroy element function.
 */
static void _hash_map_destroy_elem(void* pv_value);

/*
 * hash_map default hash function.
 */
static int _hash_map_hash_function(
    const void* cpv_value, size_t t_nodesize, size_t t_bucketcount);

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/* hash_map iterator function */
hash_map_iterator_t create_hash_map_iterator(void)
{
    hash_map_iterator_t t_newiterator = _create_hashtable_iterator();

    _GET_HASH_MAP_CONTAINER_TYPE(&t_newiterator) = _HASH_MAP_CONTAINER;
    _GET_HASH_MAP_ITERATOR_TYPE(&t_newiterator) = _FORWARD_ITERATOR;

    return t_newiterator;
}

void _hash_map_iterator_get_value(
    const struct _taghashmap* cpt_hash_map,
    const hash_map_iterator_t* cpt_iterator,
    void* pv_value)
{
    assert(cpt_hash_map != NULL && cpt_iterator && pv_value != NULL);
    assert(
        _GET_HASH_MAP_CONTAINER_TYPE(cpt_iterator) == _HASH_MAP_CONTAINER &&
        _GET_HASH_MAP_ITERATOR_TYPE(cpt_iterator) == _FORWARD_ITERATOR &&
        _GET_HASH_MAP_CONTAINER(cpt_iterator) == cpt_hash_map);

    _hashtable_iterator_get_value(
        &cpt_hash_map->_t_hashtable, cpt_iterator, pv_value);
}

const void* _hash_map_iterator_get_pointer(
    const struct _taghashmap* cpt_hash_map,
    const hash_map_iterator_t* cpt_iterator)
{
    assert(cpt_hash_map != NULL && cpt_iterator != NULL);
    assert(
        _GET_HASH_MAP_CONTAINER_TYPE(cpt_iterator) == _HASH_MAP_CONTAINER &&
        _GET_HASH_MAP_ITERATOR_TYPE(cpt_iterator) == _FORWARD_ITERATOR &&
        _GET_HASH_MAP_CONTAINER(cpt_iterator) == cpt_hash_map);

    return _hashtable_iterator_get_pointer(
        &cpt_hash_map->_t_hashtable, cpt_iterator);
}

void _hash_map_iterator_next(
    const struct _taghashmap* cpt_hash_map,
    hash_map_iterator_t* pt_iterator)
{
    assert(cpt_hash_map != NULL && pt_iterator != NULL);
    assert(
        _GET_HASH_MAP_CONTAINER_TYPE(pt_iterator) == _HASH_MAP_CONTAINER &&
        _GET_HASH_MAP_ITERATOR_TYPE(pt_iterator) == _FORWARD_ITERATOR &&
        _GET_HASH_MAP_CONTAINER(pt_iterator) == cpt_hash_map);

    _hashtable_iterator_next(&cpt_hash_map->_t_hashtable, pt_iterator);
}

bool_t _hash_map_iterator_equal(
    const struct _taghashmap* cpt_hash_map,
    const hash_map_iterator_t* cpt_iterator,
    hash_map_iterator_t t_iterator)
{
    assert(cpt_hash_map != NULL && cpt_iterator != NULL);
    assert(
        _GET_HASH_MAP_CONTAINER_TYPE(cpt_iterator) == _HASH_MAP_CONTAINER &&
        _GET_HASH_MAP_ITERATOR_TYPE(cpt_iterator) == _FORWARD_ITERATOR &&
        _GET_HASH_MAP_CONTAINER_TYPE(&t_iterator) == _HASH_MAP_CONTAINER &&
        _GET_HASH_MAP_ITERATOR_TYPE(&t_iterator) == _FORWARD_ITERATOR);
    assert(
        _GET_HASH_MAP_CONTAINER(cpt_iterator) == cpt_hash_map &&
        _GET_HASH_MAP_CONTAINER(&t_iterator) == cpt_hash_map);

    return _hashtable_iterator_equal(
        &cpt_hash_map->_t_hashtable, cpt_iterator, t_iterator);
}

int _hash_map_iterator_distance(
    const hash_map_iterator_t* cpt_begin, const hash_map_iterator_t* cpt_end)
{
    assert(cpt_begin != NULL && cpt_end != NULL);
    assert(
        _GET_HASH_MAP_CONTAINER_TYPE(cpt_begin) == _HASH_MAP_CONTAINER &&
        _GET_HASH_MAP_ITERATOR_TYPE(cpt_begin) == _FORWARD_ITERATOR &&
        _GET_HASH_MAP_CONTAINER_TYPE(cpt_end) == _HASH_MAP_CONTAINER &&
        _GET_HASH_MAP_ITERATOR_TYPE(cpt_end) == _FORWARD_ITERATOR &&
        _GET_HASH_MAP_CONTAINER(cpt_begin) == _GET_HASH_MAP_CONTAINER(cpt_end));

    return _hashtable_iterator_distance(cpt_begin, cpt_end);
}

bool_t _hash_map_iterator_before(
    const hash_map_iterator_t* cpt_iteratorfirst,
    const hash_map_iterator_t* cpt_iteratorsecond)
{
    assert(cpt_iteratorfirst != NULL && cpt_iteratorsecond != NULL);
    assert(
        _GET_HASH_MAP_CONTAINER_TYPE(cpt_iteratorfirst) == _HASH_MAP_CONTAINER &&
        _GET_HASH_MAP_ITERATOR_TYPE(cpt_iteratorfirst) == _FORWARD_ITERATOR &&
        _GET_HASH_MAP_CONTAINER_TYPE(cpt_iteratorsecond) == _HASH_MAP_CONTAINER &&
        _GET_HASH_MAP_ITERATOR_TYPE(cpt_iteratorsecond) == _FORWARD_ITERATOR &&
        _GET_HASH_MAP_CONTAINER(cpt_iteratorfirst) == 
            _GET_HASH_MAP_CONTAINER(cpt_iteratorsecond));

    return _hashtable_iterator_before(cpt_iteratorfirst, cpt_iteratorsecond);
}

/* hash_map private function */
hash_map_t _create_hash_map(
    size_t t_keytypesize, const char* s_keytypename, 
    size_t t_valuetypesize, const char* s_valuetypename)
{
    hash_map_t t_new_hash_map;
    char  ac_hashmaptypename[_ELEM_TYPE_NAME_SIZE+1];

    assert(t_keytypesize > 0 && t_valuetypesize > 0);
    assert(s_keytypename != NULL && s_valuetypename != NULL);

    /* create pair */
    t_new_hash_map._t_pair = _create_pair(
        t_keytypesize, s_keytypename, t_valuetypesize, s_valuetypename);
    /* create tree */
    memset(ac_hashmaptypename, '\0', _ELEM_TYPE_NAME_SIZE+1);
    strncpy(ac_hashmaptypename, _HASH_MAP_IDENTIFY, _ELEM_TYPE_NAME_SIZE);
    strcat(ac_hashmaptypename, _HASH_MAP_LEFT_BRACKET);
    strcat(ac_hashmaptypename, t_new_hash_map._t_pair._sz_firsttypename);
    strcat(ac_hashmaptypename, _HASH_MAP_COMMA);
    strcat(ac_hashmaptypename, t_new_hash_map._t_pair._sz_secondtypename);
    strcat(ac_hashmaptypename, _HASH_MAP_RIGHT_BRACKET);

    t_new_hash_map._t_hashtable = _create_hashtable(sizeof(pair_t), ac_hashmaptypename);

    return t_new_hash_map;
}

/* hash_map function */
void hash_map_init(
    hash_map_t* pt_hash_map, int (*pfun_hash)(const void*, size_t, size_t))
{
    hash_map_init_n(pt_hash_map, 0, pfun_hash);
}

void hash_map_init_n(
    hash_map_t* pt_hash_map, size_t t_bucketcount,
    int (*pfun_hash)(const void*, size_t, size_t))
{
    assert(pt_hash_map != NULL);

    /* initialize the pair */
    pair_init(&pt_hash_map->_t_pair);
    /* initialize the hashtable */
    if(pfun_hash != NULL)
    {
        _hashtable_init(
            &pt_hash_map->_t_hashtable, t_bucketcount,
            pfun_hash, _hash_map_cmp, _hash_map_destroy_elem);
    }
    else
    {
        _hashtable_init(
            &pt_hash_map->_t_hashtable, t_bucketcount,
            _hash_map_hash_function, _hash_map_cmp, _hash_map_destroy_elem);
    }
}

void hash_map_destroy(hash_map_t* pt_hash_map)
{
    assert(pt_hash_map != NULL);

    pair_destroy(&pt_hash_map->_t_pair);
    _hashtable_destroy(&pt_hash_map->_t_hashtable);
}

void hash_map_init_copy(
    hash_map_t* pt_hash_mapdest, const hash_map_t* cpt_hash_mapsrc)
{
    assert(pt_hash_mapdest != NULL && cpt_hash_mapsrc != NULL);
    assert(
        pt_hash_mapdest->_t_pair._t_firsttypesize == 
            cpt_hash_mapsrc->_t_pair._t_firsttypesize &&
        pt_hash_mapdest->_t_pair._t_secondtypesize == 
            cpt_hash_mapsrc->_t_pair._t_secondtypesize);
    assert(
        strncmp(
            pt_hash_mapdest->_t_pair._sz_firsttypename,
            cpt_hash_mapsrc->_t_pair._sz_firsttypename,
            _ELEM_TYPE_NAME_SIZE) == 0 &&
        strncmp(
            pt_hash_mapdest->_t_pair._sz_secondtypename,
            cpt_hash_mapsrc->_t_pair._sz_secondtypename,
            _ELEM_TYPE_NAME_SIZE) == 0);

    hash_map_init_n(
        pt_hash_mapdest,
        hash_map_bucket_count(cpt_hash_mapsrc), hash_map_hash_func(cpt_hash_mapsrc));

    if(!hash_map_empty(cpt_hash_mapsrc))
    {
        hash_map_insert_range(
            pt_hash_mapdest, 
            hash_map_begin(cpt_hash_mapsrc), hash_map_end(cpt_hash_mapsrc));
    }
}

void hash_map_init_copy_range(
    hash_map_t* pt_hash_mapdest, hash_map_iterator_t t_begin, hash_map_iterator_t t_end,
    int (*pfun_hash)(const void*, size_t, size_t))
{
    hash_map_init_copy_range_n(pt_hash_mapdest, t_begin, t_end, 0, pfun_hash);
}

void hash_map_init_copy_range_n(
    hash_map_t* pt_hash_mapdest, hash_map_iterator_t t_begin, hash_map_iterator_t t_end,
    size_t t_bucketcount, int (*pfun_hash)(const void*, size_t, size_t))
{
    assert(pt_hash_mapdest != NULL);
    assert(
        _GET_HASH_MAP_CONTAINER_TYPE(&t_begin) == _HASH_MAP_CONTAINER &&
        _GET_HASH_MAP_ITERATOR_TYPE(&t_begin) == _FORWARD_ITERATOR &&
        _GET_HASH_MAP_CONTAINER_TYPE(&t_end) == _HASH_MAP_CONTAINER &&
        _GET_HASH_MAP_ITERATOR_TYPE(&t_end) == _FORWARD_ITERATOR);
    assert(
        _GET_HASH_MAP_CONTAINER(&t_begin) != pt_hash_mapdest &&
        _GET_HASH_MAP_CONTAINER(&t_end) != pt_hash_mapdest &&
        _GET_HASH_MAP_CONTAINER(&t_begin) == _GET_HASH_MAP_CONTAINER(&t_end));
    assert(
        pt_hash_mapdest->_t_pair._t_firsttypesize == 
            _GET_HASH_MAP_CONTAINER(&t_begin)->_t_pair._t_firsttypesize &&
        pt_hash_mapdest->_t_pair._t_secondtypesize == 
            _GET_HASH_MAP_CONTAINER(&t_begin)->_t_pair._t_secondtypesize);
    assert(
        strncmp(
            pt_hash_mapdest->_t_pair._sz_firsttypename,
            _GET_HASH_MAP_CONTAINER(&t_begin)->_t_pair._sz_firsttypename,
            _ELEM_TYPE_NAME_SIZE) == 0 &&
        strncmp(
            pt_hash_mapdest->_t_pair._sz_secondtypename,
            _GET_HASH_MAP_CONTAINER(&t_begin)->_t_pair._sz_secondtypename,
            _ELEM_TYPE_NAME_SIZE) == 0);

    hash_map_init_n(pt_hash_mapdest, t_bucketcount, pfun_hash);

    if(!hash_map_empty(_GET_HASH_MAP_CONTAINER(&t_begin)))
    {
        hash_map_insert_range(pt_hash_mapdest, t_begin, t_end);
    }
}

void hash_map_assign(hash_map_t* pt_hash_mapdest, const hash_map_t* cpt_hash_mapsrc)
{
    assert(pt_hash_mapdest != NULL && cpt_hash_mapsrc != NULL);
    assert(
        _same_hash_map_pair_type(
                &pt_hash_mapdest->_t_pair, &cpt_hash_mapsrc->_t_pair));

    hash_map_destroy(pt_hash_mapdest);
    hash_map_init_n(
        pt_hash_mapdest, 
        hash_map_bucket_count(cpt_hash_mapsrc), hash_map_hash_func(cpt_hash_mapsrc));

    if(!hash_map_empty(cpt_hash_mapsrc))
    {
        hash_map_insert_range(
            pt_hash_mapdest,
            hash_map_begin(cpt_hash_mapsrc), hash_map_end(cpt_hash_mapsrc));
    }
}

void hash_map_swap(
    hash_map_t* pt_hash_mapfirst, hash_map_t* pt_hash_mapsecond)
{
    assert(pt_hash_mapfirst != NULL && pt_hash_mapsecond != NULL);
    assert(
        _same_hash_map_pair_type(
            &pt_hash_mapfirst->_t_pair, &pt_hash_mapsecond->_t_pair));

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

int (*hash_map_hash_func(const hash_map_t* cpt_hash_map))(
    const void*, size_t, size_t)
{
    assert(cpt_hash_map != NULL);

    return _hashtable_hash_func(&cpt_hash_map->_t_hashtable);
}

int (*hash_map_key_comp(const hash_map_t* cpt_hash_map))(
    const void*, const void*)
{
    assert(cpt_hash_map != NULL);

    return cpt_hash_map->_t_pair._pfun_first_cmp;
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

    _GET_CONTAINER(&t_newiterator) = (hash_map_t*)cpt_hash_map;
    _GET_HASH_MAP_CONTAINER_TYPE(&t_newiterator) = _HASH_MAP_CONTAINER;
    _GET_HASH_MAP_ITERATOR_TYPE(&t_newiterator) = _FORWARD_ITERATOR;

    return t_newiterator;
}

hash_map_iterator_t hash_map_end(const hash_map_t* cpt_hash_map)
{
    hash_map_iterator_t t_newiterator;

    assert(cpt_hash_map != NULL);

    t_newiterator = _hashtable_end(&cpt_hash_map->_t_hashtable);

    _GET_CONTAINER(&t_newiterator) = (hash_map_t*)cpt_hash_map;
    _GET_HASH_MAP_CONTAINER_TYPE(&t_newiterator) = _HASH_MAP_CONTAINER;
    _GET_HASH_MAP_ITERATOR_TYPE(&t_newiterator) = _FORWARD_ITERATOR;

    return t_newiterator;
}

bool_t hash_map_equal(
    const hash_map_t* cpt_hash_mapfirst, const hash_map_t* cpt_hash_mapsecond)
{
    assert(cpt_hash_mapfirst != NULL && cpt_hash_mapsecond != NULL);

    /* test pair */
    if(cpt_hash_mapfirst->_t_pair._t_firsttypesize != 
        cpt_hash_mapsecond->_t_pair._t_firsttypesize ||
       cpt_hash_mapfirst->_t_pair._t_secondtypesize != 
        cpt_hash_mapsecond->_t_pair._t_secondtypesize)
    {
        return false;
    }
    if(strncmp(
        cpt_hash_mapfirst->_t_pair._sz_firsttypename,
        cpt_hash_mapsecond->_t_pair._sz_firsttypename,
        _ELEM_TYPE_NAME_SIZE) != 0 ||
       strncmp(
        cpt_hash_mapfirst->_t_pair._sz_secondtypename,
        cpt_hash_mapsecond->_t_pair._sz_secondtypename,
        _ELEM_TYPE_NAME_SIZE) != 0)
    {
        return false;
    }
    if(cpt_hash_mapfirst->_t_pair._pfun_first_cmp !=
        cpt_hash_mapsecond->_t_pair._pfun_first_cmp ||
       cpt_hash_mapfirst->_t_pair._pfun_second_cmp != 
        cpt_hash_mapsecond->_t_pair._pfun_second_cmp)
    {
        return false;
    }
    /* test hashtable */
    return _hashtable_equal(
        &cpt_hash_mapfirst->_t_hashtable, &cpt_hash_mapsecond->_t_hashtable);
}

bool_t hash_map_not_equal(
    const hash_map_t* cpt_hash_mapfirst, const hash_map_t* cpt_hash_mapsecond)
{
    return !hash_map_equal(cpt_hash_mapfirst, cpt_hash_mapsecond);
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

    _get_varg_value(
        cpt_hash_map->_t_pair.first, val_elemlist, 
        cpt_hash_map->_t_pair._t_firsttypesize, cpt_hash_map->_t_pair._sz_firsttypename);

    t_iterator = _hashtable_find(&cpt_hash_map->_t_hashtable, &cpt_hash_map->_t_pair);

    _GET_CONTAINER(&t_iterator) = (hash_map_t*)cpt_hash_map;
    _GET_HASH_MAP_CONTAINER_TYPE(&t_iterator) = _HASH_MAP_CONTAINER;
    _GET_HASH_MAP_ITERATOR_TYPE(&t_iterator) = _FORWARD_ITERATOR;

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

    _get_varg_value(
        cpt_hash_map->_t_pair.first, val_elemlist,
        cpt_hash_map->_t_pair._t_firsttypesize, cpt_hash_map->_t_pair._sz_firsttypename);

    return _hashtable_count(&cpt_hash_map->_t_hashtable, &cpt_hash_map->_t_pair);
}

pair_t _hash_map_equal_range(const hash_map_t* cpt_hash_map, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, cpt_hash_map);
    return _hash_map_equal_range_varg(cpt_hash_map, val_elemlist);
}

pair_t _hash_map_equal_range_varg(
    const hash_map_t* cpt_hash_map, va_list val_elemlist)
{
    hash_map_iterator_t     t_firstiterator;
    hash_map_iterator_t     t_seconditerator;
    hashtable_result_pair_t t_result;
    pair_t                  t_pair;

    assert(cpt_hash_map != NULL);

    _get_varg_value(
        cpt_hash_map->_t_pair.first, val_elemlist, 
        cpt_hash_map->_t_pair._t_firsttypesize, cpt_hash_map->_t_pair._sz_firsttypename);

    t_result = _hashtable_equal_range(
        &cpt_hash_map->_t_hashtable, &cpt_hash_map->_t_pair);

    t_firstiterator = t_result._t_first;
    _GET_CONTAINER(&t_firstiterator) = (hash_map_t*)cpt_hash_map;
    _GET_HASH_MAP_CONTAINER_TYPE(&t_firstiterator) = _HASH_MAP_CONTAINER;
    _GET_HASH_MAP_ITERATOR_TYPE(&t_firstiterator) = _FORWARD_ITERATOR;

    t_seconditerator = t_result._t_second._t_iterator;
    _GET_CONTAINER(&t_seconditerator) = (hash_map_t*)cpt_hash_map;
    _GET_HASH_MAP_CONTAINER_TYPE(&t_seconditerator) = _HASH_MAP_CONTAINER;
    _GET_HASH_MAP_ITERATOR_TYPE(&t_seconditerator) = _FORWARD_ITERATOR;

    t_pair = create_pair(hash_map_iterator_t, hash_map_iterator_t);
    pair_init(&t_pair);
    memcpy(t_pair.first, &t_firstiterator, t_pair._t_firsttypesize);
    memcpy(t_pair.second, &t_seconditerator, t_pair._t_secondtypesize);

    return t_pair;
}

hash_map_iterator_t hash_map_insert(
    hash_map_t* pt_hash_map, const pair_t* cpt_pair)
{
    pair_t                  t_elempair;
    hashtable_result_pair_t t_result;

    assert(pt_hash_map != NULL && cpt_pair != NULL);
    assert(_same_hash_map_pair_type(&pt_hash_map->_t_pair, cpt_pair));

    /* initialize new elemen pair */
    t_elempair = _create_pair(
        pt_hash_map->_t_pair._t_firsttypesize, pt_hash_map->_t_pair._sz_firsttypename,
        pt_hash_map->_t_pair._t_secondtypesize, pt_hash_map->_t_pair._sz_secondtypename);
    pair_init(&t_elempair);
    memcpy(t_elempair.first, cpt_pair->first, t_elempair._t_firsttypesize);
    memcpy(t_elempair.second, cpt_pair->second, t_elempair._t_secondtypesize);

    /* insert int hashtable */
    t_result = _hashtable_insert_unique(&pt_hash_map->_t_hashtable, &t_elempair);

    /* destroy when insert failed */
    if(!t_result._t_second._t_bool)
    {
        pair_destroy(&t_elempair);
    }

    _GET_CONTAINER(&t_result._t_first) = pt_hash_map;
    _GET_HASH_MAP_CONTAINER_TYPE(&t_result._t_first) = _HASH_MAP_CONTAINER;
    _GET_HASH_MAP_ITERATOR_TYPE(&t_result._t_first) = _FORWARD_ITERATOR;

    return t_result._t_second._t_bool ? t_result._t_first : hash_map_end(pt_hash_map);
}

void hash_map_insert_range(
    hash_map_t* pt_hash_map, hash_map_iterator_t t_begin, hash_map_iterator_t t_end)
{
    hash_map_iterator_t t_iterator;

    assert(pt_hash_map != NULL);
    assert(
        _GET_HASH_MAP_CONTAINER_TYPE(&t_begin) == _HASH_MAP_CONTAINER &&
        _GET_HASH_MAP_ITERATOR_TYPE(&t_begin) == _FORWARD_ITERATOR &&
        _GET_HASH_MAP_CONTAINER_TYPE(&t_end) == _HASH_MAP_CONTAINER &&
        _GET_HASH_MAP_ITERATOR_TYPE(&t_end) == _FORWARD_ITERATOR);
    assert(
        _GET_HASH_MAP_CONTAINER(&t_begin) != pt_hash_map &&
        _GET_HASH_MAP_CONTAINER(&t_end) != pt_hash_map &&
        _GET_HASH_MAP_CONTAINER(&t_begin) == _GET_HASH_MAP_CONTAINER(&t_end));

    for(t_iterator = t_begin;
        !iterator_equal(&t_iterator, t_end);
        iterator_next(&t_iterator))
    {
         hash_map_insert(pt_hash_map, (pair_t*)iterator_get_pointer(&t_iterator));
    }
}

void hash_map_erase_pos(hash_map_t* pt_hash_map, hash_map_iterator_t t_pos)
{
    assert(pt_hash_map != NULL);
    assert(
        _GET_HASH_MAP_CONTAINER_TYPE(&t_pos) == _HASH_MAP_CONTAINER &&
        _GET_HASH_MAP_ITERATOR_TYPE(&t_pos) == _FORWARD_ITERATOR &&
        _GET_HASH_MAP_CONTAINER(&t_pos) == pt_hash_map);

    _hashtable_erase_pos(&pt_hash_map->_t_hashtable, t_pos);
}

void hash_map_erase_range(
    hash_map_t* pt_hash_map, hash_map_iterator_t t_begin, hash_map_iterator_t t_end)
{
    assert(pt_hash_map != NULL);
    assert(
        _GET_HASH_MAP_CONTAINER_TYPE(&t_begin) == _HASH_MAP_CONTAINER &&
        _GET_HASH_MAP_ITERATOR_TYPE(&t_begin) == _FORWARD_ITERATOR &&
        _GET_HASH_MAP_CONTAINER_TYPE(&t_end) == _HASH_MAP_CONTAINER &&
        _GET_HASH_MAP_ITERATOR_TYPE(&t_end) == _FORWARD_ITERATOR);
    assert(
        _GET_HASH_MAP_CONTAINER(&t_begin) == pt_hash_map &&
        _GET_HASH_MAP_CONTAINER(&t_end) == pt_hash_map);

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

    _get_varg_value(
        pt_hash_map->_t_pair.first, val_elemlist, 
        pt_hash_map->_t_pair._t_firsttypesize, pt_hash_map->_t_pair._sz_firsttypename);

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
    pair_t                  t_elempair; 
    void*                   pv_value = NULL;
    hashtable_result_pair_t t_result;

    assert(pt_hash_map != NULL);

    t_elempair = _create_pair(
        pt_hash_map->_t_pair._t_firsttypesize, pt_hash_map->_t_pair._sz_firsttypename,
        pt_hash_map->_t_pair._t_secondtypesize, pt_hash_map->_t_pair._sz_secondtypename);
    pair_init(&t_elempair);
    _get_varg_value(
        t_elempair.first, val_elemlist,
        t_elempair._t_firsttypesize, t_elempair._sz_firsttypename);
    memset(t_elempair.second, 0x00, t_elempair._t_secondtypesize);

    t_result = _hashtable_insert_unique(&pt_hash_map->_t_hashtable, &t_elempair);

    pv_value = ((pair_t*)(((hashnode_t*)
        _GET_HASHTABLE_COREPOS(&t_result._t_first))->_pc_data))->second;
    assert(pv_value != NULL);

    if(!t_result._t_second._t_bool)
    {
        pair_destroy(&t_elempair);
    }

    return pv_value;
}

/** local function implementation section **/
#ifndef NDEBUG
static bool_t _same_hash_map_pair_type(
    const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond)
{
    assert(cpt_pairfirst != NULL && cpt_pairsecond != NULL);

    assert(cpt_pairfirst->first != NULL && cpt_pairfirst->second != NULL);
    assert(cpt_pairsecond->first != NULL && cpt_pairsecond->second != NULL);
    assert(
        cpt_pairfirst->_t_firsttypesize == cpt_pairsecond->_t_firsttypesize && 
        cpt_pairfirst->_t_secondtypesize == cpt_pairsecond->_t_secondtypesize);
    assert(
        strncmp(
            cpt_pairfirst->_sz_firsttypename, cpt_pairsecond->_sz_firsttypename,
            _ELEM_TYPE_NAME_SIZE) == 0 &&
        strncmp(
            cpt_pairfirst->_sz_secondtypename, cpt_pairsecond->_sz_secondtypename,
            _ELEM_TYPE_NAME_SIZE) == 0);

    assert(
        cpt_pairfirst->_pfun_first_cmp == cpt_pairsecond->_pfun_first_cmp &&
        cpt_pairfirst->_pfun_second_cmp == cpt_pairsecond->_pfun_second_cmp);

    return true;
}
#endif /* NDEBUG */

static int _hash_map_cmp(const void* cpv_firstelem, const void* cpv_secondelem)
{
    pair_t* pt_first = NULL;
    pair_t* pt_second = NULL;

    assert(cpv_firstelem != NULL && cpv_secondelem != NULL);

    pt_first = (pair_t*)cpv_firstelem;
    pt_second = (pair_t*)cpv_secondelem;

    assert(_same_hash_map_pair_type(pt_first, pt_second));

    if(pt_first->_pfun_first_cmp != NULL)
    {
        return (*pt_first->_pfun_first_cmp)(pt_first->first, pt_second->first);
    }
    else
    {
        return memcmp(pt_first->first, pt_second->first, pt_first->_t_firsttypesize);
    }
}

static void _hash_map_destroy_elem(void* pv_value)
{
    assert(pv_value != NULL);

    pair_destroy((pair_t*)pv_value);
}

static int _hash_map_hash_function(
    const void* cpv_value, size_t t_nodesize, size_t t_bucketcount)
{
    size_t  t_sum = 0;
    pair_t* pt_pair = NULL;
    char*   pc_value = NULL;
    size_t  t_index = 0;
    size_t  t_avoidwarning = 0;
    t_avoidwarning = t_nodesize;

    assert(cpv_value != NULL && t_bucketcount > 0);

    pt_pair = (pair_t*)cpv_value;

    /* hash for int */
    if(strncmp(
        pt_pair->_sz_firsttypename, _INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        return abs(*(int*)pt_pair->first % t_bucketcount);
    }
    /* hash for unsigned int */
    else if(strncmp(
        pt_pair->_sz_firsttypename, _UNSIGNED_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        return *(unsigned int*)pt_pair->first % t_bucketcount;
    }
    /* hash for short */
    else if(strncmp(
        pt_pair->_sz_firsttypename, _SHORT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        return abs(*(short*)pt_pair->first % t_bucketcount);
    }
    /* hash for unsigned short */
    else if(strncmp(
        pt_pair->_sz_firsttypename, _UNSIGNED_SHORT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        return *(unsigned short*)pt_pair->first % t_bucketcount;
    }
    /* hash for long */
    else if(strncmp(
        pt_pair->_sz_firsttypename, _LONG_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        return abs(*(long*)pt_pair->first % t_bucketcount);
    }
    /* hash for unsigned long */
    else if(strncmp(
        pt_pair->_sz_firsttypename, _UNSIGNED_LONG_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        return *(unsigned long*)pt_pair->first % t_bucketcount;
    }
    /* hash for double */
    else if(strncmp(
        pt_pair->_sz_firsttypename, _DOUBLE_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        return (unsigned long)*(double*)pt_pair->first % t_bucketcount;
    }
    /* hash for float */
    else if(strncmp(
        pt_pair->_sz_firsttypename, _FLOAT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        return (unsigned long)*(float*)pt_pair->first % t_bucketcount;
    }
    else
    {
        pc_value = pt_pair->first;
        for(t_index = 0; t_index < pt_pair->_t_firsttypesize; ++t_index)
        {
            t_sum += (size_t)pc_value[t_index];
        }

        return (int)(t_sum % t_bucketcount);
    }
}

/** eof **/

