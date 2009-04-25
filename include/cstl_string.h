/*
 *  The interface of string_t
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
 *  Author e-mail: activesys.wb@gmail.com
 *                 activesys@sina.com.cn
 */

#ifndef _CSTL_STRING_H
#define _CSTL_STRING_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
typedef basic_string_t string_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_init
 *        Parameters: in) pt_string: string_t*
 *           Returns: void
 *       Description: initialize the string.
 *
 * ----------------------------------------------------------------------------
 */
extern void string_init(string_t* pt_string);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_init_cstr
 *        Parameters: in) pt_string: string_t*
 *                    in) s_cstr: const char*
 *                          the value string for initialize the string.
 *           Returns: void
 *       Description: initialize the string with value string.
 *
 * ----------------------------------------------------------------------------
 */
extern void string_init_cstr(
    string_t* pt_string, const char* s_cstr);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_init_subcstr
 *        Parameters: in) pt_string: string_t*
 *                    in) s_cstr: const char*
 *                          the value string for initialize the string.
 *                    in) t_len: size_t
 *                          the initialize count.
 *           Returns: void
 *       Description: initialize the string with value string.
 *
 * ----------------------------------------------------------------------------
 */
extern void string_init_subcstr(
    string_t* pt_string, const char* s_cstr, size_t t_len);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_init_char
 *        Parameters: in) pt_string: string_t*
 *                    in) t_count: size_t
 *                          the initialize count.
 *                    in) c_char: char
 *                          character.
 *           Returns: void
 *       Description: initialize the string with value.
 *
 * ----------------------------------------------------------------------------
 */
extern void string_init_char(
    string_t* pt_string, size_t t_count, char c_char);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_init_copy
 *        Parameters: in) pt_stringdest: string_t*
 *                          the dest string.
 *                    in) cpt_string_src: const string_t*
 *                          the source string.
 *           Returns: void
 *       Description: the copy constructor.
 *
 * ----------------------------------------------------------------------------
 */
extern void string_init_copy(
    string_t* pt_string, const string_t* cpt_string_src);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_init_copy_substring
 *        Parameters: in) pt_string: string_t*
 *                          the dest string.
 *                    in) cpt_string_src: const string_t*
 *                          the source string.
 *                    in) t_pos: size_t
 *                          the start pos.
 *                    in) t_len: size_t
 *                          initialize count.
 *           Returns: void
 *       Description: the copy constructor.
 *
 * ----------------------------------------------------------------------------
 */
extern void string_init_copy_substring(
    string_t* pt_string, const string_t* cpt_string_src, size_t t_pos, size_t t_len);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_init_copy_range
 *        Parameters: in) pt_stringdest: string_t*
 *                          the dest string.
 *                    in) t_begin: string_iterator_t
 *                          the begin iterator.
 *                    in) t_end: string_iterator_t
 *                          the end iterator.
 *           Returns: void
 *       Description: the copy constructor with specific range.
 *
 * ----------------------------------------------------------------------------
 */
extern void string_init_copy_range(
    string_t* pt_string, string_iterator_t t_begin, string_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_destroy
 *        Parameters: in) pt_string: string_t*
 *           Returns: void
 *       Description: destroy the string.
 *
 * ----------------------------------------------------------------------------
 */
extern void string_destroy(string_t* pt_string);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_c_str
 *        Parameters: in) cpt_string: const string_t*
 *           Returns: const char*
 *       Description: return a pointer to a null-terminated array of element
 *                    representing the string's contents.
 *
 * ----------------------------------------------------------------------------
 */
extern const char* string_c_str(const string_t* cpt_string);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_data
 *        Parameters: in) cpt_string: const string_t*
 *           Returns: const char*
 *       Description: return a pointer to a array of element (not necessarily
 *                    null-terminated) representing the string's contents.
 *
 * ----------------------------------------------------------------------------
 */
extern const char* string_data(const string_t* cpt_string);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_copy
 *        Parameters: in) cpt_string: const string_t*
 *                          the string.
 *                    in) s_buffer: char*
 *                          buffer pointer
 *                    in) t_copysize: size_t
 *                          the element count copied.
 *                    in) t_copypos: size_t
 *                          the copy position.
 *           Returns: size_t
 *                          the number element of actually copied
 *       Description: the copy constructor with specific range.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t string_copy(
    const string_t* cpt_string, char* s_buffer, size_t t_copysize, size_t t_copypos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_size
 *        Parameters: in) cpt_string: const string_t*
 *                          the dest string.
 *           Returns: size_t
 *       Description: get the string size.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t string_size(const string_t* cpt_string);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_length
 *        Parameters: in) cpt_string: const string_t*
 *                          the dest string.
 *           Returns: size_t
 *       Description: get the string size.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t string_length(const string_t* cpt_string);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_empty
 *        Parameters: in) cpt_string: const string_t*
 *                          the dest string.
 *           Returns: bool_t
 *       Description: if the string is empty.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t string_empty(const string_t* cpt_string);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_max_size
 *        Parameters: in) cpt_string: const string_t*
 *                          the dest string.
 *           Returns: size_t
 *       Description: get the maximum capacity of string.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t string_max_size(const string_t* cpt_string);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_capacity
 *        Parameters: in) cpt_string: const string_t*
 *                          the dest string.
 *           Returns: size_t
 *       Description: get the capacity of string with out reallocation.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t string_capacity(const string_t* cpt_string);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_at
 *        Parameters: in) cpt_string: const string_t*
 *                          the string.
 *                    in) t_pos: size_t
 *                          the element pos.
 *           Returns: char*
 *                          the element pointer.
 *       Description: return the element with the n_elempos.
 *
 * ----------------------------------------------------------------------------
 */
