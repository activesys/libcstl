/*
 *  The interface of memory management. 
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

#ifndef _CSTL_ALLOC_H_
#define _CSTL_ALLOC_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
#ifdef CSTL_MEMORY_MANAGEMENT

#define _MEM_ALIGNMENT              8     /* boundary for small memory block */
#define _MEM_SMALL_MEM_SIZE_MAX     128   /* the maxinum size of small memory */
#define _MEM_LINK_COUNT             _MEM_SMALL_MEM_SIZE_MAX/_MEM_ALIGNMENT
#define _MEM_CHUNK_COUNT            16    /* default chunk count getted from pool */
#define _MEM_POOL_DEFAULT_COUNT     16    /* memory pool count */

/* round up the size of memory to the multiple of 8 */
#define _MEM_ROUND_UP(memsize)      (((memsize) + _MEM_ALIGNMENT - 1) & ~(_MEM_ALIGNMENT - 1))
/* get the memory link index with memsize */
#define _MEM_LINK_INDEX(memsize)    (((memsize) + _MEM_ALIGNMENT - 1) / _MEM_ALIGNMENT - 1)

/** data type declaration and struct, union, enum section **/
typedef union _tagmemlink
{
    union _tagmemlink* _pui_nextmem;  /* point to next memory block */
    _byte_t            _pby_mem[1];    /* represent memory block */
}_memlink_t;

typedef struct _tagalloc
{
    _memlink_t* _apt_memlink[_MEM_LINK_COUNT];   /* memory list */
    _byte_t**   _ppby_mempoolcontainer;          /* memory pool container */
    _byte_t*    _pby_mempool;                    /* memory pool start */
    size_t      _t_mempoolsize;                  /* memory pool size */
    size_t      _t_mempoolindex;                 /* memory pool index */
    size_t      _t_mempoolcount;                 /* memory pool count */
}_alloc_t;

#else

typedef struct _tagalloc
{
    int n_avoid_vc_error_c2016;
}_alloc_t;

#endif /* CSTL_MEMORY_MANAGEMENT */

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Initialize the _alloc_t.
 * @param pt_allocator  pointer that points to allocator.
 * @return void.
 * @remarks if pt_allocator == NULL, then function of the behavior is undefined.
 */
extern void _alloc_init(_alloc_t* pt_allocator);

/**
 * Destroy the _alloc_t.
 * @param pt_allocator  pointer that points to allocator.
 * @return void.
 * @remarks if pt_allocator == NULL, then function of the behavior is undefined. if pt_allocator is not initialized by
 *          _alloc_init, then function of the behavior is undefined.
 */
extern void _alloc_destroy(_alloc_t* pt_allocator);

/**
 * Allocate to user specified amount of memory.
 * @param pt_allocator  pointer that points to allocator.
 * @param t_size        memory size.
 * @param t_count       memory count.
 * @return point to the allocated memory.
 * @remarks if pt_allocator == NULL, then function of the behavior is undefined. if allocator is not initialized by
 *          _alloc_init, then function of the behavior is undefined. the size of allocated memory is t_size * t_count.
 */
extern void* _alloc_allocate(_alloc_t* pt_allocator, size_t t_size, size_t t_count);

/**
 * Release allocated memory
 * @param pt_allocator  pointer that point to allocator.
 * @param pv_allocmem   pointer that point to allocated memory.
 * @param t_size        allocated memory size.
 * @param t_count       allocated memory count.
 * @return void.
 * @remarks if pt_allocator == NULL or pv_allocmem == NULL, then function of the behavior is undefined. if allocator is
 *          not initialized by _alloc_init, or pv_allocmem is not allocated by _alloc_allocate, then function of the
 *          behavior is undefined.
 */
extern void _alloc_deallocate(_alloc_t* pt_allocator, void* pv_allocmem, size_t t_size, size_t t_count);

#ifndef NDEBUG
/**
 * Test alloc_t is initialized.
 * @param cpt_allocator  allocator.
 * @return if allocator is initialized then return true, else return false.
 * @remarks if cpt_allocator == NULL then the behavior is undefined.
 */
extern bool_t _alloc_is_inited(const _alloc_t* cpt_allocator);
#endif /* NDEBUG */

/**
 * Set the out of memory handler and return the old handler.
 * @param pfun_newhandler  new out of memory handler.
 * @return old hanlder.
 * @remarks if pfun_newhandler == NULL, than delete the out of memory handler.
 */
extern void (*_alloc_set_malloc_handler(void (*pfun_newhandler)(void)))(void);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_ALLOC_H_ */
/** eof **/

