#ifndef _UT_CSTL_VECTOR_AUX_H_
#define _UT_CSTL_VECTOR_AUX_H_

/*
 * test _vector_iterator_belong_to_vector
 */
void test__vector_iterator_belong_to_vector__null_container_pointer(void** state);
void test__vector_iterator_belong_to_vector__invalid_iterator_container_type(void** state);
void test__vector_iterator_belong_to_vector__invalid_iterator_iterator_type(void** state);
void test__vector_iterator_belong_to_vector__invalid_iterator_different_container(void** state);
void test__vector_iterator_belong_to_vector__less_than_begin(void** state);
void test__vector_iterator_belong_to_vector__within_vector(void** state);
void test__vector_iterator_belong_to_vector__end_iterator(void** state);
void test__vector_iterator_belong_to_vector__greater_than_end(void** state);

#define UT_CSTL_VECTOR_AUX_CASE \
    unit_test(test__vector_iterator_belong_to_vector__null_container_pointer),\
    unit_test(test__vector_iterator_belong_to_vector__invalid_iterator_container_type),\
    unit_test(test__vector_iterator_belong_to_vector__invalid_iterator_iterator_type),\
    unit_test(test__vector_iterator_belong_to_vector__invalid_iterator_different_container),\
    unit_test(test__vector_iterator_belong_to_vector__less_than_begin),\
    unit_test(test__vector_iterator_belong_to_vector__within_vector),\
    unit_test(test__vector_iterator_belong_to_vector__end_iterator),\
    unit_test(test__vector_iterator_belong_to_vector__greater_than_end)

#endif /* _UT_CSTL_VECTOR_AUX_H_ */

