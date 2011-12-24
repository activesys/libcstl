#ifndef _UT_CSTL_VECTOR_AUX_H_
#define _UT_CSTL_VECTOR_AUX_H_

UT_SUIT_DECLARATION(cstl_vector_aux)

/*
 * test _vector_iterator_belong_to_vector
 */
UT_CASE_DECLARATION(_vector_iterator_belong_to_vector)
void test__vector_iterator_belong_to_vector__null_container_pointer(void** state);
void test__vector_iterator_belong_to_vector__non_inited_vector_container(void** state);
void test__vector_iterator_belong_to_vector__invalid_iterator_container_type(void** state);
void test__vector_iterator_belong_to_vector__invalid_iterator_iterator_type(void** state);
void test__vector_iterator_belong_to_vector__invalid_iterator_different_container(void** state);
void test__vector_iterator_belong_to_vector__less_than_begin(void** state);
void test__vector_iterator_belong_to_vector__within_vector(void** state);
void test__vector_iterator_belong_to_vector__end_iterator(void** state);
void test__vector_iterator_belong_to_vector__greater_than_end(void** state);
/*
 * test _vector_same_type
 */
UT_CASE_DECLARATION(_vector_same_type)
void test__vector_same_type__null_first(void** state);
void test__vector_same_type__null_second(void** state);
void test__vector_same_type__non_created_first(void** state);
void test__vector_same_type__non_created_second(void** state);
void test__vector_same_type__not_same_type_name(void** state);
void test__vector_same_type__not_same_type_pointer(void** state);
void test__vector_same_type__not_same_type_style(void** state);
void test__vector_same_type__not_same_type_style_ex1(void** state);
void test__vector_same_type__not_same_type_style_ex2(void** state);
void test__vector_same_type__same_type(void** state);
void test__vector_same_type__same_type_duplicate_name(void** state);
void test__vector_same_type__same_container(void** state);
/*
 * test _vector_same_vector_iterator_type
 */
UT_CASE_DECLARATION(_vector_same_vector_iterator_type)
void test__vector_same_vector_iterator_type__null_vector(void** state);
void test__vector_same_vector_iterator_type__iterator_null_container(void** state);
void test__vector_same_vector_iterator_type__iterator_not_vector_container(void** state);
void test__vector_same_vector_iterator_type__iterator_not_random_iterator(void** state);
void test__vector_same_vector_iterator_type__same(void** state);
void test__vector_same_vector_iterator_type__not_same(void** state);
/*
 * test _vector_same_iterator_type
 */
UT_CASE_DECLARATION(_vector_same_iterator_type)
void test__vector_same_iterator_type__null_vector_container(void** state);
void test__vector_same_iterator_type__invalid_iterator_null_container(void** state);
void test__vector_same_iterator_type__invalid_iterator_container_type(void** state);
void test__vector_same_iterator_type__invalid_iterator_iterator_type(void** state);
void test__vector_same_iterator_type__same_type_belong_to_vector(void** state);
void test__vector_same_iterator_type__same_type_not_belong_to_vector(void** state);
void test__vector_same_iterator_type__not_same_type(void** state);
void test__vector_same_iterator_type__same_type_not_vector_iterator(void** state);
void test__vector_same_iterator_type__not_same_type_not_vector_iterator(void** state);
/*
 * test _vector_get_varg_value_auxiliary
 */
UT_CASE_DECLARATION(_vector_get_varg_value_auxiliary)
void test__vector_get_varg_value_auxiliary__null_vector_container(void** state);
void test__vector_get_varg_value_auxiliary__null_varg(void** state);
void test__vector_get_varg_value_auxiliary__non_created(void** state);
void test__vector_get_varg_value_auxiliary__successfully(void** state);
/*
 * test _vector_destroy_varg_value_auxiliary
 */
