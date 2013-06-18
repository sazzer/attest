/*
 * =====================================================================================
 *
 *       Filename:  test_register.cpp
 *
 *    Description:  Tests for the registration of unit tests
 *
 *        Version:  1.0
 *        Created:  16/06/13 19:05:18
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
#include "test_harness.h"

int main(void) {
    run("test_register_simple", [](){
        int highestIndex = -1;
        Attest::clear_tests();
        Attest::Attest_register("Simple", [](){});
        Attest::for_each_test([&](int index, const char* name){
            std::cout << "Seen test " << index << " called " << name << std::endl;
            if (index > 0) {
                throw "More tests than expected were returned!";
            }
            if (index == 0 && strcmp("Simple", name) != 0) {
                throw "Test 0 had the wrong name";
            }
            highestIndex = std::max(highestIndex, index);
        });
        if (highestIndex != 0) {
            throw "Highest Index wasn't what was expected";
        }
    });
    return test_result ? 0 : 1;
}
