attest
======

Simple C++11 Unit Testing Framework 

Summary
-------
Attest is a library to make unit testing in a C++11 environment easy to implement and use, and remove some of the barriers that exist in other frameworks. Features include:
* Automatic registration of tests
* Tests are any Functor that can be called with no arguments and no return, so can include Lambda Functions if so desired (In fact, this is recommended)
* Assertion structure that makes checks easy to write
* Reporters that can be used independent to the tests to output test results as you desire (Only one exists at present)

Requirements
------------
In order to build Attest, you will need a C++11 Compiler - only g++ has been tested, and almost certainly others will currently fail - and Boost Program Options. There are no other dependencies on other libraries at this time.

Building/Installation
---------------------
The latest version of attest can be downloaded from: https://github.com/sazzer/attest/raw/distributions/attest-0.1.tar.gz

Compilation from a tar.gz archive follows the typical autoconf process of 
* ./configure
* make clean all check
* sudo make install

Compilation from the source tree needs an additional step of running
* autoreconf

to generate the configure scripts before they can be run.

Usage
-----
Using Attest is a simple case of writing unit test code, compiling them up and then linking them with the attest libraries. This will produce an executable that you can run that will autodiscover the unit tests that have been written, execute them, and report the results using one of the reporters as required.

A trivial example of a unit test can be found in tests/real_test.cpp. This shows two different tests that will be run, both of which happen to pass successfully. For ease of understanding, this looks like this:

    #include <attest/attest.h>
    #include <attest/assert.h>

    ATTEST("Simple maths", [](){
        Attest::Assert::equals(4, 2 + 2);
    });

The ATTEST macro registers a new function to act as a unit test, and gives it a name. These names don't have to be unique, but it is recommended that they are to avoid confusion. There is also no guarantee of the order that tests are run in, so dependencies between tests should be avoided.

The second argument to the macro in this case is a simple C++11 Lambda Function, which takes no parameters and returns nothing. This can actually be anything that can be coerced into std::function<void (void)>, but a lambda is the easiest and most obvious solution here.

Inside the function, anything that causes an exception to be thrown that will leave the function will cause the test to fail. Anything else will cause the test to succeed. All of the assertion routines in the Attest::Assert namespace will ultimately throw an exception if something goes wrong, which thus causes the test to fail. You can use your own exceptions if you so desire, and this will work fine. If the exception extends std::exception then the result of what() will be shown as the failure message. Alternatively, if you just throw a string then that string will be shown as the failure message. Anything else will cause the failure message to be a generic output. All of the Assert methods also take an optional final argument which is the message to show, and if not provided then a reasonable default will be used instead.

Once you have written all of your test code, you simply need to compile and link it into an executable that can then be run. This executable will return 0 on success and 1 on failure, following standard shell conventions. This means that it can then be used to pass/fail a normal Makefile build, or an Automake/CMake/etc build as necessary. Compilation and Linking is supported by use of a pkg-config configuration file, so the following is all that is needed to make the tests work:

    $ g++ test1.cpp -o test1.o --std=c++11 `pkg-config --cflags attest`
    $ g++ test2.cpp -o test2.o --std=c++11 `pkg-config --cflags attest`
    $ g++ test3.cpp -o test3.o --std=c++11 `pkg-config --cflags attest`
    $ g++ test1.o test2.o test3.o -o tests --std=c++11 `pkg-config --libs attest`

This will then produce an executable called "tests" that contains all of the unit tests defined in the source files "test1.cpp", "test2.cpp" and "test3.cpp". Running "tests" will then run all of these tests and report on the output. Note the mandatory compiler flag "--std=c++11" here, because the library depends heavily on C++11 features that would otherwise not be available.
