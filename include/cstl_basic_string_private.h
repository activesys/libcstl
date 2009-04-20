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
 *  Author Email: activesys.wb@gmail.com
 *                activesys@sina.com.cn
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
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _create_basic_string
 *        Parameters: in) t_typesize: size_t
 *                          the element type size.
 *                    in) s_typename: const char*
 *                          the element type name.
 *           Returns: basic_string_t
 *                          new basic_string.
 *       Description: create the new basic_string.
 *
 * ----------------------------------------------------------------------------
 */
extern basic_string_t _create_basic_string(
    size_t t_typesize, const char* s_typename);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _basic_string_find_elem
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *                          the basic_string.
 *                    in) t_pos: size_t
 *                          the start position.
 *                    in) ...
 *                          the find element.
 *           Returns: size_t
 *                          start position
 *       Description: search for element beginning at position t_pos.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t _basic_string_find_elem(
    const basic_string_t* cpt_basic_string, size_t t_pos, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _basic_string_find_elem_varg
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *                          the basic_string.
 *                    in) t_pos: size_t
 *                          the start position.
 *                    in) val_elemlist: va_list
 *                          the find element.
 *           Returns: size_t
 *                          start position
 *       Description: search for element beginning at position t_pos.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t _basic_string_find_elem_varg(
    const basic_string_t* cpt_basic_string, size_t t_pos, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _basic_string_rfind_elem
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *                          the basic_string.
 *                    in) t_pos: size_t
 *                          the start position.
 *                    in) ...
 *                          the find element.
 *           Returns: size_t
 *                          start position
 *       Description: search backword for element beginning at position t_pos.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t _basic_string_rfind_elem(
    const basic_string_t* cpt_basic_string,
    size_t t_pos,
    ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _basic_string_rfind_elem_varg
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *                          the basic_string.
 *                    in) t_pos: size_t
 *                          the start position.
 *                    in) val_elemlist: va_list
 *                          the find element.
 *           Returns: size_t
 *                          start position
 *       Description: search backword for element beginning at position t_pos.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t _basic_string_rfind_elem_varg(
    const basic_string_t* cpt_basic_string,
    size_t t_pos,
    va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _basic_string_find_first_not_of_elem
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *                          the basic_string.
 *                    in) t_pos: size_t
 *                          the start position.
 *                    in) ...
 *                          the find element.
 *           Returns: size_t
 *                          start position
 *       Description: search for element beginning at position t_pos.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t _basic_string_find_first_not_of_elem(
    const basic_string_t* cpt_basic_string,
    size_t t_pos,
    ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _basic_string_find_first_not_of_elem_varg
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *                          the basic_string.
 *                    in) t_pos: size_t
 *                          the start position.
 *                    in) val_elemlist: va_list
 *                          the find element.
 *           Returns: size_t
 *                          start position
 *       Description: search for element beginning at position t_pos.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t _basic_string_find_first_not_of_elem_varg(
    const basic_string_t* cpt_basic_string,
    size_t t_pos,
    va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _basic_string_find_last_not_of_elem
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *                          the basic_string.
 *                    in) t_pos: size_t
 *                          the start position.
 *                    in) ...
 *                          the find element.
 *           Returns: size_t
 *                          start position
 *       Description: search backword for element beginning at position t_pos.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t _basic_string_find_last_not_of_elem(
    const basic_string_t* cpt_basic_string,
    size_t t_pos,
    ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _basic_string_find_last_not_of_elem_varg
 *        Parameters: in) cpt_basic_string: const basic_string_t*
 *                          the basic_string.
 *                    in) t_pos: size_t
 *                          the start position.
 *                    in) val_elemlist: va_list
 *                          the find element.
 *           Returns: size_t
 *                          start position
 *       Description: search backword for element beginning at position t_pos.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t _basic_string_find_last_not_of_elem_varg(
    const basic_string_t* cpt_basic_string,
    size_t t_pos,
    va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _basic_string_init_elem
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                    in) t_count: size_t
 *                          the initialize count.
 *                    in) ...
 *                          value.
 *           Returns: void
 *       Description: initialize the basic_string with value.
 *
 * ----------------------------------------------------------------------------
 */
extern void _basic_string_init_elem(
    basic_string_t* pt_basic_string, size_t t_count, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _basic_string_init_elem_varg
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                    in) t_count: size_t
 *                          the initialize count.
 *                    in) val_elemlist: va_list
 *                          value list.
 *           Returns: void
 *       Description: initialize the basic_string with value.
 *
 * ----------------------------------------------------------------------------
 */
