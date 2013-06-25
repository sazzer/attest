/*
 * =====================================================================================
 *
 *       Filename:  test_reporter.cpp
 *
 *    Description:  Unit tests for the core Runner class
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

class RunnerImpl : public Attest::Runner {
    public:
        RunnerImpl() {
            std::cout << "Creating RunnerImpl" << std::endl;
        }
        virtual ~RunnerImpl() {
            std::cout << "Killing RunnerImpl" << std::endl;
        }

        virtual void configureOptions(boost::program_options::options_description& options) {
        }
        virtual void processOptions(const boost::program_options::variables_map& options) {
        }
};

int main(void) {
    run("test_register_unique_name", [](){
        Attest::clearRunners();
        if (!Attest::registerRunner("reporter", [](){return std::unique_ptr<Attest::Runner>(new RunnerImpl);})) {
            throw "Registration failed";
        }
    });
    run("test_register_non-unique_name", [](){
        Attest::clearRunners();
        Attest::registerRunner("reporter", [](){return std::unique_ptr<Attest::Runner>(new RunnerImpl);});

        if (Attest::registerRunner("reporter", [](){return std::unique_ptr<Attest::Runner>(new RunnerImpl);})) {
            throw "Registration should have failed";
        }
    });
    run("test_create_unknown_reporter", [](){
        auto reporter = Attest::buildRunner("unknown");
        if (reporter) {
            throw "Somehow we constructed something!";
        }
    });
    run("test_create_reporter", [](){
        Attest::registerRunner("reporter", [](){return std::unique_ptr<Attest::Runner>(new RunnerImpl);});
        auto reporter = Attest::buildRunner("reporter");
        if (!reporter) {
            throw "Somehow we constructed something!";
        }
        if (typeid(*reporter) != typeid(RunnerImpl)) {
            std::cerr << "Got " << typeid(*reporter).name() << " but wanted " << typeid(RunnerImpl).name() << std::endl;
            throw "Wrong type returned";
        }
    });
    return test_result ? 0 : 1;

}