CC=g++ -g -Wall -fno-builtin -std=c++17

UNAME := $(shell uname -s)
ifeq ($(UNAME),Darwin)
    CC+=-D_XOPEN_SOURCE
    LIBVMAPP=libvm_app_macos.o
    LIBVMPAGER=libvm_pager_macos.o
else
    LIBVMAPP=libvm_app.o
    LIBVMPAGER=libvm_pager.o
endif

# List of source files for your pager
PAGER_SOURCES=vm_pager.cpp

# Generate the names of the pager's object files
PAGER_OBJS=${PAGER_SOURCES:.cpp=.o}

all: pager test1 test2 test3 test4 test5 test6 testlab1 testbig

# Compile the pager and tag this compilation
pager: ${PAGER_OBJS} ${LIBVMPAGER}
	./autotag.sh push
	${CC} -o $@ $^

# Compile an application program
test1: test1.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl

test2: test2.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl

test3: test3.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl

test4: test4.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl

test5: test5.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl

test6: test6.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl

testlab1: testlab1.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl

testbig: testbig.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl

testbigfork: testbigfork.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl

testbad1: testbad1.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl

testbad2: testbad2.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl

testbad3: testbad3.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl

testbad4: testbad4.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl

testbad5: testbad5.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl

testbad6: testbad6.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl

testdestroy: testdestroy.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl

testdestroy2: testdestroy2.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl

testfile: testfile.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl

testextra: testextra.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl

testvpnlist: testvpnlist.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl

testfork: testfork.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl

testfork2: testfork2.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl

testforkmore: testforkmore.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl

# Generic rules for compiling a source file to an object file
%.o: %.cpp
	${CC} -c $<
%.o: %.cc
	${CC} -c $<

clean:
	rm -f ${PAGER_OBJS} pager test1 test2 test3 test4 testbig
