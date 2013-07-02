/*
 * =====================================================================================
 *
 *       Filename:  test_standard_reporter.cpp
 *
 *    Description:  Unit tests for the standard reporter
 *
 *        Version:  1.0
 *        Created:  24/06/13 21:50:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Graham Cox (coxg), graham@grahamcox.co.uk
 *        Company:  
 *
 * =====================================================================================
 */

#include "attest/standard_reporter.h"
#include <cstring>
#include "test_harness.h"
#include <boost/program_options.hpp>

int main(void) {
    run("test_options", [](){
        Attest::Runners::StandardRunner reporter;
        boost::program_options::options_description desc("Allowed options");
        reporter.configureOptions(desc);
        std::cout << desc << std::endl;
    });

    run("test_store_options", [](){
        Attest::Runners::StandardRunner reporter;
        boost::program_options::options_description desc("Allowed options");
        reporter.configureOptions(desc);
        
        boost::program_options::variables_map vm;
        const char* args[] = {"", "--output", "/tmp/output"};
        boost::program_options::store(boost::program_options::parse_command_line(3, args, desc), vm);
        boost::program_options::notify(vm);

        reporter.processOptions(vm);
        std::cout << "Output file: " << reporter.outputFile() << std::endl;
        if (reporter.outputFile() != "/tmp/output") {
            throw "Wrong output file recorded";
        }
    });

    return test_result ? 0 : 1;
}


