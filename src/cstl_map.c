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

#include "cstl_avl_tree_iterator.h"
#include "cstl_avl_tree_private.h"
#include "cstl_rb_tree_iterator.h"
#include "cstl_rb_tree_private.h"
#include "cutility.h"

#include "cstl_map_iterator.h"
#include "cstl_map_private.h"
#include "cstl_map.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/
#ifndef NDEBUG
/*
 * Test the two pair is have the same type.
 */
static bool_t _same_map_pair_type(
    const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond);
#endif /* NDEBUG */

/*
 * map_t element compare function.
 */
static int _map_cmp(const void* cpv_firstelem, const void* cpv_secondelem);

/*
 * Destroy element function.
 */
static void _map_destroy_elem(void* pv_value);

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
    char   s_typenameex[_TYPE_NAME_SIZE + 1];
    bool_t t_result = false;

    assert(s_typename != NULL);

    if((pt_newmap = (map_t*)malloc(sizeof(map_t))) == NULL)
    {
        return NULL;
    }

    t_result = _create_pair_auxiliary(&pt_newmap->_t_pair, s_typename);
    if(!t_result)
    {
        free(pt_newmap);
        return NULL;
    }

    memset(s_typenameex, '\0', _TYPE_NAME_SIZE + 1);
    strncpy(s_typenameex, _PAIR_TYPE, _TYPE_NAME_SIZE);
    strncat(s_typenameex, _CSTL_LEFT_BRACKET, _TYPE_NAME_SIZE);
    strncat(s_typenameex, s_typename, _TYPE_NAME_SIZE - 8); /* 8 is length of "pair_t<>" */
    strncat(s_typenameex, _CSTL_RIGHT_BRACKET, _TYPE_NAME_SIZE);

#ifdef CSTL_MAP_AVL_TREE
    t_result = _create_avl_tree_auxiliary(&pt_newmap->_t_tree, s_typenameex);
#else
    t_result = _create_rb_tree_auxiliary(&pt_newmap->_t_tree, s_typenameex);
#endif

    if(!t_result)
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
    strncpy(s_typenameex, _PAIR_TYPE, _TYPE_NAME_SIZE);
    strncat(s_typenameex, _CSTL_LEFT_BRACKET, _TYPE_NAME_SIZE);
    strncat(s_typenameex, s_typename, _TYPE_NAME_SIZE - 8); /* 8 is length of "pair_t<>" */
    strncat(s_typenameex, _CSTL_RIGHT_BRACKET, _TYPE_NAME_SIZE);

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
    _avl_tree_init(_GET_MAP_AVL_TREE(pt_map), _map_cmp, _map_destroy_elem);
#else
    _rb_tree_init(_GET_MAP_RB_TREE(pt_map), _map_cmp, _map_destroy_elem);
#endif
}

void map_destroy(map_t* pt_map)
{
    assert(pt_map != NULL);

    /* destroy pair */
    pair_destroy(&pt_map->_t_pair);
    /* destroy tree */
#ifdef CSTL_MAP_AVL_TREE
    _avl_tree_destroy(_GET_MAP_AVL_TREE(pt_map));
#else
    _rb_tree_destroy(_GET_MAP_RB_TREE(pt_map));
#endif
}

