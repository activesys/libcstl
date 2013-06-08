/*
 *  The implementation of hash_multiset.
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
#include <cstl/chash_set.h>

#include "cstl_hash_multiset_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Initialize hash_multiset container.
 */
void hash_multiset_init(hash_multiset_t* phmset_set)
{
    assert(phmset_set != NULL);

    hash_multiset_init_ex(phmset_set, 0, NULL, NULL);
}

/**
 * Initialize hash_multiset container with user define compare function.
 */
void hash_multiset_init_ex(
    hash_multiset_t* phmset_set, size_t t_bucketcount, ufun_t ufun_hash, bfun_t bfun_compare)
{
    assert(phmset_set != NULL);

    _hashtable_init(&phmset_set->_t_hashtable, t_bucketcount, ufun_hash, bfun_compare);
}

/**
 * Destroy hash_multiset.
 */
void hash_multiset_destroy(hash_multiset_t* phmset_set)
{
    _hash_multiset_destroy_auxiliary(phmset_set);
    free(phmset_set);
}

/**
 * Initialize hash_multiset container with hash_multiset.
 */
void hash_multiset_init_copy(hash_multiset_t* phmset_dest, const hash_multiset_t* cphmset_src)
{
    assert(phmset_dest != NULL);
    assert(cphmset_src != NULL);

    _hashtable_init_copy(&phmset_dest->_t_hashtable, &cphmset_src->_t_hashtable);
}

/**
 * Initialize hash_multiset container with specific range.
 */
void hash_multiset_init_copy_range(hash_multiset_t* phmset_dest, iterator_t it_begin, iterator_t it_end)
{
    hash_multiset_init_copy_range_ex(phmset_dest, it_begin, it_end, 0, NULL, NULL);
}

/**
 * Initialize hash_multiset container with specific array.
 */
void hash_multiset_init_copy_array(hash_multiset_t* phmset_dest, const void* cpv_array, size_t t_count)
{
    hash_multiset_init_copy_array_ex(phmset_dest, cpv_array, t_count, 0, NULL, NULL);
}

/**
 * Initialize hash_multiset container with specific range and compare function.
 */
void hash_multiset_init_copy_range_ex(hash_multiset_t* phmset_dest, iterator_t it_begin, iterator_t it_end,
    size_t t_bucketcount, ufun_t ufun_hash, bfun_t bfun_compare)
{
    assert(phmset_dest != NULL);
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));

    _hashtable_init_copy_equal_range(&phmset_dest->_t_hashtable, it_begin, it_end, t_bucketcount, ufun_hash, bfun_compare);
}

/**
 * Initialize hash_multiset container with specific array and compare function.
 */
void hash_multiset_init_copy_array_ex(hash_multiset_t* phmset_dest, const void* cpv_array, size_t t_count,
    size_t t_bucketcount, ufun_t ufun_hash, bfun_t bfun_compare)
{
    assert(phmset_dest != NULL);
    assert(cpv_array != NULL);

    _hashtable_init_copy_equal_array(&phmset_dest->_t_hashtable, cpv_array, t_count, t_bucketcount, ufun_hash, bfun_compare);
}

/**
 * Assign hash_multiset container.
 */
void hash_multiset_assign(hash_multiset_t* phmset_dest, const hash_multiset_t* cphmset_src)
{
    assert(phmset_dest != NULL);
    assert(cphmset_src != NULL);

    _hashtable_assign(&phmset_dest->_t_hashtable, &cphmset_src->_t_hashtable);
}

/**
 * Swap the datas of first hash_multiset and second hash_multiset.
 */
void hash_multiset_swap(hash_multiset_t* phmset_first, hash_multiset_t* phmset_second)
{
    assert(phmset_first != NULL);
    assert(phmset_second != NULL);

    _hashtable_swap(&phmset_first->_t_hashtable, &phmset_second->_t_hashtable);
}

/**
 * Get the number of elements int the hash_multiset.
 */
size_t hash_multiset_size(const hash_multiset_t* cphmset_set)
{
    assert(cphmset_set != NULL);

    return _hashtable_size(&cphmset_set->_t_hashtable);
}

/**
 * Get the maximum number of elements int the hash_multiset.
 */
