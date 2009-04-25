/*
 *  The interface of basic_string.
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

#ifndef _CSTL_BASIC_STRING_H
#define _CSTL_BASIC_STRING_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/* create new basic_string with specify type */
#define create_basic_string(type)\
    _create_basic_string(sizeof(type), #type)
/* initialize */
#define basic_string_init_elem(pt_basic_string, t_count, elem)\
    _basic_string_init_elem((pt_basic_string), (t_count), (elem))
/* connect (+= operator) */
#define basic_string_connect_elem(pt_basic_string, elem)\
    _basic_string_connect_elem((pt_basic_string), (elem))
/* find */
#define basic_string_find_elem(cpt_basic_string, elem, t_pos)\
    _basic_string_find_elem((cpt_basic_string), (t_pos), (elem))
#define basic_string_rfind_elem(cpt_basic_string, elem, t_pos)\
    _basic_string_rfind_elem((cpt_basic_string), (t_pos), (elem))
#define basic_string_find_first_of_elem(cpt_basic_string, elem, t_pos)\
    _basic_string_find_elem((cpt_basic_string), (t_pos), (elem))
#define basic_string_find_first_not_of_elem(cpt_basic_string, elem, t_pos)\
    _basic_string_find_first_not_of_elem((cpt_basic_string), (t_pos), (elem))
#define basic_string_find_last_of_elem(cpt_basic_string, elem, t_pos)\
    _basic_string_rfind_elem((cpt_basic_string), (t_pos), (elem))
#define basic_string_find_last_not_of_elem(cpt_basic_string, elem, t_pos)\
    _basic_string_find_last_not_of_elem((cpt_basic_string), (t_pos), (elem))
/* push back */
#define basic_string_push_back(pt_basic_string, elem)\
    _basic_string_push_back((pt_basic_string), (elem))
/* resize */
#define basic_string_resize(pt_basic_string, t_resize, elem)\
    _basic_string_resize((pt_basic_string), (t_resize), (elem))
/* assign */
#define basic_string_assign_elem(pt_basic_string, t_count, elem)\
    _basic_string_assign_elem((pt_basic_string), (t_count), (elem))
/* append element */
#define basic_string_append_elem(pt_basic_string, t_count, elem)\
    _basic_string_append_elem((pt_basic_string), (t_count), (elem))
/* insert element */
#define basic_string_insert(pt_basic_string, t_pos, elem)\
    _basic_string_insert((pt_basic_string), (t_pos), (elem))
#define basic_string_insert_n(pt_basic_string, t_pos, t_count, elem)\
    _basic_string_insert_n((pt_basic_string), (t_pos), (t_count), (elem))
#define basic_string_insert_elem(pt_basic_string, t_pos, t_count, elem)\
    _basic_string_insert_elem((pt_basic_string), (t_pos), (t_count), (elem))
/* replace element */
#define basic_string_range_replace_elem(pt_basic_string, t_begin, t_end, t_count, elem)\
    _basic_string_range_replace_elem((pt_basic_string), (t_begin), (t_end), (t_count), (elem))
#define basic_string_replace_elem(pt_basic_string, t_pos, t_len, t_count, elem)\
    _basic_string_replace_elem((pt_basic_string), (t_pos), (t_len), (t_count), (elem))

/* no position micro */
#define NPOS (size_t)(-1)

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_init
 *        Parameters: in) pt_basic_string: basic_string_t*
 *           Returns: void
 *       Description: initialize the basic_string.
 *
 * ----------------------------------------------------------------------------
 */
extern void basic_string_init(basic_string_t* pt_basic_string);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_init_cstr
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                    in) cpv_valuestring: const void*
 *                          the value string for initialize the basic_string.
 *           Returns: void
 *       Description: initialize the basic_string with value string.
 *
 * ----------------------------------------------------------------------------
 */
extern void basic_string_init_cstr(
    basic_string_t* pt_basic_string, const void* cpv_valuestring);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_init_subcstr
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                    in) cpv_valuestring: const void*
 *                          the value string for initialize the basic_string.
 *                    in) t_len: size_t
 *                          the initialize count.
 *           Returns: void
 *       Description: initialize the basic_string with value string.
 *
 * ----------------------------------------------------------------------------
 */
extern void basic_string_init_subcstr(
    basic_string_t* pt_basic_string, const void* cpv_valuestring, size_t t_len);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_init_copy
 *        Parameters: in) pt_basic_stringdest: basic_string_t*
 *                          the dest basic_string.
 *                    in) cpt_basic_string_src: const basic_string_t*
 *                          the source basic_string.
 *           Returns: void
 *       Description: the copy constructor.
 *
 * ----------------------------------------------------------------------------
 */
extern void basic_string_init_copy(
    basic_string_t* pt_basic_string, const basic_string_t* cpt_basic_string_src);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_init_copy_substring
 *        Parameters: in) pt_basic_stringdest: basic_string_t*
 *                          the dest basic_string.
 *                    in) cpt_basic_string_src: const basic_string_t*
 *                          the source basic_string.
 *                    in) t_pos: size_t
 *                          the start pos.
 *                    in) t_len: size_t
 *                          initialize count.
 *           Returns: void
 *       Description: the copy constructor.
 *
 * ----------------------------------------------------------------------------
 */
extern void basic_string_init_copy_substring(
    basic_string_t* pt_basic_string,
    const basic_string_t* cpt_basic_string_src,
    size_t t_pos,
    size_t t_len);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_init_copy_range
 *        Parameters: in) pt_basic_stringdest: basic_string_t*
 *                          the dest basic_string.
 *                    in) t_begin: basic_string_iterator_t
 *                          the begin iterator.
 *                    in) t_end: basic_string_iterator_t
 *                          the end iterator.
 *           Returns: void
 *       Description: the copy constructor with specific range.
 *
 * ----------------------------------------------------------------------------
 */
