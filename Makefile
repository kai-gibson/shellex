CXXFLAGS = -O3 -g3 -pthread -gdwarf-4 -DLinux -fPIC -Wno-deprecated -pipe -fno-elide-type -fdiagnostics-show-template-tree -Wall -Werror -Wextra -Wpedantic -Wvla -Wextra-semi -Wnull-dereference -Wswitch-enum -fvar-tracking-assignments -Wduplicated-cond -Wduplicated-branches -rdynamic -Wsuggest-override -MMD -MP

lib/libshellex.a: bin/shellex.o
	mkdir lib
	ar rvs lib/libshellex.a bin/shellex.o

bin/shellex.o: shellex.cxx shellex.h
	mkdir bin
	${CXX} ${CXXFLAGS} shellex.cxx -c -o bin/shellex.o

install: bin/shellex.o lib/libshellex.a
	mkdir -p /usr/local/include/shx
	install -m 557 lib/libshellex.a /usr/local/lib
	install -m 557 ./shellex.h /usr/local/include/shx

# I want to copy 
