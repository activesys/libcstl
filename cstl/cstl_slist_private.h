/*
 *  The slist struct and private interface.
 *  Copyright (C)  2008 - 2012  Wangbo
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

#ifndef _CSTL_SLIST_PRIVATE_H_
#define _CSTL_SLIST_PRIVATE_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
#define _SLIST_NODE_SIZE(typesize) ((typesize) + sizeof(_slistnode_t) - sizeof(_byte_t))

/** data type declaration and struct, union, enum section **/
/*
 * +----------------+
 * | next node      |
 * +----------------+
 * | data  ...      |
 * |     . . .      |
 * +----------------+
 */
typedef struct _tagslistnode
{
    struct _tagslistnode* _pt_next;
    _byte_t               _pby_data[1];   /* the element value */
}_slistnode_t;

typedef struct _tagslist
{
    /* element type information */
    _typeinfo_t  _t_typeinfo;

    /* memory allocate */
    _alloc_t     _t_allocator;

    /* slist core struct */
    _slistnode_t _t_head;
}slist_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Create slist container.
 * @param s_typename    type name.
 * @return slist container pointer, if create slist successfully, else return NULL.
 * @remarks if s_typename == NULL, the behavior is undefined. s_typename must be c builtin type, libcstl builtin type or
 *          user defined type, otherwise creation will be failure.
 */
extern slist_t* _create_slist(const char* s_typename);

/**
 * Create slist container auxiliary function.
 * @param pslist_slist  slist container.
 * @param s_typename    type name.
 * @return true if create slist container successfully, otherwise return false.
 * @remarks if pslist_slist == NULL or s_typename == NULL, the behavior is undefined. s_typename must be c builtin type,
 *          libcstl builtin type or user defined type, otherwise creation will be failure.
 */
extern bool_t _create_slist_auxiliary(slist_t* pslist_slist, const char* s_typename);

/**
 * Initialize slist with specified element.
 * @param pslist_slist   uninitialized slist container.
 * @param t_count        element number.
 * @param ...            specificed element.
 * @return void
 * @remarks if pslist_slist == NULL, then the behavior is undefined. the type of specificed element and slist element
 *          type must be same, otherwise the behavior is undefined. the first specificed element is in use, others are
 *          not in use. slist container must be created by create_slist, otherwise the behavior is undefined.
 */
extern void _slist_init_elem(slist_t* pslist_slist, size_t t_count, ...);

/**
 * Initialize slist with variable argument slist of specified element.
 * @param pslist_slist   uninitialized slist container.
 * @param t_count        element number.
 * @param val_elemlist   variable argument list of specificed element.
 * @return void
 * @remarks if pslist_slist == NULL, then the behavior is undefined. the type of specificed element and slist element
 *          type must be same, otherwise the behavior is undefined. the first specificed element is in use, others are
 *          not in use. slist container must be created by create_slist, otherwise the behavior is undefined.
 */
extern void _slist_init_elem_varg(slist_t* pslist_slist, size_t t_count, va_list val_elemlist);

/**
 * Destroy slist container auxiliary function.
 * @param pslist_slist   slist container.
 * @return void.
 * @remarks if pslist_slist == NULL, then the behavior is undefined. slist container must be initialized or created by
 *          create_slist, otherwise the behavior is undefined.
 */
extern void _slist_destroy_auxiliary(slist_t* pslist_slist);

/**
 * Assign slist with specificed element.
 * @param pslist_slist   slist container.
 * @param t_count        element number.
 * @param ...            specificed element.
 * @return void.
 * @remarks if pslist_slist == NULL or slist is uninitialized, then the behavior is undefined. the type of specificed
 *          element and slist element type must be same, otherwise the behavior is undefined. the first specificed is
 *          in use, others are not in use.
 */
extern void _slist_assign_elem(slist_t* pslist_slist, size_t t_count, ...);

