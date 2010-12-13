#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/cstl_iterator.h"
#include "cstl/cstl_list_iterator.h"
#include "cstl/clist.h"
#include "cstl_list_aux.h"

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

