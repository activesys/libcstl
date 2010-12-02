#ifndef _UT_CSTL_ALLOC_H
#define _UT_CSTL_ALLOC_H

UT_SUIT_DECLARATION(cstl_alloc)
/*
 * test _alloc_init
 */
UT_CASE_DECLARATION(_alloc_init)
void test__alloc_init__invalid_allocator(void** state);
void test__alloc_init__success(void** state);
/*
 * test _alloc_destroy
 */
UT_CASE_DECLARATION(_alloc_destroy)
void test__alloc_destroy__invalid_allocator(void** state);
void test__alloc_destroy__success(void** state);
void test__alloc_destroy__success_after_allocate(void** state);
/*
 * test _alloc_allocate
 */
UT_CASE_DECLARATION(_alloc_allocate)
void test__alloc_allocate__invalid_alocator(void** state);
void test__alloc_allocate__greater_than_max_small_memory(void** state);
void test__alloc_allocate__less_than_max_small_memory(void** state);
/*
 * test _alloc_deallocate
 */
UT_CASE_DECLARATION(_alloc_deallocate)
void test__alloc_deallocate__invalid_allocator(void** state);
void test__alloc_deallocate__invalid_allocated_memory(void** state);
void test__alloc_deallocate__greater_than_max_small_memory(void** state);
void test__alloc_deallocate__less_than_max_small_memory(void** state);
/*
 * test _alloc_set_malloc_handler
 */
UT_CASE_DECLARATION(_alloc_set_malloc_handler)
void test__alloc_set_malloc_handler___new_handler(void** state);
void test__alloc_set_malloc_handler___delete_handler(void** state);

#define UT_CSTL_ALLOC_CASE\
    UT_SUIT_BEGIN(cstl_alloc, test__alloc_init__invalid_allocator),\
    UT_CASE(test__alloc_init__success),\
    UT_CASE_BEGIN(_alloc_destroy, test__alloc_destroy__invalid_allocator),\
    UT_CASE(test__alloc_destroy__success),\
    UT_CASE(test__alloc_destroy__success_after_allocate),\
    UT_CASE_BEGIN(_alloc_allocate, test__alloc_allocate__invalid_alocator),\
    UT_CASE(test__alloc_allocate__greater_than_max_small_memory),\
    UT_CASE(test__alloc_allocate__less_than_max_small_memory),\
    UT_CASE_BEGIN(_alloc_deallocate, test__alloc_deallocate__invalid_allocator),\
    UT_CASE(test__alloc_deallocate__invalid_allocated_memory),\
    UT_CASE(test__alloc_deallocate__greater_than_max_small_memory),\
    UT_CASE(test__alloc_deallocate__less_than_max_small_memory),\
    UT_CASE_BEGIN(_alloc_set_malloc_handler, test__alloc_set_malloc_handler___new_handler),\
    UT_CASE(test__alloc_set_malloc_handler___delete_handler)

#endif /* _UT_CSTL_ALLOC_H */

