/*
 *  The implementation of hash_map.
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

#include "cstl_hash_map_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Initialize hash_map container.
 */
void hash_map_init(hash_map_t* phmap_map)
{
    hash_map_init_ex(phmap_map, 0, NULL, NULL);
}

/**
 * Initialize hash_map container with user define compare function.
 */
void hash_map_init_ex(hash_map_t* phmap_map, size_t t_bucketcount, ufun_t ufun_hash, bfun_t bfun_compare)
{
    ufun_t ufun_default_hash = NULL;

    assert(phmap_map != NULL);
    assert(_pair_is_created(&phmap_map->_pair_temp));

    /* initialize the pair */
    pair_init(&phmap_map->_pair_temp);

    phmap_map->_bfun_keycompare = bfun_compare;
    phmap_map->_pair_temp._bfun_mapkeycompare = bfun_compare;
    ufun_default_hash = ufun_hash != NULL ? ufun_hash : _hash_map_default_hash;

    /* initialize the hashtable */
    _hashtable_init(&phmap_map->_t_hashtable, t_bucketcount, ufun_default_hash, _hash_map_value_compare);
}

/**
 * Destroy hash_map.
 */
void hash_map_destroy(hash_map_t* phmap_map)
{
    _hash_map_destroy_auxiliary(phmap_map);
    free(phmap_map);
}

/**
 * Initialize hash_map container with hash_map.
 */
void hash_map_init_copy(hash_map_t* phmap_dest, const hash_map_t* cphmap_src)
{
    assert(phmap_dest != NULL);
    assert(cphmap_src != NULL);
    assert(_pair_is_created(&phmap_dest->_pair_temp));
    assert(_pair_is_inited(&cphmap_src->_pair_temp));

    hash_map_init_ex(phmap_dest, hash_map_bucket_count(cphmap_src), hash_map_hash(cphmap_src), hash_map_key_comp(cphmap_src));
    phmap_dest->_bfun_keycompare = cphmap_src->_bfun_keycompare;
    phmap_dest->_bfun_valuecompare = cphmap_src->_bfun_valuecompare;
    phmap_dest->_pair_temp._bfun_mapkeycompare = cphmap_src->_pair_temp._bfun_mapkeycompare;
    phmap_dest->_pair_temp._bfun_mapvaluecompare = cphmap_src->_pair_temp._bfun_mapvaluecompare;
    assert(_hash_map_same_pair_type_ex(&phmap_dest->_pair_temp, &cphmap_src->_pair_temp));

    if (!hash_map_empty(cphmap_src)) {
        hash_map_insert_range(phmap_dest, hash_map_begin(cphmap_src), hash_map_end(cphmap_src));
    }
}

/**
 * Initialize hash_map container with specific range.
 */
void hash_map_init_copy_range(hash_map_t* phmap_dest, iterator_t it_begin, iterator_t it_end)
{
    hash_map_init_copy_range_ex(phmap_dest, it_begin, it_end, 0, NULL, NULL);
}

/**
 * Initialize hash_map container with specific array.
 */
void hash_map_init_copy_array(hash_map_t* phmap_dest, const void* cpv_array, size_t t_count)
{
    hash_map_init_copy_array_ex(phmap_dest, cpv_array, t_count, 0, NULL, NULL);
}

/**
 * Initialize hash_map container with specific range and compare function.
 */
void hash_map_init_copy_range_ex(hash_map_t* phmap_dest, iterator_t it_begin, iterator_t it_end,
    size_t t_bucketcount, ufun_t ufun_hash, bfun_t bfun_compare)
{
    ufun_t ufun_default_hash = NULL;

    assert(phmap_dest != NULL);
    assert(_pair_is_created(&phmap_dest->_pair_temp));
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));

    ufun_default_hash = ufun_hash != NULL ? ufun_hash : _hash_map_default_hash;
    hash_map_init_ex(phmap_dest, t_bucketcount, ufun_default_hash, bfun_compare);
    hash_map_insert_range(phmap_dest, it_begin, it_end);
}

