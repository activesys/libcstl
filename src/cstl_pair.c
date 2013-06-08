/*
 *  The implemetation of pair.
 *  Copyright (C)  2008 - 2012  Wangbo
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
#include <cstl/cstring.h>
#include <cstl/cutility.h>

#include "cstl_pair_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Initialize pair container.
 */
void pair_init(pair_t* ppair_pair)
{
    assert(ppair_pair != NULL);
    assert(_pair_is_created(ppair_pair));

    if ((ppair_pair->_pv_first = malloc(_GET_PAIR_FIRST_TYPE_SIZE(ppair_pair))) == NULL) {
        fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
        exit(EXIT_FAILURE);
    } else {
        memset(ppair_pair->_pv_first, 0x00, _GET_PAIR_FIRST_TYPE_SIZE(ppair_pair));
    }

    if ((ppair_pair->_pv_second = malloc(_GET_PAIR_SECOND_TYPE_SIZE(ppair_pair))) == NULL) {
        fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
        exit(EXIT_FAILURE);
    } else {
        memset(ppair_pair->_pv_second, 0x00, _GET_PAIR_SECOND_TYPE_SIZE(ppair_pair));
    }

    /* initialize new elements */
    if (_GET_PAIR_FIRST_TYPE_STYLE(ppair_pair) == _TYPE_CSTL_BUILTIN) {
        /* get element type name */
        char s_elemtypename[_TYPE_NAME_SIZE + 1];
        _type_get_elem_typename(_GET_PAIR_FIRST_TYPE_NAME(ppair_pair), s_elemtypename);
        _GET_PAIR_FIRST_TYPE_INIT_FUNCTION(ppair_pair)(ppair_pair->_pv_first, s_elemtypename);
    } else {
        bool_t b_result = _GET_PAIR_FIRST_TYPE_SIZE(ppair_pair);
        _GET_PAIR_FIRST_TYPE_INIT_FUNCTION(ppair_pair)(ppair_pair->_pv_first, &b_result);
        assert(b_result);
    }

    if (_GET_PAIR_SECOND_TYPE_STYLE(ppair_pair) == _TYPE_CSTL_BUILTIN) {
        /* get element type name */
        char s_elemtypename[_TYPE_NAME_SIZE + 1];
        _type_get_elem_typename(_GET_PAIR_SECOND_TYPE_NAME(ppair_pair), s_elemtypename);
        _GET_PAIR_SECOND_TYPE_INIT_FUNCTION(ppair_pair)(ppair_pair->_pv_second, s_elemtypename);
    } else {
        bool_t b_result = _GET_PAIR_SECOND_TYPE_SIZE(ppair_pair);
        _GET_PAIR_SECOND_TYPE_INIT_FUNCTION(ppair_pair)(ppair_pair->_pv_second, &b_result);
        assert(b_result);
    }
}

/**
 * Destroy pair.
 */
void pair_destroy(pair_t* ppair_pair)
{
    _pair_destroy_auxiliary(ppair_pair);
    free(ppair_pair);
}

/**
 * Initialize pair container with pair.
 */
void pair_init_copy(pair_t* ppair_dest, const pair_t* cppair_src)
{
    bool_t b_result = false;

    assert(ppair_dest != NULL);
    assert(cppair_src != NULL);
    assert(_pair_is_created(ppair_dest));
    assert(_pair_is_inited(cppair_src));
    assert(_pair_same_type(ppair_dest, cppair_src));

    /* initialize dest pair */
    pair_init(ppair_dest);

    /* copy element */
    b_result = _GET_PAIR_FIRST_TYPE_SIZE(ppair_dest);
    _GET_PAIR_FIRST_TYPE_COPY_FUNCTION(ppair_dest)(ppair_dest->_pv_first, cppair_src->_pv_first, &b_result);
    assert(b_result);

    b_result = _GET_PAIR_SECOND_TYPE_SIZE(ppair_dest);
    _GET_PAIR_SECOND_TYPE_COPY_FUNCTION(ppair_dest)(ppair_dest->_pv_second, cppair_src->_pv_second, &b_result);
    assert(b_result);

    ppair_dest->_bfun_mapkeycompare = cppair_src->_bfun_mapkeycompare;
    ppair_dest->_bfun_mapvaluecompare = cppair_src->_bfun_mapvaluecompare;
}

/**
 * Assign pair container.
 */
void pair_assign(pair_t* ppair_dest, const pair_t* cppair_src)
{
    assert(ppair_dest != NULL);
    assert(cppair_src != NULL);
    assert(_pair_is_inited(ppair_dest));
    assert(_pair_is_inited(cppair_src));
    assert(_pair_same_type(ppair_dest, cppair_src));

    if (pair_not_equal(ppair_dest, cppair_src)) {
        bool_t b_result = false;

        /* copy element */
        b_result = _GET_PAIR_FIRST_TYPE_SIZE(ppair_dest);
        _GET_PAIR_FIRST_TYPE_COPY_FUNCTION(ppair_dest)(ppair_dest->_pv_first, cppair_src->_pv_first, &b_result);
        assert(b_result);

        b_result = _GET_PAIR_SECOND_TYPE_SIZE(ppair_dest);
        _GET_PAIR_SECOND_TYPE_COPY_FUNCTION(ppair_dest)(ppair_dest->_pv_second, cppair_src->_pv_second, &b_result);
        assert(b_result);
    }

    ppair_dest->_bfun_mapkeycompare = cppair_src->_bfun_mapkeycompare;
    ppair_dest->_bfun_mapvaluecompare = cppair_src->_bfun_mapvaluecompare;
}