UT_CASE_DECLARATION(_vector_destroy_varg_value_auxiliary)
void test__vector_destroy_varg_value_auxiliary__null_vector_container(void** state);
void test__vector_destroy_varg_value_auxiliary__null_varg(void** state);
void test__vector_destroy_varg_value_auxiliary__non_created(void** state);
void test__vector_destroy_varg_value_auxiliary__successfully(void** state);
/*
 * test _vector_init_elem_range_auxiliary
 */
UT_CASE_DECLARATION(_vector_init_elem_range_auxiliary)
void test__vector_init_elem_range_auxiliary__null_vector_containter(void** state);
void test__vector_init_elem_range_auxiliary__null_pby_start(void** state);
void test__vector_init_elem_range_auxiliary__null_pby_finish(void** state);
void test__vector_init_elem_range_auxiliary__pby_finish_less_then_pby_start(void** state);
void test__vector_init_elem_range_auxiliary__non_created(void** state);
void test__vector_init_elem_range_auxiliary__successfully_int(void** state);
void test__vector_init_elem_range_auxiliary__successfully_cstr(void** state);
void test__vector_init_elem_range_auxiliary__successfully_iterator(void** state);
void test__vector_init_elem_range_auxiliary__successfully_container(void** state);
/*
 * test _vector_is_created
 */
UT_CASE_DECLARATION(_vector_is_created)
void test__vector_is_created__null_vector_container(void** state);
void test__vector_is_created__non_created_invalid_start(void** state);
void test__vector_is_created__non_created_invalid_finish(void** state);
void test__vector_is_created__non_created_invalid_endofstorage(void** state);
void test__vector_is_created__non_created_invalid_type_style(void** state);
void test__vector_is_created__non_created_non_init_allocator(void** state);
void test__vector_is_created__created(void** state);
/*
 * test _vector_is_inited
 */
UT_CASE_DECLARATION(_vector_is_inited)
void test__vector_is_inited__null_vector_container(void** state);
void test__vector_is_inited__non_inited_not_all_null(void** state);
void test__vector_is_inited__non_inited_finish_less_than_start(void** state);
void test__vector_is_inited__non_inited_endofstorage_less_than_start(void** state);
void test__vector_is_inited__non_inited_endofstorage_less_than_finish(void** state);
void test__vector_is_inited__non_inited_invalid_type_style(void** state);
void test__vector_is_inited__inited_empty(void** state);
void test__vector_is_inited__inited_non_empty(void** state);
/*
 * test _vector_calculate_new_capacity
 */
UT_CASE_DECLARATION(_vector_calculate_new_capacity)
void test__vector_calculate_new_capacity__0_size_0_insert(void** state);
void test__vector_calculate_new_capacity__0_size_1_insert(void** state);
void test__vector_calculate_new_capacity__0_size_8_insert(void** state);
void test__vector_calculate_new_capacity__0_size_48_insert(void** state);
void test__vector_calculate_new_capacity__0_size_1000_insert(void** state);
void test__vector_calculate_new_capacity__5_size_0_insert(void** state);
void test__vector_calculate_new_capacity__5_size_1_insert(void** state);
void test__vector_calculate_new_capacity__5_size_10_insert(void** state);
void test__vector_calculate_new_capacity__5_size_40_insert(void** state);
void test__vector_calculate_new_capacity__5_size_4000_insert(void** state);
void test__vector_calculate_new_capacity__40_size_0_insert(void** state);
void test__vector_calculate_new_capacity__40_size_1_insert(void** state);
void test__vector_calculate_new_capacity__40_size_40_insert(void** state);
void test__vector_calculate_new_capacity__40_size_50000_insert(void** state);
void test__vector_calculate_new_capacity__12345_size_0_insert(void** state);
void test__vector_calculate_new_capacity__12345_size_1_insert(void** state);
void test__vector_calculate_new_capacity__12345_size_16_insert(void** state);
void test__vector_calculate_new_capacity__12345_size_1600894_insert(void** state);

