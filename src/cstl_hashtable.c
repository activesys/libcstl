/*
 *  The implementation of hashtable.
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
 * Create hashtable container.
 */
_hashtable_t* _create_hashtable(const char* s_typename)
{
    _hashtable_t* pt_hashtable = NULL;

    if ((pt_hashtable = (_hashtable_t*)malloc(sizeof(_hashtable_t))) == NULL) {
        return NULL;
    }

    if (!_create_hashtable_auxiliary(pt_hashtable, s_typename)) {
        free(pt_hashtable);
        return NULL;
    }

    return pt_hashtable;
}

/**
 * Initialize hashtable container.
 */
void _hashtable_init(_hashtable_t* pt_hashtable, size_t t_bucketcount, ufun_t ufun_hash, bfun_t bfun_compare)
{
    assert(pt_hashtable != NULL);
    assert(_hashtable_is_created(pt_hashtable));

    /* initialize the bucket vector and node count */
    vector_init(&pt_hashtable->_vec_bucket);
    if (t_bucketcount > 0) {
        vector_resize(&pt_hashtable->_vec_bucket, _hashtable_get_prime(t_bucketcount));
    } else {
        vector_resize(&pt_hashtable->_vec_bucket, _hashtable_get_prime(_HASHTABLE_DEFAULT_BUCKET_COUNT));
    }
    pt_hashtable->_t_nodecount = 0;

    /* initialize the hash, compare and destroy element function */
    pt_hashtable->_ufun_hash = ufun_hash != NULL ? ufun_hash : _hashtable_default_hash;
    pt_hashtable->_bfun_compare = bfun_compare != NULL ? bfun_compare : _GET_HASHTABLE_TYPE_LESS_FUNCTION(pt_hashtable);
}

/**
 * Initialize hashtable container with hashtable.
 */
void _hashtable_init_copy(_hashtable_t* pt_dest, const _hashtable_t* cpt_src)
{
    _hashtable_iterator_t it_iter;
    _hashtable_iterator_t it_begin;
    _hashtable_iterator_t it_end;

    assert(pt_dest != NULL);
    assert(cpt_src != NULL);
    assert(_hashtable_is_created(pt_dest));
    assert(_hashtable_is_inited(cpt_src));
    assert(_hashtable_same_type(pt_dest, cpt_src));

    /* initialize the dest hashtable with src hashtable attribute */
    _hashtable_init(pt_dest, _hashtable_bucket_count(cpt_src), cpt_src->_ufun_hash, cpt_src->_bfun_compare);
    it_begin = _hashtable_begin(cpt_src);
    it_end = _hashtable_end(cpt_src);

    /* insert node from src to dest */
    for (it_iter = it_begin;
         !_hashtable_iterator_equal(it_iter, it_end);
         it_iter = _hashtable_iterator_next(it_iter)) {
        _hashtable_insert_equal(pt_dest, _hashtable_iterator_get_pointer_ignore_cstr(it_iter));
    }
}

/**
 * Initialize hashtable container with specific range.
 */
void _hashtable_init_copy_equal_range(
    _hashtable_t* pt_dest, iterator_t it_begin, iterator_t it_end, size_t t_bucketcount,
    ufun_t ufun_hash, bfun_t bfun_compare)
{
    assert(pt_dest != NULL);
    assert(_hashtable_is_created(pt_dest));
    assert(_hashtable_same_iterator_type(pt_dest, it_begin));
    assert(_hashtable_same_iterator_type(pt_dest, it_end));
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));

    _hashtable_init(pt_dest, t_bucketcount, ufun_hash, bfun_compare);
    _hashtable_insert_equal_range(pt_dest, it_begin, it_end);
}

/**
 * Initialize hashtable container with specific array.
 */
void _hashtable_init_copy_equal_array(
    _hashtable_t* pt_dest, const void* cpv_array, size_t t_count, size_t t_bucketcount,
    ufun_t ufun_hash, bfun_t bfun_compare)
{
    assert(pt_dest != NULL);
    assert(_hashtable_is_created(pt_dest));
    assert(cpv_array != NULL);

    _hashtable_init(pt_dest, t_bucketcount, ufun_hash, bfun_compare);
    _hashtable_insert_equal_array(pt_dest, cpv_array, t_count);
}

/**
 * Initialize hashtable container with specific range.
 */
void _hashtable_init_copy_unique_range(
    _hashtable_t* pt_dest, iterator_t it_begin, iterator_t it_end, size_t t_bucketcount,
    ufun_t ufun_hash, bfun_t bfun_compare)
{
    assert(pt_dest != NULL);
    assert(_hashtable_is_created(pt_dest));
    assert(_hashtable_same_iterator_type(pt_dest, it_begin));
    assert(_hashtable_same_iterator_type(pt_dest, it_end));
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));

    _hashtable_init(pt_dest, t_bucketcount, ufun_hash, bfun_compare);
    _hashtable_insert_unique_range(pt_dest, it_begin, it_end);
}

/**
 * Initialize hashtable container with specific array.
 */
void _hashtable_init_copy_unique_array(
    _hashtable_t* pt_dest, const void* cpv_array, size_t t_count, size_t t_bucketcount,
    ufun_t ufun_hash, bfun_t bfun_compare)
{
    assert(pt_dest != NULL);
    assert(_hashtable_is_created(pt_dest));
    assert(cpv_array != NULL);

    _hashtable_init(pt_dest, t_bucketcount, ufun_hash, bfun_compare);
    _hashtable_insert_unique_array(pt_dest, cpv_array, t_count);
}

