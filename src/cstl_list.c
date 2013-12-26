/*
 *  The implement of list module.
 *  Copyright (C)  2008 - 2014  Wangbo
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
#include <cstl/cfunctional.h>
#include <cstl/cstring.h>
#include <cstl/clist.h>

#include "cstl_list_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Initialize an empty list container
 */
void list_init(list_t* plist_list)
{
    assert(plist_list != NULL);
    assert(_list_is_created(plist_list));

    list_init_n(plist_list, 0);
}

/**
 * Initialize list container with specific size.
 */
void list_init_n(list_t* plist_list, size_t t_count)
{
    assert(plist_list != NULL);
    assert(_list_is_created(plist_list));

    /* allocate the end element */
    /*
     * _pt_node --+
     *            V
     *     +-->+------+<--+
     *     +---| prev |   |
     *         +------+   |
     *         | next |---+
     *         +------+
     *         | data |
     *         +------+
     */
    plist_list->_pt_node = _alloc_allocate(&plist_list->_t_allocator, _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(plist_list)), 1);
    assert(plist_list->_pt_node != NULL);
    plist_list->_pt_node->_pt_next = plist_list->_pt_node;
    plist_list->_pt_node->_pt_prev = plist_list->_pt_node;

    if (t_count > 0) {
        size_t       i = 0;
        _listnode_t* pt_node = NULL;

        for (i = 0; i < t_count; ++i) {
            pt_node = _alloc_allocate(&plist_list->_t_allocator, _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(plist_list)), 1);
            assert(pt_node != NULL);
            _list_init_node_auxiliary(plist_list, pt_node);

            pt_node->_pt_next = plist_list->_pt_node;
            pt_node->_pt_prev = plist_list->_pt_node->_pt_prev;
            plist_list->_pt_node->_pt_prev->_pt_next = pt_node;
            plist_list->_pt_node->_pt_prev = pt_node;
            pt_node = NULL;
        }
    }
}

/**
 * Destroy list container.
 */
void list_destroy(list_t* plist_list)
{
    assert(plist_list != NULL);
    assert(_list_is_inited(plist_list) || _list_is_created(plist_list));

    _list_destroy_auxiliary(plist_list);
    free(plist_list);
}

/**
 * Initialize list container with exist list container.
 */
void list_init_copy(list_t* plist_dest, const list_t* cplist_src)
{
    assert(plist_dest != NULL);
    assert(cplist_src != NULL);
    assert(_list_is_created(plist_dest));
    assert(_list_is_inited(cplist_src));
    assert(_list_same_type(plist_dest, cplist_src));

    list_init_copy_range(plist_dest, list_begin(cplist_src), list_end(cplist_src));
}

/**
 * Initialize list container with specific range.
 */
void list_init_copy_range(list_t* plist_list, iterator_t it_begin, iterator_t it_end)
{
    iterator_t it_dest;
    iterator_t it_dest_begin;
    iterator_t it_dest_end;
    iterator_t it_src;
    bool_t     b_result = false;

    assert(plist_list != NULL);
    assert(_list_is_created(plist_list));
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));
    assert(_list_same_iterator_type(plist_list, it_begin));
    assert(_list_same_iterator_type(plist_list, it_end));

    /* 
     * initialize the new list with the list size, compare function,
     * destroy element function of list that it_begin and it_end iterator
     * point to.
     */
    list_init_n(plist_list, iterator_distance(it_begin, it_end));
    it_dest_begin = list_begin(plist_list);
    it_dest_end = list_end(plist_list);

    /* copy the element from the range [it_begin, it_end) to now list */
    for (it_dest = it_dest_begin, it_src = it_begin;
         !iterator_equal(it_dest, it_dest_end) && !iterator_equal(it_src, it_end);
         it_dest = iterator_next(it_dest), it_src = iterator_next(it_src)) {
        b_result = _GET_LIST_TYPE_SIZE(plist_list);
        _GET_LIST_TYPE_COPY_FUNCTION(plist_list)(
            _iterator_get_pointer_ignore_cstr(it_dest),
            _iterator_get_pointer_ignore_cstr(it_src), &b_result);
        assert(b_result);
    }
    assert(iterator_equal(it_dest, it_dest_end) && iterator_equal(it_src, it_end));
}

/**
 * Initialize list container with specific array.
 */
