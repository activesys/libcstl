/*
 *  The implementation of cstl types builtin functions.
 *  Copyright (C)  2008 - 2014  Wangbo
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
#include <cstl/cstl_def.h>
#include <cstl/cstl_alloc.h>
#include <cstl/cstl_types.h>

#include <cstl/cvector.h>
#include <cstl/clist.h>
#include <cstl/cslist.h>
#include <cstl/cdeque.h>
#include <cstl/cstack.h>
#include <cstl/cqueue.h>
#include <cstl/cset.h>
#include <cstl/cmap.h>
#include <cstl/chash_set.h>
#include <cstl/chash_map.h>
#include <cstl/cstring.h>
#include <cstl/cutility.h>

#include "cstl_types_builtin.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * The cstl builtin copy, compare destroy function for c builtin type and cstl builtins.
 */
/* c builtin */
/* char */
void _type_init_char(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    *(char*)cpv_input = '\0';
    *(bool_t*)pv_output = true;
}

void _type_copy_char(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(char*)cpv_first = *(char*)cpv_second;
    *(bool_t*)pv_output = true;
}

void _type_less_char(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = *(char*)cpv_first < *(char*)cpv_second ? true : false;
}

void _type_destroy_char(const void* cpv_input, void* pv_output)
{
    _type_destroy_default(cpv_input, pv_output);
}

/* unsigned char */
void _type_init_uchar(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    *(unsigned char*)cpv_input = 0x00;
    *(bool_t*)pv_output = true;
}

void _type_copy_uchar(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(unsigned char*)cpv_first = *(unsigned char*)cpv_second;
    *(bool_t*)pv_output = true;
}

void _type_less_uchar(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = *(unsigned char*)cpv_first < *(unsigned char*)cpv_second ? true : false;
}

void _type_destroy_uchar(const void* cpv_input, void* pv_output)
{
    _type_destroy_default(cpv_input, pv_output);
}

/* short */
void _type_init_short(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    *(short*)cpv_input = 0;
    *(bool_t*)pv_output = true;
}

void _type_copy_short(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(short*)cpv_first = *(short*)cpv_second;
    *(bool_t*)pv_output = true;
}

void _type_less_short(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = *(short*)cpv_first < *(short*)cpv_second ? true : false;
}

void _type_destroy_short(const void* cpv_input, void* pv_output)
{
    _type_destroy_default(cpv_input, pv_output);
}

/* unsigned short */
void _type_init_ushort(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    *(unsigned short*)cpv_input = 0;
    *(bool_t*)pv_output = true;
}

void _type_copy_ushort(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(unsigned short*)cpv_first = *(unsigned short*)cpv_second;
    *(bool_t*)pv_output = true;
}

void _type_less_ushort(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = *(unsigned short*)cpv_first < *(unsigned short*)cpv_second ? true : false;
}

void _type_destroy_ushort(const void* cpv_input, void* pv_output)
{
    _type_destroy_default(cpv_input, pv_output);
}

/* int */
void _type_init_int(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    *(int*)cpv_input = 0;
    *(bool_t*)pv_output = true;
}

void _type_copy_int(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(int*)cpv_first = *(int*)cpv_second;
    *(bool_t*)pv_output = true;
}

void _type_less_int(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}

void _type_destroy_int(const void* cpv_input, void* pv_output)
{
    _type_destroy_default(cpv_input, pv_output);
}

/* unsigned int */
void _type_init_uint(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    *(unsigned int*)cpv_input = 0;
    *(bool_t*)pv_output = true;
}

void _type_copy_uint(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(unsigned int*)cpv_first = *(unsigned int*)cpv_second;
    *(bool_t*)pv_output = true;
}

void _type_less_uint(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = *(unsigned int*)cpv_first < *(unsigned int*)cpv_second ? true : false;
}

void _type_destroy_uint(const void* cpv_input, void* pv_output)
{
    _type_destroy_default(cpv_input, pv_output);
}

/* long */
void _type_init_long(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    *(long*)cpv_input = 0;
    *(bool_t*)pv_output = true;
}

void _type_copy_long(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(long*)cpv_first = *(long*)cpv_second;
    *(bool_t*)pv_output = true;
}

void _type_less_long(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = *(long*)cpv_first < *(long*)cpv_second ? true : false;
}

void _type_destroy_long(const void* cpv_input, void* pv_output)
{
    _type_destroy_default(cpv_input, pv_output);
}