extern char* string_at(const string_t* cpt_string, size_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_equal
 *        Parameters: in) cpt_stringfirst: const string_t*
 *                          the first string.
 *                    in) cpt_stringsecond: const string_t*
 *                          the second string.
 *           Returns: bool_t
 *       Description: return whether first string equal to second string.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t string_equal(
    const string_t* cpt_stringfirst, const string_t* cpt_stringsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_not_equal
 *        Parameters: in) cpt_stringfirst: const string_t*
 *                          the first string.
 *                    in) cpt_stringsecond: const string_t*
 *                          the second string.
 *           Returns: bool_t
 *       Description: return whether first string not equal to second string.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t string_not_equal(
    const string_t* cpt_stringfirst, const string_t* cpt_stringsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_less
 *        Parameters: in) cpt_stringfirst: const string_t*
 *                          the first string.
 *                    in) cpt_stringsecond: const string_t*
 *                          the second string.
 *           Returns: bool_t
 *       Description: return whether first string less then second string.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t string_less(
    const string_t* cpt_stringfirst, const string_t* cpt_stringsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_great
 *        Parameters: in) cpt_stringfirst: const string_t*
 *                          the first string.
 *                    in) cpt_stringsecond: const string_t*
 *                          the second string.
 *           Returns: bool_t
 *       Description: return whether first string greater then second string.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t string_great(
    const string_t* cpt_stringfirst, const string_t* cpt_stringsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_less_equal
 *        Parameters: in) cpt_stringfirst: const string_t*
 *                          the first string.
 *                    in) cpt_stringsecond: const string_t*
 *                          the second string.
 *           Returns: bool_t
 *       Description: return whether first string less then or equal to the 
 *                    second string.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t string_less_equal(
    const string_t* cpt_stringfirst, const string_t* cpt_stringsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_great_equal
 *        Parameters: in) cpt_stringfirst: const string_t*
 *                          the first string.
 *                    in) cpt_stringsecond: const string_t*
 *                          the second string.
 *           Returns: bool_t
 *       Description: return whether first string greater then or equal to the
 *                    second string.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t string_great_equal(
    const string_t* cpt_stringfirst, const string_t* cpt_stringsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_equal_cstr
 *        Parameters: in) cpt_stringfirst: const string_t*
 *                          the string.
 *                    in) s_cstr: const char*
 *                          value string.
 *           Returns: bool_t
 *       Description: return whether first string equal to value string.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t string_equal_cstr(
    const string_t* cpt_string, const char* s_cstr);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_not_equal_cstr
 *        Parameters: in) cpt_string: const string_t*
 *                          the string.
 *                    in) s_cstr: const char*
 *                          value string.
 *           Returns: bool_t
 *       Description: return whether first string not equal to value string.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t string_not_equal_cstr(
    const string_t* cpt_string, const char* s_cstr); 

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_less_cstr
 *        Parameters: in) cpt_string: const string_t*
 *                          the string.
 *                    in) s_cstr: const char*
 *                          value string.
 *           Returns: bool_t
 *       Description: return whether first string less then value string.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t string_less_cstr(
    const string_t* cpt_string, const char* s_cstr); 

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_great_cstr
 *        Parameters: in) cpt_string: const string_t*
 *                          the string.
 *                    in) s_cstr: const char*
 *                          value string.
 *           Returns: bool_t
 *       Description: return whether first string greater then value string.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t string_great_cstr(
    const string_t* cpt_string, const char* s_cstr); 

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_less_equal_cstr
 *        Parameters: in) cpt_string: const string_t*
 *                          the string.
 *                    in) s_cstr: const char*
 *                          value string.
 *           Returns: bool_t
 *       Description: return whether first string less then or equal to the 
 *                    value string.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t string_less_equal_cstr(
    const string_t* cpt_string, const char* s_cstr); 

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_great_equal_cstr
 *        Parameters: in) cpt_string: const string_t*
 *                          the string.
 *                    in) s_cstr: const char*
 *                          value string.
 *           Returns: bool_t
 *       Description: return whether first string greater then or equal to the
 *                    value string.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t string_great_equal_cstr(
    const string_t* cpt_string, const char* s_cstr); 

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_compare
 *        Parameters: in) cpt_stringfirst: const string_t*
 *                          the first string.
 *                    in) cpt_stringsecond: const string_t*
 *                          the second string.
 *           Returns: int
 *                          compare result < 0 or == 0 or > 0.
 *       Description: three-way lexicographical comparison of the first min(
 *                    t_stringlen, string length) and substr of this
 *                    string.
 *
 * ----------------------------------------------------------------------------
 */
extern int string_compare(
    const string_t* cpt_stringfirst, const string_t* cpt_stringsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_compare_substring_string
 *        Parameters: in) cpt_stringfirst: const string_t*
 *                          the first string.
 *                    in) t_firstpos: size_t
 *                          the first string start position.
 *                    in) t_firstlen: size_t
 *                          the first string compare length.
 *                    in) cpt_stringsecond: const string_t*
 *                          the second string.
 *           Returns: int
 *                          compare result < 0 or == 0 or > 0.
 *       Description: three-way lexicographical comparison of the first min(
 *                    t_stringlen, string length) and substr of this
 *                    string.
 *
 * ----------------------------------------------------------------------------
 */
extern int string_compare_substring_string(
    const string_t* cpt_stringfirst, 
    size_t t_firstpos, 
    size_t t_firstlen,
    const string_t* cpt_stringsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_compare_substring_substring
 *        Parameters: in) cpt_stringfirst: const string_t*
 *                          the first string.
 *                    in) t_firstpos: size_t
 *                          the first string start position.
 *                    in) t_firstlen: size_t
 *                          the first string compare length.
 *                    in) cpt_stringsecond: const string_t*
 *                          the second string.
 *                    in) t_secondpos: size_t
 *                         the second string start position.
 *                    in) t_secondlen: size_t
 *                         the second string compare length.
 *           Returns: int
 *                          compare result < 0 or == 0 or > 0.
 *       Description: three-way lexicographical comparison of the first min(
 *                    t_stringlen, string length) and substr of this
 *                    string.
 *
 * ----------------------------------------------------------------------------
 */
extern int string_compare_substring_substring(
    const string_t* cpt_stringfirst,
    size_t t_firstpos,
    size_t t_firstlen,
    const string_t* cpt_stringsecond,
    size_t t_secondpos,
    size_t t_secondlen);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_compare_cstr
 *        Parameters: in) cpt_string: const string_t*
 *                          the string.
 *                    in) s_cstr: const char*
 *                          the value string.
 *           Returns: int
 *                          compare result < 0 or == 0 or > 0.
 *       Description: three-way lexicographical comparison of valuestring and 
 *                    substr of this string.
 *
 * ----------------------------------------------------------------------------
 */
extern int string_compare_cstr(
    const string_t* cpt_string,
    const char* s_cstr);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_compare_substring_cstr
 *        Parameters: in) cpt_string: const string_t*
 *                          the string.
 *                    in) t_stringpos: size_t
 *                          the string start position.
 *                    in) t_stringlen: size_t
 *                          the string compare length.
 *                    in) s_cstr: const char*
 *                          the value string.
 *           Returns: int
 *                          compare result < 0 or == 0 or > 0.
 *       Description: three-way lexicographical comparison of the first min(
 *                    t_stringlen, string length) and substr of this
 *                    string.
 *
 * ----------------------------------------------------------------------------
 */
