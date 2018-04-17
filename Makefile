# Makefile for Project5

# Compiler flags: extra warnings (-Wall), debugging (-g), and Google Test
CPPFLAGS = -std=c++11 -Wall -g -I $(GTEST_ROOT)/include

all: project5 test

project5.o: project5.h

project5: project5.o
	g++ -o $@ $^

test: project5
	./project5 < test.in
