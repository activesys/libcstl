/*
 *  The implementation of set.
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

#include "cstl_types.h"
#include "cstl_alloc.h"
#include "cstl_iterator.h"

#include "cstl_avl_tree_iterator.h"
#include "cstl_avl_tree_private.h"
#include "cstl_rb_tree_iterator.h"
#include "cstl_rb_tree_private.h"
#include "cutility.h"

#include "cstl_set_iterator.h"
#include "cstl_set_private.h"
#include "cstl_set.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

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

    _GET_SET_CONTAINER_TYPE(&t_newiterator) = _SET_CONTAINER;
    _GET_SET_ITERATOR_TYPE(&t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

void _set_iterator_get_value(
    const struct _tagset* cpt_set, const set_iterator_t* cpt_iterator, void* pv_value)
{
    assert(cpt_set != NULL && cpt_iterator != NULL && pv_value != NULL);
    assert(
        _GET_SET_CONTAINER_TYPE(cpt_iterator) == _SET_CONTAINER && 
        _GET_SET_ITERATOR_TYPE(cpt_iterator) == _BIDIRECTIONAL_ITERATOR && 
        _GET_SET_CONTAINER(cpt_iterator) == cpt_set);

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_iterator_get_value(
        _GET_SET_AVL_TREE(cpt_set), cpt_iterator, pv_value);
#else
    _rb_tree_iterator_get_value(
        _GET_SET_RB_TREE(cpt_set), cpt_iterator, pv_value);
#endif
}

const void* _set_iterator_get_pointer(
    const struct _tagset* cpt_set, const set_iterator_t* cpt_iterator)
{
    assert(cpt_set != NULL && cpt_iterator != NULL);
    assert(
        _GET_SET_CONTAINER_TYPE(cpt_iterator) == _SET_CONTAINER && 
        _GET_SET_ITERATOR_TYPE(cpt_iterator) == _BIDIRECTIONAL_ITERATOR && 
        _GET_SET_CONTAINER(cpt_iterator) == cpt_set);

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_iterator_get_pointer(
        _GET_SET_AVL_TREE(cpt_set), cpt_iterator);
#else
    return _rb_tree_iterator_get_pointer(
        _GET_SET_RB_TREE(cpt_set), cpt_iterator);
#endif
}

void _set_iterator_next(const struct _tagset* cpt_set, set_iterator_t* pt_iterator)
{
    assert(cpt_set != NULL && pt_iterator != NULL);
    assert(
        _GET_SET_CONTAINER_TYPE(pt_iterator) == _SET_CONTAINER && 
        _GET_SET_ITERATOR_TYPE(pt_iterator) == _BIDIRECTIONAL_ITERATOR && 
        _GET_SET_CONTAINER(pt_iterator) == cpt_set);

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_iterator_next(_GET_SET_AVL_TREE(cpt_set), pt_iterator);
#else
    _rb_tree_iterator_next(_GET_SET_RB_TREE(cpt_set), pt_iterator);
#endif
}

void _set_iterator_prev(const struct _tagset* cpt_set, set_iterator_t* pt_iterator)
{
    assert(cpt_set != NULL && pt_iterator != NULL);
    assert(
        _GET_SET_CONTAINER_TYPE(pt_iterator) == _SET_CONTAINER && 
        _GET_SET_ITERATOR_TYPE(pt_iterator) == _BIDIRECTIONAL_ITERATOR && 
        _GET_SET_CONTAINER(pt_iterator) == cpt_set);

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_iterator_prev(_GET_SET_AVL_TREE(cpt_set), pt_iterator);
#else
    _rb_tree_iterator_prev(_GET_SET_RB_TREE(cpt_set), pt_iterator);
#endif
}

bool_t _set_iterator_equal(
    const struct _tagset* cpt_set, const set_iterator_t* cpt_iterator,
    set_iterator_t t_iterator)
{
    assert(cpt_set != NULL && cpt_iterator != NULL);
    assert(
        _GET_SET_CONTAINER_TYPE(cpt_iterator) == _SET_CONTAINER && 
        _GET_SET_ITERATOR_TYPE(cpt_iterator) == _BIDIRECTIONAL_ITERATOR && 
        _GET_SET_CONTAINER_TYPE(&t_iterator) == _SET_CONTAINER && 
        _GET_SET_ITERATOR_TYPE(&t_iterator) == _BIDIRECTIONAL_ITERATOR);
    assert(
        _GET_SET_CONTAINER(cpt_iterator) == cpt_set && 
        _GET_SET_CONTAINER(&t_iterator) == cpt_set);

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_iterator_equal(
        _GET_SET_AVL_TREE(cpt_set), cpt_iterator, t_iterator);
#else
    return _rb_tree_iterator_equal(
        _GET_SET_RB_TREE(cpt_set), cpt_iterator, t_iterator);
#endif
}

int _set_iterator_distance(
    const set_iterator_t* cpt_begin, const set_iterator_t* cpt_end)
{
    assert(cpt_begin != NULL && cpt_end != NULL);
    assert(
        _GET_SET_CONTAINER_TYPE(cpt_begin) == _SET_CONTAINER && 
        _GET_SET_ITERATOR_TYPE(cpt_begin) == _BIDIRECTIONAL_ITERATOR && 
        _GET_SET_CONTAINER_TYPE(cpt_end) == _SET_CONTAINER && 
        _GET_SET_ITERATOR_TYPE(cpt_end) == _BIDIRECTIONAL_ITERATOR &&
        _GET_SET_CONTAINER(cpt_begin) == _GET_SET_CONTAINER(cpt_end));

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_iterator_distance(cpt_begin, cpt_end);
#else
    return _rb_tree_iterator_distance(cpt_begin, cpt_end);
#endif
}

bool_t _set_iterator_before(
    const set_iterator_t* cpt_iteratorfirst, const set_iterator_t* cpt_iteratorsecond)
{
    assert(cpt_iteratorfirst != NULL && cpt_iteratorsecond != NULL);
    assert(
        _GET_SET_CONTAINER_TYPE(cpt_iteratorfirst) == _SET_CONTAINER && 
        _GET_SET_ITERATOR_TYPE(cpt_iteratorfirst) == _BIDIRECTIONAL_ITERATOR && 
        _GET_SET_CONTAINER_TYPE(cpt_iteratorsecond) == _SET_CONTAINER && 
        _GET_SET_ITERATOR_TYPE(cpt_iteratorsecond) == _BIDIRECTIONAL_ITERATOR &&
        _GET_SET_CONTAINER(cpt_iteratorfirst) == _GET_SET_CONTAINER(cpt_iteratorsecond));

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_iterator_before(cpt_iteratorfirst, cpt_iteratorsecond);
#else
    return _rb_tree_iterator_before(cpt_iteratorfirst, cpt_iteratorsecond);
#endif
}

/* set private function */
set_t _create_set(size_t t_typesize, const char* s_typename)
{
    set_t t_newset;
    char  ac_settypename[_ELEM_TYPE_NAME_SIZE+1];
    char  ac_unifytypename[_ELEM_TYPE_NAME_SIZE+1];

    assert(s_typename != NULL);

    memset(ac_unifytypename, '\0', _ELEM_TYPE_NAME_SIZE+1);
    strncpy(ac_unifytypename, s_typename, _ELEM_TYPE_NAME_SIZE);
    _unify_types(t_typesize, ac_unifytypename);
    
    memset(ac_settypename, '\0', _ELEM_TYPE_NAME_SIZE+1);
    strncpy(ac_settypename, _SET_IDENTIFY, _ELEM_TYPE_NAME_SIZE);
    strcat(ac_settypename, _SET_LEFT_BRACKET);
    strcat(ac_settypename, ac_unifytypename);
    strcat(ac_settypename, _SET_RIGHT_BRACKET);
  

#ifdef CSTL_SET_AVL_TREE
    *_GET_SET_AVL_TREE(&t_newset) = _create_avl_tree(t_typesize, ac_settypename);
#else
    *_GET_SET_RB_TREE(&t_newset) = _create_rb_tree(t_typesize, ac_settypename);
#endif

    return t_newset;
}

