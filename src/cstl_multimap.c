/*
 *  The implementation of multimap.
 *  Copyright (C)  2008 - 2013  Wangbo
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
#include <cstl/citerator.h>
#include <cstl/cstring.h>
#include <cstl/cmap.h>

#include "cstl_multimap_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Initialize multimap container.
 */
void multimap_init(multimap_t* pmmap_map)
{
    assert(pmmap_map != NULL);
    assert(_pair_is_created(&pmmap_map->_pair_temp));

    /* initialize the pair */
    pair_init(&pmmap_map->_pair_temp);
    /* initialize the tree */
#ifdef CSTL_MULTIMAP_AVL_TREE
    _avl_tree_init(&pmmap_map->_t_tree, _multimap_value_compare);
#else
    _rb_tree_init(&pmmap_map->_t_tree, _multimap_value_compare);
#endif
}

/**
 * Initialize multimap container with user define compare function.
 */
void multimap_init_ex(multimap_t* pmmap_map, bfun_t bfun_keycompare)
{
    assert(pmmap_map != NULL);
    assert(_pair_is_created(&pmmap_map->_pair_temp));

    pair_init(&pmmap_map->_pair_temp);
    pmmap_map->_bfun_keycompare = bfun_keycompare;
    pmmap_map->_pair_temp._bfun_mapkeycompare = bfun_keycompare;

#ifdef CSTL_MULTIMAP_AVL_TREE
    _avl_tree_init(&pmmap_map->_t_tree, _multimap_value_compare);
#else
    _rb_tree_init(&pmmap_map->_t_tree, _multimap_value_compare);
#endif
}

/**
 * Destroy multimap.
 */
void multimap_destroy(multimap_t* pmmap_map)
{
    _multimap_destroy_auxiliary(pmmap_map);
    free(pmmap_map);
}

/**
 * Initialize multimap container with multimap.
 */
void multimap_init_copy(multimap_t* pmmap_dest, const multimap_t* cpmmap_src)
{
    assert(pmmap_dest != NULL);
    assert(cpmmap_src != NULL);
    assert(_pair_is_created(&pmmap_dest->_pair_temp));
    assert(_pair_is_inited(&cpmmap_src->_pair_temp));

    /* initialize dest multimap with src multimap attribute */
    multimap_init(pmmap_dest);
    pmmap_dest->_bfun_keycompare = cpmmap_src->_bfun_keycompare;
    pmmap_dest->_bfun_valuecompare = cpmmap_src->_bfun_valuecompare;
    pmmap_dest->_pair_temp._bfun_mapkeycompare = cpmmap_src->_pair_temp._bfun_mapkeycompare;
    pmmap_dest->_pair_temp._bfun_mapvaluecompare = cpmmap_src->_pair_temp._bfun_mapvaluecompare;

    assert(_multimap_same_pair_type_ex(&pmmap_dest->_pair_temp, &cpmmap_src->_pair_temp));
    /* insert all element from src to dest */
    if (!multimap_empty(cpmmap_src)) {
        multimap_insert_range(pmmap_dest, multimap_begin(cpmmap_src), multimap_end(cpmmap_src));
    }
}

/**
 * Initialize multimap container with specific range.
 */
void multimap_init_copy_range(multimap_t* pmmap_dest, iterator_t it_begin, iterator_t it_end)
{
    assert(pmmap_dest != NULL);
    assert(_pair_is_created(&pmmap_dest->_pair_temp));
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));

    multimap_init(pmmap_dest);
    multimap_insert_range(pmmap_dest, it_begin, it_end);
}

/**
 * Initialize multimap container with specific array.
 */
void multimap_init_copy_array(multimap_t* pmmap_dest, const void* cpv_array, size_t t_count)
{
    assert(pmmap_dest != NULL);
    assert(_pair_is_created(&pmmap_dest->_pair_temp));
    assert(cpv_array != NULL);

    multimap_init(pmmap_dest);
    multimap_insert_array(pmmap_dest, cpv_array, t_count);
}

/**
 * Initialize multimap container with specific range and compare function.
 */
