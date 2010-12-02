#ifndef _UT_CSTL_ALLOC_AUX_H
#define _UT_CSTL_ALLOC_AUX_H

UT_CASE_DECLARATION(cstl_alloc_aux)

#ifndef _CSTL_USER_MODEL
/*
 * test _alloc_get_memory_chunk
 */
UT_ITEM_DECLARATION(_alloc_get_memory_chunk)
void test__alloc_get_memory_chunk__invalid_allocator(void** state);
void test__alloc_get_memory_chunk__invalid_alloccount(void** state);
void test__alloc_get_memory_chunk__total_size_less_than_memory_pool(void** state);
void test__alloc_get_memory_chunk__memory_pool_less_than_total_size_greater_than_one_size(void** state);
void test__alloc_get_memory_chunk__memory_pool_size_equal_to_0(void** state);
void test__alloc_get_memory_chunk__memory_pool_size_less_then_one_allocated_chunk(void** state);
void test__alloc_get_memory_chunk__reallocate_memory_pool_container(void** state);

/*
 * test _alloc_apply_formated_memory
 */
UT_ITEM_DECLARATION(_alloc_apply_formated_memory)
void test__alloc_apply_formated_memory__invalid_allocator(void** state);
void test__alloc_apply_formated_memory__success(void** state);
#endif /* _CSTL_USER_MODEL */

/*
 * test _alloc_free
 */
UT_ITEM_DECLARATION(_alloc_free)
void test__alloc_free__invalid_memory(void** state);

/*
 * test _alloc_malloc
 */
UT_ITEM_DECLARATION(_alloc_malloc)
void test__alloc_malloc__success(void** state);

/*
 * test _alloc_malloc_out_of_memory
 */
UT_ITEM_DECLARATION(_alloc_malloc_out_of_memory)
void test__alloc_malloc_out_of_memory__success(void** state);

#ifndef _CSTL_USER_MODEL
#   define UT_CSTL_ALLOC_AUX_CASE \
        UT_CASE(cstl_alloc_aux),\
        UT_ITEM(_alloc_get_memory_chunk),\
        unit_test(test__alloc_get_memory_chunk__invalid_allocator),\
        unit_test(test__alloc_get_memory_chunk__invalid_alloccount),\
        unit_test(test__alloc_get_memory_chunk__total_size_less_than_memory_pool),\
        unit_test(test__alloc_get_memory_chunk__memory_pool_less_than_total_size_greater_than_one_size),\
        unit_test(test__alloc_get_memory_chunk__memory_pool_size_equal_to_0),\
        unit_test(test__alloc_get_memory_chunk__memory_pool_size_less_then_one_allocated_chunk),\
        unit_test(test__alloc_get_memory_chunk__reallocate_memory_pool_container),\
        UT_ITEM(_alloc_apply_formated_memory),\
        unit_test(test__alloc_apply_formated_memory__invalid_allocator),\
        unit_test(test__alloc_apply_formated_memory__success),\
        UT_ITEM(_alloc_free),\
        unit_test(test__alloc_free__invalid_memory),\
        UT_ITEM(_alloc_malloc),\
        unit_test(test__alloc_malloc__success),\
        UT_ITEM(_alloc_malloc_out_of_memory),\
        unit_test(test__alloc_malloc_out_of_memory__success)
#else
#   define UT_CSTL_ALLOC_AUX_CASE \
        UT_CASE(cstl_alloc_aux),\
        UT_ITEM(_alloc_free),\
        unit_test(test__alloc_free__invalid_memory),\
        UT_ITEM(_alloc_malloc),\
        unit_test(test__alloc_malloc__success),\
        UT_ITEM(_alloc_malloc_out_of_memory),\
        unit_test(test__alloc_malloc_out_of_memory__success)
#endif /* _CSTL_USER_MODEL */

#endif /* _UT_CSTL_ALLOC_AUX_H */
