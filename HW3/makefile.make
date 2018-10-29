CXX = g++
CCFLAGS = -g -std=c++14

# this is a "Suffix Rule" - how to create a .o from a .cc file
.cpp.o:
    $(CXX) $(CCFLAGS) -c $<

cache: cache.o
    $(CXX) -o cache cache.o

test1: test1.o.o
    $(CXX) -o cache cache.o

test2: test2.o
    $(CXX) -o cache cache.o

test3: test3.o
    $(CXX) -o cache cache.o

test4: test4.o
    $(CXX) -o cache cache.o

test5: test5.o
    $(CXX) -o cache cache.o

test6: test6.o
    $(CXX) -o cache cache.o

clean:
    rm -f *.o
    rm -f *-stats.wc
