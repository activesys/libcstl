#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/cstl_alloc.h"
#include "cstl/cstl_types.h"
#include "cstl/cstl_iterator.h"
#include "cstl/cvector.h"
#include "cstl/cstl_hashtable_iterator.h"
#include "cstl/cstl_hashtable_private.h"
/*#include "cstl/cstl_hashtable.h"*/
#include "cstl_hashtable_aux.h"
#include "cstl/cstring.h"

#include "ut_def.h"
#include "ut_cstl_hashtable_aux.h"

UT_SUIT_DEFINATION(cstl_hashtable_aux, _hashtable_is_created)
/*
 * test _hashtable_is_created
 */
UT_CASE_DEFINATION(_hashtable_is_created)
void test__hashtable_is_created__null_hashtable(void** state)
{
    expect_assert_failure(_hashtable_is_created(NULL));
}

void test__hashtable_is_created__non_inited_allocator(void** state)
{
    _hashtable_t htable;

    type_register(_hashnode_t*, NULL, NULL, NULL, NULL);

    _create_vector_auxiliary(&htable._t_bucket, _HASHTABLE_NODE_NAME);
    htable._t_nodecount = 0;
    htable._t_hash = NULL;
    htable._t_compare = NULL;
    htable._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    htable._t_typeinfo._pt_type = (_type_t*)0x999;
    _alloc_init(&htable._t_allocator);
    htable._t_allocator._t_mempoolsize = 1;
    assert_false(_hashtable_is_created(&htable));
    htable._t_allocator._t_mempoolsize = 0;
    _alloc_destroy(&htable._t_allocator);
}

void test__hashtable_is_created__invalid_rbroot_bucket(void** state)
{
    _hashtable_t htable;

    htable._t_nodecount = 0;
    htable._t_hash = NULL;
    htable._t_compare = NULL;
    htable._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    htable._t_typeinfo._pt_type = (_type_t*)0x999;
    _alloc_init(&htable._t_allocator);
    assert_false(_hashtable_is_created(&htable));
    _alloc_destroy(&htable._t_allocator);
}

void test__hashtable_is_created__invalid_rbroot_hash(void** state)
{
    _hashtable_t htable;

    _create_vector_auxiliary(&htable._t_bucket, _HASHTABLE_NODE_NAME);
    htable._t_hash = (unary_function_t)0xabc;
    htable._t_compare = NULL;
    htable._t_nodecount = 0;
    htable._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    htable._t_typeinfo._pt_type = (_type_t*)0x999;
    _alloc_init(&htable._t_allocator);
    assert_false(_hashtable_is_created(&htable));
    _alloc_destroy(&htable._t_allocator);
}

void test__hashtable_is_created__invalid_compare(void** state)
{
    _hashtable_t htable;

    _create_vector_auxiliary(&htable._t_bucket, _HASHTABLE_NODE_NAME);
    htable._t_hash = NULL;
    htable._t_compare = (binary_function_t)0x888;
    htable._t_nodecount = 0;
    htable._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    htable._t_typeinfo._pt_type = (_type_t*)0x999;
    _alloc_init(&htable._t_allocator);
    assert_false(_hashtable_is_created(&htable));
    _alloc_destroy(&htable._t_allocator);
}

void test__hashtable_is_created__invalid_nodecount(void** state)
{
    _hashtable_t htable;

    _create_vector_auxiliary(&htable._t_bucket, _HASHTABLE_NODE_NAME);
    htable._t_hash = NULL;
    htable._t_compare = NULL;
    htable._t_nodecount = 9;
    htable._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    htable._t_typeinfo._pt_type = (_type_t*)0x999;
    _alloc_init(&htable._t_allocator);
    assert_false(_hashtable_is_created(&htable));
    _alloc_destroy(&htable._t_allocator);
}

