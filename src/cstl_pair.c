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

#include "cstl_types.h"

#include "cstl_pair.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/
#ifndef NDEBUG
/*
 * Test the two pair is have the same type.
 */
static bool_t _same_pair_type(const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond);
#endif /* NDEBUG */

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/* private function */
pair_t _create_pair(
    size_t t_firsttypesize, const char* s_firsttypename, 
    size_t t_secondtypesize, const char* s_secondtypename)
{
    pair_t t_newpair;

    assert(t_firsttypesize > 0 && s_firsttypename != NULL);
    assert(t_secondtypesize > 0 && s_secondtypename != NULL);

    /* set type size and neame */
    t_newpair._t_firsttypesize = t_firsttypesize;
    memset(t_newpair._sz_firsttypename, '\0', _ELEM_TYPE_NAME_SIZE+1);
    strncpy(t_newpair._sz_firsttypename, s_firsttypename, _ELEM_TYPE_NAME_SIZE);
    _unify_types(t_newpair._t_firsttypesize, t_newpair._sz_firsttypename);

    t_newpair._t_secondtypesize = t_secondtypesize;
    memset(t_newpair._sz_secondtypename, '\0', _ELEM_TYPE_NAME_SIZE+1);
    strncpy(t_newpair._sz_secondtypename, s_secondtypename, _ELEM_TYPE_NAME_SIZE);
    _unify_types(t_newpair._t_secondtypesize, t_newpair._sz_secondtypename);

    t_newpair.first = t_newpair.second = NULL;

    t_newpair._pfun_first_cmp = NULL;
    t_newpair._pfun_second_cmp = NULL;

    return t_newpair;
}

void _pair_make_first(pair_t* pt_pair, ...)
{
    va_list val_elemlist;

    assert(pt_pair != NULL);
    assert(pt_pair->first != NULL && pt_pair->second != NULL);

    va_start(val_elemlist, pt_pair);
    _get_varg_value(
        pt_pair->first, val_elemlist,
        pt_pair->_t_firsttypesize, pt_pair->_sz_firsttypename);
}

void _pair_make_second(pair_t* pt_pair, ...)
{
    va_list val_elemlist;

    assert(pt_pair != NULL);
    assert(pt_pair->first != NULL && pt_pair->second != NULL);

    va_start(val_elemlist, pt_pair);
    _get_varg_value(
        pt_pair->second, val_elemlist,
        pt_pair->_t_secondtypesize, pt_pair->_sz_secondtypename);
}

/* pair function */
void pair_init(pair_t* pt_pair)
{
    assert(pt_pair != NULL);
    assert(pt_pair->first == NULL && pt_pair->second == NULL);
    assert(pt_pair->_pfun_first_cmp == NULL && pt_pair->_pfun_second_cmp == NULL);

    pt_pair->first = malloc(pt_pair->_t_firsttypesize);
    if(pt_pair->first == NULL)
    {
        fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        memset(pt_pair->first, 0x00, pt_pair->_t_firsttypesize);
    }

    pt_pair->second = malloc(pt_pair->_t_secondtypesize);
    if(pt_pair->second == NULL)
    {
        fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        memset(pt_pair->second, 0x00, pt_pair->_t_secondtypesize);
    }

    pt_pair->_pfun_first_cmp = _get_cmp_function(pt_pair->_sz_firsttypename);
    pt_pair->_pfun_second_cmp = _get_cmp_function(pt_pair->_sz_secondtypename);
}

void pair_destroy(pair_t* pt_pair)
{
    assert(pt_pair != NULL);
    assert(pt_pair->first != NULL && pt_pair->second != NULL);

    free(pt_pair->first);
    pt_pair->first = NULL;
    free(pt_pair->second);
    pt_pair->second = NULL;

    pt_pair->_pfun_first_cmp = NULL;
    pt_pair->_pfun_second_cmp = NULL;
}

void pair_init_copy(pair_t* pt_pairdest, const pair_t* cpt_pairsrc)
{
    assert(pt_pairdest != NULL && cpt_pairsrc != NULL);
    assert(cpt_pairsrc->first != NULL && cpt_pairsrc->second != NULL);
    assert(
        pt_pairdest->_t_firsttypesize == cpt_pairsrc->_t_firsttypesize &&
        pt_pairdest->_t_secondtypesize == cpt_pairsrc->_t_secondtypesize);
    assert(
        strncmp(
            pt_pairdest->_sz_firsttypename, cpt_pairsrc->_sz_firsttypename,
            _ELEM_TYPE_NAME_SIZE) == 0 &&
        strncmp(
            pt_pairdest->_sz_secondtypename, cpt_pairsrc->_sz_secondtypename,
            _ELEM_TYPE_NAME_SIZE) == 0);

    /* initialize dest pair */
    pair_init(pt_pairdest);

    /* copy element */
    memcpy(pt_pairdest->first, cpt_pairsrc->first, pt_pairdest->_t_firsttypesize);
    memcpy(pt_pairdest->second, cpt_pairsrc->second, pt_pairdest->_t_secondtypesize);

    /* copy compare and destroy function */
    pt_pairdest->_pfun_first_cmp = cpt_pairsrc->_pfun_first_cmp;
    pt_pairdest->_pfun_second_cmp = cpt_pairsrc->_pfun_second_cmp;
}

