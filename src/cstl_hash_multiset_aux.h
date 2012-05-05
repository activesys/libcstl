/*
 *  The interface of hash_multiset auxiliary function.
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

#ifndef _CSTL_HASH_MULTISET_AUX_H_
#define _CSTL_HASH_MULTISET_AUX_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/* macros for type informations */
#define _GET_HASH_MULTISET_TYPE_SIZE(phmset_set)             ((phmset_set)->_t_hashtable._t_typeinfo._pt_type->_t_typesize)
#define _GET_HASH_MULTISET_TYPE_NAME(phmset_set)             ((phmset_set)->_t_hashtable._t_typeinfo._s_typename)
#define _GET_HASH_MULTISET_TYPE_BASENAME(phmset_set)         ((phmset_set)->_t_hashtable._t_typeinfo._pt_type->_s_typename)
#define _GET_HASH_MULTISET_TYPE_INIT_FUNCTION(phmset_set)    ((phmset_set)->_t_hashtable._t_typeinfo._pt_type->_t_typeinit)
#define _GET_HASH_MULTISET_TYPE_COPY_FUNCTION(phmset_set)    ((phmset_set)->_t_hashtable._t_typeinfo._pt_type->_t_typecopy)
#define _GET_HASH_MULTISET_TYPE_LESS_FUNCTION(phmset_set)    ((phmset_set)->_t_hashtable._t_typeinfo._pt_type->_t_typeless)
#define _GET_HASH_MULTISET_TYPE_DESTROY_FUNCTION(phmset_set) ((phmset_set)->_t_hashtable._t_typeinfo._pt_type->_t_typedestroy)
#define _GET_HASH_MULTISET_TYPE_STYLE(phmset_set)            ((phmset_set)->_t_hashtable._t_typeinfo._t_style)

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Obtain data from variable argument list, the data type and hash_multiset element data type are same.
 * @param phmset_set         hash_multiset container.
 * @param val_elemlist      variable argument list.
 * @param pv_varg           data buffer.
 * @return void.
 * @remarks if phmset_set == NULL or pv_varg == NULL, then the behavior is undefined. phmset_set must be initialized
 *          or created by create_hash_multiset(), otherwise the behavior is undefined.
 */
extern void _hash_multiset_get_varg_value_auxiliary(hash_multiset_t* phmset_set, va_list val_elemlist, void* pv_varg);

/**
 * Destroy data, the data type and hash_multiset element data type are same.
 * @param phmset_set         hash_multiset container.
 * @param pv_varg           data buffer.
 * @return void.
 * @remarks if phmset_set == NULL or pv_varg == NULL, then the behavior is undefined. phmset_set must be initialized
 *          or created by create_hash_multiset(), otherwise the behavior is undefined.
 */
extern void _hash_multiset_destroy_varg_value_auxiliary(hash_multiset_t* phmset_set, void* pv_varg);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_HASH_MULTISET_AUX_H_ */
/** eof **/

