/*
 *  The implementation of string_t.
 *  Copyright (C)  2008,2009,2010,2011  Wangbo
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
#include <cstl/cstl_def.h>
#include <cstl/cstl_alloc.h>
#include <cstl/cstl_types.h>
#include <cstl/cstl_iterator.h>
#include <cstl/cvector.h>

#include <cstl/cstl_basic_string_iterator.h>
#include <cstl/cstl_basic_string_private.h>
#include <cstl/cstl_basic_string.h>
#include <cstl/cstl_string_iterator.h>
#include <cstl/cstl_string_private.h>
#include <cstl/cstl_string.h>

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Create string container.
 */
string_t* create_string(void)
{
    return create_basic_string(char);
}

/**
 * Initialize empty string container.
 */
void string_init(string_t* pstr_string)
{
    assert(pstr_string != NULL);

    basic_string_init(pstr_string);
    basic_string_push_back(pstr_string, '\0');
}

/**
 * Initialize string container specific c-string.
 */
void string_init_cstr(string_t* pstr_string, const char* s_cstr)
{
    assert(pstr_string != NULL);
    assert(s_cstr != NULL);

    basic_string_init_cstr(pstr_string, s_cstr);
    basic_string_push_back(pstr_string, '\0');
}

void string_init_subcstr(string_t* pstr_string, const char* s_cstr, size_t t_count)
{
    assert(pstr_string != NULL);

    basic_string_init_subcstr(pstr_string, s_cstr, t_count);
    basic_string_push_back(pstr_string, '\0');
}

/**
 * Initialize string with specified character.
 */
void string_init_char(string_t* pstr_string, size_t t_count, char c_char)
{
    assert(pstr_string != NULL);

    basic_string_init_elem(pstr_string, t_count, c_char);
    basic_string_push_back(pstr_string, '\0');
}

void string_init_copy(string_t* pstr_string, const string_t* cpstr_string_src)
{
    assert(pstr_string != NULL && cpstr_string_src != NULL);

    basic_string_init_copy(pstr_string, cpstr_string_src);
}

void string_init_copy_substring(
    string_t* pstr_string, const string_t* cpstr_string_src, size_t t_pos, size_t t_len)
{
    assert(pstr_string != NULL && cpstr_string_src != NULL);

    basic_string_init_copy_substring(pstr_string, cpstr_string_src, t_pos, t_len);
    if(t_len != NPOS && t_pos + t_len <= string_size(cpstr_string_src))
    {
        basic_string_push_back(pstr_string, '\0');
    }
}

void string_init_copy_range(
    string_t* pstr_string, string_iterator_t t_begin, string_iterator_t t_end)
{
    assert(pstr_string != NULL);

    basic_string_init_copy_range(pstr_string, t_begin, t_end);
    if(!iterator_equal(t_end, basic_string_end(_GET_BASIC_STRING_CONTAINER(t_end))))
    {
        basic_string_push_back(pstr_string, '\0');
    }
}

void string_destroy(string_t* pstr_string)
{
    basic_string_destroy(pstr_string);
}

/* c_str and data */
const char* string_c_str(const string_t* cpstr_string)
{
    return basic_string_c_str(cpstr_string);
}

const char* string_data(const string_t* cpstr_string)
{
    return basic_string_data(cpstr_string);
}

size_t string_copy(
    const string_t* cpstr_string, char* s_buffer, size_t t_copysize, size_t t_copypos)
{
    return basic_string_copy(cpstr_string, s_buffer, t_copysize, t_copypos);
}

/* size, max_size ... */
size_t string_size(const string_t* cpstr_string)
{
    return basic_string_size(cpstr_string) - 1;
}

size_t string_length(const string_t* cpstr_string)
{
    return basic_string_length(cpstr_string) - 1;
}

size_t string_max_size(const string_t* cpstr_string)
{
    return basic_string_max_size(cpstr_string) - 1;
}

size_t string_capacity(const string_t* cpstr_string)
{
    return basic_string_capacity(cpstr_string) - 1;
}

bool_t string_empty(const string_t* cpstr_string)
{
    return string_size(cpstr_string) == 0 ? true : false;
}

char* string_at(const string_t* cpstr_string, size_t t_pos)
{
    assert(t_pos < basic_string_length(cpstr_string));
    return (char*)basic_string_at(cpstr_string, t_pos);
}

