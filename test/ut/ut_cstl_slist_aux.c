#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/citerator.h"
#include "cstl/cstl_slist_iterator.h"
#include "cstl/cslist.h"
#include "cstl/cvector.h"
#include "cstl_slist_aux.h"
#include "cstl/cstring.h"
#include "cstl_vector_aux.h"

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
    pslist->_t_head._pt_next = (_slistnode_t*)0x334;

    assert_false(_slist_is_created(pslist));

    pslist->_t_head._pt_next = NULL;
    slist_destroy(pslist);
}

void test__slist_is_created__uninited_allocator(void** state)
{
    slist_t* pslist = create_slist(int);

#ifdef CSTL_MEMORY_MANAGEMENT
    pslist->_t_allocator._pby_mempool = (_byte_t*)0x444;
    assert_false(_slist_is_created(pslist));
    pslist->_t_allocator._pby_mempool = NULL;
#else
    assert_true(_slist_is_created(pslist));
#endif

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
    it_iter._pt_container = (void*)0x23423;
    expect_assert_failure(_slist_iterator_belong_to_slist(pslist, it_iter));

    slist_destroy(pslist);
}

void test__slist_iterator_belong_to_slist__not_belong_to_slist(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    it_iter = slist_begin(pslist);
    it_iter._t_pos._pby_corepos = (_byte_t*)0x9378;
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
 * test _slist_same_iterator_type
 */
UT_CASE_DEFINATION(_slist_same_iterator_type)
void test__slist_same_iterator_type__null_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    expect_assert_failure(_slist_same_iterator_type(NULL, slist_begin(pslist)));

    slist_destroy(pslist);
}

void test__slist_same_iterator_type__invalid_iterator_null_container(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_iter;

    slist_init(pslist);
    it_iter = slist_begin(pslist);
    it_iter._pt_container = NULL;
    expect_assert_failure(_slist_same_iterator_type(pslist, it_iter));

    slist_destroy(pslist);
}

void test__slist_same_iterator_type__invalid_iterator_container_type(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_iter;

    slist_init(pslist);
    it_iter = slist_begin(pslist);
    it_iter._t_containertype = 2823;
    expect_assert_failure(_slist_same_iterator_type(pslist, it_iter));

    slist_destroy(pslist);
}

void test__slist_same_iterator_type__invalid_iterator_iterator_type(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_iter;

    slist_init(pslist);
    it_iter = slist_begin(pslist);
    it_iter._t_iteratortype = 222;
    expect_assert_failure(_slist_same_iterator_type(pslist, it_iter));

    slist_destroy(pslist);
}

void test__slist_same_iterator_type__same_type_belong_to_slist(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_iter;

    slist_init(pslist);
    it_iter = slist_begin(pslist);
    assert_true(_slist_same_iterator_type(pslist, it_iter));

    slist_destroy(pslist);
}

void test__slist_same_iterator_type__same_type_not_belong_to_slist(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);
    slist_iterator_t it_iter;

    slist_init(pslist_second);
    it_iter = slist_begin(pslist_second);
    assert_true(_slist_same_iterator_type(pslist_first, it_iter));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_same_iterator_type__not_same_type(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(double);
    slist_iterator_t it_iter;

    slist_init(pslist_second);
    it_iter = slist_begin(pslist_second);
    assert_false(_slist_same_iterator_type(pslist_first, it_iter));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_same_iterator_type__same_type_not_slist_iterator(void** state)
{
    slist_t* pslist = create_slist(int);
    vector_t* pvec = create_vector(int);

    vector_init(pvec);
    assert_true(_slist_same_iterator_type(pslist, vector_begin(pvec)));

    slist_destroy(pslist);
    vector_destroy(pvec);
}

void test__slist_same_iterator_type__not_same_type_not_slist_iterator(void** state)
{
    slist_t* pslist = create_slist(int);
    vector_t* pvec = create_vector(double);

    vector_init(pvec);
    assert_false(_slist_same_iterator_type(pslist, vector_begin(pvec)));

    slist_destroy(pslist);
    vector_destroy(pvec);
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

/*
 * test _slist_get_varg_value_auxiliary
 */
UT_CASE_DEFINATION(_slist_get_varg_value_auxiliary)
static void _wrapper_slist_get_varg_value_auxiliary(slist_t* pslist_slist, _slistnode_t* pt_node, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, pt_node);
    _slist_get_varg_value_auxiliary(pslist_slist, val_elemlist, pt_node);
    va_end(val_elemlist);
}

void test__slist_get_varg_value_auxiliary__null_slist_container(void** state)
{
    _slistnode_t node;
    expect_assert_failure(_wrapper_slist_get_varg_value_auxiliary(NULL, &node, 100));
}

void test__slist_get_varg_value_auxiliary__null_node(void** state)
{
    slist_t* pslist = create_slist(int);

    expect_assert_failure(_wrapper_slist_get_varg_value_auxiliary(pslist, NULL, 100));

    slist_destroy(pslist);
}

void test__slist_get_varg_value_auxiliary__non_created_slist_containter(void** state)
{
    _slistnode_t node;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    pslist->_t_typeinfo._t_style = 999;
    expect_assert_failure(_wrapper_slist_get_varg_value_auxiliary(pslist, &node, 100));

    pslist->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist);
}

