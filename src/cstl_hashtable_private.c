/*
 *  The implementation of hashtable private interface.
 *  Copyright (C)  2008 - 2014  Wangbo
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

/** include section **/
#include <cstl/cstl_def.h>
#include <cstl/cstl_alloc.h>
#include <cstl/cstl_types.h>
#include <cstl/citerator.h>
#include <cstl/cvector.h>
#include <cstl/cstring.h>

#include <cstl/cstl_hashtable_iterator.h>
#include <cstl/cstl_hashtable_private.h>
#include <cstl/cstl_hashtable.h>

#include "cstl_hashtable_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Create hashtable container auxiliary function.
 */
bool_t _create_hashtable_auxiliary(_hashtable_t* pt_hashtable, const char* s_typename)
{
    assert(pt_hashtable != NULL);
    assert(s_typename != NULL);

    /* create new vector */
    /* register _hashnode_t* type for vecotr */
    _type_register(sizeof(_hashnode_pointer_t), _HASHTABLE_NODE_NAME, NULL, NULL, NULL, NULL);
    if (!_create_vector_auxiliary(&pt_hashtable->_vec_bucket, _HASHTABLE_NODE_NAME)) {
        return false;
    }

    /* get type information */
    _type_get_type(&pt_hashtable->_t_typeinfo, s_typename);
    if (pt_hashtable->_t_typeinfo._t_style == _TYPE_INVALID) {
        return false;
    }

    pt_hashtable->_t_nodecount = 0;
    pt_hashtable->_ufun_hash = NULL;
    pt_hashtable->_bfun_compare = NULL;

    /* initialize the allocator */
    _alloc_init(&pt_hashtable->_t_allocator);
    return true;
}

/**
 * Destroy hashtable container auxiliary function.
 */
void _hashtable_destroy_auxiliary(_hashtable_t* pt_hashtable)
{
    assert(pt_hashtable != NULL);
    assert(_hashtable_is_inited(pt_hashtable) || _hashtable_is_created(pt_hashtable));

    /* destroy all elements */
    _hashtable_clear(pt_hashtable);

    /* destroy bucket vector */
    _vector_destroy_auxiliary(&pt_hashtable->_vec_bucket);

    /* destroy allocator */
    _alloc_destroy(&pt_hashtable->_t_allocator);

    /* destroy hash, compare and destroy element function */
    pt_hashtable->_ufun_hash = NULL;
    pt_hashtable->_bfun_compare = NULL;
    pt_hashtable->_t_nodecount = 0;
}

/** local function implementation section **/

/** eof **/

