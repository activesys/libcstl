#
#   The project compilation file.
#   Copyright (C)  2008,2009,2010  Wangbo
#
#   This library is free software; you can redistribute it and/or
#   modify it under the terms of the GNU Lesser General Public
#   License as published by the Free Software Foundation; either
#   version 2.1 of the License, or (at your option) any later version.
#
#   This library is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#   Lesser General Public License for more details.
#
#   You should have received a copy of the GNU Lesser General Public
#   License along with this library; if not, write to the Free Software
#   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
#
#   Author e-mail: activesys.wb@gmail.com
#                  activesys@sina.com.cn
#

# set compiler and options
CC = gcc
CFLAGS = -c -g -ansi -Wall -Wextra -fPIC#-DNDEBUG
CPPFLAGS = -I include
LINKSOFLAGS = -shared -Wl,-soname,libcstl.so.2

ARFLAGS = ruv

# set file manipulation tools
RM = rm -rf
SED = sed
INSTALL = install
MKDIR = mkdir
LN = ln -s
MAKE = make

# set compilation directory
vpath %.c src test
vpath %.h include test

SRCS = $(notdir $(wildcard src/*.c))
OBJS = $(subst .c,.o,$(SRCS))
TESTSRC = $(notdir $(wildcard test/*.c))
TESTOBJ = $(subst .c,.o,$(TESTSRC))

BINDIR = bin
SRCDIR = src
INCDIR = include
TESTDIR = test
LIBDIR = /usr/lib/
LIBINCDIR = /usr/include/cstl/

# set compilation targets
LIBCSTL = libcstl
TARGETVER = 2.0.0
LINKTARGET = libcstl.so
SONAME = libcstl.so.2
ARTARGET = $(BINDIR)/libcstl.a
SOTARGET = $(BINDIR)/libcstl.so.$(TARGETVER)
TESTTARGET = $(BINDIR)/test
HEADERTARGET = $(INCDIR)/*.h

# compile rule
.PHONY: all
all : $(ARTARGET) $(SOTARGET) $(TESTTARGET)

$(ARTARGET): $(addprefix $(BINDIR)/,$(OBJS))
	$(AR) $(ARFLAGS) $@ $^

$(SOTARGET): $(addprefix $(BINDIR)/,$(OBJS))
	$(CC) $^ $(LINKSOFLAGS) -o $@

$(TESTTARGET): $(addprefix $(BINDIR)/,$(TESTOBJ))
	$(CC) $^ $(ARTARGET) -o $@

# include depend file
ifneq ($(MAKECMDGOALS),clean)
    -include $(addprefix $(BINDIR)/,$(subst .c,.d,$(SRCS)))
    -include $(addprefix $(BINDIR)/,$(subst .c,.d,$(TESTSRC)))
endif

# user defined rule
$(BINDIR)/%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -o $@

$(BINDIR)/%.d: %.c
	$(CC) -MM $(CPPFLAGS) $< > $@.$$$$;\
	$(SED) 's,\($*\).o[ :]*,$(BINDIR)/\1.o $@: ,g' < $@.$$$$ > $@;\
	$(RM) $@.$$$$

# phony target
.PHONY: install
install:
	$(INSTALL) $(ARTARGET) $(LIBDIR)
	$(INSTALL) $(SOTARGET) $(LIBDIR)
	$(LN) $(LIBDIR)$(LINKTARGET).$(TARGETVER) $(LIBDIR)$(SONAME)
	$(LN) $(LIBDIR)$(LINKTARGET).$(TARGETVER) $(LIBDIR)$(LINKTARGET)
	$(MKDIR) $(LIBINCDIR)
	$(INSTALL) $(HEADERTARGET) $(LIBINCDIR)

.PHONY: uninstall
uninstall:
	$(RM) $(LIBDIR)$(LIBCSTL).*
	$(RM) $(LIBINCDIR)

.PHONY: update
update:
	$(MAKE) uninstall
	$(MAKE) install

.PHONY: clean
clean:
	$(RM) $(ARTARGET) 
	$(RM) $(SOTARGET)
	$(RM) $(TESTTARGET)
	$(RM) $(addprefix $(BINDIR)/,$(OBJS)) 
	$(RM) $(addprefix $(BINDIR)/,$(subst .o,.d,$(OBJS))) 
	$(RM) $(addprefix $(BINDIR)/,$(TESTOBJ))
	$(RM) $(addprefix $(BINDIR)/,$(subst .o,.d,$(TESTOBJ)))
	$(RM) core.* $(BINDIR)/core.* $(BINDIR)/*

.PHONY: remake
remake:
	make clean
	make