/**
 * Destroy hashtable.
 */
void _hashtable_destroy(_hashtable_t* pt_hashtable)
{
    _hashtable_destroy_auxiliary(pt_hashtable);
    free(pt_hashtable);
}

/**
 * Resize.
 */
void _hashtable_resize(_hashtable_t* pt_hashtable, size_t t_resize)
{
    size_t        t_tmp = 0;
    size_t        t_pos = 0;
    size_t        i = 0;
    size_t        t_bucketcount = 0;
    _hashnode_t*  pt_node = NULL;
    _hashnode_t*  pt_nodelist = NULL;
    _hashnode_t** ppt_bucket = NULL;

    assert(pt_hashtable != NULL);

    if (t_resize > _hashtable_bucket_count(pt_hashtable)) {
        /* select all element in hash node list */
        for (i = 0; i < vector_size(&pt_hashtable->_vec_bucket); ++i) {
            ppt_bucket = (_hashnode_t**)vector_at(&pt_hashtable->_vec_bucket, i);
            pt_node = *ppt_bucket;
            while (pt_node != NULL) {
                *ppt_bucket = pt_node->_pt_next;
                pt_node->_pt_next = pt_nodelist;
                pt_nodelist = pt_node;
                pt_node = *ppt_bucket;
            }
        }

        /* resize vector bucket */
        vector_resize(&pt_hashtable->_vec_bucket, _hashtable_get_prime(t_resize));
        t_bucketcount = _hashtable_bucket_count(pt_hashtable);

        /* rehash */
        while (pt_nodelist != NULL) {
            pt_node = pt_nodelist;
            pt_nodelist = pt_node->_pt_next;

            t_tmp = _GET_HASHTABLE_TYPE_SIZE(pt_hashtable);
            _hashtable_hash_auxiliary(pt_hashtable, pt_node->_pby_data, &t_tmp);
            t_pos = t_tmp % t_bucketcount;
            ppt_bucket = (_hashnode_t**)vector_at(&pt_hashtable->_vec_bucket, t_pos);
            pt_node->_pt_next = *ppt_bucket;
            *ppt_bucket = pt_node;
        }
    }
}

/**
 * Inserts an element into a hashtable.
 */
_hashtable_iterator_t _hashtable_insert_equal(_hashtable_t* pt_hashtable, const void* cpv_value)
{
    size_t                t_bucketcount = 0;
    _hashnode_t*          pt_node = NULL;
    _hashnode_t*          pt_cur = NULL;
    _hashnode_t**         ppt_nodelist = NULL;
    _hashtable_iterator_t it_iter = _create_hashtable_iterator();
    bool_t                b_result = false;
    size_t                t_tmp = 0;
    size_t                t_pos = 0;
    bool_t                b_less = false;
    bool_t                b_greater = false;

    assert(pt_hashtable != NULL);
    assert(cpv_value != NULL);
    assert(_hashtable_is_inited(pt_hashtable));

    /* resize */
    _hashtable_resize(pt_hashtable, _hashtable_size(pt_hashtable) + 1);

    /* allocate node */
    pt_node = _alloc_allocate(
        &pt_hashtable->_t_allocator, _HASHTABLE_NODE_SIZE(_GET_HASHTABLE_TYPE_SIZE(pt_hashtable)), 1);
    assert(pt_node != NULL);
    _hashtable_init_elem_auxiliary(pt_hashtable, pt_node);
    b_result = _GET_HASHTABLE_TYPE_SIZE(pt_hashtable);
    _GET_HASHTABLE_TYPE_COPY_FUNCTION(pt_hashtable)(pt_node->_pby_data, cpv_value, &b_result);
    assert(b_result);

    /* hash */
    t_bucketcount = _hashtable_bucket_count(pt_hashtable);
    t_tmp = _GET_HASHTABLE_TYPE_SIZE(pt_hashtable);
    _hashtable_hash_auxiliary(pt_hashtable, pt_node->_pby_data, &t_tmp);
    t_pos = t_tmp % t_bucketcount;

    /* insert node into hashtable, note the node has same value together */
    ppt_nodelist = (_hashnode_t**)vector_at(&pt_hashtable->_vec_bucket, t_pos);
    assert(ppt_nodelist != NULL);
    pt_cur = *ppt_nodelist;
    if (pt_cur == NULL) {
        pt_node->_pt_next = pt_cur;
        *ppt_nodelist = pt_node;
    } else {
        b_less = b_greater = _GET_HASHTABLE_TYPE_SIZE(pt_hashtable);
        _hashtable_elem_compare_auxiliary(pt_hashtable, pt_cur->_pby_data, pt_node->_pby_data, &b_less);
        _hashtable_elem_compare_auxiliary(pt_hashtable, pt_node->_pby_data, pt_cur->_pby_data, &b_greater);
        if (!b_less && !b_greater) {
            pt_node->_pt_next = pt_cur;
            *ppt_nodelist = pt_node;
        } else {
            while (pt_cur->_pt_next != NULL) {
                b_less = b_greater = _GET_HASHTABLE_TYPE_SIZE(pt_hashtable);
                _hashtable_elem_compare_auxiliary(
                    pt_hashtable, pt_cur->_pt_next->_pby_data, pt_node->_pby_data, &b_less);
                _hashtable_elem_compare_auxiliary(
                    pt_hashtable, pt_node->_pby_data, pt_cur->_pt_next->_pby_data, &b_greater);

                if (b_less || b_greater) {
                    pt_cur = pt_cur->_pt_next;
                } else {
                    break;
                }
            } 
            pt_node->_pt_next = pt_cur->_pt_next;
            pt_cur->_pt_next = pt_node;
        }
    }
    pt_hashtable->_t_nodecount++;

    _HASHTABLE_ITERATOR_BUCKETPOS(it_iter) = (_byte_t*)ppt_nodelist;
    _HASHTABLE_ITERATOR_COREPOS(it_iter) = (_byte_t*)pt_node;
    _HASHTABLE_ITERATOR_HASHTABLE_POINTER(it_iter) = pt_hashtable;

    return it_iter;
}

