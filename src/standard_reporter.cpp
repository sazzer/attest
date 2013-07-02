/*
 * =====================================================================================
 *
 *       Filename:  standard_reporter.cpp
 *
 *    Description:  Implementation of the standard reporter
 *
 *        Version:  1.0
 *        Created:  24/06/13 21:26:16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Graham Cox (coxg), graham@grahamcox.co.uk
 *        Company:  
 *
 * =====================================================================================
 */

#include "attest/standard_reporter.h"

namespace Attest {
    namespace Runners {
        /**
         * Configure the options that are supported by this reporter
         * @param options The options object to configure
         */
        void StandardRunner::configureOptions(boost::program_options::options_description& options) {
            options.add_options()
                ("output", boost::program_options::value<std::string>(), "Write output to the specified file");
        }

        /**
         * Configure the reporter based on the variables provided by the supplied variables map
         * @param options The options to use to configure the reporter
         */
        void StandardRunner::processOptions(const boost::program_options::variables_map& options) {
            if (options.count("output")) {
                outputFile_ = options["output"].as<std::string>();
            }
        }

        /**
         * Determine the current output file that is stored
         * @return the name of the output file
         */
        const std::string& StandardRunner::outputFile() const {
            return outputFile_;
        }

        const static bool registered = ::Attest::registerRunner("standard", [](){
            return std::unique_ptr<Attest::Runner>(new StandardRunner);
        });
    }
}
