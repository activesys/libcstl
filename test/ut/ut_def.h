#ifndef _UT_DEF_H_
#define _UT_DEF_H_

#define UT_CASE_SEPARATOR_OPEN  printf("\n\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< ")
#define UT_CASE_SEPARATOR_CLOSE printf(" >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n")
#define UT_ITEM_SEPARATOR_OPEN  printf("-------------------------------- ")
#define UT_ITEM_SEPARATOR_CLOSE printf(" --------------------------------\n")
#define UT_ITEM_SEPARATOR_START printf("\n--------------------------------------------------------------------------------\n")

#define UT_CASE_DECLARATION(name)\
    void test_case_##name##_start(void** state);\
    void test_case_##name##_stop(void** state);\
    void test_case_##name##_entity(void** state);
#define UT_CASE_DEFINATION(name)\
    void test_case_##name##_start(void** state)\
    {UT_CASE_SEPARATOR_OPEN;printf("test " #name ".c");UT_CASE_SEPARATOR_CLOSE;}\
    void test_case_##name##_stop(void** state){}\
    void test_case_##name##_entity(void** state){}
#define UT_CASE(name)\
    unit_test_setup_teardown(test_case_##name##_entity, test_case_##name##_start, test_case_##name##_stop)

#define UT_ITEM_DECLARATION(name)\
    void test_item_##name##_start(void** state);\
    void test_item_##name##_stop(void** state);\
    void test_item_##name##_entity(void** state);
#define UT_ITEM_DEFINATION(name)\
    void test_item_##name##_start(void** state){UT_ITEM_SEPARATOR_START;}\
    void test_item_##name##_stop(void** state)\
    {UT_ITEM_SEPARATOR_OPEN;printf("test " #name);UT_ITEM_SEPARATOR_CLOSE;}\
    void test_item_##name##_entity(void** state){}
#define UT_ITEM(name)\
    unit_test_setup_teardown(test_item_##name##_entity, test_item_##name##_start, test_item_##name##_stop)

#endif /* _UT_DEF_H_ */