extern void basic_string_init_copy_range(
    basic_string_t* pt_basic_string, 
    basic_string_iterator_t t_begin,
    basic_string_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_destroy
 *        Parameters: in) pt_basic_string: basic_string_t*
 *           Returns: void
 *       Description: destroy the basic_string.
 *
 * ----------------------------------------------------------------------------
 */
extern void basic_string_destroy(basic_string_t* pt_basic_string);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_c_str
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *           Returns: const void*
 *       Description: return a pointer to a null-terminated array of element
 *                    representing the string's contents.
 *
 * ----------------------------------------------------------------------------
 */
extern const void* basic_string_c_str(const basic_string_t* cpt_basic_string);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_data
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *           Returns: const void*
 *       Description: return a pointer to a array of element (not necessarily
 *                    null-terminated) representing the string's contents.
 *
 * ----------------------------------------------------------------------------
 */
extern const void* basic_string_data(const basic_string_t* cpt_basic_string);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_copy
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *                          the basic_string.
 *                    in) pv_buffer: void*
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
extern size_t basic_string_copy(
    const basic_string_t* cpt_basic_string, 
    void* pv_buffer, 
    size_t t_copysize,
    size_t t_copypos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_size
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *                          the dest basic_string.
 *           Returns: size_t
 *       Description: get the basic_string size.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t basic_string_size(const basic_string_t* cpt_basic_string);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_length
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *                          the dest basic_string.
 *           Returns: size_t
 *       Description: get the basic_string size.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t basic_string_length(const basic_string_t* cpt_basic_string);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_empty
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *                          the dest basic_string.
 *           Returns: bool_t
 *       Description: if the basic_string is empty.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t basic_string_empty(const basic_string_t* cpt_basic_string);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_max_size
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *                          the dest basic_string.
 *           Returns: size_t
 *       Description: get the maximum capacity of basic_string.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t basic_string_max_size(const basic_string_t* cpt_basic_string);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_capacity
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *                          the dest basic_string.
 *           Returns: size_t
 *       Description: get the capacity of basic_string with out reallocation.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t basic_string_capacity(const basic_string_t* cpt_basic_string);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_at
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *                          the basic_string.
 *                    in) t_pos: size_t
 *                          the element position.
 *           Returns: void*
 *                          the element pointer.
 *       Description: return the element with the n_elempos.
 *
 * ----------------------------------------------------------------------------
 */
extern void* basic_string_at(
    const basic_string_t* cpt_basic_string, size_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_equal
 *        Parameters: in) cpt_basic_stringfirst: const basic_string_t*
 *                          the first basic_string.
 *                    in) cpt_basic_stringsecond: const basic_string_t*
 *                          the second basic_string.
 *           Returns: bool_t
 *       Description: return whether first basic_string equal to second basic_string.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t basic_string_equal(
    const basic_string_t* cpt_basic_stringfirst, 
    const basic_string_t* cpt_basic_stringsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_not_equal
 *        Parameters: in) cpt_basic_stringfirst: const basic_string_t*
 *                          the first basic_string.
 *                    in) cpt_basic_stringsecond: const basic_string_t*
 *                          the second basic_string.
 *           Returns: bool_t
 *       Description: return whether first basic_string not equal to second basic_string.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t basic_string_not_equal(
    const basic_string_t* cpt_basic_stringfirst, 
    const basic_string_t* cpt_basic_stringsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_less
 *        Parameters: in) cpt_basic_stringfirst: const basic_string_t*
 *                          the first basic_string.
 *                    in) cpt_basic_stringsecond: const basic_string_t*
 *                          the second basic_string.
 *           Returns: bool_t
 *       Description: return whether first basic_string less then second basic_string.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t basic_string_less(
    const basic_string_t* cpt_basic_stringfirst, 
    const basic_string_t* cpt_basic_stringsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_great
 *        Parameters: in) cpt_basic_stringfirst: const basic_string_t*
 *                          the first basic_string.
 *                    in) cpt_basic_stringsecond: const basic_string_t*
 *                          the second basic_string.
 *           Returns: bool_t
 *       Description: return whether first basic_string greater then second basic_string.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t basic_string_great(
    const basic_string_t* cpt_basic_stringfirst, 
    const basic_string_t* cpt_basic_stringsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_less_equal
 *        Parameters: in) cpt_basic_stringfirst: const basic_string_t*
 *                          the first basic_string.
 *                    in) cpt_basic_stringsecond: const basic_string_t*
 *                          the second basic_string.
 *           Returns: bool_t
 *       Description: return whether first basic_string less then or equal to the 
 *                    second basic_string.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t basic_string_less_equal(
    const basic_string_t* cpt_basic_stringfirst, 
    const basic_string_t* cpt_basic_stringsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_great_equal
 *        Parameters: in) cpt_basic_stringfirst: const basic_string_t*
 *                          the first basic_string.
 *                    in) cpt_basic_stringsecond: const basic_string_t*
 *                          the second basic_string.
 *           Returns: bool_t
 *       Description: return whether first basic_string greater then or equal to the
 *                    second basic_string.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t basic_string_great_equal(
    const basic_string_t* cpt_basic_stringfirst, 
    const basic_string_t* cpt_basic_stringsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_equal_cstr
 *        Parameters: in) cpt_basic_stringfirst: const basic_string_t*
 *                          the basic_string.
 *                    in) cpv_valuestring: const void*
 *                          value string.
 *           Returns: bool_t
 *       Description: return whether first basic_string equal to value string.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t basic_string_equal_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_valuestring);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_not_equal_cstr
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *                          the basic_string.
 *                    in) cpv_valuestring: const void*
 *                          value string.
 *           Returns: bool_t
 *       Description: return whether first basic_string not equal to value string.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t basic_string_not_equal_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_valuestring); 

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_less_cstr
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *                          the basic_string.
 *                    in) cpv_valuestring: const void*
 *                          value string.
 *           Returns: bool_t
 *       Description: return whether first basic_string less then value string.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t basic_string_less_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_valuestring); 

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_great_cstr
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *                          the basic_string.
 *                    in) cpv_valuestring: const void*
 *                          value string.
 *           Returns: bool_t
 *       Description: return whether first basic_string greater then value string.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t basic_string_great_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_valuestring); 

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_less_equal_cstr
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *                          the basic_string.
 *                    in) cpv_valuestring: const void*
 *                          value string.
 *           Returns: bool_t
 *       Description: return whether first basic_string less then or equal to the 
 *                    value string.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t basic_string_less_equal_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_valuestring); 

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_great_equal_cstr
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *                          the basic_string.
 *                    in) cpv_valuestring: const void*
 *                          value string.
 *           Returns: bool_t
 *       Description: return whether first basic_string greater then or equal to the
 *                    value string.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t basic_string_great_equal_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_valuestring); 

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_compare
 *        Parameters: in) cpt_basic_stringfirst: const basic_string_t*
 *                          the first basic_string.
 *                    in) cpt_basic_stringsecond: const basic_string_t*
 *                          the second basic_string.
 *           Returns: int
 *                          compare result < 0 or == 0 or > 0.
 *       Description: three-way lexicographical comparison of the first min(
 *                    t_stringlen, basic_string length) and substr of this
 *                    basic_string.
 *
 * ----------------------------------------------------------------------------
 */
