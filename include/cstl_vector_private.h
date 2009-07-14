/*
 *  The definition of vector_t struct.
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

#ifndef _CSTL_VECTOR_PRIVATE_H
#define _CSTL_VECTOR_PRIVATE_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
/*
 * vector_t
 * _pc_start             _pc_finish      _pc_endofstorage
 * |                     |               |
 * V                     V               V
 * +-------------------------------------+
 * |    ... data ...     |               |
 * +-------------------------------------+
 * |<--------size()----->|
 * |<---------------capacity()---------->|
 */
typedef struct _tagvector
{
    /* element type information */
    _typeinfo_t _t_typeinfo;

    /* memory allocate */
    alloc_t     _t_allocater;

    /* vector core struct pointer */
    char*       _pc_start;          /* the start of used space */
    char*       _pc_finish;         /* the end of used space */
    char*       _pc_endofstorage;   /* the end of capacity space */
}vector_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * Creation and initialization vector_t.
 */
extern vector_t* _create_vector(const char* s_typename);
extern bool_t _create_vector_auxiliary(vector_t* pt_vector, const char* s_typename);
extern void _vector_init_elem(vector_t* pt_vector, size_t t_count, ...);
extern void _vector_init_elem_varg(
    vector_t* pt_vector, size_t t_count, va_list val_elemlist);
extern void _vector_destroy_auxiliary(vector_t* pt_vector);

/*
 * The assignment operator of vector_t.
 */
extern void _vector_assign_elem(vector_t* pt_vector, size_t t_count, ...);
extern void _vector_assign_elem_varg(
    vector_t* pt_vector, size_t t_count, va_list val_elemlist);

/*
 * Insert a new element at the end of vector_t.
 */
extern void _vector_push_back(vector_t* pt_vector, ...);
extern void _vector_push_back_varg(vector_t* pt_vector, va_list val_elemlist);

/*
 * Append elements or erase elements from the end, as necessary to make the vector_t's
 * size exactly t_resize elements.
 */
extern void _vector_resize_elem(vector_t* pt_vector, size_t t_resize, ...);
extern void _vector_resize_elem_varg(
    vector_t* pt_vector, size_t t_resize, va_list val_elemlist);

/*
 * Insert t_count copys of element befor position t_pos.
 */
extern vector_iterator_t _vector_insert_n(
    vector_t* pt_vector, vector_iterator_t t_pos, size_t t_count, ...);
extern vector_iterator_t _vector_insert_n_varg(
    vector_t* pt_vector, vector_iterator_t t_pos, size_t t_count, va_list val_elemlist);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_VECTOR_PRIVATE_H */
/** eof **/

