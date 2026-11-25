#include "assembler/core/Kmer.hpp"
#include <stdexcept>

namespace assembler {

namespace {
std::uint64_t encodeBase(char c) {
    switch (c) {
        case 'A': case 'a': return 0;
        case 'C': case 'c': return 1;
        case 'G': case 'g': return 2;
        case 'T': case 't': return 3;
        default: throw std::invalid_argument(std::string("Invalid DNA base: ") + c);
    }
}
constexpr char DECODE[4] = {'A', 'C', 'G', 'T'};
}  // namespace

Kmer::Kmer(const std::string& sequence) : bits_(0), k_(sequence.size()) {
    if (k_ == 0 || k_ > MAX_K)
        throw std::invalid_argument("k must be between 1 and 31");
    for (char c : sequence)
        bits_ = (bits_ << 2) | encodeBase(c);
}

std::string Kmer::toString() const {
    std::string s(k_, 'A');
    std::uint64_t b = bits_;
    for (std::size_t i = k_; i-- > 0;) {
        s[i] = DECODE[b & 3];
        b >>= 2;
    }
    return s;
}

Kmer Kmer::reverseComplement() const {
    std::uint64_t rc = 0, b = bits_;
    for (std::size_t i = 0; i < k_; ++i) {
        rc = (rc << 2) | (3 - (b & 3));  // complement: A<->T, C<->G
        b >>= 2;
    }
    return Kmer(rc, k_);
}

Kmer Kmer::canonical() const {
    Kmer rc = reverseComplement();
    return (rc.bits_ < bits_) ? rc : *this;
}

}  // namespace assembler
