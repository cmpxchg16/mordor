// Copyright (c) 2009 - Mozy, Inc.

#include "mordor/predef.h"

#include "stdoutlistener.h"

#include <iostream>

#include <boost/exception/all.hpp>

using namespace Mordor;
using namespace Mordor::Test;

StdoutListener::StdoutListener()
: m_tests(0),
  m_success(0),
  m_skip(0)
{}

void
StdoutListener::testStarted(const std::string &suite, const std::string &test)
{
    if (test != "<invariant>")
        ++m_tests;
    std::cout << "Running " << suite << "::" << test << ": ";
    std::cout.flush();
}

void
StdoutListener::testComplete(const std::string &suite, const std::string &test)
{
    if (test != "<invariant>")
        ++m_success;
    std::cout << "OK" << std::endl;
}

void
StdoutListener::testSkipped(const std::string &suite, const std::string &test)
{
    if (test != "<invariant>") {
        ++m_skip;
        --m_tests;
    }
    std::cout << "skipped" << std::endl;
}

void
StdoutListener::testAsserted(const std::string &suite, const std::string &test,
                             const Assertion &assertion)
{
    std::cerr << "Assertion: "
        << boost::current_exception_diagnostic_information() << std::endl;
    m_failures.push_back(std::make_pair(suite, test));
}

void
StdoutListener::testException(const std::string &suite, const std::string &test)
{
    std::cerr << "Unexpected exception: "
        << boost::current_exception_diagnostic_information() << std::endl;
    m_failures.push_back(std::make_pair(suite, test));
}

void
StdoutListener::testsComplete()
{
    std::cout << "Tests complete.  " << m_success << "/" << m_tests
        << " passed, " << m_skip << " skipped." << std::endl;
    if (!m_failures.empty()) {
        std::cout << "Failures:" << std::endl;
        for (std::vector<std::pair<std::string, std::string> >::iterator
            it = m_failures.begin();
            it != m_failures.end();
            ++it)
                std::cout << '\t' << it->first << "::" << it->second
                    << std::endl;
    }
}
