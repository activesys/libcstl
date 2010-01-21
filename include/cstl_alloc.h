/*
 *  The interface of memory management. 
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

#ifndef _CSTL_ALLOC_H
#define _CSTL_ALLOC_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
#ifndef _CSTL_USER_MODEL

#define _ALIGN                  8     /* boundary for small memory block */
#define _MAX_SMALL_MEM_SIZE     128   /* the maxinum size of small memory */
#define _MEM_LIST_COUNT         _MAX_SMALL_MEM_SIZE/_ALIGN
#define _MEM_BLOCK_COUNT        20    /* default block count getted from pool */
#define _MEM_POOL_DEFAULT_COUNT 4096  /* memory pool count */

/* round up the size of memory to the multiple of 8 */
#define _ROUND_UP(nmemsize)      (((nmemsize) + _ALIGN - 1) & ~(_ALIGN - 1))
/* get the memory list index with nmemsize */
#define _MEMLIST_INDEX(nmemsize) (((nmemsize) + _ALIGN - 1) / _ALIGN - 1)

#endif

/** data type declaration and struct, union, enum section **/
#ifdef _CSTL_USER_MODEL

typedef struct _tagalloc
{
}alloc_t;

#else

typedef union _tagmemlink
{
    union _tagmemlink* _pui_nextmem;  /* point to next memory block */
    char               _a_cmem[1];    /* represent memory block */
}_memlink_t;

typedef struct _tagalloc
{
    _memlink_t* _apt_memlink[_MEM_LIST_COUNT];   /* memory list */
    char**      _ppc_allocatemempool;            /* the allocated pool */
    char*       _pc_mempool;                     /* memory pool start */
    size_t      _t_mempoolsize;                  /* memory pool size */
    size_t      _n_mempoolindex;                 /* memory pool index */
    size_t      _t_mempoolcount;                 /* memory pool count */
}alloc_t;

#endif

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * Initialize the alloc_t.
 */
extern void allocate_init(alloc_t* pt_allocater);

/*
 * Destroy the alloc_t.
 */
extern void allocate_destroy(alloc_t* pt_allocater);

/*
 * Allocate memory for specify value type and specify element numbers use default
 * model or user model.
 */
extern void* allocate(alloc_t* pt_allocater, size_t t_typesize, int n_elemcount);

/*
 * Free memory for specify value type and specify element numbers use default 
 * model or user model.
 */
extern void deallocate(
    alloc_t* pt_allocater, void* pv_allocmem, size_t t_typesize, int n_elemcount);

/*
 * Set the out of memory handler and return the old handler.
 */
extern void (*set_malloc_handler(void (*pfun_newhandler)(void)))(void);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_ALLOC_H */
/** eof **/

