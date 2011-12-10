#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/citerator.h"
#include "cstl/cmap.h"
#include "cstl/cstring.h"
#include "cstl/cvector.h"
#include "cstl_pair_aux.h"

#include "ut_def.h"
#include "ut_cstl_pair_aux.h"

UT_SUIT_DEFINATION(cstl_pair_aux, _pair_same_type)

/*
 * test _pair_same_type
 */
UT_CASE_DEFINATION(_pair_same_type)
void test__pair_same_type__first_null(void** state)
{
    pair_t* ppair = create_pair(int, int);
    pair_init(ppair);

    expect_assert_failure(_pair_same_type(NULL, ppair));

    pair_destroy(ppair);
}

void test__pair_same_type__second_null(void** state)
{
    pair_t* ppair = create_pair(int, int);
    pair_init(ppair);

    expect_assert_failure(_pair_same_type(ppair, NULL));

    pair_destroy(ppair);
}

void test__pair_same_type__first_noninited(void** state)
{
    pair_t* ppair_first = create_pair(int, int);
    pair_t* ppair_second = create_pair(int, int);

    ppair_first->_t_typeinfofirst._t_style = 99999;
    expect_assert_failure(_pair_same_type(ppair_first, ppair_second));
    ppair_first->_t_typeinfofirst._t_style = _TYPE_C_BUILTIN;

    pair_destroy(ppair_first);
    pair_destroy(ppair_second);
}

void test__pair_same_type__second_noninited(void** state)
{
    pair_t* ppair_first = create_pair(int, int);
    pair_t* ppair_second = create_pair(int, int);

    ppair_second->_t_typeinfosecond._t_style = 9999;
    expect_assert_failure(_pair_same_type(ppair_first, ppair_second));
    ppair_second->_t_typeinfosecond._t_style = _TYPE_C_BUILTIN;

    pair_destroy(ppair_first);
    pair_destroy(ppair_second);
}

void test__pair_same_type__same_pair(void** state)
{
    pair_t* ppair = create_pair(int, int);
    pair_init(ppair);

    assert_true(_pair_same_type(ppair, ppair));

    pair_destroy(ppair);
}

void test__pair_same_type__not_same_first_type(void** state)
{
    pair_t* ppair_first = create_pair(int, int);
    pair_t* ppair_second = create_pair(double, int);
    pair_init(ppair_first);
    pair_init(ppair_second);

    assert_false(_pair_same_type(ppair_first, ppair_second));

    pair_destroy(ppair_first);
    pair_destroy(ppair_second);
}

void test__pair_same_type__not_same_second_type(void** state)
{
    pair_t* ppair_first = create_pair(int, int);
    pair_t* ppair_second = create_pair(int, double);
    pair_init(ppair_first);
    pair_init(ppair_second);

    assert_false(_pair_same_type(ppair_first, ppair_second));

    pair_destroy(ppair_first);
    pair_destroy(ppair_second);
}

void test__pair_same_type__same_type(void** state)
{
    pair_t* ppair_first = create_pair(int, int);
    pair_t* ppair_second = create_pair(int, int);
    pair_init(ppair_first);
    pair_init(ppair_second);

    assert_true(_pair_same_type(ppair_first, ppair_second));

    pair_destroy(ppair_first);
    pair_destroy(ppair_second);
}

