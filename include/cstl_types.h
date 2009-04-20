/*
 *  This header file declaration some type definition, micors for cstl.
 *  Copyright (C)  2008 2009  Wangbo
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
 *  Author Email: activesys.wb@gmail.com
 *                activesys@sina.com.cn
 */

#ifndef _CSTL_TYPES_H
#define _CSTL_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
#define FALSE   0               /* declaration false bool type */
#define false   0
#define TRUE    1               /* declaration true bool type */
#define true    1

/* c built-in type */
#define _INT_TYPE                    "int"
#define _SIGNED_INT_TYPE             "signed int"
#define _SIGNED_TYPE                 "signed"
#define _UNSIGNED_INT_TYPE           "unsigned int"
#define _UNSIGNED_TYPE               "unsigned"
#define _CHAR_TYPE                   "char"
#define _SIGNED_CHAR_TYPE            "signed char"
#define _UNSIGNED_CHAR_TYPE          "unsigned char"
#define _FLOAT_TYPE                  "float"
#define _DOUBLE_TYPE                 "double"
#define _SIGNED_SHORT_INT_TYPE       "signed short int"
#define _SIGNED_SHORT_TYPE           "signed short"
#define _SHORT_INT_TYPE              "short int"
#define _SHORT_TYPE                  "short"
#define _UNSIGNED_SHORT_INT_TYPE     "unsigned short int"
#define _UNSIGNED_SHORT_TYPE         "unsigned short"
#define _LONG_TYPE                   "long"
#define _LONG_INT_TYPE               "long int"
#define _SIGNED_LONG_TYPE            "signed long"
#define _SIGNED_LONG_INT_TYPE        "signed long int"
#define _UNSIGNED_LONG_TYPE          "unsigned long"
#define _UNSIGNED_LONG_INT_TYPE      "unsigned long int"
/* cstl type */
#define _BOOL_TYPE                   "bool_t"

#define _ELEM_TYPE_NAME_SIZE         32 /* the element type name size */

/* cstl container type */
#define _CSTL_LEFT_BRACKET           '<'
#define _CSTL_RIGHT_BRACKET          '>'
#define _CSTL_COMMA                  ','
/* set */
#define _SET_IDENTIFY                "set"
#define _SET_LEFT_BRACKET            "<"
#define _SET_RIGHT_BRACKET           ">"
#define _SET_ITERATOR_NAME           "set_iterator_t"
/* multiset */
#define _MULTISET_IDENTIFY           "multiset"
#define _MULTISET_LEFT_BRACKET       "<"
#define _MULTISET_RIGHT_BRACKET      ">"
#define _MULTISET_ITERATOR_NAME      "multiset_iterator_t"
/* map */
#define _MAP_IDENTIFY                "map"
#define _MAP_LEFT_BRACKET            "<"
#define _MAP_RIGHT_BRACKET           ">"
#define _MAP_COMMA                   ","
#define _MAP_ITERATOR_NAME           "map_iterator_t"
/* multimap */
#define _MULTIMAP_IDENTIFY           "multimap"
#define _MULTIMAP_LEFT_BRACKET       "<"
#define _MULTIMAP_RIGHT_BRACKET      ">"
#define _MULTIMAP_COMMA              ","
#define _MULTIMAP_ITERATOR_NAME      "multimap_iterator_t"
/* hash_set */
#define _HASH_SET_IDENTIFY           "hash_set"
#define _HASH_SET_LEFT_BRACKET       "<"
#define _HASH_SET_RIGHT_BRACKET      ">"
#define _HASH_SET_ITERATOR_NAME      "hash_set_iterator_t"
/* hash_multiset */
#define _HASH_MULTISET_IDENTIFY      "hash_multiset"
#define _HASH_MULTISET_LEFT_BRACKET  "<"
#define _HASH_MULTISET_RIGHT_BRACKET ">"
#define _HASH_MULTISET_ITERATOR_NAME "hash_multiset_iterator_t"
/* hash_map */
#define _HASH_MAP_IDENTIFY           "hash_map"
#define _HASH_MAP_LEFT_BRACKET       "<"
#define _HASH_MAP_RIGHT_BRACKET      ">"
#define _HASH_MAP_COMMA              ","
#define _HASH_MAP_ITERATOR_NAME      "hash_map_iterator_t"
/* hash_multimap */
#define _HASH_MULTIMAP_IDENTIFY      "hash_multimap"
#define _HASH_MULTIMAP_LEFT_BRACKET  "<"
#define _HASH_MULTIMAP_RIGHT_BRACKET ">"
#define _HASH_MULTIMAP_COMMA         ","
#define _HASH_MULTIMAP_ITERATOR_NAME "hash_multimap_iterator_t"
/* basic_string */
#define _BASIC_STRING_IDENTIFY       "basic_string"
#define _BASIC_STRING_LEFT_BRACKET   "<"
#define _BASIC_STRING_RIGHT_BRACKET  ">"
#define _BASIC_STRING_ITERATOR_NAME  "basic_string_iterator_t"

