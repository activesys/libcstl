/*
 *  The implementation of hash_multimap.
 *  Copyright (C)  2008 - 2013  Wangbo
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
#include <cstl/chash_map.h>

#include "cstl_hash_multimap_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Initialize hash_multimap container.
 */
void hash_multimap_init(hash_multimap_t* phmmap_map)
{
    hash_multimap_init_ex(phmmap_map, 0, NULL, NULL);
}

/**
 * Initialize hash_multimap container with user define compare function.
 */
void hash_multimap_init_ex(hash_multimap_t* phmmap_map, size_t t_bucketcount, ufun_t ufun_hash, bfun_t bfun_compare)
{
    ufun_t ufun_default_hash = NULL;

    assert(phmmap_map != NULL);
    assert(_pair_is_created(&phmmap_map->_pair_temp));

    /* initialize the pair */
    pair_init(&phmmap_map->_pair_temp);
    phmmap_map->_bfun_keycompare = bfun_compare;
    phmmap_map->_pair_temp._bfun_mapkeycompare = bfun_compare;
    ufun_default_hash = ufun_hash != NULL ? ufun_hash : _hash_multimap_default_hash;

    /* initialize the hashtable */
    _hashtable_init(&phmmap_map->_t_hashtable, t_bucketcount, ufun_default_hash, _hash_multimap_value_compare);
}

/**
 * Destroy hash_multimap.
 */
void hash_multimap_destroy(hash_multimap_t* phmmap_map)
{
    _hash_multimap_destroy_auxiliary(phmmap_map);
    free(phmmap_map);
}

/**
 * Initialize hash_multimap container with hash_multimap.
 */
void hash_multimap_init_copy(hash_multimap_t* phmmap_dest, const hash_multimap_t* cphmmap_src)
{
    assert(phmmap_dest != NULL);
    assert(cphmmap_src != NULL);
    assert(_pair_is_created(&phmmap_dest->_pair_temp));
    assert(_pair_is_inited(&cphmmap_src->_pair_temp));

    hash_multimap_init_ex(phmmap_dest, hash_multimap_bucket_count(cphmmap_src), hash_multimap_hash(cphmmap_src), hash_multimap_key_comp(cphmmap_src));
    phmmap_dest->_bfun_keycompare = cphmmap_src->_bfun_keycompare;
    phmmap_dest->_bfun_valuecompare = cphmmap_src->_bfun_valuecompare;
    phmmap_dest->_pair_temp._bfun_mapkeycompare = cphmmap_src->_pair_temp._bfun_mapkeycompare;
    phmmap_dest->_pair_temp._bfun_mapvaluecompare = cphmmap_src->_pair_temp._bfun_mapvaluecompare;
    assert(_hash_multimap_same_pair_type_ex(&phmmap_dest->_pair_temp, &cphmmap_src->_pair_temp));

    if (!hash_multimap_empty(cphmmap_src)) {
        hash_multimap_insert_range(phmmap_dest, hash_multimap_begin(cphmmap_src), hash_multimap_end(cphmmap_src));
    }
}

/**
 * Initialize hash_multimap container with specific range.
 */
void hash_multimap_init_copy_range(hash_multimap_t* phmmap_dest, iterator_t it_begin, iterator_t it_end)
{
    hash_multimap_init_copy_range_ex(phmmap_dest, it_begin, it_end, 0, NULL, NULL);
}

/**
 * Initialize hash_multimap container with specific array.
 */
void hash_multimap_init_copy_array(hash_multimap_t* phmmap_dest, const void* cpv_array, size_t t_count)
{
    hash_multimap_init_copy_array_ex(phmmap_dest, cpv_array, t_count, 0, NULL, NULL);
}

/**
 * Initialize hash_multimap container with specific range and compare function.
 */
void hash_multimap_init_copy_range_ex(hash_multimap_t* phmmap_dest, iterator_t it_begin, iterator_t it_end,
    size_t t_bucketcount, ufun_t ufun_hash, bfun_t bfun_compare)
{
    ufun_t ufun_default_hash = NULL;

    assert(phmmap_dest != NULL);
    assert(_pair_is_created(&phmmap_dest->_pair_temp));
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));

    ufun_default_hash = ufun_hash != NULL ? ufun_hash : _hash_multimap_default_hash;
    hash_multimap_init_ex(phmmap_dest, t_bucketcount, ufun_default_hash, bfun_compare);
    hash_multimap_insert_range(phmmap_dest, it_begin, it_end);
}

