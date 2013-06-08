/*
 *  The private struct and private function of priority queue.
 *  Copyright (C)  2008 - 2013  Wangbo
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
#ifndef _CSTL_PRIORITY_QUEUE_PRIVATE_H_
#define _CSTL_PRIORITY_QUEUE_PRIVATE_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
typedef struct _tagpriority_queue
{
    vector_t          _vec_base;
    bfun_t            _bfun_priority;
}priority_queue_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Create priority queue adaptor.
 * @param s_typename    type name.
 * @return priority queue adaptor pointer, if create queue successfully, else return NULL.
 * @remarks if s_typename == NULL, the behavior is undefined. s_typename must be c builtin type, libcstl builtin type or
 *          user defined type, otherwise creation will be failure.
 */
extern priority_queue_t* _create_priority_queue(const char* s_typename);

/**
 * Create priority queue adaptor auxiliary function.
 * @param ppque_pqueue      priority queue adaptor.
 * @param s_typename        type name.
 * @return true if create priority queue adaptor successfully, otherwise return false.
 * @remarks if ppque_pqueue == NULL or s_typename == NULL, the behavior is undefined. s_typename must be c builtin type,
 *          libcstl builtin type or user defined type, otherwise creation will be failure.
 */
extern bool_t _create_priority_queue_auxiliary(priority_queue_t* ppque_pqueue, const char* s_typename);

/**
 * Destroy priority queue adaptor auxiliary function.
 * @param ppque_pqueue   priority queue adaptor.
 * @return void.
 * @remarks if ppque_pqueue == NULL, then the behavior is undefined. priority queue adaptor must be initialized or created by
 *          create_queue, otherwise the behavior is undefined.
 */
extern void _priority_queue_destroy_auxiliary(priority_queue_t* ppque_pqueue);

/**
 * Add specificed element at the back of priority queue. 
 * @param ppque_pqueue    priority queue adaptor.
 * @param ...             specificed element.
 * @return void.
 * @remarks if ppque_pqueue == NULL or priority queue is uninitialized, then the behavior is undefined. the type of specificed
 *          element and priority queue element type must be same, otherwise the behavior is undefined. the first specificed is
 *          in use, others are not in use.
 */
extern void _priority_queue_push(priority_queue_t* ppque_pqueue, ...);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_PRIORITY_QUEUE_PRIVATE_H_ */
/** eof **/

