/*
 *  The implementation of memory management.
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

/** include section **/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "cstl_types.h"

#include "cstl_alloc.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/
/* oom : out of memory */
/*
 *  Functionname: _oom_malloc
 *    Parameters: in)t_memsize: size_t
 *                    the memory size for allocate.
 *       Returns: void*
 *   Description: malloc for out of memory condition.
 */
static void* _oom_malloc(size_t t_memsize);

/*
 *  Functionname: _malloc_allocate
 *    Parameters: in)t_memsize: size_t
 *                    the memory size for allocate.
 *       Returns: void*
 *   Description: malloc memory.
 */
static void* _malloc_allocate(size_t t_memsize);

/*
 *  Functionname: _free_deallocate
 *    Parameters: in)pv_allocmem: void*
 *                    the allocated memory.
 *       Returns: void
 *   Description: free memory.
 */
static void _free_deallocate(void* pv_allocmem);

/*
 *  Functionname: _apply_mem
 *    Parameters: in)pt_allocater: alloc_t*
 *                    manage memory struct pointer
 *                in)t_allocsize: size_t
 *                    the memory size for allocate.
 *       Returns: void
 *   Description: apply memory for memory pool and format the memory block, 
 *                then add it to the memory list.
 */
static void _apply_mem(alloc_t* pt_allocater, size_t t_allocsize);

/*
 *  Functionname: _get_mem_from_mempool
 *    Parameters: in)pt_allocater: alloc_t*
 *                    manage memory struct pointer
 *                in)t_allocsize: size_t
 *                    the memory size for allocate.
 *                modify)pn_alloccount: int*
 *                    the memory block count for allocated.
 *       Returns: char*
 *   Description: apply memory for memory pool.
 */
static char* _get_mem_from_mempool(
    alloc_t* pt_allocater, size_t t_allocsize, int* pn_alloccount);

/** exported global variable definition section **/

/** local global variable definition section **/
static void (*_g_pfun_defaultmallochandler)(void) = NULL;

/** exported function implementation section **/
#ifdef _CSTL_USER_MODEL

void allocate_init(alloc_t* /* pt_allocater */)
{
}

void allocate_destroy(alloc_t* /* pt_allocater */)
{
}

void* allocate(alloc_t* /* pt_allocater */, size_t t_typesize, int n_elemcount)
{
    /* total allocated memory size */
    size_t t_allocsize = t_typesize * n_elemcount;
    
    return _malloc_allocate(t_allocsize);
}

void deallocate(
    alloc_t* /* pt_allocater */, void* pv_allocmem, 
    size_t /* t_typesize */, int /* n_elemcount */)
{
    assert(pv_allocmem != NULL);
    _free_deallocate(pv_allocmem);
}

#else

