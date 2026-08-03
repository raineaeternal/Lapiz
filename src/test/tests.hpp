#pragma once

#include "_config.h"
#include "utilities/logging.hpp"

#include <functional>
#include <vector>

extern std::vector<std::function<void()>> tests;

#define TEST(name)                                                                 \
    static void name();                                                            \
    void __attribute__((constructor)) add_test_##name() { tests.push_back(name); } \
    static void name()

#define LOG_OK(str, ...) INFO("OK: " str __VA_OPT__(, ) __VA_ARGS__)
#define LOG_FAIL(str, ...) ERROR("FAIL: " str __VA_OPT__(, ) __VA_ARGS__)
