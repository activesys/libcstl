/*
 *  The implementation of hash_map.
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
#include <cstl/cstl_hashtable_iterator.h>
#include <cstl/cstl_hashtable_private.h>
#include <cstl/cstl_hashtable.h>
#include <cstl/cutility.h>
#include <cstl/cstring.h>

#include <cstl/cstl_hash_map_iterator.h>
#include <cstl/cstl_hash_map_private.h>
#include <cstl/cstl_hash_map.h>

#include "cstl_hash_map_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/* hash_map iterator function */
hash_map_iterator_t create_hash_map_iterator(void)
{
    hash_map_iterator_t t_newiterator = _create_hashtable_iterator();

    _GET_HASH_MAP_CONTAINER_TYPE(t_newiterator) = _HASH_MAP_CONTAINER;
    _GET_HASH_MAP_ITERATOR_TYPE(t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

void _hash_map_iterator_get_value(hash_map_iterator_t t_iter, void* pv_value)
{
    assert(pv_value != NULL);
    assert(_GET_HASH_MAP_CONTAINER_TYPE(t_iter) == _HASH_MAP_CONTAINER &&
           _GET_HASH_MAP_ITERATOR_TYPE(t_iter) == _BIDIRECTIONAL_ITERATOR);

    _hashtable_iterator_get_value(t_iter, pv_value);
}

const void* _hash_map_iterator_get_pointer(hash_map_iterator_t t_iter)
{
    assert(_GET_HASH_MAP_CONTAINER_TYPE(t_iter) == _HASH_MAP_CONTAINER &&
           _GET_HASH_MAP_ITERATOR_TYPE(t_iter) == _BIDIRECTIONAL_ITERATOR);

    return _hashtable_iterator_get_pointer(t_iter);
}

hash_map_iterator_t _hash_map_iterator_prev(hash_map_iterator_t t_iter)
{
    assert(_GET_HASH_MAP_CONTAINER_TYPE(t_iter) == _HASH_MAP_CONTAINER &&
           _GET_HASH_MAP_ITERATOR_TYPE(t_iter) == _BIDIRECTIONAL_ITERATOR);

    return _hashtable_iterator_prev(t_iter);
}

hash_map_iterator_t _hash_map_iterator_next(hash_map_iterator_t t_iter)
{
    assert(_GET_HASH_MAP_CONTAINER_TYPE(t_iter) == _HASH_MAP_CONTAINER &&
           _GET_HASH_MAP_ITERATOR_TYPE(t_iter) == _BIDIRECTIONAL_ITERATOR);

    return _hashtable_iterator_next(t_iter);
}

bool_t _hash_map_iterator_equal(
    hash_map_iterator_t t_iterfirst, hash_map_iterator_t t_itersecond)
{
    assert(_GET_HASH_MAP_CONTAINER_TYPE(t_iterfirst) == _HASH_MAP_CONTAINER &&
           _GET_HASH_MAP_ITERATOR_TYPE(t_iterfirst) == _BIDIRECTIONAL_ITERATOR &&
           _GET_HASH_MAP_CONTAINER_TYPE(t_itersecond) == _HASH_MAP_CONTAINER &&
           _GET_HASH_MAP_ITERATOR_TYPE(t_itersecond) == _BIDIRECTIONAL_ITERATOR);

    return _hashtable_iterator_equal(t_iterfirst, t_itersecond);
}

int _hash_map_iterator_distance(
    hash_map_iterator_t t_iterfirst, hash_map_iterator_t t_itersecond)
{
    assert(_GET_HASH_MAP_CONTAINER_TYPE(t_iterfirst) == _HASH_MAP_CONTAINER &&
           _GET_HASH_MAP_ITERATOR_TYPE(t_iterfirst) == _BIDIRECTIONAL_ITERATOR &&
           _GET_HASH_MAP_CONTAINER_TYPE(t_itersecond) == _HASH_MAP_CONTAINER &&
           _GET_HASH_MAP_ITERATOR_TYPE(t_itersecond) == _BIDIRECTIONAL_ITERATOR &&
           _GET_HASH_MAP_CONTAINER(t_iterfirst) == _GET_HASH_MAP_CONTAINER(t_itersecond));

    return _hashtable_iterator_distance(t_iterfirst, t_itersecond);
}

bool_t _hash_map_iterator_before(
    hash_map_iterator_t t_iterfirst, hash_map_iterator_t t_itersecond)
{
    assert(_GET_HASH_MAP_CONTAINER_TYPE(t_iterfirst) == _HASH_MAP_CONTAINER &&
           _GET_HASH_MAP_ITERATOR_TYPE(t_iterfirst) == _BIDIRECTIONAL_ITERATOR &&
           _GET_HASH_MAP_CONTAINER_TYPE(t_itersecond) == _HASH_MAP_CONTAINER &&
           _GET_HASH_MAP_ITERATOR_TYPE(t_itersecond) == _BIDIRECTIONAL_ITERATOR &&
           _GET_HASH_MAP_CONTAINER(t_iterfirst) == 
               _GET_HASH_MAP_CONTAINER(t_itersecond));

    return _hashtable_iterator_before(t_iterfirst, t_itersecond);
}

/* hash_map function */
void hash_map_init(hash_map_t* pt_hash_map)
{
    hash_map_init_ex(pt_hash_map, 0, NULL, NULL);
}

void hash_map_init_ex(hash_map_t* pt_hash_map, size_t t_bucketcount,
    unary_function_t t_hash, binary_function_t t_compare)
{
    unary_function_t t_default_hash = NULL;

    assert(pt_hash_map != NULL);

    pt_hash_map->_bfun_keycompare = t_compare;
    pt_hash_map->_pair_temp._bfun_mapkeycompare = t_compare;
    t_default_hash = t_hash != NULL ? t_hash : _hash_map_default_hash;
    /* initialize the pair */
    pair_init(&pt_hash_map->_pair_temp);
    /* initialize the hashtable */
    _hashtable_init(&pt_hash_map->_t_hashtable, t_bucketcount, t_default_hash, _hash_map_value_compare);
}

void hash_map_destroy(hash_map_t* pt_hash_map)
{
    _hash_map_destroy_auxiliary(pt_hash_map);
    free(pt_hash_map);
}

void hash_map_init_copy(hash_map_t* pt_hash_mapdest, const hash_map_t* cpt_hash_mapsrc)
{
    assert(pt_hash_mapdest != NULL && cpt_hash_mapsrc != NULL);

    hash_map_init_ex(pt_hash_mapdest, hash_map_bucket_count(cpt_hash_mapsrc),
        hash_map_hash(cpt_hash_mapsrc), hash_map_key_comp(cpt_hash_mapsrc));
    pt_hash_mapdest->_bfun_keycompare = cpt_hash_mapsrc->_bfun_keycompare;
    pt_hash_mapdest->_bfun_valuecompare = cpt_hash_mapsrc->_bfun_valuecompare;
    pt_hash_mapdest->_pair_temp._bfun_mapkeycompare = cpt_hash_mapsrc->_pair_temp._bfun_mapkeycompare;
    pt_hash_mapdest->_pair_temp._bfun_mapvaluecompare = cpt_hash_mapsrc->_pair_temp._bfun_mapvaluecompare;
    assert(_hash_map_same_pair_type_ex(&pt_hash_mapdest->_pair_temp, &cpt_hash_mapsrc->_pair_temp));

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
    unary_function_t t_hash, binary_function_t t_compare)
{
    unary_function_t t_default_hash = NULL;

    assert(pt_hash_mapdest != NULL);
    assert(_GET_HASH_MAP_CONTAINER_TYPE(t_begin) == _HASH_MAP_CONTAINER &&
           _GET_HASH_MAP_ITERATOR_TYPE(t_begin) == _BIDIRECTIONAL_ITERATOR &&
           _GET_HASH_MAP_CONTAINER_TYPE(t_end) == _HASH_MAP_CONTAINER &&
           _GET_HASH_MAP_ITERATOR_TYPE(t_end) == _BIDIRECTIONAL_ITERATOR);
    assert(_GET_HASH_MAP_CONTAINER(t_begin) != pt_hash_mapdest &&
           _GET_HASH_MAP_CONTAINER(t_end) != pt_hash_mapdest &&
           _GET_HASH_MAP_CONTAINER(t_begin) == _GET_HASH_MAP_CONTAINER(t_end));

    t_default_hash = t_hash != NULL ? t_hash : _hash_map_default_hash;
    hash_map_init_ex(pt_hash_mapdest, t_bucketcount, t_default_hash, t_compare);
    if(!hash_map_empty(_GET_HASH_MAP_CONTAINER(t_begin)))
    {
        hash_map_insert_range(pt_hash_mapdest, t_begin, t_end);
    }
}

void hash_map_assign(hash_map_t* pt_hash_mapdest, const hash_map_t* cpt_hash_mapsrc)
{
    assert(pt_hash_mapdest != NULL && cpt_hash_mapsrc != NULL);
    assert(_hash_map_same_pair_type_ex(
        &pt_hash_mapdest->_pair_temp, &cpt_hash_mapsrc->_pair_temp));

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
    assert(_hash_map_same_pair_type_ex(&pt_hash_mapfirst->_pair_temp,
        &pt_hash_mapsecond->_pair_temp));

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

binary_function_t hash_map_key_comp(const hash_map_t* cpt_hash_map)
{
    assert(cpt_hash_map != NULL);

    if(cpt_hash_map->_bfun_keycompare != NULL)
    {
        return cpt_hash_map->_bfun_keycompare;
    }
    else
    {
        return _GET_HASH_MAP_FIRST_TYPE_LESS_FUNCTION(cpt_hash_map);
    }
}

binary_function_t hash_map_value_comp(const hash_map_t* cpt_hash_map)
{
#ifdef NDEBUG
    void* pv_avoidwarning = (void*)cpt_hash_map;
    pv_avoidwarning = NULL;
#endif 
    assert(cpt_hash_map != NULL);

    return _hash_map_value_compare;
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
    _GET_HASH_MAP_ITERATOR_TYPE(t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

hash_map_iterator_t hash_map_end(const hash_map_t* cpt_hash_map)
{
    hash_map_iterator_t t_newiterator;

    assert(cpt_hash_map != NULL);

    t_newiterator = _hashtable_end(&cpt_hash_map->_t_hashtable);

    _GET_CONTAINER(t_newiterator) = (hash_map_t*)cpt_hash_map;
    _GET_HASH_MAP_CONTAINER_TYPE(t_newiterator) = _HASH_MAP_CONTAINER;
    _GET_HASH_MAP_ITERATOR_TYPE(t_newiterator) = _BIDIRECTIONAL_ITERATOR;

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

bool_t hash_map_greater(
    const hash_map_t* cpt_hash_mapfirst, const hash_map_t* cpt_hash_mapsecond)
{
    assert(cpt_hash_mapfirst != NULL && cpt_hash_mapsecond != NULL);

    return _hashtable_greater(
        &cpt_hash_mapfirst->_t_hashtable, &cpt_hash_mapsecond->_t_hashtable);
}

bool_t hash_map_greater_equal(
    const hash_map_t* cpt_hash_mapfirst, const hash_map_t* cpt_hash_mapsecond)
{
    assert(cpt_hash_mapfirst != NULL && cpt_hash_mapsecond != NULL);

    return _hashtable_greater_equal(
        &cpt_hash_mapfirst->_t_hashtable, &cpt_hash_mapsecond->_t_hashtable);
}

hash_map_iterator_t hash_map_insert(
    hash_map_t* pt_hash_map, const pair_t* cpt_pair)
{
    hash_map_iterator_t t_result;

    assert(pt_hash_map != NULL && cpt_pair != NULL);
    /* set key less and value less function */
    ((pair_t*)cpt_pair)->_bfun_mapkeycompare = pt_hash_map->_bfun_keycompare;
    ((pair_t*)cpt_pair)->_bfun_mapvaluecompare = pt_hash_map->_bfun_valuecompare;
    assert(_hash_map_same_pair_type_ex(&pt_hash_map->_pair_temp, cpt_pair));

    /* insert int hashtable */
    t_result = _hashtable_insert_unique(&pt_hash_map->_t_hashtable, cpt_pair);

    _GET_CONTAINER(t_result) = pt_hash_map;
    _GET_HASH_MAP_CONTAINER_TYPE(t_result) = _HASH_MAP_CONTAINER;
    _GET_HASH_MAP_ITERATOR_TYPE(t_result) = _BIDIRECTIONAL_ITERATOR;

    return t_result;
}

void hash_map_insert_range(
    hash_map_t* pt_hash_map, hash_map_iterator_t t_begin, hash_map_iterator_t t_end)
{
    hash_map_iterator_t t_iterator;

    assert(pt_hash_map != NULL);
    assert(_GET_HASH_MAP_CONTAINER_TYPE(t_begin) == _HASH_MAP_CONTAINER &&
           _GET_HASH_MAP_ITERATOR_TYPE(t_begin) == _BIDIRECTIONAL_ITERATOR &&
           _GET_HASH_MAP_CONTAINER_TYPE(t_end) == _HASH_MAP_CONTAINER &&
           _GET_HASH_MAP_ITERATOR_TYPE(t_end) == _BIDIRECTIONAL_ITERATOR);
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
           _GET_HASH_MAP_ITERATOR_TYPE(t_pos) == _BIDIRECTIONAL_ITERATOR &&
           _GET_HASH_MAP_CONTAINER(t_pos) == pt_hash_map);

    _hashtable_erase_pos(&pt_hash_map->_t_hashtable, t_pos);
}

void hash_map_erase_range(
    hash_map_t* pt_hash_map, hash_map_iterator_t t_begin, hash_map_iterator_t t_end)
{
    assert(pt_hash_map != NULL);
    assert(_GET_HASH_MAP_CONTAINER_TYPE(t_begin) == _HASH_MAP_CONTAINER &&
           _GET_HASH_MAP_ITERATOR_TYPE(t_begin) == _BIDIRECTIONAL_ITERATOR &&
           _GET_HASH_MAP_CONTAINER_TYPE(t_end) == _HASH_MAP_CONTAINER &&
           _GET_HASH_MAP_ITERATOR_TYPE(t_end) == _BIDIRECTIONAL_ITERATOR);
    assert(_GET_HASH_MAP_CONTAINER(t_begin) == pt_hash_map &&
           _GET_HASH_MAP_CONTAINER(t_end) == pt_hash_map);

    _hashtable_erase_range(&pt_hash_map->_t_hashtable, t_begin, t_end);
}

void hash_map_clear(hash_map_t* pt_hash_map)
{
    assert(pt_hash_map != NULL);

    _hashtable_clear(&pt_hash_map->_t_hashtable);
}

/** local function implementation section **/

/** eof **/

