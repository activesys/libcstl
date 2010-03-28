/*
 *  The implementation of set.
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
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "cstl_alloc.h"
#include "cstl_types.h"
#include "cstl_iterator.h"
#include "cstl_iterator_private.h"

#ifdef CSTL_SET_AVL_TREE
#include "cstl_avl_tree_iterator.h"
#include "cstl_avl_tree_private.h"
#else
#include "cstl_rb_tree_iterator.h"
#include "cstl_rb_tree_private.h"
#endif

#include "cstl_set_iterator.h"
#include "cstl_set_private.h"
#include "cstl_set.h"

/** local constant declaration and local macro section **/
/* macros for type informations */
#define _GET_SET_TYPE_SIZE(pt_set)\
    ((pt_set)->_t_tree._t_typeinfo._pt_type->_t_typesize)
#define _GET_SET_TYPE_NAME(pt_set)\
    ((pt_set)->_t_tree._t_typeinfo._sz_typename)
#define _GET_SET_TYPE_BASENAME(pt_set)\
    ((pt_set)->_t_tree._t_typeinfo._pt_type->_sz_typename)
#define _GET_SET_TYPE_INIT_FUNCTION(pt_set)\
    ((pt_set)->_t_tree._t_typeinfo._pt_type->_t_typeinit)
#define _GET_SET_TYPE_COPY_FUNCTION(pt_set)\
    ((pt_set)->_t_tree._t_typeinfo._pt_type->_t_typecopy)
#define _GET_SET_TYPE_LESS_FUNCTION(pt_set)\
    ((pt_set)->_t_tree._t_typeinfo._pt_type->_t_typeless)
#define _GET_SET_TYPE_DESTROY_FUNCTION(pt_set)\
    ((pt_set)->_t_tree._t_typeinfo._pt_type->_t_typedestroy)
#define _GET_SET_TYPE_STYLE(pt_set)\
    ((pt_set)->_t_tree._t_typeinfo._t_style)

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/
/*static void _set_init_elem_auxiliary(set_t* pt_set, void* pv_elem);*/
static void _set_get_varg_value_auxiliary(
    set_t* pt_set, va_list val_elemlist, void* pv_varg);
