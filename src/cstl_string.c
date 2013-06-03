/*
 *  The implementation of string_t.
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

/** include section **/
#include <cstl/cstring.h>

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
    basic_string_init(pstr_string);
}

/**
 * Initialize string container specific c-string.
 */
void string_init_cstr(string_t* pstr_string, const char* s_cstr)
{
    basic_string_init_cstr(pstr_string, s_cstr);
}

/**
 * Initialize string container specific sub c-string.
 */
void string_init_subcstr(string_t* pstr_string, const char* s_cstr, size_t t_count)
{
    basic_string_init_subcstr(pstr_string, s_cstr, t_count);
}

/**
 * Initialize string with specified character.
 */
void string_init_char(string_t* pstr_string, size_t t_count, char c_char)
{
    basic_string_init_elem(pstr_string, t_count, c_char);
}

/**
 * Initialize string container with an exist string container.
 */
void string_init_copy(string_t* pstr_dest, const string_t* cpstr_src)
{
    basic_string_init_copy(pstr_dest, cpstr_src);
}

/**
 * Initialize string container with an exist sub string container.
 */
void string_init_copy_substring(string_t* pstr_dest, const string_t* cpstr_src, size_t t_pos, size_t t_len)
{
    basic_string_init_copy_substring(pstr_dest, cpstr_src, t_pos, t_len);
}


/**
 * Initialize string container with an exist string range.
 */
void string_init_copy_range(string_t* pstr_string, string_iterator_t it_begin, string_iterator_t it_end)
{
    basic_string_init_copy_range(pstr_string, it_begin, it_end);
}

/**
 * Destroy string container.
 */
void string_destroy(string_t* pstr_string)
{
    basic_string_destroy(pstr_string);
}

/**
 * Get character string.
 */
const char* string_c_str(const string_t* cpstr_string)
{
    return basic_string_c_str(cpstr_string);
}

/**
 * Get character string.
 */
const char* string_data(const string_t* cpstr_string)
{
    return basic_string_data(cpstr_string);
}

/**
 * Copy spceificed sub string to buffer.
 */
size_t string_copy(const string_t* cpstr_string, char* s_buffer, size_t t_len, size_t t_pos)
{
    return basic_string_copy(cpstr_string, s_buffer, t_len, t_pos);
}

/**
 * Get string character size.
 */
size_t string_size(const string_t* cpstr_string)
{
    return basic_string_size(cpstr_string);
}

/**
 * Get character string length.
 */
size_t string_length(const string_t* cpstr_string)
{
    return basic_string_length(cpstr_string);
}

/**
 * Return maximum character number.
 */
size_t string_max_size(const string_t* cpstr_string)
{
    return basic_string_max_size(cpstr_string);
}

/**
 * Get string capacity.
 */
size_t string_capacity(const string_t* cpstr_string)
{
    return basic_string_capacity(cpstr_string);
}

/**
 * Test string is empty.
 */
bool_t string_empty(const string_t* cpstr_string)
{
    return basic_string_empty(cpstr_string);
}

/**
 * Access string character using subscript.
 */
char* string_at(const string_t* cpstr_string, size_t t_pos)
{
    return (char*)basic_string_at(cpstr_string, t_pos);
}

/**
 * Test the two strings are equal.
 */
bool_t string_equal(const string_t* cpstr_first, const string_t* cpstr_second)
{
    return basic_string_equal(cpstr_first, cpstr_second);
}

/**
 * Test the two strings are unequal.
 */
bool_t string_not_equal(const string_t* cpstr_first, const string_t* cpstr_second)
{
    return basic_string_not_equal(cpstr_first, cpstr_second);
}

/**
 * Test the first string is less than the second string.
 */
bool_t string_less(const string_t* cpstr_first, const string_t* cpstr_second)
{
    return basic_string_less(cpstr_first, cpstr_second);
}

/**
 * Test the first string is less than or equal to the second string.
 */
bool_t string_less_equal(const string_t* cpstr_first, const string_t* cpstr_second)
{
    return basic_string_less_equal(cpstr_first, cpstr_second);
}

/**
 * Test the first string is greater than the second string.
 */
