/*
 *  The implementation of memory management.
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

/** include section **/
#include <cstl/cstl_def.h>
#include <cstl/cstl_alloc.h>
#include <cstl/cstl_types.h>

#include "cstl_alloc_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
#ifdef CSTL_MEMORY_MANAGEMENT

/**
 * Initialize the _alloc_t.
 */
void _alloc_init(_alloc_t* pt_allocator)
{
    size_t i = 0;

    assert(pt_allocator != NULL);

    pt_allocator->_t_mempoolsize = 0;
    pt_allocator->_t_mempoolindex = 0;
    pt_allocator->_pby_mempool = NULL;
    
    for (i = 0; i < _MEM_LINK_COUNT; ++i) {
        pt_allocator->_apt_memlink[i] = NULL;
    }

    /* initialize memory pool */
    pt_allocator->_t_mempoolcount = _MEM_POOL_DEFAULT_COUNT;
    pt_allocator->_ppby_mempoolcontainer = (_byte_t**)malloc(pt_allocator->_t_mempoolcount * sizeof(_byte_t*));
    if (pt_allocator->_ppby_mempoolcontainer != NULL) {
        for (i = 0; i < pt_allocator->_t_mempoolcount; ++i) {
            pt_allocator->_ppby_mempoolcontainer[i] = NULL;
        }
    } else {
        fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
}

/**
 * Destroy the _alloc_t.
 */
void _alloc_destroy(_alloc_t* pt_allocator)
{
    size_t i = 0;

    assert(pt_allocator != NULL);

    /* destroy memory pool */
    for (i = 0; i < pt_allocator->_t_mempoolcount; ++i) {
        free(pt_allocator->_ppby_mempoolcontainer[i]);
        pt_allocator->_ppby_mempoolcontainer[i] = NULL;
    }
    free(pt_allocator->_ppby_mempoolcontainer);
    pt_allocator->_ppby_mempoolcontainer = NULL;

    for (i = 0; i < _MEM_LINK_COUNT; ++i) {
        pt_allocator->_apt_memlink[i] = NULL;
    }

    pt_allocator->_pby_mempool = NULL;
    pt_allocator->_t_mempoolindex = 0;
    pt_allocator->_t_mempoolsize = 0;
    pt_allocator->_t_mempoolcount = 0;
}

/**
 * Allocate to user specified amount of memory.
 */
void* _alloc_allocate(_alloc_t* pt_allocator, size_t t_size, size_t t_count)
{
    void*       pv_allocmem = NULL;               /* allocated memory pointer */
    _memlink_t* pt_link = NULL;                   /* memory link */
    size_t      t_allocsize = t_size * t_count;   /* allocated memory size */

    assert(pt_allocator != NULL);

    if (t_allocsize > _MEM_SMALL_MEM_SIZE_MAX) {
        pv_allocmem = _alloc_malloc(t_allocsize);
        assert(pv_allocmem != NULL);
    } else {
        pt_link = pt_allocator->_apt_memlink[_MEM_LINK_INDEX(t_allocsize)];
        if (pt_link == NULL) {
            _alloc_apply_formated_memory(pt_allocator, _MEM_ROUND_UP(t_allocsize));
            pt_link = pt_allocator->_apt_memlink[_MEM_LINK_INDEX(t_allocsize)];
            assert(pt_link != NULL);
        }
        pt_allocator->_apt_memlink[_MEM_LINK_INDEX(t_allocsize)] = pt_link->_pui_nextmem;
        pv_allocmem = (void*)pt_link;
    }

    return pv_allocmem;
}

/**
 * Release allocated memory
 */
void _alloc_deallocate(_alloc_t* pt_allocator, void* pv_allocmem, size_t t_size, size_t t_count)
{
    size_t t_allocsize = t_size * t_count; /* allocated memory size */

    assert(pt_allocator != NULL);
    assert(pv_allocmem != NULL);

    if (t_allocsize > _MEM_SMALL_MEM_SIZE_MAX) {
        _alloc_free(pv_allocmem);
    } else {
        ((_memlink_t*)pv_allocmem)->_pui_nextmem = pt_allocator->_apt_memlink[_MEM_LINK_INDEX(t_allocsize)];
        pt_allocator->_apt_memlink[_MEM_LINK_INDEX(t_allocsize)] = ((_memlink_t*)pv_allocmem);
    }
}

#ifndef NDEBUG
/**
 * Test alloc_t is initialized.
 */
bool_t _alloc_is_inited(const _alloc_t* cpt_allocator)
{
    size_t i = 0;

    assert(cpt_allocator != NULL);

    if (cpt_allocator->_t_mempoolsize != 0 || cpt_allocator->_t_mempoolindex != 0 || cpt_allocator->_pby_mempool != NULL) {
        return false;
    }

    for (i = 0; i < _MEM_LINK_COUNT; ++i) {
        if (cpt_allocator->_apt_memlink[i] != NULL) {
            return false;
        }
    }

    if (cpt_allocator->_t_mempoolcount != _MEM_POOL_DEFAULT_COUNT || cpt_allocator->_ppby_mempoolcontainer == NULL) {
        return false;
    }

    for (i = 0; i < cpt_allocator->_t_mempoolcount; ++i) {
        if (cpt_allocator->_ppby_mempoolcontainer[i] != NULL) {
            return false;
        }
    }

    return true;
}
#endif /* NDEBUG */

#else

/**
 * Initialize the _alloc_t.
 */
void _alloc_init(_alloc_t* pt_allocator)
{
    pt_allocator = NULL;
}

/**
 * Destroy the _alloc_t.
 */
void _alloc_destroy(_alloc_t* pt_allocator)
{
    pt_allocator = NULL;
}

/**
 * Allocate to user specified amount of memory.
 */
void* _alloc_allocate(_alloc_t* pt_allocator, size_t t_size, size_t t_count)
{
    /* total allocated memory size */
    size_t t_allocsize = t_size * t_count;

    pt_allocator = NULL;
    return _alloc_malloc(t_allocsize);
}

/**
 * Release allocated memory
 */
void _alloc_deallocate(_alloc_t* pt_allocator, void* pv_allocmem, size_t t_size, size_t t_count)
{
    assert(pv_allocmem != NULL);

    pt_allocator = NULL;
    t_size = 0;
    t_count = 0;
    _alloc_free(pv_allocmem);
}

#ifndef NDEBUG
/**
 * Test alloc_t is initialized.
 */
bool_t _alloc_is_inited(const _alloc_t* cpt_allocator)
{
    cpt_allocator = NULL;
    return true;
}
#endif /* NDEBUG */

#endif /* CSTL_MEMORY_MANAGEMENT */

/**
 * Set the out of memory handler and return the old handler.
 */
void (*_alloc_set_malloc_handler(void (*pfun_newhandler)(void)))(void)
{
    void (*pfun_oldhandler)(void) = _gpfun_malloc_handler;
    _gpfun_malloc_handler = pfun_newhandler;

    return pfun_oldhandler;
}

/** local function implementation section **/

/** eof **/

