#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/citerator.h"
#include "cstl/cstl_list_iterator.h"
#include "cstl/clist.h"
#include "cstl_list_aux.h"
#include "cstl/cvector.h"
#include "cstl/cstring.h"
#include "cstl/cfunctional.h"
#include "cstl_vector_aux.h"

#include "ut_def.h"
#include "ut_cstl_list_aux.h"

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
    plist->_pt_node = (_listnode_t*)0x224;

    assert_false(_list_is_created(plist));

    plist->_pt_node = NULL;
    list_destroy(plist);
}

void test__list_is_created__uninited_allocator(void** state)
{
    list_t* plist = create_list(int);

#ifdef CSTL_MEMORY_MANAGEMENT
    plist->_t_allocator._pby_mempool = (_byte_t*)0x444;
    assert_false(_list_is_created(plist));
    plist->_t_allocator._pby_mempool = NULL;
#else
    assert_true(_list_is_created(plist));
#endif
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
    it_iter._pt_container = (void*)0x23423;
    expect_assert_failure(_list_iterator_belong_to_list(plist, it_iter));

    list_destroy(plist);
}

void test__list_iterator_belong_to_list__not_belong_to_list(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);
    list_init(plist);

    it_iter = list_begin(plist);
    it_iter._t_pos._pby_corepos = (_byte_t*)0x9378;
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

void test__list_same_type__same_container(void** state)
{
    list_t* plist = create_list(int);
    list_init(plist);

    assert_true(_list_same_type(plist, plist));

    list_destroy(plist);
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
 * test _list_same_iterator_type
 */
UT_CASE_DEFINATION(_list_same_iterator_type)
void test__list_same_iterator_type__null_list_container(void** state)
{
    list_t* plist = create_list(int);
    list_init(plist);

    expect_assert_failure(_list_same_iterator_type(NULL, list_begin(plist)));

    list_destroy(plist);
}

void test__list_same_iterator_type__invalid_iterator_null_container(void** state)
{
    list_t* plist = create_list(int);
    list_iterator_t it_iter;

    list_init(plist);
    it_iter = list_begin(plist);
    it_iter._pt_container = NULL;
    expect_assert_failure(_list_same_iterator_type(plist, it_iter));

    list_destroy(plist);
}

void test__list_same_iterator_type__invalid_iterator_container_type(void** state)
{
    list_t* plist = create_list(int);
    list_iterator_t it_iter;

    list_init(plist);
    it_iter = list_begin(plist);
    it_iter._t_containertype = 2823;
    expect_assert_failure(_list_same_iterator_type(plist, it_iter));

    list_destroy(plist);
}

void test__list_same_iterator_type__invalid_iterator_iterator_type(void** state)
{
    list_t* plist = create_list(int);
    list_iterator_t it_iter;

    list_init(plist);
    it_iter = list_begin(plist);
    it_iter._t_iteratortype = 222;
    expect_assert_failure(_list_same_iterator_type(plist, it_iter));

    list_destroy(plist);
}

void test__list_same_iterator_type__same_type_belong_to_list(void** state)
{
    list_t* plist = create_list(int);
    list_iterator_t it_iter;

    list_init(plist);
    it_iter = list_begin(plist);
    assert_true(_list_same_iterator_type(plist, it_iter));

    list_destroy(plist);
}

void test__list_same_iterator_type__same_type_not_belong_to_list(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);
    list_iterator_t it_iter;

    list_init(plist_second);
    it_iter = list_begin(plist_second);
    assert_true(_list_same_iterator_type(plist_first, it_iter));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test__list_same_iterator_type__not_same_type(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(double);
    list_iterator_t it_iter;

    list_init(plist_second);
    it_iter = list_begin(plist_second);
    assert_false(_list_same_iterator_type(plist_first, it_iter));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test__list_same_iterator_type__same_type_not_list_iterator(void** state)
{
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);

    vector_init(pvec);
    assert_true(_list_same_iterator_type(plist, vector_begin(pvec)));

    list_destroy(plist);
    vector_destroy(pvec);
}

void test__list_same_iterator_type__not_same_type_not_list_iterator(void** state)
{
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(double);

    vector_init(pvec);
    assert_false(_list_same_iterator_type(plist, vector_begin(pvec)));

    list_destroy(plist);
    vector_destroy(pvec);
}

/*
 * test _list_get_varg_value_auxiliary
 */
UT_CASE_DEFINATION(_list_get_varg_value_auxiliary)
static void _wrapper_list_get_varg_value_auxiliary(list_t* plist_list, _listnode_t* pt_node, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, pt_node);
    _list_get_varg_value_auxiliary(plist_list, val_elemlist, pt_node);
    va_end(val_elemlist);
}

void test__list_get_varg_value_auxiliary__null_list_container(void** state)
{
    _listnode_t node;
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
    _listnode_t node;
    list_t* plist = create_list(int);
    list_init(plist);

    plist->_pt_node->_pt_next = NULL;
    expect_assert_failure(_wrapper_list_get_varg_value_auxiliary(plist, &node, 100));

    plist->_pt_node->_pt_next = plist->_pt_node;
    list_destroy(plist);
}

void test__list_get_varg_value_auxiliary__c_builtin(void** state)
{
    _listnode_t* pt_node = NULL;
    list_t* plist = create_list(int);
    list_init(plist);
    pt_node = malloc(_LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(plist)));

    _wrapper_list_get_varg_value_auxiliary(plist, pt_node, 100);
    assert_true(*(int*)pt_node->_pby_data == 100);

    free(pt_node);
    list_destroy(plist);
}

void test__list_get_varg_value_auxiliary__cstr(void** state)
{
    _listnode_t* pt_node = NULL;
    list_t* plist = create_list(char*);
    list_init(plist);
    pt_node = malloc(_LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(plist)));

    _wrapper_list_get_varg_value_auxiliary(plist, pt_node, "abcdefg");
    assert_true(strcmp(string_c_str((string_t*)pt_node->_pby_data), "abcdefg") == 0);

    _string_destroy_auxiliary(pt_node->_pby_data);
    free(pt_node);
    list_destroy(plist);
}

void test__list_get_varg_value_auxiliary__libcstl_builtin(void** state)
{
    _listnode_t* pt_node = NULL;
    list_t* plist = create_list(vector_t<int>);
    vector_t* pvec = create_vector(int);
    vector_init_elem(pvec, 10, 100);
    list_init(plist);
    pt_node = malloc(_LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(plist)));

    _wrapper_list_get_varg_value_auxiliary(plist, pt_node, pvec);
    assert_true(vector_equal((vector_t*)pt_node->_pby_data, pvec));

    _vector_destroy_auxiliary((vector_t*)pt_node->_pby_data);
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

    _listnode_t* pt_node = NULL;
    list_t* plist = NULL;
    _test__list_get_varg_value_auxiliary__user_define_t t_use;

    type_register(_test__list_get_varg_value_auxiliary__user_define_t, NULL, NULL, NULL, NULL);
    plist = create_list(_test__list_get_varg_value_auxiliary__user_define_t);
    list_init(plist);
    pt_node = malloc(_LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(plist)));
    t_use.n_elem = 10000;

    _wrapper_list_get_varg_value_auxiliary(plist, pt_node, &t_use);
    assert_true(((_test__list_get_varg_value_auxiliary__user_define_t*)pt_node->_pby_data)->n_elem == t_use.n_elem);

    free(pt_node);
    list_destroy(plist);
}

