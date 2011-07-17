/*
 *  The implementation of multiset.
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
#include <cstl/cstl_iterator_private.h>

#ifdef CSTL_MULTISET_AVL_TREE
#include <cstl/cstl_avl_tree_iterator.h>
#include <cstl/cstl_avl_tree_private.h>
#include <cstl/cstl_avl_tree.h>
#else
#include <cstl/cstl_rb_tree_iterator.h>
#include <cstl/cstl_rb_tree_private.h>
#include <cstl/cstl_rb_tree.h>
#endif

#include <cstl/cstl_multiset_iterator.h>
#include <cstl/cstl_multiset_private.h>
#include <cstl/cstl_multiset.h>

#include "cstl_multiset_aux.h"

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

/** local function implementation section **/

/** eof **/

