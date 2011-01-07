#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/cstl_iterator.h"
#include "cstl/cstl_slist_iterator.h"
#include "cstl/cslist.h"
#include "cstl/cvector.h"
#include "cstl_slist_aux.h"

#include "ut_def.h"
#include "ut_cstl_slist_aux.h"

UT_SUIT_DEFINATION(cstl_slist_aux, _slist_is_created);

/*
 * test _slist_is_created
 */
UT_CASE_DEFINATION(_slist_is_created)
void test__slist_is_created__null_slist_container(void** state)
{
    expect_assert_failure(_slist_is_created(NULL));
}

void test__slist_is_created__invalid_type_style(void** state)
{
    slist_t* pslist = create_slist(int);

    pslist->_t_typeinfo._t_style = 9999;
    assert_false(_slist_is_created(pslist));

    pslist->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist);
}

void test__slist_is_created__invalid_type_pointer(void** state)
{
    void* pv_tmp = NULL;
    slist_t* pslist = create_slist(int);

    pv_tmp = pslist->_t_typeinfo._pt_type;
    pslist->_t_typeinfo._pt_type = NULL;
    assert_false(_slist_is_created(pslist));

    pslist->_t_typeinfo._pt_type = pv_tmp;
    slist_destroy(pslist);
}

void test__slist_is_created__null_node(void** state)
{
    slist_t* pslist = create_slist(int);
    pslist->_t_head._pt_next = 0x224;

    assert_false(_slist_is_created(pslist));

    pslist->_t_head._pt_next = NULL;
    slist_destroy(pslist);
}

void test__slist_is_created__uninited_allocator(void** state)
{
    slist_t* pslist = create_slist(int);
    pslist->_t_allocater._pby_mempool = 0x444;

    assert_false(_slist_is_created(pslist));

    pslist->_t_allocater._pby_mempool = NULL;
    slist_destroy(pslist);
}

void test__slist_is_created__successfully(void** state)
{
    slist_t* pslist = create_slist(int);

    assert_true(_slist_is_created(pslist));

    slist_destroy(pslist);
}

/*
 * test _slist_is_inited
 */
UT_CASE_DEFINATION(_slist_is_inited)
void test__slist_is_inited__null_slist_container(void** state)
{
    expect_assert_failure(_slist_is_inited(NULL));
}

void test__slist_is_inited__invalid_type_styple(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    pslist->_t_typeinfo._t_style = 9999;
    assert_false(_slist_is_inited(pslist));

    pslist->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist);
}

void test__slist_is_inited__invalid_type_pointer(void** state)
{
    void* pv_tmp = NULL;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    pv_tmp = pslist->_t_typeinfo._pt_type;
    pslist->_t_typeinfo._pt_type = NULL;
    assert_false(_slist_is_inited(pslist));

    pslist->_t_typeinfo._pt_type = pv_tmp;
    slist_destroy(pslist);
}

void test__slist_is_inited__init_empty(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    assert_true(_slist_is_inited(pslist));

    slist_destroy(pslist);
}

void test__slist_is_inited__init_non_empty(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 10);

    assert_true(_slist_is_inited(pslist));

    slist_destroy(pslist);
}

/*
 * test _slist_iterator_belong_to_slist
 */
UT_CASE_DEFINATION(_slist_iterator_belong_to_slist)
void test__slist_iterator_belong_to_slist__null_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    expect_assert_failure(_slist_iterator_belong_to_slist(NULL, slist_begin(pslist)));

    slist_destroy(pslist);
}

void test__slist_iterator_belong_to_slist__non_inited_slist_container(void** state)
{
    slist_iterator_t it_iter = _create_slist_iterator();
    slist_t* pslist = create_slist(int);

    expect_assert_failure(_slist_iterator_belong_to_slist(pslist, it_iter));

    slist_destroy(pslist);
}

void test__slist_iterator_belong_to_slist__invalid_iter_container_type(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    it_iter = slist_begin(pslist);
    it_iter._t_containertype = 999;
    expect_assert_failure(_slist_iterator_belong_to_slist(pslist, it_iter));

    slist_destroy(pslist);
}

