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
    bool_t t_b = false;
    _typecontainer_t t_type;

    type_register(abc_t, NULL, NULL, NULL);
    type_register(char**, NULL, NULL, NULL);
    type_register(int*, NULL, NULL, NULL);
    type_register(unsigned long int*, NULL, NULL, NULL);
    _type_get_type(&t_type, "map_t         <            \
            unsigned \
            long \
            int             , hash_multiset_t   < \
set_t < \
            pair_t       < \
            abc_t             ,                    \
\
\
            random_access_iterator_t>\
\
>\
>\
>");
    type_debug();
    printf("%s:", t_type._sz_typename);
    if(t_type._pt_type != NULL)
    {
        printf("%s,%p", t_type._pt_type->_sz_typename, t_type._pt_type);
    }
    printf("\n");
}

/** local function implementation section **/

/** eof **/

