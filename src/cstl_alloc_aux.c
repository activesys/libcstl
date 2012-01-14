/*
 *  The implementation of memory management auxiliary.
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
void (*_gpfun_malloc_handler)(void) = NULL;

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Malloc for out of memory condition.
 */
void* _alloc_malloc_out_of_memory(size_t t_memsize)
{
    void* pv_allocmem = NULL;       /* point to allocated memory */

    for (;;) {
        if (_gpfun_malloc_handler == NULL) {
            fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
            exit(EXIT_FAILURE);
            return NULL;
        } else {
            (*_gpfun_malloc_handler)();
            if ((pv_allocmem = malloc(t_memsize)) != NULL) {
                return pv_allocmem;
            }
        }
    }
}

/**
 * Malloc memory.
 */
void* _alloc_malloc(size_t t_memsize)
{
    void*  pv_allocmem = NULL;      /* point to the allocated memory */
    
    if ((pv_allocmem = malloc(t_memsize)) == NULL) {
        pv_allocmem = _alloc_malloc_out_of_memory(t_memsize);
        assert(pv_allocmem != NULL);
    }

    return pv_allocmem;
}

/**
 * Free memory.
 */
void _alloc_free(void* pv_allocmem)
{
    assert(pv_allocmem != NULL);
    free(pv_allocmem);
}

#ifdef CSTL_MEMORY_MANAGEMENT
/**
 * Apply a formated memory list.
 */
void _alloc_apply_formated_memory(_alloc_t* pt_allocator, size_t t_allocsize)
{
    size_t      t_alloccount = _MEM_CHUNK_COUNT;
    _memlink_t* pt_link = NULL;
    size_t      i = 0;

    assert(pt_allocator != NULL);

    pt_link = (_memlink_t*)_alloc_get_memory_chunk(pt_allocator, t_allocsize, &t_alloccount);
    assert(pt_link != NULL);

    /* format the apply memory block to memory list format */
    pt_allocator->_apt_memlink[_MEM_LINK_INDEX(t_allocsize)] = pt_link;
    for (i = 0; i < t_alloccount; ++i) {
        if (i == t_alloccount - 1) {
            pt_link->_pui_nextmem = NULL;
        } else {
            pt_link->_pui_nextmem = (_memlink_t*)((_byte_t*)pt_link + t_allocsize);
        }
        pt_link = pt_link->_pui_nextmem;
    }
}

/**
 * Get memory chunk from memory pool.
 */
_byte_t* _alloc_get_memory_chunk(_alloc_t* pt_allocator, size_t t_allocsize, size_t* pt_alloccount)
{
    size_t    t_totalsize = 0;     /* total size of alloc */
    _byte_t*  pby_allocmem = NULL;  /* the allocated memory block */
    size_t    t_getmemsize = 0;    /* bytes to get memory from system heap */
    size_t    i = 0;

    assert(pt_allocator != NULL);
    assert(pt_alloccount != NULL);

    t_totalsize = t_allocsize * (*pt_alloccount);

    if (pt_allocator->_t_mempoolsize >= t_totalsize) {
        pby_allocmem = pt_allocator->_pby_mempool;
        pt_allocator->_pby_mempool = pby_allocmem + t_totalsize;
        pt_allocator->_t_mempoolsize -= t_totalsize;
        
        return pby_allocmem;
    } else if (pt_allocator->_t_mempoolsize >= t_allocsize) {
        *pt_alloccount = pt_allocator->_t_mempoolsize / t_allocsize;
        t_totalsize = t_allocsize * (*pt_alloccount);

        pby_allocmem = pt_allocator->_pby_mempool;
        pt_allocator->_pby_mempool = pby_allocmem + t_totalsize;
        pt_allocator->_t_mempoolsize -= t_totalsize;

        return pby_allocmem;
    } else {
        /* if the memory pool conatiner is full */
        assert(pt_allocator->_t_mempoolindex <= pt_allocator->_t_mempoolcount);
        /* take the small memory block to the memory list */
        if (pt_allocator->_t_mempoolsize > 0) {
            ((_memlink_t*)pt_allocator->_pby_mempool)->_pui_nextmem = 
                pt_allocator->_apt_memlink[_MEM_LINK_INDEX(pt_allocator->_t_mempoolsize)];
            pt_allocator->_apt_memlink[_MEM_LINK_INDEX(pt_allocator->_t_mempoolsize)] =
                (_memlink_t*)pt_allocator->_pby_mempool;
            pt_allocator->_t_mempoolsize = 0;
        }

        t_getmemsize = 2 * t_totalsize;
        pt_allocator->_pby_mempool = (_byte_t*)malloc(t_getmemsize);

        if (pt_allocator->_pby_mempool == NULL) {
            /* search the memory list for unuse memory that meet the size */
            for (i = t_allocsize; i < _MEM_SMALL_MEM_SIZE_MAX; i += _MEM_ALIGNMENT) {
                pt_allocator->_pby_mempool = (_byte_t*)pt_allocator->_apt_memlink[_MEM_LINK_INDEX(i)];
                if (pt_allocator->_pby_mempool != NULL) {
                    pt_allocator->_apt_memlink[_MEM_LINK_INDEX(i)] = ((_memlink_t*)pt_allocator->_pby_mempool)->_pui_nextmem;
                    pt_allocator->_t_mempoolsize = i;

                    return _alloc_get_memory_chunk(pt_allocator, t_allocsize, pt_alloccount);
                }
            }
            pt_allocator->_pby_mempool = (_byte_t*)_alloc_malloc_out_of_memory(t_getmemsize);
        }

        /* if the memory pool container is full */
        if (pt_allocator->_t_mempoolindex == pt_allocator->_t_mempoolcount) {
            _byte_t** ppby_oldmempool = pt_allocator->_ppby_mempoolcontainer;

            pt_allocator->_t_mempoolcount += _MEM_POOL_DEFAULT_COUNT;
            pt_allocator->_ppby_mempoolcontainer = (_byte_t**)malloc(pt_allocator->_t_mempoolcount * sizeof(_byte_t*));
            if (pt_allocator->_ppby_mempoolcontainer != NULL) {
                for (i = 0; i < pt_allocator->_t_mempoolcount; ++i) {
                    pt_allocator->_ppby_mempoolcontainer[i] = NULL;
                }
                memcpy(pt_allocator->_ppby_mempoolcontainer, ppby_oldmempool,
                    (pt_allocator->_t_mempoolcount - _MEM_POOL_DEFAULT_COUNT) * sizeof(_byte_t*));
                free(ppby_oldmempool);
                assert(pt_allocator->_t_mempoolindex < pt_allocator->_t_mempoolcount);
            } else {
                fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
                exit(EXIT_FAILURE);
            }
        }
        pt_allocator->_ppby_mempoolcontainer[pt_allocator->_t_mempoolindex++] = pt_allocator->_pby_mempool;

        /* apply memory from system heap success or call _alloc_malloc_out_of_memory success */
        pt_allocator->_t_mempoolsize = t_getmemsize;

        pby_allocmem = pt_allocator->_pby_mempool;
        pt_allocator->_pby_mempool = pby_allocmem + t_totalsize;
        pt_allocator->_t_mempoolsize -= t_totalsize;

        return pby_allocmem;
    }
}

#endif /* CSTL_MEMORY_MANAGEMENT */

/** local function implementation section **/

/** eof **/

