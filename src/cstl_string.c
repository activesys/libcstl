/*
 *  The implementation of string_t.
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

/** include section **/
#include <assert.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "cstl_alloc.h"
#include "cstl_types.h"
#include "cstl_iterator.h"
#include "cvector.h"

#include "cstl_basic_string_iterator.h"
#include "cstl_basic_string_private.h"
#include "cstl_basic_string.h"
#include "cstl_string_iterator.h"
#include "cstl_string.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/* initialize and destroy */
string_t* create_string(void)
{
    return create_basic_string(char);
}

bool_t _create_string_auxiliary(string_t* pt_string)
{
    return _create_basic_string_auxiliary(pt_string, "char");
}

void _string_destroy_auxiliary(string_t* pt_string)
{
    _basic_string_destroy_auxiliary(pt_string);
}

void string_init(string_t* pt_string)
{
    assert(pt_string != NULL);

    basic_string_init(pt_string);
    basic_string_push_back(pt_string, '\0');
}

void string_init_cstr(string_t* pt_string, const char* s_cstr)
{
    assert(pt_string != NULL);

    basic_string_init_cstr(pt_string, s_cstr);
    basic_string_push_back(pt_string, '\0');
}

void string_init_subcstr(string_t* pt_string, const char* s_cstr, size_t t_count)
{
    assert(pt_string != NULL);

    basic_string_init_subcstr(pt_string, s_cstr, t_count);
    basic_string_push_back(pt_string, '\0');
}

void string_init_char(string_t* pt_string, size_t t_count, char c_char)
{
    assert(pt_string != NULL);

    basic_string_init_elem(pt_string, t_count, c_char);
    basic_string_push_back(pt_string, '\0');
}

void string_init_copy(string_t* pt_string, const string_t* cpt_string_src)
{
    assert(pt_string != NULL && cpt_string_src != NULL);

    basic_string_init_copy(pt_string, cpt_string_src);
}

void string_init_copy_substring(
    string_t* pt_string, const string_t* cpt_string_src, size_t t_pos, size_t t_len)
{
    assert(pt_string != NULL && cpt_string_src != NULL);

    basic_string_init_copy_substring(pt_string, cpt_string_src, t_pos, t_len);
    if(t_len != NPOS && t_pos + t_len <= string_size(cpt_string_src))
    {
        basic_string_push_back(pt_string, '\0');
    }
}

void string_init_copy_range(
    string_t* pt_string, string_iterator_t t_begin, string_iterator_t t_end)
{
    assert(pt_string != NULL);

    basic_string_init_copy_range(pt_string, t_begin, t_end);
    if(!iterator_equal(t_end, basic_string_end(_GET_BASIC_STRING_CONTAINER(t_end))))
    {
        basic_string_push_back(pt_string, '\0');
    }
}

void string_destroy(string_t* pt_string)
{
    basic_string_destroy(pt_string);
}

/* c_str and data */
const char* string_c_str(const string_t* cpt_string)
{
    return basic_string_c_str(cpt_string);
}

const char* string_data(const string_t* cpt_string)
{
    return basic_string_data(cpt_string);
}

size_t string_copy(
    const string_t* cpt_string, char* s_buffer, size_t t_copysize, size_t t_copypos)
{
    return basic_string_copy(cpt_string, s_buffer, t_copysize, t_copypos);
}

/* size, max_size ... */
size_t string_size(const string_t* cpt_string)
{
    return basic_string_size(cpt_string) - 1;
}

size_t string_length(const string_t* cpt_string)
{
    return basic_string_length(cpt_string) - 1;
}

size_t string_max_size(const string_t* cpt_string)
{
    return basic_string_max_size(cpt_string) - 1;
}

size_t string_capacity(const string_t* cpt_string)
{
    return basic_string_capacity(cpt_string) - 1;
}

bool_t string_empty(const string_t* cpt_string)
{
    return string_size(cpt_string) == 0 ? true : false;
}

char* string_at(const string_t* cpt_string, size_t t_pos)
{
    assert(t_pos < basic_string_length(cpt_string));
    return (char*)basic_string_at(cpt_string, t_pos);
}

/* compare operator */
bool_t string_equal(
    const string_t* cpt_stringfirst, const string_t* cpt_stringsecond)
{
    return basic_string_equal(cpt_stringfirst, cpt_stringsecond);
}

