#ifndef _UT_CSTL_AVL_TREE_AUX_H_
#define _UT_CSTL_AVL_TREE_AUX_H_

UT_SUIT_DECLARATION(cstl_avl_tree_aux)
/*
 * test _avl_tree_is_created
 */
UT_CASE_DECLARATION(_avl_tree_is_created)
void test__avl_tree_is_created__null_avl_tree(void** state);
void test__avl_tree_is_created__non_inited_allocator(void** state);
void test__avl_tree_is_created__invalid_avlroot_left(void** state);
void test__avl_tree_is_created__invalid_avlroot_right(void** state);
void test__avl_tree_is_created__invalid_avlroot_parent(void** state);
void test__avl_tree_is_created__invalid_avlroot_height(void** state);
void test__avl_tree_is_created__invalid_compare(void** state);
void test__avl_tree_is_created__invalid_nodecount(void** state);
void test__avl_tree_is_created__invalid_typeinfo_style(void** state);
void test__avl_tree_is_created__invalid_typeinfo_type(void** state);
void test__avl_tree_is_created__created(void** state);
/*
 * test _avl_tree_is_inited
 */
UT_CASE_DECLARATION(_avl_tree_is_inited)
void test__avl_tree_is_inited__null_avl_tree(void** state);
void test__avl_tree_is_inited__invalid_typeinfo_style(void** state);
void test__avl_tree_is_inited__invalid_typeinfo_type(void** state);
void test__avl_tree_is_inited__invalid_avlroot_left(void** state);
void test__avl_tree_is_inited__invalid_avlroot_right(void** state);
void test__avl_tree_is_inited__invalid_avlroot_height(void** state);
void test__avl_tree_is_inited__invalid_compare(void** state);
void test__avl_tree_is_inited__inited(void** state);
/*
 * test _avl_tree_iterator_belong_to_avl_tree
 */
UT_CASE_DECLARATION(_avl_tree_iterator_belong_to_avl_tree)
void test__avl_tree_iterator_belong_to_avl_tree__null_avl_tree(void** state);
void test__avl_tree_iterator_belong_to_avl_tree__non_inited_avl_tree(void** state);
void test__avl_tree_iterator_belong_to_avl_tree__invalid_iter_corepos(void** state);
void test__avl_tree_iterator_belong_to_avl_tree__invalid_iter_avl_tree(void** state);
void test__avl_tree_iterator_belong_to_avl_tree__empty_begin(void** state);
void test__avl_tree_iterator_belong_to_avl_tree__empty_end(void** state);
void test__avl_tree_iterator_belong_to_avl_tree__non_empty_begin(void** state);
void test__avl_tree_iterator_belong_to_avl_tree__non_empty_middle(void** state);
void test__avl_tree_iterator_belong_to_avl_tree__non_empty_end(void** state);
void test__avl_tree_iterator_belong_to_avl_tree__invalid_pos(void** state);
/*
 * test _avl_tree_same_avl_tree_iterator_type
 */
UT_CASE_DECLARATION(_avl_tree_same_avl_tree_iterator_type)
void test__avl_tree_same_avl_tree_iterator_type__null_avl_tree(void** state);
void test__avl_tree_same_avl_tree_iterator_type__non_created(void** state);
void test__avl_tree_same_avl_tree_iterator_type__invalid_iter(void** state);
void test__avl_tree_same_avl_tree_iterator_type__same_container(void** state);
void test__avl_tree_same_avl_tree_iterator_type__same(void** state);
void test__avl_tree_same_avl_tree_iterator_type__not_same(void** state);
/*
 * test _avl_tree_same_iterator_type
 */
