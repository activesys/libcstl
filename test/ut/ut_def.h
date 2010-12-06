#ifndef _UT_DEF_H_
#define _UT_DEF_H_

#define UT_SUIT_SEPARATOR_OPEN  printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< ")
#define UT_SUIT_SEPARATOR_CLOSE printf(" >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n")
#define UT_CASE_SEPARATOR_OPEN  printf("-------------------------------- ")
#define UT_CASE_SEPARATOR_CLOSE printf(" --------------------------------\n")

#define UT_SUIT_DECLARATION(suit)\
    void test_suit_##suit##_setup(void** state);\
    void test_suit_##suit##_teardown(void** state);
#define UT_SUIT_DEFINATION(suit, first_case_name)\
    void test_suit_##suit##_setup(void** state)\
    {UT_SUIT_SEPARATOR_OPEN;printf("test " #suit ".c");UT_SUIT_SEPARATOR_CLOSE;\
     UT_CASE_SEPARATOR_OPEN;printf("test " #first_case_name);UT_CASE_SEPARATOR_CLOSE;}\
    void test_suit_##suit##_teardown(void** state){printf("\n");}
#define UT_SUIT_BEGIN(suit, test_case)\
    unit_test_setup_teardown(test_case, test_suit_##suit##_setup, test_suit_##suit##_teardown)

#define UT_CASE_DECLARATION(case_name)\
    void test_case_##case_name##_setup(void** state);\
    void test_case_##case_name##_teardown(void** state);
#define UT_CASE_DEFINATION(case_name)\
    void test_case_##case_name##_setup(void** state)\
    {UT_CASE_SEPARATOR_OPEN;printf("test " #case_name);UT_CASE_SEPARATOR_CLOSE;}\
    void test_case_##case_name##_teardown(void** state){printf("\n");}
#define UT_CASE_BEGIN(case_name, test_case)\
    unit_test_setup_teardown(test_case, test_case_##case_name##_setup, test_case_##case_name##_teardown)

#define UT_CASE(test_case)\
    unit_test_setup_teardown(test_case, test_case_setup, test_case_teardown)

void test_case_setup(void** state);
void test_case_teardown(void** state);

#endif /* _UT_DEF_H_ */

