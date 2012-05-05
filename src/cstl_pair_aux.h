/*
 *  The interface of pair auxiliary function.
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

#ifndef _CSTL_PAIR_AUX_H_
#define _CSTL_PAIR_AUX_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/* macros for type informations */
#define _GET_PAIR_FIRST_TYPE_SIZE(ppair_pair)              ((ppair_pair)->_t_typeinfofirst._pt_type->_t_typesize)
#define _GET_PAIR_FIRST_TYPE_NAME(ppair_pair)              ((ppair_pair)->_t_typeinfofirst._s_typename)
#define _GET_PAIR_FIRST_TYPE_BASENAME(ppair_pair)          ((ppair_pair)->_t_typeinfofirst._pt_type->_s_typename)
#define _GET_PAIR_FIRST_TYPE_INIT_FUNCTION(ppair_pair)     ((ppair_pair)->_t_typeinfofirst._pt_type->_t_typeinit)
#define _GET_PAIR_FIRST_TYPE_COPY_FUNCTION(ppair_pair)     ((ppair_pair)->_t_typeinfofirst._pt_type->_t_typecopy)
#define _GET_PAIR_FIRST_TYPE_LESS_FUNCTION(ppair_pair)     ((ppair_pair)->_t_typeinfofirst._pt_type->_t_typeless)
#define _GET_PAIR_FIRST_TYPE_DESTROY_FUNCTION(ppair_pair)  ((ppair_pair)->_t_typeinfofirst._pt_type->_t_typedestroy)
#define _GET_PAIR_FIRST_TYPE_STYLE(ppair_pair)             ((ppair_pair)->_t_typeinfofirst._t_style)

#define _GET_PAIR_SECOND_TYPE_SIZE(ppair_pair)             ((ppair_pair)->_t_typeinfosecond._pt_type->_t_typesize)
#define _GET_PAIR_SECOND_TYPE_NAME(ppair_pair)             ((ppair_pair)->_t_typeinfosecond._s_typename)
#define _GET_PAIR_SECOND_TYPE_BASENAME(ppair_pair)         ((ppair_pair)->_t_typeinfosecond._pt_type->_s_typename)
#define _GET_PAIR_SECOND_TYPE_INIT_FUNCTION(ppair_pair)    ((ppair_pair)->_t_typeinfosecond._pt_type->_t_typeinit)
#define _GET_PAIR_SECOND_TYPE_COPY_FUNCTION(ppair_pair)    ((ppair_pair)->_t_typeinfosecond._pt_type->_t_typecopy)
#define _GET_PAIR_SECOND_TYPE_LESS_FUNCTION(ppair_pair)    ((ppair_pair)->_t_typeinfosecond._pt_type->_t_typeless)
#define _GET_PAIR_SECOND_TYPE_DESTROY_FUNCTION(ppair_pair) ((ppair_pair)->_t_typeinfosecond._pt_type->_t_typedestroy)
#define _GET_PAIR_SECOND_TYPE_STYLE(ppair_pair)            ((ppair_pair)->_t_typeinfosecond._t_style)

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Test the two pair is have the same type.
 * @param cppair_first      first pair.
 * @param cppair_second     second pair.
 * @return true if two pair are same, otherwise return false.
 * @remarks if cppair_first == NULL or cppair_second == NULL, then the behavior is undefined.
 */
extern bool_t _pair_same_type(const pair_t* cppair_first, const pair_t* cppair_second);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_PAIR_AUX_H_ */
/** eof **/