UT_CASE_DECLARATION(_avl_tree_same_iterator_type)
void test__avl_tree_same_iterator_type__null_avl_tree_container(void** state);
void test__avl_tree_same_iterator_type__invalid_iterator_null_container(void** state);
void test__avl_tree_same_iterator_type__invalid_iterator_container_type(void** state);
void test__avl_tree_same_iterator_type__invalid_iterator_iterator_type(void** state);
/*
void test__avl_tree_same_iterator_type__same_type_belong_to_avl_tree(void** state);
void test__avl_tree_same_iterator_type__same_type_not_belong_to_avl_tree(void** state);
void test__avl_tree_same_iterator_type__not_same_type(void** state);
*/
void test__avl_tree_same_iterator_type__same_type_not_avl_tree_iterator(void** state);
void test__avl_tree_same_iterator_type__not_same_type_not_avl_tree_iterator(void** state);
/*
 * test _avl_tree_same_avl_tree_iterator_type_ex
 */
UT_CASE_DECLARATION(_avl_tree_same_avl_tree_iterator_type_ex)
void test__avl_tree_same_avl_tree_iterator_type_ex__null_avl_tree(void** state);
void test__avl_tree_same_avl_tree_iterator_type_ex__non_created(void** state);
void test__avl_tree_same_avl_tree_iterator_type_ex__invalid_iter(void** state);
void test__avl_tree_same_avl_tree_iterator_type_ex__same_container(void** state);
void test__avl_tree_same_avl_tree_iterator_type_ex__same(void** state);
void test__avl_tree_same_avl_tree_iterator_type_ex__not_same(void** state);
/*
 * test _avl_tree_avlnode_belong_to_avl_tree
 */
UT_CASE_DECLARATION(_avl_tree_avlnode_belong_to_avl_tree)
void test__avl_tree_avlnode_belong_to_avl_tree__null_root(void** state);
void test__avl_tree_avlnode_belong_to_avl_tree__null_pos(void** state);
void test__avl_tree_avlnode_belong_to_avl_tree__equal(void** state);
void test__avl_tree_avlnode_belong_to_avl_tree__find(void** state);
void test__avl_tree_avlnode_belong_to_avl_tree__not_find(void** state);
/*
 * test _avl_tree_same_type
 */
UT_CASE_DECLARATION(_avl_tree_same_type)
void test__avl_tree_same_type__null_first(void** state);
void test__avl_tree_same_type__null_second(void** state);
void test__avl_tree_same_type__non_created_first(void** state);
void test__avl_tree_same_type__non_created_second(void** state);
void test__avl_tree_same_type__same_type(void** state);
void test__avl_tree_same_type__not_same_type(void** state);
/*
 * test _avl_tree_same_type_ex
 */
UT_CASE_DECLARATION(_avl_tree_same_type_ex)
void test__avl_tree_same_type_ex__null_first(void** state);
void test__avl_tree_same_type_ex__null_second(void** state);
void test__avl_tree_same_type_ex__non_created_first(void** state);
void test__avl_tree_same_type_ex__non_created_second(void** state);
void test__avl_tree_same_type_ex__same_type(void** state);
void test__avl_tree_same_type_ex__not_same_type(void** state);
void test__avl_tree_same_type_ex__not_same_compare(void** state);
/*
 * test _avl_tree_find_value
 */
UT_CASE_DECLARATION(_avl_tree_find_value)
void test__avl_tree_find_value__null_avl_tree(void** state);
void test__avl_tree_find_value__non_inited(void** state);
void test__avl_tree_find_value__null_value(void** state);
void test__avl_tree_find_value__empty(void** state);
void test__avl_tree_find_value__non_empty_not_find(void** state);
void test__avl_tree_find_value__non_empty_find(void** state);
/*
 * test _avl_tree_destroy_subtree
 */
UT_CASE_DECLARATION(_avl_tree_destroy_subtree)
void test__avl_tree_destroy_subtree__null_avl_tree(void** state);
void test__avl_tree_destroy_subtree__non_inited(void** state);
void test__avl_tree_destroy_subtree__null_root(void** state);
void test__avl_tree_destroy_subtree__root(void** state);
/*
 * test _avl_tree_left_signal_rotate
 */
