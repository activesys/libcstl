/*
 * libcst unit test main function.
 */
#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "ut_def.h"
#include "ut_cstl_alloc_aux.h"
#include "ut_cstl_alloc.h"
#include "ut_cstl_vector_iterator.h"
#include "ut_cstl_vector_aux.h"
#include "ut_cstl_vector_private.h"
#include "ut_cstl_vector.h"
#include "ut_cstl_list_iterator.h"

int main(int argc, char* argv[])
{
    const UnitTest tests[] = {
        UT_CSTL_ALLOC_AUX_CASE,
        UT_CSTL_ALLOC_CASE,
        UT_CSTL_VECTOR_ITERATOR_CASE,
        UT_CSTL_VECTOR_AUX_CASE,
        UT_CSTL_VECTOR_PRIVATE_CASE,
        UT_CSTL_VECTOR_CASE,
        UT_CSTL_LIST_ITERATOR_CASE
    };

    return run_tests(tests);
}