/**
 * Initialize hash_multimap container with specific array and compare function.
 */
void hash_multimap_init_copy_array_ex(hash_multimap_t* phmmap_dest, const void* cpv_array, size_t t_count,
    size_t t_bucketcount, ufun_t ufun_hash, bfun_t bfun_compare)
{
    ufun_t ufun_default_hash = NULL;

    assert(phmmap_dest != NULL);
    assert(_pair_is_created(&phmmap_dest->_pair_temp));
    assert(cpv_array != NULL);

    ufun_default_hash = ufun_hash != NULL ? ufun_hash : _hash_multimap_default_hash;
    hash_multimap_init_ex(phmmap_dest, t_bucketcount, ufun_default_hash, bfun_compare);
    hash_multimap_insert_array(phmmap_dest, cpv_array, t_count);
}

/**
 * Assign hash_multimap container.
 */
void hash_multimap_assign(hash_multimap_t* phmmap_dest, const hash_multimap_t* cphmmap_src)
{
    assert(phmmap_dest != NULL);
    assert(cphmmap_src != NULL);
    assert(_pair_is_inited(&phmmap_dest->_pair_temp));
    assert(_pair_is_inited(&cphmmap_src->_pair_temp));
    assert(_hash_multimap_same_pair_type_ex(&phmmap_dest->_pair_temp, &cphmmap_src->_pair_temp));

    hash_multimap_clear(phmmap_dest);
    if (!hash_multimap_empty(cphmmap_src)) {
        hash_multimap_insert_range(phmmap_dest, hash_multimap_begin(cphmmap_src), hash_multimap_end(cphmmap_src));
    }
}

/**
 * Swap the datas of first hash_multimap and second hash_multimap.
 */
void hash_multimap_swap(hash_multimap_t* phmmap_first, hash_multimap_t* phmmap_second)
{
    assert(phmmap_first != NULL);
    assert(phmmap_second != NULL);
    assert(_pair_is_inited(&phmmap_first->_pair_temp));
    assert(_pair_is_inited(&phmmap_second->_pair_temp));
    assert(_hash_multimap_same_pair_type_ex(&phmmap_first->_pair_temp, &phmmap_second->_pair_temp));

    _hashtable_swap(&phmmap_first->_t_hashtable, &phmmap_second->_t_hashtable);
}

/**
 * Get the number of elements int the hash_multimap.
 */
size_t hash_multimap_size(const hash_multimap_t* cphmmap_map)
{
    assert(cphmmap_map != NULL);
    assert(_pair_is_inited(&cphmmap_map->_pair_temp));

    return _hashtable_size(&cphmmap_map->_t_hashtable);
}

/**
 * Test if an hash_multimap is empty.
 */
bool_t hash_multimap_empty(const hash_multimap_t* cphmmap_map)
{
    assert(cphmmap_map != NULL);
    assert(_pair_is_inited(&cphmmap_map->_pair_temp));

    return _hashtable_empty(&cphmmap_map->_t_hashtable);
}

/**
 * Get the maximum number of elements int the hash_multimap.
 */
size_t hash_multimap_max_size(const hash_multimap_t* cphmmap_map)
{
    assert(cphmmap_map != NULL);
    assert(_pair_is_inited(&cphmmap_map->_pair_temp));

    return _hashtable_max_size(&cphmmap_map->_t_hashtable);
}

/**
 * Get the bucket count of elements int the hash_multimap.
 */
size_t hash_multimap_bucket_count(const hash_multimap_t* cphmmap_map)
{
    assert(cphmmap_map != NULL);
    assert(_pair_is_inited(&cphmmap_map->_pair_temp));

    return _hashtable_bucket_count(&cphmmap_map->_t_hashtable);
}

/**
 * Return the hash function of value.
 */
ufun_t hash_multimap_hash(const hash_multimap_t* cphmmap_map)
{
    assert(cphmmap_map != NULL);
    assert(_pair_is_inited(&cphmmap_map->_pair_temp));

    return _hashtable_hash(&cphmmap_map->_t_hashtable);
}

