/*
 * =====================================================================================
 *
 *       Filename:  test_run_tests.cpp
 *
 *    Description:  Test that running of tests works correctly
 *
 *        Version:  0.1
 *        Created:  17/06/13 20:23:42
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Graham Cox (coxg), graham@grahamcox.co.uk
 *        Company:  
 *
 * =====================================================================================
 */

#include "attest/attest.h"
#include "attest/attest_runner.h"
#include <cstring>
#include <stdexcept>
#include "test_harness.h"

void run_test(const char* name, const char* output, const char* error, const std::function<void(void)>& testcase) {
    Attest::clear_tests();
    Attest::Attest_register(name, testcase);
    bool seenIt = false;
    bool result = Attest::run_tests([&](const Attest::TestResult& result){
        seenIt = true;
        if (result.index != 0) {
            throw "Unexpected index seen";
        }
        if (result.name != name) {
            throw "Unexpected name seen";
        }
        if (output == 0 && !result.output.empty()) {
            throw "No output expected";
        }
        if (output != 0 && result.output != output) {
            throw "Incorrect output received";
        }
        if (error == 0) {
            if (result.success() == false) {
                throw "Success expected";
            }
            if (!result.error.empty()) {
                throw "Unexpected error message";
            }
        }
        else {
            if (result.success() == true) {
                throw "Failure expected";
            }
            if (result.error != error) {
                throw "Unexpected error message";
            }
        }
    });
    if (seenIt == false) {
        throw "Test wasn't run";
    }
    if (result && error) {
        throw "Expected to fail but passed";
    }
    else if (!result && !error) {
        throw "Expected to pass but failed";
    }
}

int main(void) {
    run("test_run_success", [](){
        run_test("Simple", "", 0, [](){});
    });
    run("test_run_throws_string", [](){
        run_test("ThrowsString", "", "This is a string", [](){
            throw "This is a string";
        });
    });
    run("test_run_throws_exception", [](){
        run_test("ThrowsException", "", "This is a string", [](){
            throw std::runtime_error("This is a string");
        });
    });
    run("test_stdout", [](){
        run_test("Stdout", "Output", 0, [](){
            std::cout << "Output";
        });
    });
    run("test_stderr", [](){
        run_test("Stderr", "Errput", 0, [](){
            std::cerr << "Errput";
        });
    });
    run("test_stdout_and_stderr", [](){
        run_test("StdoutStderr", "OutputErrput", 0, [](){
            std::cout << "Output";
            std::cerr << "Errput";
        });
    });
    return test_result ? 0 : 1;
}

