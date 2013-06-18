/*
 * =====================================================================================
 *
 *       Filename:  test_harness.h
 *
 *    Description:  Test harness for testing the unit tests
 *
 *        Version:  1.0
 *        Created:  16/06/13 19:14:13
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Graham Cox (coxg), graham@grahamcox.co.uk
 *        Company:  
 *
 * =====================================================================================
 */


#ifndef  TEST_HARNESS_INC
#define  TEST_HARNESS_INC

#include <iostream>
#include <sstream>

/** The test result to return */
static bool test_result = true;

/**
 * Actually run a test
 * @param name The name of the test to run
 * @param test The test function itself
 */
void run(const char* name, std::function<void(void)> test) {
    std::cerr << "About to execute test: " << name;
    std::stringstream buffer;
    std::streambuf* oldout = std::cout.rdbuf(buffer.rdbuf());
    std::streambuf* olderr = std::cerr.rdbuf(buffer.rdbuf());
    const char* error = 0;

    try {
        test();
    }
    catch (const char* e) {
        error = e;
    }


    std::cout.rdbuf(oldout);
    std::cerr.rdbuf(olderr);
    std::string testOutput = buffer.str();

    if (error) {
        std::cerr << "   FAILURE" << std::endl;
        std::cerr << "   ----- " << error << std::endl;
    }
    else {
        std::cerr << "   SUCCESS" << std::endl;
    }

    if (!testOutput.empty()) {
        std::cerr << "Test output:" << std::endl;
        std::cerr << testOutput << std::endl;
    }

    if (error) {
        test_result = false;
    }
}

#endif   /* ----- #ifndef TEST_HARNESS_INC  ----- */
