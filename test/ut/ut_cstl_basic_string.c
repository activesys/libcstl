#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/cstl_iterator.h"
#include "cstl/clist.h"
#include "cstl/cvector.h"
#include "cstl/cstl_basic_string_iterator.h"
#include "cstl/cstl_basic_string_private.h"
#include "cstl/cstl_basic_string.h"
#include "cstl_basic_string_aux.h"

#include "ut_def.h"
#include "ut_cstl_basic_string.h"

UT_SUIT_DEFINATION(cstl_basic_string, basic_string_init)

/*
 * test basic_string_init
 */
UT_CASE_DEFINATION(basic_string_init)
void test_basic_string_init__null_basic_string_container(void** state)
{
    expect_assert_failure(basic_string_init(NULL));
}

void test_basic_string_init__non_created(void** state)
{
    basic_string_t bstr;
    bstr._t_vector._pby_start = (_byte_t*)0x887;
    expect_assert_failure(basic_string_init(&bstr));
}

void test_basic_string_init__successfully_c_builtin(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_init(pt_basic_string);

    assert_true(basic_string_size(pt_basic_string) == 0);
    assert_true(basic_string_capacity(pt_basic_string) == 0);

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init__successfully_cstl_builtin(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(list_t<int>);
    basic_string_init(pt_basic_string);

    assert_true(basic_string_size(pt_basic_string) == 0);
    assert_true(basic_string_capacity(pt_basic_string) == 0);

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init__successfully_cstr(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(char*);
    basic_string_init(pt_basic_string);

    assert_true(basic_string_size(pt_basic_string) == 0);
    assert_true(basic_string_capacity(pt_basic_string) == 0);

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init__successfully_user_defined(void** state)
{
    typedef struct _tagtest_basic_string_init__successfully_user_defined
    {
        int n_elem;
    }_test_basic_string_init__successfully_user_defined_t;
    basic_string_t* pt_basic_string = NULL;

    type_register(_test_basic_string_init__successfully_user_defined_t, NULL, NULL, NULL, NULL);

    pt_basic_string = create_basic_string(_test_basic_string_init__successfully_user_defined_t);
    basic_string_init(pt_basic_string);

    assert_true(basic_string_size(pt_basic_string) == 0);
    assert_true(basic_string_capacity(pt_basic_string) == 0);

    basic_string_destroy(pt_basic_string);
}

/*
 * test basic_string_init_cstr
 */
UT_CASE_DEFINATION(basic_string_init_cstr)
void test_basic_string_init_cstr__null_container(void** state)
{
    expect_assert_failure(basic_string_init_cstr(NULL, "abcdef"));
}

void test_basic_string_init_cstr__non_created_container(void** state)
{
    basic_string_t bstr;
    bstr._t_vector._t_typeinfo._t_style = 24455656;
    expect_assert_failure(basic_string_init_cstr(&bstr, "abcdefg"));
}

void test_basic_string_init_cstr__null_valuestring(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);

    expect_assert_failure(basic_string_init_cstr(pt_basic_string, NULL));

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_cstr__c_builtin_init_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    int elem = 0;

    basic_string_init_cstr(pt_basic_string, &elem);
    assert_true(basic_string_size(pt_basic_string) == 0);

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_cstr__c_builtin_init_non_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    int elems[] = {9, 5, 2, 0, 13, 5455};

    basic_string_init_cstr(pt_basic_string, elems);
    assert_true(basic_string_size(pt_basic_string) == 3);
    assert_true(*(int*)basic_string_at(pt_basic_string, 0) == 9);
    assert_true(*(int*)basic_string_at(pt_basic_string, 1) == 5);
    assert_true(*(int*)basic_string_at(pt_basic_string, 2) == 2);

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_cstr__char_init_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(char);

    basic_string_init_cstr(pt_basic_string, "");
    assert_true(basic_string_size(pt_basic_string) == 0);

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_cstr__char_init_non_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(char);

    basic_string_init_cstr(pt_basic_string, "abc");
    assert_true(basic_string_size(pt_basic_string) == 3);
    assert_true(*(char*)basic_string_at(pt_basic_string, 0) == 'a');
    assert_true(*(char*)basic_string_at(pt_basic_string, 1) == 'b');
    assert_true(*(char*)basic_string_at(pt_basic_string, 2) == 'c');

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_cstr__cstr_init_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(char*);
    const char* elems[] = {NULL};

    basic_string_init_cstr(pt_basic_string, elems);
    assert_true(basic_string_size(pt_basic_string) == 0);

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_cstr__cstr_init_non_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(char*);
    const char* elems[] = {"abc", "def", "hij", NULL};

    basic_string_init_cstr(pt_basic_string, elems);
    assert_true(basic_string_size(pt_basic_string) == 3);
    assert_true(strcmp((char*)basic_string_at(pt_basic_string, 0), "abc") == 0);
    assert_true(strcmp((char*)basic_string_at(pt_basic_string, 1), "def") == 0);
    assert_true(strcmp((char*)basic_string_at(pt_basic_string, 2), "hij") == 0);

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_cstr__libcstl_builtin_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(list_t<int>);
    list_t* elems[] = {NULL};

    basic_string_init_cstr(pt_basic_string, elems);
    assert_true(basic_string_size(pt_basic_string) == 0);

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_cstr__libcstl_builtin_non_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(list_t<int>);
    list_t* plist = create_list(int);
    list_t* elems[5];

    list_init(plist);
    elems[0] = plist;
    elems[1] = plist;
    elems[2] = plist;
    elems[3] = NULL;
    elems[4] = plist;
    basic_string_init_cstr(pt_basic_string, elems);
    assert_true(basic_string_size(pt_basic_string) == 3);

    basic_string_destroy(pt_basic_string);
    list_destroy(plist);
}

typedef struct _tag_test_basic_string_init_cstr__user_define
{
    int n_elem;
    double d_elem;
}_test_basic_string_init_cstr__user_define_t;
void test_basic_string_init_cstr__user_define_empty(void** state)
{
    basic_string_t* pt_basic_string = NULL;
    _test_basic_string_init_cstr__user_define_t* elems[] = {NULL};

    type_register(_test_basic_string_init_cstr__user_define_t, NULL, NULL, NULL, NULL);
    pt_basic_string = create_basic_string(_test_basic_string_init_cstr__user_define_t);

    basic_string_init_cstr(pt_basic_string, elems);
    assert_true(basic_string_size(pt_basic_string) == 0);

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_cstr__user_define_non_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(_test_basic_string_init_cstr__user_define_t);
    _test_basic_string_init_cstr__user_define_t t_user1;
    _test_basic_string_init_cstr__user_define_t t_user2;
    _test_basic_string_init_cstr__user_define_t* elems[5] = {&t_user1, &t_user2, &t_user2, NULL, &t_user1};

    t_user1.n_elem = 4;
    t_user1.d_elem = 9.4;
    t_user2.n_elem = 0;
    t_user2.d_elem = 0.0;
    basic_string_init_cstr(pt_basic_string, elems);
    assert_true(basic_string_size(pt_basic_string) == 3);
    assert_true(((_test_basic_string_init_cstr__user_define_t*)basic_string_at(pt_basic_string, 0))->n_elem == 4);
    assert_true(((_test_basic_string_init_cstr__user_define_t*)basic_string_at(pt_basic_string, 0))->d_elem == 9.4);
    assert_true(((_test_basic_string_init_cstr__user_define_t*)basic_string_at(pt_basic_string, 1))->n_elem == 0);
    assert_true(((_test_basic_string_init_cstr__user_define_t*)basic_string_at(pt_basic_string, 1))->d_elem == 0.0);
    assert_true(((_test_basic_string_init_cstr__user_define_t*)basic_string_at(pt_basic_string, 2))->n_elem == 0);
    assert_true(((_test_basic_string_init_cstr__user_define_t*)basic_string_at(pt_basic_string, 2))->d_elem == 0.0);

    basic_string_destroy(pt_basic_string);
}

/*
 * test basic_string_init_subcstr
 */
UT_CASE_DEFINATION(basic_string_init_subcstr)
void test_basic_string_init_subcstr__null_container(void** state)
{
    expect_assert_failure(basic_string_init_subcstr(NULL, "abcdef", 0));
}

void test_basic_string_init_subcstr__non_created_container(void** state)
{
    basic_string_t bstr;
    bstr._t_vector._t_typeinfo._t_style = 24455656;
    expect_assert_failure(basic_string_init_subcstr(&bstr, "abcdefg", NPOS));
}

void test_basic_string_init_subcstr__null_valuestring(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);

    expect_assert_failure(basic_string_init_subcstr(pt_basic_string, NULL, NPOS));

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_subcstr__c_builtin_init_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    int elems[] = {9, 5, 2, 0, 13, 5455};

    basic_string_init_subcstr(pt_basic_string, elems, 0);
    assert_true(basic_string_size(pt_basic_string) == 0);

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_subcstr__c_builtin_init_non_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    int elems[] = {9, 5, 2, 0, 13, 5455};

    basic_string_init_subcstr(pt_basic_string, elems, 2);
    assert_true(basic_string_size(pt_basic_string) == 2);
    assert_true(*(int*)basic_string_at(pt_basic_string, 0) == 9);
    assert_true(*(int*)basic_string_at(pt_basic_string, 1) == 5);

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_subcstr__c_builtin_init_total(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    int elems[] = {9, 5, 2, 0, 13, 5455};

    basic_string_init_subcstr(pt_basic_string, elems, 3);
    assert_true(basic_string_size(pt_basic_string) == 3);
    assert_true(*(int*)basic_string_at(pt_basic_string, 0) == 9);
    assert_true(*(int*)basic_string_at(pt_basic_string, 1) == 5);
    assert_true(*(int*)basic_string_at(pt_basic_string, 2) == 2);

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_subcstr__char_init_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(char);

    basic_string_init_subcstr(pt_basic_string, "abc", 0);
    assert_true(basic_string_size(pt_basic_string) == 0);

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_subcstr__char_init_non_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(char);

    basic_string_init_subcstr(pt_basic_string, "abc", 1);
    assert_true(basic_string_size(pt_basic_string) == 1);
    assert_true(*(char*)basic_string_at(pt_basic_string, 0) == 'a');

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_subcstr__char_init_total(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(char);

    basic_string_init_subcstr(pt_basic_string, "abc", 100);
    assert_true(basic_string_size(pt_basic_string) == 3);
    assert_true(*(char*)basic_string_at(pt_basic_string, 0) == 'a');
    assert_true(*(char*)basic_string_at(pt_basic_string, 1) == 'b');
    assert_true(*(char*)basic_string_at(pt_basic_string, 2) == 'c');

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_subcstr__cstr_init_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(char*);
    const char* elems[] = {"abc", "def", "hij", NULL};

    basic_string_init_subcstr(pt_basic_string, elems, 0);
    assert_true(basic_string_size(pt_basic_string) == 0);

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_subcstr__cstr_init_non_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(char*);
    const char* elems[] = {"abc", "def", "hij", NULL};

    basic_string_init_subcstr(pt_basic_string, elems, 2);
    assert_true(basic_string_size(pt_basic_string) == 2);
    assert_true(strcmp((char*)basic_string_at(pt_basic_string, 0), "abc") == 0);
    assert_true(strcmp((char*)basic_string_at(pt_basic_string, 1), "def") == 0);

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_subcstr__cstr_init_total(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(char*);
    const char* elems[] = {"abc", "def", "hij", NULL};

    basic_string_init_subcstr(pt_basic_string, elems, NPOS);
    assert_true(basic_string_size(pt_basic_string) == 3);
    assert_true(strcmp((char*)basic_string_at(pt_basic_string, 0), "abc") == 0);
    assert_true(strcmp((char*)basic_string_at(pt_basic_string, 1), "def") == 0);
    assert_true(strcmp((char*)basic_string_at(pt_basic_string, 2), "hij") == 0);

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_subcstr__libcstl_builtin_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(list_t<int>);
    list_t* plist = create_list(int);
    list_t* elems[5];

    list_init(plist);
    elems[0] = plist;
    elems[1] = plist;
    elems[2] = plist;
    elems[3] = NULL;
    elems[4] = plist;
    basic_string_init_subcstr(pt_basic_string, elems, 0);
    assert_true(basic_string_size(pt_basic_string) == 0);

    basic_string_destroy(pt_basic_string);
    list_destroy(plist);
}

void test_basic_string_init_subcstr__libcstl_builtin_non_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(list_t<int>);
    list_t* plist = create_list(int);
    list_t* elems[5];

    list_init(plist);
    elems[0] = plist;
    elems[1] = plist;
    elems[2] = plist;
    elems[3] = NULL;
    elems[4] = plist;
    basic_string_init_subcstr(pt_basic_string, elems, 1);
    assert_true(basic_string_size(pt_basic_string) == 1);

    basic_string_destroy(pt_basic_string);
    list_destroy(plist);
}

void test_basic_string_init_subcstr__libcstl_builtin_total(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(list_t<int>);
    list_t* plist = create_list(int);
    list_t* elems[5];

    list_init(plist);
    elems[0] = plist;
    elems[1] = plist;
    elems[2] = plist;
    elems[3] = NULL;
    elems[4] = plist;
    basic_string_init_subcstr(pt_basic_string, elems, NPOS);
    assert_true(basic_string_size(pt_basic_string) == 3);

    basic_string_destroy(pt_basic_string);
    list_destroy(plist);
}

typedef struct _tag_test_basic_string_init_subcstr__user_define
{
    int n_elem;
    double d_elem;
}_test_basic_string_init_subcstr__user_define_t;
void test_basic_string_init_subcstr__user_define_empty(void** state)
{
    basic_string_t* pt_basic_string = NULL;
    _test_basic_string_init_subcstr__user_define_t t_user;
    _test_basic_string_init_subcstr__user_define_t* elems[5] = {&t_user, &t_user, &t_user, NULL, &t_user};

    type_register(_test_basic_string_init_subcstr__user_define_t, NULL, NULL, NULL, NULL);
    pt_basic_string = create_basic_string(_test_basic_string_init_subcstr__user_define_t);

    basic_string_init_subcstr(pt_basic_string, elems, 0);
    assert_true(basic_string_size(pt_basic_string) == 0);

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_subcstr__user_define_non_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(_test_basic_string_init_subcstr__user_define_t);
    _test_basic_string_init_subcstr__user_define_t t_user;
    _test_basic_string_init_subcstr__user_define_t* elems[5] = {&t_user, &t_user, &t_user, NULL, &t_user};

    t_user.n_elem = 4;
    t_user.d_elem = 0.0;
    basic_string_init_subcstr(pt_basic_string, elems, 1);
    assert_true(basic_string_size(pt_basic_string) == 1);
    assert_true(((_test_basic_string_init_subcstr__user_define_t*)basic_string_at(pt_basic_string, 0))->n_elem == 4);
    assert_true(((_test_basic_string_init_subcstr__user_define_t*)basic_string_at(pt_basic_string, 0))->d_elem == 0.0);

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_subcstr__user_define_total(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(_test_basic_string_init_subcstr__user_define_t);
    _test_basic_string_init_subcstr__user_define_t t_user1;
    _test_basic_string_init_subcstr__user_define_t t_user2;
    _test_basic_string_init_subcstr__user_define_t t_user3;
    _test_basic_string_init_subcstr__user_define_t* elems[5] = {&t_user1, &t_user2, &t_user3, NULL, &t_user1};

    t_user1.n_elem = 4; t_user1.d_elem = 0.0;
    t_user2.n_elem = 0; t_user2.d_elem = 9.24;
    t_user3.n_elem = 0; t_user3.d_elem = 0.0;
    basic_string_init_subcstr(pt_basic_string, elems, NPOS);
    assert_true(basic_string_size(pt_basic_string) == 3);
    assert_true(((_test_basic_string_init_subcstr__user_define_t*)basic_string_at(pt_basic_string, 0))->n_elem == 4);
    assert_true(((_test_basic_string_init_subcstr__user_define_t*)basic_string_at(pt_basic_string, 0))->d_elem == 0.0);
    assert_true(((_test_basic_string_init_subcstr__user_define_t*)basic_string_at(pt_basic_string, 1))->n_elem == 0);
    assert_true(((_test_basic_string_init_subcstr__user_define_t*)basic_string_at(pt_basic_string, 1))->d_elem == 9.24);
    assert_true(((_test_basic_string_init_subcstr__user_define_t*)basic_string_at(pt_basic_string, 2))->n_elem == 0);
    assert_true(((_test_basic_string_init_subcstr__user_define_t*)basic_string_at(pt_basic_string, 2))->d_elem == 0.0);

    basic_string_destroy(pt_basic_string);
}

/*
 * test basic_string_init_copy
 */
UT_CASE_DEFINATION(basic_string_init_copy)
void test_basic_string_init_copy__null_dest(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_init(pt_basic_string);

    expect_assert_failure(basic_string_init_copy(NULL, pt_basic_string));

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_copy__null_src(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);

    expect_assert_failure(basic_string_init_copy(pt_basic_string, NULL));

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_copy__non_create_dest(void** state)
{
    basic_string_t bstr;
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_init(pt_basic_string);

    bstr._t_vector._t_typeinfo._pt_type = NULL;
    expect_assert_failure(basic_string_init_copy(&bstr, pt_basic_string));

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_copy__non_inited_src(void** state)
{
    basic_string_t* pt_dest = create_basic_string(int);
    basic_string_t* pt_src = create_basic_string(int);

    pt_src->_t_vector._pby_finish = (_byte_t*)0x732;
    expect_assert_failure(basic_string_init_copy(pt_dest, pt_src));

    pt_src->_t_vector._pby_finish = NULL;
    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy__not_same_type(void** state)
{
    basic_string_t* pt_dest = create_basic_string(int);
    basic_string_t* pt_src = create_basic_string(double);
    basic_string_init(pt_src);

    expect_assert_failure(basic_string_init_copy(pt_dest, pt_src));

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy__successfully_c_builtin_empty(void** state)
{
    basic_string_t* pt_dest = create_basic_string(int);
    basic_string_t* pt_src = create_basic_string(int);
    basic_string_init(pt_src);

    basic_string_init_copy(pt_dest, pt_src);
    assert_true(basic_string_size(pt_dest) == basic_string_size(pt_src));
    assert_true(basic_string_capacity(pt_dest) == 0);

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy__successfully_c_builtin_little(void** state)
{
    size_t i = 0;
    basic_string_t* pt_dest = create_basic_string(int);
    basic_string_t* pt_src = create_basic_string(int);
    basic_string_init_elem(pt_src, 10, 2010);

    basic_string_init_copy(pt_dest, pt_src);
    assert_true(basic_string_size(pt_dest) == basic_string_size(pt_src));
    assert_true(basic_string_capacity(pt_dest) == 26);
    for(i = 0; i < basic_string_size(pt_dest); ++i)
    {
        assert_true(*(int*)basic_string_at(pt_dest, i) == 2010);
    }

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy__successfully_c_builtin_huge(void** state)
{
    size_t i = 0;
    basic_string_t* pt_dest = create_basic_string(int);
    basic_string_t* pt_src = create_basic_string(int);
    basic_string_init_elem(pt_src, 1000, 2010);

    basic_string_init_copy(pt_dest, pt_src);
    assert_true(basic_string_size(pt_dest) == basic_string_size(pt_src));
    assert_true(basic_string_capacity(pt_dest) == 1500);
    for(i = 0; i < basic_string_size(pt_dest); ++i)
    {
        assert_true(*(int*)basic_string_at(pt_dest, i) == 2010);
    }

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy__successfully_cstr_empty(void** state)
{
    basic_string_t* pt_dest = create_basic_string(char*);
    basic_string_t* pt_src = create_basic_string(char*);
    basic_string_init(pt_src);

    basic_string_init_copy(pt_dest, pt_src);
    assert_true(basic_string_size(pt_dest) == basic_string_size(pt_src));
    assert_true(basic_string_capacity(pt_dest) == 0);

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy__successfully_cstr_little(void** state)
{
    size_t i = 0;
    basic_string_t* pt_dest = create_basic_string(char*);
    basic_string_t* pt_src = create_basic_string(char*);
    basic_string_init_elem(pt_src, 19, "c-string");

    basic_string_init_copy(pt_dest, pt_src);
    assert_true(basic_string_size(pt_dest) == basic_string_size(pt_src));
    assert_true(basic_string_capacity(pt_dest) == 35);
    for(i = 0; i < basic_string_size(pt_dest); ++i)
    {
        assert_true(strcmp((char*)basic_string_at(pt_dest, i), "c-string") == 0);
    }

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy__successfully_cstr_huge(void** state)
{
    size_t i = 0;
    basic_string_t* pt_dest = create_basic_string(char*);
    basic_string_t* pt_src = create_basic_string(char*);
    basic_string_init_elem(pt_src, 19000, "c-string");

    basic_string_init_copy(pt_dest, pt_src);
    assert_true(basic_string_size(pt_dest) == basic_string_size(pt_src));
    assert_true(basic_string_capacity(pt_dest) == 28500);
    for(i = 0; i < basic_string_size(pt_dest); ++i)
    {
        assert_true(strcmp((char*)basic_string_at(pt_dest, i), "c-string") == 0);
    }

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy__successfully_cstl_builtin_empty(void** state)
{
    basic_string_t* pt_dest = create_basic_string(list_t<int>);
    basic_string_t* pt_src = create_basic_string(list_t<int>);
    list_t* pt_elem = create_list(int);
    list_init_elem(pt_elem, 23, 21234);
    basic_string_init(pt_src);

    basic_string_init_copy(pt_dest, pt_src);
    assert_true(basic_string_size(pt_dest) == basic_string_size(pt_src));
    assert_true(basic_string_capacity(pt_dest) == 0);

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
    list_destroy(pt_elem);
}

void test_basic_string_init_copy__successfully_cstl_builtin_little(void** state)
{
    size_t i = 0;
    basic_string_t* pt_dest = create_basic_string(list_t<int>);
    basic_string_t* pt_src = create_basic_string(list_t<int>);
    list_t* pt_elem = create_list(int);
    list_init_elem(pt_elem, 23, 21234);
    basic_string_init_elem(pt_src, 32, pt_elem);

    basic_string_init_copy(pt_dest, pt_src);
    assert_true(basic_string_size(pt_dest) == basic_string_size(pt_src));
    assert_true(basic_string_capacity(pt_dest) == 48);
    for(i = 0; i < basic_string_size(pt_dest); ++i)
    {
        assert_true(list_equal((list_t*)basic_string_at(pt_dest, i), pt_elem));
    }

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
    list_destroy(pt_elem);
}

void test_basic_string_init_copy__successfully_cstl_builtin_huge(void** state)
{
    size_t i = 0;
    basic_string_t* pt_dest = create_basic_string(list_t<int>);
    basic_string_t* pt_src = create_basic_string(list_t<int>);
    list_t* pt_elem = create_list(int);
    list_init_elem(pt_elem, 23, 21234);
    basic_string_init_elem(pt_src, 3702, pt_elem);

    basic_string_init_copy(pt_dest, pt_src);
    assert_true(basic_string_size(pt_dest) == basic_string_size(pt_src));
    assert_true(basic_string_capacity(pt_dest) == 5553);
    for(i = 0; i < basic_string_size(pt_dest); ++i)
    {
        assert_true(list_equal((list_t*)basic_string_at(pt_dest, i), pt_elem));
    }

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
    list_destroy(pt_elem);
}

typedef struct _tag_test_basic_string_init_copy__successfully_user_define
{
    int n_elem;
}_test_basic_string_init_copy__successfully_user_define_t;
void test_basic_string_init_copy__successfully_user_define_empty(void** state)
{
    basic_string_t* pt_dest = NULL;
    basic_string_t* pt_src = NULL;
    type_register(_test_basic_string_init_copy__successfully_user_define_t, NULL, NULL, NULL, NULL);
    pt_dest = create_basic_string(_test_basic_string_init_copy__successfully_user_define_t);
    pt_src = create_basic_string(_test_basic_string_init_copy__successfully_user_define_t);
    basic_string_init(pt_src);

    basic_string_init_copy(pt_dest, pt_src);
    assert_true(basic_string_size(pt_dest) == basic_string_size(pt_src));
    assert_true(basic_string_capacity(pt_dest) == 0);

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy__successfully_user_define_little(void** state)
{
    size_t i = 0;
    _test_basic_string_init_copy__successfully_user_define_t t_user;
    basic_string_t* pt_dest = create_basic_string(_test_basic_string_init_copy__successfully_user_define_t);
    basic_string_t* pt_src = create_basic_string(_test_basic_string_init_copy__successfully_user_define_t);
    t_user.n_elem = 100;
    basic_string_init_elem(pt_src, 17, &t_user);

    basic_string_init_copy(pt_dest, pt_src);
    assert_true(basic_string_size(pt_dest) == basic_string_size(pt_src));
    assert_true(basic_string_capacity(pt_dest) == 33);
    for(i = 0; i < basic_string_size(pt_dest); ++i)
    {
        assert_true(memcmp(
            (_test_basic_string_init_copy__successfully_user_define_t*)basic_string_at(pt_dest, i), &t_user, sizeof(t_user)) == 0);
    }

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy__successfully_user_define_huge(void** state)
{
    size_t i = 0;
    _test_basic_string_init_copy__successfully_user_define_t t_user;
    basic_string_t* pt_dest = create_basic_string(_test_basic_string_init_copy__successfully_user_define_t);
    basic_string_t* pt_src = create_basic_string(_test_basic_string_init_copy__successfully_user_define_t);
    t_user.n_elem = 100;
    basic_string_init_elem(pt_src, 11117, &t_user);

    basic_string_init_copy(pt_dest, pt_src);
    assert_true(basic_string_size(pt_dest) == basic_string_size(pt_src));
    assert_true(basic_string_capacity(pt_dest) == 16675);
    for(i = 0; i < basic_string_size(pt_dest); ++i)
    {
        assert_true(memcmp(
            (_test_basic_string_init_copy__successfully_user_define_t*)basic_string_at(pt_dest, i), &t_user, sizeof(t_user)) == 0);
    }

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