/**
 * Inserts an unique element into a hashtable.
 */
_hashtable_iterator_t _hashtable_insert_unique(_hashtable_t* pt_hashtable, const void* cpv_value)
{
    _hashtable_iterator_t it_iter;

    assert(pt_hashtable != NULL);
    assert(cpv_value != NULL);
    assert(_hashtable_is_inited(pt_hashtable));

    if (_hashtable_empty(pt_hashtable)) {
        return _hashtable_insert_equal(pt_hashtable, cpv_value);
    } else {
        it_iter = _hashtable_find(pt_hashtable, cpv_value);
        if (!_hashtable_iterator_equal(it_iter, _hashtable_end(pt_hashtable))) {
            return _hashtable_end(pt_hashtable);
        } else {
            return _hashtable_insert_equal(pt_hashtable, cpv_value);
        }
    }
}

/**
 * Find specific element.
 */
_hashtable_iterator_t _hashtable_find(const _hashtable_t* cpt_hashtable, const void* cpv_value)
{
    _hashtable_iterator_t it_iter = _create_hashtable_iterator();
    size_t                t_bucketcount = 0;
    _hashnode_t*          pt_node = NULL;
    _hashnode_t**         ppt_bucket = NULL;
    size_t                t_tmp = 0;
    size_t                t_pos = 0;
    bool_t                b_less = false;
    bool_t                b_greater = false;

    assert(cpt_hashtable != NULL);
    assert(cpv_value != NULL);
    assert(_hashtable_is_inited(cpt_hashtable));

    t_bucketcount = _hashtable_bucket_count(cpt_hashtable);
    t_tmp = _GET_HASHTABLE_TYPE_SIZE(cpt_hashtable);
    _hashtable_hash_auxiliary(cpt_hashtable, cpv_value, &t_tmp);
    t_pos = t_tmp % t_bucketcount;
    ppt_bucket = (_hashnode_t**)vector_at(&cpt_hashtable->_vec_bucket, t_pos);
    pt_node = *ppt_bucket;

    while (pt_node != NULL) {
        b_less = b_greater = _GET_HASHTABLE_TYPE_SIZE(cpt_hashtable);
        _hashtable_elem_compare_auxiliary(cpt_hashtable, pt_node->_pby_data, cpv_value, &b_less);
        _hashtable_elem_compare_auxiliary(cpt_hashtable, cpv_value, pt_node->_pby_data, &b_greater);
        if (b_less || b_greater) {
            pt_node = pt_node->_pt_next;
        } else {
            break;
        }
    }

    if (pt_node == NULL) {
        return _hashtable_end(cpt_hashtable);
    } else {
        _HASHTABLE_ITERATOR_BUCKETPOS(it_iter) = (_byte_t*)ppt_bucket;
        _HASHTABLE_ITERATOR_COREPOS(it_iter) = (_byte_t*)pt_node;
        _HASHTABLE_ITERATOR_HASHTABLE_POINTER(it_iter) = (_hashtable_t*)cpt_hashtable;

        return it_iter;
    }
}

/**
 * Return an iterator range that is equal to a specific element.
 */
