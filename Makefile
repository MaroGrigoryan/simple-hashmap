# -*- makefile -*-
main := main.cpp
program := main
flags := -std=c++14 -g -Wall -Wextra -I./
lib_name := libmain.a
# Just add another file here when you're done, ending in .o
objs := main.o
os := $(shell uname -s)

ifeq ($(os),Darwin)
  maybe_static_phrase :=
else
  maybe_static_phrase := -static
endif

# We statically link to avoid shared library hassles.
program:library
	clang++ ${maybe_static_pharse} ${main} -L. \
	-lmain ${flags} -o ${program}

%.o:%.cpp
	clang++ -c ${flags} $<

# Need to have a dependency on things that end with .o to have the
# wildcard pattern go off.
library:${objs}; ar rcs ${lib_name} ${objs}

clean:; @rm -rf ${program} *.dSYM *.o ${lib_name} *.so *.a
