/*
 *  The implementation of hash_multimap.
 *  Copyright (C)  2008 2009  Wangbo
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
#include "cstl_iterator.h"

#include "cvector.h"
#include "cstl_hashtable_iterator.h"
#include "cstl_hashtable_private.h"
#include "cutility.h"
#include "cstring.h"

#include "cstl_hash_multimap_iterator.h"
#include "cstl_hash_multimap_private.h"
#include "cstl_hash_multimap.h"

/** local constant declaration and local macro section **/
/* macros for type informations */
#define _GET_HASH_MULTIMAP_FIRST_TYPE_SIZE(pt_hash_multimap)\
    ((pt_hash_multimap)->_t_pair._t_typeinfofirst._pt_type->_t_typesize)
#define _GET_HASH_MULTIMAP_FIRST_TYPE_NAME(pt_hash_multimap)\
    ((pt_hash_multimap)->_t_pair._t_typeinfofirst._sz_typename)
#define _GET_HASH_MULTIMAP_FIRST_TYPE_BASENAME(pt_hash_multimap)\
    ((pt_hash_multimap)->_t_pair._t_typeinfofirst._pt_type->_sz_typename)
#define _GET_HASH_MULTIMAP_FIRST_TYPE_INIT_FUNCTION(pt_hash_multimap)\
    ((pt_hash_multimap)->_t_pair._t_typeinfofirst._pt_type->_t_typeinit)
#define _GET_HASH_MULTIMAP_FIRST_TYPE_COPY_FUNCTION(pt_hash_multimap)\
    ((pt_hash_multimap)->_t_pair._t_typeinfofirst._pt_type->_t_typecopy)
#define _GET_HASH_MULTIMAP_FIRST_TYPE_LESS_FUNCTION(pt_hash_multimap)\
    ((pt_hash_multimap)->_t_pair._t_typeinfofirst._pt_type->_t_typeless)
#define _GET_HASH_MULTIMAP_FIRST_TYPE_DESTROY_FUNCTION(pt_hash_multimap)\
    ((pt_hash_multimap)->_t_pair._t_typeinfofirst._pt_type->_t_typedestroy)
#define _GET_HASH_MULTIMAP_FIRST_TYPE_STYLE(pt_hash_multimap)\
    ((pt_hash_multimap)->_t_pair._t_typeinfofirst._t_style)

#define _GET_HASH_MULTIMAP_SECOND_TYPE_SIZE(pt_hash_multimap)\
    ((pt_hash_multimap)->_t_pair._t_typeinfosecond._pt_type->_t_typesize)
#define _GET_HASH_MULTIMAP_SECOND_TYPE_NAME(pt_hash_multimap)\
    ((pt_hash_multimap)->_t_pair._t_typeinfosecond._sz_typename)
#define _GET_HASH_MULTIMAP_SECOND_TYPE_BASENAME(pt_hash_multimap)\
    ((pt_hash_multimap)->_t_pair._t_typeinfosecond._pt_type->_sz_typename)
#define _GET_HASH_MULTIMAP_SECOND_TYPE_INIT_FUNCTION(pt_hash_multimap)\
    ((pt_hash_multimap)->_t_pair._t_typeinfosecond._pt_type->_t_typeinit)
#define _GET_HASH_MULTIMAP_SECOND_TYPE_COPY_FUNCTION(pt_hash_multimap)\
    ((pt_hash_multimap)->_t_pair._t_typeinfosecond._pt_type->_t_typecopy)
#define _GET_HASH_MULTIMAP_SECOND_TYPE_LESS_FUNCTION(pt_hash_multimap)\
    ((pt_hash_multimap)->_t_pair._t_typeinfosecond._pt_type->_t_typeless)
#define _GET_HASH_MULTIMAP_SECOND_TYPE_DESTROY_FUNCTION(pt_hash_multimap)\
    ((pt_hash_multimap)->_t_pair._t_typeinfosecond._pt_type->_t_typedestroy)
#define _GET_HASH_MULTIMAP_SECOND_TYPE_STYLE(pt_hash_multimap)\
    ((pt_hash_multimap)->_t_pair._t_typeinfosecond._t_style)

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/
#ifndef NDEBUG
/*
 * Assert support.
 */
static bool_t _same_hash_multimap_pair_type(
    const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond);
#endif /* NDEBUG */

/*
 * hash_multimap element compare function.
 */
