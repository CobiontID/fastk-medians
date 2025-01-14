# fastk-medians
A set of utilities to calculate the median number of times the k-mers in a sequence of interest occur across the whole set. For high-quality sequencing reads, this provides a rough approximation of coverage.

The code is based on the Profex module of [FastK](https://github.com/thegenemyers/FASTK), and is intended to be used in conjunction with FastK. Though it is possible to obtain medians by processing the standard Profex output, performing the calculations directly via the C-library interface is more efficient.

## ProfMedian
This program is based on FastK's Profex ([commit 8b5b988](https://github.com/thegenemyers/FASTK/blob/8b5b9884b6b78cce2862a606a2ed71556b84ac75/Profex.c)), but returns the median count for each read in a list, instead of a full list of k-mer counts. It requires a FastK profile file as input.

Usage:

Generate a profile for a read set using FASTK:

`./FastK -k<k-mer length> -p -v <file with sequences>`

Then get the median counts:

`./ProfMedian <profile: .prof> <read id: list of integers >= 1>`

## ProfMedianAll

This tool performs the same calculation as ProfMedian, but iterates through the full read set in the profile.

Usage: 
`./ProfMedianAll <profile: .prof>`

## Installation
Download the files from this repository, navigate to the `src` directory, and run `make`. This will compile the programs described above, as well as the standard FastK binaries ([commit f7365de](https://github.com/CobiontID/fastk-medians/tree/f7365de8a2aeb774262bda6d722fe5ce943ea959)).

## Additional info on FastK
For the original FastK Readme, see [here](README_FastK.md) or visit https://github.com/thegenemyers/FASTK

## Licensing
This repository incorporates code from multiple pieces of software, for which the terms can be found under:

- FastK: src/LICENSE
- Htslib: src/HTSLIB/LICENSE
- Libdeflate: src/LIBDEFLATE/COPYING
