/*
 *  The implementation of stack.
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

/** include section **/
#ifdef HAVE_CONFIG_H
#   include <config.h>
#endif
#include <cstl/cdeque.h>
#include <cstl/clist.h>
#include <cstl/cvector.h>

#include <cstl/cstl_stack_private.h>
#include <cstl/cstl_stack.h>

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/* stack private function */
stack_t* _create_stack(const char* sz_typename)
{
#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    return (stack_t*)_create_vector(sz_typename);
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    return (stack_t*)_create_list(sz_typename);
#else
    return (stack_t*)_create_deque(sz_typename);
#endif
}

bool_t _create_stack_auxiliary(stack_t* pt_stack, const char* s_typename)
{
    assert(pt_stack != NULL && s_typename != NULL);
#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    return _create_vector_auxiliary(&pt_stack->_t_sequence, s_typename);
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    return _create_list_auxiliary(&pt_stack->_t_sequence, s_typename);
#else
    return _create_deque_auxiliary(&pt_stack->_t_sequence, s_typename);
#endif
}

void _stack_destroy_auxiliary(stack_t* pt_stack)
{
    assert(pt_stack != NULL);
#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    _vector_destroy_auxiliary(&pt_stack->_t_sequence);
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    _list_destroy_auxiliary(&pt_stack->_t_sequence);
#else
    _deque_destroy_auxiliary(&pt_stack->_t_sequence);
#endif
}

/* stack function */
void stack_init(stack_t* pt_stack)
{
    assert(pt_stack != NULL);
#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    vector_init(&pt_stack->_t_sequence);
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    list_init(&pt_stack->_t_sequence);
#else
    deque_init(&pt_stack->_t_sequence);
#endif
}

void stack_destroy(stack_t* pt_stack)
{
    assert(pt_stack != NULL);
#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    vector_destroy(&pt_stack->_t_sequence);
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    list_destroy(&pt_stack->_t_sequence);
#else
    deque_destroy(&pt_stack->_t_sequence);
#endif
}

void stack_init_copy(stack_t* pt_stackdest, const stack_t* cpt_stacksrc)
{
    assert(pt_stackdest != NULL && cpt_stacksrc != NULL);

#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    vector_init_copy(&pt_stackdest->_t_sequence, &cpt_stacksrc->_t_sequence);
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    list_init_copy(&pt_stackdest->_t_sequence, &cpt_stacksrc->_t_sequence);
#else
    deque_init_copy(&pt_stackdest->_t_sequence, &cpt_stacksrc->_t_sequence);
#endif
}

void stack_assign(stack_t* pt_stackdest, const stack_t* cpt_stacksrc)
{
    assert(pt_stackdest != NULL && cpt_stacksrc != NULL);

#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    vector_assign(&pt_stackdest->_t_sequence, &cpt_stacksrc->_t_sequence);
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    list_assign(&pt_stackdest->_t_sequence, &cpt_stacksrc->_t_sequence);
#else
    deque_assign(&pt_stackdest->_t_sequence, &cpt_stacksrc->_t_sequence);
#endif
}

bool_t stack_empty(const stack_t* cpt_stack)
{
    assert(cpt_stack != NULL);

#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    return vector_empty(&cpt_stack->_t_sequence);
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    return list_empty(&cpt_stack->_t_sequence);
#else
    return deque_empty(&cpt_stack->_t_sequence);
#endif
}

size_t stack_size(const stack_t* cpt_stack)
{
    assert(cpt_stack != NULL);

#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    return vector_size(&cpt_stack->_t_sequence);
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    return list_size(&cpt_stack->_t_sequence);
#else
    return deque_size(&cpt_stack->_t_sequence);
#endif
}

void* stack_top(const stack_t* cpt_stack)
{
    assert(cpt_stack != NULL);

#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    return vector_back(&cpt_stack->_t_sequence);
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    return list_back(&cpt_stack->_t_sequence);
#else
    return deque_back(&cpt_stack->_t_sequence);
#endif
}

void _stack_push(stack_t* pt_stack, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, pt_stack);
    _stack_push_varg(pt_stack, val_elemlist);
    va_end(val_elemlist);
}

