#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/cstl_iterator.h"
#include "cstl/cstl_vector_iterator.h"
#include "cstl/cvector.h"
#include "cstl_vector_aux.h"

#include "ut_def.h"
#include "ut_cstl_vector_aux.h"

UT_SUIT_DEFINATION(cstl_vector_aux, _vector_iterator_belong_to_vector)

/*
 * test _vector_iterator_belong_to_vector
 */
UT_CASE_DEFINATION(_vector_iterator_belong_to_vector)
void test__vector_iterator_belong_to_vector__null_container_pointer(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);

    expect_assert_failure(_vector_iterator_belong_to_vector(NULL, it_iter));

    vector_destroy(pvec);
}

void test__vector_iterator_belong_to_vector__invalid_iterator_container_type(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._t_containertype = _LIST_CONTAINER;

    expect_assert_failure(_vector_iterator_belong_to_vector(pvec, it_iter));

    vector_destroy(pvec);
}

void test__vector_iterator_belong_to_vector__invalid_iterator_iterator_type(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(_vector_iterator_belong_to_vector(pvec, it_iter));

    vector_destroy(pvec);
}

void test__vector_iterator_belong_to_vector__invalid_iterator_different_container(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._pt_container = NULL;

    expect_assert_failure(_vector_iterator_belong_to_vector(pvec, it_iter));

    vector_destroy(pvec);
}

void test__vector_iterator_belong_to_vector__less_than_begin(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._t_pos._pc_corepos = NULL;

    assert_false(_vector_iterator_belong_to_vector(pvec, it_iter));

    vector_destroy(pvec);
}

void test__vector_iterator_belong_to_vector__within_vector(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);

    assert_true(_vector_iterator_belong_to_vector(pvec, it_iter));

    vector_destroy(pvec);
}

void test__vector_iterator_belong_to_vector__end_iterator(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_end(pvec);

    assert_true(_vector_iterator_belong_to_vector(pvec, it_iter));

    vector_destroy(pvec);
}

void test__vector_iterator_belong_to_vector__greater_than_end(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_end(pvec);
    it_iter._t_pos._pc_corepos += pvec->_t_typeinfo._pt_type->_t_typesize;

    assert_false(_vector_iterator_belong_to_vector(pvec, it_iter));

    vector_destroy(pvec);
}

/*
 * test _vector_same_type
 */
UT_CASE_DEFINATION(_vector_same_type)
void test__vector_same_type__null_first(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    expect_assert_failure(_vector_same_type(NULL, pvec));

    vector_destroy(pvec);
}

void test__vector_same_type__null_second(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    expect_assert_failure(_vector_same_type(pvec, NULL));

    vector_destroy(pvec);
}