void test__slist_get_varg_value_auxiliary__c_builtin(void** state)
{
    _slistnode_t* pt_node = NULL;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);
    pt_node = malloc(_SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pslist)));

    _wrapper_slist_get_varg_value_auxiliary(pslist, pt_node, 100);
    assert_true(*(int*)pt_node->_pby_data == 100);

    free(pt_node);
    slist_destroy(pslist);
}

void test__slist_get_varg_value_auxiliary__cstr(void** state)
{
    _slistnode_t* pt_node = NULL;
    slist_t* pslist = create_slist(char*);
    slist_init(pslist);
    pt_node = malloc(_SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pslist)));

    _wrapper_slist_get_varg_value_auxiliary(pslist, pt_node, "abcdefg");
    assert_true(strcmp(string_c_str((string_t*)pt_node->_pby_data), "abcdefg") == 0);

    _string_destroy_auxiliary((string_t*)pt_node->_pby_data);
    free(pt_node);
    slist_destroy(pslist);
}

void test__slist_get_varg_value_auxiliary__libcstl_builtin(void** state)
{
    _slistnode_t* pt_node = NULL;
    slist_t* pslist = create_slist(vector_t<int>);
    vector_t* pvec = create_vector(int);
    vector_init_elem(pvec, 10, 100);
    slist_init(pslist);
    pt_node = malloc(_SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pslist)));

    _wrapper_slist_get_varg_value_auxiliary(pslist, pt_node, pvec);
    assert_true(vector_equal((vector_t*)pt_node->_pby_data, pvec));

    _vector_destroy_auxiliary((vector_t*)pt_node->_pby_data);
    free(pt_node);
    slist_destroy(pslist);
    vector_destroy(pvec);
}

void test__slist_get_varg_value_auxiliary__user_define(void** state)
{
    typedef struct _tag_test__slist_get_varg_value_auxiliary__user_define
    {
        int n_elem;
    }_test__slist_get_varg_value_auxiliary__user_define_t;

    _slistnode_t* pt_node = NULL;
    slist_t* pslist = NULL;
    _test__slist_get_varg_value_auxiliary__user_define_t t_use;

    type_register(_test__slist_get_varg_value_auxiliary__user_define_t, NULL, NULL, NULL, NULL);
    pslist = create_slist(_test__slist_get_varg_value_auxiliary__user_define_t);
    slist_init(pslist);
    pt_node = malloc(_SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pslist)));
    t_use.n_elem = 10000;

    _wrapper_slist_get_varg_value_auxiliary(pslist, pt_node, &t_use);
    assert_true(((_test__slist_get_varg_value_auxiliary__user_define_t*)pt_node->_pby_data)->n_elem == t_use.n_elem);

    free(pt_node);
    slist_destroy(pslist);
}

/*
 * test _slist_destroy_varg_value_auxiliary
 */
UT_CASE_DEFINATION(_slist_destroy_varg_value_auxiliary)
void test__slist_destroy_varg_value_auxiliary__null_slist_container(void** state)
{
    _slistnode_t node;
    expect_assert_failure(_slist_destroy_varg_value_auxiliary(NULL, &node));
}

void test__slist_destroy_varg_value_auxiliary__non_created_slist_container(void** state)
{
    _slistnode_t node;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);
    pslist->_t_typeinfo._t_style = 99;
    expect_assert_failure(_slist_destroy_varg_value_auxiliary(pslist, &node));

    pslist->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist);
}

void test__slist_destroy_varg_value_auxiliary__null_node(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_init(pslist);
    expect_assert_failure(_slist_destroy_varg_value_auxiliary(pslist, NULL));

    slist_destroy(pslist);
}

void test__slist_destroy_varg_value_auxiliary__successfully(void** state)
{
    _slistnode_t* pt_node = NULL;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);
    pt_node = malloc(_SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pslist)));
    _slist_destroy_varg_value_auxiliary(pslist, pt_node);

    free(pt_node);
    slist_destroy(pslist);
}

/*
 * test _slist_init_node_auxiliary
 */
