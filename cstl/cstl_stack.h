/*
 *  The interface of stack.
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

#ifndef _CSTL_STACK_H_
#define _CSTL_STACK_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/**
 * Create stack adaptor.
 * @param ...    type name.
 * @return stack adaptor pointer, if create stack successfully, else return NULL.
 * @remarks type name must be c builtin type, libcstl builtin type or user defined type, otherwise creation will be failure.
 */
#define create_stack(...) _create_stack(#__VA_ARGS__) 

/**
 * Add specificed element at the top of stack. 
 * @param psk_stack       stack adaptor.
 * @param elem            specificed element.
 * @return void.
 * @remarks if psk_stack == NULL or stack is uninitialized, then the behavior is undefined. the type of specificed
 *          element and stack element type must be same, otherwise the behavior is undefined.
 */
#define stack_push(psk_stack, elem) _stack_push((psk_stack), (elem))

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Initialize an empty stack adaptor
 * @param psk_stack   stack adaptor.
 * @return void.
 * @remarks if psk_stack == NULL, then the behavior is undefined. psk_stack must be created by create_stack(), otherwise
 *          the behavior is undefine.
 */
extern void stack_init(stack_t* psk_stack);

/**
 * Initialize stack adaptor with exist stack adaptor.
 * @param psk_dest   destination stack adaptor.
 * @param psk_src    source stack adaptor.
 * @return void.
 * @remarks if psk_dest == NULL or psk_src == NULL, then the behavior is undefined. psk_dest must be created by
 *          create_stack(), and psk_src must be initialized, otherwise the behavior is undefined. the element type of
 *          psk_dest and psk_src must be the same, otherwise the behavior is undefined.
 */
extern void stack_init_copy(stack_t* psk_dest, const stack_t* cpsk_src);

/**
 * Destroy stack adaptor.
 * @param psk_stack   stack adaptor.
 * @return void.
 * @remraks if psk_stack == NULLL, then the behavior is undefined. psk_stack must be initialized or created by
 *          create_stack(), otherwise the behavior is undefined.
 */
extern void stack_destroy(stack_t* psk_stack);

/**
 * Assign stack element with an exist stack adaptor.
 * @param psk_dest     destination stack adaptor.
 * @param cpsk_src     source stack adaptor.
 * @return void.
 * @remarks if psk_dest == NULL or cpsk_src == NULL, then the behavior is undefined. psk_dest and cpsk_src must be
 *          initialized, otherwise the behavior is undefined. the element type of two stack must be same, otherwise
 *          the behavior is undefined. if the destination stack equal to source stack, then this function does nothing.
 */
extern void stack_assign(stack_t* psk_dest, const stack_t* cpsk_src);

/**
 * Return the number of elements in a stack.
 * @param cpsk_stack  stack adaptor.
 * @return the number of elements in the stack.
 * @remarks if cpsk_stack == NULL, then the behavior is undefined. the cpsk_stack must be initialized, otherwise the
 *          behavior is undefine.
 */
extern size_t stack_size(const stack_t* cpsk_stack);

/**
 * Tests if a stack is empty.
 * @param cpsk_stack  stack adaptor.
 * @return true if the stack is empty, else returns false.
 * @remarks if cpsk_stack == NULL, then the behavior is undefined. the cpsk_stack must be initialized, otherwise the
 *          behavior is undefine.
 */
extern bool_t stack_empty(const stack_t* cpsk_stack);

/**
 * Access stack top data.
 * @param cpsk_stack  stack adaptor.
 * @return pointer to the data.
 * @remarks if cpsk_stack == NULL, then the behavior is undefined. the stack must be initialized, otherwise the behavior
 *          is undefined. if stack is empty, the behavior is undefine.
 */
extern void* stack_top(const stack_t* cpsk_stack);