UT_CASE_DECLARATION(_avl_tree_left_signal_rotate)
void test__avl_tree_left_signal_rotate__null_root(void** state);
void test__avl_tree_left_signal_rotate__null_root_left(void** state);
void test__avl_tree_left_signal_rotate__rotate(void** state);
/*
 * test _avl_tree_right_signal_rotate
 */
UT_CASE_DECLARATION(_avl_tree_right_signal_rotate)
void test__avl_tree_right_signal_rotate__null_root(void** state);
void test__avl_tree_right_signal_rotate__null_root_right(void** state);
void test__avl_tree_right_signal_rotate__rotate(void** state);
/*
 * test _avl_tree_left_double_rotate
 */
UT_CASE_DECLARATION(_avl_tree_left_double_rotate)
void test__avl_tree_left_double_rotate__null_root(void** state);
void test__avl_tree_left_double_rotate__rotate(void** state);
/*
 * test _avl_tree_right_double_rotate
 */
UT_CASE_DECLARATION(_avl_tree_right_double_rotate)
void test__avl_tree_right_double_rotate__null_root(void** state);
void test__avl_tree_right_double_rotate__rotate(void** state);
/*
 * test _avl_tree_insert_avlnode
 */
UT_CASE_DECLARATION(_avl_tree_insert_avlnode)
void test__avl_tree_insert_avlnode__null_avl_tree(void** state);
void test__avl_tree_insert_avlnode__non_inited(void** state);
void test__avl_tree_insert_avlnode__null_value(void** state);
void test__avl_tree_insert_avlnode__empty(void** state);
void test__avl_tree_insert_avlnode__left(void** state);
void test__avl_tree_insert_avlnode__right(void** state);
void test__avl_tree_insert_avlnode__rotate(void** state);
/*
 * test _avl_tree_get_height
 */
UT_CASE_DECLARATION(_avl_tree_get_height)
void test__avl_tree_get_height__null_root(void** state);
void test__avl_tree_get_heght__not_null(void** state);
/*
 * test _avl_tree_get_min_avlnode
 */
UT_CASE_DECLARATION(_avl_tree_get_min_avlnode)
void test__avl_tree_get_min_avlnode__null_root(void** state);
void test__avl_tree_get_min_avlnode__one_node(void** state);
void test__avl_tree_get_min_avlnode__sub_tree(void** state);
/*
 * test _avl_tree_get_max_avlnode
 */
UT_CASE_DECLARATION(_avl_tree_get_max_avlnode)
void test__avl_tree_get_max_avlnode__null_root(void** state);
void test__avl_tree_get_max_avlnode__one_node(void** state);
void test__avl_tree_get_max_avlnode__sub_tree(void** state);
/*
 * test _avl_tree_rebalance
 */
UT_CASE_DECLARATION(_avl_tree_rebalance)
void test___avl_tree_rebalance__null(void** state);
void test__avl_tree_rebalance__ll(void** state);
void test__avl_tree_rebalance__lr(void** state);
void test__avl_tree_rebalance__rr(void** state);
void test__avl_tree_rebalance__rl(void** state);
void test__avl_tree_rebalance__no_rotate(void** state);
/*
 * test _avl_tree_init_elem_auxiliary
 */
UT_CASE_DECLARATION(_avl_tree_init_elem_auxiliary)
void test__avl_tree_init_elem_auxiliary__null_avl_tree(void** state);
void test__avl_tree_init_elem_auxiliary__null_node(void** state);
void test__avl_tree_init_elem_auxiliary__non_inited(void** state);
void test__avl_tree_init_elem_auxiliary__c_builtin(void** state);
void test__avl_tree_init_elem_auxiliary__cstr(void** state);
void test__avl_tree_init_elem_auxiliary__cstl_builtin(void** state);
void test__avl_tree_init_elem_auxiliary__user_define(void** state);
/*
 * test _avl_tree_elem_compare_auxiliary
 */
