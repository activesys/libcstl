#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/cqueue.h"

#include "ut_def.h"
#include "ut_cstl_queue.h"

UT_SUIT_DEFINATION(cstl_queue, queue_init)

/*
 * test queue_init
 */        
UT_CASE_DEFINATION(queue_init)
void test_queue_init__null_queue_adaptor(void** state)
{
    expect_assert_failure(queue_init(NULL));
}

void test_queue_init__non_created_queue_adaptor(void** state)
{
    queue_t queue;
    queue._t_sequence._t_typeinfo._t_style = 2323;
    expect_assert_failure(queue_init(&queue));
}

void test_queue_init__successfully(void** state)
{
    queue_t* pque = create_queue(int);

    queue_init(pque);
    assert_true(queue_size(pque) == 0);

    queue_destroy(pque);
}

/*
 * test queue_init_copy
 */
UT_CASE_DEFINATION(queue_init_copy)
void test_queue_init_copy__null_dest_queue_adaptor(void** state)
{
    queue_t* pque_dest = create_queue(int);
    queue_t* pque_src = create_queue(int);

    queue_init(pque_src);
    expect_assert_failure(queue_init_copy(NULL, pque_src));

    queue_destroy(pque_dest);
    queue_destroy(pque_src);
}

void test_queue_init_copy__null_src_queue_adaptor(void** state)
{
    queue_t* pque_dest = create_queue(int);
    queue_t* pque_src = create_queue(int);

    expect_assert_failure(queue_init_copy(pque_dest, NULL));

    queue_destroy(pque_dest);
    queue_destroy(pque_src);
}

void test_queue_init_copy__non_created_dest_queue_adaptor(void** state)
{
    queue_t* pque_dest = create_queue(int);
    queue_t* pque_src = create_queue(int);

    queue_init(pque_src);
    pque_dest->_t_sequence._t_typeinfo._t_style = 23232;
    expect_assert_failure(queue_init_copy(pque_dest, pque_src));

    pque_dest->_t_sequence._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    queue_destroy(pque_dest);
    queue_destroy(pque_src);
}

void test_queue_init_copy__non_inited_src_queue_adaptor(void** state)
{
    queue_t* pque_dest = create_queue(int);
    queue_t* pque_src = create_queue(int);

    queue_init(pque_src);
    pque_src->_t_sequence._t_typeinfo._t_style = 33333;
    expect_assert_failure(queue_init_copy(pque_dest, pque_src));

    pque_src->_t_sequence._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    queue_destroy(pque_dest);
    queue_destroy(pque_src);
}

void test_queue_init_copy__not_same_type(void** state)
{
    queue_t* pque_dest = create_queue(int);
    queue_t* pque_src = create_queue(double);

    queue_init(pque_src);
    expect_assert_failure(queue_init_copy(pque_dest, pque_src));

    queue_destroy(pque_dest);
    queue_destroy(pque_src);
}

void test_queue_init_copy__init_copy_empty(void** state)
{
    queue_t* pque_dest = create_queue(int);
    queue_t* pque_src = create_queue(int);

    queue_init(pque_src);
    queue_init_copy(pque_dest, pque_src);
    assert_true(queue_size(pque_dest) == queue_size(pque_src));

    queue_destroy(pque_dest);
    queue_destroy(pque_src);
}

void test_queue_init_copy__c_builtin(void** state)
{
    queue_t* pque_dest = create_queue(int);
    queue_t* pque_src = create_queue(int);

    queue_init(pque_src);
    queue_push(pque_src, 345);
    queue_push(pque_src, 1943);
    queue_push(pque_src, 400);
    queue_push(pque_src, 300);
    queue_push(pque_src, 200);
    queue_push(pque_src, 100);
    queue_init_copy(pque_dest, pque_src);
    assert_true(queue_size(pque_dest) == queue_size(pque_src));

    assert_true(*(int*)queue_front(pque_dest) == 345);
    queue_pop(pque_dest);
    assert_true(*(int*)queue_front(pque_dest) == 1943);
    queue_pop(pque_dest);
    assert_true(*(int*)queue_front(pque_dest) == 400);
    queue_pop(pque_dest);
    assert_true(*(int*)queue_front(pque_dest) == 300);
    queue_pop(pque_dest);
    assert_true(*(int*)queue_front(pque_dest) == 200);
    queue_pop(pque_dest);
    assert_true(*(int*)queue_front(pque_dest) == 100);
    queue_pop(pque_dest);

    queue_destroy(pque_dest);
    queue_destroy(pque_src);
}

void test_queue_init_copy__cstr(void** state)
{
    queue_t* pque_dest = create_queue(char*);
    queue_t* pque_src = create_queue(char*);

    queue_init(pque_src);
    queue_push(pque_src, "aldjflakdjf");
    queue_push(pque_src, "222222");
    queue_init_copy(pque_dest, pque_src);
    assert_true(queue_size(pque_dest) == queue_size(pque_src));

    assert_true(strcmp((char*)queue_front(pque_dest), "aldjflakdjf") == 0);
    queue_pop(pque_dest);
    assert_true(strcmp((char*)queue_front(pque_dest), "222222") == 0);
    queue_pop(pque_dest);

    queue_destroy(pque_dest);
    queue_destroy(pque_src);
}

