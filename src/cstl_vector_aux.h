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

#ifndef _CSTL_VECTOR_AUX_H
#define _CSTL_VECTOR_AUX_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/* macros for type informations */
#define _GET_VECTOR_TYPE_SIZE(pt_vector)\
    ((pt_vector)->_t_typeinfo._pt_type->_t_typesize)
#define _GET_VECTOR_TYPE_NAME(pt_vector)\
    ((pt_vector)->_t_typeinfo._sz_typename)
#define _GET_VECTOR_TYPE_BASENAME(pt_vector)\
    ((pt_vector)->_t_typeinfo._pt_type->_sz_typename)
#define _GET_VECTOR_TYPE_INIT_FUNCTION(pt_vector)\
    ((pt_vector)->_t_typeinfo._pt_type->_t_typeinit)
#define _GET_VECTOR_TYPE_COPY_FUNCTION(pt_vector)\
    ((pt_vector)->_t_typeinfo._pt_type->_t_typecopy)
#define _GET_VECTOR_TYPE_LESS_FUNCTION(pt_vector)\
    ((pt_vector)->_t_typeinfo._pt_type->_t_typeless)
#define _GET_VECTOR_TYPE_DESTROY_FUNCTION(pt_vector)\
    ((pt_vector)->_t_typeinfo._pt_type->_t_typedestroy)
#define _GET_VECTOR_TYPE_STYLE(pt_vector)\
    ((pt_vector)->_t_typeinfo._t_style)

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
#ifndef NDEBUG
/**
 * Test iterator referenced data is within the vector.
 * @param cpvec_vector point to vector container.
 * @param it_iter vector iterator.
 * @return if iterator referenced is within the vector, then return true, otherwise return false.
 * @remarks if cpvec_vector == NULL, then the behavior is undefined, the it_iter must be valie vector iterator and
 *          must belong to vector, otherwist the behavior is undefined. 
 */
extern bool_t _vector_iterator_belong_to_vector(const vector_t* cpvec_vector, vector_iterator_t it_iter);
extern bool_t _vector_same_vector_iterator_type(
    const vector_t* cpt_vector, vector_iterator_t t_iter);
#endif /* NDEBUG */

/**
 * Test the type that saved in the vector container is same.
 * @param cpvec_first first vector.
 * @param cpvec_second second vector.
 * @return if the type is same, return true, else return false.
 * @remarks if cpvec_first == NULL or cpvec_second == NULL, the behavior is undefined.
 */
extern bool_t _vector_same_type(const vector_t* cpvec_first, const vector_t* cpvec_second);

extern void _vector_get_varg_value_auxiliary(
    vector_t* pt_vector, va_list val_elemlist, void* pv_varg);
extern void _vector_destroy_varg_value_auxiliary(vector_t* pt_vector, void* pv_varg);
extern void _vector_init_elem_range_auxiliary(
    vector_t* pt_vector, char* pc_start, char* pc_finish);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_VECTOR_AUX_H */
/** eof **/

