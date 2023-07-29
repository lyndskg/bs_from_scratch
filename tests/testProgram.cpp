//
//  Program_tests.cpp
//  black-scholes
//
//  Created by lyndskg on 7/19/23.

#include <iostream>
#include <fstream>

#include "../unit_test_framework.h"
#include "../Program.h"
#include "../inputReader.h"
#include "../Program.cpp"

using namespace std;


// Demonstrate some basic assertions.
TEST(test_default_constructor) {
        Program program;

        ASSERT_EQUAL(program.inputMode, program.readInputMode());
        ASSERT_TRUE(program.inputMode.empty());
        ASSERT_EQUAL(program.inputMode, "");
        ASSERT_FALSE(sizeof(program.inputMode) > 0);
        ASSERT_FALSE(program.inputMode != "");

        cout << program.inputMode << "\n";
} // test_default_constructor

TEST(test_get_input_mode) {
	Program program;

    char* argv[] = {(char*)"program_name", (char*)"--mode", (char*)"USER"};
    int argc = sizeof(argv) / sizeof(argv[0]);

    program.get_options(argc, argv);
    ASSERT_EQUAL(program.getInputMode(), "USER");
    ASSERT_FALSE(program.invalidMode);

    cout << program.inputMode << "\n";
}

TEST(get_input_mode) {
    Program program;

    char* argv[] = {(char*)"program_name", (char*)"--mode", (char*)"USER"};
    int argc = sizeof(argv) / sizeof(argv[0]);

    program.get_options(argc, argv);
    ASSERT_EQUAL(program.getInputMode(), "USER");
    ASSERT_FALSE(program.invalidMode);

    cout << program.inputMode << "\n";
}

TEST(test_set_input_mode) {
    Program program;

    char* argv[] = {(char*)"program_name", (char*)"--mode", (char*)"USER"};
    int argc = sizeof(argv) / sizeof(argv[0]);

    program.get_options(argc, argv);
    ASSERT_EQUAL(program.getInputMode(), "USER");
    ASSERT_FALSE(program.invalidMode);

    cout << program.inputMode << "\n";
}

//TEST(test_get_help, valid_assertions) {
//    Program program;
//
//    char* argv[] = {(char*)"program_name", (char*)"--help"};
//    int argc = sizeof(argv) / sizeof(argv[0]);
//
//    program.get_options(argc, argv);
//    ASSERT_TRUE(program.help);
//
//    cout << program.inputMode << "\n";
//}

TEST(test_launch_algo) {
    Program program;

    char* argv[] = {(char*)"program_name", (char*)"--mode", (char*)"USER"};
    int argc = sizeof(argv) / sizeof(argv[0]);

    program.get_options(argc, argv);
    ASSERT_EQUAL(program.getInputMode(), "USER");
    ASSERT_FALSE(program.invalidMode);

    cout << program.inputMode << "\n";
}