void pair_assign(pair_t* pt_pairdest, const pair_t* cpt_pairsrc)
{
    assert(_same_pair_type(pt_pairdest, cpt_pairsrc));

    /* copy element */
    memcpy(pt_pairdest->first, cpt_pairsrc->first, pt_pairdest->_t_firsttypesize);
    memcpy(pt_pairdest->second, cpt_pairsrc->second, pt_pairdest->_t_secondtypesize);

    /* copy compare and destroy function */
    pt_pairdest->_pfun_first_cmp = cpt_pairsrc->_pfun_first_cmp;
    pt_pairdest->_pfun_second_cmp = cpt_pairsrc->_pfun_second_cmp;
}

bool_t pair_equal(const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond)
{
    assert(cpt_pairfirst != NULL && cpt_pairsecond != NULL);
    assert(cpt_pairfirst->first != NULL && cpt_pairfirst->second != NULL);
    assert(cpt_pairsecond->first != NULL && cpt_pairsecond->second != NULL);

    if(cpt_pairfirst->_t_firsttypesize != cpt_pairsecond->_t_firsttypesize ||
       cpt_pairfirst->_t_secondtypesize != cpt_pairsecond->_t_secondtypesize)
    {
        return false;
    }

    if(strncmp(
        cpt_pairfirst->_sz_firsttypename, cpt_pairsecond->_sz_firsttypename, 
        _ELEM_TYPE_NAME_SIZE) != 0 ||
       strncmp(
        cpt_pairfirst->_sz_secondtypename, cpt_pairsecond->_sz_secondtypename, 
        _ELEM_TYPE_NAME_SIZE) != 0)
    {
        return false;
    }

    if(cpt_pairfirst->_pfun_first_cmp != cpt_pairsecond->_pfun_first_cmp ||
       cpt_pairfirst->_pfun_second_cmp != cpt_pairsecond->_pfun_second_cmp)
    {
        return false;
    }

    if(cpt_pairfirst->_pfun_first_cmp != NULL)
    {
        if((*cpt_pairfirst->_pfun_first_cmp)(
            cpt_pairfirst->first, cpt_pairsecond->first) != 0)
        {
            return false;
        }
    }
    else
    {
        if(memcmp(
            cpt_pairfirst->first, cpt_pairsecond->first, 
            cpt_pairfirst->_t_firsttypesize) != 0)
        {
            return false;
        }
    }

    if(cpt_pairfirst->_pfun_second_cmp != NULL)
    {
        if((*cpt_pairfirst->_pfun_second_cmp)(
            cpt_pairfirst->second, cpt_pairsecond->second) != 0)
        {
            return false;
        }
    }
    else
    {
        if(memcmp(
            cpt_pairfirst->second, cpt_pairsecond->second, 
            cpt_pairfirst->_t_secondtypesize) != 0)
        {
            return false;
        }
    }

    return true;
}

bool_t pair_not_equal(const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond)
{
    return !pair_equal(cpt_pairfirst, cpt_pairsecond);
}

bool_t pair_less(const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond)
{
    int n_cmpresult = 0;

    assert(_same_pair_type(cpt_pairfirst, cpt_pairsecond));

    /* test first element */
    if(cpt_pairfirst->_pfun_first_cmp != NULL)
    {
        n_cmpresult = (*cpt_pairfirst->_pfun_first_cmp)(
            cpt_pairfirst->first, cpt_pairsecond->first);
    }
    else
    {
        n_cmpresult = memcmp(
            cpt_pairfirst->first, cpt_pairsecond->first, 
            cpt_pairfirst->_t_firsttypesize);
    }

    if(n_cmpresult < 0)
    {
        return true;
    }
    else if(n_cmpresult > 0)
    {
        return false;
    }

    /* first element equal then test second elemen */
    if(cpt_pairfirst->_pfun_second_cmp != NULL)
    {
        n_cmpresult = (*cpt_pairfirst->_pfun_second_cmp)(
            cpt_pairfirst->second, cpt_pairsecond->second);
    }
    else
    {
        n_cmpresult = memcmp(
            cpt_pairfirst->second, cpt_pairsecond->second,
            cpt_pairfirst->_t_secondtypesize);
    }

    if(n_cmpresult < 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool_t pair_less_equal(const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond)
{
    return pair_less(cpt_pairfirst, cpt_pairsecond) ||
           pair_equal(cpt_pairfirst, cpt_pairsecond);
}

bool_t pair_great(const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond)
{
    return pair_less(cpt_pairsecond, cpt_pairfirst);
}

bool_t pair_great_equal(const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond)
{
    return pair_great(cpt_pairfirst, cpt_pairsecond) ||
           pair_equal(cpt_pairfirst, cpt_pairsecond);
}

/** local function implementation section **/
#ifndef NDEBUG
static bool_t _same_pair_type(const pair_t* cpt_pairfirst, const pair_t* cpt_pairsecond)
{
    assert(cpt_pairfirst != NULL && cpt_pairsecond != NULL);

    assert(
        cpt_pairfirst->_t_firsttypesize == cpt_pairsecond->_t_firsttypesize &&
        cpt_pairfirst->_t_secondtypesize == cpt_pairsecond->_t_secondtypesize);
    assert(
        strncmp(
            cpt_pairfirst->_sz_firsttypename, cpt_pairsecond->_sz_firsttypename,
            _ELEM_TYPE_NAME_SIZE) == 0 &&
        strncmp(
            cpt_pairfirst->_sz_secondtypename, cpt_pairsecond->_sz_secondtypename,
            _ELEM_TYPE_NAME_SIZE) == 0);

    assert(
        cpt_pairfirst->_pfun_first_cmp == cpt_pairsecond->_pfun_first_cmp &&
        cpt_pairfirst->_pfun_second_cmp == cpt_pairsecond->_pfun_second_cmp);

    return true;
}
#endif /* NDEBUG */

/** eof **/

