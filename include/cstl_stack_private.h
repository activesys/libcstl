/*
 *  The private interface of stack.
 *  Copyright (C)  2008 2009  Wangbo
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
#define _GET_STACK_DEQUE_SEQUENCE(_pt_stack)\
    (&((_pt_stack)->_t_sequence._t_deque))
#define _GET_STACK_LIST_SEQUENCE(_pt_stack)\
    (&((_pt_stack)->_t_sequence._t_list))
#define _GET_STACK_VECTOR_SEQUENCE(_pt_stack)\
    (&((_pt_stack)->_t_sequence._t_vector))

/** data type declaration and struct, union, enum section **/
/* the stack struct default use deque_t */
typedef struct _tagstack
{
    union
    {
        deque_t  _t_deque;
        list_t   _t_list;
        vector_t _t_vector;
    }_t_sequence; 
}stack_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * Create stack.
 */
extern stack_t _create_stack(size_t t_typesize, const char* s_typename);

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

