# Comments start with #

# Variable definitions
CXX = g++
CXXFLAGS = -std=c++20 -Wconversion -Wall -Werror -Wextra -pedantic -g -I/opt/homebrew/opt/curl/include -I.
LDFLAGS = -L/opt/homebrew/opt/curl/lib
LIBS = -lcurl

PROJFILE = main.cpp

# Rule to compile C++ source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Define the source files used in the main project
SRCS = blackScholesModel.cpp inputReader.cpp Program.cpp

# Define the source files used in the test programs
TESTSRCS = testBlackScholesModel.cpp testInputReader.cpp testProgram.cpp
TESTSRCS := $(filter $(TESTSRCS), $(SRCS))

# Define the object files for the test programs
TESTOBJS = $(addprefix tests/, $(TESTSRCS:.cpp=.o))

SRCS := $(filter-out $(TESTSRCS), $(SRCS))

# Define the object files for the main program
OBJS := $(SRCS:.cpp=.o)

# Specify the target main executable
EXE = bs

# Rule to build the main program
bs: $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)

# Rule to compile test C++ source files into object files
tests/%.o: tests/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to build test executables
testProgram: tests/testProgram.o $(filter-out $(OBJS), $(TESTOBJS))
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)

testInputReader: tests/testInputReader.o $(filter-out $(OBJS), $(TESTOBJS))
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)

testBSModel: tests/testBSModel.o $(filter-out $(OBJS), $(TESTOBJS))
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)

# Specify the target executable to build all tests from all test files
TESTS = testProgram testInputReader testBSModel  # Names of test executables
alltests: $(TESTS)

# Clean rule to remove object files and the executable
clean:
	rm -f $(OBJS) $(EXE) $(EXE)_debug $(EXE)_profile $(TESTS) $(TESTOBJS)

# Unit tests target
.PHONY: unit_tests
unit_tests: alltests
	@for test in $(TESTS); do \
		echo "Running $$test"; \
		./$$test; \
	done





## Automatically generate any build rules for test*.cpp files
#define make_tests
#    ifeq ($(PROJFILE),)
#	    @echo Edit PROJFILE variable to .cpp file with main\(\)
#	    @exit 1
#    endif
#    SRCS = $(filter-out $(PROJFILE), $(SRCS))
#    OBJS = $(SRCS:.cpp=.o)
#    HDRS = inputReader.h Program.h blackScholesModel.h
#    $(1): CXXFLAGS += -g3 -DDEBUG
#    $(1): $(TESTOBJS) $(HDRS) $(1).cpp
#	$(CXX) $(CXXFLAGS) $(TESTOBJS) $(1).cpp -o $(1)
#endef
#
## Rule to build test executables
#TESTS = testProgram testInputReader testBSModel  # Names of test executables
#$(TESTS): %: %.o $(OBJS)
#	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)
#
#$(foreach test, $(TESTS), $(eval $(call make_tests, $(test))))
#
## Specify the target executable to build all tests from all test files
#alltests: $(TESTS)