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

#include "ut_def.h"
#include "ut_cstl_iterator.h"

UT_SUIT_DEFINATION(cstl_iterator, iterator_get_value)

/*
 * test iterator_get_value
 */
UT_CASE_DEFINATION(iterator_get_value)
void test_iterator_get_value__invalid_iter(void** state)
{
    int n;
    iterator_t it_iter;
    it_iter._t_containertype = 999;
    it_iter._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(iterator_get_value(it_iter, &n));
}

void test_iterator_get_value__null(void** state)
{
    vector_t* pvec = create_vector(int);

    vector_init_elem(pvec, 10, 10);
    expect_assert_failure(iterator_get_value(vector_begin(pvec), NULL));
    vector_destroy(pvec);
}

void test_iterator_get_value__vector(void** state)
{
    vector_t* pvec = create_vector(int);
    int n = 0;

    vector_init_elem(pvec, 10, 999);
    iterator_get_value(vector_begin(pvec), &n);
    assert_true(n == 999);
    vector_destroy(pvec);
}

void test_iterator_get_value__deque(void** state)
{
    deque_t* pdeq = create_deque(int);
    int n = 0;

    deque_init_elem(pdeq, 10, 1000);
    iterator_get_value(deque_begin(pdeq), &n);
    assert_true(n == 1000);
    deque_destroy(pdeq);
}

void test_iterator_get_value__list(void** state)
{
    list_t* plist = create_list(int);
    int n = 0;

    list_init_elem(plist, 10, 1000);
    iterator_get_value(list_begin(plist), &n);
    assert_true(n == 1000);
    list_destroy(plist);
}

void test_iterator_get_value__slist(void** state)
{
    slist_t* pslist = create_slist(int);
    int n = 0;

    slist_init_elem(pslist, 10, 9999);
    iterator_get_value(slist_begin(pslist), &n);
    assert_true(n == 9999);
    slist_destroy(pslist);
}

void test_iterator_get_value__set(void** state)
{
    set_t* pset = create_set(int);
    int n = 0;

    set_init(pset);
    set_insert(pset, 100);
    iterator_get_value(set_begin(pset), &n);
    assert_true(n == 100);
    set_destroy(pset);
}

void test_iterator_get_value__multiset(void** state)
{
    multiset_t* pmset = create_multiset(int);
    int n = 0;

    multiset_init(pmset);
    multiset_insert(pmset, 100);
    iterator_get_value(multiset_begin(pmset), &n);
    assert_true(n == 100);
    multiset_destroy(pmset);
}

void test_iterator_get_value__map(void** state)
{
    map_t* pmap = create_map(int, int);
    pair_t* ppair = create_pair(int, int);

    map_init(pmap);
    pair_init(ppair);
    *(int*)map_at(pmap, 10) = 10;
    iterator_get_value(map_begin(pmap), ppair);
    assert_true(*(int*)pair_first(ppair) == 10);
    assert_true(*(int*)pair_second(ppair) == 10);
    pair_destroy(ppair);
    map_destroy(pmap);
}

void test_iterator_get_value__multimap(void** state)
{
    multimap_t* pmmap = create_multimap(int, int);
    pair_t* ppair = create_pair(int, int);

    multimap_init(pmmap);
    pair_init_elem(ppair, 100, 333);
    multimap_insert(pmmap, ppair);
    pair_make(ppair, 0, 0);
    iterator_get_value(multimap_begin(pmmap), ppair);
    assert_true(*(int*)pair_first(ppair) == 100);
    assert_true(*(int*)pair_second(ppair) == 333);
    pair_destroy(ppair);
    multimap_destroy(pmmap);
}

void test_iterator_get_value__hash_set(void** state)
{
    hash_set_t* phset = create_hash_set(int);
    int n = 0;

    hash_set_init(phset);
    hash_set_insert(phset, 100);
    iterator_get_value(hash_set_begin(phset), &n);
    assert_true(n == 100);
    hash_set_destroy(phset);
}

void test_iterator_get_value__hash_multiset(void** state)
{
    hash_multiset_t* phmset = create_hash_multiset(int);
    int n = 0;

    hash_multiset_init(phmset);
    hash_multiset_insert(phmset, 100);
    iterator_get_value(hash_multiset_begin(phmset), &n);
    assert_true(n == 100);
    hash_multiset_destroy(phmset);
}

void test_iterator_get_value__hash_map(void** state)
{
    hash_map_t* phmap = create_hash_map(int, int);
    pair_t* ppair = create_pair(int, int);

    hash_map_init(phmap);
    pair_init_elem(ppair, 1, 2);
    hash_map_insert(phmap, ppair);
    pair_make(ppair, 0, 0);
    iterator_get_value(hash_map_begin(phmap), ppair);
    assert_true(*(int*)pair_first(ppair) == 1);
    assert_true(*(int*)pair_second(ppair) == 2);
    pair_destroy(ppair);
    hash_map_destroy(phmap);
}

void test_iterator_get_value__hash_multimap(void** state)
{
    hash_multimap_t* phmmap = create_hash_multimap(int, int);
    pair_t* ppair = create_pair(int, int);

    hash_multimap_init(phmmap);
    pair_init_elem(ppair, 4, 5);
    hash_multimap_insert(phmmap, ppair);
    pair_make(ppair, 0, 0);
    iterator_get_value(hash_multimap_begin(phmmap), ppair);
    assert_true(*(int*)pair_first(ppair) == 4);
    assert_true(*(int*)pair_second(ppair) == 5);
    pair_destroy(ppair);
    hash_multimap_destroy(phmmap);
}

void test_iterator_get_value__string(void** state)
{
    string_t* pstr = create_string();
    char c = '\0';

    string_init_cstr(pstr, "abcdefg");
    iterator_get_value(string_begin(pstr), &c);
    assert_true(c == 'a');
    string_destroy(pstr);
}

/*
 * test iterator_set_value
 */
UT_CASE_DEFINATION(iterator_set_value)
void test_iterator_set_value__invalid_iter(void** state)
{
    int n = 9;
    iterator_t it_iter;
    it_iter._t_iteratortype = 3333;
    it_iter._t_containertype = _VECTOR_CONTAINER;

    expect_assert_failure(iterator_set_value(it_iter, &n));
}

void test_iterator_set_value__null(void** state)
{
    vector_t* pvec = create_vector(int);

    vector_init_elem(pvec, 10, 10);
    expect_assert_failure(iterator_set_value(vector_begin(pvec), NULL));
    vector_destroy(pvec);
}

void test_iterator_set_value__vector(void** state)
{
    vector_t* pvec = create_vector(int);
    int n = 0;

    vector_init_elem(pvec, 10, 999);
    iterator_set_value(vector_begin(pvec), &n);
    assert_true(*(int*)iterator_get_pointer(vector_begin(pvec)) == 0);
    vector_destroy(pvec);
}

void test_iterator_set_value__deque(void** state)
{
    deque_t* pdeq = create_deque(int);
    int n = 0;

    deque_init_elem(pdeq, 10, 1000);
    iterator_set_value(deque_begin(pdeq), &n);
    assert_true(*(int*)iterator_get_pointer(deque_begin(pdeq)) == 0);
    deque_destroy(pdeq);
}

void test_iterator_set_value__list(void** state)
{
    list_t* plist = create_list(int);
    int n = 0;

    list_init_elem(plist, 10, 1000);
    iterator_set_value(list_begin(plist), &n);
    assert_true(*(int*)iterator_get_pointer(list_begin(plist)) == 0);
    list_destroy(plist);
}

void test_iterator_set_value__slist(void** state)
{
    slist_t* pslist = create_slist(int);
    int n = 0;

    slist_init_elem(pslist, 10, 9999);
    iterator_set_value(slist_begin(pslist), &n);
    assert_true(*(int*)iterator_get_pointer(slist_begin(pslist)) == 0);
    slist_destroy(pslist);
}

void test_iterator_set_value__set(void** state)
{
    set_t* pset = create_set(int);
    int n = 0;

    set_init(pset);
    set_insert(pset, 100);
    expect_assert_failure(iterator_set_value(set_begin(pset), &n));
    set_destroy(pset);
}

void test_iterator_set_value__multiset(void** state)
{
    multiset_t* pmset = create_multiset(int);
    int n = 0;

    multiset_init(pmset);
    multiset_insert(pmset, 100);
    expect_assert_failure(iterator_set_value(multiset_begin(pmset), &n));
    multiset_destroy(pmset);
}

void test_iterator_set_value__map(void** state)
{
    map_t* pmap = create_map(int, int);
    pair_t* ppair = create_pair(int, int);

    map_init(pmap);
    pair_init(ppair);
    *(int*)map_at(pmap, 10) = 10;
    expect_assert_failure(iterator_set_value(map_begin(pmap), ppair));
    pair_destroy(ppair);
    map_destroy(pmap);
}

void test_iterator_set_value__multimap(void** state)
{
    multimap_t* pmmap = create_multimap(int, int);
    pair_t* ppair = create_pair(int, int);

    multimap_init(pmmap);
    pair_init_elem(ppair, 100, 333);
    multimap_insert(pmmap, ppair);
    pair_make(ppair, 0, 0);
    expect_assert_failure(iterator_set_value(multimap_begin(pmmap), ppair));
    pair_destroy(ppair);
    multimap_destroy(pmmap);
}

void test_iterator_set_value__hash_set(void** state)
{
    hash_set_t* phset = create_hash_set(int);
    int n = 0;

    hash_set_init(phset);
    hash_set_insert(phset, 100);
    expect_assert_failure(iterator_set_value(hash_set_begin(phset), &n));
    hash_set_destroy(phset);
}

void test_iterator_set_value__hash_multiset(void** state)
{
    hash_multiset_t* phmset = create_hash_multiset(int);
    int n = 0;

    hash_multiset_init(phmset);
    hash_multiset_insert(phmset, 100);
    expect_assert_failure(iterator_set_value(hash_multiset_begin(phmset), &n));
    hash_multiset_destroy(phmset);
}

void test_iterator_set_value__hash_map(void** state)
{
    hash_map_t* phmap = create_hash_map(int, int);
    pair_t* ppair = create_pair(int, int);

    hash_map_init(phmap);
    pair_init_elem(ppair, 1, 2);
    hash_map_insert(phmap, ppair);
    pair_make(ppair, 0, 0);
    expect_assert_failure(iterator_set_value(hash_map_begin(phmap), ppair));
    pair_destroy(ppair);
    hash_map_destroy(phmap);
}

void test_iterator_set_value__hash_multimap(void** state)
{
    hash_multimap_t* phmmap = create_hash_multimap(int, int);
    pair_t* ppair = create_pair(int, int);

    hash_multimap_init(phmmap);
    pair_init_elem(ppair, 4, 5);
    hash_multimap_insert(phmmap, ppair);
    pair_make(ppair, 0, 0);
    expect_assert_failure(iterator_set_value(hash_multimap_begin(phmmap), ppair));
    pair_destroy(ppair);
    hash_multimap_destroy(phmmap);
}

void test_iterator_set_value__string(void** state)
{
    string_t* pstr = create_string();
    char c = '0';

    string_init_cstr(pstr, "abcdefg");
    iterator_set_value(string_begin(pstr), &c);
    assert_true(strcmp(string_c_str(pstr), "0bcdefg") == 0);
    string_destroy(pstr);
}

/*
 * test iterator_get_pointer
 */
UT_CASE_DEFINATION(iterator_get_pointer)
void test_iterator_get_pointer__invalid_iter(void** state)
{
    iterator_t it_iter;
    it_iter._t_containertype = 999;
    it_iter._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(iterator_get_pointer(it_iter));
}

void test_iterator_get_pointer__vector(void** state)
{
    vector_t* pvec = create_vector(int);

    vector_init_elem(pvec, 10, 999);
    assert_true(*(int*)iterator_get_pointer(vector_begin(pvec)) == 999);
    vector_destroy(pvec);
}

void test_iterator_get_pointer__deque(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_elem(pdeq, 10, 1000);
    assert_true(*(int*)iterator_get_pointer(deque_begin(pdeq)) == 1000);
    deque_destroy(pdeq);
}

void test_iterator_get_pointer__list(void** state)
{
    list_t* plist = create_list(int);

    list_init_elem(plist, 10, 1000);
    assert_true(*(int*)iterator_get_pointer(list_begin(plist)) == 1000);
    list_destroy(plist);
}

void test_iterator_get_pointer__slist(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init_elem(pslist, 10, 9999);
    assert_true(*(int*)iterator_get_pointer(slist_begin(pslist)) == 9999);
    slist_destroy(pslist);
}

void test_iterator_get_pointer__set(void** state)
{
    set_t* pset = create_set(int);

    set_init(pset);
    set_insert(pset, 100);
    assert_true(*(int*)iterator_get_pointer(set_begin(pset)) == 100);
    set_destroy(pset);
}

void test_iterator_get_pointer__multiset(void** state)
{
    multiset_t* pmset = create_multiset(int);

    multiset_init(pmset);
    multiset_insert(pmset, 100);
    assert_true(*(int*)iterator_get_pointer(multiset_begin(pmset)) == 100);
    multiset_destroy(pmset);
}

void test_iterator_get_pointer__map(void** state)
{
    map_t* pmap = create_map(int, int);
    pair_t* ppair = NULL;

    map_init(pmap);
    *(int*)map_at(pmap, 10) = 10;
    ppair = (pair_t*)iterator_get_pointer(map_begin(pmap));
    assert_true(*(int*)pair_first(ppair) == 10);
    assert_true(*(int*)pair_second(ppair) == 10);
    map_destroy(pmap);
}

void test_iterator_get_pointer__multimap(void** state)
{
    multimap_t* pmmap = create_multimap(int, int);
    pair_t* ppair = create_pair(int, int);

    multimap_init(pmmap);
    pair_init_elem(ppair, 100, 333);
    multimap_insert(pmmap, ppair);
    pair_make(ppair, 0, 0);
    assert_true(*(int*)pair_first(iterator_get_pointer(multimap_begin(pmmap))) == 100);
    assert_true(*(int*)pair_second(iterator_get_pointer(multimap_begin(pmmap))) == 333);
    pair_destroy(ppair);
    multimap_destroy(pmmap);
}

void test_iterator_get_pointer__hash_set(void** state)
{
    hash_set_t* phset = create_hash_set(int);

    hash_set_init(phset);
    hash_set_insert(phset, 100);
    assert_true(*(int*)iterator_get_pointer(hash_set_begin(phset)) == 100);
    hash_set_destroy(phset);
}

void test_iterator_get_pointer__hash_multiset(void** state)
{
    hash_multiset_t* phmset = create_hash_multiset(int);

    hash_multiset_init(phmset);
    hash_multiset_insert(phmset, 100);
    assert_true(*(int*)iterator_get_pointer(hash_multiset_begin(phmset)) == 100);
    hash_multiset_destroy(phmset);
}

void test_iterator_get_pointer__hash_map(void** state)
{
    hash_map_t* phmap = create_hash_map(int, int);
    pair_t* ppair = create_pair(int, int);

    hash_map_init(phmap);
    pair_init_elem(ppair, 1, 2);
    hash_map_insert(phmap, ppair);
    pair_make(ppair, 0, 0);
    assert_true(*(int*)pair_first(iterator_get_pointer(hash_map_begin(phmap))) == 1);
    assert_true(*(int*)pair_second(iterator_get_pointer(hash_map_begin(phmap))) == 2);
    pair_destroy(ppair);
    hash_map_destroy(phmap);
}

void test_iterator_get_pointer__hash_multimap(void** state)
{
    hash_multimap_t* phmmap = create_hash_multimap(int, int);
    pair_t* ppair = create_pair(int, int);

    hash_multimap_init(phmmap);
    pair_init_elem(ppair, 4, 5);
    hash_multimap_insert(phmmap, ppair);
    pair_make(ppair, 0, 0);
    assert_true(*(int*)pair_first(iterator_get_pointer(hash_multimap_begin(phmmap))) == 4);
    assert_true(*(int*)pair_second(iterator_get_pointer(hash_multimap_begin(phmmap))) == 5);
    pair_destroy(ppair);
    hash_multimap_destroy(phmmap);
}

void test_iterator_get_pointer__string(void** state)
{
    string_t* pstr = create_string();
    char c = '\0';

    string_init_cstr(pstr, "abcdefg");
    assert_true(*(char*)iterator_get_pointer(string_begin(pstr)) == 'a');
    string_destroy(pstr);
}

/*
 * test iterator_next
 */
UT_CASE_DEFINATION(iterator_next)
void test_iterator_next__invalid_iter(void** state)
{
    iterator_t it_iter;
    it_iter._t_containertype = 999;
    it_iter._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(iterator_next(it_iter));
}

void test_iterator_next__vector(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_iter;

    vector_init(pvec);
    vector_push_back(pvec, 1);
    vector_push_back(pvec, 2);
    vector_push_back(pvec, 3);

    it_iter = vector_begin(pvec);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);

    vector_destroy(pvec);
}

void test_iterator_next__vector_end(void** state)
{
    vector_t* pvec = create_vector(int);
    
    vector_init(pvec);
    expect_assert_failure(iterator_next(vector_end(pvec)));
    vector_destroy(pvec);
}

void test_iterator_next__deque(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it_iter;

    deque_init(pdeq);
    deque_push_back(pdeq, 1);
    deque_push_back(pdeq, 2);

    it_iter = deque_begin(pdeq);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    deque_destroy(pdeq);
}

void test_iterator_next__deque_end(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    expect_assert_failure(iterator_next(deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test_iterator_next__list(void** state)
{
    list_t* plist = create_list(int);
    iterator_t it_iter;

    list_init(plist);
    list_push_back(plist, 1);
    list_push_back(plist, 2);

    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);

    list_destroy(plist);
}

void test_iterator_next__list_end(void** state)
{
    list_t* plist = create_list(int);

    list_init(plist);
    expect_assert_failure(iterator_next(list_end(plist)));
    list_destroy(plist);
}

void test_iterator_next__slist(void** state)
{
    slist_t* pslist = create_slist(int);
    iterator_t it_iter;

    slist_init(pslist);
    slist_push_front(pslist, 1);
    slist_push_front(pslist, 2);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    slist_destroy(pslist);
}

void test_iterator_next__slist_end(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    expect_assert_failure(iterator_next(slist_end(pslist)));
    slist_destroy(pslist);
}

void test_iterator_next__set(void** state)
{
    set_t* pset = create_set(int);
    iterator_t it_iter;

    set_init(pset);
    set_insert(pset, 1);
    set_insert(pset, 2);
    it_iter = set_begin(pset);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    set_destroy(pset);
}

void test_iterator_next__set_end(void** state)
{
    set_t* pset = create_set(int);

    set_init(pset);
    expect_assert_failure(iterator_next(set_end(pset)));
    set_destroy(pset);
}

void test_iterator_next__multiset(void** state)
{
    multiset_t* pmset = create_multiset(int);
    iterator_t it_iter;

    multiset_init(pmset);
    multiset_insert(pmset, 1);
    multiset_insert(pmset, 2);
    it_iter = multiset_begin(pmset);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    multiset_destroy(pmset);
}

void test_iterator_next__multiset_end(void** state)
{
    multiset_t* pmset = create_multiset(int);

    multiset_init(pmset);
    expect_assert_failure(iterator_next(multiset_end(pmset)));
    multiset_destroy(pmset);
}

void test_iterator_next__map(void** state)
{
    map_t* pmap = create_map(int, int);
    iterator_t it_iter;

    map_init(pmap);
    *(int*)map_at(pmap, 1) = 10;
    *(int*)map_at(pmap, 2) = 20;
    it_iter = map_begin(pmap);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 2);
    map_destroy(pmap);
}

void test_iterator_next__map_end(void** state)
{
    map_t* pmap = create_map(int, int);

    map_init(pmap);
    expect_assert_failure(iterator_next(map_end(pmap)));
    map_destroy(pmap);
}

void test_iterator_next__multimap(void** state)
{
    multimap_t* pmmap = create_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_iter;

    multimap_init(pmmap);
    pair_init(ppair);
    pair_make(ppair, 1, 1);
    multimap_insert(pmmap, ppair);
    pair_make(ppair, 2, 2);
    multimap_insert(pmmap, ppair);
    it_iter = multimap_begin(pmmap);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 2);
    pair_destroy(ppair);
    multimap_destroy(pmmap);
}

