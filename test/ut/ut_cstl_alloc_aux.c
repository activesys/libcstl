#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include <stdlib.h>

#include "ut_cstl_alloc_aux.h"

#include "cstl/cstl_alloc.h"
#include "cstl_alloc_aux.h"

/*
 * test _alloc_get_memory_chunk
 */
void test__alloc_get_memory_chunk__invalid_allocater(void** state)
{
    size_t t_alloccount = 2;
    expect_assert_failure(_alloc_get_memory_chunk(NULL, 8, &t_alloccount));
}

void test__alloc_get_memory_chunk__invalid_alloccount(void** state)
{
    alloc_t allocater;
    expect_assert_failure(_alloc_get_memory_chunk(&allocater, 8, NULL));
}

void test__alloc_get_memory_chunk__total_size_less_than_memory_pool(void** state)
{
    size_t t_alloccount = 2;
    alloc_t allocater;
    char* pc_malloc = NULL;
    size_t t_old_size = 0;
    allocate_init(&allocater);

    allocater._t_mempoolsize = t_old_size = 64 * sizeof(char);
    allocater._pc_mempool = (char*)malloc(allocater._t_mempoolsize);
    allocater._ppc_allocatemempool[allocater._t_mempoolindex++] = allocater._pc_mempool;

    pc_malloc = _alloc_get_memory_chunk(&allocater, 8, &t_alloccount);

    assert_true(pc_malloc != NULL);
    assert_true(t_alloccount == 2);
    assert_true(pc_malloc == allocater._ppc_allocatemempool[0]);
    assert_true(allocater._t_mempoolsize == t_old_size - 2 * 8);
    assert_true(allocater._pc_mempool = allocater._ppc_allocatemempool[0] + 2 * 8);

    allocate_destroy(&allocater);
}

void test__alloc_get_memory_chunk__memory_pool_less_than_total_size_greater_than_one_size(void** state)
{
    size_t t_alloccount = 100;
    alloc_t allocater;
    char* pc_malloc = NULL;
    size_t t_old_size = 0;
    allocate_init(&allocater);

    allocater._t_mempoolsize = t_old_size = 64 * sizeof(char);
    allocater._pc_mempool = (char*)malloc(allocater._t_mempoolsize);
    allocater._ppc_allocatemempool[allocater._t_mempoolindex++] = allocater._pc_mempool;

    pc_malloc = _alloc_get_memory_chunk(&allocater, 8, &t_alloccount);

    assert_true(pc_malloc != NULL);
    assert_true(t_alloccount == 8);
    assert_true(pc_malloc == allocater._ppc_allocatemempool[0]);
    assert_true(allocater._t_mempoolsize == 0);
    assert_true(allocater._pc_mempool = allocater._ppc_allocatemempool[0] + t_old_size);

    allocate_destroy(&allocater);
}

void test__alloc_get_memory_chunk__memory_pool_size_equal_to_0(void** state)
{
    size_t t_alloccount = 10;
    alloc_t allocater;
    char* pc_malloc = NULL;
    allocate_init(&allocater);

    pc_malloc = _alloc_get_memory_chunk(&allocater, 8, &t_alloccount);

    assert_true(pc_malloc != NULL);
    assert_true(t_alloccount == 10);
    assert_true(pc_malloc == allocater._ppc_allocatemempool[0]);
    assert_true(allocater._t_mempoolsize == 80);
    assert_true(allocater._pc_mempool = allocater._ppc_allocatemempool[0] + t_alloccount * 8);

    allocate_destroy(&allocater);
}

