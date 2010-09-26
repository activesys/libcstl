/*
 *  The implementation of multiset.
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

#include <cstl/cstl_alloc.h>
#include <cstl/cstl_types.h>
#include <cstl/cstl_iterator.h>
#include <cstl/cstl_iterator_private.h>

#ifdef CSTL_MULTISET_AVL_TREE
#include <cstl/cstl_avl_tree_iterator.h>
#include <cstl/cstl_avl_tree_private.h>
#else
#include <cstl/cstl_rb_tree_iterator.h>
#include <cstl/cstl_rb_tree_private.h>
#endif

#include <cstl/cstl_multiset_iterator.h>
#include <cstl/cstl_multiset_private.h>
#include <cstl/cstl_multiset.h>

/** local constant declaration and local macro section **/
/* macros for type informations */
#define _GET_MULTISET_TYPE_SIZE(pt_multiset)\
    ((pt_multiset)->_t_tree._t_typeinfo._pt_type->_t_typesize)
#define _GET_MULTISET_TYPE_NAME(pt_multiset)\
    ((pt_multiset)->_t_tree._t_typeinfo._sz_typename)
#define _GET_MULTISET_TYPE_BASENAME(pt_multiset)\
    ((pt_multiset)->_t_tree._t_typeinfo._pt_type->_sz_typename)
#define _GET_MULTISET_TYPE_INIT_FUNCTION(pt_multiset)\
    ((pt_multiset)->_t_tree._t_typeinfo._pt_type->_t_typeinit)
#define _GET_MULTISET_TYPE_COPY_FUNCTION(pt_multiset)\
    ((pt_multiset)->_t_tree._t_typeinfo._pt_type->_t_typecopy)
#define _GET_MULTISET_TYPE_LESS_FUNCTION(pt_multiset)\
    ((pt_multiset)->_t_tree._t_typeinfo._pt_type->_t_typeless)
#define _GET_MULTISET_TYPE_DESTROY_FUNCTION(pt_multiset)\
    ((pt_multiset)->_t_tree._t_typeinfo._pt_type->_t_typedestroy)
#define _GET_MULTISET_TYPE_STYLE(pt_multiset)\
    ((pt_multiset)->_t_tree._t_typeinfo._t_style)

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/
static void _multiset_get_varg_value_auxiliary(
    multiset_t* pt_multiset, va_list val_elemlist, void* pv_varg);
