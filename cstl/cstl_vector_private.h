/*
 *  The definition of vector_t struct.
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

#ifndef _CSTL_VECTOR_PRIVATE_H_
#define _CSTL_VECTOR_PRIVATE_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
/*
 * vector_t
 * _pby_start          _pby_finish      _pby_endofstorage
 * |                     |               |
 * V                     V               V
 * +-------------------------------------+
 * |    ... data ...     |               |
 * +-------------------------------------+
 * |<--------size()----->|
 * |<---------------capacity()---------->|
 */
typedef struct _tagvector
{
    /* element type information */
    _typeinfo_t _t_typeinfo;

    /* memory allocate */
    _alloc_t    _t_allocator;

    /* vector core struct pointer */
    _byte_t*    _pby_start;          /* the start of used space */
    _byte_t*    _pby_finish;         /* the end of used space */
    _byte_t*    _pby_endofstorage;   /* the end of capacity space */
}vector_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Create vector container.
 * @param s_typename element type name.
 * @return if create vector successfully, then return vector pointer, else return NULL.
 * @remarks if s_typename == NULL, then the behavior is undefined. s_typename should be C builtin type name,
 *          libcstl builtin typename or registed user defined type name, otherwise the function will return NULL.
 */
extern vector_t* _create_vector(const char* s_typename);

/**
 * Create vector container auxiliary function.
 * @param pvec_vector uncreated container.
 * @param s_typename  element type name.
 * @return if create vector successfully return true, otherwise return false.
 * @remarks if s_typename == NULL, then the behavior is undefined. s_typename should be C builtin type name,
 *          libcstl builtin typename or registed user defined type name, otherwise the function will return false.
 */
extern bool_t _create_vector_auxiliary(vector_t* pvec_vector, const char* s_typename);

/**
 * Initialize vector with specified element.
 * @param pvec_vector  uninitialized vector container.
 * @param t_count      element number.
 * @param ...          specificed element.
 * @return void
 * @remarks if pvec_vector == NULL, then the behavior is undefined. the type of specificed element and vector element
 *          type must be same, otherwise the behavior is undefined. the first specificed element is in use, others are
 *          not in use. vector container must be created by create_vector, otherwise the behavior is undefined.
 */
extern void _vector_init_elem(vector_t* pvec_vector, size_t t_count, ...);

/**
 * Initialize vector with variable argument list of specified element.
 * @param pvec_vector  uninitialized vector container.
 * @param t_count      element number.
 * @param val_elemlist variable argument list of specificed element.
 * @return void
 * @remarks if pvec_vector == NULL, then the behavior is undefined. the type of specificed element and vector element
 *          type must be same, otherwise the behavior is undefined. the first specificed element is in use, others are
 *          not in use. vector container must be created by create_vector, otherwise the behavior is undefined.
 */
extern void _vector_init_elem_varg(vector_t* pvec_vector, size_t t_count, va_list val_elemlist);

/**
 * Destroy vector container auxiliary function.
 * @param pvec_vector  vector container.
 * @return void.
 * @remarks if pvec_vector == NULL or vector is not created by create_vector() function, then the behavior is undefined.
 *          vector container must be create_vector, otherwise the behavior is undefined.
 */
extern void _vector_destroy_auxiliary(vector_t* pvec_vector);

/**
 * Assign vector with specificed element.
 * @param pvec_vector  vector container.
 * @param t_count      element number.
 * @param ...          specificed element.
 * @return void.
 * @remarks if pvec_vector == NULL or vector is uninitialized, then the behavior is undefined. the type of specificed
 *          element and vector element type must be same, otherwise the behavior is undefined. the first specificed is
 *          in use, others are not in use.
 */
extern void _vector_assign_elem(vector_t* pvec_vector, size_t t_count, ...);

/**
 * Assign vector with variable argument of specificed element.
 * @param pvec_vector  vector container.
 * @param t_count      element number.
 * @param val_elemlist variable argumnet list of specificed element.
 * @return void.
 * @remarks if pvec_vector == NULL or vector is uninitialized, then the behavior is undefined. the type of specificed
 *          element and vector element type must be same, otherwise the behavior is undefined. the first specificed is
 *          in use, others are not in use.
 */
extern void _vector_assign_elem_varg(vector_t* pvec_vector, size_t t_count, va_list val_elemlist);

