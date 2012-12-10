SRCDIR      = src
OBJDIR      = obj
BINDIR      = bin

TARGET      = $(BINDIR)/wolfi

CC          = gcc
CFLAGS      = -std=c99 -Wall -g
INCLUDES    =-I./include
LIBS		   	=

RAGEL       = ragel
RAGEL_DIR   = ragel
RAGEL_SRCS  = $(wildcard $(RAGEL_DIR)/*_c.rl)
_RAGEL_SRCS = $(notdir $(RAGEL_SRCS))
_RAGEL_FSMS = $(_RAGEL_SRCS:.rl=.c)
RAGEL_FSMS  = $(addprefix $(OBJDIR)/,$(_RAGEL_FSMS))


SRCS        = $(wildcard $(SRCDIR)/*.c)
_SRCS	  		= $(notdir $(SRCS))
_OBJS       = $(_SRCS:.c=.o)
OBJS  			= $(addprefix $(OBJDIR)/, $(_OBJS))


all: $(BINDIR) $(OBJDIR) $(TARGET)

$(BINDIR):
	mkdir -p $(BINDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(TARGET): $(RAGEL_FSMS) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS)

$(OBJDIR)/%_c.c: $(RAGEL_DIR)/%_c.rl
	$(RAGEL) -I ./ragel  -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

clean:
	rm -f $(OBJS) $(RAGEL_FSMS) $(TARGET) || true
	test -d $(OBJDIR) && rmdir $(OBJDIR) || true
	test -d $(BINDIR) && rmdir $(BINDIR) || true
