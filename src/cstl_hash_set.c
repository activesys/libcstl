/*
 *  The implementation of hash_set.
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

#include "cstl_hash_set_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Initialize hash_set container.
 */
void hash_set_init(hash_set_t* phset_set)
{
    assert(phset_set != NULL);

    hash_set_init_ex(phset_set, 0, NULL, NULL);
}

/**
 * Initialize hash_set container with user define compare function.
 */
void hash_set_init_ex(hash_set_t* phset_set, size_t t_bucketcount, ufun_t ufun_hash, bfun_t bfun_compare)
{
    assert(phset_set != NULL);

    _hashtable_init(&phset_set->_t_hashtable, t_bucketcount, ufun_hash, bfun_compare);
}

/**
 * Destroy hash_set.
 */
void hash_set_destroy(hash_set_t* phset_set)
{
    _hash_set_destroy_auxiliary(phset_set);
    free(phset_set);
}

/**
 * Initialize hash_set container with hash_set.
 */
void hash_set_init_copy(hash_set_t* phset_dest, const hash_set_t* cphset_src)
{
    assert(phset_dest != NULL);
    assert(cphset_src != NULL);

    _hashtable_init_copy(&phset_dest->_t_hashtable, &cphset_src->_t_hashtable);
}

/**
 * Initialize hash_set container with specific range.
 */
void hash_set_init_copy_range(hash_set_t* phset_dest, iterator_t it_begin, iterator_t it_end)
{
    hash_set_init_copy_range_ex(phset_dest, it_begin, it_end, 0, NULL, NULL);
}

/**
 * Initialize hash_set container with specific array.
 */
void hash_set_init_copy_array(hash_set_t* phset_dest, const void* cpv_array, size_t t_count)
{
    hash_set_init_copy_array_ex(phset_dest, cpv_array, t_count, 0, NULL, NULL);
}

/**
 * Initialize hash_set container with specific range and compare function.
 */
void hash_set_init_copy_range_ex(hash_set_t* phset_set, iterator_t it_begin, iterator_t it_end,
    size_t t_bucketcount, ufun_t ufun_hash, bfun_t bfun_compare)
{
    assert(phset_set != NULL);
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));

    _hashtable_init_copy_unique_range(&phset_set->_t_hashtable, it_begin, it_end, t_bucketcount, ufun_hash, bfun_compare);
}

/**
 * Initialize hash_set container with specific array and compare function.
 */
void hash_set_init_copy_array_ex(hash_set_t* phset_set, const void* cpv_array, size_t t_count,
    size_t t_bucketcount, ufun_t ufun_hash, bfun_t bfun_compare)
{
    assert(phset_set != NULL);
    assert(cpv_array != NULL);

    _hashtable_init_copy_unique_array(&phset_set->_t_hashtable, cpv_array, t_count, t_bucketcount, ufun_hash, bfun_compare);
}

/**
 * Assign hash_set container.
 */
void hash_set_assign(hash_set_t* phset_dest, const hash_set_t* cphset_src)
{
    assert(phset_dest != NULL);
    assert(cphset_src != NULL);

    _hashtable_assign(&phset_dest->_t_hashtable, &cphset_src->_t_hashtable);
}

/**
 * Swap the datas of first hash_set and second hash_set.
 */
void hash_set_swap(hash_set_t* phset_first, hash_set_t* phset_second)
{
    assert(phset_first != NULL);
    assert(phset_second != NULL);

    _hashtable_swap(&phset_first->_t_hashtable, &phset_second->_t_hashtable);
}

/**
 * Get the number of elements int the hash_set.
 */
size_t hash_set_size(const hash_set_t* cphset_set)
{
    assert(cphset_set != NULL);

    return _hashtable_size(&cphset_set->_t_hashtable);
}

/**
 * Get the maximum number of elements int the hash_set.
 */
size_t hash_set_max_size(const hash_set_t* cphset_set)
{
    assert(cphset_set != NULL);

    return _hashtable_max_size(&cphset_set->_t_hashtable);
}

