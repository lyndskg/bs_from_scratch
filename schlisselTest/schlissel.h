//
//  schlissel.h
//  black-scholes
//
//  Created by lyndskg on 7/19/23.
//

#ifndef schlissel_h
#define schlissel_h

#include <iostream>
#include <sstream>
#include <cmath>
#include <vector>
#include <map>
#include <utility>
#include <string>
#include <algorithm>
#include <exception>
#include <stdexcept>
#include <type_traits>
#include <cstdlib>
#include <iterator>
#include <memory>
#include <typeinfo>
#include <ciso646>

using namespace std;

// For compatibility with Visual Studio
#include <ciso646>

// Place the following line of code in your test file to generate a
// main() function:
// TEST_MAIN()

using Test_func_t = void (*)();


#define TEST(name)                                                            \
    static void name();                                                       \
    static TestRegisterer register_##name((#name), name);                     \
    static void name()

#define TEST_MAIN()                                                           \
    int main(int argc, char** argv) {                                         \
        return TestSuite::get().run_tests(argc, argv);                        \
    }                                                                         \
    TEST_SUITE_INSTANCE();


struct TestCase {
    TestCase(const string& name_, Test_func_t test_func_)
        : name(name_), test_func(test_func_) {}

    void run(bool quiet_mode);
    void print(bool quiet_mode);

    string name;
    Test_func_t test_func;
    string failure_msg{};
    string exception_msg{};
}; // struct TestCase


class TestSuite {
public:
    TestSuite();

    TestSuite(const TestSuite&) = delete;

    bool operator=(const TestSuite&) = delete;

    ~TestSuite();

    static TestSuite& get();

    void add_test(const string& test_name, Test_func_t test);

    int run_tests(int argc, char* argv[]);

    void enable_quiet_mode();

    ostream& print_test_names(ostream& os);

    friend class TestSuiteDestroyer;

private:

    vector<string> get_test_names_to_run(int argc, char *argv[]);

    static TestSuite* instance;
    map<string, TestCase> tests_;

    bool quiet_mode = false;
    static bool incomplete;
}; // class TestSuite

class TestSuiteDestroyer {
public:
    ~TestSuiteDestroyer() {
        delete TestSuite::instance;
    } // ~TestSuiteDestroyer()
}; // class TestSuiteDestroyer


class TestRegisterer {
public:
    TestRegisterer(const string& test_name, Test_func_t test) {
        TestSuite::get().add_test(test_name, test);
    } // TestRegisterer()
}; // class TestRegisterer


class TestFailure : public exception {
public:
    TestFailure(string reason, int line_number)
            : reason_m(move(reason)), line_number_m(line_number) {}

    ostream& print(ostream& os) const {
        os << "In test " << test_name_m << ", line " << line_number_m << ": \n"
           << reason_m << '\n';
        return os;
    } // print()

    void set_test_name(string test_name) {
        test_name_m = move(test_name);
    } // set_test_name()

    string to_string() const {
        ostringstream oss;
        print(oss);
        return oss.str();
    } // to_string()

private:
    string test_name_m;
    string reason_m;
    int line_number_m;
}; // class TestFailure


ostream& operator<<(ostream& os, const TestFailure& test_failure);

string demangle(const char* typeinfo_name);

template <class T>
ostream& print(ostream& os, const T& t);

template <typename First, typename Second>
void assert_equal(First&& first, Second&& second, int line_number);

template <typename First, typename Second>
void assert_not_equal(First&& first, Second&& second, int line_number);

void assert_true(bool value, int line_number);
void assert_false(bool value, int line_number);

void assert_almost_equal(double first, double second, double precision, int line_number);

#define ASSERT_EQUAL(first, second) assert_equal((first), (second), __LINE__)
#define ASSERT_NOT_EQUAL(first, second) assert_not_equal((first), (second), __LINE__)

#endif /* schlissel_h */
