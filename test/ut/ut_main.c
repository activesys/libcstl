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
#include "ut_cstl_list_aux.h"
#include "ut_cstl_list_private.h"
#include "ut_cstl_list.h"
#include "ut_cstl_deque_iterator.h"
#include "ut_cstl_deque_aux.h"
#include "ut_cstl_deque_private.h"
#include "ut_cstl_deque.h"
#include "ut_cstl_slist_iterator.h"
#include "ut_cstl_slist_aux.h"
#include "ut_cstl_slist_private.h"
#include "ut_cstl_slist.h"
#include "ut_cstl_stack_private.h"
#include "ut_cstl_stack.h"
#include "ut_cstl_queue_private.h"
#include "ut_cstl_queue.h"
#include "ut_cstl_basic_string_iterator.h"
#include "ut_cstl_basic_string_aux.h"
#include "ut_cstl_basic_string_private.h"
#include "ut_cstl_basic_string.h"
#include "ut_cstl_string_private.h"
#include "ut_cstl_string.h"
#include "ut_cstl_avl_tree_aux.h"
#include "ut_cstl_avl_tree_private.h"
#include "ut_cstl_avl_tree_iterator.h"
#include "ut_cstl_avl_tree.h"
#include "ut_cstl_rb_tree_aux.h"
#include "ut_cstl_rb_tree_private.h"
#include "ut_cstl_rb_tree_iterator.h"
#include "ut_cstl_rb_tree.h"
#include "ut_cstl_set_aux.h"

int main(int argc, char* argv[])
{
    const UnitTest tests[] = {
        UT_CSTL_ALLOC_AUX_CASE,
        UT_CSTL_ALLOC_CASE,
        UT_CSTL_VECTOR_ITERATOR_CASE,
        UT_CSTL_VECTOR_AUX_CASE,
        UT_CSTL_VECTOR_PRIVATE_CASE,
        UT_CSTL_VECTOR_CASE,
        UT_CSTL_LIST_ITERATOR_CASE,
        UT_CSTL_LIST_AUX_CASE,
        UT_CSTL_LIST_PRIVATE_CASE,
        UT_CSTL_LIST_CASE,
        UT_CSTL_DEQUE_ITERATOR_CASE,
        UT_CSTL_DEQUE_AUX_CASE,
        UT_CSTL_DEQUE_PRIVATE_CASE,
        UT_CSTL_DEQUE_CASE,
        UT_CSTL_SLIST_ITERATOR_CASE,
        UT_CSTL_SLIST_AUX_CASE,
        UT_CSTL_SLIST_PRIVATE_CASE,
        UT_CSTL_SLIST_CASE,
        UT_CSTL_STACK_PRIVATE_CASE,
        UT_CSTL_STACK_CASE,
        UT_CSTL_QUEUE_PRIVATE_CASE,
        UT_CSTL_QUEUE_CASE,
        UT_CSTL_BASIC_STRING_ITERATOR_CASE,
        UT_CSTL_BASIC_STRING_AUX_CASE,
        UT_CSTL_BASIC_STRING_PRIVATE_CASE,
        UT_CSTL_BASIC_STRING_CASE,
        UT_CSTL_STRING_PRIVATE_CASE,
        UT_CSTL_STRING_CASE,
        UT_CSTL_AVL_TREE_AUX_CASE,
        UT_CSTL_AVL_TREE_PRIVATE_CASE,
        UT_CSTL_AVL_TREE_ITERATOR_CASE,
        UT_CSTL_AVL_TREE_CASE,
        UT_CSTL_RB_TREE_AUX_CASE,
        UT_CSTL_RB_TREE_PRIVATE_CASE,
        UT_CSTL_RB_TREE_ITERATOR_CASE,
        UT_CSTL_RB_TREE_CASE,
        UT_CSTL_SET_AUX_CASE
    };

    return run_tests(tests);
}

