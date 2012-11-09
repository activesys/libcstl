/*
 *  The implemention of queue.
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
 * Initialize an empty queue adaptor
 */
void queue_init(queue_t* pque_queue)
{
    assert(pque_queue != NULL);

#ifdef CSTL_QUEUE_LIST_SEQUENCE
    list_init(&pque_queue->_t_sequence);
#else
    deque_init(&pque_queue->_t_sequence);
#endif
}

/**
 * Initialize queue adaptor with exist queue adaptor.
 */
void queue_init_copy(queue_t* pque_dest, const queue_t* cpque_src)
{
    assert(pque_dest != NULL);
    assert(cpque_src != NULL);

#ifdef CSTL_QUEUE_LIST_SEQUENCE
    list_init_copy(&pque_dest->_t_sequence, &cpque_src->_t_sequence);
#else
    deque_init_copy(&pque_dest->_t_sequence, &cpque_src->_t_sequence);
#endif
}

/**
 * Destroy queue adaptor.
 */
void queue_destroy(queue_t* pque_queue)
{
    assert(pque_queue != NULL);

    _queue_destroy_auxiliary(pque_queue);
    free(pque_queue);
}

/**
 * Assign queue element with an exist queue adaptor.
 */
void queue_assign(queue_t* pque_dest, const queue_t* cpque_src)
{
    assert(pque_dest != NULL);
    assert(cpque_src != NULL);

#ifdef CSTL_QUEUE_LIST_SEQUENCE
    list_assign(&pque_dest->_t_sequence, &cpque_src->_t_sequence);
#else
    deque_assign(&pque_dest->_t_sequence, &cpque_src->_t_sequence);
#endif
}

/**
 * Tests if a queue is empty.
 */
bool_t queue_empty(const queue_t* cpque_queue)
{
    assert(cpque_queue != NULL);

#ifdef CSTL_QUEUE_LIST_SEQUENCE
    return list_empty(&cpque_queue->_t_sequence);
#else
    return deque_empty(&cpque_queue->_t_sequence);
#endif
}

/**
 * Return the number of elements in a queue.
 */
size_t queue_size(const queue_t* cpque_queue)
{
    assert(cpque_queue != NULL);

#ifdef CSTL_QUEUE_LIST_SEQUENCE
    return list_size(&cpque_queue->_t_sequence);
#else
    return deque_size(&cpque_queue->_t_sequence);
#endif
}

/**
 * Access queue front data.
 */
void* queue_front(const queue_t* cpque_queue)
{
    assert(cpque_queue != NULL);

#ifdef CSTL_QUEUE_LIST_SEQUENCE
    return list_front(&cpque_queue->_t_sequence);
#else
    return deque_front(&cpque_queue->_t_sequence);
#endif
}

/**
 * Access queue last data.
 */
void* queue_back(const queue_t* cpque_queue)
{
    assert(cpque_queue != NULL);

#ifdef CSTL_QUEUE_LIST_SEQUENCE
    return list_back(&cpque_queue->_t_sequence);
#else
    return deque_back(&cpque_queue->_t_sequence);
#endif
}

/**
 * Delete the element at the begin of queue.
 */
void queue_pop(queue_t* pque_queue)
{
    assert(pque_queue != NULL);

#ifdef CSTL_QUEUE_LIST_SEQUENCE
    list_pop_front(&pque_queue->_t_sequence);
#else
    deque_pop_front(&pque_queue->_t_sequence);
#endif
}

/**
 * Tests if the two queues are equal.
 */
bool_t queue_equal(const queue_t* cpque_first, const queue_t* cpque_second)
{
    assert(cpque_first != NULL);
    assert(cpque_second != NULL);

#ifdef CSTL_QUEUE_LIST_SEQUENCE
    return list_equal(&cpque_first->_t_sequence, &cpque_second->_t_sequence);
#else
    return deque_equal(&cpque_first->_t_sequence, &cpque_second->_t_sequence);
#endif
}

/**
 * Test the two queues are unequal.
 */
bool_t queue_not_equal(const queue_t* cpque_first, const queue_t* cpque_second)
{
    assert(cpque_first != NULL);
    assert(cpque_second != NULL);

#ifdef CSTL_QUEUE_LIST_SEQUENCE
    return list_not_equal(&cpque_first->_t_sequence, &cpque_second->_t_sequence);
#else
    return deque_not_equal(&cpque_first->_t_sequence, &cpque_second->_t_sequence);
#endif
}

/**
 * Test the first queue is less than the second queue.
 */
bool_t queue_less(const queue_t* cpque_first, const queue_t* cpque_second)
{
    assert(cpque_first != NULL);
    assert(cpque_second != NULL);

#ifdef CSTL_QUEUE_LIST_SEQUENCE
    return list_less(&cpque_first->_t_sequence, &cpque_second->_t_sequence);
#else
    return deque_less(&cpque_first->_t_sequence, &cpque_second->_t_sequence);
#endif
}

/**
 * Test the first queue is less than or equal to the second queue.
 */
bool_t queue_less_equal(const queue_t* cpque_first, const queue_t* cpque_second)
{
    assert(cpque_first != NULL);
    assert(cpque_second != NULL);

#ifdef CSTL_QUEUE_LIST_SEQUENCE
    return list_less_equal(&cpque_first->_t_sequence, &cpque_second->_t_sequence);
#else
    return deque_less_equal(&cpque_first->_t_sequence, &cpque_second->_t_sequence);
#endif
}

/**
 * Test the first queue is greater than the second queue.
 */
bool_t queue_greater(const queue_t* cpque_first, const queue_t* cpque_second)
{
    assert(cpque_first != NULL);
    assert(cpque_second != NULL);

#ifdef CSTL_QUEUE_LIST_SEQUENCE
    return list_greater(&cpque_first->_t_sequence, &cpque_second->_t_sequence);
#else
    return deque_greater(&cpque_first->_t_sequence, &cpque_second->_t_sequence);
#endif
}

/**
 * Test the first queue is greater than or equal to the second queue.
 */
bool_t queue_greater_equal(const queue_t* cpque_first, const queue_t* cpque_second)
{
    assert(cpque_first != NULL);
    assert(cpque_second != NULL);

#ifdef CSTL_QUEUE_LIST_SEQUENCE
    return list_greater_equal(&cpque_first->_t_sequence, &cpque_second->_t_sequence);
#else
    return deque_greater_equal(&cpque_first->_t_sequence, &cpque_second->_t_sequence);
#endif
}

/** local function implementation section **/

/** eof **/

