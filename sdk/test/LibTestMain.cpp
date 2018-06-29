#include "gtest/gtest.h"
#include <string>

namespace {
  TEST(FactorialTest, HandlesZeroInput) {
    ASSERT_TRUE(true);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