void list_init_copy_array(list_t* plist_list, const void* cpv_array, size_t t_count)
{
    iterator_t it_dest;
    iterator_t it_begin;
    iterator_t it_end;
    bool_t     b_result = false;
    size_t     i = 0;

    assert(plist_list != NULL);
    assert(_list_is_created(plist_list));
    assert(cpv_array != NULL);

    /* 
     * initialize the new list with the list size, compare function,
     * destroy element function of list that it_begin and it_end iterator
     * point to.
     */
    list_init_n(plist_list, t_count);
    it_begin = list_begin(plist_list);
    it_end = list_end(plist_list);

    /*
     * Copy the elements from src array to dest list.
     * The array of c builtin and user define or cstl builtin are different,
     * the elements of c builtin array are element itself, but the elements of 
     * c string, user define or cstl are pointer of element.
     */
    if (strncmp(_GET_LIST_TYPE_BASENAME(plist_list), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        /*
         * We need built a string_t for c string element.
         */
        string_t* pstr_elem = create_string();
        assert(pstr_elem != NULL);
        string_init(pstr_elem);

        for (it_dest = it_begin, i = 0;
             !iterator_equal(it_dest, it_end) && i < t_count;
             it_dest = iterator_next(it_dest), ++i) {
            string_assign_cstr(pstr_elem, *((const char**)cpv_array + i));
            b_result = _GET_LIST_TYPE_SIZE(plist_list);
            _GET_LIST_TYPE_COPY_FUNCTION(plist_list)(
                _iterator_get_pointer_ignore_cstr(it_dest), pstr_elem, &b_result);
            assert(b_result);
        }
        string_destroy(pstr_elem);
    } else if (_GET_LIST_TYPE_STYLE(plist_list) == _TYPE_C_BUILTIN) {
        for (it_dest = it_begin, i = 0;
             !iterator_equal(it_dest, it_end) && i < t_count;
             it_dest = iterator_next(it_dest), ++i) {
            b_result = _GET_LIST_TYPE_SIZE(plist_list);
            _GET_LIST_TYPE_COPY_FUNCTION(plist_list)(
                _iterator_get_pointer_ignore_cstr(it_dest),
                (unsigned char*)cpv_array + i * _GET_LIST_TYPE_SIZE(plist_list), &b_result);
            assert(b_result);
        }
    } else {
        for (it_dest = it_begin, i = 0;
             !iterator_equal(it_dest, it_end) && i < t_count;
             it_dest = iterator_next(it_dest), ++i) {
            b_result = _GET_LIST_TYPE_SIZE(plist_list);
            _GET_LIST_TYPE_COPY_FUNCTION(plist_list)(
                _iterator_get_pointer_ignore_cstr(it_dest), *((void**)cpv_array + i), &b_result);
            assert(b_result);
        }
    }
    assert(iterator_equal(it_dest, it_end) && i == t_count);
}

/**
 * Return the number of elements in a list.
 */
size_t list_size(const list_t* cplist_list)
{
    _listnode_t* pt_node = NULL;     /* the current list node */
    size_t       t_listsize = 0;     /* list size */

    assert(cplist_list != NULL);
    assert(_list_is_inited(cplist_list));
    
    for (pt_node = cplist_list->_pt_node->_pt_next; pt_node != cplist_list->_pt_node; pt_node = pt_node->_pt_next) {
        t_listsize++;
    }

    return t_listsize;
}

/**
 * Tests if a list is empty.
 */
bool_t list_empty(const list_t* cplist_list)
{
    assert(cplist_list != NULL);
    assert(_list_is_inited(cplist_list));

    if (cplist_list->_pt_node->_pt_next == cplist_list->_pt_node) {
        assert(cplist_list->_pt_node->_pt_prev == cplist_list->_pt_node);
        return true;
    } else {
        return false;
    }
}

/**
 * Return the maximum number of elements in a list.
 */
size_t list_max_size(const list_t* cplist_list)
{
    assert(cplist_list != NULL);
    assert(_list_is_inited(cplist_list));

    return (size_t)(-1) / _GET_LIST_TYPE_SIZE(cplist_list);
}

/**
 * Tests if the two lists are equal.
 */
bool_t list_equal(const list_t* cplist_first, const list_t* cplist_second)
{
    _listnode_t* pt_first = NULL;    /* the firs list node pointer */
    _listnode_t* pt_second = NULL;   /* the second node pointer */
    bool_t       b_less = false;
    bool_t       b_greater = false;

    assert(cplist_first != NULL);
    assert(cplist_second != NULL);
    assert(_list_is_inited(cplist_first));
    assert(_list_is_inited(cplist_second));
    assert(_list_same_type(cplist_first, cplist_second));

    if (cplist_first == cplist_second) {
        return true;
    }
    /* test size */
    if (list_size(cplist_first) != list_size(cplist_second)) {
        return false;
    }
    /* test each element */
    for (pt_first = cplist_first->_pt_node->_pt_next, pt_second = cplist_second->_pt_node->_pt_next;
         pt_first != cplist_first->_pt_node && pt_second != cplist_second->_pt_node;
         pt_first = pt_first->_pt_next, pt_second = pt_second->_pt_next) {
        b_less = b_greater = _GET_LIST_TYPE_SIZE(cplist_first);
        _GET_LIST_TYPE_LESS_FUNCTION(cplist_first)(pt_first->_pby_data, pt_second->_pby_data, &b_less);
        _GET_LIST_TYPE_LESS_FUNCTION(cplist_first)(pt_second->_pby_data, pt_first->_pby_data, &b_greater);
        if (b_less || b_greater) {
            return false;
        }
    }
    assert(pt_first == cplist_first->_pt_node && pt_second == cplist_second->_pt_node);

    return true;
}

/**
 * Test the two lists are unequal.
 */
bool_t list_not_equal(const list_t* cplist_first, const list_t* cplist_second)
{
    return !list_equal(cplist_first, cplist_second);
}

/**
 * Test the first list is less than the second list.
 */
bool_t list_less(const list_t* cplist_first, const list_t* cplist_second)
{
    _listnode_t* pt_first = NULL;   /* the node pointer of first list */
    _listnode_t* pt_second = NULL;  /* the node pointer of second list */
    bool_t       b_result = false;

    assert(cplist_first != NULL);
    assert(cplist_second != NULL);
    assert(_list_is_inited(cplist_first));
    assert(_list_is_inited(cplist_second));
    assert(_list_same_type(cplist_first, cplist_second));

    for (pt_first = cplist_first->_pt_node->_pt_next, pt_second = cplist_second->_pt_node->_pt_next;
         pt_first != cplist_first->_pt_node && pt_second != cplist_second->_pt_node;
         pt_first = pt_first->_pt_next, pt_second = pt_second->_pt_next) {
        b_result = _GET_LIST_TYPE_SIZE(cplist_first);
        _GET_LIST_TYPE_LESS_FUNCTION(cplist_first)(pt_first->_pby_data, pt_second->_pby_data, &b_result);
        if (b_result) {
            return true;
        }

        b_result = _GET_LIST_TYPE_SIZE(cplist_first);
        _GET_LIST_TYPE_LESS_FUNCTION(cplist_first)(pt_second->_pby_data, pt_first->_pby_data, &b_result);
        if (b_result) {
            return false;
        }
    }

    return list_size(cplist_first) < list_size(cplist_second) ? true : false;
}

/**
 * Test the first list is less than or equal to the second list.
 */
bool_t list_less_equal(const list_t* cplist_first, const list_t* cplist_second)
{
    return (list_less(cplist_first, cplist_second) || list_equal(cplist_first, cplist_second)) ? true : false;
}

/**
 * Test the first list is greater than the second list.
 */
bool_t list_greater(const list_t* cplist_first, const list_t* cplist_second)
{
    return list_less(cplist_second, cplist_first);
}

/**
 * Test the first list is greater than or equal to the second list.
 */
bool_t list_greater_equal(const list_t* cplist_first, const list_t* cplist_second)
{
    return (list_greater(cplist_first, cplist_second) || list_equal(cplist_first, cplist_second)) ? true : false;
}

/**
 * Assign list element with an exist list container.
 */
void list_assign(list_t* plist_dest, const list_t* cplist_src)
{
    assert(plist_dest != NULL);
    assert(cplist_src != NULL);
    assert(_list_is_inited(plist_dest));
    assert(_list_is_inited(cplist_src));
    assert(_list_same_type(plist_dest, cplist_src));

    if (list_equal(plist_dest, cplist_src)) {
        return;
    }

    list_assign_range(plist_dest, list_begin(cplist_src), list_end(cplist_src));
}

/**
 * Assign list element with an exist list container range.
 */
void list_assign_range(list_t* plist_list, iterator_t it_begin, iterator_t it_end)
{
    iterator_t it_dest;
    iterator_t it_dest_begin;
    iterator_t it_dest_end;
    iterator_t it_src;
    bool_t     b_result = false;

    assert(plist_list != NULL);
    assert(_list_is_inited(plist_list));
    assert(_list_same_iterator_type(plist_list, it_begin));
    assert(_list_same_iterator_type(plist_list, it_end));
    /*assert(!_list_iterator_belong_to_list(plist_list, it_begin));*/
    /*assert(!_list_iterator_belong_to_list(plist_list, it_end));*/
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));

    list_resize(plist_list, iterator_distance(it_begin, it_end));
    it_dest_begin = list_begin(plist_list);
    it_dest_end = list_end(plist_list);

    /* copy value form varg */
    for (it_dest = it_dest_begin, it_src = it_begin;
         !iterator_equal(it_dest, it_dest_end) && !iterator_equal(it_src, it_end);
         it_dest = iterator_next(it_dest), it_src = iterator_next(it_src)) {
        b_result = _GET_LIST_TYPE_SIZE(plist_list);
        _GET_LIST_TYPE_COPY_FUNCTION(plist_list)(
            _iterator_get_pointer_ignore_cstr(it_dest),
            _iterator_get_pointer_ignore_cstr(it_src), &b_result);
        assert(b_result);
    }
    assert(iterator_equal(it_dest, it_dest_end) && iterator_equal(it_src, it_end));
}