void test__vector_same_type__not_same_type_name(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(double);
    vector_init(pvec_first);
    vector_init(pvec_second);

    assert_false(_vector_same_type(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test__vector_same_type__not_same_type_pointer(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(double);
    vector_init(pvec_first);
    vector_init(pvec_second);

    pvec_second->_t_typeinfo._pt_type = NULL;
    assert_false(_vector_same_type(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test__vector_same_type__not_same_type_style(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(double);
    vector_init(pvec_first);
    vector_init(pvec_second);

    pvec_second->_t_typeinfo._t_style = _TYPE_CSTL_BUILTIN;
    assert_false(_vector_same_type(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test__vector_same_type__same_type(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);
    vector_init(pvec_first);
    vector_init(pvec_second);

    assert_true(_vector_same_type(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test__vector_same_type__same_type_duplicate_name(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(signed);
    vector_init(pvec_first);
    vector_init(pvec_second);

    assert_true(_vector_same_type(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

/*
 * test _vector_same_vector_iterator_type
 */
UT_CASE_DEFINATION(_vector_same_vector_iterator_type)
void test__vector_same_vector_iterator_type__null_vector(void** state)
{
    vector_iterator_t it_iter;

    expect_assert_failure(_vector_same_vector_iterator_type(NULL, it_iter));
}

void test__vector_same_vector_iterator_type__iterator_null_container(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter = _create_vector_iterator();

    vector_init(pvec);

    expect_assert_failure(_vector_same_vector_iterator_type(pvec, it_iter));

    vector_destroy(pvec);
}

void test__vector_same_vector_iterator_type__iterator_not_vector_container(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init(pvec);
    it_iter = vector_begin(pvec);
    it_iter._t_containertype = _LIST_CONTAINER;

    expect_assert_failure(_vector_same_vector_iterator_type(pvec, it_iter));

    vector_destroy(pvec);
}

void test__vector_same_vector_iterator_type__iterator_not_random_iterator(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init(pvec);
    it_iter = vector_begin(pvec);
    it_iter._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(_vector_same_vector_iterator_type(pvec, it_iter));

    vector_destroy(pvec);
}

void test__vector_same_vector_iterator_type__same(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(signed);
    vector_iterator_t it_iter;

    vector_init(pvec_first);
    vector_init(pvec_second);
    it_iter = vector_begin(pvec_second);

    assert_true(_vector_same_vector_iterator_type(pvec_first, it_iter));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test__vector_same_vector_iterator_type__not_same(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(double);
    vector_iterator_t it_iter;

    vector_init(pvec_first);
    vector_init(pvec_second);
    it_iter = vector_begin(pvec_second);

    assert_false(_vector_same_vector_iterator_type(pvec_first, it_iter));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

/*
 * test _vector_get_varg_value_auxiliary
 */
UT_CASE_DEFINATION(_vector_get_varg_value_auxiliary)

static void _wrapper_vector_get_varg_value_auxiliary(vector_t* pvec_vector, void* pv_varg, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, pv_varg);
    _vector_get_varg_value_auxiliary(pvec_vector, val_elemlist, pv_varg);
    va_end(val_elemlist);
}

void test__vector_get_varg_value_auxiliary__null_vector_container(void** state)
{
    int varg = 0;
    expect_assert_failure(_wrapper_vector_get_varg_value_auxiliary(NULL, &varg, 100));
}

void test__vector_get_varg_value_auxiliary__null_varg(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);
    expect_assert_failure(_wrapper_vector_get_varg_value_auxiliary(pvec, NULL, 100));
    vector_destroy(pvec);
}

void test__vector_get_varg_value_auxiliary__successfully(void** state)
{
    int varg = 0;
    vector_t* pvec = create_vector(int);
    vector_init(pvec);
    _wrapper_vector_get_varg_value_auxiliary(pvec, &varg, 100);
    assert_int_equal(varg, 100);
    vector_destroy(pvec);
}

/*
 * test _vector_destroy_varg_value_auxiliary
 */
UT_CASE_DEFINATION(_vector_destroy_varg_value_auxiliary)
void test__vector_destroy_varg_value_auxiliary__null_vector_container(void** state)
{
    int varg = 0;
    expect_assert_failure(_vector_destroy_varg_value_auxiliary(NULL, &varg));
}

void test__vector_destroy_varg_value_auxiliary__null_varg(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);
    expect_assert_failure(_vector_destroy_varg_value_auxiliary(pvec, NULL));
    vector_destroy(pvec);
}

void test__vector_destroy_varg_value_auxiliary__successfully(void** state)
{
    int varg = 100;
    vector_t* pvec = create_vector(int);
    vector_init(pvec);
    _vector_destroy_varg_value_auxiliary(pvec, &varg);
    vector_destroy(pvec);
}

/*
 * test _vector_init_elem_range_auxiliary
 */
UT_CASE_DEFINATION(_vector_init_elem_range_auxiliary)
void test__vector_init_elem_range_auxiliary__null_vector_containter(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init_elem(pvec, 10, 100);

    expect_assert_failure(_vector_init_elem_range_auxiliary(NULL, pvec->_pc_start, pvec->_pc_finish));

    vector_destroy(pvec);
}

void test__vector_init_elem_range_auxiliary__null_pby_start(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init_elem(pvec, 10, 100);

    expect_assert_failure(_vector_init_elem_range_auxiliary(pvec, NULL, pvec->_pc_finish));

    vector_destroy(pvec);
}

void test__vector_init_elem_range_auxiliary__null_pby_finish(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init_elem(pvec, 10, 100);

    expect_assert_failure(_vector_init_elem_range_auxiliary(pvec, pvec->_pc_start, NULL));

    vector_destroy(pvec);
}

void test__vector_init_elem_range_auxiliary__pby_finish_less_then_pby_start(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init_elem(pvec, 10, 100);

    expect_assert_failure(_vector_init_elem_range_auxiliary(pvec, pvec->_pc_finish, pvec->_pc_start));

    vector_destroy(pvec);
}

void test__vector_init_elem_range_auxiliary__successfully_int(void** state)
{
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_init_elem(pvec, 10, 100);

    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_int_equal(*(int*)vector_at(pvec, i), 100);
    }
    _vector_init_elem_range_auxiliary(pvec, pvec->_pc_start, pvec->_pc_finish);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_int_equal(*(int*)vector_at(pvec, i), 0);
    }

    vector_destroy(pvec);
}

void test__vector_init_elem_range_auxiliary__successfully_cstr(void** state)
{
    size_t i = 0;
    vector_t* pvec = create_vector(char*);
    vector_init_elem(pvec, 10, "abcdefg");

    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(strcmp((char*)vector_at(pvec, i), "abcdefg") == 0);
    }
    _vector_init_elem_range_auxiliary(pvec, pvec->_pc_start, pvec->_pc_finish);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(strcmp((char*)vector_at(pvec, i), "") == 0);
    }

    vector_destroy(pvec);
}

void test__vector_init_elem_range_auxiliary__successfully_iterator(void** state)
{
    size_t i = 0;
    vector_t* pvec = create_vector(iterator_t);
    vector_iterator_t it_iter = _create_vector_iterator();
    vector_init_elem(pvec, 10, &it_iter);

    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(memcmp((iterator_t*)vector_at(pvec, i), &it_iter, sizeof(iterator_t)) == 0);
    }
    _vector_init_elem_range_auxiliary(pvec, pvec->_pc_start, pvec->_pc_finish);
    memset(&it_iter, 0x00, sizeof(iterator_t));
    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(memcmp((iterator_t*)vector_at(pvec, i), &it_iter, sizeof(iterator_t)) == 0);
    }

    vector_destroy(pvec);
}

void test__vector_init_elem_range_auxiliary__successfully_container(void** state)
{
    size_t i = 0;
    vector_t a_vec[10];
    vector_t* pvec = create_vector(vector_t<int>);
    vector_init(pvec);

    _vector_init_elem_range_auxiliary(pvec, a_vec, a_vec + 10);
    for(i = 0; i < 10; ++i)
    {
        assert_true(a_vec[i]._t_typeinfo._t_style == _TYPE_C_BUILTIN);
        assert_true(strcmp(a_vec[i]._t_typeinfo._sz_typename, _INT_TYPE) == 0);
        assert_true(a_vec[i]._t_typeinfo._pt_type != NULL);
        assert_true(a_vec[i]._pc_start == NULL);
        assert_true(a_vec[i]._pc_finish == NULL);
        assert_true(a_vec[i]._pc_endofstorage == NULL);
    }

    vector_destroy(pvec);
}

/*
 * test _vector_is_created
 */
UT_CASE_DEFINATION(_vector_is_created)
void test__vector_is_created__null_vector_container(void** state)
{
    expect_assert_failure(_vector_is_created(NULL));
}

void test__vector_is_created__non_created_invalid_start(void** state)
{
    vector_t vec;
    vec._pc_start = 0xcc;
    vec._pc_finish = NULL;
    vec._pc_endofstorage = NULL;
    vec._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    _alloc_init(&vec._t_allocater);
    assert_false(_vector_is_created(&vec));
    _alloc_destroy(&vec._t_allocater);
}

void test__vector_is_created__non_created_invalid_finish(void** state)
{
    vector_t vec;
    vec._pc_start = NULL;
    vec._pc_finish = 0xcc;
    vec._pc_endofstorage = NULL;
    vec._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    _alloc_init(&vec._t_allocater);
    assert_false(_vector_is_created(&vec));
    _alloc_destroy(&vec._t_allocater);
}

void test__vector_is_created__non_created_invalid_endofstorage(void** state)
{
    vector_t vec;
    vec._pc_start = NULL;
    vec._pc_finish = NULL;
    vec._pc_endofstorage = 0xcc;
    vec._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    _alloc_init(&vec._t_allocater);
    assert_false(_vector_is_created(&vec));
    _alloc_destroy(&vec._t_allocater);
}

void test__vector_is_created__non_created_invalid_type_style(void** state)
{
    vector_t vec;
    vec._pc_start = NULL;
    vec._pc_finish = NULL;
    vec._pc_endofstorage = NULL;
    vec._t_typeinfo._t_style = 100;
    _alloc_init(&vec._t_allocater);
    assert_false(_vector_is_created(&vec));
    _alloc_destroy(&vec._t_allocater);
}

void test__vector_is_created__non_created_non_init_allocator(void** state)
{
    vector_t vec;
    vec._pc_start = NULL;
    vec._pc_finish = NULL;
    vec._pc_endofstorage = NULL;
    vec._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    _alloc_init(&vec._t_allocater);
    vec._t_allocater._t_mempoolsize = 1;
    assert_false(_vector_is_created(&vec));
    vec._t_allocater._t_mempoolsize = 0;
    _alloc_destroy(&vec._t_allocater);
}

void test__vector_is_created__created(void** state)
{
    vector_t* pvec = create_vector(int);

    assert_true(_vector_is_created(pvec));

    vector_destroy(pvec);
}

/*
 * test _vector_is_inited
 */
UT_CASE_DEFINATION(_vector_is_inited)
void test__vector_is_inited__null_vector_container(void** state)
{
    expect_assert_failure(_vector_is_inited(NULL));
}

void test__vector_is_inited__non_inited_not_all_null(void** state)
{
    vector_t vec;
    vec._pc_start = 0xcc;
    vec._pc_finish = NULL;
    vec._pc_endofstorage = NULL;
    vec._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    _alloc_init(&vec._t_allocater);
    assert_false(_vector_is_inited(&vec));
    _alloc_destroy(&vec._t_allocater);
}

void test__vector_is_inited__non_inited_finish_less_than_start(void** state)
{
    vector_t vec;
    vec._pc_start = 0x18;
    vec._pc_finish = 0x08;
    vec._pc_endofstorage = 0x20;
    vec._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    _alloc_init(&vec._t_allocater);
    assert_false(_vector_is_inited(&vec));
    _alloc_destroy(&vec._t_allocater);
}

void test__vector_is_inited__non_inited_endofstorage_less_than_start(void** state)
{
    vector_t vec;
    vec._pc_start = 0x18;
    vec._pc_finish = 0x20;
    vec._pc_endofstorage = 0x0c;
    vec._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    _alloc_init(&vec._t_allocater);
    assert_false(_vector_is_inited(&vec));
    _alloc_destroy(&vec._t_allocater);
}

void test__vector_is_inited__non_inited_endofstorage_less_than_finish(void** state)
{
    vector_t vec;
    vec._pc_start = 0x08;
    vec._pc_finish = 0x20;
    vec._pc_endofstorage = 0x0c;
    vec._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    _alloc_init(&vec._t_allocater);
    assert_false(_vector_is_inited(&vec));
    _alloc_destroy(&vec._t_allocater);
}

void test__vector_is_inited__non_inited_invalid_type_style(void** state)
{
    vector_t vec;
    vec._pc_start = NULL;
    vec._pc_finish = NULL;
    vec._pc_endofstorage = NULL;
    vec._t_typeinfo._t_style = 100;
    _alloc_init(&vec._t_allocater);
    assert_false(_vector_is_inited(&vec));
    _alloc_destroy(&vec._t_allocater);
}

void test__vector_is_inited__non_inited_non_init_allocator(void** state)
{
    vector_t vec;
    vec._pc_start = NULL;
    vec._pc_finish = NULL;
    vec._pc_endofstorage = NULL;
    vec._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    _alloc_init(&vec._t_allocater);
    vec._t_allocater._t_mempoolsize = 1;
    assert_false(_vector_is_inited(&vec));
    vec._t_allocater._t_mempoolsize = 0;
    _alloc_destroy(&vec._t_allocater);
}

void test__vector_is_inited__inited_empty(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    assert_true(_vector_is_inited(pvec));

    vector_destroy(pvec);
}

void test__vector_is_inited__inited_non_empty(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 19);

    assert_true(_vector_is_inited(pvec));

    vector_destroy(pvec);
}