UT_CASE_DEFINATION(_slist_init_node_auxiliary)
void test__slist_init_node_auxiliary__null_slist_container(void** state)
{
    _slistnode_t node;
    expect_assert_failure(_slist_init_node_auxiliary(NULL, &node));
}

void test__slist_init_node_auxiliary__null_node(void** state)
{
    slist_t* pslist = create_slist(int);

    expect_assert_failure(_slist_init_node_auxiliary(pslist, NULL));

    slist_destroy(pslist);
}

void test__slist_init_node_auxiliary__non_created_slist_containter(void** state)
{
    _slistnode_t node;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    pslist->_t_typeinfo._t_style = 4444;
    expect_assert_failure(_slist_init_node_auxiliary(pslist, &node));

    pslist->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist);
}

void test__slist_init_node_auxiliary__c_builtin(void** state)
{
    _slistnode_t* pt_node = NULL;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);
    pt_node = malloc(_SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pslist)));

    _slist_init_node_auxiliary(pslist, pt_node);
    assert_true(*(int*)pt_node->_pby_data == 0);

    free(pt_node);
    slist_destroy(pslist);
}

void test__slist_init_node_auxiliary__cstr(void** state)
{
    _slistnode_t* pt_node = NULL;
    slist_t* pslist = create_slist(char*);
    slist_init(pslist);
    pt_node = malloc(_SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pslist)));

    _slist_init_node_auxiliary(pslist, pt_node);
    assert_true(strcmp(string_c_str((string_t*)pt_node->_pby_data), "") == 0);

    _slist_destroy_varg_value_auxiliary(pslist, pt_node);
    free(pt_node);
    slist_destroy(pslist);
}

void test__slist_init_node_auxiliary__libcstl_builtin(void** state)
{
    _slistnode_t* pt_node = NULL;
    slist_t* pslist = create_slist(vector_t<int>);
    slist_init(pslist);
    pt_node = malloc(_SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pslist)));

    _slist_init_node_auxiliary(pslist, pt_node);
    assert_true(_vector_is_inited((vector_t*)pt_node->_pby_data));

    free(pt_node);
    slist_destroy(pslist);
}

void test__slist_init_node_auxiliary__user_define(void** state)
{
    typedef struct _tag_test__slist_init_node_auxiliary__user_define
    {
        int n_elem;
    }_test__slist_init_node_auxiliary__user_define_t;

    _slistnode_t* pt_node = NULL;
    slist_t* pslist = NULL;

    type_register(_test__slist_init_node_auxiliary__user_define_t, NULL, NULL, NULL, NULL);
    pslist = create_slist(_test__slist_init_node_auxiliary__user_define_t);
    slist_init(pslist);
    pt_node = malloc(_SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pslist)));

    _slist_init_node_auxiliary(pslist, pt_node);
    assert_true(((_test__slist_init_node_auxiliary__user_define_t*)pt_node->_pby_data)->n_elem == 0);

    free(pt_node);
    slist_destroy(pslist);
}

/*
 * test _slist_transfer
 */
UT_CASE_DEFINATION(_slist_transfer)
void test__slist_transfer__invalid_pos(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_pos;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;

    slist_init_n(pslist, 10);
    it_pos = slist_begin(pslist);
    it_begin = slist_begin(pslist);
    it_end = slist_end(pslist);

    it_pos._pt_container = NULL;
    expect_assert_failure(_slist_transfer(it_pos, it_begin, it_end));

    slist_destroy(pslist);
}

void test__slist_transfer__invalid_begin(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_pos;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;

    slist_init_n(pslist, 10);
    it_pos = slist_begin(pslist);
    it_begin = slist_begin(pslist);
    it_end = slist_end(pslist);

    it_begin._t_containertype = 23984;
    expect_assert_failure(_slist_transfer(it_pos, it_begin, it_end));

    slist_destroy(pslist);
}

void test__slist_transfer__invalid_end(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_pos;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;

    slist_init_n(pslist, 10);
    it_pos = slist_begin(pslist);
    it_begin = slist_begin(pslist);
    it_end = slist_end(pslist);

    it_end._t_iteratortype = 345676;
    expect_assert_failure(_slist_transfer(it_pos, it_begin, it_end));

    slist_destroy(pslist);
}