/* set function */
void set_init(set_t* pt_set)
{
    assert(pt_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_init(_GET_SET_AVL_TREE(pt_set), NULL, NULL);
#else
    _rb_tree_init(_GET_SET_RB_TREE(pt_set), NULL, NULL);
#endif
}

void set_destroy(set_t* pt_set)
{
    assert(pt_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_destroy(_GET_SET_AVL_TREE(pt_set));
#else
    _rb_tree_destroy(_GET_SET_RB_TREE(pt_set));
#endif
}

void set_init_copy(set_t* pt_setdest, const set_t* cpt_setsrc)
{
    assert(pt_setdest != NULL && cpt_setsrc != NULL);

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_init_copy(_GET_SET_AVL_TREE(pt_setdest), _GET_SET_AVL_TREE(cpt_setsrc));
#else
    _rb_tree_init_copy(_GET_SET_RB_TREE(pt_setdest), _GET_SET_RB_TREE(cpt_setsrc));
#endif
}

void set_init_copy_range(set_t* pt_setdest, set_iterator_t t_begin, set_iterator_t t_end)
{
    assert(pt_setdest != NULL);
    assert(
        _GET_SET_CONTAINER_TYPE(&t_begin) == _SET_CONTAINER &&
        _GET_SET_ITERATOR_TYPE(&t_begin) == _BIDIRECTIONAL_ITERATOR &&
        _GET_SET_CONTAINER_TYPE(&t_end) == _SET_CONTAINER &&
        _GET_SET_ITERATOR_TYPE(&t_end) == _BIDIRECTIONAL_ITERATOR);
    assert(
        _GET_SET_CONTAINER(&t_begin) != pt_setdest &&
        _GET_SET_CONTAINER(&t_end) != pt_setdest &&
        _GET_SET_CONTAINER(&t_begin) == _GET_SET_CONTAINER(&t_end));

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_init_copy_range(_GET_SET_AVL_TREE(pt_setdest), t_begin, t_end);
#else
    _rb_tree_init_copy_range(_GET_SET_RB_TREE(pt_setdest), t_begin, t_end);
#endif
}

void set_init_copy_range_cmp(
    set_t* pt_setdest, set_iterator_t t_begin, set_iterator_t t_end,
    int (*pfun_cmp)(const void*, const void*))
{
    assert(pt_setdest != NULL);
    assert(
        _GET_SET_CONTAINER_TYPE(&t_begin) == _SET_CONTAINER &&
        _GET_SET_ITERATOR_TYPE(&t_begin) == _BIDIRECTIONAL_ITERATOR &&
        _GET_SET_CONTAINER_TYPE(&t_end) == _SET_CONTAINER &&
        _GET_SET_ITERATOR_TYPE(&t_end) == _BIDIRECTIONAL_ITERATOR);
    assert(
        _GET_SET_CONTAINER(&t_begin) != pt_setdest &&
        _GET_SET_CONTAINER(&t_end) != pt_setdest &&
        _GET_SET_CONTAINER(&t_begin) == _GET_SET_CONTAINER(&t_end));

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_init_copy_range_cmp(
        _GET_SET_AVL_TREE(pt_setdest), t_begin, t_end, pfun_cmp);
#else
    _rb_tree_init_copy_range_cmp(
        _GET_SET_RB_TREE(pt_setdest), t_begin, t_end, pfun_cmp);
#endif
}

void set_assign(set_t* pt_setdest, const set_t* cpt_setsrc)
{
    assert(pt_setdest != NULL && cpt_setsrc != NULL);

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_assign(_GET_SET_AVL_TREE(pt_setdest), _GET_SET_AVL_TREE(cpt_setsrc));
#else
    _rb_tree_assign(_GET_SET_RB_TREE(pt_setdest), _GET_SET_RB_TREE(cpt_setsrc));
#endif
}

bool_t set_empty(const set_t* cpt_set)
{
    assert(cpt_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_empty(_GET_SET_AVL_TREE(cpt_set));
#else
    return _rb_tree_empty(_GET_SET_RB_TREE(cpt_set));
#endif
}

size_t set_size(const set_t* cpt_set)
{
    assert(cpt_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_size(_GET_SET_AVL_TREE(cpt_set));
#else
    return _rb_tree_size(_GET_SET_RB_TREE(cpt_set));
#endif
}

size_t set_max_size(const set_t* cpt_set)
{
    assert(cpt_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_max_size(_GET_SET_AVL_TREE(cpt_set));
#else
    return _rb_tree_max_size(_GET_SET_RB_TREE(cpt_set));
#endif
}

set_iterator_t set_begin(const set_t* cpt_set)
{
    set_iterator_t t_newiterator;

    assert(cpt_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    t_newiterator = _avl_tree_begin(_GET_SET_AVL_TREE(cpt_set));
#else
    t_newiterator = _rb_tree_begin(_GET_SET_RB_TREE(cpt_set));
#endif

    _GET_CONTAINER(&t_newiterator) = (set_t*)cpt_set;
    _GET_SET_CONTAINER_TYPE(&t_newiterator) = _SET_CONTAINER;
    _GET_SET_ITERATOR_TYPE(&t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

set_iterator_t set_end(const set_t* cpt_set)
{
    set_iterator_t t_newiterator;

    assert(cpt_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    t_newiterator = _avl_tree_end(_GET_SET_AVL_TREE(cpt_set));
#else
    t_newiterator = _rb_tree_end(_GET_SET_RB_TREE(cpt_set));
#endif

    _GET_CONTAINER(&t_newiterator) = (set_t*)cpt_set;
    _GET_SET_CONTAINER_TYPE(&t_newiterator) = _SET_CONTAINER;
    _GET_SET_ITERATOR_TYPE(&t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

set_iterator_t set_rbegin(const set_t* cpt_set)
{
    set_iterator_t t_newiterator;

    assert(cpt_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    t_newiterator = _avl_tree_rbegin(_GET_SET_AVL_TREE(cpt_set));
#else
    t_newiterator = _rb_tree_rbegin(_GET_SET_RB_TREE(cpt_set));
#endif

    _GET_CONTAINER(&t_newiterator) = (set_t*)cpt_set;
    _GET_SET_CONTAINER_TYPE(&t_newiterator) = _SET_CONTAINER;
    _GET_SET_ITERATOR_TYPE(&t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

set_iterator_t set_rend(const set_t* cpt_set)
{
    set_iterator_t t_newiterator;

    assert(cpt_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    t_newiterator = _avl_tree_rend(_GET_SET_AVL_TREE(cpt_set));
#else
    t_newiterator = _rb_tree_rend(_GET_SET_RB_TREE(cpt_set));
#endif

    _GET_CONTAINER(&t_newiterator) = (set_t*)cpt_set;
    _GET_SET_CONTAINER_TYPE(&t_newiterator) = _SET_CONTAINER;
    _GET_SET_ITERATOR_TYPE(&t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

int (*set_key_comp(const set_t* cpt_set))(const void*, const void*)
{
    assert(cpt_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_key_comp(_GET_SET_AVL_TREE(cpt_set));
#else
    return _rb_tree_key_comp(_GET_SET_RB_TREE(cpt_set));
#endif
}

int (*set_value_comp(const set_t* cpt_set))(const void*, const void*)
{
    return set_key_comp(cpt_set);
}

void set_clear(set_t* pt_set)
{
    assert(pt_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_clear(_GET_SET_AVL_TREE(pt_set));
#else
    _rb_tree_clear(_GET_SET_RB_TREE(pt_set));
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
    char*          pc_value = NULL;
    size_t         t_typesize = 0;
    set_iterator_t t_newiterator;

    assert(cpt_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    t_typesize = _GET_SET_AVL_TREE(cpt_set)->_t_typesize;
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
            pc_value, val_elemlist, t_typesize, _GET_SET_AVL_TREE(cpt_set)->_sz_typename);
    }

    t_newiterator = _avl_tree_find(_GET_SET_AVL_TREE(cpt_set), pc_value);

    free(pc_value);
    pc_value = NULL;
#else
    t_typesize = _GET_SET_RB_TREE(cpt_set)->_t_typesize;
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
            pc_value, val_elemlist, t_typesize, _GET_SET_RB_TREE(cpt_set)->_sz_typename);
    }

    t_newiterator = _rb_tree_find(_GET_SET_RB_TREE(cpt_set), pc_value);

    free(pc_value);
    pc_value = NULL;
#endif

    _GET_CONTAINER(&t_newiterator) = (set_t*)cpt_set;
    _GET_SET_CONTAINER_TYPE(&t_newiterator) = _SET_CONTAINER;
    _GET_SET_ITERATOR_TYPE(&t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

size_t _set_count(const set_t* cpt_set, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, cpt_set);
    return _set_count_varg(cpt_set, val_elemlist);
}

size_t _set_count_varg(const set_t* cpt_set, va_list val_elemlist)
{
    char*          pc_value = NULL;
    size_t         t_typesize = 0;
    size_t         t_count = 0;

    assert(cpt_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    t_typesize = _GET_SET_AVL_TREE(cpt_set)->_t_typesize;
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
            pc_value, val_elemlist, t_typesize, _GET_SET_AVL_TREE(cpt_set)->_sz_typename);
    }

    t_count = _avl_tree_count(_GET_SET_AVL_TREE(cpt_set), pc_value);

    free(pc_value);
    pc_value = NULL;
#else
    t_typesize = _GET_SET_RB_TREE(cpt_set)->_t_typesize;
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
            pc_value, val_elemlist, t_typesize, _GET_SET_RB_TREE(cpt_set)->_sz_typename);
    }

    t_count = _rb_tree_count(_GET_SET_RB_TREE(cpt_set), pc_value);

    free(pc_value);
    pc_value = NULL;
#endif

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
    char*          pc_value = NULL;
    size_t         t_typesize = 0;
    set_iterator_t t_newiterator;

    assert(cpt_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    t_typesize = _GET_SET_AVL_TREE(cpt_set)->_t_typesize;
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
            pc_value, val_elemlist, t_typesize, _GET_SET_AVL_TREE(cpt_set)->_sz_typename);
    }

    t_newiterator = _avl_tree_lower_bound(_GET_SET_AVL_TREE(cpt_set), pc_value);

    free(pc_value);
    pc_value = NULL;
#else
    t_typesize = _GET_SET_RB_TREE(cpt_set)->_t_typesize;
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
            pc_value, val_elemlist, t_typesize, _GET_SET_RB_TREE(cpt_set)->_sz_typename);
    }

    t_newiterator = _rb_tree_lower_bound(_GET_SET_RB_TREE(cpt_set), pc_value);

    free(pc_value);
    pc_value = NULL;
#endif

    _GET_CONTAINER(&t_newiterator) = (set_t*)cpt_set;
    _GET_SET_CONTAINER_TYPE(&t_newiterator) = _SET_CONTAINER;
    _GET_SET_ITERATOR_TYPE(&t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

set_iterator_t _set_upper_bound(const set_t* cpt_set, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, cpt_set);
    return _set_upper_bound_varg(cpt_set, val_elemlist);
}

set_iterator_t _set_upper_bound_varg(const set_t* cpt_set, va_list val_elemlist)
{
    char*          pc_value = NULL;
    size_t         t_typesize = 0;
    set_iterator_t t_newiterator;

    assert(cpt_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    t_typesize = _GET_SET_AVL_TREE(cpt_set)->_t_typesize;
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
            pc_value, val_elemlist, t_typesize, _GET_SET_AVL_TREE(cpt_set)->_sz_typename);
    }

    t_newiterator = _avl_tree_upper_bound(_GET_SET_AVL_TREE(cpt_set), pc_value);

    free(pc_value);
    pc_value = NULL;
#else
    t_typesize = _GET_SET_RB_TREE(cpt_set)->_t_typesize;
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
            pc_value, val_elemlist, t_typesize, _GET_SET_RB_TREE(cpt_set)->_sz_typename);
    }

    t_newiterator = _rb_tree_upper_bound(_GET_SET_RB_TREE(cpt_set), pc_value);

    free(pc_value);
    pc_value = NULL;
#endif

    _GET_CONTAINER(&t_newiterator) = (set_t*)cpt_set;
    _GET_SET_CONTAINER_TYPE(&t_newiterator) = _SET_CONTAINER;
    _GET_SET_ITERATOR_TYPE(&t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

pair_t _set_equal_range(const set_t* cpt_set, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, cpt_set);
    return _set_equal_range_varg(cpt_set, val_elemlist);
}

pair_t _set_equal_range_varg(const set_t* cpt_set, va_list val_elemlist)
{
    char*          pc_value = NULL;
    size_t         t_typesize = 0;
    set_iterator_t t_firstiterator;
    set_iterator_t t_seconditerator;
    pair_t         t_pair;
#ifdef CSTL_SET_AVL_TREE
    avl_tree_result_pair_t t_avlresult;
#else
    rb_tree_result_pair_t  t_rbresult;
#endif

    assert(cpt_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    t_typesize = _GET_SET_AVL_TREE(cpt_set)->_t_typesize;
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
            pc_value, val_elemlist, t_typesize, _GET_SET_AVL_TREE(cpt_set)->_sz_typename);
    }

    t_avlresult = _avl_tree_equal_range(_GET_SET_AVL_TREE(cpt_set), pc_value);
    t_firstiterator = t_avlresult._t_first;
    t_seconditerator = t_avlresult._t_second._t_iterator;

    free(pc_value);
    pc_value = NULL;
#else
    t_typesize = _GET_SET_RB_TREE(cpt_set)->_t_typesize;
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
            pc_value, val_elemlist, t_typesize, _GET_SET_RB_TREE(cpt_set)->_sz_typename);
    }

    t_rbresult = _rb_tree_equal_range(_GET_SET_RB_TREE(cpt_set), pc_value);
    t_firstiterator = t_rbresult._t_first;
    t_seconditerator = t_rbresult._t_second._t_iterator;

    free(pc_value);
    pc_value = NULL;
#endif

    _GET_CONTAINER(&t_firstiterator) = (set_t*)cpt_set;
    _GET_SET_CONTAINER_TYPE(&t_firstiterator) = _SET_CONTAINER;
    _GET_SET_ITERATOR_TYPE(&t_firstiterator) = _BIDIRECTIONAL_ITERATOR;

    _GET_CONTAINER(&t_seconditerator) = (set_t*)cpt_set;
    _GET_SET_CONTAINER_TYPE(&t_seconditerator) = _SET_CONTAINER;
    _GET_SET_ITERATOR_TYPE(&t_seconditerator) = _BIDIRECTIONAL_ITERATOR;

    /* create iterator pair */
    t_pair = create_pair(set_iterator_t, set_iterator_t);
    pair_init(&t_pair);
    memcpy(t_pair.first, &t_firstiterator, t_pair._t_firsttypesize);
    memcpy(t_pair.second, &t_seconditerator, t_pair._t_secondtypesize);

    return t_pair;
}

bool_t set_equal(const set_t* cpt_setfirst, const set_t* cpt_setsecond)
{
    assert(cpt_setfirst != NULL && cpt_setsecond != NULL);

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_equal(
        _GET_SET_AVL_TREE(cpt_setfirst), _GET_SET_AVL_TREE(cpt_setsecond));
#else
    return _rb_tree_equal(
        _GET_SET_RB_TREE(cpt_setfirst), _GET_SET_RB_TREE(cpt_setsecond));
#endif
}

bool_t set_not_equal(const set_t* cpt_setfirst, const set_t* cpt_setsecond)
{
    assert(cpt_setfirst != NULL && cpt_setsecond != NULL);

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_not_equal(
        _GET_SET_AVL_TREE(cpt_setfirst), _GET_SET_AVL_TREE(cpt_setsecond));
#else
    return _rb_tree_not_equal(
        _GET_SET_RB_TREE(cpt_setfirst), _GET_SET_RB_TREE(cpt_setsecond));
#endif
}

bool_t set_less(const set_t* cpt_setfirst, const set_t* cpt_setsecond)
{
    assert(cpt_setfirst != NULL && cpt_setsecond != NULL);

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_less(
        _GET_SET_AVL_TREE(cpt_setfirst), _GET_SET_AVL_TREE(cpt_setsecond));
#else
    return _rb_tree_less(
        _GET_SET_RB_TREE(cpt_setfirst), _GET_SET_RB_TREE(cpt_setsecond));
#endif
}

bool_t set_less_equal(const set_t* cpt_setfirst, const set_t* cpt_setsecond)
{
    assert(cpt_setfirst != NULL && cpt_setsecond != NULL);

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_less_equal(
        _GET_SET_AVL_TREE(cpt_setfirst), _GET_SET_AVL_TREE(cpt_setsecond));
#else
    return _rb_tree_less_equal(
        _GET_SET_RB_TREE(cpt_setfirst), _GET_SET_RB_TREE(cpt_setsecond));
#endif
}

bool_t set_great(const set_t* cpt_setfirst, const set_t* cpt_setsecond)
{
    assert(cpt_setfirst != NULL && cpt_setsecond != NULL);

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_great(
        _GET_SET_AVL_TREE(cpt_setfirst), _GET_SET_AVL_TREE(cpt_setsecond));
#else
    return _rb_tree_great(
        _GET_SET_RB_TREE(cpt_setfirst), _GET_SET_RB_TREE(cpt_setsecond));
#endif
}

bool_t set_great_equal(const set_t* cpt_setfirst, const set_t* cpt_setsecond)
{
    assert(cpt_setfirst != NULL && cpt_setsecond != NULL);

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_great_equal(
        _GET_SET_AVL_TREE(cpt_setfirst), _GET_SET_AVL_TREE(cpt_setsecond));
#else
    return _rb_tree_great_equal(
        _GET_SET_RB_TREE(cpt_setfirst), _GET_SET_RB_TREE(cpt_setsecond));
#endif
}

void set_swap(set_t* pt_setfirst, set_t* pt_setsecond)
{
    assert(pt_setfirst != NULL && pt_setsecond != NULL);

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_swap(_GET_SET_AVL_TREE(pt_setfirst), _GET_SET_AVL_TREE(pt_setsecond));
#else
    _rb_tree_swap(_GET_SET_RB_TREE(pt_setfirst), _GET_SET_RB_TREE(pt_setsecond));
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
    char*          pc_value = NULL;
    size_t         t_typesize = 0;
    set_iterator_t t_result;
#ifdef CSTL_SET_AVL_TREE
    avl_tree_result_pair_t t_avlresult;
#else
    rb_tree_result_pair_t  t_rbresult;
#endif

    assert(pt_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    t_typesize = _GET_SET_AVL_TREE(pt_set)->_t_typesize;
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
            pc_value, val_elemlist, t_typesize, _GET_SET_AVL_TREE(pt_set)->_sz_typename);
    }

    t_avlresult = _avl_tree_insert_unique(_GET_SET_AVL_TREE(pt_set), pc_value);
    if(t_avlresult._t_second._t_bool)
    {
        t_result = t_avlresult._t_first;
    }
    else
    {
        t_result = set_end(pt_set);
    }

    free(pc_value);
    pc_value = NULL;
#else
    t_typesize = _GET_SET_RB_TREE(pt_set)->_t_typesize;
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
            pc_value, val_elemlist, t_typesize, _GET_SET_RB_TREE(pt_set)->_sz_typename);
    }

    t_rbresult = _rb_tree_insert_unique(_GET_SET_RB_TREE(pt_set), pc_value);
    if(t_rbresult._t_second._t_bool)
    {
        t_result = t_rbresult._t_first;
    }
    else
    {
        t_result = set_end(pt_set);
    }

    free(pc_value);
    pc_value = NULL;
#endif

    _GET_CONTAINER(&t_result) = pt_set;
    _GET_SET_CONTAINER_TYPE(&t_result) = _SET_CONTAINER;
    _GET_SET_ITERATOR_TYPE(&t_result) = _BIDIRECTIONAL_ITERATOR;

    return t_result;
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
    char*   pc_value = NULL;
    size_t  t_typesize = 0;
#ifdef CSTL_SET_AVL_TREE
    avl_tree_result_pair_t t_avlresult;
#else
    rb_tree_result_pair_t  t_rbresult;
#endif

    assert(pt_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    t_typesize = _GET_SET_AVL_TREE(pt_set)->_t_typesize;
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
            pc_value, val_elemlist, t_typesize, _GET_SET_AVL_TREE(pt_set)->_sz_typename);
    }

    t_avlresult = _avl_tree_insert_unique(_GET_SET_AVL_TREE(pt_set), pc_value);
    t_hint = t_avlresult._t_first;

    free(pc_value);
    pc_value = NULL;
#else
    t_typesize = _GET_SET_RB_TREE(pt_set)->_t_typesize;
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
            pc_value, val_elemlist, t_typesize, _GET_SET_RB_TREE(pt_set)->_sz_typename);
    }

    t_rbresult = _rb_tree_insert_unique(_GET_SET_RB_TREE(pt_set), pc_value);
    t_hint = t_rbresult._t_first;

    free(pc_value);
    pc_value = NULL;
#endif

    _GET_CONTAINER(&t_hint) = pt_set;
    _GET_SET_CONTAINER_TYPE(&t_hint) = _SET_CONTAINER;
    _GET_SET_ITERATOR_TYPE(&t_hint) = _BIDIRECTIONAL_ITERATOR;

    return t_hint;
}

void set_insert_range(set_t* pt_set, set_iterator_t t_begin, set_iterator_t t_end)
{
    assert(pt_set != NULL);
    assert(
        _GET_SET_CONTAINER_TYPE(&t_begin) == _SET_CONTAINER && 
        _GET_SET_ITERATOR_TYPE(&t_begin) == _BIDIRECTIONAL_ITERATOR && 
        _GET_SET_CONTAINER_TYPE(&t_end) == _SET_CONTAINER && 
        _GET_SET_ITERATOR_TYPE(&t_end) == _BIDIRECTIONAL_ITERATOR);
    assert(
        _GET_SET_CONTAINER(&t_begin) != pt_set && 
        _GET_SET_CONTAINER(&t_end) != pt_set && 
        _GET_SET_CONTAINER(&t_begin) == _GET_SET_CONTAINER(&t_end));

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_insert_unique_range(_GET_SET_AVL_TREE(pt_set), t_begin, t_end);
#else
    _rb_tree_insert_unique_range(_GET_SET_RB_TREE(pt_set), t_begin, t_end);
#endif
}

void set_erase_pos(set_t* pt_set, set_iterator_t t_pos)
{
    assert(pt_set != NULL);
    assert(
        _GET_SET_CONTAINER_TYPE(&t_pos) == _SET_CONTAINER && 
        _GET_SET_ITERATOR_TYPE(&t_pos) == _BIDIRECTIONAL_ITERATOR && 
        _GET_SET_CONTAINER(&t_pos) == pt_set);

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_erase_pos(_GET_SET_AVL_TREE(pt_set), t_pos);
#else
    _rb_tree_erase_pos(_GET_SET_RB_TREE(pt_set), t_pos);
#endif
}

void set_erase_range(set_t* pt_set, set_iterator_t t_begin, set_iterator_t t_end)
{
    assert(pt_set != NULL);
    assert(
        _GET_SET_CONTAINER_TYPE(&t_begin) == _SET_CONTAINER && 
        _GET_SET_ITERATOR_TYPE(&t_begin) == _BIDIRECTIONAL_ITERATOR && 
        _GET_SET_CONTAINER_TYPE(&t_end) == _SET_CONTAINER && 
        _GET_SET_ITERATOR_TYPE(&t_end) == _BIDIRECTIONAL_ITERATOR);
    assert(
        _GET_SET_CONTAINER(&t_begin) == pt_set && 
        _GET_SET_CONTAINER(&t_end) == pt_set);

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_erase_range(_GET_SET_AVL_TREE(pt_set), t_begin, t_end);
#else
    _rb_tree_erase_range(_GET_SET_RB_TREE(pt_set), t_begin, t_end);
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
    char*          pc_value = NULL;
    size_t         t_typesize = 0;
    size_t         t_count = 0;

    assert(pt_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    t_typesize = _GET_SET_AVL_TREE(pt_set)->_t_typesize;
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
            pc_value, val_elemlist, t_typesize, _GET_SET_AVL_TREE(pt_set)->_sz_typename);
    }

    t_count = _avl_tree_erase(_GET_SET_AVL_TREE(pt_set), pc_value);

    free(pc_value);
    pc_value = NULL;
#else
    t_typesize = _GET_SET_RB_TREE(pt_set)->_t_typesize;
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
            pc_value, val_elemlist, t_typesize, _GET_SET_RB_TREE(pt_set)->_sz_typename);
    }

    t_count = _rb_tree_erase(_GET_SET_RB_TREE(pt_set), pc_value);

    free(pc_value);
    pc_value = NULL;
#endif

    return t_count;
}

/** local function implementation section **/

/** eof **/

