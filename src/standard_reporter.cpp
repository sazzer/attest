/*
 * =====================================================================================
 *
 *       Filename:  standard_reporter.cpp
 *
 *    Description:  Implementation of the standard reporter
 *
 *        Version:  0.1
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
#include <fstream>

namespace Attest {
    namespace Reporters {
        /**
         * Configure the options that are supported by this reporter
         * @param options The options object to configure
         */
        void StandardReporter::configureOptions(boost::program_options::options_description& options) const {
            options.add_options()
                ("output", boost::program_options::value<std::string>(), "Write output to the specified file");
        }

        /**
         * Configure the reporter based on the variables provided by the supplied variables map
         * @param options The options to use to configure the reporter
         */
        void StandardReporter::processOptions(const boost::program_options::variables_map& options) {
            if (options.count("output")) {
                outputFile_ = options["output"].as<std::string>();
            }
        }

        /**
         * Return a reference to the output stream to write to.
         * This is either this->outputStream_ if that is valid, or std::cout otherwise
         * @return the output stream.
         */
        std::ostream& StandardReporter::outputStream() {
            if (outputStream_.is_open()) {
                return outputStream_;
            }
            else {
                return std::cout;
            }
        }

        /**
         * Determine the current output file that is stored
         * @return the name of the output file
         */
        const std::string& StandardReporter::outputFile() const {
            return outputFile_;
        }

        /**
         * Start recording of test output.
         */
        void StandardReporter::start() {
            results_.clear();
            if (!outputFile_.empty()) {
                outputStream_.open(outputFile_);
            }
        }

        /**
         * Record a single test output.
         * @param result The result to record
         */
        void StandardReporter::record(const ::Attest::TestResult& result) {
            results_.push_back(result);
        }

        /**
         * Finish recording all of the tests
         */
        void StandardReporter::end() {
            std::ostream& output = outputStream();
            size_t tests = 0;
            size_t passed = 0;
            size_t failed = 0;
            for (auto iter = results_.begin(); iter != results_.end(); ++iter, ++tests) {
                output << iter->name << ": ";
                if (iter->success()) {
                    ++passed;
                    output << "SUCCESS" << std::endl;
                }
                else {
                    ++failed;
                    output << "FAILURE" << std::endl;
                    output << ">>> " << iter->error << std::endl;
                }
                if (!iter->output.empty()) {
                    output << "=== " << iter->output << std::endl;
                }
            }
            output << "Tests: " << tests << ", Passed: " << passed << ", Failed: " << failed << std::endl;
        }


        const static bool registered = ::Attest::registerReporter("standard", [](){
            return std::unique_ptr<Attest::Reporter>(new StandardReporter);
        });
    }
}
