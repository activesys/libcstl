#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/citerator.h"
#include "cstl/clist.h"
#include "cstl/cvector.h"
#include "cstl/cdeque.h"
#include "cstl/cslist.h"
#include "cstl/cset.h"
#include "cstl/cmap.h"
#include "cstl/chash_set.h"
#include "cstl/chash_map.h"
#include "cstl/cstring.h"
#include "cstl/cfunctional.h"
#include "cstl_list_aux.h"

#include "ut_def.h"
#include "ut_cstl_iterator_private.h"

UT_SUIT_DEFINATION(cstl_iterator_private, _iterator_is_valid)

/*
 * test _iterator_is_valid
 */        
UT_CASE_DEFINATION(_iterator_is_valid)
void test__iterator_is_valid__invalid_containertype(void** state)
{
    iterator_t it_iter;
    it_iter._t_containertype = 999;
    it_iter._t_iteratortype = _BIDIRECTIONAL_ITERATOR;
    assert_false(_iterator_is_valid(it_iter));
}

void test__iterator_is_valid__invalid_iteratortype(void** state)
{
    iterator_t it_iter;
    it_iter._t_containertype = _VECTOR_CONTAINER;
    it_iter._t_iteratortype = 999;
    assert_false(_iterator_is_valid(it_iter));
}

void test__iterator_is_valid__valid(void** state)
{
    iterator_t it_iter;
    it_iter._t_containertype = _VECTOR_CONTAINER;
    it_iter._t_iteratortype = _RANDOM_ACCESS_ITERATOR;
    assert_true(_iterator_is_valid(it_iter));
}

/*
 * test _iterator_get_pointer_ignore_cstr
 */
UT_CASE_DEFINATION(_iterator_get_pointer_ignore_cstr)
void test__iterator_get_pointer_ignore_cstr__invalid_iter(void** state)
{
    iterator_t it_iter;
    it_iter._t_containertype = 999;
    it_iter._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(_iterator_get_pointer_ignore_cstr(it_iter));
}

void test__iterator_get_pointer_ignore_cstr__vector(void** state)
{
    vector_t* pvec = create_vector(int);

    vector_init_elem(pvec, 10, 999);
    assert_true(*(int*)_iterator_get_pointer_ignore_cstr(vector_begin(pvec)) == 999);
    vector_destroy(pvec);
}

void test__iterator_get_pointer_ignore_cstr__vector_cstr(void** state)
{
    vector_t* pvec = create_vector(char*);

    vector_init_elem(pvec, 10, "abc");
    assert_true(strcmp("abc", string_c_str(_iterator_get_pointer_ignore_cstr(vector_begin(pvec)))) == 0);
    vector_destroy(pvec);
}

void test__iterator_get_pointer_ignore_cstr__deque(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_elem(pdeq, 10, 1000);
    assert_true(*(int*)_iterator_get_pointer_ignore_cstr(deque_begin(pdeq)) == 1000);
    deque_destroy(pdeq);
}

void test__iterator_get_pointer_ignore_cstr__deque_cstr(void** state)
{
    deque_t* pdeq = create_deque(char*);

    deque_init_elem(pdeq, 10, "abc");
    assert_true(strcmp("abc", string_c_str(_iterator_get_pointer_ignore_cstr(deque_begin(pdeq)))) == 0);
    deque_destroy(pdeq);
}

void test__iterator_get_pointer_ignore_cstr__list(void** state)
{
    list_t* plist = create_list(int);

    list_init_elem(plist, 10, 1000);
    assert_true(*(int*)_iterator_get_pointer_ignore_cstr(list_begin(plist)) == 1000);
    list_destroy(plist);
}

void test__iterator_get_pointer_ignore_cstr__list_cstr(void** state)
{
    list_t* plist = create_list(char*);

    list_init_elem(plist, 10, "abc");
    assert_true(strcmp("abc", string_c_str(_iterator_get_pointer_ignore_cstr(list_begin(plist)))) == 0);
    list_destroy(plist);
}

void test__iterator_get_pointer_ignore_cstr__slist(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init_elem(pslist, 10, 9999);
    assert_true(*(int*)_iterator_get_pointer_ignore_cstr(slist_begin(pslist)) == 9999);
    slist_destroy(pslist);
}

void test__iterator_get_pointer_ignore_cstr__slist_cstr(void** state)
{
    slist_t* pslist = create_slist(char*);

    slist_init_elem(pslist, 10, "abc");
    assert_true(strcmp("abc", string_c_str(_iterator_get_pointer_ignore_cstr(slist_begin(pslist)))) == 0);
    slist_destroy(pslist);
}

void test__iterator_get_pointer_ignore_cstr__set(void** state)
{
    set_t* pset = create_set(int);

    set_init(pset);
    set_insert(pset, 100);
    assert_true(*(int*)_iterator_get_pointer_ignore_cstr(set_begin(pset)) == 100);
    set_destroy(pset);
}

void test__iterator_get_pointer_ignore_cstr__set_cstr(void** state)
{
    set_t* pset = create_set(char*);

    set_init(pset);
    set_insert(pset, "abc");
    assert_true(strcmp("abc", string_c_str(_iterator_get_pointer_ignore_cstr(set_begin(pset)))) == 0);
    set_destroy(pset);
}

void test__iterator_get_pointer_ignore_cstr__multiset(void** state)
{
    multiset_t* pmset = create_multiset(int);

    multiset_init(pmset);
    multiset_insert(pmset, 100);
    assert_true(*(int*)_iterator_get_pointer_ignore_cstr(multiset_begin(pmset)) == 100);
    multiset_destroy(pmset);
}

void test__iterator_get_pointer_ignore_cstr__multiset_cstr(void** state)
{
    multiset_t* pmset = create_multiset(char*);

    multiset_init(pmset);
    multiset_insert(pmset, "abc");
    assert_true(strcmp("abc", string_c_str(_iterator_get_pointer_ignore_cstr(multiset_begin(pmset)))) == 0);
    multiset_destroy(pmset);
}

void test__iterator_get_pointer_ignore_cstr__map(void** state)
{
    map_t* pmap = create_map(int, int);
    pair_t* ppair = NULL;

    map_init(pmap);
    *(int*)map_at(pmap, 10) = 10;
    ppair = (pair_t*)_iterator_get_pointer_ignore_cstr(map_begin(pmap));
    assert_true(*(int*)pair_first(ppair) == 10);
    assert_true(*(int*)pair_second(ppair) == 10);
    map_destroy(pmap);
}

void test__iterator_get_pointer_ignore_cstr__multimap(void** state)
{
    multimap_t* pmmap = create_multimap(int, int);
    pair_t* ppair = create_pair(int, int);

    multimap_init(pmmap);
    pair_init_elem(ppair, 100, 333);
    multimap_insert(pmmap, ppair);
    pair_make(ppair, 0, 0);
    assert_true(*(int*)pair_first(_iterator_get_pointer_ignore_cstr(multimap_begin(pmmap))) == 100);
    assert_true(*(int*)pair_second(_iterator_get_pointer_ignore_cstr(multimap_begin(pmmap))) == 333);
    pair_destroy(ppair);
    multimap_destroy(pmmap);
}

void test__iterator_get_pointer_ignore_cstr__hash_set(void** state)
{
    hash_set_t* phset = create_hash_set(int);

    hash_set_init(phset);
    hash_set_insert(phset, 100);
    assert_true(*(int*)_iterator_get_pointer_ignore_cstr(hash_set_begin(phset)) == 100);
    hash_set_destroy(phset);
}

void test__iterator_get_pointer_ignore_cstr__hash_set_cstr(void** state)
{
    hash_set_t* phset = create_hash_set(char*);

    hash_set_init(phset);
    hash_set_insert(phset, "abc");
    assert_true(strcmp("abc", string_c_str(_iterator_get_pointer_ignore_cstr(hash_set_begin(phset)))) == 0);
    hash_set_destroy(phset);
}

void test__iterator_get_pointer_ignore_cstr__hash_multiset(void** state)
{
    hash_multiset_t* phmset = create_hash_multiset(int);

    hash_multiset_init(phmset);
    hash_multiset_insert(phmset, 100);
    assert_true(*(int*)_iterator_get_pointer_ignore_cstr(hash_multiset_begin(phmset)) == 100);
    hash_multiset_destroy(phmset);
}

void test__iterator_get_pointer_ignore_cstr__hash_multiset_cstr(void** state)
{
    hash_multiset_t* phmset = create_hash_multiset(char*);

    hash_multiset_init(phmset);
    hash_multiset_insert(phmset, "abc");
    assert_true(strcmp("abc", string_c_str(_iterator_get_pointer_ignore_cstr(hash_multiset_begin(phmset)))) == 0);
    hash_multiset_destroy(phmset);
}

void test__iterator_get_pointer_ignore_cstr__hash_map(void** state)
{
    hash_map_t* phmap = create_hash_map(int, int);
    pair_t* ppair = create_pair(int, int);

    hash_map_init(phmap);
    pair_init_elem(ppair, 1, 2);
    hash_map_insert(phmap, ppair);
    pair_make(ppair, 0, 0);
    assert_true(*(int*)pair_first(_iterator_get_pointer_ignore_cstr(hash_map_begin(phmap))) == 1);
    assert_true(*(int*)pair_second(_iterator_get_pointer_ignore_cstr(hash_map_begin(phmap))) == 2);
    pair_destroy(ppair);
    hash_map_destroy(phmap);
}

