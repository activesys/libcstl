/*
 *  The implement of cstl type parse functions.
 *  Copyright (C)  2008 - 2012  Wangbo
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

/** exported global variable declaration section **/

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

