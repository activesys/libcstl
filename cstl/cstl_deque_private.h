/*
 *  The definition of deque_t struct.
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

#ifndef _CSTL_DEQUE_PRIVATE_H_
#define _CSTL_DEQUE_PRIVATE_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
/* deque struct */
typedef _byte_t**  _mappointer_t;
typedef struct _tagdeque
{
    /* element type information */
    _typeinfo_t      _t_typeinfo;

    /* memory allocate */
    _alloc_t         _t_allocator;

    /* the element manager map and size */
    _mappointer_t    _ppby_map;
    size_t           _t_mapsize;
    /* the first element */
    deque_iterator_t _t_start;
    /* the element after the last element */
    deque_iterator_t _t_finish;
}deque_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Create deque container.
 * @param s_typename element type name.
 * @return if create deque successfully, then return deque pointer, else return NULL.
 * @remarks if s_typename == NULL, then the behavior is undefined. s_typename should be C builtin type name,
 *          libcstl builtin typename or registed user defined type name, otherwise the function will return NULL.
 */
extern deque_t* _create_deque(const char* s_typename);

/**
 * Create deque container auxiliary function.
 * @param pdeq_deque  uncreated container.
 * @param s_typename  element type name.
 * @return if create deque successfully return true, otherwise return false.
 * @remarks if s_typename == NULL, then the behavior is undefined. s_typename should be C builtin type name,
 *          libcstl builtin typename or registed user defined type name, otherwise the function will return false.
 */
extern bool_t _create_deque_auxiliary(deque_t* pdeq_deque, const char* s_typename);

/**
 * Initialize deque with specified element.
 * @param pdeq_deque   uninitialized deque container.
 * @param t_count      element number.
 * @param ...          specificed element.
 * @return void
 * @remarks if pdeq_deque == NULL, then the behavior is undefined. the type of specificed element and deque element
 *          type must be same, otherwise the behavior is undefined. the first specificed element is in use, others are
 *          not in use. deque container must be created by create_deque, otherwise the behavior is undefined.
 */
extern void _deque_init_elem(deque_t* pdeq_deque, size_t t_count, ...);

/**
 * Initialize deque with variable argument list of specified element.
 * @param pdeq_deque   uninitialized deque container.
 * @param t_count      element number.
 * @param val_elemlist variable argument list of specificed element.
 * @return void
 * @remarks if pdeq_deque == NULL, then the behavior is undefined. the type of specificed element and deque element
 *          type must be same, otherwise the behavior is undefined. the first specificed element is in use, others are
 *          not in use. deque container must be created by create_deque, otherwise the behavior is undefined.
 */
extern void _deque_init_elem_varg(deque_t* pdeq_deque, size_t t_count, va_list val_elemlist);

/**
 * Destroy deque container auxiliary function.
 * @param pdeq_deque  deque container.
 * @return void.
 * @remarks if pdeq_deque == NULL or deque is not created by create_deque() function, then the behavior is undefined.
 *          deque container must be create_deque, otherwise the behavior is undefined.
 */
extern void _deque_destroy_auxiliary(deque_t* pdeq_deque);

/**
 * Assign deque with specificed element.
 * @param pdeq_deque   deque container.
 * @param t_count      element number.
 * @param ...          specificed element.
 * @return void.
 * @remarks if pdeq_deque == NULL or deque is uninitialized, then the behavior is undefined. the type of specificed
 *          element and deque element type must be same, otherwise the behavior is undefined. the first specificed is
 *          in use, others are not in use.
 */
extern void _deque_assign_elem(deque_t* pdeq_deque, size_t t_count, ...);

/**
 * Assign deque with variable argument of specificed element.
 * @param pdeq_deque   deque container.
 * @param t_count      element number.
 * @param val_elemlist variable argumnet list of specificed element.
 * @return void.
 * @remarks if pdeq_deque == NULL or deque is uninitialized, then the behavior is undefined. the type of specificed
 *          element and deque element type must be same, otherwise the behavior is undefined. the first specificed is
 *          in use, others are not in use.
 */
extern void _deque_assign_elem_varg(deque_t* pdeq_deque, size_t t_count, va_list val_elemlist);

/**
 * Add specificed element at the end of deque container. 
 * @param pdeq_deque    deque container.
 * @param val_elemlist  specificed element.
 * @return void.
 * @remarks if pdeq_deque == NULL or deque is uninitialized, then the behavior is undefined. the type of specificed
 *          element and deque element type must be same, otherwise the behavior is undefined. the first specificed is
 *          in use, others are not in use.
 */
extern void _deque_push_back(deque_t* pdeq_deque, ...);