range_t _hashtable_equal_range(const _hashtable_t* cpt_hashtable, const void* cpv_value)
{
    range_t       r_result;
    size_t        t_bucketcount = 0;
    _hashnode_t*  pt_begin = NULL;
    _hashnode_t*  pt_end = NULL;
    _hashnode_t** ppt_bucket = NULL;
    size_t        t_tmp = 0;
    size_t        t_pos = 0;
    bool_t        b_less = false;
    bool_t        b_greater = false;
    size_t        i = 0;

    assert(cpt_hashtable != NULL);
    assert(cpv_value != NULL);
    assert(_hashtable_is_inited(cpt_hashtable));

    r_result.it_begin = _create_hashtable_iterator();
    r_result.it_end = _create_hashtable_iterator();

    t_bucketcount = _hashtable_bucket_count(cpt_hashtable);
    t_tmp = _GET_HASHTABLE_TYPE_SIZE(cpt_hashtable);
    _hashtable_hash_auxiliary(cpt_hashtable, cpv_value, &t_tmp);
    t_pos = t_tmp % t_bucketcount;
    ppt_bucket = (_hashnode_t**)vector_at(&cpt_hashtable->_vec_bucket, t_pos);

    for (pt_begin = *ppt_bucket; pt_begin != NULL; pt_begin = pt_begin->_pt_next) {
        b_less = b_greater = _GET_HASHTABLE_TYPE_SIZE(cpt_hashtable);
        _hashtable_elem_compare_auxiliary(cpt_hashtable, pt_begin->_pby_data, cpv_value, &b_less);
        _hashtable_elem_compare_auxiliary(cpt_hashtable, cpv_value, pt_begin->_pby_data, &b_greater);
        if (!b_less && !b_greater) {
            for (pt_end = pt_begin->_pt_next; pt_end != NULL; pt_end = pt_end->_pt_next) {
                b_less = b_greater = _GET_HASHTABLE_TYPE_SIZE(cpt_hashtable);
                _hashtable_elem_compare_auxiliary(cpt_hashtable, pt_end->_pby_data, cpv_value, &b_less);
                _hashtable_elem_compare_auxiliary(cpt_hashtable, cpv_value, pt_end->_pby_data, &b_greater);
                if (b_less || b_greater) {
                    _HASHTABLE_ITERATOR_BUCKETPOS(r_result.it_begin) = (_byte_t*)ppt_bucket;
                    _HASHTABLE_ITERATOR_COREPOS(r_result.it_begin) = (_byte_t*)pt_begin;
                    _HASHTABLE_ITERATOR_HASHTABLE_POINTER(r_result.it_begin) = (_hashtable_t*)cpt_hashtable;

                    _HASHTABLE_ITERATOR_BUCKETPOS(r_result.it_end) = (_byte_t*)ppt_bucket;
                    _HASHTABLE_ITERATOR_COREPOS(r_result.it_end) = (_byte_t*)pt_end;
                    _HASHTABLE_ITERATOR_HASHTABLE_POINTER(r_result.it_end) = (_hashtable_t*)cpt_hashtable;

                    return r_result;
                }
            }
            
            _HASHTABLE_ITERATOR_BUCKETPOS(r_result.it_begin) = (_byte_t*)ppt_bucket;
            _HASHTABLE_ITERATOR_COREPOS(r_result.it_begin) = (_byte_t*)pt_begin;
            _HASHTABLE_ITERATOR_HASHTABLE_POINTER(r_result.it_begin) = (_hashtable_t*)cpt_hashtable;

            for (i = t_pos + 1; i < t_bucketcount; ++i) {
                ppt_bucket = (_hashnode_t**)vector_at(&cpt_hashtable->_vec_bucket, i);
                pt_end = *ppt_bucket;
                if (pt_end != NULL) {
                    _HASHTABLE_ITERATOR_BUCKETPOS(r_result.it_end) = (_byte_t*)ppt_bucket;
                    _HASHTABLE_ITERATOR_COREPOS(r_result.it_end) = (_byte_t*)pt_end;
                    _HASHTABLE_ITERATOR_HASHTABLE_POINTER(r_result.it_end) = (_hashtable_t*)cpt_hashtable;

                    return r_result;
                }
            }

            r_result.it_end = _hashtable_end(cpt_hashtable);

            return r_result;
        }
    }

    r_result.it_begin = _hashtable_end(cpt_hashtable);
    r_result.it_end = _hashtable_end(cpt_hashtable);

    return r_result;
}

/**
 * Return the number of specific elements in an hashtable
 */
size_t _hashtable_count(const _hashtable_t* cpt_hashtable, const void* cpv_value)
{
    range_t r_range = _hashtable_equal_range(cpt_hashtable, cpv_value);

    return abs(_hashtable_iterator_distance(r_range.it_begin, r_range.it_end));
}

/*
 * Erase an element in an hashtable from specificed position.
 */
void _hashtable_erase_pos(_hashtable_t* pt_hashtable, _hashtable_iterator_t it_pos)
{
    _hashnode_t** ppt_bucket = NULL;
    _hashnode_t*  pt_node = NULL;
    _hashnode_t*  pt_deletion = NULL;
    bool_t        b_result = false;

    assert(pt_hashtable != NULL);
    assert(_hashtable_is_inited(pt_hashtable));
    assert(_hashtable_iterator_belong_to_hashtable(pt_hashtable, it_pos));
    assert(!_hashtable_iterator_equal(it_pos, _hashtable_end(pt_hashtable)));

    /* get the previous node */
    ppt_bucket = (_hashnode_t**)_HASHTABLE_ITERATOR_BUCKETPOS(it_pos);
    pt_node = *ppt_bucket;
    pt_deletion = (_hashnode_t*)_HASHTABLE_ITERATOR_COREPOS(it_pos);
    if (pt_node == pt_deletion) {
        /* the deletion node is the first node of node list */
        *ppt_bucket = pt_node->_pt_next;
    } else {
        while (pt_node->_pt_next != NULL) {
            if (pt_node->_pt_next == pt_deletion) {
                pt_node->_pt_next = pt_deletion->_pt_next;
                break;
            } else {
                pt_node = pt_node->_pt_next;
            }
        }
    }
    /* delete the node */
    b_result = _GET_HASHTABLE_TYPE_SIZE(pt_hashtable);
    _GET_HASHTABLE_TYPE_DESTROY_FUNCTION(pt_hashtable)(pt_deletion->_pby_data, &b_result);
    assert(b_result);
    _alloc_deallocate(
        &pt_hashtable->_t_allocator, pt_deletion, _HASHTABLE_NODE_SIZE(_GET_HASHTABLE_TYPE_SIZE(pt_hashtable)), 1);
    /* update the hashtable size */
    pt_hashtable->_t_nodecount--;
}

