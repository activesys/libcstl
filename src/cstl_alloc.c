/*
 *  The implementation of memory management.
 *  Copyright (C)  2008,2009,2010  Wangbo
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
#ifdef _CSTL_USER_MODEL

/**
 * Initialize the alloc_t.
 */
void _alloc_init(alloc_t* pt_allocator)
{
    pt_allocator = NULL;
}

/**
 * Destroy the alloc_t.
 */
void _alloc_destroy(alloc_t* pt_allocator)
{
    pt_allocator = NULL;
}

/**
 * Allocate to user specified amount of memory.
 */
void* _alloc_allocate(alloc_t* pt_allocator, size_t t_size, size_t t_count)
{
    /* total allocated memory size */
    size_t t_allocsize = t_size * t_count;

    pt_allocator = NULL;
    return _alloc_malloc(t_allocsize);
}

/**
 * Release allocated memory
 */
void _alloc_deallocate(alloc_t* pt_allocator, void* pv_allocmem, size_t t_size, size_t t_count)
{
    assert(pv_allocmem != NULL);

    pt_allocator = NULL;
    t_size = 0;
    t_count = 0;
    _alloc_free(pv_allocmem);
}

#else

/**
 * Initialize the alloc_t.
 */
void _alloc_init(alloc_t* pt_allocator)
{
    size_t i = 0;

    assert(pt_allocator != NULL);

    pt_allocator->_t_mempoolsize = 0;
    pt_allocator->_t_mempoolindex = 0;
    pt_allocator->_pc_mempool = NULL;
    
    for(i = 0; i < _MEM_LIST_COUNT; ++i)
    {
        pt_allocator->_apt_memlink[i] = NULL;
    }

    /* initialize memory pool */
    pt_allocator->_t_mempoolcount = _MEM_POOL_DEFAULT_COUNT;
    pt_allocator->_ppc_allocatemempool = (char**)malloc(pt_allocator->_t_mempoolcount * sizeof(char*));
    if(pt_allocator->_ppc_allocatemempool != NULL)
    {
        for(i = 0; i < pt_allocator->_t_mempoolcount; ++i)
        {
            pt_allocator->_ppc_allocatemempool[i] = NULL;
        }
    }
    else
    {
        fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
}

/**
 * Destroy the alloc_t.
 */
void _alloc_destroy(alloc_t* pt_allocator)
{
    size_t i = 0;

    assert(pt_allocator != NULL);

    /* destroy memory pool */
    for(i = 0; i < pt_allocator->_t_mempoolcount; ++i)
    {
        free(pt_allocator->_ppc_allocatemempool[i]);
        pt_allocator->_ppc_allocatemempool[i] = NULL;
    }
    free(pt_allocator->_ppc_allocatemempool);
    pt_allocator->_ppc_allocatemempool = NULL;

    for(i = 0; i < _MEM_LIST_COUNT; ++i)
    {
        pt_allocator->_apt_memlink[i] = NULL;
    }

    pt_allocator->_pc_mempool = NULL;
    pt_allocator->_t_mempoolindex = 0;
    pt_allocator->_t_mempoolsize = 0;
    pt_allocator->_t_mempoolcount = 0;
}

/**
 * Allocate to user specified amount of memory.
 */
void* _alloc_allocate(alloc_t* pt_allocator, size_t t_size, size_t t_count)
{
    void*       pv_allocmem = NULL;               /* allocated memory pointer */
    _memlink_t* pt_link = NULL;                   /* memory link */
    size_t      t_allocsize = t_size * t_count;   /* allocated memory size */

    assert(pt_allocator != NULL);

    if(t_allocsize > _MAX_SMALL_MEM_SIZE)
    {
        pv_allocmem = _alloc_malloc(t_allocsize);
        assert(pv_allocmem);
    }
    else
    {
        pt_link = pt_allocator->_apt_memlink[_MEMLIST_INDEX(t_allocsize)];
        if(pt_link == NULL)
        {
            _alloc_apply_formated_memory(pt_allocator, _ROUND_UP(t_allocsize));
            pt_link = pt_allocator->_apt_memlink[_MEMLIST_INDEX(t_allocsize)];
            assert(pt_link);
        }
        pt_allocator->_apt_memlink[_MEMLIST_INDEX(t_allocsize)] = pt_link->_pui_nextmem;
        pv_allocmem = (void*)pt_link;
    }

    return pv_allocmem;
}

/**
 * Release allocated memory
 */
void _alloc_deallocate(alloc_t* pt_allocator, void* pv_allocmem, size_t t_size, size_t t_count)
{
    size_t t_allocsize = t_size * t_count; /* allocated memory size */

    assert(pt_allocator != NULL);
    assert(pv_allocmem != NULL);

    if(t_allocsize > _MAX_SMALL_MEM_SIZE)
    {
        _alloc_free(pv_allocmem);
    }
    else
    {
        ((_memlink_t*)pv_allocmem)->_pui_nextmem = pt_allocator->_apt_memlink[_MEMLIST_INDEX(t_allocsize)];
        pt_allocator->_apt_memlink[_MEMLIST_INDEX(t_allocsize)] = ((_memlink_t*)pv_allocmem);
    }
}

#endif

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

