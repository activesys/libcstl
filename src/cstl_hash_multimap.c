/*
 *  The implementation of hash_multimap.
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

#include <cstl/cstl_alloc.h>
#include <cstl/cstl_types.h>
#include <cstl/cstl_iterator.h>
#include <cstl/cstl_iterator.h>

#include <cstl/cvector.h>
#include <cstl/cstl_hashtable_iterator.h>
#include <cstl/cstl_hashtable_private.h>
#include <cstl/cutility.h>
#include <cstl/cstring.h>

#include <cstl/cstl_hash_multimap_iterator.h>
#include <cstl/cstl_hash_multimap_private.h>
#include <cstl/cstl_hash_multimap.h>

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
static bool_t _hash_multimap_same_pair_type(
    const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond);
#endif /* NDEBUG */

/*
 * hash_multimap element compare function.
 */
static void _hash_multimap_value_compare(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _hash_multimap_default_hash(const void* cpv_input, void* pv_output);

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/* hash_multimap iterator function */
hash_multimap_iterator_t create_hash_multimap_iterator(void)
{
    hash_multimap_iterator_t t_newiterator = _create_hashtable_iterator();

    _GET_HASH_MULTIMAP_CONTAINER_TYPE(t_newiterator) = _HASH_MULTIMAP_CONTAINER;
    _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

void _hash_multimap_iterator_get_value(
    hash_multimap_iterator_t t_iter, void* pv_value)
{
    assert(pv_value != NULL);
    assert(_GET_HASH_MULTIMAP_CONTAINER_TYPE(t_iter) == _HASH_MULTIMAP_CONTAINER &&
           _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_iter) == _BIDIRECTIONAL_ITERATOR);

    _hashtable_iterator_get_value(t_iter, pv_value);
}

const void* _hash_multimap_iterator_get_pointer(hash_multimap_iterator_t t_iter)
{
    assert(_GET_HASH_MULTIMAP_CONTAINER_TYPE(t_iter) == _HASH_MULTIMAP_CONTAINER &&
           _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_iter) == _BIDIRECTIONAL_ITERATOR);

    return _hashtable_iterator_get_pointer(t_iter);
}

hash_multimap_iterator_t _hash_multimap_iterator_prev(hash_multimap_iterator_t t_iter)
{
    assert(_GET_HASH_MULTIMAP_CONTAINER_TYPE(t_iter) == _HASH_MULTIMAP_CONTAINER &&
           _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_iter) == _BIDIRECTIONAL_ITERATOR);

    return _hashtable_iterator_prev(t_iter);
}

hash_multimap_iterator_t _hash_multimap_iterator_next(hash_multimap_iterator_t t_iter)
{
    assert(_GET_HASH_MULTIMAP_CONTAINER_TYPE(t_iter) == _HASH_MULTIMAP_CONTAINER &&
           _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_iter) == _BIDIRECTIONAL_ITERATOR);

    return _hashtable_iterator_next(t_iter);
}

bool_t _hash_multimap_iterator_equal(
    hash_multimap_iterator_t t_iterfirst, hash_multimap_iterator_t t_itersecond)
{
    assert(_GET_HASH_MULTIMAP_CONTAINER_TYPE(t_iterfirst) == _HASH_MULTIMAP_CONTAINER &&
           _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_iterfirst) == _BIDIRECTIONAL_ITERATOR &&
           _GET_HASH_MULTIMAP_CONTAINER_TYPE(t_itersecond) == _HASH_MULTIMAP_CONTAINER &&
           _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_itersecond) == _BIDIRECTIONAL_ITERATOR);

    return _hashtable_iterator_equal(t_iterfirst, t_itersecond);
}

int _hash_multimap_iterator_distance(
    hash_multimap_iterator_t t_iterfirst, hash_multimap_iterator_t t_itersecond)
{
    assert(_GET_HASH_MULTIMAP_CONTAINER_TYPE(t_iterfirst) == _HASH_MULTIMAP_CONTAINER &&
           _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_iterfirst) == _BIDIRECTIONAL_ITERATOR &&
           _GET_HASH_MULTIMAP_CONTAINER_TYPE(t_itersecond) == _HASH_MULTIMAP_CONTAINER &&
           _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_itersecond) == _BIDIRECTIONAL_ITERATOR &&
           _GET_HASH_MULTIMAP_CONTAINER(t_iterfirst) == 
               _GET_HASH_MULTIMAP_CONTAINER(t_itersecond));

    return _hashtable_iterator_distance(t_iterfirst, t_itersecond);
}