void map_init_copy(map_t* pt_mapdest, const map_t* cpt_mapsrc)
{
    assert(pt_mapdest != NULL && cpt_mapsrc != NULL);
    assert(
        pt_mapdest->_t_pair._t_firsttypesize == cpt_mapsrc->_t_pair._t_firsttypesize &&
        pt_mapdest->_t_pair._t_secondtypesize == cpt_mapsrc->_t_pair._t_secondtypesize);
    assert(
        strncmp(
            pt_mapdest->_t_pair._sz_firsttypename,
            cpt_mapsrc->_t_pair._sz_firsttypename,
            _ELEM_TYPE_NAME_SIZE) == 0 &&
        strncmp(
            pt_mapdest->_t_pair._sz_secondtypename,
            cpt_mapsrc->_t_pair._sz_secondtypename,
            _ELEM_TYPE_NAME_SIZE) == 0);

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
    assert(pt_mapdest->_t_pair._t_firsttypesize == 
           _GET_MAP_CONTAINER(t_begin)->_t_pair._t_firsttypesize &&
           pt_mapdest->_t_pair._t_secondtypesize ==
           _GET_MAP_CONTAINER(t_begin)->_t_pair._t_secondtypesize);
    assert(strncmp(pt_mapdest->_t_pair._sz_firsttypename,
           _GET_MAP_CONTAINER(t_begin)->_t_pair._sz_firsttypename,
           _ELEM_TYPE_NAME_SIZE) == 0 &&
           strncmp(pt_mapdest->_t_pair._sz_secondtypename,
           _GET_MAP_CONTAINER(t_begin)->_t_pair._sz_secondtypename,
           _ELEM_TYPE_NAME_SIZE) == 0);

    /* initialize dest map with src map attribute */
    map_init(pt_mapdest);
    /* insert all element from src to dest */
    if(!map_empty(_GET_MAP_CONTAINER(t_begin)))
    {
        map_insert_range(pt_mapdest, t_begin, t_end);
    }
}

void map_init_copy_range_cmp(
    map_t* pt_mapdest, map_iterator_t t_begin, map_iterator_t t_end,
    int (*pfun_key_cmp)(const void*, const void*))
{
    assert(pt_mapdest != NULL);
    assert(_GET_MAP_CONTAINER_TYPE(t_begin) == _MAP_CONTAINER &&
           _GET_MAP_ITERATOR_TYPE(t_begin) == _BIDIRECTIONAL_ITERATOR &&
           _GET_MAP_CONTAINER_TYPE(t_end) == _MAP_CONTAINER &&
           _GET_MAP_ITERATOR_TYPE(t_end) == _BIDIRECTIONAL_ITERATOR);
    assert(_GET_MAP_CONTAINER(t_begin) != pt_mapdest &&
           _GET_MAP_CONTAINER(t_end) != pt_mapdest &&
           _GET_MAP_CONTAINER(t_begin) == _GET_MAP_CONTAINER(t_end));
    assert(pt_mapdest->_t_pair._t_firsttypesize == 
           _GET_MAP_CONTAINER(t_begin)->_t_pair._t_firsttypesize &&
           pt_mapdest->_t_pair._t_secondtypesize ==
           _GET_MAP_CONTAINER(t_begin)->_t_pair._t_secondtypesize);
    assert(strncmp(pt_mapdest->_t_pair._sz_firsttypename,
           _GET_MAP_CONTAINER(t_begin)->_t_pair._sz_firsttypename,
           _ELEM_TYPE_NAME_SIZE) == 0 &&
           strncmp(pt_mapdest->_t_pair._sz_secondtypename,
           _GET_MAP_CONTAINER(t_begin)->_t_pair._sz_secondtypename,
           _ELEM_TYPE_NAME_SIZE) == 0);

    /* initialize dest map with src map attribute */
    map_init(pt_mapdest);
    pt_mapdest->_t_pair._pfun_first_cmp = pfun_key_cmp;
    /* insert all element from src to dest */
    if(!map_empty(_GET_MAP_CONTAINER(t_begin)))
    {
        map_insert_range(pt_mapdest, t_begin, t_end);
    }
}

void map_assign(map_t* pt_mapdest, const map_t* cpt_mapsrc)
{
    assert(pt_mapdest != NULL && cpt_mapsrc != NULL);
    assert(_same_map_pair_type(&pt_mapdest->_t_pair, &cpt_mapsrc->_t_pair));

    /* destroy dest map */
    map_destroy(pt_mapdest);
    /* initialize dest map with src map attribute */
    map_init(pt_mapdest);
    /* insert all element from src to dest */
    if(!map_empty(cpt_mapsrc))
    {
        map_insert_range(pt_mapdest, map_begin(cpt_mapsrc), map_end(cpt_mapsrc));
    }
}

