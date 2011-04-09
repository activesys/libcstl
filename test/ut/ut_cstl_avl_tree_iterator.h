#ifndef _UT_CSTL_AVL_TREE_ITERATOR_H_
#define _UT_CSTL_AVL_TREE_ITERATOR_H_

UT_SUIT_DECLARATION(cstl_avl_tree_iterator)
/*
 * test _create_avl_tree_iterator
 */
UT_CASE_DECLARATION(_create_avl_tree_iterator)
void test__create_avl_tree_iterator__successfully(void** state);

#define UT_CSTL_AVL_TREE_ITERATOR_CASE\
    UT_SUIT_BEGIN(cstl_avl_tree_iterator, test__create_avl_tree_iterator__successfully),\

#endif /* _UT_CSTL_AVL_TREE_ITERATOR_H_ */

