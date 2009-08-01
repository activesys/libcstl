/*
 *  The implementation of multimap.
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

#ifdef CSTL_MULTIMAP_AVL_TREE
#include "cstl_avl_tree_iterator.h"
#include "cstl_avl_tree_private.h"
#else
#include "cstl_rb_tree_iterator.h"
#include "cstl_rb_tree_private.h"
#endif
#include "cutility.h"
#include "cstring.h"

#include "cstl_multimap_iterator.h"
#include "cstl_multimap_private.h"
#include "cstl_multimap.h"

/** local constant declaration and local macro section **/
/* macros for type informations */
#define _GET_MULTIMAP_FIRST_TYPE_SIZE(pt_multimap)\
    ((pt_multimap)->_t_pair._t_typeinfofirst._pt_type->_t_typesize)
#define _GET_MULTIMAP_FIRST_TYPE_NAME(pt_multimap)\
    ((pt_multimap)->_t_pair._t_typeinfofirst._sz_typename)
#define _GET_MULTIMAP_FIRST_TYPE_BASENAME(pt_multimap)\
    ((pt_multimap)->_t_pair._t_typeinfofirst._pt_type->_sz_typename)
#define _GET_MULTIMAP_FIRST_TYPE_INIT_FUNCTION(pt_multimap)\
    ((pt_multimap)->_t_pair._t_typeinfofirst._pt_type->_t_typeinit)
#define _GET_MULTIMAP_FIRST_TYPE_COPY_FUNCTION(pt_multimap)\
    ((pt_multimap)->_t_pair._t_typeinfofirst._pt_type->_t_typecopy)
#define _GET_MULTIMAP_FIRST_TYPE_LESS_FUNCTION(pt_multimap)\
    ((pt_multimap)->_t_pair._t_typeinfofirst._pt_type->_t_typeless)
#define _GET_MULTIMAP_FIRST_TYPE_DESTROY_FUNCTION(pt_multimap)\
    ((pt_multimap)->_t_pair._t_typeinfofirst._pt_type->_t_typedestroy)
#define _GET_MULTIMAP_FIRST_TYPE_STYLE(pt_multimap)\
    ((pt_multimap)->_t_pair._t_typeinfofirst._t_style)

#define _GET_MULTIMAP_SECOND_TYPE_SIZE(pt_multimap)\
    ((pt_multimap)->_t_pair._t_typeinfosecond._pt_type->_t_typesize)
#define _GET_MULTIMAP_SECOND_TYPE_NAME(pt_multimap)\
    ((pt_multimap)->_t_pair._t_typeinfosecond._sz_typename)
#define _GET_MULTIMAP_SECOND_TYPE_BASENAME(pt_multimap)\
    ((pt_multimap)->_t_pair._t_typeinfosecond._pt_type->_sz_typename)
#define _GET_MULTIMAP_SECOND_TYPE_INIT_FUNCTION(pt_multimap)\
    ((pt_multimap)->_t_pair._t_typeinfosecond._pt_type->_t_typeinit)
#define _GET_MULTIMAP_SECOND_TYPE_COPY_FUNCTION(pt_multimap)\
    ((pt_multimap)->_t_pair._t_typeinfosecond._pt_type->_t_typecopy)
#define _GET_MULTIMAP_SECOND_TYPE_LESS_FUNCTION(pt_multimap)\
    ((pt_multimap)->_t_pair._t_typeinfosecond._pt_type->_t_typeless)
#define _GET_MULTIMAP_SECOND_TYPE_DESTROY_FUNCTION(pt_multimap)\
    ((pt_multimap)->_t_pair._t_typeinfosecond._pt_type->_t_typedestroy)
#define _GET_MULTIMAP_SECOND_TYPE_STYLE(pt_multimap)\
    ((pt_multimap)->_t_pair._t_typeinfosecond._t_style)

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/
#ifndef NDEBUG
/*
 * Assert support.
 */
static bool_t _multimap_same_pair_type(
    const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond);
#endif /* NDEBUG */

