/*
 *  The private interface of pair.
 *  Copyright (C)  2008 - 2013  Wangbo
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

#ifndef _CSTL_PAIR_PRIVATE_H_
#define _CSTL_PAIR_PRIVATE_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
typedef struct _tagpair
{
    /* element type information */
    _typeinfo_t       _t_typeinfofirst;
    _typeinfo_t       _t_typeinfosecond;

    void*             _pv_first;
    void*             _pv_second;

    /* this two members are only used for map key and value compare. */
    bfun_t            _bfun_mapkeycompare;
    bfun_t            _bfun_mapvaluecompare;
}pair_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Create pair container.
 * @param s_typename        element type name.
 * @return if create pair successfully return pair pointer, otherwise return NULL.
 * @remarks s_typename == NULL, then the behavior is undefined. s_typename should be C builtin type name, libcstl builtin
 *          typename or registed user defined type name, otherwise the function will return NULL.
 */
extern pair_t* _create_pair(const char* s_typename);

/**
 * Create pair container auxiliary function.
 * @param ppair_pair        uncreated container.
 * @param s_typename        element type name.
 * @return if create pair successfully return true, otherwise return false.
 * @remarks if ppair_pair == NULL or s_typename == NULL, then the behavior is undefined. s_typename should be C builtin
 *          type name, libcstl builtin typename or registed user defined type name, otherwise the function will return false.
 */
extern bool_t _create_pair_auxiliary(pair_t* ppair_pair, const char* s_typename);

/**
 * Destroy pair container auxiliary function.
 * @param ppair_pair        pair container.
 * @return void.
 * @remarks if ppair_pair == NULL, then the behavior is undefined. pair must be initialized or created by
 *          _create_pair(), otherwise the behavior is undefine.
 */
extern void _pair_destroy_auxiliary(pair_t* ppair_pair);

/**
 * Assignment for the first element of pair.
 * @param ppair_pair        pair container.
 * @param ...               user defined data.
 * @return void.
 * @remarks if ppair_pair == NULL, then the behavior is undefined. pair must be initialized, otherwise the behavior is undefine.
 */
extern void _pair_make_first(pair_t* ppair_pair, ...);

/**
 * Assignment for the second element of pair.
 * @param ppair_pair        pair container.
 * @param ...               user defined data.
 * @return void.
 * @remarks if ppair_pair == NULL, then the behavior is undefined. pair must be initialized, otherwise the behavior is undefine.
 */
extern void _pair_make_second(pair_t* ppair_pair, ...);

/**
 * Test pair is created by create_pair.
 * @param cppair_pair           pair container.
 * @return if pair is created by create_pair, then return true, else return false.
 * @remarks if cppair_pair == NULL, then the behavior is undefined.
 */
extern bool_t _pair_is_created(const pair_t* cppair_pair);

/**
 * Test pair is initialized by pair initialization functions.
 * @param cppair_pair           pair container.
 * @return if pair is initialized by pair initialization functions, then return true, else return false.
 * @remarks if cppair_pair == NULL, then the behavior is undefined.
 */
extern bool_t _pair_is_inited(const pair_t* cppair_pair);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_PAIR_PRIVATE_H_ */
/** eof **/