void test__iterator_get_pointer_ignore_cstr__hash_multimap(void** state)
{
    hash_multimap_t* phmmap = create_hash_multimap(int, int);
    pair_t* ppair = create_pair(int, int);

    hash_multimap_init(phmmap);
    pair_init_elem(ppair, 4, 5);
    hash_multimap_insert(phmmap, ppair);
    pair_make(ppair, 0, 0);
    assert_true(*(int*)pair_first(_iterator_get_pointer_ignore_cstr(hash_multimap_begin(phmmap))) == 4);
    assert_true(*(int*)pair_second(_iterator_get_pointer_ignore_cstr(hash_multimap_begin(phmmap))) == 5);
    pair_destroy(ppair);
    hash_multimap_destroy(phmmap);
}

void test__iterator_get_pointer_ignore_cstr__string(void** state)
{
    string_t* pstr = create_string();
    char c = '\0';

    string_init_cstr(pstr, "abcdefg");
    assert_true(*(char*)_iterator_get_pointer_ignore_cstr(string_begin(pstr)) == 'a');
    string_destroy(pstr);
}

/*
 * test _iterator_same_type
 */
UT_CASE_DEFINATION(_iterator_same_type)
void test__iterator_same_type__invalid_first(void** state)
{
    iterator_t it_first;
    iterator_t it_second;
    it_first._t_containertype = 999;
    it_first._t_iteratortype = _RANDOM_ACCESS_ITERATOR;
    it_second._t_containertype = _VECTOR_CONTAINER;
    it_second._t_iteratortype = _RANDOM_ACCESS_ITERATOR;
    expect_assert_failure(_iterator_same_type(it_first, it_second));
}

void test__iterator_same_type__invalid_second(void** state)
{
    iterator_t it_first;
    iterator_t it_second;
    it_first._t_containertype = _VECTOR_CONTAINER;
    it_first._t_iteratortype = _RANDOM_ACCESS_ITERATOR;
    it_second._t_containertype = _VECTOR_CONTAINER;
    it_second._t_iteratortype = 1000;
    expect_assert_failure(_iterator_same_type(it_first, it_second));
}

void test__iterator_same_type__containertype_not_equal(void** state)
{
    iterator_t it_first;
    iterator_t it_second;
    it_first._t_containertype = _VECTOR_CONTAINER;
    it_first._t_iteratortype = _RANDOM_ACCESS_ITERATOR;
    it_second._t_containertype = _DEQUE_CONTAINER;
    it_second._t_iteratortype = _RANDOM_ACCESS_ITERATOR;
    assert_false(_iterator_same_type(it_first, it_second));
}

void test__iterator_same_type__iteratortype_not_equal(void** state)
{
    iterator_t it_first;
    iterator_t it_second;
    it_first._t_containertype = _VECTOR_CONTAINER;
    it_first._t_iteratortype = _RANDOM_ACCESS_ITERATOR;
    it_second._t_containertype = _VECTOR_CONTAINER;
    it_second._t_iteratortype = _FORWARD_ITERATOR;
    assert_false(_iterator_same_type(it_first, it_second));
}

void test__iterator_same_type__same(void** state)
{
    iterator_t it_first;
    iterator_t it_second;
    it_first._t_containertype = _VECTOR_CONTAINER;
    it_first._t_iteratortype = _RANDOM_ACCESS_ITERATOR;
    it_second._t_containertype = _VECTOR_CONTAINER;
    it_second._t_iteratortype = _RANDOM_ACCESS_ITERATOR;
    assert_true(_iterator_same_type(it_first, it_second));
}

/*
 * test _iterator_before
 */
UT_CASE_DEFINATION(_iterator_before)
void test__iterator_before__invalid_first(void** state)
{
    iterator_t it_first;
    iterator_t it_second;
    it_first._t_containertype = 999;
    it_first._t_iteratortype = _RANDOM_ACCESS_ITERATOR;
    it_second._t_containertype = _VECTOR_CONTAINER;
    it_second._t_iteratortype = _RANDOM_ACCESS_ITERATOR;
    expect_assert_failure(_iterator_before(it_first, it_second));
}

void test__iterator_before__invalid_second(void** state)
{
    iterator_t it_first;
    iterator_t it_second;
    it_first._t_containertype = _VECTOR_CONTAINER;
    it_first._t_iteratortype = _RANDOM_ACCESS_ITERATOR;
    it_second._t_containertype = _VECTOR_CONTAINER;
    it_second._t_iteratortype = 1000;
    expect_assert_failure(_iterator_before(it_first, it_second));
}

void test__iterator_before__containertype_not_equal(void** state)
{
    iterator_t it_first;
    iterator_t it_second;
    it_first._t_containertype = _VECTOR_CONTAINER;
    it_first._t_iteratortype = _RANDOM_ACCESS_ITERATOR;
    it_second._t_containertype = _DEQUE_CONTAINER;
    it_second._t_iteratortype = _RANDOM_ACCESS_ITERATOR;
    expect_assert_failure(_iterator_before(it_first, it_second));
}

void test__iterator_before__iteratortype_not_equal(void** state)
{
    iterator_t it_first;
    iterator_t it_second;
    it_first._t_containertype = _VECTOR_CONTAINER;
    it_first._t_iteratortype = _RANDOM_ACCESS_ITERATOR;
    it_second._t_containertype = _VECTOR_CONTAINER;
    it_second._t_iteratortype = _FORWARD_ITERATOR;
    expect_assert_failure(_iterator_before(it_first, it_second));
}

void test__iterator_before__vector_before(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_first;
    vector_iterator_t it_second;

    vector_init_n(pvec, 10);

    it_first = vector_begin(pvec);
    it_second = vector_end(pvec);
    assert_true(_iterator_before(it_first, it_second));

    vector_destroy(pvec);
}

void test__iterator_before__vector_equal(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_first;
    vector_iterator_t it_second;

    vector_init_n(pvec, 10);

    it_first = vector_begin(pvec);
    it_second = vector_begin(pvec);
    assert_false(_iterator_before(it_first, it_second));

    vector_destroy(pvec);
}

void test__iterator_before__vector_after(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_first;
    vector_iterator_t it_second;

    vector_init_n(pvec, 10);

    it_first = vector_end(pvec);
    it_second = vector_begin(pvec);
    assert_false(_iterator_before(it_first, it_second));

    vector_destroy(pvec);
}

void test__iterator_before__deque_before(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_first;
    deque_iterator_t it_second;

    deque_init_n(pdeq, 10);

    it_first = deque_begin(pdeq);
    it_second = deque_end(pdeq);
    assert_true(_iterator_before(it_first, it_second));

    deque_destroy(pdeq);
}

void test__iterator_before__deque_equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_first;
    deque_iterator_t it_second;

    deque_init_n(pdeq, 10);

    it_first = deque_begin(pdeq);
    it_second = deque_begin(pdeq);
    assert_false(_iterator_before(it_first, it_second));

    deque_destroy(pdeq);
}

void test__iterator_before__deque_after(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_first;
    deque_iterator_t it_second;

    deque_init_n(pdeq, 10);

    it_first = deque_end(pdeq);
    it_second = deque_begin(pdeq);
    assert_false(_iterator_before(it_first, it_second));

    deque_destroy(pdeq);
}

void test__iterator_before__list_before(void** state)
{
    list_t* plist = create_list(int);
    list_iterator_t it_first;
    list_iterator_t it_second;

    list_init_n(plist, 10);

    it_first = list_begin(plist);
    it_second = list_end(plist);
    assert_true(_iterator_before(it_first, it_second));

    list_destroy(plist);
}

void test__iterator_before__list_equal(void** state)
{
    list_t* plist = create_list(int);
    list_iterator_t it_first;
    list_iterator_t it_second;

    list_init_n(plist, 10);

    it_first = list_begin(plist);
    it_second = list_begin(plist);
    assert_false(_iterator_before(it_first, it_second));

    list_destroy(plist);
}

void test__iterator_before__list_after(void** state)
{
    list_t* plist = create_list(int);
    list_iterator_t it_first;
    list_iterator_t it_second;

    list_init_n(plist, 10);

    it_first = list_end(plist);
    it_second = list_begin(plist);
    assert_false(_iterator_before(it_first, it_second));

    list_destroy(plist);
}

void test__iterator_before__slist_before(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_first;
    slist_iterator_t it_second;

    slist_init_n(pslist, 10);

    it_first = slist_begin(pslist);
    it_second = slist_end(pslist);
    assert_true(_iterator_before(it_first, it_second));

    slist_destroy(pslist);
}

void test__iterator_before__slist_equal(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_first;
    slist_iterator_t it_second;

    slist_init_n(pslist, 10);

    it_first = slist_begin(pslist);
    it_second = slist_begin(pslist);
    assert_false(_iterator_before(it_first, it_second));

    slist_destroy(pslist);
}

void test__iterator_before__slist_after(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_first;
    slist_iterator_t it_second;

    slist_init_n(pslist, 10);

    it_first = slist_end(pslist);
    it_second = slist_begin(pslist);
    assert_false(_iterator_before(it_first, it_second));

    slist_destroy(pslist);
}

void test__iterator_before__set_before(void** state)
{
    set_t* pset = create_set(int);
    set_iterator_t it_first;
    set_iterator_t it_second;

    set_init(pset);
    set_insert(pset, 10);

    it_first = set_begin(pset);
    it_second = set_end(pset);
    assert_true(_iterator_before(it_first, it_second));

    set_destroy(pset);
}

