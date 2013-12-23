/*
 *  The private interface of function.
 *  Copyright (C)  2008 - 2014  Wangbo
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

#ifndef _CSTL_FUNCTION_PRIVATE_H_
#define _CSTL_FUNCTION_PRIVATE_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
typedef enum _tag_fun_type {
    _INVALID_FUN,

    /*
     * unary funtion type
     */
    _NEGATE_FUN,
    _LOGICAL_NOT_FUN,
    _INCREASE_FUN,
    _RANDOM_NUMBER_FUN,

    /*
     * binary function type
     */
    /* arithmetic */
    _PLUS_FUN,
    _MINUS_FUN,
    _MULTIPLIES_FUN,
    _DIVIDES_FUN,
    _MODULUS_FUN,
    /* comparisons */
    _EQUAL_FUN,
    _NOT_EQUAL_FUN,
    _GREATER_FUN,
    _GREATER_EQUAL_FUN,
    _LESS_FUN,
    _LESS_EQUAL_FUN,
    /* logical */
    _LOGICAL_AND_FUN,
    _LOGICAL_OR_FUN
} fun_type_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Select unary function accroding to unary function type.
 * @param it_iter       A iterator addressing the element.
 * @param ftype_type    Unary function type.
 * @return  Unary function.
 * @remarks The iterator and unary function type must be valid, otherwise the behavior is undefine.
 */
extern ufun_t _fun_get_unary(iterator_t it_iter, fun_type_t ftype_type);

/**
 * Select binary function accroding to binary function type.
 * @param it_iter       A iterator addressing the element.
 * @param ftype_type    Binary function type.
 * @return  Binary function.
 * @remarks The iterator and binary function type must be valid, otherwise the behavior is undefine.
 */
extern bfun_t _fun_get_binary(iterator_t it_iter, fun_type_t ftype_type);

/**
 * Increase.
 * @param cpv_input     Input.
 * @param pv_output     Output.
 * @return  void.
 * @remarks The input and output must not be NULL, otherwise the behavior is undefined.
 */
extern void _fun_increase_char(const void* cpv_input, void* pv_output);
extern void _fun_increase_uchar(const void* cpv_input, void* pv_output);
extern void _fun_increase_short(const void* cpv_input, void* pv_output);
extern void _fun_increase_ushort(const void* cpv_input, void* pv_output);
extern void _fun_increase_int(const void* cpv_input, void* pv_output);
extern void _fun_increase_uint(const void* cpv_input, void* pv_output);
extern void _fun_increase_long(const void* cpv_input, void* pv_output);
extern void _fun_increase_ulong(const void* cpv_input, void* pv_output);
extern void _fun_increase_float(const void* cpv_input, void* pv_output);
extern void _fun_increase_double(const void* cpv_input, void* pv_output);
#ifndef _MSC_VER
extern void _fun_increase_long_long(const void* cpv_input, void* pv_output);
extern void _fun_increase_ulong_long(const void* cpv_input, void* pv_output);
#endif

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_FUNCTION_PRIVATE_H_ */
/** eof **/

