#ifndef _UT_CSTL_AVL_TREE_ITERATOR_H_
#define _UT_CSTL_AVL_TREE_ITERATOR_H_

UT_SUIT_DECLARATION(cstl_avl_tree_iterator)
/*
 * test _create_avl_tree_iterator
 */
UT_CASE_DECLARATION(_create_avl_tree_iterator)
void test__create_avl_tree_iterator__successfully(void** state);
/*
 * test _avl_tree_iterator_get_value
 */
UT_CASE_DECLARATION(_avl_tree_iterator_get_value)
void test__avl_tree_iterator_get_value__null_corepos(void** state);
void test__avl_tree_iterator_get_value__null_tree(void** state);
void test__avl_tree_iterator_get_value__end(void** state);
void test__avl_tree_iterator_get_value__null_value(void** state);
void test__avl_tree_iterator_get_value__c_builtin(void** state);
void test__avl_tree_iterator_get_value__cstr(void** state);
void test__avl_tree_iterator_get_value__libcstl_builtin(void** state);
void test__avl_tree_iterator_get_value__user_define(void** state);
/*
 * test _avl_tree_iterator_get_pointer
 */
UT_CASE_DECLARATION(_avl_tree_iterator_get_pointer)
void test__avl_tree_iterator_get_pointer__null_corepos(void** state);
void test__avl_tree_iterator_get_pointer__null_tree(void** state);
void test__avl_tree_iterator_get_pointer__end(void** state);
void test__avl_tree_iterator_get_pointer__c_builtin(void** state);
void test__avl_tree_iterator_get_pointer__cstr(void** state);
void test__avl_tree_iterator_get_pointer__libcstl_builtin(void** state);
void test__avl_tree_iterator_get_pointer__user_define(void** state);
/*
 * test _avl_tree_iterator_get_pointer_ignore_cstr
 */
UT_CASE_DECLARATION(_avl_tree_iterator_get_pointer_ignore_cstr)
void test__avl_tree_iterator_get_pointer_ignore_cstr__null_corepos(void** state);
void test__avl_tree_iterator_get_pointer_ignore_cstr__null_tree(void** state);
void test__avl_tree_iterator_get_pointer_ignore_cstr__end(void** state);
void test__avl_tree_iterator_get_pointer_ignore_cstr__c_builtin(void** state);
void test__avl_tree_iterator_get_pointer_ignore_cstr__cstr(void** state);
void test__avl_tree_iterator_get_pointer_ignore_cstr__libcstl_builtin(void** state);
void test__avl_tree_iterator_get_pointer_ignore_cstr__user_define(void** state);
/*
 * test _avl_tree_iterator_next
 */
UT_CASE_DECLARATION(_avl_tree_iterator_next)
void test__avl_tree_iterator_next__null_corepos(void** state);
void test__avl_tree_iterator_next__null_tree(void** state);
void test__avl_tree_iterator_next__end(void** state);
void test__avl_tree_iterator_next__last(void** state);
void test__avl_tree_iterator_next__begin(void** state);
/*
 * test _avl_tree_iterator_prev
 */
UT_CASE_DECLARATION(_avl_tree_iterator_prev)
void test__avl_tree_iterator_prev__null_corepos(void** state);
void test__avl_tree_iterator_prev__null_tree(void** state);
void test__avl_tree_iterator_prev__begin(void** state);
void test__avl_tree_iterator_prev__end(void** state);
void test__avl_tree_iterator_prev__last(void** state);
/*
 * test _avl_tree_iterator_equal
 */
UT_CASE_DECLARATION(_avl_tree_iterator_equal)
void test__avl_tree_iterator_equal__invalid_first(void** state);
void test__avl_tree_iterator_equal__invalid_second(void** state);
void test__avl_tree_iterator_equal__not_same_avl_tree(void** state);
void test__avl_tree_iterator_equal__equal(void** state);
void test__avl_tree_iterator_equal__not_equal(void** state);
/*
 * test _avl_tree_iterator_distance
 */
UT_CASE_DECLARATION(_avl_tree_iterator_distance)
void test__avl_tree_iterator_distance__invalid_first(void** state);
void test__avl_tree_iterator_distance__invalid_second(void** state);
void test__avl_tree_iterator_distance__not_same_avl_tree(void** state);
void test__avl_tree_iterator_distance__0(void** state);
void test__avl_tree_iterator_distance__greater_0(void** state);
void test__avl_tree_iterator_distance__less_0(void** state);
/*
 * test _avl_tree_iterator_before
 */
UT_CASE_DECLARATION(_avl_tree_iterator_before)
void test__avl_tree_iterator_before__invalid_first(void** state);
void test__avl_tree_iterator_before__invalid_second(void** state);
void test__avl_tree_iterator_before__not_same_avl_tree(void** state);
void test__avl_tree_iterator_before__equal(void** state);
void test__avl_tree_iterator_before__true(void** state);
void test__avl_tree_iterator_before__false(void** state);