void test_queue_init_copy__libcstl_builtin(void** state)
{
    queue_t* pque_dest = create_queue(queue_t<int>);
    queue_t* pque_src = create_queue(queue_t<signed>);
    queue_t* pque_elem = create_queue(int);

    queue_init(pque_elem);
    queue_init(pque_src);
    queue_push(pque_src, pque_elem);
    queue_push(pque_elem, 0);
    queue_push(pque_src, pque_elem);
    queue_init_copy(pque_dest, pque_src);
    assert_true(queue_size(pque_dest) == queue_size(pque_src));

    assert_true(queue_size((queue_t*)queue_front(pque_dest)) == 0);
    queue_pop(pque_dest);
    assert_true(queue_size((queue_t*)queue_front(pque_dest)) == 1);
    queue_pop(pque_dest);

    queue_destroy(pque_dest);
    queue_destroy(pque_src);
    queue_destroy(pque_elem);
}

typedef struct _tag_test_queue_init_copy__user_define
{
    int n_elem;
}_test_queue_init_copy__user_define_t;
void test_queue_init_copy__user_define(void** state)
{
    queue_t* pque_dest = NULL;
    queue_t* pque_src = NULL;
    _test_queue_init_copy__user_define_t t_elem;

    type_register(_test_queue_init_copy__user_define_t, NULL, NULL, NULL, NULL);
    type_duplicate(_test_queue_init_copy__user_define_t, struct _tag_test_queue_init_copy__user_define);
    pque_dest = create_queue(_test_queue_init_copy__user_define_t);
    pque_src = create_queue(struct _tag_test_queue_init_copy__user_define);

    queue_init(pque_src);
    t_elem.n_elem = 0;
    queue_push(pque_src, &t_elem);
    t_elem.n_elem = 1;
    queue_push(pque_src, &t_elem);
    queue_init_copy(pque_dest, pque_src);
    assert_true(queue_size(pque_dest) == queue_size(pque_src));

    assert_true(((_test_queue_init_copy__user_define_t*)queue_front(pque_dest))->n_elem == 0);
    queue_pop(pque_dest);
    assert_true(((_test_queue_init_copy__user_define_t*)queue_front(pque_dest))->n_elem == 1);
    queue_pop(pque_dest);

    queue_destroy(pque_dest);
    queue_destroy(pque_src);
}

/*
 * test queue_destroy
 */
UT_CASE_DEFINATION(queue_destroy)
void test_queue_destroy__null_queue_adaptor(void** state)
{
    expect_assert_failure(queue_destroy(NULL));
}

void test_queue_destroy__non_created_queue_adaptor(void** state)
{
    queue_t* pque = create_queue(int);

    queue_init(pque);
    pque->_t_sequence._t_typeinfo._t_style = 32423;
    expect_assert_failure(queue_destroy(pque));

    pque->_t_sequence._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    queue_destroy(pque);
}

void test_queue_destroy__created_non_inited(void** state)
{
    queue_t* pque = create_queue(int);

    queue_destroy(pque);
}

void test_queue_destroy__empty(void** state)
{
    queue_t* pque = create_queue(int);

    queue_init(pque);
    queue_destroy(pque);
}

void test_queue_destroy__non_empty(void** state)
{
    queue_t* pque = create_queue(int);

    queue_init(pque);
    queue_push(pque, 2);
    queue_push(pque, 55);
    queue_destroy(pque);
}

/*
 * test queue_size
 */
UT_CASE_DEFINATION(queue_size)
void test_queue_size__null_queue_adaptor(void** state)
{
    expect_assert_failure(queue_size(NULL));
}

void test_queue_size__non_inited_queue_adaptor(void** state)
{
    queue_t* pque = create_queue(int);

    pque->_t_sequence._t_typeinfo._t_style = 434;
    expect_assert_failure(queue_size(pque));

    pque->_t_sequence._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    queue_destroy(pque);
}

void test_queue_size__empty(void** state)
{
    queue_t* pque = create_queue(int);

    queue_init(pque);
    assert_true(queue_size(pque) == 0);

    queue_destroy(pque);
}

void test_queue_size__non_empty(void** state)
{
    queue_t* pque = create_queue(int);

    queue_init(pque);
    queue_push(pque, 29);
    queue_push(pque, 29);
    queue_push(pque, 29);
    queue_push(pque, 29);
    queue_push(pque, 29);
    queue_push(pque, 29);
    queue_push(pque, 29);
    queue_push(pque, 29);
    queue_push(pque, 29);
    queue_push(pque, 29);
    assert_true(queue_size(pque) == 10);

    queue_destroy(pque);
}