bool_t string_not_equal(
    const string_t* cpt_stringfirst, const string_t* cpt_stringsecond)
{
    return basic_string_not_equal(cpt_stringfirst, cpt_stringsecond);
}

bool_t string_less(
    const string_t* cpt_stringfirst, const string_t* cpt_stringsecond)
{
    return basic_string_less(cpt_stringfirst, cpt_stringsecond);
}

bool_t string_less_equal(
    const string_t* cpt_stringfirst, const string_t* cpt_stringsecond)
{
    return basic_string_less_equal(cpt_stringfirst, cpt_stringsecond);
}

bool_t string_great(
    const string_t* cpt_stringfirst, const string_t* cpt_stringsecond)
{
    return basic_string_great(cpt_stringfirst, cpt_stringsecond);
}

bool_t string_great_equal(
    const string_t* cpt_stringfirst, const string_t* cpt_stringsecond)
{
    return basic_string_great_equal(cpt_stringfirst, cpt_stringsecond);
}

bool_t string_equal_cstr(const string_t* cpt_string, const char* s_cstr)
{
    bool_t t_result = false;

    _basic_string_pop_back((basic_string_t*)cpt_string);
    t_result = basic_string_equal_cstr(cpt_string, s_cstr);
    basic_string_push_back((basic_string_t*)cpt_string, '\0');

    return t_result;
}

bool_t string_not_equal_cstr(const string_t* cpt_string, const char* s_cstr)
{
    bool_t t_result = false;

    _basic_string_pop_back((basic_string_t*)cpt_string);
    t_result = basic_string_not_equal_cstr(cpt_string, s_cstr);
    basic_string_push_back((basic_string_t*)cpt_string, '\0');

    return t_result;
}

bool_t string_less_cstr(const string_t* cpt_string, const char* s_cstr)
{
    bool_t t_result = false;

    _basic_string_pop_back((basic_string_t*)cpt_string);
    t_result = basic_string_less_cstr(cpt_string, s_cstr);
    basic_string_push_back((basic_string_t*)cpt_string, '\0');

    return t_result;
}

bool_t string_less_equal_cstr(const string_t* cpt_string, const char* s_cstr)
{
    bool_t t_result = false;

    _basic_string_pop_back((basic_string_t*)cpt_string);
    t_result = basic_string_less_equal_cstr(cpt_string, s_cstr);
    basic_string_push_back((basic_string_t*)cpt_string, '\0');

    return t_result;
}

bool_t string_great_cstr(const string_t* cpt_string, const char* s_cstr)
{
    bool_t t_result = false;

    _basic_string_pop_back((basic_string_t*)cpt_string);
    t_result = basic_string_great_cstr(cpt_string, s_cstr);
    basic_string_push_back((basic_string_t*)cpt_string, '\0');

    return t_result;
}

bool_t string_great_equal_cstr(const string_t* cpt_string, const char* s_cstr)
{
    bool_t t_result = false;

    _basic_string_pop_back((basic_string_t*)cpt_string);
    t_result = basic_string_great_equal_cstr(cpt_string, s_cstr);
    basic_string_push_back((basic_string_t*)cpt_string, '\0');

    return t_result;
}

int string_compare(
    const string_t* cpt_stringfirst, const string_t* cpt_stringsecond)
{
    return string_compare_cstr(cpt_stringfirst, string_c_str(cpt_stringsecond));
}

int string_compare_substring_string(
    const string_t* cpt_stringfirst, size_t t_firstpos, size_t t_firstlen,
    const string_t* cpt_stringsecond)
{
    return string_compare_substring_cstr(
        cpt_stringfirst, t_firstpos, t_firstlen, string_c_str(cpt_stringsecond));
}

int string_compare_substring_substring(
    const string_t* cpt_stringfirst, size_t t_firstpos, size_t t_firstlen,
    const string_t* cpt_stringsecond, size_t t_secondpos, size_t t_secondlen)
{
    return string_compare_substring_subcstr(
        cpt_stringfirst, t_firstpos, t_firstlen, 
        basic_string_at(cpt_stringsecond, t_secondpos), t_secondlen);
}

