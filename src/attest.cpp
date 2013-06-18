/*
 * =====================================================================================
 *
 *       Filename:  attest.cpp
 *
 *    Description:  The main test registration and execution routines
 *
 *        Version:  1.0
 *        Created:  16/06/13 18:46:24
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
#include <list>
#include <string>
#include <memory>
#include <iostream>

namespace Attest {
    /**
     * The details of a single test that has been registered to be run
     */
    class Test {
        public:
            Test(const char* name, std::function<void(void)> testfunc) : name_(name), test_(testfunc) {
                std::cerr << "Registered test: " << name << std::endl;
            }
            ~Test() {
                std::cerr << "Destroyed test: " << name_ << std::endl;
            }
            /**
             * Get the name of the test
             * @return the name of the test
             */
            const char* name() const {
                return name_.c_str();
            }
            /**
             * Actually run the test
             */
            void run() const {
                test_();
            }
        private:
        /** The name of the test */
        std::string name_;
        /** The actual test function */
        std::function<void(void)> test_;
    };

    /** The list of tests to perform */
    static std::list<std::unique_ptr<Test> > tests;


    /**
     * Actually register a new test case with the given name. 
     * This only actually returns a value so that it can be used to assign to a static variable
     * which ensures that the method gets called before the main function runs
     *
     * @param name The name to give the test case
     * @param testfunc The actual test function
     * @return True if the function was registered. 
     */
    bool Attest_register(const char* name, std::function<void(void)> testfunc) {
        std::unique_ptr<Test> test(new Test(name, testfunc));
        tests.push_back(std::move(test));
        return true;
    }

    /**
     * Iterate over each test that has been registered, calling the provided callback for each in turn
     * @param callback The callback to execute, which is called with the index and name of the test
     */
    void for_each_test(std::function<void(std::size_t, const char*)> callback) {
        size_t index = 0;
        for (auto iter = tests.begin(); iter != tests.end(); ++iter, ++index) {
            callback(index, (*iter)->name());
        }
    }

    /**
     * Helper to clear the registered tests. This is only useful for testing purposes
     */
    void clear_tests() {
        tests.clear();
    }

    /**
     * Actually run all of the registered tests, and call the provided callback function with the results of each test run
     */
    void run_tests(std::function<void(const TestResult&)> callback) {
        size_t index = 0;
        for (auto iter = tests.begin(); iter != tests.end(); ++iter, ++index) {
            TestResult testResult = {
                (*iter)->name(),
                index,
                "",
                ""
            };

            try {
                (*iter)->run();
            }
            catch (const char* e) {
                testResult.error = e;
            }
            catch (const std::string& e) {
                testResult.error = e;
            }
            catch (const std::exception& e) {
                testResult.error = e.what();
            }
            catch (...) {
                testResult.error = "An unknown error occurred";
            }

            callback(testResult);
        }
    }
}