extern int string_compare_substring_cstr(
    const string_t* cpt_string,
    size_t t_stringpos,
    size_t t_stringlen,
    const char* s_cstr);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_compare_substring_subcstr
 *        Parameters: in) cpt_string: const string_t*
 *                          the string.
 *                    in) t_stringpos: size_t
 *                          the string start position.
 *                    in) t_stringlen: size_t
 *                          the string compare length.
 *                    in) s_cstr: const char*
 *                          the value string.
 *                    in) t_len: size_t
 *                          the value string length.
 *           Returns: int
 *                          compare result < 0 or == 0 or > 0.
 *       Description: three-way lexicographical comparison of the first min(
 *                    t_stringlen, string length) and substr of this
 *                    string.
 *
 * ----------------------------------------------------------------------------
 */
extern int string_compare_substring_subcstr(
    const string_t* cpt_string,
    size_t t_stringpos,
    size_t t_stringlen,
    const char* s_cstr,
    size_t t_len);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_substr
 *        Parameters: in) cpt_string: const string_t*
 *                          the string.
 *                    in) t_pos: size_t
 *                          start position.
 *                    in) t_len: size_t
 *                          length.
 *           Returns: string_t
 *                          the copy of substring
 *       Description: return the substring, and you must be destroy the
 *                    substring after used.
 *
 * ----------------------------------------------------------------------------
 */
extern string_t string_substr(
    const string_t* cpt_string, size_t t_pos, size_t t_len);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_connect
 *        Parameters: in) pt_string: string_t*
 *                          the string.
 *                    in) cpt_string_src: const string_t*
 *                          the source string.
 *           Returns: void
 *       Description: string concatenation.
 *
 * ----------------------------------------------------------------------------
 */
extern void string_connect(string_t* pt_string, const string_t* cpt_string_src);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_connect_cstr
 *        Parameters: in) pt_string: string_t*
 *                          the string.
 *                    in) s_cstr: const char*
 *                          the value string.
 *           Returns: void
 *       Description: string concatenation.
 *
 * ----------------------------------------------------------------------------
 */
extern void string_connect_cstr(string_t* pt_string, const char* s_cstr);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_connect_char
 *        Parameters: in) pt_string: string_t*
 *                          the string.
 *                    in) c_char: char
 *                          the character
 *           Returns: void
 *       Description: string concatenation.
 *
 * ----------------------------------------------------------------------------
 */