int string_compare_cstr(const string_t* cpt_string, const char* s_cstr)
{
    bool_t t_result = false;

    _basic_string_pop_back((basic_string_t*)cpt_string);
    t_result = basic_string_compare_cstr(cpt_string, s_cstr);
    basic_string_push_back((basic_string_t*)cpt_string, '\0');

    return t_result;
}

int string_compare_substring_cstr(
    const string_t* cpt_string, size_t t_firstpos, size_t t_firstlen, const char* s_cstr)
{
    bool_t t_result = false;

    _basic_string_pop_back((basic_string_t*)cpt_string);
    t_result = basic_string_compare_substring_cstr(cpt_string, t_firstpos, t_firstlen, s_cstr);
    basic_string_push_back((basic_string_t*)cpt_string, '\0');

    return t_result;
}

int string_compare_substring_subcstr(
    const string_t* cpt_string, size_t t_firstpos, size_t t_firstlen,
    const char* s_cstr, size_t t_len)
{
    bool_t t_result = false;

    _basic_string_pop_back((basic_string_t*)cpt_string);
    t_result = basic_string_compare_substring_subcstr(
        cpt_string, t_firstpos, t_firstlen, s_cstr, t_len);
    basic_string_push_back((basic_string_t*)cpt_string, '\0');

    return t_result;
}

/* substr */
string_t* string_substr(const string_t* cpt_string, size_t t_pos, size_t t_len)
{
    string_t* pt_string = basic_string_substr(cpt_string, t_pos, t_len);
    assert(pt_string != NULL);
    basic_string_push_back(pt_string, '\0');

    return pt_string;
}

/* connection */
void string_connect(string_t* pt_string, const string_t* cpt_string_src)
{
    _basic_string_pop_back(pt_string);
    basic_string_connect(pt_string, cpt_string_src);
}

void string_connect_cstr(string_t* pt_string, const char* s_cstr)
{
    _basic_string_pop_back(pt_string);
    basic_string_connect_cstr(pt_string, s_cstr);
    basic_string_push_back(pt_string, '\0');
}

void string_connect_char(string_t* pt_string, char c_char)
{
    _basic_string_pop_back(pt_string);
    basic_string_connect_elem(pt_string, c_char);
    basic_string_push_back(pt_string, '\0');
}

/* find */
size_t string_find(
    const string_t* cpt_string, const string_t* cpt_string_find, size_t t_pos)
{
    return string_find_cstr(cpt_string, string_c_str(cpt_string_find), t_pos);
}

size_t string_find_cstr(
    const string_t* cpt_string, const char* s_cstr, size_t t_pos)
{
    size_t t_findpos = NPOS;

    _basic_string_pop_back((string_t*)cpt_string);
    t_findpos = basic_string_find_cstr(cpt_string, s_cstr, t_pos);
    basic_string_push_back((string_t*)cpt_string, '\0');

    return t_findpos;
}

size_t string_find_subcstr(
    const string_t* cpt_string, const char* s_cstr, size_t t_pos, size_t t_len)
{
    size_t t_findpos = NPOS;

    _basic_string_pop_back((string_t*)cpt_string);
    t_findpos = basic_string_find_subcstr(cpt_string, s_cstr, t_pos, t_len);
    basic_string_push_back((string_t*)cpt_string, '\0');

    return t_findpos;
}

size_t string_find_char(const string_t* cpt_string, char c_char, size_t t_pos)
{
    size_t t_findpos = NPOS;

    _basic_string_pop_back((string_t*)cpt_string);
    t_findpos = basic_string_find_elem(cpt_string, c_char, t_pos);
    basic_string_push_back((string_t*)cpt_string, '\0');

    return t_findpos;
}

size_t string_rfind(
    const string_t* cpt_string, const string_t* cpt_string_find, size_t t_pos)
{
    return string_rfind_cstr(cpt_string, string_c_str(cpt_string_find), t_pos);
}

size_t string_rfind_cstr(
    const string_t* cpt_string, const char* s_cstr, size_t t_pos)
{
    size_t t_findpos = NPOS;

    _basic_string_pop_back((string_t*)cpt_string);
    t_findpos = basic_string_rfind_cstr(cpt_string, s_cstr, t_pos);
    basic_string_push_back((string_t*)cpt_string, '\0');

    return t_findpos;
}