void test__alloc_get_memory_chunk__memory_pool_size_less_then_one_allocated_chunk(void** state)
{
    size_t t_alloccount = 2;
    alloc_t allocater;
    char* pc_malloc = NULL;
    size_t t_old_size = 0;
    allocate_init(&allocater);

    allocater._t_mempoolsize = t_old_size = 8;
    allocater._pc_mempool = (char*)malloc(allocater._t_mempoolsize);
    allocater._ppc_allocatemempool[allocater._t_mempoolindex++] = allocater._pc_mempool;

    pc_malloc = _alloc_get_memory_chunk(&allocater, 16, &t_alloccount);

    assert_true(pc_malloc != NULL);
    assert_true(t_alloccount == 2);
    assert_true(pc_malloc == allocater._ppc_allocatemempool[1]);
    assert_true(allocater._t_mempoolsize == 32);
    assert_true(allocater._pc_mempool = allocater._ppc_allocatemempool[1] + 32);
    assert_true(allocater._ppc_allocatemempool[0] == (char*)allocater._apt_memlink[_MEMLIST_INDEX(t_old_size)]);

    allocate_destroy(&allocater);
}

void test__alloc_get_memory_chunk__reallocate_memory_pool_container(void** state)
{
    size_t t_alloccount = 2;
    alloc_t allocater;
    char* pc_malloc = NULL;
    size_t t_old_size = 0;
    allocate_init(&allocater);

    allocater._t_mempoolsize = t_old_size = 8;
    allocater._pc_mempool = (char*)malloc(allocater._t_mempoolsize);
    allocater._t_mempoolindex = _MEM_POOL_DEFAULT_COUNT - 1;
    allocater._ppc_allocatemempool[allocater._t_mempoolindex++] = allocater._pc_mempool;

    pc_malloc = _alloc_get_memory_chunk(&allocater, 16, &t_alloccount);

    assert_true(pc_malloc != NULL);
    assert_true(t_alloccount == 2);
    assert_true(pc_malloc == allocater._ppc_allocatemempool[_MEM_POOL_DEFAULT_COUNT]);
    assert_true(allocater._t_mempoolcount = 2 * _MEM_POOL_DEFAULT_COUNT);
    assert_true(allocater._t_mempoolsize == 32);
    assert_true(allocater._pc_mempool = allocater._ppc_allocatemempool[_MEM_POOL_DEFAULT_COUNT] + 32);
    assert_true(allocater._ppc_allocatemempool[_MEM_POOL_DEFAULT_COUNT - 1] == 
            (char*)allocater._apt_memlink[_MEMLIST_INDEX(t_old_size)]);

    allocate_destroy(&allocater);
}

/*
 * test _alloc_apply_formated_memory
 */
void test__alloc_apply_formated_memory__invalid_allocater(void** state)
{
    expect_assert_failure(_alloc_apply_formated_memory(NULL, 8));
}

void test__alloc_apply_formated_memory__success(void** state)
{
    alloc_t allocater;
    _memlink_t* pt_link = NULL;
    _memlink_t* pt_link_prev = NULL;
    allocate_init(&allocater);

    _alloc_apply_formated_memory(&allocater, 8);

    for(pt_link_prev = allocater._apt_memlink[_MEMLIST_INDEX(8)], pt_link = pt_link_prev->_pui_nextmem;
        pt_link != NULL; pt_link_prev = pt_link, pt_link = pt_link_prev->_pui_nextmem)
    {
        assert_true((char*)pt_link == (char*)pt_link_prev + 8);
    }
    assert_true((char*)allocater._pc_mempool == (char*)pt_link_prev + 8);

    allocate_destroy(&allocater);
}

/*
 * test _alloc_free
 */
void test__alloc_free__invalid_memory(void** state)
{
    expect_assert_failure(_alloc_free(NULL));
}

/*
 * test _alloc_malloc
 */
void test__alloc_malloc__success(void** state)
{
    void* pv_allocmem = _alloc_malloc(8);
    assert_true(pv_allocmem != NULL);
}

/*
 * test _alloc_malloc_out_of_memory
 */
static void malloc_handler(void){}

void test__alloc_malloc_out_of_memory__success(void** state)
{
    void* pv_allocmem = NULL;
    _g_pfun_default_malloc_handler = malloc_handler;

    pv_allocmem = _alloc_malloc_out_of_memory(8);
    assert_true(pv_allocmem != NULL);
}