/* unsigned long */
void _type_init_ulong(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    *(unsigned long*)cpv_input = 0;
    *(bool_t*)pv_output = true;
}

void _type_copy_ulong(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(unsigned long*)cpv_first = *(unsigned long*)cpv_second;
    *(bool_t*)pv_output = true;
}

void _type_less_ulong(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = *(unsigned long*)cpv_first < *(unsigned long*)cpv_second ? true : false;
}

void _type_destroy_ulong(const void* cpv_input, void* pv_output)
{
    _type_destroy_default(cpv_input, pv_output);
}

/* float */
void _type_init_float(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    *(float*)cpv_input = 0.0;
    *(bool_t*)pv_output = true;
}

void _type_copy_float(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(float*)cpv_first = *(float*)cpv_second;
    *(bool_t*)pv_output = true;
}

void _type_less_float(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = *(float*)cpv_first - *(float*)cpv_second < -FLT_EPSILON ? true : false;
}

void _type_destroy_float(const void* cpv_input, void* pv_output)
{
    _type_destroy_default(cpv_input, pv_output);
}

/* double */
void _type_init_double(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    *(double*)cpv_input = 0.0;
    *(bool_t*)pv_output = true;
}

void _type_copy_double(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(double*)cpv_first = *(double*)cpv_second;
    *(bool_t*)pv_output = true;
}

void _type_less_double(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = *(double*)cpv_first - *(double*)cpv_second < -DBL_EPSILON ? true : false;
}

void _type_destroy_double(const void* cpv_input, void* pv_output)
{
    _type_destroy_default(cpv_input, pv_output);
}

/* long double */
void _type_init_long_double(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    *(long double*)cpv_input = 0.0;
    *(bool_t*)pv_output = true;
}

void _type_copy_long_double(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(long double*)cpv_first = *(long double*)cpv_second;
    *(bool_t*)pv_output = true;
}

void _type_less_long_double(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = *(long double*)cpv_first - *(long double*)cpv_second < -LDBL_EPSILON ? true : false;
}

void _type_destroy_long_double(const void* cpv_input, void* pv_output)
{
    _type_destroy_default(cpv_input, pv_output);
}

/* bool_t */
void _type_init_cstl_bool(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    *(bool_t*)cpv_input = false;
    *(bool_t*)pv_output = true;
}

void _type_copy_cstl_bool(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)cpv_first = *(bool_t*)cpv_second;
    *(bool_t*)pv_output = true;
}

void _type_less_cstl_bool(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = *(bool_t*)cpv_first < *(bool_t*)cpv_second ? true : false;
}

void _type_destroy_cstl_bool(const void* cpv_input, void* pv_output)
{
    _type_destroy_default(cpv_input, pv_output);
}

/* void* */
void _type_init_pointer(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    *(void**)cpv_input = NULL;
    *(bool_t*)pv_output = true;
}

void _type_copy_pointer(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(void**)cpv_first = *(void**)cpv_second;
    *(bool_t*)pv_output = true;
}

void _type_less_pointer(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = *(void**)cpv_first < *(void**)cpv_second ? true : false;
}

void _type_destroy_pointer(const void* cpv_input, void* pv_output)
{
    _type_destroy_default(cpv_input, pv_output);
}

/* char* */
/*
 * char* is specific c builtin type, the string_t is used for storing the 
 * char* or c_str type. 
 */
void _type_init_cstr(const void* cpv_input, void* pv_output)
{
    bool_t b_result = false;

    assert(cpv_input != NULL && pv_output != NULL);

    b_result = _create_string_auxiliary((string_t*)cpv_input);
    assert(b_result);
    string_init((string_t*)cpv_input);
    *(bool_t*)pv_output = true;
}

void _type_copy_cstr(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    string_assign((string_t*)cpv_first, (string_t*)cpv_second);
    *(bool_t*)pv_output = true;
}

void _type_less_cstr(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = string_less((string_t*)cpv_first, (string_t*)cpv_second);
}

void _type_destroy_cstr(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    _string_destroy_auxiliary((string_t*)cpv_input);
    *(bool_t*)pv_output = true;
}

/* cstl container */
/* vector_t */
void _type_init_vector(const void* cpv_input, void* pv_output)
{
    bool_t b_result = false;

    assert(cpv_input != NULL && pv_output != NULL);

    b_result = _create_vector_auxiliary((vector_t*)cpv_input, (char*)pv_output);
    assert(b_result);
    /* initialize vector_t */
    vector_init((vector_t*)cpv_input);
}