static int _hash_multimap_cmp(const void* cpv_firstelem, const void* cpv_secondelem);

/*
 * Destroy element function.
 */
static void _hash_multimap_destroy_elem(void* pv_value);

/*
 * hash_multimap default hash function.
 */
static int _hash_multimap_hash_function(
    const void* cpv_value, size_t t_nodesize, size_t t_bucketcount);

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/* hash_multimap iterator function */
hash_multimap_iterator_t create_hash_multimap_iterator(void)
{
    hash_multimap_iterator_t t_newiterator = _create_hashtable_iterator();

    _GET_HASH_MULTIMAP_CONTAINER_TYPE(t_newiterator) = _HASH_MULTIMAP_CONTAINER;
    _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_newiterator) = _FORWARD_ITERATOR;

    return t_newiterator;
}

void _hash_multimap_iterator_get_value(
    hash_multimap_iterator_t t_iter, void* pv_value)
{
    assert(pv_value != NULL);
    assert(_GET_HASH_MULTIMAP_CONTAINER_TYPE(t_iter) == _HASH_MULTIMAP_CONTAINER &&
           _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_iter) == _FORWARD_ITERATOR);

    _hashtable_iterator_get_value(t_iter, pv_value);
}

const void* _hash_multimap_iterator_get_pointer(hash_multimap_iterator_t t_iter)
{
    assert(_GET_HASH_MULTIMAP_CONTAINER_TYPE(t_iter) == _HASH_MULTIMAP_CONTAINER &&
           _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_iter) == _FORWARD_ITERATOR);

    return _hashtable_iterator_get_pointer(t_iter);
}

hash_multimap_iterator_t _hash_multimap_iterator_next(hash_multimap_iterator_t t_iter)
{
    assert(_GET_HASH_MULTIMAP_CONTAINER_TYPE(t_iter) == _HASH_MULTIMAP_CONTAINER &&
           _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_iter) == _FORWARD_ITERATOR);

    return _hashtable_iterator_next(t_iter);
}

bool_t _hash_multimap_iterator_equal(
    hash_multimap_iterator_t t_iterfirst, hash_multimap_iterator_t t_itersecond)
{
    assert(_GET_HASH_MULTIMAP_CONTAINER_TYPE(t_iterfirst) == _HASH_MULTIMAP_CONTAINER &&
           _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_iterfirst) == _FORWARD_ITERATOR &&
           _GET_HASH_MULTIMAP_CONTAINER_TYPE(t_itersecond) == _HASH_MULTIMAP_CONTAINER &&
           _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_itersecond) == _FORWARD_ITERATOR);

    return _hashtable_iterator_equal(t_iterfirst, t_itersecond);
}

int _hash_multimap_iterator_distance(
    hash_multimap_iterator_t t_iterfirst, hash_multimap_iterator_t t_itersecond)
{
    assert(_GET_HASH_MULTIMAP_CONTAINER_TYPE(t_iterfirst) == _HASH_MULTIMAP_CONTAINER &&
           _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_iterfirst) == _FORWARD_ITERATOR &&
           _GET_HASH_MULTIMAP_CONTAINER_TYPE(t_itersecond) == _HASH_MULTIMAP_CONTAINER &&
           _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_itersecond) == _FORWARD_ITERATOR &&
           _GET_HASH_MULTIMAP_CONTAINER(t_iterfirst) == 
               _GET_HASH_MULTIMAP_CONTAINER(t_itersecond));

    return _hashtable_iterator_distance(t_iterfirst, t_itersecond);
}

bool_t _hash_multimap_iterator_before(
    hash_multimap_iterator_t t_iterfirst, hash_multimap_iterator_t t_itersecond)
{
    assert(_GET_HASH_MULTIMAP_CONTAINER_TYPE(t_iterfirst) == _HASH_MULTIMAP_CONTAINER &&
           _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_iterfirst) == _FORWARD_ITERATOR &&
           _GET_HASH_MULTIMAP_CONTAINER_TYPE(t_itersecond) == _HASH_MULTIMAP_CONTAINER &&
           _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_itersecond) == _FORWARD_ITERATOR &&
           _GET_HASH_MULTIMAP_CONTAINER(t_iterfirst) == 
               _GET_HASH_MULTIMAP_CONTAINER(t_itersecond));

    return _hashtable_iterator_before(t_iterfirst, t_itersecond);
}

