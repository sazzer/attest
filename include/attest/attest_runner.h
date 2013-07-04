/*
 * =====================================================================================
 *
 *       Filename:  attest_runner.h
 *
 *    Description:  Functions used in the running of tests, but that aren't part of the public API
 *
 *        Version:  1.0
 *        Created:  16/06/13 18:56:11
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Graham Cox (coxg), graham@grahamcox.co.uk
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef  ATTEST_RUNNER_INC
#define  ATTEST_RUNNER_INC

#include <functional>
#include <cstdint>
#include <string>

namespace Attest {
    /**
     * Iterate over each test that has been registered, calling the provided callback for each in turn
     * @param callback The callback to execute, which is called with the index and name of the test
     */
    void for_each_test(std::function<void(std::size_t, const char*)> callback);

    /**
     * Helper to clear the registered tests. This is only useful for testing purposes
     */
    void clear_tests();

    /**
     * Structure to represent the result of running a test
     */
    struct TestResult {
        public:
            /** The name of the test that was run */
            std::string name;
            /** The index of the test that was run */
            std::size_t index;
            /** Anything that was output by the test */
            std::string output;
            /** The error message if the test failed */
            std::string error;

            /**
             * Determine if the test was successful or not.
             * Basically a test is successful if there is no error message generated
             * @return true if the test is successful, false if not
             */
            bool success() const {
                return error.empty();
            }
    };

    /**
     * Actually run all of the registered tests, and call the provided callback function with the results of each test run
     * @return True if the tests all passed. False if any failed
     */
    bool run_tests(std::function<void(const TestResult&)> callback);
}

#endif   /* ----- #ifndef ATTEST_RUNNER_INC  ----- */
