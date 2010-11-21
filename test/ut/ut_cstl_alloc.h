#ifndef _UT_CSTL_ALLOC_H
#define _UT_CSTL_ALLOC_H

/*
 * test _alloc_init
 */
void test__alloc_init__invalid_allocator(void** state);
void test__alloc_init__success(void** state);
/*
 * test _alloc_destroy
 */
void test__alloc_destroy__invalid_allocator(void** state);
void test__alloc_destroy__success(void** state);
void test__alloc_destroy__success_after_allocate(void** state);
/*
 * test _alloc_allocate
 */
void test__alloc_allocate__invalid_alocator(void** state);
void test__alloc_allocate__greater_than_max_small_memory(void** state);
void test__alloc_allocate__less_than_max_small_memory(void** state);
/*
 * test _alloc_deallocate
 */
void test__alloc_deallocate__invalid_allocator(void** state);
void test__alloc_deallocate__invalid_allocated_memory(void** state);
void test__alloc_deallocate__greater_than_max_small_memory(void** state);
void test__alloc_deallocate__less_than_max_small_memory(void** state);
/*
 * test _alloc_set_malloc_handler
 */
void test__alloc_set_malloc_handler___new_handler(void** state);
void test__alloc_set_malloc_handler___delete_handler(void** state);

#define UT_CSTL_ALLOC_CASE\
    unit_test(test__alloc_init__invalid_allocator),\
    unit_test(test__alloc_init__success),\
    unit_test(test__alloc_destroy__invalid_allocator),\
    unit_test(test__alloc_destroy__success),\
    unit_test(test__alloc_destroy__success_after_allocate),\
    unit_test(test__alloc_allocate__invalid_alocator),\
    unit_test(test__alloc_allocate__greater_than_max_small_memory),\
    unit_test(test__alloc_allocate__less_than_max_small_memory),\
    unit_test(test__alloc_deallocate__invalid_allocator),\
    unit_test(test__alloc_deallocate__invalid_allocated_memory),\
    unit_test(test__alloc_deallocate__greater_than_max_small_memory),\
    unit_test(test__alloc_deallocate__less_than_max_small_memory),\
    unit_test(test__alloc_set_malloc_handler___new_handler),\
    unit_test(test__alloc_set_malloc_handler___delete_handler)

#endif /* _UT_CSTL_ALLOC_H */

