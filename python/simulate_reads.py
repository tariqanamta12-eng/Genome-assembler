#!/usr/bin/env python3
"""Simulate single-end FASTQ reads (with substitution errors) from a FASTA genome.

Example:
    python python/simulate_reads.py data/phiX174.fa -o reads.fastq \
        --read-len 100 --coverage 50 --error 0.01 --seed 42
"""
import argparse
import random

COMP = str.maketrans("ACGT", "TGCA")


def read_fasta(path):
    seq = []
    with open(path) as f:
        for line in f:
            if not line.startswith(">"):
                seq.append(line.strip().upper())
    return "".join(seq)


def revcomp(s):
    return s.translate(COMP)[::-1]


def mutate(read, rate, rng):
    out = list(read)
    for i, b in enumerate(out):
        if rng.random() < rate:
            out[i] = rng.choice([x for x in "ACGT" if x != b])
    return "".join(out)


def main():
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawTextHelpFormatter)
    p.add_argument("genome")
    p.add_argument("-o", "--output", default="reads.fastq")
    p.add_argument("--read-len", type=int, default=100)
    p.add_argument("--coverage", type=float, default=50)
    p.add_argument("--error", type=float, default=0.01, help="per-base substitution rate")
    p.add_argument("--seed", type=int, default=42)
    a = p.parse_args()

    rng = random.Random(a.seed)
    genome = read_fasta(a.genome)
    n_reads = int(a.coverage * len(genome) / a.read_len)

    with open(a.output, "w") as out:
        for i in range(n_reads):
            start = rng.randint(0, len(genome) - a.read_len)
            read = genome[start:start + a.read_len]
            if rng.random() < 0.5:           # reads come from both strands
                read = revcomp(read)
            read = mutate(read, a.error, rng)
            out.write(f"@read{i}\n{read}\n+\n{'I' * a.read_len}\n")

    print(f"Genome: {len(genome)} bp | wrote {n_reads} reads to {a.output}")


if __name__ == "__main__":
    main()
