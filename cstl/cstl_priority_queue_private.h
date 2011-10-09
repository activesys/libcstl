/*
 *  The private struct and private function of priority queue.
 *  Copyright (C)  2008,2009,2010,2011  Wangbo
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
    vector_t          _t_vector;
    binary_function_t _t_binary_op;
}priority_queue_t;

/** exported global variable declaration section **/

/** exported function prototype section **/

/*
 * Create the new priority queue.
 */
extern priority_queue_t* _create_priority_queue(const char* s_typename);
extern bool_t _create_priority_queue_auxiliary(
    priority_queue_t* pt_pqueue, const char* s_typename);
extern void _priority_queue_destroy_auxiliary(priority_queue_t* pt_queue);

/*
 * Append a copy of element at the top.
 */
extern void _priority_queue_push(priority_queue_t* pt_pqueue, ...);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_PRIORITY_QUEUE_PRIVATE_H_ */
/** eof **/