void test__slist_transfer__invalid_range_not_same_slist(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);
    slist_iterator_t it_pos;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;

    slist_init_n(pslist_first, 10);
    slist_init_n(pslist_second, 24);
    it_pos = slist_begin(pslist_first);
    it_begin = slist_begin(pslist_first);
    it_end = slist_end(pslist_second);

    expect_assert_failure(_slist_transfer(it_pos, it_begin, it_end));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_transfer__invalid_range_end_before_begin(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);
    slist_iterator_t it_pos;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;

    slist_init_n(pslist_first, 10);
    slist_init_n(pslist_second, 24);
    it_pos = slist_begin(pslist_first);
    it_begin = slist_begin(pslist_second);
    it_end = slist_end(pslist_second);

    expect_assert_failure(_slist_transfer(it_pos, it_end, it_begin));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_transfer__pos_range_not_same_type(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(double);
    slist_iterator_t it_pos;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;

    slist_init_n(pslist_first, 10);
    slist_init_n(pslist_second, 24);
    it_pos = slist_begin(pslist_first);
    it_begin = slist_begin(pslist_second);
    it_end = slist_end(pslist_second);

    expect_assert_failure(_slist_transfer(it_pos, it_begin, it_end));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_transfer__does_nothing_empty_range(void** state)
{
    size_t i = 0;
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);
    slist_iterator_t it_pos;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;

    slist_init_elem(pslist_first, 10, 100);
    slist_init_n(pslist_second, 24);
    it_pos = slist_begin(pslist_first);
    it_begin = slist_begin(pslist_second);
    it_end = slist_begin(pslist_second);

    assert_true(slist_size(pslist_first) == 10);
    assert_true(slist_size(pslist_second) == 24);
    _slist_transfer(it_pos, it_begin, it_end);
    assert_true(slist_size(pslist_first) == 10);
    assert_true(slist_size(pslist_second) == 24);
    for(it_pos = slist_begin(pslist_first), i = 0;
        !iterator_equal(it_pos, slist_end(pslist_first));
        it_pos = iterator_next(it_pos), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_pos) == 100);
    }
    for(it_pos = slist_begin(pslist_second), i = 0;
        !iterator_equal(it_pos, slist_end(pslist_second));
        it_pos = iterator_next(it_pos), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_pos) == 0);
    }

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_transfer__successfully_begin_begin(void** state)
{
    size_t i = 0;
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);
    slist_iterator_t it_pos;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;

    slist_init_elem(pslist_first, 10, 100);
    slist_init_n(pslist_second, 24);
    it_pos = slist_begin(pslist_first);
    it_begin = slist_begin(pslist_second);
    it_end = iterator_advance(it_begin, 4);

    assert_true(slist_size(pslist_first) == 10);
    assert_true(slist_size(pslist_second) == 24);

    _slist_transfer(it_pos, it_begin, it_end);

    assert_true(slist_size(pslist_first) == 14);
    assert_true(slist_size(pslist_second) == 20);
    for(it_pos = slist_begin(pslist_first), i = 0;
        !iterator_equal(it_pos, slist_end(pslist_first));
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

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_transfer__successfully_middle_middle(void** state)
{
    size_t i = 0;
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);
    slist_iterator_t it_pos;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;

    slist_init_elem(pslist_first, 10, 100);
    slist_init_n(pslist_second, 24);
    it_pos = iterator_advance(slist_begin(pslist_first), 5);
    it_begin = iterator_advance(slist_begin(pslist_second), 5);
    it_end = iterator_advance(it_begin, 4);

    assert_true(slist_size(pslist_first) == 10);
    assert_true(slist_size(pslist_second) == 24);

    _slist_transfer(it_pos, it_begin, it_end);

    assert_true(slist_size(pslist_first) == 14);
    assert_true(slist_size(pslist_second) == 20);
    for(it_pos = slist_begin(pslist_first), i = 0;
        !iterator_equal(it_pos, slist_end(pslist_first));
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

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_transfer__successfully_end(void** state)
{
    size_t i = 0;
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);
    slist_iterator_t it_pos;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;

    slist_init_elem(pslist_first, 10, 100);
    slist_init_n(pslist_second, 24);
    it_pos = slist_end(pslist_first);
    it_end = slist_end(pslist_second);
    it_begin = iterator_advance(slist_begin(pslist_second), 20);

    assert_true(slist_size(pslist_first) == 10);
    assert_true(slist_size(pslist_second) == 24);

    _slist_transfer(it_pos, it_begin, it_end);

    assert_true(slist_size(pslist_first) == 14);
    assert_true(slist_size(pslist_second) == 20);
    for(it_pos = slist_begin(pslist_first), i = 0;
        !iterator_equal(it_pos, slist_end(pslist_first));
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

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_transfer__successfully_middle_all(void** state)
{
    size_t i = 0;
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);
    slist_iterator_t it_pos;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;

    slist_init_elem(pslist_first, 10, 100);
    slist_init_n(pslist_second, 24);
    it_pos = slist_end(pslist_first);
    it_begin = slist_begin(pslist_second);
    it_end = slist_end(pslist_second);

    assert_true(slist_size(pslist_first) == 10);
    assert_true(slist_size(pslist_second) == 24);

    _slist_transfer(it_pos, it_begin, it_end);

    assert_true(slist_size(pslist_first) == 34);
    assert_true(slist_size(pslist_second) == 0);
    for(it_pos = slist_begin(pslist_first), i = 0;
        !iterator_equal(it_pos, slist_end(pslist_first));
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

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_transfer__same_slist_pos_belong_to_range(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_pos;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;

    slist_init_n(pslist, 10);
    it_begin = slist_begin(pslist);
    it_end = slist_end(pslist);
    it_pos = iterator_next(it_begin);
    expect_assert_failure(_slist_transfer(it_pos, it_begin, it_end));

    slist_destroy(pslist);
}

void test__slist_transfer__same_slist_does_nothing_empty_range(void** state)
{
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_pos;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;

    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, i);
    }
    it_begin = slist_end(pslist);
    it_end = slist_end(pslist);
    it_pos = slist_begin(pslist);
    _slist_transfer(it_pos, it_begin, it_end);
    for(it_pos = slist_begin(pslist), i = 0;
        !iterator_equal(it_pos, slist_end(pslist));
        it_pos = iterator_next(it_pos), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_pos) == 9 - i);
    }

    slist_destroy(pslist);
}