/* compare operator */
bool_t string_equal(
    const string_t* cpstr_stringfirst, const string_t* cpstr_stringsecond)
{
    return basic_string_equal(cpstr_stringfirst, cpstr_stringsecond);
}

bool_t string_not_equal(
    const string_t* cpstr_stringfirst, const string_t* cpstr_stringsecond)
{
    return basic_string_not_equal(cpstr_stringfirst, cpstr_stringsecond);
}

bool_t string_less(
    const string_t* cpstr_stringfirst, const string_t* cpstr_stringsecond)
{
    return basic_string_less(cpstr_stringfirst, cpstr_stringsecond);
}

bool_t string_less_equal(
    const string_t* cpstr_stringfirst, const string_t* cpstr_stringsecond)
{
    return basic_string_less_equal(cpstr_stringfirst, cpstr_stringsecond);
}

bool_t string_greater(
    const string_t* cpstr_stringfirst, const string_t* cpstr_stringsecond)
{
    return basic_string_greater(cpstr_stringfirst, cpstr_stringsecond);
}

bool_t string_greater_equal(
    const string_t* cpstr_stringfirst, const string_t* cpstr_stringsecond)
{
    return basic_string_greater_equal(cpstr_stringfirst, cpstr_stringsecond);
}

bool_t string_equal_cstr(const string_t* cpstr_string, const char* s_cstr)
{
    bool_t t_result = false;

    _basic_string_pop_back((basic_string_t*)cpstr_string);
    t_result = basic_string_equal_cstr(cpstr_string, s_cstr);
    basic_string_push_back((basic_string_t*)cpstr_string, '\0');

    return t_result;
}

bool_t string_not_equal_cstr(const string_t* cpstr_string, const char* s_cstr)
{
    bool_t t_result = false;

    _basic_string_pop_back((basic_string_t*)cpstr_string);
    t_result = basic_string_not_equal_cstr(cpstr_string, s_cstr);
    basic_string_push_back((basic_string_t*)cpstr_string, '\0');

    return t_result;
}

bool_t string_less_cstr(const string_t* cpstr_string, const char* s_cstr)
{
    bool_t t_result = false;

    _basic_string_pop_back((basic_string_t*)cpstr_string);
    t_result = basic_string_less_cstr(cpstr_string, s_cstr);
    basic_string_push_back((basic_string_t*)cpstr_string, '\0');

    return t_result;
}

bool_t string_less_equal_cstr(const string_t* cpstr_string, const char* s_cstr)
{
    bool_t t_result = false;

    _basic_string_pop_back((basic_string_t*)cpstr_string);
    t_result = basic_string_less_equal_cstr(cpstr_string, s_cstr);
    basic_string_push_back((basic_string_t*)cpstr_string, '\0');

    return t_result;
}

bool_t string_greater_cstr(const string_t* cpstr_string, const char* s_cstr)
{
    bool_t t_result = false;

    _basic_string_pop_back((basic_string_t*)cpstr_string);
    t_result = basic_string_greater_cstr(cpstr_string, s_cstr);
    basic_string_push_back((basic_string_t*)cpstr_string, '\0');

    return t_result;
}

bool_t string_greater_equal_cstr(const string_t* cpstr_string, const char* s_cstr)
{
    bool_t t_result = false;

    _basic_string_pop_back((basic_string_t*)cpstr_string);
    t_result = basic_string_greater_equal_cstr(cpstr_string, s_cstr);
    basic_string_push_back((basic_string_t*)cpstr_string, '\0');

    return t_result;
}

int string_compare(
    const string_t* cpstr_stringfirst, const string_t* cpstr_stringsecond)
{
    return string_compare_cstr(cpstr_stringfirst, string_c_str(cpstr_stringsecond));
}

int string_compare_substring_string(
    const string_t* cpstr_stringfirst, size_t t_firstpos, size_t t_firstlen,
    const string_t* cpstr_stringsecond)
{
    return string_compare_substring_cstr(
        cpstr_stringfirst, t_firstpos, t_firstlen, string_c_str(cpstr_stringsecond));
}

int string_compare_substring_substring(
    const string_t* cpstr_stringfirst, size_t t_firstpos, size_t t_firstlen,
    const string_t* cpstr_stringsecond, size_t t_secondpos, size_t t_secondlen)
{
    return string_compare_substring_subcstr(
        cpstr_stringfirst, t_firstpos, t_firstlen, 
        basic_string_at(cpstr_stringsecond, t_secondpos), t_secondlen);
}

