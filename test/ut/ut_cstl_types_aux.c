#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/cstl_alloc.h"
#include "cstl/cstl_types.h"
#include "cstl/cstring.h"
#include "cstl/clist.h"
#include "cstl/cslist.h"
#include "cstl/cdeque.h"
#include "cstl/cstack.h"
#include "cstl/cqueue.h"
#include "cstl/cset.h"
#include "cstl/cmap.h"
#include "cstl/chash_set.h"
#include "cstl/chash_map.h"
#include "cstl_types_builtin.h"
#include "cstl_types_aux.h"

#include "ut_def.h"
#include "ut_cstl_types_aux.h"

UT_SUIT_DEFINATION(cstl_types_aux, _type_hash)

/*
 * test _type_hash
 */
UT_CASE_DEFINATION(_type_hash)
void test__type_hash__null_typename(void** state)
{
    expect_assert_failure(_type_hash(NULL));
}

void test__type_hash__null_empty(void** state)
{
    assert_true(_type_hash("") == 0);
}

void test__type_hash__lessthan_bucketcount(void** state)
{
    assert_true(_type_hash("0") == 48);
}

#define TEST__TYPE_REGISTER_BEGIN()\
    _typenode_t* pt_node = NULL;\
    _type_t*     pt_type = NULL;\
    size_t       t_pos = 0