void map_swap(map_t* pt_mapfirst, map_t* pt_mapsecond)
{
    assert(pt_mapfirst != NULL && pt_mapsecond != NULL);
    assert(_same_map_pair_type(&pt_mapfirst->_t_pair, &pt_mapsecond->_t_pair));

#ifdef CSTL_MAP_AVL_TREE
    _avl_tree_swap(_GET_MAP_AVL_TREE(pt_mapfirst), _GET_MAP_AVL_TREE(pt_mapsecond));
#else
    _rb_tree_swap(_GET_MAP_RB_TREE(pt_mapfirst), _GET_MAP_RB_TREE(pt_mapsecond));
#endif
}

bool_t map_empty(const map_t* cpt_map)
{
    assert(cpt_map != NULL);

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_empty(_GET_MAP_AVL_TREE(cpt_map));
#else
    return _rb_tree_empty(_GET_MAP_RB_TREE(cpt_map));
#endif
}

size_t map_size(const map_t* cpt_map)
{
    assert(cpt_map != NULL);

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_size(_GET_MAP_AVL_TREE(cpt_map));
#else
    return _rb_tree_size(_GET_MAP_RB_TREE(cpt_map));
#endif
}

size_t map_max_size(const map_t* cpt_map)
{
    assert(cpt_map != NULL);

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_max_size(_GET_MAP_AVL_TREE(cpt_map));
#else
    return _rb_tree_max_size(_GET_MAP_RB_TREE(cpt_map));
#endif
}

int (*map_key_comp(const map_t* cpt_map))(const void*, const void*)
{
    assert(cpt_map != NULL);

    return cpt_map->_t_pair._pfun_first_cmp;
}

int (*map_value_comp(const map_t* cpt_map))(const void*, const void*)
{
    assert(cpt_map != NULL);

    return cpt_map->_t_pair._pfun_second_cmp;
}

void map_clear(map_t* pt_map)
{
    assert(pt_map != NULL);

#ifdef CSTL_MAP_AVL_TREE
    _avl_tree_clear(_GET_MAP_AVL_TREE(pt_map));
#else
    _rb_tree_clear(_GET_MAP_RB_TREE(pt_map));
#endif
}

bool_t map_equal(const map_t* cpt_mapfirst, const map_t* cpt_mapsecond)
{
    assert(cpt_mapfirst != NULL && cpt_mapsecond != NULL);

    /* test pair */
    if(cpt_mapfirst->_t_pair._t_firsttypesize != cpt_mapsecond->_t_pair._t_firsttypesize ||
       cpt_mapfirst->_t_pair._t_secondtypesize != cpt_mapsecond->_t_pair._t_secondtypesize)
    {
        return false;
    }
    if(strncmp(
        cpt_mapfirst->_t_pair._sz_firsttypename, 
        cpt_mapsecond->_t_pair._sz_firsttypename, 
        _ELEM_TYPE_NAME_SIZE) != 0 || 
       strncmp(
        cpt_mapfirst->_t_pair._sz_secondtypename, 
        cpt_mapsecond->_t_pair._sz_secondtypename, 
        _ELEM_TYPE_NAME_SIZE) != 0)
    {
        return false;
    }
    if(cpt_mapfirst->_t_pair._pfun_first_cmp != cpt_mapsecond->_t_pair._pfun_first_cmp || 
       cpt_mapfirst->_t_pair._pfun_second_cmp != cpt_mapsecond->_t_pair._pfun_second_cmp)
    {
        return false;
    }
    /* test tree */
#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_equal(
        _GET_MAP_AVL_TREE(cpt_mapfirst), _GET_MAP_AVL_TREE(cpt_mapsecond));
#else
    return _rb_tree_equal(
        _GET_MAP_RB_TREE(cpt_mapfirst), _GET_MAP_RB_TREE(cpt_mapsecond));
#endif
}

bool_t map_not_equal(const map_t* cpt_mapfirst, const map_t* cpt_mapsecond)
{
    return !map_equal(cpt_mapfirst, cpt_mapsecond);
}

bool_t map_less(const map_t* cpt_mapfirst, const map_t* cpt_mapsecond)
{
    assert(cpt_mapfirst != NULL && cpt_mapsecond != NULL);
    assert(_same_map_pair_type(&cpt_mapfirst->_t_pair, &cpt_mapsecond->_t_pair));

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_less(
        _GET_MAP_AVL_TREE(cpt_mapfirst), _GET_MAP_AVL_TREE(cpt_mapsecond));
#else
    return _rb_tree_less(
        _GET_MAP_RB_TREE(cpt_mapfirst), _GET_MAP_RB_TREE(cpt_mapsecond));
#endif
}