int string_compare_cstr(const string_t* cpstr_string, const char* s_cstr)
{
    bool_t t_result = false;

    _basic_string_pop_back((basic_string_t*)cpstr_string);
    t_result = basic_string_compare_cstr(cpstr_string, s_cstr);
    basic_string_push_back((basic_string_t*)cpstr_string, '\0');

    return t_result;
}

int string_compare_substring_cstr(
    const string_t* cpstr_string, size_t t_firstpos, size_t t_firstlen, const char* s_cstr)
{
    bool_t t_result = false;

    _basic_string_pop_back((basic_string_t*)cpstr_string);
    t_result = basic_string_compare_substring_cstr(cpstr_string, t_firstpos, t_firstlen, s_cstr);
    basic_string_push_back((basic_string_t*)cpstr_string, '\0');

    return t_result;
}

int string_compare_substring_subcstr(
    const string_t* cpstr_string, size_t t_firstpos, size_t t_firstlen,
    const char* s_cstr, size_t t_len)
{
    bool_t t_result = false;

    _basic_string_pop_back((basic_string_t*)cpstr_string);
    t_result = basic_string_compare_substring_subcstr(
        cpstr_string, t_firstpos, t_firstlen, s_cstr, t_len);
    basic_string_push_back((basic_string_t*)cpstr_string, '\0');

    return t_result;
}

/* substr */
string_t* string_substr(const string_t* cpstr_string, size_t t_pos, size_t t_len)
{
    string_t* pstr_string = basic_string_substr(cpstr_string, t_pos, t_len);
    assert(pstr_string != NULL);
    basic_string_push_back(pstr_string, '\0');

    return pstr_string;
}

/* connection */
void string_connect(string_t* pstr_string, const string_t* cpstr_string_src)
{
    _basic_string_pop_back(pstr_string);
    basic_string_connect(pstr_string, cpstr_string_src);
}

void string_connect_cstr(string_t* pstr_string, const char* s_cstr)
{
    _basic_string_pop_back(pstr_string);
    basic_string_connect_cstr(pstr_string, s_cstr);
    basic_string_push_back(pstr_string, '\0');
}

void string_connect_char(string_t* pstr_string, char c_char)
{
    _basic_string_pop_back(pstr_string);
    basic_string_connect_elem(pstr_string, c_char);
    basic_string_push_back(pstr_string, '\0');
}

/* find */
size_t string_find(
    const string_t* cpstr_string, const string_t* cpstr_string_find, size_t t_pos)
{
    return string_find_cstr(cpstr_string, string_c_str(cpstr_string_find), t_pos);
}

size_t string_find_cstr(
    const string_t* cpstr_string, const char* s_cstr, size_t t_pos)
{
    size_t t_findpos = NPOS;

    _basic_string_pop_back((string_t*)cpstr_string);
    t_findpos = basic_string_find_cstr(cpstr_string, s_cstr, t_pos);
    basic_string_push_back((string_t*)cpstr_string, '\0');

    return t_findpos;
}

size_t string_find_subcstr(
    const string_t* cpstr_string, const char* s_cstr, size_t t_pos, size_t t_len)
{
    size_t t_findpos = NPOS;

    _basic_string_pop_back((string_t*)cpstr_string);
    t_findpos = basic_string_find_subcstr(cpstr_string, s_cstr, t_pos, t_len);
    basic_string_push_back((string_t*)cpstr_string, '\0');

    return t_findpos;
}

size_t string_find_char(const string_t* cpstr_string, char c_char, size_t t_pos)
{
    size_t t_findpos = NPOS;

    _basic_string_pop_back((string_t*)cpstr_string);
    t_findpos = basic_string_find_elem(cpstr_string, c_char, t_pos);
    basic_string_push_back((string_t*)cpstr_string, '\0');

    return t_findpos;
}

size_t string_rfind(
    const string_t* cpstr_string, const string_t* cpstr_string_find, size_t t_pos)
{
    return string_rfind_cstr(cpstr_string, string_c_str(cpstr_string_find), t_pos);
}

size_t string_rfind_cstr(
    const string_t* cpstr_string, const char* s_cstr, size_t t_pos)
{
    size_t t_findpos = NPOS;

    _basic_string_pop_back((string_t*)cpstr_string);
    t_findpos = basic_string_rfind_cstr(cpstr_string, s_cstr, t_pos);
    basic_string_push_back((string_t*)cpstr_string, '\0');

    return t_findpos;
}