void _type_copy_vector(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    vector_assign((vector_t*)cpv_first, (vector_t*)cpv_second);
    *(bool_t*)pv_output = true;
}

void _type_less_vector(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = vector_less((vector_t*)cpv_first, (vector_t*)cpv_second);
}

void _type_destroy_vector(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    _vector_destroy_auxiliary((vector_t*)cpv_input);
    *(bool_t*)pv_output = true;
}

/* list_t */
void _type_init_list(const void* cpv_input, void* pv_output)
{
    bool_t b_result = false;
    assert(cpv_input != NULL && pv_output != NULL);

    b_result = _create_list_auxiliary((list_t*)cpv_input, (char*)pv_output);
    assert(b_result);
    /* initialize list_t */
    list_init((list_t*)cpv_input);
}

void _type_copy_list(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    list_assign((list_t*)cpv_first, (list_t*)cpv_second);
    *(bool_t*)pv_output = true;
}

void _type_less_list(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = list_less((list_t*)cpv_first, (list_t*)cpv_second);
}

void _type_destroy_list(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    _list_destroy_auxiliary((list_t*)cpv_input);
    *(bool_t*)pv_output = true;
}

/* slist_t */
void _type_init_slist(const void* cpv_input, void* pv_output)
{
    bool_t b_result = false;
    assert(cpv_input != NULL && pv_output != NULL);

    b_result = _create_slist_auxiliary((slist_t*)cpv_input, (char*)pv_output);
    assert(b_result);
    /* initialize slist_t */
    slist_init((slist_t*)cpv_input);
}

void _type_copy_slist(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    slist_assign((slist_t*)cpv_first, (slist_t*)cpv_second);
    *(bool_t*)pv_output = true;
}

void _type_less_slist(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = slist_less((slist_t*)cpv_first, (slist_t*)cpv_second);
}

void _type_destroy_slist(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    _slist_destroy_auxiliary((slist_t*)cpv_input);
    *(bool_t*)pv_output = true;
}

/* deque_t */
void _type_init_deque(const void* cpv_input, void* pv_output)
{
    bool_t b_result = false;
    assert(cpv_input != NULL && pv_output != NULL);

    b_result = _create_deque_auxiliary((deque_t*)cpv_input, (char*)pv_output);
    assert(b_result);
    /* initialize deque_t */
    deque_init((deque_t*)cpv_input);
}

void _type_copy_deque(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    deque_assign((deque_t*)cpv_first, (deque_t*)cpv_second);
    *(bool_t*)pv_output = true;
}

void _type_less_deque(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = deque_less((deque_t*)cpv_first, (deque_t*)cpv_second);
}

void _type_destroy_deque(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    _deque_destroy_auxiliary((deque_t*)cpv_input);
    *(bool_t*)pv_output = true;
}

/* stack_t */
void _type_init_stack(const void* cpv_input, void* pv_output)
{
    bool_t b_result = false;
    assert(cpv_input != NULL && pv_output != NULL);

    b_result = _create_stack_auxiliary((stack_t*)cpv_input, (char*)pv_output);
    assert(b_result);
    stack_init((stack_t*)cpv_input);
}

void _type_copy_stack(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    stack_assign((stack_t*)cpv_first, (stack_t*)cpv_second);
    *(bool_t*)pv_output = true;
}

void _type_less_stack(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = stack_less((stack_t*)cpv_first, (stack_t*)cpv_second);
}

void _type_destroy_stack(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    _stack_destroy_auxiliary((stack_t*)cpv_input);
    *(bool_t*)pv_output = true;
}

/* queue_t */
void _type_init_queue(const void* cpv_input, void* pv_output)
{
    bool_t b_result = false;
    assert(cpv_input != NULL && pv_output != NULL);

    b_result = _create_queue_auxiliary((queue_t*)cpv_input, (char*)pv_output);
    assert(b_result);

    queue_init((queue_t*)cpv_input);
}

void _type_copy_queue(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    queue_assign((queue_t*)cpv_first, (queue_t*)cpv_second);
    *(bool_t*)pv_output = true;
}

void _type_less_queue(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = queue_less((queue_t*)cpv_first, (queue_t*)cpv_second);
}

void _type_destroy_queue(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    _queue_destroy_auxiliary((queue_t*)cpv_input);
    *(bool_t*)pv_output = true;
}

