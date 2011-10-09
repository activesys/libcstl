#ifndef _UT_CSTL_ALLOC_AUX_H
#define _UT_CSTL_ALLOC_AUX_H

UT_SUIT_DECLARATION(cstl_alloc_aux)

#ifdef CSTL_MEMORY_MANAGEMENT
/*
 * test _alloc_get_memory_chunk
 */
UT_CASE_DECLARATION(_alloc_get_memory_chunk)
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
UT_CASE_DECLARATION(_alloc_apply_formated_memory)
void test__alloc_apply_formated_memory__invalid_allocator(void** state);
void test__alloc_apply_formated_memory__success(void** state);
#endif /* CSTL_MEMORY_MANAGEMENT */

/*
 * test _alloc_free
 */
UT_CASE_DECLARATION(_alloc_free)
void test__alloc_free__invalid_memory(void** state);

/*
 * test _alloc_malloc
 */
UT_CASE_DECLARATION(_alloc_malloc)
void test__alloc_malloc__success(void** state);

/*
 * test _alloc_malloc_out_of_memory
 */
UT_CASE_DECLARATION(_alloc_malloc_out_of_memory)
void test__alloc_malloc_out_of_memory__success(void** state);

#ifdef CSTL_MEMORY_MANAGEMENT
#   define UT_CSTL_ALLOC_AUX_CASE \
        UT_SUIT_BEGIN(cstl_alloc_aux, test__alloc_get_memory_chunk__invalid_allocator),\
        UT_CASE(test__alloc_get_memory_chunk__invalid_alloccount),\
        UT_CASE(test__alloc_get_memory_chunk__total_size_less_than_memory_pool),\
        UT_CASE(test__alloc_get_memory_chunk__memory_pool_less_than_total_size_greater_than_one_size),\
        UT_CASE(test__alloc_get_memory_chunk__memory_pool_size_equal_to_0),\
        UT_CASE(test__alloc_get_memory_chunk__memory_pool_size_less_then_one_allocated_chunk),\
        UT_CASE(test__alloc_get_memory_chunk__reallocate_memory_pool_container),\
        UT_CASE_BEGIN(_alloc_apply_formated_memory, test__alloc_apply_formated_memory__invalid_allocator),\
        UT_CASE(test__alloc_apply_formated_memory__success),\
        UT_CASE_BEGIN(_alloc_free, test__alloc_free__invalid_memory),\
        UT_CASE_BEGIN(_alloc_malloc, test__alloc_malloc__success),\
        UT_CASE_BEGIN(_alloc_malloc_out_of_memory, test__alloc_malloc_out_of_memory__success)
#else
#   define UT_CSTL_ALLOC_AUX_CASE \
        UT_SUIT_BEGIN(cstl_alloc_aux, test__alloc_free__invalid_memory),\
        UT_CASE_BEGIN(_alloc_malloc, test__alloc_malloc__success),\
        UT_CASE_BEGIN(_alloc_malloc_out_of_memory, test__alloc_malloc_out_of_memory__success)
#endif /* CSTL_MEMORY_MANAGEMENT */

#endif /* _UT_CSTL_ALLOC_AUX_H */