size_t string_rfind_subcstr(
    const string_t* cpstr_string, const char* s_cstr, size_t t_pos, size_t t_len)
{
    size_t t_findpos = NPOS;

    _basic_string_pop_back((string_t*)cpstr_string);
    t_findpos = basic_string_rfind_subcstr(cpstr_string, s_cstr, t_pos, t_len);
    basic_string_push_back((string_t*)cpstr_string, '\0');

    return t_findpos;
}

size_t string_rfind_char(const string_t* cpstr_string, char c_char, size_t t_pos)
{
    size_t t_findpos = NPOS;

    _basic_string_pop_back((string_t*)cpstr_string);
    t_findpos = basic_string_rfind_elem(cpstr_string, c_char, t_pos);
    basic_string_push_back((string_t*)cpstr_string, '\0');

    return t_findpos;
}

size_t string_find_first_of(
    const string_t* cpstr_string, const string_t* cpstr_string_find, size_t t_pos)
{
    return string_find_first_of_cstr(cpstr_string, string_c_str(cpstr_string_find), t_pos);
}

size_t string_find_first_of_cstr(
    const string_t* cpstr_string, const char* s_cstr, size_t t_pos)
{
    size_t t_findpos = NPOS;

    _basic_string_pop_back((string_t*)cpstr_string);
    t_findpos = basic_string_find_first_of_cstr(cpstr_string, s_cstr, t_pos);
    basic_string_push_back((string_t*)cpstr_string, '\0');

    return t_findpos;
}

size_t string_find_first_of_subcstr(
    const string_t* cpstr_string, const char* s_cstr, size_t t_pos, size_t t_len)
{
    size_t t_findpos = NPOS;

    _basic_string_pop_back((string_t*)cpstr_string);
    t_findpos = basic_string_find_first_of_subcstr(cpstr_string, s_cstr, t_pos, t_len);
    basic_string_push_back((string_t*)cpstr_string, '\0');

    return t_findpos;
}

size_t string_find_first_of_char(
    const string_t* cpstr_string, char c_char, size_t t_pos)
{
    size_t t_findpos = NPOS;

    _basic_string_pop_back((string_t*)cpstr_string);
    t_findpos = basic_string_find_first_of_elem(cpstr_string, c_char, t_pos);
    basic_string_push_back((string_t*)cpstr_string, '\0');

    return t_findpos;
}

size_t string_find_first_not_of(
    const string_t* cpstr_string, const string_t* cpstr_string_find, size_t t_pos)
{
    return string_find_first_not_of_cstr(cpstr_string, string_c_str(cpstr_string_find), t_pos);
}

size_t string_find_first_not_of_cstr(
    const string_t* cpstr_string, const char* s_cstr, size_t t_pos)
{
    size_t t_findpos = NPOS;

    _basic_string_pop_back((string_t*)cpstr_string);
    t_findpos = basic_string_find_first_not_of_cstr(cpstr_string, s_cstr, t_pos);
    basic_string_push_back((string_t*)cpstr_string, '\0');

    return t_findpos;
}

size_t string_find_first_not_of_subcstr(
    const string_t* cpstr_string, const char* s_cstr, size_t t_pos, size_t t_len)
{
    size_t t_findpos = NPOS;

    _basic_string_pop_back((string_t*)cpstr_string);
    t_findpos = basic_string_find_first_not_of_subcstr(cpstr_string, s_cstr, t_pos, t_len);
    basic_string_push_back((string_t*)cpstr_string, '\0');

    return t_findpos;
}

size_t string_find_first_not_of_char(
    const string_t* cpstr_string, char c_char, size_t t_pos)
{
    size_t t_findpos = NPOS;

    _basic_string_pop_back((string_t*)cpstr_string);
    t_findpos = basic_string_find_first_not_of_elem(cpstr_string, c_char, t_pos);
    basic_string_push_back((string_t*)cpstr_string, '\0');

    return t_findpos;
}

size_t string_find_last_of(
    const string_t* cpstr_string, const string_t* cpstr_string_find, size_t t_pos)
{
    return string_find_last_of_cstr(cpstr_string, string_c_str(cpstr_string_find), t_pos);
}

