/*
 *  The private interface of hash_set.
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

#ifndef _CSTL_HASH_SET_PRIVATE_H
#define _CSTL_HASH_SET_PRIVATE_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
typedef struct _taghashset
{
    hashtable_t _t_hashtable;
}hash_set_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _create_hash_set
 *        Parameters: in) t_typesize: size_t
 *                          the element type size.
 *                    in) s_typename: const char*
 *                          the element type name.
 *           Returns: hash_set_t
 *                          new hash_set.
 *       Description: create the new hash_set.
 *
 * ----------------------------------------------------------------------------
 */
extern hash_set_t _create_hash_set(size_t t_typesize, const char* s_typename);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hash_set_find
 *        Parameters: in) cpt_hash_set: const hash_set_t*
 *                        the hash_set pointer.
 *                    in) ...
 *                        the target value.
 *           Returns: hash_set_iterator_t
 *                        the target iterator or end iterator.
 *       Description: find the value in hash_set.
 *
 * ----------------------------------------------------------------------------
 */
extern hash_set_iterator_t _hash_set_find(const hash_set_t* cpt_hash_set, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hash_set_find_varg
 *        Parameters: in) cpt_hash_set: const hash_set_t*
 *                        the hash_set pointer.
 *                    in) val_elemlist: va_list
 *                        the target value.
 *           Returns: hash_set_iterator_t
 *                        the target iterator or end iterator.
 *       Description: find the value in hash_set.
 *
 * ----------------------------------------------------------------------------
 */
extern hash_set_iterator_t _hash_set_find_varg(
    const hash_set_t* cpt_hash_set, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hash_set_count
 *        Parameters: in) cpt_hash_set: const hash_set_t*
 *                        the hash_set pointer.
 *                    in) ...
 *                        the target value.
 *           Returns: size_t
 *                        count.
 *       Description: counts the numbers of element whose key is value.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t _hash_set_count(const hash_set_t* cpt_hash_set, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hash_set_count_varg
 *        Parameters: in) cpt_hash_set: const hash_set_t*
 *                        the hash_set pointer.
 *                    in) val_elemlist: va_list
 *                        the target value.
 *           Returns: size_t
 *                        count.
 *       Description: counts the numbers of element whose key is value.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t _hash_set_count_varg(
    const hash_set_t* cpt_hash_set, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hash_set_equal_range
 *        Parameters: in) cpt_hash_set: const hash_set_t*
 *                        the hash_set pointer.
 *                    in) ...
 *                        the target value.
 *           Returns: pair_t(hash_set_iterator_t, hash_set_iterator_t).
 *       Description: find a range that contain all elements whos key is value.
 *
 * ----------------------------------------------------------------------------
 */
extern pair_t _hash_set_equal_range(const hash_set_t* cpt_hash_set, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hash_set_equal_range_varg
 *        Parameters: in) cpt_hash_set: const hash_set_t*
 *                        the hash_set pointer.
 *                    in) val_elemlist: va_list
 *                        the target value.
 *           Returns: pair_t(hash_set_iterator_t, hash_set_iterator_t).
 *       Description: find a range that contain all elements whos key is value.
 *
 * ----------------------------------------------------------------------------
 */
extern pair_t _hash_set_equal_range_varg(
    const hash_set_t* cpt_hash_set, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hash_set_insert
 *        Parameters: in) pt_hash_set: hash_set_t*
 *                        the hash_set pointer.
 *                    in) ...
 *                        the target value.
 *           Returns: hash_set_iterator_t
 *                        the insert result.
 *       Description: insert value into hash_set.
 *
 * ----------------------------------------------------------------------------
 */
extern hash_set_iterator_t _hash_set_insert(hash_set_t* pt_hash_set, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hash_set_insert_varg
 *        Parameters: in) pt_hash_set: hash_set_t*
 *                        the hash_set pointer.
 *                    in) val_elemlist: va_list
 *                        the target value.
 *           Returns: hash_set_iterator_t
 *                        the insert result.
 *       Description: insert value into hash_set.
 *
 * ----------------------------------------------------------------------------
 */
extern hash_set_iterator_t _hash_set_insert_varg(
    hash_set_t* pt_hash_set, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hash_set_erase
 *        Parameters: in) pt_hash_set: hash_set_t*
 *                        the rb tree pointer.
 *                    in) ...
 *                        the target value.
 *           Returns: size_t
 *                        the element numbers.
 *       Description: erase all elements whose key is value.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t _hash_set_erase(hash_set_t* pt_hash_set, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hash_set_erase_varg
 *        Parameters: in) pt_hash_set: hash_set_t*
 *                        the rb tree pointer.
 *                    in) val_elemlist: va_list
 *                        the target value.
 *           Returns: size_t
 *                        the element numbers.
 *       Description: erase all elements whose key is value.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t _hash_set_erase_varg(hash_set_t* pt_hash_set, va_list val_elemlist);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_HASH_SET_PRIVATE_H */
/** eof **/

