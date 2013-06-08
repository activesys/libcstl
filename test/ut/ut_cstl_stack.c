#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/citerator.h"
#include "cstl/cstl_vector_iterator.h"
#include "cstl/cstack.h"

#include "ut_def.h"
#include "ut_cstl_stack.h"

UT_SUIT_DEFINATION(cstl_stack, stack_init);

/*
 * test stack_init
 */        
UT_CASE_DEFINATION(stack_init)
void test_stack_init__null_stack_adaptor(void** state)
{
    expect_assert_failure(stack_init(NULL));
}

void test_stack_init__non_created_stack_adaptor(void** state)
{
    stack_t stack;
    stack._t_sequence._t_typeinfo._t_style = 2323;
    expect_assert_failure(stack_init(&stack));
}

void test_stack_init__successfully(void** state)
{
    stack_t* psk = create_stack(int);

    stack_init(psk);
    assert_true(stack_size(psk) == 0);

    stack_destroy(psk);
}

/*
 * test stack_init_copy
 */
UT_CASE_DEFINATION(stack_init_copy)
void test_stack_init_copy__null_dest_stack_adaptor(void** state)
{
    stack_t* psk_dest = create_stack(int);
    stack_t* psk_src = create_stack(int);

    stack_init(psk_src);
    expect_assert_failure(stack_init_copy(NULL, psk_src));

    stack_destroy(psk_dest);
    stack_destroy(psk_src);
}

void test_stack_init_copy__null_src_stack_adaptor(void** state)
{
    stack_t* psk_dest = create_stack(int);
    stack_t* psk_src = create_stack(int);

    expect_assert_failure(stack_init_copy(psk_dest, NULL));

    stack_destroy(psk_dest);
    stack_destroy(psk_src);
}

void test_stack_init_copy__non_created_dest_stack_adaptor(void** state)
{
    stack_t* psk_dest = create_stack(int);
    stack_t* psk_src = create_stack(int);

    stack_init(psk_src);
    psk_dest->_t_sequence._t_typeinfo._t_style = 23232;
    expect_assert_failure(stack_init_copy(psk_dest, psk_src));

    psk_dest->_t_sequence._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    stack_destroy(psk_dest);
    stack_destroy(psk_src);
}

void test_stack_init_copy__non_inited_src_stack_adaptor(void** state)
{
    stack_t* psk_dest = create_stack(int);
    stack_t* psk_src = create_stack(int);

    stack_init(psk_src);
    psk_src->_t_sequence._t_typeinfo._t_style = 33333;
    expect_assert_failure(stack_init_copy(psk_dest, psk_src));

    psk_src->_t_sequence._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    stack_destroy(psk_dest);
    stack_destroy(psk_src);
}

void test_stack_init_copy__not_same_type(void** state)
{
    stack_t* psk_dest = create_stack(int);
    stack_t* psk_src = create_stack(double);

    stack_init(psk_src);
    expect_assert_failure(stack_init_copy(psk_dest, psk_src));

    stack_destroy(psk_dest);
    stack_destroy(psk_src);
}

void test_stack_init_copy__init_copy_empty(void** state)
{
    stack_t* psk_dest = create_stack(int);
    stack_t* psk_src = create_stack(int);

    stack_init(psk_src);
    stack_init_copy(psk_dest, psk_src);
    assert_true(stack_size(psk_dest) == stack_size(psk_src));

    stack_destroy(psk_dest);
    stack_destroy(psk_src);
}

void test_stack_init_copy__c_builtin(void** state)
{
    stack_t* psk_dest = create_stack(int);
    stack_t* psk_src = create_stack(int);

    stack_init(psk_src);
    stack_push(psk_src, 100);
    stack_push(psk_src, 200);
    stack_push(psk_src, 300);
    stack_push(psk_src, 400);
    stack_push(psk_src, 1943);
    stack_push(psk_src, 345);
    stack_init_copy(psk_dest, psk_src);
    assert_true(stack_size(psk_dest) == stack_size(psk_src));

    assert_true(*(int*)stack_top(psk_dest) == 345);
    stack_pop(psk_dest);
    assert_true(*(int*)stack_top(psk_dest) == 1943);
    stack_pop(psk_dest);
    assert_true(*(int*)stack_top(psk_dest) == 400);
    stack_pop(psk_dest);
    assert_true(*(int*)stack_top(psk_dest) == 300);
    stack_pop(psk_dest);
    assert_true(*(int*)stack_top(psk_dest) == 200);
    stack_pop(psk_dest);
    assert_true(*(int*)stack_top(psk_dest) == 100);
    stack_pop(psk_dest);

    stack_destroy(psk_dest);
    stack_destroy(psk_src);
}