void test__slist_transfer__same_slist_does_nothing_pos_equa_to_begin(void** state)
{
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_pos;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;

    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, i);
    }
    it_begin = slist_begin(pslist);
    it_end = slist_end(pslist);
    it_pos = slist_begin(pslist);
    _slist_transfer(it_pos, it_begin, it_end);
    for(it_pos = slist_begin(pslist), i = 0;
        !iterator_equal(it_pos, slist_end(pslist));
        it_pos = iterator_next(it_pos), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_pos) == 9 - i);
    }

    slist_destroy(pslist);
}

void test__slist_transfer__same_slist_does_nothing_pos_equa_to_end(void** state)
{
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_pos;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;

    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, i);
    }
    it_begin = slist_begin(pslist);
    it_end = slist_end(pslist);
    it_pos = slist_end(pslist);
    _slist_transfer(it_pos, it_begin, it_end);
    for(it_pos = slist_begin(pslist), i = 0;
        !iterator_equal(it_pos, slist_end(pslist));
        it_pos = iterator_next(it_pos), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_pos) == 9 - i);
    }

    slist_destroy(pslist);
}

void test__slist_transfer__same_slist_begin_middle(void** state)
{
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_pos;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;

    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, 9 - i);
    }
    it_pos = slist_begin(pslist);
    it_begin = iterator_next(slist_begin(pslist));
    it_end = iterator_advance(it_begin, 3);
    _slist_transfer(it_pos, it_begin, it_end);

    it_pos = slist_begin(pslist);
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

    slist_destroy(pslist);
}

void test__slist_transfer__same_slist_begin_end(void** state)
{
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_pos;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;

    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, 9 - i);
    }
    it_pos = slist_begin(pslist);
    it_begin = iterator_advance(slist_begin(pslist), 6);
    it_end = slist_end(pslist);
    _slist_transfer(it_pos, it_begin, it_end);

    it_pos = slist_begin(pslist);
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

    slist_destroy(pslist);
}

void test__slist_transfer__same_slist_middle_begin(void** state)
{
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_pos;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;

    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, 9 - i);
    }
    it_pos = iterator_advance(slist_begin(pslist), 6);
    it_begin = slist_begin(pslist);
    it_end = iterator_next(it_begin);
    _slist_transfer(it_pos, it_begin, it_end);

    it_pos = slist_begin(pslist);
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

    slist_destroy(pslist);
}

void test__slist_transfer__same_slist_middle_middle(void** state)
{
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_pos;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;

    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist,  9 - i);
    }
    it_pos = iterator_advance(slist_begin(pslist), 6);
    it_begin = iterator_next(slist_begin(pslist));
    it_end = iterator_advance(it_begin, 3);
    _slist_transfer(it_pos, it_begin, it_end);

    it_pos = slist_begin(pslist);
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

    slist_destroy(pslist);
}

void test__slist_transfer__same_slist_middle_end(void** state)
{
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_pos;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;

    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, 9 - i);
    }
    it_pos = iterator_advance(slist_begin(pslist), 6);
    it_begin = iterator_advance(slist_begin(pslist), 8);
    it_end = slist_end(pslist);
    _slist_transfer(it_pos, it_begin, it_end);

    it_pos = slist_begin(pslist);
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

    slist_destroy(pslist);
}

void test__slist_transfer__same_slist_end_begin(void** state)
{
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_pos;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;

    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, 9 - i);
    }
    it_pos = slist_end(pslist);
    it_begin = slist_begin(pslist);
    it_end = iterator_advance(it_begin, 4);
    _slist_transfer(it_pos, it_begin, it_end);

    it_pos = slist_begin(pslist);
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

    slist_destroy(pslist);
}