void test__hashtable_is_created__invalid_typeinfo_style(void** state)
{
    _hashtable_t htable;

    _create_vector_auxiliary(&htable._t_bucket, _HASHTABLE_NODE_NAME);
    htable._t_hash = NULL;
    htable._t_compare = NULL;
    htable._t_nodecount = 0;
    htable._t_typeinfo._t_style = 90;
    htable._t_typeinfo._pt_type = (_type_t*)0x999;
    _alloc_init(&htable._t_allocator);
    assert_false(_hashtable_is_created(&htable));
    _alloc_destroy(&htable._t_allocator);
}

void test__hashtable_is_created__invalid_typeinfo_type(void** state)
{
    _hashtable_t htable;

    _create_vector_auxiliary(&htable._t_bucket, _HASHTABLE_NODE_NAME);
    htable._t_hash = NULL;
    htable._t_compare = NULL;
    htable._t_nodecount = 0;
    htable._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    htable._t_typeinfo._pt_type = NULL;
    _alloc_init(&htable._t_allocator);
    assert_false(_hashtable_is_created(&htable));
    _alloc_destroy(&htable._t_allocator);
}

void test__hashtable_is_created__created(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");

    assert_true(_hashtable_is_created(pt_hashtable));

    _hashtable_destroy(pt_hashtable);
}

/*
 * test _hashtable_is_inited
 */
/*
UT_CASE_DEFINATION(_hashtable_is_inited)
void test__hashtable_is_inited__null_hashtable(void** state)
{
    expect_assert_failure(_hashtable_is_inited(NULL));
}

void test__hashtable_is_inited__invalid_typeinfo_style(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");

    _hashtable_init(pt_hashtable, NULL);

    pt_hashtable->_t_typeinfo._t_style = 999;
    assert_false(_hashtable_is_inited(pt_hashtable));
    pt_hashtable->_t_typeinfo._t_style = _TYPE_C_BUILTIN;

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_is_inited__invalid_typeinfo_type(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _type_t* pt_type = NULL;

    _hashtable_init(pt_hashtable, NULL);

    pt_type = pt_hashtable->_t_typeinfo._pt_type;
    pt_hashtable->_t_typeinfo._pt_type = NULL;
    assert_false(_hashtable_is_inited(pt_hashtable));
    pt_hashtable->_t_typeinfo._pt_type = pt_type;

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_is_inited__invalid_rbroot_left(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _rbnode_t* pt_rb_node = NULL;

    _hashtable_init(pt_hashtable, NULL);

    pt_rb_node = pt_hashtable->_t_rbroot._pt_left;
    pt_hashtable->_t_rbroot._pt_left = NULL;
    assert_false(_hashtable_is_inited(pt_hashtable));
    pt_hashtable->_t_rbroot._pt_left = pt_rb_node;

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_is_inited__invalid_rbroot_right(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _rbnode_t* pt_rb_node = NULL;

    _hashtable_init(pt_hashtable, NULL);

    pt_rb_node = pt_hashtable->_t_rbroot._pt_right;
    pt_hashtable->_t_rbroot._pt_right = NULL;
    assert_false(_hashtable_is_inited(pt_hashtable));
    pt_hashtable->_t_rbroot._pt_right = pt_rb_node;

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_is_inited__invalid_rbroot_color(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");

    _hashtable_init(pt_hashtable, NULL);

    pt_hashtable->_t_rbroot._t_color = BLACK;
    assert_false(_hashtable_is_inited(pt_hashtable));
    pt_hashtable->_t_rbroot._t_color = RED;

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_is_inited__invalid_compare(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    binary_function_t t_compare = NULL;

    _hashtable_init(pt_hashtable, NULL);

    t_compare = pt_hashtable->_t_compare;
    pt_hashtable->_t_compare = NULL;
    assert_false(_hashtable_is_inited(pt_hashtable));
    pt_hashtable->_t_compare = t_compare;

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_is_inited__inited(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");

    _hashtable_init(pt_hashtable, NULL);

    assert_true(_hashtable_is_inited(pt_hashtable));

    _hashtable_destroy(pt_hashtable);
}
*/