/*
 * test _list_destroy_varg_value_auxiliary
 */
UT_CASE_DEFINATION(_list_destroy_varg_value_auxiliary)
void test__list_destroy_varg_value_auxiliary__null_list_container(void** state)
{
    _listnode_t node;
    expect_assert_failure(_list_destroy_varg_value_auxiliary(NULL, &node));
}

void test__list_destroy_varg_value_auxiliary__non_created_list_container(void** state)
{
    _listnode_t node;
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
    _listnode_t* pt_node = NULL;
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
    _listnode_t node;
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
    _listnode_t node;
    list_t* plist = create_list(int);
    list_init(plist);

    plist->_pt_node->_pt_next = NULL;
    expect_assert_failure(_list_init_node_auxiliary(plist, &node));

    plist->_pt_node->_pt_next = plist->_pt_node;
    list_destroy(plist);
}

void test__list_init_node_auxiliary__c_builtin(void** state)
{
    _listnode_t* pt_node = NULL;
    list_t* plist = create_list(int);
    list_init(plist);
    pt_node = malloc(_LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(plist)));

    _list_init_node_auxiliary(plist, pt_node);
    assert_true(*(int*)pt_node->_pby_data == 0);

    free(pt_node);
    list_destroy(plist);
}

void test__list_init_node_auxiliary__cstr(void** state)
{
    _listnode_t* pt_node = NULL;
    list_t* plist = create_list(char*);
    list_init(plist);
    pt_node = malloc(_LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(plist)));

    _list_init_node_auxiliary(plist, pt_node);
    assert_true(strcmp(string_c_str((string_t*)pt_node->_pby_data), "") == 0);

    _list_destroy_varg_value_auxiliary(plist, pt_node);
    free(pt_node);
    list_destroy(plist);
}

void test__list_init_node_auxiliary__libcstl_builtin(void** state)
{
    _listnode_t* pt_node = NULL;
    list_t* plist = create_list(vector_t<int>);
    list_init(plist);
    pt_node = malloc(_LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(plist)));

    _list_init_node_auxiliary(plist, pt_node);
    assert_true(_vector_is_inited((vector_t*)pt_node->_pby_data));

    free(pt_node);
    list_destroy(plist);
}

void test__list_init_node_auxiliary__user_define(void** state)
{
    typedef struct _tag_test__list_init_node_auxiliary__user_define
    {
        int n_elem;
    }_test__list_init_node_auxiliary__user_define_t;

    _listnode_t* pt_node = NULL;
    list_t* plist = NULL;

    type_register(_test__list_init_node_auxiliary__user_define_t, NULL, NULL, NULL, NULL);
    plist = create_list(_test__list_init_node_auxiliary__user_define_t);
    list_init(plist);
    pt_node = malloc(_LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(plist)));

    _list_init_node_auxiliary(plist, pt_node);
    assert_true(((_test__list_init_node_auxiliary__user_define_t*)pt_node->_pby_data)->n_elem == 0);

    free(pt_node);
    list_destroy(plist);
}

/*
 * test _list_transfer
 */
UT_CASE_DEFINATION(_list_transfer)
void test__list_transfer__invalid_pos(void** state)
{
    list_t* plist = create_list(int);
    list_iterator_t it_pos;
    list_iterator_t it_begin;
    list_iterator_t it_end;

    list_init_n(plist, 10);
    it_pos = list_begin(plist);
    it_begin = list_begin(plist);
    it_end = list_end(plist);

    it_pos._pt_container = NULL;
    expect_assert_failure(_list_transfer(it_pos, it_begin, it_end));

    list_destroy(plist);
}

void test__list_transfer__invalid_begin(void** state)
{
    list_t* plist = create_list(int);
    list_iterator_t it_pos;
    list_iterator_t it_begin;
    list_iterator_t it_end;

    list_init_n(plist, 10);
    it_pos = list_begin(plist);
    it_begin = list_begin(plist);
    it_end = list_end(plist);

    it_begin._t_containertype = 23984;
    expect_assert_failure(_list_transfer(it_pos, it_begin, it_end));

    list_destroy(plist);
}

void test__list_transfer__invalid_end(void** state)
{
    list_t* plist = create_list(int);
    list_iterator_t it_pos;
    list_iterator_t it_begin;
    list_iterator_t it_end;

    list_init_n(plist, 10);
    it_pos = list_begin(plist);
    it_begin = list_begin(plist);
    it_end = list_end(plist);

    it_end._t_iteratortype = 345676;
    expect_assert_failure(_list_transfer(it_pos, it_begin, it_end));

    list_destroy(plist);
}