/**
 * Assign list element with an exist list container array.
 */
void list_assign_array(list_t* plist_list, const void* cpv_array, size_t t_count)
{
    iterator_t it_dest;
    iterator_t it_begin;
    iterator_t it_end;
    bool_t     b_result = false;
    size_t     i = 0;

    assert(plist_list != NULL);
    assert(_list_is_inited(plist_list));
    assert(cpv_array != NULL);

    list_resize(plist_list, t_count);
    it_begin = list_begin(plist_list);
    it_end = list_end(plist_list);

    /*
     * Copy the elements from src array to dest list.
     * The array of c builtin and user define or cstl builtin are different,
     * the elements of c builtin array are element itself, but the elements of 
     * c string, user define or cstl are pointer of element.
     */
    if (strncmp(_GET_LIST_TYPE_BASENAME(plist_list), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        /*
         * We need built a string_t for c string element.
         */
        string_t* pstr_elem = create_string();
        assert(pstr_elem != NULL);
        string_init(pstr_elem);

        for (it_dest = it_begin, i = 0;
             !iterator_equal(it_dest, it_end) && i < t_count;
             it_dest = iterator_next(it_dest), ++i) {
            string_assign_cstr(pstr_elem, *((const char**)cpv_array + i));
            b_result = _GET_LIST_TYPE_SIZE(plist_list);
            _GET_LIST_TYPE_COPY_FUNCTION(plist_list)(
                _iterator_get_pointer_ignore_cstr(it_dest), pstr_elem, &b_result);
            assert(b_result);
        }
        string_destroy(pstr_elem);
    } else if (_GET_LIST_TYPE_STYLE(plist_list) == _TYPE_C_BUILTIN) {
        for (it_dest = it_begin, i = 0;
             !iterator_equal(it_dest, it_end) && i < t_count;
             it_dest = iterator_next(it_dest), ++i) {
            b_result = _GET_LIST_TYPE_SIZE(plist_list);
            _GET_LIST_TYPE_COPY_FUNCTION(plist_list)(
                _iterator_get_pointer_ignore_cstr(it_dest),
                (unsigned char*)cpv_array + i * _GET_LIST_TYPE_SIZE(plist_list), &b_result);
            assert(b_result);
        }
    } else {
        for (it_dest = it_begin, i = 0;
             !iterator_equal(it_dest, it_end) && i < t_count;
             it_dest = iterator_next(it_dest), ++i) {
            b_result = _GET_LIST_TYPE_SIZE(plist_list);
            _GET_LIST_TYPE_COPY_FUNCTION(plist_list)(
                _iterator_get_pointer_ignore_cstr(it_dest), *((void**)cpv_array + i), &b_result);
            assert(b_result);
        }
    }
    assert(iterator_equal(it_dest, it_end) && i == t_count);
}

/**
 * Swap list datas.
 */
void list_swap(list_t* plist_first, list_t* plist_second)
{
    list_t list_tmp;   /* the temporary list */

    assert(plist_first != NULL);
    assert(plist_second != NULL);
    assert(_list_is_inited(plist_first));
    assert(_list_is_inited(plist_second));
    assert(_list_same_type(plist_first, plist_second));

    if (list_equal(plist_first, plist_second)) {
        return;
    }

    list_tmp = *plist_first;
    *plist_first = *plist_second;
    *plist_second = list_tmp;
}

/**
 * Access first list data.
 */
void* list_front(const list_t* cplist_list)
{
    assert(cplist_list != NULL);
    assert(_list_is_inited(cplist_list));
    assert(!list_empty(cplist_list));

    return (void*)iterator_get_pointer(list_begin(cplist_list));
}

/**
 * Access first last data.
 */
void* list_back(const list_t* cplist_list)
{
    assert(cplist_list != NULL);
    assert(_list_is_inited(cplist_list));
    assert(!list_empty(cplist_list));

    return (void*)iterator_get_pointer(iterator_prev(list_end(cplist_list)));
}

/**
 * Return a iterator to the first element in the list container.
 */
list_iterator_t list_begin(const list_t* cplist_list)
{
    list_iterator_t it_begin;  /* new list iterator */

    assert(cplist_list != NULL);
    assert(_list_is_inited(cplist_list));

    it_begin = _create_list_iterator();
    _LIST_ITERATOR_COREPOS(it_begin) = (_byte_t*)(cplist_list->_pt_node->_pt_next);
    _ITERATOR_CONTAINER(it_begin) = (list_t*)cplist_list;

    return it_begin;
}

/**
 * Return a iterator that points just beyond the end of list container.
 */
list_iterator_t list_end(const list_t* cplist_list)
{
    list_iterator_t it_end;  /* new list iterator */

    assert(cplist_list != NULL);
    assert(_list_is_inited(cplist_list));

    it_end = _create_list_iterator();
    _LIST_ITERATOR_COREPOS(it_end) = (_byte_t*)(cplist_list->_pt_node);
    _ITERATOR_CONTAINER(it_end) = (list_t*)cplist_list;

    return it_end;
}

list_reverse_iterator_t list_rbegin(const list_t* cplist_list)
{
    list_reverse_iterator_t it_rbegin;   /* new list reverse iterator */

    assert(cplist_list != NULL);
    assert(_list_is_inited(cplist_list));

    it_rbegin = _create_list_iterator();
    _LIST_ITERATOR_COREPOS(it_rbegin) = (_byte_t*)(cplist_list->_pt_node->_pt_prev);
    _ITERATOR_CONTAINER(it_rbegin) = (list_t*)cplist_list;

    return it_rbegin;
}

list_reverse_iterator_t list_rend(const list_t* cplist_list)
{
    list_reverse_iterator_t it_rend;  /* new list reverse iterator */

    assert(cplist_list != NULL);
    assert(_list_is_inited(cplist_list));

    it_rend = _create_list_iterator();
    _LIST_ITERATOR_COREPOS(it_rend) = (_byte_t*)(cplist_list->_pt_node);
    _ITERATOR_CONTAINER(it_rend) = (list_t*)cplist_list;

    return it_rend;
}

/**
 * Insert a range of elements into list at a specificed position.
 */
void list_insert_range(list_t* plist_list, list_iterator_t it_pos, iterator_t it_begin, iterator_t it_end)
{
    _listnode_t* plist_begin = NULL;    /* the begin pointer of copy list */
    _listnode_t* plist_end = NULL;      /* the end pointer of copy list */
    _listnode_t* pt_node = NULL;         /* the new allocate node */
    bool_t       b_result = false;
    iterator_t   it_iter;

    assert(plist_list != NULL);
    assert(_list_is_inited(plist_list));
    assert(_list_iterator_belong_to_list(plist_list, it_pos));
    /*assert(!_list_iterator_belong_to_list(plist_list, it_begin));*/
    /*assert(!_list_iterator_belong_to_list(plist_list, it_end));*/
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));
    assert(_list_same_iterator_type(plist_list, it_begin));
    assert(_list_same_iterator_type(plist_list, it_end));

    /* allocate the copy list of range [it_begin, it_end) */
    for (it_iter = it_begin; !iterator_equal(it_iter, it_end); it_iter = iterator_next(it_iter)) {
        pt_node = _alloc_allocate(&plist_list->_t_allocator, _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(plist_list)), 1);
        assert(pt_node != NULL);
        pt_node->_pt_next = pt_node->_pt_prev = NULL;
        _list_init_node_auxiliary(plist_list, pt_node);
        b_result = _GET_LIST_TYPE_SIZE(plist_list);
        _GET_LIST_TYPE_COPY_FUNCTION(plist_list)(
            pt_node->_pby_data, _iterator_get_pointer_ignore_cstr(it_iter), &b_result);
        assert(b_result);

        if (plist_begin == NULL) {
            assert(plist_end == NULL);
            plist_begin = plist_end = pt_node;
        } else {
            assert(plist_end != NULL);
            plist_end->_pt_next = pt_node;
            pt_node->_pt_prev = plist_end;
            plist_end = plist_end->_pt_next;
        }
        pt_node = NULL;
    }
    /* insert the list into the list */
    if (plist_begin != NULL && plist_end != NULL) {
        plist_begin->_pt_prev = ((_listnode_t*)_LIST_ITERATOR_COREPOS(it_pos))->_pt_prev;
        plist_end->_pt_next = (_listnode_t*)_LIST_ITERATOR_COREPOS(it_pos);
        ((_listnode_t*)_LIST_ITERATOR_COREPOS(it_pos))->_pt_prev->_pt_next = plist_begin;
        ((_listnode_t*)_LIST_ITERATOR_COREPOS(it_pos))->_pt_prev = plist_end;
    }
}

