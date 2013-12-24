/*
 *  The implementation of function.
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
#include <cstl/citerator.h>
#include <cstl/cfunctional.h>

#include <cstl/cvector.h>
#include <cstl/clist.h>
#include <cstl/cdeque.h>
#include <cstl/cslist.h>
#include <cstl/cstack.h>
#include <cstl/cqueue.h>
#include <cstl/cstring.h>
#include <cstl/cutility.h>
#include <cstl/cset.h>
#include <cstl/cmap.h>
#include <cstl/chash_set.h>
#include <cstl/chash_map.h>

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/* 
 * There is special condition in binary function 
 * when the second parameter is NULL.
 */
/**
 * Plus
 */
void fun_plus_char(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(char*)pv_output = *(char*)cpv_first + *(char*)cpv_second;
}

void fun_plus_uchar(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(unsigned char*)pv_output = *(unsigned char*)cpv_first + *(unsigned char*)cpv_second;
}

void fun_plus_short(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(short*)pv_output = *(short*)cpv_first + *(short*)cpv_second;
}

void fun_plus_ushort(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(unsigned short*)pv_output = *(unsigned short*)cpv_first + *(unsigned short*)cpv_second;
}

void fun_plus_int(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(int*)pv_output = *(int*)cpv_first + *(int*)cpv_second;
}

void fun_plus_uint(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(unsigned int*)pv_output = *(unsigned int*)cpv_first + *(unsigned int*)cpv_second;
}

void fun_plus_long(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(long*)pv_output = *(long*)cpv_first + *(long*)cpv_second;
}

void fun_plus_ulong(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(unsigned long*)pv_output = *(unsigned long*)cpv_first + *(unsigned long*)cpv_second;
}

void fun_plus_float(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(float*)pv_output = *(float*)cpv_first + *(float*)cpv_second;
}

void fun_plus_double(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(double*)pv_output = *(double*)cpv_first + *(double*)cpv_second;
}

void fun_plus_long_double(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(long double*)pv_output = *(long double*)cpv_first + *(long double*)cpv_second;
}

#ifndef _MSC_VER
void fun_plus_long_long(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(long long*)pv_output = *(long long*)cpv_first + *(long long*)cpv_second;
}

void fun_plus_ulong_long(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(unsigned long long*)pv_output = *(unsigned long long*)cpv_first + *(unsigned long long*)cpv_second;
}
#endif

/**
 * Minus.
 */
void fun_minus_char(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(char*)pv_output = *(char*)cpv_first - *(char*)cpv_second;
}

void fun_minus_uchar(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(unsigned char*)pv_output = *(unsigned char*)cpv_first - *(unsigned char*)cpv_second;
}

void fun_minus_short(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(short*)pv_output = *(short*)cpv_first - *(short*)cpv_second;
}

void fun_minus_ushort(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(unsigned short*)pv_output = *(unsigned short*)cpv_first - *(unsigned short*)cpv_second;
}

void fun_minus_int(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(int*)pv_output = *(int*)cpv_first - *(int*)cpv_second;
}

void fun_minus_uint(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(unsigned int*)pv_output = *(unsigned int*)cpv_first - *(unsigned int*)cpv_second;
}

void fun_minus_long(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(long*)pv_output = *(long*)cpv_first - *(long*)cpv_second;
}

void fun_minus_ulong(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(unsigned long*)pv_output = *(unsigned long*)cpv_first - *(unsigned long*)cpv_second;
}

void fun_minus_float(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(float*)pv_output = *(float*)cpv_first - *(float*)cpv_second;
}

void fun_minus_double(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(double*)pv_output = *(double*)cpv_first - *(double*)cpv_second;
}

void fun_minus_long_double(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(long double*)pv_output = *(long double*)cpv_first - *(long double*)cpv_second;
}

#ifndef _MSC_VER
void fun_minus_long_long(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(long long*)pv_output = *(long long*)cpv_first - *(long long*)cpv_second;
}

void fun_minus_ulong_long(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(unsigned long long*)pv_output = *(unsigned long long*)cpv_first - *(unsigned long long*)cpv_second;
}
#endif

/**
 * Multiplies.
 */
void fun_multiplies_char(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(char*)pv_output = *(char*)cpv_first * *(char*)cpv_second;
}

void fun_multiplies_uchar(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(unsigned char*)pv_output = *(unsigned char*)cpv_first * *(unsigned char*)cpv_second;
}

void fun_multiplies_short(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(short*)pv_output = *(short*)cpv_first * *(short*)cpv_second;
}

void fun_multiplies_ushort(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(unsigned short*)pv_output = *(unsigned short*)cpv_first * *(unsigned short*)cpv_second;
}

void fun_multiplies_int(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(int*)pv_output = *(int*)cpv_first * *(int*)cpv_second;
}

void fun_multiplies_uint(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(unsigned int*)pv_output = *(unsigned int*)cpv_first * *(unsigned int*)cpv_second;
}

void fun_multiplies_long(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(long*)pv_output = *(long*)cpv_first * *(long*)cpv_second;
}

