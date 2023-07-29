//
//  Program_tests.cpp
//  black-scholes
//
//  Created by lyndskg on 7/19/23.

#include <iostream>
#include <fstream>

#include "../Program.h"
#include "../inputReader.h"
#include "../inputReader.cpp"
#include "../Program.cpp"
#include "../unit_test_framework.h"

using namespace std;

// Demonstrate some basic assertions.
TEST(test_default_constructor) {
    inputReader reader;
    ASSERT_EQ(reader.mode, "USER");
}; // test_default_constructor

// Demonstrate some basic assertions.
TEST(test_read_from_user) {
    inputReader reader;
}; // test_default_constructor

// Demonstrate some basic assertions.
TEST(test_read_from_file) {
    inputReader reader;
}; // test_default_constructor

// Demonstrate some basic assertions.
TEST(test_read_from_db) {
    inputReader reader;
}

// Demonstrate some basic assertions.
TEST(test_read_from_api) {
    inputReader reader;
}; // test_default_constructor

// Demonstrate some basic assertions.
TEST(test_validate_set_input) {
    inputReader reader;
}; // test_default_constructor

// Demonstrate some basic assertions.
TEST(test_response_callback) {
    inputReader reader;
}; // test_default_constructor