extern void string_connect_char(string_t* pt_string, char c_char);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_find
 *        Parameters: in) cpt_string: const string_t*
 *                          the string.
 *                    in) cpt_string_find: const string_t*
 *                          the find string.
 *                    in) t_pos: size_t
 *                          start position.
 *           Returns: size_t
 *                          the position of find subcstring.
 *       Description: search for the first t_len elements of s_cstr
 *                    as a subcstring of cpt_string, beginning at 
 *                    value string of cpt_string.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t string_find(
    const string_t* cpt_string, const string_t* cpt_string_find, size_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_find_cstr
 *        Parameters: in) cpt_string: const string_t*
 *                          the string.
 *                    in) s_cstr: const char*
 *                          the find value string.
 *                    in) t_pos: size_t
 *                          start position.
 *           Returns: size_t
 *                          the position of find subcstring.
 *       Description: search for the first t_len elements of s_cstr
 *                    as a subcstring of cpt_string, beginning at 
 *                    value string of cpt_string.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t string_find_cstr(
    const string_t* cpt_string, const char* s_cstr, size_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_find_subcstr
 *        Parameters: in) cpt_string: const string_t*
 *                          the string.
 *                    in) s_cstr: const char*
 *                          the find value string.
 *                    in) t_pos: size_t
 *                          start position.
 *                    in) t_len: size_t
 *                          length.
 *           Returns: size_t
 *                          the position of find subcstring.
 *       Description: search for the first t_len elements of s_cstr
 *                    as a subcstring of cpt_string, beginning at 
 *                    value string of cpt_string.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t string_find_subcstr(
    const string_t* cpt_string, const char* s_cstr, size_t t_pos, size_t t_len);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_find_char
 *        Parameters: in) cpt_string: const string_t*
 *                          the string.
 *                    in) c_char: char
 *                          the find character.
 *                    in) t_pos: size_t
 *                          start position.
 *           Returns: size_t
 *                          the position of find subcstring.
 *       Description: search for the first t_len elements of s_cstr
 *                    as a subcstring of cpt_string, beginning at 
 *                    value string of cpt_string.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t string_find_char(
    const string_t* cpt_string, char c_char, size_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_rfind
 *        Parameters: in) cpt_string: const string_t*
 *                          the string.
 *                    in) cpt_string_find: const string_t*
 *                          the find string.
 *                    in) t_pos: size_t
 *                          start position.
 *           Returns: size_t
 *                          the position of find subcstring.
 *       Description: search backword for the first t_len elements of s_cstr
 *                    as a subcstring of cpt_string, beginning at 
 *                    value string of cpt_string.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t string_rfind(
    const string_t* cpt_string, const string_t* cpt_string_find, size_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_rfind_cstr
 *        Parameters: in) cpt_string: const string_t*
 *                          the string.
 *                    in) s_cstr: const char*
 *                          the find value string.
 *                    in) t_pos: size_t
 *                          start position.
 *           Returns: size_t
 *                          the position of find subcstring.
 *       Description: search backword for the first t_len elements of s_cstr
 *                    as a subcstring of cpt_string, beginning at 
 *                    value string of cpt_string.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t string_rfind_cstr(
    const string_t* cpt_string, const char* s_cstr, size_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_rfind_subcstr
 *        Parameters: in) cpt_string: const string_t*
 *                          the string.
 *                    in) s_cstr: const char*
 *                          the find value string.
 *                    in) t_pos: size_t
 *                          start position.
 *                    in) t_len: size_t
 *                          length.
 *           Returns: size_t
 *                          the position of find subcstring.
 *       Description: search backword for the first t_len elements of s_cstr
 *                    as a subcstring of cpt_string, beginning at 
 *                    value string of cpt_string.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t string_rfind_subcstr(
    const string_t* cpt_string, const char* s_cstr, size_t t_pos, size_t t_len);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_rfind_char
 *        Parameters: in) cpt_string: const string_t*
 *                          the string.
 *                    in) s_cstr: const char*
 *                          the find value string.
 *                    in) t_pos: size_t
 *                          start position.
 *           Returns: size_t
 *                          the position of find subcstring.
 *       Description: search backword for the first t_len elements of s_cstr
 *                    as a subcstring of cpt_string, beginning at 
 *                    value string of cpt_string.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t string_rfind_char(
    const string_t* cpt_string, char c_char, size_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_find_first_of
 *        Parameters: in) cpt_string: const string_t*
 *                          the string.
 *                    in) s_cstr: const char*
 *                          the find value string.
 *                    in) t_pos: size_t
 *                          start position.
 *                    in) t_len: size_t
 *                          length.
 *           Returns: size_t
 *                          the position of find subcstring.
 *       Description: search within cpt_string, beginning at t_pos, for 
 *                    the first element that is equal to any element within
 *                    cpt_string_find.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t string_find_first_of(
    const string_t* cpt_string, const string_t* cpt_string_find, size_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_find_first_of_cstr
 *        Parameters: in) cpt_string: const string_t*
 *                          the string.
 *                    in) s_cstr: const char*
 *                          the find value string.
 *                    in) t_pos: size_t
 *                          start position.
 *                    in) t_len: size_t
 *                          length.
 *           Returns: size_t
 *                          the position of find subcstring.
 *       Description: search within cpt_string, beginning at t_pos, for 
 *                    the first element that is equal to any element within
 *                    s_cstr.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t string_find_first_of_cstr(
    const string_t* cpt_string, const char* s_cstr, size_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_find_first_of_subcstr
 *        Parameters: in) cpt_string: const string_t*
 *                          the string.
 *                    in) s_cstr: const char*
 *                          the find value string.
 *                    in) t_pos: size_t
 *                          start position.
 *                    in) t_len: size_t
 *                          length.
 *           Returns: size_t
 *                          the position of find subcstring.
 *       Description: search within cpt_string, beginning at t_pos, for 
 *                    the first element that is equal to any element within
 *                    the first t_len elements of s_cstr.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t string_find_first_of_subcstr(
    const string_t* cpt_string, const char* s_cstr, size_t t_pos, size_t t_len);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_find_first_of_char
 *        Parameters: in) cpt_string: const string_t*
 *                          the string.
 *                    in) s_cstr: const char*
 *                          the find value string.
 *                    in) t_pos: size_t
 *                          start position.
 *                    in) t_len: size_t
 *                          length.
 *           Returns: size_t
 *                          the position of find subcstring.
 *       Description: search within cpt_string, beginning at t_pos, for 
 *                    the first element that is equal to any element within
 *                    s_cstr.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t string_find_first_of_char(
    const string_t* cpt_string, char c_char, size_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_find_first_not_of
 *        Parameters: in) cpt_string: const string_t*
 *                          the string.
 *                    in) s_cstr: const char*
 *                          the find value string.
 *                    in) t_pos: size_t
 *                          start position.
 *                    in) t_len: size_t
 *                          length.
 *           Returns: size_t
 *                          the position of find subcstring.
 *       Description: search within cpt_string, beginning at t_pos, for 
 *                    the first element that is not equal to any element within
 *                    cpt_string_find.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t string_find_first_not_of(
    const string_t* cpt_string, const string_t* cpt_string_find, size_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_find_first_not_of_cstr
 *        Parameters: in) cpt_string: const string_t*
 *                          the string.
 *                    in) s_cstr: const char*
 *                          the find value string.
 *                    in) t_pos: size_t
 *                          start position.
 *                    in) t_len: size_t
 *                          length.
 *           Returns: size_t
 *                          the position of find subcstring.
 *       Description: search within cpt_string, beginning at t_pos, for 
 *                    the first element that is not equal to any element within
 *                    s_cstr.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t string_find_first_not_of_cstr(
    const string_t* cpt_string, const char* s_cstr, size_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_find_first_not_of_subcstr
 *        Parameters: in) cpt_string: const string_t*
 *                          the string.
 *                    in) s_cstr: const char*
 *                          the find value string.
 *                    in) t_pos: size_t
 *                          start position.
 *                    in) t_len: size_t
 *                          length.
 *           Returns: size_t
 *                          the position of find subcstring.
 *       Description: search within cpt_string, beginning at t_pos, for 
 *                    the first element that is not equal to any element within
 *                    the first t_len elements of s_cstr.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t string_find_first_not_of_subcstr(
    const string_t* cpt_string, const char* s_cstr, size_t t_pos, size_t t_len);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_find_first_not_of_char
 *        Parameters: in) cpt_string: const string_t*
 *                          the string.
 *                    in) s_cstr: const char*
 *                          the find value string.
 *                    in) t_pos: size_t
 *                          start position.
 *                    in) t_len: size_t
 *                          length.
 *           Returns: size_t
 *                          the position of find subcstring.
 *       Description: search within cpt_string, beginning at t_pos, for 
 *                    the first element that is not equal to any element within
 *                    s_cstr.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t string_find_first_not_of_char(
    const string_t* cpt_string, char c_char, size_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_find_last_of
 *        Parameters: in) cpt_string: const string_t*
 *                          the string.
 *                    in) cpt_string_find: const string_t*
 *                          the find string.
 *                    in) t_pos: size_t
 *                          start position.
 *           Returns: size_t
 *                          the position of find subcstring.
 *       Description: search backword for the first t_len elements of s_cstr
 *                    as a subcstring of cpt_string, beginning at 
 *                    value string of cpt_string.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t string_find_last_of(
    const string_t* cpt_string, const string_t* cpt_string_find, size_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_find_last_of_cstr
 *        Parameters: in) cpt_string: const string_t*
 *                          the string.
 *                    in) s_cstr: const char*
 *                          the find value string.
 *                    in) t_pos: size_t
 *                          start position.
 *           Returns: size_t
 *                          the position of find subcstring.
 *       Description: search backword for the first t_len elements of s_cstr
 *                    as a subcstring of cpt_string, beginning at 
 *                    value string of cpt_string.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t string_find_last_of_cstr(
    const string_t* cpt_string, const char* s_cstr, size_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_find_last_of_subcstr
 *        Parameters: in) cpt_string: const string_t*
 *                          the string.
 *                    in) s_cstr: const char*
 *                          the find value string.
 *                    in) t_pos: size_t
 *                          start position.
 *                    in) t_len: size_t
 *                          length.
 *           Returns: size_t
 *                          the position of find subcstring.
 *       Description: search backword for the first t_len elements of s_cstr
 *                    as a subcstring of cpt_string, beginning at 
 *                    value string of cpt_string.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t string_find_last_of_subcstr(
    const string_t* cpt_string, const char* s_cstr, size_t t_pos, size_t t_len);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_find_last_of_char
 *        Parameters: in) cpt_string: const string_t*
 *                          the string.
 *                    in) s_cstr: const char*
 *                          the find value string.
 *                    in) t_pos: size_t
 *                          start position.
 *           Returns: size_t
 *                          the position of find subcstring.
 *       Description: search backword for the first t_len elements of s_cstr
 *                    as a subcstring of cpt_string, beginning at 
 *                    value string of cpt_string.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t string_find_last_of_char(
    const string_t* cpt_string, char c_char, size_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_find_last_not_of
 *        Parameters: in) cpt_string: const string_t*
 *                          the string.
 *                    in) s_cstr: const char*
 *                          the find value string.
 *                    in) t_pos: size_t
 *                          start position.
 *                    in) t_len: size_t
 *                          length.
 *           Returns: size_t
 *                          the position of find subcstring.
 *       Description: search within cpt_string, beginning at t_pos, for 
 *                    the first element that is not equal to any element within
 *                    cpt_string_find.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t string_find_last_not_of(
    const string_t* cpt_string, const string_t* cpt_string_find, size_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_find_last_not_of_cstr
 *        Parameters: in) cpt_string: const string_t*
 *                          the string.
 *                    in) s_cstr: const char*
 *                          the find value string.
 *                    in) t_pos: size_t
 *                          start position.
 *                    in) t_len: size_t
 *                          length.
 *           Returns: size_t
 *                          the position of find subcstring.
 *       Description: search within cpt_string, beginning at t_pos, for 
 *                    the first element that is not equal to any element within
 *                    s_cstr.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t string_find_last_not_of_cstr(
    const string_t* cpt_string, const char* s_cstr, size_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_find_last_not_of
 *        Parameters: in) cpt_string: const string_t*
 *                          the string.
 *                    in) s_cstr: const char*
 *                          the find value string.
 *                    in) t_pos: size_t
 *                          start position.
 *                    in) t_len: size_t
 *                          length.
 *           Returns: size_t
 *                          the position of find subcstring.
 *       Description: search within cpt_string, beginning at t_pos, for 
 *                    the first element that is not equal to any element within
 *                    cpt_string_find.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t string_find_last_not_of_subcstr(
    const string_t* cpt_string, const char* s_cstr, size_t t_pos, size_t t_len);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_find_last_not_of_char
 *        Parameters: in) cpt_string: const string_t*
 *                          the string.
 *                    in) s_cstr: const char*
 *                          the find value string.
 *                    in) t_pos: size_t
 *                          start position.
 *                    in) t_len: size_t
 *                          length.
 *           Returns: size_t
 *                          the position of find subcstring.
 *       Description: search within cpt_string, beginning at t_pos, for 
 *                    the first element that is not equal to any element within
 *                    s_cstr.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t string_find_last_not_of_char(
    const string_t* cpt_string, char c_char, size_t t_pos);
