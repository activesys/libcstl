/*
 *  The implemention of queue.
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

/** include section **/
#include "cdeque.h"
#include "clist.h"
#include "cvector.h"
#include "cfunctional.h"
#include "cutility.h"
#include "calgorithm.h"

#include "cstl_queue_private.h"
#include "cstl_queue.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/* queue private function */
queue_t _create_queue(size_t t_typesize, const char* sz_typename)
{
    queue_t t_newqueue;

#ifdef CSTL_QUEUE_LIST_SEQUENCE
    *_GET_QUEUE_LIST_SEQUENCE(&t_newqueue) = 
        _create_list(t_typesize, sz_typename);
#else
    *_GET_QUEUE_DEQUE_SEQUENCE(&t_newqueue) = 
        _create_deque(t_typesize, sz_typename);
#endif

    return t_newqueue;
}

/* queue function */
void queue_init(queue_t* pt_queue)
{
    assert(pt_queue != NULL);

#ifdef CSTL_QUEUE_LIST_SEQUENCE
    list_init(_GET_QUEUE_LIST_SEQUENCE(pt_queue));
#else
    deque_init(_GET_QUEUE_DEQUE_SEQUENCE(pt_queue));
#endif
}

void queue_destroy(queue_t* pt_queue)
{
    assert(pt_queue != NULL);

#ifdef CSTL_QUEUE_LIST_SEQUENCE
    list_destroy(_GET_QUEUE_LIST_SEQUENCE(pt_queue));
#else
    deque_destroy(_GET_QUEUE_DEQUE_SEQUENCE(pt_queue));
#endif
}

void queue_init_copy(queue_t* pt_queuedest, const queue_t* cpt_queuesrc)
{
    assert(pt_queuedest != NULL && cpt_queuesrc != NULL);

#ifdef CSTL_QUEUE_LIST_SEQUENCE
    list_init_copy(
        _GET_QUEUE_LIST_SEQUENCE(pt_queuedest),
        _GET_QUEUE_LIST_SEQUENCE(cpt_queuesrc));
#else
    deque_init_copy(
        _GET_QUEUE_DEQUE_SEQUENCE(pt_queuedest),
        _GET_QUEUE_DEQUE_SEQUENCE(cpt_queuesrc));
#endif
}

void queue_assign(queue_t* pt_queuedest, const queue_t* cpt_queuesrc)
{
    assert(pt_queuedest != NULL && cpt_queuesrc != NULL);

#ifdef CSTL_QUEUE_LIST_SEQUENCE
    list_assign(
        _GET_QUEUE_LIST_SEQUENCE(pt_queuedest),
        _GET_QUEUE_LIST_SEQUENCE(cpt_queuesrc));
#else
    deque_assign(
        _GET_QUEUE_DEQUE_SEQUENCE(pt_queuedest),
        _GET_QUEUE_DEQUE_SEQUENCE(cpt_queuesrc));
#endif
}

bool_t queue_empty(const queue_t* cpt_queue)
{
    assert(cpt_queue != NULL);

#ifdef CSTL_QUEUE_LIST_SEQUENCE
    return list_empty(_GET_QUEUE_LIST_SEQUENCE(cpt_queue));
#else
    return deque_empty(_GET_QUEUE_DEQUE_SEQUENCE(cpt_queue));
#endif
}

size_t queue_size(const queue_t* cpt_queue)
{
    assert(cpt_queue != NULL);

#ifdef CSTL_QUEUE_LIST_SEQUENCE
    return list_size(_GET_QUEUE_LIST_SEQUENCE(cpt_queue));
#else
    return deque_size(_GET_QUEUE_DEQUE_SEQUENCE(cpt_queue));
#endif
}

void* queue_front(const queue_t* cpt_queue)
{
    assert(cpt_queue != NULL);

#ifdef CSTL_QUEUE_LIST_SEQUENCE
    return list_front(_GET_QUEUE_LIST_SEQUENCE(cpt_queue));
#else
    return deque_front(_GET_QUEUE_DEQUE_SEQUENCE(cpt_queue));
#endif
}

void* queue_back(const queue_t* cpt_queue)
{
    assert(cpt_queue != NULL);

#ifdef CSTL_QUEUE_LIST_SEQUENCE
    return list_back(_GET_QUEUE_LIST_SEQUENCE(cpt_queue));
#else
    return deque_back(_GET_QUEUE_DEQUE_SEQUENCE(cpt_queue));
#endif
}

void _queue_push(queue_t* pt_queue, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, pt_queue);
    _queue_push_varg(pt_queue, val_elemlist);
}

void _queue_push_varg(queue_t* pt_queue, va_list val_elemlist)
{
    assert(pt_queue != NULL);

#ifdef CSTL_QUEUE_LIST_SEQUENCE
    _list_push_back_varg(_GET_QUEUE_LIST_SEQUENCE(pt_queue), val_elemlist);
#else
    _deque_push_back_varg(_GET_QUEUE_DEQUE_SEQUENCE(pt_queue), val_elemlist);
#endif
}

