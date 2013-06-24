/*
 * =====================================================================================
 *
 *       Filename:  runner.cpp
 *
 *    Description:  Implementation of the core components of the runners
 *
 *        Version:  1.0
 *        Created:  24/06/13 19:31:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Graham Cox (coxg), graham@grahamcox.co.uk
 *        Company:  
 *
 * =====================================================================================
 */

#include "attest/runner.h"
#include <map>

namespace Attest {
    /** The map of runners that can be used */
    static std::map<std::string, std::function<std::unique_ptr<Runner>()> > runners;

    /**
     * Register a new construction function for a new Runner of some kind
     * @param name The name of the runner
     * @param constructor The function to construct the runner
     * @return True if the runner was registered successfully. False if not
     */
    bool registerRunner(const std::string& name, std::function<std::unique_ptr<Runner>()> constructor) {
        bool result = false;
        if (runners.count(name) == 0) {
            runners[name] = constructor;
            result = true;
        }
        return result;
    }

    /**
     * Build a runner with the given name
     * @param name The name of the runner to build
     * @return the built runner
     */
    std::unique_ptr<Runner> buildRunner(const std::string& name) {
        std::unique_ptr<Runner> result;
        if (runners.count(name) == 1) {
            result = runners[name]();
        }
        return result;
    }

    /**
     * Helper to clear the registered runners. Used for unit tests
     */
    void clearRunners() {
        runners.clear();
    }
}