UT_CASE_DECLARATION(_avl_tree_elem_compare_auxiliary)
void test__avl_tree_elem_compare_auxiliary__null_avl_tree(void** state);
void test__avl_tree_elem_compare_auxiliary__null_first(void** state);
void test__avl_tree_elem_compare_auxiliary__null_second(void** state);
void test__avl_tree_elem_compare_auxiliary__null_output(void** state);
void test__avl_tree_elem_compare_auxiliary__non_inited(void** state);
void test__avl_tree_elem_compare_auxiliary__int(void** state);
void test__avl_tree_elem_compare_auxiliary__cstr(void** state);

#define UT_CSTL_AVL_TREE_AUX_CASE\
    UT_SUIT_BEGIN(cstl_avl_tree_aux, test__avl_tree_is_created__null_avl_tree),\
    UT_CASE(test__avl_tree_is_created__non_inited_allocator),\
    UT_CASE(test__avl_tree_is_created__invalid_avlroot_left),\
    UT_CASE(test__avl_tree_is_created__invalid_avlroot_right),\
    UT_CASE(test__avl_tree_is_created__invalid_avlroot_parent),\
    UT_CASE(test__avl_tree_is_created__invalid_avlroot_height),\
    UT_CASE(test__avl_tree_is_created__invalid_compare),\
    UT_CASE(test__avl_tree_is_created__invalid_nodecount),\
    UT_CASE(test__avl_tree_is_created__invalid_typeinfo_style),\
    UT_CASE(test__avl_tree_is_created__invalid_typeinfo_type),\
    UT_CASE(test__avl_tree_is_created__created),\
    UT_CASE_BEGIN(_avl_tree_is_inited, test__avl_tree_is_inited__null_avl_tree),\
    UT_CASE(test__avl_tree_is_inited__invalid_typeinfo_style),\
    UT_CASE(test__avl_tree_is_inited__invalid_typeinfo_type),\
    UT_CASE(test__avl_tree_is_inited__invalid_avlroot_left),\
    UT_CASE(test__avl_tree_is_inited__invalid_avlroot_right),\
    UT_CASE(test__avl_tree_is_inited__invalid_avlroot_height),\
    UT_CASE(test__avl_tree_is_inited__invalid_compare),\
    UT_CASE(test__avl_tree_is_inited__inited),\
    UT_CASE_BEGIN(_avl_tree_iterator_belong_to_avl_tree, test__avl_tree_iterator_belong_to_avl_tree__null_avl_tree),\
    UT_CASE(test__avl_tree_iterator_belong_to_avl_tree__non_inited_avl_tree),\
    UT_CASE(test__avl_tree_iterator_belong_to_avl_tree__invalid_iter_corepos),\
    UT_CASE(test__avl_tree_iterator_belong_to_avl_tree__invalid_iter_avl_tree),\
    UT_CASE(test__avl_tree_iterator_belong_to_avl_tree__empty_begin),\
    UT_CASE(test__avl_tree_iterator_belong_to_avl_tree__empty_end),\
    UT_CASE(test__avl_tree_iterator_belong_to_avl_tree__non_empty_begin),\
    UT_CASE(test__avl_tree_iterator_belong_to_avl_tree__non_empty_middle),\
    UT_CASE(test__avl_tree_iterator_belong_to_avl_tree__non_empty_end),\
    UT_CASE(test__avl_tree_iterator_belong_to_avl_tree__invalid_pos),\
    UT_CASE_BEGIN(_avl_tree_same_avl_tree_iterator_type, test__avl_tree_same_avl_tree_iterator_type__null_avl_tree),\
    UT_CASE(test__avl_tree_same_avl_tree_iterator_type__non_created),\
    UT_CASE(test__avl_tree_same_avl_tree_iterator_type__invalid_iter),\
    UT_CASE(test__avl_tree_same_avl_tree_iterator_type__same_container),\
    UT_CASE(test__avl_tree_same_avl_tree_iterator_type__same),\
    UT_CASE(test__avl_tree_same_avl_tree_iterator_type__not_same),\
    UT_CASE_BEGIN(_avl_tree_same_iterator_type, test__avl_tree_same_iterator_type__null_avl_tree_container),\
    UT_CASE(test__avl_tree_same_iterator_type__invalid_iterator_null_container),\
    UT_CASE(test__avl_tree_same_iterator_type__invalid_iterator_container_type),\
    UT_CASE(test__avl_tree_same_iterator_type__invalid_iterator_iterator_type),\
    UT_CASE(test__avl_tree_same_iterator_type__same_type_not_avl_tree_iterator),\
    UT_CASE(test__avl_tree_same_iterator_type__not_same_type_not_avl_tree_iterator),\
    UT_CASE_BEGIN(_avl_tree_same_avl_tree_iterator_type_ex, test__avl_tree_same_avl_tree_iterator_type_ex__null_avl_tree),\
    UT_CASE(test__avl_tree_same_avl_tree_iterator_type_ex__non_created),\
    UT_CASE(test__avl_tree_same_avl_tree_iterator_type_ex__invalid_iter),\
    UT_CASE(test__avl_tree_same_avl_tree_iterator_type_ex__same_container),\
    UT_CASE(test__avl_tree_same_avl_tree_iterator_type_ex__same),\
    UT_CASE(test__avl_tree_same_avl_tree_iterator_type_ex__not_same),\
    UT_CASE_BEGIN(_avl_tree_avlnode_belong_to_avl_tree, test__avl_tree_avlnode_belong_to_avl_tree__null_root),\
    UT_CASE(test__avl_tree_avlnode_belong_to_avl_tree__null_pos),\
    UT_CASE(test__avl_tree_avlnode_belong_to_avl_tree__equal),\
    UT_CASE(test__avl_tree_avlnode_belong_to_avl_tree__find),\
    UT_CASE(test__avl_tree_avlnode_belong_to_avl_tree__not_find),\
    UT_CASE_BEGIN(_avl_tree_same_type, test__avl_tree_same_type__null_first),\
    UT_CASE(test__avl_tree_same_type__null_second),\
    UT_CASE(test__avl_tree_same_type__non_created_first),\
    UT_CASE(test__avl_tree_same_type__non_created_second),\
    UT_CASE(test__avl_tree_same_type__same_type),\
    UT_CASE(test__avl_tree_same_type__not_same_type),\
    UT_CASE_BEGIN(_avl_tree_same_type_ex, test__avl_tree_same_type_ex__null_first),\
    UT_CASE(test__avl_tree_same_type_ex__null_second),\
    UT_CASE(test__avl_tree_same_type_ex__non_created_first),\
    UT_CASE(test__avl_tree_same_type_ex__non_created_second),\
    UT_CASE(test__avl_tree_same_type_ex__same_type),\
    UT_CASE(test__avl_tree_same_type_ex__not_same_type),\
    UT_CASE(test__avl_tree_same_type_ex__not_same_compare),\
    UT_CASE_BEGIN(_avl_tree_find_value, test__avl_tree_find_value__null_avl_tree),\
    UT_CASE(test__avl_tree_find_value__non_inited),\
    UT_CASE(test__avl_tree_find_value__null_value),\
    UT_CASE(test__avl_tree_find_value__empty),\
    UT_CASE(test__avl_tree_find_value__non_empty_not_find),\
    UT_CASE(test__avl_tree_find_value__non_empty_find),\
    UT_CASE_BEGIN(_avl_tree_destroy_subtree, test__avl_tree_destroy_subtree__null_avl_tree),\
    UT_CASE(test__avl_tree_destroy_subtree__non_inited),\
    UT_CASE(test__avl_tree_destroy_subtree__null_root),\
    UT_CASE(test__avl_tree_destroy_subtree__root),\
    UT_CASE_BEGIN(_avl_tree_left_signal_rotate, test__avl_tree_left_signal_rotate__null_root),\
    UT_CASE(test__avl_tree_left_signal_rotate__null_root_left),\
    UT_CASE(test__avl_tree_left_signal_rotate__rotate),\
    UT_CASE_BEGIN(_avl_tree_right_signal_rotate, test__avl_tree_right_signal_rotate__null_root),\
    UT_CASE(test__avl_tree_right_signal_rotate__null_root_right),\
    UT_CASE(test__avl_tree_right_signal_rotate__rotate),\
    UT_CASE_BEGIN(_avl_tree_left_double_rotate, test__avl_tree_left_double_rotate__null_root),\
    UT_CASE(test__avl_tree_left_double_rotate__rotate),\
    UT_CASE_BEGIN(_avl_tree_right_double_rotate, test__avl_tree_right_double_rotate__null_root),\
    UT_CASE(test__avl_tree_right_double_rotate__rotate),\
    UT_CASE_BEGIN(_avl_tree_insert_avlnode, test__avl_tree_insert_avlnode__null_avl_tree),\
    UT_CASE(test__avl_tree_insert_avlnode__non_inited),\
    UT_CASE(test__avl_tree_insert_avlnode__null_value),\
    UT_CASE(test__avl_tree_insert_avlnode__empty),\
    UT_CASE(test__avl_tree_insert_avlnode__left),\
    UT_CASE(test__avl_tree_insert_avlnode__right),\
    UT_CASE(test__avl_tree_insert_avlnode__rotate),\
    UT_CASE_BEGIN(_avl_tree_get_height, test__avl_tree_get_height__null_root),\
    UT_CASE(test__avl_tree_get_heght__not_null),\
    UT_CASE_BEGIN(_avl_tree_get_min_avlnode, test__avl_tree_get_min_avlnode__null_root),\
    UT_CASE(test__avl_tree_get_min_avlnode__one_node),\
    UT_CASE(test__avl_tree_get_min_avlnode__sub_tree),\
    UT_CASE_BEGIN(_avl_tree_get_max_avlnode, test__avl_tree_get_max_avlnode__null_root),\
    UT_CASE(test__avl_tree_get_max_avlnode__one_node),\
    UT_CASE(test__avl_tree_get_max_avlnode__sub_tree),\
    UT_CASE_BEGIN(_avl_tree_rebalance, test___avl_tree_rebalance__null),\
    UT_CASE(test__avl_tree_rebalance__ll),\
    UT_CASE(test__avl_tree_rebalance__lr),\
    UT_CASE(test__avl_tree_rebalance__rr),\
    UT_CASE(test__avl_tree_rebalance__rl),\
    UT_CASE(test__avl_tree_rebalance__no_rotate),\
    UT_CASE_BEGIN(_avl_tree_init_elem_auxiliary, test__avl_tree_init_elem_auxiliary__null_avl_tree),\
    UT_CASE(test__avl_tree_init_elem_auxiliary__null_node),\
    UT_CASE(test__avl_tree_init_elem_auxiliary__non_inited),\
    UT_CASE(test__avl_tree_init_elem_auxiliary__c_builtin),\
    UT_CASE(test__avl_tree_init_elem_auxiliary__cstr),\
    UT_CASE(test__avl_tree_init_elem_auxiliary__cstl_builtin),\
    UT_CASE(test__avl_tree_init_elem_auxiliary__user_define),\
    UT_CASE_BEGIN(_avl_tree_elem_compare_auxiliary, test__avl_tree_elem_compare_auxiliary__null_avl_tree),\
    UT_CASE(test__avl_tree_elem_compare_auxiliary__null_first),\
    UT_CASE(test__avl_tree_elem_compare_auxiliary__null_second),\
    UT_CASE(test__avl_tree_elem_compare_auxiliary__null_output),\
    UT_CASE(test__avl_tree_elem_compare_auxiliary__non_inited),\
    UT_CASE(test__avl_tree_elem_compare_auxiliary__int),\
    UT_CASE(test__avl_tree_elem_compare_auxiliary__cstr)

#endif /* _UT_CSTL_AVL_TREE_AUX_H_ */