void queue_pop(queue_t* pt_queue)
{
    assert(pt_queue != NULL);

#ifdef CSTL_QUEUE_LIST_SEQUENCE
    list_pop_front(_GET_QUEUE_LIST_SEQUENCE(pt_queue));
#else
    deque_pop_front(_GET_QUEUE_DEQUE_SEQUENCE(pt_queue));
#endif
}

bool_t queue_equal(
    const queue_t* cpt_queuefirst, const queue_t* cpt_queuesecond)
{
    assert(cpt_queuefirst != NULL && cpt_queuesecond != NULL);

#ifdef CSTL_QUEUE_LIST_SEQUENCE
    return list_equal(
        _GET_QUEUE_LIST_SEQUENCE(cpt_queuefirst),
        _GET_QUEUE_LIST_SEQUENCE(cpt_queuesecond));
#else
    return deque_equal(
        _GET_QUEUE_DEQUE_SEQUENCE(cpt_queuefirst),
        _GET_QUEUE_DEQUE_SEQUENCE(cpt_queuesecond));
#endif
}

bool_t queue_not_equal(
    const queue_t* cpt_queuefirst, const queue_t* cpt_queuesecond)
{
    assert(cpt_queuefirst != NULL && cpt_queuesecond != NULL);

#ifdef CSTL_QUEUE_LIST_SEQUENCE
    return list_not_equal(
        _GET_QUEUE_LIST_SEQUENCE(cpt_queuefirst),
        _GET_QUEUE_LIST_SEQUENCE(cpt_queuesecond));
#else
    return deque_not_equal(
        _GET_QUEUE_DEQUE_SEQUENCE(cpt_queuefirst),
        _GET_QUEUE_DEQUE_SEQUENCE(cpt_queuesecond));
#endif
}

bool_t queue_less(
    const queue_t* cpt_queuefirst, const queue_t* cpt_queuesecond)
{
    assert(cpt_queuefirst != NULL && cpt_queuesecond != NULL);

#ifdef CSTL_QUEUE_LIST_SEQUENCE
    return list_less(
        _GET_QUEUE_LIST_SEQUENCE(cpt_queuefirst),
        _GET_QUEUE_LIST_SEQUENCE(cpt_queuesecond));
#else
    return deque_less(
        _GET_QUEUE_DEQUE_SEQUENCE(cpt_queuefirst),
        _GET_QUEUE_DEQUE_SEQUENCE(cpt_queuesecond));
#endif
}

bool_t queue_great(
    const queue_t* cpt_queuefirst, const queue_t* cpt_queuesecond)
{
    assert(cpt_queuefirst != NULL && cpt_queuesecond != NULL);

#ifdef CSTL_QUEUE_LIST_SEQUENCE
    return list_great(
        _GET_QUEUE_LIST_SEQUENCE(cpt_queuefirst),
        _GET_QUEUE_LIST_SEQUENCE(cpt_queuesecond));
#else
    return deque_great(
        _GET_QUEUE_DEQUE_SEQUENCE(cpt_queuefirst),
        _GET_QUEUE_DEQUE_SEQUENCE(cpt_queuesecond));
#endif
}

bool_t queue_less_equal(
    const queue_t* cpt_queuefirst, const queue_t* cpt_queuesecond)
{
    assert(cpt_queuefirst != NULL && cpt_queuesecond != NULL);

#ifdef CSTL_QUEUE_LIST_SEQUENCE
    return list_less_equal(
        _GET_QUEUE_LIST_SEQUENCE(cpt_queuefirst),
        _GET_QUEUE_LIST_SEQUENCE(cpt_queuesecond));
#else
    return deque_less_equal(
        _GET_QUEUE_DEQUE_SEQUENCE(cpt_queuefirst),
        _GET_QUEUE_DEQUE_SEQUENCE(cpt_queuesecond));
#endif
}

bool_t queue_great_equal(
    const queue_t* cpt_queuefirst, const queue_t* cpt_queuesecond)
{
    assert(cpt_queuefirst != NULL && cpt_queuesecond != NULL);

#ifdef CSTL_QUEUE_LIST_SEQUENCE
    return list_great_equal(
        _GET_QUEUE_LIST_SEQUENCE(cpt_queuefirst),
        _GET_QUEUE_LIST_SEQUENCE(cpt_queuesecond));
#else
    return deque_great_equal(
        _GET_QUEUE_DEQUE_SEQUENCE(cpt_queuefirst),
        _GET_QUEUE_DEQUE_SEQUENCE(cpt_queuesecond));
#endif
}