bool_t map_less_equal(const map_t* cpt_mapfirst, const map_t* cpt_mapsecond)
{
    assert(cpt_mapfirst != NULL && cpt_mapsecond != NULL);
    assert(_same_map_pair_type(&cpt_mapfirst->_t_pair, &cpt_mapsecond->_t_pair));

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_less_equal(
        _GET_MAP_AVL_TREE(cpt_mapfirst), _GET_MAP_AVL_TREE(cpt_mapsecond));
#else
    return _rb_tree_less_equal(
        _GET_MAP_RB_TREE(cpt_mapfirst), _GET_MAP_RB_TREE(cpt_mapsecond));
#endif
}

bool_t map_great(const map_t* cpt_mapfirst, const map_t* cpt_mapsecond)
{
    assert(cpt_mapfirst != NULL && cpt_mapsecond != NULL);
    assert(_same_map_pair_type(&cpt_mapfirst->_t_pair, &cpt_mapsecond->_t_pair));

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_great(
        _GET_MAP_AVL_TREE(cpt_mapfirst), _GET_MAP_AVL_TREE(cpt_mapsecond));
#else
    return _rb_tree_great(
        _GET_MAP_RB_TREE(cpt_mapfirst), _GET_MAP_RB_TREE(cpt_mapsecond));
#endif
}

bool_t map_great_equal(const map_t* cpt_mapfirst, const map_t* cpt_mapsecond)
{
    assert(cpt_mapfirst != NULL && cpt_mapsecond != NULL);
    assert(_same_map_pair_type(&cpt_mapfirst->_t_pair, &cpt_mapsecond->_t_pair));

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_great_equal(
        _GET_MAP_AVL_TREE(cpt_mapfirst), _GET_MAP_AVL_TREE(cpt_mapsecond));
#else
    return _rb_tree_great_equal(
        _GET_MAP_RB_TREE(cpt_mapfirst), _GET_MAP_RB_TREE(cpt_mapsecond));
#endif
}

map_iterator_t map_begin(const map_t* cpt_map)
{
    map_iterator_t t_newiterator;

    assert(cpt_map != NULL);

#ifdef CSTL_MAP_AVL_TREE
    t_newiterator = _avl_tree_begin(_GET_MAP_AVL_TREE(cpt_map));
#else
    t_newiterator = _rb_tree_begin(_GET_MAP_RB_TREE(cpt_map));
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
    t_newiterator = _avl_tree_end(_GET_MAP_AVL_TREE(cpt_map));
#else
    t_newiterator = _rb_tree_end(_GET_MAP_RB_TREE(cpt_map));
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
    t_newiterator = _avl_tree_rbegin(_GET_MAP_AVL_TREE(cpt_map));
#else
    t_newiterator = _rb_tree_rbegin(_GET_MAP_RB_TREE(cpt_map));
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
    t_newiterator = _avl_tree_rend(_GET_MAP_AVL_TREE(cpt_map));
#else
    t_newiterator = _rb_tree_rend(_GET_MAP_RB_TREE(cpt_map));
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
    _get_varg_value(
        cpt_map->_t_pair.first, val_elemlist,
        cpt_map->_t_pair._t_firsttypesize, cpt_map->_t_pair._sz_firsttypename);
    /* find key in tree */
#ifdef CSTL_MAP_AVL_TREE
    t_iterator = _avl_tree_find(_GET_MAP_AVL_TREE(cpt_map), &cpt_map->_t_pair);
#else
    t_iterator = _rb_tree_find(_GET_MAP_RB_TREE(cpt_map), &cpt_map->_t_pair);
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

    _get_varg_value(
        cpt_map->_t_pair.first, val_elemlist,
        cpt_map->_t_pair._t_firsttypesize, cpt_map->_t_pair._sz_firsttypename);
#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_count(_GET_MAP_AVL_TREE(cpt_map), &cpt_map->_t_pair);
#else
    return _rb_tree_count(_GET_MAP_RB_TREE(cpt_map), &cpt_map->_t_pair);
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

    _get_varg_value(
        cpt_map->_t_pair.first, val_elemlist,
        cpt_map->_t_pair._t_firsttypesize, cpt_map->_t_pair._sz_firsttypename);
#ifdef CSTL_MAP_AVL_TREE
    t_iterator = 
        _avl_tree_lower_bound(_GET_MAP_AVL_TREE(cpt_map), &cpt_map->_t_pair);
#else
    t_iterator = 
        _rb_tree_lower_bound(_GET_MAP_RB_TREE(cpt_map), &cpt_map->_t_pair);
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

    _get_varg_value(
        cpt_map->_t_pair.first, val_elemlist,
        cpt_map->_t_pair._t_firsttypesize, cpt_map->_t_pair._sz_firsttypename);
#ifdef CSTL_MAP_AVL_TREE
    t_iterator = 
        _avl_tree_upper_bound(_GET_MAP_AVL_TREE(cpt_map), &cpt_map->_t_pair);
#else
    t_iterator = 
        _rb_tree_upper_bound(_GET_MAP_RB_TREE(cpt_map), &cpt_map->_t_pair);
#endif

    _GET_CONTAINER(t_iterator) = (map_t*)cpt_map;
    _GET_MAP_CONTAINER_TYPE(t_iterator) = _MAP_CONTAINER;
    _GET_MAP_ITERATOR_TYPE(t_iterator) = _BIDIRECTIONAL_ITERATOR;

    return t_iterator;
}