void test__iterator_before__set_equal(void** state)
{
    set_t* pset = create_set(int);
    set_iterator_t it_first;
    set_iterator_t it_second;

    set_init(pset);
    set_insert(pset, 10);

    it_first = set_end(pset);
    it_second = set_end(pset);
    assert_false(_iterator_before(it_first, it_second));

    set_destroy(pset);
}

void test__iterator_before__set_after(void** state)
{
    set_t* pset = create_set(int);
    set_iterator_t it_first;
    set_iterator_t it_second;

    set_init(pset);
    set_insert(pset, 10);

    it_first = set_end(pset);
    it_second = set_begin(pset);
    assert_false(_iterator_before(it_first, it_second));

    set_destroy(pset);
}

void test__iterator_before__multiset_before(void** state)
{
    multiset_t* pmset = create_multiset(int);
    multiset_iterator_t it_first;
    multiset_iterator_t it_second;

    multiset_init(pmset);
    multiset_insert(pmset, 10);

    it_first = multiset_begin(pmset);
    it_second = multiset_end(pmset);
    assert_true(_iterator_before(it_first, it_second));

    multiset_destroy(pmset);
}

void test__iterator_before__multiset_equal(void** state)
{
    multiset_t* pmset = create_multiset(int);
    multiset_iterator_t it_first;
    multiset_iterator_t it_second;

    multiset_init(pmset);
    multiset_insert(pmset, 10);

    it_first = multiset_begin(pmset);
    it_second = multiset_begin(pmset);
    assert_false(_iterator_before(it_first, it_second));

    multiset_destroy(pmset);
}

void test__iterator_before__multiset_after(void** state)
{
    multiset_t* pmset = create_multiset(int);
    multiset_iterator_t it_first;
    multiset_iterator_t it_second;

    multiset_init(pmset);
    multiset_insert(pmset, 10);

    it_first = multiset_end(pmset);
    it_second = multiset_begin(pmset);
    assert_false(_iterator_before(it_first, it_second));

    multiset_destroy(pmset);
}

void test__iterator_before__map_before(void** state)
{
    map_t* pmap = create_map(int, int);
    map_iterator_t it_first;
    map_iterator_t it_second;

    map_init(pmap);
    *(int*)map_at(pmap, 10) = 10;

    it_first = map_begin(pmap);
    it_second = map_end(pmap);
    assert_true(_iterator_before(it_first, it_second));

    map_destroy(pmap);
}

void test__iterator_before__map_equal(void** state)
{
    map_t* pmap = create_map(int, int);
    map_iterator_t it_first;
    map_iterator_t it_second;

    map_init(pmap);
    *(int*)map_at(pmap, 10) = 10;

    it_first = map_end(pmap);
    it_second = map_end(pmap);
    assert_false(_iterator_before(it_first, it_second));

    map_destroy(pmap);
}

void test__iterator_before__map_after(void** state)
{
    map_t* pmap = create_map(int, int);
    map_iterator_t it_first;
    map_iterator_t it_second;

    map_init(pmap);
    *(int*)map_at(pmap, 10) = 10;

    it_first = map_end(pmap);
    it_second = map_begin(pmap);
    assert_false(_iterator_before(it_first, it_second));

    map_destroy(pmap);
}

void test__iterator_before__multimap_before(void** state)
{
    multimap_t* pmmap = create_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    multimap_iterator_t it_first;
    multimap_iterator_t it_second;

    multimap_init(pmmap);
    pair_init_elem(ppair, 10, 10);
    multimap_insert(pmmap, ppair);

    it_first = multimap_begin(pmmap);
    it_second = multimap_end(pmmap);
    assert_true(_iterator_before(it_first, it_second));

    multimap_destroy(pmmap);
    pair_destroy(ppair);
}

void test__iterator_before__multimap_equal(void** state)
{
    multimap_t* pmmap = create_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    multimap_iterator_t it_first;
    multimap_iterator_t it_second;

    multimap_init(pmmap);
    pair_init_elem(ppair, 10, 10);
    multimap_insert(pmmap, ppair);

    it_first = multimap_begin(pmmap);
    it_second = multimap_begin(pmmap);
    assert_false(_iterator_before(it_first, it_second));

    multimap_destroy(pmmap);
    pair_destroy(ppair);
}

void test__iterator_before__multimap_after(void** state)
{
    multimap_t* pmmap = create_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    multimap_iterator_t it_first;
    multimap_iterator_t it_second;

    multimap_init(pmmap);
    pair_init_elem(ppair, 10, 10);
    multimap_insert(pmmap, ppair);

    it_first = multimap_end(pmmap);
    it_second = multimap_begin(pmmap);
    assert_false(_iterator_before(it_first, it_second));

    multimap_destroy(pmmap);
    pair_destroy(ppair);
}

void test__iterator_before__hash_set_before(void** state)
{
    hash_set_t* phset = create_hash_set(int);
    hash_set_iterator_t it_first;
    hash_set_iterator_t it_second;

    hash_set_init(phset);
    hash_set_insert(phset, 10);

    it_first = hash_set_begin(phset);
    it_second = hash_set_end(phset);
    assert_true(_iterator_before(it_first, it_second));

    hash_set_destroy(phset);
}

void test__iterator_before__hash_set_equal(void** state)
{
    hash_set_t* phset = create_hash_set(int);
    hash_set_iterator_t it_first;
    hash_set_iterator_t it_second;

    hash_set_init(phset);
    hash_set_insert(phset, 10);

    it_first = hash_set_begin(phset);
    it_second = hash_set_begin(phset);
    assert_false(_iterator_before(it_first, it_second));

    hash_set_destroy(phset);
}

void test__iterator_before__hash_set_after(void** state)
{
    hash_set_t* phset = create_hash_set(int);
    hash_set_iterator_t it_first;
    hash_set_iterator_t it_second;

    hash_set_init(phset);
    hash_set_insert(phset, 10);

    it_first = hash_set_end(phset);
    it_second = hash_set_begin(phset);
    assert_false(_iterator_before(it_first, it_second));

    hash_set_destroy(phset);
}

void test__iterator_before__hash_multiset_before(void** state)
{
    hash_multiset_t* phmset = create_hash_multiset(int);
    hash_multiset_iterator_t it_first;
    hash_multiset_iterator_t it_second;

    hash_multiset_init(phmset);
    hash_multiset_insert(phmset, 10);

    it_first = hash_multiset_begin(phmset);
    it_second = hash_multiset_end(phmset);
    assert_true(_iterator_before(it_first, it_second));

    hash_multiset_destroy(phmset);
}

void test__iterator_before__hash_multiset_equal(void** state)
{
    hash_multiset_t* phmset = create_hash_multiset(int);
    hash_multiset_iterator_t it_first;
    hash_multiset_iterator_t it_second;

    hash_multiset_init(phmset);
    hash_multiset_insert(phmset, 10);

    it_first = hash_multiset_begin(phmset);
    it_second = hash_multiset_begin(phmset);
    assert_false(_iterator_before(it_first, it_second));

    hash_multiset_destroy(phmset);
}

void test__iterator_before__hash_multiset_after(void** state)
{
    hash_multiset_t* phmset = create_hash_multiset(int);
    hash_multiset_iterator_t it_first;
    hash_multiset_iterator_t it_second;

    hash_multiset_init(phmset);
    hash_multiset_insert(phmset, 10);

    it_first = hash_multiset_end(phmset);
    it_second = hash_multiset_begin(phmset);
    assert_false(_iterator_before(it_first, it_second));

    hash_multiset_destroy(phmset);
}

void test__iterator_before__hash_map_before(void** state)
{
    hash_map_t* phmap = create_hash_map(int, int);
    hash_map_iterator_t it_first;
    hash_map_iterator_t it_second;

    hash_map_init(phmap);
    *(int*)hash_map_at(phmap, 10) = 10;

    it_first = hash_map_begin(phmap);
    it_second = hash_map_end(phmap);
    assert_true(_iterator_before(it_first, it_second));

    hash_map_destroy(phmap);
}

void test__iterator_before__hash_map_equal(void** state)
{
    hash_map_t* phmap = create_hash_map(int, int);
    hash_map_iterator_t it_first;
    hash_map_iterator_t it_second;

    hash_map_init(phmap);
    *(int*)hash_map_at(phmap, 10) = 10;

    it_first = hash_map_begin(phmap);
    it_second = hash_map_begin(phmap);
    assert_false(_iterator_before(it_first, it_second));

    hash_map_destroy(phmap);
}

void test__iterator_before__hash_map_after(void** state)
{
    hash_map_t* phmap = create_hash_map(int, int);
    hash_map_iterator_t it_first;
    hash_map_iterator_t it_second;

    hash_map_init(phmap);
    *(int*)hash_map_at(phmap, 10) = 10;

    it_first = hash_map_end(phmap);
    it_second = hash_map_begin(phmap);
    assert_false(_iterator_before(it_first, it_second));

    hash_map_destroy(phmap);
}

void test__iterator_before__hash_multimap_before(void** state)
{
    hash_multimap_t* phmmap = create_hash_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    hash_multimap_iterator_t it_first;
    hash_multimap_iterator_t it_second;

    hash_multimap_init(phmmap);
    pair_init_elem(ppair, 10, 10);
    hash_multimap_insert(phmmap, ppair);

    it_first = hash_multimap_begin(phmmap);
    it_second = hash_multimap_end(phmmap);
    assert_true(_iterator_before(it_first, it_second));

    hash_multimap_destroy(phmmap);
    pair_destroy(ppair);
}

