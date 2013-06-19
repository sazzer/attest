/*
 * =====================================================================================
 *
 *       Filename:  test_assertions.cpp
 *
 *    Description:  Unit tests for the assertions
 *
 *        Version:  1.0
 *        Created:  18/06/13 20:17:47
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Graham Cox (coxg), graham@grahamcox.co.uk
 *        Company:  
 *
 * =====================================================================================
 */

#include "attest/assert.h"
#include <cstring>
#include "test_harness.h"
#include <iostream>

void testAssertion(std::function<void(void)> assertion) {
    try {
        assertion();
    }
    catch (const Attest::Assert::AssertionException& e) {
        // This is expected
        std::cout << "Assertion message: " << e.what() << std::endl;
    }
}

int main(void) {
    run("test_construct_assertion_exception", [](){
        Attest::Assert::AssertionException e("This is the message");
        if (strcmp("This is the message", e.what()) != 0) {
            throw "Wrong message returned";
        }
    });

    run("test_assert_equals", [](){
        Attest::Assert::equals(1, 1);

        testAssertion([](){
            Attest::Assert::equals(1, 2);
        });

        Attest::Assert::equals(std::string("Hello"), std::string("Hello"));

        testAssertion([](){
            Attest::Assert::equals(std::string("Hello"), std::string("World"));
        });
    });

    run("test_assert_not_equals", [](){
        Attest::Assert::not_equals(1, 2);

        testAssertion([](){
            Attest::Assert::not_equals(1, 1);
        });
    });

    run("test_assert_less_than", [](){
        Attest::Assert::less_than(1, 2);

        testAssertion([](){
            Attest::Assert::less_than(2, 1);
        });
        testAssertion([](){
            Attest::Assert::less_than(1, 1);
        });
    });

    run("test_assert_less_than_or_equal", [](){
        Attest::Assert::less_than_or_equal(1, 2);
        Attest::Assert::less_than_or_equal(1, 1);

        testAssertion([](){
            Attest::Assert::less_than_or_equal(2, 1);
        });
    });

    run("test_assert_greater_than", [](){
        Attest::Assert::greater_than(2, 1);

        testAssertion([](){
            Attest::Assert::greater_than(1, 1);
        });
        testAssertion([](){
            Attest::Assert::greater_than(1, 2);
        });
    });

    run("test_assert_greater_than_or_equal", [](){
        Attest::Assert::greater_than_or_equal(2, 1);
        Attest::Assert::greater_than_or_equal(1, 1);

        testAssertion([](){
            Attest::Assert::greater_than_or_equal(1, 2);
        });
    });

    run("test_assert_true", [](){
        Attest::Assert::is_true(true);
        Attest::Assert::is_true(1 == 1);

        testAssertion([](){
            Attest::Assert::is_true(false);
        });
    });

    run("test_assert_false", [](){
        Attest::Assert::is_false(false);
        Attest::Assert::is_false(1 == 2);

        testAssertion([](){
            Attest::Assert::is_false(true);
        });
    });

    run("test_assert_fail", [](){
        testAssertion([](){
            Attest::Assert::fail();
        });
        testAssertion([](){
            Attest::Assert::fail("I failed");
        });
    });
    return test_result ? 0 : 1;
}