/**
 * Test if an hash_set is empty.
 */
bool_t hash_set_empty(const hash_set_t* cphset_set)
{
    assert(cphset_set != NULL);

    return _hashtable_empty(&cphset_set->_t_hashtable);
}

/**
 * Get the bucket number of elements int the hash_set.
 */
size_t hash_set_bucket_count(const hash_set_t* cphset_set)
{
    assert(cphset_set != NULL);

    return _hashtable_bucket_count(&cphset_set->_t_hashtable);
}

/**
 * Return the hash function.
 */
ufun_t hash_set_hash(const hash_set_t* cphset_set)
{
    assert(cphset_set != NULL);

    return _hashtable_hash(&cphset_set->_t_hashtable);
}

/**
 * Return the compare function of key.
 */
bfun_t hash_set_key_comp(const hash_set_t* cphset_set)
{
    assert(cphset_set != NULL);

    return _hashtable_key_comp(&cphset_set->_t_hashtable);
}

/**
 * Return the compare function of value.
 */
bfun_t hash_set_value_comp(const hash_set_t* cphset_set)
{
    assert(cphset_set != NULL);

    return _hashtable_key_comp(&cphset_set->_t_hashtable);
}

/**
 * Resize.
 */
void hash_set_resize(hash_set_t* phset_set, size_t t_resize)
{
    assert(phset_set != NULL);

    _hashtable_resize(&phset_set->_t_hashtable, t_resize);
}

/**
 * Tests if the two hash_set are equal.
 */
bool_t hash_set_equal(const hash_set_t* cphset_first, const hash_set_t* cphset_second)
{
    assert(cphset_first != NULL);
    assert(cphset_second != NULL);

    return _hashtable_equal(&cphset_first->_t_hashtable, &cphset_second->_t_hashtable);
}

/**
 * Tests if the two hash_set are not equal.
 */
bool_t hash_set_not_equal(const hash_set_t* cphset_first, const hash_set_t* cphset_second)
{
    assert(cphset_first != NULL);
    assert(cphset_second != NULL);

    return _hashtable_not_equal(&cphset_first->_t_hashtable, &cphset_second->_t_hashtable);
}

/**
 * Tests if the first hash_set is less than the second hash_set.
 */
bool_t hash_set_less(const hash_set_t* cphset_first, const hash_set_t* cphset_second)
{
    assert(cphset_first != NULL);
    assert(cphset_second != NULL);

    return _hashtable_less(&cphset_first->_t_hashtable, &cphset_second->_t_hashtable);
}

/**
 * Tests if the first hash_set is less than or equal to the second hash_set.
 */
bool_t hash_set_less_equal(const hash_set_t* cphset_first, const hash_set_t* cphset_second)
{
    assert(cphset_first != NULL);
    assert(cphset_second != NULL);

    return _hashtable_less_equal(&cphset_first->_t_hashtable, &cphset_second->_t_hashtable);
}

/**
 * Tests if the first hash_set is greater than the second hash_set.
 */
bool_t hash_set_greater(const hash_set_t* cphset_first, const hash_set_t* cphset_second)
{
    assert(cphset_first != NULL);
    assert(cphset_second != NULL);

    return _hashtable_greater(&cphset_first->_t_hashtable, &cphset_second->_t_hashtable);
}

/**
 * Tests if the first hash_set is greater than or equal to the second hash_set.
 */
bool_t hash_set_greater_equal(const hash_set_t* cphset_first, const hash_set_t* cphset_second)
{
    assert(cphset_first != NULL);
    assert(cphset_second != NULL);

    return _hashtable_greater_equal(&cphset_first->_t_hashtable, &cphset_second->_t_hashtable);
}

/**
 * Return an iterator that addresses the first element in the hash_set.
 */