static void _multiset_destroy_varg_value_auxiliary(multiset_t* pt_multiset, void* pv_varg);

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/* multiset iterator function */
multiset_iterator_t create_multiset_iterator(void)
{
    multiset_iterator_t t_newiterator;

#ifdef CSTL_MULTISET_AVL_TREE
    t_newiterator = _create_avl_tree_iterator();
#else
    t_newiterator = _create_rb_tree_iterator();
#endif

    _GET_MULTISET_CONTAINER_TYPE(t_newiterator) = _MULTISET_CONTAINER;
    _GET_MULTISET_ITERATOR_TYPE(t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

void _multiset_iterator_get_value(multiset_iterator_t t_iter, void* pv_value)
{
    assert(pv_value != NULL);
    assert(_GET_MULTISET_CONTAINER_TYPE(t_iter) == _MULTISET_CONTAINER && 
           _GET_MULTISET_ITERATOR_TYPE(t_iter) == _BIDIRECTIONAL_ITERATOR); 

#ifdef CSTL_MULTISET_AVL_TREE
    _avl_tree_iterator_get_value(t_iter, pv_value);
#else
    _rb_tree_iterator_get_value(t_iter, pv_value);
#endif
}

const void* _multiset_iterator_get_pointer(multiset_iterator_t t_iter)
{
    assert(_GET_MULTISET_CONTAINER_TYPE(t_iter) == _MULTISET_CONTAINER && 
           _GET_MULTISET_ITERATOR_TYPE(t_iter) == _BIDIRECTIONAL_ITERATOR); 

#ifdef CSTL_MULTISET_AVL_TREE
    return _avl_tree_iterator_get_pointer(t_iter);
#else
    return _rb_tree_iterator_get_pointer(t_iter);
#endif
}

multiset_iterator_t _multiset_iterator_next(multiset_iterator_t t_iter)
{
    assert(_GET_MULTISET_CONTAINER_TYPE(t_iter) == _MULTISET_CONTAINER && 
           _GET_MULTISET_ITERATOR_TYPE(t_iter) == _BIDIRECTIONAL_ITERATOR); 

#ifdef CSTL_MULTISET_AVL_TREE
    return _avl_tree_iterator_next(t_iter);
#else
    return _rb_tree_iterator_next(t_iter);
#endif
}

multiset_iterator_t _multiset_iterator_prev(multiset_iterator_t t_iter)
{
    assert(_GET_MULTISET_CONTAINER_TYPE(t_iter) == _MULTISET_CONTAINER && 
           _GET_MULTISET_ITERATOR_TYPE(t_iter) == _BIDIRECTIONAL_ITERATOR); 

#ifdef CSTL_MULTISET_AVL_TREE
    return _avl_tree_iterator_prev(t_iter);
#else
    return _rb_tree_iterator_prev(t_iter);
#endif
}

bool_t _multiset_iterator_equal(
    multiset_iterator_t t_iterfirst, multiset_iterator_t t_itersecond)
{
    assert(_GET_MULTISET_CONTAINER_TYPE(t_iterfirst) == _MULTISET_CONTAINER && 
           _GET_MULTISET_ITERATOR_TYPE(t_iterfirst) == _BIDIRECTIONAL_ITERATOR && 
           _GET_MULTISET_CONTAINER_TYPE(t_itersecond) == _MULTISET_CONTAINER && 
           _GET_MULTISET_ITERATOR_TYPE(t_itersecond) == _BIDIRECTIONAL_ITERATOR);

#ifdef CSTL_MULTISET_AVL_TREE
    return _avl_tree_iterator_equal(t_iterfirst, t_itersecond);
#else
    return _rb_tree_iterator_equal(t_iterfirst, t_itersecond);
#endif
}

int _multiset_iterator_distance(
    multiset_iterator_t t_iterfirst, multiset_iterator_t t_itersecond)
{
    assert(_GET_MULTISET_CONTAINER_TYPE(t_iterfirst) == _MULTISET_CONTAINER && 
           _GET_MULTISET_ITERATOR_TYPE(t_iterfirst) == _BIDIRECTIONAL_ITERATOR && 
           _GET_MULTISET_CONTAINER_TYPE(t_itersecond) == _MULTISET_CONTAINER && 
           _GET_MULTISET_ITERATOR_TYPE(t_itersecond) == _BIDIRECTIONAL_ITERATOR &&
           _GET_MULTISET_CONTAINER(t_iterfirst) == _GET_MULTISET_CONTAINER(t_itersecond));

#ifdef CSTL_MULTISET_AVL_TREE
    return _avl_tree_iterator_distance(t_iterfirst, t_itersecond);
#else
    return _rb_tree_iterator_distance(t_iterfirst, t_itersecond);
#endif
}

bool_t _multiset_iterator_before(
    multiset_iterator_t t_iterfirst, multiset_iterator_t t_itersecond)
{
    assert(_GET_MULTISET_CONTAINER_TYPE(t_iterfirst) == _MULTISET_CONTAINER && 
           _GET_MULTISET_ITERATOR_TYPE(t_iterfirst) == _BIDIRECTIONAL_ITERATOR && 
           _GET_MULTISET_CONTAINER_TYPE(t_itersecond) == _MULTISET_CONTAINER && 
           _GET_MULTISET_ITERATOR_TYPE(t_itersecond) == _BIDIRECTIONAL_ITERATOR &&
           _GET_MULTISET_CONTAINER(t_iterfirst) == 
           _GET_MULTISET_CONTAINER(t_itersecond));

#ifdef CSTL_MULTISET_AVL_TREE
    return _avl_tree_iterator_before(t_iterfirst, t_itersecond);
#else
    return _rb_tree_iterator_before(t_iterfirst, t_itersecond);
#endif
}

/* multiset private function */
multiset_t* _create_multiset(const char* s_typename)
{
#ifdef CSTL_MULTISET_AVL_TREE
    return (multiset_t*)_create_avl_tree(s_typename);
#else
    return (multiset_t*)_create_rb_tree(s_typename);
#endif
}

bool_t _create_multiset_auxiliary(multiset_t* pt_multiset, const char* s_typename)
{
    assert(pt_multiset != NULL && s_typename != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    return _create_avl_tree_auxiliary(&pt_multiset->_t_tree, s_typename);
#else
    return _create_rb_tree_auxiliary(&pt_multiset->_t_tree, s_typename);
#endif
}

/* multiset function */
void multiset_init(multiset_t* pt_multiset)
{
    assert(pt_multiset != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    _avl_tree_init(&pt_multiset->_t_tree, NULL);
#else
    _rb_tree_init(&pt_multiset->_t_tree, NULL);
#endif
}

void multiset_init_ex(multiset_t* pt_multiset, binary_function_t t_compare)
{
    assert(pt_multiset != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    _avl_tree_init(&pt_multiset->_t_tree, t_compare);
#else
    _rb_tree_init(&pt_multiset->_t_tree, t_compare);
#endif
}

void _multiset_destroy_auxiliary(multiset_t* pt_multiset)
{
    assert(pt_multiset != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    _avl_tree_destroy_auxiliary(&pt_multiset->_t_tree);
#else
    _rb_tree_destroy_auxiliary(&pt_multiset->_t_tree);
#endif
}

void multiset_destroy(multiset_t* pt_multiset)
{
    assert(pt_multiset != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    _avl_tree_destroy(&pt_multiset->_t_tree);
#else
    _rb_tree_destroy(&pt_multiset->_t_tree);
#endif
}

void multiset_init_copy(multiset_t* pt_multisetdest, const multiset_t* cpt_multisetsrc)
{
    assert(pt_multisetdest != NULL && cpt_multisetsrc != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    _avl_tree_init_copy(&pt_multisetdest->_t_tree, &cpt_multisetsrc->_t_tree);
#else
    _rb_tree_init_copy(&pt_multisetdest->_t_tree, &cpt_multisetsrc->_t_tree);
#endif
}

void multiset_init_copy_range(
    multiset_t* pt_multisetdest, multiset_iterator_t t_begin, multiset_iterator_t t_end)
{
    assert(pt_multisetdest != NULL);
    assert(_GET_MULTISET_CONTAINER_TYPE(t_begin) == _MULTISET_CONTAINER &&
           _GET_MULTISET_ITERATOR_TYPE(t_begin) == _BIDIRECTIONAL_ITERATOR &&
           _GET_MULTISET_CONTAINER_TYPE(t_end) == _MULTISET_CONTAINER &&
           _GET_MULTISET_ITERATOR_TYPE(t_end) == _BIDIRECTIONAL_ITERATOR);
    assert(_GET_MULTISET_CONTAINER(t_begin) != pt_multisetdest &&
           _GET_MULTISET_CONTAINER(t_end) != pt_multisetdest &&
           _GET_MULTISET_CONTAINER(t_begin) == _GET_MULTISET_CONTAINER(t_end));

#ifdef CSTL_MULTISET_AVL_TREE
    _avl_tree_init_copy_range(&pt_multisetdest->_t_tree, t_begin, t_end);
#else
    _rb_tree_init_copy_range(&pt_multisetdest->_t_tree, t_begin, t_end);
#endif
}

void multiset_init_copy_range_ex(multiset_t* pt_multisetdest,
    multiset_iterator_t t_begin, multiset_iterator_t t_end, binary_function_t t_compare)
{
    assert(pt_multisetdest != NULL);
    assert(_GET_MULTISET_CONTAINER_TYPE(t_begin) == _MULTISET_CONTAINER &&
           _GET_MULTISET_ITERATOR_TYPE(t_begin) == _BIDIRECTIONAL_ITERATOR &&
           _GET_MULTISET_CONTAINER_TYPE(t_end) == _MULTISET_CONTAINER &&
           _GET_MULTISET_ITERATOR_TYPE(t_end) == _BIDIRECTIONAL_ITERATOR);
    assert(_GET_MULTISET_CONTAINER(t_begin) != pt_multisetdest &&
           _GET_MULTISET_CONTAINER(t_end) != pt_multisetdest &&
           _GET_MULTISET_CONTAINER(t_begin) == _GET_MULTISET_CONTAINER(t_end));

#ifdef CSTL_MULTISET_AVL_TREE
    _avl_tree_init_copy_range_ex(&pt_multisetdest->_t_tree, t_begin, t_end, t_compare);
#else
    _rb_tree_init_copy_range_ex(&pt_multisetdest->_t_tree, t_begin, t_end, t_compare);
#endif
}

void multiset_assign(multiset_t* pt_multisetdest, const multiset_t* cpt_multisetsrc)
{
    assert(pt_multisetdest != NULL && cpt_multisetsrc != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    _avl_tree_assign(&pt_multisetdest->_t_tree, &cpt_multisetsrc->_t_tree);
#else
    _rb_tree_assign(&pt_multisetdest->_t_tree, &cpt_multisetsrc->_t_tree);
#endif
}

bool_t multiset_empty(const multiset_t* cpt_multiset)
{
    assert(cpt_multiset != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    return _avl_tree_empty(&cpt_multiset->_t_tree);
#else
    return _rb_tree_empty(&cpt_multiset->_t_tree);
#endif
}

size_t multiset_size(const multiset_t* cpt_multiset)
{
    assert(cpt_multiset != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    return _avl_tree_size(&cpt_multiset->_t_tree);
#else
    return _rb_tree_size(&cpt_multiset->_t_tree);
#endif
}

size_t multiset_max_size(const multiset_t* cpt_multiset)
{
    assert(cpt_multiset != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    return _avl_tree_max_size(&cpt_multiset->_t_tree);
#else
    return _rb_tree_max_size(&cpt_multiset->_t_tree);
#endif
}

multiset_iterator_t multiset_begin(const multiset_t* cpt_multiset)
{
    multiset_iterator_t t_newiterator;

    assert(cpt_multiset != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    t_newiterator = _avl_tree_begin(&cpt_multiset->_t_tree);
#else
    t_newiterator = _rb_tree_begin(&cpt_multiset->_t_tree);
#endif

    _GET_CONTAINER(t_newiterator) = (multiset_t*)cpt_multiset;
    _GET_MULTISET_CONTAINER_TYPE(t_newiterator) = _MULTISET_CONTAINER;
    _GET_MULTISET_ITERATOR_TYPE(t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

multiset_iterator_t multiset_end(const multiset_t* cpt_multiset)
{
    multiset_iterator_t t_newiterator;

    assert(cpt_multiset != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    t_newiterator = _avl_tree_end(&cpt_multiset->_t_tree);
#else
    t_newiterator = _rb_tree_end(&cpt_multiset->_t_tree);
#endif

    _GET_CONTAINER(t_newiterator) = (multiset_t*)cpt_multiset;
    _GET_MULTISET_CONTAINER_TYPE(t_newiterator) = _MULTISET_CONTAINER;
    _GET_MULTISET_ITERATOR_TYPE(t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

multiset_iterator_t multiset_rbegin(const multiset_t* cpt_multiset)
{
    multiset_iterator_t t_newiterator;

    assert(cpt_multiset != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    t_newiterator = _avl_tree_rbegin(&cpt_multiset->_t_tree);
#else
    t_newiterator = _rb_tree_rbegin(&cpt_multiset->_t_tree);
#endif

    _GET_CONTAINER(t_newiterator) = (multiset_t*)cpt_multiset;
    _GET_MULTISET_CONTAINER_TYPE(t_newiterator) = _MULTISET_CONTAINER;
    _GET_MULTISET_ITERATOR_TYPE(t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

multiset_iterator_t multiset_rend(const multiset_t* cpt_multiset)
{
    multiset_iterator_t t_newiterator;

    assert(cpt_multiset != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    t_newiterator = _avl_tree_rend(&cpt_multiset->_t_tree);
#else
    t_newiterator = _rb_tree_rend(&cpt_multiset->_t_tree);
#endif

    _GET_CONTAINER(t_newiterator) = (multiset_t*)cpt_multiset;
    _GET_MULTISET_CONTAINER_TYPE(t_newiterator) = _MULTISET_CONTAINER;
    _GET_MULTISET_ITERATOR_TYPE(t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

binary_function_t multiset_key_comp(const multiset_t* cpt_multiset)
{
    assert(cpt_multiset != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    return _avl_tree_key_comp(&cpt_multiset->_t_tree);
#else
    return _rb_tree_key_comp(&cpt_multiset->_t_tree);
#endif
}

binary_function_t multiset_value_comp(const multiset_t* cpt_multiset)
{
    return multiset_key_comp(cpt_multiset);
}

void multiset_clear(multiset_t* pt_multiset)
{
    assert(pt_multiset != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    _avl_tree_clear(&pt_multiset->_t_tree);
#else
    _rb_tree_clear(&pt_multiset->_t_tree);
#endif
}

multiset_iterator_t _multiset_find(const multiset_t* cpt_multiset, ...)
{
    multiset_iterator_t t_iter;
    va_list val_elemlist;

    va_start(val_elemlist, cpt_multiset);
    t_iter = _multiset_find_varg(cpt_multiset, val_elemlist);
    va_end(val_elemlist);

    return t_iter;
}

multiset_iterator_t _multiset_find_varg(
    const multiset_t* cpt_multiset, va_list val_elemlist)
{
    multiset_iterator_t t_iter;
    void*               pv_varg = NULL;

    assert(cpt_multiset != NULL);

    pv_varg = allocate(&((multiset_t*)cpt_multiset)->_t_tree._t_allocater,
        _GET_MULTISET_TYPE_SIZE(cpt_multiset), 1);
    assert(pv_varg != NULL);
    _multiset_get_varg_value_auxiliary((multiset_t*)cpt_multiset, val_elemlist, pv_varg);

#ifdef CSTL_MULTISET_AVL_TREE
    t_iter = _avl_tree_find(&cpt_multiset->_t_tree, pv_varg);
#else
    t_iter = _rb_tree_find(&cpt_multiset->_t_tree, pv_varg);
#endif

    _multiset_destroy_varg_value_auxiliary((multiset_t*)cpt_multiset, pv_varg);
    deallocate(&((multiset_t*)cpt_multiset)->_t_tree._t_allocater, pv_varg,
        _GET_MULTISET_TYPE_SIZE(cpt_multiset), 1);

    _GET_CONTAINER(t_iter) = (multiset_t*)cpt_multiset;
    _GET_MULTISET_CONTAINER_TYPE(t_iter) = _MULTISET_CONTAINER;
    _GET_MULTISET_ITERATOR_TYPE(t_iter) = _BIDIRECTIONAL_ITERATOR;

    return t_iter;
}

size_t _multiset_count(const multiset_t* cpt_multiset, ...)
{
    size_t t_count = 0;
    va_list val_elemlist;

    va_start(val_elemlist, cpt_multiset);
    t_count = _multiset_count_varg(cpt_multiset, val_elemlist);
    va_end(val_elemlist);

    return t_count;
}

size_t _multiset_count_varg(const multiset_t* cpt_multiset, va_list val_elemlist)
{
    size_t  t_count = 0;
    void*   pv_varg = NULL;

    assert(cpt_multiset != NULL);

    pv_varg = allocate(&((multiset_t*)cpt_multiset)->_t_tree._t_allocater,
        _GET_MULTISET_TYPE_SIZE(cpt_multiset), 1);
    assert(pv_varg != NULL);
    _multiset_get_varg_value_auxiliary((multiset_t*)cpt_multiset, val_elemlist, pv_varg);

#ifdef CSTL_MULTISET_AVL_TREE
    t_count = _avl_tree_count(&cpt_multiset->_t_tree, pv_varg);
#else
    t_count = _rb_tree_count(&cpt_multiset->_t_tree, pv_varg);
#endif

    _multiset_destroy_varg_value_auxiliary((multiset_t*)cpt_multiset, pv_varg);
    deallocate(&((multiset_t*)cpt_multiset)->_t_tree._t_allocater, pv_varg,
        _GET_MULTISET_TYPE_SIZE(cpt_multiset), 1);

    return t_count;
}

multiset_iterator_t _multiset_lower_bound(const multiset_t* cpt_multiset, ...)
{
    multiset_iterator_t t_iter;
    va_list val_elemlist;

    va_start(val_elemlist, cpt_multiset);
    t_iter = _multiset_lower_bound_varg(cpt_multiset, val_elemlist);
    va_end(val_elemlist);

    return t_iter;
}

multiset_iterator_t _multiset_lower_bound_varg(
    const multiset_t* cpt_multiset, va_list val_elemlist)
{
    multiset_iterator_t t_iter;
    void*               pv_varg = NULL;

    assert(cpt_multiset != NULL);

    pv_varg = allocate(&((multiset_t*)cpt_multiset)->_t_tree._t_allocater,
        _GET_MULTISET_TYPE_SIZE(cpt_multiset), 1);
    assert(pv_varg != NULL);
    _multiset_get_varg_value_auxiliary((multiset_t*)cpt_multiset, val_elemlist, pv_varg);

#ifdef CSTL_MULTISET_AVL_TREE
    t_iter = _avl_tree_lower_bound(&cpt_multiset->_t_tree, pv_varg);
#else
    t_iter = _rb_tree_lower_bound(&cpt_multiset->_t_tree, pv_varg);
#endif

    _multiset_destroy_varg_value_auxiliary((multiset_t*)cpt_multiset, pv_varg);
    deallocate(&((multiset_t*)cpt_multiset)->_t_tree._t_allocater, pv_varg,
        _GET_MULTISET_TYPE_SIZE(cpt_multiset), 1);

    _GET_CONTAINER(t_iter) = (multiset_t*)cpt_multiset;
    _GET_MULTISET_CONTAINER_TYPE(t_iter) = _MULTISET_CONTAINER;
    _GET_MULTISET_ITERATOR_TYPE(t_iter) = _BIDIRECTIONAL_ITERATOR;

    return t_iter;
}

multiset_iterator_t _multiset_upper_bound(const multiset_t* cpt_multiset, ...)
{
    multiset_iterator_t t_iter;
    va_list val_elemlist;

    va_start(val_elemlist, cpt_multiset);
    t_iter = _multiset_upper_bound_varg(cpt_multiset, val_elemlist);
    va_end(val_elemlist);

    return t_iter;
}

multiset_iterator_t _multiset_upper_bound_varg(
    const multiset_t* cpt_multiset, va_list val_elemlist)
{
    multiset_iterator_t t_iter;
    void*               pv_varg = NULL;

    assert(cpt_multiset != NULL);

    pv_varg = allocate(&((multiset_t*)cpt_multiset)->_t_tree._t_allocater,
        _GET_MULTISET_TYPE_SIZE(cpt_multiset), 1);
    assert(pv_varg != NULL);
    _multiset_get_varg_value_auxiliary((multiset_t*)cpt_multiset, val_elemlist, pv_varg);

#ifdef CSTL_MULTISET_AVL_TREE
    t_iter = _avl_tree_upper_bound(&cpt_multiset->_t_tree, pv_varg);
#else
    t_iter = _rb_tree_upper_bound(&cpt_multiset->_t_tree, pv_varg);
#endif

    _multiset_destroy_varg_value_auxiliary((multiset_t*)cpt_multiset, pv_varg);
    deallocate(&((multiset_t*)cpt_multiset)->_t_tree._t_allocater, pv_varg,
        _GET_MULTISET_TYPE_SIZE(cpt_multiset), 1);

    _GET_CONTAINER(t_iter) = (multiset_t*)cpt_multiset;
    _GET_MULTISET_CONTAINER_TYPE(t_iter) = _MULTISET_CONTAINER;
    _GET_MULTISET_ITERATOR_TYPE(t_iter) = _BIDIRECTIONAL_ITERATOR;

    return t_iter;
}

range_t _multiset_equal_range(const multiset_t* cpt_multiset, ...)
{
    range_t t_range;
    va_list val_elemlist;

    va_start(val_elemlist, cpt_multiset);
    t_range = _multiset_equal_range_varg(cpt_multiset, val_elemlist);
    va_end(val_elemlist);

    return t_range;
}

range_t _multiset_equal_range_varg(const multiset_t* cpt_multiset, va_list val_elemlist)
{
    void*   pv_varg = NULL;
    range_t t_range;

    assert(cpt_multiset != NULL);

    pv_varg = allocate(&((multiset_t*)cpt_multiset)->_t_tree._t_allocater,
        _GET_MULTISET_TYPE_SIZE(cpt_multiset), 1);
    assert(pv_varg != NULL);
    _multiset_get_varg_value_auxiliary((multiset_t*)cpt_multiset, val_elemlist, pv_varg);

#ifdef CSTL_MULTISET_AVL_TREE
    t_range = _avl_tree_equal_range(&cpt_multiset->_t_tree, pv_varg);
#else
    t_range = _rb_tree_equal_range(&cpt_multiset->_t_tree, pv_varg);
#endif

    _multiset_destroy_varg_value_auxiliary((multiset_t*)cpt_multiset, pv_varg);
    deallocate(&((multiset_t*)cpt_multiset)->_t_tree._t_allocater, pv_varg,
        _GET_MULTISET_TYPE_SIZE(cpt_multiset), 1);

    _GET_CONTAINER(t_range.it_begin) = (multiset_t*)cpt_multiset;
    _GET_MULTISET_CONTAINER_TYPE(t_range.it_begin) = _MULTISET_CONTAINER;
    _GET_MULTISET_ITERATOR_TYPE(t_range.it_begin) = _BIDIRECTIONAL_ITERATOR;

    _GET_CONTAINER(t_range.it_end) = (multiset_t*)cpt_multiset;
    _GET_MULTISET_CONTAINER_TYPE(t_range.it_end) = _MULTISET_CONTAINER;
    _GET_MULTISET_ITERATOR_TYPE(t_range.it_end) = _BIDIRECTIONAL_ITERATOR;

    return t_range;
}

bool_t multiset_equal(
    const multiset_t* cpt_multisetfirst, const multiset_t* cpt_multisetsecond)
{
    assert(cpt_multisetfirst != NULL && cpt_multisetsecond != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    return _avl_tree_equal(&cpt_multisetfirst->_t_tree, &cpt_multisetsecond->_t_tree);
#else
    return _rb_tree_equal(&cpt_multisetfirst->_t_tree, &cpt_multisetsecond->_t_tree);
#endif
}

bool_t multiset_not_equal(
    const multiset_t* cpt_multisetfirst, const multiset_t* cpt_multisetsecond)
{
    assert(cpt_multisetfirst != NULL && cpt_multisetsecond != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    return _avl_tree_not_equal(&cpt_multisetfirst->_t_tree, &cpt_multisetsecond->_t_tree);
#else
    return _rb_tree_not_equal(&cpt_multisetfirst->_t_tree, &cpt_multisetsecond->_t_tree);
#endif
}

bool_t multiset_less(
    const multiset_t* cpt_multisetfirst, const multiset_t* cpt_multisetsecond)
{
    assert(cpt_multisetfirst != NULL && cpt_multisetsecond != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    return _avl_tree_less(&cpt_multisetfirst->_t_tree, &cpt_multisetsecond->_t_tree);
#else
    return _rb_tree_less(&cpt_multisetfirst->_t_tree, &cpt_multisetsecond->_t_tree);
#endif
}

bool_t multiset_less_equal(
    const multiset_t* cpt_multisetfirst, const multiset_t* cpt_multisetsecond)
{
    assert(cpt_multisetfirst != NULL && cpt_multisetsecond != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    return _avl_tree_less_equal(&cpt_multisetfirst->_t_tree, &cpt_multisetsecond->_t_tree);
#else
    return _rb_tree_less_equal(&cpt_multisetfirst->_t_tree, &cpt_multisetsecond->_t_tree);
#endif
}

bool_t multiset_greater(
    const multiset_t* cpt_multisetfirst, const multiset_t* cpt_multisetsecond)
{
    assert(cpt_multisetfirst != NULL && cpt_multisetsecond != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    return _avl_tree_greater(&cpt_multisetfirst->_t_tree, &cpt_multisetsecond->_t_tree);
#else
    return _rb_tree_greater(&cpt_multisetfirst->_t_tree, &cpt_multisetsecond->_t_tree);
#endif
}

bool_t multiset_greater_equal(
    const multiset_t* cpt_multisetfirst, const multiset_t* cpt_multisetsecond)
{
    assert(cpt_multisetfirst != NULL && cpt_multisetsecond != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    return _avl_tree_greater_equal(&cpt_multisetfirst->_t_tree, &cpt_multisetsecond->_t_tree);
#else
    return _rb_tree_greater_equal(&cpt_multisetfirst->_t_tree, &cpt_multisetsecond->_t_tree);
#endif
}

void multiset_swap(multiset_t* pt_multisetfirst, multiset_t* pt_multisetsecond)
{
    assert(pt_multisetfirst != NULL && pt_multisetsecond != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    _avl_tree_swap(&pt_multisetfirst->_t_tree, &pt_multisetsecond->_t_tree);
#else
    _rb_tree_swap(&pt_multisetfirst->_t_tree, &pt_multisetsecond->_t_tree);
#endif
}

multiset_iterator_t _multiset_insert(multiset_t* pt_multiset, ...)
{
    multiset_iterator_t t_iter;
    va_list val_elemlist;

    va_start(val_elemlist, pt_multiset);
    t_iter = _multiset_insert_varg(pt_multiset, val_elemlist);
    va_end(val_elemlist);

    return t_iter;
}

multiset_iterator_t _multiset_insert_varg(multiset_t* pt_multiset, va_list val_elemlist)
{
    multiset_iterator_t t_iter;
    void*               pv_varg = NULL;

    assert(pt_multiset != NULL);

    pv_varg = allocate(&pt_multiset->_t_tree._t_allocater,
        _GET_MULTISET_TYPE_SIZE(pt_multiset), 1);
    assert(pv_varg != NULL);
    _multiset_get_varg_value_auxiliary(pt_multiset, val_elemlist, pv_varg);

#ifdef CSTL_MULTISET_AVL_TREE
    t_iter = _avl_tree_insert_equal(&pt_multiset->_t_tree, pv_varg);
#else
    t_iter = _rb_tree_insert_equal(&pt_multiset->_t_tree, pv_varg);
#endif

    _multiset_destroy_varg_value_auxiliary(pt_multiset, pv_varg);
    deallocate(&pt_multiset->_t_tree._t_allocater, pv_varg,
        _GET_MULTISET_TYPE_SIZE(pt_multiset), 1);

    _GET_CONTAINER(t_iter) = pt_multiset;
    _GET_MULTISET_CONTAINER_TYPE(t_iter) = _MULTISET_CONTAINER;
    _GET_MULTISET_ITERATOR_TYPE(t_iter) = _BIDIRECTIONAL_ITERATOR;

    return t_iter;
}

multiset_iterator_t _multiset_insert_hint(
    multiset_t* pt_multiset, multiset_iterator_t t_hint, ...)
{
    multiset_iterator_t t_iter;
    va_list val_elemlist;

    va_start(val_elemlist, t_hint);
    t_iter = _multiset_insert_hint_varg(pt_multiset, t_hint, val_elemlist);
    va_end(val_elemlist);

    return t_iter;
}

multiset_iterator_t _multiset_insert_hint_varg(
    multiset_t* pt_multiset, multiset_iterator_t t_hint, va_list val_elemlist)
{
    void*               pv_varg = NULL;

    assert(pt_multiset != NULL);

    pv_varg = allocate(&pt_multiset->_t_tree._t_allocater,
        _GET_MULTISET_TYPE_SIZE(pt_multiset), 1);
    assert(pv_varg != NULL);
    _multiset_get_varg_value_auxiliary(pt_multiset, val_elemlist, pv_varg);

#ifdef CSTL_MULTISET_AVL_TREE
    t_hint = _avl_tree_insert_equal(&pt_multiset->_t_tree, pv_varg);
#else
    t_hint = _rb_tree_insert_equal(&pt_multiset->_t_tree, pv_varg);
#endif

    _multiset_destroy_varg_value_auxiliary(pt_multiset, pv_varg);
    deallocate(&pt_multiset->_t_tree._t_allocater, pv_varg,
        _GET_MULTISET_TYPE_SIZE(pt_multiset), 1);

    _GET_CONTAINER(t_hint) = pt_multiset;
    _GET_MULTISET_CONTAINER_TYPE(t_hint) = _MULTISET_CONTAINER;
    _GET_MULTISET_ITERATOR_TYPE(t_hint) = _BIDIRECTIONAL_ITERATOR;

    return t_hint;
}

void multiset_insert_range(
    multiset_t* pt_multiset, multiset_iterator_t t_begin, multiset_iterator_t t_end)
{
    assert(pt_multiset != NULL);
    assert(_GET_MULTISET_CONTAINER_TYPE(t_begin) == _MULTISET_CONTAINER && 
           _GET_MULTISET_ITERATOR_TYPE(t_begin) == _BIDIRECTIONAL_ITERATOR && 
           _GET_MULTISET_CONTAINER_TYPE(t_end) == _MULTISET_CONTAINER && 
           _GET_MULTISET_ITERATOR_TYPE(t_end) == _BIDIRECTIONAL_ITERATOR);
    assert(_GET_MULTISET_CONTAINER(t_begin) != pt_multiset && 
           _GET_MULTISET_CONTAINER(t_end) != pt_multiset && 
           _GET_MULTISET_CONTAINER(t_begin) == _GET_MULTISET_CONTAINER(t_end));

#ifdef CSTL_MULTISET_AVL_TREE
    _avl_tree_insert_equal_range(&pt_multiset->_t_tree, t_begin, t_end);
#else
    _rb_tree_insert_equal_range(&pt_multiset->_t_tree, t_begin, t_end);
#endif
}

void multiset_erase_pos(multiset_t* pt_multiset, multiset_iterator_t t_pos)
{
    assert(pt_multiset != NULL);
    assert(_GET_MULTISET_CONTAINER_TYPE(t_pos) == _MULTISET_CONTAINER && 
           _GET_MULTISET_ITERATOR_TYPE(t_pos) == _BIDIRECTIONAL_ITERATOR && 
           _GET_MULTISET_CONTAINER(t_pos) == pt_multiset);

#ifdef CSTL_MULTISET_AVL_TREE
    _avl_tree_erase_pos(&pt_multiset->_t_tree, t_pos);
#else
    _rb_tree_erase_pos(&pt_multiset->_t_tree, t_pos);
#endif
}

void multiset_erase_range(
    multiset_t* pt_multiset, multiset_iterator_t t_begin, multiset_iterator_t t_end)
{
    assert(pt_multiset != NULL);
    assert(_GET_MULTISET_CONTAINER_TYPE(t_begin) == _MULTISET_CONTAINER && 
           _GET_MULTISET_ITERATOR_TYPE(t_begin) == _BIDIRECTIONAL_ITERATOR && 
           _GET_MULTISET_CONTAINER_TYPE(t_end) == _MULTISET_CONTAINER && 
           _GET_MULTISET_ITERATOR_TYPE(t_end) == _BIDIRECTIONAL_ITERATOR);
    assert(_GET_MULTISET_CONTAINER(t_begin) == pt_multiset && 
           _GET_MULTISET_CONTAINER(t_end) == pt_multiset);

#ifdef CSTL_MULTISET_AVL_TREE
    _avl_tree_erase_range(&pt_multiset->_t_tree, t_begin, t_end);
#else
    _rb_tree_erase_range(&pt_multiset->_t_tree, t_begin, t_end);
#endif
}

size_t _multiset_erase(multiset_t* pt_multiset, ...)
{
    size_t t_count = 0;
    va_list val_elemlist;

    va_start(val_elemlist, pt_multiset);
    t_count = _multiset_erase_varg(pt_multiset, val_elemlist);
    va_end(val_elemlist);

    return t_count;
}

size_t _multiset_erase_varg(multiset_t* pt_multiset, va_list val_elemlist)
{
    size_t t_count = 0;
    void*  pv_varg = NULL;

    assert(pt_multiset != NULL);

    pv_varg = allocate(&pt_multiset->_t_tree._t_allocater,
        _GET_MULTISET_TYPE_SIZE(pt_multiset), 1);
    assert(pv_varg != NULL);
    _multiset_get_varg_value_auxiliary(pt_multiset, val_elemlist, pv_varg);

#ifdef CSTL_MULTISET_AVL_TREE
    t_count = _avl_tree_erase(&pt_multiset->_t_tree, pv_varg);
#else
    t_count = _rb_tree_erase(&pt_multiset->_t_tree, pv_varg);
#endif

    _multiset_destroy_varg_value_auxiliary(pt_multiset, pv_varg);
    deallocate(&pt_multiset->_t_tree._t_allocater, pv_varg,
        _GET_MULTISET_TYPE_SIZE(pt_multiset), 1);

    return t_count;
}

void _multiset_init_elem_auxiliary(multiset_t* pt_multiset, void* pv_elem)
{
    assert(pt_multiset != NULL && pv_elem != NULL);

    /* initialize new elements */
    if(_GET_MULTISET_TYPE_STYLE(pt_multiset) == _TYPE_CSTL_BUILTIN)
    {
        /* get element type name */
        char s_elemtypename[_TYPE_NAME_SIZE + 1];
        _type_get_elem_typename(_GET_MULTISET_TYPE_NAME(pt_multiset), s_elemtypename);

        _GET_MULTISET_TYPE_INIT_FUNCTION(pt_multiset)(pv_elem, s_elemtypename);
    }
    else
    {
        bool_t t_result = _GET_MULTISET_TYPE_SIZE(pt_multiset);
        _GET_MULTISET_TYPE_INIT_FUNCTION(pt_multiset)(pv_elem, &t_result);
        assert(t_result);
    }
}

/** local function implementation section **/
static void _multiset_get_varg_value_auxiliary(
    multiset_t* pt_multiset, va_list val_elemlist, void* pv_varg)
{
    _multiset_init_elem_auxiliary(pt_multiset, pv_varg);
    _type_get_varg_value(&pt_multiset->_t_tree._t_typeinfo, val_elemlist, pv_varg);
}

static void _multiset_destroy_varg_value_auxiliary(multiset_t* pt_multiset, void* pv_varg)
{
    /* destroy varg value and free memory */
    bool_t t_result = _GET_MULTISET_TYPE_SIZE(pt_multiset);
    _GET_MULTISET_TYPE_DESTROY_FUNCTION(pt_multiset)(pv_varg, &t_result);
    assert(t_result);
}

/** eof **/