size_t string_find_last_of_cstr(
    const string_t* cpstr_string, const char* s_cstr, size_t t_pos)
{
    size_t t_findpos = NPOS;

    _basic_string_pop_back((string_t*)cpstr_string);
    t_findpos = basic_string_find_last_of_cstr(cpstr_string, s_cstr, t_pos);
    basic_string_push_back((string_t*)cpstr_string, '\0');

    return t_findpos;
}

size_t string_find_last_of_subcstr(
    const string_t* cpstr_string, const char* s_cstr, size_t t_pos, size_t t_len)
{
    size_t t_findpos = NPOS;

    _basic_string_pop_back((string_t*)cpstr_string);
    t_findpos = basic_string_find_last_of_subcstr(cpstr_string, s_cstr, t_pos, t_len);
    basic_string_push_back((string_t*)cpstr_string, '\0');

    return t_findpos;
}

size_t string_find_last_of_char(
    const string_t* cpstr_string, char c_char, size_t t_pos)
{
    size_t t_findpos = NPOS;

    _basic_string_pop_back((string_t*)cpstr_string);
    t_findpos = basic_string_find_last_of_elem(cpstr_string, c_char, t_pos);
    basic_string_push_back((string_t*)cpstr_string, '\0');

    return t_findpos;
}

size_t string_find_last_not_of(
    const string_t* cpstr_string, const string_t* cpstr_string_find, size_t t_pos)
{
    return string_find_last_not_of_cstr(cpstr_string, string_c_str(cpstr_string_find), t_pos);
}

size_t string_find_last_not_of_cstr(
    const string_t* cpstr_string, const char* s_cstr, size_t t_pos)
{
    size_t t_findpos = NPOS;

    _basic_string_pop_back((string_t*)cpstr_string);
    t_findpos = basic_string_find_last_not_of_cstr(cpstr_string, s_cstr, t_pos);
    basic_string_push_back((string_t*)cpstr_string, '\0');

    return t_findpos;
}

size_t string_find_last_not_of_subcstr(
    const string_t* cpstr_string, const char* s_cstr, size_t t_pos, size_t t_len)
{
    size_t t_findpos = NPOS;

    _basic_string_pop_back((string_t*)cpstr_string);
    t_findpos = basic_string_find_last_not_of_subcstr(cpstr_string, s_cstr, t_pos, t_len);
    basic_string_push_back((string_t*)cpstr_string, '\0');

    return t_findpos;
}

size_t string_find_last_not_of_char(
    const string_t* cpstr_string, char c_char, size_t t_pos)
{
    size_t t_findpos = NPOS;

    _basic_string_pop_back((string_t*)cpstr_string);
    t_findpos = basic_string_find_last_not_of_elem(cpstr_string, c_char, t_pos);
    basic_string_push_back((string_t*)cpstr_string, '\0');

    return t_findpos;
}

/* iterator support */
string_iterator_t string_begin(const string_t* cpstr_string)
{
    return basic_string_begin(cpstr_string);
}

string_iterator_t string_end(const string_t* cpstr_string)
{
    return basic_string_rbegin(cpstr_string);
}

string_reverse_iterator_t string_rbegin(const string_t* cpstr_string)
{
    if(string_empty(cpstr_string))
    {
        return basic_string_rbegin(cpstr_string);
    }
    else
    {
        return iterator_prev(basic_string_rbegin(cpstr_string));
    }
}

string_reverse_iterator_t string_rend(const string_t* cpstr_string)
{
    return basic_string_rend(cpstr_string);
}

/* clear swap ... */
void string_clear(string_t* pstr_string)
{
    basic_string_clear(pstr_string);
    basic_string_push_back(pstr_string, '\0');
}

void string_swap(string_t* pstr_stringfirst, string_t* pstr_stringsecond)
{
    basic_string_swap(pstr_stringfirst, pstr_stringsecond);
}

void string_reserve(string_t* pstr_string, size_t t_reservesize)
{
    basic_string_reserve(pstr_string, t_reservesize + 1);
}

void string_resize(string_t* pstr_string, size_t t_resize, char c_char)
{
    _basic_string_pop_back(pstr_string);
    basic_string_resize(pstr_string, t_resize, c_char);
    basic_string_push_back(pstr_string, '\0');
}

void string_push_back(string_t* pstr_string, char c_char)
{
    _basic_string_pop_back(pstr_string);
    basic_string_push_back(pstr_string, c_char);
    basic_string_push_back(pstr_string, '\0');
}