/**
 * Insert a array of elements into list at a specificed position.
 */
void list_insert_array(list_t* plist_list, list_iterator_t it_pos, const void* cpv_array, size_t t_count)
{
    _listnode_t* plist_begin = NULL;    /* the begin pointer of copy list */
    _listnode_t* plist_end = NULL;      /* the end pointer of copy list */
    _listnode_t* pt_node = NULL;         /* the new allocate node */
    bool_t       b_result = false;
    size_t       i = 0;

    assert(plist_list != NULL);
    assert(_list_is_inited(plist_list));
    assert(_list_iterator_belong_to_list(plist_list, it_pos));
    assert(cpv_array != NULL);

    /*
     * Copy the elements from src array to dest list.
     * The array of c builtin and user define or cstl builtin are different,
     * the elements of c builtin array are element itself, but the elements of 
     * c string, user define or cstl are pointer of element.
     */
    if (strncmp(_GET_LIST_TYPE_BASENAME(plist_list), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        /*
         * We need built a string_t for c string element.
         */
        string_t* pstr_elem = create_string();
        assert(pstr_elem != NULL);
        string_init(pstr_elem);
        for (i = 0; i < t_count; ++i) {
            string_assign_cstr(pstr_elem, *((const char**)cpv_array + i));
            pt_node = _alloc_allocate(&plist_list->_t_allocator, _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(plist_list)), 1);
            assert(pt_node != NULL);

            pt_node->_pt_next = pt_node->_pt_prev = NULL;
            _list_init_node_auxiliary(plist_list, pt_node);
            b_result = _GET_LIST_TYPE_SIZE(plist_list);
            _GET_LIST_TYPE_COPY_FUNCTION(plist_list)(pt_node->_pby_data, pstr_elem, &b_result);
            assert(b_result);

            if (plist_begin == NULL) {
                assert(plist_end == NULL);
                plist_begin = plist_end = pt_node;
            } else {
                assert(plist_end != NULL);
                plist_end->_pt_next = pt_node;
                pt_node->_pt_prev = plist_end;
                plist_end = plist_end->_pt_next;
            }
            pt_node = NULL;
        }
        string_destroy(pstr_elem);
    } else if (_GET_LIST_TYPE_STYLE(plist_list) == _TYPE_C_BUILTIN) {
        for (i = 0; i < t_count; ++i) {
            pt_node = _alloc_allocate(&plist_list->_t_allocator, _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(plist_list)), 1);
            assert(pt_node != NULL);

            pt_node->_pt_next = pt_node->_pt_prev = NULL;
            _list_init_node_auxiliary(plist_list, pt_node);
            b_result = _GET_LIST_TYPE_SIZE(plist_list);
            _GET_LIST_TYPE_COPY_FUNCTION(plist_list)(
                pt_node->_pby_data, (unsigned char*)cpv_array + i * _GET_LIST_TYPE_SIZE(plist_list), &b_result);
            assert(b_result);

            if (plist_begin == NULL) {
                assert(plist_end == NULL);
                plist_begin = plist_end = pt_node;
            } else {
                assert(plist_end != NULL);
                plist_end->_pt_next = pt_node;
                pt_node->_pt_prev = plist_end;
                plist_end = plist_end->_pt_next;
            }
            pt_node = NULL;
        }
    } else {
        for (i = 0; i < t_count; ++i) {
            pt_node = _alloc_allocate(&plist_list->_t_allocator, _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(plist_list)), 1);
            assert(pt_node != NULL);

            pt_node->_pt_next = pt_node->_pt_prev = NULL;
            _list_init_node_auxiliary(plist_list, pt_node);
            b_result = _GET_LIST_TYPE_SIZE(plist_list);
            _GET_LIST_TYPE_COPY_FUNCTION(plist_list)(pt_node->_pby_data, *((void**)cpv_array + i), &b_result);
            assert(b_result);

            if (plist_begin == NULL) {
                assert(plist_end == NULL);
                plist_begin = plist_end = pt_node;
            } else {
                assert(plist_end != NULL);
                plist_end->_pt_next = pt_node;
                pt_node->_pt_prev = plist_end;
                plist_end = plist_end->_pt_next;
            }
            pt_node = NULL;
        }
    }

    /* insert the list into the list */
    if (plist_begin != NULL && plist_end != NULL) {
        plist_begin->_pt_prev = ((_listnode_t*)_LIST_ITERATOR_COREPOS(it_pos))->_pt_prev;
        plist_end->_pt_next = (_listnode_t*)_LIST_ITERATOR_COREPOS(it_pos);
        ((_listnode_t*)_LIST_ITERATOR_COREPOS(it_pos))->_pt_prev->_pt_next = plist_begin;
        ((_listnode_t*)_LIST_ITERATOR_COREPOS(it_pos))->_pt_prev = plist_end;
    }
}