void test__slist_transfer__same_slist_end_middle(void** state)
{
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_pos;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;

    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, 9 - i);
    }
    it_pos = slist_end(pslist);
    it_begin = iterator_next(slist_begin(pslist));
    it_end = iterator_advance(it_begin, 4);
    _slist_transfer(it_pos, it_begin, it_end);

    it_pos = slist_begin(pslist);
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

    slist_destroy(pslist);
}

/*
 * test _slist_transfer_after
 */
UT_CASE_DEFINATION(_slist_transfer_after)
void test__slist_transfer_after__invalid_pos(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_pos;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;

    slist_init_n(pslist, 10);
    it_pos = slist_begin(pslist);
    it_begin = slist_begin(pslist);
    it_end = slist_end(pslist);

    it_pos._pt_container = NULL;
    expect_assert_failure(_slist_transfer_after(it_pos, it_begin, it_end));

    slist_destroy(pslist);
}

void test__slist_transfer_after__invalid_pos_end(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_pos;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;

    slist_init_n(pslist, 10);
    it_pos = slist_end(pslist);
    it_begin = slist_begin(pslist);
    it_end = slist_end(pslist);

    expect_assert_failure(_slist_transfer_after(it_pos, it_begin, it_end));

    slist_destroy(pslist);
}

void test__slist_transfer_after__invalid_begin(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_pos;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;

    slist_init_n(pslist, 10);
    it_pos = slist_begin(pslist);
    it_begin = slist_begin(pslist);
    it_end = slist_end(pslist);

    it_begin._t_containertype = 23984;
    expect_assert_failure(_slist_transfer_after(it_pos, it_begin, it_end));

    slist_destroy(pslist);
}

void test__slist_transfer_after__invalid_end(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_pos;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;

    slist_init_n(pslist, 10);
    it_pos = slist_begin(pslist);
    it_begin = slist_begin(pslist);
    it_end = slist_end(pslist);

    it_end._t_iteratortype = 345676;
    expect_assert_failure(_slist_transfer_after(it_pos, it_begin, it_end));

    slist_destroy(pslist);
}

