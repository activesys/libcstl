/*
 *  The implement of iterator private interface.
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

#include <cstl/cstl_iterator_private.h>
#include <cstl/cstl_iterator.h>
#include <cstl/cvector.h>
#include <cstl/clist.h>
#include <cstl/cdeque.h>
#include <cstl/cslist.h>
#include <cstl/cset.h>
#include <cstl/cmap.h>
#include <cstl/chash_set.h>
#include <cstl/chash_map.h>
#include <cstl/cstring.h>

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Test whether the iterator is valid.
 */
bool_t _iterator_is_valid(iterator_t it_iter)
{
    if ((it_iter._t_containertype == _VECTOR_CONTAINER ||
         it_iter._t_containertype == _LIST_CONTAINER ||
         it_iter._t_containertype == _DEQUE_CONTAINER ||
         it_iter._t_containertype == _SLIST_CONTAINER ||
         it_iter._t_containertype == _MAP_CONTAINER ||
         it_iter._t_containertype == _MULTIMAP_CONTAINER ||
         it_iter._t_containertype == _SET_CONTAINER ||
         it_iter._t_containertype == _MULTISET_CONTAINER ||
         it_iter._t_containertype == _HASH_SET_CONTAINER ||
         it_iter._t_containertype == _HASH_MULTISET_CONTAINER ||
         it_iter._t_containertype == _HASH_MAP_CONTAINER ||
         it_iter._t_containertype == _HASH_MULTIMAP_CONTAINER ||
         it_iter._t_containertype == _BASIC_STRING_CONTAINER) &&
        (it_iter._t_iteratortype == _INPUT_ITERATOR ||
         it_iter._t_iteratortype == _OUTPUT_ITERATOR ||
         it_iter._t_iteratortype == _FORWARD_ITERATOR ||
         it_iter._t_iteratortype == _BIDIRECTIONAL_ITERATOR ||
         it_iter._t_iteratortype == _RANDOM_ACCESS_ITERATOR)) {
        return true;
    } else {
        return false;
    }
}

/**
 * Get pointer that pointed by iterator, but ignore char*.
 */
const void* _iterator_get_pointer_ignore_cstr(iterator_t it_iter)
{
    assert(_iterator_is_valid(it_iter));
    assert(_iterator_limit_type(it_iter, _INPUT_ITERATOR));

    switch (it_iter._t_containertype) {
        case _VECTOR_CONTAINER:
            return _vector_iterator_get_pointer_ignore_cstr(it_iter);
            break;
        case _LIST_CONTAINER:
            return _list_iterator_get_pointer_ignore_cstr(it_iter);
            break;
        case _DEQUE_CONTAINER:
            return _deque_iterator_get_pointer_ignore_cstr(it_iter);
            break;
        case _SLIST_CONTAINER:
            return _slist_iterator_get_pointer_ignore_cstr(it_iter);
            break;
        case _SET_CONTAINER:
            return _set_iterator_get_pointer_ignore_cstr(it_iter);
            break;
        case _MULTISET_CONTAINER:
            return _multiset_iterator_get_pointer_ignore_cstr(it_iter);
            break;
        case _MAP_CONTAINER:
            return _map_iterator_get_pointer_ignore_cstr(it_iter);
            break;
        case _MULTIMAP_CONTAINER:
            return _multimap_iterator_get_pointer_ignore_cstr(it_iter);
            break;
        case _HASH_SET_CONTAINER:
            return _hash_set_iterator_get_pointer_ignore_cstr(it_iter);
            break;
        case _HASH_MULTISET_CONTAINER:
            return _hash_multiset_iterator_get_pointer_ignore_cstr(it_iter);
            break;
        case _HASH_MAP_CONTAINER:
            return _hash_map_iterator_get_pointer_ignore_cstr(it_iter);
            break;
        case _HASH_MULTIMAP_CONTAINER:
            return _hash_multimap_iterator_get_pointer_ignore_cstr(it_iter);
            break;
        case _BASIC_STRING_CONTAINER:
            return _basic_string_iterator_get_pointer_ignore_cstr(it_iter);
            break;
        default:
            assert(false);
            return NULL;
            break;
    }
}

/**
 * Test whether two iterator are equal types.
 */
