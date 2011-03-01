/*
 *  The interface of basic_string.
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

#ifndef _CSTL_BASIC_STRING_H_
#define _CSTL_BASIC_STRING_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/**
 * Create basic_string container.
 * @param ...     element type name.
 * @return if create basic_string successfully, then return basic_string pointer, else return NULL.
 * @remarks type name should be C builtin type name, libcstl builtin typename or registed user defined type name,
 *          otherwise the function will return NULL.
 */
#define create_basic_string(...) _create_basic_string(#__VA_ARGS__)

/**
 * Initialize basic_string with specified element.
 * @param pt_basic_string   uninitialized basic_string container.
 * @param t_count           element number.
 * @param elem              specificed element.
 * @return void
 * @remarks if pt_basic_string == NULL, then the behavior is undefined. the type of specificed element and basic_string element
 *          type must be same, otherwise the behavior is undefined. the first specificed element is in use, others are
 *          not in use. basic_string container must be created by create_basic_string, otherwise the behavior is undefined.
 */
#define basic_string_init_elem(pt_basic_string, t_count, elem)\
    _basic_string_init_elem((pt_basic_string), (t_count), (elem))

/**
 * Appends specificed element to basic string.
 * @param pt_basic_string      basic_string container.
 * @param elem                 specificed element.
 * @return void.
 * @remarks if pt_basic_string == NULL or uninitialized, then the bahavior is undefine.
 */
#define basic_string_connect_elem(pt_basic_string, elem) _basic_string_connect_elem((pt_basic_string), (elem))

/**
 * Find a first occurrence of a elem
 * @param cpt_basic_string     basic_string container.
 * @param elem                 specificed element.
 * @param t_pos                search begin position.
 * @return the index of first character of the substring when successful, otherwise NPOS.
 * @remarks if cpt_basic_string == NULL or uninitialized, the behavior is undefined. if t_pos is invalid position, then return
 *          NPOS.
 */
#define basic_string_find_elem(cpt_basic_string, elem, t_pos) _basic_string_find_elem((cpt_basic_string), (t_pos), (elem))

/**
 * Find a first occurrence of a elem in a backward direction.
 * @param cpt_basic_string     basic_string container.
 * @param elem                 specificed element.
 * @param t_pos                search begin position.
 * @return the index of first character of the substring when successful, otherwise NPOS.
 * @remarks if cpt_basic_string == NULL or uninitialized, the behavior is undefined. if t_pos >= the length of basic string,
 *          then finding begin with the last element.
 */
#define basic_string_rfind_elem(cpt_basic_string, elem, t_pos) _basic_string_rfind_elem((cpt_basic_string), (t_pos), (elem))

/**
 * Find basic_string for first element that matches any element of specific element.
 * @param cpt_basic_string     basic_string container.
 * @param elem                 specificed element.
 * @param t_pos                search begin position.
 * @return the index of first character of the substring when successful, otherwise NPOS.
 * @remarks if cpt_basic_string == NULL or uninitialized, the behavior is undefined. if t_pos is invalid position, then return
 *          NPOS.
 */
#define basic_string_find_first_of_elem(cpt_basic_string, elem, t_pos)\
    _basic_string_find_elem((cpt_basic_string), (t_pos), (elem))

/**
 * Find basic_string for first element that is not matches any element of specific element.
 * @param cpt_basic_string     basic_string container.
 * @param elem                 specificed element.
 * @param t_pos                search begin position.
 * @return the index of first character of the substring when successful, otherwise NPOS.
 * @remarks if cpt_basic_string == NULL or uninitialized, the behavior is undefined. if t_pos is invalid position, then return
 *          NPOS.
 */
#define basic_string_find_first_not_of_elem(cpt_basic_string, elem, t_pos)\
    _basic_string_find_first_not_of_elem((cpt_basic_string), (t_pos), (elem))

/**
 * Find basic_string for last element that matches any element of specific element.
 * @param cpt_basic_string     basic_string container.
 * @param elem                 specificed element.
 * @param t_pos                search begin position.
 * @return the index of first character of the substring when successful, otherwise NPOS.
 * @remarks if cpt_basic_string == NULL or uninitialized, the behavior is undefined. if t_pos >= the length of basic string,
 *          then finding begin with the last element.
 */
#define basic_string_find_last_of_elem(cpt_basic_string, elem, t_pos)\
    _basic_string_rfind_elem((cpt_basic_string), (t_pos), (elem))

/**
 * Find basic_string for last element that is not matches any element of specific element.
 * @param cpt_basic_string     basic_string container.
 * @param elem                 specificed element.
 * @param t_pos                search begin position.
 * @return the index of first character of the substring when successful, otherwise NPOS.
 * @remarks if cpt_basic_string == NULL or uninitialized, the behavior is undefined. if t_pos >= the length of basic string,
 *          then finding begin with the last element.
 */
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
/**
 * Initialize empty basic_string container.
 * @param pt_basic_string    basic_string container.
 * @return void.
 * @remarks if pt_basic_string == NULL, then the behavior is undefined. pt_basic_string muse be created by
 *          create_basic_string(), otherwise the behavior is undefined. the size of basic_string and the capacity of
 *          basic_string is 0 after initialization.
 */
extern void basic_string_init(basic_string_t* pt_basic_string);

/**
 * Initialize basic_string container specific value string.
 * @param pt_basic_string    basic_string container.
 * @param cpv_value_string   value string.
 * @return void.
 * @remarks if pt_basic_string == NULL or cpv_value_string == NULL, then the behavior is undefined. pt_basic_string muse be
 *          created by create_basic_string(), otherwise the behavior is undefined. the value string is terminated by memory 0,
 *          and basic_string_size() is equal to the length of value string.
 */
extern void basic_string_init_cstr(basic_string_t* pt_basic_string, const void* cpv_value_string);

/**
 * Initialize basic_string container specific sub value string.
 * @param pt_basic_string    basic_string container.
 * @param cpv_value_string   value string.
 * @param t_len              length of sub value string.
 * @return void.
 * @remarks if pt_basic_string == NULL or cpv_value_string == NULL, then the behavior is undefined. pt_basic_string muse be
 *          created by create_basic_string(), otherwise the behavior is undefined. if t_len is NPOS or greater then the
 *          length of value string, then use total value string to initialize basic_string.
 */
extern void basic_string_init_subcstr(basic_string_t* pt_basic_string, const void* cpv_value_string, size_t t_len);