extern int basic_string_compare(
    const basic_string_t* cpt_basic_stringfirst,
    const basic_string_t* cpt_basic_stringsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_compare_substring_string
 *        Parameters: in) cpt_basic_stringfirst: const basic_string_t*
 *                          the first basic_string.
 *                    in) t_firstpos: size_t
 *                          the first basic_string start position.
 *                    in) t_firstlen: size_t
 *                          the first basic_string compare length.
 *                    in) cpt_basic_stringsecond: const basic_string_t*
 *                          the second basic_string.
 *           Returns: int
 *                          compare result < 0 or == 0 or > 0.
 *       Description: three-way lexicographical comparison of the first min(
 *                    t_stringlen, basic_string length) and substr of this
 *                    basic_string.
 *
 * ----------------------------------------------------------------------------
 */
extern int basic_string_compare_substring_string(
    const basic_string_t* cpt_basic_stringfirst,
    size_t t_firstpos,
    size_t t_firstlen,
    const basic_string_t* cpt_basic_stringsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_compare_substring_substring
 *        Parameters: in) cpt_basic_stringfirst: const basic_string_t*
 *                          the first basic_string.
 *                    in) t_firstpos: size_t
 *                          the first basic_string start position.
 *                    in) t_firstlen: size_t
 *                          the first basic_string compare length.
 *                    in) cpt_basic_stringsecond: const basic_string_t*
 *                          the second basic_string.
 *                    in) t_secondpos: size_t
 *                         the second basic_string start position.
 *                    in) t_secondlen: size_t
 *                         the second basic_string compare length.
 *           Returns: int
 *                          compare result < 0 or == 0 or > 0.
 *       Description: three-way lexicographical comparison of the first min(
 *                    t_stringlen, basic_string length) and substr of this
 *                    basic_string.
 *
 * ----------------------------------------------------------------------------
 */
extern int basic_string_compare_substring_substring(
    const basic_string_t* cpt_basic_stringfirst,
    size_t t_firstpos,
    size_t t_firstlen,
    const basic_string_t* cpt_basic_stringsecond,
    size_t t_secondpos,
    size_t t_secondlen);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_compare_cstr
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *                          the basic_string.
 *                    in) cpv_valuestring: const void*
 *                          the value string.
 *           Returns: int
 *                          compare result < 0 or == 0 or > 0.
 *       Description: three-way lexicographical comparison of valuestring and 
 *                    substr of this basic_string.
 *
 * ----------------------------------------------------------------------------
 */
extern int basic_string_compare_cstr(
    const basic_string_t* cpt_basic_string,
    const void* cpv_valuestring);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_compare_substring_cstr
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *                          the basic_string.
 *                    in) t_stringpos: size_t
 *                          the basic_string start position.
 *                    in) t_stringlen: size_t
 *                          the basic_string compare length.
 *                    in) cpv_valuestring: const void*
 *                          the value string.
 *           Returns: int
 *                          compare result < 0 or == 0 or > 0.
 *       Description: three-way lexicographical comparison of the first min(
 *                    t_stringlen, basic_string length) and substr of this
 *                    basic_string.
 *
 * ----------------------------------------------------------------------------
 */
extern int basic_string_compare_substring_cstr(
    const basic_string_t* cpt_basic_string,
    size_t t_stringpos,
    size_t t_stringlen,
    const void* cpv_valuestring);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_compare_substring_subcstr
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *                          the basic_string.
 *                    in) t_stringpos: size_t
 *                          the basic_string start position.
 *                    in) t_stringlen: size_t
 *                          the basic_string compare length.
 *                    in) cpv_valuestring: const void*
 *                          the value string.
 *                    in) t_valuestringlen: size_t
 *                          the value string length.
 *           Returns: int
 *                          compare result < 0 or == 0 or > 0.
 *       Description: three-way lexicographical comparison of the first min(
 *                    t_stringlen, basic_string length) and substr of this
 *                    basic_string.
 *
 * ----------------------------------------------------------------------------
 */
extern int basic_string_compare_substring_subcstr(
    const basic_string_t* cpt_basic_string,
    size_t t_stringpos,
    size_t t_stringlen,
    const void* cpv_valuestring,
    size_t t_valuestringlen);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_substr
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *                          the basic_string.
 *                    in) t_pos: size_t
 *                          start position.
 *                    in) t_len: size_t
 *                          length.
 *           Returns: basic_string_t
 *                          the copy of substring
 *       Description: return the substring, and you must be destroy the
 *                    substring after used.
 *
 * ----------------------------------------------------------------------------
 */
