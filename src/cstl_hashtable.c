/*
 *  The implementation of hashtable.
 *  Copyright (C)  2008,2009,2010  Wangbo
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

#include "cstl_alloc.h"
#include "cstl_types.h"
#include "cstl_iterator.h"

#include "cstl_vector_iterator.h"
#include "cstl_vector_private.h"
#include "cstl_vector.h"

#include "cstl_hashtable_iterator.h"
#include "cstl_hashtable_private.h"

#include "cstring.h"

/** local constant declaration and local macro section **/
#define _HASHTABLE_NODE_SIZE(typesize)\
    ((typesize) + sizeof(hashnode_t) - 1)

#define _HASHTABLE_NODE_NAME            "hashnode_t*"
#define _HASHTABLE_DEFAULT_BUCKET_COUNT 50
#define _HASHTABLE_PRIME_LIST_COUNT     28

/* macros for type informations */
#define _GET_HASHTABLE_TYPE_SIZE(pt_hashtable)\
    ((pt_hashtable)->_t_typeinfo._pt_type->_t_typesize)
#define _GET_HASHTABLE_TYPE_NAME(pt_hashtable)\
    ((pt_hashtable)->_t_typeinfo._sz_typename)
#define _GET_HASHTABLE_TYPE_BASENAME(pt_hashtable)\
    ((pt_hashtable)->_t_typeinfo._pt_type->_sz_typename)
#define _GET_HASHTABLE_TYPE_INIT_FUNCTION(pt_hashtable)\
    ((pt_hashtable)->_t_typeinfo._pt_type->_t_typeinit)
#define _GET_HASHTABLE_TYPE_COPY_FUNCTION(pt_hashtable)\
    ((pt_hashtable)->_t_typeinfo._pt_type->_t_typecopy)
#define _GET_HASHTABLE_TYPE_LESS_FUNCTION(pt_hashtable)\
    ((pt_hashtable)->_t_typeinfo._pt_type->_t_typeless)
#define _GET_HASHTABLE_TYPE_DESTROY_FUNCTION(pt_hashtable)\
    ((pt_hashtable)->_t_typeinfo._pt_type->_t_typedestroy)
#define _GET_HASHTABLE_TYPE_STYLE(pt_hashtable)\
    ((pt_hashtable)->_t_typeinfo._t_style)

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/
#ifndef NDEBUG
/*
 * Assert support.
 */
static bool_t _hashtable_iterator_belong_to_hashtable(
    const hashtable_t* cpt_hashtable, hashtable_iterator_t t_iter);
static bool_t _hashtable_same_hashtable_iterator_type(
    const hashtable_t* cpt_hashtable, hashtable_iterator_t t_iter);
#endif /* NDEBUG */
static bool_t _hashtable_same_type(
    const hashtable_t* cpt_hashtablefirst, const hashtable_t* cpt_hashtablesecond);

/* init, copy, less and destroy function for hashnode_t* type */
static void _hashnode_init(const void* cpv_input, void* pv_output);
static void _hashnode_copy(const void* cpv_first, const void* cpv_second, void* pv_output);
static void _hashnode_less(const void* cpv_first, const void* cpv_second, void* pv_output);
static void _hashnode_destroy(const void* cpv_input, void* pv_output);

/*
 * The default hash function.
 */
static void _hashtable_default_hash(const void* cpv_input, void* pv_output);

/*
 * Get the next prime base the ul_basenum.
 */
static unsigned long _hashtable_get_prime(unsigned long ul_basenum);

/* initialize new element */
static void _hashtable_init_elem_auxiliary(hashtable_t* pt_hashtable, hashnode_t* pt_node);

/* hash auxiliary */
static void _hashtable_hash_auxiliary(const hashtable_t* cpt_hashtable, const void* cpv_input, void* pv_output);
/* compare auxiliary */
static void _hashtable_elem_compare_auxiliary(const hashtable_t* cpt_hashtable,
    const void* cpv_first, const void* cpv_second, void* pv_output);

/** exported global variable definition section **/

/** local global variable definition section **/
static const unsigned long _hashtable_prime_list[_HASHTABLE_PRIME_LIST_COUNT] =
{
    53,         97,           193,         389,       769,
    1543,       3079,         6151,        12289,     24593,
    49157,      98317,        196613,      393241,    786433,
    1572869,    3145739,      6291469,     12582917,  25165843,
    50331653,   100663319,    201326611,   402653189, 805306457,
    1610612741, 3221225473ul, 4294967291ul
};

/** exported function implementation section **/
/* hashtable iterator function */
hashtable_iterator_t _create_hashtable_iterator(void)
{
    hashtable_iterator_t t_newiterator;

    _GET_HASHTABLE_BUCKETPOS(t_newiterator) = NULL;
    _GET_HASHTABLE_COREPOS(t_newiterator) = NULL;
    _GET_HASHTABLE_POINTER(t_newiterator) = NULL;

    _GET_CONTAINER(t_newiterator) = NULL;

    return t_newiterator;
}