size_t string_rfind_subcstr(
    const string_t* cpt_string, const char* s_cstr, size_t t_pos, size_t t_len)
{
    size_t t_findpos = NPOS;

    _basic_string_pop_back((string_t*)cpt_string);
    t_findpos = basic_string_rfind_subcstr(cpt_string, s_cstr, t_pos, t_len);
    basic_string_push_back((string_t*)cpt_string, '\0');

    return t_findpos;
}

size_t string_rfind_char(const string_t* cpt_string, char c_char, size_t t_pos)
{
    size_t t_findpos = NPOS;

    _basic_string_pop_back((string_t*)cpt_string);
    t_findpos = basic_string_rfind_elem(cpt_string, c_char, t_pos);
    basic_string_push_back((string_t*)cpt_string, '\0');

    return t_findpos;
}

size_t string_find_first_of(
    const string_t* cpt_string, const string_t* cpt_string_find, size_t t_pos)
{
    return string_find_first_of_cstr(cpt_string, string_c_str(cpt_string_find), t_pos);
}

size_t string_find_first_of_cstr(
    const string_t* cpt_string, const char* s_cstr, size_t t_pos)
{
    size_t t_findpos = NPOS;

    _basic_string_pop_back((string_t*)cpt_string);
    t_findpos = basic_string_find_first_of_cstr(cpt_string, s_cstr, t_pos);
    basic_string_push_back((string_t*)cpt_string, '\0');

    return t_findpos;
}

size_t string_find_first_of_subcstr(
    const string_t* cpt_string, const char* s_cstr, size_t t_pos, size_t t_len)
{
    size_t t_findpos = NPOS;

    _basic_string_pop_back((string_t*)cpt_string);
    t_findpos = basic_string_find_first_of_subcstr(cpt_string, s_cstr, t_pos, t_len);
    basic_string_push_back((string_t*)cpt_string, '\0');

    return t_findpos;
}

size_t string_find_first_of_char(
    const string_t* cpt_string, char c_char, size_t t_pos)
{
    size_t t_findpos = NPOS;

    _basic_string_pop_back((string_t*)cpt_string);
    t_findpos = basic_string_find_first_of_elem(cpt_string, c_char, t_pos);
    basic_string_push_back((string_t*)cpt_string, '\0');

    return t_findpos;
}

size_t string_find_first_not_of(
    const string_t* cpt_string, const string_t* cpt_string_find, size_t t_pos)
{
    return string_find_first_not_of_cstr(cpt_string, string_c_str(cpt_string_find), t_pos);
}

size_t string_find_first_not_of_cstr(
    const string_t* cpt_string, const char* s_cstr, size_t t_pos)
{
    size_t t_findpos = NPOS;

    _basic_string_pop_back((string_t*)cpt_string);
    t_findpos = basic_string_find_first_not_of_cstr(cpt_string, s_cstr, t_pos);
    basic_string_push_back((string_t*)cpt_string, '\0');

    return t_findpos;
}

size_t string_find_first_not_of_subcstr(
    const string_t* cpt_string, const char* s_cstr, size_t t_pos, size_t t_len)
{
    size_t t_findpos = NPOS;

    _basic_string_pop_back((string_t*)cpt_string);
    t_findpos = basic_string_find_first_not_of_subcstr(cpt_string, s_cstr, t_pos, t_len);
    basic_string_push_back((string_t*)cpt_string, '\0');

    return t_findpos;
}

size_t string_find_first_not_of_char(
    const string_t* cpt_string, char c_char, size_t t_pos)
{
    size_t t_findpos = NPOS;

    _basic_string_pop_back((string_t*)cpt_string);
    t_findpos = basic_string_find_first_not_of_elem(cpt_string, c_char, t_pos);
    basic_string_push_back((string_t*)cpt_string, '\0');

    return t_findpos;
}

size_t string_find_last_of(
    const string_t* cpt_string, const string_t* cpt_string_find, size_t t_pos)
{
    return string_find_last_of_cstr(cpt_string, string_c_str(cpt_string_find), t_pos);
}

