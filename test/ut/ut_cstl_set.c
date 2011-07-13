#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/cstl_iterator.h"
#include "cstl/cset.h"
#include "cstl/cstring.h"
#include "cstl/cvector.h"
#include "cstl/clist.h"
#include "cstl_vector_aux.h"
#include "cstl_rb_tree_aux.h"

#include "ut_def.h"
#include "ut_cstl_set.h"

UT_SUIT_DEFINATION(cstl_set, set_init)

/*
 * test set_init
 */
UT_CASE_DEFINATION(set_init)
void test_set_init__null_set(void** state)
{
    expect_assert_failure(set_init(NULL));
}

void test_set_init__non_created(void** state)
{
    set_t* pt_set = create_set(int);

    pt_set->_t_tree._t_rbroot._t_color = BLACK;
    expect_assert_failure(set_init(pt_set));
    pt_set->_t_tree._t_rbroot._t_color = RED;

    set_destroy(pt_set);
}

void test_set_init__null_compare(void** state)
{
    set_t* pt_set = create_set(int);

    set_init(pt_set);
    assert_true(_rb_tree_is_inited(&pt_set->_t_tree));

    set_destroy(pt_set);
}

/*
 * test set_init_ex
 */
UT_CASE_DEFINATION(set_init_ex)
void test_set_init_ex__null_set(void** state)
{
    expect_assert_failure(set_init_ex(NULL, NULL));
}

void test_set_init_ex__non_created(void** state)
{
    set_t* pt_set = create_set(int);

    pt_set->_t_tree._t_rbroot._t_color = BLACK;
    expect_assert_failure(set_init_ex(pt_set, NULL));
    pt_set->_t_tree._t_rbroot._t_color = RED;

    set_destroy(pt_set);
}

void test_set_init_ex__null_compare(void** state)
{
    set_t* pt_set = create_set(int);

    set_init_ex(pt_set, NULL);
    assert_true(_rb_tree_is_inited(&pt_set->_t_tree));

    set_destroy(pt_set);
}

static void _test_set_init_ex__non_null_compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_set_init_ex__non_null_compare(void** state)
{
    set_t* pt_set = create_set(int);

    set_init_ex(pt_set, _test_set_init_ex__non_null_compare);
    assert_true(_rb_tree_is_inited(&pt_set->_t_tree));
    assert_true(pt_set->_t_tree._t_compare == _test_set_init_ex__non_null_compare);

    set_destroy(pt_set);
}

