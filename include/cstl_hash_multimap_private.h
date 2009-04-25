/*
 *  The private interface of hash_multimap.
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

#ifndef _CSTL_HASH_MULTIMAP_PRIVATE_H
#define _CSTL_HASH_MULTIMAP_PRIVATE_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
typedef struct _taghashmultimap
{
    pair_t      _t_pair;
    hashtable_t _t_hashtable;
}hash_multimap_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _create_hash_multimap
 *        Parameters: in) t_keytypesize: size_t
 *                          the key element type size.
 *                    in) s_keytypename: const char*
 *                          the key element type name.
 *                    in) t_valuetypesize: size_t
 *                          the value element type size.
 *                    in) s_valuetypename: const char*
 *                          the value element type name.
 *           Returns: hash_multimap_t
 *                          new hash_multimap.
 *       Description: create the new hash_multimap.
 *
 * ----------------------------------------------------------------------------
 */
extern hash_multimap_t _create_hash_multimap(
    size_t t_keytypesize, const char* s_keytypename,
    size_t t_valuetypesize, const char* s_valuetypename);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hash_multimap_find
 *        Parameters: in) cpt_hash_multimap: const hash_multimap_t*
 *                        the hash_multimap pointer.
 *                    in) ...
 *                        the target value.
 *           Returns: hash_multimap_iterator_t
 *                        the target iterator or end iterator.
 *       Description: find the value in hash_multimap.
 *
 * ----------------------------------------------------------------------------
 */
extern hash_multimap_iterator_t _hash_multimap_find(
    const hash_multimap_t* cpt_hash_multimap, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hash_multimap_find_varg
 *        Parameters: in) cpt_hash_multimap: const hash_multimap_t*
 *                        the hash_multimap pointer.
 *                    in) val_elemlist: va_list
 *                        the target value.
 *           Returns: hash_multimap_iterator_t
 *                        the target iterator or end iterator.
 *       Description: find the value in hash_multimap.
 *
 * ----------------------------------------------------------------------------
 */
extern hash_multimap_iterator_t _hash_multimap_find_varg(
    const hash_multimap_t* cpt_hash_multimap, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hash_multimap_count
 *        Parameters: in) cpt_hash_multimap: const hash_multimap_t*
 *                        the hash_multimap pointer.
 *                    in) ...
 *                        the target value.
 *           Returns: size_t
 *                        count.
 *       Description: counts the numbers of element whose key is value.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t _hash_multimap_count(const hash_multimap_t* cpt_hash_multimap, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hash_multimap_count_varg
 *        Parameters: in) cpt_hash_multimap: const hash_multimap_t*
 *                        the hash_multimap pointer.
 *                    in) val_elemlist: va_list
 *                        the target value.
 *           Returns: size_t
 *                        count.
 *       Description: counts the numbers of element whose key is value.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t _hash_multimap_count_varg(
    const hash_multimap_t* cpt_hash_multimap, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hash_multimap_equal_range
 *        Parameters: in) cpt_hash_multimap: const hash_multimap_t*
 *                        the hash_multimap pointer.
 *                    in) ...
 *                        the target value.
 *           Returns: pair_t(hash_multimap_iterator_t, hash_multimap_iterator_t).
 *       Description: find a range that contain all elements whos key is value.
 *
 * ----------------------------------------------------------------------------
 */
extern pair_t _hash_multimap_equal_range(
    const hash_multimap_t* cpt_hash_multimap, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hash_multimap_equal_range_varg
 *        Parameters: in) cpt_hash_multimap: const hash_multimap_t*
 *                        the hash_multimap pointer.
 *                    in) val_elemlist: va_list
 *                        the target value.
 *           Returns: pair_t(hash_multimap_iterator_t, hash_multimap_iterator_t).
 *       Description: find a range that contain all elements whos key is value.
 *
 * ----------------------------------------------------------------------------
 */
extern pair_t _hash_multimap_equal_range_varg(
    const hash_multimap_t* cpt_hash_multimap, va_list val_elemlist);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hash_multimap_erase
 *        Parameters: in) pt_hash_multimap: hash_multimap_t*
 *                        the rb tree pointer.
 *                    in) ...
 *                        the target value.
 *           Returns: size_t
 *                        the element numbers.
 *       Description: erase all elements whose key is value.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t _hash_multimap_erase(hash_multimap_t* pt_hash_multimap, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hash_multimap_erase_varg
 *        Parameters: in) pt_hash_multimap: hash_multimap_t*
 *                        the rb tree pointer.
 *                    in) val_elemlist: va_list
 *                        the target value.
 *           Returns: size_t
 *                        the element numbers.
 *       Description: erase all elements whose key is value.
 *
 * ----------------------------------------------------------------------------
 */
extern size_t _hash_multimap_erase_varg(
    hash_multimap_t* pt_hash_multimap, va_list val_elemlist);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_HASH_MULTIMAP_PRIVATE_H */
/** eof **/

