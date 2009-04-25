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

#include "cstl_types.h"
#include "cstl_alloc.h"
#include "cstl_iterator.h"

#include "cstl_avl_tree_iterator.h"
#include "cstl_avl_tree_private.h"
#include "cstl_rb_tree_iterator.h"
#include "cstl_rb_tree_private.h"
#include "cutility.h"

#include "cstl_multimap_iterator.h"
#include "cstl_multimap_private.h"
#include "cstl_multimap.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/
#ifndef NDEBUG
/*
 *  Functionname: _same_multimap_pair_type
 *    Parameters: in) cpt_pairfirst: const pair_t*
 *                    first pair pointer.
 *                in) cpt_pairsecond: const pair_t*
 *                    second pair pointer.
 *       Returns: bool_t
 *   Description: test the two pair is have the same type.
 */
static bool_t _same_multimap_pair_type(
    const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond);
#endif /* NDEBUG */

/*
 *  Functionname: _multimap_cmp
 *    Parameters: in) cpv_firstelem: const void*
 *                    first element.
 *                in) cpv_secondelem: const void*
 *                    second element.
 *       Returns: int
 *   Description: multimap element compare function.
 */
static int _multimap_cmp(const void* cpv_firstelem, const void* cpv_secondelem);

/*
 *  Functionname: _multimap_destroy_elem
 *    Parameters: in) pv_value: void*
 *                    value pointer.
 *       Returns: void
 *   Description: destroy element function.
 */