/*
 * Erase a range of element in an hashtable.
 */
void _hashtable_erase_range(
    _hashtable_t* pt_hashtable, _hashtable_iterator_t it_begin, _hashtable_iterator_t it_end)
{
    _hashtable_iterator_t it_iter;
    _hashtable_iterator_t it_next;

    assert(pt_hashtable != NULL);
    assert(_hashtable_is_inited(pt_hashtable));
    assert(_hashtable_iterator_belong_to_hashtable(pt_hashtable, it_begin));
    assert(_hashtable_iterator_belong_to_hashtable(pt_hashtable, it_end));
    assert(_hashtable_iterator_equal(it_begin, it_end) || _hashtable_iterator_before(it_begin, it_end));

    it_iter = it_next = it_begin;
    if (!_hashtable_iterator_equal(it_next, _hashtable_end(pt_hashtable))) {
        it_next = _hashtable_iterator_next(it_next);
    }
    while (!_hashtable_iterator_equal(it_iter, it_end)) {
        _hashtable_erase_pos(pt_hashtable, it_iter);

        it_iter = it_next;
        if (!_hashtable_iterator_equal(it_next, _hashtable_end(pt_hashtable))) {
            it_next = _hashtable_iterator_next(it_next);
        }
    }
}

/**
 * Erase an element from a hashtable that match a specified element.
 */
size_t _hashtable_erase(_hashtable_t* pt_hashtable, const void* cpv_value)
{
    size_t t_countsize = _hashtable_count(pt_hashtable, cpv_value);
    range_t t_range = _hashtable_equal_range(pt_hashtable, cpv_value);

    if (!_hashtable_iterator_equal(t_range.it_begin, _hashtable_end(pt_hashtable))) {
        _hashtable_erase_range(pt_hashtable, t_range.it_begin, t_range.it_end);
    }

    return t_countsize;
}

/**
 * Swap the datas of first hashtable and second hashtable.
 */
void _hashtable_swap(_hashtable_t* pt_first, _hashtable_t* pt_second)
{
    _hashtable_t t_swap;

    assert(pt_first != NULL);
    assert(pt_second != NULL);
    assert(_hashtable_is_inited(pt_first));
    assert(_hashtable_is_inited(pt_second));
    assert(_hashtable_same_type_ex(pt_first, pt_second));

    if (_hashtable_equal(pt_first, pt_second)) {
        return;
    }

    t_swap = *pt_first;
    *pt_first = *pt_second;
    *pt_second = t_swap;
}

/**
 * Assign hashtable container.
 */
void _hashtable_assign(_hashtable_t* pt_dest, const _hashtable_t* cpt_src)
{
    _hashtable_iterator_t it_iter;
    _hashtable_iterator_t it_begin;
    _hashtable_iterator_t it_end;

    assert(pt_dest != NULL);
    assert(cpt_src != NULL);
    assert(_hashtable_is_inited(pt_dest));
    assert(_hashtable_is_inited(cpt_src));
    assert(_hashtable_same_type_ex(pt_dest, cpt_src));

    /* clear all elements */
    _hashtable_clear(pt_dest);
    it_begin = _hashtable_begin(cpt_src);
    it_end = _hashtable_end(cpt_src);

    /* insert node from src to dest */
    for (it_iter = it_begin;
         !_hashtable_iterator_equal(it_iter, it_end);
         it_iter = _hashtable_iterator_next(it_iter)) {
        _hashtable_insert_equal(pt_dest, _hashtable_iterator_get_pointer_ignore_cstr(it_iter));
    }
}

/**
 * Get the number of elements int the hashtable.
 */
size_t _hashtable_size(const _hashtable_t* cpt_hashtable)
{
    assert(cpt_hashtable != NULL);
    assert(_hashtable_is_inited(cpt_hashtable));

    return cpt_hashtable->_t_nodecount;
}

/**
 * Test if an hashtable is empty.
 */
bool_t _hashtable_empty(const _hashtable_t* cpt_hashtable)
{
    assert(cpt_hashtable != NULL);
    assert(_hashtable_is_inited(cpt_hashtable));

    return cpt_hashtable->_t_nodecount == 0 ? true : false;
}

/**
 * Get the maximum number of elements int the hashtable.
 */
size_t _hashtable_max_size(const _hashtable_t* cpt_hashtable)
{
    assert(cpt_hashtable != NULL);
    assert(_hashtable_is_inited(cpt_hashtable));

    return (size_t)(-1) / _GET_HASHTABLE_TYPE_SIZE(cpt_hashtable);
}

/**
 * Get the bucket count of elements int the hashtable.
 */
size_t _hashtable_bucket_count(const _hashtable_t* cpt_hashtable)
{
    assert(cpt_hashtable != NULL);
    assert(_hashtable_is_inited(cpt_hashtable));

    return vector_size(&cpt_hashtable->_vec_bucket);
}

/**
 * Return an iterator that addresses the first element in the hashtable.
 */
