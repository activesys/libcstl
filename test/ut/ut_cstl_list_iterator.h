#ifndef _UT_CSTL_LIST_ITERATOR_H_
#define _UT_CSTL_LIST_ITERATOR_H_

UT_SUIT_DECLARATION(cstl_list_iterator)

/*
 * test _create_list_iterator
 */
UT_CASE_DECLARATION(_create_list_iterator)
void test__create_list_iterator__successfully(void** state);
/*
 * test _list_iterator_get_value
 */
UT_CASE_DECLARATION(_list_iterator_get_value)
void test__list_iterator_get_value__invalid_iterator(void** state);
void test__list_iterator_get_value__invalid_iterator_container_type(void** state);
void test__list_iterator_get_value__invalid_iterator_iterator_type(void** state);
void test__list_iterator_get_value__invalid_iterator_end(void** state);
void test__list_iterator_get_value__invalid_data_buffer(void** state);
void test__list_iterator_get_value__successfully(void** state);
void test__list_iterator_get_value__successfully_cstr(void** state);
/*
 * test _list_iterator_set_value
 */
UT_CASE_DECLARATION(_list_iterator_set_value)
void test__list_iterator_set_value__invalid_iter(void** state);
void test__list_iterator_set_value__invalid_iter_container_type(void** state);
void test__list_iterator_set_value__invalid_iter_iterator_type(void** state);
void test__list_iterator_set_value__invalid_iter_end(void** state);
void test__list_iterator_set_value__successfully(void** state);
void test__list_iterator_set_value__successfully_cstr(void** state);
/*
 * test _list_iterator_get_pointer
 */
UT_CASE_DECLARATION(_list_iterator_get_pointer)
void test__list_iterator_get_pointer__invalid_iter(void** state);
void test__list_iterator_get_pointer__invalid_iter_container_type(void** state);
void test__list_iterator_get_pointer__invalid_iter_iterator_type(void** state);
void test__list_iterator_get_pointer__successfully(void** state);
void test__list_iterator_get_pointer__successfully_cstr(void** state);
/*
 * test _list_iterator_next
 */
UT_CASE_DECLARATION(_list_iterator_next)
void test__list_iterator_next__invalid_iter(void** state);
void test__list_iterator_next__invalid_iter_container_type(void** state);
void test__list_iterator_next__invalid_iter_iterator_type(void** state);
void test__list_iterator_next__invalid_iter_end(void** state);
void test__list_iterator_next__successfully_end(void** state);
void test__list_iterator_next__successfully(void** state);
/*
 * test _list_iterator_prev
 */
UT_CASE_DECLARATION(_list_iterator_prev)
void test__list_iterator_prev__invalid_iter(void** state);
void test__list_iterator_prev__invalid_iter_container_type(void** state);
void test__list_iterator_prev__invalid_iter_iterator_type(void** state);
void test__list_iterator_prev__invalid_iter_begin(void** state);
void test__list_iterator_prev__successfully_begin(void** state);
void test__list_iterator_prev__successfully(void** state);

#define UT_CSTL_LIST_ITERATOR_CASE\
    UT_SUIT_BEGIN(cstl_list_iterator, test__create_list_iterator__successfully),\
    UT_CASE_BEGIN(_list_iterator_get_value, test__list_iterator_get_value__invalid_iterator),\
    UT_CASE(test__list_iterator_get_value__invalid_iterator_container_type),\
    UT_CASE(test__list_iterator_get_value__invalid_iterator_iterator_type),\
    UT_CASE(test__list_iterator_get_value__invalid_iterator_end),\
    UT_CASE(test__list_iterator_get_value__invalid_data_buffer),\
    UT_CASE(test__list_iterator_get_value__successfully),\
    UT_CASE(test__list_iterator_get_value__successfully_cstr),\
    UT_CASE_BEGIN(_list_iterator_set_value, test__list_iterator_set_value__invalid_iter),\
    UT_CASE(test__list_iterator_set_value__invalid_iter_container_type),\
    UT_CASE(test__list_iterator_set_value__invalid_iter_iterator_type),\
    UT_CASE(test__list_iterator_set_value__invalid_iter_end),\
    UT_CASE(test__list_iterator_set_value__successfully),\
    UT_CASE(test__list_iterator_set_value__successfully_cstr),\
    UT_CASE_BEGIN(_list_iterator_next, test__list_iterator_next__invalid_iter),\
    UT_CASE(test__list_iterator_next__invalid_iter_container_type),\
    UT_CASE(test__list_iterator_next__invalid_iter_iterator_type),\
    UT_CASE(test__list_iterator_next__invalid_iter_end),\
    UT_CASE(test__list_iterator_next__successfully_end),\
    UT_CASE(test__list_iterator_next__successfully),\
    UT_CASE_BEGIN(_list_iterator_prev, test__list_iterator_prev__invalid_iter),\
    UT_CASE(test__list_iterator_prev__invalid_iter_container_type),\
    UT_CASE(test__list_iterator_prev__invalid_iter_iterator_type),\
    UT_CASE(test__list_iterator_prev__invalid_iter_begin),\
    UT_CASE(test__list_iterator_prev__successfully_begin),\
    UT_CASE(test__list_iterator_prev__successfully)

#endif /* _UT_CSTL_LIST_ITERATOR_H_ */