/**
 * Assign slist with variable argument of specificed element.
 * @param pslist_slist   slist container.
 * @param t_count        element number.
 * @param val_elemlist   variable argumnet list of specificed element.
 * @return void.
 * @remarks if pslist_slist == NULL or slist is uninitialized, then the behavior is undefined. the type of specificed
 *          element and slist element type must be same, otherwise the behavior is undefined. the first specificed is
 *          in use, others are not in use.
 */
extern void _slist_assign_elem_varg(slist_t* pslist_slist, size_t t_count, va_list val_elemlist);

/**
 * Add specificed element at the begin of slist container. 
 * @param pslist_slist    slist container.
 * @param ...             specificed element.
 * @return void.
 * @remarks if pslist_slist == NULL or slist is uninitialized, then the behavior is undefined. the type of specificed
 *          element and slist element type must be same, otherwise the behavior is undefined. the first specificed is
 *          in use, others are not in use.
 */
extern void _slist_push_front(slist_t* pslist_slist, ...);

/**
 * Add specificed element from variable argument slist at the begin of slist container. 
 * @param pslist_slist    slist container.
 * @param val_elemlist    variable argumnet list of specificed element.
 * @return void.
 * @remarks if pslist_slist == NULL or slist is uninitialized, then the behavior is undefined. the type of specificed
 *          element and slist element type must be same, otherwise the behavior is undefined. the first specificed is
 *          in use, others are not in use.
 */
extern void _slist_push_front_varg(slist_t* pslist_slist, va_list val_elemlist);

/**
 * Remove specificed element from slist container.
 * @param pslist_slist    slist container.
 * @param ...             specificed element.
 * @return void.
 * @remarks if pslist_slist == NULL or slist is uninitialized, then the behavior is undefined. the type of specificed
 *          element and slist element type must be same, otherwise the behavior is undefined. the first specificed is
 *          in use, others are not in use. this function remove all element that equal to specificed, if no such element
 *          then does nothing.
 */
extern void _slist_remove(slist_t* pt_slist, ...);

/**
 * Remove element that specificed by variable argument slist from slist container.
 * @param pslist_slist    slist container.
 * @param val_elemlist    variable argument list.
 * @return void.
 * @remarks if pslist_slist == NULL or slist is uninitialized, then the behavior is undefined. the type of specificed
 *          element and slist element type must be same, otherwise the behavior is undefined. the first specificed is
 *          in use, others are not in use. this function remove all element that equal to specificed, if no such element
 *          then does nothing.
 */
extern void _slist_remove_varg(slist_t* pt_slist, va_list val_elemlist);

/**
 * Reset the size of slist elements.
 * @param pslist_slist  slist container.
 * @param t_resize      new size of slist elements.
 * @param ...           specificed element.
 * @return void.
 * @remarks if pslist_slist == NULL or slist is uninitialized, then the behavior is undefined. the type of specificed
 *          element and slist element type must be same, otherwise the behavior is undefined. the first specificed is
 *          in use, others are not in use. if t_resize less than current slist size, then erase elmement from the end.
 *          if t_resize greater than current slist size, then append elements to the end, and the element is specificed
 *          element.
 */
extern void _slist_resize_elem(slist_t* pslist_slist, size_t t_resize, ...);

/**
 * Reset the size of slist elements, and filled element is from variable argument slist.
 * @param pslist_slist  slist container.
 * @param t_resize      new size of slist elements.
 * @param val_elemlist  variable argument list.
 * @return void.
 * @remarks if pslist_slist == NULL or slist is uninitialized, then the behavior is undefined. the type of specificed
 *          element and slist element type must be same, otherwise the behavior is undefined. the first specificed is
 *          in use, others are not in use. if t_resize less than current slist size, then erase elmement from the end.
 *          if t_resize greater than current slist size, then append elements to the end, and the element is from
 *          variable argument slist.
 */
extern void _slist_resize_elem_varg(slist_t* pslist_slist, size_t t_resize, va_list val_elemlist);

