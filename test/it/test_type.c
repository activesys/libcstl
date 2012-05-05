/*
 *  The implement of types test.
 *  Copyright (c)  2008,2009,2010  Wangbo
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
#include <cstl/clist.h>

#include "test_type.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/
typedef struct _tagabc
{
    int a;
}abc_t;
typedef int abcdefgh;
typedef output_iterator_t myiter_t;

#define mymacro(type) printf("%s\n", #type)

/** exported function implementation section **/
void test_type(void)
{
#ifndef _WIN32
    _typeinfo_t t_type;
#endif
    type_register(struct _tagabc, NULL, NULL, NULL, NULL);
    type_duplicate(abc_t, struct _tagabc);
    type_register(struct _tagabc    *, NULL, NULL, NULL, NULL);
    type_duplicate(abc_t             *, struct   _tagabc*);
    type_register(abc_t ****, NULL, NULL, NULL, NULL);
    type_register(char**, NULL, NULL, NULL, NULL);
    type_register(int*, NULL, NULL, NULL, NULL);
    type_register(short int*  **   *  *, NULL, NULL, NULL, NULL);
    type_register(unsigned int*, NULL, NULL, NULL, NULL);
    type_register(signed char*     **** *****, NULL, NULL, NULL, NULL);
    type_register(long double      **, NULL, NULL, NULL, NULL);

    _type_debug();

#ifndef _WIN32
    _type_get_type(&t_type, "short");
    printf("%s:", t_type._s_typename);
    if(t_type._pt_type != NULL)
    {
        printf("%s,%p\n", t_type._pt_type->_s_typename, (void*)t_type._pt_type);
    }
    printf("%d\n", _type_is_same("int", "signed"));
    printf("%d\n", _type_is_same("long", "signed short"));
    printf("%d\n", _type_is_same("long double", "long double*"));
    printf("%d\n", _type_is_same("vector_t<abc_t>", "vector_t<struct _tagabc>"));
    printf("%d\n", _type_is_same("map_t<abc_t*,vector_t<pair_t<iterator_t,stack_t<char>>>>",
        "map_t<struct _tagabc*,vector_t<pair_t<string_iterator_t,stack_t<signed char>>>>"));
#endif
}

/** local function implementation section **/

/** eof **/

