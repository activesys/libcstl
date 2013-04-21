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
#include <cstl/cqueue.h>

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Create priority queue adaptor.
 */
priority_queue_t* _create_priority_queue(const char* s_typename)
{
    priority_queue_t* ppque_new = NULL;

    assert(s_typename != NULL);
    
    if ((ppque_new = (priority_queue_t*)malloc(sizeof(priority_queue_t))) == NULL) {
        return NULL;
    }

    if (!_create_priority_queue_auxiliary(ppque_new, s_typename)) {
        free(ppque_new);
        return NULL;
    }

    return ppque_new;
}

/**
 * Create priority queue adaptor auxiliary function.
 */
bool_t _create_priority_queue_auxiliary(priority_queue_t* ppque_pqueue,  const char* s_typename)
{
    assert(ppque_pqueue != NULL);
    assert(s_typename != NULL);

    if (!_create_vector_auxiliary(&ppque_pqueue->_vec_base, s_typename)) {
        return false;
    }
    ppque_pqueue->_bfun_priority = NULL;

    return true;
}

/**
 * Destroy priority queue adaptor auxiliary function.
 */
void _priority_queue_destroy_auxiliary(priority_queue_t* ppque_pqueue)
{
    assert(ppque_pqueue != NULL);

    _vector_destroy_auxiliary(&ppque_pqueue->_vec_base);
    ppque_pqueue->_bfun_priority = NULL;
}

/**
 * Add specificed element at the back of priority queue. 
 */
void _priority_queue_push(priority_queue_t* ppque_pqueue, ...)
{
    va_list val_elemlist;

    assert(ppque_pqueue != NULL);

    va_start(val_elemlist, ppque_pqueue);
    _vector_push_back_varg(&ppque_pqueue->_vec_base, val_elemlist);
    va_end(val_elemlist);

    algo_push_heap_if(vector_begin(&ppque_pqueue->_vec_base), vector_end(&ppque_pqueue->_vec_base), ppque_pqueue->_bfun_priority);
}

/** local function implementation section **/

/** eof **/

