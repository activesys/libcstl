/*
 *  The implemetation of pair.
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
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "cstl_alloc.h"
#include "cstl_types.h"

#include "cstl_pair.h"

#include "cstring.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/
/* macros for type informations */
#define _GET_PAIR_FIRST_TYPE_SIZE(pt_pair)\
    ((pt_pair)->_t_typeinfofirst._pt_type->_t_typesize)
#define _GET_PAIR_FIRST_TYPE_NAME(pt_pair)\
    ((pt_pair)->_t_typeinfofirst._sz_typename)
#define _GET_PAIR_FIRST_TYPE_BASENAME(pt_pair)\
    ((pt_pair)->_t_typeinfofirst._pt_type->_sz_typename)
#define _GET_PAIR_FIRST_TYPE_INIT_FUNCTION(pt_pair)\
    ((pt_pair)->_t_typeinfofirst._pt_type->_t_typeinit)
#define _GET_PAIR_FIRST_TYPE_COPY_FUNCTION(pt_pair)\
    ((pt_pair)->_t_typeinfofirst._pt_type->_t_typecopy)
#define _GET_PAIR_FIRST_TYPE_LESS_FUNCTION(pt_pair)\
    ((pt_pair)->_t_typeinfofirst._pt_type->_t_typeless)
#define _GET_PAIR_FIRST_TYPE_DESTROY_FUNCTION(pt_pair)\
    ((pt_pair)->_t_typeinfofirst._pt_type->_t_typedestroy)
#define _GET_PAIR_FIRST_TYPE_STYLE(pt_pair)\
    ((pt_pair)->_t_typeinfofirst._t_style)

#define _GET_PAIR_SECOND_TYPE_SIZE(pt_pair)\
    ((pt_pair)->_t_typeinfosecond._pt_type->_t_typesize)
#define _GET_PAIR_SECOND_TYPE_NAME(pt_pair)\
    ((pt_pair)->_t_typeinfosecond._sz_typename)
#define _GET_PAIR_SECOND_TYPE_BASENAME(pt_pair)\
    ((pt_pair)->_t_typeinfosecond._pt_type->_sz_typename)
#define _GET_PAIR_SECOND_TYPE_INIT_FUNCTION(pt_pair)\
    ((pt_pair)->_t_typeinfosecond._pt_type->_t_typeinit)
#define _GET_PAIR_SECOND_TYPE_COPY_FUNCTION(pt_pair)\
    ((pt_pair)->_t_typeinfosecond._pt_type->_t_typecopy)
#define _GET_PAIR_SECOND_TYPE_LESS_FUNCTION(pt_pair)\
    ((pt_pair)->_t_typeinfosecond._pt_type->_t_typeless)
#define _GET_PAIR_SECOND_TYPE_DESTROY_FUNCTION(pt_pair)\
    ((pt_pair)->_t_typeinfosecond._pt_type->_t_typedestroy)
#define _GET_PAIR_SECOND_TYPE_STYLE(pt_pair)\
    ((pt_pair)->_t_typeinfosecond._t_style)

/** local function prototype section **/
#ifndef NDEBUG
/*
 * Test the two pair is have the same type.
 */
static bool_t _pair_same_type(const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond);
#endif /* NDEBUG */

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/* private function */
pair_t* _create_pair(const char* s_typename)
{
    _typeinfo_t t_typeinfofirst;
    _typeinfo_t t_typeinfosecond;
    pair_t*     pt_newpair = NULL;

    assert(s_typename != NULL);

    /* get type information */
    _type_get_type_pair(&t_typeinfofirst, &t_typeinfosecond, s_typename);
    if(t_typeinfofirst._t_style == _TYPE_INVALID || t_typeinfosecond._t_style == _TYPE_INVALID)
    {
        return NULL;
    }

    if((pt_newpair = (pair_t*)malloc(sizeof(pair_t))) == NULL)
    {
        return NULL;
    }
    memset(pt_newpair->_t_typeinfofirst._sz_typename, '\0', _TYPE_NAME_SIZE + 1);
    strncpy(pt_newpair->_t_typeinfofirst._sz_typename,
        t_typeinfofirst._sz_typename, _TYPE_NAME_SIZE);
    pt_newpair->_t_typeinfofirst._pt_type = t_typeinfofirst._pt_type;
    pt_newpair->_t_typeinfofirst._t_style = t_typeinfofirst._t_style;

    memset(pt_newpair->_t_typeinfosecond._sz_typename, '\0', _TYPE_NAME_SIZE + 1);
    strncpy(pt_newpair->_t_typeinfosecond._sz_typename,
        t_typeinfosecond._sz_typename, _TYPE_NAME_SIZE);
    pt_newpair->_t_typeinfosecond._pt_type = t_typeinfosecond._pt_type;
    pt_newpair->_t_typeinfosecond._t_style = t_typeinfosecond._t_style;

    pt_newpair->first = NULL;
    pt_newpair->second = NULL;

    return pt_newpair;
}

