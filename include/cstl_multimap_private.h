/*
 *  The private interface of multimap.
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

#ifndef _CSTL_MULTIMAP_PRIVATE_H
#define _CSTL_MULTIMAP_PRIVATE_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
#define _GET_MULTIMAP_AVL_TREE(pt_multimap)\
    (&((pt_multimap)->_t_tree._t_avl))
#define _GET_MULTIMAP_RB_TREE(pt_multimap)\
    (&((pt_multimap)->_t_tree._t_rb))

/** data type declaration and struct, union, enum section **/
/* the multimap use rb tree default */
typedef struct _tagmultimap
{
    pair_t _t_pair;
    union
    {
        avl_tree_t _t_avl;
        rb_tree_t  _t_rb;
    }_t_tree;
}multimap_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _create_multimap
 *        Parameters: in) t_keytypesize: size_t
 *                          the key element type size.
 *                    in) s_keytypename: const char*
 *                          the key element type name.
 *                    in) t_valuetypesize: size_t
 *                          the value element type size.
 *                    in) s_valuetypename: const char*
 *                          the value element type name.
 *           Returns: multimap_t
 *                          new multimap.
 *       Description: create the new multimap.
 *
 * ----------------------------------------------------------------------------
 */
extern multimap_t _create_multimap(
    size_t t_keytypesize, const char* s_keytypename,
    size_t t_valuetypesize, const char* s_valuetypename);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _multimap_find
 *        Parameters: in) cpt_multimap: const multimap_t*
 *                        the multimap pointer.
 *                    in) ...
 *                        the target value.
 *           Returns: multimap_iterator_t
 *                        the target iterator or end iterator.
 *       Description: find the value in multimap.
 *
 * ----------------------------------------------------------------------------
 */
extern multimap_iterator_t _multimap_find(const multimap_t* cpt_multimap, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _multimap_find_varg
 *        Parameters: in) cpt_multimap: const multimap_t*
 *                        the multimap pointer.
 *                    in) val_elemlist: va_list
 *                        the target value.
 *           Returns: multimap_iterator_t
 *                        the target iterator or end iterator.
 *       Description: find the value in multimap.
 *
 * ----------------------------------------------------------------------------
 */
extern multimap_iterator_t _multimap_find_varg(
    const multimap_t* cpt_multimap, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _multimap_count
 *        Parameters: in) cpt_multimap: const multimap_t*
 *                        the multimap pointer.
 *                    in) ...
 *                        the target value.
 *           Returns: size_t
 *                        count.
 *       Description: counts the numbers of element whose key is value.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t _multimap_count(const multimap_t* cpt_multimap, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _multimap_count_varg
 *        Parameters: in) cpt_multimap: const multimap_t*
 *                        the multimap pointer.
 *                    in) val_elemlist: va_list
 *                        the target value.
 *           Returns: size_t
 *                        count.
 *       Description: counts the numbers of element whose key is value.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t _multimap_count_varg(
    const multimap_t* cpt_multimap, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _multimap_lower_bound
 *        Parameters: in) cpt_multimap: const multimap_t*
 *                        the multimap pointer.
 *                    in) ...
 *                        the target value.
 *           Returns: multimap_iterator_t
 *                        the target iterator or end iterator.
 *       Description: find the first element whose key is not less then value.
 *
 * ----------------------------------------------------------------------------
 */
extern multimap_iterator_t _multimap_lower_bound(
    const multimap_t* cpt_multimap, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _multimap_lower_bound_varg
 *        Parameters: in) cpt_multimap: const multimap_t*
 *                        the multimap pointer.
 *                    in) val_elemlist: va_list
 *                        the target value.
 *           Returns: multimap_iterator_t
 *                        the target iterator or end iterator.
 *       Description: find the first element whose key is not less then value.
 *
 * ----------------------------------------------------------------------------
 */
extern multimap_iterator_t _multimap_lower_bound_varg(
    const multimap_t* cpt_multimap, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _multimap_upper_bound
 *        Parameters: in) cpt_multimap: const multimap_t*
 *                        the multimap pointer.
 *                    in) ...
 *                        the target value.
 *           Returns: multimap_iterator_t
 *                        the target iterator or end iterator.
 *       Description: find the first element whose key is greater then value.
 *
 * ----------------------------------------------------------------------------
 */
extern multimap_iterator_t _multimap_upper_bound(
    const multimap_t* cpt_multimap, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _multimap_upper_bound_varg
 *        Parameters: in) cpt_multimap: const multimap_t*
 *                        the multimap pointer.
 *                    in) val_elemlist: va_list
 *                        the target value.
 *           Returns: multimap_iterator_t
 *                        the target iterator or end iterator.
 *       Description: find the first element whose key is greater then value.
 *
 * ----------------------------------------------------------------------------
 */
extern multimap_iterator_t _multimap_upper_bound_varg(
    const multimap_t* cpt_multimap, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _multimap_equal_range
 *        Parameters: in) cpt_multimap: const multimap_t*
 *                        the multimap pointer.
 *                    in) ...
 *                        the target value.
 *           Returns: pair_t(multimap_iterator_t, multimap_iterator_t).
 *       Description: find a range that contain all elements whos key is value.
 *
 * ----------------------------------------------------------------------------
 */
extern pair_t _multimap_equal_range(const multimap_t* cpt_multimap, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _multimap_equal_range_varg
 *        Parameters: in) cpt_multimap: const multimap_t*
 *                        the multimap pointer.
 *                    in) val_elemlist: va_list
 *                        the target value.
 *           Returns: pair_t(multimap_iterator_t, multimap_iterator_t).
 *       Description: find a range that contain all elements whos key is value.
 *
 * ----------------------------------------------------------------------------
 */
extern pair_t _multimap_equal_range_varg(
    const multimap_t* cpt_multimap, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _multimap_erase
 *        Parameters: in) pt_multimap: multimap_t*
 *                        the rb tree pointer.
 *                    in) ...
 *                        the target value.
 *           Returns: size_t
 *                        the element numbers.
 *       Description: erase all elements whose key is value.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t _multimap_erase(multimap_t* pt_multimap, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _multimap_erase_varg
 *        Parameters: in) pt_multimap: multimap_t*
 *                        the rb tree pointer.
 *                    in) val_elemlist: va_list
 *                        the target value.
 *           Returns: size_t
 *                        the element numbers.
 *       Description: erase all elements whose key is value.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t _multimap_erase_varg(multimap_t* pt_multimap, va_list val_elemlist);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_MULTIMAP_PRIVATE_H */
/** eof **/

