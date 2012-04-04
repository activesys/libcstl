/*
 *  The implement of cstl type auxiliary functions.
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

#ifndef _CSTL_TYPES_AUX_H_
#define _CSTL_TYPES_AUX_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/
extern _typeregister_t _gt_typeregister;

/** exported function prototype section **/
/**
 * Caculate hash from type name.
 * @param s_typename    type name.
 * @return hash.
 * @remarks s_typename must be not NULL.
 */
extern size_t _type_hash(const char* s_typename);
/**
 * Test the type is registered or not
 * @param s_typename    type name.
 * @return type point to registered type name.
 * @remarks s_typename must be not NULL.
 */
extern _type_t* _type_is_registered(const char* s_typename);
/**
 * Initialize the register and register c builtin type and cstl builtin type 
 */
extern void _type_init(void);
extern void _type_register_c_builtin(void);
extern void _type_register_cstl_builtin(void);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_TYPES_AUX_H_ */
/** eof **/

