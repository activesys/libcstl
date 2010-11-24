#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "ut_cstl_alloc.h"

#include "cstl/cstl_def.h"
#include "cstl/cstl_alloc.h"
#include "cstl_alloc_aux.h"

/*
 * test _alloc_init
 */
void test__alloc_init__invalid_allocator(void** state)
{
#ifndef _CSTL_USER_MODEL
    expect_assert_failure(_alloc_init(NULL));
#endif
}

void test__alloc_init__success(void** state)
{
#ifndef _CSTL_USER_MODEL
    size_t i = 0;
    _alloc_t allocator;
    _alloc_init(&allocator);

    assert_true(allocator._pby_mempool == NULL);
    assert_true(allocator._t_mempoolsize == 0);
    assert_true(allocator._t_mempoolindex == 0);
    assert_true(allocator._t_mempoolcount == _MEM_POOL_DEFAULT_COUNT);
    for(i = 0; i < _MEM_LINK_COUNT; ++i)
    {
        assert_true(allocator._apt_memlink[i] == NULL);
    }
    assert_true(allocator._ppby_mempoolcontainer != NULL);
    for(i = 0; i < allocator._t_mempoolcount; ++i)
    {
        assert_true(allocator._ppby_mempoolcontainer[i] == NULL);
    }
#endif
}

/*
 * test _alloc_destroy
 */
void test__alloc_destroy__invalid_allocator(void** state)
{
#ifndef _CSTL_USER_MODEL
    expect_assert_failure(_alloc_destroy(NULL));
#endif
}

void test__alloc_destroy__success(void** state)
{
#ifndef _CSTL_USER_MODEL
    size_t i = 0;
    _alloc_t allocator;
    _alloc_init(&allocator);

    assert_true(allocator._pby_mempool == NULL);
    assert_true(allocator._t_mempoolsize == 0);
    assert_true(allocator._t_mempoolindex == 0);
    assert_true(allocator._t_mempoolcount == _MEM_POOL_DEFAULT_COUNT);
    for(i = 0; i < _MEM_LINK_COUNT; ++i)
    {
        assert_true(allocator._apt_memlink[i] == NULL);
    }
    assert_true(allocator._ppby_mempoolcontainer != NULL);
    for(i = 0; i < allocator._t_mempoolcount; ++i)
    {
        assert_true(allocator._ppby_mempoolcontainer[i] == NULL);
    }

    _alloc_destroy(&allocator);
    assert_true(allocator._pby_mempool == NULL);
    assert_true(allocator._t_mempoolsize == 0);
    assert_true(allocator._t_mempoolindex == 0);
    assert_true(allocator._t_mempoolcount == 0);
    for(i = 0; i < _MEM_LINK_COUNT; ++i)
    {
        assert_true(allocator._apt_memlink[i] == NULL);
    }
    assert_true(allocator._ppby_mempoolcontainer == NULL);
#endif
}

void test__alloc_destroy__success_after_allocate(void** state)
{
#ifndef _CSTL_USER_MODEL
    size_t i = 0;
    void* pv_mem = NULL;
    _alloc_t allocator;
    _alloc_init(&allocator);
    pv_mem = _alloc_allocate(&allocator, 8, 1);

    assert_true(pv_mem != NULL);
    assert_true(allocator._pby_mempool == allocator._ppby_mempoolcontainer[0] + 128);
    assert_true(allocator._t_mempoolsize == 128);
    assert_true(allocator._t_mempoolindex == 1);
    assert_true(allocator._t_mempoolcount == _MEM_POOL_DEFAULT_COUNT);
    assert_true(allocator._ppby_mempoolcontainer[0] == pv_mem);
    for(i = 0; i < _MEM_LINK_COUNT; ++i)
    {
        if(i == _MEM_LINK_INDEX(8))
        {
            assert_true(allocator._apt_memlink[i] == pv_mem + 8);
        }
        else
        {
            assert_true(allocator._apt_memlink[i] == NULL);
        }
    }
    assert_true(allocator._ppby_mempoolcontainer != NULL);
    for(i = allocator._t_mempoolindex; i < allocator._t_mempoolcount; ++i)
    {
        assert_true(allocator._ppby_mempoolcontainer[i] == NULL);
    }

    _alloc_destroy(&allocator);
    assert_true(allocator._pby_mempool == NULL);
    assert_true(allocator._t_mempoolsize == 0);
    assert_true(allocator._t_mempoolindex == 0);
    assert_true(allocator._t_mempoolcount == 0);
    for(i = 0; i < _MEM_LINK_COUNT; ++i)
    {
        assert_true(allocator._apt_memlink[i] == NULL);
    }
    assert_true(allocator._ppby_mempoolcontainer == NULL);
#endif
}