void test__list_transfer__invalid_range_not_same_list(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);
    list_iterator_t it_pos;
    list_iterator_t it_begin;
    list_iterator_t it_end;

    list_init_n(plist_first, 10);
    list_init_n(plist_second, 24);
    it_pos = list_begin(plist_first);
    it_begin = list_begin(plist_first);
    it_end = list_end(plist_second);

    expect_assert_failure(_list_transfer(it_pos, it_begin, it_end));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test__list_transfer__invalid_range_end_before_begin(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);
    list_iterator_t it_pos;
    list_iterator_t it_begin;
    list_iterator_t it_end;

    list_init_n(plist_first, 10);
    list_init_n(plist_second, 24);
    it_pos = list_begin(plist_first);
    it_begin = list_begin(plist_second);
    it_end = list_end(plist_second);

    expect_assert_failure(_list_transfer(it_pos, it_end, it_begin));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test__list_transfer__pos_range_not_same_type(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(double);
    list_iterator_t it_pos;
    list_iterator_t it_begin;
    list_iterator_t it_end;

    list_init_n(plist_first, 10);
    list_init_n(plist_second, 24);
    it_pos = list_begin(plist_first);
    it_begin = list_begin(plist_second);
    it_end = list_end(plist_second);

    expect_assert_failure(_list_transfer(it_pos, it_begin, it_end));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test__list_transfer__does_nothing_empty_range(void** state)
{
    size_t i = 0;
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);
    list_iterator_t it_pos;
    list_iterator_t it_begin;
    list_iterator_t it_end;

    list_init_elem(plist_first, 10, 100);
    list_init_n(plist_second, 24);
    it_pos = list_begin(plist_first);
    it_begin = list_begin(plist_second);
    it_end = list_begin(plist_second);

    assert_true(list_size(plist_first) == 10);
    assert_true(list_size(plist_second) == 24);
    _list_transfer(it_pos, it_begin, it_end);
    assert_true(list_size(plist_first) == 10);
    assert_true(list_size(plist_second) == 24);
    for(it_pos = list_begin(plist_first), i = 0;
        !iterator_equal(it_pos, list_end(plist_first));
        it_pos = iterator_next(it_pos), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_pos) == 100);
    }
    for(it_pos = list_begin(plist_second), i = 0;
        !iterator_equal(it_pos, list_end(plist_second));
        it_pos = iterator_next(it_pos), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_pos) == 0);
    }

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test__list_transfer__successfully_begin_begin(void** state)
{
    size_t i = 0;
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);
    list_iterator_t it_pos;
    list_iterator_t it_begin;
    list_iterator_t it_end;

    list_init_elem(plist_first, 10, 100);
    list_init_n(plist_second, 24);
    it_pos = list_begin(plist_first);
    it_begin = list_begin(plist_second);
    it_end = iterator_advance(it_begin, 4);

    assert_true(list_size(plist_first) == 10);
    assert_true(list_size(plist_second) == 24);

    _list_transfer(it_pos, it_begin, it_end);

    assert_true(list_size(plist_first) == 14);
    assert_true(list_size(plist_second) == 20);
    for(it_pos = list_begin(plist_first), i = 0;
        !iterator_equal(it_pos, list_end(plist_first));
        it_pos = iterator_next(it_pos), ++i)
    {
        if(i < 4)
        {
            assert_true(*(int*)iterator_get_pointer(it_pos) == 0);
        }
        else
        {
            assert_true(*(int*)iterator_get_pointer(it_pos) == 100);
        }
    }

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test__list_transfer__successfully_middle_middle(void** state)
{
    size_t i = 0;
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);
    list_iterator_t it_pos;
    list_iterator_t it_begin;
    list_iterator_t it_end;

    list_init_elem(plist_first, 10, 100);
    list_init_n(plist_second, 24);
    it_pos = iterator_advance(list_begin(plist_first), 5);
    it_begin = iterator_advance(list_begin(plist_second), 5);
    it_end = iterator_advance(it_begin, 4);

    assert_true(list_size(plist_first) == 10);
    assert_true(list_size(plist_second) == 24);

    _list_transfer(it_pos, it_begin, it_end);

    assert_true(list_size(plist_first) == 14);
    assert_true(list_size(plist_second) == 20);
    for(it_pos = list_begin(plist_first), i = 0;
        !iterator_equal(it_pos, list_end(plist_first));
        it_pos = iterator_next(it_pos), ++i)
    {
        if(i > 4 && i < 9)
        {
            assert_true(*(int*)iterator_get_pointer(it_pos) == 0);
        }
        else
        {
            assert_true(*(int*)iterator_get_pointer(it_pos) == 100);
        }
    }

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test__list_transfer__successfully_end(void** state)
{
    size_t i = 0;
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);
    list_iterator_t it_pos;
    list_iterator_t it_begin;
    list_iterator_t it_end;

    list_init_elem(plist_first, 10, 100);
    list_init_n(plist_second, 24);
    it_pos = list_end(plist_first);
    it_end = list_end(plist_second);
    it_begin = iterator_advance(it_end, -4);

    assert_true(list_size(plist_first) == 10);
    assert_true(list_size(plist_second) == 24);

    _list_transfer(it_pos, it_begin, it_end);

    assert_true(list_size(plist_first) == 14);
    assert_true(list_size(plist_second) == 20);
    for(it_pos = list_begin(plist_first), i = 0;
        !iterator_equal(it_pos, list_end(plist_first));
        it_pos = iterator_next(it_pos), ++i)
    {
        if(i > 9)
        {
            assert_true(*(int*)iterator_get_pointer(it_pos) == 0);
        }
        else
        {
            assert_true(*(int*)iterator_get_pointer(it_pos) == 100);
        }
    }

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test__list_transfer__successfully_middle_all(void** state)
{
    size_t i = 0;
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);
    list_iterator_t it_pos;
    list_iterator_t it_begin;
    list_iterator_t it_end;

    list_init_elem(plist_first, 10, 100);
    list_init_n(plist_second, 24);
    it_pos = list_end(plist_first);
    it_begin = list_begin(plist_second);
    it_end = list_end(plist_second);

    assert_true(list_size(plist_first) == 10);
    assert_true(list_size(plist_second) == 24);

    _list_transfer(it_pos, it_begin, it_end);

    assert_true(list_size(plist_first) == 34);
    assert_true(list_size(plist_second) == 0);
    for(it_pos = list_begin(plist_first), i = 0;
        !iterator_equal(it_pos, list_end(plist_first));
        it_pos = iterator_next(it_pos), ++i)
    {
        if(i > 9)
        {
            assert_true(*(int*)iterator_get_pointer(it_pos) == 0);
        }
        else
        {
            assert_true(*(int*)iterator_get_pointer(it_pos) == 100);
        }
    }

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test__list_transfer__same_list_pos_belong_to_range(void** state)
{
    list_t* plist = create_list(int);
    list_iterator_t it_pos;
    list_iterator_t it_begin;
    list_iterator_t it_end;

    list_init_n(plist, 10);
    it_begin = list_begin(plist);
    it_end = list_end(plist);
    it_pos = iterator_next(it_begin);
    expect_assert_failure(_list_transfer(it_pos, it_begin, it_end));

    list_destroy(plist);
}

void test__list_transfer__same_list_does_nothing_empty_range(void** state)
{
    size_t i = 0;
    list_t* plist = create_list(int);
    list_iterator_t it_pos;
    list_iterator_t it_begin;
    list_iterator_t it_end;

    list_init(plist);
    for(i = 0; i < 10; ++i)
    {
        list_push_back(plist, i);
    }
    it_begin = list_end(plist);
    it_end = list_end(plist);
    it_pos = list_begin(plist);
    _list_transfer(it_pos, it_begin, it_end);
    for(it_pos = list_begin(plist), i = 0;
        !iterator_equal(it_pos, list_end(plist));
        it_pos = iterator_next(it_pos), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_pos) == i);
    }

    list_destroy(plist);
}

void test__list_transfer__same_list_does_nothing_pos_equa_to_begin(void** state)
{
    size_t i = 0;
    list_t* plist = create_list(int);
    list_iterator_t it_pos;
    list_iterator_t it_begin;
    list_iterator_t it_end;

    list_init(plist);
    for(i = 0; i < 10; ++i)
    {
        list_push_back(plist, i);
    }
    it_begin = list_begin(plist);
    it_end = list_end(plist);
    it_pos = list_begin(plist);
    _list_transfer(it_pos, it_begin, it_end);
    for(it_pos = list_begin(plist), i = 0;
        !iterator_equal(it_pos, list_end(plist));
        it_pos = iterator_next(it_pos), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_pos) == i);
    }

    list_destroy(plist);
}

void test__list_transfer__same_list_does_nothing_pos_equa_to_end(void** state)
{
    size_t i = 0;
    list_t* plist = create_list(int);
    list_iterator_t it_pos;
    list_iterator_t it_begin;
    list_iterator_t it_end;

    list_init(plist);
    for(i = 0; i < 10; ++i)
    {
        list_push_back(plist, i);
    }
    it_begin = list_begin(plist);
    it_end = list_end(plist);
    it_pos = list_end(plist);
    _list_transfer(it_pos, it_begin, it_end);
    for(it_pos = list_begin(plist), i = 0;
        !iterator_equal(it_pos, list_end(plist));
        it_pos = iterator_next(it_pos), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_pos) == i);
    }

    list_destroy(plist);
}

