/*
 *  The private interface of hashtable.
 *  Copyright (C)  2008 - 2013  Wangbo
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

#ifndef _CSTL_HASHTABLE_PRIVATE_H_
#define _CSTL_HASHTABLE_PRIVATE_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
#define _HASHTABLE_NODE_SIZE(typesize) ((typesize) + sizeof(_hashnode_t) - 1)

/** data type declaration and struct, union, enum section **/
typedef struct _taghashnode
{
    struct _taghashnode* _pt_next;
    _byte_t              _pby_data[1];
}_hashnode_t;

typedef struct _taghashtable
{
    /* element type information */
    _typeinfo_t       _t_typeinfo;

    /* memory allocate */
    _alloc_t          _t_allocator;

    /* buckets and node */
    vector_t          _vec_bucket;
    size_t            _t_nodecount;

    /* hash function */
    ufun_t            _ufun_hash;
    /* key compare function */
    bfun_t            _bfun_compare;
}_hashtable_t;

/* for the result of equal_range and insert_unique function */

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Create hashtable container auxiliary function.
 * @param pt_hashtable      uncreated container.
 * @param s_typename        element type name.
 * @return if create hashtable successfully return true, otherwise return false.
 * @remarks if pt_hashtable == NULL or s_typename == NULL, then the behavior is undefined. s_typename should be C builtin
 *          type name, libcstl builtin typename or registed user defined type name, otherwise the function will return false.
 */
extern bool_t _create_hashtable_auxiliary(_hashtable_t* pt_hashtable, const char* s_typename);

/**
 * Destroy hashtable container auxiliary function.
 * @param pt_hashtable      hashtable container.
 * @return void.
 * @remarks if pt_hashtable == NULL, then the behavior is undefined. hashtable must be initialized or created by
 *          _create_hashtable(), otherwise the behavior is undefine.
 */
extern void _hashtable_destroy_auxiliary(_hashtable_t* pt_hashtable);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_HASHTABLE_PRIVATE_H_ */
/** eof **/