void test__slist_transfer_after__invalid_range_not_same_slist(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);
    slist_iterator_t it_pos;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;

    slist_init_n(pslist_first, 10);
    slist_init_n(pslist_second, 24);
    it_pos = slist_begin(pslist_first);
    it_begin = slist_begin(pslist_first);
    it_end = slist_end(pslist_second);

    expect_assert_failure(_slist_transfer_after(it_pos, it_begin, it_end));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_transfer_after__invalid_range_end_before_begin(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);
    slist_iterator_t it_pos;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;

    slist_init_n(pslist_first, 10);
    slist_init_n(pslist_second, 24);
    it_pos = slist_begin(pslist_first);
    it_begin = slist_begin(pslist_second);
    it_end = slist_end(pslist_second);

    expect_assert_failure(_slist_transfer_after(it_pos, it_end, it_begin));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_transfer_after__pos_range_not_same_type(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(double);
    slist_iterator_t it_pos;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;

    slist_init_n(pslist_first, 10);
    slist_init_n(pslist_second, 24);
    it_pos = slist_begin(pslist_first);
    it_begin = slist_begin(pslist_second);
    it_end = slist_end(pslist_second);

    expect_assert_failure(_slist_transfer_after(it_pos, it_begin, it_end));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_transfer_after__does_nothing_empty_range(void** state)
{
    size_t i = 0;
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);
    slist_iterator_t it_pos;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;

    slist_init_elem(pslist_first, 10, 100);
    slist_init_n(pslist_second, 24);
    it_pos = slist_begin(pslist_first);
    it_begin = slist_begin(pslist_second);
    it_end = slist_begin(pslist_second);

    assert_true(slist_size(pslist_first) == 10);
    assert_true(slist_size(pslist_second) == 24);
    _slist_transfer_after(it_pos, it_begin, it_end);
    assert_true(slist_size(pslist_first) == 10);
    assert_true(slist_size(pslist_second) == 24);
    for(it_pos = slist_begin(pslist_first), i = 0;
        !iterator_equal(it_pos, slist_end(pslist_first));
        it_pos = iterator_next(it_pos), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_pos) == 100);
    }
    for(it_pos = slist_begin(pslist_second), i = 0;
        !iterator_equal(it_pos, slist_end(pslist_second));
        it_pos = iterator_next(it_pos), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_pos) == 0);
    }

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_transfer_after__successfully_begin_begin(void** state)
{
    size_t i = 0;
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);
    slist_iterator_t it_pos;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;

    slist_init_elem(pslist_first, 10, 100);
    slist_init_n(pslist_second, 24);
    it_pos = slist_begin(pslist_first);
    it_begin = slist_begin(pslist_second);
    it_end = iterator_advance(it_begin, 4);

    assert_true(slist_size(pslist_first) == 10);
    assert_true(slist_size(pslist_second) == 24);

    _slist_transfer_after(it_pos, it_begin, it_end);

    assert_true(slist_size(pslist_first) == 14);
    assert_true(slist_size(pslist_second) == 20);
    for(it_pos = slist_begin(pslist_first), i = 0;
        !iterator_equal(it_pos, slist_end(pslist_first));
        it_pos = iterator_next(it_pos), ++i)
    {
        if(i> 0 && i < 5)
        {
            assert_true(*(int*)iterator_get_pointer(it_pos) == 0);
        }
        else
        {
            assert_true(*(int*)iterator_get_pointer(it_pos) == 100);
        }
    }

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_transfer_after__successfully_middle_middle(void** state)
{
    size_t i = 0;
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);
    slist_iterator_t it_pos;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;

    slist_init_elem(pslist_first, 10, 100);
    slist_init_n(pslist_second, 24);
    it_pos = iterator_advance(slist_begin(pslist_first), 5);
    it_begin = iterator_advance(slist_begin(pslist_second), 5);
    it_end = iterator_advance(it_begin, 4);

    assert_true(slist_size(pslist_first) == 10);
    assert_true(slist_size(pslist_second) == 24);

    _slist_transfer_after(it_pos, it_begin, it_end);

    assert_true(slist_size(pslist_first) == 14);
    assert_true(slist_size(pslist_second) == 20);
    for(it_pos = slist_begin(pslist_first), i = 0;
        !iterator_equal(it_pos, slist_end(pslist_first));
        it_pos = iterator_next(it_pos), ++i)
    {
        if(i > 5 && i < 10)
        {
            assert_true(*(int*)iterator_get_pointer(it_pos) == 0);
        }
        else
        {
            assert_true(*(int*)iterator_get_pointer(it_pos) == 100);
        }
    }

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_transfer_after__successfully_end(void** state)
{
    size_t i = 0;
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);
    slist_iterator_t it_pos;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;

    slist_init_elem(pslist_first, 10, 100);
    slist_init_n(pslist_second, 24);
    it_pos = slist_end(pslist_first);
    it_pos = slist_previous(pslist_first, it_pos);
    it_end = slist_end(pslist_second);
    it_begin = iterator_advance(slist_begin(pslist_second), 20);

    assert_true(slist_size(pslist_first) == 10);
    assert_true(slist_size(pslist_second) == 24);

    _slist_transfer_after(it_pos, it_begin, it_end);

    assert_true(slist_size(pslist_first) == 14);
    assert_true(slist_size(pslist_second) == 20);
    for(it_pos = slist_begin(pslist_first), i = 0;
        !iterator_equal(it_pos, slist_end(pslist_first));
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

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_transfer_after__successfully_middle_all(void** state)
{
    size_t i = 0;
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);
    slist_iterator_t it_pos;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;

    slist_init_elem(pslist_first, 10, 100);
    slist_init_n(pslist_second, 24);
    it_pos = slist_end(pslist_first);
    it_pos = slist_previous(pslist_first, it_pos);
    it_begin = slist_begin(pslist_second);
    it_end = slist_end(pslist_second);

    assert_true(slist_size(pslist_first) == 10);
    assert_true(slist_size(pslist_second) == 24);

    _slist_transfer_after(it_pos, it_begin, it_end);

    assert_true(slist_size(pslist_first) == 34);
    assert_true(slist_size(pslist_second) == 0);
    for(it_pos = slist_begin(pslist_first), i = 0;
        !iterator_equal(it_pos, slist_end(pslist_first));
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

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_transfer_after__same_slist_pos_belong_to_range(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_pos;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;

    slist_init_n(pslist, 10);
    it_begin = slist_begin(pslist);
    it_end = slist_end(pslist);
    it_pos = iterator_next(it_begin);
    expect_assert_failure(_slist_transfer_after(it_pos, it_begin, it_end));

    slist_destroy(pslist);
}

void test__slist_transfer_after__same_slist_does_nothing_empty_range(void** state)
{
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_pos;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;

    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, i);
    }
    it_begin = slist_end(pslist);
    it_end = slist_end(pslist);
    it_pos = slist_begin(pslist);
    _slist_transfer_after(it_pos, it_begin, it_end);
    for(it_pos = slist_begin(pslist), i = 0;
        !iterator_equal(it_pos, slist_end(pslist));
        it_pos = iterator_next(it_pos), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_pos) == 9 - i);
    }

    slist_destroy(pslist);
}