bool_t _hash_multimap_iterator_before(
    hash_multimap_iterator_t t_iterfirst, hash_multimap_iterator_t t_itersecond)
{
    assert(_GET_HASH_MULTIMAP_CONTAINER_TYPE(t_iterfirst) == _HASH_MULTIMAP_CONTAINER &&
           _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_iterfirst) == _BIDIRECTIONAL_ITERATOR &&
           _GET_HASH_MULTIMAP_CONTAINER_TYPE(t_itersecond) == _HASH_MULTIMAP_CONTAINER &&
           _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_itersecond) == _BIDIRECTIONAL_ITERATOR &&
           _GET_HASH_MULTIMAP_CONTAINER(t_iterfirst) == 
               _GET_HASH_MULTIMAP_CONTAINER(t_itersecond));

    return _hashtable_iterator_before(t_iterfirst, t_itersecond);
}

/* hash_multimap private function */
hash_multimap_t* _create_hash_multimap(const char* s_typename)
{
    hash_multimap_t* pt_new_hash_multimap = NULL;

    if((pt_new_hash_multimap = (hash_multimap_t*)malloc(sizeof(hash_multimap_t))) == NULL)
    {
        return NULL;
    }

    if(!_create_hash_multimap_auxiliary(pt_new_hash_multimap, s_typename))
    {
        free(pt_new_hash_multimap);
        return NULL;
    }

    return pt_new_hash_multimap;
}

bool_t _create_hash_multimap_auxiliary(
    hash_multimap_t* pt_hash_multimap, const char* s_typename)
{
    char s_typenameex[_TYPE_NAME_SIZE + 1];

    assert(pt_hash_multimap != NULL && s_typename != NULL);

    if(!_create_pair_auxiliary(&pt_hash_multimap->_t_pair, s_typename))
    {
        return false;
    }

    memset(s_typenameex, '\0', _TYPE_NAME_SIZE + 1);
    strncpy(s_typenameex, "pair_t", _TYPE_NAME_SIZE);
    strncat(s_typenameex, "<", _TYPE_NAME_SIZE);
    strncat(s_typenameex, s_typename, _TYPE_NAME_SIZE - 8); /* 8 is length of "pair_t<>" */
    strncat(s_typenameex, ">", _TYPE_NAME_SIZE);

    pt_hash_multimap->_t_keycompare = NULL;
    pt_hash_multimap->_t_valuecompare = NULL;

    return _create_hashtable_auxiliary(&pt_hash_multimap->_t_hashtable, s_typenameex);
}

void _hash_multimap_destroy_auxiliary(hash_multimap_t* pt_hash_multimap)
{
    assert(pt_hash_multimap != NULL);

    _pair_destroy_auxiliary(&pt_hash_multimap->_t_pair);
    _hashtable_destroy_auxiliary(&pt_hash_multimap->_t_hashtable);

    pt_hash_multimap->_t_keycompare = NULL;
    pt_hash_multimap->_t_valuecompare = NULL;
}

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

    pt_hash_multimap->_t_keycompare = t_compare;
    pt_hash_multimap->_t_pair._t_mapkeycompare = t_compare;
    t_default_hash = t_hash != NULL ? t_hash : _hash_multimap_default_hash;
    /* initialize the pair */
    pair_init(&pt_hash_multimap->_t_pair);
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
    pt_hash_multimapdest->_t_keycompare = cpt_hash_multimapsrc->_t_keycompare;
    pt_hash_multimapdest->_t_valuecompare = cpt_hash_multimapsrc->_t_valuecompare;
    pt_hash_multimapdest->_t_pair._t_mapkeycompare = cpt_hash_multimapsrc->_t_pair._t_mapkeycompare;
    pt_hash_multimapdest->_t_pair._t_mapvaluecompare = cpt_hash_multimapsrc->_t_pair._t_mapvaluecompare;
    assert(_hash_multimap_same_pair_type(
        &pt_hash_multimapdest->_t_pair, &cpt_hash_multimapsrc->_t_pair));

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
    assert(_hash_multimap_same_pair_type(
        &pt_hash_multimapdest->_t_pair, &cpt_hash_multimapsrc->_t_pair));

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
    assert(_hash_multimap_same_pair_type(
        &pt_hash_multimapfirst->_t_pair, &pt_hash_multimapsecond->_t_pair));

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

    if (cpt_hash_multimap->_t_keycompare != NULL)
    {
        return cpt_hash_multimap->_t_keycompare;
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

    _type_get_varg_value(&((hash_multimap_t*)cpt_hash_multimap)->_t_pair._t_typeinfofirst,
        val_elemlist, cpt_hash_multimap->_t_pair._pv_first);

    t_iterator = _hashtable_find(
        &cpt_hash_multimap->_t_hashtable, &cpt_hash_multimap->_t_pair);

    _GET_CONTAINER(t_iterator) = (hash_multimap_t*)cpt_hash_multimap;
    _GET_HASH_MULTIMAP_CONTAINER_TYPE(t_iterator) = _HASH_MULTIMAP_CONTAINER;
    _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_iterator) = _BIDIRECTIONAL_ITERATOR;

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

    _type_get_varg_value(&((hash_multimap_t*)cpt_hash_multimap)->_t_pair._t_typeinfofirst,
        val_elemlist, cpt_hash_multimap->_t_pair._pv_first);

    return _hashtable_count(
        &cpt_hash_multimap->_t_hashtable, &cpt_hash_multimap->_t_pair);
}

