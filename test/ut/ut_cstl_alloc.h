#ifndef _UT_CSTL_ALLOC_H
#define _UT_CSTL_ALLOC_H

UT_CASE_DECLARATION(cstl_alloc)
/*
 * test _alloc_init
 */
UT_ITEM_DECLARATION(_alloc_init)
void test__alloc_init__invalid_allocator(void** state);
void test__alloc_init__success(void** state);
/*
 * test _alloc_destroy
 */
UT_ITEM_DECLARATION(_alloc_destroy)
void test__alloc_destroy__invalid_allocator(void** state);
void test__alloc_destroy__success(void** state);
void test__alloc_destroy__success_after_allocate(void** state);
/*
 * test _alloc_allocate
 */
UT_ITEM_DECLARATION(_alloc_allocate)
void test__alloc_allocate__invalid_alocator(void** state);
void test__alloc_allocate__greater_than_max_small_memory(void** state);
void test__alloc_allocate__less_than_max_small_memory(void** state);
/*
 * test _alloc_deallocate
 */
UT_ITEM_DECLARATION(_alloc_deallocate)
void test__alloc_deallocate__invalid_allocator(void** state);
void test__alloc_deallocate__invalid_allocated_memory(void** state);
void test__alloc_deallocate__greater_than_max_small_memory(void** state);
void test__alloc_deallocate__less_than_max_small_memory(void** state);
/*
 * test _alloc_set_malloc_handler
 */
UT_ITEM_DECLARATION(_alloc_set_malloc_handler)
void test__alloc_set_malloc_handler___new_handler(void** state);
void test__alloc_set_malloc_handler___delete_handler(void** state);

#define UT_CSTL_ALLOC_CASE\
    UT_CASE(cstl_alloc),\
    UT_ITEM(_alloc_init),\
    unit_test(test__alloc_init__invalid_allocator),\
    unit_test(test__alloc_init__success),\
    UT_ITEM(_alloc_destroy),\
    unit_test(test__alloc_destroy__invalid_allocator),\
    unit_test(test__alloc_destroy__success),\
    unit_test(test__alloc_destroy__success_after_allocate),\
    UT_ITEM(_alloc_allocate),\
    unit_test(test__alloc_allocate__invalid_alocator),\
    unit_test(test__alloc_allocate__greater_than_max_small_memory),\
    unit_test(test__alloc_allocate__less_than_max_small_memory),\
    UT_ITEM(_alloc_deallocate),\
    unit_test(test__alloc_deallocate__invalid_allocator),\
    unit_test(test__alloc_deallocate__invalid_allocated_memory),\
    unit_test(test__alloc_deallocate__greater_than_max_small_memory),\
    unit_test(test__alloc_deallocate__less_than_max_small_memory),\
    UT_ITEM(_alloc_set_malloc_handler),\
    unit_test(test__alloc_set_malloc_handler___new_handler),\
    unit_test(test__alloc_set_malloc_handler___delete_handler)

#endif /* _UT_CSTL_ALLOC_H */

