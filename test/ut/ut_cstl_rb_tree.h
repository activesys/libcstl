#ifndef _UT_CSTL_RB_TREE_H_
#define _UT_CSTL_RB_TREE_H_

UT_SUIT_DECLARATION(cstl_rb_tree)
/*
 * test _create_rb_tree
 */
UT_CASE_DECLARATION(_create_rb_tree)
void test__create_rb_tree__null_typename(void** state);
void test__create_rb_tree__c_builtin(void** state);
void test__create_rb_tree__cstr(void** state);
void test__create_rb_tree__libcstl_builtin(void** state);
void test__create_rb_tree__user_define(void** state);
void test__create_rb_tree__unregister(void** state);
/*
 * test _rb_tree_init
 */
UT_CASE_DECLARATION(_rb_tree_init)
void test__rb_tree_init__null_rb_tree(void** state);
void test__rb_tree_init__non_created(void** state);
void test__rb_tree_init__null_compare(void** state);
void test__rb_tree_init__non_null_compare(void** state);
/*
 * test _rb_tree_init_copy
 */
UT_CASE_DECLARATION(_rb_tree_init_copy)
void test__rb_tree_init_copy__null_dest(void** state);
void test__rb_tree_init_copy__null_src(void** state);
void test__rb_tree_init_copy__non_created_dest(void** state);
void test__rb_tree_init_copy__non_inited_src(void** state);
void test__rb_tree_init_copy__not_same_type(void** state);
void test__rb_tree_init_copy__empty(void** state);
void test__rb_tree_init_copy__non_empty(void** state);
void test__rb_tree_init_copy__non_null_compare(void** state);

#define UT_CSTL_RB_TREE_CASE\
    UT_SUIT_BEGIN(cstl_rb_tree, test__create_rb_tree__null_typename),\
    UT_CASE(test__create_rb_tree__c_builtin),\
    UT_CASE(test__create_rb_tree__cstr),\
    UT_CASE(test__create_rb_tree__libcstl_builtin),\
    UT_CASE(test__create_rb_tree__user_define),\
    UT_CASE(test__create_rb_tree__unregister),\
    UT_CASE_BEGIN(_rb_tree_init,  test__rb_tree_init__null_rb_tree),\
    UT_CASE(test__rb_tree_init__non_created),\
    UT_CASE(test__rb_tree_init__null_compare),\
    UT_CASE(test__rb_tree_init__non_null_compare),\
    UT_CASE_BEGIN(_rb_tree_init_copy, test__rb_tree_init_copy__null_dest),\
    UT_CASE(test__rb_tree_init_copy__null_src),\
    UT_CASE(test__rb_tree_init_copy__non_created_dest),\
    UT_CASE(test__rb_tree_init_copy__non_inited_src),\
    UT_CASE(test__rb_tree_init_copy__not_same_type),\
    UT_CASE(test__rb_tree_init_copy__empty),\
    UT_CASE(test__rb_tree_init_copy__non_empty),\
    UT_CASE(test__rb_tree_init_copy__non_null_compare),\

#endif /* _UT_CSTL_RB_TREE_H_ */

