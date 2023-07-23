//
// Created by lyndskg on 7/22/23.
//

// schlissel.cpp

#include "schlissel.h"

using namespace std;

TestSuite* TestSuite::instance = nullptr;

// Implement the static member variable 'incomplete' of TestSuite.
bool TestSuite::incomplete = false;


TestSuite::TestSuite() {
    auto func = []() {
        if (TestSuite::incomplete) {
            cout << "ERROR: premature call to exit()\n";
            abort();
        } // if
    }; // func

    atexit(func);

#ifdef _GLIBCXX_HAVE_AT_QUICK_EXIT
    at_quick_exit(func);
#endif
} // TestSuite::TestSuite()

TestSuite::~TestSuite() {
    for (const auto& test : tests_) {
        delete test.second.test_func;
    }
} // TestSuite::~TestSuite()

// Implement the TestSuite class methods
TestSuite& TestSuite::get() {
    if (instance == nullptr) {
        instance = new TestSuite;
    } // if

    return *instance;
} // TestSuite::get()

void TestSuite::add_test(const string& test_name, Test_func_t test) {
    tests_.insert({test_name, TestCase{ test_name, test }});
} // TestSuite::add_test()

int TestSuite::run_tests(int argc, char *argv[]) {
    // ... (existing implementation of run_tests)

    auto num_failures= count_if(tests_.begin(),tests_.end(),
                                 [](const pair<string, TestCase>& test_pair){
                                          return !(test_pair.second.failure_msg.empty());
                                 	 }
                                 ); // count_if()

    auto num_errors= count_if(tests_.begin(),tests_.end(),
                               [](const pair<string, TestCase>& test_pair) {
                                         return !(test_pair.second.exception_msg.empty());
    								}
                               ); // count_if()

    // ... (existing implementation of run_tests)

    if (num_failures == 0 && num_errors == 0) {
        return 0;
    } // if

    return 1;
} // TestSuite::run_tests()


void TestSuite::enable_quiet_mode() {
    quiet_mode = true;
} // TestSuite::enable_quiet_mode()


ostream& TestSuite::print_test_names(ostream& os) {
    for (const auto& test_pair : tests_) {
        os << test_pair.first << '\n';
    } // for

    return os;
} // TestSuite::print_test_names()

// Implement the TestFailure ostream operator
ostream& operator<<(ostream& os, const TestFailure& test_failure) {
    return test_failure.print(os);
} // operator<<(ostream& os, const TestFailure& test_failure)>>

// Implement the assert_equal function
template <typename First, typename Second>
void assert_equal(First&& first, Second&& second, int line_number) {
    if (safe_equals<First, Second>::equals(first, second)) {
        return;
    } // if (safe_equals<First, Second>::equals(first, second)) {}

    ostringstream reason;
    print(reason, first);
    reason << " != ";
    print(reason, second);
    throw TestFailure(reason.str(), line_number);
} // template <typename First, typename Second> void assert_equal(First&& first, Second&&

// Implement the assert_not_equal function
template <typename First, typename Second>
void assert_not_equal(First&& first, Second&& second, int line_number) {
    if (safe_equals<First, Second>::not_equals(first, second)) {
        return;
    }

    ostringstream reason;
    reason << "Values unexpectedly equal: ";
    print(reason, first);
    reason << " == ";
    print(reason, second);
    throw TestFailure(reason.str(), line_number);
}

// Implement the remaining assert functions (assert_true, assert_false, assert_almost_equal, etc.)
// ...

// Implement the demangle function (if needed, depending on the platform)
#if defined(__clang__) || defined(__GLIBCXX__) || defined(__GLIBCPP__)
#include <cxxabi.h>
string demangle(const char* typeinfo_name) {
    int status = 0;
    char* demangled = abi::__cxa_demangle(typeinfo_name, nullptr, nullptr, &status);

    if (status == 0) {
        string result = demangled;
        free(demangled);
        return result;
    } else {
        return typeinfo_name;
    }
}
#else
string demangle(const char* typeinfo_name) {
    return typeinfo_name;
}
#endif

// Implement the print function (if needed, depending on the use case)
template <class T>
ostream& print(ostream& os, const T& t) {
    // The extra parameters are needed so that the first overload of
    // print_helper is preferred, followed by the third one.
    return print_helper(os, t, 0, 0);
}
