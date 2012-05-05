/*
 *  The implementation of slist auxiliary functions.
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

#ifndef _CSTL_SLIST_AUX_H_
#define _CSTL_SLIST_AUX_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/* macros for type informations */
#define _GET_SLIST_TYPE_SIZE(pslist_slist)             ((pslist_slist)->_t_typeinfo._pt_type->_t_typesize)
#define _GET_SLIST_TYPE_NAME(pslist_slist)             ((pslist_slist)->_t_typeinfo._s_typename)
#define _GET_SLIST_TYPE_BASENAME(pslist_slist)         ((pslist_slist)->_t_typeinfo._pt_type->_s_typename)
#define _GET_SLIST_TYPE_INIT_FUNCTION(pslist_slist)    ((pslist_slist)->_t_typeinfo._pt_type->_t_typeinit)
#define _GET_SLIST_TYPE_COPY_FUNCTION(pslist_slist)    ((pslist_slist)->_t_typeinfo._pt_type->_t_typecopy)
#define _GET_SLIST_TYPE_LESS_FUNCTION(pslist_slist)    ((pslist_slist)->_t_typeinfo._pt_type->_t_typeless)
#define _GET_SLIST_TYPE_DESTROY_FUNCTION(pslist_slist) ((pslist_slist)->_t_typeinfo._pt_type->_t_typedestroy)
#define _GET_SLIST_TYPE_STYLE(pslist_slist)            ((pslist_slist)->_t_typeinfo._t_style)

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
#ifndef NDEBUG
/**
 * Test iterator referenced data is within the slist.
 * @param cpslist_slist   point to slist container.
 * @param it_iter         slist iterator.
 * @return if iterator referenced is within the slist, then return true, otherwise return false.
 * @remarks if cpslist_slist == NULL, then the behavior is undefined, the it_iter must be valie slist iterator and
 *          must belong to slist, otherwist the behavior is undefined. 
 */
extern bool_t _slist_iterator_belong_to_slist(const slist_t* cpslist_slist, slist_iterator_t it_iter);

/**
 * Test the type that saved in the slist container and referenced by it_iter are same.
 * @param cpslist_slist   slist container.
 * @param it_iter         slist iterator.
 * @return if the type is same, return true, else return false.
 * @remarks if cpslist_first == NULL or it_iter is not slist iterator, then the behavior is undefined.
 */
extern bool_t _slist_same_slist_iterator_type(const slist_t* cpslist_slist, slist_iterator_t it_iter);

/**
 * Test the type that saved in the slist container and referenced by it_iter are same.
 * @param cpslist_slist   slist container.
 * @param it_iter         iterator.
 * @return if the type is same, return true, else return false.
 * @remarks if cpslist_first == NULL, then the behavior is undefined.
 */
extern bool_t _slist_same_iterator_type(const slist_t* cpslist_slist, iterator_t it_iter);

/**
 * Test slist is created by create_slist.
 * @param cpslist_slist  slist container.
 * @return if slist is created by create_slist, then return true, else return false.
 * @remarks if cpslist_slist == NULL, then the behavior is undefined.
 */
extern bool_t _slist_is_created(const slist_t* cpslist_slist);

/**
 * Test slist is initialized.
 * @param cpslist_slist  slist container.
 * @return if slist is initialized, then return true, else return false.
 * @remarks if cpslist_slist == NULL, then the behavior is undefined.
 */
extern bool_t _slist_is_inited(const slist_t* cpslist_slist);
#endif /* NDEBUG */

/**
 * Test the type that saved in the slist container is same.
 * @param cpslist_first    first slist.
 * @param cpslist_second   second slist.
 * @return if the type is same, return true, else return false.
 * @remarks if cpslist_first == NULL or cpslist_second == NULL, the behavior is undefined. the two slist must be
 *          initialized or created by create_slist(), otherwise the behavior is undefined.
 */
extern bool_t _slist_same_type(const slist_t* cpslist_first, const slist_t* cpslist_second);

/**
 * Transfer the range [it_begin, it_end) to position it_pos.
 * @param it_pos      insert data position.
 * @param it_begin    range start.
 * @param it_end      range end.
 * @return void.
 * @remarks it_pos, it_begin, it_end must be valid slist iterator, otherwise the behavior is undefined. [it_begin, it_end)
 *          must be valid slist data range, otherwise the beahvior is undefined. it_pos and [it_begin, it_end) may belong
 *          to same slist container, but if it_pos belongs to (it_begin, it_end), then the behavior is undefined. if
 *          it_pos == it_begin or it_pos == it_end or it_begin == it_end, then the function does nothing.
 */
extern void _slist_transfer(slist_iterator_t it_pos, slist_iterator_t it_begin, slist_iterator_t it_end);

/**
 * Transfer the range [it_begin, it_end) to position it_pos+1.
 * @param it_pos      insert data position.
 * @param it_begin    range start.
 * @param it_end      range end.
 * @return void.
 * @remarks it_pos, it_begin, it_end must be valid slist iterator, otherwise the behavior is undefined. [it_begin, it_end)
 *          must be valid slist data range, otherwise the beahvior is undefined. it_pos and [it_begin, it_end) may belong
 *          to same slist container, but if it_pos+1 belongs to (it_begin, it_end), then the behavior is undefined. if
 *          it_pos+1 == it_begin or it_pos+1 == it_end or it_begin == it_end, then the function does nothing.
 */
extern void _slist_transfer_after(slist_iterator_t it_pos, slist_iterator_t it_begin, slist_iterator_t it_end);

/**
 * Obtain data from variable argument slist, the data type and slist element data type are same.
 * @param pslist_slist   slist container.
 * @param val_elemlist   variable argument list.
 * @param pt_node        data buffer.
 * @return void.
 * @remarks if pslist_slist == NULL or pt_node == NULL, then the behavior is undefined. pslist_slist must be initialized
 *          or created by create_slist(), otherwise the behavior is undefined.
 */
extern void _slist_get_varg_value_auxiliary(slist_t* pslist_slist, va_list val_elemlist, _slistnode_t* pt_node);

/**
 * Destroy data, the data type and slist element data type are same.
 * @param pslist_slist   slist container.
 * @param pt_node        data buffer.
 * @return void.
 * @remarks if pslist_slist == NULL or pt_node == NULL, then the behavior is undefined. pslist_slist must be initialized
 *          or created by create_slist(), otherwise the behavior is undefined.
 */
extern void _slist_destroy_varg_value_auxiliary(slist_t* pslist_slist, _slistnode_t* pt_node);

/**
 * Initialize slist node auxiliary function.
 * @param pslist_slist   slist container.
 * @param pt_node        data buffer.
 * @return void.
 * @remarks if pslist_slist == NULL or pt_node == NULL, then the behavior is undefined. pslist_slist must be initialized
 *          or created by create_slist(), otherwise the behavior is undefined.
 */
extern void _slist_init_node_auxiliary(slist_t* pslist_slist, _slistnode_t* pt_node);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_SLIST_AUX_H_ */
/** eof **/