bool_t string_greater(const string_t* cpstr_first, const string_t* cpstr_second)
{
    return basic_string_greater(cpstr_first, cpstr_second);
}

/**
 * Test the first string is greater than or equal to the second string.
 */
bool_t string_greater_equal(const string_t* cpstr_first, const string_t* cpstr_second)
{
    return basic_string_greater_equal(cpstr_first, cpstr_second);
}

/**
 * Test the string is equal to the character string.
 */
bool_t string_equal_cstr(const string_t* cpstr_string, const char* s_cstr)
{
    return basic_string_equal_cstr(cpstr_string, s_cstr);
}

/**
 * Test the string is not equal to the character string.
 */
bool_t string_not_equal_cstr(const string_t* cpstr_string, const char* s_cstr)
{
    return basic_string_not_equal_cstr(cpstr_string, s_cstr);
}

/**
 * Test the string is less than the character string.
 */
bool_t string_less_cstr(const string_t* cpstr_string, const char* s_cstr)
{
    return basic_string_less_cstr(cpstr_string, s_cstr);
}

/**
 * Test the string is less than or equal to the character string.
 */
bool_t string_less_equal_cstr(const string_t* cpstr_string, const char* s_cstr)
{
    return basic_string_less_equal_cstr(cpstr_string, s_cstr);
}

/**
 * Test the string is greater than the character string.
 */
bool_t string_greater_cstr(const string_t* cpstr_string, const char* s_cstr)
{
    return basic_string_greater_cstr(cpstr_string, s_cstr);
}

/**
 * Test the string is greater than or equal to the character string.
 */
bool_t string_greater_equal_cstr(const string_t* cpstr_string, const char* s_cstr)
{
    return basic_string_greater_equal_cstr(cpstr_string, s_cstr);
}

/**
 * Compare two string.
 */
int string_compare(const string_t* cpstr_first, const string_t* cpstr_second)
{
    return basic_string_compare(cpstr_first, cpstr_second);
}

/**
 * Compare the first sub string and the second string.
 */
int string_compare_substring_string(
    const string_t* cpstr_first, size_t t_firstpos, size_t t_firstlen, const string_t* cpstr_second)
{
    return basic_string_compare_substring_string(cpstr_first, t_firstpos, t_firstlen, cpstr_second);
}

/**
 * Compare two sub strings.
 */
int string_compare_substring_substring(
    const string_t* cpstr_first, size_t t_firstpos, size_t t_firstlen,
    const string_t* cpstr_second, size_t t_secondpos, size_t t_secondlen)
{
    return basic_string_compare_substring_substring(
        cpstr_first, t_firstpos, t_firstlen, cpstr_second, t_secondpos, t_secondlen);
}

/**
 * Compare the string and the character string.
 */
int string_compare_cstr(const string_t* cpstr_string, const char* s_cstr)
{
    return basic_string_compare_cstr(cpstr_string, s_cstr);
}

/**
 * Compare the sub string and the character string.
 */
int string_compare_substring_cstr(
    const string_t* cpstr_string, size_t t_firstpos, size_t t_firstlen, const char* s_cstr)
{
    return basic_string_compare_substring_cstr(cpstr_string, t_firstpos, t_firstlen, s_cstr);
}

/**
 * Compare the sub string and the sub character string.
 */
int string_compare_substring_subcstr(
    const string_t* cpstr_string, size_t t_firstpos, size_t t_firstlen, const char* s_cstr, size_t t_len)
{
    return basic_string_compare_substring_subcstr(cpstr_string, t_firstpos, t_firstlen, s_cstr, t_len);
}


/**
 * Get specific sub string.
 */
string_t* string_substr(const string_t* cpstr_string, size_t t_pos, size_t t_len)
{
    return basic_string_substr(cpstr_string, t_pos, t_len);
}

/**
 * Connect string with other string.
 */
void string_connect(string_t* pstr_string, const string_t* cpstr_src)
{
    basic_string_connect(pstr_string, cpstr_src);
}

/**
 * Connect string with character string.
 */
void string_connect_cstr(string_t* pstr_string, const char* s_cstr)
{
    basic_string_connect_cstr(pstr_string, s_cstr);
}

/**
 * Appends specificed character to string.
 */
