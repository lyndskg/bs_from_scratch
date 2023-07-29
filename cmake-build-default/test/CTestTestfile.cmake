# CMake generated Testfile for 
# Source directory: /Users/lyndseygu/Projects/C++/FML/test
# Build directory: /Users/lyndseygu/Projects/C++/FML/cmake-build-default/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[example_test]=] "example")
set_tests_properties([=[example_test]=] PROPERTIES  _BACKTRACE_TRIPLES "/Users/lyndseygu/Projects/C++/FML/test/CMakeLists.txt;83;add_test;/Users/lyndseygu/Projects/C++/FML/test/CMakeLists.txt;0;")
add_test([=[default_ctor]=] "/Users/lyndseygu/Projects/C++/FML/cmake-build-default/test/test")
set_tests_properties([=[default_ctor]=] PROPERTIES  _BACKTRACE_TRIPLES "/Users/lyndseygu/Projects/C++/FML/test/CMakeLists.txt;93;add_test;/Users/lyndseygu/Projects/C++/FML/test/CMakeLists.txt;0;")
add_test([=[custom_ctor]=] "/Users/lyndseygu/Projects/C++/FML/cmake-build-default/test/test")
set_tests_properties([=[custom_ctor]=] PROPERTIES  _BACKTRACE_TRIPLES "/Users/lyndseygu/Projects/C++/FML/test/CMakeLists.txt;94;add_test;/Users/lyndseygu/Projects/C++/FML/test/CMakeLists.txt;0;")
subdirs("../googletest-build")
