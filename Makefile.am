ACLOCAL_AMFLAGS=-I m4

AM_CXXFLAGS=-std=c++11 -Wall -Werror
lib_LTLIBRARIES = libattest.la
libattest_la_SOURCES = src/main.cpp src/attest.cpp
pkginclude_HEADERS = include/attest/attest.h

check_PROGRAMS = test_register
test_register_SOURCES = test/test_register.cpp
test_register_LDADD = libattest.la

TESTS = test_register
