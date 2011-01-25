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
/**
 * Initialize empty basic_string container.
 * @param pt_basic_string    basic_string container.
 * @return void.
 * @remarks if pt_basic_string == NULL, then the behavior is undefined. pt_basic_string muse be created by create_basic_string(),
 *          otherwise the behavior is undefined. the size of basic_string and the capacity of basic_string is 0 after
 *          initialization.
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
 *          created by create_basic_string(), otherwise the behavior is undefined. if t_len is NPOS or greater then the length of
 *          value string, then use total value string to initialize basic_string.
 */
extern void basic_string_init_subcstr(basic_string_t* pt_basic_string, const void* cpv_value_string, size_t t_len);
extern void basic_string_init_copy(
    basic_string_t* pt_basic_string, const basic_string_t* cpt_basic_string_src);
extern void basic_string_init_copy_substring(
    basic_string_t* pt_basic_string, const basic_string_t* cpt_basic_string_src,
    size_t t_pos, size_t t_len);
extern void basic_string_init_copy_range(
    basic_string_t* pt_basic_string,
    basic_string_iterator_t t_begin, basic_string_iterator_t t_end);
extern void basic_string_destroy(basic_string_t* pt_basic_string);

/*
 * Get element string.
 */
extern const void* basic_string_c_str(const basic_string_t* cpt_basic_string);
extern const void* basic_string_data(const basic_string_t* cpt_basic_string);
extern size_t basic_string_copy(
    const basic_string_t* cpt_basic_string, void* pv_buffer,
    size_t t_copysize, size_t t_copypos);

/*
 * basic_string_t size operation functions.
 */
extern size_t basic_string_size(const basic_string_t* cpt_basic_string);
extern size_t basic_string_length(const basic_string_t* cpt_basic_string);
extern bool_t basic_string_empty(const basic_string_t* cpt_basic_string);
extern size_t basic_string_max_size(const basic_string_t* cpt_basic_string);
extern size_t basic_string_capacity(const basic_string_t* cpt_basic_string);

/*
 * Element random access.
 */
extern void* basic_string_at(const basic_string_t* cpt_basic_string, size_t t_pos);

/*
 * Relationship operator functions.
 */
extern bool_t basic_string_equal(
    const basic_string_t* cpt_basic_stringfirst, 
    const basic_string_t* cpt_basic_stringsecond);
extern bool_t basic_string_not_equal(
    const basic_string_t* cpt_basic_stringfirst, 
    const basic_string_t* cpt_basic_stringsecond);
extern bool_t basic_string_less(
    const basic_string_t* cpt_basic_stringfirst, 
    const basic_string_t* cpt_basic_stringsecond);
extern bool_t basic_string_greater(
    const basic_string_t* cpt_basic_stringfirst, 
    const basic_string_t* cpt_basic_stringsecond);
extern bool_t basic_string_less_equal(
    const basic_string_t* cpt_basic_stringfirst, 
    const basic_string_t* cpt_basic_stringsecond);
extern bool_t basic_string_greater_equal(
    const basic_string_t* cpt_basic_stringfirst, 
    const basic_string_t* cpt_basic_stringsecond);
extern bool_t basic_string_equal_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string);
extern bool_t basic_string_not_equal_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string); 
extern bool_t basic_string_less_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string); 
extern bool_t basic_string_greater_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string); 
extern bool_t basic_string_less_equal_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string); 
extern bool_t basic_string_greater_equal_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string); 

/*
 * Compare operation functions.
 */
extern int basic_string_compare(
    const basic_string_t* cpt_basic_stringfirst,
    const basic_string_t* cpt_basic_stringsecond);
extern int basic_string_compare_substring_string(
    const basic_string_t* cpt_basic_stringfirst, size_t t_firstpos, size_t t_firstlen,
    const basic_string_t* cpt_basic_stringsecond);
extern int basic_string_compare_substring_substring(
    const basic_string_t* cpt_basic_stringfirst, size_t t_firstpos, size_t t_firstlen,
    const basic_string_t* cpt_basic_stringsecond, size_t t_secondpos, size_t t_secondlen);
extern int basic_string_compare_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string);
extern int basic_string_compare_substring_cstr(
    const basic_string_t* cpt_basic_string, size_t t_stringpos, size_t t_stringlen,
    const void* cpv_value_string);
