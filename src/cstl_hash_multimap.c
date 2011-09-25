/*
 *  The implementation of hash_multimap.
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
#include <cstl/cstl_iterator.h>

#include <cstl/cvector.h>
#include <cstl/cstl_hashtable_iterator.h>
#include <cstl/cstl_hashtable_private.h>
#include <cstl/cstl_hashtable.h>
#include <cstl/cutility.h>
#include <cstl/cstring.h>

#include <cstl/cstl_hash_multimap_iterator.h>
#include <cstl/cstl_hash_multimap_private.h>
#include <cstl/cstl_hash_multimap.h>

#include "cstl_hash_multimap_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/* hash_multimap function */
void hash_multimap_init(hash_multimap_t* pt_hash_multimap)
{
    hash_multimap_init_ex(pt_hash_multimap, 0, NULL, NULL);
}

void hash_multimap_init_ex(hash_multimap_t* pt_hash_multimap, size_t t_bucketcount,
    unary_function_t t_hash, binary_function_t t_compare)
{
    unary_function_t t_default_hash = NULL;

    assert(pt_hash_multimap != NULL);

    pt_hash_multimap->_bfun_keycompare = t_compare;
    pt_hash_multimap->_pair_temp._bfun_mapkeycompare = t_compare;
    t_default_hash = t_hash != NULL ? t_hash : _hash_multimap_default_hash;
    /* initialize the pair */
    pair_init(&pt_hash_multimap->_pair_temp);
    /* initialize the hashtable */
    _hashtable_init(&pt_hash_multimap->_t_hashtable, t_bucketcount,
        t_default_hash, _hash_multimap_value_compare);
}

void hash_multimap_destroy(hash_multimap_t* pt_hash_multimap)
{
    _hash_multimap_destroy_auxiliary(pt_hash_multimap);
    free(pt_hash_multimap);
}

void hash_multimap_init_copy(
    hash_multimap_t* pt_hash_multimapdest, const hash_multimap_t* cpt_hash_multimapsrc)
{
    assert(pt_hash_multimapdest != NULL && cpt_hash_multimapsrc != NULL);
    hash_multimap_init_ex(pt_hash_multimapdest,
        hash_multimap_bucket_count(cpt_hash_multimapsrc),
        hash_multimap_hash(cpt_hash_multimapsrc),
        hash_multimap_key_comp(cpt_hash_multimapsrc));
    pt_hash_multimapdest->_bfun_keycompare = cpt_hash_multimapsrc->_bfun_keycompare;
    pt_hash_multimapdest->_bfun_valuecompare = cpt_hash_multimapsrc->_bfun_valuecompare;
    pt_hash_multimapdest->_pair_temp._bfun_mapkeycompare = cpt_hash_multimapsrc->_pair_temp._bfun_mapkeycompare;
    pt_hash_multimapdest->_pair_temp._bfun_mapvaluecompare = cpt_hash_multimapsrc->_pair_temp._bfun_mapvaluecompare;
    assert(_hash_multimap_same_pair_type_ex(
        &pt_hash_multimapdest->_pair_temp, &cpt_hash_multimapsrc->_pair_temp));

    if(!hash_multimap_empty(cpt_hash_multimapsrc))
    {
        hash_multimap_insert_range(pt_hash_multimapdest, 
            hash_multimap_begin(cpt_hash_multimapsrc), hash_multimap_end(cpt_hash_multimapsrc));
    }
}

void hash_multimap_init_copy_range(hash_multimap_t* pt_hash_multimapdest,
    hash_multimap_iterator_t t_begin, hash_multimap_iterator_t t_end)
{
    hash_multimap_init_copy_range_ex(pt_hash_multimapdest, t_begin, t_end, 0, NULL, NULL);
}

