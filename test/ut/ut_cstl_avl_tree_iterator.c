#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/cstl_alloc.h"
#include "cstl/cstl_types.h"
#include "cstl/cstl_iterator.h"
#include "cstl/cstl_avl_tree_iterator.h"
#include "cstl/cstl_avl_tree_private.h"
#include "cstl/cstl_avl_tree.h"
#include "cstl_avl_tree_aux.h"
#include "cstl/cstring.h"

#include "ut_def.h"
#include "ut_cstl_avl_tree_iterator.h"

UT_SUIT_DEFINATION(cstl_avl_tree_iterator, _create_avl_tree_iterator)
/*
 * test _create_avl_tree_iterator
 */
UT_CASE_DEFINATION(_create_avl_tree_iterator)
void test__create_avl_tree_iterator__successfully(void** state)
{
    _avl_tree_iterator_t it_iter = _create_avl_tree_iterator();
    assert_true(it_iter._t_pos._t_treepos._pc_corepos == NULL);
    assert_true(it_iter._t_pos._t_treepos._pt_tree == NULL);
    assert_true(it_iter._pt_container == NULL);
}

/*
 * test _avl_tree_iterator_get_value
 */
UT_CASE_DEFINATION(_avl_tree_iterator_get_value)
void test__avl_tree_iterator_get_value__null_corepos(void** state)
{
}


