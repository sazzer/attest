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

namespace Attest {
    /**
     * Iterate over each test that has been registered, calling the provided callback for each in turn
     * @param callback The callback to execute, which is called with the index and name of the test
     */
    void for_each_test(std::function<void(std::size_t, const char*)> callback);
}

#endif   /* ----- #ifndef ATTEST_RUNNER_INC  ----- */