size_t string_find_last_of_cstr(
    const string_t* cpt_string, const char* s_cstr, size_t t_pos)
{
    size_t t_findpos = NPOS;

    _basic_string_pop_back((string_t*)cpt_string);
    t_findpos = basic_string_find_last_of_cstr(cpt_string, s_cstr, t_pos);
    basic_string_push_back((string_t*)cpt_string, '\0');

    return t_findpos;
}

size_t string_find_last_of_subcstr(
    const string_t* cpt_string, const char* s_cstr, size_t t_pos, size_t t_len)
{
    size_t t_findpos = NPOS;

    _basic_string_pop_back((string_t*)cpt_string);
    t_findpos = basic_string_find_last_of_subcstr(cpt_string, s_cstr, t_pos, t_len);
    basic_string_push_back((string_t*)cpt_string, '\0');

    return t_findpos;
}

size_t string_find_last_of_char(
    const string_t* cpt_string, char c_char, size_t t_pos)
{
    size_t t_findpos = NPOS;

    _basic_string_pop_back((string_t*)cpt_string);
    t_findpos = basic_string_find_last_of_elem(cpt_string, c_char, t_pos);
    basic_string_push_back((string_t*)cpt_string, '\0');

    return t_findpos;
}

size_t string_find_last_not_of(
    const string_t* cpt_string, const string_t* cpt_string_find, size_t t_pos)
{
    return string_find_last_not_of_cstr(cpt_string, string_c_str(cpt_string_find), t_pos);
}

size_t string_find_last_not_of_cstr(
    const string_t* cpt_string, const char* s_cstr, size_t t_pos)
{
    size_t t_findpos = NPOS;

    _basic_string_pop_back((string_t*)cpt_string);
    t_findpos = basic_string_find_last_not_of_cstr(cpt_string, s_cstr, t_pos);
    basic_string_push_back((string_t*)cpt_string, '\0');

    return t_findpos;
}

size_t string_find_last_not_of_subcstr(
    const string_t* cpt_string, const char* s_cstr, size_t t_pos, size_t t_len)
{
    size_t t_findpos = NPOS;

    _basic_string_pop_back((string_t*)cpt_string);
    t_findpos = basic_string_find_last_not_of_subcstr(cpt_string, s_cstr, t_pos, t_len);
    basic_string_push_back((string_t*)cpt_string, '\0');

    return t_findpos;
}

size_t string_find_last_not_of_char(
    const string_t* cpt_string, char c_char, size_t t_pos)
{
    size_t t_findpos = NPOS;

    _basic_string_pop_back((string_t*)cpt_string);
    t_findpos = basic_string_find_last_not_of_elem(cpt_string, c_char, t_pos);
    basic_string_push_back((string_t*)cpt_string, '\0');

    return t_findpos;
}

/* iterator support */
string_iterator_t string_begin(const string_t* cpt_string)
{
    return basic_string_begin(cpt_string);
}

string_iterator_t string_end(const string_t* cpt_string)
{
    return basic_string_rbegin(cpt_string);
}

string_reverse_iterator_t string_rbegin(const string_t* cpt_string)
{
    if(string_empty(cpt_string))
    {
        return basic_string_rbegin(cpt_string);
    }
    else
    {
        return iterator_prev(basic_string_rbegin(cpt_string));
    }
}

string_reverse_iterator_t string_rend(const string_t* cpt_string)
{
    return basic_string_rend(cpt_string);
}

/* clear swap ... */
void string_clear(string_t* pt_string)
{
    basic_string_clear(pt_string);
    basic_string_push_back(pt_string, '\0');
}

void string_swap(string_t* pt_stringfirst, string_t* pt_stringsecond)
{
    basic_string_swap(pt_stringfirst, pt_stringsecond);
}

void string_reserve(string_t* pt_string, size_t t_reservesize)
{
    basic_string_reserve(pt_string, t_reservesize + 1);
}

void string_resize(string_t* pt_string, size_t t_resize, char c_char)
{
    _basic_string_pop_back(pt_string);
    basic_string_resize(pt_string, t_resize, c_char);
    basic_string_push_back(pt_string, '\0');
}

void string_push_back(string_t* pt_string, char c_char)
{
    _basic_string_pop_back(pt_string);
    basic_string_push_back(pt_string, c_char);
    basic_string_push_back(pt_string, '\0');
}

/* assign and = */
void string_assign(string_t* pt_string, const string_t* cpt_string_assign)
{
    basic_string_assign(pt_string, cpt_string_assign);
}

