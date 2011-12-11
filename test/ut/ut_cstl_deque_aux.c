#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/citerator.h"
#include "cstl/cdeque.h"
#include "cstl/cstring.h"
#include "cstl/clist.h"
#include "cstl_deque_aux.h"
#include "cstl_vector_aux.h"

#include "ut_def.h"
#include "ut_cstl_deque_aux.h"

UT_SUIT_DEFINATION(cstl_deque_aux, _deque_is_created)

/*
 * test _deque_is_created
 */
UT_CASE_DEFINATION(_deque_is_created)
void test__deque_is_created__null_deque_container(void** state)
{
    expect_assert_failure(_deque_is_created(NULL));
}

void test__deque_is_created__non_created_invalid_start(void** state)
{
    deque_t* pdeq = create_deque(int);

    pdeq->_t_start._pt_container = (void*)0x334;
    assert_false(_deque_is_created(pdeq));

    pdeq->_t_start._pt_container = NULL;
    deque_destroy(pdeq);
}

void test__deque_is_created__non_created_invalid_finish(void** state)
{
    deque_t* pdeq = create_deque(int);

    pdeq->_t_finish._t_pos._t_dequepos._pby_afterlast = (_byte_t*)0x344;
    assert_false(_deque_is_created(pdeq));

    pdeq->_t_finish._t_pos._t_dequepos._pby_afterlast = NULL;
    deque_destroy(pdeq);
}

void test__deque_is_created__non_created_invalid_type_style(void** state)
{
    deque_t* pdeq = create_deque(int);

    pdeq->_t_typeinfo._t_style = 100;
    assert_false(_deque_is_created(pdeq));

    pdeq->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    deque_destroy(pdeq);
}

void test__deque_is_created__non_created_non_init_allocator(void** state)
{
    deque_t* pdeq = create_deque(int);

#ifdef CSTL_MEMORY_MANAGEMENT
    pdeq->_t_allocator._t_mempoolsize = 1;
    assert_false(_deque_is_created(pdeq));
    pdeq->_t_allocator._t_mempoolsize = 0;
#else
    assert_true(_deque_is_created(pdeq));
#endif

    deque_destroy(pdeq);
}

void test__deque_is_created__non_created_invalid_map(void** state)
{
    deque_t* pdeq = create_deque(int);

    pdeq->_ppby_map = (_mappointer_t)0x38745;
    assert_false(_deque_is_created(pdeq));

    pdeq->_ppby_map = NULL;
    deque_destroy(pdeq);
}

void test__deque_is_created__non_created_invalid_mapsize(void** state)
{
    deque_t* pdeq = create_deque(int);

    pdeq->_t_mapsize = 243;
    assert_false(_deque_is_created(pdeq));

    pdeq->_t_mapsize = 0;
    deque_destroy(pdeq);
}

void test__deque_is_created__created(void** state)
{
    deque_t* pdeq = create_deque(int);

    assert_true(_deque_is_created(pdeq));

    deque_destroy(pdeq);
}

/*
 * test _deque_is_inited
 */
UT_CASE_DEFINATION(_deque_is_inited)
void test__deque_is_inited__null_deque_container(void** state)
{
    expect_assert_failure(_deque_is_inited(NULL));
}

void test__deque_is_inited__invalid_type_style(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    pdeq->_t_typeinfo._t_style = 200;
    assert_false(_deque_is_inited(pdeq));

    pdeq->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    deque_destroy(pdeq);
}

void test__deque_is_inited__invalid_type_pointer(void** state)
{
    deque_t* pdeq = create_deque(int);
    void* pv_tmp = NULL;

    deque_init(pdeq);
    pv_tmp = pdeq->_t_typeinfo._pt_type;
    pdeq->_t_typeinfo._pt_type = NULL;
    assert_false(_deque_is_inited(pdeq));

    pdeq->_t_typeinfo._pt_type = pv_tmp;
    deque_destroy(pdeq);
}

void test__deque_is_inited__invalid_map(void** state)
{
    deque_t* pdeq = create_deque(int);
    void* pv_tmp = NULL;

    deque_init(pdeq);
    pv_tmp = pdeq->_ppby_map;
    pdeq->_ppby_map = NULL;
    assert_false(_deque_is_inited(pdeq));

    pdeq->_ppby_map = pv_tmp;
    deque_destroy(pdeq);
}

void test__deque_is_inited__invalid_mapsize(void** state)
{
    deque_t* pdeq = create_deque(int);
    size_t t_mapsize = 0;

    deque_init(pdeq);
    t_mapsize = pdeq->_t_mapsize;
    pdeq->_t_mapsize = 3;
    assert_false(_deque_is_inited(pdeq));

    pdeq->_t_mapsize = t_mapsize;
    deque_destroy(pdeq);
}

void test__deque_is_inited__invalid_mapsize_not_grow_count_multiple(void** state)
{
    deque_t* pdeq = create_deque(int);
    size_t t_mapsize = 0;

    deque_init(pdeq);
    t_mapsize = pdeq->_t_mapsize;
    pdeq->_t_mapsize = 33;
    assert_false(_deque_is_inited(pdeq));

    pdeq->_t_mapsize = t_mapsize;
    deque_destroy(pdeq);
}

void test__deque_is_inited__invalid_start(void** state)
{
    deque_t* pdeq = create_deque(int);
    void* pv_tmp = NULL;

    deque_init(pdeq);
    pv_tmp = pdeq->_t_start._t_pos._t_dequepos._ppby_mappos;
    pdeq->_t_start._t_pos._t_dequepos._ppby_mappos = NULL;
    assert_false(_deque_is_inited(pdeq));

    pdeq->_t_start._t_pos._t_dequepos._ppby_mappos = pv_tmp;
    deque_destroy(pdeq);
}

void test__deque_is_inited__invalid_finish(void** state)
{
    deque_t* pdeq = create_deque(int);
    void* pv_tmp = NULL;

    deque_init(pdeq);
    pv_tmp = pdeq->_t_finish._t_pos._t_dequepos._pby_corepos;
    pdeq->_t_finish._t_pos._t_dequepos._pby_corepos = (_byte_t*)0x99384;
    assert_false(_deque_is_inited(pdeq));

    pdeq->_t_finish._t_pos._t_dequepos._pby_corepos = pv_tmp;
    deque_destroy(pdeq);
}

void test__deque_is_inited__init(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    assert_true(_deque_is_inited(pdeq));

    deque_destroy(pdeq);
}

void test__deque_is_inited__init_n(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 16);
    assert_true(_deque_is_inited(pdeq));

    deque_destroy(pdeq);
}

void test__deque_is_inited__init_elem(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_elem(pdeq, 10, 100);
    assert_true(_deque_is_inited(pdeq));

    deque_destroy(pdeq);
}

/*
 * test _deque_iterator_belong_to_deque
 */
UT_CASE_DEFINATION(_deque_iterator_belong_to_deque)
void test__deque_iterator_belong_to_deque__null_container_pointer(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);

    expect_assert_failure(_deque_iterator_belong_to_deque(NULL, it_iter));

    deque_destroy(pdeq);
}

void test__deque_iterator_belong_to_deque__non_inited_deque_container(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter = _create_deque_iterator();

    expect_assert_failure(_deque_iterator_belong_to_deque(pdeq, it_iter));

    deque_destroy(pdeq);
}

void test__deque_iterator_belong_to_deque__invalid_iterator_container_type(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);
    it_iter._t_containertype = _LIST_CONTAINER;

    expect_assert_failure(_deque_iterator_belong_to_deque(pdeq, it_iter));

    deque_destroy(pdeq);
}

void test__deque_iterator_belong_to_deque__invalid_iterator_iterator_type(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);
    it_iter._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(_deque_iterator_belong_to_deque(pdeq, it_iter));

    deque_destroy(pdeq);
}

void test__deque_iterator_belong_to_deque__invalid_iterator_different_container(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);
    it_iter._pt_container = NULL;

    expect_assert_failure(_deque_iterator_belong_to_deque(pdeq, it_iter));

    deque_destroy(pdeq);
}

void test__deque_iterator_belong_to_deque__invalid_map(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);
    it_iter._t_pos._t_dequepos._ppby_mappos = (_byte_t**)0xcc;

    assert_false(_deque_iterator_belong_to_deque(pdeq, it_iter));

    deque_destroy(pdeq);
}

void test__deque_iterator_belong_to_deque__invalid_first_pos(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);
    it_iter._t_pos._t_dequepos._pby_first = (_byte_t*)0xcc;

    assert_false(_deque_iterator_belong_to_deque(pdeq, it_iter));

    deque_destroy(pdeq);
}

void test__deque_iterator_belong_to_deque__invalid_afterlast_pos(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);
    it_iter._t_pos._t_dequepos._pby_afterlast = (_byte_t*)0xcc;

    assert_false(_deque_iterator_belong_to_deque(pdeq, it_iter));

    deque_destroy(pdeq);
}

void test__deque_iterator_belong_to_deque__less_than_begin(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);
    it_iter._t_pos._t_dequepos._pby_corepos -= 10;

    assert_false(_deque_iterator_belong_to_deque(pdeq, it_iter));

    deque_destroy(pdeq);
}

void test__deque_iterator_belong_to_deque__within_deque(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);

    assert_true(_deque_iterator_belong_to_deque(pdeq, it_iter));

    deque_destroy(pdeq);
}

void test__deque_iterator_belong_to_deque__end_iterator(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_end(pdeq);

    assert_true(_deque_iterator_belong_to_deque(pdeq, it_iter));

    deque_destroy(pdeq);
}

void test__deque_iterator_belong_to_deque__greater_than_end(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_end(pdeq);
    it_iter._t_pos._t_dequepos._pby_corepos += 10;

    assert_false(_deque_iterator_belong_to_deque(pdeq, it_iter));

    deque_destroy(pdeq);
}

void test__deque_iterator_belong_to_deque__border(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 50);
    it_iter = iterator_next_n(deque_begin(pdeq), 15);
    it_iter._t_pos._t_dequepos._pby_corepos = it_iter._t_pos._t_dequepos._pby_afterlast;

    assert_false(_deque_iterator_belong_to_deque(pdeq, it_iter));

    deque_destroy(pdeq);
}

/*
 * test _deque_same_type
 */
UT_CASE_DEFINATION(_deque_same_type)
void test__deque_same_type__null_first(void** state)
{
    deque_t* pdeq = create_deque(int);

    expect_assert_failure(_deque_same_type(NULL, pdeq));

    deque_destroy(pdeq);
}