/**
 * Return the compare function of key.
 */
bfun_t hash_multimap_key_comp(const hash_multimap_t* cphmmap_map)
{
    assert(cphmmap_map != NULL);
    assert(_pair_is_inited(&cphmmap_map->_pair_temp));

    if (cphmmap_map->_bfun_keycompare != NULL) {
        return cphmmap_map->_bfun_keycompare;
    } else {
        return _GET_HASH_MULTIMAP_FIRST_TYPE_LESS_FUNCTION(cphmmap_map);
    }
}

/**
 * Return the compare function of value.
 */
bfun_t hash_multimap_value_comp(const hash_multimap_t* cphmmap_map)
{
#ifdef NDEBUG
    void* pv_avoidwarning = (void*)cphmmap_map;
    pv_avoidwarning = NULL;
#endif
    assert(cphmmap_map != NULL);
    assert(_pair_is_inited(&cphmmap_map->_pair_temp));

    return _hash_multimap_value_compare;
}

/**
 * Resize bucket count of hash map.
 */
void hash_multimap_resize(hash_multimap_t* phmmap_map, size_t t_resize)
{
    assert(phmmap_map != NULL);
    assert(_pair_is_inited(&phmmap_map->_pair_temp));

    _hashtable_resize(&phmmap_map->_t_hashtable, t_resize);
}

/**
 * Return an iterator that addresses the first element in the hash_multimap.
 */
hash_multimap_iterator_t hash_multimap_begin(const hash_multimap_t* cphmmap_map)
{
    hash_multimap_iterator_t it_begin;

    assert(cphmmap_map != NULL);
    assert(_pair_is_inited(&cphmmap_map->_pair_temp));

    it_begin = _hashtable_begin(&cphmmap_map->_t_hashtable);

    _ITERATOR_CONTAINER(it_begin) = (hash_multimap_t*)cphmmap_map;
    _HASH_MULTIMAP_ITERATOR_CONTAINER_TYPE(it_begin) = _HASH_MULTIMAP_CONTAINER;
    _HASH_MULTIMAP_ITERATOR_ITERATOR_TYPE(it_begin) = _BIDIRECTIONAL_ITERATOR;

    return it_begin;
}

/**
 * Return an iterator that addresses the location succeeding the last element in the hash_multimap.
 */
hash_multimap_iterator_t hash_multimap_end(const hash_multimap_t* cphmmap_map)
{
    hash_multimap_iterator_t it_end;

    assert(cphmmap_map != NULL);
    assert(_pair_is_inited(&cphmmap_map->_pair_temp));

    it_end = _hashtable_end(&cphmmap_map->_t_hashtable);

    _ITERATOR_CONTAINER(it_end) = (hash_multimap_t*)cphmmap_map;
    _HASH_MULTIMAP_ITERATOR_CONTAINER_TYPE(it_end) = _HASH_MULTIMAP_CONTAINER;
    _HASH_MULTIMAP_ITERATOR_ITERATOR_TYPE(it_end) = _BIDIRECTIONAL_ITERATOR;

    return it_end;
}

/**
 * Tests if the two hash_multimap are equal.
 */
bool_t hash_multimap_equal(const hash_multimap_t* cphmmap_first, const hash_multimap_t* cphmmap_second)
{
    assert(cphmmap_first != NULL);
    assert(cphmmap_second != NULL);
    assert(_pair_is_inited(&cphmmap_first->_pair_temp));
    assert(_pair_is_inited(&cphmmap_second->_pair_temp));

    if (cphmmap_first->_bfun_keycompare != cphmmap_second->_bfun_keycompare) {
        return false;
    }

    /* test hashtable */
    return _hashtable_equal(&cphmmap_first->_t_hashtable, &cphmmap_second->_t_hashtable);
}

/**
 * Tests if the two hash_multimap are not equal.
 */
bool_t hash_multimap_not_equal(const hash_multimap_t* cphmmap_first, const hash_multimap_t* cphmmap_second)
{
    assert(cphmmap_first != NULL);
    assert(cphmmap_second != NULL);
    assert(_pair_is_inited(&cphmmap_first->_pair_temp));
    assert(_pair_is_inited(&cphmmap_second->_pair_temp));

    if (cphmmap_first->_bfun_keycompare != cphmmap_second->_bfun_keycompare) {
        return true;
    }

    return _hashtable_not_equal(&cphmmap_first->_t_hashtable, &cphmmap_second->_t_hashtable);
}

