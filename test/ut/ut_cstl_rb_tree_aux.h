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
/*
 * test _rb_tree_iterator_belong_to_rb_tree
 */
UT_CASE_DECLARATION(_rb_tree_iterator_belong_to_rb_tree)
void test__rb_tree_iterator_belong_to_rb_tree__null_rb_tree(void** state);
void test__rb_tree_iterator_belong_to_rb_tree__non_inited_rb_tree(void** state);
void test__rb_tree_iterator_belong_to_rb_tree__invalid_iter_corepos(void** state);
void test__rb_tree_iterator_belong_to_rb_tree__invalid_iter_rb_tree(void** state);
void test__rb_tree_iterator_belong_to_rb_tree__empty_begin(void** state);
void test__rb_tree_iterator_belong_to_rb_tree__empty_end(void** state);
void test__rb_tree_iterator_belong_to_rb_tree__non_empty_begin(void** state);
void test__rb_tree_iterator_belong_to_rb_tree__non_empty_middle(void** state);
void test__rb_tree_iterator_belong_to_rb_tree__non_empty_end(void** state);
void test__rb_tree_iterator_belong_to_rb_tree__invalid_pos(void** state);
/*
 * test _rb_tree_same_rb_tree_iterator_type
 */
UT_CASE_DECLARATION(_rb_tree_same_rb_tree_iterator_type)
void test__rb_tree_same_rb_tree_iterator_type__null_rb_tree(void** state);
void test__rb_tree_same_rb_tree_iterator_type__non_created(void** state);
void test__rb_tree_same_rb_tree_iterator_type__invalid_iter(void** state);
void test__rb_tree_same_rb_tree_iterator_type__same_container(void** state);
void test__rb_tree_same_rb_tree_iterator_type__same(void** state);
void test__rb_tree_same_rb_tree_iterator_type__not_same(void** state);
/*
 * test _rb_tree_same_rb_tree_iterator_type_ex
 */
UT_CASE_DECLARATION(_rb_tree_same_rb_tree_iterator_type_ex)
void test__rb_tree_same_rb_tree_iterator_type_ex__null_rb_tree(void** state);
void test__rb_tree_same_rb_tree_iterator_type_ex__non_created(void** state);
void test__rb_tree_same_rb_tree_iterator_type_ex__invalid_iter(void** state);
void test__rb_tree_same_rb_tree_iterator_type_ex__same_container(void** state);
void test__rb_tree_same_rb_tree_iterator_type_ex__same(void** state);
void test__rb_tree_same_rb_tree_iterator_type_ex__not_same(void** state);
/*
 * test _rb_tree_rbnode_belong_to_rb_tree
 */
UT_CASE_DECLARATION(_rb_tree_rbnode_belong_to_rb_tree)
void test__rb_tree_rbnode_belong_to_rb_tree__null_root(void** state);
void test__rb_tree_rbnode_belong_to_rb_tree__null_pos(void** state);
void test__rb_tree_rbnode_belong_to_rb_tree__equal(void** state);
void test__rb_tree_rbnode_belong_to_rb_tree__find(void** state);
void test__rb_tree_rbnode_belong_to_rb_tree__not_find(void** state);

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
    UT_CASE_BEGIN(_rb_tree_iterator_belong_to_rb_tree, test__rb_tree_iterator_belong_to_rb_tree__null_rb_tree),\
    UT_CASE(test__rb_tree_iterator_belong_to_rb_tree__non_inited_rb_tree),\
    UT_CASE(test__rb_tree_iterator_belong_to_rb_tree__invalid_iter_corepos),\
    UT_CASE(test__rb_tree_iterator_belong_to_rb_tree__invalid_iter_rb_tree),\
    UT_CASE(test__rb_tree_iterator_belong_to_rb_tree__empty_begin),\
    UT_CASE(test__rb_tree_iterator_belong_to_rb_tree__empty_end),\
    UT_CASE(test__rb_tree_iterator_belong_to_rb_tree__non_empty_begin),\
    UT_CASE(test__rb_tree_iterator_belong_to_rb_tree__non_empty_middle),\
    UT_CASE(test__rb_tree_iterator_belong_to_rb_tree__non_empty_end),\
    UT_CASE(test__rb_tree_iterator_belong_to_rb_tree__invalid_pos),\
    UT_CASE_BEGIN(_rb_tree_same_rb_tree_iterator_type, test__rb_tree_same_rb_tree_iterator_type__null_rb_tree),\
    UT_CASE(test__rb_tree_same_rb_tree_iterator_type__non_created),\
    UT_CASE(test__rb_tree_same_rb_tree_iterator_type__invalid_iter),\
    UT_CASE(test__rb_tree_same_rb_tree_iterator_type__same_container),\
    UT_CASE(test__rb_tree_same_rb_tree_iterator_type__same),\
    UT_CASE(test__rb_tree_same_rb_tree_iterator_type__not_same),\
    UT_CASE_BEGIN(_rb_tree_same_rb_tree_iterator_type_ex, test__rb_tree_same_rb_tree_iterator_type_ex__null_rb_tree),\
    UT_CASE(test__rb_tree_same_rb_tree_iterator_type_ex__non_created),\
    UT_CASE(test__rb_tree_same_rb_tree_iterator_type_ex__invalid_iter),\
    UT_CASE(test__rb_tree_same_rb_tree_iterator_type_ex__same_container),\
    UT_CASE(test__rb_tree_same_rb_tree_iterator_type_ex__same),\
    UT_CASE(test__rb_tree_same_rb_tree_iterator_type_ex__not_same),\
    UT_CASE_BEGIN(_rb_tree_rbnode_belong_to_rb_tree, test__rb_tree_rbnode_belong_to_rb_tree__null_root),\
    UT_CASE(test__rb_tree_rbnode_belong_to_rb_tree__null_pos),\
    UT_CASE(test__rb_tree_rbnode_belong_to_rb_tree__equal),\
    UT_CASE(test__rb_tree_rbnode_belong_to_rb_tree__find),\
    UT_CASE(test__rb_tree_rbnode_belong_to_rb_tree__not_find),\

#endif /* _UT_CSTL_RB_TREE_AUX_H_ */

