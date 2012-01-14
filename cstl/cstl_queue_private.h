/*
 *  The private struct and private function of queue.
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

#ifndef _CSTL_QUEUE_PRIVATE_H_
#define _CSTL_QUEUE_PRIVATE_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
/* queue struct default use deque_t */
typedef struct _tagqueue
{
#ifdef CSTL_QUEUE_LIST_SEQUENCE
    list_t  _t_sequence;
#else
    deque_t _t_sequence;
#endif
}queue_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Create queue adaptor.
 * @param s_typename    type name.
 * @return queue adaptor pointer, if create queue successfully, else return NULL.
 * @remarks if s_typename == NULL, the behavior is undefined. s_typename must be c builtin type, libcstl builtin type or
 *          user defined type, otherwise creation will be failure.
 */
extern queue_t* _create_queue(const char* s_typename);

/**
 * Create queue adaptor auxiliary function.
 * @param pque_queue    queue adaptor.
 * @param s_typename    type name.
 * @return true if create queue adaptor successfully, otherwise return false.
 * @remarks if pque_queue == NULL or s_typename == NULL, the behavior is undefined. s_typename must be c builtin type,
 *          libcstl builtin type or user defined type, otherwise creation will be failure.
 */
extern bool_t _create_queue_auxiliary(queue_t* pque_queue, const char* s_typename);

/**
 * Destroy queue adaptor auxiliary function.
 * @param pque_queue   queue adaptor.
 * @return void.
 * @remarks if pque_queue == NULL, then the behavior is undefined. queue adaptor must be initialized or created by
 *          create_queue, otherwise the behavior is undefined.
 */
extern void _queue_destroy_auxiliary(queue_t* pque_queue);

/**
 * Add specificed element at the back of queue. 
 * @param pque_queue      queue adaptor.
 * @param ...             specificed element.
 * @return void.
 * @remarks if pque_queue == NULL or queue is uninitialized, then the behavior is undefined. the type of specificed
 *          element and queue element type must be same, otherwise the behavior is undefined. the first specificed is
 *          in use, others are not in use.
 */
extern void _queue_push(queue_t* pque_pqueue, ...);

/**
 * Add specificed element from variable argument queue at the back of queue adaptor. 
 * @param pque_queue      queue adaptor.
 * @param val_elemlist    variable argumnet list of specificed element.
 * @return void.
 * @remarks if pque_queue == NULL or queue is uninitialized, then the behavior is undefined. the type of specificed
 *          element and queue element type must be same, otherwise the behavior is undefined. the first specificed is
 *          in use, others are not in use.
 */
extern void _queue_push_varg(queue_t* pt_queue, va_list val_elemlist);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_QUEUE_PRIVATE_H_ */
/** eof **/

