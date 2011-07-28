/*
 *  The implemetation of pair.
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

#include <cstl/cstl_pair_private.h>
#include <cstl/cstl_pair.h>

#include <cstl/cstring.h>

#include "cstl_pair_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/* pair function */
void pair_init(pair_t* pt_pair)
{
    assert(pt_pair != NULL);
    assert(pt_pair->_pv_first == NULL && pt_pair->_pv_second == NULL);

    if((pt_pair->_pv_first = malloc(_GET_PAIR_FIRST_TYPE_SIZE(pt_pair))) == NULL)
    {
        fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        memset(pt_pair->_pv_first, 0x00, _GET_PAIR_FIRST_TYPE_SIZE(pt_pair));
    }

    if((pt_pair->_pv_second = malloc(_GET_PAIR_SECOND_TYPE_SIZE(pt_pair))) == NULL)
    {
        fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        memset(pt_pair->_pv_second, 0x00, _GET_PAIR_SECOND_TYPE_SIZE(pt_pair));
    }

    /* initialize new elements */
    if(_GET_PAIR_FIRST_TYPE_STYLE(pt_pair) == _TYPE_CSTL_BUILTIN)
    {
        /* get element type name */
        char s_elemtypename[_TYPE_NAME_SIZE + 1];
        _type_get_elem_typename(_GET_PAIR_FIRST_TYPE_NAME(pt_pair), s_elemtypename);

        _GET_PAIR_FIRST_TYPE_INIT_FUNCTION(pt_pair)(pt_pair->_pv_first, s_elemtypename);
    }
    else
    {
        bool_t t_result = _GET_PAIR_FIRST_TYPE_SIZE(pt_pair);
        _GET_PAIR_FIRST_TYPE_INIT_FUNCTION(pt_pair)(pt_pair->_pv_first, &t_result);
        assert(t_result);
    }

    if(_GET_PAIR_SECOND_TYPE_STYLE(pt_pair) == _TYPE_CSTL_BUILTIN)
    {
        /* get element type name */
        char s_elemtypename[_TYPE_NAME_SIZE + 1];
        _type_get_elem_typename(_GET_PAIR_SECOND_TYPE_NAME(pt_pair), s_elemtypename);

        _GET_PAIR_SECOND_TYPE_INIT_FUNCTION(pt_pair)(pt_pair->_pv_second, s_elemtypename);
    }
    else
    {
        bool_t t_result = _GET_PAIR_SECOND_TYPE_SIZE(pt_pair);
        _GET_PAIR_SECOND_TYPE_INIT_FUNCTION(pt_pair)(pt_pair->_pv_second, &t_result);
        assert(t_result);
    }
}

void pair_destroy(pair_t* pt_pair)
{
    _pair_destroy_auxiliary(pt_pair);
    free(pt_pair);
}

void pair_init_copy(pair_t* pt_pairdest, const pair_t* cpt_pairsrc)
{
    bool_t t_result = false;

    assert(pt_pairdest != NULL && cpt_pairsrc != NULL);
    assert(cpt_pairsrc->_pv_first != NULL && cpt_pairsrc->_pv_second != NULL);
    assert(_pair_same_type(pt_pairdest, cpt_pairsrc));

    /* initialize dest pair */
    pair_init(pt_pairdest);

    /* copy element */
    t_result = _GET_PAIR_FIRST_TYPE_SIZE(pt_pairdest);
    _GET_PAIR_FIRST_TYPE_COPY_FUNCTION(pt_pairdest)(
        pt_pairdest->_pv_first, cpt_pairsrc->_pv_first, &t_result);
    assert(t_result);

    t_result = _GET_PAIR_SECOND_TYPE_SIZE(pt_pairdest);
    _GET_PAIR_SECOND_TYPE_COPY_FUNCTION(pt_pairdest)(
        pt_pairdest->_pv_second, cpt_pairsrc->_pv_second, &t_result);
    assert(t_result);

    pt_pairdest->_t_mapkeycompare = cpt_pairsrc->_t_mapkeycompare;
    pt_pairdest->_t_mapvaluecompare = cpt_pairsrc->_t_mapvaluecompare;
}

void pair_assign(pair_t* pt_pairdest, const pair_t* cpt_pairsrc)
{
    bool_t t_result = false;

    assert(pt_pairdest != NULL && cpt_pairsrc != NULL);
    assert(cpt_pairsrc->_pv_first != NULL && cpt_pairsrc->_pv_second != NULL);
    assert(_pair_same_type(pt_pairdest, cpt_pairsrc));

    /* copy element */
    t_result = _GET_PAIR_FIRST_TYPE_SIZE(pt_pairdest);
    _GET_PAIR_FIRST_TYPE_COPY_FUNCTION(pt_pairdest)(
        pt_pairdest->_pv_first, cpt_pairsrc->_pv_first, &t_result);
    assert(t_result);

    t_result = _GET_PAIR_SECOND_TYPE_SIZE(pt_pairdest);
    _GET_PAIR_SECOND_TYPE_COPY_FUNCTION(pt_pairdest)(
        pt_pairdest->_pv_second, cpt_pairsrc->_pv_second, &t_result);
    assert(t_result);

    pt_pairdest->_t_mapkeycompare = cpt_pairsrc->_t_mapkeycompare;
    pt_pairdest->_t_mapvaluecompare = cpt_pairsrc->_t_mapvaluecompare;
}