void hash_multimap_init_copy_range_ex(hash_multimap_t* pt_hash_multimapdest,
    hash_multimap_iterator_t t_begin, hash_multimap_iterator_t t_end, size_t t_bucketcount,
    unary_function_t t_hash, binary_function_t t_compare)
{
    unary_function_t t_default_hash = NULL;

    assert(pt_hash_multimapdest != NULL);
    assert(_GET_HASH_MULTIMAP_CONTAINER_TYPE(t_begin) == _HASH_MULTIMAP_CONTAINER &&
           _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_begin) == _BIDIRECTIONAL_ITERATOR &&
           _GET_HASH_MULTIMAP_CONTAINER_TYPE(t_end) == _HASH_MULTIMAP_CONTAINER &&
           _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_end) == _BIDIRECTIONAL_ITERATOR);
    assert(_GET_HASH_MULTIMAP_CONTAINER(t_begin) != pt_hash_multimapdest &&
           _GET_HASH_MULTIMAP_CONTAINER(t_end) != pt_hash_multimapdest &&
           _GET_HASH_MULTIMAP_CONTAINER(t_begin) == 
               _GET_HASH_MULTIMAP_CONTAINER(t_end));

    t_default_hash = t_hash != NULL ? t_hash : _hash_multimap_default_hash;
    hash_multimap_init_ex(pt_hash_multimapdest, t_bucketcount, t_default_hash, t_compare);

    if(!hash_multimap_empty(_GET_HASH_MULTIMAP_CONTAINER(t_begin)))
    {
        hash_multimap_insert_range(pt_hash_multimapdest, t_begin, t_end);
    }
}

void hash_multimap_assign(
    hash_multimap_t* pt_hash_multimapdest, const hash_multimap_t* cpt_hash_multimapsrc)
{
    assert(pt_hash_multimapdest != NULL && cpt_hash_multimapsrc != NULL);
    assert(_hash_multimap_same_pair_type_ex(
        &pt_hash_multimapdest->_pair_temp, &cpt_hash_multimapsrc->_pair_temp));

    hash_multimap_clear(pt_hash_multimapdest);
    if(!hash_multimap_empty(cpt_hash_multimapsrc))
    {
        hash_multimap_insert_range(pt_hash_multimapdest, 
            hash_multimap_begin(cpt_hash_multimapsrc), hash_multimap_end(cpt_hash_multimapsrc));
    }
}

void hash_multimap_swap(
    hash_multimap_t* pt_hash_multimapfirst, hash_multimap_t* pt_hash_multimapsecond)
{
    assert(pt_hash_multimapfirst != NULL && pt_hash_multimapsecond != NULL);
    assert(_hash_multimap_same_pair_type_ex(
        &pt_hash_multimapfirst->_pair_temp, &pt_hash_multimapsecond->_pair_temp));

    _hashtable_swap(
        &pt_hash_multimapfirst->_t_hashtable, &pt_hash_multimapsecond->_t_hashtable);
}

size_t hash_multimap_size(const hash_multimap_t* cpt_hash_multimap)
{
    assert(cpt_hash_multimap != NULL);

    return _hashtable_size(&cpt_hash_multimap->_t_hashtable);
}

bool_t hash_multimap_empty(const hash_multimap_t* cpt_hash_multimap)
{
    assert(cpt_hash_multimap != NULL);

    return _hashtable_empty(&cpt_hash_multimap->_t_hashtable);
}

size_t hash_multimap_max_size(const hash_multimap_t* cpt_hash_multimap)
{
    assert(cpt_hash_multimap != NULL);

    return _hashtable_max_size(&cpt_hash_multimap->_t_hashtable);
}

size_t hash_multimap_bucket_count(const hash_multimap_t* cpt_hash_multimap)
{
    assert(cpt_hash_multimap != NULL);

    return _hashtable_bucket_count(&cpt_hash_multimap->_t_hashtable);
}

unary_function_t hash_multimap_hash(const hash_multimap_t* cpt_hash_multimap)
{
    assert(cpt_hash_multimap != NULL);

    return _hashtable_hash(&cpt_hash_multimap->_t_hashtable);
}

binary_function_t hash_multimap_key_comp(const hash_multimap_t* cpt_hash_multimap)
{
    assert(cpt_hash_multimap != NULL);

    if (cpt_hash_multimap->_bfun_keycompare != NULL)
    {
        return cpt_hash_multimap->_bfun_keycompare;
    }
    else
    {
        return _GET_HASH_MULTIMAP_FIRST_TYPE_LESS_FUNCTION(cpt_hash_multimap);
    }
}

binary_function_t hash_multimap_value_comp(const hash_multimap_t* cpt_hash_multimap)
{
#ifdef NDEBUG
    void* pv_avoidwarning = (void*)cpt_hash_multimap;
    pv_avoidwarning = NULL;
#endif
    assert(cpt_hash_multimap != NULL);

    return _hash_multimap_value_compare;
}