/**
 * Initialize hash_map container with specific array and compare function.
 */
void hash_map_init_copy_array_ex(hash_map_t* phmap_dest, const void* cpv_array, size_t t_count,
    size_t t_bucketcount, ufun_t ufun_hash, bfun_t bfun_compare)
{
    ufun_t ufun_default_hash = NULL;

    assert(phmap_dest != NULL);
    assert(_pair_is_created(&phmap_dest->_pair_temp));
    assert(cpv_array != NULL);

    ufun_default_hash = ufun_hash != NULL ? ufun_hash : _hash_map_default_hash;
    hash_map_init_ex(phmap_dest, t_bucketcount, ufun_default_hash, bfun_compare);
    hash_map_insert_array(phmap_dest, cpv_array, t_count);
}

/**
 * Assign hash_map container.
 */
void hash_map_assign(hash_map_t* phmap_dest, const hash_map_t* cphmap_src)
{
    assert(phmap_dest != NULL);
    assert(cphmap_src != NULL);
    assert(_pair_is_inited(&phmap_dest->_pair_temp));
    assert(_pair_is_inited(&cphmap_src->_pair_temp));
    assert(_hash_map_same_pair_type_ex(&phmap_dest->_pair_temp, &cphmap_src->_pair_temp));

    hash_map_clear(phmap_dest);
    if (!hash_map_empty(cphmap_src)) {
        hash_map_insert_range(phmap_dest, hash_map_begin(cphmap_src), hash_map_end(cphmap_src));
    }
}

/**
 * Swap the datas of first hash_map and second hash_map.
 */
void hash_map_swap(hash_map_t* phmap_first, hash_map_t* phmap_second)
{
    assert(phmap_first != NULL);
    assert(phmap_second != NULL);
    assert(_pair_is_inited(&phmap_first->_pair_temp));
    assert(_pair_is_inited(&phmap_second->_pair_temp));
    assert(_hash_map_same_pair_type_ex(&phmap_first->_pair_temp, &phmap_second->_pair_temp));

    _hashtable_swap(&phmap_first->_t_hashtable, &phmap_second->_t_hashtable);
}

/**
 * Get the number of elements int the hash_map.
 */
size_t hash_map_size(const hash_map_t* cphmap_map)
{
    assert(cphmap_map != NULL);
    assert(_pair_is_inited(&cphmap_map->_pair_temp));

    return _hashtable_size(&cphmap_map->_t_hashtable);
}

/**
 * Test if an hash_map is empty.
 */
bool_t hash_map_empty(const hash_map_t* cphmap_map)
{
    assert(cphmap_map != NULL);
    assert(_pair_is_inited(&cphmap_map->_pair_temp));

    return _hashtable_empty(&cphmap_map->_t_hashtable);
}

/**
 * Get the maximum number of elements int the hash_map.
 */
size_t hash_map_max_size(const hash_map_t* cphmap_map)
{
    assert(cphmap_map != NULL);
    assert(_pair_is_inited(&cphmap_map->_pair_temp));

    return _hashtable_max_size(&cphmap_map->_t_hashtable);
}

/**
 * Get the bucket count of elements int the hash_map.
 */
size_t hash_map_bucket_count(const hash_map_t* cphmap_map)
{
    assert(cphmap_map != NULL);
    assert(_pair_is_inited(&cphmap_map->_pair_temp));

    return _hashtable_bucket_count(&cphmap_map->_t_hashtable);
}

/**
 * Return the hash function of value.
 */
ufun_t hash_map_hash(const hash_map_t* cphmap_map)
{
    assert(cphmap_map != NULL);
    assert(_pair_is_inited(&cphmap_map->_pair_temp));

    return _hashtable_hash(&cphmap_map->_t_hashtable);
}

