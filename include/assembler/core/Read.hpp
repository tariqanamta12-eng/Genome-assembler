#pragma once
#include <cstddef>
#include <string>

namespace assembler {

class Read {
public:
    Read(const std::string& name,
         const std::string& sequence,
         const std::string& quality);

    const std::string& name() const;
    const std::string& sequence() const;
    const std::string& quality() const;

    std::size_t length() const;

private:
    std::string name_;
    std::string sequence_;
    std::string quality_;
};

}  // namespace assembler