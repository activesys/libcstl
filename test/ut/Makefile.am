# for libcstl unit testing.
check_PROGRAMS = ut
ut_SOURCES = ut_main.c \
	     $(srcdir)/../../src/cstl_alloc_aux.c $(srcdir)/../../src/cstl_alloc.c \
	     ut_cstl_alloc_aux.c ut_cstl_alloc_aux.h \
	     ut_cstl_alloc.c ut_cstl_alloc.h
ut_CPPFLAGS = -D_CSTL_UNIT_TESTING -I$(srcdir)/../.. -I$(srcdir)/../../src -D_CSTL_USER_MODEL
ut_LDFLAGS = -lcmockery
TESTS = $(check_PROGRAMS)
CLEANFILES = core.*
