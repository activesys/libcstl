/*
 *  The implemention of priority queue private functions.
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
/* priority queue function */
/* create new priority queue */
priority_queue_t* _create_priority_queue(const char* s_typename)
{
    priority_queue_t* pt_newpqueue = (priority_queue_t*)malloc(sizeof(priority_queue_t));

    if(pt_newpqueue == NULL)
    {
        return NULL;
    }

    if(!_create_priority_queue_auxiliary(pt_newpqueue, s_typename))
    {
        free(pt_newpqueue);
        return NULL;
    }

    return pt_newpqueue;
}

bool_t _create_priority_queue_auxiliary(priority_queue_t* pt_pqueue,  const char* s_typename)
{
    assert(pt_pqueue != NULL && s_typename != NULL);

    if(!_create_vector_auxiliary(&pt_pqueue->_t_vector, s_typename))
    {
        return false;
    }
    pt_pqueue->_t_binary_op = NULL;

    return true;
}

void _priority_queue_destroy_auxiliary(priority_queue_t* pt_pqueue)
{
    assert(pt_pqueue != NULL);

    _vector_destroy_auxiliary(&pt_pqueue->_t_vector);
    pt_pqueue->_t_binary_op = NULL;
}


void _priority_queue_push(priority_queue_t* pt_pqueue, ...)
{
    va_list val_elemlist;

    assert(pt_pqueue != NULL);

    va_start(val_elemlist, pt_pqueue);
    _vector_push_back_varg(&pt_pqueue->_t_vector, val_elemlist);
    va_end(val_elemlist);

    if(pt_pqueue->_t_binary_op == NULL)
    {
        algo_push_heap(
            vector_begin(&pt_pqueue->_t_vector), vector_end(&pt_pqueue->_t_vector));
    }
    else
    {
        algo_push_heap_if(
            vector_begin(&pt_pqueue->_t_vector), vector_end(&pt_pqueue->_t_vector),
            pt_pqueue->_t_binary_op);
    }
}

/** local function implementation section **/

/** eof **/

