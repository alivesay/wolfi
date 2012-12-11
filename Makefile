
VERSION      = 0.0.0

PREFIX       = /usr/local

SRCDIR       = src
OBJDIR       = obj
BINDIR       = bin

EXE_NAME     = wolfi
LIB_NAME     = libwolfi.la
EXE          = $(BINDIR)/$(EXE_NAME)
LIB          = $(BINDIR)/$(LIB_NAME)

CC           = clang
CFLAGS       = -std=c99 -Wall -g
INCLUDES     = -I./include
LIBS         = -lm
LDFLAGS      = -shared

LIBTOOL      = libtool --tag=CC --quiet

RAGEL        = ragel
RAGEL_DIR    = ragel
RAGEL_SRCS   = $(wildcard $(RAGEL_DIR)/*_c.rl)
_RAGEL_SRCS  = $(notdir $(RAGEL_SRCS))
_RAGEL_FSMS  = $(_RAGEL_SRCS:.rl=.c)
RAGEL_FSMS   = $(addprefix $(SRCDIR)/, $(_RAGEL_FSMS))

SRCS         = $(RAGEL_FSMS) $(wildcard $(SRCDIR)/*.c)
_SRCS        = $(notdir $(SRCS))
_OBJS        = $(_SRCS:.c=.lo)
OBJS         = $(addprefix $(OBJDIR)/, $(_OBJS))

MAIN_SRC     = main.c
_MAIN_OBJ    = $(MAIN_SRC:.c=.lo)
MAIN_OBJ     = $(addprefix $(OBJDIR)/, $(_MAIN_OBJ))


all: lib $(EXE)

lib: $(BINDIR) $(OBJDIR) $(RAGEL_FSMS) $(LIB)

$(BINDIR):
	mkdir -p $(BINDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(EXE): $(MAIN_OBJ) $(LIB)
	$(LIBTOOL) --mode=link \
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS) 

$(MAIN_OBJ): $(MAIN_SRC)
	$(LIBTOOL) --mode=compile \
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(LIB): $(OBJS)
	$(LIBTOOL) --mode=link \
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS) \
	-rpath $(PREFIX)/lib

$(OBJDIR)/%.lo: $(SRCDIR)/%.c
	$(LIBTOOL) --mode=compile \
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(SRCDIR)/%_c.c: $(RAGEL_DIR)/%_c.rl
	$(RAGEL) -I$(RAGEL_DIR) -o $@ $<

install-exe: $(EXE)
	install -c $(EXE) $(PREFIX)/bin/$(EXE_NAME)

install-lib: $(LIB)
	LIB_BASENAME = $(basename $(LIB_NAME))
	$(LIBTOOL) --mode=install install -c $(LIB) $(PREFIX)/lib/$(LIB_NAME)
	install -c $(BINDIR)/.libs/$(LIB_BASENAME).so.$(VERSION) $(PREFIX)/lib/$(LIB_BASENAME).so.$(VERSION)
	install -c $(BINDIR)/$(LIB_NAME) $(PREFIX)/lib/$(LIB_NAME)
	install -c $(BINDIR)/.libs/$(LIB_BASENAME).a $(PREFIX)/lib/$(LIB_BASENAME).a
	ranlib $(PREFIX)/lib/$(LIB_BASENAME).a
	install --mode=finish

clean:
	rm -rf $(BINDIR)/.libs $(OBJDIR)/.libs
	rm -f $(MAIN_OBJ) $(MAIN_OBJ:.lo=.o) $(OBJS) $(OBJS:.lo=.o) $(RAGEL_FSMS) $(LIB) $(EXE) || true
	test -d $(OBJDIR) && rmdir $(OBJDIR) || true
	test -d $(BINDIR) && rmdir $(BINDIR) || true
	cd tests && make clean

check: lib
	cd tests && make && make check
