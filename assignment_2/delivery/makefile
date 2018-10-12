CXXFLAGS = -std=c++14 -pthread -Wall -Wno-dangling-else -O3

CXX := /usr/bin/clang++

all: bwtencode bwtsearch

bwtencode: bwtencode.cpp encoder.cpp bwt.cpp
	$(CXX) $(CXXFLAGS) -o bwtencode bwtencode.cpp encoder.cpp bwt.cpp util.cpp

bwtsearch: bwtsearch.cpp
	$(CXX) $(CXXFLAGS) -o bwtsearch bwtsearch.cpp search.cpp util.cpp