_hashtable_iterator_t _hashtable_begin(const _hashtable_t* cpt_hashtable)
{
    vector_iterator_t     it_bucket;
    vector_iterator_t     it_begin;
    vector_iterator_t     it_end;
    _hashtable_iterator_t it_iter = _create_hashtable_iterator();

    assert(cpt_hashtable != NULL);
    assert(_hashtable_is_inited(cpt_hashtable));

    it_begin = vector_begin(&cpt_hashtable->_vec_bucket);
    it_end = vector_end(&cpt_hashtable->_vec_bucket);
    for (it_bucket = it_begin; !iterator_equal(it_bucket, it_end); it_bucket = iterator_next(it_bucket)) {
        _HASHTABLE_ITERATOR_BUCKETPOS(it_iter) = _VECTOR_ITERATOR_COREPOS(it_bucket);
        if (*(_hashnode_t**)_HASHTABLE_ITERATOR_BUCKETPOS(it_iter) != NULL) {
            _HASHTABLE_ITERATOR_COREPOS(it_iter) = (_byte_t*)*(_hashnode_t**)_HASHTABLE_ITERATOR_BUCKETPOS(it_iter);
            break;
        }
    }
    if (iterator_equal(it_bucket, it_end)) {
        assert(_HASHTABLE_ITERATOR_COREPOS(it_iter) == NULL);
        _HASHTABLE_ITERATOR_BUCKETPOS(it_iter) = _VECTOR_ITERATOR_COREPOS(it_bucket);
    }
    _HASHTABLE_ITERATOR_HASHTABLE_POINTER(it_iter) = (_hashtable_t*)cpt_hashtable;

    return it_iter;
}

/**
 * Return an iterator that addresses the location succeeding the last element in the hashtable.
 */
_hashtable_iterator_t _hashtable_end(const _hashtable_t* cpt_hashtable)
{
    vector_iterator_t     it_bucket;
    _hashtable_iterator_t it_iter = _create_hashtable_iterator();

    assert(cpt_hashtable != NULL);
    assert(_hashtable_is_inited(cpt_hashtable));

    it_bucket = vector_end(&cpt_hashtable->_vec_bucket);
    _HASHTABLE_ITERATOR_BUCKETPOS(it_iter) = _VECTOR_ITERATOR_COREPOS(it_bucket);
    _HASHTABLE_ITERATOR_COREPOS(it_iter) = NULL;
    _HASHTABLE_ITERATOR_HASHTABLE_POINTER(it_iter) = (_hashtable_t*)cpt_hashtable;

    return it_iter;
}

/**
 * Return the hash function.
 */
ufun_t _hashtable_hash(const _hashtable_t* cpt_hashtable)
{
    assert(cpt_hashtable != NULL);
    assert(_hashtable_is_inited(cpt_hashtable));

    return cpt_hashtable->_ufun_hash;
}

/**
 * Return the compare function of key.
 */
bfun_t _hashtable_key_comp(const _hashtable_t* cpt_hashtable)
{
    assert(cpt_hashtable != NULL);
    assert(_hashtable_is_inited(cpt_hashtable));

    return cpt_hashtable->_bfun_compare;
}

/**
 * Erases all the elements of an hashtable.
 */
void _hashtable_clear(_hashtable_t* pt_hashtable)
{
    size_t       t_bucketcount = 0;
    size_t       i = 0;
    _hashnode_t* pt_node = NULL;
    _hashnode_t* pt_deletion = NULL;
    bool_t       b_result = false;

    assert(pt_hashtable != NULL);
    assert(_hashtable_is_inited(pt_hashtable) || _hashtable_is_created(pt_hashtable));

    t_bucketcount = vector_size(&pt_hashtable->_vec_bucket);
    /* iterator all bucket node */
    for (i = 0; i < t_bucketcount; ++i) {
        /* iterator all element list for one bucket node */
        pt_node = *(_hashnode_t**)vector_at(&pt_hashtable->_vec_bucket, i);
        *(_hashnode_t**)vector_at(&pt_hashtable->_vec_bucket, i) = NULL;
        while (pt_node != NULL) {
            /* delete each element */
            pt_deletion = pt_node;
            pt_node = pt_node->_pt_next;

            /* destroy element */
            b_result = _GET_HASHTABLE_TYPE_SIZE(pt_hashtable);
            _GET_HASHTABLE_TYPE_DESTROY_FUNCTION(pt_hashtable)(pt_deletion->_pby_data, &b_result);
            assert(b_result);
            _alloc_deallocate(&pt_hashtable->_t_allocator,  pt_deletion, 
                _HASHTABLE_NODE_SIZE(_GET_HASHTABLE_TYPE_SIZE(pt_hashtable)), 1);
        }
    }
    
    pt_hashtable->_t_nodecount = 0;
}

/**
 * Tests if the two rb tree are equal.
 */