/**
 * Add specificed element at the end of vector container. 
 * @param pvec_vector  vector container.
 * @param val_elemlist specificed element.
 * @return void.
 * @remarks if pvec_vector == NULL or vector is uninitialized, then the behavior is undefined. the type of specificed
 *          element and vector element type must be same, otherwise the behavior is undefined. the first specificed is
 *          in use, others are not in use.
 */
extern void _vector_push_back(vector_t* pvec_vector, ...);

/**
 * Add specificed element from variable argument list at the end of vector container. 
 * @param pvec_vector  vector container.
 * @param val_elemlist variable argumnet list of specificed element.
 * @return void.
 * @remarks if pvec_vector == NULL or vector is uninitialized, then the behavior is undefined. the type of specificed
 *          element and vector element type must be same, otherwise the behavior is undefined. the first specificed is
 *          in use, others are not in use.
 */
extern void _vector_push_back_varg(vector_t* pvec_vector, va_list val_elemlist);

/**
 * Reset the size of vector elements.
 * @param pvec_vector   vector container.
 * @param t_resize      new size of vector elements.
 * @param ...           specificed element.
 * @return void.
 * @remarks if pvec_vector == NULL or vector is uninitialized, then the behavior is undefined. the type of specificed
 *          element and vector element type must be same, otherwise the behavior is undefined. the first specificed is
 *          in use, others are not in use. if t_resize less than current vector size, then erase elmement from the end.
 *          if t_resize greater than current vector size, then append elements to the end, and the element is specificed
 *          element.
 */
extern void _vector_resize_elem(vector_t* pvec_vector, size_t t_resize, ...);

/**
 * Reset the size of vector elements, and filled element is from variable argument list.
 * @param pvec_vector   vector container.
 * @param t_resize      new size of vector elements.
 * @param val_elemlist  specificed element.
 * @return void.
 * @remarks if pvec_vector == NULL or vector is uninitialized, then the behavior is undefined. the type of specificed
 *          element and vector element type must be same, otherwise the behavior is undefined. the first specificed is
 *          in use, others are not in use. if t_resize less than current vector size, then erase elmement from the end.
 *          if t_resize greater than current vector size, then append elements to the end, and the element is from
 *          variable argument list.
 */
extern void _vector_resize_elem_varg(vector_t* pvec_vector, size_t t_resize, va_list val_elemlist);

/**
 * Insert multiple copys of element befor specificed position.
 * @param pvec_vector   vector container.
 * @param it_pos        insert position.
 * @param t_count       element number.
 * @param ...           specificed element.
 * @return position refereced the first inserted elements.
 * @remarks if pvec_vector == NULL or vector is uninitialized, then the behavior is undefined. the it_pos must be invalid
 *          iterator of vector container, otherwise the behavior is undefined. the type of specificed element and vector
 *          element type must be same, otherwise the behavior is undefined. the first specificed is in use, others are not
 *          in use.
 */
extern vector_iterator_t _vector_insert_n(
    vector_t* pvec_vector, vector_iterator_t it_pos, size_t t_count, ...);

/**
 * Insert multiple copys of element befor specificed position, the element is from variable argument list.
 * @param pvec_vector   vector container.
 * @param it_pos        insert position.
 * @param t_count       element number.
 * @param val_elemlist  specificed element.
 * @return position refereced the first inserted elements.
 * @remarks if pvec_vector == NULL or vector is uninitialized, then the behavior is undefined. the it_pos must be invalid
 *          iterator of vector container, otherwise the behavior is undefined. the type of specificed element and vector
 *          element type must be same, otherwise the behavior is undefined. the first specificed is in use, others are not
 *          in use. the inserted element is from variable argument list.
 */
extern vector_iterator_t _vector_insert_n_varg(
    vector_t* pvec_vector, vector_iterator_t it_pos, size_t t_count, va_list val_elemlist);

/**
 * Initialize element with vector element type auxiliary function.
 * @param pvec_vector   vector container.
 * @param pv_elem       initialized element.
 * @return void.
 * @remarks if pvec_vector == NULL or pv_elem == NULL, then the behavior is undefined. pvec_vector must be initialized
 *          vector container or created by create_vector, otherwise the behavior is undefined.
 */
extern void _vector_init_elem_auxiliary(vector_t* pvec_vector, void* pv_elem);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_VECTOR_PRIVATE_H_ */
/** eof **/