/* hash_multimap private function */
hash_multimap_t _create_hash_multimap(
    size_t t_keytypesize, const char* s_keytypename, 
    size_t t_valuetypesize, const char* s_valuetypename)
{
    hash_multimap_t t_new_hash_multimap;
    char            ac_hashmultimaptypename[_ELEM_TYPE_NAME_SIZE+1];

    assert(t_keytypesize > 0 && t_valuetypesize > 0);
    assert(s_keytypename != NULL && s_valuetypename != NULL);

    /* create pair */
    t_new_hash_multimap._t_pair = _create_pair(
        t_keytypesize, s_keytypename, t_valuetypesize, s_valuetypename);
    /* create tree */
    memset(ac_hashmultimaptypename, '\0', _ELEM_TYPE_NAME_SIZE+1);
    strncpy(ac_hashmultimaptypename, _HASH_MULTIMAP_IDENTIFY, _ELEM_TYPE_NAME_SIZE);
    strcat(ac_hashmultimaptypename, _HASH_MULTIMAP_LEFT_BRACKET);
    strcat(ac_hashmultimaptypename, t_new_hash_multimap._t_pair._sz_firsttypename);
    strcat(ac_hashmultimaptypename, _HASH_MULTIMAP_COMMA);
    strcat(ac_hashmultimaptypename, t_new_hash_multimap._t_pair._sz_secondtypename);
    strcat(ac_hashmultimaptypename, _HASH_MULTIMAP_RIGHT_BRACKET);

    t_new_hash_multimap._t_hashtable = 
        _create_hashtable(sizeof(pair_t), ac_hashmultimaptypename);

    return t_new_hash_multimap;
}

/* hash_multimap function */
void hash_multimap_init(
    hash_multimap_t* pt_hash_multimap,
    int (*pfun_hash)(const void*, size_t, size_t))
{
    hash_multimap_init_n(pt_hash_multimap, 0, pfun_hash);
}

void hash_multimap_init_n(
    hash_multimap_t* pt_hash_multimap, size_t t_bucketcount,
    int (*pfun_hash)(const void*, size_t, size_t))
{
    assert(pt_hash_multimap != NULL);

    /* initialize the pair */
    pair_init(&pt_hash_multimap->_t_pair);
    /* initialize the hashtable */
    if(pfun_hash != NULL)
    {
        _hashtable_init(
            &pt_hash_multimap->_t_hashtable, t_bucketcount, pfun_hash, 
            _hash_multimap_cmp, _hash_multimap_destroy_elem);
    }
    else
    {
        _hashtable_init(
            &pt_hash_multimap->_t_hashtable, t_bucketcount, _hash_multimap_hash_function,
            _hash_multimap_cmp, _hash_multimap_destroy_elem);
    }
}

void hash_multimap_destroy(hash_multimap_t* pt_hash_multimap)
{
    assert(pt_hash_multimap != NULL);

    pair_destroy(&pt_hash_multimap->_t_pair);
    _hashtable_destroy(&pt_hash_multimap->_t_hashtable);
}

void hash_multimap_init_copy(
    hash_multimap_t* pt_hash_multimapdest, const hash_multimap_t* cpt_hash_multimapsrc)
{
    assert(pt_hash_multimapdest != NULL && cpt_hash_multimapsrc != NULL);
    assert(
        pt_hash_multimapdest->_t_pair._t_firsttypesize == 
            cpt_hash_multimapsrc->_t_pair._t_firsttypesize &&
        pt_hash_multimapdest->_t_pair._t_secondtypesize == 
            cpt_hash_multimapsrc->_t_pair._t_secondtypesize);
    assert(
        strncmp(
            pt_hash_multimapdest->_t_pair._sz_firsttypename,
            cpt_hash_multimapsrc->_t_pair._sz_firsttypename,
            _ELEM_TYPE_NAME_SIZE) == 0 &&
        strncmp(
            pt_hash_multimapdest->_t_pair._sz_secondtypename,
            cpt_hash_multimapsrc->_t_pair._sz_secondtypename,
            _ELEM_TYPE_NAME_SIZE) == 0);

    hash_multimap_init_n(
        pt_hash_multimapdest,
        hash_multimap_bucket_count(cpt_hash_multimapsrc),
        hash_multimap_hash_func(cpt_hash_multimapsrc));

    if(!hash_multimap_empty(cpt_hash_multimapsrc))
    {
        hash_multimap_insert_range(
            pt_hash_multimapdest, 
            hash_multimap_begin(cpt_hash_multimapsrc), 
            hash_multimap_end(cpt_hash_multimapsrc));
    }
}