/**
 * Initialize basic_string container with an exist basic_string container.
 * @param pt_dest     destination basic_string container.
 * @param cpt_src     source basic_string container.
 * @return void.
 * @remarks if pt_dest == NULL or cpt_src == NULL, then the behavior is undefined. pt_dest must be created by
 *          create_basic_string() and cpt_src must be initialized, otherwise the behavior is undefined. after initialization
 *          the size of pt_dest is equal to the size of cpt_src, and the capacity of pt_dest is satisfied capacity
 *          assignment algorithm.
 */
extern void basic_string_init_copy(basic_string_t* pt_dest, const basic_string_t* cpt_src);

/**
 * Initialize basic_string container with an exist sub basic_string container.
 * @param pt_dest     destination basic_string container.
 * @param cpt_src     source basic_string container.
 * @param t_pos       start position of source basic_string.
 * @param t_len       sub basic_string length.
 * @return void.
 * @remarks if pt_dest == NULL or cpt_src == NULL, then the behavior is undefined. pt_dest must be created by
 *          create_basic_string() and cpt_src must be initialized, otherwise the behavior is undefined. t_pos must be
 *          valid source basic_string position, otherwise the behavior is undefined. if t_len == NPOS or t_pos + t_len >=
 *          the length of source basic_string, then use all remain sub basic_string from t_pos.
 */
extern void basic_string_init_copy_substring(
    basic_string_t* pt_dest, const basic_string_t* cpt_src, size_t t_pos, size_t t_len);

/**
 * Initialize basic_string container with an exist basic_string range.
 * @param pt_basic_string     destination basic_string container.
 * @param it_begin            the begin iterator of range.
 * @param it_end              the end iterator of range.
 * @return void.
 * @remarks if pt_basic_string == NULL, then the behavior is undefined. pt_basic_string must be created by
 *          create_basic_string(), otherwise the behavior is undefined. after initialization the size of pt_basic_string
 *          is equal to the size of range, and the capacity of pt_basic_string is satisfied capacity assignment algorithm.
 */
extern void basic_string_init_copy_range(
    basic_string_t* pt_basic_string, basic_string_iterator_t it_begin, basic_string_iterator_t it_end);

/**
 * Destroy basic_string container.
 * @param pt_basic_string   basic_string container.
 * @return void.
 * @remarks if pt_basic_string == NULL, then the behavior is undefined. the pt_basic_string must be initialized or created by
 *          create_basic_string(), otherwise the behavior is undefined.
 */
extern void basic_string_destroy(basic_string_t* pt_basic_string);

/**
 * Get data string.
 * @param cpt_basic_string    basic_string container.
 * @return data string.
 * @remarks if cpt_basic_string == NULL or uninitialized, the behavior is undefined. if basic_string is empty, return NULL.
 */
extern const void* basic_string_c_str(const basic_string_t* cpt_basic_string);

/**
 * Get data string.
 * @param cpt_basic_string    basic_string container.
 * @return data string.
 * @remarks if cpt_basic_string == NULL or uninitialized, the behavior is undefined. if basic_string is empty, then the
 *          behavior is undefined.
 */
extern const void* basic_string_data(const basic_string_t* cpt_basic_string);

/**
 * Copy spceificed sub basic_string to buffer.
 * @param cpt_basic_string    basic_string container.
 * @param pv_buffer           buffer.
 * @param t_len               length of sub basic_string.
 * @param t_pos               copy position.
 * @return copy size.
 * @remarks if cpt_basic_string == NULL or uninitialized, the behavior is undefined. if pv_buffer == NULL, the behavior is
 *          undefined. t_pos must be valid position for basic_string, otherwise the behavior is undefined. the copy size is
 *          min(t_len, basic_string_size() - t_pos).
 */
extern size_t basic_string_copy(const basic_string_t* cpt_basic_string, void* pv_buffer, size_t t_len, size_t t_pos);

/**
 * Get basic_string element size.
 * @param cpt_basic_string   basic_string container.
 * @return basic_string element size.
 * @remarks if cpt_basic_string == NULL, then the behavior is undefined. cpt_basic_string must be initialized, otherwise the
 *          behavior is undefined.
 */
extern size_t basic_string_size(const basic_string_t* cpt_basic_string);

/**
 * Get data string length.
 * @param cpt_basic_string   basic_string container.
 * @return basic_string data string length.
 * @remarks if cpt_basic_string == NULL, then the behavior is undefined. cpt_basic_string must be initialized, otherwise the
 *          behavior is undefined. this function is same as basic_string_size().
 */
extern size_t basic_string_length(const basic_string_t* cpt_basic_string);

/**
 * Test basic_string is empty.
 * @param cpt_basic_string   basic_string container.
 * @return true if empty, otherwise return false.
 * @remarks if cpt_basic_string == NULL, then the behavior is undefined. cpt_basic_string must be initialized, otherwise the
 *          behavior is undefined.
 */
extern bool_t basic_string_empty(const basic_string_t* cpt_basic_string);

/**
 * Return maximum element number.
 * @param cpt_basic_string   basic_string container.
 * @return maximum number.
 * @remarks if cpt_basic_string == NULL, then the behavior is undefined. cpt_basic_string must be initialized, otherwise the
 *          behavior is undefined. this number is not fixed number.
 */
extern size_t basic_string_max_size(const basic_string_t* cpt_basic_string);

/**
 * Get basic_string capacity.
 * @param cpvec_basic_string   basic_string container.
 * @return basic_string capacity.
 * @remarks if cpt_basic_string == NULL, then the behavior is undefined. cpt_basic_string must be initialized, otherwise the
 *          behavior is undefined.
 */
extern size_t basic_string_capacity(const basic_string_t* cpt_basic_string);

/**
 * Access basic_string data using subscript.
 * @param cpt_basic_string    basic_string container.
 * @param t_pos               subscript.
 * @return pointer to the data.
 * @remarks if cpt_basic_string == NULL, then the behavior is undefined. the basic_string must be initialized, otherwise the
 *          behavior is undefined. if t_pos >= basic_string_size(cpt_basic_string), then the behavior is undefined.
 */
extern void* basic_string_at(const basic_string_t* cpt_basic_string, size_t t_pos);

/**
 * Test the two basic_strings are equal.
 * @param cpt_first   first basic_string container.
 * @param cpt_second  second basic_string container.
 * @return if first basic_string equal to second basic_string, then return true, else return false.
 * @remarks if cpt_first == NULL or cpt_second == NULL, then the behavior is undefined. the two basic_strings must be
 *          initialized, otherwise the behavior is undefined. if the two basic_strings are not same type, then return false.
 *          if cpt_first == cpt_second, then return true.
 */
