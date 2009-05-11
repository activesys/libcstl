/*
 *  The implementation of tools.
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
#include <stdarg.h>

#include "citerator.h"
#include "cvector.h"
#include "cdeque.h"
#include "clist.h"
#include "cslist.h"
#include "cset.h"
#include "cmap.h"
#include "chash_set.h"
#include "chash_map.h"
#include "cstring.h"
#include "cutility.h"

#include "cstl_tools.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
bool_t _tools_valid_iterator_range(
    iterator_t t_first, iterator_t t_last, iteratortype_t t_limittype)
{
    return _iterator_same_type(t_first, t_last) &&
           _iterator_limit_type(t_first, t_limittype) &&
           (iterator_equal(t_first, t_last) || _iterator_before(t_first, t_last));
}

char* _tools_get_typename(iterator_t t_iterator)
{
    switch(t_iterator._t_containertype)
    {
    case _VECTOR_CONTAINER:
        return _GET_VECTOR_CONTAINER(t_iterator)->_sz_typename;
        break;
    case _DEQUE_CONTAINER:
        return _GET_DEQUE_CONTAINER(t_iterator)->_sz_typename;
        break;
    case _LIST_CONTAINER:
        return _GET_LIST_CONTAINER(t_iterator)->_sz_typename;
        break;
    case _SLIST_CONTAINER:
        return _GET_SLIST_CONTAINER(t_iterator)->_sz_typename;
        break;
    case _SET_CONTAINER:
#ifdef CSTL_SET_AVL_TREE
        return _GET_AVL_TREE(t_iterator)->_sz_typename;
#else
        return _GET_RB_TREE(t_iterator)->_sz_typename;
#endif
        break;
    case _MULTISET_CONTAINER:
#ifdef CSTL_MULTISET_AVL_TREE
        return _GET_AVL_TREE(t_iterator)->_sz_typename;
#else
        return _GET_RB_TREE(t_iterator)->_sz_typename;
#endif
        break;
    case _MAP_CONTAINER:
#ifdef CSTL_MAP_AVL_TREE
        return _GET_AVL_TREE(t_iterator)->_sz_typename;
#else
        return _GET_RB_TREE(t_iterator)->_sz_typename;
#endif
        break;
    case _MULTIMAP_CONTAINER:
#ifdef CSTL_MULTIMAP_AVL_TREE
        return _GET_AVL_TREE(t_iterator)->_sz_typename;
#else
        return _GET_RB_TREE(t_iterator)->_sz_typename;
#endif
        break;
    case _HASH_SET_CONTAINER:
        return _GET_HASHTABLE(t_iterator)->_sz_typename;
        break;
    case _HASH_MULTISET_CONTAINER:
        return _GET_HASHTABLE(t_iterator)->_sz_typename;
        break;
    case _HASH_MAP_CONTAINER:
        return _GET_HASHTABLE(t_iterator)->_sz_typename;
        break;
    case _HASH_MULTIMAP_CONTAINER:
        return _GET_HASHTABLE(t_iterator)->_sz_typename;
        break;
    case _BASIC_STRING_CONTAINER:
        return _GET_VECTOR_CONTAINER(t_iterator)->_sz_typename;
        break;
    default:
        assert(false);
        return NULL;
        break;
    }
}

size_t _tools_get_typesize(iterator_t t_iterator)
{
    switch(t_iterator._t_containertype)
    {
    case _VECTOR_CONTAINER:
        return _GET_VECTOR_CONTAINER(t_iterator)->_t_typesize;
        break;
    case _DEQUE_CONTAINER:
        return _GET_DEQUE_CONTAINER(t_iterator)->_t_typesize;
        break;
    case _LIST_CONTAINER:
        return _GET_LIST_CONTAINER(t_iterator)->_t_typesize;
        break;
    case _SLIST_CONTAINER:
        return _GET_SLIST_CONTAINER(t_iterator)->_t_typesize;
        break;
    case _SET_CONTAINER:
#ifdef CSTL_SET_AVL_TREE
        return _GET_AVL_TREE(t_iterator)->_t_typesize;
#else
        return _GET_RB_TREE(t_iterator)->_t_typesize;
#endif
        break;
    case _MULTISET_CONTAINER:
#ifdef CSTL_MULTISET_AVL_TREE
        return _GET_AVL_TREE(t_iterator)->_t_typesize;
#else
        return _GET_RB_TREE(t_iterator)->_t_typesize;
#endif
        break;
    case _MAP_CONTAINER:
#ifdef CSTL_MAP_AVL_TREE
        return _GET_AVL_TREE(t_iterator)->_t_typesize;
#else
        return _GET_RB_TREE(t_iterator)->_t_typesize;
#endif
        break;
    case _MULTIMAP_CONTAINER:
#ifdef CSTL_MULTIMAP_AVL_TREE
        return _GET_AVL_TREE(t_iterator)->_t_typesize;
#else
        return _GET_RB_TREE(t_iterator)->_t_typesize;
#endif
        break;
    case _HASH_SET_CONTAINER:
        return _GET_HASHTABLE(t_iterator)->_t_typesize;
        break;
    case _HASH_MULTISET_CONTAINER:
        return _GET_HASHTABLE(t_iterator)->_t_typesize;
        break;
    case _HASH_MAP_CONTAINER:
        return _GET_HASHTABLE(t_iterator)->_t_typesize;
        break;
    case _HASH_MULTIMAP_CONTAINER:
        return _GET_HASHTABLE(t_iterator)->_t_typesize;
        break;
    case _BASIC_STRING_CONTAINER:
        return _GET_VECTOR_CONTAINER(t_iterator)->_t_typesize;
        break;
    default:
        assert(false);
        return 0;
        break;
    }
}

bool_t _tools_same_elem_type(iterator_t t_first, iterator_t t_second)
{
    char sz_firstname[_ELEM_TYPE_NAME_SIZE + 1];
    char sz_secondname[_ELEM_TYPE_NAME_SIZE + 1];

    _get_builtin_type(_tools_get_typename(t_first), sz_firstname);
    _get_builtin_type(_tools_get_typename(t_second), sz_secondname);

    return strncmp(sz_firstname, sz_secondname, _ELEM_TYPE_NAME_SIZE) == 0 ? 
           true : false;
}

/** local function implementation section **/

/** eof **/