void hash_multimap_init_copy_range(
    hash_multimap_t* pt_hash_multimapdest, hash_multimap_iterator_t t_begin,
    hash_multimap_iterator_t t_end, int (*pfun_hash)(const void*, size_t, size_t))
{
    hash_multimap_init_copy_range_n(
        pt_hash_multimapdest, t_begin, t_end, 0, pfun_hash);
}

void hash_multimap_init_copy_range_n(
    hash_multimap_t* pt_hash_multimapdest, hash_multimap_iterator_t t_begin,
    hash_multimap_iterator_t t_end, size_t t_bucketcount,
    int (*pfun_hash)(const void*, size_t, size_t))
{
    assert(pt_hash_multimapdest != NULL);
    assert(_GET_HASH_MULTIMAP_CONTAINER_TYPE(t_begin) == _HASH_MULTIMAP_CONTAINER &&
           _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_begin) == _FORWARD_ITERATOR &&
           _GET_HASH_MULTIMAP_CONTAINER_TYPE(t_end) == _HASH_MULTIMAP_CONTAINER &&
           _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_end) == _FORWARD_ITERATOR);
    assert(_GET_HASH_MULTIMAP_CONTAINER(t_begin) != pt_hash_multimapdest &&
           _GET_HASH_MULTIMAP_CONTAINER(t_end) != pt_hash_multimapdest &&
           _GET_HASH_MULTIMAP_CONTAINER(t_begin) == 
               _GET_HASH_MULTIMAP_CONTAINER(t_end));
    assert(pt_hash_multimapdest->_t_pair._t_firsttypesize == 
               _GET_HASH_MULTIMAP_CONTAINER(t_begin)->_t_pair._t_firsttypesize &&
           pt_hash_multimapdest->_t_pair._t_secondtypesize == 
               _GET_HASH_MULTIMAP_CONTAINER(t_begin)->_t_pair._t_secondtypesize);
    assert(strncmp(pt_hash_multimapdest->_t_pair._sz_firsttypename,
               _GET_HASH_MULTIMAP_CONTAINER(t_begin)->_t_pair._sz_firsttypename,
               _ELEM_TYPE_NAME_SIZE) == 0 &&
           strncmp(pt_hash_multimapdest->_t_pair._sz_secondtypename,
               _GET_HASH_MULTIMAP_CONTAINER(t_begin)->_t_pair._sz_secondtypename,
               _ELEM_TYPE_NAME_SIZE) == 0);

    hash_multimap_init_n(pt_hash_multimapdest, t_bucketcount, pfun_hash);

    if(!hash_multimap_empty(_GET_HASH_MULTIMAP_CONTAINER(t_begin)))
    {
        hash_multimap_insert_range(pt_hash_multimapdest, t_begin, t_end);
    }
}

void hash_multimap_assign(
    hash_multimap_t* pt_hash_multimapdest, 
    const hash_multimap_t* cpt_hash_multimapsrc)
{
    assert(pt_hash_multimapdest != NULL && cpt_hash_multimapsrc != NULL);
    assert(_same_hash_multimap_pair_type(
        &pt_hash_multimapdest->_t_pair, &cpt_hash_multimapsrc->_t_pair));

    hash_multimap_destroy(pt_hash_multimapdest);
    hash_multimap_init_n(
        pt_hash_multimapdest,
        hash_multimap_bucket_count(cpt_hash_multimapsrc),
        hash_multimap_hash_func(cpt_hash_multimapsrc));

    if(!hash_multimap_empty(cpt_hash_multimapsrc))
    {
        hash_multimap_insert_range(
            pt_hash_multimapdest, 
            hash_multimap_begin(cpt_hash_multimapsrc), 
            hash_multimap_end(cpt_hash_multimapsrc));
    }
}