extern bool_t basic_string_equal(const basic_string_t* cpt_first, const basic_string_t* cpt_second);

/**
 * Test the two basic_strings are unequal.
 * @param cpt_first   first basic_string container.
 * @param cpt_second  second basic_string container.
 * @return if first basic_string unequal to second basic_string, then return true, else return false.
 * @remarks if cpt_first == NULL or cpt_second == NULL, then the behavior is undefined. the two basic_strings must be
 *          initialized, otherwise the behavior is undefined. if the two basic_strings are not same type, then return true.
 *          if cpt_first == cpt_second, then return false.
 */
extern bool_t basic_string_not_equal(const basic_string_t* cpt_first, const basic_string_t* cpt_second);

/**
 * Test the first basic_string is less than the second basic_string.
 * @param cpt_first   first basic_string container.
 * @param cpt_second  second basic_string container.
 * @return if the first basic_string is less than the second basic_string, then return true, else return false.
 * @remarks if cpt_first == NULL or cpt_second == NULL, then the behavior is undefined. the two basic_strings must be
 *          initialized, otherwise the behavior is undefined. if the two basic_strings are not same type, the behavior is
 *          undefined. if cpt_first == cpt_second, then return false.
 */
extern bool_t basic_string_less(const basic_string_t* cpt_first, const basic_string_t* cpt_second);

/**
 * Test the first basic_string is less than or equal to the second basic_string.
 * @param cpt_first   first basic_string container.
 * @param cpt_second  second basic_string container.
 * @return if the first basic_string is less than or equal to the second basic_string, then return true, else return false.
 * @remarks if cpt_first == NULL or cpt_second == NULL, then the behavior is undefined. the two basic_strings must be
 *          initialized, otherwise the behavior is undefined. if the two basic_strings are not same type, the behavior is
 *          undefined. if cpt_first == cpt_second, then return true.
 */
extern bool_t basic_string_less_equal(const basic_string_t* cpt_first, const basic_string_t* cpt_second);

/**
 * Test the first basic_string is greater than the second basic_string.
 * @param cpt_first   first basic_string container.
 * @param cpt_second  second basic_string container.
 * @return if the first basic_string is greater than the second basic_string, then return true, else return false.
 * @remarks if cpt_first == NULL or cpt_second == NULL, then the behavior is undefined. the two basic_strings must be
 *          initialized, otherwise the behavior is undefined. if the two basic_strings are not same type, the behavior is
 *          undefined. if cpt_first == cpt_second, then return false.
 */
extern bool_t basic_string_greater(const basic_string_t* cpt_first, const basic_string_t* cpt_second);

/**
 * Test the first basic_string is greater than or equal to the second basic_string.
 * @param cpt_first   first basic_string container.
 * @param cpt_second  second basic_string container.
 * @return if the first basic_string is greater than or equal to the second basic_string, then return true, else return false.
 * @remarks if cpt_first == NULL or cpt_second == NULL, then the behavior is undefined. the two basic_strings must be
 *          initialized, otherwise the behavior is undefined. if the two basic_strings are not same type, the behavior is
 *          undefined. if cpt_first == cpt_second, then return true.
 */
extern bool_t basic_string_greater_equal(const basic_string_t* cpt_first, const basic_string_t* cpt_second);

/**
 * Test the basic_string is equal to the value string.
 * @param cpt_basic_string   basic_string container.
 * @param cpv_value_string   value string.
 * @return if the basic_string is equal to the value string, then return true, else return false.
 * @remarks if cpt_basic_string == NULL or cpv_value_string == NULL, then the behavior is undefined. the basic_string must be
 *          initialized, otherwise the behavior is undefined. if the basic_string type and value string type are not same
 *          type, the behavior is undefined.
 */
extern bool_t basic_string_equal_cstr(const basic_string_t* cpt_basic_string, const void* cpv_value_string);

/**
 * Test the basic_string is not equal to the value string.
 * @param cpt_basic_string   basic_string container.
 * @param cpv_value_string   value string.
 * @return if the basic_string is not equal to the value string, then return true, else return false.
 * @remarks if cpt_basic_string == NULL or cpv_value_string == NULL, then the behavior is undefined. the basic_string must be
 *          initialized, otherwise the behavior is undefined. if the basic_string type and value string type are not same
 *          type, the behavior is undefined.
 */
extern bool_t basic_string_not_equal_cstr(const basic_string_t* cpt_basic_string, const void* cpv_value_string); 

/**
 * Test the basic_string is less than the value string.
 * @param cpt_basic_string   basic_string container.
 * @param cpv_value_string   value string.
 * @return if the basic_string is less than the value string, then return true, else return false.
 * @remarks if cpt_basic_string == NULL or cpv_value_string == NULL, then the behavior is undefined. the basic_string must be
 *          initialized, otherwise the behavior is undefined. if the basic_string type and value string are not same type,
 *          the behavior is undefined.
 */
extern bool_t basic_string_less_cstr(const basic_string_t* cpt_basic_string, const void* cpv_value_string); 

/**
 * Test the basic_string is less than or equal to the value string.
 * @param cpt_basic_string   basic_string container.
 * @param cpv_value_string   value string.
 * @return if the basic_string is less than or equal to the value string, then return true, else return false.
 * @remarks if cpt_basic_string == NULL or cpv_value_string == NULL, then the behavior is undefined. the basic_string must be
 *          initialized, otherwise the behavior is undefined. if the basic_string type and value string are not same type,
 *          the behavior is undefined.
 */
extern bool_t basic_string_less_equal_cstr(const basic_string_t* cpt_basic_string, const void* cpv_value_string); 

/**
 * Test the basic_string is greater than the value string.
 * @param cpt_basic_string   basic_string container.
 * @param cpv_value_string   value string.
 * @return if the basic_string is greater than the value string, then return true, else return false.
 * @remarks if cpt_basic_string == NULL or cpv_value_string == NULL, then the behavior is undefined. the basic_string must be
 *          initialized, otherwise the behavior is undefined. if the basic_string type and value string are not same type,
 *          the behavior is undefined.
 */
extern bool_t basic_string_greater_cstr(const basic_string_t* cpt_basic_string, const void* cpv_value_string); 

