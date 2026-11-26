#include "assembler/core/Read.hpp"

namespace assembler {

Read::Read(const std::string& name,
           const std::string& sequence,
           const std::string& quality)
    : name_(name),
      sequence_(sequence),
      quality_(quality) {}

const std::string& Read::name() const {
    return name_;
}

const std::string& Read::sequence() const {
    return sequence_;
}

const std::string& Read::quality() const {
    return quality_;
}

std::size_t Read::length() const {
    return sequence_.length();
}

}  // namespace assembler