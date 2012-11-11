/*
 *  The implemention of priority queue.
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
#include <cstl/cvector.h>
#include <cstl/cfunctional.h>
#include <cstl/cutility.h>
#include <cstl/calgorithm.h>
#include <cstl/cqueue.h>

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Initialize an empty priority queue adaptor
 */
void priority_queue_init(priority_queue_t* ppque_pqueue)
{
    priority_queue_init_ex(ppque_pqueue, NULL);
}

/**
 * Initialize an empty priority queue adaptor with user define priority rule.
 */
void priority_queue_init_ex(priority_queue_t* ppque_pqueue, binary_function_t t_binary_op)
{
    assert(ppque_pqueue != NULL);

    vector_init(&ppque_pqueue->_t_vector);
    ppque_pqueue->_t_binary_op = t_binary_op;
}

/**
 * Destroy priority queue adaptor.
 */
void priority_queue_destroy(priority_queue_t* ppque_pqueue)
{
    _priority_queue_destroy_auxiliary(ppque_pqueue);
    free(ppque_pqueue);
}

/**
 * Initialize an priority queue adaptor from an exist priority queue.
 */
void priority_queue_init_copy(priority_queue_t* ppque_dest, const priority_queue_t* cppque_src)
{
    assert(ppque_dest != NULL);
    assert(cppque_src != NULL);

    vector_init_copy(&ppque_dest->_t_vector, &cppque_src->_t_vector);
    ppque_dest->_t_binary_op = cppque_src->_t_binary_op;
}

/**
 * Initialize an priority queue adaptor from an exist range.
 */
void priority_queue_init_copy_range(priority_queue_t* ppque_dest, input_iterator_t it_first, input_iterator_t it_last)
{
    priority_queue_init_copy_range_ex(ppque_dest, it_first, it_last, NULL);
}

/**
 * Initialize an priority queue adaptor from an exist range with user define priority rule.
 */
void priority_queue_init_copy_range_ex(priority_queue_t* ppque_dest, input_iterator_t it_first, input_iterator_t it_last, binary_function_t bfun_op)
{
    assert(ppque_dest != NULL);

    vector_init_copy_range(&ppque_dest->_t_vector, it_first, it_last);
    ppque_dest->_t_binary_op = bfun_op;
    algo_make_heap_if(vector_begin(&ppque_dest->_t_vector), vector_end(&ppque_dest->_t_vector), ppque_dest->_t_binary_op);
}

void priority_queue_assign(
    priority_queue_t* ppque_pqueuedest, const priority_queue_t* cppque_pqueuesrc)
{
    assert(ppque_pqueuedest != NULL && cppque_pqueuesrc != NULL);

    vector_assign(&ppque_pqueuedest->_t_vector, &cppque_pqueuesrc->_t_vector);
    ppque_pqueuedest->_t_binary_op = cppque_pqueuesrc->_t_binary_op;
}

bool_t priority_queue_empty(const priority_queue_t* cppque_pqueue)
{
    assert(cppque_pqueue != NULL);

    return vector_empty(&cppque_pqueue->_t_vector);
}

size_t priority_queue_size(const priority_queue_t* cppque_pqueue)
{
    assert(cppque_pqueue != NULL);

    return vector_size(&cppque_pqueue->_t_vector);
}

void* priority_queue_top(const priority_queue_t* cppque_pqueue)
{
    assert(cppque_pqueue != NULL);

    return vector_front(&cppque_pqueue->_t_vector);
}

void priority_queue_pop(priority_queue_t* ppque_pqueue)
{
    assert(ppque_pqueue != NULL);

    if(ppque_pqueue->_t_binary_op == NULL)
    {
        algo_pop_heap(
            vector_begin(&ppque_pqueue->_t_vector), vector_end(&ppque_pqueue->_t_vector));
    }
    else
    {
        algo_pop_heap_if(
            vector_begin(&ppque_pqueue->_t_vector), vector_end(&ppque_pqueue->_t_vector),
            ppque_pqueue->_t_binary_op);
    }
    vector_pop_back(&ppque_pqueue->_t_vector);
}

/** local function implementation section **/

/** eof **/