void test__list_transfer__same_list_begin_middle(void** state)
{
    size_t i = 0;
    list_t* plist = create_list(int);
    list_iterator_t it_pos;
    list_iterator_t it_begin;
    list_iterator_t it_end;

    list_init(plist);
    for(i = 0; i < 10; ++i)
    {
        list_push_back(plist, i);
    }
    it_pos = list_begin(plist);
    it_begin = iterator_next(list_begin(plist));
    it_end = iterator_advance(it_begin, 3);
    _list_transfer(it_pos, it_begin, it_end);

    it_pos = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 1);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 2);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 3);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 0);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 4);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 5);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 6);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 7);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 8);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 9);

    list_destroy(plist);
}

void test__list_transfer__same_list_begin_end(void** state)
{
    size_t i = 0;
    list_t* plist = create_list(int);
    list_iterator_t it_pos;
    list_iterator_t it_begin;
    list_iterator_t it_end;

    list_init(plist);
    for(i = 0; i < 10; ++i)
    {
        list_push_back(plist, i);
    }
    it_pos = list_begin(plist);
    it_begin = iterator_advance(list_begin(plist), 6);
    it_end = list_end(plist);
    _list_transfer(it_pos, it_begin, it_end);

    it_pos = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 6);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 7);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 8);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 9);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 0);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 1);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 2);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 3);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 4);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 5);

    list_destroy(plist);
}

void test__list_transfer__same_list_middle_begin(void** state)
{
    size_t i = 0;
    list_t* plist = create_list(int);
    list_iterator_t it_pos;
    list_iterator_t it_begin;
    list_iterator_t it_end;

    list_init(plist);
    for(i = 0; i < 10; ++i)
    {
        list_push_back(plist, i);
    }
    it_pos = iterator_advance(list_begin(plist), 6);
    it_begin = list_begin(plist);
    it_end = iterator_next(it_begin);
    _list_transfer(it_pos, it_begin, it_end);

    it_pos = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 1);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 2);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 3);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 4);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 5);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 0);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 6);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 7);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 8);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 9);

    list_destroy(plist);
}

void test__list_transfer__same_list_middle_middle(void** state)
{
    size_t i = 0;
    list_t* plist = create_list(int);
    list_iterator_t it_pos;
    list_iterator_t it_begin;
    list_iterator_t it_end;

    list_init(plist);
    for(i = 0; i < 10; ++i)
    {
        list_push_back(plist, i);
    }
    it_pos = iterator_advance(list_begin(plist), 6);
    it_begin = iterator_next(list_begin(plist));
    it_end = iterator_advance(it_begin, 3);
    _list_transfer(it_pos, it_begin, it_end);

    it_pos = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 0);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 4);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 5);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 1);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 2);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 3);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 6);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 7);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 8);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 9);

    list_destroy(plist);
}

void test__list_transfer__same_list_middle_end(void** state)
{
    size_t i = 0;
    list_t* plist = create_list(int);
    list_iterator_t it_pos;
    list_iterator_t it_begin;
    list_iterator_t it_end;

    list_init(plist);
    for(i = 0; i < 10; ++i)
    {
        list_push_back(plist, i);
    }
    it_pos = iterator_advance(list_begin(plist), 6);
    it_begin = iterator_advance(list_end(plist), -2);
    it_end = list_end(plist);
    _list_transfer(it_pos, it_begin, it_end);

    it_pos = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 0);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 1);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 2);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 3);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 4);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 5);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 8);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 9);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 6);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 7);

    list_destroy(plist);
}

void test__list_transfer__same_list_end_begin(void** state)
{
    size_t i = 0;
    list_t* plist = create_list(int);
    list_iterator_t it_pos;
    list_iterator_t it_begin;
    list_iterator_t it_end;

    list_init(plist);
    for(i = 0; i < 10; ++i)
    {
        list_push_back(plist, i);
    }
    it_pos = list_end(plist);
    it_begin = list_begin(plist);
    it_end = iterator_advance(it_begin, 4);
    _list_transfer(it_pos, it_begin, it_end);

    it_pos = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 4);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 5);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 6);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 7);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 8);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 9);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 0);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 1);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 2);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 3);

    list_destroy(plist);
}

void test__list_transfer__same_list_end_middle(void** state)
{
    size_t i = 0;
    list_t* plist = create_list(int);
    list_iterator_t it_pos;
    list_iterator_t it_begin;
    list_iterator_t it_end;

    list_init(plist);
    for(i = 0; i < 10; ++i)
    {
        list_push_back(plist, i);
    }
    it_pos = list_end(plist);
    it_begin = iterator_next(list_begin(plist));
    it_end = iterator_advance(it_begin, 4);
    _list_transfer(it_pos, it_begin, it_end);

    it_pos = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 0);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 5);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 6);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 7);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 8);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 9);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 1);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 2);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 3);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 4);

    list_destroy(plist);
}

/*
 * test _list_swap_node
 */
UT_CASE_DEFINATION(_list_swap_node)
void test__list_swap_node__null_ppt_first(void** state)
{
    _listnode_t node;
    _listnode_t* pt_node = &node;

    expect_assert_failure(_list_swap_node(NULL, &pt_node));
}

void test__list_swap_node__null_pt_first(void** state)
{
    _listnode_t node;
    _listnode_t* pt_first = NULL;
    _listnode_t* pt_second = &node;

    expect_assert_failure(_list_swap_node(&pt_first, &pt_second));
}

void test__list_swap_node__null_ppt_second(void** state)
{
    _listnode_t node;
    _listnode_t* pt_node = &node;

    expect_assert_failure(_list_swap_node(&pt_node, NULL));
}

void test__list_swap_node__null_pt_second(void** state)
{
    _listnode_t node;
    _listnode_t* pt_first = &node;
    _listnode_t* pt_second = NULL;

    expect_assert_failure(_list_swap_node(&pt_first, &pt_second));
}

void test__list_swap_node__first_followed_by_second(void** state)
{
    size_t i = 0;
    list_t* plist = create_list(int);
    _listnode_t* pt_firsttmp = NULL;
    _listnode_t* pt_secondtmp = NULL;
    _listnode_t* pt_first = NULL;
    _listnode_t* pt_second = NULL;
    list_iterator_t it_iter;

    list_init(plist);
    for(i = 0; i < 5; ++i)
    {
        list_push_back(plist, i);
    }
    it_iter = list_begin(plist);
    pt_firsttmp = pt_first = (_listnode_t*)it_iter._t_pos._pby_corepos;
    it_iter = iterator_next(it_iter);
    pt_secondtmp = pt_second = (_listnode_t*)it_iter._t_pos._pby_corepos;

    _list_swap_node(&pt_first, &pt_second);
    assert_true(pt_first == pt_secondtmp);
    assert_true(pt_second == pt_firsttmp);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);

    list_destroy(plist);
}

void test__list_swap_node__second_followed_by_first(void** state)
{
    size_t i = 0;
    list_t* plist = create_list(int);
    _listnode_t* pt_firsttmp = NULL;
    _listnode_t* pt_secondtmp = NULL;
    _listnode_t* pt_first = NULL;
    _listnode_t* pt_second = NULL;
    list_iterator_t it_iter;

    list_init(plist);
    for(i = 0; i < 5; ++i)
    {
        list_push_back(plist, i);
    }
    it_iter = list_begin(plist);
    pt_secondtmp = pt_second = (_listnode_t*)it_iter._t_pos._pby_corepos;
    it_iter = iterator_next(it_iter);
    pt_firsttmp = pt_first = (_listnode_t*)it_iter._t_pos._pby_corepos;

    _list_swap_node(&pt_first, &pt_second);
    assert_true(pt_first == pt_secondtmp);
    assert_true(pt_second == pt_firsttmp);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);

    list_destroy(plist);
}

