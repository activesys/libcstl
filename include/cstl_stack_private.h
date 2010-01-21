/*
 *  The private interface of stack.
 *  Copyright (C)  2008,2009,2010  Wangbo
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

#ifndef _CSTL_STACK_PRIVATE_H
#define _CSTL_STACK_PRIVATE_H

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
/*
 * Create stack.
 */
extern stack_t* _create_stack(const char* s_typename);
extern bool_t _create_stack_auxiliary(stack_t* pt_stack, const char* s_typename);
extern void _stack_destroy_auxiliary(stack_t* pt_stack);

/*
 * Push element.
 */
extern void _stack_push(stack_t* pt_stack, ...);
extern void _stack_push_varg(stack_t* pt_stack, va_list val_elemlist);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_STACK_PRIVATE_H */
/** eof **/

