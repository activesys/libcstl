#ifndef _UT_CSTL_RB_TREE_AUX_H_
#define _UT_CSTL_RB_TREE_AUX_H_

UT_SUIT_DECLARATION(cstl_rb_tree_aux)
/*
 * test _rb_tree_is_created
 */
UT_CASE_DECLARATION(_rb_tree_is_created)
void test__rb_tree_is_created__null_rb_tree(void** state);
void test__rb_tree_is_created__non_inited_allocator(void** state);
void test__rb_tree_is_created__invalid_rbroot_left(void** state);
void test__rb_tree_is_created__invalid_rbroot_right(void** state);
void test__rb_tree_is_created__invalid_rbroot_parent(void** state);
void test__rb_tree_is_created__invalid_rbroot_color(void** state);
void test__rb_tree_is_created__invalid_compare(void** state);
void test__rb_tree_is_created__invalid_nodecount(void** state);
void test__rb_tree_is_created__invalid_typeinfo_style(void** state);
void test__rb_tree_is_created__invalid_typeinfo_type(void** state);
void test__rb_tree_is_created__created(void** state);
/*
 * test _rb_tree_is_inited
 */
UT_CASE_DECLARATION(_rb_tree_is_inited)
void test__rb_tree_is_inited__null_rb_tree(void** state);
void test__rb_tree_is_inited__invalid_typeinfo_style(void** state);
void test__rb_tree_is_inited__invalid_typeinfo_type(void** state);
void test__rb_tree_is_inited__invalid_rbroot_left(void** state);
void test__rb_tree_is_inited__invalid_rbroot_right(void** state);
void test__rb_tree_is_inited__invalid_rbroot_color(void** state);
void test__rb_tree_is_inited__invalid_compare(void** state);
void test__rb_tree_is_inited__inited(void** state);

#define UT_CSTL_RB_TREE_AUX_CASE\
    UT_SUIT_BEGIN(cstl_rb_tree_aux, test__rb_tree_is_created__null_rb_tree),\
    UT_CASE(test__rb_tree_is_created__non_inited_allocator),\
    UT_CASE(test__rb_tree_is_created__invalid_rbroot_left),\
    UT_CASE(test__rb_tree_is_created__invalid_rbroot_right),\
    UT_CASE(test__rb_tree_is_created__invalid_rbroot_parent),\
    UT_CASE(test__rb_tree_is_created__invalid_rbroot_color),\
    UT_CASE(test__rb_tree_is_created__invalid_compare),\
    UT_CASE(test__rb_tree_is_created__invalid_nodecount),\
    UT_CASE(test__rb_tree_is_created__invalid_typeinfo_style),\
    UT_CASE(test__rb_tree_is_created__invalid_typeinfo_type),\
    UT_CASE(test__rb_tree_is_created__created),\
    UT_CASE_BEGIN(_rb_tree_is_inited, test__rb_tree_is_inited__null_rb_tree),\
    UT_CASE(test__rb_tree_is_inited__invalid_typeinfo_style),\
    UT_CASE(test__rb_tree_is_inited__invalid_typeinfo_type),\
    UT_CASE(test__rb_tree_is_inited__invalid_rbroot_left),\
    UT_CASE(test__rb_tree_is_inited__invalid_rbroot_right),\
    UT_CASE(test__rb_tree_is_inited__invalid_rbroot_color),\
    UT_CASE(test__rb_tree_is_inited__invalid_compare),\
    UT_CASE(test__rb_tree_is_inited__inited),\

#endif /* _UT_CSTL_RB_TREE_AUX_H_ */