void hash_multimap_swap(
    hash_multimap_t* pt_hash_multimapfirst, 
    hash_multimap_t* pt_hash_multimapsecond)
{
    assert(pt_hash_multimapfirst != NULL && pt_hash_multimapsecond != NULL);
    assert(_same_hash_multimap_pair_type(
        &pt_hash_multimapfirst->_t_pair, &pt_hash_multimapsecond->_t_pair));

    _hashtable_swap(
        &pt_hash_multimapfirst->_t_hashtable, 
        &pt_hash_multimapsecond->_t_hashtable);
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

int (*hash_multimap_hash_func(const hash_multimap_t* cpt_hash_multimap))(
    const void*, size_t, size_t)
{
    assert(cpt_hash_multimap != NULL);

    return _hashtable_hash_func(&cpt_hash_multimap->_t_hashtable);
}

int (*hash_multimap_key_comp(const hash_multimap_t* cpt_hash_multimap))(
    const void*, const void*)
{
    assert(cpt_hash_multimap != NULL);

    return cpt_hash_multimap->_t_pair._pfun_first_cmp;
}

void hash_multimap_resize(hash_multimap_t* pt_hash_multimap, size_t t_resize)
{
    assert(pt_hash_multimap != NULL);

    _hashtable_resize(&pt_hash_multimap->_t_hashtable, t_resize);
}

hash_multimap_iterator_t hash_multimap_begin(
    const hash_multimap_t* cpt_hash_multimap)
{
    hash_multimap_iterator_t t_newiterator;

    assert(cpt_hash_multimap != NULL);

    t_newiterator = _hashtable_begin(&cpt_hash_multimap->_t_hashtable);

    _GET_CONTAINER(t_newiterator) = (hash_multimap_t*)cpt_hash_multimap;
    _GET_HASH_MULTIMAP_CONTAINER_TYPE(t_newiterator) = _HASH_MULTIMAP_CONTAINER;
    _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_newiterator) = _FORWARD_ITERATOR;

    return t_newiterator;
}

hash_multimap_iterator_t hash_multimap_end(
    const hash_multimap_t* cpt_hash_multimap)
{
    hash_multimap_iterator_t t_newiterator;

    assert(cpt_hash_multimap != NULL);

    t_newiterator = _hashtable_end(&cpt_hash_multimap->_t_hashtable);

    _GET_CONTAINER(t_newiterator) = (hash_multimap_t*)cpt_hash_multimap;
    _GET_HASH_MULTIMAP_CONTAINER_TYPE(t_newiterator) = _HASH_MULTIMAP_CONTAINER;
    _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_newiterator) = _FORWARD_ITERATOR;

    return t_newiterator;
}

bool_t hash_multimap_equal(
    const hash_multimap_t* cpt_hash_multimapfirst, 
    const hash_multimap_t* cpt_hash_multimapsecond)
{
    assert(cpt_hash_multimapfirst != NULL && cpt_hash_multimapsecond != NULL);

    /* test pair */
    if(cpt_hash_multimapfirst->_t_pair._t_firsttypesize != 
        cpt_hash_multimapsecond->_t_pair._t_firsttypesize ||
       cpt_hash_multimapfirst->_t_pair._t_secondtypesize != 
        cpt_hash_multimapsecond->_t_pair._t_secondtypesize)
    {
        return false;
    }
    if(strncmp(
        cpt_hash_multimapfirst->_t_pair._sz_firsttypename,
        cpt_hash_multimapsecond->_t_pair._sz_firsttypename,
        _ELEM_TYPE_NAME_SIZE) != 0 ||
       strncmp(
        cpt_hash_multimapfirst->_t_pair._sz_secondtypename,
        cpt_hash_multimapsecond->_t_pair._sz_secondtypename,
        _ELEM_TYPE_NAME_SIZE) != 0)
    {
        return false;
    }
    if(cpt_hash_multimapfirst->_t_pair._pfun_first_cmp != 
        cpt_hash_multimapsecond->_t_pair._pfun_first_cmp ||
       cpt_hash_multimapfirst->_t_pair._pfun_second_cmp != 
        cpt_hash_multimapsecond->_t_pair._pfun_second_cmp)
    {
        return false;
    }
    /* test hashtable */
    return _hashtable_equal(
        &cpt_hash_multimapfirst->_t_hashtable, &cpt_hash_multimapsecond->_t_hashtable);
}

bool_t hash_multimap_not_equal(
    const hash_multimap_t* cpt_hash_multimapfirst, 
    const hash_multimap_t* cpt_hash_multimapsecond)
{
    return !hash_multimap_equal(cpt_hash_multimapfirst, cpt_hash_multimapsecond);
}

bool_t hash_multimap_less(
    const hash_multimap_t* cpt_hash_multimapfirst, 
    const hash_multimap_t* cpt_hash_multimapsecond)
{
    /* add now relationship operator */
    return true;
}

