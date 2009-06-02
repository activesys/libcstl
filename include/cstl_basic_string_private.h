/*
 *  The private interface of basic_string.
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

#ifndef _CSTL_BASIC_STRING_PRIVATE_H
#define _CSTL_BASIC_STRING_PRIVATE_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
typedef struct _tagbasicstring
{
    vector_t _t_vector;
}basic_string_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * Create and initialization operation functions.
 */
extern basic_string_t* _create_basic_string(const char* s_typename);
extern void _basic_string_init_elem(basic_string_t* pt_basic_string, size_t t_count, ...);
extern void _basic_string_init_elem_varg(
    basic_string_t* pt_basic_string, size_t t_count, va_list val_elemlist);

/*
 * Find operation functions.
 */
extern size_t _basic_string_find_elem(
    const basic_string_t* cpt_basic_string, size_t t_pos, ...);
extern size_t _basic_string_find_elem_varg(
    const basic_string_t* cpt_basic_string, size_t t_pos, va_list val_elemlist);
extern size_t _basic_string_rfind_elem(
    const basic_string_t* cpt_basic_string, size_t t_pos, ...);
extern size_t _basic_string_rfind_elem_varg(
    const basic_string_t* cpt_basic_string, size_t t_pos, va_list val_elemlist);
extern size_t _basic_string_find_first_not_of_elem(
    const basic_string_t* cpt_basic_string, size_t t_pos, ...);
extern size_t _basic_string_find_first_not_of_elem_varg(
    const basic_string_t* cpt_basic_string, size_t t_pos, va_list val_elemlist);
extern size_t _basic_string_find_last_not_of_elem(
    const basic_string_t* cpt_basic_string, size_t t_pos, ...);
extern size_t _basic_string_find_last_not_of_elem_varg(
    const basic_string_t* cpt_basic_string, size_t t_pos, va_list val_elemlist);

/*
 * Connect operation functions.
 */
extern void _basic_string_connect_elem(basic_string_t* pt_basic_string, ...);
extern void _basic_string_connect_elem_varg(
    basic_string_t* pt_basic_string, va_list val_elemlist);

/*
 * Push back operation functions.
 */
extern void _basic_string_push_back(basic_string_t* pt_basic_string, ...);
extern void _basic_string_push_back_varg(
    basic_string_t* pt_basic_string, va_list val_elemlist);

/*
 * Resize operation functions.
 */
extern void _basic_string_resize(
    basic_string_t* pt_basic_string, size_t t_resize, ...);
extern void _basic_string_resize_varg(
    basic_string_t* pt_basic_string, size_t t_resize, va_list val_elemlist);

/*
 * Assign operator functions.
 */
extern void _basic_string_assign_elem(
    basic_string_t* pt_basic_string, size_t t_count, ...);
extern void _basic_string_assign_elem_varg(
    basic_string_t* pt_basic_string, size_t t_count, va_list val_elemlist);

/*
 * Append operation functions.
 */
extern void _basic_string_append_elem(
    basic_string_t* pt_basic_string, size_t t_count, ...);
extern void _basic_string_append_elem_varg(
    basic_string_t* pt_basic_string, size_t t_count, va_list val_elemlist);

/*
 * Insert operation functions.
 */
extern basic_string_iterator_t _basic_string_insert(
    basic_string_t* pt_basic_string, basic_string_iterator_t t_pos, ...);
extern basic_string_iterator_t _basic_string_insert_n(
    basic_string_t* pt_basic_string, basic_string_iterator_t t_pos, size_t t_count, ...);
extern basic_string_iterator_t _basic_string_insert_n_varg(
    basic_string_t* pt_basic_string, basic_string_iterator_t t_pos, 
    size_t t_count, va_list val_elemlist);
extern void _basic_string_insert_elem(
    basic_string_t* pt_basic_string, size_t t_pos, size_t t_count, ...);
extern void _basic_string_insert_elem_varg(
    basic_string_t* pt_basic_string, size_t t_pos, size_t t_count, va_list val_elemlist);

/*
 * Replace operation functions.
 */
extern void _basic_string_range_replace_elem(
    basic_string_t* pt_basic_string, basic_string_iterator_t t_begin,
    basic_string_iterator_t t_end, size_t t_count, ...);
extern void _basic_string_range_replace_elem_varg(
    basic_string_t* pt_basic_string, basic_string_iterator_t t_begin,
    basic_string_iterator_t t_end, size_t t_count, va_list val_elemlist);
extern void _basic_string_replace_elem(
    basic_string_t* pt_basic_string, size_t t_pos, size_t t_len, size_t t_count, ...);
extern void _basic_string_replace_elem_varg(
    basic_string_t* pt_basic_string, size_t t_pos,
    size_t t_len, size_t t_count, va_list val_elemlist);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_BASIC_STRING_PRIVATE_H */
/** eof **/

