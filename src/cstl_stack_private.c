/*
 *  The implementation of stack private function.
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

/** include section **/
#include <cstl/cstack.h>

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Create stack container.
 */
stack_t* _create_stack(const char* s_typename)
{
    stack_t* psk_new = NULL;

    assert(s_typename != NULL);

    /* allocate memory for stack */
    if ((psk_new = (stack_t*)malloc(sizeof(stack_t))) == NULL) {
        return NULL;
    }

    if (!_create_stack_auxiliary(psk_new, s_typename)) {
        free(psk_new);
        return NULL;
    }

    return psk_new;
}

/**
 * Create stack container auxiliary function.
 */
bool_t _create_stack_auxiliary(stack_t* psk_stack, const char* s_typename)
{
    assert(psk_stack != NULL);
    assert(s_typename != NULL);

#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    return _create_vector_auxiliary(&psk_stack->_t_sequence, s_typename);
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    return _create_list_auxiliary(&psk_stack->_t_sequence, s_typename);
#else
    return _create_deque_auxiliary(&psk_stack->_t_sequence, s_typename);
#endif
}

/**
 * Destroy stack container auxiliary function.
 */
void _stack_destroy_auxiliary(stack_t* psk_stack)
{
    assert(psk_stack != NULL);

#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    _vector_destroy_auxiliary(&psk_stack->_t_sequence);
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    _list_destroy_auxiliary(&psk_stack->_t_sequence);
#else
    _deque_destroy_auxiliary(&psk_stack->_t_sequence);
#endif
}

/**
 * Add specificed element at the top of stack. 
 */
void _stack_push(stack_t* psk_stack, ...)
{
    va_list val_elemlist;

    assert(psk_stack != NULL);

    va_start(val_elemlist, psk_stack);
    _stack_push_varg(psk_stack, val_elemlist);
    va_end(val_elemlist);
}

/**
 * Add specificed element from variable argument stack at the top of stack adaptor. 
 */
void _stack_push_varg(stack_t* psk_stack, va_list val_elemlist)
{
    assert(psk_stack != NULL);

#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    _vector_push_back_varg(&psk_stack->_t_sequence, val_elemlist);
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    _list_push_back_varg(&psk_stack->_t_sequence, val_elemlist);
#else
    _deque_push_back_varg(&psk_stack->_t_sequence, val_elemlist);
#endif
}

/** local function implementation section **/

/** eof **/