bool_t _hashtable_iterator_equal(
    hashtable_iterator_t t_iterfirst, hashtable_iterator_t t_itersecond)
{
    assert(_hashtable_iterator_belong_to_hashtable(_GET_HASHTABLE(t_iterfirst), t_iterfirst));
    assert(_hashtable_iterator_belong_to_hashtable(_GET_HASHTABLE(t_itersecond), t_itersecond));

    if(_GET_HASHTABLE_BUCKETPOS(t_iterfirst) == _GET_HASHTABLE_BUCKETPOS(t_itersecond) &&
       _GET_HASHTABLE_COREPOS(t_iterfirst) == _GET_HASHTABLE_COREPOS(t_itersecond))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void _hashtable_iterator_get_value(
    hashtable_iterator_t t_iter, void* pv_value)
{
    assert(pv_value != NULL);
    assert(_hashtable_iterator_belong_to_hashtable(_GET_HASHTABLE(t_iter), t_iter));
    assert(!_hashtable_iterator_equal(t_iter, _hashtable_end(_GET_HASHTABLE(t_iter))));

    /* char* */
    if(strncmp(_GET_HASHTABLE_TYPE_BASENAME(_GET_HASHTABLE(t_iter)),
        _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        *(char**)pv_value = (char*)string_c_str(
            (string_t*)((hashnode_t*)_GET_HASHTABLE_COREPOS(t_iter))->_pc_data);
    }
    else
    {
        bool_t t_result = _GET_HASHTABLE_TYPE_SIZE(_GET_HASHTABLE(t_iter));
        _GET_HASHTABLE_TYPE_COPY_FUNCTION(_GET_HASHTABLE(t_iter))(
            pv_value, ((hashnode_t*)_GET_HASHTABLE_COREPOS(t_iter))->_pc_data, &t_result);
        assert(t_result);
    }
}

const void* _hashtable_iterator_get_pointer(hashtable_iterator_t t_iter)
{
    assert(_hashtable_iterator_belong_to_hashtable(_GET_HASHTABLE(t_iter), t_iter));
    assert(!_hashtable_iterator_equal(t_iter, _hashtable_end(_GET_HASHTABLE(t_iter))));

    /* char* */
    if(strncmp(_GET_HASHTABLE_TYPE_BASENAME(_GET_HASHTABLE(t_iter)),
        _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        return (char*)string_c_str(
            (string_t*)((hashnode_t*)_GET_HASHTABLE_COREPOS(t_iter))->_pc_data);
    }
    else
    {
        return ((hashnode_t*)_GET_HASHTABLE_COREPOS(t_iter))->_pc_data;
    }
}

hashtable_iterator_t _hashtable_iterator_prev(hashtable_iterator_t t_iter)
{
    vector_iterator_t t_vectoriterator;
    hashnode_t*       pt_node = NULL;
    hashnode_t*       pt_prevnode = NULL;

    assert(_hashtable_iterator_belong_to_hashtable(_GET_HASHTABLE(t_iter), t_iter));
    assert(!_hashtable_iterator_equal(t_iter, _hashtable_begin(_GET_HASHTABLE(t_iter))));

    /* for begin or empty hashtable */
    if(_hashtable_empty(_GET_HASHTABLE(t_iter)) ||
       _hashtable_iterator_equal(t_iter, _hashtable_begin(_GET_HASHTABLE(t_iter))))
    {
        return t_iter;
    }

    /* for end */
    if(_hashtable_iterator_equal(t_iter, _hashtable_end(_GET_HASHTABLE(t_iter))))
    {
        for(t_vectoriterator = iterator_prev(vector_end(&(_GET_HASHTABLE(t_iter)->_t_bucket)));
            iterator_greater_equal(t_vectoriterator, vector_begin(&(_GET_HASHTABLE(t_iter)->_t_bucket)));
            t_vectoriterator = iterator_prev(t_vectoriterator))
        {
            pt_node = *(hashnode_t**)_GET_VECTOR_COREPOS(t_vectoriterator);
            if(pt_node != NULL)
            {
                /* get the last hashnode */
                while(pt_node->_pt_next != NULL)
                {
                    pt_node = pt_node->_pt_next;
                }
                /* set bucket pos and core pos */
                _GET_HASHTABLE_BUCKETPOS(t_iter) = _GET_VECTOR_COREPOS(t_vectoriterator);
                _GET_HASHTABLE_COREPOS(t_iter) = (char*)pt_node;
                break;
            }
        }
    }
    else
    {
        pt_node = (hashnode_t*)_GET_HASHTABLE_COREPOS(t_iter);
        pt_prevnode = *(hashnode_t**)_GET_HASHTABLE_BUCKETPOS(t_iter);

        /* current node is first node in current bucket */
        if(pt_prevnode == pt_node)
        {
            t_vectoriterator = vector_begin(&(_GET_HASHTABLE(t_iter)->_t_bucket));
            _GET_VECTOR_COREPOS(t_vectoriterator) = _GET_HASHTABLE_BUCKETPOS(t_iter);
            for(t_vectoriterator = iterator_prev(t_vectoriterator);
                iterator_greater_equal(t_vectoriterator, vector_begin(&(_GET_HASHTABLE(t_iter)->_t_bucket)));
                t_vectoriterator = iterator_prev(t_vectoriterator))
            {
                pt_node = *(hashnode_t**)_GET_VECTOR_COREPOS(t_vectoriterator);
                if(pt_node != NULL)
                {
                    /* get the last hashnode */
                    while(pt_node->_pt_next != NULL)
                    {
                        pt_node = pt_node->_pt_next;
                    }
                    /* set bucket pos and core pos */
                    _GET_HASHTABLE_BUCKETPOS(t_iter) = _GET_VECTOR_COREPOS(t_vectoriterator);
                    _GET_HASHTABLE_COREPOS(t_iter) = (char*)pt_node;
                    break;
                }
            }
        }
        else
        {
            while(pt_prevnode->_pt_next != pt_node)
            {
                pt_prevnode = pt_prevnode->_pt_next;
            }
            /* set core pos */
            _GET_HASHTABLE_COREPOS(t_iter) = (char*)pt_prevnode;
        }
    }

    return t_iter;
}

hashtable_iterator_t _hashtable_iterator_next(hashtable_iterator_t t_iter)
{
    vector_iterator_t t_vectoriterator;
    hashnode_t*       pt_node = NULL;

    assert(_hashtable_iterator_belong_to_hashtable(_GET_HASHTABLE(t_iter), t_iter));
    assert(!_hashtable_iterator_equal(t_iter, _hashtable_end(_GET_HASHTABLE(t_iter))));

    pt_node = (hashnode_t*)_GET_HASHTABLE_COREPOS(t_iter);
    assert(pt_node != NULL);

    if(pt_node->_pt_next == NULL)
    {
        /* iterator from current bucket pos to end */
        t_vectoriterator = vector_begin(&(_GET_HASHTABLE(t_iter)->_t_bucket));
        _GET_VECTOR_COREPOS(t_vectoriterator) = _GET_HASHTABLE_BUCKETPOS(t_iter);
        for(t_vectoriterator = iterator_next(t_vectoriterator);
            !iterator_equal(t_vectoriterator, vector_end(&(_GET_HASHTABLE(t_iter)->_t_bucket)));
            t_vectoriterator = iterator_next(t_vectoriterator))
        {
            _GET_HASHTABLE_BUCKETPOS(t_iter) = _GET_VECTOR_COREPOS(t_vectoriterator);
            if(*(hashnode_t**)_GET_HASHTABLE_BUCKETPOS(t_iter) != NULL)
            {
                _GET_HASHTABLE_COREPOS(t_iter) = 
                    (char*)(*(hashnode_t**)_GET_HASHTABLE_BUCKETPOS(t_iter));
                break;
            }
        }
        if(iterator_equal(t_vectoriterator, vector_end(&(_GET_HASHTABLE(t_iter)->_t_bucket))))
        {
            assert((hashnode_t*)_GET_HASHTABLE_COREPOS(t_iter) == pt_node);
            _GET_HASHTABLE_COREPOS(t_iter) = NULL;
            _GET_HASHTABLE_BUCKETPOS(t_iter) = _GET_VECTOR_COREPOS(t_vectoriterator);
        }
    }
    else
    {
        _GET_HASHTABLE_COREPOS(t_iter) = (char*)pt_node->_pt_next;
    }

    return t_iter;
}

int _hashtable_iterator_distance(
    hashtable_iterator_t t_iterfirst, hashtable_iterator_t t_itersecond)
{
    hashtable_iterator_t t_iterator;
    int                  n_distance = 0;

    if(_hashtable_iterator_before(t_iterfirst, t_itersecond))
    {
        for(t_iterator = t_iterfirst;
            !_hashtable_iterator_equal(t_iterator, t_itersecond);
            t_iterator = _hashtable_iterator_next(t_iterator))
        {
            n_distance++;
        }
        return n_distance;
    }
    else if(_hashtable_iterator_before(t_itersecond, t_iterfirst))
    {
        for(t_iterator = t_itersecond;
            !_hashtable_iterator_equal(t_iterator, t_iterfirst);
            t_iterator = _hashtable_iterator_next(t_iterator))
        {
            n_distance++;
        }
        return -n_distance;
    }
    else
    {
        return 0;
    }
}

bool_t _hashtable_iterator_before(
    hashtable_iterator_t t_iterfirst, hashtable_iterator_t t_itersecond)
{
    hashtable_iterator_t t_iterator;
    hashtable_t*         pt_hashtable = NULL;

    assert(_GET_HASHTABLE(t_iterfirst) == _GET_HASHTABLE(t_itersecond));
    assert(_hashtable_iterator_belong_to_hashtable(_GET_HASHTABLE(t_iterfirst), t_iterfirst) &&
           _hashtable_iterator_belong_to_hashtable(_GET_HASHTABLE(t_itersecond), t_itersecond));
    assert(_GET_HASHTABLE(t_iterfirst) != NULL && _GET_HASHTABLE(t_itersecond) != NULL);
    assert(_GET_HASHTABLE_BUCKETPOS(t_iterfirst) != NULL &&
           _GET_HASHTABLE_BUCKETPOS(t_itersecond) != NULL);

    if(_GET_HASHTABLE_COREPOS(t_iterfirst) == _GET_HASHTABLE_COREPOS(t_itersecond))
    {
        return false;
    }

    pt_hashtable = _GET_HASHTABLE(t_iterfirst);
    for(t_iterator = t_iterfirst;
        !_hashtable_iterator_equal(t_iterator, _hashtable_end(pt_hashtable));
        t_iterator = _hashtable_iterator_next(t_iterator))
    {
        if(_hashtable_iterator_equal(t_iterator, t_itersecond))
        {
            return true;
        }
    }

    if(_hashtable_iterator_equal(t_itersecond, _hashtable_end(pt_hashtable)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void _hashtable_resize(hashtable_t* pt_hashtable, size_t t_resize)
{
    size_t       t_tmp = 0;
    size_t       t_pos = 0;
    size_t       t_index = 0;
    size_t       t_bucketcount = 0;
    hashnode_t*  pt_node = NULL;
    hashnode_t*  pt_nodelist = NULL;
    hashnode_t** ppt_bucket = NULL;

    assert(pt_hashtable != NULL);

    if(t_resize > _hashtable_bucket_count(pt_hashtable))
    {
        /* select all element in hash node list */
        for(t_index = 0; t_index < vector_size(&pt_hashtable->_t_bucket); ++t_index)
        {
            ppt_bucket = (hashnode_t**)vector_at(&pt_hashtable->_t_bucket, t_index);
            pt_node = *ppt_bucket;
            while(pt_node != NULL)
            {
                *ppt_bucket = pt_node->_pt_next;
                pt_node->_pt_next = pt_nodelist;
                pt_nodelist = pt_node;
                pt_node = *ppt_bucket;
            }
        }

        /* resize vector bucket */
        vector_resize(&pt_hashtable->_t_bucket, _hashtable_get_prime(t_resize));
        t_bucketcount = _hashtable_bucket_count(pt_hashtable);

        /* rehash */
        while(pt_nodelist != NULL)
        {
            pt_node = pt_nodelist;
            pt_nodelist = pt_node->_pt_next;

            t_tmp = _GET_HASHTABLE_TYPE_SIZE(pt_hashtable);
            /*pt_hashtable->_t_hash(pt_node->_pc_data, &t_tmp);*/
            _hashtable_hash_auxiliary(pt_hashtable, pt_node->_pc_data, &t_tmp);
            t_pos = t_tmp % t_bucketcount;
            ppt_bucket = (hashnode_t**)vector_at(&pt_hashtable->_t_bucket, t_pos);
            pt_node->_pt_next = *ppt_bucket;
            *ppt_bucket = pt_node;
        }
    }
}

hashtable_iterator_t _hashtable_insert_equal(
    hashtable_t* pt_hashtable, const void* cpv_value)
{
    size_t               t_bucketcount = 0;
    hashnode_t*          pt_node = NULL;
    hashnode_t*          pt_cur = NULL;
    hashnode_t**         ppt_nodelist = NULL;
    hashtable_iterator_t t_iterator = _create_hashtable_iterator();
    bool_t               t_result = false;
    size_t               t_tmp = 0;
    size_t               t_pos = 0;
    bool_t               t_less = false;
    bool_t               t_greater = false;

    assert(pt_hashtable != NULL && cpv_value != NULL);

    /* resize */
    _hashtable_resize(pt_hashtable, _hashtable_size(pt_hashtable)+1);

    /* allocate node */
    pt_node = allocate(&pt_hashtable->_t_allocater,
        _HASHTABLE_NODE_SIZE(_GET_HASHTABLE_TYPE_SIZE(pt_hashtable)), 1);
    assert(pt_node != NULL);
    _hashtable_init_elem_auxiliary(pt_hashtable, pt_node);
    t_result = _GET_HASHTABLE_TYPE_SIZE(pt_hashtable);
    _GET_HASHTABLE_TYPE_COPY_FUNCTION(pt_hashtable)(
        pt_node->_pc_data, cpv_value, &t_result);
    assert(t_result);

    /* hash */
    t_bucketcount = _hashtable_bucket_count(pt_hashtable);
    t_tmp = _GET_HASHTABLE_TYPE_SIZE(pt_hashtable);
    /*pt_hashtable->_t_hash(pt_node->_pc_data, &t_tmp);*/
    _hashtable_hash_auxiliary(pt_hashtable, pt_node->_pc_data, &t_tmp);
    t_pos = t_tmp % t_bucketcount;

    /* insert node into hashtable, note the node has same value together */
    ppt_nodelist = (hashnode_t**)vector_at(&pt_hashtable->_t_bucket, t_pos);
    assert(ppt_nodelist != NULL);
    pt_cur = *ppt_nodelist;
    if(pt_cur == NULL)
    {
        pt_node->_pt_next = pt_cur;
        *ppt_nodelist = pt_node;
    }
    else
    {
        t_less = t_greater = _GET_HASHTABLE_TYPE_SIZE(pt_hashtable);
        /*pt_hashtable->_t_compare(pt_cur->_pc_data, pt_node->_pc_data, &t_less);*/
        /*pt_hashtable->_t_compare(pt_node->_pc_data, pt_cur->_pc_data, &t_greater);*/
        _hashtable_elem_compare_auxiliary(pt_hashtable, pt_cur->_pc_data, pt_node->_pc_data, &t_less);
        _hashtable_elem_compare_auxiliary(pt_hashtable, pt_node->_pc_data, pt_cur->_pc_data, &t_greater);
        if(!t_less && !t_greater)
        {
            pt_node->_pt_next = pt_cur;
            *ppt_nodelist = pt_node;
        }
        else
        {
            while(pt_cur->_pt_next != NULL)
            {
                t_less = t_greater = _GET_HASHTABLE_TYPE_SIZE(pt_hashtable);
                /*pt_hashtable->_t_compare(pt_cur->_pt_next->_pc_data, pt_node->_pc_data, &t_less);*/
                /*pt_hashtable->_t_compare(pt_node->_pc_data, pt_cur->_pt_next->_pc_data, &t_greater);*/
                _hashtable_elem_compare_auxiliary(
                    pt_hashtable, pt_cur->_pt_next->_pc_data, pt_node->_pc_data, &t_less);
                _hashtable_elem_compare_auxiliary(
                    pt_hashtable, pt_node->_pc_data, pt_cur->_pt_next->_pc_data, &t_greater);

                if(t_less || t_greater)
                {
                    pt_cur = pt_cur->_pt_next;
                }
                else
                {
                    break;
                }
            } 
            pt_node->_pt_next = pt_cur->_pt_next;
            pt_cur->_pt_next = pt_node;
        }
    }
    pt_hashtable->_t_nodecount++;

    _GET_HASHTABLE_BUCKETPOS(t_iterator) = (char*)ppt_nodelist;
    _GET_HASHTABLE_COREPOS(t_iterator) = (char*)pt_node;
    _GET_HASHTABLE_POINTER(t_iterator) = pt_hashtable;

    return t_iterator;
}

hashtable_iterator_t _hashtable_insert_unique(
    hashtable_t* pt_hashtable, const void* cpv_value)
{
    hashtable_iterator_t t_iter;

    if(_hashtable_empty(pt_hashtable))
    {
        return _hashtable_insert_equal(pt_hashtable, cpv_value);
    }
    else
    {
        t_iter = _hashtable_find(pt_hashtable, cpv_value);
        if(!_hashtable_iterator_equal(t_iter, _hashtable_end(pt_hashtable)))
        {
            return _hashtable_end(pt_hashtable);
        }
        else
        {
            return _hashtable_insert_equal(pt_hashtable, cpv_value);
        }
    }
}

hashtable_iterator_t _hashtable_find(
    const hashtable_t* cpt_hashtable, const void* cpv_value)
{
    hashtable_iterator_t t_iterator = _create_hashtable_iterator();
    size_t               t_bucketcount = 0;
    hashnode_t*          pt_node = NULL;
    hashnode_t**         ppt_bucket = NULL;
    size_t               t_tmp = 0;
    size_t               t_pos = 0;
    bool_t               t_less = false;
    bool_t               t_greater = false;

    assert(cpt_hashtable != NULL && cpv_value != NULL);

    t_bucketcount = _hashtable_bucket_count(cpt_hashtable);
    t_tmp = _GET_HASHTABLE_TYPE_SIZE(cpt_hashtable);
    /*cpt_hashtable->_t_hash(cpv_value, &t_tmp);*/
    _hashtable_hash_auxiliary(cpt_hashtable, cpv_value, &t_tmp);
    t_pos = t_tmp % t_bucketcount;
    ppt_bucket = (hashnode_t**)vector_at(&cpt_hashtable->_t_bucket, t_pos);
    pt_node = *ppt_bucket;

    while(pt_node != NULL)
    {
        t_less = t_greater = _GET_HASHTABLE_TYPE_SIZE(cpt_hashtable);
        /*cpt_hashtable->_t_compare(pt_node->_pc_data, cpv_value, &t_less);*/
        /*cpt_hashtable->_t_compare(cpv_value, pt_node->_pc_data, &t_greater);*/
        _hashtable_elem_compare_auxiliary(cpt_hashtable, pt_node->_pc_data, cpv_value, &t_less);
        _hashtable_elem_compare_auxiliary(cpt_hashtable, cpv_value, pt_node->_pc_data, &t_greater);
        if(t_less || t_greater)
        {
            pt_node = pt_node->_pt_next;
        }
        else
        {
            break;
        }
    }

    if(pt_node == NULL)
    {
        return _hashtable_end(cpt_hashtable);
    }
    else
    {
        _GET_HASHTABLE_BUCKETPOS(t_iterator) = (char*)ppt_bucket;
        _GET_HASHTABLE_COREPOS(t_iterator) = (char*)pt_node;
        _GET_HASHTABLE_POINTER(t_iterator) = (hashtable_t*)cpt_hashtable;

        return t_iterator;
    }
}

range_t _hashtable_equal_range(
    const hashtable_t* cpt_hashtable, const void* cpv_value)
{
    range_t      t_result;
    size_t       t_bucketcount = 0;
    hashnode_t*  pt_begin = NULL;
    hashnode_t*  pt_end = NULL;
    hashnode_t** ppt_bucket = NULL;
    size_t       t_tmp = 0;
    size_t       t_pos = 0;
    bool_t       t_less = false;
    bool_t       t_greater = false;
    size_t       t_index = 0;

    assert(cpt_hashtable != NULL && cpv_value != NULL);

    t_result.it_begin = _create_hashtable_iterator();
    t_result.it_end = _create_hashtable_iterator();

    t_bucketcount = _hashtable_bucket_count(cpt_hashtable);
    t_tmp = _GET_HASHTABLE_TYPE_SIZE(cpt_hashtable);
    /*cpt_hashtable->_t_hash(cpv_value, &t_tmp);*/
    _hashtable_hash_auxiliary(cpt_hashtable, cpv_value, &t_tmp);
    t_pos = t_tmp % t_bucketcount;
    ppt_bucket = (hashnode_t**)vector_at(&cpt_hashtable->_t_bucket, t_pos);

    for(pt_begin = *ppt_bucket; pt_begin != NULL; pt_begin = pt_begin->_pt_next)
    {
        t_less = t_greater = _GET_HASHTABLE_TYPE_SIZE(cpt_hashtable);
        /*cpt_hashtable->_t_compare(pt_begin->_pc_data, cpv_value, &t_less);*/
        /*cpt_hashtable->_t_compare(cpv_value, pt_begin->_pc_data, &t_greater);*/
        _hashtable_elem_compare_auxiliary(cpt_hashtable, pt_begin->_pc_data, cpv_value, &t_less);
        _hashtable_elem_compare_auxiliary(cpt_hashtable, cpv_value, pt_begin->_pc_data, &t_greater);
        if(!t_less && !t_greater)
        {
            for(pt_end = pt_begin->_pt_next;
                pt_end != NULL;
                pt_end = pt_end->_pt_next)
            {
                t_less = t_greater = _GET_HASHTABLE_TYPE_SIZE(cpt_hashtable);
                /*cpt_hashtable->_t_compare(pt_end->_pc_data, cpv_value, &t_less);*/
                /*cpt_hashtable->_t_compare(cpv_value, pt_end->_pc_data, &t_greater);*/
                _hashtable_elem_compare_auxiliary(cpt_hashtable, pt_end->_pc_data, cpv_value, &t_less);
                _hashtable_elem_compare_auxiliary(cpt_hashtable, cpv_value, pt_end->_pc_data, &t_greater);
                if(t_less || t_greater)
                {
                    _GET_HASHTABLE_BUCKETPOS(t_result.it_begin) = (char*)ppt_bucket;
                    _GET_HASHTABLE_COREPOS(t_result.it_begin) = (char*)pt_begin;
                    _GET_HASHTABLE_POINTER(t_result.it_begin) = (hashnode_t*)cpt_hashtable;

                    _GET_HASHTABLE_BUCKETPOS(t_result.it_end) = (char*)ppt_bucket;
                    _GET_HASHTABLE_COREPOS(t_result.it_end) = (char*)pt_end;
                    _GET_HASHTABLE_POINTER(t_result.it_end) = (hashtable_t*)cpt_hashtable;

                    return t_result;
                }
            }
            
            _GET_HASHTABLE_BUCKETPOS(t_result.it_begin) = (char*)ppt_bucket;
            _GET_HASHTABLE_COREPOS(t_result.it_begin) = (char*)pt_begin;
            _GET_HASHTABLE_POINTER(t_result.it_begin) = (hashtable_t*)cpt_hashtable;

            for(t_index = t_pos + 1; t_index < t_bucketcount; ++t_index)
            {
                ppt_bucket = (hashnode_t**)vector_at(&cpt_hashtable->_t_bucket, t_index);
                pt_end = *ppt_bucket;
                if(pt_end != NULL)
                {
                    _GET_HASHTABLE_BUCKETPOS(t_result.it_end) = (char*)ppt_bucket;
                    _GET_HASHTABLE_COREPOS(t_result.it_end) = (char*)pt_end;
                    _GET_HASHTABLE_POINTER(t_result.it_end) = (hashtable_t*)cpt_hashtable;

                    return t_result;
                }
            }

            t_result.it_end = _hashtable_end(cpt_hashtable);

            return t_result;
        }
    }

    t_result.it_begin = _hashtable_end(cpt_hashtable);
    t_result.it_end = _hashtable_end(cpt_hashtable);

    return t_result;
}

size_t _hashtable_count(const hashtable_t* cpt_hashtable, const void* cpv_value)
{
    range_t t_range = _hashtable_equal_range(cpt_hashtable, cpv_value);

    return abs(_hashtable_iterator_distance(t_range.it_begin, t_range.it_end));
}

void _hashtable_erase_pos(hashtable_t* pt_hashtable, hashtable_iterator_t t_pos)
{
    hashnode_t** ppt_bucket = NULL;
    hashnode_t*  pt_node = NULL;
    hashnode_t*  pt_deletion = NULL;
    bool_t       t_result = false;

    assert(_hashtable_iterator_belong_to_hashtable(pt_hashtable, t_pos));
    assert(!_hashtable_iterator_equal(t_pos, _hashtable_end(pt_hashtable)));

    /* get the previous node */
    ppt_bucket = (hashnode_t**)_GET_HASHTABLE_BUCKETPOS(t_pos);
    pt_node = *ppt_bucket;
    pt_deletion = (hashnode_t*)_GET_HASHTABLE_COREPOS(t_pos);
    if(pt_node == pt_deletion)
    {
        /* the deletion node is the first node of node list */
        *ppt_bucket = pt_node->_pt_next;
    }
    else
    {
        while(pt_node->_pt_next != NULL)
        {
            if(pt_node->_pt_next == pt_deletion)
            {
                pt_node->_pt_next = pt_deletion->_pt_next;
                break;
            }
            else
            {
                pt_node = pt_node->_pt_next;
            }
        }
    }
    /* delete the node */
    t_result = _GET_HASHTABLE_TYPE_SIZE(pt_hashtable);
    _GET_HASHTABLE_TYPE_DESTROY_FUNCTION(pt_hashtable)(pt_deletion->_pc_data, &t_result);
    assert(t_result);
    deallocate(&pt_hashtable->_t_allocater, pt_deletion,
        _HASHTABLE_NODE_SIZE(_GET_HASHTABLE_TYPE_SIZE(pt_hashtable)), 1);
    /* update the hashtable size */
    pt_hashtable->_t_nodecount--;
}

void _hashtable_erase_range(
    hashtable_t* pt_hashtable, hashtable_iterator_t t_begin, hashtable_iterator_t t_end)
{
    hashtable_iterator_t t_iterator;
    hashtable_iterator_t t_next;

    assert(_hashtable_iterator_belong_to_hashtable(pt_hashtable, t_begin));
    assert(_hashtable_iterator_equal(t_begin, t_end) ||
           _hashtable_iterator_before(t_begin, t_end));

    t_iterator = t_next = t_begin;
    if(!_hashtable_iterator_equal(t_next, _hashtable_end(pt_hashtable)))
    {
        t_next = _hashtable_iterator_next(t_next);
    }
    while(!_hashtable_iterator_equal(t_iterator, t_end))
    {
        _hashtable_erase_pos(pt_hashtable, t_iterator);

        t_iterator = t_next;
        if(!_hashtable_iterator_equal(t_next, _hashtable_end(pt_hashtable)))
        {
            t_next = _hashtable_iterator_next(t_next);
        }
    }
}

size_t _hashtable_erase(hashtable_t* pt_hashtable, const void* cpv_value)
{
    size_t t_countsize = _hashtable_count(pt_hashtable, cpv_value);
    range_t t_range = _hashtable_equal_range(pt_hashtable, cpv_value);

    if(!_hashtable_iterator_equal(t_range.it_begin, _hashtable_end(pt_hashtable)))
    {
        _hashtable_erase_range(pt_hashtable, t_range.it_begin, t_range.it_end);
    }

    return t_countsize;
}

void _hashtable_swap(
    hashtable_t* pt_hashtablefirst, hashtable_t* pt_hashtablesecond)
{
    hashtable_t t_hashtableswap;

    assert(_hashtable_same_type(pt_hashtablefirst, pt_hashtablesecond));

    t_hashtableswap = *pt_hashtablefirst;
    *pt_hashtablefirst = *pt_hashtablesecond;
    *pt_hashtablesecond = t_hashtableswap;
}

/* hashtable private function */
hashtable_t* _create_hashtable(const char* s_typename)
{
    hashtable_t* pt_newhashtable = NULL;

    if((pt_newhashtable = (hashtable_t*)malloc(sizeof(hashtable_t))) == NULL)
    {
        return NULL;
    }

    if(!_create_hashtable_auxiliary(pt_newhashtable, s_typename))
    {
        free(pt_newhashtable);
        return NULL;
    }

    return pt_newhashtable;
}

bool_t _create_hashtable_auxiliary(hashtable_t* pt_hashtable, const char* s_typename)
{
    assert(pt_hashtable != NULL && s_typename != NULL);

    /* create new vector */
    /* register hashnode_t* type for vecotr */
    _type_register(sizeof(hashnode_t*), _HASHTABLE_NODE_NAME,
        _hashnode_init, _hashnode_copy, _hashnode_less, _hashnode_destroy);
    if(!_create_vector_auxiliary(&pt_hashtable->_t_bucket, _HASHTABLE_NODE_NAME))
    {
        return false;
    }

    /* get type information */
    _type_get_type(&pt_hashtable->_t_typeinfo, s_typename);
    if(pt_hashtable->_t_typeinfo._t_style == _TYPE_INVALID)
    {
        return false;
    }

    pt_hashtable->_t_nodecount = 0;
    pt_hashtable->_t_hash = NULL;
    pt_hashtable->_t_compare = NULL;

    return true;;
}

void _hashtable_init(hashtable_t* pt_hashtable, size_t t_bucketcount,
    unary_function_t t_hash, binary_function_t t_compare)
{
    assert(pt_hashtable != NULL &&
           pt_hashtable->_t_hash == NULL &&
           pt_hashtable->_t_compare == NULL);

    /* initialize the allocator */
    allocate_init(&pt_hashtable->_t_allocater);

    /* initialize the bucket vector and node count */
    vector_init(&pt_hashtable->_t_bucket);
    if(t_bucketcount > 0)
    {
        vector_resize(&pt_hashtable->_t_bucket, _hashtable_get_prime(t_bucketcount));
    }
    else
    {
        vector_resize(&pt_hashtable->_t_bucket,
            _hashtable_get_prime(_HASHTABLE_DEFAULT_BUCKET_COUNT));
    }
    pt_hashtable->_t_nodecount = 0;

    /* initialize the hash, compare and destroy element function */
    pt_hashtable->_t_hash = t_hash != NULL ? t_hash : _hashtable_default_hash;
    pt_hashtable->_t_compare = t_compare != NULL ?
        t_compare : _GET_HASHTABLE_TYPE_LESS_FUNCTION(pt_hashtable);
}

void _hashtable_destroy_auxiliary(hashtable_t* pt_hashtable)
{
    assert(pt_hashtable != NULL);

    /* destroy all elements */
    _hashtable_clear(pt_hashtable);

    /* destroy bucket vector */
    _vector_destroy_auxiliary(&pt_hashtable->_t_bucket);

    /* destroy allocator */
    allocate_destroy(&pt_hashtable->_t_allocater);

    /* destroy hash, compare and destroy element function */
    pt_hashtable->_t_hash = NULL;
    pt_hashtable->_t_compare = NULL;
    pt_hashtable->_t_nodecount = 0;
}

void _hashtable_destroy(hashtable_t* pt_hashtable)
{
    _hashtable_destroy_auxiliary(pt_hashtable);
    free(pt_hashtable);
}

void _hashtable_init_copy(
    hashtable_t* pt_hashtabledest, const hashtable_t* cpt_hashtablesrc)
{
    assert(pt_hashtabledest != NULL && cpt_hashtablesrc != NULL);
    assert(pt_hashtabledest->_t_typeinfo._pt_type == cpt_hashtablesrc->_t_typeinfo._pt_type &&
        pt_hashtabledest->_t_typeinfo._t_style == cpt_hashtablesrc->_t_typeinfo._t_style);

    /* initialize the dest hashtable with src hashtable attribute */
    _hashtable_init(pt_hashtabledest, _hashtable_bucket_count(cpt_hashtablesrc),
        cpt_hashtablesrc->_t_hash, cpt_hashtablesrc->_t_compare);
    /* insert node from src to dest */
    if(!_hashtable_empty(cpt_hashtablesrc))
    {
        _hashtable_insert_equal_range(pt_hashtabledest, 
            _hashtable_begin(cpt_hashtablesrc), _hashtable_end(cpt_hashtablesrc));
    }
}

void _hashtable_init_copy_range(hashtable_t* pt_hashtabledest,
    hashtable_iterator_t t_begin, hashtable_iterator_t t_end,
    size_t t_bucketcount, unary_function_t t_hash, binary_function_t t_compare)
{
    assert(pt_hashtabledest != NULL);
    assert(_hashtable_same_hashtable_iterator_type(pt_hashtabledest, t_begin));

    /* initialize the dest hashtable with src hashtable attribute */
    _hashtable_init(pt_hashtabledest, t_bucketcount, t_hash, t_compare);
    /* insert node from src to dest */
    if(!_hashtable_empty(_GET_HASHTABLE(t_begin)))
    {
        _hashtable_insert_equal_range(pt_hashtabledest, t_begin, t_end);
    }
}

void _hashtable_assign(
    hashtable_t* pt_hashtabledest, const hashtable_t* cpt_hashtablesrc)
{
    assert(_hashtable_same_type(pt_hashtabledest, cpt_hashtablesrc));

    /* clear all elements */
    _hashtable_clear(pt_hashtabledest);
    /* insert node from src to dest */
    if(!_hashtable_empty(cpt_hashtablesrc))
    {
        _hashtable_insert_equal_range(pt_hashtabledest,
            _hashtable_begin(cpt_hashtablesrc), _hashtable_end(cpt_hashtablesrc));
    }
}

size_t _hashtable_size(const hashtable_t* cpt_hashtable)
{
    assert(cpt_hashtable != NULL);

    return cpt_hashtable->_t_nodecount;
}

bool_t _hashtable_empty(const hashtable_t* cpt_hashtable)
{
    assert(cpt_hashtable != NULL);

    if(cpt_hashtable->_t_nodecount == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

size_t _hashtable_max_size(const hashtable_t* cpt_hashtable)
{
    assert(cpt_hashtable != NULL);

    return (size_t)(-1) / _GET_HASHTABLE_TYPE_SIZE(cpt_hashtable);
}

size_t _hashtable_bucket_count(const hashtable_t* cpt_hashtable)
{
    assert(cpt_hashtable != NULL);

    return vector_size(&cpt_hashtable->_t_bucket);
}

hashtable_iterator_t _hashtable_begin(const hashtable_t* cpt_hashtable)
{
    vector_iterator_t    t_vectoriterator;
    hashtable_iterator_t t_newiterator = _create_hashtable_iterator();

    assert(cpt_hashtable != NULL);

    for(t_vectoriterator = vector_begin(&cpt_hashtable->_t_bucket);
        !iterator_equal(t_vectoriterator, vector_end(&cpt_hashtable->_t_bucket));
        t_vectoriterator = iterator_next(t_vectoriterator))
    {
        _GET_HASHTABLE_BUCKETPOS(t_newiterator) = _GET_VECTOR_COREPOS(t_vectoriterator);
        if(*(hashnode_t**)_GET_HASHTABLE_BUCKETPOS(t_newiterator) != NULL)
        {
            _GET_HASHTABLE_COREPOS(t_newiterator) = 
                (char*)*(hashnode_t**)_GET_HASHTABLE_BUCKETPOS(t_newiterator);
            break;
        }
    }
    if(iterator_equal(t_vectoriterator, vector_end(&cpt_hashtable->_t_bucket)))
    {
        assert(_GET_HASHTABLE_COREPOS(t_newiterator) == NULL);
        _GET_HASHTABLE_BUCKETPOS(t_newiterator) = _GET_VECTOR_COREPOS(t_vectoriterator);
    }
    _GET_HASHTABLE_POINTER(t_newiterator) = (hashtable_t*)cpt_hashtable;

    return t_newiterator;
}

hashtable_iterator_t _hashtable_end(const hashtable_t* cpt_hashtable)
{
    vector_iterator_t    t_vectorend;
    hashtable_iterator_t t_newiterator = _create_hashtable_iterator();

    assert(cpt_hashtable != NULL);

    t_vectorend = vector_end(&cpt_hashtable->_t_bucket);
    _GET_HASHTABLE_BUCKETPOS(t_newiterator) = _GET_VECTOR_COREPOS(t_vectorend);
    _GET_HASHTABLE_COREPOS(t_newiterator) = NULL;
    _GET_HASHTABLE_POINTER(t_newiterator) = (hashtable_t*)cpt_hashtable;

    return t_newiterator;
}

void _hashtable_clear(hashtable_t* pt_hashtable)
{
    size_t      t_bucketcount = 0;
    size_t      t_index = 0;
    hashnode_t* pt_node = NULL;
    hashnode_t* pt_deletion = NULL;
    bool_t      t_result = false;

    assert(pt_hashtable != NULL);

    t_bucketcount = vector_size(&pt_hashtable->_t_bucket);
    /* iterator all bucket node */
    for(t_index = 0; t_index < t_bucketcount; ++t_index)
    {
        /* iterator all element list for one bucket node */
        pt_node = *(hashnode_t**)vector_at(&pt_hashtable->_t_bucket, t_index);
        *(hashnode_t**)vector_at(&pt_hashtable->_t_bucket, t_index) = NULL;
        while(pt_node != NULL)
        {
            /* delete each element */
            pt_deletion = pt_node;
            pt_node = pt_node->_pt_next;

            /* destroy element */
            t_result = _GET_HASHTABLE_TYPE_SIZE(pt_hashtable);
            _GET_HASHTABLE_TYPE_DESTROY_FUNCTION(pt_hashtable)(
                pt_deletion->_pc_data, &t_result);
            assert(t_result);
            deallocate(&pt_hashtable->_t_allocater,  pt_deletion, 
                _HASHTABLE_NODE_SIZE(_GET_HASHTABLE_TYPE_SIZE(pt_hashtable)), 1);
        }
    }
    
    pt_hashtable->_t_nodecount = 0;
}

unary_function_t _hashtable_hash(const hashtable_t* cpt_hashtable)
{
    assert(cpt_hashtable != NULL);

    return cpt_hashtable->_t_hash;
}

binary_function_t _hashtable_key_comp(const hashtable_t* cpt_hashtable)
{
    assert(cpt_hashtable != NULL);

    return cpt_hashtable->_t_compare;
}

bool_t _hashtable_equal(
    const hashtable_t* cpt_hashtablefirst, 
    const hashtable_t* cpt_hashtablesecond)
{
    hashtable_iterator_t t_first;
    hashtable_iterator_t t_second;
    bool_t               t_less = false;
    bool_t               t_greater = false;

    assert(cpt_hashtablefirst != NULL && cpt_hashtablesecond != NULL);

    /* check type */
    if(!_hashtable_same_type(cpt_hashtablefirst, cpt_hashtablesecond))
    {
        return false;
    }
    /* check size */
    if(_hashtable_size(cpt_hashtablefirst) != _hashtable_size(cpt_hashtablesecond))
    {
        return false;
    }
    /* check each element */
    for(t_first = _hashtable_begin(cpt_hashtablefirst),
        t_second = _hashtable_begin(cpt_hashtablesecond);
        !_hashtable_iterator_equal(t_first, _hashtable_end(cpt_hashtablefirst)) && 
        !_hashtable_iterator_equal(t_second, _hashtable_end(cpt_hashtablesecond));
        t_first = _hashtable_iterator_next(t_first),
        t_second = _hashtable_iterator_next(t_second))
    {
        t_less = t_greater = _GET_HASHTABLE_TYPE_SIZE(cpt_hashtablefirst);
        _GET_HASHTABLE_TYPE_LESS_FUNCTION(cpt_hashtablefirst)(
                ((hashnode_t*)_GET_HASHTABLE_COREPOS(t_first))->_pc_data,
                ((hashnode_t*)_GET_HASHTABLE_COREPOS(t_second))->_pc_data, &t_less);
        _GET_HASHTABLE_TYPE_LESS_FUNCTION(cpt_hashtablefirst)(
                ((hashnode_t*)_GET_HASHTABLE_COREPOS(t_second))->_pc_data,
                ((hashnode_t*)_GET_HASHTABLE_COREPOS(t_first))->_pc_data, &t_greater);
        /*
        _hashtable_elem_less_auxiliary(cpt_hashtablefirst,
            ((hashnode_t*)_GET_HASHTABLE_COREPOS(t_first))->_pc_data,
            ((hashnode_t*)_GET_HASHTABLE_COREPOS(t_second))->_pc_data, &t_less);
        _hashtable_elem_less_auxiliary(cpt_hashtablefirst,
            ((hashnode_t*)_GET_HASHTABLE_COREPOS(t_second))->_pc_data,
            ((hashnode_t*)_GET_HASHTABLE_COREPOS(t_first))->_pc_data, &t_greater);
        */
        if(t_less || t_greater)
        {
            return false;
        }
    }

    assert(_hashtable_iterator_equal(t_first, _hashtable_end(cpt_hashtablefirst)) &&
           _hashtable_iterator_equal(t_second, _hashtable_end(cpt_hashtablesecond)));

    return true;
}

bool_t _hashtable_not_equal(
    const hashtable_t* cpt_hashtablefirst, const hashtable_t* cpt_hashtablesecond)
{
    return !_hashtable_equal(cpt_hashtablefirst, cpt_hashtablesecond);
}

bool_t _hashtable_less(
    const hashtable_t* cpt_hashtablefirst, const hashtable_t* cpt_hashtablesecond)
{
    hashtable_iterator_t t_first;
    hashtable_iterator_t t_second;
    bool_t               t_less = false;
    bool_t               t_greater = false;

    assert(_hashtable_same_type(cpt_hashtablefirst, cpt_hashtablesecond));

    /* check vector bucket count */
    if(vector_size(&cpt_hashtablefirst->_t_bucket) ==
       vector_size(&cpt_hashtablesecond->_t_bucket))
    {
        /* check each element */
        for(t_first = _hashtable_begin(cpt_hashtablefirst),
            t_second = _hashtable_begin(cpt_hashtablesecond);
            !_hashtable_iterator_equal(t_first, _hashtable_end(cpt_hashtablefirst)) && 
            !_hashtable_iterator_equal(t_second, _hashtable_end(cpt_hashtablesecond));
            t_first = _hashtable_iterator_next(t_first),
            t_second = _hashtable_iterator_next(t_second))
        {
            t_less = _GET_HASHTABLE_TYPE_SIZE(cpt_hashtablefirst);
            _GET_HASHTABLE_TYPE_LESS_FUNCTION(cpt_hashtablefirst)(
                    ((hashnode_t*)_GET_HASHTABLE_COREPOS(t_first))->_pc_data,
                    ((hashnode_t*)_GET_HASHTABLE_COREPOS(t_second))->_pc_data, &t_less);
            /*
            _hashtable_elem_less_auxiliary(cpt_hashtablefirst,
                ((hashnode_t*)_GET_HASHTABLE_COREPOS(t_first))->_pc_data,
                ((hashnode_t*)_GET_HASHTABLE_COREPOS(t_second))->_pc_data, &t_less);
            */
            if(t_less)
            {
                return true;
            }
            t_greater = _GET_HASHTABLE_TYPE_SIZE(cpt_hashtablefirst);
            _GET_HASHTABLE_TYPE_LESS_FUNCTION(cpt_hashtablefirst)(
                    ((hashnode_t*)_GET_HASHTABLE_COREPOS(t_second))->_pc_data,
                    ((hashnode_t*)_GET_HASHTABLE_COREPOS(t_first))->_pc_data, &t_greater);
            /*
            _hashtable_elem_less_auxiliary(cpt_hashtablefirst,
                ((hashnode_t*)_GET_HASHTABLE_COREPOS(t_second))->_pc_data,
                ((hashnode_t*)_GET_HASHTABLE_COREPOS(t_first))->_pc_data, &t_greater);
            */
            if(t_greater)
            {
                return false;
            }
        }
    }

    return _hashtable_size(cpt_hashtablefirst) < _hashtable_size(cpt_hashtablesecond) ?
           true : false;
}

bool_t _hashtable_less_equal(
    const hashtable_t* cpt_hashtablefirst, const hashtable_t* cpt_hashtablesecond)
{
    return (_hashtable_less(cpt_hashtablefirst, cpt_hashtablesecond) ||
            _hashtable_equal(cpt_hashtablefirst, cpt_hashtablesecond)) ? true : false;
}

bool_t _hashtable_greater(
    const hashtable_t* cpt_hashtablefirst, const hashtable_t* cpt_hashtablesecond)
{
    return _hashtable_less(cpt_hashtablesecond, cpt_hashtablefirst);
}

bool_t _hashtable_greater_equal(
    const hashtable_t* cpt_hashtablefirst, const hashtable_t* cpt_hashtablesecond)
{
    return (_hashtable_greater(cpt_hashtablefirst, cpt_hashtablesecond) ||
            _hashtable_equal(cpt_hashtablefirst, cpt_hashtablesecond)) ? true : false;
}

void _hashtable_insert_equal_range(
    hashtable_t* pt_hashtable, hashtable_iterator_t t_begin, hashtable_iterator_t t_end)
{
    hashtable_iterator_t t_iterator;

    assert(_hashtable_same_hashtable_iterator_type(pt_hashtable, t_begin));
    assert(_hashtable_iterator_equal(t_begin, t_end) ||
           _hashtable_iterator_before(t_begin, t_end));

    for(t_iterator = t_begin;
        !_hashtable_iterator_equal(t_iterator, t_end);
        t_iterator = _hashtable_iterator_next(t_iterator))
    {
        _hashtable_insert_equal(
            pt_hashtable, ((hashnode_t*)_GET_HASHTABLE_COREPOS(t_iterator))->_pc_data);
    }
}

void _hashtable_insert_unique_range(
    hashtable_t* pt_hashtable, hashtable_iterator_t t_begin, hashtable_iterator_t t_end)
{
    hashtable_iterator_t t_iterator;

    assert(_hashtable_same_hashtable_iterator_type(pt_hashtable, t_begin));
    assert(_hashtable_iterator_equal(t_begin, t_end) ||
           _hashtable_iterator_before(t_begin, t_end));

    for(t_iterator = t_begin;
        !_hashtable_iterator_equal(t_iterator, t_end);
        t_iterator = _hashtable_iterator_next(t_iterator))
    {
        _hashtable_insert_unique(
            pt_hashtable, ((hashnode_t*)_GET_HASHTABLE_COREPOS(t_iterator))->_pc_data);
    }
}

/** local function implementation section **/
#ifndef NDEBUG
static bool_t _hashtable_iterator_belong_to_hashtable(
    const hashtable_t* cpt_hashtable, hashtable_iterator_t t_iter)
{
    vector_iterator_t t_vectoriterator;

    assert(cpt_hashtable != NULL);
    assert(_GET_HASHTABLE(t_iter) == cpt_hashtable);

    /* check for the end node */
    t_vectoriterator = vector_end(&cpt_hashtable->_t_bucket);
    if(_GET_VECTOR_COREPOS(t_vectoriterator) == _GET_HASHTABLE_BUCKETPOS(t_iter) &&
       _GET_HASHTABLE_COREPOS(t_iter) == NULL)
    {
        return true;
    }
    else
    {
        hashnode_t* pt_node = NULL;
        for(t_vectoriterator = vector_begin(&cpt_hashtable->_t_bucket);
            !iterator_equal(t_vectoriterator, vector_end(&cpt_hashtable->_t_bucket));
            t_vectoriterator = iterator_next(t_vectoriterator))
        {
            if(_GET_HASHTABLE_BUCKETPOS(t_iter) ==
               _GET_VECTOR_COREPOS(t_vectoriterator))
            {
                pt_node = *(hashnode_t**)_GET_VECTOR_COREPOS(t_vectoriterator);
                while(pt_node != NULL)
                {
                    if(pt_node == (hashnode_t*)_GET_HASHTABLE_COREPOS(t_iter))
                    {
                        return true;
                    }

                    pt_node = pt_node->_pt_next;
                }
            }
        }

        return false;
    }
}

static bool_t _hashtable_same_hashtable_iterator_type(
    const hashtable_t* cpt_hashtable, hashtable_iterator_t t_iter)
{
    assert(cpt_hashtable != NULL && _GET_HASHTABLE(t_iter) != NULL);
    return _type_is_same(_GET_HASHTABLE_TYPE_NAME(cpt_hashtable),
                         _GET_HASHTABLE_TYPE_NAME(_GET_HASHTABLE(t_iter))) &&
           (cpt_hashtable->_t_typeinfo._pt_type ==
            _GET_HASHTABLE(t_iter)->_t_typeinfo._pt_type) &&
           (cpt_hashtable->_t_typeinfo._t_style ==
            _GET_HASHTABLE(t_iter)->_t_typeinfo._t_style);
}
#endif /* NDEBUG */

static bool_t _hashtable_same_type(
    const hashtable_t* cpt_hashtablefirst, const hashtable_t* cpt_hashtablesecond)
{
    assert(cpt_hashtablefirst != NULL && cpt_hashtablesecond != NULL);

    return _type_is_same(_GET_HASHTABLE_TYPE_NAME(cpt_hashtablefirst),
                         _GET_HASHTABLE_TYPE_NAME(cpt_hashtablesecond)) &&
           (cpt_hashtablefirst->_t_typeinfo._pt_type ==
            cpt_hashtablesecond->_t_typeinfo._pt_type) &&
           (cpt_hashtablefirst->_t_typeinfo._t_style ==
            cpt_hashtablesecond->_t_typeinfo._t_style) &&
           (cpt_hashtablefirst->_t_hash == cpt_hashtablesecond->_t_hash) &&
           (cpt_hashtablefirst->_t_compare == cpt_hashtablesecond->_t_compare);
}

static unsigned long _hashtable_get_prime(unsigned long ul_basenum)
{
    int i;
    for(i = 0; i < _HASHTABLE_PRIME_LIST_COUNT; ++i)
    {
        if(_hashtable_prime_list[i] >= ul_basenum)
        {
            return _hashtable_prime_list[i];
        }
    }

    return ul_basenum;
}

static void _hashtable_default_hash(const void* cpv_input, void* pv_output)
{
    size_t t_sum = 0;
    char*  pc_value = NULL;
    size_t t_index = 0;

    assert(cpv_input != NULL && pv_output != NULL);

    pc_value = (char*)cpv_input;
    for(t_index = 0; t_index < *(size_t*)pv_output; ++t_index)
    {
        t_sum += (size_t)pc_value[t_index];
    }

    *(size_t*)pv_output = t_sum;
}

static void _hashnode_init(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);

    *(hashnode_t**)cpv_input = NULL;
    *(bool_t*)pv_output = true;
}

static void _hashnode_copy(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(hashnode_t**)cpv_first = *(hashnode_t**)cpv_second;
    *(bool_t*)pv_output = true;
}

static void _hashnode_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(hashnode_t**)cpv_first < *(hashnode_t**)cpv_second ? true : false;
}

static void _hashnode_destroy(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);

    *(hashnode_t**)cpv_input = NULL;
    *(bool_t*)pv_output = true;
}

static void _hashtable_init_elem_auxiliary(hashtable_t* pt_hashtable, hashnode_t* pt_node)
{
    assert(pt_hashtable != NULL && pt_node != NULL);

    /* initialize new elements */
    if(_GET_HASHTABLE_TYPE_STYLE(pt_hashtable) == _TYPE_CSTL_BUILTIN)
    {
        /* get element type name */
        char s_elemtypename[_TYPE_NAME_SIZE + 1];
        _type_get_elem_typename(_GET_HASHTABLE_TYPE_NAME(pt_hashtable), s_elemtypename);

        _GET_HASHTABLE_TYPE_INIT_FUNCTION(pt_hashtable)(pt_node->_pc_data, s_elemtypename);
    }
    else
    {
        bool_t t_result = _GET_HASHTABLE_TYPE_SIZE(pt_hashtable);
        _GET_HASHTABLE_TYPE_INIT_FUNCTION(pt_hashtable)(pt_node->_pc_data, &t_result);
        assert(t_result);
    }
}

static void _hashtable_hash_auxiliary(const hashtable_t* cpt_hashtable, const void* cpv_input, void* pv_output)
{
    assert(cpt_hashtable != NULL && cpv_input != NULL && pv_output != NULL);

    if(strncmp(_GET_HASHTABLE_TYPE_NAME(cpt_hashtable), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        *(size_t*)pv_output = strlen(string_c_str((string_t*)cpv_input));
        cpt_hashtable->_t_hash(string_c_str((string_t*)cpv_input), pv_output);
    }
    else
    {
        cpt_hashtable->_t_hash(cpv_input, pv_output);
    } 
}

static void _hashtable_elem_compare_auxiliary(const hashtable_t* cpt_hashtable,
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpt_hashtable != NULL && cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    if(strncmp(_GET_HASHTABLE_TYPE_NAME(cpt_hashtable), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0 &&
       cpt_hashtable->_t_compare != _GET_HASHTABLE_TYPE_LESS_FUNCTION(cpt_hashtable))
    {
        cpt_hashtable->_t_compare(string_c_str((string_t*)cpv_first), string_c_str((string_t*)cpv_second), pv_output);
    }
    else
    {
        cpt_hashtable->_t_compare(cpv_first, cpv_second, pv_output);
    }
}

/** eof **/