bool_t _iterator_same_type(iterator_t it_first, iterator_t it_second)
{
    assert(_iterator_is_valid(it_first));
    assert(_iterator_is_valid(it_second));

    if (it_first._t_containertype == it_second._t_containertype &&
        it_first._t_iteratortype == it_second._t_iteratortype) {
        return true;
    } else {
        return false;
    }
}

/**
 * Test whether an iterator on another front.
 */
bool_t _iterator_before(iterator_t it_first, iterator_t it_second)
{
    assert(_iterator_same_type(it_first, it_second));

    switch (it_first._t_containertype) {
        case _VECTOR_CONTAINER:
            return _vector_iterator_before(it_first, it_second);
            break;
        case _DEQUE_CONTAINER:
            return _deque_iterator_before(it_first, it_second);
            break;
        case _LIST_CONTAINER:
            return _list_iterator_before(it_first, it_second);
            break;
        case _SLIST_CONTAINER:
            return _slist_iterator_before(it_first, it_second);
            break;
        case _SET_CONTAINER:
            return _set_iterator_before(it_first, it_second);
            break;
        case _MULTISET_CONTAINER:
            return _multiset_iterator_before(it_first, it_second);
            break;
        case _MAP_CONTAINER:
            return _map_iterator_before(it_first, it_second);
            break;
        case _MULTIMAP_CONTAINER:
            return _multimap_iterator_before(it_first, it_second);
            break;
        case _HASH_SET_CONTAINER:
            return _hash_set_iterator_before(it_first, it_second);
            break;
        case _HASH_MULTISET_CONTAINER:
            return _hash_multiset_iterator_before(it_first, it_second);
            break;
        case _HASH_MAP_CONTAINER:
            return _hash_map_iterator_before(it_first, it_second);
            break;
        case _HASH_MULTIMAP_CONTAINER:
            return _hash_multimap_iterator_before(it_first, it_second);
            break;
        case _BASIC_STRING_CONTAINER:
            return _basic_string_iterator_before(it_first, it_second);
            break;
        default:
            return false;
            break;
    }
}

/**
 * Test whether the iterator type of restriction.
 */
bool_t _iterator_limit_type(iterator_t it_iter, iteratortype_t t_limittype)
{
    assert(_iterator_is_valid(it_iter));

    /* check iterator type */
    switch (t_limittype) {
        case _INPUT_ITERATOR:
            if (it_iter._t_iteratortype == _RANDOM_ACCESS_ITERATOR ||
                it_iter._t_iteratortype == _BIDIRECTIONAL_ITERATOR ||
                it_iter._t_iteratortype == _FORWARD_ITERATOR ||
                it_iter._t_iteratortype == _INPUT_ITERATOR) {
                return true;
            }
            break;
        case _OUTPUT_ITERATOR:
            if (it_iter._t_iteratortype == _RANDOM_ACCESS_ITERATOR ||
                it_iter._t_iteratortype == _BIDIRECTIONAL_ITERATOR ||
                it_iter._t_iteratortype == _FORWARD_ITERATOR ||
                it_iter._t_iteratortype == _OUTPUT_ITERATOR) {
                return true;
            }
            break;
        case _FORWARD_ITERATOR:
            if (it_iter._t_iteratortype == _RANDOM_ACCESS_ITERATOR ||
                it_iter._t_iteratortype == _BIDIRECTIONAL_ITERATOR ||
                it_iter._t_iteratortype == _FORWARD_ITERATOR) {
                return true;
            }
            break;
        case _BIDIRECTIONAL_ITERATOR:
            if (it_iter._t_iteratortype == _RANDOM_ACCESS_ITERATOR ||
                it_iter._t_iteratortype == _BIDIRECTIONAL_ITERATOR) {
                return true;
            }
            break;
        case _RANDOM_ACCESS_ITERATOR:
            if (it_iter._t_iteratortype == _RANDOM_ACCESS_ITERATOR) {
                return true;
            }
            break;
        default:
            assert(false);
            break;
    }

    return false;
}

/**
 * Test whether the [it_first, it_end) is valid range.
 */
bool_t _iterator_valid_range(iterator_t it_first, iterator_t it_end, iteratortype_t t_type)
{
    return _iterator_same_type(it_first, it_end) &&
           _iterator_limit_type(it_first, t_type) &&
           (iterator_equal(it_first, it_end) || _iterator_before(it_first, it_end));
}

