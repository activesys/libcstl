/*
 *  The implemention of queue private functions.
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
#include <cstl/cqueue.h>

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Create queue adaptor.
 */
queue_t* _create_queue(const char* s_typename)
{
    queue_t* pque_new = NULL;

    assert(s_typename != NULL);

    /* allocate memory for queue */
    if ((pque_new = (queue_t*)malloc(sizeof(queue_t))) == NULL) {
        return NULL;
    }

    if (!_create_queue_auxiliary(pque_new, s_typename)) {
        free(pque_new);
        return NULL;
    }

    return pque_new;
}

/**
 * Create queue adaptor auxiliary function.
 */
bool_t _create_queue_auxiliary(queue_t* pque_queue, const char* s_typename)
{
    assert(pque_queue != NULL);
    assert(s_typename != NULL);

#ifdef CSTL_QUEUE_LIST_SEQUENCE
    return _create_list_auxiliary(&pque_queue->_t_sequence, s_typename);
#else
    return _create_deque_auxiliary(&pque_queue->_t_sequence, s_typename);
#endif
}

/**
 * Destroy queue adaptor auxiliary function.
 */
void _queue_destroy_auxiliary(queue_t* pque_queue)
{
    assert(pque_queue != NULL);

#ifdef CSTL_QUEUE_LIST_SEQUENCE
    _list_destroy_auxiliary(&pque_queue->_t_sequence);
#else
    _deque_destroy_auxiliary(&pque_queue->_t_sequence);
#endif
}

/**
 * Add specificed element at the back of queue. 
 */
void _queue_push(queue_t* pque_queue, ...)
{
    va_list val_elemlist;

    assert(pque_queue != NULL);

    va_start(val_elemlist, pque_queue);
    _queue_push_varg(pque_queue, val_elemlist);
    va_end(val_elemlist);
}

/**
 * Add specificed element from variable argument queue at the back of queue adaptor. 
 */
void _queue_push_varg(queue_t* pque_queue, va_list val_elemlist)
{
    assert(pque_queue != NULL);

#ifdef CSTL_QUEUE_LIST_SEQUENCE
    _list_push_back_varg(&pque_queue->_t_sequence, val_elemlist);
#else
    _deque_push_back_varg(&pque_queue->_t_sequence, val_elemlist);
#endif
}

/** local function implementation section **/

/** eof **/