void multimap_init_copy_range_ex(
    multimap_t* pmmap_dest, iterator_t it_begin, iterator_t it_end, bfun_t bfun_keycompare)
{
    assert(pmmap_dest != NULL);
    assert(_pair_is_created(&pmmap_dest->_pair_temp));
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));

    multimap_init_ex(pmmap_dest, bfun_keycompare);
    multimap_insert_range(pmmap_dest, it_begin, it_end);
}

/**
 * Initialize multimap container with specific array and compare function.
 */
void multimap_init_copy_array_ex(
    multimap_t* pmmap_dest, const void* cpv_array, size_t t_count, bfun_t bfun_keycompare)
{
    assert(pmmap_dest != NULL);
    assert(_pair_is_created(&pmmap_dest->_pair_temp));
    assert(cpv_array != NULL);

    multimap_init_ex(pmmap_dest, bfun_keycompare);
    multimap_insert_array(pmmap_dest, cpv_array, t_count);
}

/**
 * Assign multimap container.
 */
void multimap_assign(multimap_t* pmmap_dest, const multimap_t* cpmmap_src)
{
    assert(pmmap_dest != NULL);
    assert(cpmmap_src != NULL);
    assert(_pair_is_inited(&pmmap_dest->_pair_temp));
    assert(_pair_is_inited(&cpmmap_src->_pair_temp));
    assert(_multimap_same_pair_type_ex(&pmmap_dest->_pair_temp, &cpmmap_src->_pair_temp));

    multimap_clear(pmmap_dest);
    /* insert all element from src to dest */
    if (!multimap_empty(cpmmap_src)) {
        multimap_insert_range(pmmap_dest, multimap_begin(cpmmap_src), multimap_end(cpmmap_src));
    }
}

/**
 * Swap the datas of first multimap and second multimap.
 */
void multimap_swap(multimap_t* pmmap_first, multimap_t* pmmap_second)
{
    assert(pmmap_first != NULL);
    assert(pmmap_second != NULL);
    assert(_pair_is_inited(&pmmap_first->_pair_temp));
    assert(_pair_is_inited(&pmmap_second->_pair_temp));
    assert(_multimap_same_pair_type_ex(&pmmap_first->_pair_temp, &pmmap_second->_pair_temp));

#ifdef CSTL_MULTIMAP_AVL_TREE
    _avl_tree_swap(&pmmap_first->_t_tree, &pmmap_second->_t_tree);
#else
    _rb_tree_swap(&pmmap_first->_t_tree, &pmmap_second->_t_tree);
#endif
}

/**
 * Test if an multimap is empty.
 */
bool_t multimap_empty(const multimap_t* cpmmap_map)
{
    assert(cpmmap_map != NULL);
    assert(_pair_is_inited(&cpmmap_map->_pair_temp));

#ifdef CSTL_MULTIMAP_AVL_TREE
    return _avl_tree_empty(&cpmmap_map->_t_tree);
#else
    return _rb_tree_empty(&cpmmap_map->_t_tree);
#endif
}

/**
 * Get the number of elements int the multimap.
 */
size_t multimap_size(const multimap_t* cpmmap_map)
{
    assert(cpmmap_map != NULL);
    assert(_pair_is_inited(&cpmmap_map->_pair_temp));

#ifdef CSTL_MULTIMAP_AVL_TREE
    return _avl_tree_size(&cpmmap_map->_t_tree);
#else
    return _rb_tree_size(&cpmmap_map->_t_tree);
#endif
}

/**
 * Get the maximum number of elements int the multimap.
 */
size_t multimap_max_size(const multimap_t* cpmmap_map)
{
    assert(cpmmap_map != NULL);
    assert(_pair_is_inited(&cpmmap_map->_pair_temp));

#ifdef CSTL_MULTIMAP_AVL_TREE
    return _avl_tree_max_size(&cpmmap_map->_t_tree);
#else
    return _rb_tree_max_size(&cpmmap_map->_t_tree);
#endif
}

/**
 * Return the compare function of key.
 */
bfun_t multimap_key_comp(const multimap_t* cpmmap_map)
{
    assert(cpmmap_map != NULL);
    assert(_pair_is_inited(&cpmmap_map->_pair_temp));

    if (cpmmap_map->_bfun_keycompare != NULL) {
        return cpmmap_map->_bfun_keycompare;
    } else {
        return _GET_MULTIMAP_FIRST_TYPE_LESS_FUNCTION(cpmmap_map);
    }
}