void string_assign_substring(
    string_t* pt_string, const string_t* cpt_string_assign, size_t t_pos, size_t t_len)
{
    if(string_empty(cpt_string_assign))
    {
        string_assign_cstr(pt_string, "");
    }
    else
    {
        string_assign_subcstr(pt_string, string_at(cpt_string_assign, t_pos), t_len);
    }
}

void string_assign_cstr(string_t* pt_string, const char* s_cstr)
{
    basic_string_assign_cstr(pt_string, s_cstr);
    basic_string_push_back(pt_string, '\0');
}

void string_assign_subcstr(string_t* pt_string, const char* s_cstr, size_t t_len)
{
    basic_string_assign_subcstr(pt_string, s_cstr, t_len);
    basic_string_push_back(pt_string, '\0');
}

void string_assign_char(string_t* pt_string, size_t t_count, char c_char)
{
    basic_string_assign_elem(pt_string, t_count, c_char);
    basic_string_push_back(pt_string, '\0');
}

void string_assign_range(
    string_t* pt_string, string_iterator_t t_begin, string_iterator_t t_end)
{
    assert(!iterator_equal(t_end, basic_string_end(_GET_BASIC_STRING_CONTAINER(t_end))));
    basic_string_assign_range(pt_string, t_begin, t_end);
    basic_string_push_back(pt_string, '\0');
}

/* append + += */
void string_append(string_t* pt_string, const string_t* cpt_string_append)
{
    string_append_cstr(pt_string, string_c_str(cpt_string_append));
}

void string_append_substring(
    string_t* pt_string, const string_t* cpt_string_append, size_t t_pos, size_t t_len)
{
    if(string_empty(cpt_string_append))
    {
        string_append_cstr(pt_string, "");
    }
    else
    {
        string_append_subcstr(pt_string, string_at(cpt_string_append, t_pos), t_len);
    }
}

void string_append_cstr(string_t* pt_string, const char* s_cstr)
{
    _basic_string_pop_back(pt_string);
    basic_string_append_cstr(pt_string, s_cstr);
    basic_string_push_back(pt_string, '\0');
}

void string_append_subcstr(string_t* pt_string, const char* s_cstr, size_t t_len)
{
    _basic_string_pop_back(pt_string);
    basic_string_append_subcstr(pt_string, s_cstr, t_len);
    basic_string_push_back(pt_string, '\0');
}

void string_append_char(string_t* pt_string, size_t t_count, char c_char)
{
    _basic_string_pop_back(pt_string);
    basic_string_append_elem(pt_string, t_count, c_char);
    basic_string_push_back(pt_string, '\0');
}

void string_append_range(
    string_t* pt_string, string_iterator_t t_begin, string_iterator_t t_end)
{
    assert(!iterator_equal(t_end, basic_string_end(_GET_BASIC_STRING_CONTAINER(t_end))));
    _basic_string_pop_back(pt_string);
    basic_string_append_range(pt_string, t_begin, t_end);
    basic_string_push_back(pt_string, '\0');
}

/* insert */
string_iterator_t string_insert(
    string_t* pt_string, string_iterator_t t_pos, char c_char)
{
    return basic_string_insert(pt_string, t_pos, c_char);
}

string_iterator_t string_insert_n(
    string_t* pt_string, string_iterator_t t_pos, size_t t_count, char c_char)
{
    return basic_string_insert_n(pt_string, t_pos, t_count, c_char);
}

void string_insert_string(
    string_t* pt_string, size_t t_pos, const string_t* cpt_string_insert)
{
    _basic_string_pop_back(pt_string);
    basic_string_insert_cstr(pt_string, t_pos, string_c_str(cpt_string_insert));
    basic_string_push_back(pt_string, '\0');
}

void string_insert_substring(
    string_t* pt_string, size_t t_pos, const string_t* cpt_string_insert, 
    size_t t_startpos, size_t t_len)
{
    _basic_string_pop_back(pt_string);
    basic_string_insert_subcstr(
        pt_string, t_pos, string_at(cpt_string_insert, t_startpos), t_len);
    basic_string_push_back(pt_string, '\0');
}