/**
 * Get typeinfo of iterator.
 */
_typeinfo_t* _iterator_get_typeinfo(iterator_t it_iter)
{
    assert(_iterator_is_valid(it_iter));

    switch (it_iter._t_containertype) {
        case _VECTOR_CONTAINER:
            return &((vector_t*)it_iter._pt_container)->_t_typeinfo;
            break;
        case _DEQUE_CONTAINER:
            return &((deque_t*)it_iter._pt_container)->_t_typeinfo;
            break;
        case _BASIC_STRING_CONTAINER:
            return &((basic_string_t*)it_iter._pt_container)->_t_typeinfo;
            break;
        case _LIST_CONTAINER:
            return &((list_t*)it_iter._pt_container)->_t_typeinfo;
            break;
        case _SLIST_CONTAINER:
            return &((slist_t*)it_iter._pt_container)->_t_typeinfo;
            break;
        case _SET_CONTAINER:
            return &((set_t*)it_iter._pt_container)->_t_tree._t_typeinfo;
            break;
        case _MULTISET_CONTAINER:
            return &((multiset_t*)it_iter._pt_container)->_t_tree._t_typeinfo;
            break;
        case _MAP_CONTAINER:
            return &((map_t*)it_iter._pt_container)->_t_tree._t_typeinfo;
            break;
        case _MULTIMAP_CONTAINER:
            return &((multimap_t*)it_iter._pt_container)->_t_tree._t_typeinfo;
            break;
        case _HASH_SET_CONTAINER:
            return &((hash_set_t*)it_iter._pt_container)->_t_hashtable._t_typeinfo;
            break;
        case _HASH_MULTISET_CONTAINER:
            return &((hash_multiset_t*)it_iter._pt_container)->_t_hashtable._t_typeinfo;
            break;
        case _HASH_MAP_CONTAINER:
            return &((hash_map_t*)it_iter._pt_container)->_t_hashtable._t_typeinfo;
            break;
        case _HASH_MULTIMAP_CONTAINER:
            return &((hash_multimap_t*)it_iter._pt_container)->_t_hashtable._t_typeinfo;
            break;
        default:
            assert(false);
            return NULL;
            break;
    }
}

/**
 * Get type style of iterator.
 */
_typestyle_t _iterator_get_typestyle(iterator_t it_iter)
{
    _typeinfo_t* pt_typeinfo = _iterator_get_typeinfo(it_iter);
    return pt_typeinfo != NULL ? pt_typeinfo->_t_style : _TYPE_INVALID;
}

/**
 * Get type basename of iterator.
 */
const char* _iterator_get_typebasename(iterator_t it_iter)
{
    _typeinfo_t* pt_typeinfo = _iterator_get_typeinfo(it_iter);
    return pt_typeinfo != NULL ? pt_typeinfo->_pt_type->_s_typename : NULL;
}

/**
 * Get type name of iterator.
 */
const char* _iterator_get_typename(iterator_t it_iter)
{
    _typeinfo_t* pt_typeinfo = _iterator_get_typeinfo(it_iter);
    return pt_typeinfo != NULL ? pt_typeinfo->_s_typename : NULL;
}

/**
 * Get type copy function of iterator.
 */
bfun_t _iterator_get_typecopy(iterator_t it_iter)
{
    _typeinfo_t* pt_typeinfo = _iterator_get_typeinfo(it_iter);
    return pt_typeinfo != NULL ? pt_typeinfo->_pt_type->_t_typecopy : NULL;
}

/**
 * Get type size of iterator.
 */
size_t _iterator_get_typesize(iterator_t it_iter)
{
    _typeinfo_t* pt_typeinfo = _iterator_get_typeinfo(it_iter);
    return pt_typeinfo != NULL ? pt_typeinfo->_pt_type->_t_typesize : 0;
}

/**
 * Test whether two iterator point to same type element.
 */