void allocate_init(alloc_t* pt_allocater)
{
    int i = 0;

    assert(pt_allocater != NULL);

    pt_allocater->_t_mempoolsize = 0;
    pt_allocater->_n_mempoolindex = 0;
    pt_allocater->_pc_mempool = NULL;
    
    for(i = 0; i < _MEM_LIST_COUNT; ++i)
    {
        pt_allocater->_apt_memlink[i] = NULL;
    }

    /* initialize memory pool */
    pt_allocater->_t_mempoolcount = _MEM_POOL_DEFAULT_COUNT;
    pt_allocater->_ppc_allocatemempool = 
        (char**)malloc(pt_allocater->_t_mempoolcount * sizeof(char*));
    if(pt_allocater->_ppc_allocatemempool != NULL)
    {
        for(i = 0; i < (int)pt_allocater->_t_mempoolcount; ++i)
        {
            pt_allocater->_ppc_allocatemempool[i] = NULL;
        }
    }
    else
    {
        fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
}

void allocate_destroy(alloc_t* pt_allocater)
{
    int i = 0;

    assert(pt_allocater != NULL);

    /* destroy memory pool */
    for(i = 0; i < (int)pt_allocater->_t_mempoolcount; ++i)
    {
        free(pt_allocater->_ppc_allocatemempool[i]);
        pt_allocater->_ppc_allocatemempool[i] = NULL;
    }
    free(pt_allocater->_ppc_allocatemempool);
    pt_allocater->_ppc_allocatemempool = NULL;

    for(i = 0; i < _MEM_LIST_COUNT; ++i)
    {
        pt_allocater->_apt_memlink[i] = NULL;
    }

    pt_allocater->_pc_mempool = NULL;
    pt_allocater->_n_mempoolindex = 0;
    pt_allocater->_t_mempoolsize = 0;
    pt_allocater->_t_mempoolcount = 0;
}

void* allocate(alloc_t* pt_allocater, size_t t_typesize, int n_elemcount)
{
    void*       pv_allocmem = NULL;     /* allocated memory pointer */
    _memlink_t* pt_link = NULL;         /* memory link */
    size_t      t_allocsize = t_typesize * n_elemcount; 
                                        /* allocated memory size */

    assert(pt_allocater != NULL);

    if(t_allocsize > _MAX_SMALL_MEM_SIZE)
    {
        pv_allocmem = _malloc_allocate(t_allocsize);
        assert(pv_allocmem);
    }
    else
    {
        pt_link = pt_allocater->_apt_memlink[_MEMLIST_INDEX(t_allocsize)];
        if(pt_link == NULL)
        {
            _apply_mem(pt_allocater, _ROUND_UP(t_allocsize));
            pt_link = pt_allocater->_apt_memlink[_MEMLIST_INDEX(t_allocsize)];
            assert(pt_link);
        }
        pt_allocater->_apt_memlink[_MEMLIST_INDEX(t_allocsize)] = 
            pt_link->_pui_nextmem;
        pv_allocmem = (void*)pt_link;
    }

    return pv_allocmem;
}

void deallocate(
    alloc_t* pt_allocater, void* pv_allocmem, 
    size_t t_typesize, int n_elemcount)
{
    size_t t_allocsize = t_typesize * n_elemcount; /* allocated memory size */

    assert(pt_allocater != NULL);
    assert(pv_allocmem != NULL);

    if(t_allocsize > _MAX_SMALL_MEM_SIZE)
    {
        _free_deallocate(pv_allocmem);
    }
    else
    {
        ((_memlink_t*)pv_allocmem)->_pui_nextmem = 
            pt_allocater->_apt_memlink[_MEMLIST_INDEX(t_allocsize)];
        pt_allocater->_apt_memlink[_MEMLIST_INDEX(t_allocsize)] = 
            ((_memlink_t*)pv_allocmem);
    }
}

#endif

void (*set_malloc_handler(void (*pfun_newhandler)(void)))(void)
{
    void (*pfun_oldhandler)(void) = _g_pfun_defaultmallochandler;
    _g_pfun_defaultmallochandler = pfun_newhandler;

    return pfun_oldhandler;
}

/** local function implementation section **/
static void* _oom_malloc(size_t t_memsize)
{
    void* pv_allocmem = NULL;       /* point to allocated memory */

    for(;;)
    {
        if(_g_pfun_defaultmallochandler == NULL)
        {
            fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
            exit(EXIT_FAILURE);
            return NULL;
        }
        else
        {
            (*_g_pfun_defaultmallochandler)();
            if((pv_allocmem = malloc(t_memsize)) != NULL)
            {
                return pv_allocmem;
            }
        }
    }
}

static void* _malloc_allocate(size_t t_memsize)
{
    void*  pv_allocmem = NULL;      /* point to the allocated memory */
    
    if((pv_allocmem = malloc(t_memsize)) == NULL)
    {
        pv_allocmem = _oom_malloc(t_memsize);
        assert(pv_allocmem != NULL);
    }

    return pv_allocmem;
}

static void _free_deallocate(void* pv_allocmem)
{
    assert(pv_allocmem != NULL);
    free(pv_allocmem);
}

static void _apply_mem(alloc_t* pt_allocater, size_t t_allocsize)
{
    int         n_alloccount = _MEM_BLOCK_COUNT;
    _memlink_t* pt_link = NULL;
    int         i = 0;

    assert(pt_allocater);

    pt_link = (_memlink_t*)_get_mem_from_mempool(
                 pt_allocater, t_allocsize, &n_alloccount);
    assert(pt_link);

    /* format the apply memory block to memory list format */
    pt_allocater->_apt_memlink[_MEMLIST_INDEX(t_allocsize)] = pt_link;
    for(i = 0; i < n_alloccount; ++i)
    {
        if(i == n_alloccount - 1)
        {
            pt_link->_pui_nextmem = NULL;
        }
        else
        {
            pt_link->_pui_nextmem = 
                (_memlink_t*)((char*)pt_link + t_allocsize);
        }
        pt_link = pt_link->_pui_nextmem;
    }
}

static char* _get_mem_from_mempool(
    alloc_t* pt_allocater, size_t t_allocsize, int* pn_alloccount)
{
    size_t t_totalsize = 0;     /* total size of alloc */
    char*  pc_allocmem = NULL;  /* the allocated memory block */
    size_t t_getmemsize = 0;    /* bytes to get memory from system heap */
    int    i = 0;

    assert(pt_allocater);
    assert(pn_alloccount);

    t_totalsize = t_allocsize * (*pn_alloccount);

    if(pt_allocater->_t_mempoolsize >= t_totalsize)
    {
        pc_allocmem = pt_allocater->_pc_mempool;
        pt_allocater->_pc_mempool = pc_allocmem + t_totalsize;
        pt_allocater->_t_mempoolsize -= t_totalsize;
        
        return pc_allocmem;
    }
    else if(pt_allocater->_t_mempoolsize >= t_allocsize)
    {
        *pn_alloccount = pt_allocater->_t_mempoolsize / t_allocsize;
        t_totalsize = t_allocsize * (*pn_alloccount);

        pc_allocmem = pt_allocater->_pc_mempool;
        pt_allocater->_pc_mempool = pc_allocmem + t_totalsize;
        pt_allocater->_t_mempoolsize -= t_totalsize;

        return pc_allocmem;
    }
    else
    {
        /* if the memory pool conatiner is full */
        assert(pt_allocater->_n_mempoolindex <= pt_allocater->_t_mempoolcount);
        /* take the small memory block to the memory list */
        if(pt_allocater->_t_mempoolsize > 0)
        {
            ((_memlink_t*)pt_allocater->_pc_mempool)->_pui_nextmem = 
                pt_allocater->_apt_memlink[_MEMLIST_INDEX(
                    pt_allocater->_t_mempoolsize)];
            pt_allocater->_apt_memlink[_MEMLIST_INDEX(
                pt_allocater->_t_mempoolsize)] = 
                    (_memlink_t*)pt_allocater->_pc_mempool;
            pt_allocater->_t_mempoolsize = 0;
        }

        t_getmemsize = 2 * t_totalsize + 
            _ROUND_UP(pt_allocater->_t_mempoolsize >> 4);
        pt_allocater->_pc_mempool = (char*)malloc(t_getmemsize);

        if(pt_allocater->_pc_mempool == NULL)
        {
            /* search the memory list for unuse memory that meet the size */
            for(i = t_allocsize; i < _MAX_SMALL_MEM_SIZE; i += _ALIGN)
            {
                pt_allocater->_pc_mempool = 
                    (char*)pt_allocater->_apt_memlink[_MEMLIST_INDEX(i)];
                if(pt_allocater->_pc_mempool != NULL)
                {
                    pt_allocater->_apt_memlink[_MEMLIST_INDEX(i)] = 
                        ((_memlink_t*)pt_allocater->_pc_mempool)->_pui_nextmem;
                    pt_allocater->_t_mempoolsize = (size_t)i;

                    return _get_mem_from_mempool(
                            pt_allocater, t_allocsize, pn_alloccount);
                }
            }
            pt_allocater->_pc_mempool = (char*)_oom_malloc(t_getmemsize);
        }

        /* if the memory pool container is full */
        if(pt_allocater->_n_mempoolindex == pt_allocater->_t_mempoolcount)
        {
            char** ppc_oldmempool = pt_allocater->_ppc_allocatemempool;

            pt_allocater->_t_mempoolcount += _MEM_POOL_DEFAULT_COUNT;
            pt_allocater->_ppc_allocatemempool = 
                (char**)malloc(pt_allocater->_t_mempoolcount * sizeof(char*));
            if(pt_allocater->_ppc_allocatemempool != NULL)
            {
                int i = 0;
                for(i = 0; i < (int)pt_allocater->_t_mempoolcount; ++i)
                {
                    pt_allocater->_ppc_allocatemempool[i] = NULL;
                }
                memcpy(
                    pt_allocater->_ppc_allocatemempool,
                    ppc_oldmempool,
                    pt_allocater->_t_mempoolcount - _MEM_POOL_DEFAULT_COUNT);
                free(ppc_oldmempool);
                assert(
                    pt_allocater->_n_mempoolindex < 
                    pt_allocater->_t_mempoolcount);
            }
            else
            {
                fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
                exit(EXIT_FAILURE);
            }
        }
        pt_allocater->_ppc_allocatemempool[
            pt_allocater->_n_mempoolindex++] = pt_allocater->_pc_mempool;

        /* apply memory from system heap success or call _oom_malloc success */
        pt_allocater->_t_mempoolsize = t_getmemsize;

        pc_allocmem = pt_allocater->_pc_mempool;
        pt_allocater->_pc_mempool = pc_allocmem + t_totalsize;
        pt_allocater->_t_mempoolsize -= t_totalsize;

        return pc_allocmem;
    }
}

/** eof **/

