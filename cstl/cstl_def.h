/*
 *  The common define.
 *  Copyright (C)  2008,2009,2010  Wangbo
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

#ifndef _CSTL_DEF_H
#define _CSTL_DEF_H

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
#endif /* _CSTL_UNIT_TESTING */

/**
 * libcstl version macro.
 */
#define CSTL_VERSION             20001 /* libcstl version 2.0.1 */
#define CSTL_MAJOR_VERSION       2
#define CSTL_MINOR_VERSION       0
#define CSTL_REVISION_VERSION    1

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_DEF_H */
/** eof **/

