CXX = g++
CXXFLAGS = -g -std=c++14 -Wall -Werror=return-type  -Werror=uninitialized

SRCS = $(wildcard *.cpp)
HEADERS = $(wildcard *.hpp)
OBJECTS = $(SRCS:%.cpp=%.o)

CATCH = test/catch/catch.o
TEST_SRCS = $(wildcard test/*.cpp)
TESTS = $(TEST_SRCS:test/%.cpp=%)

main: $(OBJECTS)
	$(CXX) -o $@ $^

clean:
	rm -rf main.dSYM
	$(RM) *.o *.gc* test/*.o test/*.gc* *.dSYM $(TESTS) core main $(CATCH)