/**
 * Test the basic_string is greater than or equal to the value string.
 * @param cpt_basic_string   basic_string container.
 * @param cpv_value_string   value string.
 * @return if the basic_string is greater than or equal to the value string, then return true, else return false.
 * @remarks if cpt_basic_string == NULL or cpv_value_string == NULL, then the behavior is undefined. the basic_string must be
 *          initialized, otherwise the behavior is undefined. if the basic_string type and value string are not same type,
 *          the behavior is undefined.
 */
extern bool_t basic_string_greater_equal_cstr(const basic_string_t* cpt_basic_string, const void* cpv_value_string); 

/**
 * Compare two basic_string.
 * @param cpt_first   first basic_string container.
 * @param cpt_second  second basic_string container.
 * @return if the first basic_string is greater than the second basic_string, then return value > 0, else if the first
 *         basic_string is less than the second basic_string, then return value < 0, else return value == 0.
 * @remarks if cpt_first == NULL or cpt_second == NULL, then the behavior is undefined. the two basic_strings must be
 *          initialized, otherwise the behavior is undefined. if the two basic_strings are not same type, the behavior is
 *          undefined. if cpt_first == cpt_second, then return 0.
 */
extern int basic_string_compare(const basic_string_t* cpt_first, const basic_string_t* cpt_second);

/**
 * Compare the first sub basic_string and the second basic_string.
 * @param cpt_first   first basic_string container.
 * @param t_pos       substring begin position.
 * @param t_len       substring length.
 * @param cpt_second  second basic_string container.
 * @return if the first sub basic_string is greater than the second basic_string, then return value > 0, else if the first
 *         sub basic_string is less than the second basic_string, then return value < 0, else return value == 0.
 * @remarks if cpt_first == NULL or cpt_second == NULL, then the behavior is undefined. the two basic_strings must be
 *          initialized, otherwise the behavior is undefined. if the two basic_strings are not same type, the behavior is
 *          undefined. t_pos must be valid position for the first basic_string container, otherwise the behavior is undefined.
 *          if t_len >= basic_string_size(cpt_first) - t_pos, then all remain sub string is in use.
 */
extern int basic_string_compare_substring_string(
    const basic_string_t* cpt_first, size_t t_pos, size_t t_len, const basic_string_t* cpt_second);

/**
 * Compare two sub basic_strings.
 * @param cpt_first   first basic_string container.
 * @param t_firstpos  first substring begin position.
 * @param t_firstlen  first substring length.
 * @param cpt_second  second basic_string container.
 * @param t_secondpos second substring begin position.
 * @param t_secondlen second substring length.
 * @return if the first sub basic_string is greater than the second sub basic_string, then return value > 0, else if the first
 *         sub basic_string is less than the second sub basic_string, then return value < 0, else return value == 0.
 * @remarks if cpt_first == NULL or cpt_second == NULL, then the behavior is undefined. the two basic_strings must be
 *          initialized, otherwise the behavior is undefined. if the two basic_strings are not same type, the behavior is
 *          undefined. t_firstpos must be valid position for the first basic_string container and the t_secondpos must be
 *          valie position for the second basic_string container, otherwise the behavior is undefined. if t_firstlen >= 
 *          basic_string_size(cpt_first) - t_firstpos, then all first remain sub string is in use, if t_secondlen >=
 *          basic_string_size(cpt_second) = t_secondpos, then all second remain sub string is in use.
 */
extern int basic_string_compare_substring_substring(
    const basic_string_t* cpt_first, size_t t_firstpos, size_t t_firstlen, 
    const basic_string_t* cpt_second, size_t t_secondpos, size_t t_secondlen);

/**
 * Compare the basic_string and the value string.
 * @param cpt_basic_string   basic_string container.
 * @param cpv_value_string   value string.
 * @return if the basic_string is greater than the value string, then return value > 0, else if the basic_string is less than
 *         the value string, then return value < 0, else return value == 0.
 * @remarks if cpt_basic_string == NULL or cpv_value_string == NULL, then the behavior is undefined. the basic_string must be
 *          initialized, otherwise the behavior is undefined. if the basic_string type and value string type are not same
 *          type, the behavior is undefined.
 */
extern int basic_string_compare_cstr(const basic_string_t* cpt_basic_string, const void* cpv_value_string);

/**
 * Compare the sub basic_string and the value string.
 * @param cpt_basic_string   basic_string container.
 * @param t_pos              substring begin position.
 * @param t_len              substring length.
 * @param cpv_value_string   value string.
 * @return if the sub basic_string is greater than the value string, then return value > 0, else if the sub basic_string is
 *         less than the value string, then return value < 0, else return value == 0.
 * @remarks if cpt_basic_string == NULL or cpv_value_string == NULL, then the behavior is undefined. the basic_string must be
 *          initialized, otherwise the behavior is undefined. if the basic_string type and value string type are not same
 *          type, the behavior is undefined. t_pos must be valid position for the first basic_string container, otherwise the
 *          behavior is undefined. if t_len >= basic_string_size(cpt_first) - t_pos, then all remain sub string is in use.
 */
extern int basic_string_compare_substring_cstr(
    const basic_string_t* cpt_basic_string, size_t t_pos, size_t t_len, const void* cpv_value_string);

/**
 * Compare the sub basic_string and the sub value string.
 * @param cpt_basic_string   basic_string container.
 * @param t_pos              substring begin position.
 * @param t_len              substring length.
 * @param cpv_value_string   value string.
 * @param t_valuelen         sub value string length.
 * @return if the sub basic_string is greater than the sub value string, then return value > 0, else if the sub basic_string is
 *         less than the sub value string, then return value < 0, else return value == 0.
 * @remarks if cpt_basic_string == NULL or cpv_value_string == NULL, then the behavior is undefined. the basic_string must be
 *          initialized, otherwise the behavior is undefined. if the basic_string type and value string type are not same
 *          type, the behavior is undefined. t_pos must be valid position for the first basic_string container, otherwise the
 *          behavior is undefined. if t_len >= basic_string_size(cpt_first) - t_pos, then all remain sub string is in use.
 *          if t_valuelen >= the length of cpv_value_string, then all value string is in use.
 */
extern int basic_string_compare_substring_subcstr(
    const basic_string_t* cpt_basic_string, size_t t_pos, size_t t_len, const void* cpv_value_string, size_t t_valuelen);

