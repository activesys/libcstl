#ifndef _UT_CSTL_AVL_TREE_PRIVATE_H_
#define _UT_CSTL_AVL_TREE_PRIVATE_H_

UT_SUIT_DECLARATION(cstl_avl_tree_private)
/*
 * test _create_avl_tree_auxiliary
 */
UT_CASE_DECLARATION(_create_avl_tree_auxiliary)
void test__create_avl_tree_auxiliary__null_avl_tree(void** state);
void test__create_avl_tree_auxiliary__null_typename(void** state);
void test__create_avl_tree_auxiliary__unregistered(void** state);
void test__create_avl_tree_auxiliary__c_builtin(void** state);
void test__create_avl_tree_auxiliary__cstr(void** state);
void test__create_avl_tree_auxiliary__libcstl_builtin(void** state);
void test__create_avl_tree_auxiliary__user_define(void** state);
/*
 * test _avl_tree_destroy_auxiliary
 */
UT_CASE_DECLARATION(_avl_tree_destroy_auxiliary)
void test__avl_tree_destroy_auxiliary__null_avl_tree(void** state);
void test__avl_tree_destroy_auxiliary__non_created(void** state);
void test__avl_tree_destroy_auxiliary__non_inited(void** state);
void test__avl_tree_destroy_auxiliary__empty(void** state);
void test__avl_tree_destroy_auxiliary__non_empty(void** state);

#define UT_CSTL_AVL_TREE_PRIVATE_CASE\
    UT_SUIT_BEGIN(cstl_avl_tree_private, test__create_avl_tree_auxiliary__null_avl_tree),\
    UT_CASE(test__create_avl_tree_auxiliary__null_typename),\
    UT_CASE(test__create_avl_tree_auxiliary__unregistered),\
    UT_CASE(test__create_avl_tree_auxiliary__c_builtin),\
    UT_CASE(test__create_avl_tree_auxiliary__cstr),\
    UT_CASE(test__create_avl_tree_auxiliary__libcstl_builtin),\
    UT_CASE(test__create_avl_tree_auxiliary__user_define),\
    UT_CASE_BEGIN(_avl_tree_destroy_auxiliary, test__avl_tree_destroy_auxiliary__null_avl_tree),\
    UT_CASE(test__avl_tree_destroy_auxiliary__non_created),\
    UT_CASE(test__avl_tree_destroy_auxiliary__non_inited),\
    UT_CASE(test__avl_tree_destroy_auxiliary__empty),\
    UT_CASE(test__avl_tree_destroy_auxiliary__non_empty)

#endif /* _UT_CSTL_AVL_TREE_PRIVATE_H_ */

