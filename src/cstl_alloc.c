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
#ifdef HAVE_CONFIG_H
#   include <config.h>
#endif
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

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
    
    return _alloc_malloc(t_allocsize);
}

void deallocate(
    alloc_t* /* pt_allocater */, void* pv_allocmem, 
    size_t /* t_typesize */, int /* n_elemcount */)
{
    assert(pv_allocmem != NULL);
    _alloc_free(pv_allocmem);
}

#else

void allocate_init(alloc_t* pt_allocater)
{
    int i = 0;

    assert(pt_allocater != NULL);

    pt_allocater->_t_mempoolsize = 0;
    pt_allocater->_t_mempoolindex = 0;
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
    pt_allocater->_t_mempoolindex = 0;
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
        pv_allocmem = _alloc_malloc(t_allocsize);
        assert(pv_allocmem);
    }
    else
    {
        pt_link = pt_allocater->_apt_memlink[_MEMLIST_INDEX(t_allocsize)];
        if(pt_link == NULL)
        {
            _alloc_apply_formated_memory(pt_allocater, _ROUND_UP(t_allocsize));
            pt_link = pt_allocater->_apt_memlink[_MEMLIST_INDEX(t_allocsize)];
            assert(pt_link);
        }
        pt_allocater->_apt_memlink[_MEMLIST_INDEX(t_allocsize)] = pt_link->_pui_nextmem;
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
        _alloc_free(pv_allocmem);
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
    void (*pfun_oldhandler)(void) = _g_pfun_default_malloc_handler;
    _g_pfun_default_malloc_handler = pfun_newhandler;

    return pfun_oldhandler;
}

/** local function implementation section **/

/** eof **/