/**
 * Get specific sub string.
 * @param cpt_basic_string   basic_string container.
 * @param t_pos              substring begin position.
 * @param t_len              substring length.
 * @return sub basic_string.
 * @remarks if cpt_basic_string == NULL, then the behavior is undefined. the basic_string must be initialized, otherwise
 *          the behavior is undefined. t_pos must be valid position for the first basic_string container, otherwise the
 *          behavior is undefined. if t_len >= basic_string_size(cpt_first) - t_pos, then all remain sub string is in use.
 *          the returned sub basic_string is initialized, user must be destroy this sub basic_string after using.
 *
 */
extern basic_string_t* basic_string_substr(const basic_string_t* cpt_basic_string, size_t t_pos, size_t t_len);

/**
 * Connect basic string with other basic string.
 * @param pt_dest          destination basic_string.
 * @param cpt_src          source basic_string.
 * @return void.
 * @remarks if pt_dest == NULL or cpt_src == NULL, then the behavior is undefined. pt_dest and cpt_src must be initialized,
 *          otherwise the behavior is undefined. the element type of two basic string must be same, otherwise the behavior
 *          is undefine.
 */
extern void basic_string_connect(basic_string_t* pt_dest, const basic_string_t* cpt_src);

/**
 * Connect basic string with value string.
 * @param pt_basic_string          destination basic_string.
 * @param cpt_value_string         source value string.
 * @return void.
 * @remarks if pt_basic_string == NULL or cpt_value_string == NULL, then the behavior is undefined. pt_basic_string must be
 *          initialized, otherwise the behavior is undefined. the element type of basic string and value string must be same,
 *          otherwise the behavior is undefined.
 */
extern void basic_string_connect_cstr(basic_string_t* pt_basic_string, const void* cpv_value_string);

/**
 * Find basic_string in basic_string.
 * @param cpt_basic_string         basic_string.
 * @param cpt_find                 search basic_string.
 * @param t_pos                    search position.
 * @return index of search basic_string if search successfull, else return NPOS.
 * @remarks if cpt_basic_string == NULL or cpt_find == NULL, then the behavior is undefined. cpt_basic_string and cpt_find
 *          must be initialized, otherwise the behavior is undefined. the element type of two basic_string must be same,
 *          otherwise the behavior is undefined. t_pos is valid position for cpt_basic_string, otherwise the behavior is
 *          undefined. if cpt_find is empty, then return t_pos;
 */
extern size_t basic_string_find(const basic_string_t* cpt_basic_string, const basic_string_t* cpt_find, size_t t_pos);

/**
 * Find value string in basic_string.
 * @param cpt_basic_string         basic_string.
 * @param cpv_value_string         value string.
 * @param t_pos                    search position.
 * @return index of search basic_string if search successfull, else return NPOS.
 * @remarks if cpt_basic_string == NULL or cpv_value_string == NULL, then the behavior is undefined. cpt_basic_string 
 *          must be initialized, otherwise the behavior is undefined. the element type of basic_string and cpv_value_string
 *          must be same, otherwise the behavior is undefined. t_pos is valid position for cpt_basic_string, otherwise the
 *          behavior is undefined. if cpv_value_string is empty, then return t_pos.
 */
extern size_t basic_string_find_cstr(const basic_string_t* cpt_basic_string, const void* cpv_value_string, size_t t_pos);

/**
 * Find sub value string in basic_string.
 * @param cpt_basic_string         basic_string.
 * @param cpv_value_string         value string.
 * @param t_pos                    search position.
 * @param t_len                    sub value string length.
 * @return index of search basic_string if search successfull, else return NPOS.
 * @remarks if cpt_basic_string == NULL or cpv_value_string == NULL, then the behavior is undefined. cpt_basic_string 
 *          must be initialized, otherwise the behavior is undefined. the element type of basic_string and cpv_value_string
 *          must be same, otherwise the behavior is undefined. t_pos is valid position for cpt_basic_string, otherwise the
 *          behavior is undefined. if cpv_value_string is empty or t_len == 0, then return t_pos. if t_len is greater then
 *          the length of value string, then use all value string.
 */
extern size_t basic_string_find_subcstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string, size_t t_pos, size_t t_len);

/**
 * Find basic_string in basic_string in a backward direction.
 * @param cpt_basic_string         basic_string.
 * @param cpt_find                 search basic_string.
 * @param t_pos                    search position.
 * @return index of search basic_string if search successfull, else return NPOS.
 * @remarks if cpt_basic_string == NULL or cpt_find == NULL, then the behavior is undefined. cpt_basic_string and cpt_find
 *          must be initialized, otherwise the behavior is undefined. the element type of two basic_string must be same,
 *          otherwise the behavior is undefined. if t_pos >= basic_string_size(cpt_basic_string), then search from the last
 *          element. if cpt_find is empty, then return t_pos;
 */
extern size_t basic_string_rfind(const basic_string_t* cpt_basic_string, const basic_string_t* cpt_find, size_t t_pos);

/**
 * Find value string in basic_string in a backward direction.
 * @param cpt_basic_string         basic_string.
 * @param cpv_value_string         search value string.
 * @param t_pos                    search position.
 * @return index of search basic_string if search successfull, else return NPOS.
 * @remarks if cpt_basic_string == NULL or cpv_value_string == NULL, then the behavior is undefined. cpt_basic_string 
 *          must be initialized, otherwise the behavior is undefined. the element type of basic_string and cpv_value_string 
 *          must be same, otherwise the behavior is undefined. if t_pos >= basic_string_size(cpt_basic_string), then search
 *          from the last element. if cpv_value_string is empty, then return t_pos;
 */
extern size_t basic_string_rfind_cstr(const basic_string_t* cpt_basic_string, const void* cpv_value_string, size_t t_pos);

/**
 * Find sub value string in basic_string in a backward direction.
 * @param cpt_basic_string         basic_string.
 * @param cpv_value_string         search value string.
 * @param t_pos                    search position.
 * @param t_len                    sub value string length.
 * @return index of search basic_string if search successfull, else return NPOS.
 * @remarks if cpt_basic_string == NULL or cpv_value_string == NULL, then the behavior is undefined. cpt_basic_string 
 *          must be initialized, otherwise the behavior is undefined. the element type of basic_string and cpv_value_string 
 *          must be same, otherwise the behavior is undefined. if t_pos >= basic_string_size(cpt_basic_string), then search
 *          from the last element. if cpv_value_string is empty or t_len == 0, then return t_pos; if t_len is greater than
 *          the length of value string, then use all value string.
 */
extern size_t basic_string_rfind_subcstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string, size_t t_pos, size_t t_len);

