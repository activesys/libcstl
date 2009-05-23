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
typedef int myint_t;
typedef output_iterator_t myiter_t;

#define mymacro(type) printf("%s\n", #type)

/** exported function implementation section **/
void test_type(void)
{
    bool_t t_b = false;

    t_b = type_duplicate(myiter_t, list_iterator_t);
    type_debug();
    t_b ? printf("true\n") : printf("false\n");
}

/** local function implementation section **/

/** eof **/

