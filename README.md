# Genome Assembler (de Bruijn graph, C++)

Short-read genome assembler built for an OOP-with-C++ course.

## Build
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j4
ctest --test-dir build --output-on-failure   # run unit tests
./build/assembler reads.fastq -k 31 -o contigs.fasta
```
Debug with sanitizers: `cmake -B build-debug -DCMAKE_BUILD_TYPE=Debug -DENABLE_SANITIZERS=ON`

## Layout
`include/assembler/` headers - `src/` implementations - `tests/` GoogleTest - `python/` read simulator & evaluation - `notebooks/` Colab demo