/* assign and = */
void string_assign(string_t* pstr_string, const string_t* cpstr_string_assign)
{
    basic_string_assign(pstr_string, cpstr_string_assign);
}

void string_assign_substring(
    string_t* pstr_string, const string_t* cpstr_string_assign, size_t t_pos, size_t t_len)
{
    if(string_empty(cpstr_string_assign))
    {
        string_assign_cstr(pstr_string, "");
    }
    else
    {
        string_assign_subcstr(pstr_string, string_at(cpstr_string_assign, t_pos), t_len);
    }
}

void string_assign_cstr(string_t* pstr_string, const char* s_cstr)
{
    basic_string_assign_cstr(pstr_string, s_cstr);
    basic_string_push_back(pstr_string, '\0');
}

void string_assign_subcstr(string_t* pstr_string, const char* s_cstr, size_t t_len)
{
    basic_string_assign_subcstr(pstr_string, s_cstr, t_len);
    basic_string_push_back(pstr_string, '\0');
}

void string_assign_char(string_t* pstr_string, size_t t_count, char c_char)
{
    basic_string_assign_elem(pstr_string, t_count, c_char);
    basic_string_push_back(pstr_string, '\0');
}

void string_assign_range(
    string_t* pstr_string, string_iterator_t t_begin, string_iterator_t t_end)
{
    assert(!iterator_equal(t_end, basic_string_end(_GET_BASIC_STRING_CONTAINER(t_end))));
    basic_string_assign_range(pstr_string, t_begin, t_end);
    basic_string_push_back(pstr_string, '\0');
}

/* append + += */
void string_append(string_t* pstr_string, const string_t* cpstr_string_append)
{
    string_append_cstr(pstr_string, string_c_str(cpstr_string_append));
}

void string_append_substring(
    string_t* pstr_string, const string_t* cpstr_string_append, size_t t_pos, size_t t_len)
{
    if(string_empty(cpstr_string_append))
    {
        string_append_cstr(pstr_string, "");
    }
    else
    {
        string_append_subcstr(pstr_string, string_at(cpstr_string_append, t_pos), t_len);
    }
}

void string_append_cstr(string_t* pstr_string, const char* s_cstr)
{
    _basic_string_pop_back(pstr_string);
    basic_string_append_cstr(pstr_string, s_cstr);
    basic_string_push_back(pstr_string, '\0');
}

void string_append_subcstr(string_t* pstr_string, const char* s_cstr, size_t t_len)
{
    _basic_string_pop_back(pstr_string);
    basic_string_append_subcstr(pstr_string, s_cstr, t_len);
    basic_string_push_back(pstr_string, '\0');
}

void string_append_char(string_t* pstr_string, size_t t_count, char c_char)
{
    _basic_string_pop_back(pstr_string);
    basic_string_append_elem(pstr_string, t_count, c_char);
    basic_string_push_back(pstr_string, '\0');
}

void string_append_range(
    string_t* pstr_string, string_iterator_t t_begin, string_iterator_t t_end)
{
    assert(!iterator_equal(t_end, basic_string_end(_GET_BASIC_STRING_CONTAINER(t_end))));
    _basic_string_pop_back(pstr_string);
    basic_string_append_range(pstr_string, t_begin, t_end);
    basic_string_push_back(pstr_string, '\0');
}

/* insert */
string_iterator_t string_insert(
    string_t* pstr_string, string_iterator_t t_pos, char c_char)
{
    return basic_string_insert(pstr_string, t_pos, c_char);
}

string_iterator_t string_insert_n(
    string_t* pstr_string, string_iterator_t t_pos, size_t t_count, char c_char)
{
    return basic_string_insert_n(pstr_string, t_pos, t_count, c_char);
}

void string_insert_string(
    string_t* pstr_string, size_t t_pos, const string_t* cpstr_string_insert)
{
    _basic_string_pop_back(pstr_string);
    basic_string_insert_cstr(pstr_string, t_pos, string_c_str(cpstr_string_insert));
    basic_string_push_back(pstr_string, '\0');
}

void string_insert_substring(
    string_t* pstr_string, size_t t_pos, const string_t* cpstr_string_insert, 
    size_t t_startpos, size_t t_len)
{
    _basic_string_pop_back(pstr_string);
    basic_string_insert_subcstr(
        pstr_string, t_pos, string_at(cpstr_string_insert, t_startpos), t_len);
    basic_string_push_back(pstr_string, '\0');
}

