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

#include <cstl/cstl_priority_queue_private.h>
#include <cstl/cstl_priority_queue.h>

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/

void priority_queue_init(priority_queue_t* pt_pqueue)
{
    priority_queue_init_ex(pt_pqueue, NULL);
}

void priority_queue_init_ex(priority_queue_t* pt_pqueue, binary_function_t t_binary_op)
{
    assert(pt_pqueue != NULL);

    vector_init(&pt_pqueue->_t_vector);
    pt_pqueue->_t_binary_op = t_binary_op;
}

void priority_queue_destroy(priority_queue_t* pt_pqueue)
{
    _priority_queue_destroy_auxiliary(pt_pqueue);
    free(pt_pqueue);
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
    random_access_iterator_t t_first, random_access_iterator_t t_last)
{
    priority_queue_init_copy_range_ex(pt_pqueuedest, t_first, t_last, NULL);
}

void priority_queue_init_copy_range_ex(
    priority_queue_t* pt_pqueuedest, random_access_iterator_t t_first,
    random_access_iterator_t t_last, binary_function_t t_binary_op)
{
    assert(pt_pqueuedest != NULL);

    vector_init_copy_range(&pt_pqueuedest->_t_vector, t_first, t_last);
    pt_pqueuedest->_t_binary_op = t_binary_op;

    if(pt_pqueuedest->_t_binary_op == NULL)
    {
        algo_make_heap(
            vector_begin(&pt_pqueuedest->_t_vector), vector_end(&pt_pqueuedest->_t_vector));
    }
    else
    {
        algo_make_heap_if(
            vector_begin(&pt_pqueuedest->_t_vector), vector_end(&pt_pqueuedest->_t_vector),
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

void priority_queue_pop(priority_queue_t* pt_pqueue)
{
    assert(pt_pqueue != NULL);

    if(pt_pqueue->_t_binary_op == NULL)
    {
        algo_pop_heap(
            vector_begin(&pt_pqueue->_t_vector), vector_end(&pt_pqueue->_t_vector));
    }
    else
    {
        algo_pop_heap_if(
            vector_begin(&pt_pqueue->_t_vector), vector_end(&pt_pqueue->_t_vector),
            pt_pqueue->_t_binary_op);
    }
    vector_pop_back(&pt_pqueue->_t_vector);
}

/** local function implementation section **/

/** eof **/

