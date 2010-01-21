/*
 *  The interface of stack.
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

#ifndef _CSTL_STACK_H
#define _CSTL_STACK_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/* create new stack with specific type */
#define create_stack(...) _create_stack(#__VA_ARGS__) 
/* push */
#define stack_push(pt_stack, elem)\
    _stack_push((pt_stack), (elem))

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * Initialization and destroy operation functions.
 */
extern void stack_init(stack_t* pt_stack);
extern void stack_destroy(stack_t* pt_stack);
extern void stack_init_copy(stack_t* pt_stackdest, const stack_t* cpt_stacksrc);

/*
 * Assign operator function.
 */
extern void stack_assign(stack_t* pt_stackdest, const stack_t* cpt_stacksrc);

/*
 * Stack size operation functions.
 */
extern bool_t stack_empty(const stack_t* cpt_stack);
extern size_t stack_size(const stack_t* cpt_stack);

/*
 * Element access function.
 */
extern void* stack_top(const stack_t* cpt_stack);
extern void stack_pop(stack_t* pt_stack);

/*
 * Relationship operation functions.
 */
extern bool_t stack_equal(
    const stack_t* cpt_stackfirst, const stack_t* cpt_stacksecond);
extern bool_t stack_not_equal(
    const stack_t* cpt_stackfirst, const stack_t* cpt_stacksecond);
extern bool_t stack_less(
    const stack_t* cpt_stackfirst, const stack_t* cpt_stacksecond);
extern bool_t stack_great(
    const stack_t* cpt_stackfirst, const stack_t* cpt_stacksecond);
extern bool_t stack_less_equal(
    const stack_t* cpt_stackfirst, const stack_t* cpt_stacksecond);
extern bool_t stack_great_equal(
    const stack_t* cpt_stackfirst, const stack_t* cpt_stacksecond);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_STACK_H */
/** eof **/