/**
 * Delete the element at the end of list.
 */
void list_pop_back(list_t* plist_list)
{
    _listnode_t* pt_node = NULL;    /* the delete node */
    bool_t       b_result = false;

    assert(plist_list != NULL);
    assert(_list_is_inited(plist_list));
    assert(!list_empty(plist_list));

    /* extrace the back node from the list */
    pt_node = plist_list->_pt_node->_pt_prev;
    pt_node->_pt_prev->_pt_next = plist_list->_pt_node;
    plist_list->_pt_node->_pt_prev = pt_node->_pt_prev;

    /* destroy deleted node */
    b_result = _GET_LIST_TYPE_SIZE(plist_list);
    _GET_LIST_TYPE_DESTROY_FUNCTION(plist_list)(pt_node->_pby_data, &b_result);
    assert(b_result);
    _alloc_deallocate(&plist_list->_t_allocator, pt_node, _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(plist_list)), 1);
}

/**
 * Delete the element at the begin of list.
 */
void list_pop_front(list_t* plist_list)
{
    _listnode_t* pt_node = NULL;    /* the delete node */
    bool_t       b_result = false;

    assert(plist_list != NULL);
    assert(_list_is_inited(plist_list));
    assert(!list_empty(plist_list));

    /* extrac the first node from the list */
    pt_node = plist_list->_pt_node->_pt_next;
    plist_list->_pt_node->_pt_next = pt_node->_pt_next;
    pt_node->_pt_next->_pt_prev = plist_list->_pt_node;
    /* destroy deleted node */
    b_result = _GET_LIST_TYPE_SIZE(plist_list);
    _GET_LIST_TYPE_DESTROY_FUNCTION(plist_list)(pt_node->_pby_data, &b_result);
    assert(b_result);
    _alloc_deallocate(&plist_list->_t_allocator, pt_node, _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(plist_list)), 1);
}

