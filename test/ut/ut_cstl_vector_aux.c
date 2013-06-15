#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/citerator.h"
#include "cstl/cstl_vector_iterator.h"
#include "cstl/cvector.h"
#include "cstl/clist.h"
#include "cstl_vector_aux.h"
#include "cstl/cstring.h"

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

void test__vector_iterator_belong_to_vector__non_inited_vector_container(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init(pvec);
    it_iter = vector_begin(pvec);

    pvec->_pby_start = (_byte_t*)0x9883;
    expect_assert_failure(_vector_iterator_belong_to_vector(pvec, it_iter));

    pvec->_pby_start = NULL;
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
    it_iter._t_pos._pby_corepos = NULL;

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
    it_iter._t_pos._pby_corepos += pvec->_t_typeinfo._pt_type->_t_typesize;

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

void test__vector_same_type__non_created_first(void** state)
{
    vector_t vec;
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    vec._t_typeinfo._t_style = 100;
    expect_assert_failure(_vector_same_type(&vec, pvec));

    vector_destroy(pvec);
}

void test__vector_same_type__non_created_second(void** state)
{
    vector_t vec;
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    vec._t_typeinfo._t_style = 100;
    expect_assert_failure(_vector_same_type(pvec, &vec));

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

    assert_false(_vector_same_type(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test__vector_same_type__not_same_type_style(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(vector_t<int>);
    vector_init(pvec_first);
    vector_init(pvec_second);

    assert_false(_vector_same_type(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test__vector_same_type__not_same_type_style_ex1(void** state)
{
    vector_t* pvec_first = create_vector(iterator_t);
    vector_t* pvec_second = create_vector(vector_t<int>);
    vector_init(pvec_first);
    vector_init(pvec_second);

    assert_false(_vector_same_type(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test__vector_same_type__not_same_type_style_ex2(void** state)
{
    vector_t* pvec_first = create_vector(vector_t<double>);
    vector_t* pvec_second = create_vector(vector_t<int>);
    vector_init(pvec_first);
    vector_init(pvec_second);

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

void test__vector_same_type__same_container(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    assert_true(_vector_same_type(pvec, pvec));

    vector_destroy(pvec);
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
 * test _vector_same_iterator_type
 */
UT_CASE_DEFINATION(_vector_same_iterator_type)
void test__vector_same_iterator_type__null_vector_container(void** state)
{
    vector_t* pvector = create_vector(int);
    vector_init(pvector);

    expect_assert_failure(_vector_same_iterator_type(NULL, vector_begin(pvector)));

    vector_destroy(pvector);
}

void test__vector_same_iterator_type__invalid_iterator_null_container(void** state)
{
    vector_t* pvector = create_vector(int);
    vector_iterator_t it_iter;

    vector_init(pvector);
    it_iter = vector_begin(pvector);
    it_iter._pt_container = NULL;
    expect_assert_failure(_vector_same_iterator_type(pvector, it_iter));

    vector_destroy(pvector);
}

void test__vector_same_iterator_type__invalid_iterator_container_type(void** state)
{
    vector_t* pvector = create_vector(int);
    vector_iterator_t it_iter;

    vector_init(pvector);
    it_iter = vector_begin(pvector);
    it_iter._t_containertype = 2823;
    expect_assert_failure(_vector_same_iterator_type(pvector, it_iter));

    vector_destroy(pvector);
}

void test__vector_same_iterator_type__invalid_iterator_iterator_type(void** state)
{
    vector_t* pvector = create_vector(int);
    vector_iterator_t it_iter;

    vector_init(pvector);
    it_iter = vector_begin(pvector);
    it_iter._t_iteratortype = 222;
    expect_assert_failure(_vector_same_iterator_type(pvector, it_iter));

    vector_destroy(pvector);
}

void test__vector_same_iterator_type__same_type_belong_to_vector(void** state)
{
    vector_t* pvector = create_vector(int);
    vector_iterator_t it_iter;

    vector_init(pvector);
    it_iter = vector_begin(pvector);
    assert_true(_vector_same_iterator_type(pvector, it_iter));

    vector_destroy(pvector);
}

void test__vector_same_iterator_type__same_type_not_belong_to_vector(void** state)
{
    vector_t* pvector_first = create_vector(int);
    vector_t* pvector_second = create_vector(int);
    vector_iterator_t it_iter;

    vector_init(pvector_second);
    it_iter = vector_begin(pvector_second);
    assert_true(_vector_same_iterator_type(pvector_first, it_iter));

    vector_destroy(pvector_first);
    vector_destroy(pvector_second);
}

void test__vector_same_iterator_type__not_same_type(void** state)
{
    vector_t* pvector_first = create_vector(int);
    vector_t* pvector_second = create_vector(double);
    vector_iterator_t it_iter;

    vector_init(pvector_second);
    it_iter = vector_begin(pvector_second);
    assert_false(_vector_same_iterator_type(pvector_first, it_iter));

    vector_destroy(pvector_first);
    vector_destroy(pvector_second);
}

void test__vector_same_iterator_type__same_type_not_vector_iterator(void** state)
{
    vector_t* pvector = create_vector(int);
    list_t* plist = create_list(int);

    list_init(plist);
    assert_true(_vector_same_iterator_type(pvector, list_begin(plist)));

    vector_destroy(pvector);
    list_destroy(plist);
}

void test__vector_same_iterator_type__not_same_type_not_vector_iterator(void** state)
{
    vector_t* pvector = create_vector(int);
    list_t* plist = create_list(double);

    list_init(plist);
    assert_false(_vector_same_iterator_type(pvector, list_begin(plist)));

    vector_destroy(pvector);
    list_destroy(plist);
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

void test__vector_get_varg_value_auxiliary__non_created(void** state)
{
    int varg = 0;
    vector_t vec;
    vec._t_typeinfo._t_style = 100;
    expect_assert_failure(_wrapper_vector_get_varg_value_auxiliary(&vec, &varg, 100));
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

void test__vector_destroy_varg_value_auxiliary__non_created(void** state)
{
    int varg = 0;
    vector_t vec;
    vec._t_typeinfo._t_style = 100;
    expect_assert_failure(_vector_destroy_varg_value_auxiliary(&vec, &varg));
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

    expect_assert_failure(_vector_init_elem_range_auxiliary(NULL, pvec->_pby_start, pvec->_pby_finish));

    vector_destroy(pvec);
}

void test__vector_init_elem_range_auxiliary__null_pby_start(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init_elem(pvec, 10, 100);

    expect_assert_failure(_vector_init_elem_range_auxiliary(pvec, NULL, pvec->_pby_finish));

    vector_destroy(pvec);
}

void test__vector_init_elem_range_auxiliary__null_pby_finish(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init_elem(pvec, 10, 100);

    expect_assert_failure(_vector_init_elem_range_auxiliary(pvec, pvec->_pby_start, NULL));

    vector_destroy(pvec);
}

void test__vector_init_elem_range_auxiliary__pby_finish_less_then_pby_start(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init_elem(pvec, 10, 100);

    expect_assert_failure(_vector_init_elem_range_auxiliary(pvec, pvec->_pby_finish, pvec->_pby_start));

    vector_destroy(pvec);
}

void test__vector_init_elem_range_auxiliary__non_created(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init_elem(pvec, 10, 100);
    pvec->_t_typeinfo._t_style = 100;

    expect_assert_failure(_vector_init_elem_range_auxiliary(pvec, pvec->_pby_start, pvec->_pby_finish));

    pvec->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
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
    _vector_init_elem_range_auxiliary(pvec, pvec->_pby_start, pvec->_pby_finish);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_int_equal(*(int*)vector_at(pvec, i), 0);
    }

    vector_destroy(pvec);
}

void test__vector_init_elem_range_auxiliary__successfully_cstr(void** state)
{
    string_t elems[10] = {0};
    size_t i = 0;
    vector_t* pvec = create_vector(char*);
    vector_init_elem(pvec, 10, "abcdefg");

    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(strcmp((char*)vector_at(pvec, i), "abcdefg") == 0);
    }
    _vector_init_elem_range_auxiliary(pvec, elems, elems+10);
    for(i = 0; i < 10; ++i)
    {
        assert_true(strcmp(string_c_str(elems + i), "") == 0);
    }

    for (i = 0; i < 10; ++i) {
        _string_destroy_auxiliary(elems + i);
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
    _vector_init_elem_range_auxiliary(pvec, pvec->_pby_start, pvec->_pby_finish);
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

    _vector_init_elem_range_auxiliary(pvec, (_byte_t*)a_vec, (_byte_t*)(a_vec + 10));
    for(i = 0; i < 10; ++i)
    {
        assert_true(_alloc_is_inited(&a_vec[i]._t_allocator));
        assert_true(a_vec[i]._t_typeinfo._t_style == _TYPE_C_BUILTIN);
        assert_true(strcmp(a_vec[i]._t_typeinfo._s_typename, _INT_TYPE) == 0);
        assert_true(a_vec[i]._t_typeinfo._pt_type != NULL);
        assert_true(a_vec[i]._pby_start == NULL);
        assert_true(a_vec[i]._pby_finish == NULL);
        assert_true(a_vec[i]._pby_endofstorage == NULL);
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
    vec._pby_start = (_byte_t*)0xcc;
    vec._pby_finish = NULL;
    vec._pby_endofstorage = NULL;
    vec._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    _alloc_init(&vec._t_allocator);
    assert_false(_vector_is_created(&vec));
    _alloc_destroy(&vec._t_allocator);
}

void test__vector_is_created__non_created_invalid_finish(void** state)
{
    vector_t vec;
    vec._pby_start = NULL;
    vec._pby_finish = (_byte_t*)0xcc;
    vec._pby_endofstorage = NULL;
    vec._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    _alloc_init(&vec._t_allocator);
    assert_false(_vector_is_created(&vec));
    _alloc_destroy(&vec._t_allocator);
}

void test__vector_is_created__non_created_invalid_endofstorage(void** state)
{
    vector_t vec;
    vec._pby_start = NULL;
    vec._pby_finish = NULL;
    vec._pby_endofstorage = (_byte_t*)0xcc;
    vec._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    _alloc_init(&vec._t_allocator);
    assert_false(_vector_is_created(&vec));
    _alloc_destroy(&vec._t_allocator);
}

void test__vector_is_created__non_created_invalid_type_style(void** state)
{
    vector_t vec;
    vec._pby_start = NULL;
    vec._pby_finish = NULL;
    vec._pby_endofstorage = NULL;
    vec._t_typeinfo._t_style = 100;
    _alloc_init(&vec._t_allocator);
    assert_false(_vector_is_created(&vec));
    _alloc_destroy(&vec._t_allocator);
}

void test__vector_is_created__non_created_non_init_allocator(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);
#ifdef CSTL_MEMORY_MANAGEMENT
    pvec->_t_allocator._t_mempoolsize = 1;
    assert_false(_vector_is_created(pvec));
    pvec->_t_allocator._t_mempoolsize = 0;
#else
    assert_true(_vector_is_created(pvec));
#endif
    vector_destroy(pvec);
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
    vec._pby_start = (_byte_t*)0xcc;
    vec._pby_finish = NULL;
    vec._pby_endofstorage = NULL;
    vec._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    _alloc_init(&vec._t_allocator);
    assert_false(_vector_is_inited(&vec));
    _alloc_destroy(&vec._t_allocator);
}

void test__vector_is_inited__non_inited_finish_less_than_start(void** state)
{
    vector_t vec;
    vec._pby_start = (_byte_t*)0x18;
    vec._pby_finish = (_byte_t*)0x08;
    vec._pby_endofstorage = (_byte_t*)0x20;
    vec._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    _alloc_init(&vec._t_allocator);
    assert_false(_vector_is_inited(&vec));
    _alloc_destroy(&vec._t_allocator);
}

void test__vector_is_inited__non_inited_endofstorage_less_than_start(void** state)
{
    vector_t vec;
    vec._pby_start = (_byte_t*)0x18;
    vec._pby_finish = (_byte_t*)0x20;
    vec._pby_endofstorage = (_byte_t*)0x0c;
    vec._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    _alloc_init(&vec._t_allocator);
    assert_false(_vector_is_inited(&vec));
    _alloc_destroy(&vec._t_allocator);
}

void test__vector_is_inited__non_inited_endofstorage_less_than_finish(void** state)
{
    vector_t vec;
    vec._pby_start = (_byte_t*)0x08;
    vec._pby_finish = (_byte_t*)0x20;
    vec._pby_endofstorage = (_byte_t*)0x0c;
    vec._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    _alloc_init(&vec._t_allocator);
    assert_false(_vector_is_inited(&vec));
    _alloc_destroy(&vec._t_allocator);
}

void test__vector_is_inited__non_inited_invalid_type_style(void** state)
{
    vector_t vec;
    vec._pby_start = NULL;
    vec._pby_finish = NULL;
    vec._pby_endofstorage = NULL;
    vec._t_typeinfo._t_style = 100;
    _alloc_init(&vec._t_allocator);
    assert_false(_vector_is_inited(&vec));
    _alloc_destroy(&vec._t_allocator);
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
    vector_init_n(pvec, 1);

    assert_true(_vector_is_inited(pvec));

    vector_destroy(pvec);
}

/*
 * test _vector_calculate_new_capacity
 */
UT_CASE_DEFINATION(_vector_calculate_new_capacity)
void test__vector_calculate_new_capacity__0_size_0_insert(void** state)
{
    assert_true(_vector_calculate_new_capacity(0, 0) == 16);
}

void test__vector_calculate_new_capacity__0_size_1_insert(void** state)
{
    assert_true(_vector_calculate_new_capacity(0, 1) == 17);
}

void test__vector_calculate_new_capacity__0_size_8_insert(void** state)
{
    assert_true(_vector_calculate_new_capacity(0, 8) == 24);
}

void test__vector_calculate_new_capacity__0_size_48_insert(void** state)
{
    assert_true(_vector_calculate_new_capacity(0, 48) == 72);
}

void test__vector_calculate_new_capacity__0_size_1000_insert(void** state)
{
    assert_true(_vector_calculate_new_capacity(0, 1000) == 1500);
}

void test__vector_calculate_new_capacity__5_size_0_insert(void** state)
{
    assert_true(_vector_calculate_new_capacity(5, 0) == 21);
}

void test__vector_calculate_new_capacity__5_size_1_insert(void** state)
{
    assert_true(_vector_calculate_new_capacity(5, 1) == 22);
}

void test__vector_calculate_new_capacity__5_size_10_insert(void** state)
{
    assert_true(_vector_calculate_new_capacity(5, 10) == 31);
}

void test__vector_calculate_new_capacity__5_size_40_insert(void** state)
{
    assert_true(_vector_calculate_new_capacity(5, 40) == 67);
}

void test__vector_calculate_new_capacity__5_size_4000_insert(void** state)
{
    assert_true(_vector_calculate_new_capacity(5, 4000) == 6007);
}

void test__vector_calculate_new_capacity__40_size_0_insert(void** state)
{
    assert_true(_vector_calculate_new_capacity(40, 0) == 60);
}

void test__vector_calculate_new_capacity__40_size_1_insert(void** state)
{
    assert_true(_vector_calculate_new_capacity(40, 1) == 61);
}

void test__vector_calculate_new_capacity__40_size_40_insert(void** state)
{
    assert_true(_vector_calculate_new_capacity(40, 40) == 120);
}

void test__vector_calculate_new_capacity__40_size_50000_insert(void** state)
{
    assert_true(_vector_calculate_new_capacity(40, 50000) == 75060);
}

void test__vector_calculate_new_capacity__12345_size_0_insert(void** state)
{
    assert_true(_vector_calculate_new_capacity(12345, 0) == 18517);
}

void test__vector_calculate_new_capacity__12345_size_1_insert(void** state)
{
    assert_true(_vector_calculate_new_capacity(12345, 1) == 18519);
}

void test__vector_calculate_new_capacity__12345_size_16_insert(void** state)
{
    assert_true(_vector_calculate_new_capacity(12345, 16) == 18541);
}

void test__vector_calculate_new_capacity__12345_size_1600894_insert(void** state)
{
    assert_true(_vector_calculate_new_capacity(12345, 1600894) == 2419858);
}