/* priority_queue_t */
void _type_init_priority_queue(const void* cpv_input, void* pv_output)
{
    bool_t b_result = false;
    assert(cpv_input != NULL && pv_output != NULL);

    b_result = _create_priority_queue_auxiliary((priority_queue_t*)cpv_input, (char*)pv_output);
    assert(b_result);
    priority_queue_init((priority_queue_t*)cpv_input);
}

void _type_copy_priority_queue(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    priority_queue_assign((priority_queue_t*)cpv_first, (priority_queue_t*)cpv_second);
    *(bool_t*)pv_output = true;
}

void _type_less_priority_queue(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = vector_less(&((priority_queue_t*)cpv_first)->_vec_base, &((priority_queue_t*)cpv_second)->_vec_base);
}

void _type_destroy_priority_queue(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    _priority_queue_destroy_auxiliary((priority_queue_t*)cpv_input);
    *(bool_t*)pv_output = true;
}

/* set_t */
void _type_init_set(const void* cpv_input, void* pv_output)
{
    bool_t b_result = false;
    assert(cpv_input != NULL && pv_output != NULL);

    b_result = _create_set_auxiliary((set_t*)cpv_input, (char*)pv_output);
    assert(b_result);
    set_init((set_t*)cpv_input);
}

void _type_copy_set(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    set_assign((set_t*)cpv_first, (set_t*)cpv_second);
    *(bool_t*)pv_output = true;
}

void _type_less_set(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = set_less((set_t*)cpv_first, (set_t*)cpv_second);
}

void _type_destroy_set(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    _set_destroy_auxiliary((set_t*)cpv_input);
    *(bool_t*)pv_output = true;
}

/* map_t */
void _type_init_map(const void* cpv_input, void* pv_output)
{
    bool_t b_result = false;
    assert(cpv_input != NULL && pv_output != NULL);

    b_result = _create_map_auxiliary((map_t*)cpv_input, (char*)pv_output);
    assert(b_result);
    map_init((map_t*)cpv_input);
}

void _type_copy_map(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    map_assign((map_t*)cpv_first, (map_t*)cpv_second);
    *(bool_t*)pv_output = true;
}

void _type_less_map(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = map_less((map_t*)cpv_first, (map_t*)cpv_second);
}

void _type_destroy_map(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    _map_destroy_auxiliary((map_t*)cpv_input);
    *(bool_t*)pv_output = true;
}

/* multiset_t */
void _type_init_multiset(const void* cpv_input, void* pv_output)
{
    bool_t b_result = false;
    assert(cpv_input != NULL && pv_output != NULL);

    b_result = _create_multiset_auxiliary((multiset_t*)cpv_input, (char*)pv_output);
    assert(b_result);
    multiset_init((multiset_t*)cpv_input);
}

void _type_copy_multiset(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    multiset_assign((multiset_t*)cpv_first, (multiset_t*)cpv_second);
    *(bool_t*)pv_output = true;
}

void _type_less_multiset(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = multiset_less((multiset_t*)cpv_first, (multiset_t*)cpv_second);
}

void _type_destroy_multiset(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    _multiset_destroy_auxiliary((multiset_t*)cpv_input);
    *(bool_t*)pv_output = true;
}

/* multimap_t */
void _type_init_multimap(const void* cpv_input, void* pv_output)
{
    bool_t b_result = false;
    assert(cpv_input != NULL && pv_output != NULL);

    b_result = _create_multimap_auxiliary((multimap_t*)cpv_input, (char*)pv_output);
    assert(b_result);
    multimap_init((multimap_t*)cpv_input);
}

void _type_copy_multimap(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    multimap_assign((multimap_t*)cpv_first, (multimap_t*)cpv_second);
    *(bool_t*)pv_output = true;
}

void _type_less_multimap(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = multimap_less((multimap_t*)cpv_first, (multimap_t*)cpv_second);
}

void _type_destroy_multimap(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    _multimap_destroy_auxiliary((multimap_t*)cpv_input);
    *(bool_t*)pv_output = true;
}

/* hash_set_t */
void _type_init_hash_set(const void* cpv_input, void* pv_output)
{
    bool_t b_result = false;
    assert(cpv_input != NULL && pv_output != NULL);

    b_result = _create_hash_set_auxiliary((hash_set_t*)cpv_input, (char*)pv_output);
    assert(b_result);
    hash_set_init((hash_set_t*)cpv_input);
}

void _type_copy_hash_set(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    hash_set_assign((hash_set_t*)cpv_first, (hash_set_t*)cpv_second);
    *(bool_t*)pv_output = true;
}

