#ifndef _UT_CSTL_AVL_TREE_H_
#define _UT_CSTL_AVL_TREE_H_

UT_SUIT_DECLARATION(cstl_avl_tree)
/*
 * test _create_avl_tree
 */
UT_CASE_DECLARATION(_create_avl_tree)
void test__create_avl_tree__null_typename(void** state);
void test__create_avl_tree__c_builtin(void** state);
void test__create_avl_tree__cstr(void** state);
void test__create_avl_tree__libcstl_builtin(void** state);
void test__create_avl_tree__user_define(void** state);
void test__create_avl_tree__unregister(void** state);
/*
 * test _avl_tree_init
 */
UT_CASE_DECLARATION(_avl_tree_init)
void test__avl_tree_init__null_avl_tree(void** state);
void test__avl_tree_init__non_created(void** state);
void test__avl_tree_init__null_compare(void** state);
void test__avl_tree_init__non_null_compare(void** state);
/*
 * test _avl_tree_init_copy
 */
UT_CASE_DECLARATION(_avl_tree_init_copy)
void test__avl_tree_init_copy__null_dest(void** state);
void test__avl_tree_init_copy__null_src(void** state);
void test__avl_tree_init_copy__non_created_dest(void** state);
void test__avl_tree_init_copy__non_inited_src(void** state);
void test__avl_tree_init_copy__not_same_type(void** state);
void test__avl_tree_init_copy__empty(void** state);
void test__avl_tree_init_copy__non_empty(void** state);
void test__avl_tree_init_copy__non_null_compare(void** state);
/*
 * test _avl_tree_init_copy_range
 */
UT_CASE_DECLARATION(_avl_tree_init_copy_range)
void test__avl_tree_init_copy_range__null_avl_tree(void** state);
void test__avl_tree_init_copy_range__non_created_avl_tree(void** state);
void test__avl_tree_init_copy_range__invalid_begin(void** state);
void test__avl_tree_init_copy_range__invalid_end(void** state);
void test__avl_tree_init_copy_range__invalid_range(void** state);
void test__avl_tree_init_copy_range__invalid_range_not_same_type(void** state);
void test__avl_tree_init_copy_range__empty(void** state);
void test__avl_tree_init_copy_range__non_empty(void** state);
/*
 * test _avl_tree_init_copy_range_ex
 */
UT_CASE_DECLARATION(_avl_tree_init_copy_range_ex)
void test__avl_tree_init_copy_range_ex__null_avl_tree(void** state);
void test__avl_tree_init_copy_range_ex__non_created_avl_tree(void** state);
void test__avl_tree_init_copy_range_ex__invalid_begin(void** state);
void test__avl_tree_init_copy_range_ex__invalid_end(void** state);
void test__avl_tree_init_copy_range_ex__invalid_range(void** state);
void test__avl_tree_init_copy_range_ex__invalid_range_not_same_type(void** state);
void test__avl_tree_init_copy_range_ex__empty(void** state);
void test__avl_tree_init_copy_range_ex__non_empty(void** state);
void test__avl_tree_init_copy_range_ex__compare(void** state);

#define UT_CSTL_AVL_TREE_CASE\
    UT_SUIT_BEGIN(cstl_avl_tree, test__create_avl_tree__null_typename),\
    UT_CASE(test__create_avl_tree__c_builtin),\
    UT_CASE(test__create_avl_tree__cstr),\
    UT_CASE(test__create_avl_tree__libcstl_builtin),\
    UT_CASE(test__create_avl_tree__user_define),\
    UT_CASE(test__create_avl_tree__unregister),\
    UT_CASE_BEGIN(_avl_tree_init,  test__avl_tree_init__null_avl_tree),\
    UT_CASE(test__avl_tree_init__non_created),\
    UT_CASE(test__avl_tree_init__null_compare),\
    UT_CASE(test__avl_tree_init__non_null_compare),\
    UT_CASE_BEGIN(_avl_tree_init_copy, test__avl_tree_init_copy__null_dest),\
    UT_CASE(test__avl_tree_init_copy__null_src),\
    UT_CASE(test__avl_tree_init_copy__non_created_dest),\
    UT_CASE(test__avl_tree_init_copy__non_inited_src),\
    UT_CASE(test__avl_tree_init_copy__not_same_type),\
    UT_CASE(test__avl_tree_init_copy__empty),\
    UT_CASE(test__avl_tree_init_copy__non_empty),\
    UT_CASE(test__avl_tree_init_copy__non_null_compare),\
    UT_CASE_BEGIN(_avl_tree_init_copy_range, test__avl_tree_init_copy_range__null_avl_tree),\
    UT_CASE(test__avl_tree_init_copy_range__non_created_avl_tree),\
    UT_CASE(test__avl_tree_init_copy_range__invalid_begin),\
    UT_CASE(test__avl_tree_init_copy_range__invalid_end),\
    UT_CASE(test__avl_tree_init_copy_range__invalid_range),\
    UT_CASE(test__avl_tree_init_copy_range__invalid_range_not_same_type),\
    UT_CASE(test__avl_tree_init_copy_range__empty),\
    UT_CASE(test__avl_tree_init_copy_range__non_empty),\
    UT_CASE_BEGIN(_avl_tree_init_copy_range_ex, test__avl_tree_init_copy_range_ex__null_avl_tree),\
    UT_CASE(test__avl_tree_init_copy_range_ex__non_created_avl_tree),\
    UT_CASE(test__avl_tree_init_copy_range_ex__invalid_begin),\
    UT_CASE(test__avl_tree_init_copy_range_ex__invalid_end),\
    UT_CASE(test__avl_tree_init_copy_range_ex__invalid_range),\
    UT_CASE(test__avl_tree_init_copy_range_ex__invalid_range_not_same_type),\
    UT_CASE(test__avl_tree_init_copy_range_ex__empty),\
    UT_CASE(test__avl_tree_init_copy_range_ex__non_empty),\
    UT_CASE(test__avl_tree_init_copy_range_ex__compare),\

#endif /* _UT_CSTL_AVL_TREE_H_ */