void string_connect_char(string_t* pstr_string, char c_char)
{
    basic_string_connect_elem(pstr_string, c_char);
}

/**
 * Find string in string.
 */
size_t string_find(const string_t* cpstr_string, const string_t* cpstr_find, size_t t_pos)
{
    return basic_string_find(cpstr_string, cpstr_find, t_pos);
}

/**
 * Find character string in string.
 */
size_t string_find_cstr(const string_t* cpstr_string, const char* s_cstr, size_t t_pos)
{
    return basic_string_find_cstr(cpstr_string, s_cstr, t_pos);
}

/**
 * Find sub character string in string.
 */
size_t string_find_subcstr(const string_t* cpstr_string, const char* s_cstr, size_t t_pos, size_t t_len)
{
    return basic_string_find_subcstr(cpstr_string, s_cstr, t_pos, t_len);
}

/**
 * Find a first occurrence of a elem
 */
size_t string_find_char(const string_t* cpstr_string, char c_char, size_t t_pos)
{
    return basic_string_find_elem(cpstr_string, c_char, t_pos);
}

/**
 * Find string in string in a backward direction.
 */
size_t string_rfind(const string_t* cpstr_string, const string_t* cpstr_find, size_t t_pos)
{
    return basic_string_rfind(cpstr_string, cpstr_find, t_pos);
}

/**
 * Find character string in string in a backward direction.
 */
size_t string_rfind_cstr(const string_t* cpstr_string, const char* s_cstr, size_t t_pos)
{
    return basic_string_rfind_cstr(cpstr_string, s_cstr, t_pos);
}

/**
 * Find sub character string in string in a backward direction.
 */
size_t string_rfind_subcstr(const string_t* cpstr_string, const char* s_cstr, size_t t_pos, size_t t_len)
{
    return basic_string_rfind_subcstr(cpstr_string, s_cstr, t_pos, t_len);
}

/**
 * Find a first occurrence of a character in a backward direction.
 */
size_t string_rfind_char(const string_t* cpstr_string, char c_char, size_t t_pos)
{
    return basic_string_rfind_elem(cpstr_string, c_char, t_pos);
}

/**
 * Find string for first character that matches any character of specific string.
 */
size_t string_find_first_of(const string_t* cpstr_string, const string_t* cpstr_find, size_t t_pos)
{
    return basic_string_find_first_of(cpstr_string, cpstr_find, t_pos);
}

/**
 * Find string for first character that matches any character of specific character string.
 */
size_t string_find_first_of_cstr(const string_t* cpstr_string, const char* s_cstr, size_t t_pos)
{
    return basic_string_find_first_of_cstr(cpstr_string, s_cstr, t_pos);
}

/**
 * Find string for first character that matches any character of specific sub character string.
 */
size_t string_find_first_of_subcstr(const string_t* cpstr_string, const char* s_cstr, size_t t_pos, size_t t_len)
{
    return basic_string_find_first_of_subcstr(cpstr_string, s_cstr, t_pos, t_len);
}

/**
 * Find string for first character that matches any character of specific character.
 */
size_t string_find_first_of_char(const string_t* cpstr_string, char c_char, size_t t_pos)
{
    return basic_string_find_first_of_elem(cpstr_string, c_char, t_pos);
}

/**
 * Find string for first character that is not matches any character of specific string.
 */
size_t string_find_first_not_of(const string_t* cpstr_string, const string_t* cpstr_find, size_t t_pos)
{
    return basic_string_find_first_not_of(cpstr_string, cpstr_find, t_pos);
}

/**
 * Find string for first character that is not matches any character of specific character string.
 */
size_t string_find_first_not_of_cstr(const string_t* cpstr_string, const char* s_cstr, size_t t_pos)
{
    return basic_string_find_first_not_of_cstr(cpstr_string, s_cstr, t_pos);
}

/**
 * Find string for first character that is not matches any character of specific sub character string.
 */
size_t string_find_first_not_of_subcstr(const string_t* cpstr_string, const char* s_cstr, size_t t_pos, size_t t_len)
{
    return basic_string_find_first_not_of_subcstr(cpstr_string, s_cstr, t_pos, t_len);
}