/**
 * Return the compare function of value.
 */
bfun_t multimap_value_comp(const multimap_t* cpmmap_map)
{
#ifdef NDEBUG
    void* pv_avoidwarning = (void*)cpmmap_map;
    pv_avoidwarning = NULL;
#endif
    assert(cpmmap_map != NULL);
    assert(_pair_is_inited(&cpmmap_map->_pair_temp));

    return _multimap_value_compare;
}

/**
 * Erases all the elements of an multimap.
 */
void multimap_clear(multimap_t* pmmap_map)
{
    assert(pmmap_map != NULL);
    assert(_pair_is_inited(&pmmap_map->_pair_temp));

#ifdef CSTL_MULTIMAP_AVL_TREE
    _avl_tree_clear(&pmmap_map->_t_tree);
#else
    _rb_tree_clear(&pmmap_map->_t_tree);
#endif
}

/**
 * Tests if the two multimap are equal.
 */
bool_t multimap_equal(const multimap_t* cpmmap_first, const multimap_t* cpmmap_second)
{
    assert(cpmmap_first != NULL);
    assert(cpmmap_second != NULL);
    assert(_pair_is_inited(&cpmmap_first->_pair_temp));
    assert(_pair_is_inited(&cpmmap_second->_pair_temp));

    if (cpmmap_first->_bfun_keycompare != cpmmap_second->_bfun_keycompare) {
        return false;
    }
#ifdef CSTL_MULTIMAP_AVL_TREE
    return _avl_tree_equal(&cpmmap_first->_t_tree, &cpmmap_second->_t_tree);
#else
    return _rb_tree_equal(&cpmmap_first->_t_tree, &cpmmap_second->_t_tree);
#endif
}

/**
 * Tests if the two multimap are not equal.
 */
bool_t multimap_not_equal(const multimap_t* cpmmap_first, const multimap_t* cpmmap_second)
{
    assert(cpmmap_first != NULL);
    assert(cpmmap_second != NULL);
    assert(_pair_is_inited(&cpmmap_first->_pair_temp));
    assert(_pair_is_inited(&cpmmap_second->_pair_temp));

    if (cpmmap_first->_bfun_keycompare != cpmmap_second->_bfun_keycompare) {
        return true;
    }
#ifdef CSTL_MULTIMAP_AVL_TREE
    return _avl_tree_not_equal(&cpmmap_first->_t_tree, &cpmmap_second->_t_tree);
#else
    return _rb_tree_not_equal(&cpmmap_first->_t_tree, &cpmmap_second->_t_tree);
#endif
}

/**
 * Tests if the first multimap is less than the second multimap.
 */
bool_t multimap_less(const multimap_t* cpmmap_first, const multimap_t* cpmmap_second)
{
    assert(cpmmap_first != NULL);
    assert(cpmmap_second != NULL);
    assert(_pair_is_inited(&cpmmap_first->_pair_temp));
    assert(_pair_is_inited(&cpmmap_second->_pair_temp));
    assert(_multimap_same_pair_type_ex(&cpmmap_first->_pair_temp, &cpmmap_second->_pair_temp));

#ifdef CSTL_MULTIMAP_AVL_TREE
    return _avl_tree_less(&cpmmap_first->_t_tree, &cpmmap_second->_t_tree);
#else
    return _rb_tree_less(&cpmmap_first->_t_tree, &cpmmap_second->_t_tree);
#endif
}

/**
 * Tests if the first multimap is less than or equal to the second multimap.
 */
bool_t multimap_less_equal(const multimap_t* cpmmap_first, const multimap_t* cpmmap_second)
{
    assert(cpmmap_first != NULL);
    assert(cpmmap_second != NULL);
    assert(_pair_is_inited(&cpmmap_first->_pair_temp));
    assert(_pair_is_inited(&cpmmap_second->_pair_temp));
    assert(_multimap_same_pair_type_ex(&cpmmap_first->_pair_temp, &cpmmap_second->_pair_temp));

#ifdef CSTL_MULTIMAP_AVL_TREE
    return _avl_tree_less_equal(&cpmmap_first->_t_tree, &cpmmap_second->_t_tree);
#else
    return _rb_tree_less_equal(&cpmmap_first->_t_tree, &cpmmap_second->_t_tree);
#endif
}

