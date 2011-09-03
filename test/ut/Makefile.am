# for libcstl unit testing.
check_PROGRAMS = ut
ut_SOURCES = ut_main.c ut_def.c ut_def.h \
             $(srcdir)/../../src/cstl_alloc_aux.c $(srcdir)/../../src/cstl_alloc.c \
	     $(srcdir)/../../src/cstl_algo.c \
	     $(srcdir)/../../src/cstl_algobase.c \
	     $(srcdir)/../../src/cstl_function.c \
             $(srcdir)/../../src/cstl_iterator.c \
             $(srcdir)/../../src/cstl_avl_tree.c $(srcdir)/../../src/cstl_avl_tree_iterator.c \
	     $(srcdir)/../../src/cstl_avl_tree_private.c $(srcdir)/../../src/cstl_avl_tree_aux.c \
	     $(srcdir)/../../src/cstl_basic_string.c $(srcdir)/../../src/cstl_basic_string_iterator.c \
	     $(srcdir)/../../src/cstl_basic_string_private.c $(srcdir)/../../src/cstl_basic_string_aux.c \
	     $(srcdir)/../../src/cstl_deque.c $(srcdir)/../../src/cstl_deque_iterator.c \
	     $(srcdir)/../../src/cstl_deque_private.c $(srcdir)/../../src/cstl_deque_aux.c \
	     $(srcdir)/../../src/cstl_hash_map.c \
	     $(srcdir)/../../src/cstl_hash_multimap.c \
	     $(srcdir)/../../src/cstl_hash_multiset.c \
	     $(srcdir)/../../src/cstl_hash_set.c \
	     $(srcdir)/../../src/cstl_hashtable.c $(srcdir)/../../src/cstl_hashtable_iterator.c \
	     $(srcdir)/../../src/cstl_hashtable_private.c $(srcdir)/../../src/cstl_hashtable_aux.c \
	     $(srcdir)/../../src/cstl_heap.c \
	     $(srcdir)/../../src/cstl_list.c $(srcdir)/../../src/cstl_list_iterator.c \
	     $(srcdir)/../../src/cstl_list_private.c $(srcdir)/../../src/cstl_list_aux.c \
	     $(srcdir)/../../src/cstl_map.c $(srcdir)/../../src/cstl_map_iterator.c \
	     $(srcdir)/../../src/cstl_map_private.c $(srcdir)/../../src/cstl_map_aux.c \
	     $(srcdir)/../../src/cstl_multimap.c $(srcdir)/../../src/cstl_multimap_iterator.c \
	     $(srcdir)/../../src/cstl_multimap_private.c $(srcdir)/../../src/cstl_multimap_aux.c \
	     $(srcdir)/../../src/cstl_multiset.c $(srcdir)/../../src/cstl_multiset_iterator.c \
	     $(srcdir)/../../src/cstl_multiset_private.c $(srcdir)/../../src/cstl_multiset_aux.c \
	     $(srcdir)/../../src/cstl_numeric.c \
	     $(srcdir)/../../src/cstl_rb_tree.c $(srcdir)/../../src/cstl_rb_tree_iterator.c \
	     $(srcdir)/../../src/cstl_rb_tree_private.c $(srcdir)/../../src/cstl_rb_tree_aux.c \
	     $(srcdir)/../../src/cstl_set.c $(srcdir)/../../src/cstl_set_iterator.c \
	     $(srcdir)/../../src/cstl_set_private.c $(srcdir)/../../src/cstl_set_aux.c \
	     $(srcdir)/../../src/cstl_slist.c $(srcdir)/../../src/cstl_slist_iterator.c \
	     $(srcdir)/../../src/cstl_slist_private.c $(srcdir)/../../src/cstl_slist_aux.c \
	     $(srcdir)/../../src/cstl_priority_queue.c $(srcdir)/../../src/cstl_priority_queue_private.c \
	     $(srcdir)/../../src/cstl_queue.c $(srcdir)/../../src/cstl_queue_private.c \
	     $(srcdir)/../../src/cstl_string.c $(srcdir)/../../src/cstl_string_private.c \
	     $(srcdir)/../../src/cstl_types.c \
	     $(srcdir)/../../src/cstl_pair.c $(srcdir)/../../src/cstl_pair_private.c $(srcdir)/../../src/cstl_pair_aux.c \
	     $(srcdir)/../../src/cstl_stack.c $(srcdir)/../../src/cstl_stack_private.c \
             $(srcdir)/../../src/cstl_vector.c $(srcdir)/../../src/cstl_vector_iterator.c \
	     $(srcdir)/../../src/cstl_vector_private.c $(srcdir)/../../src/cstl_vector_aux.c \
             ut_cstl_alloc_aux.c ut_cstl_alloc_aux.h \
             ut_cstl_alloc.c ut_cstl_alloc.h \
             ut_cstl_vector_iterator.c ut_cstl_vector_iterator.h \
	     ut_cstl_vector_aux.c ut_cstl_vector_aux.h \
	     ut_cstl_vector_private.c ut_cstl_vector_private.h \
	     ut_cstl_vector.c ut_cstl_vector.h \
	     ut_cstl_list_iterator.c ut_cstl_list_iterator.h \
	     ut_cstl_list_aux.c ut_cstl_list_aux.h \
	     ut_cstl_list_private.c ut_cstl_list_private.h \
	     ut_cstl_list.c ut_cstl_list.h \
	     ut_cstl_deque_iterator.c ut_cstl_deque_iterator.h \
	     ut_cstl_deque_aux.c ut_cstl_deque_aux.h \
	     ut_cstl_deque_private.c ut_cstl_deque_private.h \
	     ut_cstl_deque.c ut_cstl_deque.h \
	     ut_cstl_slist_iterator.c ut_cstl_slist_iterator.h \
	     ut_cstl_slist_aux.c ut_cstl_slist_aux.h \
	     ut_cstl_slist_private.c ut_cstl_slist_private.h \
	     ut_cstl_slist.c ut_cstl_slist.h \
	     ut_cstl_stack_private.c ut_cstl_stack_private.h \
	     ut_cstl_stack.c ut_cstl_stack.h \
	     ut_cstl_queue_private.c ut_cstl_queue_private.h \
	     ut_cstl_queue.c ut_cstl_queue.h \
	     ut_cstl_basic_string_iterator.c ut_cstl_basic_string_iterator.h \
	     ut_cstl_basic_string_aux.c ut_cstl_basic_string_aux.h \
	     ut_cstl_basic_string_private.c ut_cstl_basic_string_private.h \
	     ut_cstl_basic_string.c ut_cstl_basic_string.h \
	     ut_cstl_string_private.c ut_cstl_string_private.h \
	     ut_cstl_string.c ut_cstl_string.h \
	     ut_cstl_avl_tree_aux.c ut_cstl_avl_tree_aux.h \
	     ut_cstl_avl_tree_private.c ut_cstl_avl_tree_private.h \
	     ut_cstl_avl_tree_iterator.c ut_cstl_avl_tree_iterator.h \
	     ut_cstl_avl_tree.c ut_cstl_avl_tree.h \
	     ut_cstl_rb_tree_aux.c ut_cstl_rb_tree_aux.h \
	     ut_cstl_rb_tree_private.c ut_cstl_rb_tree_private.h \
	     ut_cstl_rb_tree_iterator.c ut_cstl_rb_tree_iterator.h \
	     ut_cstl_rb_tree.c ut_cstl_rb_tree.h \
	     ut_cstl_set_aux.c ut_cstl_set_aux.h \
	     ut_cstl_set_private.c ut_cstl_set_private.h \
	     ut_cstl_set_iterator.c ut_cstl_set_iterator.h \
	     ut_cstl_set.c ut_cstl_set.h \
	     ut_cstl_multiset_aux.c ut_cstl_multiset_aux.h \
	     ut_cstl_multiset_private.c ut_cstl_multiset_private.h \
	     ut_cstl_multiset_iterator.c ut_cstl_multiset_iterator.h \
	     ut_cstl_multiset.c ut_cstl_multiset.h \
	     ut_cstl_pair_aux.c ut_cstl_pair_aux.h \
	     ut_cstl_pair_private.c ut_cstl_pair_private.h \
	     ut_cstl_pair.c ut_cstl_pair.h \
	     ut_cstl_map_aux.c ut_cstl_map_aux.h \
	     ut_cstl_map_private.c ut_cstl_map_private.h \
	     ut_cstl_map_iterator.c ut_cstl_map_iterator.h \
	     ut_cstl_map.c ut_cstl_map.h \
	     ut_cstl_multimap_aux.c ut_cstl_multimap_aux.h \
	     ut_cstl_multimap_private.c ut_cstl_multimap_private.h \
	     ut_cstl_multimap_iterator.c ut_cstl_multimap_iterator.h \
	     ut_cstl_multimap.c ut_cstl_multimap.h \
	     ut_cstl_hashtable_aux.c ut_cstl_hashtable_aux.h \
	     ut_cstl_hashtable_private.c ut_cstl_hashtable_private.h \
	     ut_cstl_hashtable_iterator.c ut_cstl_hashtable_iterator.h
ut_CPPFLAGS = -D_CSTL_UNIT_TESTING -I$(srcdir)/../.. -I$(srcdir)/../../src
ut_LDFLAGS = -lcmockery
TESTS = $(check_PROGRAMS)
CLEANFILES = core.* *.utoutput