bool_t _iterator_same_elem_type(iterator_t it_first, iterator_t it_second)
{
    _typeinfo_t* pt_first = _iterator_get_typeinfo(it_first);
    _typeinfo_t* pt_second = _iterator_get_typeinfo(it_second);

    if (pt_first == NULL || pt_second == NULL) {
        return false;
    }
    return (pt_first->_pt_type == pt_second->_pt_type) &&
           (pt_first->_t_style == pt_second->_t_style) &&
           _type_is_same(pt_first->_s_typename, pt_second->_s_typename);
}

/**
 * Initialize an element according to the type of iterator pointed data.
 */
void* _iterator_allocate_init_elem(iterator_t it_iter)
{
    void* pv_value = NULL;

    assert(_iterator_is_valid(it_iter));
    switch (it_iter._t_containertype) {
        case _VECTOR_CONTAINER:
            pv_value = _alloc_allocate(&((vector_t*)it_iter._pt_container)->_t_allocator,
                ((vector_t*)it_iter._pt_container)->_t_typeinfo._pt_type->_t_typesize, 1);
            _vector_init_elem_auxiliary((vector_t*)it_iter._pt_container, pv_value);
            break;
        case _DEQUE_CONTAINER:
            pv_value = _alloc_allocate(&((deque_t*)it_iter._pt_container)->_t_allocator,
                ((deque_t*)it_iter._pt_container)->_t_typeinfo._pt_type->_t_typesize, 1);
            _deque_init_elem_auxiliary((deque_t*)it_iter._pt_container, pv_value);
            break;
        case _BASIC_STRING_CONTAINER:
            /*
            pv_value = _alloc_allocate(&((basic_string_t*)it_iter._pt_container)->_vec_base._t_allocator,
                ((basic_string_t*)it_iter._pt_container)->_vec_base._t_typeinfo._pt_type->_t_typesize, 1);
                */
            pv_value = malloc(((basic_string_t*)it_iter._pt_container)->_t_typeinfo._pt_type->_t_typesize);
            _basic_string_init_elem_auxiliary((basic_string_t*)it_iter._pt_container, pv_value);
            break;
        case _LIST_CONTAINER:
            pv_value = _alloc_allocate(&((list_t*)it_iter._pt_container)->_t_allocator,
                ((list_t*)it_iter._pt_container)->_t_typeinfo._pt_type->_t_typesize, 1);
            _list_init_elem_auxiliary((list_t*)it_iter._pt_container, pv_value);
            break;
        case _SLIST_CONTAINER:
            pv_value = _alloc_allocate(&((slist_t*)it_iter._pt_container)->_t_allocator,
                ((slist_t*)it_iter._pt_container)->_t_typeinfo._pt_type->_t_typesize, 1);
            _slist_init_elem_auxiliary((slist_t*)it_iter._pt_container, pv_value);
            break;
        case _SET_CONTAINER:
            pv_value = _alloc_allocate(&((set_t*)it_iter._pt_container)->_t_tree._t_allocator,
                ((set_t*)it_iter._pt_container)->_t_tree._t_typeinfo._pt_type->_t_typesize, 1);
            _set_init_elem_auxiliary((set_t*)it_iter._pt_container, pv_value);
            break;
        case _MULTISET_CONTAINER:
            pv_value = _alloc_allocate(&((multiset_t*)it_iter._pt_container)->_t_tree._t_allocator,
                ((set_t*)it_iter._pt_container)->_t_tree._t_typeinfo._pt_type->_t_typesize, 1);
            _multiset_init_elem_auxiliary((multiset_t*)it_iter._pt_container, pv_value);
            break;
        case _MAP_CONTAINER:
            pv_value = _alloc_allocate(&((map_t*)it_iter._pt_container)->_t_tree._t_allocator,
                ((map_t*)it_iter._pt_container)->_t_tree._t_typeinfo._pt_type->_t_typesize, 1);
            _map_init_elem_auxiliary((map_t*)it_iter._pt_container, pv_value);
            break;
        case _MULTIMAP_CONTAINER:
            pv_value = _alloc_allocate(&((multimap_t*)it_iter._pt_container)->_t_tree._t_allocator,
                ((multimap_t*)it_iter._pt_container)->_t_tree._t_typeinfo._pt_type->_t_typesize, 1);
            _multimap_init_elem_auxiliary((multimap_t*)it_iter._pt_container, pv_value);
            break;
        case _HASH_SET_CONTAINER:
            pv_value = _alloc_allocate(&((hash_set_t*)it_iter._pt_container)->_t_hashtable._t_allocator,
                ((hash_set_t*)it_iter._pt_container)->_t_hashtable._t_typeinfo._pt_type->_t_typesize, 1);
            _hash_set_init_elem_auxiliary((hash_set_t*)it_iter._pt_container, pv_value);
            break;
        case _HASH_MULTISET_CONTAINER:
            pv_value = _alloc_allocate(&((hash_multiset_t*)it_iter._pt_container)->_t_hashtable._t_allocator,
                ((hash_multiset_t*)it_iter._pt_container)->_t_hashtable._t_typeinfo._pt_type->_t_typesize, 1);
            _hash_multiset_init_elem_auxiliary((hash_multiset_t*)it_iter._pt_container, pv_value);
            break;
        case _HASH_MAP_CONTAINER:
            pv_value = _alloc_allocate(&((hash_map_t*)it_iter._pt_container)->_t_hashtable._t_allocator,
                ((hash_map_t*)it_iter._pt_container)->_t_hashtable._t_typeinfo._pt_type->_t_typesize, 1);
            _hash_map_init_elem_auxiliary((hash_map_t*)it_iter._pt_container, pv_value);
            break;
        case _HASH_MULTIMAP_CONTAINER:
            pv_value = _alloc_allocate(&((hash_multimap_t*)it_iter._pt_container)->_t_hashtable._t_allocator,
                ((hash_multimap_t*)it_iter._pt_container)->_t_hashtable._t_typeinfo._pt_type->_t_typesize, 1);
            _hash_multimap_init_elem_auxiliary((hash_multimap_t*)it_iter._pt_container, pv_value);
            break;
        default:
            assert(false);
            pv_value = NULL;
            break;
    }

    return pv_value;
}