void test__slist_iterator_belong_to_slist__invalid_iter_iterator_type(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    it_iter = slist_begin(pslist);
    it_iter._t_iteratortype = 884;
    expect_assert_failure(_slist_iterator_belong_to_slist(pslist, it_iter));

    slist_destroy(pslist);
}

void test__slist_iterator_belong_to_slist__invalid_iter_container_pointer(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    it_iter = slist_begin(pslist);
    it_iter._pt_container = 0x23423;
    expect_assert_failure(_slist_iterator_belong_to_slist(pslist, it_iter));

    slist_destroy(pslist);
}

void test__slist_iterator_belong_to_slist__not_belong_to_slist(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    it_iter = slist_begin(pslist);
    it_iter._t_pos._pc_corepos = 0x9378;
    assert_false(_slist_iterator_belong_to_slist(pslist, it_iter));

    slist_destroy(pslist);
}

void test__slist_iterator_belong_to_slist__belong_to_slist_begin(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 10);

    it_iter = slist_begin(pslist);
    assert_true(_slist_iterator_belong_to_slist(pslist, it_iter));

    slist_destroy(pslist);
}

void test__slist_iterator_belong_to_slist__belong_to_slist_middle(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 10);

    it_iter = iterator_next(slist_begin(pslist));
    assert_true(_slist_iterator_belong_to_slist(pslist, it_iter));

    slist_destroy(pslist);
}

void test__slist_iterator_belong_to_slist__belong_to_slist_end(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 10);

    it_iter = slist_end(pslist);
    assert_true(_slist_iterator_belong_to_slist(pslist, it_iter));

    slist_destroy(pslist);
}

/*
 * test _slist_same_slist_iterator_type
 */
UT_CASE_DEFINATION(_slist_same_slist_iterator_type)
void test__slist_same_slist_iterator_type__null_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    expect_assert_failure(_slist_same_slist_iterator_type(NULL, slist_begin(pslist)));

    slist_destroy(pslist);
}

void test__slist_same_slist_iterator_type__invalid_iterator_null_container(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_iter;

    slist_init(pslist);
    it_iter = slist_begin(pslist);
    it_iter._pt_container = NULL;
    expect_assert_failure(_slist_same_slist_iterator_type(pslist, it_iter));

    slist_destroy(pslist);
}

void test__slist_same_slist_iterator_type__invalid_iterator_container_type(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_iter;

    slist_init(pslist);
    it_iter = slist_begin(pslist);
    it_iter._t_containertype = 2823;
    expect_assert_failure(_slist_same_slist_iterator_type(pslist, it_iter));

    slist_destroy(pslist);
}

void test__slist_same_slist_iterator_type__invalid_iterator_iterator_type(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_iter;

    slist_init(pslist);
    it_iter = slist_begin(pslist);
    it_iter._t_iteratortype = 222;
    expect_assert_failure(_slist_same_slist_iterator_type(pslist, it_iter));

    slist_destroy(pslist);
}

void test__slist_same_slist_iterator_type__same_type_belong_to_slist(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_iter;

    slist_init(pslist);
    it_iter = slist_begin(pslist);
    assert_true(_slist_same_slist_iterator_type(pslist, it_iter));

    slist_destroy(pslist);
}

