#ifndef _UT_CSTL_VECTOR_ITERATOR_H_
#define _UT_CSTL_VECTOR_ITERATOR_H_

/*
 * test _create_vector_iterator
 */
void test__create_vector_iterator__successfully(void** state);
/*
 * test _vector_iterator_equal
 */
void test__vector_iterator_equal__different_container_type(void** state);
void test__vector_iterator_equal__different_iterator_type(void** state);
void test__vector_iterator_equal__different_container_pointer(void** state);
void test__vector_iterator_equal__first_is_not_belong_to_vector(void** state);
void test__vector_iterator_equal__second_is_not_belong_to_vector(void** state);
void test__vector_iterator_equal__equal(void** state);
void test__vector_iterator_equal__not_equal(void** state);

#define UT_CSTL_VECTOR_ITERATOR_CASE \
    unit_test(test__create_vector_iterator__successfully),\
    unit_test(test__vector_iterator_equal__different_container_type),\
    unit_test(test__vector_iterator_equal__different_iterator_type),\
    unit_test(test__vector_iterator_equal__different_container_pointer),\
    unit_test(test__vector_iterator_equal__first_is_not_belong_to_vector),\
    unit_test(test__vector_iterator_equal__second_is_not_belong_to_vector),\
    unit_test(test__vector_iterator_equal__equal),\
    unit_test(test__vector_iterator_equal__not_equal)

#endif /* _UT_CSTL_VECTOR_ITERATOR_H_ */