extern basic_string_t basic_string_substr(
    const basic_string_t* cpt_basic_string, size_t t_pos, size_t t_len);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_connect
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the basic_string.
 *                    in) cpt_basic_string_src: const basic_string_t*
 *                          the source basic_string.
 *           Returns: void
 *       Description: string concatenation.
 *
 * ----------------------------------------------------------------------------
 */
extern void basic_string_connect(
    basic_string_t* pt_basic_string, const basic_string_t* cpt_basic_string_src);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_connect_cstr
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the basic_string.
 *                    in) cpv_valuestring: const void*
 *                          the value string.
 *           Returns: void
 *       Description: string concatenation.
 *
 * ----------------------------------------------------------------------------
 */
extern void basic_string_connect_cstr(
    basic_string_t* pt_basic_string, const void* cpv_valuestring);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_find_cstr
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *                          the basic_string.
 *                    in) cpt_basic_string_find: const basic_string_t*
 *                          the find basic_string.
 *                    in) t_pos: size_t
 *                          start position.
 *           Returns: size_t
 *                          the position of find subcstring.
 *       Description: search for the first t_len elements of cpv_valuestring
 *                    as a subcstring of cpt_basic_string, beginning at 
 *                    value string of cpt_basic_string.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t basic_string_find(
    const basic_string_t* cpt_basic_string, 
    const basic_string_t* cpt_basic_string_find,
    size_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_find_cstr
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *                          the basic_string.
 *                    in) cpv_valuestring: const char*
 *                          the find value string.
 *                    in) t_pos: size_t
 *                          start position.
 *           Returns: size_t
 *                          the position of find subcstring.
 *       Description: search for the first t_len elements of cpv_valuestring
 *                    as a subcstring of cpt_basic_string, beginning at 
 *                    value string of cpt_basic_string.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t basic_string_find_cstr(
    const basic_string_t* cpt_basic_string,
    const void* cpv_valuestring,
    size_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_find_subcstr
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *                          the basic_string.
 *                    in) cpv_valuestring: const char*
 *                          the find value string.
 *                    in) t_pos: size_t
 *                          start position.
 *                    in) t_len: size_t
 *                          length.
 *           Returns: size_t
 *                          the position of find subcstring.
 *       Description: search for the first t_len elements of cpv_valuestring
 *                    as a subcstring of cpt_basic_string, beginning at 
 *                    value string of cpt_basic_string.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t basic_string_find_subcstr(
    const basic_string_t* cpt_basic_string,
    const void* cpv_valuestring,
    size_t t_pos,
    size_t t_len);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_rfind
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *                          the basic_string.
 *                    in) cpt_basic_string_find: const basic_string_t*
 *                          the find basic_string.
 *                    in) t_pos: size_t
 *                          start position.
 *           Returns: size_t
 *                          the position of find subcstring.
 *       Description: search backword for the first t_len elements of cpv_valuestring
 *                    as a subcstring of cpt_basic_string, beginning at 
 *                    value string of cpt_basic_string.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t basic_string_rfind(
    const basic_string_t* cpt_basic_string,
    const basic_string_t* cpt_basic_string_find,
    size_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_rfind_cstr
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *                          the basic_string.
 *                    in) cpv_valuestring: const char*
 *                          the find value string.
 *                    in) t_pos: size_t
 *                          start position.
 *           Returns: size_t
 *                          the position of find subcstring.
 *       Description: search backword for the first t_len elements of cpv_valuestring
 *                    as a subcstring of cpt_basic_string, beginning at 
 *                    value string of cpt_basic_string.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t basic_string_rfind_cstr(
    const basic_string_t* cpt_basic_string,
    const void* cpv_valuestring,
    size_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_rfind_subcstr
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *                          the basic_string.
 *                    in) cpv_valuestring: const char*
 *                          the find value string.
 *                    in) t_pos: size_t
 *                          start position.
 *                    in) t_len: size_t
 *                          length.
 *           Returns: size_t
 *                          the position of find subcstring.
 *       Description: search backword for the first t_len elements of cpv_valuestring
 *                    as a subcstring of cpt_basic_string, beginning at 
 *                    value string of cpt_basic_string.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t basic_string_rfind_subcstr(
    const basic_string_t* cpt_basic_string,
    const void* cpv_valuestring,
    size_t t_pos,
    size_t t_len);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_find_first_of
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *                          the basic_string.
 *                    in) cpv_valuestring: const char*
 *                          the find value string.
 *                    in) t_pos: size_t
 *                          start position.
 *                    in) t_len: size_t
 *                          length.
 *           Returns: size_t
 *                          the position of find subcstring.
 *       Description: search within cpt_basic_string, beginning at t_pos, for 
 *                    the first element that is equal to any element within
 *                    cpt_basic_string_find.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t basic_string_find_first_of(
    const basic_string_t* cpt_basic_string,
    const basic_string_t* cpt_basic_string_find,
    size_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_find_first_of_cstr
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *                          the basic_string.
 *                    in) cpv_valuestring: const char*
 *                          the find value string.
 *                    in) t_pos: size_t
 *                          start position.
 *                    in) t_len: size_t
 *                          length.
 *           Returns: size_t
 *                          the position of find subcstring.
 *       Description: search within cpt_basic_string, beginning at t_pos, for 
 *                    the first element that is equal to any element within
 *                    cpv_valuestring.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t basic_string_find_first_of_cstr(
    const basic_string_t* cpt_basic_string,
    const void* cpv_valuestring,
    size_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_find_first_of_subcstr
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *                          the basic_string.
 *                    in) cpv_valuestring: const char*
 *                          the find value string.
 *                    in) t_pos: size_t
 *                          start position.
 *                    in) t_len: size_t
 *                          length.
 *           Returns: size_t
 *                          the position of find subcstring.
 *       Description: search within cpt_basic_string, beginning at t_pos, for 
 *                    the first element that is equal to any element within
 *                    the first t_len elements of cpv_valuestring.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t basic_string_find_first_of_subcstr(
    const basic_string_t* cpt_basic_string,
    const void* cpv_valuestring,
    size_t t_pos,
    size_t t_len);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_find_first_not_of
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *                          the basic_string.
 *                    in) cpv_valuestring: const char*
 *                          the find value string.
 *                    in) t_pos: size_t
 *                          start position.
 *                    in) t_len: size_t
 *                          length.
 *           Returns: size_t
 *                          the position of find subcstring.
 *       Description: search within cpt_basic_string, beginning at t_pos, for 
 *                    the first element that is not equal to any element within
 *                    cpt_basic_string_find.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t basic_string_find_first_not_of(
    const basic_string_t* cpt_basic_string,
    const basic_string_t* cpt_basic_string_find,
    size_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_find_first_not_of_cstr
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *                          the basic_string.
 *                    in) cpv_valuestring: const char*
 *                          the find value string.
 *                    in) t_pos: size_t
 *                          start position.
 *                    in) t_len: size_t
 *                          length.
 *           Returns: size_t
 *                          the position of find subcstring.
 *       Description: search within cpt_basic_string, beginning at t_pos, for 
 *                    the first element that is not equal to any element within
 *                    cpv_valuestring.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t basic_string_find_first_not_of_cstr(
    const basic_string_t* cpt_basic_string,
    const void* cpv_valuestring,
    size_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_find_first_not_of_subcstr
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *                          the basic_string.
 *                    in) cpv_valuestring: const char*
 *                          the find value string.
 *                    in) t_pos: size_t
 *                          start position.
 *                    in) t_len: size_t
 *                          length.
 *           Returns: size_t
 *                          the position of find subcstring.
 *       Description: search within cpt_basic_string, beginning at t_pos, for 
 *                    the first element that is not equal to any element within
 *                    the first t_len elements of cpv_valuestring.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t basic_string_find_first_not_of_subcstr(
    const basic_string_t* cpt_basic_string,
    const void* cpv_valuestring,
    size_t t_pos,
    size_t t_len);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_find_last_of
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *                          the basic_string.
 *                    in) cpt_basic_string_find: const basic_string_t*
 *                          the find basic_string.
 *                    in) t_pos: size_t
 *                          start position.
 *           Returns: size_t
 *                          the position of find subcstring.
 *       Description: search backword for the first t_len elements of cpv_valuestring
 *                    as a subcstring of cpt_basic_string, beginning at 
 *                    value string of cpt_basic_string.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t basic_string_find_last_of(
    const basic_string_t* cpt_basic_string,
    const basic_string_t* cpt_basic_string_find,
    size_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_find_last_of_cstr
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *                          the basic_string.
 *                    in) cpv_valuestring: const char*
 *                          the find value string.
 *                    in) t_pos: size_t
 *                          start position.
 *           Returns: size_t
 *                          the position of find subcstring.
 *       Description: search backword for the first t_len elements of cpv_valuestring
 *                    as a subcstring of cpt_basic_string, beginning at 
 *                    value string of cpt_basic_string.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t basic_string_find_last_of_cstr(
    const basic_string_t* cpt_basic_string,
    const void* cpv_valuestring,
    size_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_find_last_of_subcstr
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *                          the basic_string.
 *                    in) cpv_valuestring: const char*
 *                          the find value string.
 *                    in) t_pos: size_t
 *                          start position.
 *                    in) t_len: size_t
 *                          length.
 *           Returns: size_t
 *                          the position of find subcstring.
 *       Description: search backword for the first t_len elements of cpv_valuestring
 *                    as a subcstring of cpt_basic_string, beginning at 
 *                    value string of cpt_basic_string.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t basic_string_find_last_of_subcstr(
    const basic_string_t* cpt_basic_string,
    const void* cpv_valuestring,
    size_t t_pos,
    size_t t_len);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_find_last_not_of
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *                          the basic_string.
 *                    in) cpv_valuestring: const char*
 *                          the find value string.
 *                    in) t_pos: size_t
 *                          start position.
 *                    in) t_len: size_t
 *                          length.
 *           Returns: size_t
 *                          the position of find subcstring.
 *       Description: search within cpt_basic_string, beginning at t_pos, for 
 *                    the first element that is not equal to any element within
 *                    cpt_basic_string_find.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t basic_string_find_last_not_of(
    const basic_string_t* cpt_basic_string,
    const basic_string_t* cpt_basic_string_find,
    size_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_find_last_not_of_cstr
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *                          the basic_string.
 *                    in) cpv_valuestring: const char*
 *                          the find value string.
 *                    in) t_pos: size_t
 *                          start position.
 *                    in) t_len: size_t
 *                          length.
 *           Returns: size_t
 *                          the position of find subcstring.
 *       Description: search within cpt_basic_string, beginning at t_pos, for 
 *                    the first element that is not equal to any element within
 *                    cpv_valuestring.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t basic_string_find_last_not_of_cstr(
    const basic_string_t* cpt_basic_string,
    const void* cpv_valuestring,
    size_t t_pos);
