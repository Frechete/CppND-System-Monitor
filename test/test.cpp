#include "gtest/gtest.h"
#include "../include/system.h"
#include "../include/format.h"
#include <string>

TEST(blaTest, test1) {
    //arrange
    //act
    //assert
    System test;
    
    EXPECT_EQ (Format::ElapsedTime(0.0),  "00:00:00");
}
