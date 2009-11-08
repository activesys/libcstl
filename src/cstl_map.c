/*
 *  The implementation of map.
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

#ifdef CSTL_MAP_AVL_TREE
#include "cstl_avl_tree_iterator.h"
#include "cstl_avl_tree_private.h"
#else
#include "cstl_rb_tree_iterator.h"
#include "cstl_rb_tree_private.h"
#endif
#include "cutility.h"
#include "cstring.h"

#include "cstl_map_iterator.h"
#include "cstl_map_private.h"
#include "cstl_map.h"

/** local constant declaration and local macro section **/
/* macros for type informations */
#define _GET_MAP_FIRST_TYPE_SIZE(pt_map)\
    ((pt_map)->_t_pair._t_typeinfofirst._pt_type->_t_typesize)
#define _GET_MAP_FIRST_TYPE_NAME(pt_map)\
    ((pt_map)->_t_pair._t_typeinfofirst._sz_typename)
#define _GET_MAP_FIRST_TYPE_BASENAME(pt_map)\
    ((pt_map)->_t_pair._t_typeinfofirst._pt_type->_sz_typename)
#define _GET_MAP_FIRST_TYPE_INIT_FUNCTION(pt_map)\
    ((pt_map)->_t_pair._t_typeinfofirst._pt_type->_t_typeinit)
#define _GET_MAP_FIRST_TYPE_COPY_FUNCTION(pt_map)\
    ((pt_map)->_t_pair._t_typeinfofirst._pt_type->_t_typecopy)
#define _GET_MAP_FIRST_TYPE_LESS_FUNCTION(pt_map)\
    ((pt_map)->_t_pair._t_typeinfofirst._pt_type->_t_typeless)
#define _GET_MAP_FIRST_TYPE_DESTROY_FUNCTION(pt_map)\
    ((pt_map)->_t_pair._t_typeinfofirst._pt_type->_t_typedestroy)
#define _GET_MAP_FIRST_TYPE_STYLE(pt_map)\
    ((pt_map)->_t_pair._t_typeinfofirst._t_style)

#define _GET_MAP_SECOND_TYPE_SIZE(pt_map)\
    ((pt_map)->_t_pair._t_typeinfosecond._pt_type->_t_typesize)
#define _GET_MAP_SECOND_TYPE_NAME(pt_map)\
    ((pt_map)->_t_pair._t_typeinfosecond._sz_typename)
#define _GET_MAP_SECOND_TYPE_BASENAME(pt_map)\
    ((pt_map)->_t_pair._t_typeinfosecond._pt_type->_sz_typename)
#define _GET_MAP_SECOND_TYPE_INIT_FUNCTION(pt_map)\
    ((pt_map)->_t_pair._t_typeinfosecond._pt_type->_t_typeinit)
#define _GET_MAP_SECOND_TYPE_COPY_FUNCTION(pt_map)\
    ((pt_map)->_t_pair._t_typeinfosecond._pt_type->_t_typecopy)
#define _GET_MAP_SECOND_TYPE_LESS_FUNCTION(pt_map)\
    ((pt_map)->_t_pair._t_typeinfosecond._pt_type->_t_typeless)
#define _GET_MAP_SECOND_TYPE_DESTROY_FUNCTION(pt_map)\
    ((pt_map)->_t_pair._t_typeinfosecond._pt_type->_t_typedestroy)
#define _GET_MAP_SECOND_TYPE_STYLE(pt_map)\
    ((pt_map)->_t_pair._t_typeinfosecond._t_style)

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/
#ifndef NDEBUG
/*
 * Test the two pair is have the same type.
 */
static bool_t _map_same_pair_type(const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond);
#endif /* NDEBUG */

/*
 * map key less and value less
 */