/**
 * Find basic_string for first element that matches any element of specific string.
 * @param cpt_basic_string         basic_string.
 * @param cpt_find                 search basic_string.
 * @param t_pos                    search position.
 * @return index of element if search successfull, else return NPOS.
 * @remarks if cpt_basic_string == NULL or cpt_find == NULL, then the behavior is undefined. cpt_basic_string and cpt_find
 *          must be initialized, otherwise the behavior is undefined. the element type of two basic_string must be same,
 *          otherwise the behavior is undefined. t_pos is valid position for cpt_basic_string, otherwise the behavior is
 *          undefined. if cpt_find is empty, then return t_pos.
 */
extern size_t basic_string_find_first_of(
    const basic_string_t* cpt_basic_string, const basic_string_t* cpt_find, size_t t_pos);

/**
 * Find basic_string for first element that matches any element of specific value string.
 * @param cpt_basic_string         basic_string.
 * @param cpv_value_string         search value string.
 * @param t_pos                    search position.
 * @return index of element if search successfull, else return NPOS.
 * @remarks if cpt_basic_string == NULL or cpv_value_string == NULL, then the behavior is undefined. cpt_basic_string
 *          must be initialized, otherwise the behavior is undefined. the element type of basic_string and cpv_value_string
 *          must be same, otherwise the behavior is undefined. t_pos is valid position for cpt_basic_string, otherwise the
 *          behavior is undefined. if cpv_value_string is empty, then return t_pos.
 */
extern size_t basic_string_find_first_of_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string, size_t t_pos);

/**
 * Find basic_string for first element that matches any element of specific sub value string.
 * @param cpt_basic_string         basic_string.
 * @param cpv_value_string         search value string.
 * @param t_pos                    search position.
 * @param t_len                    sub value string length.
 * @return index of element if search successfull, else return NPOS.
 * @remarks if cpt_basic_string == NULL or cpv_value_string == NULL, then the behavior is undefined. cpt_basic_string
 *          must be initialized, otherwise the behavior is undefined. the element type of basic_string and cpv_value_string
 *          must be same, otherwise the behavior is undefined. t_pos is valid position for cpt_basic_string, otherwise the
 *          behavior is undefined. if cpv_value_string is empty or t_len == 0, then return t_pos. if t_len is greater than
 *          the length of value string, then use all value string.
 */
extern size_t basic_string_find_first_of_subcstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string, size_t t_pos, size_t t_len);

/**
 * Find basic_string for first element that is not matches any element of specific string.
 * @param cpt_basic_string         basic_string.
 * @param cpt_find                 search basic_string.
 * @param t_pos                    search position.
 * @return index of element if search successfull, else return NPOS.
 * @remarks if cpt_basic_string == NULL or cpt_find == NULL, then the behavior is undefined. cpt_basic_string and cpt_find
 *          must be initialized, otherwise the behavior is undefined. the element type of two basic_string must be same,
 *          otherwise the behavior is undefined. t_pos is valid position for cpt_basic_string, otherwise the behavior is
 *          undefined. if cpt_find is empty, then return t_pos.
 */
extern size_t basic_string_find_first_not_of(
    const basic_string_t* cpt_basic_string, const basic_string_t* cpt_find, size_t t_pos);

/**
 * Find basic_string for first element that is not matches any element of specific value string.
 * @param cpt_basic_string         basic_string.
 * @param cpv_value_string         search value string.
 * @param t_pos                    search position.
 * @return index of element if search successfull, else return NPOS.
 * @remarks if cpt_basic_string == NULL or cpv_value_string == NULL, then the behavior is undefined. cpt_basic_string
 *          must be initialized, otherwise the behavior is undefined. the element type of basic_string and cpv_value_string
 *          must be same, otherwise the behavior is undefined. t_pos is valid position for cpt_basic_string, otherwise the
 *          behavior is undefined. if cpv_value_string is empty, then return t_pos.
 */
extern size_t basic_string_find_first_not_of_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string, size_t t_pos);

/**
 * Find basic_string for first element that is not matches any element of specific sub value string.
 * @param cpt_basic_string         basic_string.
 * @param cpv_value_string         search value string.
 * @param t_pos                    search position.
 * @param t_len                    sub value string length.
 * @return index of element if search successfull, else return NPOS.
 * @remarks if cpt_basic_string == NULL or cpv_value_string == NULL, then the behavior is undefined. cpt_basic_string
 *          must be initialized, otherwise the behavior is undefined. the element type of basic_string and cpv_value_string
 *          must be same, otherwise the behavior is undefined. t_pos is valid position for cpt_basic_string, otherwise the
 *          behavior is undefined. if cpv_value_string is empty or t_len == 0, then return t_pos. if t_len is greater than
 *          the length of value string, then use all value string.
 */
extern size_t basic_string_find_first_not_of_subcstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string, size_t t_pos, size_t t_len);

/**
 * Find basic_string for last element that matches any element of specific string.
 * @param cpt_basic_string         basic_string.
 * @param cpt_find                 search basic_string.
 * @param t_pos                    search position.
 * @return index of element if search successfull, else return NPOS.
 * @remarks if cpt_basic_string == NULL or cpt_find == NULL, then the behavior is undefined. cpt_basic_string and cpt_find
 *          must be initialized, otherwise the behavior is undefined. the element type of two basic_string must be same,
 *          otherwise the behavior is undefined. if t_pos >= basic_string_size(cpt_basic_string), then search from the last
 *          element. if cpt_find is empty, then return t_pos;
 */
extern size_t basic_string_find_last_of(
    const basic_string_t* cpt_basic_string, const basic_string_t* cpt_find, size_t t_pos);

/**
 * Find basic_string for last element that matches any element of specific value string.
 * @param cpt_basic_string         basic_string.
 * @param cpv_value_string         search value string.
 * @param t_pos                    search position.
 * @return index of element if search successfull, else return NPOS.
 * @remarks if cpt_basic_string == NULL or cpv_value_string == NULL, then the behavior is undefined. cpt_basic_string 
 *          must be initialized, otherwise the behavior is undefined. the element type of basic_string and cpv_value_string 
 *          must be same, otherwise the behavior is undefined. if t_pos >= basic_string_size(cpt_basic_string), then search
 *          from the last element. if cpv_value_string is empty, then return t_pos;
 */
extern size_t basic_string_find_last_of_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string, size_t t_pos);

