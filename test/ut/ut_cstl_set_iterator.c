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
#include "cstl_set_aux.h"

#include "ut_def.h"
#include "ut_cstl_set_iterator.h"

UT_SUIT_DEFINATION(cstl_set_iterator, create_set_iterator)
/*
 * test _create_set_iterator
 */
UT_CASE_DEFINATION(create_set_iterator)
void test_create_set_iterator__successfully(void** state)
{
    set_iterator_t it_iter = create_set_iterator();
    assert_true(it_iter._t_pos._t_treepos._pc_corepos == NULL);
    assert_true(it_iter._t_pos._t_treepos._pt_tree == NULL);
    assert_true(it_iter._pt_container == NULL);
    assert_true(it_iter._t_containertype == _SET_CONTAINER);
    assert_true(it_iter._t_iteratortype == _BIDIRECTIONAL_ITERATOR);
}

