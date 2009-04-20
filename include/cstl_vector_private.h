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
 *  Author Email: activesys.wb@gmail.com
 *                activesys@sina.com.cn
 */

#ifndef _CSTL_VECTOR_PRIVATE_H
#define _CSTL_VECTOR_PRIVATE_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
typedef struct _tagvector
{
    /* element identify */
    size_t  _t_typesize;                          /* element size */
    char    _sz_typename[_ELEM_TYPE_NAME_SIZE+1]; /* element name */

    /* memory allocate */
    alloc_t _t_allocater;

    /* vector core struct pointer */
    char*   _pc_start;          /* the start of used space */
    char*   _pc_finish;         /* the end of used space */
    char*   _pc_endofstorage;   /* the end of capacity space */

    /* 
     * the compare function :
     * < 0  : element first < element second.
     * == 0 : element first == element second.
     * > 0  : element first > element second. 
     */
    int (*_pfun_cmp)(const void*, const void*);
}vector_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _create_vector
 *        Parameters: in) t_typesize: size_t
 *                          the element type size.
 *                    in) s_typename: const char*
 *                          the element type name.
 *           Returns: vector_t
 *                          new vector.
 *       Description: create the new vector.
 *
 * ----------------------------------------------------------------------------
 */
extern vector_t _create_vector(size_t t_typesize, const char* s_typename);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _vector_init_elem
 *        Parameters: in) pt_vector: vector_t*
 *                    in) t_count: size_t
 *                          element count.
 *                    in) ...
 *                          element.
 *           Returns: void
 *       Description: initialize the vector.
 *
 * ----------------------------------------------------------------------------
 */
extern void _vector_init_elem(vector_t* pt_vector, size_t t_count, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _vector_init_elem_varg
 *        Parameters: in) pt_vector: vector_t*
 *                    in) t_count: size_t
 *                          element count.
 *                    in) val_elemlist: va_list
 *                          element list.
 *           Returns: void
 *       Description: initialize the vector.
 *
 * ----------------------------------------------------------------------------
 */
extern void _vector_init_elem_varg(
    vector_t* pt_vector, size_t t_count, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _vector_assign_elem
 *        Parameters: in) pt_vector: vector_t*
 *                          the vector for assign.
 *                    in) t_count: size_t
 *                          the element count.
 *                    in) ...
 *                          the element.
 *           Returns: void
 *       Description: assign n_elemcount copys of element.
 *
 * ----------------------------------------------------------------------------
 */
extern void _vector_assign_elem(vector_t* pt_vector, size_t t_count, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _vector_assign_elem_varg
 *        Parameters: in) pt_vector: vector_t*
 *                          the vector for assign.
 *                    in) t_count: size_t
 *                          the element count.
 *                    in) val_elemlist: va_list
 *                          the element list.
 *           Returns: void
 *       Description: assign n_elemcount copys of element.
 *
 * ----------------------------------------------------------------------------
 */
extern void _vector_assign_elem_varg(
    vector_t* pt_vector, size_t t_count, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _vector_push_back
 *        Parameters: in) pt_vector: vector_t*
 *                          the vector.
 *                    in) ...
 *                          the element.
 *           Returns: void
 *       Description: append a copy of element at the end.
 *
 * ----------------------------------------------------------------------------
 */
extern void _vector_push_back(vector_t* pt_vector, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _vector_push_back_varg
 *        Parameters: in) pt_vector: vector_t*
 *                          the vector.
 *                    in) val_elemlist: va_list
 *                          the element.
 *           Returns: void
 *       Description: append a copy of element at the end.
 *
 * ----------------------------------------------------------------------------
 */
extern void _vector_push_back_varg(vector_t* pt_vector, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _vector_resize_elem
 *        Parameters: in) pt_vector: vector_t*
 *                          the vector.
 *                    in) t_resize: size_t
 *                          the new size of vector.
 *                    in) ...
 *                          the default element.
 *           Returns: void
 *       Description: change the number of elements to t_resize, if the size
 *                    grows new element create with the default element.
 *
 * ----------------------------------------------------------------------------
 */
extern void _vector_resize_elem(vector_t* pt_vector, size_t t_resize, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _vector_resize_elem_varg
 *        Parameters: in) pt_vector: vector_t*
 *                          the vector.
 *                    in) t_resize: size_t
 *                          the new size of vector.
 *                    in) val_elemlist: va_list
 *                          the default element.
 *           Returns: void
 *       Description: change the number of elements to t_resize, if the size
 *                    grows new element create with the default element.
 *
 * ----------------------------------------------------------------------------
 */
extern void _vector_resize_elem_varg(
    vector_t* pt_vector, size_t t_resize, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _vector_insert_n
 *        Parameters: in) pt_vector: vector_t*
 *                          the vector.
 *                    in) t_pos: vector_iterator_t
 *                          the insert position.
 *                    in) n_elemcount: int
 *                          the element count.
 *                    in) ...
 *                          the element list.
 *           Returns: vector_iterator_t
 *       Description: insert at iterator position t_pos n_elemcount copys of
 *                    element and return nothing.
 *
 * ----------------------------------------------------------------------------
 */
extern vector_iterator_t _vector_insert_n(
    vector_t* pt_vector, 
    vector_iterator_t t_pos, 
    size_t t_count, 
    ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _vector_insert_n_varg
 *        Parameters: in) pt_vector: vector_t*
 *                          the vector.
 *                    in) t_pos: vector_iterator_t
 *                          the insert position.
 *                    in) n_elemcount: int
 *                          the element count.
 *                    in) val_elemlist: va_list
 *                          the element list.
 *           Returns: vector_iterator_t
 *       Description: insert at iterator position t_pos n_elemcount copys of
 *                    element and return nothing.
 *
 * ----------------------------------------------------------------------------
 */
extern vector_iterator_t _vector_insert_n_varg(
    vector_t* pt_vector, 
    vector_iterator_t t_pos, 
    size_t t_count, 
    va_list val_elemlist);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_VECTOR_PRIVATE_H */
/** eof **/