/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_find_last_not_of_subcstr
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *                          the basic_string.
 *                    in) cpv_valuestring: const char*
 *                          the find value string.
 *                    in) t_pos: size_t
 *                          start position.
 *                    in) t_len: size_t
 *                          length.
 *           Returns: size_t
 *                          the position of find subcstring.
 *       Description: search within cpt_basic_string, beginning at t_pos, for 
 *                    the first element that is not equal to any element within
 *                    cpt_basic_string_find.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t basic_string_find_last_not_of_subcstr(
    const basic_string_t* cpt_basic_string,
    const void* cpv_valuestring,
    size_t t_pos,
    size_t t_len);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_begin
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *                          the basic_string.
 *           Returns: basic_string_iterator_t
 *       Description: return the random access iterator for the first element.
 *
 * ----------------------------------------------------------------------------
 */
extern basic_string_iterator_t basic_string_begin(
    const basic_string_t* cpt_basic_string);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_end
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *                          the basic_string.
 *           Returns: basic_string_iterator_t
 *       Description: return the random access iterator for the last element.
 *
 * ----------------------------------------------------------------------------
 */
extern basic_string_iterator_t basic_string_end(
    const basic_string_t* cpt_basic_string);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_rbegin
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *                          the basic_string.
 *           Returns: basic_string_reverse_iterator_t
 *       Description: return the reverse iterator for the first element of the
 *                    reverse iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern basic_string_reverse_iterator_t basic_string_rbegin(
    const basic_string_t* cpt_basic_string);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_rend
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *                          the basic_string.
 *           Returns: basic_string_reverse_iterator_t
 *       Description: return the reverse iterator for the last element of the
 *                    reverse iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern basic_string_reverse_iterator_t basic_string_rend(
    const basic_string_t* cpt_basic_string);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_clear
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the basic_string.
 *           Returns: void
 *       Description: erase all elements in basic_string.
 *
 * ----------------------------------------------------------------------------
 */