/**
 * Find string for first character that is not matches any character of specific character.
 */
size_t string_find_first_not_of_char(const string_t* cpstr_string, char c_char, size_t t_pos)
{
    return basic_string_find_first_not_of_elem(cpstr_string, c_char, t_pos);
}

/**
 * Find string for last character that matches any character of specific string.
 */
size_t string_find_last_of(const string_t* cpstr_string, const string_t* cpstr_find, size_t t_pos)
{
    return basic_string_find_last_of(cpstr_string, cpstr_find, t_pos);
}

/**
 * Find string for last character that matches any character of specific character string.
 */
size_t string_find_last_of_cstr(const string_t* cpstr_string, const char* s_cstr, size_t t_pos)
{
    return basic_string_find_last_of_cstr(cpstr_string, s_cstr, t_pos);
}

/**
 * Find string for last character that matches any character of specific sub character string.
 */
size_t string_find_last_of_subcstr(const string_t* cpstr_string, const char* s_cstr, size_t t_pos, size_t t_len)
{
    return basic_string_find_last_of_subcstr(cpstr_string, s_cstr, t_pos, t_len);
}

/**
 * Find string for last character that matches any character of specific character.
 */
size_t string_find_last_of_char(const string_t* cpstr_string, char c_char, size_t t_pos)
{
    return basic_string_find_last_of_elem(cpstr_string, c_char, t_pos);
}

/**
 * Find string for last character that is not matches any character of specific string.
 */
size_t string_find_last_not_of(const string_t* cpstr_string, const string_t* cpstr_find, size_t t_pos)
{
    return basic_string_find_last_not_of(cpstr_string, cpstr_find, t_pos);
}

/**
 * Find string for last character that is not matches any character of specific character string.
 */
size_t string_find_last_not_of_cstr(const string_t* cpstr_string, const char* s_cstr, size_t t_pos)
{
    return basic_string_find_last_not_of_cstr(cpstr_string, s_cstr, t_pos);
}

/**
 * Find string for last character that is not matches any character of specific sub character string.
 */
size_t string_find_last_not_of_subcstr(const string_t* cpstr_string, const char* s_cstr, size_t t_pos, size_t t_len)
{
    return basic_string_find_last_not_of_subcstr(cpstr_string, s_cstr, t_pos, t_len);
}

/**
 * Find string for last character that is not matches any character of specific character.
 */
size_t string_find_last_not_of_char(const string_t* cpstr_string, char c_char, size_t t_pos)
{
    return basic_string_find_last_not_of_elem(cpstr_string, c_char, t_pos);
}

/**
 * Return a iterator to the first element in the basic string container.
 */
string_iterator_t string_begin(const string_t* cpstr_string)
{
    return basic_string_begin(cpstr_string);
}

/**
 * Return a iterator that points just beyond the end of string container.
 */
string_iterator_t string_end(const string_t* cpstr_string)
{
    return basic_string_rbegin(cpstr_string);
}

/** private **/
string_reverse_iterator_t string_rbegin(const string_t* cpstr_string)
{
    return basic_string_rbegin(cpstr_string);
}
string_reverse_iterator_t string_rend(const string_t* cpstr_string)
{
    return basic_string_rend(cpstr_string);
}

/**
 * Erases the characters of string.
 */
void string_clear(string_t* pstr_string)
{
    basic_string_clear(pstr_string);
}

/**
 * Swap string datas.
 */
void string_swap(string_t* pstr_first, string_t* pstr_second)
{
    basic_string_swap(pstr_first, pstr_second);
}

/**
 * Set string capacity.
 */
void string_reserve(string_t* pstr_string, size_t t_reservesize)
{
    basic_string_reserve(pstr_string, t_reservesize);
}

/**
 * Reset the size of string characters.
 */
void string_resize(string_t* pstr_string, size_t t_resize)
{
    basic_string_resize(pstr_string, t_resize);
}

/**
 * Reset the size of string characters.
 */
void string_resize_char(string_t* pstr_string, size_t t_resize, char c_char)
{
    basic_string_resize_elem(pstr_string, t_resize, c_char);
}

/**
 * Adds an character to basic string.
 */