void test_iterator_next__multimap_end(void** state)
{
    multimap_t* pmmap = create_multimap(int, int);

    multimap_init(pmmap);
    expect_assert_failure(iterator_next(multimap_end(pmmap)));
    multimap_destroy(pmmap);
}

void test_iterator_next__hash_set(void** state)
{
    hash_set_t* phset = create_hash_set(int);
    iterator_t it_iter;

    hash_set_init(phset);
    hash_set_insert(phset, 1);
    hash_set_insert(phset, 2);
    it_iter = hash_set_begin(phset);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    hash_set_destroy(phset);
}

void test_iterator_next__hash_set_end(void** state)
{
    hash_set_t* phset = create_hash_set(int);

    hash_set_init(phset);
    expect_assert_failure(iterator_next(hash_set_end(phset)));
    hash_set_destroy(phset);
}

void test_iterator_next__hash_multiset(void** state)
{
    hash_multiset_t* phmset = create_hash_multiset(int);
    iterator_t it_iter;

    hash_multiset_init(phmset);
    hash_multiset_insert(phmset, 1);
    hash_multiset_insert(phmset, 2);
    it_iter = hash_multiset_begin(phmset);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    hash_multiset_destroy(phmset);
}

void test_iterator_next__hash_multiset_end(void** state)
{
    hash_multiset_t* phmset = create_hash_multiset(int);

    hash_multiset_init(phmset);
    expect_assert_failure(iterator_next(hash_multiset_end(phmset)));
    hash_multiset_destroy(phmset);
}

void test_iterator_next__hash_map(void** state)
{
    hash_map_t* phmap = create_hash_map(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_iter;

    hash_map_init(phmap);
    pair_init(ppair);
    pair_make(ppair, 0, 0);
    hash_map_insert(phmap, ppair);
    pair_make(ppair, 1, 1);
    hash_map_insert(phmap, ppair);
    it_iter = hash_map_begin(phmap);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 1);
    pair_destroy(ppair);
    hash_map_destroy(phmap);
}

void test_iterator_next__hash_map_end(void** state)
{
    hash_map_t* phmap = create_hash_map(int, int);

    hash_map_init(phmap);
    expect_assert_failure(iterator_next(hash_map_end(phmap)));
    hash_map_destroy(phmap);
}

void test_iterator_next__hash_multimap(void** state)
{
    hash_multimap_t* phmap = create_hash_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_iter;

    hash_multimap_init(phmap);
    pair_init(ppair);
    pair_make(ppair, 0, 0);
    hash_multimap_insert(phmap, ppair);
    pair_make(ppair, 1, 1);
    hash_multimap_insert(phmap, ppair);
    it_iter = hash_multimap_begin(phmap);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 1);
    pair_destroy(ppair);
    hash_multimap_destroy(phmap);
}

void test_iterator_next__hash_multimap_end(void** state)
{
    hash_multimap_t* phmap = create_hash_multimap(int, int);

    hash_multimap_init(phmap);
    expect_assert_failure(iterator_next(hash_multimap_end(phmap)));
    hash_multimap_destroy(phmap);
}

void test_iterator_next__string(void** state)
{
    string_t* pstr = create_string();
    iterator_t it_iter;

    string_init_cstr(pstr, "abcdefg");
    it_iter = string_begin(pstr);
    assert_true(*(char*)iterator_get_pointer(it_iter) == 'a');
    it_iter = iterator_next(it_iter);
    assert_true(*(char*)iterator_get_pointer(it_iter) == 'b');
    string_destroy(pstr);
}

void test_iterator_next__string_end(void** state)
{
    string_t* pstr = create_string();

    string_init(pstr);
    expect_assert_failure(iterator_next(string_end(pstr)));
    string_destroy(pstr);
}

/*
 * test iterator_prev
 */
UT_CASE_DEFINATION(iterator_prev)
void test_iterator_prev__invalid_iter(void** state)
{
    iterator_t it_iter;
    it_iter._t_containertype = 999;
    it_iter._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(iterator_prev(it_iter));
}

void test_iterator_prev__vector(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_iter;

    vector_init(pvec);
    vector_push_back(pvec, 1);
    vector_push_back(pvec, 2);
    vector_push_back(pvec, 3);

    it_iter = iterator_next(vector_begin(pvec));
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_prev(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);

    vector_destroy(pvec);
}

void test_iterator_prev__vector_begin(void** state)
{
    vector_t* pvec = create_vector(int);
    
    vector_init(pvec);
    expect_assert_failure(iterator_prev(vector_begin(pvec)));
    vector_destroy(pvec);
}

void test_iterator_prev__deque(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it_iter;

    deque_init(pdeq);
    deque_push_back(pdeq, 1);
    deque_push_back(pdeq, 2);

    it_iter = iterator_next(deque_begin(pdeq));
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_prev(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    deque_destroy(pdeq);
}

void test_iterator_prev__deque_begin(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    expect_assert_failure(iterator_prev(deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test_iterator_prev__list(void** state)
{
    list_t* plist = create_list(int);
    iterator_t it_iter;

    list_init(plist);
    list_push_back(plist, 1);
    list_push_back(plist, 2);

    it_iter = iterator_next(list_begin(plist));
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_prev(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);

    list_destroy(plist);
}

void test_iterator_prev__list_begin(void** state)
{
    list_t* plist = create_list(int);

    list_init(plist);
    expect_assert_failure(iterator_prev(list_begin(plist)));
    list_destroy(plist);
}

void test_iterator_prev__slist(void** state)
{
    slist_t* pslist = create_slist(int);
    iterator_t it_iter;

    slist_init(pslist);
    slist_push_front(pslist, 1);
    slist_push_front(pslist, 2);
    it_iter = iterator_next(slist_begin(pslist));
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    expect_assert_failure(iterator_prev(it_iter));
    slist_destroy(pslist);
}

void test_iterator_prev__slist_begin(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    expect_assert_failure(iterator_prev(slist_begin(pslist)));
    slist_destroy(pslist);
}

void test_iterator_prev__set(void** state)
{
    set_t* pset = create_set(int);
    iterator_t it_iter;

    set_init(pset);
    set_insert(pset, 1);
    set_insert(pset, 2);
    it_iter = iterator_next(set_begin(pset));
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_prev(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    set_destroy(pset);
}

void test_iterator_prev__set_begin(void** state)
{
    set_t* pset = create_set(int);

    set_init(pset);
    expect_assert_failure(iterator_prev(set_begin(pset)));
    set_destroy(pset);
}

void test_iterator_prev__multiset(void** state)
{
    multiset_t* pmset = create_multiset(int);
    iterator_t it_iter;

    multiset_init(pmset);
    multiset_insert(pmset, 1);
    multiset_insert(pmset, 2);
    it_iter = iterator_next(multiset_begin(pmset));
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_prev(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    multiset_destroy(pmset);
}

void test_iterator_prev__multiset_begin(void** state)
{
    multiset_t* pmset = create_multiset(int);

    multiset_init(pmset);
    expect_assert_failure(iterator_prev(multiset_begin(pmset)));
    multiset_destroy(pmset);
}

void test_iterator_prev__map(void** state)
{
    map_t* pmap = create_map(int, int);
    iterator_t it_iter;

    map_init(pmap);
    *(int*)map_at(pmap, 1) = 10;
    *(int*)map_at(pmap, 2) = 20;
    it_iter = iterator_next(map_begin(pmap));
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 2);
    it_iter = iterator_prev(it_iter);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 1);
    map_destroy(pmap);
}

void test_iterator_prev__map_begin(void** state)
{
    map_t* pmap = create_map(int, int);

    map_init(pmap);
    expect_assert_failure(iterator_prev(map_begin(pmap)));
    map_destroy(pmap);
}

void test_iterator_prev__multimap(void** state)
{
    multimap_t* pmmap = create_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_iter;

    multimap_init(pmmap);
    pair_init(ppair);
    pair_make(ppair, 1, 1);
    multimap_insert(pmmap, ppair);
    pair_make(ppair, 2, 2);
    multimap_insert(pmmap, ppair);
    it_iter = iterator_next(multimap_begin(pmmap));
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 2);
    it_iter = iterator_prev(it_iter);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 1);
    pair_destroy(ppair);
    multimap_destroy(pmmap);
}

void test_iterator_prev__multimap_begin(void** state)
{
    multimap_t* pmmap = create_multimap(int, int);

    multimap_init(pmmap);
    expect_assert_failure(iterator_prev(multimap_begin(pmmap)));
    multimap_destroy(pmmap);
}

void test_iterator_prev__hash_set(void** state)
{
    hash_set_t* phset = create_hash_set(int);
    iterator_t it_iter;

    hash_set_init(phset);
    hash_set_insert(phset, 1);
    hash_set_insert(phset, 2);
    it_iter = iterator_next(hash_set_begin(phset));
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_prev(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    hash_set_destroy(phset);
}

void test_iterator_prev__hash_set_begin(void** state)
{
    hash_set_t* phset = create_hash_set(int);

    hash_set_init(phset);
    expect_assert_failure(iterator_prev(hash_set_begin(phset)));
    hash_set_destroy(phset);
}

void test_iterator_prev__hash_multiset(void** state)
{
    hash_multiset_t* phmset = create_hash_multiset(int);
    iterator_t it_iter;

    hash_multiset_init(phmset);
    hash_multiset_insert(phmset, 1);
    hash_multiset_insert(phmset, 2);
    it_iter = iterator_next(hash_multiset_begin(phmset));
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_prev(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    hash_multiset_destroy(phmset);
}

void test_iterator_prev__hash_multiset_begin(void** state)
{
    hash_multiset_t* phmset = create_hash_multiset(int);

    hash_multiset_init(phmset);
    expect_assert_failure(iterator_prev(hash_multiset_begin(phmset)));
    hash_multiset_destroy(phmset);
}

void test_iterator_prev__hash_map(void** state)
{
    hash_map_t* phmap = create_hash_map(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_iter;

    hash_map_init(phmap);
    pair_init(ppair);
    pair_make(ppair, 0, 0);
    hash_map_insert(phmap, ppair);
    pair_make(ppair, 1, 1);
    hash_map_insert(phmap, ppair);
    it_iter = iterator_next(hash_map_begin(phmap));
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 1);
    it_iter = iterator_prev(it_iter);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 0);
    pair_destroy(ppair);
    hash_map_destroy(phmap);
}

void test_iterator_prev__hash_map_begin(void** state)
{
    hash_map_t* phmap = create_hash_map(int, int);

    hash_map_init(phmap);
    expect_assert_failure(iterator_prev(hash_map_begin(phmap)));
    hash_map_destroy(phmap);
}

void test_iterator_prev__hash_multimap(void** state)
{
    hash_multimap_t* phmap = create_hash_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_iter;

    hash_multimap_init(phmap);
    pair_init(ppair);
    pair_make(ppair, 0, 0);
    hash_multimap_insert(phmap, ppair);
    pair_make(ppair, 1, 1);
    hash_multimap_insert(phmap, ppair);
    it_iter = iterator_next(hash_multimap_begin(phmap));
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 1);
    it_iter = iterator_prev(it_iter);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 0);
    pair_destroy(ppair);
    hash_multimap_destroy(phmap);
}

void test_iterator_prev__hash_multimap_begin(void** state)
{
    hash_multimap_t* phmap = create_hash_multimap(int, int);

    hash_multimap_init(phmap);
    expect_assert_failure(iterator_prev(hash_multimap_begin(phmap)));
    hash_multimap_destroy(phmap);
}

void test_iterator_prev__string(void** state)
{
    string_t* pstr = create_string();
    iterator_t it_iter;

    string_init_cstr(pstr, "abcdefg");
    it_iter = iterator_next(string_begin(pstr));
    assert_true(*(char*)iterator_get_pointer(it_iter) == 'b');
    it_iter = iterator_prev(it_iter);
    assert_true(*(char*)iterator_get_pointer(it_iter) == 'a');
    string_destroy(pstr);
}

void test_iterator_prev__string_begin(void** state)
{
    string_t* pstr = create_string();

    string_init(pstr);
    expect_assert_failure(iterator_prev(string_begin(pstr)));
    string_destroy(pstr);
}

/*
 * test iterator_next_n
 */
UT_CASE_DEFINATION(iterator_next_n)
void test_iterator_next_n__invalid_iter(void** state)
{
    iterator_t it_iter;
    it_iter._t_containertype = 999;
    it_iter._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(iterator_next_n(it_iter, 10));
}

void test_iterator_next_n__vector_0(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_iter;

    vector_init(pvec);
    vector_push_back(pvec, 1);
    vector_push_back(pvec, 2);
    vector_push_back(pvec, 3);

    it_iter = vector_begin(pvec);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next_n(it_iter, 0);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);

    vector_destroy(pvec);
}

void test_iterator_next_n__vector_n(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_iter;
    int i = 0;

    vector_init(pvec);
    for(i = 0; i < 10; ++i)
    {
        vector_push_back(pvec, i);
    }

    it_iter = vector_begin(pvec);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next_n(it_iter, 5);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);

    vector_destroy(pvec);
}

void test_iterator_next_n__vector_n_(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_iter;
    int i = 0;

    vector_init(pvec);
    for(i = 0; i < 10; ++i)
    {
        vector_push_back(pvec, i);
    }

    it_iter = iterator_prev(vector_end(pvec));
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);
    it_iter = iterator_next_n(it_iter, -5);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);

    vector_destroy(pvec);
}

void test_iterator_next_n__vector_end_n(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_iter;
    int i = 0;

    vector_init(pvec);
    for(i = 0; i < 10; ++i)
    {
        vector_push_back(pvec, i);
    }

    it_iter = vector_begin(pvec);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    expect_assert_failure(iterator_next_n(it_iter, 15));

    vector_destroy(pvec);
}

void test_iterator_next_n__vector_prev_n(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_iter;
    int i = 0;

    vector_init(pvec);
    for(i = 0; i < 10; ++i)
    {
        vector_push_back(pvec, i);
    }

    it_iter = iterator_prev(vector_end(pvec));
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);
    expect_assert_failure(iterator_next_n(it_iter, -15));

    vector_destroy(pvec);
}

void test_iterator_next_n__deque_0(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it_iter;

    deque_init(pdeq);
    deque_push_back(pdeq, 1);
    deque_push_back(pdeq, 2);

    it_iter = deque_begin(pdeq);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next_n(it_iter, 0);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    deque_destroy(pdeq);
}

void test_iterator_next_n__deque_n(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it_iter;
    int i = 0;

    deque_init(pdeq);
    for(i = 0; i < 10; ++i)
    {
        deque_push_back(pdeq, i);
    }

    it_iter = deque_begin(pdeq);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next_n(it_iter, 5);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    deque_destroy(pdeq);
}

void test_iterator_next_n__deque_n_(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it_iter;
    int i = 0;

    deque_init(pdeq);
    for(i = 0; i < 10; ++i)
    {
        deque_push_back(pdeq, i);
    }

    it_iter = iterator_prev(deque_end(pdeq));
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);
    it_iter = iterator_next_n(it_iter, -5);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    deque_destroy(pdeq);
}

void test_iterator_next_n__deque_end_n(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it_iter;
    int i = 0;

    deque_init(pdeq);
    for(i = 0; i < 10; ++i)
    {
        deque_push_back(pdeq, i);
    }

    it_iter = deque_begin(pdeq);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    expect_assert_failure(iterator_next_n(it_iter, 15));
    deque_destroy(pdeq);
}

void test_iterator_next_n__deque_prev_n(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it_iter;
    int i = 0;

    deque_init(pdeq);
    for(i = 0; i < 10; ++i)
    {
        deque_push_back(pdeq, i);
    }

    it_iter = iterator_prev(deque_end(pdeq));
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);
    expect_assert_failure(iterator_next_n(it_iter, -15));
    deque_destroy(pdeq);
}

void test_iterator_next_n__list(void** state)
{
    list_t* plist = create_list(int);
    iterator_t it_iter;

    list_init(plist);
    list_push_back(plist, 1);
    list_push_back(plist, 2);

    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    expect_assert_failure(iterator_next_n(it_iter, 1));

    list_destroy(plist);
}

void test_iterator_next_n__slist(void** state)
{
    slist_t* pslist = create_slist(int);
    iterator_t it_iter;

    slist_init(pslist);
    slist_push_front(pslist, 1);
    slist_push_front(pslist, 2);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    expect_assert_failure(iterator_next_n(it_iter, 1));
    slist_destroy(pslist);
}

void test_iterator_next_n__set(void** state)
{
    set_t* pset = create_set(int);
    iterator_t it_iter;

    set_init(pset);
    set_insert(pset, 1);
    set_insert(pset, 2);
    it_iter = set_begin(pset);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    expect_assert_failure(iterator_next_n(it_iter, 1));
    set_destroy(pset);
}

void test_iterator_next_n__multiset(void** state)
{
    multiset_t* pmset = create_multiset(int);
    iterator_t it_iter;

    multiset_init(pmset);
    multiset_insert(pmset, 1);
    multiset_insert(pmset, 2);
    it_iter = multiset_begin(pmset);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    expect_assert_failure(iterator_next_n(it_iter, 1));
    multiset_destroy(pmset);
}

void test_iterator_next_n__map(void** state)
{
    map_t* pmap = create_map(int, int);
    iterator_t it_iter;

    map_init(pmap);
    *(int*)map_at(pmap, 1) = 10;
    *(int*)map_at(pmap, 2) = 20;
    it_iter = map_begin(pmap);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 1);
    expect_assert_failure(iterator_next_n(it_iter, 1));
    map_destroy(pmap);
}

void test_iterator_next_n__multimap(void** state)
{
    multimap_t* pmmap = create_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_iter;

    multimap_init(pmmap);
    pair_init(ppair);
    pair_make(ppair, 1, 1);
    multimap_insert(pmmap, ppair);
    pair_make(ppair, 2, 2);
    multimap_insert(pmmap, ppair);
    it_iter = multimap_begin(pmmap);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 1);
    expect_assert_failure(iterator_next_n(it_iter, 1));
    pair_destroy(ppair);
    multimap_destroy(pmmap);
}

void test_iterator_next_n__hash_set(void** state)
{
    hash_set_t* phset = create_hash_set(int);
    iterator_t it_iter;

    hash_set_init(phset);
    hash_set_insert(phset, 1);
    hash_set_insert(phset, 2);
    it_iter = hash_set_begin(phset);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    expect_assert_failure(iterator_next_n(it_iter, 1));
    hash_set_destroy(phset);
}

void test_iterator_next_n__hash_multiset(void** state)
{
    hash_multiset_t* phmset = create_hash_multiset(int);
    iterator_t it_iter;

    hash_multiset_init(phmset);
    hash_multiset_insert(phmset, 1);
    hash_multiset_insert(phmset, 2);
    it_iter = hash_multiset_begin(phmset);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    expect_assert_failure(iterator_next_n(it_iter, 1));
    hash_multiset_destroy(phmset);
}

void test_iterator_next_n__hash_map(void** state)
{
    hash_map_t* phmap = create_hash_map(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_iter;

    hash_map_init(phmap);
    pair_init(ppair);
    pair_make(ppair, 0, 0);
    hash_map_insert(phmap, ppair);
    pair_make(ppair, 1, 1);
    hash_map_insert(phmap, ppair);
    it_iter = hash_map_begin(phmap);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 0);
    expect_assert_failure(iterator_next_n(it_iter, 1));
    pair_destroy(ppair);
    hash_map_destroy(phmap);
}

void test_iterator_next_n__hash_multimap(void** state)
{
    hash_multimap_t* phmap = create_hash_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_iter;

    hash_multimap_init(phmap);
    pair_init(ppair);
    pair_make(ppair, 0, 0);
    hash_multimap_insert(phmap, ppair);
    pair_make(ppair, 1, 1);
    hash_multimap_insert(phmap, ppair);
    it_iter = hash_multimap_begin(phmap);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 0);
    expect_assert_failure(iterator_next_n(it_iter, 1));
    pair_destroy(ppair);
    hash_multimap_destroy(phmap);
}