/**
 * Tests if the first multimap is greater than the second multimap.
 */
bool_t multimap_greater(const multimap_t* cpmmap_first, const multimap_t* cpmmap_second)
{
    assert(cpmmap_first != NULL);
    assert(cpmmap_second != NULL);
    assert(_pair_is_inited(&cpmmap_first->_pair_temp));
    assert(_pair_is_inited(&cpmmap_second->_pair_temp));
    assert(_multimap_same_pair_type_ex(&cpmmap_first->_pair_temp, &cpmmap_second->_pair_temp));

#ifdef CSTL_MULTIMAP_AVL_TREE
    return _avl_tree_greater(&cpmmap_first->_t_tree, &cpmmap_second->_t_tree);
#else
    return _rb_tree_greater(&cpmmap_first->_t_tree, &cpmmap_second->_t_tree);
#endif
}

/**
 * Tests if the first multimap is greater than or equal to the second multimap.
 */
bool_t multimap_greater_equal(const multimap_t* cpmmap_first, const multimap_t* cpmmap_second)
{
    assert(cpmmap_first != NULL);
    assert(cpmmap_second != NULL);
    assert(_pair_is_inited(&cpmmap_first->_pair_temp));
    assert(_pair_is_inited(&cpmmap_second->_pair_temp));
    assert(_multimap_same_pair_type_ex(&cpmmap_first->_pair_temp, &cpmmap_second->_pair_temp));

#ifdef CSTL_MULTIMAP_AVL_TREE
    return _avl_tree_greater_equal(&cpmmap_first->_t_tree, &cpmmap_second->_t_tree);
#else
    return _rb_tree_greater_equal(&cpmmap_first->_t_tree, &cpmmap_second->_t_tree);
#endif
}

/**
 * Return an iterator that addresses the first element in the multimap.
 */
multimap_iterator_t multimap_begin(const multimap_t* cpmmap_map)
{
    multimap_iterator_t it_iter;

    assert(cpmmap_map != NULL);
    assert(_pair_is_inited(&cpmmap_map->_pair_temp));

#ifdef CSTL_MULTIMAP_AVL_TREE
    it_iter = _avl_tree_begin(&cpmmap_map->_t_tree);
#else
    it_iter = _rb_tree_begin(&cpmmap_map->_t_tree);
#endif

    _ITERATOR_CONTAINER(it_iter) = (multimap_t*)cpmmap_map;
    _MULTIMAP_ITERATOR_CONTAINER_TYPE(it_iter) = _MULTIMAP_CONTAINER;
    _MULTIMAP_ITERATOR_ITERATOR_TYPE(it_iter) = _BIDIRECTIONAL_ITERATOR;

    return it_iter;
}

/**
 * Return an iterator that addresses the location succeeding the last element in the multimap.
 */
multimap_iterator_t multimap_end(const multimap_t* cpmmap_map)
{
    multimap_iterator_t it_iter;

    assert(cpmmap_map != NULL);
    assert(_pair_is_inited(&cpmmap_map->_pair_temp));

#ifdef CSTL_MULTIMAP_AVL_TREE
    it_iter = _avl_tree_end(&cpmmap_map->_t_tree);
#else
    it_iter = _rb_tree_end(&cpmmap_map->_t_tree);
#endif

    _ITERATOR_CONTAINER(it_iter) = (multimap_t*)cpmmap_map;
    _MULTIMAP_ITERATOR_CONTAINER_TYPE(it_iter) = _MULTIMAP_CONTAINER;
    _MULTIMAP_ITERATOR_ITERATOR_TYPE(it_iter) = _BIDIRECTIONAL_ITERATOR;

    return it_iter;
}