void string_push_back(string_t* pstr_string, char c_char)
{
    basic_string_push_back(pstr_string, c_char);
}

/**
 * Assign string character with an exist string container.
 */
void string_assign(string_t* pstr_dest, const string_t* cpstr_src)
{
    basic_string_assign(pstr_dest, cpstr_src);
}

/**
 * Assign string character with an exist sub string container.
 */
void string_assign_substring(string_t* pstr_dest, const string_t* cpstr_src, size_t t_pos, size_t t_len)
{
    basic_string_assign_substring(pstr_dest, cpstr_src, t_pos, t_len);
}

/**
 * Assign string character with an exist character string.
 */
void string_assign_cstr(string_t* pstr_string, const char* s_cstr)
{
    basic_string_assign_cstr(pstr_string, s_cstr);
}

/**
 * Assign string character with an exist sub character string.
 */
void string_assign_subcstr(string_t* pstr_string, const char* s_cstr, size_t t_len)
{
    basic_string_assign_subcstr(pstr_string, s_cstr, t_len);
}

/**
 * Assign string with specificed character.
 */
void string_assign_char(string_t* pstr_string, size_t t_count, char c_char)
{
    basic_string_assign_elem(pstr_string, t_count, c_char);
}

/**
 * Assign string character with an exist string container range.
 */
void string_assign_range(string_t* pstr_string, string_iterator_t it_begin, string_iterator_t it_end)
{
    basic_string_assign_range(pstr_string, it_begin, it_end);
}

/**
 * Append specific string to destination string.
 */
void string_append(string_t* pstr_dest, const string_t* cpstr_src)
{
    basic_string_append(pstr_dest, cpstr_src);
}

/**
 * Append specific sub string to destination string.
 */
void string_append_substring(string_t* pstr_dest, const string_t* cpstr_src, size_t t_pos, size_t t_len)
{
    basic_string_append_substring(pstr_dest, cpstr_src, t_pos, t_len);
}

/**
 * Append specific character string to destination string.
 */
void string_append_cstr(string_t* pstr_string, const char* s_cstr)
{
    basic_string_append_cstr(pstr_string, s_cstr);
}

/**
 * Append specific sub character string to destination string.
 */
void string_append_subcstr(string_t* pstr_string, const char* s_cstr, size_t t_len)
{
    basic_string_append_subcstr(pstr_string, s_cstr, t_len);
}

/**
 * Append specific character to destination string.
 */
void string_append_char(string_t* pstr_string, size_t t_count, char c_char)
{
    basic_string_append_elem(pstr_string, t_count, c_char);
}

/**
 * Append specific range to destination string.
 */
void string_append_range(string_t* pstr_string, string_iterator_t it_begin, string_iterator_t it_end)
{
    basic_string_append_range(pstr_string, it_begin, it_end);
}

/**
 * Insert one copy of character befor specificed position.
 */
string_iterator_t string_insert(string_t* pstr_string, string_iterator_t it_pos, char c_char)
{
    return basic_string_insert(pstr_string, it_pos, c_char);
}

/**
 * Insert multiple copys of character befor specificed position.
 */
string_iterator_t string_insert_n(string_t* pstr_string, string_iterator_t it_pos, size_t t_count, char c_char)
{
    return basic_string_insert_n(pstr_string, it_pos, t_count, c_char);
}

/**
 * Insert specific string into the destination string at specific position.
 */
void string_insert_string(string_t* pstr_string, size_t t_pos, const string_t* cpstr_insert)
{
    basic_string_insert_string(pstr_string, t_pos, cpstr_insert);
}

/**
 * Insert specific sub string into the destination string at specific position.
 */
void string_insert_substring(
    string_t* pstr_string, size_t t_pos, const string_t* cpstr_insert, size_t t_startpos, size_t t_len)
{
    basic_string_insert_substring(pstr_string, t_pos, cpstr_insert, t_startpos, t_len);
}

/**
 * Insert specific character string into the destination string at specific position.
 */
void string_insert_cstr(string_t* pstr_string, size_t t_pos, const char* s_cstr)
{
    basic_string_insert_cstr(pstr_string, t_pos, s_cstr);
}

/**
 * Insert specific sub character string into the destination string at specific position.
 */