/*
 * test allocate
 */
void test__alloc_allocate__invalid_alocator(void** state)
{
#ifndef _CSTL_USER_MODEL
    expect_assert_failure(_alloc_allocate(NULL, 8, 1));
#endif
}

void test__alloc_allocate__greater_than_max_small_memory(void** state)
{
#ifndef _CSTL_USER_MODEL
    size_t i = 0;
    void* pv_mem = NULL;
    _alloc_t allocator;
    _alloc_init(&allocator);

    pv_mem = _alloc_allocate(&allocator, _MEM_SMALL_MEM_SIZE_MAX, 2);

    assert_true(pv_mem != NULL);
    assert_true(allocator._pby_mempool == NULL);
    assert_true(allocator._t_mempoolsize == 0);
    assert_true(allocator._t_mempoolindex == 0);
    assert_true(allocator._t_mempoolcount == _MEM_POOL_DEFAULT_COUNT);
    for(i = 0; i < _MEM_LINK_COUNT; ++i)
    {
        assert_true(allocator._apt_memlink[i] == NULL);
    }
    assert_true(allocator._ppby_mempoolcontainer != NULL);
    for(i = 0; i < allocator._t_mempoolcount; ++i)
    {
        assert_true(allocator._ppby_mempoolcontainer[i] == NULL);
    }

    _alloc_destroy(&allocator);
#else
    void* pv_mem = _alloc_allocate(NULL, 128, 2);
    assert_true(pv_mem != NULL);
    _alloc_deallocate(NULL, pv_mem, 128, 2);
#endif
}

void test__alloc_allocate__less_than_max_small_memory(void** state)
{
#ifndef _CSTL_USER_MODEL
    size_t i = 0;
    void* pv_mem = NULL;
    _alloc_t allocator;
    _alloc_init(&allocator);
    pv_mem = _alloc_allocate(&allocator, 8, 1);

    assert_true(allocator._pby_mempool == allocator._ppby_mempoolcontainer[0] + 128);
    assert_true(allocator._t_mempoolsize == 128);
    assert_true(allocator._t_mempoolindex == 1);
    assert_true(allocator._t_mempoolcount == _MEM_POOL_DEFAULT_COUNT);
    assert_true(allocator._ppby_mempoolcontainer[0] == pv_mem);
    for(i = 0; i < _MEM_LINK_COUNT; ++i)
    {
        if(i == _MEM_LINK_INDEX(8))
        {
            assert_true(allocator._apt_memlink[i] == pv_mem + 8);
        }
        else
        {
            assert_true(allocator._apt_memlink[i] == NULL);
        }
    }
    assert_true(allocator._ppby_mempoolcontainer != NULL);

    _alloc_destroy(&allocator);
#else
    void* pv_mem = _alloc_allocate(NULL, 8, 1);
    assert_true(pv_mem != NULL);
    _alloc_deallocate(NULL, pv_mem, 8, 1);
#endif
}

/*
 * test _alloc_deallocate
 */
void test__alloc_deallocate__invalid_allocator(void** state)
{
#ifndef _CSTL_USER_MODEL
    void* pv_mem = NULL;
    _alloc_t allocater;
    _alloc_init(&allocater);

    pv_mem = _alloc_allocate(&allocater, 8, 1);
    assert_true(pv_mem != NULL);

    expect_assert_failure(_alloc_deallocate(NULL, pv_mem, 8, 1));

    _alloc_destroy(&allocater);
#endif
}

void test__alloc_deallocate__invalid_allocated_memory(void** state)
{
#ifndef _CSTL_USER_MODEL
    _alloc_t allocater;
    _alloc_init(&allocater);

    expect_assert_failure(_alloc_deallocate(&allocater, NULL, 8, 1));

    _alloc_destroy(&allocater);
#else
    expect_assert_failure(_alloc_deallocate(NULL, NULL, 8, 1));
#endif
}