void test_iterator_next_n__string_0(void** state)
{
    string_t* pstr = create_string();
    iterator_t it_iter;

    string_init_cstr(pstr, "abcdefg");
    it_iter = string_begin(pstr);
    assert_true(*(char*)iterator_get_pointer(it_iter) == 'a');
    it_iter = iterator_next_n(it_iter, 0);
    assert_true(*(char*)iterator_get_pointer(it_iter) == 'a');
    string_destroy(pstr);
}

void test_iterator_next_n__string_n(void** state)
{
    string_t* pstr = create_string();
    iterator_t it_iter;

    string_init_cstr(pstr, "abcdefghijklmn");
    it_iter = string_begin(pstr);
    assert_true(*(char*)iterator_get_pointer(it_iter) == 'a');
    it_iter = iterator_next_n(it_iter, 5);
    assert_true(*(char*)iterator_get_pointer(it_iter) == 'f');
    string_destroy(pstr);
}

void test_iterator_next_n__string_n_(void** state)
{
    string_t* pstr = create_string();
    iterator_t it_iter;

    string_init_cstr(pstr, "abcdefghijklmn");
    it_iter = iterator_prev(string_end(pstr));
    assert_true(*(char*)iterator_get_pointer(it_iter) == 'n');
    it_iter = iterator_next_n(it_iter, -5);
    assert_true(*(char*)iterator_get_pointer(it_iter) == 'i');
    string_destroy(pstr);
}

void test_iterator_next_n__string_end_n(void** state)
{
    string_t* pstr = create_string();
    iterator_t it_iter;

    string_init_cstr(pstr, "abcdefghijklmn");
    it_iter = string_begin(pstr);
    assert_true(*(char*)iterator_get_pointer(it_iter) == 'a');
    expect_assert_failure(iterator_next_n(it_iter, 25));
    string_destroy(pstr);
}

void test_iterator_next_n__string_prev_n(void** state)
{
    string_t* pstr = create_string();
    iterator_t it_iter;

    string_init_cstr(pstr, "abcdefghijklmn");
    it_iter = iterator_prev(string_end(pstr));
    assert_true(*(char*)iterator_get_pointer(it_iter) == 'n');
    expect_assert_failure(iterator_next_n(it_iter, -35));
    string_destroy(pstr);
}

/*
 * test iterator_prev_n
 */
UT_CASE_DEFINATION(iterator_prev_n)
void test_iterator_prev_n__invalid_iter(void** state)
{
    iterator_t it_iter;
    it_iter._t_containertype = 999;
    it_iter._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(iterator_prev_n(it_iter, 10));
}

void test_iterator_prev_n__vector_0(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_iter;

    vector_init(pvec);
    vector_push_back(pvec, 1);
    vector_push_back(pvec, 2);
    vector_push_back(pvec, 3);

    it_iter = vector_begin(pvec);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_prev_n(it_iter, 0);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);

    vector_destroy(pvec);
}

void test_iterator_prev_n__vector_n(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_iter;
    int i = 0;

    vector_init(pvec);
    for(i = 0; i < 10; ++i)
    {
        vector_push_back(pvec, i);
    }

    it_iter = vector_begin(pvec);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_prev_n(it_iter, -5);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);

    vector_destroy(pvec);
}

void test_iterator_prev_n__vector_n_(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_iter;
    int i = 0;

    vector_init(pvec);
    for(i = 0; i < 10; ++i)
    {
        vector_push_back(pvec, i);
    }

    it_iter = iterator_prev(vector_end(pvec));
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);
    it_iter = iterator_prev_n(it_iter, 5);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);

    vector_destroy(pvec);
}

void test_iterator_prev_n__vector_end_n(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_iter;
    int i = 0;

    vector_init(pvec);
    for(i = 0; i < 10; ++i)
    {
        vector_push_back(pvec, i);
    }

    it_iter = vector_begin(pvec);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    expect_assert_failure(iterator_prev_n(it_iter, -15));

    vector_destroy(pvec);
}

void test_iterator_prev_n__vector_prev_n(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_iter;
    int i = 0;

    vector_init(pvec);
    for(i = 0; i < 10; ++i)
    {
        vector_push_back(pvec, i);
    }

    it_iter = iterator_prev(vector_end(pvec));
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);
    expect_assert_failure(iterator_prev_n(it_iter, 15));

    vector_destroy(pvec);
}

void test_iterator_prev_n__deque_0(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it_iter;

    deque_init(pdeq);
    deque_push_back(pdeq, 1);
    deque_push_back(pdeq, 2);

    it_iter = deque_begin(pdeq);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_prev_n(it_iter, 0);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    deque_destroy(pdeq);
}

void test_iterator_prev_n__deque_n(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it_iter;
    int i = 0;

    deque_init(pdeq);
    for(i = 0; i < 10; ++i)
    {
        deque_push_back(pdeq, i);
    }

    it_iter = deque_begin(pdeq);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_prev_n(it_iter, -5);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    deque_destroy(pdeq);
}

void test_iterator_prev_n__deque_n_(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it_iter;
    int i = 0;

    deque_init(pdeq);
    for(i = 0; i < 10; ++i)
    {
        deque_push_back(pdeq, i);
    }

    it_iter = iterator_prev(deque_end(pdeq));
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);
    it_iter = iterator_prev_n(it_iter, 5);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    deque_destroy(pdeq);
}

void test_iterator_prev_n__deque_end_n(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it_iter;
    int i = 0;

    deque_init(pdeq);
    for(i = 0; i < 10; ++i)
    {
        deque_push_back(pdeq, i);
    }

    it_iter = deque_begin(pdeq);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    expect_assert_failure(iterator_prev_n(it_iter, -15));
    deque_destroy(pdeq);
}

void test_iterator_prev_n__deque_prev_n(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it_iter;
    int i = 0;

    deque_init(pdeq);
    for(i = 0; i < 10; ++i)
    {
        deque_push_back(pdeq, i);
    }

    it_iter = iterator_prev(deque_end(pdeq));
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);
    expect_assert_failure(iterator_prev_n(it_iter, 15));
    deque_destroy(pdeq);
}

void test_iterator_prev_n__list(void** state)
{
    list_t* plist = create_list(int);
    iterator_t it_iter;

    list_init(plist);
    list_push_back(plist, 1);
    list_push_back(plist, 2);

    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    expect_assert_failure(iterator_prev_n(it_iter, -1));

    list_destroy(plist);
}

void test_iterator_prev_n__slist(void** state)
{
    slist_t* pslist = create_slist(int);
    iterator_t it_iter;

    slist_init(pslist);
    slist_push_front(pslist, 1);
    slist_push_front(pslist, 2);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    expect_assert_failure(iterator_prev_n(it_iter, -1));
    slist_destroy(pslist);
}

void test_iterator_prev_n__set(void** state)
{
    set_t* pset = create_set(int);
    iterator_t it_iter;

    set_init(pset);
    set_insert(pset, 1);
    set_insert(pset, 2);
    it_iter = set_begin(pset);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    expect_assert_failure(iterator_prev_n(it_iter, -1));
    set_destroy(pset);
}

void test_iterator_prev_n__multiset(void** state)
{
    multiset_t* pmset = create_multiset(int);
    iterator_t it_iter;

    multiset_init(pmset);
    multiset_insert(pmset, 1);
    multiset_insert(pmset, 2);
    it_iter = multiset_begin(pmset);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    expect_assert_failure(iterator_prev_n(it_iter, -1));
    multiset_destroy(pmset);
}

void test_iterator_prev_n__map(void** state)
{
    map_t* pmap = create_map(int, int);
    iterator_t it_iter;

    map_init(pmap);
    *(int*)map_at(pmap, 1) = 10;
    *(int*)map_at(pmap, 2) = 20;
    it_iter = map_begin(pmap);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 1);
    expect_assert_failure(iterator_prev_n(it_iter, -1));
    map_destroy(pmap);
}

void test_iterator_prev_n__multimap(void** state)
{
    multimap_t* pmmap = create_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_iter;

    multimap_init(pmmap);
    pair_init(ppair);
    pair_make(ppair, 1, 1);
    multimap_insert(pmmap, ppair);
    pair_make(ppair, 2, 2);
    multimap_insert(pmmap, ppair);
    it_iter = multimap_begin(pmmap);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 1);
    expect_assert_failure(iterator_prev_n(it_iter, -1));
    pair_destroy(ppair);
    multimap_destroy(pmmap);
}

void test_iterator_prev_n__hash_set(void** state)
{
    hash_set_t* phset = create_hash_set(int);
    iterator_t it_iter;

    hash_set_init(phset);
    hash_set_insert(phset, 1);
    hash_set_insert(phset, 2);
    it_iter = hash_set_begin(phset);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    expect_assert_failure(iterator_prev_n(it_iter, -1));
    hash_set_destroy(phset);
}

void test_iterator_prev_n__hash_multiset(void** state)
{
    hash_multiset_t* phmset = create_hash_multiset(int);
    iterator_t it_iter;

    hash_multiset_init(phmset);
    hash_multiset_insert(phmset, 1);
    hash_multiset_insert(phmset, 2);
    it_iter = hash_multiset_begin(phmset);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    expect_assert_failure(iterator_prev_n(it_iter, -1));
    hash_multiset_destroy(phmset);
}

void test_iterator_prev_n__hash_map(void** state)
{
    hash_map_t* phmap = create_hash_map(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_iter;

    hash_map_init(phmap);
    pair_init(ppair);
    pair_make(ppair, 0, 0);
    hash_map_insert(phmap, ppair);
    pair_make(ppair, 1, 1);
    hash_map_insert(phmap, ppair);
    it_iter = hash_map_begin(phmap);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 0);
    expect_assert_failure(iterator_prev_n(it_iter, -1));
    pair_destroy(ppair);
    hash_map_destroy(phmap);
}

void test_iterator_prev_n__hash_multimap(void** state)
{
    hash_multimap_t* phmap = create_hash_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_iter;

    hash_multimap_init(phmap);
    pair_init(ppair);
    pair_make(ppair, 0, 0);
    hash_multimap_insert(phmap, ppair);
    pair_make(ppair, 1, 1);
    hash_multimap_insert(phmap, ppair);
    it_iter = hash_multimap_begin(phmap);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 0);
    expect_assert_failure(iterator_prev_n(it_iter, -1));
    pair_destroy(ppair);
    hash_multimap_destroy(phmap);
}

void test_iterator_prev_n__string_0(void** state)
{
    string_t* pstr = create_string();
    iterator_t it_iter;

    string_init_cstr(pstr, "abcdefg");
    it_iter = string_begin(pstr);
    assert_true(*(char*)iterator_get_pointer(it_iter) == 'a');
    it_iter = iterator_prev_n(it_iter, 0);
    assert_true(*(char*)iterator_get_pointer(it_iter) == 'a');
    string_destroy(pstr);
}

void test_iterator_prev_n__string_n(void** state)
{
    string_t* pstr = create_string();
    iterator_t it_iter;

    string_init_cstr(pstr, "abcdefghijklmn");
    it_iter = string_begin(pstr);
    assert_true(*(char*)iterator_get_pointer(it_iter) == 'a');
    it_iter = iterator_prev_n(it_iter, -5);
    assert_true(*(char*)iterator_get_pointer(it_iter) == 'f');
    string_destroy(pstr);
}

void test_iterator_prev_n__string_n_(void** state)
{
    string_t* pstr = create_string();
    iterator_t it_iter;

    string_init_cstr(pstr, "abcdefghijklmn");
    it_iter = iterator_prev(string_end(pstr));
    assert_true(*(char*)iterator_get_pointer(it_iter) == 'n');
    it_iter = iterator_prev_n(it_iter, 5);
    assert_true(*(char*)iterator_get_pointer(it_iter) == 'i');
    string_destroy(pstr);
}

void test_iterator_prev_n__string_end_n(void** state)
{
    string_t* pstr = create_string();
    iterator_t it_iter;

    string_init_cstr(pstr, "abcdefghijklmn");
    it_iter = string_begin(pstr);
    assert_true(*(char*)iterator_get_pointer(it_iter) == 'a');
    expect_assert_failure(iterator_prev_n(it_iter, -25));
    string_destroy(pstr);
}

void test_iterator_prev_n__string_prev_n(void** state)
{
    string_t* pstr = create_string();
    iterator_t it_iter;

    string_init_cstr(pstr, "abcdefghijklmn");
    it_iter = iterator_prev(string_end(pstr));
    assert_true(*(char*)iterator_get_pointer(it_iter) == 'n');
    expect_assert_failure(iterator_prev_n(it_iter, 35));
    string_destroy(pstr);
}

/*
 * test iterator_equal
 */
UT_CASE_DEFINATION(iterator_equal)
void test_iterator_equal__invalid_first(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_first;
    iterator_t it_second;

    vector_init(pvec);
    it_first = it_second = vector_begin(pvec);
    it_first._t_iteratortype = 4444;
    expect_assert_failure(iterator_equal(it_first, it_second));
    vector_destroy(pvec);
}

void test_iterator_equal__invalid_second(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_first;
    iterator_t it_second;

    vector_init(pvec);
    it_first = it_second = vector_begin(pvec);
    it_second._t_iteratortype = 4444;
    expect_assert_failure(iterator_equal(it_first, it_second));
    vector_destroy(pvec);
}

void test_iterator_equal__vector_equal(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_first;
    iterator_t it_second;

    vector_init_n(pvec, 10);
    it_first = it_second = vector_begin(pvec);
    assert_true(iterator_equal(it_first, it_second));
    vector_destroy(pvec);
}

void test_iterator_equal__vector_not_equal(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_first;
    iterator_t it_second;

    vector_init_n(pvec, 10);
    it_first = vector_begin(pvec);
    it_second = vector_end(pvec);
    assert_false(iterator_equal(it_first, it_second));
    vector_destroy(pvec);
}

void test_iterator_equal__deque_equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it_first;
    iterator_t it_second;

    deque_init_n(pdeq, 10);
    it_first = it_second = deque_begin(pdeq);
    assert_true(iterator_equal(it_first, it_second));
    deque_destroy(pdeq);
}

void test_iterator_equal__deque_not_equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it_first;
    iterator_t it_second;

    deque_init_n(pdeq, 10);
    it_first =  deque_begin(pdeq);
    it_second = deque_end(pdeq);
    assert_false(iterator_equal(it_first, it_second));
    deque_destroy(pdeq);
}

void test_iterator_equal__list_equal(void** state)
{
    list_t* plist = create_list(int);
    iterator_t it_first;
    iterator_t it_second;

    list_init_n(plist, 10);
    it_first = it_second = list_begin(plist);
    assert_true(iterator_equal(it_first, it_second));
    list_destroy(plist);
}

void test_iterator_equal__list_not_equal(void** state)
{
    list_t* plist = create_list(int);
    iterator_t it_first;
    iterator_t it_second;

    list_init_n(plist, 10);
    it_first = list_begin(plist);
    it_second = list_end(plist);
    assert_false(iterator_equal(it_first, it_second));
    list_destroy(plist);
}

void test_iterator_equal__slist_equal(void** state)
{
    slist_t* pslist = create_slist(int);
    iterator_t it_first;
    iterator_t it_second;

    slist_init_n(pslist, 10);
    it_first = it_second = slist_begin(pslist);
    assert_true(iterator_equal(it_first, it_second));
    slist_destroy(pslist);
}

void test_iterator_equal__slist_not_equal(void** state)
{
    slist_t* pslist = create_slist(int);
    iterator_t it_first;
    iterator_t it_second;

    slist_init_n(pslist, 10);
    it_first = slist_begin(pslist);
    it_second = slist_end(pslist);
    assert_false(iterator_equal(it_first, it_second));
    slist_destroy(pslist);
}

void test_iterator_equal__set_equal(void** state)
{
    set_t* pset = create_set(int);
    iterator_t it_first;
    iterator_t it_second;

    set_init(pset);
    set_insert(pset, 1);
    it_first = it_second = set_begin(pset);
    assert_true(iterator_equal(it_first, it_second));
    set_destroy(pset);
}

void test_iterator_equal__set_not_equal(void** state)
{
    set_t* pset = create_set(int);
    iterator_t it_first;
    iterator_t it_second;

    set_init(pset);
    set_insert(pset, 1);
    it_first = set_begin(pset);
    it_second = set_end(pset);
    assert_false(iterator_equal(it_first, it_second));
    set_destroy(pset);
}

void test_iterator_equal__multiset_equal(void** state)
{
    multiset_t* pset = create_multiset(int);
    iterator_t it_first;
    iterator_t it_second;

    multiset_init(pset);
    multiset_insert(pset, 1);
    it_first = it_second = multiset_begin(pset);
    assert_true(iterator_equal(it_first, it_second));
    multiset_destroy(pset);
}

void test_iterator_equal__multiset_not_equal(void** state)
{
    multiset_t* pset = create_multiset(int);
    iterator_t it_first;
    iterator_t it_second;

    multiset_init(pset);
    multiset_insert(pset, 1);
    it_first = multiset_begin(pset);
    it_second = multiset_end(pset);
    assert_false(iterator_equal(it_first, it_second));
    multiset_destroy(pset);
}