/*
 * test queue_empty
 */
UT_CASE_DEFINATION(queue_empty)
void test_queue_empty__null_queue_adaptor(void** state)
{
    expect_assert_failure(queue_empty(NULL));
}

void test_queue_empty__non_inited_queue_adaptor(void** state)
{
    queue_t* pque = create_queue(int);

    pque->_t_sequence._t_typeinfo._t_style = 24345;
    expect_assert_failure(queue_empty(pque));

    pque->_t_sequence._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    queue_destroy(pque);
}

void test_queue_empty__empty(void** state)
{
    queue_t* pque = create_queue(int);

    queue_init(pque);
    assert_true(queue_empty(pque));

    queue_destroy(pque);
}

void test_queue_empty__non_empty(void** state)
{
    queue_t* pque = create_queue(int);

    queue_init(pque);
    queue_push(pque, 42);
    assert_false(queue_empty(pque));

    queue_destroy(pque);
}

/*
 * test queue_equal
 */
UT_CASE_DEFINATION(queue_equal)
void test_queue_equal__null_first(void** state)
{
    queue_t* pque = create_queue(int);
    queue_init(pque);

    expect_assert_failure(queue_equal(NULL, pque));

    queue_destroy(pque);
}

void test_queue_equal__null_second(void** state)
{
    queue_t* pque = create_queue(int);
    queue_init(pque);

    expect_assert_failure(queue_equal(pque, NULL));

    queue_destroy(pque);
}