void fun_multiplies_ulong(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(unsigned long*)pv_output = *(unsigned long*)cpv_first * *(unsigned long*)cpv_second;
}

void fun_multiplies_float(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(float*)pv_output = *(float*)cpv_first * *(float*)cpv_second;
}

void fun_multiplies_double(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(double*)pv_output = *(double*)cpv_first * *(double*)cpv_second;
}

void fun_multiplies_long_double(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(long double*)pv_output = *(long double*)cpv_first * *(long double*)cpv_second;
}

#ifndef _MSC_VER
void fun_multiplies_long_long(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(long long*)pv_output = *(long long*)cpv_first * *(long long*)cpv_second;
}

void fun_multiplies_ulong_long(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(unsigned long long*)pv_output = *(unsigned long long*)cpv_first * *(unsigned long long*)cpv_second;
}
#endif

/**
 * Divides.
 */
void fun_divides_char(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    assert(*(char*)cpv_second != 0x00);
    *(char*)pv_output = *(char*)cpv_first / *(char*)cpv_second;
}

void fun_divides_uchar(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    assert(*(unsigned char*)cpv_second != 0x00);
    *(unsigned char*)pv_output = *(unsigned char*)cpv_first / *(unsigned char*)cpv_second;
}

void fun_divides_short(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    assert(*(short*)cpv_second != 0);
    *(short*)pv_output = *(short*)cpv_first / *(short*)cpv_second;
}

void fun_divides_ushort(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    assert(*(unsigned short*)cpv_second != 0);
    *(unsigned short*)pv_output = *(unsigned short*)cpv_first / *(unsigned short*)cpv_second;
}

void fun_divides_int(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    assert(*(int*)cpv_second != 0);
    *(int*)pv_output = *(int*)cpv_first / *(int*)cpv_second;
}

void fun_divides_uint(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    assert(*(unsigned int*)cpv_second != 0);
    *(unsigned int*)pv_output = *(unsigned int*)cpv_first / *(unsigned int*)cpv_second;
}

void fun_divides_long(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    assert(*(long*)cpv_second != 0);
    *(long*)pv_output = *(long*)cpv_first / *(long*)cpv_second;
}

void fun_divides_ulong(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    assert(*(unsigned long*)cpv_second != 0);
    *(unsigned long*)pv_output = *(unsigned long*)cpv_first / *(unsigned long*)cpv_second;
}

void fun_divides_float(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    assert(*(float*)cpv_second > FLT_EPSILON || *(float*)cpv_second < -FLT_EPSILON);
    *(float*)pv_output = *(float*)cpv_first / *(float*)cpv_second;
}

void fun_divides_double(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    assert(*(double*)cpv_second > DBL_EPSILON || *(double*)cpv_second < -DBL_EPSILON);
    *(double*)pv_output = *(double*)cpv_first / *(double*)cpv_second;
}

void fun_divides_long_double(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    assert(*(long double*)cpv_second > LDBL_EPSILON || *(long double*)cpv_second < -LDBL_EPSILON);
    *(long double*)pv_output = *(long double*)cpv_first / *(long double*)cpv_second;
}

#ifndef _MSC_VER
void fun_divides_long_long(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    assert(*(long long*)cpv_second != 0);
    *(long long*)pv_output = *(long long*)cpv_first / *(long long*)cpv_second;
}

void fun_divides_ulong_long(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    assert(*(unsigned long long*)cpv_second != 0);
    *(unsigned long long*)pv_output = *(unsigned long long*)cpv_first / *(unsigned long long*)cpv_second;
}
#endif

/**
 * Modulus.
 */
void fun_modulus_char(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    assert(*(char*)cpv_second != 0x00);
    *(char*)pv_output = *(char*)cpv_first % *(char*)cpv_second;
}

void fun_modulus_uchar(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    assert(*(unsigned char*)cpv_second != 0x00);
    *(unsigned char*)pv_output = *(unsigned char*)cpv_first % *(unsigned char*)cpv_second;
}

void fun_modulus_short(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    assert(*(short*)cpv_second != 0);
    *(short*)pv_output = *(short*)cpv_first % *(short*)cpv_second;
}

void fun_modulus_ushort(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    assert(*(unsigned short*)cpv_second != 0);
    *(unsigned short*)pv_output = *(unsigned short*)cpv_first % *(unsigned short*)cpv_second;
}

void fun_modulus_int(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    assert(*(int*)cpv_second != 0);
    *(int*)pv_output = *(int*)cpv_first % *(int*)cpv_second;
}

void fun_modulus_uint(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    assert(*(unsigned int*)cpv_second != 0);
    *(unsigned int*)pv_output = *(unsigned int*)cpv_first % *(unsigned int*)cpv_second;
}

void fun_modulus_long(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    assert(*(long*)cpv_second != 0);
    *(long*)pv_output = *(long*)cpv_first % *(long*)cpv_second;
}

void fun_modulus_ulong(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    assert(*(unsigned long*)cpv_second != 0);
    *(unsigned long*)pv_output = *(unsigned long*)cpv_first % *(unsigned long*)cpv_second;
}

