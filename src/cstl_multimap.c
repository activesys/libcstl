/*
 *  The implementation of multimap.
 *  Copyright (C)  2008,2009,2010,2011  Wangbo
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
#include <cstl/cstl_def.h>
#include <cstl/cstl_alloc.h>
#include <cstl/cstl_types.h>
#include <cstl/cstl_iterator.h>

#ifdef CSTL_MULTIMAP_AVL_TREE
#include <cstl/cstl_avl_tree_iterator.h>
#include <cstl/cstl_avl_tree_private.h>
#include <cstl/cstl_avl_tree.h>
#else
#include <cstl/cstl_rb_tree_iterator.h>
#include <cstl/cstl_rb_tree_private.h>
#include <cstl/cstl_rb_tree.h>
#endif
#include <cstl/cutility.h>
#include <cstl/cstring.h>

#include <cstl/cstl_multimap_iterator.h>
#include <cstl/cstl_multimap_private.h>
#include <cstl/cstl_multimap.h>

#include "cstl_multimap_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/

/* multimap function */
void multimap_init(multimap_t* pt_multimap)
{
    assert(pt_multimap != NULL);

    /* initialize the pair */
    pair_init(&pt_multimap->_pair_temp);
    /* initialize the tree */
#ifdef CSTL_MULTIMAP_AVL_TREE
    _avl_tree_init(&pt_multimap->_t_tree, _multimap_value_compare);
#else
    _rb_tree_init(&pt_multimap->_t_tree, _multimap_value_compare);
#endif
}

void multimap_init_ex(multimap_t* pt_multimap, binary_function_t t_keycompare)
{
    assert(pt_multimap != NULL);

    pt_multimap->_bfun_keycompare = t_keycompare;
    pt_multimap->_pair_temp._bfun_mapkeycompare = t_keycompare;

    pair_init(&pt_multimap->_pair_temp);
#ifdef CSTL_MULTIMAP_AVL_TREE
    _avl_tree_init(&pt_multimap->_t_tree, _multimap_value_compare);
#else
    _rb_tree_init(&pt_multimap->_t_tree, _multimap_value_compare);
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

    /* initialize dest multimap with src multimap attribute */
    multimap_init(pt_multimapdest);
    pt_multimapdest->_bfun_keycompare = cpt_multimapsrc->_bfun_keycompare;
    pt_multimapdest->_bfun_valuecompare = cpt_multimapsrc->_bfun_valuecompare;
    pt_multimapdest->_pair_temp._bfun_mapkeycompare = cpt_multimapsrc->_pair_temp._bfun_mapkeycompare;
    pt_multimapdest->_pair_temp._bfun_mapvaluecompare = cpt_multimapsrc->_pair_temp._bfun_mapvaluecompare;

    assert(_multimap_same_pair_type_ex(&pt_multimapdest->_pair_temp, &cpt_multimapsrc->_pair_temp));
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
    multimap_iterator_t t_begin, multimap_iterator_t t_end, binary_function_t t_keycompare)
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
    multimap_init_ex(pt_multimapdest, t_keycompare);
    /* insert all element from src to dest */
    if(!multimap_empty(_GET_MULTIMAP_CONTAINER(t_begin)))
    {
        multimap_insert_range(pt_multimapdest, t_begin, t_end);
    }
}

void multimap_assign(multimap_t* pt_multimapdest, const multimap_t* cpt_multimapsrc)
{
    assert(pt_multimapdest != NULL && cpt_multimapsrc != NULL);
    assert(_multimap_same_pair_type_ex(&pt_multimapdest->_pair_temp, &cpt_multimapsrc->_pair_temp));

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
    assert(_multimap_same_pair_type_ex(&pt_multimapfirst->_pair_temp, &pt_multimapsecond->_pair_temp));

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

binary_function_t multimap_key_comp(const multimap_t* cpt_multimap)
{
    assert(cpt_multimap != NULL);

    if(cpt_multimap->_bfun_keycompare != NULL)
    {
        return cpt_multimap->_bfun_keycompare;
    }
    else
    {
        return _GET_MULTIMAP_FIRST_TYPE_LESS_FUNCTION(cpt_multimap);
    }
}

binary_function_t multimap_value_comp(const multimap_t* cpt_multimap)
{
#ifdef NDEBUG
    void* pv_avoidwarning = (void*)cpt_multimap;
    pv_avoidwarning = NULL;
#endif
    assert(cpt_multimap != NULL);

    return _multimap_value_compare;
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
    assert(_multimap_same_pair_type_ex(&cpt_multimapfirst->_pair_temp, &cpt_multimapsecond->_pair_temp));

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
    assert(_multimap_same_pair_type_ex(&cpt_multimapfirst->_pair_temp, &cpt_multimapsecond->_pair_temp));

#ifdef CSTL_MULTIMAP_AVL_TREE
    return _avl_tree_less_equal(&cpt_multimapfirst->_t_tree, &cpt_multimapsecond->_t_tree);
#else
    return _rb_tree_less_equal(&cpt_multimapfirst->_t_tree, &cpt_multimapsecond->_t_tree);
#endif
}

bool_t multimap_greater(
    const multimap_t* cpt_multimapfirst, const multimap_t* cpt_multimapsecond)
{
    assert(cpt_multimapfirst != NULL && cpt_multimapsecond != NULL);
    assert(_multimap_same_pair_type_ex(&cpt_multimapfirst->_pair_temp, &cpt_multimapsecond->_pair_temp));

#ifdef CSTL_MULTIMAP_AVL_TREE
    return _avl_tree_greater(&cpt_multimapfirst->_t_tree, &cpt_multimapsecond->_t_tree);
#else
    return _rb_tree_greater(&cpt_multimapfirst->_t_tree, &cpt_multimapsecond->_t_tree);
#endif
}

bool_t multimap_greater_equal(
    const multimap_t* cpt_multimapfirst, const multimap_t* cpt_multimapsecond)
{
    assert(cpt_multimapfirst != NULL && cpt_multimapsecond != NULL);
    assert(_multimap_same_pair_type_ex(&cpt_multimapfirst->_pair_temp, &cpt_multimapsecond->_pair_temp));

#ifdef CSTL_MULTIMAP_AVL_TREE
    return _avl_tree_greater_equal(&cpt_multimapfirst->_t_tree, &cpt_multimapsecond->_t_tree);
#else
    return _rb_tree_greater_equal(&cpt_multimapfirst->_t_tree, &cpt_multimapsecond->_t_tree);
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

multimap_iterator_t multimap_insert(
    multimap_t* pt_multimap, const pair_t* cpt_pair)
{
    multimap_iterator_t t_iterator;

    assert(pt_multimap != NULL && cpt_pair != NULL);

    ((pair_t*)cpt_pair)->_bfun_mapkeycompare = pt_multimap->_bfun_keycompare;
    ((pair_t*)cpt_pair)->_bfun_mapvaluecompare = pt_multimap->_bfun_valuecompare;

    assert(_multimap_same_pair_type_ex(&pt_multimap->_pair_temp, cpt_pair));

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

    ((pair_t*)cpt_pair)->_bfun_mapkeycompare = pt_multimap->_bfun_keycompare;
    ((pair_t*)cpt_pair)->_bfun_mapvaluecompare = pt_multimap->_bfun_valuecompare;

    assert(_multimap_same_pair_type_ex(&pt_multimap->_pair_temp, cpt_pair));

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

/** local function implementation section **/

/** eof **/