void test__alloc_deallocate__greater_than_max_small_memory(void** state)
{
#ifndef _CSTL_USER_MODEL
    size_t i = 0;
    void* pv_mem = NULL;
    _alloc_t allocator;
    _alloc_init(&allocator);

    pv_mem = _alloc_allocate(&allocator, _MEM_SMALL_MEM_SIZE_MAX, 2);

    assert_true(pv_mem != NULL);
    assert_true(allocator._pby_mempool == NULL);
    assert_true(allocator._t_mempoolsize == 0);
    assert_true(allocator._t_mempoolindex == 0);
    assert_true(allocator._t_mempoolcount == _MEM_POOL_DEFAULT_COUNT);
    for(i = 0; i < _MEM_LINK_COUNT; ++i)
    {
        assert_true(allocator._apt_memlink[i] == NULL);
    }
    assert_true(allocator._ppby_mempoolcontainer != NULL);
    for(i = 0; i < allocator._t_mempoolcount; ++i)
    {
        assert_true(allocator._ppby_mempoolcontainer[i] == NULL);
    }

    _alloc_deallocate(&allocator, pv_mem, _MEM_SMALL_MEM_SIZE_MAX, 2);

    assert_true(allocator._pby_mempool == NULL);
    assert_true(allocator._t_mempoolsize == 0);
    assert_true(allocator._t_mempoolindex == 0);
    assert_true(allocator._t_mempoolcount == _MEM_POOL_DEFAULT_COUNT);
    for(i = 0; i < _MEM_LINK_COUNT; ++i)
    {
        assert_true(allocator._apt_memlink[i] == NULL);
    }
    assert_true(allocator._ppby_mempoolcontainer != NULL);
    for(i = 0; i < allocator._t_mempoolcount; ++i)
    {
        assert_true(allocator._ppby_mempoolcontainer[i] == NULL);
    }

    _alloc_destroy(&allocator);
#else
    void* pv_mem = _alloc_allocate(NULL, 128, 2);
    assert_true(pv_mem != NULL);
    _alloc_deallocate(NULL, pv_mem, 128, 2);
#endif
}

void test__alloc_deallocate__less_than_max_small_memory(void** state)
{
#ifndef _CSTL_USER_MODEL
    size_t i = 0;
    void* pv_mem = NULL;
    _alloc_t allocator;
    _alloc_init(&allocator);
    pv_mem = _alloc_allocate(&allocator, 8, 1);

    assert_true(allocator._pby_mempool == allocator._ppby_mempoolcontainer[0] + 128);
    assert_true(allocator._t_mempoolsize == 128);
    assert_true(allocator._t_mempoolindex == 1);
    assert_true(allocator._t_mempoolcount == _MEM_POOL_DEFAULT_COUNT);
    assert_true(allocator._ppby_mempoolcontainer[0] == pv_mem);
    for(i = 0; i < _MEM_LINK_COUNT; ++i)
    {
        if(i == _MEM_LINK_INDEX(8))
        {
            assert_true(allocator._apt_memlink[i] == pv_mem + 8);
        }
        else
        {
            assert_true(allocator._apt_memlink[i] == NULL);
        }
    }
    assert_true(allocator._ppby_mempoolcontainer != NULL);

    _alloc_deallocate(&allocator, pv_mem, 8, 1);

    assert_true(allocator._pby_mempool == allocator._ppby_mempoolcontainer[0] + 128);
    assert_true(allocator._t_mempoolsize == 128);
    assert_true(allocator._t_mempoolindex == 1);
    assert_true(allocator._t_mempoolcount == _MEM_POOL_DEFAULT_COUNT);
    assert_true(allocator._ppby_mempoolcontainer[0] == (_byte_t*)allocator._apt_memlink[_MEM_LINK_INDEX(8)]);
    for(i = 0; i < _MEM_LINK_COUNT; ++i)
    {
        if(i == _MEM_LINK_INDEX(8))
        {
            assert_true((_byte_t*)allocator._apt_memlink[i] == allocator._ppby_mempoolcontainer[0]);
        }
        else
        {
            assert_true(allocator._apt_memlink[i] == NULL);
        }
    }
    assert_true(allocator._ppby_mempoolcontainer != NULL);

    _alloc_destroy(&allocator);
#else
    void* pv_mem = _alloc_allocate(NULL, 8, 1);
    assert_true(pv_mem != NULL);
    _alloc_deallocate(NULL, pv_mem, 8, 1);
#endif
}

/*
 * test _alloc_set_malloc_handler
 */
static void new_handler(void){}
void test__alloc_set_malloc_handler___new_handler(void** state)
{
    void (*pfun_old)(void) = NULL;
    _gpfun_malloc_handler = NULL;
    pfun_old = _alloc_set_malloc_handler(new_handler);
    assert_true(pfun_old == NULL);
    assert_true(_gpfun_malloc_handler == new_handler);
}

void test__alloc_set_malloc_handler___delete_handler(void** state)
{
    void (*pfun_old)(void) = NULL;
    _gpfun_malloc_handler = new_handler;

    pfun_old = _alloc_set_malloc_handler(NULL);
    assert_true(pfun_old == new_handler);
    assert_true(_gpfun_malloc_handler == NULL);
}

