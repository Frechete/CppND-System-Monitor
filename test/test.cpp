#include "gtest/gtest.h"
#include "../include/system.h"
#include "../include/format.h"
#include "../include/processor.h"
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
    
    EXPECT_EQ(test.OperatingSystem().substr(0, 6), ("Ubuntu"));
}


TEST(ProcessorTest, test1) {
    //arrange
    //act
    //assert
    Processor test;
    for (int i = 0; i < 5; i++) {
        sleep(1);
        EXPECT_TRUE(test.Utilization() < 100);
    }
    
}