bool_t _hashtable_equal(const _hashtable_t* cpt_first, const _hashtable_t* cpt_second)
{
    _hashtable_iterator_t it_first;
    _hashtable_iterator_t it_first_begin;
    _hashtable_iterator_t it_first_end;
    _hashtable_iterator_t it_second;
    _hashtable_iterator_t it_second_begin;
    _hashtable_iterator_t it_second_end;
    bool_t                b_less = false;
    bool_t                b_greater = false;

    assert(cpt_first != NULL);
    assert(cpt_second != NULL);
    assert(_hashtable_is_inited(cpt_first));
    assert(_hashtable_is_inited(cpt_second));
    assert(_hashtable_same_type(cpt_first, cpt_second));
    assert(cpt_first->_ufun_hash == cpt_second->_ufun_hash);
    assert(cpt_first->_bfun_compare == cpt_second->_bfun_compare);

    if (cpt_first == cpt_second) {
        return true;
    }

    /* check size or bucket count*/
    if (_hashtable_size(cpt_first) != _hashtable_size(cpt_second) ||
        _hashtable_bucket_count(cpt_first) != _hashtable_bucket_count(cpt_second)) {
        return false;
    }

    it_first_begin = _hashtable_begin(cpt_first);
    it_first_end = _hashtable_end(cpt_first);
    it_second_begin = _hashtable_begin(cpt_second);
    it_second_end = _hashtable_end(cpt_second);

    /* check each element */
    for (it_first = it_first_begin, it_second = it_second_begin;
         !_hashtable_iterator_equal(it_first, it_first_end) && !_hashtable_iterator_equal(it_second, it_second_end);
         it_first = _hashtable_iterator_next(it_first), it_second = _hashtable_iterator_next(it_second)) {
        b_less = b_greater = _GET_HASHTABLE_TYPE_SIZE(cpt_first);
        _GET_HASHTABLE_TYPE_LESS_FUNCTION(cpt_first)(
                ((_hashnode_t*)_HASHTABLE_ITERATOR_COREPOS(it_first))->_pby_data,
                ((_hashnode_t*)_HASHTABLE_ITERATOR_COREPOS(it_second))->_pby_data, &b_less);
        _GET_HASHTABLE_TYPE_LESS_FUNCTION(cpt_first)(
                ((_hashnode_t*)_HASHTABLE_ITERATOR_COREPOS(it_second))->_pby_data,
                ((_hashnode_t*)_HASHTABLE_ITERATOR_COREPOS(it_first))->_pby_data, &b_greater);
        if (b_less || b_greater) {
            return false;
        }
    }

    assert(_hashtable_iterator_equal(it_first, it_first_end) && _hashtable_iterator_equal(it_second, it_second_end));

    return true;
}

/**
 * Tests if the two rb tree are not equal.
 */
bool_t _hashtable_not_equal(const _hashtable_t* cpt_first, const _hashtable_t* cpt_second)
{
    return !_hashtable_equal(cpt_first, cpt_second);
}

/**
 * Tests if the first rb tree is less than the second rb tree.
 */
bool_t _hashtable_less(const _hashtable_t* cpt_first, const _hashtable_t* cpt_second)
{
    _hashtable_iterator_t it_first;
    _hashtable_iterator_t it_first_begin;
    _hashtable_iterator_t it_first_end;
    _hashtable_iterator_t it_second;
    _hashtable_iterator_t it_second_begin;
    _hashtable_iterator_t it_second_end;
    bool_t                b_less = false;
    bool_t                b_greater = false;

    assert(cpt_first != NULL);
    assert(cpt_second != NULL);
    assert(_hashtable_is_inited(cpt_first));
    assert(_hashtable_is_inited(cpt_second));
    assert(_hashtable_same_type_ex(cpt_first, cpt_second));

    /* check vector bucket count */
    if (vector_size(&cpt_first->_vec_bucket) == vector_size(&cpt_second->_vec_bucket)) {
        it_first_begin = _hashtable_begin(cpt_first);
        it_first_end = _hashtable_end(cpt_first);
        it_second_begin = _hashtable_begin(cpt_second);
        it_second_end = _hashtable_end(cpt_second);

        /* check each element */
        for (it_first = it_first_begin,
             it_second = it_second_begin;
             !_hashtable_iterator_equal(it_first, it_first_end) && 
             !_hashtable_iterator_equal(it_second, it_second_end);
             it_first = _hashtable_iterator_next(it_first),
             it_second = _hashtable_iterator_next(it_second)) {
            b_less = _GET_HASHTABLE_TYPE_SIZE(cpt_first);
            _GET_HASHTABLE_TYPE_LESS_FUNCTION(cpt_first)(
                    ((_hashnode_t*)_HASHTABLE_ITERATOR_COREPOS(it_first))->_pby_data,
                    ((_hashnode_t*)_HASHTABLE_ITERATOR_COREPOS(it_second))->_pby_data, &b_less);
            if (b_less) {
                return true;
            }
            b_greater = _GET_HASHTABLE_TYPE_SIZE(cpt_first);
            _GET_HASHTABLE_TYPE_LESS_FUNCTION(cpt_first)(
                    ((_hashnode_t*)_HASHTABLE_ITERATOR_COREPOS(it_second))->_pby_data,
                    ((_hashnode_t*)_HASHTABLE_ITERATOR_COREPOS(it_first))->_pby_data, &b_greater);
            if (b_greater) {
                return false;
            }
        }
    }

    return _hashtable_size(cpt_first) < _hashtable_size(cpt_second) ? true : false;
}

/**
 * Tests if the first rb tree is less than or equal to the second rb tree.
 */
bool_t _hashtable_less_equal(const _hashtable_t* cpt_first, const _hashtable_t* cpt_second)
{
    return (_hashtable_less(cpt_first, cpt_second) || _hashtable_equal(cpt_first, cpt_second)) ? true : false;
}

/**
 * Tests if the first rb tree is greater than the second rb tree.
 */
