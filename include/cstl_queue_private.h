/*
 *  The private struct and static function of queue.
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

#ifndef _CSTL_QUEUE_PRIVATE_H
#define _CSTL_QUEUE_PRIVATE_H

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

typedef struct _tagpriority_queue
{
    vector_t          _t_vector;
    binary_function_t _t_binary_op;
}priority_queue_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * Create the new queue.
 */
extern queue_t* _create_queue(const char* s_typename);

/*
 * Append a copy of element at the top.
 */
extern void _queue_push(queue_t* pt_queue, ...);
extern void _queue_push_varg(queue_t* pt_queue, va_list val_elemlist);

/*
 * Create the new priority queue.
 */
extern priority_queue_t _create_priority_queue(size_t t_typesize, const char* s_typename);

/*
 * Append a copy of element at the top.
 */
extern void _priority_queue_push(priority_queue_t* pt_pqueue, ...);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_QUEUE_PRIVATE_H */
/** eof **/