#ifndef _MSC_VER
void fun_modulus_long_long(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    assert(*(long long*)cpv_second != 0);
    *(long long*)pv_output = *(long long*)cpv_first % *(long long*)cpv_second;
}

void fun_modulus_ulong_long(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    assert(*(unsigned long long*)cpv_second != 0);
    *(unsigned long long*)pv_output = *(unsigned long long*)cpv_first % *(unsigned long long*)cpv_second;
}
#endif

/**
 * Negate.
 */
void fun_negate_char(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);

    *(char*)pv_output = -*(char*)cpv_input;
}

void fun_negate_short(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);

    *(short*)pv_output = -*(short*)cpv_input;
}

void fun_negate_int(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);

    *(int*)pv_output = -*(int*)cpv_input;
}

void fun_negate_long(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);

    *(long*)pv_output = -*(long*)cpv_input;
}

void fun_negate_float(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);

    *(float*)pv_output = -*(float*)cpv_input;
}

void fun_negate_double(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);

    *(double*)pv_output = -*(double*)cpv_input;
}

void fun_negate_long_double(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);

    *(long double*)pv_output = -*(long double*)cpv_input;
}

#ifndef _MSC_VER
void fun_negate_long_long(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);

    *(long long*)pv_output = -*(long long*)cpv_input;
}
#endif

/* comparisons */
/**
 * Equal.
 */
void fun_equal_char(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(char*)cpv_first == *(char*)cpv_second ? true : false;
}

void fun_equal_uchar(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(unsigned char*)cpv_first == *(unsigned char*)cpv_second ? true : false;
}

void fun_equal_short(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(short*)cpv_first == *(short*)cpv_second ? true : false;
}

void fun_equal_ushort(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(unsigned short*)cpv_first == *(unsigned short*)cpv_second ? true : false;
}

void fun_equal_int(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(int*)cpv_first == *(int*)cpv_second ? true : false;
}

void fun_equal_uint(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(unsigned int*)cpv_first == *(unsigned int*)cpv_second ? true : false;
}

void fun_equal_long(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(long*)cpv_first == *(long*)cpv_second ? true : false;
}

void fun_equal_ulong(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(unsigned long*)cpv_first == *(unsigned long*)cpv_second ? true : false;
}

void fun_equal_float(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(float*)cpv_first - *(float*)cpv_second < FLT_EPSILON &&
        *(float*)cpv_first - *(float*)cpv_second > -FLT_EPSILON ? true : false;
}

void fun_equal_double(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(double*)cpv_first - *(double*)cpv_second < DBL_EPSILON &&
        *(double*)cpv_first - *(double*)cpv_second > -DBL_EPSILON ? true : false;
}

void fun_equal_long_double(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(long double*)cpv_first - *(long double*)cpv_second < LDBL_EPSILON &&
        *(long double*)cpv_first - *(long double*)cpv_second > -LDBL_EPSILON ? true : false;
}

void fun_equal_cstr(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    char* s_first = NULL;
    char* s_second = NULL;
    size_t t_firstlen = 0;
    size_t t_secondlen = 0;
    size_t t_len = 0;

    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    s_first = (char*)cpv_first;
    s_second = (char*)cpv_second;
    t_firstlen = strlen(s_first);
    t_secondlen = strlen(s_second);
    t_len = t_firstlen > t_secondlen ? t_firstlen : t_secondlen;

    *(bool_t*)pv_output = strncmp(s_first, s_second, t_len) == 0 ? true : false;
}

void fun_equal_pointer(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(void**)cpv_first == *(void**)cpv_second ? true : false;
}

void fun_equal_vector(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = vector_equal((vector_t*)cpv_first, (vector_t*)cpv_second);
}

void fun_equal_deque(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = deque_equal((deque_t*)cpv_first, (deque_t*)cpv_second);
}

void fun_equal_list(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = list_equal((list_t*)cpv_first, (list_t*)cpv_second);
}

void fun_equal_slist(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = slist_equal((slist_t*)cpv_first, (slist_t*)cpv_second);
}

void fun_equal_queue(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = queue_equal((queue_t*)cpv_first, (queue_t*)cpv_second);
}

void fun_equal_stack(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = stack_equal((stack_t*)cpv_first, (stack_t*)cpv_second);
}

void fun_equal_string(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = string_equal((string_t*)cpv_first, (string_t*)cpv_second);
}

void fun_equal_pair(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = pair_equal((pair_t*)cpv_first, (pair_t*)cpv_second);
}

void fun_equal_set(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = set_equal((set_t*)cpv_first, (set_t*)cpv_second);
}

void fun_equal_map(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = map_equal((map_t*)cpv_first, (map_t*)cpv_second);
}

void fun_equal_multiset(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = multiset_equal((multiset_t*)cpv_first, (multiset_t*)cpv_second);
}

void fun_equal_multimap(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = multimap_equal((multimap_t*)cpv_first, (multimap_t*)cpv_second);
}

void fun_equal_hash_set(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_set_equal((hash_set_t*)cpv_first, (hash_set_t*)cpv_second);
}