extern void _basic_string_init_elem_varg(
    basic_string_t* pt_basic_string, size_t t_count, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _basic_string_connect_elem
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the basic_string.
 *                    in) ...
 *                          the value
 *           Returns: void
 *       Description: string concatenation.
 *
 * ----------------------------------------------------------------------------
 */
extern void _basic_string_connect_elem(basic_string_t* pt_basic_string, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _basic_string_connect_elem_varg
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the basic_string.
 *                    in) val_elemlist: va_list
 *                          the value
 *           Returns: void
 *       Description: string concatenation.
 *
 * ----------------------------------------------------------------------------
 */
extern void _basic_string_connect_elem_varg(
    basic_string_t* pt_basic_string, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _basic_string_push_back
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the first basic_string.
 *                    in) ...
 *                          the element.
 *           Returns: void
 *       Description: push the element at the back of basic_string.
 *
 * ----------------------------------------------------------------------------
 */
extern void _basic_string_push_back(basic_string_t* pt_basic_string, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _basic_string_push_back_varg
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the first basic_string.
 *                    in) val_elemlist: va_list
 *                          the element.
 *           Returns: void
 *       Description: push the element at the back of basic_string.
 *
 * ----------------------------------------------------------------------------
 */
extern void _basic_string_push_back_varg(
    basic_string_t* pt_basic_string, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _basic_string_resize
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the first basic_string.
 *                    in) t_resize: size_t
 *                          new size of basic_string.
 *                    in) ...
 *                          the element.
 *           Returns: void
 *       Description: append elements or erase elements from basic string.
 *
 * ----------------------------------------------------------------------------
 */
extern void _basic_string_resize(
    basic_string_t* pt_basic_string, size_t t_resize, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _basic_string_resize_varg
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the first basic_string.
 *                    in) t_resize: size_t
 *                          new size of basic_string.
 *                    in) val_elemlist: va_list
 *                          the element.
 *           Returns: void
 *       Description: append elements or erase elements from basic string.
 *
 * ----------------------------------------------------------------------------
 */
extern void _basic_string_resize_varg(
    basic_string_t* pt_basic_string, size_t t_resize, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _basic_string_assign_elem
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the first basic_string.
 *                    in) t_count: size_t
 *                          the count.
 *                    in) ...
 *                          the element.
 *           Returns: void
 *       Description: erase the exist contents and replace them by t_count copys
 *                    of element.
 *
 * ----------------------------------------------------------------------------
 */
extern void _basic_string_assign_elem(
    basic_string_t* pt_basic_string,
    size_t t_count,
    ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _basic_string_assign_elem_varg
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the first basic_string.
 *                    in) t_count: size_t
 *                          the count.
 *                    in) val_elemlist: va_list
 *                          the element.
 *           Returns: void
 *       Description: erase the exist contents and replace them by t_count copys
 *                    of element.
 *
 * ----------------------------------------------------------------------------
 */
extern void _basic_string_assign_elem_varg(
    basic_string_t* pt_basic_string,
    size_t t_count,
    va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _basic_string_append_elem
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the first basic_string.
 *                    in) t_count: size_t
 *                          the count.
 *                    in) ...
 *                          the element.
 *           Returns: void
 *       Description: append t_count elements to basic_string.
 *
 * ----------------------------------------------------------------------------
 */
extern void _basic_string_append_elem(
    basic_string_t* pt_basic_string,
    size_t t_count,
    ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _basic_string_append_elem_varg
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the first basic_string.
 *                    in) t_count: size_t
 *                          the count.
 *                    in) val_elemlist: va_list
 *                          the element.
 *           Returns: void
 *       Description: append t_count elements to basic_string.
 *
 * ----------------------------------------------------------------------------
 */
extern void _basic_string_append_elem_varg(
    basic_string_t* pt_basic_string,
    size_t t_count,
    va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _basic_string_insert
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the first basic_string.
 *                    in) t_pos: basic_string_iterator_t
 *                          the insert position.
 *                    in) ...
 *                          the element.
 *           Returns: basic_string_iterator_t
 *       Description: insert element before t_pos.
 *
 * ----------------------------------------------------------------------------
 */
extern basic_string_iterator_t _basic_string_insert(
    basic_string_t* pt_basic_string,
    basic_string_iterator_t t_pos,
    ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _basic_string_insert_n
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the first basic_string.
 *                    in) t_pos: basic_string_iterator_t
 *                          the insert position.
 *                    in) t_count: size_t
 *                          the insert count.
 *                    in) ...
 *                          the element.
 *           Returns: basic_string_iterator_t
 *       Description: insert element before t_pos.
 *
 * ----------------------------------------------------------------------------
 */
