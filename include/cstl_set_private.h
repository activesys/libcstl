/*
 *  The private interface of set.
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

#ifndef _CSTL_SET_PRIVATE_H
#define _CSTL_SET_PRIVATE_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
#define _GET_SET_AVL_TREE(pt_set)\
    (&((pt_set)->_t_tree._t_avl))
#define _GET_SET_RB_TREE(pt_set)\
    (&((pt_set)->_t_tree._t_rb))

/** data type declaration and struct, union, enum section **/
/* the set use rb tree default */
typedef struct _tagset
{
    union
    {
        avl_tree_t _t_avl;
        rb_tree_t  _t_rb;
    }_t_tree;
}set_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _create_set
 *        Parameters: in) t_typesize: size_t
 *                          the element type size.
 *                    in) s_typename: const char*
 *                          the element type name.
 *           Returns: set_t
 *                          new set.
 *       Description: create the new set.
 *
 * ----------------------------------------------------------------------------
 */
extern set_t _create_set(size_t t_typesize, const char* s_typename);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _set_find
 *        Parameters: in) cpt_set: const set_t*
 *                        the set pointer.
 *                    in) ...
 *                        the target value.
 *           Returns: set_iterator_t
 *                        the target iterator or end iterator.
 *       Description: find the value in set.
 *
 * ----------------------------------------------------------------------------
 */
extern set_iterator_t _set_find(const set_t* cpt_set, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _set_find_varg
 *        Parameters: in) cpt_set: const set_t*
 *                        the set pointer.
 *                    in) val_elemlist: va_list
 *                        the target value.
 *           Returns: set_iterator_t
 *                        the target iterator or end iterator.
 *       Description: find the value in set.
 *
 * ----------------------------------------------------------------------------
 */
extern set_iterator_t _set_find_varg(const set_t* cpt_set, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _set_count
 *        Parameters: in) cpt_set: const set_t*
 *                        the set pointer.
 *                    in) ...
 *                        the target value.
 *           Returns: size_t
 *                        count.
 *       Description: counts the numbers of element whose key is value.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t _set_count(const set_t* cpt_set, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _set_count_varg
 *        Parameters: in) cpt_set: const set_t*
 *                        the set pointer.
 *                    in) val_elemlist: va_list
 *                        the target value.
 *           Returns: size_t
 *                        count.
 *       Description: counts the numbers of element whose key is value.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t _set_count_varg(const set_t* cpt_set, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _set_lower_bound
 *        Parameters: in) cpt_set: const set_t*
 *                        the set pointer.
 *                    in) ...
 *                        the target value.
 *           Returns: set_iterator_t
 *                        the target iterator or end iterator.
 *       Description: find the first element whose key is not less then value.
 *
 * ----------------------------------------------------------------------------
 */
extern set_iterator_t _set_lower_bound(const set_t* cpt_set, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _set_lower_bound_varg
 *        Parameters: in) cpt_set: const set_t*
 *                        the set pointer.
 *                    in) val_elemlist: va_list
 *                        the target value.
 *           Returns: set_iterator_t
 *                        the target iterator or end iterator.
 *       Description: find the first element whose key is not less then value.
 *
 * ----------------------------------------------------------------------------
 */
extern set_iterator_t _set_lower_bound_varg(
    const set_t* cpt_set, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _set_upper_bound
 *        Parameters: in) cpt_set: const set_t*
 *                        the set pointer.
 *                    in) ...
 *                        the target value.
 *           Returns: set_iterator_t
 *                        the target iterator or end iterator.
 *       Description: find the first element whose key is greater then value.
 *
 * ----------------------------------------------------------------------------
 */
extern set_iterator_t _set_upper_bound(const set_t* cpt_set, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _set_upper_bound_varg
 *        Parameters: in) cpt_set: const set_t*
 *                        the set pointer.
 *                    in) val_elemlist: va_list
 *                        the target value.
 *           Returns: set_iterator_t
 *                        the target iterator or end iterator.
 *       Description: find the first element whose key is greater then value.
 *
 * ----------------------------------------------------------------------------
 */
extern set_iterator_t _set_upper_bound_varg(
    const set_t* cpt_set, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _set_equal_range
 *        Parameters: in) cpt_set: const set_t*
 *                        the set pointer.
 *                    in) ...
 *                        the target value.
 *           Returns: pair_t(set_iterator_t, set_iterator_t).
 *       Description: find a range that contain all elements whos key is value.
 *
 * ----------------------------------------------------------------------------
 */
extern pair_t _set_equal_range(const set_t* cpt_set, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _set_equal_range_varg
 *        Parameters: in) cpt_set: const set_t*
 *                        the set pointer.
 *                    in) val_elemlist: va_list
 *                        the target value.
 *           Returns: pair_t(set_iterator_t, set_iterator_t).
 *       Description: find a range that contain all elements whos key is value.
 *
 * ----------------------------------------------------------------------------
 */
extern pair_t _set_equal_range_varg(const set_t* cpt_set, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _set_erase
 *        Parameters: in) pt_set: set_t*
 *                        the rb tree pointer.
 *                    in) ...
 *                        the target value.
 *           Returns: size_t
 *                        the element numbers.
 *       Description: erase all elements whose key is value.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t _set_erase(set_t* pt_set, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _set_erase_varg
 *        Parameters: in) pt_set: set_t*
 *                        the rb tree pointer.
 *                    in) val_elemlist: va_list
 *                        the target value.
 *           Returns: size_t
 *                        the element numbers.
 *       Description: erase all elements whose key is value.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t _set_erase_varg(set_t* pt_set, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _set_insert_hint
 *        Parameters: in) pt_set: set_t*
 *                        the set pointer.
 *                    in) t_hint: set_iterator_t
 *                        the hint iterator.
 *                    in) ...
 *                        the target value.
 *           Returns: set_iterator_t
 *                        the iterator of new element.
 *       Description: insert value into set.
 *
 * ----------------------------------------------------------------------------
 */
extern set_iterator_t _set_insert_hint(
    set_t* pt_set, set_iterator_t t_hint, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _set_insert_hint
 *        Parameters: in) pt_set: set_t*
 *                        the set pointer.
 *                    in) t_hint: set_iterator_t
 *                        the hint iterator.
 *                    in) ...
 *                        the target value.
 *           Returns: set_iterator_t
 *                        the iterator of new element.
 *       Description: insert value into set.
 *
 * ----------------------------------------------------------------------------
 */
extern set_iterator_t _set_insert_hint_varg(
    set_t* pt_set, set_iterator_t t_hint, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _set_insert
 *        Parameters: in) pt_set: set_t*
 *                        the set pointer.
 *                    in) ...
 *                        the target value.
 *           Returns: set_iterator_t
 *                        the insert position if failed return set_end().
 *       Description: insert value into set.
 *
 * ----------------------------------------------------------------------------
 */
extern set_iterator_t _set_insert(set_t* pt_set, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _set_insert_varg
 *        Parameters: in) pt_set: set_t*
 *                        the set pointer.
 *                    in) val_elemlist: va_list
 *                        the target value.
 *           Returns: set_iterator_t
 *                        the insert position if failed return set_end().
 *       Description: insert value into set.
 *
 * ----------------------------------------------------------------------------
 */
extern set_iterator_t _set_insert_varg(set_t* pt_set, va_list val_elemlist);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_SET_PRIVATE_H */
/** eof **/

