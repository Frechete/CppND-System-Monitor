#include "gtest/gtest.h"
#include "../include/system.h"
#include "../include/format.h"
#include <string>

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
    
    EXPECT_EQ(test.OperatingSystem().substr(0, 5), ("Ubuntu"));
}