void _stack_push_varg(stack_t* pt_stack, va_list val_elemlist)
{
    assert(pt_stack != NULL);

#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    _vector_push_back_varg(&pt_stack->_t_sequence, val_elemlist);
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    _list_push_back_varg(&pt_stack->_t_sequence, val_elemlist);
#else
    _deque_push_back_varg(&pt_stack->_t_sequence, val_elemlist);
#endif
}

void stack_pop(stack_t* pt_stack)
{
    assert(pt_stack != NULL);

#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    vector_pop_back(&pt_stack->_t_sequence);
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    list_pop_back(&pt_stack->_t_sequence);
#else
    deque_pop_back(&pt_stack->_t_sequence);
#endif
}

bool_t stack_equal(
    const stack_t* cpt_stackfirst, const stack_t* cpt_stacksecond)
{
    assert(cpt_stackfirst != NULL && cpt_stacksecond != NULL);

#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    return vector_equal(&cpt_stackfirst->_t_sequence, &cpt_stacksecond->_t_sequence);
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    return list_equal(&cpt_stackfirst->_t_sequence, &cpt_stacksecond->_t_sequence);
#else
    return deque_equal(&cpt_stackfirst->_t_sequence, &cpt_stacksecond->_t_sequence);
#endif
}

bool_t stack_not_equal(
    const stack_t* cpt_stackfirst, const stack_t* cpt_stacksecond)
{
    assert(cpt_stackfirst != NULL && cpt_stacksecond != NULL);

#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    return vector_not_equal(&cpt_stackfirst->_t_sequence, &cpt_stacksecond->_t_sequence);
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    return list_not_equal(&cpt_stackfirst->_t_sequence, &cpt_stacksecond->_t_sequence);
#else
    return deque_not_equal(&cpt_stackfirst->_t_sequence, &cpt_stacksecond->_t_sequence);
#endif
}

bool_t stack_less(
    const stack_t* cpt_stackfirst, const stack_t* cpt_stacksecond)
{
    assert(cpt_stackfirst != NULL && cpt_stacksecond != NULL);

#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    return vector_less(&cpt_stackfirst->_t_sequence, &cpt_stacksecond->_t_sequence);
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    return list_less(&cpt_stackfirst->_t_sequence, &cpt_stacksecond->_t_sequence);
#else
    return deque_less(&cpt_stackfirst->_t_sequence, &cpt_stacksecond->_t_sequence);
#endif
}

bool_t stack_greater(
    const stack_t* cpt_stackfirst, const stack_t* cpt_stacksecond)
{
    assert(cpt_stackfirst != NULL && cpt_stacksecond != NULL);

#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    return vector_greater(&cpt_stackfirst->_t_sequence, &cpt_stacksecond->_t_sequence);
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    return list_greater(&cpt_stackfirst->_t_sequence, &cpt_stacksecond->_t_sequence);
#else
    return deque_greater(&cpt_stackfirst->_t_sequence, &cpt_stacksecond->_t_sequence);
#endif
}

bool_t stack_less_equal(
    const stack_t* cpt_stackfirst, const stack_t* cpt_stacksecond)
{
    assert(cpt_stackfirst != NULL && cpt_stacksecond != NULL);

#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    return vector_less_equal(&cpt_stackfirst->_t_sequence, &cpt_stacksecond->_t_sequence);
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    return list_less_equal(&cpt_stackfirst->_t_sequence, &cpt_stacksecond->_t_sequence);
#else
    return deque_less_equal(&cpt_stackfirst->_t_sequence, &cpt_stacksecond->_t_sequence);
#endif
}

bool_t stack_greater_equal(
    const stack_t* cpt_stackfirst, const stack_t* cpt_stacksecond)
{
    assert(cpt_stackfirst != NULL && cpt_stacksecond != NULL);

#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    return vector_greater_equal(&cpt_stackfirst->_t_sequence, &cpt_stacksecond->_t_sequence);
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    return list_greater_equal(&cpt_stackfirst->_t_sequence, &cpt_stacksecond->_t_sequence);
#else
    return deque_greater_equal(&cpt_stackfirst->_t_sequence, &cpt_stacksecond->_t_sequence);
#endif
}

/** local function implementation section **/

/** eof **/