/**
 * Insert multiple copys of element after specificed position.
 * @param pslist_slist  slist container.
 * @param it_pos        before insert position.
 * @param t_count       element number.
 * @param val_elemlist  variable argument list.
 * @return void.
 * @remarks if pslist_slist == NULL or slist is uninitialized, then the behavior is undefined. the it_pos must be invalid
 *          iterator of slist container, otherwise the behavior is undefined. the type of specificed element and slist
 *          element type must be same, otherwise the behavior is undefined. the first specificed is in use, others are not
 *          in use.
 */
extern void _slist_insert_after_n_varg(slist_t* pslist_slist, slist_iterator_t it_pos, size_t t_count, va_list val_elemlist);

/**
 * Insert one copy of element after specificed position.
 * @param pslist_slist  slist container.
 * @param it_pos        before insert position.
 * @param t_count       element number.
 * @param ...           specificed element.
 * @return position refereced the first inserted elements.
 * @remarks if pslist_slist == NULL or slist is uninitialized, then the behavior is undefined. the it_pos must be invalid
 *          iterator of slist container, otherwise the behavior is undefined. the type of specificed element and slist
 *          element type must be same, otherwise the behavior is undefined. the first specificed is in use, others are not
 *          in use.
 */
extern slist_iterator_t _slist_insert_after(slist_t* pslist_slist, slist_iterator_t it_pos, ...);

/**
 * Insert multiple copys of element after specificed position.
 * @param pslist_slist  slist container.
 * @param it_pos        before insert position.
 * @param t_count       element number.
 * @param ...           specificed element.
 * @return void.
 * @remarks if pslist_slist == NULL or slist is uninitialized, then the behavior is undefined. the it_pos must be invalid
 *          iterator of slist container, otherwise the behavior is undefined. the type of specificed element and slist
 *          element type must be same, otherwise the behavior is undefined. the first specificed is in use, others are not
 *          in use.
 */
extern void _slist_insert_after_n(slist_t* pslist_slist, slist_iterator_t it_pos, size_t t_count, ...);

/**
 * Insert one copy of element befor specificed position.
 * @param pslist_slist  slist container.
 * @param it_pos        insert position.
 * @param t_count       element number.
 * @param ...           specificed element.
 * @return position refereced the first inserted elements.
 * @remarks if pslist_slist == NULL or slist is uninitialized, then the behavior is undefined. the it_pos must be invalid
 *          iterator of slist container, otherwise the behavior is undefined. the type of specificed element and slist
 *          element type must be same, otherwise the behavior is undefined. the first specificed is in use, others are not
 *          in use.
 */
extern slist_iterator_t _slist_insert(slist_t* pslist_slist, slist_iterator_t it_pos, ...);

/**
 * Insert multiple copys of element befor specificed position.
 * @param pslist_slist  slist container.
 * @param it_pos        insert position.
 * @param t_count       element number.
 * @param ...           specificed element.
 * @return void.
 * @remarks if pslist_slist == NULL or slist is uninitialized, then the behavior is undefined. the it_pos must be invalid
 *          iterator of slist container, otherwise the behavior is undefined. the type of specificed element and slist
 *          element type must be same, otherwise the behavior is undefined. the first specificed is in use, others are not
 *          in use.
 */
extern void _slist_insert_n(slist_t* pslist_slist, slist_iterator_t it_pos, size_t t_count, ...);

/**
 * Initialize element with slist element type auxiliary function.
 * @param pslist_slist  slist container.
 * @param pv_elem       initialized element.
 * @return void.
 * @remarks if pslist_slist == NULL or pv_elem == NULL, then the behavior is undefined. pslist_slist must be initialized
 *          slist container or created by create_slist, otherwise the behavior is undefined.
 */
extern void _slist_init_elem_auxiliary(slist_t* pslist_slist, void* pv_value);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_SLIST_PRIVATE_H_ */
/** eof **/