size_t hash_multiset_max_size(const hash_multiset_t* cphmset_set)
{
    assert(cphmset_set != NULL);

    return _hashtable_max_size(&cphmset_set->_t_hashtable);
}

/**
 * Test if an hash_multiset is empty.
 */
bool_t hash_multiset_empty(const hash_multiset_t* cphmset_set)
{
    assert(cphmset_set != NULL);

    return _hashtable_empty(&cphmset_set->_t_hashtable);
}

/**
 * Get the bucket number of elements int the hash_multiset.
 */
size_t hash_multiset_bucket_count(const hash_multiset_t* cphmset_set)
{
    assert(cphmset_set != NULL);

    return _hashtable_bucket_count(&cphmset_set->_t_hashtable);
}

/**
 * Return the hash function.
 */
ufun_t hash_multiset_hash(const hash_multiset_t* cphmset_set)
{
    assert(cphmset_set != NULL);

    return _hashtable_hash(&cphmset_set->_t_hashtable);
}

/**
 * Return the compare function of key.
 */
bfun_t hash_multiset_key_comp(const hash_multiset_t* cphmset_set)
{
    assert(cphmset_set != NULL);

    return _hashtable_key_comp(&cphmset_set->_t_hashtable);
}

/**
 * Return the compare function of value.
 */
bfun_t hash_multiset_value_comp(const hash_multiset_t* cphmset_set)
{
    assert(cphmset_set != NULL);

    return _hashtable_key_comp(&cphmset_set->_t_hashtable);
}

/**
 * Resize.
 */
void hash_multiset_resize(hash_multiset_t* phmset_set, size_t t_resize)
{
    assert(phmset_set != NULL);

    _hashtable_resize(&phmset_set->_t_hashtable, t_resize);
}

/**
 * Tests if the two hash_multiset are equal.
 */
bool_t hash_multiset_equal(const hash_multiset_t* cphmset_first, const hash_multiset_t* cphmset_second)
{
    assert(cphmset_first != NULL);
    assert(cphmset_second != NULL);

    return _hashtable_equal(&cphmset_first->_t_hashtable, &cphmset_second->_t_hashtable);
}

/**
 * Tests if the two hash_multiset are not equal.
 */
bool_t hash_multiset_not_equal(const hash_multiset_t* cphmset_first, const hash_multiset_t* cphmset_second)
{
    assert(cphmset_first != NULL);
    assert(cphmset_second != NULL);

    return _hashtable_not_equal(&cphmset_first->_t_hashtable, &cphmset_second->_t_hashtable);
}

/**
 * Tests if the first hash_multiset is less than the second hash_multiset.
 */
bool_t hash_multiset_less(const hash_multiset_t* cphmset_first, const hash_multiset_t* cphmset_second)
{
    assert(cphmset_first != NULL);
    assert(cphmset_second != NULL);

    return _hashtable_less(&cphmset_first->_t_hashtable, &cphmset_second->_t_hashtable);
}

/**
 * Tests if the first hash_multiset is less than or equal to the second hash_multiset.
 */
bool_t hash_multiset_less_equal(const hash_multiset_t* cphmset_first, const hash_multiset_t* cphmset_second)
{
    assert(cphmset_first != NULL);
    assert(cphmset_second != NULL);

    return _hashtable_less_equal(&cphmset_first->_t_hashtable, &cphmset_second->_t_hashtable);
}

/**
 * Tests if the first hash_multiset is greater than the second hash_multiset.
 */
bool_t hash_multiset_greater(const hash_multiset_t* cphmset_first, const hash_multiset_t* cphmset_second)
{
    assert(cphmset_first != NULL);
    assert(cphmset_second != NULL);

    return _hashtable_greater(&cphmset_first->_t_hashtable, &cphmset_second->_t_hashtable);
}

/**
 * Tests if the first hash_multiset is greater than or equal to the second hash_multiset.
 */
bool_t hash_multiset_greater_equal(const hash_multiset_t* cphmset_first, const hash_multiset_t* cphmset_second)
{
    assert(cphmset_first != NULL);
    assert(cphmset_second != NULL);

    return _hashtable_greater_equal(&cphmset_first->_t_hashtable, &cphmset_second->_t_hashtable);
}

/**
 * Return an iterator that addresses the first element in the hash_multiset.
 */