void test_queue_equal__non_inited_first(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_second);
    pque_first->_t_sequence._t_typeinfo._t_style = 9999;
    expect_assert_failure(queue_equal(pque_first, pque_second));

    pque_first->_t_sequence._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_equal__non_inited_second(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_first);
    pque_second->_t_sequence._t_typeinfo._t_style = 23434;
    expect_assert_failure(queue_equal(pque_first, pque_second));

    pque_second->_t_sequence._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_equal__not_same_type(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(double);

    queue_init(pque_first);
    queue_init(pque_second);
    expect_assert_failure(queue_equal(pque_first, pque_second));

    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_equal__same_queue(void** state)
{
    queue_t* pque = create_queue(int);
    queue_init(pque);

    assert_true(queue_equal(pque, pque));

    queue_destroy(pque);
}

void test_queue_equal__size_first_less_than_second(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_first);
    queue_init(pque_second);
    queue_push(pque_second, 0);
    assert_false(queue_equal(pque_first, pque_second));

    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_equal__size_first_greater_than_second(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_first);
    queue_push(pque_first, 0);
    queue_push(pque_first, 0);
    queue_push(pque_first, 0);
    queue_push(pque_first, 0);
    queue_init(pque_second);
    queue_push(pque_second, 0);
    assert_false(queue_equal(pque_first, pque_second));

    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_equal__size_equal_0(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_first);
    queue_init(pque_second);
    assert_true(queue_equal(pque_first, pque_second));

    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_equal__size_equal_elem_first_less_than_second(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_first);
    queue_push(pque_first, 100);
    queue_init(pque_second);
    queue_push(pque_second, 4545);
    assert_false(queue_equal(pque_first, pque_second));

    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_equal__size_equal_elem_first_greater_than_second(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_first);
    queue_push(pque_first, 100);
    queue_init(pque_second);
    queue_push(pque_second, 45);
    assert_false(queue_equal(pque_first, pque_second));

    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_equal__size_equal_elem_equal(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_first);
    queue_push(pque_first, 100);
    queue_init(pque_second);
    queue_push(pque_second, 100);
    assert_true(queue_equal(pque_first, pque_second));

    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

/*
 * test queue_not_equal
 */
UT_CASE_DEFINATION(queue_not_equal)
void test_queue_not_equal__null_first(void** state)
{
    queue_t* pque = create_queue(int);
    queue_init(pque);

    expect_assert_failure(queue_not_equal(NULL, pque));

    queue_destroy(pque);
}

void test_queue_not_equal__null_second(void** state)
{
    queue_t* pque = create_queue(int);
    queue_init(pque);

    expect_assert_failure(queue_not_equal(pque, NULL));

    queue_destroy(pque);
}

void test_queue_not_equal__non_inited_first(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_second);
    pque_first->_t_sequence._t_typeinfo._t_style = 432432;
    expect_assert_failure(queue_not_equal(pque_first, pque_second));

    pque_first->_t_sequence._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_not_equal__non_inited_second(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_first);
    pque_second->_t_sequence._t_typeinfo._t_style = 2222;
    expect_assert_failure(queue_not_equal(pque_first, pque_second));

    pque_second->_t_sequence._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_not_equal__not_same_type(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(double);

    queue_init(pque_first);
    queue_init(pque_second);
    expect_assert_failure(queue_not_equal(pque_first, pque_second));

    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_not_equal__same_queue(void** state)
{
    queue_t* pque = create_queue(int);
    queue_init(pque);

    assert_false(queue_not_equal(pque, pque));

    queue_destroy(pque);
}

void test_queue_not_equal__size_first_less_than_second(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_first);
    queue_init(pque_second);
    queue_push(pque_second, 0);
    assert_true(queue_not_equal(pque_first, pque_second));

    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_not_equal__size_first_greater_than_second(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_first);
    queue_push(pque_first, 0);
    queue_push(pque_first, 0);
    queue_push(pque_first, 0);
    queue_push(pque_first, 0);
    queue_push(pque_first, 0);
    queue_init(pque_second);
    queue_push(pque_second, 0);
    queue_push(pque_second, 0);
    assert_true(queue_not_equal(pque_first, pque_second));

    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_not_equal__size_equal_0(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_first);
    queue_init(pque_second);
    assert_false(queue_not_equal(pque_first, pque_second));

    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_not_equal__size_equal_elem_first_less_than_second(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_first);
    queue_push(pque_first, 100);
    queue_push(pque_first, 100);
    queue_push(pque_first, 100);
    queue_init(pque_second);
    queue_push(pque_second, 4545);
    queue_push(pque_second, 4545);
    queue_push(pque_second, 4545);
    assert_true(queue_not_equal(pque_first, pque_second));

    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_not_equal__size_equal_elem_first_greater_than_second(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_first);
    queue_push(pque_first, 100);
    queue_push(pque_first, 100);
    queue_push(pque_first, 100);
    queue_init(pque_second);
    queue_push(pque_second, 45);
    queue_push(pque_second, 45);
    queue_push(pque_second, 45);
    assert_true(queue_not_equal(pque_first, pque_second));

    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_not_equal__size_equal_elem_equal(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_first);
    queue_push(pque_first, 100);
    queue_push(pque_first, 100);
    queue_push(pque_first, 100);
    queue_init(pque_second);
    queue_push(pque_second, 100);
    queue_push(pque_second, 100);
    queue_push(pque_second, 100);
    assert_false(queue_not_equal(pque_first, pque_second));

    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

/*
 * test queue_less
 */
UT_CASE_DEFINATION(queue_less)
void test_queue_less__null_first(void** state)
{
    queue_t* pque = create_queue(int);
    queue_init(pque);

    expect_assert_failure(queue_less(NULL, pque));

    queue_destroy(pque);
}

void test_queue_less__null_second(void** state)
{
    queue_t* pque = create_queue(int);
    queue_init(pque);

    expect_assert_failure(queue_less(pque, NULL));

    queue_destroy(pque);
}

void test_queue_less__non_inited_first(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_second);
    pque_first->_t_sequence._t_typeinfo._t_style = 4834;
    expect_assert_failure(queue_less(pque_first, pque_second));

    pque_first->_t_sequence._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_less__non_inited_second(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_first);
    pque_second->_t_sequence._t_typeinfo._t_style = 22222;
    expect_assert_failure(queue_less(pque_first, pque_second));

    pque_second->_t_sequence._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_less__not_same_type(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(double);

    queue_init(pque_first);
    queue_init(pque_second);
    expect_assert_failure(queue_less(pque_first, pque_second));

    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_less__same_queue(void** state)
{
    queue_t* pque = create_queue(int);
    queue_init(pque);

    assert_false(queue_less(pque, pque));

    queue_destroy(pque);
}

void test_queue_less__size_first_less_than_second(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_first);
    queue_init(pque_second);
    queue_push(pque_second, 0);
    assert_true(queue_less(pque_first, pque_second));

    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_less__size_first_greater_than_second(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_first);
    queue_push(pque_first, 0);
    queue_push(pque_first, 0);
    queue_push(pque_first, 0);
    queue_push(pque_first, 0);
    queue_init(pque_second);
    queue_push(pque_second, 0);
    queue_push(pque_second, 0);
    assert_false(queue_less(pque_first, pque_second));

    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_less__size_equal_0(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_first);
    queue_init(pque_second);
    assert_false(queue_less(pque_first, pque_second));

    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_less__size_equal_elem_first_less_than_second(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_first);
    queue_push(pque_first, 100);
    queue_push(pque_first, 100);
    queue_push(pque_first, 100);
    queue_init(pque_second);
    queue_push(pque_second, 4545);
    queue_push(pque_second, 4545);
    queue_push(pque_second, 4545);
    assert_true(queue_less(pque_first, pque_second));

    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_less__size_equal_elem_first_greater_than_second(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_first);
    queue_push(pque_first, 100);
    queue_push(pque_first, 100);
    queue_push(pque_first, 100);
    queue_init(pque_second);
    queue_push(pque_second, 45);
    queue_push(pque_second, 45);
    queue_push(pque_second, 45);
    assert_false(queue_less(pque_first, pque_second));

    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_less__size_equal_elem_equal(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_first);
    queue_push(pque_first, 100);
    queue_push(pque_first, 100);
    queue_push(pque_first, 100);
    queue_init(pque_second);
    queue_push(pque_second, 100);
    queue_push(pque_second, 100);
    queue_push(pque_second, 100);
    assert_false(queue_less(pque_first, pque_second));

    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

/*
 * test queue_less_equal
 */
UT_CASE_DEFINATION(queue_less_equal)
void test_queue_less_equal__null_first(void** state)
{
    queue_t* pque = create_queue(int);
    queue_init(pque);

    expect_assert_failure(queue_less_equal(NULL, pque));

    queue_destroy(pque);
}

void test_queue_less_equal__null_second(void** state)
{
    queue_t* pque = create_queue(int);
    queue_init(pque);

    expect_assert_failure(queue_less_equal(pque, NULL));

    queue_destroy(pque);
}

void test_queue_less_equal__non_inited_first(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_second);
    pque_first->_t_sequence._t_typeinfo._t_style = 2233;
    expect_assert_failure(queue_less_equal(pque_first, pque_second));

    pque_first->_t_sequence._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_less_equal__non_inited_second(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_first);
    pque_second->_t_sequence._t_typeinfo._t_style = 2222;
    expect_assert_failure(queue_less_equal(pque_first, pque_second));

    pque_second->_t_sequence._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_less_equal__not_same_type(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(double);

    queue_init(pque_first);
    queue_init(pque_second);
    expect_assert_failure(queue_less_equal(pque_first, pque_second));

    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_less_equal__same_queue(void** state)
{
    queue_t* pque = create_queue(int);
    queue_init(pque);

    assert_true(queue_less_equal(pque, pque));

    queue_destroy(pque);
}

void test_queue_less_equal__size_first_less_than_second(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_first);
    queue_init(pque_second);
    queue_push(pque_second, 0);
    assert_true(queue_less_equal(pque_first, pque_second));

    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_less_equal__size_first_greater_than_second(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_first);
    queue_push(pque_first, 0);
    queue_push(pque_first, 0);
    queue_push(pque_first, 0);
    queue_init(pque_second);
    queue_push(pque_second, 0);
    assert_false(queue_less_equal(pque_first, pque_second));

    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_less_equal__size_equal_0(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_first);
    queue_init(pque_second);
    assert_true(queue_less_equal(pque_first, pque_second));

    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_less_equal__size_equal_elem_first_less_than_second(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_first);
    queue_push(pque_first, 100);
    queue_push(pque_first, 100);
    queue_push(pque_first, 100);
    queue_init(pque_second);
    queue_push(pque_second, 4545);
    queue_push(pque_second, 4545);
    queue_push(pque_second, 4545);
    assert_true(queue_less_equal(pque_first, pque_second));

    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_less_equal__size_equal_elem_first_greater_than_second(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_first);
    queue_push(pque_first, 100);
    queue_push(pque_first, 100);
    queue_push(pque_first, 100);
    queue_init(pque_second);
    queue_push(pque_second, 45);
    queue_push(pque_second, 45);
    queue_push(pque_second, 45);
    assert_false(queue_less_equal(pque_first, pque_second));

    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_less_equal__size_equal_elem_equal(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_first);
    queue_push(pque_first, 100);
    queue_push(pque_first, 100);
    queue_push(pque_first, 100);
    queue_init(pque_second);
    queue_push(pque_second, 100);
    queue_push(pque_second, 100);
    queue_push(pque_second, 100);
    assert_true(queue_less_equal(pque_first, pque_second));

    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

/*
 * test queue_greater
 */
UT_CASE_DEFINATION(queue_greater)
void test_queue_greater__null_first(void** state)
{
    queue_t* pque = create_queue(int);
    queue_init(pque);

    expect_assert_failure(queue_greater(NULL, pque));

    queue_destroy(pque);
}

void test_queue_greater__null_second(void** state)
{
    queue_t* pque = create_queue(int);
    queue_init(pque);

    expect_assert_failure(queue_greater(pque, NULL));

    queue_destroy(pque);
}

void test_queue_greater__non_inited_first(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_second);
    pque_first->_t_sequence._t_typeinfo._t_style = 3455;
    expect_assert_failure(queue_greater(pque_first, pque_second));

    pque_first->_t_sequence._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_greater__non_inited_second(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_first);
    pque_second->_t_sequence._t_typeinfo._t_style = 22222;
    expect_assert_failure(queue_greater(pque_first, pque_second));

    pque_second->_t_sequence._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_greater__not_same_type(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(double);

    queue_init(pque_first);
    queue_init(pque_second);
    expect_assert_failure(queue_greater(pque_first, pque_second));

    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_greater__same_queue(void** state)
{
    queue_t* pque = create_queue(int);
    queue_init(pque);

    assert_false(queue_greater(pque, pque));

    queue_destroy(pque);
}

void test_queue_greater__size_first_less_than_second(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_first);
    queue_init(pque_second);
    queue_push(pque_second, 0);
    assert_false(queue_greater(pque_first, pque_second));

    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_greater__size_first_greater_than_second(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_first);
    queue_push(pque_first, 0);
    queue_push(pque_first, 0);
    queue_push(pque_first, 0);
    queue_push(pque_first, 0);
    queue_init(pque_second);
    queue_push(pque_second, 0);
    queue_push(pque_second, 0);
    assert_true(queue_greater(pque_first, pque_second));

    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_greater__size_equal_0(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_first);
    queue_init(pque_second);
    assert_false(queue_greater(pque_first, pque_second));

    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_greater__size_equal_elem_first_less_than_second(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_first);
    queue_push(pque_first, 100);
    queue_push(pque_first, 100);
    queue_push(pque_first, 100);
    queue_init(pque_second);
    queue_push(pque_second, 4545);
    queue_push(pque_second, 4545);
    queue_push(pque_second, 4545);
    assert_false(queue_greater(pque_first, pque_second));

    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_greater__size_equal_elem_first_greater_than_second(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_first);
    queue_push(pque_first, 100);
    queue_push(pque_first, 100);
    queue_push(pque_first, 100);
    queue_init(pque_second);
    queue_push(pque_second, 45);
    queue_push(pque_second, 45);
    queue_push(pque_second, 45);
    assert_true(queue_greater(pque_first, pque_second));

    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_greater__size_equal_elem_equal(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_first);
    queue_push(pque_first, 100);
    queue_push(pque_first, 100);
    queue_push(pque_first, 100);
    queue_init(pque_second);
    queue_push(pque_second, 100);
    queue_push(pque_second, 100);
    queue_push(pque_second, 100);
    assert_false(queue_greater(pque_first, pque_second));

    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

/*
 * test queue_greater_equal
 */
UT_CASE_DEFINATION(queue_greater_equal)
void test_queue_greater_equal__null_first(void** state)
{
    queue_t* pque = create_queue(int);
    queue_init(pque);

    expect_assert_failure(queue_greater_equal(NULL, pque));

    queue_destroy(pque);
}

void test_queue_greater_equal__null_second(void** state)
{
    queue_t* pque = create_queue(int);
    queue_init(pque);

    expect_assert_failure(queue_greater_equal(pque, NULL));

    queue_destroy(pque);
}

void test_queue_greater_equal__non_inited_first(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_second);
    pque_first->_t_sequence._t_typeinfo._t_style = 24345;
    expect_assert_failure(queue_greater_equal(pque_first, pque_second));

    pque_first->_t_sequence._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_greater_equal__non_inited_second(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_first);
    pque_second->_t_sequence._t_typeinfo._t_style = 4444;
    expect_assert_failure(queue_greater_equal(pque_first, pque_second));

    pque_second->_t_sequence._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_greater_equal__not_same_type(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(double);

    queue_init(pque_first);
    queue_init(pque_second);
    expect_assert_failure(queue_greater_equal(pque_first, pque_second));

    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_greater_equal__same_queue(void** state)
{
    queue_t* pque = create_queue(int);
    queue_init(pque);

    assert_true(queue_greater_equal(pque, pque));

    queue_destroy(pque);
}

void test_queue_greater_equal__size_first_less_than_second(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_first);
    queue_init(pque_second);
    queue_push(pque_second, 0);
    assert_false(queue_greater_equal(pque_first, pque_second));

    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_greater_equal__size_first_greater_than_second(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_first);
    queue_push(pque_first, 0);
    queue_push(pque_first, 0);
    queue_push(pque_first, 0);
    queue_push(pque_first, 0);
    queue_init(pque_second);
    queue_push(pque_second, 0);
    queue_push(pque_second, 0);
    assert_true(queue_greater_equal(pque_first, pque_second));

    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_greater_equal__size_equal_0(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_first);
    queue_init(pque_second);
    assert_true(queue_greater_equal(pque_first, pque_second));

    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_greater_equal__size_equal_elem_first_less_than_second(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_first);
    queue_push(pque_first, 100);
    queue_push(pque_first, 100);
    queue_push(pque_first, 100);
    queue_init(pque_second);
    queue_push(pque_second, 4545);
    queue_push(pque_second, 4545);
    queue_push(pque_second, 4545);
    assert_false(queue_greater_equal(pque_first, pque_second));

    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_greater_equal__size_equal_elem_first_greater_than_second(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_first);
    queue_push(pque_first, 100);
    queue_push(pque_first, 100);
    queue_push(pque_first, 100);
    queue_init(pque_second);
    queue_push(pque_second, 45);
    queue_push(pque_second, 45);
    queue_push(pque_second, 45);
    assert_true(queue_greater_equal(pque_first, pque_second));

    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test_queue_greater_equal__size_equal_elem_equal(void** state)
{
    queue_t* pque_first = create_queue(int);
    queue_t* pque_second = create_queue(int);

    queue_init(pque_first);
    queue_push(pque_first, 100);
    queue_push(pque_first, 100);
    queue_push(pque_first, 100);
    queue_init(pque_second);
    queue_push(pque_second, 100);
    queue_push(pque_second, 100);
    queue_push(pque_second, 100);
    assert_true(queue_greater_equal(pque_first, pque_second));

    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

/*
 * test queue_assign
 */
UT_CASE_DEFINATION(queue_assign)
void test_queue_assign__null_dest(void** state)
{
    queue_t* pque = create_queue(int);
    queue_init(pque);

    expect_assert_failure(queue_assign(NULL, pque));

    queue_destroy(pque);
}

void test_queue_assign__null_src(void** state)
{
    queue_t* pque = create_queue(int);
    queue_init(pque);

    expect_assert_failure(queue_assign(pque, NULL));

    queue_destroy(pque);
}

void test_queue_assign__non_inited_dest(void** state)
{
    queue_t* pque_dest = create_queue(int);
    queue_t* pque_src = create_queue(int);

    queue_init(pque_src);

    pque_dest->_t_sequence._t_typeinfo._t_style = 232;
    expect_assert_failure(queue_assign(pque_dest, pque_src));

    pque_dest->_t_sequence._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    queue_destroy(pque_dest);
    queue_destroy(pque_src);
}

void test_queue_assign__non_inited_src(void** state)
{
    queue_t* pque_dest = create_queue(int);
    queue_t* pque_src = create_queue(int);

    queue_init(pque_dest);

    pque_src->_t_sequence._t_typeinfo._t_style = 32333;
    expect_assert_failure(queue_assign(pque_dest, pque_src));

    pque_src->_t_sequence._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    queue_destroy(pque_dest);
    queue_destroy(pque_src);
}

void test_queue_assign__not_same_type(void** state)
{
    queue_t* pque_dest = create_queue(int);
    queue_t* pque_src = create_queue(double);

    queue_init(pque_dest);
    queue_init(pque_src);

    expect_assert_failure(queue_assign(pque_dest, pque_src));

    queue_destroy(pque_dest);
    queue_destroy(pque_src);
}

void test_queue_assign__same_adaptor(void** state)
{
    queue_t* pque = create_queue(int);

    queue_init(pque);

    queue_assign(pque, pque);
    assert_true(queue_size(pque) == 0);

    queue_destroy(pque);
}

void test_queue_assign__0_assign_0(void** state)
{
    queue_t* pque_dest = create_queue(int);
    queue_t* pque_src = create_queue(int);

    queue_init(pque_dest);
    queue_init(pque_src);

    queue_assign(pque_dest, pque_src);
    assert_true(queue_size(pque_dest) == 0);
    assert_true(queue_equal(pque_dest, pque_src));

    queue_destroy(pque_dest);
    queue_destroy(pque_src);
}

void test_queue_assign__0_assign_n(void** state)
{
    queue_t* pque_dest = create_queue(int);
    queue_t* pque_src = create_queue(int);

    queue_init(pque_dest);
    queue_init(pque_src);
    queue_push(pque_src, 0);
    queue_push(pque_src, 0);
    queue_push(pque_src, 0);

    queue_assign(pque_dest, pque_src);
    assert_true(queue_size(pque_dest) == 3);
    assert_true(queue_equal(pque_dest, pque_src));

    queue_destroy(pque_dest);
    queue_destroy(pque_src);
}

void test_queue_assign__n_assign_0(void** state)
{
    queue_t* pque_dest = create_queue(int);
    queue_t* pque_src = create_queue(int);

    queue_init(pque_dest);
    queue_push(pque_dest, 23);
    queue_push(pque_dest, 23);
    queue_push(pque_dest, 23);
    queue_push(pque_dest, 23);
    queue_init(pque_src);

    queue_assign(pque_dest, pque_src);
    assert_true(queue_equal(pque_dest, pque_src));
    assert_true(queue_size(pque_dest) == 0);

    queue_destroy(pque_dest);
    queue_destroy(pque_src);
}

void test_queue_assign__n_assign_n_queue_equal(void** state)
{
    queue_t* pque_dest = create_queue(int);
    queue_t* pque_src = create_queue(int);

    queue_init(pque_dest);
    queue_push(pque_dest, 5);
    queue_push(pque_dest, 5);
    queue_push(pque_dest, 5);
    queue_push(pque_dest, 5);
    queue_init(pque_src);
    queue_push(pque_src, 5);
    queue_push(pque_src, 5);
    queue_push(pque_src, 5);
    queue_push(pque_src, 5);

    queue_assign(pque_dest, pque_src);
    assert_true(queue_equal(pque_dest, pque_src));

    queue_destroy(pque_dest);
    queue_destroy(pque_src);
}

void test_queue_assign__n_assign_n_queue_not_equal(void** state)
{
    queue_t* pque_dest = create_queue(int);
    queue_t* pque_src = create_queue(int);

    queue_init(pque_dest);
    queue_push(pque_dest, 5);
    queue_push(pque_dest, 5);
    queue_push(pque_dest, 5);
    queue_push(pque_dest, 5);
    queue_init(pque_src);
    queue_push(pque_src, 9);
    queue_push(pque_src, 9);
    queue_push(pque_src, 9);
    queue_push(pque_src, 9);

    queue_assign(pque_dest, pque_src);
    assert_true(queue_equal(pque_dest, pque_src));
    assert_true(queue_size(pque_dest) == 4);

    queue_destroy(pque_dest);
    queue_destroy(pque_src);
}

void test_queue_assign__n_assign_m(void** state)
{
    queue_t* pque_dest = create_queue(int);
    queue_t* pque_src = create_queue(int);

    queue_init(pque_dest);
    queue_push(pque_dest, 5);
    queue_push(pque_dest, 5);
    queue_push(pque_dest, 5);
    queue_push(pque_dest, 5);
    queue_init(pque_src);
    queue_push(pque_src, 9);
    queue_push(pque_src, 9);
    queue_push(pque_src, 9);
    queue_push(pque_src, 9);
    queue_push(pque_src, 9);
    queue_push(pque_src, 9);
    queue_push(pque_src, 9);
    queue_push(pque_src, 9);

    queue_assign(pque_dest, pque_src);
    assert_true(queue_equal(pque_dest, pque_src));
    assert_true(queue_size(pque_dest) == 8);

    queue_destroy(pque_dest);
    queue_destroy(pque_src);
}

/*
 * test queue_pop
 */
UT_CASE_DEFINATION(queue_pop)
void test_queue_pop__null_queue_adaptor(void** state)
{
    expect_assert_failure(queue_pop(NULL));
}

void test_queue_pop__non_inited_queue_adaptor(void** state)
{
    queue_t* pque = create_queue(int);

    pque->_t_sequence._t_typeinfo._t_style = 4444;
    expect_assert_failure(queue_pop(pque));

    pque->_t_sequence._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    queue_destroy(pque);
}

void test_queue_pop__empty(void** state)
{
    queue_t* pque = create_queue(int);

    queue_init(pque);
    expect_assert_failure(queue_pop(pque));

    queue_destroy(pque);
}

void test_queue_pop__successfully(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    queue_t* pque = create_queue(int);
    queue_init(pque);

    for(i = 0; i < 10; ++i)
    {
        queue_push(pque, i);
    }
    t_oldsize = queue_size(pque);
    assert_true(*(int*)queue_front(pque) == 0);
    queue_pop(pque);
    assert_true(queue_size(pque) == t_oldsize - 1);
    assert_true(*(int*)queue_front(pque) == 1);

    queue_destroy(pque);
}

/*
 * test queue_front
 */
UT_CASE_DEFINATION(queue_front)
void test_queue_front__null_queue_adaptor(void** state)
{
    expect_assert_failure(queue_front(NULL));
}

void test_queue_front__non_inited_queue_adaptor(void** state)
{
    queue_t* pque = create_queue(int);

    pque->_t_sequence._t_typeinfo._t_style = 4444;
    expect_assert_failure(queue_front(pque));

    pque->_t_sequence._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    queue_destroy(pque);
}

void test_queue_front__empty(void** state)
{
    queue_t* pque = create_queue(int);

    queue_init(pque);
    expect_assert_failure(queue_front(pque));

    queue_destroy(pque);
}

void test_queue_front__successfully(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    queue_t* pque = create_queue(int);
    queue_init(pque);

    for(i = 0; i < 10; ++i)
    {
        queue_push(pque, i);
    }
    t_oldsize = queue_size(pque);
    assert_true(*(int*)queue_front(pque) == 0);
    queue_pop(pque);
    assert_true(queue_size(pque) == t_oldsize - 1);
    assert_true(*(int*)queue_front(pque) == 1);

    queue_destroy(pque);
}

/*
 * test queue_back
 */
UT_CASE_DEFINATION(queue_back)
void test_queue_back__null_queue_adaptor(void** state)
{
    expect_assert_failure(queue_back(NULL));
}

void test_queue_back__non_inited_queue_adaptor(void** state)
{
    queue_t* pque = create_queue(int);

    pque->_t_sequence._t_typeinfo._t_style = 4444;
    expect_assert_failure(queue_back(pque));

    pque->_t_sequence._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    queue_destroy(pque);
}

void test_queue_back__empty(void** state)
{
    queue_t* pque = create_queue(int);

    queue_init(pque);
    expect_assert_failure(queue_back(pque));

    queue_destroy(pque);
}

void test_queue_back__successfully(void** state)
{
    size_t i = 0;
    queue_t* pque = create_queue(int);
    queue_init(pque);

    for(i = 0; i < 10; ++i)
    {
        queue_push(pque, i);
        assert_true(*(int*)queue_back(pque) == i);
    }

    queue_destroy(pque);
}