void test_iterator_equal__map_equal(void** state)
{
    map_t* pmap = create_map(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    map_init(pmap);
    pair_init(ppair);
    map_insert(pmap, ppair);
    it_first = it_second = map_begin(pmap);
    assert_true(iterator_equal(it_first, it_second));
    pair_destroy(ppair);
    map_destroy(pmap);
}

void test_iterator_equal__map_not_equal(void** state)
{
    map_t* pmap = create_map(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    map_init(pmap);
    pair_init(ppair);
    map_insert(pmap, ppair);
    it_first = map_begin(pmap);
    it_second = map_end(pmap);
    assert_false(iterator_equal(it_first, it_second));
    pair_destroy(ppair);
    map_destroy(pmap);
}

void test_iterator_equal__multimap_equal(void** state)
{
    multimap_t* pmap = create_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    multimap_init(pmap);
    pair_init(ppair);
    multimap_insert(pmap, ppair);
    it_first = it_second = multimap_begin(pmap);
    assert_true(iterator_equal(it_first, it_second));
    pair_destroy(ppair);
    multimap_destroy(pmap);
}

void test_iterator_equal__multimap_not_equal(void** state)
{
    multimap_t* pmap = create_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    multimap_init(pmap);
    pair_init(ppair);
    multimap_insert(pmap, ppair);
    it_first = multimap_begin(pmap);
    it_second = multimap_end(pmap);
    assert_false(iterator_equal(it_first, it_second));
    pair_destroy(ppair);
    multimap_destroy(pmap);
}

void test_iterator_equal__hash_set_equal(void** state)
{
    hash_set_t* phset = create_hash_set(int);
    iterator_t it_first;
    iterator_t it_second;

    hash_set_init(phset);
    hash_set_insert(phset, 1);
    it_first = it_second = hash_set_begin(phset);
    assert_true(iterator_equal(it_first, it_second));
    hash_set_destroy(phset);
}

void test_iterator_equal__hash_set_not_equal(void** state)
{
    hash_set_t* phset = create_hash_set(int);
    iterator_t it_first;
    iterator_t it_second;

    hash_set_init(phset);
    hash_set_insert(phset, 1);
    it_first = hash_set_begin(phset);
    it_second = hash_set_end(phset);
    assert_false(iterator_equal(it_first, it_second));
    hash_set_destroy(phset);
}

void test_iterator_equal__hash_multiset_equal(void** state)
{
    hash_multiset_t* phset = create_hash_multiset(int);
    iterator_t it_first;
    iterator_t it_second;

    hash_multiset_init(phset);
    hash_multiset_insert(phset, 1);
    it_first = it_second = hash_multiset_begin(phset);
    assert_true(iterator_equal(it_first, it_second));
    hash_multiset_destroy(phset);
}

void test_iterator_equal__hash_multiset_not_equal(void** state)
{
    hash_multiset_t* phset = create_hash_multiset(int);
    iterator_t it_first;
    iterator_t it_second;

    hash_multiset_init(phset);
    hash_multiset_insert(phset, 1);
    it_first = hash_multiset_begin(phset);
    it_second = hash_multiset_end(phset);
    assert_false(iterator_equal(it_first, it_second));
    hash_multiset_destroy(phset);
}

void test_iterator_equal__hash_map_equal(void** state)
{
    hash_map_t* pmap = create_hash_map(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    hash_map_init(pmap);
    pair_init(ppair);
    hash_map_insert(pmap, ppair);
    it_first = it_second = hash_map_begin(pmap);
    assert_true(iterator_equal(it_first, it_second));
    pair_destroy(ppair);
    hash_map_destroy(pmap);
}

void test_iterator_equal__hash_map_not_equal(void** state)
{
    hash_map_t* pmap = create_hash_map(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    hash_map_init(pmap);
    pair_init(ppair);
    hash_map_insert(pmap, ppair);
    it_first = hash_map_begin(pmap);
    it_second = hash_map_end(pmap);
    assert_false(iterator_equal(it_first, it_second));
    pair_destroy(ppair);
    hash_map_destroy(pmap);
}

void test_iterator_equal__hash_multimap_equal(void** state)
{
    hash_multimap_t* pmap = create_hash_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    hash_multimap_init(pmap);
    pair_init(ppair);
    hash_multimap_insert(pmap, ppair);
    it_first = it_second = hash_multimap_begin(pmap);
    assert_true(iterator_equal(it_first, it_second));
    pair_destroy(ppair);
    hash_multimap_destroy(pmap);
}

void test_iterator_equal__hash_multimap_not_equal(void** state)
{
    hash_multimap_t* pmap = create_hash_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    hash_multimap_init(pmap);
    pair_init(ppair);
    hash_multimap_insert(pmap, ppair);
    it_first = hash_multimap_begin(pmap);
    it_second = hash_multimap_end(pmap);
    assert_false(iterator_equal(it_first, it_second));
    pair_destroy(ppair);
    hash_multimap_destroy(pmap);
}

void test_iterator_equal__string_equal(void** state)
{
    string_t* pstr = create_string();
    iterator_t it_first;
    iterator_t it_second;

    string_init_cstr(pstr, "abcdefg");
    it_first = it_second = string_begin(pstr);
    assert_true(iterator_equal(it_first, it_second));
    string_destroy(pstr);
}

void test_iterator_equal__string_not_equal(void** state)
{
    string_t* pstr = create_string();
    iterator_t it_first;
    iterator_t it_second;

    string_init_cstr(pstr, "abcdefg");
    it_first = string_begin(pstr);
    it_second = string_end(pstr);
    assert_false(iterator_equal(it_first, it_second));
    string_destroy(pstr);
}

/*
 * test iterator_not_equal
 */
UT_CASE_DEFINATION(iterator_not_equal)
void test_iterator_not_equal__invalid_first(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_first;
    iterator_t it_second;

    vector_init(pvec);
    it_first = it_second = vector_begin(pvec);
    it_first._t_iteratortype = 4444;
    expect_assert_failure(iterator_not_equal(it_first, it_second));
    vector_destroy(pvec);
}

void test_iterator_not_equal__invalid_second(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_first;
    iterator_t it_second;

    vector_init(pvec);
    it_first = it_second = vector_begin(pvec);
    it_second._t_iteratortype = 4444;
    expect_assert_failure(iterator_not_equal(it_first, it_second));
    vector_destroy(pvec);
}

void test_iterator_not_equal__vector_equal(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_first;
    iterator_t it_second;

    vector_init_n(pvec, 10);
    it_first = it_second = vector_begin(pvec);
    assert_false(iterator_not_equal(it_first, it_second));
    vector_destroy(pvec);
}

void test_iterator_not_equal__vector_not_equal(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_first;
    iterator_t it_second;

    vector_init_n(pvec, 10);
    it_first = vector_begin(pvec);
    it_second = vector_end(pvec);
    assert_true(iterator_not_equal(it_first, it_second));
    vector_destroy(pvec);
}

void test_iterator_not_equal__deque_equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it_first;
    iterator_t it_second;

    deque_init_n(pdeq, 10);
    it_first = it_second = deque_begin(pdeq);
    assert_false(iterator_not_equal(it_first, it_second));
    deque_destroy(pdeq);
}

void test_iterator_not_equal__deque_not_equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it_first;
    iterator_t it_second;

    deque_init_n(pdeq, 10);
    it_first =  deque_begin(pdeq);
    it_second = deque_end(pdeq);
    assert_true(iterator_not_equal(it_first, it_second));
    deque_destroy(pdeq);
}

void test_iterator_not_equal__list_equal(void** state)
{
    list_t* plist = create_list(int);
    iterator_t it_first;
    iterator_t it_second;

    list_init_n(plist, 10);
    it_first = it_second = list_begin(plist);
    assert_false(iterator_not_equal(it_first, it_second));
    list_destroy(plist);
}

void test_iterator_not_equal__list_not_equal(void** state)
{
    list_t* plist = create_list(int);
    iterator_t it_first;
    iterator_t it_second;

    list_init_n(plist, 10);
    it_first = list_begin(plist);
    it_second = list_end(plist);
    assert_true(iterator_not_equal(it_first, it_second));
    list_destroy(plist);
}

void test_iterator_not_equal__slist_equal(void** state)
{
    slist_t* pslist = create_slist(int);
    iterator_t it_first;
    iterator_t it_second;

    slist_init_n(pslist, 10);
    it_first = it_second = slist_begin(pslist);
    assert_false(iterator_not_equal(it_first, it_second));
    slist_destroy(pslist);
}

void test_iterator_not_equal__slist_not_equal(void** state)
{
    slist_t* pslist = create_slist(int);
    iterator_t it_first;
    iterator_t it_second;

    slist_init_n(pslist, 10);
    it_first = slist_begin(pslist);
    it_second = slist_end(pslist);
    assert_true(iterator_not_equal(it_first, it_second));
    slist_destroy(pslist);
}

void test_iterator_not_equal__set_equal(void** state)
{
    set_t* pset = create_set(int);
    iterator_t it_first;
    iterator_t it_second;

    set_init(pset);
    set_insert(pset, 1);
    it_first = it_second = set_begin(pset);
    assert_false(iterator_not_equal(it_first, it_second));
    set_destroy(pset);
}

void test_iterator_not_equal__set_not_equal(void** state)
{
    set_t* pset = create_set(int);
    iterator_t it_first;
    iterator_t it_second;

    set_init(pset);
    set_insert(pset, 1);
    it_first = set_begin(pset);
    it_second = set_end(pset);
    assert_true(iterator_not_equal(it_first, it_second));
    set_destroy(pset);
}

void test_iterator_not_equal__multiset_equal(void** state)
{
    multiset_t* pset = create_multiset(int);
    iterator_t it_first;
    iterator_t it_second;

    multiset_init(pset);
    multiset_insert(pset, 1);
    it_first = it_second = multiset_begin(pset);
    assert_false(iterator_not_equal(it_first, it_second));
    multiset_destroy(pset);
}

void test_iterator_not_equal__multiset_not_equal(void** state)
{
    multiset_t* pset = create_multiset(int);
    iterator_t it_first;
    iterator_t it_second;

    multiset_init(pset);
    multiset_insert(pset, 1);
    it_first = multiset_begin(pset);
    it_second = multiset_end(pset);
    assert_true(iterator_not_equal(it_first, it_second));
    multiset_destroy(pset);
}

void test_iterator_not_equal__map_equal(void** state)
{
    map_t* pmap = create_map(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    map_init(pmap);
    pair_init(ppair);
    map_insert(pmap, ppair);
    it_first = it_second = map_begin(pmap);
    assert_false(iterator_not_equal(it_first, it_second));
    pair_destroy(ppair);
    map_destroy(pmap);
}

void test_iterator_not_equal__map_not_equal(void** state)
{
    map_t* pmap = create_map(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    map_init(pmap);
    pair_init(ppair);
    map_insert(pmap, ppair);
    it_first = map_begin(pmap);
    it_second = map_end(pmap);
    assert_true(iterator_not_equal(it_first, it_second));
    pair_destroy(ppair);
    map_destroy(pmap);
}

void test_iterator_not_equal__multimap_equal(void** state)
{
    multimap_t* pmap = create_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    multimap_init(pmap);
    pair_init(ppair);
    multimap_insert(pmap, ppair);
    it_first = it_second = multimap_begin(pmap);
    assert_false(iterator_not_equal(it_first, it_second));
    pair_destroy(ppair);
    multimap_destroy(pmap);
}

void test_iterator_not_equal__multimap_not_equal(void** state)
{
    multimap_t* pmap = create_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    multimap_init(pmap);
    pair_init(ppair);
    multimap_insert(pmap, ppair);
    it_first = multimap_begin(pmap);
    it_second = multimap_end(pmap);
    assert_true(iterator_not_equal(it_first, it_second));
    pair_destroy(ppair);
    multimap_destroy(pmap);
}

void test_iterator_not_equal__hash_set_equal(void** state)
{
    hash_set_t* phset = create_hash_set(int);
    iterator_t it_first;
    iterator_t it_second;

    hash_set_init(phset);
    hash_set_insert(phset, 1);
    it_first = it_second = hash_set_begin(phset);
    assert_false(iterator_not_equal(it_first, it_second));
    hash_set_destroy(phset);
}

void test_iterator_not_equal__hash_set_not_equal(void** state)
{
    hash_set_t* phset = create_hash_set(int);
    iterator_t it_first;
    iterator_t it_second;

    hash_set_init(phset);
    hash_set_insert(phset, 1);
    it_first = hash_set_begin(phset);
    it_second = hash_set_end(phset);
    assert_true(iterator_not_equal(it_first, it_second));
    hash_set_destroy(phset);
}

void test_iterator_not_equal__hash_multiset_equal(void** state)
{
    hash_multiset_t* phset = create_hash_multiset(int);
    iterator_t it_first;
    iterator_t it_second;

    hash_multiset_init(phset);
    hash_multiset_insert(phset, 1);
    it_first = it_second = hash_multiset_begin(phset);
    assert_false(iterator_not_equal(it_first, it_second));
    hash_multiset_destroy(phset);
}

void test_iterator_not_equal__hash_multiset_not_equal(void** state)
{
    hash_multiset_t* phset = create_hash_multiset(int);
    iterator_t it_first;
    iterator_t it_second;

    hash_multiset_init(phset);
    hash_multiset_insert(phset, 1);
    it_first = hash_multiset_begin(phset);
    it_second = hash_multiset_end(phset);
    assert_true(iterator_not_equal(it_first, it_second));
    hash_multiset_destroy(phset);
}

void test_iterator_not_equal__hash_map_equal(void** state)
{
    hash_map_t* pmap = create_hash_map(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    hash_map_init(pmap);
    pair_init(ppair);
    hash_map_insert(pmap, ppair);
    it_first = it_second = hash_map_begin(pmap);
    assert_false(iterator_not_equal(it_first, it_second));
    pair_destroy(ppair);
    hash_map_destroy(pmap);
}

void test_iterator_not_equal__hash_map_not_equal(void** state)
{
    hash_map_t* pmap = create_hash_map(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    hash_map_init(pmap);
    pair_init(ppair);
    hash_map_insert(pmap, ppair);
    it_first = hash_map_begin(pmap);
    it_second = hash_map_end(pmap);
    assert_true(iterator_not_equal(it_first, it_second));
    pair_destroy(ppair);
    hash_map_destroy(pmap);
}

void test_iterator_not_equal__hash_multimap_equal(void** state)
{
    hash_multimap_t* pmap = create_hash_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    hash_multimap_init(pmap);
    pair_init(ppair);
    hash_multimap_insert(pmap, ppair);
    it_first = it_second = hash_multimap_begin(pmap);
    assert_false(iterator_not_equal(it_first, it_second));
    pair_destroy(ppair);
    hash_multimap_destroy(pmap);
}

void test_iterator_not_equal__hash_multimap_not_equal(void** state)
{
    hash_multimap_t* pmap = create_hash_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    hash_multimap_init(pmap);
    pair_init(ppair);
    hash_multimap_insert(pmap, ppair);
    it_first = hash_multimap_begin(pmap);
    it_second = hash_multimap_end(pmap);
    assert_true(iterator_not_equal(it_first, it_second));
    pair_destroy(ppair);
    hash_multimap_destroy(pmap);
}

void test_iterator_not_equal__string_equal(void** state)
{
    string_t* pstr = create_string();
    iterator_t it_first;
    iterator_t it_second;

    string_init_cstr(pstr, "abcdefg");
    it_first = it_second = string_begin(pstr);
    assert_false(iterator_not_equal(it_first, it_second));
    string_destroy(pstr);
}

void test_iterator_not_equal__string_not_equal(void** state)
{
    string_t* pstr = create_string();
    iterator_t it_first;
    iterator_t it_second;

    string_init_cstr(pstr, "abcdefg");
    it_first = string_begin(pstr);
    it_second = string_end(pstr);
    assert_true(iterator_not_equal(it_first, it_second));
    string_destroy(pstr);
}

/*
 * test iteator_less
 */
UT_CASE_DEFINATION(iterator_less)
void test_iterator_less__invalid_first(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_first;
    iterator_t it_second;

    vector_init(pvec);
    it_first = it_second = vector_begin(pvec);
    it_first._t_iteratortype = 4444;
    expect_assert_failure(iterator_less(it_first, it_second));
    vector_destroy(pvec);
}

void test_iterator_less__invalid_second(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_first;
    iterator_t it_second;

    vector_init(pvec);
    it_first = it_second = vector_begin(pvec);
    it_second._t_iteratortype = 4444;
    expect_assert_failure(iterator_less(it_first, it_second));
    vector_destroy(pvec);
}

void test_iterator_less__vector_less(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_first;
    iterator_t it_second;

    vector_init_n(pvec, 10);
    it_first = vector_begin(pvec);
    it_second = vector_end(pvec);
    assert_true(iterator_less(it_first, it_second));
    vector_destroy(pvec);
}

void test_iterator_less__vector_equal(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_first;
    iterator_t it_second;

    vector_init_n(pvec, 10);
    it_first = vector_begin(pvec);
    it_second = vector_begin(pvec);
    assert_false(iterator_less(it_first, it_second));
    vector_destroy(pvec);
}

void test_iterator_less__vector_greater(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_first;
    iterator_t it_second;

    vector_init_n(pvec, 10);
    it_first = vector_end(pvec);
    it_second = vector_begin(pvec);
    assert_false(iterator_less(it_first, it_second));
    vector_destroy(pvec);
}

void test_iterator_less__deque_less(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it_first;
    iterator_t it_second;

    deque_init_n(pdeq, 10);
    it_first =  deque_begin(pdeq);
    it_second = deque_end(pdeq);
    assert_true(iterator_less(it_first, it_second));
    deque_destroy(pdeq);
}

void test_iterator_less__deque_equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it_first;
    iterator_t it_second;

    deque_init_n(pdeq, 10);
    it_first =  deque_begin(pdeq);
    it_second = deque_begin(pdeq);
    assert_false(iterator_less(it_first, it_second));
    deque_destroy(pdeq);
}

void test_iterator_less__deque_greater(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it_first;
    iterator_t it_second;

    deque_init_n(pdeq, 10);
    it_first =  deque_end(pdeq);
    it_second = deque_begin(pdeq);
    assert_false(iterator_less(it_first, it_second));
    deque_destroy(pdeq);
}

void test_iterator_less__list(void** state)
{
    list_t* plist = create_list(int);
    iterator_t it_first;
    iterator_t it_second;

    list_init_n(plist, 10);
    it_first = it_second = list_begin(plist);
    expect_assert_failure(iterator_less(it_first, it_second));
    list_destroy(plist);
}

void test_iterator_less__slist(void** state)
{
    slist_t* pslist = create_slist(int);
    iterator_t it_first;
    iterator_t it_second;

    slist_init_n(pslist, 10);
    it_first = it_second = slist_begin(pslist);
    expect_assert_failure(iterator_less(it_first, it_second));
    slist_destroy(pslist);
}

void test_iterator_less__set(void** state)
{
    set_t* pset = create_set(int);
    iterator_t it_first;
    iterator_t it_second;

    set_init(pset);
    set_insert(pset, 1);
    it_first = it_second = set_begin(pset);
    expect_assert_failure(iterator_less(it_first, it_second));
    set_destroy(pset);
}

void test_iterator_less__multiset(void** state)
{
    multiset_t* pset = create_multiset(int);
    iterator_t it_first;
    iterator_t it_second;

    multiset_init(pset);
    multiset_insert(pset, 1);
    it_first = it_second = multiset_begin(pset);
    expect_assert_failure(iterator_less(it_first, it_second));
    multiset_destroy(pset);
}

void test_iterator_less__map(void** state)
{
    map_t* pmap = create_map(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    map_init(pmap);
    pair_init(ppair);
    map_insert(pmap, ppair);
    it_first = it_second = map_begin(pmap);
    expect_assert_failure(iterator_less(it_first, it_second));
    pair_destroy(ppair);
    map_destroy(pmap);
}

void test_iterator_less__multimap(void** state)
{
    multimap_t* pmap = create_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    multimap_init(pmap);
    pair_init(ppair);
    multimap_insert(pmap, ppair);
    it_first = it_second = multimap_begin(pmap);
    expect_assert_failure(iterator_less(it_first, it_second));
    pair_destroy(ppair);
    multimap_destroy(pmap);
}

void test_iterator_less__hash_set(void** state)
{
    hash_set_t* phset = create_hash_set(int);
    iterator_t it_first;
    iterator_t it_second;

    hash_set_init(phset);
    hash_set_insert(phset, 1);
    it_first = it_second = hash_set_begin(phset);
    expect_assert_failure(iterator_less(it_first, it_second));
    hash_set_destroy(phset);
}

void test_iterator_less__hash_multiset(void** state)
{
    hash_multiset_t* phset = create_hash_multiset(int);
    iterator_t it_first;
    iterator_t it_second;

    hash_multiset_init(phset);
    hash_multiset_insert(phset, 1);
    it_first = it_second = hash_multiset_begin(phset);
    expect_assert_failure(iterator_less(it_first, it_second));
    hash_multiset_destroy(phset);
}

void test_iterator_less__hash_map(void** state)
{
    hash_map_t* pmap = create_hash_map(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    hash_map_init(pmap);
    pair_init(ppair);
    hash_map_insert(pmap, ppair);
    it_first = it_second = hash_map_begin(pmap);
    expect_assert_failure(iterator_less(it_first, it_second));
    pair_destroy(ppair);
    hash_map_destroy(pmap);
}

void test_iterator_less__hash_multimap(void** state)
{
    hash_multimap_t* pmap = create_hash_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    hash_multimap_init(pmap);
    pair_init(ppair);
    hash_multimap_insert(pmap, ppair);
    it_first = it_second = hash_multimap_begin(pmap);
    expect_assert_failure(iterator_less(it_first, it_second));
    pair_destroy(ppair);
    hash_multimap_destroy(pmap);
}

void test_iterator_less__string_less(void** state)
{
    string_t* pstr = create_string();
    iterator_t it_first;
    iterator_t it_second;

    string_init_cstr(pstr, "abcdefg");
    it_first = string_begin(pstr);
    it_second = string_end(pstr);
    assert_true(iterator_less(it_first, it_second));
    string_destroy(pstr);
}

void test_iterator_less__string_equal(void** state)
{
    string_t* pstr = create_string();
    iterator_t it_first;
    iterator_t it_second;

    string_init_cstr(pstr, "abcdefg");
    it_first = string_begin(pstr);
    it_second = string_begin(pstr);
    assert_false(iterator_less(it_first, it_second));
    string_destroy(pstr);
}

void test_iterator_less__string_greater(void** state)
{
    string_t* pstr = create_string();
    iterator_t it_first;
    iterator_t it_second;

    string_init_cstr(pstr, "abcdefg");
    it_first = string_end(pstr);
    it_second = string_begin(pstr);
    assert_false(iterator_less(it_first, it_second));
    string_destroy(pstr);
}

/*
 * test iteator_less_equal
 */
UT_CASE_DEFINATION(iterator_less_equal)
void test_iterator_less_equal__invalid_first(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_first;
    iterator_t it_second;

    vector_init(pvec);
    it_first = it_second = vector_begin(pvec);
    it_first._t_iteratortype = 4444;
    expect_assert_failure(iterator_less_equal(it_first, it_second));
    vector_destroy(pvec);
}

void test_iterator_less_equal__invalid_second(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_first;
    iterator_t it_second;

    vector_init(pvec);
    it_first = it_second = vector_begin(pvec);
    it_second._t_iteratortype = 4444;
    expect_assert_failure(iterator_less_equal(it_first, it_second));
    vector_destroy(pvec);
}

void test_iterator_less_equal__vector_less(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_first;
    iterator_t it_second;

    vector_init_n(pvec, 10);
    it_first = vector_begin(pvec);
    it_second = vector_end(pvec);
    assert_true(iterator_less_equal(it_first, it_second));
    vector_destroy(pvec);
}

void test_iterator_less_equal__vector_equal(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_first;
    iterator_t it_second;

    vector_init_n(pvec, 10);
    it_first = vector_begin(pvec);
    it_second = vector_begin(pvec);
    assert_true(iterator_less_equal(it_first, it_second));
    vector_destroy(pvec);
}

void test_iterator_less_equal__vector_greater(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_first;
    iterator_t it_second;

    vector_init_n(pvec, 10);
    it_first = vector_end(pvec);
    it_second = vector_begin(pvec);
    assert_false(iterator_less_equal(it_first, it_second));
    vector_destroy(pvec);
}

void test_iterator_less_equal__deque_less(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it_first;
    iterator_t it_second;

    deque_init_n(pdeq, 10);
    it_first =  deque_begin(pdeq);
    it_second = deque_end(pdeq);
    assert_true(iterator_less_equal(it_first, it_second));
    deque_destroy(pdeq);
}

void test_iterator_less_equal__deque_equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it_first;
    iterator_t it_second;

    deque_init_n(pdeq, 10);
    it_first =  deque_begin(pdeq);
    it_second = deque_begin(pdeq);
    assert_true(iterator_less_equal(it_first, it_second));
    deque_destroy(pdeq);
}

void test_iterator_less_equal__deque_greater(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it_first;
    iterator_t it_second;

    deque_init_n(pdeq, 10);
    it_first =  deque_end(pdeq);
    it_second = deque_begin(pdeq);
    assert_false(iterator_less_equal(it_first, it_second));
    deque_destroy(pdeq);
}

void test_iterator_less_equal__list(void** state)
{
    list_t* plist = create_list(int);
    iterator_t it_first;
    iterator_t it_second;

    list_init_n(plist, 10);
    it_first = it_second = list_begin(plist);
    expect_assert_failure(iterator_less_equal(it_first, it_second));
    list_destroy(plist);
}

void test_iterator_less_equal__slist(void** state)
{
    slist_t* pslist = create_slist(int);
    iterator_t it_first;
    iterator_t it_second;

    slist_init_n(pslist, 10);
    it_first = it_second = slist_begin(pslist);
    expect_assert_failure(iterator_less_equal(it_first, it_second));
    slist_destroy(pslist);
}

void test_iterator_less_equal__set(void** state)
{
    set_t* pset = create_set(int);
    iterator_t it_first;
    iterator_t it_second;

    set_init(pset);
    set_insert(pset, 1);
    it_first = it_second = set_begin(pset);
    expect_assert_failure(iterator_less_equal(it_first, it_second));
    set_destroy(pset);
}

void test_iterator_less_equal__multiset(void** state)
{
    multiset_t* pset = create_multiset(int);
    iterator_t it_first;
    iterator_t it_second;

    multiset_init(pset);
    multiset_insert(pset, 1);
    it_first = it_second = multiset_begin(pset);
    expect_assert_failure(iterator_less_equal(it_first, it_second));
    multiset_destroy(pset);
}

void test_iterator_less_equal__map(void** state)
{
    map_t* pmap = create_map(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    map_init(pmap);
    pair_init(ppair);
    map_insert(pmap, ppair);
    it_first = it_second = map_begin(pmap);
    expect_assert_failure(iterator_less_equal(it_first, it_second));
    pair_destroy(ppair);
    map_destroy(pmap);
}

void test_iterator_less_equal__multimap(void** state)
{
    multimap_t* pmap = create_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    multimap_init(pmap);
    pair_init(ppair);
    multimap_insert(pmap, ppair);
    it_first = it_second = multimap_begin(pmap);
    expect_assert_failure(iterator_less_equal(it_first, it_second));
    pair_destroy(ppair);
    multimap_destroy(pmap);
}

void test_iterator_less_equal__hash_set(void** state)
{
    hash_set_t* phset = create_hash_set(int);
    iterator_t it_first;
    iterator_t it_second;

    hash_set_init(phset);
    hash_set_insert(phset, 1);
    it_first = it_second = hash_set_begin(phset);
    expect_assert_failure(iterator_less_equal(it_first, it_second));
    hash_set_destroy(phset);
}

void test_iterator_less_equal__hash_multiset(void** state)
{
    hash_multiset_t* phset = create_hash_multiset(int);
    iterator_t it_first;
    iterator_t it_second;

    hash_multiset_init(phset);
    hash_multiset_insert(phset, 1);
    it_first = it_second = hash_multiset_begin(phset);
    expect_assert_failure(iterator_less_equal(it_first, it_second));
    hash_multiset_destroy(phset);
}

void test_iterator_less_equal__hash_map(void** state)
{
    hash_map_t* pmap = create_hash_map(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    hash_map_init(pmap);
    pair_init(ppair);
    hash_map_insert(pmap, ppair);
    it_first = it_second = hash_map_begin(pmap);
    expect_assert_failure(iterator_less_equal(it_first, it_second));
    pair_destroy(ppair);
    hash_map_destroy(pmap);
}

void test_iterator_less_equal__hash_multimap(void** state)
{
    hash_multimap_t* pmap = create_hash_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    hash_multimap_init(pmap);
    pair_init(ppair);
    hash_multimap_insert(pmap, ppair);
    it_first = it_second = hash_multimap_begin(pmap);
    expect_assert_failure(iterator_less_equal(it_first, it_second));
    pair_destroy(ppair);
    hash_multimap_destroy(pmap);
}

void test_iterator_less_equal__string_less(void** state)
{
    string_t* pstr = create_string();
    iterator_t it_first;
    iterator_t it_second;

    string_init_cstr(pstr, "abcdefg");
    it_first = string_begin(pstr);
    it_second = string_end(pstr);
    assert_true(iterator_less_equal(it_first, it_second));
    string_destroy(pstr);
}

void test_iterator_less_equal__string_equal(void** state)
{
    string_t* pstr = create_string();
    iterator_t it_first;
    iterator_t it_second;

    string_init_cstr(pstr, "abcdefg");
    it_first = string_begin(pstr);
    it_second = string_begin(pstr);
    assert_true(iterator_less_equal(it_first, it_second));
    string_destroy(pstr);
}

void test_iterator_less_equal__string_greater(void** state)
{
    string_t* pstr = create_string();
    iterator_t it_first;
    iterator_t it_second;

    string_init_cstr(pstr, "abcdefg");
    it_first = string_end(pstr);
    it_second = string_begin(pstr);
    assert_false(iterator_less_equal(it_first, it_second));
    string_destroy(pstr);
}

/*
 * test iteator_greater
 */
UT_CASE_DEFINATION(iterator_greater)
void test_iterator_greater__invalid_first(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_first;
    iterator_t it_second;

    vector_init(pvec);
    it_first = it_second = vector_begin(pvec);
    it_first._t_iteratortype = 4444;
    expect_assert_failure(iterator_greater(it_first, it_second));
    vector_destroy(pvec);
}

void test_iterator_greater__invalid_second(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_first;
    iterator_t it_second;

    vector_init(pvec);
    it_first = it_second = vector_begin(pvec);
    it_second._t_iteratortype = 4444;
    expect_assert_failure(iterator_greater(it_first, it_second));
    vector_destroy(pvec);
}

void test_iterator_greater__vector_less(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_first;
    iterator_t it_second;

    vector_init_n(pvec, 10);
    it_first = vector_begin(pvec);
    it_second = vector_end(pvec);
    assert_false(iterator_greater(it_first, it_second));
    vector_destroy(pvec);
}

void test_iterator_greater__vector_equal(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_first;
    iterator_t it_second;

    vector_init_n(pvec, 10);
    it_first = vector_begin(pvec);
    it_second = vector_begin(pvec);
    assert_false(iterator_greater(it_first, it_second));
    vector_destroy(pvec);
}

void test_iterator_greater__vector_greater(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_first;
    iterator_t it_second;

    vector_init_n(pvec, 10);
    it_first = vector_end(pvec);
    it_second = vector_begin(pvec);
    assert_true(iterator_greater(it_first, it_second));
    vector_destroy(pvec);
}

void test_iterator_greater__deque_less(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it_first;
    iterator_t it_second;

    deque_init_n(pdeq, 10);
    it_first =  deque_begin(pdeq);
    it_second = deque_end(pdeq);
    assert_false(iterator_greater(it_first, it_second));
    deque_destroy(pdeq);
}

void test_iterator_greater__deque_equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it_first;
    iterator_t it_second;

    deque_init_n(pdeq, 10);
    it_first =  deque_begin(pdeq);
    it_second = deque_begin(pdeq);
    assert_false(iterator_greater(it_first, it_second));
    deque_destroy(pdeq);
}

void test_iterator_greater__deque_greater(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it_first;
    iterator_t it_second;

    deque_init_n(pdeq, 10);
    it_first =  deque_end(pdeq);
    it_second = deque_begin(pdeq);
    assert_true(iterator_greater(it_first, it_second));
    deque_destroy(pdeq);
}

void test_iterator_greater__list(void** state)
{
    list_t* plist = create_list(int);
    iterator_t it_first;
    iterator_t it_second;

    list_init_n(plist, 10);
    it_first = it_second = list_begin(plist);
    expect_assert_failure(iterator_greater(it_first, it_second));
    list_destroy(plist);
}

void test_iterator_greater__slist(void** state)
{
    slist_t* pslist = create_slist(int);
    iterator_t it_first;
    iterator_t it_second;

    slist_init_n(pslist, 10);
    it_first = it_second = slist_begin(pslist);
    expect_assert_failure(iterator_greater(it_first, it_second));
    slist_destroy(pslist);
}

void test_iterator_greater__set(void** state)
{
    set_t* pset = create_set(int);
    iterator_t it_first;
    iterator_t it_second;

    set_init(pset);
    set_insert(pset, 1);
    it_first = it_second = set_begin(pset);
    expect_assert_failure(iterator_greater(it_first, it_second));
    set_destroy(pset);
}

void test_iterator_greater__multiset(void** state)
{
    multiset_t* pset = create_multiset(int);
    iterator_t it_first;
    iterator_t it_second;

    multiset_init(pset);
    multiset_insert(pset, 1);
    it_first = it_second = multiset_begin(pset);
    expect_assert_failure(iterator_greater(it_first, it_second));
    multiset_destroy(pset);
}

void test_iterator_greater__map(void** state)
{
    map_t* pmap = create_map(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    map_init(pmap);
    pair_init(ppair);
    map_insert(pmap, ppair);
    it_first = it_second = map_begin(pmap);
    expect_assert_failure(iterator_greater(it_first, it_second));
    pair_destroy(ppair);
    map_destroy(pmap);
}

void test_iterator_greater__multimap(void** state)
{
    multimap_t* pmap = create_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    multimap_init(pmap);
    pair_init(ppair);
    multimap_insert(pmap, ppair);
    it_first = it_second = multimap_begin(pmap);
    expect_assert_failure(iterator_greater(it_first, it_second));
    pair_destroy(ppair);
    multimap_destroy(pmap);
}

void test_iterator_greater__hash_set(void** state)
{
    hash_set_t* phset = create_hash_set(int);
    iterator_t it_first;
    iterator_t it_second;

    hash_set_init(phset);
    hash_set_insert(phset, 1);
    it_first = it_second = hash_set_begin(phset);
    expect_assert_failure(iterator_greater(it_first, it_second));
    hash_set_destroy(phset);
}

void test_iterator_greater__hash_multiset(void** state)
{
    hash_multiset_t* phset = create_hash_multiset(int);
    iterator_t it_first;
    iterator_t it_second;

    hash_multiset_init(phset);
    hash_multiset_insert(phset, 1);
    it_first = it_second = hash_multiset_begin(phset);
    expect_assert_failure(iterator_greater(it_first, it_second));
    hash_multiset_destroy(phset);
}

void test_iterator_greater__hash_map(void** state)
{
    hash_map_t* pmap = create_hash_map(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    hash_map_init(pmap);
    pair_init(ppair);
    hash_map_insert(pmap, ppair);
    it_first = it_second = hash_map_begin(pmap);
    expect_assert_failure(iterator_greater(it_first, it_second));
    pair_destroy(ppair);
    hash_map_destroy(pmap);
}

void test_iterator_greater__hash_multimap(void** state)
{
    hash_multimap_t* pmap = create_hash_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    hash_multimap_init(pmap);
    pair_init(ppair);
    hash_multimap_insert(pmap, ppair);
    it_first = it_second = hash_multimap_begin(pmap);
    expect_assert_failure(iterator_greater(it_first, it_second));
    pair_destroy(ppair);
    hash_multimap_destroy(pmap);
}

void test_iterator_greater__string_less(void** state)
{
    string_t* pstr = create_string();
    iterator_t it_first;
    iterator_t it_second;

    string_init_cstr(pstr, "abcdefg");
    it_first = string_begin(pstr);
    it_second = string_end(pstr);
    assert_false(iterator_greater(it_first, it_second));
    string_destroy(pstr);
}

void test_iterator_greater__string_equal(void** state)
{
    string_t* pstr = create_string();
    iterator_t it_first;
    iterator_t it_second;

    string_init_cstr(pstr, "abcdefg");
    it_first = string_begin(pstr);
    it_second = string_begin(pstr);
    assert_false(iterator_greater(it_first, it_second));
    string_destroy(pstr);
}

void test_iterator_greater__string_greater(void** state)
{
    string_t* pstr = create_string();
    iterator_t it_first;
    iterator_t it_second;

    string_init_cstr(pstr, "abcdefg");
    it_first = string_end(pstr);
    it_second = string_begin(pstr);
    assert_true(iterator_greater(it_first, it_second));
    string_destroy(pstr);
}

/*
 * test iteator_greater
 */
UT_CASE_DEFINATION(iterator_greater_equal)
void test_iterator_greater_equal__invalid_first(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_first;
    iterator_t it_second;

    vector_init(pvec);
    it_first = it_second = vector_begin(pvec);
    it_first._t_iteratortype = 4444;
    expect_assert_failure(iterator_greater_equal(it_first, it_second));
    vector_destroy(pvec);
}

void test_iterator_greater_equal__invalid_second(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_first;
    iterator_t it_second;

    vector_init(pvec);
    it_first = it_second = vector_begin(pvec);
    it_second._t_iteratortype = 4444;
    expect_assert_failure(iterator_greater_equal(it_first, it_second));
    vector_destroy(pvec);
}

void test_iterator_greater_equal__vector_less(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_first;
    iterator_t it_second;

    vector_init_n(pvec, 10);
    it_first = vector_begin(pvec);
    it_second = vector_end(pvec);
    assert_false(iterator_greater_equal(it_first, it_second));
    vector_destroy(pvec);
}

void test_iterator_greater_equal__vector_equal(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_first;
    iterator_t it_second;

    vector_init_n(pvec, 10);
    it_first = vector_begin(pvec);
    it_second = vector_begin(pvec);
    assert_true(iterator_greater_equal(it_first, it_second));
    vector_destroy(pvec);
}

void test_iterator_greater_equal__vector_greater(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_first;
    iterator_t it_second;

    vector_init_n(pvec, 10);
    it_first = vector_end(pvec);
    it_second = vector_begin(pvec);
    assert_true(iterator_greater_equal(it_first, it_second));
    vector_destroy(pvec);
}

void test_iterator_greater_equal__deque_less(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it_first;
    iterator_t it_second;

    deque_init_n(pdeq, 10);
    it_first =  deque_begin(pdeq);
    it_second = deque_end(pdeq);
    assert_false(iterator_greater_equal(it_first, it_second));
    deque_destroy(pdeq);
}

void test_iterator_greater_equal__deque_equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it_first;
    iterator_t it_second;

    deque_init_n(pdeq, 10);
    it_first =  deque_begin(pdeq);
    it_second = deque_begin(pdeq);
    assert_true(iterator_greater_equal(it_first, it_second));
    deque_destroy(pdeq);
}

void test_iterator_greater_equal__deque_greater(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it_first;
    iterator_t it_second;

    deque_init_n(pdeq, 10);
    it_first =  deque_end(pdeq);
    it_second = deque_begin(pdeq);
    assert_true(iterator_greater_equal(it_first, it_second));
    deque_destroy(pdeq);
}

void test_iterator_greater_equal__list(void** state)
{
    list_t* plist = create_list(int);
    iterator_t it_first;
    iterator_t it_second;

    list_init_n(plist, 10);
    it_first = it_second = list_begin(plist);
    expect_assert_failure(iterator_greater_equal(it_first, it_second));
    list_destroy(plist);
}

void test_iterator_greater_equal__slist(void** state)
{
    slist_t* pslist = create_slist(int);
    iterator_t it_first;
    iterator_t it_second;

    slist_init_n(pslist, 10);
    it_first = it_second = slist_begin(pslist);
    expect_assert_failure(iterator_greater_equal(it_first, it_second));
    slist_destroy(pslist);
}

void test_iterator_greater_equal__set(void** state)
{
    set_t* pset = create_set(int);
    iterator_t it_first;
    iterator_t it_second;

    set_init(pset);
    set_insert(pset, 1);
    it_first = it_second = set_begin(pset);
    expect_assert_failure(iterator_greater_equal(it_first, it_second));
    set_destroy(pset);
}

void test_iterator_greater_equal__multiset(void** state)
{
    multiset_t* pset = create_multiset(int);
    iterator_t it_first;
    iterator_t it_second;

    multiset_init(pset);
    multiset_insert(pset, 1);
    it_first = it_second = multiset_begin(pset);
    expect_assert_failure(iterator_greater_equal(it_first, it_second));
    multiset_destroy(pset);
}

void test_iterator_greater_equal__map(void** state)
{
    map_t* pmap = create_map(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    map_init(pmap);
    pair_init(ppair);
    map_insert(pmap, ppair);
    it_first = it_second = map_begin(pmap);
    expect_assert_failure(iterator_greater_equal(it_first, it_second));
    pair_destroy(ppair);
    map_destroy(pmap);
}

void test_iterator_greater_equal__multimap(void** state)
{
    multimap_t* pmap = create_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    multimap_init(pmap);
    pair_init(ppair);
    multimap_insert(pmap, ppair);
    it_first = it_second = multimap_begin(pmap);
    expect_assert_failure(iterator_greater_equal(it_first, it_second));
    pair_destroy(ppair);
    multimap_destroy(pmap);
}

void test_iterator_greater_equal__hash_set(void** state)
{
    hash_set_t* phset = create_hash_set(int);
    iterator_t it_first;
    iterator_t it_second;

    hash_set_init(phset);
    hash_set_insert(phset, 1);
    it_first = it_second = hash_set_begin(phset);
    expect_assert_failure(iterator_greater_equal(it_first, it_second));
    hash_set_destroy(phset);
}

void test_iterator_greater_equal__hash_multiset(void** state)
{
    hash_multiset_t* phset = create_hash_multiset(int);
    iterator_t it_first;
    iterator_t it_second;

    hash_multiset_init(phset);
    hash_multiset_insert(phset, 1);
    it_first = it_second = hash_multiset_begin(phset);
    expect_assert_failure(iterator_greater_equal(it_first, it_second));
    hash_multiset_destroy(phset);
}

void test_iterator_greater_equal__hash_map(void** state)
{
    hash_map_t* pmap = create_hash_map(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    hash_map_init(pmap);
    pair_init(ppair);
    hash_map_insert(pmap, ppair);
    it_first = it_second = hash_map_begin(pmap);
    expect_assert_failure(iterator_greater_equal(it_first, it_second));
    pair_destroy(ppair);
    hash_map_destroy(pmap);
}

void test_iterator_greater_equal__hash_multimap(void** state)
{
    hash_multimap_t* pmap = create_hash_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    hash_multimap_init(pmap);
    pair_init(ppair);
    hash_multimap_insert(pmap, ppair);
    it_first = it_second = hash_multimap_begin(pmap);
    expect_assert_failure(iterator_greater_equal(it_first, it_second));
    pair_destroy(ppair);
    hash_multimap_destroy(pmap);
}

void test_iterator_greater_equal__string_less(void** state)
{
    string_t* pstr = create_string();
    iterator_t it_first;
    iterator_t it_second;

    string_init_cstr(pstr, "abcdefg");
    it_first = string_begin(pstr);
    it_second = string_end(pstr);
    assert_false(iterator_greater_equal(it_first, it_second));
    string_destroy(pstr);
}

void test_iterator_greater_equal__string_equal(void** state)
{
    string_t* pstr = create_string();
    iterator_t it_first;
    iterator_t it_second;

    string_init_cstr(pstr, "abcdefg");
    it_first = string_begin(pstr);
    it_second = string_begin(pstr);
    assert_true(iterator_greater_equal(it_first, it_second));
    string_destroy(pstr);
}

void test_iterator_greater_equal__string_greater(void** state)
{
    string_t* pstr = create_string();
    iterator_t it_first;
    iterator_t it_second;

    string_init_cstr(pstr, "abcdefg");
    it_first = string_end(pstr);
    it_second = string_begin(pstr);
    assert_true(iterator_greater_equal(it_first, it_second));
    string_destroy(pstr);
}

/*
 * test iterator_at
 */
UT_CASE_DEFINATION(iterator_at)
void test_iterator_at__invalid_iter(void** state)
{
    iterator_t it_iter;
    it_iter._t_containertype = 999;
    it_iter._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(iterator_at(it_iter, 10));
}

void test_iterator_at__vector_0(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_iter;

    vector_init(pvec);
    vector_push_back(pvec, 1);
    vector_push_back(pvec, 2);
    vector_push_back(pvec, 3);

    it_iter = vector_begin(pvec);
    assert_true(*(int*)iterator_at(it_iter, 0) == 1);

    vector_destroy(pvec);
}

void test_iterator_at__vector_n(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_iter;
    int i = 0;

    vector_init(pvec);
    for(i = 0; i < 10; ++i)
    {
        vector_push_back(pvec, i);
    }

    it_iter = vector_begin(pvec);
    assert_true(*(int*)iterator_at(it_iter, 5) == 5);

    vector_destroy(pvec);
}

void test_iterator_at__vector_n_(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_iter;
    int i = 0;

    vector_init(pvec);
    for(i = 0; i < 10; ++i)
    {
        vector_push_back(pvec, i);
    }

    it_iter = iterator_prev(vector_end(pvec));
    assert_true(*(int*)iterator_at(it_iter, -5) == 4);

    vector_destroy(pvec);
}

void test_iterator_at__vector_end_n(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_iter;
    int i = 0;

    vector_init(pvec);
    for(i = 0; i < 10; ++i)
    {
        vector_push_back(pvec, i);
    }

    it_iter = vector_begin(pvec);
    expect_assert_failure(iterator_at(it_iter, 15));

    vector_destroy(pvec);
}

void test_iterator_at__vector_prev_n(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_iter;
    int i = 0;

    vector_init(pvec);
    for(i = 0; i < 10; ++i)
    {
        vector_push_back(pvec, i);
    }

    it_iter = iterator_prev(vector_end(pvec));
    expect_assert_failure(iterator_at(it_iter, -15));

    vector_destroy(pvec);
}

void test_iterator_at__deque_0(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it_iter;

    deque_init(pdeq);
    deque_push_back(pdeq, 1);
    deque_push_back(pdeq, 2);

    it_iter = deque_begin(pdeq);
    assert_true(*(int*)iterator_at(it_iter, 0) == 1);
    deque_destroy(pdeq);
}

void test_iterator_at__deque_n(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it_iter;
    int i = 0;

    deque_init(pdeq);
    for(i = 0; i < 10; ++i)
    {
        deque_push_back(pdeq, i);
    }

    it_iter = deque_begin(pdeq);
    assert_true(*(int*)iterator_at(it_iter, 5) == 5);
    deque_destroy(pdeq);
}

void test_iterator_at__deque_n_(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it_iter;
    int i = 0;

    deque_init(pdeq);
    for(i = 0; i < 10; ++i)
    {
        deque_push_back(pdeq, i);
    }

    it_iter = iterator_prev(deque_end(pdeq));
    assert_true(*(int*)iterator_at(it_iter, -5) == 4);
    deque_destroy(pdeq);
}

void test_iterator_at__deque_end_n(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it_iter;
    int i = 0;

    deque_init(pdeq);
    for(i = 0; i < 10; ++i)
    {
        deque_push_back(pdeq, i);
    }

    it_iter = deque_begin(pdeq);
    expect_assert_failure(iterator_at(it_iter, 15));
    deque_destroy(pdeq);
}

void test_iterator_at__deque_prev_n(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it_iter;
    int i = 0;

    deque_init(pdeq);
    for(i = 0; i < 10; ++i)
    {
        deque_push_back(pdeq, i);
    }

    it_iter = iterator_prev(deque_end(pdeq));
    expect_assert_failure(iterator_at(it_iter, -15));
    deque_destroy(pdeq);
}

void test_iterator_at__list(void** state)
{
    list_t* plist = create_list(int);
    iterator_t it_iter;

    list_init(plist);
    list_push_back(plist, 1);
    list_push_back(plist, 2);

    it_iter = list_begin(plist);
    expect_assert_failure(iterator_at(it_iter, 1));

    list_destroy(plist);
}

void test_iterator_at__slist(void** state)
{
    slist_t* pslist = create_slist(int);
    iterator_t it_iter;

    slist_init(pslist);
    slist_push_front(pslist, 1);
    slist_push_front(pslist, 2);
    it_iter = slist_begin(pslist);
    expect_assert_failure(iterator_at(it_iter, 1));
    slist_destroy(pslist);
}

void test_iterator_at__set(void** state)
{
    set_t* pset = create_set(int);
    iterator_t it_iter;

    set_init(pset);
    set_insert(pset, 1);
    set_insert(pset, 2);
    it_iter = set_begin(pset);
    expect_assert_failure(iterator_at(it_iter, 1));
    set_destroy(pset);
}

void test_iterator_at__multiset(void** state)
{
    multiset_t* pmset = create_multiset(int);
    iterator_t it_iter;

    multiset_init(pmset);
    multiset_insert(pmset, 1);
    multiset_insert(pmset, 2);
    it_iter = multiset_begin(pmset);
    expect_assert_failure(iterator_at(it_iter, 1));
    multiset_destroy(pmset);
}

void test_iterator_at__map(void** state)
{
    map_t* pmap = create_map(int, int);
    iterator_t it_iter;

    map_init(pmap);
    *(int*)map_at(pmap, 1) = 10;
    *(int*)map_at(pmap, 2) = 20;
    it_iter = map_begin(pmap);
    expect_assert_failure(iterator_at(it_iter, 1));
    map_destroy(pmap);
}

void test_iterator_at__multimap(void** state)
{
    multimap_t* pmmap = create_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_iter;

    multimap_init(pmmap);
    pair_init(ppair);
    pair_make(ppair, 1, 1);
    multimap_insert(pmmap, ppair);
    pair_make(ppair, 2, 2);
    multimap_insert(pmmap, ppair);
    it_iter = multimap_begin(pmmap);
    expect_assert_failure(iterator_at(it_iter, 1));
    pair_destroy(ppair);
    multimap_destroy(pmmap);
}

void test_iterator_at__hash_set(void** state)
{
    hash_set_t* phset = create_hash_set(int);
    iterator_t it_iter;

    hash_set_init(phset);
    hash_set_insert(phset, 1);
    hash_set_insert(phset, 2);
    it_iter = hash_set_begin(phset);
    expect_assert_failure(iterator_at(it_iter, 1));
    hash_set_destroy(phset);
}

void test_iterator_at__hash_multiset(void** state)
{
    hash_multiset_t* phmset = create_hash_multiset(int);
    iterator_t it_iter;

    hash_multiset_init(phmset);
    hash_multiset_insert(phmset, 1);
    hash_multiset_insert(phmset, 2);
    it_iter = hash_multiset_begin(phmset);
    expect_assert_failure(iterator_at(it_iter, 1));
    hash_multiset_destroy(phmset);
}

void test_iterator_at__hash_map(void** state)
{
    hash_map_t* phmap = create_hash_map(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_iter;

    hash_map_init(phmap);
    pair_init(ppair);
    pair_make(ppair, 0, 0);
    hash_map_insert(phmap, ppair);
    pair_make(ppair, 1, 1);
    hash_map_insert(phmap, ppair);
    it_iter = hash_map_begin(phmap);
    expect_assert_failure(iterator_at(it_iter, 1));
    pair_destroy(ppair);
    hash_map_destroy(phmap);
}

void test_iterator_at__hash_multimap(void** state)
{
    hash_multimap_t* phmap = create_hash_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_iter;

    hash_multimap_init(phmap);
    pair_init(ppair);
    pair_make(ppair, 0, 0);
    hash_multimap_insert(phmap, ppair);
    pair_make(ppair, 1, 1);
    hash_multimap_insert(phmap, ppair);
    it_iter = hash_multimap_begin(phmap);
    expect_assert_failure(iterator_at(it_iter, 1));
    pair_destroy(ppair);
    hash_multimap_destroy(phmap);
}

void test_iterator_at__string_0(void** state)
{
    string_t* pstr = create_string();
    iterator_t it_iter;

    string_init_cstr(pstr, "abcdefg");
    it_iter = string_begin(pstr);
    assert_true(*(char*)iterator_at(it_iter, 0) == 'a');
    string_destroy(pstr);
}

void test_iterator_at__string_n(void** state)
{
    string_t* pstr = create_string();
    iterator_t it_iter;

    string_init_cstr(pstr, "abcdefghijklmn");
    it_iter = string_begin(pstr);
    assert_true(*(char*)iterator_at(it_iter, 5) == 'f');
    string_destroy(pstr);
}

void test_iterator_at__string_n_(void** state)
{
    string_t* pstr = create_string();
    iterator_t it_iter;

    string_init_cstr(pstr, "abcdefghijklmn");
    it_iter = iterator_prev(string_end(pstr));
    assert_true(*(char*)iterator_at(it_iter, -5) == 'i');
    string_destroy(pstr);
}

void test_iterator_at__string_end_n(void** state)
{
    string_t* pstr = create_string();
    iterator_t it_iter;

    string_init_cstr(pstr, "abcdefghijklmn");
    it_iter = string_begin(pstr);
    expect_assert_failure(iterator_at(it_iter, 25));
    string_destroy(pstr);
}

void test_iterator_at__string_prev_n(void** state)
{
    string_t* pstr = create_string();
    iterator_t it_iter;

    string_init_cstr(pstr, "abcdefghijklmn");
    it_iter = iterator_prev(string_end(pstr));
    expect_assert_failure(iterator_at(it_iter, -35));
    string_destroy(pstr);
}

/*
 * test iteator_minus
 */
UT_CASE_DEFINATION(iterator_minus)
void test_iterator_minus__invalid_first(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_first;
    iterator_t it_second;

    vector_init(pvec);
    it_first = it_second = vector_begin(pvec);
    it_first._t_iteratortype = 4444;
    expect_assert_failure(iterator_minus(it_first, it_second));
    vector_destroy(pvec);
}

void test_iterator_minus__invalid_second(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_first;
    iterator_t it_second;

    vector_init(pvec);
    it_first = it_second = vector_begin(pvec);
    it_second._t_iteratortype = 4444;
    expect_assert_failure(iterator_minus(it_first, it_second));
    vector_destroy(pvec);
}

void test_iterator_minus__not_same_container(void** state)
{
    vector_t* pvec0 = create_vector(int);
    vector_t* pvec1 = create_vector(int);

    vector_init(pvec0);
    vector_init(pvec1);
    expect_assert_failure(iterator_minus(vector_begin(pvec0), vector_begin(pvec1)));
    vector_destroy(pvec0);
    vector_destroy(pvec1);
}

void test_iterator_minus__vector_less(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_first;
    iterator_t it_second;

    vector_init_n(pvec, 10);
    it_first = vector_begin(pvec);
    it_second = vector_end(pvec);
    assert_true(iterator_minus(it_first, it_second) == -10);
    vector_destroy(pvec);
}

void test_iterator_minus__vector_equal(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_first;
    iterator_t it_second;

    vector_init_n(pvec, 10);
    it_first = vector_begin(pvec);
    it_second = vector_begin(pvec);
    assert_true(iterator_minus(it_first, it_second) == 0);
    vector_destroy(pvec);
}

void test_iterator_minus__vector_greater(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_first;
    iterator_t it_second;

    vector_init_n(pvec, 10);
    it_first = vector_end(pvec);
    it_second = vector_begin(pvec);
    assert_true(iterator_minus(it_first, it_second) == 10);
    vector_destroy(pvec);
}

void test_iterator_minus__deque_less(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it_first;
    iterator_t it_second;

    deque_init_n(pdeq, 10);
    it_first =  deque_begin(pdeq);
    it_second = deque_end(pdeq);
    assert_true(iterator_minus(it_first, it_second) == -10);
    deque_destroy(pdeq);
}

void test_iterator_minus__deque_equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it_first;
    iterator_t it_second;

    deque_init_n(pdeq, 10);
    it_first =  deque_begin(pdeq);
    it_second = deque_begin(pdeq);
    assert_true(iterator_minus(it_first, it_second) == 0);
    deque_destroy(pdeq);
}

void test_iterator_minus__deque_greater(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it_first;
    iterator_t it_second;

    deque_init_n(pdeq, 10);
    it_first =  deque_end(pdeq);
    it_second = deque_begin(pdeq);
    assert_true(iterator_minus(it_first, it_second) == 10);
    deque_destroy(pdeq);
}

void test_iterator_minus__list(void** state)
{
    list_t* plist = create_list(int);
    iterator_t it_first;
    iterator_t it_second;

    list_init_n(plist, 10);
    it_first = it_second = list_begin(plist);
    expect_assert_failure(iterator_minus(it_first, it_second));
    list_destroy(plist);
}

void test_iterator_minus__slist(void** state)
{
    slist_t* pslist = create_slist(int);
    iterator_t it_first;
    iterator_t it_second;

    slist_init_n(pslist, 10);
    it_first = it_second = slist_begin(pslist);
    expect_assert_failure(iterator_minus(it_first, it_second));
    slist_destroy(pslist);
}

void test_iterator_minus__set(void** state)
{
    set_t* pset = create_set(int);
    iterator_t it_first;
    iterator_t it_second;

    set_init(pset);
    set_insert(pset, 1);
    it_first = it_second = set_begin(pset);
    expect_assert_failure(iterator_minus(it_first, it_second));
    set_destroy(pset);
}

void test_iterator_minus__multiset(void** state)
{
    multiset_t* pset = create_multiset(int);
    iterator_t it_first;
    iterator_t it_second;

    multiset_init(pset);
    multiset_insert(pset, 1);
    it_first = it_second = multiset_begin(pset);
    expect_assert_failure(iterator_minus(it_first, it_second));
    multiset_destroy(pset);
}

void test_iterator_minus__map(void** state)
{
    map_t* pmap = create_map(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    map_init(pmap);
    pair_init(ppair);
    map_insert(pmap, ppair);
    it_first = it_second = map_begin(pmap);
    expect_assert_failure(iterator_minus(it_first, it_second));
    pair_destroy(ppair);
    map_destroy(pmap);
}

void test_iterator_minus__multimap(void** state)
{
    multimap_t* pmap = create_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    multimap_init(pmap);
    pair_init(ppair);
    multimap_insert(pmap, ppair);
    it_first = it_second = multimap_begin(pmap);
    expect_assert_failure(iterator_minus(it_first, it_second));
    pair_destroy(ppair);
    multimap_destroy(pmap);
}

void test_iterator_minus__hash_set(void** state)
{
    hash_set_t* phset = create_hash_set(int);
    iterator_t it_first;
    iterator_t it_second;

    hash_set_init(phset);
    hash_set_insert(phset, 1);
    it_first = it_second = hash_set_begin(phset);
    expect_assert_failure(iterator_minus(it_first, it_second));
    hash_set_destroy(phset);
}

void test_iterator_minus__hash_multiset(void** state)
{
    hash_multiset_t* phset = create_hash_multiset(int);
    iterator_t it_first;
    iterator_t it_second;

    hash_multiset_init(phset);
    hash_multiset_insert(phset, 1);
    it_first = it_second = hash_multiset_begin(phset);
    expect_assert_failure(iterator_minus(it_first, it_second));
    hash_multiset_destroy(phset);
}

void test_iterator_minus__hash_map(void** state)
{
    hash_map_t* pmap = create_hash_map(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    hash_map_init(pmap);
    pair_init(ppair);
    hash_map_insert(pmap, ppair);
    it_first = it_second = hash_map_begin(pmap);
    expect_assert_failure(iterator_minus(it_first, it_second));
    pair_destroy(ppair);
    hash_map_destroy(pmap);
}

void test_iterator_minus__hash_multimap(void** state)
{
    hash_multimap_t* pmap = create_hash_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    hash_multimap_init(pmap);
    pair_init(ppair);
    hash_multimap_insert(pmap, ppair);
    it_first = it_second = hash_multimap_begin(pmap);
    expect_assert_failure(iterator_minus(it_first, it_second));
    pair_destroy(ppair);
    hash_multimap_destroy(pmap);
}

void test_iterator_minus__string_less(void** state)
{
    string_t* pstr = create_string();
    iterator_t it_first;
    iterator_t it_second;

    string_init_cstr(pstr, "abcdefg");
    it_first = string_begin(pstr);
    it_second = string_end(pstr);
    assert_true(iterator_minus(it_first, it_second) == -7);
    string_destroy(pstr);
}

void test_iterator_minus__string_equal(void** state)
{
    string_t* pstr = create_string();
    iterator_t it_first;
    iterator_t it_second;

    string_init_cstr(pstr, "abcdefg");
    it_first = string_begin(pstr);
    it_second = string_begin(pstr);
    assert_true(iterator_minus(it_first, it_second) == 0);
    string_destroy(pstr);
}

void test_iterator_minus__string_greater(void** state)
{
    string_t* pstr = create_string();
    iterator_t it_first;
    iterator_t it_second;

    string_init_cstr(pstr, "abcdefg");
    it_first = string_end(pstr);
    it_second = string_begin(pstr);
    assert_true(iterator_minus(it_first, it_second) == 7);
    string_destroy(pstr);
}

/*
 * test iteator_distance
 */
UT_CASE_DEFINATION(iterator_distance)
void test_iterator_distance__invalid_first(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_first;
    iterator_t it_second;

    vector_init(pvec);
    it_first = it_second = vector_begin(pvec);
    it_first._t_iteratortype = 4444;
    expect_assert_failure(iterator_distance(it_first, it_second));
    vector_destroy(pvec);
}

void test_iterator_distance__invalid_second(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_first;
    iterator_t it_second;

    vector_init(pvec);
    it_first = it_second = vector_begin(pvec);
    it_second._t_iteratortype = 4444;
    expect_assert_failure(iterator_distance(it_first, it_second));
    vector_destroy(pvec);
}

void test_iterator_distance__not_same_container(void** state)
{
    vector_t* pvec0 = create_vector(int);
    vector_t* pvec1 = create_vector(int);

    vector_init(pvec0);
    vector_init(pvec1);
    expect_assert_failure(iterator_distance(vector_begin(pvec0), vector_begin(pvec1)));
    vector_destroy(pvec0);
    vector_destroy(pvec1);
}

void test_iterator_distance__vector_less(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_first;
    iterator_t it_second;

    vector_init_n(pvec, 10);
    it_first = vector_begin(pvec);
    it_second = vector_end(pvec);
    assert_true(iterator_distance(it_first, it_second) == 10);
    vector_destroy(pvec);
}

void test_iterator_distance__vector_equal(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_first;
    iterator_t it_second;

    vector_init_n(pvec, 10);
    it_first = vector_begin(pvec);
    it_second = vector_begin(pvec);
    assert_true(iterator_distance(it_first, it_second) == 0);
    vector_destroy(pvec);
}

void test_iterator_distance__vector_greater(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_first;
    iterator_t it_second;

    vector_init_n(pvec, 10);
    it_first = vector_end(pvec);
    it_second = vector_begin(pvec);
    assert_true(iterator_distance(it_first, it_second) == -10);
    vector_destroy(pvec);
}

void test_iterator_distance__deque_less(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it_first;
    iterator_t it_second;

    deque_init_n(pdeq, 10);
    it_first =  deque_begin(pdeq);
    it_second = deque_end(pdeq);
    assert_true(iterator_distance(it_first, it_second) == 10);
    deque_destroy(pdeq);
}

void test_iterator_distance__deque_equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it_first;
    iterator_t it_second;

    deque_init_n(pdeq, 10);
    it_first =  deque_begin(pdeq);
    it_second = deque_begin(pdeq);
    assert_true(iterator_distance(it_first, it_second) == 0);
    deque_destroy(pdeq);
}

void test_iterator_distance__deque_greater(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it_first;
    iterator_t it_second;

    deque_init_n(pdeq, 10);
    it_first =  deque_end(pdeq);
    it_second = deque_begin(pdeq);
    assert_true(iterator_distance(it_first, it_second) == -10);
    deque_destroy(pdeq);
}

void test_iterator_distance__list_less(void** state)
{
    list_t* plist = create_list(int);
    iterator_t it_first;
    iterator_t it_second;

    list_init_n(plist, 10);
    it_first = list_begin(plist);
    it_second = list_end(plist);
    assert_true(iterator_distance(it_first, it_second) == 10);
    list_destroy(plist);
}

void test_iterator_distance__list_equal(void** state)
{
    list_t* plist = create_list(int);
    iterator_t it_first;
    iterator_t it_second;

    list_init_n(plist, 10);
    it_first = list_begin(plist);
    it_second = list_begin(plist);
    assert_true(iterator_distance(it_first, it_second) == 0);
    list_destroy(plist);
}

void test_iterator_distance__list_greater(void** state)
{
    list_t* plist = create_list(int);
    iterator_t it_first;
    iterator_t it_second;

    list_init_n(plist, 10);
    it_first = list_end(plist);
    it_second = list_begin(plist);
    assert_true(iterator_distance(it_first, it_second) == -10);
    list_destroy(plist);
}

void test_iterator_distance__slist_less(void** state)
{
    slist_t* pslist = create_slist(int);
    iterator_t it_first;
    iterator_t it_second;

    slist_init_n(pslist, 10);
    it_first = slist_begin(pslist);
    it_second = slist_end(pslist);
    assert_true(iterator_distance(it_first, it_second) == 10);
    slist_destroy(pslist);
}

void test_iterator_distance__slist_equal(void** state)
{
    slist_t* pslist = create_slist(int);
    iterator_t it_first;
    iterator_t it_second;

    slist_init_n(pslist, 10);
    it_first = slist_begin(pslist);
    it_second = slist_begin(pslist);
    assert_true(iterator_distance(it_first, it_second) == 0);
    slist_destroy(pslist);
}

void test_iterator_distance__slist_greater(void** state)
{
    slist_t* pslist = create_slist(int);
    iterator_t it_first;
    iterator_t it_second;

    slist_init_n(pslist, 10);
    it_first = slist_end(pslist);
    it_second = slist_begin(pslist);
    assert_true(iterator_distance(it_first, it_second) == -10);
    slist_destroy(pslist);
}

void test_iterator_distance__set_less(void** state)
{
    set_t* pset = create_set(int);
    iterator_t it_first;
    iterator_t it_second;

    set_init(pset);
    set_insert(pset, 1);
    it_first = set_begin(pset); 
    it_second = set_end(pset);
    assert_true(iterator_distance(it_first, it_second) == 1);
    set_destroy(pset);
}

void test_iterator_distance__set_equal(void** state)
{
    set_t* pset = create_set(int);
    iterator_t it_first;
    iterator_t it_second;

    set_init(pset);
    set_insert(pset, 1);
    it_first = set_begin(pset); 
    it_second = set_begin(pset);
    assert_true(iterator_distance(it_first, it_second) == 0);
    set_destroy(pset);
}

void test_iterator_distance__set_greater(void** state)
{
    set_t* pset = create_set(int);
    iterator_t it_first;
    iterator_t it_second;

    set_init(pset);
    set_insert(pset, 1);
    it_first = set_end(pset); 
    it_second = set_begin(pset);
    assert_true(iterator_distance(it_first, it_second) == -1);
    set_destroy(pset);
}

void test_iterator_distance__multiset_less(void** state)
{
    multiset_t* pset = create_multiset(int);
    iterator_t it_first;
    iterator_t it_second;

    multiset_init(pset);
    multiset_insert(pset, 1);
    it_first = multiset_begin(pset);
    it_second = multiset_end(pset);
    assert_true(iterator_distance(it_first, it_second) == 1);
    multiset_destroy(pset);
}

void test_iterator_distance__multiset_equal(void** state)
{
    multiset_t* pset = create_multiset(int);
    iterator_t it_first;
    iterator_t it_second;

    multiset_init(pset);
    multiset_insert(pset, 1);
    it_first = multiset_begin(pset);
    it_second = multiset_begin(pset);
    assert_true(iterator_distance(it_first, it_second) == 0);
    multiset_destroy(pset);
}

void test_iterator_distance__multiset_greater(void** state)
{
    multiset_t* pset = create_multiset(int);
    iterator_t it_first;
    iterator_t it_second;

    multiset_init(pset);
    multiset_insert(pset, 1);
    it_first = multiset_end(pset);
    it_second = multiset_begin(pset);
    assert_true(iterator_distance(it_first, it_second) == -1);
    multiset_destroy(pset);
}

void test_iterator_distance__map_less(void** state)
{
    map_t* pmap = create_map(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    map_init(pmap);
    pair_init(ppair);
    map_insert(pmap, ppair);
    it_first = map_begin(pmap);
    it_second = map_end(pmap);
    assert_true(iterator_distance(it_first, it_second) == 1);
    pair_destroy(ppair);
    map_destroy(pmap);
}

void test_iterator_distance__map_equal(void** state)
{
    map_t* pmap = create_map(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    map_init(pmap);
    pair_init(ppair);
    map_insert(pmap, ppair);
    it_first = map_begin(pmap);
    it_second = map_begin(pmap);
    assert_true(iterator_distance(it_first, it_second) == 0);
    pair_destroy(ppair);
    map_destroy(pmap);
}

void test_iterator_distance__map_greater(void** state)
{
    map_t* pmap = create_map(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    map_init(pmap);
    pair_init(ppair);
    map_insert(pmap, ppair);
    it_first = map_end(pmap);
    it_second = map_begin(pmap);
    assert_true(iterator_distance(it_first, it_second) == -1);
    pair_destroy(ppair);
    map_destroy(pmap);
}

void test_iterator_distance__multimap_less(void** state)
{
    multimap_t* pmap = create_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    multimap_init(pmap);
    pair_init(ppair);
    multimap_insert(pmap, ppair);
    it_first = multimap_begin(pmap);
    it_second = multimap_end(pmap);
    assert_true(iterator_distance(it_first, it_second) == 1);
    pair_destroy(ppair);
    multimap_destroy(pmap);
}

void test_iterator_distance__multimap_equal(void** state)
{
    multimap_t* pmap = create_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    multimap_init(pmap);
    pair_init(ppair);
    multimap_insert(pmap, ppair);
    it_first = multimap_begin(pmap);
    it_second = multimap_begin(pmap);
    assert_true(iterator_distance(it_first, it_second) == 0);
    pair_destroy(ppair);
    multimap_destroy(pmap);
}

void test_iterator_distance__multimap_greater(void** state)
{
    multimap_t* pmap = create_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    multimap_init(pmap);
    pair_init(ppair);
    multimap_insert(pmap, ppair);
    it_first = multimap_end(pmap);
    it_second = multimap_begin(pmap);
    assert_true(iterator_distance(it_first, it_second) == -1);
    pair_destroy(ppair);
    multimap_destroy(pmap);
}

void test_iterator_distance__hash_set_less(void** state)
{
    hash_set_t* phset = create_hash_set(int);
    iterator_t it_first;
    iterator_t it_second;

    hash_set_init(phset);
    hash_set_insert(phset, 1);
    it_first = hash_set_begin(phset);
    it_second = hash_set_end(phset);
    assert_true(iterator_distance(it_first, it_second) == 1);
    hash_set_destroy(phset);
}

void test_iterator_distance__hash_set_equal(void** state)
{
    hash_set_t* phset = create_hash_set(int);
    iterator_t it_first;
    iterator_t it_second;

    hash_set_init(phset);
    hash_set_insert(phset, 1);
    it_first = hash_set_begin(phset);
    it_second = hash_set_begin(phset);
    assert_true(iterator_distance(it_first, it_second) == 0);
    hash_set_destroy(phset);
}

void test_iterator_distance__hash_set_greater(void** state)
{
    hash_set_t* phset = create_hash_set(int);
    iterator_t it_first;
    iterator_t it_second;

    hash_set_init(phset);
    hash_set_insert(phset, 1);
    it_first = hash_set_end(phset);
    it_second = hash_set_begin(phset);
    assert_true(iterator_distance(it_first, it_second) == -1);
    hash_set_destroy(phset);
}

void test_iterator_distance__hash_multiset_less(void** state)
{
    hash_multiset_t* phset = create_hash_multiset(int);
    iterator_t it_first;
    iterator_t it_second;

    hash_multiset_init(phset);
    hash_multiset_insert(phset, 1);
    it_first = hash_multiset_begin(phset);
    it_second = hash_multiset_end(phset);
    assert_true(iterator_distance(it_first, it_second) == 1);
    hash_multiset_destroy(phset);
}

void test_iterator_distance__hash_multiset_equal(void** state)
{
    hash_multiset_t* phset = create_hash_multiset(int);
    iterator_t it_first;
    iterator_t it_second;

    hash_multiset_init(phset);
    hash_multiset_insert(phset, 1);
    it_first = hash_multiset_begin(phset);
    it_second = hash_multiset_begin(phset);
    assert_true(iterator_distance(it_first, it_second) == 0);
    hash_multiset_destroy(phset);
}

void test_iterator_distance__hash_multiset_greater(void** state)
{
    hash_multiset_t* phset = create_hash_multiset(int);
    iterator_t it_first;
    iterator_t it_second;

    hash_multiset_init(phset);
    hash_multiset_insert(phset, 1);
    it_first = hash_multiset_end(phset);
    it_second = hash_multiset_begin(phset);
    assert_true(iterator_distance(it_first, it_second) == -1);
    hash_multiset_destroy(phset);
}

void test_iterator_distance__hash_map_less(void** state)
{
    hash_map_t* pmap = create_hash_map(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    hash_map_init(pmap);
    pair_init(ppair);
    hash_map_insert(pmap, ppair);
    it_first = hash_map_begin(pmap);
    it_second = hash_map_end(pmap);
    assert_true(iterator_distance(it_first, it_second) == 1);
    pair_destroy(ppair);
    hash_map_destroy(pmap);
}

void test_iterator_distance__hash_map_equal(void** state)
{
    hash_map_t* pmap = create_hash_map(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    hash_map_init(pmap);
    pair_init(ppair);
    hash_map_insert(pmap, ppair);
    it_first = hash_map_begin(pmap);
    it_second = hash_map_begin(pmap);
    assert_true(iterator_distance(it_first, it_second) == 0);
    pair_destroy(ppair);
    hash_map_destroy(pmap);
}

void test_iterator_distance__hash_map_greater(void** state)
{
    hash_map_t* pmap = create_hash_map(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    hash_map_init(pmap);
    pair_init(ppair);
    hash_map_insert(pmap, ppair);
    it_first = hash_map_end(pmap);
    it_second = hash_map_begin(pmap);
    assert_true(iterator_distance(it_first, it_second) == -1);
    pair_destroy(ppair);
    hash_map_destroy(pmap);
}

void test_iterator_distance__hash_multimap_less(void** state)
{
    hash_multimap_t* pmap = create_hash_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    hash_multimap_init(pmap);
    pair_init(ppair);
    hash_multimap_insert(pmap, ppair);
    it_first = hash_multimap_begin(pmap);
    it_second = hash_multimap_end(pmap);
    assert_true(iterator_distance(it_first, it_second) == 1);
    pair_destroy(ppair);
    hash_multimap_destroy(pmap);
}

void test_iterator_distance__hash_multimap_equal(void** state)
{
    hash_multimap_t* pmap = create_hash_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    hash_multimap_init(pmap);
    pair_init(ppair);
    hash_multimap_insert(pmap, ppair);
    it_first = hash_multimap_begin(pmap);
    it_second = hash_multimap_begin(pmap);
    assert_true(iterator_distance(it_first, it_second) == 0);
    pair_destroy(ppair);
    hash_multimap_destroy(pmap);
}

void test_iterator_distance__hash_multimap_greater(void** state)
{
    hash_multimap_t* pmap = create_hash_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_first;
    iterator_t it_second;

    hash_multimap_init(pmap);
    pair_init(ppair);
    hash_multimap_insert(pmap, ppair);
    it_first = hash_multimap_end(pmap);
    it_second = hash_multimap_begin(pmap);
    assert_true(iterator_distance(it_first, it_second) == -1);
    pair_destroy(ppair);
    hash_multimap_destroy(pmap);
}

void test_iterator_distance__string_less(void** state)
{
    string_t* pstr = create_string();
    iterator_t it_first;
    iterator_t it_second;

    string_init_cstr(pstr, "abcdefg");
    it_first = string_begin(pstr);
    it_second = string_end(pstr);
    assert_true(iterator_distance(it_first, it_second) == 7);
    string_destroy(pstr);
}

void test_iterator_distance__string_equal(void** state)
{
    string_t* pstr = create_string();
    iterator_t it_first;
    iterator_t it_second;

    string_init_cstr(pstr, "abcdefg");
    it_first = string_begin(pstr);
    it_second = string_begin(pstr);
    assert_true(iterator_distance(it_first, it_second) == 0);
    string_destroy(pstr);
}

void test_iterator_distance__string_greater(void** state)
{
    string_t* pstr = create_string();
    iterator_t it_first;
    iterator_t it_second;

    string_init_cstr(pstr, "abcdefg");
    it_first = string_end(pstr);
    it_second = string_begin(pstr);
    assert_true(iterator_distance(it_first, it_second) == -7);
    string_destroy(pstr);
}

/*
 * test iterator_advance
 */
UT_CASE_DEFINATION(iterator_advance)
void test_iterator_advance__invalid_iter(void** state)
{
    iterator_t it_iter;
    it_iter._t_containertype = 999;
    it_iter._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(iterator_advance(it_iter, 10));
}

void test_iterator_advance__vector_0(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_iter;

    vector_init(pvec);
    vector_push_back(pvec, 1);
    vector_push_back(pvec, 2);
    vector_push_back(pvec, 3);

    it_iter = vector_begin(pvec);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_advance(it_iter, 0);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);

    vector_destroy(pvec);
}

void test_iterator_advance__vector_n(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_iter;
    int i = 0;

    vector_init(pvec);
    for(i = 0; i < 10; ++i)
    {
        vector_push_back(pvec, i);
    }

    it_iter = vector_begin(pvec);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_advance(it_iter, 5);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);

    vector_destroy(pvec);
}

void test_iterator_advance__vector_n_(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_iter;
    int i = 0;

    vector_init(pvec);
    for(i = 0; i < 10; ++i)
    {
        vector_push_back(pvec, i);
    }

    it_iter = iterator_prev(vector_end(pvec));
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);
    it_iter = iterator_advance(it_iter, -5);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);

    vector_destroy(pvec);
}

void test_iterator_advance__vector_end_n(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_iter;
    int i = 0;

    vector_init(pvec);
    for(i = 0; i < 10; ++i)
    {
        vector_push_back(pvec, i);
    }

    it_iter = vector_begin(pvec);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    expect_assert_failure(iterator_advance(it_iter, 15));

    vector_destroy(pvec);
}

void test_iterator_advance__vector_prev_n(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_iter;
    int i = 0;

    vector_init(pvec);
    for(i = 0; i < 10; ++i)
    {
        vector_push_back(pvec, i);
    }

    it_iter = iterator_prev(vector_end(pvec));
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);
    expect_assert_failure(iterator_advance(it_iter, -15));

    vector_destroy(pvec);
}

void test_iterator_advance__deque_0(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it_iter;

    deque_init(pdeq);
    deque_push_back(pdeq, 1);
    deque_push_back(pdeq, 2);

    it_iter = deque_begin(pdeq);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_advance(it_iter, 0);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    deque_destroy(pdeq);
}

void test_iterator_advance__deque_n(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it_iter;
    int i = 0;

    deque_init(pdeq);
    for(i = 0; i < 10; ++i)
    {
        deque_push_back(pdeq, i);
    }

    it_iter = deque_begin(pdeq);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_advance(it_iter, 5);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    deque_destroy(pdeq);
}

void test_iterator_advance__deque_n_(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it_iter;
    int i = 0;

    deque_init(pdeq);
    for(i = 0; i < 10; ++i)
    {
        deque_push_back(pdeq, i);
    }

    it_iter = iterator_prev(deque_end(pdeq));
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);
    it_iter = iterator_advance(it_iter, -5);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    deque_destroy(pdeq);
}

void test_iterator_advance__deque_end_n(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it_iter;
    int i = 0;

    deque_init(pdeq);
    for(i = 0; i < 10; ++i)
    {
        deque_push_back(pdeq, i);
    }

    it_iter = deque_begin(pdeq);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    expect_assert_failure(iterator_advance(it_iter, 15));
    deque_destroy(pdeq);
}

void test_iterator_advance__deque_prev_n(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it_iter;
    int i = 0;

    deque_init(pdeq);
    for(i = 0; i < 10; ++i)
    {
        deque_push_back(pdeq, i);
    }

    it_iter = iterator_prev(deque_end(pdeq));
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);
    expect_assert_failure(iterator_advance(it_iter, -15));
    deque_destroy(pdeq);
}

void test_iterator_advance__list_0(void** state)
{
    list_t* plist = create_list(int);
    iterator_t it_iter;

    list_init(plist);
    list_push_back(plist, 1);
    list_push_back(plist, 2);

    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_advance(it_iter, 0);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);

    list_destroy(plist);
}

void test_iterator_advance__list_n(void** state)
{
    list_t* plist = create_list(int);
    iterator_t it_iter;
    int i = 0;

    list_init(plist);
    for(i = 0; i < 10; ++i)
    {
        list_push_back(plist, i);
    }

    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_advance(it_iter, 5);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);

    list_destroy(plist);
}

void test_iterator_advance__list_n_(void** state)
{
    list_t* plist = create_list(int);
    iterator_t it_iter;
    int i = 0;

    list_init(plist);
    for(i = 0; i < 10; ++i)
    {
        list_push_back(plist, i);
    }

    it_iter = iterator_prev(list_end(plist));
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);
    it_iter = iterator_advance(it_iter, -5);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);

    list_destroy(plist);
}

void test_iterator_advance__list_end_n(void** state)
{
    list_t* plist = create_list(int);
    iterator_t it_iter;
    int i = 0;

    list_init(plist);
    for(i = 0; i < 10; ++i)
    {
        list_push_back(plist, i);
    }

    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    expect_assert_failure(iterator_advance(it_iter, 45));

    list_destroy(plist);
}

void test_iterator_advance__list_prev_n(void** state)
{
    list_t* plist = create_list(int);
    iterator_t it_iter;
    int i = 0;

    list_init(plist);
    for(i = 0; i < 10; ++i)
    {
        list_push_back(plist, i);
    }

    it_iter = iterator_prev(list_end(plist));
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);
    expect_assert_failure(iterator_advance(it_iter, -55));

    list_destroy(plist);
}

void test_iterator_advance__slist_0(void** state)
{
    slist_t* pslist = create_slist(int);
    iterator_t it_iter;

    slist_init(pslist);
    slist_push_front(pslist, 1);
    slist_push_front(pslist, 2);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_advance(it_iter, 0);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    slist_destroy(pslist);
}

void test_iterator_advance__slist_n(void** state)
{
    slist_t* pslist = create_slist(int);
    iterator_t it_iter;
    int i = 0;

    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, i);
    }
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);
    it_iter = iterator_advance(it_iter, 5);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    slist_destroy(pslist);
}

void test_iterator_advance__slist_n_(void** state)
{
    slist_t* pslist = create_slist(int);
    iterator_t it_iter;
    int i = 0;

    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, i);
    }
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);
    it_iter = iterator_advance(it_iter, -5);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    slist_destroy(pslist);
}