void _type_less_hash_set(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = hash_set_less((hash_set_t*)cpv_first, (hash_set_t*)cpv_second);
}

void _type_destroy_hash_set(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    _hash_set_destroy_auxiliary((hash_set_t*)cpv_input);
    *(bool_t*)pv_output = true;
}

/* hash_map_t */
void _type_init_hash_map(const void* cpv_input, void* pv_output)
{
    bool_t b_result = false;
    assert(cpv_input != NULL && pv_output != NULL);

    b_result = _create_hash_map_auxiliary((hash_map_t*)cpv_input, (char*)pv_output);
    assert(b_result);
    hash_map_init((hash_map_t*)cpv_input);
}

void _type_copy_hash_map(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    hash_map_assign((hash_map_t*)cpv_first, (hash_map_t*)cpv_second);
    *(bool_t*)pv_output = true;
}

void _type_less_hash_map(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = hash_map_less((hash_map_t*)cpv_first, (hash_map_t*)cpv_second);
}

void _type_destroy_hash_map(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    _hash_map_destroy_auxiliary((hash_map_t*)cpv_input);
    *(bool_t*)pv_output = true;
}

/* hash_multiset_t */
void _type_init_hash_multiset(const void* cpv_input, void* pv_output)
{
    bool_t b_result = false;
    assert(cpv_input != NULL && pv_output != NULL);

    b_result = _create_hash_multiset_auxiliary((hash_multiset_t*)cpv_input, (char*)pv_output);
    assert(b_result);
    hash_multiset_init((hash_multiset_t*)cpv_input);
}

void _type_copy_hash_multiset(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    hash_multiset_assign((hash_multiset_t*)cpv_first, (hash_multiset_t*)cpv_second);
    *(bool_t*)pv_output = true;
}

void _type_less_hash_multiset(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = hash_multiset_less(
        (hash_multiset_t*)cpv_first, (hash_multiset_t*)cpv_second);
}

void _type_destroy_hash_multiset(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    _hash_multiset_destroy_auxiliary((hash_multiset_t*)cpv_input);
    *(bool_t*)pv_output = true;
}

/* hash_multimap_t */
void _type_init_hash_multimap(const void* cpv_input, void* pv_output)
{
    bool_t b_result = false;
    assert(cpv_input != NULL && pv_output != NULL);

    b_result = _create_hash_multimap_auxiliary((hash_multimap_t*)cpv_input, (char*)pv_output);
    assert(b_result);
    hash_multimap_init((hash_multimap_t*)cpv_input);
}

void _type_copy_hash_multimap(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    hash_multimap_assign((hash_multimap_t*)cpv_first, (hash_multimap_t*)cpv_second);
    *(bool_t*)pv_output = true;
}

void _type_less_hash_multimap(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = hash_multimap_less(
        (hash_multimap_t*)cpv_first, (hash_multimap_t*)cpv_second);
}

void _type_destroy_hash_multimap(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    _hash_multimap_destroy_auxiliary((hash_multimap_t*)cpv_input);
    *(bool_t*)pv_output = true;
}

/* pair_t */
void _type_init_pair(const void* cpv_input, void* pv_output)
{
    bool_t b_result = false;
    assert(cpv_input != NULL && pv_output != NULL);

    b_result = _create_pair_auxiliary((pair_t*)cpv_input, (char*)pv_output);
    assert(b_result);
    /* initialize pair */
    pair_init((pair_t*)cpv_input);
}

void _type_copy_pair(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    pair_assign((pair_t*)cpv_first, (pair_t*)cpv_second);
    *(bool_t*)pv_output = true;
}

void _type_less_pair(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = pair_less((pair_t*)cpv_first, (pair_t*)cpv_second);
}

void _type_destroy_pair(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    _pair_destroy_auxiliary((pair_t*)cpv_input);
    *(bool_t*)pv_output = true;
}

/* string_t */
void _type_init_string(const void* cpv_input, void* pv_output)
{
    void* pv_avoidwarning = NULL;
    bool_t b_result = false;
    assert(cpv_input != NULL && pv_output != NULL);
    b_result = _create_string_auxiliary((string_t*)cpv_input);
    assert(b_result);
    string_init((string_t*)cpv_input);
    pv_avoidwarning = pv_output;
}

void _type_copy_string(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    string_assign((string_t*)cpv_first, (string_t*)cpv_second);
    *(bool_t*)pv_output = true;
}

void _type_less_string(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = string_less((string_t*)cpv_first, (string_t*)cpv_second);
}