/**
 * Access pair first element.
 */
void* pair_first(const pair_t* cppair_pair)
{
    assert(cppair_pair != NULL);
    assert(_pair_is_inited(cppair_pair));

    /* char* */
    if (strncmp(_GET_PAIR_FIRST_TYPE_BASENAME(cppair_pair), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        return (void*)string_c_str((string_t*)cppair_pair->_pv_first);
    } else {
        return cppair_pair->_pv_first;
    }
}

/**
 * Access pair second element.
 */
void* pair_second(const pair_t* cppair_pair)
{
    assert(cppair_pair != NULL);
    assert(_pair_is_inited(cppair_pair));

    /* char* */
    if (strncmp(_GET_PAIR_SECOND_TYPE_BASENAME(cppair_pair), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        return (void*)string_c_str((string_t*)cppair_pair->_pv_second);
    } else {
        return cppair_pair->_pv_second;
    }
}

/**
 * Tests if the two pair are equal.
 */
bool_t pair_equal(const pair_t* cppair_first, const pair_t* cppair_second)
{
    bool_t b_less = false;
    bool_t b_greater = false;

    assert(cppair_first != NULL);
    assert(cppair_second != NULL);
    assert(_pair_is_inited(cppair_first));
    assert(_pair_is_inited(cppair_second));
    assert(_pair_same_type(cppair_first, cppair_second));

    if (cppair_first == cppair_second) {
        return true;
    }

    /* compare first */
    b_less = b_greater = _GET_PAIR_FIRST_TYPE_SIZE(cppair_first);
    _GET_PAIR_FIRST_TYPE_LESS_FUNCTION(cppair_first)(cppair_first->_pv_first, cppair_second->_pv_first, &b_less);
    _GET_PAIR_FIRST_TYPE_LESS_FUNCTION(cppair_first)(cppair_second->_pv_first, cppair_first->_pv_first, &b_greater);
    if (b_less || b_greater) {
        return false;
    }

    /* compare second */
    b_less = b_greater = _GET_PAIR_SECOND_TYPE_SIZE(cppair_first);
    _GET_PAIR_SECOND_TYPE_LESS_FUNCTION(cppair_first)(cppair_first->_pv_second, cppair_second->_pv_second, &b_less);
    _GET_PAIR_SECOND_TYPE_LESS_FUNCTION(cppair_first)(cppair_second->_pv_second, cppair_first->_pv_second, &b_greater);
    if (b_less || b_greater) {
        return false;
    }

    return true;
}

/**
 * Tests if the two pair are not equal.
 */
bool_t pair_not_equal(const pair_t* cppair_first, const pair_t* cppair_second)
{
    return !pair_equal(cppair_first, cppair_second);
}

/**
 * Tests if the first pair is less than the second pair.
 */
bool_t pair_less(const pair_t* cppair_first, const pair_t* cppair_second)
{
    bool_t b_result = false;

    assert(cppair_first != NULL);
    assert(cppair_second != NULL);
    assert(_pair_is_inited(cppair_first));
    assert(_pair_is_inited(cppair_second));
    assert(_pair_same_type(cppair_first, cppair_second));

    if (cppair_first == cppair_second) {
        return false;
    }

    /* compare first */
    b_result = _GET_PAIR_FIRST_TYPE_SIZE(cppair_first);
    _GET_PAIR_FIRST_TYPE_LESS_FUNCTION(cppair_first)(cppair_first->_pv_first, cppair_second->_pv_first, &b_result);
    if (b_result) {
        return true;
    }
    b_result = _GET_PAIR_FIRST_TYPE_SIZE(cppair_first);
    _GET_PAIR_FIRST_TYPE_LESS_FUNCTION(cppair_first)(cppair_second->_pv_first, cppair_first->_pv_first, &b_result);
    if (b_result) {
        return false;
    }

    /* compare second */
    b_result = _GET_PAIR_SECOND_TYPE_SIZE(cppair_first);
    _GET_PAIR_SECOND_TYPE_LESS_FUNCTION(cppair_first)(cppair_first->_pv_second, cppair_second->_pv_second, &b_result);
    if (b_result) {
        return true;
    }
    b_result = _GET_PAIR_SECOND_TYPE_SIZE(cppair_first);
    _GET_PAIR_SECOND_TYPE_LESS_FUNCTION(cppair_first)(cppair_second->_pv_second, cppair_first->_pv_second, &b_result);
    if (b_result) {
        return false;
    }

    return false;
}

/**
 * Tests if the first pair is less than or equal to the second pair.
 */
bool_t pair_less_equal(const pair_t* cppair_first, const pair_t* cppair_second)
{
    return (pair_less(cppair_first, cppair_second) || pair_equal(cppair_first, cppair_second)) ? true : false;
}

/**
 * Tests if the first pair is greater than the second pair.
 */
bool_t pair_greater(const pair_t* cppair_first, const pair_t* cppair_second)
{
    return pair_less(cppair_second, cppair_first);
}

/**
 * Tests if the first pair is greater than or equal to the second pair.
 */
bool_t pair_greater_equal(const pair_t* cppair_first, const pair_t* cppair_second)
{
    return (pair_greater(cppair_first, cppair_second) || pair_equal(cppair_first, cppair_second)) ? true : false;
}

/** local function implementation section **/

/** eof **/

