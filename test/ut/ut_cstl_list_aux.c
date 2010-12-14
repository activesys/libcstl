#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/cstl_iterator.h"
#include "cstl/cstl_list_iterator.h"
#include "cstl/clist.h"
#include "cstl_list_aux.h"
#include "cstl/cvector.h"
#include "cstl/cstring.h"

#include "ut_def.h"
#include "ut_cstl_list_iterator.h"

UT_SUIT_DEFINATION(cstl_list_aux, _list_is_created)

/*
 * test _list_is_created
 */
UT_CASE_DEFINATION(_list_is_created)
void test__list_is_created__null_list_container(void** state)
{
    expect_assert_failure(_list_is_created(NULL));
}

void test__list_is_created__invalid_type_style(void** state)
{
    list_t* plist = create_list(int);

    plist->_t_typeinfo._t_style = 9999;
    assert_false(_list_is_created(plist));

    plist->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    list_destroy(plist);
}

void test__list_is_created__invalid_type_pointer(void** state)
{
    void* pv_tmp = NULL;
    list_t* plist = create_list(int);

    pv_tmp = plist->_t_typeinfo._pt_type;
    plist->_t_typeinfo._pt_type = NULL;
    assert_false(_list_is_created(plist));

    plist->_t_typeinfo._pt_type = pv_tmp;
    list_destroy(plist);
}

void test__list_is_created__null_node(void** state)
{
    list_t* plist = create_list(int);
    plist->_pt_node = 0x224;

    assert_false(_list_is_created(plist));

    plist->_pt_node = NULL;
    list_destroy(plist);
}

void test__list_is_created__uninited_allocator(void** state)
{
    list_t* plist = create_list(int);
    plist->_t_allocater._pby_mempool = 0x444;

    assert_false(_list_is_created(plist));

    plist->_t_allocater._pby_mempool = NULL;
    list_destroy(plist);
}

void test__list_is_created__successfully(void** state)
{
    list_t* plist = create_list(int);

    assert_true(_list_is_created(plist));

    list_destroy(plist);
}

/*
 * test _list_is_inited
 */
UT_CASE_DEFINATION(_list_is_inited)
void test__list_is_inited__null_list_container(void** state)
{
    expect_assert_failure(_list_is_inited(NULL));
}

void test__list_is_inited__invalid_type_styple(void** state)
{
    list_t* plist = create_list(int);
    list_init(plist);

    plist->_t_typeinfo._t_style = 9999;
    assert_false(_list_is_inited(plist));

    plist->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    list_destroy(plist);
}

void test__list_is_inited__invalid_type_pointer(void** state)
{
    void* pv_tmp = NULL;
    list_t* plist = create_list(int);
    list_init(plist);

    pv_tmp = plist->_t_typeinfo._pt_type;
    plist->_t_typeinfo._pt_type = NULL;
    assert_false(_list_is_inited(plist));

    plist->_t_typeinfo._pt_type = pv_tmp;
    list_destroy(plist);
}

void test__list_is_inited__null_node(void** state)
{
    void* pv_tmp = NULL;
    list_t* plist = create_list(int);

    list_init(plist);
    pv_tmp = plist->_pt_node;
    plist->_pt_node = NULL;
    assert_false(_list_is_inited(plist));

    plist->_pt_node = pv_tmp;
    list_destroy(plist);
}

void test__list_is_inited__invalid_node_prev_pointer(void** state)
{
    list_t* plist = create_list(int);
    list_init(plist);

    plist->_pt_node->_pt_prev = NULL;

    assert_false(_list_is_inited(plist));

    plist->_pt_node->_pt_prev = plist->_pt_node;
    list_destroy(plist);
}

void test__list_is_inited__invalid_node_next_pointer(void** state)
{
    list_t* plist = create_list(int);
    list_init(plist);

    plist->_pt_node->_pt_next = NULL;

    assert_false(_list_is_inited(plist));

    plist->_pt_node->_pt_next = plist->_pt_node;
    list_destroy(plist);
}

void test__list_is_inited__init_empty(void** state)
{
    list_t* plist = create_list(int);
    list_init(plist);

    assert_true(_list_is_inited(plist));

    list_destroy(plist);
}

void test__list_is_inited__init_non_empty(void** state)
{
    list_t* plist = create_list(int);
    list_init_n(plist, 10);

    assert_true(_list_is_inited(plist));

    list_destroy(plist);
}