void* pair_first(const pair_t* cpt_pair)
{
    assert(cpt_pair != NULL);
    /* char* */
    if(strncmp(_GET_PAIR_FIRST_TYPE_BASENAME(cpt_pair), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        return (void*)string_c_str((string_t*)cpt_pair->_pv_first);
    }
    else
    {
        return cpt_pair->_pv_first;
    }
}

void* pair_second(const pair_t* cpt_pair)
{
    assert(cpt_pair != NULL);
    /* char* */
    if(strncmp(_GET_PAIR_SECOND_TYPE_BASENAME(cpt_pair), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        return (void*)string_c_str((string_t*)cpt_pair->_pv_second);
    }
    else
    {
        return cpt_pair->_pv_second;
    }
}

bool_t pair_equal(const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond)
{
    bool_t t_less = false;
    bool_t t_greater = false;

    assert(cpt_pairfirst != NULL && cpt_pairsecond != NULL);
    assert(cpt_pairfirst->_pv_first != NULL && cpt_pairfirst->_pv_second != NULL);
    assert(cpt_pairsecond->_pv_first != NULL && cpt_pairsecond->_pv_second != NULL);

    if(!_pair_same_type(cpt_pairfirst, cpt_pairsecond))
    {
        return false;
    }

    /* compare first */
    t_less = t_greater = _GET_PAIR_FIRST_TYPE_SIZE(cpt_pairfirst);
    _GET_PAIR_FIRST_TYPE_LESS_FUNCTION(cpt_pairfirst)(
        cpt_pairfirst->_pv_first, cpt_pairsecond->_pv_first, &t_less);
    _GET_PAIR_FIRST_TYPE_LESS_FUNCTION(cpt_pairfirst)(
        cpt_pairsecond->_pv_first, cpt_pairfirst->_pv_first, &t_greater);
    if(t_less || t_greater)
    {
        return false;
    }

    /* compare second */
    t_less = t_greater = _GET_PAIR_SECOND_TYPE_SIZE(cpt_pairfirst);
    _GET_PAIR_SECOND_TYPE_LESS_FUNCTION(cpt_pairfirst)(
        cpt_pairfirst->_pv_second, cpt_pairsecond->_pv_second, &t_less);
    _GET_PAIR_SECOND_TYPE_LESS_FUNCTION(cpt_pairfirst)(
        cpt_pairsecond->_pv_second, cpt_pairfirst->_pv_second, &t_greater);
    if(t_less || t_greater)
    {
        return false;
    }

    return true;
}

bool_t pair_not_equal(const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond)
{
    return !pair_equal(cpt_pairfirst, cpt_pairsecond);
}

bool_t pair_less(const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond)
{
    bool_t t_result = false;

    assert(_pair_same_type(cpt_pairfirst, cpt_pairsecond));

    /* compare first */
    t_result = _GET_PAIR_FIRST_TYPE_SIZE(cpt_pairfirst);
    _GET_PAIR_FIRST_TYPE_LESS_FUNCTION(cpt_pairfirst)(
        cpt_pairfirst->_pv_first, cpt_pairsecond->_pv_first, &t_result);
    if(t_result)
    {
        return true;
    }

    t_result = _GET_PAIR_FIRST_TYPE_SIZE(cpt_pairfirst);
    _GET_PAIR_FIRST_TYPE_LESS_FUNCTION(cpt_pairfirst)(
        cpt_pairsecond->_pv_first, cpt_pairfirst->_pv_first, &t_result);
    if(t_result)
    {
        return false;
    }

    /* compare second */
    t_result = _GET_PAIR_SECOND_TYPE_SIZE(cpt_pairfirst);
    _GET_PAIR_SECOND_TYPE_LESS_FUNCTION(cpt_pairfirst)(
        cpt_pairfirst->_pv_second, cpt_pairsecond->_pv_second, &t_result);
    if(t_result)
    {
        return true;
    }

    t_result = _GET_PAIR_SECOND_TYPE_SIZE(cpt_pairfirst);
    _GET_PAIR_SECOND_TYPE_LESS_FUNCTION(cpt_pairfirst)(
        cpt_pairsecond->_pv_second, cpt_pairfirst->_pv_second, &t_result);
    if(t_result)
    {
        return false;
    }

    return false;
}

bool_t pair_less_equal(const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond)
{
    return (pair_less(cpt_pairfirst, cpt_pairsecond) ||
            pair_equal(cpt_pairfirst, cpt_pairsecond)) ? true : false;
}

bool_t pair_greater(const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond)
{
    return pair_less(cpt_pairsecond, cpt_pairfirst);
}

bool_t pair_greater_equal(const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond)
{
    return (pair_greater(cpt_pairfirst, cpt_pairsecond) ||
            pair_equal(cpt_pairfirst, cpt_pairsecond)) ? true : false;
}

/** local function implementation section **/

/** eof **/