/**
 * Delete the element at the begin of stack.
 * @param psk_stack    stack adaptor.
 * @return void.
 * @remarks if psk_stack == NULL, then the behavior is undefined. the stack must be initialized, otherwise the behavior
 *          is undefined. if stack is empty, then the behavior is undefined.
 */
extern void stack_pop(stack_t* psk_stack);

/**
 * Tests if the two stacks are equal.
 * @param cpsk_first   first stack adaptor.
 * @param cpsk_second  second stack adaptor.
 * @return if first stack equal to second stack, then return true, else return false.
 * @remarks if cpsk_first == NULL or cpsk_second == NULL, then the behavior is undefined. the two stacks must be
 *          initialized, otherwise the behavior is undefined. if the two stacks are not same type, the behavior is undefined.
 *          if cpsk_first == cpsk_second, then return true.
 */
extern bool_t stack_equal(const stack_t* cpsk_first, const stack_t* cpsk_second);

/**
 * Test the two stacks are unequal.
 * @param cpsk_first   first stack adaptor.
 * @param cpsk_second  second stack adaptor.
 * @return if first stack unequal to second stack, then return true, else return false.
 * @remarks if cpsk_first == NULL or cpsk_second == NULL, then the behavior is undefined. the two stacks must be
 *          initialized, otherwise the behavior is undefined. if the two stacks are not same type, the behavior is undefined.
 *          if cpsk_first == cpsk_second, then return false.
 */
extern bool_t stack_not_equal(const stack_t* cpsk_first, const stack_t* cpsk_second);

/**
 * Test the first stack is less than the second stack.
 * @param cpsk_first   first stack adaptor.
 * @param cpsk_second  second stack adaptor.
 * @return if the first stack is less than the second stack, then return true, else return false.
 * @remarks if cpsk_first == NULL or cpsk_second == NULL, then the behavior is undefined. the two stacks must be
 *          initialized, otherwise the behavior is undefined. if the two stacks are not same type, the behavior is
 *          undefined. if cpsk_first == cpsk_second, then return false.
 */
extern bool_t stack_less(const stack_t* cpsk_first, const stack_t* cpsk_second);

/**
 * Test the first stack is less than or equal to the second stack.
 * @param cpsk_first   first stack adaptor.
 * @param cpsk_second  second stack adaptor.
 * @return if the first stack is less than or equal to the second stack, then return true, else return false.
 * @remarks if cpsk_first == NULL or cpsk_second == NULL, then the behavior is undefined. the two stacks must be
 *          initialized, otherwise the behavior is undefined. if the two stacks are not same type, the behavior is
 *          undefined. if cpsk_first == cpsk_second, then return true.
 */
extern bool_t stack_less_equal(const stack_t* cpsk_first, const stack_t* cpsk_second);

/**
 * Test the first stack is greater than the second stack.
 * @param cpsk_first   first stack adaptor.
 * @param cpsk_second  second stack adaptor.
 * @return if the first stack is greater than the second stack, then return true, else return false.
 * @remarks if cpsk_first == NULL or cpsk_second == NULL, then the behavior is undefined. the two stacks must be
 *          initialized, otherwise the behavior is undefined. if the two stacks are not same type, the behavior is
 *          undefined. if cpsk_first == cpsk_second, then return false.
 */
extern bool_t stack_greater(const stack_t* cpsk_first, const stack_t* cpsk_second);

/**
 * Test the first stack is greater than or equal to the second stack.
 * @param cpsk_first   first stack adaptor.
 * @param cpsk_second  second stack adaptor.
 * @return if the first stack is greater than or equal to the second stack, then return true, else return false.
 * @remarks if cpsk_first == NULL or cpsk_second == NULL, then the behavior is undefined. the two stacks must be
 *          initialized, otherwise the behavior is undefined. if the two stacks are not same type, the behavior is
 *          undefined. if cpsk_first == cpsk_second, then return true.
 */
extern bool_t stack_greater_equal(const stack_t* cpsk_first, const stack_t* cpsk_second);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_STACK_H_ */
/** eof **/