void _pair_make_first(pair_t* pt_pair, ...)
{
    va_list val_elemlist;

    assert(pt_pair != NULL);
    assert(pt_pair->first != NULL && pt_pair->second != NULL);

    va_start(val_elemlist, pt_pair);
    _type_get_varg_value(&pt_pair->_t_typeinfofirst, val_elemlist, pt_pair->first);
}

void _pair_make_second(pair_t* pt_pair, ...)
{
    va_list val_elemlist;

    assert(pt_pair != NULL);
    assert(pt_pair->first != NULL && pt_pair->second != NULL);

    va_start(val_elemlist, pt_pair);
    _type_get_varg_value(&pt_pair->_t_typeinfosecond, val_elemlist, pt_pair->second);
}

/* pair function */
void pair_init(pair_t* pt_pair)
{
    assert(pt_pair != NULL);
    assert(pt_pair->first == NULL && pt_pair->second == NULL);

    if((pt_pair->first = malloc(_GET_PAIR_FIRST_TYPE_SIZE(pt_pair))) == NULL)
    {
        fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        memset(pt_pair->first, 0x00, _GET_PAIR_FIRST_TYPE_SIZE(pt_pair));
    }

    if((pt_pair->second = malloc(_GET_PAIR_SECOND_TYPE_SIZE(pt_pair))) == NULL)
    {
        fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        memset(pt_pair->second, 0x00, _GET_PAIR_SECOND_TYPE_SIZE(pt_pair));
    }

    /* initialize new elements */
    if(_GET_PAIR_FIRST_TYPE_STYLE(pt_pair) == _TYPE_CSTL_BUILTIN)
    {
        /* get element type name */
        char s_elemtypename[_TYPE_NAME_SIZE + 1];
        _type_get_elem_typename(_GET_PAIR_FIRST_TYPE_NAME(pt_pair), s_elemtypename);

        _GET_PAIR_FIRST_TYPE_INIT_FUNCTION(pt_pair)(pt_pair->first, s_elemtypename);
    }
    else
    {
        bool_t t_result = _GET_PAIR_FIRST_TYPE_SIZE(pt_pair);
        _GET_PAIR_FIRST_TYPE_INIT_FUNCTION(pt_pair)(pt_pair->first, &t_result);
        assert(t_result);
    }

    if(_GET_PAIR_SECOND_TYPE_STYLE(pt_pair) == _TYPE_CSTL_BUILTIN)
    {
        /* get element type name */
        char s_elemtypename[_TYPE_NAME_SIZE + 1];
        _type_get_elem_typename(_GET_PAIR_FIRST_TYPE_NAME(pt_pair), s_elemtypename);

        _GET_PAIR_SECOND_TYPE_INIT_FUNCTION(pt_pair)(pt_pair->second, s_elemtypename);
    }
    else
    {
        bool_t t_result = _GET_PAIR_SECOND_TYPE_SIZE(pt_pair);
        _GET_PAIR_SECOND_TYPE_INIT_FUNCTION(pt_pair)(pt_pair->second, &t_result);
        assert(t_result);
    }
}

void _pair_destroy_auxiliary(pair_t* pt_pair)
{
    bool_t t_result = false;

    assert(pt_pair != NULL);
    assert(pt_pair->first != NULL && pt_pair->second != NULL);

    /* destroy first */
    t_result = _GET_PAIR_FIRST_TYPE_SIZE(pt_pair);
    _GET_PAIR_FIRST_TYPE_DESTROY_FUNCTION(pt_pair)(pt_pair->first, &t_result);
    assert(t_result);
    free(pt_pair->first);
    pt_pair->first = NULL;

    /* destroy second */
    t_result = _GET_PAIR_SECOND_TYPE_SIZE(pt_pair);
    _GET_PAIR_SECOND_TYPE_DESTROY_FUNCTION(pt_pair)(pt_pair->second, &t_result);
    assert(t_result);
    free(pt_pair->second);
    pt_pair->second = NULL;
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
    assert(cpt_pairsrc->first != NULL && cpt_pairsrc->second != NULL);
    assert(_pair_same_type(pt_pairdest, cpt_pairsrc));

    /* initialize dest pair */
    pair_init(pt_pairdest);

    /* copy element */
    t_result = _GET_PAIR_FIRST_TYPE_SIZE(pt_pairdest);
    _GET_PAIR_FIRST_TYPE_COPY_FUNCTION(pt_pairdest)(
        pt_pairdest->first, cpt_pairsrc->first, &t_result);
    assert(t_result);

    t_result = _GET_PAIR_SECOND_TYPE_SIZE(pt_pairdest);
    _GET_PAIR_SECOND_TYPE_COPY_FUNCTION(pt_pairdest)(
        pt_pairdest->second, cpt_pairsrc->second, &t_result);
    assert(t_result);
}