#define TEST__TYPE_REGISTER_TYPE(type, type_text, type_suffix, type_style)\
    do{\
        t_pos = _type_hash(type_text);\
        pt_node = _gt_typeregister._apt_bucket[t_pos];\
        while (pt_node != NULL) {\
            if (strncmp(pt_node->_s_typename, type_text, _TYPE_NAME_SIZE) == 0) {\
                break;\
            }\
            pt_node = pt_node->_pt_next;\
        }\
        assert_true(pt_node != NULL);\
        pt_type = pt_node->_pt_type;\
        assert_true(pt_type != NULL);\
        assert_true(pt_type->_t_typesize == sizeof(type));\
        assert_true(strncmp(pt_type->_s_typename, type_text, _TYPE_NAME_SIZE) == 0);\
        assert_true(pt_type->_t_style != _TYPE_INVALID);\
        assert_true(pt_type->_t_style == type_style);\
        assert_true(pt_type->_t_typeinit == _type_init_##type_suffix);\
        assert_true(pt_type->_t_typeless == _type_less_##type_suffix);\
        assert_true(pt_type->_t_typecopy == _type_copy_##type_suffix);\
        assert_true(pt_type->_t_typedestroy == _type_destroy_##type_suffix);\
    }while(false)
#define TEST__TYPE_REGISTER_TYPE_NODE(type, type_text)\
    do{\
        t_pos = _type_hash(type_text);\
        pt_node = _gt_typeregister._apt_bucket[t_pos];\
        while (pt_node != NULL) {\
            if (strncmp(pt_node->_s_typename, type_text, _TYPE_NAME_SIZE) == 0) {\
                break;\
            }\
            pt_node->_pt_next;\
        }\
        assert_true(pt_node != NULL);\
        assert_true(pt_node->_pt_type == pt_type);\
    }while(false)
#define TEST__TYPE_REGISTER_END()

/*
 * test _type_register_c_builtin
 */
UT_CASE_DEFINATION(_type_register_c_builtin)
void test__type_register_c_builtin__all(void** state)
{
    TEST__TYPE_REGISTER_BEGIN();
    /*
    _typenode_t* pt_node = NULL;
    _type_t*     pt_type = NULL;
    size_t       t_pos = 0;
    */

    _type_register_c_builtin();

    /* char */
    TEST__TYPE_REGISTER_TYPE(char, _CHAR_TYPE, char, _TYPE_C_BUILTIN);
    TEST__TYPE_REGISTER_TYPE_NODE(char, _CHAR_TYPE);
    /* unsigned char */
    TEST__TYPE_REGISTER_TYPE(unsigned char, _UNSIGNED_CHAR_TYPE, uchar, _TYPE_C_BUILTIN);
    /* short */
    TEST__TYPE_REGISTER_TYPE(short, _SHORT_TYPE, short, _TYPE_C_BUILTIN);
    TEST__TYPE_REGISTER_TYPE_NODE(short int, _SHORT_INT_TYPE);
    TEST__TYPE_REGISTER_TYPE_NODE(signed short, _SIGNED_SHORT_TYPE);
    TEST__TYPE_REGISTER_TYPE_NODE(signed short int, _SIGNED_SHORT_INT_TYPE);
    /* unsigned short */
    TEST__TYPE_REGISTER_TYPE(unsigned short, _UNSIGNED_SHORT_TYPE, ushort, _TYPE_C_BUILTIN);
    TEST__TYPE_REGISTER_TYPE_NODE(unsigned short int, _UNSIGNED_SHORT_INT_TYPE);
    /* int */
    TEST__TYPE_REGISTER_TYPE(int, _INT_TYPE, int, _TYPE_C_BUILTIN);
    TEST__TYPE_REGISTER_TYPE_NODE(signed, _SIGNED_TYPE);
    TEST__TYPE_REGISTER_TYPE_NODE(signed int, _SIGNED_INT_TYPE);
    /* unsigned int */
    TEST__TYPE_REGISTER_TYPE(unsigned int, _UNSIGNED_INT_TYPE, uint, _TYPE_C_BUILTIN);
    TEST__TYPE_REGISTER_TYPE_NODE(signed, _UNSIGNED_TYPE);
    /* long */
    TEST__TYPE_REGISTER_TYPE(long, _LONG_TYPE, long, _TYPE_C_BUILTIN);
    TEST__TYPE_REGISTER_TYPE_NODE(long int, _LONG_INT_TYPE);
    TEST__TYPE_REGISTER_TYPE_NODE(signed long, _SIGNED_LONG_TYPE);
    TEST__TYPE_REGISTER_TYPE_NODE(signed long int, _SIGNED_LONG_INT_TYPE);
    /* unsigned long */
    TEST__TYPE_REGISTER_TYPE(unsigned long, _UNSIGNED_LONG_TYPE, ulong, _TYPE_C_BUILTIN);
    TEST__TYPE_REGISTER_TYPE_NODE(unsigned long int, _UNSIGNED_LONG_INT_TYPE);
    /* float */
    TEST__TYPE_REGISTER_TYPE(float, _FLOAT_TYPE, float, _TYPE_C_BUILTIN);
    /* double */
    TEST__TYPE_REGISTER_TYPE(double, _DOUBLE_TYPE, double, _TYPE_C_BUILTIN);
    /* long double */
    TEST__TYPE_REGISTER_TYPE(long double, _LONG_DOUBLE_TYPE, long_double, _TYPE_C_BUILTIN);
    /* bool_t */
    TEST__TYPE_REGISTER_TYPE(bool_t, _CSTL_BOOL_TYPE, cstl_bool, _TYPE_C_BUILTIN);
    /* char* */
    TEST__TYPE_REGISTER_TYPE(string_t, _C_STRING_TYPE, cstr, _TYPE_C_BUILTIN);
    /* void* */
    TEST__TYPE_REGISTER_TYPE(void*, _POINTER_TYPE, pointer, _TYPE_C_BUILTIN);
#ifndef _MSC_VER
    /* _Bool */
    TEST__TYPE_REGISTER_TYPE(_Bool, _BOOL_TYPE, bool, _TYPE_C_BUILTIN);
#endif

    TEST__TYPE_REGISTER_END();
}

/*
 * test _type_register_cstl_builtin
 */
UT_CASE_DEFINATION(_type_register_cstl_builtin)
void test__type_register_cstl_builtin__all(void** state)
{
    TEST__TYPE_REGISTER_BEGIN();

    _type_register_cstl_builtin();

    /* vector_t */
    TEST__TYPE_REGISTER_TYPE(vector_t, _VECTOR_TYPE, vector, _TYPE_CSTL_BUILTIN);
    /* list_t */
    TEST__TYPE_REGISTER_TYPE(list_t, _LIST_TYPE, list, _TYPE_CSTL_BUILTIN);
    /* slist_t */
    TEST__TYPE_REGISTER_TYPE(slist_t, _SLIST_TYPE, slist, _TYPE_CSTL_BUILTIN);
    /* deque_t */
    TEST__TYPE_REGISTER_TYPE(deque_t, _DEQUE_TYPE, deque, _TYPE_CSTL_BUILTIN);
    /* stack_t */
    TEST__TYPE_REGISTER_TYPE(stack_t, _STACK_TYPE, stack, _TYPE_CSTL_BUILTIN);
    /* queue_t */
    TEST__TYPE_REGISTER_TYPE(queue_t, _QUEUE_TYPE, queue, _TYPE_CSTL_BUILTIN);
    /* priority_queue_t */
    TEST__TYPE_REGISTER_TYPE(priority_queue_t, _PRIORITY_QUEUE_TYPE, priority_queue, _TYPE_CSTL_BUILTIN);
    /* set_t */
    TEST__TYPE_REGISTER_TYPE(set_t, _SET_TYPE, set, _TYPE_CSTL_BUILTIN);
    /* map_t */
    TEST__TYPE_REGISTER_TYPE(map_t, _MAP_TYPE, map, _TYPE_CSTL_BUILTIN);
    /* multiset_t */
    TEST__TYPE_REGISTER_TYPE(multiset_t, _MULTISET_TYPE, multiset, _TYPE_CSTL_BUILTIN);
    /* multimap_t */
    TEST__TYPE_REGISTER_TYPE(multimap_t, _MULTIMAP_TYPE, multimap, _TYPE_CSTL_BUILTIN);
    /* hash_set_t */
    TEST__TYPE_REGISTER_TYPE(hash_set_t, _HASH_SET_TYPE, hash_set, _TYPE_CSTL_BUILTIN);
    /* hash_map_t */
    TEST__TYPE_REGISTER_TYPE(hash_map_t, _HASH_MAP_TYPE, hash_map, _TYPE_CSTL_BUILTIN);
    /* hash_multiset_t */
    TEST__TYPE_REGISTER_TYPE(hash_multiset_t, _HASH_MULTISET_TYPE, hash_multiset, _TYPE_CSTL_BUILTIN);
    /* hash_multimap_t */
    TEST__TYPE_REGISTER_TYPE(hash_multimap_t, _HASH_MULTIMAP_TYPE, hash_multimap, _TYPE_CSTL_BUILTIN);
    /* pair_t */
    TEST__TYPE_REGISTER_TYPE(pair_t, _PAIR_TYPE, pair, _TYPE_CSTL_BUILTIN);
    /* string_t */
    TEST__TYPE_REGISTER_TYPE(string_t, _STRING_TYPE, string, _TYPE_CSTL_BUILTIN);
    /* range_t */
    TEST__TYPE_REGISTER_TYPE(range_t, _RANGE_TYPE, range, _TYPE_CSTL_BUILTIN);
    /* basic_string_t */
    TEST__TYPE_REGISTER_TYPE(basic_string_t, _BASIC_STRING_TYPE, basic_string, _TYPE_CSTL_BUILTIN);

    /* iterator_t */
    TEST__TYPE_REGISTER_TYPE(iterator_t, _ITERATOR_TYPE, iterator, _TYPE_CSTL_BUILTIN);
    TEST__TYPE_REGISTER_TYPE_NODE(vector_iterator_t, _VECTOR_ITERATOR_TYPE);
    TEST__TYPE_REGISTER_TYPE_NODE(list_iterator_t, _LIST_ITERATOR_TYPE);
    TEST__TYPE_REGISTER_TYPE_NODE(slist_iterator_t, _SLIST_ITERATOR_TYPE);
    TEST__TYPE_REGISTER_TYPE_NODE(deque_iterator_t, _DEQUE_ITERATOR_TYPE);
    TEST__TYPE_REGISTER_TYPE_NODE(set_iterator_t, _SET_ITERATOR_TYPE);
    TEST__TYPE_REGISTER_TYPE_NODE(map_iterator_t, _MAP_ITERATOR_TYPE);
    TEST__TYPE_REGISTER_TYPE_NODE(multiset_iterator_t, _MULTISET_ITERATOR_TYPE);
    TEST__TYPE_REGISTER_TYPE_NODE(multimap_iterator_t, _MULTIMAP_ITERATOR_TYPE);
    TEST__TYPE_REGISTER_TYPE_NODE(hash_set_iterator_t, _HASH_SET_ITERATOR_TYPE);
    TEST__TYPE_REGISTER_TYPE_NODE(hash_map_iterator_t, _HASH_MAP_ITERATOR_TYPE);
    TEST__TYPE_REGISTER_TYPE_NODE(hash_multiset_iterator_t, _HASH_MULTISET_ITERATOR_TYPE);
    TEST__TYPE_REGISTER_TYPE_NODE(hash_multimap_iterator_t, _HASH_MULTIMAP_ITERATOR_TYPE);
    TEST__TYPE_REGISTER_TYPE_NODE(string_iterator_t, _STRING_ITERATOR_TYPE);
    TEST__TYPE_REGISTER_TYPE_NODE(input_iterator_t, _INPUT_ITERATOR_TYPE);
    TEST__TYPE_REGISTER_TYPE_NODE(output_iterator_t, _OUTPUT_ITERATOR_TYPE);
    TEST__TYPE_REGISTER_TYPE_NODE(forward_iterator_t, _FORWARD_ITERATOR_TYPE);
    TEST__TYPE_REGISTER_TYPE_NODE(bidirectional_iterator_t, _BIDIRECTIONAL_ITERATOR_TYPE);
    TEST__TYPE_REGISTER_TYPE_NODE(random_access_iterator_t, _RANDOM_ACCESS_ITERATOR_TYPE);

    TEST__TYPE_REGISTER_END();
}

/*
 * test _type_init
 */
UT_CASE_DEFINATION(_type_init)
void test__type_init__all(void** state)
{
    typedef struct _tag_test_type_init {
        int a;
    } _test_type_init_t;
    type_register(_test_type_init_t, NULL, NULL, NULL, NULL);
    assert_true(_gt_typeregister._t_isinit == true);
    test__type_register_c_builtin__all(state);
    test__type_register_cstl_builtin__all(state);
}

/*
 * test _type_is_registered
 */
UT_CASE_DEFINATION(_type_is_registered)
void test__type_is_registered__null_typename(void** state)
{
    expect_assert_failure(_type_is_registered(NULL));
}

void test__type_is_registered__long_typename(void** state)
{
    expect_assert_failure(_type_is_registered("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"));
}

void test__type_is_registered__not_register(void** state)
{
    assert_true(_type_is_registered("abcdefghijklmnopqrstuvwxyz") == NULL);
}

void test__type_is_registered__register(void** state)
{
    _type_t* pt_type = _type_is_registered("int");
    assert_true(pt_type != NULL);
    assert_true(pt_type->_t_typesize == sizeof(int));
    assert_true(strncmp(pt_type->_s_typename, "int", _TYPE_NAME_SIZE) == 0);
    assert_true(pt_type->_t_typeinit == _type_init_int);
    assert_true(pt_type->_t_typeless == _type_less_int);
    assert_true(pt_type->_t_typecopy == _type_copy_int);
    assert_true(pt_type->_t_typedestroy == _type_destroy_int);
}

/*
 * test _type_cache_find
 */
UT_CASE_DEFINATION(_type_cache_find)
void test__type_cache_find__typename_null(void** state)
{
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    expect_assert_failure(_type_cache_find(NULL, s_formalname));
}

void test__type_cache_find__formalname_null(void** state)
{
    char s_typename[_TYPE_NAME_SIZE + 1] = {'\0'};
    expect_assert_failure(_type_cache_find(s_typename, NULL));
}

void test__type_cache_find__not_find_empty(void** state)
{
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};

    _gt_typecache_index = 0;
    memset(_gt_typecache, 0x00, sizeof(_typecache_t) * _TYPE_CACHE_COUNT);
    assert_true(_type_cache_find("vector_t<int>", s_formalname) == _TYPE_INVALID);
}

void test__type_cache_find__not_find(void** state)
{
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};

    _gt_typecache_index = 0;
    memset(_gt_typecache, 0x00, sizeof(_typecache_t) * _TYPE_CACHE_COUNT);
    _type_cache_update("vector_t <int  >", "vector_t<int>", _TYPE_CSTL_BUILTIN);
    _type_cache_update("vector_t<  int>", "vector_t<int>", _TYPE_CSTL_BUILTIN);
    _type_cache_update("int", "int", _TYPE_C_BUILTIN);
    _type_cache_update("abc_t", "abc_t", _TYPE_USER_DEFINE);

    assert_true(_type_cache_find("vector_t < int >", s_formalname) == _TYPE_INVALID);
    assert_true(strlen(s_formalname) == 0);
}

void test__type_cache_find__find(void** state)
{
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};

    _gt_typecache_index = 0;
    memset(_gt_typecache, 0x00, sizeof(_typecache_t) * _TYPE_CACHE_COUNT);
    _type_cache_update("vector_t <int  >", "vector_t<int>", _TYPE_CSTL_BUILTIN);
    _type_cache_update("vector_t<  int>", "vector_t<int>", _TYPE_CSTL_BUILTIN);
    _type_cache_update("int", "int", _TYPE_C_BUILTIN);
    _type_cache_update("abc_t", "abc_t", _TYPE_USER_DEFINE);

    assert_true(_type_cache_find("vector_t <int  >", s_formalname) == _TYPE_CSTL_BUILTIN);
    assert_true(strncmp(s_formalname, "vector_t<int>", _TYPE_NAME_SIZE) == 0);
}

/*
 * test _type_cache_update
 */
UT_CASE_DEFINATION(_type_cache_update)
void test__type_cache_update__typename_null(void** state)
{
    expect_assert_failure(_type_cache_update(NULL, "int", _TYPE_C_BUILTIN));
}

void test__type_cache_update__formalname_null(void** state)
{
    expect_assert_failure(_type_cache_update("int", NULL, _TYPE_C_BUILTIN));
}

void test__type_cache_update__invalid_style(void** state)
{
    expect_assert_failure(_type_cache_update("int", "int", _TYPE_INVALID));
}

void test__type_cache_update__empty(void** state)
{
    _gt_typecache_index = 0;
    memset(_gt_typecache, 0x00, sizeof(_typecache_t) * _TYPE_CACHE_COUNT);

    _type_cache_update("vector_t <int  >", "vector_t<int>", _TYPE_CSTL_BUILTIN);
    _type_cache_update("vector_t<  int>", "vector_t<int>", _TYPE_CSTL_BUILTIN);
    _type_cache_update("int", "int", _TYPE_C_BUILTIN);
    _type_cache_update("abc_t", "abc_t", _TYPE_USER_DEFINE);

    assert_true(strncmp(_gt_typecache[0]._s_typename, "vector_t <int  >", _TYPE_NAME_SIZE) == 0);
    assert_true(strncmp(_gt_typecache[0]._s_formalname, "vector_t<int>", _TYPE_NAME_SIZE) == 0);
    assert_true(_gt_typecache[0]._t_style == _TYPE_CSTL_BUILTIN);
    assert_true(strncmp(_gt_typecache[1]._s_typename, "vector_t<  int>", _TYPE_NAME_SIZE) == 0);
    assert_true(strncmp(_gt_typecache[1]._s_formalname, "vector_t<int>", _TYPE_NAME_SIZE) == 0);
    assert_true(_gt_typecache[1]._t_style == _TYPE_CSTL_BUILTIN);
    assert_true(strncmp(_gt_typecache[2]._s_typename, "int", _TYPE_NAME_SIZE) == 0);
    assert_true(strncmp(_gt_typecache[2]._s_formalname, "int", _TYPE_NAME_SIZE) == 0);
    assert_true(_gt_typecache[2]._t_style == _TYPE_C_BUILTIN);
    assert_true(strncmp(_gt_typecache[3]._s_typename, "abc_t", _TYPE_NAME_SIZE) == 0);
    assert_true(strncmp(_gt_typecache[3]._s_formalname, "abc_t", _TYPE_NAME_SIZE) == 0);
    assert_true(_gt_typecache[3]._t_style == _TYPE_USER_DEFINE);
    assert_true(_gt_typecache_index == 4);
}

void test__type_cache_update__not_empty(void** state)
{
    _gt_typecache_index = 0;
    memset(_gt_typecache, 0x00, sizeof(_typecache_t) * _TYPE_CACHE_COUNT);
    _type_cache_update("vector_t <int  >", "vector_t<int>", _TYPE_CSTL_BUILTIN);
    _type_cache_update("vector_t<  int>", "vector_t<int>", _TYPE_CSTL_BUILTIN);
    _type_cache_update("int", "int", _TYPE_C_BUILTIN);
    _type_cache_update("abc_t", "abc_t", _TYPE_USER_DEFINE);

    assert_true(_gt_typecache_index == 4);
    _type_cache_update("deque_t<   map_t<int, long long int>>", "deque_t<map_t<int,long long int>>", _TYPE_CSTL_BUILTIN);
    _type_cache_update("basic_string_iterator_t", "basic_string_iterator_t", _TYPE_CSTL_BUILTIN);
    _type_cache_update("_Bool", "_Bool", _TYPE_C_BUILTIN);
    _type_cache_update("bool_t", "bool_t", _TYPE_C_BUILTIN);

    assert_true(strncmp(_gt_typecache[4]._s_typename, "deque_t<   map_t<int, long long int>>", _TYPE_NAME_SIZE) == 0);
    assert_true(strncmp(_gt_typecache[4]._s_formalname, "deque_t<map_t<int,long long int>>", _TYPE_NAME_SIZE) == 0);
    assert_true(_gt_typecache[4]._t_style == _TYPE_CSTL_BUILTIN);
    assert_true(strncmp(_gt_typecache[5]._s_typename, "basic_string_iterator_t", _TYPE_NAME_SIZE) == 0);
    assert_true(strncmp(_gt_typecache[5]._s_formalname, "basic_string_iterator_t", _TYPE_NAME_SIZE) == 0);
    assert_true(_gt_typecache[5]._t_style == _TYPE_CSTL_BUILTIN);
    assert_true(strncmp(_gt_typecache[6]._s_typename, "_Bool", _TYPE_NAME_SIZE) == 0);
    assert_true(strncmp(_gt_typecache[6]._s_formalname, "_Bool", _TYPE_NAME_SIZE) == 0);
    assert_true(_gt_typecache[6]._t_style == _TYPE_C_BUILTIN);
    assert_true(strncmp(_gt_typecache[7]._s_typename, "bool_t", _TYPE_NAME_SIZE) == 0);
    assert_true(strncmp(_gt_typecache[7]._s_formalname, "bool_t", _TYPE_NAME_SIZE) == 0);
    assert_true(_gt_typecache[7]._t_style == _TYPE_C_BUILTIN);
    assert_true(_gt_typecache_index == 8);
}

void test__type_cache_update__round(void** state)
{
    char s_name[_TYPE_NAME_SIZE + 1] = {'\0'};
    size_t i = 0;

    _gt_typecache_index = 0;
    memset(_gt_typecache, 0x00, sizeof(_typecache_t) * _TYPE_CACHE_COUNT);
    for (i = 0; i < 300; ++i) {
        memset(s_name, '\0', _TYPE_NAME_SIZE);
        sprintf(s_name, "abc_%u_t", i);
        _type_cache_update(s_name, s_name, _TYPE_USER_DEFINE);
    }

    assert_true(strncmp(_gt_typecache[0]._s_typename, "abc_256_t", _TYPE_NAME_SIZE) == 0);
    assert_true(strncmp(_gt_typecache[0]._s_formalname, "abc_256_t", _TYPE_NAME_SIZE) == 0);
    assert_true(_gt_typecache[0]._t_style == _TYPE_USER_DEFINE);
    assert_true(_gt_typecache_index == 44);
}

