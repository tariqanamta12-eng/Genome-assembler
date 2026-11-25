#include <gtest/gtest.h>
#include "assembler/core/Kmer.hpp"

using assembler::Kmer;

TEST(Kmer, RoundTrip) {
    EXPECT_EQ(Kmer("ACGTACGT").toString(), "ACGTACGT");
}

TEST(Kmer, ReverseComplement) {
    EXPECT_EQ(Kmer("AAGC").reverseComplement().toString(), "GCTT");
}

TEST(Kmer, ReverseComplementTwiceIsIdentity) {
    Kmer k("ACGTTGCA");
    EXPECT_EQ(k.reverseComplement().reverseComplement(), k);
}

TEST(Kmer, CanonicalSameForBothStrands) {
    Kmer k("AAGC");
    EXPECT_EQ(k.canonical(), k.reverseComplement().canonical());
}

TEST(Kmer, InvalidInputThrows) {
    EXPECT_THROW(Kmer("ACGN"), std::invalid_argument);
    EXPECT_THROW(Kmer(""), std::invalid_argument);
    EXPECT_THROW(Kmer(std::string(32, 'A')), std::invalid_argument);
}
