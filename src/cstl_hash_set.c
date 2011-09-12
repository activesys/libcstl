/*
 *  The implementation of hash_set.
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

#include <cstl/cstl_hash_set_iterator.h>
#include <cstl/cstl_hash_set_private.h>
#include <cstl/cstl_hash_set.h>

#include "cstl_hash_set_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

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

void hash_set_clear(hash_set_t* pt_hash_set)
{
    assert(pt_hash_set != NULL);

    _hashtable_clear(&pt_hash_set->_t_hashtable);
}

/** local function implementation section **/

/** eof **/