bool_t _hashtable_greater(const _hashtable_t* cpt_first, const _hashtable_t* cpt_second)
{
    return _hashtable_less(cpt_second, cpt_first);
}

/**
 * Tests if the first rb tree is greater than or equal to the second rb tree.
 */
bool_t _hashtable_greater_equal(const _hashtable_t* cpt_first, const _hashtable_t* cpt_second)
{
    return (_hashtable_greater(cpt_first, cpt_second) || _hashtable_equal(cpt_first, cpt_second)) ? true : false;
}

/**
 * Inserts an range into a hashtable.
 */
void _hashtable_insert_equal_range(_hashtable_t* pt_hashtable, iterator_t it_begin, iterator_t it_end)
{
    iterator_t it_iter;

    assert(pt_hashtable != NULL);
    assert(_hashtable_is_inited(pt_hashtable));
    assert(_hashtable_same_iterator_type(pt_hashtable, it_begin));
    assert(_hashtable_same_iterator_type(pt_hashtable, it_end));
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));

    for (it_iter = it_begin; !iterator_equal(it_iter, it_end); it_iter = iterator_next(it_iter)) {
        _hashtable_insert_equal(pt_hashtable, _iterator_get_pointer_ignore_cstr(it_iter));
    }
}

/**
 * Inserts an array into a hashtable.
 */
void _hashtable_insert_equal_array(_hashtable_t* pt_hashtable, const void* cpv_array, size_t t_count)
{
    size_t i = 0;

    assert(pt_hashtable != NULL);
    assert(_hashtable_is_inited(pt_hashtable));
    assert(cpv_array != NULL);

    /*
     * Copy the elements from src array to dest hashtable
     * The array of c builtin and user define or cstl builtin are different,
     * the elements of c builtin array are element itself, but the elements of 
     * c string, user define or cstl are pointer of element.
     */
    if (strncmp(_GET_HASHTABLE_TYPE_BASENAME(pt_hashtable), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        /*
         * We need built a string_t for c string element.
         */
        string_t* pstr_elem = create_string();
        assert(pstr_elem != NULL);
        string_init(pstr_elem);
        for (i = 0; i < t_count; ++i) {
            string_assign_cstr(pstr_elem, *((const char**)cpv_array + i));
            _hashtable_insert_equal(pt_hashtable, pstr_elem);
        }
        string_destroy(pstr_elem);
    } else if (_GET_HASHTABLE_TYPE_STYLE(pt_hashtable) == _TYPE_C_BUILTIN) {
        for (i = 0; i < t_count; ++i) {
            _hashtable_insert_equal(pt_hashtable, (unsigned char*)cpv_array + i * _GET_HASHTABLE_TYPE_SIZE(pt_hashtable));
        }
    } else {
        for (i = 0; i < t_count; ++i) {
            _hashtable_insert_equal(pt_hashtable, *((void**)cpv_array + i));
        }
    }
}

/**
 * Inserts an range of unique element into a hashtable.
 */
void _hashtable_insert_unique_range(_hashtable_t* pt_hashtable, iterator_t it_begin, iterator_t it_end)
{
    iterator_t it_iter;

    assert(pt_hashtable != NULL);
    assert(_hashtable_is_inited(pt_hashtable));
    assert(_hashtable_same_iterator_type(pt_hashtable, it_begin));
    assert(_hashtable_same_iterator_type(pt_hashtable, it_end));
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));

    for (it_iter = it_begin; !iterator_equal(it_iter, it_end); it_iter = iterator_next(it_iter)) {
        _hashtable_insert_unique(pt_hashtable, _iterator_get_pointer_ignore_cstr(it_iter));
    }
}

/**
 * Inserts an array of unique element into a hashtable.
 */
void _hashtable_insert_unique_array(_hashtable_t* pt_hashtable, const void* cpv_array, size_t t_count)
{
    size_t i = 0;

    assert(pt_hashtable != NULL);
    assert(_hashtable_is_inited(pt_hashtable));
    assert(cpv_array != NULL);

    /*
     * Copy the elements from src array to dest hashtable
     * The array of c builtin and user define or cstl builtin are different,
     * the elements of c builtin array are element itself, but the elements of 
     * c string, user define or cstl are pointer of element.
     */
    if (strncmp(_GET_HASHTABLE_TYPE_BASENAME(pt_hashtable), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        /*
         * We need built a string_t for c string element.
         */
        string_t* pstr_elem = create_string();
        assert(pstr_elem != NULL);
        string_init(pstr_elem);
        for (i = 0; i < t_count; ++i) {
            string_assign_cstr(pstr_elem, *((const char**)cpv_array + i));
            _hashtable_insert_unique(pt_hashtable, pstr_elem);
        }
        string_destroy(pstr_elem);
    } else if (_GET_HASHTABLE_TYPE_STYLE(pt_hashtable) == _TYPE_C_BUILTIN) {
        for (i = 0; i < t_count; ++i) {
            _hashtable_insert_unique(pt_hashtable, (unsigned char*)cpv_array + i * _GET_HASHTABLE_TYPE_SIZE(pt_hashtable));
        }
    } else {
        for (i = 0; i < t_count; ++i) {
            _hashtable_insert_unique(pt_hashtable, *((void**)cpv_array + i));
        }
    }
}

/** local function implementation section **/

/** eof **/