/**
 * Return the compare function of key.
 */
bfun_t hash_map_key_comp(const hash_map_t* cphmap_map)
{
    assert(cphmap_map != NULL);
    assert(_pair_is_inited(&cphmap_map->_pair_temp));

    if (cphmap_map->_bfun_keycompare != NULL) {
        return cphmap_map->_bfun_keycompare;
    } else {
        return _GET_HASH_MAP_FIRST_TYPE_LESS_FUNCTION(cphmap_map);
    }
}

/**
 * Return the compare function of value.
 */
bfun_t hash_map_value_comp(const hash_map_t* cphmap_map)
{
#ifdef NDEBUG
    void* pv_avoidwarning = (void*)cphmap_map;
    pv_avoidwarning = NULL;
#endif 
    assert(cphmap_map != NULL);
    assert(_pair_is_inited(&cphmap_map->_pair_temp));

    return _hash_map_value_compare;
}

/**
 * Resize bucket count of hash map.
 */
void hash_map_resize(hash_map_t* phmap_map, size_t t_resize)
{
    assert(phmap_map != NULL);
    assert(_pair_is_inited(&phmap_map->_pair_temp));

    _hashtable_resize(&phmap_map->_t_hashtable, t_resize);
}

/**
 * Return an iterator that addresses the first element in the hash_map.
 */
hash_map_iterator_t hash_map_begin(const hash_map_t* cphmap_map)
{
    hash_map_iterator_t it_begin;

    assert(cphmap_map != NULL);
    assert(_pair_is_inited(&cphmap_map->_pair_temp));

    it_begin = _hashtable_begin(&cphmap_map->_t_hashtable);

    _ITERATOR_CONTAINER(it_begin) = (hash_map_t*)cphmap_map;
    _HASH_MAP_ITERATOR_CONTAINER_TYPE(it_begin) = _HASH_MAP_CONTAINER;
    _HASH_MAP_ITERATOR_ITERATOR_TYPE(it_begin) = _BIDIRECTIONAL_ITERATOR;

    return it_begin;
}

/**
 * Return an iterator that addresses the location succeeding the last element in the hash_map.
 */
hash_map_iterator_t hash_map_end(const hash_map_t* cphmap_map)
{
    hash_map_iterator_t it_end;

    assert(cphmap_map != NULL);
    assert(_pair_is_inited(&cphmap_map->_pair_temp));

    it_end = _hashtable_end(&cphmap_map->_t_hashtable);

    _ITERATOR_CONTAINER(it_end) = (hash_map_t*)cphmap_map;
    _HASH_MAP_ITERATOR_CONTAINER_TYPE(it_end) = _HASH_MAP_CONTAINER;
    _HASH_MAP_ITERATOR_ITERATOR_TYPE(it_end) = _BIDIRECTIONAL_ITERATOR;

    return it_end;
}

/**
 * Tests if the two hash_map are equal.
 */
bool_t hash_map_equal(const hash_map_t* cphmap_first, const hash_map_t* cphmap_second)
{
    assert(cphmap_first != NULL);
    assert(cphmap_second != NULL);
    assert(_pair_is_inited(&cphmap_first->_pair_temp));
    assert(_pair_is_inited(&cphmap_second->_pair_temp));

    if (cphmap_first->_bfun_keycompare != cphmap_second->_bfun_keycompare) {
        return false;
    }

    return _hashtable_equal(&cphmap_first->_t_hashtable, &cphmap_second->_t_hashtable);
}

/**
 * Tests if the two hash_map are not equal.
 */
bool_t hash_map_not_equal(const hash_map_t* cphmap_first, const hash_map_t* cphmap_second)
{
    assert(cphmap_first != NULL);
    assert(cphmap_second != NULL);
    assert(_pair_is_inited(&cphmap_first->_pair_temp));
    assert(_pair_is_inited(&cphmap_second->_pair_temp));

    if (cphmap_first->_bfun_keycompare != cphmap_second->_bfun_keycompare) {
        return true;
    }

    return _hashtable_not_equal(&cphmap_first->_t_hashtable, &cphmap_second->_t_hashtable);
}