void test__deque_same_type__null_second(void** state)
{
    deque_t* pdeq = create_deque(int);

    expect_assert_failure(_deque_same_type(pdeq, NULL));

    deque_destroy(pdeq);
}

void test__deque_same_type__non_created_first(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init(pdeq_second);
    pdeq_first->_t_mapsize = 89;
    expect_assert_failure(_deque_same_type(pdeq_first, pdeq_second));

    pdeq_first->_t_mapsize = 0;
    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test__deque_same_type__non_created_second(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init(pdeq_first);
    pdeq_second->_t_mapsize = 3;
    expect_assert_failure(_deque_same_type(pdeq_first, pdeq_second));

    pdeq_second->_t_mapsize = 0;
    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test__deque_same_type__same_c_builtin(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    assert_true(_deque_same_type(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test__deque_same_type__same_c_builtin_dup(void** state)
{
    deque_t* pdeq_first = create_deque(signed long int);
    deque_t* pdeq_second = create_deque(long);
    deque_init(pdeq_first);

    assert_true(_deque_same_type(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test__deque_same_type__not_same_c_builtin(void** state)
{
    deque_t* pdeq_first = create_deque(signed long int);
    deque_t* pdeq_second = create_deque(unsigned long);
    deque_init_n(pdeq_first, 10);
    deque_init_elem(pdeq_second, 10, 100);

    assert_false(_deque_same_type(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test__deque_same_type__same_libcstl_builtin(void** state)
{
    deque_t* pdeq_first = create_deque(deque_t<int>);
    deque_t* pdeq_second = create_deque(deque_t<signed>);

    assert_true(_deque_same_type(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test__deque_same_type__same_libcstl_builtin_dup(void** state)
{
    deque_t* pdeq_first = create_deque(deque_iterator_t);
    deque_t* pdeq_second = create_deque(vector_iterator_t);

    assert_true(_deque_same_type(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test__deque_same_type__not_same_libcstl_builtin_container(void** state)
{
    deque_t* pdeq_first = create_deque(vector_t<int>);
    deque_t* pdeq_second = create_deque(deque_t<int>);

    assert_false(_deque_same_type(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test__deque_same_type__not_same_libcstl_builtin_elem(void** state)
{
    deque_t* pdeq_first = create_deque(vector_t<int>);
    deque_t* pdeq_second = create_deque(vector_t<char>);

    assert_false(_deque_same_type(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test__deque_same_type__not_same_libcstl_builtin_iter(void** state)
{
    deque_t* pdeq_first = create_deque(deque_iterator_t);
    deque_t* pdeq_second = create_deque(vector_t<char>);

    assert_false(_deque_same_type(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test__deque_same_type__not_same_libcstl_builtin_string(void** state)
{
    deque_t* pdeq_first = create_deque(string_t);
    deque_t* pdeq_second = create_deque(vector_t<char>);

    assert_false(_deque_same_type(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test__deque_same_type__not_same_c_libcstl_builtin(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(vector_t<int>);

    assert_false(_deque_same_type(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

typedef struct _tag_test__deque_same_type__same_user_defined
{
    int n_elem;
}_test__deque_same_type__same_user_defined_t;

void test__deque_same_type__same_user_defined(void** state)
{
    deque_t* pdeq_first = NULL;
    deque_t* pdeq_second = NULL;
    type_register(struct _tag_test__deque_same_type__same_user_defined, NULL, NULL, NULL, NULL);
    type_duplicate(struct _tag_test__deque_same_type__same_user_defined, _test__deque_same_type__same_user_defined_t);
    pdeq_first = create_deque(_test__deque_same_type__same_user_defined_t);
    pdeq_second = create_deque(_test__deque_same_type__same_user_defined_t);

    assert_true(_deque_same_type(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test__deque_same_type__same_user_defined_dup(void** state)
{
    deque_t* pdeq_first = create_deque(_test__deque_same_type__same_user_defined_t);
    deque_t* pdeq_second = create_deque(struct _tag_test__deque_same_type__same_user_defined);

    assert_true(_deque_same_type(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test__deque_same_type__not_same_c_user_define(void** state)
{
    deque_t* pdeq_first = create_deque(_test__deque_same_type__same_user_defined_t);
    deque_t* pdeq_second = create_deque(double);

    assert_false(_deque_same_type(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test__deque_same_type__not_same_libcstl_user_define(void** state)
{
    deque_t* pdeq_first = create_deque(_test__deque_same_type__same_user_defined_t);
    deque_t* pdeq_second = create_deque(iterator_t);

    assert_false(_deque_same_type(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test__deque_same_type__same_container(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);

    assert_true(_deque_same_type(pdeq, pdeq));

    deque_destroy(pdeq);
}

/*
 * test _deque_same_deque_iterator_type
 */
UT_CASE_DEFINATION(_deque_same_deque_iterator_type)
void test__deque_same_deque_iterator_type__null_deque_container(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);

    expect_assert_failure(_deque_same_deque_iterator_type(NULL, deque_begin(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_same_deque_iterator_type__invalid_iterator_null_container(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    it_iter = deque_begin(pdeq);
    it_iter._pt_container = NULL;
    expect_assert_failure(_deque_same_deque_iterator_type(pdeq, it_iter));

    deque_destroy(pdeq);
}

void test__deque_same_deque_iterator_type__invalid_iterator_container_type(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    it_iter = deque_begin(pdeq);
    it_iter._t_containertype = 2823;
    expect_assert_failure(_deque_same_deque_iterator_type(pdeq, it_iter));

    deque_destroy(pdeq);
}

void test__deque_same_deque_iterator_type__invalid_iterator_iterator_type(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    it_iter = deque_begin(pdeq);
    it_iter._t_iteratortype = 222;
    expect_assert_failure(_deque_same_deque_iterator_type(pdeq, it_iter));

    deque_destroy(pdeq);
}

void test__deque_same_deque_iterator_type__same_type_belong_to_deque(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    it_iter = deque_begin(pdeq);
    assert_true(_deque_same_deque_iterator_type(pdeq, it_iter));

    deque_destroy(pdeq);
}

void test__deque_same_deque_iterator_type__same_type_not_belong_to_deque(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq_second);
    it_iter = deque_begin(pdeq_second);
    assert_true(_deque_same_deque_iterator_type(pdeq_first, it_iter));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test__deque_same_deque_iterator_type__not_same_type(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(double);
    deque_iterator_t it_iter;

    deque_init(pdeq_second);
    it_iter = deque_begin(pdeq_second);
    assert_false(_deque_same_deque_iterator_type(pdeq_first, it_iter));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

/*
 * test _deque_same_iterator_type
 */
UT_CASE_DEFINATION(_deque_same_iterator_type)
void test__deque_same_iterator_type__null_deque_container(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);

    expect_assert_failure(_deque_same_iterator_type(NULL, deque_begin(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_same_iterator_type__invalid_iterator_null_container(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    it_iter = deque_begin(pdeq);
    it_iter._pt_container = NULL;
    expect_assert_failure(_deque_same_iterator_type(pdeq, it_iter));

    deque_destroy(pdeq);
}

void test__deque_same_iterator_type__invalid_iterator_container_type(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    it_iter = deque_begin(pdeq);
    it_iter._t_containertype = 2823;
    expect_assert_failure(_deque_same_iterator_type(pdeq, it_iter));

    deque_destroy(pdeq);
}

void test__deque_same_iterator_type__invalid_iterator_iterator_type(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    it_iter = deque_begin(pdeq);
    it_iter._t_iteratortype = 222;
    expect_assert_failure(_deque_same_iterator_type(pdeq, it_iter));

    deque_destroy(pdeq);
}

void test__deque_same_iterator_type__same_type_belong_to_deque(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    it_iter = deque_begin(pdeq);
    assert_true(_deque_same_iterator_type(pdeq, it_iter));

    deque_destroy(pdeq);
}

void test__deque_same_iterator_type__same_type_not_belong_to_deque(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq_second);
    it_iter = deque_begin(pdeq_second);
    assert_true(_deque_same_iterator_type(pdeq_first, it_iter));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test__deque_same_iterator_type__not_same_type(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(double);
    deque_iterator_t it_iter;

    deque_init(pdeq_second);
    it_iter = deque_begin(pdeq_second);
    assert_false(_deque_same_iterator_type(pdeq_first, it_iter));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test__deque_same_iterator_type__same_type_not_deque_iterator(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);

    list_init(plist);
    assert_true(_deque_same_iterator_type(pdeq, list_begin(plist)));

    deque_destroy(pdeq);
    list_destroy(plist);
}

void test__deque_same_iterator_type__not_same_type_not_deque_iterator(void** state)
{
    deque_t* pdeq = create_deque(int);
    vector_t* pvec = create_vector(double);

    vector_init(pvec);
    assert_false(_deque_same_iterator_type(pdeq, vector_begin(pvec)));

    deque_destroy(pdeq);
    vector_destroy(pvec);
}

/*
 * test _deque_get_varg_value_auxiliary
 */
UT_CASE_DEFINATION(_deque_get_varg_value_auxiliary)
static void _wrapper_deque_get_varg_value_auxiliary(deque_t* pdeq_deque, void* pv_varg, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, pv_varg);
    _deque_get_varg_value_auxiliary(pdeq_deque, val_elemlist, pv_varg);
    va_end(val_elemlist);
}

void test__deque_get_varg_value_auxiliary__null_deque_container(void** state)
{
    int n_elem;
    expect_assert_failure(_wrapper_deque_get_varg_value_auxiliary(NULL, &n_elem, 100));
}

void test__deque_get_varg_value_auxiliary__null_node(void** state)
{
    deque_t* pdeq = create_deque(int);

    expect_assert_failure(_wrapper_deque_get_varg_value_auxiliary(pdeq, NULL, 100));

    deque_destroy(pdeq);
}

void test__deque_get_varg_value_auxiliary__non_created_deque_containter(void** state)
{
    int node;
    deque_t* pdeq = create_deque(int);

    pdeq->_t_mapsize = 4;
    expect_assert_failure(_wrapper_deque_get_varg_value_auxiliary(pdeq, &node, 100));

    pdeq->_t_mapsize = 0;
    deque_destroy(pdeq);
}

void test__deque_get_varg_value_auxiliary__c_builtin(void** state)
{
    int n_elem = 0;
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);

    _wrapper_deque_get_varg_value_auxiliary(pdeq, &n_elem, 100);
    assert_true(n_elem == 100);

    deque_destroy(pdeq);
}

void test__deque_get_varg_value_auxiliary__cstr(void** state)
{
    deque_t* pdeq = create_deque(char*);
    string_t* pstr = NULL;
    deque_init(pdeq);
    pstr = create_string();

    _wrapper_deque_get_varg_value_auxiliary(pdeq, pstr, "abcdefg");
    assert_true(strcmp(string_c_str(pstr), "abcdefg") == 0);

    string_destroy(pstr);
    deque_destroy(pdeq);
}

void test__deque_get_varg_value_auxiliary__libcstl_builtin(void** state)
{
    deque_t* pdeq = create_deque(vector_t<int>);
    vector_t* pvec = create_vector(int);
    vector_t* pvec_varg = create_vector(int);
    vector_init_elem(pvec, 10, 100);
    deque_init(pdeq);

    _wrapper_deque_get_varg_value_auxiliary(pdeq, pvec_varg, pvec);
    assert_true(vector_equal(pvec_varg, pvec));

    vector_destroy(pvec_varg);
    deque_destroy(pdeq);
    vector_destroy(pvec);
}

void test__deque_get_varg_value_auxiliary__user_define(void** state)
{
    typedef struct _tag_test__deque_get_varg_value_auxiliary__user_define
    {
        int n_elem;
    }_test__deque_get_varg_value_auxiliary__user_define_t;

    deque_t* pdeq = NULL;
    _test__deque_get_varg_value_auxiliary__user_define_t t_use;
    _test__deque_get_varg_value_auxiliary__user_define_t t_varg;

    type_register(_test__deque_get_varg_value_auxiliary__user_define_t, NULL, NULL, NULL, NULL);
    pdeq = create_deque(_test__deque_get_varg_value_auxiliary__user_define_t);
    deque_init(pdeq);
    t_use.n_elem = 10000;

    _wrapper_deque_get_varg_value_auxiliary(pdeq, &t_varg, &t_use);
    assert_true(t_varg.n_elem == t_use.n_elem);

    deque_destroy(pdeq);
}

/*
 * test _deque_destroy_varg_value_auxiliary
 */
UT_CASE_DEFINATION(_deque_destroy_varg_value_auxiliary)
void test__deque_destroy_varg_value_auxiliary__null_deque_container(void** state)
{
    int varg = 0;
    expect_assert_failure(_deque_destroy_varg_value_auxiliary(NULL, &varg));
}

void test__deque_destroy_varg_value_auxiliary__null_varg(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);
    expect_assert_failure(_deque_destroy_varg_value_auxiliary(pdeq, NULL));
    deque_destroy(pdeq);
}

void test__deque_destroy_varg_value_auxiliary__non_created(void** state)
{
    int varg = 0;
    deque_t deq;
    deq._t_mapsize = 3;
    expect_assert_failure(_deque_destroy_varg_value_auxiliary(&deq, &varg));
}

void test__deque_destroy_varg_value_auxiliary__successfully(void** state)
{
    int varg = 100;
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);
    _deque_destroy_varg_value_auxiliary(pdeq, &varg);
    deque_destroy(pdeq);
}

/*
 * test _deque_init_elem_range_auxiliary
 */
UT_CASE_DEFINATION(_deque_init_elem_range_auxiliary)
void test__deque_init_elem_range_auxiliary__null_deque_containter(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_init_elem(pdeq, 10, 100);

    expect_assert_failure(_deque_init_elem_range_auxiliary(NULL, deque_begin(pdeq), deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_init_elem_range_auxiliary__invalid_range_begin(void** state)
{
    deque_iterator_t it_iter;
    deque_t* pdeq = create_deque(int);
    deque_init_elem(pdeq, 10, 100);

    it_iter = deque_begin(pdeq);
    it_iter._pt_container = NULL;
    expect_assert_failure(_deque_init_elem_range_auxiliary(pdeq, it_iter, deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_init_elem_range_auxiliary__invalid_range_end(void** state)
{
    deque_iterator_t it_iter;
    deque_t* pdeq = create_deque(int);
    deque_init_elem(pdeq, 10, 100);

    it_iter = deque_end(pdeq);
    it_iter._t_iteratortype = _INPUT_ITERATOR;
    expect_assert_failure(_deque_init_elem_range_auxiliary(pdeq, deque_begin(pdeq), it_iter));

    deque_destroy(pdeq);
}

void test__deque_init_elem_range_auxiliary__invalid_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_init_elem(pdeq, 10, 100);

    expect_assert_failure(_deque_init_elem_range_auxiliary(pdeq, deque_end(pdeq), deque_begin(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_init_elem_range_auxiliary__non_created(void** state)
{
    deque_t  deq;
    deque_t* pdeq = create_deque(int);
    deque_init_elem(pdeq, 10, 100);

    deq._t_typeinfo._pt_type = NULL;
    expect_assert_failure(_deque_init_elem_range_auxiliary(&deq, deque_begin(pdeq), deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_init_elem_range_auxiliary__successfully_empty_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);

    _deque_init_elem_range_auxiliary(pdeq, deque_begin(pdeq), deque_end(pdeq));
    assert_true(deque_empty(pdeq));

    deque_destroy(pdeq);
}

void test__deque_init_elem_range_auxiliary__successfully_int(void** state)
{
    size_t i = 0;
    deque_t* pdeq = create_deque(int);
    deque_init_elem(pdeq, 10, 100);

    for(i = 0; i < deque_size(pdeq); ++i)
    {
        assert_int_equal(*(int*)deque_at(pdeq, i), 100);
    }
    _deque_init_elem_range_auxiliary(pdeq, deque_begin(pdeq), deque_end(pdeq));
    for(i = 0; i < deque_size(pdeq); ++i)
    {
        assert_int_equal(*(int*)deque_at(pdeq, i), 0);
    }

    deque_destroy(pdeq);
}

void test__deque_init_elem_range_auxiliary__successfully_cstr(void** state)
{
    deque_iterator_t it_iter;
    deque_t* pdeq = create_deque(char*);
    deque_init(pdeq);

    pdeq->_t_finish._t_pos._t_dequepos._pby_corepos = pdeq->_t_finish._t_pos._t_dequepos._pby_corepos +
        3 * pdeq->_t_typeinfo._pt_type->_t_typesize;
    _deque_init_elem_range_auxiliary(pdeq, deque_begin(pdeq), deque_end(pdeq));
    for(it_iter = deque_begin(pdeq);
        !iterator_equal(it_iter, deque_end(pdeq));
        it_iter = iterator_next(it_iter))
    {
        assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);
    }

    deque_destroy(pdeq);
}

void test__deque_init_elem_range_auxiliary__successfully_iterator(void** state)
{
    deque_t* pdeq = create_deque(iterator_t);
    deque_iterator_t it_iter = _create_deque_iterator();
    deque_iterator_t it_sample = _create_deque_iterator();
    deque_init(pdeq);

    pdeq->_t_finish._t_pos._t_dequepos._pby_corepos = pdeq->_t_finish._t_pos._t_dequepos._pby_corepos +
        3 * pdeq->_t_typeinfo._pt_type->_t_typesize;
    _deque_init_elem_range_auxiliary(pdeq, deque_begin(pdeq), deque_end(pdeq));
    memset(&it_sample, 0x00, sizeof(iterator_t));
    for(it_iter = deque_begin(pdeq);
        !iterator_equal(it_iter, deque_end(pdeq));
        it_iter = iterator_next(it_iter))
    {
        assert_true(memcmp((iterator_t*)iterator_get_pointer(it_iter), &it_sample, sizeof(iterator_t)) == 0);
    }

    deque_destroy(pdeq);
}

void test__deque_init_elem_range_auxiliary__successfully_container(void** state)
{
    deque_iterator_t it_iter;
    deque_t* pdeq = create_deque(vector_t<int>);
    deque_init(pdeq);

    pdeq->_t_finish._t_pos._t_dequepos._pby_corepos = pdeq->_t_finish._t_pos._t_dequepos._pby_corepos +
        3 * pdeq->_t_typeinfo._pt_type->_t_typesize;
    _deque_init_elem_range_auxiliary(pdeq, deque_begin(pdeq), deque_end(pdeq));
    for(it_iter = deque_begin(pdeq);
        !iterator_equal(it_iter, deque_end(pdeq));
        it_iter = iterator_next(it_iter))
    {
        assert_true(_vector_is_inited((vector_t*)iterator_get_pointer(it_iter)));
    }

    deque_destroy(pdeq);
}

/*
 * test _deque_iterator_get_pointer_auxiliary
 */
UT_CASE_DEFINATION(_deque_iterator_get_pointer_auxiliary)
void test__deque_iterator_get_pointer_auxiliary__invalid_iterator(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);
    it_iter._t_pos._t_dequepos._pby_corepos = NULL;

    expect_assert_failure(_deque_iterator_get_pointer_auxiliary(it_iter));

    deque_destroy(pdeq);
}

void test__deque_iterator_get_pointer_auxiliary__invalid_iterator_container_type(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);
    it_iter._t_containertype = _LIST_CONTAINER;

    expect_assert_failure(_deque_iterator_get_pointer_auxiliary(it_iter));

    deque_destroy(pdeq);
}

void test__deque_iterator_get_pointer_auxiliary__invalid_iterator_iterator_type(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);
    it_iter._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(_deque_iterator_get_pointer_auxiliary(it_iter));

    deque_destroy(pdeq);
}

void test__deque_iterator_get_pointer_auxiliary__invalid_iterator_container_pointer(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);
    it_iter._pt_container = NULL;

    expect_assert_failure(_deque_iterator_get_pointer_auxiliary(it_iter));

    deque_destroy(pdeq);
}

void test__deque_iterator_get_pointer_auxiliary__deque_end(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_end(pdeq);

    expect_assert_failure(_deque_iterator_get_pointer_auxiliary(it_iter));

    deque_destroy(pdeq);
}

void test__deque_iterator_get_pointer_auxiliary__successfully_not_border(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_front(pdeq, 23);
    deque_push_front(pdeq, 2);
    deque_push_front(pdeq, 9);
    deque_push_front(pdeq, 100);
    it_iter = deque_begin(pdeq);

    assert_int_equal(*(int*)_deque_iterator_get_pointer_auxiliary(it_iter), 100);

    deque_destroy(pdeq);
}

void test__deque_iterator_get_pointer_auxiliary__successfully_border(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_back(pdeq, 23);
    deque_push_back(pdeq, 2);
    deque_push_back(pdeq, 9);
    deque_push_back(pdeq, 100);
    it_iter = deque_begin(pdeq);

    assert_int_equal(*(int*)_deque_iterator_get_pointer_auxiliary(it_iter), 23);

    deque_destroy(pdeq);
}

void test__deque_iterator_get_pointer_auxiliary__successfully_cstr_not_border(void** state)
{
    deque_t* pdeq = create_deque(char*);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_front(pdeq, "llskd");
    deque_push_front(pdeq, "llllllll");
    deque_push_front(pdeq, "bx");
    deque_push_front(pdeq, "abcdefg");
    it_iter = deque_begin(pdeq);

    assert_true(strcmp("abcdefg", (char*)string_c_str((string_t*)_deque_iterator_get_pointer_auxiliary(it_iter))) == 0);

    deque_destroy(pdeq);
}

void test__deque_iterator_get_pointer_auxiliary__successfully_cstr_border(void** state)
{
    deque_t* pdeq = create_deque(char*);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_back(pdeq, "llskd");
    deque_push_back(pdeq, "llllllll");
    deque_push_back(pdeq, "bx");
    deque_push_back(pdeq, "abcdefg");
    it_iter = deque_begin(pdeq);

    assert_true(strcmp("llskd", (char*)string_c_str((string_t*)_deque_iterator_get_pointer_auxiliary(it_iter))) == 0);

    deque_destroy(pdeq);
}

/*
 * test _deque_expand_at_end
 */
UT_CASE_DEFINATION(_deque_expand_at_end)
void test__deque_expand_at_end__null_deque_container(void** state)
{
    expect_assert_failure(_deque_expand_at_end(NULL, 10, NULL));
}

void test__deque_expand_at_end__non_inited_deque_container(void** state)
{
    deque_t* pdeq = create_deque(int);

    expect_assert_failure(_deque_expand_at_end(pdeq, 10, NULL));

    deque_destroy(pdeq);
}

void test__deque_expand_at_end__invalid_iterator(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    it_iter = deque_begin(pdeq);
    it_iter._t_pos._t_dequepos._pby_corepos = NULL;
    expect_assert_failure(_deque_expand_at_end(pdeq, 10, &it_iter));

    deque_destroy(pdeq);
}

void test__deque_expand_at_end__expand_0(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;
    _byte_t** ppby_old = NULL;

    deque_init(pdeq);
    ppby_old = pdeq->_ppby_map;
    it_iter = _deque_expand_at_end(pdeq, 0, NULL);
    assert_true(ppby_old == pdeq->_ppby_map);
    assert_true(deque_empty(pdeq));
    assert_true(iterator_equal(it_iter, deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_expand_at_end__expand_less_than_chunk(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;
    _byte_t** ppby_old = NULL;

    deque_init(pdeq);
    ppby_old = pdeq->_ppby_map;
    it_iter = _deque_expand_at_end(pdeq, 10, NULL);
    assert_true(ppby_old == pdeq->_ppby_map);
    assert_true(deque_size(pdeq) == 10);
    assert_true(iterator_equal(it_iter, deque_begin(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_expand_at_end__expand_less_than_chunk_pos(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;
    deque_iterator_t it_pos;
    _byte_t** ppby_old = NULL;

    deque_init(pdeq);
    deque_push_back(pdeq, 1);
    deque_push_back(pdeq, 3);
    deque_push_back(pdeq, 4);
    ppby_old = pdeq->_ppby_map;
    it_pos = iterator_next(deque_begin(pdeq));
    it_iter = _deque_expand_at_end(pdeq, 10, &it_pos);
    assert_true(ppby_old == pdeq->_ppby_map);
    assert_true(deque_size(pdeq) == 13);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 3);
    assert_true(iterator_equal(it_iter, iterator_next_n(deque_begin(pdeq), 3)));

    deque_destroy(pdeq);
}

void test__deque_expand_at_end__expand_one_chunk(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;
    _byte_t** ppby_old = NULL;

    deque_init(pdeq);
    ppby_old = pdeq->_ppby_map;
    it_iter = _deque_expand_at_end(pdeq, 16, NULL);
    assert_true(pdeq->_ppby_map == ppby_old);
    assert_true(deque_size(pdeq) == 16);
    assert_true(iterator_equal(it_iter, deque_begin(pdeq)));
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) + 2 == _DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_FIRST_POS(deque_end(pdeq)) == _DEQUE_ITERATOR_COREPOS(deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_expand_at_end__expand_one_chunk_pos(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;
    deque_iterator_t it_pos;
    _byte_t** ppby_old = NULL;

    deque_init(pdeq);
    deque_push_front(pdeq, 2);
    deque_push_front(pdeq, 3);
    deque_push_front(pdeq, 5);
    deque_push_front(pdeq, 7);
    deque_push_back(pdeq, 9);
    deque_push_back(pdeq, 1);
    ppby_old = pdeq->_ppby_map;
    it_pos = deque_end(pdeq);
    it_iter = _deque_expand_at_end(pdeq, 30, &it_pos);
    assert_true(pdeq->_ppby_map == ppby_old);
    assert_true(deque_size(pdeq) == 36);
    assert_true(iterator_equal(it_iter, iterator_next_n(deque_begin(pdeq), 6)));
    assert_true(*(int*)iterator_get_pointer(it_pos) == 0);
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) + 3 == _DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_FIRST_POS(deque_end(pdeq)) == _DEQUE_ITERATOR_COREPOS(deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_expand_at_end__expand_more_than_one_chunk(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;
    _byte_t** ppby_old = NULL;

    deque_init(pdeq);
    ppby_old = pdeq->_ppby_map;
    it_iter = _deque_expand_at_end(pdeq, 20, NULL);
    assert_true(ppby_old == pdeq->_ppby_map);
    assert_true(deque_size(pdeq) == 20);
    assert_true(iterator_equal(it_iter, deque_begin(pdeq)));
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) + 2 == _DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_FIRST_POS(deque_end(pdeq)) + 4 * pdeq->_t_typeinfo._pt_type->_t_typesize ==
        _DEQUE_ITERATOR_COREPOS(deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_expand_at_end__expand_more_than_one_chunk_pos(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;
    deque_iterator_t it_pos;
    _byte_t** ppby_old = NULL;

    deque_init(pdeq);
    deque_push_front(pdeq, 3);
    deque_push_front(pdeq, 5);
    deque_push_front(pdeq, 6);
    deque_push_front(pdeq, 7);
    deque_push_front(pdeq, 9);
    it_pos = deque_begin(pdeq);
    ppby_old = pdeq->_ppby_map;
    it_iter = _deque_expand_at_end(pdeq, 20, &it_pos);
    assert_true(ppby_old == pdeq->_ppby_map);
    assert_true(deque_size(pdeq) == 25);
    assert_true(iterator_equal(it_iter, iterator_next_n(deque_begin(pdeq), 5)));
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) + 2 == _DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_FIRST_POS(deque_end(pdeq)) + 4 * pdeq->_t_typeinfo._pt_type->_t_typesize ==
        _DEQUE_ITERATOR_COREPOS(deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_expand_at_end__expand_remain_map_end(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;
    _byte_t** ppby_old = NULL;

    deque_init(pdeq);
    ppby_old = pdeq->_ppby_map;
    it_iter = _deque_expand_at_end(pdeq, 120, NULL);
    assert_true(ppby_old == pdeq->_ppby_map);
    assert_true(deque_size(pdeq) == 120);
    assert_true(iterator_equal(it_iter, deque_begin(pdeq)));
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) + 8 == _DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_FIRST_POS(deque_end(pdeq)) + 8 * pdeq->_t_typeinfo._pt_type->_t_typesize ==
        _DEQUE_ITERATOR_COREPOS(deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_expand_at_end__expand_remain_map_pos_end(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;
    deque_iterator_t it_pos;
    _byte_t** ppby_old = NULL;

    deque_init(pdeq);
    deque_push_front(pdeq, 2);
    deque_push_front(pdeq, 4);
    deque_push_front(pdeq, 5);
    ppby_old = pdeq->_ppby_map;
    it_pos = iterator_next(deque_begin(pdeq));
    it_iter = _deque_expand_at_end(pdeq, 120, &it_pos);
    assert_true(ppby_old == pdeq->_ppby_map);
    assert_true(deque_size(pdeq) == 123);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 4);
    assert_true(iterator_equal(it_iter, iterator_next_n(deque_begin(pdeq), 3)));
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) + 8 == _DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)) == pdeq->_ppby_map + _DEQUE_MAP_COUNT - 1);
    assert_true(_DEQUE_ITERATOR_FIRST_POS(deque_end(pdeq)) + 8 * pdeq->_t_typeinfo._pt_type->_t_typesize ==
        _DEQUE_ITERATOR_COREPOS(deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_expand_at_end__expand_move_map(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;
    _byte_t** ppby_old = NULL;

    deque_init(pdeq);
    ppby_old = pdeq->_ppby_map;
    it_iter = _deque_expand_at_end(pdeq, 150, NULL);
    assert_true(ppby_old == pdeq->_ppby_map);
    assert_true(deque_size(pdeq) == 150);
    assert_true(iterator_equal(it_iter, deque_begin(pdeq)));
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) + 10 == _DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)) < pdeq->_ppby_map + _DEQUE_MAP_COUNT - 1);
    assert_true(_DEQUE_ITERATOR_FIRST_POS(deque_end(pdeq)) + 6 * pdeq->_t_typeinfo._pt_type->_t_typesize ==
        _DEQUE_ITERATOR_COREPOS(deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_expand_at_end__expand_move_map_pos(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;
    deque_iterator_t it_pos;
    _byte_t** ppby_old = NULL;

    deque_init(pdeq);
    deque_push_front(pdeq, 1);
    deque_push_front(pdeq, 3);
    deque_push_front(pdeq, 4);
    deque_push_front(pdeq, 6);
    it_pos = deque_begin(pdeq);
    ppby_old = pdeq->_ppby_map;
    it_iter = _deque_expand_at_end(pdeq, 150, &it_pos);
    assert_true(ppby_old == pdeq->_ppby_map);
    assert_true(deque_size(pdeq) == 154);
    assert_true(iterator_equal(it_pos, deque_begin(pdeq)));
    assert_true(iterator_equal(it_iter, iterator_next_n(deque_begin(pdeq), 4)));
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) + 10 == _DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)) < pdeq->_ppby_map + _DEQUE_MAP_COUNT - 1);
    assert_true(_DEQUE_ITERATOR_FIRST_POS(deque_end(pdeq)) + 6 * pdeq->_t_typeinfo._pt_type->_t_typesize ==
        _DEQUE_ITERATOR_COREPOS(deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_expand_at_end__expand_full_map(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;
    _byte_t** ppby_old = NULL;

    deque_init(pdeq);
    ppby_old = pdeq->_ppby_map;
    it_iter = _deque_expand_at_end(pdeq, 230, NULL);
    assert_true(pdeq->_ppby_map == ppby_old);
    assert_true(deque_size(pdeq) == 230);
    assert_true(iterator_equal(it_iter, deque_begin(pdeq)));
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) == pdeq->_ppby_map);
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) + 15 == _DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)) == pdeq->_ppby_map + _DEQUE_MAP_COUNT - 1);
    assert_true(_DEQUE_ITERATOR_FIRST_POS(deque_end(pdeq)) + 6 * pdeq->_t_typeinfo._pt_type->_t_typesize ==
        _DEQUE_ITERATOR_COREPOS(deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_expand_at_end__expand_full_map_pos(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;
    deque_iterator_t it_pos;
    _byte_t** ppby_old = NULL;

    deque_init(pdeq);
    deque_push_front(pdeq, 4);
    deque_push_front(pdeq, 5);
    deque_push_front(pdeq, 7);
    it_pos = deque_begin(pdeq);
    ppby_old = pdeq->_ppby_map;
    it_iter = _deque_expand_at_end(pdeq, 230, &it_pos);
    assert_true(deque_size(pdeq) == 233);
    assert_true(pdeq->_ppby_map == ppby_old);
    assert_true(iterator_equal(it_pos, deque_begin(pdeq)));
    assert_true(iterator_equal(it_iter, iterator_next_n(deque_begin(pdeq), 3)));
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) == pdeq->_ppby_map);
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) + 15 == _DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)) == pdeq->_ppby_map + _DEQUE_MAP_COUNT - 1);
    assert_true(_DEQUE_ITERATOR_FIRST_POS(deque_end(pdeq)) + 6 * pdeq->_t_typeinfo._pt_type->_t_typesize ==
        _DEQUE_ITERATOR_COREPOS(deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_expand_at_end__expand_map(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;
    _byte_t** ppby_old = NULL;

    deque_init(pdeq);
    ppby_old = pdeq->_ppby_map;
    it_iter = _deque_expand_at_end(pdeq, 300, NULL);
    assert_true(deque_size(pdeq) == 300);
    assert_true(pdeq->_ppby_map != ppby_old);
    assert_true(pdeq->_t_mapsize = _DEQUE_MAP_COUNT + _DEQUE_MAP_GROW_STEP);
    assert_true(iterator_equal(it_iter, deque_begin(pdeq)));
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) + 19 == _DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)) < pdeq->_ppby_map + pdeq->_t_mapsize - 1);
    assert_true(_DEQUE_ITERATOR_FIRST_POS(deque_end(pdeq)) + 12 * pdeq->_t_typeinfo._pt_type->_t_typesize ==
        _DEQUE_ITERATOR_COREPOS(deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_expand_at_end__expand_map_pos(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;
    deque_iterator_t it_pos;
    _byte_t** ppby_old = NULL;

    deque_init(pdeq);
    deque_push_front(pdeq, 3);
    deque_push_front(pdeq, 5);
    deque_push_front(pdeq, 6);
    deque_push_front(pdeq, 7);
    it_pos = iterator_next(deque_begin(pdeq));
    ppby_old = pdeq->_ppby_map;
    it_iter = _deque_expand_at_end(pdeq, 300, &it_pos);
    assert_true(deque_size(pdeq) == 304);
    assert_true(pdeq->_ppby_map != ppby_old);
    assert_true(pdeq->_t_mapsize = _DEQUE_MAP_COUNT + _DEQUE_MAP_GROW_STEP);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 6);
    assert_true(iterator_equal(it_iter, iterator_next_n(deque_begin(pdeq), 4)));
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) + 19 == _DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)) < pdeq->_ppby_map + pdeq->_t_mapsize - 1);
    assert_true(_DEQUE_ITERATOR_FIRST_POS(deque_end(pdeq)) + 12 * pdeq->_t_typeinfo._pt_type->_t_typesize ==
        _DEQUE_ITERATOR_COREPOS(deque_end(pdeq)));

    deque_destroy(pdeq);
}

/*
 * test _deque_expand_at_begin
 */
UT_CASE_DEFINATION(_deque_expand_at_begin)
void test__deque_expand_at_begin__null_deque_container(void** state)
{
    expect_assert_failure(_deque_expand_at_begin(NULL, 10, NULL));
}

void test__deque_expand_at_begin__non_inited_deque_container(void** state)
{
    deque_t* pdeq = create_deque(int);

    expect_assert_failure(_deque_expand_at_begin(pdeq, 10, NULL));

    deque_destroy(pdeq);
}

void test__deque_expand_at_begin__invalid_iterator(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    it_iter = deque_begin(pdeq);
    it_iter._t_pos._t_dequepos._pby_corepos = NULL;
    expect_assert_failure(_deque_expand_at_begin(pdeq, 10, &it_iter));

    deque_destroy(pdeq);
}

void test__deque_expand_at_begin__expand_0(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;
    _byte_t** ppby_old = NULL;

    deque_init(pdeq);
    ppby_old = pdeq->_ppby_map;
    it_iter = _deque_expand_at_begin(pdeq, 0, NULL);
    assert_true(ppby_old == pdeq->_ppby_map);
    assert_true(deque_empty(pdeq));
    assert_true(iterator_equal(it_iter, deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_expand_at_begin__expand_less_than_chunk(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;
    _byte_t** ppby_old = NULL;

    deque_init(pdeq);
    ppby_old = pdeq->_ppby_map;
    it_iter = _deque_expand_at_begin(pdeq, 10, NULL);
    assert_true(ppby_old == pdeq->_ppby_map);
    assert_true(deque_size(pdeq) == 10);
    assert_true(iterator_equal(it_iter, deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_expand_at_begin__expand_less_than_chunk_pos(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;
    deque_iterator_t it_pos;
    _byte_t** ppby_old = NULL;

    deque_init(pdeq);
    deque_push_back(pdeq, 1);
    deque_push_back(pdeq, 3);
    deque_push_back(pdeq, 4);
    ppby_old = pdeq->_ppby_map;
    it_pos = iterator_next(deque_begin(pdeq));
    it_iter = _deque_expand_at_begin(pdeq, 10, &it_pos);
    assert_true(ppby_old == pdeq->_ppby_map);
    assert_true(deque_size(pdeq) == 13);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 3);
    assert_true(iterator_equal(it_iter, iterator_next_n(deque_begin(pdeq), 10)));

    deque_destroy(pdeq);
}

void test__deque_expand_at_begin__expand_one_chunk(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;
    _byte_t** ppby_old = NULL;

    deque_init(pdeq);
    ppby_old = pdeq->_ppby_map;
    it_iter = _deque_expand_at_begin(pdeq, 16, NULL);
    assert_true(pdeq->_ppby_map == ppby_old);
    assert_true(deque_size(pdeq) == 16);
    assert_true(iterator_equal(it_iter, deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) + 2 == _DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_AFTERLAST_POS(deque_begin(pdeq)) == _DEQUE_ITERATOR_COREPOS(deque_begin(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_expand_at_begin__expand_one_chunk_pos(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;
    deque_iterator_t it_pos;
    _byte_t** ppby_old = NULL;

    deque_init(pdeq);
    deque_push_front(pdeq, 2);
    deque_push_front(pdeq, 3);
    deque_push_front(pdeq, 5);
    deque_push_front(pdeq, 7);
    deque_push_back(pdeq, 9);
    deque_push_back(pdeq, 1);
    ppby_old = pdeq->_ppby_map;
    it_pos = deque_begin(pdeq);
    it_iter = _deque_expand_at_begin(pdeq, 28, &it_pos);
    assert_true(pdeq->_ppby_map == ppby_old);
    assert_true(deque_size(pdeq) == 34);
    assert_true(iterator_equal(it_iter, iterator_next_n(deque_begin(pdeq), 28)));
    assert_true(*(int*)iterator_get_pointer(it_pos) == 7);
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) + 3 == _DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_AFTERLAST_POS(deque_begin(pdeq)) == _DEQUE_ITERATOR_COREPOS(deque_begin(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_expand_at_begin__expand_more_than_one_chunk(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;
    _byte_t** ppby_old = NULL;

    deque_init(pdeq);
    ppby_old = pdeq->_ppby_map;
    it_iter = _deque_expand_at_begin(pdeq, 20, NULL);
    assert_true(ppby_old == pdeq->_ppby_map);
    assert_true(deque_size(pdeq) == 20);
    assert_true(iterator_equal(it_iter, deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) + 2 == _DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_FIRST_POS(deque_begin(pdeq)) + 12 * pdeq->_t_typeinfo._pt_type->_t_typesize ==
        _DEQUE_ITERATOR_COREPOS(deque_begin(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_expand_at_begin__expand_more_than_one_chunk_pos(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;
    deque_iterator_t it_pos;
    _byte_t** ppby_old = NULL;

    deque_init(pdeq);
    deque_push_front(pdeq, 3);
    deque_push_front(pdeq, 5);
    deque_push_front(pdeq, 6);
    deque_push_front(pdeq, 7);
    deque_push_front(pdeq, 9);
    it_pos = deque_end(pdeq);
    ppby_old = pdeq->_ppby_map;
    it_iter = _deque_expand_at_begin(pdeq, 20, &it_pos);
    assert_true(ppby_old == pdeq->_ppby_map);
    assert_true(deque_size(pdeq) == 25);
    assert_true(iterator_equal(it_pos, deque_end(pdeq)));
    assert_true(iterator_equal(it_iter, iterator_next_n(deque_begin(pdeq), 20)));
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) + 2 == _DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_FIRST_POS(deque_begin(pdeq)) + 7 * pdeq->_t_typeinfo._pt_type->_t_typesize ==
        _DEQUE_ITERATOR_COREPOS(deque_begin(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_expand_at_begin__expand_remain_map_begin(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;
    _byte_t** ppby_old = NULL;

    deque_init(pdeq);
    ppby_old = pdeq->_ppby_map;
    it_iter = _deque_expand_at_begin(pdeq, 120, NULL);
    assert_true(ppby_old == pdeq->_ppby_map);
    assert_true(deque_size(pdeq) == 120);
    assert_true(iterator_equal(it_iter, deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) + 8 == _DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) == pdeq->_ppby_map);
    assert_true(_DEQUE_ITERATOR_FIRST_POS(deque_begin(pdeq)) + 8 * pdeq->_t_typeinfo._pt_type->_t_typesize ==
        _DEQUE_ITERATOR_COREPOS(deque_begin(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_expand_at_begin__expand_remain_map_pos_begin(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;
    deque_iterator_t it_pos;
    _byte_t** ppby_old = NULL;

    deque_init(pdeq);
    deque_push_front(pdeq, 2);
    deque_push_front(pdeq, 4);
    deque_push_front(pdeq, 5);
    ppby_old = pdeq->_ppby_map;
    it_pos = iterator_next(deque_begin(pdeq));
    it_iter = _deque_expand_at_begin(pdeq, 120, &it_pos);
    assert_true(ppby_old == pdeq->_ppby_map);
    assert_true(deque_size(pdeq) == 123);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 4);
    assert_true(iterator_equal(it_iter, iterator_next_n(deque_begin(pdeq), 120)));
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) + 8 == _DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) == pdeq->_ppby_map);
    assert_true(_DEQUE_ITERATOR_FIRST_POS(deque_begin(pdeq)) + 5 * pdeq->_t_typeinfo._pt_type->_t_typesize ==
        _DEQUE_ITERATOR_COREPOS(deque_begin(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_expand_at_begin__expand_move_map(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;
    _byte_t** ppby_old = NULL;

    deque_init(pdeq);
    ppby_old = pdeq->_ppby_map;
    it_iter = _deque_expand_at_begin(pdeq, 150, NULL);
    assert_true(ppby_old == pdeq->_ppby_map);
    assert_true(deque_size(pdeq) == 150);
    assert_true(iterator_equal(it_iter, deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) + 10 == _DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) > pdeq->_ppby_map);
    assert_true(_DEQUE_ITERATOR_FIRST_POS(deque_begin(pdeq)) + 10 * pdeq->_t_typeinfo._pt_type->_t_typesize ==
        _DEQUE_ITERATOR_COREPOS(deque_begin(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_expand_at_begin__expand_move_map_pos(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;
    deque_iterator_t it_pos;
    _byte_t** ppby_old = NULL;

    deque_init(pdeq);
    deque_push_front(pdeq, 1);
    deque_push_front(pdeq, 3);
    deque_push_front(pdeq, 4);
    deque_push_front(pdeq, 6);
    it_pos = deque_begin(pdeq);
    ppby_old = pdeq->_ppby_map;
    it_iter = _deque_expand_at_begin(pdeq, 150, &it_pos);
    assert_true(ppby_old == pdeq->_ppby_map);
    assert_true(deque_size(pdeq) == 154);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 6);
    assert_true(iterator_equal(it_iter, iterator_next_n(deque_begin(pdeq), 150)));
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) + 10 == _DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) > pdeq->_ppby_map);
    assert_true(_DEQUE_ITERATOR_FIRST_POS(deque_begin(pdeq)) + 6 * pdeq->_t_typeinfo._pt_type->_t_typesize ==
        _DEQUE_ITERATOR_COREPOS(deque_begin(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_expand_at_begin__expand_full_map(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;
    _byte_t** ppby_old = NULL;

    deque_init(pdeq);
    ppby_old = pdeq->_ppby_map;
    it_iter = _deque_expand_at_begin(pdeq, 230, NULL);
    assert_true(pdeq->_ppby_map == ppby_old);
    assert_true(deque_size(pdeq) == 230);
    assert_true(iterator_equal(it_iter, deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) == pdeq->_ppby_map);
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) + 15 == _DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_FIRST_POS(deque_begin(pdeq)) + 10 * pdeq->_t_typeinfo._pt_type->_t_typesize ==
        _DEQUE_ITERATOR_COREPOS(deque_begin(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_expand_at_begin__expand_full_map_pos(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;
    deque_iterator_t it_pos;
    _byte_t** ppby_old = NULL;

    deque_init(pdeq);
    deque_push_front(pdeq, 4);
    deque_push_front(pdeq, 5);
    deque_push_front(pdeq, 7);
    it_pos = deque_begin(pdeq);
    ppby_old = pdeq->_ppby_map;
    it_iter = _deque_expand_at_begin(pdeq, 230, &it_pos);
    assert_true(deque_size(pdeq) == 233);
    assert_true(pdeq->_ppby_map == ppby_old);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 7);
    assert_true(iterator_equal(it_iter, iterator_next_n(deque_begin(pdeq), 230)));
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) == pdeq->_ppby_map);
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) + 15 == _DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_FIRST_POS(deque_begin(pdeq)) + 7 * pdeq->_t_typeinfo._pt_type->_t_typesize ==
        _DEQUE_ITERATOR_COREPOS(deque_begin(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_expand_at_begin__expand_map(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;
    _byte_t** ppby_old = NULL;

    deque_init(pdeq);
    ppby_old = pdeq->_ppby_map;
    it_iter = _deque_expand_at_begin(pdeq, 300, NULL);
    assert_true(deque_size(pdeq) == 300);
    assert_true(pdeq->_ppby_map != ppby_old);
    assert_true(pdeq->_t_mapsize = _DEQUE_MAP_COUNT + _DEQUE_MAP_GROW_STEP);
    assert_true(iterator_equal(it_iter, deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) + 19 == _DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) > pdeq->_ppby_map);
    assert_true(_DEQUE_ITERATOR_FIRST_POS(deque_begin(pdeq)) + 4 * pdeq->_t_typeinfo._pt_type->_t_typesize ==
        _DEQUE_ITERATOR_COREPOS(deque_begin(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_expand_at_begin__expand_map_pos(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;
    deque_iterator_t it_pos;
    _byte_t** ppby_old = NULL;

    deque_init(pdeq);
    deque_push_front(pdeq, 5);
    deque_push_front(pdeq, 6);
    deque_push_front(pdeq, 7);
    it_pos = iterator_next(deque_begin(pdeq));
    ppby_old = pdeq->_ppby_map;
    it_iter = _deque_expand_at_begin(pdeq, 300, &it_pos);
    assert_true(deque_size(pdeq) == 303);
    assert_true(pdeq->_ppby_map != ppby_old);
    assert_true(pdeq->_t_mapsize = _DEQUE_MAP_COUNT + _DEQUE_MAP_GROW_STEP);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 6);
    assert_true(iterator_equal(it_iter, iterator_next_n(deque_begin(pdeq), 300)));
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) + 19 == _DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)) > pdeq->_ppby_map);
    assert_true(_DEQUE_ITERATOR_FIRST_POS(deque_begin(pdeq)) + 1 * pdeq->_t_typeinfo._pt_type->_t_typesize ==
        _DEQUE_ITERATOR_COREPOS(deque_begin(pdeq)));

    deque_destroy(pdeq);
}

/*
 * test _deque_shrink_at_end
 */
UT_CASE_DEFINATION(_deque_shrink_at_end)
void test__deque_shrink_at_end__null_deque_container(void** state)
{
    expect_assert_failure(_deque_shrink_at_end(NULL, 100));
}

void test__deque_shrink_at_end__non_inited_deque_container(void** state)
{
    deque_t* pdeq = create_deque(int);

    expect_assert_failure(_deque_shrink_at_end(pdeq, 20));

    deque_destroy(pdeq);
}

void test__deque_shrink_at_end__empty_shrink_0(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    _deque_shrink_at_end(pdeq, 0);
    assert_true(deque_empty(pdeq));
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) + 1 == _DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_COREPOS(deque_begin(pdeq)) == _DEQUE_ITERATOR_AFTERLAST_POS(deque_begin(pdeq)));
    assert_true(_DEQUE_ITERATOR_COREPOS(deque_end(pdeq)) == _DEQUE_ITERATOR_FIRST_POS(deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_shrink_at_end__empty_shrink_6(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    _deque_shrink_at_end(pdeq, 5);
    assert_true(deque_empty(pdeq));
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) + 1 == _DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_COREPOS(deque_begin(pdeq)) == _DEQUE_ITERATOR_AFTERLAST_POS(deque_begin(pdeq)));
    assert_true(_DEQUE_ITERATOR_COREPOS(deque_end(pdeq)) == _DEQUE_ITERATOR_FIRST_POS(deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_shrink_at_end__begin_border_shrink_0(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    _deque_expand_at_end(pdeq, 10, NULL);
    _deque_shrink_at_end(pdeq, 0);
    assert_true(deque_size(pdeq) == 10);
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) + 1 == _DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_COREPOS(deque_begin(pdeq)) == _DEQUE_ITERATOR_AFTERLAST_POS(deque_begin(pdeq)));
    assert_true(_DEQUE_ITERATOR_COREPOS(deque_end(pdeq)) - 10 * pdeq->_t_typeinfo._pt_type->_t_typesize ==
        _DEQUE_ITERATOR_FIRST_POS(deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_shrink_at_end__begin_border_shrink_less_size(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    _deque_expand_at_end(pdeq, 10, NULL);
    _deque_shrink_at_end(pdeq, 3);
    assert_true(deque_size(pdeq) == 7);
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) + 1 == _DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_COREPOS(deque_begin(pdeq)) == _DEQUE_ITERATOR_AFTERLAST_POS(deque_begin(pdeq)));
    assert_true(_DEQUE_ITERATOR_COREPOS(deque_end(pdeq)) - 7 * pdeq->_t_typeinfo._pt_type->_t_typesize ==
        _DEQUE_ITERATOR_FIRST_POS(deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_shrink_at_end__begin_border_shrink_equal_to_size(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    _deque_expand_at_end(pdeq, 20, NULL);
    _deque_shrink_at_end(pdeq, 20);
    assert_true(deque_size(pdeq) == 0);
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) + 1 == _DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_COREPOS(deque_begin(pdeq)) == _DEQUE_ITERATOR_AFTERLAST_POS(deque_begin(pdeq)));
    assert_true(_DEQUE_ITERATOR_COREPOS(deque_end(pdeq)) == _DEQUE_ITERATOR_FIRST_POS(deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_shrink_at_end__begin_border_shrink_greater_than_size(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    _deque_expand_at_end(pdeq, 30, NULL);
    _deque_shrink_at_end(pdeq, 59);
    assert_true(deque_size(pdeq) == 0);
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) + 1 == _DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_COREPOS(deque_begin(pdeq)) == _DEQUE_ITERATOR_AFTERLAST_POS(deque_begin(pdeq)));
    assert_true(_DEQUE_ITERATOR_COREPOS(deque_end(pdeq)) == _DEQUE_ITERATOR_FIRST_POS(deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_shrink_at_end__end_border_shrink_0(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    _deque_expand_at_begin(pdeq, 10, NULL);
    _deque_shrink_at_end(pdeq, 0);
    assert_true(deque_size(pdeq) == 10);
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) + 1 == _DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_COREPOS(deque_begin(pdeq)) + 10 * pdeq->_t_typeinfo._pt_type->_t_typesize  ==
        _DEQUE_ITERATOR_AFTERLAST_POS(deque_begin(pdeq)));
    assert_true(_DEQUE_ITERATOR_COREPOS(deque_end(pdeq)) == _DEQUE_ITERATOR_FIRST_POS(deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_shrink_at_end__end_border_shrink_less_size(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    _deque_expand_at_begin(pdeq, 10, NULL);
    _deque_shrink_at_end(pdeq, 3);
    assert_true(deque_size(pdeq) == 7);
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) == _DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_COREPOS(deque_begin(pdeq)) - 6 * pdeq->_t_typeinfo._pt_type->_t_typesize ==
        _DEQUE_ITERATOR_FIRST_POS(deque_begin(pdeq)));
    assert_true(_DEQUE_ITERATOR_COREPOS(deque_end(pdeq)) + 3 * pdeq->_t_typeinfo._pt_type->_t_typesize ==
        _DEQUE_ITERATOR_AFTERLAST_POS(deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_shrink_at_end__end_border_shrink_equal_to_size(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    _deque_expand_at_begin(pdeq, 20, NULL);
    _deque_shrink_at_end(pdeq, 20);
    assert_true(deque_size(pdeq) == 0);
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) == _DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_COREPOS(deque_begin(pdeq)) - 12 * pdeq->_t_typeinfo._pt_type->_t_typesize ==
        _DEQUE_ITERATOR_FIRST_POS(deque_begin(pdeq)));
    assert_true(_DEQUE_ITERATOR_COREPOS(deque_end(pdeq)) + 4 * pdeq->_t_typeinfo._pt_type->_t_typesize ==
        _DEQUE_ITERATOR_AFTERLAST_POS(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_COREPOS(deque_begin(pdeq)) == _DEQUE_ITERATOR_COREPOS(deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_shrink_at_end__end_border_shrink_greater_than_size(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    _deque_expand_at_begin(pdeq, 20, NULL);
    _deque_shrink_at_end(pdeq, 80);
    assert_true(deque_size(pdeq) == 0);
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) == _DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_COREPOS(deque_begin(pdeq)) - 12 * pdeq->_t_typeinfo._pt_type->_t_typesize ==
        _DEQUE_ITERATOR_FIRST_POS(deque_begin(pdeq)));
    assert_true(_DEQUE_ITERATOR_COREPOS(deque_end(pdeq)) + 4 * pdeq->_t_typeinfo._pt_type->_t_typesize ==
        _DEQUE_ITERATOR_AFTERLAST_POS(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_COREPOS(deque_begin(pdeq)) == _DEQUE_ITERATOR_COREPOS(deque_end(pdeq)));

    deque_destroy(pdeq);
}

/*
 * test _deque_shrink_at_begin
 */
UT_CASE_DEFINATION(_deque_shrink_at_begin)
void test__deque_shrink_at_begin__null_deque_container(void** state)
{
    expect_assert_failure(_deque_shrink_at_begin(NULL, 100));
}

void test__deque_shrink_at_begin__non_inited_deque_container(void** state)
{
    deque_t* pdeq = create_deque(int);

    expect_assert_failure(_deque_shrink_at_begin(pdeq, 20));

    deque_destroy(pdeq);
}

void test__deque_shrink_at_begin__empty_shrink_0(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    _deque_shrink_at_begin(pdeq, 0);
    assert_true(deque_empty(pdeq));
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) + 1 == _DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_COREPOS(deque_begin(pdeq)) == _DEQUE_ITERATOR_AFTERLAST_POS(deque_begin(pdeq)));
    assert_true(_DEQUE_ITERATOR_COREPOS(deque_end(pdeq)) == _DEQUE_ITERATOR_FIRST_POS(deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_shrink_at_begin__empty_shrink_6(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    _deque_shrink_at_begin(pdeq, 5);
    assert_true(deque_empty(pdeq));
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) + 1 == _DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_COREPOS(deque_begin(pdeq)) == _DEQUE_ITERATOR_AFTERLAST_POS(deque_begin(pdeq)));
    assert_true(_DEQUE_ITERATOR_COREPOS(deque_end(pdeq)) == _DEQUE_ITERATOR_FIRST_POS(deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_shrink_at_begin__begin_border_shrink_0(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    _deque_expand_at_end(pdeq, 10, NULL);
    _deque_shrink_at_begin(pdeq, 0);
    assert_true(deque_size(pdeq) == 10);
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) + 1 == _DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_COREPOS(deque_begin(pdeq)) == _DEQUE_ITERATOR_AFTERLAST_POS(deque_begin(pdeq)));
    assert_true(_DEQUE_ITERATOR_COREPOS(deque_end(pdeq)) - 10 * pdeq->_t_typeinfo._pt_type->_t_typesize ==
        _DEQUE_ITERATOR_FIRST_POS(deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_shrink_at_begin__begin_border_shrink_less_size(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    _deque_expand_at_end(pdeq, 10, NULL);
    _deque_shrink_at_begin(pdeq, 3);
    assert_true(deque_size(pdeq) == 7);
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) == _DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_COREPOS(deque_begin(pdeq)) - 3 * pdeq->_t_typeinfo._pt_type->_t_typesize ==
        _DEQUE_ITERATOR_FIRST_POS(deque_begin(pdeq)));
    assert_true(_DEQUE_ITERATOR_COREPOS(deque_end(pdeq)) - 10 * pdeq->_t_typeinfo._pt_type->_t_typesize ==
        _DEQUE_ITERATOR_FIRST_POS(deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_shrink_at_begin__begin_border_shrink_equal_to_size(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    _deque_expand_at_end(pdeq, 20, NULL);
    _deque_shrink_at_begin(pdeq, 20);
    assert_true(deque_size(pdeq) == 0);
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) == _DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_COREPOS(deque_begin(pdeq)) - 4 * pdeq->_t_typeinfo._pt_type->_t_typesize ==
        _DEQUE_ITERATOR_FIRST_POS(deque_begin(pdeq)));
    assert_true(_DEQUE_ITERATOR_COREPOS(deque_end(pdeq)) -4 * pdeq->_t_typeinfo._pt_type->_t_typesize ==
        _DEQUE_ITERATOR_FIRST_POS(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_COREPOS(deque_begin(pdeq)) == _DEQUE_ITERATOR_COREPOS(deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_shrink_at_begin__begin_border_shrink_greater_than_size(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    _deque_expand_at_end(pdeq, 30, NULL);
    _deque_shrink_at_begin(pdeq, 59);
    assert_true(deque_size(pdeq) == 0);
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) == _DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_COREPOS(deque_begin(pdeq)) - 14 * pdeq->_t_typeinfo._pt_type->_t_typesize ==
        _DEQUE_ITERATOR_FIRST_POS(deque_begin(pdeq)));
    assert_true(_DEQUE_ITERATOR_COREPOS(deque_end(pdeq)) - 14 * pdeq->_t_typeinfo._pt_type->_t_typesize ==
        _DEQUE_ITERATOR_FIRST_POS(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_COREPOS(deque_begin(pdeq)) == _DEQUE_ITERATOR_COREPOS(deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_shrink_at_begin__end_border_shrink_0(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    _deque_expand_at_begin(pdeq, 10, NULL);
    _deque_shrink_at_begin(pdeq, 0);
    assert_true(deque_size(pdeq) == 10);
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) + 1 == _DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_COREPOS(deque_begin(pdeq)) + 10 * pdeq->_t_typeinfo._pt_type->_t_typesize  ==
        _DEQUE_ITERATOR_AFTERLAST_POS(deque_begin(pdeq)));
    assert_true(_DEQUE_ITERATOR_COREPOS(deque_end(pdeq)) == _DEQUE_ITERATOR_FIRST_POS(deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_shrink_at_begin__end_border_shrink_less_size(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    _deque_expand_at_begin(pdeq, 10, NULL);
    _deque_shrink_at_begin(pdeq, 3);
    assert_true(deque_size(pdeq) == 7);
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) + 1 == _DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_COREPOS(deque_begin(pdeq)) + 7 * pdeq->_t_typeinfo._pt_type->_t_typesize ==
        _DEQUE_ITERATOR_AFTERLAST_POS(deque_begin(pdeq)));
    assert_true(_DEQUE_ITERATOR_COREPOS(deque_end(pdeq)) == _DEQUE_ITERATOR_FIRST_POS(deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_shrink_at_begin__end_border_shrink_equal_to_size(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    _deque_expand_at_begin(pdeq, 20, NULL);
    _deque_shrink_at_begin(pdeq, 20);
    assert_true(deque_size(pdeq) == 0);
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) == _DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_COREPOS(deque_begin(pdeq)) == _DEQUE_ITERATOR_FIRST_POS(deque_begin(pdeq)));
    assert_true(_DEQUE_ITERATOR_COREPOS(deque_end(pdeq)) == _DEQUE_ITERATOR_FIRST_POS(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_COREPOS(deque_begin(pdeq)) == _DEQUE_ITERATOR_COREPOS(deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_shrink_at_begin__end_border_shrink_greater_than_size(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    _deque_expand_at_begin(pdeq, 20, NULL);
    _deque_shrink_at_begin(pdeq, 80);
    assert_true(deque_size(pdeq) == 0);
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(deque_begin(pdeq)) == _DEQUE_ITERATOR_MAP_POINTER(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_COREPOS(deque_begin(pdeq)) == _DEQUE_ITERATOR_FIRST_POS(deque_begin(pdeq)));
    assert_true(_DEQUE_ITERATOR_COREPOS(deque_end(pdeq)) == _DEQUE_ITERATOR_FIRST_POS(deque_end(pdeq)));
    assert_true(_DEQUE_ITERATOR_COREPOS(deque_begin(pdeq)) == _DEQUE_ITERATOR_COREPOS(deque_end(pdeq)));

    deque_destroy(pdeq);
}

/*
 * test _deque_move_elem_to_end
 */
UT_CASE_DEFINATION(_deque_move_elem_to_end)
void test__deque_move_elem_to_end__null_deque_container(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_init_n(pdeq, 10);

    expect_assert_failure(_deque_move_elem_to_end(NULL, deque_begin(pdeq), iterator_next(deque_begin(pdeq)), 4));

    deque_destroy(pdeq);
}

void test__deque_move_elem_to_end__non_inited_deque_container(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_noninited = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(_deque_move_elem_to_end(pdeq_noninited, deque_begin(pdeq), iterator_next(deque_begin(pdeq)), 3));

    deque_destroy(pdeq);
    deque_destroy(pdeq_noninited);
}

void test__deque_move_elem_to_end__invalid_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_begin;
    deque_iterator_t it_end;

    deque_init_n(pdeq, 10);

    it_begin = deque_begin(pdeq);
    it_end = iterator_next(it_begin);
    expect_assert_failure(_deque_move_elem_to_end(pdeq, it_end, it_begin, 3));

    deque_destroy(pdeq);
}

void test__deque_move_elem_to_end__invalid_range_after_moving(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(_deque_move_elem_to_end(pdeq, deque_begin(pdeq), deque_end(pdeq), 100));

    deque_destroy(pdeq);
}

void test__deque_move_elem_to_end__empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    it_iter = _deque_move_elem_to_end(pdeq, deque_begin(pdeq), deque_end(pdeq), 10);
    assert_true(iterator_equal(it_iter, deque_begin(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_move_elem_to_end__0_step(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_back(pdeq, 10);
    deque_push_back(pdeq, 20);
    deque_push_back(pdeq, 30);
    deque_push_back(pdeq, 40);
    deque_push_back(pdeq, 50);
    it_iter = _deque_move_elem_to_end(pdeq, deque_begin(pdeq), deque_end(pdeq), 0);
    assert_true(iterator_equal(it_iter, deque_begin(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_move_elem_to_end__begin_to_end(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_begin;
    deque_iterator_t it_end;
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_back(pdeq, 10);
    deque_push_back(pdeq, 20);
    deque_push_back(pdeq, 30);
    deque_push_back(pdeq, 40);
    deque_push_back(pdeq, 50);
    it_begin = deque_begin(pdeq);
    it_end = iterator_next_n(it_begin, 2);
    it_iter = _deque_move_elem_to_end(pdeq, it_begin, it_end, 3); 
    assert_true(iterator_equal(it_iter, deque_begin(pdeq)));
    it_iter = deque_begin(pdeq);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 10);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 20);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 30);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 10);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 20);

    deque_destroy(pdeq);
}

void test__deque_move_elem_to_end__begin_to_middle(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_begin;
    deque_iterator_t it_end;
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_back(pdeq, 10);
    deque_push_back(pdeq, 20);
    deque_push_back(pdeq, 30);
    deque_push_back(pdeq, 40);
    deque_push_back(pdeq, 50);
    it_begin = deque_begin(pdeq);
    it_end = iterator_next_n(it_begin, 2);
    it_iter = _deque_move_elem_to_end(pdeq, it_begin, it_end, 2); 
    assert_true(iterator_equal(it_iter, deque_begin(pdeq)));
    it_iter = deque_begin(pdeq);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 10);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 20);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 10);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 20);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 50);

    deque_destroy(pdeq);
}

void test__deque_move_elem_to_end__middle_to_end(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_begin;
    deque_iterator_t it_end;
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_back(pdeq, 10);
    deque_push_back(pdeq, 20);
    deque_push_back(pdeq, 30);
    deque_push_back(pdeq, 40);
    deque_push_back(pdeq, 50);
    it_begin = iterator_next(deque_begin(pdeq));
    it_end = iterator_next_n(it_begin, 2);
    it_iter = _deque_move_elem_to_end(pdeq, it_begin, it_end, 2); 
    assert_true(iterator_equal(it_iter, iterator_next(deque_begin(pdeq))));
    it_iter = deque_begin(pdeq);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 10);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 20);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 30);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 20);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 30);

    deque_destroy(pdeq);
}

void test__deque_move_elem_to_end__middle_to_middle(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_begin;
    deque_iterator_t it_end;
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_back(pdeq, 10);
    deque_push_back(pdeq, 20);
    deque_push_back(pdeq, 30);
    deque_push_back(pdeq, 40);
    deque_push_back(pdeq, 50);
    it_begin = iterator_next(deque_begin(pdeq));
    it_end = iterator_next_n(it_begin, 2);
    it_iter = _deque_move_elem_to_end(pdeq, it_begin, it_end, 1); 
    assert_true(iterator_equal(it_iter, iterator_next(deque_begin(pdeq))));
    it_iter = deque_begin(pdeq);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 10);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 20);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 20);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 30);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 50);

    deque_destroy(pdeq);
}

/*
 * test _deque_move_elem_to_begin
 */
UT_CASE_DEFINATION(_deque_move_elem_to_begin)
void test__deque_move_elem_to_begin__null_deque_container(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_begin;
    deque_iterator_t it_end;

    deque_init_n(pdeq, 10);
    it_begin = iterator_next_n(deque_begin(pdeq), 5);
    it_end = iterator_next(it_begin);

    expect_assert_failure(_deque_move_elem_to_begin(NULL, it_begin, it_end, 3));

    deque_destroy(pdeq);
}

void test__deque_move_elem_to_begin__non_inited_deque_container(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_noninited = create_deque(int);
    deque_iterator_t it_begin;
    deque_iterator_t it_end;

    deque_init_n(pdeq, 10);
    it_begin = iterator_next_n(deque_begin(pdeq), 5);
    it_end = iterator_next(it_begin);
    expect_assert_failure(_deque_move_elem_to_begin(pdeq_noninited, it_begin, it_end, 3));

    deque_destroy(pdeq);
    deque_destroy(pdeq_noninited);
}

void test__deque_move_elem_to_begin__invalid_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_begin;
    deque_iterator_t it_end;

    deque_init_n(pdeq, 10);

    it_begin = iterator_next_n(deque_begin(pdeq), 5);
    it_end = iterator_next(it_begin);
    expect_assert_failure(_deque_move_elem_to_begin(pdeq, it_end, it_begin, 3));

    deque_destroy(pdeq);
}

void test__deque_move_elem_to_begin__invalid_range_after_moving(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(_deque_move_elem_to_begin(pdeq, deque_begin(pdeq), deque_end(pdeq), 100));

    deque_destroy(pdeq);
}

void test__deque_move_elem_to_begin__empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = _deque_move_elem_to_begin(pdeq, deque_end(pdeq), deque_end(pdeq), 10);
    assert_true(iterator_equal(it_iter, deque_begin(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_move_elem_to_begin__0_step(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_back(pdeq, 10);
    deque_push_back(pdeq, 20);
    deque_push_back(pdeq, 30);
    deque_push_back(pdeq, 40);
    deque_push_back(pdeq, 50);
    it_iter = _deque_move_elem_to_begin(pdeq, deque_begin(pdeq), deque_end(pdeq), 0);
    assert_true(iterator_equal(it_iter, deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_move_elem_to_begin__end_to_begin(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_begin;
    deque_iterator_t it_end;
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_back(pdeq, 10);
    deque_push_back(pdeq, 20);
    deque_push_back(pdeq, 30);
    deque_push_back(pdeq, 40);
    deque_push_back(pdeq, 50);
    it_begin = iterator_next_n(deque_begin(pdeq), 3);
    it_end = deque_end(pdeq);
    it_iter = _deque_move_elem_to_begin(pdeq, it_begin, it_end, 3); 
    assert_true(iterator_equal(it_iter, iterator_next_n(deque_begin(pdeq), 2)));
    it_iter = deque_begin(pdeq);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 40);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 50);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 30);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 40);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 50);

    deque_destroy(pdeq);
}

void test__deque_move_elem_to_begin__end_to_middle(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_begin;
    deque_iterator_t it_end;
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_back(pdeq, 10);
    deque_push_back(pdeq, 20);
    deque_push_back(pdeq, 30);
    deque_push_back(pdeq, 40);
    deque_push_back(pdeq, 50);
    it_begin = iterator_next_n(deque_begin(pdeq), 3);
    it_end = deque_end(pdeq);
    it_iter = _deque_move_elem_to_begin(pdeq, it_begin, it_end, 2); 
    assert_true(iterator_equal(it_iter, iterator_next_n(deque_begin(pdeq), 3)));
    it_iter = deque_begin(pdeq);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 10);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 40);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 50);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 40);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 50);

    deque_destroy(pdeq);
}

void test__deque_move_elem_to_begin__middle_to_begin(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_begin;
    deque_iterator_t it_end;
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_back(pdeq, 10);
    deque_push_back(pdeq, 20);
    deque_push_back(pdeq, 30);
    deque_push_back(pdeq, 40);
    deque_push_back(pdeq, 50);
    it_begin = iterator_next_n(deque_begin(pdeq), 2);
    it_end = iterator_next_n(it_begin, 2);
    it_iter = _deque_move_elem_to_begin(pdeq, it_begin, it_end, 2); 
    assert_true(iterator_equal(it_iter, iterator_next_n(deque_begin(pdeq), 2)));
    it_iter = deque_begin(pdeq);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 30);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 40);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 30);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 40);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 50);

    deque_destroy(pdeq);
}

void test__deque_move_elem_to_begin__middle_to_middle(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_begin;
    deque_iterator_t it_end;
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_back(pdeq, 10);
    deque_push_back(pdeq, 20);
    deque_push_back(pdeq, 30);
    deque_push_back(pdeq, 40);
    deque_push_back(pdeq, 50);
    it_begin = iterator_next_n(deque_begin(pdeq), 2);
    it_end = iterator_next_n(it_begin, 2);
    it_iter = _deque_move_elem_to_begin(pdeq, it_begin, it_end, 1); 
    assert_true(iterator_equal(it_iter, iterator_next_n(deque_begin(pdeq), 3)));
    it_iter = deque_begin(pdeq);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 10);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 30);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 40);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 40);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 50);

    deque_destroy(pdeq);
}