/**
 * Find basic_string for last element that matches any element of specific sub value string.
 * @param cpt_basic_string         basic_string.
 * @param cpv_value_string         search value string.
 * @param t_pos                    search position.
 * @param t_len                    sub value string length.
 * @return index of element if search successfull, else return NPOS.
 * @remarks if cpt_basic_string == NULL or cpv_value_string == NULL, then the behavior is undefined. cpt_basic_string 
 *          must be initialized, otherwise the behavior is undefined. the element type of basic_string and cpv_value_string 
 *          must be same, otherwise the behavior is undefined. if t_pos >= basic_string_size(cpt_basic_string), then search
 *          from the last element. if cpv_value_string is empty or t_len == 0, then return t_pos; if t_len is greater than
 *          the length of value string, then use all value string.
 */
extern size_t basic_string_find_last_of_subcstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string, size_t t_pos, size_t t_len);

/**
 * Find basic_string for last element that is not matches any element of specific string.
 * @param cpt_basic_string         basic_string.
 * @param cpt_find                 search basic_string.
 * @param t_pos                    search position.
 * @return index of element if search successfull, else return NPOS.
 * @remarks if cpt_basic_string == NULL or cpt_find == NULL, then the behavior is undefined. cpt_basic_string and cpt_find
 *          must be initialized, otherwise the behavior is undefined. the element type of two basic_string must be same,
 *          otherwise the behavior is undefined. if t_pos >= basic_string_size(cpt_basic_string), then search from the last
 *          element. if cpt_find is empty, then return t_pos;
 */
extern size_t basic_string_find_last_not_of(
    const basic_string_t* cpt_basic_string, const basic_string_t* cpt_find, size_t t_pos);

/**
 * Find basic_string for last element that is not matches any element of specific value string.
 * @param cpt_basic_string         basic_string.
 * @param cpv_value_string         search value string.
 * @param t_pos                    search position.
 * @return index of element if search successfull, else return NPOS.
 * @remarks if cpt_basic_string == NULL or cpv_value_string == NULL, then the behavior is undefined. cpt_basic_string 
 *          must be initialized, otherwise the behavior is undefined. the element type of basic_string and cpv_value_string 
 *          must be same, otherwise the behavior is undefined. if t_pos >= basic_string_size(cpt_basic_string), then search
 *          from the last element. if cpv_value_string is empty, then return t_pos;
 */
extern size_t basic_string_find_last_not_of_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string, size_t t_pos);

/**
 * Find basic_string for last element that is not matches any element of specific sub value string.
 * @param cpt_basic_string         basic_string.
 * @param cpv_value_string         search value string.
 * @param t_pos                    search position.
 * @param t_len                    sub value string length.
 * @return index of element if search successfull, else return NPOS.
 * @remarks if cpt_basic_string == NULL or cpv_value_string == NULL, then the behavior is undefined. cpt_basic_string 
 *          must be initialized, otherwise the behavior is undefined. the element type of basic_string and cpv_value_string 
 *          must be same, otherwise the behavior is undefined. if t_pos >= basic_string_size(cpt_basic_string), then search
 *          from the last element. if cpv_value_string is empty or t_len == 0, then return t_pos; if t_len is greater than
 *          the length of value string, then use all value string.
 */
extern size_t basic_string_find_last_not_of_subcstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string, size_t t_pos, size_t t_len);

/**
 * Return a iterator to the first element in the basic string container.
 * @param cpt_basic_string         basic_string container.
 * @return a iterator to the first element in the basic string container.
 * @remarks if cpt_basic_string == NULL, then the behavior is undefined. the basic_string must be initialized, otherwise the
 *          behavior is undefined. if the basic_string is empty, then return basic_string_end(cpt_basic_string).
 */
extern basic_string_iterator_t basic_string_begin(const basic_string_t* cpt_basic_string);

/**
 * Return a iterator that points just beyond the end of basic_string container.
 * @param cpt_basic_string         basic_string container.
 * @return a iterator to the end of basic_string.
 * @remarks if cpt_basic_string == NULL, then the behavior is undefined. the basic_string must be initialized, otherwise the
 *          behavior is undefined.
 */
extern basic_string_iterator_t basic_string_end(const basic_string_t* cpt_basic_string);
/* private */
extern basic_string_reverse_iterator_t basic_string_rbegin(const basic_string_t* cpt_basic_string);
extern basic_string_reverse_iterator_t basic_string_rend(const basic_string_t* cpt_basic_string);

/**
 * Erases the elements of basic_string.
 * @param pvec_vector   basic_string container.
 * @return void.
 * @remarks if cpvec_vector == NULL, then the behavior is undefined. the basic_string must be initialized, otherwise the
 *          behavior is undefined.
 */
extern void basic_string_clear(basic_string_t* pt_basic_string);

/**
 * Swap basic_string datas.
 * @param pt_first    first basic_string.
 * @param pt_second   second basic_string.
 * @return void.
 * @remarks if pt_first == NULL or pt_second == NULL, then the behavior is undefined. the two basic_strings must be
 *          initialized, otherwise the behavior is undefined. the element type of two basic_strings must be the same,
 *          otherwise the behavior is undefined. if basic_string_equal(pt_first, pt_second) == true, then this function
 *          does nothing.
 */
extern void basic_string_swap(basic_string_t* pt_first, basic_string_t* pt_second);

/**
 * Set basic_string capacity.
 * @param pt_basic_string       basic_string container.
 * @param t_reservesize  new capacity.
 * @return void.
 * @remarks if pt_basic_string == NULL, then the behavior is undefined. pt_basic_string must be initialized, otherwise the
 *          behavior is undefined. if t_reservesize > basic_string_capacity(), then t_reservesize is new capacity, otherwise
 *          capacity is not change.
 */
extern void basic_string_reserve(basic_string_t* pt_basic_string, size_t t_reservesize);

/**
 * Assign basic_string element with an exist basic_string container.
 * @param pt_dest     destination basic_string container.
 * @param cpt_src     source basic_string container.
 * @return void.
 * @remarks if pt_dest == NULL or cpt_src == NULL, then the behavior is undefined. pt_dest and cpt_src must be initialized,
 *          otherwise the behavior is undefined. the element type of two basic_strings must be same, otherwise the behavior
 *          is undefined. if the destination basic_string equal to source basic_string, then this function does nothing.
 */
extern void basic_string_assign(basic_string_t* pt_dest,  const basic_string_t* cpt_src);