/* default element less function for multimap_t */
static void _multimap_key_less(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _multimap_value_less(
    const void* cpv_first, const void* cpv_second, void* pv_output);

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/* multimap iterator function */
multimap_iterator_t create_multimap_iterator(void)
{
    multimap_iterator_t t_newiterator;

#ifdef CSTL_MULTIMAP_AVL_TREE
    t_newiterator = _create_avl_tree_iterator();
#else
    t_newiterator = _create_rb_tree_iterator();
#endif

    _GET_MULTIMAP_CONTAINER_TYPE(t_newiterator) = _MULTIMAP_CONTAINER;
    _GET_MULTIMAP_ITERATOR_TYPE(t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

void _multimap_iterator_get_value(multimap_iterator_t t_iter, void* pv_value)
{
    assert(pv_value != NULL);
    assert(_GET_MULTIMAP_CONTAINER_TYPE(t_iter) == _MULTIMAP_CONTAINER &&
           _GET_MULTIMAP_ITERATOR_TYPE(t_iter) == _BIDIRECTIONAL_ITERATOR);

#ifdef CSTL_MULTIMAP_AVL_TREE
    _avl_tree_iterator_get_value(t_iter, pv_value);
#else
    _rb_tree_iterator_get_value(t_iter, pv_value);
#endif
}

const void* _multimap_iterator_get_pointer(multimap_iterator_t t_iter)
{
    assert(_GET_MULTIMAP_CONTAINER_TYPE(t_iter) == _MULTIMAP_CONTAINER &&
           _GET_MULTIMAP_ITERATOR_TYPE(t_iter) == _BIDIRECTIONAL_ITERATOR);

#ifdef CSTL_MULTIMAP_AVL_TREE
    return _avl_tree_iterator_get_pointer(t_iter);
#else
    return _rb_tree_iterator_get_pointer(t_iter);
#endif
}

multimap_iterator_t _multimap_iterator_next(multimap_iterator_t t_iter)
{
    assert(_GET_MULTIMAP_CONTAINER_TYPE(t_iter) == _MULTIMAP_CONTAINER &&
           _GET_MULTIMAP_ITERATOR_TYPE(t_iter) == _BIDIRECTIONAL_ITERATOR);

#ifdef CSTL_MULTIMAP_AVL_TREE
    return _avl_tree_iterator_next(t_iter);
#else
    return _rb_tree_iterator_next(t_iter);
#endif
}

multimap_iterator_t _multimap_iterator_prev(multimap_iterator_t t_iter)
{
    assert(_GET_MULTIMAP_CONTAINER_TYPE(t_iter) == _MULTIMAP_CONTAINER &&
           _GET_MULTIMAP_ITERATOR_TYPE(t_iter) == _BIDIRECTIONAL_ITERATOR);

#ifdef CSTL_MULTIMAP_AVL_TREE
    return _avl_tree_iterator_prev(t_iter);
#else
    return _rb_tree_iterator_prev(t_iter);
#endif
}

bool_t _multimap_iterator_equal(
    multimap_iterator_t t_iterfirst, multimap_iterator_t t_itersecond)
{
    assert(_GET_MULTIMAP_CONTAINER_TYPE(t_iterfirst) == _MULTIMAP_CONTAINER &&
           _GET_MULTIMAP_ITERATOR_TYPE(t_iterfirst) == _BIDIRECTIONAL_ITERATOR &&
           _GET_MULTIMAP_CONTAINER_TYPE(t_itersecond) == _MULTIMAP_CONTAINER &&
           _GET_MULTIMAP_ITERATOR_TYPE(t_itersecond) == _BIDIRECTIONAL_ITERATOR);

#ifdef CSTL_MULTIMAP_AVL_TREE
    return _avl_tree_iterator_equal(t_iterfirst, t_itersecond);
#else
    return _rb_tree_iterator_equal(t_iterfirst, t_itersecond);
#endif
}

int _multimap_iterator_distance(
    multimap_iterator_t t_iterfirst, multimap_iterator_t t_itersecond)
{
    assert(_GET_MULTIMAP_CONTAINER_TYPE(t_iterfirst) == _MULTIMAP_CONTAINER &&
           _GET_MULTIMAP_ITERATOR_TYPE(t_iterfirst) == _BIDIRECTIONAL_ITERATOR &&
           _GET_MULTIMAP_CONTAINER_TYPE(t_itersecond) == _MULTIMAP_CONTAINER &&
           _GET_MULTIMAP_ITERATOR_TYPE(t_itersecond) == _BIDIRECTIONAL_ITERATOR &&
           _GET_MULTIMAP_CONTAINER(t_iterfirst) == _GET_MULTIMAP_CONTAINER(t_itersecond));

#ifdef CSTL_MULTIMAP_AVL_TREE
    return _avl_tree_iterator_distance(t_iterfirst, t_itersecond);
#else
    return _rb_tree_iterator_distance(t_iterfirst, t_itersecond);
#endif
}

bool_t _multimap_iterator_before(
    multimap_iterator_t t_iterfirst, multimap_iterator_t t_itersecond)
{
    assert(_GET_MULTIMAP_CONTAINER_TYPE(t_iterfirst) == _MULTIMAP_CONTAINER &&
           _GET_MULTIMAP_ITERATOR_TYPE(t_iterfirst) == _BIDIRECTIONAL_ITERATOR &&
           _GET_MULTIMAP_CONTAINER_TYPE(t_itersecond) == _MULTIMAP_CONTAINER &&
           _GET_MULTIMAP_ITERATOR_TYPE(t_itersecond) == _BIDIRECTIONAL_ITERATOR &&
           _GET_MULTIMAP_CONTAINER(t_iterfirst) == _GET_MULTIMAP_CONTAINER(t_itersecond));

#ifdef CSTL_MULTIMAP_AVL_TREE
    return _avl_tree_iterator_before(t_iterfirst, t_itersecond);
#else
    return _rb_tree_iterator_before(t_iterfirst, t_itersecond);
#endif
}

/* multimap private function */
multimap_t* _create_multimap(const char* s_typename)
{
    multimap_t* pt_newmultimap = NULL;

    if((pt_newmultimap = (multimap_t*)malloc(sizeof(multimap_t))) == NULL)
    {
        return NULL;
    }

    if(!_create_multimap_auxiliary(pt_newmultimap, s_typename))
    {
        free(pt_newmultimap);
        return NULL;
    }

    return pt_newmultimap;
}

bool_t _create_multimap_auxiliary(multimap_t* pt_multimap, const char* s_typename)
{
    char   s_typenameex[_TYPE_NAME_SIZE + 1];
    bool_t t_result = false;

    assert(pt_multimap != NULL && s_typename != NULL);

    t_result = _create_pair_auxiliary(&pt_multimap->_t_pair, s_typename);
    if(!t_result)
    {
        return false;
    }

    memset(s_typenameex, '\0', _TYPE_NAME_SIZE + 1);
    strncpy(s_typenameex, "pair_t", _TYPE_NAME_SIZE);
    strncat(s_typenameex, "<", _TYPE_NAME_SIZE);
    strncat(s_typenameex, s_typename, _TYPE_NAME_SIZE - 8); /* 8 is length of "pair_t<>" */
    strncat(s_typenameex, ">", _TYPE_NAME_SIZE);

#ifdef CSTL_MULTIMAP_AVL_TREE
    t_result = _create_avl_tree_auxiliary(&pt_multimap->_t_tree, s_typenameex);
#else
    t_result = _create_rb_tree_auxiliary(&pt_multimap->_t_tree, s_typenameex);
#endif

    return t_result;
}

/* multimap function */
void multimap_init(multimap_t* pt_multimap)
{
    assert(pt_multimap != NULL);

    /* initialize the pair */
    pair_init(&pt_multimap->_t_pair);
    /* initialize the tree */
#ifdef CSTL_MULTIMAP_AVL_TREE
    _avl_tree_init(&pt_multimap->_t_tree, _multimap_key_less);
#else
    _rb_tree_init(&pt_multimap->_t_tree, _multimap_key_less);
#endif
}

void multimap_init_ex(multimap_t* pt_multimap, binary_function_t t_key_less)
{
    binary_function_t t_less = NULL;

    assert(pt_multimap != NULL);

    t_less = t_key_less != NULL ? t_key_less : _multimap_key_less;

    pair_init(&pt_multimap->_t_pair);
#ifdef CSTL_MULTIMAP_AVL_TREE
    _avl_tree_init(&pt_multimap->_t_tree, t_less);
#else
    _rb_tree_init(&pt_multimap->_t_tree, t_less);
#endif
}

void _multimap_destroy_auxiliary(multimap_t* pt_multimap)
{
    assert(pt_multimap != NULL);

    _pair_destroy_auxiliary(&pt_multimap->_t_pair);
#ifdef CSTL_MULTIMAP_AVL_TREE
    _avl_tree_destroy_auxiliary(&pt_multimap->_t_tree);
#else
    _rb_tree_destroy_auxiliary(&pt_multimap->_t_tree);
#endif
}

void multimap_destroy(multimap_t* pt_multimap)
{
    _multimap_destroy_auxiliary(pt_multimap);
    free(pt_multimap);
}

void multimap_init_copy(multimap_t* pt_multimapdest, const multimap_t* cpt_multimapsrc)
{
    assert(pt_multimapdest != NULL && cpt_multimapsrc != NULL);
    assert(_multimap_same_pair_type(&pt_multimapdest->_t_pair, &cpt_multimapsrc->_t_pair));

    /* initialize dest multimap with src multimap attribute */
    multimap_init(pt_multimapdest);
    /* insert all element from src to dest */
    if(!multimap_empty(cpt_multimapsrc))
    {
        multimap_insert_range(pt_multimapdest, 
            multimap_begin(cpt_multimapsrc), multimap_end(cpt_multimapsrc));
    }
}

void multimap_init_copy_range(
    multimap_t* pt_multimapdest, multimap_iterator_t t_begin, multimap_iterator_t t_end)
{
    assert(pt_multimapdest != NULL);
    assert(_GET_MULTIMAP_CONTAINER_TYPE(t_begin) == _MULTIMAP_CONTAINER &&
           _GET_MULTIMAP_ITERATOR_TYPE(t_begin) == _BIDIRECTIONAL_ITERATOR &&
           _GET_MULTIMAP_CONTAINER_TYPE(t_end) == _MULTIMAP_CONTAINER &&
           _GET_MULTIMAP_ITERATOR_TYPE(t_end) == _BIDIRECTIONAL_ITERATOR);
    assert(_GET_MULTIMAP_CONTAINER(t_begin) != pt_multimapdest &&
           _GET_MULTIMAP_CONTAINER(t_end) != pt_multimapdest &&
           _GET_MULTIMAP_CONTAINER(t_begin) == _GET_MULTIMAP_CONTAINER(t_end));

    /* initialize dest multimap with src multimap attribute */
    multimap_init(pt_multimapdest);
    /* insert all element from src to dest */
    if(!multimap_empty(_GET_MULTIMAP_CONTAINER(t_begin)))
    {
        multimap_insert_range(pt_multimapdest, t_begin, t_end);
    }
}

void multimap_init_copy_range_ex(multimap_t* pt_multimapdest,
    multimap_iterator_t t_begin, multimap_iterator_t t_end, binary_function_t t_less)
{
    assert(pt_multimapdest != NULL);
    assert(_GET_MULTIMAP_CONTAINER_TYPE(t_begin) == _MULTIMAP_CONTAINER &&
           _GET_MULTIMAP_ITERATOR_TYPE(t_begin) == _BIDIRECTIONAL_ITERATOR &&
           _GET_MULTIMAP_CONTAINER_TYPE(t_end) == _MULTIMAP_CONTAINER &&
           _GET_MULTIMAP_ITERATOR_TYPE(t_end) == _BIDIRECTIONAL_ITERATOR);
    assert(_GET_MULTIMAP_CONTAINER(t_begin) != pt_multimapdest &&
           _GET_MULTIMAP_CONTAINER(t_end) != pt_multimapdest &&
           _GET_MULTIMAP_CONTAINER(t_begin) == _GET_MULTIMAP_CONTAINER(t_end));

    /* initialize dest multimap with src multimap attribute */
    multimap_init_ex(pt_multimapdest, t_less);
    /* insert all element from src to dest */
    if(!multimap_empty(_GET_MULTIMAP_CONTAINER(t_begin)))
    {
        multimap_insert_range(pt_multimapdest, t_begin, t_end);
    }
}

void multimap_assign(multimap_t* pt_multimapdest, const multimap_t* cpt_multimapsrc)
{
    assert(pt_multimapdest != NULL && cpt_multimapsrc != NULL);
    assert(_multimap_same_pair_type(&pt_multimapdest->_t_pair, &cpt_multimapsrc->_t_pair));

    multimap_clear(pt_multimapdest);
    /* insert all element from src to dest */
    if(!multimap_empty(cpt_multimapsrc))
    {
        multimap_insert_range(pt_multimapdest,
            multimap_begin(cpt_multimapsrc), multimap_end(cpt_multimapsrc));
    }
}

void multimap_swap(multimap_t* pt_multimapfirst, multimap_t* pt_multimapsecond)
{
    assert(pt_multimapfirst != NULL && pt_multimapsecond != NULL);
    assert(_multimap_same_pair_type(&pt_multimapfirst->_t_pair, &pt_multimapsecond->_t_pair));

#ifdef CSTL_MULTIMAP_AVL_TREE
    _avl_tree_swap(&pt_multimapfirst->_t_tree, &pt_multimapsecond->_t_tree);
#else
    _rb_tree_swap(&pt_multimapfirst->_t_tree, &pt_multimapsecond->_t_tree);
#endif
}

bool_t multimap_empty(const multimap_t* cpt_multimap)
{
    assert(cpt_multimap != NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    return _avl_tree_empty(&cpt_multimap->_t_tree);
#else
    return _rb_tree_empty(&cpt_multimap->_t_tree);
#endif
}

size_t multimap_size(const multimap_t* cpt_multimap)
{
    assert(cpt_multimap != NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    return _avl_tree_size(&cpt_multimap->_t_tree);
#else
    return _rb_tree_size(&cpt_multimap->_t_tree);
#endif
}

size_t multimap_max_size(const multimap_t* cpt_multimap)
{
    assert(cpt_multimap != NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    return _avl_tree_max_size(&cpt_multimap->_t_tree);
#else
    return _rb_tree_max_size(&cpt_multimap->_t_tree);
#endif
}

binary_function_t multimap_key_less(const multimap_t* cpt_multimap)
{
    assert(cpt_multimap != NULL);

    return cpt_multimap->_t_tree._t_less;
}

binary_function_t multimap_value_comp(const multimap_t* cpt_multimap)
{
#ifdef NDEBUG
    multimap_t* pt_avoidwarning = NULL;
    pt_avoidwarning = (multimap_t*)cpt_multimap;
#endif
    assert(cpt_multimap != NULL);

    return _multimap_value_less;
}

void multimap_clear(multimap_t* pt_multimap)
{
    assert(pt_multimap != NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    _avl_tree_clear(&pt_multimap->_t_tree);
#else
    _rb_tree_clear(&pt_multimap->_t_tree);
#endif
}

bool_t multimap_equal(
    const multimap_t* cpt_multimapfirst, const multimap_t* cpt_multimapsecond)
{
    assert(cpt_multimapfirst != NULL && cpt_multimapsecond != NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    return _avl_tree_equal(&cpt_multimapfirst->_t_tree, &cpt_multimapsecond->_t_tree);
#else
    return _rb_tree_equal(&cpt_multimapfirst->_t_tree, &cpt_multimapsecond->_t_tree);
#endif
}

bool_t multimap_not_equal(
    const multimap_t* cpt_multimapfirst, const multimap_t* cpt_multimapsecond)
{
    assert(cpt_multimapfirst != NULL && cpt_multimapsecond != NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    return _avl_tree_not_equal(&cpt_multimapfirst->_t_tree, &cpt_multimapsecond->_t_tree);
#else
    return _rb_tree_not_equal(&cpt_multimapfirst->_t_tree, &cpt_multimapsecond->_t_tree);
#endif
}

bool_t multimap_less(
    const multimap_t* cpt_multimapfirst, const multimap_t* cpt_multimapsecond)
{
    assert(cpt_multimapfirst != NULL && cpt_multimapsecond != NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    return _avl_tree_less(&cpt_multimapfirst->_t_tree, &cpt_multimapsecond->_t_tree);
#else
    return _rb_tree_less(&cpt_multimapfirst->_t_tree, &cpt_multimapsecond->_t_tree);
#endif
}

bool_t multimap_less_equal(
    const multimap_t* cpt_multimapfirst, const multimap_t* cpt_multimapsecond)
{
    assert(cpt_multimapfirst != NULL && cpt_multimapsecond != NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    return _avl_tree_less_equal(&cpt_multimapfirst->_t_tree, &cpt_multimapsecond->_t_tree);
#else
    return _rb_tree_less_equal(&cpt_multimapfirst->_t_tree, &cpt_multimapsecond->_t_tree);
#endif
}

bool_t multimap_great(
    const multimap_t* cpt_multimapfirst, const multimap_t* cpt_multimapsecond)
{
    assert(cpt_multimapfirst != NULL && cpt_multimapsecond != NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    return _avl_tree_great(&cpt_multimapfirst->_t_tree, &cpt_multimapsecond->_t_tree);
#else
    return _rb_tree_great(&cpt_multimapfirst->_t_tree, &cpt_multimapsecond->_t_tree);
#endif
}

bool_t multimap_great_equal(
    const multimap_t* cpt_multimapfirst, const multimap_t* cpt_multimapsecond)
{
    assert(cpt_multimapfirst != NULL && cpt_multimapsecond != NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    return _avl_tree_great_equal(&cpt_multimapfirst->_t_tree, &cpt_multimapsecond->_t_tree);
#else
    return _rb_tree_great_equal(&cpt_multimapfirst->_t_tree, &cpt_multimapsecond->_t_tree);
#endif
}

multimap_iterator_t multimap_begin(const multimap_t* cpt_multimap)
{
    multimap_iterator_t t_newiterator;

    assert(cpt_multimap != NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    t_newiterator = _avl_tree_begin(&cpt_multimap->_t_tree);
#else
    t_newiterator = _rb_tree_begin(&cpt_multimap->_t_tree);
#endif

    _GET_CONTAINER(t_newiterator) = (multimap_t*)cpt_multimap;
    _GET_MULTIMAP_CONTAINER_TYPE(t_newiterator) = _MULTIMAP_CONTAINER;
    _GET_MULTIMAP_ITERATOR_TYPE(t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

multimap_iterator_t multimap_end(const multimap_t* cpt_multimap)
{
    multimap_iterator_t t_newiterator;

    assert(cpt_multimap != NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    t_newiterator = _avl_tree_end(&cpt_multimap->_t_tree);
#else
    t_newiterator = _rb_tree_end(&cpt_multimap->_t_tree);
#endif

    _GET_CONTAINER(t_newiterator) = (multimap_t*)cpt_multimap;
    _GET_MULTIMAP_CONTAINER_TYPE(t_newiterator) = _MULTIMAP_CONTAINER;
    _GET_MULTIMAP_ITERATOR_TYPE(t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

multimap_reverse_iterator_t multimap_rbegin(const multimap_t* cpt_multimap)
{
    multimap_reverse_iterator_t t_newiterator;

    assert(cpt_multimap != NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    t_newiterator = _avl_tree_rbegin(&cpt_multimap->_t_tree);
#else
    t_newiterator = _rb_tree_rbegin(&cpt_multimap->_t_tree);
#endif

    _GET_CONTAINER(t_newiterator) = (multimap_t*)cpt_multimap;
    _GET_MULTIMAP_CONTAINER_TYPE(t_newiterator) = _MULTIMAP_CONTAINER;
    _GET_MULTIMAP_ITERATOR_TYPE(t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

multimap_reverse_iterator_t multimap_rend(const multimap_t* cpt_multimap)
{
    multimap_reverse_iterator_t t_newiterator;

    assert(cpt_multimap != NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    t_newiterator = _avl_tree_rend(&cpt_multimap->_t_tree);
#else
    t_newiterator = _rb_tree_rend(&cpt_multimap->_t_tree);
#endif

    _GET_CONTAINER(t_newiterator) = (multimap_t*)cpt_multimap;
    _GET_MULTIMAP_CONTAINER_TYPE(t_newiterator) = _MULTIMAP_CONTAINER;
    _GET_MULTIMAP_ITERATOR_TYPE(t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

multimap_iterator_t _multimap_find(const multimap_t* cpt_multimap, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, cpt_multimap);
    return _multimap_find_varg(cpt_multimap, val_elemlist);
}

multimap_iterator_t _multimap_find_varg(
    const multimap_t* cpt_multimap, va_list val_elemlist)
{
    multimap_iterator_t t_iterator;

    assert(cpt_multimap != NULL);

    /* get key */
    _type_get_varg_value(&((multimap_t*)cpt_multimap)->_t_pair._t_typeinfofirst,
        val_elemlist, cpt_multimap->_t_pair.first);
    /* find key in tree */
#ifdef CSTL_MULTIMAP_AVL_TREE
    t_iterator = _avl_tree_find(&cpt_multimap->_t_tree, &cpt_multimap->_t_pair);
#else
    t_iterator = _rb_tree_find(&cpt_multimap->_t_tree, &cpt_multimap->_t_pair);
#endif

    _GET_CONTAINER(t_iterator) = (multimap_t*)cpt_multimap;
    _GET_MULTIMAP_CONTAINER_TYPE(t_iterator) = _MULTIMAP_CONTAINER;
    _GET_MULTIMAP_ITERATOR_TYPE(t_iterator) = _BIDIRECTIONAL_ITERATOR;

    return t_iterator;
}

size_t _multimap_count(const multimap_t* cpt_multimap, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, cpt_multimap);
    return _multimap_count_varg(cpt_multimap, val_elemlist);
}

size_t _multimap_count_varg(const multimap_t* cpt_multimap, va_list val_elemlist)
{
    assert(cpt_multimap != NULL);

    _type_get_varg_value(&((multimap_t*)cpt_multimap)->_t_pair._t_typeinfofirst,
        val_elemlist, cpt_multimap->_t_pair.first);
#ifdef CSTL_MULTIMAP_AVL_TREE
    return _avl_tree_count(&cpt_multimap->_t_tree, &cpt_multimap->_t_pair);
#else
    return _rb_tree_count(&cpt_multimap->_t_tree, &cpt_multimap->_t_pair);
#endif
}

multimap_iterator_t _multimap_lower_bound(const multimap_t* cpt_multimap, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, cpt_multimap);
    return _multimap_lower_bound_varg(cpt_multimap, val_elemlist);
}

multimap_iterator_t _multimap_lower_bound_varg(
    const multimap_t* cpt_multimap, va_list val_elemlist)
{
    multimap_iterator_t t_iterator;

    assert(cpt_multimap != NULL);

    _type_get_varg_value(&((multimap_t*)cpt_multimap)->_t_pair._t_typeinfofirst,
        val_elemlist, cpt_multimap->_t_pair.first);
#ifdef CSTL_MULTIMAP_AVL_TREE
    t_iterator = _avl_tree_lower_bound(&cpt_multimap->_t_tree, &cpt_multimap->_t_pair);
#else
    t_iterator = _rb_tree_lower_bound(&cpt_multimap->_t_tree, &cpt_multimap->_t_pair);
#endif

    _GET_CONTAINER(t_iterator) = (multimap_t*)cpt_multimap;
    _GET_MULTIMAP_CONTAINER_TYPE(t_iterator) = _MULTIMAP_CONTAINER;
    _GET_MULTIMAP_ITERATOR_TYPE(t_iterator) = _BIDIRECTIONAL_ITERATOR;

    return t_iterator;
}

multimap_iterator_t _multimap_upper_bound(const multimap_t* cpt_multimap, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, cpt_multimap);
    return _multimap_upper_bound_varg(cpt_multimap, val_elemlist);
}

multimap_iterator_t _multimap_upper_bound_varg(
    const multimap_t* cpt_multimap, va_list val_elemlist)
{
    multimap_iterator_t t_iterator;

    assert(cpt_multimap != NULL);

    _type_get_varg_value(&((multimap_t*)cpt_multimap)->_t_pair._t_typeinfofirst,
        val_elemlist, cpt_multimap->_t_pair.first);
#ifdef CSTL_MULTIMAP_AVL_TREE
    t_iterator = _avl_tree_upper_bound(&cpt_multimap->_t_tree, &cpt_multimap->_t_pair);
#else
    t_iterator = _rb_tree_upper_bound(&cpt_multimap->_t_tree, &cpt_multimap->_t_pair);
#endif

    _GET_CONTAINER(t_iterator) = (multimap_t*)cpt_multimap;
    _GET_MULTIMAP_CONTAINER_TYPE(t_iterator) = _MULTIMAP_CONTAINER;
    _GET_MULTIMAP_ITERATOR_TYPE(t_iterator) = _BIDIRECTIONAL_ITERATOR;

    return t_iterator;
}

range_t _multimap_equal_range(const multimap_t* cpt_multimap, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, cpt_multimap);
    return _multimap_equal_range_varg(cpt_multimap, val_elemlist);
}

range_t _multimap_equal_range_varg(const multimap_t* cpt_multimap, va_list val_elemlist)
{
    range_t t_range;

    assert(cpt_multimap != NULL);

    _type_get_varg_value(&((multimap_t*)cpt_multimap)->_t_pair._t_typeinfofirst,
        val_elemlist, cpt_multimap->_t_pair.first);
#ifdef CSTL_MULTIMAP_AVL_TREE
    t_range = _avl_tree_equal_range(&cpt_multimap->_t_tree, &cpt_multimap->_t_pair);
#else
    t_range = _rb_tree_equal_range(&cpt_multimap->_t_tree, &cpt_multimap->_t_pair);
#endif

    _GET_CONTAINER(t_range.t_begin) = (multimap_t*)cpt_multimap;
    _GET_MULTIMAP_CONTAINER_TYPE(t_range.t_begin) = _MULTIMAP_CONTAINER;
    _GET_MULTIMAP_ITERATOR_TYPE(t_range.t_begin) = _BIDIRECTIONAL_ITERATOR;
    _GET_CONTAINER(t_range.t_end) = (multimap_t*)cpt_multimap;
    _GET_MULTIMAP_CONTAINER_TYPE(t_range.t_end) = _MULTIMAP_CONTAINER;
    _GET_MULTIMAP_ITERATOR_TYPE(t_range.t_end) = _BIDIRECTIONAL_ITERATOR;

    return t_range;
}

multimap_iterator_t multimap_insert(
    multimap_t* pt_multimap, const pair_t* cpt_pair)
{
    multimap_iterator_t t_iterator;

    assert(pt_multimap != NULL && cpt_pair != NULL);
    assert(_multimap_same_pair_type(&pt_multimap->_t_pair, cpt_pair));

#ifdef CSTL_MULTIMAP_AVL_TREE
    t_iterator = _avl_tree_insert_equal(&pt_multimap->_t_tree, cpt_pair);
#else
    t_iterator = _rb_tree_insert_equal(&pt_multimap->_t_tree, cpt_pair);
#endif

    _GET_CONTAINER(t_iterator) = pt_multimap;
    _GET_MULTIMAP_CONTAINER_TYPE(t_iterator) = _MULTIMAP_CONTAINER;
    _GET_MULTIMAP_ITERATOR_TYPE(t_iterator) = _BIDIRECTIONAL_ITERATOR;

    return t_iterator;
}

multimap_iterator_t multimap_insert_hint(
    multimap_t* pt_multimap, multimap_iterator_t t_hint, const pair_t* cpt_pair)
{
    assert(pt_multimap != NULL && cpt_pair != NULL);
    assert(_multimap_same_pair_type(&pt_multimap->_t_pair, cpt_pair));

#ifdef CSTL_MULTIMAP_AVL_TREE
    t_hint = _avl_tree_insert_equal(&pt_multimap->_t_tree, cpt_pair);
#else
    t_hint = _rb_tree_insert_equal(&pt_multimap->_t_tree, cpt_pair);
#endif

    _GET_CONTAINER(t_hint) = pt_multimap;
    _GET_MULTIMAP_CONTAINER_TYPE(t_hint) = _MULTIMAP_CONTAINER;
    _GET_MULTIMAP_ITERATOR_TYPE(t_hint) = _BIDIRECTIONAL_ITERATOR;

    return t_hint;
}

void multimap_insert_range(
    multimap_t* pt_multimap, multimap_iterator_t t_begin, multimap_iterator_t t_end)
{
    multimap_iterator_t t_iterator;

    assert(pt_multimap != NULL);
    assert(_GET_MULTIMAP_CONTAINER_TYPE(t_begin) == _MULTIMAP_CONTAINER &&
           _GET_MULTIMAP_ITERATOR_TYPE(t_begin) == _BIDIRECTIONAL_ITERATOR &&
           _GET_MULTIMAP_CONTAINER_TYPE(t_end) == _MULTIMAP_CONTAINER &&
           _GET_MULTIMAP_ITERATOR_TYPE(t_end) == _BIDIRECTIONAL_ITERATOR);
    assert(_GET_MULTIMAP_CONTAINER(t_begin) != pt_multimap &&
           _GET_MULTIMAP_CONTAINER(t_end) != pt_multimap &&
           _GET_MULTIMAP_CONTAINER(t_begin) == _GET_MULTIMAP_CONTAINER(t_end));

    for(t_iterator = t_begin;
        !iterator_equal(t_iterator, t_end);
        t_iterator = iterator_next(t_iterator))
    {
        multimap_insert(pt_multimap, (pair_t*)iterator_get_pointer(t_iterator));
    }
}

void multimap_erase_pos(multimap_t* pt_multimap, multimap_iterator_t t_pos)
{
    assert(pt_multimap != NULL);
    assert(_GET_MULTIMAP_CONTAINER_TYPE(t_pos) == _MULTIMAP_CONTAINER &&
           _GET_MULTIMAP_ITERATOR_TYPE(t_pos) == _BIDIRECTIONAL_ITERATOR &&
           _GET_MULTIMAP_CONTAINER(t_pos) == pt_multimap);

#ifdef CSTL_MULTIMAP_AVL_TREE
    _avl_tree_erase_pos(&pt_multimap->_t_tree, t_pos);
#else
    _rb_tree_erase_pos(&pt_multimap->_t_tree, t_pos);
#endif
}

void multimap_erase_range(
    multimap_t* pt_multimap, multimap_iterator_t t_begin, multimap_iterator_t t_end)
{
    assert(pt_multimap != NULL);
    assert(_GET_MULTIMAP_CONTAINER_TYPE(t_begin) == _MULTIMAP_CONTAINER &&
           _GET_MULTIMAP_ITERATOR_TYPE(t_begin) == _BIDIRECTIONAL_ITERATOR &&
           _GET_MULTIMAP_CONTAINER_TYPE(t_end) == _MULTIMAP_CONTAINER &&
           _GET_MULTIMAP_ITERATOR_TYPE(t_end) == _BIDIRECTIONAL_ITERATOR);
    assert(_GET_MULTIMAP_CONTAINER(t_begin) == pt_multimap &&
           _GET_MULTIMAP_CONTAINER(t_end) == pt_multimap);

#ifdef CSTL_MULTIMAP_AVL_TREE
    _avl_tree_erase_range(&pt_multimap->_t_tree, t_begin, t_end);
#else
    _rb_tree_erase_range(&pt_multimap->_t_tree, t_begin, t_end);
#endif
}

size_t _multimap_erase(multimap_t* pt_multimap, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, pt_multimap);
    return _multimap_erase_varg(pt_multimap, val_elemlist);
}

size_t _multimap_erase_varg(multimap_t* pt_multimap, va_list val_elemlist)
{
    assert(pt_multimap != NULL);

    /* get key */
    _type_get_varg_value(&pt_multimap->_t_pair._t_typeinfofirst,
        val_elemlist, pt_multimap->_t_pair.first);
#ifdef CSTL_MULTIMAP_AVL_TREE
    return _avl_tree_erase(&pt_multimap->_t_tree, &pt_multimap->_t_pair);
#else
    return _rb_tree_erase(&pt_multimap->_t_tree, &pt_multimap->_t_pair);
#endif
}

void _multimap_init_elem_auxiliary(multimap_t* pt_multimap, void* pv_elem)
{
    assert(pt_multimap != NULL && pv_elem != NULL);

    /* initialize new elements */
    if(pt_multimap->_t_tree._t_typeinfo._t_style == _TYPE_CSTL_BUILTIN)
    {
        /* get element type name */
        char s_elemtypename[_TYPE_NAME_SIZE + 1];
        _type_get_elem_typename(pt_multimap->_t_tree._t_typeinfo._sz_typename, s_elemtypename);

        pt_multimap->_t_tree._t_typeinfo._pt_type->_t_typeinit(pv_elem, s_elemtypename);
    }
    else
    {
        bool_t t_result = pt_multimap->_t_tree._t_typeinfo._pt_type->_t_typesize;
        pt_multimap->_t_tree._t_typeinfo._pt_type->_t_typeinit(pv_elem, &t_result);
        assert(t_result);
    }
}

/** local function implementation section **/
#ifndef NDEBUG
static bool_t _multimap_same_pair_type(
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
            cpt_pairsecond->_t_typeinfosecond._t_style);
}
#endif /* NDEBUG */

static void _multimap_key_less(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    pair_t* pt_first = NULL;
    pair_t* pt_second = NULL;

    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    pt_first = (pair_t*)cpv_first;
    pt_second = (pair_t*)cpv_second;

    assert(_multimap_same_pair_type(pt_first, pt_second));

    *(bool_t*)pv_output = pt_first->_t_typeinfofirst._pt_type->_t_typesize;
    pt_first->_t_typeinfofirst._pt_type->_t_typeless(
        pt_first->first, pt_second->second, pv_output);
}

static void _multimap_value_less(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    pair_t* pt_first = NULL;
    pair_t* pt_second = NULL;

    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    pt_first = (pair_t*)cpv_first;
    pt_second = (pair_t*)cpv_second;

    assert(_multimap_same_pair_type(pt_first, pt_second));

    *(bool_t*)pv_output = pt_first->_t_typeinfosecond._pt_type->_t_typesize;
    pt_first->_t_typeinfosecond._pt_type->_t_typeless(
        pt_first->second, pt_second->second, pv_output);
}

/** eof **/

