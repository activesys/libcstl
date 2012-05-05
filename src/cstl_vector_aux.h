/*
 *  The implement of vector auxiliary function.
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

#ifndef _CSTL_VECTOR_AUX_H_
#define _CSTL_VECTOR_AUX_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/* macros for type informations */
#define _GET_VECTOR_TYPE_SIZE(pvec_vector)             ((pvec_vector)->_t_typeinfo._pt_type->_t_typesize)
#define _GET_VECTOR_TYPE_NAME(pvec_vector)             ((pvec_vector)->_t_typeinfo._s_typename)
#define _GET_VECTOR_TYPE_BASENAME(pvec_vector)         ((pvec_vector)->_t_typeinfo._pt_type->_s_typename)
#define _GET_VECTOR_TYPE_INIT_FUNCTION(pvec_vector)    ((pvec_vector)->_t_typeinfo._pt_type->_t_typeinit)
#define _GET_VECTOR_TYPE_COPY_FUNCTION(pvec_vector)    ((pvec_vector)->_t_typeinfo._pt_type->_t_typecopy)
#define _GET_VECTOR_TYPE_LESS_FUNCTION(pvec_vector)    ((pvec_vector)->_t_typeinfo._pt_type->_t_typeless)
#define _GET_VECTOR_TYPE_DESTROY_FUNCTION(pvec_vector) ((pvec_vector)->_t_typeinfo._pt_type->_t_typedestroy)
#define _GET_VECTOR_TYPE_STYLE(pvec_vector)            ((pvec_vector)->_t_typeinfo._t_style)

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

/**
 * Test the type that saved in the vector container and referenced by it_iter are same.
 * @param cpvec_vector vector container.
 * @param it_iter      vector iterator.
 * @return if the type is same, return true, else return false.
 * @remarks if cpvec_first == NULL or it_iter is not vector iterator, then the behavior is undefined.
 */
extern bool_t _vector_same_vector_iterator_type(const vector_t* cpvec_vector, vector_iterator_t it_iter);

/**
 * Test the type that saved in the vector container and referenced by it_iter are same.
 * @param cpvec_vector vector container.
 * @param it_iter      vector iterator.
 * @return if the type is same, return true, else return false.
 * @remarks if cpvec_first == NULL, then the behavior is undefined.
 */
extern bool_t _vector_same_iterator_type(const vector_t* cpvec_vector, iterator_t it_iter);

/**
 * Test vector is created by create_vector.
 * @param cpvec_vector  vector container.
 * @return if vector is created by create_vector, then return true, else return false.
 * @remarks if cpvec_vector == NULL, then the behavior is undefined.
 */
extern bool_t _vector_is_created(const vector_t* cpvec_vector);

/**
 * Test vector is initialized by vector initialization functions.
 * @param cpvec_vector  vector container.
 * @return if vector is initialized by vector initialization functions, then return true, else return false.
 * @remarks if cpvec_vector == NULL, then the behavior is undefined.
 */
extern bool_t _vector_is_inited(const vector_t* cpvec_vector);
#endif /* NDEBUG */

/**
 * Test the type that saved in the vector container is same.
 * @param cpvec_first first vector.
 * @param cpvec_second second vector.
 * @return if the type is same, return true, else return false.
 * @remarks if cpvec_first == NULL or cpvec_second == NULL, the behavior is undefined. the two vector must be
 *          initialized or created by create_vector(), otherwise the behavior is undefined.
 */
extern bool_t _vector_same_type(const vector_t* cpvec_first, const vector_t* cpvec_second);

/**
 * Obtain data from variable argument list, the data type and vector element data type are same.
 * @param pvec_vector  vector container.
 * @param val_elemlist variable argument list.
 * @param pv_varg      data buffer.
 * @return void.
 * @remarks if pvec_vector == NULL or pv_varg == NULL, then the behavior is undefined. pvec_vector must be initialized
 *          or created by create_vector(), otherwise the behavior is undefined.
 */
extern void _vector_get_varg_value_auxiliary(vector_t* pvec_vector, va_list val_elemlist, void* pv_varg);

/**
 * Destroy data, the data type and vector element data type are same.
 * @param pvec_vector  vector container.
 * @param pv_varg      data buffer.
 * @return void.
 * @remarks if pvec_vector == NULL or pv_varg == NULL, then the behavior is undefined. pvec_vector must be initialized
 *          or created by create_vector(), otherwise the behavior is undefined.
 */
extern void _vector_destroy_varg_value_auxiliary(vector_t* pvec_vector, void* pv_varg);

/**
 * Initialize data within range [pby_start, pby_finish) according to vector element data type.
 * @param pvec_vector  vector container.
 * @param pby_start    range start.
 * @param pby_finish   range end.
 * @return void.
 * @remarks if pvec_vector == NULL, pby_start == NULL or pby_finish == NULL, then the behavior is undefined.
 *          if pby_finish < pby_start, then the behavior is undefined. pvec_vector must be initialized or created
 *          by create_vector(), otherwise the behavior is undefined.
 */
extern void _vector_init_elem_range_auxiliary(vector_t* pvec_vector, _byte_t* pby_start, _byte_t* pby_finish);

/**
 * Calculate new capacity according to old size and insert size.
 * @param t_oldsize     vector old size.
 * @param t_insertsize  vector insert size.
 * @return new capacity.
 */
extern size_t _vector_calculate_new_capacity(size_t t_oldsize, size_t t_insertsize);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_VECTOR_AUX_H_ */
/** eof **/

