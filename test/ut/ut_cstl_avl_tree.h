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

#define UT_CSTL_AVL_TREE_CASE\
    UT_SUIT_BEGIN(cstl_avl_tree, test__create_avl_tree__null_typename),\
    UT_CASE(test__create_avl_tree__c_builtin),\
    UT_CASE(test__create_avl_tree__cstr),\
    UT_CASE(test__create_avl_tree__libcstl_builtin),\
    UT_CASE(test__create_avl_tree__user_define),\
    UT_CASE(test__create_avl_tree__unregister),\

#endif /* _UT_CSTL_AVL_TREE_H_ */