/**
 * Removes an element in list from specificed position.
 */
list_iterator_t list_erase(list_t* plist_list, list_iterator_t it_pos)
{
    _listnode_t* pt_node = NULL;    /* the delete node */
    bool_t       b_result = false;

    assert(plist_list != NULL);
    assert(_list_is_inited(plist_list));
    assert(_list_iterator_belong_to_list(plist_list, it_pos));
    assert(!iterator_equal(it_pos, list_end(plist_list)));

    pt_node = (_listnode_t*)_LIST_ITERATOR_COREPOS(it_pos);
    _LIST_ITERATOR_COREPOS(it_pos) = (_byte_t*)(pt_node->_pt_next);
    /* extrac the node from list */
    b_result = _GET_LIST_TYPE_SIZE(plist_list);
    _GET_LIST_TYPE_DESTROY_FUNCTION(plist_list)(pt_node->_pby_data, &b_result);
    assert(b_result);
    pt_node->_pt_prev->_pt_next = pt_node->_pt_next;
    pt_node->_pt_next->_pt_prev = pt_node->_pt_prev;
    _alloc_deallocate(&plist_list->_t_allocator, pt_node, _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(plist_list)), 1);

    return it_pos;
}

/**
 * Removes a range of elements in list from specificed position.
 */
list_iterator_t list_erase_range(list_t* plist_list, list_iterator_t it_begin, list_iterator_t it_end)
{
    assert(plist_list != NULL);
    assert(_list_is_inited(plist_list));
    assert(_list_iterator_belong_to_list(plist_list, it_begin));
    assert(_list_iterator_belong_to_list(plist_list, it_end));
    assert(iterator_equal(it_begin, it_end) || _list_iterator_before(it_begin, it_end));

    while (!iterator_equal(it_begin, it_end)) {
        it_begin = list_erase(plist_list, it_begin);
    }

    return it_end;
}

/**
 * Remove elements from a list for which a specificed predicate is satisfied.
 */