void test__iterator_before__hash_multimap_equal(void** state)
{
    hash_multimap_t* phmmap = create_hash_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    hash_multimap_iterator_t it_first;
    hash_multimap_iterator_t it_second;

    hash_multimap_init(phmmap);
    pair_init_elem(ppair, 10, 10);
    hash_multimap_insert(phmmap, ppair);

    it_first = hash_multimap_begin(phmmap);
    it_second = hash_multimap_begin(phmmap);
    assert_false(_iterator_before(it_first, it_second));

    hash_multimap_destroy(phmmap);
    pair_destroy(ppair);
}

void test__iterator_before__hash_multimap_after(void** state)
{
    hash_multimap_t* phmmap = create_hash_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    hash_multimap_iterator_t it_first;
    hash_multimap_iterator_t it_second;

    hash_multimap_init(phmmap);
    pair_init_elem(ppair, 10, 10);
    hash_multimap_insert(phmmap, ppair);

    it_first = hash_multimap_end(phmmap);
    it_second = hash_multimap_begin(phmmap);
    assert_false(_iterator_before(it_first, it_second));

    hash_multimap_destroy(phmmap);
    pair_destroy(ppair);
}

void test__iterator_before__basic_string_before(void** state)
{
    string_t* pstr = create_string();
    string_iterator_t it_first;
    string_iterator_t it_second;

    string_init_cstr(pstr, "abcdefg");
    
    it_first = string_begin(pstr);
    it_second = string_end(pstr);
    assert_true(_iterator_before(it_first, it_second));

    string_destroy(pstr);
}

void test__iterator_before__basic_string_equal(void** state)
{
    string_t* pstr = create_string();
    string_iterator_t it_first;
    string_iterator_t it_second;

    string_init_cstr(pstr, "abcdefg");
    
    it_first = string_begin(pstr);
    it_second = string_begin(pstr);
    assert_false(_iterator_before(it_first, it_second));

    string_destroy(pstr);
}

void test__iterator_before__basic_string_after(void** state)
{
    string_t* pstr = create_string();
    string_iterator_t it_first;
    string_iterator_t it_second;

    string_init_cstr(pstr, "abcdefg");
    
    it_first = string_end(pstr);
    it_second = string_begin(pstr);
    assert_false(_iterator_before(it_first, it_second));

    string_destroy(pstr);
}

/*
 * test _iterator_limit_type
 */        
UT_CASE_DEFINATION(_iterator_limit_type)
void test__iterator_limit_type__invalid_iterator(void** state)
{
    iterator_t it_iter = _create_vector_iterator();
    it_iter._t_iteratortype = 2222;
    expect_assert_failure(_iterator_limit_type(it_iter, _RANDOM_ACCESS_ITERATOR));
}

void test__iterator_limit_type__invalid_limittype(void** state)
{
    iterator_t it_iter = _create_list_iterator();
    expect_assert_failure(_iterator_limit_type(it_iter, 222));
}

void test__iterator_limit_type__input_iterator_true(void** state)
{
    iterator_t it_iter = _create_vector_iterator();
    assert_true(_iterator_limit_type(it_iter, _INPUT_ITERATOR));
}

void test__iterator_limit_type__input_iterator_false(void** state)
{
    iterator_t it_iter = _create_vector_iterator();
    it_iter._t_iteratortype = _OUTPUT_ITERATOR;
    assert_false(_iterator_limit_type(it_iter, _INPUT_ITERATOR));
}

void test__iterator_limit_type__output_iterator_true(void** state)
{
    iterator_t it_iter = _create_vector_iterator();
    assert_true(_iterator_limit_type(it_iter, _OUTPUT_ITERATOR));
}

void test__iterator_limit_type__output_iterator_false(void** state)
{
    iterator_t it_iter = _create_vector_iterator();
    it_iter._t_iteratortype = _INPUT_ITERATOR;
    assert_false(_iterator_limit_type(it_iter, _OUTPUT_ITERATOR));
}

void test__iterator_limit_type__forward_iterator_true(void** state)
{
    iterator_t it_iter = _create_vector_iterator();
    assert_true(_iterator_limit_type(it_iter, _FORWARD_ITERATOR));
}

void test__iterator_limit_type__forward_iterator_false(void** state)
{
    iterator_t it_iter = _create_vector_iterator();
    it_iter._t_iteratortype = _OUTPUT_ITERATOR;
    assert_false(_iterator_limit_type(it_iter, _FORWARD_ITERATOR));
}

void test__iterator_limit_type__bidirectional_iterator_true(void** state)
{
    iterator_t it_iter = _create_vector_iterator();
    assert_true(_iterator_limit_type(it_iter, _BIDIRECTIONAL_ITERATOR));
}

void test__iterator_limit_type__bidirectional_iterator_false(void** state)
{
    iterator_t it_iter = _create_vector_iterator();
    it_iter._t_iteratortype = _OUTPUT_ITERATOR;
    assert_false(_iterator_limit_type(it_iter, _BIDIRECTIONAL_ITERATOR));
}

void test__iterator_limit_type__random_access_iterator_true(void** state)
{
    iterator_t it_iter = _create_vector_iterator();
    assert_true(_iterator_limit_type(it_iter, _RANDOM_ACCESS_ITERATOR));
}

void test__iterator_limit_type__random_access_iterator_false(void** state)
{
    iterator_t it_iter = _create_list_iterator();
    assert_false(_iterator_limit_type(it_iter, _RANDOM_ACCESS_ITERATOR));
}

/*
 * test _iterator_valid_range
 */
UT_CASE_DEFINATION(_iterator_valid_range)
void test__iterator_valid_range__invalid_first(void** state)
{
    iterator_t it_first = _create_vector_iterator();
    iterator_t it_last = _create_vector_iterator();
    it_first._t_iteratortype = 5555;

    expect_assert_failure(_iterator_valid_range(it_first, it_last, _INPUT_ITERATOR));
}

void test__iterator_valid_range__invalid_last(void** state)
{
    iterator_t it_first = _create_vector_iterator();
    iterator_t it_last = _create_vector_iterator();
    it_last._t_containertype = 4444;

    expect_assert_failure(_iterator_valid_range(it_first, it_last, _INPUT_ITERATOR));
}

void test__iterator_valid_range__invalid_type(void** state)
{
    iterator_t it_first = _create_vector_iterator();
    iterator_t it_last = _create_vector_iterator();

    expect_assert_failure(_iterator_valid_range(it_first, it_last, 999));
}

void test__iterator_valid_range__not_same(void** state)
{
    iterator_t it_first = _create_vector_iterator();
    iterator_t it_last = _create_list_iterator();

    assert_false(_iterator_valid_range(it_first, it_last, _INPUT_ITERATOR));
}

void test__iterator_valid_range__limit_type(void** state)
{
    iterator_t it_first = _create_list_iterator();
    iterator_t it_last = _create_list_iterator();

    assert_false(_iterator_valid_range(it_first, it_last, _RANDOM_ACCESS_ITERATOR));
}

void test__iterator_valid_range__equal(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_first;
    vector_iterator_t it_last;

    vector_init_n(pvec, 10);

    it_first = vector_begin(pvec);
    it_last = vector_begin(pvec);
    assert_true(_iterator_valid_range(it_first, it_last, _RANDOM_ACCESS_ITERATOR));

    vector_destroy(pvec);
}

void test__iterator_valid_range__before(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_first;
    vector_iterator_t it_last;

    vector_init_n(pvec, 10);

    it_first = vector_begin(pvec);
    it_last = vector_end(pvec);
    assert_true(_iterator_valid_range(it_first, it_last, _RANDOM_ACCESS_ITERATOR));

    vector_destroy(pvec);
}

void test__iterator_valid_range__after(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_first;
    vector_iterator_t it_last;

    vector_init_n(pvec, 10);

    it_first = vector_end(pvec);
    it_last = vector_begin(pvec);
    assert_false(_iterator_valid_range(it_first, it_last, _RANDOM_ACCESS_ITERATOR));

    vector_destroy(pvec);
}

/*
 * test _iterator_get_typeinfo
 */
UT_CASE_DEFINATION(_iterator_get_typeinfo)
void test__iterator_get_typeinfo__invalid(void** state)
{
    iterator_t it_iter;
    it_iter._t_containertype = _VECTOR_CONTAINER;
    it_iter._t_iteratortype = 444;
    expect_assert_failure(_iterator_get_typeinfo(it_iter));
}

void test__iterator_get_typeinfo__vector(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;
    vector_init(pvec);

    it_iter = vector_begin(pvec);
    assert_true(_iterator_get_typeinfo(it_iter) != NULL);

    vector_destroy(pvec);
}

void test__iterator_get_typeinfo__deque(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    it_iter = deque_begin(pdeq);
    assert_true(_iterator_get_typeinfo(it_iter) != NULL);
    deque_destroy(pdeq);
}

void test__iterator_get_typeinfo__list(void** state)
{
    list_t* plist = create_list(int);
    list_iterator_t it_iter;

    list_init(plist);
    it_iter = list_begin(plist);
    assert_true(_iterator_get_typeinfo(it_iter) != NULL);
    list_destroy(plist);
}

void test__iterator_get_typeinfo__slist(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    it_iter = deque_begin(pdeq);
    assert_true(_iterator_get_typeinfo(it_iter) != NULL);
    deque_destroy(pdeq);
}