/**
 * Assign basic_string element with an exist sub basic_string container.
 * @param pt_dest     destination basic_string container.
 * @param cpt_src     source basic_string container.
 * @param t_pos       start position of source basic_string.
 * @param t_len       sub basic_string length.
 * @return void.
 * @remarks if pt_dest == NULL or cpt_src == NULL, then the behavior is undefined. pt_dest and cpt_src must be initialized,
 *          otherwise the behavior is undefined. the element type of two basic_strings must be same, otherwise the behavior
 *          is undefined. if the destination basic_string equal to source basic_string, then this function does nothing. if
 *          t_len == NPOS or t_pos + t_len >= basic_string_size(cpt_src), then use all remain source basic string.
 */
extern void basic_string_assign_substring(basic_string_t* pt_dest, const basic_string_t* cpt_src, size_t t_pos, size_t t_len);

/**
 * Assign basic_string element with an exist value string.
 * @param pt_basic_string    basic_string container.
 * @param cpv_value_string   value string.
 * @return void.
 * @remarks if pt_basic_string == NULL or cpv_value_string == NULL, then the behavior is undefined. pt_basic_string muse be
 *          initialized, otherwise the behavior is undefined. the element type of basic_string and value string must be same,
 *          otherwise the behavior is undefined.
 */
extern void basic_string_assign_cstr(basic_string_t* pt_basic_string, const void* cpv_value_string);

/**
 * Assign basic_string element with an exist sub value string.
 * @param pt_basic_string    basic_string container.
 * @param cpv_value_string   value string.
 * @param t_len              length of sub value string.
 * @return void.
 * @remarks if pt_basic_string == NULL or cpv_value_string == NULL, then the behavior is undefined. pt_basic_string muse be
 *          initialized, otherwise the behavior is undefined. the element type of basic_string and value string must be same,
 *          otherwise the behavior is undefined. if t_len is equal to or greater than the length of value string, then use
 *          all value string.
 */
extern void basic_string_assign_subcstr(basic_string_t* pt_basic_string, const void* cpv_value_string, size_t t_len);

/**
 * Assign basic_string element with an exist basic_string container range.
 * @param pt_basic_string     destination basic_string container.
 * @param it_begin            range begin.
 * @param it_end              range end.
 * @return void.
 * @remarks if pt_basic_string == NULL, then the behavior is undefined. pt_basic_string must be initialized, otherwise the
 *          behavior is undefined. the element type of basic_string and [it_begin, it_end) must be same, otherwise the
 *          behavior is undefined. if [it_begin, it_end) belong to the destination basic_string, the behavior is undefined.
 */
extern void basic_string_assign_range(
    basic_string_t* pt_basic_string, basic_string_iterator_t it_begin, basic_string_iterator_t it_end);

/*
 * Append operation functions.
 */
extern void basic_string_append(
    basic_string_t* pt_basic_string, const basic_string_t* cpt_basic_string_append);
extern void basic_string_append_substring(
    basic_string_t* pt_basic_string,
    const basic_string_t* cpt_basic_string_append, size_t t_pos, size_t t_len);
extern void basic_string_append_cstr(
    basic_string_t* pt_basic_string, const void* cpv_value_string);
extern void basic_string_append_subcstr(
    basic_string_t* pt_basic_string, const void* cpv_value_string, size_t t_len);
extern void basic_string_append_range(
    basic_string_t* pt_basic_string,
    basic_string_iterator_t t_begin, basic_string_iterator_t t_end);

/*
 * Insert operation functions.
 */
extern void basic_string_insert_string(
    basic_string_t* pt_basic_string, size_t t_pos,
    const basic_string_t* cpt_basic_string_insert);
extern void basic_string_insert_substring(
    basic_string_t* pt_basic_string, size_t t_pos,
    const basic_string_t* cpt_basic_string_insert, size_t t_startpos, size_t t_len);
extern void basic_string_insert_cstr(
    basic_string_t* pt_basic_string, size_t t_pos, const void* cpv_value_string);
extern void basic_string_insert_subcstr(
    basic_string_t* pt_basic_string, size_t t_pos,
    const void* cpv_value_string, size_t t_len);
extern void basic_string_insert_range(
    basic_string_t* pt_basic_string, basic_string_iterator_t t_pos,
    basic_string_iterator_t t_begin, basic_string_iterator_t t_end);

/*
 * Erase operation functions.
 */
extern basic_string_iterator_t basic_string_erase(
    basic_string_t* pt_basic_string, basic_string_iterator_t t_pos);
extern basic_string_iterator_t basic_string_erase_range(
    basic_string_t* pt_basic_string,
    basic_string_iterator_t t_begin, basic_string_iterator_t t_end);
extern void basic_string_erase_substring(
    basic_string_t* pt_basic_string, size_t t_pos, size_t t_len);

/*
 * Replace operation functions.
 */
extern void basic_string_replace(
    basic_string_t* pt_basic_string, size_t t_pos, size_t t_len,
    const basic_string_t* cpt_basic_string_replace);
extern void basic_string_replace_substring(
    basic_string_t* pt_basic_string, size_t t_pos, size_t t_len,
    const basic_string_t* cpt_basic_string_replace, size_t t_position, size_t t_length);
extern void basic_string_replace_cstr(
    basic_string_t* pt_basic_string, size_t t_pos, size_t t_len,
    const void* cpv_value_string);
extern void basic_string_replace_subcstr(
    basic_string_t* pt_basic_string, size_t t_pos, size_t t_len,
    const void* cpv_value_string, size_t t_length);
extern void basic_string_range_replace(
    basic_string_t* pt_basic_string, basic_string_iterator_t t_begin,
    basic_string_iterator_t t_end, const basic_string_t* cpt_basic_string_replace);
extern void basic_string_range_replace_substring(
    basic_string_t* pt_basic_string,
    basic_string_iterator_t t_begin, basic_string_iterator_t t_end,
    const basic_string_t* cpt_basic_string_replace, size_t t_pos, size_t t_len);
extern void basic_string_range_replace_cstr(
    basic_string_t* pt_basic_string, basic_string_iterator_t t_begin,
    basic_string_iterator_t t_end, const void* cpv_value_string);
extern void basic_string_range_replace_subcstr(
    basic_string_t* pt_basic_string, basic_string_iterator_t t_begin,
    basic_string_iterator_t t_end, const void* cpv_value_string, size_t t_len);
extern void basic_string_replace_range(
    basic_string_t* pt_basic_string,
    basic_string_iterator_t t_begin, basic_string_iterator_t t_end,
    basic_string_iterator_t t_first, basic_string_iterator_t t_last);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_BASIC_STRING_H_ */
/** eof **/

