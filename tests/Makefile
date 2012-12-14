CC         = clang
CFLAGS     = -std=c99 -Wall -g -fprofile-arcs -ftest-coverage -DUNIT_TEST
INCLUDES   = -I../include
CHECKFLAGS = -Wl,--whole-archive -lcheck -Wl,--no-whole-archive
LDFLAGS	   = -L../bin/.libs -lm -lwolfi -Wl,-rpath=../bin/.libs $(CHECKFLAGS)


# uri_check.c
URI_CHECK        = uri_check
URI_CHECK_SRC    = uri_check.c
URI_CHECK_CFLAGS = $(CFLAGS) $(INCLUDES)
URI_CHECK_LIBS   = $(LDFLAGS)


TESTS = $(URI_CHECK)


all: $(TESTS)
.PHONY: all clean check

# uri_check.c
$(URI_CHECK): $(URI_CHECK_SRC)
	$(CC) $(URI_CHECK_CFLAGS) -o $@ $^ $(URI_CHECK_LIBS)

clean:
	rm -f *.gcno *.gcda
	rm -f $(TESTS)

check:
	@for t in $(TESTS); do \
		./$$t; \
	done
