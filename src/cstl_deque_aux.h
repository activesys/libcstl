/*
 *  The implement of deque auxiliary function.
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

#ifndef _CSTL_DEQUE_AUX_H_
#define _CSTL_DEQUE_AUX_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
#define _DEQUE_MAP_COUNT                16
#define _DEQUE_MAP_GROW_STEP            8
#define _DEQUE_ELEM_COUNT               16

/* macros for type informations */
#define _GET_DEQUE_TYPE_SIZE(pdeq_deque)             ((pdeq_deque)->_t_typeinfo._pt_type->_t_typesize)
#define _GET_DEQUE_TYPE_NAME(pdeq_deque)             ((pdeq_deque)->_t_typeinfo._s_typename)
#define _GET_DEQUE_TYPE_BASENAME(pdeq_deque)         ((pdeq_deque)->_t_typeinfo._pt_type->_s_typename)
#define _GET_DEQUE_TYPE_INIT_FUNCTION(pdeq_deque)    ((pdeq_deque)->_t_typeinfo._pt_type->_t_typeinit)
#define _GET_DEQUE_TYPE_COPY_FUNCTION(pdeq_deque)    ((pdeq_deque)->_t_typeinfo._pt_type->_t_typecopy)
#define _GET_DEQUE_TYPE_LESS_FUNCTION(pdeq_deque)    ((pdeq_deque)->_t_typeinfo._pt_type->_t_typeless)
#define _GET_DEQUE_TYPE_DESTROY_FUNCTION(pdeq_deque) ((pdeq_deque)->_t_typeinfo._pt_type->_t_typedestroy)
#define _GET_DEQUE_TYPE_STYLE(pdeq_deque)            ((pdeq_deque)->_t_typeinfo._t_style)

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
#ifndef NDEBUG
/**
 * Test iterator referenced data is within the deque.
 * @param cpdeq_deque point to deque container.
 * @param it_iter deque iterator.
 * @return if iterator referenced is within the deque, then return true, otherwise return false.
 * @remarks if cpdeq_deque == NULL, then the behavior is undefined, the it_iter must be valie deque iterator and
 *          must belong to deque, otherwist the behavior is undefined. 
 */
extern bool_t _deque_iterator_belong_to_deque(const deque_t* cpdeq_deque, deque_iterator_t it_iter);

/**
 * Test the type that saved in the deque container and referenced by it_iter are same.
 * @param cpdeq_deque  deque container.
 * @param it_iter      deque iterator.
 * @return if the type is same, return true, else return false.
 * @remarks if cpdeq_first == NULL or it_iter is not deque iterator, then the behavior is undefined.
 */
extern bool_t _deque_same_deque_iterator_type(const deque_t* cpdeq_deque, deque_iterator_t it_iter);

/**
 * Test the type that saved in the deque container and referenced by it_iter are same.
 * @param cpdeq_deque  deque container.
 * @param it_iter      iterator.
 * @return if the type is same, return true, else return false.
 * @remarks if cpdeq_first == NULL, then the behavior is undefined.
 */
extern bool_t _deque_same_iterator_type(const deque_t* cpdeq_deque, iterator_t it_iter);

/**
 * Test deque is created by create_deque.
 * @param cpdeq_deque  deque container.
 * @return if deque is created by create_deque, then return true, else return false.
 * @remarks if cpdeq_deque == NULL, then the behavior is undefined.
 */
extern bool_t _deque_is_created(const deque_t* cpdeq_deque);
#endif /* NDEBUG */

/**
 * Test deque is initialized by deque initialization functions.
 * @param cpdeq_deque  deque container.
 * @return if deque is initialized by deque initialization functions, then return true, else return false.
 * @remarks if cpdeq_deque == NULL, then the behavior is undefined.
 */
extern bool_t _deque_is_inited(const deque_t* cpdeq_deque);

/**
 * Test the type that saved in the deque container is same.
 * @param cpdeq_first first deque.
 * @param cpdeq_second second deque.
 * @return if the type is same, return true, else return false.
 * @remarks if cpdeq_first == NULL or cpdeq_second == NULL, the behavior is undefined. the two deque must be
 *          initialized or created by create_deque(), otherwise the behavior is undefined.
 */
extern bool_t _deque_same_type(const deque_t* cpdeq_first, const deque_t* cpdeq_second);

/**
 * Expand deque at end.
 * @param pdeq_deque   deque container.
 * @param t_expandsize expand size.
 * @param pit_pos      iterator pointer.
 * @return iterator that reference deque end before expanding.
 * @remarks if pdeq_deque == NULL, then the behavior is undefined. the deque container must be initialized, otherwise the
 *          behavior is undefined. *pit_pos must be valid deque iterator, otherwise the behavior is undefined. the pit_pos
 *          may be NULL.
 */
extern deque_iterator_t _deque_expand_at_end(deque_t* pdeq_deque, size_t t_expandsize, deque_iterator_t* pit_pos);