extern void basic_string_clear(basic_string_t* pt_basic_string);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_swap
 *        Parameters: in) pt_basic_stringfirst: basic_string_t*
 *                          the first basic_string.
 *                    in) pt_basic_stringsecond: basic_string_t*
 *                          the second basic_string.
 *           Returns: void
 *       Description: swap the contents of two basic_strings.
 *
 * ----------------------------------------------------------------------------
 */
extern void basic_string_swap(
    basic_string_t* pt_basic_stringfirst, basic_string_t* pt_basic_stringsecond);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_reserve
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the first basic_string.
 *                    in) t_reservesize: size_t
 *                          the reserve size.
 *           Returns: void
 *       Description: reserve the capacity of basic_string.
 *
 * ----------------------------------------------------------------------------
 */
extern void basic_string_reserve(
    basic_string_t* pt_basic_string, size_t t_reservesize);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_assign
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the first basic_string.
 *                    in) cpt_basic_string_assign: const basic_string_t*
 *                          the assign basic_string.
 *           Returns: void
 *       Description: assign string to basic_string.
 *
 * ----------------------------------------------------------------------------
 */
extern void basic_string_assign(
    basic_string_t* pt_basic_string, 
    const basic_string_t* cpt_basic_string_assign);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_assign_substring
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the first basic_string.
 *                    in) cpt_basic_string_assign: const basic_string_t*
 *                          the assign basic_string.
 *                    in) t_pos: size_t
 *                          the start position.
 *                    in) t_len: size_t
 *                          the copy length.
 *           Returns: void
 *       Description: assign substring to basic_string.
 *
 * ----------------------------------------------------------------------------
 */
extern void basic_string_assign_substring(
    basic_string_t* pt_basic_string,
    const basic_string_t* cpt_basic_string_assign,
    size_t t_pos,
    size_t t_len);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_assign_cstr
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the first basic_string.
 *                    in) cpv_valuestring: const void*
 *                          the value string.
 *           Returns: void
 *       Description: assign the all copys elements of value string to
 *                    pt_basic_string.
 *
 * ----------------------------------------------------------------------------
 */
extern void basic_string_assign_cstr(
    basic_string_t* pt_basic_string,
    const void* cpv_valuestring);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_assign_subcstr
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the first basic_string.
 *                    in) cpv_valuestring: const void*
 *                          the value string.
 *                    in) t_len: size_t
 *                          the count.
 *           Returns: void
 *       Description: assign the first t_len copys elements of value string to
 *                    pt_basic_string.
 *
 * ----------------------------------------------------------------------------
 */
extern void basic_string_assign_subcstr(
    basic_string_t* pt_basic_string,
    const void* cpv_valuestring,
    size_t t_len);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_assign_range
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the first basic_string.
 *                    in) t_begin: basic_string_iterator_t
 *                          the range begin.
 *                    in) t_end: basic_string_iterator_t
 *                          the range end.
 *           Returns: void
 *       Description: erase the exist contents and replace them by t_count copys
 *                    of element.
 *
 * ----------------------------------------------------------------------------
 */
extern void basic_string_assign_range(
    basic_string_t* pt_basic_string, 
    basic_string_iterator_t t_begin,
    basic_string_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_append
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the first basic_string.
 *                    in) cpt_basic_string_append: const basic_string_t*
 *                          the append basic_string.
 *           Returns: void
 *       Description: append cpt_basic_string_append to pt_basic_string.
 *
 * ----------------------------------------------------------------------------
 */
extern void basic_string_append(
    basic_string_t* pt_basic_string,
    const basic_string_t* cpt_basic_string_append);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_append_substring
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the first basic_string.
 *                    in) cpt_basic_string_append: const basic_string_t*
 *                          the append basic_string.
 *                    in) t_pos: size_t
 *                          begin position
 *                    in) t_len: size_t
 *                          append length.
 *           Returns: void
 *       Description: append substring of cpt_basic_string_append to 
 *                    pt_basic_string.
 *
 * ----------------------------------------------------------------------------
 */
extern void basic_string_append_substring(
    basic_string_t* pt_basic_string,
    const basic_string_t* cpt_basic_string_append,
    size_t t_pos,
    size_t t_len);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_append_cstr
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the first basic_string.
 *                    in) cpv_valuestring: const void*
 *                          the append value string.
 *           Returns: void
 *       Description: append value string to pt_basic_string.
 *
 * ----------------------------------------------------------------------------
 */