void fun_equal_hash_map(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_map_equal((hash_map_t*)cpv_first, (hash_map_t*)cpv_second);
}

void fun_equal_hash_multiset(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_multiset_equal((hash_multiset_t*)cpv_first, (hash_multiset_t*)cpv_second);
}

void fun_equal_hash_multimap(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_multimap_equal((hash_multimap_t*)cpv_first, (hash_multimap_t*)cpv_second);
}

void fun_equal_basic_string(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = basic_string_equal((basic_string_t*)cpv_first, (basic_string_t*)cpv_second);
}

#ifndef _MSC_VER
void fun_equal_long_long(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(long long*)cpv_first == *(long long*)cpv_second ? true : false;
}

void fun_equal_ulong_long(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(unsigned long long*)cpv_first == *(unsigned long long*)cpv_second ? true : false;
}
#endif

/**
 * Not equal.
 */
void fun_not_equal_char(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(char*)cpv_first != *(char*)cpv_second ? true : false;
}

void fun_not_equal_uchar(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(unsigned char*)cpv_first != *(unsigned char*)cpv_second ? true : false;
}

void fun_not_equal_short(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(short*)cpv_first != *(short*)cpv_second ? true : false;
}

void fun_not_equal_ushort(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(unsigned short*)cpv_first != *(unsigned short*)cpv_second ? true : false;
}

void fun_not_equal_int(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(int*)cpv_first != *(int*)cpv_second ? true : false;
}

void fun_not_equal_uint(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(unsigned int*)cpv_first != *(unsigned int*)cpv_second ? true : false;
}

void fun_not_equal_long(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(long*)cpv_first != *(long*)cpv_second ? true : false;
}

void fun_not_equal_ulong(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(unsigned long*)cpv_first != *(unsigned long*)cpv_second ? true : false;
}

void fun_not_equal_float(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(float*)cpv_first - *(float*)cpv_second >= FLT_EPSILON ||
        *(float*)cpv_first - *(float*)cpv_second <= -FLT_EPSILON ? true : false;
}

void fun_not_equal_double(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(double*)cpv_first - *(double*)cpv_second >= DBL_EPSILON ||
        *(double*)cpv_first - *(double*)cpv_second <= -DBL_EPSILON ? true : false;
}

void fun_not_equal_long_double(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(long double*)cpv_first - *(long double*)cpv_second >= LDBL_EPSILON ||
        *(long double*)cpv_first - *(long double*)cpv_second <= -LDBL_EPSILON ? true : false;
}

void fun_not_equal_cstr(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    char* s_first = NULL;
    char* s_second = NULL;
    size_t t_firstlen = 0;
    size_t t_secondlen = 0;
    size_t t_len = 0;

    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    s_first = (char*)cpv_first;
    s_second = (char*)cpv_second;
    t_firstlen = strlen(s_first);
    t_secondlen = strlen(s_second);
    t_len = t_firstlen > t_secondlen ? t_firstlen : t_secondlen;

    *(bool_t*)pv_output = strncmp(s_first, s_second, t_len) != 0 ? true : false;
}

void fun_not_equal_pointer(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(void**)cpv_first != *(void**)cpv_second ? true : false;
}

void fun_not_equal_vector(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = vector_not_equal((vector_t*)cpv_first, (vector_t*)cpv_second);
}

void fun_not_equal_deque(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = deque_not_equal((deque_t*)cpv_first, (deque_t*)cpv_second);
}

void fun_not_equal_list(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = list_not_equal((list_t*)cpv_first, (list_t*)cpv_second);
}

void fun_not_equal_slist(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = slist_not_equal((slist_t*)cpv_first, (slist_t*)cpv_second);
}

void fun_not_equal_queue(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = queue_not_equal((queue_t*)cpv_first, (queue_t*)cpv_second);
}

void fun_not_equal_stack(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = stack_not_equal((stack_t*)cpv_first, (stack_t*)cpv_second);
}

void fun_not_equal_string(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = string_not_equal((string_t*)cpv_first, (string_t*)cpv_second);
}

void fun_not_equal_pair(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = pair_not_equal((pair_t*)cpv_first, (pair_t*)cpv_second);
}

void fun_not_equal_set(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = set_not_equal((set_t*)cpv_first, (set_t*)cpv_second);
}

void fun_not_equal_map(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = map_not_equal((map_t*)cpv_first, (map_t*)cpv_second);
}

void fun_not_equal_multiset(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = multiset_not_equal((multiset_t*)cpv_first, (multiset_t*)cpv_second);
}

void fun_not_equal_multimap(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = multimap_not_equal((multimap_t*)cpv_first, (multimap_t*)cpv_second);
}

void fun_not_equal_hash_set(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_set_not_equal((hash_set_t*)cpv_first, (hash_set_t*)cpv_second);
}

void fun_not_equal_hash_map(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_map_not_equal((hash_map_t*)cpv_first, (hash_map_t*)cpv_second);
}

void fun_not_equal_hash_multiset(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_multiset_not_equal((hash_multiset_t*)cpv_first, (hash_multiset_t*)cpv_second);
}