/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_begin
 *        Parameters: in) cpt_string: const string_t*
 *                          the string.
 *           Returns: string_iterator_t
 *       Description: return the random access iterator for the first element.
 *
 * ----------------------------------------------------------------------------
 */
extern string_iterator_t string_begin(const string_t* cpt_string);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_end
 *        Parameters: in) cpt_string: const string_t*
 *                          the string.
 *           Returns: string_iterator_t
 *       Description: return the random access iterator for the last element.
 *
 * ----------------------------------------------------------------------------
 */
extern string_iterator_t string_end(const string_t* cpt_string);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_rbegin
 *        Parameters: in) cpt_string: const string_t*
 *                          the string.
 *           Returns: string_reverse_iterator_t
 *       Description: return the reverse iterator for the first element of the
 *                    reverse iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern string_reverse_iterator_t string_rbegin(const string_t* cpt_string);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_rend
 *        Parameters: in) cpt_string: const string_t*
 *                          the string.
 *           Returns: string_reverse_iterator_t
 *       Description: return the reverse iterator for the last element of the
 *                    reverse iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern string_reverse_iterator_t string_rend(const string_t* cpt_string);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_clear
 *        Parameters: in) pt_string: string_t*
 *                          the string.
 *           Returns: void
 *       Description: erase all elements in string.
 *
 * ----------------------------------------------------------------------------
 */
extern void string_clear(string_t* pt_string);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_swap
 *        Parameters: in) pt_stringfirst: string_t*
 *                          the first string.
 *                    in) pt_stringsecond: string_t*
 *                          the second string.
 *           Returns: void
 *       Description: swap the contents of two strings.
 *
 * ----------------------------------------------------------------------------
 */
extern void string_swap(string_t* pt_stringfirst, string_t* pt_stringsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_reserve
 *        Parameters: in) pt_string: string_t*
 *                          the first string.
 *                    in) t_reservesize: size_t
 *                          the reserve size.
 *           Returns: void
 *       Description: reserve the capacity of string.
 *
 * ----------------------------------------------------------------------------
 */
extern void string_reserve(string_t* pt_string, size_t t_reservesize);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_resize
 *        Parameters: in) pt_string: string_t*
 *                          the first string.
 *                    in) t_reservesize: size_t
 *                          the reserve size.
 *                    in) c_char: char
 *                          character.
 *           Returns: void
 *       Description: reserve the capacity of string.
 *
 * ----------------------------------------------------------------------------
 */
extern void string_resize(string_t* pt_string, size_t t_resize, char c_char);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_push_back
 *        Parameters: in) pt_string: string_t*
 *                          the first string.
 *                    in) c_char: char
 *                          the character.
 *           Returns: void
 *       Description: push the element at the back of string.
 *
 * ----------------------------------------------------------------------------
 */
extern void string_push_back(string_t* pt_string, char c_char);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_assign
 *        Parameters: in) pt_string: string_t*
 *                          the first string.
 *                    in) cpt_string_assign: const string_t*
 *                          the assign string.
 *           Returns: void
 *       Description: assign string to string.
 *
 * ----------------------------------------------------------------------------
 */
