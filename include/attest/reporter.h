/*
 * =====================================================================================
 *
 *       Filename:  reporter.h
 *
 *    Description:  Base representation of the reporter to use
 *
 *        Version:  1.0
 *        Created:  19/06/13 20:39:25
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Graham Cox (coxg), graham@grahamcox.co.uk
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef  RUNNER_INC
#define  RUNNER_INC

#include <boost/program_options.hpp>
#include <memory>
#include <functional>
#include <string>

namespace Attest {
    /**
     * Class to represent a reporter to use to run the test and produce output
     */
    class Runner {
        public:
            /**
             * Virtual destructor
             */
            virtual ~Runner() {
            }
            /**
             * Configure the options that are supported by this reporter
             * @param options The options object to configure
             */
            virtual void configureOptions(boost::program_options::options_description& options) {
            }

            /**
             * Configure the reporter based on the variables provided by the supplied variables map
             * @param options The options to use to configure the reporter
             */
            virtual void processOptions(const boost::program_options::variables_map& options) {
            }
    };

    /**
     * Register a new construction function for a new Runner of some kind
     * @param name The name of the reporter
     * @param constructor The function to construct the reporter
     * @return True if the reporter was registered successfully. False if not
     */
    bool registerRunner(const std::string& name, std::function<std::unique_ptr<Runner>()> constructor);

    /**
     * Build a reporter with the given name
     * @param name The name of the reporter to build
     * @return the built reporter
     */
    std::unique_ptr<Runner> buildRunner(const std::string& name);

    /**
     * Helper to clear the registered reporters. Used for unit tests
     */
    void clearRunners();
}
#endif   /* ----- #ifndef RUNNER_INC  ----- */