/*
 * test _list_iterator_belong_to_list
 */
UT_CASE_DEFINATION(_list_iterator_belong_to_list)
void test__list_iterator_belong_to_list__null_list_container(void** state)
{
    list_t* plist = create_list(int);
    list_init(plist);

    expect_assert_failure(_list_iterator_belong_to_list(NULL, list_begin(plist)));

    list_destroy(plist);
}

void test__list_iterator_belong_to_list__non_inited_list_container(void** state)
{
    list_iterator_t it_iter = _create_list_iterator();
    list_t* plist = create_list(int);

    expect_assert_failure(_list_iterator_belong_to_list(plist, it_iter));

    list_destroy(plist);
}

void test__list_iterator_belong_to_list__invalid_iter_container_type(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);
    list_init(plist);

    it_iter = list_begin(plist);
    it_iter._t_containertype = 999;
    expect_assert_failure(_list_iterator_belong_to_list(plist, it_iter));

    list_destroy(plist);
}

void test__list_iterator_belong_to_list__invalid_iter_iterator_type(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);
    list_init(plist);

    it_iter = list_begin(plist);
    it_iter._t_iteratortype = 884;
    expect_assert_failure(_list_iterator_belong_to_list(plist, it_iter));

    list_destroy(plist);
}

void test__list_iterator_belong_to_list__invalid_iter_container_pointer(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);
    list_init(plist);

    it_iter = list_begin(plist);
    it_iter._pt_container = 0x23423;
    expect_assert_failure(_list_iterator_belong_to_list(plist, it_iter));

    list_destroy(plist);
}

void test__list_iterator_belong_to_list__not_belong_to_list(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);
    list_init(plist);

    it_iter = list_begin(plist);
    it_iter._t_pos._pc_corepos = 0x9378;
    assert_false(_list_iterator_belong_to_list(plist, it_iter));

    list_destroy(plist);
}

void test__list_iterator_belong_to_list__belong_to_list_begin(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);
    list_init_n(plist, 10);

    it_iter = list_begin(plist);
    assert_true(_list_iterator_belong_to_list(plist, it_iter));

    list_destroy(plist);
}

void test__list_iterator_belong_to_list__belong_to_list_middle(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);
    list_init_n(plist, 10);

    it_iter = iterator_next(list_begin(plist));
    assert_true(_list_iterator_belong_to_list(plist, it_iter));

    list_destroy(plist);
}

void test__list_iterator_belong_to_list__belong_to_list_end(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);
    list_init_n(plist, 10);

    it_iter = list_end(plist);
    assert_true(_list_iterator_belong_to_list(plist, it_iter));

    list_destroy(plist);
}

/*
 * test _list_same_type
 */
UT_CASE_DEFINATION(_list_same_type)
void test__list_same_type__null_first(void** state)
{
    list_t* plist = create_list(int);

    expect_assert_failure(_list_same_type(NULL, plist));

    list_destroy(plist);
}

void test__list_same_type__null_second(void** state)
{
    list_t* plist = create_list(int);

    expect_assert_failure(_list_same_type(plist, NULL));

    list_destroy(plist);
}