void string_insert_cstr(string_t* pt_string, size_t t_pos, const char* s_cstr)
{
    _basic_string_pop_back(pt_string);
    basic_string_insert_cstr(pt_string, t_pos, s_cstr);
    basic_string_push_back(pt_string, '\0');
}

void string_insert_subcstr(
    string_t* pt_string, size_t t_pos, const char* s_cstr, size_t t_len)
{
    _basic_string_pop_back(pt_string);
    basic_string_insert_subcstr(pt_string, t_pos, s_cstr, t_len);
    basic_string_push_back(pt_string, '\0');
}

void string_insert_char(
    string_t* pt_string, size_t t_pos, size_t t_count, char c_char)
{
    _basic_string_pop_back(pt_string);
    basic_string_insert_elem(pt_string, t_pos, t_count, c_char);
    basic_string_push_back(pt_string, '\0');
}

void string_insert_range(
    string_t* pt_string, string_iterator_t t_pos,
    string_iterator_t t_begin, string_iterator_t t_end)
{
    basic_string_insert_range(pt_string, t_pos, t_begin, t_end);
}

/* erase */
string_iterator_t string_erase(string_t* pt_string, string_iterator_t t_pos)
{
    assert(!iterator_equal(t_pos, string_end(pt_string)));
    return basic_string_erase(pt_string, t_pos);
}

string_iterator_t string_erase_range(
    string_t* pt_string, string_iterator_t t_begin, string_iterator_t t_end)
{
    return basic_string_erase_range(pt_string, t_begin, t_end);
}

void string_erase_substring(string_t* pt_string, size_t t_pos, size_t t_len)
{
    _basic_string_pop_back(pt_string);
    basic_string_erase_substring(pt_string, t_pos, t_len);
    basic_string_push_back(pt_string, '\0');
}

/* replace */
void string_replace(
    string_t* pt_string, size_t t_pos, size_t t_len, const string_t* cpt_string_replace)
{
    _basic_string_pop_back(pt_string);
    _basic_string_pop_back((string_t*)cpt_string_replace);
    basic_string_replace(pt_string, t_pos, t_len, cpt_string_replace);
    basic_string_push_back(pt_string, '\0');
    basic_string_push_back((string_t*)cpt_string_replace, '\0');
}

void string_replace_substring(
    string_t* pt_string, size_t t_pos, size_t t_len,
    const string_t* cpt_string_replace, size_t t_position, size_t t_length)
{
    _basic_string_pop_back(pt_string);
    _basic_string_pop_back((string_t*)cpt_string_replace);
    basic_string_replace_substring(
        pt_string, t_pos, t_len, cpt_string_replace, t_position, t_length);
    basic_string_push_back(pt_string, '\0');
    basic_string_push_back((string_t*)cpt_string_replace, '\0');
}

void string_replace_cstr(
    string_t* pt_string, size_t t_pos, size_t t_len, const char* s_cstr)
{
    _basic_string_pop_back(pt_string);
    basic_string_replace_cstr(pt_string, t_pos, t_len, s_cstr);
    basic_string_push_back(pt_string, '\0');
}

void string_replace_subcstr(
    string_t* pt_string, size_t t_pos, size_t t_len, const char* s_cstr, size_t t_length)
{
    _basic_string_pop_back(pt_string);
    basic_string_replace_subcstr(pt_string, t_pos, t_len, s_cstr, t_length);
    basic_string_push_back(pt_string, '\0');
}

void string_replace_char(
    string_t* pt_string, size_t t_pos, size_t t_len, size_t t_count, char c_char)
{
    _basic_string_pop_back(pt_string);
    basic_string_replace_elem(pt_string, t_pos, t_len, t_count, c_char);
    basic_string_push_back(pt_string, '\0');
}

void string_range_replace(
    string_t* pt_string, string_iterator_t t_begin, string_iterator_t t_end,
    const string_t* cpt_string_replace)
{
    _basic_string_pop_back((string_t*)cpt_string_replace);
    basic_string_range_replace(pt_string, t_begin, t_end, cpt_string_replace);
    basic_string_push_back((string_t*)cpt_string_replace, '\0');
}

