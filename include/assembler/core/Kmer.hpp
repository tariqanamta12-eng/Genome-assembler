#pragma once
#include <cstdint>
#include <cstddef>
#include <string>

namespace assembler {

// A DNA k-mer packed 2 bits per base into a uint64_t (A=00, C=01, G=10, T=11).
// Supports k <= 31, so one k-mer is a single machine word.
class Kmer {
public:
    static constexpr std::size_t MAX_K = 31;

    // Throws std::invalid_argument on bad characters or k > MAX_K / k == 0.
    explicit Kmer(const std::string& sequence);
    double gcContent() const;
    std::size_t k() const { return k_; }
    std::uint64_t bits() const { return bits_; }

    std::string toString() const;
    Kmer reverseComplement() const;
    // Smaller of (this, reverse complement): treats both strands as one node.
    Kmer canonical() const;

    bool operator==(const Kmer& o) const { return bits_ == o.bits_ && k_ == o.k_; }
    bool operator!=(const Kmer& o) const { return !(*this == o); }
    bool operator<(const Kmer& o) const { return bits_ < o.bits_; }

private:
    Kmer(std::uint64_t bits, std::size_t k) : bits_(bits), k_(k) {}

    std::uint64_t bits_;
    std::size_t k_;
};

}  // namespace assembler
