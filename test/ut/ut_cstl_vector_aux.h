#ifndef _UT_CSTL_VECTOR_AUX_H_
#define _UT_CSTL_VECTOR_AUX_H_

UT_CASE_DECLARATION(cstl_vector_aux)

/*
 * test _vector_iterator_belong_to_vector
 */
UT_ITEM_DECLARATION(_vector_iterator_belong_to_vector)
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
UT_ITEM_DECLARATION(_vector_same_type)
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
UT_ITEM_DECLARATION(_vector_same_vector_iterator_type)
void test__vector_same_vector_iterator_type__null_vector(void** state);
void test__vector_same_vector_iterator_type__iterator_null_container(void** state);
void test__vector_same_vector_iterator_type__iterator_not_vector_container(void** state);
void test__vector_same_vector_iterator_type__iterator_not_random_iterator(void** state);
void test__vector_same_vector_iterator_type__same(void** state);
void test__vector_same_vector_iterator_type__not_same(void** state);

#define UT_CSTL_VECTOR_AUX_CASE \
    UT_CASE(cstl_vector_aux),\
    UT_ITEM(_vector_iterator_belong_to_vector),\
    unit_test(test__vector_iterator_belong_to_vector__null_container_pointer),\
    unit_test(test__vector_iterator_belong_to_vector__invalid_iterator_container_type),\
    unit_test(test__vector_iterator_belong_to_vector__invalid_iterator_iterator_type),\
    unit_test(test__vector_iterator_belong_to_vector__invalid_iterator_different_container),\
    unit_test(test__vector_iterator_belong_to_vector__less_than_begin),\
    unit_test(test__vector_iterator_belong_to_vector__within_vector),\
    unit_test(test__vector_iterator_belong_to_vector__end_iterator),\
    unit_test(test__vector_iterator_belong_to_vector__greater_than_end),\
    UT_ITEM(_vector_same_type),\
    unit_test(test__vector_same_type__null_first),\
    unit_test(test__vector_same_type__null_second),\
    unit_test(test__vector_same_type__not_same_type_name),\
    unit_test(test__vector_same_type__not_same_type_pointer),\
    unit_test(test__vector_same_type__not_same_type_style),\
    unit_test(test__vector_same_type__same_type),\
    unit_test(test__vector_same_type__same_type_duplicate_name),\
    UT_ITEM(_vector_same_vector_iterator_type),\
    unit_test(test__vector_same_vector_iterator_type__null_vector),\
    unit_test(test__vector_same_vector_iterator_type__iterator_null_container),\
    unit_test(test__vector_same_vector_iterator_type__iterator_not_vector_container),\
    unit_test(test__vector_same_vector_iterator_type__iterator_not_random_iterator),\
    unit_test(test__vector_same_vector_iterator_type__same),\
    unit_test(test__vector_same_vector_iterator_type__not_same)

#endif /* _UT_CSTL_VECTOR_AUX_H_ */

