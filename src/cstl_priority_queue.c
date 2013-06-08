/*
 *  The implemention of priority queue.
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
void priority_queue_init_ex(priority_queue_t* ppque_pqueue, bfun_t bfun_op)
{
    assert(ppque_pqueue != NULL);

    vector_init(&ppque_pqueue->_vec_base);
    ppque_pqueue->_bfun_priority = bfun_op;
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

    vector_init_copy(&ppque_dest->_vec_base, &cppque_src->_vec_base);
    ppque_dest->_bfun_priority = cppque_src->_bfun_priority;
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
void priority_queue_init_copy_range_ex(priority_queue_t* ppque_dest, input_iterator_t it_first, input_iterator_t it_last, bfun_t bfun_op)
{
    assert(ppque_dest != NULL);

    vector_init_copy_range(&ppque_dest->_vec_base, it_first, it_last);
    ppque_dest->_bfun_priority = bfun_op;
    algo_make_heap_if(vector_begin(&ppque_dest->_vec_base), vector_end(&ppque_dest->_vec_base), ppque_dest->_bfun_priority);
}

/**
 * Initialize an priority queue adaptor from an exist array.
 */
void priority_queue_init_copy_array(priority_queue_t* ppque_dest, const void* cpv_array, size_t t_count)
{
    priority_queue_init_copy_array_ex(ppque_dest, cpv_array, t_count, NULL);
}

/**
 * Initialize an priority queue adaptor from an exist array with user define priority rule.
 */
void priority_queue_init_copy_array_ex(priority_queue_t* ppque_dest, const void* cpv_array, size_t t_count, bfun_t bfun_op)
{
    assert(ppque_dest != NULL);
    assert(cpv_array != NULL);

    vector_init_copy_array(&ppque_dest->_vec_base, cpv_array, t_count);
    ppque_dest->_bfun_priority = bfun_op;
    algo_make_heap_if(vector_begin(&ppque_dest->_vec_base), vector_end(&ppque_dest->_vec_base), ppque_dest->_bfun_priority);
}

/**
 * Assign priority queue adaptor from exist.
 */
void priority_queue_assign(priority_queue_t* ppque_dest, const priority_queue_t* cppque_src)
{
    assert(ppque_dest != NULL);
    assert(cppque_src != NULL);
    assert(ppque_dest->_bfun_priority == cppque_src->_bfun_priority);

    vector_assign(&ppque_dest->_vec_base, &cppque_src->_vec_base);
}

/**
 * Tests if a priority_queue is empty.
 */
bool_t priority_queue_empty(const priority_queue_t* cppque_pqueue)
{
    assert(cppque_pqueue != NULL);

    return vector_empty(&cppque_pqueue->_vec_base);
}

/**
 * Returns the number of elements in the priority_queue.
 */
size_t priority_queue_size(const priority_queue_t* cppque_pqueue)
{
    assert(cppque_pqueue != NULL);

    return vector_size(&cppque_pqueue->_vec_base);
}

/**
 * Returns a const reference to the largest element at the top of the priority_queue.
 */
void* priority_queue_top(const priority_queue_t* cppque_pqueue)
{
    assert(cppque_pqueue != NULL);

    return vector_front(&cppque_pqueue->_vec_base);
}

/**
 * Removes the largest element of the priority_queue from the top position.
 */
void priority_queue_pop(priority_queue_t* ppque_pqueue)
{
    assert(ppque_pqueue != NULL);

    algo_pop_heap_if(vector_begin(&ppque_pqueue->_vec_base), vector_end(&ppque_pqueue->_vec_base), ppque_pqueue->_bfun_priority);
    vector_pop_back(&ppque_pqueue->_vec_base);
}

/** local function implementation section **/

/** eof **/