void string_insert_subcstr(string_t* pstr_string, size_t t_pos, const char* s_cstr, size_t t_len)
{
    basic_string_insert_subcstr(pstr_string, t_pos, s_cstr, t_len);
}

/**
 * Insert multiple copys of character befor specificed position.
 */
void string_insert_char(string_t* pstr_string, size_t t_pos, size_t t_count, char c_char)
{
    basic_string_insert_elem(pstr_string, t_pos, t_count, c_char);
}

/**
 * Insert a range of characters into string at a specificed position.
 */
void string_insert_range(
    string_t* pstr_string, string_iterator_t it_pos, string_iterator_t it_begin, string_iterator_t it_end)
{
    basic_string_insert_range(pstr_string, it_pos, it_begin, it_end);
}

/**
 * Erase an element in a basic string from a specificed position.
 */
string_iterator_t string_erase(string_t* pstr_string, string_iterator_t it_pos)
{
    return basic_string_erase(pstr_string, it_pos);
}

/**
 * Erase a range of elements in a basic string from a specificed range.
 */
string_iterator_t string_erase_range(string_t* pstr_string, string_iterator_t it_begin, string_iterator_t it_end)
{
    return basic_string_erase_range(pstr_string, it_begin, it_end);
}

/**
 * Erase a sub basic string in a basic string from a specificed range.
 */
void string_erase_substring(string_t* pstr_string, size_t t_pos, size_t t_len)
{
    basic_string_erase_substring(pstr_string, t_pos, t_len);
}

/**
 * Replace characters in a string at a specificed position with specificed string.
 */
void string_replace(string_t* pstr_string, size_t t_pos, size_t t_len, const string_t* cpstr_replace)
{
    basic_string_replace(pstr_string, t_pos, t_len, cpstr_replace);
}

/**
 * Replace characters in a string at a specificed position with specificed sub string.
 */
void string_replace_substring(
    string_t* pstr_string, size_t t_pos, size_t t_len, const string_t* cpstr_replace, size_t t_position, size_t t_length)
{
    basic_string_replace_substring(pstr_string, t_pos, t_len, cpstr_replace, t_position, t_length);
}

/**
 * Replace characters in a string at a specificed position with specificed character string.
 */
void string_replace_cstr(string_t* pstr_string, size_t t_pos, size_t t_len, const char* s_cstr)
{
    basic_string_replace_cstr(pstr_string, t_pos, t_len, s_cstr);
}


/**
 * Replace characters in a string at a specificed position with specificed sub character string.
 */
void string_replace_subcstr(string_t* pstr_string, size_t t_pos, size_t t_len, const char* s_cstr, size_t t_length)
{
    basic_string_replace_subcstr(pstr_string, t_pos, t_len, s_cstr, t_length);
}

/**
 * Replace characters in a string at specificed posititon with specific characters.
 */
void string_replace_char(string_t* pstr_string, size_t t_pos, size_t t_len, size_t t_count, char c_char)
{
    basic_string_replace_elem(pstr_string, t_pos, t_len, t_count, c_char);
}

/**
 * Replace characters in a string at a specificed range with specificed string.
 */
void string_range_replace(
    string_t* pstr_string, string_iterator_t it_begin, string_iterator_t it_end, const string_t* cpstr_replace)
{
    basic_string_range_replace(pstr_string, it_begin, it_end, cpstr_replace);
}

/**
 * Replace characters in a string at a specificed range with specificed sub string.
 */
void string_range_replace_substring(
    string_t* pstr_string, string_iterator_t it_begin, string_iterator_t it_end,
    const string_t* cpstr_replace, size_t t_pos, size_t t_len)
{
    basic_string_range_replace_substring(pstr_string, it_begin, it_end, cpstr_replace, t_pos, t_len);
}

/**
 * Replace characters in a string at a specificed range with specificed character string.
 */
void string_range_replace_cstr(
    string_t* pstr_string, string_iterator_t it_begin, string_iterator_t it_end, const char* s_cstr)
{
    basic_string_range_replace_cstr(pstr_string, it_begin, it_end, s_cstr);
}

/**
 * Replace characters in a string at a specificed range with specificed sub character string.
 */