/**
 * Destroy and deallocate element allocated and initialized by _iterator_allocate_init_elem().
 */
void _iterator_deallocate_destroy_elem(iterator_t it_iter, void* pv_value)
{
    bool_t b_result = false;

    assert(_iterator_is_valid(it_iter));
    assert(pv_value != NULL);
    switch (it_iter._t_containertype) {
        case _VECTOR_CONTAINER:
            ((vector_t*)it_iter._pt_container)->_t_typeinfo._pt_type->_t_typedestroy(pv_value, &b_result);
            assert(b_result);
            _alloc_deallocate(&((vector_t*)it_iter._pt_container)->_t_allocator, pv_value,
                ((vector_t*)it_iter._pt_container)->_t_typeinfo._pt_type->_t_typesize, 1);
            break;
        case _DEQUE_CONTAINER:
            ((deque_t*)it_iter._pt_container)->_t_typeinfo._pt_type->_t_typedestroy(pv_value, &b_result);
            assert(b_result);
            _alloc_deallocate(&((deque_t*)it_iter._pt_container)->_t_allocator, pv_value,
                ((deque_t*)it_iter._pt_container)->_t_typeinfo._pt_type->_t_typesize, 1);
            break;
        case _BASIC_STRING_CONTAINER:
            ((basic_string_t*)it_iter._pt_container)->_t_typeinfo._pt_type->_t_typedestroy(pv_value, &b_result);
            assert(b_result);
            free(pv_value);
            /*
            _alloc_deallocate(&((basic_string_t*)it_iter._pt_container)->_vec_base._t_allocator, pv_value,
                ((basic_string_t*)it_iter._pt_container)->_vec_base._t_typeinfo._pt_type->_t_typesize, 1);
                */
            break;
        case _LIST_CONTAINER:
            ((list_t*)it_iter._pt_container)->_t_typeinfo._pt_type->_t_typedestroy(pv_value, &b_result);
            assert(b_result);
            _alloc_deallocate(&((list_t*)it_iter._pt_container)->_t_allocator, pv_value,
                ((list_t*)it_iter._pt_container)->_t_typeinfo._pt_type->_t_typesize, 1);
            break;
        case _SLIST_CONTAINER:
            ((slist_t*)it_iter._pt_container)->_t_typeinfo._pt_type->_t_typedestroy(pv_value, &b_result);
            assert(b_result);
            _alloc_deallocate(&((slist_t*)it_iter._pt_container)->_t_allocator, pv_value,
                ((slist_t*)it_iter._pt_container)->_t_typeinfo._pt_type->_t_typesize, 1);
            break;
        case _SET_CONTAINER:
            ((set_t*)it_iter._pt_container)->_t_tree._t_typeinfo._pt_type->_t_typedestroy(pv_value, &b_result);
            assert(b_result);
            _alloc_deallocate(&((set_t*)it_iter._pt_container)->_t_tree._t_allocator, pv_value,
                ((set_t*)it_iter._pt_container)->_t_tree._t_typeinfo._pt_type->_t_typesize, 1);
            break;
        case _MULTISET_CONTAINER:
            ((multiset_t*)it_iter._pt_container)->_t_tree._t_typeinfo._pt_type->_t_typedestroy(pv_value, &b_result);
            assert(b_result);
            _alloc_deallocate(&((multiset_t*)it_iter._pt_container)->_t_tree._t_allocator, pv_value,
                ((set_t*)it_iter._pt_container)->_t_tree._t_typeinfo._pt_type->_t_typesize, 1);
            break;
        case _MAP_CONTAINER:
            ((map_t*)it_iter._pt_container)->_t_tree._t_typeinfo._pt_type->_t_typedestroy(pv_value, &b_result);
            assert(b_result);
            _alloc_deallocate(&((map_t*)it_iter._pt_container)->_t_tree._t_allocator, pv_value,
                ((map_t*)it_iter._pt_container)->_t_tree._t_typeinfo._pt_type->_t_typesize, 1);
            break;
        case _MULTIMAP_CONTAINER:
            ((multimap_t*)it_iter._pt_container)->_t_tree._t_typeinfo._pt_type->_t_typedestroy(pv_value, &b_result);
            assert(b_result);
            _alloc_deallocate(&((multimap_t*)it_iter._pt_container)->_t_tree._t_allocator, pv_value,
                ((multimap_t*)it_iter._pt_container)->_t_tree._t_typeinfo._pt_type->_t_typesize, 1);
            break;
        case _HASH_SET_CONTAINER:
            ((hash_set_t*)it_iter._pt_container)->_t_hashtable._t_typeinfo._pt_type->_t_typedestroy(pv_value, &b_result);
            assert(b_result);
            _alloc_deallocate(&((hash_set_t*)it_iter._pt_container)->_t_hashtable._t_allocator, pv_value,
                ((hash_set_t*)it_iter._pt_container)->_t_hashtable._t_typeinfo._pt_type->_t_typesize, 1);
            break;
        case _HASH_MULTISET_CONTAINER:
            ((hash_multiset_t*)it_iter._pt_container)->_t_hashtable._t_typeinfo._pt_type->_t_typedestroy(pv_value, &b_result);
            assert(b_result);
            _alloc_deallocate(&((hash_multiset_t*)it_iter._pt_container)->_t_hashtable._t_allocator, pv_value,
                ((hash_multiset_t*)it_iter._pt_container)->_t_hashtable._t_typeinfo._pt_type->_t_typesize, 1);
            break;
        case _HASH_MAP_CONTAINER:
            ((hash_map_t*)it_iter._pt_container)->_t_hashtable._t_typeinfo._pt_type->_t_typedestroy(pv_value, &b_result);
            assert(b_result);
            _alloc_deallocate(&((hash_map_t*)it_iter._pt_container)->_t_hashtable._t_allocator, pv_value,
                ((hash_map_t*)it_iter._pt_container)->_t_hashtable._t_typeinfo._pt_type->_t_typesize, 1);
            break;
        case _HASH_MULTIMAP_CONTAINER:
            ((hash_multimap_t*)it_iter._pt_container)->_t_hashtable._t_typeinfo._pt_type->_t_typedestroy(pv_value, &b_result);
            assert(b_result);
            _alloc_deallocate(&((hash_multimap_t*)it_iter._pt_container)->_t_hashtable._t_allocator, pv_value,
                ((hash_multimap_t*)it_iter._pt_container)->_t_hashtable._t_typeinfo._pt_type->_t_typesize, 1);
            break;
        default:
            assert(false);
            break;
    }
}

/** local function implementation section **/

/** eof **/

