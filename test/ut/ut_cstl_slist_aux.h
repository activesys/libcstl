#ifndef _UT_CSTL_SLIST_AUX_H_
#define _UT_CSTL_SLIST_AUX_H_

UT_SUIT_DECLARATION(cstl_slist_aux)

/*
 * test _slist_is_created
 */
UT_CASE_DECLARATION(_slist_is_created)
void test__slist_is_created__null_slist_container(void** state);
void test__slist_is_created__invalid_type_style(void** state);
void test__slist_is_created__invalid_type_pointer(void** state);
void test__slist_is_created__null_node(void** state);
void test__slist_is_created__uninited_allocator(void** state);
void test__slist_is_created__successfully(void** state);
/*
 * test _slist_is_inited
 */
UT_CASE_DECLARATION(_slist_is_inited)
void test__slist_is_inited__null_slist_container(void** state);
void test__slist_is_inited__invalid_type_styple(void** state);
void test__slist_is_inited__invalid_type_pointer(void** state);
void test__slist_is_inited__init_empty(void** state);
void test__slist_is_inited__init_non_empty(void** state);
/*
 * test _slist_iterator_belong_to_slist
 */
UT_CASE_DECLARATION(_slist_iterator_belong_to_slist)
void test__slist_iterator_belong_to_slist__null_slist_container(void** state);
void test__slist_iterator_belong_to_slist__non_inited_slist_container(void** state);
void test__slist_iterator_belong_to_slist__invalid_iter_container_type(void** state);
void test__slist_iterator_belong_to_slist__invalid_iter_iterator_type(void** state);
void test__slist_iterator_belong_to_slist__invalid_iter_container_pointer(void** state);
void test__slist_iterator_belong_to_slist__not_belong_to_slist(void** state);
void test__slist_iterator_belong_to_slist__belong_to_slist_begin(void** state);
void test__slist_iterator_belong_to_slist__belong_to_slist_middle(void** state);
void test__slist_iterator_belong_to_slist__belong_to_slist_end(void** state);
/*
 * test _slist_same_type
 */
UT_CASE_DECLARATION(_slist_same_type)
void test__slist_same_type__null_first(void** state);
void test__slist_same_type__null_second(void** state);
void test__slist_same_type__non_created_first(void** state);
void test__slist_same_type__non_created_second(void** state);
void test__slist_same_type__same_c_builtin(void** state);
void test__slist_same_type__same_c_builtin_dup(void** state);
void test__slist_same_type__not_same_c_builtin(void** state);
void test__slist_same_type__same_libcstl_builtin(void** state);
void test__slist_same_type__same_libcstl_builtin_dup(void** state);
void test__slist_same_type__not_same_libcstl_builtin_container(void** state);
void test__slist_same_type__not_same_libcstl_builtin_elem(void** state);
void test__slist_same_type__not_same_libcstl_builtin_iter(void** state);
void test__slist_same_type__not_same_libcstl_builtin_string(void** state);
void test__slist_same_type__not_same_c_libcstl_builtin(void** state);
void test__slist_same_type__same_user_defined(void** state);
void test__slist_same_type__same_user_defined_dup(void** state);
void test__slist_same_type__not_same_c_user_define(void** state);
void test__slist_same_type__not_same_libcstl_user_define(void** state);
void test__slist_same_type__same_container(void** state);
/*
 * test _slist_same_slist_iterator_type
 */
UT_CASE_DECLARATION(_slist_same_slist_iterator_type)
void test__slist_same_slist_iterator_type__null_slist_container(void** state);
void test__slist_same_slist_iterator_type__invalid_iterator_null_container(void** state);
void test__slist_same_slist_iterator_type__invalid_iterator_container_type(void** state);
void test__slist_same_slist_iterator_type__invalid_iterator_iterator_type(void** state);
void test__slist_same_slist_iterator_type__same_type_belong_to_slist(void** state);
void test__slist_same_slist_iterator_type__same_type_not_belong_to_slist(void** state);
void test__slist_same_slist_iterator_type__not_same_type(void** state);