void test_iterator_advance__slist_end_n(void** state)
{
    slist_t* pslist = create_slist(int);
    iterator_t it_iter;
    int i = 0;

    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, i);
    }
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);
    expect_assert_failure(iterator_advance(it_iter, 45));
    slist_destroy(pslist);
}

void test_iterator_advance__slist_prev_n(void** state)
{
    slist_t* pslist = create_slist(int);
    iterator_t it_iter;
    int i = 0;

    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, i);
    }
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);
    expect_assert_failure(iterator_advance(it_iter, -45));
    slist_destroy(pslist);
}

void test_iterator_advance__set_0(void** state)
{
    set_t* pset = create_set(int);
    iterator_t it_iter;

    set_init(pset);
    set_insert(pset, 1);
    set_insert(pset, 2);
    it_iter = set_begin(pset);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_advance(it_iter, 0);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    set_destroy(pset);
}

void test_iterator_advance__set_n(void** state)
{
    set_t* pset = create_set(int);
    iterator_t it_iter;
    int i = 0;

    set_init(pset);
    for(i = 0; i < 10; ++i)
    {
        set_insert(pset, i);
    }
    it_iter = set_begin(pset);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_advance(it_iter, 5);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    set_destroy(pset);
}

void test_iterator_advance__set_n_(void** state)
{
    set_t* pset = create_set(int);
    iterator_t it_iter;
    int i = 0;

    set_init(pset);
    for(i = 0; i < 10; ++i)
    {
        set_insert(pset, i);
    }
    it_iter = iterator_prev(set_end(pset));
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);
    it_iter = iterator_advance(it_iter, -5);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    set_destroy(pset);
}