void test__list_same_type__non_created_first(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init(plist_first);
    plist_first->_pt_node->_pt_next = NULL;
    expect_assert_failure(_list_same_type(plist_first, plist_second));

    plist_first->_pt_node->_pt_next = plist_first->_pt_node;
    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test__list_same_type__non_created_second(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init(plist_second);
    plist_second->_pt_node->_pt_next = NULL;
    expect_assert_failure(_list_same_type(plist_first, plist_second));

    plist_second->_pt_node->_pt_next = plist_second->_pt_node;
    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test__list_same_type__same_c_builtin(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    assert_true(_list_same_type(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test__list_same_type__same_c_builtin_dup(void** state)
{
    list_t* plist_first = create_list(signed long int);
    list_t* plist_second = create_list(long);
    list_init(plist_first);

    assert_true(_list_same_type(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test__list_same_type__not_same_c_builtin(void** state)
{
    list_t* plist_first = create_list(signed long int);
    list_t* plist_second = create_list(unsigned long);
    list_init_n(plist_first, 10);
    list_init_elem(plist_second, 10, 100);

    assert_false(_list_same_type(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test__list_same_type__same_libcstl_builtin(void** state)
{
    list_t* plist_first = create_list(list_t<int>);
    list_t* plist_second = create_list(list_t<signed>);

    assert_true(_list_same_type(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test__list_same_type__same_libcstl_builtin_dup(void** state)
{
    list_t* plist_first = create_list(list_iterator_t);
    list_t* plist_second = create_list(vector_iterator_t);

    assert_true(_list_same_type(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test__list_same_type__not_same_libcstl_builtin_container(void** state)
{
    list_t* plist_first = create_list(vector_t<int>);
    list_t* plist_second = create_list(list_t<int>);

    assert_false(_list_same_type(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test__list_same_type__not_same_libcstl_builtin_elem(void** state)
{
    list_t* plist_first = create_list(vector_t<int>);
    list_t* plist_second = create_list(vector_t<char>);

    assert_false(_list_same_type(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test__list_same_type__not_same_libcstl_builtin_iter(void** state)
{
    list_t* plist_first = create_list(list_iterator_t);
    list_t* plist_second = create_list(vector_t<char>);

    assert_false(_list_same_type(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test__list_same_type__not_same_libcstl_builtin_string(void** state)
{
    list_t* plist_first = create_list(string_t);
    list_t* plist_second = create_list(vector_t<char>);

    assert_false(_list_same_type(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test__list_same_type__not_same_c_libcstl_builtin(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(vector_t<int>);

    assert_false(_list_same_type(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

typedef struct _tag_test__list_same_type__same_user_defined
{
    int n_elem;
}_test__list_same_type__same_user_defined_t;

void test__list_same_type__same_user_defined(void** state)
{
    list_t* plist_first = NULL;
    list_t* plist_second = NULL;
    type_register(struct _tag_test__list_same_type__same_user_defined, NULL, NULL, NULL, NULL);
    type_duplicate(struct _tag_test__list_same_type__same_user_defined, _test__list_same_type__same_user_defined_t);
    plist_first = create_list(_test__list_same_type__same_user_defined_t);
    plist_second = create_list(_test__list_same_type__same_user_defined_t);

    assert_true(_list_same_type(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test__list_same_type__same_user_defined_dup(void** state)
{
    list_t* plist_first = create_list(_test__list_same_type__same_user_defined_t);
    list_t* plist_second = create_list(struct _tag_test__list_same_type__same_user_defined);

    assert_true(_list_same_type(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test__list_same_type__not_same_c_user_define(void** state)
{
    list_t* plist_first = create_list(_test__list_same_type__same_user_defined_t);
    list_t* plist_second = create_list(double);

    assert_false(_list_same_type(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test__list_same_type__not_same_libcstl_user_define(void** state)
{
    list_t* plist_first = create_list(_test__list_same_type__same_user_defined_t);
    list_t* plist_second = create_list(iterator_t);

    assert_false(_list_same_type(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

/*
 * test _list_same_list_iterator_type
 */
UT_CASE_DEFINATION(_list_same_list_iterator_type)
void test__list_same_list_iterator_type__null_list_container(void** state)
{
    list_t* plist = create_list(int);
    list_init(plist);

    expect_assert_failure(_list_same_list_iterator_type(NULL, list_begin(plist)));

    list_destroy(plist);
}

void test__list_same_list_iterator_type__invalid_iterator_null_container(void** state)
{
    list_t* plist = create_list(int);
    list_iterator_t it_iter;

    list_init(plist);
    it_iter = list_begin(plist);
    it_iter._pt_container = NULL;
    expect_assert_failure(_list_same_list_iterator_type(plist, it_iter));

    list_destroy(plist);
}

void test__list_same_list_iterator_type__invalid_iterator_container_type(void** state)
{
    list_t* plist = create_list(int);
    list_iterator_t it_iter;

    list_init(plist);
    it_iter = list_begin(plist);
    it_iter._t_containertype = 2823;
    expect_assert_failure(_list_same_list_iterator_type(plist, it_iter));

    list_destroy(plist);
}

void test__list_same_list_iterator_type__invalid_iterator_iterator_type(void** state)
{
    list_t* plist = create_list(int);
    list_iterator_t it_iter;

    list_init(plist);
    it_iter = list_begin(plist);
    it_iter._t_iteratortype = 222;
    expect_assert_failure(_list_same_list_iterator_type(plist, it_iter));

    list_destroy(plist);
}

void test__list_same_list_iterator_type__same_type_belong_to_list(void** state)
{
    list_t* plist = create_list(int);
    list_iterator_t it_iter;

    list_init(plist);
    it_iter = list_begin(plist);
    assert_true(_list_same_list_iterator_type(plist, it_iter));

    list_destroy(plist);
}

void test__list_same_list_iterator_type__same_type_not_belong_to_list(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);
    list_iterator_t it_iter;

    list_init(plist_second);
    it_iter = list_begin(plist_second);
    assert_true(_list_same_list_iterator_type(plist_first, it_iter));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test__list_same_list_iterator_type__not_same_type(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(double);
    list_iterator_t it_iter;

    list_init(plist_second);
    it_iter = list_begin(plist_second);
    assert_false(_list_same_list_iterator_type(plist_first, it_iter));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

/*
 * test _list_get_varg_value_auxiliary
 */
UT_CASE_DEFINATION(_list_get_varg_value_auxiliary)
static void _wrapper_list_get_varg_value_auxiliary(list_t* plist_list, listnode_t* pt_node, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, pt_node);
    _list_get_varg_value_auxiliary(plist_list, val_elemlist, pt_node);
    va_end(val_elemlist);
}

void test__list_get_varg_value_auxiliary__null_list_container(void** state)
{
    listnode_t node;
    expect_assert_failure(_wrapper_list_get_varg_value_auxiliary(NULL, &node, 100));
}

void test__list_get_varg_value_auxiliary__null_node(void** state)
{
    list_t* plist = create_list(int);

    expect_assert_failure(_wrapper_list_get_varg_value_auxiliary(plist, NULL, 100));

    list_destroy(plist);
}

void test__list_get_varg_value_auxiliary__non_created_list_containter(void** state)
{
    listnode_t node;
    list_t* plist = create_list(int);
    list_init(plist);

    plist->_pt_node->_pt_next = NULL;
    expect_assert_failure(_wrapper_list_get_varg_value_auxiliary(plist, &node, 100));

    plist->_pt_node->_pt_next = plist->_pt_node;
    list_destroy(plist);
}

void test__list_get_varg_value_auxiliary__c_builtin(void** state)
{
    listnode_t* pt_node = NULL;
    list_t* plist = create_list(int);
    list_init(plist);
    pt_node = malloc(_LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(plist)));

    _wrapper_list_get_varg_value_auxiliary(plist, pt_node, 100);
    assert_true(*(int*)pt_node->_pc_data == 100);

    free(pt_node);
    list_destroy(plist);
}

void test__list_get_varg_value_auxiliary__cstr(void** state)
{
    listnode_t* pt_node = NULL;
    list_t* plist = create_list(char*);
    list_init(plist);
    pt_node = malloc(_LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(plist)));

    _wrapper_list_get_varg_value_auxiliary(plist, pt_node, "abcdefg");
    assert_true(strcmp(string_c_str((string_t*)pt_node->_pc_data), "abcdefg") == 0);

    free(pt_node);
    list_destroy(plist);
}

void test__list_get_varg_value_auxiliary__libcstl_builtin(void** state)
{
    listnode_t* pt_node = NULL;
    list_t* plist = create_list(vector_t<int>);
    vector_t* pvec = create_vector(int);
    vector_init_elem(pvec, 10, 100);
    list_init(plist);
    pt_node = malloc(_LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(plist)));

    _wrapper_list_get_varg_value_auxiliary(plist, pt_node, pvec);
    assert_true(vector_equal((vector_t*)pt_node->_pc_data, pvec));

    free(pt_node);
    list_destroy(plist);
    vector_destroy(pvec);
}

void test__list_get_varg_value_auxiliary__user_define(void** state)
{
    typedef struct _tag_test__list_get_varg_value_auxiliary__user_define
    {
        int n_elem;
    }_test__list_get_varg_value_auxiliary__user_define_t;

    listnode_t* pt_node = NULL;
    list_t* plist = NULL;
    _test__list_get_varg_value_auxiliary__user_define_t t_use;

    type_register(_test__list_get_varg_value_auxiliary__user_define_t, NULL, NULL, NULL, NULL);
    plist = create_list(_test__list_get_varg_value_auxiliary__user_define_t);
    list_init(plist);
    pt_node = malloc(_LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(plist)));
    t_use.n_elem = 10000;

    _wrapper_list_get_varg_value_auxiliary(plist, pt_node, &t_use);
    assert_true(((_test__list_get_varg_value_auxiliary__user_define_t*)pt_node->_pc_data)->n_elem == t_use.n_elem);

    free(pt_node);
    list_destroy(plist);
}

/*
 * test _list_destroy_varg_value_auxiliary
 */
UT_CASE_DEFINATION(_list_destroy_varg_value_auxiliary)
void test__list_destroy_varg_value_auxiliary__null_list_container(void** state)
{
    listnode_t node;
    expect_assert_failure(_list_destroy_varg_value_auxiliary(NULL, &node));
}

void test__list_destroy_varg_value_auxiliary__non_created_list_container(void** state)
{
    listnode_t node;
    list_t* plist = create_list(int);
    list_init(plist);
    plist->_pt_node->_pt_next = NULL;
    expect_assert_failure(_list_destroy_varg_value_auxiliary(plist, &node));

    plist->_pt_node->_pt_next = plist->_pt_node;
    list_destroy(plist);
}

void test__list_destroy_varg_value_auxiliary__null_node(void** state)
{
    list_t* plist = create_list(int);
    list_init(plist);
    expect_assert_failure(_list_destroy_varg_value_auxiliary(plist, NULL));

    list_destroy(plist);
}

void test__list_destroy_varg_value_auxiliary__successfully(void** state)
{
    listnode_t* pt_node = NULL;
    list_t* plist = create_list(int);
    list_init(plist);
    pt_node = malloc(_LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(plist)));
    _list_destroy_varg_value_auxiliary(plist, pt_node);

    free(pt_node);
    list_destroy(plist);
}

/*
 * test _list_init_node_auxiliary
 */
UT_CASE_DEFINATION(_list_init_node_auxiliary)
void test__list_init_node_auxiliary__null_list_container(void** state)
{
    listnode_t node;
    expect_assert_failure(_list_init_node_auxiliary(NULL, &node));
}

void test__list_init_node_auxiliary__null_node(void** state)
{
    list_t* plist = create_list(int);

    expect_assert_failure(_list_init_node_auxiliary(plist, NULL));

    list_destroy(plist);
}

void test__list_init_node_auxiliary__non_created_list_containter(void** state)
{
    listnode_t node;
    list_t* plist = create_list(int);
    list_init(plist);

    plist->_pt_node->_pt_next = NULL;
    expect_assert_failure(_list_init_node_auxiliary(plist, &node));

    plist->_pt_node->_pt_next = plist->_pt_node;
    list_destroy(plist);
}

void test__list_init_node_auxiliary__c_builtin(void** state)
{
    listnode_t* pt_node = NULL;
    list_t* plist = create_list(int);
    list_init(plist);
    pt_node = malloc(_LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(plist)));

    _list_init_node_auxiliary(plist, pt_node);
    assert_true(*(int*)pt_node->_pc_data == 0);

    free(pt_node);
    list_destroy(plist);
}

void test__list_init_node_auxiliary__cstr(void** state)
{
    listnode_t* pt_node = NULL;
    list_t* plist = create_list(char*);
    list_init(plist);
    pt_node = malloc(_LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(plist)));

    _list_init_node_auxiliary(plist, pt_node);
    assert_true(strcmp(string_c_str((string_t*)pt_node->_pc_data), "") == 0);

    free(pt_node);
    list_destroy(plist);
}

void test__list_init_node_auxiliary__libcstl_builtin(void** state)
{
    listnode_t* pt_node = NULL;
    list_t* plist = create_list(vector_t<int>);
    list_init(plist);
    pt_node = malloc(_LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(plist)));

    _list_init_node_auxiliary(plist, pt_node);
    assert_true(_vector_is_inited((vector_t*)pt_node->_pc_data));

    free(pt_node);
    list_destroy(plist);
}

void test__list_init_node_auxiliary__user_define(void** state)
{
    typedef struct _tag_test__list_init_node_auxiliary__user_define
    {
        int n_elem;
    }_test__list_init_node_auxiliary__user_define_t;

    listnode_t* pt_node = NULL;
    list_t* plist = NULL;

    type_register(_test__list_init_node_auxiliary__user_define_t, NULL, NULL, NULL, NULL);
    plist = create_list(_test__list_init_node_auxiliary__user_define_t);
    list_init(plist);
    pt_node = malloc(_LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(plist)));

    _list_init_node_auxiliary(plist, pt_node);
    assert_true(((_test__list_init_node_auxiliary__user_define_t*)pt_node->_pc_data)->n_elem == 0);

    free(pt_node);
    list_destroy(plist);
}