#define UT_CSTL_SLIST_AUX_CASE\
    UT_SUIT_BEGIN(cstl_slist_aux, test__slist_is_created__null_slist_container),\
    UT_CASE(test__slist_is_created__invalid_type_style),\
    UT_CASE(test__slist_is_created__invalid_type_pointer),\
    UT_CASE(test__slist_is_created__null_node),\
    UT_CASE(test__slist_is_created__uninited_allocator),\
    UT_CASE(test__slist_is_created__successfully),\
    UT_CASE_BEGIN(_slist_is_inited, test__slist_is_inited__null_slist_container),\
    UT_CASE(test__slist_is_inited__invalid_type_styple),\
    UT_CASE(test__slist_is_inited__invalid_type_pointer),\
    UT_CASE(test__slist_is_inited__init_empty),\
    UT_CASE(test__slist_is_inited__init_non_empty),\
    UT_CASE_BEGIN(_slist_iterator_belong_to_slist, test__slist_iterator_belong_to_slist__null_slist_container),\
    UT_CASE(test__slist_iterator_belong_to_slist__non_inited_slist_container),\
    UT_CASE(test__slist_iterator_belong_to_slist__invalid_iter_container_type),\
    UT_CASE(test__slist_iterator_belong_to_slist__invalid_iter_iterator_type),\
    UT_CASE(test__slist_iterator_belong_to_slist__invalid_iter_container_pointer),\
    UT_CASE(test__slist_iterator_belong_to_slist__not_belong_to_slist),\
    UT_CASE(test__slist_iterator_belong_to_slist__belong_to_slist_begin),\
    UT_CASE(test__slist_iterator_belong_to_slist__belong_to_slist_middle),\
    UT_CASE(test__slist_iterator_belong_to_slist__belong_to_slist_end),\
    UT_CASE_BEGIN(_slist_same_type, test__slist_same_type__null_first),\
    UT_CASE(test__slist_same_type__null_second),\
    UT_CASE(test__slist_same_type__non_created_first),\
    UT_CASE(test__slist_same_type__non_created_second),\
    UT_CASE(test__slist_same_type__same_c_builtin),\
    UT_CASE(test__slist_same_type__same_c_builtin_dup),\
    UT_CASE(test__slist_same_type__not_same_c_builtin),\
    UT_CASE(test__slist_same_type__same_libcstl_builtin),\
    UT_CASE(test__slist_same_type__same_libcstl_builtin_dup),\
    UT_CASE(test__slist_same_type__not_same_libcstl_builtin_container),\
    UT_CASE(test__slist_same_type__not_same_libcstl_builtin_elem),\
    UT_CASE(test__slist_same_type__not_same_libcstl_builtin_iter),\
    UT_CASE(test__slist_same_type__not_same_libcstl_builtin_string),\
    UT_CASE(test__slist_same_type__not_same_c_libcstl_builtin),\
    UT_CASE(test__slist_same_type__same_user_defined),\
    UT_CASE(test__slist_same_type__same_user_defined_dup),\
    UT_CASE(test__slist_same_type__not_same_c_user_define),\
    UT_CASE(test__slist_same_type__not_same_libcstl_user_define),\
    UT_CASE(test__slist_same_type__same_container),\
    UT_CASE_BEGIN(_slist_same_slist_iterator_type, test__slist_same_slist_iterator_type__null_slist_container),\
    UT_CASE(test__slist_same_slist_iterator_type__invalid_iterator_null_container),\
    UT_CASE(test__slist_same_slist_iterator_type__invalid_iterator_container_type),\
    UT_CASE(test__slist_same_slist_iterator_type__invalid_iterator_iterator_type),\
    UT_CASE(test__slist_same_slist_iterator_type__same_type_belong_to_slist),\
    UT_CASE(test__slist_same_slist_iterator_type__same_type_not_belong_to_slist),\
    UT_CASE(test__slist_same_slist_iterator_type__not_same_type)

#endif /* _UT_CSTL_SLIST_AUX_H_ */

