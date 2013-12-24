/*
 *  The implement of cstl type parse functions.
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

#ifndef _CSTL_TYPES_PARSE_H_
#define _CSTL_TYPES_PARSE_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
typedef enum _tagtypelex
{
    _LEX_START, _LEX_IN_IDENTIFIER, _LEX_ACCEPT
}_typelex_t;

typedef enum _tagtypetoken
{
    /* invalid token */
    _TOKEN_INVALID,
    /* EOI */
    _TOKEN_END_OF_INPUT,
    /* c builtin */
    _TOKEN_KEY_CHAR, _TOKEN_KEY_SHORT, _TOKEN_KEY_INT, _TOKEN_KEY_LONG, _TOKEN_KEY_FLOAT,
    _TOKEN_KEY_DOUBLE, _TOKEN_KEY_SIGNED, _TOKEN_KEY_UNSIGNED, _TOKEN_KEY_VOID,
    _TOKEN_KEY_CSTL_BOOL, _TOKEN_KEY_BOOL,
    /* user define */
    _TOKEN_KEY_STRUCT, _TOKEN_KEY_ENUM, _TOKEN_KEY_UNION, _TOKEN_IDENTIFIER,
    /* cstl container */
    _TOKEN_KEY_VECTOR, _TOKEN_KEY_LIST, _TOKEN_KEY_SLIST, _TOKEN_KEY_DEQUE, _TOKEN_KEY_STACK,
    _TOKEN_KEY_QUEUE, _TOKEN_KEY_PRIORITY_QUEUE, _TOKEN_KEY_SET, _TOKEN_KEY_MAP,
    _TOKEN_KEY_MULTISET, _TOKEN_KEY_MULTIMAP, _TOKEN_KEY_HASH_SET, _TOKEN_KEY_HASH_MAP,
    _TOKEN_KEY_HASH_MULTISET, _TOKEN_KEY_HASH_MULTIMAP, _TOKEN_KEY_PAIR, _TOKEN_KEY_STRING,
    _TOKEN_KEY_BASIC_STRING,
    /* cstl iterator */
    _TOKEN_KEY_ITERATOR, _TOKEN_KEY_VECTOR_ITERATOR, _TOKEN_KEY_LIST_ITERATOR,
    _TOKEN_KEY_SLIST_ITERATOR, _TOKEN_KEY_DEQUE_ITERATOR, _TOKEN_KEY_SET_ITERATOR,
    _TOKEN_KEY_MAP_ITERATOR, _TOKEN_KEY_MULTISET_ITERATOR, _TOKEN_KEY_MULTIMAP_ITERATOR,
    _TOKEN_KEY_HASH_SET_ITERATOR, _TOKEN_KEY_HASH_MAP_ITERATOR,
    _TOKEN_KEY_HASH_MULTISET_ITERATOR, _TOKEN_KEY_HASH_MULTIMAP_ITERATOR,
    _TOKEN_KEY_STRING_ITERATOR, _TOKEN_KEY_INPUT_ITERATOR, _TOKEN_KEY_OUTPUT_ITERATOR,
    _TOKEN_KEY_FORWARD_ITERATOR, _TOKEN_KEY_BIDIRECTIONAL_ITERATOR,
    _TOKEN_KEY_RANDOM_ACCESS_ITERATOR, _TOKEN_KEY_BASIC_STRING_ITERATOR,
    /* utility */
    _TOKEN_KEY_RANGE,
    /* sign */
    _TOKEN_SIGN_LEFT_BRACKET, _TOKEN_SIGN_RIGHT_BRACKET, _TOKEN_SIGN_COMMA, _TOKEN_SIGN_POINTER,
    _TOKEN_SIGN_SPACE,
    /* ROLLBACK */
    _TOKEN_ROLLBACK
}_typetoken_t;

typedef struct _tagtypeanalysis
{
    char         _s_typename[_TYPE_NAME_SIZE + 1];
    char         _s_tokentext[_TYPE_NAME_SIZE + 1];
    size_t       _t_index;
    _typetoken_t _t_token;
}_typeanalysis_t;

/** exported global variable declaration section **/
extern _typeanalysis_t _gt_typeanalysis;

/** exported function prototype section **/
/* the functions blow is used for analyse the type style */
/**
 * Normalize the typename, test the typename is valid or not and get the type style 
 * @param s_typename   input type name.
 * @param s_formalname formal name.
 * @return type style.
 * @remarks s_typename and s_formalname must be not NULL.
 */
extern _typestyle_t _type_get_style(const char* s_typename, char* s_formalname);
/**
 * Get the next toke from input string.
 * @return void.
 */
extern void _type_get_token(void);
/**
 * Rollback current token to input string.
 * @return void.
 */
extern void _type_token_rollback(void);
/**
 * Parse specific token, and get formal name.
 * @param s_formalname formal name.
 * @return bool_t.
 * @remarks s_formalname must be not NULL.
 */
extern bool_t _type_parse_c_builtin(char* s_formalname);
extern bool_t _type_parse_pointer_builtin(char* s_formalname);
extern bool_t _type_parse_pointer_suffix(char* s_formalname);
extern bool_t _type_parse_complex_long_suffix(char* s_formalname);
extern bool_t _type_parse_common_suffix(char* s_formalname);
extern bool_t _type_parse_simple_long_suffix(char* s_formalname);
extern bool_t _type_parse_simple_builtin(char* s_formalname);
extern bool_t _type_parse_unsigned_builtin(char* s_formalname);
extern bool_t _type_parse_complex_suffix(char* s_formalname);
extern bool_t _type_parse_signed_builtin(char* s_formalname);
extern bool_t _type_parse_user_define_type(char* s_formalname);
extern bool_t _type_parse_user_define(char* s_formalname);
extern bool_t _type_parse_sequence_name(char* s_formalname);
extern bool_t _type_parse_sequence(char* s_formalname);
extern bool_t _type_parse_relation_name(char* s_formalname);
extern bool_t _type_parse_iterator(char* s_formalname);
extern bool_t _type_parse_relation(char* s_formalname);
extern bool_t _type_parse_cstl_builtin(char* s_formalname);
extern bool_t _type_parse_type_descript(char* s_formalname);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_TYPES_PARSE_H_ */
/** eof **/

