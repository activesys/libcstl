/*
 *  The implementation of stack.
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
 * Initialize an empty stack adaptor
 */
void stack_init(stack_t* psk_stack)
{
    assert(psk_stack != NULL);

#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    vector_init(&psk_stack->_t_sequence);
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    list_init(&psk_stack->_t_sequence);
#else
    deque_init(&psk_stack->_t_sequence);
#endif
}

/**
 * Initialize stack adaptor with exist stack adaptor.
 */
void stack_init_copy(stack_t* psk_dest, const stack_t* cpsk_src)
{
    assert(psk_dest != NULL);
    assert(cpsk_src != NULL);

#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    vector_init_copy(&psk_dest->_t_sequence, &cpsk_src->_t_sequence);
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    list_init_copy(&psk_dest->_t_sequence, &cpsk_src->_t_sequence);
#else
    deque_init_copy(&psk_dest->_t_sequence, &cpsk_src->_t_sequence);
#endif
}

/**
 * Destroy stack adaptor.
 */
void stack_destroy(stack_t* psk_stack)
{
    assert(psk_stack != NULL);

    _stack_destroy_auxiliary(psk_stack);
    free(psk_stack);
}

/**
 * Assign stack element with an exist stack adaptor.
 */
void stack_assign(stack_t* psk_dest, const stack_t* cpsk_src)
{
    assert(psk_dest != NULL);
    assert(cpsk_src != NULL);

#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    vector_assign(&psk_dest->_t_sequence, &cpsk_src->_t_sequence);
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    list_assign(&psk_dest->_t_sequence, &cpsk_src->_t_sequence);
#else
    deque_assign(&psk_dest->_t_sequence, &cpsk_src->_t_sequence);
#endif
}

/**
 * Tests if a stack is empty.
 */
bool_t stack_empty(const stack_t* cpsk_stack)
{
    assert(cpsk_stack != NULL);

#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    return vector_empty(&cpsk_stack->_t_sequence);
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    return list_empty(&cpsk_stack->_t_sequence);
#else
    return deque_empty(&cpsk_stack->_t_sequence);
#endif
}

/**
 * Return the number of elements in a stack.
 */
size_t stack_size(const stack_t* cpsk_stack)
{
    assert(cpsk_stack != NULL);

#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    return vector_size(&cpsk_stack->_t_sequence);
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    return list_size(&cpsk_stack->_t_sequence);
#else
    return deque_size(&cpsk_stack->_t_sequence);
#endif
}

/**
 * Access stack top data.
 */
void* stack_top(const stack_t* cpsk_stack)
{
    assert(cpsk_stack != NULL);

#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    return vector_back(&cpsk_stack->_t_sequence);
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    return list_back(&cpsk_stack->_t_sequence);
#else
    return deque_back(&cpsk_stack->_t_sequence);
#endif
}

/**
 * Delete the element at the begin of stack.
 */
void stack_pop(stack_t* psk_stack)
{
    assert(psk_stack != NULL);

#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    vector_pop_back(&psk_stack->_t_sequence);
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    list_pop_back(&psk_stack->_t_sequence);
#else
    deque_pop_back(&psk_stack->_t_sequence);
#endif
}

/**
 * Tests if the two stacks are equal.
 */
bool_t stack_equal(const stack_t* cpsk_first, const stack_t* cpsk_second)
{
    assert(cpsk_first != NULL);
    assert(cpsk_second != NULL);

#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    return vector_equal(&cpsk_first->_t_sequence, &cpsk_second->_t_sequence);
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    return list_equal(&cpsk_first->_t_sequence, &cpsk_second->_t_sequence);
#else
    return deque_equal(&cpsk_first->_t_sequence, &cpsk_second->_t_sequence);
#endif
}

/**
 * Test the two stacks are unequal.
 */
bool_t stack_not_equal(const stack_t* cpsk_first, const stack_t* cpsk_second)
{
    assert(cpsk_first != NULL);
    assert(cpsk_second != NULL);

#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    return vector_not_equal(&cpsk_first->_t_sequence, &cpsk_second->_t_sequence);
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    return list_not_equal(&cpsk_first->_t_sequence, &cpsk_second->_t_sequence);
#else
    return deque_not_equal(&cpsk_first->_t_sequence, &cpsk_second->_t_sequence);
#endif
}

/**
 * Test the first stack is less than the second stack.
 */
bool_t stack_less(const stack_t* cpsk_first, const stack_t* cpsk_second)
{
    assert(cpsk_first != NULL);
    assert(cpsk_second != NULL);

#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    return vector_less(&cpsk_first->_t_sequence, &cpsk_second->_t_sequence);
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    return list_less(&cpsk_first->_t_sequence, &cpsk_second->_t_sequence);
#else
    return deque_less(&cpsk_first->_t_sequence, &cpsk_second->_t_sequence);
#endif
}

/**
 * Test the first stack is less than or equal to the second stack.
 */
bool_t stack_less_equal(const stack_t* cpsk_first, const stack_t* cpsk_second)
{
    assert(cpsk_first != NULL);
    assert(cpsk_second != NULL);

#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    return vector_less_equal(&cpsk_first->_t_sequence, &cpsk_second->_t_sequence);
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    return list_less_equal(&cpsk_first->_t_sequence, &cpsk_second->_t_sequence);
#else
    return deque_less_equal(&cpsk_first->_t_sequence, &cpsk_second->_t_sequence);
#endif
}

/**
 * Test the first stack is greater than the second stack.
 */
bool_t stack_greater(const stack_t* cpsk_first, const stack_t* cpsk_second)
{
    assert(cpsk_first != NULL);
    assert(cpsk_second != NULL);

#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    return vector_greater(&cpsk_first->_t_sequence, &cpsk_second->_t_sequence);
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    return list_greater(&cpsk_first->_t_sequence, &cpsk_second->_t_sequence);
#else
    return deque_greater(&cpsk_first->_t_sequence, &cpsk_second->_t_sequence);
#endif
}

/**
 * Test the first stack is greater than or equal to the second stack.
 */
bool_t stack_greater_equal(const stack_t* cpsk_first, const stack_t* cpsk_second)
{
    assert(cpsk_first != NULL && cpsk_second != NULL);

#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    return vector_greater_equal(&cpsk_first->_t_sequence, &cpsk_second->_t_sequence);
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    return list_greater_equal(&cpsk_first->_t_sequence, &cpsk_second->_t_sequence);
#else
    return deque_greater_equal(&cpsk_first->_t_sequence, &cpsk_second->_t_sequence);
#endif
}

/** local function implementation section **/

/** eof **/

