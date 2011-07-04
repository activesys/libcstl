#ifndef _UT_CSTL_SET_ITERATOR_H_
#define _UT_CSTL_SET_ITERATOR_H_

UT_SUIT_DECLARATION(cstl_set_iterator)
/*
 * test create_set_iterator
 */
UT_CASE_DECLARATION(create_set_iterator)
void test_create_set_iterator__successfully(void** state);

#define UT_CSTL_SET_ITERATOR_CASE\
    UT_SUIT_BEGIN(cstl_set_iterator, test_create_set_iterator__successfully),\

#endif /* _UT_CSTL_SET_ITERATOR_H_ */