void fun_not_equal_hash_multimap(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_multimap_not_equal((hash_multimap_t*)cpv_first, (hash_multimap_t*)cpv_second);
}

void fun_not_equal_basic_string(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = basic_string_not_equal((basic_string_t*)cpv_first, (basic_string_t*)cpv_second);
}

#ifndef _MSC_VER
void fun_not_equal_long_long(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(long long*)cpv_first != *(long long*)cpv_second ? true : false;
}

void fun_not_equal_ulong_long(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(unsigned long long*)cpv_first != *(unsigned long long*)cpv_second ? true : false;
}
#endif

/**
 * Greater.
 */
void fun_greater_char(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(char*)cpv_first > *(char*)cpv_second ? true : false;
}

void fun_greater_uchar(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(unsigned char*)cpv_first > *(unsigned char*)cpv_second ? true : false;
}

void fun_greater_short(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(short*)cpv_first > *(short*)cpv_second ? true : false;
}

void fun_greater_ushort(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(unsigned short*)cpv_first > *(unsigned short*)cpv_second ? true : false;
}

void fun_greater_int(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(int*)cpv_first > *(int*)cpv_second ? true : false;
}

void fun_greater_uint(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(unsigned int*)cpv_first > *(unsigned int*)cpv_second ? true : false;
}

void fun_greater_long(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(long*)cpv_first > *(long*)cpv_second ? true : false;
}

void fun_greater_ulong(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(unsigned long*)cpv_first > *(unsigned long*)cpv_second ? true : false;
}

void fun_greater_float(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(float*)cpv_first - *(float*)cpv_second >= FLT_EPSILON ? true : false;
}

void fun_greater_double(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(double*)cpv_first - *(double*)cpv_second >= DBL_EPSILON ? true : false;
}

void fun_greater_long_double(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(long double*)cpv_first - *(long double*)cpv_second >= LDBL_EPSILON ? true : false;
}

void fun_greater_cstr(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    char* s_first = NULL;
    char* s_second = NULL;
    size_t t_firstlen = 0;
    size_t t_secondlen = 0;
    size_t t_len = 0;

    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    s_first = (char*)cpv_first;
    s_second = (char*)cpv_second;
    t_firstlen = strlen(s_first);
    t_secondlen = strlen(s_second);
    t_len = t_firstlen > t_secondlen ? t_firstlen : t_secondlen;

    *(bool_t*)pv_output = strncmp(s_first, s_second, t_len) > 0 ? true : false;
}

void fun_greater_pointer(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(void**)cpv_first > *(void**)cpv_second ? true : false;
}

void fun_greater_vector(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = vector_greater((vector_t*)cpv_first, (vector_t*)cpv_second);
}

void fun_greater_deque(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = deque_greater((deque_t*)cpv_first, (deque_t*)cpv_second);
}

void fun_greater_list(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = list_greater((list_t*)cpv_first, (list_t*)cpv_second);
}

void fun_greater_slist(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = slist_greater((slist_t*)cpv_first, (slist_t*)cpv_second);
}

void fun_greater_queue(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = queue_greater((queue_t*)cpv_first, (queue_t*)cpv_second);
}

void fun_greater_stack(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = stack_greater((stack_t*)cpv_first, (stack_t*)cpv_second);
}

void fun_greater_string(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = string_greater((string_t*)cpv_first, (string_t*)cpv_second);
}

void fun_greater_pair(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = pair_greater((pair_t*)cpv_first, (pair_t*)cpv_second);
}

void fun_greater_set(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = set_greater((set_t*)cpv_first, (set_t*)cpv_second);
}

void fun_greater_map(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = map_greater((map_t*)cpv_first, (map_t*)cpv_second);
}

void fun_greater_multiset(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = multiset_greater((multiset_t*)cpv_first, (multiset_t*)cpv_second);
}

void fun_greater_multimap(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = multimap_greater((multimap_t*)cpv_first, (multimap_t*)cpv_second);
}

void fun_greater_hash_set(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_set_greater((hash_set_t*)cpv_first, (hash_set_t*)cpv_second);
}

void fun_greater_hash_map(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_map_greater((hash_map_t*)cpv_first, (hash_map_t*)cpv_second);
}

void fun_greater_hash_multiset(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_multiset_greater((hash_multiset_t*)cpv_first, (hash_multiset_t*)cpv_second);
}

void fun_greater_hash_multimap(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_multimap_greater((hash_multimap_t*)cpv_first, (hash_multimap_t*)cpv_second);
}

void fun_greater_basic_string(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = basic_string_greater((basic_string_t*)cpv_first, (basic_string_t*)cpv_second);
}

#ifndef _MSC_VER
void fun_greater_long_long(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(long long*)cpv_first > *(long long*)cpv_second ? true : false;
}

void fun_greater_ulong_long(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(unsigned long long*)cpv_first > *(unsigned long long*)cpv_second ? true : false;
}
#endif

/**
 * Greater or equal.
 */
void fun_greater_equal_char(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(char*)cpv_first >= *(char*)cpv_second ? true : false;
}