extern int basic_string_compare_substring_subcstr(
    const basic_string_t* cpt_basic_string, size_t t_stringpos, size_t t_stringlen,
    const void* cpv_value_string, size_t t_valuestringlen);

/*
 * Substring operation function.
 */
extern basic_string_t* basic_string_substr(
    const basic_string_t* cpt_basic_string, size_t t_pos, size_t t_len);

/*
 * Connect operation functions.
 */
extern void basic_string_connect(
    basic_string_t* pt_basic_string, const basic_string_t* cpt_basic_string_src);
extern void basic_string_connect_cstr(
    basic_string_t* pt_basic_string, const void* cpv_value_string);

/*
 * Find operation functions.
 */
/* find */
extern size_t basic_string_find(
    const basic_string_t* cpt_basic_string, const basic_string_t* cpt_basic_string_find,
    size_t t_pos);
extern size_t basic_string_find_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string, size_t t_pos);
extern size_t basic_string_find_subcstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string,
    size_t t_pos, size_t t_len);
/* rfind */
extern size_t basic_string_rfind(
    const basic_string_t* cpt_basic_string, const basic_string_t* cpt_basic_string_find,
    size_t t_pos);
extern size_t basic_string_rfind_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string, size_t t_pos);
extern size_t basic_string_rfind_subcstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string,
    size_t t_pos, size_t t_len);
/* find first of */
extern size_t basic_string_find_first_of(
    const basic_string_t* cpt_basic_string, const basic_string_t* cpt_basic_string_find,
    size_t t_pos);
extern size_t basic_string_find_first_of_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string, size_t t_pos);
extern size_t basic_string_find_first_of_subcstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string,
    size_t t_pos, size_t t_len);
/* find first not of */
extern size_t basic_string_find_first_not_of(
    const basic_string_t* cpt_basic_string, const basic_string_t* cpt_basic_string_find,
    size_t t_pos);
extern size_t basic_string_find_first_not_of_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string, size_t t_pos);
extern size_t basic_string_find_first_not_of_subcstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string,
    size_t t_pos, size_t t_len);
/* find last of */
extern size_t basic_string_find_last_of(
    const basic_string_t* cpt_basic_string, const basic_string_t* cpt_basic_string_find,
    size_t t_pos);
extern size_t basic_string_find_last_of_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string, size_t t_pos);
extern size_t basic_string_find_last_of_subcstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string,
    size_t t_pos, size_t t_len);
/* find last not of */
extern size_t basic_string_find_last_not_of(
    const basic_string_t* cpt_basic_string, const basic_string_t* cpt_basic_string_find,
    size_t t_pos);
extern size_t basic_string_find_last_not_of_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string, size_t t_pos);
extern size_t basic_string_find_last_not_of_subcstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string,
    size_t t_pos, size_t t_len);

/*
 * Iterator support.
 */
extern basic_string_iterator_t basic_string_begin(const basic_string_t* cpt_basic_string);
extern basic_string_iterator_t basic_string_end(const basic_string_t* cpt_basic_string);
/* private */
extern basic_string_reverse_iterator_t basic_string_rbegin(
    const basic_string_t* cpt_basic_string);
extern basic_string_reverse_iterator_t basic_string_rend(
    const basic_string_t* cpt_basic_string);

/*
 * Erase all elements in basic_string.
 */
extern void basic_string_clear(basic_string_t* pt_basic_string);

/*
 * Swap the contents of two basic_strings.
 */
extern void basic_string_swap(
    basic_string_t* pt_basic_stringfirst, basic_string_t* pt_basic_stringsecond);

/*
 * Reserve the capacity of basic_string.
 */
extern void basic_string_reserve(
    basic_string_t* pt_basic_string, size_t t_reservesize);

/*
 * Assign operator functions.
 */
extern void basic_string_assign(
    basic_string_t* pt_basic_string,  const basic_string_t* cpt_basic_string_assign);
extern void basic_string_assign_substring(
    basic_string_t* pt_basic_string,
    const basic_string_t* cpt_basic_string_assign, size_t t_pos, size_t t_len);
extern void basic_string_assign_cstr(
    basic_string_t* pt_basic_string, const void* cpv_value_string);
extern void basic_string_assign_subcstr(
    basic_string_t* pt_basic_string, const void* cpv_value_string, size_t t_len);
extern void basic_string_assign_range(
    basic_string_t* pt_basic_string,
    basic_string_iterator_t t_begin, basic_string_iterator_t t_end);

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