extern void string_assign(
    string_t* pt_string, const string_t* cpt_string_assign);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_assign_substring
 *        Parameters: in) pt_string: string_t*
 *                          the first string.
 *                    in) cpt_string_assign: const string_t*
 *                          the assign string.
 *                    in) t_pos: size_t
 *                          the start position.
 *                    in) t_len: size_t
 *                          the copy length.
 *           Returns: void
 *       Description: assign substring to string.
 *
 * ----------------------------------------------------------------------------
 */
extern void string_assign_substring(
    string_t* pt_string, 
    const string_t* cpt_string_assign, 
    size_t t_pos, 
    size_t t_len);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_assign_cstr
 *        Parameters: in) pt_string: string_t*
 *                          the first string.
 *                    in) s_cstr: const char*
 *                          the value string.
 *           Returns: void
 *       Description: assign the all copys elements of value string to
 *                    pt_string.
 *
 * ----------------------------------------------------------------------------
 */
extern void string_assign_cstr(
    string_t* pt_string, const char* s_cstr);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_assign_subcstr
 *        Parameters: in) pt_string: string_t*
 *                          the first string.
 *                    in) s_cstr: const char*
 *                          the value string.
 *                    in) t_len: size_t
 *                          the count.
 *           Returns: void
 *       Description: assign the first t_len copys elements of value string to
 *                    pt_string.
 *
 * ----------------------------------------------------------------------------
 */
extern void string_assign_subcstr(
    string_t* pt_string, const char* s_cstr, size_t t_len);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_assign_char
 *        Parameters: in) pt_string: string_t*
 *                          the first string.
 *                    in) t_count: size_t
 *                          the count.
 *                    in) c_char: char
 *                          the character.
 *           Returns: void
 *       Description: erase the exist contents and replace them by t_count copys
 *                    of element.
 *
 * ----------------------------------------------------------------------------
 */
extern void string_assign_char(string_t* pt_string, size_t t_count, char c_char);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_assign_range
 *        Parameters: in) pt_string: string_t*
 *                          the first string.
 *                    in) t_count: size_t
 *                          the count.
 *                    in) c_char: char
 *                          the character.
 *           Returns: void
 *       Description: erase the exist contents and replace them by t_count copys
 *                    of element.
 *
 * ----------------------------------------------------------------------------
 */
extern void string_assign_range(
    string_t* pt_string, string_iterator_t t_begin, string_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_append
 *        Parameters: in) pt_string: string_t*
 *                          the first string.
 *                    in) cpt_string_append: const string_t*
 *                          the append string.
 *           Returns: void
 *       Description: append cpt_string_append to pt_string.
 *
 * ----------------------------------------------------------------------------
 */
extern void string_append(
    string_t* pt_string, const string_t* cpt_string_append);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_append_substring
 *        Parameters: in) pt_string: string_t*
 *                          the first string.
 *                    in) cpt_string_append: const string_t*
 *                          the append string.
 *                    in) t_pos: size_t
 *                          begin position
 *                    in) t_len: size_t
 *                          append length.
 *           Returns: void
 *       Description: append substring of cpt_string_append to 
 *                    pt_string.
 *
 * ----------------------------------------------------------------------------
 */
extern void string_append_substring(
    string_t* pt_string,
    const string_t* cpt_string_append,
    size_t t_pos,
    size_t t_len);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_append_cstr
 *        Parameters: in) pt_string: string_t*
 *                          the first string.
 *                    in) s_cstr: const char*
 *                          the append value string.
 *           Returns: void
 *       Description: append value string to pt_string.
 *
 * ----------------------------------------------------------------------------
 */
extern void string_append_cstr(string_t* pt_string, const char* s_cstr);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_append_subcstr
 *        Parameters: in) pt_string: string_t*
 *                          the first string.
 *                    in) s_cstr: const char*
 *                          the append value string.
 *                    in) t_len: size_t
 *                          append length.
 *           Returns: void
 *       Description: append subcstr of value string to pt_string.
 *
 * ----------------------------------------------------------------------------
 */
extern void string_append_subcstr(
    string_t* pt_string, const char* s_cstr, size_t t_len);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_append_char
 *        Parameters: in) pt_string: string_t*
 *                          the first string.
 *                    in) t_count: size_t
 *                          the character count.
 *                    in) c_char: char
 *                          the character.
 *           Returns: void
 *       Description: append range of string to pt_string.
 *
 * ----------------------------------------------------------------------------
 */
extern void string_append_char(string_t* pt_string, size_t t_count, char c_char);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_append_range
 *        Parameters: in) pt_string: string_t*
 *                          the first string.
 *                    in) t_begin: string_iterator_t
 *                          the begin iterator
 *                    in) t_end: string_iterator_t
 *                          the end iterator.
 *           Returns: void
 *       Description: append range of string to pt_string.
 *
 * ----------------------------------------------------------------------------
 */
extern void string_append_range(
    string_t* pt_string, string_iterator_t t_begin, string_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_insert
 *        Parameters: in) pt_string: string_t*
 *                          the first string.
 *                    in) t_pos: string_iterator_t
 *                          the insert position.
 *                    in) c_char: char
 *                          the character.
 *           Returns: string_iterator_t
 *       Description: insert cpt_string_insert before t_pos.
 *
 * ----------------------------------------------------------------------------
 */
extern string_iterator_t string_insert(
    string_t* pt_string, string_iterator_t t_pos, char c_char);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_insert_n
 *        Parameters: in) pt_string: string_t*
 *                          the first string.
 *                    in) t_pos: string_iterator_t
 *                          the insert position.
 *                    in) t_count: size_t
 *                          the insert count.
 *                    in) c_char: char
 *                          the character.
 *           Returns: string_iterator_t
 *       Description: insert cpt_string_insert before t_pos.
 *
 * ----------------------------------------------------------------------------
 */
extern string_iterator_t string_insert_n(
    string_t* pt_string, string_iterator_t t_pos, size_t t_count, char c_char);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_insert_string
 *        Parameters: in) pt_string: string_t*
 *                          the first string.
 *                    in) t_pos: size_t
 *                          the insert position.
 *                    in) cpt_string_insert: const string_t*
 *                          the insert string.
 *           Returns: void
 *       Description: insert cpt_string_insert before t_pos.
 *
 * ----------------------------------------------------------------------------
 */