void test_stack_init_copy__cstr(void** state)
{
    stack_t* psk_dest = create_stack(char*);
    stack_t* psk_src = create_stack(char*);

    stack_init(psk_src);
    stack_push(psk_src, "222222");
    stack_push(psk_src, "aldjflakdjf");
    stack_init_copy(psk_dest, psk_src);
    assert_true(stack_size(psk_dest) == stack_size(psk_src));

    assert_true(strcmp((char*)stack_top(psk_dest), "aldjflakdjf") == 0);
    stack_pop(psk_dest);
    assert_true(strcmp((char*)stack_top(psk_dest), "222222") == 0);
    stack_pop(psk_dest);

    stack_destroy(psk_dest);
    stack_destroy(psk_src);
}

void test_stack_init_copy__libcstl_builtin(void** state)
{
    stack_t* psk_dest = create_stack(stack_t<int>);
    stack_t* psk_src = create_stack(stack_t<signed>);
    stack_t* psk_elem = create_stack(int);

    stack_init(psk_elem);
    stack_init(psk_src);
    stack_push(psk_src, psk_elem);
    stack_push(psk_elem, 0);
    stack_push(psk_src, psk_elem);
    stack_init_copy(psk_dest, psk_src);
    assert_true(stack_size(psk_dest) == stack_size(psk_src));

    assert_true(stack_size((stack_t*)stack_top(psk_dest)) == 1);
    stack_pop(psk_dest);
    assert_true(stack_size((stack_t*)stack_top(psk_dest)) == 0);
    stack_pop(psk_dest);

    stack_destroy(psk_dest);
    stack_destroy(psk_src);
    stack_destroy(psk_elem);
}

typedef struct _tag_test_stack_init_copy__user_define
{
    int n_elem;
}_test_stack_init_copy__user_define_t;
void test_stack_init_copy__user_define(void** state)
{
    stack_t* psk_dest = NULL;
    stack_t* psk_src = NULL;
    _test_stack_init_copy__user_define_t t_elem;

    type_register(_test_stack_init_copy__user_define_t, NULL, NULL, NULL, NULL);
    type_duplicate(_test_stack_init_copy__user_define_t, struct _tag_test_stack_init_copy__user_define);
    psk_dest = create_stack(_test_stack_init_copy__user_define_t);
    psk_src = create_stack(struct _tag_test_stack_init_copy__user_define);

    stack_init(psk_src);
    t_elem.n_elem = 0;
    stack_push(psk_src, &t_elem);
    t_elem.n_elem = 1;
    stack_push(psk_src, &t_elem);
    stack_init_copy(psk_dest, psk_src);
    assert_true(stack_size(psk_dest) == stack_size(psk_src));

    assert_true(((_test_stack_init_copy__user_define_t*)stack_top(psk_dest))->n_elem == 1);
    stack_pop(psk_dest);
    assert_true(((_test_stack_init_copy__user_define_t*)stack_top(psk_dest))->n_elem == 0);
    stack_pop(psk_dest);

    stack_destroy(psk_dest);
    stack_destroy(psk_src);
}

/*
 * test stack_destroy
 */
UT_CASE_DEFINATION(stack_destroy)
void test_stack_destroy__null_stack_adaptor(void** state)
{
    expect_assert_failure(stack_destroy(NULL));
}

void test_stack_destroy__non_created_stack_adaptor(void** state)
{
    stack_t* psk = create_stack(int);

    stack_init(psk);
    psk->_t_sequence._t_typeinfo._t_style = 32423;
    expect_assert_failure(stack_destroy(psk));

    psk->_t_sequence._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    stack_destroy(psk);
}

void test_stack_destroy__created_non_inited(void** state)
{
    stack_t* psk = create_stack(int);

    stack_destroy(psk);
}

void test_stack_destroy__empty(void** state)
{
    stack_t* psk = create_stack(int);

    stack_init(psk);
    stack_destroy(psk);
}

void test_stack_destroy__non_empty(void** state)
{
    stack_t* psk = create_stack(int);

    stack_init(psk);
    stack_push(psk, 2);
    stack_push(psk, 55);
    stack_destroy(psk);
}

/*
 * test stack_size
 */
UT_CASE_DEFINATION(stack_size)
void test_stack_size__null_stack_adaptor(void** state)
{
    expect_assert_failure(stack_size(NULL));
}

void test_stack_size__non_inited_stack_adaptor(void** state)
{
    stack_t* psk = create_stack(int);

    psk->_t_sequence._t_typeinfo._t_style = 434;
    expect_assert_failure(stack_size(psk));

    psk->_t_sequence._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    stack_destroy(psk);
}

void test_stack_size__empty(void** state)
{
    stack_t* psk = create_stack(int);

    stack_init(psk);
    assert_true(stack_size(psk) == 0);

    stack_destroy(psk);
}

