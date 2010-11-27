/*
 *  The implement of vector auxiliary function.
 *  Copyright (C)  2008,2009,2010  Wangbo
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

#include <cstl/cstl_vector_iterator.h>
#include <cstl/cstl_vector_private.h>

#include "cstl_vector_aux.h"


/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
#ifndef NDEBUG
/**
 * Test iterator referenced data is within the vector.
 */
bool_t _vector_iterator_belong_to_vector(const vector_t* cpvec_vector, vector_iterator_t it_iter)
{
    assert(cpvec_vector != NULL);
    assert(it_iter._t_iteratortype == _RANDOM_ACCESS_ITERATOR);
    assert(it_iter._t_containertype == _VECTOR_CONTAINER);
    assert(_GET_VECTOR_CONTAINER(it_iter) == cpvec_vector);

    if(_GET_VECTOR_COREPOS(it_iter) >= cpvec_vector->_pc_start &&
       _GET_VECTOR_COREPOS(it_iter) <= cpvec_vector->_pc_finish)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool_t _vector_same_vector_iterator_type(
    const vector_t* cpt_vector, vector_iterator_t t_iter)
{
    assert(cpt_vector != NULL && _GET_VECTOR_CONTAINER(t_iter) != NULL);
    assert(_GET_VECTOR_CONTAINER_TYPE(t_iter) == _VECTOR_CONTAINER &&
           _GET_VECTOR_ITERATOR_TYPE(t_iter) == _RANDOM_ACCESS_ITERATOR);
    return _vector_same_type(cpt_vector, _GET_VECTOR_CONTAINER(t_iter));
}
#endif /* NDEBUG */

bool_t _vector_same_type(
    const vector_t* cpt_vectorfirst, const vector_t* cpt_vectorsecond)
{
    assert(cpt_vectorfirst != NULL && cpt_vectorsecond != NULL);
    return _type_is_same(_GET_VECTOR_TYPE_NAME(cpt_vectorfirst),
                         _GET_VECTOR_TYPE_NAME(cpt_vectorsecond)) &&
           (cpt_vectorfirst->_t_typeinfo._pt_type ==
            cpt_vectorsecond->_t_typeinfo._pt_type) &&
           (cpt_vectorfirst->_t_typeinfo._t_style ==
            cpt_vectorsecond->_t_typeinfo._t_style);
}

void _vector_init_elem_range_auxiliary(
    vector_t* pt_vector, char* pc_start, char* pc_finish)
{
    char* pc_pos = NULL;

    assert(pt_vector != NULL && pc_start != NULL && pc_finish != NULL && pc_start <= pc_finish);

    /* initialize new elements */
    if(_GET_VECTOR_TYPE_STYLE(pt_vector) == _TYPE_CSTL_BUILTIN)
    {
        /* get element type name */
        char s_elemtypename[_TYPE_NAME_SIZE + 1];
        _type_get_elem_typename(_GET_VECTOR_TYPE_NAME(pt_vector), s_elemtypename);

        for(pc_pos = pc_start; pc_pos < pc_finish; pc_pos += _GET_VECTOR_TYPE_SIZE(pt_vector))
        {
            _GET_VECTOR_TYPE_INIT_FUNCTION(pt_vector)(pc_pos, s_elemtypename);
        }
    }
    else
    {
        for(pc_pos = pc_start; pc_pos < pc_finish; pc_pos += _GET_VECTOR_TYPE_SIZE(pt_vector))
        {
            bool_t t_result = _GET_VECTOR_TYPE_SIZE(pt_vector);
            _GET_VECTOR_TYPE_INIT_FUNCTION(pt_vector)(pc_pos, &t_result);
            assert(t_result);
        }
    }
}

void _vector_get_varg_value_auxiliary(
    vector_t* pt_vector, va_list val_elemlist, void* pv_varg)
{
    _vector_init_elem_auxiliary(pt_vector, pv_varg);
    _type_get_varg_value(&pt_vector->_t_typeinfo, val_elemlist, pv_varg);
}

void _vector_destroy_varg_value_auxiliary(vector_t* pt_vector, void* pv_varg)
{
    /* destroy varg value and free memory */
    bool_t t_result = _GET_VECTOR_TYPE_SIZE(pt_vector);
    _GET_VECTOR_TYPE_DESTROY_FUNCTION(pt_vector)(pv_varg, &t_result);
    assert(t_result);
}

/** local function implementation section **/

/** eof **/