void hash_multimap_resize(hash_multimap_t* pt_hash_multimap, size_t t_resize)
{
    assert(pt_hash_multimap != NULL);

    _hashtable_resize(&pt_hash_multimap->_t_hashtable, t_resize);
}

hash_multimap_iterator_t hash_multimap_begin(const hash_multimap_t* cpt_hash_multimap)
{
    hash_multimap_iterator_t t_newiterator;

    assert(cpt_hash_multimap != NULL);

    t_newiterator = _hashtable_begin(&cpt_hash_multimap->_t_hashtable);

    _GET_CONTAINER(t_newiterator) = (hash_multimap_t*)cpt_hash_multimap;
    _GET_HASH_MULTIMAP_CONTAINER_TYPE(t_newiterator) = _HASH_MULTIMAP_CONTAINER;
    _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

hash_multimap_iterator_t hash_multimap_end(const hash_multimap_t* cpt_hash_multimap)
{
    hash_multimap_iterator_t t_newiterator;

    assert(cpt_hash_multimap != NULL);

    t_newiterator = _hashtable_end(&cpt_hash_multimap->_t_hashtable);

    _GET_CONTAINER(t_newiterator) = (hash_multimap_t*)cpt_hash_multimap;
    _GET_HASH_MULTIMAP_CONTAINER_TYPE(t_newiterator) = _HASH_MULTIMAP_CONTAINER;
    _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

bool_t hash_multimap_equal(
    const hash_multimap_t* cpt_hash_multimapfirst, 
    const hash_multimap_t* cpt_hash_multimapsecond)
{
    assert(cpt_hash_multimapfirst != NULL && cpt_hash_multimapsecond != NULL);

    /* test hashtable */
    return _hashtable_equal(
        &cpt_hash_multimapfirst->_t_hashtable, &cpt_hash_multimapsecond->_t_hashtable);
}

bool_t hash_multimap_not_equal(
    const hash_multimap_t* cpt_hash_multimapfirst, 
    const hash_multimap_t* cpt_hash_multimapsecond)
{
    assert(cpt_hash_multimapfirst != NULL && cpt_hash_multimapsecond != NULL);

    return _hashtable_not_equal(
        &cpt_hash_multimapfirst->_t_hashtable, &cpt_hash_multimapsecond->_t_hashtable);
}

bool_t hash_multimap_less(
    const hash_multimap_t* cpt_hash_multimapfirst, 
    const hash_multimap_t* cpt_hash_multimapsecond)
{
    assert(cpt_hash_multimapfirst != NULL && cpt_hash_multimapsecond != NULL);

    return _hashtable_less(
        &cpt_hash_multimapfirst->_t_hashtable, &cpt_hash_multimapsecond->_t_hashtable);
}

bool_t hash_multimap_less_equal(
    const hash_multimap_t* cpt_hash_multimapfirst, 
    const hash_multimap_t* cpt_hash_multimapsecond)
{
    assert(cpt_hash_multimapfirst != NULL && cpt_hash_multimapsecond != NULL);

    return _hashtable_less_equal(
        &cpt_hash_multimapfirst->_t_hashtable, &cpt_hash_multimapsecond->_t_hashtable);
}

bool_t hash_multimap_greater(
    const hash_multimap_t* cpt_hash_multimapfirst, 
    const hash_multimap_t* cpt_hash_multimapsecond)
{
    assert(cpt_hash_multimapfirst != NULL && cpt_hash_multimapsecond != NULL);

    return _hashtable_greater(
        &cpt_hash_multimapfirst->_t_hashtable, &cpt_hash_multimapsecond->_t_hashtable);
}

bool_t hash_multimap_greater_equal(
    const hash_multimap_t* cpt_hash_multimapfirst, 
    const hash_multimap_t* cpt_hash_multimapsecond)
{
    assert(cpt_hash_multimapfirst != NULL && cpt_hash_multimapsecond != NULL);

    return _hashtable_greater_equal(
        &cpt_hash_multimapfirst->_t_hashtable, &cpt_hash_multimapsecond->_t_hashtable);
}

hash_multimap_iterator_t hash_multimap_insert(
    hash_multimap_t* pt_hash_multimap, const pair_t* cpt_pair)
{
    hash_multimap_iterator_t t_result;

    assert(pt_hash_multimap != NULL && cpt_pair != NULL);
    ((pair_t*)cpt_pair)->_bfun_mapkeycompare = pt_hash_multimap->_bfun_keycompare;
    ((pair_t*)cpt_pair)->_bfun_mapvaluecompare = pt_hash_multimap->_bfun_valuecompare;
    assert(_hash_multimap_same_pair_type_ex(&pt_hash_multimap->_pair_temp, cpt_pair));

    /* insert int hashtable */
    t_result = _hashtable_insert_equal(&pt_hash_multimap->_t_hashtable, cpt_pair);

    _GET_CONTAINER(t_result) = pt_hash_multimap;
    _GET_HASH_MULTIMAP_CONTAINER_TYPE(t_result) = _HASH_MULTIMAP_CONTAINER;
    _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_result) = _BIDIRECTIONAL_ITERATOR;

    return t_result;
}

void hash_multimap_insert_range(
    hash_multimap_t* pt_hash_multimap, 
    hash_multimap_iterator_t t_begin, hash_multimap_iterator_t t_end)
{
    hash_multimap_iterator_t t_iterator;

    assert(pt_hash_multimap != NULL);
    assert(_GET_HASH_MULTIMAP_CONTAINER_TYPE(t_begin) == _HASH_MULTIMAP_CONTAINER &&
           _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_begin) == _BIDIRECTIONAL_ITERATOR &&
           _GET_HASH_MULTIMAP_CONTAINER_TYPE(t_end) == _HASH_MULTIMAP_CONTAINER &&
           _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_end) == _BIDIRECTIONAL_ITERATOR);
    assert(_GET_HASH_MULTIMAP_CONTAINER(t_begin) != pt_hash_multimap &&
           _GET_HASH_MULTIMAP_CONTAINER(t_end) != pt_hash_multimap &&
           _GET_HASH_MULTIMAP_CONTAINER(t_begin) == 
               _GET_HASH_MULTIMAP_CONTAINER(t_end));

    for(t_iterator = t_begin;
        !iterator_equal(t_iterator, t_end);
        t_iterator = iterator_next(t_iterator))
    {
        hash_multimap_insert(pt_hash_multimap, (pair_t*)iterator_get_pointer(t_iterator));
    }
}