static void _set_destroy_varg_value_auxiliary(set_t* pt_set, void* pv_varg);

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/* set iterator function */
set_iterator_t create_set_iterator(void)
{
    set_iterator_t t_newiterator;

#ifdef CSTL_SET_AVL_TREE
    t_newiterator = _create_avl_tree_iterator();
#else
    t_newiterator = _create_rb_tree_iterator();
#endif

    _GET_SET_CONTAINER_TYPE(t_newiterator) = _SET_CONTAINER;
    _GET_SET_ITERATOR_TYPE(t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

void _set_iterator_get_value(set_iterator_t t_iter, void* pv_value)
{
    assert(pv_value != NULL);
    assert(_GET_SET_CONTAINER_TYPE(t_iter) == _SET_CONTAINER && 
           _GET_SET_ITERATOR_TYPE(t_iter) == _BIDIRECTIONAL_ITERATOR); 

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_iterator_get_value(t_iter, pv_value);
#else
    _rb_tree_iterator_get_value(t_iter, pv_value);
#endif
}

const void* _set_iterator_get_pointer(set_iterator_t t_iter)
{
    assert(_GET_SET_CONTAINER_TYPE(t_iter) == _SET_CONTAINER && 
           _GET_SET_ITERATOR_TYPE(t_iter) == _BIDIRECTIONAL_ITERATOR); 

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_iterator_get_pointer(t_iter);
#else
    return _rb_tree_iterator_get_pointer(t_iter);
#endif
}

set_iterator_t _set_iterator_next(set_iterator_t t_iter)
{
    assert(_GET_SET_CONTAINER_TYPE(t_iter) == _SET_CONTAINER && 
           _GET_SET_ITERATOR_TYPE(t_iter) == _BIDIRECTIONAL_ITERATOR); 

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_iterator_next(t_iter);
#else
    return _rb_tree_iterator_next(t_iter);
#endif
}

set_iterator_t _set_iterator_prev(set_iterator_t t_iter)
{
    assert(_GET_SET_CONTAINER_TYPE(t_iter) == _SET_CONTAINER && 
           _GET_SET_ITERATOR_TYPE(t_iter) == _BIDIRECTIONAL_ITERATOR); 

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_iterator_prev(t_iter);
#else
    return _rb_tree_iterator_prev(t_iter);
#endif
}

bool_t _set_iterator_equal(set_iterator_t t_iterfirst, set_iterator_t t_itersecond)
{
    assert(_GET_SET_CONTAINER_TYPE(t_iterfirst) == _SET_CONTAINER && 
           _GET_SET_ITERATOR_TYPE(t_iterfirst) == _BIDIRECTIONAL_ITERATOR && 
           _GET_SET_CONTAINER_TYPE(t_itersecond) == _SET_CONTAINER && 
           _GET_SET_ITERATOR_TYPE(t_itersecond) == _BIDIRECTIONAL_ITERATOR);

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_iterator_equal(t_iterfirst, t_itersecond);
#else
    return _rb_tree_iterator_equal(t_iterfirst, t_itersecond);
#endif
}

int _set_iterator_distance(set_iterator_t t_iterfirst, set_iterator_t t_itersecond)
{
    assert(_GET_SET_CONTAINER_TYPE(t_iterfirst) == _SET_CONTAINER && 
           _GET_SET_ITERATOR_TYPE(t_iterfirst) == _BIDIRECTIONAL_ITERATOR && 
           _GET_SET_CONTAINER_TYPE(t_itersecond) == _SET_CONTAINER && 
           _GET_SET_ITERATOR_TYPE(t_itersecond) == _BIDIRECTIONAL_ITERATOR &&
           _GET_SET_CONTAINER(t_iterfirst) == _GET_SET_CONTAINER(t_itersecond));

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_iterator_distance(t_iterfirst, t_itersecond);
#else
    return _rb_tree_iterator_distance(t_iterfirst, t_itersecond);
#endif
}

bool_t _set_iterator_before(set_iterator_t t_iterfirst, set_iterator_t t_itersecond)
{
    assert(_GET_SET_CONTAINER_TYPE(t_iterfirst) == _SET_CONTAINER && 
           _GET_SET_ITERATOR_TYPE(t_iterfirst) == _BIDIRECTIONAL_ITERATOR && 
           _GET_SET_CONTAINER_TYPE(t_itersecond) == _SET_CONTAINER && 
           _GET_SET_ITERATOR_TYPE(t_itersecond) == _BIDIRECTIONAL_ITERATOR &&
           _GET_SET_CONTAINER(t_iterfirst) == _GET_SET_CONTAINER(t_itersecond));

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_iterator_before(t_iterfirst, t_itersecond);
#else
    return _rb_tree_iterator_before(t_iterfirst, t_itersecond);
#endif
}

/* set private function */
set_t* _create_set(const char* s_typename)
{
#ifdef CSTL_SET_AVL_TREE
    return (set_t*)_create_avl_tree(s_typename);
#else
    return (set_t*)_create_rb_tree(s_typename);
#endif
}

bool_t _create_set_auxiliary(set_t* pt_set, const char* s_typename)
{
    assert(pt_set != NULL && s_typename != NULL);

#ifdef CSTL_SET_AVL_TREE
    return _create_avl_tree_auxiliary(&pt_set->_t_tree, s_typename);
#else
    return _create_rb_tree_auxiliary(&pt_set->_t_tree, s_typename);
#endif
}

/* set function */
void set_init(set_t* pt_set)
{
    assert(pt_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_init(&pt_set->_t_tree, NULL);
#else
    _rb_tree_init(&pt_set->_t_tree, NULL);
#endif
}

void set_init_ex(set_t* pt_set, binary_function_t t_less)
{
    assert(pt_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_init(&pt_set->_t_tree, t_less);
#else
    _rb_tree_init(&pt_set->_t_tree, t_less);
#endif
}

void _set_destroy_auxiliary(set_t* pt_set)
{
    assert(pt_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_destroy_auxiliary(&pt_set->_t_tree);
#else
    _rb_tree_destroy_auxiliary(&pt_set->_t_tree);
#endif
}

void set_destroy(set_t* pt_set)
{
    assert(pt_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_destroy(&pt_set->_t_tree);
#else
    _rb_tree_destroy(&pt_set->_t_tree);
#endif
}

void set_init_copy(set_t* pt_setdest, const set_t* cpt_setsrc)
{
    assert(pt_setdest != NULL && cpt_setsrc != NULL);

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_init_copy(&pt_setdest->_t_tree, &cpt_setsrc->_t_tree);
#else
    _rb_tree_init_copy(&pt_setdest->_t_tree, &cpt_setsrc->_t_tree);
#endif
}

void set_init_copy_range(set_t* pt_setdest, set_iterator_t t_begin, set_iterator_t t_end)
{
    assert(pt_setdest != NULL);
    assert(_GET_SET_CONTAINER_TYPE(t_begin) == _SET_CONTAINER &&
           _GET_SET_ITERATOR_TYPE(t_begin) == _BIDIRECTIONAL_ITERATOR &&
           _GET_SET_CONTAINER_TYPE(t_end) == _SET_CONTAINER &&
           _GET_SET_ITERATOR_TYPE(t_end) == _BIDIRECTIONAL_ITERATOR);
    assert(_GET_SET_CONTAINER(t_begin) != pt_setdest &&
           _GET_SET_CONTAINER(t_end) != pt_setdest &&
           _GET_SET_CONTAINER(t_begin) == _GET_SET_CONTAINER(t_end));

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_init_copy_range(&pt_setdest->_t_tree, t_begin, t_end);
#else
    _rb_tree_init_copy_range(&pt_setdest->_t_tree, t_begin, t_end);
#endif
}

void set_init_copy_range_ex(
    set_t* pt_setdest, set_iterator_t t_begin, set_iterator_t t_end, binary_function_t t_less)
{
    assert(pt_setdest != NULL);
    assert(_GET_SET_CONTAINER_TYPE(t_begin) == _SET_CONTAINER &&
           _GET_SET_ITERATOR_TYPE(t_begin) == _BIDIRECTIONAL_ITERATOR &&
           _GET_SET_CONTAINER_TYPE(t_end) == _SET_CONTAINER &&
           _GET_SET_ITERATOR_TYPE(t_end) == _BIDIRECTIONAL_ITERATOR);
    assert(_GET_SET_CONTAINER(t_begin) != pt_setdest &&
           _GET_SET_CONTAINER(t_end) != pt_setdest &&
           _GET_SET_CONTAINER(t_begin) == _GET_SET_CONTAINER(t_end));

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_init_copy_range_ex(&pt_setdest->_t_tree, t_begin, t_end, t_less);
#else
    _rb_tree_init_copy_range_ex(&pt_setdest->_t_tree, t_begin, t_end, t_less);
#endif
}

void set_assign(set_t* pt_setdest, const set_t* cpt_setsrc)
{
    assert(pt_setdest != NULL && cpt_setsrc != NULL);

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_assign(&pt_setdest->_t_tree, &cpt_setsrc->_t_tree);
#else
    _rb_tree_assign(&pt_setdest->_t_tree, &cpt_setsrc->_t_tree);
#endif
}

bool_t set_empty(const set_t* cpt_set)
{
    assert(cpt_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_empty(&cpt_set->_t_tree);
#else
    return _rb_tree_empty(&cpt_set->_t_tree);
#endif
}

size_t set_size(const set_t* cpt_set)
{
    assert(cpt_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_size(&cpt_set->_t_tree);
#else
    return _rb_tree_size(&cpt_set->_t_tree);
#endif
}

size_t set_max_size(const set_t* cpt_set)
{
    assert(cpt_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_max_size(&cpt_set->_t_tree);
#else
    return _rb_tree_max_size(&cpt_set->_t_tree);
#endif
}

set_iterator_t set_begin(const set_t* cpt_set)
{
    set_iterator_t t_newiterator;

    assert(cpt_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    t_newiterator = _avl_tree_begin(&cpt_set->_t_tree);
#else
    t_newiterator = _rb_tree_begin(&cpt_set->_t_tree);
#endif

    _GET_CONTAINER(t_newiterator) = (set_t*)cpt_set;
    _GET_SET_CONTAINER_TYPE(t_newiterator) = _SET_CONTAINER;
    _GET_SET_ITERATOR_TYPE(t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

set_iterator_t set_end(const set_t* cpt_set)
{
    set_iterator_t t_newiterator;

    assert(cpt_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    t_newiterator = _avl_tree_end(&cpt_set->_t_tree);
#else
    t_newiterator = _rb_tree_end(&cpt_set->_t_tree);
#endif

    _GET_CONTAINER(t_newiterator) = (set_t*)cpt_set;
    _GET_SET_CONTAINER_TYPE(t_newiterator) = _SET_CONTAINER;
    _GET_SET_ITERATOR_TYPE(t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

set_iterator_t set_rbegin(const set_t* cpt_set)
{
    set_iterator_t t_newiterator;

    assert(cpt_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    t_newiterator = _avl_tree_rbegin(&cpt_set->_t_tree);
#else
    t_newiterator = _rb_tree_rbegin(&cpt_set->_t_tree);
#endif

    _GET_CONTAINER(t_newiterator) = (set_t*)cpt_set;
    _GET_SET_CONTAINER_TYPE(t_newiterator) = _SET_CONTAINER;
    _GET_SET_ITERATOR_TYPE(t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

set_iterator_t set_rend(const set_t* cpt_set)
{
    set_iterator_t t_newiterator;

    assert(cpt_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    t_newiterator = _avl_tree_rend(&cpt_set->_t_tree);
#else
    t_newiterator = _rb_tree_rend(&cpt_set->_t_tree);
#endif

    _GET_CONTAINER(t_newiterator) = (set_t*)cpt_set;
    _GET_SET_CONTAINER_TYPE(t_newiterator) = _SET_CONTAINER;
    _GET_SET_ITERATOR_TYPE(t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

binary_function_t set_key_less(const set_t* cpt_set)
{
    assert(cpt_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_key_less(&cpt_set->_t_tree);
#else
    return _rb_tree_key_less(&cpt_set->_t_tree);
#endif
}

binary_function_t set_value_less(const set_t* cpt_set)
{
    return set_key_less(cpt_set);
}

void set_clear(set_t* pt_set)
{
    assert(pt_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_clear(&pt_set->_t_tree);
#else
    _rb_tree_clear(&pt_set->_t_tree);
#endif
}

set_iterator_t _set_find(const set_t* cpt_set, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, cpt_set);
    return _set_find_varg(cpt_set, val_elemlist);
}

set_iterator_t _set_find_varg(const set_t* cpt_set, va_list val_elemlist)
{
    set_iterator_t t_iter;
    void*          pv_varg = NULL;

    assert(cpt_set != NULL);

    pv_varg = allocate(&((set_t*)cpt_set)->_t_tree._t_allocater,
        _GET_SET_TYPE_SIZE(cpt_set), 1);
    assert(pv_varg != NULL);
    _set_get_varg_value_auxiliary((set_t*)cpt_set, val_elemlist, pv_varg);

#ifdef CSTL_SET_AVL_TREE
    t_iter = _avl_tree_find(&cpt_set->_t_tree, pv_varg);
#else
    t_iter = _rb_tree_find(&cpt_set->_t_tree, pv_varg);
#endif

    _set_destroy_varg_value_auxiliary((set_t*)cpt_set, pv_varg);
    deallocate(&((set_t*)cpt_set)->_t_tree._t_allocater, pv_varg,
        _GET_SET_TYPE_SIZE(cpt_set), 1);

    _GET_CONTAINER(t_iter) = (set_t*)cpt_set;
    _GET_SET_CONTAINER_TYPE(t_iter) = _SET_CONTAINER;
    _GET_SET_ITERATOR_TYPE(t_iter) = _BIDIRECTIONAL_ITERATOR;

    return t_iter;
}

size_t _set_count(const set_t* cpt_set, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, cpt_set);
    return _set_count_varg(cpt_set, val_elemlist);
}

size_t _set_count_varg(const set_t* cpt_set, va_list val_elemlist)
{
    void*          pv_varg = NULL;
    size_t         t_count = 0;

    assert(cpt_set != NULL);

    pv_varg = allocate(&((set_t*)cpt_set)->_t_tree._t_allocater,
        _GET_SET_TYPE_SIZE(cpt_set), 1);
    assert(pv_varg != NULL);
    _set_get_varg_value_auxiliary((set_t*)cpt_set, val_elemlist, pv_varg);

#ifdef CSTL_SET_AVL_TREE
    t_count = _avl_tree_count(&cpt_set->_t_tree, pv_varg);
#else
    t_count = _rb_tree_count(&cpt_set->_t_tree, pv_varg);
#endif

    _set_destroy_varg_value_auxiliary((set_t*)cpt_set, pv_varg);
    deallocate(&((set_t*)cpt_set)->_t_tree._t_allocater, pv_varg,
        _GET_SET_TYPE_SIZE(cpt_set), 1);

    return t_count;
}

set_iterator_t _set_lower_bound(const set_t* cpt_set, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, cpt_set);
    return _set_lower_bound_varg(cpt_set, val_elemlist);
}

set_iterator_t _set_lower_bound_varg(const set_t* cpt_set, va_list val_elemlist)
{
    void*          pv_varg = NULL;
    set_iterator_t t_iter;

    assert(cpt_set != NULL);

    pv_varg = allocate(&((set_t*)cpt_set)->_t_tree._t_allocater,
        _GET_SET_TYPE_SIZE(cpt_set), 1);
    assert(pv_varg != NULL);
    _set_get_varg_value_auxiliary((set_t*)cpt_set, val_elemlist, pv_varg);

#ifdef CSTL_SET_AVL_TREE
    t_iter = _avl_tree_lower_bound(&cpt_set->_t_tree, pv_varg);
#else
    t_iter = _rb_tree_lower_bound(&cpt_set->_t_tree, pv_varg);
#endif

    _set_destroy_varg_value_auxiliary((set_t*)cpt_set, pv_varg);
    deallocate(&((set_t*)cpt_set)->_t_tree._t_allocater, pv_varg,
        _GET_SET_TYPE_SIZE(cpt_set), 1);

    _GET_CONTAINER(t_iter) = (set_t*)cpt_set;
    _GET_SET_CONTAINER_TYPE(t_iter) = _SET_CONTAINER;
    _GET_SET_ITERATOR_TYPE(t_iter) = _BIDIRECTIONAL_ITERATOR;

    return t_iter;
}

set_iterator_t _set_upper_bound(const set_t* cpt_set, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, cpt_set);
    return _set_upper_bound_varg(cpt_set, val_elemlist);
}

set_iterator_t _set_upper_bound_varg(const set_t* cpt_set, va_list val_elemlist)
{
    void*          pv_varg = NULL;
    set_iterator_t t_iter;

    assert(cpt_set != NULL);

    pv_varg = allocate(&((set_t*)cpt_set)->_t_tree._t_allocater,
        _GET_SET_TYPE_SIZE(cpt_set), 1);
    assert(pv_varg != NULL);
    _set_get_varg_value_auxiliary((set_t*)cpt_set, val_elemlist, pv_varg);

#ifdef CSTL_SET_AVL_TREE
    t_iter = _avl_tree_upper_bound(&cpt_set->_t_tree, pv_varg);
#else
    t_iter = _rb_tree_upper_bound(&cpt_set->_t_tree, pv_varg);
#endif

    _set_destroy_varg_value_auxiliary((set_t*)cpt_set, pv_varg);
    deallocate(&((set_t*)cpt_set)->_t_tree._t_allocater, pv_varg,
        _GET_SET_TYPE_SIZE(cpt_set), 1);

    _GET_CONTAINER(t_iter) = (set_t*)cpt_set;
    _GET_SET_CONTAINER_TYPE(t_iter) = _SET_CONTAINER;
    _GET_SET_ITERATOR_TYPE(t_iter) = _BIDIRECTIONAL_ITERATOR;

    return t_iter;
}

range_t _set_equal_range(const set_t* cpt_set, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, cpt_set);
    return _set_equal_range_varg(cpt_set, val_elemlist);
}

range_t _set_equal_range_varg(const set_t* cpt_set, va_list val_elemlist)
{
    void*          pv_varg = NULL;
    range_t        t_range;

    assert(cpt_set != NULL);

    pv_varg = allocate(&((set_t*)cpt_set)->_t_tree._t_allocater,
        _GET_SET_TYPE_SIZE(cpt_set), 1);
    assert(pv_varg != NULL);
    _set_get_varg_value_auxiliary((set_t*)cpt_set, val_elemlist, pv_varg);

#ifdef CSTL_SET_AVL_TREE
    t_range = _avl_tree_equal_range(&cpt_set->_t_tree, pv_varg);
#else
    t_range = _rb_tree_equal_range(&cpt_set->_t_tree, pv_varg);
#endif

    _set_destroy_varg_value_auxiliary((set_t*)cpt_set, pv_varg);
    deallocate(&((set_t*)cpt_set)->_t_tree._t_allocater, pv_varg,
        _GET_SET_TYPE_SIZE(cpt_set), 1);

    _GET_CONTAINER(t_range.t_begin) = (set_t*)cpt_set;
    _GET_SET_CONTAINER_TYPE(t_range.t_begin) = _SET_CONTAINER;
    _GET_SET_ITERATOR_TYPE(t_range.t_begin) = _BIDIRECTIONAL_ITERATOR;

    _GET_CONTAINER(t_range.t_end) = (set_t*)cpt_set;
    _GET_SET_CONTAINER_TYPE(t_range.t_end) = _SET_CONTAINER;
    _GET_SET_ITERATOR_TYPE(t_range.t_end) = _BIDIRECTIONAL_ITERATOR;

    return t_range;
}

bool_t set_equal(const set_t* cpt_setfirst, const set_t* cpt_setsecond)
{
    assert(cpt_setfirst != NULL && cpt_setsecond != NULL);

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_equal(&cpt_setfirst->_t_tree, &cpt_setsecond->_t_tree);
#else
    return _rb_tree_equal(&cpt_setfirst->_t_tree, &cpt_setsecond->_t_tree);
#endif
}

bool_t set_not_equal(const set_t* cpt_setfirst, const set_t* cpt_setsecond)
{
    assert(cpt_setfirst != NULL && cpt_setsecond != NULL);

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_not_equal(&cpt_setfirst->_t_tree, &cpt_setsecond->_t_tree);
#else
    return _rb_tree_not_equal(&cpt_setfirst->_t_tree, &cpt_setsecond->_t_tree);
#endif
}

bool_t set_less(const set_t* cpt_setfirst, const set_t* cpt_setsecond)
{
    assert(cpt_setfirst != NULL && cpt_setsecond != NULL);

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_less(&cpt_setfirst->_t_tree, &cpt_setsecond->_t_tree);
#else
    return _rb_tree_less(&cpt_setfirst->_t_tree, &cpt_setsecond->_t_tree);
#endif
}

bool_t set_less_equal(const set_t* cpt_setfirst, const set_t* cpt_setsecond)
{
    assert(cpt_setfirst != NULL && cpt_setsecond != NULL);

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_less_equal(&cpt_setfirst->_t_tree, &cpt_setsecond->_t_tree);
#else
    return _rb_tree_less_equal(&cpt_setfirst->_t_tree, &cpt_setsecond->_t_tree);
#endif
}

bool_t set_greater(const set_t* cpt_setfirst, const set_t* cpt_setsecond)
{
    assert(cpt_setfirst != NULL && cpt_setsecond != NULL);

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_greater(&cpt_setfirst->_t_tree, &cpt_setsecond->_t_tree);
#else
    return _rb_tree_greater(&cpt_setfirst->_t_tree, &cpt_setsecond->_t_tree);
#endif
}

bool_t set_greater_equal(const set_t* cpt_setfirst, const set_t* cpt_setsecond)
{
    assert(cpt_setfirst != NULL && cpt_setsecond != NULL);

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_greater_equal(&cpt_setfirst->_t_tree, &cpt_setsecond->_t_tree);
#else
    return _rb_tree_greater_equal(&cpt_setfirst->_t_tree, &cpt_setsecond->_t_tree);
#endif
}

void set_swap(set_t* pt_setfirst, set_t* pt_setsecond)
{
    assert(pt_setfirst != NULL && pt_setsecond != NULL);

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_swap(&pt_setfirst->_t_tree, &pt_setsecond->_t_tree);
#else
    _rb_tree_swap(&pt_setfirst->_t_tree, &pt_setsecond->_t_tree);
#endif
}

set_iterator_t _set_insert(set_t* pt_set, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, pt_set);
    return _set_insert_varg(pt_set, val_elemlist);
}

set_iterator_t _set_insert_varg(set_t* pt_set, va_list val_elemlist)
{
    void*          pv_varg = NULL;
    set_iterator_t t_iter;

    assert(pt_set != NULL);

    pv_varg = allocate(&pt_set->_t_tree._t_allocater, _GET_SET_TYPE_SIZE(pt_set), 1);
    assert(pv_varg != NULL);
    _set_get_varg_value_auxiliary(pt_set, val_elemlist, pv_varg);

#ifdef CSTL_SET_AVL_TREE
    t_iter = _avl_tree_insert_unique(&pt_set->_t_tree, pv_varg);
#else
    t_iter = _rb_tree_insert_unique(&pt_set->_t_tree, pv_varg);
#endif

    _set_destroy_varg_value_auxiliary(pt_set, pv_varg);
    deallocate(&pt_set->_t_tree._t_allocater, pv_varg, _GET_SET_TYPE_SIZE(pt_set), 1);

    _GET_CONTAINER(t_iter) = pt_set;
    _GET_SET_CONTAINER_TYPE(t_iter) = _SET_CONTAINER;
    _GET_SET_ITERATOR_TYPE(t_iter) = _BIDIRECTIONAL_ITERATOR;

    return t_iter;
}

set_iterator_t _set_insert_hint(set_t* pt_set, set_iterator_t t_hint, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_hint);
    return _set_insert_hint_varg(pt_set, t_hint, val_elemlist);
}

set_iterator_t _set_insert_hint_varg(
    set_t* pt_set, set_iterator_t t_hint, va_list val_elemlist)
{
    void* pv_varg = NULL;

    assert(pt_set != NULL);

    pv_varg = allocate(&pt_set->_t_tree._t_allocater, _GET_SET_TYPE_SIZE(pt_set), 1);
    assert(pv_varg != NULL);
    _set_get_varg_value_auxiliary(pt_set, val_elemlist, pv_varg);

#ifdef CSTL_SET_AVL_TREE
    t_hint = _avl_tree_insert_unique(&pt_set->_t_tree, pv_varg);
#else
    t_hint = _rb_tree_insert_unique(&pt_set->_t_tree, pv_varg);
#endif

    _set_destroy_varg_value_auxiliary(pt_set, pv_varg);
    deallocate(&pt_set->_t_tree._t_allocater, pv_varg, _GET_SET_TYPE_SIZE(pt_set), 1);

    _GET_CONTAINER(t_hint) = pt_set;
    _GET_SET_CONTAINER_TYPE(t_hint) = _SET_CONTAINER;
    _GET_SET_ITERATOR_TYPE(t_hint) = _BIDIRECTIONAL_ITERATOR;

    return t_hint;
}

void set_insert_range(set_t* pt_set, set_iterator_t t_begin, set_iterator_t t_end)
{
    assert(pt_set != NULL);
    assert(_GET_SET_CONTAINER_TYPE(t_begin) == _SET_CONTAINER && 
           _GET_SET_ITERATOR_TYPE(t_begin) == _BIDIRECTIONAL_ITERATOR && 
           _GET_SET_CONTAINER_TYPE(t_end) == _SET_CONTAINER && 
           _GET_SET_ITERATOR_TYPE(t_end) == _BIDIRECTIONAL_ITERATOR);
    assert(_GET_SET_CONTAINER(t_begin) != pt_set && 
           _GET_SET_CONTAINER(t_end) != pt_set && 
           _GET_SET_CONTAINER(t_begin) == _GET_SET_CONTAINER(t_end));

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_insert_unique_range(&pt_set->_t_tree, t_begin, t_end);
#else
    _rb_tree_insert_unique_range(&pt_set->_t_tree, t_begin, t_end);
#endif
}

void set_erase_pos(set_t* pt_set, set_iterator_t t_pos)
{
    assert(pt_set != NULL);
    assert(_GET_SET_CONTAINER_TYPE(t_pos) == _SET_CONTAINER && 
           _GET_SET_ITERATOR_TYPE(t_pos) == _BIDIRECTIONAL_ITERATOR && 
           _GET_SET_CONTAINER(t_pos) == pt_set);

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_erase_pos(&pt_set->_t_tree, t_pos);
#else
    _rb_tree_erase_pos(&pt_set->_t_tree, t_pos);
#endif
}

void set_erase_range(set_t* pt_set, set_iterator_t t_begin, set_iterator_t t_end)
{
    assert(pt_set != NULL);
    assert(_GET_SET_CONTAINER_TYPE(t_begin) == _SET_CONTAINER && 
           _GET_SET_ITERATOR_TYPE(t_begin) == _BIDIRECTIONAL_ITERATOR && 
           _GET_SET_CONTAINER_TYPE(t_end) == _SET_CONTAINER && 
           _GET_SET_ITERATOR_TYPE(t_end) == _BIDIRECTIONAL_ITERATOR);
    assert(_GET_SET_CONTAINER(t_begin) == pt_set && 
           _GET_SET_CONTAINER(t_end) == pt_set);

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_erase_range(&pt_set->_t_tree, t_begin, t_end);
#else
    _rb_tree_erase_range(&pt_set->_t_tree, t_begin, t_end);
#endif
}

size_t _set_erase(set_t* pt_set, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, pt_set);
    return _set_erase_varg(pt_set, val_elemlist);
}

size_t _set_erase_varg(set_t* pt_set, va_list val_elemlist)
{
    void*          pv_varg = NULL;
    size_t         t_count = 0;

    assert(pt_set != NULL);

    pv_varg = allocate(&pt_set->_t_tree._t_allocater, _GET_SET_TYPE_SIZE(pt_set), 1);
    assert(pv_varg != NULL);
    _set_get_varg_value_auxiliary(pt_set, val_elemlist, pv_varg);

#ifdef CSTL_SET_AVL_TREE
    t_count = _avl_tree_erase(&pt_set->_t_tree, pv_varg);
#else
    t_count = _rb_tree_erase(&pt_set->_t_tree, pv_varg);
#endif

    _set_destroy_varg_value_auxiliary(pt_set, pv_varg);
    deallocate(&pt_set->_t_tree._t_allocater, pv_varg, _GET_SET_TYPE_SIZE(pt_set), 1);

    return t_count;
}

void _set_init_elem_auxiliary(set_t* pt_set, void* pv_elem)
{
    assert(pt_set != NULL && pv_elem != NULL);

    /* initialize new elements */
    if(_GET_SET_TYPE_STYLE(pt_set) == _TYPE_CSTL_BUILTIN)
    {
        /* get element type name */
        char s_elemtypename[_TYPE_NAME_SIZE + 1];
        _type_get_elem_typename(_GET_SET_TYPE_NAME(pt_set), s_elemtypename);

        _GET_SET_TYPE_INIT_FUNCTION(pt_set)(pv_elem, s_elemtypename);
    }
    else
    {
        bool_t t_result = _GET_SET_TYPE_SIZE(pt_set);
        _GET_SET_TYPE_INIT_FUNCTION(pt_set)(pv_elem, &t_result);
        assert(t_result);
    }
}

/** local function implementation section **/
static void _set_get_varg_value_auxiliary(
    set_t* pt_set, va_list val_elemlist, void* pv_varg)
{
    _set_init_elem_auxiliary(pt_set, pv_varg);
    _type_get_varg_value(&pt_set->_t_tree._t_typeinfo, val_elemlist, pv_varg);
}

static void _set_destroy_varg_value_auxiliary(set_t* pt_set, void* pv_varg)
{
    /* destroy varg value and free memory */
    bool_t t_result = _GET_SET_TYPE_SIZE(pt_set);
    _GET_SET_TYPE_DESTROY_FUNCTION(pt_set)(pv_varg, &t_result);
    assert(t_result);
}

/** eof **/

