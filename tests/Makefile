CC         = clang
CFLAGS     = -std=c99 -Wall -g -fprofile-arcs -ftest-coverage -DUNIT_TEST
INCLUDES   = -I../include
CHECKFLAGS = -Wl,--whole-archive -lcheck -Wl,--no-whole-archive
LDFLAGS	   = -L../bin/.libs -lm -lwolfi -Wl,-rpath=../bin/.libs $(CHECKFLAGS)


# rfc3986_check.c
RFC3986_CHECK        = rfc3986_check
RFC3986_CHECK_SRC    = rfc3986_check.c
RFC3986_CHECK_CFLAGS = $(CFLAGS) $(INCLUDES)
RFC3986_CHECK_LIBS   = $(LDFLAGS)


TESTS = $(RFC3986_CHECK)


all: $(TESTS)
.PHONY: all clean check

# rfc3986_check.c
$(RFC3986_CHECK): $(RFC3986_CHECK_SRC)
	$(CC) $(RFC3986_CHECK_CFLAGS) -o $@ $^ $(RFC3986_CHECK_LIBS)

clean:
	rm -f *.gcno *.gcda
	rm -f $(TESTS)

check:
	@for t in $(TESTS); do \
		./$$t; \
	done