void fun_greater_equal_uchar(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(unsigned char*)cpv_first >= *(unsigned char*)cpv_second ? true : false;
}

void fun_greater_equal_short(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(short*)cpv_first >= *(short*)cpv_second ? true : false;
}

void fun_greater_equal_ushort(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(unsigned short*)cpv_first >= *(unsigned short*)cpv_second ? true : false;
}

void fun_greater_equal_int(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(int*)cpv_first >= *(int*)cpv_second ? true : false;
}

void fun_greater_equal_uint(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(unsigned int*)cpv_first >= *(unsigned int*)cpv_second ? true : false;
}

void fun_greater_equal_long(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(long*)cpv_first >= *(long*)cpv_second ? true : false;
}

void fun_greater_equal_ulong(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(unsigned long*)cpv_first >= *(unsigned long*)cpv_second ? true : false;
}

void fun_greater_equal_float(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(float*)cpv_first - *(float*)cpv_second > -FLT_EPSILON ? true : false;
}

void fun_greater_equal_double(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(double*)cpv_first - *(double*)cpv_second > -DBL_EPSILON ? true : false;
}

void fun_greater_equal_long_double(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(long double*)cpv_first - *(long double*)cpv_second > -LDBL_EPSILON ? true : false;
}

void fun_greater_equal_cstr(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    char* s_first = NULL;
    char* s_second = NULL;
    size_t t_firstlen = 0;
    size_t t_secondlen = 0;
    size_t t_len = 0;

    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    s_first = (char*)cpv_first;
    s_second = (char*)cpv_second;
    t_firstlen = strlen(s_first);
    t_secondlen = strlen(s_second);
    t_len = t_firstlen > t_secondlen ? t_firstlen : t_secondlen;

    *(bool_t*)pv_output = strncmp(s_first, s_second, t_len) >= 0 ? true : false;
}

void fun_greater_equal_pointer(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(void**)cpv_first >= *(void**)cpv_second ? true : false;
}

void fun_greater_equal_vector(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = vector_greater_equal((vector_t*)cpv_first, (vector_t*)cpv_second);
}

void fun_greater_equal_deque(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = deque_greater_equal((deque_t*)cpv_first, (deque_t*)cpv_second);
}

void fun_greater_equal_list(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = list_greater_equal((list_t*)cpv_first, (list_t*)cpv_second);
}

void fun_greater_equal_slist(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = slist_greater_equal((slist_t*)cpv_first, (slist_t*)cpv_second);
}

void fun_greater_equal_queue(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = queue_greater_equal((queue_t*)cpv_first, (queue_t*)cpv_second);
}

void fun_greater_equal_stack(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = stack_greater_equal((stack_t*)cpv_first, (stack_t*)cpv_second);
}

void fun_greater_equal_string(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = string_greater_equal((string_t*)cpv_first, (string_t*)cpv_second);
}

void fun_greater_equal_pair(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = pair_greater_equal((pair_t*)cpv_first, (pair_t*)cpv_second);
}

void fun_greater_equal_set(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = set_greater_equal((set_t*)cpv_first, (set_t*)cpv_second);
}

void fun_greater_equal_map(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = map_greater_equal((map_t*)cpv_first, (map_t*)cpv_second);
}

void fun_greater_equal_multiset(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = multiset_greater_equal((multiset_t*)cpv_first, (multiset_t*)cpv_second);
}

void fun_greater_equal_multimap(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = multimap_greater_equal((multimap_t*)cpv_first, (multimap_t*)cpv_second);
}

void fun_greater_equal_hash_set(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_set_greater_equal((hash_set_t*)cpv_first, (hash_set_t*)cpv_second);
}

void fun_greater_equal_hash_map(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_map_greater_equal((hash_map_t*)cpv_first, (hash_map_t*)cpv_second);
}

void fun_greater_equal_hash_multiset(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_multiset_greater_equal((hash_multiset_t*)cpv_first, (hash_multiset_t*)cpv_second);
}

void fun_greater_equal_hash_multimap(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_multimap_greater_equal((hash_multimap_t*)cpv_first, (hash_multimap_t*)cpv_second);
}

void fun_greater_equal_basic_string(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = basic_string_greater_equal((basic_string_t*)cpv_first, (basic_string_t*)cpv_second);
}

#ifndef _MSC_VER
void fun_greater_equal_long_long(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(long long*)cpv_first >= *(long long*)cpv_second ? true : false;
}

void fun_greater_equal_ulong_long(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(unsigned long long*)cpv_first >= *(unsigned long long*)cpv_second ? true : false;
}
#endif

/**
 * Less.
 */
void fun_less_char(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(char*)cpv_first < *(char*)cpv_second ? true : false;
}

void fun_less_uchar(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(unsigned char*)cpv_first < *(unsigned char*)cpv_second ? true : false;
}

void fun_less_short(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(short*)cpv_first < *(short*)cpv_second ? true : false;
}

void fun_less_ushort(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(unsigned short*)cpv_first < *(unsigned short*)cpv_second ? true : false;
}

void fun_less_int(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}

