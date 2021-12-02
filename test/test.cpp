#include "gtest/gtest.h"
#include "../include/system.h"
#include "../include/format.h"
#include <string>
#include "gtest/gmock-matchers.h"

using ::testing::HasSubstr;
TEST(FormatTest, test1) {
    //arrange
    //act
    //assert
    
    EXPECT_EQ (Format::ElapsedTime(0.0),  "00:00:00");
}

TEST(SystemTest, test1) {
    //arrange
    //act
    //assert
    System test;
    
    EXPECT_THAT(test.OperatingSystem(), (HasSubstr("Ubuntu")));
}