static void _multimap_destroy_elem(void* pv_value);

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

    _GET_MULTIMAP_CONTAINER_TYPE(&t_newiterator) = _MULTIMAP_CONTAINER;
    _GET_MULTIMAP_ITERATOR_TYPE(&t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

void _multimap_iterator_get_value(
    const struct _tagmultimap* cpt_multimap, 
    const multimap_iterator_t* cpt_iterator, 
    void* pv_value)
{
    assert(cpt_multimap != NULL && cpt_iterator != NULL && pv_value != NULL);
    assert(
        _GET_MULTIMAP_CONTAINER_TYPE(cpt_iterator) == _MULTIMAP_CONTAINER &&
        _GET_MULTIMAP_ITERATOR_TYPE(cpt_iterator) == _BIDIRECTIONAL_ITERATOR &&
        _GET_MULTIMAP_CONTAINER(cpt_iterator) == cpt_multimap);

#ifdef CSTL_MULTIMAP_AVL_TREE
    _avl_tree_iterator_get_value(
        _GET_MULTIMAP_AVL_TREE(cpt_multimap), cpt_iterator, pv_value);
#else
    _rb_tree_iterator_get_value(
        _GET_MULTIMAP_RB_TREE(cpt_multimap), cpt_iterator, pv_value);
#endif
}

const void* _multimap_iterator_get_pointer(
    const struct _tagmultimap* cpt_multimap, const multimap_iterator_t* cpt_iterator)
{
    assert(cpt_multimap != NULL && cpt_iterator != NULL);
    assert(
        _GET_MULTIMAP_CONTAINER_TYPE(cpt_iterator) == _MULTIMAP_CONTAINER &&
        _GET_MULTIMAP_ITERATOR_TYPE(cpt_iterator) == _BIDIRECTIONAL_ITERATOR &&
        _GET_MULTIMAP_CONTAINER(cpt_iterator) == cpt_multimap);

#ifdef CSTL_MULTIMAP_AVL_TREE
    return _avl_tree_iterator_get_pointer(
        _GET_MULTIMAP_AVL_TREE(cpt_multimap), cpt_iterator);
#else
    return _rb_tree_iterator_get_pointer(
        _GET_MULTIMAP_RB_TREE(cpt_multimap), cpt_iterator);
#endif
}

void _multimap_iterator_next(
    const struct _tagmultimap* cpt_multimap, multimap_iterator_t* pt_iterator)
{
    assert(cpt_multimap != NULL && pt_iterator != NULL);
    assert(
        _GET_MULTIMAP_CONTAINER_TYPE(pt_iterator) == _MULTIMAP_CONTAINER &&
        _GET_MULTIMAP_ITERATOR_TYPE(pt_iterator) == _BIDIRECTIONAL_ITERATOR &&
        _GET_MULTIMAP_CONTAINER(pt_iterator) == cpt_multimap);

#ifdef CSTL_MULTIMAP_AVL_TREE
    _avl_tree_iterator_next(_GET_MULTIMAP_AVL_TREE(cpt_multimap), pt_iterator);
#else
    _rb_tree_iterator_next(_GET_MULTIMAP_RB_TREE(cpt_multimap), pt_iterator);
#endif
}

void _multimap_iterator_prev(
    const struct _tagmultimap* cpt_multimap, multimap_iterator_t* pt_iterator)
{
    assert(cpt_multimap != NULL && pt_iterator != NULL);
    assert(
        _GET_MULTIMAP_CONTAINER_TYPE(pt_iterator) == _MULTIMAP_CONTAINER &&
        _GET_MULTIMAP_ITERATOR_TYPE(pt_iterator) == _BIDIRECTIONAL_ITERATOR &&
        _GET_MULTIMAP_CONTAINER(pt_iterator) == cpt_multimap);

#ifdef CSTL_MULTIMAP_AVL_TREE
    _avl_tree_iterator_prev(_GET_MULTIMAP_AVL_TREE(cpt_multimap), pt_iterator);
#else
    _rb_tree_iterator_prev(_GET_MULTIMAP_RB_TREE(cpt_multimap), pt_iterator);
#endif
}

bool_t _multimap_iterator_equal(
    const struct _tagmultimap* cpt_multimap, 
    const multimap_iterator_t* cpt_iterator,
    multimap_iterator_t t_iterator)
{
    assert(cpt_multimap != NULL && cpt_iterator != NULL);
    assert(
        _GET_MULTIMAP_CONTAINER_TYPE(cpt_iterator) == _MULTIMAP_CONTAINER &&
        _GET_MULTIMAP_ITERATOR_TYPE(cpt_iterator) == _BIDIRECTIONAL_ITERATOR &&
        _GET_MULTIMAP_CONTAINER_TYPE(&t_iterator) == _MULTIMAP_CONTAINER &&
        _GET_MULTIMAP_ITERATOR_TYPE(&t_iterator) == _BIDIRECTIONAL_ITERATOR);
    assert(
        _GET_MULTIMAP_CONTAINER(cpt_iterator) == cpt_multimap &&
        _GET_MULTIMAP_CONTAINER(&t_iterator) == cpt_multimap);

#ifdef CSTL_MULTIMAP_AVL_TREE
    return _avl_tree_iterator_equal(
        _GET_MULTIMAP_AVL_TREE(cpt_multimap), cpt_iterator, t_iterator);
#else
    return _rb_tree_iterator_equal(
        _GET_MULTIMAP_RB_TREE(cpt_multimap), cpt_iterator, t_iterator);
#endif
}

int _multimap_iterator_distance(
    const multimap_iterator_t* cpt_begin, const multimap_iterator_t* cpt_end)
{
    assert(cpt_begin != NULL && cpt_end != NULL);
    assert(
        _GET_MULTIMAP_CONTAINER_TYPE(cpt_begin) == _MULTIMAP_CONTAINER &&
        _GET_MULTIMAP_ITERATOR_TYPE(cpt_begin) == _BIDIRECTIONAL_ITERATOR &&
        _GET_MULTIMAP_CONTAINER_TYPE(cpt_end) == _MULTIMAP_CONTAINER &&
        _GET_MULTIMAP_ITERATOR_TYPE(cpt_end) == _BIDIRECTIONAL_ITERATOR &&
        _GET_MULTIMAP_CONTAINER(cpt_begin) == _GET_MULTIMAP_CONTAINER(cpt_end));

#ifdef CSTL_MULTIMAP_AVL_TREE
    return _avl_tree_iterator_distance(cpt_begin, cpt_end);
#else
    return _rb_tree_iterator_distance(cpt_begin, cpt_end);
#endif
}

bool_t _multimap_iterator_before(
    const multimap_iterator_t* cpt_iteratorfirst,
    const multimap_iterator_t* cpt_iteratorsecond)
{
    assert(cpt_iteratorfirst != NULL && cpt_iteratorsecond != NULL);
    assert(
        _GET_MULTIMAP_CONTAINER_TYPE(cpt_iteratorfirst) == _MULTIMAP_CONTAINER &&
        _GET_MULTIMAP_ITERATOR_TYPE(cpt_iteratorfirst) == _BIDIRECTIONAL_ITERATOR &&
        _GET_MULTIMAP_CONTAINER_TYPE(cpt_iteratorsecond) == _MULTIMAP_CONTAINER &&
        _GET_MULTIMAP_ITERATOR_TYPE(cpt_iteratorsecond) == _BIDIRECTIONAL_ITERATOR &&
        _GET_MULTIMAP_CONTAINER(cpt_iteratorfirst) == 
            _GET_MULTIMAP_CONTAINER(cpt_iteratorsecond));

#ifdef CSTL_MULTIMAP_AVL_TREE
    return _avl_tree_iterator_before(cpt_iteratorfirst, cpt_iteratorsecond);
#else
    return _rb_tree_iterator_before(cpt_iteratorfirst, cpt_iteratorsecond);
#endif
}

/* multimap private function */
multimap_t _create_multimap(
    size_t t_keytypesize, const char* s_keytypename,
    size_t t_valuetypesize, const char* s_valuetypename)
{
    multimap_t t_newmultimap;
    char       ac_multimaptypename[_ELEM_TYPE_NAME_SIZE+1];

    assert(t_keytypesize > 0 && t_valuetypesize > 0);
    assert(s_keytypename != NULL && s_valuetypename != NULL);

    /* create pair */
    t_newmultimap._t_pair = _create_pair(
        t_keytypesize, s_keytypename, t_valuetypesize, s_valuetypename);
    /* create tree */
    memset(ac_multimaptypename, '\0', _ELEM_TYPE_NAME_SIZE+1);
    strncpy(ac_multimaptypename, _MULTIMAP_IDENTIFY, _ELEM_TYPE_NAME_SIZE);
    strcat(ac_multimaptypename, _MULTIMAP_LEFT_BRACKET);
    strcat(ac_multimaptypename, t_newmultimap._t_pair._sz_firsttypename);
    strcat(ac_multimaptypename, _MULTIMAP_COMMA);
    strcat(ac_multimaptypename, t_newmultimap._t_pair._sz_secondtypename);
    strcat(ac_multimaptypename, _MULTIMAP_RIGHT_BRACKET);

#ifdef CSTL_MULTIMAP_AVL_TREE
    *_GET_MULTIMAP_AVL_TREE(&t_newmultimap) = 
        _create_avl_tree(sizeof(pair_t), ac_multimaptypename);
#else
    *_GET_MULTIMAP_RB_TREE(&t_newmultimap) = 
        _create_rb_tree(sizeof(pair_t), ac_multimaptypename);
#endif

    return t_newmultimap;
}

/* multimap function */
void multimap_init(multimap_t* pt_multimap)
{
    assert(pt_multimap != NULL);

    /* initialize the pair */
    pair_init(&pt_multimap->_t_pair);
    /* initialize the tree */
#ifdef CSTL_MULTIMAP_AVL_TREE
    _avl_tree_init(
        _GET_MULTIMAP_AVL_TREE(pt_multimap), _multimap_cmp, _multimap_destroy_elem);
#else
    _rb_tree_init(
        _GET_MULTIMAP_RB_TREE(pt_multimap), _multimap_cmp, _multimap_destroy_elem);
#endif
}

void multimap_destroy(multimap_t* pt_multimap)
{
    assert(pt_multimap != NULL);

    /* destroy pair */
    pair_destroy(&pt_multimap->_t_pair);
    /* destroy tree */
#ifdef CSTL_MULTIMAP_AVL_TREE
    _avl_tree_destroy(_GET_MULTIMAP_AVL_TREE(pt_multimap));
#else
    _rb_tree_destroy(_GET_MULTIMAP_RB_TREE(pt_multimap));
#endif
}

void multimap_init_copy(multimap_t* pt_multimapdest, const multimap_t* cpt_multimapsrc)
{
    assert(pt_multimapdest != NULL && cpt_multimapsrc != NULL);
    assert(
        pt_multimapdest->_t_pair._t_firsttypesize == 
            cpt_multimapsrc->_t_pair._t_firsttypesize &&
        pt_multimapdest->_t_pair._t_secondtypesize ==
            cpt_multimapsrc->_t_pair._t_secondtypesize);
    assert(
        strncmp(
            pt_multimapdest->_t_pair._sz_firsttypename,
            cpt_multimapsrc->_t_pair._sz_firsttypename,
            _ELEM_TYPE_NAME_SIZE) == 0 &&
        strncmp(
            pt_multimapdest->_t_pair._sz_secondtypename,
            cpt_multimapsrc->_t_pair._sz_secondtypename,
            _ELEM_TYPE_NAME_SIZE) == 0);

    /* initialize dest multimap with src multimap attribute */
    multimap_init(pt_multimapdest);
    /* insert all element from src to dest */
    if(!multimap_empty(cpt_multimapsrc))
    {
        multimap_insert_range(
            pt_multimapdest, 
            multimap_begin(cpt_multimapsrc), 
            multimap_end(cpt_multimapsrc));
    }
}

void multimap_init_copy_range(
    multimap_t* pt_multimapdest,
    multimap_iterator_t t_begin,
    multimap_iterator_t t_end)
{
    assert(pt_multimapdest != NULL);
    assert(
        _GET_MULTIMAP_CONTAINER_TYPE(&t_begin) == _MULTIMAP_CONTAINER &&
        _GET_MULTIMAP_ITERATOR_TYPE(&t_begin) == _BIDIRECTIONAL_ITERATOR &&
        _GET_MULTIMAP_CONTAINER_TYPE(&t_end) == _MULTIMAP_CONTAINER &&
        _GET_MULTIMAP_ITERATOR_TYPE(&t_end) == _BIDIRECTIONAL_ITERATOR);
    assert(
        _GET_MULTIMAP_CONTAINER(&t_begin) != pt_multimapdest &&
        _GET_MULTIMAP_CONTAINER(&t_end) != pt_multimapdest &&
        _GET_MULTIMAP_CONTAINER(&t_begin) == _GET_MULTIMAP_CONTAINER(&t_end));
    assert(
        pt_multimapdest->_t_pair._t_firsttypesize == 
            _GET_MULTIMAP_CONTAINER(&t_begin)->_t_pair._t_firsttypesize &&
        pt_multimapdest->_t_pair._t_secondtypesize ==
            _GET_MULTIMAP_CONTAINER(&t_begin)->_t_pair._t_secondtypesize);
    assert(
        strncmp(
            pt_multimapdest->_t_pair._sz_firsttypename,
            _GET_MULTIMAP_CONTAINER(&t_begin)->_t_pair._sz_firsttypename,
            _ELEM_TYPE_NAME_SIZE) == 0 &&
        strncmp(
            pt_multimapdest->_t_pair._sz_secondtypename,
            _GET_MULTIMAP_CONTAINER(&t_begin)->_t_pair._sz_secondtypename,
            _ELEM_TYPE_NAME_SIZE) == 0);

    /* initialize dest multimap with src multimap attribute */
    multimap_init(pt_multimapdest);
    /* insert all element from src to dest */
    if(!multimap_empty(_GET_MULTIMAP_CONTAINER(&t_begin)))
    {
        multimap_insert_range(pt_multimapdest, t_begin, t_end);
    }
}

void multimap_init_copy_range_cmp(
    multimap_t* pt_multimapdest,
    multimap_iterator_t t_begin,
    multimap_iterator_t t_end,
    int (*pfun_key_cmp)(const void*, const void*))
{
    assert(pt_multimapdest != NULL);
    assert(
        _GET_MULTIMAP_CONTAINER_TYPE(&t_begin) == _MULTIMAP_CONTAINER &&
        _GET_MULTIMAP_ITERATOR_TYPE(&t_begin) == _BIDIRECTIONAL_ITERATOR &&
        _GET_MULTIMAP_CONTAINER_TYPE(&t_end) == _MULTIMAP_CONTAINER &&
        _GET_MULTIMAP_ITERATOR_TYPE(&t_end) == _BIDIRECTIONAL_ITERATOR);
    assert(
        _GET_MULTIMAP_CONTAINER(&t_begin) != pt_multimapdest &&
        _GET_MULTIMAP_CONTAINER(&t_end) != pt_multimapdest &&
        _GET_MULTIMAP_CONTAINER(&t_begin) == _GET_MULTIMAP_CONTAINER(&t_end));
    assert(
        pt_multimapdest->_t_pair._t_firsttypesize == 
            _GET_MULTIMAP_CONTAINER(&t_begin)->_t_pair._t_firsttypesize &&
        pt_multimapdest->_t_pair._t_secondtypesize ==
            _GET_MULTIMAP_CONTAINER(&t_begin)->_t_pair._t_secondtypesize);
    assert(
        strncmp(
            pt_multimapdest->_t_pair._sz_firsttypename,
            _GET_MULTIMAP_CONTAINER(&t_begin)->_t_pair._sz_firsttypename,
            _ELEM_TYPE_NAME_SIZE) == 0 &&
        strncmp(
            pt_multimapdest->_t_pair._sz_secondtypename,
            _GET_MULTIMAP_CONTAINER(&t_begin)->_t_pair._sz_secondtypename,
            _ELEM_TYPE_NAME_SIZE) == 0);

    /* initialize dest multimap with src multimap attribute */
    multimap_init(pt_multimapdest);
    pt_multimapdest->_t_pair._pfun_first_cmp = pfun_key_cmp;
    /* insert all element from src to dest */
    if(!multimap_empty(_GET_MULTIMAP_CONTAINER(&t_begin)))
    {
        multimap_insert_range(pt_multimapdest, t_begin, t_end);
    }
}

void multimap_assign(multimap_t* pt_multimapdest, const multimap_t* cpt_multimapsrc)
{
    assert(pt_multimapdest != NULL && cpt_multimapsrc != NULL);
    assert(
        _same_multimap_pair_type(
            &pt_multimapdest->_t_pair, &cpt_multimapsrc->_t_pair));

    /* destroy dest multimap */
    multimap_destroy(pt_multimapdest);
    /* initialize dest multimap with src multimap attribute */
    multimap_init(pt_multimapdest);
    /* insert all element from src to dest */
    if(!multimap_empty(cpt_multimapsrc))
    {
        multimap_insert_range(
            pt_multimapdest, 
            multimap_begin(cpt_multimapsrc), 
            multimap_end(cpt_multimapsrc));
    }
}

void multimap_swap(multimap_t* pt_multimapfirst, multimap_t* pt_multimapsecond)
{
    assert(pt_multimapfirst != NULL && pt_multimapsecond != NULL);
    assert(
        _same_multimap_pair_type(
            &pt_multimapfirst->_t_pair, &pt_multimapsecond->_t_pair));

#ifdef CSTL_MULTIMAP_AVL_TREE
    _avl_tree_swap(
        _GET_MULTIMAP_AVL_TREE(pt_multimapfirst), 
        _GET_MULTIMAP_AVL_TREE(pt_multimapsecond));
#else
    _rb_tree_swap(
        _GET_MULTIMAP_RB_TREE(pt_multimapfirst), 
        _GET_MULTIMAP_RB_TREE(pt_multimapsecond));
#endif
}

bool_t multimap_empty(const multimap_t* cpt_multimap)
{
    assert(cpt_multimap != NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    return _avl_tree_empty(_GET_MULTIMAP_AVL_TREE(cpt_multimap));
#else
    return _rb_tree_empty(_GET_MULTIMAP_RB_TREE(cpt_multimap));
#endif
}

size_t multimap_size(const multimap_t* cpt_multimap)
{
    assert(cpt_multimap != NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    return _avl_tree_size(_GET_MULTIMAP_AVL_TREE(cpt_multimap));
#else
    return _rb_tree_size(_GET_MULTIMAP_RB_TREE(cpt_multimap));
#endif
}

size_t multimap_max_size(const multimap_t* cpt_multimap)
{
    assert(cpt_multimap != NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    return _avl_tree_max_size(_GET_MULTIMAP_AVL_TREE(cpt_multimap));
#else
    return _rb_tree_max_size(_GET_MULTIMAP_RB_TREE(cpt_multimap));
#endif
}

int (*multimap_key_comp(const multimap_t* cpt_multimap))(
    const void*, const void*)
{
    assert(cpt_multimap != NULL);

    return cpt_multimap->_t_pair._pfun_first_cmp;
}

int (*multimap_value_comp(const multimap_t* cpt_multimap))(
    const void*, const void*)
{
    assert(cpt_multimap != NULL);

    return cpt_multimap->_t_pair._pfun_second_cmp;
}

void multimap_clear(multimap_t* pt_multimap)
{
    assert(pt_multimap != NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    _avl_tree_clear(_GET_MULTIMAP_AVL_TREE(pt_multimap));
#else
    _rb_tree_clear(_GET_MULTIMAP_RB_TREE(pt_multimap));
#endif
}

bool_t multimap_equal(
    const multimap_t* cpt_multimapfirst, const multimap_t* cpt_multimapsecond)
{
    assert(cpt_multimapfirst != NULL && cpt_multimapsecond != NULL);

    /* test pair */
    if(cpt_multimapfirst->_t_pair._t_firsttypesize != 
        cpt_multimapsecond->_t_pair._t_firsttypesize || 
       cpt_multimapfirst->_t_pair._t_secondtypesize != 
        cpt_multimapsecond->_t_pair._t_secondtypesize)
    {
        return false;
    }
    if(strncmp(
        cpt_multimapfirst->_t_pair._sz_firsttypename, 
        cpt_multimapsecond->_t_pair._sz_firsttypename, 
        _ELEM_TYPE_NAME_SIZE) != 0 || 
       strncmp(
        cpt_multimapfirst->_t_pair._sz_secondtypename, 
        cpt_multimapsecond->_t_pair._sz_secondtypename, 
        _ELEM_TYPE_NAME_SIZE) != 0)
    {
        return false;
    }
    if(cpt_multimapfirst->_t_pair._pfun_first_cmp != 
        cpt_multimapsecond->_t_pair._pfun_first_cmp || 
       cpt_multimapfirst->_t_pair._pfun_second_cmp != 
        cpt_multimapsecond->_t_pair._pfun_second_cmp)
    {
        return false;
    }
    /* test tree */
#ifdef CSTL_MULTIMAP_AVL_TREE
    return _avl_tree_equal(
        _GET_MULTIMAP_AVL_TREE(cpt_multimapfirst), 
        _GET_MULTIMAP_AVL_TREE(cpt_multimapsecond));
#else
    return _rb_tree_equal(
        _GET_MULTIMAP_RB_TREE(cpt_multimapfirst), 
        _GET_MULTIMAP_RB_TREE(cpt_multimapsecond));
#endif
}

bool_t multimap_not_equal(
    const multimap_t* cpt_multimapfirst, const multimap_t* cpt_multimapsecond)
{
    return !multimap_equal(cpt_multimapfirst, cpt_multimapsecond);
}

bool_t multimap_less(
    const multimap_t* cpt_multimapfirst, const multimap_t* cpt_multimapsecond)
{
    assert(cpt_multimapfirst != NULL && cpt_multimapsecond != NULL);
    assert(
        _same_multimap_pair_type(
            &cpt_multimapfirst->_t_pair, &cpt_multimapsecond->_t_pair));

#ifdef CSTL_MULTIMAP_AVL_TREE
    return _avl_tree_less(
        _GET_MULTIMAP_AVL_TREE(cpt_multimapfirst), 
        _GET_MULTIMAP_AVL_TREE(cpt_multimapsecond));
#else
    return _rb_tree_less(
        _GET_MULTIMAP_RB_TREE(cpt_multimapfirst), 
        _GET_MULTIMAP_RB_TREE(cpt_multimapsecond));
#endif
}

bool_t multimap_less_equal(
    const multimap_t* cpt_multimapfirst, const multimap_t* cpt_multimapsecond)
{
    assert(cpt_multimapfirst != NULL && cpt_multimapsecond != NULL);
    assert(
        _same_multimap_pair_type(
            &cpt_multimapfirst->_t_pair, &cpt_multimapsecond->_t_pair));

#ifdef CSTL_MULTIMAP_AVL_TREE
    return _avl_tree_less_equal(
        _GET_MULTIMAP_AVL_TREE(cpt_multimapfirst), 
        _GET_MULTIMAP_AVL_TREE(cpt_multimapsecond));
#else
    return _rb_tree_less_equal(
        _GET_MULTIMAP_RB_TREE(cpt_multimapfirst), 
        _GET_MULTIMAP_RB_TREE(cpt_multimapsecond));
#endif
}

bool_t multimap_great(
    const multimap_t* cpt_multimapfirst, const multimap_t* cpt_multimapsecond)
{
    assert(cpt_multimapfirst != NULL && cpt_multimapsecond != NULL);
    assert(
        _same_multimap_pair_type(
            &cpt_multimapfirst->_t_pair, &cpt_multimapsecond->_t_pair));

#ifdef CSTL_MULTIMAP_AVL_TREE
    return _avl_tree_great(
        _GET_MULTIMAP_AVL_TREE(cpt_multimapfirst), 
        _GET_MULTIMAP_AVL_TREE(cpt_multimapsecond));
#else
    return _rb_tree_great(
        _GET_MULTIMAP_RB_TREE(cpt_multimapfirst), 
        _GET_MULTIMAP_RB_TREE(cpt_multimapsecond));
#endif
}

bool_t multimap_great_equal(
    const multimap_t* cpt_multimapfirst, const multimap_t* cpt_multimapsecond)
{
    assert(cpt_multimapfirst != NULL && cpt_multimapsecond != NULL);
    assert(
        _same_multimap_pair_type(
            &cpt_multimapfirst->_t_pair, &cpt_multimapsecond->_t_pair));

#ifdef CSTL_MULTIMAP_AVL_TREE
    return _avl_tree_great_equal(
        _GET_MULTIMAP_AVL_TREE(cpt_multimapfirst), 
        _GET_MULTIMAP_AVL_TREE(cpt_multimapsecond));
#else
    return _rb_tree_great_equal(
        _GET_MULTIMAP_RB_TREE(cpt_multimapfirst), 
        _GET_MULTIMAP_RB_TREE(cpt_multimapsecond));
#endif
}

multimap_iterator_t multimap_begin(const multimap_t* cpt_multimap)
{
    multimap_iterator_t t_newiterator;

    assert(cpt_multimap != NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    t_newiterator = _avl_tree_begin(_GET_MULTIMAP_AVL_TREE(cpt_multimap));
#else
    t_newiterator = _rb_tree_begin(_GET_MULTIMAP_RB_TREE(cpt_multimap));
#endif

    _GET_CONTAINER(&t_newiterator) = (multimap_t*)cpt_multimap;
    _GET_MULTIMAP_CONTAINER_TYPE(&t_newiterator) = _MULTIMAP_CONTAINER;
    _GET_MULTIMAP_ITERATOR_TYPE(&t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

multimap_iterator_t multimap_end(const multimap_t* cpt_multimap)
{
    multimap_iterator_t t_newiterator;

    assert(cpt_multimap != NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    t_newiterator = _avl_tree_end(_GET_MULTIMAP_AVL_TREE(cpt_multimap));
#else
    t_newiterator = _rb_tree_end(_GET_MULTIMAP_RB_TREE(cpt_multimap));
#endif

    _GET_CONTAINER(&t_newiterator) = (multimap_t*)cpt_multimap;
    _GET_MULTIMAP_CONTAINER_TYPE(&t_newiterator) = _MULTIMAP_CONTAINER;
    _GET_MULTIMAP_ITERATOR_TYPE(&t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

multimap_reverse_iterator_t multimap_rbegin(const multimap_t* cpt_multimap)
{
    multimap_reverse_iterator_t t_newiterator;

    assert(cpt_multimap != NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    t_newiterator = _avl_tree_rbegin(_GET_MULTIMAP_AVL_TREE(cpt_multimap));
#else
    t_newiterator = _rb_tree_rbegin(_GET_MULTIMAP_RB_TREE(cpt_multimap));
#endif

    _GET_CONTAINER(&t_newiterator) = (multimap_t*)cpt_multimap;
    _GET_MULTIMAP_CONTAINER_TYPE(&t_newiterator) = _MULTIMAP_CONTAINER;
    _GET_MULTIMAP_ITERATOR_TYPE(&t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

multimap_reverse_iterator_t multimap_rend(const multimap_t* cpt_multimap)
{
    multimap_reverse_iterator_t t_newiterator;

    assert(cpt_multimap != NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    t_newiterator = _avl_tree_rend(_GET_MULTIMAP_AVL_TREE(cpt_multimap));
#else
    t_newiterator = _rb_tree_rend(_GET_MULTIMAP_RB_TREE(cpt_multimap));
#endif

    _GET_CONTAINER(&t_newiterator) = (multimap_t*)cpt_multimap;
    _GET_MULTIMAP_CONTAINER_TYPE(&t_newiterator) = _MULTIMAP_CONTAINER;
    _GET_MULTIMAP_ITERATOR_TYPE(&t_newiterator) = _BIDIRECTIONAL_ITERATOR;

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
    _get_varg_value(
        cpt_multimap->_t_pair.first, 
        val_elemlist, 
        cpt_multimap->_t_pair._t_firsttypesize,
        cpt_multimap->_t_pair._sz_firsttypename);
    /* find key in tree */
#ifdef CSTL_MULTIMAP_AVL_TREE
    t_iterator = _avl_tree_find(
        _GET_MULTIMAP_AVL_TREE(cpt_multimap), &cpt_multimap->_t_pair);
#else
    t_iterator = _rb_tree_find(
        _GET_MULTIMAP_RB_TREE(cpt_multimap), &cpt_multimap->_t_pair);
#endif

    _GET_CONTAINER(&t_iterator) = (multimap_t*)cpt_multimap;
    _GET_MULTIMAP_CONTAINER_TYPE(&t_iterator) = _MULTIMAP_CONTAINER;
    _GET_MULTIMAP_ITERATOR_TYPE(&t_iterator) = _BIDIRECTIONAL_ITERATOR;

    return t_iterator;
}

size_t _multimap_count(const multimap_t* cpt_multimap, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, cpt_multimap);
    return _multimap_count_varg(cpt_multimap, val_elemlist);
}

size_t _multimap_count_varg(
    const multimap_t* cpt_multimap, va_list val_elemlist)
{
    assert(cpt_multimap != NULL);

    _get_varg_value(
        cpt_multimap->_t_pair.first, 
        val_elemlist, 
        cpt_multimap->_t_pair._t_firsttypesize,
        cpt_multimap->_t_pair._sz_firsttypename);
#ifdef CSTL_MULTIMAP_AVL_TREE
    return _avl_tree_count(
        _GET_MULTIMAP_AVL_TREE(cpt_multimap), &cpt_multimap->_t_pair);
#else
    return _rb_tree_count(
        _GET_MULTIMAP_RB_TREE(cpt_multimap), &cpt_multimap->_t_pair);
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

    _get_varg_value(
        cpt_multimap->_t_pair.first, 
        val_elemlist, 
        cpt_multimap->_t_pair._t_firsttypesize,
        cpt_multimap->_t_pair._sz_firsttypename);
#ifdef CSTL_MULTIMAP_AVL_TREE
    t_iterator = _avl_tree_lower_bound(
        _GET_MULTIMAP_AVL_TREE(cpt_multimap), &cpt_multimap->_t_pair);
#else
    t_iterator = _rb_tree_lower_bound(
        _GET_MULTIMAP_RB_TREE(cpt_multimap), &cpt_multimap->_t_pair);
#endif

    _GET_CONTAINER(&t_iterator) = (multimap_t*)cpt_multimap;
    _GET_MULTIMAP_CONTAINER_TYPE(&t_iterator) = _MULTIMAP_CONTAINER;
    _GET_MULTIMAP_ITERATOR_TYPE(&t_iterator) = _BIDIRECTIONAL_ITERATOR;

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

    _get_varg_value(
        cpt_multimap->_t_pair.first, 
        val_elemlist, 
        cpt_multimap->_t_pair._t_firsttypesize,
        cpt_multimap->_t_pair._sz_firsttypename);
#ifdef CSTL_MULTIMAP_AVL_TREE
    t_iterator = _avl_tree_upper_bound(
        _GET_MULTIMAP_AVL_TREE(cpt_multimap), &cpt_multimap->_t_pair);
#else
    t_iterator = _rb_tree_upper_bound(
        _GET_MULTIMAP_RB_TREE(cpt_multimap), &cpt_multimap->_t_pair);
#endif

    _GET_CONTAINER(&t_iterator) = (multimap_t*)cpt_multimap;
    _GET_MULTIMAP_CONTAINER_TYPE(&t_iterator) = _MULTIMAP_CONTAINER;
    _GET_MULTIMAP_ITERATOR_TYPE(&t_iterator) = _BIDIRECTIONAL_ITERATOR;

    return t_iterator;
}

pair_t _multimap_equal_range(const multimap_t* cpt_multimap, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, cpt_multimap);
    return _multimap_equal_range_varg(cpt_multimap, val_elemlist);
}

pair_t _multimap_equal_range_varg(
    const multimap_t* cpt_multimap, va_list val_elemlist)
{
    multimap_iterator_t t_first;
    multimap_iterator_t t_second;
    pair_t              t_pair;
#ifdef CSTL_MULTIMAP_AVL_TREE
    avl_tree_result_pair_t t_avlresult;
#else
    rb_tree_result_pair_t  t_rbresult;
#endif

    assert(cpt_multimap != NULL);

    _get_varg_value(
        cpt_multimap->_t_pair.first, 
        val_elemlist, 
        cpt_multimap->_t_pair._t_firsttypesize,
        cpt_multimap->_t_pair._sz_firsttypename);
#ifdef CSTL_MULTIMAP_AVL_TREE
    t_avlresult = _avl_tree_equal_range(
        _GET_MULTIMAP_AVL_TREE(cpt_multimap), &cpt_multimap->_t_pair);
    t_first = t_avlresult._t_first;
    t_second = t_avlresult._t_second._t_iterator;
#else
    t_rbresult = _rb_tree_equal_range(
        _GET_MULTIMAP_RB_TREE(cpt_multimap), &cpt_multimap->_t_pair);
    t_first = t_rbresult._t_first;
    t_second = t_rbresult._t_second._t_iterator;
#endif

    _GET_CONTAINER(&t_first) = (multimap_t*)cpt_multimap;
    _GET_MULTIMAP_CONTAINER_TYPE(&t_first) = _MULTIMAP_CONTAINER;
    _GET_MULTIMAP_ITERATOR_TYPE(&t_first) = _BIDIRECTIONAL_ITERATOR;
    _GET_CONTAINER(&t_second) = (multimap_t*)cpt_multimap;
    _GET_MULTIMAP_CONTAINER_TYPE(&t_second) = _MULTIMAP_CONTAINER;
    _GET_MULTIMAP_ITERATOR_TYPE(&t_second) = _BIDIRECTIONAL_ITERATOR;

    t_pair = create_pair(multimap_iterator_t, multimap_iterator_t);
    pair_init(&t_pair);
    memcpy(t_pair.first, &t_first, t_pair._t_firsttypesize);
    memcpy(t_pair.second, &t_second, t_pair._t_secondtypesize);

    return t_pair;
}

multimap_iterator_t multimap_insert(
    multimap_t* pt_multimap, const pair_t* cpt_pair)
{
    pair_t              t_elempair;
    multimap_iterator_t t_iterator;

    assert(pt_multimap != NULL && cpt_pair != NULL);
    assert(_same_multimap_pair_type(&pt_multimap->_t_pair, cpt_pair));

    /* initialize the new pair */
    t_elempair = _create_pair(
        pt_multimap->_t_pair._t_firsttypesize, 
        pt_multimap->_t_pair._sz_firsttypename,
        pt_multimap->_t_pair._t_secondtypesize, 
        pt_multimap->_t_pair._sz_secondtypename);
    pair_init(&t_elempair);
    memcpy(t_elempair.first, cpt_pair->first, t_elempair._t_firsttypesize);
    memcpy(t_elempair.second, cpt_pair->second, t_elempair._t_secondtypesize);

    /* insert pair into tree */
#ifdef CSTL_MULTIMAP_AVL_TREE
    t_iterator = _avl_tree_insert_equal(
        _GET_MULTIMAP_AVL_TREE(pt_multimap), &t_elempair);
#else
    t_iterator = _rb_tree_insert_equal(
        _GET_MULTIMAP_RB_TREE(pt_multimap), &t_elempair);
#endif
    /*
     * There is no need for destroy the elempair, because the pair is copied 
     * to the tree, and it is destroied by tree when tree is desroied.
     */
    _GET_CONTAINER(&t_iterator) = pt_multimap;
    _GET_MULTIMAP_CONTAINER_TYPE(&t_iterator) = _MULTIMAP_CONTAINER;
    _GET_MULTIMAP_ITERATOR_TYPE(&t_iterator) = _BIDIRECTIONAL_ITERATOR;

    return t_iterator;
}

multimap_iterator_t multimap_insert_hint(
    multimap_t* pt_multimap, multimap_iterator_t t_hint, const pair_t* cpt_pair)
{
    pair_t t_elempair;

    assert(pt_multimap != NULL && cpt_pair != NULL);
    assert(_same_multimap_pair_type(&pt_multimap->_t_pair, cpt_pair));

    /* initialize the new pair */
    t_elempair = _create_pair(
        pt_multimap->_t_pair._t_firsttypesize, pt_multimap->_t_pair._sz_firsttypename,
        pt_multimap->_t_pair._t_secondtypesize, pt_multimap->_t_pair._sz_secondtypename);
    pair_init(&t_elempair);
    memcpy(t_elempair.first, cpt_pair->first, t_elempair._t_firsttypesize);
    memcpy(t_elempair.second, cpt_pair->second, t_elempair._t_secondtypesize);

    /* insert pair into tree */
#ifdef CSTL_MULTIMAP_AVL_TREE
    t_hint = _avl_tree_insert_equal(_GET_MULTIMAP_AVL_TREE(pt_multimap), &t_elempair);
#else
    t_hint = _rb_tree_insert_equal(_GET_MULTIMAP_RB_TREE(pt_multimap), &t_elempair);
#endif
    /*
     * There is no need for destroy the elempair, because the pair is copied 
     * to the tree, and it is destroied by tree when tree is desroied.
     */
    _GET_CONTAINER(&t_hint) = pt_multimap;
    _GET_MULTIMAP_CONTAINER_TYPE(&t_hint) = _MULTIMAP_CONTAINER;
    _GET_MULTIMAP_ITERATOR_TYPE(&t_hint) = _BIDIRECTIONAL_ITERATOR;

    return t_hint;
}

void multimap_insert_range(
    multimap_t* pt_multimap, multimap_iterator_t t_begin, multimap_iterator_t t_end)
{
    multimap_iterator_t t_iterator;

    assert(pt_multimap != NULL);
    assert(
        _GET_MULTIMAP_CONTAINER_TYPE(&t_begin) == _MULTIMAP_CONTAINER &&
        _GET_MULTIMAP_ITERATOR_TYPE(&t_begin) == _BIDIRECTIONAL_ITERATOR &&
        _GET_MULTIMAP_CONTAINER_TYPE(&t_end) == _MULTIMAP_CONTAINER &&
        _GET_MULTIMAP_ITERATOR_TYPE(&t_end) == _BIDIRECTIONAL_ITERATOR);
    assert(
        _GET_MULTIMAP_CONTAINER(&t_begin) != pt_multimap &&
        _GET_MULTIMAP_CONTAINER(&t_end) != pt_multimap &&
        _GET_MULTIMAP_CONTAINER(&t_begin) == _GET_MULTIMAP_CONTAINER(&t_end));

    for(t_iterator = t_begin;
        !iterator_equal(&t_iterator, t_end);
        iterator_next(&t_iterator))
    {
        multimap_insert(
            pt_multimap, (pair_t*)iterator_get_pointer(&t_iterator));
    }
}

void multimap_erase_pos(multimap_t* pt_multimap, multimap_iterator_t t_pos)
{
    assert(pt_multimap != NULL);
    assert(
        _GET_MULTIMAP_CONTAINER_TYPE(&t_pos) == _MULTIMAP_CONTAINER &&
        _GET_MULTIMAP_ITERATOR_TYPE(&t_pos) == _BIDIRECTIONAL_ITERATOR &&
        _GET_MULTIMAP_CONTAINER(&t_pos) == pt_multimap);

#ifdef CSTL_MULTIMAP_AVL_TREE
    _avl_tree_erase_pos(_GET_MULTIMAP_AVL_TREE(pt_multimap), t_pos);
#else
    _rb_tree_erase_pos(_GET_MULTIMAP_RB_TREE(pt_multimap), t_pos);
#endif
}

void multimap_erase_range(
    multimap_t* pt_multimap, 
    multimap_iterator_t t_begin, 
    multimap_iterator_t t_end)
{
    assert(pt_multimap != NULL);
    assert(
        _GET_MULTIMAP_CONTAINER_TYPE(&t_begin) == _MULTIMAP_CONTAINER &&
        _GET_MULTIMAP_ITERATOR_TYPE(&t_begin) == _BIDIRECTIONAL_ITERATOR &&
        _GET_MULTIMAP_CONTAINER_TYPE(&t_end) == _MULTIMAP_CONTAINER &&
        _GET_MULTIMAP_ITERATOR_TYPE(&t_end) == _BIDIRECTIONAL_ITERATOR);
    assert(
        _GET_MULTIMAP_CONTAINER(&t_begin) == pt_multimap &&
        _GET_MULTIMAP_CONTAINER(&t_end) == pt_multimap);

#ifdef CSTL_MULTIMAP_AVL_TREE
    _avl_tree_erase_range(_GET_MULTIMAP_AVL_TREE(pt_multimap), t_begin, t_end);
#else
    _rb_tree_erase_range(_GET_MULTIMAP_RB_TREE(pt_multimap), t_begin, t_end);
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
    _get_varg_value(
        pt_multimap->_t_pair.first, 
        val_elemlist, 
        pt_multimap->_t_pair._t_firsttypesize,
        pt_multimap->_t_pair._sz_firsttypename);

#ifdef CSTL_MULTIMAP_AVL_TREE
    return _avl_tree_erase(_GET_MULTIMAP_AVL_TREE(pt_multimap), &pt_multimap->_t_pair);
#else
    return _rb_tree_erase(_GET_MULTIMAP_RB_TREE(pt_multimap), &pt_multimap->_t_pair);
#endif
}

/** local function implementation section **/
#ifndef NDEBUG
static bool_t _same_multimap_pair_type(
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
        cpt_pairfirst->_pfun_first_cmp == 
            cpt_pairsecond->_pfun_first_cmp &&
        cpt_pairfirst->_pfun_second_cmp == 
            cpt_pairsecond->_pfun_second_cmp);

    return true;
}
#endif /* NDEBUG */

static int _multimap_cmp(const void* cpv_firstelem, const void* cpv_secondelem)
{
    pair_t* pt_first = NULL;
    pair_t* pt_second = NULL;

    assert(cpv_firstelem != NULL && cpv_secondelem != NULL);

    pt_first = (pair_t*)cpv_firstelem;
    pt_second = (pair_t*)cpv_secondelem;

    assert(_same_multimap_pair_type(pt_first, pt_second));

    if(pt_first->_pfun_first_cmp != NULL)
    {
        return (*pt_first->_pfun_first_cmp)(pt_first->first, pt_second->first);
    }
    else
    {
        return memcmp(
            pt_first->first, pt_second->first, pt_first->_t_firsttypesize);
    }
}

static void _multimap_destroy_elem(void* pv_value)
{
    assert(pv_value != NULL);

    pair_destroy((pair_t*)pv_value);
}

/** eof **/