void string_insert_cstr(string_t* pstr_string, size_t t_pos, const char* s_cstr)
{
    _basic_string_pop_back(pstr_string);
    basic_string_insert_cstr(pstr_string, t_pos, s_cstr);
    basic_string_push_back(pstr_string, '\0');
}

void string_insert_subcstr(
    string_t* pstr_string, size_t t_pos, const char* s_cstr, size_t t_len)
{
    _basic_string_pop_back(pstr_string);
    basic_string_insert_subcstr(pstr_string, t_pos, s_cstr, t_len);
    basic_string_push_back(pstr_string, '\0');
}

void string_insert_char(
    string_t* pstr_string, size_t t_pos, size_t t_count, char c_char)
{
    _basic_string_pop_back(pstr_string);
    basic_string_insert_elem(pstr_string, t_pos, t_count, c_char);
    basic_string_push_back(pstr_string, '\0');
}

void string_insert_range(
    string_t* pstr_string, string_iterator_t t_pos,
    string_iterator_t t_begin, string_iterator_t t_end)
{
    basic_string_insert_range(pstr_string, t_pos, t_begin, t_end);
}

/* erase */
string_iterator_t string_erase(string_t* pstr_string, string_iterator_t t_pos)
{
    assert(!iterator_equal(t_pos, string_end(pstr_string)));
    return basic_string_erase(pstr_string, t_pos);
}

string_iterator_t string_erase_range(
    string_t* pstr_string, string_iterator_t t_begin, string_iterator_t t_end)
{
    return basic_string_erase_range(pstr_string, t_begin, t_end);
}

void string_erase_substring(string_t* pstr_string, size_t t_pos, size_t t_len)
{
    _basic_string_pop_back(pstr_string);
    basic_string_erase_substring(pstr_string, t_pos, t_len);
    basic_string_push_back(pstr_string, '\0');
}

/* replace */
void string_replace(
    string_t* pstr_string, size_t t_pos, size_t t_len, const string_t* cpstr_string_replace)
{
    _basic_string_pop_back(pstr_string);
    _basic_string_pop_back((string_t*)cpstr_string_replace);
    basic_string_replace(pstr_string, t_pos, t_len, cpstr_string_replace);
    basic_string_push_back(pstr_string, '\0');
    basic_string_push_back((string_t*)cpstr_string_replace, '\0');
}

void string_replace_substring(
    string_t* pstr_string, size_t t_pos, size_t t_len,
    const string_t* cpstr_string_replace, size_t t_position, size_t t_length)
{
    _basic_string_pop_back(pstr_string);
    _basic_string_pop_back((string_t*)cpstr_string_replace);
    basic_string_replace_substring(
        pstr_string, t_pos, t_len, cpstr_string_replace, t_position, t_length);
    basic_string_push_back(pstr_string, '\0');
    basic_string_push_back((string_t*)cpstr_string_replace, '\0');
}

void string_replace_cstr(
    string_t* pstr_string, size_t t_pos, size_t t_len, const char* s_cstr)
{
    _basic_string_pop_back(pstr_string);
    basic_string_replace_cstr(pstr_string, t_pos, t_len, s_cstr);
    basic_string_push_back(pstr_string, '\0');
}

void string_replace_subcstr(
    string_t* pstr_string, size_t t_pos, size_t t_len, const char* s_cstr, size_t t_length)
{
    _basic_string_pop_back(pstr_string);
    basic_string_replace_subcstr(pstr_string, t_pos, t_len, s_cstr, t_length);
    basic_string_push_back(pstr_string, '\0');
}

void string_replace_char(
    string_t* pstr_string, size_t t_pos, size_t t_len, size_t t_count, char c_char)
{
    _basic_string_pop_back(pstr_string);
    basic_string_replace_elem(pstr_string, t_pos, t_len, t_count, c_char);
    basic_string_push_back(pstr_string, '\0');
}

void string_range_replace(
    string_t* pstr_string, string_iterator_t t_begin, string_iterator_t t_end,
    const string_t* cpstr_string_replace)
{
    _basic_string_pop_back((string_t*)cpstr_string_replace);
    basic_string_range_replace(pstr_string, t_begin, t_end, cpstr_string_replace);
    basic_string_push_back((string_t*)cpstr_string_replace, '\0');
}

