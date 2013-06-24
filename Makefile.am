ACLOCAL_AMFLAGS=-I m4

AM_CXXFLAGS=-std=c++11 -Wall -Werror
lib_LTLIBRARIES = libattest.la
libattest_la_SOURCES = src/main.cpp src/attest.cpp src/runner.cpp
libattest_la_CPPFLAGS = ${BOOST_CPPFLAGS}
libattest_la_LIBS = ${BOOST_LIBS}

pkginclude_HEADERS = include/attest/attest.h include/attest/assert.h

check_PROGRAMS = test_register
test_register_SOURCES = test/test_register.cpp
test_register_LDADD = libattest.la

check_PROGRAMS += test_auto_register
test_auto_register_SOURCES = test/test_auto_register.cpp
test_auto_register_LDADD = libattest.la

check_PROGRAMS += test_run_tests
test_run_tests_SOURCES = test/test_run_tests.cpp
test_run_tests_LDADD = libattest.la

check_PROGRAMS += test_assertions
test_assertions_SOURCES = test/test_assertions.cpp
test_assertions_LDADD = libattest.la

check_PROGRAMS += test_runner
test_runner_SOURCES = test/test_runner.cpp
test_runner_LDADD = libattest.la

TESTS = test_register test_auto_register test_run_tests test_assertions test_runner