void pair_assign(pair_t* pt_pairdest, const pair_t* cpt_pairsrc)
{
    bool_t t_result = false;

    assert(pt_pairdest != NULL && cpt_pairsrc != NULL);
    assert(cpt_pairsrc->first != NULL && cpt_pairsrc->second != NULL);
    assert(_pair_same_type(pt_pairdest, cpt_pairsrc));

    /* copy element */
    t_result = _GET_PAIR_FIRST_TYPE_SIZE(pt_pairdest);
    _GET_PAIR_FIRST_TYPE_COPY_FUNCTION(pt_pairdest)(
        pt_pairdest->first, cpt_pairsrc->first, &t_result);
    assert(t_result);

    t_result = _GET_PAIR_SECOND_TYPE_SIZE(pt_pairdest);
    _GET_PAIR_SECOND_TYPE_COPY_FUNCTION(pt_pairdest)(
        pt_pairdest->second, cpt_pairsrc->second, &t_result);
    assert(t_result);
}

bool_t pair_equal(const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond)
{
    bool_t t_less = false;
    bool_t t_great = false;

    assert(cpt_pairfirst != NULL && cpt_pairsecond != NULL);
    assert(cpt_pairfirst->first != NULL && cpt_pairfirst->second != NULL);
    assert(cpt_pairsecond->first != NULL && cpt_pairsecond->second != NULL);

    if(!_pair_same_type(cpt_pairfirst, cpt_pairsecond))
    {
        return false;
    }

    /* compare first */
    t_less = t_great = _GET_PAIR_FIRST_TYPE_SIZE(cpt_pairfirst);
    _GET_PAIR_FIRST_TYPE_LESS_FUNCTION(cpt_pairfirst)(
        cpt_pairfirst->first, cpt_pairsecond->first, &t_less);
    _GET_PAIR_FIRST_TYPE_LESS_FUNCTION(cpt_pairfirst)(
        cpt_pairsecond->first, cpt_pairfirst->first, &t_great);
    if(t_less || t_great)
    {
        return false;
    }

    /* compare second */
    t_less = t_great = _GET_PAIR_SECOND_TYPE_SIZE(cpt_pairfirst);
    _GET_PAIR_SECOND_TYPE_LESS_FUNCTION(cpt_pairfirst)(
        cpt_pairfirst->second, cpt_pairsecond->second, &t_less);
    _GET_PAIR_SECOND_TYPE_LESS_FUNCTION(cpt_pairfirst)(
        cpt_pairsecond->second, cpt_pairfirst->second, &t_great);
    if(t_less || t_great)
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
        cpt_pairfirst->first, cpt_pairsecond->first, &t_result);
    if(t_result)
    {
        return true;
    }

    t_result = _GET_PAIR_FIRST_TYPE_SIZE(cpt_pairfirst);
    _GET_PAIR_FIRST_TYPE_LESS_FUNCTION(cpt_pairfirst)(
        cpt_pairsecond->first, cpt_pairfirst->first, &t_result);
    if(t_result)
    {
        return false;
    }

    /* compare second */
    t_result = _GET_PAIR_SECOND_TYPE_SIZE(cpt_pairfirst);
    _GET_PAIR_SECOND_TYPE_LESS_FUNCTION(cpt_pairfirst)(
        cpt_pairfirst->second, cpt_pairsecond->second, &t_result);
    if(t_result)
    {
        return true;
    }

    t_result = _GET_PAIR_SECOND_TYPE_SIZE(cpt_pairfirst);
    _GET_PAIR_SECOND_TYPE_LESS_FUNCTION(cpt_pairfirst)(
        cpt_pairsecond->second, cpt_pairfirst->second, &t_result);
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

bool_t pair_great(const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond)
{
    return pair_less(cpt_pairsecond, cpt_pairfirst);
}

bool_t pair_great_equal(const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond)
{
    return (pair_great(cpt_pairfirst, cpt_pairsecond) ||
            pair_equal(cpt_pairfirst, cpt_pairsecond)) ? true : false;
}

/** local function implementation section **/
#ifndef NDEBUG
static bool_t _pair_same_type(const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond)
{
    assert(cpt_pairfirst != NULL && cpt_pairsecond != NULL);

    return _type_is_same(cpt_pairfirst->_t_typeinfofirst._sz_typename,
                         cpt_pairsecond->_t_typeinfofirst._sz_typename) &&
           _type_is_same(cpt_pairfirst->_t_typeinfosecond._sz_typename,
                         cpt_pairsecond->_t_typeinfosecond._sz_typename) &&
           cpt_pairfirst->_t_typeinfofirst._pt_type ==
           cpt_pairsecond->_t_typeinfofirst._pt_type &&
           cpt_pairfirst->_t_typeinfofirst._t_style ==
           cpt_pairsecond->_t_typeinfofirst._t_style &&
           cpt_pairfirst->_t_typeinfosecond._pt_type ==
           cpt_pairsecond->_t_typeinfosecond._pt_type &&
           cpt_pairfirst->_t_typeinfosecond._t_style ==
           cpt_pairsecond->_t_typeinfosecond._t_style;
}
#endif /* NDEBUG */

/** eof **/

