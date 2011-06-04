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
/*
 * test _rb_tree_same_type
 */
UT_CASE_DECLARATION(_rb_tree_same_type)
void test__rb_tree_same_type__null_first(void** state);
void test__rb_tree_same_type__null_second(void** state);
void test__rb_tree_same_type__non_created_first(void** state);
void test__rb_tree_same_type__non_created_second(void** state);
void test__rb_tree_same_type__same_type(void** state);
void test__rb_tree_same_type__not_same_type(void** state);
/*
 * test _rb_tree_same_type_ex
 */
UT_CASE_DECLARATION(_rb_tree_same_type_ex)
void test__rb_tree_same_type_ex__null_first(void** state);
void test__rb_tree_same_type_ex__null_second(void** state);
void test__rb_tree_same_type_ex__non_created_first(void** state);
void test__rb_tree_same_type_ex__non_created_second(void** state);
void test__rb_tree_same_type_ex__same_type(void** state);
void test__rb_tree_same_type_ex__not_same_type(void** state);
void test__rb_tree_same_type_ex__not_same_compare(void** state);
/*
 * test _rb_tree_destroy_subtree
 */
UT_CASE_DECLARATION(_rb_tree_destroy_subtree)
void test__rb_tree_destroy_subtree__null_rb_tree(void** state);
void test__rb_tree_destroy_subtree__non_inited(void** state);
void test__rb_tree_destroy_subtree__null_root(void** state);
void test__rb_tree_destroy_subtree__root(void** state);
/*
 * test _rb_tree_find_value
 */
UT_CASE_DECLARATION(_rb_tree_find_value)
void test__rb_tree_find_value__null_rb_tree(void** state);
void test__rb_tree_find_value__non_inited(void** state);
void test__rb_tree_find_value__null_value(void** state);
void test__rb_tree_find_value__empty(void** state);
void test__rb_tree_find_value__non_empty_not_find(void** state);
void test__rb_tree_find_value__non_empty_find(void** state);
/*
 * test _rb_tree_clockwise_rotation
 */
UT_CASE_DECLARATION(_rb_tree_clockwise_rotation)
void test__rb_tree_clockwise_rotation__null_root(void** state);
void test__rb_tree_clockwise_rotation__null_root_left(void** state);
void test__rb_tree_clockwise_rotation__rotate(void** state);
/*
 * test _rb_tree_anticlockwise_rotation
 */
UT_CASE_DECLARATION(_rb_tree_anticlockwise_rotation)
void test__rb_tree_anticlockwise_rotation__null_root(void** state);
void test__rb_tree_anticlockwise_rotation__null_root_right(void** state);
void test__rb_tree_anticlockwise_rotation__rotate(void** state);
/*
 * test _rb_tree_insert_rbnode
 */
UT_CASE_DECLARATION(_rb_tree_insert_rbnode)
void test__rb_tree_insert_rbnode__null_rb_tree(void** state);
void test__rb_tree_insert_rbnode__non_inited(void** state);
void test__rb_tree_insert_rbnode__null_value(void** state);
void test__rb_tree_insert_rbnode__empty(void** state);
void test__rb_tree_insert_rbnode__left_red(void** state);
void test__rb_tree_insert_rbnode__right_red(void** state);
void test__rb_tree_insert_rbnode__children_red(void** state);
void test__rb_tree_insert_rbnode__root_red_children(void** state);
void test__rb_tree_insert_rbnode__not_root_red_children(void** state);
void test__rb_tree_insert_rbnode__red_left_child(void** state);
void test__rb_tree_insert_rbnode__red_right_child(void** state);

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
    UT_CASE_BEGIN(_rb_tree_same_type, test__rb_tree_same_type__null_first),\
    UT_CASE(test__rb_tree_same_type__null_second),\
    UT_CASE(test__rb_tree_same_type__non_created_first),\
    UT_CASE(test__rb_tree_same_type__non_created_second),\
    UT_CASE(test__rb_tree_same_type__same_type),\
    UT_CASE(test__rb_tree_same_type__not_same_type),\
    UT_CASE_BEGIN(_rb_tree_same_type_ex, test__rb_tree_same_type_ex__null_first),\
    UT_CASE(test__rb_tree_same_type_ex__null_second),\
    UT_CASE(test__rb_tree_same_type_ex__non_created_first),\
    UT_CASE(test__rb_tree_same_type_ex__non_created_second),\
    UT_CASE(test__rb_tree_same_type_ex__same_type),\
    UT_CASE(test__rb_tree_same_type_ex__not_same_type),\
    UT_CASE(test__rb_tree_same_type_ex__not_same_compare),\
    UT_CASE_BEGIN(_rb_tree_destroy_subtree, test__rb_tree_destroy_subtree__null_rb_tree),\
    UT_CASE(test__rb_tree_destroy_subtree__non_inited),\
    UT_CASE(test__rb_tree_destroy_subtree__null_root),\
    UT_CASE(test__rb_tree_destroy_subtree__root),\
    UT_CASE_BEGIN(_rb_tree_find_value, test__rb_tree_find_value__null_rb_tree),\
    UT_CASE(test__rb_tree_find_value__non_inited),\
    UT_CASE(test__rb_tree_find_value__null_value),\
    UT_CASE(test__rb_tree_find_value__empty),\
    UT_CASE(test__rb_tree_find_value__non_empty_not_find),\
    UT_CASE(test__rb_tree_find_value__non_empty_find),\
    UT_CASE_BEGIN(_rb_tree_clockwise_rotation, test__rb_tree_clockwise_rotation__null_root),\
    UT_CASE(test__rb_tree_clockwise_rotation__null_root_left),\
    UT_CASE(test__rb_tree_clockwise_rotation__rotate),\
    UT_CASE_BEGIN(_rb_tree_anticlockwise_rotation, test__rb_tree_anticlockwise_rotation__null_root),\
    UT_CASE(test__rb_tree_anticlockwise_rotation__null_root_right),\
    UT_CASE(test__rb_tree_anticlockwise_rotation__rotate),\
    UT_CASE_BEGIN(_rb_tree_insert_rbnode, test__rb_tree_insert_rbnode__null_rb_tree),\
    UT_CASE(test__rb_tree_insert_rbnode__non_inited),\
    UT_CASE(test__rb_tree_insert_rbnode__null_value),\
    UT_CASE(test__rb_tree_insert_rbnode__empty),\
    UT_CASE(test__rb_tree_insert_rbnode__left_red),\
    UT_CASE(test__rb_tree_insert_rbnode__right_red),\
    UT_CASE(test__rb_tree_insert_rbnode__children_red),\
    UT_CASE(test__rb_tree_insert_rbnode__root_red_children),\
    UT_CASE(test__rb_tree_insert_rbnode__not_root_red_children),\
    UT_CASE(test__rb_tree_insert_rbnode__red_left_child),\
    UT_CASE(test__rb_tree_insert_rbnode__red_right_child),\

#endif /* _UT_CSTL_RB_TREE_AUX_H_ */