void test_iterator_advance__set_end_n(void** state)
{
    set_t* pset = create_set(int);
    iterator_t it_iter;
    int i = 0;

    set_init(pset);
    for(i = 0; i < 10; ++i)
    {
        set_insert(pset, i);
    }
    it_iter = set_begin(pset);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    expect_assert_failure(iterator_advance(it_iter, 45));
    set_destroy(pset);
}

void test_iterator_advance__set_prev_n(void** state)
{
    set_t* pset = create_set(int);
    iterator_t it_iter;
    int i = 0;

    set_init(pset);
    for(i = 0; i < 10; ++i)
    {
        set_insert(pset, i);
    }
    it_iter = iterator_prev(set_end(pset));
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);
    expect_assert_failure(iterator_advance(it_iter, -35));
    set_destroy(pset);
}

void test_iterator_advance__multiset_0(void** state)
{
    multiset_t* pmset = create_multiset(int);
    iterator_t it_iter;

    multiset_init(pmset);
    multiset_insert(pmset, 1);
    multiset_insert(pmset, 2);
    it_iter = multiset_begin(pmset);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_advance(it_iter, 0);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    multiset_destroy(pmset);
}

void test_iterator_advance__multiset_n(void** state)
{
    multiset_t* pmset = create_multiset(int);
    iterator_t it_iter;
    int i = 0;

    multiset_init(pmset);
    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pmset, i);
    }
    it_iter = multiset_begin(pmset);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_advance(it_iter, 5);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    multiset_destroy(pmset);
}