void test__slist_same_slist_iterator_type__same_type_not_belong_to_slist(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);
    slist_iterator_t it_iter;

    slist_init(pslist_second);
    it_iter = slist_begin(pslist_second);
    assert_true(_slist_same_slist_iterator_type(pslist_first, it_iter));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_same_slist_iterator_type__not_same_type(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(double);
    slist_iterator_t it_iter;

    slist_init(pslist_second);
    it_iter = slist_begin(pslist_second);
    assert_false(_slist_same_slist_iterator_type(pslist_first, it_iter));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

/*
 * test _slist_same_type
 */
UT_CASE_DEFINATION(_slist_same_type)
void test__slist_same_type__null_first(void** state)
{
    slist_t* pslist = create_slist(int);

    expect_assert_failure(_slist_same_type(NULL, pslist));

    slist_destroy(pslist);
}

void test__slist_same_type__null_second(void** state)
{
    slist_t* pslist = create_slist(int);

    expect_assert_failure(_slist_same_type(pslist, NULL));

    slist_destroy(pslist);
}

void test__slist_same_type__non_created_first(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init(pslist_first);
    pslist_first->_t_typeinfo._t_style = 38494;
    expect_assert_failure(_slist_same_type(pslist_first, pslist_second));

    pslist_first->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_same_type__non_created_second(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init(pslist_second);
    pslist_second->_t_typeinfo._t_style = 34333;
    expect_assert_failure(_slist_same_type(pslist_first, pslist_second));

    pslist_second->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_same_type__same_c_builtin(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    assert_true(_slist_same_type(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_same_type__same_c_builtin_dup(void** state)
{
    slist_t* pslist_first = create_slist(signed long int);
    slist_t* pslist_second = create_slist(long);
    slist_init(pslist_first);

    assert_true(_slist_same_type(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_same_type__not_same_c_builtin(void** state)
{
    slist_t* pslist_first = create_slist(signed long int);
    slist_t* pslist_second = create_slist(unsigned long);
    slist_init_n(pslist_first, 10);
    slist_init_elem(pslist_second, 10, 100);

    assert_false(_slist_same_type(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_same_type__same_libcstl_builtin(void** state)
{
    slist_t* pslist_first = create_slist(slist_t<int>);
    slist_t* pslist_second = create_slist(slist_t<signed>);

    assert_true(_slist_same_type(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_same_type__same_libcstl_builtin_dup(void** state)
{
    slist_t* pslist_first = create_slist(slist_iterator_t);
    slist_t* pslist_second = create_slist(vector_iterator_t);

    assert_true(_slist_same_type(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_same_type__not_same_libcstl_builtin_container(void** state)
{
    slist_t* pslist_first = create_slist(vector_t<int>);
    slist_t* pslist_second = create_slist(slist_t<int>);

    assert_false(_slist_same_type(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_same_type__not_same_libcstl_builtin_elem(void** state)
{
    slist_t* pslist_first = create_slist(vector_t<int>);
    slist_t* pslist_second = create_slist(vector_t<char>);

    assert_false(_slist_same_type(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_same_type__not_same_libcstl_builtin_iter(void** state)
{
    slist_t* pslist_first = create_slist(slist_iterator_t);
    slist_t* pslist_second = create_slist(vector_t<char>);

    assert_false(_slist_same_type(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_same_type__not_same_libcstl_builtin_string(void** state)
{
    slist_t* pslist_first = create_slist(string_t);
    slist_t* pslist_second = create_slist(vector_t<char>);

    assert_false(_slist_same_type(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_same_type__not_same_c_libcstl_builtin(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(vector_t<int>);

    assert_false(_slist_same_type(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

typedef struct _tag_test__slist_same_type__same_user_defined
{
    int n_elem;
}_test__slist_same_type__same_user_defined_t;

void test__slist_same_type__same_user_defined(void** state)
{
    slist_t* pslist_first = NULL;
    slist_t* pslist_second = NULL;
    type_register(struct _tag_test__slist_same_type__same_user_defined, NULL, NULL, NULL, NULL);
    type_duplicate(struct _tag_test__slist_same_type__same_user_defined, _test__slist_same_type__same_user_defined_t);
    pslist_first = create_slist(_test__slist_same_type__same_user_defined_t);
    pslist_second = create_slist(_test__slist_same_type__same_user_defined_t);

    assert_true(_slist_same_type(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_same_type__same_user_defined_dup(void** state)
{
    slist_t* pslist_first = create_slist(_test__slist_same_type__same_user_defined_t);
    slist_t* pslist_second = create_slist(struct _tag_test__slist_same_type__same_user_defined);

    assert_true(_slist_same_type(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_same_type__not_same_c_user_define(void** state)
{
    slist_t* pslist_first = create_slist(_test__slist_same_type__same_user_defined_t);
    slist_t* pslist_second = create_slist(double);

    assert_false(_slist_same_type(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_same_type__not_same_libcstl_user_define(void** state)
{
    slist_t* pslist_first = create_slist(_test__slist_same_type__same_user_defined_t);
    slist_t* pslist_second = create_slist(iterator_t);

    assert_false(_slist_same_type(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_same_type__same_container(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    assert_true(_slist_same_type(pslist, pslist));

    slist_destroy(pslist);
}

