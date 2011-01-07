/*
 *  The implementation of slist auxiliary functions.
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

#ifndef _CSTL_SLIST_AUX_H
#define _CSTL_SLIST_AUX_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/* macros for type informations */
#define _GET_SLIST_TYPE_SIZE(pslist_slist)             ((pslist_slist)->_t_typeinfo._pt_type->_t_typesize)
#define _GET_SLIST_TYPE_NAME(pslist_slist)             ((pslist_slist)->_t_typeinfo._sz_typename)
#define _GET_SLIST_TYPE_BASENAME(pslist_slist)         ((pslist_slist)->_t_typeinfo._pt_type->_sz_typename)
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

/*
 * Transfer functions.
 */
extern void _transfer(
    slist_iterator_t t_pos, slist_iterator_t t_begin, slist_iterator_t t_end);
extern void _transfer_after(
    slist_iterator_t t_pos, slist_iterator_t t_begin, slist_iterator_t t_end);

extern void _slist_get_varg_value_auxiliary(
    slist_t* pt_slist, va_list val_elemlist, slistnode_t* pt_node);
extern void _slist_destroy_varg_value_auxiliary(slist_t* pt_slist, slistnode_t* pt_node);
extern void _slist_init_node_auxiliary(slist_t* pt_slist, slistnode_t* pt_node);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_SLIST_AUX_H */
/** eof **/