void test_iterator_advance__multiset_n_(void** state)
{
    multiset_t* pmset = create_multiset(int);
    iterator_t it_iter;
    int i = 0;

    multiset_init(pmset);
    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pmset, i);
    }
    it_iter = iterator_prev(multiset_end(pmset));
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);
    it_iter = iterator_advance(it_iter, -5);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    multiset_destroy(pmset);
}

void test_iterator_advance__multiset_end_n(void** state)
{
    multiset_t* pmset = create_multiset(int);
    iterator_t it_iter;
    int i = 0;

    multiset_init(pmset);
    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pmset, i);
    }
    it_iter = multiset_begin(pmset);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    expect_assert_failure(iterator_advance(it_iter, 45));
    multiset_destroy(pmset);
}

void test_iterator_advance__multiset_prev_n(void** state)
{
    multiset_t* pmset = create_multiset(int);
    iterator_t it_iter;
    int i = 0;

    multiset_init(pmset);
    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pmset, i);
    }
    it_iter = iterator_prev(multiset_end(pmset));
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);
    expect_assert_failure(iterator_advance(it_iter, -45));
    multiset_destroy(pmset);
}

void test_iterator_advance__map_0(void** state)
{
    map_t* pmap = create_map(int, int);
    iterator_t it_iter;

    map_init(pmap);
    *(int*)map_at(pmap, 1) = 10;
    *(int*)map_at(pmap, 2) = 20;
    it_iter = map_begin(pmap);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 1);
    it_iter = iterator_advance(it_iter, 0);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 1);
    map_destroy(pmap);
}