hash_multimap_iterator_t _hash_multimap_find(
    const hash_multimap_t* cpt_hash_multimap, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, cpt_hash_multimap);
    return _hash_multimap_find_varg(cpt_hash_multimap, val_elemlist);
}

hash_multimap_iterator_t _hash_multimap_find_varg(
    const hash_multimap_t* cpt_hash_multimap, va_list val_elemlist)
{
    hash_multimap_iterator_t t_iterator;

    assert(cpt_hash_multimap != NULL);

    _get_varg_value(
        cpt_hash_multimap->_t_pair.first, val_elemlist, 
        cpt_hash_multimap->_t_pair._t_firsttypesize,
        cpt_hash_multimap->_t_pair._sz_firsttypename);

    t_iterator = _hashtable_find(
        &cpt_hash_multimap->_t_hashtable, &cpt_hash_multimap->_t_pair);

    _GET_CONTAINER(t_iterator) = (hash_multimap_t*)cpt_hash_multimap;
    _GET_HASH_MULTIMAP_CONTAINER_TYPE(t_iterator) = _HASH_MULTIMAP_CONTAINER;
    _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_iterator) = _FORWARD_ITERATOR;

    return t_iterator;
}

size_t _hash_multimap_count(
    const hash_multimap_t* cpt_hash_multimap, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, cpt_hash_multimap);
    return _hash_multimap_count_varg(cpt_hash_multimap, val_elemlist);
}

size_t _hash_multimap_count_varg(
    const hash_multimap_t* cpt_hash_multimap, va_list val_elemlist)
{
    assert(cpt_hash_multimap != NULL);

    _get_varg_value(
        cpt_hash_multimap->_t_pair.first, val_elemlist,
        cpt_hash_multimap->_t_pair._t_firsttypesize,
        cpt_hash_multimap->_t_pair._sz_firsttypename);

    return _hashtable_count(
        &cpt_hash_multimap->_t_hashtable, &cpt_hash_multimap->_t_pair);
}

pair_t _hash_multimap_equal_range(
    const hash_multimap_t* cpt_hash_multimap, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, cpt_hash_multimap);
    return _hash_multimap_equal_range_varg(cpt_hash_multimap, val_elemlist);
}

pair_t _hash_multimap_equal_range_varg(
    const hash_multimap_t* cpt_hash_multimap, va_list val_elemlist)
{
    hash_multimap_iterator_t t_firstiterator;
    hash_multimap_iterator_t t_seconditerator;
    hashtable_result_pair_t  t_result;
    pair_t                   t_pair;

    assert(cpt_hash_multimap != NULL);

    _get_varg_value(
        cpt_hash_multimap->_t_pair.first, val_elemlist, 
        cpt_hash_multimap->_t_pair._t_firsttypesize,
        cpt_hash_multimap->_t_pair._sz_firsttypename);

    t_result = _hashtable_equal_range(
        &cpt_hash_multimap->_t_hashtable, &cpt_hash_multimap->_t_pair);

    t_firstiterator = t_result._t_first;
    _GET_CONTAINER(t_firstiterator) = (hash_multimap_t*)cpt_hash_multimap;
    _GET_HASH_MULTIMAP_CONTAINER_TYPE(t_firstiterator) = _HASH_MULTIMAP_CONTAINER;
    _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_firstiterator) = _FORWARD_ITERATOR;

    t_seconditerator = t_result._t_second._t_iterator;
    _GET_CONTAINER(t_seconditerator) = (hash_multimap_t*)cpt_hash_multimap;
    _GET_HASH_MULTIMAP_CONTAINER_TYPE(t_seconditerator) = _HASH_MULTIMAP_CONTAINER;
    _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_seconditerator) = _FORWARD_ITERATOR;

    t_pair = create_pair(hash_multimap_iterator_t, hash_multimap_iterator_t);
    pair_init(&t_pair);
    memcpy(t_pair.first, &t_firstiterator, t_pair._t_firsttypesize);
    memcpy(t_pair.second, &t_seconditerator, t_pair._t_secondtypesize);

    return t_pair;
}

