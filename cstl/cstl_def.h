/*
 *  The common define.
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

#ifndef _CSTL_DEF_H_
#define _CSTL_DEF_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/
#ifdef HAVE_CONFIG_H
#   include <config.h>
#endif
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <float.h>
#include <time.h>
#ifndef _MSC_VER
#   include <stdbool.h>
#endif

/** constant declaration and macro section **/
#ifdef _CSTL_UNIT_TESTING
    extern void  mock_assert(const int result, const char* const expression, const char* const file, const int line);
    /*
    extern void* _test_malloc(const size_t size, const char* file, const int line);
    extern void* _test_calloc(const size_t num, const size_t size, const char* file, const int line);
    extern void* _test_free(void* const prt, const char* file, const int line);
    */

#   undef assert
#   define assert(expression) mock_assert((int)(expression), #expression, __FILE__, __LINE__)
/*
#   define malloc(size)       _test_malloc((size), __FILE__, __LINE__)
#   define calloc(num, size)  _test_calloc((num), (size), __FILE__, __LINE__)
#   define free(ptr)          _test_free((ptr), __FILE__, __LINE__)
*/
#    ifdef NDEBUG
#        undef NDEBUG
#    endif
#endif /* _CSTL_UNIT_TESTING */

#ifdef _MSC_VER
#   define va_copy(dest, src) ((dest) = (src))
#endif

/**
 * libcstl version macro.
 */
#define CSTL_VERSION             20300 /* libcstl version 2.3.0 */
#define CSTL_MAJOR_VERSION       2
#define CSTL_MINOR_VERSION       3
#define CSTL_REVISION_VERSION    0

#ifdef _MSC_VER
/**
 * for bool_t type
 */
#define false   0
#define true    1
#endif

/** data type declaration and struct, union, enum section **/
typedef unsigned char            _byte_t;
typedef size_t                   bool_t;         /* declaration for bool type */

/** exported global variable declaration section **/

/** exported function prototype section **/

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_DEF_H_ */
/** eof **/