void string_range_replace_subcstr(
    string_t* pstr_string, string_iterator_t it_begin, string_iterator_t it_end, const char* s_cstr, size_t t_len)
{
    basic_string_range_replace_subcstr(pstr_string, it_begin, it_end, s_cstr, t_len);
}

/**
 * Replace characters in a string at specificed range with specific characters.
 */
void string_range_replace_char(
    string_t* pstr_string, string_iterator_t it_begin, string_iterator_t it_end, size_t t_count, char c_char)
{
    basic_string_range_replace_elem(pstr_string, it_begin, it_end, t_count, c_char);
}

/**
 * Replace characters in a string at a specificed range with specificed range.
 */
void string_replace_range(
    string_t* pstr_string, string_iterator_t it_begin, string_iterator_t it_end,
    string_iterator_t it_first, string_iterator_t it_last)
{
    basic_string_replace_range(pstr_string, it_begin, it_end, it_first, it_last);
}

/**
 * Output the character string to specific stream.
 */
void string_output(const string_t* cpstr_string, FILE* fp_stream)
{
    assert(cpstr_string != NULL);
    assert(fp_stream != NULL);

    fprintf(fp_stream, "%s", string_data(cpstr_string));
}

/**
 * Read the character string from specific stream.
 */
void string_input(string_t* pstr_string, FILE* fp_stream)
{
    int n_char = EOF;

    assert(pstr_string != NULL);
    assert(fp_stream != NULL);

    clearerr(fp_stream);
    string_clear(pstr_string);
    while (!feof(fp_stream) && !ferror(fp_stream) && string_size(pstr_string) < string_max_size(pstr_string)) {
        if ((n_char = fgetc(fp_stream)) != EOF) {
            string_push_back(pstr_string, (char)n_char);
        }
    }
}

/**
 * Get one line from specific stream.
 */
bool_t string_getline(string_t* pstr_string, FILE* fp_stream)
{
    int n_char = EOF;
#ifdef _WIN32
    int n_prevchar = EOF;
#endif

    assert(pstr_string != NULL);
    assert(fp_stream != NULL);

    clearerr(fp_stream);
    string_clear(pstr_string);
    while (!feof(fp_stream) && !ferror(fp_stream) && n_char != '\n' &&
           string_size(pstr_string) < string_max_size(pstr_string)) {
        n_char = fgetc(fp_stream);
        if (n_char != '\n' && n_char != EOF) {
#ifdef _WIN32
            /* new line is '\r\n' in Windows */
            if (n_prevchar != EOF) {
                assert(n_prevchar == '\r');
                string_push_back(pstr_string, (char)n_prevchar);
                n_prevchar = EOF;
            }
            if (n_char == '\r') {
                assert(n_prevchar == EOF);
                n_prevchar = n_char;
            } else {
                string_push_back(pstr_string, (char)n_char);
            }
#else
            string_push_back(pstr_string, (char)n_char);
#endif
        }
    }

#ifdef _WIN32
    if (feof(fp_stream)) {
        if (n_prevchar != EOF) {
            assert(n_prevchar == '\r');
            string_push_back(pstr_string, (char)n_prevchar);
            n_prevchar = EOF;
        }

        return false;
    }
#endif

    return (char)n_char == '\n' ? true : false;
}

/**
 * Get one line from specific stream with delimiter.
 */
bool_t string_getline_delimiter(string_t* pstr_string, FILE* fp_stream, char c_delimiter)
{
    int n_char = EOF;

    assert(pstr_string != NULL);
    assert(fp_stream != NULL);

    if (c_delimiter == '\n') {
        return string_getline(pstr_string, fp_stream);
    } else {
        clearerr(fp_stream);
        string_clear(pstr_string);
        while (!feof(fp_stream) && !ferror(fp_stream) && (char)n_char != c_delimiter &&
               string_size(pstr_string) < string_max_size(pstr_string)) {
            n_char = fgetc(fp_stream);
            if ((char)n_char != c_delimiter && n_char != EOF) {
                string_push_back(pstr_string, (char)n_char);
            }
        }

        return (char)n_char == c_delimiter ? true : false;
    }
}

/** local function implementation section **/

/** eof **/

