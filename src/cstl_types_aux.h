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
#define _TYPE_CACHE_COUNT       256

/** data type declaration and struct, union, enum section **/
/**
 * type style cache
 */
typedef struct _tagtypecache {
    char                _s_typename[_TYPE_NAME_SIZE + 1];
    char                _s_formalname[_TYPE_NAME_SIZE + 1];
    _typestyle_t        _t_style;
}_typecache_t;

/** exported global variable declaration section **/
extern _typeregister_t  _gt_typeregister;
extern _typecache_t     _gt_typecache[_TYPE_CACHE_COUNT];
extern size_t           _gt_typecache_index;

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
/**
 * Find in type style cache and update cache.
 */
extern _typestyle_t _type_cache_find(const char* s_typename, char* s_formalname);
extern void _type_cache_update(const char* s_typename, const char* s_formalname, _typestyle_t t_style);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_TYPES_AUX_H_ */
/** eof **/

