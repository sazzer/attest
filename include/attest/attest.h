/*
 * =====================================================================================
 *
 *       Filename:  attest.h
 *
 *    Description:  Main attest header file
 *
 *        Version:  1.0
 *        Created:  16/06/13 18:33:53
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Graham Cox (coxg), graham@grahamcox.co.uk
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef  ATTEST_INC
#define  ATTEST_INC

#include <functional>

namespace Attest {
    /**
     * Actually register a new test case with the given name. 
     * This only actually returns a value so that it can be used to assign to a static variable
     * which ensures that the method gets called before the main function runs
     *
     * @param name The name to give the test case
     * @param testfunc The actual test function
     * @return True if the function was registered. 
     */
    bool Attest_register(const char* name, std::function<void(void)> testfunc);
}

#define CONCATENATE_DETAIL(x, y) x##y
#define CONCATENATE(x, y) CONCATENATE_DETAIL(x, y)
#define MAKE_TEST_NAME CONCATENATE(test, __COUNTER__)
#define ATTEST_DETAIL(var, name, function) static const bool var = Attest_register(name, function);
#define ATTEST(name, function) ATTEST_DETAIL(MAKE_TEST_NAME, name, function)

#endif   /* ----- #ifndef ATTEST_INC  ----- */
