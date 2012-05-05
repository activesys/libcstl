/*
 *  The interface of map auxiliary function.
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

#ifndef _CSTL_MAP_AUX_H_
#define _CSTL_MAP_AUX_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/* macros for type informations */
#define _GET_MAP_FIRST_TYPE_SIZE(pmap_map)              ((pmap_map)->_pair_temp._t_typeinfofirst._pt_type->_t_typesize)
#define _GET_MAP_FIRST_TYPE_NAME(pmap_map)              ((pmap_map)->_pair_temp._t_typeinfofirst._s_typename)
#define _GET_MAP_FIRST_TYPE_BASENAME(pmap_map)          ((pmap_map)->_pair_temp._t_typeinfofirst._pt_type->_s_typename)
#define _GET_MAP_FIRST_TYPE_INIT_FUNCTION(pmap_map)     ((pmap_map)->_pair_temp._t_typeinfofirst._pt_type->_t_typeinit)
#define _GET_MAP_FIRST_TYPE_COPY_FUNCTION(pmap_map)     ((pmap_map)->_pair_temp._t_typeinfofirst._pt_type->_t_typecopy)
#define _GET_MAP_FIRST_TYPE_LESS_FUNCTION(pmap_map)     ((pmap_map)->_pair_temp._t_typeinfofirst._pt_type->_t_typeless)
#define _GET_MAP_FIRST_TYPE_DESTROY_FUNCTION(pmap_map)  ((pmap_map)->_pair_temp._t_typeinfofirst._pt_type->_t_typedestroy)
#define _GET_MAP_FIRST_TYPE_STYLE(pmap_map)             ((pmap_map)->_pair_temp._t_typeinfofirst._t_style)

#define _GET_MAP_SECOND_TYPE_SIZE(pmap_map)             ((pmap_map)->_pair_temp._t_typeinfosecond._pt_type->_t_typesize)
#define _GET_MAP_SECOND_TYPE_NAME(pmap_map)             ((pmap_map)->_pair_temp._t_typeinfosecond._s_typename)
#define _GET_MAP_SECOND_TYPE_BASENAME(pmap_map)         ((pmap_map)->_pair_temp._t_typeinfosecond._pt_type->_s_typename)
#define _GET_MAP_SECOND_TYPE_INIT_FUNCTION(pmap_map)    ((pmap_map)->_pair_temp._t_typeinfosecond._pt_type->_t_typeinit)
#define _GET_MAP_SECOND_TYPE_COPY_FUNCTION(pmap_map)    ((pmap_map)->_pair_temp._t_typeinfosecond._pt_type->_t_typecopy)
#define _GET_MAP_SECOND_TYPE_LESS_FUNCTION(pmap_map)    ((pmap_map)->_pair_temp._t_typeinfosecond._pt_type->_t_typeless)
#define _GET_MAP_SECOND_TYPE_DESTROY_FUNCTION(pmap_map) ((pmap_map)->_pair_temp._t_typeinfosecond._pt_type->_t_typedestroy)
#define _GET_MAP_SECOND_TYPE_STYLE(pmap_map)            ((pmap_map)->_pair_temp._t_typeinfosecond._t_style)

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
#ifndef NDEBUG
/**
 * Test the two pair is have the same type.
 * @param cppair_first      first pair.
 * @param cppair_second     second pair.
 * @return true if two pair are same, otherwise return false.
 * @remarks if cppair_first == NULL or cppair_second == NULL, then the behavior is undefined.
 */
extern bool_t _map_same_pair_type(const pair_t* cppair_first, const pair_t* cppair_second);

/**
 * Test the two pair is have the same type.
 * @param cppair_first      first pair.
 * @param cppair_second     second pair.
 * @return true if two pair are same, otherwise return false.
 * @remarks if cppair_first == NULL or cppair_second == NULL, then the behavior is undefined.
 */
extern bool_t _map_same_pair_type_ex(const pair_t* cppair_first, const pair_t* cppair_second);
#endif /* NDEBUG */

/**
 * map key compare and value compare
 * @param cpv_first         frist value.
 * @param cpv_second        second value.
 * @param pv_output         output.
 * @return void.
 * @remark if cpv_first == NULL or cpv_second == NULL or pv_output == NULL, then the behavior is undefined.
 */
extern void _map_value_compare(const void* cpv_first, const void* cpv_second, void* pv_output);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_MAP_AUX_H_ */
/** eof **/

