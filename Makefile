SRCDIR       = src
OBJDIR       = obj
BINDIR       = bin

EXE				   = $(BINDIR)/wolfi
LIB				 	= $(BINDIR)/libwolfi.la 

CC           = gcc
CFLAGS       = -std=c99 -Wall -g
INCLUDES     = -I./include
LIBS		     = -lm
LDFLAGS      = -shared
LIBTOOL		   = libtool

RAGEL        = ragel
RAGEL_DIR    = ragel
RAGEL_SRCS   = $(wildcard $(RAGEL_DIR)/*_c.rl)
_RAGEL_SRCS  = $(notdir $(RAGEL_SRCS))
_RAGEL_FSMS  = $(_RAGEL_SRCS:.rl=.c)
RAGEL_FSMS   = $(addprefix $(SRCDIR)/,$(_RAGEL_FSMS))

SRCS         = $(RAGEL_FSMS) $(wildcard $(SRCDIR)/*.c)
_SRCS	  		 = $(notdir $(SRCS))
_OBJS        = $(_SRCS:.c=.lo)
OBJS  			 = $(addprefix $(OBJDIR)/, $(_OBJS))

MAIN_SRC     = main.c
_MAIN_OBJ    = $(MAIN_SRC:.c=.o)
MAIN_OBJ     = $(addprefix $(OBJDIR)/, $(_MAIN_OBJ))


all: $(lib) $(EXE)

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
	$(LIBTOOL) --mode=link -shared \
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(OBJDIR)/%.lo: $(SRCDIR)/%.c
	$(LIBTOOL) --mode=compile \
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(SRCDIR)/%_c.c: $(RAGEL_DIR)/%_c.rl
	$(RAGEL) -I$(RAGEL_DIR) -o $@ $<

clean:
	rm -rf $(OBJDIR)/.libs $(BINDIR)/.libs
	rm -f $(OBJDIR)/main.* $(OBJS) $(RAGEL_FSMS) $(LIB) $(EXE) || true
	test -d $(OBJDIR) && rmdir $(OBJDIR) || true
	test -d $(BINDIR) && rmdir $(BINDIR) || true
	cd tests && make clean

check:
	cd tests && make && make check