extern void basic_string_append_cstr(
    basic_string_t* pt_basic_string,
    const void* cpv_valuestring);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_append_subcstr
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the first basic_string.
 *                    in) cpv_valuestring: const void*
 *                          the append value string.
 *                    in) t_len: size_t
 *                          append length.
 *           Returns: void
 *       Description: append subcstr of value string to pt_basic_string.
 *
 * ----------------------------------------------------------------------------
 */
extern void basic_string_append_subcstr(
    basic_string_t* pt_basic_string,
    const void* cpv_valuestring,
    size_t t_len);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_append_range
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the first basic_string.
 *                    in) t_begin: basic_string_iterator_t
 *                          the begin iterator
 *                    in) t_end: basic_string_iterator_t
 *                          the end iterator.
 *           Returns: void
 *       Description: append range of basic_string to pt_basic_string.
 *
 * ----------------------------------------------------------------------------
 */
extern void basic_string_append_range(
    basic_string_t* pt_basic_string,
    basic_string_iterator_t t_begin,
    basic_string_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_insert_string
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the first basic_string.
 *                    in) t_pos: size_t
 *                          the insert position.
 *                    in) cpt_basic_string_insert: const basic_string_t*
 *                          the insert basic_string.
 *           Returns: void
 *       Description: insert cpt_basic_string_insert before t_pos.
 *
 * ----------------------------------------------------------------------------
 */
extern void basic_string_insert_string(
    basic_string_t* pt_basic_string,
    size_t t_pos,
    const basic_string_t* cpt_basic_string_insert);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_insert_substring
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the first basic_string.
 *                    in) t_pos: size_t
 *                          the insert position.
 *                    in) cpt_basic_string_insert: const basic_string_t*
 *                          the insert basic_string.
 *                    in) t_startpos: size_t
 *                          the start position.
 *                    in) t_len: size_t 
 *                          the insert length.
 *           Returns: void
 *       Description: insert substring of cpt_basic_string_insert before t_pos.
 *
 * ----------------------------------------------------------------------------
 */
extern void basic_string_insert_substring(
    basic_string_t* pt_basic_string,
    size_t t_pos,
    const basic_string_t* cpt_basic_string_insert,
    size_t t_startpos,
    size_t t_len);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_insert_cstr
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the first basic_string.
 *                    in) t_pos: size_t
 *                          the insert position.
 *                    in) cpv_valuestring: const void**
 *                          the value string
 *           Returns: void
 *       Description: insert value string before t_pos.
 *
 * ----------------------------------------------------------------------------
 */
extern void basic_string_insert_cstr(
    basic_string_t* pt_basic_string,
    size_t t_pos,
    const void* cpv_valuestring);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_insert_subcstr
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the first basic_string.
 *                    in) t_pos: size_t
 *                          the insert position.
 *                    in) cpv_valuestring: const void**
 *                          the value string
 *                    in) t_len: size_t
 *                          the insert length.
 *           Returns: void
 *       Description: insert subcstr of value string before t_pos.
 *
 * ----------------------------------------------------------------------------
 */
extern void basic_string_insert_subcstr(
    basic_string_t* pt_basic_string,
    size_t t_pos,
    const void* cpv_valuestring,
    size_t t_len);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_insert_range
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the first basic_string.
 *                    in) t_pos: basic_string_iterator_t
 *                          the insert position.
 *                    in) t_begin: basic_string_iterator_t
 *                          the begin iterator
 *                    in) t_end: basic_string_iterator_t
 *                          the end iterator.
 *           Returns: void
 *       Description: insert range [t_begin, t_end) before t_pos.
 *
 * ----------------------------------------------------------------------------
 */
extern void basic_string_insert_range(
    basic_string_t* pt_basic_string,
    basic_string_iterator_t t_pos,
    basic_string_iterator_t t_begin,
    basic_string_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_erase
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the first basic_string.
 *                    in) t_begin: basic_string_iterator_t
 *                          the begin iterator
 *           Returns: basic_string_iterator_t
 *       Description: erase the element at the position.
 *
 * ----------------------------------------------------------------------------
 */
extern basic_string_iterator_t basic_string_erase(
    basic_string_t* pt_basic_string,
    basic_string_iterator_t t_pos);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_erase_range
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the first basic_string.
 *                    in) t_begin: basic_string_iterator_t
 *                          the begin iterator
 *                    in) t_end: basic_string_iterator_t
 *                          the end iterator.
 *           Returns: basic_string_iterator_t
 *       Description: erase range [t_begin, t_end).
 *
 * ----------------------------------------------------------------------------
 */
extern basic_string_iterator_t basic_string_erase_range(
    basic_string_t* pt_basic_string,
    basic_string_iterator_t t_begin,
    basic_string_iterator_t t_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_erase_substring
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the basic_string.
 *                    in) t_pos: size_t
 *                          the start position
 *                    in) t_len: size_t
 *                          the erase length.
 *           Returns: void
 *       Description: erase range.
 *
 * ----------------------------------------------------------------------------
 */
extern void basic_string_erase_substring(
    basic_string_t* pt_basic_string,
    size_t t_pos,
    size_t t_len);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_replace
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the first basic_string.
 *                    in) t_pos: size_t
 *                          the begin position
 *                    in) t_len: size_t
 *                          the replace length
 *                    in) cpt_basic_string_replace: const basic_string_t*
 *                          the basic_string
 *           Returns: void
 *       Description: replace substring of pt_basic_string with 
 *                    cpt_basic_string_replace.
 *
 * ----------------------------------------------------------------------------
 */
