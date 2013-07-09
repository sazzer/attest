/*
 * =====================================================================================
 *
 *       Filename:  real_test.cpp
 *
 *    Description:  
 *
 *        Version:  0.1
 *        Created:  04/07/13 20:10:32
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Graham Cox (coxg), graham@grahamcox.co.uk
 *        Company:  
 *
 * =====================================================================================
 */

#include "attest/attest.h"
#include "attest/assert.h"

ATTEST("Simple maths", [](){
    Attest::Assert::equals(4, 2 + 2);
});

ATTEST("Complex maths", [](){
    Attest::Assert::equals(4, 2 * 2);
});