extern void string_insert_string(
    string_t* pt_string, size_t t_pos, const string_t* cpt_string_insert);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_insert_substring
 *        Parameters: in) pt_string: string_t*
 *                          the first string.
 *                    in) t_pos: size_t
 *                          the insert position.
 *                    in) cpt_string_insert: const string_t*
 *                          the insert string.
 *                    in) t_startpos: size_t
 *                          the start position.
 *                    in) t_len: size_t 
 *                          the insert length.
 *           Returns: void
 *       Description: insert substring of cpt_string_insert before t_pos.
 *
 * ----------------------------------------------------------------------------
 */
extern void string_insert_substring(
    string_t* pt_string,
    size_t t_pos,
    const string_t* cpt_string_insert,
    size_t t_startpos,
    size_t t_len);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_insert_cstr
 *        Parameters: in) pt_string: string_t*
 *                          the first string.
 *                    in) t_pos: size_t
 *                          the insert position.
 *                    in) s_cstr: const char**
 *                          the value string
 *           Returns: void
 *       Description: insert value string before t_pos.
 *
 * ----------------------------------------------------------------------------
 */
extern void string_insert_cstr(
    string_t* pt_string, size_t t_pos, const char* s_cstr);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_insert_subcstr
 *        Parameters: in) pt_string: string_t*
 *                          the first string.
 *                    in) t_pos: size_t
 *                          the insert position.
 *                    in) s_cstr: const char**
 *                          the value string
 *                    in) t_len: size_t
 *                          the insert length.
 *           Returns: void
 *       Description: insert subcstr of value string before t_pos.
 *
 * ----------------------------------------------------------------------------
 */
extern void string_insert_subcstr(
    string_t* pt_string, size_t t_pos, const char* s_cstr, size_t t_len);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_insert_char
 *        Parameters: in) pt_string: string_t*
 *                          the first string.
 *                    in) t_pos: size_t
 *                          the insert position.
 *                    in) t_count: size_t
 *                          the character count.
 *                    in) c_char: char
 *                          the character.
 *           Returns: void
 *       Description: insert subcstr of value string before t_pos.
 *
 * ----------------------------------------------------------------------------
 */
extern void string_insert_char(
    string_t* pt_string, size_t t_pos, size_t t_count, char c_char);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_insert_range
 *        Parameters: in) pt_string: string_t*
 *                          the first string.
 *                    in) t_pos: string_iterator_t
 *                          the insert position.
 *                    in) t_begin: string_iterator_t
 *                          the begin iterator
 *                    in) t_end: string_iterator_t
 *                          the end iterator.
 *           Returns: void
 *       Description: insert range [t_begin, t_end) before t_pos.
 *
 * ----------------------------------------------------------------------------
 */
extern void string_insert_range(
    string_t* pt_string,
    string_iterator_t t_pos,
    string_iterator_t t_begin,
    string_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_erase
 *        Parameters: in) pt_string: string_t*
 *                          the first string.
 *                    in) t_begin: string_iterator_t
 *                          the begin iterator
 *           Returns: string_iterator_t
 *       Description: erase the element at the position.
 *
 * ----------------------------------------------------------------------------
 */
extern string_iterator_t string_erase(
    string_t* pt_string, string_iterator_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_erase_range
 *        Parameters: in) pt_string: string_t*
 *                          the first string.
 *                    in) t_begin: string_iterator_t
 *                          the begin iterator
 *                    in) t_end: string_iterator_t
 *                          the end iterator.
 *           Returns: string_iterator_t
 *       Description: erase range [t_begin, t_end).
 *
 * ----------------------------------------------------------------------------
 */
extern string_iterator_t string_erase_range(
    string_t* pt_string,
    string_iterator_t t_begin,
    string_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_erase_substring
 *        Parameters: in) pt_string: string_t*
 *                          the string.
 *                    in) t_pos: size_t
 *                          the start position
 *                    in) t_len: size_t
 *                          the erase length.
 *           Returns: void
 *       Description: erase range.
 *
 * ----------------------------------------------------------------------------
 */
extern void string_erase_substring(
    string_t* pt_string, size_t t_pos, size_t t_len);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_replace
 *        Parameters: in) pt_string: string_t*
 *                          the first string.
 *                    in) t_pos: size_t
 *                          the begin position
 *                    in) t_len: size_t
 *                          the replace length
 *                    in) cpt_string_replace: const string_t*
 *                          the string
 *           Returns: void
 *       Description: replace substring of pt_string with 
 *                    cpt_string_replace.
 *
 * ----------------------------------------------------------------------------
 */
extern void string_replace(
    string_t* pt_string, 
    size_t t_pos, 
    size_t t_len, 
    const string_t* cpt_string_replace);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_replace_substring
 *        Parameters: in) pt_string: string_t*
 *                          the first string.
 *                    in) t_pos: size_t
 *                          the begin position
 *                    in) t_len: size_t
 *                          the replace length
 *                    in) cpt_string_replace: const string_t*
 *                          the string
 *                    in) t_pos: size_t
 *                          the start position.
 *                    in) t_len: size_t
 *                          the length.
 *           Returns: void
 *       Description: replace substring of pt_string with substring of
 *                    cpt_string_replace.
 *
 * ----------------------------------------------------------------------------
 */
extern void string_replace_substring(
    string_t* pt_string,
    size_t t_pos,
    size_t t_len,
    const string_t* cpt_string_replace,
    size_t t_position,
    size_t t_length);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_replace_cstr
 *        Parameters: in) pt_string: string_t*
 *                          the first string.
 *                    in) t_pos: size_t
 *                          the begin position
 *                    in) t_len: size_t
 *                          the replace length
 *                    in) s_cstr: const char*
 *                          the value string.
 *           Returns: void
 *       Description: replace substring of pt_string with the all
 *                    elements of value string.
 *
 * ----------------------------------------------------------------------------
 */
extern void string_replace_cstr(
    string_t* pt_string,
    size_t t_pos,
    size_t t_len,
    const char* s_cstr);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_replace_subcstr
 *        Parameters: in) pt_string: string_t*
 *                          the first string.
 *                    in) t_pos: size_t
 *                          the begin position
 *                    in) t_len: size_t
 *                          the replace length
 *                    in) s_cstr: const char*
 *                          the value string.
 *                    in) t_len: size_t
 *                          the value string length
 *           Returns: void
 *       Description: replace substring of pt_string with the first t_len
 *                    elements of value string.
 *
 * ----------------------------------------------------------------------------
 */