#define UT_CSTL_VECTOR_AUX_CASE \
    UT_SUIT_BEGIN(cstl_vector_aux, test__vector_iterator_belong_to_vector__null_container_pointer),\
    UT_CASE(test__vector_iterator_belong_to_vector__non_inited_vector_container),\
    UT_CASE(test__vector_iterator_belong_to_vector__invalid_iterator_container_type),\
    UT_CASE(test__vector_iterator_belong_to_vector__invalid_iterator_iterator_type),\
    UT_CASE(test__vector_iterator_belong_to_vector__invalid_iterator_different_container),\
    UT_CASE(test__vector_iterator_belong_to_vector__less_than_begin),\
    UT_CASE(test__vector_iterator_belong_to_vector__within_vector),\
    UT_CASE(test__vector_iterator_belong_to_vector__end_iterator),\
    UT_CASE(test__vector_iterator_belong_to_vector__greater_than_end),\
    UT_CASE_BEGIN(_vector_same_type, test__vector_same_type__null_first),\
    UT_CASE(test__vector_same_type__null_second),\
    UT_CASE(test__vector_same_type__non_created_first),\
    UT_CASE(test__vector_same_type__non_created_second),\
    UT_CASE(test__vector_same_type__not_same_type_name),\
    UT_CASE(test__vector_same_type__not_same_type_pointer),\
    UT_CASE(test__vector_same_type__not_same_type_style),\
    UT_CASE(test__vector_same_type__not_same_type_style_ex1),\
    UT_CASE(test__vector_same_type__not_same_type_style_ex2),\
    UT_CASE(test__vector_same_type__same_type),\
    UT_CASE(test__vector_same_type__same_type_duplicate_name),\
    UT_CASE(test__vector_same_type__same_container),\
    UT_CASE_BEGIN(_vector_same_vector_iterator_type, test__vector_same_vector_iterator_type__null_vector),\
    UT_CASE(test__vector_same_vector_iterator_type__iterator_null_container),\
    UT_CASE(test__vector_same_vector_iterator_type__iterator_not_vector_container),\
    UT_CASE(test__vector_same_vector_iterator_type__iterator_not_random_iterator),\
    UT_CASE(test__vector_same_vector_iterator_type__same),\
    UT_CASE(test__vector_same_vector_iterator_type__not_same),\
    UT_CASE_BEGIN(_vector_same_iterator_type, test__vector_same_iterator_type__null_vector_container),\
    UT_CASE(test__vector_same_iterator_type__invalid_iterator_null_container),\
    UT_CASE(test__vector_same_iterator_type__invalid_iterator_container_type),\
    UT_CASE(test__vector_same_iterator_type__invalid_iterator_iterator_type),\
    UT_CASE(test__vector_same_iterator_type__same_type_belong_to_vector),\
    UT_CASE(test__vector_same_iterator_type__same_type_not_belong_to_vector),\
    UT_CASE(test__vector_same_iterator_type__not_same_type),\
    UT_CASE(test__vector_same_iterator_type__same_type_not_vector_iterator),\
    UT_CASE(test__vector_same_iterator_type__not_same_type_not_vector_iterator),\
    UT_CASE_BEGIN(_vector_get_varg_value_auxiliary, test__vector_get_varg_value_auxiliary__null_vector_container),\
    UT_CASE(test__vector_get_varg_value_auxiliary__null_varg),\
    UT_CASE(test__vector_get_varg_value_auxiliary__non_created),\
    UT_CASE(test__vector_get_varg_value_auxiliary__successfully),\
    UT_CASE_BEGIN(_vector_destroy_varg_value_auxiliary, test__vector_destroy_varg_value_auxiliary__null_vector_container),\
    UT_CASE(test__vector_destroy_varg_value_auxiliary__null_varg),\
    UT_CASE(test__vector_destroy_varg_value_auxiliary__non_created),\
    UT_CASE(test__vector_destroy_varg_value_auxiliary__successfully),\
    UT_CASE_BEGIN(_vector_init_elem_range_auxiliary, test__vector_init_elem_range_auxiliary__null_vector_containter),\
    UT_CASE(test__vector_init_elem_range_auxiliary__null_pby_start),\
    UT_CASE(test__vector_init_elem_range_auxiliary__null_pby_finish),\
    UT_CASE(test__vector_init_elem_range_auxiliary__pby_finish_less_then_pby_start),\
    UT_CASE(test__vector_init_elem_range_auxiliary__non_created),\
    UT_CASE(test__vector_init_elem_range_auxiliary__successfully_int),\
    UT_CASE(test__vector_init_elem_range_auxiliary__successfully_cstr),\
    UT_CASE(test__vector_init_elem_range_auxiliary__successfully_iterator),\
    UT_CASE(test__vector_init_elem_range_auxiliary__successfully_container),\
    UT_CASE_BEGIN(_vector_is_created, test__vector_is_created__null_vector_container),\
    UT_CASE(test__vector_is_created__non_created_invalid_start),\
    UT_CASE(test__vector_is_created__non_created_invalid_finish),\
    UT_CASE(test__vector_is_created__non_created_invalid_endofstorage),\
    UT_CASE(test__vector_is_created__non_created_invalid_type_style),\
    UT_CASE(test__vector_is_created__non_created_non_init_allocator),\
    UT_CASE(test__vector_is_created__created),\
    UT_CASE_BEGIN(_vector_is_inited, test__vector_is_inited__null_vector_container),\
    UT_CASE(test__vector_is_inited__non_inited_not_all_null),\
    UT_CASE(test__vector_is_inited__non_inited_finish_less_than_start),\
    UT_CASE(test__vector_is_inited__non_inited_endofstorage_less_than_start),\
    UT_CASE(test__vector_is_inited__non_inited_endofstorage_less_than_finish),\
    UT_CASE(test__vector_is_inited__non_inited_invalid_type_style),\
    UT_CASE(test__vector_is_inited__inited_empty),\
    UT_CASE(test__vector_is_inited__inited_non_empty),\
    UT_CASE_BEGIN(_vector_calculate_new_capacity, test__vector_calculate_new_capacity__0_size_0_insert),\
    UT_CASE(test__vector_calculate_new_capacity__0_size_1_insert),\
    UT_CASE(test__vector_calculate_new_capacity__0_size_8_insert),\
    UT_CASE(test__vector_calculate_new_capacity__0_size_48_insert),\
    UT_CASE(test__vector_calculate_new_capacity__0_size_1000_insert),\
    UT_CASE(test__vector_calculate_new_capacity__5_size_0_insert),\
    UT_CASE(test__vector_calculate_new_capacity__5_size_1_insert),\
    UT_CASE(test__vector_calculate_new_capacity__5_size_10_insert),\
    UT_CASE(test__vector_calculate_new_capacity__5_size_40_insert),\
    UT_CASE(test__vector_calculate_new_capacity__5_size_4000_insert),\
    UT_CASE(test__vector_calculate_new_capacity__40_size_0_insert),\
    UT_CASE(test__vector_calculate_new_capacity__40_size_1_insert),\
    UT_CASE(test__vector_calculate_new_capacity__40_size_40_insert),\
    UT_CASE(test__vector_calculate_new_capacity__40_size_50000_insert),\
    UT_CASE(test__vector_calculate_new_capacity__12345_size_0_insert),\
    UT_CASE(test__vector_calculate_new_capacity__12345_size_1_insert),\
    UT_CASE(test__vector_calculate_new_capacity__12345_size_16_insert),\
    UT_CASE(test__vector_calculate_new_capacity__12345_size_1600894_insert)

#endif /* _UT_CSTL_VECTOR_AUX_H_ */

