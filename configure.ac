#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_INIT([libcstl],[2.3.0],[activesys.wb@gmail.com])
AC_COPYRIGHT([Copyright (C) 2008 - 2014 Wangbo.])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
#LT_INIT
AC_CONFIG_SRCDIR([src/cstl_vector.c])
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CC
AC_PROG_RANLIB
LT_INIT

# Checks for libraries.

# Checks for header files.
AC_HEADER_ASSERT

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T
AC_PROG_CC_C99
AC_C_CONST

# Checks for library functions.
AC_FUNC_MALLOC

# Checks for user options
# CSTL_MEMORY_MANAGEMENT     : use memory management.
AC_ARG_WITH(
    [memory-management],
    [AS_HELP_STRING([--with-memory-management],[use libcstl memory management(default is no).])],
    [AC_DEFINE([CSTL_MEMORY_MANAGEMENT], [1], [Define to 1 if you use libcstl memory management.])]#,
#    []
)
# CSTL_STACK_VECTOR_SEQUENCE : implement stack using vector.
# CSTL_STACK_LIST_SEQUENCE   : implement stack using list.
AC_ARG_ENABLE(
    [stack-implementation],
    [AS_HELP_STRING([--enable-stack-implementation[=ARGUMENT]],[select stack implementation(the ARGUMENTs are vector and list, deque is the default).])],
    [case "$enableval" in 
     vector)
	AC_DEFINE([CSTL_STACK_VECTOR_SEQUENCE], [1], [Define to 1 if you implement stack using vector.])
	;;
     list)
	AC_DEFINE([CSTL_STACK_LIST_SEQUENCE], [1], [Define to 1 if you implement stack using list.])
	;;
     esac]
)
# CSTL_QUEUE_LIST_SEQUENCE   : implement queue using list.
AC_ARG_ENABLE(
    [queue-implementation],
    [AS_HELP_STRING([--enable-queue-implementation[=ARGUMENT]],[select queue implementation(the ARGUMENT is list, deque is the default).])],
    [case "$enableval" in 
     list)
	AC_DEFINE([CSTL_QUEUE_LIST_SEQUENCE], [1], [Define to 1 if you implement queue using list.])
	;;
     esac]
)
# CSTL_SET_AVL_TREE          : implement set using avl-tree.
AC_ARG_ENABLE(
    [set-implementation],
    [AS_HELP_STRING([--enable-set-implementation[=ARGUMENT]],[select set implementation(the ARGUMENT is avl-tree, rb-tree is the default).])],
    [case "$enableval" in 
     avl-tree)
	AC_DEFINE([CSTL_SET_AVL_TREE], [1], [Define to 1 if you implement set using avl-tree.])
	;;
     esac]
)
# CSTL_MULTISET_AVL_TREE     : implement multiset using avl-tree.
AC_ARG_ENABLE(
    [multiset-implementation],
    [AS_HELP_STRING([--enable-multiset-implementation[=ARGUMENT]],[select multiset implementation(the ARGUMENT is avl-tree, rb-tree is the default).])],
    [case "$enableval" in 
     avl-tree)
	AC_DEFINE([CSTL_MULTISET_AVL_TREE], [1], [Define to 1 if you implement multiset using avl-tree.])
	;;
     esac]
)
# CSTL_MAP_AVL_TREE          : implement map using avl-tree.
AC_ARG_ENABLE(
    [map-implementation],
    [AS_HELP_STRING([--enable-map-implementation[=ARGUMENT]],[select map implementation(the ARGUMENT is avl-tree, rb-tree is the default).])],
    [case "$enableval" in 
     avl-tree)
	AC_DEFINE([CSTL_MAP_AVL_TREE], [1], [Define to 1 if you implement map using avl-tree.])
	;;
     esac]
)
# CSTL_MULTIMAP_AVL_TREE     : implement multimap using avl-tree.
AC_ARG_ENABLE(
    [multimap-implementation],
    [AS_HELP_STRING([--enable-multimap-implementation[=ARGUMENT]],[select multimap implementation(the ARGUMENT is avl-tree, rb-tree is the default).])],
    [case "$enableval" in 
     avl-tree)
	AC_DEFINE([CSTL_MULTIMAP_AVL_TREE], [1], [Define to 1 if you implement multimap using avl-tree.])
	;;
     esac]
)

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
    Makefile
    cstl/Makefile
    src/Makefile
    build-win/Makefile
    build-win/vc8/Makefile
    build-win/vc9/Makefile
    test/Makefile
    test/ut/Makefile
])
AC_OUTPUT