void string_range_replace_substring(
    string_t* pstr_string, string_iterator_t t_begin, string_iterator_t t_end,
    const string_t* cpstr_string_replace, size_t t_pos, size_t t_len)
{
    _basic_string_pop_back((string_t*)cpstr_string_replace);
    basic_string_range_replace_substring(
        pstr_string, t_begin, t_end, cpstr_string_replace, t_pos, t_len);
    basic_string_push_back((string_t*)cpstr_string_replace, '\0');
}

void string_range_replace_cstr(
    string_t* pstr_string, string_iterator_t t_begin, string_iterator_t t_end,
    const char* s_cstr)
{
    basic_string_range_replace_cstr(pstr_string, t_begin, t_end, s_cstr);
}

void string_range_replace_subcstr(
    string_t* pstr_string, string_iterator_t t_begin, string_iterator_t t_end,
    const char* s_cstr, size_t t_len)
{
    basic_string_range_replace_subcstr(pstr_string, t_begin, t_end, s_cstr, t_len);
}

void string_range_replace_char(
    string_t* pstr_string, string_iterator_t t_begin, string_iterator_t t_end,
    size_t t_count, char c_char)
{
    basic_string_range_replace_elem(pstr_string, t_begin, t_end, t_count, c_char);
}

void string_replace_range(
    string_t* pstr_string, string_iterator_t t_begin, string_iterator_t t_end,
    string_iterator_t t_first, string_iterator_t t_last)
{
    basic_string_replace_range(pstr_string, t_begin, t_end, t_first, t_last);
}

/* output input */
void string_output(const string_t* cpstr_string, FILE* fp_stream)
{
    assert(cpstr_string != NULL && fp_stream != NULL);
    fprintf(fp_stream, "%s", string_data(cpstr_string));
}

void string_input(string_t* pstr_string, FILE* fp_stream)
{
    int n_char = EOF;

    assert(pstr_string != NULL && fp_stream != NULL);

    clearerr(fp_stream);
    string_clear(pstr_string);
    while(!feof(fp_stream) && !ferror(fp_stream) &&
          string_size(pstr_string) < string_max_size(pstr_string))
    {
        n_char = fgetc(fp_stream);
        if(n_char != EOF)
        {
            string_push_back(pstr_string, n_char);
        }
    }
}

bool_t string_getline(string_t* pstr_string, FILE* fp_stream)
{
    int n_char = EOF;
#ifdef _WIN32
    int n_prevchar = EOF;
#endif

    assert(pstr_string != NULL && fp_stream != NULL);

    clearerr(fp_stream);
    string_clear(pstr_string);
    while(!feof(fp_stream) && !ferror(fp_stream) && n_char != '\n' &&
          string_size(pstr_string) < string_max_size(pstr_string))
    {
        n_char = fgetc(fp_stream);
        if(n_char != '\n' && n_char != EOF)
        {
#ifdef _WIN32
            /* new line is '\r\n' in Windows */
            if(n_prevchar != EOF)
            {
                assert(n_prevchar == '\r');
                string_push_back(pstr_string, n_prevchar);
                n_prevchar = EOF;
            }
            if(n_char == '\r')
            {
                assert(n_prevchar == EOF);
                n_prevchar = n_char;
            }
            else
            {
                string_push_back(pstr_string, n_char);
            }
#else
            string_push_back(pstr_string, n_char);
#endif
        }
    }

#ifdef _WIN32
    if(feof(fp_stream))
    {
        if(n_prevchar != EOF)
        {
            assert(n_prevchar == '\r');
            string_push_back(pstr_string, n_prevchar);
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

bool_t string_getline_delimiter(string_t* pstr_string, FILE* fp_stream, char c_delimiter)
{
    int n_char = EOF;

    assert(pstr_string != NULL && fp_stream != NULL);

    if(c_delimiter == '\n')
    {
        return string_getline(pstr_string, fp_stream);
    }
    else
    {
        clearerr(fp_stream);
        string_clear(pstr_string);
        while(!feof(fp_stream) && !ferror(fp_stream) && (char)n_char != c_delimiter &&
              string_size(pstr_string) < string_max_size(pstr_string))
        {
            n_char = fgetc(fp_stream);
            if((char)n_char != c_delimiter && n_char != EOF)
            {
                string_push_back(pstr_string, n_char);
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