extern void string_replace_subcstr(
    string_t* pt_string,
    size_t t_pos,
    size_t t_len,
    const char* s_cstr,
    size_t t_length);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_replace_char
 *        Parameters: in) pt_string: string_t*
 *                          the first string.
 *                    in) t_pos: size_t
 *                          the begin position
 *                    in) t_len: size_t
 *                          the replace length
 *                    in) t_count: size_t
 *                          the character count.
 *                    in) c_char: char
 *                          the character.
 *           Returns: void
 *       Description: replace substring of pt_string with the all
 *                    elements of value string.
 *
 * ----------------------------------------------------------------------------
 */
extern void string_replace_char(
    string_t* pt_string,
    size_t t_pos,
    size_t t_len,
    size_t t_count,
    char c_char);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_range_replace
 *        Parameters: in) pt_string: string_t*
 *                          the first string.
 *                    in) t_begin: string_iterator_t
 *                          the begin iterator
 *                    in) t_end: string_iterator_t
 *                          the end iterator.
 *                    in) cpt_string_replace: const string_t*
 *                          the string
 *           Returns: void
 *       Description: replace substring of pt_string with 
 *                    cpt_string_replace.
 *
 * ----------------------------------------------------------------------------
 */
extern void string_range_replace(
    string_t* pt_string,
    string_iterator_t t_begin,
    string_iterator_t t_end,
    const string_t* cpt_string_replace);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_range_replace_substring
 *        Parameters: in) pt_string: string_t*
 *                          the first string.
 *                    in) t_begin: string_iterator_t
 *                          the begin iterator
 *                    in) t_end: string_iterator_t
 *                          the end iterator.
 *                    in) cpt_string_replace: const string_t*
 *                          the string
 *                    in) t_pos: size_t
 *                          the start position.
 *                    in) t_len: size_t
 *                          the length.
 *           Returns: void
 *       Description: replace substring of pt_string with substring of
 *                    cpt_string_replace.
 *
 * ----------------------------------------------------------------------------
 */
extern void string_range_replace_substring(
    string_t* pt_string,
    string_iterator_t t_begin,
    string_iterator_t t_end,
    const string_t* cpt_string_replace,
    size_t t_pos,
    size_t t_len);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_range_replace_cstr
 *        Parameters: in) pt_string: string_t*
 *                          the first string.
 *                    in) t_begin: string_iterator_t
 *                          the begin iterator
 *                    in) t_end: string_iterator_t
 *                          the end iterator.
 *                    in) s_cstr: const char*
 *                          the value string.
 *           Returns: void
 *       Description: replace substring of pt_string with the all
 *                    elements of value string.
 *
 * ----------------------------------------------------------------------------
 */
extern void string_range_replace_cstr(
    string_t* pt_string,
    string_iterator_t t_begin,
    string_iterator_t t_end,
    const char* s_cstr);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_range_replace_subcstr
 *        Parameters: in) pt_string: string_t*
 *                          the first string.
 *                    in) t_begin: string_iterator_t
 *                          the begin iterator
 *                    in) t_end: string_iterator_t
 *                          the end iterator.
 *                    in) s_cstr: const char*
 *                          the value string.
 *                    in) t_len: size_t
 *                          the value string length
 *           Returns: void
 *       Description: replace substring of pt_string with the first t_len
 *                    elements of value string.
 *
 * ----------------------------------------------------------------------------
 */
extern void string_range_replace_subcstr(
    string_t* pt_string,
    string_iterator_t t_begin,
    string_iterator_t t_end,
    const char* s_cstr,
    size_t t_len);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_range_replace_char
 *        Parameters: in) pt_string: string_t*
 *                          the first string.
 *                    in) t_begin: string_iterator_t
 *                          the begin iterator
 *                    in) t_end: string_iterator_t
 *                          the end iterator.
 *                    in) c_char: char
 *                          the character.
 *           Returns: void
 *       Description: replace substring of pt_string with the all
 *                    elements of value string.
 *
 * ----------------------------------------------------------------------------
 */
extern void string_range_replace_char(
    string_t* pt_string,
    string_iterator_t t_begin,
    string_iterator_t t_end,
    size_t t_count,
    char c_char);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_replace_range
 *        Parameters: in) pt_string: string_t*
 *                          the first string.
 *                    in) t_begin: string_iterator_t
 *                          the begin iterator
 *                    in) t_end: string_iterator_t
 *                          the end iterator.
 *                    in) t_first: string_iterator_t
 *                          the begin iterator
 *                    in) t_last: string_iterator_t
 *                          the end iterator.
 *           Returns: void
 *       Description: replace substring of pt_string with range 
 *                    [t_first, t_last).
 *
 * ----------------------------------------------------------------------------
 */
extern void string_replace_range(
    string_t* pt_string,
    string_iterator_t t_begin,
    string_iterator_t t_end,
    string_iterator_t t_first,
    string_iterator_t t_last);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_output
 *        Parameters: in) cpt_string: const string_t*
 *                          the string.
 *                    in) fp_stream: FILE*
 *                          output stream.
 *           Returns: void
 *       Description: output the string to fp_stream.
 *
 * ----------------------------------------------------------------------------
 */
extern void string_output(const string_t* cpt_string, FILE* fp_stream);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_input
 *        Parameters: in) cpt_string: const string_t*
 *                          the string.
 *                    in) fp_stream: FILE*
 *                          input stream.
 *           Returns: void
 *       Description: input the string from fp_stream.
 *
 * ----------------------------------------------------------------------------
 */
extern void string_input(string_t* pt_string, FILE* fp_stream);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_getline
 *        Parameters: in) cpt_string: const string_t*
 *                          the string.
 *                    in) fp_stream: FILE*
 *                          input stream.
 *           Returns: bool_t
 *       Description: read signal line from fp_stream.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t string_getline(string_t* pt_string, FILE* fp_stream);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: string_getline_delimiter
 *        Parameters: in) cpt_string: const string_t*
 *                          the string.
 *                    in) fp_stream: FILE*
 *                          input stream.
 *                    in) c_delimiter: char
 *                          delimiter.
 *           Returns: bool_t
 *       Description: read string from fp_stream unitl reachs delimiter.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t string_getline_delimiter(
    string_t* pt_string, FILE* fp_stream, char c_delimiter);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_STRING_H */
/** eof **/