void list_remove_if(list_t* plist_list, ufun_t ufun_op)
{
    list_iterator_t it_pos;    /* the delete position */
    list_iterator_t it_end;
    bool_t          b_result = false;

    assert(plist_list != NULL);
    assert(_list_is_inited(plist_list));

    if (ufun_op == NULL) {
        ufun_op = fun_default_unary;
    }

    it_pos = list_begin(plist_list);
    it_end = list_end(plist_list);
    while (!iterator_equal(it_pos, it_end)) {
        (*ufun_op)(iterator_get_pointer(it_pos), &b_result);
        it_pos = b_result ? list_erase(plist_list, it_pos) : iterator_next(it_pos);
    }
}

/**
 * Specifies a new size of a list.
 */
void list_resize(list_t* plist_list, size_t t_resize)
{
    _listnode_t* pt_node = NULL; /* the node for allocate */
    size_t       t_size = 0;     /* the list size */
    size_t       i = 0;

    assert(plist_list != NULL);
    assert(_list_is_inited(plist_list));

    t_size = list_size(plist_list);
    if (t_resize < t_size) {
        for (i = 0; i < t_size - t_resize; ++i) {
            list_pop_back(plist_list);
        }
    } else {
        for (i = 0; i < t_resize - t_size; ++i) {
            pt_node = _alloc_allocate(&plist_list->_t_allocator, _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(plist_list)), 1);
            assert(pt_node != NULL);
            _list_init_node_auxiliary(plist_list, pt_node);

            pt_node->_pt_next = plist_list->_pt_node;
            pt_node->_pt_prev = plist_list->_pt_node->_pt_prev;
            plist_list->_pt_node->_pt_prev->_pt_next = pt_node;
            plist_list->_pt_node->_pt_prev = pt_node;
            pt_node = NULL;
        }
    }
}

/**
 * Erases the elements of clear.
 */
void list_clear(list_t* plist_list)
{
    assert(plist_list != NULL);
    assert(_list_is_inited(plist_list));

    list_erase_range(plist_list, list_begin(plist_list), list_end(plist_list));
}

/**
 * Removes adjacent duplicate elements from a list.
 */
void list_unique(list_t* plist_list)
{
    list_iterator_t it_pos;
    _listnode_t*    pt_node = NULL;   /* current node */
    bool_t          b_less = false;
    bool_t          b_greater = false;

    assert(plist_list != NULL);
    assert(_list_is_inited(plist_list));

    pt_node = plist_list->_pt_node->_pt_next->_pt_next;
    while (pt_node != plist_list->_pt_node) {
        b_less = b_greater = _GET_LIST_TYPE_SIZE(plist_list);
        _GET_LIST_TYPE_LESS_FUNCTION(plist_list)(pt_node->_pt_prev->_pby_data, pt_node->_pby_data, &b_less);
        _GET_LIST_TYPE_LESS_FUNCTION(plist_list)(pt_node->_pby_data, pt_node->_pt_prev->_pby_data, &b_greater);
        if (b_less || b_greater) {
            pt_node = pt_node->_pt_next;
        } else {
            it_pos = _create_list_iterator();
            _ITERATOR_CONTAINER(it_pos) = plist_list;
            _LIST_ITERATOR_COREPOS(it_pos) = (_byte_t*)pt_node;
            it_pos = list_erase(plist_list, it_pos);
            pt_node = (_listnode_t*)_LIST_ITERATOR_COREPOS(it_pos);
        }
    }
}

/**
 * Removes adjacent elements that satisfy some other binary predicate from a list.
 */
void list_unique_if(list_t* plist_list, bfun_t bfun_op)
{
    list_iterator_t it_pos;
    list_iterator_t it_prev;
    list_iterator_t it_end;
    bool_t          b_result = false;

    assert(plist_list != NULL);
    assert(_list_is_inited(plist_list));

    if (bfun_op == NULL) {
        bfun_op = fun_default_binary;
    }

    if (list_size(plist_list) <= 1) {
        return;
    }

    it_prev = list_begin(plist_list);
    it_pos = iterator_next(it_prev);
    it_end = list_end(plist_list);
    while (!iterator_equal(it_pos, it_end)) {
        (*bfun_op)(iterator_get_pointer(it_prev), iterator_get_pointer(it_pos), &b_result);
        if (b_result) {
            it_pos = list_erase(plist_list, it_pos);
        } else {
            it_prev = iterator_next(it_prev);
            it_pos = iterator_next(it_pos);
        }
    }
}

/**
 * Removes elements from the source list and insert into the target list.
 */
void list_splice(list_t* plist_list, list_iterator_t it_pos, list_t* plist_src)
{
    assert(plist_list != NULL);
    assert(plist_src != NULL);
    assert(_list_is_inited(plist_list));
    assert(_list_is_inited(plist_src));
    assert(_list_same_type(plist_list, plist_src));
    assert(_list_iterator_belong_to_list(plist_list, it_pos));

    if (plist_list != plist_src) {
        _list_transfer(it_pos, list_begin(plist_src), list_end(plist_src));
    }
}

/**
 * Removes element from the source list and insert into the target list.
 */