hash_multiset_iterator_t hash_multiset_begin(const hash_multiset_t* cphmset_set)
{
    hash_multiset_iterator_t it_begin;

    assert(cphmset_set != NULL);

    it_begin = _hashtable_begin(&cphmset_set->_t_hashtable);

    _ITERATOR_CONTAINER(it_begin) = (hash_multiset_t*)cphmset_set;
    _HASH_MULTISET_ITERATOR_CONTAINER_TYPE(it_begin) = _HASH_MULTISET_CONTAINER;
    _HASH_MULTISET_ITERATOR_ITERATOR_TYPE(it_begin) = _BIDIRECTIONAL_ITERATOR;

    return it_begin;
}

/**
 * Return an iterator that addresses the location succeeding the last element in the hash_multiset.
 */
hash_multiset_iterator_t hash_multiset_end(const hash_multiset_t* cphmset_set)
{
    hash_multiset_iterator_t it_end;

    assert(cphmset_set != NULL);

    it_end = _hashtable_end(&cphmset_set->_t_hashtable);

    _ITERATOR_CONTAINER(it_end) = (hash_multiset_t*)cphmset_set;
    _HASH_MULTISET_ITERATOR_CONTAINER_TYPE(it_end) = _HASH_MULTISET_CONTAINER;
    _HASH_MULTISET_ITERATOR_ITERATOR_TYPE(it_end) = _BIDIRECTIONAL_ITERATOR;

    return it_end;
}

/**
 * Inserts an range of unique element into a hash_multiset.
 */
void hash_multiset_insert_range(hash_multiset_t* phmset_set, iterator_t it_begin, iterator_t it_end)
{
    assert(phmset_set != NULL);
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));

    _hashtable_insert_equal_range(&phmset_set->_t_hashtable, it_begin, it_end);
}

/**
 * Inserts an array of unique element into a hash_multiset.
 */
void hash_multiset_insert_array(hash_multiset_t* phmset_set, const void* cpv_array, size_t t_count)
{
    assert(phmset_set != NULL);
    assert(cpv_array != NULL);

    _hashtable_insert_equal_array(&phmset_set->_t_hashtable, cpv_array, t_count);
}

/*
 * Erase an element in an hash_multiset from specificed position.
 */
void hash_multiset_erase_pos(hash_multiset_t* phmset_set, hash_multiset_iterator_t it_pos)
{
    assert(phmset_set != NULL);
    assert(_HASH_MULTISET_ITERATOR_CONTAINER_TYPE(it_pos) == _HASH_MULTISET_CONTAINER);
    assert(_HASH_MULTISET_ITERATOR_ITERATOR_TYPE(it_pos) == _BIDIRECTIONAL_ITERATOR);
    assert(_HASH_MULTISET_ITERATOR_CONTAINER(it_pos) == phmset_set);

    _hashtable_erase_pos(&phmset_set->_t_hashtable, it_pos);
}

/*
 * Erase a range of element in an hash_multiset.
 */
void hash_multiset_erase_range(hash_multiset_t* phmset_set, hash_multiset_iterator_t it_begin, hash_multiset_iterator_t it_end)
{
    assert(phmset_set != NULL);
    assert(_HASH_MULTISET_ITERATOR_CONTAINER_TYPE(it_begin) == _HASH_MULTISET_CONTAINER);
    assert(_HASH_MULTISET_ITERATOR_ITERATOR_TYPE(it_begin) == _BIDIRECTIONAL_ITERATOR);
    assert(_HASH_MULTISET_ITERATOR_CONTAINER_TYPE(it_end) == _HASH_MULTISET_CONTAINER);
    assert(_HASH_MULTISET_ITERATOR_ITERATOR_TYPE(it_end) == _BIDIRECTIONAL_ITERATOR);
    assert(_HASH_MULTISET_ITERATOR_CONTAINER(it_begin) == phmset_set);
    assert(_HASH_MULTISET_ITERATOR_CONTAINER(it_end) == phmset_set);

    _hashtable_erase_range(&phmset_set->_t_hashtable, it_begin, it_end);
}

/**
 * Erases all the elements of an hash_multiset.
 */
void hash_multiset_clear(hash_multiset_t* phmset_set)
{
    assert(phmset_set != NULL);

    _hashtable_clear(&phmset_set->_t_hashtable);
}

/** local function implementation section **/

/** eof **/