extern void basic_string_replace(
    basic_string_t* pt_basic_string,
    size_t t_pos,
    size_t t_len,
    const basic_string_t* cpt_basic_string_replace);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_replace_substring
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the first basic_string.
 *                    in) t_pos: size_t
 *                          the begin position
 *                    in) t_len: size_t
 *                          the replace length
 *                    in) cpt_basic_string_replace: const basic_string_t*
 *                          the basic_string
 *                    in) t_pos: size_t
 *                          the start position.
 *                    in) t_len: size_t
 *                          the length.
 *           Returns: void
 *       Description: replace substring of pt_basic_string with substring of
 *                    cpt_basic_string_replace.
 *
 * ----------------------------------------------------------------------------
 */
extern void basic_string_replace_substring(
    basic_string_t* pt_basic_string,
    size_t t_pos,
    size_t t_len,
    const basic_string_t* cpt_basic_string_replace,
    size_t t_position,
    size_t t_length);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_replace_cstr
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the first basic_string.
 *                    in) t_pos: size_t
 *                          the begin position
 *                    in) t_len: size_t
 *                          the replace length
 *                    in) cpv_valuestring: const void*
 *                          the value string.
 *           Returns: void
 *       Description: replace substring of pt_basic_string with the all
 *                    elements of value string.
 *
 * ----------------------------------------------------------------------------
 */
extern void basic_string_replace_cstr(
    basic_string_t* pt_basic_string,
    size_t t_pos,
    size_t t_len,
    const void* cpv_valuestring);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_replace_subcstr
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the first basic_string.
 *                    in) t_pos: size_t
 *                          the begin position
 *                    in) t_len: size_t
 *                          the replace length
 *                    in) cpv_valuestring: const void*
 *                          the value string.
 *                    in) t_len: size_t
 *                          the value string length
 *           Returns: void
 *       Description: replace substring of pt_basic_string with the first t_len
 *                    elements of value string.
 *
 * ----------------------------------------------------------------------------
 */
extern void basic_string_replace_subcstr(
    basic_string_t* pt_basic_string,
    size_t t_pos,
    size_t t_len,
    const void* cpv_valuestring,
    size_t t_length);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_range_replace
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the first basic_string.
 *                    in) t_begin: basic_string_iterator_t
 *                          the begin iterator
 *                    in) t_end: basic_string_iterator_t
 *                          the end iterator.
 *                    in) cpt_basic_string_replace: const basic_string_t*
 *                          the basic_string
 *           Returns: void
 *       Description: replace substring of pt_basic_string with 
 *                    cpt_basic_string_replace.
 *
 * ----------------------------------------------------------------------------
 */
extern void basic_string_range_replace(
    basic_string_t* pt_basic_string,
    basic_string_iterator_t t_begin,
    basic_string_iterator_t t_end,
    const basic_string_t* cpt_basic_string_replace);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_range_replace_substring
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the first basic_string.
 *                    in) t_begin: basic_string_iterator_t
 *                          the begin iterator
 *                    in) t_end: basic_string_iterator_t
 *                          the end iterator.
 *                    in) cpt_basic_string_replace: const basic_string_t*
 *                          the basic_string
 *                    in) t_pos: size_t
 *                          the start position.
 *                    in) t_len: size_t
 *                          the length.
 *           Returns: void
 *       Description: replace substring of pt_basic_string with substring of
 *                    cpt_basic_string_replace.
 *
 * ----------------------------------------------------------------------------
 */
extern void basic_string_range_replace_substring(
    basic_string_t* pt_basic_string,
    basic_string_iterator_t t_begin,
    basic_string_iterator_t t_end,
    const basic_string_t* cpt_basic_string_replace,
    size_t t_pos,
    size_t t_len);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_range_replace_cstr
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the first basic_string.
 *                    in) t_begin: basic_string_iterator_t
 *                          the begin iterator
 *                    in) t_end: basic_string_iterator_t
 *                          the end iterator.
 *                    in) cpv_valuestring: const void*
 *                          the value string.
 *           Returns: void
 *       Description: replace substring of pt_basic_string with the all
 *                    elements of value string.
 *
 * ----------------------------------------------------------------------------
 */
extern void basic_string_range_replace_cstr(
    basic_string_t* pt_basic_string,
    basic_string_iterator_t t_begin,
    basic_string_iterator_t t_end,
    const void* cpv_valuestring);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_range_replace_subcstr
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the first basic_string.
 *                    in) t_begin: basic_string_iterator_t
 *                          the begin iterator
 *                    in) t_end: basic_string_iterator_t
 *                          the end iterator.
 *                    in) cpv_valuestring: const void*
 *                          the value string.
 *                    in) t_len: size_t
 *                          the value string length
 *           Returns: void
 *       Description: replace substring of pt_basic_string with the first t_len
 *                    elements of value string.
 *
 * ----------------------------------------------------------------------------
 */
extern void basic_string_range_replace_subcstr(
    basic_string_t* pt_basic_string,
    basic_string_iterator_t t_begin,
    basic_string_iterator_t t_end,
    const void* cpv_valuestring,
    size_t t_len);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: basic_string_replace_range
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the first basic_string.
 *                    in) t_begin: basic_string_iterator_t
 *                          the begin iterator
 *                    in) t_end: basic_string_iterator_t
 *                          the end iterator.
 *                    in) t_first: basic_string_iterator_t
 *                          the begin iterator
 *                    in) t_last: basic_string_iterator_t
 *                          the end iterator.
 *           Returns: void
 *       Description: replace substring of pt_basic_string with range 
 *                    [t_first, t_last).
 *
 * ----------------------------------------------------------------------------
 */
extern void basic_string_replace_range(
    basic_string_t* pt_basic_string,
    basic_string_iterator_t t_begin,
    basic_string_iterator_t t_end,
    basic_string_iterator_t t_first,
    basic_string_iterator_t t_last);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_BASIC_STRING_H */
/** eof **/