pair_t _map_equal_range(const map_t* cpt_map, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, cpt_map);
    return _map_equal_range_varg(cpt_map, val_elemlist);
}

pair_t _map_equal_range_varg(const map_t* cpt_map, va_list val_elemlist)
{
    map_iterator_t t_first;
    map_iterator_t t_second;
    pair_t         t_pair;
#ifdef CSTL_MAP_AVL_TREE
    avl_tree_result_pair_t t_avlresult;
#else
    rb_tree_result_pair_t  t_rbresult;
#endif

    assert(cpt_map != NULL);

    _get_varg_value(
        cpt_map->_t_pair.first, val_elemlist,
        cpt_map->_t_pair._t_firsttypesize, cpt_map->_t_pair._sz_firsttypename);
#ifdef CSTL_MAP_AVL_TREE
    t_avlresult = 
        _avl_tree_equal_range(_GET_MAP_AVL_TREE(cpt_map), &cpt_map->_t_pair);
    t_first = t_avlresult._t_first;
    t_second = t_avlresult._t_second._t_iterator;
#else
    t_rbresult = 
        _rb_tree_equal_range(_GET_MAP_RB_TREE(cpt_map), &cpt_map->_t_pair);
    t_first = t_rbresult._t_first;
    t_second = t_rbresult._t_second._t_iterator;
#endif

    _GET_CONTAINER(t_first) = (map_t*)cpt_map;
    _GET_MAP_CONTAINER_TYPE(t_first) = _MAP_CONTAINER;
    _GET_MAP_ITERATOR_TYPE(t_first) = _BIDIRECTIONAL_ITERATOR;
    _GET_CONTAINER(t_second) = (map_t*)cpt_map;
    _GET_MAP_CONTAINER_TYPE(t_second) = _MAP_CONTAINER;
    _GET_MAP_ITERATOR_TYPE(t_second) = _BIDIRECTIONAL_ITERATOR;

    t_pair = create_pair(map_iterator_t, map_iterator_t);
    pair_init(&t_pair);
    memcpy(t_pair.first, &t_first, t_pair._t_firsttypesize);
    memcpy(t_pair.second, &t_second, t_pair._t_secondtypesize);

    return t_pair;
}