hash_set_iterator_t hash_set_begin(const hash_set_t* cphset_set)
{
    hash_set_iterator_t it_begin;

    assert(cphset_set != NULL);

    it_begin = _hashtable_begin(&cphset_set->_t_hashtable);

    _ITERATOR_CONTAINER(it_begin) = (hash_set_t*)cphset_set;
    _HASH_SET_ITERATOR_CONTAINER_TYPE(it_begin) = _HASH_SET_CONTAINER;
    _HASH_SET_ITERATOR_ITERATOR_TYPE(it_begin) = _BIDIRECTIONAL_ITERATOR;

    return it_begin;
}

/**
 * Return an iterator that addresses the location succeeding the last element in the hash_set.
 */
hash_set_iterator_t hash_set_end(const hash_set_t* cphset_set)
{
    hash_set_iterator_t it_end;

    assert(cphset_set != NULL);

    it_end = _hashtable_end(&cphset_set->_t_hashtable);

    _ITERATOR_CONTAINER(it_end) = (hash_set_t*)cphset_set;
    _HASH_SET_ITERATOR_CONTAINER_TYPE(it_end) = _HASH_SET_CONTAINER;
    _HASH_SET_ITERATOR_ITERATOR_TYPE(it_end) = _BIDIRECTIONAL_ITERATOR;

    return it_end;
}

/**
 * Inserts an range of unique element into a hash_set.
 */
void hash_set_insert_range(hash_set_t* phset_set, iterator_t it_begin, iterator_t it_end)
{
    assert(phset_set != NULL);
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));

    _hashtable_insert_unique_range(&phset_set->_t_hashtable, it_begin, it_end);
}

/**
 * inserts an array of unique element into a hash_set.
 */
void hash_set_insert_array(hash_set_t* phset_set, const void* cpv_array, size_t t_count)
{
    assert(phset_set != NULL);
    assert(cpv_array != NULL);

    _hashtable_insert_unique_array(&phset_set->_t_hashtable, cpv_array, t_count);
}

/*
 * Erase an element in an hash_set from specificed position.
 */
void hash_set_erase_pos(hash_set_t* phset_set, hash_set_iterator_t it_pos)
{
    assert(phset_set != NULL);
    assert(_HASH_SET_ITERATOR_CONTAINER_TYPE(it_pos) == _HASH_SET_CONTAINER);
    assert(_HASH_SET_ITERATOR_ITERATOR_TYPE(it_pos) == _BIDIRECTIONAL_ITERATOR);
    assert(_HASH_SET_ITERATOR_CONTAINER(it_pos) == phset_set);

    _hashtable_erase_pos(&phset_set->_t_hashtable, it_pos);
}

/*
 * Erase a range of element in an hash_set.
 */
void hash_set_erase_range(hash_set_t* phset_set, hash_set_iterator_t it_begin, hash_set_iterator_t it_end)
{
    assert(phset_set != NULL);
    assert(_HASH_SET_ITERATOR_CONTAINER_TYPE(it_begin) == _HASH_SET_CONTAINER);
    assert(_HASH_SET_ITERATOR_ITERATOR_TYPE(it_begin) == _BIDIRECTIONAL_ITERATOR);
    assert(_HASH_SET_ITERATOR_CONTAINER_TYPE(it_end) == _HASH_SET_CONTAINER);
    assert(_HASH_SET_ITERATOR_ITERATOR_TYPE(it_end) == _BIDIRECTIONAL_ITERATOR);
    assert(_HASH_SET_ITERATOR_CONTAINER(it_begin) == phset_set);
    assert(_HASH_SET_ITERATOR_CONTAINER(it_end) == phset_set);

    _hashtable_erase_range(&phset_set->_t_hashtable, it_begin, it_end);
}

/**
 * Erases all the elements of an hash_set.
 */
void hash_set_clear(hash_set_t* phset_set)
{
    assert(phset_set != NULL);

    _hashtable_clear(&phset_set->_t_hashtable);
}

/** local function implementation section **/

/** eof **/

