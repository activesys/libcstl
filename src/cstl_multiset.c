/*
 *  The implementation of multiset.
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
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "cstl_alloc.h"
#include "cstl_types.h"
#include "cstl_iterator.h"
#include "cstl_iterator_private.h"

#include "cstl_avl_tree_iterator.h"
#include "cstl_avl_tree_private.h"
#include "cstl_rb_tree_iterator.h"
#include "cstl_rb_tree_private.h"
#include "cutility.h"

#include "cstl_multiset_iterator.h"
#include "cstl_multiset_private.h"
#include "cstl_multiset.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

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
multiset_t _create_multiset(size_t t_typesize, const char* s_typename)
{
    multiset_t t_newmultiset;
    char       ac_multisettypename[_ELEM_TYPE_NAME_SIZE+1];
    char       ac_unifytypename[_ELEM_TYPE_NAME_SIZE+1];

    assert(s_typename != NULL);

    memset(ac_unifytypename, '\0', _ELEM_TYPE_NAME_SIZE+1);
    strncpy(ac_unifytypename, s_typename, _ELEM_TYPE_NAME_SIZE);
    _unify_types(t_typesize, ac_unifytypename);
    
    memset(ac_multisettypename, '\0', _ELEM_TYPE_NAME_SIZE+1);
    strncpy(ac_multisettypename, _MULTISET_IDENTIFY, _ELEM_TYPE_NAME_SIZE);
    strcat(ac_multisettypename, _MULTISET_LEFT_BRACKET);
    strcat(ac_multisettypename, ac_unifytypename);
    strcat(ac_multisettypename, _MULTISET_RIGHT_BRACKET);
  

#ifdef CSTL_MULTISET_AVL_TREE
    *_GET_MULTISET_AVL_TREE(&t_newmultiset) = 
        _create_avl_tree(t_typesize, ac_multisettypename);
#else
    *_GET_MULTISET_RB_TREE(&t_newmultiset) = 
        _create_rb_tree(t_typesize, ac_multisettypename);
#endif

    return t_newmultiset;
}

/* multiset function */
void multiset_init(multiset_t* pt_multiset)
{
    assert(pt_multiset != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    _avl_tree_init(
        _GET_MULTISET_AVL_TREE(pt_multiset), NULL, NULL);
#else
    _rb_tree_init(
        _GET_MULTISET_RB_TREE(pt_multiset), NULL, NULL);
#endif
}

void multiset_destroy(multiset_t* pt_multiset)
{
    assert(pt_multiset != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    _avl_tree_destroy(_GET_MULTISET_AVL_TREE(pt_multiset));
#else
    _rb_tree_destroy(_GET_MULTISET_RB_TREE(pt_multiset));
#endif
}

void multiset_init_copy(multiset_t* pt_multisetdest, const multiset_t* cpt_multisetsrc)
{
    assert(pt_multisetdest != NULL && cpt_multisetsrc != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    _avl_tree_init_copy(
        _GET_MULTISET_AVL_TREE(pt_multisetdest), 
        _GET_MULTISET_AVL_TREE(cpt_multisetsrc));
#else
    _rb_tree_init_copy(
        _GET_MULTISET_RB_TREE(pt_multisetdest), 
        _GET_MULTISET_RB_TREE(cpt_multisetsrc));
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
    _avl_tree_init_copy_range(
        _GET_MULTISET_AVL_TREE(pt_multisetdest), t_begin, t_end);
#else
    _rb_tree_init_copy_range(
        _GET_MULTISET_RB_TREE(pt_multisetdest), t_begin, t_end);
#endif
}

void multiset_init_copy_range_cmp(
    multiset_t* pt_multisetdest, multiset_iterator_t t_begin, multiset_iterator_t t_end,
    int (*pfun_cmp)(const void*, const void*))
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
    _avl_tree_init_copy_range_cmp(
        _GET_MULTISET_AVL_TREE(pt_multisetdest), t_begin, t_end, pfun_cmp);
#else
    _rb_tree_init_copy_range_cmp(
        _GET_MULTISET_RB_TREE(pt_multisetdest), t_begin, t_end, pfun_cmp);
#endif
}

void multiset_assign(multiset_t* pt_multisetdest, const multiset_t* cpt_multisetsrc)
{
    assert(pt_multisetdest != NULL && cpt_multisetsrc != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    _avl_tree_assign(
        _GET_MULTISET_AVL_TREE(pt_multisetdest), 
        _GET_MULTISET_AVL_TREE(cpt_multisetsrc));
#else
    _rb_tree_assign(
        _GET_MULTISET_RB_TREE(pt_multisetdest), 
        _GET_MULTISET_RB_TREE(cpt_multisetsrc));
#endif
}

bool_t multiset_empty(const multiset_t* cpt_multiset)
{
    assert(cpt_multiset != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    return _avl_tree_empty(_GET_MULTISET_AVL_TREE(cpt_multiset));
#else
    return _rb_tree_empty(_GET_MULTISET_RB_TREE(cpt_multiset));
#endif
}

size_t multiset_size(const multiset_t* cpt_multiset)
{
    assert(cpt_multiset != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    return _avl_tree_size(_GET_MULTISET_AVL_TREE(cpt_multiset));
#else
    return _rb_tree_size(_GET_MULTISET_RB_TREE(cpt_multiset));
#endif
}

size_t multiset_max_size(const multiset_t* cpt_multiset)
{
    assert(cpt_multiset != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    return _avl_tree_max_size(_GET_MULTISET_AVL_TREE(cpt_multiset));
#else
    return _rb_tree_max_size(_GET_MULTISET_RB_TREE(cpt_multiset));
#endif
}

multiset_iterator_t multiset_begin(const multiset_t* cpt_multiset)
{
    multiset_iterator_t t_newiterator;

    assert(cpt_multiset != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    t_newiterator = _avl_tree_begin(_GET_MULTISET_AVL_TREE(cpt_multiset));
#else
    t_newiterator = _rb_tree_begin(_GET_MULTISET_RB_TREE(cpt_multiset));
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
    t_newiterator = _avl_tree_end(_GET_MULTISET_AVL_TREE(cpt_multiset));
#else
    t_newiterator = _rb_tree_end(_GET_MULTISET_RB_TREE(cpt_multiset));
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
    t_newiterator = _avl_tree_rbegin(_GET_MULTISET_AVL_TREE(cpt_multiset));
#else
    t_newiterator = _rb_tree_rbegin(_GET_MULTISET_RB_TREE(cpt_multiset));
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
    t_newiterator = _avl_tree_rend(_GET_MULTISET_AVL_TREE(cpt_multiset));
#else
    t_newiterator = _rb_tree_rend(_GET_MULTISET_RB_TREE(cpt_multiset));
#endif

    _GET_CONTAINER(t_newiterator) = (multiset_t*)cpt_multiset;
    _GET_MULTISET_CONTAINER_TYPE(t_newiterator) = _MULTISET_CONTAINER;
    _GET_MULTISET_ITERATOR_TYPE(t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

int (*multiset_key_comp(const multiset_t* cpt_multiset))(const void*, const void*)
{
    assert(cpt_multiset != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    return _avl_tree_key_comp(_GET_MULTISET_AVL_TREE(cpt_multiset));
#else
    return _rb_tree_key_comp(_GET_MULTISET_RB_TREE(cpt_multiset));
#endif
}

int (*multiset_value_comp(const multiset_t* cpt_multiset))(const void*, const void*)
{
    return multiset_key_comp(cpt_multiset);
}

void multiset_clear(multiset_t* pt_multiset)
{
    assert(pt_multiset != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    _avl_tree_clear(_GET_MULTISET_AVL_TREE(pt_multiset));
#else
    _rb_tree_clear(_GET_MULTISET_RB_TREE(pt_multiset));
#endif
}

multiset_iterator_t _multiset_find(const multiset_t* cpt_multiset, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, cpt_multiset);
    return _multiset_find_varg(cpt_multiset, val_elemlist);
}

multiset_iterator_t _multiset_find_varg(
    const multiset_t* cpt_multiset, va_list val_elemlist)
{
    char*               pc_value = NULL;
    size_t              t_typesize = 0;
    multiset_iterator_t t_newiterator;

    assert(cpt_multiset != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    t_typesize = _GET_MULTISET_AVL_TREE(cpt_multiset)->_t_typesize;
    pc_value = (char*)malloc(t_typesize);
    if(pc_value == NULL)
    {
        fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        memset(pc_value, 0x00, t_typesize);
        _get_varg_value(
            pc_value, val_elemlist, t_typesize,
            _GET_MULTISET_AVL_TREE(cpt_multiset)->_sz_typename);
    }

    t_newiterator = _avl_tree_find(_GET_MULTISET_AVL_TREE(cpt_multiset), pc_value);

    free(pc_value);
    pc_value = NULL;
#else
    t_typesize = _GET_MULTISET_RB_TREE(cpt_multiset)->_t_typesize;
    pc_value = (char*)malloc(t_typesize);
    if(pc_value == NULL)
    {
        fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        memset(pc_value, 0x00, t_typesize);
        _get_varg_value(
            pc_value, val_elemlist, t_typesize,
            _GET_MULTISET_RB_TREE(cpt_multiset)->_sz_typename);
    }

    t_newiterator = _rb_tree_find(_GET_MULTISET_RB_TREE(cpt_multiset), pc_value);

    free(pc_value);
    pc_value = NULL;
#endif

    _GET_CONTAINER(t_newiterator) = (multiset_t*)cpt_multiset;
    _GET_MULTISET_CONTAINER_TYPE(t_newiterator) = _MULTISET_CONTAINER;
    _GET_MULTISET_ITERATOR_TYPE(t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

size_t _multiset_count(const multiset_t* cpt_multiset, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, cpt_multiset);
    return _multiset_count_varg(cpt_multiset, val_elemlist);
}

size_t _multiset_count_varg(const multiset_t* cpt_multiset, va_list val_elemlist)
{
    char*   pc_value = NULL;
    size_t  t_typesize = 0;
    size_t  t_count = 0;

    assert(cpt_multiset != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    t_typesize = _GET_MULTISET_AVL_TREE(cpt_multiset)->_t_typesize;
    pc_value = (char*)malloc(t_typesize);
    if(pc_value == NULL)
    {
        fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        memset(pc_value, 0x00, t_typesize);
        _get_varg_value(
            pc_value, val_elemlist, t_typesize,
            _GET_MULTISET_AVL_TREE(cpt_multiset)->_sz_typename);
    }

    t_count = _avl_tree_count(_GET_MULTISET_AVL_TREE(cpt_multiset), pc_value);

    free(pc_value);
    pc_value = NULL;
#else
    t_typesize = _GET_MULTISET_RB_TREE(cpt_multiset)->_t_typesize;
    pc_value = (char*)malloc(t_typesize);
    if(pc_value == NULL)
    {
        fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        memset(pc_value, 0x00, t_typesize);
        _get_varg_value(
            pc_value, val_elemlist, t_typesize,
            _GET_MULTISET_RB_TREE(cpt_multiset)->_sz_typename);
    }

    t_count = _rb_tree_count(_GET_MULTISET_RB_TREE(cpt_multiset), pc_value);

    free(pc_value);
    pc_value = NULL;
#endif

    return t_count;
}

multiset_iterator_t _multiset_lower_bound(const multiset_t* cpt_multiset, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, cpt_multiset);
    return _multiset_lower_bound_varg(cpt_multiset, val_elemlist);
}

multiset_iterator_t _multiset_lower_bound_varg(
    const multiset_t* cpt_multiset, va_list val_elemlist)
{
    char*               pc_value = NULL;
    size_t              t_typesize = 0;
    multiset_iterator_t t_newiterator;

    assert(cpt_multiset != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    t_typesize = _GET_MULTISET_AVL_TREE(cpt_multiset)->_t_typesize;
    pc_value = (char*)malloc(t_typesize);
    if(pc_value == NULL)
    {
        fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        memset(pc_value, 0x00, t_typesize);
        _get_varg_value(
            pc_value, val_elemlist, t_typesize,
            _GET_MULTISET_AVL_TREE(cpt_multiset)->_sz_typename);
    }

    t_newiterator = _avl_tree_lower_bound(_GET_MULTISET_AVL_TREE(cpt_multiset), pc_value);

    free(pc_value);
    pc_value = NULL;
#else
    t_typesize = _GET_MULTISET_RB_TREE(cpt_multiset)->_t_typesize;
    pc_value = (char*)malloc(t_typesize);
    if(pc_value == NULL)
    {
        fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        memset(pc_value, 0x00, t_typesize);
        _get_varg_value(
            pc_value, val_elemlist, t_typesize,
            _GET_MULTISET_RB_TREE(cpt_multiset)->_sz_typename);
    }

    t_newiterator = _rb_tree_lower_bound(_GET_MULTISET_RB_TREE(cpt_multiset), pc_value);

    free(pc_value);
    pc_value = NULL;
#endif

    _GET_CONTAINER(t_newiterator) = (multiset_t*)cpt_multiset;
    _GET_MULTISET_CONTAINER_TYPE(t_newiterator) = _MULTISET_CONTAINER;
    _GET_MULTISET_ITERATOR_TYPE(t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

multiset_iterator_t _multiset_upper_bound(const multiset_t* cpt_multiset, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, cpt_multiset);
    return _multiset_upper_bound_varg(cpt_multiset, val_elemlist);
}

multiset_iterator_t _multiset_upper_bound_varg(
    const multiset_t* cpt_multiset, va_list val_elemlist)
{
    char*               pc_value = NULL;
    size_t              t_typesize = 0;
    multiset_iterator_t t_newiterator;

    assert(cpt_multiset != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    t_typesize = _GET_MULTISET_AVL_TREE(cpt_multiset)->_t_typesize;
    pc_value = (char*)malloc(t_typesize);
    if(pc_value == NULL)
    {
        fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        memset(pc_value, 0x00, t_typesize);
        _get_varg_value(
            pc_value, val_elemlist, t_typesize,
            _GET_MULTISET_AVL_TREE(cpt_multiset)->_sz_typename);
    }

    t_newiterator = _avl_tree_upper_bound(_GET_MULTISET_AVL_TREE(cpt_multiset), pc_value);

    free(pc_value);
    pc_value = NULL;
#else
    t_typesize = _GET_MULTISET_RB_TREE(cpt_multiset)->_t_typesize;
    pc_value = (char*)malloc(t_typesize);
    if(pc_value == NULL)
    {
        fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        memset(pc_value, 0x00, t_typesize);
        _get_varg_value(
            pc_value, val_elemlist, t_typesize,
            _GET_MULTISET_RB_TREE(cpt_multiset)->_sz_typename);
    }

    t_newiterator = _rb_tree_upper_bound(_GET_MULTISET_RB_TREE(cpt_multiset), pc_value);

    free(pc_value);
    pc_value = NULL;
#endif

    _GET_CONTAINER(t_newiterator) = (multiset_t*)cpt_multiset;
    _GET_MULTISET_CONTAINER_TYPE(t_newiterator) = _MULTISET_CONTAINER;
    _GET_MULTISET_ITERATOR_TYPE(t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

pair_t _multiset_equal_range(const multiset_t* cpt_multiset, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, cpt_multiset);
    return _multiset_equal_range_varg(cpt_multiset, val_elemlist);
}

pair_t _multiset_equal_range_varg(const multiset_t* cpt_multiset, va_list val_elemlist)
{
    char*               pc_value = NULL;
    size_t              t_typesize = 0;
    multiset_iterator_t t_firstiterator;
    multiset_iterator_t t_seconditerator;
    pair_t              t_pair;
#ifdef CSTL_MULTISET_AVL_TREE
    avl_tree_result_pair_t t_avlresult;
#else
    rb_tree_result_pair_t  t_rbresult;
#endif

    assert(cpt_multiset != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    t_typesize = _GET_MULTISET_AVL_TREE(cpt_multiset)->_t_typesize;
    pc_value = (char*)malloc(t_typesize);
    if(pc_value == NULL)
    {
        fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        memset(pc_value, 0x00, t_typesize);
        _get_varg_value(
            pc_value, val_elemlist, t_typesize,
            _GET_MULTISET_AVL_TREE(cpt_multiset)->_sz_typename);
    }

    t_avlresult = _avl_tree_equal_range(_GET_MULTISET_AVL_TREE(cpt_multiset), pc_value);
    t_firstiterator = t_avlresult._t_first;
    t_seconditerator = t_avlresult._t_second._t_iterator;

    free(pc_value);
    pc_value = NULL;
#else
    t_typesize = _GET_MULTISET_RB_TREE(cpt_multiset)->_t_typesize;
    pc_value = (char*)malloc(t_typesize);
    if(pc_value == NULL)
    {
        fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        memset(pc_value, 0x00, t_typesize);
        _get_varg_value(
            pc_value, val_elemlist, t_typesize,
            _GET_MULTISET_RB_TREE(cpt_multiset)->_sz_typename);
    }

    t_rbresult = 
        _rb_tree_equal_range(_GET_MULTISET_RB_TREE(cpt_multiset), pc_value);
    t_firstiterator = t_rbresult._t_first;
    t_seconditerator = t_rbresult._t_second._t_iterator;

    free(pc_value);
    pc_value = NULL;
#endif

    _GET_CONTAINER(t_firstiterator) = (multiset_t*)cpt_multiset;
    _GET_MULTISET_CONTAINER_TYPE(t_firstiterator) = _MULTISET_CONTAINER;
    _GET_MULTISET_ITERATOR_TYPE(t_firstiterator) = _BIDIRECTIONAL_ITERATOR;

    _GET_CONTAINER(t_seconditerator) = (multiset_t*)cpt_multiset;
    _GET_MULTISET_CONTAINER_TYPE(t_seconditerator) = _MULTISET_CONTAINER;
    _GET_MULTISET_ITERATOR_TYPE(t_seconditerator) = _BIDIRECTIONAL_ITERATOR;

    t_pair = create_pair(multiset_iterator_t, multiset_iterator_t);
    pair_init(&t_pair);
    memcpy(t_pair.first, &t_firstiterator, t_pair._t_firsttypesize);
    memcpy(t_pair.second, &t_seconditerator, t_pair._t_secondtypesize);

    return t_pair;
}

bool_t multiset_equal(
    const multiset_t* cpt_multisetfirst, const multiset_t* cpt_multisetsecond)
{
    assert(cpt_multisetfirst != NULL && cpt_multisetsecond != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    return _avl_tree_equal(
        _GET_MULTISET_AVL_TREE(cpt_multisetfirst), 
        _GET_MULTISET_AVL_TREE(cpt_multisetsecond));
#else
    return _rb_tree_equal(
        _GET_MULTISET_RB_TREE(cpt_multisetfirst), 
        _GET_MULTISET_RB_TREE(cpt_multisetsecond));
#endif
}

bool_t multiset_not_equal(
    const multiset_t* cpt_multisetfirst, const multiset_t* cpt_multisetsecond)
{
    assert(cpt_multisetfirst != NULL && cpt_multisetsecond != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    return _avl_tree_not_equal(
        _GET_MULTISET_AVL_TREE(cpt_multisetfirst), 
        _GET_MULTISET_AVL_TREE(cpt_multisetsecond));
#else
    return _rb_tree_not_equal(
        _GET_MULTISET_RB_TREE(cpt_multisetfirst), 
        _GET_MULTISET_RB_TREE(cpt_multisetsecond));
#endif
}

bool_t multiset_less(
    const multiset_t* cpt_multisetfirst, const multiset_t* cpt_multisetsecond)
{
    assert(cpt_multisetfirst != NULL && cpt_multisetsecond != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    return _avl_tree_less(
        _GET_MULTISET_AVL_TREE(cpt_multisetfirst), 
        _GET_MULTISET_AVL_TREE(cpt_multisetsecond));
#else
    return _rb_tree_less(
        _GET_MULTISET_RB_TREE(cpt_multisetfirst), 
        _GET_MULTISET_RB_TREE(cpt_multisetsecond));
#endif
}

bool_t multiset_less_equal(
    const multiset_t* cpt_multisetfirst, const multiset_t* cpt_multisetsecond)
{
    assert(cpt_multisetfirst != NULL && cpt_multisetsecond != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    return _avl_tree_less_equal(
        _GET_MULTISET_AVL_TREE(cpt_multisetfirst), 
        _GET_MULTISET_AVL_TREE(cpt_multisetsecond));
#else
    return _rb_tree_less_equal(
        _GET_MULTISET_RB_TREE(cpt_multisetfirst), 
        _GET_MULTISET_RB_TREE(cpt_multisetsecond));
#endif
}

bool_t multiset_great(
    const multiset_t* cpt_multisetfirst, const multiset_t* cpt_multisetsecond)
{
    assert(cpt_multisetfirst != NULL && cpt_multisetsecond != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    return _avl_tree_great(
        _GET_MULTISET_AVL_TREE(cpt_multisetfirst), 
        _GET_MULTISET_AVL_TREE(cpt_multisetsecond));
#else
    return _rb_tree_great(
        _GET_MULTISET_RB_TREE(cpt_multisetfirst), 
        _GET_MULTISET_RB_TREE(cpt_multisetsecond));
#endif
}

bool_t multiset_great_equal(
    const multiset_t* cpt_multisetfirst, const multiset_t* cpt_multisetsecond)
{
    assert(cpt_multisetfirst != NULL && cpt_multisetsecond != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    return _avl_tree_great_equal(
        _GET_MULTISET_AVL_TREE(cpt_multisetfirst), 
        _GET_MULTISET_AVL_TREE(cpt_multisetsecond));
#else
    return _rb_tree_great_equal(
        _GET_MULTISET_RB_TREE(cpt_multisetfirst), 
        _GET_MULTISET_RB_TREE(cpt_multisetsecond));
#endif
}

void multiset_swap(multiset_t* pt_multisetfirst, multiset_t* pt_multisetsecond)
{
    assert(pt_multisetfirst != NULL && pt_multisetsecond != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    _avl_tree_swap(
        _GET_MULTISET_AVL_TREE(pt_multisetfirst), 
        _GET_MULTISET_AVL_TREE(pt_multisetsecond));
#else
    _rb_tree_swap(
        _GET_MULTISET_RB_TREE(pt_multisetfirst), 
        _GET_MULTISET_RB_TREE(pt_multisetsecond));
#endif
}

multiset_iterator_t _multiset_insert(multiset_t* pt_multiset, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, pt_multiset);
    return _multiset_insert_varg(pt_multiset, val_elemlist);
}

multiset_iterator_t _multiset_insert_varg(multiset_t* pt_multiset, va_list val_elemlist)
{
    char*               pc_value = NULL;
    size_t              t_typesize = 0;
    multiset_iterator_t t_iterator;

    assert(pt_multiset != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    t_typesize = _GET_MULTISET_AVL_TREE(pt_multiset)->_t_typesize;
    pc_value = (char*)malloc(t_typesize);
    if(pc_value == NULL)
    {
        fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        memset(pc_value, 0x00, t_typesize);
        _get_varg_value(
            pc_value, val_elemlist, t_typesize,
            _GET_MULTISET_AVL_TREE(pt_multiset)->_sz_typename);
    }

    t_iterator = 
        _avl_tree_insert_equal(_GET_MULTISET_AVL_TREE(pt_multiset), pc_value);

    free(pc_value);
    pc_value = NULL;
#else
    t_typesize = _GET_MULTISET_RB_TREE(pt_multiset)->_t_typesize;
    pc_value = (char*)malloc(t_typesize);
    if(pc_value == NULL)
    {
        fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        memset(pc_value, 0x00, t_typesize);
        _get_varg_value(
            pc_value, val_elemlist, t_typesize,
            _GET_MULTISET_RB_TREE(pt_multiset)->_sz_typename);
    }

    t_iterator = 
        _rb_tree_insert_equal(_GET_MULTISET_RB_TREE(pt_multiset), pc_value);

    free(pc_value);
    pc_value = NULL;
#endif

    _GET_CONTAINER(t_iterator) = pt_multiset;
    _GET_MULTISET_CONTAINER_TYPE(t_iterator) = _MULTISET_CONTAINER;
    _GET_MULTISET_ITERATOR_TYPE(t_iterator) = _BIDIRECTIONAL_ITERATOR;

    return t_iterator;
}

multiset_iterator_t _multiset_insert_hint(
    multiset_t* pt_multiset, multiset_iterator_t t_hint, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_hint);
    return _multiset_insert_hint_varg(pt_multiset, t_hint, val_elemlist);
}

multiset_iterator_t _multiset_insert_hint_varg(
    multiset_t* pt_multiset, multiset_iterator_t t_hint, va_list val_elemlist)
{
    char*   pc_value = NULL;
    size_t  t_typesize = 0;

    assert(pt_multiset != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    t_typesize = _GET_MULTISET_AVL_TREE(pt_multiset)->_t_typesize;
    pc_value = (char*)malloc(t_typesize);
    if(pc_value == NULL)
    {
        fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        memset(pc_value, 0x00, t_typesize);
        _get_varg_value(
            pc_value, val_elemlist, t_typesize,
            _GET_MULTISET_AVL_TREE(pt_multiset)->_sz_typename);
    }

    t_hint = 
        _avl_tree_insert_equal(_GET_MULTISET_AVL_TREE(pt_multiset), pc_value);

    free(pc_value);
    pc_value = NULL;
#else
    t_typesize = _GET_MULTISET_RB_TREE(pt_multiset)->_t_typesize;
    pc_value = (char*)malloc(t_typesize);
    if(pc_value == NULL)
    {
        fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        memset(pc_value, 0x00, t_typesize);
        _get_varg_value(
            pc_value, val_elemlist, t_typesize,
            _GET_MULTISET_RB_TREE(pt_multiset)->_sz_typename);
    }

    t_hint = 
        _rb_tree_insert_equal(_GET_MULTISET_RB_TREE(pt_multiset), pc_value);

    free(pc_value);
    pc_value = NULL;
#endif

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
    _avl_tree_insert_equal_range(_GET_MULTISET_AVL_TREE(pt_multiset), t_begin, t_end);
#else
    _rb_tree_insert_equal_range(_GET_MULTISET_RB_TREE(pt_multiset), t_begin, t_end);
#endif
}

void multiset_erase_pos(multiset_t* pt_multiset, multiset_iterator_t t_pos)
{
    assert(pt_multiset != NULL);
    assert(_GET_MULTISET_CONTAINER_TYPE(t_pos) == _MULTISET_CONTAINER && 
           _GET_MULTISET_ITERATOR_TYPE(t_pos) == _BIDIRECTIONAL_ITERATOR && 
           _GET_MULTISET_CONTAINER(t_pos) == pt_multiset);

#ifdef CSTL_MULTISET_AVL_TREE
    _avl_tree_erase_pos(_GET_MULTISET_AVL_TREE(pt_multiset), t_pos);
#else
    _rb_tree_erase_pos(_GET_MULTISET_RB_TREE(pt_multiset), t_pos);
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
    _avl_tree_erase_range(_GET_MULTISET_AVL_TREE(pt_multiset), t_begin, t_end);
#else
    _rb_tree_erase_range(_GET_MULTISET_RB_TREE(pt_multiset), t_begin, t_end);
#endif
}

size_t _multiset_erase(multiset_t* pt_multiset, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, pt_multiset);
    return _multiset_erase_varg(pt_multiset, val_elemlist);
}

size_t _multiset_erase_varg(multiset_t* pt_multiset, va_list val_elemlist)
{
    char*          pc_value = NULL;
    size_t         t_typesize = 0;
    size_t         t_count = 0;

    assert(pt_multiset != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    t_typesize = _GET_MULTISET_AVL_TREE(pt_multiset)->_t_typesize;
    pc_value = (char*)malloc(t_typesize);
    if(pc_value == NULL)
    {
        fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        memset(pc_value, 0x00, t_typesize);
        _get_varg_value(
            pc_value, val_elemlist, t_typesize,
            _GET_MULTISET_AVL_TREE(pt_multiset)->_sz_typename);
    }

    t_count = _avl_tree_erase(_GET_MULTISET_AVL_TREE(pt_multiset), pc_value);

    free(pc_value);
    pc_value = NULL;
#else
    t_typesize = _GET_MULTISET_RB_TREE(pt_multiset)->_t_typesize;
    pc_value = (char*)malloc(t_typesize);
    if(pc_value == NULL)
    {
        fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        memset(pc_value, 0x00, t_typesize);
        _get_varg_value(
            pc_value, val_elemlist, t_typesize,
            _GET_MULTISET_RB_TREE(pt_multiset)->_sz_typename);
    }

    t_count = _rb_tree_erase(_GET_MULTISET_RB_TREE(pt_multiset), pc_value);

    free(pc_value);
    pc_value = NULL;
#endif

    return t_count;
}

/** local function implementation section **/

/** eof **/