void test__iterator_get_typeinfo__set(void** state)
{
    set_t* pset = create_set(int);
    set_iterator_t it_iter;

    set_init(pset);
    it_iter = set_begin(pset);
    assert_true(_iterator_get_typeinfo(it_iter) != NULL);
    set_destroy(pset);
}

void test__iterator_get_typeinfo__multiset(void** state)
{
    multiset_t* pmset = create_multiset(int);
    multiset_iterator_t it_iter;

    multiset_init(pmset);
    it_iter = multiset_begin(pmset);
    assert_true(_iterator_get_typeinfo(it_iter) != NULL);
    multiset_destroy(pmset);
}

void test__iterator_get_typeinfo__map(void** state)
{
    map_t* pmap = create_map(int, int);
    map_iterator_t it_iter;

    map_init(pmap);
    it_iter = map_begin(pmap);
    assert_true(_iterator_get_typeinfo(it_iter) != NULL);
    map_destroy(pmap);
}

void test__iterator_get_typeinfo__multimap(void** state)
{
    multimap_t* pmmap = create_multimap(int, int);
    multimap_iterator_t it_iter;

    multimap_init(pmmap);
    it_iter = multimap_begin(pmmap);
    assert_true(_iterator_get_typeinfo(it_iter) != NULL);
    multimap_destroy(pmmap);
}

void test__iterator_get_typeinfo__hash_set(void** state)
{
    hash_set_t* phset = create_hash_set(int);
    hash_set_iterator_t it_iter;

    hash_set_init(phset);
    it_iter = hash_set_begin(phset);
    assert_true(_iterator_get_typeinfo(it_iter) != NULL);
    hash_set_destroy(phset);
}

void test__iterator_get_typeinfo__hash_multiset(void** state)
{
    hash_multiset_t* phmset = create_hash_multiset(int);
    hash_multiset_iterator_t it_iter;

    hash_multiset_init(phmset);
    it_iter = hash_multiset_begin(phmset);
    assert_true(_iterator_get_typeinfo(it_iter) != NULL);
    hash_multiset_destroy(phmset);
}

void test__iterator_get_typeinfo__hash_map(void** state)
{
    hash_map_t* phmap = create_hash_map(int, int);
    hash_map_iterator_t it_iter;

    hash_map_init(phmap);
    it_iter = hash_map_begin(phmap);
    assert_true(_iterator_get_typeinfo(it_iter) != NULL);
    hash_map_destroy(phmap);
}

void test__iterator_get_typeinfo__hash_multimap(void** state)
{
    hash_multimap_t* phmmap = create_hash_multimap(int, int);
    hash_multimap_iterator_t it_iter;

    hash_multimap_init(phmmap);
    it_iter = hash_multimap_begin(phmmap);
    assert_true(_iterator_get_typeinfo(it_iter) != NULL);
    hash_multimap_destroy(phmmap);
}

void test__iterator_get_typeinfo__string(void** state)
{
    string_t* pstr = create_string();
    string_iterator_t it_iter;

    string_init(pstr);
    it_iter = string_begin(pstr);
    assert_true(_iterator_get_typeinfo(it_iter) != NULL);
    string_destroy(pstr);
}

/*
 * test _iterator_get_typestyle
 */
UT_CASE_DEFINATION(_iterator_get_typestyle)
void test__iterator_get_typestyle__invalid(void** state)
{
    iterator_t it_iter;
    it_iter._t_containertype = _VECTOR_CONTAINER;
    it_iter._t_iteratortype = 899;
    expect_assert_failure(_iterator_get_typestyle(it_iter));
}

void test__iterator_get_typestyle__c_builtin(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init(pvec);
    it_iter = vector_begin(pvec);
    assert_true(_iterator_get_typestyle(it_iter) == _TYPE_C_BUILTIN);
    vector_destroy(pvec);
}

void test__iterator_get_typestyle__libcstl_builtin(void** state)
{
    vector_t* pvec = create_vector(list_t<int>);
    vector_iterator_t it_iter;

    vector_init(pvec);
    it_iter = vector_begin(pvec);
    assert_true(_iterator_get_typestyle(it_iter) == _TYPE_CSTL_BUILTIN);
    vector_destroy(pvec);
}

typedef struct _tagabc
{
    int n_elem;
}abc_t;
void test__iterator_get_typestyle__user_define(void** state)
{
    vector_t* pvec = NULL;
    vector_iterator_t it_iter;

    type_register(abc_t, NULL, NULL, NULL, NULL);
    pvec = create_vector(abc_t);
    vector_init(pvec);
    it_iter = vector_begin(pvec);
    assert_true(_iterator_get_typestyle(it_iter) == _TYPE_USER_DEFINE);
    vector_destroy(pvec);
}

/*
 * test _iterator_get_typebasename
 */
UT_CASE_DEFINATION(_iterator_get_typebasename)
void test__iterator_get_typebasename__invalid(void** state)
{
    iterator_t it_iter;
    it_iter._t_containertype = _VECTOR_CONTAINER;
    it_iter._t_iteratortype = 899;
    expect_assert_failure(_iterator_get_typebasename(it_iter));
}

void test__iterator_get_typebasename__c_builtin(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init(pvec);
    it_iter = vector_begin(pvec);
    assert_true(strcmp(_iterator_get_typebasename(it_iter), "int") == 0);
    vector_destroy(pvec);
}

void test__iterator_get_typebasename__libcstl_builtin(void** state)
{
    vector_t* pvec = create_vector(list_t<int>);
    vector_iterator_t it_iter;

    vector_init(pvec);
    it_iter = vector_begin(pvec);
    assert_true(strcmp(_iterator_get_typebasename(it_iter), "list_t") == 0);
    vector_destroy(pvec);
}

void test__iterator_get_typebasename__user_define(void** state)
{
    vector_t* pvec = NULL;
    vector_iterator_t it_iter;

    type_duplicate(abc_t, struct _tagabc);
    pvec = create_vector(struct _tagabc);
    vector_init(pvec);
    it_iter = vector_begin(pvec);
    assert_true(strcmp(_iterator_get_typebasename(it_iter), "abc_t") == 0);
    vector_destroy(pvec);
}

/*
 * test _iterator_get_typename
 */
UT_CASE_DEFINATION(_iterator_get_typename)
void test__iterator_get_typename__invalid(void** state)
{
    iterator_t it_iter;
    it_iter._t_containertype = _VECTOR_CONTAINER;
    it_iter._t_iteratortype = 899;
    expect_assert_failure(_iterator_get_typename(it_iter));
}

void test__iterator_get_typename__c_builtin(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init(pvec);
    it_iter = vector_begin(pvec);
    assert_true(strcmp(_iterator_get_typename(it_iter), "int") == 0);
    vector_destroy(pvec);
}

void test__iterator_get_typename__libcstl_builtin(void** state)
{
    vector_t* pvec = create_vector(list_t<int>);
    vector_iterator_t it_iter;

    vector_init(pvec);
    it_iter = vector_begin(pvec);
    assert_true(strcmp(_iterator_get_typename(it_iter), "list_t<int>") == 0);
    vector_destroy(pvec);
}

void test__iterator_get_typename__user_define(void** state)
{
    vector_t* pvec = create_vector(struct _tagabc);
    vector_iterator_t it_iter;

    vector_init(pvec);
    it_iter = vector_begin(pvec);
    assert_true(strcmp(_iterator_get_typename(it_iter), "struct _tagabc") == 0);
    vector_destroy(pvec);
}

/*
 * test _iterator_get_typecopy
 */
UT_CASE_DEFINATION(_iterator_get_typecopy)
void test__iterator_get_typecopy__invalid(void** state)
{
    iterator_t it_iter;
    it_iter._t_containertype = _VECTOR_CONTAINER;
    it_iter._t_iteratortype = 444;
    expect_assert_failure(_iterator_get_typecopy(it_iter));
}

void test__iterator_get_typecopy__c_builtin(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init(pvec);

    it_iter = vector_begin(pvec);
    /*assert_true(_iterator_get_typecopy(it_iter) == _type_copy_int);*/
    assert_true(_iterator_get_typecopy(it_iter) != NULL);

    vector_destroy(pvec);
}

void test__iterator_get_typecopy__cstl_builtin(void** state)
{
    vector_t* pvec = create_vector(list_t<int>);
    vector_iterator_t it_iter;

    vector_init(pvec);

    it_iter = vector_begin(pvec);
    /*assert_true(_iterator_get_typecopy(it_iter) == _type_copy_list);*/
    assert_true(_iterator_get_typecopy(it_iter) != NULL);

    vector_destroy(pvec);
}

void test__iterator_get_typecopy__user_define_default(void** state)
{
    vector_t* pvec = create_vector(abc_t);
    vector_iterator_t it_iter;

    vector_init(pvec);

    it_iter = vector_begin(pvec);
    /*assert_true(_iterator_get_typecopy(it_iter) == _type_copy_default);*/
    assert_true(_iterator_get_typecopy(it_iter) != NULL);

    vector_destroy(pvec);
}

