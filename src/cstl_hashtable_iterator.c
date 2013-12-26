/*
 *  The implementation of hashtable iterator.
 *  Copyright (C)  2008 - 2014  Wangbo
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
#include <cstl/cvector.h>
#include <cstl/cstring.h>

#include <cstl/cstl_hashtable_iterator.h>
#include <cstl/cstl_hashtable_private.h>
#include <cstl/cstl_hashtable.h>

#include "cstl_hashtable_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Create hashtable iterator.
 */
_hashtable_iterator_t _create_hashtable_iterator(void)
{
    _hashtable_iterator_t it_iter;

    _HASHTABLE_ITERATOR_BUCKETPOS(it_iter) = NULL;
    _HASHTABLE_ITERATOR_COREPOS(it_iter) = NULL;
    _HASHTABLE_ITERATOR_HASHTABLE_POINTER(it_iter) = NULL;

    _ITERATOR_CONTAINER(it_iter) = NULL;

    return it_iter;
}

/**
 * Test the two hashtable iterator are equal.
 */
bool_t _hashtable_iterator_equal(_hashtable_iterator_t it_first, _hashtable_iterator_t it_second)
{
    assert(_hashtable_iterator_belong_to_hashtable(_HASHTABLE_ITERATOR_HASHTABLE(it_first), it_first));
    assert(_hashtable_iterator_belong_to_hashtable(_HASHTABLE_ITERATOR_HASHTABLE(it_second), it_second));
    assert(_HASHTABLE_ITERATOR_HASHTABLE(it_first) == _HASHTABLE_ITERATOR_HASHTABLE(it_second));

    if (_HASHTABLE_ITERATOR_BUCKETPOS(it_first) == _HASHTABLE_ITERATOR_BUCKETPOS(it_second) &&
        _HASHTABLE_ITERATOR_COREPOS(it_first) == _HASHTABLE_ITERATOR_COREPOS(it_second)) {
        return true;
    } else {
        return false;
    }
}

/**
 * Get data value referenced by iterator.
 */