map_iterator_t map_insert(map_t* pt_map, const pair_t* cpt_pair)
{
    pair_t         t_elempair;
    map_iterator_t t_result;
#ifdef CSTL_MAP_AVL_TREE
    avl_tree_result_pair_t t_avlresult;
#else
    rb_tree_result_pair_t  t_rbresult;
#endif

    assert(pt_map != NULL && cpt_pair != NULL);
    assert(_same_map_pair_type(&pt_map->_t_pair, cpt_pair));

    /* initialize the new pair */
    t_elempair = _create_pair(
        pt_map->_t_pair._t_firsttypesize, pt_map->_t_pair._sz_firsttypename,
        pt_map->_t_pair._t_secondtypesize, pt_map->_t_pair._sz_secondtypename);
    pair_init(&t_elempair);
    memcpy(t_elempair.first, cpt_pair->first, t_elempair._t_firsttypesize);
    memcpy(t_elempair.second, cpt_pair->second, t_elempair._t_secondtypesize);

    /* insert pair into tree */
#ifdef CSTL_MAP_AVL_TREE
    t_avlresult = _avl_tree_insert_unique(_GET_MAP_AVL_TREE(pt_map), &t_elempair);
    if(t_avlresult._t_second._t_bool)
    {
        t_result = t_avlresult._t_first;
    }
    else
    {
        t_result = map_end(pt_map);
        pair_destroy(&t_elempair);
    }
#else
    t_rbresult = _rb_tree_insert_unique(_GET_MAP_RB_TREE(pt_map), &t_elempair);
    if(t_rbresult._t_second._t_bool)
    {
        t_result = t_rbresult._t_first;
    }
    else
    {
        t_result = map_end(pt_map);
        pair_destroy(&t_elempair);
    }
#endif

    _GET_CONTAINER(t_result) = pt_map;
    _GET_MAP_CONTAINER_TYPE(t_result) = _MAP_CONTAINER;
    _GET_MAP_ITERATOR_TYPE(t_result) = _BIDIRECTIONAL_ITERATOR;

    return t_result;
}

map_iterator_t map_insert_hint(map_t* pt_map, map_iterator_t t_hint, const pair_t* cpt_pair)
{
    pair_t t_elempair;
    bool_t t_result;
#ifdef CSTL_MAP_AVL_TREE
    avl_tree_result_pair_t t_avlresult;
#else
    rb_tree_result_pair_t  t_rbresult;
#endif

    assert(pt_map != NULL && cpt_pair != NULL);
    assert(_same_map_pair_type(&pt_map->_t_pair, cpt_pair));

    /* initialize the new pair */
    t_elempair = _create_pair(
        pt_map->_t_pair._t_firsttypesize, pt_map->_t_pair._sz_firsttypename,
        pt_map->_t_pair._t_secondtypesize, pt_map->_t_pair._sz_secondtypename);
    pair_init(&t_elempair);
    memcpy(t_elempair.first, cpt_pair->first, t_elempair._t_firsttypesize);
    memcpy(t_elempair.second, cpt_pair->second, t_elempair._t_secondtypesize);

    /* insert pair into tree */
#ifdef CSTL_MAP_AVL_TREE
    t_avlresult = _avl_tree_insert_unique(_GET_MAP_AVL_TREE(pt_map), &t_elempair);
    t_hint = t_avlresult._t_first;
    t_result = t_avlresult._t_second._t_bool;
#else
    t_rbresult = _rb_tree_insert_unique(_GET_MAP_RB_TREE(pt_map), &t_elempair);
    t_hint = t_rbresult._t_first;
    t_result = t_rbresult._t_second._t_bool;
#endif
    /* destroy when insert failed */
    if(!t_result)
    {
        pair_destroy(&t_elempair);
    }

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
    _avl_tree_erase_pos(_GET_MAP_AVL_TREE(pt_map), t_pos);
#else
    _rb_tree_erase_pos(_GET_MAP_RB_TREE(pt_map), t_pos);
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
    _avl_tree_erase_range(_GET_MAP_AVL_TREE(pt_map), t_begin, t_end);
#else
    _rb_tree_erase_range(_GET_MAP_RB_TREE(pt_map), t_begin, t_end);
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
    _get_varg_value(
        pt_map->_t_pair.first, val_elemlist,
        pt_map->_t_pair._t_firsttypesize, pt_map->_t_pair._sz_firsttypename);
#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_erase(_GET_MAP_AVL_TREE(pt_map), &pt_map->_t_pair);
#else
    return _rb_tree_erase(_GET_MAP_RB_TREE(pt_map), &pt_map->_t_pair);
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
    pair_t  t_elempair;
    bool_t  t_result = false;
    void*   pv_value = NULL;
#ifdef CSTL_MAP_AVL_TREE
    avl_tree_result_pair_t t_avlresult;
#else
    rb_tree_result_pair_t  t_rbresult;
#endif

    assert(pt_map != NULL);

    t_elempair = _create_pair(
        pt_map->_t_pair._t_firsttypesize, pt_map->_t_pair._sz_firsttypename,
        pt_map->_t_pair._t_secondtypesize, pt_map->_t_pair._sz_secondtypename);
    pair_init(&t_elempair);
    _get_varg_value(
        t_elempair.first, val_elemlist,
        t_elempair._t_firsttypesize, t_elempair._sz_firsttypename);
    memset(t_elempair.second, 0x00, t_elempair._t_secondtypesize);

#ifdef CSTL_MAP_AVL_TREE
    t_avlresult = _avl_tree_insert_unique(_GET_MAP_AVL_TREE(pt_map), &t_elempair);
    pv_value = ((pair_t*)((avlnode_t*)
        _GET_AVL_TREE_COREPOS(t_avlresult._t_first))->_pc_data)->second;
    t_result = t_avlresult._t_second._t_bool;
#else
    t_rbresult = _rb_tree_insert_unique(_GET_MAP_RB_TREE(pt_map), &t_elempair);
    pv_value = ((pair_t*)((rbnode_t*)
        _GET_RB_TREE_COREPOS(t_rbresult._t_first))->_pc_data)->second;
    t_result = t_rbresult._t_second._t_bool;
#endif
    assert(pv_value != NULL);

    /* destroy the pair when inserting failed */
    if(!t_result)
    {
        pair_destroy(&t_elempair);
    }

    return pv_value;
}