void fun_less_uint(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(unsigned int*)cpv_first < *(unsigned int*)cpv_second ? true : false;
}

void fun_less_long(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(long*)cpv_first < *(long*)cpv_second ? true : false;
}

void fun_less_ulong(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(unsigned long*)cpv_first < *(unsigned long*)cpv_second ? true : false;
}

void fun_less_float(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(float*)cpv_first - *(float*)cpv_second < -FLT_EPSILON ? true : false;
}

void fun_less_double(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(double*)cpv_first - *(double*)cpv_second < -DBL_EPSILON ? true : false;
}

void fun_less_long_double(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(long double*)cpv_first - *(long double*)cpv_second < -LDBL_EPSILON ? true : false;
}

void fun_less_cstr(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    char* s_first = NULL;
    char* s_second = NULL;
    size_t t_firstlen = 0;
    size_t t_secondlen = 0;
    size_t t_len = 0;

    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    s_first = (char*)cpv_first;
    s_second = (char*)cpv_second;
    t_firstlen = strlen(s_first);
    t_secondlen = strlen(s_second);
    t_len = t_firstlen > t_secondlen ? t_firstlen : t_secondlen;

    *(bool_t*)pv_output = strncmp(s_first, s_second, t_len) < 0 ? true : false;
}

void fun_less_pointer(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(void**)cpv_first < *(void**)cpv_second ? true : false;
}

void fun_less_vector(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = vector_less((vector_t*)cpv_first, (vector_t*)cpv_second);
}

void fun_less_deque(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = deque_less((deque_t*)cpv_first, (deque_t*)cpv_second);
}

void fun_less_list(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = list_less((list_t*)cpv_first, (list_t*)cpv_second);
}

void fun_less_slist(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = slist_less((slist_t*)cpv_first, (slist_t*)cpv_second);
}

void fun_less_queue(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = queue_less((queue_t*)cpv_first, (queue_t*)cpv_second);
}

void fun_less_stack(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = stack_less((stack_t*)cpv_first, (stack_t*)cpv_second);
}

void fun_less_string(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = string_less((string_t*)cpv_first, (string_t*)cpv_second);
}

void fun_less_pair(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = pair_less((pair_t*)cpv_first, (pair_t*)cpv_second);
}

void fun_less_set(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = set_less((set_t*)cpv_first, (set_t*)cpv_second);
}

void fun_less_map(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = map_less((map_t*)cpv_first, (map_t*)cpv_second);
}

void fun_less_multiset(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = multiset_less((multiset_t*)cpv_first, (multiset_t*)cpv_second);
}

void fun_less_multimap(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = multimap_less((multimap_t*)cpv_first, (multimap_t*)cpv_second);
}

void fun_less_hash_set(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_set_less((hash_set_t*)cpv_first, (hash_set_t*)cpv_second);
}

void fun_less_hash_map(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_map_less((hash_map_t*)cpv_first, (hash_map_t*)cpv_second);
}

void fun_less_hash_multiset(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_multiset_less((hash_multiset_t*)cpv_first, (hash_multiset_t*)cpv_second);
}

void fun_less_hash_multimap(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_multimap_less((hash_multimap_t*)cpv_first, (hash_multimap_t*)cpv_second);
}

void fun_less_basic_string(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = basic_string_less((basic_string_t*)cpv_first, (basic_string_t*)cpv_second);
}

#ifndef _MSC_VER
void fun_less_long_long(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(long long*)cpv_first < *(long long*)cpv_second ? true : false;
}

void fun_less_ulong_long(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(unsigned long long*)cpv_first < *(unsigned long long*)cpv_second ? true : false;
}
#endif

/**
 * Less or equal.
 */
void fun_less_equal_char(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(char*)cpv_first <= *(char*)cpv_second ? true : false;
}

void fun_less_equal_uchar(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(unsigned char*)cpv_first <= *(unsigned char*)cpv_second ? true : false;
}

void fun_less_equal_short(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(short*)cpv_first <= *(short*)cpv_second ? true : false;
}

void fun_less_equal_ushort(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(unsigned short*)cpv_first <= *(unsigned short*)cpv_second ? true : false;
}

void fun_less_equal_int(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(int*)cpv_first <= *(int*)cpv_second ? true : false;
}

void fun_less_equal_uint(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(unsigned int*)cpv_first <= *(unsigned int*)cpv_second ? true : false;
}

void fun_less_equal_long(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(long*)cpv_first <= *(long*)cpv_second ? true : false;
}

void fun_less_equal_ulong(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(unsigned long*)cpv_first <= *(unsigned long*)cpv_second ? true : false;
}

void fun_less_equal_float(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(float*)cpv_first - *(float*)cpv_second < FLT_EPSILON ? true : false;
}

void fun_less_equal_double(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(double*)cpv_first - *(double*)cpv_second < DBL_EPSILON ? true : false;
}

void fun_less_equal_long_double(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(long double*)cpv_first - *(long double*)cpv_second < LDBL_EPSILON ? true : false;
}