void hash_multimap_erase_pos(
    hash_multimap_t* pt_hash_multimap, hash_multimap_iterator_t t_pos)
{
    assert(pt_hash_multimap != NULL);
    assert(_GET_HASH_MULTIMAP_CONTAINER_TYPE(t_pos) == _HASH_MULTIMAP_CONTAINER &&
           _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_pos) == _BIDIRECTIONAL_ITERATOR &&
           _GET_HASH_MULTIMAP_CONTAINER(t_pos) == pt_hash_multimap);

    _hashtable_erase_pos(&pt_hash_multimap->_t_hashtable, t_pos);
}

void hash_multimap_erase_range(
    hash_multimap_t* pt_hash_multimap, 
    hash_multimap_iterator_t t_begin, hash_multimap_iterator_t t_end)
{
    assert(pt_hash_multimap != NULL);
    assert(_GET_HASH_MULTIMAP_CONTAINER_TYPE(t_begin) == _HASH_MULTIMAP_CONTAINER &&
           _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_begin) == _BIDIRECTIONAL_ITERATOR &&
           _GET_HASH_MULTIMAP_CONTAINER_TYPE(t_end) == _HASH_MULTIMAP_CONTAINER &&
           _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_end) == _BIDIRECTIONAL_ITERATOR);
    assert(_GET_HASH_MULTIMAP_CONTAINER(t_begin) == pt_hash_multimap &&
           _GET_HASH_MULTIMAP_CONTAINER(t_end) == pt_hash_multimap);

    _hashtable_erase_range(&pt_hash_multimap->_t_hashtable, t_begin, t_end);
}

void hash_multimap_clear(hash_multimap_t* pt_hash_multimap)
{
    assert(pt_hash_multimap != NULL);

    _hashtable_clear(&pt_hash_multimap->_t_hashtable);
}

/** local function implementation section **/

/** eof **/