/**
 * Tests if the first hash_multimap is less than the second hash_multimap.
 */
bool_t hash_multimap_less(const hash_multimap_t* cphmmap_first, const hash_multimap_t* cphmmap_second)
{
    assert(cphmmap_first != NULL);
    assert(cphmmap_second != NULL);
    assert(_pair_is_inited(&cphmmap_first->_pair_temp));
    assert(_pair_is_inited(&cphmmap_second->_pair_temp));
    assert(_hash_multimap_same_pair_type_ex(&cphmmap_first->_pair_temp, &cphmmap_second->_pair_temp));

    return _hashtable_less(&cphmmap_first->_t_hashtable, &cphmmap_second->_t_hashtable);
}

/**
 * Tests if the first hash_multimap is less than or equal to the second hash_multimap.
 */
bool_t hash_multimap_less_equal(const hash_multimap_t* cphmmap_first, const hash_multimap_t* cphmmap_second)
{
    assert(cphmmap_first != NULL);
    assert(cphmmap_second != NULL);
    assert(_pair_is_inited(&cphmmap_first->_pair_temp));
    assert(_pair_is_inited(&cphmmap_second->_pair_temp));
    assert(_hash_multimap_same_pair_type_ex(&cphmmap_first->_pair_temp, &cphmmap_second->_pair_temp));

    return _hashtable_less_equal(&cphmmap_first->_t_hashtable, &cphmmap_second->_t_hashtable);
}

/**
 * Tests if the first hash_multimap is greater than the second hash_multimap.
 */
bool_t hash_multimap_greater(const hash_multimap_t* cphmmap_first, const hash_multimap_t* cphmmap_second)
{
    assert(cphmmap_first != NULL);
    assert(cphmmap_second != NULL);
    assert(_pair_is_inited(&cphmmap_first->_pair_temp));
    assert(_pair_is_inited(&cphmmap_second->_pair_temp));
    assert(_hash_multimap_same_pair_type_ex(&cphmmap_first->_pair_temp, &cphmmap_second->_pair_temp));

    return _hashtable_greater(&cphmmap_first->_t_hashtable, &cphmmap_second->_t_hashtable);
}

/**
 * Tests if the first hash_multimap is greater than or equal to the second hash_multimap.
 */
bool_t hash_multimap_greater_equal(const hash_multimap_t* cphmmap_first, const hash_multimap_t* cphmmap_second)
{
    assert(cphmmap_first != NULL);
    assert(cphmmap_second != NULL);
    assert(_pair_is_inited(&cphmmap_first->_pair_temp));
    assert(_pair_is_inited(&cphmmap_second->_pair_temp));
    assert(_hash_multimap_same_pair_type_ex(&cphmmap_first->_pair_temp, &cphmmap_second->_pair_temp));

    return _hashtable_greater_equal(&cphmmap_first->_t_hashtable, &cphmmap_second->_t_hashtable);
}

/**
 * Inserts an unique element into a hash_multimap.
 */
hash_multimap_iterator_t hash_multimap_insert(hash_multimap_t* phmmap_map, const pair_t* cppair_pair)
{
    hash_multimap_iterator_t it_iter;

    assert(phmmap_map != NULL);
    assert(cppair_pair != NULL);
    assert(_pair_is_inited(&phmmap_map->_pair_temp));
    assert(_pair_is_inited(cppair_pair));

    ((pair_t*)cppair_pair)->_bfun_mapkeycompare = phmmap_map->_bfun_keycompare;
    ((pair_t*)cppair_pair)->_bfun_mapvaluecompare = phmmap_map->_bfun_valuecompare;
    assert(_hash_multimap_same_pair_type_ex(&phmmap_map->_pair_temp, cppair_pair));

    /* insert int hashtable */
    it_iter = _hashtable_insert_equal(&phmmap_map->_t_hashtable, cppair_pair);

    _ITERATOR_CONTAINER(it_iter) = phmmap_map;
    _HASH_MULTIMAP_ITERATOR_CONTAINER_TYPE(it_iter) = _HASH_MULTIMAP_CONTAINER;
    _HASH_MULTIMAP_ITERATOR_ITERATOR_TYPE(it_iter) = _BIDIRECTIONAL_ITERATOR;

    return it_iter;
}