/* priority queue function */
/* create new priority queue */
priority_queue_t _create_priority_queue(
    size_t t_typesize, const char* s_typename)
{
    priority_queue_t t_newpqueue;

    t_newpqueue._t_vector = _create_vector(t_typesize, s_typename);
    t_newpqueue._t_binary_op = NULL;

    return t_newpqueue;
}

void priority_queue_init(priority_queue_t* pt_pqueue)
{
    priority_queue_init_op(pt_pqueue, NULL);
}

void priority_queue_init_op(
    priority_queue_t* pt_pqueue, binary_function_t t_binary_op)
{
    assert(pt_pqueue != NULL);

    vector_init(&pt_pqueue->_t_vector);
    pt_pqueue->_t_binary_op = t_binary_op;
}

void priority_queue_destroy(priority_queue_t* pt_pqueue)
{
    assert(pt_pqueue != NULL);

    vector_destroy(&pt_pqueue->_t_vector);
    pt_pqueue->_t_binary_op = NULL;
}

void priority_queue_init_copy(
    priority_queue_t* pt_pqueuedest, const priority_queue_t* cpt_pqueuesrc)
{
    assert(pt_pqueuedest != NULL && cpt_pqueuesrc != NULL);

    vector_init_copy(&pt_pqueuedest->_t_vector, &cpt_pqueuesrc->_t_vector);
    pt_pqueuedest->_t_binary_op = cpt_pqueuesrc->_t_binary_op;
}

void priority_queue_init_copy_range(
    priority_queue_t* pt_pqueuedest,
    random_access_iterator_t t_first,
    random_access_iterator_t t_last)
{
    priority_queue_init_copy_range_op(pt_pqueuedest, t_first, t_last, NULL);
}

void priority_queue_init_copy_range_op(
    priority_queue_t* pt_pqueuedest,
    random_access_iterator_t t_first,
    random_access_iterator_t t_last,
    binary_function_t t_binary_op)
{
    assert(pt_pqueuedest != NULL);

    vector_init_copy_range(&pt_pqueuedest->_t_vector, t_first, t_last);
    pt_pqueuedest->_t_binary_op = t_binary_op;

    if(pt_pqueuedest->_t_binary_op == NULL)
    {
        algo_make_heap(
            vector_begin(&pt_pqueuedest->_t_vector),
            vector_end(&pt_pqueuedest->_t_vector));
    }
    else
    {
        algo_make_heap_if(
            vector_begin(&pt_pqueuedest->_t_vector),
            vector_end(&pt_pqueuedest->_t_vector),
            pt_pqueuedest->_t_binary_op);
    }
}

void priority_queue_assign(
    priority_queue_t* pt_pqueuedest, const priority_queue_t* cpt_pqueuesrc)
{
    assert(pt_pqueuedest != NULL && cpt_pqueuesrc != NULL);

    vector_assign(&pt_pqueuedest->_t_vector, &cpt_pqueuesrc->_t_vector);
    pt_pqueuedest->_t_binary_op = cpt_pqueuesrc->_t_binary_op;
}

bool_t priority_queue_empty(const priority_queue_t* cpt_pqueue)
{
    assert(cpt_pqueue != NULL);

    return vector_empty(&cpt_pqueue->_t_vector);
}

size_t priority_queue_size(const priority_queue_t* cpt_pqueue)
{
    assert(cpt_pqueue != NULL);

    return vector_size(&cpt_pqueue->_t_vector);
}

void* priority_queue_top(const priority_queue_t* cpt_pqueue)
{
    assert(cpt_pqueue != NULL);

    return vector_front(&cpt_pqueue->_t_vector);
}

void _priority_queue_push(priority_queue_t* pt_pqueue, ...)
{
    va_list val_elemlist;

    assert(pt_pqueue != NULL);

    va_start(val_elemlist, pt_pqueue);
    _vector_push_back_varg(&pt_pqueue->_t_vector, val_elemlist);

    if(pt_pqueue->_t_binary_op == NULL)
    {
        algo_push_heap(
            vector_begin(&pt_pqueue->_t_vector),
            vector_end(&pt_pqueue->_t_vector));
    }
    else
    {
        algo_push_heap_if(
            vector_begin(&pt_pqueue->_t_vector),
            vector_end(&pt_pqueue->_t_vector),
            pt_pqueue->_t_binary_op);
    }
}

void priority_queue_pop(priority_queue_t* pt_pqueue)
{
    assert(pt_pqueue != NULL);

    if(pt_pqueue->_t_binary_op == NULL)
    {
        algo_pop_heap(
            vector_begin(&pt_pqueue->_t_vector),
            vector_end(&pt_pqueue->_t_vector));
    }
    else
    {
        algo_pop_heap_if(
            vector_begin(&pt_pqueue->_t_vector),
            vector_end(&pt_pqueue->_t_vector),
            pt_pqueue->_t_binary_op);
    }
    vector_pop_back(&pt_pqueue->_t_vector);
}

/** local function implementation section **/

/** eof **/