void test__list_swap_node__first_distanced_by_second(void** state)
{
    size_t i = 0;
    list_t* plist = create_list(int);
    _listnode_t* pt_firsttmp = NULL;
    _listnode_t* pt_secondtmp = NULL;
    _listnode_t* pt_first = NULL;
    _listnode_t* pt_second = NULL;
    list_iterator_t it_iter;

    list_init(plist);
    for(i = 0; i < 5; ++i)
    {
        list_push_back(plist, i);
    }
    it_iter = iterator_next(list_begin(plist));
    pt_firsttmp = pt_first = (_listnode_t*)it_iter._t_pos._pby_corepos;
    it_iter = iterator_advance(it_iter, 2);
    pt_secondtmp = pt_second = (_listnode_t*)it_iter._t_pos._pby_corepos;

    _list_swap_node(&pt_first, &pt_second);
    assert_true(pt_first == pt_secondtmp);
    assert_true(pt_second == pt_firsttmp);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);

    list_destroy(plist);
}

void test__list_swap_node__second_distanced_by_first(void** state)
{
    size_t i = 0;
    list_t* plist = create_list(int);
    _listnode_t* pt_firsttmp = NULL;
    _listnode_t* pt_secondtmp = NULL;
    _listnode_t* pt_first = NULL;
    _listnode_t* pt_second = NULL;
    list_iterator_t it_iter;

    list_init(plist);
    for(i = 0; i < 5; ++i)
    {
        list_push_back(plist, i);
    }
    it_iter = iterator_advance(list_begin(plist), 2);
    pt_secondtmp = pt_second = (_listnode_t*)it_iter._t_pos._pby_corepos;
    it_iter = iterator_advance(it_iter, 2);
    pt_firsttmp = pt_first = (_listnode_t*)it_iter._t_pos._pby_corepos;

    _list_swap_node(&pt_first, &pt_second);
    assert_true(pt_first == pt_secondtmp);
    assert_true(pt_second == pt_firsttmp);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);

    list_destroy(plist);
}

void test__list_swap_node__same_ppt_first_ppt_second(void** state)
{
    size_t i = 0;
    list_t* plist = create_list(int);
    _listnode_t* pt_firsttmp = NULL;
    _listnode_t* pt_secondtmp = NULL;
    _listnode_t* pt_first = NULL;
    _listnode_t* pt_second = NULL;
    list_iterator_t it_iter;

    list_init(plist);
    for(i = 0; i < 5; ++i)
    {
        list_push_back(plist, i);
    }
    it_iter = iterator_advance(list_begin(plist), 2);
    pt_firsttmp = pt_first = pt_secondtmp = pt_second = (_listnode_t*)it_iter._t_pos._pby_corepos;

    _list_swap_node(&pt_first, &pt_first);
    assert_true(pt_first == pt_firsttmp);
    assert_true(pt_second == pt_secondtmp);
    assert_true(pt_first == pt_second);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);

    list_destroy(plist);
}

void test__list_swap_node__same_pt_first_pt_second(void** state)
{
    size_t i = 0;
    list_t* plist = create_list(int);
    _listnode_t* pt_firsttmp = NULL;
    _listnode_t* pt_secondtmp = NULL;
    _listnode_t* pt_first = NULL;
    _listnode_t* pt_second = NULL;
    list_iterator_t it_iter;

    list_init(plist);
    for(i = 0; i < 5; ++i)
    {
        list_push_back(plist, i);
    }
    it_iter = iterator_advance(list_begin(plist), 2);
    pt_firsttmp = pt_first = pt_secondtmp = pt_second = (_listnode_t*)it_iter._t_pos._pby_corepos;

    _list_swap_node(&pt_first, &pt_second);
    assert_true(pt_first == pt_firsttmp);
    assert_true(pt_second == pt_secondtmp);
    assert_true(pt_first == pt_second);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);

    list_destroy(plist);
}

/*
 * test _list_quick_sort
 */
UT_CASE_DEFINATION(_list_quick_sort)

static void _list_quick_sort_int_greater(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    if(*(int*)cpv_first > *(int*)cpv_second)
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}

void test__list_quick_sort__null_list_container(void** state)
{
    list_t* plist = create_list(int);

    list_init(plist);
    assert_true(list_size(plist) == 0);
    expect_assert_failure(_list_quick_sort(NULL, plist->_pt_node->_pt_next, plist->_pt_node->_pt_prev, NULL));

    list_destroy(plist);
}

void test__list_quick_sort__non_inited_list_container(void** state)
{
    list_t* plist = create_list(int);
    list_t* plist_list = create_list(int);

    list_init(plist);
    list_init(plist_list);
    assert_true(list_size(plist) == 0);
    plist_list->_pt_node->_pt_next = NULL;
    expect_assert_failure(_list_quick_sort(plist_list, plist->_pt_node->_pt_next, plist->_pt_node->_pt_prev, NULL));

    plist_list->_pt_node->_pt_next = plist_list->_pt_node;
    list_destroy(plist);
    list_destroy(plist_list);
}

void test__list_quick_sort__null_pt_first(void** state)
{
    list_t* plist = create_list(int);

    list_init(plist);
    assert_true(list_size(plist) == 0);
    expect_assert_failure(_list_quick_sort(plist, NULL, plist->_pt_node->_pt_prev, NULL));

    list_destroy(plist);
}

void test__list_quick_sort__null_pt_second(void** state)
{
    list_t* plist = create_list(int);

    list_init(plist);
    assert_true(list_size(plist) == 0);
    expect_assert_failure(_list_quick_sort(plist, plist->_pt_node->_pt_next, NULL, NULL));

    list_destroy(plist);
}

void test__list_quick_sort__invalid_range_not_belong_to_list(void** state)
{
    list_t* plist = create_list(int);
    list_t* plist_list = create_list(int);

    list_init(plist);
    list_init(plist_list);
    assert_true(list_size(plist) == 0);
    expect_assert_failure(_list_quick_sort(plist_list, plist->_pt_node->_pt_next, plist->_pt_node->_pt_prev, NULL));

    list_destroy(plist);
    list_destroy(plist_list);
}

void test__list_quick_sort__invalid_range(void** state)
{
    list_t* plist = create_list(int);

    list_init_n(plist, 10);
    assert_true(list_size(plist) == 10);
    expect_assert_failure(_list_quick_sort(plist, plist->_pt_node->_pt_prev, plist->_pt_node->_pt_next, NULL));

    list_destroy(plist);
}

void test__list_quick_sort__empty_less(void** state)
{
    list_t* plist = create_list(int);

    list_init(plist);
    assert_true(list_size(plist) == 0);
    _list_quick_sort(plist, plist->_pt_node->_pt_next, plist->_pt_node->_pt_prev, NULL);
    assert_true(list_size(plist) == 0);

    list_destroy(plist);
}

void test__list_quick_sort__empty_greater(void** state)
{
    list_t* plist = create_list(int);

    list_init(plist);
    assert_true(list_size(plist) == 0);
    _list_quick_sort(plist, plist->_pt_node->_pt_next, plist->_pt_node->_pt_prev, _list_quick_sort_int_greater);
    assert_true(list_size(plist) == 0);

    list_destroy(plist);
}