hash_multimap_iterator_t hash_multimap_insert(
    hash_multimap_t* pt_hash_multimap, const pair_t* cpt_pair)
{
    pair_t                   t_elempair;
    hash_multimap_iterator_t t_result;

    assert(pt_hash_multimap != NULL && cpt_pair != NULL);
    assert(_same_hash_multimap_pair_type(&pt_hash_multimap->_t_pair, cpt_pair));

    /* initialize new elemen pair */
    t_elempair = _create_pair(
        pt_hash_multimap->_t_pair._t_firsttypesize, 
        pt_hash_multimap->_t_pair._sz_firsttypename,
        pt_hash_multimap->_t_pair._t_secondtypesize,
        pt_hash_multimap->_t_pair._sz_secondtypename);
    pair_init(&t_elempair);
    memcpy(t_elempair.first, cpt_pair->first, t_elempair._t_firsttypesize);
    memcpy(t_elempair.second, cpt_pair->second, t_elempair._t_secondtypesize);

    /* insert int hashtable */
    t_result = _hashtable_insert_equal(&pt_hash_multimap->_t_hashtable, &t_elempair);

    /*
     * There is no need for destroy the elempair, because the pair is copied 
     * to the tree, and it is destroied by tree when tree is desroied.
     */
    _GET_CONTAINER(t_result) = pt_hash_multimap;
    _GET_HASH_MULTIMAP_CONTAINER_TYPE(t_result) = _HASH_MULTIMAP_CONTAINER;
    _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_result) = _FORWARD_ITERATOR;

    return t_result;
}

void hash_multimap_insert_range(
    hash_multimap_t* pt_hash_multimap, 
    hash_multimap_iterator_t t_begin, hash_multimap_iterator_t t_end)
{
    hash_multimap_iterator_t t_iterator;

    assert(pt_hash_multimap != NULL);
    assert(_GET_HASH_MULTIMAP_CONTAINER_TYPE(t_begin) == _HASH_MULTIMAP_CONTAINER &&
           _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_begin) == _FORWARD_ITERATOR &&
           _GET_HASH_MULTIMAP_CONTAINER_TYPE(t_end) == _HASH_MULTIMAP_CONTAINER &&
           _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_end) == _FORWARD_ITERATOR);
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
           _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_pos) == _FORWARD_ITERATOR &&
           _GET_HASH_MULTIMAP_CONTAINER(t_pos) == pt_hash_multimap);

    _hashtable_erase_pos(&pt_hash_multimap->_t_hashtable, t_pos);
}

void hash_multimap_erase_range(
    hash_multimap_t* pt_hash_multimap, 
    hash_multimap_iterator_t t_begin, hash_multimap_iterator_t t_end)
{
    assert(pt_hash_multimap != NULL);
    assert(_GET_HASH_MULTIMAP_CONTAINER_TYPE(t_begin) == _HASH_MULTIMAP_CONTAINER &&
           _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_begin) == _FORWARD_ITERATOR &&
           _GET_HASH_MULTIMAP_CONTAINER_TYPE(t_end) == _HASH_MULTIMAP_CONTAINER &&
           _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_end) == _FORWARD_ITERATOR);
    assert(_GET_HASH_MULTIMAP_CONTAINER(t_begin) == pt_hash_multimap &&
           _GET_HASH_MULTIMAP_CONTAINER(t_end) == pt_hash_multimap);

    _hashtable_erase_range(&pt_hash_multimap->_t_hashtable, t_begin, t_end);
}

size_t _hash_multimap_erase(hash_multimap_t* pt_hash_multimap, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, pt_hash_multimap);
    return _hash_multimap_erase_varg(pt_hash_multimap, val_elemlist);
}

size_t _hash_multimap_erase_varg(hash_multimap_t* pt_hash_multimap, va_list val_elemlist)
{
    assert(pt_hash_multimap != NULL);

    _get_varg_value(
        pt_hash_multimap->_t_pair.first, val_elemlist, 
        pt_hash_multimap->_t_pair._t_firsttypesize,
        pt_hash_multimap->_t_pair._sz_firsttypename);

    return _hashtable_erase(
        &pt_hash_multimap->_t_hashtable, &pt_hash_multimap->_t_pair);
}

void hash_multimap_clear(hash_multimap_t* pt_hash_multimap)
{
    assert(pt_hash_multimap != NULL);

    _hashtable_clear(&pt_hash_multimap->_t_hashtable);
}

