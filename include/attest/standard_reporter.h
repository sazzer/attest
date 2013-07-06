/*
 * =====================================================================================
 *
 *       Filename:  standard_reporter.h
 *
 *    Description:  Standard reporter that simply outputs everything to standard output or a file
 *
 *        Version:  1.0
 *        Created:  24/06/13 21:21:33
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Graham Cox (coxg), graham@grahamcox.co.uk
 *        Company:  
 *
 * =====================================================================================
 */


#ifndef  STANDARD_RUNNER_INC
#define  STANDARD_RUNNER_INC

#include "attest/reporter.h"
#include <string>
#include <list>
#include <fstream>

namespace Attest {
    namespace Reporters {
        /**
         * Class to represent a reporter to use to run the test and produce output
         */
        class StandardReporter : public ::Attest::Reporter {
            public:
                /**
                 * Virtual destructor
                 */
                virtual ~StandardReporter() {
                }
                /**
                 * Configure the options that are supported by this reporter
                 * @param options The options object to configure
                 */
                virtual void configureOptions(boost::program_options::options_description& options) const override;

                /**
                 * Configure the reporter based on the variables provided by the supplied variables map
                 * @param options The options to use to configure the reporter
                 */
                virtual void processOptions(const boost::program_options::variables_map& options) override;

                /**
                 * Determine the current output file that is stored
                 * @return the name of the output file
                 */
                const std::string& outputFile() const;
                /**
                 * Start recording of test output.
                 */
                virtual void start() override;
                /**
                 * Record a single test output.
                 * @param result The result to record
                 */
                virtual void record(const ::Attest::TestResult& result) override;
                /**
                 * Finish recording all of the tests
                 */
                virtual void end() override;
            protected:
                /**
                 * Return a reference to the output stream to write to.
                 * This is either this->outputStream_ if that is valid, or std::cout otherwise
                 * @return the output stream.
                 */
                std::ostream& outputStream();
            private:
                /** The filename to write to. Might not be specified */
                std::string outputFile_;
                /** The list of results that we've seen */
                std::list<Attest::TestResult> results_;
                /** The output stream to use */
                std::ofstream outputStream_;
        };
    }
}
#endif   /* ----- #ifndef STANDARD_RUNNER_INC  ----- */