multimap_reverse_iterator_t multimap_rbegin(const multimap_t* cpmmap_map)
{
    multimap_reverse_iterator_t it_iter;

    assert(cpmmap_map != NULL);
    assert(_pair_is_inited(&cpmmap_map->_pair_temp));

#ifdef CSTL_MULTIMAP_AVL_TREE
    it_iter = _avl_tree_rbegin(&cpmmap_map->_t_tree);
#else
    it_iter = _rb_tree_rbegin(&cpmmap_map->_t_tree);
#endif

    _ITERATOR_CONTAINER(it_iter) = (multimap_t*)cpmmap_map;
    _MULTIMAP_ITERATOR_CONTAINER_TYPE(it_iter) = _MULTIMAP_CONTAINER;
    _MULTIMAP_ITERATOR_ITERATOR_TYPE(it_iter) = _BIDIRECTIONAL_ITERATOR;

    return it_iter;
}

multimap_reverse_iterator_t multimap_rend(const multimap_t* cpmmap_map)
{
    multimap_reverse_iterator_t it_iter;

    assert(cpmmap_map != NULL);
    assert(_pair_is_inited(&cpmmap_map->_pair_temp));

#ifdef CSTL_MULTIMAP_AVL_TREE
    it_iter = _avl_tree_rend(&cpmmap_map->_t_tree);
#else
    it_iter = _rb_tree_rend(&cpmmap_map->_t_tree);
#endif

    _ITERATOR_CONTAINER(it_iter) = (multimap_t*)cpmmap_map;
    _MULTIMAP_ITERATOR_CONTAINER_TYPE(it_iter) = _MULTIMAP_CONTAINER;
    _MULTIMAP_ITERATOR_ITERATOR_TYPE(it_iter) = _BIDIRECTIONAL_ITERATOR;

    return it_iter;
}

/**
 * Inserts an unique element into a multimap.
 */
multimap_iterator_t multimap_insert(multimap_t* pmmap_map, const pair_t* cppair_pair)
{
    multimap_iterator_t it_iter;

    assert(pmmap_map != NULL);
    assert(cppair_pair != NULL);
    assert(_pair_is_inited(&pmmap_map->_pair_temp));
    assert(_pair_is_inited(cppair_pair));

    ((pair_t*)cppair_pair)->_bfun_mapkeycompare = pmmap_map->_bfun_keycompare;
    ((pair_t*)cppair_pair)->_bfun_mapvaluecompare = pmmap_map->_bfun_valuecompare;

    assert(_multimap_same_pair_type_ex(&pmmap_map->_pair_temp, cppair_pair));

#ifdef CSTL_MULTIMAP_AVL_TREE
    it_iter = _avl_tree_insert_equal(&pmmap_map->_t_tree, cppair_pair);
#else
    it_iter = _rb_tree_insert_equal(&pmmap_map->_t_tree, cppair_pair);
#endif

    _ITERATOR_CONTAINER(it_iter) = pmmap_map;
    _MULTIMAP_ITERATOR_CONTAINER_TYPE(it_iter) = _MULTIMAP_CONTAINER;
    _MULTIMAP_ITERATOR_ITERATOR_TYPE(it_iter) = _BIDIRECTIONAL_ITERATOR;

    return it_iter;
}

/**
 * Inserts an unique element into a multimap with hint position.
 */
multimap_iterator_t multimap_insert_hint(multimap_t* pmmap_map, multimap_iterator_t it_hint, const pair_t* cppair_pair)
{
    assert(pmmap_map != NULL);
    assert(cppair_pair != NULL);
    assert(_pair_is_inited(&pmmap_map->_pair_temp));
    assert(_pair_is_inited(cppair_pair));
    assert(_MULTIMAP_ITERATOR_CONTAINER_TYPE(it_hint) == _MULTIMAP_CONTAINER);
    assert(_MULTIMAP_ITERATOR_ITERATOR_TYPE(it_hint) == _BIDIRECTIONAL_ITERATOR);
    assert(_MULTIMAP_ITERATOR_CONTAINER(it_hint) == pmmap_map);

    ((pair_t*)cppair_pair)->_bfun_mapkeycompare = pmmap_map->_bfun_keycompare;
    ((pair_t*)cppair_pair)->_bfun_mapvaluecompare = pmmap_map->_bfun_valuecompare;

    assert(_multimap_same_pair_type_ex(&pmmap_map->_pair_temp, cppair_pair));

#ifdef CSTL_MULTIMAP_AVL_TREE
    it_hint = _avl_tree_insert_equal(&pmmap_map->_t_tree, cppair_pair);
#else
    it_hint = _rb_tree_insert_equal(&pmmap_map->_t_tree, cppair_pair);
#endif

    _ITERATOR_CONTAINER(it_hint) = pmmap_map;
    _MULTIMAP_ITERATOR_CONTAINER_TYPE(it_hint) = _MULTIMAP_CONTAINER;
    _MULTIMAP_ITERATOR_ITERATOR_TYPE(it_hint) = _BIDIRECTIONAL_ITERATOR;

    return it_hint;
}