void fun_less_equal_cstr(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    char* s_first = NULL;
    char* s_second = NULL;
    size_t t_firstlen = 0;
    size_t t_secondlen = 0;
    size_t t_len = 0;

    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    s_first = (char*)cpv_first;
    s_second = (char*)cpv_second;
    t_firstlen = strlen(s_first);
    t_secondlen = strlen(s_second);
    t_len = t_firstlen > t_secondlen ? t_firstlen : t_secondlen;

    *(bool_t*)pv_output = strncmp(s_first, s_second, t_len) <= 0 ? true : false;
}

void fun_less_equal_pointer(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(void**)cpv_first <= *(void**)cpv_second ? true : false;
}

void fun_less_equal_vector(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = vector_less_equal((vector_t*)cpv_first, (vector_t*)cpv_second);
}

void fun_less_equal_deque(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = deque_less_equal((deque_t*)cpv_first, (deque_t*)cpv_second);
}

void fun_less_equal_list(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = list_less_equal((list_t*)cpv_first, (list_t*)cpv_second);
}

void fun_less_equal_slist(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = slist_less_equal((slist_t*)cpv_first, (slist_t*)cpv_second);
}

void fun_less_equal_queue(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = queue_less_equal((queue_t*)cpv_first, (queue_t*)cpv_second);
}

void fun_less_equal_stack(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = stack_less_equal((stack_t*)cpv_first, (stack_t*)cpv_second);
}

void fun_less_equal_string(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = string_less_equal((string_t*)cpv_first, (string_t*)cpv_second);
}

void fun_less_equal_pair(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = pair_less_equal((pair_t*)cpv_first, (pair_t*)cpv_second);
}

void fun_less_equal_set(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = set_less_equal((set_t*)cpv_first, (set_t*)cpv_second);
}

void fun_less_equal_map(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = map_less_equal((map_t*)cpv_first, (map_t*)cpv_second);
}

void fun_less_equal_multiset(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = multiset_less_equal((multiset_t*)cpv_first, (multiset_t*)cpv_second);
}

void fun_less_equal_multimap(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = multimap_less_equal((multimap_t*)cpv_first, (multimap_t*)cpv_second);
}

void fun_less_equal_hash_set(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_set_less_equal((hash_set_t*)cpv_first, (hash_set_t*)cpv_second);
}

void fun_less_equal_hash_map(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_map_less_equal((hash_map_t*)cpv_first, (hash_map_t*)cpv_second);
}

void fun_less_equal_hash_multiset(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_multiset_less_equal((hash_multiset_t*)cpv_first, (hash_multiset_t*)cpv_second);
}

void fun_less_equal_hash_multimap(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_multimap_less_equal((hash_multimap_t*)cpv_first, (hash_multimap_t*)cpv_second);
}

void fun_less_equal_basic_string(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = basic_string_less_equal((basic_string_t*)cpv_first, (basic_string_t*)cpv_second);
}

#ifndef _MSC_VER
void fun_less_equal_long_long(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(long long*)cpv_first <= *(long long*)cpv_second ? true : false;
}

void fun_less_equal_ulong_long(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(unsigned long long*)cpv_first <= *(unsigned long long*)cpv_second ? true : false;
}
#endif

/* logical */
/**
 * Logical and.
 */
void fun_logical_and_cstl_bool(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(bool_t*)cpv_first && *(bool_t*)cpv_second;
}

#ifndef _MSC_VER
void fun_logical_and_bool(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(_Bool*)cpv_first && *(_Bool*)cpv_second;
}
#endif

/**
 * Logical or.
 */
void fun_logical_or_cstl_bool(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(bool_t*)cpv_first || *(bool_t*)cpv_second;
}

#ifndef _MSC_VER
void fun_logical_or_bool(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(_Bool*)cpv_first || *(_Bool*)cpv_second;
}
#endif

/**
 * Logical not.
 */
void fun_logical_not_cstl_bool(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);

    *(bool_t*)pv_output = !*(bool_t*)cpv_input;
}

#ifndef _MSC_VER
void fun_logical_not_bool(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);

    *(bool_t*)pv_output = !*(_Bool*)cpv_input;
}
#endif

/**
 * Random number.
 */
void fun_random_number(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);

    srand((unsigned int)time(NULL) + rand());
    *(size_t*)pv_output = *(size_t*)cpv_input != 0 ? rand() % *(size_t*)cpv_input : 0;
}

/* default unary and binary function */
/**
 * Default unary function.
 */
void fun_default_unary(const void* cpv_input, void* pv_output)
{
    void* pv_avoidwarning1 = NULL;
    void* pv_avoidwarning2 = NULL;
    pv_avoidwarning1 = (void*)cpv_input;
    pv_avoidwarning2 = (void*)pv_output;
}

/**
 * Default binary function.
 */
void fun_default_binary(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    void* pv_avoidwarning1 = NULL;
    void* pv_avoidwarning2 = NULL;
    void* pv_avoidwarning3 = NULL;
    pv_avoidwarning1 = (void*)cpv_first;
    pv_avoidwarning2 = (void*)cpv_second;
    pv_avoidwarning3 = (void*)pv_output;
}

/** local function implementation section **/

/** eof **/

