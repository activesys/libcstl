/*
 *  * file description ... *
 *  Copyright (c) 2009 Wangbo
 *
 *  * copyright description ... *
 *
 *  Author e-mail: activesys.wb@gmail.com
 *                 activesys@sina.com.cn
 */

/** include section **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>

#include "cstl_alloc.h"
#include "cstl_types.h"
#include "clist.h"

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
    _typecontainer_t t_type;

    type_register(struct _tagabc, NULL, NULL, NULL);
    type_duplicate(abc_t, struct _tagabc);
    type_register(struct _tagabc    *, NULL, NULL, NULL);
    type_duplicate(abc_t             *, struct   _tagabc*);
    type_register(abc_t ****, NULL, NULL, NULL);
    type_register(char**, NULL, NULL, NULL);
    type_register(int*, NULL, NULL, NULL);
    type_register(short int*  **   *  *, NULL, NULL, NULL);
    type_register(unsigned int*, NULL, NULL, NULL);
    type_register(signed char*     **** *****, NULL, NULL, NULL);
    type_register(long double      **, NULL, NULL, NULL);
    type_debug();
    _type_get_type(&t_type, "short");
    printf("%s:", t_type._sz_typename);
    if(t_type._pt_type != NULL)
    {
        printf("%s,%p\n", t_type._pt_type->_sz_typename, (void*)t_type._pt_type);
    }
    printf("%d\n", _type_is_same("int", "signed"));
    printf("%d\n", _type_is_same("long", "signed short"));
    printf("%d\n", _type_is_same("long double", "long double*"));
    printf("%d\n", _type_is_same("vector_t<abc_t>", "vector_t<struct _tagabc>"));
    printf("%d\n", _type_is_same("map_t<abc_t*,vector_t<pair_t<iterator_t,stack_t<char>>>>",
        "map_t<struct _tagabc*,vector_t<pair_t<string_iterator_t,stack_t<signed char>>>>"));
}

/** local function implementation section **/

/** eof **/