/**
 * Expand deque at begin.
 * @param pdeq_deque   deque container.
 * @param t_expandsize expand size.
 * @param pit_pos      iterator pointer.
 * @return iterator that reference deque begin before expanding.
 * @remarks if pdeq_deque == NULL, then the behavior is undefined. the deque container must be initialized, otherwise the
 *          behavior is undefined. *pit_pos must be valid deque iterator, otherwise the behavior is undefined. the pit_pos
 *          may be NULL.
 */
extern deque_iterator_t _deque_expand_at_begin(deque_t* pdeq_deque, size_t t_expandsize, deque_iterator_t* pit_pos);

/**
 * Shrink deque at end.
 * @param pdeq_deque   deque container.
 * @param t_shrinksize shrink size.
 * @return void.
 * @remarks if pdeq_deque == NULL, then the behavior is undefined. the deque container must be initialized, otherwise the
 *          behavior is undefined. if t_shrinksize > deque_size(pdeq_deque), then this function erase all elements.
 */
extern void _deque_shrink_at_end(deque_t* pdeq_deque, size_t t_shrinksize);

/**
 * Shrink deque at begin.
 * @param pdeq_deque   deque container.
 * @param t_shrinksize shrink size.
 * @return void.
 * @remarks if pdeq_deque == NULL, then the behavior is undefined. the deque container must be initialized, otherwise the
 *          behavior is undefined. if t_shrinksize > deque_size(pdeq_deque), then this function erase all elements.
 */
extern void _deque_shrink_at_begin(deque_t* pdeq_deque, size_t t_shrinksize);

/**
 * Move element range to deque end.
 * @param pdeq_deque   deque container.
 * @param it_begin     range begin.
 * @param it_end       range end.
 * @param t_step       move step.
 * @return the begin of gap range.
 * @remarks if pdeq_deque == NULL, then the behavior is undefined. the deque container must be initialized, otherwise the
 *          behavior is undefine. [it_begin, it_end) must be valid for deque container, otherwise the behavior is undefine.
 *          [it_begin, it_end) must also be valid for deque container after moving, otherwise the behavior is undefine.
 */
extern deque_iterator_t _deque_move_elem_to_end(
    deque_t* pdeq_deque, deque_iterator_t it_begin, deque_iterator_t it_end, size_t t_step);

/**
 * Move element range to deque begin.
 * @param pdeq_deque   deque container.
 * @param it_begin     range begin.
 * @param it_end       range end.
 * @param t_step       move step.
 * @return the begin of gap range.
 * @remarks if pdeq_deque == NULL, then the behavior is undefined. the deque container must be initialized, otherwise the
 *          behavior is undefine. [it_begin, it_end) must be valid for deque container, otherwise the behavior is undefine.
 *          [it_begin, it_end) must also be valid for deque container after moving, otherwise the behavior is undefine.
 */
extern deque_iterator_t _deque_move_elem_to_begin(
    deque_t* pdeq_deque, deque_iterator_t it_begin, deque_iterator_t it_end, size_t t_step);

/**
 * Obtain data from variable argument list, the data type and deque element data type are same.
 * @param pdeq_deque   deque container.
 * @param val_elemlist variable argument list.
 * @param pv_varg      data buffer.
 * @return void.
 * @remarks if pdeq_deque == NULL or pv_varg == NULL, then the behavior is undefined. pdeq_deque must be initialized
 *          or created by create_deque(), otherwise the behavior is undefined.
 */
extern void _deque_get_varg_value_auxiliary(deque_t* pdeq_deque, va_list val_elemlist, void* pv_varg);

/**
 * Destroy data, the data type and deque element data type are same.
 * @param pdeq_deque   deque container.
 * @param pv_varg      data buffer.
 * @return void.
 * @remarks if pdeq_deque == NULL or pv_varg == NULL, then the behavior is undefined. pdeq_deque must be initialized
 *          or created by create_deque(), otherwise the behavior is undefined.
 */
extern void _deque_destroy_varg_value_auxiliary(deque_t* pdeq_deque, void* pv_varg);

/**
 * Initialize data within range [it_begin, it_end) according to deque element data type.
 * @param pdeq_deque   deque container.
 * @param it_begin     range begin.
 * @param it_end       range end.
 * @return void.
 * @remarks if pdeq_deque == NULL, then the behavior is undefined. pdeq_deque must be initialized or created by create_deque(),
 *          otherwise the behavior is undefined. [it_begin, it_end) must be valid range, and the type of pdeq_deque and 
 *          [it_begin, it_end) must be the same, otherwise the behavior is undefined.
 */
extern void _deque_init_elem_range_auxiliary(deque_t* pdeq_deque, deque_iterator_t it_begin, deque_iterator_t it_end);

/**
 * Get the iterator pointer auxiliary function.
 * @param it_iter deque iterator.
 * @return data pointer.
 * @remarks it_iter must be valid deque iterator, otherwise the behavior is undefined.
 */
extern void* _deque_iterator_get_pointer_auxiliary(iterator_t it_iter);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_DEQUE_AUX_H_ */
/** eof **/

