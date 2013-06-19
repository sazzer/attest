/*
 * =====================================================================================
 *
 *       Filename:  assert.h
 *
 *    Description:  Assertions for use in unit tests
 *
 *        Version:  1.0
 *        Created:  18/06/13 20:11:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Graham Cox (coxg), graham@grahamcox.co.uk
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdexcept>
#include <string>
#include <sstream>

#ifndef  ASSERT_INC
#define  ASSERT_INC

namespace Attest {
    namespace Assert {
        /**
         * Exception thrown when an assertion fails
         */
        class AssertionException : public std::exception {
            public:
                /**
                 * Construct the assertion with the provided message
                 * @param what_ the message to use
                 */
                explicit AssertionException(const std::string& what_) : w(what_) {
                }
                /**
                 * Return the message from the assertion failure
                 * @return the message
                 */
                virtual const char* what() const noexcept {
                    return w.c_str();
                }
            protected:
            private:
                /** The error message */
                const std::string w;
        };

        /**
         * Assert that two values are equal to each other
         * @param expected The expected value
         * @param actual The actual value
         * @param message The optional message to use if the values differ
         */
        template<typename A, typename B>
        void equals(const A& expected, const B& actual, const char* message = 0) {
            std::string msg;
            if (message == 0) {
                std::stringstream msgstream;
                msgstream << "Assertion error: Expected equal to '" << expected << "' but got '" << actual << "'";
                msg = msgstream.str();
            } else {
                msg = message;
            }
            if (!(expected == actual)) {
                throw AssertionException(msg);
            }
        }

        /**
         * Assert that two values are equal to each other
         * @param expected The expected value
         * @param actual The actual value
         * @param message The optional message to use if the values differ.
         */
        template<typename A, typename B>
        void not_equals(const A& expected, const B& actual, const char* message = 0) {
            std::string msg;
            if (message == 0) {
                std::stringstream msgstream;
                msgstream << "Assertion error: Expected not equal to '" << expected << "' but got '" << actual << "'";
                msg = msgstream.str();
            } else {
                msg = message;
            }
            if (!(expected != actual)) {
                throw AssertionException(msg);
            }
        }

        /**
         * Assert that two values are equal to each other
         * @param expected The expected value
         * @param actual The actual value
         * @param message The optional message to use if the values differ.
         */
        template<typename A, typename B>
        void less_than(const A& expected, const B& actual, const char* message = 0) {
            std::string msg;
            if (message == 0) {
                std::stringstream msgstream;
                msgstream << "Assertion error: Expected less than '" << expected << "' but got '" << actual << "'";
                msg = msgstream.str();
            } else {
                msg = message;
            }
            if (!(expected < actual)) {
                throw AssertionException(msg);
            }
        }

        /**
         * Assert that two values are equal to each other
         * @param expected The expected value
         * @param actual The actual value
         * @param message The optional message to use if the values differ.
         */
        template<typename A, typename B>
        void less_than_or_equal(const A& expected, const B& actual, const char* message = 0) {
            std::string msg;
            if (message == 0) {
                std::stringstream msgstream;
                msgstream << "Assertion error: Expected less than or equal to '" << expected << "' but got '" << actual << "'";
                msg = msgstream.str();
            } else {
                msg = message;
            }
            if (!(expected <= actual)) {
                throw AssertionException(msg);
            }
        }

        /**
         * Assert that two values are equal to each other
         * @param expected The expected value
         * @param actual The actual value
         * @param message The optional message to use if the values differ.
         */
        template<typename A, typename B>
        void greater_than(const A& expected, const B& actual, const char* message = 0) {
            std::string msg;
            if (message == 0) {
                std::stringstream msgstream;
                msgstream << "Assertion error: Expected greater than '" << expected << "' but got '" << actual << "'";
                msg = msgstream.str();
            } else {
                msg = message;
            }
            if (!(expected > actual)) {
                throw AssertionException(msg);
            }
        }

        /**
         * Assert that two values are equal to each other
         * @param expected The expected value
         * @param actual The actual value
         * @param message The optional message to use if the values differ.
         */
        template<typename A, typename B>
        void greater_than_or_equal(const A& expected, const B& actual, const char* message = 0) {
            std::string msg;
            if (message == 0) {
                std::stringstream msgstream;
                msgstream << "Assertion error: Expected greater than or equal to '" << expected << "' but got '" << actual << "'";
                msg = msgstream.str();
            } else {
                msg = message;
            }
            if (!(expected >= actual)) {
                throw AssertionException(msg);
            }
        }
    }
}
#endif   /* ----- #ifndef ASSERT_INC  ----- */
