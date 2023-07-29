//
//  Program_tests.cpp
//  black-scholes
//
//  Created by lyndskg on 7/19/23.

#include <iostream>
#include <fstream>
//
#include "../include/custom make/unit_test_framework.h"
#include "../src/Program.h"
#include "../src/inputReader.h"
#include "../src/inputReader.cpp"
#include "../src/Program.cpp"
#include "../src/blackScholesModel.h"
#include "../src/blackScholesModel.cpp"

using namespace std;

//using Test_func_t = void (*)();

// Demonstrate some basic assertions.
TEST(test_default_constructor) {
    blackScholesModel model;
	ASSERT_EQUAL(model.version, "1");

} // test_default_constructor

// Demonstrate some basic assertions.
TEST(test_custom_constructor) {
    blackScholesModel model(100, 100, 100, 100, 100);

} // test_default_constructor

// Demonstrate some basic assertions.
TEST(test_calculate_option_price) {
    blackScholesModel model;
}

// Demonstrate some basic assertions.
TEST(test_normal_cdf) {
    blackScholesModel model;
}; // test_default_constructor

// Demonstrate some basic assertions.
TEST(test_calculate_d1) {
    blackScholesModel model;
}

// Demonstrate some basic assertions.
TEST(test_calculate_d2) {
    blackScholesModel model;
}

// Demonstrate some basic assertions.
TEST(test_calculate_k) {
    blackScholesModel model;
}

// Demonstrate some basic assertions.
TEST(test_set_underlying_price) {
    blackScholesModel model;
}

// Demonstrate some basic assertions.
TEST(test_set_strike_price) {
    blackScholesModel model;
}

// Demonstrate some basic assertions.
TEST(test_set_TTE) {
    blackScholesModel model;
}

// Demonstrate some basic assertions.
TEST(test_set_RFR) {
    blackScholesModel model;
}

// Demonstrate some basic assertions.
TEST(test_set_volatility) {
    blackScholesModel model;
}

// Demonstrate some basic assertions.
TEST(test_set_option_type) {
    blackScholesModel model;
}

// Demonstrate some basic assertions.
TEST(test_set_d1) {
    blackScholesModel model;
}

// Demonstrate some basic assertions.
TEST(test_set_d2) {
    blackScholesModel model;
}

// Demonstrate some basic assertions.
TEST(test_set_k) {
    blackScholesModel model;
}

// Demonstrate some basic assertions.
TEST(test_get_underlying_price) {
    blackScholesModel model;
}

// Demonstrate some basic assertions.
TEST(test_get_strike_price) {
    blackScholesModel model;
}

// Demonstrate some basic assertions.
TEST(test_get_TTE) {
    blackScholesModel model;
}

// Demonstrate some basic assertions.
TEST(test_get_RFR) {
    blackScholesModel model;
}

// Demonstrate some basic assertions.
TEST(test_get_volatility) {
    blackScholesModel model;
}

// Demonstrate some basic assertions.
TEST(test_get_option_type) {
    blackScholesModel model;
}

// Demonstrate some basic assertions.
TEST(test_get_d1) {
    blackScholesModel model;
}

// Demonstrate some basic assertions.
TEST(test_get_d2) {
    blackScholesModel model;
}

// Demonstrate some basic assertions.
TEST(test_get_k) {
    blackScholesModel model;
}