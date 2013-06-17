/*
 * =====================================================================================
 *
 *       Filename:  test_auto_register.cpp
 *
 *    Description:  Tests for the automatic registration of unit tests
 *
 *        Version:  1.0
 *        Created:  17/06/13 12:36:16
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

ATTEST("Test1", [](){})
ATTEST("Test2", [](){})

/**
 * Test that functions that were automatically registered are indeed found
 */
void test_register_auto() {
    int highestIndex = -1;
    Attest::for_each_test([&](int index, const char* name){
        std::cout << "Seen test " << index << " called " << name << std::endl;
        if (index > 1) {
            throw "More tests than expected were returned!";
        }
        if (index == 0 && strcmp("Test1", name) != 0) {
            throw "Test 0 had the wrong name";
        }
        if (index == 1 && strcmp("Test2", name) != 0) {
            throw "Test 1 had the wrong name";
        }
        highestIndex = std::max(highestIndex, index);
    });
    if (highestIndex != 1) {
        throw "Highest Index wasn't what was expected";
    }
}

int main(void) {
    run("test_register_auto", test_register_auto);
    return 0;
}