range_t _hash_multimap_equal_range(
    const hash_multimap_t* cpt_hash_multimap, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, cpt_hash_multimap);
    return _hash_multimap_equal_range_varg(cpt_hash_multimap, val_elemlist);
}

range_t _hash_multimap_equal_range_varg(
    const hash_multimap_t* cpt_hash_multimap, va_list val_elemlist)
{
    range_t  t_result;

    assert(cpt_hash_multimap != NULL);

    _type_get_varg_value(&((hash_multimap_t*)cpt_hash_multimap)->_t_pair._t_typeinfofirst,
        val_elemlist, cpt_hash_multimap->_t_pair._pv_first);

    t_result = _hashtable_equal_range(
        &cpt_hash_multimap->_t_hashtable, &cpt_hash_multimap->_t_pair);

    _GET_CONTAINER(t_result.it_begin) = (hash_multimap_t*)cpt_hash_multimap;
    _GET_HASH_MULTIMAP_CONTAINER_TYPE(t_result.it_begin) = _HASH_MULTIMAP_CONTAINER;
    _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_result.it_begin) = _BIDIRECTIONAL_ITERATOR;

    _GET_CONTAINER(t_result.it_end) = (hash_multimap_t*)cpt_hash_multimap;
    _GET_HASH_MULTIMAP_CONTAINER_TYPE(t_result.it_end) = _HASH_MULTIMAP_CONTAINER;
    _GET_HASH_MULTIMAP_ITERATOR_TYPE(t_result.it_end) = _BIDIRECTIONAL_ITERATOR;

    return t_result;
}

hash_multimap_iterator_t hash_multimap_insert(
    hash_multimap_t* pt_hash_multimap, const pair_t* cpt_pair)
{
    hash_multimap_iterator_t t_result;

    assert(pt_hash_multimap != NULL && cpt_pair != NULL);
    ((pair_t*)cpt_pair)->_t_mapkeycompare = pt_hash_multimap->_t_keycompare;
    ((pair_t*)cpt_pair)->_t_mapvaluecompare = pt_hash_multimap->_t_valuecompare;
    assert(_hash_multimap_same_pair_type(&pt_hash_multimap->_t_pair, cpt_pair));

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

size_t _hash_multimap_erase(hash_multimap_t* pt_hash_multimap, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, pt_hash_multimap);
    return _hash_multimap_erase_varg(pt_hash_multimap, val_elemlist);
}

size_t _hash_multimap_erase_varg(hash_multimap_t* pt_hash_multimap, va_list val_elemlist)
{
    assert(pt_hash_multimap != NULL);

    _type_get_varg_value(&pt_hash_multimap->_t_pair._t_typeinfofirst,
        val_elemlist, pt_hash_multimap->_t_pair._pv_first);

    return _hashtable_erase(
        &pt_hash_multimap->_t_hashtable, &pt_hash_multimap->_t_pair);
}

