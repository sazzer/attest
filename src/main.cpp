/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  The main entrypoint into running the tests
 *
 *        Version:  0.1
 *        Created:  16/06/13 18:22:35
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Graham Cox (coxg), graham@grahamcox.co.uk
 *        Company:  
 *
 * =====================================================================================
 */

#include "attest/attest_runner.h"
#include "attest/reporter.h"
#include <iostream>

/**
 * Main entrypoint into the application
 * @param argc The arguments count
 * @param argv The actual arguments
 * @return status code
 */
int main(const int argc, const char** argv) {
    std::unique_ptr<Attest::Reporter> reporter = Attest::buildReporter("standard");

    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
        ("help", "Help on using the reporter");
    reporter->configureOptions(desc);

    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
    boost::program_options::notify(vm);
    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 0;
    }
    else {
        reporter->processOptions(vm);
        reporter->start();
        bool success = Attest::run_tests([&](const Attest::TestResult& r){
            reporter->record(r);
        });
        reporter->end();
        return success ? 0 : 1;
    }
}