void test__list_quick_sort__1_less(void** state)
{
    list_t* plist = create_list(int);

    list_init_n(plist, 1);
    assert_true(list_size(plist) == 1);
    _list_quick_sort(plist, plist->_pt_node->_pt_next, plist->_pt_node->_pt_prev, NULL);
    assert_true(list_size(plist) == 1);
    assert_true(*(int*)iterator_get_pointer(list_begin(plist)) == 0);

    list_destroy(plist);
}

void test__list_quick_sort__1_greater(void** state)
{
    list_t* plist = create_list(int);

    list_init_n(plist, 1);
    assert_true(list_size(plist) == 1);
    _list_quick_sort(plist, plist->_pt_node->_pt_next, plist->_pt_node->_pt_prev, _list_quick_sort_int_greater);
    assert_true(list_size(plist) == 1);
    assert_true(*(int*)iterator_get_pointer(list_begin(plist)) == 0);

    list_destroy(plist);
}

void test__list_quick_sort__2_equal_less(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_n(plist, 2);
    assert_true(list_size(plist) == 2);
    _list_quick_sort(plist, plist->_pt_node->_pt_next, plist->_pt_node->_pt_prev, NULL);
    assert_true(list_size(plist) == 2);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    list_destroy(plist);
}

void test__list_quick_sort__2_equal_greater(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_n(plist, 2);
    assert_true(list_size(plist) == 2);
    _list_quick_sort(plist, plist->_pt_node->_pt_next, plist->_pt_node->_pt_prev, _list_quick_sort_int_greater);
    assert_true(list_size(plist) == 2);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    list_destroy(plist);
}

void test__list_quick_sort__2_less_less(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 0);
    list_push_back(plist, 1);
    assert_true(list_size(plist) == 2);
    _list_quick_sort(plist, plist->_pt_node->_pt_next, plist->_pt_node->_pt_prev, NULL);
    assert_true(list_size(plist) == 2);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);

    list_destroy(plist);
}

void test__list_quick_sort__2_less_greater(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 0);
    list_push_back(plist, 1);
    assert_true(list_size(plist) == 2);
    _list_quick_sort(plist, plist->_pt_node->_pt_next, plist->_pt_node->_pt_prev, _list_quick_sort_int_greater);
    assert_true(list_size(plist) == 2);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    list_destroy(plist);
}

void test__list_quick_sort__2_greater_less(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 1);
    list_push_back(plist, 0);
    assert_true(list_size(plist) == 2);
    _list_quick_sort(plist, plist->_pt_node->_pt_next, plist->_pt_node->_pt_prev, NULL);
    assert_true(list_size(plist) == 2);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);

    list_destroy(plist);
}

void test__list_quick_sort__2_greater_greater(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 1);
    list_push_back(plist, 0);
    assert_true(list_size(plist) == 2);
    _list_quick_sort(plist, plist->_pt_node->_pt_next, plist->_pt_node->_pt_prev, _list_quick_sort_int_greater);
    assert_true(list_size(plist) == 2);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    list_destroy(plist);
}

void test__list_quick_sort__random_equal_less(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_n(plist, 10);
    assert_true(list_size(plist) == 10);
    _list_quick_sort(plist, plist->_pt_node->_pt_next, plist->_pt_node->_pt_prev, NULL);
    assert_true(list_size(plist) == 10);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    list_destroy(plist);
}

void test__list_quick_sort__random_equal_greater(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_n(plist, 10);
    assert_true(list_size(plist) == 10);
    _list_quick_sort(plist, plist->_pt_node->_pt_next, plist->_pt_node->_pt_prev, _list_quick_sort_int_greater);
    assert_true(list_size(plist) == 10);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    list_destroy(plist);
}

void test__list_quick_sort__random_less_less(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 0);
    list_push_back(plist, 1);
    list_push_back(plist, 2);
    list_push_back(plist, 3);
    list_push_back(plist, 4);
    list_push_back(plist, 5);
    list_push_back(plist, 6);
    list_push_back(plist, 7);
    list_push_back(plist, 8);
    list_push_back(plist, 9);
    assert_true(list_size(plist) == 10);
    _list_quick_sort(plist, plist->_pt_node->_pt_next, plist->_pt_node->_pt_prev, NULL);
    assert_true(list_size(plist) == 10);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 6);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 8);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);

    list_destroy(plist);
}

void test__list_quick_sort__random_less_greater(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 0);
    list_push_back(plist, 1);
    list_push_back(plist, 2);
    list_push_back(plist, 3);
    list_push_back(plist, 4);
    list_push_back(plist, 5);
    list_push_back(plist, 6);
    list_push_back(plist, 7);
    list_push_back(plist, 8);
    list_push_back(plist, 9);
    assert_true(list_size(plist) == 10);
    _list_quick_sort(plist, plist->_pt_node->_pt_next, plist->_pt_node->_pt_prev, _list_quick_sort_int_greater);
    assert_true(list_size(plist) == 10);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 8);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 6);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    list_destroy(plist);
}

void test__list_quick_sort__random_greater_less(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 9);
    list_push_back(plist, 8);
    list_push_back(plist, 7);
    list_push_back(plist, 6);
    list_push_back(plist, 5);
    list_push_back(plist, 4);
    list_push_back(plist, 3);
    list_push_back(plist, 2);
    list_push_back(plist, 1);
    list_push_back(plist, 0);
    assert_true(list_size(plist) == 10);
    _list_quick_sort(plist, plist->_pt_node->_pt_next, plist->_pt_node->_pt_prev, NULL);
    assert_true(list_size(plist) == 10);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 6);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 8);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);

    list_destroy(plist);
}

void test__list_quick_sort__random_greater_greater(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 9);
    list_push_back(plist, 8);
    list_push_back(plist, 7);
    list_push_back(plist, 6);
    list_push_back(plist, 5);
    list_push_back(plist, 4);
    list_push_back(plist, 3);
    list_push_back(plist, 2);
    list_push_back(plist, 1);
    list_push_back(plist, 0);
    assert_true(list_size(plist) == 10);
    _list_quick_sort(plist, plist->_pt_node->_pt_next, plist->_pt_node->_pt_prev, _list_quick_sort_int_greater);
    assert_true(list_size(plist) == 10);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 8);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 6);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    list_destroy(plist);
}

void test__list_quick_sort__random_random_less(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 4);
    list_push_back(plist, 8);
    list_push_back(plist, 7);
    list_push_back(plist, 0);
    list_push_back(plist, 3);
    list_push_back(plist, 5);
    list_push_back(plist, 9);
    list_push_back(plist, 2);
    list_push_back(plist, 1);
    list_push_back(plist, 6);
    assert_true(list_size(plist) == 10);
    _list_quick_sort(plist, plist->_pt_node->_pt_next, plist->_pt_node->_pt_prev, NULL);
    assert_true(list_size(plist) == 10);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 6);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 8);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);

    list_destroy(plist);
}

