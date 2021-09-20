#include "gtest/gtest.h"

#include "ship_test.hpp"
#include "compstrat_test.hpp"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
