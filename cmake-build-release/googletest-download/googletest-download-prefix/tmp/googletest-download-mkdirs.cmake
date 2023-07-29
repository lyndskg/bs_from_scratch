# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/lyndseygu/Projects/C++/FML/cmake-build-release/googletest-src"
  "/Users/lyndseygu/Projects/C++/FML/cmake-build-release/googletest-build"
  "/Users/lyndseygu/Projects/C++/FML/cmake-build-release/googletest-download/googletest-download-prefix"
  "/Users/lyndseygu/Projects/C++/FML/cmake-build-release/googletest-download/googletest-download-prefix/tmp"
  "/Users/lyndseygu/Projects/C++/FML/cmake-build-release/googletest-download/googletest-download-prefix/src/googletest-download-stamp"
  "/Users/lyndseygu/Projects/C++/FML/cmake-build-release/googletest-download/googletest-download-prefix/src"
  "/Users/lyndseygu/Projects/C++/FML/cmake-build-release/googletest-download/googletest-download-prefix/src/googletest-download-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/lyndseygu/Projects/C++/FML/cmake-build-release/googletest-download/googletest-download-prefix/src/googletest-download-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/lyndseygu/Projects/C++/FML/cmake-build-release/googletest-download/googletest-download-prefix/src/googletest-download-stamp${cfgdir}") # cfgdir has leading slash
endif()
