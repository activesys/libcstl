#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "ut_def.h"
#include "ut_cstl_alloc.h"

#include "cstl/cstl_def.h"
#include "cstl/cstl_alloc.h"
#include "cstl_alloc_aux.h"

UT_SUIT_DEFINATION(cstl_alloc, _alloc_init)

/*
 * test _alloc_init
 */
UT_CASE_DEFINATION(_alloc_init)
void test__alloc_init__invalid_allocator(void** state)
{
#ifdef CSTL_MEMORY_MANAGEMENT
    expect_assert_failure(_alloc_init(NULL));
#endif
}

void test__alloc_init__success(void** state)
{
#ifdef CSTL_MEMORY_MANAGEMENT
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
UT_CASE_DEFINATION(_alloc_destroy)
void test__alloc_destroy__invalid_allocator(void** state)
{
#ifdef CSTL_MEMORY_MANAGEMENT
    expect_assert_failure(_alloc_destroy(NULL));
#endif
}

void test__alloc_destroy__success(void** state)
{
#ifdef CSTL_MEMORY_MANAGEMENT
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
#ifdef CSTL_MEMORY_MANAGEMENT
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
            assert_true(allocator._apt_memlink[i] == (_memlink_t*)((_byte_t*)pv_mem + 8));
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
UT_CASE_DEFINATION(_alloc_allocate)
void test__alloc_allocate__invalid_alocator(void** state)
{
#ifdef CSTL_MEMORY_MANAGEMENT
    expect_assert_failure(_alloc_allocate(NULL, 8, 1));
#endif
}

void test__alloc_allocate__greater_than_max_small_memory(void** state)
{
#ifdef CSTL_MEMORY_MANAGEMENT
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
#ifdef CSTL_MEMORY_MANAGEMENT
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
            assert_true(allocator._apt_memlink[i] == (_memlink_t*)((_byte_t*)pv_mem + 8));
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
UT_CASE_DEFINATION(_alloc_deallocate)
void test__alloc_deallocate__invalid_allocator(void** state)
{
#ifdef CSTL_MEMORY_MANAGEMENT
    void* pv_mem = NULL;
    _alloc_t allocator;
    _alloc_init(&allocator);

    pv_mem = _alloc_allocate(&allocator, 8, 1);
    assert_true(pv_mem != NULL);

    expect_assert_failure(_alloc_deallocate(NULL, pv_mem, 8, 1));

    _alloc_destroy(&allocator);
#endif
}

void test__alloc_deallocate__invalid_allocated_memory(void** state)
{
#ifdef CSTL_MEMORY_MANAGEMENT
    _alloc_t allocator;
    _alloc_init(&allocator);

    expect_assert_failure(_alloc_deallocate(&allocator, NULL, 8, 1));

    _alloc_destroy(&allocator);
#else
    expect_assert_failure(_alloc_deallocate(NULL, NULL, 8, 1));
#endif
}

void test__alloc_deallocate__greater_than_max_small_memory(void** state)
{
#ifdef CSTL_MEMORY_MANAGEMENT
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
#ifdef CSTL_MEMORY_MANAGEMENT
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
            assert_true(allocator._apt_memlink[i] == (_memlink_t*)((_byte_t*)pv_mem + 8));
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
 * test _alloc_is_inited
 */
UT_CASE_DEFINATION(_alloc_is_inited)
void test__alloc_is_inited__null_allocator(void** state)
{
#ifdef CSTL_MEMORY_MANAGEMENT
    expect_assert_failure(_alloc_is_inited(NULL));
#else
    assert_true(_alloc_is_inited(NULL));
#endif
}

void test__alloc_is_inited__non_zero_mempoolsize(void** state)
{
#ifdef CSTL_MEMORY_MANAGEMENT
    _alloc_t t_allocator;
    size_t i = 0;

    t_allocator._t_mempoolsize = 10;
    t_allocator._t_mempoolindex = 0;
    t_allocator._pby_mempool = NULL;
    
    for(i = 0; i < _MEM_LINK_COUNT; ++i)
    {
        t_allocator._apt_memlink[i] = NULL;
    }

    /* initialize memory pool */
    t_allocator._t_mempoolcount = _MEM_POOL_DEFAULT_COUNT;
    t_allocator._ppby_mempoolcontainer = (_byte_t**)malloc(t_allocator._t_mempoolcount * sizeof(_byte_t*));
    if(t_allocator._ppby_mempoolcontainer != NULL)
    {
        for(i = 0; i < t_allocator._t_mempoolcount; ++i)
        {
            t_allocator._ppby_mempoolcontainer[i] = NULL;
        }
    }

    assert_false(_alloc_is_inited(&t_allocator));

    free(t_allocator._ppby_mempoolcontainer);
#endif
}

void test__alloc_is_inited__non_zero_mempoolindex(void** state)
{
#ifdef CSTL_MEMORY_MANAGEMENT
    _alloc_t t_allocator;
    size_t i = 0;

    t_allocator._t_mempoolsize = 0;
    t_allocator._t_mempoolindex = 10;
    t_allocator._pby_mempool = NULL;
    
    for(i = 0; i < _MEM_LINK_COUNT; ++i)
    {
        t_allocator._apt_memlink[i] = NULL;
    }

    /* initialize memory pool */
    t_allocator._t_mempoolcount = _MEM_POOL_DEFAULT_COUNT;
    t_allocator._ppby_mempoolcontainer = (_byte_t**)malloc(t_allocator._t_mempoolcount * sizeof(_byte_t*));
    if(t_allocator._ppby_mempoolcontainer != NULL)
    {
        for(i = 0; i < t_allocator._t_mempoolcount; ++i)
        {
            t_allocator._ppby_mempoolcontainer[i] = NULL;
        }
    }

    assert_false(_alloc_is_inited(&t_allocator));
    free(t_allocator._ppby_mempoolcontainer);
#endif
}

void test__alloc_is_inited__non_null_mempool(void** state)
{
#ifdef CSTL_MEMORY_MANAGEMENT
    _alloc_t t_allocator;
    size_t i = 0;

    t_allocator._t_mempoolsize = 0;
    t_allocator._t_mempoolindex = 0;
    t_allocator._pby_mempool = (_byte_t*)0xcc;
    
    for(i = 0; i < _MEM_LINK_COUNT; ++i)
    {
        t_allocator._apt_memlink[i] = NULL;
    }

    /* initialize memory pool */
    t_allocator._t_mempoolcount = _MEM_POOL_DEFAULT_COUNT;
    t_allocator._ppby_mempoolcontainer = (_byte_t**)malloc(t_allocator._t_mempoolcount * sizeof(_byte_t*));
    if(t_allocator._ppby_mempoolcontainer != NULL)
    {
        for(i = 0; i < t_allocator._t_mempoolcount; ++i)
        {
            t_allocator._ppby_mempoolcontainer[i] = NULL;
        }
    }

    assert_false(_alloc_is_inited(&t_allocator));
    free(t_allocator._ppby_mempoolcontainer);
#endif
}

void test__alloc_is_inited__non_empty_memlink(void** state)
{
#ifdef CSTL_MEMORY_MANAGEMENT
    _alloc_t t_allocator;
    size_t i = 0;

    t_allocator._t_mempoolsize = 0;
    t_allocator._t_mempoolindex = 0;
    t_allocator._pby_mempool = NULL;
    
    for(i = 0; i < _MEM_LINK_COUNT; ++i)
    {
        t_allocator._apt_memlink[i] = (_memlink_t*)0xcc;
    }

    /* initialize memory pool */
    t_allocator._t_mempoolcount = _MEM_POOL_DEFAULT_COUNT;
    t_allocator._ppby_mempoolcontainer = (_byte_t**)malloc(t_allocator._t_mempoolcount * sizeof(_byte_t*));
    if(t_allocator._ppby_mempoolcontainer != NULL)
    {
        for(i = 0; i < t_allocator._t_mempoolcount; ++i)
        {
            t_allocator._ppby_mempoolcontainer[i] = NULL;
        }
    }

    assert_false(_alloc_is_inited(&t_allocator));
    free(t_allocator._ppby_mempoolcontainer);
#endif
}

void test__alloc_is_inited__invalid_default_mempoolcount(void** state)
{
#ifdef CSTL_MEMORY_MANAGEMENT
    _alloc_t t_allocator;
    size_t i = 0;

    t_allocator._t_mempoolsize = 0;
    t_allocator._t_mempoolindex = 0;
    t_allocator._pby_mempool = NULL;
    
    for(i = 0; i < _MEM_LINK_COUNT; ++i)
    {
        t_allocator._apt_memlink[i] = NULL;
    }

    /* initialize memory pool */
    t_allocator._t_mempoolcount = 5;
    t_allocator._ppby_mempoolcontainer = (_byte_t**)malloc(t_allocator._t_mempoolcount * sizeof(_byte_t*));
    if(t_allocator._ppby_mempoolcontainer != NULL)
    {
        for(i = 0; i < t_allocator._t_mempoolcount; ++i)
        {
            t_allocator._ppby_mempoolcontainer[i] = NULL;
        }
    }

    assert_false(_alloc_is_inited(&t_allocator));
    free(t_allocator._ppby_mempoolcontainer);
#endif
}

void test__alloc_is_inited__null_mempoolcontainer(void** state)
{
#ifdef CSTL_MEMORY_MANAGEMENT
    _alloc_t t_allocator;
    size_t i = 0;

    t_allocator._t_mempoolsize = 0;
    t_allocator._t_mempoolindex = 0;
    t_allocator._pby_mempool = NULL;
    
    for(i = 0; i < _MEM_LINK_COUNT; ++i)
    {
        t_allocator._apt_memlink[i] = NULL;
    }

    /* initialize memory pool */
    t_allocator._t_mempoolcount = _MEM_POOL_DEFAULT_COUNT;
    t_allocator._ppby_mempoolcontainer = NULL;

    assert_false(_alloc_is_inited(&t_allocator));
#endif
}

void test__alloc_is_inited__non_empty_mempoolcontainer(void** state)
{
#ifdef CSTL_MEMORY_MANAGEMENT
    _alloc_t t_allocator;
    size_t i = 0;

    t_allocator._t_mempoolsize = 0;
    t_allocator._t_mempoolindex = 0;
    t_allocator._pby_mempool = NULL;
    
    for(i = 0; i < _MEM_LINK_COUNT; ++i)
    {
        t_allocator._apt_memlink[i] = NULL;
    }

    /* initialize memory pool */
    t_allocator._t_mempoolcount = _MEM_POOL_DEFAULT_COUNT;
    t_allocator._ppby_mempoolcontainer = (_byte_t**)malloc(t_allocator._t_mempoolcount * sizeof(_byte_t*));
    if(t_allocator._ppby_mempoolcontainer != NULL)
    {
        for(i = 0; i < t_allocator._t_mempoolcount; ++i)
        {
            t_allocator._ppby_mempoolcontainer[i] = (_byte_t*)0xcc;
        }
    }

    assert_false(_alloc_is_inited(&t_allocator));
    free(t_allocator._ppby_mempoolcontainer);
#endif
}

void test__alloc_is_inited__successfully(void** state)
{
#ifdef CSTL_MEMORY_MANAGEMENT
    _alloc_t t_allocator;
    _alloc_init(&t_allocator);

    assert_true(_alloc_is_inited(&t_allocator));

    _alloc_destroy(&t_allocator);
#endif
}

/*
 * test _alloc_set_malloc_handler
 */
UT_CASE_DEFINATION(_alloc_set_malloc_handler)
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