/**
 * Tests if the first hash_map is less than the second hash_map.
 */
bool_t hash_map_less(const hash_map_t* cphmap_first, const hash_map_t* cphmap_second)
{
    assert(cphmap_first != NULL);
    assert(cphmap_second != NULL);
    assert(_pair_is_inited(&cphmap_first->_pair_temp));
    assert(_pair_is_inited(&cphmap_second->_pair_temp));
    assert(_hash_map_same_pair_type_ex(&cphmap_first->_pair_temp, &cphmap_second->_pair_temp));

    return _hashtable_less(&cphmap_first->_t_hashtable, &cphmap_second->_t_hashtable);
}

/**
 * Tests if the first hash_map is less than or equal to the second hash_map.
 */
bool_t hash_map_less_equal(const hash_map_t* cphmap_first, const hash_map_t* cphmap_second)
{
    assert(cphmap_first != NULL);
    assert(cphmap_second != NULL);
    assert(_pair_is_inited(&cphmap_first->_pair_temp));
    assert(_pair_is_inited(&cphmap_second->_pair_temp));
    assert(_hash_map_same_pair_type_ex(&cphmap_first->_pair_temp, &cphmap_second->_pair_temp));

    return _hashtable_less_equal(&cphmap_first->_t_hashtable, &cphmap_second->_t_hashtable);
}

/**
 * Tests if the first hash_map is greater than the second hash_map.
 */
bool_t hash_map_greater(const hash_map_t* cphmap_first, const hash_map_t* cphmap_second)
{
    assert(cphmap_first != NULL);
    assert(cphmap_second != NULL);
    assert(_pair_is_inited(&cphmap_first->_pair_temp));
    assert(_pair_is_inited(&cphmap_second->_pair_temp));
    assert(_hash_map_same_pair_type_ex(&cphmap_first->_pair_temp, &cphmap_second->_pair_temp));

    return _hashtable_greater(&cphmap_first->_t_hashtable, &cphmap_second->_t_hashtable);
}

/**
 * Tests if the first hash_map is greater than or equal to the second hash_map.
 */
bool_t hash_map_greater_equal(const hash_map_t* cphmap_first, const hash_map_t* cphmap_second)
{
    assert(cphmap_first != NULL);
    assert(cphmap_second != NULL);
    assert(_pair_is_inited(&cphmap_first->_pair_temp));
    assert(_pair_is_inited(&cphmap_second->_pair_temp));
    assert(_hash_map_same_pair_type_ex(&cphmap_first->_pair_temp, &cphmap_second->_pair_temp));

    return _hashtable_greater_equal(&cphmap_first->_t_hashtable, &cphmap_second->_t_hashtable);
}

/**
 * Inserts an unique element into a hash_map.
 */
hash_map_iterator_t hash_map_insert(hash_map_t* phmap_map, const pair_t* cppair_pair)
{
    hash_map_iterator_t it_iter;

    assert(phmap_map != NULL);
    assert(cppair_pair != NULL);
    assert(_pair_is_inited(&phmap_map->_pair_temp));
    assert(_pair_is_inited(cppair_pair));

    /* set key less and value less function */
    ((pair_t*)cppair_pair)->_bfun_mapkeycompare = phmap_map->_bfun_keycompare;
    ((pair_t*)cppair_pair)->_bfun_mapvaluecompare = phmap_map->_bfun_valuecompare;
    assert(_hash_map_same_pair_type_ex(&phmap_map->_pair_temp, cppair_pair));

    /* insert int hashtable */
    it_iter = _hashtable_insert_unique(&phmap_map->_t_hashtable, cppair_pair);

    _ITERATOR_CONTAINER(it_iter) = phmap_map;
    _HASH_MAP_ITERATOR_CONTAINER_TYPE(it_iter) = _HASH_MAP_CONTAINER;
    _HASH_MAP_ITERATOR_ITERATOR_TYPE(it_iter) = _BIDIRECTIONAL_ITERATOR;

    return it_iter;
}