/** local function implementation section **/
#ifndef NDEBUG
static bool_t _same_hash_multimap_pair_type(
    const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond)
{
    assert(cpt_pairfirst != NULL && cpt_pairsecond != NULL);

    assert(cpt_pairfirst->first != NULL && cpt_pairfirst->second != NULL);
    assert(cpt_pairsecond->first != NULL && cpt_pairsecond->second != NULL);
    assert(cpt_pairfirst->_t_firsttypesize == cpt_pairsecond->_t_firsttypesize && 
           cpt_pairfirst->_t_secondtypesize == cpt_pairsecond->_t_secondtypesize);
    assert(strncmp(cpt_pairfirst->_sz_firsttypename, cpt_pairsecond->_sz_firsttypename,
              _ELEM_TYPE_NAME_SIZE) == 0 &&
           strncmp(cpt_pairfirst->_sz_secondtypename, cpt_pairsecond->_sz_secondtypename,
              _ELEM_TYPE_NAME_SIZE) == 0);

    assert(cpt_pairfirst->_pfun_first_cmp == cpt_pairsecond->_pfun_first_cmp &&
           cpt_pairfirst->_pfun_second_cmp == cpt_pairsecond->_pfun_second_cmp);

    return true;
}
#endif /* NDEBUG */

static int _hash_multimap_cmp(const void* cpv_firstelem, const void* cpv_secondelem)
{
    pair_t* pt_first = NULL;
    pair_t* pt_second = NULL;

    assert(cpv_firstelem != NULL && cpv_secondelem != NULL);

    pt_first = (pair_t*)cpv_firstelem;
    pt_second = (pair_t*)cpv_secondelem;

    assert(_same_hash_multimap_pair_type(pt_first, pt_second));

    if(pt_first->_pfun_first_cmp != NULL)
    {
        return (*pt_first->_pfun_first_cmp)(pt_first->first, pt_second->first);
    }
    else
    {
        return memcmp(pt_first->first, pt_second->first, pt_first->_t_firsttypesize);
    }
}

static void _hash_multimap_destroy_elem(void* pv_value)
{
    assert(pv_value != NULL);

    pair_destroy((pair_t*)pv_value);
}

static int _hash_multimap_hash_function(
    const void* cpv_value, size_t t_nodesize, size_t t_bucketcount)
{
    size_t  t_sum = 0;
    pair_t* pt_pair = NULL;
    char*   pc_value = NULL;
    size_t  t_index = 0;
    size_t  t_avoidwarning = 0;
    t_avoidwarning = t_nodesize;

    assert(cpv_value != NULL && t_bucketcount > 0);

    pt_pair = (pair_t*)cpv_value;

    /* hash for int */
    if(strncmp(
        pt_pair->_sz_firsttypename, _INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        return abs(*(int*)pt_pair->first % t_bucketcount);
    }
    /* hash for unsigned int */
    else if(strncmp(
        pt_pair->_sz_firsttypename, _UNSIGNED_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        return *(unsigned int*)pt_pair->first % t_bucketcount;
    }
    /* hash for short */
    else if(strncmp(
        pt_pair->_sz_firsttypename, _SHORT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        return abs(*(short*)pt_pair->first % t_bucketcount);
    }
    /* hash for unsigned short */
    else if(strncmp(
        pt_pair->_sz_firsttypename, _UNSIGNED_SHORT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        return *(unsigned short*)pt_pair->first % t_bucketcount;
    }
    /* hash for long */
    else if(strncmp(
        pt_pair->_sz_firsttypename, _LONG_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        return abs(*(long*)pt_pair->first % t_bucketcount);
    }
    /* hash for unsigned long */
    else if(strncmp(
        pt_pair->_sz_firsttypename, _UNSIGNED_LONG_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        return *(unsigned long*)pt_pair->first % t_bucketcount;
    }
    /* hash for double */
    else if(strncmp(
        pt_pair->_sz_firsttypename, _DOUBLE_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        return (unsigned long)*(double*)pt_pair->first % t_bucketcount;
    }
    /* hash for float */
    else if(strncmp(
        pt_pair->_sz_firsttypename, _FLOAT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        return (unsigned long)*(float*)pt_pair->first % t_bucketcount;
    }
    else
    {
        pc_value = pt_pair->first;
        for(t_index = 0; t_index < pt_pair->_t_firsttypesize; ++t_index)
        {
            t_sum += (size_t)pc_value[t_index];
        }

        return (int)(t_sum % t_bucketcount);
    }
}

/** eof **/