/**
 * Add specificed element from variable argument list at the end of deque container. 
 * @param pdeq_deque    deque container.
 * @param val_elemlist  variable argumnet list of specificed element.
 * @return void.
 * @remarks if pdeq_deque == NULL or deque is uninitialized, then the behavior is undefined. the type of specificed
 *          element and deque element type must be same, otherwise the behavior is undefined. the first specificed is
 *          in use, others are not in use.
 */
extern void _deque_push_back_varg(deque_t* pdeq_deque, va_list val_elemlist);

/**
 * Add specificed element at the begin of deque container. 
 * @param pdeq_deque    deque container.
 * @param val_elemlist  specificed element.
 * @return void.
 * @remarks if pdeq_deque == NULL or deque is uninitialized, then the behavior is undefined. the type of specificed
 *          element and deque element type must be same, otherwise the behavior is undefined. the first specificed is
 *          in use, others are not in use.
 */
extern void _deque_push_front(deque_t* pdeq_deque, ...);

/**
 * Add specificed element from variable argument list at the begin of deque container. 
 * @param pdeq_deque    deque container.
 * @param val_elemlist  variable argumnet list of specificed element.
 * @return void.
 * @remarks if pdeq_deque == NULL or deque is uninitialized, then the behavior is undefined. the type of specificed
 *          element and deque element type must be same, otherwise the behavior is undefined. the first specificed is
 *          in use, others are not in use.
 */
extern void _deque_push_front_varg(deque_t* pdeq_deque, va_list val_elemlist);

/**
 * Reset the size of deque elements.
 * @param pdeq_deque    deque container.
 * @param t_resize      new size of deque elements.
 * @param ...           specificed element.
 * @return void.
 * @remarks if pdeq_deque == NULL or deque is uninitialized, then the behavior is undefined. the type of specificed
 *          element and deque element type must be same, otherwise the behavior is undefined. the first specificed is
 *          in use, others are not in use. if t_resize less than current deque size, then erase elmement from the end.
 *          if t_resize greater than current deque size, then append elements to the end, and the element is specificed
 *          element.
 */
extern void _deque_resize_elem(deque_t* pdeq_deque, size_t t_resize, ...);

/**
 * Reset the size of deque elements, and filled element is from variable argument list.
 * @param pdeq_deque    deque container.
 * @param t_resize      new size of deque elements.
 * @param val_elemlist  specificed element.
 * @return void.
 * @remarks if pdeq_deque == NULL or deque is uninitialized, then the behavior is undefined. the type of specificed
 *          element and deque element type must be same, otherwise the behavior is undefined. the first specificed is
 *          in use, others are not in use. if t_resize less than current deque size, then erase elmement from the end.
 *          if t_resize greater than current deque size, then append elements to the end, and the element is from
 *          variable argument list.
 */
extern void _deque_resize_elem_varg(deque_t* pdeq_deque, size_t t_resize, va_list val_elemlist);

/**
 * Insert multiple copys of element befor specificed position.
 * @param pdeq_deque    deque container.
 * @param it_pos        insert position.
 * @param t_count       element number.
 * @param ...           specificed element.
 * @return position refereced the first inserted elements.
 * @remarks if pdeq_deque == NULL or deque is uninitialized, then the behavior is undefined. the it_pos must be invalid
 *          iterator of deque container, otherwise the behavior is undefined. the type of specificed element and deque
 *          element type must be same, otherwise the behavior is undefined. the first specificed is in use, others are not
 *          in use.
 */
extern deque_iterator_t _deque_insert_n(deque_t* pdeq_deque, deque_iterator_t it_pos, size_t t_count, ...);

/**
 * Insert multiple copys of element befor specificed position, the element is from variable argument list.
 * @param pdeq_deque    deque container.
 * @param it_pos        insert position.
 * @param t_count       element number.
 * @param val_elemlist  specificed element.
 * @return position refereced the first inserted elements.
 * @remarks if pdeq_deque == NULL or deque is uninitialized, then the behavior is undefined. the it_pos must be invalid
 *          iterator of deque container, otherwise the behavior is undefined. the type of specificed element and deque
 *          element type must be same, otherwise the behavior is undefined. the first specificed is in use, others are not
 *          in use. the inserted element is from variable argument list.
 */
extern deque_iterator_t _deque_insert_n_varg(deque_t* pdeq_deque, deque_iterator_t it_pos, size_t t_count, va_list val_elemlist);

/**
 * Initialize element with deque element type auxiliary function.
 * @param pdeq_deque    deque container.
 * @param pv_elem       initialized element.
 * @return void.
 * @remarks if pdeq_deque == NULL or pv_elem == NULL, then the behavior is undefined. pdeq_deque must be initialized
 *          deque container or created by create_deque, otherwise the behavior is undefined.
 */
extern void _deque_init_elem_auxiliary(deque_t* pdeq_deque, void* pv_value);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_DEQUE_PRIVATE_H_ */
/** eof **/