void _type_destroy_string(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    _string_destroy_auxiliary((string_t*)cpv_input);
    *(bool_t*)pv_output = true;
}

/* basic_string_t */
void _type_init_basic_string(const void* cpv_input, void* pv_output)
{
    bool_t b_result = false;

    assert(cpv_input != NULL && pv_output != NULL);

    b_result = _create_basic_string_auxiliary((basic_string_t*)cpv_input, (char*)pv_output);
    assert(b_result);
    /* initialize basic_string_t */
    basic_string_init((basic_string_t*)cpv_input);
}

void _type_copy_basic_string(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    basic_string_assign((basic_string_t*)cpv_first, (basic_string_t*)cpv_second);
    *(bool_t*)pv_output = true;
}

void _type_less_basic_string(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = basic_string_less((basic_string_t*)cpv_first, (basic_string_t*)cpv_second);
}

void _type_destroy_basic_string(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    _basic_string_destroy_auxiliary((basic_string_t*)cpv_input);
    *(bool_t*)pv_output = true;
}

/* iterator_t */
void _type_init_iterator(const void* cpv_input, void* pv_output)
{
    void* pv_avoidwarning = NULL;
    bool_t b_result = sizeof(iterator_t);

    assert(cpv_input != NULL && pv_output != NULL);

    _type_init_default(cpv_input, &b_result);
    pv_avoidwarning = (void*)pv_output;
}

void _type_copy_iterator(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    memcpy((iterator_t*)cpv_first, (iterator_t*)cpv_second, sizeof(iterator_t));
    *(bool_t*)pv_output = true;
}

void _type_less_iterator(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = memcmp((iterator_t*)cpv_first, (iterator_t*)cpv_second,
        sizeof(iterator_t)) < 0 ? true : false;
}

void _type_destroy_iterator(const void* cpv_input, void* pv_output)
{
    _type_destroy_default(cpv_input, pv_output);
}

/* range_t */
void _type_init_range(const void* cpv_input, void* pv_output)
{
    void* pv_avoidwarning = NULL;
    bool_t b_result = sizeof(range_t);

    assert(cpv_input != NULL && pv_output != NULL);

    _type_init_default(cpv_input, &b_result);
    pv_avoidwarning = (void*)pv_output;
}

void _type_copy_range(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    memcpy((range_t*)cpv_first, (range_t*)cpv_second, sizeof(range_t));
    *(bool_t*)pv_output = true;
}

void _type_less_range(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = memcmp((range_t*)cpv_first, (range_t*)cpv_second,
        sizeof(range_t)) < 0 ? true : false;
}

void _type_destroy_range(const void* cpv_input, void* pv_output)
{
    _type_destroy_default(cpv_input, pv_output);
}

#ifndef _MSC_VER
/* _Bool */
void _type_init_bool(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    *(_Bool*)cpv_input = false;
    *(bool_t*)pv_output = true;
}

void _type_copy_bool(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(_Bool*)cpv_first = *(_Bool*)cpv_second;
    *(bool_t*)pv_output = true;
}

void _type_less_bool(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = *(_Bool*)cpv_first < *(_Bool*)cpv_second ? true : false;
}

void _type_destroy_bool(const void* cpv_input, void* pv_output)
{
    _type_destroy_default(cpv_input, pv_output);
}

/* long long */
void _type_init_long_long(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    *(long long*)cpv_input = false;
    *(bool_t*)pv_output = true;
}

void _type_copy_long_long(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(long long*)cpv_first = *(long long*)cpv_second;
    *(bool_t*)pv_output = true;
}

void _type_less_long_long(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = *(long long*)cpv_first < *(long long*)cpv_second ? true : false;
}

void _type_destroy_long_long(const void* cpv_input, void* pv_output)
{
    _type_destroy_default(cpv_input, pv_output);
}

/* unsigned long long */
void _type_init_ulong_long(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    *(unsigned long long*)cpv_input = false;
    *(bool_t*)pv_output = true;
}

void _type_copy_ulong_long(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(unsigned long long*)cpv_first = *(unsigned long long*)cpv_second;
    *(bool_t*)pv_output = true;
}

void _type_less_ulong_long(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = *(unsigned long long*)cpv_first < *(unsigned long long*)cpv_second ? true : false;
}

void _type_destroy_ulong_long(const void* cpv_input, void* pv_output)
{
    _type_destroy_default(cpv_input, pv_output);
}
#endif

/** local function implementation section **/

/** eof **/