/** local function implementation section **/
#ifndef NDEBUG
static bool_t _same_map_pair_type(
    const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond)
{
    assert(cpt_pairfirst != NULL && cpt_pairsecond != NULL);

    assert(cpt_pairfirst->first != NULL && cpt_pairfirst->second != NULL);
    assert(cpt_pairsecond->first != NULL && cpt_pairsecond->second != NULL);
    assert(
        cpt_pairfirst->_t_firsttypesize == cpt_pairsecond->_t_firsttypesize && 
        cpt_pairfirst->_t_secondtypesize == cpt_pairsecond->_t_secondtypesize);
    assert(
        strncmp(
            cpt_pairfirst->_sz_firsttypename,
            cpt_pairsecond->_sz_firsttypename,
            _ELEM_TYPE_NAME_SIZE) == 0 &&
        strncmp(
            cpt_pairfirst->_sz_secondtypename,
            cpt_pairsecond->_sz_secondtypename,
            _ELEM_TYPE_NAME_SIZE) == 0);

    assert(
        cpt_pairfirst->_pfun_first_cmp == cpt_pairsecond->_pfun_first_cmp &&
        cpt_pairfirst->_pfun_second_cmp == cpt_pairsecond->_pfun_second_cmp);

    return true;
}
#endif /* NDEBUG */

static int _map_cmp(const void* cpv_firstelem, const void* cpv_secondelem)
{
    pair_t* pt_first = NULL;
    pair_t* pt_second = NULL;

    assert(cpv_firstelem != NULL && cpv_secondelem != NULL);

    pt_first = (pair_t*)cpv_firstelem;
    pt_second = (pair_t*)cpv_secondelem;

    assert(_same_map_pair_type(pt_first, pt_second));

    if(pt_first->_pfun_first_cmp != NULL)
    {
        return (*pt_first->_pfun_first_cmp)(pt_first->first, pt_second->first);
    }
    else
    {
        return memcmp(pt_first->first, pt_second->first, pt_first->_t_firsttypesize);
    }
}

static void _map_destroy_elem(void* pv_value)
{
    assert(pv_value != NULL);

    pair_destroy((pair_t*)pv_value);
}

/** eof **/

