#include <iostream>
#include <string>
#include "assembler/core/Kmer.hpp"

// Keep main thin: parse arguments, build an AssemblerConfig, call Assembler.
// For now it only demonstrates the Kmer class so the build can be verified.
int main(int argc, char** argv) {
    std::string input, output = "contigs.fasta";
    std::size_t k = 31;

    for (int i = 1; i < argc; ++i) {
        std::string a = argv[i];
        if (a == "-k" && i + 1 < argc)      k = std::stoul(argv[++i]);
        else if (a == "-o" && i + 1 < argc) output = argv[++i];
        else                                input = a;
    }

    if (input.empty()) {
        std::cerr << "Usage: assembler reads.fastq [-k 31] [-o contigs.fasta]\n";
        return 1;
    }

    std::cout << "[stub] input=" << input << " k=" << k << " output=" << output << "\n";
    std::cout << "[stub] Assembly pipeline not implemented yet.\n";

    assembler::Kmer demo("ACGTAC");
    std::cout << "Kmer demo: " << demo.toString()
              << " revcomp=" << demo.reverseComplement().toString()
              << " canonical=" << demo.canonical().toString() << "\n";
    return 0;
}
