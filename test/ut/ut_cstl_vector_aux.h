#ifndef _UT_CSTL_VECTOR_AUX_H_
#define _UT_CSTL_VECTOR_AUX_H_

UT_SUIT_DECLARATION(cstl_vector_aux)

/*
 * test _vector_iterator_belong_to_vector
 */
UT_CASE_DECLARATION(_vector_iterator_belong_to_vector)
void test__vector_iterator_belong_to_vector__null_container_pointer(void** state);
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
void test__vector_same_type__not_same_type_name(void** state);
void test__vector_same_type__not_same_type_pointer(void** state);
void test__vector_same_type__not_same_type_style(void** state);
void test__vector_same_type__same_type(void** state);
void test__vector_same_type__same_type_duplicate_name(void** state);
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
 * test _vector_get_varg_value_auxiliary
 */
UT_CASE_DECLARATION(_vector_get_varg_value_auxiliary)
void test__vector_get_varg_value_auxiliary__null_vector_container(void** state);
void test__vector_get_varg_value_auxiliary__null_varg(void** state);
void test__vector_get_varg_value_auxiliary__successfully(void** state);
/*
 * test _vector_destroy_varg_value_auxiliary
 */
UT_CASE_DECLARATION(_vector_destroy_varg_value_auxiliary)
void test__vector_destroy_varg_value_auxiliary__null_vector_container(void** state);
void test__vector_destroy_varg_value_auxiliary__null_varg(void** state);
void test__vector_destroy_varg_value_auxiliary__successfully(void** state);
/*
 * test _vector_init_elem_range_auxiliary
 */
UT_CASE_DECLARATION(_vector_init_elem_range_auxiliary)
void test__vector_init_elem_range_auxiliary__null_vector_containter(void** state);
void test__vector_init_elem_range_auxiliary__null_pby_start(void** state);
void test__vector_init_elem_range_auxiliary__null_pby_finish(void** state);
void test__vector_init_elem_range_auxiliary__pby_finish_less_then_pby_start(void** state);
void test__vector_init_elem_range_auxiliary__successfully_int(void** state);
void test__vector_init_elem_range_auxiliary__successfully_cstr(void** state);
void test__vector_init_elem_range_auxiliary__successfully_iterator(void** state);

#define UT_CSTL_VECTOR_AUX_CASE \
    UT_SUIT_BEGIN(cstl_vector_aux, test__vector_iterator_belong_to_vector__null_container_pointer),\
    UT_CASE(test__vector_iterator_belong_to_vector__invalid_iterator_container_type),\
    UT_CASE(test__vector_iterator_belong_to_vector__invalid_iterator_iterator_type),\
    UT_CASE(test__vector_iterator_belong_to_vector__invalid_iterator_different_container),\
    UT_CASE(test__vector_iterator_belong_to_vector__less_than_begin),\
    UT_CASE(test__vector_iterator_belong_to_vector__within_vector),\
    UT_CASE(test__vector_iterator_belong_to_vector__end_iterator),\
    UT_CASE(test__vector_iterator_belong_to_vector__greater_than_end),\
    UT_CASE_BEGIN(_vector_same_type, test__vector_same_type__null_first),\
    UT_CASE(test__vector_same_type__null_second),\
    UT_CASE(test__vector_same_type__not_same_type_name),\
    UT_CASE(test__vector_same_type__not_same_type_pointer),\
    UT_CASE(test__vector_same_type__not_same_type_style),\
    UT_CASE(test__vector_same_type__same_type),\
    UT_CASE(test__vector_same_type__same_type_duplicate_name),\
    UT_CASE_BEGIN(_vector_same_vector_iterator_type, test__vector_same_vector_iterator_type__null_vector),\
    UT_CASE(test__vector_same_vector_iterator_type__iterator_null_container),\
    UT_CASE(test__vector_same_vector_iterator_type__iterator_not_vector_container),\
    UT_CASE(test__vector_same_vector_iterator_type__iterator_not_random_iterator),\
    UT_CASE(test__vector_same_vector_iterator_type__same),\
    UT_CASE(test__vector_same_vector_iterator_type__not_same),\
    UT_CASE_BEGIN(_vector_get_varg_value_auxiliary, test__vector_get_varg_value_auxiliary__null_vector_container),\
    UT_CASE(test__vector_get_varg_value_auxiliary__null_varg),\
    UT_CASE(test__vector_get_varg_value_auxiliary__successfully),\
    UT_CASE_BEGIN(_vector_destroy_varg_value_auxiliary, test__vector_destroy_varg_value_auxiliary__null_vector_container),\
    UT_CASE(test__vector_destroy_varg_value_auxiliary__null_varg),\
    UT_CASE(test__vector_destroy_varg_value_auxiliary__successfully),\
    UT_CASE_BEGIN(_vector_init_elem_range_auxiliary, test__vector_init_elem_range_auxiliary__null_vector_containter),\
    UT_CASE(test__vector_init_elem_range_auxiliary__null_pby_start),\
    UT_CASE(test__vector_init_elem_range_auxiliary__null_pby_finish),\
    UT_CASE(test__vector_init_elem_range_auxiliary__pby_finish_less_then_pby_start),\
    UT_CASE(test__vector_init_elem_range_auxiliary__successfully_int),\
    UT_CASE(test__vector_init_elem_range_auxiliary__successfully_cstr),\
    UT_CASE(test__vector_init_elem_range_auxiliary__successfully_iterator)

#endif /* _UT_CSTL_VECTOR_AUX_H_ */

