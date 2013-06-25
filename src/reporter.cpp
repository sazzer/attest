/*
 * =====================================================================================
 *
 *       Filename:  reporter.cpp
 *
 *    Description:  Implementation of the core components of the reporters
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

#include "attest/reporter.h"
#include <map>

namespace Attest {
    /** The map of reporters that can be used */
    static std::map<std::string, std::function<std::unique_ptr<Runner>()> > reporters;

    /**
     * Register a new construction function for a new Runner of some kind
     * @param name The name of the reporter
     * @param constructor The function to construct the reporter
     * @return True if the reporter was registered successfully. False if not
     */
    bool registerRunner(const std::string& name, std::function<std::unique_ptr<Runner>()> constructor) {
        bool result = false;
        if (reporters.count(name) == 0) {
            reporters[name] = constructor;
            result = true;
        }
        return result;
    }

    /**
     * Build a reporter with the given name
     * @param name The name of the reporter to build
     * @return the built reporter
     */
    std::unique_ptr<Runner> buildRunner(const std::string& name) {
        std::unique_ptr<Runner> result;
        if (reporters.count(name) == 1) {
            result = reporters[name]();
        }
        return result;
    }

    /**
     * Helper to clear the registered reporters. Used for unit tests
     */
    void clearRunners() {
        reporters.clear();
    }
}