void list_splice_pos(list_t* plist_list, list_iterator_t it_pos, list_t* plist_src, list_iterator_t it_src)
{
#ifdef NDEBUG
    list_t* plist_avoidwarning1 = NULL;
    list_t* plist_avoidwarning2 = NULL;
    plist_avoidwarning1 = plist_list;
    plist_avoidwarning2 = plist_src;
#endif

    assert(plist_list != NULL);
    assert(plist_src != NULL);
    assert(_list_is_inited(plist_list));
    assert(_list_is_inited(plist_src));
    assert(_list_same_type(plist_list, plist_src));
    assert(_list_iterator_belong_to_list(plist_list, it_pos));
    assert(_list_iterator_belong_to_list(plist_src, it_src));
    assert(!iterator_equal(it_src, list_end(plist_src)));

    _list_transfer(it_pos, it_src, iterator_next(it_src));
}

/**
 * Removes elements from the source list range and insert into the target list.
 */
void list_splice_range(
    list_t* plist_list, list_iterator_t it_pos, list_t* plist_src, list_iterator_t it_begin, list_iterator_t it_end)
{
#ifdef NDEBUG
    list_t* plist_avoidwarning1 = NULL;
    list_t* plist_avoidwarning2 = NULL;
    plist_avoidwarning1 = plist_list;
    plist_avoidwarning2 = plist_src;
#endif

    assert(plist_list != NULL);
    assert(plist_src != NULL);
    assert(_list_is_inited(plist_list));
    assert(_list_is_inited(plist_src));
    assert(_list_same_type(plist_list, plist_src));
    assert(_list_iterator_belong_to_list(plist_list, it_pos));
    assert(_list_iterator_belong_to_list(plist_src, it_begin));
    assert(_list_iterator_belong_to_list(plist_src, it_end));
    assert(iterator_equal(it_begin, it_end) || _list_iterator_before(it_begin, it_end));

    _list_transfer(it_pos, it_begin, it_end);
}

/**
 * Sort elements of list container.
 */
void list_sort(list_t* plist_list)
{
    assert(plist_list != NULL);
    assert(_list_is_inited(plist_list));

    list_sort_if(plist_list, NULL);
}

/**
 * Sort elements of list container with user-specifide order relation.
 */
void list_sort_if(list_t* plist_list, bfun_t bfun_op)
{
    assert(plist_list != NULL);
    assert(_list_is_inited(plist_list));

    _list_quick_sort(plist_list, plist_list->_pt_node->_pt_next, plist_list->_pt_node->_pt_prev, bfun_op);
}

/**
 * Merge two sorted list.
 */
void list_merge(list_t* plist_dest, list_t* plist_src)
{
    assert(plist_dest != NULL);
    assert(plist_src != NULL);
    assert(_list_is_inited(plist_dest));
    assert(_list_is_inited(plist_src));
    assert(_list_same_type(plist_dest, plist_src));

    list_merge_if(plist_dest, plist_src, NULL);
}

/**
 * Merge two sorted list.
 */
void list_merge_if(list_t* plist_dest, list_t* plist_src, bfun_t bfun_op)
{
    list_iterator_t it_dest;
    list_iterator_t it_dest_end;
    list_iterator_t it_src;
    list_iterator_t it_src_end;
    bool_t          b_result = false;

    assert(plist_dest != NULL);
    assert(plist_src != NULL);
    assert(_list_is_inited(plist_dest));
    assert(_list_is_inited(plist_src));
    assert(_list_same_type(plist_dest, plist_src));

    if (plist_dest == plist_src) {
        return;
    }

    it_dest = list_begin(plist_dest);
    it_dest_end = list_end(plist_dest);
    it_src = list_begin(plist_src);
    it_src_end = list_end(plist_src);

    if (bfun_op == NULL) {
        while (!iterator_equal(it_dest, it_dest_end) && !iterator_equal(it_src, it_src_end)) {
            _GET_LIST_TYPE_LESS_FUNCTION(plist_dest)(
                ((_listnode_t*)_LIST_ITERATOR_COREPOS(it_src))->_pby_data,
                ((_listnode_t*)_LIST_ITERATOR_COREPOS(it_dest))->_pby_data, &b_result);
            if (b_result) {
                it_src = iterator_next(it_src);
                _list_transfer(it_dest, iterator_prev(it_src), it_src);
            } else {
                it_dest = iterator_next(it_dest);
            }
        }
    } else {
        while (!iterator_equal(it_dest, it_dest_end) && !iterator_equal(it_src, it_src_end)) {
            (*bfun_op)(iterator_get_pointer(it_src), iterator_get_pointer(it_dest), &b_result);
            if (b_result) {
                it_src = iterator_next(it_src);
                _list_transfer(it_dest, iterator_prev(it_src), it_src);
            } else {
                it_dest = iterator_next(it_dest);
            }
        }
    }

    if (!iterator_equal(it_src, it_src_end)) {
        _list_transfer(it_dest_end, it_src, it_src_end);
    }
}

/**
 * Reverse the order of all elements.
 */
void list_reverse(list_t* plist_list)
{
    list_iterator_t it_pos;
    list_iterator_t it_end;

    assert(plist_list != NULL);
    assert(_list_is_inited(plist_list));

    if (list_size(plist_list) > 1) {
        it_pos = iterator_next(list_begin(plist_list));
        it_end = list_end(plist_list);
        while (!iterator_equal(it_pos, it_end)) {
            it_pos = iterator_next(it_pos);
            _list_transfer(list_begin(plist_list), iterator_prev(it_pos), it_pos);
        }
    }
}

/** local function implementation section **/

/** eof **/