static void _map_key_less(const void* cpv_first, const void* cpv_second, void* pv_output);
static void _map_value_less(const void* cpv_first, const void* cpv_second, void* pv_output);

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/* map iterator function */
map_iterator_t create_map_iterator(void)
{
    map_iterator_t t_newiterator;

#ifdef CSTL_MAP_AVL_TREE
    t_newiterator = _create_avl_tree_iterator();
#else
    t_newiterator = _create_rb_tree_iterator();
#endif

    _GET_MAP_CONTAINER_TYPE(t_newiterator) = _MAP_CONTAINER;
    _GET_MAP_ITERATOR_TYPE(t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

void _map_iterator_get_value(map_iterator_t t_iter, void* pv_value)
{
    assert(pv_value != NULL);
    assert(_GET_MAP_CONTAINER_TYPE(t_iter) == _MAP_CONTAINER &&
           _GET_MAP_ITERATOR_TYPE(t_iter) == _BIDIRECTIONAL_ITERATOR);

#ifdef CSTL_MAP_AVL_TREE
    _avl_tree_iterator_get_value(t_iter, pv_value);
#else
    _rb_tree_iterator_get_value(t_iter, pv_value);
#endif
}

const void* _map_iterator_get_pointer(map_iterator_t t_iter)
{
    assert(_GET_MAP_CONTAINER_TYPE(t_iter) == _MAP_CONTAINER &&
           _GET_MAP_ITERATOR_TYPE(t_iter) == _BIDIRECTIONAL_ITERATOR);

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_iterator_get_pointer(t_iter);
#else
    return _rb_tree_iterator_get_pointer(t_iter);
#endif
}

map_iterator_t _map_iterator_next(map_iterator_t t_iter)
{
    assert(_GET_MAP_CONTAINER_TYPE(t_iter) == _MAP_CONTAINER &&
           _GET_MAP_ITERATOR_TYPE(t_iter) == _BIDIRECTIONAL_ITERATOR);

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_iterator_next(t_iter);
#else
    return _rb_tree_iterator_next(t_iter);
#endif
}

map_iterator_t _map_iterator_prev(map_iterator_t t_iter)
{
    assert(_GET_MAP_CONTAINER_TYPE(t_iter) == _MAP_CONTAINER &&
           _GET_MAP_ITERATOR_TYPE(t_iter) == _BIDIRECTIONAL_ITERATOR);

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_iterator_prev(t_iter);
#else
    return _rb_tree_iterator_prev(t_iter);
#endif
}

bool_t _map_iterator_equal(
    map_iterator_t t_iterfirst, map_iterator_t t_itersecond)
{
    assert(_GET_MAP_CONTAINER_TYPE(t_iterfirst) == _MAP_CONTAINER &&
           _GET_MAP_ITERATOR_TYPE(t_iterfirst) == _BIDIRECTIONAL_ITERATOR &&
           _GET_MAP_CONTAINER_TYPE(t_itersecond) == _MAP_CONTAINER &&
           _GET_MAP_ITERATOR_TYPE(t_itersecond) == _BIDIRECTIONAL_ITERATOR);

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_iterator_equal(t_iterfirst, t_itersecond);
#else
    return _rb_tree_iterator_equal(t_iterfirst, t_itersecond);
#endif
}

int _map_iterator_distance(
    map_iterator_t t_iterfirst, map_iterator_t t_itersecond)
{
    assert(_GET_MAP_CONTAINER_TYPE(t_iterfirst) == _MAP_CONTAINER &&
           _GET_MAP_ITERATOR_TYPE(t_iterfirst) == _BIDIRECTIONAL_ITERATOR &&
           _GET_MAP_CONTAINER_TYPE(t_itersecond) == _MAP_CONTAINER &&
           _GET_MAP_ITERATOR_TYPE(t_itersecond) == _BIDIRECTIONAL_ITERATOR &&
           _GET_MAP_CONTAINER(t_iterfirst) == _GET_MAP_CONTAINER(t_itersecond));

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_iterator_distance(t_iterfirst, t_itersecond);
#else
    return _rb_tree_iterator_distance(t_iterfirst, t_itersecond);
#endif
}

bool_t _map_iterator_before(
    map_iterator_t t_iterfirst, map_iterator_t t_itersecond)
{
    assert(_GET_MAP_CONTAINER_TYPE(t_iterfirst) == _MAP_CONTAINER &&
           _GET_MAP_ITERATOR_TYPE(t_iterfirst) == _BIDIRECTIONAL_ITERATOR &&
           _GET_MAP_CONTAINER_TYPE(t_itersecond) == _MAP_CONTAINER &&
           _GET_MAP_ITERATOR_TYPE(t_itersecond) == _BIDIRECTIONAL_ITERATOR &&
           _GET_MAP_CONTAINER(t_iterfirst) == _GET_MAP_CONTAINER(t_itersecond));

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_iterator_before(t_iterfirst, t_itersecond);
#else
    return _rb_tree_iterator_before(t_iterfirst, t_itersecond);
#endif
}

/* map private function */
map_t* _create_map(const char* s_typename)
{
    map_t* pt_newmap = NULL;

    if((pt_newmap = (map_t*)malloc(sizeof(map_t))) == NULL)
    {
        return NULL;
    }

    if(!_create_map_auxiliary(pt_newmap, s_typename))
    {
        free(pt_newmap);
        return NULL;
    }

    return pt_newmap;
}

bool_t _create_map_auxiliary(map_t* pt_map, const char* s_typename)
{
    char   s_typenameex[_TYPE_NAME_SIZE + 1];
    bool_t t_result = false;

    assert(pt_map != NULL && s_typename != NULL);

    t_result = _create_pair_auxiliary(&pt_map->_t_pair, s_typename);
    if(!t_result)
    {
        return false;
    }

    memset(s_typenameex, '\0', _TYPE_NAME_SIZE + 1);
    strncpy(s_typenameex, "pair_t", _TYPE_NAME_SIZE);
    strncat(s_typenameex, "<", _TYPE_NAME_SIZE);
    strncat(s_typenameex, s_typename, _TYPE_NAME_SIZE - 8); /* 8 is length of "pair_t<>" */
    strncat(s_typenameex, ">", _TYPE_NAME_SIZE);

#ifdef CSTL_MAP_AVL_TREE
    t_result = _create_avl_tree_auxiliary(&pt_map->_t_tree, s_typenameex);
#else
    t_result = _create_rb_tree_auxiliary(&pt_map->_t_tree, s_typenameex);
#endif

    return t_result;
}

void _map_destroy_auxiliary(map_t* pt_map)
{
    assert(pt_map != NULL);

    _pair_destroy_auxiliary(&pt_map->_t_pair);
#ifdef CSTL_MAP_AVL_TREE
    _avl_tree_destroy_auxiliary(&pt_map->_t_tree);
#else
    _rb_tree_destroy_auxiliary(&pt_map->_t_tree);
#endif
}

/* map function */
void map_init(map_t* pt_map)
{
    assert(pt_map != NULL);

    /* initialize the pair */
    pair_init(&pt_map->_t_pair);
    /* initialize the tree */
#ifdef CSTL_MAP_AVL_TREE
    _avl_tree_init(&pt_map->_t_tree, _map_key_less);
#else
    _rb_tree_init(&pt_map->_t_tree, _map_key_less);
#endif
}

void map_init_ex(map_t* pt_map, binary_function_t t_key_less)
{
    binary_function_t t_less = NULL;

    assert(pt_map != NULL);

    t_less = t_key_less != NULL ? t_key_less : _map_key_less;

    pair_init(&pt_map->_t_pair);
#ifdef CSTL_MAP_AVL_TREE
    _avl_tree_init(&pt_map->_t_tree, t_less);
#else
    _rb_tree_init(&pt_map->_t_tree, t_less);
#endif
}

void map_destroy(map_t* pt_map)
{
    _map_destroy_auxiliary(pt_map);
    free(pt_map);
}

void map_init_copy(map_t* pt_mapdest, const map_t* cpt_mapsrc)
{
    assert(pt_mapdest != NULL && cpt_mapsrc != NULL);
    assert(_map_same_pair_type(&pt_mapdest->_t_pair, &cpt_mapsrc->_t_pair));

    /* initialize dest map with src map attribute */
    map_init(pt_mapdest);
    /* insert all element from src to dest */
    if(!map_empty(cpt_mapsrc))
    {
        map_insert_range(pt_mapdest, map_begin(cpt_mapsrc), map_end(cpt_mapsrc));
    }
}

void map_init_copy_range(map_t* pt_mapdest, map_iterator_t t_begin, map_iterator_t t_end)
{
    assert(pt_mapdest != NULL);
    assert(_GET_MAP_CONTAINER_TYPE(t_begin) == _MAP_CONTAINER &&
           _GET_MAP_ITERATOR_TYPE(t_begin) == _BIDIRECTIONAL_ITERATOR &&
           _GET_MAP_CONTAINER_TYPE(t_end) == _MAP_CONTAINER &&
           _GET_MAP_ITERATOR_TYPE(t_end) == _BIDIRECTIONAL_ITERATOR);
    assert(_GET_MAP_CONTAINER(t_begin) != pt_mapdest &&
           _GET_MAP_CONTAINER(t_end) != pt_mapdest &&
           _GET_MAP_CONTAINER(t_begin) == _GET_MAP_CONTAINER(t_end));

    /* initialize dest map with src map attribute */
    map_init(pt_mapdest);
    /* insert all element from src to dest */
    if(!map_empty(_GET_MAP_CONTAINER(t_begin)))
    {
        map_insert_range(pt_mapdest, t_begin, t_end);
    }
}

void map_init_copy_range_ex(map_t* pt_mapdest,
    map_iterator_t t_begin, map_iterator_t t_end, binary_function_t t_key_less)
{
    assert(pt_mapdest != NULL);
    assert(_GET_MAP_CONTAINER_TYPE(t_begin) == _MAP_CONTAINER &&
           _GET_MAP_ITERATOR_TYPE(t_begin) == _BIDIRECTIONAL_ITERATOR &&
           _GET_MAP_CONTAINER_TYPE(t_end) == _MAP_CONTAINER &&
           _GET_MAP_ITERATOR_TYPE(t_end) == _BIDIRECTIONAL_ITERATOR);
    assert(_GET_MAP_CONTAINER(t_begin) != pt_mapdest &&
           _GET_MAP_CONTAINER(t_end) != pt_mapdest &&
           _GET_MAP_CONTAINER(t_begin) == _GET_MAP_CONTAINER(t_end));

    /* initialize dest map with src map attribute */
    map_init_ex(pt_mapdest, t_key_less);
    /* insert all element from src to dest */
    if(!map_empty(_GET_MAP_CONTAINER(t_begin)))
    {
        map_insert_range(pt_mapdest, t_begin, t_end);
    }
}

void map_assign(map_t* pt_mapdest, const map_t* cpt_mapsrc)
{
    assert(pt_mapdest != NULL && cpt_mapsrc != NULL);
    assert(_map_same_pair_type(&pt_mapdest->_t_pair, &cpt_mapsrc->_t_pair));

    /* clear */
    map_clear(pt_mapdest);
    /* insert all element from src to dest */
    if(!map_empty(cpt_mapsrc))
    {
        map_insert_range(pt_mapdest, map_begin(cpt_mapsrc), map_end(cpt_mapsrc));
    }
}

void map_swap(map_t* pt_mapfirst, map_t* pt_mapsecond)
{
    assert(pt_mapfirst != NULL && pt_mapsecond != NULL);
    assert(_map_same_pair_type(&pt_mapfirst->_t_pair, &pt_mapsecond->_t_pair));

#ifdef CSTL_MAP_AVL_TREE
    _avl_tree_swap(&pt_mapfirst->_t_tree, &pt_mapsecond->_t_tree);
#else
    _rb_tree_swap(&pt_mapfirst->_t_tree, &pt_mapsecond->_t_tree);
#endif
}

bool_t map_empty(const map_t* cpt_map)
{
    assert(cpt_map != NULL);

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_empty(&cpt_map->_t_tree);
#else
    return _rb_tree_empty(&cpt_map->_t_tree);
#endif
}

size_t map_size(const map_t* cpt_map)
{
    assert(cpt_map != NULL);

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_size(&cpt_map->_t_tree);
#else
    return _rb_tree_size(&cpt_map->_t_tree);
#endif
}

size_t map_max_size(const map_t* cpt_map)
{
    assert(cpt_map != NULL);

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_max_size(&cpt_map->_t_tree);
#else
    return _rb_tree_max_size(&cpt_map->_t_tree);
#endif
}

binary_function_t map_key_less(const map_t* cpt_map)
{
    assert(cpt_map != NULL);

    return cpt_map->_t_tree._t_less;
}

binary_function_t map_value_less(const map_t* cpt_map)
{
#ifdef NDEBUG
    map_t* pt_avoidwarning = NULL;
    pt_avoidwarning = (map_t*)cpt_map;
#endif
    assert(cpt_map != NULL);

    return _map_value_less;
}

void map_clear(map_t* pt_map)
{
    assert(pt_map != NULL);

#ifdef CSTL_MAP_AVL_TREE
    _avl_tree_clear(&pt_map->_t_tree);
#else
    _rb_tree_clear(&pt_map->_t_tree);
#endif
}

bool_t map_equal(const map_t* cpt_mapfirst, const map_t* cpt_mapsecond)
{
    assert(cpt_mapfirst != NULL && cpt_mapsecond != NULL);

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_equal(&cpt_mapfirst->_t_tree, &cpt_mapsecond->_t_tree);
#else
    return _rb_tree_equal(&cpt_mapfirst->_t_tree, &cpt_mapsecond->_t_tree);
#endif
}

bool_t map_not_equal(const map_t* cpt_mapfirst, const map_t* cpt_mapsecond)
{
    assert(cpt_mapfirst != NULL && cpt_mapsecond != NULL);

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_not_equal(&cpt_mapfirst->_t_tree, &cpt_mapsecond->_t_tree);
#else
    return _rb_tree_not_equal(&cpt_mapfirst->_t_tree, &cpt_mapsecond->_t_tree);
#endif
}

bool_t map_less(const map_t* cpt_mapfirst, const map_t* cpt_mapsecond)
{
    assert(cpt_mapfirst != NULL && cpt_mapsecond != NULL);
    assert(_map_same_pair_type(&cpt_mapfirst->_t_pair, &cpt_mapsecond->_t_pair));

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_less(&cpt_mapfirst->_t_tree, &cpt_mapsecond->_t_tree);
#else
    return _rb_tree_less(&cpt_mapfirst->_t_tree, &cpt_mapsecond->_t_tree);
#endif
}

bool_t map_less_equal(const map_t* cpt_mapfirst, const map_t* cpt_mapsecond)
{
    assert(cpt_mapfirst != NULL && cpt_mapsecond != NULL);
    assert(_map_same_pair_type(&cpt_mapfirst->_t_pair, &cpt_mapsecond->_t_pair));

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_less_equal(&cpt_mapfirst->_t_tree, &cpt_mapsecond->_t_tree);
#else
    return _rb_tree_less_equal(&cpt_mapfirst->_t_tree, &cpt_mapsecond->_t_tree);
#endif
}

bool_t map_great(const map_t* cpt_mapfirst, const map_t* cpt_mapsecond)
{
    assert(cpt_mapfirst != NULL && cpt_mapsecond != NULL);
    assert(_map_same_pair_type(&cpt_mapfirst->_t_pair, &cpt_mapsecond->_t_pair));

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_great(&cpt_mapfirst->_t_tree, &cpt_mapsecond->_t_tree);
#else
    return _rb_tree_great(&cpt_mapfirst->_t_tree, &cpt_mapsecond->_t_tree);
#endif
}

bool_t map_great_equal(const map_t* cpt_mapfirst, const map_t* cpt_mapsecond)
{
    assert(cpt_mapfirst != NULL && cpt_mapsecond != NULL);
    assert(_map_same_pair_type(&cpt_mapfirst->_t_pair, &cpt_mapsecond->_t_pair));

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_great_equal(&cpt_mapfirst->_t_tree, &cpt_mapsecond->_t_tree);
#else
    return _rb_tree_great_equal(&cpt_mapfirst->_t_tree, &cpt_mapsecond->_t_tree);
#endif
}

map_iterator_t map_begin(const map_t* cpt_map)
{
    map_iterator_t t_newiterator;

    assert(cpt_map != NULL);

#ifdef CSTL_MAP_AVL_TREE
    t_newiterator = _avl_tree_begin(&cpt_map->_t_tree);
#else
    t_newiterator = _rb_tree_begin(&cpt_map->_t_tree);
#endif

    _GET_CONTAINER(t_newiterator) = (map_t*)cpt_map;
    _GET_MAP_CONTAINER_TYPE(t_newiterator) = _MAP_CONTAINER;
    _GET_MAP_ITERATOR_TYPE(t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

map_iterator_t map_end(const map_t* cpt_map)
{
    map_iterator_t t_newiterator;

    assert(cpt_map != NULL);

#ifdef CSTL_MAP_AVL_TREE
    t_newiterator = _avl_tree_end(&cpt_map->_t_tree);
#else
    t_newiterator = _rb_tree_end(&cpt_map->_t_tree);
#endif

    _GET_CONTAINER(t_newiterator) = (map_t*)cpt_map;
    _GET_MAP_CONTAINER_TYPE(t_newiterator) = _MAP_CONTAINER;
    _GET_MAP_ITERATOR_TYPE(t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

map_reverse_iterator_t map_rbegin(const map_t* cpt_map)
{
    map_reverse_iterator_t t_newiterator;

    assert(cpt_map != NULL);

#ifdef CSTL_MAP_AVL_TREE
    t_newiterator = _avl_tree_rbegin(&cpt_map->_t_tree);
#else
    t_newiterator = _rb_tree_rbegin(&cpt_map->_t_tree);
#endif

    _GET_CONTAINER(t_newiterator) = (map_t*)cpt_map;
    _GET_MAP_CONTAINER_TYPE(t_newiterator) = _MAP_CONTAINER;
    _GET_MAP_ITERATOR_TYPE(t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

map_reverse_iterator_t map_rend(const map_t* cpt_map)
{
    map_reverse_iterator_t t_newiterator;

    assert(cpt_map != NULL);

#ifdef CSTL_MAP_AVL_TREE
    t_newiterator = _avl_tree_rend(&cpt_map->_t_tree);
#else
    t_newiterator = _rb_tree_rend(&cpt_map->_t_tree);
#endif

    _GET_CONTAINER(t_newiterator) = (map_t*)cpt_map;
    _GET_MAP_CONTAINER_TYPE(t_newiterator) = _MAP_CONTAINER;
    _GET_MAP_ITERATOR_TYPE(t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

map_iterator_t _map_find(const map_t* cpt_map, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, cpt_map);
    return _map_find_varg(cpt_map, val_elemlist);
}

map_iterator_t _map_find_varg(const map_t* cpt_map, va_list val_elemlist)
{
    map_iterator_t t_iterator;

    assert(cpt_map != NULL);

    /* get key */
    _type_get_varg_value(&((map_t*)cpt_map)->_t_pair._t_typeinfofirst,
        val_elemlist, cpt_map->_t_pair._pv_first);
    /* find key in tree */
#ifdef CSTL_MAP_AVL_TREE
    t_iterator = _avl_tree_find(&cpt_map->_t_tree, &cpt_map->_t_pair);
#else
    t_iterator = _rb_tree_find(&cpt_map->_t_tree, &cpt_map->_t_pair);
#endif

    _GET_CONTAINER(t_iterator) = (map_t*)cpt_map;
    _GET_MAP_CONTAINER_TYPE(t_iterator) = _MAP_CONTAINER;
    _GET_MAP_ITERATOR_TYPE(t_iterator) = _BIDIRECTIONAL_ITERATOR;

    return t_iterator;
}

size_t _map_count(const map_t* cpt_map, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, cpt_map);
    return _map_count_varg(cpt_map, val_elemlist);
}

size_t _map_count_varg(const map_t* cpt_map, va_list val_elemlist)
{
    assert(cpt_map != NULL);

    _type_get_varg_value(&((map_t*)cpt_map)->_t_pair._t_typeinfofirst,
        val_elemlist, cpt_map->_t_pair._pv_first);
#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_count(&cpt_map->_t_tree, &cpt_map->_t_pair);
#else
    return _rb_tree_count(&cpt_map->_t_tree, &cpt_map->_t_pair);
#endif
}

map_iterator_t _map_lower_bound(const map_t* cpt_map, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, cpt_map);
    return _map_lower_bound_varg(cpt_map, val_elemlist);
}

map_iterator_t _map_lower_bound_varg(const map_t* cpt_map, va_list val_elemlist)
{
    map_iterator_t t_iterator;

    assert(cpt_map != NULL);

    _type_get_varg_value(&((map_t*)cpt_map)->_t_pair._t_typeinfofirst,
        val_elemlist, cpt_map->_t_pair._pv_first);
#ifdef CSTL_MAP_AVL_TREE
    t_iterator = _avl_tree_lower_bound(&cpt_map->_t_tree, &cpt_map->_t_pair);
#else
    t_iterator = _rb_tree_lower_bound(&cpt_map->_t_tree, &cpt_map->_t_pair);
#endif

    _GET_CONTAINER(t_iterator) = (map_t*)cpt_map;
    _GET_MAP_CONTAINER_TYPE(t_iterator) = _MAP_CONTAINER;
    _GET_MAP_ITERATOR_TYPE(t_iterator) = _BIDIRECTIONAL_ITERATOR;

    return t_iterator;
}

map_iterator_t _map_upper_bound(const map_t* cpt_map, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, cpt_map);
    return _map_upper_bound_varg(cpt_map, val_elemlist);
}

map_iterator_t _map_upper_bound_varg(const map_t* cpt_map, va_list val_elemlist)
{
    map_iterator_t t_iterator;

    assert(cpt_map != NULL);

    _type_get_varg_value(&((map_t*)cpt_map)->_t_pair._t_typeinfofirst,
        val_elemlist, cpt_map->_t_pair._pv_first);
#ifdef CSTL_MAP_AVL_TREE
    t_iterator = _avl_tree_upper_bound(&cpt_map->_t_tree, &cpt_map->_t_pair);
#else
    t_iterator = _rb_tree_upper_bound(&cpt_map->_t_tree, &cpt_map->_t_pair);
#endif

    _GET_CONTAINER(t_iterator) = (map_t*)cpt_map;
    _GET_MAP_CONTAINER_TYPE(t_iterator) = _MAP_CONTAINER;
    _GET_MAP_ITERATOR_TYPE(t_iterator) = _BIDIRECTIONAL_ITERATOR;

    return t_iterator;
}

range_t _map_equal_range(const map_t* cpt_map, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, cpt_map);
    return _map_equal_range_varg(cpt_map, val_elemlist);
}

range_t _map_equal_range_varg(const map_t* cpt_map, va_list val_elemlist)
{
    range_t t_range;

    assert(cpt_map != NULL);

    _type_get_varg_value(&((map_t*)cpt_map)->_t_pair._t_typeinfofirst,
        val_elemlist, cpt_map->_t_pair._pv_first);
#ifdef CSTL_MAP_AVL_TREE
    t_range = _avl_tree_equal_range(&cpt_map->_t_tree, &cpt_map->_t_pair);
#else
    t_range = _rb_tree_equal_range(&cpt_map->_t_tree, &cpt_map->_t_pair);
#endif

    _GET_CONTAINER(t_range.t_begin) = (map_t*)cpt_map;
    _GET_MAP_CONTAINER_TYPE(t_range.t_begin) = _MAP_CONTAINER;
    _GET_MAP_ITERATOR_TYPE(t_range.t_begin) = _BIDIRECTIONAL_ITERATOR;
    _GET_CONTAINER(t_range.t_end) = (map_t*)cpt_map;
    _GET_MAP_CONTAINER_TYPE(t_range.t_end) = _MAP_CONTAINER;
    _GET_MAP_ITERATOR_TYPE(t_range.t_end) = _BIDIRECTIONAL_ITERATOR;

    return t_range;
}

map_iterator_t map_insert(map_t* pt_map, const pair_t* cpt_pair)
{
    map_iterator_t t_iter;

    assert(pt_map != NULL && cpt_pair != NULL);
    assert(_map_same_pair_type(&pt_map->_t_pair, cpt_pair));

    /* insert pair into tree */
#ifdef CSTL_MAP_AVL_TREE
    t_iter =  _avl_tree_insert_unique(&pt_map->_t_tree, cpt_pair);
#else
    t_iter = _rb_tree_insert_unique(&pt_map->_t_tree, cpt_pair);
#endif

    _GET_CONTAINER(t_iter) = pt_map;
    _GET_MAP_CONTAINER_TYPE(t_iter) = _MAP_CONTAINER;
    _GET_MAP_ITERATOR_TYPE(t_iter) = _BIDIRECTIONAL_ITERATOR;

    return t_iter;
}

map_iterator_t map_insert_hint(map_t* pt_map, map_iterator_t t_hint, const pair_t* cpt_pair)
{
    assert(pt_map != NULL && cpt_pair != NULL);
    assert(_map_same_pair_type(&pt_map->_t_pair, cpt_pair));

#ifdef CSTL_MAP_AVL_TREE
    t_hint = _avl_tree_insert_unique(&pt_map->_t_tree, cpt_pair);
#else
    t_hint = _rb_tree_insert_unique(&pt_map->_t_tree, cpt_pair);
#endif

    _GET_CONTAINER(t_hint) = pt_map;
    _GET_MAP_CONTAINER_TYPE(t_hint) = _MAP_CONTAINER;
    _GET_MAP_ITERATOR_TYPE(t_hint) = _BIDIRECTIONAL_ITERATOR;

    return t_hint;
}

void map_insert_range(map_t* pt_map, map_iterator_t t_begin, map_iterator_t t_end)
{
    map_iterator_t t_iterator;

    assert(pt_map != NULL);
    assert(_GET_MAP_CONTAINER_TYPE(t_begin) == _MAP_CONTAINER &&
           _GET_MAP_ITERATOR_TYPE(t_begin) == _BIDIRECTIONAL_ITERATOR &&
           _GET_MAP_CONTAINER_TYPE(t_end) == _MAP_CONTAINER &&
           _GET_MAP_ITERATOR_TYPE(t_end) == _BIDIRECTIONAL_ITERATOR);
    assert(_GET_MAP_CONTAINER(t_begin) != pt_map &&
           _GET_MAP_CONTAINER(t_end) != pt_map &&
           _GET_MAP_CONTAINER(t_begin) == _GET_MAP_CONTAINER(t_end));

    for(t_iterator = t_begin;
        !iterator_equal(t_iterator, t_end);
        t_iterator = iterator_next(t_iterator))
    {
        map_insert(pt_map, (pair_t*)iterator_get_pointer(t_iterator));
    }
}

void map_erase_pos(map_t* pt_map, map_iterator_t t_pos)
{
    assert(pt_map != NULL);
    assert(_GET_MAP_CONTAINER_TYPE(t_pos) == _MAP_CONTAINER &&
           _GET_MAP_ITERATOR_TYPE(t_pos) == _BIDIRECTIONAL_ITERATOR &&
           _GET_MAP_CONTAINER(t_pos) == pt_map);

#ifdef CSTL_MAP_AVL_TREE
    _avl_tree_erase_pos(&pt_map->_t_tree, t_pos);
#else
    _rb_tree_erase_pos(&pt_map->_t_tree, t_pos);
#endif
}

void map_erase_range(map_t* pt_map, map_iterator_t t_begin, map_iterator_t t_end)
{
    assert(pt_map != NULL);
    assert(_GET_MAP_CONTAINER_TYPE(t_begin) == _MAP_CONTAINER &&
           _GET_MAP_ITERATOR_TYPE(t_begin) == _BIDIRECTIONAL_ITERATOR &&
           _GET_MAP_CONTAINER_TYPE(t_end) == _MAP_CONTAINER &&
           _GET_MAP_ITERATOR_TYPE(t_end) == _BIDIRECTIONAL_ITERATOR);
    assert(_GET_MAP_CONTAINER(t_begin) == pt_map && _GET_MAP_CONTAINER(t_end) == pt_map);

#ifdef CSTL_MAP_AVL_TREE
    _avl_tree_erase_range(&pt_map->_t_tree, t_begin, t_end);
#else
    _rb_tree_erase_range(&pt_map->_t_tree, t_begin, t_end);
#endif
}

size_t _map_erase(map_t* pt_map, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, pt_map);
    return _map_erase_varg(pt_map, val_elemlist);
}

size_t _map_erase_varg(map_t* pt_map, va_list val_elemlist)
{
    assert(pt_map != NULL);

    /* get key */
    _type_get_varg_value(&pt_map->_t_pair._t_typeinfofirst,
        val_elemlist, pt_map->_t_pair._pv_first);
#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_erase(&pt_map->_t_tree, &pt_map->_t_pair);
#else
    return _rb_tree_erase(&pt_map->_t_tree, &pt_map->_t_pair);
#endif
}

void* _map_at(map_t* pt_map, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, pt_map);
    return _map_at_varg(pt_map, val_elemlist);
}

void* _map_at_varg(map_t* pt_map, va_list val_elemlist)
{
    map_iterator_t t_iter;

    assert(pt_map != NULL);

    _type_get_varg_value(&pt_map->_t_pair._t_typeinfofirst,
        val_elemlist, pt_map->_t_pair._pv_first);
#ifdef CSTL_MAP_AVL_TREE
    t_iter = _avl_tree_insert_unique(&pt_map->_t_tree, &pt_map->_t_pair);
#else
    t_iter = _rb_tree_insert_unique(&pt_map->_t_tree, &pt_map->_t_pair);
#endif

    if(iterator_equal(t_iter, map_end(pt_map)))
    {
        t_iter = _map_find_varg(pt_map, val_elemlist);
    }

    /* char* */
    if(strncmp(_GET_MAP_SECOND_TYPE_BASENAME(pt_map), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        return (char*)string_c_str(
            (string_t*)((pair_t*)iterator_get_pointer(t_iter))->_pv_second);
    }
    else
    {
        return ((pair_t*)iterator_get_pointer(t_iter))->_pv_second;
    }
}

void _map_init_elem_auxiliary(map_t* pt_map, void* pv_elem)
{
    assert(pt_map != NULL && pv_elem != NULL);

    /* initialize new elements */
    if(pt_map->_t_tree._t_typeinfo._t_style == _TYPE_CSTL_BUILTIN)
    {
        /* get element type name */
        char s_elemtypename[_TYPE_NAME_SIZE + 1];
        _type_get_elem_typename(pt_map->_t_tree._t_typeinfo._sz_typename, s_elemtypename);

        pt_map->_t_tree._t_typeinfo._pt_type->_t_typeinit(pv_elem, s_elemtypename);
    }
    else
    {
        bool_t t_result = pt_map->_t_tree._t_typeinfo._pt_type->_t_typesize;
        pt_map->_t_tree._t_typeinfo._pt_type->_t_typeinit(pv_elem, &t_result);
        assert(t_result);
    }
}

/** local function implementation section **/
#ifndef NDEBUG
static bool_t _map_same_pair_type(
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

static void _map_key_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    pair_t* pt_first = NULL;
    pair_t* pt_second = NULL;

    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    pt_first = (pair_t*)cpv_first;
    pt_second = (pair_t*)cpv_second;

    assert(_map_same_pair_type(pt_first, pt_second));

    *(bool_t*)pv_output = pt_first->_t_typeinfofirst._pt_type->_t_typesize;
    pt_first->_t_typeinfofirst._pt_type->_t_typeless(
        pt_first->_pv_first, pt_second->_pv_first, pv_output);
}

static void _map_value_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    pair_t* pt_first = NULL;
    pair_t* pt_second = NULL;

    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    pt_first = (pair_t*)cpv_first;
    pt_second = (pair_t*)cpv_second;

    assert(_map_same_pair_type(pt_first, pt_second));

    *(bool_t*)pv_output = pt_first->_t_typeinfosecond._pt_type->_t_typesize;
    pt_first->_t_typeinfosecond._pt_type->_t_typeless(
        pt_first->_pv_second, pt_second->_pv_second, pv_output);
}

/** eof **/

