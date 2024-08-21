#include <gtest/gtest.h>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    // Custom initialization code
    return RUN_ALL_TESTS();
}