void test_iterator_advance__map_n(void** state)
{
    map_t* pmap = create_map(int, int);
    iterator_t it_iter;
    int i = 0;

    map_init(pmap);
    for(i = 0; i < 10; ++i)
    {
        *(int*)map_at(pmap, i) = i;
    }
    it_iter = map_begin(pmap);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 0);
    it_iter = iterator_advance(it_iter, 5);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 5);
    map_destroy(pmap);
}

void test_iterator_advance__map_n_(void** state)
{
    map_t* pmap = create_map(int, int);
    iterator_t it_iter;
    int i = 0;

    map_init(pmap);
    for(i = 0; i < 10; ++i)
    {
        *(int*)map_at(pmap, i) = i;
    }
    it_iter = iterator_prev(map_end(pmap));
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 9);
    it_iter = iterator_advance(it_iter, -5);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 4);
    map_destroy(pmap);
}

void test_iterator_advance__map_end_n(void** state)
{
    map_t* pmap = create_map(int, int);
    iterator_t it_iter;
    int i = 0;

    map_init(pmap);
    for(i = 0; i < 10; ++i)
    {
        *(int*)map_at(pmap, i) = i;
    }
    it_iter = map_begin(pmap);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 0);
    expect_assert_failure(iterator_advance(it_iter, 55));
    map_destroy(pmap);
}

void test_iterator_advance__map_prev_n(void** state)
{
    map_t* pmap = create_map(int, int);
    iterator_t it_iter;
    int i = 0;

    map_init(pmap);
    for(i = 0; i < 10; ++i)
    {
        *(int*)map_at(pmap, i) = i;
    }
    it_iter = iterator_prev(map_end(pmap));
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 9);
    expect_assert_failure(iterator_advance(it_iter, -45));
    map_destroy(pmap);
}

void test_iterator_advance__multimap_0(void** state)
{
    multimap_t* pmmap = create_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_iter;

    multimap_init(pmmap);
    pair_init(ppair);
    pair_make(ppair, 1, 1);
    multimap_insert(pmmap, ppair);
    pair_make(ppair, 2, 2);
    multimap_insert(pmmap, ppair);
    it_iter = multimap_begin(pmmap);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 1);
    it_iter = iterator_advance(it_iter, 0);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 1);
    pair_destroy(ppair);
    multimap_destroy(pmmap);
}

void test_iterator_advance__multimap_n(void** state)
{
    multimap_t* pmmap = create_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_iter;
    int i = 0;

    multimap_init(pmmap);
    pair_init(ppair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(ppair, i, i);
        multimap_insert(pmmap, ppair);
    }
    it_iter = multimap_begin(pmmap);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 0);
    it_iter = iterator_advance(it_iter, 5);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 5);
    pair_destroy(ppair);
    multimap_destroy(pmmap);
}

void test_iterator_advance__multimap_n_(void** state)
{
    multimap_t* pmmap = create_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_iter;
    int i = 0;

    multimap_init(pmmap);
    pair_init(ppair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(ppair, i, i);
        multimap_insert(pmmap, ppair);
    }
    it_iter = iterator_prev(multimap_end(pmmap));
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 9);
    it_iter = iterator_advance(it_iter, -5);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 4);
    pair_destroy(ppair);
    multimap_destroy(pmmap);
}

void test_iterator_advance__multimap_end_n(void** state)
{
    multimap_t* pmmap = create_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_iter;
    int i = 0;

    multimap_init(pmmap);
    pair_init(ppair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(ppair, i, i);
        multimap_insert(pmmap, ppair);
    }
    it_iter = multimap_begin(pmmap);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 0);
    expect_assert_failure(iterator_advance(it_iter, 45));
    pair_destroy(ppair);
    multimap_destroy(pmmap);
}

void test_iterator_advance__multimap_prev_n(void** state)
{
    multimap_t* pmmap = create_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_iter;
    int i = 0;

    multimap_init(pmmap);
    pair_init(ppair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(ppair, i, i);
        multimap_insert(pmmap, ppair);
    }
    it_iter = iterator_prev(multimap_end(pmmap));
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 9);
    expect_assert_failure(iterator_advance(it_iter, -35));
    pair_destroy(ppair);
    multimap_destroy(pmmap);
}

void test_iterator_advance__hash_set_0(void** state)
{
    hash_set_t* phset = create_hash_set(int);
    iterator_t it_iter;

    hash_set_init(phset);
    hash_set_insert(phset, 1);
    hash_set_insert(phset, 2);
    it_iter = hash_set_begin(phset);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_advance(it_iter, 0);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    hash_set_destroy(phset);
}

void test_iterator_advance__hash_set_n(void** state)
{
    hash_set_t* phset = create_hash_set(int);
    iterator_t it_iter;
    int i = 0;

    hash_set_init(phset);
    for(i = 0; i < 10; ++i)
    {
        hash_set_insert(phset, i);
    }
    it_iter = hash_set_begin(phset);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_advance(it_iter, 5);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    hash_set_destroy(phset);
}

void test_iterator_advance__hash_set_n_(void** state)
{
    hash_set_t* phset = create_hash_set(int);
    iterator_t it_iter;
    int i = 0;

    hash_set_init(phset);
    for(i = 0; i < 10; ++i)
    {
        hash_set_insert(phset, i);
    }
    it_iter = iterator_prev(hash_set_end(phset));
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);
    it_iter = iterator_advance(it_iter, -5);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    hash_set_destroy(phset);
}

void test_iterator_advance__hash_set_end_n(void** state)
{
    hash_set_t* phset = create_hash_set(int);
    iterator_t it_iter;
    int i = 0;

    hash_set_init(phset);
    for(i = 0; i < 10; ++i)
    {
        hash_set_insert(phset, i);
    }
    it_iter = hash_set_begin(phset);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    expect_assert_failure(iterator_advance(it_iter, 35));
    hash_set_destroy(phset);
}

void test_iterator_advance__hash_set_prev_n(void** state)
{
    hash_set_t* phset = create_hash_set(int);
    iterator_t it_iter;
    int i = 0;

    hash_set_init(phset);
    for(i = 0; i < 10; ++i)
    {
        hash_set_insert(phset, i);
    }
    it_iter = iterator_prev(hash_set_end(phset));
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);
    expect_assert_failure(iterator_advance(it_iter, -35));
    hash_set_destroy(phset);
}

void test_iterator_advance__hash_multiset_0(void** state)
{
    hash_multiset_t* phmset = create_hash_multiset(int);
    iterator_t it_iter;

    hash_multiset_init(phmset);
    hash_multiset_insert(phmset, 1);
    hash_multiset_insert(phmset, 2);
    it_iter = hash_multiset_begin(phmset);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_advance(it_iter, 0);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    hash_multiset_destroy(phmset);
}

void test_iterator_advance__hash_multiset_n(void** state)
{
    hash_multiset_t* phmset = create_hash_multiset(int);
    iterator_t it_iter;
    int i = 0;

    hash_multiset_init(phmset);
    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(phmset, i);
    }
    it_iter = hash_multiset_begin(phmset);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_advance(it_iter, 5);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    hash_multiset_destroy(phmset);
}

void test_iterator_advance__hash_multiset_n_(void** state)
{
    hash_multiset_t* phmset = create_hash_multiset(int);
    iterator_t it_iter;
    int i = 0;

    hash_multiset_init(phmset);
    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(phmset, i);
    }
    it_iter = iterator_prev(hash_multiset_end(phmset));
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);
    it_iter = iterator_advance(it_iter, -5);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    hash_multiset_destroy(phmset);
}

void test_iterator_advance__hash_multiset_end_n(void** state)
{
    hash_multiset_t* phmset = create_hash_multiset(int);
    iterator_t it_iter;
    int i = 0;

    hash_multiset_init(phmset);
    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(phmset, i);
    }
    it_iter = hash_multiset_begin(phmset);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    expect_assert_failure(iterator_advance(it_iter, 53));
    hash_multiset_destroy(phmset);
}

void test_iterator_advance__hash_multiset_prev_n(void** state)
{
    hash_multiset_t* phmset = create_hash_multiset(int);
    iterator_t it_iter;
    int i = 0;

    hash_multiset_init(phmset);
    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(phmset, i);
    }
    it_iter = iterator_prev(hash_multiset_end(phmset));
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);
    expect_assert_failure(iterator_advance(it_iter, -53));
    hash_multiset_destroy(phmset);
}

void test_iterator_advance__hash_map_0(void** state)
{
    hash_map_t* phmap = create_hash_map(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_iter;

    hash_map_init(phmap);
    pair_init(ppair);
    pair_make(ppair, 0, 0);
    hash_map_insert(phmap, ppair);
    pair_make(ppair, 1, 1);
    hash_map_insert(phmap, ppair);
    it_iter = hash_map_begin(phmap);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 0);
    it_iter = iterator_advance(it_iter, 0);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 0);
    pair_destroy(ppair);
    hash_map_destroy(phmap);
}

void test_iterator_advance__hash_map_n(void** state)
{
    hash_map_t* phmap = create_hash_map(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_iter;
    int i = 0;

    hash_map_init(phmap);
    pair_init(ppair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(ppair, i, i);
        hash_map_insert(phmap, ppair);
    }
    it_iter = hash_map_begin(phmap);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 0);
    it_iter = iterator_advance(it_iter, 5);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 5);
    pair_destroy(ppair);
    hash_map_destroy(phmap);
}

void test_iterator_advance__hash_map_n_(void** state)
{
    hash_map_t* phmap = create_hash_map(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_iter;
    int i = 0;

    hash_map_init(phmap);
    pair_init(ppair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(ppair, i, i);
        hash_map_insert(phmap, ppair);
    }
    it_iter = iterator_prev(hash_map_end(phmap));
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 9);
    it_iter = iterator_advance(it_iter, -5);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 4);
    pair_destroy(ppair);
    hash_map_destroy(phmap);
}

void test_iterator_advance__hash_map_end_n(void** state)
{
    hash_map_t* phmap = create_hash_map(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_iter;
    int i = 0;

    hash_map_init(phmap);
    pair_init(ppair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(ppair, i, i);
        hash_map_insert(phmap, ppair);
    }
    it_iter = hash_map_begin(phmap);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 0);
    expect_assert_failure(iterator_advance(it_iter, 53));
    pair_destroy(ppair);
    hash_map_destroy(phmap);
}

void test_iterator_advance__hash_map_prev_n(void** state)
{
    hash_map_t* phmap = create_hash_map(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_iter;
    int i = 0;

    hash_map_init(phmap);
    pair_init(ppair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(ppair, i, i);
        hash_map_insert(phmap, ppair);
    }
    it_iter = iterator_prev(hash_map_end(phmap));
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 9);
    expect_assert_failure(iterator_advance(it_iter, -53));
    pair_destroy(ppair);
    hash_map_destroy(phmap);
}

void test_iterator_advance__hash_multimap_0(void** state)
{
    hash_multimap_t* phmap = create_hash_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_iter;

    hash_multimap_init(phmap);
    pair_init(ppair);
    pair_make(ppair, 0, 0);
    hash_multimap_insert(phmap, ppair);
    pair_make(ppair, 1, 1);
    hash_multimap_insert(phmap, ppair);
    it_iter = hash_multimap_begin(phmap);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 0);
    it_iter = iterator_advance(it_iter, 0);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 0);
    pair_destroy(ppair);
    hash_multimap_destroy(phmap);
}

void test_iterator_advance__hash_multimap_n(void** state)
{
    hash_multimap_t* phmap = create_hash_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_iter;
    int i = 0;

    hash_multimap_init(phmap);
    pair_init(ppair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(ppair, i, i);
        hash_multimap_insert(phmap, ppair);
    }
    it_iter = hash_multimap_begin(phmap);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 0);
    it_iter = iterator_advance(it_iter, 5);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 5);
    pair_destroy(ppair);
    hash_multimap_destroy(phmap);
}

void test_iterator_advance__hash_multimap_n_(void** state)
{
    hash_multimap_t* phmap = create_hash_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_iter;
    int i = 0;

    hash_multimap_init(phmap);
    pair_init(ppair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(ppair, i, i);
        hash_multimap_insert(phmap, ppair);
    }
    it_iter = iterator_prev(hash_multimap_end(phmap));
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 9);
    it_iter = iterator_advance(it_iter, -5);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 4);
    pair_destroy(ppair);
    hash_multimap_destroy(phmap);
}

void test_iterator_advance__hash_multimap_end_n(void** state)
{
    hash_multimap_t* phmap = create_hash_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_iter;
    int i = 0;

    hash_multimap_init(phmap);
    pair_init(ppair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(ppair, i, i);
        hash_multimap_insert(phmap, ppair);
    }
    it_iter = hash_multimap_begin(phmap);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 0);
    expect_assert_failure(iterator_advance(it_iter, 35));
    pair_destroy(ppair);
    hash_multimap_destroy(phmap);
}

void test_iterator_advance__hash_multimap_prev_n(void** state)
{
    hash_multimap_t* phmap = create_hash_multimap(int, int);
    pair_t* ppair = create_pair(int, int);
    iterator_t it_iter;
    int i = 0;

    hash_multimap_init(phmap);
    pair_init(ppair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(ppair, i, i);
        hash_multimap_insert(phmap, ppair);
    }
    it_iter = iterator_prev(hash_multimap_end(phmap));
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 9);
    expect_assert_failure(iterator_advance(it_iter, -25));
    pair_destroy(ppair);
    hash_multimap_destroy(phmap);
}

void test_iterator_advance__string_0(void** state)
{
    string_t* pstr = create_string();
    iterator_t it_iter;

    string_init_cstr(pstr, "abcdefg");
    it_iter = string_begin(pstr);
    assert_true(*(char*)iterator_get_pointer(it_iter) == 'a');
    it_iter = iterator_advance(it_iter, 0);
    assert_true(*(char*)iterator_get_pointer(it_iter) == 'a');
    string_destroy(pstr);
}

void test_iterator_advance__string_n(void** state)
{
    string_t* pstr = create_string();
    iterator_t it_iter;

    string_init_cstr(pstr, "abcdefghijklmn");
    it_iter = string_begin(pstr);
    assert_true(*(char*)iterator_get_pointer(it_iter) == 'a');
    it_iter = iterator_advance(it_iter, 5);
    assert_true(*(char*)iterator_get_pointer(it_iter) == 'f');
    string_destroy(pstr);
}

void test_iterator_advance__string_n_(void** state)
{
    string_t* pstr = create_string();
    iterator_t it_iter;

    string_init_cstr(pstr, "abcdefghijklmn");
    it_iter = iterator_prev(string_end(pstr));
    assert_true(*(char*)iterator_get_pointer(it_iter) == 'n');
    it_iter = iterator_advance(it_iter, -5);
    assert_true(*(char*)iterator_get_pointer(it_iter) == 'i');
    string_destroy(pstr);
}

void test_iterator_advance__string_end_n(void** state)
{
    string_t* pstr = create_string();
    iterator_t it_iter;

    string_init_cstr(pstr, "abcdefghijklmn");
    it_iter = string_begin(pstr);
    assert_true(*(char*)iterator_get_pointer(it_iter) == 'a');
    expect_assert_failure(iterator_advance(it_iter, 25));
    string_destroy(pstr);
}

void test_iterator_advance__string_prev_n(void** state)
{
    string_t* pstr = create_string();
    iterator_t it_iter;

    string_init_cstr(pstr, "abcdefghijklmn");
    it_iter = iterator_prev(string_end(pstr));
    assert_true(*(char*)iterator_get_pointer(it_iter) == 'n');
    expect_assert_failure(iterator_advance(it_iter, -35));
    string_destroy(pstr);
}

