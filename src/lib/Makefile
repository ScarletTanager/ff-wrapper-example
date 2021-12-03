CC=/usr/bin/gcc
CFLAGS=-Wall -O2 -g -c -fPIC
CFLAGS_SHARED=-shared
RM=/bin/rm
SRC_FILES=proto.c
OBJECT_FILES=*.o
LIB_FILES=*.so
LD_DIRS=-L . -L /usr/local/homebrew/lib
LD_LIBS=-lproto -lcgreen
OBJS_TEST=all_tests.o proto_test.o
INCLUDE_PATHS=/usr/local/homebrew/include
CFLAGS_TEST=$(CFLAGS) -I $(INCLUDE_PATHS)
LD_FLAGS_TEST=$(LD_DIRS) $(LD_LIBS)


.PHONY: all
all: libproto.so

.PHONY: clean
clean:
	$(RM) $(OBJECT_FILES) $(LIB_FILES)

proto.o: proto.c proto.h
	$(CC) $(CFLAGS) proto.c -o proto.o

libproto.so: proto.o
	$(CC) proto.o $(CFLAGS_SHARED) -o libproto.so

# Tests

all_tests.o: all_tests.c
	$(CC) $(CFLAGS_TEST) all_tests.c

proto_test.o: proto_test.c
	$(CC) $(CFLAGS_TEST) proto_test.c

all_tests: all_tests.o proto_test.o libproto.so
	$(CC) $(OBJS_TEST) $(LD_FLAGS_TEST) -o all_tests