extern basic_string_iterator_t _basic_string_insert_n(
    basic_string_t* pt_basic_string,
    basic_string_iterator_t t_pos,
    size_t t_count,
    ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _basic_string_insert_n_varg
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the first basic_string.
 *                    in) t_pos: basic_string_iterator_t
 *                          the insert position.
 *                    in) t_count: size_t
 *                          the insert count.
 *                    in) val_elemlist: va_list
 *                          the element.
 *           Returns: basic_string_iterator_t
 *       Description: insert element befor t_pos.
 *
 * ----------------------------------------------------------------------------
 */
extern basic_string_iterator_t _basic_string_insert_n_varg(
    basic_string_t* pt_basic_string, 
    basic_string_iterator_t t_pos, 
    size_t t_count,
    va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _basic_string_insert_elem
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the first basic_string.
 *                    in) t_pos: size_t
 *                          the insert position.
 *                    in) t_count: size_t
 *                          the element count.
 *                    in) ...
 *                          the element.
 *           Returns: void
 *       Description: insert element before t_pos.
 *
 * ----------------------------------------------------------------------------
 */
extern void _basic_string_insert_elem(
    basic_string_t* pt_basic_string, size_t t_pos, size_t t_count, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _basic_string_insert_elem_varg
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the first basic_string.
 *                    in) t_pos: size_t
 *                          the insert position.
 *                    in) t_count: size_t
 *                          the element count.
 *                    in) val_elemlist: va_list
 *                          the element.
 *           Returns: void
 *       Description: insert element befor t_pos.
 *
 * ----------------------------------------------------------------------------
 */
extern void _basic_string_insert_elem_varg(
    basic_string_t* pt_basic_string,
    size_t t_pos,
    size_t t_count,
    va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _basic_string_range_replace_elem
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the first basic_string.
 *                    in) t_begin: basic_string_iterator_t
 *                          the begin position.
 *                    in) t_end: basic_string_iterator_t
 *                          the end position.
 *                    in) t_count: size_t
 *                          the element count.
 *                    in) ...
 *                          the element.
 *           Returns: void
 *       Description: replace range [t_begin, t_end) with t_count elements.
 *
 * ----------------------------------------------------------------------------
 */
extern void _basic_string_range_replace_elem(
    basic_string_t* pt_basic_string,
    basic_string_iterator_t t_begin,
    basic_string_iterator_t t_end,
    size_t t_count,
    ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _basic_string_range_replace_elem_varg
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the first basic_string.
 *                    in) t_begin: basic_string_iterator_t
 *                          the begin position.
 *                    in) t_end: basic_string_iterator_t
 *                          the end position.
 *                    in) t_count: size_t
 *                          the element count.
 *                    in) val_elemlist: va_list
 *                          the element.
 *           Returns: void
 *       Description: replace range [t_begin, t_end) with t_count elements.
 *
 * ----------------------------------------------------------------------------
 */
extern void _basic_string_range_replace_elem_varg(
    basic_string_t* pt_basic_string,
    basic_string_iterator_t t_begin,
    basic_string_iterator_t t_end,
    size_t t_count,
    va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _basic_string_replace_elem
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the first basic_string.
 *                    in) t_pos: size_t
 *                          the begin position.
 *                    in) t_le: size_t
 *                          the replace length.
 *                    in) t_count: size_t
 *                          the element count.
 *                    in) ...
 *                          the element.
 *           Returns: void
 *       Description: replace range [t_begin, t_end) with t_count elements.
 *
 * ----------------------------------------------------------------------------
 */
extern void _basic_string_replace_elem(
    basic_string_t* pt_basic_string,
    size_t t_pos,
    size_t t_len,
    size_t t_count,
    ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _basic_string_replace_elem_varg
 *        Parameters: in) pt_basic_string: basic_string_t*
 *                          the first basic_string.
 *                    in) t_pos: size_t
 *                          the begin position.
 *                    in) t_le: size_t
 *                          the replace length.
 *                    in) t_count: size_t
 *                          the element count.
 *                    in) val_elemlist: va_list
 *                          the element.
 *           Returns: void
 *       Description: replace range [t_begin, t_end) with t_count elements.
 *
 * ----------------------------------------------------------------------------
 */
extern void _basic_string_replace_elem_varg(
    basic_string_t* pt_basic_string,
    size_t t_pos,
    size_t t_len,
    size_t t_count,
    va_list val_elemlist);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_BASIC_STRING_PRIVATE_H */
/** eof **/