/**
 * Inserts an range of unique element into a hash_multimap.
 */
void hash_multimap_insert_range(hash_multimap_t* phmmap_map, iterator_t it_begin, iterator_t it_end)
{
    iterator_t it_iter;

    assert(phmmap_map != NULL);
    assert(_pair_is_inited(&phmmap_map->_pair_temp));
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));

    for (it_iter = it_begin; !iterator_equal(it_iter, it_end); it_iter = iterator_next(it_iter)) {
        assert(_hash_multimap_same_pair_type(&phmmap_map->_pair_temp, (pair_t*)iterator_get_pointer(it_iter)));
        hash_multimap_insert(phmmap_map, (pair_t*)iterator_get_pointer(it_iter));
    }
}

/**
 * Inserts an array of unique element into a hash_multimap.
 */
void hash_multimap_insert_array(hash_multimap_t* phmmap_map, const void* cpv_array, size_t t_count)
{
    size_t i = 0;

    assert(phmmap_map != NULL);
    assert(_pair_is_inited(&phmmap_map->_pair_temp));
    assert(cpv_array != NULL);

    for (i = 0; i < t_count; ++i) {
        assert(_hash_multimap_same_pair_type(&phmmap_map->_pair_temp, ((pair_t**)cpv_array)[i]));
        hash_multimap_insert(phmmap_map, ((pair_t**)cpv_array)[i]);
    }
}

/**
 * Erase an element in an hash_multimap from specificed position.
 */
void hash_multimap_erase_pos(hash_multimap_t* phmmap_map, hash_multimap_iterator_t it_pos)
{
    assert(phmmap_map != NULL);
    assert(_pair_is_inited(&phmmap_map->_pair_temp));
    assert(_HASH_MULTIMAP_ITERATOR_CONTAINER_TYPE(it_pos) == _HASH_MULTIMAP_CONTAINER);
    assert(_HASH_MULTIMAP_ITERATOR_ITERATOR_TYPE(it_pos) == _BIDIRECTIONAL_ITERATOR);
    assert(_HASH_MULTIMAP_ITERATOR_CONTAINER(it_pos) == phmmap_map);

    _hashtable_erase_pos(&phmmap_map->_t_hashtable, it_pos);
}

/**
 * Erase a range of element in an hash_multimap.
 */
void hash_multimap_erase_range(hash_multimap_t* phmmap_map, hash_multimap_iterator_t it_begin, hash_multimap_iterator_t it_end)
{
    assert(phmmap_map != NULL);
    assert(_pair_is_inited(&phmmap_map->_pair_temp));
    assert(_HASH_MULTIMAP_ITERATOR_CONTAINER_TYPE(it_begin) == _HASH_MULTIMAP_CONTAINER);
    assert(_HASH_MULTIMAP_ITERATOR_ITERATOR_TYPE(it_begin) == _BIDIRECTIONAL_ITERATOR);
    assert(_HASH_MULTIMAP_ITERATOR_CONTAINER_TYPE(it_end) == _HASH_MULTIMAP_CONTAINER);
    assert(_HASH_MULTIMAP_ITERATOR_ITERATOR_TYPE(it_end) == _BIDIRECTIONAL_ITERATOR);
    assert(_HASH_MULTIMAP_ITERATOR_CONTAINER(it_begin) == phmmap_map);
    assert(_HASH_MULTIMAP_ITERATOR_CONTAINER(it_end) == phmmap_map);

    _hashtable_erase_range(&phmmap_map->_t_hashtable, it_begin, it_end);
}

/**
 * Erases all the elements of an hash_multimap.
 */
void hash_multimap_clear(hash_multimap_t* phmmap_map)
{
    assert(phmmap_map != NULL);
    assert(_pair_is_inited(&phmmap_map->_pair_temp));

    _hashtable_clear(&phmmap_map->_t_hashtable);
}

/** local function implementation section **/

/** eof **/