#define UT_CSTL_AVL_TREE_ITERATOR_CASE\
    UT_SUIT_BEGIN(cstl_avl_tree_iterator, test__create_avl_tree_iterator__successfully),\
    UT_CASE_BEGIN(_avl_tree_iterator_get_value, test__avl_tree_iterator_get_value__null_corepos),\
    UT_CASE(test__avl_tree_iterator_get_value__null_tree),\
    UT_CASE(test__avl_tree_iterator_get_value__end),\
    UT_CASE(test__avl_tree_iterator_get_value__null_value),\
    UT_CASE(test__avl_tree_iterator_get_value__c_builtin),\
    UT_CASE(test__avl_tree_iterator_get_value__cstr),\
    UT_CASE(test__avl_tree_iterator_get_value__libcstl_builtin),\
    UT_CASE(test__avl_tree_iterator_get_value__user_define),\
    UT_CASE_BEGIN(_avl_tree_iterator_get_pointer, test__avl_tree_iterator_get_pointer__null_corepos),\
    UT_CASE(test__avl_tree_iterator_get_pointer__null_tree),\
    UT_CASE(test__avl_tree_iterator_get_pointer__end),\
    UT_CASE(test__avl_tree_iterator_get_pointer__c_builtin),\
    UT_CASE(test__avl_tree_iterator_get_pointer__cstr),\
    UT_CASE(test__avl_tree_iterator_get_pointer__libcstl_builtin),\
    UT_CASE(test__avl_tree_iterator_get_pointer__user_define),\
    UT_CASE_BEGIN(_avl_tree_iterator_get_pointer_ignore_cstr, test__avl_tree_iterator_get_pointer_ignore_cstr__null_corepos),\
    UT_CASE(test__avl_tree_iterator_get_pointer_ignore_cstr__null_tree),\
    UT_CASE(test__avl_tree_iterator_get_pointer_ignore_cstr__end),\
    UT_CASE(test__avl_tree_iterator_get_pointer_ignore_cstr__c_builtin),\
    UT_CASE(test__avl_tree_iterator_get_pointer_ignore_cstr__cstr),\
    UT_CASE(test__avl_tree_iterator_get_pointer_ignore_cstr__libcstl_builtin),\
    UT_CASE(test__avl_tree_iterator_get_pointer_ignore_cstr__user_define),\
    UT_CASE_BEGIN(_avl_tree_iterator_next, test__avl_tree_iterator_next__null_corepos),\
    UT_CASE(test__avl_tree_iterator_next__null_tree),\
    UT_CASE(test__avl_tree_iterator_next__end),\
    UT_CASE(test__avl_tree_iterator_next__last),\
    UT_CASE(test__avl_tree_iterator_next__begin),\
    UT_CASE_BEGIN(_avl_tree_iterator_prev, test__avl_tree_iterator_prev__null_corepos),\
    UT_CASE(test__avl_tree_iterator_prev__null_tree),\
    UT_CASE(test__avl_tree_iterator_prev__begin),\
    UT_CASE(test__avl_tree_iterator_prev__end),\
    UT_CASE(test__avl_tree_iterator_prev__last),\
    UT_CASE_BEGIN(_avl_tree_iterator_equal, test__avl_tree_iterator_equal__invalid_first),\
    UT_CASE(test__avl_tree_iterator_equal__invalid_second),\
    UT_CASE(test__avl_tree_iterator_equal__not_same_avl_tree),\
    UT_CASE(test__avl_tree_iterator_equal__equal),\
    UT_CASE(test__avl_tree_iterator_equal__not_equal),\
    UT_CASE_BEGIN(_avl_tree_iterator_distance, test__avl_tree_iterator_distance__invalid_first),\
    UT_CASE(test__avl_tree_iterator_distance__invalid_second),\
    UT_CASE(test__avl_tree_iterator_distance__not_same_avl_tree),\
    UT_CASE(test__avl_tree_iterator_distance__0),\
    UT_CASE(test__avl_tree_iterator_distance__greater_0),\
    UT_CASE(test__avl_tree_iterator_distance__less_0),\
    UT_CASE_BEGIN(_avl_tree_iterator_before, test__avl_tree_iterator_before__invalid_first),\
    UT_CASE(test__avl_tree_iterator_before__invalid_second),\
    UT_CASE(test__avl_tree_iterator_before__not_same_avl_tree),\
    UT_CASE(test__avl_tree_iterator_before__equal),\
    UT_CASE(test__avl_tree_iterator_before__true),\
    UT_CASE(test__avl_tree_iterator_before__false)

#endif /* _UT_CSTL_AVL_TREE_ITERATOR_H_ */

