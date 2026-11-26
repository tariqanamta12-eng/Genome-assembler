#include <gtest/gtest.h>

#include "assembler/core/Read.hpp"

using assembler::Read;

TEST(ReadTest, GettersAndLength) {
    Read read("@read1", "ACGT", "!!!!");

    EXPECT_EQ(read.name(), "@read1");
    EXPECT_EQ(read.sequence(), "ACGT");
    EXPECT_EQ(read.quality(), "!!!!");
    EXPECT_EQ(read.length(), 4u);
}