void test_stack_size__non_empty(void** state)
{
    stack_t* psk = create_stack(int);

    stack_init(psk);
    stack_push(psk, 29);
    stack_push(psk, 29);
    stack_push(psk, 29);
    stack_push(psk, 29);
    stack_push(psk, 29);
    stack_push(psk, 29);
    stack_push(psk, 29);
    stack_push(psk, 29);
    stack_push(psk, 29);
    stack_push(psk, 29);
    assert_true(stack_size(psk) == 10);

    stack_destroy(psk);
}

/*
 * test stack_empty
 */
UT_CASE_DEFINATION(stack_empty)
void test_stack_empty__null_stack_adaptor(void** state)
{
    expect_assert_failure(stack_empty(NULL));
}

void test_stack_empty__non_inited_stack_adaptor(void** state)
{
    stack_t* psk = create_stack(int);

    psk->_t_sequence._t_typeinfo._t_style = 24345;
    expect_assert_failure(stack_empty(psk));

    psk->_t_sequence._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    stack_destroy(psk);
}

void test_stack_empty__empty(void** state)
{
    stack_t* psk = create_stack(int);

    stack_init(psk);
    assert_true(stack_empty(psk));

    stack_destroy(psk);
}

void test_stack_empty__non_empty(void** state)
{
    stack_t* psk = create_stack(int);

    stack_init(psk);
    stack_push(psk, 42);
    assert_false(stack_empty(psk));

    stack_destroy(psk);
}

/*
 * test stack_equal
 */
UT_CASE_DEFINATION(stack_equal)
void test_stack_equal__null_first(void** state)
{
    stack_t* psk = create_stack(int);
    stack_init(psk);

    expect_assert_failure(stack_equal(NULL, psk));

    stack_destroy(psk);
}

void test_stack_equal__null_second(void** state)
{
    stack_t* psk = create_stack(int);
    stack_init(psk);

    expect_assert_failure(stack_equal(psk, NULL));

    stack_destroy(psk);
}