void string_range_replace_substring(
    string_t* pt_string, string_iterator_t t_begin, string_iterator_t t_end,
    const string_t* cpt_string_replace, size_t t_pos, size_t t_len)
{
    _basic_string_pop_back((string_t*)cpt_string_replace);
    basic_string_range_replace_substring(
        pt_string, t_begin, t_end, cpt_string_replace, t_pos, t_len);
    basic_string_push_back((string_t*)cpt_string_replace, '\0');
}

void string_range_replace_cstr(
    string_t* pt_string, string_iterator_t t_begin, string_iterator_t t_end,
    const char* s_cstr)
{
    basic_string_range_replace_cstr(pt_string, t_begin, t_end, s_cstr);
}

void string_range_replace_subcstr(
    string_t* pt_string, string_iterator_t t_begin, string_iterator_t t_end,
    const char* s_cstr, size_t t_len)
{
    basic_string_range_replace_subcstr(pt_string, t_begin, t_end, s_cstr, t_len);
}

void string_range_replace_char(
    string_t* pt_string, string_iterator_t t_begin, string_iterator_t t_end,
    size_t t_count, char c_char)
{
    basic_string_range_replace_elem(pt_string, t_begin, t_end, t_count, c_char);
}

void string_replace_range(
    string_t* pt_string, string_iterator_t t_begin, string_iterator_t t_end,
    string_iterator_t t_first, string_iterator_t t_last)
{
    basic_string_replace_range(pt_string, t_begin, t_end, t_first, t_last);
}

/* output input */
void string_output(const string_t* cpt_string, FILE* fp_stream)
{
    assert(cpt_string != NULL && fp_stream != NULL);
    fprintf(fp_stream, "%s", string_data(cpt_string));
}

void string_input(string_t* pt_string, FILE* fp_stream)
{
    int n_char = EOF;

    assert(pt_string != NULL && fp_stream != NULL);

    clearerr(fp_stream);
    string_clear(pt_string);
    while(!feof(fp_stream) && !ferror(fp_stream) &&
          string_size(pt_string) < string_max_size(pt_string))
    {
        n_char = fgetc(fp_stream);
        if(n_char != EOF)
        {
            string_push_back(pt_string, n_char);
        }
    }
}

bool_t string_getline(string_t* pt_string, FILE* fp_stream)
{
    int n_char = EOF;
#ifdef _WIN32
    int n_prevchar = EOF;
#endif

    assert(pt_string != NULL && fp_stream != NULL);

    clearerr(fp_stream);
    string_clear(pt_string);
    while(!feof(fp_stream) && !ferror(fp_stream) && n_char != '\n' &&
          string_size(pt_string) < string_max_size(pt_string))
    {
        n_char = fgetc(fp_stream);
        if(n_char != '\n' && n_char != EOF)
        {
#ifdef _WIN32
            /* new line is '\r\n' in Windows */
            if(n_prevchar != EOF)
            {
                assert(n_prevchar == '\r');
                string_push_back(pt_string, n_prevchar);
                n_prevchar = EOF;
            }
            if(n_char == '\r')
            {
                assert(n_prevchar == EOF);
                n_prevchar = n_char;
            }
            else
            {
                string_push_back(pt_string, n_char);
            }
#else
            string_push_back(pt_string, n_char);
#endif
        }
    }

#ifdef _WIN32
    if(feof(fp_stream))
    {
        if(n_prevchar != EOF)
        {
            assert(n_prevchar == '\r');
            string_push_back(pt_string, n_prevchar);
            n_prevchar = EOF;
        }

        return false;
    }
#endif

    if((char)n_char == '\n')
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool_t string_getline_delimiter(string_t* pt_string, FILE* fp_stream, char c_delimiter)
{
    int n_char = EOF;

    assert(pt_string != NULL && fp_stream != NULL);

    if(c_delimiter == '\n')
    {
        return string_getline(pt_string, fp_stream);
    }
    else
    {
        clearerr(fp_stream);
        string_clear(pt_string);
        while(!feof(fp_stream) && !ferror(fp_stream) && (char)n_char != c_delimiter &&
              string_size(pt_string) < string_max_size(pt_string))
        {
            n_char = fgetc(fp_stream);
            if((char)n_char != c_delimiter && n_char != EOF)
            {
                string_push_back(pt_string, n_char);
            }
        }

        if((char)n_char == c_delimiter)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

/** local function implementation section **/

/** eof **/