/**
 * Inserts an range of unique element into a hash_map.
 */
void hash_map_insert_range(hash_map_t* phmap_map, iterator_t it_begin, iterator_t it_end)
{
    iterator_t it_iter;

    assert(phmap_map != NULL);
    assert(_pair_is_inited(&phmap_map->_pair_temp));
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));

    for (it_iter = it_begin; !iterator_equal(it_iter, it_end); it_iter = iterator_next(it_iter)) {
        assert(_hash_map_same_pair_type(&phmap_map->_pair_temp, (pair_t*)iterator_get_pointer(it_iter)));
        hash_map_insert(phmap_map, (pair_t*)iterator_get_pointer(it_iter));
    }
}

/**
 * Inserts an array of unique element into a hash_map.
 */
void hash_map_insert_array(hash_map_t* phmap_map, const void* cpv_array, size_t t_count)
{
    size_t i = 0;

    assert(phmap_map != NULL);
    assert(_pair_is_inited(&phmap_map->_pair_temp));
    assert(cpv_array != NULL);

    for (i = 0; i < t_count; ++i) {
        assert(_hash_map_same_pair_type(&phmap_map->_pair_temp, ((pair_t**)cpv_array)[i]));
        hash_map_insert(phmap_map, ((pair_t**)cpv_array)[i]);
    }
}

/*
 * Erase an element in an hash_map from specificed position.
 */
void hash_map_erase_pos(hash_map_t* phmap_map, hash_map_iterator_t it_pos)
{
    assert(phmap_map != NULL);
    assert(_pair_is_inited(&phmap_map->_pair_temp));
    assert(_HASH_MAP_ITERATOR_CONTAINER_TYPE(it_pos) == _HASH_MAP_CONTAINER);
    assert(_HASH_MAP_ITERATOR_ITERATOR_TYPE(it_pos) == _BIDIRECTIONAL_ITERATOR);
    assert(_HASH_MAP_ITERATOR_CONTAINER(it_pos) == phmap_map);

    _hashtable_erase_pos(&phmap_map->_t_hashtable, it_pos);
}

/*
 * Erase a range of element in an hash_map.
 */
void hash_map_erase_range(hash_map_t* phmap_map, hash_map_iterator_t it_begin, hash_map_iterator_t it_end)
{
    assert(phmap_map != NULL);
    assert(_pair_is_inited(&phmap_map->_pair_temp));
    assert(_HASH_MAP_ITERATOR_CONTAINER_TYPE(it_begin) == _HASH_MAP_CONTAINER);
    assert(_HASH_MAP_ITERATOR_ITERATOR_TYPE(it_begin) == _BIDIRECTIONAL_ITERATOR);
    assert(_HASH_MAP_ITERATOR_CONTAINER_TYPE(it_end) == _HASH_MAP_CONTAINER);
    assert(_HASH_MAP_ITERATOR_ITERATOR_TYPE(it_end) == _BIDIRECTIONAL_ITERATOR);
    assert(_HASH_MAP_ITERATOR_CONTAINER(it_begin) == phmap_map);
    assert(_HASH_MAP_ITERATOR_CONTAINER(it_end) == phmap_map);

    _hashtable_erase_range(&phmap_map->_t_hashtable, it_begin, it_end);
}

/**
 * Erases all the elements of an hash_map.
 */
void hash_map_clear(hash_map_t* phmap_map)
{
    assert(phmap_map != NULL);
    assert(_pair_is_inited(&phmap_map->_pair_temp));

    _hashtable_clear(&phmap_map->_t_hashtable);
}

/** local function implementation section **/

/** eof **/