/**
 * Inserts an range of unique element into a multimap.
 */
void multimap_insert_range(multimap_t* pmmap_map, iterator_t it_begin, iterator_t it_end)
{
    iterator_t it_iter;

    assert(pmmap_map != NULL);
    assert(_pair_is_inited(&pmmap_map->_pair_temp));
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));

    for (it_iter = it_begin; !iterator_equal(it_iter, it_end); it_iter = iterator_next(it_iter)) {
        assert(_multimap_same_pair_type(&pmmap_map->_pair_temp, (pair_t*)iterator_get_pointer(it_iter)));
        multimap_insert(pmmap_map, (pair_t*)iterator_get_pointer(it_iter));
    }
}

/**
 * Inserts an array of element into a multimap.
 */
void multimap_insert_array(multimap_t* pmmap_map, const void* cpv_array, size_t t_count)
{
    size_t i = 0;

    assert(pmmap_map != NULL);
    assert(_pair_is_inited(&pmmap_map->_pair_temp));
    assert(cpv_array != NULL);

    for (i = 0; i < t_count; ++i) {
        assert(_multimap_same_pair_type(&pmmap_map->_pair_temp, ((pair_t**)cpv_array)[i]));
        multimap_insert(pmmap_map, ((pair_t**)cpv_array)[i]);
    }
}

/*
 * Erase an element in an multimap from specificed position.
 */
void multimap_erase_pos(multimap_t* pmmap_map, multimap_iterator_t it_pos)
{
    assert(pmmap_map != NULL);
    assert(_pair_is_inited(&pmmap_map->_pair_temp));
    assert(_MULTIMAP_ITERATOR_CONTAINER_TYPE(it_pos) == _MULTIMAP_CONTAINER);
    assert(_MULTIMAP_ITERATOR_ITERATOR_TYPE(it_pos) == _BIDIRECTIONAL_ITERATOR);
    assert(_MULTIMAP_ITERATOR_CONTAINER(it_pos) == pmmap_map);

#ifdef CSTL_MULTIMAP_AVL_TREE
    _avl_tree_erase_pos(&pmmap_map->_t_tree, it_pos);
#else
    _rb_tree_erase_pos(&pmmap_map->_t_tree, it_pos);
#endif
}

/*
 * Erase a range of element in an multimap.
 */
void multimap_erase_range(multimap_t* pmmap_map, multimap_iterator_t it_begin, multimap_iterator_t it_end)
{
    assert(pmmap_map != NULL);
    assert(_pair_is_inited(&pmmap_map->_pair_temp));
    assert(_MULTIMAP_ITERATOR_CONTAINER_TYPE(it_begin) == _MULTIMAP_CONTAINER);
    assert(_MULTIMAP_ITERATOR_ITERATOR_TYPE(it_begin) == _BIDIRECTIONAL_ITERATOR);
    assert(_MULTIMAP_ITERATOR_CONTAINER_TYPE(it_end) == _MULTIMAP_CONTAINER);
    assert(_MULTIMAP_ITERATOR_ITERATOR_TYPE(it_end) == _BIDIRECTIONAL_ITERATOR);
    assert(_MULTIMAP_ITERATOR_CONTAINER(it_begin) == pmmap_map && _MULTIMAP_ITERATOR_CONTAINER(it_end) == pmmap_map);

#ifdef CSTL_MULTIMAP_AVL_TREE
    _avl_tree_erase_range(&pmmap_map->_t_tree, it_begin, it_end);
#else
    _rb_tree_erase_range(&pmmap_map->_t_tree, it_begin, it_end);
#endif
}

/** local function implementation section **/

/** eof **/

