#ifndef _UT_CSTL_LIST_AUX_H_
#define _UT_CSTL_LIST_AUX_H_

UT_SUIT_DECLARATION(cstl_list_aux)

/*
 * test _list_is_created
 */
UT_CASE_DECLARATION(_list_is_created)
void test__list_is_created__null_list_container(void** state);
void test__list_is_created__invalid_type_style(void** state);
void test__list_is_created__invalid_type_pointer(void** state);
void test__list_is_created__null_node(void** state);
void test__list_is_created__uninited_allocator(void** state);
void test__list_is_created__successfully(void** state);
/*
 * test _list_is_inited
 */
UT_CASE_DECLARATION(_list_is_inited)
void test__list_is_inited__null_list_container(void** state);
void test__list_is_inited__invalid_type_styple(void** state);
void test__list_is_inited__invalid_type_pointer(void** state);
void test__list_is_inited__null_node(void** state);
void test__list_is_inited__invalid_node_prev_pointer(void** state);
void test__list_is_inited__invalid_node_next_pointer(void** state);
void test__list_is_inited__init_empty(void** state);
void test__list_is_inited__init_non_empty(void** state);
/*
 * test _list_iterator_belong_to_list
 */
UT_CASE_DECLARATION(_list_iterator_belong_to_list)
void test__list_iterator_belong_to_list__null_list_container(void** state);
void test__list_iterator_belong_to_list__non_inited_list_container(void** state);
void test__list_iterator_belong_to_list__invalid_iter_container_type(void** state);
void test__list_iterator_belong_to_list__invalid_iter_iterator_type(void** state);
void test__list_iterator_belong_to_list__invalid_iter_container_pointer(void** state);
void test__list_iterator_belong_to_list__not_belong_to_list(void** state);
void test__list_iterator_belong_to_list__belong_to_list_begin(void** state);
void test__list_iterator_belong_to_list__belong_to_list_middle(void** state);
void test__list_iterator_belong_to_list__belong_to_list_end(void** state);

#define UT_CSTL_LIST_AUX_CASE \
    UT_SUIT_BEGIN(cstl_list_aux, test__list_is_created__null_list_container),\
    UT_CASE(test__list_is_created__invalid_type_style),\
    UT_CASE(test__list_is_created__invalid_type_pointer),\
    UT_CASE(test__list_is_created__null_node),\
    UT_CASE(test__list_is_created__uninited_allocator),\
    UT_CASE(test__list_is_created__successfully),\
    UT_CASE_BEGIN(_list_is_inited, test__list_is_inited__null_list_container),\
    UT_CASE(test__list_is_inited__invalid_type_styple),\
    UT_CASE(test__list_is_inited__invalid_type_pointer),\
    UT_CASE(test__list_is_inited__null_node),\
    UT_CASE(test__list_is_inited__invalid_node_prev_pointer),\
    UT_CASE(test__list_is_inited__invalid_node_next_pointer),\
    UT_CASE(test__list_is_inited__init_empty),\
    UT_CASE(test__list_is_inited__init_non_empty),\
    UT_CASE_BEGIN(_list_iterator_belong_to_list, test__list_iterator_belong_to_list__null_list_container),\
    UT_CASE(test__list_iterator_belong_to_list__non_inited_list_container),\
    UT_CASE(test__list_iterator_belong_to_list__invalid_iter_container_type),\
    UT_CASE(test__list_iterator_belong_to_list__invalid_iter_iterator_type),\
    UT_CASE(test__list_iterator_belong_to_list__invalid_iter_container_pointer),\
    UT_CASE(test__list_iterator_belong_to_list__not_belong_to_list),\
    UT_CASE(test__list_iterator_belong_to_list__belong_to_list_begin),\
    UT_CASE(test__list_iterator_belong_to_list__belong_to_list_middle),\
    UT_CASE(test__list_iterator_belong_to_list__belong_to_list_end)

#endif /* _UT_CSTL_LIST_AUX_H_ */