void test_stack_equal__non_inited_first(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_second);
    psk_first->_t_sequence._t_typeinfo._t_style = 9999;
    expect_assert_failure(stack_equal(psk_first, psk_second));

    psk_first->_t_sequence._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_equal__non_inited_second(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_first);
    psk_second->_t_sequence._t_typeinfo._t_style = 23434;
    expect_assert_failure(stack_equal(psk_first, psk_second));

    psk_second->_t_sequence._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_equal__not_same_type(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(double);

    stack_init(psk_first);
    stack_init(psk_second);
    expect_assert_failure(stack_equal(psk_first, psk_second));

    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_equal__same_stack(void** state)
{
    stack_t* psk = create_stack(int);
    stack_init(psk);

    assert_true(stack_equal(psk, psk));

    stack_destroy(psk);
}

void test_stack_equal__size_first_less_than_second(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_first);
    stack_init(psk_second);
    stack_push(psk_second, 0);
    assert_false(stack_equal(psk_first, psk_second));

    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_equal__size_first_greater_than_second(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_first);
    stack_push(psk_first, 0);
    stack_push(psk_first, 0);
    stack_push(psk_first, 0);
    stack_push(psk_first, 0);
    stack_init(psk_second);
    stack_push(psk_second, 0);
    assert_false(stack_equal(psk_first, psk_second));

    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_equal__size_equal_0(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_first);
    stack_init(psk_second);
    assert_true(stack_equal(psk_first, psk_second));

    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_equal__size_equal_elem_first_less_than_second(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_first);
    stack_push(psk_first, 100);
    stack_init(psk_second);
    stack_push(psk_second, 4545);
    assert_false(stack_equal(psk_first, psk_second));

    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_equal__size_equal_elem_first_greater_than_second(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_first);
    stack_push(psk_first, 100);
    stack_init(psk_second);
    stack_push(psk_second, 45);
    assert_false(stack_equal(psk_first, psk_second));

    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_equal__size_equal_elem_equal(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_first);
    stack_push(psk_first, 100);
    stack_init(psk_second);
    stack_push(psk_second, 100);
    assert_true(stack_equal(psk_first, psk_second));

    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

/*
 * test stack_not_equal
 */
UT_CASE_DEFINATION(stack_not_equal)
void test_stack_not_equal__null_first(void** state)
{
    stack_t* psk = create_stack(int);
    stack_init(psk);

    expect_assert_failure(stack_not_equal(NULL, psk));

    stack_destroy(psk);
}

void test_stack_not_equal__null_second(void** state)
{
    stack_t* psk = create_stack(int);
    stack_init(psk);

    expect_assert_failure(stack_not_equal(psk, NULL));

    stack_destroy(psk);
}

void test_stack_not_equal__non_inited_first(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_second);
    psk_first->_t_sequence._t_typeinfo._t_style = 432432;
    expect_assert_failure(stack_not_equal(psk_first, psk_second));

    psk_first->_t_sequence._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_not_equal__non_inited_second(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_first);
    psk_second->_t_sequence._t_typeinfo._t_style = 2222;
    expect_assert_failure(stack_not_equal(psk_first, psk_second));

    psk_second->_t_sequence._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_not_equal__not_same_type(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(double);

    stack_init(psk_first);
    stack_init(psk_second);
    expect_assert_failure(stack_not_equal(psk_first, psk_second));

    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_not_equal__same_stack(void** state)
{
    stack_t* psk = create_stack(int);
    stack_init(psk);

    assert_false(stack_not_equal(psk, psk));

    stack_destroy(psk);
}

void test_stack_not_equal__size_first_less_than_second(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_first);
    stack_init(psk_second);
    stack_push(psk_second, 0);
    assert_true(stack_not_equal(psk_first, psk_second));

    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_not_equal__size_first_greater_than_second(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_first);
    stack_push(psk_first, 0);
    stack_push(psk_first, 0);
    stack_push(psk_first, 0);
    stack_push(psk_first, 0);
    stack_push(psk_first, 0);
    stack_init(psk_second);
    stack_push(psk_second, 0);
    stack_push(psk_second, 0);
    assert_true(stack_not_equal(psk_first, psk_second));

    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_not_equal__size_equal_0(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_first);
    stack_init(psk_second);
    assert_false(stack_not_equal(psk_first, psk_second));

    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_not_equal__size_equal_elem_first_less_than_second(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_first);
    stack_push(psk_first, 100);
    stack_push(psk_first, 100);
    stack_push(psk_first, 100);
    stack_init(psk_second);
    stack_push(psk_second, 4545);
    stack_push(psk_second, 4545);
    stack_push(psk_second, 4545);
    assert_true(stack_not_equal(psk_first, psk_second));

    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_not_equal__size_equal_elem_first_greater_than_second(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_first);
    stack_push(psk_first, 100);
    stack_push(psk_first, 100);
    stack_push(psk_first, 100);
    stack_init(psk_second);
    stack_push(psk_second, 45);
    stack_push(psk_second, 45);
    stack_push(psk_second, 45);
    assert_true(stack_not_equal(psk_first, psk_second));

    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_not_equal__size_equal_elem_equal(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_first);
    stack_push(psk_first, 100);
    stack_push(psk_first, 100);
    stack_push(psk_first, 100);
    stack_init(psk_second);
    stack_push(psk_second, 100);
    stack_push(psk_second, 100);
    stack_push(psk_second, 100);
    assert_false(stack_not_equal(psk_first, psk_second));

    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

/*
 * test stack_less
 */
UT_CASE_DEFINATION(stack_less)
void test_stack_less__null_first(void** state)
{
    stack_t* psk = create_stack(int);
    stack_init(psk);

    expect_assert_failure(stack_less(NULL, psk));

    stack_destroy(psk);
}

void test_stack_less__null_second(void** state)
{
    stack_t* psk = create_stack(int);
    stack_init(psk);

    expect_assert_failure(stack_less(psk, NULL));

    stack_destroy(psk);
}

void test_stack_less__non_inited_first(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_second);
    psk_first->_t_sequence._t_typeinfo._t_style = 4834;
    expect_assert_failure(stack_less(psk_first, psk_second));

    psk_first->_t_sequence._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_less__non_inited_second(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_first);
    psk_second->_t_sequence._t_typeinfo._t_style = 22222;
    expect_assert_failure(stack_less(psk_first, psk_second));

    psk_second->_t_sequence._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_less__not_same_type(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(double);

    stack_init(psk_first);
    stack_init(psk_second);
    expect_assert_failure(stack_less(psk_first, psk_second));

    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_less__same_stack(void** state)
{
    stack_t* psk = create_stack(int);
    stack_init(psk);

    assert_false(stack_less(psk, psk));

    stack_destroy(psk);
}

void test_stack_less__size_first_less_than_second(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_first);
    stack_init(psk_second);
    stack_push(psk_second, 0);
    assert_true(stack_less(psk_first, psk_second));

    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_less__size_first_greater_than_second(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_first);
    stack_push(psk_first, 0);
    stack_push(psk_first, 0);
    stack_push(psk_first, 0);
    stack_push(psk_first, 0);
    stack_init(psk_second);
    stack_push(psk_second, 0);
    stack_push(psk_second, 0);
    assert_false(stack_less(psk_first, psk_second));

    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_less__size_equal_0(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_first);
    stack_init(psk_second);
    assert_false(stack_less(psk_first, psk_second));

    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_less__size_equal_elem_first_less_than_second(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_first);
    stack_push(psk_first, 100);
    stack_push(psk_first, 100);
    stack_push(psk_first, 100);
    stack_init(psk_second);
    stack_push(psk_second, 4545);
    stack_push(psk_second, 4545);
    stack_push(psk_second, 4545);
    assert_true(stack_less(psk_first, psk_second));

    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_less__size_equal_elem_first_greater_than_second(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_first);
    stack_push(psk_first, 100);
    stack_push(psk_first, 100);
    stack_push(psk_first, 100);
    stack_init(psk_second);
    stack_push(psk_second, 45);
    stack_push(psk_second, 45);
    stack_push(psk_second, 45);
    assert_false(stack_less(psk_first, psk_second));

    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_less__size_equal_elem_equal(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_first);
    stack_push(psk_first, 100);
    stack_push(psk_first, 100);
    stack_push(psk_first, 100);
    stack_init(psk_second);
    stack_push(psk_second, 100);
    stack_push(psk_second, 100);
    stack_push(psk_second, 100);
    assert_false(stack_less(psk_first, psk_second));

    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

/*
 * test stack_less_equal
 */
UT_CASE_DEFINATION(stack_less_equal)
void test_stack_less_equal__null_first(void** state)
{
    stack_t* psk = create_stack(int);
    stack_init(psk);

    expect_assert_failure(stack_less_equal(NULL, psk));

    stack_destroy(psk);
}

void test_stack_less_equal__null_second(void** state)
{
    stack_t* psk = create_stack(int);
    stack_init(psk);

    expect_assert_failure(stack_less_equal(psk, NULL));

    stack_destroy(psk);
}

void test_stack_less_equal__non_inited_first(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_second);
    psk_first->_t_sequence._t_typeinfo._t_style = 2233;
    expect_assert_failure(stack_less_equal(psk_first, psk_second));

    psk_first->_t_sequence._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_less_equal__non_inited_second(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_first);
    psk_second->_t_sequence._t_typeinfo._t_style = 2222;
    expect_assert_failure(stack_less_equal(psk_first, psk_second));

    psk_second->_t_sequence._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_less_equal__not_same_type(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(double);

    stack_init(psk_first);
    stack_init(psk_second);
    expect_assert_failure(stack_less_equal(psk_first, psk_second));

    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_less_equal__same_stack(void** state)
{
    stack_t* psk = create_stack(int);
    stack_init(psk);

    assert_true(stack_less_equal(psk, psk));

    stack_destroy(psk);
}

void test_stack_less_equal__size_first_less_than_second(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_first);
    stack_init(psk_second);
    stack_push(psk_second, 0);
    assert_true(stack_less_equal(psk_first, psk_second));

    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_less_equal__size_first_greater_than_second(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_first);
    stack_push(psk_first, 0);
    stack_push(psk_first, 0);
    stack_push(psk_first, 0);
    stack_init(psk_second);
    stack_push(psk_second, 0);
    assert_false(stack_less_equal(psk_first, psk_second));

    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_less_equal__size_equal_0(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_first);
    stack_init(psk_second);
    assert_true(stack_less_equal(psk_first, psk_second));

    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_less_equal__size_equal_elem_first_less_than_second(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_first);
    stack_push(psk_first, 100);
    stack_push(psk_first, 100);
    stack_push(psk_first, 100);
    stack_init(psk_second);
    stack_push(psk_second, 4545);
    stack_push(psk_second, 4545);
    stack_push(psk_second, 4545);
    assert_true(stack_less_equal(psk_first, psk_second));

    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_less_equal__size_equal_elem_first_greater_than_second(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_first);
    stack_push(psk_first, 100);
    stack_push(psk_first, 100);
    stack_push(psk_first, 100);
    stack_init(psk_second);
    stack_push(psk_second, 45);
    stack_push(psk_second, 45);
    stack_push(psk_second, 45);
    assert_false(stack_less_equal(psk_first, psk_second));

    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_less_equal__size_equal_elem_equal(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_first);
    stack_push(psk_first, 100);
    stack_push(psk_first, 100);
    stack_push(psk_first, 100);
    stack_init(psk_second);
    stack_push(psk_second, 100);
    stack_push(psk_second, 100);
    stack_push(psk_second, 100);
    assert_true(stack_less_equal(psk_first, psk_second));

    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

/*
 * test stack_greater
 */
UT_CASE_DEFINATION(stack_greater)
void test_stack_greater__null_first(void** state)
{
    stack_t* psk = create_stack(int);
    stack_init(psk);

    expect_assert_failure(stack_greater(NULL, psk));

    stack_destroy(psk);
}

void test_stack_greater__null_second(void** state)
{
    stack_t* psk = create_stack(int);
    stack_init(psk);

    expect_assert_failure(stack_greater(psk, NULL));

    stack_destroy(psk);
}

void test_stack_greater__non_inited_first(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_second);
    psk_first->_t_sequence._t_typeinfo._t_style = 3455;
    expect_assert_failure(stack_greater(psk_first, psk_second));

    psk_first->_t_sequence._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_greater__non_inited_second(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_first);
    psk_second->_t_sequence._t_typeinfo._t_style = 22222;
    expect_assert_failure(stack_greater(psk_first, psk_second));

    psk_second->_t_sequence._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_greater__not_same_type(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(double);

    stack_init(psk_first);
    stack_init(psk_second);
    expect_assert_failure(stack_greater(psk_first, psk_second));

    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_greater__same_stack(void** state)
{
    stack_t* psk = create_stack(int);
    stack_init(psk);

    assert_false(stack_greater(psk, psk));

    stack_destroy(psk);
}

void test_stack_greater__size_first_less_than_second(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_first);
    stack_init(psk_second);
    stack_push(psk_second, 0);
    assert_false(stack_greater(psk_first, psk_second));

    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_greater__size_first_greater_than_second(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_first);
    stack_push(psk_first, 0);
    stack_push(psk_first, 0);
    stack_push(psk_first, 0);
    stack_push(psk_first, 0);
    stack_init(psk_second);
    stack_push(psk_second, 0);
    stack_push(psk_second, 0);
    assert_true(stack_greater(psk_first, psk_second));

    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_greater__size_equal_0(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_first);
    stack_init(psk_second);
    assert_false(stack_greater(psk_first, psk_second));

    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_greater__size_equal_elem_first_less_than_second(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_first);
    stack_push(psk_first, 100);
    stack_push(psk_first, 100);
    stack_push(psk_first, 100);
    stack_init(psk_second);
    stack_push(psk_second, 4545);
    stack_push(psk_second, 4545);
    stack_push(psk_second, 4545);
    assert_false(stack_greater(psk_first, psk_second));

    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_greater__size_equal_elem_first_greater_than_second(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_first);
    stack_push(psk_first, 100);
    stack_push(psk_first, 100);
    stack_push(psk_first, 100);
    stack_init(psk_second);
    stack_push(psk_second, 45);
    stack_push(psk_second, 45);
    stack_push(psk_second, 45);
    assert_true(stack_greater(psk_first, psk_second));

    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_greater__size_equal_elem_equal(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_first);
    stack_push(psk_first, 100);
    stack_push(psk_first, 100);
    stack_push(psk_first, 100);
    stack_init(psk_second);
    stack_push(psk_second, 100);
    stack_push(psk_second, 100);
    stack_push(psk_second, 100);
    assert_false(stack_greater(psk_first, psk_second));

    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

/*
 * test stack_greater_equal
 */
UT_CASE_DEFINATION(stack_greater_equal)
void test_stack_greater_equal__null_first(void** state)
{
    stack_t* psk = create_stack(int);
    stack_init(psk);

    expect_assert_failure(stack_greater_equal(NULL, psk));

    stack_destroy(psk);
}

void test_stack_greater_equal__null_second(void** state)
{
    stack_t* psk = create_stack(int);
    stack_init(psk);

    expect_assert_failure(stack_greater_equal(psk, NULL));

    stack_destroy(psk);
}

void test_stack_greater_equal__non_inited_first(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_second);
    psk_first->_t_sequence._t_typeinfo._t_style = 24345;
    expect_assert_failure(stack_greater_equal(psk_first, psk_second));

    psk_first->_t_sequence._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_greater_equal__non_inited_second(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_first);
    psk_second->_t_sequence._t_typeinfo._t_style = 4444;
    expect_assert_failure(stack_greater_equal(psk_first, psk_second));

    psk_second->_t_sequence._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_greater_equal__not_same_type(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(double);

    stack_init(psk_first);
    stack_init(psk_second);
    expect_assert_failure(stack_greater_equal(psk_first, psk_second));

    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_greater_equal__same_stack(void** state)
{
    stack_t* psk = create_stack(int);
    stack_init(psk);

    assert_true(stack_greater_equal(psk, psk));

    stack_destroy(psk);
}

void test_stack_greater_equal__size_first_less_than_second(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_first);
    stack_init(psk_second);
    stack_push(psk_second, 0);
    assert_false(stack_greater_equal(psk_first, psk_second));

    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_greater_equal__size_first_greater_than_second(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_first);
    stack_push(psk_first, 0);
    stack_push(psk_first, 0);
    stack_push(psk_first, 0);
    stack_push(psk_first, 0);
    stack_init(psk_second);
    stack_push(psk_second, 0);
    stack_push(psk_second, 0);
    assert_true(stack_greater_equal(psk_first, psk_second));

    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_greater_equal__size_equal_0(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_first);
    stack_init(psk_second);
    assert_true(stack_greater_equal(psk_first, psk_second));

    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_greater_equal__size_equal_elem_first_less_than_second(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_first);
    stack_push(psk_first, 100);
    stack_push(psk_first, 100);
    stack_push(psk_first, 100);
    stack_init(psk_second);
    stack_push(psk_second, 4545);
    stack_push(psk_second, 4545);
    stack_push(psk_second, 4545);
    assert_false(stack_greater_equal(psk_first, psk_second));

    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_greater_equal__size_equal_elem_first_greater_than_second(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_first);
    stack_push(psk_first, 100);
    stack_push(psk_first, 100);
    stack_push(psk_first, 100);
    stack_init(psk_second);
    stack_push(psk_second, 45);
    stack_push(psk_second, 45);
    stack_push(psk_second, 45);
    assert_true(stack_greater_equal(psk_first, psk_second));

    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

void test_stack_greater_equal__size_equal_elem_equal(void** state)
{
    stack_t* psk_first = create_stack(int);
    stack_t* psk_second = create_stack(int);

    stack_init(psk_first);
    stack_push(psk_first, 100);
    stack_push(psk_first, 100);
    stack_push(psk_first, 100);
    stack_init(psk_second);
    stack_push(psk_second, 100);
    stack_push(psk_second, 100);
    stack_push(psk_second, 100);
    assert_true(stack_greater_equal(psk_first, psk_second));

    stack_destroy(psk_first);
    stack_destroy(psk_second);
}

/*
 * test stack_assign
 */
UT_CASE_DEFINATION(stack_assign)
void test_stack_assign__null_dest(void** state)
{
    stack_t* psk = create_stack(int);
    stack_init(psk);

    expect_assert_failure(stack_assign(NULL, psk));

    stack_destroy(psk);
}

void test_stack_assign__null_src(void** state)
{
    stack_t* psk = create_stack(int);
    stack_init(psk);

    expect_assert_failure(stack_assign(psk, NULL));

    stack_destroy(psk);
}

void test_stack_assign__non_inited_dest(void** state)
{
    stack_t* psk_dest = create_stack(int);
    stack_t* psk_src = create_stack(int);

    stack_init(psk_src);

    psk_dest->_t_sequence._t_typeinfo._t_style = 232;
    expect_assert_failure(stack_assign(psk_dest, psk_src));

    psk_dest->_t_sequence._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    stack_destroy(psk_dest);
    stack_destroy(psk_src);
}

void test_stack_assign__non_inited_src(void** state)
{
    stack_t* psk_dest = create_stack(int);
    stack_t* psk_src = create_stack(int);

    stack_init(psk_dest);

    psk_src->_t_sequence._t_typeinfo._t_style = 32333;
    expect_assert_failure(stack_assign(psk_dest, psk_src));

    psk_src->_t_sequence._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    stack_destroy(psk_dest);
    stack_destroy(psk_src);
}

void test_stack_assign__not_same_type(void** state)
{
    stack_t* psk_dest = create_stack(int);
    stack_t* psk_src = create_stack(double);

    stack_init(psk_dest);
    stack_init(psk_src);

    expect_assert_failure(stack_assign(psk_dest, psk_src));

    stack_destroy(psk_dest);
    stack_destroy(psk_src);
}

void test_stack_assign__same_adaptor(void** state)
{
    stack_t* psk = create_stack(int);

    stack_init(psk);

    stack_assign(psk, psk);
    assert_true(stack_size(psk) == 0);

    stack_destroy(psk);
}

void test_stack_assign__0_assign_0(void** state)
{
    stack_t* psk_dest = create_stack(int);
    stack_t* psk_src = create_stack(int);

    stack_init(psk_dest);
    stack_init(psk_src);

    stack_assign(psk_dest, psk_src);
    assert_true(stack_size(psk_dest) == 0);
    assert_true(stack_equal(psk_dest, psk_src));

    stack_destroy(psk_dest);
    stack_destroy(psk_src);
}

void test_stack_assign__0_assign_n(void** state)
{
    stack_t* psk_dest = create_stack(int);
    stack_t* psk_src = create_stack(int);

    stack_init(psk_dest);
    stack_init(psk_src);
    stack_push(psk_src, 0);
    stack_push(psk_src, 0);
    stack_push(psk_src, 0);

    stack_assign(psk_dest, psk_src);
    assert_true(stack_size(psk_dest) == 3);
    assert_true(stack_equal(psk_dest, psk_src));

    stack_destroy(psk_dest);
    stack_destroy(psk_src);
}

void test_stack_assign__n_assign_0(void** state)
{
    stack_t* psk_dest = create_stack(int);
    stack_t* psk_src = create_stack(int);

    stack_init(psk_dest);
    stack_push(psk_dest, 23);
    stack_push(psk_dest, 23);
    stack_push(psk_dest, 23);
    stack_push(psk_dest, 23);
    stack_init(psk_src);

    stack_assign(psk_dest, psk_src);
    assert_true(stack_equal(psk_dest, psk_src));
    assert_true(stack_size(psk_dest) == 0);

    stack_destroy(psk_dest);
    stack_destroy(psk_src);
}

void test_stack_assign__n_assign_n_stack_equal(void** state)
{
    stack_t* psk_dest = create_stack(int);
    stack_t* psk_src = create_stack(int);

    stack_init(psk_dest);
    stack_push(psk_dest, 5);
    stack_push(psk_dest, 5);
    stack_push(psk_dest, 5);
    stack_push(psk_dest, 5);
    stack_init(psk_src);
    stack_push(psk_src, 5);
    stack_push(psk_src, 5);
    stack_push(psk_src, 5);
    stack_push(psk_src, 5);

    stack_assign(psk_dest, psk_src);
    assert_true(stack_equal(psk_dest, psk_src));

    stack_destroy(psk_dest);
    stack_destroy(psk_src);
}

void test_stack_assign__n_assign_n_stack_not_equal(void** state)
{
    stack_t* psk_dest = create_stack(int);
    stack_t* psk_src = create_stack(int);

    stack_init(psk_dest);
    stack_push(psk_dest, 5);
    stack_push(psk_dest, 5);
    stack_push(psk_dest, 5);
    stack_push(psk_dest, 5);
    stack_init(psk_src);
    stack_push(psk_src, 9);
    stack_push(psk_src, 9);
    stack_push(psk_src, 9);
    stack_push(psk_src, 9);

    stack_assign(psk_dest, psk_src);
    assert_true(stack_equal(psk_dest, psk_src));
    assert_true(stack_size(psk_dest) == 4);

    stack_destroy(psk_dest);
    stack_destroy(psk_src);
}

void test_stack_assign__n_assign_m(void** state)
{
    stack_t* psk_dest = create_stack(int);
    stack_t* psk_src = create_stack(int);

    stack_init(psk_dest);
    stack_push(psk_dest, 5);
    stack_push(psk_dest, 5);
    stack_push(psk_dest, 5);
    stack_push(psk_dest, 5);
    stack_init(psk_src);
    stack_push(psk_src, 9);
    stack_push(psk_src, 9);
    stack_push(psk_src, 9);
    stack_push(psk_src, 9);
    stack_push(psk_src, 9);
    stack_push(psk_src, 9);
    stack_push(psk_src, 9);
    stack_push(psk_src, 9);

    stack_assign(psk_dest, psk_src);
    assert_true(stack_equal(psk_dest, psk_src));
    assert_true(stack_size(psk_dest) == 8);

    stack_destroy(psk_dest);
    stack_destroy(psk_src);
}

/*
 * test stack_pop
 */
UT_CASE_DEFINATION(stack_pop)
void test_stack_pop__null_stack_adaptor(void** state)
{
    expect_assert_failure(stack_pop(NULL));
}

void test_stack_pop__non_inited_stack_adaptor(void** state)
{
    stack_t* psk = create_stack(int);

    psk->_t_sequence._t_typeinfo._t_style = 4444;
    expect_assert_failure(stack_pop(psk));

    psk->_t_sequence._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    stack_destroy(psk);
}

void test_stack_pop__empty(void** state)
{
    stack_t* psk = create_stack(int);

    stack_init(psk);
    expect_assert_failure(stack_pop(psk));

    stack_destroy(psk);
}

void test_stack_pop__successfully(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    stack_t* psk = create_stack(int);
    stack_init(psk);

    for(i = 0; i < 10; ++i)
    {
        stack_push(psk, i);
    }
    t_oldsize = stack_size(psk);
    assert_true(*(int*)stack_top(psk) == 9);
    stack_pop(psk);
    assert_true(stack_size(psk) == t_oldsize - 1);
    assert_true(*(int*)stack_top(psk) == 8);

    stack_destroy(psk);
}

/*
 * test stack_top
 */
UT_CASE_DEFINATION(stack_top)
void test_stack_top__null_stack_adaptor(void** state)
{
    expect_assert_failure(stack_top(NULL));
}

void test_stack_top__non_inited_stack_adaptor(void** state)
{
    stack_t* psk = create_stack(int);

    psk->_t_sequence._t_typeinfo._t_style = 4444;
    expect_assert_failure(stack_top(psk));

    psk->_t_sequence._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    stack_destroy(psk);
}

void test_stack_top__empty(void** state)
{
    stack_t* psk = create_stack(int);

    stack_init(psk);
    expect_assert_failure(stack_top(psk));

    stack_destroy(psk);
}

void test_stack_top__successfully(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    stack_t* psk = create_stack(int);
    stack_init(psk);

    for(i = 0; i < 10; ++i)
    {
        stack_push(psk, i);
    }
    t_oldsize = stack_size(psk);
    assert_true(*(int*)stack_top(psk) == 9);
    stack_pop(psk);
    assert_true(stack_size(psk) == t_oldsize - 1);
    assert_true(*(int*)stack_top(psk) == 8);

    stack_destroy(psk);
}

