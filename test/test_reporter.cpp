/*
 * =====================================================================================
 *
 *       Filename:  test_reporter.cpp
 *
 *    Description:  Unit tests for the core Reporter class
 *
 *        Version:  1.0
 *        Created:  24/06/13 12:42:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Graham Cox (coxg), graham@grahamcox.co.uk
 *        Company:  
 *
 * =====================================================================================
 */

#include "attest/reporter.h"
#include "test_harness.h"
#include <iostream>
#include <typeinfo>

class ReporterImpl : public Attest::Reporter {
    public:
        ReporterImpl() {
            std::cout << "Creating ReporterImpl" << std::endl;
        }
        virtual ~ReporterImpl() {
            std::cout << "Killing ReporterImpl" << std::endl;
        }

        virtual void configureOptions(boost::program_options::options_description& options) {
        }
        virtual void processOptions(const boost::program_options::variables_map& options) {
        }
};

int main(void) {
    run("test_register_unique_name", [](){
        Attest::clearReporters();
        if (!Attest::registerReporter("reporter", [](){return std::unique_ptr<Attest::Reporter>(new ReporterImpl);})) {
            throw "Registration failed";
        }
    });
    run("test_register_non-unique_name", [](){
        Attest::clearReporters();
        Attest::registerReporter("reporter", [](){return std::unique_ptr<Attest::Reporter>(new ReporterImpl);});

        if (Attest::registerReporter("reporter", [](){return std::unique_ptr<Attest::Reporter>(new ReporterImpl);})) {
            throw "Registration should have failed";
        }
    });
    run("test_create_unknown_reporter", [](){
        auto reporter = Attest::buildReporter("unknown");
        if (reporter) {
            throw "Somehow we constructed something!";
        }
    });
    run("test_create_reporter", [](){
        Attest::registerReporter("reporter", [](){return std::unique_ptr<Attest::Reporter>(new ReporterImpl);});
        auto reporter = Attest::buildReporter("reporter");
        if (!reporter) {
            throw "Somehow we constructed something!";
        }
        if (typeid(*reporter) != typeid(ReporterImpl)) {
            std::cerr << "Got " << typeid(*reporter).name() << " but wanted " << typeid(ReporterImpl).name() << std::endl;
            throw "Wrong type returned";
        }
    });
    return test_result ? 0 : 1;

}
