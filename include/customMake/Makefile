# Comments start with #

PROJFILE = main.cpp

# Designate which compiler to use
CXX = g++-13

# Default flags
# Remember to put -Werror back in after -Wall
CXXFLAGS = -std=c++20 -Wconversion -Wall -Werror -Wextra -pedantic -g -I/opt/homebrew/opt/curl/include -I. -I./include -I./include/customMake
# Linker flags
LDFLAGS = -L/opt/homebrew/opt/curl/lib
# Libraries
LIBS = -lcurl

# Define the output directory for object files
OBJDIR = bin

# Define the source files used in the main project
SRCS = main.cpp src/Program.cpp src/inputReader.cpp src/blackScholesModel.cpp
SRCS := $(filter-out $(TESTSRCS), $(SRCS))

# Define the object files for the main program
OBJS := $(SRCS:.cpp=.o)

# Define the source files used in the test programs
TESTSRCS = gtest.cpp test/testProgram.cpp test/testInputReader.cpp test/testBlackScholesModel.cpp
TESTSRCS := $(filter-out main.cpp, $(TESTSRCS)) # Exclude main.cpp from TESTSRCS
TESTSRCS := $(filter $(TESTSRCS), $(SRCS))

## Define the object files for the test programs
#TESTOBJS = test/testProgram.o test/testInputReader.o test/testBlackScholesModel.o

# Create object file names from source file names
TESTOBJS = $(addprefix $(OBJDIR)/, $(TESTSRCS:.cpp=.o))

# Names of test executables
TESTS = testProgram testInputReader testBSModel

# Compile rule for each .cpp file to produce .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -arch arm64 -c $< -o $@      # For Apple Silicon (arm64) architecture
#    $(CXX) $(CXXFLAGS) -arch x86_64 -c $< -o $@   # For Intel (x86_64) architecture

# Specify the target main executable
EXE = bs

# Link rule to produce the final [main] executable
bs: $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -arch arm64 $(OBJS) -o $(EXE) $(LDLIBS)
#    $(CXX) $(CXXFLAGS) $(LDFLAGS) -arch x86_64 $(OBJS) -o $(EXE) $(LDLIBS)    # For Intel (x86_64) architecture

# Define the name of the final executable
TESTEXE = testProgram

# Rule to compile test C++ source files into object files
$(OBJDIR)/%.o: %.cpp
	$mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -arch arm64 -c $< -o $@


# Rule to build the final executable
testProgram: $(TESTOBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -arch arm64 $^ -o $@ $(LIBS)

## Rule to build test executables
#testProgram: test/testProgram.o
#	$(CXX) $(CXXFLAGS) $(LDFLAGS) -arch arm64 $^ -o $@ $(LIBS)

testInputReader: test/testInputReader.o $(filter-out $(OBJS), $(TESTOBJS))
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -arch arm64 $^ -o $@ $(LIBS)

testBSModel: test/testBSModel.o $(filter-out $(OBJS), $(TESTOBJS))
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -arch arm64 $^ -o $@ $(LIBS)

alltests: testProgram testInputReader testBSModel

# Clean rule to remove object files and the executable
.PHONY: clean
clean:
	rm -f $(OBJS) $(EXE) $(EXE)_debug $(EXE)_profile $(TESTS) $(TESTOBJS) test/testInputReader.o test/testBlackScholesModel.o
	rm -rf $(OBJDIR) $(TESTEXE)

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