void test__slist_transfer_after__same_slist_does_nothing_pos_equa_to_begin(void** state)
{
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_pos;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;

    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, i);
    }
    it_begin = iterator_next(slist_begin(pslist));
    it_end = slist_end(pslist);
    it_pos = slist_begin(pslist);
    _slist_transfer_after(it_pos, it_begin, it_end);
    for(it_pos = slist_begin(pslist), i = 0;
        !iterator_equal(it_pos, slist_end(pslist));
        it_pos = iterator_next(it_pos), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_pos) == 9 - i);
    }

    slist_destroy(pslist);
}

void test__slist_transfer_after__same_slist_does_nothing_pos_equa_to_end(void** state)
{
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_pos;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;

    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, i);
    }
    it_begin = slist_begin(pslist);
    it_end = slist_end(pslist);
    it_pos = slist_previous(pslist, slist_end(pslist));
    _slist_transfer_after(it_pos, it_begin, it_end);
    for(it_pos = slist_begin(pslist), i = 0;
        !iterator_equal(it_pos, slist_end(pslist));
        it_pos = iterator_next(it_pos), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_pos) == 9 - i);
    }

    slist_destroy(pslist);
}

void test__slist_transfer_after__same_slist_begin_middle(void** state)
{
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_pos;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;

    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, 9 - i);
    }
    it_pos = slist_begin(pslist);
    it_begin = iterator_advance(slist_begin(pslist), 2);
    it_end = iterator_advance(it_begin, 3);
    _slist_transfer_after(it_pos, it_begin, it_end);

    it_pos = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 0);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 2);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 3);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 4);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 1);
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

    slist_destroy(pslist);
}

void test__slist_transfer_after__same_slist_begin_end(void** state)
{
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_pos;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;

    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, 9 - i);
    }
    it_pos = slist_begin(pslist);
    it_begin = iterator_advance(slist_begin(pslist), 6);
    it_end = slist_end(pslist);
    _slist_transfer_after(it_pos, it_begin, it_end);

    it_pos = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 0);
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
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 5);

    slist_destroy(pslist);
}

void test__slist_transfer_after__same_slist_middle_begin(void** state)
{
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_pos;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;

    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, 9 - i);
    }
    it_pos = iterator_advance(slist_begin(pslist), 6);
    it_begin = slist_begin(pslist);
    it_end = iterator_next(it_begin);
    _slist_transfer_after(it_pos, it_begin, it_end);

    it_pos = slist_begin(pslist);
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
    assert_true(*(int*)iterator_get_pointer(it_pos) == 6);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 0);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 7);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 8);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 9);

    slist_destroy(pslist);
}

void test__slist_transfer_after__same_slist_middle_middle(void** state)
{
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_pos;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;

    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist,  9 - i);
    }
    it_pos = iterator_advance(slist_begin(pslist), 6);
    it_begin = iterator_next(slist_begin(pslist));
    it_end = iterator_advance(it_begin, 3);
    _slist_transfer_after(it_pos, it_begin, it_end);

    it_pos = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 0);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 4);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 5);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 6);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 1);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 2);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 3);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 7);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 8);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 9);

    slist_destroy(pslist);
}

void test__slist_transfer_after__same_slist_middle_end(void** state)
{
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_pos;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;

    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, 9 - i);
    }
    it_pos = iterator_advance(slist_begin(pslist), 6);
    it_begin = iterator_advance(slist_begin(pslist), 8);
    it_end = slist_end(pslist);
    _slist_transfer_after(it_pos, it_begin, it_end);

    it_pos = slist_begin(pslist);
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
    assert_true(*(int*)iterator_get_pointer(it_pos) == 6);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 8);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 9);
    it_pos = iterator_next(it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 7);

    slist_destroy(pslist);
}

void test__slist_transfer_after__same_slist_end_begin(void** state)
{
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_pos;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;

    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, 9 - i);
    }
    it_pos = slist_previous(pslist, slist_end(pslist));
    it_begin = slist_begin(pslist);
    it_end = iterator_advance(it_begin, 4);
    _slist_transfer_after(it_pos, it_begin, it_end);

    it_pos = slist_begin(pslist);
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

    slist_destroy(pslist);
}

void test__slist_transfer_after__same_slist_end_middle(void** state)
{
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_pos;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;

    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, 9 - i);
    }
    it_pos = slist_previous(pslist, slist_end(pslist));
    it_begin = iterator_next(slist_begin(pslist));
    it_end = iterator_advance(it_begin, 4);
    _slist_transfer_after(it_pos, it_begin, it_end);

    it_pos = slist_begin(pslist);
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

    slist_destroy(pslist);
}

