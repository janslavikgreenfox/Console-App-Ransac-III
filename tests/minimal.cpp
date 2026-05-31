#pragma message(">>> minimal.cpp is compiled")

#include <gtest/gtest.h>

#ifndef TEST
#error "TEST macro missing or broken"
#endif

int dummy = 123;

TEST(Smoke, Works)
{
    EXPECT_EQ(dummy, 123);
}