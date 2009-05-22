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

/** exported function implementation section **/
void test_type(void)
{
    type_register(abc_t, NULL, NULL, NULL);
    type_debug();
}

/** local function implementation section **/

/** eof **/

