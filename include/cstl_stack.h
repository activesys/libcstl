/*
 *  The interface of stack.
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
 *  Author Email: activesys.wb@gmail.com
 *                activesys@sina.com.cn
 */

#ifndef _CSTL_STACK_H
#define _CSTL_STACK_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/* create new stack with specific type */
#define create_stack(type)\
    _create_stack(sizeof(type), #type) 
/* push */
#define stack_push(pt_stack, elem)\
    _stack_push((pt_stack), (elem))

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: stack_init
 *        Parameters: in) pt_stack: stack_t*
 *           Returns: void
 *       Description: initialize the stack.
 *
 * ----------------------------------------------------------------------------
 */
extern void stack_init(stack_t* pt_stack);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: stack_destroy
 *        Parameters: in) pt_stack: stack_t*
 *           Returns: void
 *       Description: destroy the stack.
 *
 * ----------------------------------------------------------------------------
 */
extern void stack_destroy(stack_t* pt_stack);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: stack_init_copy
 *        Parameters: in) pt_stackdest: stack_t*
 *                          the dest stack.
 *                    in) cpt_stacksrc: const stack_t*
 *                          the source stack.
 *           Returns: void
 *       Description: the copy constructor.
 *
 * ----------------------------------------------------------------------------
 */
extern void stack_init_copy(stack_t* pt_stackdest, const stack_t* cpt_stacksrc);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: stack_assign
 *        Parameters: in) pt_stackdest: stack_t*
 *                          the dest stack.
 *                    in) cpt_stacksrc: const stack_t*
 *                          the source stack.
 *           Returns: void
 *       Description: copy the stack.
 *
 * ----------------------------------------------------------------------------
 */
extern void stack_assign(stack_t* pt_stackdest, const stack_t* cpt_stacksrc);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: stack_empty
 *        Parameters: in) cpt_stack: const stack_t*
 *                          the dest stack.
 *           Returns: bool_t
 *       Description: if the stack is empty.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t stack_empty(const stack_t* cpt_stack);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: stack_size
 *        Parameters: in) cpt_stack: const stack_t*
 *                          the dest stack.
 *           Returns: size_t
 *       Description: get the stack size.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t stack_size(const stack_t* cpt_stack);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: stack_top
 *        Parameters: in) cpt_stack: const stack_t*
 *                          the stack.
 *           Returns: void*
 *       Description: return the top element.
 *
 * ----------------------------------------------------------------------------
 */
extern void* stack_top(const stack_t* cpt_stack);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: stack_pop
 *        Parameters: in) pt_stack: stack_t*
 *                          the stack.
 *           Returns: void
 *       Description: remove the top element and does not return it.
 *
 * ----------------------------------------------------------------------------
 */
extern void stack_pop(stack_t* pt_stack);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: stack_equal
 *        Parameters: in) cpt_stackfirst: const stack_t*
 *                          the first stack.
 *                    in) cpt_stacksecond: const stack_t*
 *                          the second stack.
 *           Returns: bool_t
 *       Description: return whether first stack equal to second stack.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t stack_equal(
    const stack_t* cpt_stackfirst, const stack_t* cpt_stacksecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: stack_not_equal
 *        Parameters: in) cpt_stackfirst: const stack_t*
 *                          the first stack.
 *                    in) cpt_stacksecond: const stack_t*
 *                          the second stack.
 *           Returns: bool_t
 *       Description: return whether first stack not equal to second stack.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t stack_not_equal(
    const stack_t* cpt_stackfirst, const stack_t* cpt_stacksecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: stack_less
 *        Parameters: in) cpt_stackfirst: const stack_t*
 *                          the first stack.
 *                    in) cpt_stacksecond: const stack_t*
 *                          the second stack.
 *           Returns: bool_t
 *       Description: return whether first stack less then second stack.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t stack_less(
    const stack_t* cpt_stackfirst, const stack_t* cpt_stacksecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: stack_great
 *        Parameters: in) cpt_stackfirst: const stack_t*
 *                          the first stack.
 *                    in) cpt_stacksecond: const stack_t*
 *                          the second stack.
 *           Returns: bool_t
 *       Description: return whether first stack greater then second stack.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t stack_great(
    const stack_t* cpt_stackfirst, const stack_t* cpt_stacksecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: stack_less_equal
 *        Parameters: in) cpt_stackfirst: const stack_t*
 *                          the first stack.
 *                    in) cpt_stacksecond: const stack_t*
 *                          the second stack.
 *           Returns: bool_t
 *       Description: return whether first stack less then or equal to the 
 *                    second stack.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t stack_less_equal(
    const stack_t* cpt_stackfirst, const stack_t* cpt_stacksecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: stack_great_equal
 *        Parameters: in) cpt_stackfirst: const stack_t*
 *                          the first stack.
 *                    in) cpt_stacksecond: const stack_t*
 *                          the second stack.
 *           Returns: bool_t
 *       Description: return whether first stack greater then or equal to the
 *                    second stack.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t stack_great_equal(
    const stack_t* cpt_stackfirst, const stack_t* cpt_stacksecond);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_STACK_H */
/** eof **/