void test__list_quick_sort__random_random_greater(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 1);
    list_push_back(plist, 8);
    list_push_back(plist, 3);
    list_push_back(plist, 0);
    list_push_back(plist, 2);
    list_push_back(plist, 6);
    list_push_back(plist, 4);
    list_push_back(plist, 9);
    list_push_back(plist, 5);
    list_push_back(plist, 7);
    assert_true(list_size(plist) == 10);
    _list_quick_sort(plist, plist->_pt_node->_pt_next, plist->_pt_node->_pt_prev, _list_quick_sort_int_greater);
    assert_true(list_size(plist) == 10);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 8);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 6);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    list_destroy(plist);
}

void test__list_quick_sort__random_random_dup_less(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 4);
    list_push_back(plist, 8);
    list_push_back(plist, 7);
    list_push_back(plist, 8);
    list_push_back(plist, 0);
    list_push_back(plist, 3);
    list_push_back(plist, 5);
    list_push_back(plist, 1);
    list_push_back(plist, 6);
    list_push_back(plist, 9);
    list_push_back(plist, 2);
    list_push_back(plist, 1);
    list_push_back(plist, 1);
    list_push_back(plist, 6);
    list_push_back(plist, 4);
    assert_true(list_size(plist) == 15);
    _list_quick_sort(plist, plist->_pt_node->_pt_next, plist->_pt_node->_pt_prev, NULL);
    assert_true(list_size(plist) == 15);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 6);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 6);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 8);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 8);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);

    list_destroy(plist);
}

void test__list_quick_sort__random_random_dup_greater(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 1);
    list_push_back(plist, 8);
    list_push_back(plist, 0);
    list_push_back(plist, 8);
    list_push_back(plist, 3);
    list_push_back(plist, 0);
    list_push_back(plist, 0);
    list_push_back(plist, 2);
    list_push_back(plist, 6);
    list_push_back(plist, 4);
    list_push_back(plist, 9);
    list_push_back(plist, 5);
    list_push_back(plist, 7);
    list_push_back(plist, 5);
    list_push_back(plist, 7);
    assert_true(list_size(plist) == 15);
    _list_quick_sort(plist, plist->_pt_node->_pt_next, plist->_pt_node->_pt_prev, _list_quick_sort_int_greater);
    assert_true(list_size(plist) == 15);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 8);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 8);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 6);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    list_destroy(plist);
}

void test__list_quick_sort__cstr_empty_less(void** state)
{
    list_t* plist = create_list(char*);

    list_init(plist);
    assert_true(list_size(plist) == 0);
    _list_quick_sort(plist, plist->_pt_node->_pt_next, plist->_pt_node->_pt_prev, NULL);
    assert_true(list_size(plist) == 0);

    list_destroy(plist);
}

void test__list_quick_sort__cstr_empty_greater(void** state)
{
    list_t* plist = create_list(char*);

    list_init(plist);
    assert_true(list_size(plist) == 0);
    _list_quick_sort(plist, plist->_pt_node->_pt_next, plist->_pt_node->_pt_prev, fun_greater_cstr);
    assert_true(list_size(plist) == 0);

    list_destroy(plist);
}

void test__list_quick_sort__cstr_1_less(void** state)
{
    list_t* plist = create_list(char*);

    list_init_n(plist, 1);
    assert_true(list_size(plist) == 1);
    _list_quick_sort(plist, plist->_pt_node->_pt_next, plist->_pt_node->_pt_prev, NULL);
    assert_true(list_size(plist) == 1);
    assert_true(strcmp((char*)iterator_get_pointer(list_begin(plist)), "") == 0);

    list_destroy(plist);
}

void test__list_quick_sort__cstr_1_greater(void** state)
{
    list_t* plist = create_list(char*);

    list_init_n(plist, 1);
    assert_true(list_size(plist) == 1);
    _list_quick_sort(plist, plist->_pt_node->_pt_next, plist->_pt_node->_pt_prev, fun_greater_cstr);
    assert_true(list_size(plist) == 1);
    assert_true(strcmp((char*)iterator_get_pointer(list_begin(plist)), "") == 0);

    list_destroy(plist);
}

void test__list_quick_sort__cstr_2_equal_less(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(char*);

    list_init_n(plist, 2);
    assert_true(list_size(plist) == 2);
    _list_quick_sort(plist, plist->_pt_node->_pt_next, plist->_pt_node->_pt_prev, NULL);
    assert_true(list_size(plist) == 2);
    it_iter = list_begin(plist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);

    list_destroy(plist);
}

void test__list_quick_sort__cstr_2_equal_greater(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(char*);

    list_init_n(plist, 2);
    assert_true(list_size(plist) == 2);
    _list_quick_sort(plist, plist->_pt_node->_pt_next, plist->_pt_node->_pt_prev, fun_greater_cstr);
    assert_true(list_size(plist) == 2);
    it_iter = list_begin(plist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);

    list_destroy(plist);
}

void test__list_quick_sort__cstr_2_less_less(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(char*);

    list_init(plist);
    list_push_back(plist, "0");
    list_push_back(plist, "1");
    assert_true(list_size(plist) == 2);
    _list_quick_sort(plist, plist->_pt_node->_pt_next, plist->_pt_node->_pt_prev, NULL);
    assert_true(list_size(plist) == 2);
    it_iter = list_begin(plist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "0") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "1") == 0);

    list_destroy(plist);
}

void test__list_quick_sort__cstr_2_less_greater(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(char*);

    list_init(plist);
    list_push_back(plist, "0");
    list_push_back(plist, "1");
    assert_true(list_size(plist) == 2);
    _list_quick_sort(plist, plist->_pt_node->_pt_next, plist->_pt_node->_pt_prev, fun_greater_cstr);
    assert_true(list_size(plist) == 2);
    it_iter = list_begin(plist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "1") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "0") == 0);

    list_destroy(plist);
}

void test__list_quick_sort__cstr_2_greater_less(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(char*);

    list_init(plist);
    list_push_back(plist, "1");
    list_push_back(plist, "0");
    assert_true(list_size(plist) == 2);
    _list_quick_sort(plist, plist->_pt_node->_pt_next, plist->_pt_node->_pt_prev, NULL);
    assert_true(list_size(plist) == 2);
    it_iter = list_begin(plist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "0") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "1") == 0);

    list_destroy(plist);
}

void test__list_quick_sort__cstr_2_greater_greater(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(char*);

    list_init(plist);
    list_push_back(plist, "1");
    list_push_back(plist, "0");
    assert_true(list_size(plist) == 2);
    _list_quick_sort(plist, plist->_pt_node->_pt_next, plist->_pt_node->_pt_prev, fun_greater_cstr);
    assert_true(list_size(plist) == 2);
    it_iter = list_begin(plist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "1") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "0") == 0);

    list_destroy(plist);
}

void test__list_quick_sort__cstr_random_equal_less(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(char*);

    list_init_n(plist, 10);
    assert_true(list_size(plist) == 10);
    _list_quick_sort(plist, plist->_pt_node->_pt_next, plist->_pt_node->_pt_prev, NULL);
    assert_true(list_size(plist) == 10);
    it_iter = list_begin(plist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);

    list_destroy(plist);
}

void test__list_quick_sort__cstr_random_equal_greater(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(char*);

    list_init_n(plist, 10);
    assert_true(list_size(plist) == 10);
    _list_quick_sort(plist, plist->_pt_node->_pt_next, plist->_pt_node->_pt_prev, fun_greater_cstr);
    assert_true(list_size(plist) == 10);
    it_iter = list_begin(plist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);

    list_destroy(plist);
}

