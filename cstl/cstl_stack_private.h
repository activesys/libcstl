/*
 *  The private interface of stack.
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

#ifndef _CSTL_STACK_PRIVATE_H_
#define _CSTL_STACK_PRIVATE_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
/* the stack struct default use deque_t */
typedef struct _tagstack
{
#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    vector_t _t_sequence;
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    list_t   _t_sequence;
#else
    deque_t  _t_sequence;
#endif
}stack_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Create stack adaptor.
 * @param s_typename    type name.
 * @return stack adaptor pointer, if create stack successfully, else return NULL.
 * @remarks if s_typename == NULL, the behavior is undefined. s_typename must be c builtin type, libcstl builtin type or
 *          user defined type, otherwise creation will be failure.
 */
extern stack_t* _create_stack(const char* s_typename);

/**
 * Create stack adaptor auxiliary function.
 * @param psk_stack  stack adaptor.
 * @param s_typename    type name.
 * @return true if create stack adaptor successfully, otherwise return false.
 * @remarks if psk_stack == NULL or s_typename == NULL, the behavior is undefined. s_typename must be c builtin type,
 *          libcstl builtin type or user defined type, otherwise creation will be failure.
 */
extern bool_t _create_stack_auxiliary(stack_t* psk_stack, const char* s_typename);

/**
 * Destroy stack adaptor auxiliary function.
 * @param psk_stack   stack adaptor.
 * @return void.
 * @remarks if psk_stack == NULL, then the behavior is undefined. stack adaptor must be initialized or created by
 *          create_stack, otherwise the behavior is undefined.
 */
extern void _stack_destroy_auxiliary(stack_t* psk_stack);

/**
 * Add specificed element at the top of stack. 
 * @param psk_stack       stack adaptor.
 * @param ...             specificed element.
 * @return void.
 * @remarks if psk_stack == NULL or stack is uninitialized, then the behavior is undefined. the type of specificed
 *          element and stack element type must be same, otherwise the behavior is undefined. the first specificed is
 *          in use, others are not in use.
 */
extern void _stack_push(stack_t* psk_stack, ...);

/**
 * Add specificed element from variable argument stack at the top of stack adaptor. 
 * @param psk_stack       stack adaptor.
 * @param val_elemlist    variable argumnet list of specificed element.
 * @return void.
 * @remarks if psk_stack == NULL or stack is uninitialized, then the behavior is undefined. the type of specificed
 *          element and stack element type must be same, otherwise the behavior is undefined. the first specificed is
 *          in use, others are not in use.
 */
extern void _stack_push_varg(stack_t* psk_stack, va_list val_elemlist);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_STACK_PRIVATE_H_ */
/** eof **/