void _hashtable_iterator_get_value(_hashtable_iterator_t it_iter, void* pv_value)
{
    assert(pv_value != NULL);
    assert(_hashtable_iterator_belong_to_hashtable(_HASHTABLE_ITERATOR_HASHTABLE(it_iter), it_iter));
    assert(!_hashtable_iterator_equal(it_iter, _hashtable_end(_HASHTABLE_ITERATOR_HASHTABLE(it_iter))));

    /* char* */
    if (strncmp(_GET_HASHTABLE_TYPE_BASENAME(_HASHTABLE_ITERATOR_HASHTABLE(it_iter)), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        *(char**)pv_value = (char*)string_c_str((string_t*)((_hashnode_t*)_HASHTABLE_ITERATOR_COREPOS(it_iter))->_pby_data);
    } else {
        bool_t b_result = _GET_HASHTABLE_TYPE_SIZE(_HASHTABLE_ITERATOR_HASHTABLE(it_iter));
        _GET_HASHTABLE_TYPE_COPY_FUNCTION(_HASHTABLE_ITERATOR_HASHTABLE(it_iter))(
            pv_value, ((_hashnode_t*)_HASHTABLE_ITERATOR_COREPOS(it_iter))->_pby_data, &b_result);
        assert(b_result);
    }
}

/**
 * Get data value pointer referenced by iterator.
 */
const void* _hashtable_iterator_get_pointer(_hashtable_iterator_t it_iter)
{
    assert(_hashtable_iterator_belong_to_hashtable(_HASHTABLE_ITERATOR_HASHTABLE(it_iter), it_iter));
    assert(!_hashtable_iterator_equal(it_iter, _hashtable_end(_HASHTABLE_ITERATOR_HASHTABLE(it_iter))));

    /* char* */
    if (strncmp(_GET_HASHTABLE_TYPE_BASENAME(_HASHTABLE_ITERATOR_HASHTABLE(it_iter)), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        return (char*)string_c_str((string_t*)((_hashnode_t*)_HASHTABLE_ITERATOR_COREPOS(it_iter))->_pby_data);
    } else {
        return ((_hashnode_t*)_HASHTABLE_ITERATOR_COREPOS(it_iter))->_pby_data;
    }
}

/**
 * Get data value pointer referenced by iterator, but ignore char*.
 */
const void* _hashtable_iterator_get_pointer_ignore_cstr(_hashtable_iterator_t it_iter)
{
    assert(_hashtable_iterator_belong_to_hashtable(_HASHTABLE_ITERATOR_HASHTABLE(it_iter), it_iter));
    assert(!_hashtable_iterator_equal(it_iter, _hashtable_end(_HASHTABLE_ITERATOR_HASHTABLE(it_iter))));

    return ((_hashnode_t*)_HASHTABLE_ITERATOR_COREPOS(it_iter))->_pby_data;
}

/**
 * Return iterator reference previous element.
 */
_hashtable_iterator_t _hashtable_iterator_prev(_hashtable_iterator_t it_iter)
{
    vector_iterator_t it_bucket;
    _hashnode_t*      pt_node = NULL;
    _hashnode_t*      pt_prevnode = NULL;

    assert(_hashtable_iterator_belong_to_hashtable(_HASHTABLE_ITERATOR_HASHTABLE(it_iter), it_iter));
    assert(!_hashtable_iterator_equal(it_iter, _hashtable_begin(_HASHTABLE_ITERATOR_HASHTABLE(it_iter))));

    /* hashtable end is specifical condition. corepos == NULL and bucketpos is invalid pos */
    if (_hashtable_iterator_equal(it_iter, _hashtable_end(_HASHTABLE_ITERATOR_HASHTABLE(it_iter)))) {
        it_bucket = iterator_prev(vector_end(&_HASHTABLE_ITERATOR_HASHTABLE(it_iter)->_vec_bucket));
        _HASHTABLE_ITERATOR_BUCKETPOS(it_iter) = _VECTOR_ITERATOR_COREPOS(it_bucket);
    }

    pt_node = (_hashnode_t*)_HASHTABLE_ITERATOR_COREPOS(it_iter);
    pt_prevnode = *(_hashnode_t**)_HASHTABLE_ITERATOR_BUCKETPOS(it_iter);

    /* current node is first node in current bucket */
    if (pt_prevnode == pt_node) {
        it_bucket = vector_begin(&(_HASHTABLE_ITERATOR_HASHTABLE(it_iter)->_vec_bucket));
        _VECTOR_ITERATOR_COREPOS(it_bucket) = _HASHTABLE_ITERATOR_BUCKETPOS(it_iter);
        for (it_bucket = iterator_prev(it_bucket);
             iterator_greater_equal(it_bucket, vector_begin(&(_HASHTABLE_ITERATOR_HASHTABLE(it_iter)->_vec_bucket)));
             it_bucket = iterator_prev(it_bucket)) {
            pt_node = *(_hashnode_t**)_VECTOR_ITERATOR_COREPOS(it_bucket);
            if (pt_node != NULL) {
                /* get the last hashnode */
                while (pt_node->_pt_next != NULL) {
                        pt_node = pt_node->_pt_next;
                }
                /* set bucket pos and core pos */
                _HASHTABLE_ITERATOR_BUCKETPOS(it_iter) = _VECTOR_ITERATOR_COREPOS(it_bucket);
                _HASHTABLE_ITERATOR_COREPOS(it_iter) = (_byte_t*)pt_node;
                break;
            }
        }
    } else {
        while (pt_prevnode->_pt_next != pt_node) {
            pt_prevnode = pt_prevnode->_pt_next;
        }
        /* set core pos */
        _HASHTABLE_ITERATOR_COREPOS(it_iter) = (_byte_t*)pt_prevnode;
    }

    return it_iter;
}

/**
 * Return iterator reference next element.
 */
_hashtable_iterator_t _hashtable_iterator_next(_hashtable_iterator_t it_iter)
{
    vector_iterator_t it_bucket;
    vector_iterator_t it_end;
    _hashnode_t*      pt_node = NULL;

    assert(_hashtable_iterator_belong_to_hashtable(_HASHTABLE_ITERATOR_HASHTABLE(it_iter), it_iter));
    assert(!_hashtable_iterator_equal(it_iter, _hashtable_end(_HASHTABLE_ITERATOR_HASHTABLE(it_iter))));

    pt_node = (_hashnode_t*)_HASHTABLE_ITERATOR_COREPOS(it_iter);
    assert(pt_node != NULL);

    if (pt_node->_pt_next == NULL) {
        /* iterator from current bucket pos to end */
        it_bucket = vector_begin(&(_HASHTABLE_ITERATOR_HASHTABLE(it_iter)->_vec_bucket));
        _VECTOR_ITERATOR_COREPOS(it_bucket) = _HASHTABLE_ITERATOR_BUCKETPOS(it_iter);
        it_end = vector_end(&(_HASHTABLE_ITERATOR_HASHTABLE(it_iter)->_vec_bucket));
        for (it_bucket = iterator_next(it_bucket);
             !iterator_equal(it_bucket, it_end);
             it_bucket = iterator_next(it_bucket)) {
            _HASHTABLE_ITERATOR_BUCKETPOS(it_iter) = _VECTOR_ITERATOR_COREPOS(it_bucket);
            if (*(_hashnode_t**)_HASHTABLE_ITERATOR_BUCKETPOS(it_iter) != NULL) {
                _HASHTABLE_ITERATOR_COREPOS(it_iter) = (_byte_t*)(*(_hashnode_t**)_HASHTABLE_ITERATOR_BUCKETPOS(it_iter));
                break;
            }
        }
        if (iterator_equal(it_bucket, it_end)) {
            assert((_hashnode_t*)_HASHTABLE_ITERATOR_COREPOS(it_iter) == pt_node);
            _HASHTABLE_ITERATOR_COREPOS(it_iter) = NULL;
            _HASHTABLE_ITERATOR_BUCKETPOS(it_iter) = _VECTOR_ITERATOR_COREPOS(it_bucket);
        }
    } else {
        _HASHTABLE_ITERATOR_COREPOS(it_iter) = (_byte_t*)pt_node->_pt_next;
    }

    return it_iter;
}

/**
 * Calculate distance between two iterators.
 */
int _hashtable_iterator_distance(_hashtable_iterator_t it_first, _hashtable_iterator_t it_second)
{
    _hashtable_iterator_t it_iter;
    int                   n_distance = 0;

    if (_hashtable_iterator_before(it_first, it_second)) {
        for (it_iter = it_first;
             !_hashtable_iterator_equal(it_iter, it_second);
             it_iter = _hashtable_iterator_next(it_iter)) {
            n_distance++;
        }
        return n_distance;
    } else if (_hashtable_iterator_before(it_second, it_first)) {
        for (it_iter = it_second;
             !_hashtable_iterator_equal(it_iter, it_first);
             it_iter = _hashtable_iterator_next(it_iter)) {
            n_distance++;
        }
        return -n_distance;
    } else {
        return 0;
    }
}

/**
 * Test the first iterator is before the second.
 */
bool_t _hashtable_iterator_before(_hashtable_iterator_t it_first, _hashtable_iterator_t it_second)
{
    _hashtable_iterator_t it_iter;
    _hashtable_iterator_t it_end;
    _hashtable_t*         pt_hashtable = NULL;

    assert(_hashtable_iterator_belong_to_hashtable(_HASHTABLE_ITERATOR_HASHTABLE(it_first), it_first));
    assert(_hashtable_iterator_belong_to_hashtable(_HASHTABLE_ITERATOR_HASHTABLE(it_second), it_second));
    assert(_HASHTABLE_ITERATOR_HASHTABLE(it_first) == _HASHTABLE_ITERATOR_HASHTABLE(it_second));

    if (_HASHTABLE_ITERATOR_COREPOS(it_first) == _HASHTABLE_ITERATOR_COREPOS(it_second)) {
        return false;
    }

    pt_hashtable = _HASHTABLE_ITERATOR_HASHTABLE(it_first);
    it_end = _hashtable_end(pt_hashtable);
    for (it_iter = it_first;
         !_hashtable_iterator_equal(it_iter, it_end);
         it_iter = _hashtable_iterator_next(it_iter)) {
        if (_hashtable_iterator_equal(it_iter, it_second)) {
            return true;
        }
    }

    if (_hashtable_iterator_equal(it_second, it_end)) {
        return true;
    } else {
        return false;
    }
}

/** local function implementation section **/

/** eof **/