typedef struct _tag_iterator_get_typecopy__user_define
{
    int n_elem;
}_iterator_get_typecopy__user_define_t;
void _iterator_get_typecopy__user_define_t_copy(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    ((_iterator_get_typecopy__user_define_t*)cpv_first)->n_elem = ((_iterator_get_typecopy__user_define_t*)cpv_second)->n_elem;
    *(bool_t*)pv_output = true;
}
void test__iterator_get_typecopy__user_define(void** state)
{
    vector_t* pvec = NULL;
    vector_iterator_t it_iter;

    type_register(_iterator_get_typecopy__user_define_t, NULL, _iterator_get_typecopy__user_define_t_copy, NULL, NULL);
    pvec = create_vector(_iterator_get_typecopy__user_define_t);
    vector_init(pvec);

    it_iter = vector_begin(pvec);
    assert_true(_iterator_get_typecopy(it_iter) == _iterator_get_typecopy__user_define_t_copy);

    vector_destroy(pvec);
}

/*
 * test _iterator_get_typesize
 */
UT_CASE_DEFINATION(_iterator_get_typesize)
void test__iterator_get_typesize__invalid(void** state)
{
    iterator_t it_iter;
    it_iter._t_containertype = _VECTOR_CONTAINER;
    it_iter._t_iteratortype = 4444;

    expect_assert_failure(_iterator_get_typesize(it_iter));
}

void test__iterator_get_typesize__c_builtin(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init(pvec);
    it_iter = vector_begin(pvec);
    assert_true(_iterator_get_typesize(it_iter) == sizeof(int));
    vector_destroy(pvec);
}

void test__iterator_get_typesize__cstl_builtin(void** state)
{
    vector_t* pvec = create_vector(list_t<int>);
    vector_iterator_t it_iter;

    vector_init(pvec);
    it_iter = vector_begin(pvec);
    assert_true(_iterator_get_typesize(it_iter) == sizeof(list_t));
    vector_destroy(pvec);
}

void test__iterator_get_typesize__user_define(void** state)
{
    vector_t* pvec = create_vector(abc_t);
    vector_iterator_t it_iter;

    vector_init(pvec);
    it_iter = vector_begin(pvec);
    assert_true(_iterator_get_typesize(it_iter) == sizeof(abc_t));
    vector_destroy(pvec);
}

/*
 * test _iterator_same_elem_type
 */
UT_CASE_DEFINATION(_iterator_same_elem_type)
void test__iterator_same_elem_type__invalid_first(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_first;
    iterator_t it_second;

    vector_init(pvec);
    it_second = vector_begin(pvec);
    it_first._t_containertype = _VECTOR_CONTAINER;
    it_first._t_iteratortype = 8888;
    expect_assert_failure(_iterator_same_elem_type(it_first, it_second));
    vector_destroy(pvec);
}

void test__iterator_same_elem_type__invalid_second(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_first;
    iterator_t it_second;

    vector_init(pvec);
    it_first = vector_begin(pvec);
    it_second._t_containertype = _VECTOR_CONTAINER;
    it_second._t_iteratortype = 8888;
    expect_assert_failure(_iterator_same_elem_type(it_first, it_second));
    vector_destroy(pvec);
}