void hash_multimap_clear(hash_multimap_t* pt_hash_multimap)
{
    assert(pt_hash_multimap != NULL);

    _hashtable_clear(&pt_hash_multimap->_t_hashtable);
}

void _hash_multimap_init_elem_auxiliary(hash_multimap_t* pt_hash_multimap, void* pv_elem)
{
    assert(pt_hash_multimap != NULL && pv_elem != NULL);

    /* initialize new elements */
    if(pt_hash_multimap->_t_hashtable._t_typeinfo._t_style == _TYPE_CSTL_BUILTIN)
    {
        /* get element type name */
        char s_elemtypename[_TYPE_NAME_SIZE + 1];
        _type_get_elem_typename(
            pt_hash_multimap->_t_hashtable._t_typeinfo._sz_typename, s_elemtypename);

        pt_hash_multimap->_t_hashtable._t_typeinfo._pt_type->_t_typeinit(
            pv_elem, s_elemtypename);
    }
    else
    {
        bool_t t_result = pt_hash_multimap->_t_hashtable._t_typeinfo._pt_type->_t_typesize;
        pt_hash_multimap->_t_hashtable._t_typeinfo._pt_type->_t_typeinit(pv_elem, &t_result);
        assert(t_result);
    }
}

/** local function implementation section **/
#ifndef NDEBUG
static bool_t _hash_multimap_same_pair_type(
    const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond)
{
    assert(cpt_pairfirst != NULL && cpt_pairsecond != NULL);

    return _type_is_same(cpt_pairfirst->_t_typeinfofirst._sz_typename,
                         cpt_pairsecond->_t_typeinfofirst._sz_typename) &&
           (cpt_pairfirst->_t_typeinfofirst._pt_type ==
            cpt_pairsecond->_t_typeinfofirst._pt_type) &&
           (cpt_pairfirst->_t_typeinfofirst._t_style ==
            cpt_pairsecond->_t_typeinfofirst._t_style) &&
           _type_is_same(cpt_pairfirst->_t_typeinfosecond._sz_typename,
                         cpt_pairsecond->_t_typeinfosecond._sz_typename) &&
           (cpt_pairfirst->_t_typeinfosecond._pt_type ==
            cpt_pairsecond->_t_typeinfosecond._pt_type) &&
           (cpt_pairfirst->_t_typeinfosecond._t_style ==
            cpt_pairsecond->_t_typeinfosecond._t_style) &&
           (cpt_pairfirst->_t_mapkeycompare == cpt_pairsecond->_t_mapkeycompare) &&
           (cpt_pairfirst->_t_mapvaluecompare == cpt_pairsecond->_t_mapvaluecompare);
}
#endif /* NDEBUG */

static void _hash_multimap_value_compare(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    pair_t* pt_first = NULL;
    pair_t* pt_second = NULL;

    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    pt_first = (pair_t*)cpv_first;
    pt_second = (pair_t*)cpv_second;

    assert(_hash_multimap_same_pair_type(pt_first, pt_second));

    *(bool_t*)pv_output = pt_first->_t_typeinfofirst._pt_type->_t_typesize;
    if (pt_first->_t_mapkeycompare != NULL) /* external key less */
    {
        pt_first->_t_mapkeycompare(pair_first(pt_first), pair_first(pt_second), pv_output);
    }
    else
    {
        pt_first->_t_typeinfofirst._pt_type->_t_typeless(
            pt_first->_pv_first, pt_second->_pv_first, pv_output);
    }
}

static void _hash_multimap_default_hash(const void* cpv_input, void* pv_output)
{
    pair_t* pt_pair = NULL;
    char*   pc_value = NULL;
    size_t  t_sum = 0;
    size_t  t_index = 0;
    size_t  t_len = 0;

    assert(cpv_input != NULL && pv_output != NULL);

    pt_pair = (pair_t*)cpv_input;
    pc_value = (char*)pair_first(pt_pair);
    if(strncmp(pt_pair->_t_typeinfofirst._pt_type->_sz_typename, _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        t_len = strlen(pc_value);
    }
    else
    {
        t_len = pt_pair->_t_typeinfofirst._pt_type->_t_typesize;
    }

    for(t_index = 0; t_index < t_len; ++t_index)
    {
        t_sum += (size_t)pc_value[t_index];
    }

    *(size_t*)pv_output = t_sum;
}

/** eof **/