void test__list_quick_sort__cstr_random_less_less(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(char*);

    list_init(plist);
    list_push_back(plist, "0");
    list_push_back(plist, "1");
    list_push_back(plist, "2");
    list_push_back(plist, "3");
    list_push_back(plist, "4");
    list_push_back(plist, "5");
    list_push_back(plist, "6");
    list_push_back(plist, "7");
    list_push_back(plist, "8");
    list_push_back(plist, "9");
    assert_true(list_size(plist) == 10);
    _list_quick_sort(plist, plist->_pt_node->_pt_next, plist->_pt_node->_pt_prev, NULL);
    assert_true(list_size(plist) == 10);
    it_iter = list_begin(plist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "0") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "1") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "2") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "3") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "4") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "5") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "6") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "7") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "8") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "9") == 0);

    list_destroy(plist);
}

void test__list_quick_sort__cstr_random_less_greater(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(char*);

    list_init(plist);
    list_push_back(plist, "0");
    list_push_back(plist, "1");
    list_push_back(plist, "2");
    list_push_back(plist, "3");
    list_push_back(plist, "4");
    list_push_back(plist, "5");
    list_push_back(plist, "6");
    list_push_back(plist, "7");
    list_push_back(plist, "8");
    list_push_back(plist, "9");
    assert_true(list_size(plist) == 10);
    _list_quick_sort(plist, plist->_pt_node->_pt_next, plist->_pt_node->_pt_prev, fun_greater_cstr);
    assert_true(list_size(plist) == 10);
    it_iter = list_begin(plist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "9") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "8") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "7") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "6") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "5") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "4") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "3") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "2") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "1") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "0") == 0);

    list_destroy(plist);
}

void test__list_quick_sort__cstr_random_greater_less(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(char*);

    list_init(plist);
    list_push_back(plist, "9");
    list_push_back(plist, "8");
    list_push_back(plist, "7");
    list_push_back(plist, "6");
    list_push_back(plist, "5");
    list_push_back(plist, "4");
    list_push_back(plist, "3");
    list_push_back(plist, "2");
    list_push_back(plist, "1");
    list_push_back(plist, "0");
    assert_true(list_size(plist) == 10);
    _list_quick_sort(plist, plist->_pt_node->_pt_next, plist->_pt_node->_pt_prev, NULL);
    assert_true(list_size(plist) == 10);
    it_iter = list_begin(plist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "0") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "1") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "2") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "3") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "4") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "5") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "6") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "7") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "8") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "9") == 0);

    list_destroy(plist);
}

void test__list_quick_sort__cstr_random_greater_greater(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(char*);

    list_init(plist);
    list_push_back(plist, "9");
    list_push_back(plist, "8");
    list_push_back(plist, "7");
    list_push_back(plist, "6");
    list_push_back(plist, "5");
    list_push_back(plist, "4");
    list_push_back(plist, "3");
    list_push_back(plist, "2");
    list_push_back(plist, "1");
    list_push_back(plist, "0");
    assert_true(list_size(plist) == 10);
    _list_quick_sort(plist, plist->_pt_node->_pt_next, plist->_pt_node->_pt_prev, fun_greater_cstr);
    assert_true(list_size(plist) == 10);
    it_iter = list_begin(plist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "9") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "8") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "7") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "6") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "5") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "4") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "3") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "2") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "1") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "0") == 0);

    list_destroy(plist);
}

void test__list_quick_sort__cstr_random_random_less(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(char*);

    list_init(plist);
    list_push_back(plist, "4");
    list_push_back(plist, "8");
    list_push_back(plist, "7");
    list_push_back(plist, "0");
    list_push_back(plist, "3");
    list_push_back(plist, "5");
    list_push_back(plist, "9");
    list_push_back(plist, "2");
    list_push_back(plist, "1");
    list_push_back(plist, "6");
    assert_true(list_size(plist) == 10);
    _list_quick_sort(plist, plist->_pt_node->_pt_next, plist->_pt_node->_pt_prev, NULL);
    assert_true(list_size(plist) == 10);
    it_iter = list_begin(plist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "0") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "1") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "2") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "3") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "4") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "5") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "6") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "7") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "8") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "9") == 0);

    list_destroy(plist);
}

void test__list_quick_sort__cstr_random_random_greater(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(char*);

    list_init(plist);
    list_push_back(plist, "1");
    list_push_back(plist, "8");
    list_push_back(plist, "3");
    list_push_back(plist, "0");
    list_push_back(plist, "2");
    list_push_back(plist, "6");
    list_push_back(plist, "4");
    list_push_back(plist, "9");
    list_push_back(plist, "5");
    list_push_back(plist, "7");
    assert_true(list_size(plist) == 10);
    _list_quick_sort(plist, plist->_pt_node->_pt_next, plist->_pt_node->_pt_prev, fun_greater_cstr);
    assert_true(list_size(plist) == 10);
    it_iter = list_begin(plist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "9") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "8") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "7") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "6") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "5") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "4") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "3") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "2") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "1") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "0") == 0);

    list_destroy(plist);
}

void test__list_quick_sort__cstr_random_random_dup_less(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(char*);

    list_init(plist);
    list_push_back(plist, "4");
    list_push_back(plist, "8");
    list_push_back(plist, "7");
    list_push_back(plist, "8");
    list_push_back(plist, "0");
    list_push_back(plist, "3");
    list_push_back(plist, "5");
    list_push_back(plist, "1");
    list_push_back(plist, "6");
    list_push_back(plist, "9");
    list_push_back(plist, "2");
    list_push_back(plist, "1");
    list_push_back(plist, "1");
    list_push_back(plist, "6");
    list_push_back(plist, "4");
    assert_true(list_size(plist) == 15);
    _list_quick_sort(plist, plist->_pt_node->_pt_next, plist->_pt_node->_pt_prev, NULL);
    assert_true(list_size(plist) == 15);
    it_iter = list_begin(plist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "0") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "1") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "1") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "1") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "2") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "3") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "4") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "4") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "5") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "6") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "6") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "7") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "8") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "8") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "9") == 0);

    list_destroy(plist);
}

void test__list_quick_sort__cstr_random_random_dup_greater(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(char*);

    list_init(plist);
    list_push_back(plist, "1");
    list_push_back(plist, "8");
    list_push_back(plist, "0");
    list_push_back(plist, "8");
    list_push_back(plist, "3");
    list_push_back(plist, "0");
    list_push_back(plist, "0");
    list_push_back(plist, "2");
    list_push_back(plist, "6");
    list_push_back(plist, "4");
    list_push_back(plist, "9");
    list_push_back(plist, "5");
    list_push_back(plist, "7");
    list_push_back(plist, "5");
    list_push_back(plist, "7");
    assert_true(list_size(plist) == 15);
    _list_quick_sort(plist, plist->_pt_node->_pt_next, plist->_pt_node->_pt_prev, fun_greater_cstr);
    assert_true(list_size(plist) == 15);
    it_iter = list_begin(plist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "9") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "8") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "8") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "7") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "7") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "6") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "5") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "5") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "4") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "3") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "2") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "1") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "0") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "0") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "0") == 0);

    list_destroy(plist);
}