void test__iterator_same_elem_type__c_builtin_not_same(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(long);

    vector_init(pvec_first);
    vector_init(pvec_second);
    assert_false(_iterator_same_elem_type(vector_begin(pvec_first), vector_begin(pvec_second)));
    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test__iterator_same_elem_type__c_builtin_same(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(signed);

    vector_init(pvec_first);
    vector_init(pvec_second);
    assert_true(_iterator_same_elem_type(vector_begin(pvec_first), vector_begin(pvec_second)));
    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test__iterator_same_elem_type__cstl_builtin_not_same_1(void** state)
{
    vector_t* pvec_first = create_vector(list_t<int>);
    vector_t* pvec_second = create_vector(slist_t<int>);

    vector_init(pvec_first);
    vector_init(pvec_second);
    assert_false(_iterator_same_elem_type(vector_begin(pvec_first), vector_begin(pvec_second)));
    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test__iterator_same_elem_type__cstl_builtin_not_same_2(void** state)
{
    vector_t* pvec_first = create_vector(list_t<int>);
    vector_t* pvec_second = create_vector(list_t<double>);

    vector_init(pvec_first);
    vector_init(pvec_second);
    assert_false(_iterator_same_elem_type(vector_begin(pvec_first), vector_begin(pvec_second)));
    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test__iterator_same_elem_type__cstl_builtin_same(void** state)
{
    vector_t* pvec_first = create_vector(list_t<int>);
    vector_t* pvec_second = create_vector(list_t<signed int>);

    vector_init(pvec_first);
    vector_init(pvec_second);
    assert_true(_iterator_same_elem_type(vector_begin(pvec_first), vector_begin(pvec_second)));
    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

typedef struct _tag_iterator_same_elem_type__user_define_1
{
    int n_elem;
}_iterator_same_elem_type__user_define_1_t;
typedef struct _tag_iterator_same_elem_type__user_define_2
{
    int n_elem;
}_iterator_same_elem_type__user_define_2_t;
void test__iterator_same_elem_type__user_define_not_same(void** state)
{
    vector_t* pvec_first = NULL;
    vector_t* pvec_second = NULL;

    type_register(_iterator_same_elem_type__user_define_1_t, NULL, NULL, NULL, NULL);
    type_register(_iterator_same_elem_type__user_define_2_t, NULL, NULL, NULL, NULL);
    pvec_first = create_vector(_iterator_same_elem_type__user_define_1_t);
    pvec_second = create_vector(_iterator_same_elem_type__user_define_2_t);

    assert_false(_iterator_same_elem_type(vector_begin(pvec_first), vector_begin(pvec_second)));
    
    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test__iterator_same_elem_type__user_define_same(void** state)
{
    vector_t* pvec_first = NULL;
    vector_t* pvec_second = NULL;

    type_duplicate(_iterator_same_elem_type__user_define_1_t, struct _tag_iterator_same_elem_type__user_define_1);
    type_duplicate(_iterator_same_elem_type__user_define_2_t, struct _tag_iterator_same_elem_type__user_define_2);
    pvec_first = create_vector(_iterator_same_elem_type__user_define_1_t);
    pvec_second = create_vector(struct _tag_iterator_same_elem_type__user_define_1);

    assert_true(_iterator_same_elem_type(vector_begin(pvec_first), vector_begin(pvec_second)));
    
    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test__iterator_same_elem_type__not_same_container_not_same_type(void** state)
{
    vector_t* pvec_first = create_vector(int);
    list_t* plist_second = create_list(long);

    vector_init(pvec_first);
    list_init(plist_second);
    assert_false(_iterator_same_elem_type(vector_begin(pvec_first), list_begin(plist_second)));
    vector_destroy(pvec_first);
    list_destroy(plist_second);
}

void test__iterator_same_elem_type__not_same_container_same_type(void** state)
{
    vector_t* pvec_first = create_vector(map_t<int, double>);
    list_t* plist_second = create_list(map_t<signed int, double>);

    vector_init(pvec_first);
    list_init(plist_second);
    assert_true(_iterator_same_elem_type(vector_begin(pvec_first), list_begin(plist_second)));
    vector_destroy(pvec_first);
    list_destroy(plist_second);
}

/*
 * test _iterator_allocate_init_elem and _iterator_deallocate_destroy_elem
 */
UT_CASE_DEFINATION(_iterator_allocate_init_elem__iterator_deallocate_destroy_elem)
typedef struct _tag_iterator_allocate_init_elem__user_define
{
    int n_elem;
}_iterator_allocate_init_elem__user_define_t;
void _iterator_allocate_init_eleme__user_define_init(const void* cpv_input, void* pv_output)
{
    ((_iterator_allocate_init_elem__user_define_t*)cpv_input)->n_elem = 999;
    *(bool_t*)pv_output = true;
}
void _iterator_allocate_init_elem__user_define_destroy(const void* cpv_input, void* pv_output)
{
    ((_iterator_allocate_init_elem__user_define_t*)cpv_input)->n_elem = 0;
    *(bool_t*)pv_output = true;
}
void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__allocate_invalid(void** state)
{
    iterator_t it_iter;
    it_iter._t_containertype = _VECTOR_CONTAINER;
    it_iter._t_iteratortype = 4444;
    expect_assert_failure(_iterator_allocate_init_elem(it_iter));
}

void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__deallocate_invalid(void** state)
{
    int n_elem = 999;
    iterator_t it_iter;
    it_iter._t_containertype = 9999;
    it_iter._t_iteratortype = _FORWARD_ITERATOR;
    expect_assert_failure(_iterator_deallocate_destroy_elem(it_iter, &n_elem));
}

void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__null_value(void** state)
{
    vector_t* pvec = create_vector(int);
    
    vector_init(pvec);
    expect_assert_failure(_iterator_deallocate_destroy_elem(vector_begin(pvec), NULL));
    vector_destroy(pvec);
}

void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__vector_c_builtin(void** state)
{
    vector_t* pvec = create_vector(int);
    int* pn_elem = NULL;

    vector_init(pvec);
    pn_elem = (int*)_iterator_allocate_init_elem(vector_begin(pvec));
    assert_true(pn_elem != NULL);
    assert_true(*pn_elem == 0);
    _iterator_deallocate_destroy_elem(vector_begin(pvec), pn_elem);
    vector_destroy(pvec);
}

void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__vector_cstl_builtin(void** state)
{
    vector_t* pvec = create_vector(list_t<int>);
    list_t* plist_elem = NULL;

    vector_init(pvec);
    plist_elem = (list_t*)_iterator_allocate_init_elem(vector_begin(pvec));
    assert_true(plist_elem != NULL);
    assert_true(_list_is_inited(plist_elem));
    _iterator_deallocate_destroy_elem(vector_begin(pvec), plist_elem);
    vector_destroy(pvec);
}

void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__vector_user_define(void** state)
{
    vector_t* pvec = NULL;
    _iterator_allocate_init_elem__user_define_t* pt_elem = NULL;

    type_register(_iterator_allocate_init_elem__user_define_t,
        _iterator_allocate_init_eleme__user_define_init, NULL, NULL, _iterator_allocate_init_elem__user_define_destroy);
    pvec = create_vector(_iterator_allocate_init_elem__user_define_t);
    vector_init(pvec);
    pt_elem = (_iterator_allocate_init_elem__user_define_t*)_iterator_allocate_init_elem(vector_begin(pvec));
    assert_true(pt_elem != NULL);
    assert_true(pt_elem->n_elem == 999);
    _iterator_deallocate_destroy_elem(vector_begin(pvec), pt_elem);
    vector_destroy(pvec);
}

void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__list_c_builtin(void** state)
{
    list_t* pvec = create_list(int);
    int* pn_elem = NULL;

    list_init(pvec);
    pn_elem = (int*)_iterator_allocate_init_elem(list_begin(pvec));
    assert_true(pn_elem != NULL);
    assert_true(*pn_elem == 0);
    _iterator_deallocate_destroy_elem(list_begin(pvec), pn_elem);
    list_destroy(pvec);
}

void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__list_cstl_builtin(void** state)
{
    list_t* pvec = create_list(list_t<int>);
    list_t* plist_elem = NULL;

    list_init(pvec);
    plist_elem = (list_t*)_iterator_allocate_init_elem(list_begin(pvec));
    assert_true(plist_elem != NULL);
    assert_true(_list_is_inited(plist_elem));
    _iterator_deallocate_destroy_elem(list_begin(pvec), plist_elem);
    list_destroy(pvec);
}

void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__list_user_define(void** state)
{
    list_t* pvec = NULL;
    _iterator_allocate_init_elem__user_define_t* pt_elem = NULL;

    pvec = create_list(_iterator_allocate_init_elem__user_define_t);
    list_init(pvec);
    pt_elem = (_iterator_allocate_init_elem__user_define_t*)_iterator_allocate_init_elem(list_begin(pvec));
    assert_true(pt_elem != NULL);
    assert_true(pt_elem->n_elem == 999);
    _iterator_deallocate_destroy_elem(list_begin(pvec), pt_elem);
    list_destroy(pvec);
}

void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__deque_c_builtin(void** state)
{
    deque_t* pvec = create_deque(int);
    int* pn_elem = NULL;

    deque_init(pvec);
    pn_elem = (int*)_iterator_allocate_init_elem(deque_begin(pvec));
    assert_true(pn_elem != NULL);
    assert_true(*pn_elem == 0);
    _iterator_deallocate_destroy_elem(deque_begin(pvec), pn_elem);
    deque_destroy(pvec);
}

void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__deque_cstl_builtin(void** state)
{
    deque_t* pvec = create_deque(list_t<int>);
    list_t* plist_elem = NULL;

    deque_init(pvec);
    plist_elem = (list_t*)_iterator_allocate_init_elem(deque_begin(pvec));
    assert_true(plist_elem != NULL);
    assert_true(_list_is_inited(plist_elem));
    _iterator_deallocate_destroy_elem(deque_begin(pvec), plist_elem);
    deque_destroy(pvec);
}

void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__deque_user_define(void** state)
{
    deque_t* pvec = NULL;
    _iterator_allocate_init_elem__user_define_t* pt_elem = NULL;

    pvec = create_deque(_iterator_allocate_init_elem__user_define_t);
    deque_init(pvec);
    pt_elem = (_iterator_allocate_init_elem__user_define_t*)_iterator_allocate_init_elem(deque_begin(pvec));
    assert_true(pt_elem != NULL);
    assert_true(pt_elem->n_elem == 999);
    _iterator_deallocate_destroy_elem(deque_begin(pvec), pt_elem);
    deque_destroy(pvec);
}

void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__slist_c_builtin(void** state)
{
    slist_t* pvec = create_slist(int);
    int* pn_elem = NULL;

    slist_init(pvec);
    pn_elem = (int*)_iterator_allocate_init_elem(slist_begin(pvec));
    assert_true(pn_elem != NULL);
    assert_true(*pn_elem == 0);
    _iterator_deallocate_destroy_elem(slist_begin(pvec), pn_elem);
    slist_destroy(pvec);
}

void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__slist_cstl_builtin(void** state)
{
    slist_t* pvec = create_slist(list_t<int>);
    list_t* plist_elem = NULL;

    slist_init(pvec);
    plist_elem = (list_t*)_iterator_allocate_init_elem(slist_begin(pvec));
    assert_true(plist_elem != NULL);
    assert_true(_list_is_inited(plist_elem));
    _iterator_deallocate_destroy_elem(slist_begin(pvec), plist_elem);
    slist_destroy(pvec);
}

void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__slist_user_define(void** state)
{
    slist_t* pvec = NULL;
    _iterator_allocate_init_elem__user_define_t* pt_elem = NULL;

    pvec = create_slist(_iterator_allocate_init_elem__user_define_t);
    slist_init(pvec);
    pt_elem = (_iterator_allocate_init_elem__user_define_t*)_iterator_allocate_init_elem(slist_begin(pvec));
    assert_true(pt_elem != NULL);
    assert_true(pt_elem->n_elem == 999);
    _iterator_deallocate_destroy_elem(slist_begin(pvec), pt_elem);
    slist_destroy(pvec);
}

void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__set_c_builtin(void** state)
{
    set_t* pvec = create_set(int);
    int* pn_elem = NULL;

    set_init(pvec);
    pn_elem = (int*)_iterator_allocate_init_elem(set_begin(pvec));
    assert_true(pn_elem != NULL);
    assert_true(*pn_elem == 0);
    _iterator_deallocate_destroy_elem(set_begin(pvec), pn_elem);
    set_destroy(pvec);
}

void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__set_cstl_builtin(void** state)
{
    set_t* pvec = create_set(list_t<int>);
    list_t* plist_elem = NULL;

    set_init(pvec);
    plist_elem = (list_t*)_iterator_allocate_init_elem(set_begin(pvec));
    assert_true(plist_elem != NULL);
    assert_true(_list_is_inited(plist_elem));
    _iterator_deallocate_destroy_elem(set_begin(pvec), plist_elem);
    set_destroy(pvec);
}

void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__set_user_define(void** state)
{
    set_t* pvec = NULL;
    _iterator_allocate_init_elem__user_define_t* pt_elem = NULL;

    pvec = create_set(_iterator_allocate_init_elem__user_define_t);
    set_init(pvec);
    pt_elem = (_iterator_allocate_init_elem__user_define_t*)_iterator_allocate_init_elem(set_begin(pvec));
    assert_true(pt_elem != NULL);
    assert_true(pt_elem->n_elem == 999);
    _iterator_deallocate_destroy_elem(set_begin(pvec), pt_elem);
    set_destroy(pvec);
}

void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__multiset_c_builtin(void** state)
{
    multiset_t* pvec = create_multiset(int);
    int* pn_elem = NULL;

    multiset_init(pvec);
    pn_elem = (int*)_iterator_allocate_init_elem(multiset_begin(pvec));
    assert_true(pn_elem != NULL);
    assert_true(*pn_elem == 0);
    _iterator_deallocate_destroy_elem(multiset_begin(pvec), pn_elem);
    multiset_destroy(pvec);
}

void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__multiset_cstl_builtin(void** state)
{
    multiset_t* pvec = create_multiset(list_t<int>);
    list_t* plist_elem = NULL;

    multiset_init(pvec);
    plist_elem = (list_t*)_iterator_allocate_init_elem(multiset_begin(pvec));
    assert_true(plist_elem != NULL);
    assert_true(_list_is_inited(plist_elem));
    _iterator_deallocate_destroy_elem(multiset_begin(pvec), plist_elem);
    multiset_destroy(pvec);
}

void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__multiset_user_define(void** state)
{
    multiset_t* pvec = NULL;
    _iterator_allocate_init_elem__user_define_t* pt_elem = NULL;

    pvec = create_multiset(_iterator_allocate_init_elem__user_define_t);
    multiset_init(pvec);
    pt_elem = (_iterator_allocate_init_elem__user_define_t*)_iterator_allocate_init_elem(multiset_begin(pvec));
    assert_true(pt_elem != NULL);
    assert_true(pt_elem->n_elem == 999);
    _iterator_deallocate_destroy_elem(multiset_begin(pvec), pt_elem);
    multiset_destroy(pvec);
}

void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__hash_set_c_builtin(void** state)
{
    hash_set_t* pvec = create_hash_set(int);
    int* pn_elem = NULL;

    hash_set_init(pvec);
    pn_elem = (int*)_iterator_allocate_init_elem(hash_set_begin(pvec));
    assert_true(pn_elem != NULL);
    assert_true(*pn_elem == 0);
    _iterator_deallocate_destroy_elem(hash_set_begin(pvec), pn_elem);
    hash_set_destroy(pvec);
}

void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__hash_set_cstl_builtin(void** state)
{
    hash_set_t* pvec = create_hash_set(list_t<int>);
    list_t* plist_elem = NULL;

    hash_set_init(pvec);
    plist_elem = (list_t*)_iterator_allocate_init_elem(hash_set_begin(pvec));
    assert_true(plist_elem != NULL);
    assert_true(_list_is_inited(plist_elem));
    _iterator_deallocate_destroy_elem(hash_set_begin(pvec), plist_elem);
    hash_set_destroy(pvec);
}

void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__hash_set_user_define(void** state)
{
    hash_set_t* pvec = NULL;
    _iterator_allocate_init_elem__user_define_t* pt_elem = NULL;

    pvec = create_hash_set(_iterator_allocate_init_elem__user_define_t);
    hash_set_init(pvec);
    pt_elem = (_iterator_allocate_init_elem__user_define_t*)_iterator_allocate_init_elem(hash_set_begin(pvec));
    assert_true(pt_elem != NULL);
    assert_true(pt_elem->n_elem == 999);
    _iterator_deallocate_destroy_elem(hash_set_begin(pvec), pt_elem);
    hash_set_destroy(pvec);
}

void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__hash_multiset_c_builtin(void** state)
{
    hash_multiset_t* pvec = create_hash_multiset(int);
    int* pn_elem = NULL;

    hash_multiset_init(pvec);
    pn_elem = (int*)_iterator_allocate_init_elem(hash_multiset_begin(pvec));
    assert_true(pn_elem != NULL);
    assert_true(*pn_elem == 0);
    _iterator_deallocate_destroy_elem(hash_multiset_begin(pvec), pn_elem);
    hash_multiset_destroy(pvec);
}

void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__hash_multiset_cstl_builtin(void** state)
{
    hash_multiset_t* pvec = create_hash_multiset(list_t<int>);
    list_t* plist_elem = NULL;

    hash_multiset_init(pvec);
    plist_elem = (list_t*)_iterator_allocate_init_elem(hash_multiset_begin(pvec));
    assert_true(plist_elem != NULL);
    assert_true(_list_is_inited(plist_elem));
    _iterator_deallocate_destroy_elem(hash_multiset_begin(pvec), plist_elem);
    hash_multiset_destroy(pvec);
}

void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__hash_multiset_user_define(void** state)
{
    hash_multiset_t* pvec = NULL;
    _iterator_allocate_init_elem__user_define_t* pt_elem = NULL;

    pvec = create_hash_multiset(_iterator_allocate_init_elem__user_define_t);
    hash_multiset_init(pvec);
    pt_elem = (_iterator_allocate_init_elem__user_define_t*)_iterator_allocate_init_elem(hash_multiset_begin(pvec));
    assert_true(pt_elem != NULL);
    assert_true(pt_elem->n_elem == 999);
    _iterator_deallocate_destroy_elem(hash_multiset_begin(pvec), pt_elem);
    hash_multiset_destroy(pvec);
}

void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__map_c_builtin(void** state)
{
    map_t* pvec = create_map(int, int);
    pair_t* ppair = NULL;

    map_init(pvec);
    ppair = (pair_t*)_iterator_allocate_init_elem(map_begin(pvec));
    assert_true(ppair != NULL);
    assert_true(*(int*)pair_first(ppair) == 0);
    _iterator_deallocate_destroy_elem(map_begin(pvec), ppair);
    map_destroy(pvec);
}

void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__map_cstl_builtin(void** state)
{
    map_t* pvec = create_map(list_t<int>, int);
    pair_t* ppair = NULL;

    map_init(pvec);
    ppair = (pair_t*)_iterator_allocate_init_elem(map_begin(pvec));
    assert_true(ppair != NULL);
    assert_true(_list_is_inited((list_t*)pair_first(ppair)));
    _iterator_deallocate_destroy_elem(map_begin(pvec), ppair);
    map_destroy(pvec);
}

void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__map_user_define(void** state)
{
    map_t* pvec = NULL;
    pair_t* ppair = NULL;

    pvec = create_map(_iterator_allocate_init_elem__user_define_t, int);
    map_init(pvec);
    ppair = (pair_t*)_iterator_allocate_init_elem(map_begin(pvec));
    assert_true(ppair != NULL);
    assert_true(((_iterator_allocate_init_elem__user_define_t*)pair_first(ppair))->n_elem == 999);
    _iterator_deallocate_destroy_elem(map_begin(pvec), ppair);
    map_destroy(pvec);
}

void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__multimap_c_builtin(void** state)
{
    multimap_t* pvec = create_multimap(int, int);
    pair_t* ppair = NULL;

    multimap_init(pvec);
    ppair = (pair_t*)_iterator_allocate_init_elem(multimap_begin(pvec));
    assert_true(ppair != NULL);
    assert_true(*(int*)pair_first(ppair) == 0);
    _iterator_deallocate_destroy_elem(multimap_begin(pvec), ppair);
    multimap_destroy(pvec);
}

void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__multimap_cstl_builtin(void** state)
{
    multimap_t* pvec = create_multimap(list_t<int>, int);
    pair_t* ppair = NULL;

    multimap_init(pvec);
    ppair = (pair_t*)_iterator_allocate_init_elem(multimap_begin(pvec));
    assert_true(ppair != NULL);
    assert_true(_list_is_inited((list_t*)pair_first(ppair)));
    _iterator_deallocate_destroy_elem(multimap_begin(pvec), ppair);
    multimap_destroy(pvec);
}

void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__multimap_user_define(void** state)
{
    multimap_t* pvec = NULL;
    pair_t* ppair = NULL;

    pvec = create_multimap(_iterator_allocate_init_elem__user_define_t, int);
    multimap_init(pvec);
    ppair = (pair_t*)_iterator_allocate_init_elem(multimap_begin(pvec));
    assert_true(ppair != NULL);
    assert_true(((_iterator_allocate_init_elem__user_define_t*)pair_first(ppair))->n_elem == 999);
    _iterator_deallocate_destroy_elem(multimap_begin(pvec), ppair);
    multimap_destroy(pvec);
}

void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__hash_map_c_builtin(void** state)
{
    hash_map_t* pvec = create_hash_map(int, int);
    pair_t* ppair = NULL;

    hash_map_init(pvec);
    ppair = (pair_t*)_iterator_allocate_init_elem(hash_map_begin(pvec));
    assert_true(ppair != NULL);
    assert_true(*(int*)pair_first(ppair) == 0);
    _iterator_deallocate_destroy_elem(hash_map_begin(pvec), ppair);
    hash_map_destroy(pvec);
}

void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__hash_map_cstl_builtin(void** state)
{
    hash_map_t* pvec = create_hash_map(list_t<int>, int);
    pair_t* ppair = NULL;

    hash_map_init(pvec);
    ppair = (pair_t*)_iterator_allocate_init_elem(hash_map_begin(pvec));
    assert_true(ppair != NULL);
    assert_true(_list_is_inited((list_t*)pair_first(ppair)));
    _iterator_deallocate_destroy_elem(hash_map_begin(pvec), ppair);
    hash_map_destroy(pvec);
}

void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__hash_map_user_define(void** state)
{
    hash_map_t* pvec = NULL;
    pair_t* ppair = NULL;

    pvec = create_hash_map(_iterator_allocate_init_elem__user_define_t, int);
    hash_map_init(pvec);
    ppair = (pair_t*)_iterator_allocate_init_elem(hash_map_begin(pvec));
    assert_true(ppair != NULL);
    assert_true(((_iterator_allocate_init_elem__user_define_t*)pair_first(ppair))->n_elem == 999);
    _iterator_deallocate_destroy_elem(hash_map_begin(pvec), ppair);
    hash_map_destroy(pvec);
}

void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__hash_multimap_c_builtin(void** state)
{
    hash_multimap_t* pvec = create_hash_multimap(int, int);
    pair_t* ppair = NULL;

    hash_multimap_init(pvec);
    ppair = (pair_t*)_iterator_allocate_init_elem(hash_multimap_begin(pvec));
    assert_true(ppair != NULL);
    assert_true(*(int*)pair_first(ppair) == 0);
    _iterator_deallocate_destroy_elem(hash_multimap_begin(pvec), ppair);
    hash_multimap_destroy(pvec);
}

void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__hash_multimap_cstl_builtin(void** state)
{
    hash_multimap_t* pvec = create_hash_multimap(list_t<int>, int);
    pair_t* ppair = NULL;

    hash_multimap_init(pvec);
    ppair = (pair_t*)_iterator_allocate_init_elem(hash_multimap_begin(pvec));
    assert_true(ppair != NULL);
    assert_true(_list_is_inited((list_t*)pair_first(ppair)));
    _iterator_deallocate_destroy_elem(hash_multimap_begin(pvec), ppair);
    hash_multimap_destroy(pvec);
}

void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__hash_multimap_user_define(void** state)
{
    hash_multimap_t* pvec = NULL;
    pair_t* ppair = NULL;

    pvec = create_hash_multimap(_iterator_allocate_init_elem__user_define_t, int);
    hash_multimap_init(pvec);
    ppair = (pair_t*)_iterator_allocate_init_elem(hash_multimap_begin(pvec));
    assert_true(ppair != NULL);
    assert_true(((_iterator_allocate_init_elem__user_define_t*)pair_first(ppair))->n_elem == 999);
    _iterator_deallocate_destroy_elem(hash_multimap_begin(pvec), ppair);
    hash_multimap_destroy(pvec);
}

void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__string(void** state)
{
    string_t* pstr = create_string();
    char* pc = NULL;

    string_init(pstr);
    pc = (char*)_iterator_allocate_init_elem(string_begin(pstr));
    assert_true(pc != NULL);
    assert_true(*pc == 0x00);
    _iterator_deallocate_destroy_elem(string_begin(pstr), pc);
    string_destroy(pstr);
}

