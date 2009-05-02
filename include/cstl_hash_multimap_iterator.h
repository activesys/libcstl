/*
 *  The iterator interface of hash_multimap.
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

#ifndef _CSTL_HASH_MULTIMAP_ITERATOR_H
#define _CSTL_HASH_MULTIMAP_ITERATOR_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
typedef iterator_t hash_multimap_iterator_t;
struct _taghashmultimap;

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * Iterator support.
 */
extern hash_multimap_iterator_t create_hash_multimap_iterator(void);
extern void _hash_multimap_iterator_get_value(
    const struct _taghashmultimap* cpt_hash_multimap,
    const hash_multimap_iterator_t* cpt_iterator, 
    void* pv_value);
extern const void* _hash_multimap_iterator_get_pointer(
    const struct _taghashmultimap* cpt_hash_multimap,
    const hash_multimap_iterator_t* cpt_iterator); 
extern void _hash_multimap_iterator_next(
    const struct _taghashmultimap* cpt_hash_multimap, 
    hash_multimap_iterator_t* pt_iterator);
extern bool_t _hash_multimap_iterator_equal(
    const struct _taghashmultimap* cpt_hash_multimap,
    const hash_multimap_iterator_t* cpt_iterator,
    hash_multimap_iterator_t t_iterator);
extern int _hash_multimap_iterator_distance(
    const hash_multimap_iterator_t* cpt_begin, 
    const hash_multimap_iterator_t* cpt_end);
extern bool_t _hash_multimap_iterator_before(
    const hash_multimap_iterator_t* cpt_iteratorfirst, 
    const hash_multimap_iterator_t* cpt_iteratorsecond);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_HASH_MULTIMAP_ITERATOR_H */
/** eof **/