/* 
 * cstl types unification:
 * the macro CSTL_TYPES_UNIFICATION is definied for types unification,
 * if CSTL_TYPES_UNIFICATION = 1
 * e.g. cstl will deal "signed int" and "int" with different type.
 * if CSTL_TYPES_UNIFICATION = 2
 * e.g. cstl will deal "signed int" and "int" with the same type.
 * if CSTL_TYPES_UNIFICATION = 3
 * e.g. cstl will deal "unsigned int" and "int" with the same type.
 * if CSTL_TYPES_UNIFICATION = 4
 * e.g. cstl will deal "short" and "int" with the same type when the 
 * sizeof(short) == sizeof(int) or deal "long" and "int" with the same
 * type when sizeof(long) == sizeof(int).
 * when CSTL_TYPES_UNIFICATION greater then 4 will error.
 *
 * don't defined CSTL_TYPES_UNIFICATION will default define with value 2.
 */
#ifndef CSTL_TYPES_UNIFICATION
#define CSTL_TYPES_UNIFICATION   2
#endif

/** data type declaration and struct, union, enum section **/
typedef int     bool_t;         /* declaration for bool type */

/* note: the last parameter is for output */
typedef void (*unary_function_t)(const void*, void*);
typedef void (*binary_function_t)(const void*, const void*, void*);

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _unify_types
 *        Parameters: in) t_typesize: size_t
 *                          the element type size.
 *                    in) sz_typename: char*
 *                          the element type name.
 *           Returns: void
 *       Description: unify the types.
 *
 * ----------------------------------------------------------------------------
 */
extern void _unify_types(size_t t_typesize, char* sz_typename);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _get_varg_value
 *        Parameters: out) pv_output: void*
 *                          the output value.
 *                    in) val_elemlist: va_list
 *                          value list.
 *                    in) t_typesize: size_t
 *                          the element type size.
 *                    in) sz_typename: char*
 *                          the element type name.
 *           Returns: void
 *       Description: get the val_elemlist value.
 *
 * ----------------------------------------------------------------------------
 */
extern void _get_varg_value(
    void* pv_output,
    va_list val_elemlist,
    size_t t_typesize,
    const char* s_typename);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _get_builtin_type
 *        Parameters: in) s_typename: const char*
 *                          type name
 *                    out) s_builtin: char*
 *                          build in type.
 *           Returns: void
 *       Description: drop the set mulitset e.g. identify.
 *
 * ----------------------------------------------------------------------------
 */
extern void _get_builtin_type(const char* s_typename, char* s_builtin);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _get_cmp_function
 *        Parameters: in) s_typename: const char*
 *                          type name
 *           Returns: int (*)(const void*, const void*);
 *       Description: get default compare function.
 *
 * ----------------------------------------------------------------------------
 */
extern int (*_get_cmp_function(const char* s_typename))(const void*, const void*);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_TYPES_H */
/** eof **/

